#include "common.h"

/* shape b027:01E00080, 544 insns: B027_W_S, the effect scene's step (b522:01E01D30 form): colour 0x80,0,0,0, counts
   the frame (0x3932) and turns the scene (0x3914) to the camera's heading; frames 11/40 and 29/49 twenty 0x1E00900
   10 under joints 0x3916 / 0x3918, frames 63..98 three 0x1E00B20; from frame 63 (level 16 on) the spin follows joints
   0x391A / 0x391C; on fixed frames from 119 a burst of 0x1E00DB0 / 0x1E01310 / 0x1E014A0 / 0x1E016D0 on either;
   frame 72 two 0x1E01600, frame 94 0x1E017A0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x38D0 - 0x260];
    s32 level;
    u8 col[4];
    u8 pad38D8[0x3914 - 0x38D8];
    s16 yaw;
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 pad391E[0x3928 - 0x391E];
    s16 spin;
    u8 pad392A[4];
    s16 side;
    u8 pad3930[2];
    s16 t;
} Scene_b027_01E00080;

static void func_01E00080_b027(Scene_b027_01E00080 *g) {
    extern void b027_01E00900(void);
    extern void b027_01E00B20(void);
    extern void b027_01E00DB0(void);
    extern void b027_01E01310(void);
    extern void b027_01E014A0(void);
    extern void b027_01E01600(void);
    extern void b027_01E016D0(void);
    extern void b027_01E017A0(void);
    extern f32 b027_01E01A30(s32);
    extern void b027_01E03E50(Scene_b027_01E00080 *, void (*)(void), s32);
    extern s32 func_001A22C0(f32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    g->yaw = func_001A22C0(b027_01E01A30(func_001F53A0()) / 180.0f);
    g->yaw -= 180;
    func_001F5620(func_001F53A0(), g->ja, &v);
    if (g->t == 11 || g->t == 40) {
        for (i = 0; i < 20; i++) {
            g->side = 0;
            g->pos.w = 0.0f;
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y - 10.0f;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E00900, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->jb, &v);
    if (g->t == 29 || g->t == 49) {
        for (i = 0; i < 20; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y - 10.0f;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E00900, 0);
        }
    }
    if (g->t > 62 && g->t < 99) {
        for (i = 0; i < 3; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y - 10.0f;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E00B20, 0);
        }
    }
    if (g->t > 62 && g->level > 15) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
        }
        func_001F5620(func_001F53A0(), g->jd, &v);
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
        }
    }
    if (g->t > 67 && g->level > 15) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        if (g->t > 62) {
            for (i = 0; i < 1; i++) {
                g->spin = func_0019A5C8() % 360;
                g->pos.x = v.x;
                g->pos.y = v.y;
                g->pos.z = v.z;
                g->side = 2;
            }
        }
        func_001F5620(func_001F53A0(), g->jd, &v);
        if (g->t > 62) {
            for (i = 0; i < 1; i++) {
                g->spin = func_0019A5C8() % 360;
                g->pos.x = v.x;
                g->pos.y = v.y;
                g->pos.z = v.z;
                g->side = 3;
            }
        }
    }
    if (g->t == 119 || g->t == 125 || g->t == 131 || g->t == 136 || g->t == 141 || g->t == 146 || g->t == 151 || g->t == 156 || g->t == 162 || g->t == 168 || g->t == 174) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        for (i = 0; i < 5; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = func_0019A5C8() % 80;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E00DB0, 0);
        }
        for (i = 0; i < 4; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = func_0019A5C8() % 80;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E01310, 0);
        }
        for (i = 0; i < 10; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = 0;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E014A0, 0);
        }
        b027_01E03E50(g, b027_01E016D0, 0);
    }
    func_001F5620(func_001F53A0(), g->jd, &v);
    if (g->t == 122 || g->t == 128 || g->t == 133 || g->t == 138 || g->t == 143 || g->t == 149 || g->t == 154 || g->t == 159 || g->t == 165 || g->t == 171) {
        for (i = 0; i < 5; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = func_0019A5C8() % 80;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E00DB0, 0);
        }
        for (i = 0; i < 4; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = func_0019A5C8() % 80;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E01310, 0);
        }
        for (i = 0; i < 10; i++) {
            g->spin = func_0019A5C8() % 360;
            g->side = 0;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b027_01E03E50(g, b027_01E014A0, 0);
        }
        b027_01E03E50(g, b027_01E016D0, 0);
    }
    if (g->t == 72) {
        g->side = 0;
        b027_01E03E50(g, b027_01E01600, 0);
        g->side = 1;
        b027_01E03E50(g, b027_01E01600, 0);
    }
    if (g->t == 94) {
        b027_01E03E50(g, b027_01E017A0, 0);
    }
}

/* shape b027:01E00900, 134 insns: b194:01E00C60 with colour 0x3F/0x38/0x3F and the sine table at g+0x3A34 */

