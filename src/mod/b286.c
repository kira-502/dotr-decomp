#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b286(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b286:01E004D0, 312 insns: B286_W_S, the effect scene's step (b522:01E01D30 form): colour 0x80,0,0,0, counts
   the frame (0x6AE4); frames 52..152 spawn 0x1E01130 on sides 0..5; frame 22 ten rounds of it on sides 0..5;
   frames 62..104 spawn 0x1E00B40 jittered around joints 0x6AC4 and 0x6AC6; frame 105 puts the point on joint
   0x6ACA and spawns ten 0x1E009B0 per side 0/1 and fifty 0x1E00F90; frames 105..115 spawn 0x1E00C60 */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x6A84 - 0x90];
    u8 col[4];
    u8 pad6A88[0x6AC4 - 0x6A88];
    s16 ja;
    s16 jb;
    u8 pad6AC8[2];
    s16 jc;
    u8 pad6ACC[0x6ADE - 0x6ACC];
    s16 side;
    u8 pad6AE0[4];
    s16 t;
} Scene_b286_01E004D0;

static void func_01E004D0_b286(Scene_b286_01E004D0 *g) {
    extern void b286_01E009B0(void);
    extern void b286_01E00B40(void);
    extern void b286_01E00C60(void);
    extern void b286_01E00F90(void);
    extern void b286_01E01130(void);
    extern void b286_01E01990(Scene_b286_01E004D0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t < 153) {
        if (g->t >= 52) {
            g->side = 0;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 1;
            b286_01E01990(g, b286_01E01130, 0);
        }
        if (g->t >= 52) {
            g->side = 2;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 3;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 4;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 5;
            b286_01E01990(g, b286_01E01130, 0);
        }
    }
    if (g->t == 22) {
        for (i = 0; i < 10; i++) {
            g->side = 0;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 1;
            b286_01E01990(g, b286_01E01130, 0);
        }
    }
    if (g->t == 22) {
        for (i = 0; i < 10; i++) {
            g->side = 2;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 3;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 4;
            b286_01E01990(g, b286_01E01130, 0);
            g->side = 5;
            b286_01E01990(g, b286_01E01130, 0);
        }
    }
    if (g->t > 61 && g->t < 105) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x - (func_0019A5C8() % 10 - 5);
        if (g->t >= 73) {
            g->pos.x = v.x + (func_0019A5C8() % 10 - 5);
        }
        g->pos.y = v.y + func_0019A5C8() % 15;
        g->pos.z = v.z;
        b286_01E01990(g, b286_01E00B40, 0);
        func_001F5620(func_001F53A0(), g->jb, &v);
        g->pos.x = v.x - (func_0019A5C8() % 10 - 5);
        if (g->t >= 73) {
            g->pos.x = v.x + (func_0019A5C8() % 10 - 5);
        }
        g->pos.y = v.y + func_0019A5C8() % 15;
        g->pos.z = v.z;
        b286_01E01990(g, b286_01E00B40, 0);
    }
    if (g->t == 105) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
        for (i = 0; i < 10; i++) {
            b286_01E01990(g, b286_01E009B0, 0);
        }
        g->side = 1;
        for (i = 0; i < 10; i++) {
            b286_01E01990(g, b286_01E009B0, 0);
        }
        for (i = 0; i < 50; i++) {
            b286_01E01990(g, b286_01E00F90, 0);
        }
    }
    if (g->t >= 105 && g->t <= 115) {
        b286_01E01990(g, b286_01E00C60, 0);
    }
}

/* shape b286:01E009B0, 99 insns: an orange or teal (by kind) streak: frame 15 growing by 4, random tilt 0..0x3FFF, turn and
   sub-frame 0..6; alpha up by 0x50 for 2 frames, then down by 13 once grown past 15, and by 15 when the scene timer drops under 10 */

typedef struct {
    u8 pad0[0x6A80];
    s32 timer;
} Scene_b286_01E009B0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 rot0;
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b286_01E009B0;

