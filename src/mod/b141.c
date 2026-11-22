#include "common.h"

/* shape b141:01E00080 (b141), 1923 insns, 1 copy: GS packet scene effect: twin, pair, rush, cloud, mote and smoke
   sprite bursts */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b141_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b141_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b141_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b141_01E00080 c;
    Uv_b141_01E00080 uv0;
    Xyz_b141_01E00080 p0;
    Uv_b141_01E00080 uv1;
    Xyz_b141_01E00080 p1;
    u8 tail[0x20];
} Spr_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f pos[2];
    Vec4f v[2][8];
} Twin_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos[2];
    Vec4f v[2];
} Pair_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos[8];
    Vec4f v[8];
} Rush_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Cloud_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f v;
} Mote_b141_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f v[16];
} Smoke_b141_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[2];
    u8 pad18[8];
    Vec4f tgt;
    s32 bone[2];
    u8 pad38[8];
    Vec4f bp[2];
    Vec4f mid;
    Twin_b141_01E00080 twin[16];
    Pair_b141_01E00080 pair[32];
    Rush_b141_01E00080 rush[48];
    Cloud_b141_01E00080 cloud[16];
    Mote_b141_01E00080 mote[64];
    Smoke_b141_01E00080 smoke[32];
} Scene_b141_01E00080;

