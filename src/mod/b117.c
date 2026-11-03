#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b117(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E00120_b117(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b117", func_01E00270_b117);

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00C30_b117(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b117:01E00CB0, 239 insns, 1 copy (-O3,p): the effect scene step (the frame test 48/49/50 stays three compares
   at -O3): sets the scene colour to dark red, counts the frame (0x3B8C); frame 1 spawns 0x1E01D00; frames 48..50
   spawn twelve 0x1E01070 and nineteen 0x1E019D0 at the camera point, frame 49 also thirty-three 0x1E01640 and
   0x1E01780; frames 26..44 spawn thirteen 0x1E01290; frame 28 measures a 21-step drift from joint 0x3B78 (20 up) to
   the camera, spawns 0x1E01490 on the joint and fills the 10-point trail at 0x3A70 with it; frames 28..44 spawn five
   0x1E01BB0; every spawn gets a random turn (0x3B82) */

typedef struct {
    u8 pad0[0x80];
    f32 px, py, pz;
    u8 pad8C[0xD0 - 0x8C];
    f32 dx, dy, dz;
    u8 padDC[0x3A70 - 0xDC];
    Vec4f tr[10];
    u8 pad3B10[0x3B34 - 0x3B10];
    u8 col[4];
    u8 pad3B38[0x3B78 - 0x3B38];
    s16 joint;
    u8 pad3B7A[8];
    s16 ang;
    u8 pad3B84[8];
    s16 t;
} Scene_b117_01E00CB0;

static s32 func_01E02480_b117();
static s32 func_01E01070_b117();
static s32 func_01E01290_b117();
extern void b117_01E01490(void);
static s32 func_01E01640_b117();
static s32 func_01E01780_b117();
static s32 func_01E019D0_b117();
static s32 func_01E01BB0_b117();
static s32 func_01E01D00_b117();

#pragma optimization_level 3
#pragma opt_loop_invariants off

static void func_01E00CB0_b117(s32 arg0) {
    Scene_b117_01E00CB0 *g = (Scene_b117_01E00CB0 *)arg0;
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    Vec4f w;
    s32 i;
    s32 j;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 1) {
        func_01E02480_b117(g, (s32)func_01E01D00_b117, 0);
    }
    func_001F5F90(func_001F5380(), &v);
    if (g->t == 48 || g->t == 49 || g->t == 50) {
        for (i = 0; i < 12; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)func_01E01070_b117, 0);
        }
        for (i = 0; i < 19; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)func_01E019D0_b117, 0);
        }
    }
    if (g->t == 49) {
        for (i = 0; i < 33; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = v.y;
            g->pz = v.z;
            func_01E02480_b117(g, (s32)func_01E01640_b117, 0);
        }
        func_01E02480_b117(g, (s32)func_01E01780_b117, 0);
    }
    if (g->t > 25 && g->t < 45) {
        for (i = 0; i < 13; i++) {
            g->ang = func_0019A5C8() % 360;
            func_01E02480_b117(g, (s32)func_01E01290_b117, 0);
        }
    }
    if (g->t == 28) {
        func_001F5620(func_001F53A0(), g->joint, &w);
        g->dx = (v.x - w.x) / 21.0f;
        g->dy = (20.0f + v.y - w.y) / 21.0f;
        g->dz = (v.z - w.z) / 21.0f;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    if (g->t == 28) {
        for (j = 0; j < 1; j++) {
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)b117_01E01490, 0);
            {
                s32 k;
                Vec4f *p = g->tr;
                for (k = 0; k < 10; k++, p++) {
                    p->x = v.x;
                    p->y = *(f32 *)(u32)&v.y;
                    p->z = *(f32 *)(u32)&v.z;
                }
            }
        }
    }
    if (g->t >= 28 && g->t < 45) {
        for (i = 0; i < 5; i++) {
            g->ang = func_0019A5C8() % 360;
            func_01E02480_b117(g, (s32)func_01E01BB0_b117, 0);
        }
    }
}
#pragma opt_loop_invariants reset
#pragma optimization_level reset


/* shape b117:01E01070, 133 insns: b117:01E019D0's drifting mote in grey-purple: alpha up by 9 (below 0x60) for 10
   ticks, then fades by 10; h38 grows to 18 on odd ticks, the frame to 7 every third tick; drifts 12 a tick */

typedef struct {
    u8 pad0[0x3B90];
    u8 sin[1];
} Game_b117_01E01070;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b117_01E01070;

