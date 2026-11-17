#include "common.h"

/* shape b151:01E00080 (b151), 2513 insns, 1 copy: b151 scene manager (b724/b440 family, written from the asm): setup
   clears the 0x9920 scene, takes both units, five textures and unit B's position, builds a 9-point ring and 48 random
   directions; else lerps a point between the units (out on 0x32..0x63, back on 0xD0..0xFA), from 0xA a 0x10F-frame
   render-to-texture aura (func_001F7070 with func_01E027D0), at 0x7D/0x87/0x91/0x9B four 6-blade ring flowers, from
   0x14 a 0x105-frame twisted vortex (a 16x33 rippling grid drawn twice, the second through a screen copy) that drops
   16-slot ripple grids every 5th frame, and on 0x81..0xC7 18-slot 48-spark bursts and 12-slot 4-sprite bits at unit
   B; returns 1 / 6 / 2 / 8 at 0x76 / 0x81..0xC7 / 0xC8 / >0x118 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b151_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b151_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b151_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b151_01E00080;

typedef struct {
    Reg_b151_01E00080 a;
    Reg_b151_01E00080 b;
} Tx_b151_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b151_01E00080 c;
    Uv_b151_01E00080 uv0;
    Xyz_b151_01E00080 p0;
    Uv_b151_01E00080 uv1;
    Xyz_b151_01E00080 p1;
    u64 pad38;
    Tx_b151_01E00080 tx;
    u64 pad50;
} Spr_b151_01E00080;

typedef struct {
    Rgbaq_b151_01E00080 c;
    f32 s, t;
    Xyz_b151_01E00080 p;
} Tv_b151_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b151_01E00080 v[3];
    u64 pad58;
    Tx_b151_01E00080 tx;
    u64 pad70;
} Tri_b151_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b151_01E00080 v[4];
    u64 pad70;
    Tx_b151_01E00080 tx;
    u64 pad88;
} Quad_b151_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b151_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 len;
    s32 ang[6];
    u8 pad24[0xC];
    Vec4f v[6];
} Limb_b151_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[48];
    u8 pad38[8];
    Vec4f v[48];
} Spark_b151_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f v[4];
} Bit_b151_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 t0;
    u8 padC[4];
    Vec4f pos;
} Rip_b151_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    u8 pad24[0xC];
    Vec4f posA;
    Vec4f posB;
    Vec4f mid;
    u8 on1;
    u8 pad61[3];
    s32 t1;
    u8 pad68[8];
    Vec4f grid0[16][33];
    Vec4f grid1[16][33];
    Vec4f ring[9];
    Limb_b151_01E00080 limb[4];
    Vec4f dir[48];
    Spark_b151_01E00080 spark[18];
    Bit_b151_01E00080 bit[12];
    s32 nrip;
    u8 pad8684[0xC];
    Vec4f grid2[8][33];
    Rip_b151_01E00080 rip[16];
    u8 on2;
    u8 pad9911[3];
    s32 t2;
    u8 pad9918[8];
} Scene_b151_01E00080;

static s32 func_01E00080_b151(s32 arg0, s32 code) {
    Scene_b151_01E00080 *g = (Scene_b151_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F63F0(s32, s32, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00205CA0(void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_002087A0(void *, s32);
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
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern void b151_01E027D0();
    extern s32 D_01E02A80_b151;
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 c;
    s32 x;
    s32 y;
    s32 n;
    s32 a;
    u8 alpha;
    u8 al;
    u8 cr;
    u8 cg;
    u8 cb;
    f32 r;
    f32 h;
    f32 s;
    f32 f;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 u0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f p[4];
    Vec4f v;
    Vec4f w;
    Spr_b151_01E00080 spr __attribute__((aligned(8)));
    Tri_b151_01E00080 tri __attribute__((aligned(8)));
    Quad_b151_01E00080 quad __attribute__((aligned(8)));
    s32 xy[2];
    Rgbaq_b151_01E00080 cc __attribute__((aligned(8)));
    f32 depth;
    f32 depth2;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9920);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        func_001F53C0(1, g->unitB, &g->posB);
        g->on1 = 0;
        for (i = 0; i < 9; i++) {
            g->ring[i].x = 1.5f * func_0020B550((i << 16) >> 3);
            g->ring[i].y = 0.0f;
            g->ring[i].z = 1.5f * func_0020B480((i << 16) >> 3);
            g->ring[i].w = 1.0f;
        }
        for (i = 0; i < 4; i++) {
            g->limb[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            func_00101080(&g->dir[i], 1.5f);
        }
        for (i = 0; i < 18; i++) {
            g->spark[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->bit[i].on = 0;
        }
        g->nrip = 0;
        for (i = 0; i < 16; i++) {
            g->rip[i].on = 0;
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    if (g->t < 0xD0) {
        f = func_00101050(g->t - 0x32, 0, 49) / 49.0f;
        a = (s32)(32768.0f * f);
        a &= 0xFFFF;
        s1 = 0.5f * (1.0f - func_0020B480(a));
        func_00187B18(&v, &g->posB, &g->posA);
        func_00187B48(&v, &v, s1);
        func_00187B00(&g->mid, &v, &g->posA);
        a = (s32)(65536.0f * f);
        a &= 0xFFFF;
        g->mid.x = 10.0f * func_0020B550(a);
    } else {
        f = func_00101050(g->t - 0xD0, 0, 42) / 42.0f;
        a = (s32)(32768.0f * f);
        a &= 0xFFFF;
        s1 = 0.5f * (1.0f - func_0020B480(a));
        func_00187B18(&v, &g->posA, &g->posB);
        func_00187B48(&v, &v, s1);
        func_00187B00(&g->mid, &v, &g->posB);
        a = (s32)(65536.0f * f);
        a &= 0xFFFF;
        g->mid.x = 10.0f * func_0020B550(a);
    }
    g->mid.y = 36.0f;

    if (g->t == 0xA) {
        g->on2 = 1;
        g->t2 = 0;
    }
    func_001F63F0(g->unitA, 0, 0);
    if (g->on2 == 1) {
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        ((Spr_b151_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b151_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b151_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b151_01E00080 *)(s32)&spr)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        D_01E02A80_b151 = (s32)g;
        func_001F7070(1, &spr.tx.a, &spr.tx.b, 0, b151_01E027D0);
        func_00208460();
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        x = 0;
        ((Spr_b151_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b151_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b151_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b151_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b151_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x10E) {
            g->on2 = 0;
            func_001F63F0(g->unitA, 0, 0);
        }
    }

    a = -1;
    switch (g->t) {
    case 0x7D:
        a = 0;
        break;
    case 0x87:
        a = 1;
        break;
    case 0x91:
        a = 2;
        break;
    case 0x9B:
        a = 3;
        break;
    }
    if (a >= 0) {
        g->limb[a].on = 1;
        g->limb[a].t = 0;
        if (a == 3) {
            g->limb[a].len = 0x31;
        } else {
            g->limb[a].len = 0x10;
        }
        for (i = 0; i < 6; i++) {
            g->limb[a].ang[i] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->limb[a].v[i], 0.5f);
            g->limb[a].v[i].y = 0.0f;
        }
    }

    ((Tri_b151_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b151_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b151_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b151_01E00080 *)(s32)&tri)->pad4 = 0;
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    func_002087A0(&tri, 1);
    for (i = 0; i < 4; i++) {
        if (g->limb[i].on == 0) {
            continue;
        }
        h = func_00100FF0((f32)g->limb[i].t, (f32)g->limb[i].len, (f32)(g->limb[i].len - 4));
        r = func_00101020((f32)g->limb[i].t, 4.0f);
        r *= h;
        w.x = r;
        w.y = r;
        w.z = r;
        w.w = 1.0f;
        for (j = 0; j < 6; j++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B00(&v, &g->limb[i].v[j], &g->mid);
            func_00187B60(m2, m2, &v);
            func_00100E00(m2, g->limb[i].ang[j], 1);
            func_0020CB20(m2, &w);
            func_0020BC00(m, m2);
            v.x = 0.0f;
            v.y = 30.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            for (k = 0; k < 8; k++) {
                s = func_0020B550((k << 15) >> 3);
                cr = (u32)(255.0f * s);
                (void)cr;
                cg = (u32)(64.0f * s);
                (void)cg;
                cb = (u32)(64.0f * s);
                (void)cb;
                tri.v[1].c.r = cr;
                tri.v[1].c.g = cg;
                tri.v[1].c.b = cb;
                tri.v[1].c.a = 0x80;
                tri.v[1].c.q = 1.0f;
                tri.v[0].c = tri.v[1].c;
                s = func_0020B550(((k + 1) << 15) >> 3);
                tri.v[2].c.r = (u32)(255.0f * s);
                tri.v[2].c.g = (u32)(64.0f * s);
                tri.v[2].c.b = (u32)(64.0f * s);
                tri.v[2].c.a = 0x80;
                tri.v[2].c.q = 1.0f;
                tri.v[0].s = 0.3125f;
                tri.v[0].t = 0.0f;
                tri.v[1].s = 640.0f * k / 8.0f / 1024.0f;
                tri.v[1].t = 0.875f;
                tri.v[2].s = 640.0f * (k + 1) / 8.0f / 1024.0f;
                tri.v[2].t = 0.875f;
                if (func_00100B00(&v, &g->ring[k], &g->ring[k + 1], m, &tri, &depth) == 1) {
                    func_002075F0(&tri, ot, (u32)depth);
                }
            }
        }
        g->limb[i].t++;
        if (g->limb[i].t > g->limb[i].len) {
            g->limb[i].on = 0;
        }
    }

    if (g->t == 0x14) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        func_00205440(&g->mid, m, xy, &depth2);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->mid);
        func_0020BC00(m, m2);
        if ((g->t > 0x32 && g->t < 0x63) || (g->t > 0xD0 && g->t < 0xFA)) {
            if (g->t % 5 == 0) {
                n = g->nrip;
                (void)n;
                g->rip[n].on = 1;
                g->rip[n].t = 0;
                g->rip[n].t0 = g->t1;
                g->rip[n].pos = g->mid;
                g->nrip++;
                if (g->nrip >= 16) {
                    g->nrip = 0;
                }
            }
        }
        for (i = 0; i < 16; i++) {
            r = 17.5f * (16 - i) / 16.0f;
            for (j = 0; j < 33; j++) {
                x = ((j * 0x60000 >> 5) + g->t1 * 0x1C8) & 0xFFFF;
                c = ((j * 0x20000 >> 5) + g->t1 * 0x457) & 0xFFFF;
                h = 0.1f * func_0020B550(x);
                s = r * (0.9f + h * func_0020B550(c));
                c = (j << 16) >> 5;
                g->grid0[i][j].x = s * func_0020B550(c);
                g->grid0[i][j].y = 0.0f;
                g->grid0[i][j].z = s * func_0020B480(c);
                g->grid0[i][j].w = 1.0f;
            }
        }
        ((Quad_b151_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b151_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b151_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b151_01E00080 *)(s32)&quad)->pad4 = 0;
        func_002086D0(&quad, func_00208D00(1));
        func_00208700(&quad, g->tex[2], 1);
        func_00208CB0(&quad, 0);
        f = func_00101020((f32)g->t1, 30.0f);
        al = (u32)(255.0f * (f * func_00100FF0((f32)g->t1, 260.0f, 230.0f)));
        quad.v[0].c.r = 0xFF;
        quad.v[0].c.g = 0x30;
        quad.v[0].c.b = 0x30;
        quad.v[0].c.a = al;
        quad.v[0].c.q = 1.0f;
        quad.v[1].c = quad.v[0].c;
        quad.v[2].c = quad.v[0].c;
        quad.v[3].c = quad.v[0].c;
        h = 0.5f * (g->t1 % 64) / 64.0f;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 16; i++) {
            if (i == 0) {
                quad.v[0].c.a = 0;
                quad.v[1].c.a = 0;
            } else {
                quad.v[0].c.a = al;
                quad.v[1].c.a = al;
            }
            t0 = 0.5f * i / 16.0f;
            t1 = 0.5f * (i + 1) / 16.0f;
            if (i == 15) {
                u0 = t0 + h;
                u1 = t1 + h;
                for (j = 0; j < 32; j++) {
                    s0 = 0.5f * j / 32.0f;
                    s1 = 0.5f * (j + 1) / 32.0f;
                    quad.v[0].s = s0;
                    quad.v[0].t = u0;
                    quad.v[1].s = s1;
                    quad.v[1].t = u0;
                    quad.v[2].s = s0;
                    quad.v[2].t = u1;
                    quad.v[3].s = s1;
                    quad.v[3].t = u1;
                    if (func_00100BA0(&g->grid0[i][j], &g->grid0[i][j + 1], &v, &v, m, &quad, &depth) == 1) {
                        func_002075F0(&quad, ot, (u32)depth2);
                    }
                }
            } else {
                u0 = t0 + h;
                u1 = t1 + h;
                for (j = 0; j < 32; j++) {
                    s0 = 2.0f * j / 32.0f;
                    s1 = 2.0f * (j + 1) / 32.0f;
                    quad.v[0].s = s0;
                    quad.v[0].t = u0;
                    quad.v[1].s = s1;
                    quad.v[1].t = u0;
                    quad.v[2].s = s0;
                    quad.v[2].t = u1;
                    quad.v[3].s = s1;
                    quad.v[3].t = u1;
                    if (func_00100BA0(&g->grid0[i][j], &g->grid0[i][j + 1], &g->grid0[i + 1][j],
                                      &g->grid0[i + 1][j + 1], m, &quad, &depth) == 1) {
                        func_002075F0(&quad, ot, (u32)depth2);
                    }
                }
            }
        }
        ((Tri_b151_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b151_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b151_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b151_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Quad_b151_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b151_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b151_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b151_01E00080 *)(s32)&quad)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
        quad.tx.a = tri.tx.a;
        quad.tx.b = tri.tx.b;
        func_00208460();
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        ((Tri_b151_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&quad, func_00208D00(0));
        func_00208CB0(&quad, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b151_01E00080 *)(s32)&quad)->flags |= 0x800;
        f = func_00101020((f32)g->t1, 30.0f);
        al = (u32)(128.0f * (f * func_00100FF0((f32)g->t1, 260.0f, 230.0f)));
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0x44;
        tri.v[0].c.b = 0x44;
        tri.v[0].c.a = al;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        cc = tri.v[0].c;
        quad.v[0].c = cc;
        quad.v[1].c = cc;
        quad.v[2].c = cc;
        quad.v[3].c = cc;
        for (i = 0; i < 16; i++) {
            r = 17.5f * (16 - i) / 16.0f;
            s0 = (f32)(i + 1) / 16.0f;
            for (j = 0; j < 33; j++) {
                h = 1.0f + s0 * (0.2f * func_0020B480((u16)(g->t1 * 0x83F + ((i * 0x20000 >> 4) + (j * 0x20000 >> 5)))));
                a = (u16)(s32)((f32)(j * 0x10000 >> 5) + s0 * (1456.0f * func_0020B480((u16)((i * 0x10000 >> 4) + g->t1 * 0x457))));
                g->grid1[i][j].x = r * h * func_0020B550(a);
                g->grid1[i][j].y = 0.0f;
                g->grid1[i][j].z = r * h * func_0020B480(a);
                g->grid1[i][j].w = 1.0f;
            }
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 16; i++) {
            if (i == 15) {
                for (j = 0; j < 32; j++) {
                    if (func_00100B00(&v, &g->grid1[i][j], &g->grid1[i][j + 1], m, &tri, &depth) == 1) {
                        func_00100C60(&tri.v[0].s, &tri.v[0].p, 0, 0);
                        func_00100C60(&tri.v[1].s, &tri.v[1].p, 0, 0);
                        func_00100C60(&tri.v[2].s, &tri.v[2].p, 0, 0);
                        if (func_00100B00(&v, &g->grid0[i][j], &g->grid0[i][j + 1], m, &tri, &depth) == 1) {
                            func_002075F0(&tri, 0, 0);
                        }
                    }
                }
            } else {
                if (i == 0) {
                    quad.v[0].c.a = 0;
                    quad.v[1].c.a = 0;
                } else {
                    quad.v[0].c.a = al;
                    quad.v[1].c.a = al;
                }
                for (j = 0; j < 32; j++) {
                    if (func_00100BA0(&g->grid1[i][j], &g->grid1[i][j + 1], &g->grid1[i + 1][j],
                                      &g->grid1[i + 1][j + 1], m, &quad, &depth) == 1) {
                        func_00100C60(&quad.v[0].s, &quad.v[0].p, 0, 0);
                        func_00100C60(&quad.v[1].s, &quad.v[1].p, 0, 0);
                        func_00100C60(&quad.v[2].s, &quad.v[2].p, 0, 0);
                        func_00100C60(&quad.v[3].s, &quad.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid0[i][j], &g->grid0[i][j + 1], &g->grid0[i + 1][j],
                                          &g->grid0[i + 1][j + 1], m, &quad, &depth) == 1) {
                            func_002075F0(&quad, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(buf, ot, (u32)depth2);
        g->t1++;
        if (g->t1 > 0x104) {
            g->on1 = 0;
        }
    }

    if (g->t > 0x80 && g->t < 0xC8) {
        n = g->t % 18;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (i = 0; i < 48; i++) {
            g->spark[n].c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&v, 0.5f);
            func_00187B00(&g->spark[n].v[i], &v, &g->dir[i]);
        }
    }

    ((Spr_b151_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b151_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b151_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b151_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b151_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 18; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 1.0f;
        alpha = (u32)(r * (50.0f * func_00100FF0((f32)g->spark[i].t, 18.0f, 12.0f)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.8f + 0.2f * func_00100D50(g->spark[i].t, 18, 1));
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
        s = 0.05f + (f32)g->spark[i].t / 18.0f;
        h = 12.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->spark[i].t, 2.0f)));
        for (j = 0; j < 48; j++) {
            x = g->spark[i].c[j] % 4 * 32;
            y = (g->spark[i].c[j] >> 2) * 32;
            ((Uv_b151_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->spark[i].v[j], s);
            func_00187B00(&v, &v, &g->posB);
            v.y += h;
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 18) {
            g->spark[i].on = 0;
        }
    }

    if (g->t > 0x80 && g->t < 0xC8) {
        n = g->t % 12;
        (void)n;
        g->bit[n].on = 1;
        g->bit[n].t = 0;
        for (i = 0; i < 4; i++) {
            g->bit[n].c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->bit[n].v[i], 1.3f);
        }
    }

    ((Spr_b151_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b151_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b151_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b151_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b151_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[3], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 12; i++) {
        if (g->bit[i].on == 0) {
            continue;
        }
        r = 1.0f;
        alpha = (u32)(r * (50.0f * func_0020B480((g->bit[i].t << 14) / 12)));
        spr.c.r = 0xC8;
        spr.c.g = 0;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f;
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
        s = 0.3f + 0.7f * g->bit[i].t / 12.0f;
        for (j = 0; j < 4; j++) {
            x = g->bit[i].c[j] % 4 * 32;
            y = (g->bit[i].c[j] >> 2) * 32;
            ((Uv_b151_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b151_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->bit[i].v[j], s);
            func_00187B00(&v, &v, &g->posB);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->bit[i].t++;
        if (g->bit[i].t > 12) {
            g->bit[i].on = 0;
        }
    }

    for (i = 0; i < 16; i++) {
        if (g->rip[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        func_00205440(&g->mid, m, xy, &depth2);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->rip[i].pos);
        func_0020BC00(m, m2);
        for (y = 0; y < 8; y++) {
            r = 17.5f * (8 - y) / 8.0f;
            for (j = 0; j < 33; j++) {
                x = ((j * 0x60000 >> 5) + g->rip[i].t0 * 0x1C8) & 0xFFFF;
                a = ((j * 0x20000 >> 5) + g->rip[i].t0 * 0x457) & 0xFFFF;
                h = 0.1f * func_0020B550(x);
                s = r * (0.9f + h * func_0020B550(a));
                a = (j << 16) >> 5;
                g->grid2[y][j].x = s * func_0020B550(a);
                g->grid2[y][j].y = 0.0f;
                g->grid2[y][j].z = s * func_0020B480(a);
                g->grid2[y][j].w = 1.0f;
            }
        }
        ((Quad_b151_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b151_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b151_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b151_01E00080 *)(s32)&quad)->pad4 = 0;
        func_002086D0(&quad, func_00208D00(0));
        func_00208700(&quad, g->tex[4], 1);
        func_00208CB0(&quad, 0);
        al = (u32)(100.0f * ((f32)(16 - g->rip[i].t) / 16.0f));
        quad.v[0].c.r = 0xFF;
        quad.v[0].c.g = 0x40;
        quad.v[0].c.b = 0x40;
        quad.v[0].c.a = al;
        quad.v[0].c.q = 1.0f;
        quad.v[1].c = quad.v[0].c;
        quad.v[2].c = quad.v[0].c;
        quad.v[3].c = quad.v[0].c;
        h = 0.5f * (g->rip[i].t % 64) / 64.0f;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (y = 0; y < 8; y++) {
            if (y == 0) {
                quad.v[0].c.a = 0;
                quad.v[1].c.a = 0;
            } else {
                quad.v[0].c.a = al;
                quad.v[1].c.a = al;
            }
            t0 = 0.5f * y / 8.0f;
            t1 = 0.5f * (y + 1) / 8.0f;
            if (y == 7) {
                u0 = t0 + h;
                u1 = t1 + h;
                for (j = 0; j < 32; j++) {
                    s0 = 0.5f * j / 32.0f;
                    s1 = 0.5f * (j + 1) / 32.0f;
                    quad.v[0].s = s0;
                    quad.v[0].t = u0;
                    quad.v[1].s = s1;
                    quad.v[1].t = u0;
                    quad.v[2].s = s0;
                    quad.v[2].t = u1;
                    quad.v[3].s = s1;
                    quad.v[3].t = u1;
                    if (func_00100BA0(&g->grid2[y][j], &g->grid2[y][j + 1], &v, &v, m, &quad, &depth) == 1) {
                        func_002075F0(&quad, ot, (u32)depth2);
                    }
                }
            } else {
                u0 = t0 + h;
                u1 = t1 + h;
                for (j = 0; j < 32; j++) {
                    s0 = 2.0f * j / 32.0f;
                    s1 = 2.0f * (j + 1) / 32.0f;
                    quad.v[0].s = s0;
                    quad.v[0].t = u0;
                    quad.v[1].s = s1;
                    quad.v[1].t = u0;
                    quad.v[2].s = s0;
                    quad.v[2].t = u1;
                    quad.v[3].s = s1;
                    quad.v[3].t = u1;
                    if (func_00100BA0(&g->grid2[y][j], &g->grid2[y][j + 1], &g->grid2[y + 1][j],
                                      &g->grid2[y + 1][j + 1], m, &quad, &depth) == 1) {
                        func_002075F0(&quad, ot, (u32)depth2);
                    }
                }
            }
        }
        g->rip[i].t++;
        if (g->rip[i].t > 16) {
            g->rip[i].on = 0;
        }
    }

    if (g->t == 0x76) {
        ret = 1;
    } else {
        if (g->t > 0x80 && g->t < 0xC8) {
            ret = 6;
        }
        if (g->t == 0xC8) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x118) {
        ret = 8;
    }
    return ret;
}

/* shape b151:01E027D0 (Gb151_GenAuraTex), 143 insns, 1 copy: draws a full-screen red-pink flash: a 5-reg sprite
   packet with integer UVs (0,0 to 640,448), its alpha 255 x func_00101020(t, 30) x func_00100FF0(t, 270, 240) from
   the module scene's timer (0x9914), sent through the frame's draw context */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b151_01E027D0;

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_b151_01E027D0;

