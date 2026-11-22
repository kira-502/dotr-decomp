#include "common.h"

/* shape b724:01E00080 (b724), 2283 insns, 1 copy: b724 scene manager (b451:01E00080's family, written from the asm):
   setup clears the 0xA750 scene, takes both units, two textures, the target and joint 0x28, builds a 17.5-radius
   32x17 cone grid; else from frame 0 a 200-frame render-to-texture vortex (fading flare, the grid twisted into a
   second grid drawn as triangle/quad strips), on 1..0x91 128-slot spinning 4-corner sprites at the joint, on
   0x91..0x9A 24-slot 32-mote waves, and at 0x9A a 32-frame burst of 128 ST-quad streaks, a flare and 64 motes;
   returns 1 / 2 / 8 at 0x90 / 0x9A / >0xBA */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b724_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b724_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b724_01E00080;

typedef struct {
    f32 s;
    f32 t;
} St_b724_01E00080;

typedef struct {
    Rgbaq_b724_01E00080 c;
    Uv_b724_01E00080 uv;
    Xyz_b724_01E00080 p;
} Tv_b724_01E00080;

typedef struct {
    Rgbaq_b724_01E00080 c;
    union {
        Uv_b724_01E00080 uv;
        St_b724_01E00080 st;
    } uv;
    Xyz_b724_01E00080 p;
} Qv_b724_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b724_01E00080;

typedef struct {
    Reg_b724_01E00080 a;
    Reg_b724_01E00080 b;
} Tx_b724_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b724_01E00080 c;
    Uv_b724_01E00080 uv0;
    Xyz_b724_01E00080 p0;
    Uv_b724_01E00080 uv1;
    Xyz_b724_01E00080 p1;
    u64 pad38;
    Tx_b724_01E00080 tx;
    u64 pad50;
} Spr_b724_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b724_01E00080 v[3];
    u64 pad58;
    Tx_b724_01E00080 tx;
    u64 pad70;
} Tri_b724_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Qv_b724_01E00080 v[4];
    u64 pad70;
    Tx_b724_01E00080 tx;
    u64 pad88;
} Quad_b724_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b724_01E00080 c;
    struct {
        Uv_b724_01E00080 uv;
        Xyz_b724_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Spr4_b724_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b724_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1];
    u8 pad9[3];
    f32 sc[1];
    s32 ang[1];
    u8 pad14[0xC];
    Vec4f p;
    Vec4f v[1];
} Part_b724_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f p[1];
    Vec4f v[1][32];
} Wave_b724_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f posA;
    Vec4f tgt;
    s32 m0;
    u8 pad44[0xC];
    Vec4f pos0;
    Vec4f pos1;
    u8 burst;
    u8 pad71[3];
    s32 bt;
    u8 pad78[8];
    Vec4f grid0[32][17];
    Vec4f grid1[32][17];
    Part_b724_01E00080 part[128];
    Wave_b724_01E00080 wave[24];
    u8 on2;
    u8 pad9A81[3];
    s32 t2;
    u8 c2[128];
    u8 pad9B08[8];
    Vec4f v2[128];
    u8 c3[64];
    Vec4f v3[64];
} Scene_b724_01E00080;

