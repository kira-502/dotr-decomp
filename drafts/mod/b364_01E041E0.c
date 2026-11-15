#include "common.h"

/* shape b364:01E041E0 (b364), 977 insns, 1 copy: b364 scene manager (b118:01E03A20's form plus a sixth camera, the
   auto-blur volume and a beam): setup (60-point spark, a sprite, two rings, two outlines, a 16-point emitter, the
   ball, a 48-item beam); each tick follows joint 2, auto-blur fades in/out at 340, emitter until 106, ball from 105
   in random colours spinning, the second outline chases the vec with a sine bob (or the spark), sprite/rings/outline
   fade after 340, beam from 45; returns 2/1/6/8 by tick */

typedef struct {
    u8 b, g, r, a;
} Col_b364_01E041E0;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    s32 rot[4];
    f32 pos[4];
    u8 pad30[0x40];
} Cam_b364_01E041E0;

typedef struct {
    s32 a, b, c, d;
} Rnd_b364_01E041E0;

typedef struct {
    s32 kind;
    s32 flags;
    Col_b364_01E041E0 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rnd_b364_01E041E0 r[64];
} Spr_b364_01E041E0;

typedef struct {
    s32 kind;
    s32 flags;
    s32 type;
    u8 padC[0x94];
} Fx_b364_01E041E0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_b364_01E041E0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_b364_01E041E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b364_01E041E0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b364_01E041E0;

typedef struct {
    f32 x, y, z;
} Pt_b364_01E041E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b364_01E041E0 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_b364_01E041E0 pts[60];
} Spark_b364_01E041E0;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_b364_01E041E0;

typedef struct {
    void *tex;
    s32 flags;
    Col_b364_01E041E0 color;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_b364_01E041E0 pts[16];
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
} Em1_b364_01E041E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b364_01E041E0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x1808];
} Ball_b364_01E041E0;

typedef struct {
    u8 pad0[0xC];
    u8 a;
    u8 padD[3];
} Item_b364_01E041E0;

typedef struct {
    s32 texture;
    Col_b364_01E041E0 color;
    s32 flags;
    f32 scale;
    s16 u, v, w, h;
    s16 u2, v2, w2, h2;
    f32 pts[0x24][2];
    s16 n;
    s16 phase;
    f32 width;
    Item_b364_01E041E0 *items;
    s16 count;
    s16 rows;
    f32 speed;
    u8 pad154[0xC];
} Beam_b364_01E041E0;

typedef struct {
    Cam_b364_01E041E0 cam0;
    Cam_b364_01E041E0 cam1;
    Spr_b364_01E041E0 spr;
    Fx_b364_01E041E0 fx;
    Mdl_b364_01E041E0 mdl;
    Ring_b364_01E041E0 ring0;
    Ring_b364_01E041E0 ring1;
    Cam_b364_01E041E0 cam2;
    Em1_b364_01E041E0 em;
    Cam_b364_01E041E0 cam3;
    Fx_b364_01E041E0 fx2;
    Mdl_b364_01E041E0 mdl2;
    Spark_b364_01E041E0 spark;
    Cam_b364_01E041E0 cam4;
    Ball_b364_01E041E0 ball;
    Cam_b364_01E041E0 cam5;
    Beam_b364_01E041E0 beam;
    Item_b364_01E041E0 items[64];
    Vec4f vec;
    s32 flags;
    s32 timer;
    s32 t;
    s32 code;
    s32 j0;
    s32 j1;
    s32 j2;
    s32 vol;
    f32 f32F0;
    u8 col[4];
    s32 lag;
    s32 ang;
} Scene_b364_01E041E0;

