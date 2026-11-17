#include "common.h"

/* shape b296:01E00080 (b296), 2001 insns, 1 copy: b296 scene manager (b440:01E00080's twin, ported): setup clears the
   0xA3B0 scene, takes both units, two textures, the target and joints 9 / 10 / 0x1C / 0x1D, builds an 8x16 grid of
   randomly twisted 4-point blades on a cone and a 32x17 ring grid and tints the unit black; else on 0x44..0xBD spawns
   a 12-slot ring burst at the target (32 sprites, a ground flare and 16x12 trails), every 4th frame a 2-slot two-limb
   blade-quad burst and 16-slot 8-sprite puffs at joints 1 and 3, from frame 0 a 0x31-frame render-to-texture cone
   (func_001F7070 with func_01E01FD0); returns 1 / 6 / 2 / 8 at 0x39 / 0x44..0xBD / 0xBE / >0xEA */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b296_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b296_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b296_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b296_01E00080 c;
    Uv_b296_01E00080 uv0;
    Xyz_b296_01E00080 p0;
    Uv_b296_01E00080 uv1;
    Xyz_b296_01E00080 p1;
    u64 tail;
} Spr_b296_01E00080;

typedef struct {
    Rgbaq_b296_01E00080 c;
    f32 s, t;
    Xyz_b296_01E00080 p;
} Tv_b296_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b296_01E00080 v[4];
    u8 tail[0x20];
} Quad_b296_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b296_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f p;
    Vec4f v[32];
    Vec4f w[16];
} Ring_b296_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[2];
    Vec4f pos[2];
    Mtx_b296_01E00080 mat[2];
} Burst_b296_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Spark_b296_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    Vec4f pos;
    s32 jn[4];
    Vec4f jp[4];
    Mtx_b296_01E00080 mat[2];
    s32 nr;
    u8 pad114[0xC];
    Ring_b296_01E00080 ring[12];
    s32 nb;
    u8 pad29A4[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Burst_b296_01E00080 burst[2];
    s32 ns;
    u8 pad4B94[0xC];
    Spark_b296_01E00080 spark[16];
    u8 on2;
    u8 pad5FA1[3];
    s32 t2;
    u8 pad5FA8[8];
    Vec4f cone[32][17];
    Vec4f cone2[32][17];
} Scene_b296_01E00080;

