#include "common.h"

/* shape b156:01E00080 (b156), 2429 insns, 1 copy (-O3,p): b156 scene manager (-O3): twin bursts from two joints
   (b141/b175 sections), a double-sprite burst with a ring of quads, thrown spinning sprites shedding shards toward
   the target, 256 falling quads, a 256-sprite burst at the target and a screen blur; returns 1 / 2 / 8 at 64 / 74 /
   139 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b156_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b156_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b156_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b156_01E00080 c;
    Uv_b156_01E00080 uv0;
    Xyz_b156_01E00080 p0;
    Uv_b156_01E00080 uv1;
    Xyz_b156_01E00080 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b156_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b156_01E00080 c;
        Uv_b156_01E00080 uv;
        Xyz_b156_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b156_01E00080;

typedef struct {
    Rgbaq_b156_01E00080 c;
    f32 s, t;
    Xyz_b156_01E00080 p;
} Tv_b156_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b156_01E00080 v[4];
    u8 tail[0x20];
} Quad_b156_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b156_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b156_01E00080 c;
    struct {
        Uv_b156_01E00080 uv;
        Xyz_b156_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Spr4_b156_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][4];
    Vec4f p[2];
    Vec4f v[2][4];
    Vec4f w[2];
} Twin_b156_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f p;
    Vec4f v[8];
} Shard_b156_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f tgt;
    s32 jn[2];
    u8 pad38[8];
    Vec4f jp[2];
    Twin_b156_01E00080 twin[32];
    u8 on1;
    u8 pad1A61[3];
    s32 t1;
    u8 c1[2][32];
    u8 pad1AA8[8];
    Vec4f p1[2];
    Vec4f v1[2][32];
    Vec4f ring[17][2];
    u8 on2;
    u8 pad20F1[3];
    s32 t2;
    u8 c2[2];
    u8 pad20FA[6];
    Mtx_b156_01E00080 mat[2];
    Vec4f p2[2];
    Shard_b156_01E00080 shard[2][32];
    u8 on3;
    u8 pad49A1[3];
    s32 t3;
    u8 c3[256];
    u8 pad4AA8[8];
    Vec4f quad[256][4];
    Vec4f vel[256];
    u8 on4;
    u8 pad9AB1[3];
    s32 t4;
    u8 c4[256];
    u8 pad9BB8[8];
    Vec4f v4[256];
    u8 on5;
    u8 padABC1[3];
    s32 t5;
    u8 padABC8[8];
} Scene_b156_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b156(s32 arg0, s32 code) {
    Scene_b156_01E00080 *g = (Scene_b156_01E00080 *)arg0;
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
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
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
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u16 D_28BBF0[][4];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 c;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 e;
    f32 a;
    f32 b;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b156_01E00080 m4;
    Vec4f v;
    Spr_b156_01E00080 spr __attribute__((aligned(8)));
    Spr4_b156_01E00080 spr2 __attribute__((aligned(8)));
    Quad_b156_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xABD0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x58, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x69, 0);
        for (i = 0; i < 32; i++) {
            g->twin[i].on = 0;
        }
        g->on1 = 0;
        for (i = 0; i < 17; i++) {
            s = func_0020B550((i << 16) >> 4);
            r = func_0020B480((i << 16) >> 4);
            g->ring[i][0].x = 10.0f * s;
            g->ring[i][0].y = 10.0f * r;
            g->ring[i][0].z = 0.0f;
            g->ring[i][0].w = 1.0f;
            g->ring[i][1].x = 20.0f * s;
            g->ring[i][1].y = 20.0f * r;
            g->ring[i][1].z = 0.0f;
            g->ring[i][1].w = 1.0f;
        }
        g->on2 = 0;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 32; j++) {
                g->shard[i][j].on = 0;
            }
        }
        g->on3 = 0;
        g->on4 = 0;
        g->on5 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    if (g->t > 0 && g->t < 0x32) {
        n = g->t % 32;
        g->twin[n].on = 1;
        g->twin[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->twin[n].p[i] = g->jp[i];
            func_00101080(&g->twin[n].w[i], 0.7f);
            for (j = 0; j < 4; j++) {
                g->twin[n].c[i][j] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->twin[n].v[i][j], 0.3f);
            }
        }
    }
    ((Spr_b156_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b156_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b156_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b156_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b156_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->twin[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        alpha = (u32)(96.0f * func_0020B480((g->twin[i].t << 14) >> 5));
        spr.c.r = 0x64;
        spr.c.g = 0x64;
        spr.c.b = 0x64;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 2.5f * (0.5f + 0.5f * g->twin[i].t / 32.0f);
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
        s = g->twin[i].t / 32.0f;
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 4; k++) {
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->twin[i].c[j][k]][0];
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->twin[i].c[j][k]][2];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->twin[i].c[j][k]][1];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->twin[i].c[j][k]][3];
                func_00187B48(&v, &g->twin[i].v[j][k], s);
                h = 15.0f * s;
                v.y += h;
                func_00187B00(&v, &v, &g->twin[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(128.0f * func_0020B480((g->twin[i].t << 14) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0x12;
        spr.c.b = 0x0E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        r = 5.0f * (0.5f + 0.5f * g->twin[i].t / 32.0f);
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
        s = g->twin[i].t / 32.0f;
        for (j = 0; j < 2; j++) {
            func_00187B48(&v, &g->twin[i].w[j], s);
            h = 15.0f * s;
            v.y += h;
            func_00187B00(&v, &v, &g->twin[i].p[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->twin[i].t++;
        if (g->twin[i].t > 0x20) {
            g->twin[i].on = 0;
        }
    }
    if (g->t == 0x32) {
        g->on1 = 1;
        g->t1 = 0;
        for (i = 0; i < 2; i++) {
            g->p1[i] = g->jp[i];
            for (j = 0; j < 32; j++) {
                g->c1[i][j] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->v1[i][j], 0.7f);
                g->v1[i][j].z *= 0.5f;
            }
        }
    }
    if (g->on1 == 1) {
        ((Spr_b156_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b156_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b156_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b156_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b156_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208CB0(&spr, 5);
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (u32)(128.0f * func_0020B480((g->t1 << 14) >> 4));
        spr.c.r = 0x40;
        spr.c.g = 0x40;
        spr.c.b = 0x40;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 4.0f * (0.5f + 0.5f * g->t1 / 16.0f);
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
        r = func_00100D50(g->t1, 0x10, 1);
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 32; j++) {
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->c1[i][j]][0];
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->c1[i][j]][2];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->c1[i][j]][1];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->c1[i][j]][3];
                func_00187B48(&v, &g->v1[i][j], r);
                func_00187B00(&v, &v, &g->p1[i]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        ((Quad_b156_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b156_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b156_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b156_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208CB0(&pk, 5);
        func_00208700(&pk, g->tex[2], 1);
        func_002086D0(&pk, func_00208D00(1));
        h = func_00100FF0((f32)g->t1, 16.0f, 8.0f);
        alpha = (u32)(48.0f * h);
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x40;
        pk.v[0].c.b = 0x20;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        alpha = (u32)(255.0f * h);
        pk.v[2].c.r = 0xFF;
        pk.v[2].c.g = 0x80;
        pk.v[2].c.b = 0x64;
        pk.v[2].c.a = alpha;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        a = func_00100D50(g->t1, 0x10, 1);
        v.x = a;
        v.y = a;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->p1[i]);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (j = 0; j < 16; j++) {
                pk.v[0].s = 0.1f;
                pk.v[0].t = 0.0f;
                pk.v[1].s = 0.9f;
                pk.v[1].t = 0.0f;
                pk.v[2].s = 0.0f;
                pk.v[2].t = 1.0f;
                pk.v[3].s = 1.0f;
                pk.v[3].t = 1.0f;
                if (func_00100BA0(&g->ring[j][0], &g->ring[j + 1][0], &g->ring[j][1], &g->ring[j + 1][1], m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t1++;
        if (g->t1 > 0x10) {
            g->on1 = 0;
        }
    }
    if (g->t == 0x32) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 2; i++) {
            g->c2[i] = (func_0019A5C8() >> 23) % 3;
            func_0020BBB0(&g->mat[i]);
            func_00100E00(&g->mat[i], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            g->p2[i] = g->jp[i];
        }
    }
    if (g->on2 == 1) {
        ((Spr4_b156_01E00080 *)(s32)&spr2)->flags = 0x24;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->size = 9;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->pad4 = 0;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->flags |= 0x800;
        func_00208CB0(&spr2, 0);
        func_00208700(&spr2, g->tex[3], 1);
        func_002086D0(&spr2, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        spr2.c.r = 0x80;
        spr2.c.g = 0x80;
        spr2.c.b = 0x80;
        spr2.c.a = 0x80;
        spr2.c.q = 1.0f;
        a = g->t2 / 24.0f;
        r = 3.0f;
        for (i = 0; i < 2; i++) {
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
            x = g->c2[i] * 64;
            y = 0;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[0].uv)->u = x << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[0].uv)->v = y << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[1].uv)->u = (x + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[1].uv)->v = y << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[2].uv)->u = x << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[2].uv)->v = (y + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[3].uv)->u = (x + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[3].uv)->v = (y + 64) << 4;
            func_00187B18(&v, &g->tgt, &g->p2[i]);
            v.x = g->p2[i].x;
            v.y = v.y * a;
            v.z = v.z * a;
            func_00187B00(&v, &v, &g->p2[i]);
            for (k = 0; k < 4; k++) {
                func_001878E0(&cn[k], &g->mat[i], &cn[k]);
                func_001878E0(&cn[k], m3, &cn[k]);
                func_00187B00(&out[k], &cn[k], &v);
            }
            if (func_00205630(out, D_0030FF00, m, &spr2, &depth) == 1) {
                func_002075F0(&spr2, ot, (u32)depth);
            }
            n = g->t2 % 32;
            g->shard[i][n].on = 1;
            g->shard[i][n].t = 0;
            g->shard[i][n].p = v;
            for (k = 0; k < 8; k++) {
                g->shard[i][n].c[k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->shard[i][n].v[k], 0.7f);
            }
        }
        g->t2++;
        if (g->t2 > 0x18) {
            g->on2 = 0;
        }
    }
    ((Spr_b156_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b156_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b156_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b156_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b156_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 32; j++) {
            if (g->shard[i][j].on == 0) {
                continue;
            }
            alpha = (u32)(128.0f * func_0020B480((g->shard[i][j].t << 14) >> 5));
            spr.c.r = 0x80;
            spr.c.g = 0x20;
            spr.c.b = 0x18;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 5.0f * (0.5f + 0.5f * (0x20 - g->shard[i][j].t) / 32.0f);
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
            b = 0.2f + 0.8f * func_00100D50(g->shard[i][j].t, 0x20, 1);
            for (k = 0; k < 8; k++) {
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->shard[i][j].c[k]][0];
                ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->shard[i][j].c[k]][2];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->shard[i][j].c[k]][1];
                ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->shard[i][j].c[k]][3];
                func_00187B48(&v, &g->shard[i][j].v[k], b);
                func_00187B00(&v, &v, &g->shard[i][j].p);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->shard[i][j].t++;
            if (g->shard[i][j].t > 32) {
                g->shard[i][j].on = 0;
            }
        }
    }
    if (g->t == 0x4A) {
        g->on3 = 1;
        g->t3 = 0;
        r = 0.5f;
        for (i = 0; i < 256; i++) {
            g->c3[i] = (func_0019A5C8() >> 23) % 3;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            g->quad[i][0].x = -r;
            g->quad[i][0].y = -r;
            g->quad[i][0].z = 0.0f;
            g->quad[i][0].w = 1.0f;
            g->quad[i][1].x = r;
            g->quad[i][1].y = -r;
            g->quad[i][1].z = 0.0f;
            g->quad[i][1].w = 1.0f;
            g->quad[i][2].x = -r;
            g->quad[i][2].y = r;
            g->quad[i][2].z = 0.0f;
            g->quad[i][2].w = 1.0f;
            g->quad[i][3].x = r;
            g->quad[i][3].y = r;
            g->quad[i][3].z = 0.0f;
            g->quad[i][3].w = 1.0f;
            for (k = 0; k < 4; k++) {
                func_001878E0(&g->quad[i][k], &m4, &g->quad[i][k]);
            }
            func_00101080(&g->vel[i], 3.0f);
        }
    }
    if (g->on3 == 1) {
        ((Spr4_b156_01E00080 *)(s32)&spr2)->flags = 0x24;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->size = 9;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->pad4 = 0;
        ((Spr4_b156_01E00080 *)(s32)&spr2)->flags |= 0x800;
        func_00208700(&spr2, g->tex[3], 1);
        func_002086D0(&spr2, func_00208D00(0));
        func_00208CB0(&spr2, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (u32)(128.0f * func_00100FF0((f32)g->t3, 64.0f, 32.0f));
        spr2.c.r = 0x80;
        spr2.c.g = 0x80;
        spr2.c.b = 0x80;
        spr2.c.a = alpha;
        spr2.c.q = 1.0f;
        r = 0.1f + 0.9f * func_00100D50(g->t3, 0x40, 1);
        h = 5.0f * (0.5f * (-0.0108962776f * func_001A6C48((f32)g->t3, 2.0f)));
        for (i = 0; i < 256; i++) {
            x = g->c3[i] * 64;
            y = 0;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[0].uv)->u = x << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[0].uv)->v = y << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[1].uv)->u = (x + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[1].uv)->v = y << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[2].uv)->u = x << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[2].uv)->v = (y + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[3].uv)->u = (x + 64) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr2.v[3].uv)->v = (y + 64) << 4;
            func_00187B48(&v, &g->vel[i], r);
            v.y += h;
            func_00187B00(&v, &v, &g->tgt);
            for (k = 0; k < 4; k++) {
                func_001878E0(&cn[k], m3, &g->quad[i][k]);
                func_00187B00(&out[k], &cn[k], &v);
            }
            if (func_00205630(out, D_0030FF00, m, &spr2, &depth) == 1) {
                func_002075F0(&spr2, ot, (u32)depth);
            }
        }
        g->t3++;
        if (g->t3 > 0x40) {
            g->on3 = 0;
        }
    }
    if (g->t == 0x4A) {
        g->on4 = 1;
        g->t4 = 0;
        for (i = 0; i < 256; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->v4[i], 1.2f);
        }
    }
    if (g->on4 == 1) {
        ((Spr_b156_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b156_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b156_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b156_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b156_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
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
        a = 0.1f + 0.9f * func_00100D50(g->t4, 0x20, 1);
        b = func_00100FF0((f32)g->t4, 32.0f, 16.0f);
        s = 0.8f * a;
        r = 100.0f * b;
        h = 128.0f * b;
        for (i = 0; i < 256; i++) {
            if (i % 3 == 0) {
                func_002086D0(&spr, func_00208D00(2));
                e = s;
                alpha = (u32)r;
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                e = a;
                alpha = (u32)h;
                spr.c.r = 0x80;
                spr.c.g = 0x38;
                spr.c.b = 0x26;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->c4[i]][0];
            ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->c4[i]][2];
            ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->c4[i]][1];
            ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->c4[i]][3];
            func_00187B48(&v, &g->v4[i], e);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t4++;
        if (g->t4 > 0x20) {
            g->on4 = 0;
        }
    }
    if (g->t == 0x4A) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Spr_b156_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b156_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b156_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b156_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b156_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 5);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &spr.txa, &spr.txb);
        func_00208460();
        alpha = (0x1C - g->t5) * 32 / 28;
        spr.c.r = 0x80;
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
            ((Uv_b156_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b156_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b156_01E00080 *)(s32)&spr.uv1)->u = (0x280 - x) << 4;
            ((Uv_b156_01E00080 *)(s32)&spr.uv1)->v = (0x1C0 - y) << 4;
            func_002075F0(&spr, 0, 0);
        }
        func_00207FD0(buf, ot, 0);
        g->t5++;
        if (g->t5 > 0x1C) {
            g->on5 = 0;
        }
    }
    if (g->t == 0x40) {
        ret = 1;
    } else if (g->t == 0x4A) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0x8A) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
