#include "common.h"

/* shape b769:01E00080 (b769), 3107 insns, 1 copy (-O3,p): scene effect: two screen flashes, a magenta flash fan, two-
   joint orb sparks, streaks and swirls, spinning rim rings and a glow */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b769_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b769_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b769_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b769_01E00080;

typedef struct {
    Reg_b769_01E00080 a;
    Reg_b769_01E00080 b;
} Tx_b769_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b769_01E00080 c;
    Uv_b769_01E00080 uv0;
    Xyz_b769_01E00080 p0;
    Uv_b769_01E00080 uv1;
    Xyz_b769_01E00080 p1;
    u64 pad38;
    Tx_b769_01E00080 tx;
    u64 pad50;
} Spr_b769_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b769_01E00080 c;
    Xyz_b769_01E00080 p0;
    Xyz_b769_01E00080 p1;
    u64 tail;
} Rect_b769_01E00080;

typedef struct {
    Rgbaq_b769_01E00080 c;
    f32 s, t;
    Xyz_b769_01E00080 p;
} Tv_b769_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b769_01E00080 v[4];
    u8 tail[0x20];
} Quad_b769_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b769_01E00080 c;
        Uv_b769_01E00080 uv;
        Xyz_b769_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b769_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b769_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Flash_b769_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][4];
    Vec4f p[2];
    Vec4f v[2][4];
} Orb_b769_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[8][2];
    f32 sc[8][2];
    f32 w[8][2];
    u8 pad88[8];
    Vec4f p[2];
    Vec4f v[8][2];
} Streak_b769_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[6][2];
    s32 ang[6][2];
    u8 pad68[8];
    Vec4f p[2];
    Vec4f v[6][2];
} Swirl_b769_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Rim_b769_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Mtx_b769_01E00080 mat;
} Spin_b769_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[2];
    u8 pad24[0xC];
    Vec4f jp[2];
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr;
    f32 lift;
    s32 z;
    Flash_b769_01E00080 flash[12];
    u8 padE8[8];
    Orb_b769_01E00080 orb[32];
    Streak_b769_01E00080 streak[48];
    Swirl_b769_01E00080 swirl[48];
    Rim_b769_01E00080 rim[17];
    Spin_b769_01E00080 spin[32];
    u8 fon[2];
    u8 padC022[2];
    s32 ft[2];
    u8 padC02C[4];
} Scene_b769_01E00080;


#pragma optimization_level 3

