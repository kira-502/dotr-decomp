#include "common.h"

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E00080, 237 insns, 27 copies: b010:01E00080 (move an emitter, set its level from the blend mode) built at -O1,p: every field read again, nothing CSEd */

typedef struct Obj_b002_01E00080 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 pad5[0xB];
    u8 f10[0x10];
    Vec4f pos;
    u8 pad30[8];
    f32 level;
    u8 pad3C[4];
    Vec4f vel;
    f32 base;
} Obj_b002_01E00080;

#pragma optimization_level 1

static void func_01E00080_b002(Obj_b002_01E00080 *arg0) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    Obj_b002_01E00080 *o;
    u8 d;
    u8 e;
    s32 on;
    f32 k;

    o = arg0;
    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    d = o->b0 & o->b3;
    e = o->b2 - o->b0;
    if (o->b3 == 0xFF) {
        k = o->base / o->b2;
    } else {
        k = o->base / (o->b3 + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (o->b3 == 0xFF) {
            if (e < o->b2 >> 1) {
                o->level = 2.0f * k * e;
            } else {
                o->level = 2.0f * k * o->b0;
            }
        } else {
            if (d < o->b3 >> 1) {
                o->level = 2.0f * k * (o->b3 - d);
            } else {
                o->level = 2.0f * k * d;
            }
        }
        break;
    case 4:
        o->level = o->base;
        if (o->b0 & 1) {
            o->level *= 0.5f;
        }
        break;
    case 8:
        if (o->b0 & 1) {
            on = 0;
        }
    default:
        o->level = o->base;
        break;
    }
    if (on == 0 || o->b0 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(o->f10);
    }
}
#pragma optimization_level reset

/* shape b002:01E00440 (ShFx_Smk01), 647 insns, 1 copy (-O1,p): n particle emitters (0x38 bytes each), each with up to
   8 particles (0x28 bytes, indexes into a shared table): moves each live particle (gravity, floor), sizes it by age,
   and draws it as a textured screen-space quad of radius func_001018E0(scale, depth), flipped by the particle's flags
   & 0x30; b011:01E00440's C at -O1, b002 compiled cold (config/mod_warm.txt) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b002_01E00440;

typedef struct {
    f32 s, t;
    Xyz_b002_01E00440 xyz;
} Vtx_b002_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b002_01E00440 v[4];
    u8 tail[0x20];
} Pkt_b002_01E00440;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b002_01E00440;

typedef struct {
    f32 x, y, z;
} V3_b002_01E00440;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 flags;
    V3_b002_01E00440 pos;
    V3_b002_01E00440 vel;
    V3_b002_01E00440 acc;
} Part_b002_01E00440;

typedef struct {
    u8 drawn;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Part_b002_01E00440 *parts;
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
} Emit_b002_01E00440;

#pragma optimization_level 1

static s32 func_01E00440_b002(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern f32 func_001018E0(f32, f32);
    f32 mat[16];
    Vec4f pos;
    Tex_b002_01E00440 td;
    Pkt_b002_01E00440 pkt __attribute__((aligned(8)));
    Xyz_b002_01E00440 xyz;
    f32 dep;
    Emit_b002_01E00440 *e;
    s32 i;
    Part_b002_01E00440 *parts;
    Part_b002_01E00440 *p;
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
            ((Pkt_b002_01E00440 *)(s32)&pkt)->count = 0x24;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->tag = 9;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->pad = 0;
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Node_b002_01E00E60;

typedef struct {
    u8 pad00[8];
    Node_b002_01E00E60 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
} Sys_b002_01E00E60;

typedef struct {
    Sys_b002_01E00E60 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    f32 cx, cy, cz;
} Burst_b002_01E00E60;

#pragma optimization_level 1

static void func_01E00E60_b002(Burst_b002_01E00E60 *arg) {
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Burst_b002_01E00E60 *pr;
    Sys_b002_01E00E60 *s;
    Node_b002_01E00E60 *node;
    s32 i;
    s32 idx;
    f32 angle;
    f32 step;
    f32 c;
    f32 sn;

    pr = arg;
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
            c = func_001A6A88(3.1415927f * angle / 180.0f);
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
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E011B0, 312 insns, 6 copies: effect spawner (per-frame joint lists -> b002:01E00E60 bursts, then a
   timed particle cloud). Calls b002_01E00E60 of the same module as a plain extern. Its Burst type here uses a Vec
   for the centre where ovl-matched/b002_01E00E60.c has three floats: same layout, unify the types when integrating. */

typedef struct {
    f32 x, y, z, w;
} Vec_b002_01E011B0;

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Part_b002_01E011B0;

