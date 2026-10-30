#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00080_b774);

/* shape b774:01E009D0, 287 insns: B774_OBJ_MOVE_2_, a trail spark: pink (white-ish after frame 140), set up once
   (life 3..12, spin -15..14, random turn), fades in over its life then out (faster from level 30), and scatters its
   trail's eight points (0x110 + idx * 0x80) by up to 4, stacked by 0x3710 before frame 140, else 17 apart */

typedef struct {
    u8 pad0[0x110];
    Vec4f trail[10][8];
    u8 pad610[0x36D0 - 0x610];
    s32 level;
    u8 pad36D4[0x3710 - 0x36D4];
    s16 step;
    u8 pad3712[0x371E - 0x3712];
    s16 t;
} Scene_b774_01E009D0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 idx;
    s16 age;
    s16 f34;
    s16 state;
    s16 life;
    s16 spin;
} Spark_b774_01E009D0;

static s32 func_01E009D0_b774(Scene_b774_01E009D0 *g, Spark_b774_01E009D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    Vec4f *p;

    if (g->t > 140) {
        func_001076F0(o->col, 0xFF, 0x10, 0xFF);
    } else {
        func_001076F0(o->col, 0x2F, 0x10, 0x2F);
    }
    if (o->state == 1) {
        o->life = func_0019A5C8() % 10 + 3;
        o->spin = func_0019A5C8() % 30 - 15;
        o->f34 = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->col[3] = 0;
        o->age = 0;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->col[3] < 240) {
            o->col[3] += 240 / (o->life - 1);
        }
    } else if (g->level < 30) {
        if (o->col[3] > 16) {
            o->col[3] -= 10;
        } else {
            o->state = 0;
        }
    } else {
        if (o->col[3] > 16) {
            o->col[3] -= 15;
        } else {
            o->state = 1;
        }
    }
    o->age++;
    if (o->idx == 0) {
        p = g->trail[0];
    } else if (o->idx == 1) {
        p = g->trail[1];
    } else if (o->idx == 2) {
        p = g->trail[2];
    } else if (o->idx == 3) {
        p = g->trail[3];
    } else if (o->idx == 4) {
        p = g->trail[4];
    } else if (o->idx == 5) {
        p = g->trail[5];
    } else if (o->idx == 6) {
        p = g->trail[6];
    } else if (o->idx == 7) {
        p = g->trail[7];
    } else if (o->idx == 8) {
        p = g->trail[8];
    } else {
        p = g->trail[9];
    }
    for (i = 0; i < 8; i++) {
        p->x = func_0019A5C8() % 8 - 4;
        p->z = func_0019A5C8() % 8 - 4;
        if (g->t < 140) {
            p->y = i * g->step;
        } else {
            p->y = i * 17;
        }
        p++;
    }
    if (o->idx == 0) {
        g->trail[0][0].x = 0.0f;
        g->trail[0][0].z = 0.0f;
    } else if (o->idx == 1) {
        g->trail[1][0].x = 0.0f;
        g->trail[1][0].z = 0.0f;
    } else if (o->idx == 2) {
        g->trail[2][0].x = 0.0f;
        g->trail[2][0].z = 0.0f;
    } else if (o->idx == 3) {
        g->trail[3][0].x = 0.0f;
        g->trail[3][0].z = 0.0f;
    } else if (o->idx == 4) {
        g->trail[4][0].x = 0.0f;
        g->trail[4][0].z = 0.0f;
    } else if (o->idx == 5) {
        g->trail[5][0].x = 0.0f;
        g->trail[5][0].z = 0.0f;
    } else if (o->idx == 6) {
        g->trail[6][0].x = 0.0f;
        g->trail[6][0].z = 0.0f;
    } else if (o->idx == 7) {
        g->trail[7][0].x = 0.0f;
        g->trail[7][0].z = 0.0f;
    } else if (o->idx == 8) {
        g->trail[8][0].x = 0.0f;
        g->trail[8][0].z = 0.0f;
    } else {
        g->trail[9][0].x = 0.0f;
        g->trail[9][0].z = 0.0f;
    }
    o->rot[2] += o->spin * 64;
    if (g->level < 30 && o->col[3] > 15) {
        o->col[3] -= 14;
    }
    return 0;
}

/* shape b774:01E00E50, 78 insns: on start 0x38 = 30, one random roll thrown away, colour blue, random rotation; alpha
   grows by 12 for 10 ticks, then fades by 9 and stops; 0x38 counts up; the position follows the game's float point
   at 0x610 */

