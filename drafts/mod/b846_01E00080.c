#include "common.h"

/* shape b846:01E00080 (b846), 3982 insns, 1 copy (-O3,p): b846 scene manager. DRAFT, not matching: 3849/3982 by dk try.
   Still different: float scheduling of the two ST blocks (seg, dart), the on4 alpha and the spark offsets, one argument
   order before func_00187B00, and the registers that follow from them */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b846_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b846_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b846_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b846_01E00080;

typedef struct {
    Reg_b846_01E00080 a;
    Reg_b846_01E00080 b;
} Tx_b846_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b846_01E00080 c;
    Xyz_b846_01E00080 p0;
    Xyz_b846_01E00080 p1;
    u64 tail;
} Rect_b846_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b846_01E00080 c;
    Uv_b846_01E00080 uv0;
    Xyz_b846_01E00080 p0;
    Uv_b846_01E00080 uv1;
    Xyz_b846_01E00080 p1;
    u64 pad38;
    Tx_b846_01E00080 tx;
    u64 pad50;
} Spr_b846_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b846_01E00080 c;
        Xyz_b846_01E00080 p;
    } v[4];
    u64 tail;
} Strip_b846_01E00080;

typedef struct {
    Rgbaq_b846_01E00080 c;
    union {
        Uv_b846_01E00080 uv;
        struct {
            f32 s, t;
        } st;
    } uv;
    Xyz_b846_01E00080 p;
} Tv_b846_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b846_01E00080 v[4];
    u64 pad70;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Quad_b846_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b846_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 ang[4];
    u8 pad18[8];
    Vec4f pos[4];
    Mtx_b846_01E00080 mat[4];
} Seg_b846_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4][1];
    u8 padC[4];
    Vec4f p[4];
    Vec4f v[4][1];
} Bit_b846_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
} Ring_b846_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3];
    u8 padB[5];
    Vec4f v[3];
} Dart_b846_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c;
    s8 d;
    u8 n;
    u8 padB[5];
    Vec4f v;
} Bird_b846_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    u8 padA[2];
    f32 a;
    Vec4f pos;
    Vec4f v[2];
} Spk_b846_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    Vec4f pos;
    Vec4f pos2;
    Vec4f scr;
    s32 jn[6];
    u8 pad78[8];
    Vec4f jp[6];
    Mtx_b846_01E00080 jm[4];
    s32 jn2;
    u8 pad1E4[0xC];
    Vec4f jq;
    s32 cnt;
    u8 pad204[0xC];
    Vec4f q[8][16][4];
    u8 qc[8][16];
    Seg_b846_01E00080 seg[1];
    s32 cur;
    u8 pad23F4[0xC];
    Bit_b846_01E00080 bit[16];
    Ring_b846_01E00080 ring[33];
    u8 on3;
    u8 pad3121[3];
    s32 t3;
    u8 rc[32];
    s32 ofs[32];
    u8 pad31C8[8];
    Mtx_b846_01E00080 rm[32];
    u8 on4;
    u8 pad39D1[3];
    s32 t4;
    u8 pad39D8[8];
    Dart_b846_01E00080 dart[24];
    s32 cnt3;
    u8 pad3FE4[0xC];
    Bird_b846_01E00080 bird[24];
    Spk_b846_01E00080 spk[24][16];
    u8 on5;
    u8 padA2F1[3];
    s32 t5;
    u8 padA2F8[8];
    Vec4f rim[33][3];
    Vec4f shard[96][4];
    u8 c[128];
    Vec4f sv[128];
    u8 on6;
    u8 padC9B1[3];
    s32 t6;
    u8 padC9B8[8];
} Scene_b846_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b846(s32 arg0, s32 code) {
    Scene_b846_01E00080 *g = (Scene_b846_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F57B0(s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0017B340(u64);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00100E40(void *, void *);
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
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F6D00(s32);
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
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 a;
    f32 b;
    f32 e;
    f32 u;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b846_01E00080 m4;
    Vec4f v;
    Vec4f v2;
    Rect_b846_01E00080 rc __attribute__((aligned(8)));
    Spr_b846_01E00080 spr __attribute__((aligned(8)));
    Strip_b846_01E00080 st __attribute__((aligned(8)));
    Quad_b846_01E00080 pk __attribute__((aligned(8)));
    Xyz_b846_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC9C0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        func_001F53C0(1, g->unitB, &g->pos2);
        g->jn[0] = func_001F5560(g->unitA, 0xA9, 1);
        g->jn[1] = func_001F5560(g->unitA, 0xAB, 0);
        g->jn[2] = func_001F5560(g->unitA, 0xAD, 0);
        g->jn[3] = func_001F5560(g->unitA, 0xAF, 0);
        g->jn[4] = func_001F5560(g->unitA, 0x8B, 0);
        g->jn[5] = func_001F5560(g->unitA, 0x8E, 0);
        g->jn2 = func_001F5560(g->unitA, 0x99, 0);
        g->cnt = 0;
        for (y = 0; y < 8; y++) {
            h = -6.7f * (y + 1) / 8.0f;
            e = -6.7f * y / 7.0f;
            r = 4.8f * (8 - (y + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                x = (((i << 16) >> 4) + ((y << 13) >> 3)) & 0xFFFF;
                v.x = r * func_0020B550(x);
                v.y = r * func_0020B480(x);
                v.z = e;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->q[y][i][0].x = -0.85f;
                g->q[y][i][0].y = 0.0f;
                g->q[y][i][0].z = 0.0f;
                g->q[y][i][0].w = 1.0f;
                g->q[y][i][1].x = 0.85f;
                g->q[y][i][1].y = 0.0f;
                g->q[y][i][1].z = 0.0f;
                g->q[y][i][1].w = 1.0f;
                g->q[y][i][2].x = -0.85f;
                g->q[y][i][2].y = 0.0f;
                g->q[y][i][2].z = h;
                g->q[y][i][2].w = 1.0f;
                g->q[y][i][3].x = 0.85f;
                g->q[y][i][3].y = 0.0f;
                g->q[y][i][3].z = h;
                g->q[y][i][3].w = 1.0f;
                for (j = 0; j < 4; j++) {
                    func_001878E0(&g->q[y][i][j], &m4, &g->q[y][i][j]);
                }
                g->qc[y][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (n = 0; n < 1; n++) {
            g->seg[n].on = 0;
        }
        g->cur = 0;
        for (x = 0; x < 16; x++) {
            g->bit[x].on = 0;
        }
        for (j = 0; j < 33; j++) {
            x = (j << 16) >> 5;
            s = func_0020B550(x);
            r = func_0020B480(x);
            g->ring[j].a.x = 3.0f * s;
            g->ring[j].a.y = 3.0f * r;
            g->ring[j].a.z = 0.0f;
            g->ring[j].a.w = 1.0f;
            g->ring[j].b.x = 6.0f * s;
            g->ring[j].b.y = 6.0f * r;
            g->ring[j].b.z = 0.0f;
            g->ring[j].b.w = 1.0f;
        }
        g->on3 = 0;
        g->t4 = 0;
        for (l = 0; l < 24; l++) {
            g->dart[l].on = 0;
        }
        g->cnt3 = 0;
        for (y = 0; y < 24; y++) {
            g->bird[y].on = 0;
            g->bird[y].n = 0;
        }
        for (n = 0; n < 24; n++) {
            for (l = 0; l < 16; l++) {
                g->spk[n][l].on = 0;
            }
        }
        g->on5 = 0;
        for (i = 0; i < 33; i++) {
            x = (i << 16) >> 5;
            s = func_0020B550(x);
            r = func_0020B480(x);
            g->rim[i][0].x = 6.5f * s;
            g->rim[i][0].y = 6.5f * r;
            g->rim[i][0].z = 0.0f;
            g->rim[i][0].w = 1.0f;
            g->rim[i][1].x = 10.8f * s;
            g->rim[i][1].y = 10.8f * r;
            g->rim[i][1].z = 0.0f;
            g->rim[i][1].w = 1.0f;
            g->rim[i][2].x = 11.0f * s;
            g->rim[i][2].y = 11.0f * r;
            g->rim[i][2].z = 0.0f;
            g->rim[i][2].w = 1.0f;
        }
        for (n = 0; n < 96; n++) {
            r = 0.1f + 0.9f * (n + 1) / 96.0f;
            b = 15.0f * r;
            a = -r;
            cn[0].x = 0.0f;
            cn[0].y = a;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = 0.0f;
            cn[2].y = a;
            cn[2].z = b;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = r;
            cn[3].z = b;
            cn[3].w = 1.0f;
            func_00101080(&v, 1.0f);
            func_00100E40(&m4, &v);
            func_00100E00(&m4, ((func_0019A5C8() >> 23) % 256 << 16) >> 8, 2);
            for (x = 0; x < 4; x++) {
                func_001878E0(&g->shard[n][x], &m4, &cn[x]);
            }
        }
        for (n = 0; n < 128; n++) {
            g->c[n] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->sv[n], 0.4f);
        }
        g->on6 = 0;
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (j = 0; j < 6; j++) {
        func_001F5620(g->unitA, g->jn[j], &g->jp[j]);
    }
    for (j = 0; j < 4; j++) {
        func_00187B18(&v, &g->jp[j], &g->jp[4]);
        func_00100E40(&g->jm[j], &v);
    }
    func_001F5620(g->unitA, g->jn2, &g->jq);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
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

    if ((g->t > 0xE6 && g->t < 0x10E && g->t % 8 == 0) || g->t == 0x87) {
        g->on6 = 1;
        g->t6 = 0;
    }
    if (g->on6 == 1) {
        buf = func_00207F60();
        ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
        func_00208460();
        func_00208800(func_00209E50(), 0, &spr.tx.a, &spr.tx.b);
        func_00208460();
        ((Rect_b846_01E00080 *)(s32)&rc)->flags = 6;
        ((Rect_b846_01E00080 *)(s32)&rc)->size = 3;
        ((Rect_b846_01E00080 *)(s32)&rc)->regs = 0x441;
        ((Rect_b846_01E00080 *)(s32)&rc)->pad4 = 0;
        func_002086D0(&rc, func_00208D00(3));
        alpha = func_00101050(16 - g->t6, 0, 16) * 128 >> 4;
        rc.c.r = 0x80;
        rc.c.g = 0;
        rc.c.b = 0;
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
        func_002075F0(&rc, 0, 0);
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80 - alpha;
        spr.c.q = 1.0f;
        y = 0;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = y;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
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
        g->t6++;
        if (g->t6 > 16) {
            g->on6 = 0;
        }
    }

    if (g->t == 0x53) {
        n = g->cnt;
        g->seg[n].on = 1;
        g->seg[n].t = 0;
        for (j = 0; j < 4; j++) {
            g->seg[n].ang[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->seg[n].pos[j] = g->jp[j];
            g->seg[n].mat[j] = g->jm[j];
        }
        g->cnt++;
        if (g->cnt > 0) {
            g->cnt = 0;
        }
    }

    ((Quad_b846_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b846_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b846_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b846_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (i = 0; i < 1; i++) {
        if (g->seg[i].on == 0) {
            continue;
        }
        a = 48.0f * func_00101020((f32)g->seg[i].t, 8.0f);
        alpha = (u32)((a * func_00100FF0((f32)g->seg[i].t, 198.0f, 190.0f)) * (0.3 + 0.7f * (g->seg[i].t % 2)));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x58;
        pk.v[0].c.b = 0x30;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        v.x = 1.0f;
        v.y = 1.0f;
        v.z = 1.0f;
        v.w = 1.0f;
        for (l = 0; l < 4; l++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->jm[l], &g->jp[l]);
            func_00100E00(m2, g->seg[i].ang[l] + g->seg[i].t * 0x457, 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (k = 0; k < 8; k++) {
                for (j = 0; j < 16; j++) {
                    x = g->qc[k][j] % 4 * 32;
                    y = (g->qc[k][j] >> 2) * 32;
                    a = (f32)x;
                    b = (f32)y;
                    h = (32.0f + a) / 128.0f;
                    a = a / 128.0f;
                    e = b / 64.0f;
                    f = (16.0f + b) / 64.0f;
                    pk.v[0].uv.st.s = a;
                    pk.v[0].uv.st.t = f;
                    pk.v[1].uv.st.s = h;
                    pk.v[1].uv.st.t = f;
                    pk.v[2].uv.st.s = a;
                    pk.v[2].uv.st.t = e;
                    pk.v[3].uv.st.s = h;
                    pk.v[3].uv.st.t = e;
                    if (func_002058D0(&g->q[k][j][0], D_0030FF00, m, &pk, &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        func_002075F0(&pk, ot, 0);
                    }
                }
            }
        }
        ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 5.5f;
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
        a = 64.0f * func_00101020((f32)g->seg[i].t, 8.0f);
        alpha = (u32)((0.6f + 0.4f * (g->seg[i].t % 2)) * (a * func_00100FF0((f32)g->seg[i].t, 198.0f, 190.0f)));
        spr.c.r = 0xFF;
        spr.c.g = 0x58;
        spr.c.b = 0x1C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (l = 0; l < 4; l++) {
            v = g->jp[l];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = 0x600;
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = 0;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = 0x800;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = 0x200;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->seg[i].t++;
        if (g->seg[i].t > 0xC6) {
            g->seg[i].on = 0;
        }
    }

    if (g->t > 0x53 && g->t < 0x119) {
        n = g->cur;
        g->bit[n].on = 1;
        g->bit[n].t = 0;
        for (i = 0; i < 4; i++) {
            g->bit[n].p[i] = g->jp[i];
            for (l = 0; l < 1; l++) {
                g->bit[n].c[i][l] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->bit[n].v[i][l], 0.5f);
            }
        }
        g->cur++;
        if (g->cur > 15) {
            g->cur = 0;
        }
    }

    ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->bit[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->bit[i].t / 16.0f);
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
        alpha = (16 - g->bit[i].t) * 64 >> 4;
        spr.c.r = 0x8A;
        spr.c.g = 0x8A;
        spr.c.b = 0x8A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = func_00100D50(g->bit[i].t, 16, 1);
        for (l = 0; l < 4; l++) {
            for (j = 0; j < 1; j++) {
                func_00187B48(&v, &g->bit[i].v[l][j], f);
                func_00187B00(&v, &v, &g->bit[i].p[l]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->bit[i].c[l][j] % 4 * 32;
                y = (g->bit[i].c[l][j] >> 2) * 32;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->bit[i].t++;
        if (g->bit[i].t > 16) {
            g->bit[i].on = 0;
        }
    }

    if (g->t == 0x96) {
        g->on3 = 1;
        g->t3 = 0;
        for (k = 0; k < 32; k++) {
            g->rc[k] = (func_0019A5C8() >> 23) % 8;
            g->ofs[k] = (func_0019A5C8() >> 23) % 32;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
            g->rm[k] = m4;
        }
    }
    if (g->on3 == 1) {
        ((Quad_b846_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b846_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b846_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b846_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208700(&pk, g->tex[0], 1);
        func_002086D0(&pk, func_00208D00(1));
        func_00208CB0(&pk, 0);
        alpha = (u32)(128.0f * (func_00101020((f32)g->t3, 16.0f) * func_00100FF0((f32)g->t3, 120.0f, 104.0f)));
        pk.v[0].c.r = 0x78;
        pk.v[0].c.g = 0x4B;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0;
        pk.v[2].c.g = 0;
        pk.v[2].c.b = 0;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        for (j = 0; j < 32; j++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->jp[5]);
            m4 = g->rm[j];
            func_00100E00(&m4, g->t3 * 0x21, 2);
            func_00100E00(&m4, g->t3 * 0x2C, 1);
            func_00100E00(&m4, g->t3 * 0x22B, 0);
            func_0020BC00(m2, &m4);
            f = 0.8f + 0.2f * (j + 1) / 32.0f;
            v.x = f;
            v.y = f;
            v.z = f;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            s = 32.0f * ((g->t3 + g->ofs[j]) % 32) / 32.0f;
            x = g->rc[j] % 4 * 32;
            y = (g->rc[j] >> 2) * 32;
            s = (x + s) / 128.0f;
            b = (f32)y;
            e = b / 64.0f;
            h = (32.0f + b) / 64.0f;
            for (k = 0; k < 32; k++) {
                pk.v[0].uv.st.s = s;
                pk.v[0].uv.st.t = e;
                pk.v[1].uv.st.s = s;
                pk.v[1].uv.st.t = e;
                pk.v[2].uv.st.s = s;
                pk.v[2].uv.st.t = h;
                pk.v[3].uv.st.s = s;
                pk.v[3].uv.st.t = h;
                if (func_00100BA0(&g->ring[k].a, &g->ring[k + 1].a, &g->ring[k].b, &g->ring[k + 1].b, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t3++;
        if (g->t3 > 0x78) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x96) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jp[5]);
        func_0020BC00(m, m2);
        a = func_00101020((f32)g->t4, 16.0f);
        a = (0.8f + 0.2f * (g->t4 % 2)) * a;
        alpha = (u32)(128.0f * (a * func_00100FF0((f32)g->t4, 120.0f, 104.0f)));
        spr.c.r = 0x78;
        spr.c.g = 0x4B;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f;
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&out[0], m3, &cn[0]);
        func_001878E0(&out[1], m3, &cn[1]);
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = 0x200;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = 0x200;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = 0x400;
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->t4++;
        if (g->t4 > 0x78) {
            g->on4 = 0;
        }
    }

    if (g->t > 0x95 && g->t < 0x10E) {
        n = g->t % 24;
        g->dart[n].on = 1;
        g->dart[n].t = 0;
        for (y = 0; y < 3; y++) {
            g->dart[n].c[y] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->dart[n].v[y], 0.5f);
        }
    }

    ((Quad_b846_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b846_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b846_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b846_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, 5);
    a = (f32)func_00101050(g->t - 0x95, 0, 16);
    a = a * (f32)func_00101050(0x10E - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 24; i++) {
        if (g->dart[i].on == 0) {
            continue;
        }
        alpha = (u32)(a * ((24 - g->dart[i].t) * 0x50 / 24));
        pk.v[0].c.r = 0x78;
        pk.v[0].c.g = 0x4B;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        func_0020EB40(m);
        v = g->jp[5];
        func_0020C940(m2, 0, 0, &v);
        func_0020BC00(m, m2);
        f = -3.5f * (0.5f + 0.5f * func_00100D50(g->dart[i].t, 24, 1));
        for (k = 0; k < 3; k++) {
            func_00100E40(&m4, &g->dart[i].v[k]);
            func_00100E00(&m4, (i << 16) / 24 + (k << 16) / 3, 2);
            cn[0].x = 0.0f;
            cn[0].y = 0.5f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -0.5f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&out[0], &cn[0], &g->dart[i].v[k]);
            func_00187B00(&out[1], &cn[1], (void *)&g->dart[i].v[k]);
            func_00187B48(&v, &g->dart[i].v[k], f);
            func_00187B00(&out[2], &out[0], &v);
            func_00187B00(&out[3], &out[1], (void *)&v);
            x = g->dart[i].c[k] % 4 * 32;
            y = (g->dart[i].c[k] >> 2) * 32;
            r = (f32)x;
            s = (f32)y;
            h = r / 128.0f;
            e = (32.0f + r) / 128.0f;
            u = s / 64.0f;
            w = (32.0f + s) / 64.0f;
            pk.v[0].uv.st.s = h;
            pk.v[0].uv.st.t = u;
            pk.v[1].uv.st.s = e;
            pk.v[1].uv.st.t = u;
            pk.v[2].uv.st.s = h;
            pk.v[2].uv.st.t = w;
            pk.v[3].uv.st.s = e;
            pk.v[3].uv.st.t = w;
            if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        g->dart[i].t++;
        if (g->dart[i].t > 24) {
            g->dart[i].on = 0;
        }
    }

    if (g->t == 0x87) {
        for (x = 0; x < 24; x++) {
            g->bird[x].on = 1;
            g->bird[x].t = 0;
            g->bird[x].c = (func_0019A5C8() >> 23) % 3 + 1;
            g->bird[x].d = (func_0019A5C8() >> 23) % 2 * 2 - 1;
            func_00101080(&g->bird[x].v, 1.0f);
        }
    }

    ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (l = 0; l < 24; l++) {
        if (g->bird[l].on == 0) {
            continue;
        }
        e = func_00101020((f32)g->bird[l].t, 7.0f);
        alpha = (u32)(255.0f * e);
        spr.c.r = 0x78;
        spr.c.g = 0x4B;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = g->bird[l].c % 4 * 32;
        y = (g->bird[l].c >> 2) * 32;
        g->bird[l].c += g->bird[l].d;
        if (g->bird[l].c == 0 || g->bird[l].c == 4) {
            g->bird[l].d = -g->bird[l].d;
        }
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        f = g->bird[l].t / 15.0f;
        func_00187B18(&v, &g->jp[5], &g->pos2);
        func_00187B48(&v, &v, f);
        func_00187B00(&v, &v, &g->pos2);
        func_00187B48(&v2, &g->bird[l].v, func_0020B550((g->bird[l].t << 15) / 15));
        func_00187B00(&v, &v, &v2);
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        n = g->bird[l].n;
        g->spk[l][n].on = 1;
        g->spk[l][n].t = 0;
        g->spk[l][n].a = e;
        g->spk[l][n].pos = v;
        for (k = 0; k < 2; k++) {
            g->spk[l][n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->spk[l][n].v[k], 0.6f);
        }
        g->bird[l].n++;
        if (g->bird[l].n > 15) {
            g->bird[l].n = 0;
        }
        g->bird[l].t++;
        if (g->bird[l].t > 15) {
            g->bird[l].on = 0;
        }
    }

    ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 24; j++) {
        for (n = 0; n < 16; n++) {
            if (g->spk[j][n].on == 0) {
                continue;
            }
            alpha = (u32)(g->spk[j][n].a * (64.0f * func_0020B480((g->spk[j][n].t << 14) >> 4)));
            spr.c.r = 0x78;
            spr.c.g = 0x4B;
            spr.c.b = 0xFF;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 3.9f * (0.2f + 0.8f * (16 - g->spk[j][n].t) / 16.0f);
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
            b = g->spk[j][n].t;
            h = 18.0f * (b / 16.0f);
            s = 0.2f + 0.8f * b / 16.0f;
            for (k = 0; k < 2; k++) {
                x = g->spk[j][n].c[k] % 4 * 32;
                y = (g->spk[j][n].c[k] >> 2) * 32;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->spk[j][n].v[k].x * s;
                v.y = h + g->spk[j][n].v[k].y * s;
                v.z = g->spk[j][n].v[k].z * s;
                func_00187B00(&v, &v, &g->spk[j][n].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->spk[j][n].t++;
            if (g->spk[j][n].t > 16) {
                g->spk[j][n].on = 0;
            }
        }
    }

    if (g->t == 0x3A) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = 0x400;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = 0x600;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 30.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        a = (16 - g->t5) / 16.0f;
        alpha = (u32)(140.0f * a);
        spr.c.r = 0xFF;
        spr.c.g = 0x20;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jq);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Strip_b846_01E00080 *)(s32)&st)->flags = 0x14;
        ((Strip_b846_01E00080 *)(s32)&st)->size = 8;
        ((Strip_b846_01E00080 *)(s32)&st)->regs = 0x41414141;
        ((Strip_b846_01E00080 *)(s32)&st)->pad4 = 0;
        func_002086D0(&st, func_00208D00(0));
        a = 255.0f * a;
        alpha = (u32)a;
        st.v[0].c.r = 0xFF;
        st.v[0].c.g = 0;
        st.v[0].c.b = 0;
        st.v[0].c.a = alpha;
        st.v[0].c.q = 1.0f;
        st.v[1].c = st.v[0].c;
        st.v[2].c.r = 0;
        st.v[2].c.g = 0;
        st.v[2].c.b = 0;
        st.v[2].c.a = 0;
        st.v[2].c.q = 1.0f;
        st.v[3].c = st.v[2].c;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jq);
        s = 0.3f + 0.7f * func_00100D50(g->t5, 16, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (y = 0; y < 32; y++) {
            if (func_00100BA0(&g->rim[y][1], &g->rim[y + 1][1], &g->rim[y][0], &g->rim[y + 1][0], m, &st, &depth) == 1) {
                st.v[0].p.z = 0xFFFFF8;
                st.v[1].p.z = st.v[0].p.z;
                st.v[2].p.z = st.v[0].p.z;
                st.v[3].p.z = st.v[0].p.z;
                func_002075F0(&st, ot, 0);
            }
            if (func_00100BA0(&g->rim[y][1], &g->rim[y + 1][1], &g->rim[y][2], &g->rim[y + 1][2], m, &st, &depth) == 1) {
                st.v[0].p.z = 0xFFFFF8;
                st.v[1].p.z = st.v[0].p.z;
                st.v[2].p.z = st.v[0].p.z;
                st.v[3].p.z = st.v[0].p.z;
                func_002075F0(&st, ot, 0);
            }
        }
        ((Quad_b846_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b846_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b846_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b846_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[1], 1);
        func_00208CB0(&pk, 0);
        alpha = (u32)a;
        pk.v[0].c.r = 0x78;
        pk.v[0].c.g = 0x78;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0x62;
        pk.v[2].c.g = 0x64;
        pk.v[2].c.b = 0x80;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jq);
        func_0020BC00(m, m2);
        for (i = 0; i < 96; i++) {
            pk.v[0].uv.st.s = 0.5f;
            pk.v[0].uv.st.t = 0.25f;
            pk.v[1].uv.st.s = 0.75f;
            pk.v[1].uv.st.t = 0.25f;
            pk.v[2].uv.st.s = 0.5f;
            pk.v[2].uv.st.t = 0.25f;
            pk.v[3].uv.st.s = 0.75f;
            pk.v[3].uv.st.t = 0.25f;
            if (func_00100BA0(&g->shard[i][0], &g->shard[i][1], &g->shard[i][2], &g->shard[i][3], m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        ((Spr_b846_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b846_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b846_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b846_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b846_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        r = 0.4f;
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
        alpha = (u32)a;
        spr.c.r = 0xC5;
        spr.c.g = 0xC8;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->jq);
        func_0020BC00(m, m2);
        s = 0.8f + 0.2f * func_00100D50(g->t5, 16, 1);
        for (k = 0; k < 128; k++) {
            x = g->c[k] % 4 * 32;
            y = (g->c[k] >> 2) * 32;
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->sv[k], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t5++;
        if (g->t5 > 16) {
            g->on5 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x169 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x7D) {
        ret = 1;
    } else {
        if (g->t == 0x87) {
            ret = 2;
        }
        if (g->t == 0x119) {
            ret = 4;
        }
    }
    g->t++;
    if (g->t > 0x169) {
        ret = 8;
    }
    return ret;
}
