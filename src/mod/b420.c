#include "common.h"

/* shape b420:01E00080 (b420), 4559 insns, 1 copy (-O3,p): b420 scene manager, b766:01E00080's ring burst and blade
   volley with b511:01E00080's second volley and closing burst: seven joints, a blur fan, thirty-two tumbling shards
   */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b420_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b420_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b420_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b420_01E00080 c;
    Uv_b420_01E00080 uv0;
    Xyz_b420_01E00080 p0;
    Uv_b420_01E00080 uv1;
    Xyz_b420_01E00080 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b420_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b420_01E00080 c;
    struct {
        f32 s, t;
        Xyz_b420_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Tex_b420_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b420_01E00080 c;
        Uv_b420_01E00080 uv;
        Xyz_b420_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b420_01E00080;

typedef struct {
    Rgbaq_b420_01E00080 c;
    f32 s, t;
    Xyz_b420_01E00080 p;
} Tv_b420_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b420_01E00080 v[4];
    u8 tail[0x20];
} Quad_b420_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b420_01E00080;

typedef struct {
    f32 m[4][4];
} __attribute__((aligned(16))) Mq_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f p;
    Vec4f v[32];
    Vec4f w[32];
} Ring_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[1];
    u8 padC[4];
    Vec4f pos[1];
    Mtx_b420_01E00080 mat[1];
} Blade1_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][8];
    Vec4f pos[1];
    Vec4f v[1][8];
} Spark1_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot;
    u8 padC[4];
    Vec4f pos;
    Vec4f vel;
} Shard_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[1];
    u8 padC[4];
    Vec4f pos[1];
} Blade_b420_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Spark_b420_01E00080;

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
} Burst_b420_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr;
    s32 jn[7];
    u8 pad6C[4];
    Vec4f jp[7];
    Mtx_b420_01E00080 mtx;
    s32 nr;
    u8 pad124[0xC];
    Ring_b420_01E00080 ring[12];
    s32 nb1;
    u8 pad35B4[0xC];
    Vec4f grid1[8][16][4];
    u8 gc1[8][16];
    Blade1_b420_01E00080 blade1[3];
    s32 ns1;
    u8 pad5764[0xC];
    Spark1_b420_01E00080 spark1[16];
    s32 nq;
    u8 pad6174[0xC];
    Shard_b420_01E00080 shard[32];
    s32 nb;
    u8 pad6784[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Blade_b420_01E00080 blade[4];
    s32 ns;
    u8 pad8894[0xC];
    Spark_b420_01E00080 spark[4];
    s32 cur;
    u8 pad91A4[0xC];
    Burst_b420_01E00080 burst[4];
    u8 on3;
    u8 padD531[3];
    s32 t3;
    u8 padD538[8];
} Scene_b420_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b420(s32 arg0, s32 code) {
    Scene_b420_01E00080 *g = (Scene_b420_01E00080 *)arg0;
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
    extern void func_001F6D00(s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_001A6C48(f32, f32);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 p;
    s32 l;
    u8 a2;
    s32 buf;
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
    s32 ca;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 u0;
    f32 w1;
    f32 w0;
    f32 u1;
    f32 u2;
    f32 w3;
    f32 w2;
    f32 u3;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mq_b420_01E00080 m4;
    Vec4f v;
    Spr_b420_01E00080 spr __attribute__((aligned(8)));
    Tex_b420_01E00080 tx __attribute__((aligned(8)));
    Tri_b420_01E00080 tri __attribute__((aligned(8)));
    Quad_b420_01E00080 pk __attribute__((aligned(8)));
    Xyz_b420_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD540);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x1C, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x23, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x22, 0);
        g->jn[3] = func_001F5560(g->unitA, 9, 0);
        g->jn[4] = func_001F5560(g->unitA, 0xA, 0);
        g->jn[5] = func_001F5560(g->unitA, 0xB, 0);
        g->jn[6] = func_001F5560(g->unitA, 0xC, 0);
        g->nr = 0;
        for (i = 0; i < 12; i++) {
            g->ring[i].on = 0;
        }
        g->nb1 = 0;
        for (i = 0; i < 8; i++) {
            h = -30.0f * (i + 1) / 8.0f;
            f = -30.0f * i / 7.0f;
            s = 12.5f * (8 - (i + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                ang = ((j << 16) >> 4) + ((i << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid1[i][j][0].x = -2.5f;
                g->grid1[i][j][0].y = 0.0f;
                g->grid1[i][j][0].z = 0.0f;
                g->grid1[i][j][0].w = 1.0f;
                g->grid1[i][j][1].x = 2.5f;
                g->grid1[i][j][1].y = 0.0f;
                g->grid1[i][j][1].z = 0.0f;
                g->grid1[i][j][1].w = 1.0f;
                g->grid1[i][j][2].x = -2.5f;
                g->grid1[i][j][2].y = 0.0f;
                g->grid1[i][j][2].z = h;
                g->grid1[i][j][2].w = 1.0f;
                g->grid1[i][j][3].x = 2.5f;
                g->grid1[i][j][3].y = 0.0f;
                g->grid1[i][j][3].z = h;
                g->grid1[i][j][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid1[i][j][k], &m4, &g->grid1[i][j][k]);
                }
                g->gc1[i][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 3; i++) {
            g->blade1[i].on = 0;
        }
        g->ns1 = 0;
        for (i = 0; i < 16; i++) {
            g->spark1[i].on = 0;
        }
        g->nq = 0;
        for (i = 0; i < 32; i++) {
            g->shard[i].on = 0;
        }
        g->nb = 0;
        for (q = 0; q < 8; q++) {
            h = -240.0f * (q + 1) / 8.0f;
            f = -1.0f * (-240.0f * q / 7.0f * (f32)g->obj);
            s = 6.0f * (8 - (q + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                ang = ((i << 16) >> 4) + ((q << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[q][i][0].x = -2.5f;
                g->grid[q][i][0].y = 0.0f;
                g->grid[q][i][0].z = 0.0f;
                g->grid[q][i][0].w = 1.0f;
                g->grid[q][i][1].x = 2.5f;
                g->grid[q][i][1].y = 0.0f;
                g->grid[q][i][1].z = 0.0f;
                g->grid[q][i][1].w = 1.0f;
                g->grid[q][i][2].x = -2.5f;
                g->grid[q][i][2].y = 0.0f;
                g->grid[q][i][2].z = h;
                g->grid[q][i][2].w = 1.0f;
                g->grid[q][i][3].x = 2.5f;
                g->grid[q][i][3].y = 0.0f;
                g->grid[q][i][3].z = h;
                g->grid[q][i][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[q][i][k], &m4, &g->grid[q][i][k]);
                }
                g->gc[q][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 4; i++) {
            g->blade[i].on = 0;
        }
        g->ns = 0;
        for (k = 0; k < 4; k++) {
            g->spark[k].on = 0;
        }
        g->cur = 0;
        for (i = 0; i < 4; i++) {
            g->burst[i].on = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (k = 0; k < 7; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    func_00187B18((void *)&v, &g->jp[1], &g->jp[0]);
    func_00100E40(&g->mtx, &v);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
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

    n = -1;
    switch (g->t) {
    case 0xEA:
    case 0xFB:
    case 0x10C:
    case 0x11D:
        n = 1;
    }
    if (n == 1) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b420_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b420_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b420_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b420_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b420_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x20 - g->t3) * 0x40 / 32;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (q = 0; q < 8; q++) {
            r = 1.0f + 0.15f * (8 - q) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b420_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b420_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b420_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b420_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b420_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b420_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
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
        g->t3++;
        if (g->t3 > 32) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x30 && g->t < 0x84) {
        g->ring[g->nr].on = 1;
        g->ring[g->nr].t = 1;
        func_00101080(&g->ring[g->nr].p, 1.0f);
        func_00187B00(&g->ring[g->nr].p, &g->ring[g->nr].p, &g->tgt);
        for (j = 0; j < 32; j++) {
            g->ring[g->nr].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring[g->nr].v[j], 0.5f);
        }
        for (j = 0; j < 32; j++) {
            func_00101080(&g->ring[g->nr].w[j], 1.75f);
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
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 6.0f * (0.8f + 0.2f * g->ring[i].t / 12.0f);
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
        ca = 0;
        alpha = (12 - g->ring[i].t) * 255 / 12;
        for (j = 0; j < 32; j++) {
            s = func_00100D50(g->ring[i].t, 12, 1);
            if (j % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = ca;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xFF;
                spr.c.g = 0x60;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->ring[i].v[j], s);
            func_00187B00(&v, &v, &g->ring[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->ring[i].c[j] % 4 * 32;
            y = (g->ring[i].c[j] >> 2) * 32;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        a2 = (u32)(255.0f * ((12 - g->ring[i].t) / 12.0f));
        spr.c.r = 0x40;
        spr.c.g = 0xFF;
        spr.c.b = 0x1C;
        spr.c.a = a2;
        spr.c.q = 1.0f;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        s = func_00100D50(g->ring[i].t, 12, 1);
        for (n = 0; n < 32; n++) {
            for (k = 0; k < 6; k++) {
                spr.c.r = 0xFF;
                spr.c.g = 0x5A;
                spr.c.b = 0x30;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->ring[i].w[n], s + 0.007f * k);
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

    if (g->t % 4 == 1 && g->t > 0x2C && g->t < 0x84) {
        n = g->nb1;
        (void)n;
        g->blade1[n].on = 1;
        g->blade1[n].t = 0;
        c = g->ns1;
        (void)c;
        g->spark1[c].on = 1;
        g->spark1[c].t = 0;
        for (j = 0; j < 1; j++) {
            g->blade1[n].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade1[n].pos[j] = g->jp[1];
            g->blade1[n].mat[j] = g->mtx;
        }
        for (i = 0; i < 1; i++) {
            g->spark1[c].pos[i] = g->jp[1];
            for (k = 0; k < 8; k++) {
                g->spark1[c].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark1[c].v[i][k], 0.5f);
            }
        }
        g->nb1++;
        if (g->nb1 >= 3) {
            g->nb1 = 0;
        }
        g->ns1++;
        if (g->ns1 >= 16) {
            g->ns1 = 0;
        }
        l = g->nq;
        (void)l;
        g->shard[l].on = 1;
        g->shard[l].t = 0;
        g->shard[l].pos = g->jp[2];
        g->shard[l].rot = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        func_00101080(&v, 0.5f);
        g->shard[l].vel.x = 30.0f * (f32)g->obj;
        g->shard[l].vel.y = 20.0f;
        g->shard[l].vel.z = 20.0f * (f32)g->obj;
        g->shard[l].vel.w = 1.0f;
        func_00187B00(&g->shard[l].vel, &g->shard[l].vel, &v);
        g->nq++;
        if (g->nq >= 32) {
            g->nq = 0;
        }
    }

    ((Quad_b420_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b420_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b420_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b420_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 3; i++) {
        if (g->blade1[i].on == 0) {
            continue;
        }
        alpha = (3 - g->blade1[i].t) * 0x56 / 3;
        pk.v[0].c.r = 0x54;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0x30;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade1[i].t / 3.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (p = 0; p < 1; p++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->blade1[i].mat[p], &g->blade1[i].pos[p]);
            func_00100E00(m2, g->blade1[i].rot[p], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (k = 0; k < 8; k++) {
                for (j = 0; j < 16; j++) {
                    x = g->gc1[k][j] % 4 * 32;
                    y = (g->gc1[k][j] >> 2) * 32;
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
                    if (func_002058D0(g->grid1[k][j], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade1[i].t, 3, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x56;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 1; j++) {
            v = g->blade1[i].pos[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = 0x600;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = 0;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = 0x800;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = 0x200;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade1[i].t++;
        if (g->blade1[i].t > 3) {
            g->blade1[i].on = 0;
        }
    }

    ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->spark1[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->spark1[i].t / 16.0f);
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
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark1[i].t, 16, 1);
        for (k = 0; k < 1; k++) {
            for (j = 0; j < 8; j++) {
                func_00187B48(&v, &g->spark1[i].v[k][j], s);
                func_00187B00(&v, &v, &g->spark1[i].pos[k]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark1[i].c[k][j] % 4 * 32;
                y = (g->spark1[i].c[k][j] >> 2) * 32;
                ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark1[i].t++;
        if (g->spark1[i].t > 16) {
            g->spark1[i].on = 0;
        }
    }

    ((Tex_b420_01E00080 *)(s32)&tx)->flags = 0x24;
    ((Tex_b420_01E00080 *)(s32)&tx)->size = 9;
    ((Tex_b420_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
    ((Tex_b420_01E00080 *)(s32)&tx)->pad4 = 0;
    func_00208700(&tx, g->tex[2], 1);
    func_00208CB0(&tx, 5);
    func_002086D0(&tx, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->shard[i].on == 0) {
            continue;
        }
        alpha = (u32)(0.0f * func_00100FF0((f32)g->shard[i].t, 32.0f, 28.0f));
        (void)alpha;
        tx.c.r = 0x80;
        tx.c.g = 0x80;
        tx.c.b = 0x80;
        tx.c.a = alpha;
        tx.c.q = 1.0f;
        tx.v[0].s = 0.0f;
        tx.v[0].t = 0.0f;
        tx.v[1].s = 1.0f;
        tx.v[1].t = 0.0f;
        tx.v[2].s = 0.0f;
        tx.v[2].t = 1.0f;
        tx.v[3].s = 1.0f;
        tx.v[3].t = 1.0f;
        r = 0.35f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        cn[2].x = -r;
        cn[2].y = r;
        cn[2].z = 0.0f;
        cn[2].w = 1.0f;
        cn[3].x = r;
        cn[3].y = r;
        cn[3].z = 0.0f;
        cn[3].w = 1.0f;
        m4 = *(Mq_b420_01E00080 *)m3;
        func_00100E00(&m4, g->shard[i].t * 0xD903 + g->shard[i].rot, 2);
        func_00187B48(&v, &g->shard[i].vel, g->shard[i].t / 32.0f);
        func_00187B00(&v, &v, &g->shard[i].pos);
        v.y += 10.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->shard[i].t, 2.0f)));
        for (k = 0; k < 4; k++) {
            func_001878E0(&cn[k], &m4, &cn[k]);
            func_00187B00(&out[k], &cn[k], &v);
        }
        if (func_00205630(out, D_0030FF00, m, &tx, &depth) == 1) {
            func_002075F0(&tx, ot, (u32)depth);
        }
        g->shard[i].t++;
        if (g->shard[i].t > 32) {
            g->shard[i].on = 0;
        }
    }

    buf = -1;
    switch (g->t) {
    case 0xBA:
        buf = 0;
        break;
    case 0xC5:
        buf = 1;
        break;
    case 0xCD:
        buf = 2;
        break;
    case 0xD5:
        buf = 3;
        break;
    }
    if (buf >= 0) {
        i = g->nb;
        (void)i;
        g->blade[i].on = 1;
        g->blade[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (k = 0; k < 1; k++) {
            j = buf + 3;
            g->blade[i].rot[k] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade[i].pos[k] = g->jp[j];
            g->spark[c].pos[k] = g->jp[j];
            for (l = 0; l < 32; l++) {
                g->spark[c].c[k][l] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[k][l], 1.0f);
            }
        }
        g->nb++;
        if (g->nb >= 4) {
            g->nb = 0;
        }
        g->ns++;
        if (g->ns >= 4) {
            g->ns = 0;
        }
    }

    ((Quad_b420_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b420_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b420_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b420_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 4; i++) {
        if (g->blade[i].on == 0) {
            continue;
        }
        alpha = (7 - g->blade[i].t) * 0x56 / 7;
        pk.v[0].c.r = 0x54;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0x30;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade[i].t / 7.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 1; l++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->blade[i].pos[l]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->blade[i].rot[l], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (c = 0; c < 8; c++) {
                for (j = 0; j < 16; j++) {
                    n = g->gc[c][j];
                    ang = n % 4 * 32;
                    y = (n >> 2) * 32;
                    u2 = ang / 128.0f;
                    u3 = (32.0f + ang) / 128.0f;
                    w3 = y / 64.0f;
                    w2 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u2;
                    pk.v[0].t = w2;
                    pk.v[1].s = u3;
                    pk.v[1].t = w2;
                    pk.v[2].s = u2;
                    pk.v[2].t = w3;
                    pk.v[3].s = u3;
                    pk.v[3].t = w3;
                    if (func_002058D0(g->grid[c][j], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 50.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade[i].t, 7, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x64;
        spr.c.b = 0x1E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (n = 0; n < 1; n++) {
            v = g->blade[i].pos[n];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade[i].t++;
        if (g->blade[i].t > 7) {
            g->blade[i].on = 0;
        }
    }

    ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->spark[i].t / 32.0f);
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
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[i].t, 32, 1);
        for (k = 0; k < 1; k++) {
            for (q = 0; q < 32; q++) {
                func_00187B48(&v, &g->spark[i].v[k][q], s);
                func_00187B00(&v, &v, &g->spark[i].pos[k]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[i].c[k][q] % 4 * 32;
                y = (g->spark[i].c[k][q] >> 2) * 32;
                ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    n = -1;
    switch (g->t) {
    case 0xEA:
    case 0xFB:
    case 0x10C:
    case 0x11D:
        n = 1;
    }
    if (n == 1) {
        g->burst[g->cur].on = 1;
        g->burst[g->cur].t = 1;
        func_00101080(&g->burst[g->cur].pos, 0.5f);
        func_00187B00(&g->burst[g->cur].pos, &g->burst[g->cur].pos, &g->tgt);
        for (n = 0; n < 64; n++) {
            g->burst[g->cur].c[n] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->burst[g->cur].v[n], 1.5f);
        }
        for (j = 0; j < 128; j++) {
            func_00101080(&g->burst[g->cur].w[j], 1.5f);
        }
        for (l = 0; l < 64; l++) {
            g->burst[g->cur].c2[l] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->burst[g->cur].v3[l], 1.5f);
        }
        g->cur++;
        if (g->cur >= 4) {
            g->cur = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[3], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 8.0f * (0.8f + 0.2f * g->burst[i].t / 32.0f);
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
        alpha = (0x20 - g->burst[i].t) * 0xFF / 32;
        spr.c.r = 0x80;
        spr.c.g = 0xFF;
        spr.c.b = 0x30;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[i].t, 0x20, 1);
        for (l = 0; l < 64; l++) {
            func_00187B48(&v, &g->burst[i].v3[l], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c2[l] % 4 * 32;
            y = (g->burst[i].c2[l] >> 2) * 32;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 8.0f * (0.8f + 0.2f * g->burst[i].t / 32.0f);
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
        alpha = (0x20 - g->burst[i].t) * 0xFF / 32;
        a2 = (0x20 - g->burst[i].t) * 0x80 / 32;
        for (q = 0; q < 64; q++) {
            s = func_00100D50(g->burst[i].t, 0x20, 1);
            if (q % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xFF;
                spr.c.g = 0x5A;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[i].v[q], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c[q] % 4 * 32;
            y = (g->burst[i].c[q] >> 2) * 32;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[i].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[i].t, 0x20, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((f32)(0x20 - g->burst[i].t) / 32.0f));
        spr.c.r = 0x5E;
        spr.c.g = 0xFF;
        spr.c.b = 0x3A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 120.0f;
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
        ((Spr_b420_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b420_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b420_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b420_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b420_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b420_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b420_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        h = func_00100D50(g->burst[i].t, 0x20, 1);
        for (n = 0; n < 128; n++) {
            for (k = 0; k < 6; k++) {
                spr.c.r = 0xFF;
                spr.c.g = 0xF0;
                spr.c.b = 0x80;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[i].w[n], h + 0.007f * k);
                func_00187B00(&v, &v, &g->burst[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x20) {
            g->burst[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x15D - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x26 || g->t == 0xE0) {
        ret = 1;
    } else {
        if (g->t > 0x30 && g->t < 0x84) {
            ret = 6;
        }
        if (g->t > 0xEA && g->t < 0x13D) {
            ret = 6;
        }
        if (g->t == 0x84) {
            ret = 7;
        }
        if (g->t == 0x13D) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x15D) {
        ret = 8;
    }
    return ret;
}
