#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b711", func_01E00080_b711);

/* shape b711:01E054B0 (Gb711_GenAuraTex), 174 insns, 1 copy: draws an orange cover: a white 5-reg sprite packet (UVs
   0,0 to 640,448) then a flat 3-reg packet at (0xC8, 0x46, 0) alpha 0xE4 over the same rectangle, sent through the
   frame draw context */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b711_01E054B0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b711_01E054B0 v[2];
    u8 tail[8];
} Flat_b711_01E054B0;

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_b711_01E054B0;

typedef struct {
    Uv_b711_01E054B0 st;
    Xyz_b711_01E054B0 p;
} Tv_b711_01E054B0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b711_01E054B0 v[2];
    u8 tail[8];
} Spr_b711_01E054B0;

static void func_01E054B0_b711(void *ctx) {
    extern s32 func_00207650(s32, void *, s32, s32);
    Flat_b711_01E054B0 flat __attribute__((aligned(8)));
    Spr_b711_01E054B0 pk __attribute__((aligned(8)));
    s32 oA8[2];
    s32 oB0[3];

    ctx = func_00209F70(ctx, 0xFF000000);
    ((Spr_b711_01E054B0 *)(u32)&pk)->count = 0x26;
    ((Spr_b711_01E054B0 *)(u32)&pk)->n = 5;
    ((Spr_b711_01E054B0 *)(u32)&pk)->regs = 0x42421;
    ((Spr_b711_01E054B0 *)(u32)&pk)->pad4 = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, oA8, oB0));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Spr_b711_01E054B0 *)(u32)&pk)->count |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[0].st)->s = 0;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[0].st)->t = 0;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[1].st)->s = 0x2800;
    ((Uv_b711_01E054B0 *)(s32)&pk.v[1].st)->t = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    ctx = (void *)func_00207650((s32)ctx, &pk, 0, 0);
    ((Flat_b711_01E054B0 *)(u32)&flat)->count = 6;
    ((Flat_b711_01E054B0 *)(u32)&flat)->n = 3;
    ((Flat_b711_01E054B0 *)(u32)&flat)->regs = 0x441;
    ((Flat_b711_01E054B0 *)(u32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0xC8;
    flat.g = 0x46;
    flat.b = 0;
    flat.a = 0xE4;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    func_00209F70((void *)func_00207650((s32)ctx, &flat, 0, 0), 0);
}

