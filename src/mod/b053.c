#include "common.h"

/* shape b053:01E00080, 102 insns: draws an object twice, mirrored: takes its colours, clears a 0x20-byte range block and sets
   its low and high edges from the object (low, low + span, neither below 0), then builds a matrix from the object turn and the
   given point and draws with it; the second pass negates the turn */

typedef struct {
    f32 x, y, z, w;
} V4_b053_01E00080;

typedef struct {
    f32 x, y, z;
} V3_b053_01E00080;

typedef struct {
    s32 x, y, z, w;
} R4_b053_01E00080;

typedef struct {
    f32 f0;
    f32 lo;
    u8 pad8[0xC];
    f32 hi;
    u8 pad18[8];
} Rng_b053_01E00080;

typedef struct {
    u8 pad0[2];
    s16 lo;
    u8 pad4[2];
    s16 span;
    u8 pad8[8];
    R4_b053_01E00080 rot;
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
} Obj_b053_01E00080;

static void func_01E00080_b053(s32 arg0, Obj_b053_01E00080 *o, void *arg2, V4_b053_01E00080 *pt) {
    extern void func_001091B0(void *, void *, void *);
    extern void func_00195108(void *, s32);
    extern void func_00108EF0(void *, s32, void *, void *);
    extern void func_00109050(void *, void *, void *, s32);
    V4_b053_01E00080 a;
    Rng_b053_01E00080 r;
    V4_b053_01E00080 b;
    R4_b053_01E00080 rot;
    f32 m[16];
    s32 i;

    a = *pt;
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    func_001091B0(arg2, o->c0, o->c1);
    func_00195108(&r, 0x20);
    r.lo = o->lo;
    r.hi = r.lo + o->span;
    if (r.lo < 0.0f) {
        r.lo = 0.0f;
    }
    if (r.hi < 0.0f) {
        r.hi = 0.0f;
    }
    rot = o->rot;
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            rot.x *= -1;
            rot.y *= -1;
            rot.z *= -1;
        }
        func_00108EF0(m, 0, &rot, &b);
        func_00109050(&r, arg2, m, arg0);
    }
}

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b053:01E00220, 256 insns: the scene script of b053: scene colour red 0x80, counts ctx+0x3B5E; the model angle
   (/180, less 180) goes to ctx+0x3B50 and gives a z offset of -20 * cos; on tick 20 it dims the colour and spawns
   b053:01E00620 through 0x1E01730; on ticks 105..108 five 0x1E00BD0 on the joint ctx+0x3B48 (shifted by the offset),
   past tick 28 while ctx+0x3B00 is over 20 three 0x1E00D00 a tick and one 0x1E00F20 every third tick, and on tick 106
   65 0x1E009F0 (shifted), each with random angles 0x3B5A / 0x3B54 through 0x1E01890 */

typedef struct {
    u8 pad0[0x80];
    f32 px, py, pz;
    u8 pad8C[0x3B00 - 0x8C];
    s32 w3B00;
    u8 col[4];
    u8 pad3B08[0x14];
    s32 w3B1C;
    u8 pad3B20[0x28];
    s16 joint;
    u8 pad3B4A[6];
    s16 h3B50;
    u8 pad3B52[2];
    s16 h3B54;
    u8 pad3B56[2];
    s16 h3B58;
    s16 h3B5A;
    u8 pad3B5C[2];
    s16 t;
    u8 pad3B60[4];
    u8 trig[1];
} Ctx_b053_01E00220;


#pragma optimization_level 3