static s32 func_01E041E0_b364(s32 arg0, s32 code) {
    Scene_b364_01E041E0 *g = (Scene_b364_01E041E0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_001039A0(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53B0(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_001F5850(void);
    extern void func_001F62B0(s32, void *);
    extern void func_00103580(void *, f32, f32);
    extern s32 func_001033D0(void *, f32, f32);
    extern void func_00104490(void *, void *, s32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern void func_00103DB0(void *, void *, void *);
    extern void func_001F6D00(s32);
    extern void func_00103540(void *, f32, f32);
    Vec4f v0;
    Vec4f v1;
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 m;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3300);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam4);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam5);
        g->j0 = func_001F5560(func_001F53A0(), 6, 1);
        g->j1 = func_001F5560(func_001F53A0(), 5, 0);
        g->j2 = func_001F5560(func_001F53A0(), 7, 0);
        g->timer = 0x164;
        g->t = 1;
        g->code = code;
        g->flags = 0;
        g->lag = 0x1E;
        g->ang = 0;
        g->f32F0 = func_001F5850();
        g->vol = 0x80;
        g->col[0] = 0;
        g->col[1] = 0;
        g->col[3] = 0x80;
        g->col[2] = 0x80;
        func_00103260(&tex, 0xF);
        g->spark.texture = tex;
        g->spark.size = 1.0f;
        for (i = 0; i < 60; i++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.pts[i].x = func_0019A5C8() % 100 - 50;
                g->spark.pts[i].z = func_0019A5C8() % 50;
                g->spark.pts[i].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.pts[i].x = func_0019A5C8() % 50 - 25;
                g->spark.pts[i].y = func_0019A5C8() % 25;
                g->spark.pts[i].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 0x20080081;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x80;
        g->spark.color.b = 0x80;
        g->spark.color.a = 0x80;
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.color.r = 0xD0;
        g->spr.color.g = 0xA0;
        g->spr.color.b = 0x70;
        g->spr.color.a = 0x20;
        { f32 fs2 = 1.5f; func_01E03250_b364((Obj_b000_01E032C0 *)&g->spr, tex, fs2); }
        g->ring0.flags = 0x20080000;
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.color.r = 0xD0;
        g->ring0.color.g = 0xA0;
        g->ring0.color.b = 0x70;
        g->ring0.color.a = 0x20;
        func_01E01750_b364((Ring_b001_01E035A0 *)&g->ring0, tex, 12.0f, 11.2f, 0.0f, 0.0f);
        g->ring1.flags = 0x20080000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0xD0;
        g->ring1.color.g = 0xA0;
        g->ring1.color.b = 0x70;
        g->ring1.color.a = 0x30;
        { f32 fs2 = 12.0f; func_01E01750_b364(&g->ring1, tex, fs2, 12.8f, 0.0f, 0.0f); }
        g->mdl.flags = 0x40001;
        g->mdl.r[0] = 0xB0;
        g->mdl.r[1] = 0x20;
        g->mdl.r[2] = 0x20;
        g->mdl.r[3] = 0x20;
        g->mdl.r[4] = 0xB0;
        g->mdl.r[5] = 0x20;
        g->mdl.r[6] = 0x100;
        g->mdl.r[7] = 0x100;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0xD0;
        g->mdl.color.g = 0xA0;
        g->mdl.color.b = 0x70;
        g->mdl.color.a = 0x60;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        g->fx.type = 1;
        { extern s32 b364_01E00250(void *, void *, s32, f32); b364_01E00250(&g->mdl, &g->fx, tex, 16.0f); }
        g->mdl2.flags = 0x80001;
        g->mdl2.r[0] = 0xB0;
        g->mdl2.r[1] = 0x20;
        g->mdl2.r[2] = 0x20;
        g->mdl2.r[3] = 0x20;
        g->mdl2.r[4] = 0xB0;
        g->mdl2.r[5] = 0x20;
        g->mdl2.r[6] = 0x100;
        g->mdl2.r[7] = 0x100;
        g->mdl2.f30 = 1.0f;
        g->mdl2.color.r = 0x80;
        g->mdl2.color.g = 0x80;
        g->mdl2.color.b = 0x80;
        g->mdl2.color.a = 0xFF;
        g->mdl2.h48 = 0;
        g->mdl2.h4A = 0;
        g->mdl2.h4C = 0;
        g->mdl2.h4E = 1;
        g->mdl2.h50 = 0;
        g->mdl2.h52 = 999;
        g->fx2.type = 1;
        func_01E00250_b364((Model_b013_01E001A0 *)&g->mdl2, (Fx_b013_01E001A0 *)&g->fx2, tex, 50.0f);
        func_00103290(&tex, 0);
        g->em.tex = (void *)tex;
        g->em.flags = 0x81083;
        g->em.x = 0.0f;
        g->em.y = 0.0f;
        g->em.z = 0.0f;
        g->em.w1C = 0;
        g->em.tu = 0;
        g->em.tv = 0;
        g->em.w = 0x20;
        g->em.h = 0x20;
        g->em.tw = 0x80;
        g->em.th = 0x40;
        g->em.size = 6.0f;
        g->em.count = 0x10;
        g->em.step = 3;
        g->em.h13C = 2;
        g->em.h140 = 8;
        g->em.h136 = 10;
        g->em.h138 = 10;
        g->em.color.r = 0x60;
        g->em.color.g = 0x70;
        g->em.color.b = 0x80;
        g->em.color.a = 0xA0;
        for (m = 0; m < 16; m++) {
            g->em.pts[m].x = g->em.x + (func_0019A5C8() % 10 - 5);
            g->em.pts[m].y = g->em.y + (func_0019A5C8() % 8 - 2);
            g->em.pts[m].z = g->em.z;
            g->em.pts[m].life = -g->em.step * m;
            g->em.pts[m].pad = 0;
            g->em.h13E = g->em.h140 - 1;
        }
        func_00103290(&tex, 1);
        g->ball.flags = 3;
        g->ball.u = 0;
        g->ball.v = 0;
        g->ball.w = 0x80;
        g->ball.h = 0x80;
        g->ball.color.r = 0xB0;
        g->ball.color.g = 0xA0;
        g->ball.color.b = 0x70;
        g->ball.color.a = 0;
        func_01E02A90_b364((Dome_b364_01E02A90 *)&g->ball, tex, (f32)g->f32F0);
        g->beam.texture = tex;
        g->beam.color.r = 0x40;
        g->beam.color.g = 0x40;
        g->beam.color.b = 0x80;
        g->beam.color.a = 0xA0;
        g->beam.flags = 0x8000;
        g->beam.scale = 5.0f;
        g->beam.n = 0x20;
        g->beam.phase = 0;
        g->beam.width = 5.0f;
        g->beam.u = 0;
        g->beam.v = 0;
        g->beam.w = 0x80;
        g->beam.h = 0x80;
        g->beam.u2 = 0;
        g->beam.v2 = 0;
        g->beam.w2 = 0x80;
        g->beam.h2 = 0x80;
        g->beam.items = g->items;
        g->beam.count = 0x30;
        g->beam.rows = 0;
        g->beam.speed = 2.0f;
        func_01E039C0_b364((Obj_b047_01E01170 *)&g->beam, tex);
        for (i = 0; i < g->beam.count; i++) {
            g->beam.items[i].a = g->beam.color.a - i * (g->beam.color.a / g->beam.count);
        }
        func_001F53B0(2, g->cam0.pos);
        func_001F53C0(1, func_001F5380(), g->cam1.pos);
        func_001F53C0(1, func_001F53A0(), &g->vec);
        g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        g->cam3.x = g->cam3.y = g->cam3.z = 0.1f;
        g->cam4.x = g->cam4.y = g->cam4.z = 0.1f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j2, g->cam2.pos);
    func_001F5620(func_001F53A0(), g->j2, &g->vec);
    func_001F5620(func_001F53A0(), g->j2, g->cam1.pos);
    func_001F53C0(1, func_001F5380(), g->cam4.pos);
    if (g->t > 0xEB && g->t < 0x106) {
        func_001F53C0(1, func_001F5380(), g->cam3.pos);
    }
    func_001F5620(func_001F53A0(), g->j2, g->cam5.pos);
    func_00103DB0(g->cam4.pos, g->cam5.pos, g->cam5.rot);
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001038D0(&g->cam4);
    func_001039A0(&g->cam3);
    func_001038D0(&g->cam5);
    if (g->t < 0x154) {
        func_01E00120_b364();
    }
    if (g->t < 0x154) {
        func_00103470((u8 *)&g->vol, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->vol, 0x80, 4);
    }
    func_001F6D00((u8)g->vol);
    if (g->t < 0x6A) {
        v0.x = v0.y = v0.z = 1.01f;
        func_01E01F00_b364(ot, (Cam_b001_01E00A30 *)&g->cam2, (Emit_b001_01E00A30 *)&g->em,
                           (Vec_b001_01E00A30 *)&v0);
        if (g->t >= 0x5A) {
            func_00103470(&g->em.color.a, 0, 10);
        }
    }
    if (g->t >= 0x69) {
        func_01E02B80_b364(ot, (Grid_b364_01E02B80 *)&g->ball, (Cam_b364_01E02B80 *)&g->cam4);
        if (g->t > 0xB4) {
            g->ball.color.r = func_0019A5C8() % 128;
            g->ball.color.g = func_0019A5C8() % 128;
            g->ball.color.b = func_0019A5C8() % 128;
            if (g->t < 0xDC) {
                func_001033D0(&g->cam4, 1.0f, 0.1f);
            }
            func_001032C0(&g->ball.color.a, 0x80, 8);
            g->cam4.rot[1] += 0x800;
        }
        if (g->t > 0xDC && g->t < 0x154) {
            func_001F62B0(func_001F5380(), &g->cam4);
            { f32 fs2 = 0.05f; func_00103580(&g->cam4, 0.0f, fs2); }
        }
        if (func_00104520(g->flags, 0x1F) == 0) {
            if (g->t > 0xE6) {
                g->mdl2.color.r = func_0019A5C8() % 128;
                g->mdl2.color.g = func_0019A5C8() % 128;
                g->mdl2.color.b = func_0019A5C8() % 128;
                func_01E00590_b364(ot, (Model_b013_01E004E0 *)&g->mdl2, (Fx_b013_01E004E0 *)&g->fx2,
                                   (Cam_b013_01E004E0 *)&g->cam3);
                if (g->t < 0x110) {
                    { extern s32 func_001033D0(void *, f32, f32); func_001033D0(&g->cam3, 1.0f, 0.1f); }
                }
            }
            if (g->t >= 0x110) {
                func_00104490(g->cam3.pos, &g->vec, g->lag);
                { extern void func_00103580(void *, f32, f32); f32 fs1 = 0.2f; func_00103580(&g->cam3, fs1, 0.03f); }
                if (g->lag != 0) {
                    g->lag--;
                    g->ang += 0x444;
                    g->cam3.pos[1] += 5.0f * func_0020B550(g->ang);
                } else {
                    g->cam3.x = g->cam3.y = g->cam3.z = 1.0f;
                    g->flags |= 0x80000000;
                }
            }
        } else {
            g->spark.color.r = func_0019A5C8() % 128;
            g->spark.color.g = func_0019A5C8() % 128;
            g->spark.color.b = func_0019A5C8() % 128;
            v1.x = v1.y = v1.z = 1.02f;
            func_01E01170_b364(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)&g->cam3, (s32)&v1);
            func_00103470(&g->spark.color.a, 0, 8);
        }
        if (g->t < 0x154) {
            func_01E00590_b364(ot, (Model_b013_01E004E0 *)&g->mdl, (Fx_b013_01E004E0 *)&g->fx,
                               (Cam_b013_01E004E0 *)&g->cam1);
            if (g->t > 0x105) {
                func_01E01A10_b364(ot, (Ring_b001_01E03860 *)&g->ring0, (Cam_b001_01E03860 *)&g->cam1);
                func_01E01A10_b364(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)&g->cam1);
            }
        }
        if (g->t > 0xC2) {
            func_01E033B0_b364(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->cam1);
        }
        if (g->t > 0x154) {
            func_00103470(&g->spr.color.a, 0, 2);
            func_00103470(&g->ring0.color.a, 0, 2);
            func_00103470(&g->ring1.color.a, 0, 3);
            func_00103470(&g->mdl.color.a, 0, 6);
        } else {
            { f32 fs1 = 1.0f; f32 fs2 = 0.1f; func_001033D0(&g->cam1, fs1, fs2); }
        }
        for (i = 0; i < 64; i++) {
            g->spr.r[i].a += 0x80;
            g->spr.r[i].b += 0x80;
            g->spr.r[i].c += 0x80;
        }
        g->mdl.color.r = g->ring0.color.r = g->ring1.color.r = g->spr.color.r = func_0019A5C8() % 128;
        g->mdl.color.g = g->ring0.color.g = g->ring1.color.g = g->spr.color.g = func_0019A5C8() % 128;
        g->mdl.color.b = g->ring0.color.b = g->ring1.color.b = g->spr.color.b = func_0019A5C8() % 128;
    }
    if (g->t >= 0x2D) {
        g->beam.color.b = func_0019A5C8() % 0x60 + 0x60;
        func_01E03AC0_b364(ot, (Beam_b047_01E01270 *)&g->beam, (Cam_b047_01E01270 *)&g->cam5);
        if (g->t >= 0x7A) {
            { extern void func_00103540(void *, f32, f32); func_00103540(&g->beam.speed, 0.0f, 0.05f); }
        }
        if (g->t >= 0xB8) {
            func_00103470(&g->beam.color.a, 0, 10);
        }
        g->beam.rows++;
    }
    g->t++;
    g->timer--;
    if (g->t == 0x154) {
        func_001F62B0(func_001F5380(), g);
        return 2;
    }
    if (g->t == 0xB0) {
        return 1;
    }
    if (g->t > 0xBC && g->t < 0xEC) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
