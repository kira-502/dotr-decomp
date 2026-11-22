#include "common.h"

/* shape c400:01E00080 (c400), 822 insns, 1 copy: campaign-map sparkle burst (c402:01E00080's form with a
   countdown flag): code >= 0 fills all six slots (ages 6..1) with 128 random sprites; else, once the campaign byte
   0x62 is 2, starts a flag counter, refills the next slot each tick and draws every live slot's sprites as GS sprites
   on a turning matrix, alpha scaled by the flag's ramp (func_00100FF0 160..64), growing and fading over 6 ticks;
   returns 8 once the flag passes 160 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c400_01E00080;

typedef struct {
    u16 u : 14;
    u16 u_pad : 2;
    u16 v : 14;
    u16 v_pad : 2;
} Uv_c400_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c400_01E00080;

typedef struct {
    u64 uv;
    Xyz_c400_01E00080 p;
} Sv_c400_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_c400_01E00080 c;
    Sv_c400_01E00080 v[4];
    u8 tail[0x20];
} Spr_c400_01E00080;

typedef struct {
    u8 c;
    u8 a;
} Col_c400_01E00080;

typedef struct {
    u8 used;
    u8 pad1[3];
    s32 t;
    u8 kind[128];
    f32 sc[128];
    Col_c400_01E00080 col[128];
    s32 xy[128][2];
} Slot_c400_01E00080;

typedef struct {
    s32 flag;
    s32 t;
    void *tex0;
    void *tex1;
    void *tex2;
    s32 next;
    Slot_c400_01E00080 slot[6];
} Ctx_c400_01E00080;

static s32 func_01E00080_c400(s32 arg0, s32 code) {
    Ctx_c400_01E00080 *g = (Ctx_c400_01E00080 *)arg0;
    extern void func_00195108(void *, s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_00100E00(void *, s32, s32);
    extern void func_002075F0(void *, void *, s32);
    s32 ret;
    u8 *ot __attribute__((aligned(8)));
    s32 i;
    s32 j;
    s32 k;
    s32 a;
    s32 s;
    s32 x;
    s32 y;
    f32 r;
    f32 f;
    f32 al;
    Vec4f q[4];
    f32 m[4][4];
    Vec4f off;
    Spr_c400_01E00080 pk __attribute__((aligned(8)));

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2D50);
        g->flag = 0;
        g->t = 0;
        g->tex0 = func_00202BF0(8, 0x18);
        g->tex1 = func_00202BF0(8, 0x19);
        g->tex2 = func_00202BF0(8, 0x1A);
        g->next = 0;
        for (i = 0; i < 6; i++) {
            g->slot[i].used = 0;
        }
        for (k = 0; k < 6; k++) {
            a = g->next++;
            if (g->next >= 6) {
                g->next = 0;
            }
            g->slot[a].used = 1;
            g->slot[a].t = 6 - k;
            for (i = 0; i < 128; i++) {
                g->slot[a].kind[i] = (func_0019A5C8() >> 23) % 8;
                g->slot[a].sc[i] = 0.4f + 0.6f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f;
                g->slot[a].col[i].c = (u32)(255.0f * (0.9f + 0.1f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->slot[a].col[i].a = (u32)(128.0f * (0.3f + 0.7f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f));
                g->slot[a].xy[i][0] = (s32)(-490.0f + 980.0f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f);
                g->slot[a].xy[i][1] = (s32)(-490.0f + 980.0f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f);
            }
        }
        return 0;
    }
    if (*(s8 *)(CAMPAIGN_WORK_ADDR + 0x62) == 2 && g->flag == 0) {
        g->flag = 1;
    }
    a = g->next++;
    if (g->next >= 6) {
        g->next = 0;
    }
    g->slot[a].used = 1;
    g->slot[a].t = 0;
    for (k = 0; k < 128; k++) {
        g->slot[a].kind[k] = (func_0019A5C8() >> 23) % 8;
        g->slot[a].sc[k] = 0.4f + 0.6f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f;
        g->slot[a].col[k].c = (u32)(255.0f * (1.0f + 0.0f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f));
        g->slot[a].col[k].a = (u32)(128.0f * (0.3f + 0.7f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f));
        g->slot[a].xy[k][0] = (s32)(-490.0f + 980.0f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f);
        g->slot[a].xy[k][1] = (s32)(-490.0f + 980.0f * (f32)((func_0019A5C8() >> 23) % 256) / 256.0f);
    }
    ((Spr_c400_01E00080 *)(s32)&pk)->flags = 0x24;
    ((Spr_c400_01E00080 *)(s32)&pk)->size = 9;
    ((Spr_c400_01E00080 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr_c400_01E00080 *)(s32)&pk)->pad4 = 0;
    ((Spr_c400_01E00080 *)(s32)&pk)->flags |= 0x800;
    func_00208700(&pk, g->tex1, 1);
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, 0);
    f = func_00100FF0((f32)g->flag, 160.0f, 64.0f);
    func_0020BBB0(m);
    func_00100E00(m, (g->t * 3) << 8, 2);
    for (i = 0; i < 6; i++) {
        if (g->slot[i].used != 0) {
            al = f * func_0020B550((g->slot[i].t << 15) / 6);
            r = 0.4f + 0.7f * (f32)g->slot[i].t / 6.0f;
            for (k = 0; k < 128; k++) {
                a = (u32)((f32)g->slot[i].col[k].a * al);
                pk.c.r = g->slot[i].col[k].c;
                pk.c.g = g->slot[i].col[k].c;
                pk.c.b = g->slot[i].col[k].c;
                pk.c.a = a;
                pk.c.q = 1.0f;
                s = (s32)(170.0f * (0.4f + 0.6f * (f32)g->slot[i].t / 6.0f) * g->slot[i].sc[k]);
                x = g->slot[i].kind[k] % 4 * 32;
                y = (g->slot[i].kind[k] >> 2) * 32;
                ((Uv_c400_01E00080 *)(s32)&pk.v[0].uv)->u = x << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[0].uv)->v = y << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[1].uv)->u = (x + 32) << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[1].uv)->v = y << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[2].uv)->u = x << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[2].uv)->v = (y + 32) << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[3].uv)->u = (x + 32) << 4;
                ((Uv_c400_01E00080 *)(s32)&pk.v[3].uv)->v = (y + 32) << 4;
                off.x = (f32)g->slot[i].xy[k][0] * r;
                off.y = (f32)g->slot[i].xy[k][1] * r;
                off.z = 0.0f;
                off.w = 1.0f;
                q[0].x = -s;
                q[0].y = -s;
                q[0].z = 0.0f;
                q[0].w = 1.0f;
                q[1].x = s;
                q[1].y = -s;
                q[1].z = 0.0f;
                q[1].w = 1.0f;
                q[2].x = -s;
                q[2].y = s;
                q[2].z = 0.0f;
                q[2].w = 1.0f;
                q[3].x = s;
                q[3].y = s;
                q[3].z = 0.0f;
                q[3].w = 1.0f;
                for (j = 0; j < 4; j++) {
                    func_00187B00(&q[j], &q[j], &off);
                    func_001878E0(&q[j], m, &q[j]);
                }
                x = (s32)q[0].x;
                y = (s32)q[0].y;
                pk.v[0].p.x = (x + 0x800) << 4;
                pk.v[0].p.y = (y + 0x800) << 4;
                pk.v[0].p.z = 0xFFFFF7;
                pk.v[0].p.f = 0;
                x = (s32)q[1].x;
                y = (s32)q[1].y;
                pk.v[1].p.x = (x + 0x800) << 4;
                pk.v[1].p.y = (y + 0x800) << 4;
                pk.v[1].p.z = 0xFFFFF7;
                pk.v[1].p.f = 0;
                x = (s32)q[2].x;
                y = (s32)q[2].y;
                pk.v[2].p.x = (x + 0x800) << 4;
                pk.v[2].p.y = (y + 0x800) << 4;
                pk.v[2].p.z = 0xFFFFF7;
                pk.v[2].p.f = 0;
                x = (s32)q[3].x;
                y = (s32)q[3].y;
                pk.v[3].p.x = (x + 0x800) << 4;
                pk.v[3].p.y = (y + 0x800) << 4;
                pk.v[3].p.z = 0xFFFFF7;
                pk.v[3].p.f = 0;
                func_002075F0(&pk, ot, 0);
            }
            g->slot[i].t++;
            if (g->slot[i].t > 6) {
                g->slot[i].used = 0;
            }
        }
    }
    g->t++;
    if (g->flag > 0) {
        g->flag++;
    }
    if (g->flag > 0xA0) {
        ret = 8;
    }
    return ret;
}