static void func_01E00220_b053(Ctx_b053_01E00220 *g) {
    extern void b053_01E00620();
    extern void b053_01E009F0();
    extern void b053_01E00BD0();
    extern void b053_01E00D00();
    extern void b053_01E00F20();
    extern void b053_01E01730(Ctx_b053_01E00220 *, void *, s32);
    extern void b053_01E01890(Ctx_b053_01E00220 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A22C0(f32);
    f32 v[4];
    s32 r[4];
    s32 off;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F6160(func_001F53A0(), r);
    g->h3B50 = func_001A22C0(r[1] / 180.0f);
    g->h3B50 -= 180;
    off = func_001A22C0(20.0f * -func_00108030(g->trig, g->h3B50, 1));
    if (g->t == 20) {
        g->col[0] = 0x20;
        g->col[1] = 0x20;
        g->col[2] = 0x20;
        for (i = 0; i < 1; i++) {
            g->h3B58 = 1;
            g->w3B1C = 0;
            g->h3B5A = 1;
            g->h3B54 = 0;
            b053_01E01730(g, b053_01E00620, 0);
        }
    }
    if (g->t == 105 || g->t == 106 || g->t == 107 || g->t == 108) {
        func_001F5620(func_001F53A0(), g->joint, v);
        for (i = 0; i < 5; i++) {
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2] + off;
            g->h3B5A = func_0019A5C8() % 360;
            g->h3B54 = func_0019A5C8() % 360;
            b053_01E01890(g, b053_01E00BD0, 0);
        }
    }
    if (g->t > 28 && g->w3B00 > 20) {
        func_001F5620(func_001F53A0(), g->joint, v);
        for (i = 0; i < 3; i++) {
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2];
            g->h3B5A = func_0019A5C8() % 360;
            g->h3B54 = func_0019A5C8() % 360;
            b053_01E01890(g, b053_01E00D00, 0);
        }
    }
    if (g->t > 28 && g->w3B00 > 20 && g->t % 3 == 1) {
        func_001F5620(func_001F53A0(), g->joint, v);
        for (i = 0; i < 1; i++) {
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2];
            g->h3B5A = func_0019A5C8() % 360;
            g->h3B54 = func_0019A5C8() % 360;
            b053_01E01890(g, b053_01E00F20, 0);
        }
    }
    if (g->t == 106) {
        func_001F5620(func_001F53A0(), g->joint, v);
        for (i = 0; i < 65; i++) {
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2] + off;
            g->h3B5A = func_0019A5C8() % 360;
            g->h3B54 = func_0019A5C8() % 360;
            b053_01E01890(g, b053_01E009F0, 0);
        }
    }
}
#pragma optimization_level reset

/* OVL_WARM */

/* shape b053:01E00620, 148 insns: a rising white column: both colours 0x80 at alpha 0x2F; it turns by 12 (wrapped past
   -359); its two heights (f4, f14) grow by 2, the top first up to 60 with the base kept within 5, then the base until it
   reaches the top, which ends its parent link and h68; their halves + 10 are kept as sizes (at least 0); in state 1, with
   a base above 0, it publishes itself and the base to the scene (g+0x3B10..0x3B5A) and, once the scene step reaches 15,
   asks the module to run it (b053:01E01730), entering state 2 */

typedef struct {
    u8 pad0[0x50];
    s32 w50;
} Link_b053_01E00620;

typedef struct Obj_b053_01E00620 {
    u8 pad0[4];
    f32 top;
    u8 pad8[0xC];
    f32 base;
    u8 pad18[0x3C];
    Link_b053_01E00620 *link;
    u8 pad58[8];
    u8 c60[4];
    u8 c64[4];
    s16 state;
    s16 s6A;
    s16 s6C;
    u8 pad6E[4];
    s16 ang;
} Obj_b053_01E00620;

typedef struct {
    u8 pad0[0x3B00];
    s32 step;
    u8 pad3B04[0xC];
    Obj_b053_01E00620 *obj;
    f32 size;
    u8 pad3B18[4];
    f32 base;
    u8 pad3B20[0x34];
    s16 ang;
    u8 pad3B56[2];
    s16 h3B58;
    s16 h3B5A;
} Scene_b053_01E00620;

