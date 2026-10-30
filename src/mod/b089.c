#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b089(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b089:01E00100, 220 insns: event step: colour 0x80/0/0/0, tick h3B88; tick 1 spawns 0x1E026B0; follows the
   joint h3B74; on odd ticks 85..159 spawns three 0x1E00470 sparks at a random height 32..61; follows joint h3B76;
   at tick 200 places itself there, fills the 9-point trail from joint h3B74, sets a ring of 6 points (radius 14,
   60 apart) in both point lists, spawns 6 each of 0x1E00A30 / 0x1E014C0 / 0x1E016D0 and resets the 10-point
   trail; then a 6-step delay loop and the final joint update */

typedef struct {
    f32 x, y, z, w;
} Vec_b089_01E00100;

typedef struct {
    f32 x, y, z;
    u8 pad0C[0x1230 - 0xC];
    Vec_b089_01E00100 ringA[6];
    u8 pad1290[0x1C50 - 0x1290];
    Vec_b089_01E00100 ringB[6];
    u8 pad1CB0[0x2640 - 0x1CB0];
    Vec_b089_01E00100 trail[10];
    u8 pad26E0[4];
    u8 col[4];
    u8 pad26E8[0x3B74 - 0x26E8];
    s16 joint0;
    s16 joint1;
    u8 pad3B78[6];
    s16 dir;
    u8 pad3B80[4];
    s16 slot;
    u8 pad3B86[2];
    s16 tick;
    u8 pad3B8A[2];
    u8 tbl[1];
} Scene_b089_01E00100;

