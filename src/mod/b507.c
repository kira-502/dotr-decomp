#include "common.h"

/* shape b507:01E00080 (b507), 1721 insns, 1 copy: grid-quad burst scene: ST values in the family order (u0, u1, t0,
   t1) with the floats declared u0, t0, u1, t1 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b507_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b507_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b507_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b507_01E00080 c;
    Uv_b507_01E00080 uv0;
    Xyz_b507_01E00080 p0;
    Uv_b507_01E00080 uv1;
    Xyz_b507_01E00080 p1;
    u8 tail[0x20];
} Spr_b507_01E00080;

typedef struct {
    Rgbaq_b507_01E00080 c;
    f32 s, t;
    Xyz_b507_01E00080 p;
} Tv_b507_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b507_01E00080 v[4];
    u8 tail[0x20];
} Tex_b507_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f pos;
    Vec4f v[32];
    Vec4f w[32];
} Burst_b507_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b507_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 ang[1];
    u8 padC[4];
    Vec4f pos[1];
    Mtx_b507_01E00080 mat[1];
} Ring_b507_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][8];
    Vec4f pos[1];
    Vec4f v[1][8];
} Puff_b507_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    Vec4f top;
    s32 m[2];
    u8 pad48[8];
    Vec4f pos[2];
    Mtx_b507_01E00080 mat;
    s32 na;
    u8 padB4[0xC];
    Burst_b507_01E00080 a[12];
    s32 nb;
    u8 pad3544[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Ring_b507_01E00080 b[3];
    s32 nc;
    u8 pad56F4[0xC];
    Puff_b507_01E00080 c[16];
} Scene_b507_01E00080;

static s32 func_01E00080_b507(s32 arg0, s32 code) {
    Scene_b507_01E00080 *g = (Scene_b507_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00101080(void *, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 h;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 n;
    s32 n2;
    s32 c;
    s32 x;
    s32 y;
    u8 alpha;
    u8 alpha2;
    f32 r;
    f32 s;
    f32 f;
    f32 z;
    f32 u0;
    f32 t0;
    f32 u1;
    f32 t1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    f32 mt[4][4];
    Vec4f v;
    Spr_b507_01E00080 spr __attribute__((aligned(8)));
    Tex_b507_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x6100);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->m[0] = func_001F5560(g->unitA, 0x21, 1);
        g->m[1] = func_001F5560(g->unitA, 0x23, 0);
        g->na = 0;
        for (q = 0; q < 12; q++) {
            g->a[q].on = 0;
        }
        g->nb = 0;
        for (i = 0; i < 8; i++) {
            z = -140.0f * (i + 1) / 8.0f;
            f = -140.0f * i / 7.0f;
            r = 5.0f * (8 - (i + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                x = (((j << 16) >> 4) + ((i << 13) >> 3)) & 0xFFFF;
                v.x = r * func_0020B550(x);
                v.y = r * func_0020B480(x);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(mt, &v);
                func_00100E00(mt, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
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
                    func_001878E0(&g->grid[i][j][k], mt, &g->grid[i][j][k]);
                }
                g->gc[i][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 3; i++) {
            g->b[i].on = 0;
        }
        g->nc = 0;
        for (i = 0; i < 16; i++) {
            g->c[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->top);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    func_00187B18(&v, &g->pos[1], &g->pos[0]);
    func_00100E40(&g->mat, &v);
    if (g->t > 0x46 && g->t < 0xD7) {
        g->a[g->na].on = 1;
        g->a[g->na].t = 1;
        func_00101080(&g->a[g->na].pos, 1.0f);
        func_00187B00(&g->a[g->na].pos, &g->a[g->na].pos, &g->tgt);
        for (j = 0; j < 32; j++) {
            g->a[g->na].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->a[g->na].v[j], 0.5f);
        }
        for (j = 0; j < 32; j++) {
            func_00101080(&g->a[g->na].w[j], 1.75f);
        }
        g->na++;
        if (g->na >= 12) {
            g->na = 0;
        }
    }

    for (i = 0; i < 12; i++) {
        if (g->a[i].on == 0) {
            continue;
        }
        ((Spr_b507_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b507_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b507_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b507_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b507_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 6.0f * (0.8f + 0.2f * g->a[i].t / 12.0f);
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
        alpha = (12 - g->a[i].t) * 255 / 12;
        alpha2 = (12 - g->a[i].t) * 128 / 12;
        for (j = 0; j < 32; j++) {
            s = func_00100D50(g->a[i].t, 12, 1);
            if (j % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = alpha2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x1E;
                spr.c.g = 0x60;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->a[i].v[j], s);
            func_00187B00(&v, &v, &g->a[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            c = g->a[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b507_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b507_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b507_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b507_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }

        ((Spr_b507_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b507_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b507_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b507_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b507_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->a[i].pos);
        f = 0.2f + 0.8f * func_00100D50(g->a[i].t, 12, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        spr.c.r = 0x1C;
        spr.c.g = 0x40;
        spr.c.b = 0xFF;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b507_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b507_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b507_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b507_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 45.0f;
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

        ((Spr_b507_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b507_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b507_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b507_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b507_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 0;
        ((Uv_b507_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b507_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b507_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b507_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 0.75f;
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
        f = func_00100D50(g->a[i].t, 12, 1);
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 6; k++) {
                spr.c.r = 0x30;
                spr.c.g = 0x5A;
                spr.c.b = 0xFF;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->a[i].w[j], f + 0.007f * k);
                func_00187B00(&v, &v, &g->a[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->a[i].t++;
        if (g->a[i].t > 12) {
            g->a[i].on = 0;
        }
    }

    if (g->t % 4 == 0) {
        if (g->t > 0x40 && g->t < 0xD7) {
            n = g->nb;
            (void)n;
            g->b[n].on = 1;
            g->b[n].t = 0;
            n2 = g->nc;
            (void)n2;
            g->c[n2].on = 1;
            g->c[n2].t = 0;
            for (j = 0; j < 1; j++) {
                g->b[n].ang[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
                g->b[n].pos[j] = g->pos[1];
                g->b[n].mat[j] = g->mat;
            }
            for (k = 0; k < 1; k++) {
                g->c[n2].pos[k] = g->pos[1];
                for (i = 0; i < 8; i++) {
                    g->c[n2].c[k][i] = (func_0019A5C8() >> 23) % 8;
                    func_00101080(&g->c[n2].v[k][i], 0.5f);
                }
            }
            g->nb++;
            if (g->nb >= 3) {
                g->nb = 0;
            }
            g->nc++;
            if (g->nc >= 16) {
                g->nc = 0;
            }
        }
    }

    ((Tex_b507_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b507_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b507_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b507_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 3; i++) {
        if (g->b[i].on == 0) {
            continue;
        }
        alpha = (3 - g->b[i].t) * 0x56 / 3;
        pk.v[0].c.r = 0x30;
        pk.v[0].c.g = 0x54;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        f = 0.5f + 0.5f * g->b[i].t / 3.0f;
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        for (h = 0; h < 1; h++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->b[i].mat[h], &g->b[i].pos[h]);
            func_00100E00(m2, g->b[i].ang[h], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (c = 0; c < 8; c++) {
                for (q = 0; q < 16; q++) {
                    x = g->gc[c][q] % 4 * 32;
                    y = (g->gc[c][q] >> 2) * 32;
                    u0 = x / 128.0f;
                    u1 = (32.0f + x) / 128.0f;
                    t0 = y / 64.0f;
                    t1 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = t1;
                    pk.v[1].s = u1;
                    pk.v[1].t = t1;
                    pk.v[2].s = u0;
                    pk.v[2].t = t0;
                    pk.v[3].s = u1;
                    pk.v[3].t = t0;
                    if (func_002058D0(g->grid[c][q], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }

        ((Spr_b507_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b507_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b507_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b507_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b507_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha2 = (u32)(0.0f * func_00100D50(g->b[i].t, 3, 1));
        (void)alpha2;
        spr.c.r = 0x14;
        spr.c.g = 0x56;
        spr.c.b = 0xFF;
        spr.c.a = alpha2;
        spr.c.q = 1.0f;
        for (h = 0; h < 1; h++) {
            v = g->b[i].pos[h];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 0;
            ((Uv_b507_01E00080 *)(s32)&spr.uv0)->u = 0x600;
            ((Uv_b507_01E00080 *)(s32)&spr.uv0)->v = x;
            ((Uv_b507_01E00080 *)(s32)&spr.uv1)->u = 0x800;
            ((Uv_b507_01E00080 *)(s32)&spr.uv1)->v = 0x200;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->b[i].t++;
        if (g->b[i].t > 3) {
            g->b[i].on = 0;
        }
    }

    ((Spr_b507_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b507_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b507_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b507_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b507_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->c[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->c[i].t / 16.0f);
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
        spr.c.r = 0xEE;
        spr.c.g = 0xEE;
        spr.c.b = 0xEE;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        f = func_00100D50(g->c[i].t, 16, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 8; k++) {
                func_00187B48(&v, &g->c[i].v[j][k], f);
                func_00187B00(&v, &v, &g->c[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                c = g->c[i].c[j][k];
                x = c % 4 * 32;
                y = (c >> 2) * 32;
                ((Uv_b507_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b507_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b507_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b507_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->c[i].t++;
        if (g->c[i].t > 16) {
            g->c[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x103 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x3C) {
        ret = 1;
    } else {
        if (g->t > 0x46 && g->t < 0xD7) {
            ret = 6;
        }
        if (g->t == 0xD7) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x103) {
        ret = 8;
    }
    return ret;
}