typedef struct {
    u8 pad0[0x610];
    f32 pos[3];
} Game_b774_01E00E50;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b774_01E00E50;

static s32 func_01E00E50_b774(Game_b774_01E00E50 *g, Fx_b774_01E00E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 30;
        func_0019A5C8();
        func_001076F0(o->col, 0, 0, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] += 12;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f38++;
    o->tick++;
    o->x = g->pos[0];
    o->y = g->pos[1];
    o->z = g->pos[2];
    return 0;
}

/* shape b774:01E00F90, 138 insns: a purple glow at the scene's point (ctx+0x610) with a random turn: fades in over 1..5 ticks (more as scene count passes 140/145/150/155), then down by 9; size grows 3 per tick up to the scene's limit */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x610];
    f32 at[3];
    u8 pad61C[0x36F4 - 0x61C];
    f32 limit;
    u8 pad36F8[0x371E - 0x36F8];
    s16 count;
} Ctx_b774_01E00F90;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
} Fx_b774_01E00F90;

static s32 func_01E00F90_b774(Ctx_b774_01E00F90 *g, Fx_b774_01E00F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 n;

    if (g->count < 140) {
        n = 1;
    } else if (g->count < 145) {
        n = 2;
    } else if (g->count < 150) {
        n = 3;
    } else if (g->count < 155) {
        n = 4;
    } else {
        n = 5;
    }
    if (o->mode == 1) {
        o->size = 0;
        func_0019A5C8();
        if (g->count < 140) {
            func_001076F0(o->col, 0x2F, 0x1F, 0x40);
        } else {
            func_001076F0(o->col, 0x4F, 0x2F, 0x80);
        }
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < n) {
        o->col[3] += 0x80 / n;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->size < g->limit) {
        o->size += 3;
    }
    o->tick++;
    o->x = g->at[0];
    o->y = g->at[1];
    o->z = g->at[2];
    return 0;
}

/* shape b774:01E011C0, 182 insns: b774:01E00F90's glow from size 5, dimming in steps over scene frames 257..260, fading
   by 10 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x610];
    f32 at[3];
    u8 pad61C[0x36F4 - 0x61C];
    f32 limit;
    u8 pad36F8[0x371E - 0x36F8];
    s16 count;
} Ctx_b774_01E011C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
} Fx_b774_01E011C0;

static s32 func_01E011C0_b774(Ctx_b774_01E011C0 *g, Fx_b774_01E011C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 n;

    if (g->count < 140) {
        n = 1;
    } else if (g->count < 145) {
        n = 2;
    } else if (g->count < 150) {
        n = 3;
    } else if (g->count < 155) {
        n = 4;
    } else {
        n = 5;
    }
    if (o->mode == 1) {
        o->size = 5;
        func_0019A5C8();
        if (g->count < 140) {
            func_001076F0(o->col, 0x2F, 0x1F, 0x40);
        } else if (g->count < 257) {
            func_001076F0(o->col, 0x4F, 0x2F, 0x80);
        } else if (g->count == 258) {
            func_001076F0(o->col, 0x40, 0x1F, 0x70);
        } else if (g->count == 259) {
            func_001076F0(o->col, 0x30, 0x1F, 0x60);
        } else if (g->count == 260) {
            func_001076F0(o->col, 0x20, 0x1F, 0x50);
        } else if (g->count > 260) {
            func_001076F0(o->col, 0x10, 0x1F, 0x40);
        }
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < n) {
        o->col[3] += 0x80 / n;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->size < g->limit) {
        o->size += 3;
    }
    o->tick++;
    o->x = g->at[0];
    o->y = g->at[1];
    o->z = g->at[2];
    return 0;
}

/* shape b774:01E014A0, 75 insns: an orange tumbling glow at three random turns, growing 5 a tick up to 100 and turning 12: in by 24 for 4 ticks; past size 30 out by 9, and ends */

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
} Glow_b774_01E014A0;

static s32 func_01E014A0_b774(s32 arg0, Glow_b774_01E014A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x80, 0x40, 0x20);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->kind = 0;
        o->f38 = 0;
        o->mode = 2;
    }
    if (o->tick < 4) {
        o->col[3] += 0x18;
    }
    if (o->f38 > 30) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->f38 < 100) {
        o->f38 += 5;
    }
    o->tick++;
    o->ang += 12;
    return 0;
}

/* shape b774:01E015D0, 97 insns: on start random rotation, variant 0, alpha 0; alpha grows by 6 (below 0x40) for 10
   ticks; the colour flickers red; 0x38 from the game float 0x36F8 and the position from the game point 0x610; fades by
   9 and stops while the game counter 0x36D0 is below 0x1E */