static void func_01E00100_b089(Scene_b089_01E00100 *g) {
    extern s32 b089_01E031D0(void *, s32, s32);
    extern s32 b089_01E030B0(void *, s32, s32);
    extern void b089_01E026B0(void);
    extern void b089_01E00470(void);
    extern void b089_01E00A30(void);
    extern void b089_01E014C0(void);
    extern void b089_01E016D0(void);
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[4];
    f32 w[4];
    s32 i;
    s32 a;
    s32 j;
    s32 k;
    Vec_b089_01E00100 *e;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    a = 0;
    if (g->tick == 1) {
        b089_01E031D0(g, (s32)b089_01E026B0, 0);
    }
    func_001F5620(func_001F53A0(), g->joint0, v);
    if (g->tick > 0x54 && g->tick % 2 == 1 && g->tick <= 0x9F) {
        for (i = 0; i < 3; i++) {
            g->dir = func_0019A5C8() % 360;
            g->x = v[0];
            g->y = func_0019A5C8() % 30 + 32;
            g->z = v[2];
            b089_01E031D0(g, (s32)b089_01E00470, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->joint1, v);
    if (g->tick == 200) {
        g->dir = func_0019A5C8() % 360;
        e = g->trail;
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        func_001F5620(func_001F53A0(), g->joint0, w);
        for (k = 0; k < 9; k++) {
            e->x = w[0];
            e->y = w[1];
            e->z = w[2];
            e++;
        }
        for (k = 0; k < 6; k++) {
            g->ringA[k].x = g->ringB[k].x = v[0] + 14.0f * func_00108030(g->tbl, a, 1);
            g->ringA[k].y = g->ringB[k].y = v[1] + 14.0f * func_00108030(g->tbl, a, 0);
            g->ringA[k].z = g->ringB[k].z = v[2];
            a += 60;
        }
        for (i = 0; i < 6; i++) {
            g->slot = i;
            b089_01E030B0(g, (s32)b089_01E00A30, 0);
        }
        for (i = 0; i < 6; i++) {
            g->slot = i;
            b089_01E030B0(g, (s32)b089_01E014C0, 0);
        }
        for (i = 0; i < 6; i++) {
            g->slot = i;
            b089_01E030B0(g, (s32)b089_01E016D0, 0);
        }
        e = g->trail;
        for (j = 0; j < 10; j++) {
            e->x = v[0];
            e->y = v[1];
            e->z = v[2];
            e++;
        }
    }
    for (k = 0; k < 6; k++) {
    }
    func_001F5F90(func_001F5380(), v);
}

/* shape b089:01E00470, 73 insns: a grey smoke puff of random size 10..24, frame 0..14 and two random angles: in by 9 up to 0x60 for 10 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b089_01E00470;

static s32 func_01E00470_b089(s32 arg0, Glow_b089_01E00470 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 15 + 10;
        o->ang = func_0019A5C8() % 360;
        o->col[3] = 0;
        o->kind = func_0019A5C8() % 15;
        o->h30 = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b089:01E005A0, 79 insns: colour (0x5F, 0x50, 0x50); register its position with the game (b089:01E00080 on
   0x26D0, kind 10); sink z by 7 x the sine of the model angle - 180; on start 0x38 = 5; alpha 0x50, tick 8 */

typedef struct {
    u8 pad0[0x26D0];
    u8 list[0x3B8C - 0x26D0];
    u8 trig[1];
} Game_b089_01E005A0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b089_01E005A0;

static s32 func_01E005A0_b089(Game_b089_01E005A0 *g, Fx_b089_01E005A0 *o) {
    extern void b089_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    Vec4f pos;
    s32 ang[4];

    func_001076F0(o->col, 0x5F, 0x50, 0x50);
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    b089_01E00080(g->list, 10, 0, &pos);
    func_001F6160(func_001F53A0(), ang);
    o->z = o->z - 7.0f * func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    o->col[3] = 0x50;
    o->tick = 8;
    return 0;
}

/* shape b089:01E006E0, 107 insns: b266:01E01610 family: a blue ember (size 5, random frame 0..3) at two random angles drifting 9 a tick on all three axes (sine table ctx+0x3B8C): alpha 0x80 for 10 ticks, then out by 10 and ends */

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
} Glow_b089_01E006E0;

typedef struct {
    u8 pad[0x3B8C];
    u8 sin[1];
} Game_b089_01E006E0;

static s32 func_01E006E0_b089(Game_b089_01E006E0 *g, Glow_b089_01E006E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 5;
        o->kind = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0x1F, 0x1F, 0xFF);
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
    o->h8 = func_001A22C0(o->h8 + 9.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 9.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 9.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b089:01E00890, 102 insns: a dark drifting puff (b194:01E015C0 shape): frame 4, sub-frame 2, random angles; alpha 0x60
   for 4 frames, then down by 9 until it ends; drifts 24 along its angle and bobs 24 by its second angle */

typedef struct {
    u8 pad0[0x3B8C];
    u8 sin[1];
} Game_b089_01E00890;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 bob;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b089_01E00890;

static s32 func_01E00890_b089(Game_b089_01E00890 *g, Obj_b089_01E00890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 4;
        o->sub = 2;
        func_0019A5C8();
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->bob = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 4) {
        o->c0[3] = 0x60;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 24.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 24.0f * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + 24.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E00A30_b089);

/* shape b089:01E013A0, 70 insns: a dark smoke puff (size 13) cycling frames 0..6 from a random start: in by 48 up to 0x60 for 2 ticks; out by 5 once the scene counter is under 25, then ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b089_01E013A0;

typedef struct {
    u8 pad[0x26E0];
    s32 count;
} Game_b089_01E013A0;

static s32 func_01E013A0_b089(Game_b089_01E013A0 *g, Glow_b089_01E013A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x10, 0x10, 0x10);
    if (o->mode == 1) {
        o->kind = func_0019A5C8() % 5;
        o->f38 = 13;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    }
    if (o->tick != 0) {
        if (o->kind < 6) {
            o->kind++;
        } else {
            o->kind = 0;
        }
    }
    o->tick++;
    if (g->count < 25) {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* OVL_WARM */

/* shape b089:01E014C0, 131 insns: a dark red glow riding a scene point: random spin words, frame 0..4, size 7; alpha
   grows by 9 (below 0x60) for 10 ticks; the frame cycles 0..6 after the first tick; it sits on point[k]; the point's
   state grows the size to 12 (state 1) or sets 14 (state 2); fades by 9 once the scene timer drops below 20 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 k;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
} Fx_b089_01E014C0;

typedef struct {
    u8 pad0[0x1C50];
    Vec4f pt[0xA9];
    s32 timer;
    u8 pad26E4[0x1484];
    s16 state[1];
} Scene_b089_01E014C0;

static s32 func_01E014C0_b089(Scene_b089_01E014C0 *g, Fx_b089_01E014C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x40, 0x20, 0x20);
    if (o->mode == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->frame = func_0019A5C8() % 5;
        o->size = 7;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    }
    if (o->t != 0) {
        if (o->frame < 6) {
            o->frame++;
        } else {
            o->frame = 0;
        }
    }
    o->t++;
    o->x = g->pt[o->k].x;
    o->y = g->pt[o->k].y;
    o->z = g->pt[o->k].z;
    if (g->state[o->k] == 1) {
        if (o->size < 12) {
            o->size++;
        }
    }
    if (g->state[o->k] == 2) {
        o->size = 14;
    }
    if (g->timer < 20) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape b089:01E016D0, 308 insns: a white flame on scene point n (ctx+0x1C50 table, 1 higher): random spin words,
   frame 0..4 cycling 0..6, size 3; alpha in by 12 below 0x80 for 10 ticks; while the point's state (ctx+0x3B68) is 1
   it grows to 6 every third tick; when it turns 2 it greys, sets size 13 and spawns three b089:01E013A0 puffs
   (jitter 10, numbered) and four b089:01E01D90 + b089:01E024F0 pairs (jitter 15 / 10, the latter lowered by 8 x the
   camera-angle sine); fades by 7 and ends once the scene counter (ctx+0x26E0) is under 25 */

typedef struct {
    f32 x, y, z, w;
} V4_b089_01E016D0;

typedef struct {
    f32 px, py, pz;
    u8 padC[0x1C50 - 0xC];
    V4_b089_01E016D0 pt[1];
    u8 pad1C60[0x26E0 - 0x1C60];
    s32 count;
    u8 pad26E4[0x3B68 - 0x26E4];
    s16 state[1];
    u8 pad3B6A[0x3B84 - 0x3B6A];
    s16 idx;
    u8 pad3B86[6];
    u8 sin[4];
} Game_b089_01E016D0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0xA];
    s32 r10;
    s32 r14;
    s32 r18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 n;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
} Obj_b089_01E016D0;

