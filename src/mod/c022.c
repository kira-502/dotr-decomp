#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00080_c022);

/* shape c022:01E00750, 274 insns, 1 copy (C022_OBJ_MOVE_1_): a rising ribbon segment: grows its top (f1C) by 8 up to
   220 and pulls its bottom (f20) after it (8 a tick in state 0, 5 later) while the gap is over 20; in state 100 fades
   both alphas by 9 and dies; past height 80 an idle segment counts down, then climbs its bottom and hands state 100 to
   its link; turns both angles by its speed, bobs 70 + 25 sine, fades in by 15 under scene frame 40 and out above 200 */

typedef struct Seg_c022_01E00750 {
    u8 pad0[4];
    f32 speed;
    u8 pad8[0xC];
    struct Seg_c022_01E00750 *link;
    u8 pad18[4];
    f32 top;
    f32 bottom;
    f32 bob;
    u8 pad28[3];
    u8 a0;
    u8 pad2C[3];
    u8 a1;
    s16 state;
    s16 alive;
    s16 ang0;
    s16 ang1;
    s16 hold;
    s16 phase;
    s16 wait;
} Seg_c022_01E00750;

typedef struct {
    u8 pad0[0x3A48];
    s16 frame;
} Scene_c022_01E00750;

static s32 func_01E00750_c022(Scene_c022_01E00750 *g, Seg_c022_01E00750 *o) {
    extern f32 func_001A6A88(f32);
    Seg_c022_01E00750 *link;

    link = o->link;
    if (o->state == 0) {
        if (o->top < 220.0f) {
            o->top += 8.0f;
        }
        if (o->top - o->bottom > 20.0f) {
            o->bottom += 8.0f;
        }
    } else if (o->state == 100) {
        if (o->a0 > 10) {
            o->a0 -= 9;
        }
        if (o->a1 > 10) {
            o->a1 -= 9;
        } else {
            o->alive = 0;
        }
    } else if (o->top > 80.0f && o->hold == 0) {
        if (o->wait == 0) {
            o->bottom += 8.0f;
            if (o->top < o->bottom) {
                o->state = 100;
                if (link != NULL) {
                    link->state = 100;
                }
            }
        } else {
            o->wait--;
            if (o->hold == 0) {
                if (o->top < 220.0f) {
                    o->top += 8.0f;
                }
                if (o->top - o->bottom > 20.0f) {
                    o->bottom += 5.0f;
                }
            }
        }
    } else if (o->hold == 0) {
        if (o->top < 220.0f) {
            o->top += 8.0f;
        }
        if (o->top - o->bottom > 20.0f) {
            o->bottom += 5.0f;
        }
    }
    o->ang0 = o->ang0 + o->speed;
    o->ang1 = o->ang1 + o->speed;
    o->phase += 5;
    if (o->hold == 0) {
        o->bob = 70.0f + 25.0f * func_001A6A88(3.1415927f * o->phase / 180.0f);
        o->phase += 15;
    }
    if (o->ang0 >= 360) {
        o->ang0 %= 360;
    }
    if (o->ang1 >= 360) {
        o->ang1 %= 360;
    }
    if (o->phase >= 360) {
        o->ang0 %= 360;
    }
    if (g->frame < 40) {
        if (o->a0 < 0x40) {
            o->a0 += 15;
        }
        if (o->a1 < 0x40) {
            o->a1 += 15;
        }
    }
    if (o->top > 200.0f) {
        if (o->a0 > 10) {
            o->a0 -= 9;
        }
        if (o->a1 > 10) {
            o->a1 -= 9;
        } else {
            o->alive = 0;
        }
    }
    return 0;
}

/* shape c022:01E00BA0, 52 insns: c056:01E04780 family two-alpha sprite: in by 32/16 while the scene value is under 8, out by 15 from 36, ends when the counter is under 3 */

