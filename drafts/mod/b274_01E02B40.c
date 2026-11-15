#include "common.h"

/* shape b274:01E02B40 (b274), 905 insns, 1 copy: b274 scene manager (b419:01E02B40's form with a third emitter): code
   >= 0 sets up two trails, two discs/band sprites and three 128-particle emitters; else follows joints 9/10 until 50,
   then homes on the camera sides with trails, flashes from 68, emitters 1/2 and trails 50..83, emitter 3 from 50
   (bits respawn on a unit sphere); returns 2/1/6/8 by tick. HARD: 2 words, emit2's func_01E011A0 call schedules addiu
   a0 before mtc1  (emit1's order wanted) */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b274_01E02B40;

typedef struct {
    s32 tex;
    u8 c[4];
    s32 flags;
    f32 size;
    s16 uv[8];
    u8 pad20[0x10];
    f32 rate;
    s16 a;
    s16 b;
    s16 c34;
    s16 count;
    s16 e;
    u8 pad3E[2];
} Spot_b274_01E02B40;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Pt_b274_01E02B40;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b274_01E02B40;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 scale;
    u8 c[4];
    s32 mode;
    u8 pad3C[0xC];
    s16 s[6];
    u8 pad54[0xC];
} Band_b274_01E02B40;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Aux_b274_01E02B40;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Pt_b274_01E02B40 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 life;
    u8 f2F;
} Emit_b274_01E02B40;

typedef struct {
    Crd_b274_01E02B40 m0;
    Spot_b274_01E02B40 trail1;
    Pt_b274_01E02B40 pts1[24];
    Spot_b274_01E02B40 trail2;
    Pt_b274_01E02B40 pts2[24];
    Crd_b274_01E02B40 cam1;
    Disc_b274_01E02B40 disc1;
    Band_b274_01E02B40 band1;
    Aux_b274_01E02B40 aux1;
    Crd_b274_01E02B40 cam2;
    Disc_b274_01E02B40 disc2;
    Band_b274_01E02B40 band2;
    Aux_b274_01E02B40 aux2;
    Crd_b274_01E02B40 cam3;
    Crd_b274_01E02B40 cam4;
    Crd_b274_01E02B40 cam5;
    Emit_b274_01E02B40 emit1;
    Pt_b274_01E02B40 parts1[128];
    Crd_b274_01E02B40 cam6;
    Emit_b274_01E02B40 emit2;
    Pt_b274_01E02B40 parts2[128];
    Crd_b274_01E02B40 cam7;
    Emit_b274_01E02B40 emit3;
    Pt_b274_01E02B40 parts3[128];
    s32 timer;
    s32 t;
    s32 code;
    s32 cnt1;
    s32 cnt2;
    s32 ja;
    s32 jb;
    u8 c[4];
} Scene_b274_01E02B40;


static s32 func_01E02B40_b274(s32 arg0, s32 code) {
    Scene_b274_01E02B40 *g = (Scene_b274_01E02B40 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_001043F0(void *, f32);
    extern s32 func_001A22C0(f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001033D0(void *, f32, f32);
    extern s32 func_0019A5C8();
    Vec4f v[2];
    Vec4f q;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 r;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x20D0);
        func_00103890(&g->m0);
        func_00103890(&g->cam1);
        g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        func_00103890(&g->cam2);
        g->cam2.x = g->cam2.y = g->cam2.z = 0.1f;
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        func_00103890(&g->cam5);
        func_00103890(&g->cam6);
        func_00103890(&g->cam7);
        g->ja = func_001F5560(func_001F53A0(), 9, 1);
        g->jb = func_001F5560(func_001F53A0(), 0xA, 0);
        g->timer = 0x64;
        g->t = 1;
        g->code = code;
        g->cnt1 = 0x12;
        g->cnt2 = 0x12;
        g->c[2] = 0x80;
        g->c[1] = 0xA0;
        g->c[0] = 0xC0;
        g->c[3] = 0;
        g->disc1.flags = 0;
        g->disc1.c[2] = 0x60;
        g->disc1.c[1] = 0x80;
        g->disc1.c[0] = 0xA0;
        g->disc1.c[3] = 0;
        g->disc1.radius = 4.0f;
        g->disc1.count = 0x24;
        g->disc1.height = 0;
        g->disc2.flags = 0;
        g->disc2.c[2] = 0x60;
        g->disc2.c[1] = 0x80;
        g->disc2.c[0] = 0xA0;
        g->disc2.c[3] = 0;
        g->disc2.radius = 4.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        func_00103290(tx, 2);
        g->band1.mode = 3;
        g->band1.uv[0] = 0;
        g->band1.uv[1] = 0;
        g->band1.uv[2] = 0x40;
        g->band1.uv[3] = 0x40;
        g->band1.uv[4] = 0;
        g->band1.uv[5] = 0;
        g->band1.uv[6] = 0x80;
        g->band1.uv[7] = 0x80;
        g->band1.scale = 1.0f;
        g->band1.c[2] = 0x80;
        g->band1.c[1] = 0x80;
        g->band1.c[0] = 0x80;
        g->band1.c[3] = 0;
        g->band1.s[0] = 0;
        g->band1.s[1] = 2;
        g->band1.s[2] = 3;
        g->band1.s[3] = 4;
        g->band1.s[4] = 0;
        g->band1.s[5] = 999;
        r = tx[0];
        g->aux1.z = 0.0f;
        g->aux1.y = 0.0f;
        g->aux1.x = 0.0f;
        g->aux1.scale = 3.0f;
        g->aux1.tex = r;
        g->aux1.c[2] = 0x80;
        g->aux1.c[1] = 0x80;
        g->aux1.c[0] = 0x80;
        g->aux1.c[3] = 0x80;
        g->band2.mode = 3;
        g->band2.uv[0] = 0;
        g->band2.uv[1] = 0;
        g->band2.uv[2] = 0x40;
        g->band2.uv[3] = 0x40;
        g->band2.uv[4] = 0;
        g->band2.uv[5] = 0;
        g->band2.uv[6] = 0x80;
        g->band2.uv[7] = 0x80;
        g->band2.scale = 1.0f;
        g->band2.c[2] = 0x80;
        g->band2.c[1] = 0x80;
        g->band2.c[0] = 0x80;
        g->band2.c[3] = 0;
        g->band2.s[0] = 0;
        g->band2.s[1] = 2;
        g->band2.s[2] = 3;
        g->band2.s[3] = 4;
        g->band2.s[4] = 0;
        g->band2.s[5] = 999;
        r = tx[0];
        g->aux2.z = 0.0f;
        g->aux2.y = 0.0f;
        g->aux2.x = 0.0f;
        g->aux2.scale = 3.0f;
        g->aux2.tex = r;
        g->aux2.c[2] = 0x80;
        g->aux2.c[1] = 0x80;
        g->aux2.c[0] = 0x80;
        g->aux2.c[3] = 0x80;
        func_00103290(tx, 0);
        g->trail1.tex = tx[0];
        g->trail1.c[2] = 0x80;
        g->trail1.c[1] = 0x80;
        g->trail1.c[0] = 0x80;
        g->trail1.c[3] = 0x30;
        g->trail1.flags = 0x8003;
        g->trail1.size = 20.0f;
        g->trail1.uv[0] = 0x9C;
        g->trail1.uv[1] = 0;
        g->trail1.uv[2] = 0x40;
        g->trail1.uv[3] = 0x40;
        g->trail1.uv[4] = 0x9C;
        g->trail1.uv[5] = 0;
        g->trail1.uv[6] = 0x100;
        g->trail1.uv[7] = 0x80;
        g->trail1.rate = 0.05f;
        g->trail1.a = 0;
        g->trail1.b = 0x10;
        g->trail1.c34 = 0x18;
        g->trail1.count = 0;
        g->trail1.e = 1;
        g->trail2.tex = tx[0];
        g->trail2.c[2] = 0x80;
        g->trail2.c[1] = 0x80;
        g->trail2.c[0] = 0x80;
        g->trail2.c[3] = 0x30;
        g->trail2.flags = 0x8003;
        g->trail2.size = 20.0f;
        g->trail2.uv[0] = 0x9C;
        g->trail2.uv[1] = 0;
        g->trail2.uv[2] = 0x40;
        g->trail2.uv[3] = 0x40;
        g->trail2.uv[4] = 0x9C;
        g->trail2.uv[5] = 0;
        g->trail2.uv[6] = 0x100;
        g->trail2.uv[7] = 0x80;
        g->trail2.rate = 0.05f;
        g->trail2.a = 0;
        g->trail2.b = 0x10;
        g->trail2.c34 = 0x18;
        g->trail2.count = 0;
        g->trail2.e = 1;
        func_00103290(tx, 1);
        g->emit1.tex = tx[0];
        g->emit1.flags = 0x20000003;
        g->emit1.c[2] = 0x80;
        g->emit1.c[1] = 0x80;
        g->emit1.c[0] = 0x80;
        g->emit1.c[3] = 0x80;
        g->emit1.f20 = 0.5f;
        g->emit1.f24 = 5.0f;
        g->emit1.uv[0] = 0;
        g->emit1.uv[1] = 0;
        g->emit1.uv[2] = 0x20;
        g->emit1.uv[3] = 0x20;
        g->emit1.uv[4] = 0;
        g->emit1.uv[5] = 0;
        g->emit1.uv[6] = 0x80;
        g->emit1.uv[7] = 0x40;
        g->emit1.parts = g->parts1;
        g->emit1.radius = 5.0f;
        g->emit1.count = 0x80;
        g->emit1.life = 8;
        g->emit1.f2F = 0;
        func_01E011A0_b274((Obj_b015_01E01620 *)&g->emit1, 0xC, 4.0f);
        g->emit2.tex = tx[0];
        g->emit2.flags = 0x20000003;
        g->emit2.c[2] = 0x80;
        g->emit2.c[1] = 0x80;
        g->emit2.c[0] = 0x80;
        g->emit2.c[3] = 0x80;
        g->emit2.f20 = 0.5f;
        g->emit2.f24 = 5.0f;
        g->emit2.uv[0] = 0;
        g->emit2.uv[1] = 0;
        g->emit2.uv[2] = 0x20;
        g->emit2.uv[3] = 0x20;
        g->emit2.uv[4] = 0;
        g->emit2.uv[5] = 0;
        g->emit2.uv[6] = 0x80;
        g->emit2.uv[7] = 0x40;
        g->emit2.parts = g->parts2;
        g->emit2.radius = 5.0f;
        g->emit2.count = 0x80;
        g->emit2.life = 8;
        g->emit2.f2F = 0;
        func_01E011A0_b274((Obj_b015_01E01620 *)&g->emit2, 0xC, 4.0f);
        g->emit3.tex = tx[0];
        g->emit3.flags = 3;
        g->emit3.c[2] = 0x80;
        g->emit3.c[1] = 0x80;
        g->emit3.c[0] = 0x80;
        g->emit3.c[3] = 0;
        g->emit3.f20 = 0.5f;
        g->emit3.f24 = 5.0f;
        g->emit3.uv[0] = 0;
        g->emit3.uv[1] = 0;
        g->emit3.uv[2] = 0x20;
        g->emit3.uv[3] = 0x20;
        g->emit3.uv[4] = 0;
        g->emit3.uv[5] = 0;
        g->emit3.uv[6] = 0x80;
        g->emit3.uv[7] = 0x40;
        g->emit3.parts = g->parts3;
        g->emit3.radius = 5.0f;
        g->emit3.count = 0x80;
        g->emit3.life = 8;
        g->emit3.f2F = 0;
        func_01E011A0_b274((Obj_b015_01E01620 *)&g->emit3, 0xC, 4.0f);
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->cam3.pos);
    func_001F5F90(func_001F5380(), &g->cam4.pos);
    if (g->t < 0x32) {
        func_001F5620(func_001F53A0(), g->ja, &g->cam1.pos);
        func_001F5620(func_001F53A0(), g->jb, &g->cam2.pos);
    } else {
        func_00104490(&g->cam1.pos, &g->cam3.pos, g->cnt1);
        if (g->cnt1 != 0) {
            g->cnt1--;
        }
        func_01E020C0_b274((Trail_b025_01E01EF0 *)&g->trail1, (Pt_b025_01E01EF0 *)g->pts1,
                           (Vec_b025_01E01EF0 *)&g->cam1.pos);
        func_00104490(&g->cam2.pos, &g->cam4.pos, g->cnt2);
        if (g->cnt2 != 0) {
            g->cnt2--;
        }
        func_01E020C0_b274((Trail_b025_01E01EF0 *)&g->trail2, (Pt_b025_01E01EF0 *)g->pts2,
                           (Vec_b025_01E01EF0 *)&g->cam2.pos);
    }
    func_001F5F90(func_001F53A0(), &v[0]);
    g->cam5.pos = g->cam7.pos = g->cam1.pos;
    func_00103DB0(&v[0], &g->cam3.pos, &g->cam5.rot);
    func_001F5F90(func_001F53A0(), &v[1]);
    g->cam6.pos = g->cam2.pos;
    func_00103DB0(&v[1], &g->cam4.pos, &g->cam6.rot);
    func_001038D0(&g->m0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001039A0(&g->cam3);
    func_001039A0(&g->cam4);
    func_001038D0(&g->cam5);
    func_001038D0(&g->cam6);
    func_001038D0(&g->cam7);
    if (g->t >= 0x32 && g->t < 0x9E) {
        func_01E00120_b274();
    }
    if (g->t >= 0x44) {
        func_01E00250_b274(ot, (Src_b000_01E00400 *)g->c);
        if (g->t < 0x54) {
            func_001032C0(&g->c[3], 0xFF, 0x10);
        } else {
            func_00103470(&g->c[3], 0, 0x20);
        }
    }
    func_01E003B0_b274(ot, (Disc_b540_01E00250 *)&g->disc1, (Cam_b540_01E00250 *)&g->cam1);
    func_01E003B0_b274(ot, (Disc_b540_01E00250 *)&g->disc2, (Cam_b540_01E00250 *)&g->cam2);
    func_01E00910_b274(ot, (Spr_b000_01E02A30 *)&g->band1, (Part_b000_01E02A30 *)&g->aux1,
                       (Cam_b000_01E02A30 *)&g->cam1);
    func_01E00910_b274(ot, (Spr_b000_01E02A30 *)&g->band2, (Part_b000_01E02A30 *)&g->aux2,
                       (Cam_b000_01E02A30 *)&g->cam2);
    if (g->t < 0x32) {
        func_001033D0(&g->cam1, 1.0f, 0.05f);
        func_001032C0(&g->disc1.c[3], 0xFF, 0x20);
        func_001032C0(&g->band1.c[3], 0x80, 0x10);
        { extern void func_001033D0(void *, f32, f32); f32 fs2 = 0.05f; func_001033D0(&g->cam2, 1.0f, fs2); }
        func_001032C0(&g->disc2.c[3], 0xFF, 0x20);
        func_001032C0(&g->band2.c[3], 0x80, 0x10);
    }
    if (g->t >= 0x32 && g->t < 0x54) {
        func_01E01360_b274(ot, (Emit_b489_01E00240 *)&g->emit1, (Cam_b489_01E00240 *)&g->cam5);
        if (g->t > 0x54) {
            func_00103470(&g->emit1.c[3], 0, 8);
        }
        for (i = 0; i < g->emit1.count; i++) {
            if (g->parts1[i].t >= 0) {
                g->parts1[i].x *= 1.2f;
                g->parts1[i].y *= 1.2f;
                g->parts1[i].z *= 1.2f;
                if (g->parts1[i].y > 30.0f) {
                    r = func_001A22C0(10.0f * g->emit1.radius);
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (f32)(func_0019A5C8() % r);
                    g->parts1[i].y = 4.0f;
                    g->parts1[i].z = d * func_0020B480(a);
                    g->parts1[i].x = d * func_0020B550(a);
                    g->parts1[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
        func_01E01360_b274(ot, (Emit_b489_01E00240 *)&g->emit2, (Cam_b489_01E00240 *)&g->cam6);
        if (g->t > 0x54) {
            func_00103470(&g->emit2.c[3], 0, 8);
        }
        for (i = 0; i < g->emit2.count; i++) {
            if (g->parts2[i].t >= 0) {
                g->parts2[i].x *= 1.2f;
                g->parts2[i].y *= 1.2f;
                g->parts2[i].z *= 1.2f;
                if (g->parts2[i].y > 30.0f) {
                    r = func_001A22C0(10.0f * g->emit2.radius);
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (f32)(func_0019A5C8() % r);
                    g->parts2[i].y = 4.0f;
                    g->parts2[i].z = d * func_0020B480(a);
                    g->parts2[i].x = d * func_0020B550(a);
                    g->parts2[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
        func_01E021A0_b274(ot, (Em_b025_01E01FD0 *)&g->trail1, (Part_b025_01E01FD0 *)g->pts1,
                           (Cam_b025_01E01FD0 *)&g->m0);
        for (i = 0; i < g->trail1.count; i++) {
            func_00103470(&g->pts1[i].c, 0, 3);
        }
        func_01E021A0_b274(ot, (Em_b025_01E01FD0 *)&g->trail2, (Part_b025_01E01FD0 *)g->pts2,
                           (Cam_b025_01E01FD0 *)&g->m0);
        for (i = 0; i < g->trail2.count; i++) {
            func_00103470(&g->pts2[i].c, 0, 3);
        }
    }
    if (g->t == 0x54) {
        g->emit3.c[3] = 0x80;
        for (i = 0; i < g->emit3.count; i++) {
            g->parts3[i].c = 0x80;
        }
    }
    if (g->t >= 0x32) {
        func_01E01360_b274(ot, (Emit_b489_01E00240 *)&g->emit3, (Cam_b489_01E00240 *)&g->cam7);
        if (g->t > 0x54) {
            func_00103470(&g->emit3.c[3], 0, 8);
        }
        for (i = 0; i < g->emit3.count; i++) {
            if (g->parts3[i].t >= 0) {
                g->parts3[i].x *= 1.4f;
                g->parts3[i].y *= 1.4f;
                g->parts3[i].z *= 1.4f;
                if (g->parts3[i].t > 8) {
                    { extern void func_001043F0(void *, f32); func_001043F0(&q, 1.0f); }
                    g->parts3[i].y = q.y;
                    g->parts3[i].z = q.z;
                    g->parts3[i].x = q.x;
                    g->parts3[i].t = -(func_0019A5C8() % 12);
                    g->parts3[i].c = g->emit3.c[3];
                }
            }
        }
    }
    if (g->cnt1 == 0) {
        { extern void func_001033D0(void *, f32, f32); f32 fs2 = 1.0f; func_001033D0(&g->cam1, 10.0f, fs2); }
        func_00103470(&g->disc1.c[3], 0, 0x10);
        func_00103470(&g->band1.c[3], 0, 8);
        func_00103470(&g->trail1.c[3], 0, 5);
    }
    if (g->cnt2 == 0) {
        func_001033D0(&g->cam2, 10.0f, 1.0f);
        func_00103470(&g->disc2.c[3], 0, 0x10);
        func_00103470(&g->band2.c[3], 0, 8);
        func_00103470(&g->trail2.c[3], 0, 5);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x54) {
        return 2;
    }
    if (g->t == 0x3A) {
        return 1;
    }
    if (g->t >= 0x44 && g->t < 0x54) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
