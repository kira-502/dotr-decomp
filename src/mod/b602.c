#include "common.h"

/* shape b602:01E00080 (b602), 2851 insns, 1 copy: scene effect: rush streaks, smoke clouds, sparks, a three-band
   ring and motes */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b602_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b602_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b602_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b602_01E00080 c;
    Uv_b602_01E00080 uv0;
    Xyz_b602_01E00080 p0;
    Uv_b602_01E00080 uv1;
    Xyz_b602_01E00080 p1;
    u8 tail[0x20];
} Spr_b602_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b602_01E00080 c;
    struct {
        Uv_b602_01E00080 uv;
        Xyz_b602_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Spr4_b602_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b602_01E00080 c;
        Xyz_b602_01E00080 p;
    } v[4];
    u64 tail;
} Quad_b602_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b602_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[4];
    Vec4f p;
    Vec4f v[4];
} Puff_b602_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[8];
    f32 f[8];
    u8 pad48[8];
    Vec4f p;
    Vec4f v[8];
    s32 n;
    u8 padE4[0xC];
} Rush_b602_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f v[16];
    s32 n;
    u8 pad124[0xC];
} Cloud_b602_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 sc;
    s32 ang;
    Vec4f p;
} Mote_b602_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 bone[2];
    u8 pad24[0xC];
    Vec4f bp[2];
    Vec4f mid;
    s32 bone2;
    u8 pad64[0xC];
    Vec4f bp2;
    Vec4f tgt;
    Rush_b602_01E00080 rush[48];
    Cloud_b602_01E00080 cloud[24];
    Puff_b602_01E00080 spark[24];
    u8 on2;
    u8 pad5311[3];
    s32 t2;
    u8 pad5318[8];
    Vec4f ring[33][3];
    u8 c2[128];
    Vec4f p2;
    Vec4f v2[128];
    Mote_b602_01E00080 mote[48][8];
    Mote_b602_01E00080 mote2[24][8];
} Scene_b602_01E00080;

