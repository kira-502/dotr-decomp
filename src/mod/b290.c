#include "common.h"

/* shape b290:01E00080 (b290), 1725 insns, 1 copy: b290 module main (written from the asm, b507/b261 family): code >=
   0 clears the scene, takes both units, five textures and the target's top, builds a 17-point double ring; else on
   ticks 0..304 draws four fading textured quads (two passes) above the unit, on 89..239 spawns a beam toward the top
   in 64 slots that walks a parabola for 65 frames leaving 4-sprite puffs (64x8 slots) and at frame 63 a spinning ring
   swirl (32 slots) drawn as a 16-segment textured strip plus a sprite; passes a tick-faded level to func_001F6D00 and
   returns 1 / 6 / 2 / 8 at 142 / 153..335 / 336 / 369 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b290_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b290_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b290_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b290_01E00080 c;
    Uv_b290_01E00080 uv0;
    Xyz_b290_01E00080 p0;
    Uv_b290_01E00080 uv1;
    Xyz_b290_01E00080 p1;
    u8 tail[0x20];
} Spr_b290_01E00080;

typedef struct {
    Rgbaq_b290_01E00080 c;
    f32 s, t;
    Xyz_b290_01E00080 p;
} Tv_b290_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b290_01E00080 v[4];
    u8 tail[0x20];
} Tex_b290_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b290_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 n;
    f32 len[1];
    Mtx_b290_01E00080 mat[1];
} Beam_b290_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    f32 sc;
    Vec4f pos;
    Vec4f v[4];
} Puff_b290_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b290_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Mtx_b290_01E00080 mat;
} Swirl_b290_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    u8 pad24[0xC];
    Vec4f top;
    u8 on;
    u8 pad41[3];
    s32 t44;
    u8 pad48[8];
    Beam_b290_01E00080 a[64];
    Puff_b290_01E00080 b[64][1][8];
    Ring_b290_01E00080 ring[17];
    s32 nc[1];
    u8 padD784[0xC];
    Swirl_b290_01E00080 c[1][32];
} Scene_b290_01E00080;

static s32 func_01E00080_b290(s32 arg0, s32 code) {
    Scene_b290_01E00080 *g = (Scene_b290_01E00080 *)arg0;
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
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_00205CA0(void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00101080(void *, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    extern Vec4f D_28BAF0[4][4];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 n;
    s32 c;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 u;
    f32 u5;
    f32 u1;
    f32 s0;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Vec4f v;
    Vec4f w;
    Tex_b290_01E00080 pk __attribute__((aligned(8)));
    Spr_b290_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xE390);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        func_001F53C0(1, g->unitB, &g->top);
        g->on = 0;
        for (i = 0; i < 64; i++) {
            g->a[i].on = 0;
            g->a[i].n = 0;
        }
        for (i = 0; i < 64; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 8; k++) {
                    g->b[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 17; i++) {
            ang = (i << 16) >> 4;
            g->ring[i].a.x = 10.0f * func_0020B550(ang);
            g->ring[i].a.y = 10.0f * func_0020B480(ang);
            g->ring[i].a.z = 0.0f;
            g->ring[i].a.w = 1.0f;
            g->ring[i].b.x = 35.0f * func_0020B550(ang);
            g->ring[i].b.y = 35.0f * func_0020B480(ang);
            g->ring[i].b.z = 0.0f;
            g->ring[i].b.w = 1.0f;
            func_00187B00(&g->ring[i].mid, &g->ring[i].a, &g->ring[i].b);
            { Vec4f *pm = &g->ring[i].mid; func_00187B48(pm, pm, 0.5f); }
        }
        for (j = 0; j < 1; j++) {
            g->nc[j] = 0;
            for (k = 0; k < 32; k++) {
                g->c[j][k].on = 0;
            }
        }
        return 0;
    }
    func_00205CA0(m3);
    if (g->t == 0) {
        g->on = 1;
        g->t44 = 0;
    }
    if (g->on == 1) {
        ((Tex_b290_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Tex_b290_01E00080 *)(s32)&pk)->size = 0xC;
        ((Tex_b290_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Tex_b290_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208CB0(&pk, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        v.x = 0.0f;
        v.y = 52.0f;
        v.z = 95.0f * g->obj;
        v.w = 1.0f;
        func_00187B60(m2, m2, &v);
        func_0020BC00(m, m2);
        f = (f32)func_00101050(g->t44, 0, 32) * (f32)func_00101050(0x130 - g->t44, 0, 32) / 1024.0f;

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                func_00187B48(&cn[j], &D_28BAF0[i][j], 12.0f * f);
            }
            func_00208700(&pk, g->tex[0], 1);
            func_002086D0(&pk, func_00208D00(0));
            pk.v[0].s = 0.0f;
            pk.v[0].t = 0.0f;
            pk.v[1].s = 1.0f;
            pk.v[1].t = 0.0f;
            pk.v[2].s = 0.0f;
            pk.v[2].t = 1.0f;
            pk.v[3].s = 1.0f;
            pk.v[3].t = 1.0f;
            ang = (g->t44 % 32 << 15) >> 5;
            (void)ang;
            alpha = (u32)((0.8f + 0.2f * (g->t44 % 2)) * (80.0f * f * func_0020B550(ang)));
            pk.v[0].c.r = 0x80;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0x80;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
            pk.v[0].s = 0.0f;
            pk.v[0].t = 0.0f;
            pk.v[1].s = 1.0f;
            pk.v[1].t = 0.0f;
            pk.v[2].s = 0.0f;
            pk.v[2].t = 1.0f;
            pk.v[3].s = 1.0f;
            pk.v[3].t = 1.0f;
            ang += 0x4000;
            ang &= 0xFFFF;
            alpha = (u32)((0.8f + 0.2f * (g->t44 % 2)) * (255.0f * f * f * func_001A6970(func_0020B550(ang))));
            pk.v[0].c.r = 0xFF;
            pk.v[0].c.g = 0xFF;
            pk.v[0].c.b = 0x80;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            func_00208700(&pk, g->tex[1], 1);
            func_002086D0(&pk, func_00208D00(1));
            if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->t44++;
        if (g->t44 > 0x130) {
            g->on = 0;
        }
    }

    if (g->t > 0x58 && g->t < 0xF0) {
        n = g->t;
        n %= 64;
        g->a[n].on = 1;
        g->a[n].t = 0;
        w.x = 0.0f;
        w.y = 52.0f;
        w.z = 95.0f * g->obj;
        w.w = 1.0f;
        for (j = 0; j < 1; j++) {
            func_00101080(&v, 1.0f);
            func_00187B00(&v, &v, &g->top);
            func_00187B18(&v, &v, &w);
            g->a[n].len[j] = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
            func_00100E40(&g->a[n].mat[j], &v);
            func_00100E00(&g->a[n].mat[j], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
    }

    ((Spr_b290_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b290_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b290_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b290_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b290_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
    w.x = 0.0f;
    w.y = 52.0f;
    w.z = 95.0f * g->obj;
    w.w = 1.0f;
    for (i = 0; i < 64; i++) {
        if (g->a[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0x28;
        spr.c.b = 0x14;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        f = func_001A6C48(g->a[i].t / 64.0f, 2.0f);
        h = 4.0f * f + -4.0f * f * f;
        n = g->a[i].n;
        g->a[i].n++;
        if (g->a[i].n >= 8) {
            g->a[i].n = 0;
        }
        for (j = 0; j < 1; j++) {
            v.x = 0.0f;
            v.y = 40.0f * h;
            v.z = f * g->a[i].len[j];
            v.w = 1.0f;
            func_001878E0(&v, &g->a[i].mat[j], &v);
            func_00187B00(&v, &v, &w);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->b[i][j][n].on = 1;
            g->b[i][j][n].t = 0;
            g->b[i][j][n].sc = 0.3f + 0.7f * g->a[i].t / 64.0f;
            g->b[i][j][n].pos = v;
            for (k = 0; k < 4; k++) {
                g->b[i][j][n].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->b[i][j][n].v[k], 0.2f * g->b[i][j][n].sc);
            }
            if (g->a[i].t == 0x3F) {
                c = g->nc[j];
                g->c[j][c].on = 1;
                g->c[j][c].t = 0;
                g->c[j][c].pos = v;
                func_0020BBB0(&g->c[j][c].mat);
                func_00100E00(&g->c[j][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 0);
                func_00100E00(&g->c[j][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 1);
                func_00100E00(&g->c[j][c].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->nc[j]++;
                if (g->nc[j] >= 32) {
                    g->nc[j] = 0;
                }
            }
        }
        g->a[i].t++;
        if (g->a[i].t > 64) {
            g->a[i].on = 0;
        }
    }

    ((Spr_b290_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b290_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b290_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b290_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b290_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 8; k++) {
                if (g->b[i][j][k].on == 0) {
                    continue;
                }
                r = 6.5f * (0.5f + 0.5f * g->b[i][j][k].t / 8.0f);
                r *= g->b[i][j][k].sc;
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
                alpha = (8 - g->b[i][j][k].t) * 255 >> 3;
                spr.c.r = 0xFF;
                spr.c.g = 0x3C;
                spr.c.b = 0x14;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->b[i][j][k].t, 8, 1);
                for (q = 0; q < 4; q++) {
                    c = g->b[i][j][k].c[q];
                    x = c % 4 * 32;
                    y = (c >> 2) * 32;
                    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->b[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->b[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->b[i][j][k].t++;
                if (g->b[i][j][k].t > 8) {
                    g->b[i][j][k].on = 0;
                }
            }
        }
    }

    ((Tex_b290_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b290_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b290_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b290_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[4], 1);
    func_00208CB0(&pk, 0);
    ((Spr_b290_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b290_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b290_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b290_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b290_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b290_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b290_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 20.0f;
    cn[0].x = -r;
    cn[0].y = -r;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = r;
    cn[1].y = r;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 32; j++) {
            if (g->c[i][j].on == 0) {
                continue;
            }
            f = func_00100FF0((f32)g->c[i][j].t, 32.0f, 16.0f);
            pk.v[0].c.r = 0x40;
            pk.v[0].c.g = 0x10;
            pk.v[0].c.b = 0x08;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            alpha = (u32)(128.0f * f);
            (void)alpha;
            pk.v[2].c.r = 0xFF;
            pk.v[2].c.g = 0x3C;
            pk.v[2].c.b = 0x14;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->c[i][j].pos);
            func_0020BC00(m2, &g->c[i][j].mat);
            s = 0.1f + 0.9f * func_00100D50(g->c[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = 0.0f;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            u = -1.0f * (g->c[i][j].t % 32) / 32.0f;
            u5 = 0.5f + u;
            u1 = 1.0f + u;
            for (q = 0; q < 16; q++) {
                s0 = 6.0f * q / 16.0f;
                s1 = 6.0f * (q + 1) / 16.0f;
                pk.v[0].s = s0;
                pk.v[0].t = u;
                pk.v[1].s = s1;
                pk.v[1].t = u;
                pk.v[2].s = s0;
                pk.v[2].t = u5;
                pk.v[3].s = s1;
                pk.v[3].t = u5;
                if (func_00100BA0(&g->ring[q].a, &g->ring[q + 1].a, &g->ring[q].mid, &g->ring[q + 1].mid, m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
                pk.v[0].s = s0;
                pk.v[0].t = u1;
                pk.v[1].s = s1;
                pk.v[1].t = u1;
                pk.v[2].s = s0;
                pk.v[2].t = u5;
                pk.v[3].s = s1;
                pk.v[3].t = u5;
                if (func_00100BA0(&g->ring[q].b, &g->ring[q + 1].b, &g->ring[q].mid, &g->ring[q + 1].mid, m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
            alpha = (u32)(255.0f * func_00100FF0((f32)g->c[i][j].t, 32.0f, 16.0f));
            spr.c.r = 0xFF;
            spr.c.g = 0x56;
            spr.c.b = 0x28;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->c[i][j].pos);
            s = 0.1f + 0.9f * func_00100D50(g->c[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = s;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->c[i][j].t++;
            if (g->c[i][j].t > 32) {
                g->c[i][j].on = 0;
            }
        }
    }

    func_001F6D00((u8)((func_00101050(0x170 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x8E) {
        ret = 1;
    } else {
        if (g->t > 0x98 && g->t < 0x150) {
            ret = 6;
        }
        if (g->t == 0x150) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x170) {
        ret = 8;
    }
    return ret;
}
