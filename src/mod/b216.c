#include "common.h"

/* shape b216:01E00080 (b216), 5270 insns, 1 copy (-O3,p): b216 scene manager, b088:01E00080's form: four comets at
   0x30..0x4E with ember trails and flashes, sixteen two-pass sparks, four novas and warp fans at 0x64/0x78/0x8C/0xA0
   with a white screen flash, a b371-style rotating cylinder at 8 and a render-to-texture aura (func_001F7070 with
   func_01E052E0) from 0; returns 1 / 6 / 2 / 8 at 0x5A / 0x65..0xBF / 0xC0 / >0xE8 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b216_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b216_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b216_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b216_01E00080 c;
    Uv_b216_01E00080 uv0;
    Xyz_b216_01E00080 p0;
    Uv_b216_01E00080 uv1;
    Xyz_b216_01E00080 p1;
    u8 tail[0x20];
} Spr_b216_01E00080;

typedef struct {
    Rgbaq_b216_01E00080 c;
    f32 s, t;
    Xyz_b216_01E00080 p;
} Tv_b216_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b216_01E00080 c;
        Uv_b216_01E00080 uv;
        Xyz_b216_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b216_01E00080;

typedef struct {
    Rgbaq_b216_01E00080 c;
    Xyz_b216_01E00080 p;
} Lv_b216_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b216_01E00080 v[4];
    u64 tail;
} Line_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life;
    s32 n;
    s32 c;
    u8 pad14[0xC];
    Vec4f p[1];
    Vec4f v[1];
} Comet_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p[1];
    u8 c[1][16];
    Vec4f v[1][16];
    u8 c2[1][32];
    Vec4f v2[1][32];
} Flash_b216_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f pos;
    Vec4f v[16];
} Spark_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Smoke_b216_01E00080;

typedef struct {
    f32 s, t;
    Xyz_b216_01E00080 p;
} Qv_b216_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b216_01E00080 c;
    Qv_b216_01E00080 v[4];
    u8 tail[0x20];
} Quad_b216_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b216_01E00080 c;
    Xyz_b216_01E00080 p0;
    Xyz_b216_01E00080 p1;
    u64 tail;
} Flat_b216_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f v2[128];
    u8 c2[64];
    Vec4f v3[64];
} Nova_b216_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn[1];
    u8 pad24[0xC];
    Vec4f jp[1];
    s32 jn2[2];
    u8 pad48[8];
    Vec4f jp2[2];
    Vec4f pos;
    Vec4f tgt;
    Vec4f scr;
    Vec4f scr2;
    s32 nshot;
    s32 ncomet;
    u8 padB8[8];
    Comet_b216_01E00080 comet[4];
    Puff_b216_01E00080 trail[4][1][16];
    Smoke_b216_01E00080 smoke[4][1][16];
    s32 nflash;
    u8 pad41C4[0xC];
    Flash_b216_01E00080 flash[4];
    Spark_b216_01E00080 spark[16];
    u8 on;
    u8 pad6211[3];
    s32 t2;
    u8 pad6218[8];
    Ring_b216_01E00080 rg[33];
    u8 bc[128];
    Vec4f bpos;
    Vec4f bv[128];
    u8 on2;
    u8 pad70E1[3];
    s32 t3;
    s32 nn;
    u8 pad70EC[4];
    Nova_b216_01E00080 nova[4];
    Vec4f grid[33][17];
    s32 ph[33][17];
    u8 on3;
    u8 padE045[3];
    s32 t4;
    u8 on4;
    u8 padE04D[3];
    s32 t5;
    u8 on5;
    u8 padE055[3];
    s32 t6;
    u8 padE05C[4];
} Scene_b216_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b216(s32 arg0, s32 code) {
    Scene_b216_01E00080 *g = (Scene_b216_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00101080(void *, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_0017B340();
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void b216_01E052E0();
    extern s32 D_01E05600_b216;
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 x;
    s32 k;
    s32 q;
    s32 n;
    s32 y;
    s32 idx;
    f32 a;
    f32 b;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    u8 alpha;
    s32 buf;
    u8 a2;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Vec4f v;
    Flat_b216_01E00080 fl __attribute__((aligned(8)));
    Quad_b216_01E00080 qd __attribute__((aligned(8)));
    Line_b216_01E00080 lp __attribute__((aligned(8)));
    Tri_b216_01E00080 tri __attribute__((aligned(8)));
    Spr_b216_01E00080 spr __attribute__((aligned(8)));
    Xyz_b216_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xE060);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->jn[0] = func_001F5560(g->unitA, 0x15, 1);
        g->jn2[0] = func_001F5560(g->unitA, 0x16, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x17, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->nshot = 0;
        g->ncomet = 0;
        for (i = 0; i < 4; i++) {
            g->comet[i].on = 0;
            g->comet[i].n = 0;
            g->comet[i].c = 0;
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
        g->nflash = 0;
        for (i = 0; i < 4; i++) {
            g->flash[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->on = 0;
        for (i = 0; i < 33; i++) {
            idx = (i << 16) >> 5;
            v.x = func_0020B550(idx);
            v.y = func_0020B480(idx);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->rg[i].a, &v, 36.5f);
            func_00187B48((void *)&g->rg[i].b, &v, 46.4f);
            func_00187B48((void *)&g->rg[i].mid, &v, 47.0f);
        }
        g->nn = 0;
        for (i = 0; i < 4; i++) {
            g->nova[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 33; i++) {
            for (j = 0; j < 17; j++) {
                g->ph[i][j] = (((func_0019A5C8() >> 23) % 256) << 16) >> 8;
            }
        }
        g->on3 = 0;
        g->on4 = 0;
        g->on5 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 1; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jp2[i]);
    }
    func_001F53C0(1, g->unitA, &g->pos);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
    g->scr.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr.z = func_0017B340(xyz.z);
    g->scr.w = 1.0f;
    if (g->scr.x < 0.0f) {
        g->scr.x = 0.0f;
    }
    if (g->scr.x > 640.0f) {
        g->scr.x = 640.0f;
    }
    if (g->scr.y < 0.0f) {
        g->scr.y = 0.0f;
    }
    if (g->scr.y > 448.0f) {
        g->scr.y = 448.0f;
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
    g->scr2.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr2.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr2.z = func_0017B340(xyz.z);
    g->scr2.w = 1.0f;
    if (g->scr2.x < 0.0f) {
        g->scr2.x = 0.0f;
    }
    if (g->scr2.x > 640.0f) {
        g->scr2.x = 640.0f;
    }
    if (g->scr2.y < 0.0f) {
        g->scr2.y = 0.0f;
    }
    if (g->scr2.y > 448.0f) {
        g->scr2.y = 448.0f;
    }
    if (g->t == 0x64 || g->t == 0x78 || g->t == 0x8C || g->t == 0xA0) {
        g->on5 = 1;
        g->t6 = 0;
    }
    ((Flat_b216_01E00080 *)(s32)&fl)->flags = 6;
    ((Flat_b216_01E00080 *)(s32)&fl)->size = 3;
    ((Flat_b216_01E00080 *)(s32)&fl)->regs = 0x441;
    ((Flat_b216_01E00080 *)(s32)&fl)->pad4 = 0;
    func_002086D0(&fl, func_00208D00(0));
    if (g->on5 == 1) {
        alpha = (u32)(128.0f * ((8 - g->t6) / 8.0f));
        fl.c.r = 0xFF;
        fl.c.g = 0xE8;
        fl.c.b = 0xE1;
        fl.c.a = alpha;
        fl.c.q = 1.0f;
        fl.p0.x = 0x6C00;
        fl.p0.y = 0x7200;
        fl.p0.z = 0xFFFFF8;
        fl.p0.f = 0;
        fl.p1.x = 0x9400;
        fl.p1.y = 0x8E00;
        fl.p1.z = 0xFFFFF8;
        fl.p1.f = 0;
        func_002075F0(&fl, ot, 0);
        g->t6++;
        if (g->t6 > 8) {
            g->on5 = 0;
        }
    }
    if (g->t == 0x64 || g->t == 0x78 || g->t == 0x8C || g->t == 0xA0) {
        g->on2 = 1;
        g->t3 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b216_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b216_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b216_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b216_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b216_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (32 - g->t3) * 80 >> 5;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            f = 1.0f + 0.2f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr2.x;
                y = (s32)g->scr2.y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr2);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr2);
                func_00187B48(&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
                func_00187B00(&out[0], &out[0], &g->scr2);
                func_00187B00(&out[1], &out[1], &g->scr2);
                x = (s32)g->scr2.x;
                y = (s32)g->scr2.y;
                tri.v[0].p.x = (x + 0x6C0) << 4;
                tri.v[0].p.y = (y + 0x720) << 4;
                tri.v[0].p.z = 0xFFFFF8;
                tri.v[0].p.f = 0;
                x = (s32)out[0].x;
                y = (s32)out[0].y;
                tri.v[1].p.x = (x + 0x6C0) << 4;
                tri.v[1].p.y = (y + 0x720) << 4;
                tri.v[1].p.z = 0xFFFFF8;
                tri.v[1].p.f = 0;
                x = (s32)out[1].x;
                y = (s32)out[1].y;
                tri.v[2].p.x = (x + 0x6C0) << 4;
                tri.v[2].p.y = (y + 0x720) << 4;
                tri.v[2].p.z = 0xFFFFF8;
                tri.v[2].p.f = 0;
                func_002075F0(&tri, 0, 0);
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t3++;
        if (g->t3 > 32) {
            g->on2 = 0;
        }
    }
    n = -1;
    switch (g->t) {
    case 0x30:
        n = 0x34;
        break;
    case 0x3A:
        n = 0x3E;
        break;
    case 0x44:
        n = 0x48;
        break;
    case 0x4E:
        n = 0x52;
        break;
    }
    if (n >= 0) {
        idx = g->ncomet;
        g->comet[idx].on = 1;
        g->comet[idx].t = 0;
        g->comet[idx].life = n;
        n = g->nflash;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->comet[idx].p[j] = g->jp[j];
            g->flash[n].p[j] = g->jp[j];
            func_00101080(&v, 0.0f);
            func_00187B00(&v, &v, &g->tgt);
            v.x = g->comet[idx].p[j].x;
            func_00187B18(&g->comet[idx].v[j], &v, &g->comet[idx].p[j]);
            for (k = 0; k < 16; k++) {
                g->flash[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->flash[n].v[j][k], 1.0f);
            }
            for (k = 0; k < 32; k++) {
                g->flash[n].c2[j][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->flash[n].v2[j][k], 1.0f);
            }
        }
        g->nshot++;
        g->ncomet++;
        if (g->ncomet >= 4) {
            g->ncomet = 0;
        }
        g->nflash++;
        if (g->nflash >= 4) {
            g->nflash = 0;
        }
    }

    ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 14.0f;
    cn[0].x = -r;
    cn[0].y = -r;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = r;
    cn[1].y = r;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    func_001878E0(&cn[0], m3, &cn[0]);
    func_001878E0(&cn[1], m3, &cn[1]);
    for (i = 0; i < 4; i++) {
        if (g->comet[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        s = (f32)g->comet[i].t / (f32)g->comet[i].life;
        idx = g->comet[i].n;
        g->comet[i].n++;
        if (g->comet[i].n >= 16) {
            g->comet[i].n = 0;
        }
        n = g->comet[i].c;
        g->comet[i].c++;
        if (g->comet[i].c >= 16) {
            g->comet[i].c = 0;
        }
        for (j = 0; j < 1; j++) {
            func_00187B48(&v, &g->comet[i].v[j], s);
            func_00187B00(&v, &v, &g->comet[i].p[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
            g->trail[i][j][idx].on = 1;
            g->trail[i][j][idx].t = 0;
            g->trail[i][j][idx].pos = v;
            for (k = 0; k < 4; k++) {
                g->trail[i][j][idx].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->trail[i][j][idx].v[k], 0.5f);
            }
            g->smoke[i][j][n].on = 1;
            g->smoke[i][j][n].t = 0;
            g->smoke[i][j][n].pos = v;
            for (k = 0; k < 8; k++) {
                g->smoke[i][j][n].c[k] = (func_0019A5C8() >> 23) % 3;
                func_00101080(&g->smoke[i][j][n].v[k], 1.0f);
            }
        }
        g->comet[i].t++;
        if (g->comet[i].t > g->comet[i].life) {
            g->comet[i].on = 0;
        }
    }

    ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                if (g->trail[i][j][k].on == 0) {
                    continue;
                }
                r = 0.5f + 0.5f * (16 - g->trail[i][j][k].t) / 16.0f;
                r = 10.0f * r;
                cn[0].x = -r;
                cn[0].y = -r;
                cn[0].z = 0.0f;
                cn[0].w = 1.0f;
                cn[1].x = r;
                cn[1].y = r;
                cn[1].z = 0.0f;
                cn[1].w = 1.0f;
                func_001878E0(&cn[0], m3, &cn[0]);
                func_001878E0(&cn[1], m3, &cn[1]);
                alpha = (16 - g->trail[i][j][k].t) * 128 >> 4;
                spr.c.r = 0xFF;
                spr.c.g = 0x3C;
                spr.c.b = 0x3C;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->trail[i][j][k].t, 16, 1);
                for (q = 0; q < 4; q++) {
                    x = g->trail[i][j][k].c[q] % 4 * 32;
                    y = (g->trail[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->trail[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->trail[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, 0);
                    }
                }
                g->trail[i][j][k].t++;
                if (g->trail[i][j][k].t > 16) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                if (g->smoke[i][j][k].on == 0) {
                    continue;
                }
                r = 2.5f * (0.5f + 0.5f * (16 - g->smoke[i][j][k].t) / 16.0f);
                cn[0].x = -r;
                cn[0].y = -r;
                cn[0].z = 0.0f;
                cn[0].w = 1.0f;
                cn[1].x = r;
                cn[1].y = r;
                cn[1].z = 0.0f;
                cn[1].w = 1.0f;
                func_001878E0(&cn[0], m3, &cn[0]);
                func_001878E0(&cn[1], m3, &cn[1]);
                alpha = (16 - g->smoke[i][j][k].t) * 255 >> 4;
                spr.c.r = 0xFF;
                spr.c.g = 0x96;
                spr.c.b = 0x96;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.1f + 0.9f * func_00100D50(g->smoke[i][j][k].t, 16, 1);
                for (q = 0; q < 8; q++) {
                    x = g->smoke[i][j][k].c[q] % 4 * 32;
                    y = (g->smoke[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->smoke[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->smoke[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, 0);
                    }
                }
                g->smoke[i][j][k].t++;
                if (g->smoke[i][j][k].t > 16) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->flash[i].on == 0) {
            continue;
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 150.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->flash[i].t, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 1; j++) {
            v = g->flash[i].p[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        func_002086D0(&spr, func_00208D00(0));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        r = 10.0f * (0.5f + 0.5f * g->flash[i].t / 32.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (32 - g->flash[i].t) * 128 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                x = g->flash[i].c[j][k] % 4 * 32;
                y = (g->flash[i].c[j][k] >> 2) * 32;
                ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 2.0f * (0.5f + 0.5f * (32 - g->flash[i].t) / 32.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (32 - g->flash[i].t) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                x = g->flash[i].c2[j][k] % 4 * 32;
                y = (g->flash[i].c2[j][k] >> 2) * 32;
                ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v2[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->flash[i].t++;
        if (g->flash[i].t > 32) {
            g->flash[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x32) {
        n = g->t % 16;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].pos = g->jp[0];
        for (k = 0; k < 16; k++) {
            g->spark[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[k], 1.0f);
        }
    }

    ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 0.2f + 0.8f * (16 - g->spark[i].t) / 16.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (u32)(255.0f * func_0020B480((g->spark[i].t << 14) >> 4));
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->spark[i].t, 16, 1);
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[k] % 4 * 32;
            y = (g->spark[i].c[k] >> 2) * 32;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
        }
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 8.0f * (0.2f + 0.8f * g->spark[i].t / 16.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (u32)(80.0f * func_0020B480((g->spark[i].t << 14) >> 4));
        spr.c.r = 0xFF;
        spr.c.g = 0x60;
        spr.c.b = 0x60;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = -0.7f * (0.1f + 0.9f * func_00100D50(g->spark[i].t, 16, 1));
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = (g->spark[i].c[k] + 4) % 4 * 32;
            y = ((g->spark[i].c[k] + 4) >> 2) * 32;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 16) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 3) {
        g->on = 1;
        g->t2 = 0;
        func_00187B00(&v, &g->jp2[0], &g->jp2[1]);
        func_00187B48((void *)&v, &v, 0.5f);
        g->bpos = v;
        for (k = 0; k < 128; k++) {
            g->bc[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->bv[k], 1.0f);
        }
    }
    if (g->on == 1) {
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 48.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Line_b216_01E00080 *)(s32)&lp)->flags = 0x14;
        ((Line_b216_01E00080 *)(s32)&lp)->size = 8;
        ((Line_b216_01E00080 *)(s32)&lp)->regs = 0x41414141;
        ((Line_b216_01E00080 *)(s32)&lp)->pad4 = 0;
        func_002086D0(&lp, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        s = 0.1f + 0.9f * func_00100D50(g->t2, 32, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        lp.v[0].c.r = 0xFF;
        lp.v[0].c.g = 0x96;
        lp.v[0].c.b = 0x96;
        lp.v[0].c.a = alpha;
        lp.v[0].c.q = 1.0f;
        lp.v[1].c = lp.v[0].c;
        lp.v[2].c.r = 0xFF;
        lp.v[2].c.g = 0;
        lp.v[2].c.b = 0;
        lp.v[2].c.a = 0;
        lp.v[2].c.q = 1.0f;
        lp.v[3].c = lp.v[2].c;
        for (j = 0; j < 32; j++) {
            if (func_00100BA0(&g->rg[j].b, &g->rg[j + 1].b, &g->rg[j].a, &g->rg[j + 1].a, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
            if (func_00100BA0(&g->rg[j].b, &g->rg[j + 1].b, &g->rg[j].mid, &g->rg[j + 1].mid, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
        }
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 1.5f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        for (k = 0; k < 128; k++) {
            x = g->bc[k] % 4 * 32;
            y = (g->bc[k] >> 2) * 32;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->bv[k], s);
            func_00187B00(&v, &v, &g->bpos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 32) {
            g->on = 0;
        }
    }

    n = -1;
    switch (g->t) {
    case 0x64:
        n = 0;
        break;
    case 0x78:
        n = 1;
        break;
    case 0x8C:
        n = 2;
        break;
    case 0xA0:
        n = 3;
        break;
    }
    if (n >= 0) {
        g->nn = n;
        g->nova[g->nn].on = 1;
        g->nova[g->nn].t = 1;
        g->nova[g->nn].pos.x = 0.0f;
        g->nova[g->nn].pos.y = 0.0f;
        g->nova[g->nn].pos.z = 0.0f;
        g->nova[g->nn].pos.w = 1.0f;
        func_00187B00(&g->nova[g->nn].pos, &g->nova[g->nn].pos, &g->tgt);
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->nova[g->nn].v[k], 2.0f);
        }
        for (k = 0; k < 128; k++) {
            func_00101080(&g->nova[g->nn].v2[k], 1.5f);
        }
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c2[k] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->nova[g->nn].v3[k], 2.0f);
        }
    }
    for (i = 0; i < 4; i++) {
        if (g->nova[i].on == 0) {
            continue;
        }
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 8.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (32 - g->nova[i].t) * 200 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x96;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->nova[i].t, 32, 1);
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->nova[i].v3[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c2[k] % 4 * 32;
            y = (g->nova[i].c2[k] >> 2) * 32;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 10.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (32 - g->nova[i].t) * 128 >> 5;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->nova[i].t, 32, 1);
            if (k % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(0));
                spr.c.r = 8;
                spr.c.g = 8;
                spr.c.b = 8;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xFF;
                spr.c.g = 0xC8;
                spr.c.b = 0xC8;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->nova[i].v[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c[k] % 4 * 32;
            y = (g->nova[i].c[k] >> 2) * 32;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->nova[i].pos);
        s = 0.2f + 0.8f * func_00100D50(g->nova[i].t, 32, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((32 - g->nova[i].t) / 32.0f));
        spr.c.r = 0xFF;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 150.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Spr_b216_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b216_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b216_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b216_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b216_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 0;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b216_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b216_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        s = (32 - g->nova[i].t) / 32.0f;
        h = func_00100D50(g->nova[i].t, 32, 1);
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 6; k++) {
                alpha = (u32)(s * ((k + 6) * 255 / 12));
                spr.c.r = 0xFF;
                spr.c.g = 0x96;
                spr.c.b = 0x96;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->nova[i].v2[j], h + 0.007f * k);
                func_00187B00(&v, &v, &g->nova[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->nova[i].t++;
        if (g->nova[i].t > 32) {
            g->nova[i].on = 0;
        }
    }

    if (g->t == 8) {
        g->on3 = 1;
        g->t4 = 0;
    }
    if (g->on3 == 1) {
        ((Quad_b216_01E00080 *)(s32)&qd)->flags = 0x24;
        ((Quad_b216_01E00080 *)(s32)&qd)->size = 9;
        ((Quad_b216_01E00080 *)(s32)&qd)->regs = ((u64)4 << 32) | 0x24242421;
        ((Quad_b216_01E00080 *)(s32)&qd)->pad4 = 0;
        func_002086D0(&qd, func_00208D00(0));
        func_00208700(&qd, g->tex[3], 1);
        func_00208CB0(&qd, 0);
        a = func_00101020(g->t4, 16.0f) * func_00100FF0(g->t4, 216.0f, 184.0f);
        for (k = 0; k < 2; k++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 50.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            t0 = 180.0f + 2.0f * (20.0f * k);
            for (i = 0; i < 33; i++) {
                b = -3000.0f + 6000.0f * i / 32.0f;
                for (j = 0; j < 16; j++) {
                    f = t0 + 20.0f * func_0020B550((g->ph[i][j] + (k * 0x33333 >> 1) + g->t4 * 0x8AE) & 0xFFFF);
                    x = (j << 16) >> 4;
                    g->grid[i][j].x = f * func_0020B550(x);
                    g->grid[i][j].y = f * func_0020B480(x);
                    g->grid[i][j].z = b;
                    g->grid[i][j].w = 1.0f;
                }
                g->grid[i][16] = g->grid[i][0];
            }
            x = ((k % 2 * 2 - 1) * ((g->t4 + k * 32) % 128 << 16 >> 7)) & 0xFFFF;
            h = func_0020B550(x);
            b = 0.0f * func_0020B480(x) + 2.0f * (g->t4 % 32) / 32.0f * g->obj;
            for (i = 0; i < 32; i++) {
                t0 = (f32)(i % 2) / 2.0f;
                t1 = (f32)(i % 2 + 1) / 2.0f;
                s = func_0020B550((i << 15) >> 5);
                if (k == 0) {
                    alpha = (u32)(64.0f * a * s);
                } else {
                    alpha = (u32)(116.0f * a * s);
                }
                qd.c.r = 0x38;
                qd.c.g = 0x10;
                qd.c.b = 0x10;
                qd.c.a = alpha;
                qd.c.q = 1.0f;
                for (j = 0; j < 16; j++) {
                    s0 = (f32)(j % 2) / 2.0f;
                    s1 = (f32)(j % 2 + 1) / 2.0f + h;
                    qd.v[0].s = s0 + h;
                    qd.v[0].t = t0 + b;
                    qd.v[1].s = s1;
                    qd.v[1].t = t0 + b;
                    qd.v[2].s = s0 + h;
                    qd.v[2].t = t1 + b;
                    qd.v[3].s = s1;
                    qd.v[3].t = t1 + b;
                    if (func_00100BA0(&g->grid[i][j], &g->grid[i][j + 1], &g->grid[i + 1][j], &g->grid[i + 1][j + 1], m,
                                      &qd, &depth) == 1) {
                        func_002075F0(&qd, ot, 0xFFFFFF);
                    }
                }
            }
        }
        g->t4++;
        if (g->t4 > 0xD8) {
            g->on3 = 0;
        }
    }
    if (g->t == 0) {
        g->on4 = 1;
        g->t5 = 0;
    }
    if (g->on4 == 1) {
        ((Tri_b216_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b216_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b216_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b216_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b216_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        n = func_00207F60();
        func_00208460();
        D_01E05600_b216 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, b216_01E052E0);
        func_00208460();
        a = func_00101020(g->t5, 32.0f);
        b = func_00101020(g->t5, 128.0f);
        a = 80.0f * a;
        b = 80.0f * b;
        for (i = 0; i < 1; i++) {
            alpha = (u32)a;
            (void)alpha;
            a2 = (u32)b;
            (void)a2;
            tri.v[0].c.r = 0xFF;
            tri.v[0].c.g = 0xFF;
            tri.v[0].c.b = 0xFF;
            tri.v[0].c.a = alpha;
            tri.v[0].c.q = 1.0f;
            tri.v[1].c.r = 0xFF;
            tri.v[1].c.g = 0xFF;
            tri.v[1].c.b = 0xFF;
            tri.v[1].c.a = a2;
            tri.v[1].c.q = 1.0f;
            tri.v[2].c = tri.v[1].c;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b216_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b216_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48((void *)&out[0], &out[0], 1.5f);
                func_00187B48(&out[1], &out[1], 1.5f);
                func_00187B00(&out[0], &out[0], &g->scr);
                func_00187B00(&out[1], &out[1], &g->scr);
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                tri.v[0].p.x = (x + 0x6C0) << 4;
                tri.v[0].p.y = (y + 0x720) << 4;
                tri.v[0].p.z = 0xFFFFF8;
                tri.v[0].p.f = 0;
                x = (s32)out[0].x;
                y = (s32)out[0].y;
                tri.v[1].p.x = (x + 0x6C0) << 4;
                tri.v[1].p.y = (y + 0x720) << 4;
                tri.v[1].p.z = 0xFFFFF8;
                tri.v[1].p.f = 0;
                x = (s32)out[1].x;
                y = (s32)out[1].y;
                tri.v[2].p.x = (x + 0x6C0) << 4;
                tri.v[2].p.y = (y + 0x720) << 4;
                tri.v[2].p.z = 0xFFFFF8;
                tri.v[2].p.f = 0;
                func_002075F0(&tri, 0, 0);
            }
        }
        func_00207FD0(n, ot, 0);
        g->t5++;
        if (g->t5 > 0xA0) {
            g->on4 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0xE8 - g->t, 0, 8) * (func_00101050(g->t, 0, 8) * -128) >> 6) + 0x80));
    if (g->t == 0x5A) {
        ret = 1;
    } else {
        if (g->t > 0x64 && g->t < 0xC0) {
            ret = 6;
        }
        if (g->t == 0xC0) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xE8) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b216:01E052E0 (Gb216_GenAuraTex), 173 insns, 1 copy: b711:01E054B0 with the cover at (0x80, 0, 0) alpha 0xFF:
   a white 5-reg sprite packet then a flat 3-reg packet over the same rectangle */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b216_01E052E0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b216_01E052E0 v[2];
    u8 tail[8];
} Flat_b216_01E052E0;

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_b216_01E052E0;

