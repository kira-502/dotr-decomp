#include "common.h"

/* shape b014:01E00080 (b014), 2105 insns, 1 copy: b014 scene manager (b512:01E00080's family, written from the asm):
   setup clears the 0x9360 scene, takes both units, three textures, the target and joints 0x25 / 0x26; else lines
   eight points along the joint pair and projects the target to the screen (clamped to 640x448), on 1..0x9F spawns a
   16-slot 8x4 rising spark puff along the line, at 0x76 a 21-frame flickering flash, on 0x77..0x89 an 8-slot 12-quad
   wave ring, on 0x87..0x92 a 20-slot two-layer 8x4 burst, at 0x92 a 33-frame render-to-texture screen ripple of 8
   rings of 8 triangles around the target (D_28B960 table); returns 1 / 6 / 3 / 8 at 0x88 / 0x93..0xB1 / 0xB2 / >0xE8
   */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b014_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b014_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b014_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b014_01E00080;

typedef struct {
    Reg_b014_01E00080 a;
    Reg_b014_01E00080 b;
} Tx_b014_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b014_01E00080 c;
    Uv_b014_01E00080 uv0;
    Xyz_b014_01E00080 p0;
    Uv_b014_01E00080 uv1;
    Xyz_b014_01E00080 p1;
    u64 pad38;
    Tx_b014_01E00080 tx;
    u64 pad50;
} Spr_b014_01E00080;

typedef struct {
    Rgbaq_b014_01E00080 c;
    Uv_b014_01E00080 uv;
    Xyz_b014_01E00080 p;
} Tv_b014_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b014_01E00080 v[3];
    u64 pad58;
    Tx_b014_01E00080 tx;
    u64 pad70;
} Tri_b014_01E00080;

typedef struct {
    Rgbaq_b014_01E00080 c;
    f32 s, t;
    Xyz_b014_01E00080 p;
} Sv_b014_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Sv_b014_01E00080 v[4];
    u8 tail[0x20];
} Quad_b014_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b014_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8][4];
    u8 pad28[8];
    Vec4f pos[8];
    Vec4f v[8][4];
} Spark_b014_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[12];
    u8 pad14[0xC];
    Vec4f v[12];
} Wave_b014_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8][4];
    u8 pad28[8];
    Vec4f pos[8];
    Vec4f v[8][4];
    u8 c2[8][4];
    Vec4f v2[8][4];
} Burst_b014_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    Vec4f scr;
    s32 jn[2];
    u8 pad48[8];
    Vec4f jp[2];
    Vec4f line[8];
    Spark_b014_01E00080 spark[16];
    u8 on2;
    u8 pad2BF1[3];
    s32 t2;
    u8 pad2BF8[8];
    Wave_b014_01E00080 wave[8];
    s32 nb;
    u8 pad3304[0xC];
    Burst_b014_01E00080 burst[20];
    u8 on3;
    u8 pad9351[3];
    s32 t3;
    u8 pad9358[8];
} Scene_b014_01E00080;

