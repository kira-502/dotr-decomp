#include "common.h"

/* shape b471:01E00080 (b471), 1886 insns, 1 copy */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b471_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b471_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b471_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b471_01E00080 c;
    Uv_b471_01E00080 uv0;
    Xyz_b471_01E00080 p0;
    Uv_b471_01E00080 uv1;
    Xyz_b471_01E00080 p1;
    u8 tail[0x20];
} Spr_b471_01E00080;

typedef struct {
    Rgbaq_b471_01E00080 c;
    Uv_b471_01E00080 uv;
    Xyz_b471_01E00080 p;
} Tv_b471_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b471_01E00080;

typedef struct {
    Reg_b471_01E00080 a;
    Reg_b471_01E00080 b;
} Tx_b471_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b471_01E00080 v[3];
    u64 pad58;
    Tx_b471_01E00080 tx;
    u64 pad70;
} Tri_b471_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b471_01E00080 c;
    struct {
        Uv_b471_01E00080 uv;
        Xyz_b471_01E00080 p;
    } v[4];
    u64 pad58;
    Tx_b471_01E00080 tx;
    u64 pad70;
} Warp_b471_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b471_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[8];
    u8 pad18[8];
    Vec4f v[8];
} Burst_b471_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[6];
} Ring_b471_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v[4];
} Spark_b471_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 obj;
    s32 tex[2];
    s32 bone[6];
    u8 pad2C[4];
    Vec4f bp[6];
    Vec4f mid;
    u8 on;
    u8 padA1[3];
    s32 t1;
    s32 cnt;
    u8 padAC[4];
    Burst_b471_01E00080 burst[32];
    Vec4f hex[7];
    Ring_b471_01E00080 ring[32];
    Spark_b471_01E00080 spark[16];
    u8 on2;
    u8 pad2821[3];
    s32 t2;
    s32 grid[21][15][2];
    s32 off[21][15][2];
} Scene_b471_01E00080;