static s32 func_01E00620_b053(Scene_b053_01E00620 *g, Obj_b053_01E00620 *o) {
    extern s32 b053_01E01730(Scene_b053_01E00620 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c60, 0x80, 0x80, 0x80);
    func_001076F0(o->c64, 0x80, 0x80, 0x80);
    o->c64[3] = o->c60[3] = 0x2F;
    o->ang -= 12;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->s6A = 10.0f + o->top / 2.0f;
    o->s6C = 10.0f + o->base / 2.0f;
    if (o->s6A < 0) {
        o->s6A = 0;
    }
    if (o->s6C < 0) {
        o->s6C = 0;
    }
    if (o->top <= 60.0f) {
        o->top += 2.0f;
        if (!(o->top - o->base <= 5.0f)) {
            o->base += 2.0f;
        }
    } else {
        o->base += 2.0f;
        if (!(o->base <= o->top)) {
            if (o->link != 0) {
                o->link->w50 = 0;
            }
            o->state = 0;
        }
    }
    if (o->state == 1) {
        if (!(o->base <= 0.0f)) {
            g->size = o->s6C;
            g->obj = o;
            g->h3B58 = 1;
            g->base = o->base;
            g->h3B5A = 1;
            g->ang = o->ang - 15;
            if (g->step > 14) {
                if (b053_01E01730(g, func_01E00620_b053, 0)) {
                    o->state = 2;
                }
            }
        }
    }
    return 0;
}

/* shape b053:01E00870, 32 insns: b120:01E01EA0 family: fades in by 0x40 to 0x80, then out by 9 and ends; colour (0xF0, 0x80, 0x40) */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Glow_b053_01E00870;

static s32 func_01E00870_b053(s32 arg0, Glow_b053_01E00870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->f30 == 0) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        } else {
            o->f30 = 1;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001076F0(o->col, 0xF0, 0x80, 0x40);
    return 0;
}

/* shape b053:01E008F0, 63 insns: a red sparkle: first tick picks three random turns, then grows by 3 a tick at size 10 and ends past 70 */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 state;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b053_01E008F0;

static s32 func_01E008F0_b053(s32 arg0, Glow_b053_01E008F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 0) {
        o->h2 = 0;
        o->col[3] = 0x30;
        o->col2[3] = 0xFF;
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->state = 1;
    } else if (o->state == 1) {
        o->h6 = 10;
        o->h2 += 3;
        if (o->h2 > 70) {
            o->mode = 0;
        }
    }
    func_001076F0(o->col, 0xFF, 0x3F, 0x3F);
    func_001076F0(o->col2, 0xFF, 0x3F, 0x3F);
    return 0;
}

typedef struct {
    u8 pad0000[0x3B64];
    u8 tab[1];
} Mgr_b053_01E009F0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 x, y, z;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b053_01E009F0;

static s32 func_01E009F0_b053(Mgr_b053_01E009F0 *m, Obj_b053_01E009F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        func_0019A5C8();
        func_001076F0(o->col, 0xFF, 0, 0xFF);
        o->h3A = func_0019A5C8() % 360;
        o->h30 = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 10;
        o->h6 = func_0019A5C8() % 15 + 1;
        o->h38 = 6;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    o->x = o->x + o->hE * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + o->hE * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + o->hE * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b053:01E00BD0, 76 insns: a dark ring (b130:01E012D0 shape): set up once at alpha 0x60 with a random turn on all three
   axes and a random growth step 2..6; grows by that step up to 50, fades by 9 after 10, turns 12 a frame */

typedef struct {
    u8 pad0[0xE];
    s16 step;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[8];
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b053_01E00BD0;

static s32 func_01E00BD0_b053(void *arg0, Obj_b053_01E00BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x10, 0x10, 8);
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->step = func_0019A5C8() % 5 + 2;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x60;
    }
    if (o->size > 0xA) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->size < 0x32) {
        o->size += o->step;
    }
    o->ang += 0xC;
    return 0;
}

