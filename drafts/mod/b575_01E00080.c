#include "common.h"

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b575_01E00080;

typedef struct {
    u16 x;
    u16 y;
    u32 zf;
} Xy_b575_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b575_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b575_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b575_01E00080 c;
    Uv_b575_01E00080 uv0;
    Xyz_b575_01E00080 p0;
    Uv_b575_01E00080 uv1;
    Xyz_b575_01E00080 p1;
    u8 tail[0x20];
} Spr_b575_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b575_01E00080 c;
        Xyz_b575_01E00080 p;
    } v[4];
    u64 tail;
} Line_b575_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b575_01E00080 c;
        Xyz_b575_01E00080 p;
    } v[3];
    u64 tail;
} Edge_b575_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b575_01E00080 c;
        f32 s, t;
        Xyz_b575_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b575_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b575_01E00080;

typedef struct {
    Rgbaq_b575_01E00080 c;
    f32 s, t;
    Xy_b575_01E00080 p;
} Tv_b575_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b575_01E00080 v[4];
    u8 tail[0x20];
} Tex_b575_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[4][6];
} Burst_b575_01E00080;

typedef struct {
    Vec4f v[6];
    Vec4f n[2];
} Uvs_b575_01E00080;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Spin_b575_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[8];
    u8 pad18[8];
    Vec4f v[8];
} Ring_b575_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[4];
    u8 pad2C[4];
    Vec4f jp[4];
    Vec4f pos;
    f32 h;
    u8 on0;
    u8 pad85[3];
    s32 t0;
    u8 pad8C[4];
    Burst_b575_01E00080 burst[24];
    u8 on2;
    u8 pad2611[3];
    s32 t2;
    u8 pad2618[8];
    Uvs_b575_01E00080 uv[16][16];
    Vec4f grid[17][17];
    Vec4f nrm[16][16][2];
    Spin_b575_01E00080 spin[16][16];
    u8 on3;
    u8 padE431[3];
    s32 t3;
    u8 padE438[8];
    Ring_b575_01E00080 ring[32];
    u8 on4;
    u8 padF841[3];
    s32 t4;
    u16 c4[64];
    u8 padF8C8[8];
    Vec4f dv[64];
} Scene_b575_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b575(s32 arg0, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00100F60(void *, void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00205E70(s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern f32 D_0028BC10[][32][3];
    extern u8 D_0030FF00[];
    extern void func_00100E40(void *, void *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern f32 func_001A6C18(f32, f32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern u16 D_28BBF0[][4];
    Scene_b575_01E00080 *g = (Scene_b575_01E00080 *)arg0;
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 q;
    s32 x;
    s32 y;
    s32 a;
    u32 z;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 f;
    f32 p;
    f32 u;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b575_01E00080 m3;
    Vec4f cn[2];
    Vec4f out[4];
    Mtx_b575_01E00080 m4;
    Vec4f v;
    Vec4f d;
    Vec4f c;
    Vec4f e[4];
    s32 ang[4];
    Spr_b575_01E00080 spr __attribute__((aligned(8)));
    Tex_b575_01E00080 pk __attribute__((aligned(8)));
    Tri_b575_01E00080 tri __attribute__((aligned(8)));
    Edge_b575_01E00080 edge __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xFCD0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x14, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x1D, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x26, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x2F, 0);
        func_001F53C0(1, g->unitB, &g->pos);
        g->h = func_001F5860(g->unitB);
        if (g->h > 20.0f) {
            g->h = 20.0f;
        }
        g->on0 = 0;
        for (i = 0; i < 24; i++) {
            g->burst[i].on = 0;
        }
        g->on2 = 0;
        for (k = 0; k < 17; k++) {
            for (j = 0; j < 17; j++) {
                i = (k << 15) >> 4;
                r = g->h * func_0020B550(i & 0xFFFF);
                r += 0.5f * r * ((func_0019A5C8() >> 23) % 8) / 8.0f;
                h = -(5.0f * g->h) / 2.0f + 5.0f * g->h * k / 16.0f;
                if (k != 0 && k != 16) {
                    h += 5.0f * g->h / 16.0f / 2.0f * (4.0f - (func_0019A5C8() >> 23) % 8) / 4.0f;
                }
                i = ((j << 16) >> 4) + (((func_0019A5C8() >> 23) % 8 << 11) >> 3);
                i &= 0xFFFF;
                g->grid[k][j].x = r * func_0020B550(i);
                g->grid[k][j].y = h;
                g->grid[k][j].z = r * func_0020B480(i);
                g->grid[k][j].w = 1.0f;
            }
            g->grid[k][16] = g->grid[k][0];
        }
        for (k = 0; k < 16; k++) {
            for (i = 0; i < 16; i++) {
                func_00100F60(&g->nrm[k][i][0], &g->grid[k][i], &g->grid[k + 1][i], &g->grid[k + 1][i + 1]);
                func_00100F60(&g->nrm[k][i][1], &g->grid[k][i], &g->grid[k][i + 1], &g->grid[k + 1][i + 1]);
            }
        }
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                g->spin[i][j].a = (((func_0019A5C8() >> 23) % 256 * 333 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
                g->spin[i][j].b = (((func_0019A5C8() >> 23) % 256 * 222 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
                g->spin[i][j].c = (((func_0019A5C8() >> 23) % 256 * 111 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
            }
        }
        g->on3 = 0;
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                s = (64.0f + 512.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f) / 1024.0f;
                h = (64.0f + 320.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f) / 512.0f;
                for (a = 0; a < 6; a++) {
                    g->uv[i][j].v[a].x = s + 0.125f * (-0.5f + ((func_0019A5C8() >> 23) % 256) / 256.0f);
                    g->uv[i][j].v[a].y = h + 0.25f * (-0.5f + ((func_0019A5C8() >> 23) % 256) / 256.0f);
                    g->uv[i][j].v[a].z = 0.0f;
                    g->uv[i][j].v[a].w = 1.0f;
                }
                func_00100F60(&g->uv[i][j].n[0], &g->uv[i][j].v[0], &g->uv[i][j].v[1], &g->uv[i][j].v[2]);
                func_00100F60(&g->uv[i][j].n[1], &g->uv[i][j].v[3], &g->uv[i][j].v[4], &g->uv[i][j].v[5]);
            }
        }
        for (i = 0; i < 32; i++) {
            g->ring[i].on = 0;
            for (j = 0; j < 8; j++) {
                g->ring[i].c[j] = (func_0019A5C8() >> 23) % 4;
            }
        }
        for (i = 0; i < 64; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 4;
        }
        g->on4 = 0;
        return 0;
    }
    func_00205CA0(&m3);
    for (i = 0; i < 4; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    if (g->t == 0) {
        g->on0 = 1;
        g->t0 = 0;
    }
    ((Spr_b575_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b575_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b575_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b575_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b575_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    if (g->on0 == 1) {
        n = 0xC8 - g->t0;
        if (n > 32) {
            n = 32;
        }
        alpha = n * 0xFF >> 5;
        spr.c.r = 0xA4;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b575_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b575_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b575_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b575_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        k = g->t0;
        if (k > 32) {
            k = 32;
        }
        for (i = 0; i < 4; i++) {
            r = k * (10.0f * (1.0f - 0.3f * ((g->t0 + i) % 2))) / 32.0f;
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m3, &cn[0]);
            func_001878E0(&cn[1], &m3, &cn[1]);
            func_00187B00(&out[0], &cn[0], &g->jp[i]);
            func_00187B00(&out[1], &cn[1], &g->jp[i]);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t0++;
        if (g->t0 > 200) {
            g->on0 = 0;
        }
    }
    if (g->t > 0 && g->t < 0xA8) {
        n = g->t % 24;
        if (g->t < 0x2D) {
            g->burst[n].on = 1;
        } else {
            g->burst[n].on = 2;
        }
        g->burst[n].t = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 6; j++) {
                q = (j + (g->t + i)) % 32;
                g->burst[n].v[i][j].x = 1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][0];
                g->burst[n].v[i][j].y = 1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][1];
                g->burst[n].v[i][j].z = 1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][2];
                g->burst[n].v[i][j].w = 1.0f;
            }
        }
    }
    ((Tex_b575_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b575_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b575_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b575_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 24; i++) {
        if (g->burst[i].on != 0) {
            f = func_00100D50(g->burst[i].t, 24, 1);
            alpha = (u32)(255.0f * (1.0f - f));
            if (g->burst[i].on == 2) {
                alpha = (u32)alpha >> 1;
            }
            pk.v[0].c.r = 0xA4;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0xFF;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            for (n = 0; n < 4; n++) {
                func_0020EB40(m);
                func_0020C940(m2, 0, 0, &g->jp[n]);
                func_0020BC00(m, m2);
                for (k = 0; k < 6; k++) {
                    func_00100E40(&m4, &g->burst[i].v[n][k]);
                    func_00100E00(&m4, (i << 16) / 24 + (k << 16) / 6, 2);
                    cn[0].x = 0.0f;
                    cn[0].y = 1.5f;
                    cn[0].z = 0.0f;
                    cn[0].w = 1.0f;
                    cn[1].x = 0.0f;
                    cn[1].y = -1.0f * cn[0].y;
                    cn[1].z = 0.0f;
                    cn[1].w = 1.0f;
                    func_001878E0(&cn[0], &m4, &cn[0]);
                    func_001878E0(&cn[1], &m4, &cn[1]);
                    func_00187B00(&out[0], &cn[0], &g->burst[i].v[n][k]);
                    func_00187B00(&out[1], &cn[1], (void *)&g->burst[i].v[n][k]);
                    func_00187B48(&v, &g->burst[i].v[n][k], -2.0f * f);
                    func_00187B00(&out[2], (void *)&out[0], (void *)&v);
                    func_00187B00(&out[3], &out[1], (void *)&v);
                    pk.v[0].s = 0.0f;
                    pk.v[0].t = 0.0f;
                    pk.v[1].s = 1.0f;
                    pk.v[1].t = 0.0f;
                    pk.v[2].s = 0.0f;
                    pk.v[2].t = 1.0f;
                    pk.v[3].s = 1.0f;
                    pk.v[3].t = 1.0f;
                    if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
            g->burst[i].t++;
            if (g->burst[i].t > 24) {
                g->burst[i].on = 0;
            }
        }
    }
    if (g->t == 0x2D) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tex_b575_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Tex_b575_01E00080 *)(s32)&pk)->size = 0xC;
        ((Tex_b575_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Tex_b575_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 5);
        n = 0x91 - g->t2;
        if (n > 32) {
            n = 32;
        }
        alpha = n * 0xFF >> 5;
        pk.v[0].c.r = 0xA4;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        k = g->t2;
        if (k > 32) {
            k = 32;
        }
        f = k / 32.0f;
        for (i = 0; i < 4; i++) {
            h = f * (3.0f * (1.0f - 0.1f * ((g->t2 + i) % 2)));
            cn[0].x = -h;
            cn[0].y = -h;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = h;
            cn[1].y = h;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m3, &cn[0]);
            func_001878E0(&cn[1], &m3, &cn[1]);
            v = g->pos;
            v.y -= 5.0f * g->h / 2.0f;
            func_00187B18(&v, &v, &g->jp[i]);
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->jp[i]);
            func_0020BC00(m, m2);
            l = 0;
            for (k = 0; k < 16; k++) {
                func_00187B48(&d, &v, f * k / 16.0f);
                func_00187B00(&out[0], &cn[0], &d);
                func_00187B00(&out[1], &cn[1], (void *)&d);
                func_00187B48(&d, &v, f * (k + 1) / 16.0f);
                func_00187B00(&out[2], (void *)&cn[0], (void *)&d);
                func_00187B00(&out[3], &cn[1], (void *)&d);
                pk.v[0].s = 0.0f;
                pk.v[0].t = 0.0f;
                pk.v[1].s = 1.0f;
                pk.v[1].t = 0.0f;
                pk.v[2].s = 0.0f;
                pk.v[2].t = 1.0f;
                pk.v[3].s = 1.0f;
                pk.v[3].t = 1.0f;
                if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                    d.x = (f32)(*(u16 *)(s32)&pk.v[0].p.x + *(u16 *)(s32)&pk.v[1].p.x) / 2.0f;
                    d.y = (f32)(*(u16 *)(s32)&pk.v[0].p.y + *(u16 *)(s32)&pk.v[1].p.y) / 2.0f;
                    d.z = 0.0f;
                    c.x = (f32)(*(u16 *)(s32)&pk.v[2].p.x + *(u16 *)(s32)&pk.v[3].p.x) / 2.0f;
                    d.w = 1.0f;
                    c.y = (f32)(*(u16 *)(s32)&pk.v[2].p.y + *(u16 *)(s32)&pk.v[3].p.y) / 2.0f;
                    c.z = 0.0f;
                    c.w = 1.0f;
                    a = (s32)(65536.0f * (func_001A6C18(d.y - c.y, d.x - c.x) / 6.2831855f));
                    x = ((k % 8 << 16) >> 3) + (g->t * -0x176F + i * 0x83F);
                    x &= 0xFFFF;
                    z = *(u16 *)(s32)&pk.v[0].p.x;
                    w = func_001A6C48(d.x - (f32)z, 2.0f);
                    z = *(u16 *)(s32)&pk.v[0].p.y;
                    w = func_001A6C60(w + func_001A6C48(d.y - (f32)z, 2.0f));
                    w = 0.9f * w + 0.1f * w * func_0020B550(x);
                    x = (((k + 1) % 8 << 16) >> 3) + (g->t * -0x176F + i * 0x83F);
                    x &= 0xFFFF;
                    z = *(u16 *)(s32)&pk.v[2].p.x;
                    p = func_001A6C48(c.x - (f32)z, 2.0f);
                    z = *(u16 *)(s32)&pk.v[2].p.y;
                    p = func_001A6C60(p + func_001A6C48(c.y - (f32)z, 2.0f));
                    p = 0.9f * p + 0.1f * p * func_0020B550(x);
                    if (l == 0) {
                        e[0].x = d.x - w * func_0020B550(a);
                        e[0].y = d.y + w * func_0020B480(a);
                        e[0].z = 0.0f;
                        e[0].w = 0.0f;
                        e[1].x = d.x + w * func_0020B550(a);
                        e[1].y = d.y - w * func_0020B480(a);
                        e[1].z = 0.0f;
                        e[1].w = 0.0f;
                    } else {
                        e[0] = e[2];
                        e[1] = e[3];
                    }
                    e[2].x = c.x - p * func_0020B550(a);
                    e[2].y = c.y + p * func_0020B480(a);
                    e[2].z = 0.0f;
                    e[2].w = 0.0f;
                    e[3].x = c.x + p * func_0020B550(a);
                    e[3].y = c.y - p * func_0020B480(a);
                    e[3].z = 0.0f;
                    e[3].w = 0.0f;
                    *(u16 *)(s32)&pk.v[0].p.x = (u32)e[0].x;
                    *(u16 *)(s32)&pk.v[0].p.y = (u32)e[0].y;
                    *(u16 *)(s32)&pk.v[1].p.x = (u32)e[1].x;
                    *(u16 *)(s32)&pk.v[1].p.y = (u32)e[1].y;
                    *(u16 *)(s32)&pk.v[2].p.x = (u32)e[2].x;
                    *(u16 *)(s32)&pk.v[2].p.y = (u32)e[2].y;
                    *(u16 *)(s32)&pk.v[3].p.x = (u32)e[3].x;
                    *(u16 *)(s32)&pk.v[3].p.y = (u32)e[3].y;
                    func_002075F0(&pk, ot, (u32)depth);
                    l = 1;
                } else {
                    l = 0;
                }
            }
        }
        g->t2++;
        if (g->t2 > 0x91) {
            g->on2 = 0;
        }
    }
    if (g->t == 0x9E) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b575_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b575_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b575_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b575_01E00080 *)(s32)&tri)->pad4 = 0;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        func_002087A0(&tri, 1);
        ((Edge_b575_01E00080 *)(s32)&edge)->flags = 0x13;
        ((Edge_b575_01E00080 *)(s32)&edge)->size = 6;
        ((Edge_b575_01E00080 *)(s32)&edge)->regs = 0x414141;
        ((Edge_b575_01E00080 *)(s32)&edge)->pad4 = 0;
        func_002086D0(&edge, func_00208D00(1));
        n = g->t3;
        if (n > 32) {
            n = 32;
        }
        a = n * 16 >> 5;
        if (a > 16) {
            a = 16;
        }
        y = 0x96 - g->t3;
        if (y > 32) {
            y = 32;
        }
        w = 3.0f * g->h * func_00100D50(32 - y, 32, 1);
        alpha = (u32)(120.0f * func_00100FF0(32 - y, 32.0f, 16.0f));
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = 0;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0x80;
        tri.v[1].c.g = 0x80;
        tri.v[1].c.b = 0x80;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        alpha = (u32)(56.0f * func_00100FF0(32 - y, 32.0f, 16.0f));
        edge.v[0].c.r = 0;
        edge.v[0].c.g = 0;
        edge.v[0].c.b = 0;
        edge.v[0].c.a = 0;
        edge.v[0].c.q = 1.0f;
        edge.v[1].c.r = 0xFF;
        edge.v[1].c.g = 0xFF;
        edge.v[1].c.b = 0xFF;
        edge.v[1].c.a = alpha;
        edge.v[1].c.q = 1.0f;
        edge.v[2].c = edge.v[1].c;
        for (i = 0; i < a; i++) {
            for (j = 0; j < 16; j++) {
                ang[0] = ((32 - y) * g->spin[i][j].a) & 0xFFFF;
                ang[1] = ((32 - y) * g->spin[i][j].b) & 0xFFFF;
                ang[2] = ((32 - y) * g->spin[i][j].c) & 0xFFFF;
                ang[3] = 1;
                for (k = 0; k < 2; k++) {
                    func_00187B18(&out[0], &g->nrm[i][j][k], &g->nrm[i][j][k]);
                    func_00187B18(&out[1], &g->grid[i][j], &g->nrm[i][j][k]);
                    func_00187B18(&out[2], &g->grid[i + !k][j + k], (void *)&g->nrm[i][j][k]);
                    func_00187B18(&out[3], &g->grid[i + 1][j + 1], (void *)&g->nrm[i][j][k]);
                    func_00205E70(3, &out[1], &c);
                    func_00187B48(&d, &c, w * (k * 2 - 1));
                    func_00187B00(&d, &d, &g->pos);
                    func_00187B00(&d, &d, &g->nrm[i][j][k]);
                    func_0020EB40(m);
                    func_0020C940(m2, 0, ang, &d);
                    func_0020BC00(m, m2);
                    n = k * 3;
                    tri.v[0].s = g->uv[i][j].n[k].x;
                    tri.v[0].t = g->uv[i][j].n[k].y;
                    tri.v[1].s = g->uv[i][j].v[n].x;
                    tri.v[1].t = g->uv[i][j].v[n].y;
                    tri.v[2].s = g->uv[i][j].v[n + 1].x;
                    tri.v[2].t = g->uv[i][j].v[n + 1].y;
                    if (func_00100B00(&out[0], &out[1], &out[2], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                    tri.v[0].s = g->uv[i][j].n[k].x;
                    tri.v[0].t = g->uv[i][j].n[k].y;
                    tri.v[1].s = g->uv[i][j].v[n + 1].x;
                    tri.v[1].t = g->uv[i][j].v[n + 1].y;
                    tri.v[2].s = g->uv[i][j].v[n + 2].x;
                    tri.v[2].t = g->uv[i][j].v[n + 2].y;
                    if (func_00100B00(&out[0], &out[2], &out[3], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                    tri.v[0].s = g->uv[i][j].n[k].x;
                    tri.v[0].t = g->uv[i][j].n[k].y;
                    tri.v[1].s = g->uv[i][j].v[n + 2].x;
                    tri.v[1].t = g->uv[i][j].v[n + 2].y;
                    tri.v[2].s = g->uv[i][j].v[n].x;
                    tri.v[2].t = g->uv[i][j].v[n].y;
                    if (func_00100B00(&out[0], &out[3], &out[1], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                }
            }
        }
        g->t3++;
        if (g->t3 > 0x96) {
            g->on3 = 0;
        }
    }
    if (g->t > 0x4D && g->t < 0xBE) {
        n = g->t % 32;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (k = 0; k < 8; k++) {
            q = (g->t + k) % 32;
            g->ring[n].v[k].x = 0.1f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][0];
            g->ring[n].v[k].y = 3.0f * g->h + 0.1f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][1];
            g->ring[n].v[k].z = 0.1f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][q][2];
            g->ring[n].v[k].w = 1.0f;
        }
    }
    ((Spr_b575_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b575_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b575_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b575_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b575_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    v = g->pos;
    v.y -= 5.0f * g->h / 2.0f;
    func_0020EB40(m);
    func_0020C940(m2, 0, 0, &v);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->ring[i].on != 0) {
            s = 0.5f * (0.5f * g->h);
            r = s + s * g->ring[i].t / 32.0f;
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m3, &cn[0]);
            func_001878E0(&cn[1], &m3, &cn[1]);
            alpha = (u32)(128.0f * func_00100FF0(g->ring[i].t, 32.0f, 10.666667f));
            spr.c.r = 0x80;
            spr.c.g = 0x80;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            s = g->ring[i].t / 32.0f;
            for (y = 0; y < 8; y++) {
                func_00187B48(&v, &g->ring[i].v[y], s);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                ((Uv_b575_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->ring[i].c[y]][0];
                ((Uv_b575_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->ring[i].c[y]][2];
                ((Uv_b575_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->ring[i].c[y]][1];
                ((Uv_b575_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->ring[i].c[y]][3];
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->ring[i].t++;
            if (g->ring[i].t > 32) {
                g->ring[i].on = 0;
            }
        }
    }
    if (g->t == 0x115) {
        g->on4 = 1;
        g->t4 = 0;
        for (j = 0; j < 64; j++) {
            n = (func_0019A5C8() >> 23) % 32;
            g->dv[j].x = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][0];
            g->dv[j].y = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][1];
            g->dv[j].z = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][2];
            g->dv[j].w = 1.0f;
        }
    }
    ((Spr_b575_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b575_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b575_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b575_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b575_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020C940(m2, 0, 0, &g->pos);
    func_0020BC00(m, m2);
    if (g->on4 == 1) {
        s = 0.5f * g->h;
        r = s + s * g->t4 / 32.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        alpha = (u32)(128.0f * func_00100FF0(g->t4, 32.0f, 16.0f));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.5f + 0.5f * g->t4 / 32.0f;
        for (q = 0; q < 64; q++) {
            func_00187B48(&v, &g->dv[q], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b575_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->c4[q]][0];
            ((Uv_b575_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->c4[q]][2];
            ((Uv_b575_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->c4[q]][1];
            ((Uv_b575_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->c4[q]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t4++;
        if (g->t4 > 32) {
            g->on4 = 0;
        }
    }
    if (g->t == 0xB4) {
        func_001F6730(g->unitB, 0);
    }
    if (g->t == 0x114) {
        func_001F6730(g->unitB, 1);
    }
    if (g->t == 0x94) {
        ret = 1;
    } else {
        if (g->t > 0x9E && g->t < 0xBE) {
            ret = 6;
        }
        if (g->t == 0xBE) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x135) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
