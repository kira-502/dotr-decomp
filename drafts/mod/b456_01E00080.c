#include "common.h"

/* shape b456:01E00080 (b456), 5097 insns, 1 copy (-O3,p): b456 scene manager, a b012/b359 relative with four
   textures: warp fan at 0xB3/0xD1/0xEF, comets at 0x57/0x9A/0xD9 on a sine arc, flashes with a rotating quad pass,
   ground rings on 1..0x10F, sparks on 1..0xEF, a ring burst at 0x26, three novae ending in a rotating quad pass;
   returns 1 / 6 / 2 / 8 at 0xA9 / 0xB4..0x10E / 0x10F / >0x12F. DRAFT: 8 words differ, the comet-spawn index is in a0
   where the original has a1 and the temp n << 6 takes a0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b456_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b456_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b456_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b456_01E00080;

typedef struct {
    Reg_b456_01E00080 a;
    Reg_b456_01E00080 b;
} Tx_b456_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b456_01E00080 c;
    Uv_b456_01E00080 uv0;
    Xyz_b456_01E00080 p0;
    Uv_b456_01E00080 uv1;
    Xyz_b456_01E00080 p1;
    u8 tail[0x20];
} Spr_b456_01E00080;

typedef struct {
    Rgbaq_b456_01E00080 c;
    f32 s, t;
    Xyz_b456_01E00080 p;
} Tv_b456_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b456_01E00080 v[4];
    u64 pad70;
    Tx_b456_01E00080 tx;
    u64 pad88;
} Tex_b456_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b456_01E00080 c;
        Uv_b456_01E00080 uv;
        Xyz_b456_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b456_01E00080;

typedef struct {
    Rgbaq_b456_01E00080 c;
    Xyz_b456_01E00080 p;
} Lv_b456_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b456_01E00080 v[4];
    u64 tail;
} Line_b456_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b456_01E00080 c;
    struct {
        Uv_b456_01E00080 uv;
        Xyz_b456_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Quad_b456_01E00080;

typedef struct {
    f32 m[4][4];
} __attribute__((aligned(16))) Mq_b456_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life;
    s32 n;
    s32 c;
    u8 pad14[0xC];
    Vec4f p[1];
    Vec4f v[1];
} Comet_b456_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b456_01E00080;

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
} Flash_b456_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Ring_b456_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 sc[9];
    u8 pad2C[4];
    Vec4f v;
} Shock_b456_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f pos;
    Vec4f v[16];
} Spark_b456_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f v2[128];
    u8 c2[64];
    Vec4f v3[64];
} Nova_b456_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn[1];
    u8 pad24[0xC];
    Vec4f jp[1];
    s32 jn2;
    u8 pad34[0xC];
    Vec4f jp2;
    Vec4f pos;
    Vec4f tgt;
    Vec4f scr;
    f32 h;
    s32 nshot;
    s32 ncomet;
    u8 pad7C[4];
    Comet_b456_01E00080 comet[3];
    Puff_b456_01E00080 trail[3][1][8];
    Puff_b456_01E00080 smoke[3][1][32];
    s32 nflash;
    u8 pad2E14[0xC];
    Flash_b456_01E00080 flash[3];
    s32 nshock;
    u8 pad3864[0xC];
    Ring_b456_01E00080 sr[9];
    Ring_b456_01E00080 sr2[9];
    Shock_b456_01E00080 shock[16];
    Spark_b456_01E00080 spark[16];
    u8 on;
    u8 pad6CC1[3];
    s32 t2;
    u8 pad6CC8[8];
    Ring_b456_01E00080 rg[33];
    u8 bc[128];
    Vec4f bpos;
    Vec4f bv[128];
    u8 on2;
    u8 pad7261[3];
    s32 t3;
    s32 nn;
    u8 pad726C[4];
    Nova_b456_01E00080 nova[3];
} Scene_b456_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b456(s32 arg0, s32 code) {
    Scene_b456_01E00080 *g = (Scene_b456_01E00080 *)arg0;
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
    extern void func_00101080(void *, f32);
    extern s32 func_00101050(s32, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
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
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_0017B340();
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern Vec4f D_28B960[];
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
    u8 a2;
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
    Vec4f out[4];
    Mq_b456_01E00080 m4;
    Vec4f v;
    Quad_b456_01E00080 qd __attribute__((aligned(8)));
    Line_b456_01E00080 lp __attribute__((aligned(8)));
    Tex_b456_01E00080 pk __attribute__((aligned(8)));
    Tri_b456_01E00080 tri __attribute__((aligned(8)));
    Spr_b456_01E00080 spr __attribute__((aligned(8)));
    Xyz_b456_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9450);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->jn[0] = func_001F5560(g->unitA, 0xC, 1);
        g->jn2 = func_001F5560(g->unitA, 0xE, 0);
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
        g->nshock = 0;
        for (i = 0; i < 16; i++) {
            g->shock[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->on = 0;
        for (i = 0; i < 33; i++) {
            idx = (i << 16) >> 5;
            v.x = func_0020B550(idx);
            v.y = func_0020B480(idx);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->rg[i].a, &v, 16.5f);
            func_00187B48((void *)&g->rg[i].b, &v, 26.4f);
            func_00187B48((void *)&g->rg[i].mid, &v, 27.0f);
        }
        g->nn = 0;
        for (i = 0; i < 3; i++) {
            g->nova[i].on = 0;
        }
        g->on2 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 1; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_001F5620(g->unitA, g->jn2, &g->jp2);
    func_001F53C0(1, g->unitA, &g->pos);
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
    if (g->t == 0xB3 || g->t == 0xD1 || g->t == 0xEF) {
        g->on2 = 1;
        g->t3 = 0;
    }
    if (g->on2 == 1) {
        ((Tri_b456_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b456_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b456_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b456_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b456_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (32 - g->t3) * 64 >> 5;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            f = 1.0f + 0.15f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b456_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b456_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b456_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48(&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
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
        g->t3++;
        if (g->t3 > 32) {
            g->on2 = 0;
        }
    }
    n = -1;
    switch (g->t) {
    case 0x57:
        n = 0;
        g->comet[0].life = 0x5C;
        break;
    case 0x9A:
        n = 1;
        g->comet[1].life = 0x37;
        break;
    case 0xD9:
        n = 2;
        g->comet[2].life = 0x16;
        break;
    }
    if (n >= 0) {
        g->comet[n].on = 1;
        g->comet[n].t = 0;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->comet[n].p[j] = g->jp[j];
            g->flash[n].p[j] = g->jp[j];
            func_00101080(&v, 0.0f);
            func_00187B00(&v, &v, &g->tgt);
            v.x = g->comet[n].p[j].x;
            func_00187B18(&g->comet[n].v[j], &v, &g->comet[n].p[j]);
            for (k = 0; k < 16; k++) {
                g->flash[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->flash[n].v[j][k], 1.0f);
            }
            for (k = 0; k < 32; k++) {
                g->flash[n].c2[j][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->flash[n].v2[j][k], 1.5f);
            }
        }
    }

    ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[3], 1);
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
    for (i = 0; i < 3; i++) {
        if (g->comet[i].on == 0) {
            continue;
        }
        x = i * 64;
        y = i * 64 + 64;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = y << 4;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = 0x400;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        f = (f32)g->comet[i].t / (f32)g->comet[i].life;
        h = 150.0f * func_0020B550(g->comet[i].t * 0x8000 / g->comet[i].life);
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
            v.y += h;
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
                func_00101080(&g->trail[i][j][idx].v[k], 0.35f);
            }
            g->smoke[i][j][n].on = 1;
            g->smoke[i][j][n].t = 0;
            g->smoke[i][j][n].pos = v;
            for (k = 0; k < 4; k++) {
                g->smoke[i][j][n].c[k] = (func_0019A5C8() >> 23) % 3;
                func_00101080(&g->smoke[i][j][n].v[k], 0.7f);
            }
        }
        g->comet[i].t++;
        if (g->comet[i].t > g->comet[i].life) {
            g->comet[i].on = 0;
        }
    }

    ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
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
                r = 7.5f * r;
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
                spr.c.r = 0xFF;
                spr.c.g = 0x40;
                spr.c.b = 0x16;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->trail[i][j][k].t, 8, 1);
                for (q = 0; q < 4; q++) {
                    x = g->trail[i][j][k].c[q] % 4 * 32;
                    y = (g->trail[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
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
                r = 2.5f * (0.5f + 0.5f * (32 - g->smoke[i][j][k].t) / 32.0f);
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
                spr.c.r = 0xFF;
                spr.c.g = 0x40;
                spr.c.b = 0x16;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.2f + 0.8f * func_00100D50(g->smoke[i][j][k].t, 32, 1);
                for (q = 0; q < 4; q++) {
                    x = g->smoke[i][j][k].c[q] % 4 * 32;
                    y = (g->smoke[i][j][k].c[q] >> 2) * 32;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
    ((Quad_b456_01E00080 *)(s32)&qd)->flags = 0x24;
    ((Quad_b456_01E00080 *)(s32)&qd)->size = 9;
    ((Quad_b456_01E00080 *)(s32)&qd)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b456_01E00080 *)(s32)&qd)->pad4 = 0;
    ((Quad_b456_01E00080 *)(s32)&qd)->flags |= 0x800;
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
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 35.0f;
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
        spr.c.g = 0x64;
        spr.c.b = 0x32;
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
                ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->flash[i].v[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        func_002086D0(&qd, func_00208D00(0));
        func_00208700(&qd, g->tex[3], 1);
        func_00208CB0(&qd, 5);
        r = 0.5f;
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
        alpha = (u32)(128.0f * func_00100FF0((f32)g->flash[i].t, 32.0f, 21.0f));
        qd.c.r = 0xFF;
        qd.c.g = 0x80;
        qd.c.b = 0x80;
        qd.c.a = alpha;
        qd.c.q = 1.0f;
        s = func_00100D50(g->flash[i].t, 32, 1);
        h = 5.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->flash[i].t, 2.0f)));
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                x = g->flash[i].c2[j][k] % 4 * 64;
                ((Uv_b456_01E00080 *)(s32)&qd.v[0].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[0].uv)->v = 0;
                ((Uv_b456_01E00080 *)(s32)&qd.v[1].uv)->u = (x + 64) << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[1].uv)->v = 0;
                ((Uv_b456_01E00080 *)(s32)&qd.v[2].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[2].uv)->v = 0x400;
                ((Uv_b456_01E00080 *)(s32)&qd.v[3].uv)->u = (x + 64) << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[3].uv)->v = 0x400;
                func_00187B48(&v, &g->flash[i].v2[j][k], s);
                func_00187B00(&v, &v, &g->flash[i].p[j]);
                v.y += h;
                m4 = *(Mq_b456_01E00080 *)m3;
                func_00100E00(&m4, (k << 16) >> 5, 2);
                for (q = 0; q < 4; q++) {
                    func_001878E0(&out[q], &m4, &cn[q]);
                    func_00187B00(&out[q], &out[q], &v);
                }
                if (func_00205630(out, D_0030FF00, m, &qd, &depth) == 1) {
                    func_002075F0(&qd, ot, (u32)depth);
                }
            }
        }
        g->flash[i].t++;
        if (g->flash[i].t > 32) {
            g->flash[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x110) {
        n = g->nshock;
        (void)n;
        g->shock[n].on = 1;
        g->shock[n].t = 0;
        func_00101080(&g->shock[n].v, 0.4f);
        for (i = 0; i < 8; i++) {
            g->shock[n].sc[i] = 0.2f + (1.0f - 0.4f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
        }
        g->shock[n].sc[8] = g->shock[n].sc[0];
        g->nshock++;
        if (g->nshock >= 16) {
            g->nshock = 0;
        }
    }

    ((Tex_b456_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b456_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b456_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b456_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Tex_b456_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t, 0, 32) / 32.0f;
    drawn = 0;
    for (i = 0; i < 16; i++) {
        if (g->shock[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_00187B00(&v, &g->shock[i].v, &g->pos);
        func_00187B60(m2, m3, &v);
        func_0020BC00(m, m2);
        u = (f32)g->shock[i].t / 16.0f;
        for (j = 0; j < 9; j++) {
            idx = (j << 16) >> 3;
            s = func_0020B550(idx);
            cs = func_0020B480(idx);
            r = 2.0f * g->h * u - 15.0f - 15.0f;
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
            r = 2.0f * g->h * u - 15.0f;
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
            y0 = 2.0f * g->h * u;
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
        alpha = (u32)(100.0f * f * func_0020B480((g->shock[i].t << 14) >> 4));
        pk.v[0].c.r = 0xE4;
        pk.v[0].c.g = 0x40;
        pk.v[0].c.b = 0x19;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0;
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

    if (g->t > 0 && g->t < 0xF0) {
        n = g->t % 16;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].pos = g->jp[0];
        for (k = 0; k < 16; k++) {
            g->spark[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[n].v[k], 0.7f);
        }
    }

    ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        r = 0.2f + 0.8f * (16 - g->spark[i].t) / 16.0f;
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
        alpha = (u32)(228.0f * func_0020B550((g->spark[i].t << 15) >> 4));
        spr.c.r = 0xFF;
        spr.c.g = 0x46;
        spr.c.b = 0x1E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->spark[i].t, 16, 1);
        h = 5.0f * g->spark[i].t / 16.0f;
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            v.y += h;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->spark[i].c[k] % 4 * 32;
            y = (g->spark[i].c[k] >> 2) * 32;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(0));
        r = 5.0f * (0.5f + 0.5f * g->spark[i].t / 16.0f);
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
        alpha = (u32)(96.0f * func_0020B480((g->spark[i].t << 14) >> 4));
        spr.c.r = 0x8A;
        spr.c.g = 0x8A;
        spr.c.b = 0x8A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = -0.7f * (0.3f + 0.7f * func_00100D50(g->spark[i].t, 16, 1));
        h = 5.0f * g->spark[i].t / 16.0f;
        for (k = 0; k < 16; k++) {
            func_00187B48(&v, &g->spark[i].v[k], s);
            func_00187B00(&v, &v, &g->spark[i].pos);
            v.y += h;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = (g->spark[i].c[k] + 4) % 4 * 32;
            y = ((g->spark[i].c[k] + 4) >> 2) * 32;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 16) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x26) {
        g->on = 1;
        g->t2 = 0;
        g->bpos = g->jp2;
        for (k = 0; k < 128; k++) {
            g->bc[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->bv[k], 0.5f);
        }
    }
    if (g->on == 1) {
        ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 32, 1)));
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0x30;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 48.0f;
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
        ((Line_b456_01E00080 *)(s32)&lp)->flags = 0x14;
        ((Line_b456_01E00080 *)(s32)&lp)->size = 8;
        ((Line_b456_01E00080 *)(s32)&lp)->regs = 0x41414141;
        ((Line_b456_01E00080 *)(s32)&lp)->pad4 = 0;
        func_002086D0(&lp, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->bpos);
        s = 0.1f + 0.9f * func_00100D50(g->t2, 32, 1);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        lp.v[0].c.r = 0xFF;
        lp.v[0].c.g = 0xE4;
        lp.v[0].c.b = 0x94;
        lp.v[0].c.a = alpha;
        lp.v[0].c.q = 1.0f;
        lp.v[1].c = lp.v[0].c;
        lp.v[2].c.r = 0xFF;
        lp.v[2].c.g = 0x1C;
        lp.v[2].c.b = 0x12;
        lp.v[2].c.a = 0;
        lp.v[2].c.q = 1.0f;
        lp.v[3].c = lp.v[2].c;
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->rg[i].b, &g->rg[i + 1].b, &g->rg[i].a, &g->rg[i + 1].a, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
            if (func_00100BA0(&g->rg[i].b, &g->rg[i + 1].b, &g->rg[i].mid, &g->rg[i + 1].mid, m, &lp, &depth) == 1) {
                lp.v[0].p.z = 0xFFFFF8;
                lp.v[1].p.z = lp.v[0].p.z;
                lp.v[2].p.z = lp.v[0].p.z;
                lp.v[3].p.z = lp.v[0].p.z;
                func_002075F0(&lp, ot, 0);
            }
        }
        ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (32 - g->t2) * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0x30;
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
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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

    n = -1;
    switch (g->t) {
    case 0xB3:
        n = 0;
        break;
    case 0xD1:
        n = 1;
        break;
    case 0xEF:
        n = 2;
        break;
    }
    if (n >= 0) {
        g->nn = n;
        g->nova[g->nn].on = 1;
        g->nova[g->nn].t = 1;
        g->nova[g->nn].pos.x = 0.0f;
        g->nova[g->nn].pos.y = 0.0f;
        g->nova[g->nn].pos.z = 0.0f;
        g->nova[g->nn].pos.w = 1.0f;
        func_00187B00(&g->nova[g->nn].pos, &g->nova[g->nn].pos, &g->tgt);
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->nova[g->nn].v[k], 1.8f);
        }
        for (k = 0; k < 128; k++) {
            func_00101080(&g->nova[g->nn].v2[k], 2.75f);
        }
        for (k = 0; k < 64; k++) {
            g->nova[g->nn].c2[k] = (func_0019A5C8() >> 23) % 3 + 5;
            func_00101080(&g->nova[g->nn].v3[k], 2.7f);
        }
    }
    for (i = 0; i < 3; i++) {
        if (g->nova[i].on == 0) {
            continue;
        }
        ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 18.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
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
        alpha = (32 - g->nova[i].t) * 200 >> 5;
        spr.c.r = 0xE6;
        spr.c.g = 0x8A;
        spr.c.b = 0x4C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->nova[i].t, 32, 1);
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->nova[i].v3[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c2[k] % 4 * 32;
            y = (g->nova[i].c2[k] >> 2) * 32;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->nova[i].t / 32.0f);
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
        alpha = (32 - g->nova[i].t) * 255 >> 5;
        a2 = (32 - g->nova[i].t) * 48 >> 5;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->nova[i].t, 32, 1);
            if (k % 2 == 0) {
                s *= 0.9f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xBC;
                spr.c.b = 0xFF;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0xC8;
                spr.c.g = 0x64;
                spr.c.b = 0x32;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->nova[i].v[k], s);
            func_00187B00(&v, &v, &g->nova[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->nova[i].c[k] % 4 * 32;
            y = (g->nova[i].c[k] >> 2) * 32;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b456_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b456_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b456_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b456_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b456_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->nova[i].pos);
        s = 0.2f + 0.8f * func_00100D50(g->nova[i].t, 32, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((32 - g->nova[i].t) / 32.0f));
        spr.c.r = 0xFF;
        spr.c.g = 0x5E;
        spr.c.b = 0x26;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b456_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b456_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 195.0f;
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
        ((Quad_b456_01E00080 *)(s32)&qd)->flags = 0x24;
        ((Quad_b456_01E00080 *)(s32)&qd)->size = 9;
        ((Quad_b456_01E00080 *)(s32)&qd)->regs = ((u64)4 << 32) | 0x24242421;
        ((Quad_b456_01E00080 *)(s32)&qd)->pad4 = 0;
        ((Quad_b456_01E00080 *)(s32)&qd)->flags |= 0x800;
        func_00208700(&qd, g->tex[3], 1);
        func_00208CB0(&qd, 5);
        func_002086D0(&qd, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.0f;
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
        alpha = (u32)(128.0f * func_00100FF0((f32)g->nova[i].t, 32.0f, 21.0f));
        qd.c.r = 0xFF;
        qd.c.g = 0x80;
        qd.c.b = 0x80;
        qd.c.a = alpha;
        qd.c.q = 1.0f;
        h = func_00100D50(g->nova[i].t, 32, 1);
        s = 7.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->nova[i].t, 2.0f)));
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 1; k++) {
                x = j % 4 * 64;
                ((Uv_b456_01E00080 *)(s32)&qd.v[0].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[0].uv)->v = 0;
                ((Uv_b456_01E00080 *)(s32)&qd.v[1].uv)->u = (x + 64) << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[1].uv)->v = 0;
                ((Uv_b456_01E00080 *)(s32)&qd.v[2].uv)->u = x << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[2].uv)->v = 0x400;
                ((Uv_b456_01E00080 *)(s32)&qd.v[3].uv)->u = (x + 64) << 4;
                ((Uv_b456_01E00080 *)(s32)&qd.v[3].uv)->v = 0x400;
                func_00187B48(&v, &g->nova[i].v2[j], h + 0.007f * k);
                func_00187B00(&v, &v, &g->nova[i].pos);
                v.y += s;
                m4 = *(Mq_b456_01E00080 *)m3;
                func_00100E00(&m4, (j << 16) >> 7, 2);
                for (q = 0; q < 4; q++) {
                    func_001878E0(&out[q], &m4, &cn[q]);
                    func_00187B00(&out[q], &out[q], &v);
                }
                if (func_00205630(out, D_0030FF00, m, &qd, &depth) == 1) {
                    func_002075F0(&qd, ot, (u32)depth);
                }
            }
        }
        g->nova[i].t++;
        if (g->nova[i].t > 32) {
            g->nova[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x12F - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0xA9) {
        ret = 1;
    } else {
        if (g->t > 0xB3 && g->t < 0x10F) {
            ret = 6;
        }
        if (g->t == 0x10F) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x12F) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
