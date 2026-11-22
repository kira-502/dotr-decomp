#include "common.h"

/* shape b730:01E00080 (b730), 2816 insns, 1 copy (-O3,p): b730 scene manager (b729:01E00080's twin): setup clears the
   0x2080 scene, takes both units, five textures, the target and joint 0x2C, builds a 33-point triple rim; projects
   the unit point (taken at 0xDC) to the screen every frame, at 0xDC a 0x95-frame spinning 4-quad flash there
   (D_28BAF0), from 0x171 a 0x5E-frame 8-layer radial blur (render-to-texture, D_28B960) at the target's screen point
   and an 84-frame burst (64+64 sprites, a 195-unit glow and 128x6 streaks), from 0xEC four expanding screen rings
   every 33 frames, at 0x31 an 18-frame ring burst of line strips and 128 sprites at the joint, at 0x135 a unit colour
   flash, the screen tint; returns 1 / 6 / 2 / 8 at 0x167 / 0x172..0x1C4 / 0x1C5 / >0x1EF */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b730_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b730_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b730_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b730_01E00080 c;
    Uv_b730_01E00080 uv0;
    Xyz_b730_01E00080 p0;
    Uv_b730_01E00080 uv1;
    Xyz_b730_01E00080 p1;
    u8 tail[0x20];
} Spr_b730_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b730_01E00080 c;
    struct {
        Uv_b730_01E00080 uv;
        Xyz_b730_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Quad_b730_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b730_01E00080 c;
        Xyz_b730_01E00080 p;
    } v[4];
    u64 tail;
} Line_b730_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b730_01E00080 c;
        Uv_b730_01E00080 uv;
        Xyz_b730_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b730_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b730_01E00080;

