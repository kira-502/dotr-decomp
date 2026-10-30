#include "common.h"

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

static void func_01E00080_b272(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b272 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E00920_b272(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b272((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* shape b272:01E00BE0, 167 insns: the effect scene's step: counts the frame (0x451A); from frame 36 to 180 it spawns a
   0x1E00E80 scattered +-15 around and up to 9 below joint 0x44E4; from 220 to 350 two 0x1E00FE0 scattered +-20 around
   the other model's joint 0x44F4 at a height of 70..99 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4284];
    s16 j0;
    u8 pad44E6[0xE];
    s16 j1;
    u8 pad44F6[0x24];
    s16 t;
} Scene_b272_01E00BE0;

static void func_01E00BE0_b272(Scene_b272_01E00BE0 *g) {
    extern void b272_01E00E80(void);
    extern void b272_01E00FE0(void);
    extern s32 b272_01E019E0(Scene_b272_01E00BE0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);

    g->t++;
    if (g->t >= 36 && g->t < 181) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.x += func_0019A5C8() % 30 - 15;
        g->pos.y -= func_0019A5C8() % 10;
        g->pos.z += func_0019A5C8() % 30 - 15;
        b272_01E019E0(g, (s32)b272_01E00E80, 0);
    }
    if (g->t >= 220 && g->t < 351) {
        func_001F5620(func_001F5380(), g->j1, &g->pos);
        g->pos.x += func_0019A5C8() % 40 - 20;
        g->pos.y = func_0019A5C8() % 30 + 70;
        g->pos.z += func_0019A5C8() % 40 - 20;
        b272_01E019E0(g, (s32)b272_01E00FE0, 0);
        func_001F5620(func_001F5380(), g->j1, &g->pos);
        g->pos.x += func_0019A5C8() % 40 - 20;
        g->pos.y = func_0019A5C8() % 30 + 70;
        g->pos.z += func_0019A5C8() % 40 - 20;
        b272_01E019E0(g, (s32)b272_01E00FE0, 0);
    }
}

/* shape b272:01E00E80, 86 insns: on start 0x8/0xA = 10, variant 3, f34 0.5, colour white, random 0x5A, random spin
   direction (0x50); alpha grows by 0x60 (below 0xC0) for 20 ticks, then fades by 9 and stops; f14 grows by 1 after the
   first tick; func_00205C40 on the rotation at 0x20; 0x5A turns by 5 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[8];
    f32 f14;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x18];
    s16 dir;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b272_01E00E80;

static s32 func_01E00E80_b272(s32 arg0, Fx_b272_01E00E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 10;
        o->fA = 10;
        o->f56 = 3;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->dir = (func_0019A5C8() >> 4) % 2;
        o->mode = 2;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f14 += 1.0f;
    }
    func_00205C40((s32)o->rot);
    if (o->dir == 0) {
        o->f5A += 5;
    } else {
        o->f5A -= 5;
    }
    o->tick++;
    return 0;
}

/* shape b272:01E00FE0, 118 insns: rising spark: on start size 10/10, frame 3, white, random heading and turn direction;
   alpha +0x60 (below 0xC0) for 15 ticks, then it grows by 15 up to 100 and finally spawns the module's burst
   (01E011C0) at its position; it shrinks by 2 every third tick, rises 1 per tick and turns 5 a tick. */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x42B2];
    s16 dir;
} Game_b272_01E00FE0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x18];
    s16 turn;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 heading;
    u8 pad5C[4];
    u8 col[4];
} Fx_b272_01E00FE0;

