#include "common.h"

/* shape b295:01E00080 (b295), 2006 insns, 1 copy: b295 scene manager (b141:01E00080's family, written from the asm):
   setup clears the 0x9550 scene, takes both units, two textures, joints 0x47 / 0x4A / 0x2E and the target and builds
   a 33x3 ring table; else spawns 32-slot 4-sprite puffs at the joint midpoint on 1..0x3B, 48-slot 16-sprite rushes
   toward the target and 24-slot sparks on 0x43..0xDB, 16-slot 32-sprite clouds on 0x5B..0x171, and at frame 4 a
   32-frame flare with a two-band ring of gouraud quads and 128 motes; returns 1 / 6 / 2 / 8 at 0x50 / 0x5B..0x170 /
   0x171 / >0x172 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b295_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b295_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b295_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b295_01E00080 c;
    Uv_b295_01E00080 uv0;
    Xyz_b295_01E00080 p0;
    Uv_b295_01E00080 uv1;
    Xyz_b295_01E00080 p1;
    u8 tail[0x20];
} Spr_b295_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b295_01E00080 c;
        Xyz_b295_01E00080 p;
    } v[4];
    u64 tail;
} Quad_b295_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[4];
    Vec4f p;
    Vec4f v[4];
} Puff_b295_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[16];
    f32 f[16];
    u8 pad88[8];
    Vec4f p;
    Vec4f v[16];
} Rush_b295_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Cloud_b295_01E00080;

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
    Puff_b295_01E00080 puff[32];
    Rush_b295_01E00080 rush[48];
    Cloud_b295_01E00080 cloud[16];
    Puff_b295_01E00080 spark[24];
    u8 on2;
    u8 pad8681[3];
    s32 t2;
    u8 pad8688[8];
    Vec4f ring[33][3];
    u8 c2[128];
    Vec4f p2;
    Vec4f v2[128];
} Scene_b295_01E00080;

static s32 func_01E00080_b295(s32 arg0, s32 code) {
    Scene_b295_01E00080 *g = (Scene_b295_01E00080 *)arg0;
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
    Vec4f v;
    Spr_b295_01E00080 spr __attribute__((aligned(8)));
    Quad_b295_01E00080 qd __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9550);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->bone[0] = func_001F5560(g->unitA, 0x47, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x4A, 0);
        g->bone2 = func_001F5560(g->unitA, 0x2E, 0);
        func_001F53C0(1, g->unitB, &g->tgt);
        for (i = 0; i < 32; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->rush[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->cloud[i].on = 0;
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
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->bone[i], &g->bp[i]);
    }
    func_00187B00(&g->mid, &g->bp[0], &g->bp[1]);
    func_00187B48((void *)&g->mid, &g->mid, 0.5f);
    func_001F5620(g->unitA, g->bone2, &g->bp2);

    if (g->t > 0 && g->t < 0x3C) {
        n = g->t % 32;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        g->puff[n].p = g->mid;
        for (i = 0; i < 4; i++) {
            g->puff[n].c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->puff[n].v[i], 0.2f);
        }
    }

    ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        r = 5.0f * (0.2f + 0.8f * g->puff[i].t / 32.0f);
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
        alpha = (32 - g->puff[i].t) * 96 >> 5;
        spr.c.r = 0x8F;
        spr.c.g = 0x64;
        spr.c.b = 0x60;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->puff[i].t, 32, 1);
        for (q = 0; q < 4; q++) {
            func_00187B48(&v, &g->puff[i].v[q], s);
            func_00187B00(&v, &v, &g->puff[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->puff[i].c[q] % 4 * 32;
            y = (g->puff[i].c[q] >> 2) * 32;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 32) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0x42 && g->t < 0xDC) {
        n = g->t % 48;
        (void)n;
        g->rush[n].on = 1;
        g->rush[n].t = 0;
        g->rush[n].p = g->mid;
        g->rush[n].p.z += 4.0f * g->obj;
        for (j = 0; j < 16; j++) {
            g->rush[n].c[j] = (func_0019A5C8() >> 23) % 8;
            g->rush[n].f[j] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->rush[n].v[j], 1.0f);
            func_00187B00(&g->rush[n].v[j], &g->rush[n].v[j], &g->tgt);
            func_00187B18(&g->rush[n].v[j], &g->rush[n].v[j], &g->rush[n].p);
        }
    }

    ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0xDC - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->rush[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (180.0f * func_00101020((f32)g->rush[i].t, 4.0f) * func_00100FF0((f32)g->rush[i].t, 48.0f, 32.0f)));
        spr.c.r = 0x8C;
        spr.c.g = 0x38;
        spr.c.b = 0xFF;
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
        for (q = 0; q < 16; q++) {
            x = g->rush[i].c[q] % 4 * 32;
            y = (g->rush[i].c[q] >> 2) * 32;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t > 0x5A && g->t < 0x172) {
        n = g->t % 16;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->cloud[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->cloud[n].v[j], 1.3f);
        }
    }

    ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x5A, 0, 32) * (f32)func_00101050(0x172 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (96.0f * func_0020B550((g->cloud[i].t << 15) >> 4)));
        spr.c.r = 0x8B;
        spr.c.g = 0x39;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * (16 - g->cloud[i].t) / 16.0f);
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
        s = g->cloud[i].t / 16.0f;
        h = 0.9f + 0.1f * (16 - g->cloud[i].t) / 16.0f;
        w = -25.0f + 80.0f * s;
        for (q = 0; q < 32; q++) {
            x = g->cloud[i].c[q] % 4 * 32;
            y = (g->cloud[i].c[q] >> 2) * 32;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v.x = g->cloud[i].v[q].x * h;
            v.y = w + g->cloud[i].v[q].y;
            v.z = g->cloud[i].v[q].z * h;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->cloud[i].t++;
        if (g->cloud[i].t > 16) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t > 0x42 && g->t < 0xDC) {
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

    ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
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
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (u32)(255.0f * func_0020B550((g->spark[i].t << 15) / 24));
        spr.c.r = 0x80;
        spr.c.g = 0x28;
        spr.c.b = 0x8F;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[i].t, 24, 1);
        for (q = 0; q < 4; q++) {
            func_00187B48(&v, &g->spark[i].v[q], s);
            func_00187B00(&v, &v, &g->spark[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[q] % 4 * 32;
            y = (g->spark[i].c[q] >> 2) * 32;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 24) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 4) {
        g->on2 = 1;
        g->t2 = 0;
        g->p2 = g->bp2;
        for (j = 0; j < 128; j++) {
            g->c2[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v2[j], 0.3f);
        }
    }
    if (g->on2 == 1) {
        ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 96;
        y = 0;
        ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->p2);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xE4;
        spr.c.g = 0xB4;
        spr.c.b = 0xFF;
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
        ((Quad_b295_01E00080 *)(s32)&qd)->flags = 0x14;
        ((Quad_b295_01E00080 *)(s32)&qd)->size = 8;
        ((Quad_b295_01E00080 *)(s32)&qd)->regs = 0x41414141;
        ((Quad_b295_01E00080 *)(s32)&qd)->pad4 = 0;
        func_002086D0(&qd, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->p2);
        s = func_00100D50(g->t2, 32, 2);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        qd.v[0].c.r = 0x64;
        qd.v[0].c.g = 0x40;
        qd.v[0].c.b = 0xFF;
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
        ((Spr_b295_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b295_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b295_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b295_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b295_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0x64;
        spr.c.g = 0x40;
        spr.c.b = 0xFF;
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
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        for (j = 0; j < 128; j++) {
            x = g->c2[j] % 4 * 32;
            y = (g->c2[j] >> 2) * 32;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b295_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    if (g->t == 0x50) {
        ret = 1;
    } else {
        if (g->t > 0x5A && g->t < 0x171) {
            ret = 6;
        }
        if (g->t == 0x171) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x172) {
        ret = 8;
    }
    return ret;
}
