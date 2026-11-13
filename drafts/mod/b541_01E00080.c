#include "common.h"

/* shape b541:01E00080 (b541), 2410 insns, 1 copy: b541 scene manager: code >= 0 clears the scene, takes both units,
   two textures and two models, builds 4 texture cells and random offset tables; else spawns and draws seven sprite
   effects (corner pairs at frames 31..79, a 64-spark burst at 116, pairs and quads at 116..184, 32- and 24-point
   rings at 186..208, a flash at 185) and returns 1 / 2 / 8 at frames 175 / 185 / 234 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b541_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b541_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b541_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b541_01E00080 c;
    Uv_b541_01E00080 uv0;
    Xyz_b541_01E00080 p0;
    Uv_b541_01E00080 uv1;
    Xyz_b541_01E00080 p1;
    u8 tail[0x20];
} Spr_b541_01E00080;

typedef struct {
    u16 c[4];
} Cell_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][2];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[2][2];
} SlotA_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[64];
    u8 rnd[64][2];
    u8 padC8[8];
    Vec4f pos;
    Vec4f v[64];
} Burst_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    u8 padA[6];
    Vec4f pos;
    Vec4f v[2];
} SlotC_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} SlotD_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f p[32];
} SlotF_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[24];
    u8 rnd[24][2];
    Vec4f p[24];
} SlotH_b541_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
} Flash_b541_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex[2];
    u8 pad18[8];
    Vec4f tgt;
    Cell_b541_01E00080 cell[4];
    s32 m0;
    u8 pad54[0xC];
    SlotA_b541_01E00080 a[32];
    s32 m1;
    u8 padC64[0xC];
    Burst_b541_01E00080 b;
    SlotC_b541_01E00080 c[32];
    SlotD_b541_01E00080 d[4];
    s32 nf;
    u8 pad1AD4[0xC];
    Vec4f df[32];
    SlotF_b541_01E00080 f[16];
    s32 nh;
    u8 pad3FE4[0xC];
    Vec4f dh[24];
    SlotH_b541_01E00080 h[32];
    Flash_b541_01E00080 fl;
} Scene_b541_01E00080;

static s32 func_01E00080_b541(s32 arg0, s32 code) {
    Scene_b541_01E00080 *g = (Scene_b541_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern s32 func_002087A0(void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern f32 D_0028BC10[4][32][3];
    extern u8 D_0030FF00[];
    s32 ot;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    u8 alpha;
    s32 row;
    s32 x;
    s32 y;
    f32 r;
    f32 h;
    f32 depth;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p0;
    Vec4f p1;
    Vec4f v;
    Spr_b541_01E00080 spr __attribute__((aligned(8)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x7B80);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->m0 = func_001F5560(g->unitA, 9, 1);
        g->m1 = func_001F5560(g->unitA, 7, 0);
        for (i = 0; i < 4; i++) {
            g->cell[i].c[0] = i % 2 << 6;
            g->cell[i].c[1] = g->cell[i].c[0] + 0x40;
            g->cell[i].c[2] = (i >> 1) << 6;
            g->cell[i].c[3] = g->cell[i].c[2] + 0x40;
            for (j = 0; j < 4; j++) {
                g->cell[i].c[j] <<= 4;
            }
        }
        for (i = 0; i < 32; i++) {
            g->a[i].on = 0;
        }
        g->b.on = 0;
        for (i = 0; i < 64; i++) {
            g->b.rnd[i][0] = (func_0019A5C8() >> 23) % 128;
            g->b.rnd[i][1] = (func_0019A5C8() >> 23) % 32 + 0x60;
        }
        for (i = 0; i < 32; i++) {
            g->c[i].on = 0;
        }
        for (i = 0; i < 4; i++) {
            g->d[i].on = 0;
        }
        g->nf = 0;
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 32; i++) {
            g->df[i].x = g->obj * (2.0f * D_0028BC10[0][i % 32][0]);
            g->df[i].y = 2.0f * D_0028BC10[2][i % 32][1];
            g->df[i].z = 2.0f * D_0028BC10[1][i % 32][2] * g->obj;
            g->df[i].w = 1.0f;
        }
        for (i = 0; i < 16; i++) {
            g->f[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            for (j = 0; j < 24; j++) {
                g->h[i].rnd[j][0] = (func_0019A5C8() >> 23) % 128;
                g->h[i].rnd[j][1] = (func_0019A5C8() >> 23) % 32 + 0x60;
            }
        }
        g->nh = 0;
        func_001F5F90(g->unitB, &g->tgt);
        for (row = 0; row < 24; row++) {
            g->dh[row].x = g->obj * (3.0f * D_0028BC10[0][row % 32][0]);
            g->dh[row].y = 3.0f * D_0028BC10[3][row % 32][1];
            g->dh[row].z = 3.0f * D_0028BC10[2][row % 32][2] * g->obj;
            g->dh[row].w = 1.0f;
        }
        for (row = 0; row < 32; row++) {
            g->h[row].on = 0;
        }
        g->fl.on = 0;
        return 0;
    }
    func_00205CA0(m3);

    if (g->t > 0x1E && g->t < 0x50) {
        n = g->t;
        n %= 32;
        g->a[n].on = 1;
        g->a[n].t = 0;
        func_001F5620(g->unitA, g->m0, &g->a[n].pos);
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                g->a[n].c[i][j] = (g->t + i + j) % 4;
                row = (g->t + i + j) % 32;
                g->a[n].v[i][j].x = 20.0f * (i * 2 - 1) + D_0028BC10[(func_0019A5C8() >> 23) % 4][row][0];
                g->a[n].v[i][j].y = -10.0f + D_0028BC10[(func_0019A5C8() >> 23) % 4][row][1];
                g->a[n].v[i][j].z = -30.0f * g->obj + D_0028BC10[(func_0019A5C8() >> 23) % 4][row][2];
                g->a[n].v[i][j].w = 1.0f;
            }
        }
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->a[i].on == 0) {
            continue;
        }
        r = 3.0f + 3.0f * g->a[i].t / 32.0f;
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
        alpha = (32 - g->a[i].t) * 48 >> 5;
        spr.c.r = 0x30;
        spr.c.g = 0x60;
        spr.c.b = 0xA0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = g->a[i].t / 32.0f;
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                func_00187B48(&v, &g->a[i].v[j][k], h);
                func_00187B00(&v, &v, &g->a[i].pos);
                func_00187B00(&p0, &cn[0], &v);
                func_00187B00(&p1, &cn[1], (void *)&v);
                ((Uv_b541_01E00080 *)&spr.uv0)->u = g->cell[g->a[i].c[j][k]].c[0];
                ((Uv_b541_01E00080 *)&spr.uv0)->v = g->cell[g->a[i].c[j][k]].c[2];
                ((Uv_b541_01E00080 *)&spr.uv1)->u = g->cell[g->a[i].c[j][k]].c[1];
                ((Uv_b541_01E00080 *)&spr.uv1)->v = g->cell[g->a[i].c[j][k]].c[3];
                if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->a[i].t++;
        if (g->a[i].t > 32) {
            g->a[i].on = 0;
        }
    }

    if (g->t == 0x74) {
        g->b.on = 1;
        g->b.t = 0;
        func_001F5620(g->unitA, g->m1, &g->b.pos);
        for (i = 0; i < 64; i++) {
            g->b.c[i] = i % 4;
            row = i % 32;
            g->b.v[i].x = 1.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][0];
            g->b.v[i].y = 1.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][1];
            g->b.v[i].z = 1.5f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][2];
            g->b.v[i].w = 1.0f;
        }
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    if (g->b.on == 1) {
        r = 4.0f + 4.0f * g->b.t / 64.0f;
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
        h = func_00100D50(g->b.t, 64, 1);
        for (i = 0; i < 64; i++) {
            alpha = g->b.rnd[i][1] * (64 - g->b.t) >> 6;
            switch (i % 7) {
            case 0:
                spr.c.r = 0xFF;
                spr.c.g = 0;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 2:
                spr.c.r = 0xFF;
                spr.c.g = 0xFF;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 4:
                spr.c.r = 0;
                spr.c.g = 0xFF;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 1:
                spr.c.r = 0;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 6:
                spr.c.r = 0;
                spr.c.g = 0;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 3:
                spr.c.r = 0xFF;
                spr.c.g = 0;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 5:
                spr.c.r = 0;
                spr.c.g = 0x80;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            default:
                spr.c.r = 0xFF;
                spr.c.g = 0;
                spr.c.b = 0xFF;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            }
            func_00187B48(&v, &g->b.v[i], h);
            func_00187B00(&v, &v, &g->b.pos);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            x = 0;
            y = 0;
            ((Uv_b541_01E00080 *)&spr.uv0)->u = x << 4;
            ((Uv_b541_01E00080 *)&spr.uv0)->v = y << 4;
            ((Uv_b541_01E00080 *)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b541_01E00080 *)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->b.t++;
        if (g->b.t > 64) {
            g->b.on = 0;
        }
    }

    if (g->t > 0x73 && g->t < 0xB9) {
        n = g->t;
        n %= 32;
        g->c[n].on = 1;
        g->c[n].t = 0;
        func_001F5620(g->unitA, g->m0, &g->c[n].pos);
        for (i = 0; i < 2; i++) {
            g->c[n].c[i] = (g->t + i) % 4;
            row = (g->t + i) % 32;
            g->c[n].v[i].x = D_0028BC10[(func_0019A5C8() >> 23) % 4][row][0];
            g->c[n].v[i].y = D_0028BC10[(func_0019A5C8() >> 23) % 4][row][1];
            g->c[n].v[i].z = D_0028BC10[(func_0019A5C8() >> 23) % 4][row][2];
            g->c[n].v[i].w = 1.0f;
        }
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->c[i].on == 0) {
            continue;
        }
        r = 3.6000001f + 8.4f * g->c[i].t / 32.0f;
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
        alpha = (32 - g->c[i].t) * 128 >> 5;
        switch (i % 7) {
        case 0:
            spr.c.r = 0x80;
            spr.c.g = 0x20;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 2:
            spr.c.r = 0x80;
            spr.c.g = 0x80;
            spr.c.b = 0x20;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 4:
            spr.c.r = 0x20;
            spr.c.g = 0x80;
            spr.c.b = 0;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 1:
            spr.c.r = 0x20;
            spr.c.g = 0x80;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 6:
            spr.c.r = 0x20;
            spr.c.g = 0x20;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 3:
            spr.c.r = 0x80;
            spr.c.g = 0x20;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 5:
            spr.c.r = 0x20;
            spr.c.g = 0x40;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        default:
            spr.c.r = 0x80;
            spr.c.g = 0x20;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        }
        h = g->c[i].t / 32.0f;
        for (k = 0; k < 2; k++) {
            func_00187B48(&v, &g->c[i].v[k], h);
            func_00187B00(&v, &v, &g->c[i].pos);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            ((Uv_b541_01E00080 *)&spr.uv0)->u = g->cell[g->c[i].c[k]].c[0];
            ((Uv_b541_01E00080 *)&spr.uv0)->v = g->cell[g->c[i].c[k]].c[2];
            ((Uv_b541_01E00080 *)&spr.uv1)->u = g->cell[g->c[i].c[k]].c[1];
            ((Uv_b541_01E00080 *)&spr.uv1)->v = g->cell[g->c[i].c[k]].c[3];
            if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->c[i].t++;
        if (g->c[i].t > 32) {
            g->c[i].on = 0;
        }
    }

    if (g->t > 0x73 && g->t < 0xB9) {
        n = g->t;
        n %= 4;
        g->d[n].on = 1;
        g->d[n].t = 0;
        func_001F5620(g->unitA, g->m0, &g->d[n].pos);
        for (k = 0; k < 4; k++) {
            g->d[n].c[k] = (g->t + k) % 4;
            row = (g->t + k) % 32;
            g->d[n].v[k].x = 0.1f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][0];
            g->d[n].v[k].y = 0.1f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][1];
            g->d[n].v[k].z = 0.1f * D_0028BC10[(func_0019A5C8() >> 23) % 4][row][2];
            g->d[n].v[k].w = 1.0f;
        }
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->d[i].on == 0) {
            continue;
        }
        r = 3.0f + 3.0f * g->d[i].t / 4.0f;
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
        alpha = (4 - g->d[i].t) * 128 >> 2;
        spr.c.r = 0x40;
        spr.c.g = 0x40;
        spr.c.b = 0;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = g->d[i].t / 4.0f;
        for (k = 0; k < 4; k++) {
            func_00187B48(&v, &g->d[i].v[k], h);
            func_00187B00(&v, &v, &g->d[i].pos);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            ((Uv_b541_01E00080 *)&spr.uv0)->u = g->cell[g->d[i].c[k]].c[0];
            ((Uv_b541_01E00080 *)&spr.uv0)->v = g->cell[g->d[i].c[k]].c[2];
            ((Uv_b541_01E00080 *)&spr.uv1)->u = g->cell[g->d[i].c[k]].c[1];
            ((Uv_b541_01E00080 *)&spr.uv1)->v = g->cell[g->d[i].c[k]].c[3];
            if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->d[i].t++;
        if (g->d[i].t > 4) {
            g->d[i].on = 0;
        }
    }

    if (g->t > 0xB9 && g->t < 0xC9) {
        n = g->t;
        n %= 16;
        g->f[n].on = 1;
        g->f[n].t = 0;
        h = func_00100D50(g->nf, 16, 1);
        for (k = 0; k < 32; k++) {
            func_00187B48(&g->f[n].p[k], &g->df[k], h);
            func_00187B00(&g->f[n].p[k], &g->f[n].p[k], &g->tgt);
        }
        for (k = 0; k < 32; k++) {
            g->f[n].c[k] = (g->t + k) % 4;
        }
        g->nf++;
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->f[i].on == 0) {
            continue;
        }
        r = 2.0f + 8.0f * g->f[i].t / 16.0f;
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
        alpha = (16 - g->f[i].t) * 255 >> 4;
        switch (i % 7) {
        case 0:
            spr.c.r = 0x80;
            spr.c.g = 0;
            spr.c.b = 0;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 2:
            spr.c.r = 0x80;
            spr.c.g = 0x80;
            spr.c.b = 0;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 4:
            spr.c.r = 0;
            spr.c.g = 0x80;
            spr.c.b = 0;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 1:
            spr.c.r = 0;
            spr.c.g = 0x80;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 6:
            spr.c.r = 0;
            spr.c.g = 0;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 3:
            spr.c.r = 0x80;
            spr.c.g = 0;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        case 5:
            spr.c.r = 0;
            spr.c.g = 0x40;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        default:
            spr.c.r = 0x80;
            spr.c.g = 0;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            break;
        }
        for (k = 0; k < 32; k++) {
            func_00187B00(&p0, &cn[0], &g->f[i].p[k]);
            func_00187B00(&p1, &cn[1], (void *)&g->f[i].p[k]);
            ((Uv_b541_01E00080 *)&spr.uv0)->u = g->cell[g->f[i].c[k]].c[0];
            ((Uv_b541_01E00080 *)&spr.uv0)->v = g->cell[g->f[i].c[k]].c[2];
            ((Uv_b541_01E00080 *)&spr.uv1)->u = g->cell[g->f[i].c[k]].c[1];
            ((Uv_b541_01E00080 *)&spr.uv1)->v = g->cell[g->f[i].c[k]].c[3];
            if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->f[i].t++;
        if (g->f[i].t > 16) {
            g->f[i].on = 0;
        }
    }

    if (g->t > 0xB9 && g->t < 0xD1) {
        n = g->t;
        n %= 32;
        g->h[n].on = 1;
        g->h[n].t = 0;
        h = g->nh / 24.0f;
        for (k = 0; k < 24; k++) {
            func_00187B48(&g->h[n].p[k], &g->dh[k], h);
            func_00187B00(&g->h[n].p[k], &g->h[n].p[k], &g->tgt);
        }
        for (k = 0; k < 24; k++) {
            g->h[n].c[k] = (g->t + k) % 4;
        }
        g->nh++;
    }

    ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->h[i].on == 0) {
            continue;
        }
        r = 2.4f + 9.6f * g->h[i].t / 32.0f;
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
        for (k = 0; k < 24; k++) {
            alpha = g->h[i].rnd[k][1] * (32 - g->h[i].t) >> 5;
            switch (i % 7) {
            case 0:
                spr.c.r = 0x80;
                spr.c.g = 0;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 2:
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 4:
                spr.c.r = 0;
                spr.c.g = 0x80;
                spr.c.b = 0;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 1:
                spr.c.r = 0;
                spr.c.g = 0x80;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 6:
                spr.c.r = 0;
                spr.c.g = 0;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 3:
                spr.c.r = 0x80;
                spr.c.g = 0;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            case 5:
                spr.c.r = 0;
                spr.c.g = 0x40;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            default:
                spr.c.r = 0x80;
                spr.c.g = 0;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                break;
            }
            func_00187B00(&p0, &cn[0], &g->h[i].p[k]);
            func_00187B00(&p1, &cn[1], (void *)&g->h[i].p[k]);
            x = 0;
            y = 0;
            ((Uv_b541_01E00080 *)&spr.uv0)->u = x << 4;
            ((Uv_b541_01E00080 *)&spr.uv0)->v = y << 4;
            ((Uv_b541_01E00080 *)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b541_01E00080 *)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->h[i].t++;
        if (g->h[i].t > 32) {
            g->h[i].on = 0;
        }
    }

    if (g->t == 0xB9) {
        g->fl.on = 1;
        g->fl.t = 0;
    }
    if (g->fl.on == 1) {
        ((Spr_b541_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b541_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b541_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b541_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b541_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_002087A0(&spr, 1);
        func_00208CB0(&spr, 5);
        x = 42;
        y = 29;
        ((Uv_b541_01E00080 *)&spr.uv0)->u = x << 4;
        ((Uv_b541_01E00080 *)&spr.uv0)->v = y << 4;
        ((Uv_b541_01E00080 *)&spr.uv1)->u = 598 << 4;
        ((Uv_b541_01E00080 *)&spr.uv1)->v = 419 << 4;
        alpha = ((48 - g->fl.t) << 6) / 48;
        spr.c.r = 0xFF;
        spr.c.g = 0xC8;
        spr.c.b = 0xC8;
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
        g->fl.t++;
        if (g->fl.t > 48) {
            g->fl.on = 0;
        }
    }

    if (g->t == 0xAF) {
        ret = 1;
    } else if (g->t == 0xB9) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0xE9) {
        ret = 8;
    }
    return ret;
}
