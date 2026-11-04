#include "common.h"

/* shape b015:01E008F0 (LkPrim_ModelShot2), 422 insns, 7 copies (-O3,p): a 2x2 sprite light shot around the
   model's screen point, its texture window stretched over count steps by the point's offset over 640/448.
   Best 97% (411/422): only the prologue's q.x/q.y temp registers and the packet address placement differ. */

typedef struct {
    f32 x, y, z, w;
} Vec_b015_01E008F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b015_01E008F0;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b015_01E008F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b015_01E008F0 st0;
    Xyz_b015_01E008F0 p0;
    Uv_b015_01E008F0 st1;
    Xyz_b015_01E008F0 p1;
    u8 pad50[8];
    u64 t58;
    u64 t60;
    u8 pad68[8];
} Pkt_b015_01E008F0;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b015_01E008F0;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    s16 count;
    s16 model;
} Shot_b015_01E008F0;

#pragma optimization_level 3
static inline void b015_01E008F0_tag(Pkt_b015_01E008F0 *p, s32 tag, s32 count, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E008F0_b015(Shot_b015_01E008F0 *o, Vec_b015_01E008F0 *pos) {
    extern s32 func_00207F60(void);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern f32 func_001F5860(s32);
    extern u64 func_00205D10(void *, f32);
    extern f32 func_00205DF0(void *, f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    s32 h;
    s32 j;
    s32 i;
    u16 py;
    u16 y;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    u16 x;
    s32 k;
    s16 x0;
    s16 y0;
    f32 ax;
    f32 bx;
    f32 ay;
    f32 by;
    Cam_b015_01E008F0 cam;
    Pkt_b015_01E008F0 pkt __attribute__((aligned(8)));
    Xyz_b015_01E008F0 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    x0 = (q.x >> 4) - 0x6C0;
    y0 = (q.y >> 4) - 0x720;
    ax = x0 / 640.0f;
    bx = 1.0f - ax;
    ay = y0 / 448.0f;
    by = 1.0f - ay;
    ax *= o->scale;
    bx *= o->scale;
    ay *= 0.7f * o->scale;
    by *= 0.7f * o->scale;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = o->r;
    pkt.g = o->g;
    pkt.b = o->b;
    pkt.a = o->a;
    pkt.q = 1.0f;
    func_00208460();
    func_001F7060(o->model, 0, &pkt.t58, &pkt.t60);
    func_00208460();
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count |= 0x800;
    for (i = 0; i < o->count; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                x = k * 640 + 0x6C0;
                y = j * 448 + 0x720;
                u0 = ((s32)ax * i) << 4;
                v0 = ((s32)ay * i) << 4;
                u1 = (640 - (s32)bx * i) << 4;
                v1 = (448 - (s32)by * i) << 4;
                py = (y << 4) - 8;
                pkt.p0.x = q.x;
                pkt.p0.y = q.y;
                pkt.p0.f = 0;
                pkt.p1.x = (x << 4) - 8;
                pkt.p1.y = py;
                pkt.p1.f = 0;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->s = x0 << 4;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->t = y0 << 4;
                if (j == 0) {
                    if (k == 0) {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    } else {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    }
                } else if (k == 0) {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                } else {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                }
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.p0.z = pkt.p1.z = 0xFFFFFF;
                    func_002075F0(&pkt, 0, 0);
                } else {
                    pkt.p0.z = pkt.p1.z = func_00205D10(pos, -func_001F5860(o->model));
                    func_002075F0(&pkt, 0, (u32)func_00205DF0(pos, -func_001F5860(o->model)));
                }
            }
        }
    }
    func_00207FD0(h, func_00207500(), 0);
    return 0;
}
#pragma optimization_level reset
