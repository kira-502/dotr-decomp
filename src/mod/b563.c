#include "common.h"

/* shape b563:01E00080 (b563), 2112 insns, 1 copy: b563 scene manager (b599/b562:01E00080's family, written from the
   asm): setup clears the 0x91E0 scene, takes both units, four textures, eight joints and the target, seeds 4x4 smoke
   slots, builds eight 33x3 ribbon strips, a 33x2 arc and a 33-point ring; else every 16 frames per joint group fills
   a smoke slot (func_01E02180) and draws them, on 1..0x10D a 32-slot 3x4 spark puff at joints 4..6, from 0x9B a
   111-frame scrolling ribbon fan at the target, on 0x9C..0xE8 a 32-slot 8-sprite burst above it and every 10th frame
   a 32-slot rising arc wave, from 0x6C a 131-frame line ring at joint 7; returns 1 / 6 / 2 / 8 at 0x91 / 0x9C..0xFC /
   0xFD / >0x12E */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b563_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b563_01E00080;

typedef struct {
    f32 s;
    f32 t;
} St_b563_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b563_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b563_01E00080 c;
    union {
        Uv_b563_01E00080 uv;
        St_b563_01E00080 st;
    } uv0;
    Xyz_b563_01E00080 p0;
    union {
        Uv_b563_01E00080 uv;
        St_b563_01E00080 st;
    } uv1;
    Xyz_b563_01E00080 p1;
    u8 tail[0x20];
} Spr_b563_01E00080;

typedef struct {
    Rgbaq_b563_01E00080 c;
    f32 s, t;
    Xyz_b563_01E00080 p;
} Tv_b563_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b563_01E00080 v[4];
    u8 tail[0x20];
} Quad_b563_01E00080;

typedef struct {
    Rgbaq_b563_01E00080 c;
    Xyz_b563_01E00080 p;
} Lv_b563_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b563_01E00080 v[3];
    u64 tail;
} Line_b563_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b563_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f pos;
    Vec4f v[32];
} Smoke_b563_01E00080;

typedef struct {
    Smoke_b563_01E00080 e[4];
} Grp_b563_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos[3];
    Vec4f v[3][4];
} Spark_b563_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[8];
} Burst_b563_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Wave_b563_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    s32 jn[4];
    Vec4f jp[4];
    s32 jn2[3];
    u8 pad7C[4];
    Vec4f jp2[3];
    s32 jn3;
    u8 padB4[0xC];
    Vec4f jp3;
    Vec4f tgt;
    s32 cnt[4];
    s32 cur[4];
    Grp_b563_01E00080 grp[4];
    Spark_b563_01E00080 spark[32];
    Vec4f rib[8][33][3];
    u8 on2;
    u8 pad7881[3];
    s32 t2;
    u8 pad7888[8];
    Burst_b563_01E00080 burst[32];
    s32 nw;
    u8 pad8A94[0xC];
    Vec4f arc[33][2];
    Wave_b563_01E00080 wave[32];
    Vec4f ring[33];
    u8 on3;
    u8 pad91D1[3];
    s32 t3;
    u8 pad91D8[8];
} Scene_b563_01E00080;

