#include "common.h"

/* shape b453:01E00080 (b453), 2979 insns, 1 copy (-O3,p): b453 scene manager (written from the asm with b729/b768
   sections): setup clears the 0xA7C0 scene, takes both units, four textures, both positions (the target lowered by
   20), joints 0x10 / 9 and 0x1B / 0x1C / 0x20; projects the unit's and the target's screen points, at 0xB5 a
   0x4C-frame 8-layer radial blur at the target (render-to-texture, D_28B960), a fading screen flash on 0x21..0x109,
   on 0xB5..0xF9 16-slot 12-spark bursts at the target (two sprite passes and a spinning quad pass), six 32-sprite
   rings at a hand every 25 frames from 0x18, on 0x21..0x109 28-slot 3x20 and 20-slot 3x4 sprite puffs at three
   joints, from 0x20 a 0xEA-frame render-to-texture aura at the unit (func_001F7070 with func_01E02F10) as 5x8 screen
   triangles, the screen tint; returns 1 / 6 / 2 / 8 at 0xAA / 0xB5..0xF9 / 0xFA / >0x12A */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b453_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b453_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b453_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b453_01E00080 c;
    Uv_b453_01E00080 uv0;
    Xyz_b453_01E00080 p0;
    Uv_b453_01E00080 uv1;
    Xyz_b453_01E00080 p1;
    u8 tail[0x20];
} Spr_b453_01E00080;