typedef struct {
    u8 pad0[0x3A34];
    u8 trig[1];
} World_b027_01E00900;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b027_01E00900;

static s32 func_01E00900_b027(World_b027_01E00900 *w, Wisp_b027_01E00900 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x38, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
        o->a30 = func_0019A5C8() % 30 - 15;
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
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b027:01E00B20, 158 insns: b019:01E01F60 family wisp (0x3F, 0x38, 0x3F; table at ctx+0x3A34): angle random, or the scene's facing +-60 after scene count 130; f30 -30..29; alpha up by 9 to 0x60 for 10 ticks then down by 10; size counter grows each tick, frame every third tick to 7; swings 20 on x/z and rises 0..4 per tick */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3914];
    s16 facing;
    u8 pad3916[0x3932 - 0x3916];
    s16 count;
    u8 pad3934[0x3A34 - 0x3934];
    u8 tab[1];
} Mgr_b027_01E00B20;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b027_01E00B20;

static s32 func_01E00B20_b027(Mgr_b027_01E00B20 *m, Fx_b027_01E00B20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s32 t;

    func_001076F0(o->col, 0x3F, 0x38, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        if (m->count < 130) {
            o->f3A = func_0019A5C8() % 360;
        } else {
            o->f3A = m->facing + (func_0019A5C8() % 120 - 60);
        }
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 60 - 30;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->f38++;
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 20.0f * func_00108030(m->tab, o->f3A, 0);
    t = o->tick;
    if (t != 0) {
        if ((s16)t < 5) {
            o->y += (s16)(func_0019A5C8() % 5);
        } else {
            o->y += (s16)(func_0019A5C8() % 5);
        }
    }
    o->z = o->z + 20.0f * func_00108030(m->tab, o->f3A, 1);
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E00DA0_b027(void) {
    return 0;
}

/* shape b027:01E00DB0, 117 insns: a white drifting mote: frame 3..7, random sub-frame 0..3 and angles; full alpha for 10 frames,
   then down by 10 until it ends; while the scene flag is set it drifts 16 along its angle and bobs 16 by its second angle */

typedef struct {
    u8 pad0[0x3932];
    s16 flag;
    u8 pad3934[0x100];
    u8 sin[1];
} Game_b027_01E00DB0;

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
} Obj_b027_01E00DB0;

static s32 func_01E00DB0_b027(Game_b027_01E00DB0 *g, Obj_b027_01E00DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 5 + 3;
        o->sub = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->bob = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 0xA) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (g->flag != 0) {
        o->h8 = func_001A22C0(o->h8 + 16.0f * func_00108030(g->sin, o->ang, 0));
        o->hA = func_001A22C0(o->hA + 16.0f * func_00108030(g->sin, o->bob, 1));
        o->hC = func_001A22C0(o->hC + 16.0f * func_00108030(g->sin, o->ang, 1));
    }
    o->t++;
    return 0;
}

