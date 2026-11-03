#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b453", func_01E00080_b453);

/* shape b453:01E02F10 (Gb453_GenAuraTex), 174 insns, 1 copy: opens the frame buffer, sends a white sprite (alpha
   0x80) over the whole screen (0x6BF8,0x71F8 - 0x93F8,0x8DF8, far z) with texel corners 0,0 - 160,112 from the frame
   copy, then a flat orange (0xC8/0x76/0) rect over the same area, and closes it */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b453_01E02F10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b453_01E02F10 v[2];
    u64 tail;
} Flat_b453_01E02F10;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u8 pad4[4];
    Xyz_b453_01E02F10 p;
} Uv_b453_01E02F10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b453_01E02F10 v[2];
    u64 tail;
} Spr_b453_01E02F10;

static void func_01E02F10_b453(void *buf) {
    extern void *func_00209F70(void *, u32);
    extern void *func_0020F290(void *);
    extern void *func_00208870(void *, s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_00208CB0(void *, u64);
    extern void *func_00207650(void *, void *, s32, s32);
    Flat_b453_01E02F10 flat __attribute__((aligned(8)));
    Spr_b453_01E02F10 pk __attribute__((aligned(8)));
    s32 a[2];
    s32 b[3];

    buf = func_00209F70(buf, 0xFF000000);
    ((Spr_b453_01E02F10 *)(s32)&pk)->flags = 0x26;
    ((Spr_b453_01E02F10 *)(s32)&pk)->size = 5;
    ((Spr_b453_01E02F10 *)(s32)&pk)->regs = 0x42421;
    ((Spr_b453_01E02F10 *)(s32)&pk)->pad4 = 0;
    buf = func_0020F290(func_00208870(func_0020F290(buf), -1, 1, a, b));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
    ((Spr_b453_01E02F10 *)(s32)&pk)->flags |= 0x800;
    pk.r = 0xFF;
    pk.g = 0xFF;
    pk.b = 0xFF;
    pk.a = 0x80;
    pk.q = 1.0f;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[0])->u = 0;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[0])->v = 0;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[1])->u = 0x2800;
    ((Uv_b453_01E02F10 *)(s32)&pk.v[1])->v = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    buf = func_00207650(buf, &pk, 0, 0);
    ((Flat_b453_01E02F10 *)(s32)&flat)->flags = 6;
    ((Flat_b453_01E02F10 *)(s32)&flat)->size = 3;
    ((Flat_b453_01E02F10 *)(s32)&flat)->regs = 0x441;
    ((Flat_b453_01E02F10 *)(s32)&flat)->pad4 = 0;
    func_002086D0(&flat, func_00208D00(3));
    flat.r = 0xC8;
    flat.g = 0x76;
    flat.b = 0;
    flat.a = 0xFF;
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFF8;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFF8;
    flat.v[1].f = 0;
    buf = func_00207650(buf, &flat, 0, 0);
    func_00209F70(buf, 0);
}

