#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b005_01E00080;

typedef struct {
    u8 count;
    u8 pad01;
    u8 length;
    u8 mask;
    u8 mode;
    u8 pad05[0xB];
    u8 light[0x10];
    Vec_b005_01E00080 pos;
    u8 pad30[8];
    f32 value;
    u8 pad3C[4];
    Vec_b005_01E00080 vel;
    f32 base;
} Fx_b005_01E00080;

static void func_01E00080_b137(Fx_b005_01E00080 *o) {
    u8 phase;
    u8 mask;
    u8 rest;
    u8 count;
    f32 step;
    u8 length;
    s32 on;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, (s32)&o->pos);
    count = o->count;
    mask = o->mask;
    length = o->length;
    phase = count & mask;
    rest = length - count;
    if (mask == 0xFF) {
        step = o->base / length;
    } else {
        step = o->base / (mask + 1);
    }
    on = 1;
    switch (o->mode & 0xF) {
    case 1:
        o->value = step * phase;
        break;
    case 2:
        if (mask == 0xFF) {
            if (rest < length >> 1) {
                o->value = 2.0f * step * rest;
            } else {
                o->value = 2.0f * step * count;
            }
        } else {
            if (phase < mask >> 1) {
                o->value = 2.0f * step * (mask - phase);
            } else {
                o->value = 2.0f * step * phase;
            }
        }
        break;
    case 4:
        o->value = o->base;
        if (o->count & 1) {
            o->value *= 0.5f;
        }
        break;
    case 8:
        if (count & 1) {
            on = 0;
        }
    default:
        o->value = o->base;
        break;
    }
    if (on == 0 || o->count == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10((s32)o->light);
    }
}

