#include "common.h"

/* shape b483:01E00080 (b483), 1288 insns, 1 copy: DRAFT 1282/1288 (10 words). b483 module main (b512:01E00080's
   author): code >= 0 clears the scene, takes both units, the texture and the target, builds a 32x17 cone grid; else
   slides unit A between them, from frame 180 runs a 189-frame burst (fading sprite, the grid twisted into a second grid
   drawn as triangle/quad strips), on 221..347 spawns 20-spark rings in 12 slots drawn as sprites, overlays the unit;
   returns 1 / 6 / 3 / 8 at 210 / 221..359 / 360 / 551. Left: the slot draw's 5.0f * (t / 12.0f) loads 5.0 into $f0
   before the divide (t in $f2, 12.0 in $f1) where the original loads it after (t in $f1, 12.0 and 5.0 in $f0) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b483_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b483_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b483_01E00080;

typedef struct {
    Rgbaq_b483_01E00080 c;
    Uv_b483_01E00080 uv;
    Xyz_b483_01E00080 p;
} Tv_b483_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b483_01E00080;

typedef struct {
    Reg_b483_01E00080 a;
    Reg_b483_01E00080 b;
} Tx_b483_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b483_01E00080 c;
    Uv_b483_01E00080 uv0;
    Xyz_b483_01E00080 p0;
    Uv_b483_01E00080 uv1;
    Xyz_b483_01E00080 p1;
    u64 pad38;
    Tx_b483_01E00080 tx;
    u64 pad50;
} Spr_b483_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b483_01E00080 v[3];
    u64 pad58;
    Tx_b483_01E00080 tx;
    u64 pad70;
} Tri_b483_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b483_01E00080 v[4];
    u64 pad70;
    Tx_b483_01E00080 tx;
    u64 pad88;
} Quad_b483_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[20];
    s32 ang[20];
    f32 sc[20];
    u8 padBC[4];
    Vec4f v[20];
} Slot_b483_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex;
    u8 pad14[0xC];
    Vec4f posA;
    Vec4f posB;
    Vec4f dir;
    Slot_b483_01E00080 slot[12];
    u8 burst;
    u8 pad1851[3];
    s32 bt;
    u8 pad1858[8];
    Vec4f grid0[32][17];
    Vec4f grid1[32][17];
} Scene_b483_01E00080;

static s32 func_01E00080_b483(s32 arg0, s32 code) {
    Scene_b483_01E00080 *g = (Scene_b483_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5F00(s32, void *);
    extern void func_001F63F0(s32, s32, void *);
    extern void func_001F7060(s32, s32, void *, void *);
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
    extern void func_00187B48(void *, void *, f32);
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
    extern u32 func_001A23B0(f32);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 ot2;
    s32 i;
    s32 j;
    s32 c;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    f32 r;
    f32 h;
    f32 k;
    f32 a;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p0;
    Vec4f p1;
    Vec4f v;
    Vec4f w;
    Spr_b483_01E00080 spr __attribute__((aligned(8)));
    Tri_b483_01E00080 tri __attribute__((aligned(8)));
    Quad_b483_01E00080 quad __attribute__((aligned(8)));
    Rgbaq_b483_01E00080 cc __attribute__((aligned(8)));
    f32 depth __attribute__((aligned(4)));
    u8 col[4] __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x5C60);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex = func_00202BF0(5, 0);
        func_001F53C0(1, g->unitA, &g->posA);
        func_001F53C0(1, g->unitB, &g->posB);
        func_001F5F90(g->unitA, &v);
        func_00187B18(&g->dir, &v, &g->posA);
        for (i = 0; i < 12; i++) {
            g->slot[i].on = 0;
        }
        g->burst = 0;
        for (i = 0; i < 32; i++) {
            r = 37.5f * (32 - i) / 32.0f;
            for (j = 0; j < 17; j++) {
                g->grid0[i][j].x = r * func_0020B550(j * 0x10000 >> 4);
                g->grid0[i][j].y = r * func_0020B480(j * 0x10000 >> 4);
                g->grid0[i][j].z = 0.0f;
                g->grid0[i][j].w = 1.0f;
            }
        }
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        return 0;
    }
    func_00205CA0(m3);
    a = func_00101050(g->t - 0x20, 0, 0x76) / 118.0f;
    ang = (s32)(32768.0f * (a * (1.0f - func_00101050(g->t - 0x1A2, 0, 0x84) / 132.0f)));
    ang &= 0xFFFF;
    r = -0.5f * (func_0020B480(ang) - 1.0f);
    v.x = g->posA.x + r * (g->posB.x - g->posA.x);
    v.z = g->posA.z + r * (g->posB.z - g->posA.z);
    v.y = 50.0f;
    w = v;
    func_00187B00(&v, &v, &g->dir);
    v.y = 50.0f;
    func_001F5F00(g->unitA, &v);
    if (g->t == 0xB4) {
        g->burst = 1;
        g->bt = 0;
    }
    if (g->burst == 1) {
        ((Spr_b483_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b483_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b483_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b483_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b483_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex, 1);
        func_00208CB0(&spr, 0);
        x = 0;
        ((Uv_b483_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b483_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b483_01E00080 *)(s32)&spr.uv1)->u = 0x200;
        ((Uv_b483_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 75.0f;
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = -r;
        cn[1].y = -r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        h = func_00101020((f32)g->bt, 32.0f);
        h = h * func_00100FF0((f32)g->bt, 188.0f, 156.0f);
        alpha = func_001A23B0(255.0f * h);
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x94;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        v = w;
        v.y += 15.0f;
        func_00187B60(m2, m3, &v);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Tri_b483_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b483_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b483_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b483_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Quad_b483_01E00080 *)(s32)&quad)->flags = 0x34;
        ((Quad_b483_01E00080 *)(s32)&quad)->size = 0xC;
        ((Quad_b483_01E00080 *)(s32)&quad)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b483_01E00080 *)(s32)&quad)->pad4 = 0;
        ot2 = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
        quad.tx.a = tri.tx.a;
        quad.tx.b = tri.tx.b;
        func_00208460();
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        ((Tri_b483_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&quad, func_00208D00(0));
        func_00208CB0(&quad, ((u64)0x700 << 32) | 0xA0000A);
        ((Quad_b483_01E00080 *)(s32)&quad)->flags |= 0x800;
        alpha = func_001A23B0(128.0f * h);
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0xA4;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        cc = tri.v[0].c;
        quad.v[0].c = cc;
        quad.v[1].c = cc;
        quad.v[2].c = cc;
        quad.v[3].c = cc;
        for (i = 0; i < 32; i++) {
            r = 37.5f * (32 - i) / 32.0f;
            a = (f32)(i + 1) / 32.0f;
            for (j = 0; j < 17; j++) {
                h = 1.0f + a * (0.2f * func_0020B480((u16)(g->bt * 0x83F + ((i * 0x20000 >> 5) + (j * 0x20000 >> 4)))));
                ang = (u16)(s32)((f32)(j * 0x10000 >> 4) + a * (910.0f * func_0020B480((u16)((i * 0x10000 >> 5) + g->bt * 0x457))));
                g->grid1[i][j].x = r * h * func_0020B550(ang);
                g->grid1[i][j].y = r * h * func_0020B480(ang);
                g->grid1[i][j].z = 0.0f;
                g->grid1[i][j].w = 1.0f;
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
        if (g->bt > 0xBC) {
            g->burst = 0;
        }
    }
    c = g->t;
    if (c > 0xDC && c < 0x15C) {
        c = c % 12;
        g->slot[c].on = 1;
        g->slot[c].t = 0;
        for (i = 0; i < 20; i++) {
            g->slot[c].c[i] = (func_0019A5C8() >> 23) % 6;
            g->slot[c].ang[i] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->slot[c].sc[i] = 0.1f + 0.9f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->slot[c].v[i], 0.7f);
            g->slot[c].v[i].y *= 0.9f;
        }
    }
    ((Spr_b483_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b483_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b483_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b483_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b483_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex, 1);
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 12; i++) {
        if (g->slot[i].on == 0) {
            continue;
        }
        alpha = func_001A23B0(200.0f * func_0020B550((g->slot[i].t << 15) / 12));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        k = 5.0f * (g->slot[i].t / 12.0f);
        for (j = 0; j < 20; j++) {
            h = 3.0f * g->slot[i].sc[j];
            cn[0].x = h;
            cn[0].y = h;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = -h;
            cn[1].y = -h;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(&cn[1], m3, &cn[1]);
            h = func_0020B550((u16)(g->slot[i].ang[j] + g->slot[i].t * 0xDE));
            c = g->slot[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b483_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b483_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b483_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b483_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->slot[i].v[j], h);
            v.y = g->slot[i].v[j].y;
            v.x += w.x;
            v.y += 10.0f + g->posA.y + k;
            v.z += w.z;
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            if (func_00205630(&p0, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->slot[i].t++;
        if (g->slot[i].t > 12) {
            g->slot[i].on = 0;
        }
    }
    ((Spr_b483_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b483_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b483_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b483_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b483_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
    ot2 = func_00207F60();
    func_00208460();
    func_001F7060(g->unitA, 0, &spr.tx.a, &spr.tx.b);
    func_00208460();
    spr.c.r = 0x80;
    spr.c.g = 0x80;
    spr.c.b = 0x80;
    spr.c.a = 0x80;
    spr.c.q = 1.0f;
    x = 0;
    ((Uv_b483_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b483_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b483_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
    ((Uv_b483_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
    spr.p0.x = 0x6C00;
    spr.p0.y = 0x7200;
    spr.p0.z = 0xFFFFF8;
    spr.p0.f = 0;
    spr.p1.x = 0x9400;
    spr.p1.y = 0x8E00;
    spr.p1.z = 0xFFFFF8;
    spr.p1.f = 0;
    func_002075F0(&spr, 0, 0);
    func_00207FD0(ot2, ot, 0);
    if (g->t == 0x226) {
        func_001F63F0(g->unitA, 0, 0);
    }
    if (g->t == 0xD2) {
        ret = 1;
    } else {
        if (g->t > 0xDC && g->t < 0x168) {
            ret = 6;
        }
        if (g->t == 0x168) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x226) {
        ret = 8;
    }
    return ret;
}
