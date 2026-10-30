#include "common.h"

/* shape c022:01E01850 (C022PAINT_RAIN3), 153 insns (+35 stale words), 1 copy: mode 0 sets up the packet (8-tag, 4 RGBAQ/XYZ regs, alpha
   0x48, q 1.0, colours 0x28 top and 0x2C bottom); otherwise draws 12 steps of a ring band, the inner edge at the
   centre 10 up, the outer edge at radius 200 from angle 0x34 in 30 steps (scene table 0x3A50), at the scene depth
   0x3A28 into 0x39FC */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c022_01E01850;

typedef struct {
    Rgbaq_c022_01E01850 c;
    u8 xyz[8];
} Vtx_c022_01E01850;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c022_01E01850 v[4];
} Pkt_c022_01E01850;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[4];
    s16 angle;
} Obj_c022_01E01850;

typedef struct {
    u8 pad0[0x39FC];
    s32 ot;
    u8 pad3A00[0x28];
    f32 depth;
    u8 pad3A2C[0x24];
    u8 trig[1];
} Scene_c022_01E01850;

static void func_01E01850_c022(Scene_c022_01E01850 *g, Obj_c022_01E01850 *o, Pkt_c022_01E01850 *p, s32 mode) {
    extern Rgbaq_c022_01E01850 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    s32 i;
    s16 a;
    s16 b;

    a = 0;
    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 1.0f;
        p->v[0].xyz[7] = 0;
        p->v[1].xyz[7] = 0;
        p->v[2].xyz[7] = 0;
        p->v[3].xyz[7] = 0;
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
    } else {
        q[0].x = 0.0f;
        q[0].z = 0.0f;
        q[1].x = q[0].x;
        q[1].z = q[0].z;
        q[0].y = 10.0f;
        q[1].y = 10.0f;
        q[2].y = 10.0f;
        q[3].y = 10.0f;
        for (i = 0; i < 12; i++) {
            b = o->angle + a;
            q[2].x = 200.0f * func_00108030(g->trig, b, 1);
            q[2].z = 200.0f * func_00108030(g->trig, b, 0);
            b = o->angle + 30 + a;
            q[3].x = 200.0f * func_00108030(g->trig, b, 1);
            q[3].z = 200.0f * func_00108030(g->trig, b, 0);
            if (func_00205630(q, 0x70000000, 0, p, &g->depth) != 0) {
                func_002075F0(p, g->ot, func_001A23B0(g->depth));
            }
            a += 30;
        }
    }
}
