#include "common.h"

/* shape b131:01E06510 (b131), 658 insns, 1 copy: b131 scene manager (b029:01E05F20 form): code -3/-2 returns 8; code
   >= 0 clears the scene (0x2690), takes both units, the camera and four joints and sets up the walk emitters; else
   counts the frame: 2 and 0x31/0x160 set up the follow particles and the emitter, 0x10A the trail, 0x118 the trail
   emitter, 0x11A five sparks, three rings, the flare and the emitter at the joint, 0x1B8 returns 8; steps every
   effect; returns 1/2 on frames 0x110/0x117 */

typedef struct {
    s32 a;
    s32 b;
    u8 pad8[0xC];
} Cam_b131_01E06510;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 b6;
    u8 pad7[0xD];
    f32 f14;
    f32 f18;
    f32 f1C;
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b131_01E06510;

typedef struct {
    s16 a;
    s16 b;
} Wv_b131_01E06510;

typedef struct {
    void *emits;
    void *parts;
    s16 *frames[2];
    u8 pad10[0x18];
    u8 bone[2];
    u8 pad2A[6];
    u8 emit_kind;
    u8 part_kind;
    u8 kind;
    u8 bone2;
    s16 lo;
    s16 hi;
    f32 x0;
    f32 x1;
    f32 y;
} Walk_b131_01E06510;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[3];
    void *p8;
    s16 h0C[9];
    s16 h1E[9];
    u8 b30;
    u8 b31;
    u8 b32;
    u8 b33;
    u8 pad34[4];
    f32 f38;
    u8 pad3C[8];
    u8 c[4];
    u8 b48;
    u8 b49;
    u8 b4A;
    u8 pad4B[0x15];
    u8 buf[0x320];
} Trl_b131_01E06510;

typedef struct {
    u8 age;
    u8 pad1[3];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA[2];
    s8 *tbl;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 c1C[4];
    u8 c20[4];
    Vec4f pos;
    u8 pad34[0x20];
    s32 rot;
    u8 pad58[0x1C];
} Spk_b131_01E06510;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 seg;
    u8 type;
    u8 pad9[3];
    f32 scale;
    f32 base;
    f32 dy;
    f32 y;
    f32 vy;
    u8 c0[4];
    u8 c1[4];
    Vec4f pos;
    u8 pad38[0x10];
} Ring_b131_01E06510;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    s32 m2;
    s32 m3;
    u8 pad1C[0x10];
    Cam_b131_01E06510 cam;
    Emit_b131_01E06510 emit;
    Wv_b131_01E06510 wv;
    Walk_b131_01E06510 walk;
    u8 smk[0x20][0x38];
    u8 parts[0x32][0x28];
    Trl_b131_01E06510 trl;
    Part_b131_01E053B0 part[0x18];
    Obj_b051_01E003A0 obj[3];
    Beam_b040_01E03E90 beam[4];
    Spk_b131_01E06510 spk[5];
    Ring_b131_01E06510 ring[3];
    Rib_b285_01E014C0 rib[0x14];
    Emit_b131_01E03B50 act;
    s8 tbl[0x100];
    u8 pad2684[0xC];
} Scene_b131_01E06510;

