#include "common.h"

/* shape b620:01E00080 (b620), 1939 insns, 1 copy: b620 module main (written from the asm, b290's family): code >= 0
   clears the 0xB0F0 scene, takes both units, three textures, the target and six joints, builds a 33-point double
   ring, a 33-point band and a 17-point ring; else every tenth tick spawns an expanding line-ring wave (8 slots), on
   0..0x122 draws four spinning banded textured rings round the unit, fires the six joint trails (func_01E01ED0) on
   their schedules, draws the trail heads leaving 16-slot four-sprite puffs and at frame 32 a ring swirl (textured
   strip plus sprite); returns 1 / 6 / 2 / 8 at 0x79 / 0x84..0x118 / 0x119 / >0x139 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b620_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b620_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b620_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b620_01E00080 c;
    Uv_b620_01E00080 uv0;
    Xyz_b620_01E00080 p0;
    Uv_b620_01E00080 uv1;
    Xyz_b620_01E00080 p1;
    u8 tail[0x20];
} Spr_b620_01E00080;

typedef struct {
    Rgbaq_b620_01E00080 c;
    f32 s, t;
    Xyz_b620_01E00080 p;
} Tv_b620_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b620_01E00080 v[4];
    u8 tail[0x20];
} Tex_b620_01E00080;

typedef struct {
    Rgbaq_b620_01E00080 c;
    Xyz_b620_01E00080 p;
} Lv_b620_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b620_01E00080 v[4];
    u8 tail[8];
} Line_b620_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b620_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b620_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
} Band_b620_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Wave_b620_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 n;
    u8 pad9[3];
    f32 len;
    Vec4f pos;
    Mtx_b620_01E00080 mat;
} Rec_b620_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Vec4f v[4];
} Puff_b620_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Mtx_b620_01E00080 mat;
} Swirl_b620_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f pos;
    Vec4f top;
    s32 bone[6];
    u8 pad58[8];
    Vec4f bp[6];
    Ring_b620_01E00080 ring[33];
    s32 nw;
    Wave_b620_01E00080 w[8];
    u8 pad734[0xC];
    Band_b620_01E00080 band[33];
    u8 on;
    u8 padB61[3];
    s32 t2;
    s32 cnt[6];
    s32 cur[6];
    u8 padB98[8];
    Rec_b620_01E00080 rec[6][4];
    Puff_b620_01E00080 puff[6][4][16];
    Ring_b620_01E00080 ring3[17];
    s32 nc[6];
    u8 padA7E8[8];
    Swirl_b620_01E00080 sw[6][4];
} Scene_b620_01E00080;

static s32 func_01E00080_b620(Scene_b620_01E00080 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
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
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern s32 b620_01E01ED0();
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 n;
    s32 c;
    s32 x;
    s32 ang;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 b;
    f32 a;
    f32 u;
    f32 u1;
    f32 u5;
    f32 s0;
    f32 su;
    f32 sv;
    f32 s1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Line_b620_01E00080 lp __attribute__((aligned(8)));
    Tex_b620_01E00080 pk __attribute__((aligned(8)));
    Spr_b620_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB0F0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F53C0(1, g->unitB, &g->top);
        g->bone[0] = func_001F5560(g->unitA, 0x29, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x34, 0);
        g->bone[2] = func_001F5560(g->unitA, 0x3E, 0);
        g->bone[3] = func_001F5560(g->unitA, 0x50, 0);
        g->bone[4] = func_001F5560(g->unitA, 0x47, 0);
        g->bone[5] = func_001F5560(g->unitA, 0x59, 0);
        for (i = 0; i < 33; i++) {
            ang = (i << 16) >> 5;
            g->ring[i].a.x = 17.0f * func_0020B550(ang);
            g->ring[i].a.y = 17.0f * func_0020B480(ang);
            g->ring[i].a.z = 0.0f;
            g->ring[i].a.w = 1.0f;
            g->ring[i].b.x = 20.0f * func_0020B550(ang);
            g->ring[i].b.y = 20.0f * func_0020B480(ang);
            g->ring[i].b.z = 0.0f;
            g->ring[i].b.w = 1.0f;
            func_00187B00(&g->ring[i].mid, &g->ring[i].a, &g->ring[i].b);
            { Vec4f *pm = &g->ring[i].mid; func_00187B48(pm, pm, 0.5f); }
        }
        g->nw = 0;
        for (i = 0; i < 8; i++) {
            g->w[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            ang = (i << 16) >> 5;
            g->band[i].a.x = 16.0f * func_0020B550(ang);
            g->band[i].a.y = 16.0f * func_0020B480(ang);
            g->band[i].a.z = 1.0f;
            g->band[i].a.w = 1.0f;
            g->band[i].b = g->band[i].a;
            g->band[i].b.z *= -1.0f;
        }
        g->on = 0;
        for (i = 0; i < 6; i++) {
            g->cnt[i] = 0;
            g->cur[i] = 0;
            for (j = 0; j < 4; j++) {
                g->rec[i][j].on = 0;
                g->rec[i][j].n = 0;
            }
        }
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 16; k++) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 17; i++) {
            ang = (i << 16) >> 4;
            g->ring3[i].a.x = 20.0f * func_0020B550(ang);
            g->ring3[i].a.y = 20.0f * func_0020B480(ang);
            g->ring3[i].a.z = 0.0f;
            g->ring3[i].a.w = 1.0f;
            g->ring3[i].b.x = 50.0f * func_0020B550(ang);
            g->ring3[i].b.y = 50.0f * func_0020B480(ang);
            g->ring3[i].b.z = 0.0f;
            g->ring3[i].b.w = 1.0f;
            func_00187B00(&g->ring3[i].mid, &g->ring3[i].a, &g->ring3[i].b);
            { Vec4f *pm = &g->ring3[i].mid; func_00187B48(pm, pm, 0.5f); }
        }
        for (i = 0; i < 6; i++) {
            g->nc[i] = 0;
            for (j = 0; j < 4; j++) {
                g->sw[i][j].on = 0;
            }
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (i = 0; i < 6; i++) {
        func_001F5620(g->unitA, g->bone[i], &g->bp[i]);
    }
    if (g->t % 10 == 0 && g->t > 0 && g->t < 0x122) {
        n = g->nw;
        g->w[n].on = 1;
        g->w[n].t = 0;
        g->nw++;
        if (g->nw >= 8) {
            g->nw = 0;
        }
    }

    ((Line_b620_01E00080 *)(s32)&lp)->flags = 0x14;
    ((Line_b620_01E00080 *)(s32)&lp)->size = 8;
    ((Line_b620_01E00080 *)(s32)&lp)->regs = 0x41414141;
    ((Line_b620_01E00080 *)(s32)&lp)->pad4 = 0;
    func_002086D0(&lp, func_00208D00(1));
    x = g->t;
    su = (f32)func_00101050(0x122 - x, 0, 32) / 32.0f;
    su = (0.8f + 0.2f * (g->t % 2)) * su;
    r = (f32)func_00101050(x, 0, 32) / 32.0f;
    for (i = 0; i < 8; i++) {
        if (g->w[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos);
        s = 0.6f + 0.4f * func_00100D50(g->w[i].t, 32, 1);
        s *= r;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        f = func_0020B550((g->w[i].t << 15) >> 5);
        f *= su;
        lp.v[0].c.r = 0;
        lp.v[0].c.g = 0;
        lp.v[0].c.b = 0x80;
        lp.v[0].c.a = 0;
        lp.v[0].c.q = 1.0f;
        lp.v[1].c = lp.v[0].c;
        alpha = (u32)(255.0f * f);
        (void)alpha;
        lp.v[2].c.r = 0x18;
        lp.v[2].c.g = 0x40;
        lp.v[2].c.b = 0xFF;
        lp.v[2].c.a = alpha;
        lp.v[2].c.q = 1.0f;
        lp.v[3].c = lp.v[2].c;
        for (j = 0; j < 32; j++) {
            if (func_00100BA0(&g->ring[j].a, &g->ring[j + 1].a, &g->ring[j].mid, &g->ring[j + 1].mid, m, &lp,
                              &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
            if (func_00100BA0(&g->ring[j].b, &g->ring[j + 1].b, &g->ring[j].mid, &g->ring[j + 1].mid, m, &lp,
                              &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
        }
        g->w[i].t++;
        if (g->w[i].t > 32) {
            g->w[i].on = 0;
        }
    }

    if (g->t == 0) {
        g->on = 1;
        g->t2 = 0;
    }
    if (g->on == 1) {
        ((Tex_b620_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Tex_b620_01E00080 *)(s32)&pk)->size = 0xC;
        ((Tex_b620_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Tex_b620_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        f = (f32)func_00101050(g->t2, 0, 32) * (f32)func_00101050(0x122 - g->t2, 0, 32) / 1024.0f;
        s = (f32)func_00101050(g->t2, 0, 32) / 32.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (i = 0; i < 4; i++) {
            alpha = (u32)(128.0f * f * (0.2f + 0.8f * func_001A6970(func_0020B550((g->t2 * 0x29A + i * 0x15B3) & 0xFFFF))));
            pk.v[0].c.r = 0xA4;
            pk.v[0].c.g = 0xA4;
            pk.v[0].c.b = 0x80;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->pos);
            func_00100E00(m2, g->t2 * 0x14D, 2);
            func_00100E00(m2, g->t2 * 0x14D + i * 0x15B3, 0);
            func_00100E00(m2, g->t2 * 0x14D + i * 0x1E61, 1);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (j = 0; j < 32; j++) {
                k = i + j;
                su = 0.25f * (k % 4);
                sv = 0.25f * (k >> 2);
                pk.v[0].s = su;
                pk.v[0].t = sv;
                pk.v[1].s = 0.25f + su;
                pk.v[1].t = sv;
                pk.v[2].s = su;
                pk.v[2].t = 0.25f + sv;
                pk.v[3].s = 0.25f + su;
                pk.v[3].t = 0.25f + sv;
                if (func_00100BA0(&g->band[j].a, &g->band[j + 1].a, &g->band[j].b, &g->band[j + 1].b, m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 0x122) {
            g->on = 0;
        }
    }

    if (g->t == g->cnt[0] * 10 + 99 && g->t < 250) {
        b620_01E01ED0(g, 0);
    }
    if (g->t == g->cnt[1] * 10 + 104 && g->t < 245) {
        b620_01E01ED0(g, 1);
    }
    if (g->t == g->cnt[2] * 10 + 106 && g->t < 247) {
        b620_01E01ED0(g, 2);
    }
    if (g->t == g->cnt[3] * 10 + 101 && g->t < 242) {
        b620_01E01ED0(g, 3);
    }
    if (g->t == g->cnt[4] * 10 + 103 && g->t < 244) {
        b620_01E01ED0(g, 4);
    }
    if (g->t == g->cnt[5] * 10 + 107 && g->t < 248) {
        b620_01E01ED0(g, 5);
    }

    ((Spr_b620_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b620_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b620_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b620_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b620_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->v = 0x800;
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
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            if (g->rec[i][j].on == 0) {
                continue;
            }
            spr.c.r = 0xFF;
            spr.c.g = 0xC4;
            spr.c.b = 0xB4;
            spr.c.a = 0xFF;
            spr.c.q = 1.0f;
            f = g->rec[i][j].t / 32.0f;
            v.x = 0.0f;
            v.y = 40.0f * (4.0f * f + -4.0f * f * f);
            v.z = f * g->rec[i][j].len;
            v.w = 1.0f;
            func_001878E0(&v, &g->rec[i][j].mat, &v);
            func_00187B00(&v, &v, &g->rec[i][j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            n = g->rec[i][j].n;
            g->puff[i][j][n].on = 1;
            g->puff[i][j][n].t = 0;
            g->puff[i][j][n].pos = v;
            for (k = 0; k < 4; k++) {
                func_00101080(&g->puff[i][j][n].v[k], 0.3f);
            }
            g->rec[i][j].n++;
            if (g->rec[i][j].n >= 16) {
                g->rec[i][j].n = 0;
            }
            if (g->rec[i][j].t == 32) {
                c = g->nc[i];
                g->sw[i][c].on = 1;
                g->sw[i][c].t = 0;
                g->sw[i][c].pos = v;
                func_0020BBB0(&g->sw[i][c].mat);
                func_00100E00(&g->sw[i][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 0);
                func_00100E00(&g->sw[i][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 1);
                func_00100E00(&g->sw[i][c].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->nc[i]++;
                if (g->nc[i] >= 4) {
                    g->nc[i] = 0;
                }
            }
            g->rec[i][j].t++;
            if (g->rec[i][j].t > 32) {
                g->rec[i][j].on = 0;
            }
        }
    }

    ((Spr_b620_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b620_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b620_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b620_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b620_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    r = 1.5f;
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
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 16; k++) {
                if (g->puff[i][j][k].on == 0) {
                    continue;
                }
                alpha = (16 - g->puff[i][j][k].t) * 255 >> 4;
                spr.c.r = 0xFF;
                spr.c.g = 0x8C;
                spr.c.b = 0x82;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->puff[i][j][k].t, 16, 1);
                for (q = 0; q < 4; q++) {
                    func_00187B48(&v, &g->puff[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->puff[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->puff[i][j][k].t++;
                if (g->puff[i][j][k].t > 16) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
    }

    ((Tex_b620_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b620_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b620_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b620_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 0);
    ((Spr_b620_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b620_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b620_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b620_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b620_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b620_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    r = 35.0f;
    cn[0].x = -r;
    cn[0].y = -r;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = r;
    cn[1].y = r;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            if (g->sw[i][j].on == 0) {
                continue;
            }
            f = func_00100FF0((f32)g->sw[i][j].t, 32.0f, 16.0f);
            pk.v[0].c.r = 0x60;
            pk.v[0].c.g = 0x26;
            pk.v[0].c.b = 0x1C;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            alpha = (u32)(196.0f * f);
            (void)alpha;
            pk.v[2].c.r = 0xFF;
            pk.v[2].c.g = 0x62;
            pk.v[2].c.b = 0x4E;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->sw[i][j].pos);
            func_0020BC00(m2, &g->sw[i][j].mat);
            s = 0.1f + 0.9f * func_00100D50(g->sw[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = 0.0f;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            u = -1.0f * (g->sw[i][j].t % 64) / 64.0f;
            u1 = 0.5f + u;
            u5 = 1.0f + u;
            for (q = 0; q < 16; q++) {
                s0 = 6.0f * q / 16.0f;
                s1 = 6.0f * (q + 1) / 16.0f;
                pk.v[0].s = s0;
                pk.v[0].t = u;
                pk.v[1].s = s1;
                pk.v[1].t = u;
                pk.v[2].s = s0;
                pk.v[2].t = u1;
                pk.v[3].s = s1;
                pk.v[3].t = u1;
                if (func_00100BA0(&g->ring3[q].a, &g->ring3[q + 1].a, &g->ring3[q].mid, &g->ring3[q + 1].mid, m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
                pk.v[0].s = s0;
                pk.v[0].t = u5;
                pk.v[1].s = s1;
                pk.v[1].t = u5;
                pk.v[2].s = s0;
                pk.v[2].t = u1;
                pk.v[3].s = s1;
                pk.v[3].t = u1;
                if (func_00100BA0(&g->ring3[q].b, &g->ring3[q + 1].b, &g->ring3[q].mid, &g->ring3[q + 1].mid, m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
            alpha = (u32)(255.0f * func_00100FF0((f32)g->sw[i][j].t, 32.0f, 16.0f));
            spr.c.r = 0xFF;
            spr.c.g = 0x80;
            spr.c.b = 0x5A;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->sw[i][j].pos);
            s = 0.1f + 0.9f * func_00100D50(g->sw[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = s;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->sw[i][j].t++;
            if (g->sw[i][j].t > 32) {
                g->sw[i][j].on = 0;
            }
        }
    }

    if (g->t == 0x79) {
        ret = 1;
    } else {
        if (g->t > 0x83 && g->t < 0x119) {
            ret = 6;
        }
        if (g->t == 0x119) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x139) {
        ret = 8;
    }
    return ret;
}

/* shape b620:01E01ED0, 106 insns: record a new step in one of the scene's 4-entry trails (track i): mark the next record, copy the track's point, store the distance to the scene centre (+0x30) and a direction (func_00100E40) with a random twist, then advance the track's count and index (wrapping at 4) */

