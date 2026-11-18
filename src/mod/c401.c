#include "common.h"

/* shape c401:01E00080 (c401), 731 insns, 1 copy: flash and ribbon draw: the draw loop's counter is set right after
   the per-slot fraction */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c401_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c401_01E00080;

typedef struct {
    Rgbaq_c401_01E00080 c;
    f32 s, t;
    Xyz_c401_01E00080 p;
} Tv_c401_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_c401_01E00080 v[4];
    u8 tail[0x20];
} Tex_c401_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_c401_01E00080 c;
    Xyz_c401_01E00080 v[2];
    u64 tail;
} Spr_c401_01E00080;

typedef struct {
    f32 w;
    f32 c[3];
    Vec4f pos;
    f32 near;
    f32 far;
    f32 k;
} Light_c401_01E00080;

typedef struct {
    u8 used;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Vec4f dir;
    f32 len;
    f32 a[32];
    f32 b[32];
    u8 pad184[0xC];
    f32 mat[32][4][4];
} Slot_c401_01E00080;

typedef struct {
    s32 t;
    s32 t2;
    void *tex0;
    void *tex1;
    void *tex2;
    u8 pad14[0xC];
    Vec4f pos;
    Vec4f target;
    s32 next;
    u8 pad44[0xC];
    Slot_c401_01E00080 slot[1];
    u8 flash;
    u8 pad991[3];
    s32 flash_t;
    u8 light;
    u8 pad999[3];
    s32 light_t;
} Ctx_c401_01E00080;

