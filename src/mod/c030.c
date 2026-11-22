#include "common.h"

/* shape c030:01E00080 (C030_W_S), 693 insns, 1 copy: C030_W_S, the scene step: tint 0x30, counts the frame (0x2E4);
   at 1 colours twelve slots by the mode at 0x2E0 (white, red, green, blue, yellow, magenta, cyan, 0xFF/0x80/0xFF,
   0x80/0/0xFF, 0xFF/0x80/0, else white), four random timers 120 apart, then one-pass loops (i = 4) spawn 0x1E00E30
   through 0x1E01AE0 and nine 0x1E00B60 columns through 0x1E018C0 at angles i*15/35/45 (+120, +240), sides 0/1/2 */

typedef struct {
    u8 pad0[0x80];
    f32 f80;
    f32 f84;
    f32 f88;
    u8 pad8C[0xF4 - 0x8C];
    u8 col[4];
    u8 padF8[8];
    s32 w100;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D0 - 0x114];
    f32 f2D0;
    s16 h2D4;
    s16 h2D6;
    u8 pad2D8[2];
    s16 h2DA;
    u8 pad2DC[2];
    s16 h2DE;
    s16 mode;
    u8 pad2E2[2];
    s16 frame;
    u8 pad2E6[4];
    s16 h2EA;
    u8 pad2EC[4];
    s16 h2F0;
    s16 t[4];
    u8 pad2FA[2];
    u8 cols[12][4];
} Scene_c030_01E00080;

static void func_01E00080_c030(Scene_c030_01E00080 *g) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void c030_01E01AE0();
    extern void c030_01E018C0();
    extern s32 func_01E00E30_c030();
    extern s32 func_01E00B60_c030();
    s32 i;

    g->col[0] = 0x30;
    g->col[1] = 0x30;
    g->col[2] = 0x30;
    g->frame++;
    if (g->frame == 1) {
        for (i = 0; i < 12; i++) {
            g->cols[i][3] = 0x80;
            if (g->mode == 0) {
                func_001076F0(g->cols[i], 0xFF, 0xFF, 0xFF);
            } else if (g->mode == 1) {
                func_001076F0(g->cols[i], 0xFF, 0, 0);
            } else if (g->mode == 2) {
                func_001076F0(g->cols[i], 0, 0xFF, 0);
            } else if (g->mode == 3) {
                func_001076F0(g->cols[i], 0, 0, 0xFF);
            } else if (g->mode == 4) {
                func_001076F0(g->cols[i], 0xFF, 0xFF, 0);
            } else if (g->mode == 5) {
                func_001076F0(g->cols[i], 0xFF, 0, 0xFF);
            } else if (g->mode == 6) {
                func_001076F0(g->cols[i], 0, 0xFF, 0xFF);
            } else if (g->mode == 7) {
                func_001076F0(g->cols[i], 0xFF, 0x80, 0xFF);
            } else if (g->mode == 8) {
                func_001076F0(g->cols[i], 0x80, 0, 0xFF);
            } else if (g->mode == 9) {
                func_001076F0(g->cols[i], 0xFF, 0x80, 0);
            } else {
                func_001076F0(g->cols[i], 0xFF, 0xFF, 0xFF);
            }
        }
        g->f2D0 = 0.5f;
        g->t[0] = func_0019A5C8() % 120;
        g->t[1] = g->t[0] + func_0019A5C8() % 120 + 100;
        g->t[2] = g->t[0] + func_0019A5C8() % 120 + 200;
        g->t[3] = g->t[0] + func_0019A5C8() % 120 + 300;
        g->f80 = 0.0f;
        g->f84 = 1.0f;
        g->f88 = 0.0f;
        g->f108 = 10.0f;
        func_001076F0(g->col, 0x80, 0x80, 0x80);
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = i * 10 + 1;
            g->f10C = i * 11 + 1;
            if (i != 4) {
                g->h2DA = 0;
            } else {
                g->h2DA = 1;
            }
            g->f110 = i * 15;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->col[3] = 0;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->h2D6 = i * 15;
            g->h2D4 = 3;
            c030_01E01AE0(g, func_01E00E30_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 15;
            g->h2EA = 7;
            g->h2D4 = 0;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 15 + 120;
            g->h2EA = 7;
            g->h2D4 = 0;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 15 + 240;
            g->h2EA = 7;
            g->h2D4 = 0;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 35;
            g->h2EA = 7;
            g->h2D4 = 1;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 35 + 120;
            g->h2EA = 7;
            g->h2D4 = 1;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 35 + 240;
            g->h2EA = 7;
            g->h2D4 = 1;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 45;
            g->h2EA = 7;
            g->h2D4 = 2;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 45 + 120;
            g->h2EA = 7;
            g->h2D4 = 2;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
        g->w100 = 0;
        for (i = 4; i < 5; i++) {
            g->f108 = 30.0f;
            g->f10C = 30.0f;
            if (i == 4) {
                g->h2DA = 1;
            } else {
                g->h2DA = 0;
            }
            g->f110 = i * 25;
            g->h2DE = 1;
            g->f84 = 0.0f;
            g->f80 = 0.0f;
            g->f88 = 0.0f;
            g->col[3] = 0;
            g->h2D6 = i * 45 + 240;
            g->h2EA = 7;
            g->h2D4 = 2;
            if (g->h2F0 == 0) {
                g->h2F0 = 1;
            } else {
                g->h2F0 = 0;
            }
            c030_01E018C0(g, func_01E00B60_c030);
        }
    }
}

