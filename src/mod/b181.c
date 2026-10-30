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

static void func_01E00080_b181(Obj_b002_01E00080 *arg0) {
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

#define ABS_b011_01E04380(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b011_01E04380;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E04380;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b011_01E04380 p;
} Vtx_b011_01E04380;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b011_01E04380 v[4];
    u8 tail[0x20];
} Pkt_b011_01E04380;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b011_01E04380;

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
    Vec_b011_01E04380 pos;
    Vec_b011_01E04380 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b011_01E04380;

extern Tex_b011_01E04380 D_01E03E80_b181;

#pragma optimization_level 1

static s32 func_01E00440_b181(Ray_b011_01E04380 *obj, s32 target, s32 count) {
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
    Ray_b011_01E04380 *o;
    s32 i;
    s32 j;
    u8 idx;
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
    Xyz_b011_01E04380 xy[2];
    Vec_b011_01E04380 pt;
    Vec_b011_01E04380 d;
    Vec_b011_01E04380 tmp;
    Tex_b011_01E04380 tex0;
    Tex_b011_01E04380 tex;
    Pkt_b011_01E04380 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E03E80_b181;
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
        ((Pkt_b011_01E04380 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->pad = 0;
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
            if (ABS_b011_01E04380(xy[1].x - xy[0].x) > ABS_b011_01E04380(xy[1].y - xy[0].y)) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b181", func_01E01170_b181);

/* OVL_WARM */

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b059:01E00E10, 941 insns, 11 copies: b024:01E02120 at -O1 (angle inline, step = 17.0f local, ABS macro): update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b059_01E00E10 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b059_01E00E10;

typedef struct Rib_b059_01E00E10 {
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
} Rib_b059_01E00E10;

typedef struct Xyz_b059_01E00E10 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b059_01E00E10;

typedef struct Pk_b059_01E00E10 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b059_01E00E10 v[4];
    u64 pad60[3];
} Pk_b059_01E00E10;

static inline void b059_01E00E10_tag(Pk_b059_01E00E10 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 1
typedef struct W_tbl_func_01E01E90_b181 {
    Uvs_b059_01E00E10 v[4];
} W_tbl_func_01E01E90_b181;

static s32 func_01E01E90_b181(Rib_b059_01E00E10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 step;
    f32 b;
    Rib_b059_01E00E10 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    s32 tex;
    u8 k;
    f32 w;
    f32 d;
    f32 a;
    f32 h0;
    s32 life;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E01E90_b181 D_01E03EC0_b181;
    W_tbl_func_01E01E90_b181 tbl_w = D_01E03EC0_b181;
    Uvs_b059_01E00E10 uvs;
    Pk_b059_01E00E10 pk;
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
        step = 17.0f;
        ang = 0.0f;
        life = p->life - p->age;
        b059_01E00E10_tag((Pk_b059_01E00E10 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
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
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                v.x = a * b * func_001A6898(3.1415927f * ang / 180.0f);
                v.z = a * b * func_001A6A88(3.1415927f * ang / 180.0f);
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
                dy = ABS(pk.v[2].y - pk.v[0].y);
                dx = ABS(pk.v[2].x - pk.v[0].x);
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b181:01E02D50, 346 insns (b198:01E05C30 at -O1): moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b181_01E02D50;

typedef struct {
    u8 r, g, b, a;
} C4_b181_01E02D50;

typedef struct {
    u8 pad00[4];
    u8 flags;
    u8 b5;
    u8 pad06[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 pad0E[2];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    C4_b181_01E02D50 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b181_01E02D50;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b181_01E02D50 *list;
    s32 w0C;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    C4_b181_01E02D50 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
} Trail_b181_01E02D50;

#pragma optimization_level 1

static s32 func_01E02D50_b181(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    Spline_b181_01E02D50 sp;
    Vec4f tmp;
    Trail_b181_01E02D50 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b181_01E02D50 *)((u8 *)e + 0x7C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        if (e->follow != 0) {
            e->pos.x += e->off.x;
            e->pos.y += e->off.y;
            e->pos.z += e->off.z;
        }
        if (e->flags & 1) {
            sp.out[0] = e->pos;
            sp.out[1] = e->prev;
            cnt = 1;
        } else {
            sp.n = 3;
            sp.x[0] = e->pos.x;
            sp.y[0] = e->pos.y;
            sp.z[0] = e->pos.z;
            sp.x[1] = e->prev.x;
            sp.y[1] = e->prev.y;
            sp.z[1] = e->prev.z;
            sp.x[2] = e->prev2.x;
            sp.y[2] = e->prev2.y;
            sp.z[2] = e->prev2.z;
            func_00102550(&sp);
            cnt = 4;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x58, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                e->list[idx].f14 = e->f18;
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 5;
                if (e->flags & 2) {
                    e->list[idx].flags |= 8;
                }
                e->list[idx].bC = e->b16;
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f20;
                e->list[idx].f20 = e->f24;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b13;
                e->list[idx].bB = e->b14;
                e->list[idx].bD = e->b15;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].pos = sp.out[k];
                func_00101940(&tmp, e->list[idx].x48);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b061:01E03440, 346 insns, 11 copies: b010:01E05740 rewritten for an -O1,p file (no mode/w temps, c = 32768.0f, one long 0xFF chain, local copy of the object pointer): full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b061_01E03440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b061_01E03440;

typedef struct {
    Hdr_b061_01E03440 h;
    Vtx_b061_01E03440 v[4];
    u8 tail[8];
} Pkt_b061_01E03440;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b061_01E03440;

#pragma optimization_level 1

static s32 func_01E032C0_b181(Obj_b061_01E03440 *arg0, s32 tex) {
    Obj_b061_01E03440 *o = arg0;
    Pkt_b061_01E03440 p __attribute__((aligned(8)));
    u8 a;
    s32 d;
    f32 s;
    f32 c;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b061_01E03440 *)(s32)&p)->count = 0x14;
    ((Hdr_b061_01E03440 *)(s32)&p)->tag = 8;
    ((Hdr_b061_01E03440 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b061_01E03440 *)(s32)&p)->pad = 0;
    switch (o->flags & 7) {
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
    if (o->cur == 1 && (o->flags & 0x80)) {
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
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g =
        p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        s = 7168.0f / (o->max >> 1);
        c = 32768.0f;
        d = o->max - o->cur;
        a = (0x80 / (o->max >> 1)) * (d >> 1);
        if ((o->max >> 1) < d) {
            p.v[0].a = p.v[1].a = a;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = func_001A23B0(c - s * d);
        p.v[2].y = p.v[3].y = func_001A23B0(c);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(c);
        p.v[2].y = p.v[3].y = func_001A23B0(c + s * d);
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

/* shape b181:01E03830 (b181), 380 insns, 1 copy (-O1,p): b181 scene manager: setup clears the scene, takes both
   units, a model and texture pages, fills the 256-entry table; then a frame timer arms the trail at frame 39 and the
   glow, fade, ray and emitter at frame 51, steps all six effects, plays the first camera cue whose frame range holds
   the timer, and returns 8 / 6 / 1 / 2 at frames 105 / 51..71 / 41 / 72 */

typedef struct {
    f32 x, y, z, w;
} V4_b181_01E03830;

typedef struct {
    u16 start;
    u16 end;
    u8 motion;
    u8 flags;
    u8 rate;
    u8 pad7;
    s32 w8;
    u8 c0[4];
    u8 c1[4];
} Cue_b181_01E03830;

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
} Emit_b181_01E03830;

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
    u8 c[4];
    f32 f10;
    f32 f14;
    f32 f18;
    V4_b181_01E03830 pos;
    u8 pad2C[0x10];
    s32 w3C;
    s32 w40;
    s32 w44;
    u8 pad48[4];
} Glow_b181_01E03830;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 model;
    u8 pad10[0x1C];
    u8 cam[0x14];
    Emit_b181_01E03830 emit;
    Glow_b181_01E03830 glow;
    Obj_b061_01E03440 fade;
    Ray_b011_01E04380 ray;
    Trail_b181_01E02D50 trail;
    Rib_b059_01E00E10 rib[100];
    s8 tbl[0x100];
    u8 pad2538[8];
} Scene_b181_01E03830;

#pragma optimization_level 1

static s32 func_01E03830_b181(Scene_b181_01E03830 *g, s32 code) {
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
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern void func_01E01170_b181();
    extern Cue_b181_01E03830 D_01E03F20_b181[];
    s32 ot;
    V4_b181_01E03830 v;
    s32 i;
    Cue_b181_01E03830 *e;
    u16 t;
    s32 unit;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x2540);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 1; i++) {
            func_00202BF0(5, i);
        }
        g->model = func_001F5560(g->unitA, 0x40, 1);
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x27:
        func_00101AD0(&g->trail, 0x1F, 0, 0xFF);
        g->trail.flags = 0;
        g->trail.follow = 1;
        g->trail.pad6[0] = g->model;
        g->trail.list = (Part_b181_01E02D50 *)g->rib;
        g->trail.b10 = 100;
        g->trail.b12 = 4;
        g->trail.b11 = 0x12;
        g->trail.b13 = 0;
        g->trail.b16 = 2;
        g->trail.b14 = 4;
        g->trail.f18 = 0.4f;
        g->trail.f1C = 0.5f;
        g->trail.f20 = 45.0f;
        g->trail.f24 = -1.5f;
        g->trail.w0C = (s32)g->tbl;
        g->trail.col.b = g->trail.col.g = g->trail.col.r = g->trail.col.a = 0x80;
        func_001F5620(g->unitA, g->model, &g->trail.prev);
        g->trail.prev2 = g->trail.prev;
        break;
    case 0x33:
        func_00101AD0(&g->fade, 4, 0, 0xFF);
        g->fade.flags = 1;
        func_00101AD0(&g->glow, 0x1C, 0, 0xFF);
        g->glow.b5 = 0;
        g->glow.b4 = 0x81;
        g->glow.b7 = 9;
        g->glow.f10 = 600.0f;
        g->glow.f14 = 20.0f;
        g->glow.c[2] = g->glow.c[1] = g->glow.c[0] = g->glow.c[3] = 0xC0;
        g->glow.bA = 0x20;
        g->glow.b9 = 0x20;
        g->glow.b8 = 0x80;
        g->glow.w3C = g->glow.w40 = g->glow.w44 = 0;
        g->glow.pos = v;
        g->glow.f18 = 20.0f;
        func_00101AD0(&g->ray, 0x18, 0, 0xFF);
        g->ray.flags = 5;
        g->ray.size = 2.8f;
        g->ray.width = 40.0f;
        g->ray.pad05[0] = 0;
        g->ray.texkind = 0;
        g->ray.texpage = 2;
        g->ray.texmode = 3;
        g->ray.segments = 0xA0;
        g->ray.index = func_0019A5C8() >> 4;
        g->ray.table = (u8 *)g->tbl;
        g->ray.radius = 1.0f;
        g->ray.r0 = g->ray.g0 = g->ray.b0 = g->ray.r1 = g->ray.g1 = g->ray.b1 = 0x80;
        g->ray.a0 = 0x20;
        g->ray.a1 = 0x80;
        g->ray.pos = *(Vec_b011_01E04380 *)&v;
        g->ray.spin[0] = 0x40;
        g->ray.spin[1] = 0x80;
        g->ray.spin[2] = 0x100;
        func_00101AD0(&g->emit, 0x18, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.8f;
        g->emit.f18 = 1.0f;
        g->emit.f1C = 2.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 60.0f;
        g->emit.f50 = 6.0f;
        func_001F5F90(g->unitB, &g->emit.pos);
        break;
    case 0x69:
        return 8;
    }
    func_01E00080_b181((Obj_b002_01E00080 *)&g->emit);
    func_01E02D50_b181(&g->trail, ot, 1);
    func_01E01E90_b181(g->rib, ot, 100);
    func_01E01170_b181(&g->glow, ot, 1);
    func_01E032C0_b181(&g->fade, ot);
    func_01E00440_b181(&g->ray, ot, 1);
    t = g->t;
    for (e = D_01E03F20_b181; e->start != 0; e++) {
        if (t >= e->start && t <= e->end) {
            if (e->flags & 0x80) {
                unit = func_001F5380();
            } else {
                unit = func_001F53A0();
            }
            if (e->flags & 0x40) {
                e->c0[3] = e->c1[3] = (t - *(u8 *)&e->start) * e->rate;
            }
            func_001F71A0(unit, e->motion, e->flags & 3, e->c0, e->c1, e->w8);
            break;
        }
    }
    if (g->t >= 0x33 && g->t <= 0x47) {
        return 6;
    }
    switch (g->t) {
    case 0x29:
        return 1;
    case 0x48:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
