#include "common.h"

/* shape c606:01E00080 (c606), 182 insns, 3 copies: a spinning two-triangle marker: on start clears the angles and
   sets a 60-tick timer; each tick turns it by 0x800, builds its matrix at the point from func_001F53B0(0) and sends
   two gouraud triangles (red, green, blue corners) from the module's six points, each at its mean depth; ends with 8
   when the timer runs out. Parameters copied under opt_propagation off; the packet (with a trailing u64) and the
   depths are aligned(8), which lays the frame out like the original */

typedef struct {
    f32 x, y, z, w;
} Vec_c606_01E00080;

typedef struct {
    Vec_c606_01E00080 v[6];
} Tri_c606_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_c606_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c606_01E00080;

typedef struct {
    Col_c606_01E00080 c;
    Xyz_c606_01E00080 p;
} Vtx_c606_01E00080;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c606_01E00080 v[3];
    u64 end;
} Pkt_c606_01E00080;

typedef struct {
    s32 w0, w4, w8, wC;
    s32 timer;
} Obj_c606_01E00080;

#pragma opt_propagation off

static s32 func_01E00080_c608(Obj_c606_01E00080 *arg0, s32 arg1) {
    extern Tri_c606_01E00080 D_01E00380_c608;
    extern s32 func_00207500(void);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Tri_c606_01E00080 pts;
    Vec_c606_01E00080 pos;
    f32 r[16];
    f32 m[16];
    f32 d[3] __attribute__((aligned(8)));
    Pkt_c606_01E00080 pkt __attribute__((aligned(8)));
    Obj_c606_01E00080 *o;
    s32 t;
    s32 mode;

    mode = arg1;
    o = arg0;
    t = func_00207500();
    pts = D_01E00380_c608;
    if (mode >= 0) {
        o->w0 = 0;
        o->w4 = 0;
        o->w8 = 0;
        o->wC = 0;
        o->timer = 60;
        return 0;
    }
    func_001F53B0(0, &pos);
    o->w4 += 0x800;
    func_0020EB40(m);
    func_0020C940(r, 0, o, &pos);
    func_0020BC00(m, r);
    ((Pkt_c606_01E00080 *)(s32)&pkt)->count = 0x13;
    ((Pkt_c606_01E00080 *)(s32)&pkt)->tag = 6;
    ((Pkt_c606_01E00080 *)(s32)&pkt)->regs = 0x414141;
    ((Pkt_c606_01E00080 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    pkt.v[0].c.r = 0x80;
    pkt.v[0].c.g = 0x20;
    pkt.v[0].c.b = 0x20;
    pkt.v[0].c.a = 0x80;
    pkt.v[0].c.q = 1.0f;
    pkt.v[1].c.r = 0x20;
    pkt.v[1].c.g = 0x80;
    pkt.v[1].c.b = 0x20;
    pkt.v[1].c.a = 0x80;
    pkt.v[1].c.q = 1.0f;
    pkt.v[2].c.r = 0x20;
    pkt.v[2].c.g = 0x20;
    pkt.v[2].c.b = 0x80;
    pkt.v[2].c.a = 0x80;
    pkt.v[2].c.q = 1.0f;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.f = 0;
    pkt.v[2].p.f = 0;
    if (func_00205440(&pts.v[0], m, &pkt.v[0].p, &d[0]) != 0 && func_00205440(&pts.v[1], m, &pkt.v[1].p, &d[1]) != 0 &&
        func_00205440(&pts.v[2], m, &pkt.v[2].p, &d[2]) != 0) {
        func_002075F0(&pkt, t, (u32)((d[0] + d[1] + d[2]) / 3.0f));
    }
    if (func_00205440(&pts.v[3], m, &pkt.v[0].p, &d[0]) != 0 && func_00205440(&pts.v[4], m, &pkt.v[1].p, &d[1]) != 0 &&
        func_00205440(&pts.v[5], m, &pkt.v[2].p, &d[2]) != 0) {
        func_002075F0(&pkt, t, (u32)((d[0] + d[1] + d[2]) / 3.0f));
    }
    if (--o->timer <= 0) {
        return 8;
    }
    return 0;
}
#pragma opt_propagation reset