static s32 func_01E013A0_b089();
static s32 func_01E01D90_b089();
static s32 func_01E024F0_b089();
static s32 func_01E031D0_b089();

static s32 func_01E016D0_b089(Game_b089_01E016D0 *g, Obj_b089_01E016D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0();
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s32, s32);
    s32 cam[4];
    s16 i;
    s16 j;
    s16 a;

    func_001076F0(o->col, 0x80, 0x80, 0x80);
    if (o->mode == 1) {
        o->r10 = func_0019A5C8() % 0xFFFF;
        o->r14 = func_0019A5C8() % 0xFFFF;
        o->r18 = func_0019A5C8() % 0xFFFF;
        o->frame = func_0019A5C8() % 5;
        o->size = 3;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0xC;
        }
    }
    if (o->t != 0) {
        if (o->frame < 6) {
            o->frame++;
        } else {
            o->frame = 0;
        }
    }
    o->t++;
    o->x = g->pt[o->n].x;
    o->y = 1.0f + g->pt[o->n].y;
    o->z = g->pt[o->n].z;
    if (g->state[o->n] == 1) {
        if (o->size < 6 && o->t % 3 == 1) {
            o->size++;
        }
    }
    if (g->state[o->n] == 2) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->size = 0xD;
        for (i = 0; i < 3; i++) {
            g->px = o->x + func_0019A5C8() % 20 - 10;
            g->py = o->y + func_0019A5C8() % 20 - 10;
            g->pz = o->z;
            g->idx = i;
            func_01E031D0_b089(g, func_01E013A0_b089, 0);
        }
        for (j = 0; j < 4; j++) {
            g->px = o->x + func_0019A5C8() % 30 - 15;
            g->py = o->y + func_0019A5C8() % 30 - 15;
            g->pz = o->z;
            func_01E031D0_b089(g, func_01E01D90_b089, 0);
            func_001F6160(func_001F53A0(), cam);
            a = 8.0f * -func_00108030(g->sin, (s16)(cam[1] / 180.0f) - 180, 1);
            g->px = o->x + func_0019A5C8() % 20 - 10;
            g->py = o->y + func_0019A5C8() % 20 - 10;
            g->pz = o->z + a;
            func_01E031D0_b089(g, func_01E024F0_b089, 0);
        }
    }
    if (g->count < 25) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape b089:01E01BA0, 123 insns: a white spark on scene point h3B76: random spin words, size 14..23; alpha in by 16 up
   to 0xA0 for 10 ticks, then out by 19 and ends; placed at the point, its height lowered by twice the sine of the
   camera's angle */

typedef struct {
    u8 pad0[0x3B76];
    s16 point;
    u8 pad3B78[0x14];
    u8 sin[4];
} Game_b089_01E01BA0;

