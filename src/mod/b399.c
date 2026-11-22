#include "common.h"

/* shape b399:01E00080 (b399), 1970 insns, 1 copy: b399 scene manager (b371:01E00080's grid-quad family, written from
   the asm): setup clears the 0xD380 scene, takes both units and two textures, builds a 33x33 floor grid and a 33x17
   wall grid (shaped by table D_28B850) with random phases; else from frame 0 draws the rippling floor as two
   scrolling textured quad layers, from 0x38 the wall grid (shrinking over 300 frames) and a 0x20-frame flash, on
   0x39..0x163 spawns 16-slot 33-sprite drops along the wall, on 0x142..0x1CB 8-slot 32-sprite screen star bursts,
   from 0x141 four scrolling full-screen sprite layers (float STs through a union), and at 0x18C a fade that clears
   every layer at its frame 0x40; returns 1 / 6 / 2 / 8 at 0x137 / 0x142..0x1CB / 0x1CC / >0x1EC */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b399_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b399_01E00080;

typedef struct {
    f32 s;
    f32 t;
} St_b399_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b399_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b399_01E00080 c;
    Xyz_b399_01E00080 v[2];
    u64 tail;
} Flat_b399_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b399_01E00080 c;
    union {
        Uv_b399_01E00080 uv;
        St_b399_01E00080 st;
    } uv0;
    Xyz_b399_01E00080 p0;
    union {
        Uv_b399_01E00080 uv;
        St_b399_01E00080 st;
    } uv1;
    Xyz_b399_01E00080 p1;
    u8 tail[0x20];
} Spr_b399_01E00080;

typedef struct {
    f32 s, t;
    Xyz_b399_01E00080 p;
} Tv_b399_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b399_01E00080 c;
    Tv_b399_01E00080 v[4];
    u8 tail[0x20];
} Tex_b399_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[33][1];
    u8 pad29[7];
    Vec4f pos[33];
    Vec4f v[33][1];
} Drop_b399_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    f32 f[32];
    s32 xy[32][2];
} Star_b399_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f grid[33][33];
    s32 gr[33][33];
    u8 on1;
    u8 pad5535[3];
    s32 t1;
    u8 pad553C[4];
    Vec4f grid2[33][17];
    s32 gr2[33][17];
    u8 on2;
    u8 pad8115[3];
    s32 t2;
    u8 pad811C[4];
    Drop_b399_01E00080 drop[16];
    u8 on3;
    u8 padC621[3];
    s32 t3;
    Star_b399_01E00080 star[8];
    u8 on4;
    u8 padD369[3];
    s32 t4;
    u8 on5;
    u8 padD371[3];
    s32 t5;
    u8 padD378[8];
} Scene_b399_01E00080;

