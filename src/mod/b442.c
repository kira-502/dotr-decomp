#include "common.h"

/* shape b442:01E00080 (b442), 3990 insns, 1 copy (-O3,p): b442 scene manager, b352:01E00080's relative with one
   joint: flash from 0x3C, tornado from 0x55, particle sections, an 8-sprite spray and b222's rippling water grid over
   the first 0x110 frames */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b442_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b442_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b442_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b442_01E00080 c;
    Uv_b442_01E00080 uv0;
    Xyz_b442_01E00080 p0;
    Uv_b442_01E00080 uv1;
    Xyz_b442_01E00080 p1;
    u8 tail[0x20];
} Spr_b442_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b442_01E00080 c;
        Xyz_b442_01E00080 p;
    } v[4];
    u64 tail;
} Strip_b442_01E00080;

typedef struct {
    Rgbaq_b442_01E00080 c;
    union {
        Uv_b442_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b442_01E00080 p;
} Tv_b442_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b442_01E00080 v[4];
    u64 pad70;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Quad_b442_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b442_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[20][4];
    u8 pad58[8];
    Vec4f v[20][4];
} Burst_b442_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[48];
    u8 pad38[8];
    Vec4f v[48];
} Puff_b442_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f v[4];
} Mote_b442_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Drop_b442_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Spray_b442_01E00080;

