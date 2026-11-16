#include "common.h"

/* shape b599:01E00080 (b599), 1701 insns, 1 copy: b599 module main (written from the asm, b261:01E00080's family):
   code >= 0 clears the scene, takes the unit, three textures and four joints; else follows the joint pair's midpoint
   and joint 0xF, at seven ticks (39..129, a switch) spawns a 32-sprite burst at the midpoint in 10 slots, on 141..349
   a sprite at joint 0xF in 32 slots, on 141..167 an 8-sprite rise at joint 0x70's tick-140 spot and on 221..359 a
   24-sprite swirl at its tick-220 spot (sprites scaled from random rows of D_0028BC10), passes a tick-faded level to
   func_001F6D00 and returns 1 / 6 / 2 / 8 at 220.67 / 231..359 / 360 / 401 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b599_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b599_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b599_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b599_01E00080 c;
    Uv_b599_01E00080 uv0;
    Xyz_b599_01E00080 p0;
    Uv_b599_01E00080 uv1;
    Xyz_b599_01E00080 p1;
    u8 tail[0x20];
} Spr_b599_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[32];
    u8 pad48[8];
    Vec4f pos;
    Vec4f v[32];
} Burst_b599_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c;
    u8 padA[6];
    Vec4f pos;
} Spot_b599_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[8];
} Rise_b599_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[24];
    f32 sc[24];
    u8 padC8[8];
    Vec4f v[24];
} Swirl_b599_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 obj;
    s32 tex[3];
    s32 m[2];
    Vec4f pos[2];
    Vec4f mid;
    s32 m2;
    u8 pad54[0xC];
    Vec4f pos2;
    s32 m3;
    u8 pad74[0xC];
    Vec4f p80;
    Vec4f p90;
    s32 na;
    u8 padA4[0xC];
    Burst_b599_01E00080 a[10];
    Spot_b599_01E00080 b[32];
    Rise_b599_01E00080 c[32];
    Swirl_b599_01E00080 d[32];
} Scene_b599_01E00080;

static s32 func_01E00080_b599(s32 arg0, s32 code) {
    Scene_b599_01E00080 *g = (Scene_b599_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00101050(s32, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    extern f32 D_0028BC10[4][32][3];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 c;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b599_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x7870);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->m[0] = func_001F5560(g->unitA, 0x4F, 1);
        g->m[1] = func_001F5560(g->unitA, 0x59, 0);
        g->m2 = func_001F5560(g->unitA, 0xF, 0);
        g->m3 = func_001F5560(g->unitA, 0x70, 0);
        g->na = 0;
        for (i = 0; i < 10; i++) {
            g->a[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->b[i].on = 0;
        }
        g->p80.x = 0.0f;
        g->p80.y = 0.0f;
        g->p80.z = 0.0f;
        g->p80.w = 1.0f;
        for (i = 0; i < 32; i++) {
            g->c[i].on = 0;
        }
        g->p90.x = 0.0f;
        g->p90.y = 0.0f;
        g->p90.z = 0.0f;
        g->p90.w = 1.0f;
        for (j = 0; j < 32; j++) {
            g->d[j].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    func_00187B00(&g->mid, &g->pos[0], &g->pos[1]);
    { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }
    func_001F5620(g->unitA, g->m2, &g->pos2);
    if (g->t == 0x8C) {
        func_001F5620(g->unitA, g->m3, &g->p80);
    }
    if (g->t == 0xDC) {
        func_001F5620(g->unitA, g->m3, &g->p90);
    }
    switch (g->t) {
    case 0x27:
    case 0x31:
    case 0x3B:
    case 0x63:
    case 0x6D:
    case 0x77:
    case 0x81:
        n = g->na;
        (void)n;
        g->a[n].on = 1;
        g->a[n].t = 1;
        g->a[n].pos = g->mid;
        for (j = 0; j < 32; j++) {
            g->a[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->a[n].v[j].x = 0.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->a[n].v[j].y = 0.2f * func_001A6970(D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                                            [(func_0019A5C8() >> 23) % 3]);
            g->a[n].v[j].z = 0.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->a[n].v[j].w = 1.0f;
        }
        g->na++;
        if (g->na >= 10) {
            g->na = 0;
        }
        break;
    }

    ((Spr_b599_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b599_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b599_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b599_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b599_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 10; i++) {
        if (g->a[i].on == 0) {
            continue;
        }
        alpha = (32 - g->a[i].t) * 96 >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 3.0f * (0.5f + 0.5f * g->a[i].t / 32.0f);
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
        f = func_00100D50(g->a[i].t, 32, 1);
        for (k = 0; k < 32; k++) {
            func_00187B48(&v, &g->a[i].v[k], f);
            func_00187B00(&v, &v, &g->a[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b599_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->a[i].c[k]][0];
            ((Uv_b599_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->a[i].c[k]][2];
            ((Uv_b599_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->a[i].c[k]][1];
            ((Uv_b599_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->a[i].c[k]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->a[i].t++;
        if (g->a[i].t > 32) {
            g->a[i].on = 0;
        }
    }

    if (g->t > 0x8C && g->t < 0x15E) {
        n = g->t % 32;
        (void)n;
        g->b[n].on = 1;
        g->b[n].t = 0;
        g->b[n].c = (func_0019A5C8() >> 23) % 16;
        g->b[n].pos.x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                         [(func_0019A5C8() >> 23) % 3];
        g->b[n].pos.y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                         [(func_0019A5C8() >> 23) % 3];
        g->b[n].pos.z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                         [(func_0019A5C8() >> 23) % 3];
        g->b[n].pos.w = 1.0f;
        func_00187B00(&g->b[n].pos, &g->b[n].pos, &g->pos2);
    }

    ((Spr_b599_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b599_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b599_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b599_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b599_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->b[i].on == 0) {
            continue;
        }
        alpha = (u32)(64.0f * func_0020B550((g->b[i].t << 15) >> 5));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 6.0f * (0.5f + 0.5f * g->b[i].t / 32.0f);
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
        func_00187B00(&out[0], &cn[0], &g->b[i].pos);
        func_00187B00(&out[1], &cn[1], &g->b[i].pos);
        c = g->b[i].c;
        x = c % 4 * 32;
        y = (c >> 2) * 32;
        ((Uv_b599_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b599_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b599_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b599_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        g->b[i].t++;
        if (g->b[i].t > 32) {
            g->b[i].on = 0;
        }
    }

    if (g->t > 0x8C && g->t < 0xA8) {
        n = g->t;
        n %= 32;
        g->c[n].on = 1;
        g->c[n].t = 0;
        for (j = 0; j < 8; j++) {
            g->c[n].v[j].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->c[n].v[j].y = func_001A6970(2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4]
                                                            [(func_0019A5C8() >> 23) % 32]
                                                            [(func_0019A5C8() >> 23) % 3]);
            g->c[n].v[j].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->c[n].v[j].w = 1.0f;
        }
    }

    ((Spr_b599_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b599_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b599_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b599_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b599_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b599_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b599_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b599_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b599_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->c[i].on == 0) {
            continue;
        }
        alpha = (u32)(164.0f * func_0020B550((g->c[i].t << 15) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0xE8;
        spr.c.b = 0xE0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 2.0f;
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
        f = 1.0f - func_00100D50(g->c[i].t, 32, 1);
        s = 1.0f - 0.7f * func_00100D50(g->c[i].t, 32, 1);
        for (j = 0; j < 8; j++) {
            v.x = g->c[i].v[j].x * s;
            v.y = (30.0f + g->c[i].v[j].y) * f;
            v.z = g->c[i].v[j].z * s;
            func_00187B00(&v, &v, &g->p80);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->c[i].t++;
        if (g->c[i].t > 32) {
            g->c[i].on = 0;
        }
    }

    if (g->t > 0xDC && g->t < 0x168) {
        n = g->t;
        n %= 32;
        g->d[n].on = 1;
        g->d[n].t = 0;
        for (j = 0; j < 24; j++) {
            g->d[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->d[n].sc[j] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->d[n].v[j].x = 3.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->d[n].v[j].y = 3.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->d[n].v[j].z = 3.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32]
                                             [(func_0019A5C8() >> 23) % 3];
            g->d[n].v[j].w = 1.0f;
        }
    }

    ((Spr_b599_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b599_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b599_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b599_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b599_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    h = 1.0f - (f32)(func_00101050(g->t, 0x148, 0x168) - 0x148) / 32.0f;
    for (i = 0; i < 32; i++) {
        if (g->d[i].on == 0) {
            continue;
        }
        alpha = (u32)(h * (128.0f * func_0020B480((g->d[i].t << 14) >> 5)));
        spr.c.r = 0x80;
        spr.c.g = 0x34;
        spr.c.b = 0x28;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 18.0f * (0.5f + 0.5f * g->d[i].t / 32.0f);
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
        f = g->d[i].t / 32.0f;
        s = 0.1f + 0.9f * g->d[i].t / 32.0f;
        for (j = 0; j < 24; j++) {
            ((Uv_b599_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->d[i].c[j]][0];
            ((Uv_b599_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->d[i].c[j]][2];
            ((Uv_b599_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->d[i].c[j]][1];
            ((Uv_b599_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->d[i].c[j]][3];
            func_00187B48(&out[0], &cn[0], g->d[i].sc[j]);
            func_00187B48(&out[1], &cn[1], g->d[i].sc[j]);
            v.x = g->d[i].v[j].x * s;
            v.z = f * (g->d[i].v[j].z + -150.0f * g->obj) + -10.0f * g->obj;
            v.y = g->d[i].v[j].y * s;
            func_00187B00(&v, &v, &g->p90);
            func_00187B00(&out[0], &out[0], &v);
            func_00187B00(&out[1], &out[1], &v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->d[i].t++;
        if (g->d[i].t > 32) {
            g->d[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x190 - g->t, 0, 32) * (func_00101050(g->t - 0x8C, 0, 32) * -64) >> 10) + 0x80));
    if (g->t == 220.66667f) {
        ret = 1;
    } else {
        if (g->t > 230.66667f && g->t < 0x168) {
            ret = 6;
        }
        if (g->t == 0x168) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x190) {
        ret = 8;
    }
    return ret;
}
