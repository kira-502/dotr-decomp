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

static void func_01E00080_b104(Obj_b010_01E00080 *o) {
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

static s32 func_01E00410_b104(void *arg0, s32 ot, s32 n) {
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

static void func_01E00DC0_b104(Emit_b010_01E00DC0 *e) {
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

extern void b104_01E00DC0(Burst_b010_01E010E0 *);

#pragma optimization_level 2

static s32 func_01E010E0_b104(Obj_b010_01E010E0 *obj, u16 frame) {
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
                    b104_01E00DC0(&burst);
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
typedef struct W_tbl_func_01E015A0_b104 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E015A0_b104;

static s32 func_01E015A0_b104(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E015A0_b104 D_01E04980_b104;
    W_tbl_func_01E015A0_b104 tbl_w = D_01E04980_b104;
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

static s32 func_01E02350_b104(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E049E0_b104;
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
    t = D_01E049E0_b104;
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b104:01E02ED0, 359 insns: draws n streak emitters (0x50 bytes each): a sprite from the emitter's position
   to position + dir * (life - age), turned by its rotation, widened on screen sideways or up (flags & 3: 1 up,
   2 sideways, else by the streak's slope); alpha fades in over the first 8 ticks. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b104_01E02ED0;

typedef struct {
    u64 uv;
    Xyz_b104_01E02ED0 xyz;
} Vtx_b104_01E02ED0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b104_01E02ED0 v[4];
    u8 tail[0x20];
} Pkt_b104_01E02ED0;

typedef struct {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b104_01E02ED0;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    f32 width;
    u8 b, g, r, a;
    Vec4f pos;
    Vec4f dir;
    Vec4f rot;
    u8 pad40[0x10];
} Streak_b104_01E02ED0;

#pragma optimization_level 2

static s32 func_01E02ED0_b104(Streak_b104_01E02ED0 *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101D20(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    Streak_b104_01E02ED0 *e = arg0;
    s32 tex __attribute__((aligned(16)));
    s32 i;
    s32 h;
    s32 k;
    s32 dx;
    s32 dy;
    f32 l;
    f32 w;
    f32 w0;
    f32 w1;
    f32 m2[16];
    f32 m[16];
    Vec4f p[2];
    Xyz_b104_01E02ED0 xy[2];
    extern Uvs_b104_01E02ED0 D_01E04A00_b104;
    Uvs_b104_01E02ED0 tbl = D_01E04A00_b104;
    f32 dep[2] __attribute__((aligned(16)));
    Pkt_b104_01E02ED0 pkt __attribute__((aligned(8)));

    tex = func_00202BF0(tbl.kind, tbl.tex);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        func_0020C940(m2, NULL, &e->rot, &e->pos);
        func_0020BC00(m, m2);
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->tag = 9;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b104_01E02ED0 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        func_00101D20(&pkt, &tbl, tex);
        if (e->age < 8) {
            pkt.a = (e->a >> 3) * e->age;
        } else {
            pkt.a = e->a;
        }
        k = e->life - e->age;
        p[0].z = 0.0f;
        p[0].y = 0.0f;
        p[0].x = 0.0f;
        l = k;
        p[1].x = e->dir.x * l;
        p[1].y = e->dir.y * l;
        p[1].z = e->dir.z * l;
        if (func_00205440(&p[0], m, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0 ||
            func_00205440(&p[1], m, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        w = e->width;
        w0 = w / (dep[0] / 256.0f);
        w1 = w / (dep[1] / 256.0f);
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[1].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[0].z;
        switch (e->flags & 3) {
        case 1:
            h = 0;
            break;
        case 2:
            h = 1;
            break;
        default:
            dy = xy[0].y - xy[1].y;
            dy = dy >= 0 ? dy : -dy;
            dx = xy[0].x - xy[1].x;
            dx = dx >= 0 ? dx : -dx;
            h = dy < dx;
            break;
        }
        if (h != 0) {
            pkt.v[0].xyz.y = (u32)((f32)(u32)xy[1].y - w1);
            pkt.v[1].xyz.y = (u32)((f32)(u32)xy[0].y - w0);
            pkt.v[2].xyz.y = xy[1].y;
            pkt.v[3].xyz.y = xy[0].y;
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[1].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[0].x;
            func_002075F0(&pkt, ot, 0);
        } else {
            pkt.v[0].xyz.x = (u32)((f32)(u32)xy[1].x - w1);
            pkt.v[1].xyz.x = (u32)((f32)(u32)xy[0].x - w0);
            pkt.v[2].xyz.x = xy[1].x;
            pkt.v[3].xyz.x = xy[0].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[1].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[0].y;
            func_002075F0(&pkt, ot, 0);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b104:01E03470 (ShFx_Dlyline), 624 insns, 1 copy (-O2,p): ShFx_Dlyline: n delayed lines (0x48 bytes each):
   move unless flag 1, shift the point history in the pool, splined through func_00102550 and drawn as four widened
   quads per segment, alpha fading toward the tail */

typedef struct {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b104_01E03470;

typedef struct {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Pool_b104_01E03470 *pool;
    s16 idx[9];
    u8 slot;
    u8 count;
    f32 width;
    u8 b, g, r, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
} Line_b104_01E03470;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b104_01E03470;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b104_01E03470;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b104_01E03470 xyz;
} Vtx_b104_01E03470;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b104_01E03470 v[4];
} Pkt_b104_01E03470;

#pragma optimization_level 2

static s32 func_01E03470_b104(Line_b104_01E03470 *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101B40(void *, u8, u8);
    Line_b104_01E03470 *e = arg0;
    Pool_b104_01E03470 *pool = arg0->pool;
    Pool_b104_01E03470 *pt;
    s32 i __attribute__((aligned(16)));
    s32 k;
    s32 idx;
    s32 segs;
    s32 t;
    f32 a;
    f32 step;
    f32 w;
    f32 w0;
    f32 w1;
    f32 m[16];
    Spl_b104_01E03470 spl;
    Xyz_b104_01E03470 s[2];
    Pkt_b104_01E03470 pkt;
    f32 dep[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_0020EB40(m);
        if (!(e->flags & 1)) {
            e->pos[0] += e->vel[0];
            e->pos[1] += e->vel[1];
            e->pos[2] += e->vel[2];
            func_00101BA0(e, e->pos);
        }
        for (k = e->count; k > 0; k--) {
            if (e->idx[k - 1] >= 0) {
                pt = &pool[e->idx[k - 1]];
                pt->kind = e->kind;
            }
            e->idx[k] = e->idx[k - 1];
        }
        if (e->idx[e->count] >= 0) {
            pt = &pool[e->idx[e->count]];
            pt->kind = 0;
            e->idx[e->count] = -1;
        }
        if (e->kind == 0) {
            continue;
        }
        idx = func_00101C30(pool, 0x10, e->slot);
        if (idx >= 0) {
            e->idx[0] = idx;
            pt = &pool[e->idx[0]];
            func_00101B40(pt, e->kind, 0);
            pt->x = e->pos[0];
            pt->y = e->pos[1];
            pt->z = e->pos[2];
        } else {
            e->idx[0] = -1;
        }
        spl.n = 0;
        for (k = 0; k < e->count; k++) {
            if (e->idx[k] >= 0) {
                pt = &pool[e->idx[k]];
                spl.x[spl.n] = pt->x;
                spl.y[spl.n] = pt->y;
                spl.z[spl.n] = pt->z;
                spl.n++;
            }
        }
        if (func_00102550(&spl) == 0) {
            continue;
        }
        segs = (spl.n - 1) * 4;
        ((Pkt_b104_01E03470 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b104_01E03470 *)(s32)&pkt)->tag = 8;
        ((Pkt_b104_01E03470 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b104_01E03470 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
        func_002086D0(&pkt, 0x48);
        pkt.v[0].a = pkt.v[1].a = 0;
        if (e->kind < 8) {
            a = (f32)e->kind * (f32)e->a / 8.0f;
        } else {
            a = e->a;
        }
        step = a / (f32)segs;
        for (k = 0; k < segs - 1; k++) {
            if (func_00205440(&spl.out[k], m, &s[0], &dep[0]) == 0 || func_00101600(&s[0]) == 0 ||
                func_00205440(&spl.out[k + 1], m, &s[1], &dep[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            w = e->width;
            w0 = w / (dep[0] / 256.0f);
            w1 = w / (dep[1] / 256.0f);
            t = segs - k;
            pkt.v[2].a = func_001A23B0(step * t);
            pkt.v[3].a = func_001A23B0(step * (t - 1));
            if (k == 0) {
                pkt.v[2].a = 0;
            }
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[0].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[1].z;
            pkt.v[2].xyz.y = s[0].y;
            pkt.v[3].xyz.y = s[1].y;
            pkt.v[0].xyz.y = (u32)((f32)s[0].y - w0);
            pkt.v[1].xyz.y = (u32)((f32)s[1].y - w1);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
            func_002075F0(&pkt, ot, 0);
            pkt.v[0].xyz.y = (u32)((f32)s[0].y + w0);
            pkt.v[1].xyz.y = (u32)((f32)s[1].y + w1);
            func_002075F0(&pkt, ot, 0);
            pkt.v[0].xyz.x = (u32)((f32)s[0].x - w0);
            pkt.v[1].xyz.x = (u32)((f32)s[1].x - w1);
            pkt.v[2].xyz.x = s[0].x;
            pkt.v[3].xyz.x = s[1].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
            func_002075F0(&pkt, ot, 0);
            pkt.v[0].xyz.x = (u32)((f32)s[0].x + w0);
            pkt.v[1].xyz.x = (u32)((f32)s[1].x + w1);
            func_002075F0(&pkt, ot, 0);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b104:01E03E30 (b104), 705 insns, 1 copy (-O2,p): b104 scene manager (-O2): code >= 0 clears the scene, takes
   both units, the camera and five joints, sets up the walk effect; else counts the frame: 0x7C sets up 36 streaks on
   two 18-point rings, the emitter, the flare and four ribbons around the joints; 0x72..0x7B place 11 delayed lines on
   a joint ring (set up at 0x72), 0xCC ends; steps every effect; returns 1/2 on 0x72/0x79 */

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
} Emit_b104_01E03E30;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    f32 width;
    u8 b, g, r, a;
    Vec4f pos;
    Vec4f dir;
    u8 pad30[0x20];
} Streak_b104_01E03E30;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    void *pool;
    s16 idx[9];
    u8 slot;
    u8 count;
    f32 width;
    u8 b, g, r, a;
    f32 pos[3];
    u8 pad34[0x14];
} Line_b104_01E03E30;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 count;
    u8 k;
    u8 idx;
    u8 padB[5];
    s8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    Vec4f pos;
    u8 pad38[0x20];
} Rib_b104_01E03E30;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    Vec4f vel;
    Vec4f org;
} Flare_b104_01E03E30;

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
    u8 pad20[0xC];
    u8 cam[0x14];
    Emit_b104_01E03E30 emit;
    Obj_b010_01E010E0 obj;
    u8 emits[0x700];
    u8 parts[0x7D0];
    Flare_b104_01E03E30 flare;
    Streak_b104_01E03E30 streak[36];
    Line_b104_01E03E30 line[11];
    Rib_b104_01E03E30 rib[4];
    u8 pool[0x5A0];
    s8 tbl[0x100];
    u8 pad2658[8];
} Scene_b104_01E03E30;

#pragma optimization_level 2

static s32 func_01E03E30_b104(Scene_b104_01E03E30 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101A00(void *, void *);
    extern f32 func_0020D0E0(void *);
    extern f32 func_001A6A88(f32);
    extern f32 func_001A6898(f32);
    extern void func_0020CDD0(void *, void *, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern s16 D_01E04A20_b104[];
    extern s16 D_01E04A40_b104[];
    s32 ot;
    Vec4f p[2];
    Vec4f q[2];
    Vec4f ve;
    Vec4f vf;
    Vec4f vh;
    Vec4f vw;
    Vec4f m[4];
    s32 i;
    s32 j;
    f32 a;
    f32 r;
    f32 R;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x2660);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 1; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0xC, 1);
        g->m1 = func_001F5560(g->unitA, 0x37, 0);
        g->m2 = func_001F5560(g->unitA, 0x26, 0);
        g->m3 = func_001F5560(g->unitA, 0x22, 0);
        g->m4 = func_001F5560(g->unitA, 0x24, 0);
        g->obj.bone[0] = g->m0;
        g->obj.bone[1] = g->m1;
        g->obj.frames[0] = D_01E04A20_b104;
        g->obj.frames[1] = D_01E04A40_b104;
        g->obj.emits = (Emit_b010_01E010E0 *)g->emits;
        g->obj.emit_kind = 0x20;
        g->obj.parts = (Part_b010_01E010E0 *)g->parts;
        g->obj.part_kind = 0x32;
        g->obj.kind = 0;
        g->obj.lo = 0;
        g->obj.x0 = 120.0f;
        g->obj.x1 = 120.0f;
        g->obj.y = 5.0f;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    switch (g->t) {
    case 0x7C:
        func_001F5620(g->unitA, g->m2, &vf);
        func_001F5620(g->unitA, g->m3, &ve);
        func_001F5620(g->unitA, g->m4, &vh);
        vw.x = vf.x - vh.x;
        vw.y = vf.y - vh.y;
        vw.z = vf.z - vh.z;
        func_00101A00(&vw, m);
        vw.x = vf.x - ve.x;
        vw.y = vf.y - ve.y;
        vw.z = vf.z - ve.z;
        r = func_0020D0E0(&vw) - 0.4f;
        R = 5.0f + r;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 18; j++) {
                a = 10.0f * j;
                a = 3.1415927f * a / 180.0f;
                p[0].y = R * func_001A6A88(a);
                p[0].x = R * func_001A6898(a);
                if (i) {
                    p[0].z = -2.0f;
                } else {
                    p[0].z = 2.0f;
                }
                p[1].y = r * func_001A6A88(a);
                p[1].x = r * func_001A6898(a);
                p[1].z = 0.0f;
                func_0020CDD0(&q[0], m, &p[0]);
                func_0020CDD0(&q[1], m, &p[1]);
                func_00101AD0(&g->streak[j + i * 18], 0x10, 0, 0xFF);
                g->streak[j + i * 18].flags = 1;
                g->streak[j + i * 18].b5 = 0;
                g->streak[j + i * 18].width = 80.0f;
                g->streak[j + i * 18].r = 0x80;
                g->streak[j + i * 18].g = 0x40;
                g->streak[j + i * 18].b = 0x20;
                g->streak[j + i * 18].a = 0xC0;
                g->streak[j + i * 18].pos.x = q[1].x + vf.x;
                g->streak[j + i * 18].pos.y = q[1].y + vf.y;
                g->streak[j + i * 18].pos.z = q[1].z + vf.z;
                g->streak[j + i * 18].dir.x = (q[0].x - q[1].x) / 3.5f;
                g->streak[j + i * 18].dir.y = (q[0].y + q[1].y) / 3.5f;
                g->streak[j + i * 18].dir.z = (q[0].z + q[1].z) / 3.5f;
            }
        }
        func_00101AD0(&g->emit, 0x10, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 1.0f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 4.0f;
        g->emit.pos = vf;
        func_00101AD0(&g->flare, 0x14, 0, 0xFF);
        g->flare.b5 = 0;
        g->flare.flags = 0x81;
        g->flare.segs = 9;
        g->flare.radius = 500.0f;
        g->flare.grow = 0.0f;
        g->flare.r = 0xC0;
        g->flare.ib = 0xC0;
        g->flare.ig = 0xC0;
        g->flare.ir = 0xC0;
        g->flare.b = 0x20;
        g->flare.g = 0x20;
        g->flare.alpha = 0x60;
        g->flare.org.z = 0.0f;
        g->flare.org.y = 0.0f;
        g->flare.org.x = 0.0f;
        g->flare.pos = vf;
        for (i = 0; i < 4; i++) {
            func_00101AD0(&g->rib[i], (u8)(((func_0019A5C8() >> 4) & 7) + 0x14), (func_0019A5C8() >> 4) & 3, 0xFF);
            g->rib[i].width = 8.0f + (f32)(i * 3);
            g->rib[i].scale = 0.8f - 0.1f * (f32)i;
            g->rib[i].idx = 0;
            g->rib[i].count = 0x1E;
            g->rib[i].b = 0xC0;
            g->rib[i].g = 0x30;
            g->rib[i].r = 0x10;
            g->rib[i].a = 0xF0;
            g->rib[i].flags = 1;
            g->rib[i].b5 = 0;
            g->rib[i].k = func_0019A5C8() >> 4;
            g->rib[i].pts = g->tbl;
            g->rib[i].pos = vf;
        }
        break;
    case 0xCC:
        return 8;
    }
    if (g->t > 0x71 && g->t < 0x7C) {
        func_001F5620(g->unitA, g->m2, &vf);
        func_001F5620(g->unitA, g->m3, &ve);
        func_001F5620(g->unitA, g->m4, &vh);
        vw.x = vf.x - vh.x;
        vw.y = vf.y - vh.y;
        vw.z = vf.z - vh.z;
        func_00101A00(&vw, m);
        vw.x = vf.x - ve.x;
        vw.y = vf.y - ve.y;
        vw.z = vf.z - ve.z;
        r = 1.0f + func_0020D0E0(&vw);
        a = -20.0f;
        for (j = 0; j < 11; j++) {
            a += 20.0f;
            R = 3.1415927f * a / 180.0f;
            p[0].y = r * func_001A6A88(R);
            p[0].x = r * func_001A6898(R);
            p[0].z = 0.0f;
            func_0020CDD0(&q[0], m, &p[0]);
            if (g->t == 0x72) {
                func_00101AD0(&g->line[j], 0xE, 0, 0xFF);
                g->line[j].flags = 1;
                g->line[j].b5 = 0;
                g->line[j].pool = g->pool;
                g->line[j].slot = 0x5A;
                g->line[j].count = 8;
                g->line[j].width = 8.0f;
                g->line[j].r = 0x80;
                g->line[j].g = 0x40;
                g->line[j].b = 0x20;
                g->line[j].a = 0xC0;
                for (i = 0; i < g->line[j].count + 1; i++) {
                    g->line[j].idx[i] = -1;
                }
            }
            g->line[j].pos[0] = q[0].x + vf.x;
            g->line[j].pos[1] = q[0].y + vf.y;
            g->line[j].pos[2] = q[0].z + vf.z;
        }
    }
    func_01E00080_b104((Obj_b010_01E00080 *)&g->emit);
    func_01E010E0_b104(&g->obj, g->t);
    func_01E00410_b104(g->emits, ot, 0x20);
    func_01E015A0_b104((Rib_b024_01E02120 *)g->rib, ot, 4);
    func_01E02350_b104((Obj_b035_01E00410 *)&g->flare, ot, 1);
    func_01E03470_b104((Line_b104_01E03470 *)g->line, ot, 0xB);
    func_01E02ED0_b104((Streak_b104_01E02ED0 *)g->streak, ot, 0x24);
    switch (g->t) {
    case 0x72:
        return 1;
    case 0x79:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