typedef struct {
    u8 pad0[0x610];
    f32 pos[3];
    u8 pad61C[0x36D0 - 0x61C];
    s32 count;
    u8 pad36D4[0x24];
    f32 f36F8;
} Game_b774_01E015D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b774_01E015D0;

static s32 func_01E015D0_b774(Game_b774_01E015D0 *g, Fx_b774_01E015D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f34 = 0;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x40) {
            o->col[3] += 6;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0x10, 0x20);
    } else {
        func_001076F0(o->col, 0x5F, 0x10, 0x20);
    }
    o->f38 = g->f36F8;
    o->x = g->pos[0];
    o->y = g->pos[1];
    o->z = g->pos[2];
    if (g->count < 0x1E) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* OVL_WARM */

/* shape b774:01E01760, 85 insns: a purple glow at three random turns sitting on the scene point (ctx+0x610) for its first 4 ticks, sized by the scene value (ctx+0x36F8): in by 80 up to 0x50 on its first tick; its angle sweeps 8 a tick from 90 and it ends at 270 */

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
} Glow_b774_01E01760;

typedef struct {
    u8 pad[0x610];
    f32 x, y, z;
    u8 pad61C[0x36F8 - 0x61C];
    f32 size;
} Game_b774_01E01760;

static s32 func_01E01760_b774(Game_b774_01E01760 *g, Glow_b774_01E01760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x3F, 0x10, 0x30);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->kind = 0;
        o->h30 = 90;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 1) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x50;
        }
    }
    o->f38 = g->size;
    if (o->tick < 4) {
        o->h0 = g->x;
        o->h2 = g->y;
        o->h4 = g->z;
    }
    o->tick++;
    if (o->h30 < 270) {
        o->h30 += 8;
    } else {
        o->mode = 0;
    }
    return 0;
}

/* shape b774:01E018C0, 171 insns: b714:01E02E50 family ember: frame 0..3, a random yellow / red / orange, angles 0..359, nudged -10..9 per axis; alpha 0x2A for 3 ticks, then down by 10; drifts 14 along its two angles (0x8, 0xC by the sine/cosine of the heading, 0xA by the cosine of 0x30) from the game table 0x3724 */

typedef struct {
    u8 pad0[0x3724];
    u8 trig[1];
} Game_b774_01E018C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b774_01E018C0;

static s32 func_01E018C0_b774(Game_b774_01E018C0 *g, Fx_b774_01E018C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = 1;
        o->f34 = func_0019A5C8() % 4;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0xFF, 0xF0, 0);
        } else if (k == 1) {
            func_001076F0(o->col, 0xFF, 0, 0);
        } else if (k == 2) {
            func_001076F0(o->col, 0xFF, 0x80, 0);
        }
        o->f30 = func_0019A5C8() % 360;
        o->heading = func_0019A5C8() % 360;
        o->x += (s16)(func_0019A5C8() % 20 - 10);
        o->y += (s16)(func_0019A5C8() % 20 - 10);
        o->z += (s16)(func_0019A5C8() % 20 - 10);
        o->mode = 2;
    }
    if (o->tick < 3) {
        o->col[3] = 0x2A;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->f8 = o->f8 + 14.0f * func_00108030(g->trig, o->heading, 0);
    o->fA = o->fA + 14.0f * func_00108030(g->trig, o->f30, 1);
    o->fC = o->fC + 14.0f * func_00108030(g->trig, o->heading, 1);
    return 0;
}

/* shape b774:01E01B70, 87 insns: a green spark (size 1, random frame 0..3) at two random angles and three random turns: alpha 0x18 for 10 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[2];
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
} Glow_b774_01E01B70;

static s32 func_01E01B70_b774(s32 arg0, Glow_b774_01E01B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->kind = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0, 0xFF, 0);
        func_001076F0(o->col2, 0, 0xFF, 0);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x18;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b774:01E01CD0, 87 insns: second colour (0x20, 0x10, 0x10); on start the rotation faces the model angle side
   (-0x4000 or -0xC000, 0, 0x3800), 0x24 = 0, size 0x5A, second alpha 0; it grows by 0x40 (below 0x80) for 2 ticks,
   then fades by 5 and stops; 0x28 = 10 + the game float 0x36F4; the size grows by 8 up to 0xA0 */

typedef struct {
    u8 pad0[0x36F4];
    f32 v;
} Game_b774_01E01CD0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[4];
    s16 size;
    s16 tick;
    s16 f24;
    s16 mode;
    s16 f28;
    u8 pad2A[2];
    u8 col2[4];
} Fx_b774_01E01CD0;

