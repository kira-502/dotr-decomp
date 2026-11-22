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

static void func_01E00080_b125(Obj_b010_01E00080 *o) {
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
typedef struct W_tbl_func_01E00410_b125 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E00410_b125;

static s32 func_01E00410_b125(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E00410_b125 D_01E05F80_b125;
    W_tbl_func_01E00410_b125 tbl_w = D_01E05F80_b125;
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b042:01E038E0, 339 insns: trail emitters (0x8C bytes each): move, follow a bone, then spawn
   particles (0x58 bytes) along the path from the last three positions (a spline of 4 points, or just the
   last segment when flags & 1). */

typedef struct {
    u8 r, g, b, a;
} Col_b042_01E038E0;

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
    Col_b042_01E038E0 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 f48[0x10];
} Part_b042_01E038E0;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 attached;
    u8 pad6[2];
    Part_b042_01E038E0 *pool;
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
    Col_b042_01E038E0 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
    f32 drift[3];
    u8 pad88[4];
} Emit_b042_01E038E0;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spline_b042_01E038E0;

#pragma optimization_level 2

static s32 func_01E011C0_b125(Emit_b042_01E038E0 *arg0, s32 arg1, s32 n) {
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101AD0();
    extern void func_00101940();
    Emit_b042_01E038E0 *e = arg0;
    Spline_b042_01E038E0 spl;
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
#pragma optimization_level reset

/* shape b125:01E01710 (ShFx_Mgw01), 500 insns, 1 copy (-O2,p): n glow sprites (0x2C-byte emitters): each moves by its
   velocity once 8 frames old, is projected, coloured, sized by its depth (shrunk over its last 16 frames, stretched
   over its first 8), alpha quartered on even frames, flag 0x80 pins it to the far plane, and drawn as one quad (again
   1.15 times larger with flag 1) */

typedef struct {
    f32 x, y, z, w;
} Vec_b125_01E01710;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b125_01E01710;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b125_01E01710 xyz;
} Vtx_b125_01E01710;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b125_01E01710 v[4];
    u8 tail[0x20];
} Pkt_b125_01E01710;

typedef struct {
    s32 id;
    u8 kind;
    u8 b5;
    u8 pad06[2];
    s32 w[6];
} Tex_b125_01E01710;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    f32 size;
    u8 b, g, r, a;
    f32 x, y, z;
    f32 dx, dy, dz;
} Obj_b125_01E01710;

#pragma optimization_level 2

static s32 func_01E01710_b125(Obj_b125_01E01710 *obj, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern void func_001020B0();
    extern void func_00101EE0(void *, void *, s32);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b125_01E01710 *o;
    s32 i;
    s32 h;
    s32 k;
    f32 m[16];
    Vec_b125_01E01710 pos;
    Tex_b125_01E01710 t;
    Pkt_b125_01E01710 pkt;
    Xyz_b125_01E01710 xy;
    f32 d;
    f32 s;
    f32 wx;
    f32 wy;
    f32 ex;
    f32 ey;

    o = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        h = func_00202BF0(5, o->tex);
        if (o->cur > 7) {
            o->x += o->dx;
            o->y += o->dy;
            o->z += o->dz;
        }
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        if (o->b5) {
            func_00101BA0(o, &pos);
        }
        func_0020EB40(m);
        if (func_00205440(&pos, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        ((Pkt_b125_01E01710 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b125_01E01710 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b125_01E01710 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b125_01E01710 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = o->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = o->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = o->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
        if (o->flags & 0x80) {
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
            d = 0.0f;
        } else {
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xy.z;
        }
        t.b5 = o->bB;
        func_001020B0(&t, o->bA, o->b9);
        func_00101EE0(&pkt, &t, h);
        s = func_001018E0(o->size, d);
        k = o->max - o->cur;
        wx = wy = s;
        if (k < 16) {
            wx = wy = s / 16.0f * k;
        }
        if (o->cur < 8) {
            wx = s - s / 8.0f * (8 - o->cur);
            wy = s + s * (8 - o->cur);
        }
        if (o->cur & 1) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->a;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->a >> 2;
        }
        pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - wx);
        pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)((f32)(u32)xy.x + wx);
        pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - wy);
        pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)((f32)(u32)xy.y + wy);
        func_002075F0(&pkt, ot, (u32)d);
        if (o->flags & 1) {
            ex = 1.15f * wx;
            ey = 1.15f * wy;
            t.b5 = 2;
            func_00101EE0(&pkt, &t, h);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - ex);
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)((f32)(u32)xy.x + ex);
            pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - ey);
            pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)((f32)(u32)xy.y + ey);
            func_002075F0(&pkt, ot, (u32)d);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b125:01E01EE0 (ShFx_Mgw02), 842 insns, 1 copy (-O2,p): n magic-wave arcs (0x44-byte emitters): the radius
   shrinks to r0, the angle steps; four arc corners around the joint at angle -/+ spread, projected; a coloured quad
   (alpha ramped by age) with the first texture, then the four edges as white quads of depth-scaled half-width
   with the second texture */