typedef struct {
    s16 x;
    s16 pad2;
    s16 y;
    u8 pad6[0xA];
    s32 r10;
    s32 r14;
    s32 r18;
    u8 pad1C[0xC];
    u8 c28[4];
    u8 c2C[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 size;
} Obj_b089_01E01BA0;

static s32 func_01E01BA0_b089(Game_b089_01E01BA0 *g, Obj_b089_01E01BA0 *o) {
    extern s32 func_001F53A0();
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F6160(s32, s32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s32, s32);
    f32 pos[4];
    s32 cam[4];
    s16 a;

    func_001F5620(func_001F53A0(), g->point, pos);
    if (o->mode == 1) {
        func_001076F0(o->c28, 0x80, 0x80, 0x80);
        func_001076F0(o->c2C, 0x80, 0x80, 0x80);
        o->r10 = func_0019A5C8() % 0xFFFF;
        o->r14 = func_0019A5C8() % 0xFFFF;
        o->r18 = func_0019A5C8() % 0xFFFF;
        o->size = func_0019A5C8() % 10 + 14;
        o->mode = 2;
        o->c28[3] = 0;
        o->c2C[3] = 0;
    }
    if (o->t < 10) {
        if (o->c28[3] < 0xA0) {
            o->c28[3] += 0x10;
        }
    } else if (o->c28[3] > 0x14) {
        o->c28[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    o->t++;
    func_001F6160(func_001F53A0(), cam);
    a = 2.0f * -func_00108030(g->sin, (s16)(cam[1] / 180.0f) - 180, 1);
    o->x = pos[0];
    o->y = pos[2] - a;
    return 0;
}

typedef struct {
    u8 pad0000[0x3B8C];
    u8 tab[1];
} Mgr_b089_01E01D90;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b089_01E01D90;

static s32 func_01E01D90_b089(Mgr_b089_01E01D90 *m, Obj_b089_01E01D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 11;
        o->h34 = 2;
        func_0019A5C8();
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->h30 = func_0019A5C8() % 360;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 4) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h34 < 6) {
        o->h34++;
    } else {
        o->h34 = 0;
    }
    o->h32++;
    o->x = o->x + 10.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 10.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* OVL_WARM */

/* shape b089:01E01F50, 99 insns: a white smoke puff (size 16, frames cycling 2..6) pinned to one of the scene points (ctx+0x1C50 table, by its +0x30) rising from -50 by 2 a tick, turning 2: in by 19 for 5 ticks, then out by 9 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    s32 w10;
    s32 w14;
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b089_01E01F50;

typedef struct {
    f32 x, y, z, w;
} V4_b089_01E01F50;

typedef struct {
    u8 pad[0x1C50];
    V4_b089_01E01F50 pt[1];
} Game_b089_01E01F50;

static s32 func_01E01F50_b089(Game_b089_01E01F50 *g, Glow_b089_01E01F50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 16;
        o->kind = 2;
        func_0019A5C8();
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h0 = g->pt[o->h30].x;
        o->h2 = g->pt[o->h30].y;
        o->h4 = g->pt[o->h30].z;
        o->ang = func_0019A5C8() % 360;
        o->hA = -50;
        o->mode = 2;
    }
    if (o->tick < 5) {
        o->col[3] += 0x13;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->hA += 2;
    if (o->kind < 6) {
        o->kind++;
    } else {
        o->kind = 0;
    }
    o->h0 = g->pt[o->h30].x;
    o->h4 = g->pt[o->h30].z;
    o->tick++;
    o->ang += 2;
    return 0;
}

/* shape b089:01E020E0, 117 insns: a scene light (ctx+0x2610) on the scene joint whose four colour terms rise by 1 up to 32 (height 20); while active its level climbs 0.05 a tick until it reaches 1.0 (double compare), then it holds; turned off and ended once the scene value reaches 341 */

typedef struct {
    u8 pad0[0x36];
    s16 mode;
} Obj_b089_01E020E0;

typedef struct {
    u8 pad[0x2610];
    f32 c[4];
    f32 x, y, z;
    u8 pad262C[4];
    s32 w2630;
    f32 h;
    f32 level;
    u8 pad263C[0x3B76 - 0x263C];
    s16 joint;
    u8 pad3B78[0x10];
    s16 val;
} Game_b089_01E020E0;

static s32 func_01E020E0_b089(Game_b089_01E020E0 *g, Obj_b089_01E020E0 *o) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    Vec4f v;

    func_001F5620(func_001F53A0(), g->joint, &v);
    if (o->mode == 1) {
        o->mode = 2;
    }
    g->x = v.x;
    g->y = v.y;
    g->z = v.z;
    if (g->c[0] < 32.0f) {
        g->c[0] += 1.0f;
    }
    if (g->c[1] < 32.0f) {
        g->c[1] += 1.0f;
    }
    if (g->c[2] < 32.0f) {
        g->c[2] += 1.0f;
    }
    if (g->c[3] < 32.0f) {
        g->c[3] += 1.0f;
    }
    g->w2630 = 0;
    g->h = 20.0f;
    if (o->mode == 2) {
        if (g->level < 1.0) {
            g->level += 0.05f;
        } else {
            o->mode = 3;
        }
    }
    if (g->val > 340) {
        func_001F6C10(0);
        o->mode = 0;
    } else {
        func_001F6C10(g->c);
    }
    return 0;
}

/* shape b089:01E022C0, 139 insns: b056:01E023E0 family scene light (ctx+0x2610) at the camera: until scene count 380 red rises by 25 to 128 and green by 6 to 32, height 30, level +0.2 below 1.0 (double compare); after it they fall by 12 / 3 to 20 / 9 and the level by 0.1 above 0.1; off and ended from 391 */

typedef struct {
    f32 c[4];
    f32 pos[4];
    f32 f20;
    f32 f24;
    f32 level;
} Light_b089_01E022C0;

typedef struct {
    u8 pad0[0x2610];
    Light_b089_01E022C0 lt;
    u8 pad263C[0x3B88 - 0x263C];
    s16 count;
} Ctx_b089_01E022C0;

typedef struct {
    u8 pad0[0x36];
    s16 mode;
} Fx_b089_01E022C0;

static s32 func_01E022C0_b089(Ctx_b089_01E022C0 *g, Fx_b089_01E022C0 *o) {
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F6C10(void *);
    f32 v[4];

    func_001F5F90(func_001F5380(), v);
    if (o->mode == 1) {
        g->lt.c[0] = 0.0f;
        g->lt.c[1] = 0.0f;
        g->lt.c[2] = 0.0f;
        g->lt.c[3] = 0.0f;
        g->lt.level = 0.0f;
        o->mode = 2;
    }
    g->lt.pos[0] = v[0];
    g->lt.pos[1] = v[1];
    g->lt.pos[2] = v[2];
    if (g->count < 380) {
        if (g->lt.c[0] < 128.0f) {
            g->lt.c[0] += 25.0f;
        }
        if (g->lt.c[1] < 32.0f) {
            g->lt.c[1] += 6.0f;
        }
        g->lt.f20 = 0.0f;
        g->lt.f24 = 30.0f;
        if (g->lt.level < 1.0) {
            g->lt.level += 0.2f;
        }
    } else {
        if (g->lt.c[0] > 20.0f) {
            g->lt.c[0] -= 12.0f;
        }
        if (g->lt.c[1] > 9.0f) {
            g->lt.c[1] -= 3.0f;
        }
        if (g->lt.level > 0.1) {
            g->lt.level -= 0.1f;
        }
    }
    if (g->count > 390) {
        func_001F6C10(NULL);
        o->mode = 0;
    } else {
        func_001F6C10(&g->lt);
    }
    return 0;
}

typedef struct {
    u8 pad0000[0x3B8C];
    u8 tab[1];
} Mgr_b089_01E024F0;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b089_01E024F0;

static s32 func_01E024F0_b089(Mgr_b089_01E024F0 *m, Obj_b089_01E024F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 10;
        o->h34 = 2;
        func_0019A5C8();
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->h30 = func_0019A5C8() % 360;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 4) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->h36 = 0;
    }
    if (o->h34 < 6) {
        o->h34++;
    } else {
        o->h34 = 0;
    }
    o->h32++;
    o->x = o->x + 10.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 10.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b089:01E026B0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x26E0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x26E0];
    s32 state;
} Game_b089_01E026B0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b089_01E026B0;

