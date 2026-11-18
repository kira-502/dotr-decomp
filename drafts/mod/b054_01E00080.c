#include "common.h"

/* shape b054:01E00080 (b054), 3372 insns, 1 copy (-O3,p): b054 scene manager, b624:01E00080's relative (HARD draft, 6
   words: the puff clear loop's counter/pointer registers swap with the main-path k/i loop webs; naming every setup
   loop k moves the swap to the ctr loop's i counter/pointer): joint 0x3C, a 0x7D-frame red twin tornado from 0x56,
   bursts, gravity puffs, motes and drops on 0x57..0xD1, a 0x24-frame red glow and 6-quad shards from t 0, at 0x24 a
   64-mote grey dust puff, the unit tint from 0x93; returns 1 / 6 / 2 / 8 at 0x4C / 0x57..0xD0 / 0xD1 / >0xD2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b054_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b054_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b054_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b054_01E00080 c;
    Uv_b054_01E00080 uv0;
    Xyz_b054_01E00080 p0;
    Uv_b054_01E00080 uv1;
    Xyz_b054_01E00080 p1;
    u8 tail[0x20];
} Spr_b054_01E00080;

typedef struct {
    Rgbaq_b054_01E00080 c;
    union {
        Uv_b054_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b054_01E00080 p;
} Tv_b054_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b054_01E00080 v[4];
    u64 pad70;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Quad_b054_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b054_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[20][4];
    u8 pad58[8];
    Vec4f v[20][4];
} Burst_b054_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[48];
    u8 pad38[8];
    Vec4f v[48];
} Puff_b054_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f v[4];
} Mote_b054_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Drop_b054_01E00080;


typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f v[6];
} Shard_b054_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][64];
    u8 pad48[8];
    Vec4f pos[1];
    Vec4f v[1][64];
} Dust_b054_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn;
    u8 pad24[0xC];
    Vec4f jp;
    Vec4f posA;
    Vec4f tgt;
    Mtx_b054_01E00080 mat;
    f32 dist;
    u8 padA4[0xC];
    Vec4f ring[17];
    Vec4f grid[21][17];
    Vec4f grid2[21][17];
    Vec4f ctr[1][21];
    u8 on;
    u8 pad2FB1[3];
    s32 t2;
    u8 pad2FB8[8];
    Burst_b054_01E00080 burst[8];
    Vec4f pts[48];
    Puff_b054_01E00080 puff[18];
    Mote_b054_01E00080 mote[12];
    Drop_b054_01E00080 drop[12];
    u8 on3;
    u8 padA081[3];
    s32 t3;
    u8 padA088[8];
    Shard_b054_01E00080 shard[8];
    Dust_b054_01E00080 dust;
} Scene_b054_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b054(s32 arg0, s32 code) {
    Scene_b054_01E00080 *g = (Scene_b054_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern s32 func_00101430(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_001F6EF0(void);
    extern void func_001F6590(s32, s32, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    u8 alpha;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 w;
    f32 b;
    f32 r;
    f32 s;
    f32 t0;
    f32 h;
    f32 e;
    f32 a;
    f32 t1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b054_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    Vec4f v3;
    Spr_b054_01E00080 spr __attribute__((aligned(8)));
    Quad_b054_01E00080 pk __attribute__((aligned(8)));
    f32 depth;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA870);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->jn = func_001F5560(g->unitA, 0x3C, 1);
        func_001F53C0(1, g->unitB, &g->tgt);
        g->on = 0;
        g->t2 = 0;
        for (k = 0; k < 48; k++) {
            func_00101080(&g->pts[k], 1.5f);
        }
        for (i = 0; i < 18; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->drop[i].on = 0;
        }
        g->t3 = 0;
        for (i = 0; i < 8; i++) {
            g->shard[i].on = 0;
        }
        g->dust.on = 0;
        func_001F6590(g->unitB, 2, 0);
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    func_001F5620(g->unitA, g->jn, &g->jp);
    func_00187B18(&v, &g->jp, &g->tgt);
    func_00100E40(&g->mat, &v);
    func_00100E00(&g->mat, 0x4000, 0);
    g->dist = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    if (g->t == 0x56) {
        g->on = 1;
        g->t2 = 0;
    }
    a = func_00101050(0x7C - g->t2, 0, 32) / 32.0f;
    if (g->on == 1) {
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 21; j++) {
                r = 0.0f;
                w = (g->t2 * 0x71C + (i * 0x3039 + (j * 0x10000) / 20)) & 0xFFFF;
                g->ctr[i][j].x = r * func_0020B550(w);
                g->ctr[i][j].y = 0.0f;
                g->ctr[i][j].z = r * func_0020B480(w);
                g->ctr[i][j].w = 1.0f;
            }
        }
        b = func_00101050(g->t2, 0, 16);
        h = g->dist * b / 16.0f;
        e = 0.5f + 0.5f * b / 16.0f;
        ((Quad_b054_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b054_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b054_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b054_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)(64.0f * a);
        r = 4.5f * e;
        for (k = 0; k < 17; k++) {
            g->ring[k].x = r * func_0020B550((k << 16) >> 4);
            g->ring[k].y = 0.0f;
            g->ring[k].z = r * func_0020B480((k << 16) >> 4);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 1; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat, &g->tgt);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                t0 = h * j / 20.0f;
                s = (f32)((0.1f + 0.9f * (20 - j) / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                for (n = 0; n < 17; n++) {
                    func_00187B48(&g->grid[j][n], &g->ring[n], s);
                    g->grid[j][n].y = t0;
                    func_00187B00(&g->grid[j][n], &g->grid[j][n], &g->ctr[i][j]);
                }
            }
            r = (f32)i - (g->t2 % 10) / 10.0f;
            for (j = 0; j < 20; j++) {
                if (j == 0) {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0xC8;
                    pk.v[2].c.g = 0;
                    pk.v[2].c.b = 0;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (j == 19) {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0xC8;
                    pk.v[2].c.g = 0;
                    pk.v[2].c.b = 0;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                t0 = 5.0f * j / 20.0f + r;
                t1 = 5.0f * (j + 1) / 20.0f + r;
                for (k = 0; k < 16; k++) {
                    pk.v[0].uv.st.s = k / 16.0f;
                    pk.v[0].uv.st.t = t0;
                    pk.v[1].uv.st.s = (k + 1) / 16.0f;
                    pk.v[1].uv.st.t = t0;
                    pk.v[2].uv.st.s = k / 16.0f;
                    pk.v[2].uv.st.t = t1;
                    pk.v[3].uv.st.s = (k + 1) / 16.0f;
                    pk.v[3].uv.st.t = t1;
                    if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k], &g->grid[j + 1][k + 1],
                                      m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b054_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b054_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b054_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b054_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tex0, &pk.tex1);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b054_01E00080 *)(s32)&pk)->flags |= 0x800;
        alpha = (u32)(128.0f * a);
        r = 4.0f * e;
        for (k = 0; k < 17; k++) {
            g->ring[k].x = r * func_0020B550((k << 16) >> 4);
            g->ring[k].y = 0.0f;
            g->ring[k].z = r * func_0020B480((k << 16) >> 4);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 1; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat, &g->tgt);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                t0 = h * j / 20.0f;
                s = (f32)((0.1f + 0.9f * (20 - j) / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(8192.0f * func_0020B550((((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 46) << 16) / 46) & 0xFFFF)), 1);
                for (k = 0; k < 17; k++) {
                    func_00187B48(&g->grid[j][k], &g->ring[k], s);
                    g->grid[j][k].y = t0;
                    func_00187B00(&g->grid[j][k], &g->grid[j][k], &g->ctr[i][j]);
                    func_001878E0(&g->grid2[j][k], &m4, &g->grid[j][k]);
                    g->grid2[j][k].y = t0 + 0.1f * (h / 20.0f) *
                                                func_0020B550((((k % 16) << 16 >> 4) +
                                                               (((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 48) << 16) / 48)) & 0xFFFF);
                }
            }
            for (j = 0; j < 20; j++) {
                if (j == 0) {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0xC8;
                    pk.v[2].c.g = 0;
                    pk.v[2].c.b = 0;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (j == 19) {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0xC8;
                    pk.v[2].c.g = 0;
                    pk.v[2].c.b = 0;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0xC8;
                    pk.v[0].c.g = 0;
                    pk.v[0].c.b = 0;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                for (k = 0; k < 16; k++) {
                    if (func_00100BA0(&g->grid2[j][k], &g->grid2[j][k + 1], &g->grid2[j + 1][k],
                                      &g->grid2[j + 1][k + 1], m, &pk, &depth) == 1) {
                        func_00100C60(&pk.v[0].uv, &pk.v[0].p, 0, 0);
                        func_00100C60(&pk.v[1].uv, &pk.v[1].p, 0, 0);
                        func_00100C60(&pk.v[2].uv, &pk.v[2].p, 0, 0);
                        func_00100C60(&pk.v[3].uv, &pk.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k],
                                          &g->grid[j + 1][k + 1], m, &pk, &depth) == 1 &&
                            func_00101430(&pk.v[0].p, &pk.v[1].p, &pk.v[2].p) == 1) {
                            func_002075F0(&pk, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x7C) {
            g->on = 0;
        }
    }

    if (g->t > 0x56 && g->t < 0xD2) {
        n = g->t % 8;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        func_00187B18(&v, &g->jp, &g->tgt);
        func_00187B48(&v, &v, func_00101050(g->t2, 0, 16) / 16.0f);
        b = 4.5f * (0.5f + 0.5f * func_00101050(g->t2, 0, 16) / 16.0f);
        for (j = 0; j < 20; j++) {
            r = (f32)(b * ((0.1f + 0.9f * j / 20.0f) *
                           (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF))));
            for (k = 0; k < 4; k++) {
                g->burst[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00187B48(&v2, &v, (20 - j) / 20.0f + 0.05f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
                func_00187B00(&v2, &v2, &g->tgt);
                w = (((k << 16) >> 2) + ((func_0019A5C8() >> 23) % 256 << 16 >> 8)) & 0xFFFF;
                v3.x = r * func_0020B550(w);
                v3.y = 0.0f;
                v3.z = r * func_0020B480(w);
                v3.w = 1.0f;
                func_001878E0(&g->burst[n].v[j][k], &g->mat, &v3);
                func_00187B00(&g->burst[n].v[j][k], &g->burst[n].v[j][k], &v2);
            }
        }
    }

    ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = (f32)func_00101050(g->t - 0x56, 0, 32) * (f32)func_00101050(0xD2 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 8; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (50.0f * func_0020B550((g->burst[i].t << 15) >> 3)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 20; j++) {
            r = (0.5f + 0.5f * j / 20.0f) * (4.0f * (0.2f + 0.8f * func_00100D50(g->burst[i].t, 8, 1)));
            cn[0].x = r;
            cn[0].y = r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = -r;
            cn[1].y = -r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(&cn[1], m3, &cn[1]);
            for (k = 0; k < 4; k++) {
                x = g->burst[i].c[j][k] % 4 * 32;
                y = (g->burst[i].c[j][k] >> 2) * 32;
                ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v = g->burst[i].v[j][k];
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 8) {
            g->burst[i].on = 0;
        }
    }

    if (g->t > 0x56 && g->t < 0xD2) {
        n = g->t % 18;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (k = 0; k < 48; k++) {
            g->puff[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&v, 0.5f);
            func_00187B00(&g->puff[n].v[k], &v, &g->pts[k]);
        }
    }

    ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0xD2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 18; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (50.0f * func_00100FF0(g->puff[i].t, 18.0f, 12.0f)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.2f + 0.8f * func_00100D50(g->puff[i].t, 18, 1));
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        s = 0.05f + (f32)g->puff[i].t / 18.0f;
        h = 12.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->puff[i].t, 2.0f)));
        for (k = 0; k < 48; k++) {
            x = g->puff[i].c[k] % 4 * 32;
            y = (g->puff[i].c[k] >> 2) * 32;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->puff[i].v[k], s);
            func_00187B00(&v, &v, &g->tgt);
            v.y += h;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 18) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0x56 && g->t < 0xD2) {
        n = g->t % 12;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (k = 0; k < 4; k++) {
            g->mote[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->mote[n].v[k], 1.3f);
        }
    }

    ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    t1 = func_00101050(0xD2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(t1 * (50.0f * func_0020B550((g->mote[i].t << 15) / 12)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 5.0f;
        cn[0].x = h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        s = 0.3f + 0.7f * g->mote[i].t / 12.0f;
        for (k = 0; k < 4; k++) {
            x = g->mote[i].c[k] % 4 * 32;
            y = (g->mote[i].c[k] >> 2) * 32;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->mote[i].v[k], s);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 12) {
            g->mote[i].on = 0;
        }
    }

    if (g->t > 0x66 && g->t < 0xD2) {
        n = g->t % 12;
        g->drop[n].on = 1;
        g->drop[n].t = 0;
        g->drop[n].pos = g->jp;
        for (k = 0; k < 4; k++) {
            g->drop[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->drop[n].v[k], 0.5f);
        }
    }

    ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0xD2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->drop[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (96.0f * func_0020B480((g->drop[i].t << 14) / 12)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.5f + 0.5f * g->drop[i].t / 12.0f);
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        h = 0.1f + 0.9f * (f32)g->drop[i].t / 12.0f;
        s = 10.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->drop[i].t, 2.0f)));
        for (k = 0; k < 4; k++) {
            x = g->drop[i].c[k] % 4 * 32;
            y = (g->drop[i].c[k] >> 2) * 32;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->drop[i].v[k], h);
            func_00187B00(&v, &v, &g->drop[i].pos);
            v.y += s;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->drop[i].t++;
        if (g->drop[i].t > 12) {
            g->drop[i].on = 0;
        }
    }

    if (g->t == 0) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        e = func_00101020(g->t3, 16.0f) * func_00100FF0(g->t3, 35.0f, 19.0f);
        alpha = (u32)(255.0f * ((0.8f + 0.2f * (g->t3 % 2)) * e));
        spr.c.r = 0xFF;
        spr.c.g = 0x37;
        spr.c.b = 0x55;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 20.0f;
        cn[0].x = h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        x = 0;
        y = 32;
        ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        v = g->posA;
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->t3++;
        if (g->t3 > 0x23) {
            g->on3 = 0;
        }
    }

    if (g->t > 0 && g->t < 0x23) {
        n = g->t % 8;
        g->shard[n].on = 1;
        g->shard[n].t = 0;
        for (k = 0; k < 6; k++) {
            g->shard[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->shard[n].v[k], 0.5f);
        }
    }

    ((Quad_b054_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b054_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b054_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b054_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, 5);
    b = (f32)func_00101050(g->t, 0, 16) * (f32)func_00101050(0x23 - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 8; i++) {
        if (g->shard[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (((8 - g->shard[i].t) * 255) >> 3));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0xB4;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        func_0020EB40(m);
        v = g->posA;
        func_0020C940(m2, 0, 0, &v);
        func_0020BC00(m, m2);
        s = -3.5f * func_00100D50(g->shard[i].t, 8, 1);
        for (k = 0; k < 6; k++) {
            func_00100E40(&m4, &g->shard[i].v[k]);
            func_00100E00(&m4, ((i << 16) >> 3) + (k << 16) / 6, 2);
            cn[0].x = 0.0f;
            cn[0].y = 1.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -1.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&out[0], &cn[0], &g->shard[i].v[k]);
            func_00187B00(&out[1], &cn[1], (void *)&g->shard[i].v[k]);
            func_00187B48((void *)&v, &g->shard[i].v[k], s);
            func_00187B00(&out[2], (void *)&out[0], (void *)&v);
            func_00187B00(&out[3], &out[1], (void *)&v);
            x = g->shard[i].c[k] % 4 * 32;
            y = (g->shard[i].c[k] >> 2) * 32;
            t0 = x / 128.0f;
            t1 = (32.0f + x) / 128.0f;
            h = y / 64.0f;
            e = (32.0f + y) / 64.0f;
            pk.v[0].uv.st.s = t0;
            pk.v[0].uv.st.t = h;
            pk.v[1].uv.st.s = t1;
            pk.v[1].uv.st.t = h;
            pk.v[2].uv.st.s = t0;
            pk.v[2].uv.st.t = e;
            pk.v[3].uv.st.s = t1;
            pk.v[3].uv.st.t = e;
            if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        g->shard[i].t++;
        if (g->shard[i].t > 8) {
            g->shard[i].on = 0;
        }
    }

    if (g->t == 0x24) {
        g->dust.on = 1;
        g->dust.t = 0;
        for (i = 0; i < 1; i++) {
            g->dust.pos[i] = g->posA;
            g->dust.pos[i].y += -5.0f;
            for (k = 0; k < 64; k++) {
                g->dust.c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->dust.v[i][k], 1.0f);
                g->dust.v[i][k].y = 0.5f * func_001A6970(g->dust.v[i][k].y);
            }
        }
    }
    if (g->dust.on == 1) {
        ((Spr_b054_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b054_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b054_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b054_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b054_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208CB0(&spr, 5);
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (u32)(128.0f * func_0020B480((g->dust.t << 14) >> 5));
        spr.c.r = 0xC8;
        spr.c.g = 0xC8;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.5f + 0.5f * g->dust.t / 32.0f);
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
        s = func_00100D50(g->dust.t, 32, 1);
        for (i = 0; i < 1; i++) {
            for (k = 0; k < 64; k++) {
                x = g->dust.c[i][k] % 4 * 32;
                y = (g->dust.c[i][k] >> 2) * 32;
                ((Uv_b054_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b054_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->dust.v[i][k], s);
                func_00187B00(&v, &v, &g->dust.pos[i]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->dust.t++;
        if (g->dust.t > 32) {
            g->dust.on = 0;
        }
    }

    if (func_001F6EF0() == 1 && g->t > 0x92) {
        x = func_00101050(g->t - 0x92, 0, 64) * 100 >> 6;
        col[2] = 0x60;
        col[1] = 0x40;
        col[0] = 0;
        col[3] = x;
        func_001F6590(g->unitB, 2, col);
    }

    if (g->t == 0x4C) {
        ret = 1;
    } else {
        if (g->t > 0x56 && g->t < 0xD1) {
            ret = 6;
        }
        if (g->t == 0xD1) {
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