/* shape c030:01E00B60, 179 insns: c560:01E02520 family falling column segment: its angle turns back by 18 (wrapped past
   -359), the bottom drops by 5 to the floor while the top follows within 13, then the top closes down and ends it
   (clearing the linked node); while it may still spawn and its top is under 50 it hands the scene one more segment
   (this function) at its place, angle + 35, grey 0x10, numbered on, side by flag 0x78, once the scene timer is 23 or
   more; both alphas rise by 8 to 0x40 for 8 frames, fade by 10 when low, else rise by 7 to 0x80 (the second only
   while linked) */

typedef struct {
    u8 pad0[0x50];
    s32 w50;
} Link_c030_01E00B60;

typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x3C];
    Link_c030_01E00B60 *link;
    u8 pad58[8];
    u8 col[4];
    u8 col2[4];
    s16 h68;
    s16 h6A;
    s16 h6C;
    u8 pad6E[2];
    s16 h70;
    s16 ang;
    s16 h74;
    u8 pad76[2];
    s16 h78;
} Seg_c030_01E00B60;

typedef struct {
    u8 pad0[0xF0];
    s32 timer;
    u8 col[4];
    u8 padF8[8];
    Seg_c030_01E00B60 *parent;
    u8 pad104[4];
    f32 px, py, pz;
    u8 pad114[0x1C0];
    s16 h2D4;
    s16 ang;
    u8 pad2D8[2];
    s16 h2DA;
    u8 pad2DC[2];
    s16 h2DE;
    u8 pad2E0[4];
    s16 frame;
    u8 pad2E6[4];
    s16 h2EA;
    u8 pad2EC[4];
    s16 h2F0;
} Scene_c030_01E00B60;

static s32 func_01E00B60_c030(Scene_c030_01E00B60 *g, Seg_c030_01E00B60 *o) {
    extern void c030_01E018C0(Scene_c030_01E00B60 *, void *);
    extern s16 func_001A22C0(f32);

    o->ang -= 18;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->h6A = func_001A22C0(o->f4);
    o->h6C = func_001A22C0(o->f14);
    if (o->f4 > 0.0f) {
        o->f4 -= 5.0f;
        if (o->f14 - o->f4 >= 13.0f) {
            o->f14 -= 5.0f;
        }
    } else {
        o->f14 -= 5.0f;
        if (o->f14 < o->f4) {
            o->f14 = o->f4;
            if (o->link != NULL) {
                o->link->w50 = 0;
            }
            o->h68 = 0;
        }
    }
    if (o->h74 > 0 && o->f14 < 50.0f) {
        g->parent = o;
        g->px = o->h6A;
        g->py = o->h6C;
        g->col[3] = 0;
        g->col[0] = 0x10;
        g->col[1] = 0x10;
        g->col[2] = 0x10;
        g->h2DA = 1;
        g->pz = o->f14;
        g->h2DE = 1;
        g->ang = o->ang + 35;
        if (o->h78 != 0) {
            g->h2F0 = 0;
        } else {
            g->h2F0 = 1;
        }
        g->h2D4 = o->h70;
        g->h2EA = 7;
        if (g->timer > 22) {
            c030_01E018C0(g, func_01E00B60_c030);
        }
        o->h74 = 0;
    }
    if (g->frame < 8) {
        if (o->col[3] < 0x40) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x40) {
            o->col2[3] += 8;
        }
    } else if (o->f14 < 15.0f) {
        if (o->col[3] > 16) {
            o->col[3] -= 10;
        }
        if (o->col2[3] > 16) {
            o->col2[3] -= 10;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 7;
        }
        if (o->link != NULL) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 7;
            }
        }
    }
    return 0;
}

