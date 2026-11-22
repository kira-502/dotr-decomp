#include "common.h"

/* shape b717:01E00080 (b717), 3760 insns, 1 copy (-O3,p): b717 scene manager, b739:01E00080's relative: joint-
   triggered blade quads and sparks, three triple bursts, a blur fan, a flash fan, a four-quad ring and smoke puffs */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b717_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b717_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b717_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b717_01E00080 c;
    Uv_b717_01E00080 uv0;
    Xyz_b717_01E00080 p0;
    Uv_b717_01E00080 uv1;
    Xyz_b717_01E00080 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b717_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b717_01E00080 c;
        Uv_b717_01E00080 uv;
        Xyz_b717_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b717_01E00080;

typedef struct {
    Rgbaq_b717_01E00080 c;
    f32 s, t;
    Xyz_b717_01E00080 p;
} Tv_b717_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b717_01E00080 v[4];
    u8 tail[0x20];
} Quad_b717_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b717_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b717_01E00080 c;
    struct {
        Uv_b717_01E00080 uv;
        Xyz_b717_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Fan_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f w[128];
    u8 c2[64];
    Vec4f v3[64];
} Burst_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[1];
    u8 padC[4];
    Vec4f pos[1];
} Blade_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Spark_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Flash_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 s;
    u8 padC[4];
    Vec4f pos;
} Ring_b717_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][4];
    u8 padC[4];
    Vec4f pos[1];
    Vec4f v[1][4];
} Puff_b717_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    Vec4f pos;
    Vec4f pos2;
    Vec4f scrA;
    Vec4f scrB;
    s32 jn[3];
    u8 pad7C[4];
    Vec4f jp[3];
    s32 nb;
    u8 padB4[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Blade_b717_01E00080 blade[3];
    s32 ns;
    u8 pad21A4[0xC];
    Spark_b717_01E00080 spark[3];
    s32 cur;
    u8 pad2874[0xC];
    Burst_b717_01E00080 burst[3];
    u8 on3;
    u8 pad5B21[3];
    s32 t3;
    Flash_b717_01E00080 flash[12];
    u8 pad5B88[8];
    Vec4f quad[4][4];
    Ring_b717_01E00080 ring[1][1];
    Puff_b717_01E00080 puff[24];
} Scene_b717_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b717(s32 arg0, s32 code) {
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
    extern void func_00187B18(void *, void *, void *);
    extern void func_00100E40(void *, void *);
    extern f32 func_00100FF0(f32, f32, f32);
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
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F63F0(s32, s32, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern f32 func_00205DF0(void *, f32);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    Scene_b717_01E00080 *g = (Scene_b717_01E00080 *)arg0;
    s32 l;
    u8 a2;
    s32 buf;
    u8 on;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 c;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    u8 fade;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 u0;
    f32 w1;
    f32 w0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b717_01E00080 m4;
    Vec4f v;
    Spr_b717_01E00080 spr __attribute__((aligned(8)));
    Fan_b717_01E00080 fan __attribute__((aligned(8)));
    Tri_b717_01E00080 tri __attribute__((aligned(8)));
    Quad_b717_01E00080 pk __attribute__((aligned(8)));
    Xyz_b717_01E00080 xyz;
    f32 depth;
    u8 col[4] __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x65B0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x28, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x2F, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x19, 0);
        g->nb = 0;
        for (n = 0; n < 8; n++) {
            h = 180.0f * (n + 1) / 8.0f;
            f = -1.0f * (180.0f * n / 7.0f * (f32)g->obj);
            s = 5.0f * (8 - (n + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                ang = ((i << 16) >> 4) + ((n << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[n][i][0].x = -2.0f;
                g->grid[n][i][0].y = 0.0f;
                g->grid[n][i][0].z = 0.0f;
                g->grid[n][i][0].w = 1.0f;
                g->grid[n][i][1].x = 2.0f;
                g->grid[n][i][1].y = 0.0f;
                g->grid[n][i][1].z = 0.0f;
                g->grid[n][i][1].w = 1.0f;
                g->grid[n][i][2].x = -2.0f;
                g->grid[n][i][2].y = 0.0f;
                g->grid[n][i][2].z = h;
                g->grid[n][i][2].w = 1.0f;
                g->grid[n][i][3].x = 2.0f;
                g->grid[n][i][3].y = 0.0f;
                g->grid[n][i][3].z = h;
                g->grid[n][i][3].w = 1.0f;
                for (j = 0; j < 4; j++) {
                    func_001878E0(&g->grid[n][i][j], &m4, &g->grid[n][i][j]);
                }
                g->gc[n][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (j = 0; j < 3; j++) {
            g->blade[j].on = 0;
        }
        g->ns = 0;
        for (n = 0; n < 3; n++) {
            g->spark[n].on = 0;
        }
        g->cur = 0;
        for (i = 0; i < 3; i++) {
            g->burst[i].on = 0;
        }
        k = 0;
        g->on3 = k;
        for (i = 0; i < 12; i++) {
            g->flash[i].on = 0;
        }
        r = 0.4f;
        for (n = 0; n < 4; n++) {
            h = 10.0f * (1.0f - 0.4f * (n % 2));
            cn[0].x = -r;
            cn[0].y = -h;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = -h;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = -r;
            cn[2].y = h;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = r;
            cn[3].y = h;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (n << 15) >> 2, 2);
            for (i = 0; i < 4; i++) {
                func_001878E0(&g->quad[n][i], &m4, &cn[i]);
            }
        }
        for (n = 0; n < 1; n++) {
            for (i = 0; i < 1; i++) {
                g->ring[n][i].on = 0;
            }
        }
        for (q = 0; q < 24; q++) {
            g->puff[q].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    func_001F53C0(1, g->unitB, &g->pos2);
    for (k = 0; k < 3; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
    g->scrA.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scrA.y = (s32)(xyz.y >> 4) - 0x720;
    g->scrA.z = func_0017B340(xyz.z);
    g->scrA.w = 1.0f;
    if (g->scrA.x < 0.0f) {
        g->scrA.x = 0.0f;
    }
    if (g->scrA.x > 640.0f) {
        g->scrA.x = 640.0f;
    }
    if (g->scrA.y < 0.0f) {
        g->scrA.y = 0.0f;
    }
    if (g->scrA.y > 448.0f) {
        g->scrA.y = 448.0f;
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
    g->scrB.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scrB.y = (s32)(xyz.y >> 4) - 0x720;
    g->scrB.z = func_0017B340(xyz.z);
    g->scrB.w = 1.0f;
    if (g->scrB.x < 0.0f) {
        g->scrB.x = 0.0f;
    }
    if (g->scrB.x > 640.0f) {
        g->scrB.x = 640.0f;
    }
    if (g->scrB.y < 0.0f) {
        g->scrB.y = 0.0f;
    }
    if (g->scrB.y > 448.0f) {
        g->scrB.y = 448.0f;
    }

    n = -1;
    switch (g->t) {
        case 0xF4:
        case 0x11C:
        case 0x14E:
            n = 1;
            break;
    }
    if (n == 1) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b717_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b717_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b717_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b717_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b717_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x30 - g->t3) * 0x40 / 48;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (j = 0; j < 8; j++) {
            r = 1.0f + 0.15f * (8 - j) / 8.0f;
            for (q = 0; q < 8; q++) {
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
                ((Uv_b717_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b717_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[q].x;
                y = (s32)D_28B960[q].y;
                ((Uv_b717_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b717_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[q + 1].x;
                y = (s32)D_28B960[q + 1].y;
                ((Uv_b717_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b717_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[q], (void *)&g->scrB);
                func_00187B18(&out[1], &D_28B960[q + 1], &g->scrB);
                func_00187B48(&out[0], &out[0], r);
                func_00187B48(&out[1], &out[1], r);
                func_00187B00(&out[0], &out[0], &g->scrB);
                func_00187B00(&out[1], &out[1], &g->scrB);
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
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
        g->t3++;
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    n = -1;
    switch (g->t) {
        case 0x5D:
            n = 0;
            break;
        case 0x8E:
            n = 1;
            break;
        case 0xC1:
            n = 2;
            break;
    }
    if (n >= 0) {
        i = g->nb;
        (void)i;
        g->blade[i].on = 1;
        g->blade[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (j = 0; j < 1; j++) {
            g->blade[i].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade[i].pos[j] = g->jp[n];
            g->spark[c].pos[j] = g->jp[n];
            for (k = 0; k < 32; k++) {
                g->spark[c].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[j][k], 0.8f);
            }
        }
        g->nb++;
        if (g->nb >= 3) {
            g->nb = 0;
        }
        g->ns++;
        if (g->ns >= 3) {
            g->ns = 0;
        }
    }

    ((Quad_b717_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b717_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b717_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b717_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (j = 0; j < 3; j++) {
        if (g->blade[j].on == 0) {
            continue;
        }
        fade = (10 - g->blade[j].t) * 0x40 / 10;
        pk.v[0].c.r = 0x3C;
        pk.v[0].c.g = 0x64;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = fade;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade[j].t / 10.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 1; l++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->jp[j]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->blade[j].rot[l], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (k = 0; k < 8; k++) {
                for (i = 0; i < 16; i++) {
                    n = g->gc[k][i];
                    x = n % 4 * 32;
                    y = (n >> 2) * 32;
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
                    if (func_002058D0(g->grid[k][i], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 100.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade[j].t, 10, 1));
        (void)alpha;
        spr.c.r = 0xD7;
        spr.c.g = 0x64;
        spr.c.b = 0x3C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (l = 0; l < 1; l++) {
            v = g->blade[j].pos[l];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade[j].t++;
        if (g->blade[j].t > 10) {
            g->blade[j].on = 0;
        }
    }

    ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 3; j++) {
        if (g->spark[j].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->spark[j].t / 64.0f);
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
        s = func_00100D50(g->spark[j].t, 64, 1);
        for (c = 0; c < 1; c++) {
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->spark[j].v[c][k], s);
                func_00187B00(&v, &v, &g->spark[j].pos[c]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[j].c[c][k] % 4 * 32;
                y = (g->spark[j].c[c][k] >> 2) * 32;
                ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[j].t++;
        if (g->spark[j].t > 64) {
            g->spark[j].on = 0;
        }
    }

    n = -1;
    switch (g->t) {
        case 0xF4:
        case 0x11C:
        case 0x14E:
            n = 1;
            break;
    }
    if (n == 1) {
        g->burst[g->cur].on = 1;
        g->burst[g->cur].t = 1;
        g->burst[g->cur].pos.x = 0.0f;
        g->burst[g->cur].pos.y = 0.0f;
        g->burst[g->cur].pos.z = 0.0f;
        g->burst[g->cur].pos.w = 1.0f;
        func_00187B00(&g->burst[g->cur].pos, &g->burst[g->cur].pos, &g->tgt);
        for (k = 0; k < 64; k++) {
            g->burst[g->cur].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->burst[g->cur].v[k], 2.5f);
        }
        for (n = 0; n < 128; n++) {
            func_00101080(&g->burst[g->cur].w[n], 3.0f);
        }
        for (i = 0; i < 64; i++) {
            g->burst[g->cur].c2[i] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->burst[g->cur].v3[i], 2.5f);
        }
        g->cur++;
        if (g->cur >= 3) {
            g->cur = 0;
        }
    }

    for (j = 0; j < 3; j++) {
        if (g->burst[j].on == 0) {
            continue;
        }
        ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
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
        alpha = (0x30 - g->burst[j].t) * 0xC8 / 48;
        spr.c.r = 0x32;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[j].t, 0x30, 1);
        for (i = 0; i < 64; i++) {
            func_00187B48(&v, &g->burst[j].v3[i], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c2[i] % 4 * 32;
            y = (g->burst[j].c2[i] >> 2) * 32;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 13.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
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
        fade = (0x30 - g->burst[j].t) * 0xFF / 48;
        a2 = (0x30 - g->burst[j].t) * 0x80 / 48;
        for (q = 0; q < 64; q++) {
            s = func_00100D50(g->burst[j].t, 0x30, 1);
            if (q % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0x80;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x1E;
                spr.c.g = 0x60;
                spr.c.b = 0xFF;
                spr.c.a = fade;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[j].v[q], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c[q] % 4 * 32;
            y = (g->burst[j].c[q] >> 2) * 32;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[j].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[j].t, 0x30, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((f32)(0x30 - g->burst[j].t) / 48.0f));
        spr.c.r = 0x3A;
        spr.c.g = 0x5E;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 130.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.0f;
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
        h = func_00100D50(g->burst[j].t, 0x30, 1);
        for (k = 0; k < 128; k++) {
            for (i = 0; i < 6; i++) {
                spr.c.r = 0x80;
                spr.c.g = 0xF0;
                spr.c.b = 0xFF;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[j].w[k], h + 0.007f * i);
                func_00187B00(&v, &v, &g->burst[j].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[j].t++;
        if (g->burst[j].t > 0x30) {
            g->burst[j].on = 0;
        }
    }

    if (g->t > 0x14 && g->t < 0x46) {
        n = g->t % 12;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
    }
    ((Tri_b717_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b717_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b717_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b717_01E00080 *)(s32)&tri)->pad4 = 0;
    ((Tri_b717_01E00080 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&tri, func_00208D00(1));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t - 0x14, 0, 16) * (f32)func_00101050(0x46 - g->t, 0, 16) / 256.0f;
    on = 0;
    for (j = 0; j < 12; j++) {
        if (g->flash[j].on == 0) {
            continue;
        }
        if (on == 0) {
            on = 1;
            buf = func_00207F60();
            func_00208460();
            func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
            func_00208460();
        }
        alpha = (u32)(f * (128.0f * func_0020B550(((g->flash[j].t + 1) << 15) / 13)));
        tri.v[0].c.r = 0x94;
        tri.v[0].c.g = 0xC8;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(f * (0.0f * func_0020B550(((g->flash[j].t + 1) << 15) / 13)));
        tri.v[1].c.r = 0;
        tri.v[1].c.g = 0;
        tri.v[1].c.b = 0xFF;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 1.0f + (-0.2f + 0.4f * g->flash[j].t / 12.0f) + 0.2f / 12.0f;
        for (k = 0; k < 8; k++) {
            x = (s32)g->scrA.x;
            y = (s32)g->scrA.y;
            ((Uv_b717_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
            x = (s32)D_28B960[k].x;
            y = (s32)D_28B960[k].y;
            ((Uv_b717_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
            x = (s32)D_28B960[k + 1].x;
            y = (s32)D_28B960[k + 1].y;
            ((Uv_b717_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
            ((Uv_b717_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
            func_00187B18((void *)&out[0], &D_28B960[k], (void *)&g->scrA);
            func_00187B18(&out[1], &D_28B960[k + 1], (void *)&g->scrA);
            func_00187B48(&out[0], &out[0], r);
            func_00187B48(&out[1], &out[1], r);
            func_00187B00(&out[0], &out[0], &g->scrA);
            func_00187B00(&out[1], &out[1], &g->scrA);
            x = (s32)g->scrA.x;
            y = (s32)g->scrA.y;
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
        g->flash[j].t++;
        if (g->flash[j].t > 12) {
            g->flash[j].on = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    n = -1;
    switch (g->t) {
        case 2:
            v = g->jp[2];
            n = 0;
            break;
    }
    if (n >= 0) {
        g->ring[n][0].on = 1;
        g->ring[n][0].t = 0;
        g->ring[n][0].s = 1.0f;
        g->ring[n][0].pos = v;
    }

    ((Fan_b717_01E00080 *)(s32)&fan)->flags = 0x24;
    ((Fan_b717_01E00080 *)(s32)&fan)->size = 9;
    ((Fan_b717_01E00080 *)(s32)&fan)->regs = ((u64)4 << 32) | 0x24242421;
    ((Fan_b717_01E00080 *)(s32)&fan)->pad4 = 0;
    ((Fan_b717_01E00080 *)(s32)&fan)->flags |= 0x800;
    func_002086D0(&fan, func_00208D00(1));
    func_00208700(&fan, g->tex[1], 1);
    func_00208CB0(&fan, 5);
    ((Uv_b717_01E00080 *)(s32)&fan.v[0].uv)->u = 0;
    ((Uv_b717_01E00080 *)(s32)&fan.v[0].uv)->v = 0x200;
    ((Uv_b717_01E00080 *)(s32)&fan.v[1].uv)->u = 0x200;
    ((Uv_b717_01E00080 *)(s32)&fan.v[1].uv)->v = 0x200;
    ((Uv_b717_01E00080 *)(s32)&fan.v[2].uv)->u = 0;
    ((Uv_b717_01E00080 *)(s32)&fan.v[2].uv)->v = 0x400;
    ((Uv_b717_01E00080 *)(s32)&fan.v[3].uv)->u = 0x200;
    ((Uv_b717_01E00080 *)(s32)&fan.v[3].uv)->v = 0x400;
    ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = 0x600;
    ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = 0;
    ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 1; j++) {
        for (k = 0; k < 1; k++) {
            if (g->ring[j][k].on == 0) {
                continue;
            }
            alpha = (u32)(255.0f * (1.0f - func_00100D50(g->ring[j][k].t, 16, 1)));
            fan.c.r = 0x86;
            fan.c.g = 0x68;
            fan.c.b = 0xFF;
            fan.c.a = alpha;
            fan.c.q = 1.0f;
            s = g->ring[j][k].s;
            for (n = 0; n < 4; n++) {
                for (l = 0; l < 4; l++) {
                    func_00187B48(&cn[l], &g->quad[n][l], s);
                    func_001878E0(&cn[l], m3, &cn[l]);
                    func_00187B00(&out[l], &cn[l], &g->jp[2]);
                }
                if (func_00205630(out, D_0030FF00, m, &fan, &depth) == 1) {
                    fan.v[0].p.z = 0xFFFFF8;
                    fan.v[1].p.z = fan.v[0].p.z;
                    fan.v[2].p.z = fan.v[0].p.z;
                    fan.v[3].p.z = fan.v[0].p.z;
                    func_002075F0(&fan, ot, 0);
                }
            }
            r = 3.0f * g->ring[j][k].s;
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
            alpha = (u32)(255.0f * func_00100FF0((f32)g->ring[j][k].t, 16.0f, 10.0f));
            spr.c.r = 0x86;
            spr.c.g = 0x68;
            spr.c.b = 0xFF;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            v = g->jp[2];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
            g->ring[j][k].t++;
            if (g->ring[j][k].t > 16) {
                g->ring[j][k].on = 0;
            }
        }
    }

    if (g->t > 0x14E && g->t < 0x1B2) {
        n = g->t % 24;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->puff[n].pos[j] = g->pos2;
            for (i = 0; i < 4; i++) {
                g->puff[n].c[j][i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[j][i], 1.5f);
            }
        }
    }

    ((Spr_b717_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b717_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b717_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b717_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b717_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 24; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(0.0f * func_0020B550((g->puff[i].t << 15) / 24));
        spr.c.r = 0xC;
        spr.c.g = 8;
        spr.c.b = 8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.5f + 0.5f * g->puff[i].t / 24.0f);
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
        h = 0.4f + 0.6f * g->puff[i].t / 24.0f;
        f = -15.0f + 40.0f * g->puff[i].t / 24.0f;
        for (n = 0; n < 1; n++) {
            for (k = 0; k < 4; k++) {
                func_00187B48(&v, &g->puff[i].v[n][k], h);
                func_00187B00(&v, &v, &g->puff[i].pos[n]);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->puff[i].c[n][k] % 4 * 32;
                y = (g->puff[i].c[n][k] >> 2) * 32;
                ((Uv_b717_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b717_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 24) {
            g->puff[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x19E - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0xEA) {
        ret = 1;
    } else {
        if (g->t > 0xF4 && g->t < 0x17E) {
            ret = 6;
        }
        if (g->t == 0x17E) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x1CA) {
        ret = 8;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b717", func_01E03B84_b717);