static s32 func_01E026B0_b089(Game_b089_01E026B0 *g, Fade_b089_01E026B0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b089", func_01E02770_b089);

/* shape b089:01E030B0, 72 insns: takes the first free of 20 effect slots (0x40 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and stores the frame and both arguments */

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
} Slot_b089_01E030B0;

typedef struct {
    f32 pos[3];
    u8 padC[0xA4];
    Slot_b089_01E030B0 slots[0x14];
    u8 pad[0x26E4 - 0xB0 - 0x14 * 0x40];
    u8 rgba[4];
    u8 pad26E8[0x149C];
    s16 f3B84;
} Ctx_b089_01E030B0;

static s32 func_01E030B0_b089(Ctx_b089_01E030B0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b089_01E030B0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x14; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x40);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x14;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f3B84;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b089:01E031D0, 72 insns: takes the first free of 50 effect slots (0x40 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and stores the frame and both arguments */

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
} Slot_b089_01E031D0;

typedef struct {
    f32 pos[3];
    u8 padC[0x5A4];
    Slot_b089_01E031D0 slots[0x32];
    u8 pad[0x26E4 - 0x5B0 - 0x32 * 0x40];
    u8 rgba[4];
    u8 pad26E8[0x149C];
    s16 f3B84;
} Ctx_b089_01E031D0;

static s32 func_01E031D0_b089(Ctx_b089_01E031D0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b089_01E031D0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x40);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f3B84;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b089:01E032F0, 186 insns: b089:01E035E0 family flat quad: mode 0 sets texture 0x1E at its angle 0x34, the colour and the scene texture (g+0x7C); else places it at its position plus a tenth of 0x8..0xC and spans the quad between the angles 0x3A and 0x3A + 20 at radius 0x38 (g+0x3B8C), 10 high on the far edge */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fx_b089_01E032F0;

typedef struct {
    u8 pad0[0x7C];
    s32 tex;
    u8 pad80[0x3B8C - 0x80];
    u8 trig[1];
} Scene_b089_01E032F0;

static void func_01E032F0_b089(Scene_b089_01E032F0 *g, Fx_b089_01E032F0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;
    s16 k;

    v = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x1E, o->h34, rm);
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
    func_00108EF0(m, 0, 0, &pos);
    k = o->ang;
    quad[2].x = o->size * func_00108030(g->trig, k, 1);
    quad[2].z = o->size * func_00108030(g->trig, k, 0);
    quad[0].x = o->size * func_00108030(g->trig, k, 1);
    quad[0].z = o->size * func_00108030(g->trig, k, 0);
    k = o->ang + 20;
    quad[3].x = o->size * func_00108030(g->trig, k, 1);
    quad[3].z = o->size * func_00108030(g->trig, k, 0);
    quad[1].x = o->size * func_00108030(g->trig, k, 1);
    quad[1].z = o->size * func_00108030(g->trig, k, 0);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 10.0f;
    quad[3].y = 10.0f;
    func_00108F90(quad, p, m, v);
}