/* shape c030:01E00E30, 182 insns: c030:01E00B60's segment handing on in grey 0x70 with the scene turn (0x80) cleared,
   through the other spawner (0x1E01AE0), alphas capped at 0xC0 */

typedef struct {
    u8 pad0[0x50];
    s32 w50;
} Link_c030_01E00E30;

typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x3C];
    Link_c030_01E00E30 *link;
    u8 pad58[8];
    u8 col[4];
    u8 col2[4];
    s16 h68;
    s16 h6A;
    s16 h6C;
    u8 pad6E[2];
    s16 h70;
    s16 ang;
    s16 h74;
    u8 pad76[2];
    s16 h78;
} Seg_c030_01E00E30;

typedef struct {
    u8 pad0[0x80];
    s32 r80, r84, r88;
    u8 pad8C[0x64];
    s32 timer;
    u8 col[4];
    u8 padF8[8];
    Seg_c030_01E00E30 *parent;
    u8 pad104[4];
    f32 px, py, pz;
    u8 pad114[0x1C0];
    s16 h2D4;
    s16 ang;
    u8 pad2D8[2];
    s16 h2DA;
    u8 pad2DC[2];
    s16 h2DE;
    u8 pad2E0[4];
    s16 frame;
    u8 pad2E6[4];
    s16 h2EA;
    u8 pad2EC[4];
    s16 h2F0;
} Scene_c030_01E00E30;

static s32 func_01E00E30_c030(Scene_c030_01E00E30 *g, Seg_c030_01E00E30 *o) {
    extern void c030_01E01AE0(Scene_c030_01E00E30 *, void *);
    extern s16 func_001A22C0(f32);

    o->ang -= 18;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->h6A = func_001A22C0(o->f4);
    o->h6C = func_001A22C0(o->f14);
    if (o->f4 > 0.0f) {
        o->f4 -= 5.0f;
        if (o->f14 - o->f4 >= 13.0f) {
            o->f14 -= 5.0f;
        }
    } else {
        o->f14 -= 5.0f;
        if (o->f14 < o->f4) {
            o->f14 = o->f4;
            if (o->link != NULL) {
                o->link->w50 = 0;
            }
            o->h68 = 0;
        }
    }
    if (o->h74 > 0 && o->f14 < 50.0f) {
        g->parent = o;
        g->px = o->h6A;
        g->py = o->h6C;
        g->col[3] = 0;
        g->col[0] = 0x70;
        g->col[1] = 0x70;
        g->col[2] = 0x70;
        g->h2DA = 1;
        g->pz = o->f14;
        g->h2DE = 1;
        g->r84 = 0;
        g->r80 = 0;
        g->r88 = 0;
        g->ang = o->ang + 35;
        g->h2EA = 7;
        if (o->h78 != 0) {
            g->h2F0 = 0;
        } else {
            g->h2F0 = 1;
        }
        g->h2D4 = o->h70;
        if (g->timer > 22) {
            c030_01E01AE0(g, func_01E00E30_c030);
        }
        o->h74 = 0;
    }
    if (g->frame < 8) {
        if (o->col[3] < 0x40) {
            o->col[3] += 8;
        }
        if (o->col2[3] < 0x40) {
            o->col2[3] += 8;
        }
    } else if (o->f14 < 15.0f) {
        if (o->col[3] > 16) {
            o->col[3] -= 10;
        }
        if (o->col2[3] > 16) {
            o->col2[3] -= 10;
        }
    } else {
        if (o->col[3] < 0xC0) {
            o->col[3] += 7;
        }
        if (o->link != NULL) {
            if (o->col2[3] < 0xC0) {
                o->col2[3] += 7;
            }
        }
    }
    return 0;
}

/* shape c030:01E01110, 98 insns, 1 copy (C030_CARD_EAREY_1): sets up 22 models (0..10 and 256..266): random speed 1..5, frame 5..12, turn 256..6399 and
   tilt -1024..1023; the current model gets its flag set if it has one; each model present takes its position and turn */

