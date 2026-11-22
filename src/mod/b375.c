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

static void func_01E00080_b375(Obj_b010_01E00080 *o) {
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

static s32 func_01E00410_b375(void *arg0, s32 ot, s32 n) {
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

static void func_01E00DC0_b375(Emit_b010_01E00DC0 *e) {
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

extern void b375_01E00DC0(Burst_b010_01E010E0 *);

#pragma optimization_level 2

static s32 func_01E010E0_b375(Obj_b010_01E010E0 *obj, u16 frame) {
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
                    b375_01E00DC0(&burst);
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

extern Tex_b532_01E00080 D_01E05A00_b375;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E015A0_b375(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E05A00_b375;
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

/* shape b213:01E00F90 (ShFx_Core01), 644 insns, 28 copies (-O2,p): update and draw spinning 2-D beams (0x50 bytes
   each): move, project, and draw each as two quads per half-turn, alpha and length fading in and out */

#define ABS_b213_01E00F90(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b213_01E00F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b213_01E00F90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b213_01E00F90 p;
} Vtx_b213_01E00F90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b213_01E00F90 v[4];
    u8 tail[0x20];
} Pkt_b213_01E00F90;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b213_01E00F90;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 b, g, r;
    u8 pad0B;
    u8 b2, g2, r2, a;
    f32 len;
    f32 width;
    f32 angle;
    f32 spin;
    Vec_b213_01E00F90 pos;
    Vec_b213_01E00F90 vel;
    Vec_b213_01E00F90 point;
} Beam_b213_01E00F90;

#pragma optimization_level 2

static s32 func_01E02130_b375(void *p, s32 target, s32 count) {
    extern Tex_b213_01E00F90 D_01E05A20_b375;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Beam_b213_01E00F90 *o = p;
    s32 i;
    s32 h __attribute__((aligned(16)));
    s32 j;
    u8 k;
    u8 a;
    s32 s;
    f32 zd;
    f32 dx;
    f32 ady;
    f32 dy;
    f32 len;
    f32 r1;
    f32 w;
    f32 t;
    f32 m2[16];
    f32 m1[16];
    Vec_b213_01E00F90 pt;
    Tex_b213_01E00F90 tex;
    Xyz_b213_01E00F90 q;
    Pkt_b213_01E00F90 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E05A20_b375;
    h = func_00202BF0(tex.id, tex.kind);
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->angle += o->spin;
        pt = o->point;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m2, 0, 0, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = 0;
        pkt.v[1].r = pkt.v[2].r = o->r;
        pkt.v[0].g = 0;
        pkt.v[1].g = pkt.v[2].g = o->g;
        pkt.v[0].b = 0;
        pkt.v[1].b = pkt.v[2].b = o->b;
        pkt.v[3].r = o->r2;
        pkt.v[3].g = o->g2;
        pkt.v[3].b = o->b2;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_00101EE0(&pkt, &tex, h);
        a = o->a;
        s = a >> 3;
        if (o->life >= 8 || (o->flags & 0x40)) {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = a;
        } else {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = s * o->life;
        }
        pkt.v[0].a = 0;
        if (func_00205440(&pt, m1, &q, &dep) == 0 || func_00101600(&q) == 0) {
            continue;
        }
        r1 = func_001018E0(o->len, dep);
        w = func_001018E0(o->width, dep);
        if (o->flags & 0x80) {
            q.z = 0xFFFFFE;
            zd = 0.0f;
        } else {
            zd = dep;
        }
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
        pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
        len = r1;
        if (!(o->flags & 0x40)) {
            if (!(o->flags & 1)) {
                k = o->total - o->life;
                if (k < 8) {
                    len = r1 * (0.125f * k);
                }
            }
            if (o->life < 8) {
                len = r1 * (0.125f * o->life);
            }
        }
        for (j = 0; j < 2; j++) {
            t = 180.0f * j;
            dx = len * func_001A6898(3.1415927f * (o->angle + t) / 180.0f);
            dy = len * func_001A6A88(3.1415927f * (o->angle + t) / 180.0f);
            ady = ABS_b213_01E00F90(dy);
            if (!(ABS_b213_01E00F90(dx) <= ady)) {
                pkt.v[0].p.x = pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[1].p.x = pkt.v[3].p.x = q.x;
                pkt.v[0].p.y = (u32)(q.y + dy - w);
                pkt.v[1].p.y = (u32)(q.y - w);
                pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[3].p.y = q.y;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.y = (u32)(w + (q.y + dy));
                pkt.v[1].p.y = (u32)(q.y + w);
                func_002075F0(&pkt, target, (u32)zd);
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[1].p.y = pkt.v[3].p.y = q.y;
                pkt.v[0].p.x = (u32)(q.x + dx - w);
                pkt.v[1].p.x = (u32)(q.x - w);
                pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[3].p.x = q.x;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.x = (u32)(w + (q.x + dx));
                pkt.v[1].p.x = (u32)(q.x + w);
                func_002075F0(&pkt, target, (u32)zd);
            }
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

static s32 func_01E02B40_b375(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E05A40_b375;
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
    t = D_01E05A40_b375;
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

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E04D20, 646 insns, 49 copies: update and draw a pool of particles (0x44 bytes each): move,
   floor bounce, colour and frame, project, then one textured sprite whose corners follow the flip bits */

typedef struct Part_b010_01E04D20 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 frame;
    u8 anim;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    f32 grow;
    f32 grav;
    f32 floor;
    f32 pos[3];
    f32 vel[3];
    f32 acc[3];
} Part_b010_01E04D20;

typedef struct Xyz_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b010_01E04D20;

typedef struct Pk_b010_01E04D20 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b010_01E04D20 v[4];
    u64 pad60[3];
} Pk_b010_01E04D20;

typedef struct Buf_b010_01E04D20 {
    u64 tag;
    Pk_b010_01E04D20 pk;
} Buf_b010_01E04D20;

typedef struct Uvs_b010_01E04D20 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b010_01E04D20;

typedef struct Scr_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b010_01E04D20;

static inline void b010_01E04D20_tag(Pk_b010_01E04D20 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E036C0_b375(Part_b010_01E04D20 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b010_01E04D20 *p = arg0;
    s32 i;
    s32 tex;
    s32 life;
    s32 frame;
    f32 half;
    f32 zf;
    u16 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b010_01E04D20 uvs;
    Pk_b010_01E04D20 pk __attribute__((aligned(8)));
    Scr_b010_01E04D20 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->vel[0] += p->acc[0];
        p->vel[1] += p->acc[1] + p->grav;
        p->vel[2] += p->acc[2];
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->size += p->grow;
        if (p->pos[1] < p->floor) {
            p->pos[1] = p->floor;
            if (p->flags & 2) {
                p->vel[1] = -(0.7f * p->vel[1]);
            }
        }
        if (p->follow != 0) {
            func_00101BA0(p, &tmp);
            p->pos[0] = tmp.x;
            p->pos[1] = tmp.y;
            p->pos[2] = tmp.z;
        }
        pos.x = p->pos[0];
        pos.y = p->pos[1];
        pos.z = p->pos[2];
        func_0020EB40(m);
        ((Pk_b010_01E04D20 *)(u32)&pk)->flags = 0x24;
        ((Pk_b010_01E04D20 *)(u32)&pk)->size = 9;
        ((Pk_b010_01E04D20 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b010_01E04D20 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        life = p->life - p->age;
        frame = p->frame;
        if (p->flags & 1) {
            frame = (u8)func_001022D0(p->anim, life);
            if (p->flags & 4) {
                p->flags &= 0xCF;
                p->flags |= (u8)(((func_0019A5C8() >> 4) & 3) << 4);
            }
        }
        uvs.b5 = p->bB;
        func_001020B0(&uvs, frame, p->anim);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 0x10) {
            pk.a = (p->a >> 4) * p->age;
        }
        if (func_00205440(&pos, m, &scr, &depth) == 0) {
            continue;
        }
        if (func_00101600(&scr) == 0) {
            continue;
        }
        half = func_001018E0(p->size, depth);
        if (p->flags & 0x80) {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
            zf = depth;
        }
        switch (p->flags & 0x30) {
        case 0x10:
            c = scr.x;
            pk.v[0].x = pk.v[1].x = (u32)(c - half);
            pk.v[2].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[1].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[2].y = (u32)(c + half);
            break;
        case 0x20:
            c = scr.x;
            pk.v[1].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[2].x = (u32)(c + half);
            c = scr.y;
            pk.v[2].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[1].y = (u32)(c + half);
            break;
        case 0x30:
            c = scr.x;
            pk.v[2].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[1].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[2].y = (u32)(c - half);
            pk.v[1].y = pk.v[3].y = (u32)(c + half);
            break;
        default:
            c = scr.x;
            pk.v[0].x = pk.v[2].x = (u32)(c - half);
            pk.v[1].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[1].y = (u32)(c - half);
            pk.v[2].y = pk.v[3].y = (u32)(c + half);
            break;
        }
        func_002075F0((s32)&pk, id, (u32)(zf));
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

static s32 func_01E040E0_b375(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
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

/* shape b032:01E02820 (ShFx_Swave01), 538 insns, 5 copies (-O2,p): draws n ring/cone emitters (0x48 bytes each): a
   quarter ring of up to 9 segments between an inner radius at height y+dy and an outer one at y, mirrored into four
   quadrants as quads; texture page from a 4-entry module table by e->type, STQ from the page rectangle (types 1-3) or
   func_00101EE0; the source of shape b059:01E00440, built here at -O2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b032_01E02820;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b032_01E02820 xyz;
} Vtx_b032_01E02820;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b032_01E02820 v[4];
    u8 tail[0x20];
} Pkt_b032_01E02820;

typedef struct {
    s32 id;
    u8 sub;
    u8 pad5[3];
    s32 u, w, v, h;
} Tex_b032_01E02820;

typedef struct {
    Tex_b032_01E02820 e[4];
} Tab_b032_01E02820;

typedef struct {
    u8 b, g, r, a;
} Col_b032_01E02820;

typedef struct {
    u8 life;
    u8 pad1[6];
    u8 seg;
    u8 type;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 scale;
    f32 base;
    f32 dy;
    f32 y;
    f32 vy;
    Col_b032_01E02820 c0;
    Col_b032_01E02820 c1;
    Vec4f pos;
    Vec4f rot;
} Emit_b032_01E02820;

extern Tab_b032_01E02820 D_01E05A60_b375;

#pragma optimization_level 2

static s32 func_01E04630_b375(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f a[10];
    Vec4f b[10];
    Vec4f c[4];
    f32 depth[4];
    Tab_b032_01E02820 tab;
    Tex_b032_01E02820 td;
    Pkt_b032_01E02820 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b032_01E02820 *e;
    s32 i;
    s32 j;
    s32 k;
    s32 nseg;
    s32 tex;
    f32 sn;
    f32 step;
    f32 r1;
    f32 r2;
    f32 cs;

    e = arg0;
    tab = D_01E05A60_b375;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(tab.e[e->type].id, tab.e[e->type].sub);
        e->y += e->vy;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        if (e->seg > 9) {
            nseg = 9;
        } else {
            nseg = e->seg;
        }
        step = 90.0f / nseg;
        r1 = e->scale * (e->y + e->dy) / e->base;
        r2 = e->scale * e->y / e->base;
        for (j = 0; j < nseg + 1; j++) {
            sn = func_001A6A88(3.1415927f * (step * j) / 180.0f);
            cs = func_001A6898(3.1415927f * (step * j) / 180.0f);
            a[j].x = r1 * cs;
            a[j].z = r1 * sn;
            a[j].y = e->y + e->dy;
            b[j].x = r2 * cs;
            b[j].z = r2 * sn;
            b[j].y = e->y;
        }
        ((Pkt_b032_01E02820 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b032_01E02820 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b032_01E02820 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b032_01E02820 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        c[0].y = c[1].y = a[0].y;
        c[2].y = c[3].y = b[0].y;
        for (j = 0; j < nseg; j++) {
            for (k = 0; k < 4; k++) {
                switch (k) {
                case 0:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    c[0].z = a[j].z;
                    c[1].z = a[j + 1].z;
                    c[2].z = b[j].z;
                    c[3].z = b[j + 1].z;
                    break;
                case 1:
                    c[0].x = -a[j].x;
                    c[1].x = -a[j + 1].x;
                    c[2].x = -b[j].x;
                    c[3].x = -b[j + 1].x;
                    break;
                case 2:
                    c[0].z = -a[j].z;
                    c[1].z = -a[j + 1].z;
                    c[2].z = -b[j].z;
                    c[3].z = -b[j + 1].z;
                    break;
                case 3:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    break;
                }
                if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                    func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                    func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                    func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    td = tab.e[e->type];
                    switch (e->type) {
                    case 1:
                    case 2:
                    case 3:
                        func_00208CB0(&pkt, 0xB | ((u64)e->b9 << 4) | ((u64)td.u << 14) | ((u64)td.v << 24) |
                                                ((u64)(td.h - 1) << 34));
                        td.u = 0;
                        td.w = e->bA;
                        pkt.v[0].q = 1.0f / depth[0];
                        pkt.v[1].q = 1.0f / depth[1];
                        pkt.v[2].q = 1.0f / depth[2];
                        pkt.v[3].q = 1.0f / depth[3];
                        pkt.v[0].s = td.u / 256.0f / depth[0];
                        pkt.v[0].t = td.v / 256.0f / depth[0];
                        pkt.v[1].s = td.w / 256.0f / depth[1];
                        pkt.v[1].t = td.v / 256.0f / depth[1];
                        pkt.v[2].s = td.u / 256.0f / depth[2];
                        pkt.v[2].t = td.h / 256.0f / depth[2];
                        pkt.v[3].s = td.w / 256.0f / depth[3];
                        pkt.v[3].t = td.h / 256.0f / depth[3];
                        func_00101C80(&td, bl);
                        func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                        func_00208700(&pkt, (void *)tex, 1);
                        break;
                    default:
                        func_00101EE0(&pkt, &td, (void *)tex);
                        break;
                    }
                    func_002075F0((s32)&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b375:01E04EA0 (b375), 722 insns, 1 copy (-O2,p): b375 scene manager: b095:01E03C40's form; joint waves and
   gus at 0x32, fade/waves/flare/ray/gus/emit at 0x90, ends at 0xC9 */

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
} Emit_b375_01E04EA0;

typedef struct {
    void *emits;
    void *parts;
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
} Walk_b375_01E04EA0;

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
    f32 f18;
    Vec4f pos;
    u8 pad2C[0x10];
    f32 ox;
    f32 oy;
    f32 oz;
    u8 pad48[4];
} Flear_b375_01E04EA0;

typedef struct {
    u8 pad0[0x50];
} Beam_b375_01E04EA0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    void *tbl;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    Vec4f pos;
    u8 pad38[0x20];
    s32 r58;
    s32 r5C;
    s32 r60;
    u8 pad64[4];
} Rib_b375_01E04EA0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[3];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 c[4];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 x;
    f32 y;
    f32 z;
    f32 f2C;
    f32 f30;
    f32 f34;
    u8 pad38[0xC];
} Gus_b375_01E04EA0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c[4];
    u8 d[4];
    Vec4f pos;
    s32 rot;
    u8 pad3C[0xC];
} Wave_b375_01E04EA0;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 pad5[3];
} Fade_b375_01E04EA0;

typedef struct {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b375_01E04EA0;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    s32 m2;
    u8 pad18[0x14];
    Cam_b375_01E04EA0 cam;
    Emit_b375_01E04EA0 emit;
    Walk_b375_01E04EA0 walk;
    u8 smk[0x20][0x38];
    u8 parts[0x3C][0x28];
    Flear_b375_01E04EA0 flear;
    Beam_b375_01E04EA0 core[4];
    Gus_b375_01E04EA0 gus[0xC8];
    Rib_b375_01E04EA0 ray;
    s16 span[2];
    Fade_b375_01E04EA0 fade;
    Wave_b375_01E04EA0 wave[6];
    s8 tbl[0x100];
    u8 pad4B14[0xC];
} Scene_b375_01E04EA0;

#pragma optimization_level 2

static s32 func_01E04EA0_b375(Scene_b375_01E04EA0 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_01E00080_b375();
    extern s32 func_01E040E0_b375();
    extern s32 b375_01E010E0(void *, u16);
    extern s32 func_01E00410_b375();
    extern s32 func_01E02B40_b375();
    extern s32 func_01E02130_b375();
    extern s32 func_01E015A0_b375();
    extern s32 func_01E036C0_b375();
    extern s32 func_01E04630_b375();
    extern s16 D_01E05AC0_b375[];
    extern s16 D_01E05AD0_b375[];
    extern s16 D_01E05AE0_b375[];
    s32 ot;
    Vec4f v;
    Vec4f v2;
    s32 i;
    s32 k;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x4B20);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0x45, 1);
        g->m1 = func_001F5560(g->unitA, 0x4D, 0);
        g->m2 = func_001F5560(g->unitA, 0x31, 0);
        g->walk.bone[0] = g->m0;
        g->walk.bone[1] = g->m1;
        g->walk.bone[2] = g->m2;
        g->walk.frames[0] = D_01E05AC0_b375;
        g->walk.frames[1] = D_01E05AD0_b375;
        g->walk.frames[2] = D_01E05AE0_b375;
        g->walk.emits = g->smk;
        g->walk.emit_kind = 0x20;
        g->walk.parts = g->parts;
        g->walk.part_kind = 0x3C;
        g->walk.kind = 0;
        g->walk.lo = 0;
        g->walk.x0 = 150.0f;
        g->walk.x1 = 0.0f;
        g->walk.y = 6.0f;
        g->span[0] = 2;
        g->span[1] = 0xC3;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x32:
        func_001F5620(g->unitA, g->m2, &v2);
        for (k = 0; k < 1; k++) {
            func_00101AD0(&g->wave[k], 0x10, (u8)(k * 3), 0xFF);
            g->wave[k].b4 = 0;
            g->wave[k].b5 = 0;
            g->wave[k].b7 = 9;
            g->wave[k].b8 = 2;
            g->wave[k].fC = 1.0f;
            g->wave[k].f10 = 0.1f;
            g->wave[k].f14 = 0.3f;
            g->wave[k].f18 = 0.0f;
            g->wave[k].f1C = 0.03f;
            g->wave[k].c[3] = 0x80;
            g->wave[k].c[0] = 0x80;
            g->wave[k].c[1] = 0x80;
            g->wave[k].c[2] = 0x80;
            g->wave[k].d[2] = 0xC0;
            g->wave[k].d[1] = 0;
            g->wave[k].d[0] = 0;
            g->wave[k].d[3] = 0;
            g->wave[k].pos = v2;
        }
        for (i = 0; i < 0x50; i++) {
            k = func_00101C30(g->gus, 0x44, 0xC8);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x20, func_0019A5C8() >> 4 & 7, 0xFF);
                g->gus[k].b4 = 0;
                g->gus[k].b8 = 1;
                g->gus[k].bB = 2;
                g->gus[k].bA = 0;
                g->gus[k].b9 = 3;
                g->gus[k].c[3] = 0x80;
                g->gus[k].c[0] = 0x80;
                g->gus[k].c[1] = 0x80;
                g->gus[k].c[2] = 0x80;
                g->gus[k].f10 = 20.0f;
                g->gus[k].f14 = 0.0f;
                g->gus[k].f18 = -0.05f;
                g->gus[k].f1C = 0.0f;
                g->gus[k].x = v2.x;
                g->gus[k].y = v2.y;
                g->gus[k].z = v2.z;
                g->gus[k].f2C = (f32)((func_0019A5C8() >> 4) % 80 - 40) / 100.0f;
                g->gus[k].f30 = 0.8f + (f32)((func_0019A5C8() >> 4) % 20 - 10) / 100.0f;
                g->gus[k].f34 = (f32)((func_0019A5C8() >> 4) % 80 - 40) / 100.0f;
            }
        }
        break;
    case 0x90:
        func_00101AD0(&g->fade, 0xA, 0, 0xFF);
        g->fade.on = 1;
        for (k = 0; k < 6; k++) {
            func_00101AD0(&g->wave[k], 0x18, (u8)k, 0xFF);
            g->wave[k].b4 = 0;
            g->wave[k].b5 = 0;
            g->wave[k].b7 = 9;
            g->wave[k].b8 = 2;
            g->wave[k].bA = 0x20;
            g->wave[k].b9 = 7;
            g->wave[k].fC = 2.0f;
            g->wave[k].f10 = 0.3f;
            g->wave[k].f14 = 1.5f;
            g->wave[k].f18 = 0.0f;
            g->wave[k].f1C = 0.12f;
            g->wave[k].c[2] = 0xA0;
            g->wave[k].c[1] = 0xA0;
            g->wave[k].c[0] = 0xA0;
            g->wave[k].c[3] = 0;
            g->wave[k].d[2] = 0xC0;
            g->wave[k].d[1] = 0x20;
            g->wave[k].d[0] = 0x10;
            g->wave[k].d[3] = 0x80;
            g->wave[k].pos = v;
            if (g->cam.dir == 0x8000) {
                g->wave[k].rot = 0x4000;
            } else {
                g->wave[k].rot = -0x4000;
            }
        }
        func_00101AD0(&g->flear, 0x20, 0, 0xFF);
        g->flear.b5 = 0;
        g->flear.segs = 9;
        g->flear.flags = 0x81;
        g->flear.radius = 800.0f;
        g->flear.grow = g->flear.f18 = 0.0f;
        g->flear.c[3] = 0xC0;
        g->flear.c[0] = 0xC0;
        g->flear.c[1] = 0xC0;
        g->flear.c[2] = 0xC0;
        g->flear.bA = 0x20;
        g->flear.b9 = 0x10;
        g->flear.b8 = 0x80;
        g->flear.ox = g->flear.oy = g->flear.oz = 0.0f;
        g->flear.pos = v;
        func_00101AD0(&g->ray, 0x1C, 0, 0xFF);
        g->ray.b4 = 5;
        g->ray.f14 = 2.5f;
        g->ray.f1C = 40.0f;
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
        g->ray.r58 = 0x40;
        g->ray.r5C = 0x80;
        g->ray.r60 = 0x100;
        for (i = 0; i < 0xC8; i++) {
            k = func_00101C30(g->gus, 0x44, 0xC8);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x20, func_0019A5C8() >> 4 & 0xF, 0xFF);
                g->gus[k].b4 = 0;
                g->gus[k].b8 = 1;
                g->gus[k].bB = 2;
                g->gus[k].bA = 0;
                g->gus[k].b9 = 3;
                g->gus[k].c[3] = 0x80;
                g->gus[k].c[0] = 0x80;
                g->gus[k].c[1] = 0x80;
                g->gus[k].c[2] = 0x80;
                g->gus[k].f10 = 120.0f + (f32)((func_0019A5C8() >> 4) % 20 * 200 - 2000) / 100.0f;
                g->gus[k].f14 = -0.8f;
                g->gus[k].f18 = -0.09f;
                g->gus[k].f1C = 0.0f;
                g->gus[k].x = v.x;
                g->gus[k].y = v.y;
                g->gus[k].z = v.z;
                g->gus[k].f2C = (f32)((func_0019A5C8() >> 4) % 230 - 115) / 100.0f;
                g->gus[k].f30 = 0.8f + (f32)((func_0019A5C8() >> 4) % 230 - 115) / 100.0f;
                g->gus[k].f34 = (f32)((func_0019A5C8() >> 4) % 230 - 115) / 100.0f;
            }
        }
        func_00101AD0(&g->emit, 0x20, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 1.6f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 6.0f;
        func_001F5F90(g->unitB, &g->emit.pos);
        break;
    case 0xC9:
        return 8;
    }
    func_01E00080_b375(&g->emit);
    func_001031C0(g->span, g->t);
    func_01E040E0_b375(&g->fade, ot);
    b375_01E010E0(&g->walk, g->t);
    func_01E00410_b375(g->smk, ot, 0x20);
    func_01E02B40_b375(&g->flear, ot, 1);
    func_01E02130_b375(g->core, ot, 4);
    func_01E015A0_b375(&g->ray, ot, 1);
    func_01E036C0_b375(g->gus, ot, 0xC8);
    func_01E04630_b375(g->wave, ot, 6);
    switch (g->t) {
    case 0x86:
        return 1;
    case 0x8D:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