typedef struct {
    u8 pad0[0x39f0];
    s32 count;
    u8 padC[0x54];
    s16 val;
} Ctx_c022_01E00BA0;

typedef struct {
    u8 pad0[0x2B];
    u8 alpha;
    u8 pad2C[0x3];
    u8 alpha2;
    u8 pad30[0x2];
    s16 state;
    u8 bA[1];
} Obj_c022_01E00BA0;

static s32 func_01E00BA0_c022(Ctx_c022_01E00BA0 *ctx, Obj_c022_01E00BA0 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 0x8) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x20;
        }
        if (o->alpha2 < 0x11) {
            o->alpha2 += 0x10;
        }
    }
    if (ctx->val > 0x23) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
        if (o->alpha2 > 0x10) {
            o->alpha2 -= 15;
        }
    }
    if (ctx->count < 0x3) {
        o->state = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E00C70_c022);

/* shape c022:01E00F10 (C022_EARLY_1_), 113 insns, 1 copy (-O3,p): the trail-slot setup of c022:01E01580 at -O3, but
   with the scene colour halved (all three channels in the first colour, green only in the second): take the first
   free trail slot of 193, mark it, position and angle it, link it after the current slot and make it current */

typedef struct Slot_c022_01E00F10 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[8];
    struct Slot_c022_01E00F10 *prev;
    struct Slot_c022_01E00F10 *next;
    s32 fn;
    f32 x;
    f32 z;
    f32 y;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 used;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 ang;
    s16 h3C;
    u8 pad3E[2];
} Slot_c022_01E00F10;

typedef struct {
    u8 pad0[0xF0];
    Slot_c022_01E00F10 slot[193];
    u8 padEnd[0x39F4 - 0xF0 - 193 * 0x40];
    u8 rgba[4];
    u8 pad39F8[8];
    Slot_c022_01E00F10 *head;
    u8 pad3A04[4];
    f32 x;
    f32 z;
    u8 pad3A10[0xC];
    f32 f3A1C;
    u8 pad3A20[0x1A];
    s16 h3A3A;
    u8 pad3A3C[2];
    s16 ang;
    s16 h3A40;
    s16 h3A42;
    u8 pad3A44[0xA];
    s16 h3A4E;
    u8 sin[1];
} Ctx_c022_01E00F10;

#pragma optimization_level 3

static void func_01E00F10_c022(Ctx_c022_01E00F10 *g) {
    extern void c022_01E010E0();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Slot_c022_01E00F10 *s;
    Slot_c022_01E00F10 *q;
    s16 i;

    s = NULL;
    for (i = 0; i < 193; i++) {
        if (g->slot[i].used == 0) {
            s = &g->slot[i];
            func_00195108(s, 0x40);
            g->slot[i].used = i + 1;
            i = 193;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, (u8)(g->rgba[0] >> 1), (u8)(g->rgba[1] >> 1), (u8)(g->rgba[2] >> 1));
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], (u8)(g->rgba[1] >> 1), g->rgba[2]);
        s->col2[3] = g->rgba[3];
        s->x = g->x;
        s->z = g->z;
        s->ang = g->ang;
        s->y = 70.0f + 25.0f * func_00108030(g->sin, s->ang, 0);
        s->h34 = g->h3A3A;
        s->h36 = g->h3A3A;
        s->h30 = g->h3A42;
        s->h38 = g->h3A40;
        s->prev = g->head;
        s->f4 = g->f3A1C;
        s->h3C = g->h3A4E;
        q = s->prev;
        if (q != NULL) {
            s->x = q->x;
            s->z = q->z;
            s->h34 = q->h34;
            s->h36 = q->h36;
            q->next = s;
        }
        s->fn = (s32)c022_01E010E0;
        g->head = s;
    }
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E010E0_c022);

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E01570_c022(void) {
}

