#include "common.h"

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E00080_b232(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

/* shape b232:01E00480, 164 insns: the b232 module's event step: counts ticks; until 154 follows the tracked point (ctx+0x44E4) with its marker (ctx+0x4470), at 155 aims it at the other point over 32 ticks and moves it until 185; spawns b232:01E00EA0 at tick 1, two b232:01E00710 at 35, b232:01E00F80 at 45, b232:01E01130 at 236; from 191 to 240 spawns b232:01E00AC0 every other tick turning 3; from 226 to 300 spawns b232:01E00970 every other tick 10 higher each tick */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x4470 - 0x25C];
    f32 m[3];
    u8 pad447C[8];
    f32 dy;
    f32 dz;
    u8 pad448C[0x44E4 - 0x448C];
    s16 id0;
    u8 pad44E6[0x44F4 - 0x44E6];
    s16 id1;
    u8 pad44F6[0x454A - 0x44F6];
    s16 turn;
    u8 pad454C[4];
    s16 slot;
    u8 pad4552[8];
    s16 timer;
} Ctx_b232_01E00480;

static void func_01E00480_b232(Ctx_b232_01E00480 *g) {
    extern s32 b232_01E00710(void);
    extern s32 b232_01E00970(void);
    extern s32 b232_01E00AC0(void);
    extern s32 b232_01E00EA0(void);
    extern s32 b232_01E00F80(void);
    extern s32 b232_01E01130(void);
    extern void b232_01E01A50(Ctx_b232_01E00480 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];

    g->timer++;
    if (g->timer < 155) {
        func_001F5620(func_001F53A0(), g->id0, g->m);
    } else {
        if (g->timer == 155) {
            func_001F5620(func_001F5380(), g->id1, v);
            g->dz = (v[2] - g->m[2]) / 32.0f;
            g->dy = (v[1] - g->m[1]) / 32.0f;
        }
        if (g->timer < 186) {
            g->m[2] += g->dz;
            g->m[1] += g->dy;
        }
    }
    if (g->timer == 1) {
        b232_01E01A50(g, b232_01E00EA0, 0);
    }
    if (g->timer == 35) {
        g->slot = 0;
        b232_01E01A50(g, b232_01E00710, 0);
        g->slot = 1;
        b232_01E01A50(g, b232_01E00710, 0);
    }
    if (g->timer == 45) {
        b232_01E01A50(g, b232_01E00F80, 0);
    }
    if (g->timer == 236) {
        b232_01E01A50(g, b232_01E01130, 0);
    }
    if (g->timer >= 191 && g->timer < 241) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        if (g->timer % 2 == 1) {
            b232_01E01A50(g, b232_01E00AC0, 0);
        }
        g->turn += 3;
    }
    if (g->timer >= 226 && g->timer < 301) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        g->pos[2] = 0.0f;
        g->pos[1] += 10.0f;
        if (g->timer % 2 == 1) {
            b232_01E01A50(g, b232_01E00970, 0);
        }
    }
}