/* shape b089:01E035E0, 103 insns: mode 0 sets the drawing state (a 0x14 matrix from its angle 0x34, colour, the scene
   texture 0x78); otherwise draws the effect as a camera-facing square of its size 0x38: camera rotation, world matrix at its position offset by
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
} Fx_b089_01E035E0;

typedef struct {
    u8 pad0[0x78];
    s32 tex;
} Scene_b089_01E035E0;

static void func_01E035E0_b089(Scene_b089_01E035E0 *g, Fx_b089_01E035E0 *o, void *p, s32 mode) {
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
        func_00106080(rm, 0x14, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x + o->dx / 10;
        pos.y = o->y + o->dy / 10;
        pos.z = o->z + o->dz / 10;
        func_00108EF0(m, 0, rot, &pos);
        func_00108CE0(quad, o->size, o->size);
        func_00108F90(quad, p, m, v);
    }
}

/* shape b089:01E03780, 106 insns: draws a small sprite (b004:01E01860 shape): unlit, it sets up the colour and texture page; lit,
   it builds a matrix at a tenth scale from its turn, at its position plus a fiftieth of its drift, and draws a square of its
   size */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b089_01E03780;

typedef struct {
    u8 pad0[0xAC];
    s32 tex;
} Scene_b089_01E03780;