static s32 func_01E06510_b131(Scene_b131_01E06510 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, s32);
    extern void func_01E00EF0_b131();
    extern s32 func_01E02460_b131();
    extern s16 D_01E07140_b131[];
    extern s16 D_01E07160_b131[];
    s32 ot;
    Vec4f v;
    Vec4f w;
    s32 i;
    s32 j;
    s32 r;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x2690);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0x1C, 1);
        g->m1 = func_001F5560(g->unitA, 0x1D, 0);
        g->m2 = func_001F5560(g->unitA, 0x35, 0);
        g->m3 = func_001F5560(g->unitA, 0x3B, 0);
        g->walk.bone[0] = g->m3;
        g->walk.bone[1] = g->m2;
        g->walk.frames[0] = D_01E07140_b131;
        g->walk.frames[1] = D_01E07160_b131;
        g->walk.emits = g->smk;
        g->walk.emit_kind = 0x20;
        g->walk.parts = g->parts;
        g->walk.part_kind = 0x32;
        g->walk.kind = 0;
        g->walk.bone2 = g->m1;
        g->walk.lo = 0;
        g->walk.x0 = 100.0f;
        g->walk.y = 5.0f;
        g->wv.a = 2;
        g->wv.b = 0x1B2;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        for (i = 0; i < 16; i++) {
            func_00101AD0(&g->part[i], 0x30, i & 7, 7);
            g->part[i].follow = 1;
            g->part[i].b6[0] = g->m0;
            g->part[i].flags = (((func_0019A5C8() >> 4) & 3) << 4) | 0x81;
            g->part[i].tex = 2;
            g->part[i].b9 = 3;
            g->part[i].bA = 2;
            g->part[i].bB = 0;
            g->part[i].r = 0x80;
            g->part[i].g = 0x80;
            g->part[i].b = 0x80;
            g->part[i].a = 0xC0;
            g->part[i].size = 80.0f;
            g->part[i].range = 0x28;
        }
        for (i = 16; i < 24; i++) {
            func_00101AD0(&g->part[i], 0x30, i & 7, 7);
            g->part[i].follow = 1;
            g->part[i].b6[0] = g->m0;
            g->part[i].flags = 1;
            g->part[i].tex = 0;
            g->part[i].b9 = 3;
            g->part[i].bA = 1;
            g->part[i].bB = 0;
            g->part[i].r = 0x80;
            g->part[i].g = 0x80;
            g->part[i].b = 0x80;
            g->part[i].a = 0x20;
            g->part[i].size = 200.0f;
            g->part[i].range = 1;
        }
        func_00101AD0(&g->obj[0], 0x30, 0, 0xFF);
        g->obj[0].pad5[0] = 1;
        g->obj[0].flags = 0x85;
        g->obj[0].flags = 0x85;
        g->obj[0].segs = 9;
        g->obj[0].ir = g->obj[0].ig = g->obj[0].ib = g->obj[0].alpha = 0xC0;
        g->obj[0].g = g->obj[0].r = 0x60;
        g->obj[0].b = 0;
        g->obj[0].grow = 0.0f;
        g->obj[0].radius = 200.0f;
        func_00101AD0(&g->emit, 0x30, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m0;
        g->emit.on = 4;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 1.5f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 60.0f;
        g->emit.f50 = 3.0f;
        break;
    case 0x31:
    case 0x160:
        for (i = 0; i < 8; i++) {
            func_00101AD0(&g->part[i], 0x9A, (u8)i, 7);
            g->part[i].follow = 1;
            g->part[i].b6[0] = g->m0;
            g->part[i].flags = (((func_0019A5C8() >> 4) & 3) << 4) | 1;
            g->part[i].tex = 2;
            g->part[i].b9 = 3;
            g->part[i].bA = 2;
            g->part[i].bB = 0;
            g->part[i].r = 0x80;
            g->part[i].g = 0x80;
            g->part[i].b = 0x80;
            g->part[i].a = 0xC0;
            g->part[i].size = 80.0f;
            g->part[i].range = 0x28;
        }
        for (i = 8; i < 16; i++) {
            func_00101AD0(&g->part[i], 0x9A, i & 7, 7);
            g->part[i].follow = 1;
            g->part[i].b6[0] = g->m0;
            g->part[i].flags = 1;
            g->part[i].tex = 0;
            g->part[i].b9 = 3;
            g->part[i].bA = 1;
            g->part[i].bB = 0;
            g->part[i].r = 0x80;
            g->part[i].g = 0x80;
            g->part[i].b = 0x80;
            g->part[i].a = 0x20;
            g->part[i].size = 150.0f;
            g->part[i].range = 1;
        }
        func_00101AD0(&g->emit, 0x9A, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m0;
        g->emit.on = 4;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 1.5f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 60.0f;
        g->emit.f50 = 3.0f;
        break;
    case 0x10A:
        func_00101AD0(&g->trl, 0x15, 0, 0xFF);
        g->trl.b4 = 1;
        g->trl.p8 = g->trl.buf;
        g->trl.b30 = 0x32;
        g->trl.b31 = 8;
        g->trl.b32 = g->m0;
        g->trl.b33 = g->m1;
        g->trl.f38 = 1.0f;
        g->trl.c[0] = 0x80;
        g->trl.c[1] = 0x80;
        g->trl.c[2] = 0x80;
        g->trl.c[3] = 0xC0;
        g->trl.b4A = 0x80;
        g->trl.b49 = 0x10;
        g->trl.b48 = 0x10;
        for (j = 0; j < g->trl.b31 + 1; j++) {
            g->trl.h0C[j] = -1;
            g->trl.h1E[j] = -1;
        }
        break;
    case 0x118:
        func_00101AD0(&g->act, 3, 0, 0xFF);
        g->act.flags = 2;
        g->act.attached = 1;
        g->act.pad6[0] = g->m0;
        g->act.pool = (Part_b131_01E03B50 *)g->rib;
        g->act.kind = 0x14;
        g->act.f12 = 0x2D;
        g->act.sub = 0x20;
        g->act.f13 = 1;
        g->act.f16 = 2;
        g->act.f14 = 3;
        g->act.scale = 1.0f;
        g->act.f1C = 0.3f;
        g->act.f20 = 30.0f;
        g->act.fC = (s32)g->tbl;
        g->act.col.b = g->act.col.g = g->act.col.r = g->act.col.a = 0x80;
        func_001F5620(g->unitA, g->m0, &g->act.prev);
        g->act.prev2 = g->act.prev;
        break;
    case 0x11A:
        func_001F5620(g->unitA, g->m0, &w);
        for (i = 0, r = 0xD000; i < 5; i++, r += 0x1800) {
            func_00101AD0(&g->spk[i], 0x16, 0, 0xFF);
            g->spk[i].age -= 4;
            g->spk[i].b4 = 0;
            g->spk[i].b5 = 0;
            g->spk[i].b8 = 0x28;
            g->spk[i].b9 = func_0019A5C8() >> 4;
            g->spk[i].f18 = 60.0f;
            g->spk[i].tbl = g->tbl;
            g->spk[i].f10 = 3.5f;
            g->spk[i].f14 = 1.0f;
            g->spk[i].c1C[2] = 0xC0;
            g->spk[i].c1C[1] = 0;
            g->spk[i].c1C[0] = 0;
            g->spk[i].c20[0] = 0x80;
            g->spk[i].c20[1] = 0x80;
            g->spk[i].c20[2] = 0x80;
            g->spk[i].c20[3] = 0x80;
            g->spk[i].pos = w;
            g->spk[i].rot = (u16)r;
        }
        for (i = 0; i < 3; i++) {
            func_00101AD0(&g->ring[i], 0x10, (u8)(i * 3), 0xFF);
            g->ring[i].b4 = 0;
            g->ring[i].b5 = 0;
            g->ring[i].seg = 9;
            g->ring[i].type = 0;
            g->ring[i].scale = 3.0f;
            g->ring[i].base = 0.2f;
            g->ring[i].dy = 0.5f;
            g->ring[i].y = 0.0f;
            g->ring[i].vy = 0.1f;
            g->ring[i].c0[2] = g->ring[i].c0[1] = g->ring[i].c0[0] = g->ring[i].c0[3] = 0x80;
            g->ring[i].c1[2] = 0xC0;
            g->ring[i].c1[1] = 0;
            g->ring[i].c1[0] = 0;
            g->ring[i].c1[3] = 0;
            g->ring[i].pos = w;
        }
        func_00101AD0(&g->obj[0], 0x18, 0, 0xFF);
        g->obj[0].pad5[0] = 0;
        g->obj[0].flags = 0x81;
        g->obj[0].segs = 9;
        g->obj[0].ir = g->obj[0].ig = g->obj[0].ib = g->obj[0].alpha = 0xC0;
        g->obj[0].r = 0xC0;
        g->obj[0].b = g->obj[0].g = 0x10;
        g->obj[0].grow = 0.0f;
        g->obj[0].radius = 800.0f;
        g->obj[0].pos = *(V4_b051_01E003A0 *)&w;
        func_00101AD0(&g->emit, 0x18, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 2.0f;
        g->emit.f1C = 2.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 6.0f;
        g->emit.pos = w;
        break;
    case 0x1B8:
        return 8;
    }
    func_01E00080_b131((Fx_b005_01E00080 *)&g->emit);
    func_001031C0(&g->wv, g->t);
    func_01E00EF0_b131(&g->walk, g->t);
    func_01E003A0_b131(g->smk, ot, 0x20);
    func_01E01340_b131((Rib_b285_01E003A0 *)&g->trl, ot, 1);
    func_01E053B0_b131(g->part, ot, 0x18);
    func_01E04960_b131(g->obj, ot, 3);
    func_01E04060_b131(g->beam, ot, 4);
    func_01E02460_b131(g->spk, ot, 5);
    func_01E05D00_b131(g->ring, ot, 3);
    func_01E03B50_b131(&g->act, ot, 1);
    func_01E02EF0_b131(g->rib, ot, 0x14);
    switch (g->t) {
    case 0x110:
        return 1;
    case 0x117:
        return 2;
    }
    return 0;
}
