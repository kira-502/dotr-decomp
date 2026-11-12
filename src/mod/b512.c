#include "common.h"

/* shape b512:01E00080 (b512), 1449 insns, 1 copy: b512 scene manager: code >= 0 clears the scene, takes both units,
   three textures and six models, builds a 32x13 cone grid; else follows the models, starts three cone bursts (frames
   60/71/83) that each draw the grid and drop rings, three waves (108/117/125) that spawn spark clusters, draws rings
   and sparks as sprites, and returns 1 / 6 / 2 / 8 at frames 98 / 109..132 / 133 / 165 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b512_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b512_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b512_01E00080;

typedef struct {
    Rgbaq_b512_01E00080 c;
    f32 s, t;
    Xyz_b512_01E00080 p;
} Tv_b512_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b512_01E00080 v[3];
    u8 tail[0x20];
} Tri_b512_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b512_01E00080 c;
    Uv_b512_01E00080 uv0;
    Xyz_b512_01E00080 p0;
    Uv_b512_01E00080 uv1;
    Xyz_b512_01E00080 p1;
    u8 tail[0x20];
} Spr_b512_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Burst_b512_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Ring_b512_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 n;
    u8 padC[4];
    Vec4f v[16];
} Wave_b512_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16][6];
    u8 pad68[8];
    Vec4f p[16];
    Vec4f v[16][6];
} Spark_b512_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    s32 m[6];
    u8 pad48[8];
    Vec4f pos[6];
    f32 mat[3][4][4];
    Vec4f grid[32][13];
    Burst_b512_01E00080 b[3];
    u8 pad1B88[8];
    Ring_b512_01E00080 ring[3][24];
    Wave_b512_01E00080 wave[3];
    Spark_b512_01E00080 spark[3][8];
    u8 padFE40[0x10];
} Scene_b512_01E00080;

static s32 func_01E00080_b512(s32 arg0, s32 code) {
    Scene_b512_01E00080 *g = (Scene_b512_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_001F57B0(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00100E40(void *, void *);
    extern void func_00101080(void *, f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_00101020(f32, f32);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;

    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 a;
    s32 n;
    u16 ang;
    u8 alpha;
    s32 c;
    s32 x;
    s32 y;
    f32 h;
    f32 r;
    f32 depth;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p0;
    Vec4f p1;
    Vec4f v;
    Spr_b512_01E00080 spr __attribute__((aligned(8)));
    Tri_b512_01E00080 pk __attribute__((aligned(8)));
    s32 ot;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xFE50);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->m[0] = func_001F5560(g->unitA, 2, 1);
        g->m[1] = func_001F5560(g->unitA, 3, 0);
        g->m[2] = func_001F5560(g->unitA, 4, 0);
        g->m[3] = func_001F5560(g->unitA, 5, 0);
        g->m[4] = func_001F5560(g->unitA, 6, 0);
        g->m[5] = func_001F5560(g->unitA, 7, 0);
        for (i = 0; i < 32; i++) {
            h = 20.0f * (i + 1) / 32.0f;
            r = 6.0f * (32 - i) / 32.0f;
            a = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            for (j = 0; j < 13; j++) {
                ang = a + j * 0x10000 / 12;
                g->grid[i][j].x = r * func_0020B550(ang);
                g->grid[i][j].y = r * func_0020B480(ang);
                g->grid[i][j].z = h;
                g->grid[i][j].w = 1.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            g->b[i].on = 0;
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 24; j++) {
                g->ring[i][j].on = 0;
            }
        }
        for (i = 0; i < 3; i++) {
            g->wave[i].on = 0;
            g->wave[i].n = 0;
        }
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    for (i = 0; i < 6; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    for (i = 0; i < 3; i++) {
        func_00187B18(&v, &g->pos[i * 2 + 1], &g->pos[i * 2]);
        func_00100E40(g->mat[i], &v);
    }
    if (g->t == 0x47) {
        g->b[0].on = 1;
        g->b[0].t = 0;
    }
    if (g->t == 0x3C) {
        g->b[1].on = 1;
        g->b[1].t = 0;
    }
    if (g->t == 0x53) {
        g->b[2].on = 1;
        g->b[2].t = 0;
    }
    if (g->t == 0x75) {
        g->b[0].on = 0;
        g->wave[0].on = 1;
        g->wave[0].t = 0;
        n = 0;
        for (i = 0; i < 16; i++) {
            func_00101080(&g->wave[n].v[i], 4.0f);
        }
    }
    if (g->t == 0x6C) {
        g->b[1].on = 0;
        g->wave[1].on = 1;
        g->wave[1].t = 0;
        n = 1;
        for (i = 0; i < 16; i++) {
            func_00101080(&g->wave[n].v[i], 4.0f);
        }
    }
    if (g->t == 0x7D) {
        g->b[2].on = 0;
        g->wave[2].on = 1;
        g->wave[2].t = 0;
        n = 2;
        for (i = 0; i < 16; i++) {
            func_00101080(&g->wave[n].v[i], 4.0f);
        }
    }

    ((Tri_b512_01E00080 *)(s32)&pk)->flags = 0x33;
    ((Tri_b512_01E00080 *)(s32)&pk)->size = 9;
    ((Tri_b512_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b512_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, 0);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    for (i = 0; i < 3; i++) {
        if (g->b[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->pos[i * 2 + 1]);
        func_0020BC00(m2, g->mat[i]);
        func_0020BC00(m, m2);
        alpha = (u32)(64.0f * func_00101020((f32)g->b[i].t, 16.0f));
        pk.v[0].c.r = 0x64;
        pk.v[0].c.g = 0xA4;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c.r = 0xC;
        pk.v[1].c.g = 0xC;
        pk.v[1].c.b = 0xFF;
        pk.v[1].c.a = 0;
        pk.v[1].c.q = 1.0f;
        pk.v[2].c = pk.v[1].c;
        for (j = 0; j < 32; j++) {
            r = -1.0f * (g->b[i].t % 6) / 6.0f + 3.0f * j / 32.0f;
            for (k = 0; k < 12; k++) {
                pk.v[0].s = 0.5f;
                pk.v[0].t = r;
                pk.v[1].s = 0.0f;
                pk.v[1].t = 4.0f + r;
                pk.v[2].s = 1.0f;
                pk.v[2].t = 4.0f + r;
                if (func_00100B00(&v, &g->grid[j][k], &g->grid[j][k + 1], m, &pk, &depth) == 1) {
                    if (g->t > 0x5A) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        func_002075F0(&pk, ot, 0);
                    } else {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        n = g->b[i].t % 24;
        g->ring[i][n].on = 1;
        g->ring[i][n].t = 0;
        g->ring[i][n].pos = g->pos[i * 2 + 1];
        for (k = 0; k < 8; k++) {
            g->ring[i][n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[i][n].v[k], 0.5f);
        }
        g->b[i].t++;
        if (g->b[i].t > 0x100) {
            g->b[i].on = 0;
        }
    }

    ((Spr_b512_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b512_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b512_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b512_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b512_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 24; j++) {
            if (g->ring[i][j].on == 0) {
                continue;
            }
            r = 6.0f * (0.8f + 0.2f * g->ring[i][j].t / 24.0f);
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
            alpha = (u32)(128.0f * func_0020B480((g->ring[i][j].t << 14) / 24));
            switch ((i + 7 + j * 17) % 7) {
            case 0:
                spr.c.r = 0;
                spr.c.g = 0x20;
                spr.c.b = 0x20;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 2:
                spr.c.r = 0;
                spr.c.g = 0;
                spr.c.b = 0x20;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 4:
                spr.c.r = 0x20;
                spr.c.g = 0;
                spr.c.b = 0x20;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 6:
                spr.c.r = 0x20;
                spr.c.g = 0;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 1:
                spr.c.r = 0x20;
                spr.c.g = 0x20;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 3:
                spr.c.r = 0;
                spr.c.g = 0x20;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 5:
                spr.c.r = 0x20;
                spr.c.g = 0x80;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            default:
                spr.c.r = 0;
                spr.c.g = 0x20;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            }
            h = 0.3f + 0.7f * func_00100D50(g->ring[i][j].t, 24, 1);
            for (k = 0; k < 8; k++) {
                func_00187B48(&v, &g->ring[i][j].v[k], h);
                func_00187B00(&v, &v, &g->ring[i][j].pos);
                func_00187B00(&p0, &cn[0], &v);
                func_00187B00(&p1, &cn[1], (void *)&v);
                x = 0;
                y = 0;
                ((Uv_b512_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b512_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b512_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b512_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    if (g->t > 0x5A) {
                        spr.p0.z = 0xFFFFF8;
                        spr.p1.z = spr.p0.z;
                        func_002075F0(&spr, ot, 0);
                    } else {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
            }
            g->ring[i][j].t++;
            if (g->ring[i][j].t > 24) {
                g->ring[i][j].on = 0;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        l = g->wave[i].n++;
        if (g->wave[i].n >= 8) {
            g->wave[i].n = 8;
        }
        if (l < 8) {
            g->spark[i][l].on = 1;
            g->spark[i][l].t = 0;
            h = 0.1f + 0.9f * g->wave[i].t / 8.0f;
            for (j = 0; j < 16; j++) {
                func_00187B48(&v, &g->wave[i].v[j], h);
                func_00187B00(&g->spark[i][l].p[j], &v, &g->tgt);
                for (k = 0; k < 6; k++) {
                    g->spark[i][l].c[j][k] = (func_0019A5C8() >> 23) % 4 + 2;
                    func_00101080(&g->spark[i][l].v[j][k], 0.5f);
                }
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 8) {
            g->wave[i].on = 0;
        }
    }

    ((Spr_b512_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b512_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b512_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b512_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b512_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            if (g->spark[i][j].on == 0) {
                continue;
            }
            r = 8.0f * (0.7f + 0.3f * g->spark[i][j].t / 32.0f);
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
            alpha = (u32)(200.0f * func_0020B480((g->spark[i][j].t << 14) >> 5));
            h = 0.2f + 0.8f * func_00100D50(g->spark[i][j].t, 32, 1);
            for (k = 0; k < 16; k++) {
                for (n = 0; n < 6; n++) {
                    if (n < 2) {
                        func_002086D0(&spr, func_00208D00(0));
                    } else {
                        func_002086D0(&spr, func_00208D00(1));
                    }
                    switch ((i + 7 + j * 3 + k + n) % 7) {
                    case 0:
                        spr.c.r = 0x80;
                        spr.c.g = 0;
                        spr.c.b = 0;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 2:
                        spr.c.r = 0x80;
                        spr.c.g = 0x80;
                        spr.c.b = 0;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 4:
                        spr.c.r = 0;
                        spr.c.g = 0x80;
                        spr.c.b = 0;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 1:
                        spr.c.r = 0;
                        spr.c.g = 0x80;
                        spr.c.b = 0x80;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 6:
                        spr.c.r = 0;
                        spr.c.g = 0;
                        spr.c.b = 0x80;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 3:
                        spr.c.r = 0x80;
                        spr.c.g = 0;
                        spr.c.b = 0x80;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    case 5:
                        spr.c.r = 0;
                        spr.c.g = 0x40;
                        spr.c.b = 0x80;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    default:
                        spr.c.r = 0x80;
                        spr.c.g = 0;
                        spr.c.b = 0x80;
                        spr.c.a = alpha;
                        spr.c.q = 1.0f;
                        break;
                    }
                    func_00187B48(&v, &g->spark[i][j].v[k][n], h);
                    func_00187B00(&v, &v, &g->spark[i][j].p[k]);
                    func_00187B00(&p0, &cn[0], &v);
                    func_00187B00(&p1, &cn[1], (void *)&v);
                    c = g->spark[i][j].c[k][n];
                    x = c % 4 * 32;
                    y = (c >> 2) * 32;
                    ((Uv_b512_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b512_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b512_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b512_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
            }
            g->spark[i][j].t++;
            if (g->spark[i][j].t > 32) {
                g->spark[i][j].on = 0;
            }
        }
    }

    if (g->t == 0x62) {
        ret = 1;
    } else {
        if (g->t > 0x6C && g->t < 0x85) {
            ret = 6;
        }
        if (g->t == 0x85) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xA5) {
        ret = 8;
    }
    return ret;
}
