#include "common.h"

/* shape b711:01E00080 (b711), 5386 insns, 1 copy (-O3,p): b711 scene manager, b216:01E00080's form: three comets at
   0x35/0x4B/0x70 with ember trails and flashes, sixteen two-pass sparks, a ring at 6, three novas and warp fans at
   0x8C/0xA1/0xBB with a white screen flash, a six-ring render-to-texture aura from 5 and 32 slots of 64 flying
   textured blades spawned 9..0xFA; returns 1 / 6 / 2 / 8 at 0x82 / 0x8D..0xDA / 0xDB / >0x123 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b711_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b711_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b711_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b711_01E00080 c;
    Uv_b711_01E00080 uv0;
    Xyz_b711_01E00080 p0;
    Uv_b711_01E00080 uv1;
    Xyz_b711_01E00080 p1;
    u8 tail[0x20];
} Spr_b711_01E00080;

typedef struct {
    Rgbaq_b711_01E00080 c;
    f32 s, t;
    Xyz_b711_01E00080 p;
} Tv_b711_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b711_01E00080 c;
        Uv_b711_01E00080 uv;
        Xyz_b711_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b711_01E00080;

typedef struct {
    Rgbaq_b711_01E00080 c;
    Xyz_b711_01E00080 p;
} Lv_b711_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b711_01E00080 v[4];
    u64 tail;
} Line_b711_01E00080;

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
} Comet_b711_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b711_01E00080;

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
} Flash_b711_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b711_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f pos;
    Vec4f v[16];
} Spark_b711_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Smoke_b711_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b711_01E00080 c;
    Xyz_b711_01E00080 p0;
    Xyz_b711_01E00080 p1;
    u64 tail;
} Flat_b711_01E00080;

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
} Nova_b711_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 life[64];
    s32 ang[64];
    u8 c[64][3];
} Bolt_b711_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b711_01E00080 v[4];
    u8 tail[0x20];
} Blade_b711_01E00080;

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
    Comet_b711_01E00080 comet[3];
    Puff_b711_01E00080 trail[3][1][16];
    Smoke_b711_01E00080 smoke[3][1][16];
    s32 nflash;
    u8 pad41C4[0xC];
    Flash_b711_01E00080 flash[3];
    Spark_b711_01E00080 spark[16];
    u8 on;
    u8 pad6211[3];
    s32 t2;
    u8 pad6218[8];
    Ring_b711_01E00080 rg[33];
    u8 bc[128];
    Vec4f bpos;
    Vec4f bv[128];
    u8 on2;
    u8 pad70E1[3];
    s32 t3;
    s32 nn;
    u8 pad70EC[4];
    Nova_b711_01E00080 nova[4];
    u8 on4;
    u8 padA0E1[3];
    s32 t5;
    u8 on5;
    u8 padA0E9[3];
    s32 t6;
    Bolt_b711_01E00080 bolt[32];
} Scene_b711_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b711(s32 arg0, s32 code) {
    Scene_b711_01E00080 *g = (Scene_b711_01E00080 *)arg0;
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
    extern void b711_01E054B0();
    extern s32 D_01E05780_b711;
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_00100E00(void *, s32, s32);
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
    Flat_b711_01E00080 fl __attribute__((aligned(8)));
    Line_b711_01E00080 lp __attribute__((aligned(8)));
    Tri_b711_01E00080 tri __attribute__((aligned(8)));
    Blade_b711_01E00080 bl __attribute__((aligned(8)));
    Spr_b711_01E00080 spr __attribute__((aligned(8)));
    Xyz_b711_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xE1F0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->jn[0] = func_001F5560(g->unitA, 0x1B, 1);
        g->jn2[0] = func_001F5560(g->unitA, 0x1C, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x1D, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->nshot = 0;
        g->ncomet = 0;
        for (i = 0; i < 3; i++) {
            g->comet[i].on = 0;
            g->comet[i].n = 0;
            g->comet[i].c = 0;
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
        g->nflash = 0;
        for (i = 0; i < 3; i++) {
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
        g->on4 = 0;
        g->on5 = 0;
        for (i = 0; i < 32; i++) {
            g->bolt[i].on = 0;
        }
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
    if (g->t == 0x8C || g->t == 0xA1 || g->t == 0xBB) {
        g->on5 = 1;
        g->t6 = 0;
    }
    ((Flat_b711_01E00080 *)(s32)&fl)->flags = 6;
    ((Flat_b711_01E00080 *)(s32)&fl)->size = 3;
    ((Flat_b711_01E00080 *)(s32)&fl)->regs = 0x441;
    ((Flat_b711_01E00080 *)(s32)&fl)->pad4 = 0;
    func_002086D0(&fl, func_00208D00(0));
    if (g->on5 == 1) {
        alpha = (u32)(128.0f * ((16 - g->t6) / 16.0f));
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
        if (g->t6 > 16) {
            g->on5 = 0;
        }
    }
    if (g->t == 0x8C || g->t == 0xA1 || g->t == 0xBB) {
        g->on2 = 1;
        g->t3 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b711_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b711_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b711_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b711_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b711_01E00080 *)(s32)&tri)->flags |= 0x800;
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
                ((Uv_b711_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b711_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b711_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
    case 0x35:
        n = 0x57;
        break;
    case 0x4B:
        n = 0x56;
        break;
    case 0x70:
        n = 0x4B;
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
        if (g->ncomet >= 3) {
            g->ncomet = 0;
        }
        g->nflash++;
        if (g->nflash >= 3) {
            g->nflash = 0;
        }
    }

    ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
    for (i = 0; i < 3; i++) {
        if (g->comet[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0xA0;
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

    ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
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
                spr.c.g = 0x46;
                spr.c.b = 0x3C;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->trail[i][j][k].t, 16, 1);
                for (q = 0; q < 4; q++) {
                    x = g->trail[i][j][k].c[q] % 4 * 32;
                    y = (g->trail[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
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
                spr.c.g = 0xA0;
                spr.c.b = 0x96;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.1f + 0.9f * func_00100D50(g->smoke[i][j][k].t, 16, 1);
                for (q = 0; q < 8; q++) {
                    x = g->smoke[i][j][k].c[q] % 4 * 32;
                    y = (g->smoke[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        if (g->flash[i].on == 0) {
            continue;
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        spr.c.g = 0xA0;
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
        spr.c.g = 0xA0;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                x = g->flash[i].c[j][k] % 4 * 32;
                y = (g->flash[i].c[j][k] >> 2) * 32;
                ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        spr.c.g = 0xA0;
        spr.c.b = 0x96;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                x = g->flash[i].c2[j][k] % 4 * 32;
                y = (g->flash[i].c2[j][k] >> 2) * 32;
                ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t > 6 && g->t < 0x2D) {
        n = g->t % 16;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].pos = g->jp[0];
        for (k = 0; k < 16; k++) {
            g->spark[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[k], 1.0f);
        }
    }

    ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        spr.c.g = 0xA0;
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
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        alpha = (u32)(64.0f * func_0020B480((g->spark[i].t << 14) >> 4));
        spr.c.r = 0xFF;
        spr.c.g = 0x6A;
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
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 16) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 6) {
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
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0xA0;
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
        ((Line_b711_01E00080 *)(s32)&lp)->flags = 0x14;
        ((Line_b711_01E00080 *)(s32)&lp)->size = 8;
        ((Line_b711_01E00080 *)(s32)&lp)->regs = 0x41414141;
        ((Line_b711_01E00080 *)(s32)&lp)->pad4 = 0;
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
        lp.v[0].c.g = 0xA0;
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
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0xA0;
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
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
    case 0x8C:
        n = 0;
        break;
    case 0xA1:
        n = 1;
        break;
    case 0xBB:
        n = 2;
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
            func_00101080(&g->nova[g->nn].v2[k], 2.0f);
        }
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c2[k] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->nova[g->nn].v3[k], 2.5f);
        }
    }
    for (i = 0; i < 4; i++) {
        if (g->nova[i].on == 0) {
            continue;
        }
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 12.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
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
        spr.c.g = 0xA0;
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
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
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
        alpha = (32 - g->nova[i].t) * 228 >> 5;
        a2 = (32 - g->nova[i].t) * 128 >> 5;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->nova[i].t, 32, 1);
            if (k % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(0));
                spr.c.r = 0x80;
                spr.c.g = 0x40;
                spr.c.b = 0x20;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xFF;
                spr.c.g = 0x90;
                spr.c.b = 0x60;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->nova[i].v[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c[k] % 4 * 32;
            y = (g->nova[i].c[k] >> 2) * 32;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (u32)(255.0f * ((32 - g->nova[i].t) / 32.0f));
        spr.c.r = 0xFF;
        spr.c.g = 0x64;
        spr.c.b = 0x32;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 170.0f;
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
        ((Spr_b711_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b711_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b711_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b711_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b711_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 0;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b711_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b711_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
                spr.c.g = 0xA0;
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

    if (g->t == 5) {
        g->on4 = 1;
        g->t5 = 0;
    }
    if (g->on4 == 1) {
        ((Tri_b711_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b711_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b711_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b711_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b711_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        n = func_00207F60();
        func_00208460();
        D_01E05780_b711 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, b711_01E054B0);
        func_00208460();
        a = func_00101020(g->t5, 45.0f);
        b = func_00101020(g->t5, 45.0f);
        for (i = 0; i < 6; i++) {
            f = 1.0f + 0.15f * i / 5.0f - 0.075f;
            idx = ((i + 1) << 15) / 7;
            alpha = (u32)(a * (48.0f * func_0020B550(idx)));
            a2 = (u32)(b * (48.0f * func_0020B550(idx)));
            tri.v[0].c.r = 0x80;
            tri.v[0].c.g = 0x80;
            tri.v[0].c.b = 0x80;
            tri.v[0].c.a = alpha;
            tri.v[0].c.q = 1.0f;
            tri.v[1].c.r = 0x80;
            tri.v[1].c.g = 0x80;
            tri.v[1].c.b = 0x80;
            tri.v[1].c.a = a2;
            tri.v[1].c.q = 1.0f;
            tri.v[2].c = tri.v[1].c;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b711_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b711_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b711_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b711_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48((void *)&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
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

    if (g->t > 8 && g->t < 0xFB) {
        n = g->t % 32;
        g->bolt[n].on = 1;
        g->bolt[n].t = 0;
        for (k = 0; k < 64; k++) {
            g->bolt[n].life[k] = (u32)(32.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->bolt[n].ang[k] = (((func_0019A5C8() >> 23) % 256) << 16) >> 8;
            g->bolt[n].c[k][0] = (u32)(200.0f * (0.6f + 0.4f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->bolt[n].c[k][1] = (u32)(150.0f * (0.6f + 0.4f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->bolt[n].c[k][2] = (u32)(255.0f * (0.6f + 0.4f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
        }
    }
    ((Blade_b711_01E00080 *)(s32)&bl)->flags = 0x34;
    ((Blade_b711_01E00080 *)(s32)&bl)->size = 12;
    ((Blade_b711_01E00080 *)(s32)&bl)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Blade_b711_01E00080 *)(s32)&bl)->pad4 = 0;
    func_002086D0(&bl, func_00208D00(1));
    func_00208700(&bl, g->tex[0], 1);
    func_00208CB0(&bl, 5);
    a = (f32)func_00101050(g->t - 8, 0, 32) * (f32)func_00101050(0xFB - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 32; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        for (k = 0; k < 64; k++) {
            if (g->bolt[i].t > g->bolt[i].life[k]) {
                continue;
            }
            func_0020EB40(m);
            func_0020BBB0(m2);
            s = 6000.0f * g->bolt[i].t / g->bolt[i].life[k];
            x = g->bolt[i].ang[k];
            v.x = s - 3000.0f;
            f = 0.5f + 0.5f * k / 64.0f;
            h = 360.0f * f;
            v.y = 50.0f + h * func_0020B480(x);
            v.z = h * func_0020B550(x);
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_00100E00(m2, x, 0);
            func_0020BC00(m, m2);
            alpha = (u32)(a * (255.0f * func_00101020(g->bolt[i].t, 16.0f) * func_00100FF0(g->bolt[i].t, g->bolt[i].life[k], g->bolt[i].life[k] - 16)));
            bl.v[0].c.r = g->bolt[i].c[k][0];
            bl.v[0].c.g = g->bolt[i].c[k][1];
            bl.v[0].c.b = g->bolt[i].c[k][2];
            bl.v[0].c.a = alpha;
            bl.v[0].c.q = 1.0f;
            bl.v[1].c = bl.v[0].c;
            bl.v[2].c = bl.v[0].c;
            bl.v[3].c = bl.v[0].c;
            r = 20.0f * f;
            cn[0].x = 20.0f * -r;
            cn[0].y = 0.0f;
            cn[0].z = -r;
            cn[0].w = 1.0f;
            cn[1].x = 20.0f * -r;
            cn[1].y = 0.0f;
            cn[1].z = r;
            cn[1].w = 1.0f;
            cn[2].x = 20.0f * r;
            cn[2].y = 0.0f;
            cn[2].z = -r;
            cn[2].w = 1.0f;
            cn[3].x = 20.0f * r;
            cn[3].y = 0.0f;
            cn[3].z = r;
            cn[3].w = 1.0f;
            q = k % 8;
            s0 = 32.0f * (q % 4) / 128.0f;
            t0 = 32.0f * (q >> 2) / 64.0f;
            s1 = 0.25f + s0;
            t1 = 0.5f + t0;
            bl.v[0].s = s0;
            bl.v[0].t = t0;
            bl.v[1].s = s1;
            bl.v[1].t = t0;
            bl.v[2].s = s0;
            bl.v[2].t = t1;
            bl.v[3].s = s1;
            bl.v[3].t = t1;
            if (func_002058D0(cn, D_0030FF00, m, &bl, &depth) == 1) {
                func_002075F0(&bl, ot, 0xFFFFFF);
            }
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 32) {
            g->bolt[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x123 - g->t, 0, 8) * (func_00101050(g->t, 0, 8) * -128) >> 6) + 0x80));
    if (g->t == 0x82) {
        ret = 1;
    } else {
        if (g->t > 0x8C && g->t < 0xDB) {
            ret = 6;
        }
        if (g->t == 0xDB) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x123) {
        ret = 8;
    }
    return ret;
}
#pragma optimization_level reset

/* shape b711:01E054B0 (Gb711_GenAuraTex), 174 insns, 1 copy: draws an orange cover: a white 5-reg sprite packet (UVs
   0,0 to 640,448) then a flat 3-reg packet at (0xC8, 0x46, 0) alpha 0xE4 over the same rectangle, sent through the
   frame draw context */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b711_01E054B0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b711_01E054B0 v[2];
    u8 tail[8];
} Flat_b711_01E054B0;

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_b711_01E054B0;

