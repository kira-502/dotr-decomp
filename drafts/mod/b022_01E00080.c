#include "common.h"

/* shape b022:01E00080 (b022), 2020 insns, 1 copy: b022 scene manager (b226:01E00080's family with 10 burst slots,
   written from the asm): setup clears the 0xCB40 scene, takes both units, three textures, joint 0x66 and the target,
   seeds a 17x17 phase table; projects the unit to the screen each frame; on 0x3C..0xCC every 8th frame fires a burst
   toward the target (rippled 17x17 cone as textured quads, puff trail, 16-spark ring, 64-sprite double wave at its
   end); at 0x14 a 32-frame radial blur of the unit (func_001F7060 render-to-texture, 3x8 triangles from table
   D_28B960); returns 1 / 6 / 2 / 8 at 0x51 / 0x5C..0x12C / 0x12D / >0x14D */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b022_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b022_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b022_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b022_01E00080 c;
    Uv_b022_01E00080 uv0;
    Xyz_b022_01E00080 p0;
    Uv_b022_01E00080 uv1;
    Xyz_b022_01E00080 p1;
    u8 tail[0x20];
} Spr_b022_01E00080;

typedef struct {
    Rgbaq_b022_01E00080 c;
    f32 s, t;
    Xyz_b022_01E00080 p;
} Tv_b022_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b022_01E00080 v[4];
    u8 tail[0x20];
} Tex_b022_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b022_01E00080 c;
        Uv_b022_01E00080 uv;
        Xyz_b022_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b022_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 n;
    u8 padC[4];
    Vec4f base;
    Vec4f dir;
    f32 mat[4][4];
} Burst_b022_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f p;
    Vec4f v[4];
} Puff_b022_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f p;
    Vec4f v[16];
} Ring_b022_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[64];
    u8 pad48[8];
    Vec4f p;
    Vec4f v[64];
} Wave_b022_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f pos;
    Vec4f scr;
    Vec4f tgt;
    s32 m0;
    u8 pad54[0xC];
    Vec4f pos0;
    s32 nburst;
    u8 pad74[0xC];
    Vec4f grid[17][17];
    s32 phase[17][17];
    u8 pad1714[0xC];
    Burst_b022_01E00080 burst[10];
    Puff_b022_01E00080 puff[10][1][32];
    Ring_b022_01E00080 ring[10];
    s32 nwave;
    u8 pad9F64[0xC];
    Wave_b022_01E00080 wave[10];
    u8 on2;
    u8 padCB31[3];
    s32 t2;
    u8 padCB38[8];
} Scene_b022_01E00080;

