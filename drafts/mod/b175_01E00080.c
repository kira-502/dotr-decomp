#include "common.h"

/* HARD, 8 words: the spark k-loop and j-loop counters take each other's spill slots (0x250 / 0x280); loop names, declaration order, pointer locals and if/continue forms leave it */
/* shape b175:01E00080 (b175), 1538 insns, 1 copy: b175 scene manager (draft): setup clears the 0x4D90 scene, takes
   both units, three textures, the target and joints 0x10 / 0x17, builds a 33-point ring of radius 42; else follows
   both joints, spawns a two-point particle per frame in 32 slots (faded in/out over 0x1F400 frames), fires a bolt at
   frames 33 + 34n (n < 8) in 2 slots whose bouncing sprites leave 12-slot spark trails and at bolt frame 24 a
   2x128-sprite burst with a ring of triangles; returns 1 / 6 / 2 / 8 at 0x2F / 0x3A..0x14D / 0x14E / >0x14F */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b175_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b175_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b175_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b175_01E00080 c;
    Uv_b175_01E00080 uv0;
    Xyz_b175_01E00080 p0;
    Uv_b175_01E00080 uv1;
    Xyz_b175_01E00080 p1;
    u8 tail[0x20];
} Spr_b175_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b175_01E00080 c0;
    Xyz_b175_01E00080 p0;
    Rgbaq_b175_01E00080 c1;
    Xyz_b175_01E00080 p1;
    Rgbaq_b175_01E00080 c2;
    Xyz_b175_01E00080 p2;
    u8 tail[8];
} Ln_b175_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f p[2];
    Vec4f v[2];
} Part_b175_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2];
    s8 dc[2];
    u8 nspark;
    u8 padD[3];
    Vec4f p[2];
    Vec4f v[2];
} Bolt_b175_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][8];
    u8 pad18[8];
    Vec4f p[2];
    Vec4f v[2][8];
} Spark_b175_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[2][128];
    u8 pad108[8];
    Vec4f p[2];
    Vec4f v[2][128];
} Burst_b175_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    s32 m[2];
    u8 pad38[8];
    Vec4f pos[2];
    Part_b175_01E00080 part[32];
    s32 nbolt;
    s32 ibolt;
    u8 padA68[8];
    Bolt_b175_01E00080 bolt[2];
    Spark_b175_01E00080 spark[2][12];
    s32 nburst;
    u8 pad2914[0xC];
    Burst_b175_01E00080 burst[2];
    Vec4f ring[33];
} Scene_b175_01E00080;

