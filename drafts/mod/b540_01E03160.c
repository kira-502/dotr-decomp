#include "common.h"

/* shape b540:01E03160 (b540), 616 insns, 1 copy: b540 scene manager: code >= 0 sets up the disc, the 8-point sword
   trail between two joints, the sprite and two particle sprays (256 spinning, 128 rising); else aims cameras at joint
   1, steps the trail (reset at 292), flashes 220..253, fades the screen, draws disc/sprite from 294, the sprays
   (b540:01E03B00) and the trail in 293..302; returns 2/1/6/8 by tick */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b540_01E03160;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    s16 max;
    s16 len;
    Vec4f a[8];
    Vec4f b[8];
    s16 u, v, w, h;
    u8 pad188[8];
    Vec4f *p1;
    Vec4f *p2;
    u8 pad198[8];
} Trail_b540_01E03160;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b540_01E03160;

typedef struct {
    s32 a, b, c, d;
} Rot_b540_01E03160;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 uv[8];
    Pt_b540_01E03160 *pts;
    Rot_b540_01E03160 *rots;
    s32 x48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b540_01E03160;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rot_b540_01E03160 r[64];
} Spr_b540_01E03160;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b540_01E03160;

typedef struct {
    Crd_b540_01E03160 m0;
    Trail_b540_01E03160 trail;
    Crd_b540_01E03160 m1;
    Crd_b540_01E03160 m2;
    Emit_b540_01E03160 emit1;
    Pt_b540_01E03160 pts1[0x100];
    Rot_b540_01E03160 rots1[0x100];
    Crd_b540_01E03160 m3;
    Emit_b540_01E03160 emit2;
    Pt_b540_01E03160 pts2[0x80];
    Rot_b540_01E03160 rots2[0x80];
    Crd_b540_01E03160 m4;
    Spr_b540_01E03160 spr;
    Disc_b540_01E03160 disc;
    s32 timer;
    s32 t;
    s32 code;
    s32 j[3];
    f32 f38A8;
    u8 fade;
    u8 pad38AD[3];
    Vec4f tp1[28];
    Vec4f tp2[28];
} Scene_b540_01E03160;

static inline void Fill_b540_01E03160(Trail_b540_01E03160 *o, Vec4f *p1, Vec4f *p2) {
    s32 i;

    for (i = 0; i < 8; i++) {
        o->a[i].x = p1->x;
        o->a[i].y = p1->y;
        o->a[i].z = p1->z;
        o->b[i].x = p2->x;
        o->b[i].y = p2->y;
        o->b[i].z = p2->z;
    }
    o->len = 0;
}