/* shape b027:01E00F90, 78 insns: a pink flame (size 17 growing to 25) at a random angle, or within 60 degrees of the scene angle once its value reaches 130: in by 48 up to 0x60 for 2 ticks, then out by 7 and ends */

typedef struct {
    u8 pad0[0x10];
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
} Glow_b027_01E00F90;

typedef struct {
    u8 pad[0x3914];
    s16 ang;
    u8 pad3916[0x1C];
    s16 val;
} Game_b027_01E00F90;

static s32 func_01E00F90_b027(Game_b027_01E00F90 *g, Glow_b027_01E00F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x50, 0x5F);
    if (o->mode == 1) {
        o->f38 = 17;
        if (g->val < 130) {
            o->ang = func_0019A5C8() % 360;
        } else {
            o->ang = g->ang + (func_0019A5C8() % 120 - 60);
        }
        o->kind = 0;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0x2A) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 25) {
        o->f38++;
    }
    return 0;
}

/* shape b027:01E010D0, 78 insns: an olive flame (size 15 shrinking to 0) at a random angle, or within 60 degrees of the scene angle once its value reaches 130: in by 15 up to 0x60 for 8 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x10];
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
} Glow_b027_01E010D0;

typedef struct {
    u8 pad[0x3914];
    s16 ang;
    u8 pad3916[0x1C];
    s16 val;
} Game_b027_01E010D0;

static s32 func_01E010D0_b027(Game_b027_01E010D0 *g, Glow_b027_01E010D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x40, 0x40, 0x1F);
    if (o->mode == 1) {
        o->f38 = 15;
        if (g->val < 130) {
            o->ang = func_0019A5C8() % 360;
        } else {
            o->ang = g->ang + (func_0019A5C8() % 120 - 60);
        }
        o->kind = 0;
        o->col[3] = 0;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 15;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 != 0) {
        o->f38--;
    }
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01210_b027(void) {
    return 0;
}

/* shape b027:01E01220, 58 insns: a grey flash (b533:01E022F0 shape at 0x28): both alphas jump to 0xA0, then fall by
   0x2C a frame and the effect ends below 0x2E; colours stay 0x40 grey */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 lit;
    u8 pad32[4];
    s16 state;
} Obj_b027_01E01220;

static s32 func_01E01220_b027(void *arg0, Obj_b027_01E01220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->lit = 0;
        o->state = 2;
    }
    if (o->lit == 0) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] = 0xA0;
        } else {
            o->lit = 1;
        }
        if (o->c1[3] < 0xA0) {
            o->c1[3] = 0xA0;
        }
    } else {
        if (o->c0[3] > 0x2D) {
            o->c0[3] -= 0x2C;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x2D) {
            o->c1[3] -= 0x2C;
        }
    }
    func_001076F0(o->c0, 0x40, 0x40, 0x40);
    func_001076F0(o->c1, 0x40, 0x40, 0x40);
    return 0;
}

/* shape b027:01E01310, 99 insns: b233:01E02860 family: a white spark (size -10 growing a random 4..6 a tick, random frame 0..6) tipped +-0x2000 and turned at random: in by 64 up to 0x80 for 2 ticks; past size 20 out by 19, and out by 15 once the scene state is under 10; ends */

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
} Glow_b027_01E01310;

typedef struct {
    u8 pad[0x38D0];
    s32 state;
} Game_b027_01E01310;