static s32 func_01E00080_b602(s32 arg0, s32 code) {
    Scene_b602_01E00080 *g = (Scene_b602_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
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
    extern void func_00100E00(void *, s32, s32);
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 n;
    s32 k;
    s32 x;
    s32 y;
    u8 alpha;
    u8 a1;
    u8 a2;
    f32 f;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b602_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b602_01E00080 m4;
    Vec4f v;
    Spr_b602_01E00080 spr __attribute__((aligned(8)));
    Spr4_b602_01E00080 sq __attribute__((aligned(8)));
    Quad_b602_01E00080 qd __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA9E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->bone[0] = func_001F5560(g->unitA, 0x15, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x17, 0);
        g->bone2 = func_001F5560(g->unitA, 0x13, 0);
        func_001F53C0(1, g->unitB, &g->tgt);
        for (i = 0; i < 48; i++) {
            g->rush[i].on = 0;
            g->rush[i].n = 0;
        }
        for (i = 0; i < 24; i++) {
            g->cloud[i].on = 0;
            g->cloud[i].n = 0;
        }
        for (i = 0; i < 24; i++) {
            g->spark[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 33; i++) {
            v.x = func_0020B550((i << 16) >> 5);
            v.y = func_0020B480((i << 16) >> 5);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->ring[i][0], &v, 4.0f);
            func_00187B48((void *)&g->ring[i][1], &v, 4.7f);
            func_00187B48((void *)&g->ring[i][2], &v, 5.0f);
        }
        for (i = 0; i < 48; i++) {
            for (j = 0; j < 8; j++) {
                g->mote[i][j].on = 0;
            }
        }
        for (i = 0; i < 24; i++) {
            for (j = 0; j < 8; j++) {
                g->mote2[i][j].on = 0;
            }
        }
        return 0;
    }
    func_00205CA0(&m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->bone[i], &g->bp[i]);
    }
    func_00187B00(&g->mid, &g->bp[0], &g->bp[1]);
    func_00187B48((void *)&g->mid, &g->mid, 0.5f);
    func_001F5620(g->unitA, g->bone2, &g->bp2);

    if (g->t > 0x48 && g->t < 0xE5) {
        n = g->t % 48;
        (void)n;
        g->rush[n].on = 1;
        g->rush[n].t = 0;
        g->rush[n].p = g->mid;
        g->rush[n].p.z += 4.0f * g->obj;
        for (j = 0; j < 8; j++) {
            g->rush[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->rush[n].f[j] = 0.8f + 0.2f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->rush[n].v[j], 1.0f);
            func_00187B00(&g->rush[n].v[j], &g->rush[n].v[j], &g->tgt);
            func_00187B18(&g->rush[n].v[j], &g->rush[n].v[j], &g->rush[n].p);
        }
    }

    ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xE5 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->rush[i].on == 0) {
            continue;
        }
        a1 = (u32)(f * (80.0f * func_00101020((f32)g->rush[i].t, 2.0f) * func_00100FF0((f32)g->rush[i].t, 48.0f, 32.0f)));
        a2 = (u32)(f * (32.0f * func_00101020((f32)g->rush[i].t, 2.0f) * func_00100FF0((f32)g->rush[i].t, 48.0f, 32.0f)));
        r = 12.0f * (0.5f + 0.5f * g->rush[i].t / 48.0f);
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
        s = 1.5f * g->rush[i].t / 48.0f;
        for (n = 0; n < 8; n++) {
            if (n % 2 == 0) {
                func_002086D0(&spr, func_00208D00(0));
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0xC8;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0x40;
                spr.c.a = a1;
                spr.c.q = 1.0f;
            }
            x = g->rush[i].c[n] % 4 * 32;
            y = (g->rush[i].c[n] >> 2) * 32;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&out[0], &cn[0], g->rush[i].f[n]);
            func_00187B48(&out[1], &cn[1], g->rush[i].f[n]);
            func_00187B48(&v, &g->rush[i].v[n], s);
            func_00187B00(&v, &v, &g->rush[i].p);
            func_00187B00(&out[0], &out[0], &v);
            func_00187B00(&out[1], &out[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        if (g->rush[i].t % 4 == 0) {
            k = g->rush[i].n;
            g->rush[i].n++;
            if (g->rush[i].n >= 8) {
                g->rush[i].n = 0;
            }
            g->mote[i][k].on = 1;
            g->mote[i][k].t = 0;
            g->mote[i][k].sc = 0.3f + 0.7f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->mote[i][k].ang = ((func_0019A5C8() >> 23) % 8 << 16) >> 3;
            func_00101080(&g->mote[i][k].p, 0.5f);
            func_00187B00(&g->mote[i][k].p, &g->mote[i][k].p, &v);
        }
        g->rush[i].t++;
        if (g->rush[i].t > 48) {
            g->rush[i].on = 0;
        }
    }

    if (g->t > 0x64 && g->t < 0x12C) {
        n = g->t % 24;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        for (j = 0; j < 16; j++) {
            g->cloud[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->cloud[n].v[j], 1.3f);
        }
    }

    ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x64, 0, 32) * (f32)func_00101050(0x12C - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 24; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (64.0f * func_0020B550((g->cloud[i].t << 15) / 24)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x5A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * (24 - g->cloud[i].t) / 24.0f);
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
        s = g->cloud[i].t / 24.0f;
        h = 0.9f + 0.1f * (24 - g->cloud[i].t) / 24.0f;
        w = -25.0f + 80.0f * s;
        for (k = 0; k < 16; k++) {
            x = g->cloud[i].c[k] % 4 * 32;
            y = (g->cloud[i].c[k] >> 2) * 32;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v.x = g->cloud[i].v[k].x * h;
            v.y = w + g->cloud[i].v[k].y;
            v.z = g->cloud[i].v[k].z * h;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        if (g->cloud[i].t % 4 == 0) {
            k = g->cloud[i].n;
            g->cloud[i].n++;
            if (g->cloud[i].n >= 8) {
                g->cloud[i].n = 0;
            }
            g->mote2[i][k].on = 1;
            g->mote2[i][k].t = 0;
            g->mote2[i][k].sc = 0.1f + 0.9f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->mote2[i][k].ang = ((func_0019A5C8() >> 23) % 8 << 16) >> 3;
            func_00101080(&g->mote2[i][k].p, 0.1f);
            func_00187B00(&g->mote2[i][k].p, &g->mote2[i][k].p, &v);
        }
        g->cloud[i].t++;
        if (g->cloud[i].t > 24) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t > 0x48 && g->t < 0xE5) {
        n = g->t % 24;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].p = g->mid;
        for (j = 0; j < 4; j++) {
            g->spark[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[j], 0.5f);
        }
    }

    ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xE5 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 24; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 4.0f * (0.2f + 0.8f * (24 - g->spark[i].t) / 24.0f);
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
        alpha = (u32)(f * (128.0f * func_0020B480((g->spark[i].t << 14) / 24)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x40;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[i].t, 24, 1);
        for (k = 0; k < 4; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[k] % 4 * 32;
            y = (g->spark[i].c[k] >> 2) * 32;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 24) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x3C) {
        g->on2 = 1;
        g->t2 = 0;
        g->p2 = g->bp2;
        for (j = 0; j < 128; j++) {
            g->c2[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v2[j], 0.3f);
        }
    }
    if (g->on2 == 1) {
        ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 96;
        y = 0;
        ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_00187B60(m2, &m3, &g->p2);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0xC8;
        spr.c.b = 0xB4;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 6.0f;
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
        ((Quad_b602_01E00080 *)(s32)&qd)->flags = 0x14;
        ((Quad_b602_01E00080 *)(s32)&qd)->size = 8;
        ((Quad_b602_01E00080 *)(s32)&qd)->regs = 0x41414141;
        ((Quad_b602_01E00080 *)(s32)&qd)->pad4 = 0;
        func_002086D0(&qd, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, &m3, &g->p2);
        s = func_00100D50(g->t2, 32, 2);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        qd.v[0].c.r = 0xFF;
        qd.v[0].c.g = 0xC8;
        qd.v[0].c.b = 0xB4;
        qd.v[0].c.a = alpha;
        qd.v[0].c.q = 1.0f;
        qd.v[1].c = qd.v[0].c;
        qd.v[2].c.r = 0;
        qd.v[2].c.g = 0;
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
        ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0xC8;
        spr.c.b = 0xB4;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.5f;
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
        for (j = 0; j < 128; j++) {
            x = g->c2[j] % 4 * 32;
            y = (g->c2[j] >> 2) * 32;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    ((Spr4_b602_01E00080 *)(s32)&sq)->flags = 0x24;
    ((Spr4_b602_01E00080 *)(s32)&sq)->size = 9;
    ((Spr4_b602_01E00080 *)(s32)&sq)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr4_b602_01E00080 *)(s32)&sq)->pad4 = 0;
    ((Spr4_b602_01E00080 *)(s32)&sq)->flags |= 0x800;
    func_002086D0(&sq, func_00208D00(1));
    func_00208700(&sq, g->tex[2], 1);
    func_00208CB0(&sq, 5);
    x = 0;
    ((Uv_b602_01E00080 *)(s32)&sq.v[0].uv)->u = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[0].uv)->v = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[1].uv)->u = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[1].uv)->v = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[2].uv)->u = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[2].uv)->v = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[3].uv)->u = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[3].uv)->v = 0x200;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = 0x600;
    ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xE5 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        for (j = 0; j < 8; j++) {
            if (g->mote[i][j].on == 0) {
                continue;
            }
            r = 2.0f * g->mote[i][j].sc;
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
            m4 = m3;
            func_00100E00(&m4, g->mote[i][j].ang, 2);
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_001878E0(&cn[2], &m4, &cn[2]);
            func_001878E0(&cn[3], &m4, &cn[3]);
            alpha = (u32)((0.8f + 0.2f * (g->mote[i][j].t % 2)) * (f * (255.0f * func_0020B550((g->mote[i][j].t << 15) / 24))));
            sq.c.r = 0xFF;
            sq.c.g = 0xBE;
            sq.c.b = 0x96;
            sq.c.a = alpha;
            sq.c.q = 1.0f;
            v = g->mote[i][j].p;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], &v);
            func_00187B00(&out[2], &cn[2], (void *)&v);
            func_00187B00(&out[3], &cn[3], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &sq, &depth) == 1) {
                func_002075F0(&sq, ot, (u32)depth);
            }
            r = g->mote[i][j].sc;
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
            alpha = (u32)((0.8f + 0.2f * (g->mote[i][j].t % 2)) * (f * (255.0f * func_0020B550((g->mote[i][j].t << 15) / 24))));
            spr.c.r = 0xFF;
            spr.c.g = 0xBE;
            spr.c.b = 0x96;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            v = g->mote[i][j].p;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], &v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->mote[i][j].t++;
            if (g->mote[i][j].t > 24) {
                g->mote[i][j].on = 0;
            }
        }
    }

    ((Spr4_b602_01E00080 *)(s32)&sq)->flags = 0x24;
    ((Spr4_b602_01E00080 *)(s32)&sq)->size = 9;
    ((Spr4_b602_01E00080 *)(s32)&sq)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr4_b602_01E00080 *)(s32)&sq)->pad4 = 0;
    ((Spr4_b602_01E00080 *)(s32)&sq)->flags |= 0x800;
    func_002086D0(&sq, func_00208D00(1));
    func_00208700(&sq, g->tex[2], 1);
    func_00208CB0(&sq, 5);
    x = 0;
    ((Uv_b602_01E00080 *)(s32)&sq.v[0].uv)->u = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[0].uv)->v = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[1].uv)->u = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[1].uv)->v = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[2].uv)->u = x;
    ((Uv_b602_01E00080 *)(s32)&sq.v[2].uv)->v = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[3].uv)->u = 0x200;
    ((Uv_b602_01E00080 *)(s32)&sq.v[3].uv)->v = 0x200;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b602_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b602_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b602_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b602_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b602_01E00080 *)(s32)&spr.uv0)->u = 0x600;
    ((Uv_b602_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b602_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b602_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x64, 0, 32) * (f32)func_00101050(0x12C - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 8; j++) {
            if (g->mote2[i][j].on == 0) {
                continue;
            }
            r = 4.0f * g->mote2[i][j].sc;
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
            m4 = m3;
            func_00100E00(&m4, g->mote2[i][j].ang, 2);
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_001878E0(&cn[2], &m4, &cn[2]);
            func_001878E0(&cn[3], &m4, &cn[3]);
            alpha = (u32)((0.8f + 0.2f * (g->mote2[i][j].t % 2)) * (f * (255.0f * func_0020B550((g->mote2[i][j].t << 15) >> 4))));
            sq.c.r = 0xFF;
            sq.c.g = 0xBE;
            sq.c.b = 0x96;
            sq.c.a = alpha;
            sq.c.q = 1.0f;
            v = g->mote2[i][j].p;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], &v);
            func_00187B00(&out[2], &cn[2], (void *)&v);
            func_00187B00(&out[3], &cn[3], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &sq, &depth) == 1) {
                func_002075F0(&sq, ot, (u32)depth);
            }
            r = 3.0f * g->mote2[i][j].sc;
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
            alpha = (u32)((0.8f + 0.2f * (g->mote2[i][j].t % 2)) * (f * (255.0f * func_0020B550((g->mote2[i][j].t << 15) >> 4))));
            spr.c.r = 0xFF;
            spr.c.g = 0xBE;
            spr.c.b = 0x96;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            v = g->mote2[i][j].p;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], &v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->mote2[i][j].t++;
            if (g->mote2[i][j].t > 16) {
                g->mote2[i][j].on = 0;
            }
        }
    }

    if (g->t == 0x5A) {
        ret = 1;
    } else {
        if (g->t > 0x64 && g->t < 0x12B) {
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
