#include "common.h"

/* shape b704:01E00080 (b704), 3181 insns, 1 copy (-O3,p): b704 scene manager, b424:01E00080's twin: joints 0xE / 0xF
   with their midpoint, a 17-step colour table; at 0x63 a warm flash, at 0x62 a 0xE3-frame orange midpoint glow, at
   0x126 the fade flash and the func_002087A0 blur, on even frames of 0x64..0x143 the zoom and the func_01E03770
   backdrop, on 0x63..0x143 the 1x6 ribbon fans (16 steps) and 32-shard bursts, from 0x30 the radial blur through
   func_01E03240, at 0x10 a 32-frame cream blur, the screen tint; returns 1 / 6 / 3 / 8 at 0x58 / 0x63..0x143 / 0x144
   / >0x1B6 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b704_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b704_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b704_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b704_01E00080 c;
    Xyz_b704_01E00080 v[2];
    u64 tail;
} Flat_b704_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b704_01E00080 c;
    Uv_b704_01E00080 uv0;
    Xyz_b704_01E00080 p0;
    Uv_b704_01E00080 uv1;
    Xyz_b704_01E00080 p1;
    u64 pad38;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Spr_b704_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b704_01E00080 c;
        f32 s, t;
        Xyz_b704_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Quad_b704_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b704_01E00080 c;
        Uv_b704_01E00080 uv;
        Xyz_b704_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b704_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b704_01E00080 c;
    struct {
        Uv_b704_01E00080 uv;
        Xyz_b704_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Tex_b704_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b704_01E00080;


typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life[1][6];
    f32 w[1][6];
    f32 len[1][6];
    f32 amp[1][6];
    u8 pad68[8];
    Mtx_b704_01E00080 m[1][6];
} Fan_b704_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life[32];
    s32 ang[32];
    f32 size[32];
    u8 pad188[8];
    Vec4f pos;
    Vec4f v[32];
} Shard_b704_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[6];
    u8 pad28[8];
    Vec4f posA;
    Vec4f scrA;
    Vec4f tgt;
    Vec4f posB;
    Vec4f scrB;
    s32 jn[2];
    u8 pad88[8];
    Vec4f jp[2];
    Vec4f mid;
    Mtx_b704_01E00080 mat[1];
    u8 on;
    u8 pad101[3];
    s32 t1;
    u8 pad108[8];
    Vec4f grid[17][17];
    u8 on2;
    u8 pad1301[3];
    s32 t2;
    u8 col[17][4];
    u8 pad136C[4];
    Fan_b704_01E00080 fan[16];
    u8 on3;
    u8 pad3241[3];
    s32 t3;
    u8 on4;
    u8 pad3249[3];
    s32 t4;
    u8 on5;
    u8 pad3251[3];
    s32 t5;
    u8 on6;
    u8 pad3259[3];
    s32 t6;
    Shard_b704_01E00080 shard[4];
    u8 on7;
    u8 pad40E1[3];
    s32 t7;
    u8 pad40E8[8];
} Scene_b704_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b704(s32 arg0, s32 code) {
    Scene_b704_01E00080 *g = (Scene_b704_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
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
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_002087A0(void *, s32);
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
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern void func_001F70A0(s32, s32, void *, void *, s32, void *);
    extern void func_001F6D00(s32);
    extern void b704_01E03240();
    extern void b704_01E03770();
    extern s32 D_01E03900_b704;
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ph;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    u8 a2;
    f32 r;
    f32 s;
    f32 h;
    f32 a;
    f32 e;
    f32 f;
    f32 s0;
    f32 s1;
    f32 t0;
    f32 t1;
    f32 x0;
    f32 x1;
    f32 w;
    f32 z0;
    f32 z1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Vec4f v;
    Flat_b704_01E00080 flat __attribute__((aligned(8)));
    Spr_b704_01E00080 spr __attribute__((aligned(8)));
    Quad_b704_01E00080 pk __attribute__((aligned(8)));
    Tri_b704_01E00080 tri __attribute__((aligned(8)));
    Tex_b704_01E00080 tx __attribute__((aligned(8)));
    Xyz_b704_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4120);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        g->tex[5] = func_00202BF0(4, 0xF);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0xE, 1);
        g->jn[1] = func_001F5560(g->unitA, 0xF, 0);
        g->on = 0;
        for (j = 0; j < 17; j++) {
            h = 50.0f * func_0020B480((j << 15) >> 4);
            r = func_001A6C60(func_001A6C48(50.0f, 2.0f) - func_001A6C48(h, 2.0f));
            for (k = 0; k < 17; k++) {
                g->grid[j][k].x = r * func_0020B550((k << 16) >> 4);
                g->grid[j][k].y = h;
                g->grid[j][k].z = r * func_0020B480((k << 16) >> 4);
                g->grid[j][k].w = 1.0f;
            }
        }
        g->on2 = 0;
        g->t2 = 0;
        for (i = 0; i < 17; i++) {
            f = (f32)i / 16.0f;
            a = 1.0f - f;
            s = 64.0f * a + 200.0f * f;
            g->col[i][0] = (u32)s;
            g->col[i][1] = (u32)s;
            g->col[i][2] = (u32)(255.0f * a + 255.0f * f);
            g->col[i][3] = (u32)(128.0f * a);
        }
        for (i = 0; i < 16; i++) {
            g->fan[i].on = 0;
        }
        g->on3 = 0;
        g->on4 = 0;
        g->on5 = 0;
        g->on6 = 0;
        for (i = 0; i < 4; i++) {
            g->shard[i].on = 0;
        }
        g->on7 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    func_001F53C0(1, g->unitB, &g->posB);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_00187B00(&v, &g->jp[0], &g->jp[1]);
    func_00187B48((void *)&g->mid, &v, 0.5f);
    func_00187B18(&v, &g->mid, &g->posB);
    func_00100E40(&g->mat[0], &v);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->posA, m, &xyz, &depth);
    g->scrA.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scrA.y = (s32)(xyz.y >> 4) - 0x720;
    g->scrA.z = func_0017B340(xyz.z);
    g->scrA.w = 1.0f;
    if (g->scrA.x < 0.0f) {
        g->scrA.x = 0.0f;
    }
    if (g->scrA.x > 640.0f) {
        g->scrA.x = 640.0f;
    }
    if (g->scrA.y < 0.0f) {
        g->scrA.y = 0.0f;
    }
    if (g->scrA.y > 448.0f) {
        g->scrA.y = 448.0f;
    }
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

    if (g->t == 0x63) {
        g->on6 = 1;
        g->t6 = 0;
    }
    if (g->on6 == 1) {
        ((Flat_b704_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b704_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b704_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b704_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(0));
        alpha = (u32)(128.0f * ((f32)(0x20 - g->t6) / 32.0f));
        flat.c.r = 0xFF;
        flat.c.g = 0xFA;
        flat.c.b = 0xC8;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        flat.v[0].x = 0x6C00;
        flat.v[0].y = 0x7200;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t6++;
        if (g->t6 > 0x20) {
            g->on6 = 0;
        }
    }

    if (g->t == 0x126) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t4 == 0x1E) {
            g->on3 = 0;
            g->on6 = 0;
            g->on = 0;
        }
        ((Flat_b704_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b704_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b704_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b704_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (func_00101020((f32)g->t4, 30.0f) *
                                (1.0f - func_00100D50(func_00101050(g->t4 - 0x32, 0, 0x40), 0x40, 1))));
        flat.c.r = 0xFF;
        flat.c.g = 0xFF;
        flat.c.b = 0xFF;
        flat.c.a = alpha;
        flat.c.q = 1.0f;
        flat.v[0].x = 0x6C00;
        flat.v[0].y = 0x7200;
        flat.v[0].z = 0xFFFFF8;
        flat.v[0].f = 0;
        flat.v[1].x = 0x9400;
        flat.v[1].y = 0x8E00;
        flat.v[1].z = 0xFFFFF8;
        flat.v[1].f = 0;
        func_002075F0(&flat, ot, 0);
        g->t4++;
        if (g->t4 > 0x72) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x126) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b704_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b704_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b704_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b704_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b704_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        func_002087A0(&tri, 1);
        alpha = (u32)(128.0f * func_00101020((f32)g->t3, 20.0f));
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (i = 0; i < 1; i++) {
            f = 1.0f + 0.1f * (1 - i);
            for (j = 0; j < 8; j++) {
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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
        g->t3++;
        if (g->t3 > 0x1E) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x63 && g->t < 0x144 && g->t % 2 == 0) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Spr_b704_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b704_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b704_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b704_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b704_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &spr.tex0, &spr.tex1);
        func_00208460();
        alpha = (u32)(32.0f * (f32)(1 - g->t5));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        for (i = 0; i < 4; i++) {
            f = 1.0f + 0.1f * (i + 1) / 4.0f;
            j = (s32)(320.0f * f);
            x = (s32)(224.0f * f);
            spr.p0.x = (0x800 - j) << 4;
            spr.p0.y = (0x800 - x) << 4;
            spr.p0.z = 0xFFFFF8;
            spr.p0.f = 0;
            spr.p1.x = (j + 0x800) << 4;
            spr.p1.y = (x + 0x800) << 4;
            spr.p1.z = 0xFFFFF8;
            spr.p1.f = 0;
            func_002075F0(&spr, 0, 0);
        }
        func_00207FD0(buf, ot, 0);
        g->t5++;
        if (g->t5 > 1) {
            g->on5 = 0;
        }
    }

    if (g->t == 0x62) {
        g->on2 = 1;
        g->t2 = 0;
    }
    w = func_00101020((f32)g->t2, 4.0f) * func_00100FF0((f32)g->t2, 226.0f, 222.0f);
    if (g->on2 == 1) {
        ((Spr_b704_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b704_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b704_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b704_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b704_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[3], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(255.0f * (0.7f + 0.3f * (g->t2 % 2)) * w);
        spr.c.r = 0xC8;
        spr.c.g = 0x8C;
        spr.c.b = 0x3C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 35.0f;
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
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        for (i = 0; i < 1; i++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->mid);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 0xE2) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x62 && g->t < 0x144) {
        n = g->t % 16;
        g->fan[n].on = 1;
        g->fan[n].t = 0;
        for (i = 0; i < 1; i++) {
            for (j = 0; j < 6; j++) {
                g->fan[n].life[i][j] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->fan[n].w[i][j] = 10.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->fan[n].len[i][j] = -400.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->fan[n].amp[i][j] = 35.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                func_0020BBB0(&g->fan[n].m[i][j]);
                func_00100E00(&g->fan[n].m[i][j], ((func_0019A5C8() >> 23) % 256 * 0xE38 >> 8) - 0x71C, 1);
                func_00100E00(&g->fan[n].m[i][j], ((func_0019A5C8() >> 23) % 256 * 0xE38 >> 8) - 0x71C, 0);
                func_00100E00(&g->fan[n].m[i][j], (j << 16) / 6, 2);
            }
        }
    }

    ((Quad_b704_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b704_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b704_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b704_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 16; i++) {
        if (g->fan[i].on == 0) {
            continue;
        }
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 6; k++) {
                if (g->fan[i].t > g->fan[i].life[j][k]) {
                    continue;
                }
                func_0020EB40(m);
                func_0020C940(m2, NULL, NULL, &g->mid);
                func_0020BC00(m2, &g->mat[0]);
                func_0020BC00(m2, &g->fan[i].m[j][k]);
                func_0020BC00(m, m2);
                h = 1.0f - func_00100D50(g->fan[i].t, g->fan[i].life[j][k], 1);
                e = (32.0f * (k % 4)) / 128.0f;
                z0 = 0.25f + e;
                ph = i * 0xD05 + j * 0x115C + k * 0x15B3;
                for (l = 0; l < 16; l++) {
                    z1 = 1.0f + (1.0f - h);
                    alpha = (u32)(w * (g->col[l][3] * h));
                    a2 = (u32)(w * (g->col[l + 1][3] * h));
                    pk.v[0].c.r = g->col[l][0];
                    pk.v[0].c.g = g->col[l][1];
                    pk.v[0].c.b = g->col[l][2];
                    pk.v[0].c.a = alpha;
                    pk.v[0].c.q = 1.0f;
                    pk.v[2].c.r = g->col[l + 1][0];
                    pk.v[2].c.g = g->col[l + 1][1];
                    pk.v[2].c.b = g->col[l + 1][2];
                    pk.v[2].c.a = a2;
                    pk.v[2].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[3].c = pk.v[2].c;
                    t0 = (128.0f * (l % 4) / 4.0f) / 128.0f;
                    t1 = (128.0f * (l % 4 + 1) / 4.0f) / 128.0f;
                    pk.v[0].s = e;
                    pk.v[0].t = t0;
                    pk.v[1].s = z0;
                    pk.v[1].t = t0;
                    pk.v[2].s = e;
                    pk.v[2].t = t1;
                    pk.v[3].s = z0;
                    pk.v[3].t = t1;
                    s0 = l / 16.0f;
                    s1 = (l + 1) / 16.0f;
                    r = g->fan[i].len[j][k] * s0;
                    a = g->fan[i].w[j][k] * h;
                    f = g->fan[i].len[j][k] * s1;
                    x0 = s0 * (z1 * (g->fan[i].amp[j][k] * func_0020B550((ph + ((l << 16) >> 4)) & 0xFFFF)));
                    x1 = s1 * (z1 * (g->fan[i].amp[j][k] * func_0020B550((ph + (((l + 1) << 16) >> 4)) & 0xFFFF)));
                    cn[0].x = x0;
                    cn[0].y = -a + x0;
                    cn[0].z = r;
                    cn[0].w = 1.0f;
                    cn[1].x = x0;
                    cn[1].y = a + x0;
                    cn[1].z = r;
                    cn[1].w = 1.0f;
                    cn[2].x = x1;
                    cn[2].y = -a + x1;
                    cn[2].z = f;
                    cn[2].w = 1.0f;
                    cn[3].x = x1;
                    cn[3].y = a + x1;
                    cn[3].z = f;
                    cn[3].w = 1.0f;
                    if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, 0);
                    }
                }
            }
        }
        g->fan[i].t++;
        if (g->fan[i].t > 16) {
            g->fan[i].on = 0;
        }
    }

    if (g->t > 0x62 && g->t < 0x144) {
        n = g->t % 4;
        g->shard[n].on = 1;
        g->shard[n].t = 0;
        for (k = 0; k < 32; k++) {
            g->shard[n].life[k] = (s32)(4.0f * (0.3f + 0.7f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->shard[n].size[k] = 10.0f * (0.3f + 0.7f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->shard[n].ang[k] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->shard[n].pos = g->posB;
            func_00101080(&g->shard[n].v[k], 1.5f);
        }
    }

    ((Tex_b704_01E00080 *)(s32)&tx)->flags = 0x24;
    ((Tex_b704_01E00080 *)(s32)&tx)->size = 9;
    ((Tex_b704_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
    ((Tex_b704_01E00080 *)(s32)&tx)->pad4 = 0;
    ((Tex_b704_01E00080 *)(s32)&tx)->flags |= 0x800;
    func_002086D0(&tx, func_00208D00(1));
    func_00208700(&tx, g->tex[5], 1);
    func_00208CB0(&tx, ((u64)0x3FC << 32) | 0x811FC0BA);
    ((Spr_b704_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b704_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b704_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b704_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b704_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    for (i = 0; i < 4; i++) {
        if (g->shard[i].on == 0) {
            continue;
        }
        for (k = 0; k < 32; k++) {
            if (g->shard[i].t <= g->shard[i].life[k]) {
            h = func_0020B480((g->shard[i].t << 14) / g->shard[i].life[k]);
            alpha = (u32)(64.0f * h);
            tx.c.r = 0x96;
            tx.c.g = 0x78;
            tx.c.b = 0x20;
            tx.c.a = alpha;
            tx.c.q = 1.0f;
            alpha = (u32)(255.0f * h);
            spr.c.r = 0x96;
            spr.c.g = 0x78;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            x = k % 4 % 2 * 0x3B + 0xA;
            y = k % 4 / 2 * 64 + 0x80;
            ((Uv_b704_01E00080 *)(s32)&tx.v[0].uv)->u = x << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[0].uv)->v = y << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[1].uv)->u = (x + 0x3B) << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[1].uv)->v = y << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[2].uv)->u = x << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[2].uv)->v = (y + 0x40) << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[3].uv)->u = (x + 0x3B) << 4;
            ((Uv_b704_01E00080 *)(s32)&tx.v[3].uv)->v = (y + 0x40) << 4;
            x = k % 8 % 4 * 32;
            y = (k % 8 >> 2) * 32;
            ((Uv_b704_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b704_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b704_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b704_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            r = g->shard[i].size[k];
            h = 0.5f * r * func_0020B550((g->shard[i].t << 14) / g->shard[i].life[k]);
            cn[0].x = -r + h;
            cn[0].y = -r - h;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r + h;
            cn[1].y = -r - h;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = -r - h;
            cn[2].y = r + h;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = r - h;
            cn[3].y = r + h;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            func_0020EB40(m);
            func_00187B00(&v, &g->shard[i].v[k], &g->shard[i].pos);
            func_00187B60(m2, m3, &v);
            func_00100E00(m2, g->shard[i].ang[k], 2);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &tx, &depth) == 1) {
                tx.v[0].p.z = 0xFFFFF8;
                tx.v[1].p.z = tx.v[0].p.z;
                tx.v[2].p.z = tx.v[0].p.z;
                tx.v[3].p.z = tx.v[0].p.z;
                func_002075F0(&tx, ot, 0);
            }
            r = 0.1f * g->shard[i].size[k];
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_0020EB40(m);
            func_00187B48(&v, &g->shard[i].v[k], -1.0f * (0.8f + 0.2f * g->shard[i].t / (f32)g->shard[i].life[k]));
            func_00187B00(&v, &v, &g->shard[i].pos);
            func_00187B60(m2, m3, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
            }
        }
        g->shard[i].t++;
        if (g->shard[i].t > 4) {
            g->shard[i].on = 0;
        }
    }

    if (g->t == 0x30) {
        g->on = 1;
        g->t1 = 0;
    }
    if (g->on == 1) {
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        v.y = g->posA.y;
        func_00205440(&v, m, &xyz, &depth);
        ((Tri_b704_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b704_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b704_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b704_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b704_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        D_01E03900_b704 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, b704_01E03240);
        func_00208460();
        a = func_00101020((f32)g->t1, 48.0f) * func_00100FF0((f32)g->t1, 4350.0f, 4302.0f);
        e = func_00101020((f32)g->t1, 48.0f) * func_00100FF0((f32)g->t1, 4350.0f, 4302.0f);
        for (i = 0; i < 1; i++) {
            alpha = (u32)(128.0f * a);
            a2 = (u32)(128.0f * e);
            tri.v[0].c.r = 0x80;
            tri.v[0].c.g = 0x80;
            tri.v[0].c.b = 0x80;
            tri.v[0].c.a = alpha;
            tri.v[0].c.q = 1.0f;
            tri.v[1].c.r = 0x80;
            tri.v[1].c.g = 0x80;
            tri.v[1].c.b = 0x80;
            tri.v[1].c.a = a2;
            tri.v[1].c.q = 1.0f;
            tri.v[2].c = tri.v[1].c;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scrA);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scrA);
                func_00187B48((void *)&out[0], &out[0], 1.0f);
                func_00187B48(&out[1], &out[1], 1.0f);
                func_00187B00(&out[0], &out[0], &g->scrA);
                func_00187B00(&out[1], &out[1], &g->scrA);
                x = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
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
        g->t1++;
        if (g->t1 > 0x10FE) {
            g->on = 0;
        }
    }

    if (g->t > 0x63 && g->t < 0x144 && g->t % 2 == 0) {
        ((Spr_b704_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b704_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b704_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b704_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b704_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        D_01E03900_b704 = (s32)g;
        func_001F70A0(g->unitB, 1, &spr.tex0, &spr.tex1, 0, b704_01E03770);
        func_00208460();
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b704_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b704_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6C00;
        spr.p0.y = 0x7200;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x9400;
        spr.p1.y = 0x8E00;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        func_00207FD0(buf, ot, 0);
    }

    if (g->t == 0x10) {
        g->on7 = 1;
        g->t7 = 0;
    }
    if (g->on7 == 1) {
        ((Tri_b704_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b704_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b704_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b704_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b704_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(1));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x20 - g->t7) * 128 >> 5;
        tri.v[0].c.r = 0xFA;
        tri.v[0].c.g = 0xDC;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = 0;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0xFA;
        tri.v[1].c.g = 0xDC;
        tri.v[1].c.b = 0x80;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 0.3f * func_00100D50(g->t7, 0x20, 1);
        for (i = 0; i < 3; i++) {
            f = 1.0f + r * (i + 1) / 3.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b704_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scrA);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scrA);
                func_00187B48(&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
                func_00187B00(&out[0], &out[0], &g->scrA);
                func_00187B00(&out[1], &out[1], &g->scrA);
                x = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
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
        g->t7++;
        if (g->t7 > 0x20) {
            g->on7 = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x1B6 - g->t, 0, 0x40) * (func_00101050(g->t, 0, 0x40) * -96) >> 12) + 0x80));
    if (g->t == 0x58) {
        ret = 1;
    } else {
        if (g->t > 0x62 && g->t < 0x144) {
            ret = 6;
        }
        if (g->t == 0x144) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x1B6) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b704:01E03240 (Gb704_GenAuraTex), 331 insns, 1 copy (-O3,p): b066:01E036B0 at -O3 with a 0x40 grey backdrop
   and the grid tinted blue (0x58, 0x58, 0xFF), grid at object +0x110 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b704_01E03240;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b704_01E03240 v[2];
    u64 tail;
} Flat_b704_01E03240;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b704_01E03240;

typedef struct {
    Rgbaq_b704_01E03240 c;
    f32 s, t;
    Xyz_b704_01E03240 p;
} Tv_b704_01E03240;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b704_01E03240 v[4];
    u8 tail[0x20];
} Tex_b704_01E03240;

typedef struct {
    u8 pad0[0x14];
    void *texture;
    u8 pad18[0x18];
    u8 pos[0x10];
    u8 pad40[0xD0];
    Vec4f grid[17][17];
} Obj_b704_01E03240;

extern Obj_b704_01E03240 *D_01E03900_b704;

#pragma optimization_level 3

static void func_01E03240_b704(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern u64 func_00208D00(s32);
    extern void *func_00207650(void *, void *, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    Obj_b704_01E03240 *o __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    Flat_b704_01E03240 flat __attribute__((aligned(8)));
    Tex_b704_01E03240 pk __attribute__((aligned(8)));
    f32 depth;
    void *p;
    s32 j;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;

    o = D_01E03900_b704;
    p = func_00209F70(buf, 0xFF000000);
    ((Flat_b704_01E03240 *)(s32)&flat)->flags = 6;
    ((Flat_b704_01E03240 *)(s32)&flat)->size = 3;
    ((Flat_b704_01E03240 *)(s32)&flat)->regs = 0x441;
    ((Flat_b704_01E03240 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(2));
    flat.r = 0x40;
    flat.g = 0x40;
    flat.b = 0x40;
    flat.a = 0x80;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    p = func_00207650(p, &flat, 0, 0);
    ((Tex_b704_01E03240 *)(s32)&pk)->flags = 0x34;
    ((Tex_b704_01E03240 *)(s32)&pk)->size = 0xC;
    ((Tex_b704_01E03240 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b704_01E03240 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, o->texture, 1);
    func_00208CB0(&pk, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_00187B60(m2, m2, o->pos);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
    func_0020BC00((s32)m, m2);
    pk.v[0].c.r = 0x58;
    pk.v[0].c.g = 0x58;
    pk.v[0].c.b = 0xFF;
    pk.v[0].c.a = 0x80;
    pk.v[0].c.q = 1.0f;
    pk.v[1].c = pk.v[0].c;
    pk.v[2].c = pk.v[0].c;
    pk.v[3].c = pk.v[0].c;
    for (i = 0; i < 16; i++) {
        t0 = (f32)(i % 4) / 4.0f;
        t1 = (f32)(i % 4 + 1) / 4.0f;
        for (j = 0; j < 16; j++) {
            s0 = (f32)(j % 4) / 4.0f;
            s1 = (f32)(j % 4 + 1) / 4.0f;
            pk.v[0].s = s0;
            pk.v[0].t = t0;
            pk.v[1].s = s1;
            pk.v[1].t = t0;
            pk.v[2].s = s0;
            pk.v[2].t = t1;
            pk.v[3].s = s1;
            pk.v[3].t = t1;
            if (func_00100BA0(&o->grid[i][j], &o->grid[i][j + 1], &o->grid[i + 1][j], &o->grid[i + 1][j + 1], m, &pk,
                              &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                p = func_00207650(p, &pk, 0, 0);
            }
        }
    }
    func_00209F70(p, 0);
}

#pragma optimization_level reset

/* shape b066:01E03BE0, 69 insns, 8 copies: one flat GS sprite (RGBAQ, XYZ2, XYZ2) in grey 0x80, drawn between two
   func_00209F70 calls (mask 0xFF000000 on, then off) */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b066_01E03BE0;

typedef struct {
    Hdr_b066_01E03BE0 h;
    u8 r, g, b, a;
    f32 q;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
} Pkt_b066_01E03BE0;

static void func_01E03770_b704(void *arg0) {
    extern void *func_00207650();
    Pkt_b066_01E03BE0 p;
    void *ctx;

    ctx = func_00209F70(arg0, 0xFF000000);
    ((Hdr_b066_01E03BE0 *)(s32)&p)->count = 6;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->tag = 3;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->regs = 0x441;
    ((Hdr_b066_01E03BE0 *)(s32)&p)->pad = 0;
    func_002086D0(&p, func_00208D00(3));
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0xFF;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFF8;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFF8;
    p.f1 = 0;
    func_00209F70(func_00207650(ctx, &p, 0, 0), 0);
}
