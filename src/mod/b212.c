#include "common.h"

/* shape b212:01E00080 (b212), 2415 insns, 1 copy */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b212_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b212_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b212_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b212_01E00080;

typedef struct {
    Reg_b212_01E00080 a;
    Reg_b212_01E00080 b;
} Tx_b212_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b212_01E00080 c;
    Uv_b212_01E00080 uv0;
    Xyz_b212_01E00080 p0;
    Uv_b212_01E00080 uv1;
    Xyz_b212_01E00080 p1;
    u64 pad38;
    Tx_b212_01E00080 tx;
    u64 pad50;
} Spr_b212_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b212_01E00080 c;
        Xyz_b212_01E00080 p;
    } v[4];
    u64 tail;
} Strip_b212_01E00080;

typedef struct {
    Rgbaq_b212_01E00080 c;
    f32 s, t;
    Xyz_b212_01E00080 p;
} Sv_b212_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Sv_b212_01E00080 v[4];
    u64 pad70;
    Tx_b212_01E00080 tx;
    u64 pad88;
} Quad_b212_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b212_01E00080;

typedef struct {
    u8 c[4];
} Col_b212_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f c;
} Rim_b212_01E00080;

typedef struct {
    Vec4f v[4];
} Leaf_b212_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[24];
    Vec4f pos[24];
} Burst_b212_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    s32 ang[4];
    u8 pad1C[4];
    Vec4f v[4];
} Spark_b212_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn;
    Vec4f jp;
    Vec4f tgt;
    u8 on1;
    u8 pad41[3];
    s32 t1;
    u8 pad48[8];
    Rim_b212_01E00080 rim[33];
    Leaf_b212_01E00080 leaf[96];
    u8 c[128];
    Vec4f v[128];
    Vec4f cir[17];
    Vec4f grid[21][17];
    Vec4f grid2[21][17];
    Vec4f ctr[1][21];
    u8 on2;
    u8 pad5601[3];
    s32 t2;
    u8 pad5608[8];
    Vec4f base[1];
    Burst_b212_01E00080 burst[8];
    Spark_b212_01E00080 spark[32];
} Scene_b212_01E00080;