static s32 func_01E01CD0_b774(Game_b774_01E01CD0 *g, Fx_b774_01E01CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    func_001076F0(o->col2, 0x20, 0x10, 0x10);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), ang);
        if ((s32)(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->f24 = 0;
        o->size = 0x5A;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->f28 = 10.0f + g->v;
    o->tick++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    return 0;
}

/* shape b774:01E01E30, 145 insns: scene light (ctx+0x3680) at the scene's point (y/z from ctx+0x614), height 63: kind 0 raises the level 0.01 to 1.0 and red by 3 to 128, green and alpha by 6 to 240 (255 at count 250); under timer 40 the level falls 0.03 to 0.3; off under 30, ended at 1 */

typedef struct {
    f32 c[4];
    f32 pos[4];
    f32 f20;
    f32 f24;
    f32 level;
} Light_b774_01E01E30;

typedef struct {
    u8 pad0[0x610];
    f32 at[3];
    u8 pad61C[0x3680 - 0x61C];
    Light_b774_01E01E30 lt;
    u8 pad36AC[0x36D0 - 0x36AC];
    s32 timer;
    u8 pad36D4[0x371E - 0x36D4];
    s16 count;
} Ctx_b774_01E01E30;

typedef struct {
    u8 pad0[0x30];
    s16 kind;
    u8 pad32[4];
    s16 mode;
    u8 pad38[2];
    s16 ang;
} Fx_b774_01E01E30;

static s32 func_01E01E30_b774(Ctx_b774_01E01E30 *g, Fx_b774_01E01E30 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->lt.c[0] = 0.0f;
        g->lt.c[1] = 0.0f;
        g->lt.c[2] = 0.0f;
        g->lt.c[3] = 0.0f;
        g->lt.f20 = 0.0f;
        g->lt.f24 = 63.0f;
        g->lt.level = 0.0f;
        o->mode = 2;
    }
    g->lt.pos[0] = 0.0f;
    g->lt.pos[1] = g->at[1];
    g->lt.pos[2] = g->at[2];
    o->ang += 6;
    if (g->count == 250) {
        g->lt.c[1] = 255.0f;
        g->lt.c[2] = 128.0f;
        g->lt.c[3] = 0.0f;
        g->lt.c[3] = 128.0f;
    }
    if (o->kind == 0) {
        if (g->lt.level < 1.0f) {
            g->lt.level += 0.01f;
        } else {
            o->kind = 1;
        }
        if (g->lt.c[0] < 128.0f) {
            g->lt.c[0] += 3.0f;
        } else {
            g->lt.c[0] = 128.0f;
        }
        if (g->lt.c[1] < 240.0f) {
            g->lt.c[1] += 6.0f;
        } else {
            g->lt.c[1] = 255.0f;
        }
        if (g->lt.c[3] < 240.0f) {
            g->lt.c[3] += 6.0f;
        } else {
            g->lt.c[3] = 255.0f;
        }
    }
    if (g->timer < 40) {
        if (g->lt.level > 0.3f) {
            g->lt.level -= 0.03f;
        }
    }
    if (g->timer < 30) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->lt);
    }
    if (g->timer == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b774:01E02080, 55 insns: volume fade by game state (b058:01E017A0 shape): state at 0x36D0 limit 0x1E, down 10
   to 0x30, up 10 capped at 0x80; state 2 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0x36D0];
    s32 state;
} Game_b774_01E02080;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b774_01E02080;

