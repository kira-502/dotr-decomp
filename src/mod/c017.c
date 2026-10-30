#include "common.h"

/* shape c017:01E00080, 393 insns: C017_W_S, the scene's step: colour 0x80,0x80,0x80,0, counts the frame (0x3960);
   frame 1 fills the template (eight 160.0, a 5x5 table of random times) and spawns 0x1E006B0 and 0x1E01020;
   every 7th frame two 0x1E009E0 with random spin and colour; every 4th frame, from level 11 on, 0x1E00D50 and
   0x1E00F10 at (100, 50, 130) in one of three colours */

typedef struct {
    u8 pad0[0x180];
    Vec4f scale;
    u8 pad190[0x38DC - 0x190];
    s32 level;
    u8 col[4];
    u8 pad38E4[8];
    s32 f38EC;
    u8 pad38F0[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad3900[8];
    f32 f3908;
    u8 pad390C[4];
    f32 f3910;
    f32 arr[8];
    u8 pad3934[0x394C - 0x3934];
    s32 f394C;
    u8 pad3950[2];
    s16 f3952;
    s16 f3954;
    s16 f3956;
    s16 f3958;
    s16 f395A;
    u8 pad395C[4];
    s16 t;
    u8 pad3962[4];
    s16 f3966;
    s16 tab[5][5];
    u8 pad399A[4];
    s16 f399E;
} Scene_c017_01E00080;

static void func_01E00080_c017(Scene_c017_01E00080 *g) {
    extern void c017_01E006B0(void);
    extern void c017_01E009E0(void);
    extern void c017_01E00D50(void);
    extern void c017_01E00F10(void);
    extern void c017_01E01020(void);
    extern void c017_01E01400(Scene_c017_01E00080 *, void (*)(void));
    extern void c017_01E01610(Scene_c017_01E00080 *, void (*)(void));
    extern void c017_01E01840(Scene_c017_01E00080 *, void (*)(void));
    extern void c017_01E019B0(Scene_c017_01E00080 *, void (*)(void));
    extern void c017_01E01B00(Scene_c017_01E00080 *, void (*)(void));
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    s16 m;

    g->col[0] = 0x80;
    g->col[1] = 0x80;
    g->col[2] = 0x80;
    g->col[3] = 0;
    g->f3966 = 20;
    g->f399E = 130;
    g->t++;
    if (g->t == 1) {
        g->f38EC = 0;
        for (i = 0; i < 8; i++) {
            g->arr[i] = 160.0f;
        }
        for (i = 0; i < 5; i++) {
            g->tab[0][i] = func_0019A5C8() % 40 + 60;
            g->tab[1][i] = func_0019A5C8() % 40 + 140;
            g->tab[2][i] = func_0019A5C8() % 40 + 200;
            g->tab[3][i] = func_0019A5C8() % 40 + 280;
            g->tab[4][i] = func_0019A5C8() % 40 + 60;
        }
        g->f394C = 0;
        for (i = 0; i < 1; i++) {
            g->x = 0.0f;
            g->y = 0.0f;
            g->f3956 = 1;
            g->z = i * 25;
            g->f395A = 1;
            func_00106DD0(&g->scale, 0.0f, 0.0f, 0.0f);
            g->col[3] = 0;
            g->f3952 = i * 15;
            func_001076F0(g->col, 20, 20, 40);
            c017_01E01400(g, c017_01E006B0);
            g->f38EC = 0;
            g->f3954 = func_0019A5C8() % 360;
            g->f3958 = 15;
            func_001076F0(g->col, 0x40, 0x40, 0x70);
        }
        c017_01E01B00(g, c017_01E01020);
    }
    if (g->t % 7 == 1) {
        g->f394C = 0;
        for (i = 0; i < 2; i++) {
            g->x = 0.0f;
            g->y = 0.0f;
            g->f3956 = 1;
            g->z = i * 25;
            g->f395A = 1;
            g->col[3] = 0;
            g->f3952 = i * 15;
            g->f38EC = 0;
            g->f3954 = func_0019A5C8() % 360;
            g->f3958 = 8;
            g->f3908 = func_0019A5C8() % 3 + 3;
            g->f3910 = func_0019A5C8() % 5;
            if (func_0019A5C8() % 2 != 0) {
                func_001076F0(g->col, 0x40, 0x40, 0x40);
            } else {
                func_001076F0(g->col, 0x40, 0x40, 0x70);
            }
            c017_01E01610(g, c017_01E009E0);
        }
    }
    if (g->t % 4 == 1 && g->level > 10) {
        g->z = 130.0f;
        g->x = 100.0f;
        g->y = 50.0f;
        g->f3956 = func_0019A5C8() % 4;
        m = func_0019A5C8() % 3;
        if (m == 0) {
            func_001076F0(g->col, 0x30, 0x40, 0x50);
        } else if (m == 1) {
            func_001076F0(g->col, 0x20, 0x20, 0x60);
        } else {
            func_001076F0(g->col, 0x40, 0x40, 0x40);
        }
        g->f3952 = func_0019A5C8() % 360;
        c017_01E01840(g, c017_01E00D50);
    }
    if (g->t % 4 == 1 && g->level > 10) {
        g->z = 130.0f;
        g->x = 100.0f;
        g->y = 50.0f;
        g->f3952 = func_0019A5C8() % 360;
        g->f3956 = func_0019A5C8() % 4;
        g->f3908 = func_0019A5C8() % 3 + 3;
        g->f395A = func_0019A5C8() % 6 + 7;
        m = func_0019A5C8() % 3;
        if (m == 0) {
            func_001076F0(g->col, 0x40, 0x60, 0x60);
        } else if (m == 1) {
            func_001076F0(g->col, 0x40, 0x40, 0x60);
        } else {
            func_001076F0(g->col, 0x40, 0x40, 0x40);
        }
        g->f3952 = func_0019A5C8() % 360;
        c017_01E019B0(g, c017_01E00F10);
    }
}

/* shape c017:01E006B0, 201 insns: c017's column piece step (c017:01E01400 entries): turns 6 a tick (wrapped past -359);
   its two screen heights are the scene scale (ctx+0x3914[f68] / ctx+0x399E) x height - 20 (ends once the scale drops
   under 1); above the floor (ctx+0x399A) it falls 3 a tick with its top kept 18 above, below it the top falls until it
   meets the bottom, unhooking the next piece; while it still has links (f64) and its top is under the ceiling it
   hands its place, colour, top and turn + 20 to the scene and spawns the next piece with itself as the callback;
   fades in by 4 to 0x54 while the scene value is under 14, out by 16 while the scene state is under 10, else in by 10 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E006B0;

typedef struct Ent_c017_01E006B0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x28];
    struct Ent_c017_01E006B0 *prev;
    struct Ent_c017_01E006B0 *next;
    u8 pad48[8];
    Col_c017_01E006B0 col0;
    Col_c017_01E006B0 col1;
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    s16 f60;
    s16 f62;
    s16 f64;
    u8 pad66[2];
    s16 f68;
} Ent_c017_01E006B0;

typedef struct {
    u8 pad0[0x180];
    s32 v[3];
    u8 pad18C[0x38DC - 0x18C];
    s32 state;
    u8 rgb[4];
    u8 pad38E4[8];
    Ent_c017_01E006B0 *last;
    u8 pad38F0[4];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[0x14];
    f32 scale[14];
    f32 f394C;
    u8 pad3950[2];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
    u8 pad395C[4];
    s16 val;
    u8 pad3962[0x399A - 0x3962];
    s16 floor;
    u8 pad399C[2];
    s16 top;
} Ctx_c017_01E006B0;

/* the spawner takes a third argument it never reads (c017:01E01400 matches with two) */

static s32 func_01E006B0_c017(Ctx_c017_01E006B0 *g, Ent_c017_01E006B0 *o) {
    extern void c017_01E01400(Ctx_c017_01E006B0 *g, s32 arg, s32 h);
    f32 d;
    f32 fl;
    f32 s;
    s32 h;

    d = g->top;
    o->f5A -= 6;
    if (o->f5A < -359) {
        o->f5A %= 360;
    }
    fl = g->floor;
    s = g->scale[o->f68] / d;
    o->f60 = (s16)(s * o->f4 - 20.0f);
    if (g->scale[o->f68] < 1.0f) {
        o->used = 0;
    }
    o->f62 = (s16)(s * o->f14 - 20.0f);
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
        h = o->f60;
        g->f38F4 = h;
        g->f38F8 = o->f62;
        g->rgb[0] = o->col0.r;
        g->rgb[1] = o->col0.g;
        g->rgb[2] = o->col0.b;
        g->rgb[3] = 0;
        g->f3956 = 1;
        g->f38FC = o->f14;
        g->f394C = o->f68;
        g->f395A = 1;
        g->v[1] = 0;
        g->v[0] = 0;
        g->v[2] = 0;
        g->f3952 = o->f5A + 20;
        c017_01E01400(g, (s32)func_01E006B0_c017, h);
        o->f64 = 0;
    }
    if (g->val < 14) {
        if (o->col0.a < 0x50) {
            o->col0.a += 4;
        }
        if (o->col1.a < 0x50) {
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
        if (o->col0.a < 0xB0) {
            o->col0.a += 10;
        }
        if (o->col1.a < 0xB0) {
            o->col1.a += 10;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c017", func_01E009E0_c017);

/* shape c017:01E00D50, 112 insns: a falling trail piece: drops 2 a tick to -50 then fades both colours by 16 and ends; its two screen heights are the scene scale (ctx+0x3914 / ctx+0x399E) x height - 40 (ends when negative); its turn eases by its speed; fades in by 8 while the scene value is under 13, out by 16 while the scene state is under 10; ends at state 2 */

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[0xC];
    s32 w24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    u8 pad52[4];
    s16 h56;
    s16 h58;
} Obj_c017_01E00D50;

typedef struct {
    u8 pad[0x38DC];
    s32 state;
    u8 pad38E0[0x34];
    f32 scale;
    u8 pad3918[0x48];
    s16 val;
    u8 pad3962[0x3C];
    s16 div;
} Game_c017_01E00D50;

static s32 func_01E00D50_c017(Game_c017_01E00D50 *g, Obj_c017_01E00D50 *o) {
    extern s32 func_001A22C0(f32);
    f32 s;
    f32 d;

    d = g->div;
    if (o->y > -50.0f) {
        o->y -= 2.0f;
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    s = g->scale / d;
    o->h56 = func_001A22C0(s * o->y - 40.0f);
    if (o->h56 < 0) {
        o->mode = 0;
    }
    o->h58 = func_001A22C0(s * o->y - 40.0f);
    if (o->h58 < 0) {
        o->mode = 0;
    }
    o->w24 = func_001A22C0(o->w24 - o->f34);
    if (g->val < 13) {
        if (o->col[3] < 0x80) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 8;
        }
    }
    if (g->state < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        }
    }
    if (g->state == 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c017:01E00F10, 66 insns: sinks by its speed (0x34) down to -50, then both alphas fade by 0x10 (the second
   ends it); both grow by 8 (below 0x80) while the game step at 0x3960 is below 13; both fade by 0x10 while the
   counter at 0x38DC is below 10; the effect stops at counter 2 */

typedef struct {
    u8 pad0[0x38DC];
    s32 count;
    u8 pad38E0[0x80];
    s16 step;
} Game_c017_01E00F10;

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[0x1C];
    f32 speed;
    u8 pad38[0x10];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c017_01E00F10;

static s32 func_01E00F10_c017(Game_c017_01E00F10 *g, Fx_c017_01E00F10 *o) {
    if (!(o->y <= -50.0f)) {
        o->y -= o->speed;
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    if (g->step < 0xD) {
        if (o->col[3] < 0x80) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 8;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        }
    }
    if (g->count == 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c017:01E01020, 40 insns: both alphas grow by 0x20 (below 0x80 and 0x60) while the game step at 0x3960 is
   below 8; both fade by 15 while the counter at 0x38DC is below 10; the effect stops below 3 */

typedef struct {
    u8 pad0[0x38DC];
    s32 count;
    u8 pad38E0[0x80];
    s16 step;
} Game_c017_01E01020;

typedef struct {
    u8 pad0[0x50];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c017_01E01020;

static s32 func_01E01020_c017(Game_c017_01E01020 *g, Fx_c017_01E01020 *o) {
    if (g->step < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 0x20;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 15;
        }
    }
    if (g->count < 3) {
        o->mode = 0;
    }
    return 0;
}

/* shape c017:01E010C0, 205 insns: the c017 module's main step: with a code it clears the scene, fills the cosine table
   (0..90 degrees at ctx+0x39A4), keeps the code and a 156-tick timer and loads texture (4,15); otherwise it runs the
   scene setup (c017:01E00080), every live slot's handler (85 of 0x6C bytes) and every live trail piece (42 of 0x60
   bytes, c017:01E00D50), then draws them at the camera point (func_001F9D30) turned a quarter, scale (0.5, 1.5, 0.5):
   slots through their draw handler, pieces through c017:01E025B0 (falling pieces) or c017:01E02790, two passes each;
   counts down and returns 8 when the timer ends */

typedef struct {
    f32 x, y, z, w;
} V4_c017_01E010C0;

typedef struct Slot_c017_01E010C0 {
    u8 pad0[0x48];
    s32 (*draw)(void *, struct Slot_c017_01E010C0 *, void *, s32);
    s32 (*fn)(void *, struct Slot_c017_01E010C0 *);
    u8 pad50[8];
    s16 used;
    u8 pad5A[0x12];
} Slot_c017_01E010C0;

typedef struct {
    u8 pad0[0x44];
    s32 (*fn)(void *, void *);
    u8 pad48[8];
    s16 used;
    u8 pad52[0xE];
} Piece_c017_01E010C0;

typedef struct {
    u8 pad0[0x140];
    u8 cam[0xA0];
    s32 tex[16];
    s32 rot[4];
    V4_c017_01E010C0 sc;
    Slot_c017_01E010C0 slot[0x55];
    Piece_c017_01E010C0 piece[0x2A];
    u8 pad3B9C[0x38DC - 0x261C - 0x2A * 0x60];
    s32 timer;
    u8 pad38E0[8];
    s32 ot;
    u8 pad38EC[0x395C - 0x38EC];
    s16 code;
    u8 pad395E[0x39A4 - 0x395E];
    f32 cos[91];
} Ctx_c017_01E010C0;

static s32 func_01E010C0_c017(s32 arg0, s32 code) {
    extern void c017_01E00080(Ctx_c017_01E010C0 *, s32);
    extern s32 c017_01E00D50(Ctx_c017_01E010C0 *, Piece_c017_01E010C0 *);
    extern void c017_01E025B0(Ctx_c017_01E010C0 *, Piece_c017_01E010C0 *, void *, s32);
    extern void c017_01E02790(Ctx_c017_01E010C0 *, Piece_c017_01E010C0 *, void *, s32);
    Ctx_c017_01E010C0 *g = (Ctx_c017_01E010C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6A88(f32);
    extern V4_c017_01E010C0 *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    s32 n;
    V4_c017_01E010C0 pos;
    u8 pkt[0x90];
    s32 (*draw)(void *, Slot_c017_01E010C0 *, void *, s32);
    s32 i;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3B10);
        for (; n < 91; n++) {
            g->cos[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        g->code = code;
        g->timer = 156;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    c017_01E00080(g, 0);
    for (i = 0; i < 0x55; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn != NULL) {
                g->slot[i].fn(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 0x2A; i++) {
        if (g->piece[i].used != 0) {
            c017_01E00D50(g, &g->piece[i]);
        }
    }
    pos.x = pos.y = pos.z = 0.0f;
    pos.y = 50.0f;
    func_00205C40((s32)g->rot);
    pos = *func_001F9D30(0);
    g->rot[0] += 0x4000;
    g->sc.y = 1.5f;
    g->sc.x = 0.5f;
    g->sc.z = 0.5f;
    for (i = 0; i < 0x55; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            draw = g->slot[i].draw;
            if (draw != NULL) {
                draw(g, &g->slot[i], pkt, 0);
                draw(g, &g->slot[i], pkt, 1);
            }
        }
    }
    for (i = 0; i < 0x2A; i++) {
        if (g->piece[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            if (g->piece[i].fn == (void *)c017_01E00D50) {
                c017_01E025B0(g, &g->piece[i], pkt, 0);
                c017_01E025B0(g, &g->piece[i], pkt, 1);
            } else {
                c017_01E02790(g, &g->piece[i], pkt, 0);
                c017_01E02790(g, &g->piece[i], pkt, 1);
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape c017:01E01400, 131 insns: c017 trail link spawner (c560:01E01C50 family, 85 slots of 0x6C at ctx+0x240): takes the first free slot (marks it slot+1), both colours from the context with alpha 0, the context's vector, its sizes as shorts, height 18 above, both capped by the context's ceiling, chained after the context's last piece and becomes it; draws with c017:01E01BF0 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E01400;

typedef struct Ent_c017_01E01400 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    struct Ent_c017_01E01400 *prev;
    struct Ent_c017_01E01400 *next;
    void (*cb)(void);
    s32 arg;
    Col_c017_01E01400 col0;
    Col_c017_01E01400 col1;
    s16 used;
    s16 f5A;
    u8 pad5C[2];
    s16 f5E;
    s16 f60;
    s16 f62;
    s16 f64;
    s16 f66;
    s16 f68;
    u8 pad6A[2];
} Ent_c017_01E01400;

typedef struct {
    u8 pad0[0x180];
    Vec4f v;
    u8 pad190[0x240 - 0x190];
    Ent_c017_01E01400 ent[85];
    u8 padEnd[0x38E0 - 0x240 - 85 * 0x6C];
    u8 rgb[4];
    u8 pad38E4[8];
    Ent_c017_01E01400 *last;
    u8 pad38F0[4];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[0x394C - 0x3900];
    f32 f394C;
    u8 pad3950[2];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
    u8 pad395C[0x399E - 0x395C];
    s16 top;
} Ctx_c017_01E01400;

static void func_01E01400_c017(Ctx_c017_01E01400 *g, s32 arg) {
    extern void c017_01E01BF0(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s32 i;
    Ent_c017_01E01400 *e = NULL;
    Ent_c017_01E01400 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 85; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x6C);
            g->ent[i].used = i + 1;
            i = 85;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col1.a = 0;
        e->v = g->v;
        e->f60 = (s16)g->f38F4;
        e->f62 = (s16)g->f38F8;
        e->f5E = (s16)g->f38FC;
        e->f5A = g->f3952;
        e->prev = g->last;
        e->f66 = g->f395A;
        if (e->prev == NULL) {
            h = g->f38FC;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f38FC;
            e->f4 = h;
            e->f14 = h + d;
        }
        if ((f32)g->top < e->f4) {
            e->f4 = g->top;
        }
        if ((f32)g->top < e->f14) {
            e->f14 = g->top;
        }
        e->f68 = (s16)g->f394C;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->f64 = g->f3956;
        e->cb = c017_01E01BF0;
        e->arg = arg;
        g->last = e;
    }
}

/* shape c017:01E01610, 139 insns: c017:01E01400 with three more copied words (f5C, f6A, and the position's y/w at
   f24/f2C) and the c017:01E02120 draw callback */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E01610;

typedef struct Ent_c017_01E01610 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[4];
    f32 f2C;
    Vec4f v;
    struct Ent_c017_01E01610 *prev;
    struct Ent_c017_01E01610 *next;
    void (*cb)(void);
    s32 arg;
    Col_c017_01E01610 col0;
    Col_c017_01E01610 col1;
    s16 used;
    s16 f5A;
    s16 f5C;
    s16 f5E;
    s16 f60;
    s16 f62;
    s16 f64;
    s16 f66;
    s16 f68;
    s16 f6A;
} Ent_c017_01E01610;

typedef struct {
    u8 pad0[0x180];
    Vec4f v;
    u8 pad190[0x240 - 0x190];
    Ent_c017_01E01610 ent[85];
    u8 padEnd[0x38E0 - 0x240 - 85 * 0x6C];
    u8 rgb[4];
    u8 pad38E4[8];
    Ent_c017_01E01610 *last;
    u8 pad38F0[4];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[8];
    f32 f3908;
    u8 pad390C[4];
    f32 f3910;
    u8 pad3914[0x394C - 0x3914];
    f32 f394C;
    u8 pad3950[2];
    s16 f3952;
    s16 f3954;
    s16 f3956;
    s16 f3958;
    s16 f395A;
    u8 pad395C[0x399E - 0x395C];
    s16 top;
} Ctx_c017_01E01610;

static void func_01E01610_c017(Ctx_c017_01E01610 *g, s32 arg) {
    extern void c017_01E02120(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s32 i;
    Ent_c017_01E01610 *e = NULL;
    Ent_c017_01E01610 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 85; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x6C);
            g->ent[i].used = i + 1;
            i = 85;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col1.a = 0;
        e->v = g->v;
        e->f60 = (s16)g->f38F4;
        e->f62 = (s16)g->f38F8;
        e->f5E = (s16)g->f38FC;
        e->f5A = g->f3952;
        e->f5C = g->f3954;
        e->prev = g->last;
        e->f66 = g->f395A;
        if (e->prev == NULL) {
            h = g->f38FC;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f38FC;
            e->f4 = h;
            e->f14 = h + d;
        }
        if ((f32)g->top < e->f4) {
            e->f4 = g->top;
        }
        if ((f32)g->top < e->f14) {
            e->f14 = g->top;
        }
        e->f6A = g->f3958;
        e->f68 = (s16)g->f394C;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->f24 = g->f3908;
        e->f2C = g->f3910;
        e->f64 = g->f3956;
        e->cb = c017_01E02120;
        e->arg = arg;
        g->last = e;
    }
}

/* shape c017:01E01840, 91 insns: take a free row (0x32 of 0x60 bytes at 0x261C, mark = index + 1), clear it, two
   colours from the scene colour 0x38E0 with alpha 0x80, copy the scene vector 0x180, 0x56/0x58 from the scene floats
   0x38F4/0x38F8, 0x52/0x5C/0x5A from 0x3952/0x395A/0x3956, f14 from 0x38FC, f34 random 16..2063, callback
   c017:01E025B0 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c017_01E01840;

typedef struct {
    V4_c017_01E01840 pos;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[8];
    void (*cb)(void);
    s32 arg;
    u8 c48[4];
    u8 c4C[4];
    s16 used;
    s16 f52;
    u8 pad54[2];
    s16 f56;
    s16 f58;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
} Row_c017_01E01840;

typedef struct {
    u8 pad0[0x180];
    V4_c017_01E01840 pos;
    u8 pad190[0x261C - 0x190];
    Row_c017_01E01840 rows[0x32];
    u8 pad38DC[4];
    u8 rgb[4];
    u8 pad38E4[0x10];
    f32 f38F4;
    f32 f38F8;
    f32 f38FC;
    u8 pad3900[0x52];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
} Scene_c017_01E01840;

static void func_01E01840_c017(Scene_c017_01E01840 *g, s32 arg) {
    extern void c017_01E025B0(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c017_01E01840 *s = NULL;
    s32 i;

    for (i = 0; i < 0x32; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x60);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c48, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c48[3] = 0x80;
        func_001076F0(s->c4C, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c4C[3] = 0x80;
        s->pos = g->pos;
        s->f56 = g->f38F4;
        s->f58 = g->f38F8;
        s->f52 = g->f3952;
        s->f14 = g->f38FC;
        s->f5C = g->f395A;
        s->f34 = func_0019A5C8() % 0x800 + 0x10;
        s->f5A = g->f3956;
        s->cb = c017_01E025B0;
        s->arg = arg;
    }
}

/* shape c017:01E019B0, 82 insns: takes the first free of 50 effect slots (0x60 bytes, c017:01E01B00 family), marks it with its
   index + 1, colours both from the context at alpha 0x80, copies the context's point, frames, sizes and turn, and hooks
   c017:01E02790 with the given argument */

typedef struct {
    Vec4f pos;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[8];
    void (*cb)(void);
    s32 arg;
    u8 c48[4];
    u8 c4C[4];
    s16 used;
    s16 f52;
    u8 pad54[2];
    s16 w;
    s16 h;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
} Slot_c017_01E019B0;

typedef struct {
    u8 pad0[0x180];
    Vec4f pos;
    u8 pad190[0x261C - 0x190];
    Slot_c017_01E019B0 slots[0x32];
    u8 pad[0x38E0 - 0x261C - 0x32 * 0x60];
    u8 rgba[4];
    u8 pad38E4[0x10];
    f32 w;
    f32 h;
    f32 f38FC;
    u8 pad3900[8];
    f32 f3908;
    u8 pad390C[0x46];
    s16 f3952;
    u8 pad3954[2];
    s16 f3956;
    u8 pad3958[2];
    s16 f395A;
} Ctx_c017_01E019B0;

static void func_01E019B0_c017(Ctx_c017_01E019B0 *ctx, s32 arg) {
    extern void c017_01E02790(void);
    extern void func_001076F0();
    extern void func_00195108();
    s32 i;
    Slot_c017_01E019B0 *s = NULL;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x60);
            ctx->slots[i].used = i + 1;
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c48, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c48[3] = 0x80;
        func_001076F0(s->c4C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c4C[3] = 0x80;
        s->pos = ctx->pos;
        s->w = ctx->w;
        s->h = ctx->h;
        s->f52 = ctx->f3952;
        s->f14 = ctx->f38FC;
        s->f5C = ctx->f395A;
        s->f34 = ctx->f3908;
        s->f5A = ctx->f3956;
        s->cb = c017_01E02790;
        s->arg = arg;
    }
}

/* shape c017:01E01B00, 58 insns: takes the first free of 85 effect slots (0x6C bytes, b108:01E02FF0 family), marks it
   with its index + 1, colours both from the context at alpha 0, and hooks c017:01E02970 with the given argument */

typedef struct {
    u8 pad0[0x48];
    void (*cb)(void);
    s32 arg;
    u8 c50[4];
    u8 c54[4];
    s16 used;
    u8 pad5A[0x12];
} Slot_c017_01E01B00;

typedef struct {
    u8 pad0[0x240];
    Slot_c017_01E01B00 slots[0x55];
    u8 pad[0x38E0 - 0x240 - 0x55 * 0x6C];
    u8 rgba[4];
} Ctx_c017_01E01B00;

static void func_01E01B00_c017(Ctx_c017_01E01B00 *ctx, s32 arg) {
    extern void c017_01E02970(void);
    extern void func_001076F0();
    extern void func_00195108();
    s32 i;
    Slot_c017_01E01B00 *s = NULL;

    for (i = 0; i < 0x55; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x6C);
            ctx->slots[i].used = i + 1;
            i = 0x55;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c50, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c50[3] = 0;
        func_001076F0(s->c54, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c54[3] = 0;
        s->cb = c017_01E02970;
        s->arg = arg;
    }
}

/* shape c017:01E01BF0 (C017PAINT_RAIN2), 330 insns, 1 copy: mode 0 sets the drawing state (a 0x97
   matrix, packet header, top colours from the previous segment 0x54 or own 0x50, bottom from own 0x54, scene texture
   0x21C); otherwise a 12-step ring band 30 degrees apart: inner edge from the previous segment (radius 0x62, height
   0x14) or its own (radius 0x60, height 0x04), outer edge at radius 0x62 and height 0x14, a 0x9C matrix, the scene
   quad 0x1A0 sent twice with texture 0x38E8 when on screen */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c017_01E01BF0;

typedef struct {
    Rgbaq_c017_01E01BF0 c;
    u64 st;
    u64 xyz;
} Vtx_c017_01E01BF0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c017_01E01BF0 v[4];
} Pkt_c017_01E01BF0;

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E01BF0;

typedef struct Ent_c017_01E01BF0 {
    f32 x0;
    f32 y0;
    f32 z0;
    u8 padC[4];
    f32 x1;
    f32 y1;
    f32 z1;
    u8 pad1C[0x10];
    f32 f2C;
    Vec4f v;
    struct Ent_c017_01E01BF0 *prev;
    struct Ent_c017_01E01BF0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c017_01E01BF0 col0;
    Col_c017_01E01BF0 col1;
    s16 used;
    s16 f5A;
    s16 f5C;
    s16 f5E;
    s16 f60;
    s16 f62;
    s16 f64;
    s16 f66;
    s16 f68;
    s16 f6A;
} Ent_c017_01E01BF0;

typedef struct {
    u8 pad0[0x140];
    f32 m[16];
    u8 pad180[0x20];
    Vec4f quad[4];
    u8 pad1E0[0x3C];
    s32 tex;
    u8 pad220[0x38E8 - 0x220];
    s32 tex2;
    u8 pad38EC[0x3934 - 0x38EC];
    f32 depth;
    u8 pad3938[0x39A4 - 0x3938];
    u8 trig[1];
} Scene_c017_01E01BF0;

static void func_01E01BF0_c017(Scene_c017_01E01BF0 *g, Ent_c017_01E01BF0 *o, Pkt_c017_01E01BF0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c017_01E01BF0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Ent_c017_01E01BF0 *prev = o->prev;
    f32 rm[4];
    f32 m[16];
    s16 a = 0;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0xB0 << 32) | 0x48);
        if (prev != NULL) {
            p->v[0].c = func_00107740(&prev->col1);
            p->v[1].c = func_00107740(&prev->col1);
        } else {
            p->v[0].c = func_00107740(&o->col0);
            p->v[1].c = func_00107740(&o->col0);
        }
        p->v[2].c = func_00107740(&o->col1);
        p->v[3].c = func_00107740(&o->col1);
        func_00108500(p, rm, 1);
        func_00208700(p, g->tex, 1);
    } else {
        func_0020EB40(m);
        for (i = 0; i < 12; i++) {
            if (prev != NULL) {
                g->quad[0].x = prev->f62 * func_00108030(g->trig, a + prev->f5A, 1);
                g->quad[0].z = prev->f62 * func_00108030(g->trig, a + prev->f5A, 0);
                g->quad[1].x = prev->f62 * func_00108030(g->trig, a + prev->f5A + 30, 1);
                g->quad[1].z = prev->f62 * func_00108030(g->trig, a + prev->f5A + 30, 0);
                g->quad[1].y = g->quad[0].y = prev->y1;
            } else {
                g->quad[0].x = o->f60 * func_00108030(g->trig, a + o->f5A, 1);
                g->quad[0].z = o->f60 * func_00108030(g->trig, a + o->f5A, 0);
                g->quad[1].x = o->f60 * func_00108030(g->trig, a + o->f5A + 30, 1);
                g->quad[1].z = o->f60 * func_00108030(g->trig, a + o->f5A + 30, 0);
                g->quad[1].y = g->quad[0].y = o->y0;
            }
            g->quad[2].x = o->f62 * func_00108030(g->trig, a + o->f5A, 1);
            g->quad[2].z = o->f62 * func_00108030(g->trig, a + o->f5A, 0);
            g->quad[3].x = o->f62 * func_00108030(g->trig, a + o->f5A + 30, 1);
            g->quad[3].z = o->f62 * func_00108030(g->trig, a + o->f5A + 30, 0);
            g->quad[3].y = g->quad[2].y = o->y1;
            func_00106080(rm, 0x9C, 0, rm);
            func_00108500(p, rm, 0);
            if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
                func_002075F0(p, g->tex2, func_001A23B0(g->depth));
                func_002075F0(p, g->tex2, func_001A23B0(g->depth));
            }
            a += 30;
        }
    }
}

/* shape c017:01E02120 (C017PAINT_RAIN3), 289 insns, 1 copy: mode 0 sets the drawing state (a 0x97 matrix, colour 1
   from the previous segment 0x54 or own 0x50, colour 2 from 0x54 with its alpha cleared when 0x6A is 0, the scene
   texture 0x21C); otherwise three passes of a 15-step band: the inner edge from the previous segment (radius 0x62,
   angle 0x5A, height 0x14) or its own (radius 0x60, height 0x04), the outer edge at radius 0x62 and height 0x14, the
   scene quad 0x1A0 sent with texture 0x38E8 when on screen, the next start angle from the scene table 0x3968 row
   (s16)0x2C */

typedef struct {
    u8 r, g, b, a;
} Col_c017_01E02120;

typedef struct Ent_c017_01E02120 {
    f32 x0;
    f32 y0;
    f32 z0;
    u8 padC[4];
    f32 x1;
    f32 y1;
    f32 z1;
    u8 pad1C[0x10];
    f32 f2C;
    Vec4f v;
    struct Ent_c017_01E02120 *prev;
    struct Ent_c017_01E02120 *next;
    void (*cb)(void);
    s32 arg;
    Col_c017_01E02120 col0;
    Col_c017_01E02120 col1;
    s16 used;
    s16 f5A;
    s16 f5C;
    s16 f5E;
    s16 f60;
    s16 f62;
    s16 f64;
    s16 f66;
    s16 f68;
    s16 f6A;
} Ent_c017_01E02120;

typedef struct {
    u8 pad0[0x140];
    f32 m[16];
    u8 pad180[0x20];
    Vec4f quad[4];
    u8 pad1E0[0x3C];
    s32 tex;
    u8 pad220[0x38E8 - 0x220];
    s32 tex2;
    u8 pad38EC[0x3934 - 0x38EC];
    f32 depth;
    u8 pad3938[0x3968 - 0x3938];
    s16 tab[6][5];
    u8 trig[1];
} Scene_c017_01E02120;

static void func_01E02120_c017(Scene_c017_01E02120 *g, Ent_c017_01E02120 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Ent_c017_01E02120 *prev = o->prev;
    f32 rm[4];
    s16 a;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        if (prev != NULL) {
            func_00107790(p, &prev->col1, 1);
        } else {
            func_00107790(p, &o->col0, 1);
        }
        if (o->f6A != 0) {
            func_00107790(p, &o->col1, 2);
        } else {
            o->col1.a = 0;
            func_00107790(p, &o->col1, 2);
        }
        func_00108500(p, rm, 1);
        func_00208700(p, g->tex, 1);
    } else {
        a = o->f5C;
        for (i = 0; i < 3; i++) {
            if (prev != NULL) {
                g->quad[0].x = o->x0 = prev->f62 * func_00108030(g->trig, a + prev->f5A, 1);
                g->quad[0].z = o->z0 = prev->f62 * func_00108030(g->trig, a + prev->f5A, 0);
                g->quad[1].x = prev->f62 * func_00108030(g->trig, a + prev->f5A + 15, 1);
                g->quad[1].z = prev->f62 * func_00108030(g->trig, a + prev->f5A + 15, 0);
                g->quad[1].y = g->quad[0].y = o->y0 = prev->y1;
            } else {
                g->quad[0].x = o->x0 = o->f60 * func_00108030(g->trig, a + o->f5A, 1);
                g->quad[0].z = o->z0 = o->f60 * func_00108030(g->trig, a + o->f5A, 0);
                g->quad[1].x = o->f60 * func_00108030(g->trig, a + o->f5A + 15, 1);
                g->quad[1].z = o->f60 * func_00108030(g->trig, a + o->f5A + 15, 0);
                g->quad[1].y = g->quad[0].y = o->y0;
            }
            g->quad[2].x = o->x1 = o->f62 * func_00108030(g->trig, a + o->f5A, 1);
            g->quad[2].z = o->z1 = o->f62 * func_00108030(g->trig, a + o->f5A, 0);
            g->quad[3].x = o->f62 * func_00108030(g->trig, a + o->f5A + 15, 1);
            g->quad[3].z = o->f62 * func_00108030(g->trig, a + o->f5A + 15, 0);
            g->quad[2].y = g->quad[3].y = o->y1;
            if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
                func_002075F0(p, g->tex2, func_001A23B0(g->depth));
            }
            a = g->tab[(s16)(s32)o->f2C][i];
        }
    }
}

/* shape c017:01E025B0, 118 insns: mode 0 sets the drawing state (a 0x9B matrix from the angle 0x5A, colours 0x48/0x4C,
   the scene texture 0x21C); otherwise sizes the scene quad 0x1A0 to 0x56, puts all four corners at height 0x14,
   pushes them 0x58 along the heading 0x52 (game table 0x39A4), builds the rotation matrix 0x140 from 0x20 and, when
   the quad is on screen, sends it with the scene texture 0x38E8 */

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[0x18];
    u8 col[4];
    u8 col2[4];
    u8 pad50[2];
    s16 heading;
    u8 pad54[2];
    s16 size;
    s16 dist;
    s16 angle;
} Fx_c017_01E025B0;

