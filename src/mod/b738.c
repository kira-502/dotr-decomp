#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b738", func_01E00080_b738);

/* shape b738:01E05B00 (Gb738_GenAuraTex), 333 insns, 1 copy (-O3,p): b704:01E03240 (b066:01E036B0 at -O3) with the
   texture at +0x1C, the position at +0x70, the grid at +0x8DE0 and the grid tinted (0x80, 0x80, 0x80) alpha 0x64 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b738_01E05B00;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b738_01E05B00 v[2];
    u64 tail;
} Flat_b738_01E05B00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b738_01E05B00;

typedef struct {
    Rgbaq_b738_01E05B00 c;
    f32 s, t;
    Xyz_b738_01E05B00 p;
} Tv_b738_01E05B00;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b738_01E05B00 v[4];
    u8 tail[0x20];
} Tex_b738_01E05B00;

typedef struct {
    u8 pad0[0x1C];
    void *texture;
    u8 pad20[0x50];
    u8 pos[0x10];
    u8 pad80[0x8D60];
    Vec4f grid[17][17];
} Obj_b738_01E05B00;

extern Obj_b738_01E05B00 *D_01E06080_b738;

#pragma optimization_level 3

static void func_01E05B00_b738(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern u64 func_00208D00(s32);
    extern void *func_00207650(void *, void *, s32, s32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_00100E00(void *, s32, s32);
    extern s32 func_00100BA0(void *, void *, void *, void *, void *, void *, f32 *);
    Obj_b738_01E05B00 *o __attribute__((aligned(16)));
    s32 i __attribute__((aligned(16)));
    f32 m[4][4];
    f32 m2[4][4];
    Flat_b738_01E05B00 flat __attribute__((aligned(8)));
    Tex_b738_01E05B00 pk __attribute__((aligned(8)));
    f32 depth;
    void *p;
    s32 j;
    f32 t0;
    f32 t1;
    f32 s0;
    f32 s1;

    o = D_01E06080_b738;
    p = func_00209F70(buf, 0xFF000000);
    ((Flat_b738_01E05B00 *)(s32)&flat)->flags = 6;
    ((Flat_b738_01E05B00 *)(s32)&flat)->size = 3;
    ((Flat_b738_01E05B00 *)(s32)&flat)->regs = 0x441;
    ((Flat_b738_01E05B00 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(2));
    flat.r = 0x40;
    flat.g = 0x40;
    flat.b = 0x40;
    flat.a = 0x80;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    p = func_00207650(p, &flat, 0, 0);
    ((Tex_b738_01E05B00 *)(s32)&pk)->flags = 0x34;
    ((Tex_b738_01E05B00 *)(s32)&pk)->size = 0xC;
    ((Tex_b738_01E05B00 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Tex_b738_01E05B00 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, func_00208D00(1));
    func_00208700(&pk, o->texture, 1);
    func_00208CB0(&pk, 0);
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_00187B60(m2, m2, o->pos);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 0);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 1);
    func_00100E00(m2, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
    func_0020BC00((s32)m, m2);
    pk.v[0].c.r = 0x80;
    pk.v[0].c.g = 0x80;
    pk.v[0].c.b = 0x80;
    pk.v[0].c.a = 0x64;
    pk.v[0].c.q = 1.0f;
    pk.v[1].c = pk.v[0].c;
    pk.v[2].c = pk.v[0].c;
    pk.v[3].c = pk.v[0].c;
    for (i = 0; i < 16; i++) {
        t0 = (f32)(i % 4) / 4.0f;
        t1 = (f32)(i % 4 + 1) / 4.0f;
        for (j = 0; j < 16; j++) {
            s0 = (f32)(j % 4) / 4.0f;
            s1 = (f32)(j % 4 + 1) / 4.0f;
            pk.v[0].s = s0;
            pk.v[0].t = t0;
            pk.v[1].s = s1;
            pk.v[1].t = t0;
            pk.v[2].s = s0;
            pk.v[2].t = t1;
            pk.v[3].s = s1;
            pk.v[3].t = t1;
            if (func_00100BA0(&o->grid[i][j], &o->grid[i][j + 1], &o->grid[i + 1][j], &o->grid[i + 1][j + 1], m, &pk,
                              &depth) == 1) {
                pk.v[0].p.z = 0xFFFFF8;
                pk.v[1].p.z = pk.v[0].p.z;
                pk.v[2].p.z = pk.v[0].p.z;
                pk.v[3].p.z = pk.v[0].p.z;
                p = func_00207650(p, &pk, 0, 0);
            }
        }
    }
    func_00209F70(p, 0);
}

#pragma optimization_level reset
