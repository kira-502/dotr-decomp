#include "common.h"

/* shape b454:01E00080 (b454), 2008 insns, 1 copy: b454 scene manager (b296:01E00080's family, written from the asm):
   setup clears the 0x7300 scene, takes both units, three textures, the target and joints 6 / 7 / 8 / 9, builds an
   8x16 grid of randomly twisted 4-point blades on a cone; else on 0x65..0xF7 spawns a 12-slot ring burst at the
   target (32 sprites, a ground flare and 32x6 trails), every 4th frame a 3-slot two-limb blade-quad burst at joints
   0/1 and 16-slot 8-sprite puffs at joints 2/3, at 0x40 a 48-frame 128-sprite rising puff above the unit; returns 1 /
   6 / 2 / 8 at 0x5A / 0x65..0xF7 / 0xF8 / >0x124 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b454_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b454_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b454_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b454_01E00080 c;
    Uv_b454_01E00080 uv0;
    Xyz_b454_01E00080 p0;
    Uv_b454_01E00080 uv1;
    Xyz_b454_01E00080 p1;
    u8 tail[0x20];
} Spr_b454_01E00080;

typedef struct {
    Rgbaq_b454_01E00080 c;
    f32 s, t;
    Xyz_b454_01E00080 p;
} Tv_b454_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b454_01E00080 v[4];
    u8 tail[0x20];
} Quad_b454_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b454_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f p;
    Vec4f v[32];
    Vec4f w[32];
} Ring_b454_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[2];
    Vec4f pos[2];
} Burst_b454_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Spark_b454_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    Vec4f pos;
    s32 jn[2];
    u8 pad48[8];
    Vec4f jp[2];
    s32 jn2[2];
    u8 pad78[8];
    Vec4f jp2[2];
    s32 nr;
    u8 padA4[0xC];
    Ring_b454_01E00080 ring[12];
    s32 nb;
    u8 pad3534[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Burst_b454_01E00080 burst[3];
    s32 ns;
    u8 pad5654[0xC];
    Spark_b454_01E00080 spark[16];
    u8 on2;
    u8 pad6A61[3];
    s32 t2;
    u8 c2[128];
    u8 pad6AE8[8];
    Vec4f p2;
    Vec4f v2[128];
} Scene_b454_01E00080;

static s32 func_01E00080_b454(s32 arg0, s32 code) {
    Scene_b454_01E00080 *g = (Scene_b454_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 c;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha2;
    u8 alpha;
    f32 r;
    f32 s;
    f32 z;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b454_01E00080 m4;
    Vec4f v;
    Spr_b454_01E00080 spr __attribute__((aligned(8)));
    Quad_b454_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x7300);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 6, 1);
        g->jn[1] = func_001F5560(g->unitA, 7, 0);
        g->jn2[0] = func_001F5560(g->unitA, 8, 0);
        g->jn2[1] = func_001F5560(g->unitA, 9, 0);
        g->nr = 0;
        for (i = 0; i < 12; i++) {
            g->ring[i].on = 0;
        }
        g->nb = 0;
        for (i = 0; i < 8; i++) {
            r = -300.0f * g->obj * (i + 1) / 8.0f;
            z = 24.0f * (8 - (i + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                ang = ((j << 16) >> 4) + ((i << 13) >> 3) & 0xFFFF;
                v.x = z * func_0020B550(ang);
                v.y = z * func_0020B480(ang);
                v.z = 0.0f;
                v.w = 1.0f;
                func_0020BBB0(&m4);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[i][j][0].x = -2.0f;
                g->grid[i][j][0].y = 0.0f;
                g->grid[i][j][0].z = 0.0f;
                g->grid[i][j][0].w = 1.0f;
                g->grid[i][j][1].x = 2.0f;
                g->grid[i][j][1].y = 0.0f;
                g->grid[i][j][1].z = 0.0f;
                g->grid[i][j][1].w = 1.0f;
                g->grid[i][j][2].x = -2.0f;
                g->grid[i][j][2].y = 0.0f;
                g->grid[i][j][2].z = r;
                g->grid[i][j][2].w = 1.0f;
                g->grid[i][j][3].x = 2.0f;
                g->grid[i][j][3].y = 0.0f;
                g->grid[i][j][3].z = r;
                g->grid[i][j][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[i][j][k], &m4, &g->grid[i][j][k]);
                }
                func_00187B00(&g->grid[i][j][2], &g->grid[i][j][2], &v);
                func_00187B00(&g->grid[i][j][3], &g->grid[i][j][3], &v);
                g->gc[i][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 3; i++) {
            g->burst[i].on = 0;
        }
        g->ns = 0;
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jp2[i]);
    }
    if (g->t > 0x64 && g->t < 0xF8) {
        g->ring[g->nr].on = 1;
        g->ring[g->nr].t = 1;
        func_00101080(&g->ring[g->nr].p, 3.0f);
        func_00187B00(&g->ring[g->nr].p, &g->ring[g->nr].p, &g->tgt);
        for (j = 0; j < 32; j++) {
            g->ring[g->nr].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[g->nr].v[j], 1.0f);
        }
        for (j = 0; j < 32; j++) {
            func_00101080(&g->ring[g->nr].w[j], 3.5f);
        }
        g->nr++;
        if (g->nr >= 12) {
            g->nr = 0;
        }
    }

    for (i = 0; i < 12; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 12.0f * (0.8f + 0.2f * g->ring[i].t / 12.0f);
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
        alpha2 = (12 - g->ring[i].t) * 255 / 12;
        alpha = (12 - g->ring[i].t) * 128 / 12;
        for (j = 0; j < 32; j++) {
            s = func_00100D50(g->ring[i].t, 12, 1);
            if (j % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xFF;
                spr.c.g = 0x1E;
                spr.c.b = 0x60;
                spr.c.a = alpha2;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->ring[i].v[j], s);
            func_00187B00(&v, &v, &g->ring[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->ring[i].c[j] % 4 * 32;
            y = (g->ring[i].c[j] >> 2) * 32;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->ring[i].p);
        s = 0.2f + 0.8f * func_00100D50(g->ring[i].t, 12, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x1C;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        x = 96;
        y = 0;
        ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        r = 90.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 96;
        y = 0;
        ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.5f;
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
        s = func_00100D50(g->ring[i].t, 12, 1);
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 6; k++) {
                spr.c.r = 0xFF;
                spr.c.g = 0x5A;
                spr.c.b = 0x30;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->ring[i].w[j], s + 0.01f * k);
                func_00187B00(&v, &v, &g->ring[i].p);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 12) {
            g->ring[i].on = 0;
        }
    }

    if (g->t % 4 == 0 && g->t > 0x63 && g->t < 0xF8) {
        i = g->nb;
        (void)i;
        g->burst[i].on = 1;
        g->burst[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (j = 0; j < 2; j++) {
            g->burst[i].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->burst[i].pos[j] = g->jp[j];
        }
        for (i = 0; i < 2; i++) {
            g->spark[c].pos[i] = g->jp2[i];
            for (k = 0; k < 8; k++) {
                g->spark[c].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[i][k], 0.5f);
            }
        }
        g->nb++;
        if (g->nb >= 3) {
            g->nb = 0;
        }
        g->ns++;
        if (g->ns >= 16) {
            g->ns = 0;
        }
    }

    ((Quad_b454_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b454_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b454_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b454_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 3; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (3 - g->burst[i].t) * 0x56 / 3;
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x30;
        pk.v[0].c.b = 0x54;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->burst[i].t / 3.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 2; l++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->burst[i].pos[l]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->burst[i].rot[l], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (k = 0; k < 8; k++) {
                for (j = 0; j < 16; j++) {
                    x = g->gc[k][j] % 4 * 32;
                    y = (g->gc[k][j] >> 2) * 32;
                    u0 = x / 128.0f;
                    u1 = (32.0f + x) / 128.0f;
                    w1 = y / 64.0f;
                    w0 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = w0;
                    pk.v[1].s = u1;
                    pk.v[1].t = w0;
                    pk.v[2].s = u0;
                    pk.v[2].t = w1;
                    pk.v[3].s = u1;
                    pk.v[3].t = w1;
                    if (func_002058D0(g->grid[k][j], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 45.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->burst[i].t, 3, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x56;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 2; j++) {
            v = g->burst[i].pos[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 3) {
            g->burst[i].on = 0;
        }
    }

    ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
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
        spr.c.r = 0x9E;
        spr.c.g = 0x9E;
        spr.c.b = 0x9E;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[i].t, 16, 1);
        for (l = 0; l < 2; l++) {
            for (j = 0; j < 8; j++) {
                func_00187B48(&v, &g->spark[i].v[l][j], s);
                func_00187B00(&v, &v, &g->spark[i].pos[l]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[i].c[l][j] % 4 * 32;
                y = (g->spark[i].c[l][j] >> 2) * 32;
                ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 16) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x40) {
        g->on2 = 1;
        g->t2 = 0;
        g->p2 = g->pos;
        g->p2.y += 17.0f;
        g->p2.z += -10.0f * g->obj;
        for (j = 0; j < 128; j++) {
            g->c2[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v2[j], 1.0f);
        }
    }
    if (g->on2 == 1) {
        ((Spr_b454_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b454_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b454_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b454_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b454_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 6.0f * (0.5f + 0.5f * g->t2 / 48.0f);
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
        alpha = (48 - g->t2) * 128 / 48;
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->t2, 48, 1);
        w1 = -30.0f * g->t2 / 48.0f;
        for (j = 0; j < 128; j++) {
            func_00187B48(&v, &g->v2[j], s);
            func_00187B00(&v, &v, &g->p2);
            v.y += w1;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->c2[j] % 2 * 64;
            y = (g->c2[j] >> 1) * 64;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->u = (x + 64) << 4;
            ((Uv_b454_01E00080 *)(s32)&spr.uv1)->v = (y + 64) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t2++;
        if (g->t2 > 48) {
            g->on2 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x124 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -64) >> 10) + 0x80));
    if (g->t == 0x5A) {
        ret = 1;
    } else {
        if (g->t > 0x64 && g->t < 0xF8) {
            ret = 6;
        }
        if (g->t == 0xF8) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x124) {
        ret = 8;
    }
    return ret;
}
