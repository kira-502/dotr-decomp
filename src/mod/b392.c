#include "common.h"

/* shape b392:01E00080 (b392), 2332 insns, 1 copy: b392 scene manager (b290:01E00080's family, written from the asm):
   setup clears the 0xB4E0 scene, takes both units, two textures, the target and joint 0x1D; else at 0x8C a 256-mote
   two-tone ring, a 32-mote rain shedding 16-slot two-mote trails and a 32-frame eight-layer render-to-texture flash,
   on 0x1F..0x69 32-slot 16-sprite swirls at the joint, at 0x5D a 64-mote burst and a 48-frame beam to the target
   dropping 8-slot puffs; returns 1 / 2 / 8 at 0x82 / 0x8C / >0xBC */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b392_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b392_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b392_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b392_01E00080;

typedef struct {
    Reg_b392_01E00080 a;
    Reg_b392_01E00080 b;
} Tx_b392_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b392_01E00080 c;
    Uv_b392_01E00080 uv0;
    Xyz_b392_01E00080 p0;
    Uv_b392_01E00080 uv1;
    Xyz_b392_01E00080 p1;
    u64 pad38;
    Tx_b392_01E00080 tx;
    u64 pad50;
} Spr_b392_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[256];
    u8 pad108[8];
    Vec4f v[256];
} Ring_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Rain_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32][2];
    f32 f;
    u8 pad4C[4];
    Vec4f p[32];
    Vec4f v[32][2];
} Trail_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
} Flash_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    s32 rot[16];
    u8 pad58[8];
    Vec4f p;
    Vec4f v[16];
} Swirl_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][64];
    u8 pad48[8];
    Vec4f p[1];
    Vec4f v[1][64];
} Burst_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 n;
    f32 d[1];
    Mtx_b392_01E00080 mat[1];
    Vec4f p;
} Beam_b392_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f p;
    Vec4f v[16];
} Puff_b392_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    s32 jn;
    u8 pad34[0xC];
    Vec4f jp;
    Ring_b392_01E00080 ring;
    Rain_b392_01E00080 rain;
    Trail_b392_01E00080 trail[16];
    Flash_b392_01E00080 flash;
    Swirl_b392_01E00080 swirl[32];
    Burst_b392_01E00080 burst;
    Beam_b392_01E00080 beam[1];
    Puff_b392_01E00080 puff[1][1][8];
} Scene_b392_01E00080;

