#include "common.h"

/* shape c403:01E00080 (c403), 423 insns, 1 copy: the ship wake (campaign map): code >= 0 builds a 17-point two-ring
   half circle and clears 32 slots; else every 6 ticks while the ship sails it drops a slot at the ship (campaign work
   0x1A4..0x1B8), and draws each slot as 16 textured quads growing and fading over 32 ticks; returns 8 once stopped
   for 32 ticks */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c403_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c403_01E00080;

typedef struct {
    Rgbaq_c403_01E00080 c;
    f32 s, t;
    Xyz_c403_01E00080 p;
} Tv_c403_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_c403_01E00080 v[4];
    u8 tail[0x20];
} Tex_c403_01E00080;

typedef struct {
    u8 used;
    u8 pad1[3];
    s32 t;
    u8 kind;
    u8 pad9[3];
    s32 ang;
    f32 scale;
    u8 pad14[0xC];
    Vec4f pos;
} Slot_c403_01E00080;

typedef struct {
    s32 t;
    s32 t2;
    void *tex0;
    void *tex1;
    void *tex2;
    u8 pad14[0xC];
    Vec4f pos;
    s32 ang;
    f32 scale;
    s16 stop;
    u8 pad3A[6];
    Vec4f ring[17][2];
    s32 next;
    u8 pad264[0xC];
    Slot_c403_01E00080 slot[32];
} Ctx_c403_01E00080;

static s32 func_01E00080_c403(s32 arg0, s32 code) {
    Ctx_c403_01E00080 *g = (Ctx_c403_01E00080 *)arg0;
    extern void func_00195108(void *, s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_00100E00(void *, s32, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, void *, s32);
    s32 ret;
    u8 *ot;
    s32 i;
    s32 j;
    s32 u;
    f32 tv;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;
    f32 sc;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    Vec4f v;
    Tex_c403_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x870);
        g->t = 0;
        g->t2 = 0;
        g->tex0 = func_00202BF0(8, 0x18);
        g->tex1 = func_00202BF0(8, 0x19);
        g->tex2 = func_00202BF0(8, 0x1A);
        g->stop = 0;
        for (i = 0; i < 17; i++) {
            u = (i << 15) >> 4;
            g->ring[i][0].x = 6.0f * func_0020B480(u);
            g->ring[i][0].y = 1.0f;
            g->ring[i][0].z = 9.0f * (6.0f * func_0020B550(u));
            g->ring[i][0].w = 1.0f;
            g->ring[i][1].x = 12.0f * func_0020B480(u);
            g->ring[i][1].y = 1.0f;
            g->ring[i][1].z = 5.0f * (12.0f * func_0020B550(u));
            g->ring[i][1].w = 1.0f;
            g->ring[i][0].z -= 27.0f;
            g->ring[i][1].z -= 27.0f;
        }
        g->next = 0;
        for (i = 0; i < 32; i++) {
            g->slot[i].used = 0;
        }
        return 0;
    }
    g->pos = *(Vec4f *)(CAMPAIGN_WORK_ADDR + 0x1B8);
    g->ang = *(s32 *)(CAMPAIGN_WORK_ADDR + 0x1A8);
    if (*(s8 *)(CAMPAIGN_WORK_ADDR + 0x1AC) == 0) {
        g->scale = 1.0f;
    } else {
        g->scale = 0.5f;
    }
    if (*(s16 *)(CAMPAIGN_WORK_ADDR + 0x1A4) != 2) {
        g->stop = 1;
    }
    if (g->t % 6 == 0 && g->stop == 0) {
        g->slot[i = g->next].used = 1;
        g->slot[i].t = 0;
        g->slot[i].kind = (func_0019A5C8() >> 23) % 4 + 4;
        g->slot[i].pos = g->pos;
        g->slot[i].ang = g->ang;
        g->slot[i].scale = g->scale;
        g->next++;
        if (g->next >= 32) {
            g->next = 0;
        }
    }
    ((Tex_c403_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_c403_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_c403_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_c403_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex0, 1);
    func_00208CB0(&pk, 5);
    for (i = 0; i < 32; i++) {
        if (g->slot[i].used != 0) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->slot[i].pos);
            sc = (0.1f + 0.9f * (f32)g->slot[i].t / 32.0f) * g->slot[i].scale;
            v.x = sc;
            v.y = 1.0f;
            v.z = sc;
            v.w = 1.0f;
            func_0020CB20(m2, &v);
            func_00100E00(m2, g->slot[i].ang, 1);
            func_0020BC00(m, m2);
            f = 56.0f * func_00101020((f32)g->slot[i].t, 1.0f);
            u = func_001A23B0(f * func_00100FF0((f32)g->slot[i].t, 32.0f, 16.0f));
            pk.v[0].c.r = 0x80;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0x80;
            pk.v[0].c.a = u;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            u = g->slot[i].kind % 4 * 32;
            tv = (g->slot[i].kind >> 2) * 32;
            t0 = tv / 64.0f;
            t1 = (32.0f + tv) / 64.0f;
            for (j = 0; j < 16; j++) {
                s0 = ((f32)u + 32.0f * func_0020B550((j << 15) >> 4)) / 128.0f;
                s1 = ((f32)u + 32.0f * func_0020B550(((j + 1) << 15) >> 4)) / 128.0f;
                pk.v[0].s = s0;
                pk.v[0].t = t0;
                pk.v[1].s = s1;
                pk.v[1].t = t0;
                pk.v[2].s = s0;
                pk.v[2].t = t1;
                pk.v[3].s = s1;
                pk.v[3].t = t1;
                if (func_00100BA0(&g->ring[j][0], &g->ring[j + 1][0], &g->ring[j][1], &g->ring[j + 1][1], m, &pk,
                                  &depth) == 1) {
                    func_002075F0(&pk, ot, func_001A23B0(depth));
                }
            }
            g->slot[i].t++;
            if (g->slot[i].t > 32) {
                g->slot[i].used = 0;
            }
        }
    }
    g->t++;
    if (g->stop == 1) {
        g->t2++;
    }
    if (g->t2 > 32) {
        ret = 8;
    }
    return ret;
}