/* shape b029:01E003A0 (ShFx_Smk01), 542 insns, 11 copies (-O3,p): n particle emitters (0x38 bytes each), each with up
   to 8 particles (0x28 bytes, indexes into a shared table): moves each live particle (gravity, floor), sizes it by
   age, and draws it as a textured screen-space quad of radius func_001018E0(scale, depth), flipped by the particle's
   flags & 0x30; the source of shape b122:01E00440, built here at -O3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b029_01E003A0;

typedef struct {
    f32 s, t;
    Xyz_b029_01E003A0 xyz;
} Vtx_b029_01E003A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b029_01E003A0 v[4];
    u8 tail[0x20];
} Pkt_b029_01E003A0;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b029_01E003A0;

typedef struct {
    f32 x, y, z;
} V3_b029_01E003A0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 flags;
    V3_b029_01E003A0 pos;
    V3_b029_01E003A0 vel;
    V3_b029_01E003A0 acc;
} Part_b029_01E003A0;

typedef struct {
    u8 drawn;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Part_b029_01E003A0 *parts;
    s16 idx[8];
    u8 pad1C;
    u8 count;
    u8 sub;
    u8 texid;
    u8 size;
    u8 shift;
    u8 b, g, r, a;
    f32 scale;
    f32 dscale;
    f32 grav;
    f32 floor;
} Emit_b029_01E003A0;

#pragma optimization_level 3

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E003A0_b137(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern f32 func_001018E0(f32, f32);
    f32 mat[16];
    Vec4f pos;
    Tex_b029_01E003A0 td;
    Pkt_b029_01E003A0 pkt __attribute__((aligned(8)));
    Xyz_b029_01E003A0 xyz;
    f32 dep;
    Emit_b029_01E003A0 *e;
    s32 i;
    Part_b029_01E003A0 *parts;
    Part_b029_01E003A0 *p;
    s32 j;
    s32 tex;
    s32 d;
    s32 sz;
    f32 r;

    e = arg0;
    parts = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            tex = func_00202BF0(5, e->texid);
        } else {
            tex = func_00202BF0(4, 2);
        }
        e->scale += e->dscale;
        for (j = 0; j < e->count; j++) {
            if (e->idx[j] == -1) {
                continue;
            }
            p = &parts[e->idx[j]];
            if (p->life < 2) {
                e->idx[j] = -1;
            } else {
                e->drawn = 1;
            }
            if (func_00101B50(p) == 0) {
                continue;
            }
            p->vel.x += p->acc.x;
            p->vel.y += p->acc.y + e->grav;
            p->vel.z += p->acc.z;
            p->pos.x += p->vel.x;
            p->pos.y += p->vel.y;
            p->pos.z += p->vel.z;
            if (p->pos.y < e->floor) {
                p->pos.y = e->floor;
            }
            pos.x = p->pos.x;
            pos.y = p->pos.y;
            pos.z = p->pos.z;
            func_0020EB40(mat);
            ((Pkt_b029_01E003A0 *)(s32)&pkt)->count = 0x24;
            ((Pkt_b029_01E003A0 *)(s32)&pkt)->tag = 9;
            ((Pkt_b029_01E003A0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
            ((Pkt_b029_01E003A0 *)(s32)&pkt)->pad = 0;
            pkt.r = e->r;
            pkt.g = e->g;
            pkt.b = e->b;
            pkt.q = 1.0f;
            d = p->max - p->life;
            sz = e->size;
            if (e->flags & 8) {
                sz = ((d >> e->shift) & 3) + 2;
                if (d < 3) {
                    sz = d;
                }
                if (p->life < 7) {
                    sz = 7 - (p->life >> e->shift);
                }
            }
            td.b5 = e->sub;
            func_001020B0(&td, sz, 0);
            func_00101D20(&pkt, &td, (void *)tex);
            if (p->life < 16) {
                pkt.a = (e->a >> 4) * p->life;
            } else {
                pkt.a = e->a;
            }
            if (func_00205440(&pos, mat, &xyz, &dep) == 0 || func_00101600(&xyz) == 0) {
                continue;
            }
            r = func_001018E0(e->scale, dep);
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xyz.z;
            switch (p->flags & 0x30) {
            case 0x10:
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x - r);
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x20:
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x + r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x30:
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y - r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            default:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x - r);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y - r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            }
            func_002075F0((s32)&pkt, ot, (u32)dep);
        }
    }
    return 1;
}
#pragma optimization_level reset

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Node_b029_01E00C20;

typedef struct {
    u8 pad00[8];
    Node_b029_01E00C20 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
} Sys_b029_01E00C20;

typedef struct {
    Sys_b029_01E00C20 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    f32 cx, cy, cz;
} Burst_b029_01E00C20;

static void func_01E00C20_b137(Burst_b029_01E00C20 *pr) {
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Sys_b029_01E00C20 *s;
    Node_b029_01E00C20 *node;
    s32 i;
    s32 idx;
    f32 angle;
    f32 step;
    f32 c;
    f32 sn;

    s = pr->sys;
    angle = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / s->count;
    for (i = 0; i < s->count; i++) {
        idx = func_00101C30(s->pool, 0x28, s->kind);
        if (idx >= 0) {
            s->ids[i] = idx;
            node = &s->pool[idx];
            func_00101B40(node, pr->life, pr->mask & (func_0019A5C8() >> 4));
            node->frame = ((func_0019A5C8() >> 4) & 3) << 4;
            angle += step;
            if (!(angle <= 360.0f)) {
                angle -= 360.0f;
            }
            c = 3.1415927f * angle / 180.0f;
            c = func_001A6A88(c);
            sn = func_001A6898(3.1415927f * angle / 180.0f);
            node->x = pr->cx + pr->radius * sn;
            node->z = pr->cz + pr->radius * c;
            node->y = pr->cy;
            node->vx = pr->speed * sn;
            node->vz = pr->speed * c;
            node->vy = pr->rise;
            node->ax = -(node->vx / pr->life);
            node->az = -(node->vz / pr->life);
            node->ay = 0.0f;
        } else {
            s->ids[i] = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b137", func_01E00EF0_b137);

INCLUDE_ASM("asm/nonmatchings/mod/b137", func_01E01340_b137);

/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b040:01E01340, 1016 insns: n beam emitters (0x38 bytes each): on first use the two ends come from
   func_00101BA0 (sel = i0, then i1); the beam a-b is drawn as 4 offset lines of half-width func_001018E0(size,
   depth) at each end, plus the extensions past a (ext0) and past b (ext1), far z with flags & 0x80; the
   extensions use a width the original never sets (r2) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b040_01E01340;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b040_01E01340 xyz;
} Vtx_b040_01E01340;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b040_01E01340 v[4];
    u8 tail[8];
} Pkt_b040_01E01340;

typedef struct {
    u8 b, g, r, a;
} Col_b040_01E01340;

typedef struct {
    f32 x, y, z;
} V3_b040_01E01340;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 inited;
    u8 sel;
    u8 pad7;
    u8 i0;
    u8 i1;
    u8 padA[2];
    f32 size;
    f32 ext0;
    f32 ext1;
    Col_b040_01E01340 c1;
    Col_b040_01E01340 c0;
    V3_b040_01E01340 a;
    V3_b040_01E01340 b;
} Emit_b040_01E01340;

static s32 func_01E02460_b137(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern f32 func_001018E0(f32, f32);
    s32 i;
    f32 mat[16];
    Vec4f pt[4];
    Vec4f tmp;
    Xyz_b040_01E01340 xy[4];
    f32 dep[4];
    Pkt_b040_01E01340 pkt __attribute__((aligned(8)));
    Emit_b040_01E01340 *e;
    f32 r0;
    f32 r1;
    f32 r2;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (!(e->flags & 1)) {
            e->inited = 1;
            e->sel = e->i0;
            func_00101BA0(e, &tmp);
            e->a.x = tmp.x;
            e->a.y = tmp.y;
            e->a.z = tmp.z;
            e->sel = e->i1;
            func_00101BA0(e, &tmp);
            e->b.x = tmp.x;
            e->b.y = tmp.y;
            e->b.z = tmp.z;
        }
        pt[0].x = e->a.x;
        pt[0].y = e->a.y;
        pt[0].z = e->a.z;
        pt[1].x = e->b.x;
        pt[1].y = e->b.y;
        pt[1].z = e->b.z;
        pt[2].x = e->a.x + e->ext0 * (e->a.x - e->b.x);
        pt[2].y = e->a.y + e->ext0 * (e->a.y - e->b.y);
        pt[2].z = e->a.z + e->ext0 * (e->a.z - e->b.z);
        pt[3].x = e->b.x - e->ext1 * (e->a.x - e->b.x);
        pt[3].y = e->b.y - e->ext1 * (e->a.y - e->b.y);
        pt[3].z = e->b.z - e->ext1 * (e->a.z - e->b.z);
        func_0020EB40(mat);
        ((Pkt_b040_01E01340 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->tag = 8;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->pad = 0;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        if ((e->flags & 2) && (e->life & 1)) {
            pkt.v[0].a = pkt.v[1].a = e->c0.a >> 1;
            pkt.v[2].a = pkt.v[3].a = e->c1.a >> 1;
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        if (func_00205440(&pt[0], mat, &xy[0], &dep[0]) == 0 || func_00205440(&pt[1], mat, &xy[1], &dep[1]) == 0 ||
            (!(e->ext0 <= 0.0f) && func_00205440(&pt[2], mat, &xy[2], &dep[2]) == 0) ||
            (!(e->ext1 <= 0.0f) &&
             (func_00205440(&pt[3], mat, &xy[3], &dep[3]) == 0 || func_00101600(&xy[3]) == 0))) {
            continue;
        }
        r0 = func_001018E0(e->size, dep[0]);
        r1 = func_001018E0(e->size, dep[1]);
        if (e->flags & 0x80) {
            xy[0].z = xy[1].z = xy[2].z = 0xFFFFFE;
            dep[0] = dep[1] = dep[2] = 0.0f;
        }
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[1].z;
        pkt.v[0].xyz.f = pkt.v[2].xyz.f = pkt.v[1].xyz.f = pkt.v[3].xyz.f = 1;
        pkt.v[2].xyz.y = xy[0].y;
        pkt.v[3].xyz.y = xy[1].y;
        pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y - r1);
        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[1].x;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x - r1);
        pkt.v[2].xyz.x = xy[0].x;
        pkt.v[3].xyz.x = xy[1].x;
        pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
        pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[1].y;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[3].a = 0;
        if (!(e->ext0 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[2].z;
            pkt.v[2].xyz.y = xy[0].y;
            pkt.v[3].xyz.y = xy[2].y;
            pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[2].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x - r2);
            pkt.v[2].xyz.x = xy[0].x;
            pkt.v[3].xyz.x = xy[2].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[2].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        }
        if (!(e->ext1 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[1].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[3].z;
            pkt.v[2].xyz.y = xy[1].y;
            pkt.v[3].xyz.y = xy[3].y;
            pkt.v[0].xyz.y = (u32)(xy[1].y - r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[1].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[3].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.y = (u32)(xy[1].y + r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x - r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x - r2);
            pkt.v[2].xyz.x = xy[1].x;
            pkt.v[3].xyz.x = xy[3].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[1].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[3].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x + r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b137", func_01E03440_b137);

/* shape b285:01E014C0 (ShFx_Mptc), 791 insns, 12 copies (-O3,p): update and draw ribbon emitters (0x58 bytes each);
   every segment is projected straight into the packet's vertex slots and widened on screen; the source of shape
   b024:01E02120, built here at -O3 */

