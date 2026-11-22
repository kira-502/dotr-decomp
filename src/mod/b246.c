#include "common.h"

/* shape b246:01E00080 (b246), 1871 insns, 1 copy */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b246_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b246_01E00080;

typedef struct {
    f32 s, t;
} St_b246_01E00080;

typedef union {
    Uv_b246_01E00080 uv;
    St_b246_01E00080 st;
} Tc_b246_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b246_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b246_01E00080 c;
    Xyz_b246_01E00080 v[2];
    u8 tail[8];
} Flat_b246_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b246_01E00080 c;
    Tc_b246_01E00080 uv0;
    Xyz_b246_01E00080 p0;
    Tc_b246_01E00080 uv1;
    Xyz_b246_01E00080 p1;
    u8 tail[0x20];
} Spr_b246_01E00080;

typedef struct {
    f32 s, t;
    Xyz_b246_01E00080 p;
} Qv_b246_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b246_01E00080 c;
    Qv_b246_01E00080 v[4];
    u8 tail[0x20];
} Quad_b246_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[33][1];
    u8 pad29[7];
    Vec4f pos[33];
    Vec4f v[33][1];
} Col_b246_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    f32 sc[32];
    s32 xy[32][2];
} Star_b246_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f grid[33][33];
    s32 phase[33][33];
    u8 on1;
    u8 pad5535[3];
    s32 t1;
    u8 pad553C[4];
    Vec4f grid2[33][17];
    s32 phase2[33][17];
    u8 on2;
    u8 pad8115[3];
    s32 t2;
    u8 pad811C[4];
    Col_b246_01E00080 col[16];
    u8 on3;
    u8 padC621[3];
    s32 t3;
    Star_b246_01E00080 star[8];
    u8 on4;
    u8 padD369[3];
    s32 t4;
} Scene_b246_01E00080;

