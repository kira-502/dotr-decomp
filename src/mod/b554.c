#include "common.h"

/* shape b554:01E00080 (b554), 3902 insns, 1 copy (-O3,p): b554 scene manager, b592:01E00080's relative with
   b560:01E00080's shape: joints 0x22 and 0xA, three shots at 0x87/0x8B/0x8F fly 76-frame comets with 8-slot ember and
   32-slot smoke trails and a three-layer flash, 16 target swirls on 0xD4..0x103, 16 ground shock rings on
   0x3F..0x100, 32 sparks round the joint on 0x1F..0x59, at 0x1B a 33-point ring burst of 128 motes at the second
   joint; returns 1 / 6 / 2 / 8 at 0xC9 / 0xD4..0x103 / 0x104 / >0x134 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b554_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b554_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b554_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b554_01E00080;

typedef struct {
    Reg_b554_01E00080 a;
    Reg_b554_01E00080 b;
} Tx_b554_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b554_01E00080 c;
    Uv_b554_01E00080 uv0;
    Xyz_b554_01E00080 p0;
    Uv_b554_01E00080 uv1;
    Xyz_b554_01E00080 p1;
    u8 tail[0x20];
} Spr_b554_01E00080;

typedef struct {
    Rgbaq_b554_01E00080 c;
    f32 s, t;
    Xyz_b554_01E00080 p;
} Tv_b554_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b554_01E00080 v[4];
    u64 pad70;
    Tx_b554_01E00080 tx;
    u64 pad88;
} Tex_b554_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b554_01E00080;

typedef struct {
    Rgbaq_b554_01E00080 c;
    Xyz_b554_01E00080 p;
} Lv_b554_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b554_01E00080 v[4];
    u64 tail;
} Line_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 n;
    s32 c;
    Vec4f p[1];
    Vec4f v[1];
} Comet_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p[1];
    u8 c[1][16];
    Vec4f v[1][16];
    u8 c2[1][32];
    Vec4f v2[1][32];
} Flash_b554_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Mtx_b554_01E00080 mat;
} Swirl_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 sc[9];
    u8 pad2C[4];
    Vec4f v;
} Shock_b554_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f v[16];
} Spark_b554_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[1];
    Vec4f jp[1];
    s32 jn2;
    u8 pad34[0xC];
    Vec4f jp2;
    Vec4f pos;
    Vec4f tgt;
    f32 h;
    s32 nshot;
    s32 ncomet;
    u8 pad7C[4];
    Comet_b554_01E00080 comet[3];
    Puff_b554_01E00080 trail[3][1][8];
    Puff_b554_01E00080 smoke[3][1][32];
    s32 nflash;
    u8 pad2E14[0xC];
    Flash_b554_01E00080 flash[3];
    Ring_b554_01E00080 ring[17];
    s32 nc[1];
    u8 pad3B44[0xC];
    Swirl_b554_01E00080 c[1][16];
    s32 nshock;
    u8 pad4154[0xC];
    Ring_b554_01E00080 sr[9];
    Ring_b554_01E00080 sr2[9];
    Shock_b554_01E00080 shock[16];
    Spark_b554_01E00080 spark[32];
    u8 on;
    u8 pad6CC1[3];
    s32 t2;
    u8 pad6CC8[8];
    Ring_b554_01E00080 rg[33];
    u8 bc[128];
    Vec4f bpos;
    Vec4f bv[128];
} Scene_b554_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b554(s32 arg0, s32 code) {
    Scene_b554_01E00080 *g = (Scene_b554_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00187B18(void *, void *, void *);
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
    extern void func_00100C60(void *, void *, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 n;
    s32 x;
    s32 y;
    s32 idx;
    u8 alpha;
    u8 drawn;
    s32 buf;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 u;
    f32 u5;
    f32 u1;
    f32 s0;
    f32 cs;
    f32 x0;
    f32 y0;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Vec4f v;
    Line_b554_01E00080 lp __attribute__((aligned(8)));
    Tex_b554_01E00080 pk __attribute__((aligned(8)));
    Spr_b554_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x7B90);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x22, 1);
        g->jn2 = func_001F5560(g->unitA, 0xA, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->h = func_001F5860(g->unitA);
        g->nshot = 0;
        g->ncomet = 0;
        for (i = 0; i < 3; i++) {
            g->comet[i].on = 0;
            g->comet[i].n = 0;
            g->comet[i].c = 0;
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 8; k++) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 32; k++) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
        g->nflash = 0;
        for (i = 0; i < 3; i++) {
            g->flash[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            idx = (i << 16) >> 4;
            g->ring[i].a.x = 25.0f * func_0020B550(idx);
            g->ring[i].a.y = 25.0f * func_0020B480(idx);
            g->ring[i].a.z = 0.0f;
            g->ring[i].a.w = 1.0f;
            g->ring[i].b.x = 70.0f * func_0020B550(idx);
            g->ring[i].b.y = 70.0f * func_0020B480(idx);
            g->ring[i].b.z = 0.0f;
            g->ring[i].b.w = 1.0f;
            func_00187B00(&g->ring[i].mid, &g->ring[i].a, &g->ring[i].b);
            { Vec4f *pm = &g->ring[i].mid; func_00187B48(pm, pm, 0.5f); }
        }
        for (i = 0; i < 1; i++) {
            g->nc[i] = 0;
            for (k = 0; k < 16; k++) {
                g->c[i][k].on = 0;
            }
        }
        g->nshock = 0;
        for (i = 0; i < 16; i++) {
            g->shock[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->spark[i].on = 0;
        }
        g->on = 0;
        for (i = 0; i < 33; i++) {
            idx = (i << 16) >> 5;
            v.x = func_0020B550(idx);
            v.y = func_0020B480(idx);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->rg[i].a, &v, 5.5f);
            func_00187B48((void *)&g->rg[i].b, &v, 8.8f);
            func_00187B48((void *)&g->rg[i].mid, &v, 9.0f);
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 1; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_001F5620(g->unitA, g->jn2, &g->jp2);
    func_001F53C0(1, g->unitA, &g->pos);
    if (g->nshot < 3 && g->t == g->nshot * 4 + 0x87) {
        n = g->ncomet;
        (void)n;
        g->comet[n].on = 1;
        g->comet[n].t = 0;
        idx = g->nflash;
        g->flash[idx].on = 1;
        g->flash[idx].t = 0;
        for (j = 0; j < 1; j++) {
            g->comet[n].p[j] = g->jp[j];
            g->flash[idx].p[j] = g->jp[j];
            func_00101080(&v, 0.0f);
            func_00187B00(&v, &v, &g->tgt);
            v.x = g->comet[n].p[j].x;
            func_00187B18(&g->comet[n].v[j], &v, &g->comet[n].p[j]);
            for (k = 0; k < 16; k++) {
                g->flash[idx].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->flash[idx].v[j][k], 1.0f);
            }
            for (k = 0; k < 32; k++) {
                g->flash[idx].c2[j][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->flash[idx].v2[j][k], 2.0f);
            }
        }
        g->nshot++;
        g->ncomet++;
        if (g->ncomet >= 3) {
            g->ncomet = 0;
        }
        g->nflash++;
        if (g->nflash >= 3) {
            g->nflash = 0;
        }
    }

    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 10.0f;
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
    for (i = 0; i < 3; i++) {
        if (g->comet[i].on == 0) {
            continue;
        }
        spr.c.r = 0xC8;
        spr.c.g = 0x50;
        spr.c.b = 0x32;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        f = (f32)g->comet[i].t / 76.0f;
        idx = g->comet[i].n;
        g->comet[i].n++;
        if (g->comet[i].n >= 8) {
            g->comet[i].n = 0;
        }
        n = g->comet[i].c;
        g->comet[i].c++;
        if (g->comet[i].c >= 32) {
            g->comet[i].c = 0;
        }
        for (j = 0; j < 1; j++) {
            func_00187B48(&v, &g->comet[i].v[j], f);
            func_00187B00(&v, &v, &g->comet[i].p[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->trail[i][j][idx].on = 1;
            g->trail[i][j][idx].t = 0;
            g->trail[i][j][idx].pos = v;
            for (k = 0; k < 4; k++) {
                g->trail[i][j][idx].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->trail[i][j][idx].v[k], 0.5f);
            }
            g->smoke[i][j][n].on = 1;
            g->smoke[i][j][n].t = 0;
            g->smoke[i][j][n].pos = v;
            for (k = 0; k < 4; k++) {
                g->smoke[i][j][n].c[k] = (func_0019A5C8() >> 23) % 3;
                func_00101080(&g->smoke[i][j][n].v[k], 1.0f);
            }
        }
        g->comet[i].t++;
        if (g->comet[i].t > 76) {
            g->comet[i].on = 0;
        }
    }

    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 8; k++) {
                if (g->trail[i][j][k].on == 0) {
                    continue;
                }
                r = 0.5f + 0.5f * (8 - g->trail[i][j][k].t) / 8.0f;
                r = 10.5f * r;
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
                alpha = (8 - g->trail[i][j][k].t) * 128 >> 3;
                spr.c.r = 0xC8;
                spr.c.g = 0x1E;
                spr.c.b = 0x14;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->trail[i][j][k].t, 8, 1);
                for (q = 0; q < 4; q++) {
                    x = g->trail[i][j][k].c[q] % 4 * 32;
                    y = (g->trail[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->trail[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->trail[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->trail[i][j][k].t++;
                if (g->trail[i][j][k].t > 8) {
                    g->trail[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                if (g->smoke[i][j][k].on == 0) {
                    continue;
                }
                r = 6.5f * (0.5f + 0.5f * (32 - g->smoke[i][j][k].t) / 32.0f);
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
                alpha = (32 - g->smoke[i][j][k].t) * 200 >> 5;
                spr.c.r = 0xC8;
                spr.c.g = 0x1E;
                spr.c.b = 0x18;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.2f + 0.8f * func_00100D50(g->smoke[i][j][k].t, 32, 1);
                for (q = 0; q < 4; q++) {
                    x = g->smoke[i][j][k].c[q] % 4 * 32;
                    y = (g->smoke[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->smoke[i][j][k].v[q], s);
                    func_00187B00(&v, &v, &g->smoke[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->smoke[i][j][k].t++;
                if (g->smoke[i][j][k].t > 32) {
                    g->smoke[i][j][k].on = 0;
                }
            }
        }
    }

    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 3; i++) {
        if (g->flash[i].on == 0) {
            continue;
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 10.0f;
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
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->flash[i].t, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0x48;
        spr.c.b = 0x36;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 1; j++) {
            v = g->flash[i].p[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        func_002086D0(&spr, func_00208D00(0));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        r = 10.0f * (0.5f + 0.5f * g->flash[i].t / 32.0f);
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
        alpha = (32 - g->flash[i].t) * 128 >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                x = g->flash[i].c[j][k] % 4 * 32;
                y = (g->flash[i].c[j][k] >> 2) * 32;
                ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 4.0f * (0.5f + 0.5f * (32 - g->flash[i].t) / 32.0f);
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
        alpha = (32 - g->flash[i].t) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x50;
        spr.c.b = 0x28;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                x = g->flash[i].c2[j][k] % 4 * 32;
                y = (g->flash[i].c2[j][k] >> 2) * 32;
                ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v2[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->flash[i].t++;
        if (g->flash[i].t > 32) {
            g->flash[i].on = 0;
        }
    }

    if (g->t > 0xD3 && g->t < 0x104) {
        n = g->t % 16;
        for (j = 0; j < 1; j++) {
            g->c[j][n].on = 1;
            g->c[j][n].t = 0;
            g->c[j][n].pos = g->tgt;
            func_0020BBB0(&g->c[j][n].mat);
            func_00100E00(&g->c[j][n].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 0);
            func_00100E00(&g->c[j][n].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 1);
            func_00100E00(&g->c[j][n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
    }

    ((Tex_b554_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b554_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b554_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b554_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 0);
    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 90.0f;
    cn[0].x = -r;
    cn[0].y = -r;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = r;
    cn[1].y = r;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    u1 = func_00101050(0x104 - g->t, 0, 64) / 64.0f;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 16; j++) {
            if (g->c[i][j].on == 0) {
                continue;
            }
            s = func_00100FF0((f32)g->c[i][j].t, 16.0f, 8.0f);
            pk.v[0].c.r = 0xFF;
            pk.v[0].c.g = 0;
            pk.v[0].c.b = 0;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            alpha = (u32)(200.0f * s * u1);
            (void)alpha;
            pk.v[2].c.r = 0xFF;
            pk.v[2].c.g = 0x64;
            pk.v[2].c.b = 0x3C;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            for (idx = 0; idx < 1; idx++) {
                func_0020EB40(m);
                func_0020C940(m2, 0, 0, &g->c[i][j].pos);
                func_0020BC00(m2, &g->c[i][j].mat);
                func_00100E00(m2, idx << 15, 0);
                s = 0.1f + 0.9f * func_00100D50(g->c[i][j].t, 16, 1);
                v.x = s;
                v.y = s;
                v.z = 0.0f;
                v.w = 1.0f;
                func_0020CB20(m2, &v);
                func_0020BC00(m, m2);
                u = -1.0f * (g->c[i][j].t % 32) / 32.0f;
                cs = 0.5f + u;
                f = 1.0f + u;
                for (q = 0; q < 16; q++) {
                    s0 = 6.0f * q / 16.0f;
                    h = 6.0f * (q + 1) / 16.0f;
                    pk.v[0].s = s0;
                    pk.v[0].t = u;
                    pk.v[1].s = h;
                    pk.v[1].t = u;
                    pk.v[2].s = s0;
                    pk.v[2].t = cs;
                    pk.v[3].s = h;
                    pk.v[3].t = cs;
                    if (func_00100BA0(&g->ring[q].a, &g->ring[q + 1].a, &g->ring[q].mid, &g->ring[q + 1].mid, m, &pk,
                                      &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        func_002075F0(&pk, ot, 0);
                    }
                    pk.v[0].s = s0;
                    pk.v[0].t = f;
                    pk.v[1].s = h;
                    pk.v[1].t = f;
                    pk.v[2].s = s0;
                    pk.v[2].t = cs;
                    pk.v[3].s = h;
                    pk.v[3].t = cs;
                    if (func_00100BA0(&g->ring[q].b, &g->ring[q + 1].b, &g->ring[q].mid, &g->ring[q + 1].mid, m, &pk,
                                      &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        func_002075F0(&pk, ot, 0);
                    }
                }
            }
            s = func_00100FF0((f32)g->c[i][j].t, 16.0f, 8.0f);
            alpha = (u32)(128.0f * s * u1);
            spr.c.r = 0xFF;
            spr.c.g = 0xA4;
            spr.c.b = 0x6C;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->c[i][j].pos);
            s = 0.1f + 0.9f * func_00100D50(g->c[i][j].t, 16, 1);
            v.x = s;
            v.y = s;
            v.z = s;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
            g->c[i][j].t++;
            if (g->c[i][j].t > 16) {
                g->c[i][j].on = 0;
            }
        }
    }

    if (g->t > 0x3E && g->t < 0x101) {
        n = g->nshock;
        (void)n;
        g->shock[n].on = 1;
        g->shock[n].t = 0;
        func_00101080(&g->shock[n].v, 0.4f);
        for (i = 0; i < 8; i++) {
            g->shock[n].sc[i] = 0.25f + (1.0f - 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
        }
        g->shock[n].sc[8] = g->shock[n].sc[0];
        g->nshock++;
        if (g->nshock >= 16) {
            g->nshock = 0;
        }
    }

    ((Tex_b554_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b554_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b554_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b554_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Tex_b554_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t - 0x3E, 0, 60) / 60.0f;
    drawn = 0;
    for (i = 0; i < 16; i++) {
        if (g->shock[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_00187B00(&v, &g->shock[i].v, &g->pos);
        func_00187B60(m2, m3, &v);
        func_0020BC00(m, m2);
        h = (f32)g->shock[i].t / 16.0f;
        for (j = 0; j < 9; j++) {
            idx = (j << 16) >> 3;
            s = func_0020B550(idx);
            cs = func_0020B480(idx);
            r = 2.0f * g->h * h - 15.0f - 15.0f;
            if (r < 0.0f) {
                r = 0.0f;
            }
            x0 = r * s;
            y0 = r * cs;
            g->sr[j].a.x = x0;
            g->sr[j].a.y = y0;
            g->sr[j].a.z = 0.0f;
            g->sr[j].a.w = 1.0f;
            g->sr2[j].a.x = g->shock[i].sc[j] * x0;
            g->sr2[j].a.y = g->shock[i].sc[j] * y0;
            g->sr2[j].a.z = 0.0f;
            g->sr2[j].a.w = 1.0f;
            r = 2.0f * g->h * h - 15.0f;
            if (r < 0.0f) {
                r = 0.0f;
            }
            x0 = r * s;
            y0 = r * cs;
            g->sr[j].b.x = x0;
            g->sr[j].b.y = y0;
            g->sr[j].b.z = 0.0f;
            g->sr[j].b.w = 1.0f;
            g->sr2[j].b.x = g->shock[i].sc[j] * x0;
            g->sr2[j].b.y = g->shock[i].sc[j] * y0;
            g->sr2[j].b.z = 0.0f;
            g->sr2[j].b.w = 1.0f;
            y0 = 2.0f * g->h * h;
            x0 = y0 * s;
            y0 = y0 * cs;
            g->sr[j].mid.x = x0;
            g->sr[j].mid.y = y0;
            g->sr[j].mid.z = 0.0f;
            g->sr[j].mid.w = 1.0f;
            g->sr2[j].mid.x = g->shock[i].sc[j] * x0;
            g->sr2[j].mid.y = g->shock[i].sc[j] * y0;
            g->sr2[j].mid.z = 0.0f;
            g->sr2[j].mid.w = 1.0f;
        }
        if (drawn == 0) {
            drawn = 1;
            buf = func_00207F60();
            func_00208460();
            func_001F7060(g->unitA, 1, &pk.tx.a, &pk.tx.b);
            func_00208460();
        }
        alpha = (u32)(200.0f * f * func_0020B480((g->shock[i].t << 14) >> 4));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x5A;
        pk.v[0].c.b = 0x0F;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0x80;
        pk.v[2].c.g = 0;
        pk.v[2].c.b = 0;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        for (j = 0; j < 8; j++) {
            if (func_00100BA0(&g->sr2[j].b, &g->sr2[j + 1].b, &g->sr2[j].a, &g->sr2[j + 1].a, m, &pk, &depth) == 1) {
                func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                if (func_00100BA0(&g->sr[j].b, &g->sr[j + 1].b, &g->sr[j].a, &g->sr[j + 1].a, m, &pk, &depth) == 1) {
                    pk.v[0].p.z = 0xFFFFF8;
                    pk.v[1].p.z = pk.v[0].p.z;
                    pk.v[2].p.z = pk.v[0].p.z;
                    pk.v[3].p.z = pk.v[0].p.z;
                    func_002075F0(&pk, 0, 0);
                }
            }
            if (func_00100BA0(&g->sr2[j].b, &g->sr2[j + 1].b, &g->sr2[j].mid, &g->sr2[j + 1].mid, m, &pk, &depth) ==
                1) {
                func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                if (func_00100BA0(&g->sr[j].b, &g->sr[j + 1].b, &g->sr[j].mid, &g->sr[j + 1].mid, m, &pk, &depth) ==
                    1) {
                    pk.v[0].p.z = 0xFFFFF8;
                    pk.v[1].p.z = pk.v[0].p.z;
                    pk.v[2].p.z = pk.v[0].p.z;
                    pk.v[3].p.z = pk.v[0].p.z;
                    func_002075F0(&pk, 0, 0);
                }
            }
        }
        g->shock[i].t++;
        if (g->shock[i].t > 16) {
            g->shock[i].on = 0;
        }
    }
    if (drawn == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0x1E && g->t < 0x5A) {
        n = g->t % 32;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (k = 0; k < 16; k++) {
            g->spark[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[k], 1.0f);
            func_00187B00(&g->spark[n].v[k], &g->spark[n].v[k], &g->jp[0]);
        }
    }

    ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 2.0f * (0.2f + 0.8f * g->spark[i].t / 32.0f);
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
        alpha = (u32)(255.0f * func_0020B550((g->spark[i].t << 14) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0x38;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(32 - g->spark[i].t, 32, 1);
        for (k = 0; k < 16; k++) {
            func_00187B18(&v, &g->spark[i].v[k], &g->jp[0]);
            func_00187B48(&v, &v, s);
            func_00187B00(&v, &v, &g->jp[0]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[k] % 4 * 32;
            y = (g->spark[i].c[k] >> 2) * 32;
            ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x1B) {
        g->on = 1;
        g->t2 = 0;
        g->bpos = g->jp2;
        for (k = 0; k < 128; k++) {
            g->bc[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->bv[k], 0.8f);
        }
    }
    if (g->on == 1) {
        ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0xC4;
        spr.c.b = 0xB4;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Line_b554_01E00080 *)(s32)&lp)->flags = 0x14;
        ((Line_b554_01E00080 *)(s32)&lp)->size = 8;
        ((Line_b554_01E00080 *)(s32)&lp)->regs = 0x41414141;
        ((Line_b554_01E00080 *)(s32)&lp)->pad4 = 0;
        func_002086D0(&lp, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        s = 0.1f + 0.9f * func_00100D50(g->t2, 32, 2);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 128 >> 5;
        lp.v[0].c.r = 0xFF;
        lp.v[0].c.g = 0xC4;
        lp.v[0].c.b = 0xAA;
        lp.v[0].c.a = alpha;
        lp.v[0].c.q = 1.0f;
        lp.v[1].c = lp.v[0].c;
        lp.v[2].c.r = 0xFF;
        lp.v[2].c.g = 0x20;
        lp.v[2].c.b = 0x17;
        lp.v[2].c.a = 0;
        lp.v[2].c.q = 1.0f;
        lp.v[3].c = lp.v[2].c;
        for (j = 0; j < 32; j++) {
            if (func_00100BA0(&g->rg[j].b, &g->rg[j + 1].b, &g->rg[j].a, &g->rg[j + 1].a, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
            if (func_00100BA0(&g->rg[j].b, &g->rg[j + 1].b, &g->rg[j].mid, &g->rg[j + 1].mid, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
        }
        ((Spr_b554_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b554_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b554_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b554_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b554_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0xC4;
        spr.c.b = 0xAA;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.8f;
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
        for (k = 0; k < 128; k++) {
            x = g->bc[k] % 4 * 32;
            y = (g->bc[k] >> 2) * 32;
            ((Uv_b554_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b554_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->bv[k], s);
            func_00187B00(&v, &v, &g->bpos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 32) {
            g->on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x134 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0xC9) {
        ret = 1;
    } else {
        if (g->t > 0xD3 && g->t < 0x104) {
            ret = 6;
        }
        if (g->t == 0x104) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x134) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