typedef struct Uvs_b285_01E014C0 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b285_01E014C0;

typedef struct Rib_b285_01E014C0 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 div;
    u8 padE[2];
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    f32 rot[4];
} Rib_b285_01E014C0;

typedef struct Xyz_b285_01E014C0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b285_01E014C0;

typedef struct Pk_b285_01E014C0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b285_01E014C0 v[4];
    u64 pad60[3];
} Pk_b285_01E014C0;

static inline void b285_01E014C0_tag(Pk_b285_01E014C0 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 3
typedef struct W_tbl_func_01E02BC0_b536 {
    Uvs_b285_01E014C0 v[4];
} W_tbl_func_01E02BC0_b536;

/* id aligned: its spill slot, needed for the match */
static s32 func_01E04250_b137(Rib_b285_01E014C0 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 w;
    f32 b;
    Rib_b285_01E014C0 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    u8 k;
    s32 tex;
    s32 life;
    f32 rad;
    f32 d;
    f32 a;
    f32 h0;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E02BC0_b536 D_01E06D10_b137;
    W_tbl_func_01E02BC0_b536 tbl_w = D_01E06D10_b137;
    Uvs_b285_01E014C0 uvs;
    Pk_b285_01E014C0 pk;
    f32 depth[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        if (p->flags & 4) {
            tex = func_00202BF0(5, p->idx);
        } else {
            tex = func_00202BF0(tbl_w.v[p->idx].kind, tbl_w.v[p->idx].tex);
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        func_00101BA0(p, p->pos);
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        k = p->k;
        ang = 0.0f;
        life = p->life - p->age;
        b285_01E014C0_tag((Pk_b285_01E014C0 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        if (p->flags & 4) {
            sel = p->frame;
            if (p->flags & 8) {
                sel = life & 7;
                if (life < 3) {
                    sel = life;
                }
                if (p->age < 4) {
                    sel = 7 - p->age;
                }
            }
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, sel, 0);
            func_00101D20(&pk, &uvs, tex);
        } else {
            func_00101D20(&pk, &tbl_w.v[p->idx], tex);
        }
        if (p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        } else {
            pk.a = p->a;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                v.x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                v.y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                v.z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                v.x = a * b * func_001A6898(rad);
                v.z = a * b * func_001A6A88(rad);
                v.y = a * p->scale;
            }
            w = p->width + p->grow * (f32)life;
            if (p->div > 1) {
                d = p->scale / (f32)p->div;
                w = w / (1.0f + func_0020D0E0(&v.x) / d);
            }
            t[0].x = v.x * (f32)life;
            t[0].y = v.y * (f32)life;
            t[0].z = v.z * (f32)life;
            if (func_00205440(&t[0], m, &pk.v[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&pk.v[0]) == 0) {
                continue;
            }
            h0 = func_001018E0(w, depth[0]);
            if (p->flags & 2) {
                t[1].x = t[0].x + 4.0f * v.x;
                t[1].y = t[0].y + 4.0f * v.y;
                t[1].z = t[0].z + 4.0f * v.z;
                if (func_00205440(&t[1], m, &pk.v[2], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&pk.v[2]) == 0) {
                    continue;
                }
                h1 = func_001018E0(w, depth[1]);
                dy = pk.v[2].y - pk.v[0].y;
                dy = dy >= 0 ? dy : -dy;
                dx = pk.v[2].x - pk.v[0].x;
                dx = dx >= 0 ? dx : -dx;
                if (dy < dx) {
                    pk.v[1].x = pk.v[0].x;
                    pk.v[3].x = pk.v[2].x;
                    pk.v[1].y = (u32)(pk.v[0].y + h0);
                    pk.v[0].y = (u32)(pk.v[0].y - h0);
                    pk.v[3].y = (u32)(pk.v[2].y + h1);
                    pk.v[2].y = (u32)(pk.v[2].y - h1);
                } else {
                    pk.v[1].y = pk.v[0].y;
                    pk.v[3].y = pk.v[2].y;
                    pk.v[1].x = (u32)(pk.v[0].x + h0);
                    pk.v[0].x = (u32)(pk.v[0].x - h0);
                    pk.v[3].x = (u32)(pk.v[2].x + h1);
                    pk.v[2].x = (u32)(pk.v[2].x - h1);
                }
                pk.v[1].z = pk.v[0].z;
                pk.v[3].z = pk.v[2].z;
            } else {
                pk.v[1].x = (u32)(pk.v[0].x + h0);
                pk.v[1].y = (u32)(pk.v[0].y - h0);
                pk.v[2].x = (u32)(pk.v[0].x - h0);
                pk.v[2].y = (u32)(pk.v[0].y + h0);
                pk.v[3].x = (u32)(pk.v[0].x + h0);
                pk.v[3].y = (u32)(pk.v[0].y + h0);
                pk.v[0].x = (u32)(pk.v[0].x - h0);
                pk.v[0].y = (u32)(pk.v[0].y - h0);
                pk.v[1].z = pk.v[2].z = pk.v[3].z = pk.v[0].z;
            }
            pk.v[0].fog = pk.v[1].fog = pk.v[2].fog = pk.v[3].fog = 1;
            func_002075F0((s32)&pk, id, (u32)(depth[0]));
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b131:01E03B50, 323 insns (b042:01E038E0 at -O4): trail emitters (0x8C bytes each): move, follow a bone, then spawn
   particles (0x58 bytes) along the path from the last three positions (a spline of 4 points, or just the
   last segment when flags & 1). */

typedef struct {
    u8 r, g, b, a;
} Col_b131_01E03B50;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 f5;
    u8 pad6[2];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
    u8 fC;
    u8 fD;
    u8 padE[2];
    s32 f10;
    f32 len;
    f32 f18;
    f32 f1C;
    f32 f20;
    Col_b131_01E03B50 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 f48[0x10];
} Part_b131_01E03B50;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 attached;
    u8 pad6[2];
    Part_b131_01E03B50 *pool;
    s32 fC;
    u8 kind;
    u8 sub;
    u8 f12;
    u8 f13;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 pad17;
    f32 scale;
    f32 f1C;
    f32 f20;
    f32 f24;
    Col_b131_01E03B50 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
    f32 drift[3];
    u8 pad88[4];
} Emit_b131_01E03B50;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spline_b131_01E03B50;

static s32 func_01E04EB0_b137(Emit_b131_01E03B50 *arg0, s32 arg1, s32 n) {
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101AD0();
    extern void func_00101940();
    Emit_b131_01E03B50 *e = arg0;
    Spline_b131_01E03B50 spl;
    f32 dir[4];
    s32 i;
    s32 j;
    s32 k;
    s32 idx;
    s32 off;
    f32 len;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0 && e->age != e->life - 1) {
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            func_00101BA0(e, &e->pos);
            if (e->attached != 0) {
                e->pos.x += e->off.x;
                e->pos.y += e->off.y;
                e->pos.z += e->off.z;
            }
            if (e->flags & 1) {
                spl.pts[0] = e->pos;
                spl.pts[1] = e->prev;
                k = 1;
            } else {
                spl.n = 3;
                spl.x[0] = e->pos.x;
                spl.y[0] = e->pos.y;
                spl.z[0] = e->pos.z;
                spl.x[1] = e->prev.x;
                spl.y[1] = e->prev.y;
                spl.z[1] = e->prev.z;
                spl.x[2] = e->prev2.x;
                spl.y[2] = e->prev2.y;
                spl.z[2] = e->prev2.z;
                func_00102550(&spl);
                k = 4;
            }
            for (j = 0; j < k; j++) {
                idx = func_00101C30(e->pool, 0x58, e->kind);
                if (idx >= 0) {
                    func_00101AD0(&e->pool[idx], e->sub, 0, 0xFF);
                    dir[0] = spl.pts[j + 1].x - spl.pts[j].x;
                    dir[1] = spl.pts[j + 1].y - spl.pts[j].y;
                    dir[2] = spl.pts[j + 1].z - spl.pts[j].z;
                    len = func_0020D0E0(dir);
                    if (len < 0.3f) {
                        dir[0] += e->drift[0];
                        dir[1] += e->drift[1];
                        dir[2] += e->drift[2];
                    } else if (!(len <= 1.0f)) {
                        func_0020D070(dir);
                    }
                    e->pool[idx].len = func_0020D0E0(dir);
                    if (e->scale) {
                        e->pool[idx].len *= e->scale;
                    }
                    e->pool[idx].f18 = e->f1C;
                    e->pool[idx].flags = 0;
                    if (e->flags & 2) {
                        e->pool[idx].flags |= 4;
                        e->pool[idx].fC = e->f16;
                    }
                    if (e->flags & 4) {
                        e->pool[idx].flags |= 8;
                    }
                    e->pool[idx].f5 = 0;
                    e->pool[idx].f8 = e->f12;
                    e->pool[idx].f1C = e->f20;
                    e->pool[idx].f20 = e->f24;
                    e->pool[idx].f9 = func_0019A5C8() >> 4;
                    e->pool[idx].fA = e->f13;
                    e->pool[idx].fB = e->f14;
                    e->pool[idx].fD = e->f15;
                    e->pool[idx].f10 = e->fC;
                    e->pool[idx].col = e->col;
                    e->pool[idx].pos = spl.pts[j];
                    func_00101940(dir, (u8 *)e->pool + idx * 0x58 + 0x48);
                }
            }
            e->prev2 = e->prev;
            e->prev = e->pos;
        }
    }
    return 1;
}

/* OVL_WARM */

/* shape b029:01E02B80, 696 insns, 37 copies: update and draw ribbon emitters (0x68 bytes each, may turn toward a
   target object); each segment is projected and drawn as a quad from the emitter's origin, widened on screen */

typedef struct Uvs_b029_01E02B80 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b029_01E02B80;

typedef struct Rib_b029_01E02B80 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 b5c;
    u8 frame;
    u8 hold;
    u8 target;
    u8 padF;
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1c, g1, r1, a1;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    s32 rot[3];
    u8 pad54[4];
    s32 drot[3];
    u8 pad64[4];
} Rib_b029_01E02B80;

typedef struct Xyz_b029_01E02B80 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b029_01E02B80;

typedef struct Vtx_b029_01E02B80 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b029_01E02B80 xyz;
} Vtx_b029_01E02B80;

