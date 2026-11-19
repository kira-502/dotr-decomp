#include "common.h"

/* shape b373:01E00080 (b373), 4620 insns, 1 copy (-O3,p): b373 scene manager, b612:01E00080's form plus a wall-and-
   floor room and a 512-point cloud: setup builds floor, walls, sphere grid and colours; else fades, rays, sprites,
   fans, shards, room, cloud, ring and dust effects; returns 1 at 0x100, 6 in 0x10B..0x1B2, 3 at 0x1B3, 8 when the
   timer ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b373_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b373_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b373_01E00080 c;
    Xyz_b373_01E00080 v[2];
    u64 tail;
} Flat_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b373_01E00080 c;
    Uv_b373_01E00080 uv0;
    Xyz_b373_01E00080 p0;
    Uv_b373_01E00080 uv1;
    Xyz_b373_01E00080 p1;
    u64 pad38;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Spr_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b373_01E00080 c;
        f32 s, t;
        Xyz_b373_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Quad_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b373_01E00080 c;
        Uv_b373_01E00080 uv;
        Xyz_b373_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b373_01E00080 c;
    struct {
        union {
            Uv_b373_01E00080 uv;
            struct {
                f32 s, t;
            } st;
        };
        Xyz_b373_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Tex_b373_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b373_01E00080;


typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 life[2][6];
    f32 w[2][6];
    f32 len[2][6];
    f32 amp[2][6];
    u8 padC8[8];
    Mtx_b373_01E00080 m[2][6];
} Fan_b373_01E00080;

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
} Shard_b373_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][32];
    u8 pad28[8];
    Vec4f pos[1];
    Vec4f v[1][32];
} Dust_b373_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[1][512];
    u8 pad208[8];
    Vec4f pos[1];
    Vec4f v[1][512];
} Cloud_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b373_01E00080 c;
    Xyz_b373_01E00080 p[4];
    u64 tail;
} Line_b373_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b373_01E00080 c;
        Xyz_b373_01E00080 p;
    } v[4];
    u64 tail;
} Gou_b373_01E00080;

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
    s32 jn2[2];
    u8 padB8[8];
    Vec4f jp2[2];
    Vec4f floor[21][21];
    s32 rnd[21][21];
    u8 on8;
    u8 pad2355[3];
    s32 t8;
    u8 pad235C[4];
    Vec4f wall[4][17][2];
    u8 on;
    u8 pad2BE1[3];
    s32 t1;
    u8 pad2BE8[8];
    Vec4f grid[17][17];
    u8 on2;
    u8 pad3E01[3];
    s32 t2;
    u8 col[9][4];
    u8 pad3E2C[4];
    Fan_b373_01E00080 fan[16];
    u8 on3;
    u8 pad7B31[3];
    s32 t3;
    u8 on4;
    u8 pad7B39[3];
    s32 t4;
    u8 on5;
    u8 pad7B41[3];
    s32 t5;
    u8 on6;
    u8 pad7B49[3];
    s32 t6;
    Shard_b373_01E00080 shard[4];
    Dust_b373_01E00080 dust[2];
    Cloud_b373_01E00080 cloud[1];
    u8 on7;
    u8 padB071[3];
    s32 t7;
    u8 padB078[8];
} Scene_b373_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b373(s32 arg0, s32 code) {
    Scene_b373_01E00080 *g = (Scene_b373_01E00080 *)arg0;
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
    extern f32 func_001A6970(f32);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void b373_01E048B0();
    extern void b373_01E04DE0();
    extern s32 D_01E04F00_b373;
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
    Flat_b373_01E00080 flat __attribute__((aligned(8)));
    Spr_b373_01E00080 spr __attribute__((aligned(8)));
    Quad_b373_01E00080 pk __attribute__((aligned(8)));
    Tri_b373_01E00080 tri __attribute__((aligned(8)));
    Tex_b373_01E00080 tx __attribute__((aligned(8)));
    Line_b373_01E00080 ln __attribute__((aligned(8)));
    Gou_b373_01E00080 gq __attribute__((aligned(8)));
    Xyz_b373_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB080);
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
        g->jn[0] = func_001F5560(g->unitA, 0xF, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x13, 0);
        g->jn2[0] = func_001F5560(g->unitA, 6, 0);
        g->jn2[1] = func_001F5560(g->unitA, 9, 0);
        for (i = 0; i < 21; i++) {
            s = 900.0f * i / 20.0f;
            for (j = 0; j < 21; j++) {
                h = 900.0f * j / 20.0f;
                g->floor[i][j].x = s - 450.0f;
                g->floor[i][j].y = 0.0f;
                g->floor[i][j].z = h - 450.0f;
                g->floor[i][j].w = 1.0f;
                g->rnd[i][j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            }
        }
        g->on8 = 0;
        r = 450.0f;
        for (i = 0; i < 17; i++) {
            s = 900.0f * i / 16.0f - r;
            g->wall[0][i][0].x = s;
            g->wall[0][i][0].y = 0.0f;
            g->wall[0][i][0].z = -r;
            g->wall[0][i][0].w = 1.0f;
            g->wall[1][i][0].x = s;
            g->wall[1][i][0].y = 0.0f;
            g->wall[1][i][0].z = r;
            g->wall[1][i][0].w = 1.0f;
            g->wall[2][i][0].x = -r;
            g->wall[2][i][0].y = 0.0f;
            g->wall[2][i][0].z = s;
            g->wall[2][i][0].w = 1.0f;
            g->wall[3][i][0].x = r;
            g->wall[3][i][0].y = 0.0f;
            g->wall[3][i][0].z = s;
            g->wall[3][i][0].w = 1.0f;
            for (j = 0; j < 4; j++) {
                g->wall[j][i][1] = g->wall[j][i][0];
                g->wall[j][i][1].y = 70.0f;
            }
        }
        g->on = n = 0;
        for (i = 0; i < 17; i++) {
            h = 90.0f * func_0020B480((i << 15) >> 4);
            r = func_001A6C60(func_001A6C48(90.0f, 2.0f) - func_001A6C48(h, 2.0f));
            for (k = 0; k < 17; k++) {
                g->grid[i][k].x = r * func_0020B550((k << 16) >> 4);
                g->grid[i][k].y = h;
                g->grid[i][k].z = r * func_0020B480((k << 16) >> 4);
                g->grid[i][k].w = 1.0f;
            }
        }
        g->on2 = 0;
        g->t2 = 0;
        for (j = 0; j < 9; j++) {
            f = (f32)j / 8.0f;
            h = 1.0f - f;
            s = 128.0f * f;
            r = 128.0f * h;
            a = r + s;
            g->col[j][0] = (u32)a;
            g->col[j][1] = (u32)a;
            g->col[j][2] = (u32)(228.0f * h + s);
            g->col[j][3] = (u32)r;
        }
        for (k = 0; k < 16; k++) {
            g->fan[k].on = 0;
        }
        g->on3 = 0;
        g->on4 = 0;
        g->on5 = 0;
        g->on6 = 0;
        for (k = 0; k < 4; k++) {
            g->shard[k].on = 0;
        }
        for (k = 0; k < 2; k++) {
            g->dust[k].on = 0;
        }
        for (j = 0; j < 1; j++) {
            g->cloud[j].on = 0;
        }
        g->on7 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->posA);
    func_001F53C0(1, g->unitB, &g->posB);
    for (k = 0; k < 2; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    for (k = 0; k < 2; k++) {
        func_001F5620(g->unitA, g->jn2[k], &g->jp2[k]);
        v.x = (f32)g->obj * (-5.0f * (f32)(k % 2 * 2 - 1));
        v.y = -10.0f;
        v.z = -15.0f * (f32)g->obj;
        v.w = 1.0f;
        func_00187B00(&g->jp2[k], &g->jp2[k], &v);
    }
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

    if (g->t == 0xA0 || g->t == 0x10A) {
        g->on6 = 1;
        g->t6 = 0;
    }
    if (g->on6 == 1) {
        ((Flat_b373_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b373_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b373_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b373_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(0));
        alpha = (u32)(128.0f * ((f32)(0x20 - g->t6) / 32.0f));
        flat.c.r = 0xFF;
        flat.c.g = 0xFF;
        flat.c.b = 0xE0;
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

    if (g->t == 0x195) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        if (g->t4 == 0x1E) {
            g->on3 = 0;
            g->on6 = 0;
            g->on8 = 0;
            g->on = 0;
        }
        ((Flat_b373_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b373_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b373_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b373_01E00080 *)(s32)&flat)->pad4 = 0;
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

    if (g->t == 0x195) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b373_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b373_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b373_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b373_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b373_01E00080 *)(s32)&tri)->flags |= 0x800;
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
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
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

    if (g->t > 0x108 && g->t < 0x1B3 && g->t % 2 == 0) {
        g->on5 = 1;
        g->t5 = 0;
    }
    if (g->on5 == 1) {
        ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &spr.tex0, &spr.tex1);
        func_00208460();
        alpha = (u32)(32.0f * (f32)(1 - g->t5));
        spr.c.r = 0xC8;
        spr.c.g = 0xC8;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
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

    if (g->t == 0x109) {
        g->on2 = 1;
        g->t2 = 0;
    }
    w = func_00101020((f32)g->t2, 4.0f) * func_00100FF0((f32)g->t2, 170.0f, 166.0f);
    if (g->on2 == 1) {
        ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[3], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(255.0f * (0.3f + 0.7f * (g->t2 % 2)) * w);
        spr.c.r = 0x30;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
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
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        for (k = 0; k < 2; k++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->jp[k]);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t2++;
        if (g->t2 > 0xAA) {
            g->on2 = 0;
        }
    }

    if (g->t > 0x109 && g->t < 0x1B3) {
        n = g->t % 16;
        g->fan[n].on = 1;
        g->fan[n].t = 0;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 6; i++) {
                g->fan[n].life[j][i] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->fan[n].w[j][i] = 20.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->fan[n].len[j][i] = (f32)g->obj * (-300.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f));
                g->fan[n].amp[j][i] = 20.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                func_0020BBB0(&g->fan[n].m[j][i]);
                func_00100E00(&g->fan[n].m[j][i], ((func_0019A5C8() >> 23) % 256 * 0x238E >> 8) - 0x11C7, 1);
                func_00100E00(&g->fan[n].m[j][i], ((func_0019A5C8() >> 23) % 256 * 0x238E >> 8) - 0x11C7, 0);
                func_00100E00(&g->fan[n].m[j][i], (i << 16) / 6, 2);
            }
        }
    }

    ((Quad_b373_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b373_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b373_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b373_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[2], 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 16; i++) {
        if (g->fan[i].on == 0) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 6; k++) {
                if (g->fan[i].t > g->fan[i].life[j][k]) {
                    continue;
                }
                func_0020EB40(m);
                func_0020C940(m2, NULL, NULL, &g->jp[j]);
                func_0020BC00(m2, &g->fan[i].m[j][k]);
                func_0020BC00(m, m2);
                h = 1.0f - func_00100D50(g->fan[i].t, g->fan[i].life[j][k], 1);
                e = (32.0f * (k % 4)) / 128.0f;
                z0 = 0.25f + e;
                ph = i * 0xD05 + j * 0x115C + k * 0x15B3;
                for (l = 0; l < 8; l++) {
                    z1 = 1.0f + (1.0f - h);
                    alpha = (u32)(w * ((u32)g->col[l][3] * h));
                    a2 = (u32)(w * ((u32)g->col[l + 1][3] * h));
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
                    x0 = l / 8.0f;
                    s1 = (l + 1) / 8.0f;
                    r = g->fan[i].len[j][k] * x0;
                    a = g->fan[i].w[j][k] * h;
                    f = g->fan[i].len[j][k] * s1;
                    s0 = x0 * (z1 * (g->fan[i].amp[j][k] * func_0020B550((ph + ((l << 16) >> 3)) & 0xFFFF)));
                    x1 = s1 * (z1 * (g->fan[i].amp[j][k] * func_0020B550((ph + (((l + 1) << 16) >> 3)) & 0xFFFF)));
                    cn[0].x = s0;
                    cn[0].y = -a + s0;
                    cn[0].z = r;
                    cn[0].w = 1.0f;
                    cn[1].x = s0;
                    cn[1].y = a + s0;
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

    if (g->t > 0x10A && g->t < 0x1B3) {
        n = g->t % 4;
        g->shard[n].on = 1;
        g->shard[n].t = 0;
        for (y = 0; y < 32; y++) {
            g->shard[n].life[y] = (s32)(4.0f * (0.3f + 0.7f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->shard[n].size[y] = 15.0f * (0.3f + 0.7f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->shard[n].ang[y] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->shard[n].pos = g->posB;
            func_00101080(&g->shard[n].v[y], 2.5f);
        }
    }

    ((Tex_b373_01E00080 *)(s32)&tx)->flags = 0x24;
    ((Tex_b373_01E00080 *)(s32)&tx)->size = 9;
    ((Tex_b373_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
    ((Tex_b373_01E00080 *)(s32)&tx)->pad4 = 0;
    ((Tex_b373_01E00080 *)(s32)&tx)->flags |= 0x800;
    func_002086D0(&tx, func_00208D00(1));
    func_00208700(&tx, g->tex[5], 1);
    func_00208CB0(&tx, ((u64)0x3FC << 32) | 0x811FC0BA);
    ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    for (i = 0; i < 4; i++) {
        if (g->shard[i].on == 0) {
            continue;
        }
        for (l = 0; l < 32; l++) {
            if (g->shard[i].t > g->shard[i].life[l]) {
                continue;
            }
            h = func_0020B480((g->shard[i].t << 14) / g->shard[i].life[l]);
            alpha = (u32)(64.0f * h);
            tx.c.r = 0x40;
            tx.c.g = 0x80;
            tx.c.b = 0xFF;
            tx.c.a = alpha;
            tx.c.q = 1.0f;
            alpha = (u32)(255.0f * h);
            spr.c.r = 0x20;
            spr.c.g = 0x40;
            spr.c.b = 0xFF;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            x = l % 4 % 2 * 0x3B + 0xA;
            y = l % 4 / 2 * 64 + 0x80;
            ((Uv_b373_01E00080 *)(s32)&tx.v[0].uv)->u = x << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[0].uv)->v = y << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[1].uv)->u = (x + 0x3B) << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[1].uv)->v = y << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[2].uv)->u = x << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[2].uv)->v = (y + 0x40) << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[3].uv)->u = (x + 0x3B) << 4;
            ((Uv_b373_01E00080 *)(s32)&tx.v[3].uv)->v = (y + 0x40) << 4;
            x = l % 8 % 4 * 32;
            y = (l % 8 >> 2) * 32;
            ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            r = g->shard[i].size[l];
            h = 0.5f * r * func_0020B550((g->shard[i].t << 14) / g->shard[i].life[l]);
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
            func_00187B00(&v, &g->shard[i].v[l], &g->shard[i].pos);
            func_00187B60(m2, m3, &v);
            func_00100E00(m2, g->shard[i].ang[l], 2);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &tx, &depth) == 1) {
                if (g->t >= 0x142) {
                    tx.v[0].p.z = 0xFFFFF8;
                    tx.v[1].p.z = tx.v[0].p.z;
                    tx.v[2].p.z = tx.v[0].p.z;
                    tx.v[3].p.z = tx.v[0].p.z;
                }
                func_002075F0(&tx, ot, 0);
            }
            r = 0.1f * g->shard[i].size[l];
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_0020EB40(m);
            func_00187B48(&v, &g->shard[i].v[l], -1.0f * (0.8f + 0.2f * g->shard[i].t / (f32)g->shard[i].life[l]));
            func_00187B00(&v, &v, &g->shard[i].pos);
            func_00187B60(m2, m3, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                if (g->t >= 0x142) {
                    spr.p0.z = 0xFFFFF8;
                    spr.p1.z = spr.p0.z;
                }
                func_002075F0(&spr, ot, 0);
            }
        }
        g->shard[i].t++;
        if (g->shard[i].t > 4) {
            g->shard[i].on = 0;
        }
    }

    if (g->t == 0xA0) {
        g->on8 = 1;
        g->t8 = 0;
    }
    if (g->on8 == 1) {
        ((Tex_b373_01E00080 *)(s32)&tx)->flags = 0x24;
        ((Tex_b373_01E00080 *)(s32)&tx)->size = 9;
        ((Tex_b373_01E00080 *)(s32)&tx)->regs = ((u64)4 << 32) | 0x24242421;
        ((Tex_b373_01E00080 *)(s32)&tx)->pad4 = 0;
        func_002086D0(&tx, func_00208D00(0));
        func_00208700(&tx, g->tex[0], 1);
        func_00208CB0(&tx, 0);
        ((Line_b373_01E00080 *)(s32)&ln)->flags = 4;
        ((Line_b373_01E00080 *)(s32)&ln)->size = 5;
        ((Line_b373_01E00080 *)(s32)&ln)->regs = 0x44441;
        ((Line_b373_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        ((Gou_b373_01E00080 *)(s32)&gq)->flags = 0x14;
        ((Gou_b373_01E00080 *)(s32)&gq)->size = 8;
        ((Gou_b373_01E00080 *)(s32)&gq)->regs = 0x41414141;
        ((Gou_b373_01E00080 *)(s32)&gq)->pad4 = 0;
        func_002086D0(&gq, func_00208D00(1));
        w = func_00100FF0((f32)g->t8, 4350.0f, 4318.0f);
        f = func_00101050(0x38 - g->t8, 0, 8) / 8.0f;
        h = (0.9f + 0.1f * (g->t8 % 2)) * f;
        alpha = (u32)(128.0f * h);
        ln.c.r = 0xFF;
        ln.c.g = 0xFF;
        ln.c.b = 0xE0;
        ln.c.a = alpha;
        ln.c.q = 1.0f;
        if (g->t8 < 0x38) {
            alpha = (u32)(255.0f * h);
            gq.v[0].c.r = 0xFF;
            gq.v[0].c.g = 0xFF;
            gq.v[0].c.b = 0xE0;
            gq.v[0].c.a = alpha;
            gq.v[0].c.q = 1.0f;
            gq.v[1].c = gq.v[0].c;
            gq.v[2].c.r = 0;
            gq.v[2].c.g = 0;
            gq.v[2].c.b = 0;
            gq.v[2].c.a = 0;
            gq.v[2].c.q = 1.0f;
            gq.v[3].c = gq.v[2].c;
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 1.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 16; j++) {
                    if (func_00100BA0(&g->wall[i][j][0], &g->wall[i][j + 1][0], &g->wall[i][j][1], &g->wall[i][j + 1][1],
                                      m, &gq, &depth) == 1) {
                        func_002075F0(&gq, ot, (u32)depth);
                    }
                }
            }
        }
        w = 70.0f * w;
        for (n = 0; n < 1; n++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            v.x = 0.0f;
            v.y = 15.0f - 2.0f * (7.0f * n);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B60(m2, m2, &v);
            func_0020BC00(m, m2);
            if (n == 0) {
                alpha = (u32)w;
            } else {
                alpha = (u32)w;
            }
            tx.c.r = 0x8C;
            tx.c.g = 0x8C;
            tx.c.b = 0xB4;
            tx.c.a = alpha;
            tx.c.q = 1.0f;
            for (i = 0; i < 21; i++) {
                for (y = 0; y < 21; y++) {
                    g->floor[i][y].y = 7.0f * func_0020B550((g->rnd[i][y] + n * 0x33333 + g->t8 * 0x457) & 0xFFFF);
                }
            }
            x = (n % 2 * 2 - 1) * (((g->t8 + n * 32) % 128) << 16 >> 7) & 0xFFFF;
            t0 = 0.2f * func_0020B550(x);
            s1 = 0.2f * func_0020B480(x);
            for (i = 0; i < 20; i++) {
                z0 = (i % 2) / 2.0f;
                z1 = (i % 2 + 1) / 2.0f;
                s0 = z0 + s1;
                t1 = z1 + s1;
                for (l = 0; l < 20; l++) {
                    z0 = (l % 2) / 2.0f;
                    z1 = (l % 2 + 1) / 2.0f;
                    x0 = z0 + t0;
                    x1 = z1 + t0;
                    tx.v[0].st.s = x0;
                    tx.v[0].st.t = s0;
                    tx.v[1].st.s = x1;
                    tx.v[1].st.t = s0;
                    tx.v[2].st.s = x0;
                    tx.v[2].st.t = t1;
                    tx.v[3].st.s = x1;
                    tx.v[3].st.t = t1;
                    if (func_00100BA0(&g->floor[i][l], &g->floor[i][l + 1], &g->floor[i + 1][l], &g->floor[i + 1][l + 1],
                                      m, &tx, &depth) == 1) {
                        if (g->t8 < 0x38) {
                            ln.p[0] = tx.v[0].p;
                            ln.p[1] = tx.v[1].p;
                            ln.p[2] = tx.v[2].p;
                            ln.p[3] = tx.v[3].p;
                            func_002075F0(&ln, ot, 0);
                        }
                        func_002075F0(&tx, ot, 0);
                    }
                }
            }
        }
        g->t8++;
        if (g->t8 > 0x10FE) {
            g->on8 = 0;
        }
    }

    if (g->t == 0xA0) {
        g->cloud[0].on = 1;
        g->cloud[0].t = 0;
        for (i = 0; i < 1; i++) {
            g->cloud[0].pos[i] = g->posA;
            for (x = 0; x < 512; x++) {
                g->cloud[0].c[i][x] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->cloud[0].v[i][x], 3.5f);
            }
        }
    }

    ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 1; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(1));
        a = 1.0f;
        alpha = (u32)(a * (128.0f * func_00100FF0((f32)g->cloud[i].t, 64.0f, 42.0f)));
        r = 3.5f * (0.2f + 0.8f * (0x40 - g->cloud[i].t) / 64.0f);
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
        s = 0.8f + 0.2f * g->cloud[i].t / 64.0f;
        h = 5.0f * g->cloud[i].t / 64.0f;
        for (j = 0; j < 1; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0xFA;
            spr.c.b = 0xA4;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (n = 0; n < 512; n++) {
                x = g->cloud[i].c[j][n] % 4 * 32;
                y = (g->cloud[i].c[j][n] >> 2) * 32;
                ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->cloud[i].v[j][n], s);
                func_00187B00(&v, &v, &g->cloud[i].pos[j]);
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
        g->cloud[i].t++;
        if (g->cloud[i].t > 0x40) {
            g->cloud[i].on = 0;
        }
        if (g->t == 0xB8) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t == 0x6E) {
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
        ((Tri_b373_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b373_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b373_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b373_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b373_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        D_01E04F00_b373 = (s32)g;
        func_001F7070(1, &tri.tex0, &tri.tex1, 0, b373_01E048B0);
        func_00208460();
        a = func_00101020((f32)g->t1, 48.0f) * func_00100FF0((f32)g->t1, 4350.0f, 4302.0f);
        e = func_00101020((f32)g->t1, 48.0f) * func_00100FF0((f32)g->t1, 4350.0f, 4302.0f);
        for (i = 0; i < 5; i++) {
            f = 1.0f + 0.2f * i / 4.0f - 0.1f;
            n = ((i + 1) << 15) / 6;
            alpha = (u32)(a * (64.0f * func_0020B550(n)));
            a2 = (u32)(e * (64.0f * func_0020B550(n)));
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
                k = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->u = k << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                k = (s32)D_28B960[j].x;
                y = (s32)D_28B960[j].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->u = k << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                k = (s32)D_28B960[j + 1].x;
                y = (s32)D_28B960[j + 1].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->u = k << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[j], (void *)&g->scrA);
                func_00187B18(&out[1], &D_28B960[j + 1], (void *)&g->scrA);
                func_00187B48((void *)&out[0], &out[0], f);
                func_00187B48(&out[1], &out[1], f);
                func_00187B00(&out[0], &out[0], &g->scrA);
                func_00187B00(&out[1], &out[1], &g->scrA);
                k = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
                tri.v[0].p.x = (k + 0x6C0) << 4;
                tri.v[0].p.y = (y + 0x720) << 4;
                tri.v[0].p.z = 0xFFFFF8;
                tri.v[0].p.f = 0;
                k = (s32)out[0].x;
                y = (s32)out[0].y;
                tri.v[1].p.x = (k + 0x6C0) << 4;
                tri.v[1].p.y = (y + 0x720) << 4;
                tri.v[1].p.z = 0xFFFFF8;
                tri.v[1].p.f = 0;
                k = (s32)out[1].x;
                y = (s32)out[1].y;
                tri.v[2].p.x = (k + 0x6C0) << 4;
                tri.v[2].p.y = (y + 0x720) << 4;
                tri.v[2].p.z = 0xFFFFF8;
                tri.v[2].p.f = 0;
                func_002075F0(&tri, 0, 0);
            }
        }
        if (g->t < 0x142) {
            func_00207FD0(buf, ot, 0);
        } else {
            func_00207FD0(buf, ot, (u32)depth);
        }
        g->t1++;
        if (g->t1 > 0x10FE) {
            g->on = 0;
        }
    }

    if (g->t > 0x108 && g->t < 0x1B3 && g->t % 2 == 0) {
        ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        D_01E04F00_b373 = (s32)g;
        func_001F70A0(g->unitB, 1, &spr.tex0, &spr.tex1, 0, b373_01E04DE0);
        func_00208460();
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
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

    if (g->t == 0x3C || g->t == 0x57) {
        n = g->t == 0x3C ? 0 : 1;
        g->dust[n].on = 1;
        g->dust[n].t = 0;
        for (i = 0; i < 1; i++) {
            g->dust[n].pos[i] = g->jp2[n];
            for (k = 0; k < 32; k++) {
                g->dust[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->dust[n].v[i][k], 1.8f);
                g->dust[n].v[i][k].y = func_001A6970(g->dust[n].v[i][k].y);
                g->dust[n].v[i][k].y *= 0.8f;
            }
        }
    }

    ((Spr_b373_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b373_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b373_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b373_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b373_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[4], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 2; i++) {
        if (g->dust[i].on == 0) {
            continue;
        }
        alpha = (u32)(64.0f * func_0020B480((g->dust[i].t << 14) >> 5));
        spr.c.r = 0xEE;
        spr.c.g = 0xEE;
        spr.c.b = 0xEE;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 17.0f * (0.5f + 0.5f * g->dust[i].t / 32.0f);
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
        a = func_00100D50(g->dust[i].t, 32, 1);
        e = 0.0f * g->dust[i].t / 32.0f;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 32; k++) {
                func_00187B48(&v, &g->dust[i].v[j][k], a);
                func_00187B00(&v, &v, &g->dust[i].pos[j]);
                v.y += e;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->dust[i].c[j][k] % 4 * 32;
                y = (g->dust[i].c[j][k] >> 2) * 32;
                ((Uv_b373_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b373_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, 0);
                }
            }
        }
        g->dust[i].t++;
        if (g->dust[i].t > 32) {
            g->dust[i].on = 0;
        }
    }

    if (g->t == 6) {
        g->on7 = 1;
        g->t7 = 0;
    }
    if (g->on7 == 1) {
        ((Tri_b373_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b373_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b373_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b373_01E00080 *)(s32)&tri)->pad4 = 0;
        ((Tri_b373_01E00080 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(1));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_001F7060(g->unitA, 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x20 - g->t7) * 128 >> 5;
        tri.v[0].c.r = 0x40;
        tri.v[0].c.g = 0x40;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = 0;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0x40;
        tri.v[1].c.g = 0x40;
        tri.v[1].c.b = 0xFF;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 0.3f * func_00100D50(g->t7, 0x20, 1);
        for (i = 0; i < 3; i++) {
            f = 1.0f + r * (i + 1) / 3.0f;
            for (n = 0; n < 8; n++) {
                x = (s32)g->scrA.x;
                y = (s32)g->scrA.y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[n].x;
                y = (s32)D_28B960[n].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[n + 1].x;
                y = (s32)D_28B960[n + 1].y;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b373_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[n], (void *)&g->scrA);
                func_00187B18(&out[1], &D_28B960[n + 1], (void *)&g->scrA);
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

    func_001F6D00((u8)((func_00101050(0x207 - g->t, 0, 0x40) * (func_00101050(g->t, 0, 0x40) * -128) >> 12) + 0x80));
    if (g->t == 0x100) {
        ret = 1;
    } else {
        if (g->t > 0x10A && g->t < 0x1B3) {
            ret = 6;
        }
        if (g->t == 0x1B3) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x207) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b373:01E048B0, 329 insns: b217:01E02FD0 with the grid at 0x2BF0 and a blue tint: draw a grey backdrop rect (screen 0x6BF8,0x71F8 - 0x93F8,0x8DF8, far z), then the
   module object's 17x17 point grid as 16x16 textured quads (each 4x4 cell block spans the texture once), under the
   camera matrix times the object's position and a random tilt on each axis; far z */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b217_01E02FD0_b373;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b217_01E02FD0_b373 v[2];
    u64 tail;
} Flat_b217_01E02FD0_b373;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b217_01E02FD0_b373;