static s32 func_01E009B0_b286(Scene_b286_01E009B0 *g, Obj_b286_01E009B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->state == 1) {
        o->h38 = 0xF;
        base = 0;
        o->rot0 = func_0019A5C8() % 0x4000 + base;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
        o->h6 = 1;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c0, 0, 0x80, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 0xF) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->timer < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    o->t++;
    o->h38 += 4;
    return 0;
}

/* shape b286:01E00B40, 70 insns: an orange flame: set up once (reads the model's point, clears its y turn), alpha up by
   0x40 for 2 frames, then down by 9; frame 50; fades faster (13) while the game state is below 15; rises 5 a frame */

typedef struct {
    u8 pad0[0x6A80];
    s32 state;
} Game_b286_01E00B40;

typedef struct {
    u8 pad0[0xE];
    s16 y;
    u8 pad10[4];
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b286_01E00B40;

static s32 func_01E00B40_b286(Game_b286_01E00B40 *g, Obj_b286_01E00B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    Vec4f v;

    func_001076F0(o->c0, 0x80, 0x40, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), &v);
        o->rot1 = 0;
        o->h34 = 0;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (g->state < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    o->y += 5;
    return 0;
}

/* OVL_WARM */

/* shape b286:01E00C60, 202 insns: b194:01E01180 with the game fields moved (joints g+0x6AC4/0x6AC8, step 0x6AE4, counter 0x6A80): reads the model angle and keeps whether its turn / 180 is non-zero; on start 0x38 =
   10..19, no spin, variant 0..6, 0x6 = 5..19, random 0x3A; before game step 0x60 it sits on joint A (g+0x6AC4); alpha
   up by 0x40 (below 0x80) for 2 ticks, then fades by 13 after 0x38 passes 25 and by 15 while the counter 0x6A80 is
   below 10; colour (0x20, 0x20, 0); aims at joint B (g+0x6AC8): pitch from the flat and full distances
   (func_001082B0) times 180, mirrored by the turn, before step 0x60 */

typedef struct {
    u8 pad0[0x6A80];
    s32 count;
    u8 pad6A84[0x6AC4 - 0x6A84];
    s16 ja;
    u8 pad6AC6[2];
    s16 jb;
    u8 pad6ACA[0x6AE4 - 0x6ACA];
    s16 step;
} Game_b286_01E00C60;

typedef struct {
    s16 x, y, z;
    s16 f6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b286_01E00C60;

static s32 func_01E00C60_b286(Game_b286_01E00C60 *g, Fx_b286_01E00C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001A6C60(f32);
    extern s16 func_001082B0(s32, s32);
    f32 v[8];
    s32 ang[4];
    s32 turn;
    f32 *q;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 r;
    s16 l;
    s16 a;

    func_001F6160(func_001F53A0(), ang);
    turn = (s16)(ang[1] / 180.0f);
    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 10 + 10;
        o->w18 = 0;
        o->w10 = 0;
        o->w14 = 0;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f6 = func_0019A5C8() % 15 + 5;
        o->f3A = func_0019A5C8() % 360;
    }
    func_001F5620(func_001F53A0(), g->ja, v);
    func_001F5620(func_001F53A0(), g->jb, q = (f32 *)(u32)&v[4]);
    if (g->step < 0x60) {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->f38 > 25) {
            if (o->col[3] > 14) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 16) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x20, 0x20, 0);
    dx = v[0] - q[0];
    dy = v[1] - v[5];
    dz = v[2] - v[6];
    r = func_001A6C60(dx * dx + dz * dz);
    l = func_001A6C60(dx * dx + (dy * dy + dz * dz));
    a = func_001082B0(r, l);
    if (g->step < 0x60) {
        if (turn != 0) {
            o->w10 = a * 180;
        } else {
            o->w10 = -a * 180;
        }
    }
    o->tick++;
    o->f38++;
    return 0;
}