static s32 func_01E00080_b296(s32 arg0, s32 code) {
    Scene_b296_01E00080 *g = (Scene_b296_01E00080 *)arg0;
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
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
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
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern void func_001F63F0(s32, s32, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern f32 func_00205DF0(void *, f32);
    extern void func_001F6D00(s32);
    extern void b296_01E01FD0();
    extern s32 func_01E02900_b296;
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 c;
    s32 x;
    s32 y;
    s32 ang;
    s32 n;
    u8 alpha;
    f32 r;
    f32 s;
    f32 z;
    f32 w0;
    f32 w1;
    f32 u0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b296_01E00080 m4;
    Vec4f v;
    Spr_b296_01E00080 spr __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    Quad_b296_01E00080 pk __attribute__((aligned(8)));
    f32 depth;
    u8 col[4] __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA3B0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 9, 1);
        g->jn[1] = func_001F5560(g->unitA, 10, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x1C, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x1D, 0);
        g->nr = 0;
        for (i = 0; i < 12; i++) {
            g->ring[i].on = 0;
        }
        g->nb = 0;
        for (i = 0; i < 8; i++) {
            z = -400.0f * (i + 1) / 8.0f;
            s = -400.0f * i / 7.0f;
            r = 4.0f * (8 - (i + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                ang = ((j << 16) >> 4) + ((i << 13) >> 3) & 0xFFFF;
                v.x = r * func_0020B550(ang);
                v.y = r * func_0020B480(ang);
                v.z = s;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[i][j][0].x = -5.0f;
                g->grid[i][j][0].y = 0.0f;
                g->grid[i][j][0].z = 0.0f;
                g->grid[i][j][0].w = 1.0f;
                g->grid[i][j][1].x = 5.0f;
                g->grid[i][j][1].y = 0.0f;
                g->grid[i][j][1].z = 0.0f;
                g->grid[i][j][1].w = 1.0f;
                g->grid[i][j][2].x = -5.0f;
                g->grid[i][j][2].y = 0.0f;
                g->grid[i][j][2].z = z;
                g->grid[i][j][2].w = 1.0f;
                g->grid[i][j][3].x = 5.0f;
                g->grid[i][j][3].y = 0.0f;
                g->grid[i][j][3].z = z;
                g->grid[i][j][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[i][j][k], &m4, &g->grid[i][j][k]);
                }
                g->gc[i][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 2; i++) {
            g->burst[i].on = 0;
        }
        g->ns = 0;
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 32; i++) {
            r = 35.0f * (32 - i) / 32.0f;
            for (j = 0; j < 17; j++) {
                g->cone[i][j].x = r * func_0020B550((j << 16) >> 4);
                g->cone[i][j].y = r * func_0020B480((j << 16) >> 4);
                g->cone[i][j].z = 0.0f;
                g->cone[i][j].w = 1.0f;
            }
        }
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (i = 0; i < 4; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 2; i++) {
        n = i * 2;
        func_00187B18(&v, &g->jp[n + 1], &g->jp[n]);
        func_00100E40(&g->mat[i], &v);
    }
    if (g->t > 0x43 && g->t < 0xBE) {
        g->ring[g->nr].on = 1;
        g->ring[g->nr].t = 1;
        func_00101080(&g->ring[g->nr].p, 2.5f);
        func_00187B00(&g->ring[g->nr].p, &g->ring[g->nr].p, &g->tgt);
        for (j = 0; j < 32; j++) {
            g->ring[g->nr].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[g->nr].v[j], 1.2f);
        }
        for (j = 0; j < 16; j++) {
            func_00101080(&g->ring[g->nr].w[j], 2.0f);
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
        ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (12 - g->ring[i].t) * 128 / 12;
        for (j = 0; j < 32; j++) {
            s = func_00100D50(g->ring[i].t, 12, 1);
            if (j % 2 == 0) {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x32;
                spr.c.g = 0x40;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x40;
                spr.c.g = 0x80;
                spr.c.b = 0x32;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->ring[i].v[j], s);
            func_00187B00(&v, &v, &g->ring[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->ring[i].c[j] % 4 * 32;
            y = (g->ring[i].c[j] >> 2) * 32;
            ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (u32)(228.0f * ((f32)(12 - g->ring[i].t) / 12.0f));
        spr.c.r = 0x40;
        spr.c.g = 0xB4;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 96;
        y = 0;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 96;
        y = 0;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        for (j = 0; j < 16; j++) {
            for (k = 0; k < 12; k++) {
                spr.c.r = 0x64;
                spr.c.g = 0x40;
                spr.c.b = 0x80;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->ring[i].w[j], s + 0.008f * k);
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

    if (g->t % 4 == 0 && g->t > 0x3F && g->t < 0xBE) {
        i = g->nb;
        (void)i;
        g->burst[i].on = 1;
        g->burst[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (j = 0; j < 2; j++) {
            n = j * 2 + 1;
            g->burst[i].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->burst[i].pos[j] = g->jp[n];
            g->burst[i].mat[j] = g->mat[j];
        }
        for (j = 0; j < 2; j++) {
            n = j * 2 + 1;
            g->spark[c].pos[j] = g->jp[n];
            for (k = 0; k < 8; k++) {
                g->spark[c].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[j][k], 0.7f);
            }
        }
        g->nb++;
        if (g->nb >= 2) {
            g->nb = 0;
        }
        g->ns++;
        if (g->ns >= 16) {
            g->ns = 0;
        }
    }

    ((Quad_b296_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b296_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b296_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b296_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 2; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (2 - g->burst[i].t) * 0x56 / 2;
        pk.v[0].c.r = 0x40;
        pk.v[0].c.g = 0x64;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->burst[i].t / 2.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 2; l++) {
            func_0020EB40(m);
            func_00187B60(m2, (void *)&g->burst[i].mat[l], &g->jp[l * 2 + 1]);
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
        ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 80.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->burst[i].t, 2, 1));
        (void)alpha;
        spr.c.r = 0xC8;
        spr.c.g = 0x40;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 2; j++) {
            v = g->burst[i].pos[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 2) {
            g->burst[i].on = 0;
        }
    }

    ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        r = 12.0f * (0.5f + 0.5f * g->spark[i].t / 16.0f);
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
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
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
                ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
    }
    func_001F63F0(g->unitA, 0, 0);
    if (g->on2 == 1) {
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        ((Spr_b296_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b296_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b296_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b296_01E00080 *)(s32)&spr)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_01E02900_b296 = (s32)g;
        func_001F7070(1, &a, b, 0, b296_01E01FD0);
        func_00208460();
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        x = 0;
        ((Spr_b296_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b296_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b296_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        depth = func_00205DF0(&g->pos, 0.0f);
        func_00207FD0(buf, ot, (u32)depth);
        g->t2++;
        if (g->t2 > 0x30) {
            g->on2 = 0;
            func_001F63F0(g->unitA, 0, 0);
        }
    }

    func_001F6D00((u8)((func_00101050(0xEA - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -64) >> 10) + 0x80));
    if (g->t == 0x39) {
        ret = 1;
    } else {
        if (g->t > 0x43 && g->t < 0xBE) {
            ret = 6;
        }
        if (g->t == 0xBE) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xEA) {
        ret = 8;
    }
    return ret;
}

/* shape b296:01E01FD0, 561 insns, 1 copy (-O3,p): draws a two-layer 32x17 cone grid (b766:01E02B40 with the cosine-
   power fade call kept, b511:01E03A70's): a sine-rippled ring grid fading with the timer, triangles to an apex for
   the last row, textured quads elsewhere */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b296_01E01FD0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b296_01E01FD0;

typedef struct {
    Rgbaq_b296_01E01FD0 c;
    f32 s, t;
    Xyz_b296_01E01FD0 p;
} Tv_b296_01E01FD0;

typedef struct {
    u64 d;
} Reg_b296_01E01FD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b296_01E01FD0 v[3];
    u64 pad58;
    Reg_b296_01E01FD0 tex0;
    Reg_b296_01E01FD0 tex1;
    u64 tail;
} Tri_b296_01E01FD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b296_01E01FD0 v[4];
    u64 pad70;
    Reg_b296_01E01FD0 tex0;
    Reg_b296_01E01FD0 tex1;
    u64 tail;
} Quad_b296_01E01FD0;

typedef struct {
    u8 pad0[0x30];
    Vec4f pos;
    u8 pad40[0x5F64];
    s32 t;
    u8 pad5FA8[8];
    union {
        Vec4f lo[40][17];
        struct {
            u8 pad[0x2200];
            Vec4f hi[32][17];
        } s;
    } u;
} Obj_b296_01E01FD0;

extern Obj_b296_01E01FD0 *func_01E02900_b296;

#pragma optimization_level 3

static void func_01E01FD0_b296(void *buf) {
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void *func_00207650(void *, void *, s32, s32);
    Obj_b296_01E01FD0 *g __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f v;
    Tri_b296_01E01FD0 tri __attribute__((aligned(8)));
    Quad_b296_01E01FD0 pk __attribute__((aligned(8)));
    Rgbaq_b296_01E01FD0 c;
    f32 depth;
    void *p;
    s32 k;
    f32 s;
    f32 h;
    f32 rad;
    f32 w;
    s32 t;
    f32 r;
    u16 a;
    u16 b;

    g = func_01E02900_b296;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0((s32)m3);
    func_0020EB40(m);
    v = g->pos;
    func_00187B60(m2, m3, &v);
    func_0020BC00((s32)m, m2);
    ((Tri_b296_01E01FD0 *)(s32)&tri)->flags = 0x33;
    ((Tri_b296_01E01FD0 *)(s32)&tri)->size = 9;
    ((Tri_b296_01E01FD0 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b296_01E01FD0 *)(s32)&tri)->pad4 = 0;
    ((Quad_b296_01E01FD0 *)(s32)&pk)->flags = 0x34;
    ((Quad_b296_01E01FD0 *)(s32)&pk)->size = 0xC;
    ((Quad_b296_01E01FD0 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b296_01E01FD0 *)(s32)&pk)->pad4 = 0;
    p = (void *)func_00208870(func_0020F290((s32)p), -1, 1, &tri.tex0, &tri.tex1);
    pk.tex0 = tri.tex0;
    pk.tex1 = tri.tex1;
    p = (void *)func_0020F290((s32)p);
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((s64)0x700 << 32) | 0xA0000A);
    ((Tri_b296_01E01FD0 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Quad_b296_01E01FD0 *)(s32)&pk)->flags |= 0x800;
    s = func_00100FF0(g->t, 48.0f, 24.0f);
    func_001A6C48(func_001A6970(func_0020B550((u16)(g->t % 64 << 16 >> 6))), 3.0f);
    w = 1.0f;
    r = s * w;
    tri.v[0].c.r = 0xFF;
    tri.v[0].c.g = 0xFF;
    tri.v[0].c.b = 0xFF;
    tri.v[0].c.a = (u32)(255.0f * r);
    tri.v[0].c.q = 1.0f;
    tri.v[1].c = tri.v[0].c;
    tri.v[2].c = tri.v[0].c;
    c = tri.v[0].c;
    pk.v[0].c = c;
    pk.v[1].c = c;
    pk.v[2].c = c;
    pk.v[3].c = c;
    t = g->t;
    for (i = 0; i < 32; i++) {
        rad = 35.0f * (f32)(32 - i) / 32.0f;
        h = (f32)(i + 1) / 32.0f;
        for (k = 0; k < 17; k++) {
            r = 1.0f + h * (0.3f * func_0020B480((u16)(t * 211 + (((i * 0x20000) >> 5) + ((k * 0x20000) >> 4)))));
            a = (s32)((f32)((k * 0x10000) >> 4) +
                      h * (5461.0f * func_0020B480((u16)(((i * 0x4000) >> 5) + t * 111))));
            g->u.s.hi[i][k].x = rad * r * func_0020B550(a);
            g->u.s.hi[i][k].y = rad * r * func_0020B480(a);
            g->u.s.hi[i][k].z = 0.0f;
            g->u.s.hi[i][k].w = 1.0f;
        }
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    for (i = 0; i < 32; i++) {
        if (i == 31) {
            for (k = 0; k < 16; k++) {
                if (func_00100B00(&v, &g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], m, &tri, &depth) == 1) {
                    func_00100C60(&tri.v[0].s, &tri.v[0].p, 0, 0);
                    func_00100C60(&tri.v[1].s, &tri.v[1].p, 0, 0);
                    func_00100C60(&tri.v[2].s, &tri.v[2].p, 0, 0);
                    if (func_00100B00(&v, &g->u.lo[i][k], &g->u.lo[i][k + 1], m, &tri, &depth) == 1) {
                        tri.v[0].p.z = 0xFFFFF8;
                        tri.v[1].p.z = tri.v[0].p.z;
                        tri.v[2].p.z = tri.v[0].p.z;
                        p = func_00207650(p, &tri, 0, 0);
                    }
                }
            }
        } else {
            for (k = 0; k < 16; k++) {
                if (func_00100BA0(&g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], &g->u.s.hi[i + 1][k],
                                  &g->u.s.hi[i + 1][k + 1], m, &pk, &depth) == 1) {
                    func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                    func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                    func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                    func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                    if (func_00100BA0(&g->u.lo[i][k], &g->u.lo[i][k + 1], &g->u.lo[i + 1][k],
                                      &g->u.lo[i + 1][k + 1], m, &pk, &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        p = func_00207650(p, &pk, 0, 0);
                    }
                }
            }
        }
    }
    func_00209F70(p, 0);
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b296", func_01E02900_b296);
