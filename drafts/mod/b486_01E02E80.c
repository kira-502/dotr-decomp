#include "common.h"
#include "mod/b486.c"

/* shape b486:01E02E80 (b486), 626 insns, 1 copy: b486 scene manager (b143:01E02510 form): code >= 0 clears the scene
   (0x7CD0), resets six coords, joints 8 and 10, a 329-tick timer, a ring (LkSetRing 11.2/12.8), a 16-point trail
   emitter and two spinning particle sprays (512 at radius 2, 256 at radius 4); otherwise follows the joints, auto-
   blurs, fades the screen in to 105 and out from 310, draws the trail 21..49 (fading from 34), the ring with random
   colours 129..309 (re-grown when its scale settles), runs b486_Drop; returns 2 at 310, 1 at 118, 6 in 128..309, 8
   when the timer ends */

typedef struct {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b486_01E02E80;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_b486_01E02E80;

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_b486_01E02E80 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Em1_b486_01E02E80;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt2_b486_01E02E80;

typedef struct {
    s32 a, b;
    u8 pad8[8];
} Spin_b486_01E02E80;

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 u, v, w, h, u0, v0, tw, th;
    Pt2_b486_01E02E80 *pts;
    Spin_b486_01E02E80 *rots;
    s32 w48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Em2_b486_01E02E80;

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b486_01E02E80;

typedef struct {
    Crd_b486_01E02E80 crd;
    Crd_b486_01E02E80 crd2;
    Crd_b486_01E02E80 crd3;
    Em2_b486_01E02E80 em2;
    Pt2_b486_01E02E80 pts2[0x200];
    Spin_b486_01E02E80 spin2[0x200];
    Crd_b486_01E02E80 crd4;
    Em2_b486_01E02E80 em3;
    Pt2_b486_01E02E80 pts3[0x100];
    Spin_b486_01E02E80 spin3[0x100];
    u8 pad6280[0x1000];
    Crd_b486_01E02E80 crd5;
    Ring_b486_01E02E80 ring;
    u8 pad76F0[0x400];
    Crd_b486_01E02E80 cam;
    Em1_b486_01E02E80 em1;
    s32 count;
    s32 step;
    s32 id;
    s32 jA;
    s32 jB;
    u8 c[4];
    f32 f7CC8;
    u8 fade;
    u8 pad7CCD[3];
} Scene_b486_01E02E80;

static s32 func_01E02E80_b486(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5850(void);
    extern void func_001F6580(s32, void *);
    extern void func_001F6D00(s32);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern s32 func_001A22C0(f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern void b486_01E03850();
    Scene_b486_01E02E80 *g = (Scene_b486_01E02E80 *)arg0;
    s32 ot;
    Vec4f t[2];
    Vec4f sc;
    s32 tex[4];
    s32 i;
    s32 r;
    s32 n;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x7CD0);
        func_00103890(&g->crd);
        func_00103890(&g->crd2);
        func_00103890(&g->crd3);
        func_00103890(&g->crd4);
        func_00103890(&g->cam);
        func_00103890(&g->crd5);
        g->crd5.scale.x = g->crd5.scale.y = g->crd5.scale.z = 0.1f;
        g->jA = func_001F5560(func_001F53A0(), 8, 1);
        g->jB = func_001F5560(func_001F53A0(), 0xA, 0);
        g->count = 0x149;
        g->step = 1;
        g->id = code;
        g->f7CC8 = func_001F5850();
        g->fade = 0x80;
        g->c[3] = 0x80;
        g->c[0] = 0x80;
        g->c[1] = 0x80;
        g->c[2] = 0x80;
        func_00103260(tex, 0xF);
        g->ring.flags = 0x20000000;
        g->ring.u = 0x8E;
        g->ring.v = 0;
        g->ring.w = 0x20;
        g->ring.h = 0x80;
        g->ring.r = 0x80;
        g->ring.g = 0x80;
        g->ring.b = 0x80;
        g->ring.a = 0x80;
        func_01E026D0_b486((Ring_b001_01E035A0 *)&g->ring, tex[0], 11.2f, 12.8f, 0.0f, 0.0f);
        g->em1.tex = (void *)tex[0];
        g->em1.flags = 0x80083;
        g->em1.x = 0.0f;
        g->em1.y = 0.0f;
        g->em1.z = 0.0f;
        g->em1.w1C = 0;
        g->em1.tu = 0x80;
        g->em1.tv = 0xC0;
        g->em1.w = 0x20;
        g->em1.h = 0x20;
        g->em1.tw = 0x80;
        g->em1.th = 0x40;
        g->em1.size = 5.0f;
        g->em1.count = 0x10;
        g->em1.step = 2;
        g->em1.h13C = 1;
        g->em1.h140 = 8;
        g->em1.h136 = 0;
        g->em1.h138 = 0;
        g->em1.r = 0x80;
        g->em1.g = 0x60;
        g->em1.b = 0x70;
        g->em1.a = 0x20;
        for (i = 0; i < 16; i++) {
            g->em1.pts[i].x = g->em1.x + (func_0019A5C8() % 6 - 3);
            g->em1.pts[i].y = g->em1.y + (func_0019A5C8() % 6 - 3);
            g->em1.pts[i].z = g->em1.z;
            g->em1.pts[i].life = -g->em1.step * i;
            g->em1.pts[i].pad = 0;
            g->em1.h13E = g->em1.h140 - 1;
        }
        func_00103290(tex, 0);
        g->em2.tex = (void *)tex[0];
        g->em2.flags = 0xD0000003;
        g->em2.r = 0x80;
        g->em2.g = 0x80;
        g->em2.b = 0x80;
        g->em2.a = 0;
        g->em2.size = 3.0f;
        g->em2.rot[0] = 0;
        g->em2.rot[1] = 0x800;
        g->em2.rot[2] = 0;
        g->em2.u = 0;
        g->em2.v = 0;
        g->em2.w = 0x80;
        g->em2.h = 0x40;
        g->em2.u0 = 0;
        g->em2.v0 = 0;
        g->em2.tw = 0x80;
        g->em2.th = 0x40;
        g->em2.pts = g->pts2;
        g->em2.rots = g->spin2;
        g->em2.w48 = 0;
        g->em2.radius = 2.0f;
        g->em2.amp = 25.0f;
        g->em2.freq = 0x400;
        g->em2.count = 0x200;
        g->em2.nframes = 1;
        g->em2.rate = 0;
        for (i = 0; i < g->em2.count; i++) {
            r = func_0019A5C8() % 0x10000;
            g->pts2[i].y = 0.1f * (func_0019A5C8() % 2000);
            g->pts2[i].z = g->em2.radius * func_0020B480(r);
            g->pts2[i].x = g->em2.radius * func_0020B550(r);
            g->pts2[i].t = -(func_0019A5C8() % 20);
            g->pts2[i].a = 0;
            g->pts2[i].frame = 0;
            g->spin2[i].a = func_0019A5C8() % 0x10000;
            g->spin2[i].b = func_0019A5C8() % 0x10000;
        }
        g->em3.tex = (void *)tex[0];
        g->em3.flags = 0xF0000003;
        g->em3.r = 0x80;
        g->em3.g = 0x80;
        g->em3.b = 0x80;
        g->em3.a = 0;
        g->em3.size = 3.0f;
        g->em3.rot[0] = 0;
        g->em3.rot[1] = 0;
        g->em3.rot[2] = 0;
        g->em3.u = 0;
        g->em3.v = 0;
        g->em3.w = 0x80;
        g->em3.h = 0x40;
        g->em3.u0 = 0;
        g->em3.v0 = 0;
        g->em3.tw = 0x80;
        g->em3.th = 0x40;
        g->em3.pts = g->pts3;
        g->em3.rots = g->spin3;
        g->em3.w48 = 0;
        g->em3.radius = 4.0f;
        g->em3.amp = 0.0f;
        g->em3.freq = 0;
        g->em3.count = 0x100;
        g->em3.nframes = 1;
        g->em3.rate = 0;
        for (i = 0; i < g->em3.count; i++) {
            n = func_001A22C0(10.0f * g->em3.radius);
            r = func_0019A5C8() % 0x10000;
            d = 0.1f * (func_0019A5C8() % n);
            g->pts3[i].y = 0.1f * -(f32)(func_0019A5C8() % 40 - 20);
            g->pts3[i].z = d * func_0020B480(r);
            g->pts3[i].x = d * func_0020B550(r);
            g->pts3[i].t = -(func_0019A5C8() % 12);
            g->pts3[i].a = 0x80;
            g->spin3[i].a = func_0019A5C8() % 0x10000;
            g->spin3[i].b = func_0019A5C8() % 0x10000;
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->crd5.pos);
    func_001F5620(func_001F53A0(), g->jA, &g->cam.pos);
    func_001F5620(func_001F53A0(), g->jA, &g->crd3.pos);
    func_001F5F90(func_001F5380(), &t[0]);
    func_001F5620(func_001F53A0(), g->jA, &t[1]);
    func_00103DB0(&t[0], &t[1], &g->crd3.rot);
    func_001F5620(func_001F53A0(), g->jB, &g->crd4.pos);
    func_001F5620(func_001F53A0(), g->jB, &t[0]);
    func_00103DB0(&t[0], &t[1], &g->crd4.rot);
    func_001038D0(&g->crd);
    func_001039A0(&g->crd2);
    func_001039A0(&g->cam);
    func_001038D0(&g->crd3);
    func_001038D0(&g->crd4);
    func_001038D0(&g->crd5);
    func_01E00120_b486();
    if (g->step < 0x69) {
        func_00103470(&g->fade, 0x20, 4);
    } else if (g->step >= 0x136) {
        func_001032C0(&g->fade, 0x80, 4);
    }
    func_001F6D00(g->fade);
    if (g->step >= 0x15 && g->step < 0x32) {
        sc.x = sc.y = sc.z = 1.01f;
        func_01E01B40_b486(ot, (Cam_b001_01E00A30 *)&g->cam, (Emit_b001_01E00A30 *)&g->em1,
                           (Vec_b001_01E00A30 *)&sc);
        if (g->step >= 0x22) {
            func_00103470(&g->em1.a, 0, 2);
        }
    }
    if (g->step > 0x80) {
        if (g->step < 0x136) {
        func_001F6580(func_001F5380(), g->c);
        g->c[2] = func_0019A5C8() % 0x80;
        g->c[1] = func_0019A5C8() % 0x80;
        g->c[0] = func_0019A5C8() % 0x80;
        func_01E02990_b486(ot, (Ring_b001_01E03860 *)&g->ring, (Cam_b001_01E03860 *)&g->crd5);
        func_00103470(&g->ring.a, 0, 8);
        g->ring.r = func_0019A5C8() % 0x80;
        g->ring.g = func_0019A5C8() % 0x80;
        g->ring.b = func_0019A5C8() % 0x80;
        if (func_001033D0(&g->crd5, 2.0f, 0.2f) == 0) {
            g->crd5.scale.x = g->crd5.scale.y = g->crd5.scale.z = 0.1f;
            g->ring.a = 0x80;
        }
        }
    }
    b486_01E03850(g, ot);
    g->step++;
    g->count--;
    if (g->step == 0x136) {
        func_001F6580(func_001F5380(), 0);
        return 2;
    }
    if (g->step == 0x76) {
        return 1;
    }
    if (g->step >= 0x80 && g->step < 0x136) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
