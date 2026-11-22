#include "common.h"

/* shape b614:01E00080 (b614), 1537 insns, 1 copy: b614 scene manager (b451:01E00080's form, three sparks per
   particle): setup clears the 0x8040 scene, takes both units, two textures, the target and joint 0xF, builds a 32x17
   cone grid; else follows unit A (raised by 2) and the joint, from frame 0 runs a 300-frame burst (fading sprite, the
   grid rippled per ring and per vertex into a second grid drawn as triangle/quad strips), on 134..269 spawns a three-
   spark particle per frame in 128 slots drawn as 4-corner sprites bobbing on a sine, each leaving a two-sprite wave
   (two textures) in 12 slots; returns 1 / 6 / 2 / 8 at 251 / 262..409 / 410 / 412; the wave header indexes g->nwave
   once directly */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b614_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b614_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b614_01E00080;

typedef struct {
    Rgbaq_b614_01E00080 c;
    Uv_b614_01E00080 uv;
    Xyz_b614_01E00080 p;
} Tv_b614_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b614_01E00080;

typedef struct {
    Reg_b614_01E00080 a;
    Reg_b614_01E00080 b;
} Tx_b614_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b614_01E00080 c;
    Uv_b614_01E00080 uv0;
    Xyz_b614_01E00080 p0;
    Uv_b614_01E00080 uv1;
    Xyz_b614_01E00080 p1;
    u64 pad38;
    Tx_b614_01E00080 tx;
    u64 pad50;
} Spr_b614_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b614_01E00080 v[3];
    u64 pad58;
    Tx_b614_01E00080 tx;
    u64 pad70;
} Tri_b614_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b614_01E00080 v[4];
    u64 pad70;
    Tx_b614_01E00080 tx;
    u64 pad88;
} Quad_b614_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b614_01E00080 c;
    struct {
        Uv_b614_01E00080 uv;
        Xyz_b614_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Spr4_b614_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3];
    u8 padB[1];
    f32 sc[3];
    s32 ang[3];
    u8 pad24[0xC];
    Vec4f p;
    Vec4f v[3];
} Part_b614_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3];
    u8 padB[1];
    f32 sc[3];
    u8 pad18[8];
    Vec4f p[3];
} Wave_b614_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex[2];
    u8 pad18[8];
    Vec4f posA;
    Vec4f tgt;
    s32 m0;
    u8 pad44[0xC];
    Vec4f pos0;
    u8 burst;
    u8 pad41[3];
    s32 bt;
    u8 pad48[8];
    Vec4f grid0[32][17];
    Vec4f grid1[32][17];
    Part_b614_01E00080 part[128];
    s32 nwave;
    u8 pad6C74[0xC];
    Wave_b614_01E00080 wave[12];
} Scene_b614_01E00080;