typedef struct {
    Uv_b453_01E00080 uv;
    Xyz_b453_01E00080 p;
} Qv_b453_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b453_01E00080 c;
    Qv_b453_01E00080 v[4];
    u8 tail[0x20];
} Quad_b453_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b453_01E00080 c;
        Uv_b453_01E00080 uv;
        Xyz_b453_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b453_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b453_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[12];
} Spark_b453_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Ring_b453_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3][20];
    u8 pad44[0xC];
    Vec4f pos[3];
    Vec4f v[3][20];
} Blob_b453_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3][4];
    u8 pad14[0xC];
    Vec4f pos[3];
    Vec4f v[3][4];
} Mote_b453_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f posA;
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr0;
    Vec4f scr;
    s32 jn[2];
    u8 pad78[8];
    Vec4f jp[2];
    s32 jn2[3];
    u8 padAC[4];
    Vec4f jp2[3];
    Spark_b453_01E00080 spark[1][16];
    u8 on3;
    u8 padDE1[3];
    s32 t3;
    s32 nring;
    u8 padDEC[4];
    Ring_b453_01E00080 ring[6];
    u8 on2;
    u8 pad1B71[3];
    s32 t2;
    u8 pad1B78[8];
    Blob_b453_01E00080 blob[28];
    Mote_b453_01E00080 mote[20];
} Scene_b453_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b453(s32 arg0, s32 code) {
    Scene_b453_01E00080 *g = (Scene_b453_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6970(f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern void func_01E02F10_b453(void *);
    extern s32 D_01E03200_b453;
    extern Vec4f D_28B960[];
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
    s32 a;
    u8 alpha;
    u8 alpha2;
    f32 r;
    f32 f;
    f32 s;
    f32 e;
    f32 b;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b453_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b453_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    Tri_b453_01E00080 tri __attribute__((aligned(8)));
    Quad_b453_01E00080 pk __attribute__((aligned(8)));
    Spr_b453_01E00080 spr __attribute__((aligned(8)));
    Xyz_b453_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA7C0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitA, &g->posA);
        func_001F5F90(g->unitB, &g->tgt);
        g->tgt.y += -20.0f;
        g->jn[0] = func_001F5560(g->unitA, 0x10, 1);
        g->jn[1] = func_001F5560(g->unitA, 9, 0);
        g->jn2[0] = func_001F5560(g->unitA, 0x1B, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x1C, 0);
        g->jn2[2] = func_001F5560(g->unitA, 0x20, 0);
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 16; j++) {
                g->spark[i][j].on = 0;
            }
        }
        g->on3 = 0;
        for (i = 0; i < 6; i++) {
            g->ring[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 28; i++) {
            g->blob[i].on = 0;
        }
        for (k = 0; k < 20; k++) {
            g->mote[k].on = 0;
        }
        return 0;
    }
    func_00205CA0(&m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 3; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jp2[i]);
    }
    func_001F53C0(1, g->unitA, &g->pos);
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

    if (g->t == 0xB5) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b453_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b453_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b453_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b453_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b453_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x4C - g->t2) * 0x38 / 76;
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
                ((Uv_b453_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b453_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b453_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        if (g->t2 > 0x4C) {
            g->on2 = 0;
        }
    }

    b = (f32)func_00101050(g->t - 0x20, 0, 16) * (f32)func_00101050(0x10A - g->t, 0, 16) / 256.0f;
    if (b > 0.0f) {
        ((Spr_b453_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b453_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b453_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b453_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b453_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = 0x60;
        ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = 0x40;
        ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = 0x27A0;
        ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = 0x1BC0;
        alpha = (u32)(64.0f * b);
        spr.c.r = 0xA8;
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

    if (g->t > 0xB4 && g->t < 0xFA) {
        n = g->t % 16;
        g->spark[0][n].on = 1;
        g->spark[0][n].t = 0;
        for (k = 0; k < 12; k++) {
            func_00101080(&g->spark[0][n].v[k], 2.0f);
        }
    }

    ((Spr_b453_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b453_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b453_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b453_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b453_01E00080 *)(s32)&spr)->flags |= 0x800;
    ((Quad_b453_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Quad_b453_01E00080 *)(s32)&pk)->size = 9;
    ((Quad_b453_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b453_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Quad_b453_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, 5);
    func_002086D0(&pk, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    w = func_00101050(0xFA - g->t, 0, 16) / 16.0f;
    b = 3.5f;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 16; j++) {
            if (g->spark[i][j].on == 0) {
                continue;
            }
            func_00208700(&spr, g->tex[1], 1);
            func_00208CB0(&spr, 5);
            func_002086D0(&spr, func_00208D00(1));
            r = 15.0f * (0.5f + 0.5f * g->spark[i][j].t / 16.0f);
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
            alpha = (u32)(w * (180.0f * func_0020B480((g->spark[i][j].t << 14) >> 4)));
            spr.c.r = 0xFF;
            spr.c.g = 0x6E;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            s = 0.4f + 0.6f * func_00100D50(g->spark[i][j].t, 16, 1);
            f = 90.0f * g->spark[i][j].t / 16.0f;
            for (a = 0; a < 12; a++) {
                x = a % 4 * 32;
                y = (a >> 2) * 32;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i][j].v[a], s);
                func_00187B00(&v, &v, &g->tgt);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
            func_00208700(&spr, g->tex[2], 1);
            func_00208CB0(&spr, 5);
            func_002086D0(&spr, func_00208D00(1));
            r = 15.0f * (0.5f + 0.5f * g->spark[i][j].t / 16.0f);
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
            alpha = (u32)(w * (180.0f * func_0020B480((g->spark[i][j].t << 14) >> 4)));
            spr.c.r = 0xFF;
            spr.c.g = 0x6E;
            spr.c.b = 0x0C;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            f = -1.0f * (2.0f * (0.4f + 0.6f * func_00100D50(g->spark[i][j].t, 16, 1)) / 2.0f);
            s = 90.0f * g->spark[i][j].t / 16.0f;
            for (k = 0; k < 12; k++) {
                x = k % 4 * 32;
                y = 32;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i][j].v[k], f);
                func_00187B00(&v, &v, &g->tgt);
                v.y += s;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
            cn[0].x = -b;
            cn[0].y = -b;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = b;
            cn[1].y = -b;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = -b;
            cn[2].y = b;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = b;
            cn[3].y = b;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            alpha = (u32)(128.0f * func_00100FF0(g->spark[i][j].t, 16.0f, 10.0f));
            pk.c.r = 0xFF;
            pk.c.g = 0x80;
            pk.c.b = 0x80;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            f = -1.0f * (2.5f * (0.2f + 0.8f * func_00100D50(g->spark[i][j].t, 16, 1)) / 2.0f);
            s = -10.0f - 5.0f * (0.5f * (0.010896278f * func_001A6C48(g->spark[i][j].t, 2.0f)));
            for (k = 0; k < 12; k++) {
                x = k % 4 * 64;
                y = 0;
                ((Uv_b453_01E00080 *)(s32)&pk.v[0].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[0].uv)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[1].uv)->u = (x + 64) << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[1].uv)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[2].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[2].uv)->v = (y + 64) << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[3].uv)->u = (x + 64) << 4;
                ((Uv_b453_01E00080 *)(s32)&pk.v[3].uv)->v = (y + 64) << 4;
                func_00187B48(&v, &g->spark[i][j].v[k], f);
                v.y = func_001A6970(v.y);
                func_00187B00(&v, &v, &g->tgt);
                v.y += s;
                m4 = m3;
                func_00100E00(&m4, (k << 16) / 12 + ((j << 16) >> 4), 2);
                e = 0.2f + 0.8f * k / 11.0f;
                v2.x = e;
                v2.y = e;
                v2.z = 0.0f;
                v2.w = 1.0f;
                func_0020CB20(&m4, &v2);
                for (l = 0; l < 4; l++) {
                    func_001878E0(&out[l], &m4, &cn[l]);
                    func_00187B00(&out[l], &out[l], &v);
                }
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, 0);
                }
            }
            g->spark[i][j].t++;
            if (g->spark[i][j].t > 16) {
                g->spark[i][j].on = 0;
            }
        }
    }

    n = g->nring;
    if (g->t == n * 25 + 0x18 && n < 6) {
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->ring[n].pos[i] = g->jp[n % 2];
            for (k = 0; k < 32; k++) {
                g->ring[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->ring[n].v[i][k], 1.0f);
                g->ring[n].v[i][k].y = func_001A6970(g->ring[n].v[i][k].y);
                g->ring[n].v[i][k].y *= 0.8f;
            }
        }
        g->nring++;
    }

    ((Spr_b453_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b453_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b453_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b453_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b453_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 6; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480((g->ring[i].t << 14) >> 5));
        spr.c.r = 0x58;
        spr.c.g = 0x58;
        spr.c.b = 0x58;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.5f + 0.5f * g->ring[i].t / 32.0f);
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
        f = 0.3f + 0.7f * func_00100D50(g->ring[i].t, 32, 1);
        s = -10.0f + 0.0f * g->ring[i].t;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->ring[i].v[j][k], f);
                func_00187B00(&v, &v, &g->ring[i].pos[j]);
                v.y += s;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->ring[i].c[j][k] % 4 * 32;
                y = (g->ring[i].c[j][k] >> 2) * 32;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 32) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0x20 && g->t < 0x10A) {
        n = g->t % 28;
        g->blob[n].on = 1;
        g->blob[n].t = 0;
        for (i = 0; i < 3; i++) {
            g->blob[n].pos[i] = g->jp2[i];
            for (k = 0; k < 20; k++) {
                g->blob[n].c[i][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->blob[n].v[i][k], 0.6f);
            }
        }
    }

    ((Spr_b453_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b453_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b453_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b453_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b453_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = (f32)func_00101050(g->t - 0x20, 0, 32) * (f32)func_00101050(0x10A - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 28; i++) {
        if (g->blob[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (128.0f * func_0020B480((g->blob[i].t << 14) / 28)));
        r = 0.8f * (0.5f + 0.5f * (28 - g->blob[i].t) / 28.0f);
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
        s = 0.8f + 0.2f * func_00100D50(g->blob[i].t, 28, 1);
        f = 8.0f * g->blob[i].t / 28.0f;
        for (j = 0; j < 3; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x32;
            spr.c.b = 0x14;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 20; k++) {
                x = g->blob[i].c[j][k] % 4 * 32;
                y = (g->blob[i].c[j][k] >> 2) * 32;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->blob[i].v[j][k], s);
                func_00187B00(&v, &v, &g->blob[i].pos[j]);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->blob[i].t++;
        if (g->blob[i].t > 28) {
            g->blob[i].on = 0;
        }
    }

    if (g->t > 0x20 && g->t < 0x10A) {
        n = g->t % 20;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (i = 0; i < 3; i++) {
            g->mote[n].pos[i] = g->jp2[i];
            for (k = 0; k < 4; k++) {
                g->mote[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->mote[n].v[i][k], 0.5f);
            }
        }
    }

    ((Spr_b453_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b453_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b453_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b453_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b453_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    b = (f32)func_00101050(g->t - 0x20, 0, 32) * (f32)func_00101050(0x10A - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 20; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(b * (128.0f * func_0020B480((g->mote[i].t << 14) / 20)));
        r = 5.0f * (0.3f + 0.7f * (20 - g->mote[i].t) / 20.0f);
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
        s = 0.2f + 0.8f * g->mote[i].t / 20.0f;
        f = 6.0f * g->mote[i].t / 20.0f;
        for (j = 0; j < 3; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x32;
            spr.c.b = 0x14;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 4; k++) {
                x = g->mote[i].c[j][k] % 4 * 32;
                y = (g->mote[i].c[j][k] >> 2) * 32;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b453_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->mote[i].v[j][k], s);
                func_00187B00(&v, &v, &g->mote[i].pos[j]);
                v.y += f;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 20) {
            g->mote[i].on = 0;
        }
    }

    if (g->t == 0x20) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b453_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b453_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b453_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b453_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b453_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        D_01E03200_b453 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, func_01E02F10_b453);
        func_00208460();
        b = func_00101020(g->t3, 48.0f) * func_00100FF0(g->t3, 234.0f, 186.0f);
        e = func_00101020(g->t3, 192.0f) * func_00100FF0(g->t3, 234.0f, 186.0f);
        for (i = 0; i < 5; i++) {
            s = 1.0f + 0.2f * i / 4.0f - 0.1f;
            a = ((i + 1) << 15) / 6;
            alpha = (u32)(b * (128.0f * func_0020B550(a)));
            alpha2 = (u32)(e * (128.0f * func_0020B550(a)));
            tri.v[0].c.r = 0x80;
            tri.v[0].c.g = 0x80;
            tri.v[0].c.b = 0x80;
            tri.v[0].c.a = alpha;
            tri.v[0].c.q = 1.0f;
            tri.v[1].c.r = 0x80;
            tri.v[1].c.g = 0x80;
            tri.v[1].c.b = 0x80;
            tri.v[1].c.a = alpha2;
            tri.v[1].c.q = 1.0f;
            tri.v[2].c = tri.v[1].c;
            for (k = 0; k < 8; k++) {
                x = (s32)g->scr0.x;
                y = (s32)g->scr0.y;
                ((Uv_b453_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[k].x;
                y = (s32)D_28B960[k].y;
                ((Uv_b453_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[k + 1].x;
                y = (s32)D_28B960[k + 1].y;
                ((Uv_b453_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b453_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[k], (void *)&g->scr0);
                func_00187B18(&out[1], &D_28B960[k + 1], (void *)&g->scr0);
                func_00187B48(&out[0], &out[0], s);
                func_00187B48(&out[1], &out[1], s);
                func_00187B00(&out[0], &out[0], &g->scr0);
                func_00187B00(&out[1], &out[1], &g->scr0);
                x = (s32)g->scr0.x;
                y = (s32)g->scr0.y;
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
        g->t3++;
        if (g->t3 > 0xEA) {
            g->on3 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x12A - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0xAA) {
        ret = 1;
    } else {
        if (g->t > 0xB4 && g->t < 0xFA) {
            ret = 6;
        }
        if (g->t == 0xFA) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x12A) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b453:01E02F10 (Gb453_GenAuraTex), 174 insns, 1 copy: opens the frame buffer, sends a white sprite (alpha
   0x80) over the whole screen (0x6BF8,0x71F8 - 0x93F8,0x8DF8, far z) with texel corners 0,0 - 160,112 from the frame
   copy, then a flat orange (0xC8/0x76/0) rect over the same area, and closes it */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b453_01E02F10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b453_01E02F10 v[2];
    u64 tail;
} Flat_b453_01E02F10;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u8 pad4[4];
    Xyz_b453_01E02F10 p;
} Uv_b453_01E02F10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b453_01E02F10 v[2];
    u64 tail;
} Spr_b453_01E02F10;

static void func_01E02F10_b453(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern void *func_0020F290(void *);
    extern void *func_00208870(void *, s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_00208CB0(void *, u64);
    extern void *func_00207650(void *, void *, s32, s32);
    Flat_b453_01E02F10 flat __attribute__((aligned(8)));
    Spr_b453_01E02F10 pk __attribute__((aligned(8)));
    s32 a[2];
    s32 b[3];

    buf = func_00209F70(buf, 0xFF000000);
    ((Spr_b453_01E02F10 *)(s32)&pk)->flags = 0x26;
    ((Spr_b453_01E02F10 *)(s32)&pk)->size = 5;
    ((Spr_b453_01E02F10 *)(s32)&pk)->regs = 0x42421;
    ((Spr_b453_01E02F10 *)(s32)&pk)->pad4 = 0;
    buf = func_0020F290(func_00208870(func_0020F290(buf), -1, 1, a, b));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
    ((Spr_b453_01E02F10 *)(s32)&pk)->flags |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[0])->u = 0;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[0])->v = 0;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[1])->u = 0x2800;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[1])->v = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    buf = func_00207650(buf, &pk, 0, 0);
    ((Flat_b453_01E02F10 *)(s32)&flat)->flags = 6;
    ((Flat_b453_01E02F10 *)(s32)&flat)->size = 3;
    ((Flat_b453_01E02F10 *)(s32)&flat)->regs = 0x441;
    ((Flat_b453_01E02F10 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0xC8;
    flat.g = 0x76;
    flat.b = 0;
    flat.a = 0xFF;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    buf = func_00207650(buf, &flat, 0, 0);
    func_00209F70(buf, 0);
}