static s32 func_01E00080_b022(s32 arg0, s32 code) {
    Scene_b022_01E00080 *g = (Scene_b022_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18();
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_001A6C18(f32, f32);
    extern void func_00101080(void *, f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern s32 func_00205630(s32, s32, s32, s32, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u8 D_0030FF00[];
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    s32 ot;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 n;
    s32 y;
    s32 x;
    s32 ang;
    s32 buf;
    u8 alpha;
    f32 a;
    f32 d;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 u0;
    f32 u1;
    f32 t0;
    f32 t1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f v2;
    Vec4f v3;
    Spr_b022_01E00080 spr __attribute__((aligned(8)));
    Tex_b022_01E00080 pk __attribute__((aligned(8)));
    Tri_b022_01E00080 tri __attribute__((aligned(8)));
    Xyz_b022_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xCB40);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->m0 = func_001F5560(g->unitA, 0x66, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->nburst = 0;
        for (i = 0; i < 17; i++) {
            for (j = 0; j < 16; j++) {
                g->phase[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
            g->phase[i][16] = g->phase[i][0];
        }
        for (i = 0; i < 10; i++) {
            g->burst[i].on = 0;
            g->burst[i].n = 0;
        }
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 32; k++) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 10; i++) {
            g->ring[i].on = 0;
        }
        g->nwave = 0;
        for (i = 0; i < 10; i++) {
            g->wave[i].on = 0;
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
    g->scr.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr.z = func_0017B340(xyz.z);
    g->scr.w = 1.0f;
    if (g->scr.x < 0.0f) {
        g->scr.x = 0.0f;
    }
    if (g->scr.x > 640.0f) {
        g->scr.x = 640.0f;
    }
    if (g->scr.y < 0.0f) {
        g->scr.y = 0.0f;
    }
    if (g->scr.y > 448.0f) {
        g->scr.y = 448.0f;
    }
    func_001F5620(g->unitA, g->m0, &g->pos0);
    g->pos0.z += 0.0f * g->obj;
    if (g->t > 0x3B && g->t < 0xCD && g->t % 8 == 0) {
        n = g->nburst;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        g->burst[n].base = g->pos0;
        func_00101080(&v, 1.5f);
        func_00187B00(&v, &v, &g->tgt);
        func_00187B18(&g->burst[n].dir, &v, &g->pos0);
        n = g->nburst;
        (void)n;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        g->ring[n].p = g->pos0;
        for (j = 0; j < 16; j++) {
            g->ring[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[n].v[j], 0.7f);
        }
        g->nburst++;
        if (g->nburst >= 10) {
            g->nburst = 0;
        }
    }

    ((Tex_b022_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b022_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b022_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b022_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[0], 1);
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 10; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_00187B48(&v, &g->burst[i].dir, g->burst[i].t / 32.0f);
        v.y += 0.0f * func_0020B550(((g->burst[i].t << 15) >> 5) & 0xFFFF);
        func_00187B48(&v2, &g->burst[i].dir, (g->burst[i].t + 1) / 32.0f);
        v2.y += 0.0f * func_0020B550((((g->burst[i].t + 1) << 15) >> 5) & 0xFFFF);
        func_00187B18(&v2, &v2, &v);
        ang = -(s32)(65536.0f * (func_001A6C18(v2.y, v2.z) / 6.2831855f)) & 0xFFFF;
        func_0020BBB0(g->burst[i].mat);
        func_00100E00(g->burst[i].mat, ang, 0);
        func_00187B00(&v, &v, &g->burst[i].base);
        func_00187B60(m2, g->burst[i].mat, &v);
        v3 = v;
        func_0020BC00(m, m2);
        for (k = 0; k < 17; k++) {
            a = 3.0f * func_0020B480((k << 15) >> 4);
            d = func_001A6C60(func_001A6C48(3.0f, 2.0f) - func_001A6C48(a, 2.0f));
            for (j = 0; j < 17; j++) {
                x = (g->phase[k][j] - g->burst[i].t * 0x457) & 0xFFFF;
                y = ((i << 16) / 10 + (k % 8 << 16 >> 3) + (j % 8 << 16 >> 3) - g->burst[i].t * 0x8AE) & 0xFFFF;
                r = 1.0f + 0.1f * func_0020B550(x);
                r = d * (r + 0.1f * func_0020B550(y));
                y = (j << 16) >> 4;
                g->grid[k][j].x = r * func_0020B550(y);
                g->grid[k][j].y = r * func_0020B480(y);
                g->grid[k][j].z = 2.0f * (-1.5f + a);
                g->grid[k][j].w = 1.0f;
            }
        }
        w = -1.0f * (g->burst[i].t % 24) / 24.0f;
        for (k = 0; k < 16; k++) {
            u0 = (f32)(k % 16) / 16.0f + w;
            u1 = (f32)(k % 16 + 1) / 16.0f + w;
            alpha = (16 - k) * 150 >> 4;
            pk.v[0].c.r = 0x70;
            pk.v[0].c.g = 0xFF;
            pk.v[0].c.b = 0x60;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            alpha = (16 - (k + 1)) * 150 >> 4;
            (void)alpha;
            pk.v[2].c.r = 0x70;
            pk.v[2].c.g = 0xFF;
            pk.v[2].c.b = 0x60;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            for (j = 0; j < 16; j++) {
                t0 = (f32)(j % 16) / 16.0f;
                t1 = (f32)(j % 16 + 1) / 16.0f;
                pk.v[0].s = u0;
                pk.v[0].t = t0;
                pk.v[1].s = u0;
                pk.v[1].t = t1;
                pk.v[2].s = u1;
                pk.v[2].t = t0;
                pk.v[3].s = u1;
                pk.v[3].t = t1;
                if (func_00100BA0(&g->grid[k][j], &g->grid[k][j + 1], &g->grid[k + 1][j], &g->grid[k + 1][j + 1], m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        n = g->burst[i].n;
        g->burst[i].n++;
        if (g->burst[i].n >= 32) {
            g->burst[i].n = 0;
        }
        g->puff[i][0][n].on = 1;
        g->puff[i][0][n].t = 0;
        g->puff[i][0][n].p = v;
        for (j = 0; j < 4; j++) {
            g->puff[i][0][n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->puff[i][0][n].v[j], 0.7f);
        }
        g->burst[i].t++;
        if (g->burst[i].t > 32) {
            g->burst[i].on = 0;
            n = g->nwave;
            g->wave[n].on = 1;
            g->wave[n].t = 0;
            g->wave[n].p = v3;
            for (j = 0; j < 64; j++) {
                g->wave[n].c[j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->wave[n].v[j], 1.7f);
            }
            g->nwave++;
            if (g->nwave >= 10) {
                g->nwave = 0;
            }
        }
    }

    ((Spr_b022_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b022_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b022_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b022_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b022_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                if (g->puff[i][j][k].on == 0) {
                    continue;
                }
                r = 8.0f * (0.6f + 0.4f * g->puff[i][j][k].t / 32.0f);
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
                alpha = (32 - g->puff[i][j][k].t) * 80 >> 5;
                spr.c.r = 0x70;
                spr.c.g = 0xFF;
                spr.c.b = 0x60;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.2f + 0.8f * g->puff[i][j][k].t / 32.0f;
                for (q = 0; q < 4; q++) {
                    x = g->puff[i][j][k].c[q] % 4 * 32;
                    y = (g->puff[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b022_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b022_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b022_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b022_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->puff[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->puff[i][j][k].p);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->puff[i][j][k].t++;
                if (g->puff[i][j][k].t > 32) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b022_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b022_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b022_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b022_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b022_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 10; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.6f + 0.4f * g->ring[i].t / 16.0f);
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
        alpha = (16 - g->ring[i].t) << 6 >> 4;
        spr.c.r = 0x70;
        spr.c.g = 0xFF;
        spr.c.b = 0x60;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.2f + 0.8f * func_00100D50(g->ring[i].t, 0x10, 1);
        for (q = 0; q < 16; q++) {
            x = g->ring[i].c[q] % 4 * 32;
            y = (g->ring[i].c[q] >> 2) * 32;
            ((Uv_b022_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->ring[i].v[q], s);
            func_00187B00(&v, &v, &g->ring[i].p);
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

    ((Spr_b022_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b022_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b022_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b022_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b022_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 10; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        r = 13.0f * (0.6f + 0.4f * g->wave[i].t / 64.0f);
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
        alpha = (64 - g->wave[i].t) * 50 >> 6;
        s = 0.2f + 0.8f * func_00100D50(g->wave[i].t, 0x40, 1);
        h = 50.0f * (g->wave[i].t / 64.0f);
        for (q = 0; q < 64; q++) {
            func_00208700(&spr, g->tex[1], 1);
            x = g->wave[i].c[q] % 4 * 32;
            y = (g->wave[i].c[q] >> 2) * 32;
            ((Uv_b022_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b022_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->wave[i].v[q], s);
            func_00187B00(&v, &v, &g->wave[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            spr.c.r = 0x70;
            spr.c.g = 0xFF;
            spr.c.b = 0x60;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            func_00208700(&spr, g->tex[2], 1);
            v.y += h;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            spr.c.r = 0x70;
            spr.c.g = 0xFF;
            spr.c.b = 0x60;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 64) {
            g->wave[i].on = 0;
        }
    }

    if (g->t == 0x14) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b022_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b022_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b022_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b022_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b022_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(1));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (32 - g->t2) * 228 >> 5;
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0x40;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = 0;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0xFF;
        tri.v[1].c.g = 0x40;
        tri.v[1].c.b = 0xFF;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        a = 0.3f * func_00100D50(g->t2, 32, 1);
        for (i = 0; i < 3; i++) {
            r = 1.0f + a * (i + 1) / 3.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b022_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b022_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b022_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b022_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b022_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b022_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18(&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48(&out[0], &out[0], r);
                func_00187B48(&out[1], &out[1], r);
                func_00187B00(&out[0], &out[0], &g->scr);
                func_00187B00(&out[1], &out[1], &g->scr);
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                tri.v[0].p.x = (x + 0x6C0) << 4;
                tri.v[0].p.y = (y + 0x720) << 4;
                tri.v[0].p.z = 0xFFFFF8;
                tri.v[0].p.f = 0;
                x = (s32)out[0].x;
                y = (s32)out[0].y;
                tri.v[1].p.x = (x + 0x6C0) << 4;
                tri.v[1].p.y = (y + 0x720) << 4;
                tri.v[1].p.z = 0xFFFFF8;
                tri.v[1].p.f = 0;
                x = (s32)out[1].x;
                y = (s32)out[1].y;
                tri.v[2].p.x = (x + 0x6C0) << 4;
                tri.v[2].p.y = (y + 0x720) << 4;
                tri.v[2].p.z = 0xFFFFF8;
                tri.v[2].p.f = 0;
                func_002075F0(&tri, 0, 0);
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 32) {
            g->on2 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x14D - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -64) >> 10) + 0x80));
    if (g->t == 0x51) {
        ret = 1;
    } else {
        if (g->t > 0x5B && g->t < 0x12D) {
            ret = 6;
        }
        if (g->t == 0x12D) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x14D) {
        ret = 8;
    }
    return ret;
}