static s32 func_01E00080_b212(s32 arg0, s32 code) {
    Scene_b212_01E00080 *g = (Scene_b212_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
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
    extern Col_b212_01E00080 D_01E02680_b212;
    extern Col_b212_01E00080 D_01E02688_b212;
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 a;
    s32 q;
    s32 p;
    u8 alpha;
    f32 f;
    f32 h;
    f32 r;
    f32 s;
    f32 w;
    f32 fade;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Mtx_b212_01E00080 m4;
    Vec4f v;
    Spr_b212_01E00080 spr __attribute__((aligned(8)));
    Strip_b212_01E00080 qd __attribute__((aligned(8)));
    Quad_b212_01E00080 pk __attribute__((aligned(8)));
    f32 depth;
    Col_b212_01E00080 col0;
    Col_b212_01E00080 col1;

    ret = 0;
    ot = func_00207500();
    col0 = D_01E02680_b212;
    col1 = D_01E02688_b212;
    if (code >= 0) {
        func_00195108(g, 0x6F20);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn = func_001F5560(g->unitA, 0x4D, 1);
        func_001F53C0(1, g->unitB, &g->tgt);
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            s = func_0020B550((i << 16) >> 5);
            h = func_0020B480((i << 16) >> 5);
            g->rim[i].a.x = 6.5f * s;
            g->rim[i].a.y = 6.5f * h;
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 10.8f * s;
            g->rim[i].b.y = 10.8f * h;
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
            g->rim[i].c.x = 11.0f * s;
            g->rim[i].c.y = 11.0f * h;
            g->rim[i].c.z = 0.0f;
            g->rim[i].c.w = 1.0f;
        }
        for (i = 0; i < 96; i++) {
            s = 0.1f + 0.9f * (i + 1) / 96.0f;
            r = 15.0f * s;
            (void)r;
            cn[0].x = 0.0f;
            cn[0].y = -s;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = s;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = 0.0f;
            cn[2].y = -s;
            cn[2].z = r;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = s;
            cn[3].z = r;
            cn[3].w = 1.0f;
            func_00101080(&v, 1.0f);
            func_00100E40(&m4, &v);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            for (k = 0; k < 4; k++) {
                func_001878E0(&g->leaf[i].v[k], &m4, &cn[k]);
            }
        }
        for (i = 0; i < 128; i++) {
            g->c[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v[i], 0.4f);
        }
        g->on2 = 0;
        g->t2 = 0;
        for (i = 0; i < 8; i++) {
            g->burst[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->spark[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    if (g->t == 0x3C) {
        func_001F5620(g->unitA, g->jn, &g->jp);
    }

    if (g->t == 0x3C) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        ((Spr_b212_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b212_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b212_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b212_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b212_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 64;
        y = 0;
        ((Uv_b212_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b212_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b212_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b212_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        r = 30.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        f = (f32)(16 - g->t1) / 16.0f;
        alpha = (u32)(255.0f * f);
        spr.c.r = 0x64;
        spr.c.g = 0x78;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Strip_b212_01E00080 *)(s32)&qd)->flags = 0x14;
        ((Strip_b212_01E00080 *)(s32)&qd)->size = 8;
        ((Strip_b212_01E00080 *)(s32)&qd)->regs = 0x41414141;
        ((Strip_b212_01E00080 *)(s32)&qd)->pad4 = 0;
        func_002086D0(&qd, func_00208D00(1));
        alpha = (u32)(255.0f * f);
        (void)alpha;
        qd.v[0].c.r = 0xA;
        qd.v[0].c.g = 0x50;
        qd.v[0].c.b = 0xFF;
        qd.v[0].c.a = alpha;
        qd.v[0].c.q = 1.0f;
        qd.v[1].c = qd.v[0].c;
        qd.v[2].c.r = 0x18;
        qd.v[2].c.g = 0x20;
        qd.v[2].c.b = 0xFF;
        qd.v[2].c.a = 0;
        qd.v[2].c.q = 1.0f;
        qd.v[3].c = qd.v[2].c;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp);
        s = 0.3f + 0.7f * func_00100D50(g->t1, 16, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].a, &g->rim[i + 1].a, m, &qd, &depth) == 1) {
                qd.v[0].p.z = 0xFFFFF8;
                qd.v[1].p.z = qd.v[0].p.z;
                qd.v[2].p.z = qd.v[0].p.z;
                qd.v[3].p.z = qd.v[0].p.z;
                func_002075F0(&qd, ot, 0);
            }
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].c, &g->rim[i + 1].c, m, &qd, &depth) == 1) {
                qd.v[0].p.z = 0xFFFFF8;
                qd.v[1].p.z = qd.v[0].p.z;
                qd.v[2].p.z = qd.v[0].p.z;
                qd.v[3].p.z = qd.v[0].p.z;
                func_002075F0(&qd, ot, 0);
            }
        }
        ((Quad_b212_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b212_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b212_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b212_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)(96.0f * f);
        (void)alpha;
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0xD8;
        pk.v[0].c.b = 0xC4;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0x80;
        pk.v[2].c.g = 0x64;
        pk.v[2].c.b = 0x5A;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jp);
        func_0020BC00(m, m2);
        for (i = 0; i < 96; i++) {
            pk.v[0].s = 0.5f;
            pk.v[0].t = 0.25f;
            pk.v[1].s = 0.75f;
            pk.v[1].t = 0.25f;
            pk.v[2].s = 0.5f;
            pk.v[2].t = 0.25f;
            pk.v[3].s = 0.75f;
            pk.v[3].t = 0.25f;
            if (func_00100BA0(&g->leaf[i].v[0], &g->leaf[i].v[1], &g->leaf[i].v[2], &g->leaf[i].v[3], m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        ((Spr_b212_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b212_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b212_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b212_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b212_01E00080 *)(s32)&spr)->flags |= 0x800;
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
        alpha = (u32)(128.0f * f);
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0xC8;
        spr.c.b = 0xBB;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jp);
        func_0020BC00(m, m2);
        s = 0.8f + 0.2f * func_00100D50(g->t1, 16, 1);
        for (k = 0; k < 128; k++) {
            x = g->c[k] % 4 * 32;
            y = (g->c[k] >> 2) * 32;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v[k], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t1++;
        if (g->t1 > 16) {
            g->on1 = 0;
        }
    }

    if (g->t % 12 == 0 && g->t > 0 && g->t < 0x4E) {
        func_001F71A0(g->unitA, 0x20, 1, &col0, &col1, 0);
    }

    if (g->t == 0x4B) {
        g->on2 = 1;
        g->t2 = 0;
        for (x = 0; x < 1; x++) {
            a = ((x << 16) + 0xE38) & 0xFFFF;
            g->base[x].x = 0.0f * func_0020B550(a);
            g->base[x].y = 0.0f;
            g->base[x].z = 0.0f * func_0020B480(a);
            g->base[x].w = 1.0f;
            func_00187B00(&g->base[x], &g->base[x], &g->tgt);
            g->base[x].y = 5.0f;
        }
    }
    t0 = (f32)func_00101050(0x82 - g->t2, 0, 0x20) / 32.0f;
    if (g->on2 == 1) {
        for (x = 0; x < 1; x++) {
            for (a = 0; a < 21; a++) {
                k = (g->t2 * 0x71C + (x * 0x3039 + (a * 0x10000) / 20)) & 0xFFFF;
                r = 0.0f;
                g->ctr[x][a].x = r * func_0020B550(k);
                g->ctr[x][a].y = 0.0f;
                g->ctr[x][a].z = r * func_0020B480(k);
                g->ctr[x][a].w = 1.0f;
            }
        }
        w = 100.0f * func_00100D50(func_00101050(g->t2, 0, 0x10), 0x10, 1);
        ((Quad_b212_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b212_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b212_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b212_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)(96.0f * t0);
        r = 45.0f + 0.0f * g->t2;
        for (y = 0; y < 17; y++) {
            g->cir[y].x = r * func_0020B550((y << 16) >> 4);
            g->cir[y].y = 0.0f;
            g->cir[y].z = r * func_0020B480((y << 16) >> 4);
            g->cir[y].w = 1.0f;
        }
        for (k = 0; k < 1; k++) {
            func_0020EB40(m);
            func_0020C940(m2, NULL, NULL, &g->base[k]);
            func_0020BC00(m, m2);
            for (x = 0; x < 21; x++) {
                h = w * x / 20.0f;
                r = 0.5f + 0.5f * (1.0f - func_00100D50(x, 20, 1));
                for (j = 0; j < 17; j++) {
                    func_00187B48(&g->grid[x][j], &g->cir[j], r);
                    g->grid[x][j].y = h;
                    func_00187B00(&g->grid[x][j], &g->grid[x][j], &g->ctr[k][x]);
                }
            }
            fade = (f32)k - (f32)(g->t2 % 14) / 14.0f;
            for (a = 0; a < 20; a++) {
                if (a == 0) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0xB2;
                    pk.v[0].c.b = 0xC8;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0xB2;
                    pk.v[2].c.b = 0xC8;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (a == 19) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0xB2;
                    pk.v[0].c.b = 0xC8;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0xB2;
                    pk.v[2].c.b = 0xC8;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0xB2;
                    pk.v[0].c.b = 0xC8;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                t1 = 2.0f * a / 20.0f + fade;
                f = 2.0f * (a + 1) / 20.0f + fade;
                for (i = 0; i < 16; i++) {
                    s0 = 2.0f * i / 16.0f;
                    s1 = 2.0f * (i + 1) / 16.0f;
                    pk.v[0].s = s0;
                    pk.v[0].t = t1;
                    pk.v[1].s = s1;
                    pk.v[1].t = t1;
                    pk.v[2].s = s0;
                    pk.v[2].t = f;
                    pk.v[3].s = s1;
                    pk.v[3].t = f;
                    if (func_00100BA0(&g->grid[a][i], &g->grid[a][i + 1], &g->grid[a + 1][i], &g->grid[a + 1][i + 1], m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Quad_b212_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b212_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b212_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b212_01E00080 *)(s32)&pk)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &pk.tx.a, &pk.tx.b);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b212_01E00080 *)(s32)&pk)->flags |= 0x800;
        alpha = (u32)(128.0f * t0);
        r = 44.0f + 0.0f * g->t2;
        for (a = 0; a < 17; a++) {
            g->cir[a].x = r * func_0020B550((a << 16) >> 4);
            g->cir[a].y = 0.0f;
            g->cir[a].z = r * func_0020B480((a << 16) >> 4);
            g->cir[a].w = 1.0f;
        }
        for (k = 0; k < 1; k++) {
            func_0020EB40(m);
            func_0020C940(m2, NULL, NULL, &g->base[k]);
            func_0020BC00(m, m2);
            for (a = 0; a < 21; a++) {
                r = w * a / 20.0f;
                h = 0.5f + 0.5f * (1.0f - func_00100D50(a, 20, 1));
                func_0020BBB0(&m4);
                func_00100E00(&m4, (s32)(910.0f * func_0020B550(((a << 16) / 20 + ((g->t2 + k * 5) % 96 << 16) / 96) & 0xFFFF)), 1);
                for (y = 0; y < 17; y++) {
                    func_00187B48(&g->grid[a][y], &g->cir[y], h);
                    g->grid[a][y].y = r;
                    func_00187B00(&g->grid[a][y], &g->grid[a][y], &g->ctr[k][a]);
                    func_001878E0(&g->grid2[a][y], &m4, &g->grid[a][y]);
                    g->grid2[a][y].y = r + 0.15f * (w / 20.0f) * func_0020B550(((y << 16) >> 4) + ((g->t2 + k * 5) % 48 << 16) / 48 & 0xFFFF);
                    func_00187B00(&g->grid2[a][y], &g->grid2[a][y], &g->ctr[k][a]);
                }
            }
            for (x = 0; x < 20; x++) {
                if (x == 0) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x8A;
                    pk.v[0].c.b = 0xAA;
                    pk.v[0].c.a = 0;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x8A;
                    pk.v[2].c.b = 0xAA;
                    pk.v[2].c.a = alpha;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else if (x == 19) {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x8A;
                    pk.v[0].c.b = 0xAA;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x8A;
                    pk.v[2].c.b = 0xAA;
                    pk.v[2].c.a = 0;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                } else {
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x8A;
                    pk.v[0].c.b = 0xAA;
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[2].c = pk.v[0].c;
                    pk.v[3].c = pk.v[0].c;
                }
                for (i = 0; i < 16; i++) {
                    if (func_00100BA0(&g->grid2[x][i], &g->grid2[x][i + 1], &g->grid2[x + 1][i], &g->grid2[x + 1][i + 1], m, &pk, &depth) == 1) {
                        func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                        func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                        func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                        func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid[x][i], &g->grid[x][i + 1], &g->grid[x + 1][i], &g->grid[x + 1][i + 1], m, &pk, &depth) == 1 && func_00101430(&pk.v[0].p, &pk.v[1].p, &pk.v[2].p) == 1) {
                            func_002075F0(&pk, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x82) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x4B && g->t < 0xCD) {
        n = g->t % 8;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        k = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        for (j = 0; j < 24; j++) {
            g->burst[n].c[j] = (func_0019A5C8() >> 23) % 8;
            q = (k + (j << 16) / 24) & 0xFFFF;
            g->burst[n].pos[j].x = 46.0f * func_0020B550(q);
            g->burst[n].pos[j].y = 0.0f;
            g->burst[n].pos[j].z = 46.0f * func_0020B480(q);
            g->burst[n].pos[j].w = 1.0f;
        }
    }

    ((Spr_b212_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b212_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b212_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b212_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b212_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (k = 0; k < 8; k++) {
        if (g->burst[k].on == 0) {
            continue;
        }
        h = 13.0f * (0.2f + 0.8f * func_00100D50(g->burst[k].t, 8, 1));
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
        alpha = (u32)(t0 * (100.0f * func_0020B480((g->burst[k].t << 14) >> 3)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (n = 0; n < 24; n++) {
            x = g->burst[k].c[n] % 4 * 32;
            y = (g->burst[k].c[n] >> 2) * 32;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B00(&v, &g->burst[k].pos[n], &g->tgt);
            v.y = 5.0f;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            if (n % 2 == 0) {
                func_00187B48((void *)&v, &g->burst[k].pos[n], 0.5f);
                func_00187B00(&v, &v, &g->tgt);
                v.y = w;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[k].t++;
        if (g->burst[k].t > 8) {
            g->burst[k].on = 0;
        }
    }

    if (g->t > 0x4B && g->t < 0xCD) {
        n = g->t % 32;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (j = 0; j < 4; j++) {
            g->spark[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->spark[n].ang[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->spark[n].v[j], 0.9f);
        }
    }

    ((Spr_b212_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b212_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b212_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b212_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b212_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 4.0f;
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
        alpha = (u32)(t0 * (164.0f * func_0020B550((g->spark[i].t << 15) >> 5)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = g->spark[i].t / 32.0f;
        for (q = 0; q < 4; q++) {
            s = func_0020B550((g->spark[i].ang[q] + g->spark[i].t * 0x309) & 0xFFFF);
            x = g->spark[i].c[q] % 4 * 32;
            y = (g->spark[i].c[q] >> 2) * 32;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b212_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->spark[i].v[q], s);
            v.x += g->tgt.x;
            v.y += 5.0f + 100.0f * f;
            v.z += g->tgt.z;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x41) {
        ret = 1;
    } else {
        if (g->t > 0x4B && g->t < 0xCC) {
            ret = 6;
        }
        if (g->t == 0xCC) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xCD) {
        ret = 8;
    }
    return ret;
}