typedef struct Pk_b029_01E02B80 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b029_01E02B80 v[4];
    u8 pad70[0x20];
} Pk_b029_01E02B80;

static inline void b029_01E02B80_tag(Pk_b029_01E02B80 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E053C0_b137(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101EE0();
    extern void func_0020C940();
    extern void func_0020BC00();
    extern void func_00101940();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Rib_b029_01E02B80 *p = arg0;
    s32 i __attribute__((aligned(16)));
    s32 life __attribute__((aligned(16)));
    s32 j __attribute__((aligned(16)));
    s32 tex;
    u8 k;
    s32 dx;
    s32 dy;
    f32 h;
    f32 ang;
    f32 zf;
    f32 x;
    f32 lf;
    f32 half;
    f32 y;
    f32 z;
    f32 b;
    f32 rad;

    f32 m2[4][4];
    f32 m[4][4];
    Xyz_b029_01E02B80 s[2];
    f32 v[4];
    Vec4f d;
    Vec4f tgt;
    extern Uvs_b029_01E02B80 D_01E06D70_b137;
    Uvs_b029_01E02B80 tbl = D_01E06D70_b137;
    Uvs_b029_01E02B80 uvs;
    Pk_b029_01E02B80 pk __attribute__((aligned(8)));
    f32 depth[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        if (p->flags & 4) {
            tex = func_00202BF0(5, p->idx);
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, p->frame, 0);
        } else {
            tex = func_00202BF0(tbl.kind, tbl.tex);
            uvs = tbl;
        }
        if (!(p->flags & 2)) {
            uvs.v0 -= 0x10;
            uvs.v1 -= 0x10;
        }
        ang = 0.0f;
        k = p->k;
        if (p->age < p->hold) {
            life = p->life - p->hold;
        } else {
            life = p->life - p->age;
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->rot[0] += p->drot[0];
        p->rot[1] += p->drot[1];
        p->rot[2] += p->drot[2];
        func_00101BA0(p, p->pos);
        if (p->flags & 8) {
            func_001F5620(func_001F53A0(), p->target, &tgt);
            d.x = tgt.x - p->pos[0];
            d.y = tgt.y - p->pos[1];
            d.z = tgt.z - p->pos[2];
            func_00101940(&d, p->rot);
        }
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        b029_01E02B80_tag((Pk_b029_01E02B80 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
        pk.v[0].r = pk.v[1].r = p->r0;
        pk.v[2].r = pk.v[3].r = p->r1;
        pk.v[0].g = pk.v[1].g = p->g0;
        pk.v[2].g = pk.v[3].g = p->g1;
        pk.v[0].b = pk.v[1].b = p->b0;
        pk.v[2].b = pk.v[3].b = p->b1c;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        if (p->age < 8 && !(p->flags & 0x40)) {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = (p->a0 >> 3) * p->age;
            pk.v[3].a = (p->a1 >> 3) * p->age;
        } else {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = p->a0;
            pk.v[3].a = p->a1;
        }
        func_00101EE0(&pk, &uvs, tex);
        v[0] = v[1] = v[2] = 0.0f;
        if (func_00205440(v, m, &s[1], &depth[1]) == 0) {
            continue;
        }
        if (func_00101600(&s[1]) == 0) {
            continue;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                b = p->f18 * (f32)(u32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                x = b * func_001A6898(rad);
                z = b * func_001A6A88(rad);
                half = p->scale / 2.0f;
                y = half + half * ((f32)(u32)p->pts[k++] / 255.0f);
            }
            lf = (f32)life;
            v[0] = x * lf;
            v[1] = y * lf;
            v[2] = z * lf;
            if (func_00205440(v, m, &s[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&s[0]) == 0) {
                continue;
            }
            h = func_001018E0(p->width, depth[0]);
            if (p->flags & 0x80) {
                zf = 0.0f;
                pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFE;
            } else {
                if (depth[0] < depth[1]) {
                    zf = depth[0];
                } else {
                    zf = depth[1];
                }
                pk.v[0].xyz.z = pk.v[1].xyz.z = s[0].z;
                pk.v[2].xyz.z = pk.v[3].xyz.z = s[1].z;
            }
            pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
            dy = s[1].y - s[0].y;
            dy = dy >= 0 ? dy : -dy;
            dx = s[1].x - s[0].x;
            dx = dx >= 0 ? dx : -dx;
            if (dy < dx) {
                pk.v[0].xyz.y = s[0].y;
                pk.v[1].xyz.y = s[0].y - h;
                pk.v[2].xyz.y = s[0].y + h;
                pk.v[3].xyz.y = s[1].y;
                if ((s32)s[0].x < (s32)s[1].x) {
                    pk.v[0].xyz.x = s[0].x - h;
                } else {
                    pk.v[0].xyz.x = s[0].x + h;
                }
                pk.v[1].xyz.x = pk.v[2].xyz.x = s[0].x;
                pk.v[3].xyz.x = s[1].x;
            } else {
                pk.v[0].xyz.x = s[0].x;
                pk.v[1].xyz.x = s[0].x - h;
                pk.v[2].xyz.x = s[0].x + h;
                pk.v[3].xyz.x = s[1].x;
                if ((s32)s[0].y < (s32)s[1].y) {
                    pk.v[0].xyz.y = s[0].y - h;
                } else {
                    pk.v[0].xyz.y = s[0].y + h;
                }
                pk.v[1].xyz.y = pk.v[2].xyz.y = s[0].y;
                pk.v[3].xyz.y = s[1].y;
            }
            func_002075F0((s32)&pk, id, (u32)zf);
        }
    }
    return 1;
}

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b029:01E026A0, 310 insns, 35 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b029_01E026A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b029_01E026A0;

typedef struct {
    Hdr_b029_01E026A0 h;
    Vtx_b029_01E026A0 v[4];
    u8 tail[8];
} Pkt_b029_01E026A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b029_01E026A0;

static s32 func_01E05EA0_b137(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
    Pkt_b029_01E026A0 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 mid;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b029_01E026A0 *)(s32)&p)->count = 0x14;
    ((Hdr_b029_01E026A0 *)(s32)&p)->tag = 8;
    ((Hdr_b029_01E026A0 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b029_01E026A0 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = 128.0f / o->max * o->cur;
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (mode & 0x80)) {
        o->cur = o->max;
        if (o->flags & 1) {
            o->flags = 2;
        } else {
            o->flags = 1;
        }
    }
    if (o->flags & 8) {
        a >>= 1;
    }
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = 0xFF;
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        h = o->max >> 1;
        s = h;
        s = 7168.0f / s;
        d = o->max - o->cur;
        k = (0x80 / h) * (d >> 1);
        if (h < d) {
            p.v[0].a = p.v[1].a = k;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        w = s * d;
        mid = 32768.0f;
        p.v[0].y = p.v[1].y = mid - w;
        p.v[2].y = p.v[3].y = mid;
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = mid;
        p.v[2].y = p.v[3].y = mid + w;
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        if (o->flags & 0x20) {
            p.v[2].a = p.v[3].a = 0;
        }
        if (o->flags & 0x40) {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b137", func_01E06380_b137);
