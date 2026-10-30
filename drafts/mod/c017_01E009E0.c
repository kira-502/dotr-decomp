#include "common.h"

/* shape c017:01E009E0 (C017_OBJ_MOVE_3_), 220 insns, 1 copy (-O3,p): a falling streak segment: turns by its 0x24
   speed, sizes itself by the scene scale table, drops 3 a frame down to the floor, then its tail follows; the first
   one below the top hands its position, colour and depth to the scene and spawns the next segment while its count
   lasts; fades in, out or up by the scene state; the source of shape c017:01E006B0, built here at -O3 */

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E009E0;

typedef struct Ent_c017_01E009E0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[4];
    f32 f2C;
    u8 pad30[0x10];
    struct Ent_c017_01E009E0 *prev;
    struct Ent_c017_01E009E0 *next;
    u8 pad48[8];
    Col_c017_01E009E0 col0;
    Col_c017_01E009E0 col1;
    s16 used;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    s16 f60;
    s16 f62;
    s16 f64;
    u8 pad66[2];
    s16 f68;
    s16 f6A;
} Ent_c017_01E009E0;

typedef struct {
    u8 pad0[0x180];
    s32 v[3];
    u8 pad18C[0x38DC - 0x18C];
    s32 state;
    u8 rgb[4];
    u8 pad38E4[8];
    Ent_c017_01E009E0 *last;
    u8 pad38F0[4];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[8];
    f32 f3908;
    u8 pad390C[4];
    f32 f3910;
    f32 scale[14];
    f32 f394C;
    u8 pad3950[2];
    s16 f3952;
    s16 f3954;
    s16 f3956;
    s16 f3958;
    s16 f395A;
    u8 pad395C[4];
    s16 val;
    u8 pad3962[0x399A - 0x3962];
    s16 floor;
    u8 pad399C[2];
    s16 top;
} Ctx_c017_01E009E0;

#pragma optimization_level 3

static s32 func_01E009E0_c017(Ctx_c017_01E009E0 *g, Ent_c017_01E009E0 *o) {
    extern s16 func_001A22C0(f32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void c017_01E01610();
    f32 fl;
    f32 d;
    f32 s;

    d = g->top;
    o->f5A -= func_001A22C0(o->f24);
    if (o->f5A < -359) {
        o->f5A %= 360;
    }
    fl = g->floor;
    s = g->scale[o->f68] / d;
    o->f60 = func_001A22C0(s * o->f4 - 17.0f);
    if (g->scale[o->f68] < 1.0f) {
        o->used = 0;
    }
    o->f62 = func_001A22C0(s * o->f14 - 17.0f);
    if (o->f4 >= fl) {
        o->f4 -= 3.0f;
        if (o->f14 - o->f4 >= 18.0f) {
            o->f14 -= 3.0f;
        }
    } else {
        o->f14 -= 3.0f;
        if (o->f14 < o->f4) {
            if (o->next != NULL) {
                o->next->prev = NULL;
            }
            o->used = 0;
        }
    }
    if (o->f64 > 0 && o->f14 < (f32)g->top) {
        g->last = o;
        g->f38F4 = o->f60;
        g->f38F8 = o->f62;
        g->rgb[3] = 0;
        g->f3956 = 1;
        g->f38FC = o->f14;
        g->f394C = o->f68;
        g->f395A = 1;
        g->f3954 = o->f5C;
        o->f6A--;
        g->f3958 = o->f6A;
        g->f3908 = o->f24;
        g->f3910 = o->f2C;
        func_001076F0(g->rgb, o->col0.r, o->col0.g, o->col0.b);
        func_00106DD0(g->v, 0.0f, 0.0f, 0.0f);
        g->f3952 = o->f5A + 15;
        if (o->f6A != 0) {
            c017_01E01610(g, func_01E009E0_c017);
        }
        o->f64 = 0;
    }
    if (g->val < 14) {
        if (o->col0.a < 0x30) {
            o->col0.a += 4;
        }
        if (o->col1.a < 0x30) {
            o->col1.a += 4;
        }
    }
    if (g->state < 10) {
        if (o->col0.a > 16) {
            o->col0.a -= 16;
        }
        if (o->col1.a > 16) {
            o->col1.a -= 16;
        }
    } else {
        if (o->col0.a < 0x50) {
            o->col0.a += 10;
        }
        if (o->col1.a < 0x50) {
            o->col1.a += 10;
        }
    }
    return 0;
}

#pragma optimization_level reset