/* shape b286:01E00F90, 101 insns: an orange ember (size 13, frame 2) at two random angles drifting 13 a tick on all three axes (sine table ctx+0x6AE8): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[2];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b286_01E00F90;

typedef struct {
    u8 pad[0x6ae8];
    u8 sin[1];
} Game_b286_01E00F90;

static s32 func_01E00F90_b286(Game_b286_01E00F90 *g, Glow_b286_01E00F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 13;
        o->kind = 2;
        func_001076F0(o->col, 0x60, 0x40, 0);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 13.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 13.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 13.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b286:01E01130, 175 insns: b112:01E01A60's puff (lilac 0x3F/0x30/0x3F for kinds 0-1, grey 0x10 else), size from 15 growing 7 to 60, frame up to 7 every other tick, angles 0..359 / 0..89; alpha up by 0x20 to 0x60 for 3 ticks, then down by 9; for its first 5 ticks sits on its tracked point (ctx+0x6AC4 by kind; kinds 2+ only for 3); drifts 8 along the heading and 2 up */

typedef struct {
    u8 pad0[0x6AC4];
    s16 ids[4];
    u8 pad6ACC[0x6AE8 - 0x6ACC];
    u8 trig[1];
} Game_b286_01E01130;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b286_01E01130;

static s32 func_01E01130_b286(Game_b286_01E01130 *g, Fx_b286_01E01130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];

    if (o->mode == 1) {
        if (o->kind < 2) {
            func_001076F0(o->col, 0x3F, 0x30, 0x3F);
        } else {
            func_001076F0(o->col, 0x10, 0x10, 0x10);
        }
        o->f38 = 15;
        o->heading = func_0019A5C8() % 360;
        o->f34 = 0;
        o->h6 = func_0019A5C8() % 90;
        o->mode = 2;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick < 6) {
        func_001F5620(func_001F53A0(), g->ids[o->kind], v);
        if (o->kind < 2) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        } else if (o->tick < 4) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        }
    }
    if (o->f38 < 60) {
        o->f38 += 7;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->h8 = o->h8 + 8.0f * func_00108030(g->trig, o->heading, 0);
    o->hA = o->hA + 2.0f * func_00108030(g->trig, o->h6, 1);
    o->hC = o->hC + 8.0f * func_00108030(g->trig, o->heading, 1);
    return 0;
}

/* shape b286:01E013F0, 54 insns: volume fade: starts at 0x80; while the game counter at 0x6A80 is over 0x1E it drops by
   10 to 0x30, otherwise it rises by 10 (clamped) and stops at 0x80; func_001F6D00 gets it when the counter is 1,
   else the volume */

typedef struct {
    u8 pad0[0x6A80];
    s32 count;
} Game_b286_01E013F0;

typedef struct {
    u8 pad0[0x30];
    s16 v;
    u8 pad32[0x4];
    s16 mode;
} Fx_b286_01E013F0;