typedef struct {
    f32 x, y, z, w;
} Vec_b125_01E01EE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b125_01E01EE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b125_01E01EE0 xyz;
} Vtx_b125_01E01EE0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b125_01E01EE0 v[4];
    u8 tail[0x20];
} Pkt_b125_01E01EE0;

typedef struct {
    s32 id;
    u8 kind;
    u8 b5;
    u8 pad06[2];
    s32 w[6];
} Tex_b125_01E01EE0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 tex1;
    u8 tex2;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE;
    u8 bF;
    f32 r0;
    f32 w;
    f32 rad;
    f32 step;
    f32 ang;
    f32 dang;
    f32 spread;
    f32 size;
    u8 b, g, r, a;
    u8 b2, g2, r2, a2;
    f32 x, y, z;
} Obj_b125_01E01EE0;

static inline f32 rad_b125_01E01EE0(f32 d) {
    return 3.1415927f * d / 180.0f;
}

#pragma optimization_level 2

static s32 func_01E01EE0_b125(Obj_b125_01E01EE0 *obj, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0();
    extern void func_00101EE0(void *, void *, s32);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    extern void func_002086D0(void *, s32);
    Obj_b125_01E01EE0 *o;
    s32 i;
    s32 h1;
    s32 h2;
    s32 k;
    s32 a;
    s32 b;
    s32 al;
    f32 m[16];
    f32 m2[16];
    Tex_b125_01E01EE0 t;
    Xyz_b125_01E01EE0 xy[4];
    Vec_b125_01E01EE0 pt[4];
    Vec_b125_01E01EE0 pos;
    f32 dep[4];
    f32 sz[4];
    Pkt_b125_01E01EE0 pkt __attribute__((aligned(8)));
    f32 c0;
    f32 s0;
    f32 c1;
    f32 s1;
    f32 ang;

    o = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        h1 = func_00202BF0(5, o->tex1);
        h2 = func_00202BF0(5, o->tex2);
        if (o->rad != o->r0) {
            o->rad -= o->step;
            if (o->rad < o->r0) {
                o->rad = o->r0;
            }
        }
        o->ang += o->dang;
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        if (o->b5) {
            func_00101BA0(o, &pos);
        }
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &pos);
        func_0020BC00(m, m2);
        ang = rad_b125_01E01EE0(o->ang);
        c0 = o->r0 * func_001A6898(ang);
        s0 = o->r0 * func_001A6A88(ang);
        c1 = o->rad * func_001A6898(ang);
        s1 = o->rad * func_001A6A88(ang);
        ang = rad_b125_01E01EE0(o->ang - o->spread);
        pt[0].x = c1 - c0 + o->w * func_001A6898(ang);
        pt[0].y = 0.0f;
        pt[0].z = s1 - s0 + o->w * func_001A6A88(ang);
        pt[2].x = c1 - c0 + o->r0 * func_001A6898(ang);
        pt[2].y = 0.0f;
        pt[2].z = s1 - s0 + o->r0 * func_001A6A88(ang);
        ang = rad_b125_01E01EE0(o->ang + o->spread);
        pt[1].x = c1 - c0 + o->w * func_001A6898(ang);
        pt[1].y = 0.0f;
        pt[1].z = s1 - s0 + o->w * func_001A6A88(ang);
        pt[3].x = c1 - c0 + o->r0 * func_001A6898(ang);
        pt[3].y = 0.0f;
        pt[3].z = s1 - s0 + o->r0 * func_001A6A88(ang);
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = o->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = o->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = o->b;
        k = o->max - o->cur;
        pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->a;
        if (k < 32) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = k * (o->a >> 5);
        }
        if (o->cur < 8) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->cur * (o->a >> 3);
        }
        if (func_00205440(&pt[0], m, &xy[0], &dep[0]) == 0) {
            continue;
        }
        if (func_00205440(&pt[1], m, &xy[1], &dep[1]) == 0) {
            continue;
        }
        if (func_00205440(&pt[2], m, &xy[2], &dep[2]) == 0) {
            continue;
        }
        if (func_00205440(&pt[3], m, &xy[3], &dep[3]) == 0) {
            continue;
        }
        pkt.v[0].xyz = xy[0];
        pkt.v[1].xyz = xy[1];
        pkt.v[2].xyz = xy[2];
        pkt.v[3].xyz = xy[3];
        pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
        t.b5 = o->bE;
        func_001020B0(&t, o->bC, o->bA);
        func_00101EE0(&pkt, &t, h1);
        func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b125_01E01EE0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = 0x80;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = 0x80;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = 0x80;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        al = o->a2;
        if (k < 32) {
            al = k * (o->a2 >> 5);
        }
        if (o->cur < 8) {
            al = o->cur * (o->a2 >> 3);
        }
        if ((o->cur & 1) && (o->flags & 1)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = al >> 2;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = al;
        }
        pkt.v[0].xyz.f = pkt.v[2].xyz.f = pkt.v[1].xyz.f = pkt.v[3].xyz.f = 1;
        t.b5 = o->bF;
        func_001020B0(&t, o->bD, o->bB);
        t.w[0] += 0xC;
        t.w[1] = t.w[0] + 8;
        func_00101EE0(&pkt, &t, h2);
        for (k = 0; k < 4; k++) {
            switch (k) {
            case 0:
                a = 0;
                b = 1;
                break;
            case 1:
                a = 1;
                b = 3;
                break;
            case 2:
                a = 3;
                b = 2;
                break;
            case 3:
                a = 2;
                b = 0;
                break;
            }
            sz[a] = func_001018E0(o->size, dep[a]);
            sz[b] = func_001018E0(o->size, dep[b]);
            pkt.v[2].xyz.y = (u32)((f32)(u32)xy[a].y + sz[a]);
            pkt.v[3].xyz.y = (u32)((f32)(u32)xy[b].y + sz[b]);
            pkt.v[0].xyz.y = (u32)((f32)(u32)xy[a].y - sz[a]);
            pkt.v[1].xyz.y = (u32)((f32)(u32)xy[b].y - sz[b]);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[a].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[b].x;
            func_002075F0(&pkt, ot, (u32)((f32)(u32)(dep[a] + dep[b]) / 2.0f));
            pkt.v[2].xyz.x = (u32)((f32)(u32)xy[a].x + sz[a]);
            pkt.v[3].xyz.x = (u32)((f32)(u32)xy[b].x + sz[b]);
            pkt.v[0].xyz.x = (u32)((f32)(u32)xy[a].x - sz[a]);
            pkt.v[1].xyz.x = (u32)((f32)(u32)xy[b].x - sz[b]);
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[a].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[b].y;
            func_002075F0(&pkt, ot, (u32)((f32)(u32)(dep[a] + dep[b]) / 2.0f));
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b033:01E03590, 674 insns: update and draw a pool of jittering particles (0x3C bytes each): move, every
   (mask+1) ticks re-follow the owner and pick a new random offset, frame from the tick (fade-in frames while
   young), project, then one textured sprite whose corners (rounded) follow the flip bits */

typedef struct Part_b033_01E03590 {
    u8 age;
    u8 b1;
    u8 life;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    s32 range;
    f32 pos[3];
    f32 vel[3];
    f32 off[3];
} Part_b033_01E03590;

typedef struct Xyz_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b033_01E03590;

typedef struct Pk_b033_01E03590 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b033_01E03590 v[4];
    u64 pad60[3];
} Pk_b033_01E03590;