/* shape b232:01E00710, 149 insns: b094:01E01900-family flickering pair: variant 0..6, f8 4..6, sway angle 0..359; both
   alphas grow by 12 (below 0x80) for 240 ticks, then fade by 9 (the first ends it); while the scene flag 0x455A is
   set the size grows by 0.5 to 20 with f4C 7 below it; it sways 20 x sin(0xE), turning 5 a tick, and 0x5A grows 10 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[4];
    s16 swing;
    u8 pad10[0x38];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 h5A;
    s16 sway;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b232_01E00710;

typedef struct {
    u8 pad0[0x455A];
    s16 grow;
    u8 pad455C[0x200];
    u8 sin[1];
} Ctx_b232_01E00710;

static s32 func_01E00710_b232(Ctx_b232_01E00710 *g, Fx_b232_01E00710 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    f32 f;

    if (o->mode == 1) {
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->swing = func_0019A5C8() % 360;
        o->sway = 0;
        o->h5A = 0;
    }
    if (o->tick < 240) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    if (g->grow != 0) {
        if (o->f48 < 20.0f) {
            o->f48 += 0.5f;
        }
        f = o->f4C = o->f48 - 7.0f;
        if (f < 0.0f) {
            o->f4C = 0.0f;
        }
    }
    o->sway = func_001A22C0(20.0f * func_00108030(g->sin, o->swing, 0));
    o->swing += 5;
    o->h5A += 10;
    o->tick++;
    return 0;
}

/* shape b232:01E00970, 81 insns: a white-grey rising flash (b749:01E028A0 shape, starting x turn by the game's side, no y turn): f48 200 with f4C 58 below, rising by
   f34 = 950 / 10 a frame with f4C 400 below; full alpha for 15 frames, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x4554];
    s16 side;
} Game_b232_01E00970;

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b232_01E00970;

static s32 func_01E00970_b232(Game_b232_01E00970 *g, Obj_b232_01E00970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->f34 = 950.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        if (g->side != 0) {
            o->rot0 = -0x1800;
        } else {
            o->rot0 = 0x1800;
        }
    }
    if (o->t < 0xF) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    o->t++;
    return 0;
}

/* shape b232:01E00AC0, 70 insns: a white/grey beam from 200 growing 95 a tick (tail 400 behind): alpha 0x80 for 13 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b232_01E00AC0;

static s32 func_01E00AC0_b232(s32 arg0, Obj_b232_01E00AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->f34 = 950.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 13) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    o->t++;
    return 0;
}

/* shape b232:01E00BE0, 89 insns: a white shard (3 x 13, random 3..4 at +8, angle from the scene, tipped +-0x1000 by the scene side flag): alpha at least 0x80 for 8 ticks, then out by 11 and ends; grows 11..20 a tick */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b232_01E00BE0;

typedef struct {
    u8 pad[0x4544];
    s16 ang;
    u8 pad4546[0xE];
    s16 side;
} Game_b232_01E00BE0;

static s32 func_01E00BE0_b232(Game_b232_01E00BE0 *g, Obj_b232_01E00BE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->f4C = 13.0f;
        o->kind = 0;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 2 + 3;
        o->h5C = g->ang;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        if (g->side != 0) {
            o->w20 = -0x1000;
        } else {
            o->w20 = 0x1000;
        }
    }
    if (o->t < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f48 += 11.0f + func_0019A5C8() % 10;
    }
    o->t++;
    return 0;
}

/* shape b232:01E00D50, 81 insns: a white streak: f48 3 growing by 11..25 a frame, f4C 26, random width 3 or 4, height from the
   game; full alpha for 25 frames, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x4544];
    s16 h;
} Game_b232_01E00D50;

typedef struct {
    u8 pad0[8];
    s16 w;
    u8 padA[0x3E];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[2];
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b232_01E00D50;

static s32 func_01E00D50_b232(Game_b232_01E00D50 *g, Obj_b232_01E00D50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 3.0f;
        o->f4C = 26.0f;
        o->h56 = 0;
        o->state = 2;
        o->w = func_0019A5C8() % 2 + 3;
        o->h = g->h;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
    }
    if (o->t < 0x19) {
        if (o->c0[3] < 0x80) {
            o->c0[3] = 0x80;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->f48 += 11.0f + func_0019A5C8() % 15;
    }
    o->t++;
    return 0;
}

/* shape b232:01E00EA0, 56 insns: volume fade (layout at 0x50): for 0x97 frames down 10 to 0x30, then while the game
   state at 0x44B0 is below 0x1E up 10 to 0x80; state 3 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0x44B0];
    s32 state;
} Game_b232_01E00EA0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b232_01E00EA0;

static s32 func_01E00EA0_b232(Game_b232_01E00EA0 *g, Fade_b232_01E00EA0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0x97) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b232:01E00F80, 106 insns: a yellow-grey full-screen veil (b081:01E044C0 shape): one sprite over the whole screen
   at the object alpha, sent at once; alpha up by 10 to 0x50 until frame 274, then down by 6 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b232_01E00F80;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b232_01E00F80 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b232_01E00F80;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b232_01E00F80;

static s32 func_01E00F80_b232(void *arg0, Obj_b232_01E00F80 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b232_01E00F80 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->state = 2;
    }
    ((Pkt_b232_01E00F80 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b232_01E00F80 *)(s32)&pkt)->tag = 5;
    ((Pkt_b232_01E00F80 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b232_01E00F80 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x90;
    pkt.g = 0x90;
    pkt.b = 0x78;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b232_01E00F80 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (o->t < 0x112) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0xA;
        }
    } else if (o->c0[3] > 7) {
        o->c0[3] -= 6;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b232:01E01130, 144 insns: b555:01E02CB0 family grey (0x38) sprite in the scene packet (ctx+0x44C8), a fixed texture window (0..0.625, 0..0.875) swaying sideways by h8 = 10 sin(h5A) (h5A from 0 or 180, +25 per tick), drawn twice; alpha up by 10 to 0x80 for 80 ticks, then down by 9 */

