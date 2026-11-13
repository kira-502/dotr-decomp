#include "common.h"

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00080, 226 insns, 89 copies: move an emitter (pos += vel) and set its level from the blend mode */

typedef struct Obj_b010_01E00080 {
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
} Obj_b010_01E00080;

#pragma optimization_level 2

static void func_01E00080_b508(Obj_b010_01E00080 *o) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    u8 d;
    u8 e;
    u8 a;
    s32 on;
    u8 n;
    f32 k;
    u8 m;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    a = o->b0;
    m = o->b3;
    d = a & m;
    n = o->b2;
    e = n - a;
    if (m == 0xFF) {
        k = o->base / n;
    } else {
        k = o->base / (m + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (m == 0xFF) {
            if (e < n >> 1) {
                k = 2.0f * k;
                o->level = k * e;
            } else {
                k = 2.0f * k;
                o->level = k * a;
            }
        } else {
            if (d < m >> 1) {
                k = 2.0f * k;
                o->level = k * (m - d);
            } else {
                k = 2.0f * k;
                o->level = k * d;
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
        if (a & 1) {
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

/* shape b010:01E00410 (ShFx_Smk01), 620 insns, 35 copies (-O2,p): n particle emitters (0x38 bytes each), each with up
   to 8 particles (0x28 bytes, indexes into a shared table): moves each live particle (gravity, floor), sizes it by
   age, and draws it as a textured screen-space quad of radius func_001018E0(scale, depth), flipped by the particle's
   flags & 0x30; the source of shape b011:01E00440, built here at -O2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b010_01E00410;

typedef struct {
    f32 s, t;
    Xyz_b010_01E00410 xyz;
} Vtx_b010_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b010_01E00410 v[4];
    u8 tail[0x20];
} Pkt_b010_01E00410;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b010_01E00410;

typedef struct {
    f32 x, y, z;
} V3_b010_01E00410;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 flags;
    V3_b010_01E00410 pos;
    V3_b010_01E00410 vel;
    V3_b010_01E00410 acc;
} Part_b010_01E00410;

typedef struct {
    u8 drawn;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Part_b010_01E00410 *parts;
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
} Emit_b010_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b508(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern f32 func_001018E0(f32, f32);
    f32 mat[16];
    Vec4f pos;
    Tex_b010_01E00410 td;
    Pkt_b010_01E00410 pkt __attribute__((aligned(8)));
    Xyz_b010_01E00410 xyz;
    f32 dep;
    Emit_b010_01E00410 *e;
    s32 i;
    Part_b010_01E00410 *parts;
    Part_b010_01E00410 *p;
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
            ((Pkt_b010_01E00410 *)(s32)&pkt)->count = 0x24;
            ((Pkt_b010_01E00410 *)(s32)&pkt)->tag = 9;
            ((Pkt_b010_01E00410 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
            ((Pkt_b010_01E00410 *)(s32)&pkt)->pad = 0;
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00DC0, 200 insns, 34 copies: spawns the emitter's particle ring: one particle per slot, evenly spaced from a
   random start angle, placed on the radius and moving outwards; the slot keeps the particle index (-1 if none) */

typedef struct {
    u8 pad0[3];
    s8 flag;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax;
    s32 ay;
    f32 az;
} Part_b010_01E00DC0;

typedef struct {
    u8 pad0[8];
    u8 *parts;
    s16 idx[8];
    u8 type;
    u8 count;
} Sys_b010_01E00DC0;

typedef struct {
    Sys_b010_01E00DC0 *sys;
    u8 kind;
    u8 mask;
    u8 pad6[2];
    f32 speed;
    f32 vy;
    f32 radius;
    f32 cx, cy, cz;
} Emit_b010_01E00DC0;

#pragma optimization_level 2

static void func_01E00DC0_b508(Emit_b010_01E00DC0 *e) {
    extern void func_00101B40(void *, u8, u8);
    Sys_b010_01E00DC0 *sys;
    f32 ang;
    f32 step;
    Part_b010_01E00DC0 *p;
    s32 i;
    s32 k;
    f32 r;
    f32 s;
    f32 c;

    sys = e->sys;
    ang = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / sys->count;
    for (i = 0; i < sys->count; i++) {
        k = func_00101C30(sys->parts, 0x28, sys->type);
        if (k >= 0) {
            sys->idx[i] = k;
            p = (Part_b010_01E00DC0 *)(sys->parts + k * 0x28);
            func_00101B40(p, e->kind, e->mask & (func_0019A5C8() >> 4));
            p->flag = ((func_0019A5C8() >> 4) & 3) * 16;
            ang += step;
            if (ang > 360.0f) {
                ang -= 360.0f;
            }
            r = 3.1415927f * ang / 180.0f;
            s = func_001A6A88(r);
            c = func_001A6898(r);
            p->x = e->cx + e->radius * c;
            p->z = e->cz + e->radius * s;
            p->y = e->cy;
            p->vx = e->speed * c;
            p->vz = e->speed * s;
            p->vy = e->vy;
            p->ax = -(p->vx / e->kind);
            p->az = -(p->vz / e->kind);
            p->ay = 0;
        } else {
            sys->idx[i] = -1;
        }
    }
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E010E0, 304 insns, 34 copies: on a given frame, starts the effect emitters listed for it:
   each of the 8 frame tables starts a 4-particle burst at its bone, and the frame window lo..hi starts a
   2-particle emitter with randomly spread particles. */

typedef struct {
    u8 pad0[4];
    u8 type;
    u8 pad5[3];
    void *pool;
    s16 idx[8];
    u8 pool_kind;
    u8 count;
    u8 one;
    u8 kind;
    u8 four;
    u8 pad21;
    u8 r, g, b, a;
    u8 pad26[2];
    f32 x;
    f32 y;
    f32 speed;
    f32 depth;
} Emit_b010_01E010E0;

typedef struct {
    u8 pad0[3];
    u8 frame;
    f32 x, y, z;
    s32 w[6];
} Part_b010_01E010E0;

typedef struct {
    Emit_b010_01E010E0 *emits;
    Part_b010_01E010E0 *parts;
    s16 *frames[8];
    u8 bone[8];
    u8 emit_kind;
    u8 part_kind;
    u8 kind;
    u8 bone2;
    s16 lo;
    s16 hi;
    f32 x0;
    f32 x1;
    f32 y;
} Obj_b010_01E010E0;

typedef struct {
    Emit_b010_01E010E0 *e;
    u8 n;
    u8 m;
    f32 a, b, c;
    Vec4f pos;
} Burst_b010_01E010E0;

extern void b508_01E00DC0(Burst_b010_01E010E0 *);

#pragma optimization_level 2

static s32 func_01E010E0_b508(Obj_b010_01E010E0 *obj, u16 frame) {
    extern s32 func_001F53A0();
    extern s32 func_00101C30();
    extern s32 func_001F5620();
    extern void func_00101AD0();
    Vec4f pos;
    Burst_b010_01E010E0 burst;
    Emit_b010_01E010E0 *e;
    Part_b010_01E010E0 *pt;
    s32 i;
    s16 *list;
    s32 k;
    s32 j;

    for (i = 0; i < 8; i++) {
        list = obj->frames[i];
        if (list != NULL) {
            for (; *list > 0; list++) {
                if (*list == frame) {
                    if (func_001F5620(func_001F53A0(), obj->bone[i], &pos) == 0) {
                        break;
                    }
                    k = func_00101C30(obj->emits, 0x38, obj->emit_kind);
                    if (k < 0) {
                        return 0;
                    }
                    e = &obj->emits[k];
                    func_00101AD0(e, 1, 0, 0xFF);
                    e->type = 4;
                    e->pool = obj->parts;
                    e->pool_kind = obj->part_kind;
                    e->count = 4;
                    e->one = 1;
                    e->kind = obj->kind;
                    e->four = 4;
                    e->r = 0x90;
                    e->g = 0x90;
                    e->b = 0x90;
                    e->a = 0x30;
                    e->x = obj->x0;
                    e->y = obj->y;
                    e->speed = -0.015f;
                    e->depth = pos.y;
                    burst.e = e;
                    burst.n = 0x20;
                    burst.m = 3;
                    burst.a = 0.25f;
                    burst.b = 0.3f;
                    burst.c = 0.15f;
                    burst.pos = pos;
                    b508_01E00DC0(&burst);
                }
            }
        }
    }
    if (obj->lo != 0) {
        if ((s16)obj->lo <= frame && obj->hi >= frame) {
            if (func_001F5620(func_001F53A0(), obj->bone2, &pos) == 0) {
                return 0;
            }
            k = func_00101C30(obj->emits, 0x38, obj->emit_kind);
            if (k < 0) {
                return 0;
            }
            e = &obj->emits[k];
            func_00101AD0(e, 1, 0, 0xFF);
            e->type = 4;
            e->pool = obj->parts;
            e->pool_kind = obj->part_kind;
            e->count = 2;
            e->one = 1;
            e->kind = obj->kind;
            e->four = 4;
            e->r = 0x90;
            e->g = 0x90;
            e->b = 0x90;
            e->a = 0x30;
            e->x = obj->x1;
            e->y = obj->y;
            e->speed = -0.007f;
            e->depth = 0.0f;
            for (j = 0; j < e->count; j++) {
                k = func_00101C30(obj->parts, 0x28, obj->part_kind);
                if (k >= 0) {
                    e->idx[j] = k;
                    pt = &obj->parts[k];
                    func_00101B40(pt, 0x20, 0);
                    pt->frame = ((func_0019A5C8() >> 4) & 3) * 0x10;
                    pt->x = pos.x + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->z = pos.z + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->y = pos.y + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                    pt->w[5] = 0;
                    pt->w[4] = 0;
                    pt->w[3] = 0;
                    pt->w[2] = 0;
                    pt->w[1] = 0;
                    pt->w[0] = 0;
                } else {
                    e->idx[j] = -1;
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b010:01E015A0 (ShFx_Afx01), 663 insns, 5 copies (-O2,p): draws n glow entities (0x30 bytes each): projects
   each one on its first frame, then a fan of up to 8 triangles (flag bits of mask) from its screen centre to the
   corners and edge midpoints of a square of half-size (size + (life & 3) * 2) << 4; the -O2 build of b132:01E04B00,
   the size kept as an int and shifted in each case */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b010_01E015A0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b010_01E015A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b010_01E015A0 uv;
    Xyz_b010_01E015A0 xyz;
} Vtx_b010_01E015A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b010_01E015A0 v[4];
    u8 tail[8];
} Pkt_b010_01E015A0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3[5];
    u8 size;
    u8 blend;
    u8 mask;
    u8 padB;
    Vec4f pos;
    u8 b2, g2, r2, a2;
    u8 b, g, r, a;
    u8 pad24[4];
    Xyz_b010_01E015A0 xy;
} Afx_b010_01E015A0;

#pragma optimization_level 2

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E015A0_b508(Afx_b010_01E015A0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b010_01E015A0 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Pkt_b010_01E015A0 pk;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 u;
    s32 v;
    s32 j;
    s32 sz;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->span - 1) {
            func_0020EB40(mat);
            if (func_00205440(&e->pos, mat, &e->xy, &depth) == 0) {
                e->life = 0;
                continue;
            }
            if (func_00101770(&e->xy) == 0) {
                e->life = 0;
                continue;
            }
        }
        u = (s32)(e->xy.x - 27648.0f);
        v = (s32)(e->xy.y - 29184.0f);
        ((Pkt_b010_01E015A0 *)(s32)&pk)->count = 0x33;
        ((Pkt_b010_01E015A0 *)(s32)&pk)->tag = 9;
        ((Pkt_b010_01E015A0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x21421421;
        ((Pkt_b010_01E015A0 *)(s32)&pk)->pad = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = e->r;
        pk.v[2].r = e->r2;
        pk.v[0].g = pk.v[1].g = e->g;
        pk.v[2].g = e->g2;
        pk.v[0].b = pk.v[1].b = e->b;
        pk.v[2].b = e->b2;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = 0;
        td[5] = e->blend;
        func_00101C80(td, bl);
        func_002086D0(&pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        ((Pkt_b010_01E015A0 *)(s32)&pk)->count |= 0x800;
        ((Uv_b010_01E015A0 *)(s32)&pk.v[2].uv)->u = u;
        ((Uv_b010_01E015A0 *)(s32)&pk.v[2].uv)->v = v;
        pk.v[2].xyz.x = e->xy.x;
        pk.v[2].xyz.y = e->xy.y;
        if (e->life < 8) {
            pk.v[0].a = pk.v[1].a = (e->a >> 3) * e->life;
            pk.v[2].a = (e->a2 >> 3) * e->life;
        } else {
            pk.v[0].a = pk.v[1].a = e->a;
            pk.v[2].a = e->a2;
        }
        sz = e->size + (e->life & 3) * 2;
        for (j = 0; j < 8; j++) {
            if (!(e->mask & (1 << j))) {
                continue;
            }
            switch (j) {
            case 0:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 1:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 2:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 3:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = (u32)(29184.0f - (sz << 4));
                pk.v[1].xyz.y = e->xy.y;
                break;
            case 4:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 5:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 6:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 7:
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b010_01E015A0 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = (u32)(36352.0f + (sz << 4));
                pk.v[1].xyz.y = e->xy.y;
                break;
            }
            func_002075F0(&pk, ot, 0);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b035:01E00410 (ShFx_Flear01), 736 insns, 89 copies (-O2,p): draws each emitter of a list as a glowing ring: a
   fan of segs*4 triangles from the centre colour out to the edge colour, and unless flag 1 a textured band along the
   edge (two quads per slice); the radius grows each frame */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b035_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b035_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b035_01E00410 xyz;
} Vtx1_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    Vtx1_b035_01E00410 v[3];
    u8 tail[8];
} Pkt1_b035_01E00410;

typedef struct {
    u64 st;
    Xyz_b035_01E00410 xyz;
} Vtx2_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b035_01E00410 v[4];
    u8 tail[0x20];
} Pkt2_b035_01E00410;

typedef struct {
    f32 x, y, z, w;
} V4_b035_01E00410;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b035_01E00410;

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
    V4_b035_01E00410 pos;
    V4_b035_01E00410 vel;
    V4_b035_01E00410 org;
} Obj_b035_01E00410;

#pragma optimization_level 2

static s32 func_01E02000_b508(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E06700_b508;
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
    Obj_b035_01E00410 *o; /* a copy of obj: needed for the match (register order) */
    s32 k;
    s32 h __attribute__((aligned(16))); /* aligned: its spill slot, needed for the match */
    f32 m0[16];
    f32 m1[16];
    V4_b035_01E00410 org;
    Tex_b035_01E00410 t;
    Xyz_b035_01E00410 scr;
    Pkt1_b035_01E00410 p1 __attribute__((aligned(8)));
    Pkt2_b035_01E00410 p2 __attribute__((aligned(8)));
    f32 depth;
    s32 i;
    s32 segs;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    f32 v;
    f32 a;
    u8 d;

    o = obj;
    t = D_01E06700_b508;
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
        segs = o->segs;
        segs = segs > 9 ? 9 : segs; /* this form for the match */
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
        ((Hdr_b035_01E00410 *)(s32)&p1)->count = 0x13;
        ((Hdr_b035_01E00410 *)(s32)&p1)->tag = 6;
        ((Hdr_b035_01E00410 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b035_01E00410 *)(s32)&p1)->pad = 0;
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
        ((Hdr_b035_01E00410 *)(s32)&p2)->count = 0x24;
        ((Hdr_b035_01E00410 *)(s32)&p2)->tag = 9;
        ((Hdr_b035_01E00410 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b035_01E00410 *)(s32)&p2)->pad = 0;
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
            a = 3.1415927f * (step * i) / 180.0f;
            x = r * func_001A6898(a);
            y = r * func_001A6A88(a);
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
            v = scr.y + py;
            p2.v[0].xyz.y = v - w;
            p2.v[2].xyz.y = w + v;
            v = scr.y + y;
            p2.v[1].xyz.y = v - w;
            p2.v[3].xyz.y = w + v;
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            px = scr.x + px; /* px reused as the temporary: needed for the match */
            p2.v[0].xyz.x = w + px;
            p2.v[2].xyz.x = px - w;
            px = scr.x + x;
            p2.v[1].xyz.x = w + px;
            p2.v[3].xyz.x = px - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b532:01E00080 (ShFx_Ndl), 737 insns, 73 copies (-O2,p): a needle beam: per emitter a strip of quads from a
   point out along a table-driven path (or a circle of growing radius), each quad turned to face its direction; the
   source of shape b011:01E04380, built here at -O2 */

#define ABS_b532_01E00080(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b532_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b532_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b532_01E00080 p;
} Vtx_b532_01E00080;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b532_01E00080 v[4];
    u8 tail[0x20];
} Pkt_b532_01E00080;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b532_01E00080;

typedef struct {
    u8 step;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 segments;
    u8 index;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 delay;
    u8 target;
    u8 pad0F;
    u8 *table;
    f32 size;
    f32 radius;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec_b532_01E00080 pos;
    Vec_b532_01E00080 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b532_01E00080;

extern Tex_b532_01E00080 D_01E06720_b508;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E02B80_b508(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101940(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Ray_b532_01E00080 *o;
    s32 i;
    u8 idx;
    s32 j;
    s32 span;
    s32 texture;
    f32 w;
    f32 zd;
    f32 y;
    f32 angle;
    f32 x;
    f32 r;
    f32 z;
    f32 step;
    f32 m2[16];
    f32 m1[16];
    Xyz_b532_01E00080 xy[2];
    Vec_b532_01E00080 pt;
    Vec_b532_01E00080 d;
    Vec_b532_01E00080 tmp;
    Tex_b532_01E00080 tex0;
    Tex_b532_01E00080 tex;
    Pkt_b532_01E00080 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E06720_b508;
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 4) {
            texture = func_00202BF0(5, o->texkind);
            tex.page = o->texpage;
            func_001020B0(&tex, o->texmode, 0);
        } else {
            texture = func_00202BF0(tex0.id, tex0.kind);
            tex = tex0;
        }
        if (!(o->flags & 2)) {
            tex.u -= 0x10;
            tex.v -= 0x10;
        }
        idx = o->index;
        step = 17.0f;
        angle = 0.0f;
        if (o->step < o->delay) {
            span = o->total - o->delay;
        } else {
            span = o->total - o->step;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
        func_00101BA0(o, &o->pos);
        if (o->flags & 8) {
            func_001F5620(func_001F53A0(), o->target, &tmp);
            d.x = tmp.x - o->pos.x;
            d.y = tmp.y - o->pos.y;
            d.z = tmp.z - o->pos.z;
            func_00101940(&d, o->rot);
        }
        func_0020EB40(m1);
        func_0020C940(m2, 0, o->rot, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b532_01E00080 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = o->r0;
        pkt.v[2].r = pkt.v[3].r = o->r1;
        pkt.v[0].g = pkt.v[1].g = o->g0;
        pkt.v[2].g = pkt.v[3].g = o->g1;
        pkt.v[0].b = pkt.v[1].b = o->b0;
        pkt.v[2].b = pkt.v[3].b = o->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (o->step <= 7 && !(o->flags & 0x40)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = (o->a0 >> 3) * o->step;
            pkt.v[3].a = (o->a1 >> 3) * o->step;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = o->a0;
            pkt.v[3].a = o->a1;
        }
        func_00101EE0(&pkt, &tex, texture);
        pt.x = pt.y = pt.z = 0.0f;
        if (func_00205440(&pt, m1, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        for (j = 0; j < o->segments; j++) {
            if (o->flags & 1) {
                x = o->size * (o->table[idx] - o->table[idx + 1]) / 255.0f;
                y = o->size * (o->table[idx + 2] - o->table[idx + 3]) / 255.0f;
                z = o->size * (o->table[idx + 4] - o->table[idx + 5]) / 255.0f;
                idx += 6;
            } else {
                angle += step;
                if (!(angle <= 360.0f)) {
                    angle -= 360.0f;
                }
                r = o->radius * o->table[idx] / 255.0f;
                idx++;
                x = r * func_001A6898(3.1415927f * angle / 180.0f);
                z = r * func_001A6A88(3.1415927f * angle / 180.0f);
                y = o->size / 2.0f;
                y += y * (o->table[idx] / 255.0f);
                idx++;
            }
            pt.x = x * span;
            pt.y = y * span;
            pt.z = z * span;
            if (func_00205440(&pt, m1, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0) {
                continue;
            }
            w = func_001018E0(o->width, dep[0]);
            if (o->flags & 0x80) {
                pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                zd = 0.0f;
            } else {
                if (dep[0] < dep[1]) {
                    zd = dep[0];
                } else {
                    zd = dep[1];
                }
                pkt.v[0].p.z = pkt.v[1].p.z = xy[0].z;
                pkt.v[2].p.z = pkt.v[3].p.z = xy[1].z;
            }
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 0;
            if (ABS_b532_01E00080(xy[1].x - xy[0].x) > ABS_b532_01E00080(xy[1].y - xy[0].y)) {
                pkt.v[0].p.y = xy[0].y;
                pkt.v[1].p.y = (u32)(xy[0].y - w);
                pkt.v[2].p.y = (u32)(xy[0].y + w);
                pkt.v[3].p.y = xy[1].y;
                if (xy[0].x < xy[1].x) {
                    pkt.v[0].p.x = (u32)(xy[0].x - w);
                } else {
                    pkt.v[0].p.x = (u32)(xy[0].x + w);
                }
                pkt.v[1].p.x = pkt.v[2].p.x = xy[0].x;
                pkt.v[3].p.x = xy[1].x;
            } else {
                pkt.v[0].p.x = xy[0].x;
                pkt.v[1].p.x = (u32)(xy[0].x - w);
                pkt.v[2].p.x = (u32)(xy[0].x + w);
                pkt.v[3].p.x = xy[1].x;
                if (xy[0].y < xy[1].y) {
                    pkt.v[0].p.y = (u32)(xy[0].y - w);
                } else {
                    pkt.v[0].p.y = (u32)(xy[0].y + w);
                }
                pkt.v[1].p.y = pkt.v[2].p.y = xy[0].y;
                pkt.v[3].p.y = xy[1].y;
            }
            func_002075F0(&pkt, target, (u32)zd);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b561:01E02A90 (ShFx_RingTX), 505 insns, 16 copies (-O2,p): n ring emitters (0x5C bytes each): an inner and an
   outer circle of up to 36 points (radii growing each frame) joined into textured quads; texture rect from
   func_001020B0, mode 1 = no clamp and s scaled by e->scale, mode 2 = a 1-texel column in the middle; far z with
   flags & 0x80; the source of shape b603:01E039B0, built here at -O2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b561_01E02A90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b561_01E02A90 xyz;
} Vtx_b561_01E02A90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b561_01E02A90 v[4];
    u8 tail[0x20];
} Pkt_b561_01E02A90;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b561_01E02A90;

typedef struct {
    u8 b, g, r, a;
} Col_b561_01E02A90;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 texid;
    u8 sub;
    u8 bA;
    u8 bB;
    u8 mode;
    u8 padD[3];
    f32 radius[2];
    f32 dradius[2];
    f32 scale;
    Col_b561_01E02A90 c0;
    Col_b561_01E02A90 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b561_01E02A90;

#pragma optimization_level 2

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E03710_b508(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b561_01E02A90 td;
    Pkt_b561_01E02A90 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b561_01E02A90 *e;
    s32 i;
    s32 tex;
    s32 nseg;
    s32 k;
    s32 r;
    f32 step;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texid);
        e->radius[0] += e->dradius[0];
        e->radius[1] += e->dradius[1];
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        if (e->seg > 36) {
            nseg = 36;
        } else {
            nseg = e->seg;
        }
        step = 360.0f / nseg;
        for (r = 0; r < 2; r++) {
            for (k = 0; k < nseg; k++) {
                ring[r][k].x = e->radius[r] * func_001A6898(3.1415927f * (step * k) / 180.0f);
                ring[r][k].z = e->radius[r] * func_001A6A88(3.1415927f * (step * k) / 180.0f);
                ring[r][k].y = 0.0f;
            }
        }
        ring[0][nseg] = ring[0][0];
        ring[1][nseg] = ring[1][0];
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        td.b5 = e->sub;
        func_001020B0(&td, e->bB, e->bA);
        func_00102210(e->bA, &sw, &sh);
        switch (e->mode & 3) {
        case 1:
            func_00208CB0(&pkt, 0);
            sw *= e->scale;
            break;
        case 2:
            {
                s32 h = (td.w - td.u) >> 1; /* through a local: needed for the match */
                td.u += h;
            }
            td.w = td.u + 1;
        default:
            func_00208CB0(&pkt, 0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            break;
        }
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        for (k = 0; k < nseg; k++) {
            if (func_00205440(&ring[0][k], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                func_00205440(&ring[0][k + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                func_00205440(&ring[1][k], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                func_00205440(&ring[1][k + 1], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                pkt.v[0].q = 1.0f / depth[0];
                pkt.v[1].q = 1.0f / depth[1];
                pkt.v[2].q = 1.0f / depth[2];
                pkt.v[3].q = 1.0f / depth[3];
                pkt.v[0].s = td.u / sw / depth[0];
                pkt.v[0].t = td.v / sh / depth[0];
                pkt.v[1].s = td.w / sw / depth[1];
                pkt.v[1].t = td.v / sh / depth[1];
                pkt.v[2].s = td.u / sw / depth[2];
                pkt.v[2].t = td.h / sh / depth[2];
                pkt.v[3].s = td.w / sw / depth[3];
                pkt.v[3].t = td.h / sh / depth[3];
                func_00101C80(&td, bl);
                func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                func_00208700(&pkt, (void *)tex, 1);
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E05740, 337 insns, 56 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b010_01E05740;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b010_01E05740;

typedef struct {
    Hdr_b010_01E05740 h;
    Vtx_b010_01E05740 v[4];
    u8 tail[8];
} Pkt_b010_01E05740;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b010_01E05740;

#pragma optimization_level 2

static s32 func_01E03F00_b508(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
    Pkt_b010_01E05740 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b010_01E05740 *)(s32)&p)->count = 0x14;
    ((Hdr_b010_01E05740 *)(s32)&p)->tag = 8;
    ((Hdr_b010_01E05740 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b010_01E05740 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = func_001A23B0(128.0f / o->max * o->cur);
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
        p.v[0].y = p.v[1].y = func_001A23B0(32768.0f - w);
        p.v[2].y = p.v[3].y = func_001A23B0(32768.0f);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(32768.0f);
        p.v[2].y = p.v[3].y = func_001A23B0(32768.0f + w);
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
#pragma optimization_level reset

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b024:01E02120, 875 insns, 51 copies: update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b024_01E02120 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b024_01E02120;

typedef struct Rib_b024_01E02120 {
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
} Rib_b024_01E02120;

typedef struct Xyz_b024_01E02120 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b024_01E02120;

typedef struct Pk_b024_01E02120 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b024_01E02120 v[4];
    u64 pad60[3];
} Pk_b024_01E02120;

static inline void b024_01E02120_tag(Pk_b024_01E02120 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2
typedef struct W_tbl_func_01E04450_b508 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E04450_b508;

static s32 func_01E04450_b508(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    Rib_b024_01E02120 *p = arg0;
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
    extern W_tbl_func_01E04450_b508 D_01E06740_b508;
    W_tbl_func_01E04450_b508 tbl_w = D_01E06740_b508;
    Uvs_b024_01E02120 uvs;
    Pk_b024_01E02120 pk;
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
        b024_01E02120_tag((Pk_b024_01E02120 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
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

INCLUDE_ASM("asm/nonmatchings/mod/b508", func_01E05200_b508);

/* shape b508:01E05D90 (b508), 597 insns, 1 copy (-O2,p): -O2 scene manager: code >= 0 clears the scene, takes both
   units, the camera and six joints, sets up the walk emitters and the wave; else counts the frame: 2 arms two arcs,
   83 starts the fade, ray, 12 cores, 16 ribbons, the flare and the light, 150 ends; steps every effect; returns 6 on
   frames 83..111, 1/2 on frames 73/112 */

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 pad6[0xE];
    f32 f14;
    f32 f18;
    f32 f1C;
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b508_01E05D90;

typedef struct {
    s16 a;
    s16 b;
} Wv_b508_01E05D90;

typedef struct {
    void *emits;
    void *parts;
    s16 *frames[4];
    u8 pad18[0x10];
    u8 bone[4];
    u8 pad2C[4];
    u8 emit_kind;
    u8 part_kind;
    u8 kind;
    u8 pad33;
    s16 lo;
    s16 hi;
    f32 x0;
    f32 x1;
    f32 y;
} Walk_b508_01E05D90;

typedef struct {
    u8 pad0[0x30];
} Blade_b508_01E05D90;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6;
    u8 segs;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    u8 c[4];
    f32 radius;
    f32 grow;
    u8 pad18[4];
    Vec4f pos;
    u8 pad2C[0x20];
} Flear_b508_01E05D90;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    s8 *tbl;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    Vec4f pos;
    u8 pad38[0x20];
    s32 w58;
    s32 w5C;
    s32 w60;
    u8 pad64[4];
} Ray_b508_01E05D90;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    Vec4f pos;
    s32 w3C;
    s32 w40;
    s32 w44;
    u8 pad48[0x14];
} Core_b508_01E05D90;

typedef struct {
    u8 b0;
    u8 pad1[3];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    s8 *tbl;
    f32 f14;
    u8 pad18[4];
    f32 f1C;
    f32 f20;
    u8 c24[4];
    Vec4f pos;
    u8 pad38[0x20];
} Rib_b508_01E05D90;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 pad5[3];
} Fade_b508_01E05D90;

typedef struct {
    u8 pad0[5];
    u8 b5;
    u8 pad6[2];
    void *pool;
    s16 h[9];
    u8 pad1E;
    u8 b1F;
    u8 b20;
    u8 b21;
    u8 b22;
    u8 pad23;
    u8 pad24[4];
    f32 f28;
    f32 f2C;
    f32 f30;
    u8 c34[4];
    u8 pad38[0x10];
} Arc_b508_01E05D90;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    s32 m2;
    s32 m3;
    s32 m4;
    s32 m5;
    u8 pad24[8];
    u8 cam[0x14];
    Emit_b508_01E05D90 emit;
    Wv_b508_01E05D90 wv;
    Walk_b508_01E05D90 walk;
    u8 smk[0x20][0x38];
    u8 parts[0x32][0x28];
    Blade_b508_01E05D90 blade;
    Flear_b508_01E05D90 flear;
    Ray_b508_01E05D90 ray;
    Core_b508_01E05D90 core[12];
    Rib_b508_01E05D90 rib[16];
    Fade_b508_01E05D90 fade;
    Arc_b508_01E05D90 arc[2];
    u8 pool[0x200];
    s8 tbl[0x100];
    u8 pad1E04[0xC];
} Scene_b508_01E05D90;

#pragma optimization_level 2
#pragma opt_propagation off

static s32 func_01E05D90_b508(Scene_b508_01E05D90 *arg0, s32 arg1) {
    Scene_b508_01E05D90 *g = arg0;
    s32 code = arg1;
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_01E00080_b508();
    extern s32 b508_01E010E0(void *, u16);
    extern s32 func_01E00410_b508();
    extern s32 func_01E015A0_b508();
    extern s32 func_01E02000_b508();
    extern s32 func_01E02B80_b508();
    extern s32 func_01E03710_b508();
    extern s32 func_01E03F00_b508();
    extern s32 func_01E04450_b508();
    extern s32 func_01E05200_b508();
    extern s16 D_01E067E0_b508[];
    extern s16 D_01E067D0_b508[];
    s32 ot;
    Vec4f v;
    s32 i;
    s32 k;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x1E10);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0x2C, 1);
        g->m1 = func_001F5560(g->unitA, 0x17, 0);
        g->m2 = func_001F5560(g->unitA, 0xA, 0);
        g->m3 = func_001F5560(g->unitA, 0x33, 0);
        g->m4 = func_001F5560(g->unitA, 0x21, 0);
        g->m5 = func_001F5560(g->unitA, 0x22, 0);
        g->walk.bone[0] = g->m0;
        g->walk.bone[1] = g->m1;
        g->walk.bone[2] = g->m2;
        g->walk.bone[3] = g->m3;
        g->walk.frames[0] = D_01E067E0_b508;
        g->walk.frames[1] = D_01E067D0_b508;
        g->walk.frames[2] = D_01E067D0_b508;
        g->walk.frames[3] = D_01E067E0_b508;
        g->walk.emits = g->smk;
        g->walk.emit_kind = 0x20;
        g->walk.parts = g->parts;
        g->walk.part_kind = 0x32;
        g->walk.kind = 0;
        g->walk.lo = 0;
        g->walk.x0 = 300.0f;
        g->walk.y = 15.0f;
        g->wv.a = 2;
        g->wv.b = 0x90;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        for (k = 0; k < 2; k++) {
            func_00101AD0(&g->arc[k], 0x70, 0, 0xFF);
            g->arc[k].b5 = 1;
            if (k == 0) {
                g->arc[k].b21 = g->m4;
                g->arc[k].b22 = g->m5;
            } else {
                g->arc[k].b21 = g->m5;
                g->arc[k].b22 = g->m4;
            }
            g->arc[k].pool = g->pool;
            g->arc[k].pad1E = 0x20;
            g->arc[k].b1F = 5;
            g->arc[k].b20 = 1;
            g->arc[k].f2C = 40.0f;
            g->arc[k].f28 = 0.3f;
            g->arc[k].c34[0] = 0x80;
            g->arc[k].c34[1] = 0x80;
            g->arc[k].c34[2] = 0x80;
            g->arc[k].c34[3] = 0x80;
            for (i = 0; i < g->arc[k].b1F + 1; i++) {
                g->arc[k].h[i] = -1;
            }
            g->arc[k].f30 = -1.0f;
        }
        break;
    case 0x53:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.on = 1;
        func_00101AD0(&g->ray, 0x30, 0, 0xFF);
        g->ray.flags = 5;
        g->ray.f14 = 2.5f;
        g->ray.f1C = 60.0f;
        g->ray.b5 = 0;
        g->ray.bA = 1;
        g->ray.bB = 2;
        g->ray.bC = 3;
        g->ray.b8 = 0xA0;
        g->ray.b9 = func_0019A5C8() >> 4;
        g->ray.tbl = g->tbl;
        g->ray.f18 = 1.0f;
        g->ray.c24[0] = 0x80;
        g->ray.c24[1] = 0x80;
        g->ray.c24[2] = 0x80;
        g->ray.c20[0] = 0x80;
        g->ray.c20[1] = 0x80;
        g->ray.c20[2] = 0x80;
        g->ray.c20[3] = 0x20;
        g->ray.c24[3] = 0x80;
        g->ray.pos = v;
        g->ray.w58 = 0x40;
        g->ray.w5C = 0x80;
        g->ray.w60 = 0x100;
        for (i = 0; i < 12; i++) {
            func_00101AD0(&g->core[i], 0x30, (u8)(i % 3 * 2 + (i >> 2) * 4), 0xFF);
            g->core[i].b4 = 0;
            g->core[i].b7 = 0x24;
            g->core[i].bC = 1;
            g->core[i].b8 = 2;
            g->core[i].b9 = 2;
            g->core[i].bA = 6;
            g->core[i].bB = 0;
            g->core[i].f10 = 1.5f;
            g->core[i].f14 = 0.0f;
            g->core[i].f18 = 3.0f;
            g->core[i].f1C = 2.0f;
            g->core[i].f20 = 0.25f;
            g->core[i].c28[0] = 0x80;
            g->core[i].c28[1] = 0x80;
            g->core[i].c28[2] = 0x80;
            g->core[i].c24[0] = 0x80;
            g->core[i].c24[1] = 0x80;
            g->core[i].c24[2] = 0x80;
            g->core[i].c24[3] = 0x10;
            g->core[i].c28[3] = 0x30;
            g->core[i].pos = v;
            switch (i >> 2) {
            case 0:
                g->core[i].w3C = 0x4000;
                g->core[i].w40 = 0x3000;
                g->core[i].w44 = 0x2000;
                break;
            case 1:
                g->core[i].w44 = 0x3000;
                break;
            case 2:
                g->core[i].w44 = 0x1000;
                break;
            }
        }
        for (i = 0; i < 16; i++) {
            func_00101AD0(&g->rib[i], 0x20, (u8)(i * 2), 0xFF);
            g->rib[i].b0 -= 4;
            g->rib[i].b4 = 5;
            g->rib[i].b5 = 0;
            g->rib[i].b8 = 0x3C;
            g->rib[i].b9 = func_0019A5C8() >> 4;
            g->rib[i].bA = 1;
            g->rib[i].bC = 2;
            g->rib[i].bB = (func_0019A5C8() >> 4) & 3;
            g->rib[i].f1C = 120.0f;
            g->rib[i].f20 = 2.0f;
            g->rib[i].tbl = g->tbl;
            g->rib[i].f14 = 3.5f;
            g->rib[i].c24[3] = 0x80;
            g->rib[i].c24[0] = 0x80;
            g->rib[i].c24[1] = 0x80;
            g->rib[i].c24[2] = 0x80;
            g->rib[i].pos = v;
        }
        func_00101AD0(&g->flear, 0x34, 0, 0xFF);
        g->flear.b5 = 0;
        g->flear.flags = 0x81;
        g->flear.segs = 9;
        g->flear.c[3] = 0xF0;
        g->flear.c[0] = 0xF0;
        g->flear.c[1] = 0xF0;
        g->flear.c[2] = 0xF0;
        g->flear.bA = 0x80;
        g->flear.b9 = 0x80;
        g->flear.b8 = 0x10;
        g->flear.grow = 0.0f;
        g->flear.radius = 1500.0f;
        g->flear.pos = v;
        func_00101AD0(&g->emit, 0x30, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.2f;
        g->emit.f18 = 2.0f;
        g->emit.f1C = 1.2f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 6.0f;
        g->emit.pos = v;
        break;
    case 0x96:
        return 8;
    }
    func_01E00080_b508(&g->emit);
    func_001031C0(&g->wv, g->t);
    b508_01E010E0(&g->walk, g->t);
    func_01E00410_b508(g->smk, ot, 0x20);
    func_01E015A0_b508(&g->blade, ot, 1);
    func_01E02000_b508(&g->flear, ot, 1);
    func_01E02B80_b508(&g->ray, ot, 1);
    func_01E03710_b508(g->core, ot, 0xC);
    func_01E03F00_b508(&g->fade, ot);
    func_01E04450_b508(g->rib, ot, 0x10);
    func_01E05200_b508(g->arc, ot, 2);
    if (g->t >= 0x53 && g->t < 0x70) {
        return 6;
    }
    switch (g->t) {
    case 0x49:
        return 1;
    case 0x70:
        return 2;
    }
    return 0;
}
#pragma opt_propagation reset
#pragma optimization_level reset
