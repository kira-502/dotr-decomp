#include "common.h"

/* shape b722:01E00080 (b722), 3114 insns, 1 copy (-O3,p): scene effect: a radial blur, a flash at the lifted joint
   point, 16 ribbon tornadoes, a beam, a quad ring, sparks and three screen strips */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b722_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b722_01E00080;

typedef struct {
    f32 s, t;
} St_b722_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b722_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b722_01E00080 c;
    Uv_b722_01E00080 uv0;
    Xyz_b722_01E00080 p0;
    Uv_b722_01E00080 uv1;
    Xyz_b722_01E00080 p1;
    u8 tail[0x20];
} Spr_b722_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b722_01E00080 c;
        Uv_b722_01E00080 uv;
        Xyz_b722_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b722_01E00080;

typedef struct {
    Rgbaq_b722_01E00080 c;
    f32 s, t;
    Xyz_b722_01E00080 p;
} Tv_b722_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b722_01E00080 v[4];
    u8 tail[0x20];
} Quad_b722_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b722_01E00080 c;
    struct {
        union {
            Uv_b722_01E00080 uv;
            St_b722_01E00080 st;
        } t;
        Xyz_b722_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Strip_b722_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b722_01E00080 c;
    Xyz_b722_01E00080 p0;
    Xyz_b722_01E00080 p1;
    u64 tail;
} Rect_b722_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b722_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life[1][12];
    f32 a[1][12];
    f32 b[1][12];
    f32 c[1][12];
    u8 padC8[8];
    Mtx_b722_01E00080 m[1][12];
} Strand_b722_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Vec4f dir;
    f32 len;
    f32 w[16];
    f32 r[16];
    u8 padB4[0xC];
    Mtx_b722_01E00080 m[16];
} Beam_b722_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[1];
    u8 padC[4];
    Vec4f pos[1];
    Mtx_b722_01E00080 m[1];
} Ring_b722_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Spark_b722_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn[2];
    u8 pad28[8];
    Vec4f jp[2];
    Mtx_b722_01E00080 mat;
    s32 jn2[2];
    u8 pad98[8];
    Vec4f jp2[2];
    Vec4f tgt;
    Vec4f scr;
    Vec4f pos;
    Vec4f scale;
    u8 on1;
    u8 pad101[3];
    s32 t1;
    u8 col[11][4];
    u8 pad134[0xC];
    Strand_b722_01E00080 st[16];
    s32 nb;
    u8 pad3E44[0xC];
    Beam_b722_01E00080 bm[1];
    s32 nr;
    u8 pad4314[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Ring_b722_01E00080 rg[1];
    Spark_b722_01E00080 sp[2];
    u8 on2;
    u8 pad6881[3];
    s32 t2;
    s32 pt[10][2];
    u8 fon[3];
    u8 pad68DB;
    s32 ft[3];
    u8 on3;
    u8 pad68E9[3];
    s32 t3;
} Scene_b722_01E00080;


#pragma optimization_level 3