static s32 func_01E00080_b563(s32 arg0, s32 code) {
    Scene_b563_01E00080 *g = (Scene_b563_01E00080 *)arg0;
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
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void b563_01E02180(s32, s32);
    extern f32 D_0028BC10[4][32][3];
    extern u16 D_28BBF0[][4];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    u8 alpha;
    f32 a;
    f32 b;
    f32 r;
    f32 s;
    f32 h;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b563_01E00080 m4;
    Vec4f v;
    Spr_b563_01E00080 spr __attribute__((aligned(8)));
    Quad_b563_01E00080 pk __attribute__((aligned(8)));
    Line_b563_01E00080 ln __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x91E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(4, 0xF);
        g->jn[0] = func_001F5560(g->unitA, 0xD, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x1E, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x31, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x39, 0);
        g->jn2[0] = func_001F5560(g->unitA, 0xF, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x11, 0);
        g->jn2[2] = func_001F5560(g->unitA, 0x12, 0);
        g->jn3 = func_001F5560(g->unitA, 0x27, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->tgt.y += -30.0f;
        for (i = 0; i < 4; i++) {
            g->cnt[i] = 0;
            g->cur[i] = 0;
            for (j = 0; j < 4; j++) {
                g->grp[i].e[j].on = 0;
                for (k = 0; k < 32; k++) {
                    g->grp[i].e[j].c[k] = (func_0019A5C8() >> 23) % 4;
                }
            }
        }
        for (i = 0; i < 32; i++) {
            g->spark[i].on = 0;
        }
        for (i = 0; i < 8; i++) {
            func_0020BBB0(&m4);
            if (i < 4) {
                func_00100E00(&m4, (i << 16) >> 3, 1);
            } else {
                func_00100E00(&m4, ((i << 16) >> 3) + 0x1000, 1);
            }
            for (j = 0; j < 33; j++) {
                g->rib[i][j][0].x = -25.0f + 50.0f * j / 32.0f;
                g->rib[i][j][0].y = 0.0f;
                g->rib[i][j][0].z = 5.0f * func_0020B550((j << 16) >> 5);
                g->rib[i][j][0].w = 1.0f;
                g->rib[i][j][1] = g->rib[i][j][0];
                g->rib[i][j][1].y = 100.0f * func_0020B550((j * 0x5555) >> 5) *
                                    (0.8f + 0.2f * func_001A6970(func_0020B550((j % 6 << 16) / 6)));
                g->rib[i][j][2] = g->rib[i][j][1];
                g->rib[i][j][2].y /= 2.0f;
                func_001878E0(&g->rib[i][j][0], &m4, &g->rib[i][j][0]);
                func_001878E0(&g->rib[i][j][1], &m4, &g->rib[i][j][1]);
                func_001878E0(&g->rib[i][j][2], &m4, &g->rib[i][j][2]);
            }
        }
        g->on2 = 0;
        for (i = 0; i < 32; i++) {
            g->burst[i].on = 0;
        }
        g->nw = 0;
        for (i = 0; i < 33; i++) {
            n = ((i << 16) >> 5) - 0x4000;
            n &= 0xFFFF;
            g->arc[i][0].x = 20.0f * func_0020B480(n);
            g->arc[i][0].y = 0.0f;
            g->arc[i][0].z = 20.0f * func_0020B550(n);
            g->arc[i][0].w = 1.0f;
            h = 20.0f + 50.0f * func_0020B550((i * 0x8000) >> 5);
            g->arc[i][1].x = h * func_0020B480(n);
            g->arc[i][1].y = 30.0f * func_0020B550((i * 0x8000) >> 5);
            g->arc[i][1].z = h * func_0020B550(n);
            g->arc[i][1].w = 1.0f;
        }
        for (i = 0; i < 32; i++) {
            g->wave[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            g->ring[i].x = 20.0f * func_0020B550((i << 16) >> 5);
            g->ring[i].y = 20.0f * func_0020B480((i << 16) >> 5);
            g->ring[i].z = 0.0f;
            g->ring[i].w = 1.0f;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 4; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 3; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jp2[i]);
    }
    func_001F5620(g->unitA, g->jn3, &g->jp3);
    if (g->t == g->cnt[0] * 16 + 0x2D && g->t < 0x9E) {
        b563_01E02180(arg0, 0);
    }
    if (g->t == g->cnt[1] * 16 + 0x2F && g->t < 0x90) {
        b563_01E02180(arg0, 1);
    }
    if (g->t == g->cnt[2] * 16 + 0x37 && g->t < 0x98) {
        b563_01E02180(arg0, 2);
    }
    if (g->t == g->cnt[3] * 16 + 0x36 && g->t < 0x97) {
        b563_01E02180(arg0, 3);
    }
    if (g->t == 0xF3) {
        b563_01E02180(arg0, 1);
        b563_01E02180(arg0, 2);
    }

    ((Spr_b563_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b563_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b563_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b563_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b563_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (g->grp[i].e[j].on == 0) {
                continue;
            }
            r = 3.5f * g->grp[i].e[j].t / 32.0f;
            r = 3.5f + r;
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
            alpha = (u32)(64.0f * func_00100FF0((f32)g->grp[i].e[j].t, 32.0f, 16.0f));
            spr.c.r = 0x60;
            spr.c.g = 0x60;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            s = func_00100D50(g->grp[i].e[j].t, 32, 1);
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->grp[i].e[j].v[k], s);
                func_00187B00(&v, &v, &g->grp[i].e[j].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                ((Uv_b563_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->grp[i].e[j].c[k]][0];
                ((Uv_b563_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->grp[i].e[j].c[k]][2];
                ((Uv_b563_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->grp[i].e[j].c[k]][1];
                ((Uv_b563_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->grp[i].e[j].c[k]][3];
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->grp[i].e[j].t++;
            if (g->grp[i].e[j].t > 32) {
                g->grp[i].e[j].on = 0;
            }
        }
    }

    if (g->t > 0 && g->t < 0x10E) {
        n = g->t % 32;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (j = 0; j < 3; j++) {
            g->spark[n].pos[j] = g->jp2[j];
            for (k = 0; k < 4; k++) {
                g->spark[n].v[j][k].x = 1.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
                g->spark[n].v[j][k].y =
                    -2.0f * func_001A6970(D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1]);
                g->spark[n].v[j][k].z = 1.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
                g->spark[n].v[j][k].w = 1.0f;
            }
        }
    }

    ((Spr_b563_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b563_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b563_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b563_01E00080 *)(s32)&spr)->pad4 = 0;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    spr.uv0.st.s = 0.0f;
    spr.uv0.st.t = 0.0f;
    spr.uv1.st.s = 1.0f;
    spr.uv1.st.t = 1.0f;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        r = 4.0f + 4.0f * g->spark[i].t / 32.0f;
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
        alpha = (u32)(255.0f * func_00100FF0((f32)g->spark[i].t, 32.0f, 0.0f));
        spr.c.r = 0xC4;
        spr.c.g = 0xC4;
        spr.c.b = 0x40;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = (f32)g->spark[i].t / 32.0f;
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                func_00187B48(&v, &g->spark[i].v[j][k], s);
                func_00187B00(&v, &v, &g->spark[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 32) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x9B) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Quad_b563_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b563_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b563_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b563_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[2], 1);
        func_00208CB0(&pk, 0);
        func_0020EB40(m);
        func_0020C940(m2, NULL, NULL, &g->tgt);
        func_00100E00(m2, g->obj * -0xAAA, 0);
        a = func_00101020((f32)g->t2, 12.0f);
        b = 0.5f + 0.5f * func_00101020((f32)g->t2, 12.0f);
        v.x = b;
        v.y = a;
        v.z = b;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        u0 = 128.0f * func_00100FF0((f32)g->t2, 110.0f, 12.0f);
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 32; j++) {
                alpha = (u32)(u0 * func_001A6C48(func_0020B550((j << 15) >> 5), 1.0f));
                pk.v[0].c.r = 0xFF;
                pk.v[0].c.g = 0x80;
                pk.v[0].c.b = 0x40;
                pk.v[0].c.a = alpha;
                pk.v[0].c.q = 1.0f;
                alpha = (u32)(u0 * func_001A6C48(func_0020B550(((j + 1) << 15) >> 5), 1.0f));
                pk.v[1].c.r = 0xFF;
                pk.v[1].c.g = 0x80;
                pk.v[1].c.b = 0x40;
                pk.v[1].c.a = alpha;
                pk.v[1].c.q = 1.0f;
                pk.v[2].c = pk.v[0].c;
                pk.v[2].c.a = 0;
                pk.v[3].c = pk.v[1].c;
                pk.v[3].c.a = 0;
                u1 = 5.0f * j / 32.0f;
                h = 5.0f * (j + 1) / 32.0f;
                w0 = (f32)(g->t % (i + 8)) / (f32)(i + 8);
                w1 = 1.0f + w0;
                pk.v[0].s = u1;
                pk.v[0].t = w0;
                pk.v[1].s = h;
                pk.v[1].t = w0;
                pk.v[2].s = u1;
                pk.v[2].t = w1;
                pk.v[3].s = h;
                pk.v[3].t = w1;
                if (func_00100BA0(&g->rib[i][j][2], &g->rib[i][j + 1][2], &g->rib[i][j][0], &g->rib[i][j + 1][0], m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
                pk.v[0].s = u1;
                pk.v[0].t = w1;
                pk.v[1].s = h;
                pk.v[1].t = w1;
                pk.v[2].s = u1;
                pk.v[2].t = w0;
                pk.v[3].s = h;
                pk.v[3].t = w0;
                if (func_00100BA0(&g->rib[i][j][2], &g->rib[i][j + 1][2], &g->rib[i][j][1], &g->rib[i][j + 1][1], m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 110) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x9B && g->t < 0xE9) {
        n = g->t % 32;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        func_0020BBB0(&m4);
        func_00100E00(&m4, g->obj * -0xAAA, 0);
        v.x = 0.0f;
        v.y = 100.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        func_001878E0(&v, &m4, &v);
        for (j = 0; j < 8; j++) {
            g->burst[n].v[j].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            g->burst[n].v[j].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
            g->burst[n].v[j].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            g->burst[n].v[j].w = 1.0f;
            func_00187B00(&g->burst[n].v[j], &g->burst[n].v[j], &v);
        }
    }

    ((Spr_b563_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b563_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b563_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b563_01E00080 *)(s32)&spr)->pad4 = 0;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    spr.uv0.st.s = 0.0f;
    spr.uv0.st.t = 0.0f;
    spr.uv1.st.s = 1.0f;
    spr.uv1.st.t = 1.0f;
    func_0020EB40(m);
    func_0020C940(m2, NULL, NULL, &g->tgt);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        r = 7.5f + 7.5f * g->burst[i].t / 32.0f;
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
        alpha = (u32)(255.0f * func_0020B550((g->burst[i].t << 15) >> 5));
        spr.c.r = 0xC4;
        spr.c.g = 0xC4;
        spr.c.b = 0x40;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[i].t, 32, 1);
        for (j = 0; j < 8; j++) {
            func_00187B48(&v, &g->burst[i].v[j], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 32) {
            g->burst[i].on = 0;
        }
    }

    if (g->t % 10 == 0 && g->t > 0x9B && g->t < 0xE9) {
        g->wave[g->nw].on = 1;
        g->wave[g->nw].t = 0;
        g->nw++;
        if (g->nw >= 32) {
            g->nw = 0;
        }
    }

    ((Quad_b563_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b563_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b563_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b563_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[3], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x012BC8FA);
    for (i = 0; i < 32; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_0020C940(m2, NULL, NULL, &g->tgt);
        func_00100E00(m2, (g->obj + 1) >> 1 << 15, 1);
        s = func_00100D50(g->wave[i].t, 32, 1);
        b = 0.5f + 0.5f * s;
        v.x = b;
        v.y = s;
        v.z = b;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x40;
        pk.v[0].c.a = 0;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        for (j = 0; j < 32; j++) {
            alpha = (u32)((f32)(32 - g->wave[i].t) * (255.0f * func_0020B550((j << 15) >> 5)) / 32.0f);
            pk.v[2].c.r = 0xFF;
            pk.v[2].c.g = 0x80;
            pk.v[2].c.b = 0x40;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            u0 = 0.5546875f + 0.1328125f * (j % 2) / 2.0f;
            u1 = 0.5546875f + 0.1328125f * (j % 2 + 1) / 2.0f;
            pk.v[0].s = u0;
            pk.v[0].t = 0.5f;
            pk.v[1].s = u1;
            pk.v[1].t = 0.5f;
            pk.v[2].s = u0;
            pk.v[2].t = 0.0f;
            pk.v[3].s = u1;
            pk.v[3].t = 0.0f;
            if (func_00100BA0(&g->arc[j][0], &g->arc[j + 1][0], &g->arc[j][1], &g->arc[j + 1][1], m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 32) {
            g->wave[i].on = 0;
        }
    }

    if (g->t == 0x6C) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Line_b563_01E00080 *)(s32)&ln)->flags = 0x13;
        ((Line_b563_01E00080 *)(s32)&ln)->size = 6;
        ((Line_b563_01E00080 *)(s32)&ln)->regs = 0x414141;
        ((Line_b563_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp3);
        s = 1.0f - 0.1f * (g->t3 % 2);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        h = 96.0f * func_00101020((f32)g->t3, 32.0f);
        alpha = (u32)(h * func_00100FF0((f32)g->t3, 130.0f, 98.0f));
        ln.v[0].c.r = 0xFF;
        ln.v[0].c.g = 0xFF;
        ln.v[0].c.b = 0x80;
        ln.v[0].c.a = alpha;
        ln.v[0].c.q = 1.0f;
        ln.v[1].c.r = 0xFF;
        ln.v[1].c.g = 0xFF;
        ln.v[1].c.b = 0x80;
        ln.v[1].c.a = 0;
        ln.v[1].c.q = 1.0f;
        ln.v[2].c = ln.v[1].c;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 32; i++) {
            if (func_00100B00(&v, &g->ring[i], &g->ring[i + 1], m, &ln, &depth) == 1) {
                ln.v[0].p.z = 0xFFFFF8;
                ln.v[1].p.z = ln.v[0].p.z;
                ln.v[2].p.z = ln.v[0].p.z;
                func_002075F0(&ln, ot, 0);
            }
        }
        g->t3++;
        if (g->t3 > 130) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x91) {
        ret = 1;
    } else {
        if (g->t > 0x9B && g->t < 0xFD) {
            ret = 6;
        }
        if (g->t == 0xFD) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x12E) {
        ret = 8;
    }
    return ret;
}

/* shape b563:01E02180, 215 insns: fills the next of the 4 slots of group k (slot index ctx+0xF0[k], wrapping): marks
   it live (byte 1, word 1), 32 random points 1.2 x a random row/column of the main table D_0028BC10[4][32][3] (y
   through func_001A6970), w 1; the slot's position is the group's point ctx+0x30[k]; counts ctx+0xE0[k] up */

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 w4;
    u8 pad8[0x48];
    Vec4f pos;
    Vec4f v[32];
} Ent_b563_01E02180;

typedef struct {
    Ent_b563_01E02180 e[4];
} Grp_b563_01E02180;

typedef struct {
    u8 pad0[0x30];
    Vec4f pos[11];
    s32 cnt[4];
    s32 cur[4];
    Grp_b563_01E02180 grp[1];
} Ctx_b563_01E02180;

static void func_01E02180_b563(s32 arg0, s32 k) {
    extern f32 D_0028BC10[4][32][3];
    extern f32 func_001A6970(f32);
    Ctx_b563_01E02180 *g = (Ctx_b563_01E02180 *)arg0;
    s32 i;

    g->grp[k].e[g->cur[k]].on = 1;
    g->grp[k].e[g->cur[k]].w4 = 1;
    for (i = 0; i < 32; i++) {
        g->grp[k].e[g->cur[k]].v[i].x =
            1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
        g->grp[k].e[g->cur[k]].v[i].y =
            1.2f * func_001A6970(D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1]);
        g->grp[k].e[g->cur[k]].v[i].z =
            1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
        g->grp[k].e[g->cur[k]].v[i].w = 1.0f;
    }
    g->grp[k].e[g->cur[k]].pos = g->pos[k];
    g->cnt[k]++;
    g->cur[k]++;
    if (g->cur[k] >= 4) {
        g->cur[k] = 0;
    }
}