/* OVL_WARM */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b232_01E01130;

typedef struct {
    f32 s, t;
    Xyz_b232_01E01130 p;
} Tv_b232_01E01130;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b232_01E01130 v[2];
} Tex_b232_01E01130;

typedef struct {
    u8 pad[0x44C8];
    Tex_b232_01E01130 *pk;
    u8 pad44CC[0x475C - 0x44CC];
    u8 tab[1];
} Game_b232_01E01130;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b232_01E01130;

static s32 func_01E01130_b232(Game_b232_01E01130 *g, Fx_b232_01E01130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        if (o->kind == 0) {
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->ang = 180;
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = (f + 0x6C0) * 16 - 8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = (f + 0x940) * 16 - 8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    func_002075F0((s32)g->pk, 0, 0);
    o->f8 = 10.0f * func_00108030(g->tab, o->ang, 1);
    o->ang += 25;
    if (o->tick < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b232:01E01370 (b232), 438 insns, 1 copy: b232 scene manager in b396:01E01F00 form: setup (six joints, two
   type-4 and three type-5 textures, 256 s8 and 30 s16 jitters), step b232:01E00480 and every slot, counting the
   b232:01E01130 anchors, draw the b232:01E00710 burst at joint A and the b232:01E00970/00AC0/00BE0/00D50 circles by
   frame, then the anchor paint if any; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b232_01E01370;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[4];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b232_01E01370 fx[150];
    u8 pad4440[0x50];
    s32 tex[3];
    u8 pad449C[0x14];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad44F0[4];
    s16 cam;
    u8 pad44F6[0xE];
    s16 jit16[30];
    u8 pad4540[0x14];
    s16 turn;
    s16 id;
    s16 anchors;
    s16 frame;
    s8 jit[0x100];
    u8 pad465C[0x100];
    u8 crd[0x174];
} Scene_b232_01E01370;

static s32 func_01E01370_b232(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00480_b232();
    extern void func_01E00080_b232();
    extern void b232_01E01B90();
    extern void b232_01E01EE0();
    Scene_b232_01E01370 *g = (Scene_b232_01E01370 *)arg0;
    s16 n;
    Vec4f pos;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x48D0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 360;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    g->anchors = 0;
    func_01E00480_b232(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E01130_b232) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    g->anchors++;
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E00710_b232) {
                func_001F5620(func_001F53A0(), g->jA, &pos);
                g->tex88 = g->tex[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                b232_01E01B90(g, &g->fx[k], 0x20, &pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E00970_b232) {
                g->tex88 = g->tex[2];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x24;
                g->hBE = 0;
                if (g->frame >= 240) {
                    func_01E00080_b232(g, &g->fx[k], 0x20, g->fx[k].pos);
                }
            }
            if (g->fx[k].fn == (s32 (*)())func_01E00AC0_b232) {
                g->tex88 = g->tex[2];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x24;
                g->hBE = 0;
                if (g->frame < 237) {
                    func_01E00080_b232(g, &g->fx[k], 0x20, g->fx[k].pos);
                }
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E00BE0_b232) {
                g->tex88 = g->tex[2];
                func_00106080(rm2, 0x8C, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                if (g->frame < 237) {
                    func_01E00080_b232(g, &g->fx[k], 0x20, g->fx[k].pos);
                }
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E00D50_b232) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x8C, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                if (g->frame >= 236) {
                    func_01E00080_b232(g, &g->fx[k], 0x20, g->fx[k].pos);
                }
                g->hB8 = 0;
            }
        }
    }
    if (g->anchors != 0) {
        b232_01E01EE0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 226) {
        return 1;
    }
    if (g->frame == 325) {
        return 4;
    }
    if (g->frame == 315) {
        return 2;
    }
    if (g->frame > 236 && g->frame < 310) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b232:01E01A50, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b232_01E01A50 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b232_01E01A50;

typedef struct Obj_b232_01E01A50 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b232_01E01A50 slots[0x96];
    u8 padB[0x74];
    u8 rgba[4];
    u8 padC[0x98];
    s16 fB2B0;
} Obj_b232_01E01A50;

static s32 func_01E01A50_b232(Obj_b232_01E01A50 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b232_01E01A50 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* OVL_WARM */

/* shape b232:01E01B90, 212 insns: b108:01E03130 family burst draw: two-colour packet, the scene rect and texture,
   blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles
   a - 200 (a = 20 i) between radii f4C and f48 (trig g+0x475C), each turned by the object's 0x5A / 0x5C twist, with
   its frame from the scene table (g+0x4504) through func_00106080 into the rect, depth-tested into g+0x44BC */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b232_01E01B90;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x44BC - 0xC0];
    s32 ot;
    u8 pad44C0[0x4504 - 0x44C0];
    s16 frames[18];
    u8 pad4528[0x475C - 0x4528];
    u8 trig[1];
} Game_b232_01E01B90;

