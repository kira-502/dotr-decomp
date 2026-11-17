#include "common.h"

/* shape b214:01E00080 (b214), 2285 insns, 1 copy: b214 scene manager (b296:01E00080's family, written from the asm):
   setup clears the 0xAB50 scene, takes both units, three textures, the target, joints 0xA / 0x3E and six more, and
   builds a 5x17 wavy two-sided ribbon grid with cubed-sine weights; else 11 joint sources every 15 frames shedding
   16-slot drops, 32-slot cloud and puff bursts at six joints on 1..0x18F, 16-slot puffs on 0xAE..0x17B, from 0x104 a
   0x8F-frame 24-pass ribbon of scrolling ST quads round the target, the unit tint; returns 1 / 6 / 2 / 8 at 0xFA /
   0x105..0x191 / 0x192 / >0x1BA */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b214_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b214_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b214_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b214_01E00080 c;
    Uv_b214_01E00080 uv0;
    Xyz_b214_01E00080 p0;
    Uv_b214_01E00080 uv1;
    Xyz_b214_01E00080 p1;
    u8 tail[0x20];
} Spr_b214_01E00080;

typedef struct {
    Rgbaq_b214_01E00080 c;
    f32 s, t;
    Xyz_b214_01E00080 p;
} Tv_b214_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b214_01E00080 v[4];
    u8 tail[0x20];
} Quad_b214_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p;
} Src_b214_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    u8 padA[2];
    f32 f;
    Vec4f v[2];
} Drop_b214_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[6][4];
    Vec4f p[6];
    Vec4f v[6][4];
} Cloud_b214_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[6][2];
    u8 pad14[0xC];
    Vec4f p[6];
    Vec4f v[6][2];
} Puff_b214_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    s32 jn0[2];
    u8 pad38[8];
    Vec4f jp0[2];
    s32 jn[6];
    u8 pad78[8];
    Vec4f jp[6];
    s32 n;
    u8 padE4[0xC];
    Src_b214_01E00080 src[11];
    Drop_b214_01E00080 drop[11][16];
    Cloud_b214_01E00080 cloud[32];
    Puff_b214_01E00080 puff[32];
    Puff_b214_01E00080 puff2[16];
    Vec4f grid[5][17][2];
    u8 on2;
    u8 padA9F1[3];
    s32 t2;
    f32 wt[5][17];
    u8 padAB4C[4];
} Scene_b214_01E00080;

