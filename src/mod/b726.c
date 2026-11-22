#include "common.h"

/* shape b726:01E00080 (b726), 3642 insns, 1 copy (-O3,p): b726 scene manager, b725:01E00080's twin in violet with a
   wider spiral: flash, two joint-aimed spiral tubes with tip sprites, bursts, sparks and leaf quads, a render-target
   disc, a dim overlay and smoke puffs */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b726_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b726_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b726_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b726_01E00080 c;
    Xyz_b726_01E00080 v[2];
    u64 tail;
} Flat_b726_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b726_01E00080 c;
    Uv_b726_01E00080 uv0;
    Xyz_b726_01E00080 p0;
    Uv_b726_01E00080 uv1;
    Xyz_b726_01E00080 p1;
    u8 tail[0x20];
} Spr_b726_01E00080;

typedef struct {
    Rgbaq_b726_01E00080 c;
    union {
        Uv_b726_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b726_01E00080 p;
} Tv_b726_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b726_01E00080;

typedef struct {
    Reg_b726_01E00080 a;
    Reg_b726_01E00080 b;
} Tx_b726_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b726_01E00080 v[3];
    u64 pad58;
    Tx_b726_01E00080 tx;
    u64 tail;
} Tri_b726_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b726_01E00080 v[4];
    u64 pad70;
    Tx_b726_01E00080 tx;
    u64 tail;
} Quad_b726_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b726_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[16];
    u8 pad48[8];
    Vec4f v[16];
} Burst_b726_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][16];
    u8 pad28[8];
    Vec4f pos[2];
    Vec4f v[2][16];
} Spark_b726_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][20];
    s32 ang[2][20];
    Vec4f v[2][20];
} Leaf_b726_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][4];
    u8 padC[4];
    Vec4f pos[1];
    Vec4f v[1][4];
} Puff_b726_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f pos;
    Vec4f tgt;
    f32 h;
    s32 z;
    s32 joint;
    u8 pad4C[4];
    Vec4f jp;
    u8 on1;
    u8 pad61[3];
    s32 t1;
    u8 pad68[8];
    Mtx_b726_01E00080 mtx;
    f32 dist;
    u8 padB4[0xC];
    Vec4f ring[9];
    Vec4f tube[21][9];
    Vec4f tube2[21][9];
    Vec4f cen[2][21];
    u8 on2;
    u8 pad1B91[3];
    s32 t2;
    u8 pad1B98[8];
    Vec4f p[2];
    Vec4f q[2];
    Burst_b726_01E00080 burst[16];
    Spark_b726_01E00080 spark[16];
    f32 u[8][4];
    f32 vv[8][2];
    Vec4f l[4][2];
    Leaf_b726_01E00080 leaf[12];
    Vec4f disc[16][33];
    Vec4f disc2[16][33];
    u8 on4;
    u8 padC0E1[3];
    s32 t4;
    u8 padC0E8[8];
    Puff_b726_01E00080 puff[24];
} Scene_b726_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b726(s32 arg0, s32 code) {
    Scene_b726_01E00080 *g = (Scene_b726_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_002087A0(void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern s32 func_00101430(void *, void *, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00100E40(void *, void *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern s32 func_001F6EF0(void);
    extern void func_001F6590(s32, s32, void *);
    extern void b726_01E03970();
    extern s32 D_01E03C80_b726;
    extern f32 D_0028BC10[4][32][3];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 q;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 t0;
    f32 e;
    f32 a;
    f32 b;
    f32 f;
    f32 h;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b726_01E00080 m4;
    Vec4f v;
    Vec4f sc;
    Spr_b726_01E00080 spr __attribute__((aligned(8)));
    Flat_b726_01E00080 flat __attribute__((aligned(8)));
    Tri_b726_01E00080 tri __attribute__((aligned(8)));
    Quad_b726_01E00080 pk __attribute__((aligned(8)));
    Xyz_b726_01E00080 xyz;
    f32 depth;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC9F0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->h = 1.5f * func_001F5860(g->unitA);
        g->joint = func_001F5560(g->unitA, 0x35, 1);
        k = 0;
        g->on1 = k;
        g->on2 = 0;
        for (i = 0; i < 16; i++) {
            g->burst[i].on = 0;
        }
        for (k = 0; k < 16; k++) {
            g->spark[k].on = 0;
        }
        for (i = 0; i < 8; i++) {
            x = i % 4 * 32;
            for (j = 0; j < 4; j++) {
                g->u[i][j] = ((f32)x + 32.0f * j / 3.0f) / 128.0f;
            }
            g->vv[i][0] = (f32)((i >> 2) * 32) / 64.0f;
            g->vv[i][1] = (32.0f + (f32)((i >> 2) * 32)) / 64.0f;
        }
        for (i = 0; i < 4; i++) {
            x = (i << 15) / 3;
            g->l[i][0].x = 15.0f * func_0020B550(x);
            g->l[i][0].y = 10.0f;
            g->l[i][0].z = 15.0f * func_0020B480(x);
            g->l[i][0].w = 1.0f;
            g->l[i][1] = g->l[i][0];
            g->l[i][1].y *= -1.0f;
            r = 15.0f + -30.0f * i / 3.0f;
            g->l[i][0].y += r;
            g->l[i][1].y += r;
        }
        for (i = 0; i < 12; i++) {
            g->leaf[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            r = 40.0f * (16 - i) / 16.0f;
            for (j = 0; j < 33; j++) {
                x = (j << 16) >> 5;
                g->disc[i][j].x = r * func_0020B550(x);
                g->disc[i][j].y = r * func_0020B480(x);
                g->disc[i][j].z = 0.0f;
                g->disc[i][j].w = 1.0f;
            }
        }
        g->on4 = 0;
        for (i = 0; i < 24; i++) {
            g->puff[i].on = 0;
        }
        func_001F6590(g->unitB, 2, 0);
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = -g->h;
    v.w = 1.0f;
    func_001878E0(&v, m3, &v);
    func_00187B00(&v, &v, &g->pos);
    func_00205440(&v, m, &xyz, &depth);
    g->z = xyz.z;

    if (g->t == 0x82) {
        func_001F5620(g->unitA, g->joint, &g->jp);
    }
    func_00187B18(&v, &g->tgt, &g->jp);
    func_00100E40(&g->mtx, &v);
    func_00100E00(&g->mtx, 0x4000, 0);
    g->dist = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    if (g->t == 0x82) {
        g->on1 = 1;
        g->t1 = 0;
        g->on4 = 0;
    }
    if (g->on1 == 1) {
        ((Flat_b726_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b726_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b726_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b726_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->t1, 0x30, 1)));
        flat.c.r = 0xFF;
        flat.c.g = 0xF8;
        flat.c.b = 0xE8;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        flat.v[0].x = 0x6C00;
        flat.v[0].y = 0x7200;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t1++;
        if (g->t1 > 0x30) {
            k = 0;
        g->on1 = k;
        }
    }

    if (g->t == 0x82) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 2; i++) {
            x = (((i << 16) >> 1) + 0x4000) & 0xFFFF;
            g->p[i].x = 0.0f * func_0020B550(x);
            g->p[i].y = 0.0f;
            g->p[i].z = 0.0f * func_0020B480(x);
            g->p[i].w = 1.0f;
        }
    }
    if (g->on2 == 1) {
        func_00101050(g->t2, 0, 0x40);
        s = 1.0f;
        for (i = 0; i < 2; i++) {
            g->q[i] = g->p[i];
            h = 0.0f;
            g->q[i].z = h + s * (g->p[i].z - h);
        }
        x = func_00101050(g->t - 0x82, 0, 0x10);
        t0 = 17.0f * x / 16.0f;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 21; j++) {
                f = t0 * func_0020B550((j * 0x5555) / 20);
                x = (g->t2 * 0x16C + (i * 0x6301 + (j * 0x8000) / 20) + 0x4000) & 0xFFFF;
                g->cen[i][j].x = f * func_0020B550(x);
                g->cen[i][j].y = 0.0f;
                g->cen[i][j].z = f * func_0020B480(x);
                g->cen[i][j].w = 1.0f;
            }
        }
        h = g->dist * func_00100D50(func_00101050(g->t2, 0, 0x54), 0x54, 1);
        r = (f32)func_00101050(0xD0 - g->t2, 0, 0x20) / 32.0f;
        ((Quad_b726_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b726_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b726_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b726_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[2], 1);
        func_00208CB0(&pk, 0);
        pk.v[0].c.r = 0x9E;
        pk.v[0].c.g = 0x6C;
        pk.v[0].c.b = 0xC8;
        pk.v[0].c.a = 0x40;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        t0 = 5.0f * r;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = t0 * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = t0 * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mtx, &g->jp);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                f = h * j / 20.0f;
                for (y = 0; y < 9; y++) {
                    g->tube[j][y] = g->ring[y];
                    g->tube[j][y].y = f;
                    func_00187B00(&g->tube[j][y], &g->tube[j][y], &g->cen[i][j]);
                }
            }
            e = (f32)i / 2.0f - 2.0f * (g->t2 % 16) / 16.0f;
            for (j = 0; j < 20; j++) {
                b = 5.0f * j / 20.0f + e;
                s = 5.0f * (j + 1) / 20.0f + e;
                for (k = 0; k < 8; k++) {
                    pk.v[0].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[0].uv.st.t = b;
                    pk.v[1].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[1].uv.st.t = b;
                    pk.v[2].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[2].uv.st.t = s;
                    pk.v[3].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[3].uv.st.t = s;
                    if (func_00100BA0(&g->tube[j][k], &g->tube[j][k + 1], &g->tube[j + 1][k], &g->tube[j + 1][k + 1],
                                      m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b726_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b726_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b726_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b726_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tx.a, &pk.tx.b);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b726_01E00080 *)(s32)&pk)->flags |= 0x800;
        pk.v[0].c.r = 0x87;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x8A;
        pk.v[0].c.a = 0x80;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        t0 = 4.0f * r;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = t0 * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = t0 * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mtx, &g->jp);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                f = h * j / 20.0f;
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(910.0f * func_0020B550(((j << 16) / 20 + ((g->t2 + i * 5) % 64 << 16 >> 6)) & 0xFFFF)), 1);
                for (k = 0; k < 9; k++) {
                    g->tube[j][k] = g->ring[k];
                    g->tube[j][k].y = f;
                    func_00187B00(&g->tube[j][k], &g->tube[j][k], &g->cen[i][j]);
                    func_001878E0(&g->tube2[j][k], &m4, &g->ring[k]);
                    g->tube2[j][k].y = f + 0.2f * (h / 20.0f) * func_0020B550((((k << 16) >> 3) + ((g->t2 + i * 5) % 64 << 16 >> 6)) & 0xFFFF);
                    func_00187B00(&g->tube2[j][k], &g->tube2[j][k], &g->cen[i][j]);
                }
            }
            for (j = 0; j < 20; j++) {
                for (k = 0; k < 8; k++) {
                    if (func_00100BA0(&g->tube2[j][k], &g->tube2[j][k + 1], &g->tube2[j + 1][k],
                                      &g->tube2[j + 1][k + 1], m, &pk, &depth) == 1) {
                        func_00100C60(&pk.v[0].uv, &pk.v[0].p, 0, 0);
                        func_00100C60(&pk.v[1].uv, &pk.v[1].p, 0, 0);
                        func_00100C60(&pk.v[2].uv, &pk.v[2].p, 0, 0);
                        func_00100C60(&pk.v[3].uv, &pk.v[3].p, 0, 0);
                        if (func_00100BA0(&g->tube[j][k], &g->tube[j][k + 1], &g->tube[j + 1][k],
                                          &g->tube[j + 1][k + 1], m, &pk, &depth) == 1 &&
                            func_00101430(&pk.v[0].p, &pk.v[1].p, &pk.v[2].p) == 1) {
                            func_002075F0(&pk, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, 1);
        ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 0);
        alpha = (u32)(128.0f * ((f32)func_00101050(0xD0 - g->t2, 0, 0x20) / 32.0f));
        spr.c.r = 0x9E;
        spr.c.g = 0x6C;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 30.0f;
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        for (i = 0; i < 2; i++) {
            func_00187B00(&v, &g->cen[i][20], &g->q[i]);
            v.y += h;
            func_001878E0(&v, &g->mtx, &v);
            func_00187B00(&v, &g->jp, &v);
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m3, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t2++;
        if (g->t2 > 0xD0) {
            g->on2 = 0;
        }
    }

    if (g->t > 0xD6 && g->t < 0x152) {
        n = g->t % 16;
        g->burst[n].on = 1;
        g->burst[n].t = 1;
        for (i = 0; i < 16; i++) {
            g->burst[n].c[i] = (func_0019A5C8() >> 23) % 4 + 4;
            g->burst[n].v[i].x = 2.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].y = 2.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].z = 2.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].w = 1.0f;
        }
    }

    ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (16 - g->burst[i].t) * 128 >> 4;
        spr.c.r = 0x9E;
        spr.c.g = 0x6C;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 18.0f * (0.5f + 0.5f * g->burst[i].t / 16.0f);
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
        f = func_00100D50(g->burst[i].t, 0x10, 1);
        for (j = 0; j < 16; j++) {
            func_00187B48(&v, &g->burst[i].v[j], f);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c[j] % 4 * 32;
            y = (g->burst[i].c[j] >> 2) * 32;
            ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x10) {
            g->burst[i].on = 0;
        }
    }

    if (g->t > 0x82 && g->t < 0x152) {
        n = g->t % 16;
        g->spark[n].on = 1;
        g->spark[n].t = 1;
        for (i = 0; i < 2; i++) {
            g->spark[n].pos[i] = g->jp;
            for (j = 0; j < 16; j++) {
                g->spark[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[n].v[i][j], 1.2f);
            }
        }
    }

    ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        alpha = (16 - g->spark[i].t) * 0x30 >> 4;
        spr.c.r = 0x9E;
        spr.c.g = 0x6C;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.5f + 0.5f * g->spark[i].t / 16.0f);
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
        f = 0.2f + 0.8f * func_00100D50(g->spark[i].t, 0x10, 1);
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 16; k++) {
                func_00187B48(&v, &g->spark[i].v[j][k], f);
                func_00187B00(&v, &v, &g->spark[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[i].c[j][k] % 4 * 32;
                y = (g->spark[i].c[j][k] >> 2) * 32;
                ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 0x10) {
            g->spark[i].on = 0;
        }
    }

    if (g->t > 0x82) {
        if (g->t < 0x152) {
            n = g->t % 12;
            g->leaf[n].on = 1;
            g->leaf[n].t = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 20; j++) {
                    g->leaf[n].c[i][j] = (func_0019A5C8() >> 23) % 3 + 5;
                    g->leaf[n].ang[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
                    func_00101080(&g->leaf[n].v[i][j], 0.0f);
                    g->leaf[n].v[i][j].y *= 2.0f;
                }
            }
        }
    }

    ((Quad_b726_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b726_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b726_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b726_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 12; i++) {
        if (g->leaf[i].on == 0) {
            continue;
        }
        alpha = (12 - g->leaf[i].t) * 0x60 / 12;
        pk.v[0].c.r = 0xD0;
        pk.v[0].c.g = 0x8A;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.1f + 0.9f * g->leaf[i].t / 12.0f;
        sc.x = s;
        sc.y = s;
        sc.z = s;
        sc.w = 1.0f;
        f = g->dist * func_00100D50(func_00101050(g->t2 - 1, 0, 0x54), 0x54, 1);
        for (j = 0; j < 2; j++) {
            for (n = 0; n < 20; n++) {
                func_00187B00(&v, &g->cen[j][n + 1], &g->q[j]);
                func_00187B00(&v, &v, &g->leaf[i].v[j][n]);
                v.y += f * (n + 1) / 20.0f;
                func_001878E0(&v, &g->mtx, &v);
                func_00187B00(&v, &g->jp, &v);
                func_0020EB40(m);
                func_0020BBB0(m2);
                func_0020BC00(m2, &g->mtx);
                func_00187B60(m2, m2, &v);
                func_00100E00(m2, (g->leaf[i].ang[j][n] + g->leaf[i].t * 0x3E7) & 0xFFFF, 1);
                func_0020CB20(m2, &sc);
                func_0020BC00(m, m2);
                x = g->leaf[i].c[j][n];
                for (q = 0; q < 3; q++) {
                    pk.v[0].uv.st.s = g->u[x][q];
                    pk.v[0].uv.st.t = g->vv[x][0];
                    pk.v[1].uv.st.s = g->u[x][q + 1];
                    pk.v[1].uv.st.t = g->vv[x][0];
                    pk.v[2].uv.st.s = g->u[x][q];
                    pk.v[2].uv.st.t = g->vv[x][1];
                    pk.v[3].uv.st.s = g->u[x][q + 1];
                    pk.v[3].uv.st.t = g->vv[x][1];
                    if (func_00100BA0(&g->l[q][0], &g->l[q + 1][0], &g->l[q][1], &g->l[q + 1][1], m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        g->leaf[i].t++;
        if (g->leaf[i].t > 0xC) {
            g->leaf[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x182 - g->t, 0, 0x20) * (func_00101050(g->t, 0, 0x20) * -0x50) >> 10) + 0x80));

    if (g->t == 0x20) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t < 0x82) {
            ((Tri_b726_01E00080 *)(s32)&tri)->flags = 0x33;
            ((Tri_b726_01E00080 *)(s32)&tri)->size = 9;
            ((Tri_b726_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
            ((Tri_b726_01E00080 *)(s32)&tri)->pad4 = 0;
            ((Quad_b726_01E00080 *)(s32)&pk)->flags = 0x34;
            ((Quad_b726_01E00080 *)(s32)&pk)->size = 0xC;
            ((Quad_b726_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Quad_b726_01E00080 *)(s32)&pk)->pad4 = 0;
            buf = func_00207F60();
            func_00208460();
            D_01E03C80_b726 = (s32)g;
            func_001F7070(1, &tri.tx.a, &tri.tx.b, 0, b726_01E03970);
            pk.tx.a = tri.tx.a;
            pk.tx.b = tri.tx.b;
            func_00208460();
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->pos);
            func_0020BC00(m, m2);
            func_002086D0(&tri, func_00208D00(1));
            func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
            ((Tri_b726_01E00080 *)(s32)&tri)->flags |= 0x800;
            func_002086D0(&pk, func_00208D00(1));
            func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
            ((Quad_b726_01E00080 *)(s32)&pk)->flags |= 0x800;
            for (i = 0; i < 16; i++) {
                e = 20.0f * (16 - i) / 16.0f;
                for (j = 0; j < 33; j++) {
                    f = 1.0f + 0.5f * func_0020B550((g->t4 * 0xD05 + ((i * 0x30000 >> 4) + (j * 0x20000 >> 5))) & 0xFFFF);
                    x = (s32)((f32)((j << 16) >> 5) + 8192.0f * func_0020B550(((i * 0x30000 >> 4) + g->t4 * 0x8AE) & 0xFFFF)) & 0xFFFF;
                    g->disc2[i][j].x = e * f * func_0020B550(x);
                    g->disc2[i][j].y = e * f * func_0020B480(x);
                    g->disc2[i][j].z = 0.0f;
                    g->disc2[i][j].w = 1.0f;
                }
            }
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            a = (f32)func_00101050(g->t4, 0, 0x60);
            b = (f32)func_00101050(0x152 - g->t4, 0, 0x60);
            h = a * b / 9216.0f;
            for (i = 0; i < 16; i++) {
                if (i == 15) {
                    alpha = (u32)(h * (f32)(i * 0x80 / 17));
                    tri.v[0].c.r = 0x50;
                    tri.v[0].c.g = 0x40;
                    tri.v[0].c.b = 0xFF;
                    tri.v[0].c.a = alpha;
                    tri.v[0].c.q = 1.0f;
                    alpha = (u32)(h * (f32)((i - 1) * 0x80 / 17));
                    tri.v[1].c.r = 0x50;
                    tri.v[1].c.g = 0x40;
                    tri.v[1].c.b = 0xFF;
                    tri.v[1].c.a = alpha;
                    tri.v[1].c.q = 1.0f;
                    tri.v[2].c = tri.v[1].c;
                    for (k = 0; k < 32; k++) {
                        if (func_00100B00(&v, &g->disc2[i][k], &g->disc2[i][k + 1], m, &tri, &depth) == 1) {
                            func_00100C60(&tri.v[0].uv, &tri.v[0].p, 0, 0);
                            func_00100C60(&tri.v[1].uv, &tri.v[1].p, 0, 0);
                            func_00100C60(&tri.v[2].uv, &tri.v[2].p, 0, 0);
                            if (func_00100B00(&v, &g->disc[i][k], &g->disc[i][k + 1], m, &tri, &depth) == 1) {
                                tri.v[0].p.z = g->z;
                                tri.v[1].p.z = tri.v[0].p.z;
                                tri.v[2].p.z = tri.v[0].p.z;
                                func_002075F0(&tri, 0, 0);
                            }
                        }
                    }
                } else {
                    alpha = (u32)(h * (f32)(i * 0x80 / 17));
                    pk.v[0].c.r = 0x50;
                    pk.v[0].c.g = 0x40;
                    pk.v[0].c.b = 0xFF;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    alpha = (u32)(h * (f32)((i + 1) * 0x80 / 17));
                    pk.v[2].c.r = 0x50;
                    pk.v[2].c.g = 0x40;
                    pk.v[2].c.b = 0xFF;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                    for (k = 0; k < 32; k++) {
                        if (func_00100BA0(&g->disc2[i][k], &g->disc2[i][k + 1], &g->disc2[i + 1][k],
                                          &g->disc2[i + 1][k + 1], m, &pk, &depth) == 1) {
                            func_00100C60(&pk.v[0].uv, &pk.v[0].p, 0, 0);
                            func_00100C60(&pk.v[1].uv, &pk.v[1].p, 0, 0);
                            func_00100C60(&pk.v[2].uv, &pk.v[2].p, 0, 0);
                            func_00100C60(&pk.v[3].uv, &pk.v[3].p, 0, 0);
                            if (func_00100BA0(&g->disc[i][k], &g->disc[i][k + 1], &g->disc[i + 1][k],
                                              &g->disc[i + 1][k + 1], m, &pk, &depth) == 1) {
                                pk.v[0].p.z = g->z;
                                pk.v[1].p.z = pk.v[0].p.z;
                                pk.v[2].p.z = pk.v[0].p.z;
                                pk.v[3].p.z = pk.v[0].p.z;
                                func_002075F0(&pk, 0, 0);
                            }
                        }
                    }
                }
            }
            func_00207FD0(buf, ot, 0);
        }
        ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 0);
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos);
        func_0020BC00(m, m2);
        a = (f32)func_00101050(g->t4, 0, 0x60);
        h = a * (f32)func_00101050(0x152 - g->t4, 0, 0x60) / 9216.0f;
        alpha = (u32)(255.0f * h * (0.8f + 0.2f * (g->t4 % 2)));
        spr.c.r = 0x94;
        spr.c.g = 0x38;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 80.0f;
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        g->t4++;
        if (g->t4 > 0x152) {
            g->on4 = 0;
        }
    }

    a = (f32)func_00101050(g->t - 0x82, 0, 0x10);
    h = a * (f32)func_00101050(0x182 - g->t, 0, 0x10) / 256.0f;
    if (h > 0.0f) {
        ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = 0x190;
        ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = 0x110;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = 0x2670;
        ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = 0x1AF0;
        alpha = (u32)(64.0f * h);
        spr.c.r = 0x9E;
        spr.c.g = 0x80;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        spr.p0.x = 0x6C00;
        spr.p0.y = 0x7200;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x9400;
        spr.p1.y = 0x8E00;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, ot, 0);
    }

    if (g->t > 0xD6 && g->t < 0x186) {
        n = g->t % 24;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->puff[n].pos[i] = g->tgt;
            for (j = 0; j < 4; j++) {
                g->puff[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[i][j], 2.0f);
            }
        }
    }

    ((Spr_b726_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b726_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b726_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b726_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b726_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 24; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B550((g->puff[i].t << 15) / 24));
        spr.c.r = 0xC;
        spr.c.g = 8;
        spr.c.b = 8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.5f + 0.5f * g->puff[i].t / 24.0f);
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
        f = 0.4f + 0.6f * g->puff[i].t / 24.0f;
        a = -15.0f + 40.0f * g->puff[i].t / 24.0f;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 4; k++) {
                func_00187B48(&v, &g->puff[i].v[j][k], f);
                func_00187B00(&v, &v, &g->puff[i].pos[j]);
                v.y += a;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->puff[i].c[j][k] % 4 * 32;
                y = (g->puff[i].c[j][k] >> 2) * 32;
                ((Uv_b726_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b726_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 0x18) {
            g->puff[i].on = 0;
        }
    }

    if (func_001F6EF0() == 1) {
        if (g->t > 0xE6) {
            x = func_00101050(g->t - 0xE6, 0, 0x20) * 128 >> 5;
            col[2] = 0x80;
            col[1] = 0x80;
            col[0] = 0x80;
            col[3] = x;
            func_001F6590(g->unitB, 2, col);
        }
    }

    if (g->t == 0xCC) {
        ret = 1;
    } else {
        if (g->t > 0xD6 && g->t < 0x162) {
            ret = 6;
        }
        if (g->t == 0x162) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1BE) {
        ret = 8;
    }
    return ret;
}

