#include "common.h"

/* shape b643:01E00080 (b643), 1515 insns, 1 copy: b643 scene manager (b261:01E00080's family; HARD draft, 6 words):
   setup clears the 0x4B40 scene, takes both units, two textures, four joints, the target and its top; follows the
   joint pair midpoint and a tip 1.4x along the second pair, from 0x92..0x12B spawns an 8-spark burst in 32 slots and
   a 4-sprite puff in 24, from 0xB5..0x149 a 32-sprite rising ring in 16, from 1..0x98 a 4-point tip trail in 8, plus
   a flickering tip glow; returns 1 / 6 / 2 / 8 at 0xAA / 0xB5..0x148 / 0x149 / >0x14A. Left: the 24-slot puff spawn's
   constant 1 and slot-address chain take v0/v1 swapped (b261's open %24 spawn; b475 pointer form fixes the order, n =
   g->t; n %= K fixes the and-modulo spawns) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b643_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b643_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b643_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b643_01E00080 c;
    Uv_b643_01E00080 uv0;
    Xyz_b643_01E00080 p0;
    Uv_b643_01E00080 uv1;
    Xyz_b643_01E00080 p1;
    u8 tail[0x20];
} Spr_b643_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[8];
    f32 sz[8];
    f32 rise;
    u8 pad4C[4];
    Vec4f p;
    Vec4f v[8];
} Spark_b643_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Ring_b643_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[4];
    Vec4f p;
    Vec4f v[4];
} Puff_b643_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p[4];
} Trail_b643_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    s32 j[2];
    Vec4f jp[2];
    Vec4f mid;
    s32 k[2];
    u8 pad58[8];
    Vec4f kp[2];
    Vec4f tip;
    Vec4f prev;
    Vec4f tgt;
    Vec4f tgt2;
    Spark_b643_01E00080 spark[32];
    Ring_b643_01E00080 ring[16];
    Puff_b643_01E00080 puff[24];
    Trail_b643_01E00080 trail[8];
} Scene_b643_01E00080;

static s32 func_01E00080_b643(s32 arg0, s32 code) {
    Scene_b643_01E00080 *g = (Scene_b643_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00101080(void *, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(s32, s32, s32, s32, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u8 D_0030FF00[];
    s32 ot;
    s32 ret;
    s32 i;
    s32 j;
    s32 n;
    s32 y;
    s32 x;
    s32 q;
    s32 w;
    u8 alpha;
    f32 a;
    f32 r;
    f32 s;
    f32 h;
    f32 k;
    f32 depth;
    Puff_b643_01E00080 *pw;
    Puff_b643_01E00080 *pbase;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f v2;
    Spr_b643_01E00080 spr __attribute__((aligned(8)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4B40);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->j[0] = func_001F5560(g->unitA, 0x1D, 1);
        g->j[1] = func_001F5560(g->unitA, 0x1E, 0);
        g->k[0] = func_001F5560(g->unitA, 0x17, 0);
        g->k[1] = func_001F5560(g->unitA, 0x18, 0);
        func_001F5F90(g->unitB, &g->tgt);
        func_001F53C0(1, g->unitB, &g->tgt2);
        for (i = 0; i < 32; i++) {
            g->spark[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->ring[i].on = 0;
        }
        for (i = 0; i < 24; i++) {
            g->puff[i].on = 0;
        }
        g->tip.x = 0.0f;
        g->tip.y = 0.0f;
        g->tip.z = 0.0f;
        g->tip.w = 1.0f;
        for (j = 0; j < 8; j++) {
            g->trail[j].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->j[i], &g->jp[i]);
    }
    func_00187B00(&g->mid, &g->jp[0], &g->jp[1]);
    { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }
    g->prev = g->tip;
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->k[i], &g->kp[i]);
    }
    func_00187B18(&v, &g->kp[1], &g->kp[0]);
    func_00187B48((void *)&v, &v, 1.4f);
    func_00187B00(&g->tip, &v, &g->kp[0]);
    if (g->t == 0) {
        g->prev = g->tip;
    }

    if (g->t > 0x91 && g->t < 0x12C) {
        n = g->t;
        n %= 32;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].rise = -50.0f + 100.0f * func_00101050(g->t - 0x91, 0, 0x9B) / 155.0f;
        g->spark[n].p = g->mid;
        g->spark[n].p.z += 0.0f * g->obj;
        for (j = 0; j < 8; j++) {
            g->spark[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->spark[n].sz[j] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->spark[n].v[j], 0.4f);
            func_00187B00(&g->spark[n].v[j], &g->spark[n].v[j], &g->tgt);
            func_00187B18(&g->spark[n].v[j], &g->spark[n].v[j], &g->spark[n].p);
        }
    }

    ((Spr_b643_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b643_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b643_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b643_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b643_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    k = func_00101050(0x12C - g->t, 0, 0x20) / 32.0f;
    for (i = 0; i < 32; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        a = 180.0f * func_00101020(g->spark[i].t, 3.0f);
        alpha = (u32)(k * (a * func_00100FF0(g->spark[i].t, 32.0f, 21.0f)));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x38;
        spr.c.b = 0x19;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 12.0f * (0.5f + 0.5f * g->spark[i].t / 32.0f);
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
        h = 2.5f * g->spark[i].t / 32.0f;
        s = g->spark[i].rise * g->spark[i].t / 32.0f;
        for (q = 0; q < 8; q++) {
            x = g->spark[i].c[q] % 4 * 32;
            y = (g->spark[i].c[q] >> 2) * 32;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&out[0], &cn[0], g->spark[i].sz[q]);
            func_00187B48(&out[1], &cn[1], g->spark[i].sz[q]);
            func_00187B48(&v, &g->spark[i].v[q], h);
            v.y += s;
            func_00187B00(&v, &v, &g->spark[i].p);
            func_00187B00(&out[0], &out[0], &v);
            func_00187B00(&out[1], &out[1], &v);
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    if (g->t > 0xB4 && g->t < 0x14A) {
        n = g->t;
        n %= 16;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->ring[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[n].v[j], 1.3f);
        }
    }

    ((Spr_b643_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b643_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b643_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b643_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b643_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    k = (f32)func_00101050(g->t - 0xB4, 0, 0x20) * func_00101050(0x14A - g->t, 0, 0x20) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(k * (96.0f * func_0020B550((g->ring[i].t << 15) >> 4)));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x39;
        spr.c.b = 0x19;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * (16 - g->ring[i].t) / 16.0f);
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
        a = g->ring[i].t / 16.0f;
        s = 0.9f + 0.1f * (16 - g->ring[i].t) / 16.0f;
        h = -25.0f + 80.0f * a;
        for (j = 0; j < 32; j++) {
            x = g->ring[i].c[j] % 4 * 32;
            y = (g->ring[i].c[j] >> 2) * 32;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v.x = g->ring[i].v[j].x * s;
            v.y = h + g->ring[i].v[j].y;
            v.z = g->ring[i].v[j].z * s;
            func_00187B00(&v, &v, &g->tgt2);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 16) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0x91 && g->t < 0x12C) {
        n = g->t % 24;
        pbase = g->puff;
        pw = &pbase[n];
        pw->on = 1;
        pw->t = 0;
        g->puff[n].p = g->mid;
        for (j = 0; j < 4; j++) {
            g->puff[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->puff[n].v[j], 0.5f);
        }
    }

    ((Spr_b643_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b643_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b643_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b643_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b643_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 24; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        r = 4.0f * (0.2f + 0.8f * (24 - g->puff[i].t) / 24.0f);
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
        alpha = (u32)(255.0f * func_0020B480((g->puff[i].t << 14) / 24));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x46;
        spr.c.b = 0x17;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->puff[i].t, 0x18, 1);
        for (j = 0; j < 4; j++) {
            func_00187B48(&v, &g->puff[i].v[j], s);
            func_00187B00(&v, &v, &g->puff[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->puff[i].c[j] % 4 * 32;
            y = (g->puff[i].c[j] >> 2) * 32;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b643_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 24) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x99) {
        n = g->t;
        n %= 8;
        g->trail[n].on = 1;
        g->trail[n].t = 0;
        func_00187B18(&v, &g->tip, &g->prev);
        for (j = 0; j < 4; j++) {
            func_00187B48(&v2, &v, (j + 1) / 4.0f);
            func_00187B00(&v2, &v2, &g->prev);
            g->trail[n].p[j] = v2;
        }
    }

    ((Spr_b643_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b643_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b643_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b643_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b643_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 96;
    y = 0;
    ((Uv_b643_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b643_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b643_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
    ((Uv_b643_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
    k = (f32)func_00101050(g->t, 0, 0x20) * func_00101050(0x99 - g->t, 0, 0x20) / 1024.0f;
    r = 2.0f;
    for (i = 0; i < 8; i++) {
        if (g->trail[i].on == 0) {
            continue;
        }
        alpha = (u32)(k * (64.0f * func_0020B480((g->trail[i].t << 14) >> 3)));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
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
        for (j = 0; j < 4; j++) {
            v = g->trail[i].p[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->trail[i].t++;
        if (g->trail[i].t > 8) {
            g->trail[i].on = 0;
        }
    }

    k = (f32)func_00101050(g->t, 0, 0x20) * func_00101050(0x12C - g->t, 0, 0x20) / 1024.0f;
    if (k > 0.0f) {
        alpha = (u32)(255.0f * k * (0.8f + 0.2f * (g->t % 2)));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 4.0f;
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
        v = g->tip;
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
    }

    if (g->t == 0xAA) {
        ret = 1;
    } else {
        if (g->t > 0xB4 && g->t < 0x149) {
            ret = 6;
        }
        if (g->t == 0x149) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x14A) {
        ret = 8;
    }
    return ret;
}