typedef struct {
    union {
        Uv_b442_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b442_01E00080 p;
} Txv_b442_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b442_01E00080 c;
    Txv_b442_01E00080 v[4];
    u8 tail[0x20];
} Tex_b442_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    s32 jn;
    u8 pad28[8];
    Vec4f jp;
    Vec4f anchor;
    Vec4f tgt;
    Mtx_b442_01E00080 mat;
    f32 dist;
    u8 on1;
    u8 padB5[3];
    s32 t1;
    u8 padBC[4];
    Vec4f rim[33][3];
    Vec4f shard[96][4];
    u8 c[128];
    Vec4f spk[128];
    Vec4f ring[17];
    Vec4f grid[21][17];
    Vec4f grid2[21][17];
    Vec4f ctr[1][21];
    u8 on;
    u8 pad5671[3];
    s32 t2;
    u8 pad5678[8];
    Burst_b442_01E00080 burst[8];
    Vec4f pts[48];
    Puff_b442_01E00080 puff[18];
    Mote_b442_01E00080 mote[12];
    Drop_b442_01E00080 drop[12];
    Spray_b442_01E00080 spray[32];
    Vec4f grid3[17][17];
    s32 ph[17][17];
    u8 on5;
    u8 padF1C5[3];
    s32 t5;
} Scene_b442_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b442(s32 arg0, s32 code) {
    Scene_b442_01E00080 *g = (Scene_b442_01E00080 *)arg0;
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
    f32 q;
    f32 f;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b442_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    Vec4f v3;
    Spr_b442_01E00080 spr __attribute__((aligned(8)));
    Strip_b442_01E00080 st __attribute__((aligned(8)));
    Quad_b442_01E00080 pk __attribute__((aligned(8)));
    Tex_b442_01E00080 tx __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xF1D0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        g->jn = func_001F5560(g->unitA, 0x30, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            w = (i << 16) >> 5;
            s = func_0020B550(w);
            r = func_0020B480(w);
            g->rim[i][0].x = 6.5f * s;
            g->rim[i][0].y = 6.5f * r;
            g->rim[i][0].z = 0.0f;
            g->rim[i][0].w = 1.0f;
            g->rim[i][1].x = 20.8f * s;
            g->rim[i][1].y = 20.8f * r;
            g->rim[i][1].z = 0.0f;
            g->rim[i][1].w = 1.0f;
            g->rim[i][2].x = 22.0f * s;
            g->rim[i][2].y = 22.0f * r;
            g->rim[i][2].z = 0.0f;
            g->rim[i][2].w = 1.0f;
        }
        for (i = 0; i < 96; i++) {
            f = 0.1f + 0.9f * (i + 1) / 96.0f;
            r = 2.0f * f;
            a = -r;
            b = 30.0f * f;
            cn[0].x = 0.0f;
            cn[0].y = a;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = 0.0f;
            cn[2].y = a;
            cn[2].z = b;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = r;
            cn[3].z = b;
            cn[3].w = 1.0f;
            func_00101080(&v, 1.0f);
            func_00100E40(&m4, &v);
            func_00100E00(&m4, ((func_0019A5C8() >> 23) % 256 << 16) >> 8, 2);
            for (k = 0; k < 4; k++) {
                func_001878E0(&g->shard[i][k], &m4, &cn[k]);
            }
        }
        for (i = 0; i < 128; i++) {
            g->c[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spk[i], 0.4f);
        }
        j = 0;
        g->on = j;
        g->t2 = 0;
        for (i = 0; i < 48; i++) {
            func_00101080(&g->pts[i], 4.0f);
        }
        for (i = 0; i < 18; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->drop[i].on = 0;
        }
        for (k = 0; k < 32; k++) {
            g->spray[k].on = 0;
        }
        for (i = 0; i < 17; i++) {
            a = 600.0f * i / 16.0f;
            for (j = 0; j < 17; j++) {
                b = 600.0f * j / 16.0f;
                g->grid3[i][j].x = a - 300.0f;
                g->grid3[i][j].y = 0.0f;
                g->grid3[i][j].z = b - 300.0f;
                g->grid3[i][j].w = 1.0f;
                g->ph[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on5 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->jn, &g->jp);
    if (g->t == 0x3C) {
        g->anchor = g->jp;
    }
    func_00187B18(&v, &g->tgt, &g->jp);
    func_00100E40(&g->mat, &v);
    func_00100E00(&g->mat, 0x4000, 0);
    g->dist = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    if (g->t == 0x3C) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 64;
        y = 0;
        ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        r = 60.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        a = 255.0f * ((32 - g->t1) / 32.0f);
        alpha = (u32)a;
        spr.c.r = 0xFF;
        spr.c.g = 0xE0;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->anchor);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Strip_b442_01E00080 *)(s32)&st)->flags = 0x14;
        ((Strip_b442_01E00080 *)(s32)&st)->size = 8;
        ((Strip_b442_01E00080 *)(s32)&st)->regs = 0x41414141;
        ((Strip_b442_01E00080 *)(s32)&st)->pad4 = 0;
        func_002086D0(&st, func_00208D00(1));
        alpha = (u32)a;
        st.v[0].c.r = 0x9B;
        st.v[0].c.g = 0x8C;
        st.v[0].c.b = 0x5A;
        st.v[0].c.a = alpha;
        st.v[0].c.q = 1.0f;
        st.v[1].c = st.v[0].c;
        st.v[2].c.r = 0xFF;
        st.v[2].c.g = 0x20;
        st.v[2].c.b = 0x20;
        st.v[2].c.a = 0;
        st.v[2].c.q = 1.0f;
        st.v[3].c = st.v[2].c;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->anchor);
        s = 0.3f + 0.7f * func_00100D50(g->t1, 32, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->rim[i][1], &g->rim[i + 1][1], &g->rim[i][0], &g->rim[i + 1][0], m, &st, &depth) ==
                1) {
                st.v[0].p.z = 0xFFFFF8;
                st.v[1].p.z = st.v[0].p.z;
                st.v[2].p.z = st.v[0].p.z;
                st.v[3].p.z = st.v[0].p.z;
                func_002075F0(&st, ot, 0);
            }
            if (func_00100BA0(&g->rim[i][1], &g->rim[i + 1][1], &g->rim[i][2], &g->rim[i + 1][2], m, &st, &depth) ==
                1) {
                st.v[0].p.z = 0xFFFFF8;
                st.v[1].p.z = st.v[0].p.z;
                st.v[2].p.z = st.v[0].p.z;
                st.v[3].p.z = st.v[0].p.z;
                func_002075F0(&st, ot, 0);
            }
        }
        ((Quad_b442_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b442_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b442_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b442_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)a;
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0xB2;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0x50;
        pk.v[2].c.g = 0x5F;
        pk.v[2].c.b = 0x20;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->anchor);
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
            if (func_00100BA0(&g->shard[i][0], &g->shard[i][1], &g->shard[i][2], &g->shard[i][3], m, &pk, &depth) ==
                1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
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
        alpha = (u32)a;
        spr.c.r = 0xFA;
        spr.c.g = 0xFF;
        spr.c.b = 0x8C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->anchor);
        func_0020BC00(m, m2);
        s = 0.8f + 0.2f * func_00100D50(g->t1, 32, 1);
        for (i = 0; i < 128; i++) {
            x = g->c[i] % 4 * 32;
            y = (g->c[i] >> 2) * 32;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->spk[i], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t1++;
        if (g->t1 > 32) {
            g->on1 = 0;
        }
    }

    if (g->t == 0x55) {
        g->on = 1;
        g->t2 = 0;
    }
    h = func_00101050(0x7B - g->t2, 0, 32) / 32.0f;
    if (g->on == 1) {
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 21; j++) {
                s = 0.0f;
                w = (g->t2 * 0x71C + (i * 0x3039 + (j * 0x10000) / 20)) & 0xFFFF;
                g->ctr[i][j].x = s * func_0020B550(w);
                g->ctr[i][j].y = 0.0f;
                g->ctr[i][j].z = s * func_0020B480(w);
                g->ctr[i][j].w = 1.0f;
            }
        }
        b = func_00101050(g->t2, 0, 16);
        e = g->dist * b / 16.0f;
        t0 = 0.5f + 0.5f * b / 16.0f;
        ((Quad_b442_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b442_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b442_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b442_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        r = 128.0f * h;
        alpha = (u32)r;
        s = 9.0f * t0;
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
                a = e * j / 20.0f;
                q = (f32)((0.2f + 0.8f * j / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                for (n = 0; n < 17; n++) {
                    func_00187B48(&g->grid[j][n], &g->ring[n], q);
                    g->grid[j][n].y = a;
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
                a = 5.0f * j / 20.0f + s;
                t1 = 5.0f * (j + 1) / 20.0f + s;
                for (k = 0; k < 16; k++) {
                    pk.v[0].uv.st.s = k / 16.0f;
                    pk.v[0].uv.st.t = a;
                    pk.v[1].uv.st.s = (k + 1) / 16.0f;
                    pk.v[1].uv.st.t = a;
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
        ((Quad_b442_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b442_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b442_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b442_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tex0, &pk.tex1);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b442_01E00080 *)(s32)&pk)->flags |= 0x800;
        alpha = (u32)r;
        s = 8.5f * t0;
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
                a = e * j / 20.0f;
                q = (f32)((0.2f + 0.8f * j / 20.0f) *
                          (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF)));
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(5461.0f * func_0020B550((((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 46) << 16) / 46) & 0xFFFF)), 1);
                for (k = 0; k < 17; k++) {
                    func_00187B48(&g->grid[j][k], &g->ring[k], q);
                    g->grid[j][k].y = a;
                    func_00187B00(&g->grid[j][k], &g->grid[j][k], &g->ctr[i][j]);
                    func_001878E0(&g->grid2[j][k], &m4, &g->grid[j][k]);
                    g->grid2[j][k].y = a + 0.1f * (e / 20.0f) *
                                                func_0020B550((((k % 16) << 16 >> 4) +
                                                               (((j % 8 << 16) >> 3) + (((g->t2 + i * 5) % 48) << 16) / 48)) & 0xFFFF);
                    func_00187B00(&g->grid2[j][k], &g->grid2[j][k], &g->ctr[i][j]);
                }
            }
            for (j = 0; j < 20; j++) {
                if (j == 0) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x85;
                    pk.v[0].c.b = 0x8A;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x85;
                    pk.v[2].c.b = 0x8A;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (j == 19) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x85;
                    pk.v[0].c.b = 0x8A;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x85;
                    pk.v[2].c.b = 0x8A;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x85;
                    pk.v[0].c.b = 0x8A;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                for (k = 0; k < 16; k++) {
                    if (func_00100BA0(&g->grid2[j][k], &g->grid2[j][k + 1], &g->grid2[j + 1][k],
                                      &g->grid2[j + 1][k + 1], m, &pk, &depth) == 1) {
                        func_00100C60(&pk.v[0].uv, &pk.v[0].p, 0, 0);
                        func_00100C60(&pk.v[1].uv, &pk.v[1].p, 0, 0);
                        func_00100C60(&pk.v[2].uv, &pk.v[2].p, 0, 0);
                        func_00100C60(&pk.v[3].uv, &pk.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k],
                                          &g->grid[j + 1][k + 1], m, &pk, &depth) == 1 &&
                            func_00101430(&pk.v[0].p, &pk.v[1].p, &pk.v[2].p) == 1) {
                            func_002075F0(&pk, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x7B) {
            g->on = 0;
        }
    }

    if (g->t > 0x55 && g->t < 0xD0) {
        n = g->t % 8;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        func_00187B18(&v, &g->tgt, &g->jp);
        func_00187B48(&v, &v, func_00101050(g->t2, 0, 16) / 16.0f);
        b = 9.0f * (0.5f + 0.5f * func_00101050(g->t2, 0, 16) / 16.0f);
        for (j = 0; j < 20; j++) {
            s = (f32)(b * ((0.2f + 0.8f * j / 20.0f) *
                           (0.8 + 0.2f * func_0020B550(((j % 12 << 16) / 12 - g->t2 * 0x8AE) & 0xFFFF))));
            for (i = 0; i < 4; i++) {
                g->burst[n].c[j][i] = (func_0019A5C8() >> 23) % 8;
                func_00187B48(&v2, &v, j / 20.0f + 0.05f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
                func_00187B00(&v2, &v2, &g->jp);
                w = (((i << 16) >> 2) + ((func_0019A5C8() >> 23) % 256 << 16 >> 8)) & 0xFFFF;
                v3.x = s * func_0020B550(w);
                v3.y = 0.0f;
                v3.z = s * func_0020B480(w);
                v3.w = 1.0f;
                func_001878E0(&g->burst[n].v[j][i], &g->mat, &v3);
                func_00187B00(&g->burst[n].v[j][i], &g->burst[n].v[j][i], &v2);
            }
        }
    }

    ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = (f32)func_00101050(g->t - 0x55, 0, 32) * (f32)func_00101050(0xD0 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 8; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (80.0f * func_0020B550((g->burst[i].t << 15) >> 3)));
        spr.c.r = 0x6C;
        spr.c.g = 0x94;
        spr.c.b = 0x9B;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 20; j++) {
            r = (0.5f + 0.5f * j / 20.0f) * (8.0f * (0.2f + 0.8f * func_00100D50(g->burst[i].t, 8, 1)));
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
                x = g->burst[i].c[j][k] % 4 * 32;
                y = (g->burst[i].c[j][k] >> 2) * 32;
                ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v = g->burst[i].v[j][k];
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

    if (g->t > 0x65 && g->t < 0xD0) {
        n = g->t % 18;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (k = 0; k < 48; k++) {
            g->puff[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&v, 0.3f);
            func_00187B00(&g->puff[n].v[k], &v, &g->pts[k]);
        }
    }

    ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0xD0 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 18; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (60.0f * func_00100FF0(g->puff[i].t, 18.0f, 12.0f)));
        spr.c.r = 0x6C;
        spr.c.g = 0x91;
        spr.c.b = 0x9B;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 20.0f * (0.2f + 0.8f * func_00100D50(g->puff[i].t, 18, 1));
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
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t > 0x65 && g->t < 0xD0) {
        n = g->t % 12;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (k = 0; k < 4; k++) {
            g->mote[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->mote[n].v[k], 2.0f);
        }
    }

    ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0xD0 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (60.0f * func_0020B550((g->mote[i].t << 15) / 12)));
        spr.c.r = 0x80;
        spr.c.g = 0xB9;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 18.0f;
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
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t > 0x55 && g->t < 0xD0) {
        n = g->t % 12;
        g->drop[n].on = 1;
        g->drop[n].t = 0;
        g->drop[n].pos = g->jp;
        for (k = 0; k < 4; k++) {
            g->drop[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->drop[n].v[k], 1.0f);
        }
    }

    ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = func_00101050(0xD0 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 12; i++) {
        if (g->drop[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (96.0f * func_0020B480((g->drop[i].t << 14) / 12)));
        spr.c.r = 0x6C;
        spr.c.g = 0x94;
        spr.c.b = 0x9B;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.5f + 0.5f * g->drop[i].t / 12.0f);
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
        s = 0.1f + 0.9f * g->drop[i].t / 12.0f;
        for (k = 0; k < 4; k++) {
            x = g->drop[i].c[k] % 4 * 32;
            y = (g->drop[i].c[k] >> 2) * 32;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->drop[i].v[k], s);
            func_00187B00(&v, &v, &g->drop[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->drop[i].t++;
        if (g->drop[i].t > 12) {
            g->drop[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x3C) {
        n = g->t % 32;
        g->spray[n].on = 1;
        g->spray[n].t = 0;
        g->spray[n].pos = g->jp;
        for (k = 0; k < 8; k++) {
            g->spray[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->spray[n].v[k], 0.8f);
        }
    }

    ((Spr_b442_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b442_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b442_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b442_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b442_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->spray[i].on == 0) {
            continue;
        }
        alpha = (u32)(100.0f * func_0020B480((g->spray[i].t << 14) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.3f + 0.7f * func_00100D50(g->spray[i].t, 32, 1));
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
        s = 0.1f + 0.9f * g->spray[i].t / 32.0f;
        for (k = 0; k < 8; k++) {
            x = g->spray[i].c[k] % 4 * 32;
            y = (g->spray[i].c[k] >> 2) * 32;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b442_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->spray[i].v[k], s);
            func_00187B00(&v, &v, &g->spray[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spray[i].t++;
        if (g->spray[i].t > 32) {
            g->spray[i].on = 0;
        }
    }

    if (g->t == 0) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Tex_b442_01E00080 *)(s32)&tx)->flags = 0x24;
        ((Tex_b442_01E00080 *)(s32)&tx)->size = 9;
        ((Tex_b442_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b442_01E00080 *)(s32)&tx)->pad4 = 0;
        func_002086D0(&tx, func_00208D00(0));
        func_00208700(&tx, g->tex[4], 1);
        func_00208CB0(&tx, 0);
        f = func_00101020((f32)g->t5, 32.0f);
        a = f * func_00100FF0((f32)g->t5, 272.0f, 208.0f);
        for (buf = 0; buf < 1; buf++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 20.0f - 2.0f * (7.0f * buf);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (buf == 0) {
                alpha = (u32)(110.0f * a);
            } else {
                alpha = (u32)(80.0f * a);
            }
            tx.c.r = 0x80;
            tx.c.g = 0x96;
            tx.c.b = 0xA0;
            tx.c.a = alpha;
            tx.c.q = 1.0f;
            for (j = 0; j < 17; j++) {
                for (n = 0; n < 17; n++) {
                    g->grid3[j][n].y = 7.0f * func_0020B550((g->ph[j][n] + buf * 0x33333 + g->t5 * 0x14D) & 0xFFFF);
                }
            }
            x = ((buf % 2 * 2 - 1) * ((g->t5 + buf * 0x20) % 128 << 16 >> 7)) & 0xFFFF;
            f = 0.1f * func_0020B550(x);
            e = 0.1f * func_0020B480(x);
            for (j = 0; j < 16; j++) {
                n = j % 2;
                h = (f32)n / 2.0f;
                r = (f32)(n + 1) / 2.0f;
                t0 = h + e;
                t1 = r + e;
                for (k = 0; k < 16; k++) {
                    n = k % 2;
                    s = (f32)n / 2.0f;
                    h = (f32)(n + 1) / 2.0f;
                    s0 = s + f;
                    s1 = h + f;
                    tx.v[0].uv.st.s = s0;
                    tx.v[0].uv.st.t = t0;
                    tx.v[1].uv.st.s = s1;
                    tx.v[1].uv.st.t = t0;
                    tx.v[2].uv.st.s = s0;
                    tx.v[2].uv.st.t = t1;
                    tx.v[3].uv.st.s = s1;
                    tx.v[3].uv.st.t = t1;
                    if (func_00100BA0(&g->grid3[j][k], &g->grid3[j][k + 1], &g->grid3[j + 1][k],
                                      &g->grid3[j + 1][k + 1], m, &tx, &depth) == 1) {
                        func_002075F0(&tx, ot, (u32)depth);
                    }
                }
            }
        }
        g->t5++;
        if (g->t5 > 0x110) {
            g->on5 = 0;
        }
    }

    if (g->t == 0x5B) {
        ret = 1;
    } else {
        if (g->t > 0x65 && g->t < 0xCF) {
            ret = 6;
        }
        if (g->t == 0xCF) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x110) {
        ret = 8;
    }
    return ret;
}
