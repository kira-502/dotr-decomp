#include "common.h"

/* shape b023:01E00080 (ShFx_Gus), 580 insns, 1 copy (-O2,p): n gust puffs (0x44-byte emitters): each moves with its
   acceleration and gravity, stops at its floor and grows; its animation frame comes from its age with flag 8; it
   fades over its last 16 frames and draws as a textured screen-space square of its projected width, flipped by flags
   & 0x30; the source of b097:01E059B0, built here at -O2 */

typedef struct {
    f32 x, y, z, w;
} Vec_b023_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b023_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b023_01E00080;

typedef struct {
    u64 st;
    Xyz_b023_01E00080 p;
} Vtx_b023_01E00080;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Col_b023_01E00080 c;
    Vtx_b023_01E00080 v[4];
    u8 tail[0x20];
} Pkt_b023_01E00080;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b023_01E00080;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 page;
    u8 texkind;
    u8 frame;
    u8 shift;
    u8 b, g, r, a;
    f32 width;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Fx_b023_01E00080;

#pragma optimization_level 2

static s32 func_01E00080_b023(Fx_b023_01E00080 *obj, s32 target, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 m[16];
    Vec_b023_01E00080 a;
    Tex_b023_01E00080 tex;
    Pkt_b023_01E00080 pkt __attribute__((aligned(8)));
    Xyz_b023_01E00080 xy;
    f32 d;
    Fx_b023_01E00080 *e;
    s32 age;
    s32 i;
    s32 fr;
    f32 w;
    s32 texture;

    e = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Fx_b023_01E00080 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            texture = func_00202BF0(5, e->texkind);
        } else {
            texture = func_00202BF0(4, 2);
        }
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->width += e->grow;
        if (e->y < e->floor) {
            e->y = e->floor;
        }
        a.x = e->x;
        a.y = e->y;
        a.z = e->z;
        func_0020EB40(m);
        ((Pkt_b023_01E00080 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->tag = 9;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->pad = 0;
        pkt.c.r = e->r;
        pkt.c.g = e->g;
        pkt.c.b = e->b;
        pkt.c.q = 1.0f;
        age = e->total - e->life;
        fr = e->frame;
        if (e->flags & 8) {
            fr = ((age >> e->shift) & 3) + 2;
            if (age < 3) {
                fr = age;
            }
            if (e->life < 7) {
                fr = 7 - (e->life >> e->shift);
            }
        }
        tex.page = e->page;
        func_001020B0(&tex, fr, 0);
        func_00101D20(&pkt, &tex, texture);
        if (e->life < 16) {
            pkt.c.a = (e->a >> 4) * e->life;
        } else {
            pkt.c.a = e->a;
        }
        if (func_00205440(&a, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        w = func_001018E0(e->width, d);
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = xy.z;
        switch (e->flags & 0x30) {
        case 0x10:
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x20:
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x30:
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        default:
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        }
        func_002075F0(&pkt, target, (u32)d);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b023", func_01E00990_b023);