static void func_01E03780_b089(Scene_b089_01E03780 *g, Fx_b089_01E03780 *o, void *p, s32 lit) {
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
    f32 f;

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
    f = o->dx;
    f /= 50.0f;
    pos.x = o->x;
    pos.x += f;
    f = o->dy;
    f /= 50.0f;
    pos.y = o->y;
    pos.y += f;
    f = o->dz;
    f /= 50.0f;
    pos.z = o->z;
    pos.z += f;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

/* OVL_WARM */

/* shape b089:01E03930, 266 insns: draw the scene's 12 x 12 point grid (g+0x12F0) as 11 rows of 12 quads (the last
   quad of a row wraps to column 0), each quad turned twice by the object's rotation and offset by the object's
   per-point shift tables (g+0x2728 / 0x2DE8 / 0x34A8, set o->h30); from o->h36 100 the shifts move by each point's
   drift (g+0x1D10); mode 0 only sets the packet up */

typedef struct {
    u8 pad0[0x10];
    Vec4f b[6];
    u8 pad70[0xAC - 0x70];
    s32 tex;
    u8 padB0[0x12F0 - 0xB0];
    Vec4f pts[12][12];
    Vec4f a[6];
    Vec4f c[6];
    u8 pad1CB0[0x1D10 - 0x1CB0];
    Vec4f vel[11][12];
    u8 pad2550[0x26EC - 0x2550];
    s32 ot;
    u8 pad26F0[0x2714 - 0x26F0];
    f32 depth;
    u8 pad2718[0x2728 - 0x2718];
    s16 tx[6][12][12];
    s16 ty[6][12][12];
    s16 tz[6][12][12];
    u8 pad3B68[0x3B8C - 0x3B68];
    u8 x3B8C[4];
} G_b089_01E03930;

typedef struct {
    u8 pad0[0x10];
    u8 rot[0x18];
    u8 x28[8];
    s16 h30;
    u8 pad32[2];
    s16 h34;
    s16 h36;
} Obj_b089_01E03930;

static void func_01E03930_b089(G_b089_01E03930 *g, Obj_b089_01E03930 *o, void *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 r;
    s16 ang;
    s32 j;
    Vec4f v[4];
    f32 m[16];
    u8 rect[0x10];

    ang = 0;
    if (mode == 0) {
        func_00106080(rect, 0x9C, o->h34, rect);
        func_00109270(pk, 0, 0);
        func_00107790(pk, o->x28, 0);
        func_00108500(pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
        func_00108EF0(m, &g->a[o->h30], &g->b[o->h30], &g->c[o->h30]);
        for (r = 0; r < 11; r++) {
            for (j = 0; j < 12; j++) {
                if (j < 11) {
                    v[0] = g->pts[r][j];
                    v[1] = g->pts[r][j + 1];
                    v[2] = g->pts[r + 1][j];
                    v[3] = g->pts[r + 1][j + 1];
                } else {
                    v[0] = g->pts[r][j];
                    v[1] = g->pts[r][0];
                    v[2] = g->pts[r + 1][j];
                    v[3] = g->pts[r + 1][0];
                }
                func_00109100(v, o->rot, 0, g->x3B8C);
                func_00109100(v, o->rot, 1, g->x3B8C);
                func_00107070(v, 0, g->tx[o->h30][r][j]);
                func_00107070(v, 1, g->ty[o->h30][r][j]);
                func_00107070(v, 2, g->tz[o->h30][r][j]);
                if (o->h36 >= 100) {
                    g->tx[o->h30][r][j] -= g->vel[r][j].x;
                    g->ty[o->h30][r][j] -= g->vel[r][j].y;
                    g->tz[o->h30][r][j] -= g->vel[r][j].z;
                }
                if (func_00205630(v, 0x70000000, m, pk, &g->depth) != 0) {
                    func_002075F0(pk, g->ot, (u32)g->depth);
                }
                ang += 30;
            }
            ang = 0;
        }
    }
}

/* shape b089:01E03D60, 223 insns: a ribbon along the scene's trail points (ctx+0x2640, 0x32 of them): each segment is
   18 thin quads 20 degrees apart around the segment's two points (radius 1), in the object's colour fading by
   alpha/count per segment (second colour), drawn flat into the frame's list */

typedef struct {
    u8 r, g, b, a;
} Col_b089_01E03D60;

typedef struct {
    u8 pad0[0x28];
    Col_b089_01E03D60 col;
    u8 pad2C[6];
    s16 count;
} Obj_b089_01E03D60;

typedef struct {
    u8 pad0[0x2640];
    Vec4f pt[0x50];
    u8 pad[0x3B8C - 0x2640 - 0x500];
    u8 trig[1];
} Scn_b089_01E03D60;

static void func_01E03D60_b089(Scn_b089_01E03D60 *g, Obj_b089_01E03D60 *o) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec4f q[4];
    struct {
        u64 tag;
        u8 pk[0x90];
    } buf;
    Col_b089_01E03D60 c;
    s32 i;
    s32 ot __attribute__((aligned(8)));
    s16 n;
    s32 j;
    void *pk;
    s16 a;
    f32 r;

    ot = (s32)func_00207500();
    pk = buf.pk;
    n = o->count;
    func_001092E0(pk, 0);
    func_001094F0(pk);
    c = o->col;
    r = 1.0f;
    for (i = 0; i < n - 1; i++) {
        a = 0;
        func_00107990(pk, &c, 1);
        c.a -= o->col.a / n;
        func_00107990(pk, &c, 2);
        for (j = 0; j < 18; j++) {
            q[0].x = g->pt[i].x;
            q[0].y = g->pt[i].y;
            q[0].z = g->pt[i].z;
            q[1].x = g->pt[i].x;
            q[1].y = g->pt[i].y;
            q[1].z = g->pt[i].z;
            q[0].y += r * func_00108030(g->trig, a, 1);
            q[0].x += r * func_00108030(g->trig, a, 0);
            q[1].y += r * func_00108030(g->trig, a + 20, 1);
            q[1].x += r * func_00108030(g->trig, a + 20, 0);
            q[2].x = g->pt[i + 1].x;
            q[2].y = g->pt[i + 1].y;
            q[2].z = g->pt[i + 1].z;
            q[3].x = g->pt[i + 1].x;
            q[3].y = g->pt[i + 1].y;
            q[3].z = g->pt[i + 1].z;
            q[2].y += r * func_00108030(g->trig, a, 1);
            q[2].x += r * func_00108030(g->trig, a, 0);
            q[3].y += r * func_00108030(g->trig, a + 20, 1);
            q[3].x += r * func_00108030(g->trig, a + 20, 0);
            if (func_00205630(q, 0x70000000, NULL, pk, depth) != 0) {
                func_002075F0(pk, ot, 0);
            }
            a += 20;
        }
    }
}

/* shape b089:01E040E0, 148 insns: c035:01E013A0 family two-layer sprite: texture 0xA (scene texture 0x74) in the setup pass; the draw pass draws it, then again with texture 0x14 and the second scene texture (0x70) at half alpha */

typedef struct {
    u8 r, g, b, a;
} Col_b089_01E040E0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b089_01E040E0;

typedef struct {
    u8 pad0[0x70];
    s32 tex2;
    s32 tex;
} Scene_b089_01E040E0;

static void func_01E040E0_b089(Scene_b089_01E040E0 *g, Fx_b089_01E040E0 *o, void *p, s32 lit) {
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
    {
    extern Col_b089_01E040E0 D_01E04C80_b089;
    Col_b089_01E040E0 c = D_01E04C80_b089;

    if (lit == 0) {
        func_00106080(rm, 0xA, o->h34, rm);
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
    func_00108F90(quad, p, m, v);
    func_00106080(rm, 0x14, o->h34, rm);
    func_00108500(p, rm, 0);
    c = *(Col_b089_01E040E0 *)o->col;
    c.a >>= 1;
    func_00107790(p, &c, 0);
    func_00208700(p, g->tex2, 1);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
    }
}

/* shape b089:01E04330, 155 insns: c022:01E01850 family flat ring segment: one quad between angles o->h3A and +20 at radius o->h38, built at the object (turned by its rotation); blend switches to 0x42 after 16 ticks; the setup pass sets two colours (texture 0x9C, scene texture at ctx+0xAC) */

typedef struct {
    u8 pad0[0xAC];
    s32 tex;
    u8 padB0[0x26EC - 0xB0];
    s32 ot;
    u8 pad26F0[0x24];
    f32 depth;
    u8 pad2718[0x3B8C - 0x2718];
    u8 tab[1];
} Ctx_b089_01E04330;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 h34;
    u8 pad36[2];
    s16 r;
    s16 ang;
} Fx_b089_01E04330;

static void func_01E04330_b089(Ctx_b089_01E04330 *g, Fx_b089_01E04330 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    f32 rm[4];
    s32 i;
    s16 a;
    s16 t;

    a = 0;
    if (lit == 0) {
        func_00106080(rm, 0x9C, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 1);
        func_00107790(p, o->col2, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
    if (o->tick > 16) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, 0, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 1; i++) {
        t = o->ang + a;
        q[2].x = o->r * func_00108030(g->tab, t, 1);
        q[2].z = o->r * func_00108030(g->tab, t, 0);
        q[0].x = 0.0f;
        q[0].z = 0.0f;
        t = o->ang + 20 + a;
        q[3].x = o->r * func_00108030(g->tab, t, 1);
        q[3].z = o->r * func_00108030(g->tab, t, 0);
        q[1].x = 0.0f;
        q[1].z = 0.0f;
        if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, (u32)g->depth);
        }
        a += 180;
    }
    }
}

