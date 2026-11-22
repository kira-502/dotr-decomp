#include "common.h"

/* shape b625:01E00080 (b625), 2219 insns, 1 copy (-O3,p): b625 scene manager (b222:01E00080's tube form, -O3):
   pillars of wisps and sparks from the two joints, a white flash, a four-column twisting vortex of 21x9 grids at the
   target (rippled twin grid drawn through a render target), debris sprites, a colour pulse on the unit and a glow at
   the joint midpoint; returns 1 / 6 / 2 / 8 at 250 / 261..347 / 348 / 381 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b625_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b625_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b625_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b625_01E00080 c;
    Xyz_b625_01E00080 v[2];
    u64 tail;
} Flat_b625_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b625_01E00080 c;
    Uv_b625_01E00080 uv0;
    Xyz_b625_01E00080 p0;
    Uv_b625_01E00080 uv1;
    Xyz_b625_01E00080 p1;
    u8 tail[0x20];
} Spr_b625_01E00080;

typedef struct {
    Rgbaq_b625_01E00080 c;
    union {
        Uv_b625_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b625_01E00080 p;
} Tv_b625_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b625_01E00080;

typedef struct {
    Reg_b625_01E00080 a;
    Reg_b625_01E00080 b;
} Tx_b625_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b625_01E00080 v[4];
    u64 pad70;
    Tx_b625_01E00080 tx;
    u64 tail;
} Quad_b625_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b625_01E00080;

typedef struct {
    u8 c[4];
} Col_b625_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p[4];
} Part_b625_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[8];
} Wisp_b625_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[4];
    u8 pad18[8];
    Vec4f v[4];
} Debris_b625_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f pos;
    Vec4f tgt;
    s32 jn[2];
    u8 pad48[8];
    Vec4f jp[2];
    Vec4f mid;
    Part_b625_01E00080 part[12];
    Wisp_b625_01E00080 wisp[32];
    u8 on1;
    u8 pad1641[3];
    s32 t1;
    u8 pad1648[8];
    Vec4f ring[9];
    Vec4f tube[21][9];
    Vec4f tube2[21][9];
    Vec4f cen[4][21];
    u8 on2;
    u8 pad33C1[3];
    s32 t2;
    u8 pad33C8[8];
    Vec4f q[4];
    Debris_b625_01E00080 debris[32];
    u8 on3;
    u8 pad4011[3];
    s32 t3;
    u8 pad4018[8];
} Scene_b625_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b625(s32 arg0, s32 code) {
    Scene_b625_01E00080 *g = (Scene_b625_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
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
    extern void func_001F6D00(s32);
    extern Col_b625_01E00080 D_01E02380_b625;
    extern Col_b625_01E00080 D_01E02388_b625;
    extern f32 D_0028BC10[4][32][3];
    extern u16 D_28BBF0[][4];
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
    s32 c;
    u8 alpha;
    f32 r;
    f32 s;
    f32 t0;
    f32 e;
    f32 f;
    f32 h;
    f32 a;
    f32 b;
    f32 u;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b625_01E00080 m4;
    Vec4f v;
    Spr_b625_01E00080 spr __attribute__((aligned(8)));
    Flat_b625_01E00080 flat __attribute__((aligned(8)));
    Quad_b625_01E00080 pk __attribute__((aligned(8)));
    f32 depth;
    Col_b625_01E00080 c0;
    Col_b625_01E00080 c1;

    ret = 0;
    ot = func_00207500();
    c0 = D_01E02380_b625;
    c1 = D_01E02388_b625;
    if (code >= 0) {
        func_00195108(g, 0x4020);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F53C0(1, g->unitA, &g->pos);
        func_001F53C0(1, g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x50, 1);
        i = func_001F5560(g->unitA, 0x60, 0);
        g->jn[1] = i;
        for (k = 0; k < 12; k++) {
            g->part[k].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->wisp[i].on = 0;
        }
        g->on1 = 0;
        g->on2 = 0;
        for (i = 0; i < 32; i++) {
            g->debris[i].on = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (k = 0; k < 2; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    func_00187B00(&g->mid, &g->jp[0], &g->jp[1]);
    func_00187B48((void *)&g->mid, &g->mid, 0.5f);
    if (g->t > 0 && g->t < 0x7C) {
        n = g->t % 12;
        g->part[n].on = 1;
        g->part[n].t = 0;
        for (k = 0; k < 4; k++) {
            g->part[n].p[k].x = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            g->part[n].p[k].y = -35.0f;
            g->part[n].p[k].z = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            g->part[n].p[k].w = 1.0f;
            func_00187B00(&g->part[n].p[k], &g->part[n].p[k], &g->pos);
        }
    }
    ((Spr_b625_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b625_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b625_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b625_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b625_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b625_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b625_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b625_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b625_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    cn[0].x = -1.0f;
    cn[0].y = -12.0f;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = 1.0f;
    cn[1].y = 12.0f;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    func_001878E0(&cn[0], m3, &cn[0]);
    func_001878E0(&cn[1], m3, &cn[1]);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    t0 = (f32)func_00101050(g->t, 0, 0x40) / 64.0f;
    for (i = 0; i < 12; i++) {
        if (g->part[i].on == 0) {
            continue;
        }
        alpha = (u32)(t0 * (255.0f * func_0020B550((g->part[i].t << 15) / 12)));
        spr.c.r = 0x84;
        spr.c.g = 0xB4;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = 70.0f * g->part[i].t / 12.0f;
        for (j = 0; j < 4; j++) {
            v = g->part[i].p[j];
            v.y += f;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->part[i].t++;
        if (g->part[i].t > 12) {
            g->part[i].on = 0;
        }
    }
    if (g->t > 0x14 && g->t < 0x5C) {
        n = g->t % 32;
        g->wisp[n].on = 1;
        g->wisp[n].t = 0;
        for (k = 0; k < 8; k++) {
            g->wisp[n].v[k].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->wisp[n].v[k].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->wisp[n].v[k].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->wisp[n].v[k].w = 1.0f;
            func_00187B00(&g->wisp[n].v[k], &g->wisp[n].v[k], &g->mid);
        }
    }
    ((Spr_b625_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b625_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b625_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b625_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b625_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b625_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b625_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b625_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b625_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->wisp[i].on == 0) {
            continue;
        }
        r = 0.2f + 0.8f * (32 - g->wisp[i].t) / 32.0f;
        r = 6.0f * r;
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
        alpha = g->wisp[i].t * 0xFF >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        t0 = (f32)(32 - g->wisp[i].t) / 32.0f;
        for (j = 0; j < 8; j++) {
            func_00187B18(&v, &g->wisp[i].v[j], &g->mid);
            func_00187B48(&v, &v, t0);
            func_00187B00(&v, &v, &g->mid);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->wisp[i].t++;
        if (g->wisp[i].t > 32) {
            g->wisp[i].on = 0;
        }
    }
    if (g->t == 0x7C) {
        g->on1 = 1;
        g->t1 = 0;
        for (i = 0; i < 12; i++) {
            g->part[i].on = 0;
        }
        g->on3 = 0;
    }
    if (g->on1 == 1) {
        ((Flat_b625_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b625_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b625_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b625_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t1, 0x30, 1)));
        (void)alpha;
        flat.c.r = 0x80;
        flat.c.g = 0x80;
        flat.c.b = 0xFF;
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
            g->on1 = 0;
        }
    }
    if (g->t == 0x7C) {
        g->on2 = 1;
        g->t2 = 0;
        for (k = 0; k < 4; k++) {
            x = ((k << 16) >> 2) + 0xE38 & 0xFFFF;
            g->q[k].x = 24.0f * func_0020B550(x);
            g->q[k].y = -125.0f;
            g->q[k].z = 24.0f * func_0020B480(x);
            g->q[k].w = 1.0f;
            func_00187B00(&g->q[k], &g->q[k], &g->tgt);
        }
    }
    if (g->on2 == 1) {
        x = func_00101050(g->t - 0x104, 0, 0x10);
        u = 10.0f * x / 16.0f;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 21; j++) {
                x = (g->t2 * 0x71C + (i * 0x3039 + (j * 0x10000) / 20)) & 0xFFFF;
                g->cen[i][j].x = u * func_0020B550(x);
                g->cen[i][j].y = 0.0f;
                g->cen[i][j].z = u * func_0020B480(x);
                g->cen[i][j].w = 1.0f;
            }
        }
        u = 250.0f * func_00100D50(func_00101050(g->t2, 0, 0x10), 0x10, 1);
        h = (f32)func_00101050(0x100 - g->t2, 0, 0x20) / 32.0f;
        ((Quad_b625_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b625_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b625_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b625_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[2], 1);
        func_00208CB0(&pk, 0);
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = 0x80;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        b = 5.0f * h;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = b * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = b * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 4; i++) {
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->q[i]);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                b = u * j / 20.0f;
                for (q = 0; q < 9; q++) {
                    g->tube[j][q] = g->ring[q];
                    g->tube[j][q].y = b;
                    func_00187B00(&g->tube[j][q], &g->tube[j][q], &g->cen[i][j]);
                }
            }
            e = (f32)i / 4.0f - 2.0f * (g->t2 % 16) / 16.0f;
            for (j = 0; j < 20; j++) {
                r = 5.0f * j / 20.0f + e;
                a = 5.0f * (j + 1) / 20.0f + e;
                for (k = 0; k < 8; k++) {
                    pk.v[0].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[0].uv.st.t = r;
                    pk.v[1].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[1].uv.st.t = r;
                    pk.v[2].uv.st.s = 2.0f * k / 8.0f;
                    pk.v[2].uv.st.t = a;
                    pk.v[3].uv.st.s = 2.0f * (k + 1) / 8.0f;
                    pk.v[3].uv.st.t = a;
                    if (func_00100BA0(&g->tube[j][k], &g->tube[j][k + 1], &g->tube[j + 1][k], &g->tube[j + 1][k + 1],
                                      m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b625_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b625_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b625_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b625_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tx.a, &pk.tx.b);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b625_01E00080 *)(s32)&pk)->flags |= 0x800;
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = 0x80;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        r = 7.0f * h;
        for (k = 0; k < 9; k++) {
            x = (k << 16) >> 3;
            g->ring[k].x = r * func_0020B550(x);
            g->ring[k].y = 0.0f;
            g->ring[k].z = r * func_0020B480(x);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 4; i++) {
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->q[i]);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                h = u * j / 20.0f;
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(910.0f * func_0020B550(((j << 16) / 20 + ((g->t2 + i * 5) % 24 << 16) / 24) & 0xFFFF)), 1);
                for (k = 0; k < 9; k++) {
                    g->tube[j][k] = g->ring[k];
                    g->tube[j][k].y = h;
                    func_00187B00(&g->tube[j][k], &g->tube[j][k], &g->cen[i][j]);
                    func_001878E0(&g->tube2[j][k], &m4, &g->ring[k]);
                    g->tube2[j][k].y = h + 0.1f * (u / 20.0f) * func_0020B550((((k << 16) >> 3) + ((g->t2 + i * 5) % 24 << 16) / 24) & 0xFFFF);
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
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x100) {
            g->on2 = 0;
        }
    }
    if (g->t > 0x104 && g->t < 0x15C) {
        n = g->t % 32;
        g->debris[n].on = 1;
        g->debris[n].t = 1;
        for (k = 0; k < 4; k++) {
            g->debris[n].c[k] = (func_0019A5C8() >> 23) % 4;
            g->debris[n].v[k].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->debris[n].v[k].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->debris[n].v[k].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][(func_0019A5C8() >> 23) % 3];
            g->debris[n].v[k].w = 1.0f;
        }
    }
    ((Spr_b625_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b625_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b625_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b625_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b625_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->debris[i].on == 0) {
            continue;
        }
        alpha = (0x20 - g->debris[i].t) * 100 >> 5;
        spr.c.r = 0x64;
        spr.c.g = 0x64;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.5f + 0.5f * g->debris[i].t / 32.0f);
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
        s = func_00100D50(g->debris[i].t, 0x20, 1);
        for (j = 0; j < 4; j++) {
            func_00187B48(&v, &g->debris[i].v[j], s);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b625_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->debris[i].c[j]][0];
            ((Uv_b625_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->debris[i].c[j]][2];
            ((Uv_b625_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->debris[i].c[j]][1];
            ((Uv_b625_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->debris[i].c[j]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->debris[i].t++;
        if (g->debris[i].t > 32) {
            g->debris[i].on = 0;
        }
    }
    if (g->t % 8 == 0 && g->t > 0xA2 && g->t < 0x104) {
        func_001F71A0(g->unitA, 0x20, 1, &c0, &c1, 0);
    }
    if (g->t == 0x14) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b625_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b625_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b625_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b625_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b625_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b625_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b625_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b625_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b625_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = func_00101050(g->t3, 0, 0x20) * 0xFF >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0xE0;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.9f + 0.1f * (g->t3 % 2));
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
        func_00187B00(&out[0], &cn[0], &g->mid);
        func_00187B00(&out[1], &cn[1], &g->mid);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            if (g->t < 0x46) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            } else {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t3++;
    }
    func_001F6D00((u8)((func_00101050(0x177 - g->t, 0, 0x20) * (func_00101050(g->t, 0, 0x20) * -64) >> 10) + 0x80));
    if (g->t == 0xFA) {
        ret = 1;
    } else {
        if (g->t > 0x104 && g->t < 0x15C) {
            ret = 6;
        }
        if (g->t == 0x15C) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x17C) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