static s32 func_01E00080_c401(s32 arg0, s32 code) {
    Ctx_c401_01E00080 *g = (Ctx_c401_01E00080 *)arg0;
    extern u8 D_0030FF00[];
    extern void func_00195108(void *, s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_002075F0(void *, void *, s32);
    extern void func_001F9940(s32, s32, void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    s32 ret;
    u8 *ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 a;
    Vec4f *p;
    f32 z0;
    f32 u0;
    f32 y0;
    f32 y1;
    f32 u1;
    f32 al;
    f32 sc;
    f32 sw;
    f32 z1;
    f32 w;
    f32 x0;
    f32 x1;
    f32 f;
    f32 t0;
    f32 t1;
    f32 mt[4][4];
    f32 mt2[4][4];
    Vec4f q[4];
    Light_c401_01E00080 l;
    Tex_c401_01E00080 pk __attribute__((aligned(8)));
    Spr_c401_01E00080 sp __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x9A0);
        g->t = 0;
        g->t2 = 0;
        g->tex0 = func_00202BF0(8, 0x18);
        g->tex1 = func_00202BF0(8, 0x19);
        g->tex2 = func_00202BF0(8, 0x1A);
        g->pos.x = 0.0f;
        g->pos.y = 800.0f;
        g->pos.z = 0.0f;
        g->pos.w = 1.0f;
        g->target.x = 0.0f;
        g->target.y = 0.0f;
        g->target.z = 0.0f;
        g->target.w = 1.0f;
        g->next = 0;
        for (i = 0; i < 1; i++) {
            g->slot[i].used = 0;
        }
        g->flash = 0;
        g->light = 0;
        return 0;
    }
    if (g->t == 0x20) {
        g->flash = 1;
        g->flash_t = 0;
    }
    if (g->flash == 1) {
        ((Spr_c401_01E00080 *)(s32)&sp)->flags = 6;
        ((Spr_c401_01E00080 *)(s32)&sp)->size = 3;
        ((Spr_c401_01E00080 *)(s32)&sp)->regs = 0x441;
        ((Spr_c401_01E00080 *)(s32)&sp)->pad4 = 0;
        func_002086D0(&sp, func_00208D00(1));
        a = (u32)(128.0f * ((f32)(0x30 - g->flash_t) / 48.0f));
        sp.c.r = 0xC8;
        sp.c.g = 0xDC;
        sp.c.b = 0xFF;
        sp.c.a = a;
        sp.c.q = 1.0f;
        sp.v[0].x = 0x6C00;
        sp.v[0].y = 0x7200;
        sp.v[0].z = 0xFFFFF7;
        sp.v[0].f = 0;
        sp.v[1].x = 0x9400;
        sp.v[1].y = 0x8E00;
        sp.v[1].z = 0xFFFFF7;
        sp.v[1].f = 0;
        func_002075F0(&sp, ot, 0);
        g->flash_t++;
        if (g->flash_t > 0x30) {
            g->flash = 0;
        }
    }
    if (g->t == 0x1F) {
        g->light = 1;
        g->light_t = 0;
    }
    if (g->light == 1) {
        l.c[0] = 100.0f;
        l.c[1] = 100.0f;
        l.c[2] = 100.0f;
        l.w = 1.0f;
        l.pos.x = 0.0f;
        l.pos.y = 20.0f;
        l.pos.z = 0.0f;
        l.pos.w = 1.0f;
        l.near = 10.0f;
        l.far = 500.0f;
        l.k = (f32)(0x30 - g->light_t) / 48.0f;
        func_001F9940(0, 7, &l);
        g->light_t++;
        if (g->light_t > 0x30) {
            g->light = 0;
            func_001F9940(0, 7, 0);
        }
    }
    if (g->t == 0x10) {
        g->slot[a = g->next].used = 1;
        g->slot[a].t = 0;
        g->slot[a].pos = g->pos;
        func_00187B18(&g->slot[a].dir, &g->target, &g->slot[a].pos);
        g->slot[a].len = func_001A6C60(func_001A6C48(g->slot[a].dir.x, 2.0f) + func_001A6C48(g->slot[a].dir.y, 2.0f) +
                                       func_001A6C48(g->slot[a].dir.z, 2.0f));
        for (i = 0; i < 32; i++) {
            g->slot[a].a[i] = 40.0f * (0.5f + 0.5f * (f32)((s32)(func_0019A5C8() >> 23) % 256) / 256.0f);
            g->slot[a].b[i] = 15.0f * (0.5f + 0.5f * (f32)((s32)(func_0019A5C8() >> 23) % 256) / 256.0f);
            func_00100E40(g->slot[a].mat[i], (f32 *)&g->slot[a].dir);
            func_00100E00(g->slot[a].mat[i], (((s32)(func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
        }
        g->next++;
        if (g->next > 0) {
            g->next = 0;
        }
    }
    ((Tex_c401_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_c401_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_c401_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_c401_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex2, 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 1; i++) {
        if (g->slot[i].used != 0) {
            n = (s32)(32.0f * func_00101020((f32)g->slot[i].t, 16.0f));
            if (n > 32) {
                n = 32;
            }
            f = (f32)(0x40 - g->slot[i].t) / 64.0f;
            j = 0;
            p = &g->slot[i].pos;
            al = 100.0f * f;
            sc = 0.5f + 0.5f * f;
            sw = 1.0f + 0.5f * (1.0f - f);
            for (; j < 32; j++) {
                func_0020EB40(mt);
                func_00187B60(mt2, g->slot[i].mat[j], p);
                func_0020BC00(mt, mt2);
                u0 = 32.0f * (f32)(j % 4) / 128.0f;
                k = 0;
                if (k < n) {
                    u1 = 0.25f + u0;
                    do {
                    y0 = 400.0f * (1.0f - func_00100D50(k, 0x20, 2));
                    y1 = 400.0f * (1.0f - func_00100D50(k + 1, 0x20, 2));
                    a = (u32)(al * (f32)k / 32.0f);
                    pk.v[0].c.r = 0x80;
                    pk.v[0].c.g = 0x80;
                    pk.v[0].c.b = 0x80;
                    pk.v[0].c.a = a;
                    pk.v[0].c.q = 1.0f;
                    pk.v[1].c = pk.v[0].c;
                    a = (u32)(al * (f32)(k + 1) / 32.0f);
                    pk.v[2].c.r = 0x80;
                    pk.v[2].c.g = 0x80;
                    pk.v[2].c.b = 0x80;
                    pk.v[2].c.a = a;
                    pk.v[2].c.q = 1.0f;
                    pk.v[3].c = pk.v[2].c;
                    if (k == n - 1) {
                        pk.v[2].c.r = 0x80;
                        pk.v[2].c.g = 0x80;
                        pk.v[2].c.b = 0x80;
                        pk.v[2].c.a = 0;
                        pk.v[2].c.q = 1.0f;
                        pk.v[3].c = pk.v[2].c;
                    }
                    t0 = 128.0f * (f32)((k + j) % 8) / 8.0f / 128.0f;
                    t1 = 128.0f * (f32)((k + j) % 8 + 1) / 8.0f / 128.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = t0;
                    pk.v[1].s = u1;
                    pk.v[1].t = t0;
                    pk.v[2].s = u0;
                    pk.v[2].t = t1;
                    pk.v[3].s = u1;
                    pk.v[3].t = t1;
                    z0 = g->slot[i].len * (f32)k / 32.0f;
                    z1 = g->slot[i].len * (f32)(k + 1) / 32.0f;
                    w = g->slot[i].a[j] * sc;
                    x0 = sw * (g->slot[i].b[j] * func_0020B480((u16)(((k << 17) >> 5) + (i * 0x15B3 + j * 0x411A))));
                    x1 = sw * (g->slot[i].b[j] * func_0020B480((u16)((((k + 1) << 17) >> 5) + (i * 0x15B3 + j * 0x411A))));
                    q[0].x = x0;
                    q[0].y = -w + y0;
                    q[0].z = z0;
                    q[0].w = 1.0f;
                    q[1].x = x0;
                    q[1].y = w + y0;
                    q[1].z = z0;
                    q[1].w = 1.0f;
                    q[2].x = x1;
                    q[2].y = -w + y1;
                    q[2].z = z1;
                    q[2].w = 1.0f;
                    q[3].x = x1;
                    q[3].y = w + y1;
                    q[3].z = z1;
                    q[3].w = 1.0f;
                    if (func_002058D0(q, D_0030FF00, mt, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                    } while (++k < n);
                }
            }
            g->slot[i].t++;
            if (g->slot[i].t > 0x40) {
                g->slot[i].used = 0;
            }
        }
    }
    g->t2++;
    g->t++;
    if (g->t > 0x70) {
        ret = 8;
    }
    return ret;
}
