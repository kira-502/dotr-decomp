#include "common.h"

/* shape b222:01E00080 (b222), 3517 insns, 1 copy (-O3,p): b222 scene manager: a white flash, twin spiral tubes rising
   from the target, bursts, sparks and leaf quads along them, a rippling water grid, a render-target disc and a dim
   screen overlay */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b222_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b222_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b222_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b222_01E00080 c;
    Xyz_b222_01E00080 v[2];
    u64 tail;
} Flat_b222_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b222_01E00080 c;
    Uv_b222_01E00080 uv0;
    Xyz_b222_01E00080 p0;
    Uv_b222_01E00080 uv1;
    Xyz_b222_01E00080 p1;
    u8 tail[0x20];
} Spr_b222_01E00080;

typedef struct {
    Rgbaq_b222_01E00080 c;
    union {
        Uv_b222_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b222_01E00080 p;
} Tv_b222_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b222_01E00080;

typedef struct {
    Reg_b222_01E00080 a;
    Reg_b222_01E00080 b;
} Tx_b222_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b222_01E00080 v[3];
    u64 pad58;
    Tx_b222_01E00080 tx;
    u64 tail;
} Tri_b222_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b222_01E00080 v[4];
    u64 pad70;
    Tx_b222_01E00080 tx;
    u64 tail;
} Quad_b222_01E00080;

