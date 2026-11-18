#include "common.h"

/* shape b249:01E00080 (b249), 2870 insns, 1 copy (-O3,p): scene manager: setup builds a 33-point triple rim, four
   blades and a 16x13 jittered shell grid with normals, spin rates and ST triangles; 48-slot blade bursts at the
   joint, a flash, rim strips and 128 flakes, a 0x96-frame shell shatter of textured triangles with edge lines, and a
   closing 64-sprite puff */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b249_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b249_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b249_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b249_01E00080 c;
    Uv_b249_01E00080 uv0;
    Xyz_b249_01E00080 p0;
    Uv_b249_01E00080 uv1;
    Xyz_b249_01E00080 p1;
    u8 tail[0x20];
} Spr_b249_01E00080;

typedef struct {
    Uv_b249_01E00080 uv;
    Xyz_b249_01E00080 p;
} Qv_b249_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b249_01E00080 c;
    Qv_b249_01E00080 v[4];
    u8 tail[0x20];
} Quad_b249_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b249_01E00080 c;
        Xyz_b249_01E00080 p;
    } v[4];
    u64 tail;
} Line_b249_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b249_01E00080 c;
        Xyz_b249_01E00080 p;
    } v[3];
    u64 tail;
} Edge_b249_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b249_01E00080 c;
        f32 s, t;
        Xyz_b249_01E00080 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b249_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b249_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[8];
    f32 sc[8];
    u8 pad48[8];
    Vec4f pos;
    Vec4f v[8];
    s32 cnt;
    u8 padE4[0xC];
} Burst_b249_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
    Vec4f c;
} Rim_b249_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 s;
    s32 ang;
    Vec4f p;
} Shard_b249_01E00080;

typedef struct {
    Vec4f v[6];
    Vec4f n[2];
} Uvs_b249_01E00080;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Spin_b249_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn;
    Vec4f jp;
    s32 jn2;
    u8 pad34[0xC];
    Vec4f jp2;
    Vec4f pos;
    f32 h;
    u8 pad64[0xC];
    Burst_b249_01E00080 burst[48];
    u8 on2;
    u8 pad2D71[3];
    s32 t2;
    u8 pad2D78[8];
    Rim_b249_01E00080 rim[33];
    u8 cc[128];
    Vec4f cpos;
    Vec4f vv[128];
    Vec4f blade[4][4];
    Shard_b249_01E00080 shard[48][8];
    Uvs_b249_01E00080 uv[15][12];
    Vec4f grid[16][13];
    Vec4f nrm[15][12][2];
    Spin_b249_01E00080 spin[15][12];
    u8 on3;
    u8 padF331[3];
    s32 t3;
    u8 padF338[8];
    u8 on4;
    u8 padF341[3];
    s32 t4;
    u16 c4[64];
    u8 padF3C8[8];
    Vec4f dv[64];
} Scene_b249_01E00080;

#pragma optimization_level 3