static s32 func_01E01310_b027(Game_b027_01E01310 *g, Glow_b027_01E01310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = -10;
        o->w10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = func_0019A5C8() % 65535;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = 20;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->f38 > 20) {
            if (o->col[3] > 0x14) {
                o->col[3] -= 0x13;
            } else {
                o->mode = 0;
            }
        }
        if (g->state < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->tick != 0) {
        o->f38 += o->h8;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E014A0, 88 insns: on start 0x38 = 20, 0x34 = 1, random rotation 0x18, colour 0x80 grey, random 0x3A, speed 130..147 (0xE), 0x8 0..9, hold 3..9 (0x6); alpha grows by 0x40 (up to 0x80) during the hold,
   then fades by 10 and stops; 0x30 grows by the speed after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b027_01E014A0;

static s32 func_01E014A0_b027(s32 arg0, Fx_b027_01E014A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->f34 = 1;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 18 + 0x82;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E01600, 49 insns: a blue two-colour glow of size 120 at alpha 0x60 for 175 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
} Glow_b027_01E01600;

static s32 func_01E01600_b027(s32 arg0, Glow_b027_01E01600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        func_001076F0(o->col2, 0x20, 0x20, 0x80);
        o->h6 = 6;
        o->col[3] = 0;
        o->kind = 1;
        o->f38 = 120;
        o->mode = 2;
    }
    if (o->tick < 175) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E016D0, 52 insns: on start 0x38 = 0x140, colour 0xC0 grey and second colour (0x80, 0x80, 0x20) with
   alpha 0, random 0x3A; alpha 0xA0 on the first tick, then fades by 0x30 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b027_01E016D0;

static s32 func_01E016D0_b027(s32 arg0, Fx_b027_01E016D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x140;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x80, 0x80, 0x20);
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick <= 0) {
        o->col[3] = 0xA0;
    } else if (o->col[3] > 0x32) {
        o->col[3] -= 0x30;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E017A0, 109 insns: a screen tint: builds a grey (0x80) full-screen textured sprite (0x6BF8,0x71F8 -
   0x93F8,0x8DF8, uv 0..0.625 x 0..0.875) in the effect's alpha on the stack and sends it; (the same uv for both kinds
   0x30); the alpha grows by 12 (below 0x30) for 90 ticks, then fades by 12 and stops */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b027_01E017A0;

typedef struct {
    f32 s, t;
    Xyz_b027_01E017A0 p;
} Tv_b027_01E017A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b027_01E017A0 v[2];
    u8 tail[0x20];
} Tex_b027_01E017A0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b027_01E017A0;