static s32 func_01E01070_b117(Game_b117_01E01070 *g, Obj_b117_01E01070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->ang = func_0019A5C8() % 360;
        o->sub = 0;
        o->turn = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 18) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->h8 = func_001A22C0(o->h8 + 12.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 12.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 12.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b117:01E01290, 126 insns: b117:01E019D0's drifting mote in yellow, placed at the scene point on start, alpha up by 0xF0
   on its first tick, drifting 10 a tick */

typedef struct {
    u8 pad0[0x3A70];
    f32 x, y, z;
    u8 pad3A7C[0x114];
    u8 sin[1];
} Game_b117_01E01290;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b117_01E01290;

static s32 func_01E01290_b117(Game_b117_01E01290 *g, Obj_b117_01E01290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->c0, 0x80, 0x80, 0);
    if (o->state == 1) {
        o->h38 = 1;
        o->ang = func_0019A5C8() % 360;
        o->sub = 0;
        o->turn = func_0019A5C8() % 360;
        o->x = func_001A22C0(g->x);
        o->y = func_001A22C0(g->y);
        o->z = func_001A22C0(g->z);
        o->state = 2;
    }
    if (o->t < 1) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] += 0xF0;
        }
    } else if (o->c0[3] > 0x28) {
        o->c0[3] -= 0x27;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 5 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->h8 = func_001A22C0(o->h8 + 10.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 10.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 10.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b117:01E01490, 105 insns, 1 copy: a red mote that leads the scene's trail: on start it resets its counters;
   each tick it pushes its position into the 10-point trail (func_01E00C30_b117), drifts by the scene's velocity in
   y and z and a tenth of the way to the target point in x, and writes itself back as the trail's head; it ends when
   the scene timer reaches 50 */

typedef struct {
    u8 pad0[0xD4];
    f32 vy;
    f32 vz;
    u8 padDC[0x3B00 - 0xDC];
    Vec4f trail[7];
    u8 pad3B70[0xA];
    s16 target;
    u8 pad3B7C[0x10];
    s16 timer;
} Game_b117_01E01490;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[4];
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b117_01E01490;

static s32 func_01E01490_b117(Game_b117_01E01490 *g, Obj_b117_01E01490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f p;
    Vec4f t;

    func_001076F0(o->c0, 0xFF, 0x80, 0x80);
    func_001076F0(o->c1, 0, 0, 0);
    if (o->state == 1) {
        o->h38 = 2;
        o->sub = 0;
        o->state = 2;
    }
    p.x = o->x;
    p.y = o->y;
    p.z = o->z;
    func_01E00C30_b117(g->trail, 10, 0, &p);
    o->z = func_001A22C0(o->z + g->vz);
    o->y = func_001A22C0(o->y + g->vy);
    func_001F5620(func_001F5380(), g->target, &t);
    {
        f32 d = (t.x - p.x) / 10.0f;
        o->x = func_001A22C0(o->x + d);
    }
    o->c0[3] = 0xFF;
    g->trail[1].x = o->x;
    g->trail[1].y = o->y;
    g->trail[1].z = o->z;
    if (g->timer == 50) {
        o->state = 0;
    }
    return 0;
}

/* shape b117:01E01640, 77 insns: a yellow spark: random frame 5..42 and sub-frame 0..3, random turn on all three axes; alpha
   up by 0x40 for 2 frames, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b117_01E01640;

static s32 func_01E01640_b117(void *arg0, Obj_b117_01E01640 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 38 + 5;
        o->sub = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->c0, 0x50, 0x50, 0);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->state = 2;
    }
    if (o->t < 2) {
        o->c0[3] += 0x40;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b117:01E01780, 40 insns: a yellow flash: fades in by 0x40 for 2 ticks, out by 10 and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b117_01E01780;

static s32 func_01E01780_b117(s32 arg0, Glow_b117_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 17;
        func_001076F0(o->col, 0x8F, 0x8F, 0);
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b117:01E01820, 108 insns, 2 copies: a blue swell by kind: random turn on all axes once; grows 1/3/2 a frame (kinds
   0/1/2, the last two capped at 50/30) and fades out after 11/26/21 frames of growth; turns 12 a frame */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    u8 pad32[2];
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Swell_b117_01E01820;

static s32 func_01E01820_b117(void *arg0, Swell_b117_01E01820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x30, 0x30, 0x60);
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x80;
    }
    if (o->kind == 0) {
        if (o->size > 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        o->size += 1;
    } else if (o->kind == 1) {
        if (o->size > 0x19) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x32) {
            o->size += 3;
        }
    } else {
        if (o->size > 0x14) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x1E) {
            o->size += 2;
        }
    }
    o->ang += 12;
    return 0;
}