static s32 func_01E00080_b014(s32 arg0, s32 code) {
    Scene_b014_01E00080 *g = (Scene_b014_01E00080 *)arg0;
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
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
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
    s32 cg;
    s32 cb;
    f32 f;
    f32 h;
    f32 r;
    f32 s;
    f32 z;
    f32 w;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[4];
    Mtx_b014_01E00080 m4;
    Vec4f v;
    Spr_b014_01E00080 spr __attribute__((aligned(8)));
    Tri_b014_01E00080 tri __attribute__((aligned(8)));
    Quad_b014_01E00080 pk __attribute__((aligned(8)));
    Xyz_b014_01E00080 scr;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9360);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x25, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x26, 0);
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->t2 = 0;
        for (i = 0; i < 8; i++) {
            g->wave[i].on = 0;
        }
        g->nb = 0;
        for (i = 0; i < 20; i++) {
            g->burst[i].on = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_00187B18(&v, &g->jp[1], &g->jp[0]);
    for (i = 0; i < 8; i++) {
        func_00187B48(&g->line[i], &v, (f32)i / 7.0f);
        func_00187B00(&g->line[i], &g->line[i], &g->jp[0]);
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &scr, &depth);
    g->scr.x = (scr.x >> 4) - 0x6C0;
    g->scr.y = (scr.y >> 4) - 0x720;
    g->scr.z = scr.z;
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
    if (g->t > 0 && g->t < 0xA0) {
        n = g->t;
        n %= 16;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (i = 0; i < 8; i++) {
            g->spark[n].pos[i] = g->line[i];
            for (j = 0; j < 4; j++) {
                g->spark[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[n].v[i][j], 0.6f);
            }
        }
    }

    ((Spr_b014_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b014_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b014_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b014_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b014_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = func_00101050(g->t, 0, 32);
    h = f * func_00101050(0xA0 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        s = func_0020B480((g->spark[i].t << 14) >> 4);
        alpha = (u32)(55.0f * s * h);
        (void)alpha;
        cg = (s32)(75.0f * s);
        cb = (s32)(33.0f * s);
        spr.c.r = 0xFF;
        spr.c.g = cg;
        spr.c.b = cb;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.5f + 0.5f * (16 - g->spark[i].t) / 16.0f;
        r = 3.5f * r;
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
        u0 = (f32)g->spark[i].t / 16.0f;
        z = 0.1f + 0.9f * g->spark[i].t / 16.0f;
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 4; k++) {
                x = g->spark[i].c[j][k] % 4 * 32;
                y = (g->spark[i].c[j][k] >> 2) * 32;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                v.x = g->spark[i].v[j][k].x * z;
                v.y = 15.0f * u0 + g->spark[i].v[j][k].y * z;
                v.z = g->spark[i].v[j][k].z * z;
                func_00187B00(&v, &v, &g->spark[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 16) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x76) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Spr_b014_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b014_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b014_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b014_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b014_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        f = func_00101020((f32)g->t2, 4.0f);
        alpha = (u32)(164.0f * ((0.8f + 0.2f * (g->t2 % 2)) * (f * func_00100FF0((f32)g->t2, 20.0f, 16.0f))));
        spr.c.r = 0xFF;
        spr.c.g = 0xE6;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 50.0f;
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
        ((Uv_b014_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b014_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b014_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b014_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        v = g->line[4];
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        g->t2++;
        if (g->t2 > 20) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x76 && g->t < 0x8A) {
        n = g->t;
        n %= 8;
        g->wave[n].on = 1;
        g->wave[n].t = 0;
        for (j = 0; j < 12; j++) {
            g->wave[n].c[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->wave[n].v[j], 2.5f);
        }
    }

    ((Quad_b014_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b014_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b014_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b014_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, 5);
    f = func_00101050(g->t - 0x76, 0, 4);
    h = f * func_00101050(0x8A - g->t, 0, 4) / 16.0f;
    for (i = 0; i < 8; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        alpha = (u32)(h * (f32)((8 - g->wave[i].t) * 80 >> 3));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0xE6;
        pk.v[0].c.b = 0xC8;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        func_0020EB40(m);
        v = g->line[4];
        func_0020C940(m2, NULL, NULL, &v);
        func_0020BC00(m, m2);
        s = -1.5f * func_00100D50(g->wave[i].t, 8, 1);
        for (j = 0; j < 12; j++) {
            func_00100E40(&m4, &g->wave[i].v[j]);
            func_00100E00(&m4, (i << 16 >> 3) + (j << 16) / 12, 2);
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
            func_00187B00(&out[0], &cn[0], &g->wave[i].v[j]);
            func_00187B00(&out[1], &cn[1], (void *)&g->wave[i].v[j]);
            func_00187B48(&v, &g->wave[i].v[j], s);
            func_00187B00(&out[2], (void *)&out[0], (void *)&v);
            func_00187B00(&out[3], &out[1], (void *)&v);
            x = g->wave[i].c[j] % 4 * 32;
            y = (g->wave[i].c[j] >> 2) * 32;
            u0 = x / 128.0f;
            u1 = (32.0f + x) / 128.0f;
            w0 = y / 64.0f;
            w1 = (32.0f + y) / 64.0f;
            pk.v[0].s = u0;
            pk.v[0].t = w0;
            pk.v[1].s = u1;
            pk.v[1].t = w0;
            pk.v[2].s = u0;
            pk.v[2].t = w1;
            pk.v[3].s = u1;
            pk.v[3].t = w1;
            if (func_002058D0(out, D_0030FF00, m, &pk, &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 8) {
            g->wave[i].on = 0;
        }
    }

    if (g->t > 0x86 && g->t < 0x93) {
        n = g->nb;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        for (i = 0; i < 8; i++) {
            g->burst[n].pos[i] = g->line[i];
            for (k = 0; k < 4; k++) {
                g->burst[n].c[i][k] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[n].v[i][k], 1.3f);
            }
            for (k = 0; k < 4; k++) {
                g->burst[n].c2[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst[n].v2[i][k], 1.0f);
            }
        }
        g->nb++;
        if (g->nb >= 20) {
            g->nb = 0;
        }
    }

    ((Spr_b014_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b014_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b014_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b014_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b014_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 20; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        alpha = (u32)(80.0f * func_0020B480((g->burst[i].t << 14) >> 5));
        cg = 0x80;
        cb = 0x3C;
        spr.c.r = 0xC8;
        spr.c.g = cg;
        spr.c.b = cb;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.5f * (0.5f + 0.5f * g->burst[i].t / 32.0f);
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
        s = 0.3f + 0.7f * func_00100D50(g->burst[i].t, 32, 1);
        z = 10.0f * g->burst[i].t / 32.0f;
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 4; k++) {
                x = g->burst[i].c[j][k] % 4 * 32;
                y = (g->burst[i].c[j][k] >> 2) * 32;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->burst[i].v[j][k], s);
                v.y += z;
                func_00187B00(&v, &v, &g->burst[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        alpha = (u32)(30.0f * func_0020B480((g->burst[i].t << 14) >> 5));
        cg = 0x42;
        cb = 0x19;
        spr.c.r = 0xE6;
        spr.c.g = cg;
        spr.c.b = cb;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 14.5f * (0.5f + 0.5f * g->burst[i].t / 32.0f);
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
        s = 0.3f + 0.7f * func_00100D50(g->burst[i].t, 32, 1);
        z = 10.0f * g->burst[i].t / 32.0f;
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 4; k++) {
                x = g->burst[i].c2[j][k] % 4 * 32;
                y = (g->burst[i].c2[j][k] >> 2) * 32;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b014_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->burst[i].v2[j][k], s);
                v.y += z;
                func_00187B00(&v, &v, &g->burst[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 32) {
            g->burst[i].on = 0;
        }
    }

    if (g->t == 0x92) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b014_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b014_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b014_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b014_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b014_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
        func_00208460();
        alpha = (32 - g->t3) * 64 >> 5;
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0xFF;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 8; i++) {
            s = 1.0f + 0.1f * (8 - i) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b014_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b014_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b014_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b014_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18(&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48(&out[0], &out[0], s);
                func_00187B48(&out[1], &out[1], s);
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
            g->on3 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0xE8 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x88) {
        ret = 1;
    } else {
        if (g->t > 0x92 && g->t < 0xB2) {
            ret = 6;
        }
        if (g->t == 0xB2) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0xE8) {
        ret = 8;
    }
    return ret;
}
