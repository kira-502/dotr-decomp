#include "common.h"

/* shape b587:01E00080 (b587), 2220 insns, 1 copy: b587 scene manager (b141:01E00080's family, written from the asm):
   setup clears the 0x8180 scene, takes both units, three textures, joints 0x59 / 0x69 and the target; else at 0x87 +
   10n (n < 4) fires a bolt from a joint toward the target with a 16-mote ring at the joint, each live bolt leaves
   4-sprite spark trails in two 4x16 / 4x32 slot grids and at frame 0x44 seeds a 2x64-sprite burst, on 1..0x57 32-slot
   4x2 puffs swirl round both joints, and from 0x112 the target fades to a tint; returns 1 / 6 / 2 / 8 at 0xC1 /
   0xCC..0x168 / 0x169 / >0x16A */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b587_01E00080;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b587_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b587_01E00080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b587_01E00080 c;
    Uv_b587_01E00080 uv0;
    Xyz_b587_01E00080 p0;
    Uv_b587_01E00080 uv1;
    Xyz_b587_01E00080 p1;
    u8 tail[0x20];
} Spr_b587_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 a;
    s32 b;
    Vec4f pos[1];
    Vec4f v[1];
} Bolt_b587_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4];
    u8 padC[4];
    Vec4f pos;
    Vec4f v[4];
} Spark_b587_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos[1];
    u8 c[1][16];
    Vec4f v[1][16];
} Ring_b587_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[64];
    u8 pad48[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f v2[64];
} Big_b587_01E00080;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[4][2];
    Vec4f v[4][2];
} Puff_b587_01E00080;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[3];
    s32 jn[2];
    u8 pad24[0xC];
    Vec4f jp[2];
    Vec4f tgt;
    s32 cnt;
    s32 slot;
    u8 pad68[8];
    Bolt_b587_01E00080 bolt[4];
    Spark_b587_01E00080 sa[4][1][16];
    Spark_b587_01E00080 sb[4][1][32];
    s32 slot2;
    u8 pad4934[0xC];
    Ring_b587_01E00080 ring[4];
    Big_b587_01E00080 big[4];
    Puff_b587_01E00080 puff[32];
} Scene_b587_01E00080;