typedef struct {
    Rgbaq_b217_01E02FD0_b373 c;
    f32 s, t;
    Xyz_b217_01E02FD0_b373 p;
} Tv_b217_01E02FD0_b373;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b217_01E02FD0_b373 v[4];
    u8 tail[0x20];
} Tex_b217_01E02FD0_b373;

typedef struct {
    u8 pad0[0x14];
    void *texture;
    u8 pad18[0x18];
    u8 pos[0x10];
    u8 pad40[0x2BB0];
    Vec4f grid[17][17];
} Obj_b217_01E02FD0_b373;

extern Obj_b217_01E02FD0_b373 *D_01E04F00_b373;

static void func_01E048B0_b373(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern u64 func_00208D00(s32);
    extern void *func_00207650(void *, void *, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    Obj_b217_01E02FD0_b373 *o __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    Flat_b217_01E02FD0_b373 flat __attribute__((aligned(8)));
    Tex_b217_01E02FD0_b373 pk __attribute__((aligned(8)));
    f32 depth;
    void *p;
    s32 j;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;

    o = D_01E04F00_b373;
    p = func_00209F70(buf, 0xFF000000);
    ((Flat_b217_01E02FD0_b373 *)(s32)&flat)->flags = 6;
    ((Flat_b217_01E02FD0_b373 *)(s32)&flat)->size = 3;
    ((Flat_b217_01E02FD0_b373 *)(s32)&flat)->regs = 0x441;
    ((Flat_b217_01E02FD0_b373 *)(s32)&flat)->pad4 = 0;
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
    ((Tex_b217_01E02FD0_b373 *)(s32)&pk)->flags = 0x34;
    ((Tex_b217_01E02FD0_b373 *)(s32)&pk)->size = 0xC;
    ((Tex_b217_01E02FD0_b373 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b217_01E02FD0_b373 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].c.r = 0x80;
    pk.v[0].c.g = 0x80;
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

static void func_01E04DE0_b373(void *arg0) {
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