typedef struct {
    f32 pos[8];
    f32 rot[2];
    s32 frame;
    u8 pad2C[8];
    s32 turn;
    s32 tilt;
    u8 pad3C[0x18];
    f32 speed;
    u8 pad58[0x18];
} Ent_c030_01E01110;

typedef struct {
    u8 pad0[0x22B0];
    Ent_c030_01E01110 ents[22];
} Ctx_c030_01E01110;

static void func_01E01110_c030(Ctx_c030_01E01110 *ctx) {
    extern s32 func_001F5380();
    extern s32 func_001F5AF0(s32);
    extern f32 func_001F5970(s32, s32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6210(s32, void *);
    s16 i;
    Ent_c030_01E01110 *e;
    s32 id;

    func_001F5380(ctx);
    for (i = 0; i < 0x16; i++) {
        id = i;
        if (id > 10) {
            id += 0xF5;
        }
        e = &ctx->ents[i];
        e->speed = (func_0019A5C8() % 26 + 9) / 6;
        e->frame = func_0019A5C8() % 8 + 5;
        e->turn = func_0019A5C8() % 6144 + 0x100;
        e->tilt = func_0019A5C8() % 0x800 - 0x400;
        if (id == func_001F5380()) {
            if (func_001F5AF0(id) != 0) {
                func_001F5970(id, 1);
            }
        }
        if (func_001F5EC0(id) != 0) {
            func_001F5F90(id, e->pos);
            func_001F6210(id, e->rot);
        }
    }
}

/* shape c030:01E012A0, 155 insns: c030's camera step for one view (id, or id + 245 past 10): when that view is the active
   one and is live, from scene time 15 it lowers the view's height by 4 (not below 0) and slides its depth by a 24th of
   the camera speed (backwards for ids under 11); from time 28 it eases the view's three offsets down by 0.02 to 0; from
   time 10 it turns the view by 0x1000; then the view is committed */

typedef struct {
    u8 pad0[0x2E4];
    s16 time;
} Ctx_c030_01E012A0;

static s32 func_01E012A0_c030(Ctx_c030_01E012A0 *g, s32 unused, s32 id) {
    extern s32 func_001F5380(void);
    extern s32 func_001F5EC0(s32);
    extern void func_00107450(s32, s32, f32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5F00(s32, void *);
    extern void func_001F5D70(s32, void *);
    extern void func_001F5D10(s32, void *);
    extern void func_001F6210(s32, void *);
    extern void func_001F60D0(s32, void *);
    extern void func_001F5AF0(s32);
    f32 v[4];
    f32 w[4];
    s32 r[4];
    s32 k;

    k = id;
    if (id > 10) {
        k = id + 245;
    }
    if (k != func_001F5380()) {
        return 0;
    }
    if (func_001F5EC0(k)) {
        if (g->time > 14) {
            func_00107450(k, 0, 0.08f);
            func_001F5F90(k, v);
            v[1] -= 4.0f;
            if (v[1] < 0.0f) {
                v[1] = 0.0f;
            }
            if (id < 11) {
                v[2] += -func_001F5860(func_001F5380()) / 24.0f;
            } else {
                v[2] += func_001F5860(func_001F5380()) / 24.0f;
            }
            func_001F5F00(k, v);
        }
        if (g->time >= 28) {
            func_001F5D70(k, w);
            if (!(w[0] <= 0.0f)) {
                w[0] -= 0.02f;
            } else {
                w[0] = 0.0f;
            }
            if (!(w[1] <= 0.0f)) {
                w[1] -= 0.02f;
            } else {
                w[1] = 0.0f;
            }
            if (!(w[2] <= 0.0f)) {
                w[2] -= 0.02f;
            } else {
                w[2] = 0.0f;
            }
            func_001F5D10(k, w);
        }
        if (g->time > 9) {
            func_001F6210(k, r);
            r[1] += 0x1000;
            func_001F60D0(k, r);
        }
    }
    func_001F5AF0(k);
    return 0;
}

/* shape c030:01E01510 (c030), 233 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, sets the step
   function, builds a 91-entry cosine table, sets the timer to 38 and loads texture 15; otherwise it runs the scene
   step and, once started, every live slot's update, then lights (four scale settings by kind) and draws each toward
   the camera target; keeps the 22 units stepping (timer >= 4) and, late, the non-player models' checks; counts the
   timer down (8 when it ends) */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x28];
    void (*draw)(void *, void *, void *, s32);
    void (*update)(void *, void *);
    u8 pad60[8];
    s16 live;
    u8 pad6A[6];
    s16 kind;
    u8 pad72[0xA];
} Slot_c030_01E01510;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x50];
    s32 tex[20];
    u8 lightE0[0x10];
    s32 timer;
    u8 padF4[8];
    s32 ot;
    u8 pad100[4];
    void *fn;
    u8 pad108[0x50];
    f32 sin[91];
    u8 pad2C4[0x1C];
    s16 mode;
    u8 pad2E2[2];
    s16 h2E4;
    u8 pad2E6[0x4E];
    Slot_c030_01E01510 slot[65];
    u8 unit[22][0x70];
    u8 pad2C50[0x4478 - 0x2C50];
    s32 f4478;
} Scene_c030_01E01510;