/* shape b222:01E03780, 192 insns: draw a flat dark sprite (screen rect 0x6C00,0x7200 - 0x9400,0x8E00, far z) and a
   40x40 textured quad at the scene object's position whose texture scrolls with the object's counter (t =
   -(counter % 32) / 32); the quad is sent only when it projects fully on screen */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b222_01E03780;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b222_01E03780 v[2];
    u64 tail;
} Flat_b222_01E03780;

typedef struct {
    f32 s, t;
    Xyz_b222_01E03780 p;
} Tv_b222_01E03780;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b222_01E03780 v[2];
    u8 tail[0x20];
} Tex_b222_01E03780;

typedef struct {
    s32 counter;
    u8 pad4[0x14];
    void *texture;
    u8 pad1C[4];
    u8 pos[0x10];
} Obj_b222_01E03780;

extern Obj_b222_01E03780 *D_01E03C80_b726;
extern u8 D_0030FF00[];

static void func_01E03970_b726(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern void func_00205CA0(void *);
    extern u64 func_00208D00(s32);
    extern void *func_00207650(void *, void *, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    f32 m[4][4];
    f32 m2[4][4];
    f32 cam[4][4];
    Vec4f v[2];
    Flat_b222_01E03780 flat __attribute__((aligned(8)));
    Tex_b222_01E03780 pk __attribute__((aligned(8)));
    f32 depth;
    Obj_b222_01E03780 *o;
    void *p;
    f32 t;
    f32 w;

    o = D_01E03C80_b726;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0(cam);
    ((Flat_b222_01E03780 *)(s32)&flat)->flags = 6;
    ((Flat_b222_01E03780 *)(s32)&flat)->size = 3;
    ((Flat_b222_01E03780 *)(s32)&flat)->regs = 0x441;
    ((Flat_b222_01E03780 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(0));
    flat.r = 0;
    flat.g = 0;
    flat.b = 0;
    flat.a = 0x80;
    flat.q = 1.0f;
    flat.v[0].x = 0x6C00;
    flat.v[0].y = 0x7200;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x9400;
    flat.v[1].y = 0x8E00;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    p = func_00207650(p, &flat, 0, 0);
    ((Tex_b222_01E03780 *)(s32)&pk)->flags = 0x26;
    ((Tex_b222_01E03780 *)(s32)&pk)->size = 5;
    ((Tex_b222_01E03780 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b222_01E03780 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, o->texture, 1);
    func_00208CB0(&pk, 0);
    func_0020EB40(m);
    func_00187B60(m2, cam, o->pos);
    func_0020BC00((s32)m, m2);
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    t = (-1.0f * (o->counter % 32)) / 32.0f;
    w = 20.0f;
    pk.v[0].s = 0.0f;
    pk.v[0].t = t;
    pk.v[1].s = 5.0f;
    pk.v[1].t = 2.0f + t;
    v[0].x = -w;
    v[0].y = -w;
    v[0].z = 0.0f;
    v[0].w = 1.0f;
    v[1].x = w;
    v[1].y = w;
    v[1].z = 0.0f;
    v[1].w = 1.0f;
    if (func_00205630((s32)v, (s32)D_0030FF00, (s32)m, (s32)&pk, &depth) == 1) {
        pk.v[0].p.z = 0xFFFFF8;
        pk.v[1].p.z = pk.v[0].p.z;
        p = func_00207650(p, &pk, 0, 0);
    }
    func_00209F70(p, 0);
}