typedef struct Buf_b033_01E03590 {
    u64 tag;
    Pk_b033_01E03590 pk;
} Buf_b033_01E03590;

typedef struct Uvs_b033_01E03590 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b033_01E03590;

typedef struct Scr_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b033_01E03590;

static inline void b033_01E03590_tag(Pk_b033_01E03590 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E02C10_b125(Part_b033_01E03590 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b033_01E03590 *p = arg0;
    s32 i;
    s32 tex;
    s32 tick;
    s32 frame;
    s32 r;
    f32 half;
    u32 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b033_01E03590 uvs;
    Pk_b033_01E03590 pk __attribute__((aligned(8)));
    Scr_b033_01E03590 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        tick = p->mask & (p->life - p->age);
        if (tick == 0 || p->life - 1 == p->age) {
            if (p->follow != 0) {
                func_00101BA0(p, &tmp);
                p->pos[0] = tmp.x;
                p->pos[1] = tmp.y;
                p->pos[2] = tmp.z;
            }
            r = p->range;
            p->off[0] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[1] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[2] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
        }
        pos.x = p->pos[0] + p->off[0];
        pos.y = p->pos[1] + p->off[1];
        pos.z = p->pos[2] + p->off[2];
        func_0020EB40(m);
        ((Pk_b033_01E03590 *)(u32)&pk)->flags = 0x24;
        ((Pk_b033_01E03590 *)(u32)&pk)->size = 9;
        ((Pk_b033_01E03590 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b033_01E03590 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        frame = tick & 7;
        if (p->age < 4) {
            frame = 7 - p->age;
        }
        if ((p->flags & 1) && frame == 0) {
            p->flags = (p->flags & 0xC7) | (((func_0019A5C8() >> 4) & 3) << 4);
        }
        uvs.b5 = p->bA;
        func_001020B0(&uvs, frame, 0);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
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
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
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
        func_002075F0((s32)&pk, id, 0);
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

static s32 func_01E036A0_b125(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E05FE0_b125;
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
    t = D_01E05FE0_b125;
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

/* shape b125:01E04220 (ShFx_RiseCore), 430 insns, 1 copy (-O2,p): draws n rising-core streaks (0x3C-byte emitters):
   re-seeds the x/z jitter each cycle, projects a low and a high end (rise/rise2 times the masked age), each end sized
   by its depth, alpha from flag 0x40, flag 0x80 pins it to the far plane */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b125_01E04220;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b125_01E04220;

typedef struct {
    u64 st;
    Xyz_b125_01E04220 xyz;
} Vtx_b125_01E04220;

typedef struct {
    Hdr_b125_01E04220 h;
    u8 r, g, b, a;
    f32 q;
    Vtx_b125_01E04220 v[4];
    u8 tail[0x20];
} Pkt_b125_01E04220;

typedef struct {
    f32 x, y, z, w;
} V4_b125_01E04220;

typedef struct {
    s32 id;
    u8 kind;
    u8 b5;
    u8 pad06[2];
    s32 w[4];
} Tex_b125_01E04220;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 mask;
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    s32 range;
    s32 drange;
    f32 size;
    f32 rise;
    f32 rise2;
    u8 c20, c21, c22, c23;
    f32 x, y, z;
    f32 dx;
    s32 w34;
    f32 dz;
} Obj_b125_01E04220;

#pragma optimization_level 2

static s32 func_01E04220_b125(Obj_b125_01E04220 *obj, s32 ot, s32 n) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_0019A5C8(void);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_001020B0();
    extern void func_00101D20(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b125_01E04220 *o;
    s32 i;
    s32 h;
    s32 k;
    s32 d;
    f32 m[16];
    V4_b125_01E04220 v[2];
    V4_b125_01E04220 pos;
    Xyz_b125_01E04220 scr[2];
    Tex_b125_01E04220 t;
    Pkt_b125_01E04220 p;
    f32 depth[2];
    f32 q;
    f32 s0;
    f32 s1;

    o = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        h = func_00202BF0(5, o->tex);
        o->range += o->drange;
        k = o->mask & (o->max - o->cur);
        if (k == 0 || o->max - 1 == o->cur) {
            if (o->b5) {
                func_00101BA0(o, &pos);
                o->x = pos.x;
                o->y = pos.y;
                o->z = pos.z;
            }
            o->dx = (f32)((func_0019A5C8() >> 4) % o->range - (o->range >> 1)) / 100.0f;
            o->w34 = 0;
            o->dz = (f32)((func_0019A5C8() >> 4) % o->range - (o->range >> 1)) / 100.0f;
        }
        v[0].x = v[1].x = o->x + o->dx;
        v[0].z = v[1].z = o->z + o->dz;
        v[0].y = o->y + (f32)k * o->rise;
        v[1].y = o->y + (f32)k * o->rise2;
        func_0020EB40(m);
        ((Hdr_b125_01E04220 *)(s32)&p)->count = 0x24;
        ((Hdr_b125_01E04220 *)(s32)&p)->tag = 9;
        ((Hdr_b125_01E04220 *)(s32)&p)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b125_01E04220 *)(s32)&p)->pad = 0;
        p.r = o->c22;
        p.g = o->c21;
        p.b = o->c20;
        p.q = 1.0f;
        t.b5 = o->bA;
        func_001020B0(&t, o->b9, 0);
        func_00101D20(&p, &t, h);
        p.a = o->c23;
        if (!(o->flags & 0x40)) {
            if (o->cur < 8) {
                p.a = (o->c23 >> 3) * o->cur;
            } else {
                d = o->mask - k;
                if (d < 8) {
                    p.a = (o->c23 >> 3) * d;
                }
            }
        }
        if (func_00205440(&v[0], m, &scr[0], &depth[0]) == 0 || func_00101600(&scr[0]) == 0) {
            continue;
        }
        if (func_00205440(&v[1], m, &scr[1], &depth[1]) == 0 || func_00101600(&scr[1]) == 0) {
            continue;
        }
        s0 = func_001018E0(o->size, depth[0]);
        s1 = func_001018E0(o->size, depth[1]);
        if (o->flags & 0x80) {
            p.v[0].xyz.z = p.v[1].xyz.z = p.v[2].xyz.z = p.v[3].xyz.z = 0xFFFFFE;
            q = 0.0f;
        } else {
            p.v[0].xyz.z = p.v[1].xyz.z = scr[1].z;
            p.v[2].xyz.z = p.v[3].xyz.z = scr[0].z;
            q = (depth[0] + depth[1]) / 2.0f;
        }
        p.v[0].xyz.x = (u32)(scr[1].x - s1);
        p.v[1].xyz.x = (u32)(scr[1].x + s1);
        p.v[2].xyz.x = (u32)(scr[0].x - s0);
        p.v[3].xyz.x = (u32)(scr[0].x + s0);
        p.v[0].xyz.y = p.v[1].xyz.y = scr[1].y;
        p.v[2].xyz.y = p.v[3].xyz.y = scr[0].y;
        func_002075F0(&p, ot, (u32)q);
    }
    return 1;
}

#pragma optimization_level reset

/* shape b125:01E048E0 (ShFx_Afx07), 552 insns, 1 copy (-O2,p): b172:01E020F0 (ShFx_Afx07) at -O2: n arc emitters
   (0x34 bytes each), grow the radius and spin, project the two ends of an angular span and draw a textured band down
   to a fixed baseline */

typedef struct {
    f32 x, y, z, w;
} Vec_b125_01E048E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b125_01E048E0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b125_01E048E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b125_01E048E0 uv;
    Xyz_b125_01E048E0 xyz;
} Vtx_b125_01E048E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b125_01E048E0 v[4];
    u8 tail[0x20];
} Pkt_b125_01E048E0;