typedef struct {
    u8 c[4];
} Col_b730_01E00080;

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
} Burst_b730_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Ring_b730_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f c;
} Rim_b730_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    u8 pad24[0xC];
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr0;
    Vec4f scr;
    s32 jn;
    u8 pad74[0xC];
    Vec4f jp;
    s32 cur;
    u8 pad94[0xC];
    Burst_b730_01E00080 burst[1];
    u8 on2;
    u8 pad1181[3];
    s32 t2;
    s32 nring;
    s32 tring;
    Ring_b730_01E00080 ring[4];
    u8 on3;
    u8 pad11B1[3];
    s32 t3;
    u8 on4;
    u8 pad11B9[3];
    s32 t4;
    Rim_b730_01E00080 rim[33];
    u8 c4[128];
    Vec4f pos4;
    Vec4f v4[128];
} Scene_b730_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b730(s32 arg0, s32 code) {
    Scene_b730_01E00080 *g = (Scene_b730_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F57B0(s32);
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
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    extern Vec4f D_28BAF0[][4];
    extern u8 D_0030FF00[];
    extern Col_b730_01E00080 D_01E02D00_b730;
    extern Col_b730_01E00080 D_01E02D08_b730;
    s32 ret;
    s32 ot;
    u8 a2;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 d;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Mtx_b730_01E00080 m4;
    Vec4f v;
    s32 ix[4];
    s32 iy[4];
    Spr_b730_01E00080 spr __attribute__((aligned(8)));
    Quad_b730_01E00080 quad __attribute__((aligned(8)));
    Line_b730_01E00080 line __attribute__((aligned(8)));
    Tri_b730_01E00080 tri __attribute__((aligned(8)));
    Xyz_b730_01E00080 xyz;
    f32 depth;
    Col_b730_01E00080 c0;
    Col_b730_01E00080 c1;

    ret = 0;
    ot = func_00207500();
    c0 = D_01E02D00_b730;
    c1 = D_01E02D08_b730;
    if (code >= 0) {
        func_00195108(g, 0x2080);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        func_001F5F90(g->unitB, &g->tgt);
        g->pos.x = 0.0f;
        g->pos.y = 0.0f;
        g->pos.z = 0.0f;
        g->pos.w = 1.0f;
        g->scr0.x = 0.0f;
        g->scr0.y = 0.0f;
        g->scr0.z = 0.0f;
        g->scr0.w = 1.0f;
        g->jn = func_001F5560(g->unitA, 0x2C, 1);
        g->cur = 0;
        for (i = 0; i < 1; i++) {
            g->burst[i].on = 0;
        }
        g->on2 = 0;
        g->nring = 0;
        g->tring = 0;
        for (i = 0; i < 4; i++) {
            g->ring[i].on = 0;
        }
        g->on3 = 0;
        g->on4 = 0;
        for (i = 0; i < 33; i++) {
            v.x = func_0020B550((i << 16) >> 5);
            v.y = func_0020B480((i << 16) >> 5);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->rim[i].a, &v, 16.5f);
            func_00187B48((void *)&g->rim[i].b, &v, 26.4f);
            func_00187B48((void *)&g->rim[i].c, &v, 27.0f);
        }
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    if (g->t == 0xDC) {
        func_001F53C0(1, g->unitA, &g->pos);
    }
    func_001F5620(g->unitA, g->jn, &g->jp);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
    g->scr0.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr0.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr0.z = func_0017B340(xyz.z);
    g->scr0.w = 1.0f;
    if (g->scr0.x < 0.0f) {
        g->scr0.x = 0.0f;
    }
    if (g->scr0.x > 640.0f) {
        g->scr0.x = 640.0f;
    }
    if (g->scr0.y < 0.0f) {
        g->scr0.y = 0.0f;
    }
    if (g->scr0.y > 448.0f) {
        g->scr0.y = 448.0f;
    }
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

    if (g->t == 0x171) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b730_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b730_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b730_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b730_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b730_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x5E - g->t2) * 0x55 / 94;
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
                ((Uv_b730_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b730_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b730_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b730_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b730_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b730_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        if (g->t2 > 0x5E) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x171) {
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
                func_00101080(&g->burst[g->cur].v[i], 2.5f);
            }
            for (i = 0; i < 128; i++) {
                func_00101080(&g->burst[g->cur].w[i], 2.5f);
            }
            for (i = 0; i < 64; i++) {
                g->burst[g->cur].c2[i] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[g->cur].v3[i], 2.5f);
            }
        }
    }

    for (i = 0; i < 1; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        s = 15.0f * (0.8f + 0.2f * g->burst[i].t / 84.0f);
        cn[0].x = -s;
        cn[0].y = -s;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = s;
        cn[1].y = s;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (0x54 - g->burst[i].t) * 0xFF / 84;
        spr.c.r = 0x6C;
        spr.c.g = 0x48;
        spr.c.b = 0x9B;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[i].t, 0x54, 1);
        for (j = 0; j < 64; j++) {
            func_00187B48(&v, &g->burst[i].v3[j], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c2[j] % 4 * 32;
            y = (g->burst[i].c2[j] >> 2) * 32;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->burst[i].t / 84.0f);
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
        alpha = (0x54 - g->burst[i].t) * 0xFF / 84;
        a2 = (0x54 - g->burst[i].t) * 0x64 / 84;
        for (j = 0; j < 64; j++) {
            s = func_00100D50(g->burst[i].t, 0x54, 1);
            if (j % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x94;
                spr.c.g = 0xFF;
                spr.c.b = 0x80;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x6C;
                spr.c.g = 0x48;
                spr.c.b = 0x9B;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[i].v[j], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c[j] % 4 * 32;
            y = (g->burst[i].c[j] >> 2) * 32;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[i].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[i].t, 0x54, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(228.0f * ((f32)(0x54 - g->burst[i].t) / 84.0f));
        spr.c.r = 0x64;
        spr.c.g = 0x1E;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 195.0f;
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
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
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
        n = g->burst[i].t;
        f = (f32)(0x54 - n) / 84.0f;
        s = func_00100D50(n, 0x54, 1);
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 6; k++) {
                alpha = (u32)(f * ((k + 6) * 0xFF / 12));
                spr.c.r = 0xDC;
                spr.c.g = 0xB4;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[i].w[j], s + 0.007f * k);
                func_00187B00(&v, &v, &g->burst[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x54) {
            g->burst[i].on = 0;
        }
    }

    if (g->t > 0xEB) {
        if (g->tring % 33 == 0) {
            n = g->nring;
            if (n < 4) {
                g->ring[n].on = 1;
                g->ring[n].t = 0;
                g->nring++;
            }
        }
        g->tring++;
    }

    ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(1));
    for (i = 0; i < 4; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480((g->ring[i].t << 14) / 33));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        n = 0xC0 - i * 64;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = n << 4;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = (n + 64) << 4;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = 0x400;
        x = (s32)g->scr0.x;
        y = (s32)g->scr0.y;
        d = (s32)(70.0f * func_0020B480((g->ring[i].t << 14) / 33));
        spr.p0.x = (x - d + 0x6C0) << 4;
        spr.p0.y = (y - d + 0x720) << 4;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = (d + x + 0x6C0) << 4;
        spr.p1.y = (d + y + 0x720) << 4;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, ot, 0);
        g->ring[i].t++;
        if (g->ring[i].t > 0x21) {
            g->ring[i].on = 0;
        }
    }

    if (g->t == 0xDC) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Quad_b730_01E00080 *)(s32)&quad)->flags = 0x24;
        ((Quad_b730_01E00080 *)(s32)&quad)->size = 9;
        ((Quad_b730_01E00080 *)(s32)&quad)->regs = ((u64)4 << 32) | 0x24242421;
        ((Quad_b730_01E00080 *)(s32)&quad)->pad4 = 0;
        ((Quad_b730_01E00080 *)(s32)&quad)->flags |= 0x800;
        func_00208700(&quad, g->tex[4], 1);
        func_00208CB0(&quad, 5);
        func_002086D0(&quad, func_00208D00(0));
        alpha = (u32)(45.0f * func_00101020((f32)g->t3, 16.0f) * func_00100FF0((f32)g->t3, 149.0f, 133.0f));
        quad.c.r = 0x80;
        quad.c.g = 0x80;
        quad.c.b = 0x80;
        quad.c.a = alpha;
        quad.c.q = 1.0f;
        ((Uv_b730_01E00080 *)(s32)&quad.v[0].uv)->u = 0;
        ((Uv_b730_01E00080 *)(s32)&quad.v[0].uv)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&quad.v[1].uv)->u = 0x400;
        ((Uv_b730_01E00080 *)(s32)&quad.v[1].uv)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&quad.v[2].uv)->u = 0;
        ((Uv_b730_01E00080 *)(s32)&quad.v[2].uv)->v = 0x400;
        ((Uv_b730_01E00080 *)(s32)&quad.v[3].uv)->u = 0x400;
        ((Uv_b730_01E00080 *)(s32)&quad.v[3].uv)->v = 0x400;
        func_0020BBB0(&m4);
        func_00100E00(&m4, g->t3 * 0x457, 2);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                func_00187B48(&cn[j], &D_28BAF0[i][j], 100.0f);
                func_001878E0(&cn[j], &m4, &cn[j]);
                ix[j] = (s32)cn[j].x;
                iy[j] = (s32)cn[j].y;
            }
            x = (s32)g->scr0.x;
            y = (s32)g->scr0.y;
            quad.v[0].p.x = (ix[0] + x + 0x6C0) << 4;
            quad.v[0].p.y = (iy[0] + y + 0x720) << 4;
            quad.v[0].p.z = 0xFFFFF8;
            quad.v[0].p.f = 0;
            quad.v[1].p.x = (ix[1] + x + 0x6C0) << 4;
            quad.v[1].p.y = (iy[1] + y + 0x720) << 4;
            quad.v[1].p.z = 0xFFFFF8;
            quad.v[1].p.f = 0;
            quad.v[2].p.x = (ix[2] + x + 0x6C0) << 4;
            quad.v[2].p.y = (iy[2] + y + 0x720) << 4;
            quad.v[2].p.z = 0xFFFFF8;
            quad.v[2].p.f = 0;
            quad.v[3].p.x = (ix[3] + x + 0x6C0) << 4;
            quad.v[3].p.y = (iy[3] + y + 0x720) << 4;
            quad.v[3].p.z = 0xFFFFF8;
            quad.v[3].p.f = 0;
            func_002075F0(&quad, ot, 0);
        }
        g->t3++;
        if (g->t3 > 0x95) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x31) {
        g->on4 = 1;
        g->t4 = 0;
        g->pos4 = g->jp;
        for (i = 0; i < 128; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v4[i], 0.5f);
        }
    }
    if (g->on4 == 1) {
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos4);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t4, 18, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0x30;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 48.0f;
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
        ((Line_b730_01E00080 *)(s32)&line)->flags = 0x14;
        ((Line_b730_01E00080 *)(s32)&line)->size = 8;
        ((Line_b730_01E00080 *)(s32)&line)->regs = 0x41414141;
        ((Line_b730_01E00080 *)(s32)&line)->pad4 = 0;
        func_002086D0(&line, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos4);
        s = 0.1f + 0.9f * func_00100D50(g->t4, 18, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (18 - g->t4) * 0xFF / 18;
        line.v[0].c.r = 0xFF;
        line.v[0].c.g = 0x94;
        line.v[0].c.b = 0xE4;
        line.v[0].c.a = alpha;
        line.v[0].c.q = 1.0f;
        line.v[1].c = line.v[0].c;
        line.v[2].c.r = 0xFF;
        line.v[2].c.g = 0x12;
        line.v[2].c.b = 0x1C;
        line.v[2].c.a = 0;
        line.v[2].c.q = 1.0f;
        line.v[3].c = line.v[2].c;
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].a, &g->rim[i + 1].a, m, &line, &depth) == 1) {
                line.v[0].p.z = 0xFFFFF8;
                line.v[1].p.z = line.v[0].p.z;
                line.v[2].p.z = line.v[0].p.z;
                line.v[3].p.z = line.v[0].p.z;
                func_002075F0(&line, ot, 0);
            }
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].c, &g->rim[i + 1].c, m, &line, &depth) == 1) {
                line.v[0].p.z = 0xFFFFF8;
                line.v[1].p.z = line.v[0].p.z;
                line.v[2].p.z = line.v[0].p.z;
                line.v[3].p.z = line.v[0].p.z;
                func_002075F0(&line, ot, 0);
            }
        }
        ((Spr_b730_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b730_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b730_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b730_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b730_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (18 - g->t4) * 0xFF / 18;
        spr.c.r = 0xFF;
        spr.c.g = 0x30;
        spr.c.b = 0x80;
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
        for (i = 0; i < 128; i++) {
            x = g->c4[i] % 4 * 32;
            y = (g->c4[i] >> 2) * 32;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b730_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v4[i], s);
            func_00187B00(&v, &v, &g->pos4);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t4++;
        if (g->t4 > 18) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x135) {
        func_001F71A0(g->unitA, 0x3B, 0, &c0, &c1, 0);
    }
    func_001F6D00((u8)((func_00101050(0x1EF - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x167) {
        ret = 1;
    } else {
        if (g->t > 0x171 && g->t < 0x1C5) {
            ret = 6;
        }
        if (g->t == 0x1C5) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1EF) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
