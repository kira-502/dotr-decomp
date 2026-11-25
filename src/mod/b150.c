#include "common.h"

/* shape b150:01E00080 (b150), 1298 insns, 1 copy: b150 scene manager (b512:01E00080's family, written from the asm):
   code >= 0 clears the scene, takes both units, two textures and two joints; else lays an 8-point path between the
   joints, starts a smoke burst along it on frames 1..209, side streams on 134..180 that drop puffs, a flash and a
   256-spark shower at 197; draws bursts, puffs and sparks as sprites; returns 1 / 6 / 2 / 8 at frames 123 / 134..204
   / 205 / 262 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b150_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b150_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b150_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b150_01E00080 c;
    Uv_b150_01E00080 uv0;
    Xyz_b150_01E00080 p0;
    Uv_b150_01E00080 uv1;
    Xyz_b150_01E00080 p1;
    u8 tail[0x20];
} Spr_b150_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b150_01E00080 c;
    Xyz_b150_01E00080 p0;
    Xyz_b150_01E00080 p1;
    u8 tail[8];
} Rect_b150_01E00080;

typedef struct {
    u16 u0, u1, v0, v1;
} Cell_b150_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8][4];
    u8 pad28[8];
    Vec4f p[8];
    Vec4f v[8][4];
} Burst_b150_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 n;
    u8 pad9[3];
} Stream_b150_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[16];
    u8 pad18[8];
    Vec4f p;
    Vec4f v[16];
} Puff_b150_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
} Flash_b150_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[256];
    u8 pad108[8];
    Vec4f v[256];
} Shower_b150_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    void *tex[2];
    u8 pad18[8];
    Vec4f tgt;
    s32 m[2];
    u8 pad38[8];
    Vec4f pos[2];
    Vec4f path[8];
    Burst_b150_01E00080 b[16];
    Stream_b150_01E00080 st[8];
    Puff_b150_01E00080 puff[8][16];
    Flash_b150_01E00080 flash;
    Shower_b150_01E00080 sh;
} Scene_b150_01E00080;

static s32 func_01E00080_b150(s32 arg0, s32 code) {
    Scene_b150_01E00080 *g = (Scene_b150_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern void *func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_00205CA0(void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00101080(void *, f32);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00101050(s32, s32, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_001A6970(f32);
    extern f32 func_00100FF0(f32, f32, f32);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001878E0(void *, void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern u8 D_0030FF00[];
    extern Cell_b150_01E00080 D_28BBF0[];
    s32 ret;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 c;
    s32 x;
    s32 y;
    u8 alpha;
    f32 s;
    f32 h;
    f32 r;
    f32 dy;
    f32 depth;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f p0;
    Vec4f p1;
    Vec4f v;
    Spr_b150_01E00080 spr __attribute__((aligned(8)));
    Rect_b150_01E00080 rc __attribute__((aligned(8)));
    s32 ot;
    s32 l;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xD560);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        func_001F5F90(g->unitB, &g->tgt);
        g->m[0] = func_001F5560(g->unitA, 0x1B, 1);
        i = func_001F5560(g->unitA, 0x1C, 0);
        g->m[1] = i;
        for (k = 0; k < 16; k++) {
            g->b[k].on = 0;
        }
        for (i = 0; i < 8; i++) {
            g->st[i].on = 0;
            g->st[i].n = 0;
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 16; j++) {
                g->puff[i][j].on = 0;
            }
        }
        g->flash.on = 0;
        g->sh.on = 0;
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->m[i], &g->pos[i]);
    }
    func_00187B18(&v, &g->pos[1], &g->pos[0]);
    for (i = 0; i < 8; i++) {
        func_00187B48(&g->path[i], &v, 2.0f * i / 7.0f);
        func_00187B00(&g->path[i], &g->path[i], &g->pos[0]);
    }
    if (g->t > 0 && g->t < 0xD2) {
        n = g->t % 16;
        (void)n;
        g->b[n].on = 1;
        g->b[n].t = 0;
        for (j = 0; j < 8; j++) {
            g->b[n].p[j] = g->path[j];
            for (k = 0; k < 4; k++) {
                g->b[n].c[j][k] = (func_0019A5C8() >> 23) % 4;
                func_00101080(&g->b[n].v[j][k], 0.1f);
            }
        }
    }

    ((Spr_b150_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b150_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b150_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b150_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b150_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    s = (f32)func_00101050(g->t, 0, 0x40) * (f32)func_00101050(0xD2 - g->t, 0, 0x40) / 4096.0f;
    for (i = 0; i < 16; i++) {
        if (g->b[i].on == 0) {
            continue;
        }
        alpha = (u32)(s * (128.0f * func_0020B480((g->b[i].t << 14) >> 4)));
        spr.c.r = 0x80;
        spr.c.g = 0x18;
        spr.c.b = 0x14;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        r = 2.5f * (0.5f + 0.5f * (16 - g->b[i].t) / 16.0f);
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
        dy = g->b[i].t / 16.0f;
        h = 0.9f + 0.1f * g->b[i].t / 16.0f;
        for (j = 0; j < 8; j++) {
            for (l = 0; l < 4; l++) {
                ((Uv_b150_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->b[i].c[j][l]].u0;
                ((Uv_b150_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->b[i].c[j][l]].v0;
                ((Uv_b150_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->b[i].c[j][l]].u1;
                ((Uv_b150_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->b[i].c[j][l]].v1;
                v.x = g->b[i].v[j][l].x * h;
                v.y = -1.0f + 15.0f * dy + g->b[i].v[j][l].y;
                v.z = g->b[i].v[j][l].z * h;
                func_00187B00(&v, &v, &g->b[i].p[j]);
                func_00187B00(&p0, &cn[0], &v);
                func_00187B00(&p1, &cn[1], (void *)&v);
                if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->b[i].t++;
        if (g->b[i].t > 16) {
            g->b[i].on = 0;
        }
    }

    if (g->t > 0x85 && g->t < 0xB5) {
        n = g->t % 8;
        (void)n;
        g->st[n].on = 1;
        g->st[n].t = 0;
    }
    for (i = 0; i < 8; i++) {
        if (g->st[i].on == 0) {
            continue;
        }
        r = (-45.0f + -95.0f * g->st[i].t / 8.0f) * g->obj;
        v.x = 0.0f;
        v.y = 20.0f;
        v.z = r;
        v.w = 1.0f;
        n = g->st[i].n;
        g->puff[i][n].on = 1;
        g->puff[i][n].t = 0;
        g->puff[i][n].p = v;
        for (k = 0; k < 16; k++) {
            g->puff[i][n].c[k] = (func_0019A5C8() >> 23) % 4;
            func_00101080(&g->puff[i][n].v[k], 1.0f);
            g->puff[i][n].v[k].y = func_001A6970(g->puff[i][n].v[k].y);
        }
        g->st[i].n++;
        if (g->st[i].n >= 16) {
            g->st[i].n = 0;
        }
        g->st[i].t++;
        if (g->st[i].t > 8) {
            g->st[i].on = 0;
        }
    }

    ((Spr_b150_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b150_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b150_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b150_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b150_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_002086D0(&spr, func_00208D00(1));
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) {
            if (g->puff[i][j].on == 0) {
                continue;
            }
            alpha = (u32)(128.0f * func_0020B550((g->puff[i][j].t << 15) >> 4));
            spr.c.r = 0x80;
            spr.c.g = 0x1E;
            spr.c.b = 0x1A;
            spr.c.a = alpha;
            spr.c.q = 1.0f;
            r = 7.0f * (0.5f + 0.5f * (16 - g->puff[i][j].t) / 16.0f);
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
            dy = g->puff[i][j].t / 16.0f;
            h = 0.9f + 0.1f * g->puff[i][j].t / 16.0f;
            dy = 50.0f * dy;
            for (k = 0; k < 16; k++) {
                ((Uv_b150_01E00080 *)(s32)&spr.uv0)->u = D_28BBF0[g->puff[i][j].c[k]].u0;
                ((Uv_b150_01E00080 *)(s32)&spr.uv0)->v = D_28BBF0[g->puff[i][j].c[k]].v0;
                ((Uv_b150_01E00080 *)(s32)&spr.uv1)->u = D_28BBF0[g->puff[i][j].c[k]].u1;
                ((Uv_b150_01E00080 *)(s32)&spr.uv1)->v = D_28BBF0[g->puff[i][j].c[k]].v1;
                v.x = g->puff[i][j].v[k].x * h;
                v.y = dy + g->puff[i][j].v[k].y;
                v.z = g->puff[i][j].v[k].z * h;
                func_00187B00(&v, &v, &g->puff[i][j].p);
                func_00187B00(&p0, &cn[0], &v);
                func_00187B00(&p1, &cn[1], (void *)&v);
                if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
            g->puff[i][j].t++;
            if (g->puff[i][j].t > 16) {
                g->puff[i][j].on = 0;
            }
        }
    }

    if (g->t == 0xC5) {
        g->flash.on = 1;
        g->flash.t = 0;
        for (i = 0; i < 8; i++) {
            g->st[i].on = 0;
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 16; j++) {
                g->puff[i][j].on = 0;
            }
        }
    }
    if (g->flash.on == 1) {
        ((Rect_b150_01E00080 *)(s32)&rc)->flags = 6;
        ((Rect_b150_01E00080 *)(s32)&rc)->size = 3;
        ((Rect_b150_01E00080 *)(s32)&rc)->regs = 0x441;
        ((Rect_b150_01E00080 *)(s32)&rc)->pad4 = 0;
        func_002086D0(&rc, func_00208D00(1));
        alpha = (u32)(200.0f * (1.0f - func_00100D50(g->flash.t, 0x40, 1)));
        rc.c.r = 0xFF;
        rc.c.g = 0xA4;
        rc.c.b = 0xA4;
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
        g->flash.t++;
        if (g->flash.t > 0x40) {
            g->flash.on = 0;
        }
    }
    if (g->t == 0xC5) {
        g->sh.on = 1;
        g->sh.t = 0;
        for (i = 0; i < 256; i++) {
            g->sh.c[i] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->sh.v[i], 5.0f);
        }
    }
    if (g->sh.on == 1) {
        ((Spr_b150_01E00080 *)(s32)&spr)->flags = 0x26;
        ((Spr_b150_01E00080 *)(s32)&spr)->size = 5;
        ((Spr_b150_01E00080 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b150_01E00080 *)(s32)&spr)->pad4 = 0;
        ((Spr_b150_01E00080 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_002086D0(&spr, func_00208D00(1));
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 2.5f;
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
        h = func_00100D50(g->sh.t, 0x40, 1);
        s = 255.0f * func_00100FF0(g->sh.t, 64.0f, 32.0f);
        for (i = 0; i < 256; i++) {
            c = g->sh.c[i];
            x = c % 4 * 32;
            y = (c >> 2) * 32;
            ((Uv_b150_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b150_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b150_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b150_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            for (k = 0; k < 8; k++) {
                alpha = (u32)(s * (k + 1) / 8.0f);
                (void)alpha;
                spr.c.r = 0xFF;
                spr.c.g = 0x40;
                spr.c.b = 0x30;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->sh.v[i], h + 0.007f * k);
                func_00187B00(&v, &v, &g->tgt);
                func_00187B00(&p0, &cn[0], &v);
                func_00187B00(&p1, &cn[1], (void *)&v);
                if (func_00205630((s32)&p0, (s32)D_0030FF00, (s32)m, (s32)&spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->sh.t++;
        if (g->sh.t > 0x40) {
            g->sh.on = 0;
        }
    }

    if (g->t == 0x7B) {
        ret = 1;
    } else {
        if (g->t > 0x85 && g->t < 0xCD) {
            ret = 6;
        }
        if (g->t == 0xCD) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x105) {
        ret = 8;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b150", func_01E01500_b150);