/* shape b117:01E019D0, 119 insns: a yellow drifting mote: frame 5, random angle and turn; alpha up by 0xC0 for 6 frames, then
   down by 39 until it ends; sub-frame steps up to 7 every fifth frame; drifts 18 along its angle and bobs 18 by its turn */

typedef struct {
    u8 pad0[0x3B90];
    u8 sin[1];
} Game_b117_01E019D0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b117_01E019D0;

static s32 func_01E019D0_b117(Game_b117_01E019D0 *g, Obj_b117_01E019D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->c0, 0x80, 0x80, 0x40);
    if (o->state == 1) {
        o->h38 = 5;
        o->ang = func_0019A5C8() % 360;
        o->sub = 0;
        o->turn = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 6) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0xC0;
        }
    } else if (o->c0[3] > 0x28) {
        o->c0[3] -= 0x27;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 5 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->h8 = func_001A22C0(o->h8 + 18.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 18.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 18.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b117:01E01BB0, 82 insns: a grey spark at the game's point (b117:01E01640 shape): frame 25, random sub-frame 0..3 and turn
   on all three axes; alpha up by 0x40 for 2 frames, then down by 31 until it ends */

typedef struct {
    u8 pad0[0x3B10];
    f32 x, y, z;
} Game_b117_01E01BB0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b117_01E01BB0;

static s32 func_01E01BB0_b117(Game_b117_01E01BB0 *g, Obj_b117_01E01BB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x19;
        o->sub = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->c0, 0x48, 0x48, 0x48);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->state = 2;
    }
    o->x = g->x;
    o->y = g->y;
    o->z = g->z;
    if (o->t < 2) {
        o->c0[3] += 0x40;
    } else if (o->c0[3] > 0x20) {
        o->c0[3] -= 0x1F;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b117:01E01D00, 31 insns: func_001F7170(4, 0, &a, &b, 0) with copies of the module's floats at 0x01E02E00 and
   0x01E02E08; when the game value at 0x3B8C is 40 the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b117_01E01D00;

typedef struct {
    u8 pad0[0x3B8C];
    s16 v;
} Game_b117_01E01D00;

typedef struct {
    u8 pad0[0x36];
    s16 f36;
} Fx_b117_01E01D00;

extern F_b117_01E01D00 D_01E02E00_b117;
extern F_b117_01E01D00 D_01E02E08_b117;

static s32 func_01E01D00_b117(Game_b117_01E01D00 *g, Fx_b117_01E01D00 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b117_01E01D00 a;
    F_b117_01E01D00 b;

    a = D_01E02E00_b117;
    b = D_01E02E08_b117;
    func_001F7170(4, 0, &a, &b, 0);
    if (g->v == 40) {
        o->f36 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b117", func_01E01D80_b117);

/* shape b117:01E02480, 85 insns: spawns an effect: handler b117:01E01490 always takes slot 0, others the first free of slots
   1..219 (0x40 bytes, b089:01E030B0 shape); colours it from the context, places it at the context's position and stores the
   frame and both arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 c28[4];
    u8 c2C[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b117_01E02480;

typedef struct {
    u8 pad0[0x80];
    f32 pos[3];
    u8 pad8C[0x294 - 0x8C];
    Slot_b117_01E02480 slots[0xDC];
    u8 pad[0x3B34 - 0x294 - 0xDC * 0x40];
    u8 rgba[4];
    u8 pad3B38[0x50];
    s16 f3B88;
} Ctx_b117_01E02480;

static s32 func_01E02480_b117(Ctx_b117_01E02480 *ctx, s32 arg1, s32 arg2) {
    extern void b117_01E01490(void);
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b117_01E02480 *s = NULL;
    s16 i;

    if ((s32)b117_01E01490 == arg1) {
        func_00195108(&ctx->slots[0], 0x40);
        s = &ctx->slots[0];
        ctx->slots[0].used = 1;
    } else {
        for (i = 1; i < 0xDC; i++) {
            if (ctx->slots[i].used == 0) {
                func_00195108(&ctx->slots[i], 0x40);
                ctx->slots[i].used = 1;
                s = &ctx->slots[i];
                i = 0xDC;
            }
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f3B88;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b117:01E025E0, 132 insns: b117:01E02C00 family sprite draw for two callbacks (texture 0x99 for b117:01E01070, 0x9B for b117:01E01290), position + speed/10 in integers, no scale */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x16];
    void *cb;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b117_01E025E0;

typedef struct {
    u8 pad0[0x11C];
    s32 tex;
} Scene_b117_01E025E0;

static void func_01E025E0_b117(Scene_b117_01E025E0 *g, Fx_b117_01E025E0 *o, void *p, s32 mode) {
    extern void b117_01E01070(void);
    extern void b117_01E01290(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (mode == 0) {
        if (o->cb == b117_01E01070) {
            func_00106080(rm, 0x99, o->h34, rm);
        }
        if (o->cb == b117_01E01290) {
            func_00106080(rm, 0x9B, o->h34, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        if (o->cb == b117_01E01070) {
            func_00208700(p, g->tex, 1);
        }
        if (o->cb == b117_01E01290) {
            func_00208700(p, g->tex, 1);
        }
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x + o->dx / 10;
        pos.y = o->y + o->dy / 10;
        pos.z = o->z + o->dz / 10;
        func_00108EF0(m, NULL, rot, &pos);
        func_00108CE0(quad, o->size, o->size);
        func_00108F90(quad, p, m, v);
    }
}

/* shape b117:01E027F0, 142 insns: b117:01E02A30 family sprite (texture 0x9B) at position + speed/10 in integers, spun by its own rotation plus the scene's (ctx+0x3B20, growing 20/24/20 per draw), 2 wide and o->size tall */

/* OVL_WARM */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b117_01E027F0;

typedef struct {
    u8 pad0[0x11C];
    s32 tex;
    u8 pad120[0x3B20 - 0x120];
    s32 spin[3];
} Scene_b117_01E027F0;

static void func_01E027F0_b117(Scene_b117_01E027F0 *g, Fx_b117_01E027F0 *o, void *p, s32 lit) {
    f32 w;
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    Vec4f quad[4];
    f32 z[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9B, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    *(Vec4f *)rot = *(Vec4f *)o->rot;
    g->spin[0] += 20;
    g->spin[1] += 24;
    g->spin[2] += 20;
    rot[0] += g->spin[0];
    rot[1] += g->spin[1];
    rot[2] += g->spin[2];
    func_00108EF0(m, 0, rot, &pos);
    w = 2.0f;
    func_00108CE0(quad, w, o->size);
    if (func_00205630(quad, 0x70000000, m, p, z) != 0) {
        func_00109380(p, 0);
        func_002075F0((s32)p, v, (u32)z[0]);
    }
}

/* shape b117:01E02A30, 115 insns: draws a small depth-sorted sprite (b004:01E01860 shape): unlit, it sets up the colour and
   texture page; lit, it builds a matrix from its turn at its position plus a tenth of its drift, and sends the square of its
   size at its depth if it lands on screen */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b117_01E02A30;

typedef struct {
    u8 pad0[0x11C];
    s32 tex;
} Scene_b117_01E02A30;

static void func_01E02A30_b117(Scene_b117_01E02A30 *g, Fx_b117_01E02A30 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern s32 func_001A23B0(f32);
    Vec4f quad[4];
    Vec4f pos;
    f32 z[4];
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9b, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m, 0, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, z) != 0) {
        func_00109380(p, 0);
        func_002075F0((s32)p, v, func_001A23B0(z[0]));
    }
}

/* shape b117:01E02C00, 106 insns: mode 0 sets the drawing state (a 0x9B matrix from its angle 0x34, colour, the scene
   texture 0x11C); otherwise draws the effect as a camera-facing square of its size 0x38: camera rotation, world matrix (scale 0.1) at its position offset by
   a tenth of 0x8..0xC, then func_00108F90 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b117_01E02C00;

typedef struct {
    u8 pad0[0x11C];
    s32 tex;
} Scene_b117_01E02C00;

static void func_01E02C00_b117(Scene_b117_01E02C00 *g, Fx_b117_01E02C00 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;
    f32 t;

    v = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x9B, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        func_00205C40((s32)rot);
        t = o->dx;
        t /= 10.0f;
        pos.x = o->x;
        pos.x += t;
        t = o->dy;
        t /= 10.0f;
        pos.y = o->y;
        pos.y += t;
        t = o->dz;
        t /= 10.0f;
        pos.z = o->z;
        pos.z += t;
        func_00108EF0(m, &scale, rot, &pos);
        func_00108CE0(quad, o->size, o->size);
        func_00108F90(quad, p, m, v);
    }
}