typedef struct {
    u8 pad00[4];
    u8 b4;
    u8 pad05[3];
    Part_b002_01E011B0 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
    u8 b1E;
    u8 b1F;
    u8 b20;
    u8 pad21;
    u8 r, g, b, a;
    u8 pad26[2];
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
} Node_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    Vec_b002_01E011B0 c;
} Burst_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *nodes;
    Part_b002_01E011B0 *parts;
    s16 *lists[8];
    u8 joint[8];
    u8 kind;
    u8 pkind;
    u8 b32;
    u8 joint2;
    s16 start;
    s16 end;
    f32 f38;
    f32 f3C;
    f32 f40;
} Spawner_b002_01E011B0;

extern void b002_01E00E60(Burst_b002_01E011B0 *);

#pragma optimization_level 1

static s32 func_01E011B0_b002(Spawner_b002_01E011B0 *obj, u16 t) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101B40(void *, s32, s32);
    Spawner_b002_01E011B0 *o;
    Node_b002_01E011B0 *node;
    s16 *p;
    s32 k;
    Part_b002_01E011B0 *part;
    s32 idx;
    Vec_b002_01E011B0 pos;
    Burst_b002_01E011B0 burst;

    o = obj;
    for (k = 0; k < 8; k++) {
        if (o->lists[k] == 0) {
            continue;
        }
        for (p = o->lists[k]; *p > 0; p++) {
            if (*p != t) {
                continue;
            }
            if (func_001F5620(func_001F53A0(), o->joint[k], &pos) == 0) {
                break;
            }
            idx = func_00101C30(o->nodes, 0x38, o->kind);
            if (idx < 0) {
                return 0;
            }
            node = &o->nodes[idx];
            func_00101AD0(node, 1, 0, 0xFF);
            node->b4 = 4;
            node->pool = o->parts;
            node->kind = o->pkind;
            node->count = 4;
            node->b1E = 1;
            node->b1F = o->b32;
            node->b20 = 4;
            node->b = node->g = node->r = 0x90;
            node->a = 0x30;
            node->f28 = o->f38;
            node->f2C = o->f40;
            node->f30 = -0.015f;
            node->f34 = pos.y;
            burst.sys = node;
            burst.life = 0x20;
            burst.mask = 3;
            burst.speed = 0.25f;
            burst.rise = 0.3f;
            burst.radius = 0.15f;
            burst.c = pos;
            b002_01E00E60(&burst);
        }
    }
    if (o->start != 0 && o->start <= t && o->end >= t) {
        if (func_001F5620(func_001F53A0(), o->joint2, &pos) == 0) {
            return 0;
        }
        idx = func_00101C30(o->nodes, 0x38, o->kind);
        if (idx < 0) {
            return 0;
        }
        node = &o->nodes[idx];
        func_00101AD0(node, 1, 0, 0xFF);
        node->b4 = 4;
        node->pool = o->parts;
        node->kind = o->pkind;
        node->count = 2;
        node->b1E = 1;
        node->b1F = o->b32;
        node->b20 = 4;
        node->b = node->g = node->r = 0x90;
        node->a = 0x30;
        node->f28 = o->f3C;
        node->f2C = o->f40;
        node->f30 = -0.007f;
        node->f34 = 0.0f;
        for (k = 0; k < node->count; k++) {
            idx = func_00101C30(o->parts, 0x28, o->pkind);
            if (idx >= 0) {
                node->ids[k] = idx;
                part = &o->parts[idx];
                func_00101B40(part, 0x20, 0);
                part->frame = ((func_0019A5C8() >> 4) & 3) << 4;
                part->x = pos.x + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->z = pos.z + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->y = pos.y + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->vx = part->vy = part->vz = part->ax = part->ay = part->az = 0.0f;
            } else {
                node->ids[k] = -1;
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E01690_b002);

/* shape b241:01E00440 (ShFx_Flear01), 839 insns, 26 copies (-O1,p): draws each emitter of a list as a glowing ring: a
   fan of triangles and a quad pair per segment */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b241_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b241_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b241_01E00440 xyz;
} Vtx1_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    Vtx1_b241_01E00440 v[3];
    u8 tail[8];
} Pkt1_b241_01E00440;

typedef struct {
    u64 st;
    Xyz_b241_01E00440 xyz;
} Vtx2_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b241_01E00440 v[4];
    u8 tail[0x20];
} Pkt2_b241_01E00440;

typedef struct {
    f32 x, y, z, w;
} V4_b241_01E00440;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b241_01E00440;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    V4_b241_01E00440 pos;
    V4_b241_01E00440 vel;
    V4_b241_01E00440 org;
} Obj_b241_01E00440;

#pragma optimization_level 1