static s32 func_01E00080_b175(s32 arg0, s32 code) {
    Scene_b175_01E00080 *g = (Scene_b175_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
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
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    s32 ot;
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 u;
    s32 c;
    s32 q;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 a;
    f32 depth;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f save[2];
    Spr_b175_01E00080 spr __attribute__((aligned(8)));
    Ln_b175_01E00080 ln __attribute__((aligned(8)));
    Bolt_b175_01E00080 *bb;
    Bolt_b175_01E00080 *bp;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4D90);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->m[0] = func_001F5560(g->unitA, 0x10, 1);
        g->m[1] = func_001F5560(g->unitA, 0x17, 0);
        for (i = 0; i < 32; i++) {
            g->part[i].on = 0;
        }
        g->nbolt = 0;
        g->ibolt = 0;
        for (i = 0; i < 2; i++) {
            g->bolt[i].on = 0;
            g->bolt[i].nspark = 0;
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 12; j++) {
                g->spark[i][j].on = 0;
            }
        }
        g->nburst = 0;
        for (i = 0; i < 2; i++) {
            g->burst[i].on = 0;
        }
        for (i = 0; i < 33; i++) {
            g->ring[i].x = 42.0f * func_0020B550(i * 0x10000 >> 5);
            g->ring[i].y = 42.0f * func_0020B480(i * 0x10000 >> 5);
            g->ring[i].z = 0.0f;
            g->ring[i].w = 1.0f;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (j = 0; j < 2; j++) {
        func_001F5620(g->unitA, g->m[j], &g->pos[j]);
    }
    if (g->t > 0 && g->t < 0x1F400) {
        n = g->t;
        n %= 32;
        g->part[n].on = 1;
        g->part[n].t = 0;
        for (j = 0; j < 2; j++) {
            g->part[n].p[j] = g->pos[j];
            func_00101080(&g->part[n].v[j], 0.5f);
        }
    }

    ((Spr_b175_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b175_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b175_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b175_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b175_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    x = 0;
    ((Uv_b175_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b175_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b175_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b175_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t, 0, 0x20) * (f32)func_00101050(0x1F400 - g->t, 0, 0x20) / 1024.0f;
    for (i = 0; i < 32; i++) {
        if (g->part[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (255.0f * func_0020B480((g->part[i].t << 14) >> 5)));
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x18;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 8.0f * (0.2f + 0.8f * g->part[i].t / 32.0f);
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
        s = 0.1f + 0.9f * g->part[i].t / 32.0f;
        for (j = 0; j < 2; j++) {
            v.x = g->part[i].v[j].x * s;
            v.y = g->part[i].v[j].y * s;
            v.z = g->part[i].v[j].z * s;
            func_00187B00(&v, &v, &g->part[i].p[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->part[i].t++;
        if (g->part[i].t > 32) {
            g->part[i].on = 0;
        }
    }

    if (g->t == g->nbolt * 34 + 33 && g->nbolt < 8) {
        n = g->ibolt;
        bb = g->bolt;
        bp = &bb[n];
        bp->on = 1;
        bp->t = 0;
        for (j = 0; j < 2; j++) {
            g->bolt[n].c[j] = (func_0019A5C8() >> 23) % 4;
            g->bolt[n].dc[j] = 1;
            g->bolt[n].p[j] = g->pos[j];
            func_00101080(&g->bolt[n].v[j], 1.0f);
            func_00187B00(&g->bolt[n].v[j], &g->bolt[n].v[j], &g->tgt);
            func_00187B18(&g->bolt[n].v[j], &g->bolt[n].v[j], &g->bolt[n].p[j]);
        }
        g->nbolt++;
        g->ibolt++;
        if (g->ibolt >= 2) {
            g->ibolt = 0;
        }
    }

    ((Spr_b175_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b175_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b175_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b175_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b175_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 2; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x1C;
        spr.c.a = 0xFF;
        spr.c.q = 1.0f;
        r = 6.0f;
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
        for (j = 0; j < 2; j++) {
            x = g->bolt[i].c[j] % 4 * 32;
            y = (g->bolt[i].c[j] >> 2) * 32;
            g->bolt[i].c[j] += g->bolt[i].dc[j];
            if (g->bolt[i].c[j] == 0 || g->bolt[i].c[j] == 4) {
                g->bolt[i].dc[j] = -g->bolt[i].dc[j];
            }
            ((Uv_b175_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b175_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b175_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b175_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->bolt[i].v[j], (f32)g->bolt[i].t / 24.0f);
            func_00187B00(&v, &v, &g->bolt[i].p[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            save[j] = v;
        }
        n = g->bolt[i].nspark;
        g->spark[i][n].on = 1;
        g->spark[i][n].t = 0;
        for (j = 0; j < 2; j++) {
            g->spark[i][n].p[j] = save[j];
            for (q = 0; q < 8; q++) {
                g->spark[i][n].c[j][q] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->spark[i][n].v[j][q], 0.5f);
            }
        }
        g->bolt[i].nspark++;
        if (g->bolt[i].nspark >= 12) {
            g->bolt[i].nspark = 0;
        }
        if (g->bolt[i].t == 24) {
            n = g->nburst;
            g->burst[n].on = 1;
            g->burst[n].t = 0;
            for (j = 0; j < 2; j++) {
                g->burst[n].p[j] = save[j];
                for (q = 0; q < 128; q++) {
                    g->burst[n].c[j][q] = (func_0019A5C8() >> 23) % 4;
                    func_00101080(&g->burst[n].v[j][q], 1.2f);
                }
            }
            g->nburst++;
            if (g->nburst >= 2) {
                g->nburst = 0;
            }
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 24) {
            g->bolt[i].on = 0;
        }
    }

    ((Spr_b175_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b175_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b175_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b175_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b175_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 2; i++) {
        for (q = 0; q < 12; q++) {
            if (g->spark[i][q].on == 0) {
                continue;
            }
            alpha = (12 - g->spark[i][q].t) * 128 / 12;
            spr.c.r = 0x80;
            spr.c.g = 0x28;
            spr.c.b = 0x12;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 6.0f * (0.8f + 0.2f * g->spark[i][q].t / 12.0f);
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
            s = 0.3f + 0.7f * func_00100D50(g->spark[i][q].t, 12, 1);
            for (j = 0; j < 2; j++) {
                for (c = 0; c < 8; c++) {
                    ((Uv_b175_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->spark[i][q].c[j][c]][0];
                    ((Uv_b175_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->spark[i][q].c[j][c]][2];
                    ((Uv_b175_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->spark[i][q].c[j][c]][1];
                    ((Uv_b175_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->spark[i][q].c[j][c]][3];
                    func_00187B48(&v, &g->spark[i][q].v[j][c], s);
                    func_00187B00(&v, &v, &g->spark[i][q].p[j]);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
            }
            g->spark[i][q].t++;
            if (g->spark[i][q].t > 12) {
                g->spark[i][q].on = 0;
            }
        }
    }

    ((Spr_b175_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b175_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b175_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b175_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b175_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    ((Ln_b175_01E00080 *)(s32)&ln)->flags = 0x13;
    ((Ln_b175_01E00080 *)(s32)&ln)->size = 6;
    ((Ln_b175_01E00080 *)(s32)&ln)->regs = 0x414141;
    ((Ln_b175_01E00080 *)(s32)&ln)->pad4 = 0;
    func_002086D0(&ln, func_00208D00(1));
    for (i = 0; i < 2; i++) {
        if (g->burst[i].on == 0) {
            continue;
        }
        r = 6.0f * (0.8f + 0.2f * g->burst[i].t / 40.0f);
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
        r = 0.3f + 0.7f * func_00100D50(g->burst[i].t, 0x28, 1);
        a = func_00100FF0((f32)g->burst[i].t, 40.0f, 20.0f);
        for (j = 0; j < 2; j++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_0020BC00(m, m2);
            for (q = 0; q < 128; q++) {
                if (q % 3 == 0) {
                    s = 0.8f * r;
                    func_002086D0(&spr, func_00208D00(2));
                    alpha = (u32)(128.0f * a);
                    (void)alpha;
                    spr.c.r = 0x80;
                    spr.c.g = 0x80;
                    spr.c.b = 0x80;
                    spr.c.a = alpha;
                    spr.c.q = 1.0f;
                } else {
                    s = r;
                    func_002086D0(&spr, func_00208D00(1));
                    alpha = (u32)(128.0f * a);
                    (void)alpha;
                    spr.c.r = 0x80;
                    spr.c.g = 0x22;
                    spr.c.b = 0x08;
                    spr.c.a = alpha;
                    spr.c.q = 1.0f;
                }
                ((Uv_b175_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->burst[i].c[j][q]][0];
                ((Uv_b175_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->burst[i].c[j][q]][2];
                ((Uv_b175_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->burst[i].c[j][q]][1];
                ((Uv_b175_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->burst[i].c[j][q]][3];
                func_00187B48(&v, &g->burst[i].v[j][q], s);
                func_00187B00(&v, &v, &g->burst[i].p[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            func_0020EB40(m);
            func_00187B60(m2, m3, &g->burst[i].p[j]);
            v.x = r;
            v.y = r;
            v.z = r;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            alpha = (u32)(128.0f * a);
            (void)alpha;
            ln.c0.r = 0xFF;
            ln.c0.g = 0xA4;
            ln.c0.b = 0x38;
            ln.c0.a = alpha;
            ln.c0.q = 1.0f;
            ln.c1.r = 0xFF;
            ln.c1.g = 0x26;
            ln.c1.b = 0x06;
            ln.c1.a = 0;
            ln.c1.q = 1.0f;
            ln.c2 = ln.c1;
            v.x = 0.0f;
            v.y = 0.0f;
            v.z = 0.0f;
            v.w = 1.0f;
            for (q = 0; q < 32; q++) {
                if (func_00100B00(&v, &g->ring[q], &g->ring[q + 1], m, &ln, &depth) == 1) {
                    func_002075F0(&ln, ot, 0xFFFFFF);
                }
            }
        }
        g->burst[i].t++;
        if (g->burst[i].t > 40) {
            g->burst[i].on = 0;
        }
    }

    if (g->t == 0x2F) {
        ret = 1;
    } else {
        if (g->t > 0x39 && g->t < 0x14E) {
            ret = 6;
        }
        if (g->t == 0x14E) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x14F) {
        ret = 8;
    }
    return ret;
}
