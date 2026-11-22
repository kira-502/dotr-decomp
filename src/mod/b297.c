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

static void func_01E00080_b297(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b003:01E00920, 352 insns: b003:01E00EA0 placed at the def's s16 position instead of the object's; draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00920;

typedef struct {
    f32 u, v;
} Uv_b003_01E00920;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00920 uv;
    u64 pad18;
    Xyz_b003_01E00920 v[4];
    u64 pad60[6];
} Pk_b003_01E00920;

typedef struct {
    u64 tag;
    Pk_b003_01E00920 pk;
} Buf_b003_01E00920;

static void func_01E00920_b297(Obj_b003_01E00920 *obj, Def_b003_01E00920 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00920 buf;
    Uv_b003_01E00920 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00920 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b297((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b297:01E00EA0, 156 insns: the scene script of b297: it sets the scene colour to red 0x80 and counts g+0x3534;
   from tick 21 to 75 it puts the burst point 2 above model joint A (g+0x3516) and spawns the 0x1E02010 effect; from 81
   to 311 the same with the 0x1E011F0 and 0x1E014F0 effects; from 121 to 319 it scatters the point around joint B
   (g+0x3518) seen from the other camera and spawns the 0x1E01B70 and 0x1E01DC0 effects */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x3298];
    u8 col[4];
    u8 pad34F8[0x1E];
    s16 ja;
    s16 jb;
    u8 pad351A[0x1A];
    s16 tick;
} Ctx_b297_01E00EA0;

static void func_01E00EA0_b297(Ctx_b297_01E00EA0 *g) {
    extern void b297_01E011F0();
    extern void b297_01E014F0();
    extern void b297_01E01B70();
    extern void b297_01E01DC0();
    extern void b297_01E02010();
    extern void b297_01E03030(Ctx_b297_01E00EA0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick >= 21 && g->tick < 76) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = 2.0f + v[1];
        g->z = v[2];
        for (i = 0; i < 1; i++) {
            b297_01E03030(g, b297_01E02010, 0);
        }
    }
    if (g->tick > 80 && g->tick < 312) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = 2.0f + v[1];
        g->z = v[2];
        for (i = 0; i < 1; i++) {
            b297_01E03030(g, b297_01E011F0, 0);
        }
        for (i = 0; i < 1; i++) {
            b297_01E03030(g, b297_01E014F0, 0);
        }
    }
    if (g->tick > 120 && g->tick < 320) {
        func_001F5620(func_001F5380(), g->jb, v);
        g->x = v[0] + func_0019A5C8() % 20 - 10.0f;
        g->y = v[1] + func_0019A5C8() % 40 - 20.0f;
        g->z = v[2] + func_0019A5C8() % 20 - 10.0f;
        for (i = 0; i < 1; i++) {
            b297_01E03030(g, b297_01E01B70, 0);
        }
        b297_01E03030(g, b297_01E01DC0, 0);
    }
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E01110_b297(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b297:01E011F0, 175 insns: b297:01E014F0's glow, grey 0x50 of size 45 growing by 2 (by 4 below 90), rise 5..9, holds for
   30..54 ticks fading in by 18 to 0x92; on start hC is the angle from joint g+0x3514 to g+0x3516, each tick h4 turns
   by a fortieth of the camera depth difference between func_001F5380's and func_001F53A0's views, and h30 grows by
   the rise */

typedef struct {
    u8 pad0[0x3514];
    s16 ja;
    s16 jb;
} Game_b297_01E011F0;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b297_01E011F0;

static s32 func_01E011F0_b297(Game_b297_01E011F0 *g, Glow_b297_01E011F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 45;
        o->kind = 0;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 3;
        o->h6 = func_0019A5C8() % 25 + 30;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 18;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f38 < 90) {
            o->f38 += 2;
        }
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 40.0f;
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 2;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b297:01E014F0, 175 insns: b008:01E01660's glow aimed between two joints: grey 0x70 of size 50, rise 5..9, holds for
   30..39 ticks fading in by 0x20 to 0x40; on start hC is the angle from joint g+0x3514 to g+0x3516, each tick h4 turns
   by a fortieth of the camera depth difference between func_001F5380's and func_001F53A0's views, and h30 grows by
   the rise */

typedef struct {
    u8 pad0[0x3514];
    s16 ja;
    s16 jb;
} Game_b297_01E014F0;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b297_01E014F0;

static s32 func_01E014F0_b297(Game_b297_01E014F0 *g, Glow_b297_01E014F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 50;
        o->kind = 0;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 30;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 40.0f;
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b297:01E017B0, 240 insns: b257:01E024F0's random-colour glow on joints ctx+0x3514/0x3516, rise 3..12, held
   11..20 ticks fading in by 0x10 to 0x80, then out by 15 */

typedef struct {
    u8 pad0[0x3514];
    s16 ja;
    s16 jb;
} Game_b297_01E017B0;

typedef struct {
    s16 h0;
    u8 pad2[2];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b297_01E017B0;

static s32 func_01E017B0_b297(Game_b297_01E017B0 *g, Glow_b297_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];
    s32 k;

    if (o->mode == 1) {
        o->f38 = 100;
        o->kind = 0;
        k = (s16)(func_0019A5C8() % 3);
        if (k == 0) {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
        } else if ((s16)k == 1) {
            func_001076F0(o->col, 0x40, 0, 0x80);
        } else {
            func_001076F0(o->col, 0x80, 0x10, 0x10);
        }
        o->h30 = func_0019A5C8() % 50 + 100;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 11;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 40.0f;
    if (o->tick == 0) {
        o->h4 = func_001A22C0(o->h4 + 17.0f * v[0].z);
    }
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        o->h0 += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 3) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 1;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad00[2];
    s16 h2;
    u8 pad04[2];
    s16 h6;
    s16 h8;
    u8 pad0A[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b003_01E01C70;

static s32 func_01E01B70_b297(s32 unused, Obj_b003_01E01C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 45;
        o->h34 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 300 + 130;
        o->h3A = func_0019A5C8() % 360;
        o->hE = 0;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 2;
        o->h6 = func_0019A5C8() % 10 + 15;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h32 != 0) {
        if (o->h38 < 90) {
            o->h38 += 2;
        }
    }
    if (o->h32 % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->h32 != 0) {
        o->h30 += o->hE;
    }
    if (o->h32 != 0) {
        o->h38 += 2;
    }
    o->h2++;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->h32++;
    return 0;
}

/* shape b003:01E01EC0, 146 insns, 4 copies: step of a rising puff: on state 1 sets a grey colour, random start, angle,
   size, layers and lifetime; fades in by 0x12, then out by 9 until it ends; grows, climbs and spins randomly. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[2];
    s16 layers;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b003_01E01EC0;

static s32 func_01E01DC0_b297(void *arg0, Obj_b003_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0x2D;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->pos = func_0019A5C8() % 300 + 130;
        o->ang = func_0019A5C8() % 360;
        o->speed = 0;
        o->h8 = func_0019A5C8() % 35;
        o->layers = func_0019A5C8() % 3 + 2;
        o->life = func_0019A5C8() % 10 + 15;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x12;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 0x5A) {
            o->size += 2;
        }
    }
    if (o->t % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    if (o->t != 0) {
        o->size += 2;
    }
    o->y++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

/* shape b297:01E02010, 178 insns: b297:01E014F0's glow in grey 0x50 placed 10 off along z by the scene flag (0x3530) and
   5 lower; it grows by 2 to 90 and then 2 more a tick, without the camera drift */

typedef struct {
    u8 pad0[0x3514];
    s16 ja;
    s16 jb;
    u8 pad3518[0x18];
    s16 flag;
} Game_b297_01E02010;

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b297_01E02010;

static s32 func_01E02010_b297(Game_b297_01E02010 *g, Glow_b297_01E02010 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 45;
        o->kind = 0;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 15;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 3;
        o->h6 = func_0019A5C8() % 15 + 10;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        if (g->flag != 0) {
            o->h4 -= 10;
        } else {
            o->h4 += 10;
        }
        o->h2 -= 5;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f38 < 90) {
            o->f38 += 2;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 2;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E022E0_b297(void) {
    return 0;
}

/* shape b257:01E031C0, 55 insns: a flash: on start f38 0x12C, colours (0xF0,0xF0,0xF0) and (0xF0,0xF0,0x10) with
   alpha 0x10, a random direction; alpha grows by 0x60 for the first 2 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b257_01E031C0;

static s32 func_01E022F0_b297(s32 arg0, Flash_b257_01E031C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b297:01E023D0, 92 insns: b582:01E03470 family scene light at ctx+0x34C0 (orange 4/2/0, height 70): raised by 0.2 to 1, lowered by 0.1 and ended; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b297_01E023D0;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x4];
    s32 state;
} Light_b297_01E023D0;

typedef struct {
    u8 pad[0x34c0];
    Light_b297_01E023D0 l;
} Game_b297_01E023D0;

static s32 func_01E023D0_b297(Game_b297_01E023D0 *g, Obj_b297_01E023D0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 0.0f;
        g->l.r = 4.0f;
        g->l.g = 2.0f;
        g->l.b = 0.0f;
        g->l.w20 = 0;
        g->l.h = 70.0f;
        g->l.level = 0.0f;
        g->l.x = o->x;
        g->l.y = o->y;
        g->l.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->l.level > 0.1f) {
        g->l.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b297:01E02540, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x34F0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x34F0];
    s32 state;
} Game_b297_01E02540;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b297_01E02540;

static s32 func_01E02540_b297(Game_b297_01E02540 *g, Fade_b297_01E02540 *o) {
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

static s32 func_01E02600_b297(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03180_b297;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03188_b297;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b297:01E02650 (b297), 631 insns, 1 copy: b297 scene manager (b003:01E02650 form): setup (five models,
   textures, two s8 jitter tables, eight random 0..3 values), step B297_W_S and 200 slots of eleven kinds, draw seven
   kinds; scene code from the timer */

typedef struct Fx_b297_01E02650 {
    s16 x;
    u8 pad2[0xA];
    s16 hC;
    u8 padE[0x16];
    void *fn;
    u8 pad28[0xA];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b297_01E02650;

typedef struct Q_b297_01E02650 {
    f32 a, b, c, d;
} Q_b297_01E02650;

typedef union R_b297_01E02650 {
    Q_b297_01E02650 q;
    s16 s[8];
} R_b297_01E02650;

typedef struct Scene_b297_01E02650 {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    R_b297_01E02650 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    s16 hC0[8];
    u8 padD0[8];
    u8 camD8[0x260 - 0xD8];
    s32 tex[16];
    Fx_b297_01E02650 fx[200];
    s32 tex2[4];
    u8 pad34B0[0x34F0 - 0x34B0];
    s32 state;
    u8 pad34F4[8];
    s32 ot2;
    u8 pad3500[0x3514 - 0x3500];
    s16 model0;
    s16 model1;
    s16 model2;
    s16 model3;
    s16 model4;
    u8 pad351E[0x3530 - 0x351E];
    s16 flag;
    s16 id;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
    u8 pad3736[2];
    u8 cam[0x38B0 - 0x3738];
} Scene_b297_01E02650;

static s32 func_01E02650_b297(s32 arg0, s32 id) {
    Scene_b297_01E02650 *g = (Scene_b297_01E02650 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern f32 D_01E03180_b297;
    extern f32 D_01E03188_b297;
    extern void b297_01E00EA0();
    extern s32 func_01E01110_b297();
    extern s32 func_01E011F0_b297();
    extern s32 func_01E014F0_b297();
    extern s32 func_01E017B0_b297();
    extern s32 func_01E01B70_b297();
    extern s32 func_01E01DC0_b297();
    extern s32 func_01E02010_b297();
    extern s32 func_01E022E0_b297();
    extern s32 func_01E022F0_b297();
    extern s32 func_01E023D0_b297();
    extern s32 func_01E02540_b297();
    extern s32 func_01E02600_b297();
    extern void func_01E00920_b297();
    s32 n;
    Vec4f v;
    Q_b297_01E02650 r0;
    Q_b297_01E02650 r1;
    Q_b297_01E02650 r2;
    Q_b297_01E02650 r3;
    Q_b297_01E02650 r4;
    Q_b297_01E02650 r5;
    Q_b297_01E02650 r6;
    Q_b297_01E02650 r7;
    s32 info[4];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x38B0);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->state = 0x17E;
        func_001F6160(func_001F53A0(), info);
        g->flag = (s32)(info[1] / 180.0f);
        g->model0 = func_001F5560(func_001F53A0(), 0xB, 1);
        g->model1 = func_001F5560(func_001F53A0(), 8, 0);
        g->model2 = func_001F5560(func_001F5380(), 1, 1);
        g->model3 = func_001F5560(func_001F53A0(), 0x47, 0);
        g->model4 = func_001F5560(func_001F53A0(), 0x4E, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 4; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 256; i++) {
            g->rnd2[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->rnd2[i] = -(func_0019A5C8() % 15);
        }
        for (i = 180; i < 256; i++) {
            g->rnd2[i] = 0;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    b297_01E00EA0(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E01110_b297) {
                func_01E01110_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E011F0_b297) {
                func_01E011F0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E014F0_b297) {
                func_01E014F0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E017B0_b297) {
                func_01E017B0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01B70_b297) {
                func_01E01B70_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01DC0_b297) {
                func_01E01DC0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02010_b297) {
                func_01E02010_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E022F0_b297) {
                func_01E022F0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E023D0_b297) {
                func_01E023D0_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02540_b297) {
                func_01E02540_b297(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02600_b297) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03180_b297;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03188_b297;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 200; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E011F0_b297) {
                g->texture = g->tex2[2];
                func_00106080(&r0, 0x14, g->fx[i].h34, 0);
                g->rect.q = r0;
                g->rect.s[0] = 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x3F;
                g->rect.s[3] = 0x3F;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b297(g, &g->fx[i], 0x20, g->rnd);
                g->count = 0;
                g->texture = g->tex[0];
                func_00106080(&r1, 0x14, g->fx[i].h34, 0);
                g->rect.q = r1;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    func_01E00920_b297(g, &g->fx[i], 0x20, g->rnd);
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E014F0_b297) {
                g->texture = g->tex[0];
                func_00106080(&r2, 0x14, g->fx[i].h34, 0);
                g->rect.q = r2;
                g->count = 4;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b297(g, &g->fx[i], 0x20, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E017B0_b297) {
                g->texture = g->tex2[2];
                func_00106080(&r3, 0x14, g->fx[i].h34, 0);
                g->rect.q = r3;
                g->rect.s[0] = 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x3F;
                g->rect.s[3] = 0x3F;
                g->count = 6;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b297(g, &g->fx[i], 2, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E01B70_b297) {
                g->texture = g->tex2[3];
                func_00106080(&r4, 0x14, g->fx[i].h34, 0);
                g->rect.q = r4;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b297(g, &g->fx[i], 0x10, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E01DC0_b297) {
                g->texture = g->tex2[1];
                g->rect.s[0] = g->fx[i].h34 * 32 + 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x1F;
                g->rect.s[3] = 0x3D;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b297(g, &g->fx[i], 0x20, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E02010_b297) {
                g->texture = g->tex2[0];
                func_00106080(&r5, 0x14, g->fx[i].h34, 0);
                g->rect.q = r5;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    func_01E00920_b297(g, &g->fx[i], 0x10, g->rnd2);
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E022E0_b297) {
                g->texture = g->tex[14];
                func_00106080(&r6, 0x8C, g->fx[i].h34, 0);
                g->rect.q = r6;
                g->rect.s[1] = 0xF;
                g->rect.s[2] >>= 1;
                g->rect.s[3] >>= 1;
                g->texture = g->tex[15];
                func_00106080(&r7, 0x96, g->fx[i].h34, 0);
                g->rect.q = r7;
            }
        }
    }
    if (g->state != 0) {
        g->state--;
    }
    if (g->timer == 90) {
        return 1;
    }
    if (g->timer == 350) {
        return 3;
    }
    if (g->timer > 100 && g->timer < 345) {
        return 6;
    }
    if (g->state <= 0) {
        return 8;
    }
    return 0;
}

/* shape b297:01E03030, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x352E and the two arguments; returns 1 if a
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
} Slot_b297_01E03030;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b297_01E03030 s[200];
    u8 pad34A0[0x54];
    u8 r, g, b, a;
    u8 pad34F8[0x36];
    s16 v;
} Pool_b297_01E03030;

static s32 func_01E03030_b297(Pool_b297_01E03030 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b297_01E03030 *s = NULL;
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
    } else {
        ret = 0;
    }
    return ret;
}