static s32 func_01E02AD0_b002(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E06C90_b002;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002086D0(void *, u64);
    extern void func_00101D20(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b241_01E00440 *o;
    s32 k;
    s32 i;
    s32 segs;
    s32 h;
    f32 m0[16];
    f32 m1[16];
    V4_b241_01E00440 org;
    Tex_b241_01E00440 t;
    Xyz_b241_01E00440 scr;
    Pkt1_b241_01E00440 p1 __attribute__((aligned(8)));
    Pkt2_b241_01E00440 p2 __attribute__((aligned(8)));
    f32 depth;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    u8 d;

    o = obj;
    t = D_01E06C90_b002;
    h = func_00202BF0(t.id, t.kind);
    for (k = 0; k < n; k++) {
        if (k != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->radius += o->grow;
        org = o->org;
        segs = o->segs > 9 ? 9 : o->segs;
        step = 90.0f / segs;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m0, NULL, NULL, &o->pos);
        func_0020BC00(m1, m0);
        if (func_00205440(&org, m1, &scr, &depth) == 0 || func_00101600(&scr) == 0) {
            continue;
        }
        r = func_001018E0(o->radius, depth);
        w = func_001018E0(o->width, depth);
        if (o->flags & 0x80) {
            scr.z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            zf = depth;
        }
        ((Hdr_b241_01E00440 *)(s32)&p1)->count = 0x13;
        ((Hdr_b241_01E00440 *)(s32)&p1)->tag = 6;
        ((Hdr_b241_01E00440 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b241_01E00440 *)(s32)&p1)->pad = 0;
        p1.v[0].r = o->ir;
        p1.v[1].r = p1.v[2].r = o->r;
        p1.v[0].g = o->ig;
        p1.v[1].g = p1.v[2].g = o->g;
        p1.v[0].b = o->ib;
        p1.v[1].b = p1.v[2].b = o->b;
        p1.v[0].q = p1.v[1].q = p1.v[2].q = 1.0f;
        if (o->flags & 8) {
            func_002086D0(&p1, 0x42);
        } else {
            func_002086D0(&p1, 0x48);
        }
        ((Hdr_b241_01E00440 *)(s32)&p2)->count = 0x24;
        ((Hdr_b241_01E00440 *)(s32)&p2)->tag = 9;
        ((Hdr_b241_01E00440 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b241_01E00440 *)(s32)&p2)->pad = 0;
        p2.r = o->r;
        p2.g = o->g;
        p2.b = o->b;
        p2.q = 1.0f;
        func_00101D20(&p2, &t, h);
        p1.v[0].a = o->alpha;
        p2.a = o->alpha >> 1;
        p1.v[1].a = p1.v[2].a = 0;
        if (!(o->flags & 0x40)) {
            if (o->cur < 8) {
                p1.v[0].a = (o->alpha >> 3) * o->cur;
                p2.a = (o->alpha >> 4) * o->cur;
            } else {
                d = o->max - o->cur;
                if (d < 8) {
                    p1.v[0].a = (o->alpha >> 3) * d;
                    p2.a = (o->alpha >> 4) * d;
                }
            }
        }
        if (o->cur & 1) {
            if (o->flags & 2) {
                if (p1.v[0].a > 0x10) {
                    p1.v[0].a -= 0x10;
                }
            }
            if (o->flags & 4) {
                if (p1.v[0].a > 0) {
                    p1.v[0].a >>= 1;
                }
            }
        }
        x = r * func_001A6898(0.0f);
        y = r * func_001A6A88(0.0f);
        p2.v[0].xyz.z = p2.v[1].xyz.z = p2.v[2].xyz.z = p2.v[3].xyz.z = p1.v[0].xyz.z = p1.v[1].xyz.z =
            p1.v[2].xyz.z = scr.z;
        p2.v[0].xyz.f = p2.v[1].xyz.f = p2.v[2].xyz.f = p2.v[3].xyz.f = p1.v[0].xyz.f = p1.v[1].xyz.f =
            p1.v[2].xyz.f = 1;
        for (i = 1; i < segs * 4 + 1; i++) {
            px = x;
            py = y;
            x = r * func_001A6898(3.1415927f * (step * i) / 180.0f);
            y = r * func_001A6A88(3.1415927f * (step * i) / 180.0f);
            p1.v[0].xyz.x = scr.x;
            p1.v[0].xyz.y = scr.y;
            p1.v[1].xyz.x = scr.x + px;
            p1.v[1].xyz.y = scr.y + py;
            p1.v[2].xyz.x = scr.x + x;
            p1.v[2].xyz.y = scr.y + y;
            func_002075F0(&p1, tex, (u32)zf);
            if (o->flags & 1) {
                continue;
            }
            p2.v[0].xyz.x = p2.v[2].xyz.x = scr.x + px;
            p2.v[1].xyz.x = p2.v[3].xyz.x = scr.x + x;
            p2.v[0].xyz.y = scr.y + py - w;
            p2.v[2].xyz.y = w + (scr.y + py);
            p2.v[1].xyz.y = scr.y + y - w;
            p2.v[3].xyz.y = w + (scr.y + y);
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            p2.v[0].xyz.x = w + (scr.x + px);
            p2.v[2].xyz.x = scr.x + px - w;
            p2.v[1].xyz.x = w + (scr.x + x);
            p2.v[3].xyz.x = scr.x + x - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E037F0_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E04520_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E053E0_b002);

INCLUDE_ASM("asm/nonmatchings/mod/b002", func_01E05FE0_b002);