typedef struct {
    f32 x, y, z, w;
} V4_b620_01E01ED0;

typedef struct {
    s8 on;
    u8 pad1[3];
    s32 w4;
    u8 pad8[4];
    f32 len;
    V4_b620_01E01ED0 pos;
    u8 q[0x40];
} Rec_b620_01E01ED0;

typedef struct {
    u8 pad0[0x30];
    V4_b620_01E01ED0 c;
    u8 pad40[0x20];
    V4_b620_01E01ED0 pt[1];
    u8 pad70[0xB68 - 0x70];
    s32 cnt[6];
    s32 cur[8];
    Rec_b620_01E01ED0 rec[1][4];
} Scene_b620_01E01ED0;

#pragma opt_propagation off

static void func_01E01ED0_b620(Scene_b620_01E01ED0 *g0, s32 i) {
    Scene_b620_01E01ED0 *g = g0;
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    V4_b620_01E01ED0 v;
    s32 c;

    c = g->cur[i];
    g->rec[i][c].on = 1;
    g->rec[i][c].w4 = 0;
    g->rec[i][c].pos = g->pt[i];
    func_00101080(&v, 2.0f);
    func_00187B00(&v, &v, &g->c);
    func_00187B18(&v, &v, &g->pt[i]);
    g->rec[i][c].len = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    func_00100E40(g->rec[i][c].q, &v);
    func_00100E00(g->rec[i][c].q, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
    g->cnt[i]++;
    g->cur[i]++;
    if (g->cur[i] >= 4) {
        g->cur[i] = 0;
    }
}
#pragma opt_propagation reset
