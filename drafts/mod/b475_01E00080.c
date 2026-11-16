#include "common.h"

/* shape b475:01E00080 (b475), 1302 insns, 1 copy: b475 module main (b512:01E00080's family, written from the asm;
   HARD draft, 855/1302): setup clears the scene, takes both units, two textures and five joints; frames 86..233 start
   a two-flame burst per frame at the first joint toward the target, each burst draws two quads for 128 frames then
   drops a ring pair, rings draw two sprites (two textures) for 25 frames, frames 24..48 every third start a 2x4 spark
   wave at the joint pairs; returns 1/6/2 at 203/214..385/386, 8 from 388 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b475_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b475_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b475_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b475_01E00080 c;
    Uv_b475_01E00080 uv0;
    Xyz_b475_01E00080 p0;
    Uv_b475_01E00080 uv1;
    Xyz_b475_01E00080 p1;
    u8 tail[0x20];
} Spr_b475_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b475_01E00080 c;
    Uv_b475_01E00080 uv0;
    Xyz_b475_01E00080 p0;
    Uv_b475_01E00080 uv1;
    Xyz_b475_01E00080 p1;
    Uv_b475_01E00080 uv2;
    Xyz_b475_01E00080 p2;
    Uv_b475_01E00080 uv3;
    Xyz_b475_01E00080 p3;
    u8 tail[0x20];
} Quad_b475_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    u8 padA[2];
    f32 sc[2];
    s32 ang[2];
    u8 pad1C[4];
    Vec4f base;
    Vec4f v[2];
} Burst_b475_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    u8 padA[2];
    f32 sc[2];
    u8 pad14[0xC];
    Vec4f p[2];
} Ring_b475_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][4];
    Vec4f p[2];
    Vec4f v[2][4];
} Wave_b475_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    s32 m0;
    u8 pad34[0xC];
    Vec4f pos0;
    s32 m[4];
    Vec4f pos[4];
    Burst_b475_01E00080 burst[128];
    s32 nring;
    u8 pad28A4[0xC];
    Ring_b475_01E00080 ring[24];
    s32 nwave;
    s32 iwave;
    u8 pad2EB8[8];
    Wave_b475_01E00080 wave[12];
    u8 pad36F0[0x10];
} Scene_b475_01E00080;

static s32 func_01E00080_b475(Scene_b475_01E00080 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00101080(void *, f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(s32, s32, s32, s32, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    u8 alpha2;
    f32 h;
    f32 s;
    f32 r;
    f32 qx;
    f32 qy;
    f32 depth;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f cq[2];
    Vec4f out[4];
    Vec4f v;
    Vec4f save[2];
    Spr_b475_01E00080 spr __attribute__((aligned(8)));
    Quad_b475_01E00080 pk __attribute__((aligned(8)));
    Vec4f *c1;
    s32 ot;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3700);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->m0 = func_001F5560(g->unitA, 7, 1);
        g->m[0] = func_001F5560(g->unitA, 0x26, 0);
        g->m[1] = func_001F5560(g->unitA, 0x35, 0);
        g->m[2] = func_001F5560(g->unitA, 0x2B, 0);
        g->m[3] = func_001F5560(g->unitA, 0x30, 0);
        for (i = 0; i < 128; i++) {
            g->burst[i].on = 0;
        }
        g->nring = 0;
        for (i = 0; i < 24; i++) {
            g->ring[i].on = 0;
        }
        g->nwave = 0;
        g->iwave = 0;
        for (i = 0; i < 12; i++) {
            g->wave[i].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    c1 = &cn[1];
    func_001F5620(g->unitA, g->m0, &g->pos0);
    for (i = 0; i < 4; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    if (g->t > 0x55 && g->t < 0xEA) {
        n = g->t % 128;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        g->burst[n].base = g->pos0;
        for (j = 0; j < 2; j++) {
            g->burst[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->burst[n].sc[j] = 0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            g->burst[n].ang[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            func_00101080(&g->burst[n].v[j], 1.0f);
            func_00187B00(&g->burst[n].v[j], &g->burst[n].v[j], &g->tgt);
            func_00187B18(&g->burst[n].v[j], &g->burst[n].v[j], &g->burst[n].base);
        }
    }

    ((Quad_b475_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Quad_b475_01E00080 *)(s32)&pk)->size = 9;
    ((Quad_b475_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Quad_b475_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Quad_b475_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_00208700(&pk, g->tex[0], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 128; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_00101020((f32)g->burst[i].t, 12.0f));
        pk.c.r = 0xB9;
        pk.c.g = 0xFF;
        pk.c.b = 0x58;
        pk.c.a = alpha;
        pk.c.q = 1.0f;
        s = func_00101050(g->burst[i].t, 0, 0x80) / 128.0f;
        h = 0.1f + 0.9f * s;
        for (j = 0; j < 2; j++) {
            ang = (g->burst[i].ang[j] + g->burst[i].t * 0x15B3) & 0xFFFF;
            r = 10.0f * (0.5f + 0.5f * g->burst[i].t / 128.0f) * g->burst[i].sc[j];
            qx = r * (0.9f + 0.1f * func_0020B550(ang));
            qy = r * (0.9f + 0.1f * func_0020B480(ang));
            cn[0].x = qx;
            cn[0].y = qx;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            c1->x = -qx;
            c1->y = qy;
            c1->z = 0.0f;
            c1->w = 1.0f;
            cq[0].x = qy;
            cq[0].y = -qx;
            cq[0].z = 0.0f;
            cq[0].w = 1.0f;
            cq[1].x = -qy;
            cq[1].y = -qy;
            cq[1].z = 0.0f;
            cq[1].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(c1, m3, c1);
            func_001878E0(&cq[0], m3, &cq[0]);
            func_001878E0(&cq[1], m3, &cq[1]);
            x = g->burst[i].c[j] % 4 * 32;
            y = (g->burst[i].c[j] >> 2) * 32;
            ((Uv_b475_01E00080 *)(s32)&pk.uv0)->u = x << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv0)->v = y << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv1)->u = (x + 32) << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv1)->v = y << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv2)->u = x << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv2)->v = (y + 32) << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv3)->u = (x + 32) << 4;
            ((Uv_b475_01E00080 *)(s32)&pk.uv3)->v = (y + 32) << 4;
            v.x = g->burst[i].v[j].x * h;
            v.y = g->burst[i].v[j].y * h;
            v.z = g->burst[i].v[j].z * s;
            func_00187B00(&v, &v, &g->burst[i].base);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], c1, &v);
            func_00187B00(&out[2], &cq[0], &v);
            func_00187B00(&out[3], &cq[1], &v);
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
            save[j] = v;
        }
        g->burst[i].t++;
        if (g->burst[i].t >= 0x80) {
            g->burst[i].on = 0;
            g->ring[g->nring].on = 1;
            g->ring[g->nring].t = 0;
            for (j = 0; j < 2; j++) {
                g->ring[g->nring].c[j] = (func_0019A5C8() >> 23) % 4 + 4;
                g->ring[g->nring].sc[j] = 0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
                g->ring[g->nring].p[j] = save[j];
            }
            g->nring++;
            if (g->nring >= 24) {
                g->nring = 0;
            }
        }
    }

    ((Spr_b475_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b475_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b475_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b475_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b475_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 24; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(128.0f * func_0020B480(g->ring[i].t * 0x4000 / 24));
        alpha2 = (u32)(64.0f * func_0020B480(g->ring[i].t * 0x4000 / 24));
        h = 30.0f * g->ring[i].t / 24.0f;
        for (j = 0; j < 2; j++) {
            r = 24.0f * (0.5f + 0.5f * g->ring[i].t / 24.0f) * g->ring[i].sc[j];
            cn[0].x = r;
            cn[0].y = r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            c1->x = -r;
            c1->y = -r;
            c1->z = 0.0f;
            c1->w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(c1, m3, c1);
            x = g->ring[i].c[j] % 4 * 32;
            y = (g->ring[i].c[j] >> 2) * 32;
            ((Uv_b475_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b475_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b475_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b475_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v = g->ring[i].p[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], c1, &v);
            func_00208700(&spr, g->tex[0], 1);
            spr.c.r = 0xB9;
            spr.c.g = 0xFF;
            spr.c.b = 0x58;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            v.y += h;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], c1, &v);
            func_00208700(&spr, g->tex[1], 1);
            spr.c.r = 0xC8;
            spr.c.g = 0xFF;
            spr.c.b = 0x58;
            spr.c.a = alpha2;
            spr.c.q = 1.0f;
            if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 24) {
            g->ring[i].on = 0;
        }
    }

    if (g->nwave < 9 && g->t == g->nwave * 3 + 0x18) {
        g->wave[g->iwave].on = 1;
        g->wave[g->iwave].t = 0;
        for (j = 0; j < 2; j++) {
            g->wave[g->iwave].p[j] = g->pos[g->nwave % 2 * 2 + j];
            for (k = 0; k < 4; k++) {
                g->wave[g->iwave].c[j][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->wave[g->iwave].v[j][k], 0.2f);
                g->wave[g->iwave].v[j][k].y = func_001A6970(g->wave[g->iwave].v[j][k].y);
            }
        }
        g->nwave++;
        g->iwave++;
        if (g->iwave >= 12) {
            g->iwave = 0;
        }
    }

    ((Spr_b475_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b475_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b475_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b475_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b475_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 12; i++) {
        if (g->wave[i].on == 0) {
            continue;
        }
        r = 5.0f * (0.5f + 0.5f * g->wave[i].t / 32.0f);
        cn[0].x = r;
        cn[0].y = r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        c1->x = -r;
        c1->y = -r;
        c1->z = 0.0f;
        c1->w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(c1, m3, c1);
        alpha = (u32)(128.0f * func_0020B480(g->wave[i].t << 14 >> 5));
        spr.c.r = 0x62;
        spr.c.g = 0x58;
        spr.c.b = 0x58;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->wave[i].t, 0x20, 1);
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 4; k++) {
                x = g->wave[i].c[j][k] % 4 * 32;
                y = (g->wave[i].c[j][k] >> 2) * 32;
                ((Uv_b475_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b475_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b475_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b475_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->wave[i].v[j][k], 0.1f + 0.9f * s);
                func_00187B00(&v, &v, &g->wave[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], c1, &v);
                if (func_00205630((s32)out, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->wave[i].t++;
        if (g->wave[i].t > 32) {
            g->wave[i].on = 0;
        }
    }
    if (g->t == 0xCB) {
        ret = 1;
    } else if (g->t > 0xD5 && g->t < 0x182) {
        ret = 6;
    } else if (g->t == 0x182) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0x183) {
        ret = 8;
    }
    return ret;
}
