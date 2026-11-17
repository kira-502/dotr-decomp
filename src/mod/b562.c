#include "common.h"

/* shape b562:01E00080 (b562), 1884 insns, 1 copy: GS packet scene effect: fans, spinners, bolts and textured ring
   strips */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b562_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b562_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b562_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b562_01E00080 c;
    Uv_b562_01E00080 uv0;
    Xyz_b562_01E00080 p0;
    Uv_b562_01E00080 uv1;
    Xyz_b562_01E00080 p1;
    u8 tail[0x20];
} Spr_b562_01E00080;

typedef struct {
    Rgbaq_b562_01E00080 c;
    f32 s, t;
    Xyz_b562_01E00080 p;
} Tv_b562_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b562_01E00080 v[4];
    u8 tail[0x20];
} Tex_b562_01E00080;

typedef struct {
    f32 s, t;
} St_b562_01E00080;

typedef struct {
    St_b562_01E00080 q[8];
} Quad_b562_01E00080;

typedef struct {
    Vec4f a;
    Vec4f mid;
    Vec4f b;
} Ring_b562_01E00080;

typedef struct {
    Vec4f a;
    Vec4f b;
} Seg_b562_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    s32 ang;
    f32 r;
    f32 rad;
    u8 pad24[0xC];
    Vec4f pos;
} Fan_b562_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 ang;
    u8 padC[4];
    Vec4f pos;
} Spin_b562_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 ang;
    s32 ang2[4];
    u8 pad1C[4];
    Vec4f pos[4];
} Bolt_b562_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    u8 pad1C[4];
    Vec4f tgt;
    s32 bone;
    u8 pad34[0xC];
    Vec4f bp;
    Vec4f prev;
    s32 cnt;
    u8 pad64[0xC];
    Fan_b562_01E00080 fan[32];
    s32 nsp;
    u8 pad874[0xC];
    Ring_b562_01E00080 ring[17];
    Quad_b562_01E00080 st[16];
    Spin_b562_01E00080 spin[16];
    Ring_b562_01E00080 ring2[9];
    Quad_b562_01E00080 st2[8];
    Bolt_b562_01E00080 bolt[16];
    u8 on2;
    u8 pad1B61[3];
    s32 t2;
    u8 pad1B68[8];
    Vec4f dir[128];
    Seg_b562_01E00080 seg[9];
    u8 on3;
    u8 pad2491[3];
    s32 t3;
    u8 pad2498[8];
} Scene_b562_01E00080;