typedef struct {
    Uv_b216_01E052E0 st;
    Xyz_b216_01E052E0 p;
} Tv_b216_01E052E0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b216_01E052E0 v[2];
    u8 tail[8];
} Spr_b216_01E052E0;


static void func_01E052E0_b216(void *ctx) {
    extern s32 func_00207650(s32, void *, s32, s32);
    Flat_b216_01E052E0 flat __attribute__((aligned(8)));
    Spr_b216_01E052E0 pk __attribute__((aligned(8)));
    s32 oA8[2];
    s32 oB0[3];

    ctx = func_00209F70(ctx, 0xFF000000);
    ((Spr_b216_01E052E0 *)(u32)&pk)->count = 0x26;
    ((Spr_b216_01E052E0 *)(u32)&pk)->n = 5;
    ((Spr_b216_01E052E0 *)(u32)&pk)->regs = 0x42421;
    ((Spr_b216_01E052E0 *)(u32)&pk)->pad4 = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, oA8, oB0));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Spr_b216_01E052E0 *)(u32)&pk)->count |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    ((Uv_b216_01E052E0 *)(s32)&pk.v[0].st)->s = 0;
    ((Uv_b216_01E052E0 *)(s32)&pk.v[0].st)->t = 0;
    ((Uv_b216_01E052E0 *)(s32)&pk.v[1].st)->s = 0x2800;
    ((Uv_b216_01E052E0 *)(s32)&pk.v[1].st)->t = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    ctx = (void *)func_00207650((s32)ctx, &pk, 0, 0);
    ((Flat_b216_01E052E0 *)(u32)&flat)->count = 6;
    ((Flat_b216_01E052E0 *)(u32)&flat)->n = 3;
    ((Flat_b216_01E052E0 *)(u32)&flat)->regs = 0x441;
    ((Flat_b216_01E052E0 *)(u32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0x80;
    flat.g = 0;
    flat.b = 0;
    flat.a = 0xFF;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    func_00209F70((void *)func_00207650((s32)ctx, &flat, 0, 0), 0);
}