static s32 func_01E00080_b246(s32 arg0, s32 code) {
    Scene_b246_01E00080 *g = (Scene_b246_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
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
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern Vec4f D_28B850[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 p;
    s32 o;
    s32 n;
    s32 a;
    s32 c;
    s32 x;
    s32 y;
    s32 d;
    s32 sz;
    s32 px;
    s32 py;
    u8 alpha;
    f32 e;
    f32 f;
    f32 r;
    f32 su;
    f32 sv;
    f32 s0;
    f32 s1;
    f32 t0;
    f32 t1;
    f32 q;
    f32 sa;
    f32 w0;
    f32 w3;
    f32 u0;
    f32 u1;
    f32 z0;
    f32 z1;
    f32 z2;
    f32 z3;
    f32 z4;
    f32 z5;
    f32 z6;
    f32 z7;
    f32 w1;
    f32 w2;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Flat_b246_01E00080 flat __attribute__((aligned(8)));
    Spr_b246_01E00080 spr __attribute__((aligned(8)));
    Quad_b246_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD370);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        for (i = 0; i < 33; i++) {
            q = 600.0f * i / 32.0f;
            for (j = 0; j < 33; j++) {
                r = 600.0f * j / 32.0f;
                (void)r;
                g->grid[i][j].x = q - 300.0f;
                g->grid[i][j].y = 0.0f;
                g->grid[i][j].z = r - 300.0f;
                g->grid[i][j].w = 1.0f;
                g->phase[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            f = 600.0f * i / 32.0f;
            for (j = 0; j < 17; j++) {
                g->grid2[i][j].x = f - 300.0f;
                g->grid2[i][j].y = 160.0f * D_28B850[j].y;
                g->grid2[i][j].z = g->obj * (-150.0f * D_28B850[j].z);
                g->grid2[i][j].w = 1.0f;
                g->phase2[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        k = 0;
        g->on2 = k;
        for (k = 0; k < 16; k++) {
            g->col[k].on = 0;
        }
        g->on3 = 0;
        for (i = 0; i < 8; i++) {
            g->star[i].on = 0;
        }
        g->on4 = 0;
        return 0;
    }
    func_00205CA0(m3);

    if (g->t == 0x1F4) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t4 == 0x40) {
            g->on1 = 0;
            g->on2 = 0;
            for (i = 0; i < 16; i++) {
                g->col[i].on = 0;
            }
            g->on3 = 0;
            for (i = 0; i < 8; i++) {
                g->star[i].on = 0;
            }
        }
        ((Flat_b246_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b246_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b246_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b246_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (func_00101020((f32)g->t4, 64.0f) * (1.0f - func_00100D50(func_00101050(g->t4 - 0x40, 0, 0x20), 0x20, 1))));
        flat.c.r = 0xFF;
        flat.c.g = 0xFF;
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
        g->t4++;
        if (g->t4 > 0x60) {
            g->on4 = 0;
        }
    }

    if (g->t == 0) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        ((Quad_b246_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Quad_b246_01E00080 *)(s32)&pk)->size = 9;
        ((Quad_b246_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Quad_b246_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        s1 = func_00101020(g->t1, 64.0f);
        f = s1 * func_00100FF0(g->t1, 12800.0f, 12736.0f);
        for (l = 0; l < 2; l++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 10.0f - 2.0f * (5.0f * l);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (l == 0) {
                alpha = (u32)(60.0f * f);
            } else {
                alpha = (u32)(128.0f * f);
            }
            pk.c.r = 0x80;
            pk.c.g = 0xBE;
            pk.c.b = 0xE4;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            for (j = 0; j < 33; j++) {
                for (k = 0; k < 33; k++) {
                    g->grid[j][k].y = 5.0f * func_0020B550((g->phase[j][k] + (l * 0x33333 >> 1) + g->t1 * 0x14D) & 0xFFFF);
                }
            }
            a = ((l % 2 * 2 - 1) * ((g->t1 + l * 32) % 128 << 16 >> 7)) & 0xFFFF;
            r = 0.1f * func_0020B550(a);
            s1 = 0.1f * func_0020B480(a);
            for (j = 0; j < 32; j++) {
                w0 = (f32)(j % 2) / 2.0f;
                w1 = (f32)(j % 2 + 1) / 2.0f;
                for (k = 0; k < 32; k++) {
                    w2 = (f32)(k % 2) / 2.0f;
                    w3 = (f32)(k % 2 + 1) / 2.0f + r;
                    pk.v[0].s = w2 + r;
                    pk.v[0].t = w0 + s1;
                    pk.v[1].s = w3;
                    pk.v[1].t = w0 + s1;
                    pk.v[2].s = w2 + r;
                    pk.v[2].t = w1 + s1;
                    pk.v[3].s = w3;
                    pk.v[3].t = w1 + s1;
                    if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k], &g->grid[j + 1][k + 1], m,
                                      &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        g->t1++;
        if (g->t1 > 0x3200) {
            g->on1 = 0;
        }
    }

    if (g->t == 0x6E) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Quad_b246_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Quad_b246_01E00080 *)(s32)&pk)->size = 9;
        ((Quad_b246_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Quad_b246_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        e = func_00101020(g->t2, 32.0f);
        e = e * func_00100FF0(g->t2, 250.0f, 218.0f);
        func_0020EB40(m);
        func_0020BBB0(m2);
        f = g->t2 / 250.0f;
        v.x = 0.0f;
        v.y = -5.0f;
        v.z = (300.0f + -400.0f * f) * g->obj;
        v.w = 1.0f;
        func_00187B60(m2, m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(90.0f * e);
        (void)alpha;
        pk.c.r = 0x80;
        pk.c.g = 0xBE;
        pk.c.b = 0xE4;
        pk.c.a = alpha;
        pk.c.q = 1.0f;
        f = func_00100D50(g->t2, 250, 3);
        for (j = 0; j < 33; j++) {
            for (k = 0; k < 17; k++) {
                r = 0.04f * func_0020B550((g->phase2[j][k] + g->t2 * 0x14D) & 0xFFFF);
                g->grid2[j][k].y = f * (160.0f * (r + D_28B850[k].y));
            }
        }
        a = (g->t2 % 128 << 16 >> 7) & 0xFFFF;
        su = (f32)(g->t2 % 24) / 24.0f + 0.1f * func_0020B550(a);
        sv = 0.2f * func_0020B480(a);
        for (j = 0; j < 32; j++) {
            t0 = (f32)(j % 2) / 2.0f;
            t1 = (f32)(j % 2 + 1) / 2.0f;
            for (k = 0; k < 16; k++) {
                s0 = (f32)(k % 2) / 2.0f;
                (void)s0;
                s1 = (f32)(k % 2 + 1) / 2.0f;
                (void)s1;
                pk.v[0].s = s0 + su;
                pk.v[0].t = t0 + sv;
                pk.v[1].s = s1 + su;
                pk.v[1].t = t0 + sv;
                pk.v[2].s = s0 + su;
                pk.v[2].t = t1 + sv;
                pk.v[3].s = s1 + su;
                pk.v[3].t = t1 + sv;
                if (func_00100BA0(&g->grid2[j][k], &g->grid2[j][k + 1], &g->grid2[j + 1][k], &g->grid2[j + 1][k + 1], m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 250) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x6E && g->t < 0x168) {
        n = g->t % 16;
        (void)n;
        g->col[n].on = 1;
        g->col[n].t = 0;
        for (j = 0; j < 33; j++) {
            g->col[n].pos[j] = g->grid2[j][10];
            for (k = 0; k < 1; k++) {
                g->col[n].c[j][k] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->col[n].v[j][k], 1.0f);
            }
        }
    }

    ((Spr_b246_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b246_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b246_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b246_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b246_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_00187B60(m2, m2, &v);
    func_0020BC00(m, m2);
    e = (f32)func_00101050(g->t - 0x6E, 0, 32) * (f32)func_00101050(0x168 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->col[i].on == 0) {
            continue;
        }
        alpha = (u32)(e * (100.0f * func_0020B550((g->col[i].t << 15) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x94;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 17.0f * (0.5f + 0.5f * g->col[i].t / 16.0f);
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
        f = 0.2f + 0.8f * func_00100D50(g->col[i].t, 16, 1);
        for (j = 0; j < 33; j++) {
            for (k = 0; k < 1; k++) {
                c = g->col[i].c[j][k];
                x = c % 4 * 32;
                y = (c >> 2) * 32;
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->col[i].v[j][k], f);
                func_00187B00(&v, &v, &g->col[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->col[i].t++;
        if (g->col[i].t > 16) {
            g->col[i].on = 0;
        }
    }

    if (g->t > 0x14A && g->t < 0x234) {
        n = g->t % 8;
        (void)n;
        g->star[n].on = 1;
        g->star[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->star[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->star[n].sc[j] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->star[n].xy[j][0] = (s32)(-520.0f + 1040.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->star[n].xy[j][1] = (s32)(-520.0f + 1040.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
        }
    }

    ((Spr_b246_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b246_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b246_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b246_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b246_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    e = func_00101050(g->t - 0x14A, 0, 8) / 8.0f;
    for (i = 0; i < 8; i++) {
        if (g->star[i].on == 0) {
            continue;
        }
        alpha = (u32)(e * (96.0f * func_0020B550((g->star[i].t << 15) >> 3)));
        spr.c.r = 0x80;
        spr.c.g = 0xB2;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = 0.2f + 0.8f * g->star[i].t / 8.0f;
        for (j = 0; j < 32; j++) {
            sz = (s32)(200.0f * (0.5f + 0.5f * g->star[i].t / 8.0f) * g->star[i].sc[j]);
            c = g->star[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            if (c < 4) {
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->v = (y + 1) << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            } else {
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv0)->v = (y - 1) << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b246_01E00080 *)(s32)&spr.uv1)->v = (y + 33) << 4;
            }
            x = (s32)(320.0f + g->star[i].xy[j][0] * f);
            y = (s32)(224.0f + g->star[i].xy[j][1] * f);
            spr.p0.x = (x - sz + 0x6C0) << 4;
            spr.p0.y = (y - sz + 0x720) << 4;
            spr.p0.z = 0xFFFFF8;
            spr.p0.f = 0;
            spr.p1.x = (x + sz + 0x6C0) << 4;
            spr.p1.y = (y + sz + 0x720) << 4;
            spr.p1.z = 0xFFFFF8;
            spr.p1.f = 0;
            func_002075F0(&spr, ot, 0);
        }
        g->star[i].t++;
        if (g->star[i].t > 8) {
            g->star[i].on = 0;
        }
    }

    if (g->t == 0x14A) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b246_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b246_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b246_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b246_01E00080 *)(s32)&spr)->pad4 = 0;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 0);
        alpha = (u32)(64.0f * func_00101020(g->t3, 8.0f));
        spr.c.r = 0x80;
        spr.c.g = 0x94;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        spr.p0.x = 0x6C00;
        spr.p0.y = 0x6C00;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x9400;
        spr.p1.y = 0x9400;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        for (j = 0, d = 16; j < 4; j++, d += 10) {
            q = (f32)(g->t3 % d) / (f32)d;
            if (j % 2 == 0) {
                sa = 1.0f;
            } else {
                sa = -1.0f;
            }
            if ((j >> 1) == 0) {
                f = 1.0f;
            } else {
                f = -1.0f;
            }
            s0 = sa * q;
            t0 = f * q;
            spr.uv0.st.s = s0;
            spr.uv0.st.t = t0;
            spr.uv1.st.s = 1.0f + s0;
            spr.uv1.st.t = 1.0f + t0;
            func_002075F0(&spr, ot, 0);
        }
        g->t3++;
        if (g->t3 > 0x3200) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x140) {
        ret = 1;
    } else {
        if (g->t > 0x14A && g->t < 0x234) {
            ret = 6;
        }
        if (g->t == 0x234) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x254) {
        ret = 8;
    }
    return ret;
}
