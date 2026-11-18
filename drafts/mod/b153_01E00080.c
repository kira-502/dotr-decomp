#include "common.h"

/* shape b153:01E00080 (b153), 3152 insns, 1 copy (-O3,p): scene effect: a radial blur and a 48-frame burst at the
   target, a spinning quad, puffs, motes, rings and sparks at a lifted joint point */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b153_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b153_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b153_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b153_01E00080 c;
    Uv_b153_01E00080 uv0;
    Xyz_b153_01E00080 p0;
    Uv_b153_01E00080 uv1;
    Xyz_b153_01E00080 p1;
    u8 tail[0x20];
} Spr_b153_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b153_01E00080 c;
        Uv_b153_01E00080 uv;
        Xyz_b153_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b153_01E00080;

typedef struct {
    Rgbaq_b153_01E00080 c;
    f32 s, t;
    Xyz_b153_01E00080 p;
} Tv_b153_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b153_01E00080 v[4];
    u8 tail[0x20];
} Quad_b153_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b153_01E00080;

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
} Burst_b153_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][20];
    u8 pad1C[4];
    Vec4f pos[1];
    Vec4f v[1][20];
} Puff_b153_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][4];
    u8 padC[4];
    Vec4f pos[1];
    Vec4f v[1][4];
} Mote_b153_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Ring_b153_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][16];
    u8 pad18[8];
    Vec4f pos[1];
    Vec4f v[1][16];
} Spark_b153_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f tgt;
    Vec4f scr;
    s32 jn[2];
    u8 pad48[8];
    Vec4f jp[2];
    Mtx_b153_01E00080 mat;
    Vec4f pos;
    s32 cur;
    u8 padC4[0xC];
    Burst_b153_01E00080 burst[1];
    u8 on2;
    u8 pad11B1[3];
    s32 t2;
    u8 on3;
    u8 pad11B9[3];
    s32 t3;
    Puff_b153_01E00080 puff[28];
    Mote_b153_01E00080 mote[20];
    Ring_b153_01E00080 ring[16];
    Spark_b153_01E00080 spark[4];
} Scene_b153_01E00080;


#pragma optimization_level 3