static s32 func_01E00080_b471(s32 arg0, s32 code) {
    Scene_b471_01E00080 *g = (Scene_b471_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00100C60(void *, void *, s32, s32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
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
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    extern f32 D_0028BC10[4][32][3];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 done;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 q;
    s32 x;
    s32 y;
    s32 ang;
    s32 drawn;
    u8 alpha;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Mtx_b471_01E00080 m4;
    Vec4f w;
    Vec4f sc;
    Spr_b471_01E00080 spr __attribute__((aligned(8)));
    Tri_b471_01E00080 tri __attribute__((aligned(8)));
    Warp_b471_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3BE0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->bone[0] = func_001F5560(g->unitA, 0xD, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x30, 0);
        g->bone[2] = func_001F5560(g->unitA, 0x29, 0);
        g->bone[3] = func_001F5560(g->unitA, 0x1B, 0);
        g->bone[4] = func_001F5560(g->unitA, 0x22, 0);
        g->bone[5] = func_001F5560(g->unitA, 0x14, 0);
        g->on = 0;
        g->cnt = 0;
        for (i = 0; i < 32; i++) {
            g->burst[i].on = 0;
            for (n = 0; n < 8; n++) {
                g->burst[i].c[n] = (func_0019A5C8() >> 23) % 4;
            }
        }
        for (i = 0; i < 7; i++) {
            ang = (i << 16) / 6;
            g->hex[i].x = 10.0f * func_0020B550(ang);
            g->hex[i].y = 10.0f * func_0020B480(ang);
            g->hex[i].z = 0.0f;
            g->hex[i].w = 1.0f;
        }
        for (i = 0; i < 32; i++) {
            g->ring[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->spark[i].on = 0;
        }
        g->on2 = 0;
        for (i = 0; i < 21; i++) {
            for (n = 0; n < 15; n++) {
                g->grid[i][n][0] = i * 0x200 / 20 + 0x40;
                g->grid[i][n][1] = n * 0x168 / 14 + 0x2C;
            }
        }
        return 0;
    }
    func_00205CA0(m3);
    for (n = 0; n < 6; n++) {
        func_001F5620(g->unitA, g->bone[n], &g->bp[n]);
    }
    func_00187B00(&g->mid, &g->bp[0], &g->bp[3]);
    { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }
    if (g->t == 0) {
        g->on = 1;
        g->t1 = 0;
    }

    ((Spr_b471_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b471_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b471_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b471_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b471_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    if (g->on == 1) {
        k = 0xE4 - g->t1;
        if (k > 32) {
            k = 32;
        }
        k = k * 255 >> 5;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0xC4;
        spr.c.a = k;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b471_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b471_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b471_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b471_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        n = g->t1;
        if (n > 32) {
            n = 32;
        }
        for (i = 0; i < 6; i++) {
            r = n * (10.0f * (1.0f - 0.3f * ((g->t1 + i) % 2))) / 32.0f;
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
            func_00187B00(&out[0], &cn[0], &g->bp[i]);
            func_00187B00(&out[1], &cn[1], &g->bp[i]);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t1++;
        if (g->t1 > 0xE4) {
            g->on = 0;
        }
    }

    if (g->t > 0x2D && g->t < 0xC4) {
        n = g->t % 32;
        (void)n;
        g->burst[n].on = 1;
        g->burst[n].t = 0;
        for (k = 0; k < 8; k++) {
            q = (g->t + k + (func_0019A5C8() >> 23) % 256) % 32;
            g->burst[n].v[k].x = D_0028BC10[(func_0019A5C8() >> 23) % 4][q][0];
            g->burst[n].v[k].y = D_0028BC10[(func_0019A5C8() >> 23) % 4][q][1];
            g->burst[n].v[k].z = D_0028BC10[(func_0019A5C8() >> 23) % 4][q][2];
            g->burst[n].v[k].w = 1.0f;
            func_00187B00(&g->burst[n].v[k], &g->burst[n].v[k], &g->mid);
        }
        g->cnt++;
        if (g->cnt > 32) {
            g->cnt = 32;
        }
    }

    ((Spr_b471_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b471_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b471_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b471_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b471_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (x = 0; x < 32; x++) {
        if (g->burst[x].on == 0) {
            continue;
        }
        r = 5.0f + 5.0f * (32 - g->burst[x].t) / 32.0f;
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
        n = g->cnt * (g->burst[x].t * 96 / 32) >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x40;
        spr.c.b = 0x60;
        spr.c.a = n;
        spr.c.q = 1.0f;
        r = (32 - g->burst[x].t) / 32.0f;
        func_0020BBB0(&m4);
        func_00100E00(&m4, g->burst[x].t * 999, 2);
        for (k = 0; k < 8; k++) {
            ang = (k << 16) >> 3;
            w.x = 30.0f * func_0020B550(ang);
            w.y = 30.0f * func_0020B480(ang);
            w.z = -150.0f * g->obj;
            w.w = 1.0f;
            func_001878E0(&w, &m4, &w);
            func_00187B00(&w, &w, &g->burst[x].v[k]);
            func_00187B18(&w, &w, &g->mid);
            func_00187B48(&w, &w, r);
            func_00187B00(&w, &w, &g->mid);
            func_00187B00(&out[0], &cn[0], &w);
            func_00187B00(&out[1], &cn[1], (void *)&w);
            ((Uv_b471_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->burst[x].c[k]][0];
            ((Uv_b471_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->burst[x].c[k]][2];
            ((Uv_b471_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->burst[x].c[k]][1];
            ((Uv_b471_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->burst[x].c[k]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->burst[x].t++;
        if (g->burst[x].t > 32) {
            g->burst[x].on = 0;
        }
    }

    if (g->t > 0x4B && g->t < 0xC4) {
        n = g->t % 32;
        (void)n;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (q = 0; q < 6; q++) {
            k = (g->t + q + (func_0019A5C8() >> 23) % 256) % 32;
            g->ring[n].v[q].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][0];
            g->ring[n].v[q].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][1];
            g->ring[n].v[q].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][2];
            g->ring[n].v[q].w = 1.0f;
            func_00187B00(&g->ring[n].v[q], &g->ring[n].v[q], &g->mid);
        }
    }

    ((Tri_b471_01E00080 *)(s32)&tri)->flags = 0x33;
    ((Tri_b471_01E00080 *)(s32)&tri)->size = 9;
    ((Tri_b471_01E00080 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
    ((Tri_b471_01E00080 *)(s32)&tri)->pad4 = 0;
    func_002086D0(&tri, func_00208D00(0));
    func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
    ((Tri_b471_01E00080 *)(s32)&tri)->flags |= 0x800;
    tri.v[0].c.r = 0x80;
    tri.v[0].c.g = 0x80;
    tri.v[0].c.b = 0xFF;
    tri.v[0].c.a = 0x80;
    tri.v[0].c.q = 1.0f;
    tri.v[1].c.r = 0x80;
    tri.v[1].c.g = 0x80;
    tri.v[1].c.b = 0xFF;
    tri.v[1].c.a = 0;
    tri.v[1].c.q = 1.0f;
    tri.v[2].c = tri.v[1].c;
    done = 0;
    for (i = 0; i < 32; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        if (done == 0) {
            done = 1;
            buf = func_00207F60();
            func_00208460();
            func_00208800(func_00209E50(), 1, &tri.tx.a, &tri.tx.b);
            func_00208460();
        }
        func_0020BBB0(&m4);
        func_00100E00(&m4, g->ring[i].t * 999, 2);
        s = func_00100D50(g->ring[i].t, 32, 2);
        sc.x = s;
        sc.y = s;
        sc.z = s;
        sc.w = 1.0f;
        h = (32 - g->ring[i].t) / 32.0f;
        for (n = 0; n < 6; n++) {
            ang = (n << 16) / 6;
            w.x = 80.0f * func_0020B550(ang);
            w.y = 80.0f * func_0020B480(ang);
            w.z = -250.0f * g->obj;
            w.w = 1.0f;
            func_001878E0(&w, &m4, &w);
            func_00187B00(&w, &w, &g->ring[i].v[n]);
            func_00187B18(&w, &w, &g->mid);
            func_00187B48(&w, &w, h);
            func_00187B00(&w, &w, &g->mid);
            func_0020EB40(m);
            func_00187B60(m2, m3, &w);
            func_0020CB20(m2, &sc);
            func_0020BC00(m, m2);
            w.x = 0.0f;
            w.y = 0.0f;
            w.z = 0.0f;
            w.w = 1.0f;
            ang &= 0xFFFF;
            drawn = 0;
            for (j = 0; j < 6; j++) {
                if (func_00100B00(&w, &g->hex[j], &g->hex[j + 1], m, &tri, &depth) == 1) {
                    if (drawn == 0) {
                        r = func_001A6C60(func_001A6C48((f32)((tri.v[0].p.x >> 4) - (tri.v[1].p.x >> 4)), 2.0f) +
                                          func_001A6C48((f32)((tri.v[0].p.y >> 4) - (tri.v[1].p.y >> 4)), 2.0f)) /
                            2.0f;
                        drawn = 1;
                    }
                    x = (s32)(r * func_0020B550(ang));
                    y = (s32)(r * func_0020B480(ang));
                    func_00100C60(&tri.v[0].uv, &tri.v[0].p, x, y);
                    func_00100C60(&tri.v[1].uv, &tri.v[1].p, 0, 0);
                    func_00100C60(&tri.v[2].uv, &tri.v[2].p, 0, 0);
                    func_002075F0(&tri, 0, 0);
                }
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 32) {
            g->ring[i].on = 0;
        }
    }
    if (done == 1) {
        func_00207FD0(buf, ot, 0);
    }

    if (g->t > 0x4B && g->t < 0xD4) {
        n = g->t % 16;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        for (j = 0; j < 4; j++) {
            k = (g->t + j + (func_0019A5C8() >> 23) % 256) % 32;
            g->spark[n].v[j].x = 4.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][0];
            g->spark[n].v[j].y = 4.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][1];
            g->spark[n].v[j].z = 4.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][2];
            g->spark[n].v[j].w = 1.0f;
            func_00187B00(&g->spark[n].v[j], &g->spark[n].v[j], &g->mid);
        }
    }

    ((Spr_b471_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b471_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b471_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b471_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b471_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b471_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b471_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b471_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b471_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    cn[0].x = -6.0f;
    cn[0].y = -6.0f;
    cn[0].z = 0.0f;
    cn[0].w = 1.0f;
    cn[1].x = 6.0f;
    cn[1].y = 6.0f;
    cn[1].z = 0.0f;
    cn[1].w = 1.0f;
    func_001878E0(&cn[0], m3, &cn[0]);
    func_001878E0(&cn[1], m3, &cn[1]);
    for (x = 0; x < 16; x++) {
        if (g->spark[x].on == 0) {
            continue;
        }
        for (q = 0; q < 16; q++) {
            alpha = (u32)(g->spark[x].t * (128.0f * func_0020B550(((q + 1) << 15) / 17)) / 16.0f);
            spr.c.r = 0xFF;
            spr.c.g = 0x80;
            spr.c.b = 0x80;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            f = g->spark[x].t + 0.2f * q;
            if (f > 16.0f) {
                f = 16.0f;
            }
            h = (16.0f - f) / 16.0f;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (s32)(999.0f * f), 2);
            for (k = 0; k < 4; k++) {
                ang = (k << 16) >> 2;
                w.x = 80.0f * func_0020B550(ang);
                w.y = 80.0f * func_0020B480(ang);
                w.z = -250.0f * g->obj;
                w.w = 1.0f;
                func_001878E0(&w, &m4, &w);
                func_00187B00(&w, &w, &g->spark[x].v[k]);
                func_00187B18(&w, &w, &g->mid);
                func_00187B48(&w, &w, h);
                func_00187B00(&w, &w, &g->mid);
                func_00187B00(&out[0], &cn[0], &w);
                func_00187B00(&out[1], &cn[1], (void *)&w);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[x].t++;
        if (g->spark[x].t > 16) {
            g->spark[x].on = 0;
        }
    }

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
    }
    if (g->on2 == 1) {
        ((Warp_b471_01E00080 *)(s32)&pk)->flags = 0x24;
        ((Warp_b471_01E00080 *)(s32)&pk)->size = 9;
        ((Warp_b471_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Warp_b471_01E00080 *)(s32)&pk)->pad4 = 0;
        ((Warp_b471_01E00080 *)(s32)&pk)->flags |= 0x800;
        func_002086D0(&pk, func_00208D00(0));
        buf = func_00207F60();
        func_00208460();
        func_001F7060(g->unitA, 1, &pk.tx.a, &pk.tx.b);
        func_00208460();
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        alpha = (u32)(96.0f * func_0020B550((g->t2 << 15) / 80));
        pk.c.r = 0x80;
        pk.c.g = 0x80;
        pk.c.b = 0xFF;
        pk.c.a = alpha;
        pk.c.q = 1.0f;
        for (k = 0; k < 21; k++) {
            x = (s32)((f32)(k * 0x280 / 20) + 10.0f * func_0020B550((g->t2 * 0x15B3 + k * 0x2B67) & 0xFFFF));
            for (n = 0; n < 15; n++) {
                y = (s32)((f32)(n * 0x1C0 / 14) + 10.0f * func_0020B480((g->t2 * 0x15B3 + n * 0x2B67) & 0xFFFF));
                g->off[k][n][0] = x;
                g->off[k][n][1] = y;
            }
        }
        for (i = 0; i < 20; i++) {
            for (y = 0; y < 14; y++) {
                ((Uv_b471_01E00080 *)(s32)&pk.v[0].uv)->u = g->grid[i][y][0] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[0].uv)->v = g->grid[i][y][1] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[1].uv)->u = g->grid[i + 1][y][0] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[1].uv)->v = g->grid[i + 1][y][1] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[2].uv)->u = g->grid[i][y + 1][0] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[2].uv)->v = g->grid[i][y + 1][1] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[3].uv)->u = g->grid[i + 1][y + 1][0] << 4;
                ((Uv_b471_01E00080 *)(s32)&pk.v[3].uv)->v = g->grid[i + 1][y + 1][1] << 4;
                pk.v[0].p.x = (g->off[i][y][0] + 0x6C0) << 4;
                pk.v[0].p.y = (g->off[i][y][1] + 0x720) << 4;
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[0].p.f = 0;
                pk.v[1].p.x = (g->off[i + 1][y][0] + 0x6C0) << 4;
                pk.v[1].p.y = (g->off[i + 1][y][1] + 0x720) << 4;
                pk.v[1].p.z = 0xFFFFF8;
                pk.v[1].p.f = 0;
                pk.v[2].p.x = (g->off[i][y + 1][0] + 0x6C0) << 4;
                pk.v[2].p.y = (g->off[i][y + 1][1] + 0x720) << 4;
                pk.v[2].p.z = 0xFFFFF8;
                pk.v[2].p.f = 0;
                pk.v[3].p.x = (g->off[i + 1][y + 1][0] + 0x6C0) << 4;
                pk.v[3].p.y = (g->off[i + 1][y + 1][1] + 0x720) << 4;
                pk.v[3].p.z = 0xFFFFF8;
                pk.v[3].p.f = 0;
                func_002075F0(&pk, 0, 0);
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t2++;
        if (g->t2 > 0x50) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x41) {
        ret = 1;
    } else {
        if (g->t > 0x4B && g->t < 0xE4) {
            ret = 6;
        }
        if (g->t == 0xE4) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xEE) {
        ret = 8;
    }
    return ret;
}