/* shape b053:01E00D00, 135 insns: b019:01E01F60 family wisp (0x3F, 0x20, 0x3F), table at ctx+0x3B64: size from 2 stepping every fourth tick to 12, f30 -30..29, alpha up by 6 to 0x30 for 8 ticks then down by 4, swinging 16 / 4 / 16 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3B64];
    u8 tab[1];
} Mgr_b053_01E00D00;

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
} Fx_b053_01E00D00;

static s32 func_01E00D00_b053(Mgr_b053_01E00D00 *m, Fx_b053_01E00D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x20, 0x3F);
    if (o->mode == 1) {
        o->f38 = 2;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 60 - 30;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x30) {
            o->col[3] += 6;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 4 == 1) {
        if (o->f38 < 12) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 16.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 16.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b053:01E00F20, 113 insns: glow pinned to a scene object, rising slowly; its size follows a sine ramp */

typedef struct Fl_b053_01E00F20 {
    s16 x, y, z;
    u8 pad6[4];
    s16 ang;
    u8 padC[0x1C];
    u8 c28[4];
    u8 c2C[4];
    s16 rise;
    s16 age;
    s16 h34;
    s16 state;
    s16 size;
    s16 h3A;
} Fl_b053_01E00F20;

typedef struct Scn_b053_01E00F20 {
    u8 pad0[0x3B48];
    s16 id;
    u8 pad3B4A[0x1A];
    u8 table[0x10];
} Scn_b053_01E00F20;

static s32 func_01E00F20_b053(Scn_b053_01E00F20 *w, Fl_b053_01E00F20 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Vec4f v;

    func_001076F0(o->c28, 0x28, 0x10, 0x28);
    if (o->state == 1) {
        o->size = 10;
        o->h3A = func_0019A5C8() % 360;
        o->h34 = 0;
        o->rise = 0;
        o->ang = 20;
        o->state = 2;
    }
    func_001F5620(func_001F53A0(), w->id, &v);
    o->x = (s32)v.x;
    o->y = (s32)(v.y - 8.0f + (f32)o->rise);
    o->z = (s32)v.z;
    if (o->age % 2 == 1) {
        o->rise++;
    }
    o->size = (s32)(100.0f * func_00108030((s32)w->table, o->ang, 0));
    if (o->ang < 0x5A) {
        o->ang += 5;
    }
    if (o->age < 8) {
        if (o->c28[3] < 0x30) {
            o->c28[3] += 6;
        }
    } else if (o->ang >= 0x46) {
        if (o->c28[3] > 5) {
            o->c28[3] -= 4;
        } else {
            o->state = 0;
        }
    }
    o->age++;
    return 0;
}

/* shape b053:01E010F0 (b053), 398 insns, 1 copy (-O3,p): b053 scene manager (b058:01E01880 form): with a scene id (>=
   0) it clears the scene, resets the camera, keeps the id, sets the 140-frame countdown, takes two model handles (the
   second is the joint) and loads textures 2, 14 and 15; otherwise it runs the scene script, steps and draws the 15
   trail segments, spawns one glow at frame 105 and five sparkles at 104..107, steps every live node (the glow fade
   written out inline) and draws it, grows the scene scale by 0.01 up to 0.5 after frame 20, counts down and returns 1
   / 4 / 2 at frames 96 / 117 / 107, 8 once the countdown runs out */

typedef struct Seg_b053_01E010F0 {
    u8 pad0[0x68];
    s16 used;
    u8 pad6A[0x12];
} Seg_b053_01E010F0;