static s32 func_01E00080_b562(s32 arg0, s32 code) {
    Scene_b562_01E00080 *g = (Scene_b562_01E00080 *)arg0;
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
    extern f32 func_001A6C18(f32, f32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern u8 D_0030FF00[];
    extern u16 D_28BBF0[][4];
    extern f32 D_0028BC10[4][32][3];
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 q;
    s32 x;
    s32 ang;
    u8 alpha;
    f32 r;
    f32 s;
    f32 f;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Vec4f w;
    s32 rot[4];
    Spr_b562_01E00080 spr __attribute__((aligned(8)));
    Tex_b562_01E00080 pk __attribute__((aligned(8)));
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x24A0);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(4, 0xF);
        g->tex[2] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->bone = func_001F5560(g->unitA, 2, 1);
        g->cnt = 0;
        for (i = 0; i < 32; i++) {
            g->fan[i].on = 0;
        }
        g->nsp = 0;
        for (i = 0; i < 17; i++) {
            ang = (i << 16) >> 4;
            g->ring[i].mid.x = 30.0f * func_0020B550(ang);
            g->ring[i].mid.y = 0.0f;
            g->ring[i].mid.z = 30.0f * func_0020B480(ang);
            g->ring[i].mid.w = 1.0f;
            g->ring[i].a = g->ring[i].mid;
            g->ring[i].a.y = 1.0f;
            g->ring[i].b = g->ring[i].mid;
            g->ring[i].b.y = -1.0f;
        }
        for (i = 0; i < 16; i++) {
            g->st[i].q[0].s = 0.5f + 0.5f * (i % 4) / 4.0f;
            g->st[i].q[0].t = 0.5f;
            g->st[i].q[1].s = 0.5f + 0.5f * (i % 4 + 1) / 4.0f;
            g->st[i].q[1].t = g->st[i].q[0].t;
            g->st[i].q[2].s = g->st[i].q[0].s;
            g->st[i].q[2].t = 0.625f;
            g->st[i].q[3].s = g->st[i].q[1].s;
            g->st[i].q[3].t = g->st[i].q[2].t;
            g->st[i].q[4].s = g->st[i].q[0].s;
            g->st[i].q[4].t = 0.75f;
            g->st[i].q[5].s = g->st[i].q[1].s;
            g->st[i].q[5].t = g->st[i].q[4].t;
            g->st[i].q[6].s = g->st[i].q[4].s;
            g->st[i].q[6].t = g->st[i].q[2].t;
            g->st[i].q[7].s = g->st[i].q[5].s;
            g->st[i].q[7].t = g->st[i].q[6].t;
        }
        for (i = 0; i < 16; i++) {
            g->spin[i].on = 0;
        }
        for (i = 0; i < 9; i++) {
            ang = i * 0xAAAA >> 3;
            g->ring2[i].mid.x = 20.0f * func_0020B550(ang);
            g->ring2[i].mid.y = 0.0f;
            g->ring2[i].mid.z = 20.0f * func_0020B480(ang);
            g->ring2[i].mid.w = 1.0f;
            g->ring2[i].a = g->ring2[i].mid;
            g->ring2[i].a.y = 7.5f;
            g->ring2[i].b = g->ring2[i].mid;
            g->ring2[i].b.y = -7.5f;
        }
        for (i = 0; i < 8; i++) {
            g->st2[i].q[0].s = 0.5f + 0.5f * (i % 4) / 4.0f;
            g->st2[i].q[0].t = 0.5f;
            g->st2[i].q[1].s = 0.5f + 0.5f * (i % 4 + 1) / 4.0f;
            g->st2[i].q[1].t = g->st2[i].q[0].t;
            g->st2[i].q[2].s = g->st2[i].q[0].s;
            g->st2[i].q[2].t = 0.625f;
            g->st2[i].q[3].s = g->st2[i].q[1].s;
            g->st2[i].q[3].t = g->st2[i].q[2].t;
            g->st2[i].q[4].s = g->st2[i].q[0].s;
            g->st2[i].q[4].t = 0.75f;
            g->st2[i].q[5].s = g->st2[i].q[1].s;
            g->st2[i].q[5].t = g->st2[i].q[4].t;
            g->st2[i].q[6].s = g->st2[i].q[4].s;
            g->st2[i].q[6].t = g->st2[i].q[2].t;
            g->st2[i].q[7].s = g->st2[i].q[5].s;
            g->st2[i].q[7].t = g->st2[i].q[6].t;
        }
        for (i = 0; i < 16; i++) {
            g->bolt[i].on = 0;
        }
        g->on2 = 0;
        g->on3 = 0;
        for (j = 0; j < 9; j++) {
            ang = (j << 15) >> 3;
            g->seg[j].a.x = 0.0f;
            g->seg[j].a.y = 15.0f + 15.0f * func_0020B480(ang);
            g->seg[j].a.z = 15.0f * func_0020B550(ang);
            g->seg[j].a.w = 1.0f;
            g->seg[j].b = g->seg[j].a;
            g->seg[j].b.z += 15.0f;
        }
        return 0;
    }
    func_00205CA0(m3);
    g->prev = g->bp;
    func_001F5620(g->unitA, g->bone, &g->bp);
    if (g->t == 0) {
        g->prev = g->bp;
    }
    if (g->t > 0xA && g->t < 0x87) {
        n = g->t % 32;
        g->fan[n].on = 1;
        g->fan[n].t = 0;
        for (j = 0; j < 16; j++) {
            g->fan[n].c[j] = (n + (g->t + j)) % 4;
        }
        g->fan[n].ang = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        g->fan[n].r = 10.0f * g->cnt / 64.0f;
        g->fan[n].rad = 50.0f * g->cnt / 64.0f;
        g->fan[n].pos = g->bp;
        g->fan[n].pos.y += -5.0f;
    }
    g->cnt++;
    if (g->cnt > 64) {
        g->cnt = 64;
    }

    ((Spr_b562_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b562_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b562_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b562_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b562_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->fan[i].on == 0) {
            continue;
        }
        r = 0.2f * g->fan[i].r + 0.8f * g->fan[i].r * g->fan[i].t / 32.0f;
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
        alpha = (u32)(64.0f * func_0020B550((g->fan[i].t << 16) >> 5));
        spr.c.r = 0x80;
        spr.c.g = 0x80;
        spr.c.b = 0x80;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        f = g->fan[i].t / 32.0f;
        for (x = 0; x < 16; x++) {
            ang = g->fan[i].ang + (((x << 16) >> 4) + (g->fan[i].t * 0x5555 >> 5));
            ang &= 0xFFFF;
            v.x = g->fan[i].rad * func_0020B550(ang);
            v.y = 0.0f;
            v.z = g->fan[i].rad * func_0020B480(ang);
            v.w = 1.0f;
            func_00187B48(&v, &v, f);
            func_00187B00(&v, &v, &g->fan[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            ((Uv_b562_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->fan[i].c[x]][0];
            ((Uv_b562_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->fan[i].c[x]][2];
            ((Uv_b562_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->fan[i].c[x]][1];
            ((Uv_b562_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->fan[i].c[x]][3];
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->fan[i].t++;
        if (g->fan[i].t > 32) {
            g->fan[i].on = 0;
        }
    }

    if (g->t % 4 == 0 && g->t > 0x28 && g->t < 0x87) {
        n = g->nsp;
        g->spin[n].on = 1;
        g->spin[n].t = 0;
        g->spin[n].ang = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
        g->spin[n].pos = g->bp;
        g->spin[n].pos.y += 15.0f;
        g->nsp++;
        if (g->nsp >= 16) {
            g->nsp = 0;
        }
    }

    ((Tex_b562_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b562_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b562_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b562_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(0));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, ((u64)0x2FC << 32) | 0x813FC81A);
    for (i = 0; i < 16; i++) {
        if (g->spin[i].on == 0) {
            continue;
        }
        f = -24.0f * func_00100D50(g->spin[i].t, 64, 1);
        v.x = 0.0f;
        v.y = f;
        v.z = 0.0f;
        v.w = 1.0f;
        func_00187B00(&v, &v, &g->spin[i].pos);
        s = 0.2f + 0.8f * g->spin[i].t / 64.0f;
        w.x = s;
        w.y = 1.0f;
        w.z = s;
        w.w = 1.0f;
        g->spin[i].ang += 0x1555;
        g->spin[i].ang = (u16)g->spin[i].ang;
        rot[0] = 0;
        rot[1] = g->spin[i].ang;
        rot[2] = 0;
        rot[3] = 1;
        func_0020EB40(m);
        func_0020C940(m2, &w, rot, &v);
        func_0020BC00(m, m2);
        for (x = 0; x < 16; x++) {
            f = 64.0f * func_0020B550((g->spin[i].t << 15) >> 6);
            alpha = (u32)(f * func_0020B550((x << 15) >> 4));
            pk.v[0].c.r = 0x80;
            pk.v[0].c.g = 0x80;
            pk.v[0].c.b = 0x80;
            pk.v[0].c.a = 0;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c.r = 0x80;
            pk.v[2].c.g = 0x80;
            pk.v[2].c.b = 0x80;
            pk.v[2].c.a = alpha;
            pk.v[2].c.q = 1.0f;
            f = 64.0f * func_0020B550((g->spin[i].t << 15) >> 6);
            alpha = (u32)(f * func_0020B550(((x + 1) << 15) >> 4));
            pk.v[3].c.r = 0x80;
            pk.v[3].c.g = 0x80;
            pk.v[3].c.b = 0x80;
            pk.v[3].c.a = alpha;
            pk.v[3].c.q = 1.0f;
            pk.v[0].s = g->st[x].q[0].s;
            pk.v[0].t = g->st[x].q[0].t;
            pk.v[1].s = g->st[x].q[1].s;
            pk.v[1].t = g->st[x].q[1].t;
            pk.v[2].s = g->st[x].q[2].s;
            pk.v[2].t = g->st[x].q[2].t;
            pk.v[3].s = g->st[x].q[3].s;
            pk.v[3].t = g->st[x].q[3].t;
            if (func_00100BA0(&g->ring[x].a, &g->ring[x + 1].a, &g->ring[x].mid, &g->ring[x + 1].mid, m, &pk,
                              &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
            pk.v[0].s = g->st[x].q[4].s;
            pk.v[0].t = g->st[x].q[4].t;
            pk.v[1].s = g->st[x].q[5].s;
            pk.v[1].t = g->st[x].q[5].t;
            pk.v[2].s = g->st[x].q[6].s;
            pk.v[2].t = g->st[x].q[6].t;
            pk.v[3].s = g->st[x].q[7].s;
            pk.v[3].t = g->st[x].q[7].t;
            if (func_00100BA0(&g->ring[x].b, &g->ring[x + 1].b, &g->ring[x].mid, &g->ring[x + 1].mid, m, &pk,
                              &depth) == 1) {
                func_002075F0(&pk, ot, (u32)depth);
            }
        }
        g->spin[i].t++;
        if (g->spin[i].t > 64) {
            g->spin[i].on = 0;
        }
    }

    if (g->t > 0x91 && g->t < 0x9A) {
        n = g->t % 16;
        (void)n;
        g->bolt[n].on = 1;
        g->bolt[n].t = 0;
        g->bolt[n].ang = (s32)(65536.0f * (func_001A6C18(g->bp.z - g->prev.z, g->bp.y - g->prev.y) / 6.2831855f));
        for (j = 0; j < 4; j++) {
            g->bolt[n].ang2[j] = ((j << 16) >> 2) + ((func_0019A5C8() >> 23) % 256 << 16 >> 8);
            g->bolt[n].ang2[j] = (u16)g->bolt[n].ang2[j];
            g->bolt[n].pos[j] = g->bp;
            k = g->t % 32;
            g->bolt[n].pos[j].x += 0.1f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][0];
            g->bolt[n].pos[j].y += 0.1f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][1];
            g->bolt[n].pos[j].z += 4.0f * j * g->obj;
        }
    }

    ((Tex_b562_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b562_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b562_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b562_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[1], 1);
    func_00208CB0(&pk, ((u64)0x2FC << 32) | 0x813FC81A);
    for (i = 0; i < 16; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        s = 0.5f + 0.5f * g->bolt[i].t / 16.0f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (k = 0; k < 4; k++) {
            func_0020EB40(m);
            func_0020C940(m2, NULL, NULL, &g->bolt[i].pos[k]);
            func_00100E00(m2, g->bolt[i].ang, 0);
            func_00100E00(m2, g->bolt[i].ang2[k], 1);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (q = 0; q < 8; q++) {
                f = 64.0f * func_0020B480((g->bolt[i].t << 14) >> 4);
                alpha = (u32)(f * func_0020B550((q << 15) >> 3));
                pk.v[0].c.r = 0x80;
                pk.v[0].c.g = 0x80;
                pk.v[0].c.b = 0x80;
                pk.v[0].c.a = 0;
                pk.v[0].c.q = 1.0f;
                pk.v[1].c = pk.v[0].c;
                pk.v[2].c.r = 0x80;
                pk.v[2].c.g = 0x80;
                pk.v[2].c.b = 0x80;
                pk.v[2].c.a = alpha;
                pk.v[2].c.q = 1.0f;
                f = 64.0f * func_0020B480((g->bolt[i].t << 14) >> 4);
                alpha = (u32)(f * func_0020B550(((q + 1) << 15) >> 3));
                pk.v[3].c.r = 0x80;
                pk.v[3].c.g = 0x80;
                pk.v[3].c.b = 0x80;
                pk.v[3].c.a = alpha;
                pk.v[3].c.q = 1.0f;
                pk.v[0].s = g->st2[q].q[0].s;
                pk.v[0].t = g->st2[q].q[0].t;
                pk.v[1].s = g->st2[q].q[1].s;
                pk.v[1].t = g->st2[q].q[1].t;
                pk.v[2].s = g->st2[q].q[2].s;
                pk.v[2].t = g->st2[q].q[2].t;
                pk.v[3].s = g->st2[q].q[3].s;
                pk.v[3].t = g->st2[q].q[3].t;
                if (func_00100BA0(&g->ring2[q].a, &g->ring2[q + 1].a, &g->ring2[q].mid, &g->ring2[q + 1].mid, m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
                pk.v[0].s = g->st2[q].q[4].s;
                pk.v[0].t = g->st2[q].q[4].t;
                pk.v[1].s = g->st2[q].q[5].s;
                pk.v[1].t = g->st2[q].q[5].t;
                pk.v[2].s = g->st2[q].q[6].s;
                pk.v[2].t = g->st2[q].q[6].t;
                pk.v[3].s = g->st2[q].q[7].s;
                pk.v[3].t = g->st2[q].q[7].t;
                if (func_00100BA0(&g->ring2[q].b, &g->ring2[q + 1].b, &g->ring2[q].mid, &g->ring2[q + 1].mid, m,
                                  &pk, &depth) == 1) {
                    func_002075F0(&pk, ot, (u32)depth);
                }
            }
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 16) {
            g->bolt[i].on = 0;
        }
    }

    if (g->t == 0x9B) {
        g->on2 = 1;
        g->t2 = 0;
        for (i = 0; i < 128; i++) {
            k = i;
            k %= 32;
            g->dir[i].x = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][0];
            g->dir[i].y = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][1];
            g->dir[i].z = 2.0f * D_0028BC10[(func_0019A5C8() >> 23) % 4][k][2];
            g->dir[i].w = 1.0f;
        }
    }

    ((Spr_b562_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b562_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b562_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b562_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b562_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020C940(m2, NULL, NULL, &g->tgt);
    func_0020BC00(m, m2);
    if (g->on2 == 1) {
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
        x = 0;
        ((Uv_b562_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b562_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b562_01E00080 *)(s32)&spr.uv1)->u = 0x400;
        ((Uv_b562_01E00080 *)(s32)&spr.uv1)->v = 0x400;
        spr.c.r = 0x60;
        spr.c.g = 0x80;
        spr.c.b = 0xFF;
        spr.c.a = 0;
        spr.c.q = 1.0f;
        f = 255.0f * (1.0f - func_00100D50(g->t2, 24, 1));
        for (i = 0; i < 128; i++) {
            for (k = 0; k < 8; k++) {
                spr.c.a = (u32)(f * func_0020B550(((k + 1) << 14) >> 3));
                func_00187B48(&v, &g->dir[i], (g->t2 + 0.4f * k) / 24.0f);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->t2++;
        if (g->t2 > 24) {
            g->on2 = 0;
        }
    }
    if (g->t == 0x9B) {
        g->on3 = 1;
        g->t3 = 0;
    }

    ((Tex_b562_01E00080 *)(s32)&pk)->flags = 0x34;
    ((Tex_b562_01E00080 *)(s32)&pk)->size = 0xC;
    ((Tex_b562_01E00080 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b562_01E00080 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, g->tex[0], 1);
    func_00208CB0(&pk, 5);
    if (g->on3 == 1) {
        s = 0.2f + 0.8f * func_00100D50(g->t3, 48, 1);
        v.x = 1.0f;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (k = 0; k < 4; k++) {
            alpha = (u32)((k + 1) * (255.0f * (1.0f - func_00100D50(g->t3, 48, 1))) / 4.0f);
            pk.v[0].c.r = 0x40;
            pk.v[0].c.g = 0x40;
            pk.v[0].c.b = 0xFF;
            pk.v[0].c.a = alpha;
            pk.v[0].c.q = 1.0f;
            pk.v[1].c = pk.v[0].c;
            pk.v[2].c = pk.v[0].c;
            pk.v[3].c = pk.v[0].c;
            for (i = 0; i < 8; i++) {
                func_0020EB40(m);
                func_0020C940(m2, NULL, NULL, &g->tgt);
                func_00100E00(m2, g->obj << 13, 2);
                func_00100E00(m2, (i << 16) / 8 + (g->t * 0x16C + (k * 0xE38 >> 2)), 0);
                func_0020CB20(m2, &v);
                func_0020BC00(m, m2);
                for (j = 0; j < 8; j++) {
                    pk.v[0].s = 0.0f;
                    pk.v[0].t = 0.5f * j / 8.0f;
                    pk.v[1].s = 0.5f;
                    pk.v[1].t = pk.v[0].t;
                    pk.v[2].s = pk.v[0].s;
                    pk.v[2].t = 0.5f * (j + 1) / 8.0f;
                    pk.v[3].s = pk.v[1].s;
                    pk.v[3].t = pk.v[2].t;
                    if (func_00100BA0(&g->seg[j].a, &g->seg[j].b, &g->seg[j + 1].a, &g->seg[j + 1].b, m, &pk,
                                      &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        g->t3++;
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x91) {
        ret = 1;
    } else if (g->t == 0x9B) {
        ret = 2;
    }
    g->t++;
    if (g->t > 0xCB) {
        ret = 8;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b562", func_01E01E00_b562);
