#include "common.h"

/* shape b571:01E00080 (b571), 1744 insns, 1 copy: b571 scene manager (b512:01E00080's family): setup clears the
   0x3680 scene, takes both units, five textures, the target and joints 0x36 / 0x38, builds a two-radius 33-point
   band, two 33-point circles and 64 random four-step blades; else spawns 8-mote puffs per frame in 16 slots (frames
   1..0x59), ground rings in 32 slots (0x45..0xC7), a band wave every 10th frame in 16 slots, a line circle from frame
   0 and at 0xBB a blade burst, two crossed flares and a second circle; returns 1 / 2 / 8 at 0xB1 / 0xBB / >0xEB */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b571_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b571_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b571_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b571_01E00080 c;
    Uv_b571_01E00080 uv0;
    Xyz_b571_01E00080 p0;
    Uv_b571_01E00080 uv1;
    Xyz_b571_01E00080 p1;
    u8 tail[0x20];
} Spr_b571_01E00080;

typedef struct {
    Rgbaq_b571_01E00080 c;
    f32 s, t;
    Xyz_b571_01E00080 p;
} Tv_b571_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b571_01E00080 v[4];
    u8 tail[0x20];
} Quad_b571_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b571_01E00080 c0;
    Xyz_b571_01E00080 p0;
    Rgbaq_b571_01E00080 c1;
    Xyz_b571_01E00080 p1;
    Rgbaq_b571_01E00080 c2;
    Xyz_b571_01E00080 p2;
    u8 tail[8];
} Ln_b571_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[8];
} Part_b571_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot1;
    s32 rot2;
    Vec4f pos;
} Ring_b571_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Wave_b571_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    u8 pad24[0xC];
    Vec4f tgt;
    s32 m[2];
    u8 pad48[8];
    Vec4f pos[2];
    Part_b571_01E00080 part[16];
    s32 count;
    u8 pad974[0xC];
    Ring_b571_01E00080 ring[32];
    s32 next;
    u8 padD84[0xC];
    Vec4f band[33][2];
    Wave_b571_01E00080 wave[16];
    Vec4f circle[33];
    u8 on2;
    u8 pad1441[3];
    s32 t2;
    u8 pad1448[8];
    Vec4f blade[64][4][2];
    u8 on3;
    u8 pad3451[3];
    s32 t3;
    u8 on4;
    u8 pad3459[3];
    s32 t4;
    Vec4f circle2[33];
    u8 on5;
    u8 pad3671[3];
    s32 t5;
    u8 pad3678[8];
} Scene_b571_01E00080;

