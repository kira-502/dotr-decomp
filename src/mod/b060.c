#include "common.h"

/* shape b060:01E00080 (B060_W_S), 587 insns, 1 copy (-O3,p): B060_W_S, the effect scene step: colour
   0x80,0,0,0, counts the frame (0x3B5C); joints at frames 113 and 1; pairs of 0x1E009B0 sparks round joints
   0x3B48..0x3B4E on three frames each; frames 117..119 ten 0x1E00BB0, twenty 0x1E00ED0 and six 0x1E00D80 round joint
   0x3B48; frames 133/176/199 ten 0x1E009B0 at joint 0x3B4A */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x3B04 - 0x90];
    u8 col[4];
    u8 pad3B08[0x3B48 - 0x3B08];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 pad3B50[2];
    s16 spin;
    u8 pad3B54[8];
    s16 t;
} Scene_b060_01E00080;

#pragma optimization_level 3

static void func_01E00080_b060(Scene_b060_01E00080 *g) {
    extern void b060_01E009B0(void);
    extern void b060_01E00BB0(void);
    extern void b060_01E00D80(void);
    extern void b060_01E00ED0(void);
    extern void b060_01E01890(Scene_b060_01E00080 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0x71) {
        g->ja = func_001F5560(func_001F53A0(), 0x28, 1);
        g->jb = func_001F5560(func_001F53A0(), 2, 0);
    }
    if (g->t == 1) {
        g->ja = func_001F5560(func_001F53A0(), 0xC, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x21, 0);
        g->jc = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jd = func_001F5560(func_001F53A0(), 2, 0);
    }
    func_001F5620(func_001F53A0(), g->ja, &v);
    if (g->t == 0x46 || g->t == 0x5A || g->t == 0x70) {
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 4 - 2.0f;
            g->pos.y = v.y - 1.0f;
            g->pos.z = v.z + func_0019A5C8() % 4 - 2.0f;
            b060_01E01890(g, b060_01E009B0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->jb, &v);
    if (g->t == 0x3D || g->t == 0x52 || g->t == 0x66) {
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 4 - 2.0f;
            g->pos.y = v.y - 1.0f;
            g->pos.z = v.z + func_0019A5C8() % 4 - 2.0f;
            b060_01E01890(g, b060_01E009B0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->jc, &v);
    if (g->t == 0x3A || g->t == 0x51 || g->t == 0x64) {
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 4 - 2.0f;
            g->pos.y = v.y - 1.0f;
            g->pos.z = v.z + func_0019A5C8() % 4 - 2.0f;
            b060_01E01890(g, b060_01E009B0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->jd, &v);
    if (g->t == 0x44 || g->t == 0x5B || g->t == 0x6C) {
        for (i = 0; i < 2; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 4 - 2.0f;
            g->pos.y = v.y - 1.0f;
            g->pos.z = v.z + func_0019A5C8() % 4 - 2.0f;
            b060_01E01890(g, b060_01E009B0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->ja, &v);
    if (g->t == 0x75 || g->t == 0x76 || g->t == 0x77) {
        for (i = 0; i < 10; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 10 - 5.0f;
            g->pos.y = v.y + func_0019A5C8() % 10 - 5.0f;
            g->pos.z = v.z + func_0019A5C8() % 10 - 5.0f;
            b060_01E01890(g, b060_01E00BB0, 0);
        }
        for (i = 0; i < 20; i++) {
            g->pos.x = v.x + func_0019A5C8() % 10 - 5.0f;
            g->pos.y = v.y + func_0019A5C8() % 10 - 5.0f;
            g->pos.z = v.z + func_0019A5C8() % 10 - 5.0f;
            b060_01E01890(g, b060_01E00ED0, 0);
        }
        for (i = 0; i < 6; i++) {
            g->pos.x = v.x + func_0019A5C8() % 10 - 5.0f;
            g->pos.y = v.y + func_0019A5C8() % 10 - 5.0f;
            g->pos.z = v.z + func_0019A5C8() % 10 - 5.0f;
            b060_01E01890(g, b060_01E00D80, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->jb, &v);
    if (g->t == 0x85 || g->t == 0xB0 || g->t == 0xC7) {
        for (i = 0; i < 10; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x + func_0019A5C8() % 10 - 5.0f;
            g->pos.y = v.y - 5.0f;
            g->pos.z = v.z + func_0019A5C8() % 10 - 5.0f;
            b060_01E01890(g, b060_01E009B0, 0);
        }
    }
}
#pragma optimization_level reset

/* shape b060:01E009B0, 125 insns: b064:01E01A00's drifting spark, grey-purple, tilt -15..14, speeds 6/4/6 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b060_01E009B0;

static s32 func_01E009B0_b060(u8 * g, Spark_b060_01E009B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x2F, 0x20, 0x2F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 0x28) {
        o->f38 += 5;
    }
    if (o->tick % 3 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 6.0f * func_00108030(g + 0x3B60, o->dir, 0);
    o->fA = o->fA + 4.0f * func_00108030(g + 0x3B60, o->angle, 1);
    o->fC = o->fC + 6.0f * func_00108030(g + 0x3B60, o->dir, 1);
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b060:01E00BB0, 116 insns: dim mote drifting 13 units a frame along two random angles, fading in and out */

typedef struct Mo_b060_01E00BB0 {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c28[4];
    u8 c2C[4];
    s16 ang2;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Mo_b060_01E00BB0;

typedef struct Scn_b060_01E00BB0 {
    u8 pad0[0x3B60];
    u8 table[0x10];
} Scn_b060_01E00BB0;

static s32 func_01E00BB0_b060(Scn_b060_01E00BB0 *w, Mo_b060_01E00BB0 *o) {
    extern s32 func_001076F0();
    func_001076F0(o->c28, 0x10, 0x10, 0x10);
    if (o->state == 1) {
        o->h38 = 7;
        o->ang = func_0019A5C8() % 360;
        o->h34 = func_0019A5C8() % 7;
        o->ang2 = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->age < 2) {
        if (o->c28[3] < 0x60) {
            o->c28[3] += 0x30;
        }
    } else if (o->c28[3] > 5) {
        o->c28[3] -= 4;
    } else {
        o->state = 0;
    }
    o->age++;
    if (o->h38 < 10) {
        o->h38++;
    }
    o->x = (s32)(o->x + 13.0f * func_00108030((s32)w->table, o->ang, 0));
    o->y = (s32)(o->y + 13.0f * func_00108030((s32)w->table, o->ang2, 1));
    o->z = (s32)(o->z + 13.0f * func_00108030((s32)w->table, o->ang, 1));
    return 0;
}

/* shape b060:01E00D80, 84 insns: a dark blue tumbling glow at three random turns, growing a random 2..6 a tick up to 50 and turning 2: in by 48 for 2 ticks; past size 10 out by 9, and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
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
} Glow_b060_01E00D80;

static s32 func_01E00D80_b060(s32 arg0, Glow_b060_01E00D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x20, 0x20, 0x40);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->hE = func_0019A5C8() % 5 + 2;
        o->kind = 0;
        o->f38 = 0;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x30;
    }
    o->tick++;
    if (o->f38 > 10) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->f38 < 50) {
        o->f38 += o->hE;
    }
    o->ang += 2;
    return 0;
}

/* shape b060:01E00ED0, 107 insns: a grey drifting puff (b194:01E015C0 shape): frame 5, random sub-frame 0..3 and angles; alpha up by
   42 for 3 frames, then down by 5 until it ends; drifts 15 along its angle and bobs 15 by its second angle */

typedef struct {
    u8 pad0[0x3B60];
    u8 sin[1];
} Game_b060_01E00ED0;

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
} Obj_b060_01E00ED0;

static s32 func_01E00ED0_b060(Game_b060_01E00ED0 *g, Obj_b060_01E00ED0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 5;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->bob = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 3) {
        o->c0[3] += 0x2A;
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 15.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 15.0f * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + 15.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b060:01E01080, 103 insns: colour (0x8F, 0x50, 0x5F); on start 0x38 = 17 and a heading 0x3A: random, or (game step 0x3B5C from
   0x82) -60..59 / 120..239 depending on func_001F53A0 below 10; alpha grows by 0x30 (below 0x60) for 2 ticks, then
   fades by 7 and stops; 0x38 counts up to 0x19 */

typedef struct {
    u8 pad0[0x3B5C];
    s16 step;
} Game_b060_01E01080;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b060_01E01080;

static s32 func_01E01080_b060(Game_b060_01E01080 *g, Fx_b060_01E01080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x8F, 0x50, 0x5F);
    if (o->mode == 1) {
        o->f38 = 17;
        if (func_001F53A0() < 10) {
            if (g->step < 0x82) {
                o->heading = func_0019A5C8() % 360;
            } else {
                o->heading = func_0019A5C8() % 120 - 60;
            }
        } else if (g->step < 0x82) {
            o->heading = func_0019A5C8() % 360;
        } else {
            o->heading = func_0019A5C8() % 120 + 120;
        }
        o->f34 = 0;
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
    if (o->f38 < 0x19) {
        o->f38++;
    }
    return 0;
}

/* shape b060:01E01220, 103 insns: colour (0x40, 0x40, 0x1F); on start 0x38 = 15 and a heading 0x3A: random, or (game step 0x3B5C from
   0x82) -60..59 / 120..239 depending on func_001F53A0 below 10; alpha grows by 0xF (below 0x60) for 8 ticks, then
   fades by 15 and stops; 0x38 counts down to 0 */

typedef struct {
    u8 pad0[0x3B5C];
    s16 step;
} Game_b060_01E01220;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b060_01E01220;

static s32 func_01E01220_b060(Game_b060_01E01220 *g, Fx_b060_01E01220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x40, 0x40, 0x1F);
    if (o->mode == 1) {
        o->f38 = 15;
        if (func_001F53A0() < 10) {
            if (g->step < 0x82) {
                o->heading = func_0019A5C8() % 360;
            } else {
                o->heading = func_0019A5C8() % 120 - 60;
            }
        } else if (g->step < 0x82) {
            o->heading = func_0019A5C8() % 360;
        } else {
            o->heading = func_0019A5C8() % 120 + 120;
        }
        o->f34 = 0;
        o->col[3] = 0;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0xF;
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

/* shape b060:01E013C0 (b060), 305 insns, 1 copy: b060's scene manager: with a scene id (>= 0) it clears the scene,
   resets the camera block, keeps the id, sets the 180-frame countdown, zeroes the three fade values, takes two model
   handles and loads textures 13..15 and 2; otherwise it runs the module's step and every live node's update (by its
   callback), draws every live node twice (callback -> draw function) 25 below the player's point, from frame 21 eases
   fades 0xC0 and 0xC8 up to 0.5 by 0.01 (0xC4 = 0.1), counts down and returns 1 / 4 / 2 / 6 at frames 107 / 145 / 132
   / 118..126, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[8];
} Node_b060_01E013C0;

typedef struct {
    u8 pad0[0xC0];
    f32 fC0;
    f32 fC4;
    f32 fC8;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x284 - 0x110];
    Node_b060_01E013C0 node[220];
    u8 pad3984[0x3B00 - 0x3984];
    s32 count;
    u8 pad3B04[8];
    s32 ot;
    u8 pad3B10[0x38];
    s16 h3B48;
    s16 h3B4A;
    u8 pad3B4C[0xE];
    s16 id;
    s16 timer;
    u8 pad3B5E[2];
    u8 cam[0x170];
} Scene_b060_01E013C0;

static s32 func_01E013C0_b060(s32 arg0, s32 id) {
    Scene_b060_01E013C0 *g = (Scene_b060_01E013C0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_01E00080_b060();
    extern s32 func_01E009B0_b060();
    extern s32 func_01E00BB0_b060();
    extern s32 func_01E00D80_b060();
    extern s32 func_01E00ED0_b060();
    extern s32 func_01E01080_b060();
    extern s32 func_01E01220_b060();
    extern void b060_01E019B0();
    extern void b060_01E01B50();
    extern void b060_01E01D00();
    extern void b060_01E01EB0();
    Vec4f v;
    u8 buf[0x90];
    s32 j;
    s32 n;
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3CD0);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 180;
        g->fC0 = 0.0f;
        g->fC4 = 0.0f;
        g->fC8 = 0.0f;
        g->h3B48 = func_001F5560(func_001F53A0(), 40, 1);
        g->h3B4A = func_001F5560(func_001F53A0(), 2, 0);
        for (i = 13; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        return 0;
    }
    func_01E00080_b060(g, 0);
    for (j = 0; j < 220; j++) {
        if (g->node[j].used != 0) {
            if (g->node[j].fn == func_01E009B0_b060) {
                func_01E009B0_b060(g, &g->node[j]);
            }
            if (g->node[j].fn == func_01E00BB0_b060) {
                func_01E00BB0_b060(g, &g->node[j]);
            }
            if (g->node[j].fn == func_01E00D80_b060) {
                func_01E00D80_b060(g, &g->node[j]);
            }
            if (g->node[j].fn == func_01E00ED0_b060) {
                func_01E00ED0_b060(g, &g->node[j]);
            }
            if (g->node[j].fn == func_01E01080_b060) {
                func_01E01080_b060(g, &g->node[j]);
            }
            if (g->node[j].fn == func_01E01220_b060) {
                func_01E01220_b060(g, &g->node[j]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E009B0_b060) {
                b060_01E01B50(g, &g->node[i], buf, 0);
                b060_01E01B50(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00BB0_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00D80_b060) {
                b060_01E01EB0(g, &g->node[i], buf, 0);
                b060_01E01EB0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00ED0_b060) {
                b060_01E01D00(g, &g->node[i], buf, 0);
                b060_01E01D00(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E01080_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E01220_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
        }
    }
    if (g->timer > 20) {
        if (g->fC0 < 0.5) {
            g->fC0 += 0.01f;
        }
        g->fC4 = 0.1f;
        if (g->fC8 < 0.5) {
            g->fC8 += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 107) {
        return 1;
    }
    if (g->timer == 145) {
        return 4;
    }
    if (g->timer == 132) {
        return 2;
    }
    if (g->timer > 117 && g->timer < 127) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b060:01E01890, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B58 and the two arguments; returns 1 if a
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
} Slot_b060_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b060_01E01890 s[220];
    u8 pad3984[0x180];
    u8 r, g, b, a;
    u8 pad3B08[0x50];
    s16 v;
} Pool_b060_01E01890;

static s32 func_01E01890_b060(Pool_b060_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b060_01E01890 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 220; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 220;
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

/* shape b053:01E022F0, 103 insns: one textured square of an object (like b058:01E00080); mode 0 only sets up the
   packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn via
   func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b053_01E022F0;

static void func_01E019B0_b060(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b058:01E02240, 107 insns, 2 copies: one textured square of an object (b053:01E022F0 with a 0.1 scale); mode 0 only
   sets up the packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn
   via func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b058_01E02240;

static void func_01E01B50_b060(u8 *ctx, Obj_b058_01E02240 *o, void *pkt, s32 mode) {
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
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b053:01E01E30, 107 insns: b053:01E022F0 with a 0.1 scale vector (texture 0x9B, page at ctx+0x10C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b053_01E01E30;

static void func_01E01D00_b060(u8 *ctx, Obj_b053_01E01E30 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    sc.z = sc.y = sc.x = 0.1f;
    func_00108EF0(m, &sc, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b060:01E01EB0, 179 insns: b089:01E04330 family fan of 9 thin triangles 40 apart (8 wide) drawn twice each,
   first with texture frame 0x8F and then 0x8C; mode 0 sets up the packet (frame 0x8D, one colour) */

typedef struct {
    u8 pad0[0x108];
    s32 tex;
    u8 pad10C[0x3B0C - 0x10C];
    s32 ot;
    u8 pad3B10[0x24];
    f32 depth;
    u8 pad3B38[0x3B60 - 0x3B38];
    u8 tab[1];
} Ctx_b060_01E01EB0;

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
} Fx_b060_01E01EB0;

static void func_01E01EB0_b060(Ctx_b060_01E01EB0 *g, Fx_b060_01E01EB0 *o, void *p, s32 lit) {
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
        func_00106080(rm, 0x8D, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, 0, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 9; i++) {
        t = o->ang + a;
        q[2].x = o->r * func_00108030(g->tab, t, 1);
        q[2].z = o->r * func_00108030(g->tab, t, 0);
        q[0].x = 0.0f;
        q[0].z = 0.0f;
        t = o->ang + 8 + a;
        q[3].x = o->r * func_00108030(g->tab, t, 1);
        q[3].z = o->r * func_00108030(g->tab, t, 0);
        q[1].x = 0.0f;
        q[1].z = 0.0f;
        func_00106080(rm, 0x8F, o->h34, rm);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, (u32)g->depth);
        }
        func_00106080(rm, 0x8C, o->h34, rm);
        func_00108500(p, rm, 0);
        if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, (u32)g->depth);
        }
        a += 40;
    }
    }
}