static s32 func_01E00080_b141(s32 arg0, s32 code) {
    Scene_b141_01E00080 *g = (Scene_b141_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6590(s32, s32, void *);
    extern s32 func_001F6EF0(void);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 q;
    s32 x;
    u8 alpha;
    f32 f;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b141_01E00080 spr __attribute__((aligned(8)));
    f32 depth;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xA070);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F53C0(1, g->unitB, &g->tgt);
        g->bone[0] = func_001F5560(g->unitA, 0x2D, 1);
        g->bone[1] = func_001F5560(g->unitA, 0x40, 0);
        for (i = 0; i < 16; i++) {
            g->twin[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->pair[i].on = 0;
        }
        for (i = 0; i < 48; i++) {
            g->rush[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->cloud[i].on = 0;
        }
        for (i = 0; i < 64; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->smoke[i].on = 0;
        }
        func_001F6590(g->unitB, 2, 0);
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->bone[i], &g->bp[i]);
    }
    func_00187B00(&g->mid, &g->bp[0], &g->bp[1]);
    { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }

    if (g->t > 0 && g->t < 0x104) {
        n = g->t % 16;
        (void)n;
        g->twin[n].on = 1;
        g->twin[n].t = 0;
        for (i = 0; i < 2; i++) {
            g->twin[n].pos[i] = g->bp[i];
            for (j = 0; j < 8; j++) {
                g->twin[n].c[i][j] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->twin[n].v[i][j], 0.2f);
            }
        }
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x104 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->twin[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->twin[i].t << 15) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x20;
        spr.c.b = 0x10;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 3.0f * (0.2f + 0.8f * g->twin[i].t / 16.0f);
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
        w = g->twin[i].t / 16.0f;
        s = 0.9f + 0.1f * g->twin[i].t / 16.0f;
        for (n = 0; n < 2; n++) {
            for (k = 0; k < 8; k++) {
                ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->twin[i].c[n][k]][0];
                ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->twin[i].c[n][k]][2];
                ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->twin[i].c[n][k]][1];
                ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->twin[i].c[n][k]][3];
                v.x = g->twin[i].v[n][k].x * s;
                v.y = -4.0f + 10.0f * w + g->twin[i].v[n][k].y;
                v.z = g->twin[i].v[n][k].z * s;
                func_00187B00(&v, &v, &g->twin[i].pos[n]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    if (g->t < 0x78) {
                        spr.p0.z = 0xFFFFF8;
                        spr.p1.z = spr.p0.z;
                        func_002075F0(&spr, ot, 0);
                    } else {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
            }
        }
        g->twin[i].t++;
        if (g->twin[i].t > 16) {
            g->twin[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x104) {
        n = g->t % 32;
        (void)n;
        g->pair[n].on = 1;
        g->pair[n].t = 0;
        for (q = 0; q < 2; q++) {
            g->pair[n].pos[q] = g->bp[q];
            func_00101080(&g->pair[n].v[q], 0.3f);
        }
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 32) * (f32)func_00101050(0x104 - g->t, 0, 32) / 1024.0f;
    for (x = 0; x < 32; x++) {
        if (g->pair[x].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->pair[x].t << 15) >> 5)));
        spr.c.r = 0xFF;
        spr.c.g = 0x1C;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 6.0f * (0.5f + 0.5f * g->pair[x].t / 32.0f);
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
        w = g->pair[x].t / 32.0f;
        s = 0.7f + 0.3f * g->pair[x].t / 32.0f;
        h = -2.0f + 8.0f * w;
        for (q = 0; q < 2; q++) {
            v.x = g->pair[x].v[q].x * s;
            v.y = h + g->pair[x].v[q].y;
            v.z = g->pair[x].v[q].z * s;
            func_00187B00(&v, &v, &g->pair[x].pos[q]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->pair[x].t++;
        if (g->pair[x].t > 32) {
            g->pair[x].on = 0;
        }
    }

    if (g->t > 0x6E && g->t < 0x104) {
        n = g->t % 48;
        (void)n;
        g->rush[n].on = 1;
        g->rush[n].t = 0;
        for (k = 0; k < 8; k++) {
            g->rush[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->rush[n].pos[k], 0.2f);
            func_00187B00(&g->rush[n].pos[k], &g->rush[n].pos[k], &g->mid);
            func_00101080(&g->rush[n].v[k], 1.0f);
            func_00187B00(&g->rush[n].v[k], &g->rush[n].v[k], &g->tgt);
            func_00187B18(&g->rush[n].v[k], &g->rush[n].v[k], &g->rush[n].pos[k]);
        }
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x6E, 0, 32) * (f32)func_00101050(0x104 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 48; i++) {
        if (g->rush[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (100.0f * func_00100FF0((f32)g->rush[i].t, 48.0f, 24.0f)));
        spr.c.r = 0x80;
        spr.c.g = 0x26;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * g->rush[i].t / 48.0f);
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
        s = 1.5f * g->rush[i].t / 48.0f;
        for (q = 0; q < 8; q++) {
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->rush[i].c[q]][0];
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->rush[i].c[q]][2];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->rush[i].c[q]][1];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->rush[i].c[q]][3];
            func_00187B48(&v, &g->rush[i].v[q], s);
            func_00187B00(&v, &v, &g->rush[i].pos[q]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->rush[i].t++;
        if (g->rush[i].t > 48) {
            g->rush[i].on = 0;
        }
    }

    if (g->t > 0x8C && g->t < 0x154) {
        n = g->t % 16;
        (void)n;
        g->cloud[n].on = 1;
        g->cloud[n].t = 0;
        for (j = 0; j < 32; j++) {
            g->cloud[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->cloud[n].v[j], 1.3f);
        }
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x8C, 0, 32) * (f32)func_00101050(0x154 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->cloud[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->cloud[i].t << 15) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x26;
        spr.c.b = 0x16;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.2f + 0.8f * g->cloud[i].t / 16.0f);
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
        w = g->cloud[i].t / 16.0f;
        s = 0.9f + 0.1f * g->cloud[i].t / 16.0f;
        h = -25.0f + 50.0f * w;
        for (x = 0; x < 32; x++) {
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->cloud[i].c[x]][0];
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->cloud[i].c[x]][2];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->cloud[i].c[x]][1];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->cloud[i].c[x]][3];
            v.x = g->cloud[i].v[x].x * s;
            v.y = h + g->cloud[i].v[x].y;
            v.z = g->cloud[i].v[x].z * s;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->cloud[i].t++;
        if (g->cloud[i].t > 16) {
            g->cloud[i].on = 0;
        }
    }

    if (g->t > 0x8C && g->t < 0x154) {
        n = g->t % 64;
        (void)n;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        func_00101080(&g->mote[n].v, 2.0f);
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x8C, 0, 32) * (f32)func_00101050(0x154 - g->t, 0, 32) / 1024.0f;
    for (k = 0; k < 64; k++) {
        if (g->mote[k].on == 0) {
            continue;
        }
        alpha = (u32)(f * (128.0f * func_0020B550((g->mote[k].t << 15) >> 6)));
        spr.c.r = 0xFF;
        spr.c.g = 0x1C;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 20.0f * (0.5f + 0.5f * g->mote[k].t / 64.0f);
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
        w = g->mote[k].t / 64.0f;
        s = 0.5f + 0.5f * g->mote[k].t / 64.0f;
        h = -25.0f + 50.0f * w;
        v.x = g->mote[k].v.x * s;
        v.y = h + g->mote[k].v.y;
        v.z = g->mote[k].v.z * s;
        func_00187B00(&v, &v, &g->tgt);
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        g->mote[k].t++;
        if (g->mote[k].t > 64) {
            g->mote[k].on = 0;
        }
    }

    if (g->t > 0x12C && g->t < 0x172) {
        n = g->t % 32;
        (void)n;
        g->smoke[n].on = 1;
        g->smoke[n].t = 0;
        for (j = 0; j < 16; j++) {
            g->smoke[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->smoke[n].v[j], 1.3f);
        }
    }

    ((Spr_b141_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b141_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b141_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b141_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b141_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(0));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0x12C, 0, 32) * (f32)func_00101050(0x172 - g->t, 0, 32) / 1024.0f;
    for (i = 0; i < 32; i++) {
        if (g->smoke[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (200.0f * func_0020B550((g->smoke[i].t << 15) >> 5)));
        spr.c.r = 0xA;
        spr.c.g = 0xA;
        spr.c.b = 0xA;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 10.0f * (0.2f + 0.8f * g->smoke[i].t / 32.0f);
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
        w = g->smoke[i].t / 32.0f;
        s = 0.9f + 0.1f * g->smoke[i].t / 32.0f;
        h = -25.0f + 50.0f * w;
        for (x = 0; x < 16; x++) {
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->smoke[i].c[x]][0];
            ((Uv_b141_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->smoke[i].c[x]][2];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->smoke[i].c[x]][1];
            ((Uv_b141_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->smoke[i].c[x]][3];
            v.x = g->smoke[i].v[x].x * s;
            v.y = h + g->smoke[i].v[x].y;
            v.z = g->smoke[i].v[x].z * s;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->smoke[i].t++;
        if (g->smoke[i].t > 32) {
            g->smoke[i].on = 0;
        }
    }

    if (func_001F6EF0() == 1 && g->t > 0x9C) {
        x = func_00101050(g->t - 0x9C, 0, 32) << 7 >> 5;
        col[0] = col[1] = col[2] = 0x80;
        col[3] = x;
        func_001F6590(g->unitB, 2, col);
    }

    if (g->t == 0x82) {
        ret = 1;
    } else {
        if (g->t > 0x8C && g->t < 0x168) {
            ret = 6;
        }
        if (g->t == 0x168) {
            ret = 3;
        }
    }
    g->t++;
    if (g->t > 0x172) {
        ret = 8;
    }
    return ret;
}