static s32 func_01E03160_b540(s32 arg0, s32 code) {
    Scene_b540_01E03160 *g = (Scene_b540_01E03160 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern f32 func_001F5850(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6D00(s32);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_001A22C0(f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001033D0(void *, f32, f32);
    extern s32 func_0019A5C8();
    extern void b540_01E03B00();
    Vec4f v[2];
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 r;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3C30);
        func_00103890(&g->m0);
        func_00103890(&g->m1);
        func_00103890(&g->m2);
        func_00103890(&g->m3);
        func_00103890(&g->m4);
        g->j[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 7, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 6, 0);
        g->timer = 0x140;
        g->t = 1;
        g->code = code;
        g->f38A8 = func_001F5850();
        g->fade = 0x80;
        g->disc.flags = 0x80000;
        g->disc.c[2] = 0x80;
        g->disc.c[1] = 0x40;
        g->disc.c[0] = 0x40;
        g->disc.c[3] = 0xFF;
        g->disc.radius = 30.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        func_00103260(tx, 0xF);
        g->trail.tex = tx[0];
        g->trail.flags = 1;
        g->trail.max = 8;
        g->trail.u = 0x8E;
        g->trail.v = 0x54;
        g->trail.w = 0x20;
        g->trail.h = 1;
        g->trail.c[2] = 0x80;
        g->trail.c[1] = 0xA0;
        g->trail.c[0] = 0xE0;
        g->trail.c[3] = 0xFF;
        g->trail.p1 = g->tp1;
        g->trail.p2 = g->tp2;
        func_001F5620(func_001F53A0(), g->j[1], &v[0]);
        func_001F5620(func_001F53A0(), g->j[2], &v[1]);
        Fill_b540_01E03160(&g->trail, &v[0], &v[1]);
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.c[2] = 0x80;
        g->spr.c[1] = 0x40;
        g->spr.c[0] = 0x40;
        g->spr.c[3] = 0x20;
        func_01E029F0_b540((Obj_b000_01E032C0 *)&g->spr, tx[0], 3.0f);
        func_00103290(tx, 0);
        g->emit1.tex = tx[0];
        g->emit1.flags = 0xD0000003;
        g->emit1.c[2] = 0x80;
        g->emit1.c[1] = 0x40;
        g->emit1.c[0] = 0x40;
        g->emit1.c[3] = 0;
        g->emit1.size = 2.0f;
        g->emit1.rot[0] = 0;
        g->emit1.rot[1] = 0x800;
        g->emit1.rot[2] = 0;
        g->emit1.uv[0] = 0;
        g->emit1.uv[1] = 0;
        g->emit1.uv[2] = 0x80;
        g->emit1.uv[3] = 0x40;
        g->emit1.uv[4] = 0;
        g->emit1.uv[5] = 0;
        g->emit1.uv[6] = 0x80;
        g->emit1.uv[7] = 0x40;
        g->emit1.pts = g->pts1;
        g->emit1.rots = g->rots1;
        g->emit1.x48 = 0;
        g->emit1.radius = 10.0f;
        g->emit1.amp = 25.0f;
        g->emit1.freq = 0x400;
        g->emit1.count = 0x100;
        g->emit1.nframes = 1;
        g->emit1.rate = 0;
        for (i = 0; i < g->emit1.count; i++) {
            r = func_001A22C0(10.0f * g->emit1.radius);
            a = func_0019A5C8() % 0x10000;
            d = 0.1f * (f32)(func_0019A5C8() % r);
            g->pts1[i].y = 0.1f * (f32)(func_0019A5C8() % 1000);
            g->pts1[i].z = d * func_0020B480(a);
            g->pts1[i].x = d * func_0020B550(a);
            g->pts1[i].t = -(func_0019A5C8() % 20);
            g->pts1[i].a = 0;
            g->pts1[i].frame = 0;
            g->rots1[i].a = func_0019A5C8() % 0x10000;
            g->rots1[i].b = func_0019A5C8() % 0x10000;
            g->rots1[i].c = func_0019A5C8() % 0x10000;
        }
        func_00103290(tx, 1);
        g->emit2.tex = tx[0];
        g->emit2.flags = 0x78000003;
        g->emit2.c[2] = 0x80;
        g->emit2.c[1] = 0x40;
        g->emit2.c[0] = 0x40;
        g->emit2.c[3] = 0;
        g->emit2.size = 20.0f;
        g->emit2.rot[0] = 0;
        g->emit2.rot[1] = 0;
        g->emit2.rot[2] = 0;
        g->emit2.uv[0] = 0;
        g->emit2.uv[1] = 0;
        g->emit2.uv[2] = 0x20;
        g->emit2.uv[3] = 0x20;
        g->emit2.uv[4] = 0;
        g->emit2.uv[5] = 0;
        g->emit2.uv[6] = 0x80;
        g->emit2.uv[7] = 0x40;
        g->emit2.pts = g->pts2;
        g->emit2.rots = g->rots2;
        g->emit2.x48 = 0;
        g->emit2.radius = 10.0f;
        g->emit2.amp = 0.0f;
        g->emit2.grow = 1.0f;
        g->emit2.freq = 0;
        g->emit2.count = 0x80;
        g->emit2.nframes = 8;
        g->emit2.rate = 0;
        for (i = 0; i < g->emit2.count; i++) {
            r = func_001A22C0(10.0f * g->emit2.radius);
            a = func_0019A5C8() % 0x10000;
            d = 0.1f * (f32)(func_0019A5C8() % r);
            g->pts2[i].y = 0.1f * -(f32)(func_0019A5C8() % 40 - 20);
            g->pts2[i].z = d * func_0020B480(a);
            g->pts2[i].x = d * func_0020B550(a);
            g->pts2[i].t = -(func_0019A5C8() % 12);
            g->pts2[i].a = 0;
            g->pts2[i].frame = func_0019A5C8() % 8;
            g->rots2[i].a = func_0019A5C8() % 0x10000;
            g->rots2[i].b = func_0019A5C8() % 0x10000;
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->m4.pos);
    if (g->t < 0x35) {
        func_001F5620(func_001F53A0(), g->j[0], &g->m2.pos);
        func_001F5F90(func_001F5380(), &v[0]);
        func_001F5620(func_001F53A0(), g->j[0], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->m2.rot);
    }
    func_001F5620(func_001F53A0(), g->j[0], &g->m3.pos);
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5620(func_001F53A0(), g->j[0], &v[1]);
    func_00103DB0(&v[0], &v[1], &g->m3.rot);
    func_001F5620(func_001F53A0(), g->j[1], &v[0]);
    func_001F5620(func_001F53A0(), g->j[2], &v[1]);
    if (g->t == 0x124) {
        Fill_b540_01E03160(&g->trail, &v[0], &v[1]);
    } else {
        func_01E020A0_b540((Trail_b025_01E007C0 *)&g->trail, &v[0], &v[1]);
    }
    func_001038D0(&g->m0);
    func_001039A0(&g->m1);
    func_001038D0(&g->m2);
    func_001038D0(&g->m3);
    func_001039A0(&g->m4);
    if (g->t >= 0xDC && g->t < 0xFE) {
        func_01E00120_b540();
    }
    if (g->t < 0xFE) {
        func_00103470(&g->fade, 0x20, 4);
    } else if (g->t >= 0x126) {
        func_001032C0(&g->fade, 0x80, 4);
    }
    func_001F6D00(g->fade);
    if (g->t >= 0x126) {
        func_01E00250_b540(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->m4);
        func_00103470(&g->disc.c[3], 0, 0x10);
        func_01E02B50_b540(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->m4);
        func_00103470(&g->spr.c[3], 0, 2);
        { f32 q = 2.0f; func_001033D0(&g->m4, q, 0.1f); }
    }
    b540_01E03B00(g, ot);
    if (g->t > 0x124 && g->t < 0x12F) {
        func_01E021F0_b540((Obj_b025_01E00910 *)&g->trail, (Cam_b025_01E00910 *)&g->m0);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x126) {
        return 2;
    }
    if (g->t == 0x53) {
        return 1;
    }
    if (g->t >= 0x5D && g->t < 0x126) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
