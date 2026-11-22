#include "common.h"

/* shape b472:01E00080 (b472), 2767 insns, 1 copy (-O3,p): b472 scene manager (written from the asm with b022/b440
   sections): setup clears the 0xB1E0 scene, takes both units, five textures, the target and joints 0x11 / 0x21,
   builds a 17-segment 25/55 rim; on 0xB5..0x115 32-slot beams toward the target leaving 4-sprite puffs and, at frame
   0x1F, 32-slot spinning rim quads; on 0x15..0x135 28-slot 2x20 and 20-slot 2x8 rising motes at two lifted joint
   points, and 5-slot radial-blur flashes (func_001F7060 render-to-texture, 8 triangles from D_28B960) at the unit's
   screen point; returns 1 / 6 / 2 / 8 at 0xCA / 0xD5..0x155 / 0x156 / >0x176 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b472_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b472_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b472_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b472_01E00080 c;
    Uv_b472_01E00080 uv0;
    Xyz_b472_01E00080 p0;
    Uv_b472_01E00080 uv1;
    Xyz_b472_01E00080 p1;
    u8 tail[0x20];
} Spr_b472_01E00080;

typedef struct {
    Rgbaq_b472_01E00080 c;
    f32 s, t;
    Xyz_b472_01E00080 p;
} Tv_b472_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b472_01E00080 v[4];
    u8 tail[0x20];
} Quad_b472_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b472_01E00080 c;
        Uv_b472_01E00080 uv;
        Xyz_b472_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b472_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
} Flash_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 k;
    f32 dist[1];
    Mtx_b472_01E00080 mat[1];
} Beam_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    f32 sc;
    Vec4f pos;
    Vec4f v[4];
} Puff_b472_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f mid;
} Rim_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Mtx_b472_01E00080 mat;
} Spin_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][20];
    Vec4f pos[2];
    Vec4f v[2][20];
} Mote_b472_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Spark_b472_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[5];
    s32 jn[2];
    u8 pad2C[4];
    Vec4f jp[2];
    Vec4f pos;
    Vec4f scr;
    f32 lift;
    s32 z;
    Flash_b472_01E00080 flash[5];
    Vec4f tgt;
    Vec4f jq[2];
    f32 sc;
    u8 padD4[0xC];
    Beam_b472_01E00080 beam[32];
    Puff_b472_01E00080 puff[32][1][4];
    Rim_b472_01E00080 rim[17];
    s32 ns[1];
    u8 pad3E14[0xC];
    Spin_b472_01E00080 spin[1][32];
    Mote_b472_01E00080 mote[28];
    Spark_b472_01E00080 spark[20];
} Scene_b472_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b472(s32 arg0, s32 code) {
    Scene_b472_01E00080 *g = (Scene_b472_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
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
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
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
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
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
    s32 c;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 w0;
    f32 w1;
    f32 u0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Vec4f v;
    Vec4f off;
    Tri_b472_01E00080 tri __attribute__((aligned(8)));
    Quad_b472_01E00080 pk __attribute__((aligned(8)));
    Spr_b472_01E00080 spr __attribute__((aligned(8)));
    Xyz_b472_01E00080 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB1E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        g->tex[4] = func_00202BF0(5, 4);
        g->jn[0] = func_001F5560(g->unitA, 0x11, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x21, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->lift = 1.5f * func_001F5860(g->unitA);
        for (i = 0; i < 5; i++) {
            g->flash[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->beam[i].on = 0;
            g->beam[i].k = 0;
        }
        for (i = 0; i < 32; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 4; k++) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 17; i++) {
            g->rim[i].a.x = 25.0f * func_0020B550((i << 16) >> 4);
            g->rim[i].a.y = 25.0f * func_0020B480((i << 16) >> 4);
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 55.0f * func_0020B550((i << 16) >> 4);
            g->rim[i].b.y = 55.0f * func_0020B480((i << 16) >> 4);
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
            func_00187B00(&g->rim[i].mid, &g->rim[i].a, &g->rim[i].b);
            func_00187B48((void *)&g->rim[i].mid, &g->rim[i].mid, 0.5f);
        }
        for (i = 0; i < 1; i++) {
            g->ns[i] = 0;
            for (j = 0; j < 32; j++) {
                g->spin[i][j].on = 0;
            }
        }
        for (i = 0; i < 28; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 20; i++) {
            g->spark[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    s = func_00101050(g->t - 0x82, 0, 0x28) / 40.0f;
    g->sc = 1.0f + s;
    for (i = 0; i < 2; i++) {
        v.x = 0.0f;
        v.y = 80.0f;
        v.z = 70.0f * g->obj;
        v.w = 1.0f;
        func_00187B18(&v, &v, &g->jp[i]);
        func_00187B48(&v, &v, s);
        func_00187B00(&g->jq[i], &v, &g->jp[i]);
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

    if (g->t > 0xB4 && g->t < 0x116) {
        n = g->t % 32;
        g->beam[n].on = 1;
        g->beam[n].t = 0;
        off.x = 0.0f;
        off.y = 80.0f;
        off.z = 70.0f * g->obj;
        off.w = 1.0f;
        for (j = 0; j < 1; j++) {
            func_00101080(&v, 1.0f);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B18(&v, &v, &off);
            g->beam[n].dist[j] = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
            func_00100E40(&g->beam[n].mat[j], &v);
            func_00100E00(&g->beam[n].mat[j], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
    }

    ((Spr_b472_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b472_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b472_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b472_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b472_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 64;
    y = 0;
    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
    r = 5.0f;
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
    off.x = 0.0f;
    off.y = 80.0f;
    off.z = 70.0f * g->obj;
    off.w = 1.0f;
    for (i = 0; i < 32; i++) {
        if (g->beam[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0x50;
        spr.c.b = 0x23;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        s = g->beam[i].t / 32.0f;
        w1 = 4.0f * s + -4.0f * s * s;
        n = g->beam[i].k++;
        if (g->beam[i].k >= 4) {
            g->beam[i].k = 0;
        }
        for (j = 0; j < 1; j++) {
            v.x = 0.0f;
            v.y = 40.0f * w1;
            v.z = s * g->beam[i].dist[j];
            v.w = 1.0f;
            func_001878E0(&v, &g->beam[i].mat[j], &v);
            func_00187B00(&v, &v, &off);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->puff[i][j][n].on = 1;
            g->puff[i][j][n].t = 0;
            g->puff[i][j][n].sc = 0.3f + 0.7f * g->beam[i].t / 32.0f;
            g->puff[i][j][n].pos = v;
            for (k = 0; k < 4; k++) {
                g->puff[i][j][n].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[i][j][n].v[k], 0.3f * g->puff[i][j][n].sc);
            }
            if (g->beam[i].t == 0x1F) {
                c = g->ns[j];
                g->spin[j][c].on = 1;
                g->spin[j][c].t = 0;
                g->spin[j][c].pos = v;
                func_0020BBB0(&g->spin[j][c].mat);
                func_00100E00(&g->spin[j][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 0);
                func_00100E00(&g->spin[j][c].mat, (func_0019A5C8() >> 23) % 256 << 15 >> 8, 1);
                func_00100E00(&g->spin[j][c].mat, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->ns[j]++;
                if (g->ns[j] >= 32) {
                    g->ns[j] = 0;
                }
            }
        }
        g->beam[i].t++;
        if (g->beam[i].t > 32) {
            g->beam[i].on = 0;
        }
    }

    ((Spr_b472_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b472_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b472_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b472_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b472_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[3], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 4; k++) {
                if (g->puff[i][j][k].on == 0) {
                    continue;
                }
                w1 = 6.0f * (0.5f + 0.5f * (4 - g->puff[i][j][k].t) / 4.0f);
                cn[0].x = -w1;
                cn[0].y = -w1;
                cn[0].z = 0.0f;
                cn[0].w = 1.0f;
                cn[1].x = w1;
                cn[1].y = w1;
                cn[1].z = 0.0f;
                cn[1].w = 1.0f;
                func_001878E0(&cn[0], m3, &cn[0]);
                func_001878E0(&cn[1], m3, &cn[1]);
                alpha = (4 - g->puff[i][j][k].t) * 128 >> 2;
                spr.c.r = 0xFF;
                spr.c.g = 0x46;
                spr.c.b = 0x1E;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.2f + 0.8f * func_00100D50(g->puff[i][j][k].t, 4, 1);
                for (l = 0; l < 4; l++) {
                    x = g->puff[i][j][k].c[l] % 4 * 32;
                    y = (g->puff[i][j][k].c[l] >> 2) * 32;
                    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->puff[i][j][k].v[l], s);
                    func_00187B00(&v, &v, &g->puff[i][j][k].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->puff[i][j][k].t++;
                if (g->puff[i][j][k].t > 4) {
                    g->puff[i][j][k].on = 0;
                }
            }
        }
    }

    ((Quad_b472_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Quad_b472_01E00080 *)(s32)&pk)->size = 0xC;
    ((Quad_b472_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b472_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[4], 1);
    func_00208CB0(&pk, 0);
    ((Spr_b472_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b472_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b472_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b472_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b472_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    x = 64;
    y = 0;
    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
    ((Uv_b472_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
    w1 = 20.0f;
    cn[0].x = -w1;
    cn[0].y = -w1;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = w1;
    cn[1].y = w1;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 32; j++) {
            if (g->spin[i][j].on == 0) {
                continue;
            }
            r = func_00100FF0(g->spin[i][j].t, 32.0f, 16.0f);
            pk.v[0].c.r = 0x60;
            pk.v[0].c.g = 0x26;
            pk.v[0].c.b = 0x1C;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            alpha = (u32)(100.0f * r);
            pk.v[2].c.r = 0xFF;
            pk.v[2].c.g = 0x62;
            pk.v[2].c.b = 0x26;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            pk.v[3].c = pk.v[2].c;
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &g->spin[i][j].pos);
            func_0020BC00(m2, &g->spin[i][j].mat);
            s = 0.1f + 0.9f * func_00100D50(g->spin[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = 0.0f;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            w0 = -1.0f * (g->spin[i][j].t % 32) / 32.0f;
            w1 = 0.5f + w0;
            h = 1.0f + w0;
            for (l = 0; l < 16; l++) {
                u0 = 6.0f * l / 16.0f;
                u1 = 6.0f * (l + 1) / 16.0f;
                pk.v[0].s = u0;
                pk.v[0].t = w0;
                pk.v[1].s = u1;
                pk.v[1].t = w0;
                pk.v[2].s = u0;
                pk.v[2].t = w1;
                pk.v[3].s = u1;
                pk.v[3].t = w1;
                if (func_00100BA0(&g->rim[l].a, &g->rim[l + 1].a, &g->rim[l].mid, &g->rim[l + 1].mid, m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
                pk.v[0].s = u0;
                pk.v[0].t = h;
                pk.v[1].s = u1;
                pk.v[1].t = h;
                pk.v[2].s = u0;
                pk.v[2].t = w1;
                pk.v[3].s = u1;
                pk.v[3].t = w1;
                if (func_00100BA0(&g->rim[l].b, &g->rim[l + 1].b, &g->rim[l].mid, &g->rim[l + 1].mid, m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
            alpha = (u32)(255.0f * func_00100FF0(g->spin[i][j].t, 32.0f, 16.0f));
            spr.c.r = 0xFF;
            spr.c.g = 0x44;
            spr.c.b = 0x23;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->spin[i][j].pos);
            s = 0.1f + 0.9f * func_00100D50(g->spin[i][j].t, 32, 1);
            v.x = s;
            v.y = s;
            v.z = s;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->spin[i][j].t++;
            if (g->spin[i][j].t > 32) {
                g->spin[i][j].on = 0;
            }
        }
    }

    if (g->t > 0x14 && g->t < 0x136) {
        n = g->t % 28;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->mote[n].pos[i] = g->jq[i];
            for (k = 0; k < 20; k++) {
                g->mote[n].c[i][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->mote[n].v[i][k], 0.28f * g->sc);
            }
        }
    }

    ((Spr_b472_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b472_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b472_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b472_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b472_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x14, 0, 32) * (f32)func_00101050(0x136 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 28; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->mote[i].t << 15) / 28)));
        r = 0.25f * (0.5f + 0.5f * (28 - g->mote[i].t) / 28.0f) * g->sc;
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
        s = 0.2f + 0.8f * func_00100D50(g->mote[i].t, 28, 1);
        h = (-0.5f + 15.0f * g->mote[i].t / 28.0f) * g->sc;
        for (j = 0; j < 2; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x64;
            spr.c.b = 0x2D;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 20; k++) {
                x = g->mote[i].c[j][k] % 4 * 32;
                y = (g->mote[i].c[j][k] >> 2) * 32;
                ((Uv_b472_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->mote[i].v[j][k], s);
                func_00187B00(&v, &v, &g->mote[i].pos[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 28) {
            g->mote[i].on = 0;
        }
    }

    if (g->t > 0x14 && g->t < 0x136) {
        n = g->t % 20;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->spark[n].pos[i] = g->jq[i];
            for (k = 0; k < 8; k++) {
                g->spark[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[n].v[i][k], 0.15f * g->sc);
            }
        }
    }

    ((Spr_b472_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b472_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b472_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b472_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b472_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    s = (f32)func_00101050(g->t - 0x14, 0, 32) * (f32)func_00101050(0x136 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 20; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        func_00208700(&spr, g->tex[3], 1);
        func_002086D0(&spr, func_00208D00(1));
        alpha = (u32)(s * (128.0f * func_0020B550((g->spark[i].t << 15) / 20)));
        r = 3.0f * (0.3f + 0.7f * (20 - g->spark[i].t) / 20.0f) * g->sc;
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
        f = 0.8f + 0.2f * (20 - g->spark[i].t) / 20.0f;
        h = (-4.5f + 17.0f * g->spark[i].t / 20.0f) * g->sc;
        for (j = 0; j < 2; j++) {
            spr.c.r = 0xFF;
            spr.c.g = 0x3C;
            spr.c.b = 0x1E;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            for (k = 0; k < 8; k++) {
                x = g->spark[i].c[j][k] % 4 * 32;
                y = (g->spark[i].c[j][k] >> 2) * 32;
                ((Uv_b472_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b472_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->spark[i].v[j][k], f);
                func_00187B00(&v, &v, &g->spark[i].pos[j]);
                v.y += h;
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 20) {
            g->spark[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x136) {
        n = g->t % 5;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
    }
    ((Tri_b472_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b472_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b472_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b472_01E00080 *)(s32)&tri)->pad4 = 0;
    ((Tri_b472_01E00080 *)(s32)&tri)->flags |= 0x800;
    func_002086D0(&tri, func_00208D00(1));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x136 - g->t, 0, 32) / 1024.0f;
    on = 0;
    for (i = 0; i < 5; i++) {
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
        alpha = (u32)(f * (255.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 6)));
        tri.v[0].c.r = 0xA8;
        tri.v[0].c.g = 0xFF;
        tri.v[0].c.b = 0x64;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        alpha = (u32)(f * (0.0f * func_0020B550(((g->flash[i].t + 1) << 15) / 6)));
        tri.v[1].c.r = 0x20;
        tri.v[1].c.g = 0xFF;
        tri.v[1].c.b = 8;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        r = 1.0f + (-0.15f + 0.3f * g->flash[i].t / 5.0f) + 0.15f / 5.0f;
        for (j = 0; j < 8; j++) {
            x = (s32)g->scr.x;
            y = (s32)g->scr.y;
            ((Uv_b472_01E00080 *)(s32)&tri.v[0].uv)->u = x << 4;
            ((Uv_b472_01E00080 *)(s32)&tri.v[0].uv)->v = y << 4;
            x = (s32)D_28B960[j].x;
            y = (s32)D_28B960[j].y;
            ((Uv_b472_01E00080 *)(s32)&tri.v[1].uv)->u = x << 4;
            ((Uv_b472_01E00080 *)(s32)&tri.v[1].uv)->v = y << 4;
            x = (s32)D_28B960[j + 1].x;
            y = (s32)D_28B960[j + 1].y;
            ((Uv_b472_01E00080 *)(s32)&tri.v[2].uv)->u = x << 4;
            ((Uv_b472_01E00080 *)(s32)&tri.v[2].uv)->v = y << 4;
            func_00187B18(&out[0], &D_28B960[j], (void *)&g->scr);
            func_00187B18(&out[1], &D_28B960[j + 1], &g->scr);
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
        if (g->flash[i].t > 5) {
            g->flash[i].on = 0;
        }
    }
    if (on == 1) {
        func_00207FD0(buf, ot, 0);
    }

    func_001F6D00((u8)((func_00101050(0x176 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -96) >> 10) + 0x80));
    if (g->t == 0xCA) {
        ret = 1;
    } else {
        if (g->t > 0xD4 && g->t < 0x156) {
            ret = 6;
        }
        if (g->t == 0x156) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x176) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