typedef struct Fx_b053_01E010F0 {
    u8 pad0[0x24];
    void *fn;
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Fx_b053_01E010F0;

typedef struct Scene_b053_01E010F0 {
    u8 pad0[0x8C];
    s32 w8C;
    u8 pad90[0x30];
    f32 sx, sy, sz;
    u8 padCC[4];
    s32 tex[16];
    Seg_b053_01E010F0 seg[15];
    Fx_b053_01E010F0 fx[200];
    u8 pad3A54[0x3B00 - 0x854 - 200 * 0x40];
    s32 count;
    u8 pad3B04[8];
    s32 ot;
    u8 pad3B10[0x38];
    s16 joint;
    u8 pad3B4A[0x10];
    s16 h3B5A;
    s16 id;
    s16 t;
    u8 pad3B60[4];
    u8 cam[0x16C];
} Scene_b053_01E010F0;

#pragma optimization_level 3

static s32 func_01E010F0_b053(s32 arg0, s32 code) {
    Scene_b053_01E010F0 *g = (Scene_b053_01E010F0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_01E00220_b053();
    extern void b053_01E01890();
    extern void b053_01E019C0();
    extern void b053_01E01E30();
    extern void b053_01E01FE0();
    extern void b053_01E022F0();
    extern void b053_01E02490();
    s32 j;
    s32 k;
    s32 i;
    Vec4f v;
    u8 buf[0x90];
    s32 n;

    n = 0;
    g->ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3CD0);
        func_00107C10(g->cam);
        g->id = code;
        g->count = 140;
        func_001F5560(func_001F53A0(), 1, 1);
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->joint = func_001F5560(func_001F53A0(), 1, 1);
        for (j = 2; j < 3; j++) {
            g->tex[j] = func_00202BF0(4, j);
        }
        for (j = 14; j < 16; j++) {
            g->tex[j] = func_00202BF0(4, j);
        }
        return 0;
    }
    func_01E00220_b053(g, 0);
    for (i = 0; i < 15; i++) {
        if (g->seg[i].used != 0) {
            func_01E00620_b053((Scene_b053_01E00620 *)g, (Obj_b053_01E00620 *)&g->seg[i]);
        }
    }
    for (j = 0; j < 15; j++) {
        if (g->seg[j].used != 0) {
            n++;
            b053_01E019C0(g, &g->seg[j], buf, 0);
            b053_01E019C0(g, &g->seg[j], buf, 1);
        }
    }
    g->h3B5A = 0;
    g->w8C = 0;
    if (g->t == 105) {
        b053_01E01890(g, func_01E00870_b053, 0);
    }
    if (g->t == 104 || g->t == 105 || g->t == 106 || g->t == 107) {
        for (k = 0; k < 5; k++) {
            b053_01E01890(g, func_01E008F0_b053, 0);
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn == func_01E00870_b053) {
                if (g->fx[k].f30 == 0) {
                    if (g->fx[k].col[3] < 0x80) {
                        g->fx[k].col[3] += 0x40;
                    } else {
                        g->fx[k].f30 = 1;
                    }
                } else if (g->fx[k].col[3] > 10) {
                    g->fx[k].col[3] -= 9;
                } else {
                    g->fx[k].used = 0;
                }
                func_001076F0(g->fx[k].col, 0xF0, 0x80, 0x40);
            }
            if (g->fx[k].fn == func_01E008F0_b053) {
                func_01E008F0_b053((s32)g, (Glow_b053_01E008F0 *)&g->fx[k]);
            }
            if (g->fx[k].fn == func_01E009F0_b053) {
                func_01E009F0_b053((Mgr_b053_01E009F0 *)g, (Obj_b053_01E009F0 *)&g->fx[k]);
            }
            if (g->fx[k].fn == func_01E00BD0_b053) {
                func_01E00BD0_b053(g, (Obj_b053_01E00BD0 *)&g->fx[k]);
            }
            if (g->fx[k].fn == func_01E00D00_b053) {
                func_01E00D00_b053((Mgr_b053_01E00D00 *)g, (Fx_b053_01E00D00 *)&g->fx[k]);
            }
            if (g->fx[k].fn == func_01E00F20_b053) {
                func_01E00F20_b053((Scn_b053_01E00F20 *)g, (Fl_b053_01E00F20 *)&g->fx[k]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    j = 0;
    for (n = 0; n < 200; n++) {
        if (g->fx[n].used != 0) {
            j++;
            if (g->fx[n].fn == func_01E00870_b053) {
                s32 ot = g->ot;
                func_00107990(buf, g->fx[n].col, 0);
                func_001092E0(buf, 0);
                func_001094F0(buf);
                func_002075F0(buf, ot, 0);
            }
            if (g->fx[n].fn == func_01E008F0_b053) {
                func_01E00080_b053(g->ot, (Obj_b053_01E00080 *)&g->fx[n], (void *)buf, (V4_b053_01E00080 *)&v);
            }
            if (g->fx[n].fn == func_01E009F0_b053) {
                b053_01E01E30(g, &g->fx[n], buf, 0);
                b053_01E01E30(g, &g->fx[n], buf, 1);
            }
            if (g->fx[n].fn == func_01E00BD0_b053) {
                b053_01E01FE0(g, &g->fx[n], buf, 0);
                b053_01E01FE0(g, &g->fx[n], buf, 1);
            }
            if (g->fx[n].fn == func_01E00D00_b053) {
                b053_01E022F0(g, &g->fx[n], buf, 0);
                b053_01E022F0(g, &g->fx[n], buf, 1);
            }
            if (g->fx[n].fn == func_01E00F20_b053) {
                b053_01E02490(g, &g->fx[n], buf, 0);
                b053_01E02490(g, &g->fx[n], buf, 1);
            }
        }
    }
    if (g->t > 20) {
        if (g->sx < 0.5) {
            g->sx += 0.01f;
        }
        g->sy = 0.1f;
        if (g->sz < 0.5) {
            g->sz += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->t == 96) {
        return 1;
    }
    if (g->t == 117) {
        return 4;
    }
    if (g->t == 107) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

#pragma optimization_level reset

/* shape b053:01E01730, 87 insns: takes the first free of 15 trail segments (0x7C bytes), copies the context's point and two frames,
   chains it after the context's last segment (height from the context, its lower edge 18 below), and makes it the new last */

typedef struct Seg_b053_01E01730 {
    u8 pad0[4];
    f32 top;
    u8 pad8[0xC];
    f32 bottom;
    u8 pad18[0x18];
    Vec4f pos;
    u8 pad40[0x10];
    struct Seg_b053_01E01730 *prev;
    struct Seg_b053_01E01730 *next;
    u8 pad58[0x10];
    s16 used;
    u8 pad6A[4];
    s16 f6E;
    u8 pad70[2];
    s16 f72;
    s16 f74;
    s16 f76;
    u8 pad78[4];
} Seg_b053_01E01730;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x80];
    Seg_b053_01E01730 segs[0xF];
    u8 pad[0x3B10 - 0x110 - 0xF * 0x7C];
    Seg_b053_01E01730 *last;
    u8 pad3B14[8];
    f32 height;
    u8 pad3B20[0x34];
    s16 f3B54;
    u8 pad3B56[4];
    s16 f3B5A;
} Ctx_b053_01E01730;

static s32 func_01E01730_b053(Ctx_b053_01E01730 *ctx) {
    extern void func_00195108();
    Seg_b053_01E01730 *s = NULL;
    Seg_b053_01E01730 *p;
    s16 i;
    f32 h;

    for (i = 0; i < 0xF; i++) {
        if (ctx->segs[i].used == 0) {
            func_00195108(&ctx->segs[i], 0x7C);
            ctx->segs[i].used = 1;
            s = &ctx->segs[i];
            i = 0xF;
        }
    }
    if (s != NULL) {
        s->pos = ctx->pos;
        s->f72 = ctx->f3B54;
        s->prev = ctx->last;
        s->f6E = ctx->f3B5A;
        if (s->prev == NULL) {
            h = ctx->height;
            s->top = h;
            s->bottom = h - 18.0f;
        } else {
            h = ctx->height;
            s->top = h;
            s->bottom = h - 18.0f;
        }
        s->prev = ctx->last;
        p = s->prev;
        if (p != NULL) {
            p->next = s;
        }
        s->f74 = 1;
        s->f76 = 1;
        ctx->last = s;
        return 1;
    }
    return 0;
}

/* shape b053:01E01890, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3B5A and 0x3B54 and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b053_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x7D4];
    Slot_b053_01E01890 s[200];
    u8 pad3A54[0xB0];
    u8 r, g, b, a;
    u8 pad3B08[0x4C];
    s16 w;
    u8 pad3B56[0x4];
    s16 v;
} Pool_b053_01E01890;

static s32 func_01E01890_b053(Pool_b053_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b053_01E01890 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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
        s->w = o->w;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b053:01E019C0, 282 insns (B053PAINT_RAIN): mode 0 sets up the packet (colours 0x60 top, 0x64 bottom, the
   scene texture); otherwise draws four 90-degree wall pieces of a ring around joint 0 (3 lower): bottom edge on the
   object's radius 0x6C and height 0x14, top edge on the parent's ring (or the object's radius 0x6A at its own height
   when it has none), each piece spanning 25 degrees */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b053_01E019C0;

typedef struct {
    Rgbaq_b053_01E019C0 c;
    f32 s, t;
    u64 xyz;
} Vtx_b053_01E019C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b053_01E019C0 v[4];
} Pkt_b053_01E019C0;

typedef struct Ring_b053_01E019C0 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 y2;
    u8 pad18[0x38];
    struct Ring_b053_01E019C0 *parent;
    u8 pad54[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 pad68[2];
    s16 r0;
    s16 r1;
    u8 pad6E[4];
    s16 ang;
} Ring_b053_01E019C0;

typedef struct {
    u8 pad0[0xC0];
    s32 rot[4];
    u8 padD0[0x10C - 0xD0];
    void *texture;
    u8 pad110[0x3B0C - 0x110];
    s32 ot;
    u8 pad3B10[0x3B34 - 0x3B10];
    f32 depth;
    u8 pad3B38[0x3B64 - 0x3B38];
    u8 sin[4];
} Scene_b053_01E019C0;

static void func_01E019C0_b053(Scene_b053_01E019C0 *g, Ring_b053_01E019C0 *o, Pkt_b053_01E019C0 *pk, s32 mode) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b053_01E019C0 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f c;
    f32 m[16];
    Vec4f t;
    Vec4f p;
    s32 i;
    Ring_b053_01E019C0 *pa;
    s16 k;
    s16 a;

    pa = o->parent;
    a = 0;
    if (mode == 0) {
        func_00109270(pk, 0, 0);
        pk->v[0].c = func_00107740(o->col0);
        pk->v[1].c = func_00107740(o->col0);
        pk->v[2].c = func_00107740(o->col1);
        pk->v[3].c = func_00107740(o->col1);
        func_00208700(pk, g->texture, 1);
        return;
    }
    func_001F5620(func_001F53A0(), 0, &p);
    t.x = p.x;
    t.y = p.y - 3.0f;
    t.z = p.z;
    func_00108EF0(m, g->rot, 0, &t);
    func_00106080(&c, 0x96, 0, &c);
    func_00108500(pk, &c, 1);
    for (i = 0; i < 4; i++) {
        if (pa != NULL) {
            k = a + pa->ang;
            q[0].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[0].z = pa->r1 * func_00108030(g->sin, k, 0);
            k = a + pa->ang - 25;
            q[1].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[1].z = pa->r1 * func_00108030(g->sin, k, 0);
            o->y = pa->y2;
        } else {
            q[0].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 1);
            q[0].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 0);
            q[1].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 1);
            q[1].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 0);
        }
        k = a + o->ang;
        q[2].x = o->r1 * func_00108030(g->sin, k, 1);
        q[2].z = o->r1 * func_00108030(g->sin, k, 0);
        k = a + o->ang - 25;
        q[3].x = o->r1 * func_00108030(g->sin, k, 1);
        q[3].z = o->r1 * func_00108030(g->sin, k, 0);
        q[0].y = o->y;
        q[1].y = o->y;
        q[2].y = o->y2;
        q[3].y = o->y2;
        if (func_00205630(q, 0x70000000, m, pk, &g->depth) != 0) {
            func_002075F0(pk, g->ot, (u32)g->depth);
        }
        a += 90;
    }
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

