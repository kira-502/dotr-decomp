#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b151", func_01E00080_b151);

/* shape b151:01E027D0 (Gb151_GenAuraTex), 143 insns, 1 copy: draws a full-screen red-pink flash: a 5-reg sprite
   packet with integer UVs (0,0 to 640,448), its alpha 255 x func_00101020(t, 30) x func_00100FF0(t, 270, 240) from
   the module scene's timer (0x9914), sent through the frame's draw context */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b151_01E027D0;

typedef struct {
    u16 s : 14;
    u16 ps : 2;
    u16 t : 14;
    u16 pt : 2;
    u32 pad;
} Uv_b151_01E027D0;

typedef struct {
    Uv_b151_01E027D0 st;
    Xyz_b151_01E027D0 p;
} Tv_b151_01E027D0;

typedef struct {
    s16 n;
    u16 count;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b151_01E027D0 v[2];
    u8 tail[8];
} Pkt_b151_01E027D0;

typedef struct {
    u8 pad0[0x9914];
    s32 t;
} Scene_b151_01E027D0;

extern Scene_b151_01E027D0 *D_01E02A80_b151;

static void func_01E027D0_b151(void *ctx) {
    extern s32 func_00207650(s32, void *, s32, s32);
    Pkt_b151_01E027D0 pk __attribute__((aligned(8)));
    s32 o98[2];
    s32 oA0[3];
    Scene_b151_01E027D0 *s;
    s32 a;
    f32 f;

    s = D_01E02A80_b151;
    ctx = func_00209F70(ctx, 0xFF000000);
    ((Pkt_b151_01E027D0 *)(u32)&pk)->count = 0x26;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->n = 5;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->regs = 0x42421;
    ((Pkt_b151_01E027D0 *)(u32)&pk)->pad4 = 0;
    ctx = (void *)func_0020F290(func_00208870(func_0020F290((s32)ctx), -1, 1, o98, oA0));
    func_002086D0(&pk, func_00208D00(0));
    func_00208CB0(&pk, ((s64)0x700 << 32) | 0xA0000A);
    ((Pkt_b151_01E027D0 *)(u32)&pk)->count |= 0x800;
    f = 255.0f * func_00101020(s->t, 30.0f);
    a = (u32)(f * func_00100FF0(s->t, 270.0f, 240.0f));
    pk.r = 0xFF;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = a;
    pk.q = 1.0f;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[0].st)->s = 0;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[0].st)->t = 0;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[1].st)->s = 0x2800;
    ((Uv_b151_01E027D0 *)(s32)&pk.v[1].st)->t = 0x1C00;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFF8;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFF8;
    pk.v[1].p.f = 0;
    func_00209F70((void *)func_00207650((s32)ctx, &pk, 0, 0), 0);
}