static s32 func_01E02080_b774(Game_b774_01E02080 *g, Fade_b774_01E02080 *o) {
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
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    if (g->state == 2) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b774:01E02160, 31 insns: func_001F7170(3, 0, &a, &b, 0) with copies of the module's floats at 0x01E04880 and
   0x01E04888; when the game value at 0x371E is 0x3A the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b774_01E02160;

typedef struct {
    u8 pad0[0x371E];
    s16 v;
} Game_b774_01E02160;

typedef struct {
    u8 pad0[0x36];
    s16 f;
} Fx_b774_01E02160;

extern F_b774_01E02160 D_01E04880_b774;
extern F_b774_01E02160 D_01E04888_b774;

static s32 func_01E02160_b774(Game_b774_01E02160 *g, Fx_b774_01E02160 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b774_01E02160 a;
    F_b774_01E02160 b;

    a = D_01E04880_b774;
    b = D_01E04888_b774;
    func_001F7170(3, 0, &a, &b, 0);
    if (g->v == 0x3A) {
        o->f = 0;
    }
    return 0;
}

/* shape b774:01E021E0, 146 insns: b763:01E032F0's own-colour veil on the small effect layout: zoom from the s16 0x38 (7), purple (0x50, 0x20, 0x50), additive 0x48, brightening by 14 (below 0x48) while the scene timer (0x36D0) is above 25 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b774_01E021E0;

typedef struct {
    f32 s, t;
    Xyz_b774_01E021E0 p;
} Tv_b774_01E021E0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b774_01E021E0 v[2];
    u8 tail[0x20];
} Tex_b774_01E021E0;

typedef struct {
    u8 pad0[0x36D0];
    s32 timer;
} Ctx_b774_01E021E0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f48;
} Fx_b774_01E021E0;

static s32 func_01E021E0_b774(Ctx_b774_01E021E0 *g, Fx_b774_01E021E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b774_01E021E0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 7;
        func_001076F0(o->col, 0x50, 0x20, 0x50);
        o->mode = 2;
    }
    ((Tex_b774_01E021E0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b774_01E021E0 *)(s32)&pk)->size = 5;
    ((Tex_b774_01E021E0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b774_01E021E0 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
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
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->timer > 25) {
        if (o->col[3] < 0x48) {
            o->col[3] += 14;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

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
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E02430_b774(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02610_b774);

/* shape b774:01E02D50, 72 insns: twin of b046:01E03E20: take the first free slot of the 170-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3716 and the two arguments; returns 1 if a
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
} Slot_b774_01E02D50;

typedef struct {
    u8 pad[0x40];
    u8 m[0x620];
    Slot_b774_01E02D50 s[170];
    u8 pad30E0[0x5F4];
    u8 r, g, b, a;
    u8 pad36D8[0x3E];
    s16 v;
} Pool_b774_01E02D50;

static s32 func_01E02D50_b774(Pool_b774_01E02D50 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b774_01E02D50 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 170; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 170;
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

/* shape b774:01E02E70, 59 insns: takes the first free of 30 effect slots (0x30 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and copies the context's frame */

typedef struct {
    u8 pad0[0x20];
    s16 f20;
    u8 pad22[4];
    s16 used;
    u8 pad28[4];
    u8 c2C[4];
} Slot_b774_01E02E70;

typedef struct {
    u8 pad0[0x40];
    f32 pos[3];
    u8 pad4C[0x30E0 - 0x4C];
    Slot_b774_01E02E70 slots[0x1E];
    u8 pad[0x36D4 - 0x30E0 - 0x1E * 0x30];
    u8 rgba[4];
    u8 pad36D8[0x3E];
    s16 f3716;
} Ctx_b774_01E02E70;

static s32 func_01E02E70_b774(Ctx_b774_01E02E70 *ctx) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b774_01E02E70 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1E; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x30);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x1E;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f20 = ctx->f3716;
        return 1;
    }
    return 0;
}