static s32 func_01E00080_b769(s32 arg0, s32 code) {
    Scene_b769_01E00080 *g = (Scene_b769_01E00080 *)arg0;
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
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f w;
    Rect_b769_01E00080 rc __attribute__((aligned(8)));
    Spr_b769_01E00080 spr __attribute__((aligned(8)));
    Tri_b769_01E00080 tri __attribute__((aligned(8)));
    Quad_b769_01E00080 pk __attribute__((aligned(8)));
    Xyz_b769_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC030);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x23, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x46, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->lift = 1.5f * func_001F5860(g->unitA);
        for (i = 0; i < 12; i++) {
            g->flash[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->orb[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->streak[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->swirl[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            s = func_0020B550((i << 16) >> 4);
            h = func_0020B480((i << 16) >> 4);
            g->rim[i].a.x = 30.0f * s;
            g->rim[i].a.y = 30.0f * h;
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 80.0f * s;
            g->rim[i].b.y = 80.0f * h;
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
            func_00187B00(&g->rim[i].mid, &g->rim[i].a, &g->rim[i].b);
            func_00187B48((void *)&g->rim[i].mid, &g->rim[i].mid, 0.5f);
        }
        for (i = 0; i < 32; i++) {
            g->spin[i].on = 0;
        }
        for (k = 0; k < 2; k++) {
            g->fon[k] = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
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

    if (g->t == 0x6E) {
        g->fon[0] = 1;
        g->ft[0] = 0;
    }
    if (g->t == 0x96) {
        g->fon[1] = 1;
        g->ft[1] = 0;
    }
    ((Rect_b769_01E00080 *)(s32)&rc)->flags = 6;
    ((Rect_b769_01E00080 *)(s32)&rc)->size = 3;
    ((Rect_b769_01E00080 *)(s32)&rc)->regs = 0x441;
    ((Rect_b769_01E00080 *)(s32)&rc)->pad4 = 0;
    func_002086D0(&rc, func_00208D00(3));
    ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
    ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
    on = 0;
    for (i = 0; i < 2; i++) {
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
        x = 32 - g->ft[i];
        f = x / 32.0f;
        if (i == 0) {
            a8 = (u32)(128.0f * f);
            rc.c.r = 0xFF;
            rc.c.g = 0x40;
            rc.c.b = 0x24;
            rc.c.a = a8;
            rc.c.q = 1.0f;
        } else {
            a8 = (u32)(128.0f * f);
            rc.c.r = 0x24;
            rc.c.g = 0x40;
            rc.c.b = 0xFF;
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
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = y;
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = y;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
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
        if (g->ft[i] > 32) {
            g->fon[i] = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0x1E && g->t < 0x1F2) {
        n = g->t % 12;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
    }
    ((Tri_b769_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b769_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b769_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b769_01E00080 *)(s32)&tri)->pad4 = 0;
    ((Tri_b769_01E00080 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&tri, func_00208D00(1));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t - 0x1E, 0, 64) * (f32)func_00101050(0x1F2 - g->t, 0, 64) / 4096.0f;
    a8 = 0;
    for (k = 0; k < 12; k++) {
        if (g->flash[k].on == 0) {
            continue;
        }
        if (a8 == 0) {
            a8 = 1;
            buf = func_00207F60();
            func_00208460();
            func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
            func_00208460();
        }
        alpha = (u32)(f * (255.0f * func_0020B550(((g->flash[k].t + 1) << 15) / 13)));
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x1C;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(f * (0.0f * func_0020B550(((g->flash[k].t + 1) << 15) / 13)));
        tri.v[1].c.r = 0x60;
        tri.v[1].c.g = 0x40;
        tri.v[1].c.b = 0x60;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 1.0f + (-0.3f + 0.6f * g->flash[k].t / 12.0f) + 0.3f / 12.0f;
        for (j = 0; j < 8; j++) {
            x = (s32)g->scr.x;
            y = (s32)g->scr.y;
            ((Uv_b769_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
            ((Uv_b769_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
            x = (s32)D_28B960[j].x;
            y = (s32)D_28B960[j].y;
            ((Uv_b769_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
            ((Uv_b769_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
            x = (s32)D_28B960[j + 1].x;
            y = (s32)D_28B960[j + 1].y;
            ((Uv_b769_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
            ((Uv_b769_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        g->flash[k].t++;
        if (g->flash[k].t > 12) {
            g->flash[k].on = 0;
        }
    }
    if (a8 == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0 && g->t < 0x1F2) {
        n = g->t % 32;
        g->orb[n].on = 1;
        g->orb[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->orb[n].p[i] = g->jp[i];
            for (y = 0; y < 4; y++) {
                g->orb[n].c[i][y] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->orb[n].v[i][y], 1.0f);
            }
        }
    }

    ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x1F2 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 32; i++) {
        if (g->orb[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (255.0f * func_0020B550((g->orb[i].t << 15) >> 5)));
        r = 3.0f * (0.2f + 0.8f * (32 - g->orb[i].t) / 32.0f);
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
        s = 0.1f + 0.9f * g->orb[i].t / 32.0f;
        for (j = 0; j < 2; j++) {
            if (j == 1) {
                spr.c.r = 0xFF;
                spr.c.g = 0x3C;
                spr.c.b = 0x18;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                spr.c.r = 0x18;
                spr.c.g = 0x3C;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            for (l = 0; l < 4; l++) {
                x = g->orb[i].c[j][l] % 4 * 32;
                y = (g->orb[i].c[j][l] >> 2) * 32;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->orb[i].v[j][l], s);
                func_00187B00(&v, &v, &g->orb[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->orb[i].t++;
        if (g->orb[i].t > 32) {
            g->orb[i].on = 0;
        }
    }

    if (g->t > 0xF3 && g->t < 0x1F2) {
        n = g->t % 48;
        g->streak[n].on = 1;
        g->streak[n].t = 0;
        for (j = 0; j < 2; j++) {
            g->streak[n].p[j] = g->jp[j];
            for (l = 0; l < 8; l++) {
                g->streak[n].c[l][j] = (func_0019A5C8() >> 23) % 8;
                g->streak[n].sc[l][j] = 0.5 + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
                func_00101080(&g->streak[n].v[l][j], 1.1f);
                h = func_001A6C60(func_001A6C48(g->streak[n].v[l][j].x, 2.0f) +
                                  func_001A6C48(g->streak[n].v[l][j].y, 2.0f));
                g->streak[n].w[l][j] = 0.8f + 0.2f * (func_001A6C60(2.0f * func_001A6C48(17.6f, 2.0f)) - h) /
                                                  func_001A6C60(2.0f * func_001A6C48(17.6f, 2.0f));
            }
        }
    }

    ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0x1F2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->streak[i].on == 0) {
            continue;
        }
        r = 13.0f * (0.5f + 0.5f * g->streak[i].t / 48.0f);
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
        h = 1.7f * g->streak[i].t / 48.0f;
        s = 0.2f + 0.8f * g->streak[i].t / 48.0f;
        for (l = 0; l < 2; l++) {
            func_00187B18(&w, &g->tgt, &g->streak[i].p[l]);
            func_00187B48(&w, &w, h);
            func_00187B00(&w, &w, &g->streak[i].p[l]);
            for (j = 0; j < 8; j++) {
                alpha = (u32)(g->streak[i].w[j][l] * (f * (80.0f * func_00101020((f32)g->streak[i].t, 1.0f) *
                                                            func_00100FF0((f32)g->streak[i].t, 48.0f, 32.0f))));
                if (l == 1) {
                    spr.c.r = 0xC8;
                    spr.c.g = 0x46;
                    spr.c.b = 0x0A;
                    spr.c.a = alpha;
                    spr.c.q = 1.0f;
                } else {
                    spr.c.r = 0x0A;
                    spr.c.g = 0x46;
                    spr.c.b = 0xC8;
                    spr.c.a = alpha;
                    spr.c.q = 1.0f;
                }
                x = g->streak[i].c[j][l] % 4 * 32;
                y = (g->streak[i].c[j][l] >> 2) * 32;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&out[0], &cn[0], g->streak[i].sc[j][l]);
                func_00187B48(&out[1], &cn[1], g->streak[i].sc[j][l]);
                func_00187B48(&v, &g->streak[i].v[j][l], s);
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

    if (g->t > 0xF3 && g->t < 0x1F2) {
        n = g->t % 48;
        g->swirl[n].on = 1;
        g->swirl[n].t = 0;
        for (j = 0; j < 2; j++) {
            g->swirl[n].p[j] = g->jp[j];
            for (x = 0; x < 6; x++) {
                g->swirl[n].c[x][j] = (func_0019A5C8() >> 23) % 4;
                g->swirl[n].ang[x][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
                func_00101080(&g->swirl[n].v[x][j], 0.8f);
            }
        }
    }

    ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(0x1F2 - g->t, 0, 32) / 32.0f;
    for (i = 0; i < 48; i++) {
        if (g->swirl[i].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->swirl[i].t / 48.0f);
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
        a = 1.7f * g->swirl[i].t / 48.0f;
        for (l = 0; l < 2; l++) {
            func_00187B18(&w, &g->tgt, &g->swirl[i].p[l]);
            func_00187B48(&w, &w, a);
            func_00187B00(&w, &w, &g->swirl[i].p[l]);
            alpha = (u32)(f * (200.0f * func_00101020((f32)g->swirl[i].t, 1.0f) *
                               func_00100FF0((f32)g->swirl[i].t, 48.0f, 32.0f)));
            if (l == 1) {
                spr.c.r = 0xFF;
                spr.c.g = 0x3C;
                spr.c.b = 0x32;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                spr.c.r = 0x32;
                spr.c.g = 0x3C;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            for (j = 0; j < 6; j++) {
                k = (g->swirl[i].ang[j][l] + (g->swirl[i].t << 15) / 48) & 0xFFFF;
                r = (0.2f + 0.8f * g->swirl[i].t / 48.0f) * func_0020B550(k);
                x = g->swirl[i].c[j][l] % 4 * 32;
                y = (g->swirl[i].c[j][l] >> 2) * 32;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->swirl[i].v[j][l], r);
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

    if (g->t > 0x10E && g->t < 0x1F2) {
        n = g->t % 32;
        g->spin[n].on = 1;
        g->spin[n].t = 0;
        func_0020BBB0(&g->spin[n].mat);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
        func_00100E00(&g->spin[n].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
    }

    ((Quad_b769_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b769_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b769_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b769_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 0);
    for (i = 0; i < 32; i++) {
        if (g->spin[i].on == 0) {
            continue;
        }
        r = func_0020B550((g->spin[i].t << 15) >> 5);
        k = i % 2;
        if (k == 0) {
            pk.v[0].c.r = 0xFF;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0x1C;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
        } else {
            pk.v[0].c.r = 0x1C;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0xFF;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
        }
        pk.v[1].c = pk.v[0].c;
        alpha = (u32)(80.0f * r);
        if (k == 0) {
            pk.v[2].c.r = 0xC8;
            pk.v[2].c.g = 0x3C;
            pk.v[2].c.b = 0x20;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
        } else {
            pk.v[2].c.r = 0x20;
            pk.v[2].c.g = 0x3C;
            pk.v[2].c.b = 0xC8;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
        }
        pk.v[3].c = pk.v[2].c;
        func_0020EB40(m);
        func_0020C940(m2, 0, 0, &g->tgt);
        func_0020BC00(m2, &g->spin[i].mat);
        k = k * 2 - 1;
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
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
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
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                func_002075F0(&pk, ot, 0);
            }
        }
        g->spin[i].t++;
        if (g->spin[i].t > 32) {
            g->spin[i].on = 0;
        }
    }

    f = (f32)func_00101050(g->t - 0x10E, 0, 32) * (f32)func_00101050(0x212 - g->t, 0, 32) / 1024.0f;
    if (f > 0.0f) {
        ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = 0x400;
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = 0x600;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 60.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        alpha = (u32)(128.0f * f * (0.9f + 0.1f * (g->t % 2)));
        spr.c.r = 0xFF;
        spr.c.g = 0x64;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->tgt);
        func_0020BC00(m, m2);
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
    }
    f = (f32)func_00101050(g->t - 0x172, 0, 32) * (f32)func_00101050(0x212 - g->t, 0, 32) / 1024.0f;
    if (f > 0.0f) {
        ((Spr_b769_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b769_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b769_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b769_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b769_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->u = 0x2A0;
        ((Uv_b769_01E00080 *)(s32)&spr.uv0)->v = 0x1D0;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->u = 0x2560;
        ((Uv_b769_01E00080 *)(s32)&spr.uv1)->v = 0x1A30;
        alpha = (u32)(48.0f * f);
        spr.c.r = 0x80;
        spr.c.g = 0x80;
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

    func_001F6D00((u8)((func_00101050(0x232 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0x104) {
        ret = 1;
    } else {
        if (g->t > 0x10E && g->t < 0x212) {
            ret = 6;
        }
        if (g->t == 0x212) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x232) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
