#include "common.h"

/* shape b100:01E00080 (b100), 1882 insns, 1 copy: b100 scene manager (b584:01E00080's family; best draft): setup
   clears the 0xBF60 scene, takes both units, two textures, the target and six joints; else 6x8-sprite trails at the
   joints in 8 slots (1..0xF9), every 4th frame 6-sprite rings in 8 slots, from 0x1E a streamer of 16 sub-puffs per
   slot in 32 slots flying from the joints' midpoint toward the target, 32-spark bursts and single dots at the target
   (0x75..0xF9) and a target tint via func_001F6590; returns 1 / 6 / 2 / 8 at 0x6A / 0x75..0xF9 / 0xFA / >0xFB */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b100_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b100_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b100_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b100_01E00080 c;
    Uv_b100_01E00080 uv0;
    Xyz_b100_01E00080 p0;
    Uv_b100_01E00080 uv1;
    Xyz_b100_01E00080 p1;
    u8 tail[0x20];
} Spr_b100_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[6][8];
    u8 pad38[8];
    Vec4f pos[6];
    Vec4f v[6][8];
} Trail_b100_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos[6];
    Vec4f v[6];
} Ring_b100_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 son[16];
    s32 st[16];
    u8 c[16][2];
    u8 pad78[8];
    Vec4f pos[16];
    Vec4f v[16][2];
} Str_b100_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Spark_b100_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v;
} Dot_b100_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f posB;
    s32 m[6];
    u8 pad48[8];
    Vec4f jp[6];
    Vec4f mid;
    Vec4f dir;
    Trail_b100_01E00080 trail[8];
    s32 n1;
    u8 pad1DD4[0xC];
    Ring_b100_01E00080 ring[8];
    Str_b100_01E00080 str[32];
    Spark_b100_01E00080 sp[16];
    Dot_b100_01E00080 dot[64];
} Scene_b100_01E00080;

