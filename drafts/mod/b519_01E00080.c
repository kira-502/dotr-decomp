#include "common.h"

/* shape b519:01E00080 (b519), 2456 insns, 1 copy: b519 scene manager (b470:01E00080's twin, draft): lifted joint
   midpoint and a target-facing matrix for 16 swirls; returns 1 / 6 / 2 / 8 at 0x5D / 0x68..0xDE / 0xDF / >0x10F */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b519_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b519_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b519_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b519_01E00080 c;
    Uv_b519_01E00080 uv0;
    Xyz_b519_01E00080 p0;
    Uv_b519_01E00080 uv1;
    Xyz_b519_01E00080 p1;
    u8 tail[0x20];
} Spr_b519_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b519_01E00080 c0;
    Xyz_b519_01E00080 p0;
    Rgbaq_b519_01E00080 c1;
    Xyz_b519_01E00080 p1;
    Rgbaq_b519_01E00080 c2;
    Xyz_b519_01E00080 p2;
    u8 tail[8];
} Ln_b519_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b519_01E00080 c;
        Xyz_b519_01E00080 p;
    } v[4];
    u64 tail;
} Quad_b519_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[24];
    f32 f[24];
    u8 padC8[8];
    Vec4f p;
    Vec4f v[24];
} Rush_b519_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[16];
    u8 pad28[8];
    Vec4f p;
    Vec4f v[16];
} Cloud_b519_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f v[16];
} Puff_b519_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    s32 a;
} Swirl_b519_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    s32 bone[2];
    Vec4f bp[2];
    Vec4f mid;
    s32 bone2;
    u8 pad54[0xC];
    Vec4f bp2;
    Vec4f tgt;
    Rush_b519_01E00080 rush[48];
    Cloud_b519_01E00080 cloud[16];
    u8 on2;
    u8 pad8681[3];
    s32 t2;
    u8 pad8688[8];
    Vec4f ring[33][3];
    u8 c2[128];
    Vec4f p2;
    Vec4f v2[128];
    Puff_b519_01E00080 puff[32];
    u8 on4;
    u8 padB951[3];
    s32 t4;
    u8 padB958[8];
    Vec4f ring2[33];
    Swirl_b519_01E00080 sw[16];
} Scene_b519_01E00080;

