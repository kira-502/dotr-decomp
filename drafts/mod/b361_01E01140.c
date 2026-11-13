#include "common.h"

/* shape b361:01E01140 (B361_OBJ_MOVE_202_), 559 insns, 1 copy: best draft 452/559 (81%), not matching. A grey
   (0x30) scrolling full-screen overlay written into the scene's shared packet (0x5F54): four passes, each projects
   the scene point (z +-60 by side 0x5F92) onto one corner and places the other three from the scroll offsets
   (u + 0x940 / 0x6C0 - u, v + 0x8E0 / 0x720 - v, *16 - 8), far z, texture coords from the screen position
   clamped to 640 x 480 (/1024, /512); the offsets grow by 20..34 a tick; alpha down by 19 once running; ends at
   scene frame 166. Left: the per-vertex s/t float block's constant registers (-16.0f in $f3 / zero in $f1 where
   the original has $f0 / $f3) and the pk reload scheduled ahead of the z-mask build, which costs the k == 3
   delay slot. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b361_01E01140;

typedef struct {
    Rgbaq_b361_01E01140 c;
    f32 s, t;
    u64 x : 16, y : 16, z : 24, f : 8;
} Vtx_b361_01E01140;

typedef struct {
    u8 hdr[0x10];
    Vtx_b361_01E01140 v[4];
} Pkt_b361_01E01140;

typedef struct {
    u8 pad0[0x5F10];
    f32 x, y, z;
    u8 pad5F1C[0x38];
    Pkt_b361_01E01140 *pk;
    u8 pad5F58[4];
    s32 z5C;
    u8 pad5F60[0x1C];
    s16 joint;
    u8 pad5F7E[0x14];
    s16 side;
    u8 pad5F94[2];
    s16 t;
} Scene_b361_01E01140;

typedef struct {
    u8 pad0[8];
    s16 u;
    s16 v;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Fx_b361_01E01140;

static s32 func_01E01140_b361(Scene_b361_01E01140 *g, Fx_b361_01E01140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern Rgbaq_b361_01E01140 func_00107740(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, void *);
    Vec4f d;
    Vec4f p[4];
    Vec4f j;
    s16 k;
    f32 s;
    f32 t;
    f32 z;

    if (o->state == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
        o->col[3] = 0x80;
        o->u = 0;
        o->v = 0;
        o->state = 2;
    }
    g->pk->v[0].c = func_00107740(o->col);
    g->pk->v[1].c = func_00107740(o->col);
    g->pk->v[2].c = func_00107740(o->col);
    g->pk->v[3].c = func_00107740(o->col);
    p[0].x = g->x;
    p[0].y = g->y;
    p[0].z = g->z;
    if (g->side) {
        p[0].z += 60.0f;
    } else {
        p[0].z -= 60.0f;
    }
    func_00205440(p, 0, &g->pk->v[0].x, &g->z5C);
    for (k = 0; k < 4; k++) {
        if (k == 0) {
            func_001F5620(func_001F53A0(), g->joint, &j);
            p[0].x = g->x;
            p[0].y = g->y;
            p[0].z = g->z;
            func_00205440(p, 0, (u8 *)g->pk + 0x20, &d);
            g->pk->v[1].x = (o->u + 0x940) * 16 - 8;
            g->pk->v[1].y = g->pk->v[0].y;
            g->pk->v[2].x = g->pk->v[0].x;
            g->pk->v[2].y = (o->v + 0x8E0) * 16 - 8;
            g->pk->v[3].x = (o->u + 0x940) * 16 - 8;
            g->pk->v[3].y = (o->v + 0x8E0) * 16 - 8;
        }
        if (k == 1) {
            p[0].x = g->x;
            p[0].y = g->y;
            p[0].z = g->z;
            func_00205440(p, 0, (u8 *)g->pk + 0x38, &d);
            g->pk->v[0].x = (0x6C0 - o->u) * 16 - 8;
            g->pk->v[0].y = g->pk->v[1].y;
            g->pk->v[2].x = (0x6C0 - o->u) * 16 - 8;
            g->pk->v[2].y = (o->v + 0x8E0) * 16 - 8;
            g->pk->v[3].x = g->pk->v[1].x;
            g->pk->v[3].y = (o->v + 0x8E0) * 16 - 8;
        }
        if (k == 2) {
            p[0].x = g->x;
            p[0].y = g->y;
            p[0].z = g->z;
            func_00205440(p, 0, (u8 *)g->pk + 0x50, &d);
            g->pk->v[0].x = g->pk->v[2].x;
            g->pk->v[0].y = (0x720 - o->v) * 16 - 8;
            g->pk->v[1].x = (o->u + 0x940) * 16 - 8;
            g->pk->v[1].y = (0x720 - o->v) * 16 - 8;
            g->pk->v[3].x = (o->u + 0x940) * 16 - 8;
            g->pk->v[3].y = g->pk->v[2].y;
        }
        if (k == 3) {
            p[0].x = g->x;
            p[0].y = g->y;
            p[0].z = g->z;
            func_00205440(p, 0, (u8 *)g->pk + 0x68, &d);
            g->pk->v[0].x = (0x6C0 - o->u) * 16 - 8;
            g->pk->v[0].y = (0x720 - o->v) * 16 - 8;
            g->pk->v[1].x = g->pk->v[3].x;
            g->pk->v[1].y = (0x720 - o->v) * 16 - 8;
            g->pk->v[2].x = (0x6C0 - o->u) * 16 - 8;
            g->pk->v[2].y = g->pk->v[3].y;
        }
        z = 0.0f;
        g->pk->v[0].z = 0xFFFFFF;
        g->pk->v[0].f = 0;
        g->pk->v[1].z = 0xFFFFFF;
        g->pk->v[1].f = 0;
        g->pk->v[2].z = 0xFFFFFF;
        g->pk->v[2].f = 0;
        g->pk->v[3].z = 0xFFFFFF;
        g->pk->v[3].f = 0;
        s = (0x6BF8 - g->pk->v[0].x) / -16.0f - z;
        t = (0x71F8 - g->pk->v[0].y) / -16.0f - z;
        if (s < z) {
            s = z;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        g->pk->v[0].s = s / 1024.0f;
        g->pk->v[0].t = t / 512.0f;
        s = (0x6BF8 - g->pk->v[1].x) / -16.0f - z;
        t = (0x71F8 - g->pk->v[1].y) / -16.0f - z;
        if (s > 640.0f) {
            s = 640.0f;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        g->pk->v[1].s = s / 1024.0f;
        g->pk->v[1].t = t / 512.0f;
        s = (0x6BF8 - g->pk->v[2].x) / -16.0f - z;
        t = (0x71F8 - g->pk->v[2].y) / -16.0f - z;
        if (s < z) {
            s = z;
        }
        if (t > 480.0f) {
            t = 480.0f;
        }
        g->pk->v[2].s = s / 1024.0f;
        g->pk->v[2].t = t / 512.0f;
        s = (0x6BF8 - g->pk->v[3].x) / -16.0f - z;
        t = (0x71F8 - g->pk->v[3].y) / -16.0f - z;
        if (s > 640.0f) {
            s = 640.0f;
        }
        if (t > 480.0f) {
            t = 480.0f;
        }
        g->pk->v[3].s = s / 1024.0f;
        g->pk->v[3].t = t / 512.0f;
        func_002075F0((s32)g->pk, 0, 0);
    }
    o->u += (s16)((func_0019A5C8() >> 4) % 15 + 20);
    o->v += (s16)((func_0019A5C8() >> 4) % 15 + 20);
    if (o->t) {
        if (o->col[3] > 20) {
            o->col[3] -= 19;
        } else {
            o->state = 0;
        }
    }
    if (g->t >= 166) {
        o->state = 0;
    }
    o->t++;
    return 0;
}