typedef struct {
    u8 life;
    u8 pad01[4];
    u8 follow;
    u8 pad06[2];
    u8 lift;
    u8 blend;
    u8 pad0A[2];
    f32 rad;
    f32 grow;
    f32 ang;
    f32 spin;
    f32 span;
    u8 b1, g1, r1, a1;
    u8 b0, g0, r0, a0;
    f32 x, y, z;
} Afx_b125_01E048E0;

static inline f32 rad_b125_01E048E0(f32 d) {
    return 3.1415927f * d / 180.0f;
}

#pragma optimization_level 2

static s32 func_01E048E0_b125(Afx_b125_01E048E0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002087A0(void *, s32);
    extern void func_00101C80(void *, u8 *);
    extern void func_002086D0(void *, u64);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    f32 mat2[16];
    u8 td[0x20];
    Xyz_b125_01E048E0 xy[2];
    Vec_b125_01E048E0 p[2];
    Vec_b125_01E048E0 pos;
    Pkt_b125_01E048E0 pkt;
    f32 depth[3];
    u8 bl[4];
    Afx_b125_01E048E0 *e;
    s32 i;
    f32 a;
    f32 b;
    f32 a2;
    f32 b2;
    f32 h;
    s32 k;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->rad += e->grow;
        e->ang += e->spin;
        pos.x = e->x;
        pos.y = e->y;
        pos.z = e->z;
        if (e->follow) {
            func_00101BA0(e, &pos);
        }
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, NULL, &pos);
        func_0020BC00(mat, mat2);
        a = rad_b125_01E048E0(e->ang);
        p[0].x = e->rad * func_001A6898(a);
        p[0].y = 0.0f;
        p[0].z = e->rad * func_001A6A88(a);
        a = rad_b125_01E048E0(e->ang + e->span);
        p[1].x = e->rad * func_001A6898(a);
        p[1].y = 0.0f;
        p[1].z = e->rad * func_001A6A88(a);
        if (func_00205440(&p[0], mat, &xy[0], &depth[0]) == 0) {
            continue;
        }
        if (func_00205440(&p[1], mat, &xy[1], &depth[1]) == 0) {
            continue;
        }
        if (xy[1].x > xy[0].x) {
            continue;
        }
        if (xy[0].y >= 36352.0f) {
            xy[0].y = 0x8E00;
        }
        if (xy[1].y >= 36352.0f) {
            xy[1].y = 0x8E00;
        }
        ((Pkt_b125_01E048E0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b125_01E048E0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b125_01E048E0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b125_01E048E0 *)(s32)&pkt)->pad = 0;
        func_002087A0(&pkt, 1);
        pkt.v[0].r = pkt.v[1].r = e->r0;
        pkt.v[2].r = pkt.v[3].r = e->r1;
        pkt.v[0].g = pkt.v[1].g = e->g0;
        pkt.v[2].g = pkt.v[3].g = e->g1;
        pkt.v[0].b = pkt.v[1].b = e->b0;
        pkt.v[2].b = pkt.v[3].b = e->b1;
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = (e->a0 >> 3) * e->life;
            pkt.v[2].a = pkt.v[3].a = (e->a1 >> 3) * e->life;
        } else {
            pkt.v[0].a = pkt.v[1].a = e->a0;
            pkt.v[2].a = pkt.v[3].a = e->a1;
        }
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
        td[5] = e->blend;
        func_00101C80(td, bl);
        func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        ((Pkt_b125_01E048E0 *)(s32)&pkt)->count |= 0x800;
        a = xy[0].x - 27648.0f;
        b = xy[1].x - 27648.0f;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[0].uv)->u = (u32)a;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[0].uv)->v = 0;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[1].uv)->u = (u32)b;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[1].uv)->v = 0;
        a2 = xy[0].y - 29184.0f;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[2].uv)->u = (u32)a;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[2].uv)->v = (u32)a2;
        a2 = xy[1].y - 29184.0f;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[3].uv)->u = (u32)b;
        ((Uv_b125_01E048E0 *)(s32)&pkt.v[3].uv)->v = (u32)a2;
        k = e->lift + (e->life & 3);
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[1].z;
        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[1].x;
        h = 29184.0f - (k << 4);
        pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)h;
        pkt.v[2].xyz.y = xy[0].y;
        pkt.v[3].xyz.y = xy[1].y;
        func_002075F0(&pkt, ot, (u32)((u32)(depth[0] + depth[1]) / 2.0f));
    }
    return 1;
}