static s32 func_01E00080_b399(s32 arg0, s32 code) {
    Scene_b399_01E00080 *g = (Scene_b399_01E00080 *)arg0;
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
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
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
    s32 q;
    s32 n;
    s32 x;
    s32 y;
    s32 r;
    s32 ang;
    u8 alpha;
    f32 f;
    f32 a;
    f32 s;
    f32 h;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 hh;
    f32 ww;
    f32 u0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Flat_b399_01E00080 flat __attribute__((aligned(8)));
    Spr_b399_01E00080 spr __attribute__((aligned(8)));
    Tex_b399_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD380);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        for (i = 0; i < 33; i++) {
            s = 600.0f * i / 32.0f;
            for (j = 0; j < 33; j++) {
                h = 600.0f * j / 32.0f;
                (void)h;
                g->grid[i][j].x = s - 300.0f;
                g->grid[i][j].y = 0.0f;
                g->grid[i][j].z = h - 300.0f;
                g->grid[i][j].w = 1.0f;
                g->gr[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            h = 600.0f * i / 32.0f;
            for (j = 0; j < 17; j++) {
                g->grid2[i][j].x = h - 300.0f;
                g->grid2[i][j].y = 160.0f * D_28B850[j].y;
                g->grid2[i][j].z = g->obj * (-150.0f * D_28B850[j].z);
                g->grid2[i][j].w = 1.0f;
                g->gr2[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on2 = 0;
        for (i = 0; i < 16; i++) {
            g->drop[i].on = 0;
        }
        g->on3 = 0;
        for (i = 0; i < 8; i++) {
            g->star[i].on = 0;
        }
        g->on4 = 0;
        g->on5 = 0;
        return 0;
    }
    func_00205CA0(m3);
    if (g->t == 0x18C) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t4 == 0x40) {
            g->on1 = 0;
            g->on2 = 0;
            for (i = 0; i < 16; i++) {
                g->drop[i].on = 0;
            }
            g->on3 = 0;
            for (i = 0; i < 8; i++) {
                g->star[i].on = 0;
            }
        }
        ((Flat_b399_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b399_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b399_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b399_01E00080 *)(s32)&flat)->pad4 = 0;
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
        ((Tex_b399_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Tex_b399_01E00080 *)(s32)&pk)->size = 9;
        ((Tex_b399_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b399_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        a = func_00101020((f32)g->t1, 64.0f) * func_00100FF0((f32)g->t1, 12800.0f, 12736.0f);
        for (q = 0; q < 2; q++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 10.0f - 2.0f * (5.0f * q);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (q == 0) {
                alpha = (u32)(60.0f * a);
            } else {
                alpha = (u32)(128.0f * a);
            }
            pk.c.r = 0xA0;
            pk.c.g = 0xA0;
            pk.c.b = 0xA0;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            for (i = 0; i < 33; i++) {
                for (j = 0; j < 33; j++) {
                    g->grid[i][j].y = 5.0f * func_0020B550((g->gr[i][j] + (q * 0x33333 >> 1) + g->t1 * 0x14D) & 0xFFFF);
                }
            }
            ang = ((q % 2 * 2 - 1) * ((g->t1 + q * 32) % 128 << 16 >> 7)) & 0xFFFF;
            s = 0.1f * func_0020B550(ang);
            h = 0.1f * func_0020B480(ang);
            for (i = 0; i < 32; i++) {
                t0 = (f32)(i % 2) / 2.0f;
                t1 = (f32)(i % 2 + 1) / 2.0f;
                for (j = 0; j < 32; j++) {
                    s0 = (f32)(j % 2) / 2.0f;
                    s1 = (f32)(j % 2 + 1) / 2.0f + s;
                    pk.v[0].s = s0 + s;
                    pk.v[0].t = t0 + h;
                    pk.v[1].s = s1;
                    pk.v[1].t = t0 + h;
                    pk.v[2].s = s0 + s;
                    pk.v[2].t = t1 + h;
                    pk.v[3].s = s1;
                    pk.v[3].t = t1 + h;
                    if (func_00100BA0(&g->grid[i][j], &g->grid[i][j + 1], &g->grid[i + 1][j], &g->grid[i + 1][j + 1], m,
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

    if (g->t == 0x38) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tex_b399_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Tex_b399_01E00080 *)(s32)&pk)->size = 9;
        ((Tex_b399_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b399_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        a = func_00101020((f32)g->t2, 32.0f) * func_00100FF0((f32)g->t2, 300.0f, 268.0f);
        func_0020EB40(m);
        func_0020BBB0(m2);
        f = g->t2 / 300.0f;
        v.x = 0.0f;
        v.y = -5.0f;
        v.z = (300.0f + -400.0f * f) * g->obj;
        v.w = 1.0f;
        func_00187B60(m2, m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(90.0f * a);
        (void)alpha;
        pk.c.r = 0xA0;
        pk.c.g = 0xA0;
        pk.c.b = 0xA0;
        pk.c.a = alpha;
        pk.c.q = 1.0f;
        s = func_00100D50(g->t2, 300, 3);
        for (i = 0; i < 33; i++) {
            for (j = 0; j < 17; j++) {
                f = 0.04f * func_0020B550((g->gr2[i][j] + g->t2 * 0x14D) & 0xFFFF);
                g->grid2[i][j].y = s * (160.0f * (f + D_28B850[j].y));
            }
        }
        ang = (g->t2 % 128 << 16 >> 7) & 0xFFFF;
        hh = (f32)(g->t2 % 24) / 24.0f + 0.1f * func_0020B550(ang);
        ww = 0.2f * func_0020B480(ang);
        for (i = 0; i < 32; i++) {
            u0 = (f32)(i % 2) / 2.0f;
            u1 = (f32)(i % 2 + 1) / 2.0f;
            for (j = 0; j < 16; j++) {
                s0 = (f32)(j % 2) / 2.0f;
                s1 = (f32)(j % 2 + 1) / 2.0f;
                (void)s1;
                pk.v[0].s = s0 + hh;
                pk.v[0].t = u0 + ww;
                pk.v[1].s = s1 + hh;
                pk.v[1].t = u0 + ww;
                pk.v[2].s = s0 + hh;
                pk.v[2].t = u1 + ww;
                pk.v[3].s = s1 + hh;
                pk.v[3].t = u1 + ww;
                if (func_00100BA0(&g->grid2[i][j], &g->grid2[i][j + 1], &g->grid2[i + 1][j], &g->grid2[i + 1][j + 1],
                                  m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 0x12C) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x38 && g->t < 0x164) {
        n = g->t % 16;
        (void)n;
        g->drop[n].on = 1;
        g->drop[n].t = 0;
        for (k = 0; k < 33; k++) {
            g->drop[n].pos[k] = g->grid2[k][10];
            for (j = 0; j < 1; j++) {
                g->drop[n].c[k][j] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->drop[n].v[k][j], 1.0f);
            }
        }
    }

    ((Spr_b399_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b399_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b399_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b399_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b399_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_00187B60(m2, m2, &v);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x38, 0, 0x20) * (f32)func_00101050(0x164 - g->t, 0, 0x20) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->drop[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (100.0f * func_0020B550((g->drop[i].t << 15) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x8A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        a = 17.0f * (0.5f + 0.5f * g->drop[i].t / 16.0f);
        cn[0].x = a;
        cn[0].y = a;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -a;
        cn[1].y = -a;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        s = 0.2f + 0.8f * func_00100D50(g->drop[i].t, 16, 1);
        for (k = 0; k < 33; k++) {
            for (j = 0; j < 1; j++) {
                x = g->drop[i].c[k][j] % 4 * 32;
                y = (g->drop[i].c[k][j] >> 2) * 32;
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->drop[i].v[k][j], s);
                func_00187B00(&v, &v, &g->drop[i].pos[k]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->drop[i].t++;
        if (g->drop[i].t > 16) {
            g->drop[i].on = 0;
        }
    }

    if (g->t > 0x141 && g->t < 0x1CC) {
        n = g->t % 8;
        (void)n;
        g->star[n].on = 1;
        g->star[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->star[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->star[n].f[j] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->star[n].xy[j][0] = (s32)(-520.0f + 1040.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->star[n].xy[j][1] = (s32)(-520.0f + 1040.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
        }
    }

    ((Spr_b399_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b399_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b399_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b399_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b399_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    a = (f32)func_00101050(g->t - 0x141, 0, 8) / 8.0f;
    for (i = 0; i < 8; i++) {
        if (g->star[i].on == 0) {
            continue;
        }
        alpha = (u32)(a * (96.0f * func_0020B550((g->star[i].t << 15) >> 3)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x8A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.2f + 0.8f * g->star[i].t / 8.0f;
        for (j = 0; j < 32; j++) {
            r = (s32)(200.0f * (0.5f + 0.5f * g->star[i].t / 8.0f) * g->star[i].f[j]);
            x = g->star[i].c[j] % 4 * 32;
            y = (g->star[i].c[j] >> 2) * 32;
            if (g->star[i].c[j] < 4) {
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->v = (y + 1) << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            } else {
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv0)->v = (y - 1) << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b399_01E00080 *)(s32)&spr.uv1)->v = (y + 33) << 4;
            }
            x = (s32)(320.0f + g->star[i].xy[j][0] * s);
            y = (s32)(224.0f + g->star[i].xy[j][1] * s);
            spr.p0.x = (x - r + 0x6C0) << 4;
            spr.p0.y = (y - r + 0x720) << 4;
            spr.p0.z = 0xFFFFF8;
            spr.p0.f = 0;
            spr.p1.x = (x + r + 0x6C0) << 4;
            spr.p1.y = (y + r + 0x720) << 4;
            spr.p1.z = 0xFFFFF8;
            spr.p1.f = 0;
            func_002075F0(&spr, ot, 0);
        }
        g->star[i].t++;
        if (g->star[i].t > 8) {
            g->star[i].on = 0;
        }
    }

    if (g->t == 0x141) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b399_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b399_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b399_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b399_01E00080 *)(s32)&spr)->pad4 = 0;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 0);
        alpha = (u32)(64.0f * func_00101020((f32)g->t3, 8.0f));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x8A;
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
        n = 16;
        for (k = 0; k < 4; k++) {
            a = (f32)(g->t3 % n) / n;
            if (k % 2 == 0) {
                s = 1.0f;
            } else {
                s = -1.0f;
            }
            if (k >> 1 == 0) {
                f = 1.0f;
            } else {
                f = -1.0f;
            }
            spr.uv0.st.s = s * a;
            spr.uv0.st.t = f * a;
            spr.uv1.st.s = 1.0f + s * a;
            spr.uv1.st.t = 1.0f + f * a;
            func_002075F0(&spr, ot, 0);
            n += 10;
        }
        g->t3++;
        if (g->t3 > 0x3200) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x38) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Flat_b399_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b399_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b399_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b399_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->t5, 0x20, 1)));
        flat.c.r = 0xFF;
        flat.c.g = 0xE8;
        flat.c.b = 0xC8;
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
        g->t5++;
        if (g->t5 > 0x20) {
            g->on5 = 0;
        }
    }

    if (g->t == 0x137) {
        ret = 1;
    } else {
        if (g->t > 0x141 && g->t < 0x1CC) {
            ret = 6;
        }
        if (g->t == 0x1CC) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1EC) {
        ret = 8;
    }
    return ret;
}