static s32 func_01E00080_b614(s32 arg0, s32 code) {
    Scene_b614_01E00080 *g = (Scene_b614_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, void *, s32);
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
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_00100C60(void *, void *, s32, s32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot __attribute__((aligned(8)));
    s32 i;
    s32 j;
    s32 c;
    s32 x;
    s32 y;
    s32 n;
    s32 a;
    u8 alpha;
    u8 alpha2;
    s32 ot2;
    f32 r;
    f32 h;
    f32 w;
    f32 s;
    f32 k;
    f32 x1;
    f32 y1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f p[4];
    Vec4f v;
    Vec4f save[3];
    Spr_b614_01E00080 spr __attribute__((aligned(8)));
    Spr4_b614_01E00080 spr2 __attribute__((aligned(8)));
    Tri_b614_01E00080 tri __attribute__((aligned(8)));
    Quad_b614_01E00080 quad __attribute__((aligned(8)));
    Rgbaq_b614_01E00080 cc __attribute__((aligned(8)));
    f32 depth __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x8040);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->m0 = func_001F5560(g->unitA, 0xF, 1);
        g->burst = 0;
        for (i = 0; i < 32; i++) {
            r = 12.5f * (32 - i) / 32.0f;
            for (j = 0; j < 17; j++) {
                g->grid0[i][j].x = r * func_0020B550(j * 0x10000 >> 4);
                g->grid0[i][j].y = r * func_0020B480(j * 0x10000 >> 4);
                g->grid0[i][j].z = 0.0f;
                g->grid0[i][j].w = 1.0f;
            }
        }
        for (i = 0; i < 128; i++) {
            g->part[i].on = 0;
        }
        g->nwave = 0;
        for (i = 0; i < 12; i++) {
            g->wave[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    g->posA.y += 2.0f;
    func_001F5620(g->unitA, g->m0, &g->pos0);
    if (g->t == 0) {
        g->burst = 1;
        g->bt = 0;
    }
    if (g->burst == 1) {
        ((Spr_b614_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b614_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b614_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b614_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b614_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 0);
        x = 0;
        ((Uv_b614_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b614_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b614_01E00080 *)(s32)&spr.uv1)->u = 0x200;
        ((Uv_b614_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 25.0f;
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        h = func_00101020((f32)g->bt, 48.0f);
        h = h * func_00100FF0((f32)g->bt, 300.0f, 252.0f);
        alpha = (u32)(255.0f * h);
        (void)alpha;
        spr.c.r = 0x80;
        spr.c.g = 0xF8;
        spr.c.b = 0x9E;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->posA);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Tri_b614_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b614_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b614_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b614_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Quad_b614_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b614_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b614_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b614_01E00080 *)(s32)&quad)->pad4 = 0;
        ot2 = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
        quad.tx.a = tri.tx.a;
        quad.tx.b = tri.tx.b;
        func_00208460();
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        ((Tri_b614_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&quad, func_00208D00(0));
        func_00208CB0(&quad, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b614_01E00080 *)(s32)&quad)->flags |= 0x800;
        alpha = (u32)(128.0f * h);
        (void)alpha;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x94;
        tri.v[0].c.b = 0x9E;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        cc = tri.v[0].c;
        quad.v[0].c = cc;
        quad.v[1].c = cc;
        quad.v[2].c = cc;
        quad.v[3].c = cc;
        for (j = 0; j < 32; j++) {
            x = j * 0x50000 >> 5;
            x = (x + g->bt * 0x8AE) & 0xFFFF;
            r = 12.5f * (32 - j) / 32.0f * (1.0f + 0.1f * func_0020B480(x));
            for (i = 0; i < 17; i++) {
                x = (g->bt * 0xD05 + ((j * 0x30000 >> 5) + (i * 0x20000 >> 4))) & 0xFFFF;
                h = 1.0f + 0.1f * func_0020B550(x);
                x = i * 0x10000 >> 4;
                g->grid1[j][i].x = r * h * func_0020B550(x);
                g->grid1[j][i].y = r * h * func_0020B480(x);
                g->grid1[j][i].z = 0.0f;
                g->grid1[j][i].w = 1.0f;
            }
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 32; i++) {
            if (i == 31) {
                for (j = 0; j < 16; j++) {
                    if (func_00100B00(&v, &g->grid1[i][j], &g->grid1[i][j + 1], m, &tri, &depth) == 1) {
                        func_00100C60(&tri.v[0].uv, &tri.v[0].p, 0, 0);
                        func_00100C60(&tri.v[1].uv, &tri.v[1].p, 0, 0);
                        func_00100C60(&tri.v[2].uv, &tri.v[2].p, 0, 0);
                        if (func_00100B00(&v, &g->grid0[i][j], &g->grid0[i][j + 1], m, &tri, &depth) == 1) {
                            tri.v[0].p.z = 0xFFFFF8;
                            tri.v[1].p.z = tri.v[0].p.z;
                            tri.v[2].p.z = tri.v[0].p.z;
                            func_002075F0(&tri, 0, 0);
                        }
                    }
                }
            } else {
                for (j = 0; j < 16; j++) {
                    if (func_00100BA0(&g->grid1[i][j], &g->grid1[i][j + 1], &g->grid1[i + 1][j], &g->grid1[i + 1][j + 1], m, &quad, &depth) == 1) {
                        func_00100C60(&quad.v[0].uv, &quad.v[0].p, 0, 0);
                        func_00100C60(&quad.v[1].uv, &quad.v[1].p, 0, 0);
                        func_00100C60(&quad.v[2].uv, &quad.v[2].p, 0, 0);
                        func_00100C60(&quad.v[3].uv, &quad.v[3].p, 0, 0);
                        if (func_00100BA0(&g->grid0[i][j], &g->grid0[i][j + 1], &g->grid0[i + 1][j], &g->grid0[i + 1][j + 1], m, &quad, &depth) == 1) {
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
        if (g->bt > 0x12C) {
            g->burst = 0;
        }
    }
    c = g->t;
    if (c > 0x85 && c < 0x10E) {
        c = c % 128;
        g->part[c].on = 1;
        g->part[c].t = 0;
        g->part[c].p = g->pos0;
        for (i = 0; i < 3; i++) {
            g->part[c].c[i] = (func_0019A5C8() >> 23) % 4;
            g->part[c].sc[i] = 0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->part[c].ang[i] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->part[c].v[i], 1.0f);
            func_00187B00(&g->part[c].v[i], &g->part[c].v[i], &g->tgt);
            func_00187B18(&g->part[c].v[i], &g->part[c].v[i], &g->part[c].p);
        }
    }
    ((Spr4_b614_01E00080 *)(s32)&spr2)->flags = 0x24;
    ((Spr4_b614_01E00080 *)(s32)&spr2)->size = 9;
    ((Spr4_b614_01E00080 *)(s32)&spr2)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr4_b614_01E00080 *)(s32)&spr2)->pad4 = 0;
    ((Spr4_b614_01E00080 *)(s32)&spr2)->flags |= 0x800;
    func_00208700(&spr2, g->tex[0], 1);
    func_002086D0(&spr2, func_00208D00(1));
    func_00208CB0(&spr2, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 128; i++) {
        if (g->part[i].on == 0) {
            continue;
        }
        alpha = (u32)(188.0f * func_00101020((f32)g->part[i].t, 12.0f));
        spr2.c.r = 0x80;
        spr2.c.g = 0xF8;
        spr2.c.b = 0xB2;
        spr2.c.a = alpha;
        spr2.c.q = 1.0f;
        k = func_00101050(g->part[i].t, 0, 0x80) / 128.0f;
        s = 0.2f + 0.8f * k;
        a = (s32)(32768.0f * k);
        a &= 0xFFFF;
        w = 60.0f * func_0020B550(a);
        for (j = 0; j < 3; j++) {
            h = 10.0f * (0.4f + 0.6f * g->part[i].t / 128.0f) * g->part[i].sc[j];
            a = (g->part[i].ang[j] + g->part[i].t * 0x15B3) & 0xFFFF;
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
            c = g->part[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[0].uv)->u = x << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[0].uv)->v = y << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[1].uv)->u = (x + 32) << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[1].uv)->v = y << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[2].uv)->u = x << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[2].uv)->v = (y + 32) << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[3].uv)->u = (x + 32) << 4;
            ((Uv_b614_01E00080 *)(s32)&spr2.v[3].uv)->v = (y + 32) << 4;
            v.x = g->part[i].v[j].x * s;
            v.y = w + g->part[i].v[j].y * s;
            v.z = g->part[i].v[j].z * k;
            func_00187B00(&v, &v, &g->part[i].p);
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            func_00187B00(&p[2], &cn[2], (void *)&v);
            func_00187B00(&p[3], &cn[3], (void *)&v);
            if (func_00205630(p, D_0030FF00, m, &spr2, &depth) == 1) {
                func_002075F0(&spr2, ot, (u32)depth);
            }
            save[j] = v;
        }
        g->part[i].t++;
        if (g->part[i].t >= 0x80) {
            g->part[i].on = 0;
            n = g->nwave;
            g->wave[g->nwave].on = 1;
            g->wave[n].t = 0;
            for (j = 0; j < 3; j++) {
                g->wave[n].c[j] = (func_0019A5C8() >> 23) % 4 + 4;
                g->wave[n].sc[j] = 0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
                g->wave[n].p[j] = save[j];
            }
            g->nwave++;
            if (g->nwave >= 12) {
                g->nwave = 0;
            }
        }
    }
    ((Spr_b614_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b614_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b614_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b614_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b614_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 12; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480((g->wave[i].t << 14) / 12));
        alpha2 = (u32)(80.0f * func_0020B480((g->wave[i].t << 14) / 12));
        h = 10.0f * g->wave[i].t / 12.0f;
        for (j = 0; j < 3; j++) {
            r = 24.0f * (0.5f + 0.5f * g->wave[i].t / 12.0f) * g->wave[i].sc[j];
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
            c = g->wave[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b614_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b614_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b614_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b614_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v = g->wave[i].p[j];
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            func_00208700(&spr, g->tex[0], 1);
            spr.c.r = 0x80;
            spr.c.g = 0xF8;
            spr.c.b = 0xB2;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            v.y += h;
            func_00187B00(&p[0], &cn[0], &v);
            func_00187B00(&p[1], &cn[1], (void *)&v);
            func_00208700(&spr, g->tex[1], 1);
            spr.c.r = 0x80;
            spr.c.g = 0xF8;
            spr.c.b = 0x94;
            spr.c.a = alpha2;
            spr.c.q = 1.0f;
            if (func_00205630(p, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 12) {
            g->wave[i].on = 0;
        }
    }
    if (g->t == 0xFB) {
        ret = 1;
    } else {
        if (g->t > 0x105 && g->t < 0x19A) {
            ret = 6;
        }
        if (g->t == 0x19A) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x19B) {
        ret = 8;
    }
    return ret;
}