typedef struct {
    Uv_b151_01E027D0 st;
    Xyz_b151_01E027D0 p;
} Tv_b151_01E027D0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b151_01E027D0 v[2];
    u8 tail[8];
} Pkt_b151_01E027D0;

typedef struct {
    u8 pad0[0x9914];
    s32 t;
} Scene_b151_01E027D0;

extern Scene_b151_01E027D0 *D_01E02A80_b151;

static void func_01E027D0_b151(void *ctx) {
    extern s32 func_00207650(s32, void *, s32, s32);
    Pkt_b151_01E027D0 pk __attribute__((aligned(8)));
    s32 o98[2];
    s32 oA0[3];
    Scene_b151_01E027D0 *s;
    s32 a;
    f32 f;

    s = D_01E02A80_b151;
    ctx = func_00209F70(ctx, 0xFF000000);
    ((Pkt_b151_01E027D0 *)(u32)&pk)->count = 0x26;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->n = 5;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->regs = 0x42421;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->pad4 = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, o98, oA0));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Pkt_b151_01E027D0 *)(u32)&pk)->count |= 0x800;
    f = 255.0f * func_00101020(s->t, 30.0f);
    a = (u32)(f * func_00100FF0(s->t, 270.0f, 240.0f));
    pk.r = 0xFF;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = a;
    pk.q = 1.0f;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[0].st)->s = 0;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[0].st)->t = 0;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[1].st)->s = 0x2800;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[1].st)->t = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    func_00209F70((void *)func_00207650((s32)ctx, &pk, 0, 0), 0);
}

