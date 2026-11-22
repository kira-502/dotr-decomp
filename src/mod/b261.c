#include "common.h"

/* shape b261:01E00080 (b261), 1426 insns, 1 copy: b261 module main (b483/b512 family, written from the asm): code >=
   0 clears the scene, takes both units, two textures, two joints and the target; else follows the joints' midpoint,
   spawns 4-sprite puffs at the midpoint on 102..135 (32 slots), 32-spark swirls at joint 1 on 129..339 (40 slots,
   spinning out), 32-spark rises at the target on 161..401 (16 slots) and 4-sprite puffs on 129..339 (24 slots), each
   drawn as sprites; returns 1 / 6 / 2 / 8 at 150 / 161..400 / 401 / 403.; the 24-slot spawn header takes (void)n after n = g->t % 24 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b261_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b261_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b261_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b261_01E00080 c;
    Uv_b261_01E00080 uv0;
    Xyz_b261_01E00080 p0;
    Uv_b261_01E00080 uv1;
    Xyz_b261_01E00080 p1;
    u8 tail[0x20];
} Spr_b261_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[4];
    Vec4f pos;
    Vec4f v[4];
} Puff_b261_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 c[32];
    f32 sc[32];
    u8 pad108[8];
    Vec4f pos;
    Vec4f v[32];
} Swirl_b261_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[32];
    u8 pad28[8];
    Vec4f v[32];
} Rise_b261_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex[2];
    s32 m[2];
    Vec4f pos[2];
    Vec4f mid;
    Vec4f tgt;
    Puff_b261_01E00080 a[32];
    Swirl_b261_01E00080 b[40];
    Rise_b261_01E00080 c[16];
    Puff_b261_01E00080 d[24];
} Scene_b261_01E00080;

static s32 func_01E00080_b261(s32 arg0, s32 code) {
    Scene_b261_01E00080 *g = (Scene_b261_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_00101020(f32, f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_00101080(void *, f32);
    extern void func_00100E00(void *, s32, s32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern u8 D_0030FF00[];
    s32 ret;
    s32 ot;
    s32 i;
    s32 k;
    s32 j;
    s32 n;
    s32 c;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 h;
    f32 s;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p0;
    Vec4f p1;
    f32 m4[4][4];
    Vec4f v;
    Vec4f w;
    Spr_b261_01E00080 spr __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB560);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->m[0] = func_001F5560(g->unitA, 0x3B, 1);
        g->m[1] = func_001F5560(g->unitA, 0x3C, 0);
        func_001F53C0(1, g->unitB, &g->tgt);
        for (i = 0; i < 32; i++) {
            g->a[i].on = 0;
        }
        for (i = 0; i < 40; i++) {
            g->b[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->c[i].on = 0;
        }
        for (k = 0; k < 24; k++) {
            g->d[k].on = 0;
        }
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    func_00187B00(&g->mid, &g->pos[0], &g->pos[1]);
    { Vec4f *pm = &g->mid; func_00187B48(pm, pm, 0.5f); }
    if (g->t > 0x65 && g->t < 0x88) {
        n = g->t;
        n %= 32;
        g->a[n].on = 1;
        g->a[n].t = 0;
        g->a[n].pos = g->mid;
        for (k = 0; k < 4; k++) {
            g->a[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->a[n].v[k], 0.4f);
            g->a[n].v[k].y *= 0.5f;
        }
    }

    ((Spr_b261_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b261_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b261_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b261_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b261_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->a[i].on == 0) {
            continue;
        }
        r = 5.0f * (0.2f + 0.8f * g->a[i].t / 32.0f);
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
        alpha = (32 - g->a[i].t) * 96 >> 5;
        spr.c.r = 0x8F;
        spr.c.g = 0x84;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = func_00100D50(g->a[i].t, 32, 1);
        for (j = 0; j < 4; j++) {
            func_00187B48(&v, &g->a[i].v[j], f);
            func_00187B00(&v, &v, &g->a[i].pos);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            c = g->a[i].c[j];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(&p0, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->a[i].t++;
        if (g->a[i].t > 32) {
            g->a[i].on = 0;
        }
    }

    if (g->t > 0x80 && g->t < 0x154) {
        n = g->t;
        n %= 40;
        g->b[n].on = 1;
        g->b[n].t = 0;
        g->b[n].pos = g->pos[1];
        g->b[n].pos.y += -1.0f;
        for (k = 0; k < 32; k++) {
            g->b[n].c[k] = (func_0019A5C8() >> 23) % 8;
            g->b[n].sc[k] = 0.2f + 0.8f * ((func_0019A5C8() >> 23) % 256) / 256.0f;
            func_00101080(&g->b[n].v[k], 1.5f);
        }
    }

    ((Spr_b261_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b261_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b261_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b261_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b261_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    h = (f32)func_00101050(g->t - 0x80, 0, 0x20) * (f32)func_00101050(0x154 - g->t, 0, 0x20) / 1024.0f;
    for (i = 0; i < 40; i++) {
        if (g->b[i].on == 0) {
            continue;
        }
        alpha = (u32)(h * (100.0f * func_00101020((f32)g->b[i].t, 4.0f) * func_00100FF0((f32)g->b[i].t, 40.0f, 26.0f)));
        spr.c.r = 0xFF;
        spr.c.g = 0x38;
        spr.c.b = 0x28;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.4f + 0.6f * g->b[i].t / 40.0f);
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
        s = g->b[i].t / 40.0f;
        for (k = 0; k < 32; k++) {
            c = g->b[i].c[k];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&p0, &cn[0], g->b[i].sc[k]);
            func_00187B48(&p1, &cn[1], g->b[i].sc[k]);
            func_0020BBB0(m4);
            func_00100E00(m4, g->b[i].t * ((i % 2 * 2 - 1) * 0x22B), 2);
            func_001878E0(&w, m4, &g->b[i].v[k]);
            v.x = w.x * s;
            v.z = s * (w.z + -200.0f * g->obj);
            v.y = w.y * s;
            func_00187B00(&v, &v, &g->b[i].pos);
            func_00187B00(&p0, &p0, &v);
            func_00187B00(&p1, &p1, (void *)&v);
            if (func_00205630(&p0, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->b[i].t++;
        if (g->b[i].t > 40) {
            g->b[i].on = 0;
        }
    }

    if (g->t > 0xA0 && g->t < 0x192) {
        n = g->t;
        n %= 16;
        g->c[n].on = 1;
        g->c[n].t = 0;
        for (k = 0; k < 32; k++) {
            g->c[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->c[n].v[k], 1.3f);
        }
    }

    ((Spr_b261_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b261_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b261_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b261_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b261_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    h = (f32)func_00101050(g->t - 0xA0, 0, 0x20) * (f32)func_00101050(0x192 - g->t, 0, 0x20) / 1024.0f;
    for (i = 0; i < 16; i++) {
        if (g->c[i].on == 0) {
            continue;
        }
        alpha = (u32)(h * (134.0f * func_0020B550((g->c[i].t << 15) >> 4)));
        spr.c.r = 0xFF;
        spr.c.g = 0x39;
        spr.c.b = 0x27;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 15.0f * (0.2f + 0.8f * (16 - g->c[i].t) / 16.0f);
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
        r = g->c[i].t / 16.0f;
        s = 0.9f + 0.1f * (16 - g->c[i].t) / 16.0f;
        f = -25.0f + 80.0f * r;
        for (k = 0; k < 32; k++) {
            c = g->c[i].c[k];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            v.x = g->c[i].v[k].x * s;
            v.y = f + g->c[i].v[k].y;
            v.z = g->c[i].v[k].z * s;
            func_00187B00(&v, &v, &g->tgt);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            if (func_00205630(&p0, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->c[i].t++;
        if (g->c[i].t > 16) {
            g->c[i].on = 0;
        }
    }

    if (g->t > 0x80 && g->t < 0x154) {
        n = g->t % 24;
        (void)n;
        g->d[n].on = 1;
        g->d[n].t = 0;
        g->d[n].pos = g->mid;
        for (k = 0; k < 4; k++) {
            g->d[n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->d[n].v[k], 0.5f);
        }
    }

    ((Spr_b261_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b261_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b261_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b261_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b261_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 24; i++) {
        if (g->d[i].on == 0) {
            continue;
        }
        r = 8.0f * (0.2f + 0.8f * (24 - g->d[i].t) / 24.0f);
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
        alpha = (u32)(128.0f * func_0020B550((g->d[i].t << 15) / 24));
        spr.c.r = 0x8F;
        spr.c.g = 0x28;
        spr.c.b = 0x1C;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        h = func_00100D50(g->d[i].t, 24, 1);
        for (k = 0; k < 4; k++) {
            func_00187B48(&v, &g->d[i].v[k], h);
            func_00187B00(&v, &v, &g->d[i].pos);
            func_00187B00(&p0, &cn[0], &v);
            func_00187B00(&p1, &cn[1], (void *)&v);
            c = g->d[i].c[k];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b261_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(&p0, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->d[i].t++;
        if (g->d[i].t > 24) {
            g->d[i].on = 0;
        }
    }

    if (g->t == 0x96) {
        ret = 1;
    } else {
        if (g->t > 0xA0 && g->t < 0x191) {
            ret = 6;
        }
        if (g->t == 0x191) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x192) {
        ret = 8;
    }
    return ret;
}
