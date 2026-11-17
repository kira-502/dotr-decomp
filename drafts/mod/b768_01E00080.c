#include "common.h"

/* shape b768:01E00080 (b768), 1858 insns, 1 copy: b768 scene manager (b584:01E00080's family; best draft, 12 words
   off): setup clears the 0x4980 scene, takes both units, four textures and the target; else projects joint-tracked
   point A to the screen (clamped to 640x448), every 18 frames from 0xBC spawns one of 8 orbs between the units (32
   jittered points drawn as rotated quads), each mature orb spawns 6-spark puffs (two sprite passes and a spinning
   quad pass), a fading full-screen flash on 0xD6..0x1CD, and from 0x66 a render-to-texture aura (func_001F7070 with
   func_01E01D90) drawn as 3x8 screen triangles; returns 1 / 6 / 2 / 8 at 0x118 / 0x123..0x1BC / 0x1BD / >0x1FD */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b768_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b768_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b768_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b768_01E00080 c;
    Uv_b768_01E00080 uv0;
    Xyz_b768_01E00080 p0;
    Uv_b768_01E00080 uv1;
    Xyz_b768_01E00080 p1;
    u8 tail[0x20];
} Spr_b768_01E00080;

typedef struct {
    Uv_b768_01E00080 uv;
    Xyz_b768_01E00080 p;
} Qv_b768_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b768_01E00080 c;
    Qv_b768_01E00080 v[4];
    u8 tail[0x20];
} Quad_b768_01E00080;

typedef struct {
    Rgbaq_b768_01E00080 c;
    Uv_b768_01E00080 uv;
    Xyz_b768_01E00080 p;
} Tv_b768_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b768_01E00080 v[3];
    u8 tail[8];
} Tri_b768_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b768_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Vec4f pt[32];
} Orb_b768_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[6];
} Spark_b768_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f posA;
    Vec4f posA2;
    Vec4f posB;
    Vec4f scr;
    s32 n;
    u8 pad64[0xC];
    Orb_b768_01E00080 orb[8];
    Spark_b768_01E00080 spark[8][16];
    u8 on2;
    u8 pad4971[3];
    s32 t2;
    u8 pad4978[8];
} Scene_b768_01E00080;