/* shape b774:01E02F60 (B774PAINT_RAIN), 259 insns, 1 copy: two-pass ring (b053:01E02490's family): mode 0 sets the
   material (frame 0x97 at the object's page, its colour, scene texture 0x10C); other modes scale (0.8, 1, 0.8) at the
   object, the 1.0f through a block local, then 12 quads 30 apart between radius size and size - w, the outer corners
   jittered by -10..9 when the matching scene slot runs callback 0x1E011C0 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b774_01E02F60;

typedef struct {
    s32 pad0;
    void *cb;
    u8 pad8[0x38];
} Slot_b774_01E02F60;

typedef struct {
    u8 pad0[0x10C];
    void *tex;
    u8 pad110[0x680 - 0x110];
    Slot_b774_01E02F60 slot[12];
    u8 pad980[0x36DC - 0x980];
    s32 ot;
    u8 pad36E0[0x1C];
    f32 depth;
    u8 pad3700[0x1E];
    s16 tick;
    u8 pad3720[4];
    u8 tbl[1];
} Ctx_b774_01E02F60;

static void func_01E02F60_b774(Ctx_b774_01E02F60 *ctx, Obj_b774_01E02F60 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    extern void func_01E011C0_b774(void);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x10];
    f32 w;
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, ctx->tex, 1);
    } else {
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        {
            f32 r = 1.0f;
            func_00106DD0(&sc, 0.8f, r, 0.8f);
        }
        func_00108EF0(m, &sc, o->rot, &pos);
        q[0].y = 0.0f;
        q[1].y = 0.0f;
        q[2].y = 0.0f;
        q[3].y = 0.0f;
        if (ctx->tick < 140) {
            if (o->size - 10 < 0) {
                w = 3.0f;
            } else {
                w = 10.0f;
            }
        } else {
            if (o->size - 10 < 0) {
                w = 3.0f;
            } else {
                w = o->size;
            }
        }
        for (i = 0; i < 12; i++) {
            k = o->ang + a;
            q[2].x = o->size * func_00108030(ctx->tbl, k, 1);
            q[2].z = o->size * func_00108030(ctx->tbl, k, 0);
            q[0].x = (o->size - w) * func_00108030(ctx->tbl, k, 1);
            q[0].z = (o->size - w) * func_00108030(ctx->tbl, k, 0);
            k = o->ang + 30 + a;
            q[3].x = o->size * func_00108030(ctx->tbl, k, 1);
            q[3].z = o->size * func_00108030(ctx->tbl, k, 0);
            q[1].x = (o->size - w) * func_00108030(ctx->tbl, k, 1);
            q[1].z = (o->size - w) * func_00108030(ctx->tbl, k, 0);
            if (ctx->slot[i].cb == func_01E011C0_b774) {
                q[2].y = func_0019A5C8() % 20 - 10;
                q[3].y = func_0019A5C8() % 20 - 10;
            }
            if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, &ctx->depth) != 0) {
                func_002075F0((s32)pkt, ctx->ot, (u32)ctx->depth);
            }
            a += 30;
        }
    }
}


/* shape b774:01E03370, 212 insns: draws a ribbon along trail h30 (ctx+0x110 + 0x80 k, k 0..8, else 9): mode 0 sets up
   the packet's texture (0x96, page h34) and returns; otherwise it places the camera point (ctx+0x610) with scale
   (0.5, 0.5, 1) and the object's turn, then for 5 links joins each trail point to the next with a quad h38 wide that
   narrows by a fifth per link */

typedef struct {
    u8 pad0[0x10C];
    void *tex;
    Vec4f tr[10][8];
    Vec4f cam;
} Ctx_b774_01E03370;

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 k;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 w;
} Obj_b774_01E03370;

static inline void cp2_b774_01E03370(Vec4f *a, Vec4f *b, Vec4f v) {
    *a = v;
    *b = v;
}

static void func_01E03370_b774(Ctx_b774_01E03370 *g, Obj_b774_01E03370 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    u8 td[0x10];
    f32 m[16];
    u8 *ot;
    s32 rot[4];
    s16 i;
    Vec4f *tr;
    Vec4f *nx;
    f32 w;
    f32 w0;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x96, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = g->cam.x;
        *(f32 *)(u32)&pos.y = g->cam.y;
        *(f32 *)(u32)&pos.z = g->cam.z;
        sc.x = 0.5f;
        sc.y = 0.5f;
        sc.z = 1.0f;
        func_00108EF0(m, &sc, o->rot, &pos);
        w = o->w;
        w0 = w;
        if (o->k == 0) {
            tr = g->tr[0];
        } else if (o->k == 1) {
            tr = g->tr[1];
        } else if (o->k == 2) {
            tr = g->tr[2];
        } else if (o->k == 3) {
            tr = g->tr[3];
        } else if (o->k == 4) {
            tr = g->tr[4];
        } else if (o->k == 5) {
            tr = g->tr[5];
        } else if (o->k == 6) {
            tr = g->tr[6];
        } else if (o->k == 7) {
            tr = g->tr[7];
        } else if (o->k == 8) {
            tr = g->tr[8];
        } else {
            tr = g->tr[9];
        }
        nx = tr + 1;
        for (i = 0; i < 5; i++) {
            pos.x = tr->x;
            *(f32 *)(u32)&pos.y = tr->y;
            *(f32 *)(u32)&pos.z = tr->z;
            tr++;
            cp2_b774_01E03370(&q[0], &q[1], pos);
            q[0].x += w;
            q[1].x -= w;
            w -= w0 / 5.0f;
            pos.x = nx->x;
            *(f32 *)(u32)&pos.y = nx->y;
            *(f32 *)(u32)&pos.z = nx->z;
            nx++;
            cp2_b774_01E03370(&q[2], &q[3], pos);
            q[2].x += w;
            q[3].x -= w;
            func_00108F90(q, pkt, m, (s32)ot);
        }
    }
}