static s32 func_01E01510_c030(s32 arg0, s32 arg) {
    Scene_c030_01E01510 *g = (Scene_c030_01E01510 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_01E00080_c030();
    extern void func_01E01110_c030(void *);
    extern void func_01E012A0_c030(void *, void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_001F5EC0(s32);
    extern void func_001F5AF0(s32);
    void (*draw)(void *, void *, void *, s32);
    Vec4f at;
    Vec4f v;
    u8 buf[0x90];
    s32 k;
    s32 n;
    s32 i;
    s32 id;

    n = 0;
    g->ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0x2DA0);
        g->fn = func_01E00080_c030;
        for (k = 0; k < 91; k++) {
            g->sin[k] = func_001A6A88(3.1415927f * k / 180.0f);
        }
        g->mode = arg;
        g->timer = 0x26;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        func_01E01110_c030(g);
        return 0;
    }
    func_01E00080_c030(g, 0);
    if (g->h2E4 > 0) {
        for (i = 0; i < 65; i++) {
            if (g->slot[i].live != 0) {
                if (g->slot[i].update != NULL) {
                    g->slot[i].update(g, &g->slot[i]);
                }
            }
        }
        func_001F5BD0(func_001F5380(), &v);
        at.x = v.x;
        at.y = v.y;
        at.z = v.z;
        for (i = 0; i < 65; i++) {
            if (g->slot[i].live != 0) {
                n++;
                func_0020EB40(g->m40);
                if (g->slot[i].kind == 0) {
                    func_00106DD0(g->lightE0, 1.6f, 4.0f, 1.6f);
                }
                if (g->slot[i].kind == 1) {
                    func_00106DD0(g->lightE0, 1.2f, 8.0f, 1.2f);
                }
                if (g->slot[i].kind == 2) {
                    func_00106DD0(g->lightE0, 1.0f, 11.0f, 1.0f);
                }
                if (g->slot[i].kind == 3) {
                    func_00106DD0(g->lightE0, 1.6f, 1.0f, 1.6f);
                }
                func_0020C940(g, g->lightE0, &g->slot[i].pos, &at);
                func_0020BC00(g->m40, g);
                draw = g->slot[i].draw;
                if (draw != NULL) {
                    draw(g, &g->slot[i], buf, 0);
                    draw(g, &g->slot[i], buf, 1);
                }
            }
        }
    }
    if (g->h2E4 >= 0) {
        if (g->timer > 3) {
            for (i = 0; i < 22; i++) {
                func_01E012A0_c030(g, g->unit[i], i);
            }
        }
        if (g->timer < 10) {
            for (i = 0; i < 22; i++) {
                id = i;
                if (i > 10) {
                    id = i + 245;
                }
                if (func_001F5380() != id && g->f4478 < 10) {
                    func_001F5EC0(id);
                    func_001F5AF0(id);
                }
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape c030:01E018C0, 133 insns: c030 trail link spawner (c560:01E01C50 family, 65 slots of 0x7C at ctx+0x334): first free slot (marked slot+1), both colours and alpha from the context, its vector, sizes as shorts, height 18 above, both capped at 50, chained after the context's last piece and becomes it; draws with c030:01E02170 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E018C0;

typedef struct Ent_c030_01E018C0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E018C0 *prev;
    struct Ent_c030_01E018C0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E018C0 col0;
    Col_c030_01E018C0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E018C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E018C0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E018C0 ent[65];
} Ctx_c030_01E018C0;

static void func_01E018C0_c030(Ctx_c030_01E018C0 *g, s32 arg) {
    extern void c030_01E02170(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E018C0 *e = NULL;
    Ent_c030_01E018C0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        e->f70 = g->f2D4;
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E02170;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

/* shape c030:01E01AE0, 134 insns: c030:01E018C0 with f70 copied after the caps and the c030:01E01D00 draw callback */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E01AE0;

typedef struct Ent_c030_01E01AE0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E01AE0 *prev;
    struct Ent_c030_01E01AE0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E01AE0 col0;
    Col_c030_01E01AE0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E01AE0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E01AE0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E01AE0 ent[65];
} Ctx_c030_01E01AE0;

static void func_01E01AE0_c030(Ctx_c030_01E01AE0 *g, s32 arg) {
    extern void c030_01E01D00(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E01AE0 *e = NULL;
    Ent_c030_01E01AE0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->f70 = g->f2D4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E01D00;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

/* shape c030:01E01D00 (C030PAINT_RAIN4), 281 insns, 1 copy: c030:01E02170's ring segments in four steps (the scene's
   step table at 0x2F2) and 35 wide, with the corner colours from its own colour: the outer one's alpha from the
   parent's inner colour (or its own), the inner one with its inner alpha; heights follow the parent and itself */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E01D00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c030_01E01D00;

typedef struct {
    u8 pad0[0x10];
    Rgbaq_c030_01E01D00 c10;
    u8 pad18[0x10];
    Rgbaq_c030_01E01D00 c28;
    u8 pad30[0x10];
    Rgbaq_c030_01E01D00 c40;
    u8 pad48[0x10];
    Rgbaq_c030_01E01D00 c58;
} Pkt_c030_01E01D00;

typedef struct Fx_c030_01E01D00 {
    Vec4f q[4];
    u8 pad40[0x10];
    struct Fx_c030_01E01D00 *parent;
    u8 pad54[0xC];
    Col_c030_01E01D00 col;
    Col_c030_01E01D00 col2;
    u8 pad68[2];
    s16 hA;
    s16 hC;
    u8 pad6E[4];
    s16 ang;
} Fx_c030_01E01D00;

typedef struct {
    u8 pad0[0x40];
    f32 m40[16];
    u8 pad80[0x4C];
    s32 tex;
    u8 padD0[0x2C];
    s32 ot;
    u8 pad100[0x48];
    f32 depth;
    u8 pad14C[0xC];
    u8 sin[0x2F2 - 0x158];
    s16 step[4];
} Scene_c030_01E01D00;

static void func_01E01D00_c030(Scene_c030_01E01D00 *g, Fx_c030_01E01D00 *o, Pkt_c030_01E01D00 *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c030_01E01D00 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 rm[4];
    Col_c030_01E01D00 c;
    s32 i;
    Fx_c030_01E01D00 *p;
    s16 a;
    s16 t;

    p = o->parent;
    a = 0;
    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        func_00109270(pk, 0, 0);
        func_00108500(pk, rm, 1);
        func_00208700(pk, g->tex, 1);
    } else {
        for (i = 0; i < 4; i++) {
            if (p != NULL) {
                t = a + p->ang;
                q[0].x = p->hC * func_00108030(g->sin, t, 1);
                q[0].z = p->hC * func_00108030(g->sin, t, 0);
                t = a + p->ang + 35;
                q[1].x = p->hC * func_00108030(g->sin, t, 1);
                q[1].z = p->hC * func_00108030(g->sin, t, 0);
                o->q[0].y = p->q[1].y;
                q[1].y = q[0].y = p->q[1].y;
            } else {
                t = a;
                q[0].x = o->hA * func_00108030(g->sin, t + o->ang, 1);
                q[0].z = o->hA * func_00108030(g->sin, t + o->ang, 0);
                q[1].x = o->hA * func_00108030(g->sin, t + o->ang + 35, 1);
                q[1].z = o->hA * func_00108030(g->sin, t + o->ang + 35, 0);
            }
            t = a + o->ang;
            q[2].x = o->hC * func_00108030(g->sin, t, 1);
            q[2].z = o->hC * func_00108030(g->sin, t, 0);
            t = a + o->ang + 35;
            q[3].x = o->hC * func_00108030(g->sin, t, 1);
            q[3].z = o->hC * func_00108030(g->sin, t, 0);
            q[3].y = q[2].y = o->q[1].y;
            if (p == NULL) {
                c.a = o->col.a;
            } else {
                c.a = p->col2.a;
            }
            c.r = o->col.r;
            c.g = o->col.g;
            c.b = o->col.b;
            pk->c10 = func_00107740(&c);
            pk->c28 = func_00107740(&c);
            c.a = o->col2.a;
            pk->c40 = func_00107740(&c);
            pk->c58 = func_00107740(&c);
            if (func_00205630(q, 0x70000000, g->m40, pk, &g->depth) != 0) {
                func_002075F0(pk, g->ot, (u32)g->depth);
            }
            a += g->step[i];
        }
    }
}

/* shape c030:01E02170 (C030PAINT_RAIN5), 279 insns, 1 copy: c056:01E02790's ring segments without the material's
   colours: mode 0 only binds the scene texture; otherwise (frame 0x9C) for each of three segments (25 apart) the outer
   edge follows the parent's ring (its angle, radius 0x6C, height) or its own (radius 0x6A, one angle), the inner edge
   its own ring, both colours go through the scene's slot colour, the heights bob 30 + 30 sin(y - 180), and the segment
   is sent at the scene depth */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E02170;

typedef struct Fx_c030_01E02170 {
    Vec4f q[4];
    u8 pad40[0x10];
    struct Fx_c030_01E02170 *parent;
    u8 pad54[0xC];
    Col_c030_01E02170 col;
    Col_c030_01E02170 col2;
    u8 pad68[2];
    s16 hA;
    s16 hC;
    u8 pad6E[4];
    s16 ang;
} Fx_c030_01E02170;

typedef struct {
    u8 pad0[0x40];
    f32 m40[16];
    u8 pad80[0x4C];
    s32 tex;
    u8 padD0[0x2C];
    s32 ot;
    u8 pad100[0x48];
    f32 depth;
    u8 pad14C[0xC];
    u8 sin[0x2FC - 0x158];
    Col_c030_01E02170 col[3];
} Scene_c030_01E02170;

static void func_01E02170_c030(Scene_c030_01E02170 *g, Fx_c030_01E02170 *o, void *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 rm[4];
    s32 i;
    Fx_c030_01E02170 *p;
    s16 a;
    s16 t;

    p = o->parent;
    a = 0;
    if (mode == 0) {
        func_00109270(pk, 0, 0);
        func_00208700(pk, g->tex, 1);
    } else {
    func_00106080(rm, 0x9C, 0, rm);
    func_00108500(pk, rm, 1);
    for (i = 0; i < 3; i++) {
        if (p != NULL) {
            t = a + p->ang;
            q[0].x = p->hC * func_00108030(g->sin, t, 1);
            q[0].z = p->hC * func_00108030(g->sin, t, 0);
            t = a + p->ang + 20;
            q[1].x = p->hC * func_00108030(g->sin, t, 1);
            q[1].z = p->hC * func_00108030(g->sin, t, 0);
            o->q[0].y = p->q[1].y;
        } else {
            t = a;
            q[0].x = o->hA * func_00108030(g->sin, t + o->ang, 1);
            q[0].z = o->hA * func_00108030(g->sin, t + o->ang, 0);
            q[1].x = o->hA * func_00108030(g->sin, t + o->ang, 1);
            q[1].z = o->hA * func_00108030(g->sin, t + o->ang, 0);
        }
        t = a + o->ang;
        q[2].x = o->hC * func_00108030(g->sin, t, 1);
        q[2].z = o->hC * func_00108030(g->sin, t, 0);
        t = a + o->ang + 20;
        q[3].x = o->hC * func_00108030(g->sin, t, 1);
        q[3].z = o->hC * func_00108030(g->sin, t, 0);
        if (p == NULL) {
            g->col[i].a = o->col.a;
        } else {
            g->col[i].a = p->col2.a;
        }
        func_00107790(pk, &g->col[i], 1);
        g->col[i].a = o->col2.a;
        func_00107790(pk, &g->col[i], 2);
        q[0].y = 30.0f + 30.0f * func_00108030(g->sin, (s32)(o->q[0].y - 180.0f), 1);
        q[1].y = q[0].y;
        q[2].y = 30.0f + 30.0f * func_00108030(g->sin, (s16)(o->q[1].y - 180.0f), 1);
        q[3].y = q[2].y;
        if (func_00205630(q, 0x70000000, g->m40, pk, &g->depth) != 0) {
            func_002075F0(pk, g->ot, (u32)g->depth);
        }
        a += 25;
    }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E02600_c030);