static s32 func_01E017A0_b027(s32 arg0, Fx_b027_01E017A0 *o) {
    Tex_b027_01E017A0 pk __attribute__((aligned(8)));

    ((Tex_b027_01E017A0 *)(s32)&pk)->count = 0x26;
    ((Tex_b027_01E017A0 *)(s32)&pk)->tag = 5;
    ((Tex_b027_01E017A0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b027_01E017A0 *)(s32)&pk)->pad = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    if (o->kind == 0) {
        pk.v[0].s = 0.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 0.625f;
        pk.v[1].t = 0.875f;
    } else {
        pk.v[0].s = 0.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 0.625f;
        pk.v[1].t = 0.875f;
    }
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->tick < 0x5A) {
        if (o->col[3] < 0x30) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 0xD) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E01960_b027(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

/* shape b004:01E00C10, 9 insns: asks func_001F6160 for a pair of ints and returns the second as a float */

static f32 func_01E01A30_b027(s32 arg0) {
    extern void func_001F6160(s32, s32 *);
    s32 v[4];

    func_001F6160(arg0, v);
    return v[1];
}

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E01A60_b027(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

/* shape b027:01E02300, 162 insns, 8 copies: a fan of 18 quads (centre at the origin, outer edge on a circle of
   radius data->radius, 20 angle units per step) sent through the caller's packet; same family as b016:01E01190 */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02300;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b027_01E02300;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 radius;
    s16 step;
} Data_b027_01E02300;

static void func_01E02300_b027(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b027_01E02300 quad[4];
    Vec_b027_01E02300 pos;
    Vec_b027_01E02300 scale;
    f32 matrix[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 j;
    s32 a;
    f32 fx;
    f32 fy;
    f32 fz;

    j = 0;
    func_00107990(pkt, data->mode0, 1);
    func_00107990(pkt, data->mode1, 2);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = data->dx;
    fy = data->dy;
    fz = data->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = data->x + fx;
    pos.y = data->y + fy;
    pos.z = data->z + fz;
    func_00108EF0(matrix, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        a = data->step + j;
        quad[2].x = data->radius * func_00108030(obj->table, a, 1);
        quad[2].z = data->radius * func_00108030(obj->table, a, 0);
        a = j + (data->step + 20);
        quad[3].x = data->radius * func_00108030(obj->table, a, 1);
        quad[3].z = data->radius * func_00108030(obj->table, a, 0);
        if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
            func_00109380(pkt, 1);
            func_002075F0(pkt, obj->texture, 0);
        }
        j += 20;
    }
}

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02590;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b027_01E02590;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b027_01E02590;

static void func_01E02590_b027(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b027_01E02590 quad[4];
    Vec_b027_01E02590 pos;
    Vec_b027_01E02590 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 0);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 2);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 40;
    }
}

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

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E02890_b027(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E01A60_b027((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E02C10_b027(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b027:01E03050, 346 insns: KTPOINT_RAIN_6, b257:01E01270 with 2 quads per sub-step and a real depth: a textured curved beam along the module's spline (shape b018:01E00EE0, here at
   b257:01E00E30) through the given points (b018:01E01320 family): 4 sub-steps per segment, each drawn as a
   4-quad cross (two tilted by half the width), gouraud between the two colours, alpha fading along the beam,
   depth far. The spline must be in the same file and static: the original keeps $a0/$a1 across each call. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b257_01E01270_b027;

typedef struct {
    u8 r, g, b, a;
} Col_b257_01E01270_b027;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b257_01E01270_b027;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b257_01E01270_b027 c;
        u64 st;
        Xyz_b257_01E01270_b027 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b257_01E01270_b027;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b257_01E01270_b027;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b257_01E01270_b027 col0;
    Col_b257_01E01270_b027 col1;
    u8 pad30[8];
    s16 width;
} Beam_b257_01E01270_b027;

static void func_01E03050_b027(Ctx_b257_01E01270_b027 *c, Beam_b257_01E01270_b027 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b257_01E01270_b027 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b257_01E01270_b027 pkt __attribute__((aligned(8)));
    Col_b257_01E01270_b027 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b257_01E01270_b027 *p;
    s32 target;
    f32 t;
    f32 w;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E02C10_b027(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E02C10_b027(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E02C10_b027(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E02C10_b027(ctrl, 0, t);
                ab[1] = r2;
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            for (k = 0; k < 2; k++) {
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
                if (k == 0) {
                    q[1].y += w;
                    q[3].y += w;
                } else if (k == 1) {
                    q[1].y -= w;
                    q[3].y -= w;
                } else if (k == 2) {
                    q[1].x += w;
                    q[3].x += w;
                    q[1].z += w / 2.0f;
                    q[3].z += w / 2.0f;
                } else if (k == 3) {
                    q[1].x -= w;
                    q[3].x -= w;
                    q[1].z -= w / 2.0f;
                    q[3].z -= w / 2.0f;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    func_002075F0(p, target, func_001A23B0(depth));
                }
            }
        }
    }
}

/* shape b027:01E035C0 (b027), 547 insns, 1 copy: b027 scene manager (b018:01E02E00 form): with a scene id (>= 0) it
   clears the scene, keeps the id, sets the 215-frame countdown, takes six joint handles, looks up texture 4:15 and
   5:0 and fills a 256-byte random table (-5..4); otherwise at frame 72 fills both ten-point trails from joints 4 and
   5, shifts them, runs the script, steps the 210 slots, draws every live slot (0x1E01220 as a two-colour fill in
   place) and returns 1 / 4 / 6 / 2 at frames 110 / 185 / 121..169 / 175, 8 once the countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x1E];
    s32 (*fn)();
    u8 c0[4];
    u8 c1[4];
    s16 tr;
    u8 pad32[2];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b027_01E035C0;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rm;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x1E4];
    s32 tex2BC;
    Slot_b027_01E035C0 slot[210];
    u8 pad3740[0x30];
    Vec4f tr[2][10];
    s32 tex[8];
    s32 count;
    u8 pad38D4[8];
    s32 ot;
    u8 pad38E0[0x36];
    s16 j[6];
    u8 pad3922[0xE];
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 crd[0x16C];
} Scene_b027_01E035C0;

static s32 func_01E035C0_b027(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_01E00080_b027();
    extern void func_01E02590_b027();
    extern void func_01E02300_b027();
    extern void func_01E02890_b027();
    extern void b027_01E03F70();
    extern void b027_01E04110();
    Scene_b027_01E035C0 *g = (Scene_b027_01E035C0 *)arg0;
    s32 m;
    Vec4f c;
    Vec4f rm;
    Vec4f rm2;
    Vec4f rm3;
    Vec4f pa;
    Vec4f pb;
    u8 pk[0x90];
    u8 buf[0x90];
    s32 i;

    m = 0;
    g->ot = (s32)func_00207500();
    g->ot80 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3BA0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0xD7;
        g->j[0] = func_001F5560(func_001F53A0(), 0x12, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x14, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 8, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 7, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xC, 0);
        g->tex2BC = func_00202BF0(4, 15);
        for (i = 0; i < 1; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 10 - 5;
        }
        return 0;
    }
    if (g->frame == 0x48) {
        Vec4f *p = g->tr[0];

        func_001F5620(func_001F53A0(), g->j[4], (s32)&pa);
        for (i = 0; i < 10; i++, p++) {
            p->x = pa.x;
            p->y = pa.y;
            p->z = pa.z;
        }
    }
    if (g->frame == 0x48) {
        Vec4f *p = g->tr[1];

        func_001F5620(func_001F53A0(), g->j[5], (s32)&pb);
        for (i = 0; i < 10; i++, p++) {
            p->x = pb.x;
            p->y = pb.y;
            p->z = pb.z;
        }
    }
    func_01E01960_b027((Vec_b004_01E00B40 *)&g->tr[0][9], 10, g->j[4]);
    func_01E01960_b027((Vec_b004_01E00B40 *)&g->tr[1][9], 10, g->j[5]);
    func_01E00080_b027(g, 0);
    for (i = 0; i < 210; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E00900_b027) {
                func_01E00900_b027((World_b027_01E00900 *)g, (Wisp_b027_01E00900 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E00B20_b027) {
                func_01E00B20_b027((Mgr_b027_01E00B20 *)g, (Fx_b027_01E00B20 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E00DB0_b027) {
                func_01E00DB0_b027((Game_b027_01E00DB0 *)g, (Obj_b027_01E00DB0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E00F90_b027) {
                func_01E00F90_b027((Game_b027_01E00F90 *)g, (Glow_b027_01E00F90 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E010D0_b027) {
                func_01E010D0_b027((Game_b027_01E010D0 *)g, (Glow_b027_01E010D0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01220_b027) {
                func_01E01220_b027(g, (Obj_b027_01E01220 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01310_b027) {
                func_01E01310_b027((Game_b027_01E01310 *)g, (Glow_b027_01E01310 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E014A0_b027) {
                func_01E014A0_b027((s32)g, (Fx_b027_01E014A0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01600_b027) {
                func_01E01600_b027((s32)g, (Glow_b027_01E01600 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E016D0_b027) {
                func_01E016D0_b027((s32)g, (Fx_b027_01E016D0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E017A0_b027) {
                func_01E017A0_b027((s32)g, (Fx_b027_01E017A0 *)&g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    c.z -= 25.0f;
    for (i = 0; i < 210; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E00900_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E00B20_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E00DA0_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E00DB0_b027) {
                b027_01E04110(g, &g->slot[i], buf, 0);
                b027_01E04110(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E00F90_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E010D0_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E01210_b027) {
                b027_01E03F70(g, &g->slot[i], buf, 0);
                b027_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E01220_b027) {
                s32 ot = (s32)func_00207500();
                func_00107990(pk, g->slot[i].c0, 1);
                func_00107990(pk, g->slot[i].c1, 2);
                func_001092E0(pk, 0);
                func_001094F0(pk);
                func_002075F0(pk, ot, 0);
            }
            if (g->slot[i].fn == func_01E01310_b027) {
                g->tex88 = g->tex[0];
                func_00106080(&rm, 0x9B, g->slot[i].h34, NULL);
                g->rm = rm;
                g->hB8 = 1;
                func_01E02590_b027(g, &g->slot[i], buf, 0);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E014A0_b027) {
                g->tex88 = g->tex[0];
                func_00106080(&rm2, 0x14, g->slot[i].h34, NULL);
                g->rm = rm2;
                g->hB8 = 2;
                func_01E02890_b027(g, &g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E01600_b027) {
                g->tex88 = g->tex[0];
                func_00106080(&rm3, 0x14, g->slot[i].h34, NULL);
                g->rm = rm3;
                g->hBE = 0;
                ((s16 *)&g->rm)[0] = 15;
                ((s16 *)&g->rm)[1] = 16;
                ((s16 *)&g->rm)[2] = 15;
                ((s16 *)&g->rm)[3] = 1;
                func_01E03050_b027((Ctx_b257_01E01270_b027 *)g, (Beam_b257_01E01270_b027 *)&g->slot[i],
                                   (Vec_b018_01E00EE0 *)g->tr[g->slot[i].tr]);
            }
            if (g->slot[i].fn == func_01E016D0_b027) {
                func_01E02300_b027(g, &g->slot[i], buf, 0);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x6E) {
        return 1;
    }
    if (g->frame == 0xB9) {
        return 4;
    }
    if (g->frame > 0x78 && g->frame < 0xAA) {
        return 6;
    }
    if (g->frame == 0xAF) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b027:01E03E50, 72 insns: twin of b046:01E03E20: take the first free slot of the 210-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x392E and the two arguments; returns 1 if a
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
} Slot_b027_01E03E50;

typedef struct {
    u8 pad[0x250];
    u8 m[0x70];
    Slot_b027_01E03E50 s[210];
    u8 pad3740[0x194];
    u8 r, g, b, a;
    u8 pad38D8[0x56];
    s16 v;
} Pool_b027_01E03E50;

static s32 func_01E03E50_b027(Pool_b027_01E03E50 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b027_01E03E50 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 210; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 210;
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

/* shape b027:01E03F70, 103 insns: c035:01E013A0 family sprite draw in two passes: with lit 0 it sets the material (texture id 0x99 at frame +0x34, colour, scene texture) and returns; otherwise it places a size x size quad at position + speed/10 with the object's turn */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b027_01E03F70;

typedef struct {
    u8 pad0[0x2bc];
    s32 tex;
} Scene_b027_01E03F70;

static void func_01E03F70_b027(Scene_b027_01E03F70 *g, Fx_b027_01E03F70 *o, void *p, s32 lit) {
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
    if (lit == 0) {
        func_00106080(rm, 0x99, o->h34, rm);
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
}

/* shape b027:01E04110, 113 insns: b004:01E01860 family two-pass sprite draw with depth: pass 0 sets the material (texture id 0x99, alpha test 0x42, scene texture at +0x2BC); pass 1 places a size x size quad at position + speed/10 scaled 0.1, projects it (func_00205630) and sends it at its depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b027_01E04110;

typedef struct {
    u8 pad0[0x2BC];
    s32 tex;
    u8 pad2C0[0x38DC - 0x2C0];
    s32 ot;
} Scene_b027_01E04110;

static void func_01E04110_b027(Scene_b027_01E04110 *g, Fx_b027_01E04110 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    f32 ax, ay, az;

    func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x99, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, g->ot, func_001A23B0(depth[0]));
    }
}