static s32 func_01E00080_b519(s32 arg0, s32 code) {
    Scene_b519_01E00080 *g = (Scene_b519_01E00080 *)arg0;
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
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern f32 func_0020B480(s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_001F6D00(s32);
    extern void func_00100E40(void *, void *);
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 n;
    s32 q;
    s32 x;
    s32 y;
    u8 alpha;
    f32 f;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    f32 m4[4][4];
    Vec4f v;
    Spr_b519_01E00080 spr __attribute__((aligned(8)));
    Ln_b519_01E00080 ln __attribute__((aligned(8)));
    Quad_b519_01E00080 qd __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xBD30);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->bone[0] = func_001F5560(g->unitA, 0x3A, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x3F, 0);
        g->bone2 = func_001F5560(g->unitA, 0x3C, 0);
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 48; i++) {
            g->rush[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->cloud[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 33; i++) {
            v.x = func_0020B550((i << 16) >> 5);
            v.y = func_0020B480((i << 16) >> 5);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->ring[i][0], &v, 11.5f);
            func_00187B48((void *)&g->ring[i][1], &v, 11.8f);
            func_00187B48((void *)&g->ring[i][2], &v, 12.0f);
        }
        for (i = 0; i < 32; i++) {
            g->puff[i].on = 0;
        }
        g->on4 = 0;
        for (i = 0; i < 33; i++) {
            g->ring2[i].x = 12.0f * func_0020B550((i << 16) >> 5);
            g->ring2[i].y = 12.0f * func_0020B480((i << 16) >> 5);
            g->ring2[i].z = 0.0f;
            g->ring2[i].w = 1.0f;
        }
        for (i = 0; i < 16; i++) {
            g->sw[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->bone[i], &g->bp[i]);
    }
    func_00187B00(&g->mid, &g->bp[0], &g->bp[1]);
    func_00187B48((void *)&g->mid, &g->mid, 0.5f);
    g->mid.y += 1.0f;
    g->mid.z += -2.0f * g->obj;
    func_001F5620(g->unitA, g->bone2, &g->bp2);
    func_00187B18(&v, &g->tgt, &g->mid);
    func_00100E40(m4, &v);

    if (g->t > 0x46 && g->t < 0xDF) {
        n = g->t % 48;
        (void)n;
        g->rush[n].on = 1;
        g->rush[n].t = 0;
        g->rush[n].p = g->mid;
        g->rush[n].p.z += 8.0f * g->obj;
        for (i = 0; i < 24; i++) {
            g->rush[n].c[i] = (func_0019A5C8() >> 23) % 8;
            g->rush[n].f[i] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->rush[n].v[i], 0.7f);
            func_00187B00(&g->rush[n].v[i], &g->rush[n].v[i], &g->tgt);
            func_00187B18(&g->rush[n].v[i], &g->rush[n].v[i], &g->rush[n].p);
        }
    }

    ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xDF - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->rush[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_00101020((f32)g->rush[i].t, 4.0f) * func_00100FF0((f32)g->rush[i].t, 48.0f, 32.0f)));
        spr.c.r = 0xFF;
        spr.c.g = 0x54;
        spr.c.b = 0x38;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 12.0f * (0.5f + 0.5f * g->rush[i].t / 48.0f);
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
        s = 1.5f * g->rush[i].t / 48.0f;
        for (q = 0; q < 24; q++) {
            x = g->rush[i].c[q] % 4 * 32;
            y = (g->rush[i].c[q] >> 2) * 32;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&out[0], &cn[0], g->rush[i].f[q]);
            func_00187B48(&out[1], &cn[1], g->rush[i].f[q]);
            func_00187B48(&v, &g->rush[i].v[q], s);
            func_00187B00(&v, &v, &g->rush[i].p);
            func_00187B00(&out[0], &out[0], &v);
            func_00187B00(&out[1], &out[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->rush[i].t++;
        if (g->rush[i].t > 48) {
            g->rush[i].on = 0;
        }
    }

    if (g->t > 0x46 && g->t < 0xBF) {
        n = g->t % 16;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        g->cloud[n].p = g->mid;
        for (i = 0; i < 16; i++) {
            g->cloud[n].c[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->cloud[n].v[i], 0.7f);
        }
    }

    ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        r = 4.0f * (0.2f + 0.8f * (16 - g->cloud[i].t) / 16.0f);
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
        alpha = (u32)(255.0f * func_0020B550((g->cloud[i].t << 15) >> 4));
        spr.c.r = 0xFF;
        spr.c.g = 0x68;
        spr.c.b = 0x4C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->cloud[i].t, 16, 1);
        for (q = 0; q < 16; q++) {
            func_00187B48(&v, &g->cloud[i].v[q], s);
            func_00187B00(&v, &v, &g->cloud[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->cloud[i].c[q] % 4 * 32;
            y = (g->cloud[i].c[q] >> 2) * 32;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->cloud[i].t++;
        if (g->cloud[i].t > 16) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t == 0xC) {
        g->on2 = 1;
        g->t2 = 0;
        g->p2 = g->bp2;
        for (j = 0; j < 128; j++) {
            g->c2[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v2[j], 0.8f);
        }
    }
    if (g->on2 == 1) {
        ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 96;
        y = 0;
        ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->p2);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0x37;
        spr.c.g = 0x50;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f;
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
        ((Quad_b519_01E00080 *)(s32)&qd)->flags = 0x14;
        ((Quad_b519_01E00080 *)(s32)&qd)->size = 8;
        ((Quad_b519_01E00080 *)(s32)&qd)->regs = 0x41414141;
        ((Quad_b519_01E00080 *)(s32)&qd)->pad4 = 0;
        func_002086D0(&qd, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->p2);
        s = 0.5f + 0.5f * func_00100D50(g->t2, 32, 2);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        qd.v[0].c.r = 0x3C;
        qd.v[0].c.g = 0x50;
        qd.v[0].c.b = 0xFF;
        qd.v[0].c.a = alpha;
        qd.v[0].c.q = 1.0f;
        qd.v[1].c = qd.v[0].c;
        qd.v[2].c.r = 0x20;
        qd.v[2].c.g = 0x24;
        qd.v[2].c.b = 0x80;
        qd.v[2].c.a = 0;
        qd.v[2].c.q = 1.0f;
        qd.v[3].c = qd.v[2].c;
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->ring[i][1], &g->ring[i + 1][1], &g->ring[i][0], &g->ring[i + 1][0], m, &qd,
                              &depth) == 1) {
                qd.v[0].p.z = 0xFFFFF8;
                qd.v[1].p.z = qd.v[0].p.z;
                qd.v[2].p.z = qd.v[0].p.z;
                qd.v[3].p.z = qd.v[0].p.z;
                func_002075F0(&qd, ot, 0);
            }
            if (func_00100BA0(&g->ring[i][1], &g->ring[i + 1][1], &g->ring[i][2], &g->ring[i + 1][2], m, &qd,
                              &depth) == 1) {
                qd.v[0].p.z = 0xFFFFF8;
                qd.v[1].p.z = qd.v[0].p.z;
                qd.v[2].p.z = qd.v[0].p.z;
                qd.v[3].p.z = qd.v[0].p.z;
                func_002075F0(&qd, ot, 0);
            }
        }
        ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0x20;
        spr.c.g = 0xC8;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.8f;
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
        s = 0.1f + 0.9f * func_00100D50(g->t2, 32, 2);
        for (j = 0; j < 128; j++) {
            x = g->c2[j] % 4 * 32;
            y = (g->c2[j] >> 2) * 32;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v2[j], s);
            func_00187B00(&v, &v, &g->p2);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 32) {
            g->on2 = 0;
        }
    }

    if (g->t > 0xC && g->t < 0x1E) {
        n = g->t % 32;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (j = 0; j < 16; j++) {
            g->puff[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->puff[n].v[j], 1.0f);
            func_00187B00(&g->puff[n].v[j], &g->puff[n].v[j], &g->mid);
        }
    }

    ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        r = 2.0f * (0.2f + 0.8f * g->puff[i].t / 32.0f);
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
        alpha = (u32)(255.0f * func_0020B550((g->puff[i].t << 14) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0x38;
        spr.c.b = 0x26;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(32 - g->puff[i].t, 32, 1);
        for (q = 0; q < 16; q++) {
            func_00187B18(&v, &g->puff[i].v[q], &g->mid);
            func_00187B48(&v, &v, s);
            func_00187B00(&v, &v, &g->mid);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->puff[i].c[q] % 4 * 32;
            y = (g->puff[i].c[q] >> 2) * 32;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 32) {
            g->puff[i].on = 0;
        }
    }

    if (g->t == 8) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 96;
        y = 0;
        ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->mid);
        func_0020BC00(m, m2);
        f = (f32)func_00101050(0xD7 - g->t4, 0, 64) * (f32)func_00101050(g->t4, 0, 64) / 4096.0f;
        f = (0.8f + 0.2f * (g->t4 % 2)) * f;
        alpha = (u32)(255.0f * f);
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0xA8;
        spr.c.b = 0x94;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 12.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            if (g->t < 0x9C) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            } else {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        ((Ln_b519_01E00080 *)(s32)&ln)->flags = 0x13;
        ((Ln_b519_01E00080 *)(s32)&ln)->size = 6;
        ((Ln_b519_01E00080 *)(s32)&ln)->regs = 0x414141;
        ((Ln_b519_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        alpha = (u32)(128.0f * f);
        (void)alpha;
        ln.c0.r = 0xFF;
        ln.c0.g = 0xA;
        ln.c0.b = 0xA;
        ln.c0.a = alpha;
        ln.c0.q = 1.0f;
        ln.c1.r = 0xFF;
        ln.c1.g = 0;
        ln.c1.b = 0;
        ln.c1.a = 0;
        ln.c1.q = 1.0f;
        ln.c2 = ln.c1;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 32; i++) {
            if (func_00100B00(&v, &g->ring2[i], &g->ring2[i + 1], m, &ln, &depth) == 1) {
                if (g->t < 0x9C) {
                    ln.p0.z = 0xFFFFF8;
                    ln.p1.z = ln.p0.z;
                    ln.p2.z = ln.p0.z;
                    func_002075F0(&ln, ot, 0);
                } else {
                    func_002075F0(&ln, ot, (u32)depth);
                }
            }
        }
        g->t4++;
        if (g->t4 > 0xD7) {
            g->on4 = 0;
        }
    }

    if (g->t > 0x67 && g->t < 0xDF) {
        n = g->t % 16;
        (void)n;
        g->sw[n].on = 1;
        g->sw[n].t = 0;
        g->sw[n].a = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        for (j = 0; j < 16; j++) {
            g->sw[n].c[j] = (func_0019A5C8() >> 23) % 8;
        }
    }

    ((Spr_b519_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b519_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b519_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b519_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b519_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xDF - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 16; i++) {
        if (g->sw[i].on == 0) {
            continue;
        }
        r = 23.0f * (0.5f + 0.5f * (16 - g->sw[i].t) / 16.0f);
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
        alpha = (u32)(f * (200.0f * func_0020B480((g->sw[i].t << 14) >> 4)));
        spr.c.r = 0xFF;
        spr.c.g = 0x5E;
        spr.c.b = 0x36;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.1f + 0.9f * func_00100D50(g->sw[i].t, 16, 1);
        s = 80.0f * (g->sw[i].t / 16.0f);
        r = 60.0f * r;
        for (q = 0; q < 16; q++) {
            n = (g->sw[i].a + ((q << 16) >> 4)) & 0xFFFF;
            v.x = r * func_0020B550(n);
            v.y = r * func_0020B480(n);
            v.z = s;
            v.w = 1.0f;
            func_001878E0(&v, m4, &v);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->sw[i].c[q] % 4 * 32;
            y = (g->sw[i].c[q] >> 2) * 32;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b519_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->sw[i].t++;
        if (g->sw[i].t > 16) {
            g->sw[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x10F - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));

    if (g->t == 0x5D) {
        ret = 1;
    } else {
        if (g->t > 0x67 && g->t < 0xDF) {
            ret = 6;
        }
        if (g->t == 0xDF) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x10F) {
        ret = 8;
    }
    return ret;
}
