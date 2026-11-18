#include "common.h"

/* shape b248:01E00080 (b248), 3009 insns, 1 copy (-O3,p): b248 scene manager (b291:01E00080's tornado, bursts, puffs
   and motes with other timings, plus at 0x43 a glow sprite, a 32-step gouraud arc, 96 textured fins and 128 sparkles
   at the second joint); 13 words differ in the setup's 96-fin loop (counter/pointer registers s0/s2 and the r / -r
   FPRs swapped) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b248_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b248_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b248_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b248_01E00080 c;
    Uv_b248_01E00080 uv0;
    Xyz_b248_01E00080 p0;
    Uv_b248_01E00080 uv1;
    Xyz_b248_01E00080 p1;
    u8 tail[0x20];
} Spr_b248_01E00080;

typedef struct {
    Rgbaq_b248_01E00080 c;
    union {
        Uv_b248_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b248_01E00080 p;
} Tv_b248_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b248_01E00080 v[4];
    u64 pad70;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Quad_b248_01E00080;

typedef struct {
    Rgbaq_b248_01E00080 c;
    Xyz_b248_01E00080 p;
} Gv_b248_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Gv_b248_01E00080 v[4];
    u64 tail;
} Gq_b248_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b248_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[20][4];
    u8 pad58[8];
    Vec4f v[20][4];
} Burst_b248_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[48];
    u8 pad38[8];
    Vec4f v[48];
} Puff_b248_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f v[4];
} Mote_b248_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn;
    u8 pad24[0xC];
    Vec4f jp;
    s32 jn2;
    u8 pad44[0xC];
    Vec4f jp2;
    Vec4f tgt;
    Mtx_b248_01E00080 mat;
    f32 dist;
    u8 on;
    u8 padB5[3];
    s32 t1;
    u8 padBC[4];
    Vec4f arc[33][3];
    Vec4f fin[96][4];
    u8 c[128];
    Vec4f sp[128];
    Vec4f ring[17];
    Vec4f grid[21][17];
    Vec4f grid2[21][17];
    Vec4f ctr[1][21];
    u8 on2;
    u8 pad5671[3];
    s32 t2;
    u8 pad5678[8];
    Burst_b248_01E00080 burst[8];
    Vec4f pts[48];
    Puff_b248_01E00080 puff[18];
    Mote_b248_01E00080 mote[12];
} Scene_b248_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b248(s32 arg0, s32 code) {
    Scene_b248_01E00080 *g = (Scene_b248_01E00080 *)arg0;
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
    extern f32 func_001A6C60(f32);
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
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern s32 func_00101430(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    u8 alpha;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 w;
    f32 a;
    f32 b;
    f32 r;
    f32 s;
    f32 h;
    f32 e;
    f32 t0;
    f32 t1;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Mtx_b248_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    Vec4f v3;
    Spr_b248_01E00080 spr __attribute__((aligned(8)));
    Gq_b248_01E00080 lq __attribute__((aligned(8)));
    Quad_b248_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC2C0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->jn = func_001F5560(g->unitA, 0x1D, 1);
        g->jn2 = func_001F5560(g->unitA, 0x26, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->on = 0;
        for (j = 0; j < 33; j++) {
            s = func_0020B550((j << 16) >> 5);
            h = func_0020B480((j << 16) >> 5);
            g->arc[j][0].x = 3.3f * s;
            g->arc[j][0].y = 3.3f * h;
            g->arc[j][0].z = 0.0f;
            g->arc[j][0].w = 1.0f;
            g->arc[j][1].x = 5.4f * s;
            g->arc[j][1].y = 5.4f * h;
            g->arc[j][1].z = 0.0f;
            g->arc[j][1].w = 1.0f;
            g->arc[j][2].x = 5.5f * s;
            g->arc[j][2].y = 5.5f * h;
            g->arc[j][2].z = 0.0f;
            g->arc[j][2].w = 1.0f;
        }
        for (i = 0; i < 96; i++) {
            f = 0.1f + 0.9f * (i + 1) / 96.0f;
            r = 0.5f * f;
            h = 7.5f * f;
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
            cn[2].z = h;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = r;
            cn[3].z = h;
            cn[3].w = 1.0f;
            func_00101080(&v, 1.0f);
            func_00100E40(&m4, &v);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            for (k = 0; k < 4; k++) {
                func_001878E0(&g->fin[i][k], &m4, &cn[k]);
            }
        }
        for (i = 0; i < 128; i++) {
            g->c[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->sp[i], 0.2f);
        }
        g->on2 = 0;
        g->t2 = 0;
        for (i = 0; i < 48; i++) {
            func_00101080(&g->pts[i], 3.0f);
        }
        for (i = 0; i < 18; i++) {
            g->puff[i].on = 0;
        }
        for (w = 0; w < 12; w++) {
            g->mote[w].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->jn, &g->jp);
    if (g->t == 0x43) {
        func_001F5620(g->unitA, g->jn2, &g->jp2);
        g->jp2.y += 1.0f;
    }
    func_00187B18(&v, &g->tgt, &g->jp);
    func_00100E40(&g->mat, &v);
    func_00100E00(&g->mat, 0x4000, 0);
    g->dist = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    if (g->t == 0x43) {
        g->on = 1;
        g->t1 = 0;
    }
    if (g->on == 1) {
        ((Spr_b248_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b248_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b248_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b248_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b248_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        ((Uv_b248_01E00080 *)(s32)&spr.uv0)->u = 0x400;
        ((Uv_b248_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b248_01E00080 *)(s32)&spr.uv1)->u = 0x600;
        ((Uv_b248_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 15.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        a = (f32)(0x10 - g->t1) / 16.0f;
        alpha = (u32)(255.0f * a);
        spr.c.r = 0xC8;
        spr.c.g = 0x78;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp2);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Gq_b248_01E00080 *)(s32)&lq)->flags = 0x14;
        ((Gq_b248_01E00080 *)(s32)&lq)->size = 8;
        ((Gq_b248_01E00080 *)(s32)&lq)->regs = 0x41414141;
        ((Gq_b248_01E00080 *)(s32)&lq)->pad4 = 0;
        func_002086D0(&lq, func_00208D00(1));
        alpha = (u32)(255.0f * a);
        lq.v[0].c.r = 0xFF;
        lq.v[0].c.g = 0x50;
        lq.v[0].c.b = 0xC8;
        lq.v[0].c.a = alpha;
        lq.v[0].c.q = 1.0f;
        lq.v[1].c = lq.v[0].c;
        lq.v[2].c.r = 0x18;
        lq.v[2].c.g = 0x20;
        lq.v[2].c.b = 0xFF;
        lq.v[2].c.a = 0;
        lq.v[2].c.q = 1.0f;
        lq.v[3].c = lq.v[2].c;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp2);
        r = 0.3f + 0.7f * func_00100D50(g->t1, 0x10, 1);
        v.x = r;
        v.y = r;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (j = 0; j < 32; j++) {
            if (func_00100BA0(&g->arc[j][1], &g->arc[j + 1][1], &g->arc[j][0], &g->arc[j + 1][0], m, &lq,
                              &depth) == 1) {
                lq.v[0].p.z = 0xFFFFF8;
                lq.v[1].p.z = lq.v[0].p.z;
                lq.v[2].p.z = lq.v[0].p.z;
                lq.v[3].p.z = lq.v[0].p.z;
                func_002075F0(&lq, ot, 0);
            }
            if (func_00100BA0(&g->arc[j][1], &g->arc[j + 1][1], &g->arc[j][2], &g->arc[j + 1][2], m, &lq,
                              &depth) == 1) {
                lq.v[0].p.z = 0xFFFFF8;
                lq.v[1].p.z = lq.v[0].p.z;
                lq.v[2].p.z = lq.v[0].p.z;
                lq.v[3].p.z = lq.v[0].p.z;
                func_002075F0(&lq, ot, 0);
            }
        }
        ((Quad_b248_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b248_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b248_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b248_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)(96.0f * a);
        pk.v[0].c.r = 0x2E;
        pk.v[0].c.g = 0xA4;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0;
        pk.v[2].c.g = 0x20;
        pk.v[2].c.b = 0x80;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jp2);
        func_0020BC00(m, m2);
        for (i = 0; i < 96; i++) {
            pk.v[0].uv.st.s = 0.5f;
            pk.v[0].uv.st.t = 0.25f;
            pk.v[1].uv.st.s = 0.75f;
            pk.v[1].uv.st.t = 0.25f;
            pk.v[2].uv.st.s = 0.5f;
            pk.v[2].uv.st.t = 0.25f;
            pk.v[3].uv.st.s = 0.75f;
            pk.v[3].uv.st.t = 0.25f;
            if (func_00100BA0(&g->fin[i][0], &g->fin[i][1], &g->fin[i][2], &g->fin[i][3], m, &pk, &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        ((Spr_b248_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b248_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b248_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b248_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b248_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 0.4f;
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
        alpha = (u32)(128.0f * a);
        spr.c.r = 0x8F;
        spr.c.g = 0x84;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jp2);
        func_0020BC00(m, m2);
        s = 0.8f + 0.2f * func_00100D50(g->t1, 0x10, 1);
        for (i = 0; i < 128; i++) {
            x = g->c[i] % 4 * 32;
            y = (g->c[i] >> 2) * 32;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->sp[i], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t1++;
        if (g->t1 > 0x10) {
            g->on = 0;
        }
    }

    if (g->t == 0x5F) {
        g->on2 = 1;
        g->t2 = 0;
    }
    a = func_00101050(0xCD - g->t2, 0, 32) / 32.0f;
    if (g->on2 == 1) {
        for (i = 0; i < 1; i++) {
            for (x = 0; x < 21; x++) {
                s = 0.0f;
                w = (g->t2 * 0x71C + (i * 0x3039 + (x * 0x10000) / 20)) & 0xFFFF;
                g->ctr[i][x].x = s * func_0020B550(w);
                g->ctr[i][x].y = 0.0f;
                g->ctr[i][x].z = s * func_0020B480(w);
                g->ctr[i][x].w = 1.0f;
            }
        }
        b = func_00101050(g->t2, 0, 16);
        h = g->dist * b / 16.0f;
        r = 0.5f + 0.5f * b / 16.0f;
        ((Quad_b248_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b248_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b248_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b248_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)(100.0f * a);
        s = 10.0f * r;
        for (k = 0; k < 17; k++) {
            g->ring[k].x = s * func_0020B550((k << 16) >> 4);
            g->ring[k].y = 0.0f;
            g->ring[k].z = s * func_0020B480((k << 16) >> 4);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 1; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat, &g->jp);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                t0 = h * j / 20.0f;
                e = (f32)((0.1f + 0.9f * j / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                for (n = 0; n < 17; n++) {
                    func_00187B48(&g->grid[j][n], &g->ring[n], e);
                    g->grid[j][n].y = t0;
                    func_00187B00(&g->grid[j][n], &g->grid[j][n], &g->ctr[i][j]);
                }
            }
            s = (f32)i - (g->t2 % 10) / 10.0f;
            for (j = 0; j < 20; j++) {
                if (j == 0) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x80;
                    pk.v[2].c.b = 0x80;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (j == 19) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x80;
                    pk.v[2].c.b = 0x80;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                t0 = 5.0f * j / 20.0f + s;
                t1 = 5.0f * (j + 1) / 20.0f + s;
                for (k = 0; k < 16; k++) {
                    pk.v[0].uv.st.s = k / 16.0f;
                    pk.v[0].uv.st.t = t0;
                    pk.v[1].uv.st.s = (k + 1) / 16.0f;
                    pk.v[1].uv.st.t = t0;
                    pk.v[2].uv.st.s = k / 16.0f;
                    pk.v[2].uv.st.t = t1;
                    pk.v[3].uv.st.s = (k + 1) / 16.0f;
                    pk.v[3].uv.st.t = t1;
                    if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k], &g->grid[j + 1][k + 1],
                                      m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b248_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b248_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b248_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b248_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tex0, &pk.tex1);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b248_01E00080 *)(s32)&pk)->flags |= 0x800;
        alpha = (u32)(128.0f * a);
        s = 9.0f * r;
        for (k = 0; k < 17; k++) {
            g->ring[k].x = s * func_0020B550((k << 16) >> 4);
            g->ring[k].y = 0.0f;
            g->ring[k].z = s * func_0020B480((k << 16) >> 4);
            g->ring[k].w = 1.0f;
        }
        for (i = 0; i < 1; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat, &g->jp);
            func_0020BC00(m, m2);
            for (j = 0; j < 21; j++) {
                t0 = h * j / 20.0f;
                e = (f32)((0.1f + 0.9f * j / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(5461.0f * func_0020B550((((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 46) << 16) / 46) & 0xFFFF)), 1);
                for (k = 0; k < 17; k++) {
                    func_00187B48(&g->grid[j][k], &g->ring[k], e);
                    g->grid[j][k].y = t0;
                    func_00187B00(&g->grid[j][k], &g->grid[j][k], &g->ctr[i][j]);
                    func_001878E0(&g->grid2[j][k], &m4, &g->grid[j][k]);
                    g->grid2[j][k].y = t0 + 0.1f * (h / 20.0f) *
                                                func_0020B550((((k % 16) << 16 >> 4) +
                                                               (((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 48) << 16) / 48)) & 0xFFFF);
                    func_00187B00(&g->grid2[j][k], &g->grid2[j][k], &g->ctr[i][j]);
                }
            }
            for (w = 0; w < 20; w++) {
                if (w == 0) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x80;
                    pk.v[2].c.b = 0x80;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (w == 19) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x80;
                    pk.v[2].c.b = 0x80;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                for (k = 0; k < 16; k++) {
                    if (func_00100BA0(&g->grid2[w][k], &g->grid2[w][k + 1], &g->grid2[w + 1][k],
                                      &g->grid2[w + 1][k + 1], m, &pk, &depth) == 1) {
                        func_00100C60(&pk.v[0].uv, &pk.v[0].p, 0, 0);
                        func_00100C60(&pk.v[1].uv, &pk.v[1].p, 0, 0);
                        func_00100C60(&pk.v[2].uv, &pk.v[2].p, 0, 0);
                        func_00100C60(&pk.v[3].uv, &pk.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid[w][k], &g->grid[w][k + 1], &g->grid[w + 1][k],
                                          &g->grid[w + 1][k + 1], m, &pk, &depth) == 1 &&
                            func_00101430(&pk.v[0].p, &pk.v[1].p, &pk.v[2].p) == 1) {
                            func_002075F0(&pk, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0xCD) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x5F && g->t < 0x12C) {
        n = g->t % 8;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        func_00187B18(&v, &g->tgt, &g->jp);
        func_00187B48(&v, &v, func_00101050(g->t2, 0, 16) / 16.0f);
        b = 10.0f * (0.5f + 0.5f * func_00101050(g->t2, 0, 16) / 16.0f);
        for (j = 0; j < 20; j++) {
            r = (f32)(b * ((0.1f + 0.9f * j / 20.0f) *
                           (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF))));
            for (k = 0; k < 4; k++) {
                g->burst[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00187B48(&v2, &v, j / 20.0f + 0.05f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
                func_00187B00(&v2, &v2, &g->jp);
                w = (((k << 16) >> 2) + ((func_0019A5C8() >> 23) % 256 << 16 >> 8)) & 0xFFFF;
                v3.x = r * func_0020B550(w);
                v3.y = 0.0f;
                v3.z = r * func_0020B480(w);
                v3.w = 1.0f;
                func_001878E0(&g->burst[n].v[j][k], &g->mat, &v3);
                func_00187B00(&g->burst[n].v[j][k], &g->burst[n].v[j][k], &v2);
            }
        }
    }

    ((Spr_b248_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b248_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b248_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b248_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b248_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = (f32)func_00101050(g->t - 0x5F, 0, 32) * (f32)func_00101050(0x12C - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 8; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (50.0f * func_0020B550((g->burst[i].t << 15) >> 3)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (w = 0; w < 20; w++) {
            r = (0.5f + 0.5f * w / 20.0f) * (8.0f * (0.2f + 0.8f * func_00100D50(g->burst[i].t, 8, 1)));
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
            for (k = 0; k < 4; k++) {
                x = g->burst[i].c[w][k] % 4 * 32;
                y = (g->burst[i].c[w][k] >> 2) * 32;
                ((Uv_b248_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b248_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b248_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b248_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v = g->burst[i].v[w][k];
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 8) {
            g->burst[i].on = 0;
        }
    }

    if (g->t > 0x6F && g->t < 0x12C) {
        n = g->t % 18;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (k = 0; k < 48; k++) {
            g->puff[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&v, 0.5f);
            func_00187B00(&g->puff[n].v[k], &v, &g->pts[k]);
        }
    }

    ((Spr_b248_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b248_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b248_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b248_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b248_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0x12C - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 18; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * ((18 - g->puff[i].t) * 100 / 18));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.2f + 0.8f * func_00100D50(g->puff[i].t, 18, 1));
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
        s = 0.05f + g->puff[i].t / 18.0f;
        for (k = 0; k < 48; k++) {
            x = g->puff[i].c[k] % 4 * 32;
            y = (g->puff[i].c[k] >> 2) * 32;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->puff[i].v[k], s);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 18) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0x6F && g->t < 0x12C) {
        n = g->t % 12;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (k = 0; k < 4; k++) {
            g->mote[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->mote[n].v[k], 1.5f);
        }
    }

    ((Spr_b248_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b248_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b248_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b248_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b248_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    t1 = func_00101050(0x12C - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(t1 * (32.0f * func_0020B550((g->mote[i].t << 15) / 12)));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 15.0f;
        cn[0].x = h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        s = 0.3f + 0.7f * g->mote[i].t / 12.0f;
        for (k = 0; k < 4; k++) {
            x = g->mote[i].c[k] % 4 * 32;
            y = (g->mote[i].c[k] >> 2) * 32;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b248_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->mote[i].v[k], s);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 12) {
            g->mote[i].on = 0;
        }
    }

    if (g->t == 0x65) {
        ret = 1;
    } else {
        if (g->t > 0x6F && g->t < 0x12B) {
            ret = 6;
        }
        if (g->t == 0x12B) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x12C) {
        ret = 8;
    }
    return ret;
}
