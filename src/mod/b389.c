#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b389", func_01E00080_b389);

/* shape b389:01E02160, 555 insns, 1 copy (-O3,p): draws a two-layer 32x17 cone grid (b511:01E03A70 with other
   constants): a sine-rippled ring grid faded by two timer ramps and a pulse, triangles to an apex for the last row,
   textured quads elsewhere, each drawn where both layers project */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b389_01E02160;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b389_01E02160;

typedef struct {
    Rgbaq_b389_01E02160 c;
    f32 s, t;
    Xyz_b389_01E02160 p;
} Tv_b389_01E02160;

typedef struct {
    u64 d;
} Reg_b389_01E02160;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b389_01E02160 v[3];
    u64 pad58;
    Reg_b389_01E02160 tex0;
    Reg_b389_01E02160 tex1;
    u64 tail;
} Tri_b389_01E02160;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b389_01E02160 v[4];
    u64 pad70;
    Reg_b389_01E02160 tex0;
    Reg_b389_01E02160 tex1;
    u64 tail;
} Quad_b389_01E02160;

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad40[0x3544];
    s32 t;
    u8 pad2CF8[8];
    union {
        Vec4f lo[40][17];
        struct {
            u8 pad[0x2200];
            Vec4f hi[32][17];
        } s;
    } u;
} Obj_b389_01E02160;

extern Obj_b389_01E02160 *D_01E02A80_b389;

#pragma optimization_level 3

static void func_01E02160_b389(void *buf) {
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void *func_00207650(void *, void *, s32, s32);
    Obj_b389_01E02160 *g __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f v;
    Tri_b389_01E02160 tri __attribute__((aligned(8)));
    Quad_b389_01E02160 pk __attribute__((aligned(8)));
    Rgbaq_b389_01E02160 c;
    f32 depth;
    void *p;
    s32 k;
    f32 s;
    f32 h;
    f32 rad;
    s32 t;
    f32 r;
    u16 a;
    u16 b;

    g = D_01E02A80_b389;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0((s32)m3);
    func_0020EB40(m);
    v = g->pos;
    func_00187B60(m2, m3, &v);
    func_0020BC00((s32)m, m2);
    ((Tri_b389_01E02160 *)(s32)&tri)->flags = 0x33;
    ((Tri_b389_01E02160 *)(s32)&tri)->size = 9;
    ((Tri_b389_01E02160 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b389_01E02160 *)(s32)&tri)->pad4 = 0;
    ((Quad_b389_01E02160 *)(s32)&pk)->flags = 0x34;
    ((Quad_b389_01E02160 *)(s32)&pk)->size = 0xC;
    ((Quad_b389_01E02160 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b389_01E02160 *)(s32)&pk)->pad4 = 0;
    p = (void *)func_00208870(func_0020F290((s32)p), -1, 1, &tri.tex0, &tri.tex1);
    pk.tex0 = tri.tex0;
    pk.tex1 = tri.tex1;
    p = (void *)func_0020F290((s32)p);
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((s64)0x700 << 32) | 0xA0000A);
    ((Tri_b389_01E02160 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Quad_b389_01E02160 *)(s32)&pk)->flags |= 0x800;
    s = func_00101020(g->t, 16.0f);
    s *= func_00100FF0(g->t, 300.0f, 284.0f);
    r = s * (0.1f + 0.9f * func_001A6970(func_0020B550((u16)(g->t % 64 << 16 >> 6))));
    tri.v[0].c.r = 0xFF;
    tri.v[0].c.g = 0xFF;
    tri.v[0].c.b = 0xFF;
    tri.v[0].c.a = (u32)(128.0f * r);
    tri.v[0].c.q = 1.0f;
    tri.v[1].c = tri.v[0].c;
    tri.v[2].c = tri.v[0].c;
    c = tri.v[0].c;
    pk.v[0].c = c;
    pk.v[1].c = c;
    pk.v[2].c = c;
    pk.v[3].c = c;
    t = g->t;
    for (i = 0; i < 32; i++) {
        rad = 30.0f * (f32)(32 - i) / 32.0f;
        h = (f32)(i + 1) / 32.0f;
        for (k = 0; k < 17; k++) {
            r = 1.0f + h * (0.3f * func_0020B480((u16)(t * 211 + (((i * 0x20000) >> 5) + ((k * 0x20000) >> 4)))));
            a = (s32)((f32)((k * 0x10000) >> 4) +
                      h * (1820.0f * func_0020B480((u16)(((i * 0x4000) >> 5) + t * 111))));
            g->u.s.hi[i][k].x = rad * r * func_0020B550(a);
            g->u.s.hi[i][k].y = rad * r * func_0020B480(a);
            g->u.s.hi[i][k].z = 0.0f;
            g->u.s.hi[i][k].w = 1.0f;
        }
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    for (i = 0; i < 32; i++) {
        if (i == 31) {
            for (k = 0; k < 16; k++) {
                if (func_00100B00(&v, &g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], m, &tri, &depth) == 1) {
                    func_00100C60(&tri.v[0].s, &tri.v[0].p, 0, 0);
                    func_00100C60(&tri.v[1].s, &tri.v[1].p, 0, 0);
                    func_00100C60(&tri.v[2].s, &tri.v[2].p, 0, 0);
                    if (func_00100B00(&v, &g->u.lo[i][k], &g->u.lo[i][k + 1], m, &tri, &depth) == 1) {
                        tri.v[0].p.z = 0xFFFFF8;
                        tri.v[1].p.z = tri.v[0].p.z;
                        tri.v[2].p.z = tri.v[0].p.z;
                        p = func_00207650(p, &tri, 0, 0);
                    }
                }
            }
        } else {
            for (k = 0; k < 16; k++) {
                if (func_00100BA0(&g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], &g->u.s.hi[i + 1][k],
                                  &g->u.s.hi[i + 1][k + 1], m, &pk, &depth) == 1) {
                    func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                    func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                    func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                    func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                    if (func_00100BA0(&g->u.lo[i][k], &g->u.lo[i][k + 1], &g->u.lo[i + 1][k],
                                      &g->u.lo[i + 1][k + 1], m, &pk, &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        p = func_00207650(p, &pk, 0, 0);
                    }
                }
            }
        }
    }
    func_00209F70(p, 0);
}

#pragma optimization_level reset