static s32 func_01E00080_b724(s32 arg0, s32 code) {
    Scene_b724_01E00080 *g = (Scene_b724_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F57B0(s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6970(f32);
    extern void func_00205CA0(void *);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
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
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 c;
    s32 x;
    s32 y;
    s32 n;
    s32 a;
    u8 alpha;
    s32 ot2;
    f32 r;
    f32 h;
    f32 s;
    f32 f;
    f32 x1;
    f32 y1;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f p[4];
    Mtx_b724_01E00080 m4;
    Vec4f v;
    Spr_b724_01E00080 spr __attribute__((aligned(8)));
    Tri_b724_01E00080 tri __attribute__((aligned(8)));
    Quad_b724_01E00080 quad __attribute__((aligned(8)));
    Spr4_b724_01E00080 spr2 __attribute__((aligned(8)));
    Rgbaq_b724_01E00080 cc __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA750);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->m0 = func_001F5560(g->unitA, 0x28, 1);
        g->burst = 0;
        for (k = 0; k < 32; k++) {
            r = 17.5f * (32 - k) / 32.0f;
            for (c = 0; c < 17; c++) {
                g->grid0[k][c].x = r * func_0020B550(c * 0x10000 >> 4);
                g->grid0[k][c].y = r * func_0020B480(c * 0x10000 >> 4);
                g->grid0[k][c].z = 0.0f;
                g->grid0[k][c].w = 1.0f;
            }
        }
        for (j = 0; j < 128; j++) {
            g->part[j].on = 0;
        }
        return 0;
    }
    func_001F57B0(1);
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    func_001F5620(g->unitA, g->m0, &g->pos0);
    if (g->t == 0x9A) {
        g->pos1 = g->pos0;
    }
    if (g->t == 0) {
        g->burst = 1;
        g->bt = 0;
    }
    if (g->burst == 1) {
        ((Spr_b724_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b724_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b724_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b724_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b724_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 0);
        x = 0;
        ((Uv_b724_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b724_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b724_01E00080 *)(s32)&spr.uv1)->u = 0x200;
        ((Uv_b724_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 35.0f;
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        h = func_00101020((f32)g->bt, 32.0f);
        h = h * func_00100FF0((f32)g->bt, 200.0f, 168.0f);
        alpha = (u32)(255.0f * h);
        (void)alpha;
        spr.c.r = 0x80;
        spr.c.g = 0x94;
        spr.c.b = 0x9E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        v = g->posA;
        func_00187B60(m2, m3, &v);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Tri_b724_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b724_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b724_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b724_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Quad_b724_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b724_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b724_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b724_01E00080 *)(s32)&quad)->pad4 = 0;
        ot2 = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
        quad.tx.a = tri.tx.a;
        quad.tx.b = tri.tx.b;
        func_00208460();
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        ((Tri_b724_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&quad, func_00208D00(0));
        func_00208CB0(&quad, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b724_01E00080 *)(s32)&quad)->flags |= 0x800;
        alpha = (u32)(128.0f * h);
        (void)alpha;
        tri.v[0].c.r = 0x8A;
        tri.v[0].c.g = 0x94;
        tri.v[0].c.b = 0x94;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        cc = tri.v[0].c;
        quad.v[0].c = cc;
        quad.v[1].c = cc;
        quad.v[2].c = cc;
        quad.v[3].c = cc;
        for (y = 0; y < 32; y++) {
            r = 17.5f * (32 - y) / 32.0f;
            f = (f32)(y + 1) / 32.0f;
            for (k = 0; k < 17; k++) {
                h = 1.0f + f * (0.05f * func_0020B480((u16)(g->bt * 0x83F + ((y * 0x20000 >> 5) + (k * 0x20000 >> 4)))));
                c = (u16)(s32)((f32)(k * 0x10000 >> 4) + f * (364.0f * func_0020B480((u16)((y * 0x10000 >> 5) + g->bt * 0x457))));
                g->grid1[y][k].x = r * h * func_0020B550(c);
                g->grid1[y][k].y = r * h * func_0020B480(c);
                g->grid1[y][k].z = 0.0f;
                g->grid1[y][k].w = 1.0f;
            }
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (j = 0; j < 32; j++) {
            if (j == 31) {
                for (a = 0; a < 16; a++) {
                    if (func_00100B00(&v, &g->grid1[j][a], &g->grid1[j][a + 1], m, &tri, &depth) == 1) {
                        func_00100C60(&tri.v[0].uv, &tri.v[0].p, 0, 0);
                        func_00100C60(&tri.v[1].uv, &tri.v[1].p, 0, 0);
                        func_00100C60(&tri.v[2].uv, &tri.v[2].p, 0, 0);
                        if (func_00100B00(&v, &g->grid0[j][a], &g->grid0[j][a + 1], m, &tri, &depth) == 1) {
                            tri.v[0].p.z = 0xFFFFF8;
                            tri.v[1].p.z = tri.v[0].p.z;
                            tri.v[2].p.z = tri.v[0].p.z;
                            func_002075F0(&tri, 0, 0);
                        }
                    }
                }
            } else {
                for (a = 0; a < 16; a++) {
                    if (func_00100BA0(&g->grid1[j][a], &g->grid1[j][a + 1], &g->grid1[j + 1][a],
                                      &g->grid1[j + 1][a + 1], m, &quad, &depth) == 1) {
                        func_00100C60(&quad.v[0].uv, &quad.v[0].p, 0, 0);
                        func_00100C60(&quad.v[1].uv, &quad.v[1].p, 0, 0);
                        func_00100C60(&quad.v[2].uv, &quad.v[2].p, 0, 0);
                        func_00100C60(&quad.v[3].uv, &quad.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid0[j][a], &g->grid0[j][a + 1], &g->grid0[j + 1][a],
                                          &g->grid0[j + 1][a + 1], m, &quad, &depth) == 1) {
                            quad.v[0].p.z = 0xFFFFF8;
                            quad.v[1].p.z = quad.v[0].p.z;
                            quad.v[2].p.z = quad.v[0].p.z;
                            quad.v[3].p.z = quad.v[0].p.z;
                            func_002075F0(&quad, 0, 0);
                        }
                    }
                }
            }
        }
        func_00207FD0(ot2, ot, 0);
        g->bt++;
        if (g->bt > 0xC8) {
            g->burst = 0;
        }
    }

    if (g->t > 0 && g->t < 0x92) {
        c = g->t % 128;
        (void)c;
        g->part[c].on = 1;
        g->part[c].t = 0;
        g->part[c].p = g->pos0;
        for (y = 0; y < 1; y++) {
            g->part[c].c[y] = (func_0019A5C8() >> 23) % 4;
            g->part[c].sc[y] = 0.1f + 0.9f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->part[c].ang[y] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->part[c].v[y], 1.0f);
        }
    }

    ((Spr4_b724_01E00080 *)(s32)&spr2)->flags = 0x24;
    ((Spr4_b724_01E00080 *)(s32)&spr2)->size = 9;
    ((Spr4_b724_01E00080 *)(s32)&spr2)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr4_b724_01E00080 *)(s32)&spr2)->pad4 = 0;
    ((Spr4_b724_01E00080 *)(s32)&spr2)->flags |= 0x800;
    func_00208700(&spr2, g->tex[0], 1);
    func_002086D0(&spr2, func_00208D00(1));
    func_00208CB0(&spr2, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 128; j++) {
        if (g->part[j].on == 0) {
            continue;
        }
        alpha = (u32)(188.0f * func_00101020((f32)g->part[j].t, 12.0f) * func_00100FF0((f32)g->part[j].t, 128.0f, 115.0f));
        spr2.c.r = 0x80;
        spr2.c.g = 0x94;
        spr2.c.b = 0x9E;
        spr2.c.a = alpha;
        spr2.c.q = 1.0f;
        k = func_00101050(g->part[j].t, 0, 0x80);
        f = k / 128.0f;
        s = 40.0f * f;
        for (k = 0; k < 1; k++) {
            h = 5.0f * (0.4f + 0.6f * g->part[j].t / 128.0f) * g->part[j].sc[k];
            a = (g->part[j].ang[k] + g->part[j].t * 0x15B3) & 0xFFFF;
            x1 = h * (0.9f + 0.1f * func_0020B550(a));
            y1 = h * (0.9f + 0.1f * func_0020B480(a));
            cn[0].x = x1;
            cn[0].y = x1;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = -x1;
            cn[1].y = y1;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = y1;
            cn[2].y = -x1;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = -y1;
            cn[3].y = -y1;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(&cn[1], m3, &cn[1]);
            func_001878E0(&cn[2], m3, &cn[2]);
            func_001878E0(&cn[3], m3, &cn[3]);
            c = g->part[j].c[k];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[0].uv)->u = x << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[0].uv)->v = y << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[1].uv)->u = (x + 32) << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[1].uv)->v = y << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[2].uv)->u = x << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[2].uv)->v = (y + 32) << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[3].uv)->u = (x + 32) << 4;
            ((Uv_b724_01E00080 *)(s32)&spr2.v[3].uv)->v = (y + 32) << 4;
            func_00187B48(&v, &g->part[j].v[k], f);
            v.y += s;
            func_00187B00(&v, &v, &g->part[j].p);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            func_00187B00(&p[2], &cn[2], (void *)&v);
            func_00187B00(&p[3], &cn[3], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr2, &depth) == 1) {
                func_002075F0(&spr2, ot, (u32)depth);
            }
        }
        g->part[j].t++;
        if (g->part[j].t >= 0x80) {
            g->part[j].on = 0;
        }
    }

    if (g->t > 0x90 && g->t < 0x9B) {
        n = g->t % 24;
        (void)n;
        g->wave[n].on = 1;
        g->wave[n].t = 0;
        for (k = 0; k < 1; k++) {
            g->wave[n].p[k] = g->pos0;
            for (j = 0; j < 32; j++) {
                g->wave[n].c[k][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->wave[n].v[k][j], 0.5f);
                g->wave[n].v[k][j].z = 5.0f * (g->obj * func_001A6970(g->wave[n].v[k][j].z));
            }
        }
    }

    ((Spr_b724_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b724_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b724_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b724_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b724_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (c = 0; c < 24; c++) {
        if (g->wave[c].on == 0) {
            continue;
        }
        alpha = (u32)(96.0f * func_0020B480((g->wave[c].t << 14) / 24));
        spr.c.r = 0x80;
        spr.c.g = 0x94;
        spr.c.b = 0x9E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.5f + 0.5f * g->wave[c].t / 24.0f);
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
        h = 0.9f + 0.1f * g->wave[c].t / 24.0f;
        s = 0.5f + 0.5f * g->wave[c].t / 24.0f;
        for (n = 0; n < 1; n++) {
            for (i = 0; i < 32; i++) {
                v.x = g->wave[c].v[n][i].x * s;
                v.y = g->wave[c].v[n][i].y * s;
                v.z = g->wave[c].v[n][i].z * h;
                func_00187B00(&v, &v, &g->wave[c].p[n]);
                func_00187B00(&p[0], &cn[0], &v);
                func_00187B00(&p[1], &cn[1], (void *)&v);
                x = g->wave[c].c[n][i] % 4 * 32;
                y = (g->wave[c].c[n][i] >> 2) * 32;
                ((Uv_b724_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b724_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b724_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b724_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->wave[c].t++;
        if (g->wave[c].t > 24) {
            g->wave[c].on = 0;
        }
    }

    if (g->t == 0x9A) {
        g->on2 = 1;
        g->t2 = 0;
        for (j = 0; j < 128; j++) {
            g->c2[j] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->v2[j], 1.5f);
        }
        for (i = 0; i < 64; i++) {
            g->c3[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->v3[i], 0.8f);
        }
    }
    if (g->on2 == 1) {
        ((Quad_b724_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b724_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b724_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b724_01E00080 *)(s32)&quad)->pad4 = 0;
        func_002086D0(&quad, func_00208D00(1));
        func_00208700(&quad, g->tex[1], 1);
        func_00208CB0(&quad, 5);
        alpha = (u32)(100.0f * func_00100FF0((f32)g->t2, 32.0f, 16.0f));
        quad.v[0].c.r = 0xFF;
        quad.v[0].c.g = 0x78;
        quad.v[0].c.b = 0x72;
        quad.v[0].c.a = alpha;
        quad.v[0].c.q = 1.0f;
        quad.v[1].c = quad.v[0].c;
        quad.v[2].c.r = 0xFF;
        quad.v[2].c.g = 0x78;
        quad.v[2].c.b = 0x72;
        quad.v[2].c.a = 0;
        quad.v[2].c.q = 1.0f;
        quad.v[3].c = quad.v[2].c;
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &g->pos1);
        s = 0.5f + 0.5f * func_00100D50(g->t2, 32, 1);
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        for (i = 0; i < 128; i++) {
            func_00100E40(&m4, &g->v2[i]);
            func_00100E00(&m4, (i << 16) >> 7, 2);
            cn[0].x = 0.0f;
            cn[0].y = 1.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = -1.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m4, &cn[0]);
            func_001878E0(&cn[1], &m4, &cn[1]);
            func_00187B00(&p[0], &cn[0], &g->v2[i]);
            func_00187B00(&p[1], &cn[1], (void *)&g->v2[i]);
            func_00187B48((void *)&v, &g->v2[i], -2.0f);
            func_00187B00(&p[2], (void *)&p[0], (void *)&v);
            func_00187B00(&p[3], &p[1], (void *)&v);
            x = g->c2[i] % 4 * 32;
            y = (g->c2[i] >> 2) * 32;
            u0 = x / 128.0f;
            u1 = (32.0f + x) / 128.0f;
            w0 = y / 64.0f;
            w1 = (32.0f + y) / 64.0f;
            quad.v[0].uv.st.s = u0;
            quad.v[0].uv.st.t = w0;
            quad.v[1].uv.st.s = u1;
            quad.v[1].uv.st.t = w0;
            quad.v[2].uv.st.s = u0;
            quad.v[2].uv.st.t = w1;
            quad.v[3].uv.st.s = u1;
            quad.v[3].uv.st.t = w1;
            if (func_002058D0(p, D_0030FF00, m, &quad, &depth) == 1) {
                quad.v[0].p.z = 0xFFFFF8;
                quad.v[1].p.z = quad.v[0].p.z;
                quad.v[2].p.z = quad.v[0].p.z;
                quad.v[3].p.z = quad.v[0].p.z;
                func_002075F0(&quad, ot, 0);
            }
        }
        ((Spr_b724_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b724_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b724_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b724_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b724_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        alpha = (u32)(48.0f * func_00100FF0((f32)g->t2, 32.0f, 16.0f));
        spr.c.r = 0xEB;
        spr.c.g = 0xDC;
        spr.c.b = 0xB4;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 96;
        y = 0;
        ((Uv_b724_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b724_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b724_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b724_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_00187B60(m2, m2, &g->pos1);
        func_0020BC00(m, m2);
        r = 50.0f * (0.5f + 0.5f * func_00100D50(g->t2, 32, 1));
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
        ((Spr_b724_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b724_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b724_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b724_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b724_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        alpha = (u32)(116.0f * func_00100FF0((f32)g->t2, 32.0f, 16.0f));
        spr.c.r = 0x78;
        spr.c.g = 0xAA;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 9.0f * (0.2f + 0.8f * g->t2 / 32.0f);
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
        func_00187B60(m2, m2, &g->pos1);
        func_0020BC00(m, m2);
        s = 0.1f + 0.9 * func_00100D50(g->t2, 32, 1);
        for (a = 0; a < 64; a++) {
            x = g->c3[a] % 4 * 32;
            y = (g->c3[a] >> 2) * 32;
            ((Uv_b724_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b724_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b724_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b724_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v3[a], s);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 32) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x90) {
        ret = 1;
    } else if (g->t == 0x9A) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0xBA) {
        ret = 8;
    }
    return ret;
}