static void func_01E01B90_b232(Game_b232_01E01B90 *g, Obj_b232_01E01B90 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    *(f32 *)(u32)&q[0].y = 0.0f;
    *(f32 *)(u32)&q[1].y = 0.0f;
    *(f32 *)(u32)&q[2].y = 0.0f;
    *(f32 *)(u32)&q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    tw[1] = o->h5A;
    tw[2] = o->h5C;
    for (i = 0; i < 18; i++) {
        *(f32 *)(u32)&q[0].y = 0.0f;
        *(f32 *)(u32)&q[1].y = 0.0f;
        *(f32 *)(u32)&q[2].y = 0.0f;
        *(f32 *)(u32)&q[3].y = 0.0f;
        func_00106080(rm, 0x14, g->frames[i], 0);
        g->rect = *(Vec4f *)rm;
        func_00108500(p, &g->rect, g->frame);
        s = a - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        s = a - 180;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        func_00109100(q, tw, 2, g->trig);
        func_00109100(q, tw, 0, g->trig);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        a += 20;
    }
}

/* shape b232:01E01EE0, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x44C8, ot at
   0x44C4), texture from func_001F5380, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b232:01E01130 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b232_01E01EE0;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b232_01E01EE0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b232_01E01EE0 slots[0x96];
    u8 pad4440[0x84];
    s32 ot;
    Pkt_b232_01E01EE0 *pk;
} Scene_b232_01E01EE0;

static void func_01E01EE0_b232(Scene_b232_01E01EE0 *g) {
    extern void b232_01E01130(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F5380(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b232_01E01EE0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F5380(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b232_01E01130) {
                b232_01E01130(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