static s32 func_01E00080_b392(s32 arg0, s32 code) {
    Scene_b392_01E00080 *g = (Scene_b392_01E00080 *)arg0;
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
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
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
    Spr_b392_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB4E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn = func_001F5560(g->unitA, 0x1D, 1);
        g->ring.on = 0;
        g->rain.on = 0;
        for (i = 0; i < 16; i++) {
            g->trail[i].on = 0;
        }
        g->flash.on = 0;
        for (i = 0; i < 32; i++) {
            g->swirl[i].on = 0;
        }
        g->burst.on = 0;
        for (i = 0; i < 1; i++) {
            g->beam[i].on = 0;
            g->beam[i].n = 0;
        }
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 8; k++) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->jn, &g->jp);

    if (g->t == 0x8C) {
        g->ring.on = 1;
        g->ring.t = 0;
        for (j = 0; j < 256; j++) {
            g->ring.c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->ring.v[j], 1.2f);
        }
    }
    if (g->ring.on == 1) {
        ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 6.0f;
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
        s = 0.1f + 0.9f * func_00100D50(g->ring.t, 32, 2);
        w = func_00100FF0((f32)g->ring.t, 32.0f, 16.0f);
        for (j = 0; j < 256; j++) {
            if (j % 2 == 0) {
                func_002086D0(&spr, func_00208D00(2));
                h = 0.8f * s;
                alpha = (u32)(32.0f * w);
                (void)alpha;
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                h = s;
                alpha = (u32)(96.0f * w);
                (void)alpha;
                spr.c.r = 0xFF;
                spr.c.g = 0x50;
                spr.c.b = 0x19;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            x = g->ring.c[j] % 4 * 32;
            y = (g->ring.c[j] >> 2) * 32;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->ring.v[j], h);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->ring.t++;
        if (g->ring.t > 32) {
            g->ring.on = 0;
        }
    }

    if (g->t == 0x8C) {
        g->rain.on = 1;
        g->rain.t = 0;
        for (j = 0; j < 32; j++) {
            g->rain.c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->rain.v[j], 3.0f);
        }
    }
    if (g->rain.on == 1) {
        ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 3.0f;
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
        f = func_00100FF0((f32)g->rain.t, 32.0f, 16.0f);
        alpha = (u32)(255.0f * f);
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->rain.t, 32, 1);
        h = 8.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->rain.t, 2.0f)));
        n = g->rain.t % 16;
        (void)n;
        g->trail[n].on = 1;
        g->trail[n].t = 0;
        g->trail[n].f = f;
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 2; k++) {
                g->trail[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->trail[n].v[j][k], 0.2f);
            }
        }
        for (j = 0; j < 32; j++) {
            x = g->rain.c[j] % 4 * 32;
            y = (g->rain.c[j] >> 2) * 32;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->rain.v[j], s);
            v.y += h;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            g->trail[n].p[j] = v;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->rain.t++;
        if (g->rain.t > 32) {
            g->rain.on = 0;
        }
    }

    ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->trail[i].on == 0) {
            continue;
        }
        r = 0.5f + 0.5f * (16 - g->trail[i].t) / 16.0f;
        r = 3.0f * r;
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
        f = func_00100FF0((f32)g->trail[i].t, 16.0f, 8.0f);
        alpha = (u32)(255.0f * f * g->trail[i].f);
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->trail[i].t, 16, 1);
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 2; k++) {
                x = g->trail[i].c[j][k] % 4 * 32;
                y = (g->trail[i].c[j][k] >> 2) * 32;
                ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->trail[i].v[j][k], s);
                func_00187B00(&v, &v, &g->trail[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->trail[i].t++;
        if (g->trail[i].t > 16) {
            g->trail[i].on = 0;
        }
    }

    if (g->t == 0x8C) {
        g->flash.on = 1;
        g->flash.t = 0;
    }
    if (g->flash.on == 1) {
        ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 5);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &spr.tx.a, &spr.tx.b);
        func_00208460();
        alpha = (32 - g->flash.t) * 32 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        spr.p0.x = 0x6C00;
        spr.p0.y = 0x7200;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x9400;
        spr.p1.y = 0x8E00;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        for (k = 0; k < 8; k++) {
            x = (k + 1) * 42 >> 3;
            y = (k + 1) * 29 >> 3;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (0x280 - x) << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (0x1C0 - y) << 4;
            func_002075F0(&spr, 0, 0);
        }
        func_00207FD0(buf, ot, 0);
        g->flash.t++;
        if (g->flash.t > 32) {
            g->flash.on = 0;
        }
    }

    if (g->t > 0x1E && g->t < 0x6A) {
        n = g->t % 32;
        (void)n;
        g->swirl[n].on = 1;
        g->swirl[n].t = 0;
        g->swirl[n].p = g->jp;
        for (j = 0; j < 16; j++) {
            g->swirl[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->swirl[n].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->swirl[n].v[j], 0.3f);
        }
    }

    ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->swirl[i].on == 0) {
            continue;
        }
        r = 1.5f * (0.2f + 0.8f * (32 - g->swirl[i].t) / 32.0f);
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
        alpha = (u32)(255.0f * func_0020B550((g->swirl[i].t << 15) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0x28;
        spr.c.b = 0x0A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->swirl[i].t, 32, 1);
        h = 2.0f * s;
        for (j = 0; j < 16; j++) {
            func_00187B48(&v, &g->swirl[i].v[j], s);
            v.y += 2.0f * g->swirl[i].t / 32.0f;
            n = (g->swirl[i].rot[j] + ((g->swirl[i].t << 14) >> 5)) * (j % 2 * 2 - 1) & 0xFFFF;
            v.x += h * func_0020B550(n);
            v.z += h * func_0020B480(n);
            func_00187B00(&v, &v, &g->swirl[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->swirl[i].c[j] % 4 * 32;
            y = (g->swirl[i].c[j] >> 2) * 32;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->swirl[i].t++;
        if (g->swirl[i].t > 32) {
            g->swirl[i].on = 0;
        }
    }

    if (g->t == 0x5D) {
        g->burst.on = 1;
        g->burst.t = 0;
        for (i = 0; i < 1; i++) {
            g->burst.p[i] = g->jp;
            for (j = 0; j < 64; j++) {
                g->burst.c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst.v[i][j], 0.5f);
            }
        }
    }
    if (g->burst.on == 1) {
        ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208CB0(&spr, 5);
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (u32)(64.0f * func_0020B480((g->burst.t << 14) >> 5));
        spr.c.r = 0x80;
        spr.c.g = 0x70;
        spr.c.b = 0x64;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f * (0.5f + 0.5f * g->burst.t / 32.0f);
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
        s = func_00100D50(g->burst.t, 32, 1);
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 64; j++) {
                x = g->burst.c[i][j] % 4 * 32;
                y = (g->burst.c[i][j] >> 2) * 32;
                ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->burst.v[i][j], s);
                func_00187B00(&v, &v, &g->burst.p[i]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst.t++;
        if (g->burst.t > 32) {
            g->burst.on = 0;
        }
    }

    if (g->t == 0x5D) {
        n = g->t;
        n %= 1;
        g->beam[n].on = 1;
        g->beam[n].t = 0;
        g->beam[n].p = g->jp;
        for (j = 0; j < 1; j++) {
            v = g->tgt;
            func_00187B18(&v, &v, &g->beam[n].p);
            g->beam[n].d[j] = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
            func_00100E40(&g->beam[n].mat[j], &v);
            func_00100E00(&g->beam[n].mat[j], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
    }

    ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 64;
    y = 0;
    ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
    ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
    r = 5.0f;
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
    for (i = 0; i < 1; i++) {
        if (g->beam[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0x28;
        spr.c.b = 0x0A;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        f = (f32)g->beam[i].t / 47.0f;
        n = g->beam[i].n;
        g->beam[i].n++;
        if (g->beam[i].n >= 8) {
            g->beam[i].n = 0;
        }
        for (j = 0; j < 1; j++) {
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = f * g->beam[i].d[j];
            v.w = 1.0f;
            func_001878E0(&v, &g->beam[i].mat[j], &v);
            func_00187B00(&v, &v, &g->beam[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->puff[i][j][n].on = 1;
            g->puff[i][j][n].t = 0;
            g->puff[i][j][n].p = v;
            for (y = 0; y < 16; y++) {
                g->puff[i][j][n].c[y] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[i][j][n].v[y], 0.3f);
            }
        }
        g->beam[i].t++;
        if (g->beam[i].t > 0x2F) {
            g->beam[i].on = 0;
        }
    }

    ((Spr_b392_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b392_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b392_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b392_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b392_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 8; k++) {
                if (g->puff[i][j][k].on == 0) {
                    continue;
                }
                r = 3.5f * (0.5f + 0.5f * (8 - g->puff[i][j][k].t) / 8.0f);
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
                alpha = (8 - g->puff[i][j][k].t) * 128 >> 3;
                spr.c.r = 0xFF;
                spr.c.g = 0x3C;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->puff[i][j][k].t, 8, 1);
                for (l = 0; l < 16; l++) {
                    x = g->puff[i][j][k].c[l] % 4 * 32;
                    y = (g->puff[i][j][k].c[l] >> 2) * 32;
                    ((Uv_b392_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b392_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b392_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b392_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->puff[i][j][k].v[l], s);
                    func_00187B00(&v, &v, &g->puff[i][j][k].p);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->puff[i][j][k].t++;
                if (g->puff[i][j][k].t > 8) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
    }

    if (g->t == 0x82) {
        ret = 1;
    } else if (g->t == 0x8C) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0xBC) {
        ret = 8;
    }
    return ret;
}