static s32 func_01E013F0_b286(Game_b286_01E013F0 *g, Fx_b286_01E013F0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
            o->mode = 0;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b194:01E01AE0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E02500_b286;
extern f32 D_01E02508_b286;

static s32 func_01E014D0_b286(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02500_b286;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02508_b286;
    func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b286:01E01520 (b286), 284 insns, 1 copy: b286 scene manager (b069:01E01210 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 170-frame countdown, takes six model handles and loads
   textures 14, 15 and 2; otherwise it runs the module step and every live node update (the last helper inlined), then
   draws every live node twice by its callback, counts down and returns 1 / 4 / 2 at frames 95 / 130 / 105, 8 once the
   countdown runs out */

typedef struct Fx_b286_01E01520 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[0x8];
} Fx_b286_01E01520;

typedef struct Scene_b286_01E01520 {
    u8 pad0[0xE0];
    s32 tex[16];
    Fx_b286_01E01520 fx[420];
    u8 pad6A20[0x60];
    s32 count;
    u8 pad6A84[8];
    s32 ot;
    u8 pad6A90[0x34];
    s16 model[6];
    u8 pad6AD0[0x12];
    s16 id;
    s16 timer;
    u8 pad6AE6[2];
    u8 cam[0x178];
} Scene_b286_01E01520;

static s32 func_01E01520_b286(s32 arg0, s32 id) {
    Scene_b286_01E01520 *g = (Scene_b286_01E01520 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 D_01E02500_b286;
    extern f32 D_01E02508_b286;
    extern void func_01E004D0_b286();
    extern s32 func_01E009B0_b286();
    extern s32 func_01E00B40_b286();
    extern s32 func_01E00C60_b286();
    extern s32 func_01E00F90_b286();
    extern s32 func_01E01130_b286();
    extern s32 func_01E013F0_b286();
    extern s32 func_01E014D0_b286();
    extern void b286_01E01AB0();
    extern void b286_01E01D40();
    extern void b286_01E01FC0();
    extern void b286_01E022A0();
    s32 j;
    s32 n;
    Vec4f v;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x6C60);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 170;
        g->model[0] = func_001F5560(func_001F53A0(), 0x18, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0xB, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 1, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x33, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0x21, 0);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        return 0;
    }
    func_01E004D0_b286(g, 0);
    for (j = 0; j < 420; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == func_01E009B0_b286) {
                func_01E009B0_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00B40_b286) {
                func_01E00B40_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00C60_b286) {
                func_01E00C60_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00F90_b286) {
                func_01E00F90_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01130_b286) {
                func_01E01130_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E013F0_b286) {
                func_01E013F0_b286(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E014D0_b286) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02500_b286;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02508_b286;
                func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 420; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E009B0_b286) {
                b286_01E01D40(g, &g->fx[i], buf, 0);
                b286_01E01D40(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00B40_b286) {
                b286_01E01AB0(g, &g->fx[i], buf, 0);
                b286_01E01AB0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00C60_b286) {
                b286_01E01FC0(g, &g->fx[i], buf, 0);
                b286_01E01FC0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00F90_b286) {
                b286_01E022A0(g, &g->fx[i], buf, 0);
                b286_01E022A0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01130_b286) {
                b286_01E022A0(g, &g->fx[i], buf, 0);
                b286_01E022A0(g, &g->fx[i], buf, 1);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 95) {
        return 1;
    }
    if (g->timer == 130) {
        return 4;
    }
    if (g->timer == 105) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b286:01E01990, 72 insns: twin of b046:01E03E20: take the first free slot of the 420-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x6ADE and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b286_01E01990;

typedef struct {
    u8 pad[0x80];
    u8 m[0xA0];
    Slot_b286_01E01990 s[420];
    u8 pad6A20[0x64];
    u8 r, g, b, a;
    u8 pad6A88[0x56];
    s16 v;
} Pool_b286_01E01990;

static s32 func_01E01990_b286(Pool_b286_01E01990 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b286_01E01990 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 420; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 420;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b286:01E01AB0, 164 insns: b194:01E022C0 with callback b286:01E01130, textures at ctx+0xE8 / 0x11C and width 2 */

/* OVL_WARM */

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 dx, dy, dz;
    s16 hE;
    u8 pad10[0x14];
    void *cb;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b286_01E01AB0;

typedef struct {
    u8 pad0[0xE8];
    s32 tex2;
    u8 padT[0x11C - 0xE8 - 4];
    s32 tex;
} Scene_b286_01E01AB0;

static void func_01E01AB0_b286(Scene_b286_01E01AB0 *g, Fx_b286_01E01AB0 *o, void *p, s32 lit) {
    extern void b286_01E01130(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 a[4];
    s32 v;
    f32 ax, ay, az;

    v = (s32)func_00207500();
    if (lit == 0) {
        if (o->cb == b286_01E01130) {
            func_00106080(rm, 0x14, o->h34, rm);
        } else {
            func_00106080(rm, 0x9B, o->h34, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        if (o->cb == b286_01E01130) {
            func_00208700(p, g->tex2, 1);
            return;
        }
        func_00208700(p, g->tex, 1);
        return;
    }
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_001F6160(func_001F53A0(), a);
    rot[1] = -(a[1] - 16384.0f);
    rot[0] = 0;
    rot[2] = 0;
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, 2.0f);
    quad[0].x = 0.0f;
    quad[2].x = 0.0f;
    func_00107070(quad, 0, o->hE);
    quad[1].y += o->h6;
    quad[3].y += o->h6;
    func_00107070(quad, 1, o->h6);
    func_00108F90(quad, p, m, v);
}

/* shape b286:01E01D40, 158 insns: variant of b112:01E039F0 (flat ring of 9 quads, each 2 wide) with the texture at 0x11C, the
   target/depth/trig table at 0x6A8C/0x6AB4/0x6AE8, and an additive blend (0x80, 0x42) when the anim's w is set */

typedef struct {
    f32 x, y, z, w;
} Vec_b286_01E01D40;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b286_01E01D40;

typedef struct {
    u8 pad00[0x11C];
    s32 texture;
    u8 pad120[0x6A8C - 0x120];
    s32 target;
    u8 pad31B0[0x6AB4 - 0x6A90];
    f32 depth;
    u8 pad31CC[0x6AE8 - 0x6AB8];
    u8 trig[1];
} Game_b286_01E01D40;

static void func_01E01D40_b286(Game_b286_01E01D40 *g, Anim_b286_01E01D40 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b286_01E01D40 quad[4];
    Vec_b286_01E01D40 pos;
    Vec_b286_01E01D40 scale;
    f32 m[16];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        if (an->w != 0) {
            func_002086D0(p, 0x8000000042);
        }
        pos.x = an->x;
        pos.y = an->y;
        pos.z = an->z;
        scale.x = 1.0f;
        scale.y = 1.5f;
        scale.z = 1.0f;
        func_00108EF0(m, &scale, an->rot, &pos);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        for (k = 0; k < 9; k++) {
            a = an->start + j;
            quad[2].x = an->radius * func_00108030(g->trig, a, 1);
            quad[2].z = an->radius * func_00108030(g->trig, a, 0);
            quad[0].x = 0.0f;
            quad[0].z = 0.0f;
            a = j + (an->start + 2);
            quad[3].x = an->radius * func_00108030(g->trig, a, 1);
            quad[3].z = an->radius * func_00108030(g->trig, a, 0);
            quad[1].x = 0.0f;
            quad[1].z = 0.0f;
            if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
            j += 40;
        }
    }
}

/* shape b286:01E01FC0, 182 insns: b195:01E02A40's fan of 9 thin triangles (span 1) with the rim raised to the object's
   h6, scaled 1 x 1.5 x 1 at the object's position; mode 0 sets up the packet with texture 0x97. Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b286_01E01FC0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b286_01E01FC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b286_01E01FC0 c;
    struct {
        u64 tc;
        Xyz_b286_01E01FC0 p;
    } v[4];
} Pkt_b286_01E01FC0;

typedef struct {
    u8 pad0[0x11C];
    void *texture;
    u8 pad120[0x696C];
    s32 ot;
    u8 pad6A90[0x24];
    f32 dep;
    u8 pad6AB8[0x30];
    u8 trig[1];
} Ctx_b286_01E01FC0;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b286_01E01FC0;

static void func_01E01FC0_b286(Ctx_b286_01E01FC0 *c, Fan_b286_01E01FC0 *o, Pkt_b286_01E01FC0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b286_01E01FC0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 t;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00080_b286((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = o->h6;
    quad[3].y = o->h6;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + 1);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b286:01E022A0, 134 insns: b112:01E04260's textured square with handler shape b286:01E01130 and scene textures 0xE8 / 0x11C */


typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x16];
    void *fn;
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b286_01E022A0;

static void func_01E022A0_b286(u8 *ctx, Obj_b286_01E022A0 *o, void *pkt, s32 mode) {
    extern s32 b286_01E01130();
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        if (o->fn == (void *)b286_01E01130) {
            func_00106080(td, 0x14, o->page, td);
        } else {
            func_00106080(td, 0x9B, o->page, td);
        }
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        if (o->fn == (void *)b286_01E01130) {
            func_00208700(pkt, *(void **)(ctx + 0xE8), 1);
            return;
        }
        func_00208700(pkt, *(void **)(ctx + 0x11C), 1);
        return;
    }
    if (o->fn == (void *)b286_01E01130) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)&rot);
    dx = o->vx;
    dy = o->vy;
    dz = o->vz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = o->x + dx;
    pos.y = o->y + dy;
    pos.z = o->z + dz;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}
