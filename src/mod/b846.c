#include "common.h"

/* shape b846:01E00080 (b846), 3982 insns, 1 copy (-O3,p): b846 scene manager; the on4 alpha's third timer read goes
   through a zero index local (beam[n4]), so it is reloaded with lwc1 instead of reusing the % 2 value */

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Beam_b846_01E00080;

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
    Beam_b846_01E00080 beam[1];
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
    s32 n4;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    s32 buf;
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
        for (l = 0; l < 8; l++) {
            u = -6.7f * (l + 1) / 8.0f;
            e = -6.7f * l / 7.0f;
            r = 4.8f * (8 - (l + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                x = (((i << 16) >> 4) + ((l << 13) >> 3)) & 0xFFFF;
                v.x = r * func_0020B550(x);
                v.y = r * func_0020B480(x);
                v.z = e;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->q[l][i][0].x = -0.85f;
                g->q[l][i][0].y = 0.0f;
                g->q[l][i][0].z = 0.0f;
                g->q[l][i][0].w = 1.0f;
                g->q[l][i][1].x = 0.85f;
                g->q[l][i][1].y = 0.0f;
                g->q[l][i][1].z = 0.0f;
                g->q[l][i][1].w = 1.0f;
                g->q[l][i][2].x = -0.85f;
                g->q[l][i][2].y = 0.0f;
                g->q[l][i][2].z = u;
                g->q[l][i][2].w = 1.0f;
                g->q[l][i][3].x = 0.85f;
                g->q[l][i][3].y = 0.0f;
                g->q[l][i][3].z = u;
                g->q[l][i][3].w = 1.0f;
                for (j = 0; j < 4; j++) {
                    func_001878E0(&g->q[l][i][j], &m4, &g->q[l][i][j]);
                }
                g->qc[l][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 1; i++) {
            g->seg[i].on = 0;
        }
        g->cur = 0;
        for (j = 0; j < 16; j++) {
            g->bit[j].on = 0;
        }
        for (l = 0; l < 33; l++) {
            x = (l << 16) >> 5;
            s = func_0020B550(x);
            r = func_0020B480(x);
            g->ring[l].a.x = 3.0f * s;
            g->ring[l].a.y = 3.0f * r;
            g->ring[l].a.z = 0.0f;
            g->ring[l].a.w = 1.0f;
            g->ring[l].b.x = 6.0f * s;
            g->ring[l].b.y = 6.0f * r;
            g->ring[l].b.z = 0.0f;
            g->ring[l].b.w = 1.0f;
        }
        g->on3 = 0;
        g->beam[0].t = 0;
        for (i = 0; i < 24; i++) {
            g->dart[i].on = 0;
        }
        g->cnt3 = 0;
        for (x = 0; x < 24; x++) {
            g->bird[x].on = 0;
            g->bird[x].n = 0;
        }
        for (l = 0; l < 24; l++) {
            for (i = 0; i < 16; i++) {
                g->spk[l][i].on = 0;
            }
        }
        g->on5 = 0;
        for (j = 0; j < 33; j++) {
            x = (j << 16) >> 5;
            s = func_0020B550(x);
            r = func_0020B480(x);
            g->rim[j][0].x = 6.5f * s;
            g->rim[j][0].y = 6.5f * r;
            g->rim[j][0].z = 0.0f;
            g->rim[j][0].w = 1.0f;
            g->rim[j][1].x = 10.8f * s;
            g->rim[j][1].y = 10.8f * r;
            g->rim[j][1].z = 0.0f;
            g->rim[j][1].w = 1.0f;
            g->rim[j][2].x = 11.0f * s;
            g->rim[j][2].y = 11.0f * r;
            g->rim[j][2].z = 0.0f;
            g->rim[j][2].w = 1.0f;
        }
        for (l = 0; l < 96; l++) {
            b = 0.1f + 0.9f * (l + 1) / 96.0f;
            r = b;
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
            for (j = 0; j < 4; j++) {
                func_001878E0(&g->shard[l][j], &m4, &cn[j]);
            }
        }
        for (x = 0; x < 128; x++) {
            g->c[x] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->sv[x], 0.4f);
        }
        g->on6 = 0;
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (l = 0; l < 6; l++) {
        func_001F5620(g->unitA, g->jn[l], &g->jp[l]);
    }
    for (x = 0; x < 4; x++) {
        func_00187B18(&v, &g->jp[x], &g->jp[4]);
        func_00100E40(&g->jm[x], &v);
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
        for (i = 0; i < 4; i++) {
            g->seg[n].ang[i] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->seg[n].pos[i] = g->jp[i];
            g->seg[n].mat[i] = g->jm[i];
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
    for (j = 0; j < 1; j++) {
        if (g->seg[j].on == 0) {
            continue;
        }
        a = 48.0f * func_00101020((f32)g->seg[j].t, 8.0f);
        alpha = (u32)((a * func_00100FF0((f32)g->seg[j].t, 198.0f, 190.0f)) * (0.3 + 0.7f * (g->seg[j].t % 2)));
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
        for (k = 0; k < 4; k++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->jm[k], &g->jp[k]);
            func_00100E00(m2, g->seg[j].ang[k] + g->seg[j].t * 0x457, 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (n = 0; n < 8; n++) {
                for (i = 0; i < 16; i++) {
                    x = g->qc[n][i] % 4 * 32;
                    y = (g->qc[n][i] >> 2) * 32;
                    r = x / 128.0f;
                    a = (32.0f + x) / 128.0f;
                    b = y / 64.0f;
                    h = (16.0f + y) / 64.0f;
                    pk.v[0].uv.st.s = r;
                    pk.v[0].uv.st.t = h;
                    pk.v[1].uv.st.s = a;
                    pk.v[1].uv.st.t = h;
                    pk.v[2].uv.st.s = r;
                    pk.v[2].uv.st.t = b;
                    pk.v[3].uv.st.s = a;
                    pk.v[3].uv.st.t = b;
                    if (func_002058D0(&g->q[n][i][0], D_0030FF00, m, &pk, &depth) == 1) {
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
        a = 64.0f * func_00101020((f32)g->seg[j].t, 8.0f);
        alpha = (u32)((0.6f + 0.4f * (g->seg[j].t % 2)) * (a * func_00100FF0((f32)g->seg[j].t, 198.0f, 190.0f)));
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
        g->seg[j].t++;
        if (g->seg[j].t > 0xC6) {
            g->seg[j].on = 0;
        }
    }

    if (g->t > 0x53 && g->t < 0x119) {
        n = g->cur;
        g->bit[n].on = 1;
        g->bit[n].t = 0;
        for (l = 0; l < 4; l++) {
            g->bit[n].p[l] = g->jp[l];
            for (k = 0; k < 1; k++) {
                g->bit[n].c[l][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->bit[n].v[l][k], 0.5f);
            }
        }
        g->cur++;
        if (g->cur >= 16) {
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
    for (l = 0; l < 16; l++) {
        if (g->bit[l].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->bit[l].t / 16.0f);
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
        alpha = (16 - g->bit[l].t) * 64 >> 4;
        spr.c.r = 0x8A;
        spr.c.g = 0x8A;
        spr.c.b = 0x8A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = func_00100D50(g->bit[l].t, 16, 1);
        for (n = 0; n < 4; n++) {
            for (j = 0; j < 1; j++) {
                func_00187B48(&v, &g->bit[l].v[n][j], f);
                func_00187B00(&v, &v, &g->bit[l].p[n]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->bit[l].c[n][j] % 4 * 32;
                y = (g->bit[l].c[n][j] >> 2) * 32;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->bit[l].t++;
        if (g->bit[l].t > 16) {
            g->bit[l].on = 0;
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
        for (n = 0; n < 32; n++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->jp[5]);
            m4 = g->rm[n];
            func_00100E00(&m4, g->t3 * 0x21, 2);
            func_00100E00(&m4, g->t3 * 0x2C, 1);
            func_00100E00(&m4, g->t3 * 0x22B, 0);
            func_0020BC00(m2, &m4);
            e = 0.8f + 0.2f * (n + 1) / 32.0f;
            v.x = e;
            v.y = e;
            v.z = e;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            s = 32.0f * ((g->t3 + g->ofs[n]) % 32) / 32.0f;
            x = g->rc[n] % 4 * 32;
            y = (g->rc[n] >> 2) * 32;
            s = (x + s) / 128.0f;
            u = y / 64.0f;
            h = (32.0f + y) / 64.0f;
            for (x = 0; x < 32; x++) {
                pk.v[0].uv.st.s = s;
                pk.v[0].uv.st.t = u;
                pk.v[1].uv.st.s = s;
                pk.v[1].uv.st.t = u;
                pk.v[2].uv.st.s = s;
                pk.v[2].uv.st.t = h;
                pk.v[3].uv.st.s = s;
                pk.v[3].uv.st.t = h;
                if (func_00100BA0(&g->ring[x].a, &g->ring[x + 1].a, &g->ring[x].b, &g->ring[x + 1].b, m, &pk, &depth) == 1) {
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
        g->beam[0].on = 1;
        g->beam[0].t = 0;
    }
    if (g->beam[0].on == 1) {
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
        n4 = 0;
        a = func_00101020((f32)g->beam[0].t, 16.0f);
        a = (0.8f + 0.2f * (g->beam[0].t % 2)) * a;
        alpha = (u32)(128.0f * (a * func_00100FF0((f32)g->beam[n4].t, 120.0f, 104.0f)));
        spr.c.r = 0x78;
        spr.c.g = 0x4B;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        w = 8.0f;
        cn[0].x = w;
        cn[0].y = w;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -w;
        cn[1].y = -w;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&out[0], m3, &cn[0]);
        func_001878E0(&out[1], (void *)m3, &cn[1]);
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = 0x200;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = 0x200;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = 0x400;
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->beam[0].t++;
        if (g->beam[0].t > 0x78) {
            g->beam[0].on = 0;
        }
    }

    if (g->t > 0x95 && g->t < 0x10E) {
        n = g->t % 24;
        g->dart[n].on = 1;
        g->dart[n].t = 0;
        for (l = 0; l < 3; l++) {
            g->dart[n].c[l] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->dart[n].v[l], 0.5f);
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
    for (l = 0; l < 24; l++) {
        if (g->dart[l].on == 0) {
            continue;
        }
        alpha = (u32)(a * ((24 - g->dart[l].t) * 0x50 / 24));
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
        f = -3.5f * (0.5f + 0.5f * func_00100D50(g->dart[l].t, 24, 1));
        for (j = 0; j < 3; j++) {
            func_00100E40(&m4, &g->dart[l].v[j]);
            func_00100E00(&m4, (l << 16) / 24 + (j << 16) / 3, 2);
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
            func_00187B00(&out[0], &cn[0], &g->dart[l].v[j]);
            func_00187B00(&out[1], &cn[1], (void *)&g->dart[l].v[j]);
            func_00187B48(&v, &g->dart[l].v[j], f);
            func_00187B00(&out[2], (void *)&out[0], (void *)&v);
            func_00187B00(&out[3], &out[1], (void *)&v);
            x = g->dart[l].c[j] % 4 * 32;
            y = (g->dart[l].c[j] >> 2) * 32;
            h = x / 128.0f;
            e = (32.0f + x) / 128.0f;
            u = y / 64.0f;
            w = (32.0f + y) / 64.0f;
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
        g->dart[l].t++;
        if (g->dart[l].t > 24) {
            g->dart[l].on = 0;
        }
    }

    if (g->t == 0x87) {
        for (j = 0; j < 24; j++) {
            g->bird[j].on = 1;
            g->bird[j].t = 0;
            g->bird[j].c = (func_0019A5C8() >> 23) % 3 + 1;
            g->bird[j].d = (func_0019A5C8() >> 23) % 2 * 2 - 1;
            func_00101080(&g->bird[j].v, 1.0f);
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
    for (i = 0; i < 24; i++) {
        if (g->bird[i].on == 0) {
            continue;
        }
        w = func_00101020((f32)g->bird[i].t, 7.0f);
        alpha = (u32)(255.0f * w);
        spr.c.r = 0x78;
        spr.c.g = 0x4B;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = g->bird[i].c % 4 * 32;
        y = (g->bird[i].c >> 2) * 32;
        g->bird[i].c += g->bird[i].d;
        if (g->bird[i].c == 0 || g->bird[i].c == 4) {
            g->bird[i].d = -g->bird[i].d;
        }
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        a = 3.0f;
        cn[0].x = -a;
        cn[0].y = -a;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = a;
        cn[1].y = a;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        f = g->bird[i].t / 15.0f;
        func_00187B18(&v, &g->jp[5], &g->pos2);
        func_00187B48(&v, &v, f);
        func_00187B00(&v, &v, &g->pos2);
        func_00187B48(&v2, &g->bird[i].v, func_0020B550((g->bird[i].t << 15) / 15));
        func_00187B00(&v, &v, &v2);
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        n = g->bird[i].n;
        g->spk[i][n].on = 1;
        g->spk[i][n].t = 0;
        g->spk[i][n].a = w;
        g->spk[i][n].pos = v;
        for (j = 0; j < 2; j++) {
            g->spk[i][n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->spk[i][n].v[j], 0.6f);
        }
        g->bird[i].n++;
        if (g->bird[i].n >= 16) {
            g->bird[i].n = 0;
        }
        g->bird[i].t++;
        if (g->bird[i].t > 15) {
            g->bird[i].on = 0;
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
    for (k = 0; k < 24; k++) {
        for (i = 0; i < 16; i++) {
            if (g->spk[k][i].on == 0) {
                continue;
            }
            alpha = (u32)(g->spk[k][i].a * (64.0f * func_0020B480((g->spk[k][i].t << 14) >> 4)));
            spr.c.r = 0x78;
            spr.c.g = 0x4B;
            spr.c.b = 0xFF;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 3.9f * (0.2f + 0.8f * (16 - g->spk[k][i].t) / 16.0f);
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
            l = g->spk[k][i].t;
            b = l / 16.0f;
            s = 0.2f + 0.8f * l / 16.0f;
            u = 18.0f * b;
            for (j = 0; j < 2; j++) {
                x = g->spk[k][i].c[j] % 4 * 32;
                y = (g->spk[k][i].c[j] >> 2) * 32;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->spk[k][i].v[j].x * s;
                v.y = u + g->spk[k][i].v[j].y * s;
                v.z = g->spk[k][i].v[j].z * s;
                func_00187B00(&v, &v, &g->spk[k][i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->spk[k][i].t++;
            if (g->spk[k][i].t > 16) {
                g->spk[k][i].on = 0;
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
        h = 30.0f;
        cn[0].x = -h;
        cn[0].y = -h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = h;
        cn[1].y = h;
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
        for (n = 0; n < 32; n++) {
            if (func_00100BA0(&g->rim[n][1], &g->rim[n + 1][1], &g->rim[n][0], &g->rim[n + 1][0], m, &st, &depth) == 1) {
                st.v[0].p.z = 0xFFFFF8;
                st.v[1].p.z = st.v[0].p.z;
                st.v[2].p.z = st.v[0].p.z;
                st.v[3].p.z = st.v[0].p.z;
                func_002075F0(&st, ot, 0);
            }
            if (func_00100BA0(&g->rim[n][1], &g->rim[n + 1][1], &g->rim[n][2], &g->rim[n + 1][2], m, &st, &depth) == 1) {
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
        for (l = 0; l < 96; l++) {
            pk.v[0].uv.st.s = 0.5f;
            pk.v[0].uv.st.t = 0.25f;
            pk.v[1].uv.st.s = 0.75f;
            pk.v[1].uv.st.t = 0.25f;
            pk.v[2].uv.st.s = 0.5f;
            pk.v[2].uv.st.t = 0.25f;
            pk.v[3].uv.st.s = 0.75f;
            pk.v[3].uv.st.t = 0.25f;
            if (func_00100BA0(&g->shard[l][0], &g->shard[l][1], &g->shard[l][2], &g->shard[l][3], m, &pk, &depth) == 1) {
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
        h = 0.4f;
        cn[0].x = -h;
        cn[0].y = -h;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = h;
        cn[1].y = h;
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
        for (l = 0; l < 128; l++) {
            x = g->c[l] % 4 * 32;
            y = (g->c[l] >> 2) * 32;
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b846_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->sv[l], s);
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
