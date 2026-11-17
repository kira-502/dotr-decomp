#include "common.h"

/* shape b271:01E00080 (b271), 2126 insns, 1 copy: b271 scene manager (b141:01E00080's family, written from the asm):
   setup clears the 0xE8F0 scene, takes both units, five textures, eight joints and the target; else on 1..0x167
   spawns 32-slot 2x20-mote bursts and 20-slot 2x8-sprite twins at random joints of two limbs, on 0x69..0x167 64-slot
   20-sprite clouds and 40-slot 8-sprite puffs at the target, a fading screen tint, and from 0x68 a 289-frame render-
   to-texture flash; returns 1 / 6 / 2 / 8 at 0x5E / 0x69..0x167 / 0x168 / >0x190 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b271_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b271_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b271_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b271_01E00080;

typedef struct {
    Reg_b271_01E00080 a;
    Reg_b271_01E00080 b;
} Tx_b271_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b271_01E00080 c;
    Uv_b271_01E00080 uv0;
    Xyz_b271_01E00080 p0;
    Uv_b271_01E00080 uv1;
    Xyz_b271_01E00080 p1;
    u64 pad38;
    Tx_b271_01E00080 tx;
    u64 pad50;
} Spr_b271_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b271_01E00080 c;
    Xyz_b271_01E00080 p0;
    Xyz_b271_01E00080 p1;
    u64 tail;
} Rect_b271_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][20];
    Vec4f pos[2];
    Vec4f v[2][20];
} Burst_b271_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Twin_b271_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][20];
    u8 pad1C[4];
    Vec4f pos[1];
    Vec4f v[1][20];
} Cloud_b271_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][8];
    Vec4f pos[1];
    Vec4f v[1][8];
} Puff_b271_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    s32 jn[8];
    u8 pad44[0xC];
    Vec4f jp[8];
    Vec4f tgt;
    Burst_b271_01E00080 burst[32];
    Twin_b271_01E00080 twin[20];
    Cloud_b271_01E00080 cloud[64];
    Puff_b271_01E00080 puff[40];
    u8 on;
    u8 padE8E1[3];
    s32 tt;
    u8 padE8E8[8];
} Scene_b271_01E00080;

static s32 func_01E00080_b271(s32 arg0, s32 code) {
    Scene_b271_01E00080 *g = (Scene_b271_01E00080 *)arg0;
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
    extern void func_00205CA0(void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern void func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    f32 f;
    f32 r;
    f32 h;
    f32 s;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Vec4f v;
    Spr_b271_01E00080 spr __attribute__((aligned(8)));
    Rect_b271_01E00080 rc __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xE8F0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        g->jn[0] = func_001F5560(g->unitA, 0x2E, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x31, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x35, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x38, 0);
        g->jn[4] = func_001F5560(g->unitA, 0x3C, 0);
        g->jn[5] = func_001F5560(g->unitA, 0x3F, 0);
        g->jn[6] = func_001F5560(g->unitA, 0x43, 0);
        g->jn[7] = func_001F5560(g->unitA, 0x46, 0);
        func_001F53C0(1, g->unitB, &g->tgt);
        for (j = 0; j < 32; j++) {
            g->burst[j].on = 0;
        }
        for (j = 0; j < 20; j++) {
            g->twin[j].on = 0;
        }
        for (j = 0; j < 64; j++) {
            g->cloud[j].on = 0;
        }
        for (j = 0; j < 40; j++) {
            g->puff[j].on = 0;
        }
        g->on = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (j = 0; j < 8; j++) {
        func_001F5620(g->unitA, g->jn[j], &g->jp[j]);
    }

    if (g->t > 0 && g->t < 0x168) {
        n = g->t % 32;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        for (j = 0; j < 2; j++) {
            g->burst[n].pos[j] = g->jp[j * 4 + (func_0019A5C8() >> 23) % 4];
            for (i = 0; i < 20; i++) {
                g->burst[n].c[j][i] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->burst[n].v[j][i], 1.0f);
            }
        }
    }

    ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x168 - g->t, 0, 32) / 1024.0f;
    for (j = 0; j < 32; j++) {
        if (g->burst[j].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->burst[j].t << 15) >> 5)));
        r = 0.5f * (0.5f + 0.5f * (32 - g->burst[j].t) / 32.0f);
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
        s = 0.1f + 0.9f * func_00100D50(g->burst[j].t, 32, 1);
        h = -0.5f + 5.0f * g->burst[j].t / 32.0f;
        for (i = 0; i < 2; i++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x64;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 20; k++) {
                x = g->burst[j].c[i][k] % 4 * 32;
                y = (g->burst[j].c[i][k] >> 2) * 32;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->burst[j].v[i][k], s);
                func_00187B00(&v, &v, &g->burst[j].pos[i]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[j].t++;
        if (g->burst[j].t > 32) {
            g->burst[j].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x168) {
        n = g->t % 20;
        (void)n;
        g->twin[n].on = 1;
        g->twin[n].t = 0;
        for (j = 0; j < 2; j++) {
            g->twin[n].pos[j] = g->jp[j * 4 + (func_0019A5C8() >> 23) % 4];
            for (k = 0; k < 8; k++) {
                g->twin[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->twin[n].v[j][k], 0.3f);
            }
        }
    }

    ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x168 - g->t, 0, 32) / 1024.0f;
    for (j = 0; j < 20; j++) {
        if (g->twin[j].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(f * (100.0f * func_0020B550((g->twin[j].t << 15) / 20)));
        r = 3.0f * (0.5f + 0.5f * (20 - g->twin[j].t) / 20.0f);
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
        s = 0.1f + 0.9f * func_00100D50(g->twin[j].t, 20, 1);
        h = 0.0f + 0.0f * g->twin[j].t / 20.0f;
        for (i = 0; i < 2; i++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x64;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 8; k++) {
                x = g->twin[j].c[i][k] % 4 * 32;
                y = (g->twin[j].c[i][k] >> 2) * 32;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->twin[j].v[i][k], s);
                func_00187B00(&v, &v, &g->twin[j].pos[i]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->twin[j].t++;
        if (g->twin[j].t > 20) {
            g->twin[j].on = 0;
        }
    }

    if (g->t > 0x68 && g->t <= 0x167) {
        n = g->t % 64;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->cloud[n].pos[j] = g->tgt;
            for (k = 0; k < 20; k++) {
                g->cloud[n].c[j][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->cloud[n].v[j][k], 4.5f);
            }
        }
    }

    ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x68, 0, 32) * (f32)func_00101050(0x168 - g->t, 0, 32) / 1024.0f;
    for (j = 0; j < 64; j++) {
        if (g->cloud[j].on == 0) {
            continue;
        }
        alpha = (u32)(f * (255.0f * func_0020B550((g->cloud[j].t << 15) >> 6)));
        r = 5.0f * (0.5f + 0.5f * (64 - g->cloud[j].t) / 64.0f);
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
        s = 0.1f + 0.9f * func_00100D50(g->cloud[j].t, 64, 1);
        h = -30.0f + 60.0f * g->cloud[j].t / 64.0f;
        for (i = 0; i < 1; i++) {
            spr.c.r = 0xFF;
            spr.c.g = 0xB4;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 20; k++) {
                x = g->cloud[j].c[i][k] % 4 * 32;
                y = (g->cloud[j].c[i][k] >> 2) * 32;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->cloud[j].v[i][k], s);
                func_00187B00(&v, &v, &g->cloud[j].pos[i]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->cloud[j].t++;
        if (g->cloud[j].t > 64) {
            g->cloud[j].on = 0;
        }
    }

    if (g->t > 0x68 && g->t <= 0x167) {
        n = g->t % 40;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->puff[n].pos[j] = g->tgt;
            for (k = 0; k < 8; k++) {
                g->puff[n].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[j][k], 2.5f);
            }
        }
    }

    ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x68, 0, 32) * (f32)func_00101050(0x168 - g->t, 0, 32) / 1024.0f;
    for (j = 0; j < 40; j++) {
        if (g->puff[j].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(f * (200.0f * func_0020B550((g->puff[j].t << 15) / 40)));
        r = 15.0f * (0.5f + 0.5f * (40 - g->puff[j].t) / 40.0f);
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
        s = 0.1f + 0.9f * func_00100D50(g->puff[j].t, 40, 1);
        h = -30.0f + 60.0f * g->puff[j].t / 40.0f;
        for (i = 0; i < 1; i++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x64;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 8; k++) {
                x = g->puff[j].c[i][k] % 4 * 32;
                y = (g->puff[j].c[i][k] >> 2) * 32;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->puff[j].v[i][k], s);
                func_00187B00(&v, &v, &g->puff[j].pos[i]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[j].t++;
        if (g->puff[j].t > 40) {
            g->puff[j].on = 0;
        }
    }

    f = (f32)func_00101050(g->t - 0x68, 0, 32) * (f32)func_00101050(0x188 - g->t, 0, 32) / 1024.0f;
    if (f > 0.0f) {
        ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = 5 << 4;
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = 3 << 4;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = 0x27B << 4;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = 0x1BD << 4;
        alpha = (u32)(80.0f * f);
        (void)alpha;
        spr.c.r = 0xA8;
        spr.c.g = 0x8A;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        spr.p0.x = 0x6C00;
        spr.p0.y = 0x7200;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x9400;
        spr.p1.y = 0x8E00;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, ot, 0);
    }

    if (g->t == 0x68) {
        g->on = 1;
        g->tt = 0;
    }
    if (g->on == 1) {
        buf = func_00207F60();
        ((Spr_b271_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b271_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b271_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b271_01E00080 *)(s32)&spr)->pad4 = 0;
        func_00208460();
        func_00208800(func_00209E50(), 0, &spr.tx.a, &spr.tx.b);
        func_00208460();
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        ((Spr_b271_01E00080 *)(s32)&spr)->flags |= 0x800;
        alpha = (u32)(128.0f * func_00101020((f32)g->tt, 32.0f) * func_00100FF0((f32)g->tt, 288.0f, 256.0f));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        ((Rect_b271_01E00080 *)(s32)&rc)->flags = 6;
        ((Rect_b271_01E00080 *)(s32)&rc)->size = 3;
        ((Rect_b271_01E00080 *)(s32)&rc)->regs = 0x441;
        ((Rect_b271_01E00080 *)(s32)&rc)->pad4 = 0;
        func_002086D0(&rc, func_00208D00(3));
        alpha = (u32)(128.0f * func_00101020((f32)g->tt, 32.0f) * func_00100FF0((f32)g->tt, 288.0f, 256.0f));
        rc.c.r = 0x80;
        rc.c.g = 0;
        rc.c.b = 0;
        rc.c.a = alpha;
        rc.c.q = 1.0f;
        rc.p0.x = 0x6C00;
        rc.p0.y = 0x7200;
        rc.p0.z = 0xFFFFF8;
        rc.p0.f = 0;
        rc.p1.x = 0x9400;
        rc.p1.y = 0x8E00;
        rc.p1.z = 0xFFFFF8;
        rc.p1.f = 0;
        func_002075F0(&rc, 0, 0);
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80 - alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b271_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b271_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        func_00207FD0(buf, ot, 0xFFFFFF);
        g->tt++;
        if (g->tt > 0x120) {
            g->on = 0;
        }
    }

    if (g->t == 0x5E) {
        ret = 1;
    } else {
        if (g->t > 0x68 && g->t <= 0x167) {
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
