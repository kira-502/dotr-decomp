#include "common.h"

/* shape b739:01E00080 (b739), 3173 insns, 1 copy (-O3,p): scene effect: three bursts at the target, a render-to-
   texture cone, blade quads, sparks and a flash fan, b153's blur and burst */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b739_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b739_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b739_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b739_01E00080 c;
    Uv_b739_01E00080 uv0;
    Xyz_b739_01E00080 p0;
    Uv_b739_01E00080 uv1;
    Xyz_b739_01E00080 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b739_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b739_01E00080 c;
        Uv_b739_01E00080 uv;
        Xyz_b739_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b739_01E00080;

typedef struct {
    Rgbaq_b739_01E00080 c;
    f32 s, t;
    Xyz_b739_01E00080 p;
} Tv_b739_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b739_01E00080 v[4];
    u8 tail[0x20];
} Quad_b739_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b739_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f w[128];
    u8 c2[32];
    Vec4f v3[32];
} Burst_b739_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[3];
    u8 pad14[0xC];
    Vec4f pos[3];
} Blade_b739_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[3][32];
    u8 pad68[8];
    Vec4f pos[3];
    Vec4f v[3][32];
} Spark_b739_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Flash_b739_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f pos;
    Vec4f tgt;
    Vec4f scrA;
    Vec4f scrB;
    s32 jn[3];
    u8 pad6C[4];
    Vec4f jp[3];
    s32 cur;
    u8 padA4[0xC];
    Burst_b739_01E00080 burst[3];
    u8 on2;
    u8 pad2CF1[3];
    s32 t2;
    u8 pad2CF8[8];
    Vec4f cone[32][17];
    Vec4f cone2[32][17];
    s32 nb;
    u8 pad7104[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Blade_b739_01E00080 blade[1];
    s32 ns;
    u8 pad91E4[0xC];
    Spark_b739_01E00080 spark[1];
    Flash_b739_01E00080 flash[12];
    u8 on3;
    u8 pad98F1[3];
    s32 t3;
    u8 pad98F8[8];
} Scene_b739_01E00080;


#pragma optimization_level 3