/* shape b774:01E036C0, 103 insns: mode 0 sets the drawing state (a 0x9C matrix from its angle 0x34, colour, the scene
   texture 0x10C); otherwise draws the effect as a camera-facing square of its size 0x38: camera rotation, world matrix at its position offset by
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
} Fx_b774_01E036C0;

typedef struct {
    u8 pad0[0x10C];
    s32 tex;
} Scene_b774_01E036C0;

static void func_01E036C0_b774(Scene_b774_01E036C0 *g, Fx_b774_01E036C0 *o, void *p, s32 mode) {
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
        func_00106080(rm, 0x9C, o->h34, rm);
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

/* shape b774:01E03860, 209 insns: b774:01E03BB0's texture page 0x9C on a sphere: 18 bands 20 degrees tall (radius and height 45 * cos/sin), 12 quads 30 degrees wide from 0x3A, scaled by 0x38 / 2000 at the object */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b774_01E03860;

static void func_01E03860_b774(u8 *ctx, Obj_b774_01E03860 *o, void *pkt) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A23B0(f32);
    extern s32 func_00205630();
    Vec4f q[4];
    Vec4f pos;
    Vec4f sv;
    f32 m[16];
    u8 td[0x10];
    f32 sc;
    f32 r0;
    f32 r1;
    s32 j;
    s16 c;
    s16 k;
    s32 a;
    s32 b;
    s32 i;

    func_00106080(td, 0x9C, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc = o->size;
    sc /= 2000.0f;
    func_00106DD0(&sv, sc, sc, sc);
    func_00108EF0(m, &sv, NULL, &pos);
    b = 20;
    for (i = 0, a = 0; i < 18; i++) {
        q[1].y = *(f32 *)(u32)&q[0].y = 45.0f * func_00108030(ctx + 0x3724, a, 0);
        q[3].y = *(f32 *)(u32)&q[2].y = 45.0f * func_00108030(ctx + 0x3724, b, 0);
        r0 = 45.0f * func_00108030(ctx + 0x3724, a, 1);
        r1 = 45.0f * func_00108030(ctx + 0x3724, b, 1);
        c = 0;
        for (j = 0; j < 12; j++) {
            k = o->ang + c;
            q[2].x = r1 * func_00108030(ctx + 0x3724, k, 1);
            q[2].z = r1 * func_00108030(ctx + 0x3724, k, 0);
            q[0].x = r0 * func_00108030(ctx + 0x3724, k, 1);
            q[0].z = r0 * func_00108030(ctx + 0x3724, k, 0);
            k = o->ang + 30 + c;
            q[3].x = r1 * func_00108030(ctx + 0x3724, k, 1);
            q[3].z = r1 * func_00108030(ctx + 0x3724, k, 0);
            q[1].x = r0 * func_00108030(ctx + 0x3724, k, 1);
            q[1].z = r0 * func_00108030(ctx + 0x3724, k, 0);
            if (func_00205630(q, 0x70000000, m, pkt, ctx + 0x36FC) != 0) {
                func_002075F0((s32)pkt, *(s32 *)(ctx + 0x36DC), func_001A23B0(*(f32 *)(ctx + 0x36FC)));
            }
            c += 30;
        }
        a += 20;
        b += 20;
    }
}

/* shape b774:01E03BB0, 182 insns: b159:01E01B30's ring of 18 quads 20 apart, inner radius size - 10 (not below -10) */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b774_01E03BB0;

static void func_01E03BB0_b774(u8 *ctx, Obj_b774_01E03BB0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A23B0(f32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x10];
    s32 i;
    s16 a;
    s16 k;
    s16 r;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x96, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r = o->size - 10;
    if (r < -10) {
        r = -10;
    }
    for (i = 0; i < 18; i++) {
        k = o->ang + a;
        q[2].x = o->size * func_00108030(ctx + 0x3724, k, 1);
        q[2].z = o->size * func_00108030(ctx + 0x3724, k, 0);
        q[0].x = r * func_00108030(ctx + 0x3724, k, 1);
        q[0].z = r * func_00108030(ctx + 0x3724, k, 0);
        k = o->ang + 20 + a;
        q[3].x = o->size * func_00108030(ctx + 0x3724, k, 1);
        q[3].z = o->size * func_00108030(ctx + 0x3724, k, 0);
        q[1].x = r * func_00108030(ctx + 0x3724, k, 1);
        q[1].z = r * func_00108030(ctx + 0x3724, k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x36FC)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x36DC), func_001A23B0(*(f32 *)(ctx + 0x36FC)));
        }
        a += 20;
    }
}

/* shape b774:01E03E90, 208 insns: b148:01E05240 twin with the band heights not lowered by 90; b046:01E03F40 family: a
   dome band of 12 sectors 30 apart */

