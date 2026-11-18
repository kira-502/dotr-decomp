#include "common.h"

/* shape b647:01E00080 (b647), 2848 insns, 1 copy: scene effect (draft, 2837/2848, 7 words): rim rings, arcs, flares,
   rays with pops, bursts and halos. Still different: the arc loop's h and x0 in each other's saved FPRs ($f24/$f26) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b647_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b647_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b647_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b647_01E00080 c;
    Uv_b647_01E00080 uv0;
    Xyz_b647_01E00080 p0;
    Uv_b647_01E00080 uv1;
    Xyz_b647_01E00080 p1;
    u8 tail[0x20];
} Spr_b647_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b647_01E00080 c;
        f32 s;
        f32 t;
        Xyz_b647_01E00080 p;
    } v[4];
    u8 tail[0x20];
} Pk_b647_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b647_01E00080 c;
        Xyz_b647_01E00080 p;
    } v[4];
    u64 tail;
} Quad_b647_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b647_01E00080 c;
        Xyz_b647_01E00080 p;
    } v[3];
    u64 tail;
} Tri_b647_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b647_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
} Rim_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 delay[2][6];
    f32 w[2][6];
    f32 len[2][6];
    f32 amp[2][6];
    u8 padC8[8];
    Mtx_b647_01E00080 mat[2][6];
} Arc_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 delay[4];
    f32 w[4];
    f32 amp[4];
    s32 ang[4];
} Flare_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p;
    Vec4f d;
    f32 len;
    f32 a[8];
    f32 b[8];
    u8 pad74[0xC];
    Mtx_b647_01E00080 mat[8];
} Ray_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c;
    u8 padC[4];
    Vec4f p;
} Pop_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p;
    Vec4f v[64];
} Burst_b647_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p;
} Halo_b647_01E00080;

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
    Rim_b647_01E00080 rim[17];
    u8 on;
    u8 pad281[3];
    s32 t1;
    u8 col[9][4];
    u8 pad2AC[4];
    Arc_b647_01E00080 arc[16];
    Flare_b647_01E00080 flare[16];
    s32 cnt;
    s32 idx;
    u8 pad4438[8];
    Ray_b647_01E00080 ray[24];
    s32 npop;
    u8 pad8044[0xC];
    Pop_b647_01E00080 pop[12];
    s32 nburst;
    u8 pad81D4[0xC];
    Burst_b647_01E00080 burst[16];
    Vec4f ring[17];
    s32 nhalo;
    u8 padC4F4[0xC];
    Halo_b647_01E00080 halo[16];
} Scene_b647_01E00080;

static s32 func_01E00080_b647(s32 arg0, s32 code) {
    Scene_b647_01E00080 *g = (Scene_b647_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00100E40(void *, void *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020CB20(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern f32 D_0028BC10[4][32][3];
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 n;
    u8 a1;
    u8 a2;
    s32 seg;
    s32 cnt;
    f32 a;
    f32 len;
    f32 e;
    f32 h;
    f32 s;
    f32 r;
    f32 t0;
    f32 t1;
    f32 w;
    f32 y0;
    f32 y1;
    f32 x0;
    f32 x1;
    f32 m[4][4];
    f32 m2[4][4];
    Mtx_b647_01E00080 m3;
    Vec4f cn[4];
    Vec4f out[4];
    Vec4f v;
    Vec4f mid;
    Tri_b647_01E00080 tri __attribute__((aligned(8)));
    Quad_b647_01E00080 ln __attribute__((aligned(8)));
    Pk_b647_01E00080 pk __attribute__((aligned(8)));
    Spr_b647_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xC700);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(4, 0xF);
        g->tex[1] = func_00202BF0(5, 0);
        g->tex[2] = func_00202BF0(5, 1);
        g->jn[0] = func_001F5560(g->unitA, 0xA, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x1D, 0);
        func_001F5F90(g->unitB, &g->tgt);
        for (i = 0; i < 17; i++) {
            g->rim[i].a.x = 4.0f * func_0020B550((i << 16) >> 4);
            g->rim[i].a.y = 4.0f * func_0020B480((i << 16) >> 4);
            g->rim[i].a.z = 0.0f;
            g->rim[i].a.w = 1.0f;
            g->rim[i].b.x = 12.0f * func_0020B550((i << 16) >> 4);
            g->rim[i].b.y = 12.0f * func_0020B480((i << 16) >> 4);
            g->rim[i].b.z = 0.0f;
            g->rim[i].b.w = 1.0f;
        }
        k = 0;
        g->on = k;
        g->t1 = 0;
        for (i = 0; i < 9; i++) {
            h = i / 8.0f;
            s = 1.0f - h;
            g->col[i][0] = (u32)(96.0f * s);
            g->col[i][1] = (u32)(128.0f * s);
            g->col[i][2] = (u32)(255.0f * s + 128.0f * h);
            g->col[i][3] = (u32)(255.0f * s);
        }
        for (k = 0; k < 16; k++) {
            g->arc[k].on = 0;
        }
        for (k = 0; k < 16; k++) {
            g->flare[k].on = 0;
        }
        g->cnt = 0;
        g->idx = 0;
        for (i = 0; i < 24; i++) {
            g->ray[i].on = 0;
        }
        g->npop = 0;
        for (i = 0; i < 12; i++) {
            g->pop[i].on = 0;
        }
        g->nburst = 0;
        for (i = 0; i < 16; i++) {
            g->burst[i].on = 0;
        }
        for (i = 0; i < 17; i++) {
            g->ring[i].x = 64.0f * func_0020B550((i << 16) >> 4);
            g->ring[i].y = 64.0f * func_0020B480((i << 16) >> 4);
            g->ring[i].z = 0.0f;
            g->ring[i].w = 1.0f;
        }
        g->nhalo = 0;
        for (n = 0; n < 16; n++) {
            g->halo[n].on = 0;
        }
        return 0;
    }
    func_00205CA0(&m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }
    func_00187B00(&mid, &g->jp[0], &g->jp[1]);
    func_00187B48((void *)&mid, &mid, 0.5f);
    w = func_001A6C60(func_001A6C48(g->jp[0].x - g->jp[1].x, 2.0f) + func_001A6C48(g->jp[0].y - g->jp[1].y, 2.0f) +
                        func_001A6C48(g->jp[0].z - g->jp[1].z, 2.0f));
    if (g->t == 0) {
        g->on = 1;
        g->t1 = 0;
    }

    ((Quad_b647_01E00080 *)(s32)&ln)->flags = 0x14;
    ((Quad_b647_01E00080 *)(s32)&ln)->size = 8;
    ((Quad_b647_01E00080 *)(s32)&ln)->regs = 0x41414141;
    ((Quad_b647_01E00080 *)(s32)&ln)->pad4 = 0;
    func_002086D0(&ln, func_00208D00(1));
    e = func_00101020((f32)g->t1, 32.0f) * func_00100FF0((f32)g->t1, 400.0f, 368.0f);
    if (g->on == 1) {
        a1 = (u32)(200.0f * e);
        (void)a1;
        ln.v[0].c.r = 0xA4;
        ln.v[0].c.g = 0x80;
        ln.v[0].c.b = 0xA4;
        ln.v[0].c.a = a1;
        ln.v[0].c.q = 1.0f;
        ln.v[2].c.r = 0;
        ln.v[2].c.g = 0;
        ln.v[2].c.b = 0xFF;
        ln.v[2].c.a = 0;
        ln.v[2].c.q = 1.0f;
        ln.v[1].c = ln.v[0].c;
        ln.v[3].c = ln.v[2].c;
        for (n = 0; n < 2; n++) {
            func_0020EB40(m);
            func_00187B60(m2, &m3, &g->jp[n]);
            r = 0.9f + 0.1f * (f32)((g->t1 + n) % 2);
            v.x = r;
            v.y = r;
            v.z = r;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (l = 0; l < 16; l++) {
                if (func_00100BA0(&g->rim[l].a, &g->rim[l + 1].a, &g->rim[l].b, &g->rim[l + 1].b, m, &ln, &depth) == 1) {
                    func_002075F0(&ln, ot, (u32)depth);
                }
            }
        }
        g->t1++;
        if (g->t1 > 400) {
            g->on = 0;
        }
    }

    if (g->t > 0 && g->t < 400) {
        n = g->t % 16;
        (void)n;
        g->arc[n].on = 1;
        g->arc[n].t = 0;
        for (k = 0; k < 2; k++) {
            for (i = 0; i < 6; i++) {
                g->arc[n].delay[k][i] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->arc[n].w[k][i] = 2.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->arc[n].len[k][i] = 25.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                g->arc[n].amp[k][i] = 4.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256 + 1) / 256.0f);
                v.x = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
                v.y = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
                v.z = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
                v.w = 1.0f;
                func_00100E40(&g->arc[n].mat[k][i], &v);
                func_00100E00(&g->arc[n].mat[k][i], (i << 16) / 6, 2);
            }
        }
    }

    ((Pk_b647_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Pk_b647_01E00080 *)(s32)&pk)->size = 0xC;
    ((Pk_b647_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pk_b647_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x12340BA);
    for (n = 0; n < 16; n++) {
        if (g->arc[n].on == 0) {
            continue;
        }
        for (l = 0; l < 2; l++) {
            for (seg = 0; seg < 6; seg++) {
                if (g->arc[n].t > g->arc[n].delay[l][seg]) {
                    continue;
                }
                func_0020EB40(m);
                func_0020C940(m2, 0, 0, &g->jp[l]);
                func_0020BC00(m2, &g->arc[n].mat[l][seg]);
                func_0020BC00(m, m2);
                x1 = 1.0f - func_00100D50(g->arc[n].t, g->arc[n].delay[l][seg], 1);
                h = 1.0f + (1.0f - x1);
                for (j = 0; j < 8; j++) {
                    a1 = (u32)(e * (g->col[j][3] * x1));
                    a2 = (u32)(e * (g->col[j + 1][3] * x1));
                    pk.v[0].c.r = g->col[j][0];
                    pk.v[0].c.g = g->col[j][1];
                    pk.v[0].c.b = g->col[j][2];
                    pk.v[0].c.a = a1;
                    pk.v[0].c.q = 1.0f;
                    pk.v[2].c.r = g->col[j + 1][0];
                    pk.v[2].c.g = g->col[j + 1][1];
                    pk.v[2].c.b = g->col[j + 1][2];
                    pk.v[2].c.a = a2;
                    pk.v[2].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    pk.v[3].c = pk.v[2].c;
                    t0 = 0.5f * (j % 4) / 4.0f;
                    t1 = 0.5f * (j % 4 + 1) / 4.0f;
                    pk.v[0].s = 0.0390625f;
                    pk.v[0].t = t0;
                    pk.v[1].s = 0.2109375f;
                    pk.v[1].t = t0;
                    pk.v[2].s = 0.0390625f;
                    pk.v[2].t = t1;
                    pk.v[3].s = 0.2109375f;
                    pk.v[3].t = t1;
                    a = g->arc[n].len[l][seg] * j / 8.0f;
                    len = g->arc[n].len[l][seg] * (j + 1) / 8.0f;
                    x0 = g->arc[n].w[l][seg] * x1;
                    y0 = h * (g->arc[n].amp[l][seg] * func_0020B550((j << 16) >> 3));
                    y1 = h * (g->arc[n].amp[l][seg] * func_0020B550(((j + 1) << 16) >> 3));
                    cn[0].x = y0;
                    cn[0].y = -x0 + y0;
                    cn[0].z = a;
                    cn[0].w = 1.0f;
                    cn[1].x = y0;
                    cn[1].y = x0 + y0;
                    cn[1].z = a;
                    cn[1].w = 1.0f;
                    cn[2].x = y1;
                    cn[2].y = -x0 + y1;
                    cn[2].z = len;
                    cn[2].w = 1.0f;
                    cn[3].x = y1;
                    cn[3].y = x0 + y1;
                    cn[3].z = len;
                    cn[3].w = 1.0f;
                    if (func_00205630(cn, D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        g->arc[n].t++;
        if (g->arc[n].t > 16) {
            g->arc[n].on = 0;
        }
    }

    if (g->t > 0x50 && g->t < 400) {
        n = g->t % 16;
        (void)n;
        g->flare[n].on = 1;
        g->flare[n].t = 1;
        for (seg = 0; seg < 4; seg++) {
            g->flare[n].delay[seg] = (s32)(16.0f * (0.7f + 0.3f * ((func_0019A5C8() >> 23) % 256) / 256.0f));
            g->flare[n].w[seg] = 3.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->flare[n].amp[seg] = 3.5f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
            g->flare[n].ang[seg] = ((func_0019A5C8() >> 23) % 256 << 16 >> 8) & 0xFFFF;
        }
    }

    ((Pk_b647_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Pk_b647_01E00080 *)(s32)&pk)->size = 0xC;
    ((Pk_b647_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pk_b647_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x12340BA);
    n = g->t - 0x50;
    if (n < 0) {
        n = 0;
    }
    e = func_00101020((f32)n, 32.0f) * func_00100FF0((f32)n, 320.0f, 288.0f);
    for (i = 0; i < 16; i++) {
        if (g->flare[i].on == 0) {
            continue;
        }
        for (k = 0; k < 4; k++) {
            if (g->flare[i].t > g->flare[i].delay[k]) {
                continue;
            }
            func_0020EB40(m);
            func_0020C940(m2, 0, 0, &mid);
            func_00100E00(m2, g->flare[i].ang[k], 0);
            func_0020BC00(m, m2);
            s = 1.0f - func_00100D50(g->flare[i].t, g->flare[i].delay[k], 1);
            a1 = (u32)(255.0f * s * e);
            (void)a1;
            pk.v[0].c.r = 0xA4;
            pk.v[0].c.g = 0x64;
            pk.v[0].c.b = 0xFF;
            pk.v[0].c.a = a1;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            for (n = 0; n < 8; n++) {
                h = 1.0f + (1.0f - s);
                t0 = 0.5f * (n % 4) / 4.0f;
                t1 = 0.5f * (n % 4 + 1) / 4.0f;
                pk.v[0].s = 0.0390625f;
                pk.v[0].t = t0;
                pk.v[1].s = 0.2109375f;
                pk.v[1].t = t0;
                pk.v[2].s = 0.0390625f;
                pk.v[2].t = t1;
                pk.v[3].s = 0.2109375f;
                pk.v[3].t = t1;
                a = w * n / 8.0f - w / 2.0f;
                len = w * (n + 1) / 8.0f - w / 2.0f;
                x0 = g->flare[i].w[k] * s;
                y0 = h * (g->flare[i].amp[k] * func_0020B480((((n << 16) >> 3) + (i * 5555 + k * 6666)) & 0xFFFF));
                y1 = h * (g->flare[i].amp[k] * func_0020B480(((((n + 1) << 16) >> 3) + (i * 5555 + k * 6666)) & 0xFFFF));
                cn[0].x = a;
                cn[0].y = -x0 + y0;
                cn[0].z = 0.0f;
                cn[0].w = 1.0f;
                cn[1].x = a;
                cn[1].y = x0 + y0;
                cn[1].z = 0.0f;
                cn[1].w = 1.0f;
                cn[2].x = len;
                cn[2].y = -x0 + y1;
                cn[2].z = 0.0f;
                cn[2].w = 1.0f;
                cn[3].x = len;
                cn[3].y = x0 + y1;
                cn[3].z = 0.0f;
                cn[3].w = 1.0f;
                if (func_00205630(cn, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->flare[i].t++;
        if (g->flare[i].t > 16) {
            g->flare[i].on = 0;
        }
    }

    if (g->t > 0xC8 && g->t < 0x159) {
        if (g->cnt % 10 == 0) {
            g->ray[g->idx].on = 1;
            g->ray[g->idx].t = 0;
            g->ray[g->idx].p = g->jp[(g->idx + 1) % 2];
            g->ray[g->idx].d.x = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
            g->ray[g->idx].d.y = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1];
            g->ray[g->idx].d.z = D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
            g->ray[g->idx].d.w = 1.0f;
            func_00187B00(&g->ray[g->idx].d, &g->ray[g->idx].d, &g->tgt);
            func_00187B18(&g->ray[g->idx].d, &g->ray[g->idx].d, &g->ray[g->idx].p);
            g->ray[g->idx].len = func_001A6C60(func_001A6C48(g->ray[g->idx].d.x, 2.0f) +
                                               func_001A6C48(g->ray[g->idx].d.y, 2.0f) +
                                               func_001A6C48(g->ray[g->idx].d.z, 2.0f));
            for (i = 0; i < 8; i++) {
                g->ray[g->idx].a[i] = 8.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
                g->ray[g->idx].b[i] = 6.0f * (0.5f + 0.5f * ((func_0019A5C8() >> 23) % 256) / 256.0f);
                func_00100E40(&g->ray[g->idx].mat[i], &g->ray[g->idx].d);
                func_00100E00(&g->ray[g->idx].mat[i], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
            }
            g->idx++;
            if (g->idx >= 24) {
                g->idx = 0;
            }
        }
        g->cnt++;
    }

    ((Spr_b647_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b647_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b647_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b647_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b647_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    ((Pk_b647_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Pk_b647_01E00080 *)(s32)&pk)->size = 0xC;
    ((Pk_b647_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pk_b647_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, ((u64)0x1FC << 32) | 0x12340BA);
    for (i = 0; i < 24; i++) {
        if (g->ray[i].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        a1 = (u32)(255.0f * func_00100FF0((f32)g->ray[i].t, 24.0f, 16.0f));
        spr.c.r = 0xA4;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = a1;
        spr.c.q = 1.0f;
        ((Uv_b647_01E00080 *)(s32)&spr.uv0)->u = 0;
        ((Uv_b647_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b647_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b647_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        if (g->ray[i].t < 4) {
            r = 0.5f;
        } else {
            r = 1.0f;
        }
        s = 25.0f * r;
        cn[0].x = -s;
        cn[0].y = -s;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = s;
        cn[1].y = s;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        h = func_00101020((f32)g->ray[i].t, 4.0f);
        func_00187B48(&v, &g->ray[i].d, h);
        func_00187B00(&v, &v, &g->ray[i].p);
        if (g->ray[i].t == 4) {
            n = g->npop;
            g->pop[n].on = 1;
            g->pop[n].t = 0;
            g->pop[n].c = (func_0019A5C8() >> 23) % 8;
            g->pop[n].p = v;
            g->npop++;
            if (g->npop >= 12) {
                g->npop = 0;
            }
            n = g->nburst;
            g->burst[n].on = 1;
            g->burst[n].t = 0;
            g->burst[n].p = v;
            for (k = 0; k < 64; k++) {
                func_00101080(&g->burst[n].v[k], 2.0f);
            }
            g->nburst++;
            if (g->nburst >= 16) {
                g->nburst = 0;
            }
            n = g->nhalo;
            g->halo[n].on = 1;
            g->halo[n].t = 0;
            g->halo[n].p = v;
            g->nhalo++;
            if (g->nhalo >= 16) {
                g->nhalo = 0;
            }
        }
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        cnt = (s32)(8.0f * h);
        if (cnt > 8) {
            cnt = 8;
        }
        x1 = 1.0f - func_00100D50(g->ray[i].t, 24, 1);
        a1 = (u32)(255.0f * x1);
        (void)a1;
        pk.v[0].c.r = 0x60;
        pk.v[0].c.g = 0x40;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = a1;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        for (l = 0; l < 8; l++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->ray[i].mat[l], &g->ray[i].p);
            func_0020BC00(m, m2);
            for (n = 0; n < cnt; n++) {
                t0 = 0.5f * (n % 3) / 3.0f;
                t1 = 0.5f * (n % 3 + 1) / 3.0f;
                pk.v[0].s = 0.0390625f;
                pk.v[0].t = t0;
                pk.v[1].s = 0.2109375f;
                pk.v[1].t = t0;
                pk.v[2].s = 0.0390625f;
                pk.v[2].t = t1;
                pk.v[3].s = 0.2109375f;
                pk.v[3].t = t1;
                a = g->ray[i].len * n / 8.0f;
                len = g->ray[i].len * (n + 1) / 8.0f;
                x0 = g->ray[i].a[l] * x1;
                h = 1.0f + 1.5f * (1.0f - x1);
                y0 = h * (g->ray[i].b[l] * func_0020B480((((n << 16) >> 3) + (i * 5555 + l * 6666)) & 0xFFFF));
                y1 = h * (g->ray[i].b[l] * func_0020B480(((((n + 1) << 16) >> 3) + (i * 5555 + l * 6666)) & 0xFFFF));
                out[0].x = 0.0f;
                out[0].y = -x0 + y0;
                out[0].z = a;
                out[0].w = 1.0f;
                out[1].x = 0.0f;
                out[1].y = x0 + y0;
                out[1].z = a;
                out[1].w = 1.0f;
                out[2].x = 0.0f;
                out[2].y = -x0 + y1;
                out[2].z = len;
                out[2].w = 1.0f;
                out[3].x = 0.0f;
                out[3].y = x0 + y1;
                out[3].z = len;
                out[3].w = 1.0f;
                if (func_00205630(out, D_0030FF00, m, &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->ray[i].t++;
        if (g->ray[i].t > 24) {
            g->ray[i].on = 0;
        }
    }

    ((Spr_b647_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b647_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b647_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b647_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b647_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (k = 0; k < 12; k++) {
        if (g->pop[k].on == 0) {
            continue;
        }
        n = (12 - g->pop[k].t) * 255 / 12;
        spr.c.r = 0xFF;
        spr.c.g = 0x20;
        spr.c.b = 0x40;
        spr.c.a = n;
        spr.c.q = 1.0f;
        ((Uv_b647_01E00080 *)(s32)&spr.uv0)->u = g->pop[k].c % 4 * 32 << 4;
        ((Uv_b647_01E00080 *)(s32)&spr.uv0)->v = (g->pop[k].c >> 2) * 32 << 4;
        ((Uv_b647_01E00080 *)(s32)&spr.uv1)->u = (g->pop[k].c % 4 + 1) * 32 << 4;
        ((Uv_b647_01E00080 *)(s32)&spr.uv1)->v = ((g->pop[k].c >> 2) + 1) * 32 << 4;
        s = 24.0f * func_00100D50(g->pop[k].t, 12, 2);
        cn[0].x = -s;
        cn[0].y = -s;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = s;
        cn[1].y = s;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        func_00187B00(&out[0], &cn[0], &g->pop[k].p);
        func_00187B00(&out[1], &cn[1], (void *)&g->pop[k].p);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        g->pop[k].t++;
        if (g->pop[k].t > 12) {
            g->pop[k].on = 0;
        }
    }

    ((Spr_b647_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b647_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b647_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b647_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b647_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    ((Uv_b647_01E00080 *)(s32)&spr.uv0)->u = 0;
    ((Uv_b647_01E00080 *)(s32)&spr.uv0)->v = 0;
    ((Uv_b647_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b647_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    s = 2.5f;
    for (k = 0; k < 16; k++) {
        if (g->burst[k].on == 0) {
            continue;
        }
        n = (16 - g->burst[k].t) * 255 >> 4;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0xA4;
        spr.c.a = n;
        spr.c.q = 1.0f;
        cn[0].x = -s;
        cn[0].y = -s;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = s;
        cn[1].y = s;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], &m3, &cn[0]);
        func_001878E0(&cn[1], &m3, &cn[1]);
        r = 0.7f + 0.3f * func_00100D50(g->burst[k].t, 16, 1);
        for (n = 0; n < 64; n++) {
            func_00187B48(&v, &g->burst[k].v[n], r);
            func_00187B00(&v, &v, &g->burst[k].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[k].t++;
        if (g->burst[k].t > 16) {
            g->burst[k].on = 0;
        }
    }

    ((Tri_b647_01E00080 *)(s32)&tri)->flags = 0x13;
    ((Tri_b647_01E00080 *)(s32)&tri)->size = 6;
    ((Tri_b647_01E00080 *)(s32)&tri)->regs = 0x414141;
    ((Tri_b647_01E00080 *)(s32)&tri)->pad4 = 0;
    func_002086D0(&tri, func_00208D00(1));
    for (k = 0; k < 16; k++) {
        if (g->halo[k].on == 0) {
            continue;
        }
        func_0020EB40(m);
        func_00187B60(m2, &m3, &g->halo[k].p);
        r = 0.8f + 0.2f * func_00100D50(g->halo[k].t, 16, 1);
        v.x = r;
        v.y = r;
        v.z = r;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        a1 = (u32)(255.0f * ((16 - g->halo[k].t) / 16.0f));
        tri.v[0].c.r = 0xA4;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0xFF;
        tri.v[0].c.a = a1;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c.r = 0x20;
        tri.v[1].c.g = 0x20;
        tri.v[1].c.b = 0xFF;
        tri.v[1].c.a = 0;
        tri.v[1].c.q = 1.0f;
        tri.v[2].c = tri.v[1].c;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (l = 0; l < 16; l++) {
            if (func_00100B00(&v, &g->ring[l], &g->ring[l + 1], m, &tri, &depth) == 1) {
                func_002075F0(&tri, ot, (u32)depth);
            }
        }
        g->halo[k].t++;
        if (g->halo[k].t > 16) {
            g->halo[k].on = 0;
        }
    }

    if (g->t == 0xC2) {
        ret = 1;
    } else {
        if (g->t > 0xCC && g->t < 0x159) {
            ret = 6;
        }
        if (g->t == 0x159) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 400) {
        ret = 8;
    }
    return ret;
}
