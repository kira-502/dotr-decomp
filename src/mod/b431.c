#include "common.h"

/* shape b431:01E00080 (b431), 2581 insns, 1 copy: b431 scene manager (b072/b399 grid family with b724's ST-quad
   motes, written from the asm): setup clears the 0xC450 scene, takes both units, three textures, joints 0x5D/0x60 and
   the target, builds a 41x41 floor grid with random phases and four 17-column walls; else at 0x7E a 246-frame glowing
   wall fence and rippling floor (quads plus outline lines), a tick-faded func_001F6D00 level, on 0x11A..0x153 16-slot
   16-sprite drops at the joints' midpoint, at 0x6A a 146-frame flicker flare, on 0x6B..0xFA 32-slot 8-streak swirls,
   at 0x137 a 33-frame burst of 128 streaks, a flare and 64 motes at the target, and at 0x107 a rising screen fade;
   returns 1 / 6 / 2 / 8 at 0x12D / 0x138..0x156 / 0x157 / >0x188 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b431_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b431_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b431_01E00080 c;
    Xyz_b431_01E00080 v[2];
    u64 tail;
} Flat_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b431_01E00080 c;
    Uv_b431_01E00080 uv0;
    Xyz_b431_01E00080 p0;
    Uv_b431_01E00080 uv1;
    Xyz_b431_01E00080 p1;
    u8 tail[0x20];
} Spr_b431_01E00080;

typedef struct {
    f32 s, t;
    Xyz_b431_01E00080 p;
} Gv_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b431_01E00080 c;
    Gv_b431_01E00080 v[4];
    u8 tail[0x20];
} Grid_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b431_01E00080 c;
    Xyz_b431_01E00080 p[4];
    u64 tail;
} Line_b431_01E00080;

typedef struct {
    Rgbaq_b431_01E00080 c;
    Xyz_b431_01E00080 p;
} Cv_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Cv_b431_01E00080 v[4];
    u64 tail;
} Gq_b431_01E00080;

typedef struct {
    Rgbaq_b431_01E00080 c;
    f32 s, t;
    Xyz_b431_01E00080 p;
} Tv_b431_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b431_01E00080 v[4];
    u8 tail[0x20];
} Quad_b431_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b431_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    f32 sc[16];
    u8 pad58[8];
    Vec4f pos;
    Vec4f v[16];
} Drop_b431_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Swarm_b431_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[2];
    u8 pad24[0xC];
    Vec4f jp[2];
    Vec4f mid;
    Vec4f pos;
    Vec4f tgt;
    Vec4f grid[41][41];
    s32 gr[41][41];
    u8 on1;
    u8 pad83D5[3];
    s32 t1;
    u8 pad83DC[4];
    Vec4f wall[4][17][2];
    u8 on2;
    u8 pad8C61[3];
    s32 t2;
    u8 pad8C68[8];
    Drop_b431_01E00080 drop[16];
    u8 on3;
    u8 padA371[3];
    s32 t3;
    u8 padA378[8];
    Swarm_b431_01E00080 sw[32];
    u8 on4;
    u8 padB781[3];
    s32 t4;
    u8 c4[128];
    u8 padB808[8];
    Vec4f v4[128];
    u8 c5[64];
    Vec4f v5[64];
} Scene_b431_01E00080;

static s32 func_01E00080_b431(s32 arg0, s32 code) {
    Scene_b431_01E00080 *g = (Scene_b431_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F57B0(s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00187B00(void *, void *, void *);
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
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
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
    s32 ang;
    u8 alpha;
    f32 f;
    f32 a;
    f32 s;
    f32 h;
    f32 r;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p[4];
    Mtx_b431_01E00080 m4;
    Vec4f v;
    Flat_b431_01E00080 flat __attribute__((aligned(8)));
    Spr_b431_01E00080 spr __attribute__((aligned(8)));
    Grid_b431_01E00080 pk __attribute__((aligned(8)));
    Line_b431_01E00080 ln __attribute__((aligned(8)));
    Gq_b431_01E00080 gq __attribute__((aligned(8)));
    Quad_b431_01E00080 quad __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC450);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x5D, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x60, 0);
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 41; i++) {
            s = 450.0f * i / 40.0f;
            for (j = 0; j < 41; j++) {
                h = 450.0f * j / 40.0f;
                (void)h;
                g->grid[i][j].x = s - 225.0f;
                g->grid[i][j].y = 0.0f;
                g->grid[i][j].z = h - 225.0f;
                g->grid[i][j].w = 1.0f;
                g->gr[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on1 = 0;
        r = 225.0f;
        for (i = 0; i < 17; i++) {
            h = 450.0f * i / 16.0f - r;
            g->wall[0][i][0].x = h;
            g->wall[0][i][0].y = 0.0f;
            g->wall[0][i][0].z = -r;
            g->wall[0][i][0].w = 1.0f;
            g->wall[1][i][0].x = h;
            g->wall[1][i][0].y = 0.0f;
            g->wall[1][i][0].z = r;
            g->wall[1][i][0].w = 1.0f;
            g->wall[2][i][0].x = -r;
            g->wall[2][i][0].y = 0.0f;
            g->wall[2][i][0].z = h;
            g->wall[2][i][0].w = 1.0f;
            g->wall[3][i][0].x = r;
            g->wall[3][i][0].y = 0.0f;
            g->wall[3][i][0].z = h;
            g->wall[3][i][0].w = 1.0f;
            for (j = 0; j < 4; j++) {
                g->wall[j][i][1] = g->wall[j][i][0];
                g->wall[j][i][1].y = 100.0f;
            }
        }
        g->on2 = 0;
        for (i = 0; i < 16; i++) {
            g->drop[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->sw[i].on = 0;
        }
        g->t3 = 0;
        g->on4 = 0;
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_00187B00(&v, &g->jp[0], &g->jp[1]);
    func_00187B48((void *)&g->mid, &v, 0.5f);
    func_001F53C0(1, g->unitA, &g->pos);
    if (g->t == 0x7E) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        ((Grid_b431_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Grid_b431_01E00080 *)(s32)&pk)->size = 9;
        ((Grid_b431_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Grid_b431_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(0));
        func_00208700(&pk, g->tex[0], 1);
        func_00208CB0(&pk, 0);
        ((Line_b431_01E00080 *)(s32)&ln)->flags = 4;
        ((Line_b431_01E00080 *)(s32)&ln)->size = 5;
        ((Line_b431_01E00080 *)(s32)&ln)->regs = 0x44441;
        ((Line_b431_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        ((Gq_b431_01E00080 *)(s32)&gq)->flags = 0x14;
        ((Gq_b431_01E00080 *)(s32)&gq)->size = 8;
        ((Gq_b431_01E00080 *)(s32)&gq)->regs = 0x41414141;
        ((Gq_b431_01E00080 *)(s32)&gq)->pad4 = 0;
        func_002086D0(&gq, func_00208D00(1));
        a = func_00101020((f32)g->t1, 128.0f) * func_00100FF0((f32)g->t1, 245.0f, 213.0f);
        f = (f32)func_00101050(g->t1, 0, 24) * func_00101050(0x7D - g->t1, 0, 24) / 576.0f;
        s = (0.9f + 0.1f * (g->t1 % 2)) * f;
        alpha = (u32)(128.0f * s);
        ln.c.r = 0xFF;
        ln.c.g = 0xEB;
        ln.c.b = 0x80;
        ln.c.a = alpha;
        ln.c.q = 1.0f;
        alpha = (u32)(255.0f * s);
        (void)alpha;
        gq.v[0].c.r = 0xFF;
        gq.v[0].c.g = 0xE8;
        gq.v[0].c.b = 0xD8;
        gq.v[0].c.a = alpha;
        gq.v[0].c.q = 1.0f;
        gq.v[1].c = gq.v[0].c;
        gq.v[2].c.r = 0;
        gq.v[2].c.g = 0;
        gq.v[2].c.b = 0;
        gq.v[2].c.a = 0;
        gq.v[2].c.q = 1.0f;
        gq.v[3].c = gq.v[2].c;
        func_0020EB40(m);
        func_0020BBB0(m2);
        v.x = 0.0f;
        v.y = 55.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        func_00187B60(m2, m2, &v);
        func_0020BC00(m, m2);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 16; j++) {
                if (func_00100BA0(&g->wall[i][j][0], &g->wall[i][j + 1][0], &g->wall[i][j][1], &g->wall[i][j + 1][1], m,
                                  &gq, &depth) == 1) {
                    func_002075F0(&gq, ot, (u32)depth);
                }
            }
        }
        for (q = 0; q < 1; q++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 59.0f - 2.0f * (2.0f * q);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (q == 0) {
                alpha = (u32)(70.0f * a);
            } else {
                alpha = (u32)(70.0f * a);
            }
            pk.c.r = 0x8C;
            pk.c.g = 0x8C;
            pk.c.b = 0x8C;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            for (i = 0; i < 41; i++) {
                for (j = 0; j < 41; j++) {
                    g->grid[i][j].y = 2.0f * func_0020B550((g->gr[i][j] + q * 0x33333 + g->t1 * 0x14D) & 0xFFFF);
                }
            }
            ang = ((q % 2 * 2 - 1) * ((g->t1 + q * 32) % 128 << 16 >> 7)) & 0xFFFF;
            s = 0.1f * func_0020B550(ang);
            h = 0.1f * func_0020B480(ang);
            for (i = 0; i < 40; i++) {
                s0 = (f32)(i % 2) / 2.0f;
                t1 = (f32)(i % 2 + 1) / 2.0f;
                for (j = 0; j < 40; j++) {
                    f = (f32)(j % 2) / 2.0f;
                    s1 = (f32)(j % 2 + 1) / 2.0f + s;
                    pk.v[0].s = f + s;
                    pk.v[0].t = s0 + h;
                    pk.v[1].s = s1;
                    pk.v[1].t = s0 + h;
                    pk.v[2].s = f + s;
                    pk.v[2].t = t1 + h;
                    pk.v[3].s = s1;
                    pk.v[3].t = t1 + h;
                    if (func_00100BA0(&g->grid[i][j], &g->grid[i][j + 1], &g->grid[i + 1][j], &g->grid[i + 1][j + 1], m,
                                      &pk, &depth) == 1) {
                        ln.p[0] = pk.v[0].p;
                        ln.p[1] = pk.v[1].p;
                        ln.p[2] = pk.v[2].p;
                        ln.p[3] = pk.v[3].p;
                        func_002075F0(&ln, ot, (u32)depth);
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        g->t1++;
        if (g->t1 > 0xF5) {
            g->on1 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x188 - g->t, 0, 32) * (func_00101050(g->t - 0x3C, 0, 32) * -96) >> 10) + 0x80));

    if (g->t > 0x119 && g->t < 0x154) {
        n = g->t;
        n %= 16;
        g->drop[n].on = 1;
        g->drop[n].t = 0;
        g->drop[n].pos = g->mid;
        for (i = 0; i < 16; i++) {
            g->drop[n].c[i] = (func_0019A5C8() >> 23) % 8;
            if (g->drop[n].c[i] < 5) {
                g->drop[n].sc[i] = 0.5f;
            } else {
                g->drop[n].sc[i] = 1.0f;
            }
            func_00101080(&g->drop[n].v[i], 1.0f);
        }
    }

    ((Spr_b431_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b431_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b431_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b431_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b431_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->drop[i].on == 0) {
            continue;
        }
        alpha = (u32)(100.0f * func_0020B480((g->drop[i].t << 14) >> 4));
        spr.c.r = 0x78;
        spr.c.g = 0x78;
        spr.c.b = 0xA0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.2f + 0.8f * g->drop[i].t / 16.0f;
        for (j = 0; j < 16; j++) {
            r = 12.5f * (0.1f + 0.9f * g->drop[i].t / 16.0f) * g->drop[i].sc[j];
            cn[0].x = r;
            cn[0].y = r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = -r;
            cn[1].y = -r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(&cn[1], m3, &cn[1]);
            x = g->drop[i].c[j] % 4 * 32;
            y = (g->drop[i].c[j] >> 2) * 32;
            ((Uv_b431_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->drop[i].v[j], s);
            func_00187B00(&v, &v, &g->drop[i].pos);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->drop[i].t++;
        if (g->drop[i].t > 16) {
            g->drop[i].on = 0;
        }
    }

    if (g->t == 0x6A) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Spr_b431_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b431_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b431_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b431_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b431_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        a = func_00101020((f32)g->t3, 16.0f);
        alpha = (u32)(255.0f * ((0.8f + 0.2f * (g->t3 % 2)) * (a * func_00100FF0((f32)g->t3, 145.0f, 129.0f))));
        spr.c.r = 0x62;
        spr.c.g = 0x10;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 30.0f;
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        x = 0;
        y = 32;
        ((Uv_b431_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        v = g->pos;
        func_00187B00(&p[0], &cn[0], &v);
        func_00187B00(&p[1], &cn[1], (void *)&v);
        if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->t3++;
        if (g->t3 > 0x91) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x6A && g->t < 0xFB) {
        n = g->t;
        n %= 32;
        g->sw[n].on = 1;
        g->sw[n].t = 0;
        g->sw[n].pos = g->pos;
        for (i = 0; i < 8; i++) {
            g->sw[n].c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->sw[n].v[i], 0.2f);
        }
    }

    ((Quad_b431_01E00080 *)(s32)&quad)->flags = 0x34;
    ((Quad_b431_01E00080 *)(s32)&quad)->size = 0xC;
    ((Quad_b431_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b431_01E00080 *)(s32)&quad)->pad4 = 0;
    func_002086D0(&quad, func_00208D00(1));
    func_00208700(&quad, g->tex[2], 1);
    func_00208CB0(&quad, 5);
    s = (f32)func_00101050(g->t - 0x6A, 0, 16) * func_00101050(0xFB - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 32; i++) {
        if (g->sw[i].on == 0) {
            continue;
        }
        alpha = (u32)(s * ((32 - g->sw[i].t) * 128 >> 5));
        quad.v[0].c.r = 0x9B;
        quad.v[0].c.g = 0x74;
        quad.v[0].c.b = 0xC4;
        quad.v[0].c.a = alpha;
        quad.v[0].c.q = 1.0f;
        quad.v[1].c = quad.v[0].c;
        quad.v[2].c = quad.v[0].c;
        quad.v[3].c = quad.v[0].c;
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &g->sw[i].pos);
        func_0020BC00(m, m2);
        f = -20.0f * func_00100D50(g->sw[i].t, 32, 1);
        for (j = 0; j < 8; j++) {
            func_00100E40(&m4, &g->sw[i].v[j]);
            func_00100E00(&m4, ((i << 16) >> 5) + ((j << 16) >> 3), 2);
            cn[0].x = 0.0f;
            cn[0].y = 2.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -2.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&p[0], &cn[0], &g->sw[i].v[j]);
            func_00187B00(&p[1], &cn[1], (void *)&g->sw[i].v[j]);
            func_00187B48((void *)&v, &g->sw[i].v[j], f);
            func_00187B00(&p[2], (void *)&p[0], (void *)&v);
            func_00187B00(&p[3], &p[1], (void *)&v);
            x = g->sw[i].c[j] % 4 * 32;
            y = (g->sw[i].c[j] >> 2) * 32;
            u0 = x / 128.0f;
            u1 = (32.0f + x) / 128.0f;
            w0 = y / 64.0f;
            w1 = (32.0f + y) / 64.0f;
            quad.v[0].s = u0;
            quad.v[0].t = w0;
            quad.v[1].s = u1;
            quad.v[1].t = w0;
            quad.v[2].s = u0;
            quad.v[2].t = w1;
            quad.v[3].s = u1;
            quad.v[3].t = w1;
            if (func_002058D0(p, D_0030FF00, m, &quad, &depth) == 1) {
                func_002075F0(&quad, ot, (u32)depth);
            }
        }
        g->sw[i].t++;
        if (g->sw[i].t > 32) {
            g->sw[i].on = 0;
        }
    }

    if (g->t == 0x137) {
        g->on4 = 1;
        g->t4 = 0;
        for (i = 0; i < 128; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->v4[i], 5.0f);
        }
        for (i = 0; i < 64; i++) {
            g->c5[i] = (func_0019A5C8() >> 23) % 4 + 4;
            func_00101080(&g->v5[i], 2.5f);
        }
    }
    if (g->on4 == 1) {
        ((Quad_b431_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b431_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b431_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b431_01E00080 *)(s32)&quad)->pad4 = 0;
        func_002086D0(&quad, func_00208D00(1));
        func_00208700(&quad, g->tex[2], 1);
        func_00208CB0(&quad, 5);
        alpha = (u32)(128.0f * func_00100FF0((f32)g->t4, 32.0f, 16.0f));
        quad.v[0].c.r = 0xC8;
        quad.v[0].c.g = 0xAA;
        quad.v[0].c.b = 0x96;
        quad.v[0].c.a = alpha;
        quad.v[0].c.q = 1.0f;
        quad.v[1].c = quad.v[0].c;
        quad.v[2].c.r = 0xC8;
        quad.v[2].c.g = 0xAA;
        quad.v[2].c.b = 0x96;
        quad.v[2].c.a = 0;
        quad.v[2].c.q = 1.0f;
        quad.v[3].c = quad.v[2].c;
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &g->tgt);
        s = 0.5f + 0.5f * func_00100D50(g->t4, 32, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (i = 0; i < 128; i++) {
            func_00100E40(&m4, &g->v4[i]);
            func_00100E00(&m4, (i << 16) >> 7, 2);
            cn[0].x = 0.0f;
            cn[0].y = 4.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -4.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&p[0], &cn[0], &g->v4[i]);
            func_00187B00(&p[1], &cn[1], (void *)&g->v4[i]);
            func_00187B48((void *)&v, &g->v4[i], -2.0f);
            func_00187B00(&p[2], (void *)&p[0], (void *)&v);
            func_00187B00(&p[3], &p[1], (void *)&v);
            x = g->c4[i] % 4 * 32;
            y = (g->c4[i] >> 2) * 32;
            u0 = x / 128.0f;
            u1 = (32.0f + x) / 128.0f;
            w0 = y / 64.0f;
            w1 = (32.0f + y) / 64.0f;
            quad.v[0].s = u0;
            quad.v[0].t = w0;
            quad.v[1].s = u1;
            quad.v[1].t = w0;
            quad.v[2].s = u0;
            quad.v[2].t = w1;
            quad.v[3].s = u1;
            quad.v[3].t = w1;
            if (func_002058D0(p, D_0030FF00, m, &quad, &depth) == 1) {
                quad.v[0].p.z = 0xFFFFF8;
                quad.v[1].p.z = quad.v[0].p.z;
                quad.v[2].p.z = quad.v[0].p.z;
                quad.v[3].p.z = quad.v[0].p.z;
                func_002075F0(&quad, ot, 0);
            }
        }
        ((Spr_b431_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b431_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b431_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b431_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b431_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        alpha = (u32)(128.0f * func_00100FF0((f32)g->t4, 32.0f, 16.0f));
        spr.c.r = 0x92;
        spr.c.g = 0xC8;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 96;
        y = 0;
        ((Uv_b431_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b431_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->tgt);
        func_0020BC00(m, m2);
        r = 120.0f * (0.5f + 0.5f * func_00100D50(g->t4, 32, 1));
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Spr_b431_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b431_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b431_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b431_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b431_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        alpha = (u32)(164.0f * func_00100FF0((f32)g->t4, 32.0f, 16.0f));
        spr.c.r = 0x78;
        spr.c.g = 0x78;
        spr.c.b = 0xA0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * g->t4 / 32.0f);
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->tgt);
        func_0020BC00(m, m2);
        s = 0.1f + 0.9 * func_00100D50(g->t4, 32, 1);
        for (i = 0; i < 64; i++) {
            x = g->c5[i] % 4 * 32;
            y = (g->c5[i] >> 2) * 32;
            ((Uv_b431_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b431_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v5[i], s);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t4++;
        if (g->t4 > 32) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x107) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Flat_b431_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b431_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b431_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b431_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(0));
        alpha = (u32)(64.0f * func_00100FF0((f32)g->t2, 108.0f, 93.0f));
        flat.c.r = 0x1C;
        flat.c.g = 0x30;
        flat.c.b = 0x60;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        y = (s32)(448.0f * (1.0f - func_00101020((f32)g->t2, 15.0f)));
        flat.v[0].x = 0x6C00;
        flat.v[0].y = (y + 0x720) * 16;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t2++;
        if (g->t2 > 0x6C) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x12D) {
        ret = 1;
    } else {
        if (g->t > 0x137 && g->t < 0x157) {
            ret = 6;
        }
        if (g->t == 0x157) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x188) {
        ret = 8;
    }
    return ret;
}