typedef struct {
    Uv_b711_01E054B0 st;
    Xyz_b711_01E054B0 p;
} Tv_b711_01E054B0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b711_01E054B0 v[2];
    u8 tail[8];
} Spr_b711_01E054B0;

static void func_01E054B0_b711(void *ctx) {
    extern s32 func_00207650(s32, void *, s32, s32);
    Flat_b711_01E054B0 flat __attribute__((aligned(8)));
    Spr_b711_01E054B0 pk __attribute__((aligned(8)));
    s32 oA8[2];
    s32 oB0[3];

    ctx = func_00209F70(ctx, 0xFF000000);
    ((Spr_b711_01E054B0 *)(u32)&pk)->count = 0x26;
    ((Spr_b711_01E054B0 *)(u32)&pk)->n = 5;
    ((Spr_b711_01E054B0 *)(u32)&pk)->regs = 0x42421;
    ((Spr_b711_01E054B0 *)(u32)&pk)->pad4 = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, oA8, oB0));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Spr_b711_01E054B0 *)(u32)&pk)->count |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[0].st)->s = 0;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[0].st)->t = 0;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[1].st)->s = 0x2800;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[1].st)->t = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    ctx = (void *)func_00207650((s32)ctx, &pk, 0, 0);
    ((Flat_b711_01E054B0 *)(u32)&flat)->count = 6;
    ((Flat_b711_01E054B0 *)(u32)&flat)->n = 3;
    ((Flat_b711_01E054B0 *)(u32)&flat)->regs = 0x441;
    ((Flat_b711_01E054B0 *)(u32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0xC8;
    flat.g = 0x46;
    flat.b = 0;
    flat.a = 0xE4;
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