static s32 func_01E00080_b214(s32 arg0, s32 code) {
    Scene_b214_01E00080 *g = (Scene_b214_01E00080 *)arg0;
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
    extern f32 func_001A6C48(f32, f32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
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
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    s32 l;
    s32 q;
    u8 alpha;
    f32 f;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 z;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b214_01E00080 spr __attribute__((aligned(8)));
    Quad_b214_01E00080 qd __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xAB50);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn0[0] = func_001F5560(g->unitA, 0xA, 1);
        g->jn0[1] = func_001F5560(g->unitA, 0x3E, 0);
        g->jn[0] = func_001F5560(g->unitA, 0x14, 0);
        g->jn[1] = func_001F5560(g->unitA, 0x15, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x16, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x2C, 0);
        g->jn[4] = func_001F5560(g->unitA, 0x2D, 0);
        g->jn[5] = func_001F5560(g->unitA, 0x2E, 0);
        g->n = 0;
        for (i = 0; i < 11; i++) {
            g->src[i].on = 0;
        }
        for (i = 0; i < 11; i++) {
            for (j = 0; j < 16; j++) {
                g->drop[i][j].on = 0;
            }
        }
        for (i = 0; i < 32; i++) {
            g->cloud[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->puff2[i].on = 0;
        }
        for (i = 0; i < 5; i++) {
            h = 140.0f * i / 4.0f;
            for (j = 0; j < 17; j++) {
                s = 70.0f * j / 16.0f - 35.0f;
                w = h + 7.0f * func_0020B550(((j << 17) >> 4) - 0x4000 & 0xFFFF);
                z = 4.0f * func_0020B550((j << 16) >> 4);
                g->grid[i][j][0].x = s;
                g->grid[i][j][0].y = w;
                g->grid[i][j][0].z = z;
                g->grid[i][j][0].w = 1.0f;
                g->grid[i][j][1].x = s;
                g->grid[i][j][1].y = w;
                g->grid[i][j][1].z = -z;
                g->grid[i][j][1].w = 1.0f;
                g->wt[i][j] = (4 - i) * func_001A6C48(func_0020B550((j << 15) >> 4), 3.0f) / 4.0f;
            }
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn0[i], &g->jp0[i]);
    }
    for (i = 0; i < 6; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }

    if (g->t == g->n * 15 + 12 && g->n < 11) {
        n = g->n;
        g->src[n].on = 1;
        g->src[n].t = 0;
        g->src[n].p = g->jp0[(n + 1) % 2];
        g->n++;
    }
    for (i = 0; i < 11; i++) {
        if (g->src[i].on == 0) {
            continue;
        }
        f = (f32)func_00101050(0x80 - g->src[i].t, 0, 32) / 32.0f;
        n = g->src[i].t % 16;
        (void)n;
        g->drop[i][n].on = 1;
        g->drop[i][n].t = 0;
        g->drop[i][n].f = f;
        for (j = 0; j < 2; j++) {
            g->drop[i][n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->drop[i][n].v[j], 0.1f);
        }
        g->src[i].t++;
        if (g->src[i].t > 0x80) {
            g->src[i].on = 0;
        }
    }

    ((Spr_b214_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b214_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b214_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b214_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b214_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 16; j++) {
            if (g->drop[i][j].on == 0) {
                continue;
            }
            alpha = (u32)(g->drop[i][j].f * (164.0f * func_0020B550((g->drop[i][j].t << 15) >> 4)));
            spr.c.r = 0xFF;
            spr.c.g = 0x36;
            spr.c.b = 0x30;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 0.3f + 0.7f * (16 - g->drop[i][j].t) / 16.0f;
            r = 3.0f * r;
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
            t1 = g->drop[i][j].t / 16.0f;
            f = 0.8f + 0.2f * (16 - g->drop[i][j].t) / 16.0f;
            t0 = -1.0f + 8.0f * t1;
            for (k = 0; k < 2; k++) {
                x = g->drop[i][j].c[k] % 4 * 32;
                y = (g->drop[i][j].c[k] >> 2) * 32;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->drop[i][j].v[k].x * f;
                v.y = t0 + g->drop[i][j].v[k].y;
                v.z = g->drop[i][j].v[k].z * f;
                func_00187B00(&v, &v, &g->src[i].p);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->drop[i][j].t++;
            if (g->drop[i][j].t > 16) {
                g->drop[i][j].on = 0;
            }
        }
    }

    if (g->t > 0 && g->t < 0x190) {
        n = g->t % 32;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        for (i = 0; i < 6; i++) {
            g->cloud[n].p[i] = g->jp[i];
            for (j = 0; j < 4; j++) {
                g->cloud[n].c[i][j] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->cloud[n].v[i][j], 0.3f);
            }
        }
    }

    ((Spr_b214_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b214_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b214_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b214_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b214_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0x190 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 32; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (164.0f * func_0020B550((g->cloud[i].t << 15) >> 5)));
        spr.c.r = 0xFF;
        spr.c.g = 0x36;
        spr.c.b = 0x30;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.3f + 0.7f * (32 - g->cloud[i].t) / 32.0f;
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
        s = g->cloud[i].t / 32.0f;
        t0 = 0.7f + 0.3f * g->cloud[i].t / 32.0f;
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 4; k++) {
                x = g->cloud[i].c[j][k] % 4 * 32;
                y = (g->cloud[i].c[j][k] >> 2) * 32;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->cloud[i].v[j][k].x * t0;
                v.y = 10.0f * s + g->cloud[i].v[j][k].y;
                v.z = g->cloud[i].v[j][k].z * t0;
                func_00187B00(&v, &v, &g->cloud[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->cloud[i].t++;
        if (g->cloud[i].t > 32) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x190) {
        n = g->t % 32;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (i = 0; i < 6; i++) {
            g->puff[n].p[i] = g->jp[i];
            for (j = 0; j < 2; j++) {
                g->puff[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[i][j], 0.3f);
            }
        }
    }

    ((Spr_b214_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b214_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b214_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b214_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b214_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0x190 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 32; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->puff[i].t << 15) >> 5)));
        spr.c.r = 0xC8;
        spr.c.g = 0xC8;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 2.0f * (0.3f + 0.7f * g->puff[i].t / 32.0f);
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
        s = g->puff[i].t / 32.0f;
        t0 = 0.7f + 0.3f * g->puff[i].t / 32.0f;
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 2; k++) {
                x = g->puff[i].c[j][k] % 4 * 32;
                y = (g->puff[i].c[j][k] >> 2) * 32;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->puff[i].v[j][k].x * t0;
                v.y = 13.0f * s + g->puff[i].v[j][k].y;
                v.z = g->puff[i].v[j][k].z * t0;
                func_00187B00(&v, &v, &g->puff[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 32) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0xAD && g->t < 0x17C) {
        n = g->t % 16;
        (void)n;
        g->puff2[n].on = 1;
        g->puff2[n].t = 0;
        for (i = 0; i < 6; i++) {
            g->puff2[n].p[i] = g->jp[i];
            for (j = 0; j < 2; j++) {
                g->puff2[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff2[n].v[i][j], 0.2f);
            }
        }
    }

    ((Spr_b214_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b214_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b214_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b214_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b214_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0xAD, 0, 32) * (f32)func_00101050(0x17C - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->puff2[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->puff2[i].t << 15) >> 4)));
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x2E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 4.0f * (0.3f + 0.7f * (16 - g->puff2[i].t) / 16.0f);
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
        s = g->puff2[i].t / 16.0f;
        s0 = 0.7f + 0.3f * g->puff2[i].t / 16.0f;
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 2; k++) {
                x = g->puff2[i].c[j][k] % 4 * 32;
                y = (g->puff2[i].c[j][k] >> 2) * 32;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b214_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->puff2[i].v[j][k].x * s0;
                v.y = -2.0f + 10.0f * s + g->puff2[i].v[j][k].y;
                v.z = g->puff2[i].v[j][k].z * s0;
                func_00187B00(&v, &v, &g->puff2[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    spr.p0.z = 0xFFFFF8;
                    spr.p1.z = spr.p0.z;
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->puff2[i].t++;
        if (g->puff2[i].t > 16) {
            g->puff2[i].on = 0;
        }
    }

    if (g->t == 0x104) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Quad_b214_01E00080 *)(s32)&qd)->flags = 0x34;
        ((Quad_b214_01E00080 *)(s32)&qd)->size = 0xC;
        ((Quad_b214_01E00080 *)(s32)&qd)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b214_01E00080 *)(s32)&qd)->pad4 = 0;
        func_00208700(&qd, g->tex[2], 1);
        func_002086D0(&qd, func_00208D00(1));
        func_00208CB0(&qd, 0);
        f = 128.0f * ((f32)func_00101050(g->t2, 0, 32) * (f32)func_00101050(0x8E - g->t2, 0, 32) / 1024.0f);
        for (i = 0; i < 24; i++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            ang = i * 0x30000 / 24 & 0xFFFF;
            v.x = 8.0f * func_0020B550(ang);
            v.y = 0.0f;
            v.z = 8.0f * func_0020B480(ang);
            v.w = 1.0f;
            func_00187B00(&v, &v, &g->tgt);
            v.y += -46.666668f;
            func_00187B60(m2, m2, &v);
            if (i < 12) {
                l = (i << 16) / 24;
            } else {
                l = (i << 16) / 24 + 0xAAA;
                (void)l;
            }
            func_00100E00(m2, l, 1);
            func_0020BC00(m, m2);
            for (j = 0; j < 4; j++) {
                r = 3.0f * j / 4.0f - 2.0f * (g->t2 % (i * 12 / 24 + 24)) / (i * 12 / 24 + 24);
                t1 = 3.0f * (j + 1) / 4.0f - 2.0f * (g->t2 % (i * 12 / 24 + 24)) / (i * 12 / 24 + 24);
                for (k = 0; k < 16; k++) {
                    q = i % 2;
                    if (j == 0) {
                        qd.v[0].c.r = 0xFF;
                        qd.v[0].c.g = 0x5A;
                        qd.v[0].c.b = 0x40;
                        qd.v[0].c.a = 0;
                        qd.v[0].c.q = 1.0f;
                        qd.v[1].c.r = 0xFF;
                        qd.v[1].c.g = 0x5A;
                        qd.v[1].c.b = 0x40;
                        qd.v[1].c.a = 0;
                        qd.v[1].c.q = 1.0f;
                    } else {
                        alpha = (u32)(f * g->wt[j][k]);
                        qd.v[0].c.r = 0xFF;
                        qd.v[0].c.g = 0x5A;
                        qd.v[0].c.b = 0x40;
                        qd.v[0].c.a = alpha;
                        qd.v[0].c.q = 1.0f;
                        alpha = (u32)(f * g->wt[j][k + 1]);
                        qd.v[1].c.r = 0xFF;
                        qd.v[1].c.g = 0x5A;
                        qd.v[1].c.b = 0x40;
                        qd.v[1].c.a = alpha;
                        qd.v[1].c.q = 1.0f;
                    }
                    alpha = (u32)(f * g->wt[j + 1][k]);
                    qd.v[2].c.r = 0xFF;
                    qd.v[2].c.g = 0x5A;
                    qd.v[2].c.b = 0x40;
                    qd.v[2].c.a = alpha;
                    qd.v[2].c.q = 1.0f;
                    alpha = (u32)(f * g->wt[j + 1][k + 1]);
                    qd.v[3].c.r = 0xFF;
                    qd.v[3].c.g = 0x5A;
                    qd.v[3].c.b = 0x40;
                    qd.v[3].c.a = alpha;
                    qd.v[3].c.q = 1.0f;
                    s0 = 3.0f * k / 16.0f;
                    s1 = 3.0f * (k + 1) / 16.0f;
                    qd.v[0].s = s0;
                    qd.v[0].t = r;
                    qd.v[1].s = s1;
                    qd.v[1].t = r;
                    qd.v[2].s = s0;
                    qd.v[2].t = t1;
                    qd.v[3].s = s1;
                    qd.v[3].t = t1;
                    if (func_00100BA0(&g->grid[j][k][q], &g->grid[j][k + 1][q], &g->grid[j + 1][k][q],
                                      &g->grid[j + 1][k + 1][q], m, &qd, &depth) == 1) {
                        qd.v[0].p.z = 0xFFFFF8;
                        qd.v[1].p.z = qd.v[0].p.z;
                        qd.v[2].p.z = qd.v[0].p.z;
                        qd.v[3].p.z = qd.v[0].p.z;
                        func_002075F0(&qd, ot, 0);
                    }
                }
            }
        }
        g->t2++;
        if (g->t2 > 0x8E) {
            g->on2 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x1BA - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -64) >> 10) + 0x80));
    if (g->t == 0xFA) {
        ret = 1;
    } else {
        if (g->t > 0x104 && g->t < 0x192) {
            ret = 6;
        }
        if (g->t == 0x192) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1BA) {
        ret = 8;
    }
    return ret;
}