static s32 func_01E00080_b249(s32 arg0, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00100F60(void *, void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
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
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00205E70(s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern f32 D_0028BC10[][32][3];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    s32 q;
    s32 x;
    s32 y;
    s32 a;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b249_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    s32 ang[4];
    Mtx_b249_01E00080 m4;
    Vec4f v;
    Vec4f d;
    Vec4f c;
    Spr_b249_01E00080 spr __attribute__((aligned(8)));
    Quad_b249_01E00080 pk __attribute__((aligned(8)));
    Line_b249_01E00080 line __attribute__((aligned(8)));
    Edge_b249_01E00080 edge __attribute__((aligned(8)));
    Tri_b249_01E00080 tri __attribute__((aligned(8)));
    f32 depth;
    Scene_b249_01E00080 *g = (Scene_b249_01E00080 *)arg0;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xF7D0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn = func_001F5560(g->unitA, 0x27, 1);
        g->jn2 = func_001F5560(g->unitA, 0x1C, 0);
        func_001F53C0(1, g->unitB, &g->pos);
        g->h = func_001F5860(g->unitB);
        if (g->h > 20.0f) {
            g->h = 20.0f;
        }
        for (i = 0; i < 48; i++) {
            g->burst[i].on = 0;
            g->burst[i].cnt = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 33; i++) {
            v.x = func_0020B550((i << 16) >> 5);
            v.y = func_0020B480((i << 16) >> 5);
            v.z = 0.0f;
            v.w = 1.0f;
            func_00187B48((void *)&g->rim[i].a, &v, 5.0f);
            func_00187B48((void *)&g->rim[i].b, &v, 9.8f);
            func_00187B48((void *)&g->rim[i].c, &v, 10.0f);
        }
        w = 0.4f;
        for (i = 0; i < 4; i++) {
            r = 6.0f * (1.0f - 0.4f * (i % 2));
            cn[0].x = -w;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = w;
            cn[1].y = -r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = -w;
            cn[2].y = r;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = w;
            cn[3].y = r;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (i << 15) >> 2, 2);
            for (j = 0; j < 4; j++) {
                func_001878E0(&g->blade[i][j], &m4, &cn[j]);
            }
        }
        for (i = 0; i < 48; i++) {
            for (j = 0; j < 8; j++) {
                g->shard[i][j].on = 0;
            }
        }
        for (ot = 0; ot < 16; ot++) {
            for (j = 0; j < 13; j++) {
                i = (ot << 15) / 15;
                r = g->h * func_0020B550(i & 0xFFFF);
                r += 0.5f * r * ((func_0019A5C8() >> 23) % 8) / 8.0f;
                h = -(5.0f * g->h) / 2.0f + 5.0f * g->h * ot / 15.0f;
                if (ot != 0 && ot != 15) {
                    h += 5.0f * g->h / 15.0f / 2.0f * (4.0f - (func_0019A5C8() >> 23) % 8) / 4.0f;
                }
                k = func_0019A5C8() >> 23;
                i = (j << 16) / 12 + ((k % 8 * 0xAAA) >> 3);
                i &= 0xFFFF;
                g->grid[ot][j].x = r * func_0020B550(i);
                g->grid[ot][j].y = h;
                g->grid[ot][j].z = r * func_0020B480(i);
                g->grid[ot][j].w = 1.0f;
            }
            g->grid[ot][12] = g->grid[ot][0];
        }
        for (j = 0; j < 15; j++) {
            for (k = 0; k < 12; k++) {
                func_00100F60(&g->nrm[j][k][0], &g->grid[j][k], &g->grid[j + 1][k], &g->grid[j + 1][k + 1]);
                func_00100F60(&g->nrm[j][k][1], &g->grid[j][k], &g->grid[j][k + 1], &g->grid[j + 1][k + 1]);
            }
        }
        for (i = 0; i < 15; i++) {
            for (k = 0; k < 12; k++) {
                g->spin[i][k].a = (((func_0019A5C8() >> 23) % 256 * 333 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
                g->spin[i][k].b = (((func_0019A5C8() >> 23) % 256 * 222 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
                g->spin[i][k].c = (((func_0019A5C8() >> 23) % 256 * 111 >> 8) * (((func_0019A5C8() >> 23) % 2 - 1) * 2)) & 0xFFFF;
            }
        }
        g->on3 = 0;
        for (i = 0; i < 15; i++) {
            for (k = 0; k < 12; k++) {
                s = (64.0f + 512.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f) / 1024.0f;
                h = (64.0f + 320.0f * ((func_0019A5C8() >> 23) % 256) / 256.0f) / 512.0f;
                for (l = 0; l < 6; l++) {
                    g->uv[i][k].v[l].x = s + 0.125f * (-0.5f + ((func_0019A5C8() >> 23) % 256) / 256.0f);
                    g->uv[i][k].v[l].y = h + 0.25f * (-0.5f + ((func_0019A5C8() >> 23) % 256) / 256.0f);
                    g->uv[i][k].v[l].z = 0.0f;
                    g->uv[i][k].v[l].w = 1.0f;
                }
                func_00100F60(&g->uv[i][k].n[0], &g->uv[i][k].v[0], &g->uv[i][k].v[1], &g->uv[i][k].v[2]);
                func_00100F60(&g->uv[i][k].n[1], &g->uv[i][k].v[3], &g->uv[i][k].v[4], &g->uv[i][k].v[5]);
            }
        }
        for (i = 0; i < 64; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 8;
        }
        g->on4 = 0;
        return 0;
    }
    func_00205CA0(&m3);
    func_001F5620(g->unitA, g->jn, &g->jp);
    func_001F5620(g->unitA, g->jn2, &g->jp2);
    if (g->t > 0x5B && g->t < 0xEB) {
        n = g->t % 48;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        g->burst[n].pos = g->jp;
        g->burst[n].pos.z += 4.0f * g->obj;
        for (k = 0; k < 8; k++) {
            g->burst[n].c[k] = (func_0019A5C8() >> 23) % 8;
            g->burst[n].sc[k] = 0.8f + 0.2f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->burst[n].v[k], 1.0f);
            func_00187B00(&g->burst[n].v[k], &g->burst[n].v[k], &g->pos);
            func_00187B18(&g->burst[n].v[k], &g->burst[n].v[k], &g->burst[n].pos);
        }
    }

    ((Spr_b249_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b249_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b249_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b249_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b249_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 48; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (u32)(80.0f * func_00101020(g->burst[i].t, 2.0f) * func_00100FF0(g->burst[i].t, 48.0f, 32.0f));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 12.0f * (0.4f + 0.6f * g->burst[i].t / 48.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        w = 1.5f * g->burst[i].t / 48.0f;
        n = (s32)(32768.0f * w);
        n &= 0xFFFF;
        h = -10.0f * func_0020B550(n);
        for (k = 0; k < 8; k++) {
            x = g->burst[i].c[k] % 4 * 32;
            y = (g->burst[i].c[k] >> 2) * 32;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&out[0], &cn[0], g->burst[i].sc[k]);
            func_00187B48(&out[1], &cn[1], g->burst[i].sc[k]);
            func_00187B48(&v, &g->burst[i].v[k], w);
            v.y += h;
            func_00187B00(&v, &v, &g->burst[i].pos);
            func_00187B00(&out[0], &out[0], &v);
            func_00187B00(&out[1], &out[1], &v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        if (g->burst[i].t % 4 == 0) {
            n = g->burst[i].cnt;
            g->burst[i].cnt++;
            if (g->burst[i].cnt >= 8) {
                g->burst[i].cnt = 0;
            }
            g->shard[i][n].on = 1;
            g->shard[i][n].t = 0;
            g->shard[i][n].s = (0.5f + 0.5f * g->burst[i].t / 48.0f) * (0.1f + 0.9f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->shard[i][n].ang = ((func_0019A5C8() >> 23) % 8 << 16) >> 3;
            func_00101080(&g->shard[i][n].p, 0.5f);
            func_00187B00(&g->shard[i][n].p, &g->shard[i][n].p, &v);
        }
        g->burst[i].t++;
        if (g->burst[i].t > 48) {
            g->burst[i].on = 0;
        }
    }

    if (g->t == 0x28) {
        g->on2 = 1;
        g->t2 = 0;
        g->cpos = g->jp2;
        for (k = 0; k < 128; k++) {
            g->cc[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->vv[k], 0.3f);
        }
    }
    if (g->on2 == 1) {
        ((Spr_b249_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b249_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b249_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b249_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b249_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 96;
        y = 0;
        ((Uv_b249_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b249_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b249_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b249_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
        func_0020EB40(m);
        func_00187B60(m2, &m3, &g->cpos);
        func_0020BC00(m, m2);
        alpha = (u32)(255.0f * (1.0f - func_00100D50(g->t2, 16, 1)));
        spr.c.r = 0xB4;
        spr.c.g = 0xC8;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 12.0f;
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
        ((Line_b249_01E00080 *)(s32)&line)->flags = 0x14;
        ((Line_b249_01E00080 *)(s32)&line)->size = 8;
        ((Line_b249_01E00080 *)(s32)&line)->regs = 0x41414141;
        ((Line_b249_01E00080 *)(s32)&line)->pad4 = 0;
        func_002086D0(&line, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, &m3, &g->cpos);
        s = func_00100D50(g->t2, 16, 2);
        v.x = s;
        v.y = s;
        v.z = 0.0f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        alpha = (0x10 - g->t2) * 0xFF >> 4;
        line.v[0].c.r = 0xB4;
        line.v[0].c.g = 0xC8;
        line.v[0].c.b = 0xFF;
        line.v[0].c.a = alpha;
        line.v[0].c.q = 1.0f;
        line.v[1].c = line.v[0].c;
        line.v[2].c.r = 0;
        line.v[2].c.g = 0;
        line.v[2].c.b = 0xFF;
        line.v[2].c.a = 0;
        line.v[2].c.q = 1.0f;
        line.v[3].c = line.v[2].c;
        for (i = 0; i < 32; i++) {
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].a, &g->rim[i + 1].a, m, &line, &depth) == 1) {
                line.v[0].p.z = 0xFFFFF8;
                line.v[1].p.z = line.v[0].p.z;
                line.v[2].p.z = line.v[0].p.z;
                line.v[3].p.z = line.v[0].p.z;
                func_002075F0(&line, ot, 0);
            }
            if (func_00100BA0(&g->rim[i].b, &g->rim[i + 1].b, &g->rim[i].c, &g->rim[i + 1].c, m, &line, &depth) == 1) {
                line.v[0].p.z = 0xFFFFF8;
                line.v[1].p.z = line.v[0].p.z;
                line.v[2].p.z = line.v[0].p.z;
                line.v[3].p.z = line.v[0].p.z;
                func_002075F0(&line, ot, 0);
            }
        }
        ((Spr_b249_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b249_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b249_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b249_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b249_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        alpha = (0x10 - g->t2) * 0xFF >> 4;
        spr.c.r = 0x84;
        spr.c.g = 0xA4;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.5f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        for (k = 0; k < 128; k++) {
            x = g->cc[k] % 4 * 32;
            y = (g->cc[k] >> 2) * 32;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->vv[k], s);
            func_00187B00(&v, &v, &g->cpos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->t2++;
        if (g->t2 > 16) {
            g->on2 = 0;
        }
    }

    ((Quad_b249_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Quad_b249_01E00080 *)(s32)&pk)->size = 9;
    ((Quad_b249_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b249_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Quad_b249_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, 5);
    x = 96;
    y = 32;
    ((Uv_b249_01E00080 *)(s32)&pk.v[0].uv)->u = x << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[0].uv)->v = y << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[1].uv)->u = (x + 32) << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[1].uv)->v = y << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[2].uv)->u = x << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[2].uv)->v = (y + 32) << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[3].uv)->u = (x + 32) << 4;
    ((Uv_b249_01E00080 *)(s32)&pk.v[3].uv)->v = (y + 32) << 4;
    ((Spr_b249_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b249_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b249_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b249_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b249_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    ((Uv_b249_01E00080 *)(s32)&spr.uv0)->u = x << 4;
    ((Uv_b249_01E00080 *)(s32)&spr.uv0)->v = y << 4;
    ((Uv_b249_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
    ((Uv_b249_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 48; j++) {
        for (x = 0; x < 8; x++) {
            if (g->shard[j][x].on == 0) {
                continue;
            }
            alpha = (u32)(64.0f * func_0020B480((g->shard[j][x].t << 14) >> 3));
            pk.c.r = 0xAA;
            pk.c.g = 0xEB;
            pk.c.b = 0xFF;
            pk.c.a = alpha;
            pk.c.q = 1.0f;
            m4 = m3;
            s = g->shard[j][x].s;
            for (l = 0; l < 4; l++) {
                for (q = 0; q < 4; q++) {
                    func_00187B48(&cn[q], &g->blade[l][q], s);
                    func_001878E0(&cn[q], &m4, &cn[q]);
                    func_00187B00(&out[q], &cn[q], &g->shard[j][x].p);
                }
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
            r = 2.0f * g->shard[j][x].s;
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], &m3, &cn[0]);
            func_001878E0(&cn[1], &m3, &cn[1]);
            alpha = (u32)(32.0f * func_0020B480((g->shard[j][x].t << 14) >> 3));
            spr.c.r = 0xAA;
            spr.c.g = 0xEB;
            spr.c.b = 0xFF;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            v = g->shard[j][x].p;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->shard[j][x].t++;
            if (g->shard[j][x].t > 8) {
                g->shard[j][x].on = 0;
            }
        }
    }

    if (g->t == 0xC8) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b249_01E00080 *)(s32)&tri)->flags = 0x33;
        ((Tri_b249_01E00080 *)(s32)&tri)->size = 9;
        ((Tri_b249_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b249_01E00080 *)(s32)&tri)->pad4 = 0;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        func_002087A0(&tri, 1);
        ((Edge_b249_01E00080 *)(s32)&edge)->flags = 0x13;
        ((Edge_b249_01E00080 *)(s32)&edge)->size = 6;
        ((Edge_b249_01E00080 *)(s32)&edge)->regs = 0x414141;
        ((Edge_b249_01E00080 *)(s32)&edge)->pad4 = 0;
        func_002086D0(&edge, func_00208D00(1));
        n = g->t3;
        if (n > 32) {
            n = 32;
        }
        k = n * 15 >> 5;
        if (k > 15) {
            k = 15;
        }
        y = 0x96 - g->t3;
        if (y > 32) {
            y = 32;
        }
        w = 3.0f * g->h * func_00100D50(32 - y, 32, 1);
        alpha = (u32)(128.0f * func_00100FF0(32 - y, 32.0f, 16.0f));
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = 0;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0x80;
        tri.v[1].c.g = 0x80;
        tri.v[1].c.b = 0x80;
        tri.v[1].c.a = alpha;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        alpha = (u32)(80.0f * func_00100FF0(32 - y, 32.0f, 16.0f));
        edge.v[0].c.r = 0;
        edge.v[0].c.g = 0;
        edge.v[0].c.b = 0;
        edge.v[0].c.a = 0;
        edge.v[0].c.q = 1.0f;
        edge.v[1].c.r = 0xD7;
        edge.v[1].c.g = 0xEB;
        edge.v[1].c.b = 0xFF;
        edge.v[1].c.a = alpha;
        edge.v[1].c.q = 1.0f;
        edge.v[2].c = edge.v[1].c;
        for (j = 0; j < k; j++) {
            for (x = 0; x < 12; x++) {
                ang[0] = ((32 - y) * g->spin[j][x].a) & 0xFFFF;
                ang[1] = ((32 - y) * g->spin[j][x].b) & 0xFFFF;
                ang[2] = ((32 - y) * g->spin[j][x].c) & 0xFFFF;
                ang[3] = 1;
                for (l = 0; l < 2; l++) {
                    func_00187B18(&out[0], &g->nrm[j][x][l], &g->nrm[j][x][l]);
                    func_00187B18(&out[1], &g->grid[j][x], (void *)&g->nrm[j][x][l]);
                    func_00187B18(&out[2], &g->grid[j + !l][x + l], (void *)&g->nrm[j][x][l]);
                    func_00187B18(&out[3], &g->grid[j + 1][x + 1], (void *)&g->nrm[j][x][l]);
                    func_00205E70(3, &out[1], &c);
                    func_00187B48(&d, &c, w * (l * 2 - 1));
                    func_00187B00(&d, &d, &g->pos);
                    func_00187B00(&d, &d, &g->nrm[j][x][l]);
                    func_0020EB40(m);
                    func_0020C940(m2, 0, ang, &d);
                    func_0020BC00(m, m2);
                    n = l * 3;
                    tri.v[0].s = g->uv[j][x].n[l].x;
                    tri.v[0].t = g->uv[j][x].n[l].y;
                    tri.v[1].s = g->uv[j][x].v[n].x;
                    tri.v[1].t = g->uv[j][x].v[n].y;
                    tri.v[2].s = g->uv[j][x].v[n + 1].x;
                    tri.v[2].t = g->uv[j][x].v[n + 1].y;
                    if (func_00100B00(&out[0], &out[1], &out[2], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                    tri.v[0].s = g->uv[j][x].n[l].x;
                    tri.v[0].t = g->uv[j][x].n[l].y;
                    tri.v[1].s = g->uv[j][x].v[n + 1].x;
                    tri.v[1].t = g->uv[j][x].v[n + 1].y;
                    tri.v[2].s = g->uv[j][x].v[n + 2].x;
                    tri.v[2].t = g->uv[j][x].v[n + 2].y;
                    if (func_00100B00(&out[0], &out[2], &out[3], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                    tri.v[0].s = g->uv[j][x].n[l].x;
                    tri.v[0].t = g->uv[j][x].n[l].y;
                    tri.v[1].s = g->uv[j][x].v[n + 2].x;
                    tri.v[1].t = g->uv[j][x].v[n + 2].y;
                    tri.v[2].s = g->uv[j][x].v[n].x;
                    tri.v[2].t = g->uv[j][x].v[n].y;
                    if (func_00100B00(&out[0], &out[3], &out[1], m, &tri, &depth) == 1) {
                        edge.v[0].p = tri.v[0].p;
                        edge.v[1].p = tri.v[1].p;
                        edge.v[2].p = tri.v[2].p;
                        func_002075F0(&edge, ot, (u32)depth);
                        func_002075F0(&tri, ot, (u32)depth);
                    }
                }
            }
        }
        g->t3++;
        if (g->t3 > 0x96) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x13F) {
        g->on4 = 1;
        g->t4 = 0;
        for (k = 0; k < 64; k++) {
            n = (func_0019A5C8() >> 23) % 32;
            g->dv[k].x = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][0];
            g->dv[k].y = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][1];
            g->dv[k].z = 0.2f * g->h * D_0028BC10[(func_0019A5C8() >> 23) % 4][n][2];
            g->dv[k].w = 1.0f;
        }
    }

    ((Spr_b249_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b249_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b249_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b249_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b249_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020C940(m2, 0, 0, &g->pos);
    func_0020BC00(m, m2);
    if (g->on4 == 1) {
        r = 0.5f * g->h + 0.5f * g->h * g->t4 / 32.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        alpha = (u32)(200.0f * func_00100FF0(g->t4, 32.0f, 16.0f));
        spr.c.r = 0xC8;
        spr.c.g = 0xC8;
        spr.c.b = 0xC8;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.5f + 0.5f * g->t4 / 32.0f;
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->dv[k], s);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->c4[k] % 4 * 32;
            y = (g->c4[k] >> 2) * 32;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b249_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t4++;
        if (g->t4 > 32) {
            g->on4 = 0;
        }
    }

    if (g->t == 0xDE) {
        func_001F6730(g->unitB, 0);
    }
    if (g->t == 0x13E) {
        func_001F6730(g->unitB, 1);
    }
    if (g->t == 0x70) {
        ret = 1;
    } else {
        if (g->t > 0x7A && g->t < 0xE8) {
            ret = 6;
        }
        if (g->t == 0xE8) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x15F) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset
