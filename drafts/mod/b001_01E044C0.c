#include "common.h"
#include "mod/b001.c"

/* shape b001:01E044C0 (b001), 738 insns, 1 copy: b001 scene manager: code >= 0 sets up seven coords, two joints, a
   380-tick timer, a disc, a model shot, a light, two tall rings, four flat rings, an 8-point spark emitter and a
   256-point rising emitter; else follows the joints, fades, draws disc, rings, light and shot 40..180 (camera shakes
   from 151), the sparks from 358, the tall rings and the emitter from 181 (points rise 2/4/6 by i % 3, respawn above
   35; everything shrinks and fades from 340); returns 2 at 340, 1 at 171, 6 in 181..339, 8 when the timer ends */

typedef struct {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b001_01E044C0;

typedef struct {
    s32 a, b, c, d;
} Rnd_b001_01E044C0;

typedef struct {
    s32 kind;
    s32 model;
    u8 b, g, r, a;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[0x48];
    Rnd_b001_01E044C0 rnd[64];
} Light_b001_01E044C0;

typedef struct {
    s32 f0;
    u8 b, g, r, a;
    f32 size;
    s16 n;
    s16 id;
} Shot_b001_01E044C0;

typedef struct {
    s32 type;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 rest[0x3E8];
} Ring_b001_01E044C0;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt3_b001_01E044C0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 cx, cy;
    s32 x18;
    u8 pad1C[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Pt3_b001_01E044C0 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 h136;
    s16 h138;
    s16 h13A;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Em3_b001_01E044C0;

typedef struct {
    Crd_b001_01E044C0 cam0;
    Crd_b001_01E044C0 cam1;
    Disc_b540_01E00250 disc;
    Shot_b001_01E044C0 shot;
    Light_b001_01E044C0 light;
    Crd_b001_01E044C0 cam2;
    Ring_b001_01E044C0 ring[4];
    Crd_b001_01E044C0 cam3;
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[0x100];
    Crd_b001_01E044C0 cam4;
    Ring_b001_01E044C0 ringA;
    Crd_b001_01E044C0 cam5;
    Ring_b001_01E044C0 ringB;
    Crd_b001_01E044C0 cam6;
    Em3_b001_01E044C0 em3;
    u8 col[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 j0;
    s32 j1;
    s32 alpha;
    u8 pad315C[4];
} Scene_b001_01E044C0;

static s32 func_01E044C0_b001(s32 arg0, s32 code) {
    Scene_b001_01E044C0 *g = (Scene_b001_01E044C0 *)arg0;
    extern u8 D_01E05100_b001;
    extern void func_00199B50(void *, s32);
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6D00(s32);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern void func_00103580(void *, f32, f32);
    extern void func_00103540(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    Vec_b001_01E00A30 vel;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 a;
    f32 r;

    ot = func_00207500();
    if (code >= 0) {
        func_00199B50(&D_01E05100_b001, 0x3160);
        func_00195108(g, 0x3160);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        func_00103890(&g->cam5);
        func_00103890(&g->cam6);
        g->j0 = func_001F5560(func_001F53A0(), 0x12, 1);
        g->j1 = func_001F5560(func_001F53A0(), 1, 0);
        g->timer = 0x17C;
        g->t = 1;
        g->code = code;
        g->alpha = 0x80;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        g->col[3] = 0xFF;
        g->disc.flags = 0;
        g->disc.r = 0x70;
        g->disc.g = 0xB0;
        g->disc.b = 0xE0;
        g->disc.a = 0;
        g->disc.radius = 20.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        g->shot.f0 = 0;
        g->shot.r = 0x60;
        g->shot.g = 0x60;
        g->shot.b = 0x80;
        g->shot.a = 0;
        g->shot.size = 0.3f;
        g->shot.n = 10;
        g->shot.id = func_001F53A0();
        func_00103260(tx, 0xF);
        g->light.model = 0x40001;
        g->light.u = 0x8E;
        g->light.v = 0;
        g->light.w = 0x22;
        g->light.h = 0x40;
        g->light.r = 0xD0;
        g->light.g = 0xA0;
        g->light.b = 0x70;
        g->light.a = 0;
        func_01E03D50_b001((Obj_b000_01E032C0 *)&g->light, tx[0], 0.8f);
        g->ringA.flags = 0;
        g->ringA.u = 0x8E;
        g->ringA.v = 0;
        g->ringA.w = 0x20;
        g->ringA.h = 0x80;
        g->ringA.r = 0x70;
        g->ringA.g = 0xB0;
        g->ringA.b = 0xE0;
        g->ringA.a = 0x20;
        r = 18.0f;
        func_01E035A0_b001((Ring_b001_01E035A0 *)(&g->cam4 + 1), tx[0], r, r, 0.0f, 80.0f);
        g->ringB.flags = 0;
        g->ringB.u = 0x8E;
        g->ringB.v = 0;
        g->ringB.w = 0x20;
        g->ringB.h = 0x80;
        g->ringB.r = 0x70;
        g->ringB.g = 0xB0;
        g->ringB.b = 0xE0;
        g->ringB.a = 0x20;
        r = 18.0f;
        func_01E035A0_b001((Ring_b001_01E035A0 *)&g->ringB.type, tx[0], r, r, -40.0f, 80.0f);
        for (i = 0; i < 4; i++) {
            r = 6.0f * (f32)(i + 1);
            g->ring[i].flags = 0x20000000;
            g->ring[i].u = 0x8E;
            g->ring[i].v = 0;
            g->ring[i].w = 0x20;
            g->ring[i].h = 0x80;
            g->ring[i].r = 0x70;
            g->ring[i].g = 0xB0;
            g->ring[i].b = 0xE0;
            g->ring[i].a = 0;
            func_01E035A0_b001((Ring_b001_01E035A0 *)&g->ring[i], tx[0], r, r - 4.0f, 0.0f, 0.0f);
        }
        func_00103290(tx, 0);
        g->em3.texture = (void *)tx[0];
        g->em3.flags = 0x80007;
        g->em3.cx = 0.0f;
        g->em3.cy = 0.0f;
        g->em3.x18 = 0;
        g->em3.u = 0;
        g->em3.v = 0;
        g->em3.w = 0x20;
        g->em3.h = 0x20;
        g->em3.u0 = 0;
        g->em3.v0 = 0;
        g->em3.tw = 0x80;
        g->em3.th = 0x40;
        g->em3.size = 1.0f;
        g->em3.count = 0x10;
        g->em3.h13A = 1;
        g->em3.h13C = 0;
        g->em3.h140 = 4;
        g->em3.h136 = 10;
        g->em3.h138 = 10;
        g->em3.r = 0x80;
        g->em3.g = 0x80;
        g->em3.b = 0x80;
        g->em3.a = 0x40;
        for (i = 0; i < 8; i++) {
            g->em3.pts[i].x = func_0019A5C8() % 20 - 10;
            g->em3.pts[i].y = func_0019A5C8() % 20 - 10;
            g->em3.pts[i].life = -g->em3.h13A * i;
            g->em3.pts[i].pad = 0;
            g->em3.h13E = g->em3.h140 - 1;
        }
        g->emit.texture = (void *)tx[0];
        g->emit.flags = 0x50000003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x80;
        g->emit.size = 12.0f;
        *(s32 *)&g->emit.rot.x = 0;
        *(s32 *)&g->emit.rot.y = 0x400;
        *(s32 *)&g->emit.rot.z = 0;
        g->emit.r.i.u = 0;
        g->emit.r.i.v = 0;
        g->emit.r.i.w = 0x20;
        g->emit.r.i.h = 0x20;
        g->emit.r.i.u0 = 0;
        g->emit.r.i.v0 = 0;
        g->emit.r.i.tw = 0x80;
        g->emit.r.i.th = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = NULL;
        *(s32 *)g->emit.pad48 = 0;
        g->emit.radius = 15.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        func_01E01B20_b001((Ring_b001_01E01B20 *)&g->emit, 12.0f);
        for (i = 0; i < g->emit.count; i++) {
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0;
            g->pts[i].frame = 0;
            g->pts[i].y -= 35.0f;
        }
        g->cam1.scale.y = 1.5f;
        func_001F5F90(func_001F5380(), &g->cam6.pos);
        func_001F53C0(1, func_001F5380(), &g->cam3.pos);
        g->cam3.scale.x = g->cam3.scale.z = 0.1f;
        g->cam3.pos.y = 50.0f;
        func_001F53C0(1, func_001F5380(), &g->cam4.pos);
        g->cam4.scale.x = g->cam4.scale.z = 0.1f;
        g->cam4.pos.y = 15.0f;
        func_001F53C0(1, func_001F5380(), &g->cam5.pos);
        g->cam5.scale.x = g->cam5.scale.z = 0.1f;
        g->cam5.pos.y = 55.0f;
        return 0;
    }
    func_001F53C0(1, func_001F53A0(), &g->cam1.pos);
    func_001F53C0(1, func_001F53A0(), &g->cam2.pos);
    g->cam4.rot[1] += 0x400;
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001038D0(&g->cam3);
    func_001038D0(&g->cam4);
    func_001038D0(&g->cam5);
    func_001039A0(&g->cam6);
    if (g->t <= 0x95) {
        func_00103470((u8 *)&g->alpha, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->alpha, 0x80, 4);
    }
    func_001F6D00(*(u8 *)&g->alpha);
    if (g->t >= 0x157) {
        func_01E00120_b001(ot, (Src_b000_01E00400 *)g->col);
        func_00103470(&g->col[3], 0, 8);
    }
    if (g->t >= 0x28 && g->t <= 0xB4) {
        func_01E00900_b001();
        func_01E015C0_b001(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam1);
        func_001032C0(&g->disc.a, 0xFF, 0x10);
        for (i = 0; i < 4; i++) {
            func_01E03860_b001(ot, (Ring_b001_01E03860 *)&g->ring[i], (Cam_b001_01E03860 *)&g->cam2);
            func_001032C0(&g->ring[i].a, 0x40, 4);
        }
        func_01E03EB0_b001(ot, (Spr_b000_01E03420 *)&g->light, (Cam_b000_01E03420 *)&g->cam1);
        func_001032C0(&g->light.a, 0x10, 1);
        for (i = 0; i < 64; i++) {
            g->light.rnd[i].a += 0x40;
            g->light.rnd[i].b += 0x40;
            g->light.rnd[i].c += 0x40;
        }
        func_01E00280_b001((Obj_b000_01E00560 *)&g->shot, &g->cam1.pos);
        func_001032C0(&g->shot.a, 0x40, 4);
        if (g->t > 0x96) {
            func_001033D0(&g->cam2, 15.0f, 1.0f);
            func_001033D0(&g->cam1, 10.0f, 0.1f);
        }
    }
    if (g->t >= 0x166) {
        vel.x = vel.y = vel.z = 0.0f;
        func_01E00A30_b001(ot, (Cam_b001_01E00A30 *)&g->cam6, (Emit_b001_01E00A30 *)&g->em3, &vel);
        func_00103470(&g->em3.a, 0, 2);
    }
    if (g->t >= 0xB5) {
        func_01E03860_b001(ot, (Ring_b001_01E03860 *)&g->ringA, (Cam_b001_01E03860 *)&g->cam4);
        func_01E03860_b001(ot, (Ring_b001_01E03860 *)&g->ringB, (Cam_b001_01E03860 *)&g->cam5);
        if (g->t >= 0x154) {
            {
                f32 q = 0.05f;
                func_00103580(&g->cam4, 0.03f, q);
            }
            g->cam4.scale.y = 1.0f;
            func_00103470(&g->ringA.a, 0, 6);
            g->cam5.scale.x += 0.4f;
            g->cam5.scale.z += 0.4f;
            func_00103540(&g->cam5.scale.y, 0.03f, 0.08f);
            func_00103470(&g->ringB.a, 0, 8);
            func_00103580(&g->cam3, 0.03f, 0.05f);
            g->cam3.scale.y = 1.0f;
            func_00103470(&g->emit.color.a, 0, 6);
        } else {
            func_001032C0(&g->ringB.a, 0x80, 1);
            func_001032C0(&g->ringA.a, 0x60, 1);
            func_001033D0(&g->cam4, 1.0f, 0.025f);
            func_001033D0(&g->cam3, 1.0f, 0.025f);
        }
        func_01E01CB0_b001(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam3);
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts[i].t >= 0) {
                if (i % 3 == 0) {
                    g->pts[i].y += 2.0f;
                } else if (i % 3 == 1) {
                    g->pts[i].y += 4.0f;
                } else {
                    g->pts[i].y += 6.0f;
                }
                g->pts[i].a = 0x80;
                if (g->pts[i].y > 35.0f) {
                    a = func_0019A5C8() % 0x10000;
                    g->pts[i].z = g->emit.radius * func_0020B480(a);
                    g->pts[i].x = g->emit.radius * func_0020B550(a);
                    g->pts[i].y = -(f32)(func_0019A5C8() % 10) - 35.0f;
                    g->pts[i].a = 0;
                }
            }
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x154) {
        return 2;
    }
    if (g->t == 0xAB) {
        return 1;
    }
    if (g->t >= 0xB5 && g->t < 0x154) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