typedef struct {
    u8 pad0[0x140];
    f32 m[16];
    u8 pad180[0x20];
    Vec4f quad[4];
    u8 pad1E0[0x3C];
    s32 tex;
    u8 pad220[0x38E8 - 0x220];
    s32 tex2;
    u8 pad38EC[0x3934 - 0x38EC];
    f32 depth;
    u8 pad3938[0x39A4 - 0x3938];
    u8 trig[1];
} Scene_c017_01E025B0;

static void func_01E025B0_c017(Scene_c017_01E025B0 *g, Fx_c017_01E025B0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108D20(void *, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_0020C940(void *, s32, void *, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 m[16];
    f32 a;
    f32 b;
    s16 size;

    size = o->size;
    if (mode == 0) {
        func_00106080(rm, 0x9B, o->angle, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 1);
        func_00107790(p, o->col2, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00108D20(g->quad, size, size);
        g->quad[0].y = g->quad[1].y = g->quad[2].y = g->quad[3].y = o->y;
        a = o->dist * func_00108030(g->trig, o->heading, 1);
        b = o->dist * func_00108030(g->trig, o->heading, 0);
        g->quad[0].x += a;
        g->quad[0].z += b;
        g->quad[1].x += a;
        g->quad[1].z += b;
        g->quad[2].x += a;
        g->quad[2].z += b;
        g->quad[3].x += a;
        g->quad[3].z += b;
        func_0020C940(m, 0, o->rot, 0);
        func_0020BC00(g->m, m);
        if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
            func_002075F0(p, g->tex2, func_001A23B0(g->depth));
        }
    }
}

/* shape c017:01E02790 (C017PAINT_RAIN5), 119 insns, 1 copy (-O3,p): mode 0 sets the drawing state (a 0x9B matrix from
   the angle 0x5A, colour 0x48 for both slots, the scene texture 0x21C); otherwise sizes the scene quad 0x1A0 to 0x5C,
   puts all four corners at height 0x14, pushes them 0x56 along the heading 0x52 (game table 0x39A4), builds the
   rotation matrix 0x140 from 0x20 and, when the quad is on screen, sends it with the scene texture 0x38E8; the source
   of shape c017:01E025B0, built here at -O3 */

typedef struct {
    u8 pad0[0x14];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[0x18];
    u8 col[4];
    u8 col2[4];
    u8 pad50[2];
    s16 heading;
    u8 pad54[2];
    s16 dist;
    u8 pad58[2];
    s16 angle;
    s16 size;
} Fx_c017_01E02790;

typedef struct {
    u8 pad0[0x140];
    f32 m[16];
    u8 pad180[0x20];
    Vec4f quad[4];
    u8 pad1E0[0x3C];
    s32 tex;
    u8 pad220[0x38E8 - 0x220];
    s32 tex2;
    u8 pad38EC[0x3934 - 0x38EC];
    f32 depth;
    u8 pad3938[0x39A4 - 0x3938];
    u8 trig[1];
} Scene_c017_01E02790;

#pragma optimization_level 3

static void func_01E02790_c017(Scene_c017_01E02790 *g, Fx_c017_01E02790 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108D20(void *, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_0020C940(void *, s32, void *, s32);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 m[16];
    f32 a;
    f32 b;

    if (mode == 0) {
        func_00106080(rm, 0x9B, o->angle, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 1);
        func_00107790(p, o->col, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00108D20(g->quad, o->size, o->size);
        g->quad[0].y = g->quad[1].y = g->quad[2].y = g->quad[3].y = o->y;
        a = o->dist * func_00108030(g->trig, o->heading, 1);
        b = o->dist * func_00108030(g->trig, o->heading, 0);
        g->quad[0].x += a;
        g->quad[0].z += b;
        g->quad[1].x += a;
        g->quad[1].z += b;
        g->quad[2].x += a;
        g->quad[2].z += b;
        g->quad[3].x += a;
        g->quad[3].z += b;
        func_0020C940(m, 0, o->rot, 0);
        func_0020BC00(g->m, m);
        if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
            func_002075F0(p, g->tex2, func_001A23B0(g->depth));
        }
    }
}

#pragma optimization_level reset

/* shape c017:01E02970, 71 insns: draws a slot effect (c035:01E01290 shape with the effect colours at 0x50): mode 0 builds the
   gouraud packet with q 0, other modes queue it */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c017_01E02970;

typedef struct {
    Rgbaq_c017_01E02970 c;
    u64 xyz;
} Vtx_c017_01E02970;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c017_01E02970 v[4];
} Pkt_c017_01E02970;

typedef struct {
    u8 pad0[0x50];
    u8 c40[4];
    u8 c44[4];
} Fx_c017_01E02970;

typedef struct {
    u8 pad0[0x38E8];
    s32 target;
} Scene_c017_01E02970;

static void func_01E02970_c017(Scene_c017_01E02970 *g, Fx_c017_01E02970 *o, Pkt_c017_01E02970 *p, s32 mode) {
    extern Rgbaq_c017_01E02970 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->c40);
        p->v[1].c = func_00107740(o->c40);
        p->v[2].c = func_00107740(o->c44);
        p->v[3].c = func_00107740(o->c44);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 0.0f;
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}