static s32 func_01E00080_b571(s32 arg0, s32 code) {
    Scene_b571_01E00080 *g = (Scene_b571_01E00080 *)arg0;
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
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern f32 D_0028BC10[4][32][3];
    extern Vec4f D_28B9F0[][4];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    s32 a;
    u8 alpha;
    f32 s;
    f32 f;
    f32 z;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    f32 m4[4][4];
    Vec4f v;
    Spr_b571_01E00080 spr __attribute__((aligned(8)));
    Quad_b571_01E00080 pk __attribute__((aligned(8)));
    Ln_b571_01E00080 ln __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3680);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(4, 0xF);
        g->tex[3] = func_00202BF0(5, 2);
        g->tex[4] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->m[0] = func_001F5560(g->unitA, 0x36, 1);
        g->m[1] = func_001F5560(g->unitA, 0x38, 0);
        for (i = 0; i < 16; i++) {
            g->part[i].on = 0;
        }
        g->count = 0;
        for (i = 0; i < 32; i++) {
            g->ring[i].on = 0;
        }
        g->next = 0;
        for (i = 0; i < 33; i++) {
            g->band[i][0].x = 20.0f * func_0020B550((i << 16) >> 5);
            g->band[i][0].y = 20.0f * func_0020B480((i << 16) >> 5);
            g->band[i][0].z = 0.0f;
            g->band[i][0].w = 1.0f;
            g->band[i][1].x = 50.0f * func_0020B550((i << 16) >> 5);
            g->band[i][1].y = 50.0f * func_0020B480((i << 16) >> 5);
            g->band[i][1].z = 0.0f;
            g->band[i][1].w = 1.0f;
        }
        for (i = 0; i < 16; i++) {
            g->wave[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            a = (i << 16) >> 5;
            g->circle[i].x = 10.0f * func_0020B550(a);
            g->circle[i].y = 10.0f * func_0020B480(a);
            g->circle[i].z = 0.0f;
            g->circle[i].w = 1.0f;
        }
        g->on2 = 0;
        for (i = 0; i < 64; i++) {
            v.x = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            v.y = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
            v.z = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            v.w = 1.0f;
            func_00100E40(m4, &v);
            func_00100E00(m4, (i % 16 << 16) >> 4, 2);
            f = 80.0f * (0.5f + 0.5f * i / 64.0f);
            for (j = 0; j < 4; j++) {
                z = f * j / 3.0f;
                cn[0].x = 0.0f;
                cn[0].y = -5.0f;
                cn[0].z = z;
                cn[0].w = 1.0f;
                cn[1].x = 0.0f;
                cn[1].y = 5.0f;
                cn[1].z = z;
                cn[1].w = 1.0f;
                func_001878E0(&g->blade[i][j][0], m4, &cn[0]);
                func_001878E0(&g->blade[i][j][1], m4, &cn[1]);
            }
        }
        g->on3 = 0;
        g->on4 = 0;
        for (i = 0; i < 33; i++) {
            a = (i << 16) >> 5;
            g->circle2[i].x = 50.0f * func_0020B550(a);
            g->circle2[i].y = 50.0f * func_0020B480(a);
            g->circle2[i].z = 0.0f;
            g->circle2[i].w = 1.0f;
        }
        g->on5 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    if (g->t > 0 && g->t < 0x5A) {
        n = g->t % 16;
        (void)n;
        g->part[n].on = 1;
        g->part[n].t = 0;
        for (j = 0; j < 8; j++) {
            k = (func_0019A5C8() >> 23) % 256 % 32;
            g->part[n].v[j].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][0];
            g->part[n].v[j].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][1];
            g->part[n].v[j].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][2];
            g->part[n].v[j].w = 1.0f;
            func_00187B00(&g->part[n].v[j], &g->part[n].v[j], &g->pos[0]);
        }
    }

    ((Spr_b571_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b571_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b571_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b571_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b571_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    y = 0;
    ((Uv_b571_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b571_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b571_01E00080 *)(s32)&spr.uv1)->u = (x + 128) << 4;
    ((Uv_b571_01E00080 *)(s32)&spr.uv1)->v = (y + 128) << 4;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    cn[0].x = -0.6f;
    cn[0].y = -0.6f;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = 0.6f;
    cn[1].y = 0.6f;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    func_001878E0(&cn[0], m3, &cn[0]);
    func_001878E0(&cn[1], m3, &cn[1]);
    for (i = 0; i < 16; i++) {
        if (g->part[i].on == 0) {
            continue;
        }
        alpha = g->part[i].t * 255 >> 4;
        spr.c.r = 0xFF;
        spr.c.g = 0x60;
        spr.c.b = 0x56;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (l = 0; l < 16; l++) {
            f = g->part[i].t + 0.07f * l;
            if (f > 16.0f) {
                f = 16.0f;
            }
            s = (16.0f - f) / 16.0f;
            for (k = 0; k < 8; k++) {
                func_00187B18(&v, &g->part[i].v[k], &g->pos[0]);
                func_00187B48(&v, &v, s);
                func_00187B00(&v, &v, &g->pos[0]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->part[i].t++;
        if (g->part[i].t > 16) {
            g->part[i].on = 0;
        }
    }

    if (g->t > 0x44 && g->t < 0xC8) {
        n = g->t % 32;
        (void)n;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        g->ring[n].rot1 = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        g->ring[n].rot2 = ((func_0019A5C8() >> 23) % 256 * 0xB60 >> 8) - 0x5B0;
        g->ring[n].pos = g->pos[0];
        g->count++;
        if (g->count > 64) {
            g->count = 64;
        }
    }

    ((Quad_b571_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b571_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b571_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b571_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, 5);
    cn[0].x = -20.0f;
    cn[0].y = 0.0f;
    cn[0].z = -20.0f;
    cn[0].w = 1.0f;
    cn[1].x = 20.0f;
    cn[1].y = 0.0f;
    cn[1].z = -20.0f;
    cn[1].w = 1.0f;
    cn[2].x = -20.0f;
    cn[2].y = 0.0f;
    cn[2].z = 20.0f;
    cn[2].w = 1.0f;
    cn[3].x = 20.0f;
    cn[3].y = 0.0f;
    cn[3].z = 20.0f;
    cn[3].w = 1.0f;
    for (i = 0; i < 32; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        s = 0.4f + 0.6f * g->ring[i].t / 32.0f;
        v.x = s;
        v.y = 1.0f;
        v.z = s;
        v.w = 1.0f;
        func_0020EB40(m);
        func_0020C940(m2, NULL, NULL, &g->ring[i].pos);
        func_00100E00(m2, g->ring[i].rot2, 2);
        func_00100E00(m2, g->ring[i].rot1, 1);
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(g->count * (200.0f * (1.0f - func_00100D50(g->ring[i].t, 32, 1))) / 64.0f);
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x74;
        pk.v[0].c.b = 0x64;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        pk.v[0].s = 0.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 1.0f;
        pk.v[1].t = 0.0f;
        pk.v[2].s = 0.0f;
        pk.v[2].t = 1.0f;
        pk.v[3].s = 1.0f;
        pk.v[3].t = 1.0f;
        if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
            func_002075F0(&pk, ot, (u32)depth);
        }
        g->ring[i].t++;
        if (g->ring[i].t > 32) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x5A && g->t % 10 == 0) {
        g->wave[g->next].on = 1;
        g->wave[g->next].t = 0;
        g->next++;
        if (g->next >= 16) {
            g->next = 0;
        }
    }

    ((Quad_b571_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b571_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b571_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b571_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x012BC8FA);
    for (i = 0; i < 16; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        s = (f32)(16 - g->wave[i].t) / 16.0f;
        v.x = s;
        v.y = s;
        v.z = 1.0f;
        v.w = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos[0]);
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = g->wave[i].t * 255 >> 4;
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x68;
        pk.v[0].c.b = 0x60;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c.r = 0xFF;
        pk.v[2].c.g = 0x68;
        pk.v[2].c.b = 0x60;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        for (j = 0; j < 32; j++) {
            pk.v[0].s = 0.5546875f;
            pk.v[0].t = 0.0f;
            pk.v[1].s = 0.6875f;
            pk.v[1].t = 0.0f;
            pk.v[2].s = 0.5546875f;
            pk.v[2].t = 0.5f;
            pk.v[3].s = 0.6875f;
            pk.v[3].t = 0.5f;
            if (func_00100BA0(&g->band[j][0], &g->band[j + 1][0], &g->band[j][1], &g->band[j + 1][1], m, &pk,
                              &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 16) {
            g->wave[i].on = 0;
        }
    }

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Ln_b571_01E00080 *)(s32)&ln)->flags = 0x13;
        ((Ln_b571_01E00080 *)(s32)&ln)->size = 6;
        ((Ln_b571_01E00080 *)(s32)&ln)->regs = 0x414141;
        ((Ln_b571_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->pos[0]);
        s = 1.0f - 0.1f * (g->t2 % 2);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(128.0f * func_00101020((f32)g->t2, 32.0f) * func_00100FF0((f32)g->t2, 106.0f, 74.0f));
        ln.c0.r = 0xFF;
        ln.c0.g = 0x40;
        ln.c0.b = 0x40;
        ln.c0.a = alpha;
        ln.c0.q = 1.0f;
        ln.c1.r = 0xFF;
        ln.c1.g = 0x40;
        ln.c1.b = 0x40;
        ln.c1.a = 0;
        ln.c1.q = 1.0f;
        ln.c2 = ln.c1;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (j = 0; j < 32; j++) {
            if (func_00100B00(&v, &g->circle[j], &g->circle[j + 1], m, &ln, &depth) == 1) {
                ln.p0.z = 0xFFFFF8;
                ln.p1.z = ln.p0.z;
                ln.p2.z = ln.p0.z;
                func_002075F0(&ln, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 106) {
            g->on2 = 0;
        }
    }

    if (g->t == 0xBB) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Quad_b571_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b571_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b571_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b571_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[3], 1);
        func_00208CB0(&pk, 5);
        s = 0.6f + 0.4f * g->t3 / 48.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020EB40(m);
        func_0020C940(m2, &v, NULL, &g->tgt);
        func_0020BC00(m, m2);
        f = 1.0f - func_00100D50(g->t3, 48, 1);
        for (i = 0; i < 64; i++) {
            for (j = 0; j < 3; j++) {
                alpha = (u32)(f * (f32)((3 - j) * 255 / 3));
                pk.v[0].c.r = 0xFF;
                pk.v[0].c.g = 0x64;
                pk.v[0].c.b = 0x5A;
                pk.v[0].c.a = alpha;
                pk.v[0].c.q = 1.0f;
                pk.v[1].c = pk.v[0].c;
                alpha = (u32)(f * (f32)((3 - (j + 1)) * 255 / 3));
                (void)alpha;
                pk.v[2].c.r = 0xFF;
                pk.v[2].c.g = 0x64;
                pk.v[2].c.b = 0x5A;
                pk.v[2].c.a = alpha;
                pk.v[2].c.q = 1.0f;
                pk.v[3].c = pk.v[2].c;
                pk.v[0].s = 0.0f;
                pk.v[0].t = 0.0f;
                pk.v[1].s = 1.0f;
                pk.v[1].t = 0.0f;
                pk.v[2].s = 0.0f;
                pk.v[2].t = 1.0f;
                pk.v[3].s = 1.0f;
                pk.v[3].t = 1.0f;
                if (func_00100BA0(&g->blade[i][j][0], &g->blade[i][j][1], &g->blade[i][j + 1][0],
                                  &g->blade[i][j + 1][1], m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t3++;
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    if (g->t == 0xBB) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        ((Quad_b571_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b571_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b571_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b571_01E00080 *)(s32)&pk)->pad4 = 0;
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[4], 1);
        func_00208CB0(&pk, 5);
        s = 50.0f * (0.4f + 0.6f * g->t4 / 48.0f);
        v.x = s;
        v.y = s;
        v.z = 1.0f;
        v.w = 1.0f;
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->t4, 48, 1)));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        for (i = 0; i < 2; i++) {
            func_0020EB40(m);
            func_0020C940(m2, NULL, NULL, &g->tgt);
            a = (i * 2 - 1) * 30 * 0x10000 / 360;
            func_00100E00(m2, a, 2);
            func_00100E00(m2, a + 0x4000, 0);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (j = 0; j < 4; j++) {
                pk.v[0].s = 0.0f;
                pk.v[0].t = 0.0f;
                pk.v[1].s = 1.0f;
                pk.v[1].t = 0.0f;
                pk.v[2].s = 0.0f;
                pk.v[2].t = 1.0f;
                pk.v[3].s = 1.0f;
                pk.v[3].t = 1.0f;
                if (func_002058D0(D_28B9F0[j], D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->t4++;
        if (g->t4 > 48) {
            g->on4 = 0;
        }
    }

    if (g->t == 0xBB) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Ln_b571_01E00080 *)(s32)&ln)->flags = 0x13;
        ((Ln_b571_01E00080 *)(s32)&ln)->size = 6;
        ((Ln_b571_01E00080 *)(s32)&ln)->regs = 0x414141;
        ((Ln_b571_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->tgt);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t5, 48, 1)));
        ln.c0.r = 0xFF;
        ln.c0.g = 0x60;
        ln.c0.b = 0x50;
        ln.c0.a = alpha;
        ln.c0.q = 1.0f;
        ln.c1.r = 0xFF;
        ln.c1.g = 0x60;
        ln.c1.b = 0x50;
        ln.c1.a = 0;
        ln.c1.q = 1.0f;
        ln.c2 = ln.c1;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (j = 0; j < 32; j++) {
            if (func_00100B00(&v, &g->circle2[j], &g->circle2[j + 1], m, &ln, &depth) == 1) {
                ln.p0.z = 0xFFFFF8;
                ln.p1.z = ln.p0.z;
                ln.p2.z = ln.p0.z;
                func_002075F0(&ln, ot, 0);
            }
        }
        g->t5++;
        if (g->t5 > 48) {
            g->on5 = 0;
        }
    }

    if (g->t == 0xB1) {
        ret = 1;
    } else if (g->t == 0xBB) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0xEB) {
        ret = 8;
    }
    return ret;
}
