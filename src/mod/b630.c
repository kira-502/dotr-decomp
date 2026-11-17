#include "common.h"

/* shape b630:01E00080 (b630), 2339 insns, 1 copy: b630 scene manager (b014:01E00080's family, written from the asm):
   setup clears the 0x25E0 scene, takes both units, four textures and unit B's target, builds two 33-point double
   rings; else pulls a midpoint between the units and projects B to the screen, at 0x20 a 0x249-frame beam sprite
   beside A, from frame 0 32 spinning textured rim layers and a ring sprite, on 1..0x20F 24-slot three-quad puffs, on
   0x185..0x20F 18-slot expanding shells, at 0x1C8 an 8-triangle screen ripple, at 0x208 a 128-mote burst (double 0.7f
   + 0.3 scale) and a fade, a flash at 0xFE; returns 1 / 6 / 3 / 8 at 0x17A / 0x185..0x21F / 0x220 / >0x288 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b630_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b630_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b630_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b630_01E00080;

typedef struct {
    Reg_b630_01E00080 a;
    Reg_b630_01E00080 b;
} Tx_b630_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b630_01E00080 c;
    Xyz_b630_01E00080 v[2];
    u64 tail;
} Flat_b630_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b630_01E00080 c;
    Uv_b630_01E00080 uv0;
    Xyz_b630_01E00080 p0;
    Uv_b630_01E00080 uv1;
    Xyz_b630_01E00080 p1;
    u64 pad38;
    Tx_b630_01E00080 tx;
    u64 pad50;
} Spr_b630_01E00080;

typedef struct {
    Rgbaq_b630_01E00080 c;
    Uv_b630_01E00080 uv;
    Xyz_b630_01E00080 p;
} Tv_b630_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b630_01E00080 v[3];
    u64 pad58;
    Tx_b630_01E00080 tx;
    u64 pad70;
} Tri_b630_01E00080;

typedef struct {
    Rgbaq_b630_01E00080 c;
    f32 s, t;
    Xyz_b630_01E00080 p;
} Sv_b630_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Sv_b630_01E00080 v[4];
    u8 tail[0x20];
} Quad_b630_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b630_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
} Rim_b630_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3];
    u8 padB[5];
    Vec4f v[3];
} Puff_b630_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c;
    u8 pad9[7];
    Mtx_b630_01E00080 m;
} Shell_b630_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f tgt;
    Vec4f tgtB;
    Vec4f scr;
    Vec4f mid;
    Vec4f scale;
    u8 on1;
    u8 pad71[3];
    s32 t1;
    u8 pad78[8];
    Vec4f pos;
    Rim_b630_01E00080 rim[33];
    u8 on2;
    u8 pad4B1[3];
    s32 t2;
    u8 c2[32];
    s32 ph[32];
    u8 pad558[8];
    Mtx_b630_01E00080 rot[32];
    u8 on3;
    u8 padD61[3];
    s32 t3;
    u8 padD68[8];
    Puff_b630_01E00080 puff[24];
    Rim_b630_01E00080 rim2[33];
    Shell_b630_01E00080 shell[18];
    u8 on4;
    u8 pad1D31[3];
    s32 t4;
    u8 on5;
    u8 pad1D39[3];
    s32 t5;
    u8 on6;
    u8 pad1D41[3];
    s32 t6;
    u8 c6[128];
    u8 pad1DC8[8];
    Vec4f v6[128];
    u8 on7;
    u8 pad25D1[3];
    s32 t7;
    u8 pad25D8[8];
} Scene_b630_01E00080;

static s32 func_01E00080_b630(s32 arg0, s32 code) {
    Scene_b630_01E00080 *g = (Scene_b630_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern Vec4f *func_001F9AD0(s32);
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
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_002087A0(void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    f32 f;
    f32 h;
    f32 s;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    Mtx_b630_01E00080 m2;
    Mtx_b630_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b630_01E00080 m4;
    Vec4f v;
    Vec4f w;
    Flat_b630_01E00080 flat __attribute__((aligned(8)));
    Spr_b630_01E00080 spr __attribute__((aligned(8)));
    Tri_b630_01E00080 tri __attribute__((aligned(8)));
    Quad_b630_01E00080 pk __attribute__((aligned(8)));
    Xyz_b630_01E00080 scr;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x25E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F53C0(1, g->unitB, &g->tgtB);
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            s = func_0020B550((i << 16) >> 5);
            h = func_0020B480((i << 16) >> 5);
            g->rim[i].a.x = 10.0f * s;
            g->rim[i].a.y = 10.0f * h;
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 20.0f * s;
            g->rim[i].b.y = 20.0f * h;
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
        }
        g->on2 = 0;
        g->t3 = 0;
        for (i = 0; i < 24; i++) {
            g->puff[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            s = func_0020B550((i << 16) >> 5);
            h = func_0020B480((i << 16) >> 5);
            g->rim2[i].a.x = 70.0f * s;
            g->rim2[i].a.y = 70.0f * h;
            g->rim2[i].a.z = 0.0f;
            g->rim2[i].a.w = 1.0f;
            g->rim2[i].b.x = 150.0f * s;
            g->rim2[i].b.y = 150.0f * h;
            g->rim2[i].b.z = 0.0f;
            g->rim2[i].b.w = 1.0f;
        }
        for (i = 0; i < 18; i++) {
            g->shell[i].on = 0;
        }
        g->on4 = 0;
        g->on5 = 0;
        g->on6 = 0;
        g->on7 = 0;
        return 0;
    }
    func_00205CA0(&m3);
    func_001F53C0(1, g->unitA, &g->tgt);
    k = (s32)(32768.0f * ((f32)func_00101050(g->t - 0xFE, 0, 0xC4) / 196.0f));
    k &= 0xFFFF;
    s = 0.5f * (1.0f - func_0020B480(k));
    func_00187B18(&v, &g->tgtB, &g->tgt);
    func_00187B48(&v, &v, s);
    func_00187B00(&g->mid, &v, &g->tgt);
    g->scale.z = g->scale.y = g->scale.x = 1.0f + s;
    g->scale.w = 1.0f;
    func_0020EB40(m);
    func_0020BBB0(&m2);
    func_0020BC00(m, &m2);
    func_00205440(&g->tgtB, m, &scr, &depth);
    g->scr.x = (scr.x >> 4) - 0x6C0;
    g->scr.y = (scr.y >> 4) - 0x720;
    g->scr.z = scr.z;
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

    if (g->t == 0x208) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t4 == 8) {
            g->on5 = 0;
            g->on2 = 0;
            g->on3 = 0;
            for (i = 0; i < 24; i++) {
                g->puff[i].on = 0;
            }
            for (i = 0; i < 18; i++) {
                g->shell[i].on = 0;
            }
        }
        ((Flat_b630_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b630_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b630_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b630_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (func_00101020((f32)g->t4, 8.0f) * (1.0f - func_00100D50(func_00101050(g->t4 - 0x18, 0, 0x20), 0x20, 1))));
        flat.c.r = 0xFF;
        flat.c.g = 0xFF;
        flat.c.b = 0xFF;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        flat.v[0].x = 0x6C00;
        flat.v[0].y = 0x7200;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t4++;
        if (g->t4 > 0x38) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x20) {
        g->on1 = 1;
        g->t1 = 0;
        w = *func_001F9AD0(0);
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = -160.0f;
        v.w = 1.0f;
        m4 = m3;
        if (w.x * g->obj < 0.0f) {
            func_00100E00(&m4, -0x4000, 1);
        } else {
            func_00100E00(&m4, 0x4000, 1);
        }
        func_001878E0(&v, &m4, &v);
        func_00187B00(&g->pos, &v, &g->tgt);
        g->pos.y += 100.0f;
    }
    if (g->on1 == 1) {
        ((Spr_b630_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b630_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b630_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b630_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b630_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(&m2);
        func_0020BC00(m, &m2);
        alpha = (u32)(128.0f * (func_00101020((f32)g->t1, 32.0f) * func_00100FF0((f32)g->t1, 584.0f, 552.0f)));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 52.0f;
        cn[0].x = -h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        x = 0;
        ((Uv_b630_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv0)->v = x << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv1)->u = (x + 128) << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv1)->v = (x + 128) << 4;
        v = g->pos;
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], &v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, 0xFFFFFF);
        }
        g->t1++;
        if (g->t1 > 0x248) {
            g->on1 = 0;
        }
    }

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 32; i++) {
            g->c2[i] = (func_0019A5C8() >> 23) % 8;
            g->ph[i] = (func_0019A5C8() >> 23) % 32;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
            g->rot[i] = m4;
        }
    }
    if (g->on2 == 1) {
        ((Quad_b630_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b630_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b630_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b630_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208700(&pk, g->tex[1], 1);
        func_002086D0(&pk, func_00208D00(1));
        func_00208CB0(&pk, 0);
        alpha = (u32)(128.0f * (func_00101020((f32)g->t2, 128.0f) * func_00100FF0((f32)g->t2, 12800.0f, 12672.0f)));
        pk.v[0].c.r = 0xE0;
        pk.v[0].c.g = 0xE8;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0;
        pk.v[2].c.g = 0;
        pk.v[2].c.b = 0x80;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        for (j = 0; j < 32; j++) {
            func_0020EB40(m);
            func_0020BBB0(&m2);
            func_0020CB20(&m2, &g->scale);
            func_00187B60(&m2, &m2, &g->mid);
            m4 = g->rot[j];
            func_00100E00(&m4, g->t2 * 0x21, 2);
            func_00100E00(&m4, g->t2 * 0x2C, 1);
            func_00100E00(&m4, g->t2 * 0x22B, 0);
            func_0020BC00(&m2, &m4);
            s = 0.8f + 0.2f * (j + 1) / 32.0f;
            v.x = s;
            v.y = s;
            v.z = s;
            v.w = 1.0f;
            func_0020CB20(&m2, &v);
            func_0020BC00(m, &m2);
            h = 32.0f * ((g->t2 + g->ph[j]) % 32) / 32.0f;
            (void)h;
            x = g->c2[j] % 4 * 32;
            y = (g->c2[j] >> 2) * 32;
            w0 = (x + h) / 128.0f;
            w1 = y / 64.0f;
            u0 = (32.0f + y) / 64.0f;
            for (i = 0; i < 32; i++) {
                pk.v[0].s = w0;
                pk.v[0].t = w1;
                pk.v[1].s = w0;
                pk.v[1].t = w1;
                pk.v[2].s = w0;
                pk.v[2].t = u0;
                pk.v[3].s = w0;
                pk.v[3].t = u0;
                if (func_00100BA0(&g->rim[i].a, &g->rim[i + 1].a, &g->rim[i].b, &g->rim[i + 1].b, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 0x3200) {
            g->on2 = 0;
        }
    }

    if (g->t == 0) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b630_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b630_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b630_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b630_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b630_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(&m2);
        func_0020CB20(&m2, &g->scale);
        func_00187B60(&m2, &m2, &g->mid);
        func_0020BC00(m, &m2);
        alpha = (u32)(128.0f * ((0.8f + 0.2f * (g->t3 % 2)) * func_00101020((f32)g->t3, 128.0f)));
        spr.c.r = 0x80;
        spr.c.g = 0xA4;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 25.0f;
        cn[0].x = h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&out[0], &m3, &cn[0]);
        func_001878E0(&out[1], &m3, &cn[1]);
        x = 0;
        y = 32;
        ((Uv_b630_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b630_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->t3++;
        if (g->t3 > 0x3200) {
            g->on3 = 0;
        }
    }

    if (g->t > 0 && g->t < 0x210) {
        n = g->t % 24;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (j = 0; j < 3; j++) {
            g->puff[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->puff[n].v[j], 1.0f);
        }
    }

    ((Quad_b630_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b630_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b630_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b630_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 5);
    f = (f32)func_00101050(g->t, 0, 0x80) / 128.0f;
    for (i = 0; i < 24; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (f32)((24 - g->puff[i].t) * 80 / 24));
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        func_0020EB40(m);
        v = g->mid;
        func_0020C940(&m2, NULL, NULL, &v);
        func_0020CB20(&m2, &g->scale);
        func_0020BC00(m, &m2);
        s = -3.5f * (0.5f + 0.5f * func_00100D50(g->puff[i].t, 24, 1));
        for (j = 0; j < 3; j++) {
            func_00100E40(&m4, &g->puff[i].v[j]);
            func_00100E00(&m4, (i << 16) / 24 + (j << 16) / 3, 2);
            cn[0].x = 0.0f;
            cn[0].y = 2.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -2.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&out[0], &cn[0], &g->puff[i].v[j]);
            func_00187B00(&out[1], &cn[1], (void *)&g->puff[i].v[j]);
            func_00187B48(&v, &g->puff[i].v[j], s);
            func_00187B00(&out[2], (void *)&out[0], (void *)&v);
            func_00187B00(&out[3], &out[1], (void *)&v);
            x = g->puff[i].c[j] % 4 * 32;
            y = (g->puff[i].c[j] >> 2) * 32;
            u0 = x / 128.0f;
            u1 = (32.0f + x) / 128.0f;
            w0 = y / 64.0f;
            w1 = (32.0f + y) / 64.0f;
            pk.v[0].s = u0;
            pk.v[0].t = w0;
            pk.v[1].s = u1;
            pk.v[1].t = w0;
            pk.v[2].s = u0;
            pk.v[2].t = w1;
            pk.v[3].s = u1;
            pk.v[3].t = w1;
            if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 24) {
            g->puff[i].on = 0;
        }
    }

    if (g->t > 0x184 && g->t < 0x210) {
        n = g->t % 18;
        (void)n;
        g->shell[n].on = 1;
        g->shell[n].t = 0;
        g->shell[n].c = (func_0019A5C8() >> 23) % 8;
        func_0020BBB0(&m4);
        func_00187B60(&m4, &m4, &g->mid);
        func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
        func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
        g->shell[n].m = m4;
    }

    ((Quad_b630_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b630_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b630_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b630_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[3], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 18; i++) {
        if (g->shell[i].on == 0) {
            continue;
        }
        alpha = (u32)(200.0f * func_0020B480((g->shell[i].t << 14) / 18));
        pk.v[0].c.r = 0xC6;
        pk.v[0].c.g = 0xC6;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0x40;
        pk.v[2].c.g = 0x50;
        pk.v[2].c.b = 0xFF;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        s = g->shell[i].t / 18.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        m2 = g->shell[i].m;
        func_0020CB20(&m2, &v);
        func_0020BC00(m, &m2);
        for (j = 0; j < 32; j++) {
            pk.v[0].s = 0.0f;
            pk.v[0].t = 0.0f;
            pk.v[1].s = 1.0f;
            pk.v[1].t = 0.0f;
            pk.v[2].s = 0.0f;
            pk.v[2].t = 1.0f;
            pk.v[3].s = 1.0f;
            pk.v[3].t = 1.0f;
            if (func_00100BA0(&g->rim2[j].a, &g->rim2[j + 1].a, &g->rim2[j].b, &g->rim2[j + 1].b, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->shell[i].t++;
        if (g->shell[i].t > 18) {
            g->shell[i].on = 0;
        }
    }

    if (g->t == 0x1C8) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Tri_b630_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b630_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b630_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b630_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b630_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        func_002087A0(&tri, 1);
        alpha = (u32)(128.0f * func_00101020((f32)g->t5, 64.0f));
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 1; i++) {
            s = 1.0f + 0.1f * (1 - i);
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b630_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b630_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b630_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b630_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b630_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b630_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48(&out[0], &out[0], s);
                func_00187B48(&out[1], &out[1], s);
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
                func_002075F0(&tri, ot, 0);
            }
        }
        g->t5++;
        if (g->t5 > 0xC80) {
            g->on5 = 0;
        }
    }

    if (g->t == 0x208) {
        g->on6 = 1;
        g->t6 = 0;
        for (i = 0; i < 128; i++) {
            g->c6[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v6[i], 2.0f);
        }
    }
    if (g->on6 == 1) {
        ((Spr_b630_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b630_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b630_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b630_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b630_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        alpha = (u32)(255.0f * func_00100FF0((f32)g->t6, 64.0f, 32.0f));
        spr.c.r = 0x64;
        spr.c.g = 0x64;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = 4.0f;
        cn[0].x = h;
        cn[0].y = h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -h;
        cn[1].y = -h;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        func_0020EB40(m);
        func_0020BBB0(&m2);
        func_00187B60(&m2, &m2, &g->tgtB);
        func_0020BC00(m, &m2);
        s = 0.7f + 0.3 * func_00100D50(g->t6, 0x40, 1);
        for (i = 0; i < 128; i++) {
            x = g->c6[i] % 4 * 32;
            y = (g->c6[i] >> 2) * 32;
            ((Uv_b630_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b630_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b630_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b630_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v6[i], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t6++;
        if (g->t6 > 0x40) {
            g->on6 = 0;
        }
    }

    if (g->t == 0xFE) {
        g->on7 = 1;
        g->t7 = 0;
    }
    if (g->on7 == 1) {
        ((Flat_b630_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b630_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b630_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b630_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * ((f32)(32 - g->t7) / 32.0f));
        flat.c.r = 0xFF;
        flat.c.g = 0xFF;
        flat.c.b = 0xFF;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        flat.v[0].x = 0x6C00;
        flat.v[0].y = 0x7200;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t7++;
        if (g->t7 > 0x20) {
            g->on7 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x288 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -128) >> 10) + 0x80));
    if (g->t == 0x17A) {
        ret = 1;
    } else {
        if (g->t > 0x184 && g->t < 0x220) {
            ret = 6;
        }
        if (g->t == 0x220) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x288) {
        ret = 8;
    }
    return ret;
}