typedef struct {
    union {
        Uv_b222_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b222_01E00080 p;
} Txv_b222_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b222_01E00080 c;
    Txv_b222_01E00080 v[4];
    u8 tail[0x20];
} Tex_b222_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b222_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[16];
    u8 pad48[8];
    Vec4f v[16];
} Burst_b222_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][32];
    u8 pad48[8];
    Vec4f pos[2];
    Vec4f v[2][32];
} Spark_b222_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][20];
    s32 ang[2][20];
    Vec4f v[2][20];
} Leaf_b222_01E00080;

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
    u8 on1;
    u8 pad49[3];
    s32 t1;
    Vec4f ring[9];
    Vec4f tube[21][9];
    Vec4f tube2[21][9];
    Vec4f cen[2][21];
    u8 on2;
    u8 pad1B21[3];
    s32 t2;
    u8 pad1B28[8];
    Vec4f p[2];
    Vec4f q[2];
    Burst_b222_01E00080 burst[16];
    Vec4f grid[17][17];
    s32 ph[17][17];
    u8 on3;
    u8 pad4705[3];
    s32 t3;
    u8 pad470C[4];
    Spark_b222_01E00080 spark[16];
    f32 u[8][4];
    f32 vv[8][2];
    Vec4f l[4][2];
    Leaf_b222_01E00080 leaf[12];
    Vec4f disc[16][33];
    Vec4f disc2[16][33];
    u8 on4;
    u8 padF911[3];
    s32 t4;
    u8 padF918[8];
} Scene_b222_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b222(s32 arg0, s32 code) {
    Scene_b222_01E00080 *g = (Scene_b222_01E00080 *)arg0;
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
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern void b222_01E03780();
    extern s32 D_01E03B00_b222;
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
    f32 t1;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b222_01E00080 m4;
    Vec4f v;
    Vec4f sc;
    Spr_b222_01E00080 spr __attribute__((aligned(8)));
    Flat_b222_01E00080 flat __attribute__((aligned(8)));
    Tri_b222_01E00080 tri __attribute__((aligned(8)));
    Quad_b222_01E00080 pk __attribute__((aligned(8)));
    Tex_b222_01E00080 tx __attribute__((aligned(8)));
    Xyz_b222_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xF920);
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
        g->on1 = 0;
        g->on2 = 0;
        for (i = 0; i < 16; i++) {
            g->burst[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            f = 600.0f * i / 16.0f;
            for (j = 0; j < 17; j++) {
                s = 600.0f * j / 16.0f;
                g->grid[i][j].x = f - 300.0f;
                g->grid[i][j].y = 0.0f;
                g->grid[i][j].z = s - 300.0f;
                g->grid[i][j].w = 1.0f;
                g->ph[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        k = 0;
        g->on3 = k;
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
            g->l[i][0].x = 25.0f * func_0020B550(x);
            g->l[i][0].y = 12.0f;
            g->l[i][0].z = 25.0f * func_0020B480(x);
            g->l[i][0].w = 1.0f;
            g->l[i][1] = g->l[i][0];
            g->l[i][1].y *= -1.0f;
            r = 12.5f + -25.0f * i / 3.0f;
            g->l[i][0].y += r;
            g->l[i][1].y += r;
        }
        for (i = 0; i < 12; i++) {
            g->leaf[i].on = 0;
        }
        for (j = 0; j < 16; j++) {
            r = 40.0f * (16 - j) / 16.0f;
            for (k = 0; k < 33; k++) {
                x = (k << 16) >> 5;
                g->disc[j][k].x = r * func_0020B550(x);
                g->disc[j][k].y = r * func_0020B480(x);
                g->disc[j][k].z = 0.0f;
                g->disc[j][k].w = 1.0f;
            }
        }
        g->on4 = 0;
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

    if (g->t == 0x42) {
        g->on1 = 1;
        g->t1 = 0;
        g->on4 = 0;
    }
    if (g->on1 == 1) {
        ((Flat_b222_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b222_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b222_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b222_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(200.0f * (1.0f - func_00100D50(g->t1, 0x18, 1)));
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
        if (g->t1 > 0x18) {
            g->on1 = 0;
        }
    }

    if (g->t == 0x42) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 2; i++) {
            x = (((i << 16) >> 1) + 0x4000) & 0xFFFF;
            g->p[i].x = 12.0f * func_0020B550(x);
            g->p[i].y = 8.0f;
            g->p[i].z = 12.0f * func_0020B480(x);
            g->p[i].w = 1.0f;
            g->p[i].x += g->tgt.x;
            g->p[i].z += g->tgt.z;
        }
    }
    if (g->on2 == 1) {
        e = (f32)func_00101050(g->t2, 0, 100) / 100.0f;
        func_00101050(g->t2, 0, 0x40);
        for (i = 0; i < 2; i++) {
            g->q[i] = g->p[i];
            h = 70.0f * (f32)g->obj;
            g->q[i].z = h + e * (g->p[i].z - h);
        }
        x = func_00101050(g->t - 0x42, 0, 0x10);
        t0 = 12.0f * x / 16.0f;
        for (i = 0; i < 2; i++) {
            for (k = 0; k < 21; k++) {
                x = (g->t2 * 0x222 + (i * 0x6301 + (k * 0x8000) / 20) + 0x6AAA) & 0xFFFF;
                g->cen[i][k].x = t0 * func_0020B550(x);
                g->cen[i][k].y = 0.0f;
                g->cen[i][k].z = t0 * func_0020B480(x);
                g->cen[i][k].w = 1.0f;
            }
        }
        h = 130.0f * func_00100D50(func_00101050(g->t2, 0, 0x10), 0x10, 1);
        f = (f32)func_00101050(0x100 - g->t2, 0, 0x20) / 32.0f;
        ((Quad_b222_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b222_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b222_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b222_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[2], 1);
        func_00208CB0(&pk, 0);
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0xB2;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = 0x40;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        t0 = 10.0f * f;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = t0 * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = t0 * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->q[i]);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                r = h * j / 20.0f;
                for (y = 0; y < 9; y++) {
                    g->tube[j][y] = g->ring[y];
                    g->tube[j][y].y = r;
                    func_00187B00(&g->tube[j][y], &g->tube[j][y], &g->cen[i][j]);
                }
            }
            t1 = (f32)i / 2.0f - 2.0f * (g->t2 % 16) / 16.0f;
            for (j = 0; j < 20; j++) {
                r = 5.0f * j / 20.0f + t1;
                e = 5.0f * (j + 1) / 20.0f + t1;
                for (k = 0; k < 8; k++) {
                    pk.v[0].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[0].uv.st.t = r;
                    pk.v[1].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[1].uv.st.t = r;
                    pk.v[2].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[2].uv.st.t = e;
                    pk.v[3].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[3].uv.st.t = e;
                    if (func_00100BA0(&g->tube[j][k], &g->tube[j][k + 1], &g->tube[j + 1][k], &g->tube[j + 1][k + 1],
                                      m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b222_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b222_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b222_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b222_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tx.a, &pk.tx.b);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b222_01E00080 *)(s32)&pk)->flags |= 0x800;
        pk.v[0].c.r = 0x74;
        pk.v[0].c.g = 0x7C;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = 0x80;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        t0 = 9.5f * f;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = t0 * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = t0 * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->q[i]);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                r = h * j / 20.0f;
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(910.0f * func_0020B550(((j << 16) / 20 + ((g->t2 + i * 5) % 64 << 16 >> 6)) & 0xFFFF)), 1);
                for (k = 0; k < 9; k++) {
                    g->tube[j][k] = g->ring[k];
                    g->tube[j][k].y = r;
                    func_00187B00(&g->tube[j][k], &g->tube[j][k], &g->cen[i][j]);
                    func_001878E0(&g->tube2[j][k], &m4, &g->ring[k]);
                    g->tube2[j][k].y = r + 0.3f * (h / 20.0f) * func_0020B550((((k << 16) >> 3) + ((g->t2 + i * 5) % 64 << 16 >> 6)) & 0xFFFF);
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
        g->t2++;
        if (g->t2 > 0x100) {
            g->on2 = 0;
        }
    }

    if (g->t > 0xA2 && g->t < 0x142) {
        n = g->t % 16;
        g->burst[n].on = 1;
        g->burst[n].t = 1;
        for (i = 0; i < 16; i++) {
            g->burst[n].c[i] = (func_0019A5C8() >> 23) % 8;
            g->burst[n].v[i].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->burst[n].v[i].w = 1.0f;
        }
    }

    ((Spr_b222_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b222_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b222_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b222_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b222_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (16 - g->burst[i].t) * 0x56 >> 4;
        spr.c.r = 0x80;
        spr.c.g = 0xA8;
        spr.c.b = 0xB2;
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
            ((Uv_b222_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b222_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b222_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b222_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x10) {
            g->burst[i].on = 0;
        }
    }

    if (g->t > 0x42 && g->t < 0x142) {
        n = g->t % 16;
        g->spark[n].on = 1;
        g->spark[n].t = 1;
        for (i = 0; i < 2; i++) {
            func_00187B00(&g->spark[n].pos[i], &g->cen[i][1], &g->q[i]);
            for (j = 0; j < 32; j++) {
                g->spark[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[n].v[i][j], 2.0f);
                g->spark[n].v[i][j].y = 0.8f * func_001A6970(g->spark[n].v[i][j].y);
            }
        }
    }

    ((Spr_b222_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b222_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b222_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b222_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b222_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (16 - g->spark[i].t) * 0x38 >> 4;
        spr.c.r = 0x80;
        spr.c.g = 0xA8;
        spr.c.b = 0xB2;
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
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->spark[i].v[j][k], f);
                func_00187B00(&v, &v, &g->spark[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[i].c[j][k] % 4 * 32;
                y = (g->spark[i].c[j][k] >> 2) * 32;
                ((Uv_b222_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b222_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b222_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b222_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t > 0x42) {
        if (g->t < 0x142) {
            n = g->t % 12;
            g->leaf[n].on = 1;
            g->leaf[n].t = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 20; j++) {
                    g->leaf[n].c[i][j] = (func_0019A5C8() >> 23) % 3 + 5;
                    g->leaf[n].ang[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
                    func_00101080(&g->leaf[n].v[i][j], 0.5f);
                    g->leaf[n].v[i][j].y *= 2.0f;
                }
            }
        }
    }

    ((Quad_b222_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b222_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b222_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b222_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 12; i++) {
        if (g->leaf[i].on == 0) {
            continue;
        }
        alpha = (12 - g->leaf[i].t) * 0x76 / 12;
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0xA8;
        pk.v[0].c.b = 0xB2;
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
        for (j = 0; j < 2; j++) {
            for (n = 0; n < 20; n++) {
                func_00187B00(&v, &g->cen[j][n], &g->q[j]);
                func_00187B00(&v, &v, &g->leaf[i].v[j][n]);
                v.y += 130.0f * n / 20.0f;
                func_0020EB40(m);
                func_0020BBB0(m2);
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

    if (g->t == 0) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tex_b222_01E00080 *)(s32)&tx)->flags = 0x24;
        ((Tex_b222_01E00080 *)(s32)&tx)->size = 9;
        ((Tex_b222_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b222_01E00080 *)(s32)&tx)->pad4 = 0;
        func_002086D0(&tx, func_00208D00(0));
        func_00208700(&tx, g->tex[2], 1);
        func_00208CB0(&tx, 0);
        f = func_00101020((f32)g->t3, 32.0f);
        a = f * func_00100FF0((f32)g->t3, 386.0f, 354.0f);
        for (y = 0; y < 1; y++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 15.0f - 2.0f * (7.0f * y);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (y == 0) {
                alpha = (u32)(100.0f * a);
            } else {
                alpha = (u32)(80.0f * a);
            }
            tx.c.r = 0x50;
            tx.c.g = 0xD2;
            tx.c.b = 0xFF;
            tx.c.a = alpha;
            tx.c.q = 1.0f;
            for (j = 0; j < 17; j++) {
                for (k = 0; k < 17; k++) {
                    g->grid[j][k].y = 7.0f * func_0020B550((g->ph[j][k] + y * 0x33333 + g->t3 * 0x29A) & 0xFFFF);
                }
            }
            x = ((y % 2 * 2 - 1) * ((g->t3 + y * 0x20) % 128 << 16 >> 7)) & 0xFFFF;
            f = 0.2f * func_0020B550(x);
            e = 0.2f * func_0020B480(x);
            for (j = 0; j < 16; j++) {
                n = j % 2;
                h = (f32)n / 2.0f;
                r = (f32)(n + 1) / 2.0f;
                t0 = h + e;
                t1 = r + e;
                for (k = 0; k < 16; k++) {
                    n = k % 2;
                    s = (f32)n / 2.0f;
                    h = (f32)(n + 1) / 2.0f;
                    s0 = s + f;
                    s1 = h + f;
                    tx.v[0].uv.st.s = s0;
                    tx.v[0].uv.st.t = t0;
                    tx.v[1].uv.st.s = s1;
                    tx.v[1].uv.st.t = t0;
                    tx.v[2].uv.st.s = s0;
                    tx.v[2].uv.st.t = t1;
                    tx.v[3].uv.st.s = s1;
                    tx.v[3].uv.st.t = t1;
                    if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k], &g->grid[j + 1][k + 1],
                                      m, &tx, &depth) == 1) {
                        func_002075F0(&tx, ot, (u32)depth);
                    }
                }
            }
        }
        g->t3++;
        if (g->t3 > 0x182) {
            g->on3 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x182 - g->t, 0, 0x20) * (func_00101050(g->t, 0, 0x20) * -0x40) >> 10) + 0x80));

    if (g->t == 0) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        ((Tri_b222_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b222_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b222_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b222_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Quad_b222_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b222_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b222_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b222_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        D_01E03B00_b222 = (s32)g;
        func_001F7070(1, &tri.tx.a, &tri.tx.b, 0, b222_01E03780);
        pk.tx.a = tri.tx.a;
        pk.tx.b = tri.tx.b;
        func_00208460();
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos);
        func_0020BC00(m, m2);
        func_002086D0(&tri, func_00208D00(1));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        ((Tri_b222_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&pk, func_00208D00(1));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b222_01E00080 *)(s32)&pk)->flags |= 0x800;
        for (i = 0; i < 16; i++) {
            e = 20.0f * (16 - i) / 16.0f;
            for (k = 0; k < 33; k++) {
                f = 1.0f + 0.5f * func_0020B550((g->t4 * 0xD05 + (((i << 16) >> 4) + ((k << 17) >> 5))) & 0xFFFF);
                x = (s32)((f32)((k << 16) >> 5) + 14563.0f * func_0020B550((((i << 17) >> 4) + g->t4 * 0x8AE) & 0xFFFF)) & 0xFFFF;
                g->disc2[i][k].x = e * f * func_0020B550(x);
                g->disc2[i][k].y = e * f * func_0020B480(x);
                g->disc2[i][k].z = 0.0f;
                g->disc2[i][k].w = 1.0f;
            }
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        a = (f32)func_00101050(g->t4, 0, 0x20);
        b = (f32)func_00101050(0x3200 - g->t4, 0, 0x20);
        h = a * b / 1024.0f;
        for (i = 0; i < 16; i++) {
            if (i == 15) {
                alpha = (u32)(h * (f32)(i * 0x78 / 17));
                tri.v[0].c.r = 0x4F;
                tri.v[0].c.g = 0xC4;
                tri.v[0].c.b = 0xFF;
                tri.v[0].c.a = alpha;
                tri.v[0].c.q = 1.0f;
                alpha = (u32)(h * (f32)((i - 1) * 0x78 / 17));
                tri.v[1].c.r = 0x4F;
                tri.v[1].c.g = 0xC4;
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
                alpha = (u32)(h * (f32)(i * 0x78 / 17));
                pk.v[0].c.r = 0x4F;
                pk.v[0].c.g = 0xC4;
                pk.v[0].c.b = 0xFF;
                pk.v[0].c.a = alpha;
                pk.v[0].c.q = 1.0f;
                pk.v[1].c = pk.v[0].c;
                alpha = (u32)(h * (f32)((i + 1) * 0x78 / 17));
                pk.v[2].c.r = 0x4F;
                pk.v[2].c.g = 0xC4;
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
        ((Spr_b222_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b222_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b222_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b222_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b222_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 0);
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * h * (0.8f + 0.2f * (g->t4 % 2)));
        spr.c.r = 0x4F;
        spr.c.g = 0xC4;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 40.0f;
        ((Uv_b222_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b222_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b222_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b222_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        if (g->t4 > 0x3200) {
            g->on4 = 0;
        }
    }

    a = (f32)func_00101050(g->t - 0x42, 0, 0x20);
    h = a * (f32)func_00101050(0x172 - g->t, 0, 0x20) / 1024.0f;
    if (h > 0.0f) {
        ((Spr_b222_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b222_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b222_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b222_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b222_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b222_01E00080 *)(s32)&spr.uv0)->u = 0x190;
        ((Uv_b222_01E00080 *)(s32)&spr.uv0)->v = 0x110;
        ((Uv_b222_01E00080 *)(s32)&spr.uv1)->u = 0x2670;
        ((Uv_b222_01E00080 *)(s32)&spr.uv1)->v = 0x1AF0;
        alpha = (u32)(64.0f * h);
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
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

    if (g->t == 0x98) {
        ret = 1;
    } else {
        if (g->t > 0xA2 && g->t < 0x152) {
            ret = 6;
        }
        if (g->t == 0x152) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x182) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

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

extern Obj_b222_01E03780 *D_01E03B00_b222;
extern u8 D_0030FF00[];

static void func_01E03780_b222(void *buf) {
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

    o = D_01E03B00_b222;
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
