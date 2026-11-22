#include "common.h"

/* shape b371:01E00080 (b371), 1751 insns, 1 copy: b371 scene manager (b512:01E00080's family): setup clears the
   0x6830 scene, takes both units, four textures, the target and joint 4, seeds a 33x17 phase table; else follows the
   joint, spawns a 4-mote puff per frame in 12 slots (0x29..0xE7), from frame 8 draws a two-layer rippled 33x16 tunnel
   grid of textured quads for 0x108 frames, a jittered full-screen sprite fade, 16-mote swirls in 32 slots drifting to
   the target and frames 1..0x15 an 8-slot two-pass spark burst; returns 1 / 6 / 2 / 8 at 0x2D / 0x38..0xE7 / 0xE8 /
   >0x118 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b371_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b371_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b371_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b371_01E00080 c;
    Uv_b371_01E00080 uv0;
    Xyz_b371_01E00080 p0;
    Uv_b371_01E00080 uv1;
    Xyz_b371_01E00080 p1;
    u8 tail[0x20];
} Spr_b371_01E00080;

typedef struct {
    f32 s, t;
    Xyz_b371_01E00080 p;
} Tv_b371_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b371_01E00080 c;
    Tv_b371_01E00080 v[4];
    u8 tail[0x20];
} Tex_b371_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f p;
    Vec4f v[4];
} Puff_b371_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    s32 rot[16];
    u8 pad58[8];
    Vec4f p;
    Vec4f v[16];
} Swirl_b371_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[0x18];
    Vec4f v[16];
} Spark_b371_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 m0;
    u8 pad24[0xC];
    Vec4f pos0;
    Vec4f tgt;
    Puff_b371_01E00080 puff[12];
    Vec4f grid[33][17];
    s32 phase[33][17];
    u8 on;
    u8 pad30A5[3];
    s32 tt;
    u8 pad30AC[4];
    Swirl_b371_01E00080 swirl[32];
    Spark_b371_01E00080 spark[8];
} Scene_b371_01E00080;

static s32 func_01E00080_b371(s32 arg0, s32 code) {
    Scene_b371_01E00080 *g = (Scene_b371_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern void func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 q;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    f32 f;
    f32 a;
    f32 r;
    f32 s;
    f32 h;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    f32 m4[4][4];
    Vec4f v;
    Vec4f c;
    Spr_b371_01E00080 spr __attribute__((aligned(8)));
    Tex_b371_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x6830);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->m0 = func_001F5560(g->unitA, 4, 1);
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 12; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            for (j = 0; j < 17; j++) {
                g->phase[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on = 0;
        for (i = 0; i < 32; i++) {
            g->swirl[i].on = 0;
        }
        for (l = 0; l < 8; l++) {
            g->spark[l].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->m0, &g->pos0);
    g->pos0.y += -3.0f;
    g->pos0.z += -8.0f * g->obj;
    if (g->t > 0x28 && g->t < 0xE8) {
        n = g->t % 12;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        g->puff[n].p = g->pos0;
        for (j = 0; j < 4; j++) {
            g->puff[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->puff[n].v[j], 1.5f);
        }
    }

    ((Spr_b371_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b371_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b371_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b371_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b371_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xE8 - g->t, 0, 0x20) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (64.0f * func_0020B480((g->puff[i].t << 14) / 12)));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.5f + 0.5f * g->puff[i].t / 12.0f);
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
        s = 0.1f + 0.9f * g->puff[i].t / 12.0f;
        for (j = 0; j < 4; j++) {
            x = g->puff[i].c[j] % 4 * 32;
            y = (g->puff[i].c[j] >> 2) * 32;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->puff[i].v[j], s);
            func_00187B00(&v, &v, &g->puff[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 12) {
            g->puff[i].on = 0;
        }
    }

    if (g->t == 8) {
        g->on = 1;
        g->tt = 0;
    }
    if (g->on == 1) {
        ((Tex_b371_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Tex_b371_01E00080 *)(s32)&pk)->size = 9;
        ((Tex_b371_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b371_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        a = func_00101020((f32)g->tt, 16.0f) * func_00100FF0((f32)g->tt, 264.0f, 232.0f);
        for (q = 0; q < 2; q++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 50.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            t0 = 220.0f + 2.0f * (30.0f * q);
            for (i = 0; i < 33; i++) {
                h = -3000.0f + 6000.0f * i / 32.0f;
                for (j = 0; j < 16; j++) {
                    r = t0 + 30.0f * func_0020B550((g->phase[i][j] + (q * 0x33333 >> 1) + g->tt * 0x8AE) & 0xFFFF);
                    x = (j << 16) >> 4;
                    g->grid[i][j].x = r * func_0020B550(x);
                    g->grid[i][j].y = r * func_0020B480(x);
                    g->grid[i][j].z = h;
                    g->grid[i][j].w = 1.0f;
                }
                g->grid[i][16] = g->grid[i][0];
            }
            h = (f32)(g->tt % 32) / 32.0f * (f32)(q % 2 * 2 - 1);
            r = 2.0f * (g->tt % 16) / 16.0f * g->obj;
            for (i = 0; i < 32; i++) {
                t0 = (f32)(i % 2) / 2.0f;
                t1 = (f32)(i % 2 + 1) / 2.0f;
                s = func_0020B550((i << 15) >> 5);
                if (q == 0) {
                    alpha = (u32)(32.0f * a * s);
                } else {
                    alpha = (u32)(48.0f * a * s);
                }
                pk.c.r = 0x69;
                pk.c.g = 0x69;
                pk.c.b = 0x69;
                pk.c.a = alpha;
                pk.c.q = 1.0f;
                for (j = 0; j < 16; j++) {
                    s0 = (f32)(j % 2) / 2.0f;
                    s1 = (f32)(j % 2 + 1) / 2.0f + h;
                    pk.v[0].s = s0 + h;
                    pk.v[0].t = t0 + r;
                    pk.v[1].s = s1;
                    pk.v[1].t = t0 + r;
                    pk.v[2].s = s0 + h;
                    pk.v[2].t = t1 + r;
                    pk.v[3].s = s1;
                    pk.v[3].t = t1 + r;
                    if (func_00100BA0(&g->grid[i][j], &g->grid[i][j + 1], &g->grid[i + 1][j], &g->grid[i + 1][j + 1], m,
                                      &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, 0xFFFFFF);
                    }
                }
            }
        }
        g->tt++;
        if (g->tt > 0x108) {
            g->on = 0;
        }
    }

    f = (f32)func_00101050(g->t - 8, 0, 0x20) * (f32)func_00101050(0x110 - g->t, 0, 0x20) / 1024.0f;
    if (f > 0.0f) {
        ((Spr_b371_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b371_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b371_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b371_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b371_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        x = (func_0019A5C8() >> 23) % 21 - 10;
        y = (func_0019A5C8() >> 23) % 21 - 10;
        ((Uv_b371_01E00080 *)(s32)&spr.uv0)->u = (x + 25) << 4;
        ((Uv_b371_01E00080 *)(s32)&spr.uv0)->v = (y + 17) << 4;
        ((Uv_b371_01E00080 *)(s32)&spr.uv1)->u = (x + 0x267) << 4;
        ((Uv_b371_01E00080 *)(s32)&spr.uv1)->v = (y + 0x1AF) << 4;
        alpha = (u32)(70.0f * f);
        (void)alpha;
        spr.c.r = 0xAF;
        spr.c.g = 0xAF;
        spr.c.b = 0xAF;
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

    if (g->t > 0x28 && g->t < 0xE8) {
        n = g->t % 32;
        (void)n;
        g->swirl[n].on = 1;
        g->swirl[n].t = 0;
        g->swirl[n].p = g->pos0;
        for (j = 0; j < 16; j++) {
            g->swirl[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->swirl[n].rot[j] = (func_0019A5C8() >> 23) % 256 * 0x8AE >> 8;
            func_00101080(&g->swirl[n].v[j], 4.5f);
        }
    }

    ((Spr_b371_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b371_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b371_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b371_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b371_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xE8 - g->t, 0, 8) / 8.0f;
    for (i = 0; i < 32; i++) {
        if (g->swirl[i].on == 0) {
            continue;
        }
        a = 128.0f * func_00101020((f32)g->swirl[i].t, 3.0f);
        alpha = (u32)(f * (a * func_00100FF0((f32)g->swirl[i].t, 32.0f, 6.0f)));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 17.0f * (0.5f + 0.5f * g->swirl[i].t / 32.0f);
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
        h = 0.1f + 0.9f * g->swirl[i].t / 32.0f;
        s = 2.7f * g->swirl[i].t / 32.0f;
        (void)s;
        func_00187B18(&c, &g->tgt, &g->swirl[i].p);
        func_00187B48(&c, &c, s);
        func_00187B00(&c, &c, &g->swirl[i].p);
        for (q = 0; q < 16; q++) {
            x = g->swirl[i].c[q] % 4 * 32;
            y = (g->swirl[i].c[q] >> 2) * 32;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            ang = (g->swirl[i].rot[q] * g->swirl[i].t) & 0xFFFF;
            func_0020BBB0(m4);
            func_00100E00(m4, ang, 2);
            func_00187B48(&v, &g->swirl[i].v[q], h);
            func_001878E0(&v, m4, &v);
            func_00187B00(&v, &v, &c);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->swirl[i].t++;
        if (g->swirl[i].t > 32) {
            g->swirl[i].on = 0;
        }
    }

    g->pos0.y += -5.0f;
    if (g->t > 0 && g->t < 0x16) {
        n = g->t % 8;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (j = 0; j < 16; j++) {
            g->spark[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[j], 3.0f);
            g->spark[n].v[j].z = -1.0f * (g->obj * func_001A6970(g->spark[n].v[j].z));
            func_00187B00(&g->spark[n].v[j], &g->spark[n].v[j], &g->pos0);
        }
    }

    ((Spr_b371_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b371_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b371_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b371_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b371_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 8; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 3.0f * (0.2f + 0.8f * (8 - g->spark[i].t) / 8.0f);
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
        alpha = (u32)(128.0f * func_0020B550((g->spark[i].t << 14) >> 3));
        spr.c.r = 0xFF;
        spr.c.g = 0xE8;
        spr.c.b = 0xE0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * (8 - g->spark[i].t) / 8.0f;
        for (q = 0; q < 16; q++) {
            func_00187B18(&v, &g->spark[i].v[q], &g->pos0);
            func_00187B48(&v, &v, s);
            func_00187B00(&v, &v, &g->pos0);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[q] % 4 * 32;
            y = (g->spark[i].c[q] >> 2) * 32;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(0));
        r = 15.0f * (0.2f + 0.8f * (8 - g->spark[i].t) / 8.0f);
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
        alpha = (u32)(128.0f * func_0020B550((g->spark[i].t << 14) >> 3));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.7f * (8 - g->spark[i].t) / 8.0f;
        for (q = 0; q < 16; q++) {
            func_00187B18(&v, &g->spark[i].v[q], &g->pos0);
            func_00187B48(&v, &v, s);
            func_00187B00(&v, &v, &g->pos0);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = (g->spark[i].c[q] + 4) % 4 * 32;
            y = (g->spark[i].c[q] + 4 >> 2) * 32;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b371_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 8) {
            g->spark[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x118 - g->t, 0, 8) * (func_00101050(g->t, 0, 8) * -0x80) >> 6) + 0x80));
    if (g->t == 0x2D) {
        ret = 1;
    } else {
        if (g->t > 0x37 && g->t < 0xE8) {
            ret = 6;
        }
        if (g->t == 0xE8) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x118) {
        ret = 8;
    }
    return ret;
}
