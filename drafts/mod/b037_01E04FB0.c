#include "common.h"
#include "mod/b037.c"

/* shape b037:01E04FB0 (b037), 989 insns, 1 copy: b037 scene manager: code >= 0 clears the scene, eight cameras, six
   joints, the field particles, two trail emitters, a 256-point spark emitter, twelve rings, the spiral and the shaver
   light; else follows the joints, feeds field particles on frames 25..31/50..64/74..122, waits on func_001F7260 from
   248 to 330, fades, draws rings from 243 and sparks from 123 then runs b037:01E05F30; returns 2/1/6/8 by tick */

typedef struct Rot_b037_01E04FB0 {
    s32 x, y, z, w;
} Rot_b037_01E04FB0;

typedef struct Crd_b037_01E04FB0 {
    Vec4f scale;
    Rot_b037_01E04FB0 rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b037_01E04FB0;

typedef struct Fld_b037_01E04FB0 {
    s32 tex;
    u8 b, g, r, a;
    s32 flags;
    f32 size;
    s16 s10, s12;
    s16 cw, ch;
    s16 u0, v0;
    s16 aw, ah;
    u8 pad20[0x10];
    f32 grow;
    s16 h34;
    s16 life;
    s16 max;
    s16 used;
    s16 frames;
    s16 rate;
} Fld_b037_01E04FB0;

typedef struct Part_b037_01E04FB0 {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b037_01E04FB0;

typedef struct Spiral_b037_01E04FB0 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 h;
    f32 dy;
    f32 f14;
    f32 scale;
    s32 count;
    s16 u, v, w, hh;
    u8 pad28[8];
    Vec4f pts[30];
} Spiral_b037_01E04FB0;

typedef struct Shav_b037_01E04FB0 {
    s32 model;
    u8 col[4];
    u8 pad8[4];
    s32 z;
    s16 pts[4][128][2];
    s16 rot[4];
    u8 padDF8[8];
} Shav_b037_01E04FB0;

typedef struct Dot_b037_01E04FB0 {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Dot_b037_01E04FB0;

typedef struct Emit2_b037_01E04FB0 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 cx, cy, cz, cw;
    s16 u, v, w, h;
    s16 s28, s2A, s2C, s2E;
    Dot_b037_01E04FB0 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 s136;
    s16 s138;
    s16 step;
    s16 s13C;
    s16 s13E;
    s16 s140;
    u8 pad142[0xE];
} Emit2_b037_01E04FB0;

typedef struct Pt_b037_01E04FB0 {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b037_01E04FB0;

typedef struct Emit_b037_01E04FB0 {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 uv[8];
    Pt_b037_01E04FB0 *pts;
    s32 rots;
    s32 x48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b037_01E04FB0;

typedef struct Ring_b037_01E04FB0 {
    s32 type;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b037_01E04FB0;

typedef struct Scene_b037_01E04FB0 {
    Crd_b037_01E04FB0 c0;
    Fld_b037_01E04FB0 fld;
    Part_b037_01E04FB0 pts[0x24];
    Crd_b037_01E04FB0 c2F0;
    Spiral_b037_01E04FB0 spiral;
    Crd_b037_01E04FB0 c570;
    Shav_b037_01E04FB0 shav;
    Crd_b037_01E04FB0 cE00;
    Emit2_b037_01E04FB0 emitA;
    Crd_b037_01E04FB0 cFC0;
    Emit2_b037_01E04FB0 emitB;
    Crd_b037_01E04FB0 c1180;
    Crd_b037_01E04FB0 c11F0;
    Emit_b037_01E04FB0 emit;
    Pt_b037_01E04FB0 pts2[0x100];
    Crd_b037_01E04FB0 c22C0;
    Ring_b037_01E04FB0 ringA[4];
    Ring_b037_01E04FB0 ringB[4];
    Ring_b037_01E04FB0 ringC[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 j[6];
    u8 pad5354[4];
    u8 colA[4];
    u8 colB[4];
    u8 colC[4];
    u8 fade;
    u8 pad5365[0xB];
} Scene_b037_01E04FB0;

static s32 func_01E04FB0_b037(s32 arg0, s32 code) {
    Scene_b037_01E04FB0 *g = (Scene_b037_01E04FB0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F57C0(s32, s32);
    extern void func_001F6D00(s32);
    extern void func_001F7260(s32);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern s32 func_0019A5C8();
    extern void b037_01E05F30();
    Vec4f v[2];
    Vec4f w;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 a;
    f32 ang;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x5370);
        func_00103890(&g->c0);
        func_00103890(&g->c2F0);
        func_00103890(&g->cFC0);
        func_00103890(&g->c570);
        func_00103890(&g->cE00);
        func_00103890(&g->c1180);
        func_00103890(&g->c11F0);
        func_00103890(&g->c22C0);
        g->j[0] = func_001F5560(func_001F53A0(), 0x30, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x31, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x4A, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x52, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x60, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x6A, 0);
        g->timer = 0x154;
        g->t = 1;
        g->code = code;
        g->fade = 0x80;
        g->colA[0] = 0x80;
        g->colA[1] = 0x80;
        g->colA[2] = 0x80;
        g->colA[3] = 0;
        g->colB[2] = 0x30;
        g->colB[1] = 0x60;
        g->colB[0] = 0x80;
        g->colB[3] = 0;
        g->colC[2] = 0x80;
        g->colC[1] = 0x80;
        g->colC[0] = 0x80;
        g->colC[3] = 0x60;
        func_00103290(tx, 0);
        g->emitB.texture = tx[0];
        g->emitB.flags = 7;
        g->emitB.cx = 0.0f;
        g->emitB.cy = 0.0f;
        g->emitB.cz = 0.0f;
        g->emitB.u = 0;
        g->emitB.v = 0;
        g->emitB.w = 0x20;
        g->emitB.h = 0x20;
        g->emitB.s28 = 0;
        g->emitB.s2A = 0;
        g->emitB.s2C = 0x80;
        g->emitB.s2E = 0x40;
        g->emitB.size = 6.0f;
        g->emitB.count = 0x10;
        g->emitB.step = 2;
        g->emitB.s13C = 0;
        g->emitB.s140 = 8;
        g->emitB.s136 = 0xA;
        g->emitB.s138 = 0xA;
        g->emitB.r = 0x80;
        g->emitB.g = 0x80;
        g->emitB.b = 0x80;
        g->emitB.a = 0x40;
        for (i = 0; i < 8; i++) {
            g->emitB.pts[i].x = func_0019A5C8() % 20 - 10;
            g->emitB.pts[i].y = func_0019A5C8() % 20 - 10;
            g->emitB.pts[i].life = -g->emitB.step * i;
            g->emitB.pts[i].pad = 0;
            g->emitB.s13E = g->emitB.s140 - 1;
        }
        g->emit.tex = tx[0];
        g->emit.flags = 0x50000003;
        g->emit.c[2] = 0x80;
        g->emit.c[1] = 0x80;
        g->emit.c[0] = 0x80;
        g->emit.c[3] = 0x80;
        g->emit.size = 1.0f;
        g->emit.rot[0] = 0;
        g->emit.rot[1] = 0x800;
        g->emit.rot[2] = 0;
        g->emit.uv[0] = 0;
        g->emit.uv[1] = 0;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0;
        g->emit.uv[5] = 0;
        g->emit.uv[6] = 0x80;
        g->emit.uv[7] = 0x40;
        g->emit.pts = g->pts2;
        g->emit.rots = 0;
        g->emit.x48 = 0;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        func_01E017E0_b037((Ring_b001_01E01B20 *)&g->emit, 2.0f);
        for (i = 0; i < g->emit.count; i++) {
            g->pts2[i].t = -(func_0019A5C8() % 12);
            g->pts2[i].a = 0;
            g->pts2[i].frame = func_0019A5C8() % 8;
            g->pts2[i].y += 20.0f;
        }
        for (i = 0; i < 4; i++) {
            g->ringA[i].flags = 0x60000000;
            g->ringA[i].u = 0;
            g->ringA[i].v = 0x20;
            g->ringA[i].w = 0x20;
            g->ringA[i].h = 0x10;
            g->ringA[i].r = 0x80;
            g->ringA[i].g = 0x80;
            g->ringA[i].b = 0x80;
            g->ringA[i].a = 0x80;
            g->ringB[i].flags = 0x60000000;
            g->ringB[i].u = 0;
            g->ringB[i].v = 0x20;
            g->ringB[i].w = 0x20;
            g->ringB[i].h = 0x10;
            g->ringB[i].r = 0x80;
            g->ringB[i].g = 0x80;
            g->ringB[i].b = 0x80;
            g->ringB[i].a = 0x80;
        }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 r = 6.0f; f32 q = 4.0f; f32 z = 0.0f; b037_01E03260(&g->ringA[0], tx[0], r, q, 0.0f, z); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 r = 3.75f; f32 q = 4.0f; f32 z = 0.0f; b037_01E03260(&g->ringB[0], tx[0], r, q, z, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32);  b037_01E03260(&g->ringA[1], tx[0], 8.0f, 6.0f, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 z = 0.0f; b037_01E03260(&g->ringB[1], tx[0], 5.75f, 6.0f, z, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 z = 0.0f; b037_01E03260(&g->ringA[2], tx[0], 10.0f, 8.0f, z, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 z = 0.0f; b037_01E03260(&g->ringB[2], tx[0], 7.75f, 8.0f, 0.0f, z); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32);  b037_01E03260(&g->ringA[3], tx[0], 12.0f, 10.0f, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 z = 0.0f; b037_01E03260(&g->ringB[3], tx[0], 9.75f, 10.0f, z, z); }
        func_00103260(tx, 0xF);
        for (i = 0; i < 4; i++) {
            g->ringC[i].flags = 0x20000000;
            g->ringC[i].u = 0x8E;
            g->ringC[i].v = 0;
            g->ringC[i].w = 0x20;
            g->ringC[i].h = 0x80;
            g->ringC[i].r = 0x70;
            g->ringC[i].g = 0x40;
            g->ringC[i].b = 0xA0;
            g->ringC[i].a = 0x40;
        }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 r; f32 q; r = 4.25f; q = 3.75f; b037_01E03260(&g->ringC[0], tx[0], r, q, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 r = 6.25f; f32 z = 0.0f; b037_01E03260(&g->ringC[1], tx[0], r, 5.75f, 0.0f, z); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32);  b037_01E03260(&g->ringC[2], tx[0], 8.25f, 7.75f, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32);  b037_01E03260(&g->ringC[3], tx[0], 10.25f, 9.75f, 0.0f, 0.0f); }
        g->fld.tex = tx[0];
        g->fld.r = 0x30;
        g->fld.g = 0x60;
        g->fld.b = 0x80;
        g->fld.a = 0x30;
        g->fld.flags = 0x9003;
        g->fld.size = 3.0f;
        g->fld.s10 = 0x80;
        g->fld.s12 = 0xC0;
        g->fld.cw = 0x20;
        g->fld.ch = 0x20;
        g->fld.u0 = 0x80;
        g->fld.v0 = 0xC0;
        g->fld.aw = 0x80;
        g->fld.ah = 0x100;
        g->fld.grow = 0.3f;
        g->fld.h34 = 0;
        g->fld.life = 0x18;
        g->fld.max = 0x24;
        g->fld.used = 0;
        g->fld.frames = 8;
        g->shav.model = 0xA0081000;
        g->shav.col[2] = 0x80;
        g->shav.col[1] = 0x80;
        g->shav.col[0] = 0x80;
        g->shav.col[3] = 0x80;
        g->spiral.tex = tx[0];
        g->spiral.flags = 1;
        g->spiral.r = 0x20;
        g->spiral.g = 0xA0;
        g->spiral.b = 0xB0;
        g->spiral.a = 0xFF;
        g->spiral.h = 0.8f;
        g->spiral.dy = 0.1f;
        g->spiral.f14 = 30.0f;
        g->spiral.scale = 0.05f;
        g->spiral.count = 0;
        g->spiral.u = 0x8E;
        g->spiral.v = 0x54;
        g->spiral.w = 0x20;
        g->spiral.hh = 0x2C;
        for (a = 0; a < 30; a++) {
            ang = 0.20943952f * (f32)a;
            g->spiral.pts[a].x = func_0020B620(ang);
            g->spiral.pts[a].z = func_0020B730(ang);
            g->spiral.pts[a].y = 0.0f;
        }
        func_00103260(tx, 1);
        g->emitA.texture = tx[0];
        g->emitA.flags = 0x403;
        g->emitA.cx = 0.0f;
        g->emitA.cy = 0.0f;
        g->emitA.cz = 0.0f;
        g->emitA.cw = 0.0f;
        g->emitA.s28 = 0;
        g->emitA.s2A = 0;
        g->emitA.w = 0x18;
        g->emitA.h = 0x20;
        g->emitA.s2C = 0x80;
        g->emitA.s2E = 0x40;
        g->emitA.size = 12.0f;
        g->emitA.count = 0x10;
        g->emitA.step = 2;
        g->emitA.s13C = 1;
        g->emitA.s140 = 0xA;
        g->emitA.s136 = 0xA;
        g->emitA.s138 = 0xA;
        g->emitA.r = 0x80;
        g->emitA.g = 0x80;
        g->emitA.b = 0x80;
        g->emitA.a = 0;
        func_01E00280_b037((Trail_b037_01E00280 *)&g->emitA);
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j[0], &v[0]);
    func_001F5620(func_001F53A0(), g->j[1], &v[1]);
    func_001F5F90(func_001F5380(), &g->cFC0.pos);
    func_001F53C0(1, func_001F53A0(), &g->cE00.pos);
    func_001F5620(func_001F53A0(), g->j[0], &g->c1180.pos);
    if (((g->t >= 0x19 && g->t < 0x20) || (g->t >= 0x32 && g->t < 0x41) || (g->t >= 0x4A && g->t < 0x7B)) &&
        g->t % 2 == 0) {
        if (func_0019A5C8() % 2) {
            func_001F5620(func_001F53A0(), g->j[5], &w);
        } else {
            func_001F5620(func_001F53A0(), g->j[4], &w);
        }
        func_01E04530_b037((Trail_b025_01E01EF0 *)&g->fld, (Pt_b025_01E01EF0 *)g->pts, (Vec_b025_01E01EF0 *)&w);
    }
    func_001F5F90(func_001F5380(), &g->c570.pos);
    func_001F5F90(func_001F5380(), &g->c22C0.pos);
    if (g->c22C0.pos.z > 0.0f) {
        g->c22C0.rot.y = 0x8000;
    }
    if (g->t == 0x7B) {
        func_001F5620(func_001F53A0(), g->j[0], &g->c2F0.pos);
    }
    func_00103DB0(&v[0], &v[1], &g->c2F0.rot);
    g->c2F0.pos.x = v[1].x;
    g->c2F0.pos.y = v[1].y;
    g->c2F0.pos.z = v[1].z;
    func_00103DB0(&v[1], &v[0], &g->c1180.rot);
    func_001038D0(&g->c0);
    func_001038D0(&g->c570);
    func_001038D0(&g->c2F0);
    func_001038D0(&g->c1180);
    func_001039A0(&g->cFC0);
    func_001039A0(&g->cE00);
    func_001038D0(&g->c22C0);
    if (g->t >= 0xE9) {
        func_001F57C0(func_001F53A0(), 1);
    }
    if (g->t >= 0xF8 && g->t < 0x14A) {
        func_001F7260(1);
    } else if (g->t == 0x14A) {
        func_001F7260(0);
    }
    func_001F6D00(g->fade);
    if (g->t >= 0x7B && g->t < 0xF8) {
        func_00103470(&g->fade, 0x30, 2);
    }
    if (g->t >= 0x14A) {
        func_001032C0(&g->fade, 0x80, 0x10);
    }
    if (g->t >= 0x125) {
        func_01E00120_b037(ot, (Src_b000_01E00400 *)g->colA);
        func_001032C0(&g->colA[3], 0xFF, 8);
    }
    func_01E00F70_b037(g->colC);
    if (g->t >= 0xE9) {
        func_00103470(&g->colC[3], 0, 6);
    }
    if (g->t < 0xD1) {
        w.x = w.y = w.z = 0.0f;
        func_01E003E0_b037(ot, (Cam_b001_01E00A30 *)&g->cE00, (Emit_b001_01E00A30 *)&g->emitA, (Vec_b001_01E00A30 *)&w);
        if (g->t > 0x5D && g->t < 0x7B) {
            func_001032C0(&g->emitA.a, 0x20, 2);
        } else if (g->t > 0x7B) {
            func_00103470(&g->emitA.a, 0, 2);
        }
    }
    func_01E04610_b037(ot, (Em_b025_01E01FD0 *)&g->fld, (Part_b025_01E01FD0 *)g->pts, (Cam_b025_01E01FD0 *)&g->c0);
    for (i = 0; i < g->fld.used; i++) {
        func_00103470(&g->pts[i].c, 0, 2);
    }
    if (g->t > 0x94) {
        func_00103470(&g->fld.a, 0, 8);
    }
    if (g->t >= 0xF3) {
        for (i = 0; i < 4; i++) {
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringC[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringA[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringB[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_00103470(&g->ringA[i].a, 0, 8);
            func_00103470(&g->ringB[i].a, 0, 8);
            func_00103470(&g->ringC[i].a, 0, 4);
        }
        if (g->c22C0.pos.z > 0.0f) {
            g->c22C0.rot.z -= 0x300;
        } else {
            g->c22C0.rot.z += 0x300;
        }
        func_001033D0(&g->c22C0, 3.0f, 0.1f);
    }
    if (g->t >= 0x7B) {
        func_01E01970_b037(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->c1180);
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts2[i].t >= 0) {
                g->pts2[i].y -= 2.0f;
                func_001032C0(&g->pts2[i].a, 0x80, 8);
                if (g->pts2[i].y > 0.0f) {
                    g->pts2[i].z *= 0.8f;
                    g->pts2[i].x *= 0.8f;
                }
                if (g->pts2[i].y < 0.0f) {
                    a = func_0019A5C8() % 0x10000;
                    g->pts2[i].z = g->emit.radius * func_0020B480(a);
                    g->pts2[i].x = g->emit.radius * func_0020B550(a);
                    g->pts2[i].y = 20.0f + (f32)(func_0019A5C8() % 10);
                    g->pts2[i].a = 0;
                }
            }
        }
        if (g->t >= 0xD1) {
            func_00103470(&g->emit.c[3], 0, 2);
        }
        b037_01E05F30(g, ot);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x14A) {
        return 2;
    }
    if (g->t == 0xAE) {
        return 1;
    }
    if (g->t >= 0xD1 && g->t < 0x14A) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