static s32 func_01E00080_b722(s32 arg0, s32 code) {
    Scene_b722_01E00080 *g = (Scene_b722_01E00080 *)arg0;
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
    extern void func_00205CA0(void *);
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
    extern void func_0020CB20(void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern f32 func_001A6970(f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 q;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    u8 a2;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 e;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 z0;
    f32 z1;
    f32 d0;
    f32 d1;
    f32 c0;
    f32 c1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b722_01E00080 m4;
    Vec4f v;
    Rect_b722_01E00080 rc __attribute__((aligned(8)));
    Strip_b722_01E00080 sb __attribute__((aligned(8)));
    Tri_b722_01E00080 tri __attribute__((aligned(8)));
    Quad_b722_01E00080 pk __attribute__((aligned(8)));
    Spr_b722_01E00080 spr __attribute__((aligned(8)));
    Xyz_b722_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x68F0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(4, 0xF);
        g->tex[1] = func_00202BF0(5, 0);
        g->tex[2] = func_00202BF0(5, 1);
        g->tex[3] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x23, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x24, 0);
        g->jn2[0] = func_001F5560(g->unitA, 0x46, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x4C, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->on1 = 0;
        g->t1 = 0;
        for (i = 0; i < 11; i++) {
            f = (f32)i / 10.0f;
            u1 = 1.0f - f;
            g->col[i][0] = (u32)(170.0f * u1 + 50.0f * f);
            g->col[i][1] = (u32)(255.0f * u1 + 128.0f * f);
            g->col[i][2] = (u32)(70.0f * u1 + 30.0f * f);
            g->col[i][3] = (u32)(128.0f * u1);
        }
        for (i = 0; i < 16; i++) {
            g->st[i].on = 0;
        }
        g->nb = 0;
        for (i = 0; i < 1; i++) {
            g->bm[i].on = 0;
        }
        g->nr = 0;
        for (n = 0; n < 8; n++) {
            z1 = -20.0f * (n + 1) / 8.0f;
            z0 = -20.0f * n / 7.0f;
            h = 14.0f * (8 - (n + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                k = ((j << 16) >> 4) + ((n << 13) >> 3) & 0xFFFF;
                v.x = h * func_0020B550(k);
                v.y = h * func_0020B480(k);
                v.z = z0;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[n][j][0].x = -2.5f;
                g->grid[n][j][0].y = 0.0f;
                g->grid[n][j][0].z = 0.0f;
                g->grid[n][j][0].w = 1.0f;
                g->grid[n][j][1].x = 2.5f;
                g->grid[n][j][1].y = 0.0f;
                g->grid[n][j][1].z = 0.0f;
                g->grid[n][j][1].w = 1.0f;
                g->grid[n][j][2].x = -2.5f;
                g->grid[n][j][2].y = 0.0f;
                g->grid[n][j][2].z = z1;
                g->grid[n][j][2].w = 1.0f;
                g->grid[n][j][3].x = 2.5f;
                g->grid[n][j][3].y = 0.0f;
                g->grid[n][j][3].z = z1;
                g->grid[n][j][3].w = 1.0f;
                for (q = 0; q < 4; q++) {
                    func_001878E0(&g->grid[n][j][q], &m4, &g->grid[n][j][q]);
                }
                g->gc[n][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 1; i++) {
            g->rg[i].on = 0;
        }
        for (i = 0; i < 2; i++) {
            g->sp[i].on = 0;
        }
        g->on2 = 0;
        g->pt[0][0] = -0x60;
        g->pt[0][1] = -0xA0;
        g->pt[2][0] = 0x60;
        g->pt[2][1] = -0xA0;
        g->pt[4][0] = 0x60;
        g->pt[4][1] = 0xA0;
        g->pt[6][0] = -0x60;
        g->pt[6][1] = 0xA0;
        g->pt[8][0] = g->pt[0][0];
        g->pt[8][1] = g->pt[0][1];
        g->pt[1][0] = -0x20;
        g->pt[1][1] = -0x60;
        g->pt[3][0] = 0x20;
        g->pt[3][1] = -0x60;
        g->pt[5][0] = 0x20;
        g->pt[5][1] = 0x60;
        g->pt[7][0] = -0x20;
        g->pt[7][1] = 0x60;
        g->pt[9][0] = g->pt[1][0];
        g->pt[9][1] = g->pt[1][1];
        for (i = 0; i < 3; i++) {
            g->fon[i] = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_00187B18(&v, &g->jp[1], &g->jp[0]);
    func_00100E40(&g->mat, &v);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jp2[i]);
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
    f = (f32)func_00101050(g->t - 0x17F, 0, 18) / 18.0f;
    func_00187B18(&v, &g->tgt, &g->jp[1]);
    func_00187B48(&v, &v, f);
    func_00187B00(&g->pos, &v, &g->jp[1]);
    f = 1.0f + 4.5f * func_00101050(g->t - 0x191, 0, 64) / 64.0f;
    g->scale.x = f;
    g->scale.y = f;
    g->scale.z = f;
    g->scale.w = 1.0f;

    if (g->t == 0x191) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b722_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b722_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b722_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b722_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b722_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x4A - g->t2) * 0x50 / 74;
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0xFF;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            r = 1.0f + 0.25f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b722_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b722_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b722_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b722_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b722_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b722_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        if (g->t2 > 0x4A) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x12A) {
        g->on1 = 1;
        g->t1 = 0;
    }
    r = func_00101020((f32)g->t1, 16.0f);
    e = r * func_00100FF0((f32)g->t1, 167.0f, 151.0f);
    if (g->on1 == 1) {
        ((Spr_b722_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b722_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b722_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b722_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b722_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->pos);
        func_0020CB20(m2, &g->scale);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (0.7f + 0.3f * (g->t1 % 2)) * e);
        spr.c.r = 0xAA;
        spr.c.g = 0xFF;
        spr.c.b = 0x46;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 30.0f;
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
        ((Uv_b722_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b722_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b722_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b722_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        for (j = 0; j < 1; j++) {
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t1++;
        if (g->t1 > 0xA7) {
            g->on1 = 0;
        }
    }

    if (g->t > 0x12A && g->t < 0x1D1) {
        n = g->t % 16;
        g->st[n].on = 1;
        g->st[n].t = 0;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 12; k++) {
                g->st[n].life[j][k] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->st[n].a[j][k] = 2.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->st[n].b[j][k] = 35.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->st[n].c[j][k] = 8.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                func_00101080(&v, 1.0f);
                func_00100E40(&g->st[n].m[j][k], &v);
                func_00100E00(&g->st[n].m[j][k], (k << 16) / 12, 2);
            }
        }
    }

    ((Quad_b722_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b722_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b722_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b722_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x12340BA);
    for (i = 0; i < 16; i++) {
        if (g->st[i].on == 0) {
            continue;
        }
        for (n = 0; n < 1; n++) {
            for (k = 0; k < 12; k++) {
                if (g->st[i].t <= g->st[i].life[n][k]) {
                    func_0020EB40(m);
                    func_0020C940(m2, 0, 0, &g->pos);
                    func_0020BC00(m2, &g->st[i].m[n][k]);
                    func_0020CB20(m2, &g->scale);
                    func_0020BC00(m, m2);
                    f = 1.0f - func_00100D50(g->st[i].t, g->st[i].life[n][k], 1);
                    d0 = 1.0f + (1.0f - f);
                    for (l = 0; l < 10; l++) {
                        alpha = (u32)(e * (g->col[l][3] * f));
                        a2 = (u32)(e * (g->col[l + 1][3] * f));
                        pk.v[0].c.r = g->col[l][0];
                        pk.v[0].c.g = g->col[l][1];
                        pk.v[0].c.b = g->col[l][2];
                        pk.v[0].c.a = alpha;
                        pk.v[0].c.q = 1.0f;
                        pk.v[2].c.r = g->col[l + 1][0];
                        pk.v[2].c.g = g->col[l + 1][1];
                        pk.v[2].c.b = g->col[l + 1][2];
                        pk.v[2].c.a = a2;
                        pk.v[2].c.q = 1.0f;
                        pk.v[1].c = pk.v[0].c;
                        pk.v[3].c = pk.v[2].c;
                        z0 = 0.5f * (l % 4) / 4.0f;
                        z1 = 0.5f * (l % 4 + 1) / 4.0f;
                        pk.v[0].s = 0.0390625f;
                        pk.v[0].t = z0;
                        pk.v[1].s = 0.2109375f;
                        pk.v[1].t = z0;
                        pk.v[2].s = 0.0390625f;
                        pk.v[2].t = z1;
                        pk.v[3].s = 0.2109375f;
                        pk.v[3].t = z1;
                        z0 = g->st[i].b[n][k] * l / 10.0f;
                        z1 = g->st[i].b[n][k] * (l + 1) / 10.0f;
                        h = f * (g->st[i].a[n][k] * (10 - l) / 10.0f);
                        s = f * (g->st[i].a[n][k] * (10 - (l + 1)) / 10.0f);
                        c0 = d0 * (g->st[i].c[n][k] * func_0020B550((l << 16) / 10 & 0xFFFF));
                        c1 = d0 * (g->st[i].c[n][k] * func_0020B550(((l + 1) << 16) / 10 & 0xFFFF));
                        cn[0].x = c0;
                        cn[0].y = -h + c0;
                        cn[0].z = z0;
                        cn[0].w = 1.0f;
                        cn[1].x = c0;
                        cn[1].y = h + c0;
                        cn[1].z = z0;
                        cn[1].w = 1.0f;
                        cn[2].x = c1;
                        cn[2].y = -s + c1;
                        cn[2].z = z1;
                        cn[2].w = 1.0f;
                        cn[3].x = c1;
                        cn[3].y = s + c1;
                        cn[3].z = z1;
                        cn[3].w = 1.0f;
                        if (func_00205630(cn, D_0030FF00, m, &pk, &depth) == 1) {
                            func_002075F0(&pk, ot, (u32)depth);
                        }
                    }
                }
            }
        }
        g->st[i].t++;
        if (g->st[i].t > 16) {
            g->st[i].on = 0;
        }
    }

    if (g->t == 0x17F) {
        n = g->nb;
        g->bm[n].on = 1;
        g->bm[n].t = 0;
        g->bm[n].pos = g->jp[1];
        func_00187B18(&g->bm[n].dir, &g->tgt, &g->bm[n].pos);
        g->bm[n].len = func_001A6C60(func_001A6C48(g->bm[n].dir.x, 2.0f) + func_001A6C48(g->bm[n].dir.y, 2.0f) +
                               func_001A6C48(g->bm[n].dir.z, 2.0f));
        for (j = 0; j < 16; j++) {
            g->bm[n].w[j] = 1.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->bm[n].r[j] = 8.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            func_00100E40(&g->bm[n].m[j], &g->bm[n].dir);
            func_00100E00(&g->bm[n].m[j], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
        g->nb++;
        if (g->nb > 0) {
            g->nb = 0;
        }
    }

    ((Quad_b722_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b722_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b722_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b722_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x12340BA);
    for (i = 0; i < 1; i++) {
        if (g->bm[i].on == 0) {
            continue;
        }
        n = (s32)(16.0f * func_00101020((f32)g->bm[i].t, 18.0f));
        if (n > 16) {
            n = 16;
        }
        f = 1.0f - func_00100D50(g->bm[i].t, 0x40, 1);
        alpha = (u32)(128.0f * f);
        pk.v[0].c.r = 0xAA;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0x46;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        for (j = 0; j < 16; j++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->bm[i].m[j], &g->bm[i].pos);
            func_0020BC00(m, m2);
            for (k = 0; k < n; k++) {
                q = k % 3;
                c0 = 0.5f * q / 3.0f;
                c1 = 0.5f * (q + 1) / 3.0f;
                pk.v[0].s = 0.0390625f;
                pk.v[0].t = c0;
                pk.v[1].s = 0.2109375f;
                pk.v[1].t = c0;
                pk.v[2].s = 0.0390625f;
                pk.v[2].t = c1;
                pk.v[3].s = 0.2109375f;
                pk.v[3].t = c1;
                z0 = g->bm[i].len * k / 16.0f;
                z1 = g->bm[i].len * (k + 1) / 16.0f;
                d0 = g->bm[i].w[j] * f;
                d1 = 1.0f + 1.5f * (1.0f - f);
                c0 = d1 * (g->bm[i].r[j] * func_0020B480(((k << 16) >> 4) + (i * 0x15B3 + j * 0x1A0A) & 0xFFFF));
                c1 = d1 * (g->bm[i].r[j] * func_0020B480((((k + 1) << 16) >> 4) + (i * 0x15B3 + j * 0x1A0A) & 0xFFFF));
                out[0].x = 0.0f;
                out[0].y = -d0 + c0;
                out[0].z = z0;
                out[0].w = 1.0f;
                out[1].x = 0.0f;
                out[1].y = d0 + c0;
                out[1].z = z0;
                out[1].w = 1.0f;
                out[2].x = 0.0f;
                out[2].y = -d0 + c1;
                out[2].z = z1;
                out[2].w = 1.0f;
                out[3].x = 0.0f;
                out[3].y = d0 + c1;
                out[3].z = z1;
                out[3].w = 1.0f;
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->bm[i].t++;
        if (g->bm[i].t > 0x40) {
            g->bm[i].on = 0;
        }
    }

    if (g->t == 0xAA) {
        n = g->nr;
        g->rg[n].on = 1;
        g->rg[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->rg[n].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->rg[n].pos[j] = g->jp[1];
            g->rg[n].m[j] = g->mat;
        }
        g->nr++;
        if (g->nr > 0) {
            g->nr = 0;
        }
    }

    ((Quad_b722_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b722_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b722_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b722_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 1; i++) {
        if (g->rg[i].on == 0) {
            continue;
        }
        alpha = (u32)(48.0f * func_00101020((f32)g->rg[i].t, 16.0f) * func_00100FF0((f32)g->rg[i].t, 250.0f, 234.0f) *
                      (0.5 + 0.5f * (g->rg[i].t % 2)));
        pk.v[0].c.r = 0xAA;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0x46;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        v.x = 1.0f;
        v.y = 1.0f;
        v.z = 1.0f;
        v.w = 1.0f;
        for (j = 0; j < 1; j++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat, &g->jp[1]);
            func_00100E00(m2, g->rg[i].rot[j] + g->rg[i].t * 0x457, 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (q = 0; q < 8; q++) {
                for (k = 0; k < 16; k++) {
                    n = g->gc[q][k];
                    x = n % 4 * 32;
                    y = (n >> 2) * 32;
                    u0 = x / 128.0f;
                    u1 = (32.0f + x) / 128.0f;
                    w1 = y / 64.0f;
                    w0 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = w0;
                    pk.v[1].s = u1;
                    pk.v[1].t = w0;
                    pk.v[2].s = u0;
                    pk.v[2].t = w1;
                    pk.v[3].s = u1;
                    pk.v[3].t = w1;
                    if (func_002058D0(g->grid[q][k], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b722_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b722_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b722_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b722_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b722_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 16.5f;
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
        alpha = (u32)((0.6f + 0.4f * (g->rg[i].t % 2)) *
                      (128.0f * func_00101020((f32)g->rg[i].t, 16.0f) * func_00100FF0((f32)g->rg[i].t, 250.0f, 234.0f)));
        spr.c.r = 0xAA;
        spr.c.g = 0xFF;
        spr.c.b = 0x46;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 1; j++) {
            v = g->jp[1];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b722_01E00080 *)(s32)&spr.uv0)->u = 0x600;
            ((Uv_b722_01E00080 *)(s32)&spr.uv0)->v = 0;
            ((Uv_b722_01E00080 *)(s32)&spr.uv1)->u = 0x800;
            ((Uv_b722_01E00080 *)(s32)&spr.uv1)->v = 0x200;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->rg[i].t++;
        if (g->rg[i].t > 0xFA) {
            g->rg[i].on = 0;
        }
    }

    if (g->t == 0xB2 || g->t == 0xCC) {
        if (g->t == 0xB2) {
            n = 1;
        } else {
            n = 0;
        }
        g->sp[n].on = 1;
        g->sp[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->sp[n].pos[i] = g->jp2[n];
            for (k = 0; k < 32; k++) {
                g->sp[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->sp[n].v[i][k], 0.8f);
                g->sp[n].v[i][k].y = func_001A6970(g->sp[n].v[i][k].y);
                g->sp[n].v[i][k].y *= 0.8f;
            }
        }
    }

    ((Spr_b722_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b722_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b722_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b722_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b722_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 2; i++) {
        if (g->sp[i].on == 0) {
            continue;
        }
        alpha = (u32)(64.0f * func_0020B480((g->sp[i].t << 14) >> 5));
        spr.c.r = 0xEE;
        spr.c.g = 0xEE;
        spr.c.b = 0xEE;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 7.0f * (0.5f + 0.5f * g->sp[i].t / 32.0f);
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
        s = func_00100D50(g->sp[i].t, 0x20, 1);
        c0 = -5.0f + 0.0f * g->sp[i].t;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->sp[i].v[j][k], s);
                func_00187B00(&v, &v, &g->sp[i].pos[j]);
                v.y += c0;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->sp[i].c[j][k] % 4 * 32;
                y = (g->sp[i].c[j][k] >> 2) * 32;
                ((Uv_b722_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b722_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b722_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b722_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->sp[i].t++;
        if (g->sp[i].t > 0x20) {
            g->sp[i].on = 0;
        }
    }

    n = -1;
    switch (g->t) {
    case 0x38:
        n = 0;
        break;
    case 0x4A:
        n = 1;
        break;
    case 0x82:
        n = 2;
        break;
    }
    if (n >= 0) {
        g->fon[n] = 1;
        g->ft[n] = 0;
    }
    ((Strip_b722_01E00080 *)(s32)&sb)->flags = 0x24;
    ((Strip_b722_01E00080 *)(s32)&sb)->size = 9;
    ((Strip_b722_01E00080 *)(s32)&sb)->regs = ((u64)4 << 32) | 0x24242421;
    ((Strip_b722_01E00080 *)(s32)&sb)->pad4 = 0;
    ((Strip_b722_01E00080 *)(s32)&sb)->flags |= 0x800;
    func_00208700(&sb, g->tex[1], 1);
    func_00208CB0(&sb, 5);
    func_002086D0(&sb, func_00208D00(1));
    x = 0x96;
    ((Uv_b722_01E00080 *)(s32)&sb.v[0].t.uv)->u = 0x600;
    ((Uv_b722_01E00080 *)(s32)&sb.v[0].t.uv)->v = 0x100;
    ((Uv_b722_01E00080 *)(s32)&sb.v[1].t.uv)->u = 0x800;
    ((Uv_b722_01E00080 *)(s32)&sb.v[1].t.uv)->v = 0x100;
    ((Uv_b722_01E00080 *)(s32)&sb.v[2].t.uv)->u = 0x600;
    ((Uv_b722_01E00080 *)(s32)&sb.v[2].t.uv)->v = 0x100;
    ((Uv_b722_01E00080 *)(s32)&sb.v[3].t.uv)->u = 0x800;
    ((Uv_b722_01E00080 *)(s32)&sb.v[3].t.uv)->v = 0x100;
    for (i = 0; i < 3; i++) {
        if (g->fon[i] != 0) {
            alpha = (u32)((0.5f + 0.5f * (g->ft[i] % 2)) * (255.0f * func_00101020((f32)g->ft[i], 8.0f)));
            sb.c.r = 0x60;
            sb.c.g = 0xFF;
            sb.c.b = 0x60;
            sb.c.a = alpha;
            sb.c.q = 1.0f;
            for (k = 0; k < 4; k++) {
                sb.v[0].p.x = (g->pt[k * 2][0] + x + 0x6C0) << 4;
                sb.v[0].p.y = (g->pt[k * 2][1] + 0x800) << 4;
                sb.v[0].p.z = 0xFFFFF8;
                sb.v[0].p.f = 0;
                sb.v[1].p.x = (g->pt[k * 2 + 1][0] + x + 0x6C0) << 4;
                sb.v[1].p.y = (g->pt[k * 2 + 1][1] + 0x800) << 4;
                sb.v[1].p.z = 0xFFFFF8;
                sb.v[1].p.f = 0;
                sb.v[2].p.x = (g->pt[k * 2 + 2][0] + x + 0x6C0) << 4;
                sb.v[2].p.y = (g->pt[k * 2 + 2][1] + 0x800) << 4;
                sb.v[2].p.z = 0xFFFFF8;
                sb.v[2].p.f = 0;
                sb.v[3].p.x = (g->pt[k * 2 + 3][0] + x + 0x6C0) << 4;
                sb.v[3].p.y = (g->pt[k * 2 + 3][1] + 0x800) << 4;
                sb.v[3].p.z = 0xFFFFF8;
                sb.v[3].p.f = 0;
                func_002075F0(&sb, ot, 0);
            }
            g->ft[i]++;
            if (g->ft[i] > 0x3200) {
                g->fon[i] = 0;
            }
        }
        x += 0xAA;
    }

    if (g->t == 0x91) {
        g->on3 = 1;
        g->t3 = 0;
        for (i = 0; i < 3; i++) {
            g->fon[i] = 0;
        }
    }
    if (g->on3 == 1) {
        ((Strip_b722_01E00080 *)(s32)&sb)->flags = 0x24;
        ((Strip_b722_01E00080 *)(s32)&sb)->size = 9;
        ((Strip_b722_01E00080 *)(s32)&sb)->regs = ((u64)4 << 32) | 0x24242421;
        ((Strip_b722_01E00080 *)(s32)&sb)->pad4 = 0;
        func_00208700(&sb, g->tex[3], 1);
        func_00208CB0(&sb, 5);
        func_002086D0(&sb, func_00208D00(1));
        sb.v[0].t.st.s = 0.0f;
        sb.v[0].t.st.t = 0.0f;
        sb.v[1].t.st.s = 1.0f;
        sb.v[1].t.st.t = 0.0f;
        sb.v[2].t.st.s = 0.0f;
        sb.v[2].t.st.t = 1.0f;
        sb.v[3].t.st.s = 1.0f;
        sb.v[3].t.st.t = 1.0f;
        alpha = (0x20 - g->t3) * 0xFF >> 5;
        sb.c.r = 0x80;
        sb.c.g = 0x80;
        sb.c.b = 0x80;
        sb.c.a = alpha;
        sb.c.q = 1.0f;
        sb.v[0].p.x = 0x5A80;
        sb.v[0].p.y = 0x7200;
        sb.v[0].p.z = 0xFFFFF8;
        sb.v[0].p.f = 0;
        sb.v[1].p.x = 0x5A80;
        sb.v[1].p.y = 0x8E00;
        sb.v[1].p.z = 0xFFFFF8;
        sb.v[1].p.f = 0;
        sb.v[2].p.x = 0xA580;
        sb.v[2].p.y = 0x7200;
        sb.v[2].p.z = 0xFFFFF8;
        sb.v[2].p.f = 0;
        sb.v[3].p.x = 0xA580;
        sb.v[3].p.y = 0x8E00;
        sb.v[3].p.z = 0xFFFFF8;
        sb.v[3].p.f = 0;
        func_002075F0(&sb, ot, 0);
        ((Rect_b722_01E00080 *)(s32)&rc)->flags = 6;
        ((Rect_b722_01E00080 *)(s32)&rc)->size = 3;
        ((Rect_b722_01E00080 *)(s32)&rc)->regs = 0x441;
        ((Rect_b722_01E00080 *)(s32)&rc)->pad4 = 0;
        func_002086D0(&rc, func_00208D00(2));
        alpha = (0x20 - g->t3) * 0x94 >> 5;
        rc.c.r = 0x80;
        rc.c.g = 0x80;
        rc.c.b = 0x80;
        rc.c.a = alpha;
        rc.c.q = 1.0f;
        rc.p0.x = 0x6C00;
        rc.p0.y = 0x7200;
        rc.p0.z = 0xFFFFF8;
        rc.p0.f = 0;
        rc.p1.x = 0x9400;
        rc.p1.y = 0x8E00;
        rc.p1.z = 0xFFFFF8;
        rc.p1.f = 0;
        func_002075F0(&rc, ot, 0);
        g->t3++;
        if (g->t3 > 0x20) {
            g->on3 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x1FB - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x187) {
        ret = 1;
    } else {
        if (g->t > 0x191 && g->t < 0x1D1) {
            ret = 6;
        }
        if (g->t == 0x1D1) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1FB) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
