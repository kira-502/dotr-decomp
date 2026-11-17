#include "common.h"

/* shape b209:01E00080 (b209), 2122 insns, 1 copy: b209 scene manager (b512:01E00080's family, written from the asm):
   setup clears the 0xB7E0 scene, takes both units, three textures, the target and joint 1, builds a 33-point ring;
   else from frame 0 a 33-frame flickering flare and ring line strip at the joint, 64 randomly turned spinning blade
   quads, at 0x1E a 33-frame screen flash, on 0x1F..0x55 a 20-slot 32-sprite rising puff at the joint, at 0x56 a
   256-sprite burst, a 32-sprite falling arc at the target that seeds 16-slot 32x2 smoke puffs, and a 33-frame render-
   to-texture zoom (8 shrinking screen copies); returns 1 / 2 / 8 at 0x4C / 0x56 / >0x86 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b209_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b209_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b209_01E00080;

typedef struct {
    u64 lo : 32;
    u64 hi : 32;
} Reg_b209_01E00080;

typedef struct {
    Reg_b209_01E00080 a;
    Reg_b209_01E00080 b;
} Tx_b209_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b209_01E00080 c;
    Uv_b209_01E00080 uv0;
    Xyz_b209_01E00080 p0;
    Uv_b209_01E00080 uv1;
    Xyz_b209_01E00080 p1;
    u64 pad38;
    Tx_b209_01E00080 tx;
    u64 pad50;
} Spr_b209_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b209_01E00080 c;
    Xyz_b209_01E00080 p0;
    Xyz_b209_01E00080 p1;
    u64 tail;
} Rect_b209_01E00080;

typedef struct {
    Rgbaq_b209_01E00080 c;
    Xyz_b209_01E00080 p;
} Lv_b209_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Lv_b209_01E00080 v[3];
    u64 tail;
} Line_b209_01E00080;

typedef struct {
    Rgbaq_b209_01E00080 c;
    f32 s, t;
    Xyz_b209_01E00080 p;
} Tv_b209_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b209_01E00080 v[4];
    u8 tail[0x20];
} Quad_b209_01E00080;

typedef struct {
    f32 m[4][4];
} Mtx_b209_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f pos;
    Vec4f v[32];
} Spark_b209_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32][2];
    f32 a;
    u8 pad4C[4];
    Vec4f pos[32];
    Vec4f v[32][2];
} Puff_b209_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    s32 jn;
    u8 pad34[0xC];
    Vec4f jp;
    u8 on1;
    u8 pad51[3];
    s32 t1;
    u8 pad58[8];
    Vec4f ring[33];
    u8 on2;
    u8 pad271[3];
    s32 t2;
    u8 pad278[8];
    Mtx_b209_01E00080 mat[64];
    u8 on3;
    u8 pad1281[3];
    s32 t3;
    u8 pad1288[8];
    Spark_b209_01E00080 spark[20];
    u8 on4;
    u8 pad3F91[3];
    s32 t4;
    u8 c4[256];
    u8 pad4098[8];
    Vec4f v4[256];
    u8 on5;
    u8 pad50A1[3];
    s32 t5;
    u8 c5[32];
    u8 pad50C8[8];
    Vec4f v5[32];
    Puff_b209_01E00080 puff[16];
    u8 on6;
    u8 padB7D1[3];
    s32 t6;
    u8 padB7D8[8];
} Scene_b209_01E00080;

static s32 func_01E00080_b209(s32 arg0, s32 code) {
    Scene_b209_01E00080 *g = (Scene_b209_01E00080 *)arg0;
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
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern f32 func_001A6C48(f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00100B00(void *, void *, void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 y;
    u8 alpha;
    f32 a;
    f32 b;
    f32 r;
    f32 s;
    f32 h;
    f32 w;
    f32 z;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[2];
    Vec4f v;
    Rect_b209_01E00080 rc __attribute__((aligned(8)));
    Spr_b209_01E00080 spr __attribute__((aligned(8)));
    Line_b209_01E00080 ln __attribute__((aligned(8)));
    Quad_b209_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB7E0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn = func_001F5560(g->unitA, 1, 1);
        g->on1 = 0;
        for (i = 0; i < 33; i++) {
            g->ring[i].x = 20.0f * func_0020B550((i << 16) >> 5);
            g->ring[i].y = 20.0f * func_0020B480((i << 16) >> 5);
            g->ring[i].z = 0.0f;
            g->ring[i].w = 1.0f;
        }
        g->on2 = 0;
        g->on3 = 0;
        for (i = 0; i < 20; i++) {
            g->spark[i].on = 0;
        }
        g->on4 = 0;
        g->on5 = 0;
        for (i = 0; i < 16; i++) {
            g->puff[i].on = 0;
        }
        g->on6 = 0;
        return 0;
    }
    func_00205CA0(m3);
    func_001F5620(g->unitA, g->jn, &g->jp);
    if (g->t == 0) {
        g->on1 = 1;
        g->t1 = 0;
    }
    if (g->on1 == 1) {
        ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        x = 0;
        ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->jp);
        func_0020BC00(m, m2);
        a = func_00101050(g->t1, 0, 32) / 32.0f;
        b = (0.8f + 0.2f * (g->t1 % 2)) * a;
        alpha = (u32)(255.0f * b);
        (void)alpha;
        spr.c.r = 0xE8;
        spr.c.g = 0xE0;
        spr.c.b = 0xBE;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 20.0f;
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
        ((Line_b209_01E00080 *)(s32)&ln)->flags = 0x13;
        ((Line_b209_01E00080 *)(s32)&ln)->size = 6;
        ((Line_b209_01E00080 *)(s32)&ln)->regs = 0x414141;
        ((Line_b209_01E00080 *)(s32)&ln)->pad4 = 0;
        func_002086D0(&ln, func_00208D00(1));
        alpha = (u32)(128.0f * b);
        (void)alpha;
        ln.v[0].c.r = 0xFF;
        ln.v[0].c.g = 0xD8;
        ln.v[0].c.b = 0xC4;
        ln.v[0].c.a = alpha;
        ln.v[0].c.q = 1.0f;
        ln.v[1].c.r = 0x64;
        ln.v[1].c.g = 0x64;
        ln.v[1].c.b = 0x64;
        ln.v[1].c.a = 0;
        ln.v[1].c.q = 1.0f;
        ln.v[2].c = ln.v[1].c;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 1.0f;
        for (i = 0; i < 32; i++) {
            if (func_00100B00(&v, &g->ring[i], &g->ring[i + 1], m, &ln, &depth) == 1) {
                ln.v[0].p.z = 0xFFFFF8;
                ln.v[1].p.z = ln.v[0].p.z;
                ln.v[2].p.z = ln.v[0].p.z;
                func_002075F0(&ln, ot, 0);
            }
        }
        g->t1++;
        if (g->t1 > 32) {
            g->on1 = 0;
        }
    }

    if (g->t == 0) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 64; i++) {
            func_00101080(&v, 1.0f);
            func_00100E40(&g->mat[i], &v);
            func_00100E00(&g->mat[i], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
            func_00100E00(&g->mat[i], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
            func_00100E00(&g->mat[i], (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
        }
    }
    if (g->on2 == 1) {
        ((Quad_b209_01E00080 *)(s32)&pk)->flags = 0x34;
        ((Quad_b209_01E00080 *)(s32)&pk)->size = 0xC;
        ((Quad_b209_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b209_01E00080 *)(s32)&pk)->pad4 = 0;
        func_00208700(&pk, g->tex[1], 1);
        func_002086D0(&pk, func_00208D00(1));
        func_00208CB0(&pk, 5);
        a = func_00101050(g->t2, 0, 32) / 32.0f;
        alpha = (u32)(48.0f * ((0.8f + 0.2f * (g->t2 % 2)) * a));
        pk.v[0].c.r = 0xFF;
        pk.v[0].c.g = 0xD8;
        pk.v[0].c.b = 0xC4;
        pk.v[0].c.a = 0;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c.r = 0xFF;
        pk.v[1].c.g = 0xD8;
        pk.v[1].c.b = 0xC4;
        pk.v[1].c.a = alpha;
        pk.v[1].c.q = 1.0f;
        pk.v[2].c.r = 0x20;
        pk.v[2].c.g = 0x10;
        pk.v[2].c.b = 0xC;
        pk.v[2].c.a = 0;
        pk.v[2].c.q = 1.0f;
        pk.v[3].c.r = 0x20;
        pk.v[3].c.g = 0x10;
        pk.v[3].c.b = 0xC;
        pk.v[3].c.a = 0;
        pk.v[3].c.q = 1.0f;
        for (i = 0; i < 64; i++) {
            func_0020EB40(m);
            func_00187B60(m2, &g->mat[i], &g->jp);
            func_00100E00(m2, g->t2 * 0x14D, 0);
            func_00100E00(m2, g->t2 * 0x1BC, 1);
            func_00100E00(m2, g->t2 * 0x63, 2);
            func_0020BC00(m, m2);
            pk.v[0].s = 0.0f;
            pk.v[0].t = 0.5f;
            pk.v[1].s = 0.5f;
            pk.v[1].t = 0.5f;
            pk.v[2].s = 0.0f;
            pk.v[2].t = 1.0f;
            pk.v[3].s = 0.5f;
            pk.v[3].t = 1.0f;
            cn[0].x = 0.0f;
            cn[0].y = -1.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = 0.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = 0.0f;
            cn[2].y = -1.0f;
            cn[2].z = 40.0f;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = 0.0f;
            cn[3].z = 40.0f;
            cn[3].w = 1.0f;
            if (func_00205630(cn, D_0030FF00, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
            pk.v[0].s = 1.0f;
            pk.v[0].t = 0.5f;
            pk.v[1].s = 0.5f;
            pk.v[1].t = 0.5f;
            pk.v[2].s = 1.0f;
            pk.v[2].t = 1.0f;
            pk.v[3].s = 0.5f;
            pk.v[3].t = 1.0f;
            cn[0].x = 0.0f;
            cn[0].y = 1.0f;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = 0.0f;
            cn[1].y = 0.0f;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = 0.0f;
            cn[2].y = 1.0f;
            cn[2].z = 40.0f;
            cn[2].w = 1.0f;
            cn[3].x = 0.0f;
            cn[3].y = 0.0f;
            cn[3].z = 40.0f;
            cn[3].w = 1.0f;
            if (func_00205630(cn, D_0030FF00, m, &pk, &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->t2++;
        if (g->t2 > 32) {
            g->on2 = 0;
        }
    }

    if (g->t == 0x1E) {
        g->on3 = 1;
        g->t3 = 0;
        g->on1 = 0;
        g->on2 = 0;
    }
    if (g->on3 == 1) {
        ((Rect_b209_01E00080 *)(s32)&rc)->flags = 6;
        ((Rect_b209_01E00080 *)(s32)&rc)->size = 3;
        ((Rect_b209_01E00080 *)(s32)&rc)->regs = 0x441;
        ((Rect_b209_01E00080 *)(s32)&rc)->pad4 = 0;
        func_002086D0(&rc, func_00208D00(1));
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->t3, 32, 1)));
        rc.c.r = 0xFF;
        rc.c.g = 0xE8;
        rc.c.b = 0xD8;
        rc.c.a = alpha;
        rc.c.q = 1.0f;
        rc.p0.x = 0x6C00;
        rc.p0.y = 0x7200;
        rc.p0.z = 0xFFFFF8;
        rc.p0.f = 0;
        rc.p1.x = 0x9400;
        rc.p1.y = 0x8E00;
        rc.p1.z = 0xFFFFF8;
        rc.p1.f = 0;
        func_002075F0(&rc, ot, 0);
        g->t3++;
        if (g->t3 > 32) {
            g->on3 = 0;
        }
    }

    if (g->t > 0x1E && g->t < 0x56) {
        n = g->t % 20;
        (void)n;
        g->spark[n].on = 1;
        g->spark[n].t = 0;
        g->spark[n].pos = g->jp;
        for (i = 0; i < 32; i++) {
            g->spark[n].c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->spark[n].v[i], 0.5f);
        }
    }

    ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 20; i++) {
        if (g->spark[i].on == 0) {
            continue;
        }
        alpha = (u32)(70.0f * func_0020B480((g->spark[i].t << 14) / 20));
        spr.c.r = 0xFF;
        spr.c.g = 0x4B;
        spr.c.b = 0x28;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 0.5f + 0.5f * (20 - g->spark[i].t) / 20.0f;
        r = 5.0f * r;
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
        h = (f32)g->spark[i].t / 20.0f;
        w = 0.9f + 0.1f * (20 - g->spark[i].t) / 20.0f;
        z = -2.0f + 30.0f * h;
        for (j = 0; j < 32; j++) {
            x = g->spark[i].c[j] % 4 * 32;
            y = (g->spark[i].c[j] >> 2) * 32;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v.x = g->spark[i].v[j].x * w;
            v.y = z + g->spark[i].v[j].y;
            v.z = g->spark[i].v[j].z * w;
            func_00187B00(&v, &v, &g->spark[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->spark[i].t++;
        if (g->spark[i].t > 20) {
            g->spark[i].on = 0;
        }
    }

    if (g->t == 0x56) {
        g->on4 = 1;
        g->t4 = 0;
        for (i = 0; i < 256; i++) {
            g->c4[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->v4[i], 1.2f);
        }
    }
    if (g->on4 == 1) {
        ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
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
        s = 0.1f + 0.9f * func_00100D50(g->t4, 32, 2);
        h = func_00100FF0((f32)g->t4, 32.0f, 16.0f);
        for (i = 0; i < 256; i++) {
            if (i % 3 == 0) {
                func_002086D0(&spr, func_00208D00(2));
                w = 0.8f * s;
                alpha = (u32)(128.0f * h);
                (void)alpha;
                spr.c.r = 0x80;
                spr.c.g = 0x80;
                spr.c.b = 0x80;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                w = s;
                alpha = (u32)(128.0f * h);
                (void)alpha;
                spr.c.r = 0xFF;
                spr.c.g = 0x50;
                spr.c.b = 0x23;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
            }
            x = g->c4[i] % 4 * 32;
            y = (g->c4[i] >> 2) * 32;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v4[i], w);
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t4++;
        if (g->t4 > 32) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x56) {
        g->on5 = 1;
        g->t5 = 0;
        for (i = 0; i < 32; i++) {
            g->c5[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->v5[i], 3.0f);
        }
    }
    if (g->on5 == 1) {
        ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 3.0f;
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
        a = func_00100FF0((f32)g->t5, 32.0f, 16.0f);
        alpha = (u32)(255.0f * a);
        (void)alpha;
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->t5, 32, 1);
        h = 8.0f * (0.5f * (-0.010896278f * func_001A6C48((f32)g->t5, 2.0f)));
        n = g->t5;
        n %= 16;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        g->puff[n].a = a;
        for (i = 0; i < 32; i++) {
            for (j = 0; j < 2; j++) {
                g->puff[n].c[i][j] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[i][j], 0.2f);
            }
        }
        for (i = 0; i < 32; i++) {
            x = g->c5[i] % 4 * 32;
            y = (g->c5[i] >> 2) * 32;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->v5[i], s);
            v.y += h;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            g->puff[n].pos[i] = v;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->t5++;
        if (g->t5 > 32) {
            g->on5 = 0;
        }
    }

    ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[2], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 16; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        r = 3.0f * (0.5f + 0.5f * (16 - g->puff[i].t) / 16.0f);
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
        h = func_00100FF0((f32)g->puff[i].t, 16.0f, 8.0f);
        alpha = (u32)(255.0f * h * g->puff[i].a);
        spr.c.r = 0xFF;
        spr.c.g = 0x40;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->puff[i].t, 16, 1);
        for (j = 0; j < 32; j++) {
            for (k = 0; k < 2; k++) {
                x = g->puff[i].c[j][k] % 4 * 32;
                y = (g->puff[i].c[j][k] >> 2) * 32;
                ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->puff[i].v[j][k], s);
                func_00187B00(&v, &v, &g->puff[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 16) {
            g->puff[i].on = 0;
        }
    }

    if (g->t == 0x56) {
        g->on6 = 1;
        g->t6 = 0;
    }
    if (g->on6 == 1) {
        ((Spr_b209_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b209_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b209_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b209_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b209_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_002086D0(&spr, func_00208D00(0));
        func_00208CB0(&spr, 5);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &spr.tx.a, &spr.tx.b);
        func_00208460();
        alpha = (32 - g->t6) * 32 >> 5;
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
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
        for (i = 0; i < 8; i++) {
            x = (i + 1) * 42 >> 3;
            y = (i + 1) * 29 >> 3;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->u = (640 - x) << 4;
            ((Uv_b209_01E00080 *)(s32)&spr.uv1)->v = (448 - y) << 4;
            func_002075F0(&spr, 0, 0);
        }
        func_00207FD0(buf, ot, 0);
        g->t6++;
        if (g->t6 > 32) {
            g->on6 = 0;
        }
    }

    if (g->t == 0x4C) {
        ret = 1;
    } else if (g->t == 0x56) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0x86) {
        ret = 8;
    }
    return ret;
}