static void func_01E01E30_b053(u8 *ctx, Obj_b053_01E01E30 *o, void *pkt, s32 mode) {
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

/* OVL_WARM */

/* shape b053:01E01FE0, 195 insns: b159:01E01B30 cousin, b064:01E03F20's ring, 18 sectors of 20 between radius o->size
   and o->size - 1 at the object's position; mode 0 sets up the packet's texture (0x8D, page o->page), the ring itself
   re-binds the texture with frame 0x8C */

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
} Obj_b053_01E01FE0;

static void func_01E01FE0_b053(u8 *ctx, Obj_b053_01E01FE0 *o, void *pkt, s32 mode) {
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

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x8D, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x108), 1);
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
    func_00208700(pkt, *(void **)(ctx + 0x108), 1);
    func_00106080(td, 0x8C, o->page, td);
    func_00108500(pkt, td, 0);
    for (i = 0; i < 18; i++) {
        k = o->ang + a;
        q[2].x = o->size * func_00108030(ctx + 0x3B64, k, 1);
        q[2].z = o->size * func_00108030(ctx + 0x3B64, k, 0);
        q[0].x = (o->size - 1) * func_00108030(ctx + 0x3B64, k, 1);
        q[0].z = (o->size - 1) * func_00108030(ctx + 0x3B64, k, 0);
        k = o->ang + 20 + a;
        q[3].x = o->size * func_00108030(ctx + 0x3B64, k, 1);
        q[3].z = o->size * func_00108030(ctx + 0x3B64, k, 0);
        q[1].x = (o->size - 1) * func_00108030(ctx + 0x3B64, k, 1);
        q[1].z = (o->size - 1) * func_00108030(ctx + 0x3B64, k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B34)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), (u32)*(f32 *)(ctx + 0x3B34));
        }
        a += 20;
    }
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

