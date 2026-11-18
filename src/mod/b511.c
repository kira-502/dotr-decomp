#include "common.h"

/* shape b511:01E00080 (b511), 3705 insns, 1 copy (-O3,p): b511 scene manager, b739:01E00080's relative: six joints
   with two aim matrices, a blur fan at frame 0x157, blade quads and sparks every fourth frame, a render-to-texture
   cone, a second blade and spark volley and a triple burst */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b511_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b511_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b511_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b511_01E00080 c;
    Uv_b511_01E00080 uv0;
    Xyz_b511_01E00080 p0;
    Uv_b511_01E00080 uv1;
    Xyz_b511_01E00080 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b511_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b511_01E00080 c;
        Uv_b511_01E00080 uv;
        Xyz_b511_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b511_01E00080;

typedef struct {
    Rgbaq_b511_01E00080 c;
    f32 s, t;
    Xyz_b511_01E00080 p;
} Tv_b511_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b511_01E00080 v[4];
    u8 tail[0x20];
} Quad_b511_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b511_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f w[128];
    u8 c2[64];
    Vec4f v3[64];
} Burst_b511_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[2];
    Vec4f pos[2];
    Mtx_b511_01E00080 mtx[2];
} Blade1_b511_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Spark1_b511_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[1];
    u8 padC[4];
    Vec4f pos[1];
} Blade_b511_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][64];
    u8 pad48[8];
    Vec4f pos[1];
    Vec4f v[1][64];
} Spark_b511_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr;
    s32 jn[6];
    u8 pad68[8];
    Vec4f jp[6];
    Mtx_b511_01E00080 mtx[2];
    s32 cur1;
    u8 pad154[0xC];
    Vec4f grid1[8][16][4];
    u8 gc1[8][16];
    Blade1_b511_01E00080 blade1[3];
    s32 ns1;
    u8 pad23F4[0xC];
    Spark1_b511_01E00080 spark1[16];
    u8 on2;
    u8 pad3801[3];
    s32 t2;
    u8 pad3808[8];
    Vec4f cone[32][17];
    Vec4f cone2[32][17];
    s32 nb;
    u8 pad7C14[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Blade_b511_01E00080 blade[1];
    s32 ns;
    u8 pad9CC4[0xC];
    Spark_b511_01E00080 spark[1];
    s32 cur;
    u8 padA134[0xC];
    Burst_b511_01E00080 burst[1];
    u8 on3;
    u8 padB221[3];
    s32 t3;
    u8 padB228[8];
} Scene_b511_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b511(s32 arg0, s32 code) {
    Scene_b511_01E00080 *g = (Scene_b511_01E00080 *)arg0;
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
    extern void func_00100E40(void *, void *);
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
    extern void b511_01E03A70();
    extern s32 D_01E04380_b511;
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 l;
    u8 a2;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 c;
    s32 sn;
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
    f32 w1;
    f32 w0;
    f32 u1;
    f32 u2;
    f32 w3;
    f32 w2;
    f32 u3;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b511_01E00080 m4;
    Vec4f v;
    Spr_b511_01E00080 spr __attribute__((aligned(8)));
    Tri_b511_01E00080 tri __attribute__((aligned(8)));
    Quad_b511_01E00080 pk __attribute__((aligned(8)));
    Xyz_b511_01E00080 xyz;
    f32 depth;
    u8 col[4] __attribute__((aligned(4)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB230);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 0xF, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x10, 0);
        g->jn[2] = func_001F5560(g->unitA, 0x20, 0);
        g->jn[3] = func_001F5560(g->unitA, 0x21, 0);
        g->jn[4] = func_001F5560(g->unitA, 0x1A, 0);
        g->jn[5] = func_001F5560(g->unitA, 0x19, 0);
        g->cur1 = 0;
        for (i = 0; i < 8; i++) {
            h = -30.0f * (i + 1) / 8.0f;
            f = -30.0f * i / 7.0f;
            s = 2.0f * (8 - (i + 1)) / 7.0f;
            for (j = 0; j < 16; j++) {
                ang = ((j << 16) >> 4) + ((i << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid1[i][j][0].x = -1.0f;
                g->grid1[i][j][0].y = 0.0f;
                g->grid1[i][j][0].z = 0.0f;
                g->grid1[i][j][0].w = 1.0f;
                g->grid1[i][j][1].x = 1.0f;
                g->grid1[i][j][1].y = 0.0f;
                g->grid1[i][j][1].z = 0.0f;
                g->grid1[i][j][1].w = 1.0f;
                g->grid1[i][j][2].x = -1.0f;
                g->grid1[i][j][2].y = 0.0f;
                g->grid1[i][j][2].z = h;
                g->grid1[i][j][2].w = 1.0f;
                g->grid1[i][j][3].x = 1.0f;
                g->grid1[i][j][3].y = 0.0f;
                g->grid1[i][j][3].z = h;
                g->grid1[i][j][3].w = 1.0f;
                for (c = 0; c < 4; c++) {
                    func_001878E0(&g->grid1[i][j][c], &m4, &g->grid1[i][j][c]);
                }
                g->gc1[i][j] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (c = 0; c < 3; c++) {
            g->blade1[c].on = 0;
        }
        g->ns1 = 0;
        for (i = 0; i < 16; i++) {
            g->spark1[i].on = 0;
        }
        k = 0;
        g->on2 = k;
        for (c = 0; c < 32; c++) {
            r = 35.0f * (32 - c) / 32.0f;
            for (k = 0; k < 17; k++) {
                g->cone[c][k].x = r * func_0020B550((k << 16) >> 4);
                g->cone[c][k].y = r * func_0020B480((k << 16) >> 4);
                g->cone[c][k].z = 0.0f;
                g->cone[c][k].w = 1.0f;
            }
        }
        col[2] = 0;
        col[1] = 0;
        col[0] = 0;
        col[3] = 0x80;
        func_001F63F0(g->unitA, 1, col);
        g->nb = 0;
        for (q = 0; q < 8; q++) {
            h = -80.0f * (q + 1) / 8.0f;
            f = -1.0f * (-80.0f * q / 7.0f * (f32)g->obj);
            s = 5.0f * (8 - (q + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                ang = ((i << 16) >> 4) + ((q << 13) >> 3) & 0xFFFF;
                v.x = s * func_0020B550(ang);
                v.y = s * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[q][i][0].x = -2.0f;
                g->grid[q][i][0].y = 0.0f;
                g->grid[q][i][0].z = 0.0f;
                g->grid[q][i][0].w = 1.0f;
                g->grid[q][i][1].x = 2.0f;
                g->grid[q][i][1].y = 0.0f;
                g->grid[q][i][1].z = 0.0f;
                g->grid[q][i][1].w = 1.0f;
                g->grid[q][i][2].x = -2.0f;
                g->grid[q][i][2].y = 0.0f;
                g->grid[q][i][2].z = h;
                g->grid[q][i][2].w = 1.0f;
                g->grid[q][i][3].x = 2.0f;
                g->grid[q][i][3].y = 0.0f;
                g->grid[q][i][3].z = h;
                g->grid[q][i][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[q][i][k], &m4, &g->grid[q][i][k]);
                }
                g->gc[q][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 1; i++) {
            g->blade[i].on = 0;
        }
        g->ns = 0;
        for (k = 0; k < 1; k++) {
            g->spark[k].on = 0;
        }
        g->cur = 0;
        for (i = 0; i < 1; i++) {
            g->burst[i].on = 0;
        }
        g->on3 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (k = 0; k < 6; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    for (q = 0; q < 2; q++) {
        n = q * 2;
        func_00187B18((void *)&v, &g->jp[n + 1], &g->jp[n]);
        func_00100E40(&g->mtx[q], &v);
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
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

    if (g->t == 0x157) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b511_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b511_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b511_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b511_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b511_01E00080 *)(s32)&tri)->flags |= 0x800;
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
        for (q = 0; q < 8; q++) {
            r = 1.0f + 0.15f * (8 - q) / 8.0f;
            for (j = 0; j < 8; j++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b511_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b511_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b511_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b511_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b511_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b511_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
                func_00187B48(&out[0], &out[0], r);
                func_00187B48(&out[1], &out[1], r);
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
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    if (g->t % 4 == 0 && g->t > 0x7A && g->t < 0xFA) {
        i = g->cur1;
        (void)i;
        g->blade1[i].on = 1;
        g->blade1[i].t = 0;
        sn = g->ns1;
        (void)sn;
        g->spark1[sn].on = 1;
        g->spark1[sn].t = 0;
        for (q = 0; q < 2; q++) {
            n = q * 2 + 1;
            g->blade1[i].rot[q] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade1[i].pos[q] = g->jp[n];
            g->blade1[i].mtx[q] = g->mtx[q];
        }
        for (k = 0; k < 2; k++) {
            q = k * 2 + 1;
            g->spark1[sn].pos[k] = g->jp[q];
            for (i = 0; i < 8; i++) {
                g->spark1[sn].c[k][i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark1[sn].v[k][i], 0.3f);
            }
        }
        g->cur1++;
        if (g->cur1 >= 3) {
            g->cur1 = 0;
        }
        g->ns1++;
        if (g->ns1 >= 16) {
            g->ns1 = 0;
        }
    }

    ((Quad_b511_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b511_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b511_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b511_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (q = 0; q < 3; q++) {
        if (g->blade1[q].on == 0) {
            continue;
        }
        alpha = (3 - g->blade1[q].t) * 0x56 / 3;
        pk.v[0].c.r = 0x40;
        pk.v[0].c.g = 0x30;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade1[q].t / 3.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (l = 0; l < 2; l++) {
            func_0020EB40(m);
            k = l * 2 + 1;
            func_00187B60(m2, (void *)&g->blade1[q].mtx[l], &g->jp[k]);
            func_00100E00(m2, g->blade1[q].rot[l], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (k = 0; k < 8; k++) {
                for (c = 0; c < 16; c++) {
                    n = g->gc1[k][c];
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
                    if (func_002058D0(g->grid1[k][c], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 40.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade1[q].t, 3, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x4C;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (c = 0; c < 2; c++) {
            v = g->blade1[q].pos[c];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade1[q].t++;
        if (g->blade1[q].t > 3) {
            g->blade1[q].on = 0;
        }
    }

    ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (q = 0; q < 16; q++) {
        if (g->spark1[q].on == 0) {
            continue;
        }
        r = 5.0f * (0.5f + 0.5f * g->spark1[q].t / 16.0f);
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
        s = func_00100D50(g->spark1[q].t, 16, 1);
        for (i = 0; i < 2; i++) {
            for (k = 0; k < 8; k++) {
                func_00187B48(&v, &g->spark1[q].v[i][k], s);
                func_00187B00(&v, &v, &g->spark1[q].pos[i]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark1[q].c[i][k] % 4 * 32;
                y = (g->spark1[q].c[i][k] >> 2) * 32;
                ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark1[q].t++;
        if (g->spark1[q].t > 16) {
            g->spark1[q].on = 0;
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
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        buf = func_00207F60();
        func_00208460();
        D_01E04380_b511 = (s32)g;
        func_001F7070(1, &spr.txa, &spr.txb, 0, b511_01E03A70);
        func_00208460();
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        x = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
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
        if (g->t2 > 0x30) {
            g->on2 = 0;
            func_001F63F0(g->unitA, 0, 0);
        }
    }

    if (g->t == 0x126) {
        i = g->nb;
        (void)i;
        g->blade[i].on = 1;
        g->blade[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (k = 0; k < 1; k++) {
            g->blade[i].rot[k] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade[i].pos[k] = g->jp[4];
            g->spark[c].pos[k] = g->jp[4];
            for (l = 0; l < 64; l++) {
                g->spark[c].c[k][l] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[k][l], 1.0f);
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

    ((Quad_b511_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b511_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b511_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b511_01E00080 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (k = 0; k < 1; k++) {
        if (g->blade[k].on == 0) {
            continue;
        }
        alpha = (10 - g->blade[k].t) * 0x56 / 10;
        pk.v[0].c.r = 0x40;
        pk.v[0].c.g = 0xFF;
        pk.v[0].c.b = 0x30;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        s = 0.5f + 0.5f * g->blade[k].t / 10.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (x = 0; x < 1; x++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->blade[k].pos[x]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->blade[k].rot[x], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (j = 0; j < 8; j++) {
                for (c = 0; c < 16; c++) {
                    l = g->gc[j][c];
                    ang = l % 4 * 32;
                    y = (l >> 2) * 32;
                    u2 = ang / 128.0f;
                    u3 = (32.0f + ang) / 128.0f;
                    w3 = y / 64.0f;
                    w2 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u2;
                    pk.v[0].t = w2;
                    pk.v[1].s = u3;
                    pk.v[1].t = w2;
                    pk.v[2].s = u2;
                    pk.v[2].t = w3;
                    pk.v[3].s = u3;
                    pk.v[3].t = w3;
                    if (func_002058D0(g->grid[j][c], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 90.0f;
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
        alpha = (u32)(0.0f * func_00100D50(g->blade[k].t, 10, 1));
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0xB0;
        spr.c.b = 0x78;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (n = 0; n < 1; n++) {
            v = g->blade[k].pos[n];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade[k].t++;
        if (g->blade[k].t > 10) {
            g->blade[k].on = 0;
        }
    }

    ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (c = 0; c < 1; c++) {
        if (g->spark[c].on == 0) {
            continue;
        }
        r = 10.0f * (0.5f + 0.5f * g->spark[c].t / 32.0f);
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
        s = func_00100D50(g->spark[c].t, 32, 1);
        for (i = 0; i < 1; i++) {
            for (q = 0; q < 64; q++) {
                func_00187B48(&v, &g->spark[c].v[i][q], s);
                func_00187B00(&v, &v, &g->spark[c].pos[i]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[c].c[i][q] % 4 * 32;
                y = (g->spark[c].c[i][q] >> 2) * 32;
                ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[c].t++;
        if (g->spark[c].t > 32) {
            g->spark[c].on = 0;
        }
    }

    if (g->t == 0x157) {
        for (q = 0; q < 1; q++) {
            g->cur = q;
            g->burst[g->cur].on = 1;
            g->burst[g->cur].t = 1;
            g->burst[g->cur].pos.x = 0.0f;
            g->burst[g->cur].pos.y = 0.0f;
            g->burst[g->cur].pos.z = 0.0f;
            g->burst[g->cur].pos.w = 1.0f;
            func_00187B00(&g->burst[g->cur].pos, &g->burst[g->cur].pos, &g->tgt);
            for (n = 0; n < 64; n++) {
                g->burst[g->cur].c[n] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst[g->cur].v[n], 2.7f);
            }
            for (j = 0; j < 128; j++) {
                func_00101080(&g->burst[g->cur].w[j], 3.75f);
            }
            for (l = 0; l < 64; l++) {
                g->burst[g->cur].c2[l] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[g->cur].v3[l], 2.7f);
            }
        }
    }

    for (i = 0; i < 1; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 18.0f * (0.8f + 0.2f * g->burst[i].t / 48.0f);
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
        alpha = (0x30 - g->burst[i].t) * 0xC8 / 48;
        spr.c.r = 0x6C;
        spr.c.g = 0xFF;
        spr.c.b = 0x38;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[i].t, 0x30, 1);
        for (l = 0; l < 64; l++) {
            func_00187B48(&v, &g->burst[i].v3[l], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c2[l] % 4 * 32;
            y = (g->burst[i].c2[l] >> 2) * 32;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->burst[i].t / 48.0f);
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
        alpha = (0x30 - g->burst[i].t) * 0xFF / 48;
        a2 = (0x30 - g->burst[i].t) * 0x80 / 48;
        for (q = 0; q < 64; q++) {
            s = func_00100D50(g->burst[i].t, 0x30, 1);
            if (q % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x5A;
                spr.c.g = 0xFF;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[i].v[q], s);
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[i].c[q] % 4 * 32;
            y = (g->burst[i].c[q] >> 2) * 32;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[i].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[i].t, 0x30, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (u32)(200.0f * ((f32)(0x30 - g->burst[i].t) / 48.0f));
        spr.c.r = 0x5E;
        spr.c.g = 0xFF;
        spr.c.b = 0x3A;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 195.0f;
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
        ((Spr_b511_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b511_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b511_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b511_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b511_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b511_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b511_01E00080 *)(s32)&spr.uv1)->v = 0x200;
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
        h = func_00100D50(g->burst[i].t, 0x30, 1);
        for (n = 0; n < 128; n++) {
            for (k = 0; k < 6; k++) {
                spr.c.r = 0xFF;
                spr.c.g = 0xF0;
                spr.c.b = 0x80;
                spr.c.a = 0;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[i].w[n], h + 0.007f * k);
                func_00187B00(&v, &v, &g->burst[i].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 0x30) {
            g->burst[i].on = 0;
        }
    }

    func_001F6D00((u8)((func_00101050(0x1A7 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x14D) {
        ret = 1;
    } else {
        if (g->t > 0x157 && g->t < 0x187) {
            ret = 6;
        }
        if (g->t == 0x187) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x1A7) {
        ret = 8;
    }
    return ret;
}

/* shape b511:01E03A70, 547 insns, 1 copy (-O3,p): draws a two-layer 32x17 cone grid: a sine-rippled ring grid fading
   with the timer, triangles to an apex for the last row, textured quads elsewhere, each drawn where both layers
   project */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b511_01E03A70;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b511_01E03A70;

typedef struct {
    Rgbaq_b511_01E03A70 c;
    f32 s, t;
    Xyz_b511_01E03A70 p;
} Tv_b511_01E03A70;

typedef struct {
    u64 d;
} Reg_b511_01E03A70;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b511_01E03A70 v[3];
    u64 pad58;
    Reg_b511_01E03A70 tex0;
    Reg_b511_01E03A70 tex1;
    u64 tail;
} Tri_b511_01E03A70;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b511_01E03A70 v[4];
    u64 pad70;
    Reg_b511_01E03A70 tex0;
    Reg_b511_01E03A70 tex1;
    u64 tail;
} Quad_b511_01E03A70;

typedef struct {
    u8 pad0[0x30];
    Vec4f pos;
    u8 pad40[0x37C4];
    s32 t;
    u8 pad2CF8[8];
    union {
        Vec4f lo[40][17];
        struct {
            u8 pad[0x2200];
            Vec4f hi[32][17];
        } s;
    } u;
} Obj_b511_01E03A70;

extern Obj_b511_01E03A70 *D_01E04380_b511;

#pragma optimization_level 3

static void func_01E03A70_b511(void *buf) {
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void *func_00207650(void *, void *, s32, s32);
    Obj_b511_01E03A70 *g __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f v;
    Tri_b511_01E03A70 tri __attribute__((aligned(8)));
    Quad_b511_01E03A70 pk __attribute__((aligned(8)));
    Rgbaq_b511_01E03A70 c;
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

    g = D_01E04380_b511;
    p = func_00209F70(buf, 0xFF000000);
    func_00205CA0((s32)m3);
    func_0020EB40(m);
    v = g->pos;
    func_00187B60(m2, m3, &v);
    func_0020BC00((s32)m, m2);
    ((Tri_b511_01E03A70 *)(s32)&tri)->flags = 0x33;
    ((Tri_b511_01E03A70 *)(s32)&tri)->size = 9;
    ((Tri_b511_01E03A70 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b511_01E03A70 *)(s32)&tri)->pad4 = 0;
    ((Quad_b511_01E03A70 *)(s32)&pk)->flags = 0x34;
    ((Quad_b511_01E03A70 *)(s32)&pk)->size = 0xC;
    ((Quad_b511_01E03A70 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b511_01E03A70 *)(s32)&pk)->pad4 = 0;
    p = (void *)func_00208870(func_0020F290((s32)p), -1, 1, &tri.tex0, &tri.tex1);
    pk.tex0 = tri.tex0;
    pk.tex1 = tri.tex1;
    p = (void *)func_0020F290((s32)p);
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((s64)0x700 << 32) | 0xA0000A);
    ((Tri_b511_01E03A70 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Quad_b511_01E03A70 *)(s32)&pk)->flags |= 0x800;
    s = func_00100FF0(g->t, 48.0f, 24.0f);
    func_001A6C48(func_001A6970(func_0020B550((u16)(g->t % 64 << 16 >> 6))), 3.0f);
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
        rad = 35.0f * (f32)(32 - i) / 32.0f;
        h = (f32)(i + 1) / 32.0f;
        for (k = 0; k < 17; k++) {
            r = 1.0f + h * (0.3f * func_0020B480((u16)(t * 211 + (((i * 0x20000) >> 5) + ((k * 0x20000) >> 4)))));
            a = (s32)((f32)((k * 0x10000) >> 4) +
                      h * (5461.0f * func_0020B480((u16)(((i * 0x4000) >> 5) + t * 111))));
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