static s32 func_01E00FE0_b272(Game_b272_01E00FE0 *g, Fx_b272_01E00FE0 *o) {
    extern void b272_01E011C0(void);
    extern void b272_01E019E0(void *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 10;
        o->fA = 10;
        o->f56 = 3;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->heading = func_0019A5C8() % 360;
        o->turn = (func_0019A5C8() >> 4) % 2;
        o->mode = 2;
    }
    if (o->tick < 15) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else {
        if (o->fA < 100) {
            o->fA += 15;
        } else {
            g->pos = o->pos;
            g->dir = o->turn;
            b272_01E019E0(g, b272_01E011C0, 0);
            o->mode = 0;
        }
        if (o->f8 > 0 && o->tick % 3 == 1) {
            o->f8 -= 2;
        }
    }
    if (o->tick != 0) {
        o->pos.y -= 1.0f;
    }
    func_00205C40((s32)o->rot);
    if (o->turn == 0) {
        o->heading += 5;
    } else {
        o->heading -= 5;
    }
    o->tick++;
    return 0;
}

/* shape b272:01E011C0, 123 insns: a white flickering cross: sizes 0 growing (width by 3, height by 6, both to 30) for 5 frames,
   random sub-frame and frame 0..7; alpha up by 0x60 for 5 frames, then down by 9 while the width shrinks by 6; sinks 0.5 a
   frame once started; turns 5 one way or the other by kind */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[0x20];
    s16 kind;
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b272_01E011C0;

static s32 func_01E011C0_b272(void *arg0, Obj_b272_01E011C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0;
        o->h = 0;
        o->sub = (func_0019A5C8() >> 4) % 8;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
    }
    if (o->t < 5) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->w > 0) {
            o->w -= 6;
        }
    }
    if (o->t < 5) {
        if (o->h < 0x1E) {
            o->h += 6;
        }
        if (o->w < 0x1E) {
            o->w += 3;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    if (o->t != 0) {
        o->y -= 0.5f;
    }
    func_00205C40((s32)o->rot);
    if (o->kind == 0) {
        o->ang += 5;
    } else {
        o->ang -= 5;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E013B0_b272(void) {
    return 0;
}

/* shape b272:01E013C0 (b272), 390 insns, 1 copy: b272 scene manager in b422:01E02020 form: setup (seven joints, one
   type-4 and two type-5 textures, two s8 jitter tables), step b272:01E00BE0 and every slot except the empty handler,
   draw the b272:01E00E80, b272:01E00FE0 and b272:01E011C0 sparks; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xA];
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b272_01E013C0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x1A];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b272_01E013C0 fx[0x96];
    u8 pad4440[0x50];
    s32 tex[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad44F0[4];
    s16 cam;
    u8 pad44F6[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b272_01E013C0;

static s32 func_01E013C0_b272(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E00BE0_b272();
    Scene_b272_01E013C0 *g = (Scene_b272_01E013C0 *)arg0;
    s16 n;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4890);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 400;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E00BE0_b272(g, 0);
    for (k = 0; k < 0x96; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E013B0_b272) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    n++;
                }
            }
        }
    }
    for (k = 0; k < 0x96; k++) {
        if (g->fx[k].used != 0) {
            m++;
            if (g->fx[k].fn == (s32 (*)())func_01E00E80_b272) {
                g->tex88 = g->tex[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hBE = 5;
                v.x = g->fx[k].pos.x + 4.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b272((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E00FE0_b272) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = g->fx[k].h52;
                v.x = g->fx[k].pos.x + 4.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b272((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E011C0_b272) {
                g->tex88 = g->tex[0];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hBE = 5;
                v.x = g->fx[k].pos.x + 4.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b272((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 225) {
        return 1;
    }
    if (g->frame == 385) {
        return 4;
    }
    if (g->frame == 375) {
        return 2;
    }
    if (g->frame > 235 && g->frame < 370) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b272:01E019E0, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b272_01E019E0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b272_01E019E0;

typedef struct Obj_b272_01E019E0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b272_01E019E0 slots[0x96];
    u8 padB[0x74];
    u8 rgba[4];
    u8 padC[0x5A];
    s16 fB2B0;
} Obj_b272_01E019E0;

static s32 func_01E019E0_b272(Obj_b272_01E019E0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b272_01E019E0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}
