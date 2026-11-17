#include "common.h"

/* shape b165:01E00080 (b165), 1748 insns, 1 copy: b165 scene manager (b175:01E00080's family): setup clears the
   0x92B0 scene, takes both units, two textures, the target and joint 0x5D; frames 0xA1..0x144 spawn a rising 8-mote
   puff at the joint and an 8-sprite ring at the target per frame in 20 slots (depth-fixed sprites), every 4th frame
   below 0x60 a bouncing bolt spiralling into the joint that leaves 16-slot 4-spark trails, and from frame 0 a
   32-frame white flash and a 0x166-frame purple screen fade; returns 1 / 6 / 2 / 8 at 0x96 / 0xA1..0x144 / 0x145 /
   >0x165 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b165_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b165_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b165_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b165_01E00080 c;
    Uv_b165_01E00080 uv0;
    Xyz_b165_01E00080 p0;
    Uv_b165_01E00080 uv1;
    Xyz_b165_01E00080 p1;
    u64 tail;
} Spr_b165_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b165_01E00080 c;
    Xyz_b165_01E00080 v[2];
    u64 tail;
} Flat_b165_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f p;
    Vec4f v[8];
} Mote_b165_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f v[8];
} Ring_b165_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c;
    s8 dc;
    u8 nspark;
    u8 padB[5];
    Vec4f p;
} Bolt_b165_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    f32 f;
    Vec4f p;
    Vec4f v[4];
} Spark_b165_01E00080;

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
    Mote_b165_01E00080 mote[20];
    Ring_b165_01E00080 ring[20];
    s32 nbolt;
    u8 pad1814[0xC];
    Bolt_b165_01E00080 bolt[20];
    Spark_b165_01E00080 spark[20][16];
    u8 flash;
    u8 pad92A1[3];
    s32 ft;
    u8 fade;
    u8 pad92A9[3];
    s32 dt;
} Scene_b165_01E00080;

static s32 func_01E00080_b165(s32 arg0, s32 code) {
    Scene_b165_01E00080 *g = (Scene_b165_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
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
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    s32 ot;
    s32 ret;
    s32 buf;
    s32 i;
    s32 j;
    s32 q;
    s32 c;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    f32 f;
    f32 r;
    f32 s;
    f32 h;
    f32 k;
    f32 w;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b165_01E00080 spr __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    Flat_b165_01E00080 flat __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x92B0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F53C0(1, g->unitB, &g->tgt);
        g->m0 = func_001F5560(g->unitA, 0x5D, 1);
        for (i = 0; i < 20; i++) {
            g->mote[i].on = 0;
        }
        for (i = 0; i < 20; i++) {
            g->ring[i].on = 0;
        }
        g->nbolt = 0;
        for (i = 0; i < 20; i++) {
            g->bolt[i].on = 0;
            g->bolt[i].nspark = 0;
        }
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 16; j++) {
                g->spark[i][j].on = 0;
            }
        }
        g->flash = 0;
        g->fade = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->m0, &g->pos0);
    if (g->t > 0xA0 && g->t < 0x145) {
        n = g->t % 20;
        (void)n;
        g->mote[n].on = 1;
        g->mote[n].t = 0;
        g->mote[n].p = g->pos0;
        for (j = 0; j < 8; j++) {
            g->mote[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->mote[n].v[j], 0.1f);
        }
    }

    ((Spr_b165_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b165_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b165_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b165_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b165_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0xA0, 0, 8) * (f32)func_00101050(0x145 - g->t, 0, 8) / 64.0f;
    for (i = 0; i < 20; i++) {
        if (g->mote[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (112.0f * func_0020B550((g->mote[i].t << 15) / 20)));
        spr.c.r = 0x20;
        spr.c.g = 0x20;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 2.0f * (0.2f + 0.8f * (20 - g->mote[i].t) / 20.0f);
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
        w = g->mote[i].t / 20.0f;
        s = 0.9f + 0.1f * (20 - g->mote[i].t) / 20.0f;
        h = -3.0f + 11.0f * w;
        for (q = 0; q < 8; q++) {
            ((Uv_b165_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->mote[i].c[q]][0];
            ((Uv_b165_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->mote[i].c[q]][2];
            ((Uv_b165_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->mote[i].c[q]][1];
            ((Uv_b165_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->mote[i].c[q]][3];
            v.x = g->mote[i].v[q].x * s;
            v.y = h + g->mote[i].v[q].y;
            v.z = g->mote[i].v[q].z * s;
            func_00187B00(&v, &v, &g->mote[i].p);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->mote[i].t++;
        if (g->mote[i].t > 20) {
            g->mote[i].on = 0;
        }
    }

    if (g->t > 0xA0 && g->t < 0x145) {
        n = g->t % 20;
        (void)n;
        g->ring[n].on = 1;
        g->ring[n].t = 0;
        for (j = 0; j < 8; j++) {
            g->ring[n].c[j] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->ring[n].v[j], 1.0f);
        }
    }

    ((Spr_b165_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b165_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b165_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b165_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b165_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    f = (f32)func_00101050(g->t - 0xA0, 0, 16) * (f32)func_00101050(0x145 - g->t, 0, 16) / 256.0f;
    for (i = 0; i < 20; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        alpha = (u32)(f * (112.0f * func_0020B550((g->ring[i].t << 15) / 20)));
        spr.c.r = 0x20;
        spr.c.g = 0x20;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 20.0f * (0.2f + 0.8f * (20 - g->ring[i].t) / 20.0f);
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
        w = g->ring[i].t / 20.0f;
        s = 0.9f + 0.1f * (20 - g->ring[i].t) / 20.0f;
        h = -35.0f + 110.0f * w;
        for (q = 0; q < 8; q++) {
            ((Uv_b165_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->ring[i].c[q]][0];
            ((Uv_b165_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->ring[i].c[q]][2];
            ((Uv_b165_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->ring[i].c[q]][1];
            ((Uv_b165_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->ring[i].c[q]][3];
            v.x = g->ring[i].v[q].x * s;
            v.y = h + g->ring[i].v[q].y;
            v.z = g->ring[i].v[q].z * s;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 20) {
            g->ring[i].on = 0;
        }
    }

    if (g->t % 4 == 0 && g->t > 0 && g->t < 0x60) {
        n = g->nbolt;
        (void)n;
        g->bolt[n].on = 1;
        g->bolt[n].t = 0;
        g->bolt[n].c = 0;
        g->bolt[n].dc = 1;
        func_00101080(&g->bolt[n].p, 3.0f);
        func_00187B00(&g->bolt[n].p, &g->bolt[n].p, &g->pos0);
        g->nbolt++;
        if (g->nbolt >= 20) {
            g->nbolt = 0;
        }
    }

    ((Spr_b165_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b165_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b165_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b165_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b165_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[1], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 20; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        f = (f32)g->bolt[i].t / 64.0f;
        alpha = (u32)(255.0f * f);
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x80;
        spr.c.b = 0xB4;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = g->bolt[i].c % 4 * 32;
        y = (g->bolt[i].c >> 2) * 32;
        g->bolt[i].c += g->bolt[i].dc;
        if (g->bolt[i].c == 0 || g->bolt[i].c == 4) {
            g->bolt[i].dc = -g->bolt[i].dc;
        }
        ((Uv_b165_01E00080 *)(s32)&spr.uv0)->u = x << 4;
        ((Uv_b165_01E00080 *)(s32)&spr.uv0)->v = y << 4;
        ((Uv_b165_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
        ((Uv_b165_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
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
        k = (f32)(64 - g->bolt[i].t) / 64.0f;
        w = 7.0f * k * (f32)(i % 2 * 2 - 1);
        ang = (s32)(32768.0f * k);
        func_00187B18(&v, &g->bolt[i].p, &g->pos0);
        func_00187B48(&v, &v, k);
        func_00187B00(&v, &v, &g->pos0);
        v.x += w * func_0020B550(ang);
        v.y += w * func_0020B480(ang);
        v.z += w * func_0020B480(ang);
        func_00187B00(&out[0], &cn[0], &v);
        func_00187B00(&out[1], &cn[1], (void *)&v);
        if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
            func_002075F0(&spr, ot, (u32)depth);
        }
        n = g->bolt[i].nspark;
        g->spark[i][n].on = 1;
        g->spark[i][n].t = 0;
        g->spark[i][n].f = f;
        g->spark[i][n].p = v;
        for (q = 0; q < 4; q++) {
            g->spark[i][n].c[q] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->spark[i][n].v[q], 0.2f);
        }
        g->bolt[i].nspark++;
        if (g->bolt[i].nspark >= 16) {
            g->bolt[i].nspark = 0;
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 64) {
            g->bolt[i].on = 0;
        }
    }

    ((Spr_b165_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b165_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b165_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b165_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b165_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 16; j++) {
            if (g->spark[i][j].on == 0) {
                continue;
            }
            alpha = (u32)(g->spark[i][j].f * (64.0f * func_0020B480((g->spark[i][j].t << 14) >> 4)));
            spr.c.r = 0x80;
            spr.c.g = 0x40;
            spr.c.b = 0x64;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 1.3f * (0.2f + 0.8f * (16 - g->spark[i][j].t) / 16.0f);
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
            w = g->spark[i][j].t / 16.0f;
            s = 0.2f + 0.8f * g->spark[i][j].t / 16.0f;
            r = 6.0f * w;
            for (c = 0; c < 4; c++) {
                ((Uv_b165_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->spark[i][j].c[c]][0];
                ((Uv_b165_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->spark[i][j].c[c]][2];
                ((Uv_b165_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->spark[i][j].c[c]][1];
                ((Uv_b165_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->spark[i][j].c[c]][3];
                v.x = g->spark[i][j].v[c].x * s;
                v.y = r + g->spark[i][j].v[c].y * s;
                v.z = g->spark[i][j].v[c].z * s;
                func_00187B00(&v, &v, &g->spark[i][j].p);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->spark[i][j].t++;
            if (g->spark[i][j].t > 16) {
                g->spark[i][j].on = 0;
            }
        }
    }

    if (g->t == 0) {
        g->flash = 1;
        g->ft = 0;
    }
    if (g->flash == 1) {
        ((Flat_b165_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b165_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b165_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b165_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(1));
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->ft, 0x20, 1)));
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
        g->ft++;
        if (g->ft > 32) {
            g->flash = 0;
        }
    }
    if (g->t == 0) {
        g->fade = 1;
        g->dt = 0;
    }
    if (g->fade == 1) {
        buf = func_00207F60();
        ((Spr_b165_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b165_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b165_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b165_01E00080 *)(s32)&spr)->pad4 = 0;
        func_00208460();
        func_00208800(func_00209E50(), 0, &a, b);
        func_00208460();
        ((Flat_b165_01E00080 *)(s32)&flat)->flags = 6;
        ((Flat_b165_01E00080 *)(s32)&flat)->size = 3;
        ((Flat_b165_01E00080 *)(s32)&flat)->regs = 0x441;
        ((Flat_b165_01E00080 *)(s32)&flat)->pad4 = 0;
        func_002086D0(&flat, func_00208D00(3));
        alpha = func_00101050(0x165 - g->dt, 0, 0x20) << 7 >> 5;
        flat.c.r = 0x60;
        flat.c.g = 0;
        flat.c.b = 0x80;
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
        func_002075F0(&flat, 0, 0);
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, ((u64)0x700 << 32) | 0xA0000A);
        x = 0;
        ((Spr_b165_01E00080 *)(s32)&spr)->flags |= 0x800;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = 0x80 - alpha;
        spr.c.q = 1.0f;
        ((Uv_b165_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b165_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b165_01E00080 *)(s32)&spr.uv1)->u = 0x2800;
        ((Uv_b165_01E00080 *)(s32)&spr.uv1)->v = 0x1C00;
        spr.p0.x = 0x6BF8;
        spr.p0.y = 0x71F8;
        spr.p0.z = 0xFFFFF8;
        spr.p0.f = 0;
        spr.p1.x = 0x93F8;
        spr.p1.y = 0x8DF8;
        spr.p1.z = 0xFFFFF8;
        spr.p1.f = 0;
        func_002075F0(&spr, 0, 0);
        func_00207FD0(buf, ot, 0xFFFFFF);
        g->dt++;
        if (g->dt > 0x165) {
            g->fade = 0;
        }
    }

    if (g->t == 0x96) {
        ret = 1;
    } else {
        if (g->t > 0xA0 && g->t < 0x145) {
            ret = 6;
        }
        if (g->t == 0x145) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x165) {
        ret = 8;
    }
    return ret;
}