static s32 func_01E00080_b100(s32 arg0, s32 code) {
    Scene_b100_01E00080 *g = (Scene_b100_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6590(s32, s32, void *);
    extern s32 func_001F6EF0(void);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 p;
    s32 q;
    s32 n;
    s32 x;
    s32 a;
    u8 alpha;
    f32 e;
    f32 e1;
    f32 e2;
    f32 f;
    f32 r;
    f32 s;
    f32 s1;
    f32 s2;
    f32 s3;
    f32 s4;
    f32 s5;
    f32 h;
    f32 h1;
    f32 h2;
    f32 h3;
    f32 h4;
    f32 h5;
    f32 z0;
    f32 z1;
    f32 z2;
    f32 z3;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b100_01E00080 spr __attribute__((aligned(8)));
    f32 depth;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xBF60);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F53C0(1, g->unitB, &g->posB);
        g->m[0] = func_001F5560(g->unitA, 0xA, 1);
        g->m[1] = func_001F5560(g->unitA, 0x15, 0);
        g->m[2] = func_001F5560(g->unitA, 0x26, 0);
        g->m[3] = func_001F5560(g->unitA, 0x34, 0);
        g->m[4] = func_001F5560(g->unitA, 0x3D, 0);
        g->m[5] = func_001F5560(g->unitA, 0x46, 0);
        for (i = 0; i < 8; i++) {
            g->trail[i].on = 0;
        }
        g->n1 = 0;
        for (i = 0; i < 8; i++) {
            g->ring[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->str[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->sp[i].on = 0;
        }
        for (i = 0; i < 64; i++) {
            g->dot[i].on = 0;
        }
        func_001F6590(g->unitB, 2, 0);
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 6; i++) {
        func_001F5620(g->unitA, g->m[i], &g->jp[i]);
    }
    if (g->t == 0x1E) {
        func_00187B00(&g->mid, &g->jp[0], &g->jp[5]);
        { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }
        func_00187B18(&g->dir, &g->posB, &g->mid);
    }

    if (g->t > 0 && g->t < 0xFA) {
        n = g->t % 8;
        (void)n;
        g->trail[n].on = 1;
        g->trail[n].t = 0;
        for (j = 0; j < 6; j++) {
            g->trail[n].pos[j] = g->jp[j];
            for (l = 0; l < 8; l++) {
                g->trail[n].c[j][l] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->trail[n].v[j][l], 0.3f);
            }
        }
    }

    ((Spr_b100_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b100_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b100_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b100_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b100_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e = (f32)func_00101050(g->t, 0, 16) * (f32)func_00101050(0xFA - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 8; i++) {
        if (g->trail[i].on == 0) {
            continue;
        }
        alpha = (u32)(e * (80.0f * func_0020B550((g->trail[i].t << 15) >> 3)));
        spr.c.r = 0x80;
        spr.c.g = 0x30;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 5.0f * (0.2f + 0.8f * g->trail[i].t / 8.0f);
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
        h1 = g->trail[i].t / 8.0f;
        s1 = 0.9f + 0.1f * g->trail[i].t / 8.0f;
        h1 = -4.0f + 10.0f * h1;
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 8; k++) {
                ((Uv_b100_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->trail[i].c[j][k]][0];
                ((Uv_b100_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->trail[i].c[j][k]][2];
                ((Uv_b100_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->trail[i].c[j][k]][1];
                ((Uv_b100_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->trail[i].c[j][k]][3];
                v.x = g->trail[i].v[j][k].x * s1;
                v.y = h1 + g->trail[i].v[j][k].y;
                v.z = g->trail[i].v[j][k].z * s1;
                func_00187B00(&v, &v, &g->trail[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->trail[i].t++;
        if (g->trail[i].t > 8) {
            g->trail[i].on = 0;
        }
    }

    if (g->t % 4 == 0 && g->t > 0 && g->t < 0xFA) {
        n = g->n1;
        (void)n;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (j = 0; j < 6; j++) {
            g->ring[n].pos[j] = g->jp[j];
            func_00101080(&g->ring[n].v[j], 0.3f);
        }
        g->n1++;
        if (g->n1 >= 8) {
            g->n1 = 0;
        }
    }

    ((Spr_b100_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b100_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b100_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b100_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b100_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b100_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b100_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b100_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b100_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e1 = (f32)func_00101050(g->t, 0, 16) * (f32)func_00101050(0xFA - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 8; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(e1 * (128.0f * func_0020B550((g->ring[i].t << 15) / 24)));
        spr.c.r = 0xFF;
        spr.c.g = 0x18;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.5f + 0.5f * g->ring[i].t / 24.0f);
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
        h2 = g->ring[i].t / 24.0f;
        s2 = 0.5f + 0.5f * g->ring[i].t / 24.0f;
        h2 = 6.0f * h2;
        for (j = 0; j < 6; j++) {
            v.x = g->ring[i].v[j].x * s2;
            v.y = h2 + g->ring[i].v[j].y;
            v.z = g->ring[i].v[j].z * s2;
            func_00187B00(&v, &v, &g->ring[i].pos[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 24) {
            g->ring[i].on = 0;
        }
    }

    if (g->t > 0x1E && g->t < 0x3E) {
        n = g->t % 32;
        (void)n;
        g->str[n].on = 1;
        g->str[n].t = 0;
        for (p = 0; p < 16; p++) {
            g->str[n].son[p] = 0;
        }
    }

    ((Spr_b100_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b100_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b100_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b100_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b100_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e = func_00101050(0xC2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 32; i++) {
        if (g->str[i].on == 0) {
            continue;
        }
        n = g->str[i].t % 16;
        g->str[i].son[n] = 1;
        g->str[i].st[n] = 0;
        func_00187B48(&g->str[i].pos[n], &g->dir, 2.0f * g->str[i].t / 164.0f);
        func_00187B00(&g->str[i].pos[n], &g->str[i].pos[n], &g->mid);
        for (k = 0; k < 2; k++) {
            g->str[i].c[n][k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->str[i].v[n][k], 0.3f);
        }
        e1 = (f32)func_00101050(g->str[i].t, 0, 16) * (f32)func_00101050(0xA4 - g->str[i].t, 0, 16) / 256.0f;
        for (j = 0; j < 16; j++) {
            if (g->str[i].son[j] == 0) {
                continue;
            }
            alpha = (u32)(e * (e1 * (80.0f * func_0020B550((g->str[i].st[j] << 15) >> 4))));
            spr.c.r = 0x80;
            spr.c.g = 0x30;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 4.0f * (0.2f + 0.8f * g->str[i].st[j] / 16.0f);
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
            h3 = g->str[i].st[j] / 16.0f;
            s3 = 0.9f + 0.1f * g->str[i].st[j] / 16.0f;
            h3 = -8.0f + 10.0f * h3;
            for (k = 0; k < 2; k++) {
                ((Uv_b100_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->str[i].c[j][k]][0];
                ((Uv_b100_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->str[i].c[j][k]][2];
                ((Uv_b100_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->str[i].c[j][k]][1];
                ((Uv_b100_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->str[i].c[j][k]][3];
                v.x = g->str[i].v[j][k].x * s3;
                v.y = h3 + g->str[i].v[j][k].y;
                v.z = g->str[i].v[j][k].z * s3;
                func_00187B00(&v, &v, &g->str[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->str[i].st[j]++;
            if (g->str[i].st[j] > 16) {
                g->str[i].son[j] = 0;
            }
        }
        g->str[i].t++;
        if (g->str[i].t > 164) {
            g->str[i].on = 0;
        }
    }

    if (g->t > 0x74 && g->t < 0xFA) {
        n = g->t % 16;
        (void)n;
        g->sp[n].on = 1;
        g->sp[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->sp[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->sp[n].v[j], 1.3f);
        }
    }

    ((Spr_b100_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b100_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b100_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b100_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b100_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e = (f32)func_00101050(g->t - 0x74, 0, 32) * (f32)func_00101050(0xFA - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->sp[i].on == 0) {
            continue;
        }
        alpha = (u32)(e * (128.0f * func_0020B550((g->sp[i].t << 15) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x30;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.2f + 0.8f * g->sp[i].t / 16.0f);
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
        h4 = g->sp[i].t / 16.0f;
        s4 = 0.9f + 0.1f * g->sp[i].t / 16.0f;
        h4 = -25.0f + 50.0f * h4;
        for (j = 0; j < 32; j++) {
            ((Uv_b100_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->sp[i].c[j]][0];
            ((Uv_b100_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->sp[i].c[j]][2];
            ((Uv_b100_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->sp[i].c[j]][1];
            ((Uv_b100_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->sp[i].c[j]][3];
            v.x = g->sp[i].v[j].x * s4;
            v.y = h4 + g->sp[i].v[j].y;
            v.z = g->sp[i].v[j].z * s4;
            func_00187B00(&v, &v, &g->posB);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->sp[i].t++;
        if (g->sp[i].t > 16) {
            g->sp[i].on = 0;
        }
    }

    if (g->t > 0x74 && g->t < 0xFA) {
        n = g->t % 64;
        (void)n;
        g->dot[n].on = 1;
        g->dot[n].t = 0;
        func_00101080(&g->dot[n].v, 1.5f);
    }

    ((Spr_b100_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b100_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b100_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b100_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b100_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b100_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b100_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b100_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b100_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    e = (f32)func_00101050(g->t - 0x74, 0, 32) * (f32)func_00101050(0xFA - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 64; i++) {
        if (g->dot[i].on == 0) {
            continue;
        }
        alpha = (u32)(e * (128.0f * func_0020B550((g->dot[i].t << 15) >> 6)));
        spr.c.r = 0xFF;
        spr.c.g = 0x18;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 20.0f * (0.5f + 0.5f * g->dot[i].t / 64.0f);
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
        h5 = -25.0f + 50.0f * (g->dot[i].t / 64.0f);
        s5 = 0.5f + 0.5f * g->dot[i].t / 64.0f;
        v.x = g->dot[i].v.x * s5;
        v.y = h5 + g->dot[i].v.y;
        v.z = g->dot[i].v.z * s5;
        func_00187B00(&v, &v, &g->posB);
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        g->dot[i].t++;
        if (g->dot[i].t > 64) {
            g->dot[i].on = 0;
        }
    }

    if (func_001F6EF0() == 1) {
        if (g->t > 0x84) {
            a = func_00101050(g->t - 0x84, 0, 32) << 7 >> 5;
            col[2] = 0x80;
            col[1] = 0x80;
            col[0] = 0x80;
            col[3] = a;
            func_001F6590(g->unitB, 2, col);
        }
    }

    if (g->t == 0x6A) {
        ret = 1;
    } else {
        if (g->t > 0x74 && g->t < 0xFA) {
            ret = 6;
        }
        if (g->t == 0xFA) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xFB) {
        ret = 8;
    }
    return ret;
}