static s32 func_01E00080_b739(s32 arg0, s32 code) {
    Scene_b739_01E00080 *g = (Scene_b739_01E00080 *)arg0;
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
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
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
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F63F0(s32, s32, void *);
    extern void func_001F7070(s32, void *, void *, s32, void *);
    extern f32 func_00205DF0(void *, f32);
    extern void func_001F6D00(s32);
    extern void b739_01E03220();
    extern s32 D_01E03B00_b739;
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 l;
    u8 a2;
    s32 buf;
    u8 on;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 c;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 h;
    f32 u0;
    f32 u1;
    f32 w0;
    f32 w1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b739_01E00080 m4;
    Vec4f v;
    Spr_b739_01E00080 spr __attribute__((aligned(8)));
    Tri_b739_01E00080 tri __attribute__((aligned(8)));
    Quad_b739_01E00080 pk __attribute__((aligned(8)));
    Xyz_b739_01E00080 xyz;
    f32 depth;
    u8 col[4] __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9900);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0x1D, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x30, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x39, 0);
        g->cur = 0;
        for (i = 0; i < 3; i++) {
            g->burst[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 32; i++) {
            r = 45.0f * (32 - i) / 32.0f;
            for (j = 0; j < 17; j++) {
                g->cone[i][j].x = r * func_0020B550((j << 16) >> 4);
                g->cone[i][j].y = r * func_0020B480((j << 16) >> 4);
                g->cone[i][j].z = 0.0f;
                g->cone[i][j].w = 1.0f;
            }
        }
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        g->nb = 0;
        for (n = 0; n < 8; n++) {
            h = -70.0f * g->obj * (n + 1) / 8.0f;
            s = 2.0f * (8 - (n + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                ang = ((i << 16) >> 4) + ((n << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = 0.0f;
                v.w = 1.0f;
                func_0020BBB0(&m4);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[n][i][0].x = -1.0f;
                g->grid[n][i][0].y = 0.0f;
                g->grid[n][i][0].z = 0.0f;
                g->grid[n][i][0].w = 1.0f;
                g->grid[n][i][1].x = 1.0f;
                g->grid[n][i][1].y = 0.0f;
                g->grid[n][i][1].z = 0.0f;
                g->grid[n][i][1].w = 1.0f;
                g->grid[n][i][2].x = -1.0f;
                g->grid[n][i][2].y = 0.0f;
                g->grid[n][i][2].z = h;
                g->grid[n][i][2].w = 1.0f;
                g->grid[n][i][3].x = 1.0f;
                g->grid[n][i][3].y = 0.0f;
                g->grid[n][i][3].z = h;
                g->grid[n][i][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[n][i][k], &m4, &g->grid[n][i][k]);
                }
                func_00187B00(&g->grid[n][i][2], &g->grid[n][i][2], &v);
                func_00187B00(&g->grid[n][i][3], &g->grid[n][i][3], &v);
                g->gc[n][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 1; i++) {
            g->blade[i].on = 0;
        }
        g->ns = 0;
        for (i = 0; i < 1; i++) {
            g->spark[i].on = 0;
        }
        for (i = 0; i < 12; i++) {
            g->flash[i].on = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (k = 0; k < 3; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->pos, m, &xyz, &depth);
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

    if (g->t == 0xBD) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b739_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b739_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b739_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b739_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b739_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x30 - g->t3) * 0x40 / 48;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (j = 0; j < 8; j++) {
            r = 1.0f + 0.15f * (8 - j) / 8.0f;
            for (i = 0; i < 8; i++) {
                x = (s32)g->scrB.x;
                y = (s32)g->scrB.y;
                ((Uv_b739_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b739_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[i].x;
                y = (s32)D_28B960[i].y;
                ((Uv_b739_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b739_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[i + 1].x;
                y = (s32)D_28B960[i + 1].y;
                ((Uv_b739_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b739_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[i], (void *)&g->scrB);
                func_00187B18(&out[1], &D_28B960[i + 1], &g->scrB);
                func_00187B48(&out[0], &out[0], r);
                func_00187B48(&out[1], &out[1], r);
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
                func_002075F0(&tri, 0, 0);
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t3++;
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    if (g->t == 0xBD) {
        for (q = 0; q < 3; q++) {
            g->cur = q;
            g->burst[g->cur].on = 1;
            g->burst[g->cur].t = 1;
            g->burst[g->cur].pos.x = 30.0f * (g->cur - 1);
            g->burst[g->cur].pos.y = 0.0f;
            g->burst[g->cur].pos.z = 0.0f;
            g->burst[g->cur].pos.w = 1.0f;
            func_00187B00(&g->burst[g->cur].pos, &g->burst[g->cur].pos, &g->tgt);
            for (i = 0; i < 64; i++) {
                g->burst[g->cur].c[i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst[g->cur].v[i], 2.0f);
            }
            for (i = 0; i < 128; i++) {
                func_00101080(&g->burst[g->cur].w[i], 2.5f);
            }
            for (i = 0; i < 32; i++) {
                g->burst[g->cur].c2[i] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[g->cur].v3[i], 2.0f);
            }
        }
    }

    for (j = 0; j < 3; j++) {
        if (g->burst[j].on == 0) {
            continue;
        }
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 12.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
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
        spr.c.r = 0x50;
        spr.c.g = 0xE4;
        spr.c.b = 0xFF;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[j].t, 0x30, 1);
        for (k = 0; k < 32; k++) {
            func_00187B48(&v, &g->burst[j].v3[k], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c2[k] % 4 * 32;
            y = (g->burst[j].c2[k] >> 2) * 32;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 10.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
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
        alpha = (0x30 - g->burst[j].t) * 0 / 48;
        a2 = (0x30 - g->burst[j].t) * 0 / 48;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->burst[j].t, 0x30, 1);
            if (k % 2 == 0) {
                s *= 0.9f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x1E;
                spr.c.g = 0x60;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[j].v[k], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c[k] % 4 * 32;
            y = (g->burst[j].c[k] >> 2) * 32;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[j].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[j].t, 0x30, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        spr.c.r = 0xFF;
        spr.c.g = 0x5E;
        spr.c.b = 0x3A;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 130.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        n = g->burst[j].t;
        f = (f32)(0x30 - n) / 48.0f;
        h = func_00100D50(n, 0x30, 1);
        for (k = 0; k < 128; k++) {
            for (q = 0; q < 6; q++) {
                alpha = (u32)(f * ((q + 6) * 0xFF / 12));
                spr.c.r = 0x80;
                spr.c.g = 0xF0;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[j].w[k], h + 0.01f * q);
                func_00187B00(&v, &v, &g->burst[j].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[j].t++;
        if (g->burst[j].t > 0x30) {
            g->burst[j].on = 0;
        }
    }

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
    }
    func_001F63F0(g->unitA, 0, 0);
    if (g->on2 == 1) {
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        D_01E03B00_b739 = (s32)g;
        func_001F7070(1, &spr.txa, &spr.txb, 0, b739_01E03220);
        func_00208460();
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        x = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        depth = func_00205DF0(&g->pos, 0.0f);
        func_00207FD0(buf, ot, (u32)depth);
        g->t2++;
        if (g->t2 > 0x40) {
            g->on2 = 0;
            func_001F63F0(g->unitA, 0, 0);
        }
    }

    if (g->t == 0xB0) {
        i = g->nb;
        (void)i;
        g->blade[i].on = 1;
        g->blade[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (j = 0; j < 3; j++) {
            g->blade[i].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade[i].pos[j] = g->jp[j];
            g->spark[c].pos[j] = g->jp[j];
            for (n = 0; n < 32; n++) {
                g->spark[c].c[j][n] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[j][n], 1.0f);
            }
        }
        g->nb++;
        if (g->nb >= 1) {
            g->nb = 0;
        }
        g->ns++;
        if (g->ns >= 1) {
            g->ns = 0;
        }
    }

    ((Quad_b739_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b739_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b739_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b739_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (j = 0; j < 1; j++) {
        if (g->blade[j].on == 0) {
            continue;
        }
        alpha = (6 - g->blade[j].t) * 0x56 / 6;
        pk.v[0].c.r = 0x30;
        pk.v[0].c.g = 0x40;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade[j].t / 6.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 3; l++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->blade[j].pos[l]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->blade[j].rot[l], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (q = 0; q < 8; q++) {
                for (c = 0; c < 16; c++) {
                    n = g->gc[q][c];
                    x = n % 4 * 32;
                    y = (n >> 2) * 32;
                    u0 = x / 128.0f;
                    u1 = (32.0f + x) / 128.0f;
                    w1 = y / 64.0f;
                    w0 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = w0;
                    pk.v[1].s = u1;
                    pk.v[1].t = w0;
                    pk.v[2].s = u0;
                    pk.v[2].t = w1;
                    pk.v[3].s = u1;
                    pk.v[3].t = w1;
                    if (func_002058D0(g->grid[q][c], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 45.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade[j].t, 6, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x4C;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (i = 0; i < 3; i++) {
            v = g->blade[j].pos[i];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade[j].t++;
        if (g->blade[j].t > 6) {
            g->blade[j].on = 0;
        }
    }

    ((Spr_b739_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b739_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b739_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b739_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b739_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 1; j++) {
        if (g->spark[j].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->spark[j].t / 16.0f);
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
        spr.c.r = 0xBC;
        spr.c.g = 0xBC;
        spr.c.b = 0xBC;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[j].t, 16, 1);
        for (q = 0; q < 3; q++) {
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->spark[j].v[q][k], s);
                func_00187B00(&v, &v, &g->spark[j].pos[q]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[j].c[q][k] % 4 * 32;
                y = (g->spark[j].c[q][k] >> 2) * 32;
                ((Uv_b739_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b739_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b739_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b739_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[j].t++;
        if (g->spark[j].t > 16) {
            g->spark[j].on = 0;
        }
    }

    if (g->t > 0x46 && g->t < 0x6E) {
        n = g->t % 12;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
    }
    ((Tri_b739_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b739_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b739_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b739_01E00080 *)(s32)&tri)->pad4 = 0;
    ((Tri_b739_01E00080 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&tri, func_00208D00(1));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t - 0x46, 0, 16) * (f32)func_00101050(0x6E - g->t, 0, 16) / 256.0f;
    on = 0;
    for (i = 0; i < 12; i++) {
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
        alpha = (u32)(f * (128.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 13)));
        tri.v[0].c.r = 0x64;
        tri.v[0].c.g = 0x30;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(f * (128.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 13)));
        tri.v[1].c.r = 0x64;
        tri.v[1].c.g = 0x30;
        tri.v[1].c.b = 0xFF;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 1.0f + (-0.2f + 0.4f * g->flash[i].t / 12.0f) + 0.2f / 12.0f;
        for (k = 0; k < 8; k++) {
            x = (s32)g->scrA.x;
            y = (s32)g->scrA.y;
            ((Uv_b739_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
            x = (s32)D_28B960[k].x;
            y = (s32)D_28B960[k].y;
            ((Uv_b739_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
            x = (s32)D_28B960[k + 1].x;
            y = (s32)D_28B960[k + 1].y;
            ((Uv_b739_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
            ((Uv_b739_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
            func_00187B18((void *)&out[0], &D_28B960[k], (void *)&g->scrA);
            func_00187B18(&out[1], &D_28B960[k + 1], (void *)&g->scrA);
            func_00187B48(&out[0], &out[0], r);
            func_00187B48(&out[1], &out[1], r);
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
        g->flash[i].t++;
        if (g->flash[i].t > 12) {
            g->flash[i].on = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    func_001F6D00((u8)((func_00101050(0x12D - g->t, 0, 64) * (func_00101050(g->t, 0, 64) * -104) >> 12) + 0x80));
    if (g->t == 0xB3) {
        ret = 1;
    } else {
        if (g->t > 0xBD && g->t < 0xED) {
            ret = 6;
        }
        if (g->t == 0xED) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x12D) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b739:01E03220, 543 insns, 1 copy (-O3,p): draws a two-layer 32x17 cone grid: a sine-rippled ring grid fading
   with the timer, triangles to an apex for the last row, textured quads elsewhere, each drawn where both layers
   project */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b739_01E03220;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b739_01E03220;

typedef struct {
    Rgbaq_b739_01E03220 c;
    f32 s, t;
    Xyz_b739_01E03220 p;
} Tv_b739_01E03220;

typedef struct {
    u64 d;
} Reg_b739_01E03220;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b739_01E03220 v[3];
    u64 pad58;
    Reg_b739_01E03220 tex0;
    Reg_b739_01E03220 tex1;
    u64 tail;
} Tri_b739_01E03220;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b739_01E03220 v[4];
    u64 pad70;
    Reg_b739_01E03220 tex0;
    Reg_b739_01E03220 tex1;
    u64 tail;
} Quad_b739_01E03220;

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x2CC4];
    s32 t;
    u8 pad2CF8[8];
    union {
        Vec4f lo[40][17];
        struct {
            u8 pad[0x2200];
            Vec4f hi[32][17];
        } s;
    } u;
} Obj_b739_01E03220;

extern Obj_b739_01E03220 *D_01E03B00_b739;

#pragma optimization_level 3

static void func_01E03220_b739(void *buf) {
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void *func_00207650(void *, void *, s32, s32);
    Obj_b739_01E03220 *g __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f v;
    Tri_b739_01E03220 tri __attribute__((aligned(8)));
    Quad_b739_01E03220 pk __attribute__((aligned(8)));
    Rgbaq_b739_01E03220 c;
    f32 depth;
    void *p;
    s32 k;
    f32 s;
    f32 h;
    f32 rad;
    f32 w;
    s32 t;
    f32 r;
    u16 a;
    u16 b;

    g = D_01E03B00_b739;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0((s32)m3);
    func_0020EB40(m);
    v = g->pos;
    func_00187B60(m2, m3, &v);
    func_0020BC00((s32)m, m2);
    ((Tri_b739_01E03220 *)(s32)&tri)->flags = 0x33;
    ((Tri_b739_01E03220 *)(s32)&tri)->size = 9;
    ((Tri_b739_01E03220 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b739_01E03220 *)(s32)&tri)->pad4 = 0;
    ((Quad_b739_01E03220 *)(s32)&pk)->flags = 0x34;
    ((Quad_b739_01E03220 *)(s32)&pk)->size = 0xC;
    ((Quad_b739_01E03220 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b739_01E03220 *)(s32)&pk)->pad4 = 0;
    p = (void *)func_00208870(func_0020F290((s32)p), -1, 1, &tri.tex0, &tri.tex1);
    pk.tex0 = tri.tex0;
    pk.tex1 = tri.tex1;
    p = (void *)func_0020F290((s32)p);
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((s64)0x700 << 32) | 0xA0000A);
    ((Tri_b739_01E03220 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Quad_b739_01E03220 *)(s32)&pk)->flags |= 0x800;
    s = func_00100FF0(g->t, 64.0f, 32.0f);
    func_001A6970(func_0020B550((u16)(g->t % 64 << 16 >> 6)));
    w = 1.0f;
    r = s * w;
    tri.v[0].c.r = 0xFF;
    tri.v[0].c.g = 0xFF;
    tri.v[0].c.b = 0xFF;
    tri.v[0].c.a = (u32)(255.0f * r);
    tri.v[0].c.q = 1.0f;
    tri.v[1].c = tri.v[0].c;
    tri.v[2].c = tri.v[0].c;
    c = tri.v[0].c;
    pk.v[0].c = c;
    pk.v[1].c = c;
    pk.v[2].c = c;
    pk.v[3].c = c;
    t = g->t;
    for (i = 0; i < 32; i++) {
        rad = 45.0f * (f32)(32 - i) / 32.0f;
        h = (f32)(i + 1) / 32.0f;
        for (k = 0; k < 17; k++) {
            r = 1.0f + h * (0.2f * func_0020B480((u16)(t * 211 + (((i * 0x20000) >> 5) + ((k * 0x20000) >> 4)))));
            a = (s32)((f32)((k * 0x10000) >> 4) +
                      h * (5461.0f * func_0020B480((u16)(((i * 0x10000) >> 5) + t * 111))));
            g->u.s.hi[i][k].x = rad * r * func_0020B550(a);
            g->u.s.hi[i][k].y = rad * r * func_0020B480(a);
            g->u.s.hi[i][k].z = 0.0f;
            g->u.s.hi[i][k].w = 1.0f;
        }
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    for (i = 0; i < 32; i++) {
        if (i == 31) {
            for (k = 0; k < 16; k++) {
                if (func_00100B00(&v, &g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], m, &tri, &depth) == 1) {
                    func_00100C60(&tri.v[0].s, &tri.v[0].p, 0, 0);
                    func_00100C60(&tri.v[1].s, &tri.v[1].p, 0, 0);
                    func_00100C60(&tri.v[2].s, &tri.v[2].p, 0, 0);
                    if (func_00100B00(&v, &g->u.lo[i][k], &g->u.lo[i][k + 1], m, &tri, &depth) == 1) {
                        tri.v[0].p.z = 0xFFFFF8;
                        tri.v[1].p.z = tri.v[0].p.z;
                        tri.v[2].p.z = tri.v[0].p.z;
                        p = func_00207650(p, &tri, 0, 0);
                    }
                }
            }
        } else {
            for (k = 0; k < 16; k++) {
                if (func_00100BA0(&g->u.s.hi[i][k], &g->u.s.hi[i][k + 1], &g->u.s.hi[i + 1][k],
                                  &g->u.s.hi[i + 1][k + 1], m, &pk, &depth) == 1) {
                    func_00100C60(&pk.v[0].s, &pk.v[0].p, 0, 0);
                    func_00100C60(&pk.v[1].s, &pk.v[1].p, 0, 0);
                    func_00100C60(&pk.v[2].s, &pk.v[2].p, 0, 0);
                    func_00100C60(&pk.v[3].s, &pk.v[3].p, 0, 0);
                    if (func_00100BA0(&g->u.lo[i][k], &g->u.lo[i][k + 1], &g->u.lo[i + 1][k],
                                      &g->u.lo[i + 1][k + 1], m, &pk, &depth) == 1) {
                        pk.v[0].p.z = 0xFFFFF8;
                        pk.v[1].p.z = pk.v[0].p.z;
                        pk.v[2].p.z = pk.v[0].p.z;
                        pk.v[3].p.z = pk.v[0].p.z;
                        p = func_00207650(p, &pk, 0, 0);
                    }
                }
            }
        }
    }
    func_00209F70(p, 0);
}

#pragma optimization_level reset