#pragma optimization_level reset

/* shape b125:01E05180 (b125), 870 insns, 1 copy (-O2,p): b125 scene manager (-O2), b568:01E038C0's form: code >= 0
   clears the 0x3E80 scene, takes both units, the camera, joints 0x2F/0x41 and the table; else counts the frame: 38
   the ActMptc trail, 60 30 Mgw01 glows at joint 0x41, 142 two rings of 32 Mgw02 waves, 196 50 rising cores and 36
   Afx07 arcs; 196-219 spins the waves; steps every effect, each Mgw01 at state 7 spawns 6 sparks and a flare; 340
   returns 8; 6 from 212 to 296, 1 at 202, 2 at 297 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_b125_01E05180;

typedef struct {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b125_01E05180;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    void *rib;
    void *tbl;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 pad15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 pad24[4];
    u8 c[4];
    u8 pad2C[0x60];
} Act_b125_01E05180;

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
    f32 fC;
    u8 c[4];
    V3_b125_01E05180 pos;
    f32 f20;
    f32 f24;
    f32 f28;
} Gw1_b125_01E05180;

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
    u8 bD;
    u8 bE;
    u8 bF;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    u8 c[4];
    u8 b34;
    u8 b35;
    u8 b36;
    u8 b37;
    f32 x;
    f32 y;
    f32 z;
} Gw2_b125_01E05180;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 c[4];
    f32 f10;
    s32 n14;
    V3_b125_01E05180 pos;
    u8 pad24[4];
    f32 f28;
    u8 pad2C[0x10];
} Part_b125_01E05180;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    s32 nC;
    s32 n10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad30[0xC];
} Rise_b125_01E05180;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 c[4];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 x;
    f32 y;
    f32 z;
    u8 pad28[0x24];
} Flear_b125_01E05180;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA[2];
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c[4];
    u8 d[4];
    f32 x;
    f32 y;
    f32 z;
} Afx_b125_01E05180;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    u8 pad14[0x18];
    Cam_b125_01E05180 cam;
    u8 mv[0x60];
    u8 rib[30][0x58];
    Act_b125_01E05180 act;
    Gw1_b125_01E05180 gw1[30];
    Gw2_b125_01E05180 gw2[64];
    Part_b125_01E05180 part[30];
    Rise_b125_01E05180 rise[50];
    Flear_b125_01E05180 flear[6];
    Afx_b125_01E05180 afx[36];
    s8 tbl[0x100];
    u8 pad3E7C[4];
} Scene_b125_01E05180;

#pragma optimization_level 2

static s32 func_01E05180_b125(Scene_b125_01E05180 *g, s32 code) {
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
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_01E00080_b125();
    extern s32 func_01E00410_b125();
    extern s32 func_01E011C0_b125();
    extern s32 func_01E01710_b125();
    extern s32 func_01E01EE0_b125();
    extern s32 func_01E02C10_b125();
    extern s32 func_01E036A0_b125();
    extern s32 func_01E04220_b125();
    extern s32 func_01E048E0_b125();
    s32 ot = func_00207500();
    Vec4f v;
    Vec4f b;
    s32 i;
    s32 k;
    s32 j;
    s32 r;
    s32 d;
    u16 t;

    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x3E80);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0x2F, 1);
        g->m1 = func_001F5560(g->unitA, 0x41, 0);
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x26:
        func_00101AD0(&g->act, 0x10, 0, 0xFF);
        g->act.b4 = 7;
        g->act.b5 = 1;
        g->act.b6 = g->m0;
        g->act.b13 = 1;
        g->act.b14 = 3;
        g->act.b16 = 2;
        g->act.rib = g->rib;
        g->act.b10 = 0x1E;
        g->act.b12 = 5;
        g->act.b11 = 0x1C;
        g->act.f18 = 0.1f;
        g->act.f1C = 0.1f;
        g->act.f20 = 10.0f;
        g->act.tbl = g->tbl;
        g->act.c[2] = 0x60;
        g->act.c[1] = 0xC0;
        g->act.c[0] = 0x60;
        g->act.c[3] = 0x80;
        break;
    case 0x3C:
        func_001F5620(g->unitA, g->m1, &b);
        for (i = 0; i < 0x1E; i++) {
            k = func_00101C30(g->gw1, 0x2C, 0x1E);
            if (k >= 0) {
                func_00101AD0(&g->gw1[k], (u8)((func_0019A5C8() & 3) + 0x1C), (u8)(i * 4), 0xFF);
                g->gw1[k].b4 = 1;
                g->gw1[k].b5 = 0;
                g->gw1[k].b8 = 0;
                g->gw1[k].b9 = 1;
                g->gw1[k].bA = i & 7;
                g->gw1[k].bB = 2;
                g->gw1[k].fC = 60.0f + (f32)((func_0019A5C8() >> 4) % 300 - 150) / 100.0f;
                g->gw1[k].c[2] = g->gw1[k].c[1] = g->gw1[k].c[0] = g->gw1[k].c[3] = 0xC0;
                g->gw1[k].pos.x = b.x;
                g->gw1[k].pos.y = b.y;
                g->gw1[k].pos.z = b.z;
                g->gw1[k].f20 = (f32)((func_0019A5C8() >> 4) % 50 - 25) / 100.0f;
                g->gw1[k].f24 = (f32)((func_0019A5C8() >> 4) % 50 - 25) / 100.0f;
                if (g->cam.dir == 0x8000) {
                    g->gw1[k].f28 = -0.7f;
                } else {
                    g->gw1[k].f28 = 0.7f;
                }
                g->gw1[k].f28 += (f32)((func_0019A5C8() >> 4) % 30 - 15) / 100.0f;
            }
        }
        break;
    case 0x8E:
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 0x20; i++) {
                k = func_00101C30(g->gw2, 0x44, 0x40);
                if (k >= 0) {
                    g->gw2[k].b4 = 0;
                    g->gw2[k].b5 = 0;
                    g->gw2[k].b8 = 0;
                    g->gw2[k].bA = 1;
                    g->gw2[k].bC = (i + j * 5) & 7;
                    g->gw2[k].bE = 2;
                    g->gw2[k].b9 = 1;
                    g->gw2[k].bB = 0;
                    g->gw2[k].bD = 3;
                    g->gw2[k].bF = 2;
                    r = func_0019A5C8() & 0xF;
                    switch (j) {
                    case 0:
                        func_00101AD0(&g->gw2[k], (u8)(0xBC - r), (u8)r, 0xFF);
                        g->gw2[k].f10 = 18.0f;
                        g->gw2[k].f14 = 28.0f;
                        g->gw2[k].f18 = 40.0f;
                        g->gw2[k].f1C = 1.0f;
                        g->gw2[k].f20 = g->gw2[k].f24 * (f32)r + 11.25f * (f32)i;
                        break;
                    case 1:
                        func_00101AD0(&g->gw2[k], (u8)(0xB4 - r), (u8)(r + 8), 0xFF);
                        g->gw2[k].f10 = 28.0f;
                        g->gw2[k].f14 = 38.0f;
                        g->gw2[k].f18 = 80.0f;
                        g->gw2[k].f1C = 1.8f;
                        g->gw2[k].f20 = g->gw2[k].f24 * (f32)(r + 8) + 11.25f * (f32)i;
                        break;
                    }
                    g->gw2[k].f28 = 5.625f;
                    g->gw2[k].f2C = 15.0f;
                    g->gw2[k].c[2] = g->gw2[k].c[1] = g->gw2[k].c[0] = g->gw2[k].c[3] = 0xF0;
                    g->gw2[k].b36 = 0x10;
                    g->gw2[k].b34 = g->gw2[k].b35 = 0x80;
                    g->gw2[k].b37 = 0x20;
                    func_001F53C0(1, g->unitB, &b);
                    g->gw2[k].x = b.x;
                    g->gw2[k].y = b.y - 18.0f;
                    g->gw2[k].z = b.z;
                }
            }
        }
        break;
    case 0xC4:
        func_001F53C0(1, g->unitB, &b);
        for (i = 0; i < 0x32; i++) {
            k = func_00101C30(g->rise, 0x3C, 0x32);
            if (k >= 0) {
                func_00101AD0(&g->rise[k], 0x78, func_0019A5C8() & 0xF, 0xF);
                g->rise[k].b4 = 0;
                g->rise[k].b5 = 0;
                g->rise[k].b8 = 1;
                g->rise[k].b9 = 3;
                g->rise[k].bA = 2;
                g->rise[k].nC = 3000;
                g->rise[k].n10 = 0xF;
                g->rise[k].f18 = 0.1f;
                g->rise[k].f1C = 6.0f;
                g->rise[k].c[2] = g->rise[k].c[1] = g->rise[k].c[0] = g->rise[k].c[3] = 0x80;
                g->rise[k].f14 = 60.0f;
                g->rise[k].x = b.x;
                g->rise[k].y = b.y - 19.0f;
                g->rise[k].z = b.z;
            }
        }
        for (k = 0; k < 0x24; k++) {
            func_00101AD0(&g->afx[k], 0x72, 0x18, 0xFF);
            g->afx[k].b4 = 0;
            g->afx[k].b5 = 0;
            g->afx[k].b8 = 0xC;
            g->afx[k].b9 = 2;
            g->afx[k].fC = 18.0f;
            g->afx[k].f10 = 0.18f;
            g->afx[k].f14 = 10.0f * k;
            g->afx[k].f18 = 0.0f;
            g->afx[k].f1C = 10.0f;
            g->afx[k].d[0] = 0x80;
            g->afx[k].d[1] = 0x80;
            g->afx[k].d[2] = 0x80;
            g->afx[k].d[3] = 0x40;
            g->afx[k].c[2] = g->afx[k].c[1] = g->afx[k].c[0] = g->afx[k].c[3] = 0x80;
            g->afx[k].x = b.x;
            g->afx[k].z = b.z;
            g->afx[k].y = b.y - 18.0f;
        }
        break;
    case 0x154:
        return 8;
    }
    t = g->t;
    if (t >= 0xC4 && t < 0xDC) {
        d = t - 0xC4;
        for (i = 0; i < 0x40; i++) {
            if (g->gw2[i].f10 == 18.0f) {
                g->gw2[i].f24 = 0.2f * (f32)d;
            } else {
                g->gw2[i].f24 = 0.2f * (f32)-d;
            }
            g->gw2[i].b37 += 3;
            g->gw2[i].f2C += 6.0f;
        }
    }
    func_01E00080_b125(g->mv);
    func_01E011C0_b125(&g->act, ot, 1);
    func_01E00410_b125(g->rib, ot, 0x1E);
    func_01E01710_b125(g->gw1, ot, 0x1E);
    func_01E01EE0_b125(g->gw2, ot, 0x40);
    func_01E04220_b125(g->rise, ot, 0x32);
    func_01E048E0_b125(g->afx, ot, 0x24);
    for (i = 0; i < 0x1E; i++) {
        if (g->gw1[i].b0 == 7) {
            for (j = 0; j < 6; j++) {
                k = func_00101C30(g->part, 0x3C, 0x1E);
                if (k >= 0) {
                    func_00101AD0(&g->part[k], 0x10, func_0019A5C8() & 3, 7);
                    g->part[k].b5 = 0;
                    g->part[k].b4 = 0;
                    g->part[k].b8 = 1;
                    g->part[k].b9 = 3;
                    g->part[k].bA = 2;
                    g->part[k].bB = 0;
                    g->part[k].c[2] = g->part[k].c[1] = g->part[k].c[0] = g->part[k].c[3] = 0x80;
                    g->part[k].f10 = 25.0f;
                    g->part[k].n14 = 0xD2;
                    g->part[k].pos = g->gw1[i].pos;
                    if (j & 1) {
                        g->part[k].f28 = 0.3f;
                    } else {
                        g->part[k].f28 = -0.3f;
                    }
                    g->part[k].f28 += (f32)((func_0019A5C8() >> 4) % 30 - 15) / 100.0f;
                }
            }
            k = func_00101C30(g->flear, 0x4C, 6);
            if (k >= 0) {
                func_00101AD0(&g->flear[k], 8, 0, 0xFF);
                g->flear[k].b5 = 0;
                g->flear[k].b4 = 0x80;
                g->flear[k].b7 = 9;
                g->flear[k].bA = 0x10;
                g->flear[k].b9 = 0x80;
                g->flear[k].b8 = 0x80;
                g->flear[k].bB = 0x10;
                g->flear[k].c[2] = g->flear[k].c[1] = g->flear[k].c[0] = g->flear[k].c[3] = 0xFF;
                g->flear[k].f10 = 100.0f;
                g->flear[k].f14 = 20.0f;
                g->flear[k].f18 = 3.0f;
                g->flear[k].x = g->gw1[i].pos.x;
                g->flear[k].y = g->gw1[i].pos.y;
                g->flear[k].z = g->gw1[i].pos.z;
            }
        }
    }
    func_01E02C10_b125(g->part, ot, 0x1E);
    func_01E036A0_b125(g->flear, ot, 6);
    t = g->t;
    if (t >= 0xD4 && t < 0x129) {
        return 6;
    }
    switch (t) {
    case 0xCA:
        return 1;
    case 0x129:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
