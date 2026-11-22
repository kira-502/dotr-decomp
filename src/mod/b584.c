#include "common.h"

/* shape b584:01E00080 (b584), 1809 insns, 1 copy: b584 scene manager (b571:01E00080's family): setup clears the
   0xD3E0 scene, takes both units, three textures, the target and joints 0x22 / 0x1C, builds a 64x9 random-phase cone
   grid and 33- / 17-point circles; else every third frame 0x42..0xDA spawns a cone ring at joint 0x22 in 10 slots
   (triangle fan over the grid plus a line circle), on 1..0x27 a four-sprite burst at joint 0x1C in 32 slots, every
   third frame 0x89..0xDB a 64-sprite cloud at a random spot round the target in 24 slots (two-texture sprites, a line
   circle, 32x8 sparks); returns 1 / 6 / 2 / 8 at 0x7E / 0x89..0xDB / 0xDC / >0xF4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b584_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b584_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b584_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b584_01E00080 c;
    Uv_b584_01E00080 uv0;
    Xyz_b584_01E00080 p0;
    Uv_b584_01E00080 uv1;
    Xyz_b584_01E00080 p1;
    u8 tail[0x20];
} Spr_b584_01E00080;

typedef struct {
    Rgbaq_b584_01E00080 c;
    f32 s, t;
    Xyz_b584_01E00080 p;
} Tv_b584_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b584_01E00080 v[3];
    u8 tail[0x20];
} Tri_b584_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b584_01E00080 c0;
    Xyz_b584_01E00080 p0;
    Rgbaq_b584_01E00080 c1;
    Xyz_b584_01E00080 p1;
    Rgbaq_b584_01E00080 c2;
    Xyz_b584_01E00080 p2;
    u8 tail[8];
} Ln_b584_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
} Ring_b584_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[4];
    Vec4f pos;
    Vec4f v[4];
} Burst_b584_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f w[32];
} Big_b584_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 m0;
    Vec4f pos0;
    s32 m1;
    u8 pad34[0xC];
    Vec4f pos1;
    Vec4f tgt;
    s32 next;
    u8 pad64[0xC];
    Vec4f grid[64][9];
    Ring_b584_01E00080 ring[10];
    Vec4f circle[33];
    Burst_b584_01E00080 burst[32];
    s32 count;
    u8 pad33C4[0xC];
    Big_b584_01E00080 big[24];
    Vec4f circle2[17];
} Scene_b584_01E00080;

static s32 func_01E00080_b584(s32 arg0, s32 code) {
    Scene_b584_01E00080 *g = (Scene_b584_01E00080 *)arg0;
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
    extern void func_00101080(void *, f32);
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
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    extern f32 D_0028BC10[4][32][3];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 a;
    s32 x;
    u8 alpha;
    u8 a2;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Tri_b584_01E00080 tri __attribute__((aligned(8)));
    Ln_b584_01E00080 ln __attribute__((aligned(8)));
    Spr_b584_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD3E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(4, 0xF);
        g->tex[1] = func_00202BF0(5, 0);
        g->tex[2] = func_00202BF0(5, 1);
        g->m0 = func_001F5560(g->unitA, 0x22, 1);
        g->m1 = func_001F5560(g->unitA, 0x1C, 0);
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 64; i++) {
            s = (i + 1) / 64.0f;
            h = 50.0f * (64 - i) / 64.0f;
            a = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            for (l = 0; l < 9; l++) {
                k = a + ((l << 16) >> 3);
                k &= 0xFFFF;
                g->grid[i][l].x = s * func_0020B550(k);
                g->grid[i][l].y = s * func_0020B480(k);
                g->grid[i][l].z = h;
                g->grid[i][l].w = 1.0f;
            }
        }
        for (i = 0; i < 33; i++) {
            g->circle[i].x = 25.0f * func_0020B550((i << 16) >> 5);
            g->circle[i].y = 25.0f * func_0020B480((i << 16) >> 5);
            g->circle[i].z = 0.0f;
            g->circle[i].w = 1.0f;
        }
        for (i = 0; i < 32; i++) {
            g->burst[i].on = 0;
        }
        g->count = 0;
        for (i = 0; i < 24; i++) {
            g->big[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            a = (i << 16) >> 4;
            g->circle2[i].x = 20.0f * func_0020B550(a);
            g->circle2[i].y = 20.0f * func_0020B480(a);
            g->circle2[i].z = 0.0f;
            g->circle2[i].w = 1.0f;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->m0, &g->pos0);
    func_001F5620(g->unitA, g->m1, &g->pos1);
    if (g->t % 3 == 0) {
        if (g->t > 0x41 && g->t < 0xDB) {
        g->ring[g->next].on = 1;
        g->ring[g->next].t = 0;
        g->ring[g->next].pos = g->pos0;
        g->next++;
        if (g->next >= 10) {
            g->next = 0;
        }
        }
    }

    ((Tri_b584_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b584_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b584_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b584_01E00080 *)(s32)&tri)->pad4 = 0;
    func_002086D0(&tri, func_00208D00(1));
    func_00208700(&tri, g->tex[0], 1);
    func_00208CB0(&tri, ((u64)0x1FC << 32) | 0x012BC8FA);
    ((Ln_b584_01E00080 *)(s32)&ln)->flags = 0x13;
    ((Ln_b584_01E00080 *)(s32)&ln)->size = 6;
    ((Ln_b584_01E00080 *)(s32)&ln)->regs = 0x414141;
    ((Ln_b584_01E00080 *)(s32)&ln)->pad4 = 0;
    func_002086D0(&ln, func_00208D00(1));
    for (i = 0; i < 10; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_0020C940(m2, NULL, NULL, &g->ring[i].pos);
        func_00100E00(m2, (g->obj + 1) >> 1 << 15, 1);
        s = 0.8f + 0.2f * g->ring[i].t / 2.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        f = 1.0f - func_00100D50(g->ring[i].t, 2, 1);
        alpha = (u32)(128.0f * f);
        tri.v[0].c.r = 0xA4;
        tri.v[0].c.g = 0xFF;
        tri.v[0].c.b = 0x64;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(16.0f * f);
        (void)alpha;
        tri.v[1].c.r = 0x40;
        tri.v[1].c.g = 0xFF;
        tri.v[1].c.b = 0x20;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (k = 0; k < 64; k++) {
            for (j = 0; j < 8; j++) {
                tri.v[0].s = 0.62109375f;
                tri.v[0].t = 0.25f;
                tri.v[1].s = 0.5546875f;
                tri.v[1].t = 0.0f;
                tri.v[2].s = 0.6875f;
                tri.v[2].t = 0.0f;
                if (func_00100B00(&v, &g->grid[k][j], &g->grid[k][j + 1], m, &tri, &depth) == 1) {
                    func_002075F0(&tri, ot, (u32)depth);
                }
            }
        }
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->ring[i].pos);
        s = 0.8f + 0.2f * func_00100D50(g->ring[i].t, 2, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        ln.c0.r = 0xFF;
        ln.c0.g = 0xC4;
        ln.c0.b = 0xA4;
        ln.c0.a = 0;
        ln.c0.q = 1.0f;
        ln.c1.r = 0xC8;
        ln.c1.g = 0;
        ln.c1.b = 0;
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
        g->ring[i].t++;
        if (g->ring[i].t > 2) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x28) {
        n = g->t % 32;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        g->burst[n].pos = g->pos1;
        for (j = 0; j < 4; j++) {
            g->burst[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->burst[n].v[j].x = 0.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            g->burst[n].v[j].y = 0.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
            g->burst[n].v[j].z = 0.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            g->burst[n].v[j].w = 1.0f;
            g->burst[n].v[j].y += -10.0f;
            g->burst[n].v[j].z += -10.0f * g->obj;
        }
    }

    ((Spr_b584_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b584_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b584_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b584_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b584_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        r = 0.2f + 0.8f * g->burst[i].t / 32.0f;
        r = 5.0f * r;
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
        alpha = (32 - g->burst[i].t) * 96 >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x20;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = func_00100D50(g->burst[i].t, 32, 1);
        for (k = 0; k < 4; k++) {
            func_00187B48(&v, &g->burst[i].v[k], f);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b584_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->burst[i].c[k]][0];
            ((Uv_b584_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->burst[i].c[k]][2];
            ((Uv_b584_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->burst[i].c[k]][1];
            ((Uv_b584_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->burst[i].c[k]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 32) {
            g->burst[i].on = 0;
        }
    }

    if (g->t % 3 == 0 && g->t > 0x88 && g->t < 0xDC) {
        g->big[g->count].on = 1;
        g->big[g->count].t = 1;
        g->big[g->count].pos.x = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
        g->big[g->count].pos.y = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
        g->big[g->count].pos.z = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
        g->big[g->count].pos.w = 1.0f;
        func_00187B00(&g->big[g->count].pos, &g->big[g->count].pos, &g->tgt);
        for (j = 0; j < 64; j++) {
            g->big[g->count].c[j] = (func_0019A5C8() >> 23) % 4;
            g->big[g->count].v[j].x = 0.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            g->big[g->count].v[j].y = 0.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
            g->big[g->count].v[j].z = 0.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            g->big[g->count].v[j].w = 1.0f;
        }
        for (j = 0; j < 32; j++) {
            func_00101080(&g->big[g->count].w[j], 2.5f);
        }
        g->count++;
        if (g->count >= 24) {
            g->count = 0;
        }
    }

    ((Ln_b584_01E00080 *)(s32)&ln)->flags = 0x13;
    ((Ln_b584_01E00080 *)(s32)&ln)->size = 6;
    ((Ln_b584_01E00080 *)(s32)&ln)->regs = 0x414141;
    ((Ln_b584_01E00080 *)(s32)&ln)->pad4 = 0;
    func_002086D0(&ln, func_00208D00(1));
    for (i = 0; i < 24; i++) {
        if (g->big[i].on == 0) {
            continue;
        }
        ((Spr_b584_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b584_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b584_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b584_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b584_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 4.0f * (0.8f + 0.2f * g->big[i].t / 24.0f);
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
        alpha = (24 - g->big[i].t) * 255 / 24;
        a2 = (24 - g->big[i].t) * 116 / 24;
        for (j = 0; j < 64; j++) {
            f = func_00100D50(g->big[i].t, 24, 1);
            if (j % 2 == 0) {
                f *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0x80;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x40;
                spr.c.g = 0x80;
                spr.c.b = 0x30;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->big[i].v[j], f);
            func_00187B00(&v, &v, &g->big[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b584_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->big[i].c[j]][0];
            ((Uv_b584_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->big[i].c[j]][2];
            ((Uv_b584_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->big[i].c[j]][1];
            ((Uv_b584_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->big[i].c[j]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->big[i].pos);
        s = 0.2f + 0.8f * func_00100D50(g->big[i].t, 24, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(196.0f * ((f32)(24 - g->big[i].t) / 24.0f));
        ln.c0.r = 0xB4;
        ln.c0.g = 0xFF;
        ln.c0.b = 0xA4;
        ln.c0.a = alpha;
        ln.c0.q = 1.0f;
        ln.c1.r = 0x20;
        ln.c1.g = 0xFF;
        ln.c1.b = 0x20;
        ln.c1.a = 0;
        ln.c1.q = 1.0f;
        ln.c2 = ln.c1;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (j = 0; j < 16; j++) {
            if (func_00100B00(&v, &g->circle2[j], &g->circle2[j + 1], m, &ln, &depth) == 1) {
                func_002075F0(&ln, ot, 0xFFFFFF);
            }
        }
        ((Spr_b584_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b584_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b584_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b584_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b584_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        x = 0;
        ((Uv_b584_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b584_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b584_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b584_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.0f;
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
        f = func_00100D50(g->big[i].t, 24, 1);
        for (l = 0; l < 32; l++) {
            for (k = 0; k < 8; k++) {
                spr.c.r = 0xFF;
                spr.c.g = 0x60;
                spr.c.b = 0x60;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->big[i].w[l], f + 0.007f * k);
                func_00187B00(&v, &v, &g->big[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->big[i].t++;
        if (g->big[i].t > 24) {
            g->big[i].on = 0;
        }
    }

    if (g->t == 0x7E) {
        ret = 1;
    } else {
        if (g->t > 0x88 && g->t < 0xDC) {
            ret = 6;
        }
        if (g->t == 0xDC) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xF4) {
        ret = 8;
    }
    return ret;
}