static s32 func_01E00080_b768(s32 arg0, s32 code) {
    Scene_b768_01E00080 *g = (Scene_b768_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern void func_01E01D90_b768(void *);
    extern s32 D_01E02080_b768;
    extern u8 D_0030FF00[];
    extern Vec4f D_28B960[];
    s32 ret;
    s32 ot;
    s32 h;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 l;
    s32 p;
    s32 n;
    s32 x;
    s32 y;
    s32 a;
    u8 alpha;
    u8 alpha2;
    f32 r;
    f32 s;
    f32 f;
    f32 e;
    f32 b;
    f32 c;
    f32 d;
    f32 z;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b768_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b768_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    struct {
        Tri_b768_01E00080 pk;
        s32 a[2];
        s32 b[3];
    } w __attribute__((aligned(8)));
    Quad_b768_01E00080 pk __attribute__((aligned(8)));
    Spr_b768_01E00080 spr __attribute__((aligned(8)));
    Xyz_b768_01E00080 xy;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4980);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitA, &g->posA);
        func_001F53C0(1, g->unitB, &g->posB);
        g->n = 0;
        for (i = 0; i < 8; i++) {
            g->orb[i].on = 0;
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 16; j++) {
                g->spark[i][j].on = 0;
            }
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(&m3);
    func_001F53C0(1, g->unitA, &g->posA2);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->posA2, m, &xy, &depth);
    g->scr.x = (s32)(xy.x >> 4) - 0x6C0;
    g->scr.y = (s32)(xy.y >> 4) - 0x720;
    g->scr.z = xy.z;
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
    n = g->n;
    if (n < 8 && g->t == n * 18 + 0xBC) {
        g->orb[n].on = 1;
        g->orb[n].t = 0;
        s = 1.25f * (n + 2) / 8.0f;
        (void)s;
        func_00187B18(&v, &g->posB, &g->posA);
        func_00187B48(&v, &v, s);
        func_00187B00(&v, &v, &g->posA);
        v.y = 10.0f;
        g->orb[n].pos = v;
        for (k = 0; k < 32; k++) {
            func_00101080(&v2, 2.0f);
            v2.y *= 0.1f;
            func_00187B00(&g->orb[n].pt[k], &v2, &v);
        }
        g->n++;
    }

    ((Quad_b768_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Quad_b768_01E00080 *)(s32)&pk)->size = 9;
    ((Quad_b768_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b768_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Quad_b768_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, 5);
    func_002086D0(&pk, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    r = 10.0f;
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
    for (i = 0; i < 8; i++) {
        if (g->orb[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_00101020(g->orb[i].t, 32.0f) * func_00100FF0(g->t, 477.0f, 445.0f));
        pk.c.r = 0x40;
        pk.c.g = 0x40;
        pk.c.b = 0x40;
        pk.c.a = alpha;
        pk.c.q = 1.0f;
        for (k = 0; k < 32; k++) {
            x = k % 4 * 64;
            y = 0;
            ((Uv_b768_01E00080 *)(s32)&pk.v[0].uv)->u = x << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[0].uv)->v = y << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[1].uv)->u = (x + 64) << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[1].uv)->v = y << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[2].uv)->u = x << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[2].uv)->v = (y + 64) << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[3].uv)->u = (x + 64) << 4;
            ((Uv_b768_01E00080 *)(s32)&pk.v[3].uv)->v = (y + 64) << 4;
            m4 = m3;
            func_00100E00(&m4, (k << 16) >> 5, 2);
            for (l = 0; l < 4; l++) {
                func_001878E0(&out[l], &m4, &cn[l]);
                func_00187B00(&out[l], &out[l], &g->orb[i].pt[k]);
            }
            if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        if (g->orb[i].t > 48 && g->t < 0x1BD) {
            n = g->t % 16;
            (void)n;
            g->spark[i][n].on = 1;
            g->spark[i][n].t = 0;
            for (k = 0; k < 6; k++) {
                func_00101080(&g->spark[i][n].v[k], 1.0f);
            }
        }
        g->orb[i].t++;
        if (g->t > 0x1DD) {
            g->orb[i].on = 0;
        }
    }

    ((Spr_b768_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b768_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b768_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b768_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b768_01E00080 *)(s32)&spr)->flags |= 0x800;
    ((Quad_b768_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Quad_b768_01E00080 *)(s32)&pk)->size = 9;
    ((Quad_b768_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b768_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Quad_b768_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, 5);
    func_002086D0(&pk, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e = func_00101050(0x1BD - g->t, 0, 16) / 16.0f;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) {
            if (g->spark[i][j].on == 0) {
                continue;
            }
            func_00208700(&spr, g->tex[1], 1);
            func_00208CB0(&spr, 5);
            func_002086D0(&spr, func_00208D00(1));
            r = 0.5f + 0.5f * g->spark[i][j].t / 16.0f;
            r = 12.0f * r;
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
            alpha = (u32)(e * (164.0f * func_0020B480((g->spark[i][j].t << 14) >> 4)));
            spr.c.r = 0xFF;
            spr.c.g = 0x50;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            s = 0.4f + 0.6f * func_00100D50(g->spark[i][j].t, 16, 1);
            f = 70.0f * g->spark[i][j].t / 16.0f;
            for (k = 0; k < 6; k++) {
                x = k % 4 * 32;
                y = (k >> 2) * 32;
                ((Uv_b768_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i][j].v[k], s);
                func_00187B00(&v, &v, &g->orb[i].pos);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            func_00208700(&spr, g->tex[2], 1);
            func_00208CB0(&spr, 5);
            func_002086D0(&spr, func_00208D00(1));
            r = 12.0f * (0.5f + 0.5f * g->spark[i][j].t / 16.0f);
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
            alpha = (u32)(e * (128.0f * func_0020B480((g->spark[i][j].t << 14) >> 4)));
            spr.c.r = 0xFF;
            spr.c.g = 0x50;
            spr.c.b = 0x0C;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            s = -1.0f * (0.4f + 0.6f * func_00100D50(g->spark[i][j].t, 16, 1));
            f = 70.0f * g->spark[i][j].t / 16.0f;
            for (k = 0; k < 6; k++) {
                x = k % 4 * 32;
                y = 32;
                ((Uv_b768_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b768_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i][j].v[k], s);
                func_00187B00(&v, &v, &g->orb[i].pos);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            r = 3.0f;
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
            alpha = (u32)(128.0f * func_00100FF0(g->spark[i][j].t, 16.0f, 10.0f));
            pk.c.r = 0xFF;
            pk.c.g = 0x80;
            pk.c.b = 0x80;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            s = -1.0f * (2.0f * (0.2f + 0.8f * func_00100D50(g->spark[i][j].t, 16, 1)));
            f = 5.0f * (0.5f * (-0.010896278f * func_001A6C48(g->spark[i][j].t, 2.0f)));
            for (k = 0; k < 6; k++) {
                x = k % 4 * 64;
                y = 0;
                ((Uv_b768_01E00080 *)(s32)&pk.v[0].uv)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[0].uv)->v = y << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[1].uv)->u = (x + 64) << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[1].uv)->v = y << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[2].uv)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[2].uv)->v = (y + 64) << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[3].uv)->u = (x + 64) << 4;
                ((Uv_b768_01E00080 *)(s32)&pk.v[3].uv)->v = (y + 64) << 4;
                func_00187B48(&v, &g->spark[i][j].v[k], s);
                v.y = func_001A6970(v.y);
                func_00187B00(&v, &v, &g->orb[i].pos);
                v.y += f;
                m4 = m3;
                func_00100E00(&m4, (k << 16) / 6 + ((j << 16) >> 4), 2);
                b = 0.2f + 0.8f * k / 5.0f;
                v2.x = b;
                v2.y = b;
                v2.z = 0.0f;
                v2.w = 1.0f;
                func_0020CB20(&m4, &v2);
                for (q = 0; q < 4; q++) {
                    func_001878E0(&out[q], &m4, &cn[q]);
                    func_00187B00(&out[q], &out[q], &v);
                }
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
            g->spark[i][j].t++;
            if (g->spark[i][j].t > 16) {
                g->spark[i][j].on = 0;
            }
        }
    }

    b = func_00101050(g->t - 0xD6, 0, 16) * (f32)func_00101050(0x1CD - g->t, 0, 16) / 256.0f;
    if (b > 0.0f) {
        ((Spr_b768_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b768_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b768_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b768_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b768_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b768_01E00080 *)(s32)&spr.uv0)->u = 0x60;
        ((Uv_b768_01E00080 *)(s32)&spr.uv0)->v = 0x40;
        ((Uv_b768_01E00080 *)(s32)&spr.uv1)->u = 0x27A0;
        ((Uv_b768_01E00080 *)(s32)&spr.uv1)->v = 0x1BC0;
        alpha = (u32)(64.0f * b);
        (void)alpha;
        spr.c.r = 0xBC;
        spr.c.g = 0x8A;
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
        func_002075F0(&spr, ot, 0);
    }

    if (g->t == 0x66) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b768_01E00080 *)(s32)&w.pk)->flags = 0x33;
        ((Tri_b768_01E00080 *)(s32)&w.pk)->size = 9;
        ((Tri_b768_01E00080 *)(s32)&w.pk)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b768_01E00080 *)(s32)&w.pk)->pad4 = 0;
        ((Tri_b768_01E00080 *)(s32)&w.pk)->flags |= 0x800;
        func_002086D0(&w.pk, func_00208D00(0));
        func_00208CB0(&w.pk, ((u64)0x700 << 32) | 0xA0000A);
        h = func_00207F60();
        func_00208460();
        D_01E02080_b768 = (s32)g;
        func_001F7070(1, w.a, w.b, 0, func_01E01D90_b768);
        func_00208460();
        e = func_00101020(g->t2, 48.0f);
        b = func_00101020(g->t2, 192.0f);
        for (i = 0; i < 3; i++) {
            s = 1.0f + 0.1f * i / 2.0f - 0.05f;
            a = ((i + 1) << 15) >> 2;
            alpha = (u32)(e * (128.0f * func_0020B550(a)));
            alpha2 = (u32)(b * (128.0f * func_0020B550(a)));
            w.pk.v[0].c.r = 0x80;
            w.pk.v[0].c.g = 0x80;
            w.pk.v[0].c.b = 0x80;
            w.pk.v[0].c.a = alpha;
            w.pk.v[0].c.q = 1.0f;
            w.pk.v[1].c.r = 0x80;
            w.pk.v[1].c.g = 0x80;
            w.pk.v[1].c.b = 0x80;
            w.pk.v[1].c.a = alpha2;
            w.pk.v[1].c.q = 1.0f;
            w.pk.v[2].c = w.pk.v[1].c;
            for (k = 0; k < 8; k++) {
                x = g->scr.x;
                y = g->scr.y;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[0].uv)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[0].uv)->v = y << 4;
                x = D_28B960[k].x;
                y = D_28B960[k].y;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[1].uv)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[1].uv)->v = y << 4;
                x = D_28B960[k + 1].x;
                y = D_28B960[k + 1].y;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[2].uv)->u = x << 4;
                ((Uv_b768_01E00080 *)(s32)&w.pk.v[2].uv)->v = y << 4;
                func_00187B18(&out[0], &D_28B960[k], &g->scr);
                func_00187B18(&out[1], &D_28B960[k + 1], &g->scr);
                func_00187B48(&out[0], &out[0], s);
                func_00187B48(&out[1], &out[1], s);
                func_00187B00(&out[0], &out[0], &g->scr);
                func_00187B00(&out[1], &out[1], &g->scr);
                x = g->scr.x;
                y = g->scr.y;
                w.pk.v[0].p.x = (x + 0x6C0) << 4;
                w.pk.v[0].p.y = (y + 0x720) << 4;
                w.pk.v[0].p.z = 0xFFFFF8;
                w.pk.v[0].p.f = 0;
                x = out[0].x;
                y = out[0].y;
                w.pk.v[1].p.x = (x + 0x6C0) << 4;
                w.pk.v[1].p.y = (y + 0x720) << 4;
                w.pk.v[1].p.z = 0xFFFFF8;
                w.pk.v[1].p.f = 0;
                x = out[1].x;
                y = out[1].y;
                w.pk.v[2].p.x = (x + 0x6C0) << 4;
                w.pk.v[2].p.y = (y + 0x720) << 4;
                w.pk.v[2].p.z = 0xFFFFF8;
                w.pk.v[2].p.f = 0;
                func_002075F0(&w.pk, 0, 0);
            }
        }
        func_00207FD0(h, ot, 0);
        g->t2++;
        if (g->t2 > 168) {
            g->on2 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x1FD - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x118) {
        ret = 1;
    } else {
        if (g->t > 0x122 && g->t < 0x1BD) {
            ret = 6;
        }
        if (g->t == 0x1BD) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1FD) {
        ret = 8;
    }
    return ret;
}