static s32 func_01E00080_b153(s32 arg0, s32 code) {
    Scene_b153_01E00080 *g = (Scene_b153_01E00080 *)arg0;
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
    extern void func_00205CA0(void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
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
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    u8 a2;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Vec4f v;
    Spr_b153_01E00080 spr __attribute__((aligned(8)));
    Tri_b153_01E00080 tri __attribute__((aligned(8)));
    Quad_b153_01E00080 pk __attribute__((aligned(8)));
    Xyz_b153_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x6A40);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x22, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x2C, 0);
        g->cur = 0;
        for (i = 0; i < 1; i++) {
            g->burst[i].on = 0;
        }
        g->on2 = 0;
        g->on3 = 0;
        for (i = 0; i < 28; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 20; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->ring[i].on = 0;
        }
        for (i = 0; i < 4; i++) {
            g->spark[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    if (g->t < 0x55) {
        func_00187B18(&v, &g->jp[1], &g->jp[0]);
        func_00100E40(&g->mat, &v);
    } else {
        func_0020BBB0(&g->mat);
        if (g->obj < 0) {
            func_00100E00(&g->mat, 0x8000, 1);
        }
    }
    f = (f32)func_00101050(g->t - 0x55, 0, 10) / 10.0f;
    func_00187B18(&v, &g->tgt, &g->jp[0]);
    func_00187B48(&v, &v, f);
    func_00187B00(&g->pos, &v, &g->jp[0]);
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

    if (g->t == 0x5F) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b153_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b153_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b153_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b153_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b153_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x30 - g->t2) * 0x40 / 48;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            r = 1.0f + 0.15f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b153_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b153_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b153_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        g->t2++;
        if (g->t2 > 48) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x5F) {
        for (j = 0; j < 1; j++) {
            g->cur = j;
            g->burst[g->cur].on = 1;
            g->burst[g->cur].t = 1;
            g->burst[g->cur].pos.x = 0.0f;
            g->burst[g->cur].pos.y = 0.0f;
            g->burst[g->cur].pos.z = 0.0f;
            g->burst[g->cur].pos.w = 1.0f;
            func_00187B00(&g->burst[g->cur].pos, &g->burst[g->cur].pos, &g->tgt);
            for (i = 0; i < 64; i++) {
                g->burst[g->cur].c[i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst[g->cur].v[i], 0.9f);
            }
            for (i = 0; i < 128; i++) {
                func_00101080(&g->burst[g->cur].w[i], 1.25f);
            }
            for (i = 0; i < 64; i++) {
                g->burst[g->cur].c2[i] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[g->cur].v3[i], 0.9f);
            }
        }
    }

    for (i = 0; i < 1; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 6.0f * (0.8f + 0.2f * g->burst[i].t / 48.0f);
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
        alpha = (0x30 - g->burst[i].t) * 0xC8 / 48;
        spr.c.r = 0xFF;
        spr.c.g = 0x6C;
        spr.c.b = 0x38;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[i].t, 0x30, 1);
        for (j = 0; j < 64; j++) {
            func_00187B48(&v, &g->burst[i].v3[j], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c2[j] % 4 * 32;
            y = (g->burst[i].c2[j] >> 2) * 32;
            ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 5.0f * (0.8f + 0.2f * g->burst[i].t / 48.0f);
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
        alpha = (0x30 - g->burst[i].t) * 0xFF / 48;
        a2 = (0x30 - g->burst[i].t) * 0x80 / 48;
        for (j = 0; j < 64; j++) {
            s = func_00100D50(g->burst[i].t, 0x30, 1);
            if (j % 2 == 0) {
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
                spr.c.g = 0x60;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[i].v[j], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c[j] % 4 * 32;
            y = (g->burst[i].c[j] >> 2) * 32;
            ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[i].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[i].t, 0x30, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((f32)(0x30 - g->burst[i].t) / 48.0f));
        spr.c.r = 0xFF;
        spr.c.g = 0x5E;
        spr.c.b = 0x3A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 65.0f;
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
        ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 0.5f;
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
        n = g->burst[i].t;
        f = (f32)(0x30 - n) / 48.0f;
        h = func_00100D50(n, 0x30, 1);
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 6; k++) {
                alpha = (u32)(f * ((k + 6) * 0xFF / 12));
                spr.c.r = 0xFF;
                spr.c.g = 0x8C;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[i].w[j], h + 0.01f * k);
                func_00187B00(&v, &v, &g->burst[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x30) {
            g->burst[i].on = 0;
        }
    }

    if (g->t == 0x31) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Quad_b153_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b153_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b153_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b153_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208700(&pk, g->tex[3], 1);
        func_00208CB0(&pk, 5);
        func_002086D0(&pk, func_00208D00(0));
        func_0020EB40(m);
        func_00187B60(m2, &g->mat, &g->pos);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * func_00101020((f32)g->t3, 32.0f) * func_00100FF0((f32)g->t3, 78.0f, 46.0f));
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        r = 1.5f;
        cn[0].x = 0.0f;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = 0.0f;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        cn[2].x = 0.0f;
        cn[2].y = -r;
        cn[2].z = 12.0f;
        cn[2].w = 1.0f;
        cn[3].x = 0.0f;
        cn[3].y = r;
        cn[3].z = 12.0f;
        cn[3].w = 1.0f;
        pk.v[0].s = 0.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 0.0f;
        pk.v[1].t = 1.0f;
        pk.v[2].s = 1.0f;
        pk.v[2].t = 0.0f;
        pk.v[3].s = 1.0f;
        pk.v[3].t = 1.0f;
        if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
            func_002075F0(&pk, ot, (u32)depth);
        }
        g->t3++;
        if (g->t3 > 0x4E) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x31 && g->t < 0x55) {
        n = g->t % 28;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->puff[n].pos[i] = g->pos;
            for (k = 0; k < 20; k++) {
                g->puff[n].c[i][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->puff[n].v[i][k], 0.08f);
            }
        }
    }

    ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x31, 0, 32) / 32.0f;
    for (i = 0; i < 28; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B480((g->puff[i].t << 14) / 28)));
        r = 0.25f * (0.5f + 0.5f * (28 - g->puff[i].t) / 28.0f);
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
        s = 0.2f + 0.8f * func_00100D50(g->puff[i].t, 28, 1);
        h = 8.0f * g->puff[i].t / 28.0f;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x5A;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 20; k++) {
                x = g->puff[i].c[j][k] % 4 * 32;
                y = (g->puff[i].c[j][k] >> 2) * 32;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->puff[i].v[j][k], s);
                func_00187B00(&v, &v, &g->puff[i].pos[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 28) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0x31 && g->t < 0x55) {
        n = g->t % 20;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->mote[n].pos[i] = g->pos;
            for (k = 0; k < 4; k++) {
                g->mote[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->mote[n].v[i][k], 0.05f);
            }
        }
    }

    ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x31, 0, 32) / 32.0f;
    for (i = 0; i < 20; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->mote[i].t << 15) / 20)));
        r = 1.5f * (0.3f + 0.7f * (20 - g->mote[i].t) / 20.0f);
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
        s = 0.8f + 0.2f * (20 - g->mote[i].t) / 20.0f;
        h = -1.0f + 6.0f * g->mote[i].t / 20.0f;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 4; k++) {
                x = g->mote[i].c[j][k] % 4 * 32;
                y = (g->mote[i].c[j][k] >> 2) * 32;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->mote[i].v[j][k], s);
                func_00187B00(&v, &v, &g->mote[i].pos[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 20) {
            g->mote[i].on = 0;
        }
    }

    if (g->t > 0x55 && g->t < 0x5F) {
        n = g->t % 16;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->ring[n].pos[i] = g->pos;
            for (k = 0; k < 32; k++) {
                g->ring[n].c[i][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->ring[n].v[i][k], 0.4f);
            }
        }
    }

    ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480((g->ring[i].t << 14) >> 4));
        r = 0.5f * (0.5f + 0.5f * (16 - g->ring[i].t) / 16.0f);
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
        s = 0.7f + 0.3f * func_00100D50(g->ring[i].t, 16, 1);
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x5A;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 32; k++) {
                x = g->ring[i].c[j][k] % 4 * 32;
                y = (g->ring[i].c[j][k] >> 2) * 32;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->ring[i].v[j][k], s);
                func_00187B00(&v, &v, &g->ring[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 16) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0x55 && g->t < 0x5F) {
        n = g->t % 4;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->spark[n].pos[i] = g->pos;
            for (k = 0; k < 16; k++) {
                g->spark[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[n].v[i][k], 0.2f);
            }
        }
    }

    ((Spr_b153_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b153_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b153_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b153_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b153_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480((g->spark[i].t << 14) >> 2));
        r = 1.5f * (0.3f + 0.7f * (4 - g->spark[i].t) / 4.0f);
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
        s = 0.1f + 0.9f * g->spark[i].t / 4.0f;
        h = 7.0f * g->spark[i].t / 4.0f * g->obj;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 16; k++) {
                x = g->spark[i].c[j][k] % 4 * 32;
                y = (g->spark[i].c[j][k] >> 2) * 32;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b153_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i].v[j][k], s);
                func_00187B00(&v, &v, &g->pos);
                v.z += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    spr.p0.z = 0xFFFFF8;
                    spr.p1.z = spr.p0.z;
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 4) {
            g->spark[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0xAF - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x55) {
        ret = 1;
    } else {
        if (g->t > 0x5F && g->t < 0x8F) {
            ret = 6;
        }
        if (g->t == 0x8F) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xAF) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