/* shape c022:01E01580, 105 insns: take the first free trail slot of 193 (0x40 bytes at ctx+0xF0), mark it with its index + 1, give it the scene colour twice, position, angle (height 70 + 25 sine, table ctx+0x3A50), ids and handler shape c022:01E01570; link it after the scene's current slot (inheriting its x/z and ids) and make it current */

typedef struct Slot_c022_01E01580 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[8];
    struct Slot_c022_01E01580 *prev;
    struct Slot_c022_01E01580 *next;
    s32 fn;
    f32 x;
    f32 z;
    f32 y;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 used;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 ang;
    s16 h3C;
    u8 pad3E[2];
} Slot_c022_01E01580;

typedef struct {
    u8 pad0[0xF0];
    Slot_c022_01E01580 slot[193];
    u8 padEnd[0x39F4 - 0xF0 - 193 * 0x40];
    u8 rgba[4];
    u8 pad39F8[8];
    Slot_c022_01E01580 *head;
    u8 pad3A04[4];
    f32 x;
    f32 z;
    u8 pad3A10[0xC];
    f32 f3A1C;
    u8 pad3A20[0x1A];
    s16 h3A3A;
    u8 pad3A3C[2];
    s16 ang;
    s16 h3A40;
    s16 h3A42;
    u8 pad3A44[0xA];
    s16 h3A4E;
    u8 sin[1];
} Ctx_c022_01E01580;

static void func_01E01580_c022(Ctx_c022_01E01580 *g) {
    extern void c022_01E01570();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Slot_c022_01E01580 *s;
    Slot_c022_01E01580 *q;
    s16 i;

    s = NULL;
    for (i = 0; i < 193; i++) {
        if (g->slot[i].used == 0) {
            s = &g->slot[i];
            func_00195108(s, 0x40);
            g->slot[i].used = i + 1;
            i = 193;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        s->x = g->x;
        s->z = g->z;
        s->ang = g->ang;
        s->y = 70.0f + 25.0f * func_00108030(g->sin, s->ang, 0);
        s->h34 = g->h3A3A;
        s->h36 = g->h3A3A;
        s->h30 = g->h3A42;
        s->h38 = g->h3A40;
        s->prev = g->head;
        s->f4 = g->f3A1C;
        s->h3C = g->h3A4E;
        q = s->prev;
        if (q != NULL) {
            s->x = q->x;
            s->z = q->z;
            s->h34 = q->h34;
            s->h36 = q->h36;
            q->next = s;
        }
        s->fn = (s32)c022_01E01570;
        g->head = s;
    }
}

/* shape c022:01E01730, 71 insns: takes the first free of 193 effect slots (0x40 bytes, b108:01E02FF0 family), marks it with
   its index + 1, colours both at half the context's colour with its alpha, and hooks c022:01E01850 */

typedef struct {
    u8 pad0[0x18];
    void (*cb)(void);
    u8 pad1C[0xC];
    u8 c28[4];
    u8 c2C[4];
    u8 pad30[2];
    s16 used;
    u8 pad34[0xC];
} Slot_c022_01E01730;

typedef struct {
    u8 pad0[0xF0];
    Slot_c022_01E01730 slots[0xC1];
    u8 pad[0x39F4 - 0xF0 - 0xC1 * 0x40];
    u8 rgba[4];
} Ctx_c022_01E01730;

static void func_01E01730_c022(Ctx_c022_01E01730 *ctx) {
    extern void c022_01E01850(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c022_01E01730 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC1; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x40);
            ctx->slots[i].used = i + 1;
            i = 0xC1;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, (u8)(ctx->rgba[0] >> 1), (u8)(ctx->rgba[1] >> 1), (u8)(ctx->rgba[2] >> 1));
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, (u8)(ctx->rgba[0] >> 1), (u8)(ctx->rgba[1] >> 1), (u8)(ctx->rgba[2] >> 1));
        s->c2C[3] = ctx->rgba[3];
        s->cb = c022_01E01850;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c022", func_01E01850_c022);