typedef struct {
    u8 pad0[0x10C];
    void *texture;
    u8 pad110[0x36DC - 0x110];
    s32 ot;
    u8 pad36E0[0x36FC - 0x36E0];
    f32 dep;
    u8 pad3700[0x3724 - 0x3700];
    u8 trig[1];
} Ctx_b774_01E03E90;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 tilt;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Band_b774_01E03E90;

static void func_01E03E90_b774(Ctx_b774_01E03E90 *c, Band_b774_01E03E90 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x10];
    s32 k;
    s32 j;
    s16 a;
    s16 t;
    f32 sc;
    f32 r0;
    f32 r1;
    f32 y;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc = o->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        quad[0].y = 90.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 90.0f * func_00108030(c->trig, o->tilt + 0x14, 0);
        quad[3].y = quad[2].y;
        r0 = 90.0f * func_00108030(c->trig, o->tilt, 1);
        r1 = 90.0f * func_00108030(c->trig, o->tilt + 0x14, 1);
        a = 0;
        for (k = 0; k < 12; k++) {
            t = o->ang + a;
            quad[2].x = r1 * func_00108030(c->trig, t, 1);
            quad[2].z = r1 * func_00108030(c->trig, t, 0);
            quad[0].x = r0 * func_00108030(c->trig, t, 1);
            quad[0].z = r0 * func_00108030(c->trig, t, 0);
            t = o->ang + 30 + a;
            quad[3].x = r1 * func_00108030(c->trig, t, 1);
            quad[3].z = r1 * func_00108030(c->trig, t, 0);
            quad[1].x = r0 * func_00108030(c->trig, t, 1);
            quad[1].z = r0 * func_00108030(c->trig, t, 0);
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 0x1E;
        }
    }
    }
}

/* shape b774:01E041D0, 214 insns: b774:01E03860's sphere cut to one band: mode 0 sets up texture page 0x97 (0x24) with colour 0x2C; otherwise one band from latitude 0x20 (clamped to 160 for the radius) to +40 / +30, radius 90, 12 quads 30 degrees wide from 0x2A, scaled by 0x28 / 250 and turned by 0x10 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    s16 lat;
    u8 pad22[2];
    s16 page;
    u8 pad26[2];
    s16 size;
    s16 ang;
    u8 col[8];
} Obj_b774_01E041D0;

static inline void put_b774_01E041D0(f32 *a, f32 *b, f32 v) {
    a[0] = v;
    *b = a[0];
}

static void func_01E041D0_b774(u8 *ctx, Obj_b774_01E041D0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A23B0(f32);
    extern s32 func_00205630();
    Vec4f q[4];
    Vec4f pos;
    Vec4f sv;
    f32 m[16];
    u8 td[0x10];
    f32 sc;
    f32 r0;
    f32 r1;
    s32 j;
    s32 i;
    s16 c;
    s16 a;
    s16 k;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
    } else {
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        sc = o->size;
        sc /= 250.0f;
        func_00106DD0(&sv, sc, sc, sc);
        func_00108EF0(m, &sv, o->rot, &pos);
        for (i = 0; i < 1; i++) {
            k = o->lat;
            if (k > 160) {
                k = 160;
            }
            put_b774_01E041D0(&q[0].y, &q[1].y, 90.0f * func_00108030(ctx + 0x3724, o->lat, 0));
            put_b774_01E041D0(&q[2].y, &q[3].y, 90.0f * func_00108030(ctx + 0x3724, o->lat + 40, 0));
            r0 = 90.0f * func_00108030(ctx + 0x3724, k, 1);
            r1 = 90.0f * func_00108030(ctx + 0x3724, k + 30, 1);
            c = 0;
            for (j = 0; j < 12; j++) {
                a = o->ang + c;
                q[2].x = r1 * func_00108030(ctx + 0x3724, a, 1);
                q[2].z = r1 * func_00108030(ctx + 0x3724, a, 0);
                q[0].x = r0 * func_00108030(ctx + 0x3724, a, 1);
                q[0].z = r0 * func_00108030(ctx + 0x3724, a, 0);
                a = o->ang + 30 + c;
                q[3].x = r1 * func_00108030(ctx + 0x3724, a, 1);
                q[3].z = r1 * func_00108030(ctx + 0x3724, a, 0);
                q[1].x = r0 * func_00108030(ctx + 0x3724, a, 1);
                q[1].z = r0 * func_00108030(ctx + 0x3724, a, 0);
                if (func_00205630(q, 0x70000000, m, pkt, ctx + 0x36FC) != 0) {
                    func_002075F0((s32)pkt, *(s32 *)(ctx + 0x36DC), func_001A23B0(*(f32 *)(ctx + 0x36FC)));
                }
                c += 30;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E04530_b774);
