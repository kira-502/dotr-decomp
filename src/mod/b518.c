#include "common.h"

/* shape b518:01E00080 (b518), 4161 insns, 1 copy (-O3,p): b518 scene manager, b382:01E00080's relative with four
   joints: screen flash, target-copy rays, joint orbs, streaks, swirls, spinning rim quads, a burst sprite, a closing
   ray fan and two extra sprite sections on the second joint pair */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b518_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b518_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b518_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b518_01E00080;

typedef struct {
    Reg_b518_01E00080 a;
    Reg_b518_01E00080 b;
} Tx_b518_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b518_01E00080 c;
    Uv_b518_01E00080 uv0;
    Xyz_b518_01E00080 p0;
    Uv_b518_01E00080 uv1;
    Xyz_b518_01E00080 p1;
    u64 pad38;
    Tx_b518_01E00080 tx;
    u64 pad50;
} Spr_b518_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b518_01E00080 c;
    Xyz_b518_01E00080 p0;
    Xyz_b518_01E00080 p1;
    u64 tail;
} Rect_b518_01E00080;

typedef struct {
    Rgbaq_b518_01E00080 c;
    f32 s, t;
    Xyz_b518_01E00080 p;
} Tv_b518_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b518_01E00080 v[4];
    u8 tail[0x20];
} Quad_b518_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b518_01E00080 c;
        Uv_b518_01E00080 uv;
        Xyz_b518_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b518_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Flash_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f p[1];
    Vec4f v[1][32];
} Orb_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][8];
    Vec4f p[1];
    Vec4f v[1][8];
} Orb2_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][20];
    Vec4f p[2];
    Vec4f v[2][20];
} Leaf_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][6];
    u8 pad14[12];
    Vec4f p[2];
    Vec4f v[2][6];
} Puff_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[8][1];
    f32 sc[8][1];
    f32 w[8][1];
    u8 pad68[8];
    Vec4f p[1];
    Vec4f v[8][1];
} Streak_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[6][1];
    s32 ang[6][1];
    u8 pad38[8];
    Vec4f p[1];
    Vec4f v[6][1];
} Swirl_b518_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Rim_b518_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Mtx_b518_01E00080 mat;
} Spin_b518_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[2];
    u8 pad24[0xC];
    Vec4f jp[2];
    s32 jn2[2];
    u8 pad58[8];
    Vec4f jq[2];
    Vec4f tgt;
    Vec4f scrB;
    Vec4f pos;
    Vec4f scr;
    f32 lift;
    s32 z;
    Flash_b518_01E00080 flash[10];
    u8 padC8[8];
    Orb_b518_01E00080 orb[8];
    Streak_b518_01E00080 streak[48];
    Swirl_b518_01E00080 swirl[48];
    Rim_b518_01E00080 rim[17];
    Spin_b518_01E00080 spin[32];
    u8 fon[1];
    u8 pad7151[3];
    s32 ft[1];
    u8 pad7158[8];
    Orb2_b518_01E00080 orb2[8];
    u8 on;
    u8 pad7661[3];
    s32 t2;
    u8 pad7668[8];
    Leaf_b518_01E00080 leaf[28];
    Puff_b518_01E00080 puff[12];
} Scene_b518_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b518(s32 arg0, s32 code) {
    Scene_b518_01E00080 *g = (Scene_b518_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F6D00(s32);
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    u8 on;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    u8 a8;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 a;
    f32 u;
    f32 u5;
    f32 u1;
    f32 s0;
    f32 e;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f w;
    Rect_b518_01E00080 rc __attribute__((aligned(8)));
    Spr_b518_01E00080 spr __attribute__((aligned(8)));
    Tri_b518_01E00080 tri __attribute__((aligned(8)));
    Quad_b518_01E00080 pk __attribute__((aligned(8)));
    Xyz_b518_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD130);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x42, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x45, 0);
        g->jn2[0] = func_001F5560(g->unitA, 0x3F, 0);
        g->jn2[1] = func_001F5560(g->unitA, 0x40, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->lift = 1.5f * func_001F5860(g->unitA);
        for (i = 0; i < 10; i++) {
            g->flash[i].on = 0;
        }
        for (i = 0; i < 8; i++) {
            g->orb[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->streak[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->swirl[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            x = (i << 16) >> 4;
            s = func_0020B550(x);
            h = func_0020B480(x);
            g->rim[i].a.x = 30.0f * s;
            g->rim[i].a.y = 30.0f * h;
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 100.0f * s;
            g->rim[i].b.y = 100.0f * h;
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
            func_00187B00(&g->rim[i].mid, &g->rim[i].a, &g->rim[i].b);
            func_00187B48((void *)&g->rim[i].mid, &g->rim[i].mid, 0.5f);
        }
        for (i = 0; i < 32; i++) {
            g->spin[i].on = 0;
        }
        for (k = 0; k < 1; k++) {
            g->fon[k] = 0;
        }
        for (i = 0; i < 8; i++) {
            g->orb2[i].on = 0;
        }
        g->on = 0;
        for (i = 0; i < 28; i++) {
            g->leaf[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->puff[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn2[i], &g->jq[i]);
    }
    func_001F53C0(1, g->unitA, &g->pos);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
    g->scr.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr.z = func_0017B340(xyz.z);
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
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = -g->lift;
    v.w = 1.0f;
    func_001878E0(&v, m3, &v);
    func_00187B00(&v, &v, &g->pos);
    func_00205440(&v, m, &xyz, &depth);
    g->z = xyz.z;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
    g->scrB.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scrB.y = (s32)(xyz.y >> 4) - 0x720;
    g->scrB.z = func_0017B340(xyz.z);
    g->scrB.w = 1.0f;
    if (g->scrB.x < 0.0f) {
        g->scrB.x = 0.0f;
    }
    if (g->scrB.x > 640.0f) {
        g->scrB.x = 640.0f;
    }
    if (g->scrB.y < 0.0f) {
        g->scrB.y = 0.0f;
    }
    if (g->scrB.y > 448.0f) {
        g->scrB.y = 448.0f;
    }

    if (g->t == 0x19) {
        g->fon[0] = 1;
        g->ft[0] = 0;
    }
    ((Rect_b518_01E00080 *)(s32)&rc)->flags = 6;
    ((Rect_b518_01E00080 *)(s32)&rc)->size = 3;
    ((Rect_b518_01E00080 *)(s32)&rc)->regs = 0x441;
    ((Rect_b518_01E00080 *)(s32)&rc)->pad4 = 0;
    func_002086D0(&rc, func_00208D00(3));
    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    on = 0;
    for (i = 0; i < 1; i++) {
        if (g->fon[i] == 0) {
            continue;
        }
        if (on == 0) {
            on = 1;
            buf = func_00207F60();
            func_00208460();
            func_00208800(func_00209E50(), 0, &spr.tx.a, &spr.tx.b);
            func_00208460();
        }
        x = 16 - g->ft[i];
        f = x / 16.0f;
        if (i == 0) {
            a8 = (u32)(128.0f * f);
            rc.c.r = 0xFF;
            rc.c.g = 0x5A;
            rc.c.b = 0x1C;
            rc.c.a = a8;
            rc.c.q = 1.0f;
        }
        rc.p0.x = 0x6C00;
        rc.p0.y = 0x7200;
        rc.p0.z = 0xFFFFF8;
        rc.p0.f = 0;
        rc.p1.x = 0x9400;
        rc.p1.y = 0x8E00;
        rc.p1.z = 0xFFFFF8;
        rc.p1.f = 0;
        func_002075F0(&rc, 0, 0);
        a8 = 0x80 - a8;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = a8;
        spr.c.q = 1.0f;
        y = 0;
        ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = y;
        ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y;
        ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        g->ft[i]++;
        if (g->ft[i] > 16) {
            g->fon[i] = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0 && g->t < 0xDA) {
        n = g->t % 10;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
    }
    ((Tri_b518_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b518_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b518_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b518_01E00080 *)(s32)&tri)->pad4 = 0;
    ((Tri_b518_01E00080 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&tri, func_00208D00(1));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t, 0, 64) * (f32)func_00101050(0xDA - g->t, 0, 64) / 4096.0f;
    on = 0;
    for (i = 0; i < 10; i++) {
        if (g->flash[i].on == 0) {
            continue;
        }
        if (on == 0) {
            on = 1;
            buf = func_00207F60();
            func_00208460();
            func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
            func_00208460();
        }
        alpha = (u32)(f * (255.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 11)));
        tri.v[0].c.r = 0xFF;
        tri.v[0].c.g = 0xBC;
        tri.v[0].c.b = 0x30;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(f * (128.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 11)));
        tri.v[1].c.r = 0xFF;
        tri.v[1].c.g = 0x64;
        tri.v[1].c.b = 0;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 1.0f + (-0.1f + 0.2f * g->flash[i].t / 10.0f) + 0.1f / 10.0f;
        for (j = 0; j < 8; j++) {
            x = (s32)g->scr.x;
            y = (s32)g->scr.y;
            ((Uv_b518_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
            ((Uv_b518_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
            x = (s32)D_28B960[j].x;
            y = (s32)D_28B960[j].y;
            ((Uv_b518_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
            ((Uv_b518_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
            x = (s32)D_28B960[j + 1].x;
            y = (s32)D_28B960[j + 1].y;
            ((Uv_b518_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
            ((Uv_b518_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
            func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
            func_00187B18(&out[1], &D_28B960[j + 1], (void *)&g->scr);
            func_00187B48(&out[0], &out[0], r);
            func_00187B48(&out[1], &out[1], r);
            func_00187B00(&out[0], &out[0], &g->scr);
            func_00187B00(&out[1], &out[1], &g->scr);
            x = (s32)g->scr.x;
            y = (s32)g->scr.y;
            tri.v[0].p.x = (x + 0x6C0) << 4;
            tri.v[0].p.y = (y + 0x720) << 4;
            tri.v[0].p.z = g->z;
            tri.v[0].p.f = 0;
            x = (s32)out[0].x;
            y = (s32)out[0].y;
            tri.v[1].p.x = (x + 0x6C0) << 4;
            tri.v[1].p.y = (y + 0x720) << 4;
            tri.v[1].p.z = g->z;
            tri.v[1].p.f = 0;
            x = (s32)out[1].x;
            y = (s32)out[1].y;
            tri.v[2].p.x = (x + 0x6C0) << 4;
            tri.v[2].p.y = (y + 0x720) << 4;
            tri.v[2].p.z = g->z;
            tri.v[2].p.f = 0;
            func_002075F0(&tri, 0, 0);
        }
        g->flash[i].t++;
        if (g->flash[i].t > 10) {
            g->flash[i].on = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0 && g->t < 0x11) {
        n = g->t % 8;
        g->orb[n].on = 1;
        g->orb[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->orb[n].p[i] = g->jp[1];
            for (y = 0; y < 32; y++) {
                g->orb[n].c[i][y] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->orb[n].v[i][y], 0.7f);
                func_00187B00(&g->orb[n].v[i][y], &g->orb[n].v[i][y], &g->orb[n].p[i]);
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 8; i++) {
        if (g->orb[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        f = 1.0f;
        alpha = (u32)(f * (255.0f * func_0020B550((g->orb[i].t << 14) >> 3)));
        r = 0.2f + 0.8f * (8 - g->orb[i].t) / 8.0f;
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
        h = (f32)(8 - g->orb[i].t) / 8.0f;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (l = 0; l < 32; l++) {
                x = g->orb[i].c[j][l] % 4 * 32;
                y = (g->orb[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B18(&v, &g->orb[i].v[j][l], &g->jp[1]);
                func_00187B48(&v, &v, h);
                func_00187B00(&v, &v, &g->jp[1]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->orb[i].t++;
        if (g->orb[i].t > 8) {
            g->orb[i].on = 0;
        }
    }

    if (g->t > 0x2C && g->t < 0xDA) {
        n = g->t % 48;
        g->streak[n].on = 1;
        g->streak[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->streak[n].p[j] = g->jp[0];
            for (i = 0; i < 8; i++) {
                g->streak[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                g->streak[n].sc[i][j] = 0.5 + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
                func_00101080(&g->streak[n].v[i][j], 1.0f);
                h = func_001A6C60(func_001A6C48(g->streak[n].v[i][j].x, 2.0f) +
                                  func_001A6C48(g->streak[n].v[i][j].y, 2.0f));
                g->streak[n].w[i][j] = 0.8f + 0.2f * (func_001A6C60(2.0f * func_001A6C48(16.0f, 2.0f)) - h) /
                                                  func_001A6C60(2.0f * func_001A6C48(16.0f, 2.0f));
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    h = (f32)func_00101050(0xDA - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->streak[i].on == 0) {
            continue;
        }
        r = 18.0f * (0.3f + 0.7f * g->streak[i].t / 48.0f);
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
        a = 1.7f * g->streak[i].t / 48.0f;
        e = 0.1f + 0.9f * g->streak[i].t / 48.0f;
        for (l = 0; l < 1; l++) {
            func_00187B18(&w, &g->tgt, &g->streak[i].p[l]);
            func_00187B48(&w, &w, a);
            func_00187B00(&w, &w, &g->streak[i].p[l]);
            for (j = 0; j < 8; j++) {
                alpha = (u32)(g->streak[i].w[j][l] * (h * (128.0f * func_00101020((f32)g->streak[i].t, 1.0f) *
                                                            func_00100FF0((f32)g->streak[i].t, 48.0f, 32.0f))));
                spr.c.r = 0x80;
                spr.c.g = 0x30;
                spr.c.b = 0x1C;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                x = g->streak[i].c[j][l] % 4 * 32;
                y = (g->streak[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&out[0], &cn[0], g->streak[i].sc[j][l]);
                func_00187B48(&out[1], &cn[1], g->streak[i].sc[j][l]);
                func_00187B48(&v, &g->streak[i].v[j][l], e);
                func_00187B00(&v, &v, &w);
                func_00187B00(&out[0], &out[0], &v);
                func_00187B00(&out[1], &out[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->streak[i].t++;
        if (g->streak[i].t > 48) {
            g->streak[i].on = 0;
        }
    }

    if (g->t > 0x2C && g->t < 0xDA) {
        n = g->t % 48;
        g->swirl[n].on = 1;
        g->swirl[n].t = 0;
        for (j = 0; j < 1; j++) {
            g->swirl[n].p[j] = g->jp[0];
            for (x = 0; x < 6; x++) {
                g->swirl[n].c[x][j] = (func_0019A5C8() >> 23) % 4;
                g->swirl[n].ang[x][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
                func_00101080(&g->swirl[n].v[x][j], 1.0f);
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    a = (f32)func_00101050(0xDA - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->swirl[i].on == 0) {
            continue;
        }
        r = 12.0f * (0.3f + 0.7f * g->swirl[i].t / 48.0f);
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
        f = 1.7f * g->swirl[i].t / 48.0f;
        for (l = 0; l < 1; l++) {
            func_00187B18(&w, &g->tgt, &g->swirl[i].p[l]);
            func_00187B48(&w, &w, f);
            func_00187B00(&w, &w, &g->swirl[i].p[l]);
            alpha = (u32)(a * (100.0f * func_00101020((f32)g->swirl[i].t, 1.0f) *
                               func_00100FF0((f32)g->swirl[i].t, 48.0f, 32.0f)));
            spr.c.r = 0xFF;
            spr.c.g = 0x40;
            spr.c.b = 0x14;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (j = 0; j < 6; j++) {
                k = (g->swirl[i].ang[j][l] + (g->swirl[i].t << 15) / 48) & 0xFFFF;
                r = (0.1f + 0.9f * g->swirl[i].t / 48.0f) * func_0020B550(k);
                x = g->swirl[i].c[j][l] % 4 * 32;
                y = (g->swirl[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48((void *)&v, &g->swirl[i].v[j][l], r);
                func_00187B00(&v, &v, &w);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->swirl[i].t++;
        if (g->swirl[i].t > 48) {
            g->swirl[i].on = 0;
        }
    }

    if (g->t > 0x48 && g->t < 0xBA) {
        n = g->t % 32;
        g->spin[n].on = 1;
        g->spin[n].t = 0;
        func_0020BBB0(&g->spin[n].mat);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
    }

    ((Quad_b518_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b518_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b518_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b518_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 0);
    for (i = 0; i < 32; i++) {
        if (g->spin[i].on == 0) {
            continue;
        }
        r = func_0020B550((g->spin[i].t << 15) >> 5);
        pk.v[0].c.r = 0xE4;
        pk.v[0].c.g = 0x26;
        pk.v[0].c.b = 0x1A;
        pk.v[0].c.a = 0;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        alpha = (u32)(100.0f * r);
        pk.v[2].c.r = 0xFF;
        pk.v[2].c.g = 0xAE;
        pk.v[2].c.b = 0x5A;
        pk.v[2].c.a = alpha;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &g->tgt);
        func_0020BC00(m2, &g->spin[i].mat);
        k = i % 2 * 2 - 1;
        func_00100E00(m2, k * (g->spin[i].t * 0x37), 0);
        func_00100E00(m2, k * (g->spin[i].t * 0x4D), 1);
        func_00100E00(m2, k * (g->spin[i].t * 0x63), 2);
        s = 0.4f + 0.6f * g->spin[i].t / 32.0f;
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        u = -1.0f * (g->spin[i].t % 16) / 16.0f;
        u5 = 0.5f + u;
        u1 = 1.0f + u;
        for (j = 0; j < 16; j++) {
            s0 = 8.0f * j / 16.0f;
            h = 8.0f * (j + 1) / 16.0f;
            pk.v[0].s = s0;
            pk.v[0].t = u;
            pk.v[1].s = h;
            pk.v[1].t = u;
            pk.v[2].s = s0;
            pk.v[2].t = u5;
            pk.v[3].s = h;
            pk.v[3].t = u5;
            if (func_00100BA0(&g->rim[j].a, &g->rim[j + 1].a, &g->rim[j].mid, &g->rim[j + 1].mid, m, &pk, &depth) ==
                1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
            pk.v[0].s = s0;
            pk.v[0].t = u1;
            pk.v[1].s = h;
            pk.v[1].t = u1;
            pk.v[2].s = s0;
            pk.v[2].t = u5;
            pk.v[3].s = h;
            pk.v[3].t = u5;
            if (func_00100BA0(&g->rim[j].b, &g->rim[j + 1].b, &g->rim[j].mid, &g->rim[j + 1].mid, m, &pk, &depth) ==
                1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->spin[i].t++;
        if (g->spin[i].t > 32) {
            g->spin[i].on = 0;
        }
    }

    f = (f32)func_00101050(g->t - 0x48, 0, 32) * (f32)func_00101050(0xDA - g->t, 0, 32) / 1024.0f;
    if (f > 0.0f) {
        ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = 0x400;
        ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = 0x600;
        ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 60.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        alpha = (u32)(255.0f * f * (0.9f + 0.1f * (g->t % 2)));
        spr.c.r = 0xFF;
        spr.c.g = 0xA4;
        spr.c.b = 0x64;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->tgt);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
    }

    if (g->t == 0x87) {
        g->on = 1;
        g->t2 = 0;
    }
    if (g->on == 1) {
        ((Tri_b518_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b518_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b518_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b518_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b518_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        func_002087A0(&tri, 1);
        alpha = (u32)(64.0f * (func_00101020((f32)g->t2, 32.0f) * func_00100FF0((f32)g->t2, 115.0f, 83.0f)));
        tri.v[0].c.r = 0xBC;
        tri.v[0].c.g = 0x6C;
        tri.v[0].c.b = 0x44;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 1; i++) {
            f = 1.0f + 0.05f * (1 - i);
            for (j = 0; j < 8; j++) {
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
                ((Uv_b518_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b518_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b518_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scrB);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scrB);
                func_00187B48(&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
                func_00187B00(&out[0], &out[0], &g->scrB);
                func_00187B00(&out[1], &out[1], &g->scrB);
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
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
                func_002075F0(&tri, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 0x73) {
            g->on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x11) {
        n = g->t % 8;
        g->orb2[n].on = 1;
        g->orb2[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->orb2[n].p[i] = g->jp[1];
            for (y = 0; y < 8; y++) {
                g->orb2[n].c[i][y] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->orb2[n].v[i][y], 0.7f);
                func_00187B00(&g->orb2[n].v[i][y], &g->orb2[n].v[i][y], &g->orb2[n].p[i]);
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 8; i++) {
        if (g->orb2[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(0));
        f = 1.0f;
        alpha = (u32)(f * (128.0f * func_0020B550((g->orb2[i].t << 14) >> 3)));
        r = 10.0f * (0.5f + 0.5f * (8 - g->orb2[i].t) / 8.0f);
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
        s = (f32)(8 - g->orb2[i].t) / 8.0f;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0x64;
            spr.c.g = 0x64;
            spr.c.b = 0x64;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (l = 0; l < 8; l++) {
                x = g->orb2[i].c[j][l] % 4 * 32;
                y = (g->orb2[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B18(&v, &g->orb2[i].v[j][l], &g->jp[1]);
                func_00187B48(&v, &v, s);
                func_00187B00(&v, &v, &g->jp[1]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->orb2[i].t++;
        if (g->orb2[i].t > 8) {
            g->orb2[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0xDA) {
        n = g->t % 28;
        g->leaf[n].on = 1;
        g->leaf[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->leaf[n].p[i] = g->jq[i];
            for (y = 0; y < 20; y++) {
                g->leaf[n].c[i][y] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->leaf[n].v[i][y], 0.6f);
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0xDA - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 28; i++) {
        if (g->leaf[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->leaf[i].t << 15) / 28)));
        r = 0.8f * (0.5f + 0.5f * (28 - g->leaf[i].t) / 28.0f);
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
        s = 0.8f + 0.2f * func_00100D50(g->leaf[i].t, 28, 1);
        h = 8.0f * g->leaf[i].t / 28.0f;
        for (j = 0; j < 2; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (l = 0; l < 20; l++) {
                x = g->leaf[i].c[j][l] % 4 * 32;
                y = (g->leaf[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->leaf[i].v[j][l], s);
                func_00187B00(&v, &v, &g->leaf[i].p[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->leaf[i].t++;
        if (g->leaf[i].t > 28) {
            g->leaf[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0xDA) {
        n = g->t % 12;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->puff[n].p[i] = g->jq[i];
            for (y = 0; y < 6; y++) {
                g->puff[n].c[i][y] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[i][y], 0.5f);
            }
        }
    }

    ((Spr_b518_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b518_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b518_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b518_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b518_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0xDA - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 12; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->puff[i].t << 15) / 12)));
        r = 5.0f * (0.3f + 0.7f * (12 - g->puff[i].t) / 12.0f);
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
        s = 0.5f + 0.5f * g->puff[i].t / 12.0f;
        h = 6.0f * g->puff[i].t / 12.0f;
        for (j = 0; j < 2; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (l = 0; l < 6; l++) {
                x = g->puff[i].c[j][l] % 4 * 32;
                y = (g->puff[i].c[j][l] >> 2) * 32;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b518_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->puff[i].v[j][l], s);
                func_00187B00(&v, &v, &g->puff[i].p[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    spr.p0.z = 0xFFFFF8;
                    spr.p1.z = spr.p0.z;
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 12) {
            g->puff[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x11A - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x3E) {
        ret = 1;
    } else {
        if (g->t > 0x48 && g->t < 0xDA) {
            ret = 6;
        }
        if (g->t == 0xDA) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x11A) {
        ret = 8;
    }
    return ret;
}