static void func_01E022F0_b053(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
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

/* OVL_WARM */

/* shape b053:01E02490, 225 insns: b053:01E01FE0's ring as 12 flat sectors of 30 between radius o->size - 2 and
   o->size (inner edge lifted 3) under a (0.08, 1, 0.08) scale, each drawn twice: texture 0x8F with the scene
   texture (ctx+0x108), then 0x8C; mode 0 sets up texture 0x97 in the object's colour and the scene texture
   (ctx+0x10C) */

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
} Obj_b053_01E02490;

static void func_01E02490_b053(u8 *ctx, Obj_b053_01E02490 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x10];
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc.x = 0.08f;
    sc.y = 1.0f;
    sc.z = 0.08f;
    func_00108EF0(m, &sc, o->rot, &pos);
    q[0].y = 3.0f;
    q[1].y = 3.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 12; i++) {
        k = o->ang + a;
        q[2].x = (o->size - 2) * func_00108030(ctx + 0x3B64, k, 1);
        q[2].z = (o->size - 2) * func_00108030(ctx + 0x3B64, k, 0);
        q[0].x = o->size * func_00108030(ctx + 0x3B64, k, 1);
        q[0].z = o->size * func_00108030(ctx + 0x3B64, k, 0);
        k = o->ang + 30 + a;
        q[3].x = (o->size - 2) * func_00108030(ctx + 0x3B64, k, 1);
        q[3].z = (o->size - 2) * func_00108030(ctx + 0x3B64, k, 0);
        q[1].x = o->size * func_00108030(ctx + 0x3B64, k, 1);
        q[1].z = o->size * func_00108030(ctx + 0x3B64, k, 0);
        func_00106080(td, 0x8F, o->page, td);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x108), 1);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B34)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), (u32)*(f32 *)(ctx + 0x3B34));
        }
        func_00106080(td, 0x8C, o->page, td);
        func_00108500(pkt, td, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B34)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), (u32)*(f32 *)(ctx + 0x3B34));
        }
        a += 30;
    }
}