static s32 func_01E00080_b587(s32 arg0, s32 code) {
    Scene_b587_01E00080 *g = (Scene_b587_01E00080 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6590(s32, s32, void *);
    extern s32 func_001F6EF0(void);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
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
    s32 ret;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 q;
    s32 n;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    u8 alpha;
    f32 r;
    f32 s;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[2];
    Vec4f out[2];
    Vec4f v;
    Spr_b587_01E00080 spr __attribute__((aligned(8)));
    f32 depth;
    u8 col[4];

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x8180);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->jn[0] = func_001F5560(g->unitA, 0x59, 1);
        g->jn[1] = func_001F5560(g->unitA, 0x69, 0);
        func_001F5F90(g->unitB, &g->tgt);
        g->cnt = 0;
        g->slot = 0;
        for (i = 0; i < 4; i++) {
            g->bolt[i].on = 0;
            g->bolt[i].a = 0;
            g->bolt[i].b = 0;
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 16; k++) {
                    g->sa[i][j][k].on = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 1; j++) {
                for (k = 0; k < 32; k++) {
                    g->sb[i][j][k].on = 0;
                }
            }
        }
        g->slot2 = 0;
        for (i = 0; i < 4; i++) {
            g->ring[i].on = 0;
        }
        for (i = 0; i < 4; i++) {
            g->big[i].on = 0;
        }
        for (i = 0; i < 32; i++) {
            g->puff[i].on = 0;
        }
        func_001F6590(g->unitB, 2, 0);
        return 0;
    }
    func_00205CA0(m3);
    for (i = 0; i < 2; i++) {
        func_001F5620(g->unitA, g->jn[i], &g->jp[i]);
    }

    if (g->cnt < 4 && g->t == g->cnt * 10 + 0x87) {
        n = g->slot;
        g->bolt[n].on = 1;
        g->bolt[n].t = 0;
        k = g->slot2;
        (void)k;
        g->ring[k].on = 1;
        g->ring[k].t = 0;
        for (l = 0; l < 1; l++) {
            g->bolt[n].pos[l] = g->jp[n % 2];
            g->ring[k].pos[l] = g->jp[n % 2];
            func_00101080(&v, 1.0f);
            func_00187B00(&v, &v, &g->tgt);
            v.x = g->bolt[n].pos[l].x;
            func_00187B18(&g->bolt[n].v[l], &v, &g->bolt[n].pos[l]);
            for (i = 0; i < 16; i++) {
                g->ring[k].c[l][i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->ring[k].v[l][i], 0.3f);
            }
        }
        g->cnt++;
        g->slot++;
        if (g->slot >= 4) {
            g->slot = 0;
        }
        g->slot2++;
        if (g->slot2 >= 4) {
            g->slot2 = 0;
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = 0x400;
    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = 0;
    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = 0x600;
    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = 0x200;
    r = 4.0f;
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
    for (i = 0; i < 4; i++) {
        if (g->bolt[i].on == 0) {
            continue;
        }
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0x20;
        spr.c.a = 0x80;
        spr.c.q = 1.0f;
        s = g->bolt[i].t / 68.0f;
        a = g->bolt[i].a;
        g->bolt[i].a++;
        if (g->bolt[i].a >= 16) {
            g->bolt[i].a = 0;
        }
        b = g->bolt[i].b;
        g->bolt[i].b++;
        if (g->bolt[i].b >= 32) {
            g->bolt[i].b = 0;
        }
        for (j = 0; j < 1; j++) {
            func_00187B48(&v, &g->bolt[i].v[j], s);
            func_00187B00(&v, &v, &g->bolt[i].pos[j]);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
            g->sa[i][j][a].on = 1;
            g->sa[i][j][a].t = 0;
            g->sa[i][j][a].pos = v;
            for (k = 0; k < 4; k++) {
                g->sa[i][j][a].c[k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->sa[i][j][a].v[k], 0.2f);
            }
            g->sb[i][j][b].on = 1;
            g->sb[i][j][b].t = 0;
            g->sb[i][j][b].pos = v;
            for (k = 0; k < 4; k++) {
                func_00101080(&g->sb[i][j][b].v[k], 0.3f);
            }
            if (g->bolt[i].t == 0x44) {
                g->big[i].on = 1;
                g->big[i].t = 0;
                g->big[i].pos = v;
                for (k = 0; k < 64; k++) {
                    g->big[i].c[k] = (func_0019A5C8() >> 23) % 8;
                    func_00101080(&g->big[i].v[k], 2.0f);
                }
                for (k = 0; k < 64; k++) {
                    func_00101080(&g->big[i].v2[k], 2.0f);
                }
            }
        }
        g->bolt[i].t++;
        if (g->bolt[i].t > 0x44) {
            g->bolt[i].on = 0;
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 1; j++) {
            for (l = 0; l < 16; l++) {
                if (g->sa[i][j][l].on == 0) {
                    continue;
                }
                r = 0.7f + 0.3f * g->sa[i][j][l].t / 16.0f;
                r = 4.5f * r;
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
                alpha = (16 - g->sa[i][j][l].t) * 128 >> 4;
                spr.c.r = 0xC8;
                spr.c.g = 0xFF;
                spr.c.b = 0x20;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.4f + 0.6f * func_00100D50(g->sa[i][j][l].t, 16, 1);
                for (q = 0; q < 4; q++) {
                    x = g->sa[i][j][l].c[q] % 4 * 32;
                    y = (g->sa[i][j][l].c[q] >> 2) * 32;
                    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                    func_00187B48(&v, &g->sa[i][j][l].v[q], s);
                    func_00187B00(&v, &v, &g->sa[i][j][l].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->sa[i][j][l].t++;
                if (g->sa[i][j][l].t > 16) {
                    g->sa[i][j][l].on = 0;
                }
            }
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[2], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    x = 0;
    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x;
    ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = x;
    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = 0x800;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 1; j++) {
            for (l = 0; l < 32; l++) {
                if (g->sb[i][j][l].on == 0) {
                    continue;
                }
                r = 8.5f * (0.5f + 0.5f * g->sb[i][j][l].t / 32.0f);
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
                alpha = (32 - g->sb[i][j][l].t) * 96 >> 5;
                spr.c.r = 0xC8;
                spr.c.g = 0xFF;
                spr.c.b = 0x20;
                spr.c.a = alpha;
                spr.c.q = 1.0f;
                s = 0.2f + 0.8f * func_00100D50(g->sb[i][j][l].t, 32, 1);
                for (k = 0; k < 4; k++) {
                    func_00187B48(&v, &g->sb[i][j][l].v[k], s);
                    func_00187B00(&v, &v, &g->sb[i][j][l].pos);
                    func_00187B00(&out[0], &cn[0], &v);
                    func_00187B00(&out[1], &cn[1], (void *)&v);
                    if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                        func_002075F0(&spr, ot, (u32)depth);
                    }
                }
                g->sb[i][j][l].t++;
                if (g->sb[i][j][l].t > 32) {
                    g->sb[i][j][l].on = 0;
                }
            }
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->ring[i].on == 0) {
            continue;
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = 0x200;
        r = 5.0f;
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
        alpha = (u32)(128.0f * (1.0f - func_00100D50(g->ring[i].t, 32, 1)));
        spr.c.r = 0xC8;
        spr.c.g = 0xFF;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (j = 0; j < 1; j++) {
            v = g->ring[i].pos[j];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        func_002086D0(&spr, func_00208D00(0));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 5.0f * (0.5f + 0.5f * g->ring[i].t / 32.0f);
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
        alpha = (32 - g->ring[i].t) * 128 >> 5;
        spr.c.r = 0xC8;
        spr.c.g = 0xFF;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(g->ring[i].t, 32, 1);
        for (j = 0; j < 1; j++) {
            for (k = 0; k < 16; k++) {
                x = g->ring[i].c[j][k] % 4 * 32;
                y = (g->ring[i].c[j][k] >> 2) * 32;
                ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                func_00187B48(&v, &g->ring[i].v[j][k], s);
                func_00187B00(&v, &v, &g->ring[i].pos[j]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->ring[i].t++;
        if (g->ring[i].t > 32) {
            g->ring[i].on = 0;
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (g->big[i].on == 0) {
            continue;
        }
        func_002086D0(&spr, func_00208D00(0));
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        r = 14.0f * (0.4f + 0.6f * g->big[i].t / 128.0f);
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
        alpha = (u32)(116.0f * func_0020B480((g->big[i].t << 14) >> 7));
        spr.c.r = 0xC8;
        spr.c.g = 0xFF;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->big[i].t, 128, 1);
        for (k = 0; k < 64; k++) {
            x = g->big[i].c[k] % 4 * 32;
            y = (g->big[i].c[k] >> 2) * 32;
            ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->big[i].v[k], s);
            func_00187B00(&v, &v, &g->big[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        func_002086D0(&spr, func_00208D00(1));
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        r = 8.0f * (0.5f + 0.5f * g->big[i].t / 128.0f);
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
        alpha = (u32)(128.0f * func_0020B480((g->big[i].t << 14) >> 7));
        spr.c.r = 0xC8;
        spr.c.g = 0xFF;
        spr.c.b = 0x20;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        x = 0;
        ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x;
        ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = x;
        ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = 0x800;
        s = 0.1f + 0.9f * func_00100D50(g->big[i].t, 128, 1);
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->big[i].v2[k], s);
            func_00187B00(&v, &v, &g->big[i].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->big[i].t++;
        if (g->big[i].t > 128) {
            g->big[i].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x58) {
        n = g->t % 32;
        (void)n;
        g->puff[n].on = 1;
        g->puff[n].t = 0;
        for (i = 0; i < 4; i++) {
            for (k = 0; k < 2; k++) {
                g->puff[n].c[i][k] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->puff[n].v[i][k], 1.0f);
                func_00187B00(&g->puff[n].v[i][k], &g->puff[n].v[i][k], &g->jp[k]);
            }
        }
    }

    ((Spr_b587_01E00080 *)(s32)&spr)->flags = 0x26;
    ((Spr_b587_01E00080 *)(s32)&spr)->size = 5;
    ((Spr_b587_01E00080 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b587_01E00080 *)(s32)&spr)->pad4 = 0;
    ((Spr_b587_01E00080 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(0));
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (i = 0; i < 32; i++) {
        if (g->puff[i].on == 0) {
            continue;
        }
        r = 8.0f * (0.2f + 0.8f * (32 - g->puff[i].t) / 32.0f);
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
        alpha = (u32)(64.0f * func_0020B550((g->puff[i].t << 14) >> 5));
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        s = func_00100D50(32 - g->puff[i].t, 32, 1);
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 2; k++) {
                func_00187B18(&v, &g->puff[i].v[j][k], &g->jp[k]);
                func_00187B48(&v, &v, s);
                func_00187B00(&v, &v, &g->jp[k]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->puff[i].c[j][k] % 4 * 32;
                y = (g->puff[i].c[j][k] >> 2) * 32;
                ((Uv_b587_01E00080 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b587_01E00080 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->puff[i].t++;
        if (g->puff[i].t > 32) {
            g->puff[i].on = 0;
        }
    }

    if (func_001F6EF0() == 1 && g->t > 0x111) {
        x = func_00101050(g->t - 0x111, 0, 64) * 64 >> 6;
        col[2] = 0x64;
        col[1] = 0x20;
        col[0] = 0xFF;
        col[3] = x;
        func_001F6590(g->unitB, 1, col);
    }

    if (g->t == 0xC1) {
        ret = 1;
    } else {
        if (g->t > 0xCB && g->t <= 0x168) {
            ret = 6;
        }
        if (g->t == 0x169) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0x16A) {
        ret = 8;
    }
    return ret;
}
