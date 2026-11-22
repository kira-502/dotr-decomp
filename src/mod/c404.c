#include "common.h"

/* shape c404:01E00080 (c404), 329 insns, 1 copy: whole-module draw: code >= 0 clears 64 slots of 8 sprite quads; else
   from tick 13 to 67 fills slot t % 64 with 8 random cells and offsets, then draws every live slot growing and fading
   over 64 ticks; returns 8 after tick 132 */

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
} Uv_c404_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c404_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_c404_01E00080 uv0;
    Xyz_c404_01E00080 p0;
    Uv_c404_01E00080 uv1;
    Xyz_c404_01E00080 p1;
    u8 tail[0x20];
} Spr_c404_01E00080;

typedef struct {
    Vec4f pos;
    u8 pad10[0x24];
} Pos_c404_01E00080;

typedef struct {
    u8 used;
    s32 t;
    u8 kind[8];
    Vec4f pos[8];
} Slot_c404_01E00080;

typedef struct {
    s32 t;
    void *tex0;
    void *tex1;
    void *tex2;
    Vec4f pos;
    Slot_c404_01E00080 slot[64];
} Ctx_c404_01E00080;

static s32 func_01E00080_c404(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void *func_00202BF0(s32, s32);
    extern Pos_c404_01E00080 D_00298BA0[];
    extern u8 D_0030FF00[];
    extern void func_00205CA0(void *);
    extern void func_00101080(f32, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(f32, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, void *, s32);
    extern void func_0020BC00(void *, void *);
    s32 ret;
    u8 *ot;
    s32 i;
    s32 j;
    s32 l;
    s32 n;
    s32 u;
    s32 w;
    s32 x;
    s32 y;
    u8 al;
    f32 f;
    f32 sc;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f v[2];
    Vec4f out[2];
    Vec4f c;
    Spr_c404_01E00080 pk __attribute__((aligned(8)));
    f32 depth;
    Ctx_c404_01E00080 *g = (Ctx_c404_01E00080 *)arg0;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2420);
        g->t = 0;
        g->tex0 = func_00202BF0(8, 0x18);
        g->tex1 = func_00202BF0(8, 0x19);
        g->tex2 = func_00202BF0(8, 0x1A);
        g->pos = D_00298BA0[code].pos;
        g->pos.y += 5.0f;
        for (i = 0; i < 64; i++) {
            g->slot[i].used = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    if (g->t > 12 && g->t < 68) {
        n = g->t % 64;
        (void)n;
        g->slot[n].used = 1;
        g->slot[n].t = 0;
        for (i = 0; i < 8; i++) {
            g->slot[n].kind[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(0.7f, &g->slot[n].pos[i]);
            g->slot[n].pos[i].y *= 0.5f;
        }
    }
    ((Spr_c404_01E00080 *)(s32)&pk)->flags = 0x26;
    ((Spr_c404_01E00080 *)(s32)&pk)->size = 5;
    ((Spr_c404_01E00080 *)(s32)&pk)->regs = 0x42421;
    ((Spr_c404_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Spr_c404_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(0));
    func_00208700(&pk, g->tex1, 1);
    func_00208CB0(&pk, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 64; i++) {
        if (g->slot[i].used != 0) {
            sc = 3.0f * (0.8f + 0.2f * (f32)g->slot[i].t / 64.0f);
            v[0].x = -sc;
            v[0].y = -sc;
            v[0].z = 0.0f;
            v[0].w = 1.0f;
            v[1].x = sc;
            v[1].y = sc;
            v[1].z = 0.0f;
            v[1].w = 1.0f;
            func_001878E0(&v[0], m3, &v[0]);
            func_001878E0(&v[1], m3, &v[1]);
            al = (u32)(128.0f * func_0020B550((g->slot[i].t << 15) >> 6));
            pk.r = 0x9E;
            pk.g = 0x8A;
            pk.b = 0x50;
            pk.a = al;
            pk.q = 1.0f;
            f = func_00100D50(g->slot[i].t, 0x40, 1);
            for (l = 0; l < 8; l++) {
                u = g->slot[i].kind[l] % 4;
                w = g->slot[i].kind[l] / 4;
                x = u * 32;
                y = w * 32;
                ((Uv_c404_01E00080 *)(s32)&pk.uv0)->u = x << 4;
                ((Uv_c404_01E00080 *)(s32)&pk.uv0)->v = y << 4;
                ((Uv_c404_01E00080 *)(s32)&pk.uv1)->u = (x + 32) << 4;
                ((Uv_c404_01E00080 *)(s32)&pk.uv1)->v = (y + 32) << 4;
                func_00187B48(f, &c, &g->slot[i].pos[l]);
                func_00187B00(&c, &c, &g->pos);
                func_00187B00(&out[0], &v[0], &c);
                func_00187B00(&out[1], &v[1], (Vec4f *)&c);
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, 0);
                }
            }
            g->slot[i].t++;
            if (g->slot[i].t > 64) {
                g->slot[i].used = 0;
            }
        }
    }
    g->t++;
    if (g->t > 132) {
        ret = 8;
    }
    return ret;
}
