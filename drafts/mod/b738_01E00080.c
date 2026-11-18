#include "common.h"

/* shape b738:01E00080 (b738), 5792 insns, 1 copy (-O3,p): b738 scene manager, b711/b216:01E00080's form (HARD draft):
   one comet at 0x61 with ember trails and flashes, 32 two-pass sparks, a nova and warp at 0x82, a dome table, 16
   slots of six fanned bolts spawned 0x62..0xB1, a beam at 0x61 and a render-to-texture aura from 0; returns 1 / 6 / 2
   / 8 at 0x78 / 0x83..0xB1 / 0xB2 / >0xD2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b738_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b738_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b738_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b738_01E00080 c;
    Uv_b738_01E00080 uv0;
    Xyz_b738_01E00080 p0;
    Uv_b738_01E00080 uv1;
    Xyz_b738_01E00080 p1;
    u8 tail[0x20];
} Spr_b738_01E00080;

typedef struct {
    Rgbaq_b738_01E00080 c;
    f32 s, t;
    Xyz_b738_01E00080 p;
} Tv_b738_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b738_01E00080 c;
        Uv_b738_01E00080 uv;
        Xyz_b738_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b738_01E00080;

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
} Comet_b738_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b738_01E00080;

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
} Flash_b738_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f pos;
    Vec4f v[16];
} Spark_b738_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f pos;
    Vec4f v[32];
} Smoke_b738_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b738_01E00080 c;
    Xyz_b738_01E00080 p0;
    Xyz_b738_01E00080 p1;
    u64 tail;
} Flat_b738_01E00080;

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
} Nova_b738_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life[1][6];
    f32 a[1][6];
    f32 b[1][6];
    f32 c[1][6];
    u8 pad68[8];
    f32 m[1][6][4][4];
} Bolt_b738_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p;
    Vec4f d;
    f32 len;
    f32 a[8];
    f32 b[8];
    u8 pad74[0xC];
    f32 m[8][4][4];
} Beam_b738_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b738_01E00080 v[4];
    u8 tail[0x20];
} Blade_b738_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    s32 jn[1];
    u8 pad28[8];
    Vec4f jp[1];
    s32 jn2[2];
    u8 pad48[8];
    Vec4f jp2[2];
    Vec4f pos;
    Vec4f scr;
    Vec4f tgt;
    Vec4f scr2;
    Vec4f mv;
    Vec4f sc;
    s32 nshot;
    s32 ncomet;
    u8 padD8[8];
    Comet_b738_01E00080 comet[1];
    Puff_b738_01E00080 trail[1][1][16];
    Smoke_b738_01E00080 smoke[1][1][16];
    s32 nflash;
    u8 pad2B24[0xC];
    Flash_b738_01E00080 flash[3];
    Spark_b738_01E00080 spark[32];
    u8 on2;
    u8 pad5B21[3];
    s32 t3;
    s32 nn;
    u8 pad5B2C[4];
    Nova_b738_01E00080 nova[3];
    u8 on4;
    u8 pad8DD1[3];
    s32 t5;
    u8 pad8DD8[8];
    Vec4f dome[17][17];
    u8 col[11][4];
    u8 padA01C[4];
    Bolt_b738_01E00080 bolt[16];
    u8 on3;
    u8 padBF21[3];
    s32 t4;
    s32 nbeam;
    u8 padBF2C[4];
    Beam_b738_01E00080 beam[1];
    u8 on5;
    u8 padC1B1[3];
    s32 t6;
    u8 padC1B8[8];
} Scene_b738_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b738(s32 arg0, s32 code) {
    Scene_b738_01E00080 *g = (Scene_b738_01E00080 *)arg0;
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
    extern void b738_01E05B00();
    extern s32 D_01E06080_b738;
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_00100E40(void *, void *);
    extern Vec4f *func_001F9AD0(s32);
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
    f32 e;
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
    Vec4f w;
    Blade_b738_01E00080 bl __attribute__((aligned(8)));
    Tri_b738_01E00080 tri __attribute__((aligned(8)));
    Spr_b738_01E00080 spr __attribute__((aligned(8)));
    Flat_b738_01E00080 fl __attribute__((aligned(8)));
    Xyz_b738_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC1C0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(4, 0xF);
        g->jn[0] = func_001F5560(g->unitA, 0x33, 1);
        g->jn2[0] = func_001F5560(g->unitA, 0x36, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x38, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->nshot = 0;
        g->ncomet = 0;
        for (i = 0; i < 1; i++) {
            g->comet[i].on = 0;
            g->comet[i].n = 0;
            g->comet[i].c = 0;
        }
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 1; i++) {
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
        for (i = 0; i < 32; i++) {
            g->spark[i].on = 0;
        }
        g->nn = 0;
        for (i = 0; i < 3; i++) {
            g->nova[i].on = 0;
        }
        g->on2 = 0;
        g->on4 = 0;
        for (i = 0; i < 17; i++) {
            f = 80.0f * func_0020B480((i << 15) >> 4);
            r = func_001A6C60(func_001A6C48(80.0f, 2.0f) - func_001A6C48(f, 2.0f));
            for (j = 0; j < 17; j++) {
                idx = (j << 16) >> 4;
                g->dome[i][j].x = r * func_0020B550(idx);
                g->dome[i][j].y = f;
                g->dome[i][j].z = r * func_0020B480(idx);
                g->dome[i][j].w = 1.0f;
            }
        }
        for (i = 0; i < 11; i++) {
            r = i / 10.0f;
            f = 1.0f - r;
            g->col[i][0] = (u32)(100.0f * f);
            g->col[i][1] = (u32)(70.0f * f);
            f = 255.0f * f;
            g->col[i][2] = (u32)(f + 128.0f * r);
            g->col[i][3] = (u32)f;
        }
        for (i = 0; i < 16; i++) {
            g->bolt[i].on = 0;
        }
        g->on3 = 0;
        g->t4 = 0;
        g->nbeam = 0;
        for (i = 0; i < 1; i++) {
            g->beam[i].on = 0;
        }
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
    a = (f32)func_00101050(g->t - 0x61, 0, 0x21) / 33.0f;
    func_00187B18(&v, &g->tgt, &g->jp[0]);
    func_00187B48(&v, &v, a);
    func_00187B00(&g->mv, &v, &g->jp[0]);
    s = 1.0f + 4.5f * func_00101050(g->t - 0x82, 0, 0x30) / 48.0f;
    g->sc.x = s;
    g->sc.y = s;
    g->sc.z = s;
    g->sc.w = 1.0f;
    e = 1.0f - func_00101050(g->t - 0x82, 0, 0x30) / 48.0f;
    if (g->t == 0x82) {
        g->on5 = 1;
        g->t6 = 0;
    }
    if (g->on5 == 1) {
        ((Flat_b738_01E00080 *)(s32)&fl)->flags = 6;
        ((Flat_b738_01E00080 *)(s32)&fl)->size = 3;
        ((Flat_b738_01E00080 *)(s32)&fl)->regs = 0x441;
        ((Flat_b738_01E00080 *)(s32)&fl)->pad4 = 0;
        func_002086D0(&fl, func_00208D00(0));
        x = (u32)(128.0f * ((24 - g->t6) / 24.0f));
        fl.c.r = 0xFF;
        fl.c.g = 0xE8;
        fl.c.b = 0xE0;
        fl.c.a = x;
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
        if (g->t6 > 24) {
            g->on5 = 0;
        }
    }
    if (g->t == 0x82) {
        g->on2 = 1;
        g->t3 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b738_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b738_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b738_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b738_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b738_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (48 - g->t3) * 64 / 48;
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0xFF;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            f = 1.0f + 0.2f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr2.x;
                y = (s32)g->scr2.y;
                ((Uv_b738_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b738_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b738_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        if (g->t3 > 48) {
            g->on2 = 0;
        }
    }
    n = -1;
    switch (g->t) {
    case 0x61:
        n = 0x21;
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
        if (g->ncomet >= 1) {
            g->ncomet = 0;
        }
        g->nflash++;
        if (g->nflash >= 3) {
            g->nflash = 0;
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 20.0f;
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
    for (i = 0; i < 1; i++) {
        if (g->comet[i].on == 0) {
            continue;
        }
        spr.c.r = 0xC8;
        spr.c.g = 0x78;
        spr.c.b = 0xFF;
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
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->trail[i][j][idx].on = 1;
            g->trail[i][j][idx].t = 0;
            g->trail[i][j][idx].pos = v;
            for (k = 0; k < 4; k++) {
                g->trail[i][j][idx].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->trail[i][j][idx].v[k], 0.8f);
            }
            g->smoke[i][j][n].on = 1;
            g->smoke[i][j][n].t = 0;
            g->smoke[i][j][n].pos = v;
            for (k = 0; k < 32; k++) {
                g->smoke[i][j][n].c[k] = (func_0019A5C8() >> 23) % 3;
                func_00101080(&g->smoke[i][j][n].v[k], 1.5f);
            }
        }
        g->comet[i].t++;
        if (g->comet[i].t > g->comet[i].life) {
            g->comet[i].on = 0;
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                if (g->trail[i][j][k].on == 0) {
                    continue;
                }
                r = 0.5f + 0.5f * (16 - g->trail[i][j][k].t) / 16.0f;
                r = 12.0f * r;
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
                spr.c.r = 0x64;
                spr.c.g = 0x46;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->trail[i][j][k].t, 16, 1);
                for (q = 0; q < 4; q++) {
                    x = g->trail[i][j][k].c[q] % 4 * 32;
                    y = (g->trail[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->trail[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->trail[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->trail[i][j][k].t++;
                if (g->trail[i][j][k].t > 16) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                if (g->smoke[i][j][k].on == 0) {
                    continue;
                }
                r = 1.5f * (0.5f + 0.5f * (16 - g->smoke[i][j][k].t) / 16.0f);
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
                spr.c.r = 0x64;
                spr.c.g = 0x46;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.1f + 0.9f * func_00100D50(g->smoke[i][j][k].t, 16, 1);
                for (q = 0; q < 32; q++) {
                    x = g->smoke[i][j][k].c[q] % 4 * 32;
                    y = (g->smoke[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->smoke[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->smoke[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->smoke[i][j][k].t++;
                if (g->smoke[i][j][k].t > 16) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 100.0f;
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
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->flash[i].t, 8, 1)));
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
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
        r = 10.0f * (0.5f + 0.5f * g->flash[i].t / 8.0f);
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
        alpha = (8 - g->flash[i].t) * 128 >> 3;
        spr.c.r = 0x7D;
        spr.c.g = 0x64;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 8, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                x = g->flash[i].c[j][k] % 4 * 32;
                y = (g->flash[i].c[j][k] >> 2) * 32;
                ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 2.0f * (0.5f + 0.5f * (8 - g->flash[i].t) / 8.0f);
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
        alpha = (8 - g->flash[i].t) * 255 >> 3;
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 8, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                x = g->flash[i].c2[j][k] % 4 * 32;
                y = (g->flash[i].c2[j][k] >> 2) * 32;
                ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v2[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->flash[i].t++;
        if (g->flash[i].t > 8) {
            g->flash[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x64) {
        n = g->t % 32;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].pos = g->jp[0];
        for (k = 0; k < 16; k++) {
            g->spark[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[k], 0.7f);
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 0.5f * (0.2f + 0.8f * (32 - g->spark[i].t) / 32.0f);
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
        alpha = (u32)(255.0f * func_0020B480((g->spark[i].t << 14) >> 5));
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->spark[i].t, 32, 1);
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[k] % 4 * 32;
            y = (g->spark[i].c[k] >> 2) * 32;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
        }
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 5.0f * (0.2f + 0.8f * g->spark[i].t / 32.0f);
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
        alpha = (u32)(64.0f * func_0020B480((g->spark[i].t << 14) >> 5));
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = -0.7f * (0.1f + 0.9f * func_00100D50(g->spark[i].t, 32, 1));
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = (g->spark[i].c[k] + 4) % 4 * 32;
            y = ((g->spark[i].c[k] + 4) >> 2) * 32;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, 0);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    n = -1;
    switch (g->t) {
    case 0x82:
        n = 0;
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
            func_00101080(&g->nova[g->nn].v[k], 2.7f);
        }
        for (k = 0; k < 128; k++) {
            func_00101080(&g->nova[g->nn].v2[k], 3.75f);
        }
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c2[k] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->nova[g->nn].v3[k], 2.7f);
        }
    }
    for (i = 0; i < 3; i++) {
        if (g->nova[i].on == 0) {
            continue;
        }
        ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 20.0f * (0.8f + 0.2f * g->nova[i].t / 48.0f);
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
        alpha = (48 - g->nova[i].t) * 100 / 48;
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->nova[i].t, 48, 1);
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->nova[i].v3[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c2[k] % 4 * 32;
            y = (g->nova[i].c2[k] >> 2) * 32;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->nova[i].t / 48.0f);
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
        alpha = (48 - g->nova[i].t) * 255 / 48;
        a2 = (48 - g->nova[i].t) * 128 / 48;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->nova[i].t, 48, 1);
            if (k % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xFF;
                spr.c.b = 0x40;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x64;
                spr.c.g = 0x46;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->nova[i].v[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c[k] % 4 * 32;
            y = (g->nova[i].c[k] >> 2) * 32;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->nova[i].pos);
        s = 0.2f + 0.8f * func_00100D50(g->nova[i].t, 48, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((48 - g->nova[i].t) / 48.0f));
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 200.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 0;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        h = (48 - g->nova[i].t) / 48.0f;
        s = func_00100D50(g->nova[i].t, 48, 1);
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 6; k++) {
                alpha = (u32)(h * ((k + 6) * 255 / 12));
                spr.c.r = 0xC8;
                spr.c.g = 0x64;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->nova[i].v2[j], s + 0.007f * k);
                func_00187B00(&v, &v, &g->nova[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->nova[i].t++;
        if (g->nova[i].t > 48) {
            g->nova[i].on = 0;
        }
    }

    ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x600;
    ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    s = (f32)func_00101050(g->t - 0x15, 0, 8) * (f32)func_00101050(0x30 - g->t, 0, 8) / 64.0f;
    if (s > 0.0f) {
        alpha = (u32)(255.0f * s * (0.8f + 0.2f * (g->t % 2)));
        spr.c.r = 0xFF;
        spr.c.g = 0x64;
        spr.c.b = 0x46;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f;
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
        w = *func_001F9AD0(0);
        v = w.x * g->obj < 0.0f ? g->jp2[0] : g->jp2[1];
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
    }

    if (g->t == 0) {
        g->on4 = 1;
        g->t5 = 0;
    }
    if (g->on4 == 1) {
        ((Tri_b738_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b738_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b738_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b738_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b738_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        n = func_00207F60();
        func_00208460();
        D_01E06080_b738 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, b738_01E05B00);
        func_00208460();
        a = func_00101020(g->t5, 48.0f) * func_00100FF0(g->t5, 171.0f, 123.0f);
        b = func_00101020(g->t5, 48.0f) * func_00100FF0(g->t5, 171.0f, 123.0f);
        a = 128.0f * a;
        b = 128.0f * b;
        for (i = 0; i < 1; i++) {
            alpha = (u32)a;
            (void)alpha;
            a2 = (u32)b;
            (void)a2;
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
                ((Uv_b738_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b738_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b738_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b738_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48((void *)&out[0], &out[0], 1.0f);
                func_00187B48(&out[1], &out[1], 1.0f);
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
        if (g->t5 > 0xAB) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x61) {
        g->on3 = 1;
        g->t4 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b738_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b738_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b738_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b738_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b738_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->mv);
        func_0020CB20(m2, &g->sc);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (0.7f + 0.3f * (g->t4 % 2)) * e);
        spr.c.r = 0x64;
        spr.c.g = 0x46;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 45.0f;
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
        x = 0;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b738_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b738_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        for (j = 0; j < 1; j++) {
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t4++;
        if (g->t4 > 0x51) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x61 && g->t < 0xB2) {
        n = g->t % 16;
        g->bolt[n].on = 1;
        g->bolt[n].t = 0;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 6; k++) {
                g->bolt[n].life[j][k] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->bolt[n].a[j][k] = 2.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->bolt[n].b[j][k] = 30.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->bolt[n].c[j][k] = 6.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                func_00101080(&v, 1.0f);
                func_00100E40(g->bolt[n].m[j][k], &v);
                func_00100E00(g->bolt[n].m[j][k], (k << 16) / 6, 2);
            }
        }
    }
    ((Blade_b738_01E00080 *)(s32)&bl)->flags = 0x34;
    ((Blade_b738_01E00080 *)(s32)&bl)->size = 12;
    ((Blade_b738_01E00080 *)(s32)&bl)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Blade_b738_01E00080 *)(s32)&bl)->pad4 = 0;
    func_002086D0(&bl, func_00208D00(1));
    func_00208700(&bl, g->tex[4], 1);
    func_00208CB0(&bl, ((u64)0x1FC << 32) | 0x12340BA);
    for (i = 0; i < 16; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 6; k++) {
                if (g->bolt[i].t > g->bolt[i].life[j][k]) {
                    continue;
                }
                func_0020EB40(m);
                func_0020C940(m2, 0, 0, &g->mv);
                func_0020BC00(m2, g->bolt[i].m[j][k]);
                func_0020CB20(m2, &g->sc);
                func_0020BC00(m, m2);
                f = 1.0f - func_00100D50(g->bolt[i].t, g->bolt[i].life[j][k], 1);
                s1 = 1.0f + (1.0f - f);
                for (q = 0; q < 10; q++) {
                    alpha = (u32)(e * (g->col[q][3] * f));
                    a2 = (u32)(e * (g->col[q + 1][3] * f));
                    bl.v[0].c.r = g->col[q][0];
                    bl.v[0].c.g = g->col[q][1];
                    bl.v[0].c.b = g->col[q][2];
                    bl.v[0].c.a = alpha;
                    bl.v[0].c.q = 1.0f;
                    bl.v[2].c.r = g->col[q + 1][0];
                    bl.v[2].c.g = g->col[q + 1][1];
                    bl.v[2].c.b = g->col[q + 1][2];
                    bl.v[2].c.a = a2;
                    bl.v[2].c.q = 1.0f;
                    bl.v[1].c = bl.v[0].c;
                    bl.v[3].c = bl.v[2].c;
                    x = q % 4;
                    t0 = 0.5f * x / 4.0f;
                    t1 = 0.5f * (x + 1) / 4.0f;
                    bl.v[0].s = 0.0390625f;
                    bl.v[0].t = t0;
                    bl.v[1].s = 0.2109375f;
                    bl.v[2].s = 0.0390625f;
                    bl.v[2].t = t1;
                    bl.v[1].t = t0;
                    bl.v[3].s = 0.2109375f;
                    bl.v[3].t = t1;
                    a = g->bolt[i].b[j][k] * q / 10.0f;
                    h = g->bolt[i].b[j][k] * (q + 1) / 10.0f;
                    b = f * (g->bolt[i].a[j][k] * (10 - q) / 10.0f);
                    s0 = f * (g->bolt[i].a[j][k] * (10 - (q + 1)) / 10.0f);
                    r = s1 * (g->bolt[i].c[j][k] * func_0020B550(((q << 16) / 10) & 0xFFFF));
                    s = s1 * (g->bolt[i].c[j][k] * func_0020B550((((q + 1) << 16) / 10) & 0xFFFF));
                    cn[0].x = r;
                    cn[0].y = -b + r;
                    cn[0].z = a;
                    cn[0].w = 1.0f;
                    cn[1].x = r;
                    cn[1].y = b + r;
                    cn[1].z = a;
                    cn[1].w = 1.0f;
                    cn[2].x = s;
                    cn[2].y = -s0 + s;
                    cn[2].z = h;
                    cn[2].w = 1.0f;
                    cn[3].x = s;
                    cn[3].y = s0 + s;
                    cn[3].z = h;
                    cn[3].w = 1.0f;
                    if (func_002058D0(cn, D_0030FF00, m, &bl, &depth) == 1) {
                        func_002075F0(&bl, ot, (u32)depth);
                    }
                }
            }
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 16) {
            g->bolt[i].on = 0;
        }
    }

    if (g->t == 0x61) {
        n = g->nbeam;
        g->beam[n].on = 1;
        g->beam[n].t = 0;
        g->beam[n].p = g->jp[0];
        func_00187B18(&g->beam[n].d, &g->tgt, &g->beam[n].p);
        g->beam[n].len = func_001A6C60(func_001A6C48(g->beam[n].d.x, 2.0f) + func_001A6C48(g->beam[n].d.y, 2.0f) +
                                       func_001A6C48(g->beam[n].d.z, 2.0f));
        for (k = 0; k < 8; k++) {
            g->beam[n].a[k] = 3.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->beam[n].b[k] = 8.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            func_00100E40(g->beam[n].m[k], &g->beam[n].d);
            func_00100E00(g->beam[n].m[k], (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
        }
        g->nbeam++;
        if (g->nbeam >= 1) {
            g->nbeam = 0;
        }
    }
    ((Blade_b738_01E00080 *)(s32)&bl)->flags = 0x34;
    ((Blade_b738_01E00080 *)(s32)&bl)->size = 12;
    ((Blade_b738_01E00080 *)(s32)&bl)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Blade_b738_01E00080 *)(s32)&bl)->pad4 = 0;
    func_002086D0(&bl, func_00208D00(1));
    func_00208700(&bl, g->tex[4], 1);
    func_00208CB0(&bl, ((u64)0x1FC << 32) | 0x12340BA);
    for (i = 0; i < 1; i++) {
        if (g->beam[i].on == 0) {
            continue;
        }
        q = (s32)(16.0f * func_00101020(g->beam[i].t, 33.0f));
        if (q > 16) {
            q = 16;
        }
        a = (64 - g->beam[i].t) / 64.0f;
        alpha = (u32)(164.0f * a);
        bl.v[0].c.r = 0x32;
        bl.v[0].c.g = 0x23;
        bl.v[0].c.b = 0xFF;
        bl.v[0].c.a = alpha;
        bl.v[0].c.q = 1.0f;
        f = 1.0f + 1.5f * (1.0f - a);
        bl.v[1].c = bl.v[0].c;
        bl.v[2].c = bl.v[0].c;
        bl.v[3].c = bl.v[0].c;
        for (k = 0; k < 8; k++) {
            func_0020EB40(m);
            func_00187B60(m2, g->beam[i].m[k], &g->beam[i].p);
            func_0020BC00(m, m2);
            idx = i * 0x15B3 + k * 0x1A0A;
            for (n = 0; n < q; n++) {
                x = n % 2;
                t0 = 0.5f * x / 2.0f;
                bl.v[0].s = 0.0390625f;
                t1 = 0.5f * (x + 1) / 2.0f;
                bl.v[0].t = t0;
                bl.v[1].s = 0.2109375f;
                bl.v[2].s = 0.0390625f;
                bl.v[3].s = 0.2109375f;
                bl.v[1].t = t0;
                bl.v[3].t = t1;
                s0 = g->beam[i].len * n / 16.0f;
                h = g->beam[i].len * (n + 1) / 16.0f;
                bl.v[2].t = t1;
                s1 = g->beam[i].a[k] * a;
                r = f * (g->beam[i].b[k] * func_0020B480((((n << 16) >> 4) + idx) & 0xFFFF));
                s = f * (g->beam[i].b[k] * func_0020B480((((n + 1 << 16) >> 4) + idx) & 0xFFFF));
                out[0].x = 0.0f;
                out[0].y = -s1 + r;
                out[0].z = s0;
                out[0].w = 1.0f;
                out[1].x = 0.0f;
                out[1].y = s1 + r;
                out[1].z = s0;
                out[1].w = 1.0f;
                out[2].x = 0.0f;
                out[2].y = -s1 + s;
                out[2].z = h;
                out[2].w = 1.0f;
                out[3].x = 0.0f;
                out[3].y = s1 + s;
                out[3].z = h;
                out[3].w = 1.0f;
                if (func_002058D0(out, D_0030FF00, m, &bl, &depth) == 1) {
                    func_002075F0(&bl, ot, (u32)depth);
                }
            }
        }
        g->beam[i].t++;
        if (g->beam[i].t > 64) {
            g->beam[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0xD2 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x78) {
        ret = 1;
    } else {
        if (g->t > 0x82 && g->t < 0xB2) {
            ret = 6;
        }
        if (g->t == 0xB2) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xD2) {
        ret = 8;
    }
    return ret;
}
#pragma optimization_level reset