/* shape b089:01E045A0 (B089PAINT_RAIN10), 115 insns, 1 copy (-O3,p): the rain object's draw (b027:01E03F70's source
   at -O3): in the setup pass it sets the light, colour and the scene texture; in the draw pass, for b089:01E024F0's
   objects it first switches to blend 0x42, then draws a size x size quad at the position plus a tenth of the velocity
   */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x16];
    void *handler;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b089_01E045A0;

typedef struct {
    u8 pad0[0x70];
    s32 tex;
} Scene_b089_01E045A0;

static s32 func_01E024F0_b089();

#pragma optimization_level 3

static void func_01E045A0_b089(Scene_b089_01E045A0 *g, Fx_b089_01E045A0 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern void func_002086D0(void *, u64);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x14, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    if (o->handler == func_01E024F0_b089) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m, 0, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

#pragma optimization_level reset

/* shape b089:01E04770, 92 insns, 1 copy: draws a thin rain strip: mode 0 builds the packet (texture page 10 frame from
   the object, its colour, the scene texture); other modes turn it at random, place it at the object's point lifted by a
   tenth of its rise, make a 3 by len strip with its lower corners at height 0 and draw it */

typedef struct {
    s16 x, y, z;
    u8 pad6[4];
    s16 rise;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[8];
    s16 sub;
    u8 pad36[2];
    s16 len;
} Obj_b089_01E04770;

typedef struct {
    u8 pad0[0x74];
    void *tex;
} Game_b089_01E04770;

#pragma opt_propagation off

static void func_01E04770_b089(Game_b089_01E04770 *g, Obj_b089_01E04770 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    s16 rect[8];
    f32 m[16];
    s32 rot[4];
    s32 ot;
    f32 r;
    f32 w;

    ot = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0xA, o->sub, rect);
        func_00109270(p, 0, 0);
        func_00107790(p, o->c0, 0);
        func_00108500(p, rect, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        r = o->rise;
        r /= 10.0f;
        pos.y += r;
        func_00108EF0(m, NULL, rot, &pos);
        w = 3.0f;
        func_00108CE0(quad, w, o->len);
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        func_00108F90(quad, p, m, ot);
    }
}
#pragma opt_propagation reset

/* shape b089:01E048E0, 199 insns (MAP_IN): builds a 12x12 point sphere at ctx+0x12F0 (ring radius 20 * sin of
   90, 120, ... degrees, 30 degrees between points; height 20 * sin of the row angle), then copies it to
   ctx+0x1D10 shrunk to a third */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V_b089_01E048E0;

typedef struct {
    u8 pad0[0x12F0];
    V_b089_01E048E0 p[12][12];
    u8 pad1BF0[0x1D10 - 0x1BF0];
    V_b089_01E048E0 q[12][12];
} Ctx_b089_01E048E0;

static void func_01E048E0_b089(Ctx_b089_01E048E0 *g) {
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    s16 i;
    s16 j;
    s16 a;
    s16 b;
    f32 r;
    f32 t;

    a = 0;
    b = 90;
    r = 20.0f * func_001A6898(3.1415927f * b / 180.0f);
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            t = 3.1415927f * a / 180.0f;
            g->p[i][j].x = r * func_001A6898(t);
            g->p[i][j].z = r * func_001A6A88(t);
            a += 30;
        }
        b += 30;
        r = 20.0f * func_001A6898(3.1415927f * b / 180.0f);
        a = 0;
    }
    a = 0;
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            g->p[i][j].y = 20.0f * func_001A6898(3.1415927f * a / 180.0f);
        }
        a += 30;
    }
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 12; j++) {
            g->q[i][j] = g->p[i][j];
            g->q[i][j].x /= 3.0f;
            g->q[i][j].y /= 3.0f;
            g->q[i][j].z /= 3.0f;
        }
    }
}
