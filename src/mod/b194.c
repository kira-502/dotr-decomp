#include "common.h"

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

static void func_01E00080_b194(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00260_b194(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

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

static void func_01E00330_b194(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b194:01E00780, 312 insns: the b194 module's event step (B194_W_S): scene colour (0x80, 0, 0, 0); counts ticks
   (ctx+0x3E2E); from 52 to 132 six b194:01E01760 (slots 0..5) a tick, ten rounds of them at tick 22; 50..86 two
   b194:01E01010 at the two hands (0x3E18, 0x3E1A) jittered on x by -5..4 (sign flips from 73) and up by 0..14; at 91
   ten b194:01E00E80 per slot 0 and 1 and fifty b194:01E015C0 at the first hand; 85..95 b194:01E01180 */

typedef struct {
    u8 pad0[0x80];
    Vec4f p;
    u8 pad90[0x3DD4 - 0x90];
    u8 col[4];
    u8 pad3DD8[0x3E18 - 0x3DD8];
    s16 hand0;
    s16 hand1;
    u8 pad3E1C[0x3E2A - 0x3E1C];
    s16 slot;
    u8 pad3E2C[2];
    s16 timer;
} Ctx_b194_01E00780;

static void func_01E00780_b194(Ctx_b194_01E00780 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_01E021A0_b194();
    extern s32 func_01E00E80_b194();
    extern s32 func_01E01010_b194();
    extern s32 func_01E01180_b194();
    extern s32 func_01E015C0_b194();
    extern s32 func_01E01760_b194();
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer < 133) {
        if (g->timer >= 52) {
            g->slot = 0;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 1;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
        }
        if (g->timer >= 52) {
            g->slot = 2;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 3;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 4;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 5;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
        }
    }
    if (g->timer == 22) {
        for (i = 0; i < 10; i++) {
            g->slot = 0;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 1;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
        }
    }
    if (g->timer == 22) {
        for (i = 0; i < 10; i++) {
            g->slot = 2;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 3;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 4;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
            g->slot = 5;
            func_01E021A0_b194(g, func_01E01760_b194, 0);
        }
    }
    if (g->timer > 49 && g->timer < 87) {
        func_001F5620(func_001F53A0(), g->hand0, &v);
        g->p.x = v.x - (func_0019A5C8() % 10 - 5);
        if (g->timer >= 73) {
            g->p.x = v.x + (func_0019A5C8() % 10 - 5);
        }
        g->p.y = v.y + func_0019A5C8() % 15;
        g->p.z = v.z;
        func_01E021A0_b194(g, func_01E01010_b194, 0);
        func_001F5620(func_001F53A0(), g->hand1, &v);
        g->p.x = v.x - (func_0019A5C8() % 10 - 5);
        if (g->timer >= 73) {
            g->p.x = v.x + (func_0019A5C8() % 10 - 5);
        }
        g->p.y = v.y + func_0019A5C8() % 15;
        g->p.z = v.z;
        func_01E021A0_b194(g, func_01E01010_b194, 0);
    }
    if (g->timer == 91) {
        func_001F5620(func_001F53A0(), g->hand0, &v);
        g->p.x = v.x;
        g->p.y = v.y;
        g->p.z = v.z;
        g->slot = 0;
        for (i = 0; i < 10; i++) {
            func_01E021A0_b194(g, func_01E00E80_b194, 0);
        }
        g->slot = 1;
        for (i = 0; i < 10; i++) {
            func_01E021A0_b194(g, func_01E00E80_b194, 0);
        }
        for (i = 0; i < 50; i++) {
            func_01E021A0_b194(g, func_01E015C0_b194, 0);
        }
    }
    if (g->timer >= 85 && g->timer < 96) {
        func_01E021A0_b194(g, func_01E01180_b194, 0);
    }
}

/* shape b194:01E00C60, 134 insns, 2 copies: a violet wisp (b018:01E01F60 twin): set up once (random heading, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18, its frame every third up to 7; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x3E34];
    u8 trig[1];
} World_b194_01E00C60;

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
} Wisp_b194_01E00C60;

static s32 func_01E00C60_b194(World_b194_01E00C60 *w, Wisp_b194_01E00C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
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

/* shape b194:01E00E80, 99 insns: on start 0x38 = 8, rotation (0..0x3FFF plus a zero offset, random), variant 0..6, 0x6 = 1, colour by
   kind 0x30 (orange / cyan); alpha grows by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0xF and
   by 15 while the game counter 0x3DD0 is below 10; 0x38 grows by 2 */

typedef struct {
    u8 pad0[0x3DD0];
    s32 count;
} Game_b194_01E00E80;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[8];
    s32 rot[2];
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b194_01E00E80;

static s32 func_01E00E80_b194(Game_b194_01E00E80 *g, Fx_b194_01E00E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->mode == 1) {
        o->f38 = 8;
        base = 0;
        o->rot[0] = func_0019A5C8() % 0x4000 + base;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f6 = 1;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0xF) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    o->tick++;
    o->f38 += 2;
    return 0;
}

/* shape b194:01E01010, 89 insns: colour (0x80, 0x40, 0); on start reads the model angle, 0x6 = 20 (game step 0x3E2E
   from 0x55) or -20 (from 0x4E), alpha 0; alpha grows by 0x40 (below 0x80) for 2 ticks, then fades by 9 and stops;
   from step 0x55 0x6 counts up; 0x38 = 50; fades by 13 while the counter 0x3DD0 is below 15; 0xE grows by 5 */

typedef struct {
    u8 pad0[0x3DD0];
    s32 count;
    u8 pad3DD4[0x5A];
    s16 step;
} Game_b194_01E01010;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[6];
    s16 fE;
    u8 pad10[4];
    s32 f14;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b194_01E01010;

static s32 func_01E01010_b194(Game_b194_01E01010 *g, Fx_b194_01E01010 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    func_001076F0(o->col, 0x80, 0x40, 0);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (g->step >= 0x55) {
            o->f6 = 20;
        } else if (g->step >= 0x4E) {
            o->f6 = -20;
        }
        o->f14 = 0;
        o->f34 = 0;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->step >= 0x55) {
        o->f6++;
    }
    o->f38 = 50;
    o->tick++;
    if (g->count < 15) {
        if (o->col[3] > 0xE) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
    }
    o->fE += 5;
    return 0;
}

/* OVL_WARM */

/* shape b194:01E01180, 202 insns: reads the model angle and keeps whether its turn / 180 is non-zero; on start 0x38 =
   10..19, no spin, variant 0..6, 0x6 = 5..19, random 0x3A; before game step 0x60 it sits on joint A (g+0x3E18); alpha
   up by 0x40 (below 0x80) for 2 ticks, then fades by 13 after 0x38 passes 25 and by 15 while the counter 0x3DD0 is
   below 10; colour (0x20, 0x20, 0); aims at joint B (g+0x3E1C): pitch from the flat and full distances
   (func_001082B0) times 180, mirrored by the turn, before step 0x60 */

typedef struct {
    u8 pad0[0x3DD0];
    s32 count;
    u8 pad3DD4[0x3E18 - 0x3DD4];
    s16 ja;
    u8 pad3E1A[2];
    s16 jb;
    u8 pad3E1E[0x3E2E - 0x3E1E];
    s16 step;
} Game_b194_01E01180;

typedef struct {
    s16 x, y, z;
    s16 f6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b194_01E01180;

static s32 func_01E01180_b194(Game_b194_01E01180 *g, Fx_b194_01E01180 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001A6C60(f32);
    extern s16 func_001082B0(s32, s32);
    f32 v[8];
    s32 ang[4];
    s32 turn;
    f32 *q;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 r;
    s16 l;
    s16 a;

    func_001F6160(func_001F53A0(), ang);
    turn = (s16)(ang[1] / 180.0f);
    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 10 + 10;
        o->w18 = 0;
        o->w10 = 0;
        o->w14 = 0;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f6 = func_0019A5C8() % 15 + 5;
        o->f3A = func_0019A5C8() % 360;
    }
    func_001F5620(func_001F53A0(), g->ja, v);
    func_001F5620(func_001F53A0(), g->jb, q = (f32 *)(u32)&v[4]);
    if (g->step < 0x60) {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->f38 > 25) {
            if (o->col[3] > 14) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 16) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x20, 0x20, 0);
    dx = v[0] - q[0];
    dy = v[1] - v[5];
    dz = v[2] - v[6];
    r = func_001A6C60(dx * dx + dz * dz);
    l = func_001A6C60(dx * dx + (dy * dy + dz * dz));
    a = func_001082B0(r, l);
    if (g->step < 0x60) {
        if (turn != 0) {
            o->w10 = a * 180;
        } else {
            o->w10 = -a * 180;
        }
    }
    o->tick++;
    o->f38++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E014B0_b194(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    return 0;
}

/* shape b194:01E015C0, 101 insns: an orange drifting mote: frame 13, sub-frame 2, random angles; full alpha for 10 frames, then
   down by 10 until it ends; drifts 9 along its angle and bobs 9 by its second angle */

typedef struct {
    u8 pad0[0x3E34];
    u8 sin[1];
} Game_b194_01E015C0;

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
} Obj_b194_01E015C0;

static s32 func_01E015C0_b194(Game_b194_01E015C0 *g, Obj_b194_01E015C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0xD;
        o->sub = 2;
        func_001076F0(o->c0, 0x60, 0x40, 0);
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
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 9.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 9.0f * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + 9.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b194:01E01760, 175 insns: b112:01E01A60's puff (lilac 0x3F/0x30/0x3F for kinds 0-1, grey 0x10 else), size from 10 growing 5 to 40, frame up to 7 every other tick, angles 0..359 / 0..89; alpha up by 0x20 to 0x60 for 3 ticks, then down by 9; for its first 5 ticks sits on its tracked point (ctx+0x3E18 by kind; kinds 2+ only for 3); drifts 8 along the heading and 2 up */

typedef struct {
    u8 pad0[0x3E18];
    s16 ids[4];
    u8 pad3E20[0x3E34 - 0x3E20];
    u8 trig[1];
} Game_b194_01E01760;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b194_01E01760;

static s32 func_01E01760_b194(Game_b194_01E01760 *g, Fx_b194_01E01760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];

    if (o->mode == 1) {
        if (o->kind < 2) {
            func_001076F0(o->col, 0x3F, 0x30, 0x3F);
        } else {
            func_001076F0(o->col, 0x10, 0x10, 0x10);
        }
        o->f38 = 10;
        o->heading = func_0019A5C8() % 360;
        o->f34 = 0;
        o->h6 = func_0019A5C8() % 90;
        o->mode = 2;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick < 6) {
        func_001F5620(func_001F53A0(), g->ids[o->kind], v);
        if (o->kind < 2) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        } else if (o->tick < 4) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        }
    }
    if (o->f38 < 40) {
        o->f38 += 5;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->h8 = o->h8 + 8.0f * func_00108030(g->trig, o->heading, 0);
    o->hA = o->hA + 2.0f * func_00108030(g->trig, o->h6, 1);
    o->hC = o->hC + 8.0f * func_00108030(g->trig, o->heading, 1);
    return 0;
}

/* shape b194:01E01A20, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3DD0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3DD0];
    s32 state;
} Game_b194_01E01A20;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b194_01E01A20;

static s32 func_01E01A20_b194(Game_b194_01E01A20 *g, Fade_b194_01E01A20 *o) {
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

/* shape b194:01E01AE0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E02F00_b194;
extern f32 D_01E02F08_b194;

static s32 func_01E01AE0_b194(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02F00_b194;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02F08_b194;
    func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b194:01E01B30 (b194), 411 insns, 1 copy: b194 scene manager (b378:01E01D10 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 160-frame countdown, takes six model handles and loads
   textures 2 and 14..15; otherwise it seeds the 10-point trail at frame 45 and steps it, runs the module step and
   every live node update (B194_OBJ_MOVE_201_ written out in place), draws every live node (twice by its drawer, or
   one KEMU_PAINT_1 square), grows the scene scale by 0.01 up to 0.5 after frame 20, counts down and returns 1 / 4 / 2
   at frames 81 / 125 / 105, 6 in 92..99, 8 once the countdown runs out */

typedef struct Fx_b194_01E01B30 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[0x8];
} Fx_b194_01E01B30;

typedef struct Spr_b194_01E01B30 {
    s32 texture;
    s32 tex;
    s32 c;
    s32 mode;
} Spr_b194_01E01B30;

typedef struct Scene_b194_01E01B30 {
    u8 pad0[0xC0];
    f32 sx, sy, sz;
    u8 padCC[0x24];
    s32 tex[16];
    u8 pad130[0x524 - 0x130];
    Fx_b194_01E01B30 fx[220];
    u8 pad3C24[0x3D20 - 0x3C24];
    Vec_b004_01E00B40 pts[10];
    u8 pad3DC0[0x10];
    s32 count;
    u8 pad3DD4[8];
    s32 ot;
    u8 pad3DE0[0x3E18 - 0x3DE0];
    s16 model[6];
    u8 pad3E24[8];
    s16 id;
    s16 timer;
    u8 pad3E30[4];
    u8 cam[0x170];
} Scene_b194_01E01B30;

static s32 func_01E01B30_b194(s32 arg0, s32 id) {
    Scene_b194_01E01B30 *g = (Scene_b194_01E01B30 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_01E00780_b194();
    extern s32 func_01E00C60_b194();
    extern s32 func_01E00E80_b194();
    extern s32 func_01E01010_b194();
    extern s32 func_01E01180_b194();
    extern s32 func_01E014B0_b194();
    extern s32 func_01E015C0_b194();
    extern s32 func_01E01760_b194();
    extern s32 func_01E01A20_b194();
    extern s32 func_01E01AE0_b194();
    extern void b194_01E022C0();
    extern void b194_01E02550();
    extern void b194_01E027D0();
    extern void b194_01E02AB0();
    extern void b194_01E02CD0();
    s32 j;
    s32 n;
    Vec4f v;
    Spr_b194_01E01B30 s;
    Vec4f p;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;
    Vec_b004_01E00B40 *q;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3FA0);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 160;
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x18, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0xB, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 1, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x33, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0x21, 0);
        for (i = 2; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    if (g->timer == 45) {
        q = g->pts;
        func_001F5620(func_001F53A0(), g->model[0], &p);
        for (i = 0; i < 9; i++, q++) {
            q->x = p.x;
            q->y = p.y;
            q->z = p.z;
        }
    }
    func_01E00260_b194(&g->pts[9], 10, g->model[2]);
    func_01E00780_b194(g, 0);
    for (j = 0; j < 220; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == func_01E00C60_b194) {
                func_01E00C60_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00E80_b194) {
                func_01E00E80_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01010_b194) {
                func_01E01010_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01180_b194) {
                func_01E01180_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E014B0_b194) {
                func_01E014B0_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E015C0_b194) {
                func_01E015C0_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01760_b194) {
                func_01E01760_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01A20_b194) {
                func_01E01A20_b194(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01AE0_b194) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02F00_b194;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02F08_b194;
                func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00C60_b194) {
                s.texture = g->tex[2];
                s.c = 0;
                s.tex = 0x14;
                s.mode = 0;
                func_01E00080_b194(g->ot, (Obj_b058_01E00080 *)&g->fx[i], (Spr_b058_01E00080 *)&s);
            }
            if (g->fx[i].fn == func_01E00E80_b194) {
                b194_01E02550(g, &g->fx[i], buf, 0);
                b194_01E02550(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01010_b194) {
                b194_01E022C0(g, &g->fx[i], buf, 0);
                b194_01E022C0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01180_b194) {
                b194_01E027D0(g, &g->fx[i], buf, 0);
                b194_01E027D0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E014B0_b194) {
                b194_01E02AB0(g, &g->fx[i], buf, 0);
                b194_01E02AB0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E015C0_b194) {
                b194_01E02CD0(g, &g->fx[i], buf, 0);
                b194_01E02CD0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01760_b194) {
                b194_01E02CD0(g, &g->fx[i], buf, 0);
                b194_01E02CD0(g, &g->fx[i], buf, 1);
            }
        }
    }
    if (g->timer > 20) {
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
    if (g->timer == 81) {
        return 1;
    }
    if (g->timer == 125) {
        return 4;
    }
    if (g->timer == 105) {
        return 2;
    }
    if (g->timer > 91 && g->timer < 100) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b194:01E021A0, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3E2A and the two arguments; returns 1 if a
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
} Slot_b194_01E021A0;

typedef struct {
    u8 pad[0x80];
    u8 m[0x4A4];
    Slot_b194_01E021A0 s[220];
    u8 pad3C24[0x1B0];
    u8 r, g, b, a;
    u8 pad3DD8[0x52];
    s16 v;
} Pool_b194_01E021A0;

static s32 func_01E021A0_b194(Pool_b194_01E021A0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b194_01E021A0 *s = NULL;
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

/* shape b194:01E022C0, 164 insns: b117:01E02C00 family upright sprite (texture 0x14 and the scene texture at ctx+0xF8 for callback b194:01E01760, else 0x9B and ctx+0x12C) facing the camera turn, size x 1, sheared by hE and h6, scaled 0.1 */

/* OVL_WARM */

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 dx, dy, dz;
    s16 hE;
    u8 pad10[0x14];
    void *cb;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b194_01E022C0;

typedef struct {
    u8 pad0[0xF8];
    s32 tex2;
    u8 padT[0x12C - 0xF8 - 4];
    s32 tex;
} Scene_b194_01E022C0;

static void func_01E022C0_b194(Scene_b194_01E022C0 *g, Fx_b194_01E022C0 *o, void *p, s32 lit) {
    extern void b194_01E01760(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 a[4];
    s32 v;
    f32 ax, ay, az;

    v = (s32)func_00207500();
    if (lit == 0) {
        if (o->cb == b194_01E01760) {
            func_00106080(rm, 0x14, o->h34, rm);
        } else {
            func_00106080(rm, 0x9B, o->h34, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        if (o->cb == b194_01E01760) {
            func_00208700(p, g->tex2, 1);
            return;
        }
        func_00208700(p, g->tex, 1);
        return;
    }
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_001F6160(func_001F53A0(), a);
    rot[1] = -(a[1] - 16384.0f);
    rot[0] = 0;
    rot[2] = 0;
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, 1.0f);
    quad[0].x = 0.0f;
    quad[2].x = 0.0f;
    func_00107070(quad, 0, o->hE);
    quad[1].y += o->h6;
    quad[3].y += o->h6;
    func_00107070(quad, 1, o->h6);
    func_00108F90(quad, p, m, v);
}

/* shape b194:01E02550, 158 insns: variant of b112:01E039F0 (flat ring of 9 quads, each 2 wide) with the texture at 0x12C, the
   target/depth/trig table at 0x3DDC/0x3E04/0x3E34, and an additive blend (0x80, 0x42) when the anim's w is set */

typedef struct {
    f32 x, y, z, w;
} Vec_b194_01E02550;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b194_01E02550;

typedef struct {
    u8 pad00[0x12C];
    s32 texture;
    u8 pad130[0x3DDC - 0x130];
    s32 target;
    u8 pad3DE0[0x3E04 - 0x3DE0];
    f32 depth;
    u8 pad3E08[0x3E34 - 0x3E08];
    u8 trig[1];
} Game_b194_01E02550;

static void func_01E02550_b194(Game_b194_01E02550 *g, Anim_b194_01E02550 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b194_01E02550 quad[4];
    Vec_b194_01E02550 pos;
    Vec_b194_01E02550 scale;
    f32 m[16];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        if (an->w != 0) {
            func_002086D0(p, 0x8000000042);
        }
        pos.x = an->x;
        pos.y = an->y;
        pos.z = an->z;
        scale.x = 1.0f;
        scale.y = 1.5f;
        scale.z = 1.0f;
        func_00108EF0(m, &scale, an->rot, &pos);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        for (k = 0; k < 9; k++) {
            a = an->start + j;
            quad[2].x = an->radius * func_00108030(g->trig, a, 1);
            quad[2].z = an->radius * func_00108030(g->trig, a, 0);
            quad[0].x = 0.0f;
            quad[0].z = 0.0f;
            a = j + (an->start + 2);
            quad[3].x = an->radius * func_00108030(g->trig, a, 1);
            quad[3].z = an->radius * func_00108030(g->trig, a, 0);
            quad[1].x = 0.0f;
            quad[1].z = 0.0f;
            if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
            j += 40;
        }
    }
}

/* shape b194:01E027D0, 182 insns: b195:01E02A40's fan of 9 thin triangles (span 1) with the rim raised to the object's
   h6, scaled 1 x 1.5 x 1 at the object's position; mode 0 sets up the packet with texture 0x97. Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b194_01E027D0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b194_01E027D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b194_01E027D0 c;
    struct {
        u64 tc;
        Xyz_b194_01E027D0 p;
    } v[4];
} Pkt_b194_01E027D0;

typedef struct {
    u8 pad0[0x12C];
    void *texture;
    u8 pad130[0x3CAC];
    s32 ot;
    u8 pad3DE0[0x24];
    f32 dep;
    u8 pad3E08[0x2C];
    u8 trig[1];
} Ctx_b194_01E027D0;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b194_01E027D0;

static void func_01E027D0_b194(Ctx_b194_01E027D0 *c, Fan_b194_01E027D0 *o, Pkt_b194_01E027D0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b194_01E027D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 t;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00330_b194((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = o->h6;
    quad[3].y = o->h6;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + 1);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b194:01E02AB0, 133 insns: b120:01E03DF0's two-pass quad with 9 quads: mode 0 sets the material (frame 0x97, two
   colours, scene texture 0x12C); other modes place it at the object with a 0.4 x-scale and a -0x4000 turn, then draw each of
   the 9 quads at scene 0x130 against the matrix at 0x40 (depth 0x3E04, packet list 0x3DDC) */

typedef struct {
    f32 x, y, z, w;
} Vec_b194_01E02AB0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b194_01E02AB0;

typedef struct {
    Rgbaq_b194_01E02AB0 c;
    u64 st;
    u64 xyz;
} Vtx_b194_01E02AB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b194_01E02AB0 v[4];
} Pkt_b194_01E02AB0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    s32 r0;
    s32 r1;
    s32 r2;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
} Anim_b194_01E02AB0;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0xAC];
    s32 texture;
    Vec_b194_01E02AB0 quad[9][4];
    u8 pad370[0x3A6C];
    s32 target;
    u8 pad3DE0[0x24];
    f32 depth;
} Game_b194_01E02AB0;

static void func_01E02AB0_b194(Game_b194_01E02AB0 *g, Anim_b194_01E02AB0 *an, Pkt_b194_01E02AB0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b194_01E02AB0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b194_01E02AB0 pos;
    f32 rm[4];
    s32 rot[4];
    Vec_b194_01E02AB0 sc;
    f32 m[16];
    s16 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020EB40(g->m);
        func_00106DD0(&pos, an->x, an->y, an->z);
        sc.x = 0.4f;
        sc.y = 1.0f;
        sc.z = 1.0f;
        rot[0] = an->r0 - 0x4000;
        rot[1] = 0;
        rot[2] = an->r2;
        func_0020C940(m, &sc, rot, &pos);
        func_0020BC00(g->m, m);
        for (i = 0; i < 9; i++) {
            if (func_00205630(g->quad[i], 0x70000000, g->m, p, &g->depth) != 0) {
                func_00109380(p, 0);
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape b194:01E02CD0, 134 insns: b112:01E04260 with the handler b194:01E01760 and scene textures at 0xF8 / 0x12C */


typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x16];
    void *fn;
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b194_01E02CD0;

static void func_01E02CD0_b194(u8 *ctx, Obj_b194_01E02CD0 *o, void *pkt, s32 mode) {
    extern s32 b194_01E01760();
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
    f32 dx;
    f32 dy;
    f32 dz;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        if (o->fn == (void *)b194_01E01760) {
            func_00106080(td, 0x14, o->page, td);
        } else {
            func_00106080(td, 0x9B, o->page, td);
        }
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        if (o->fn == (void *)b194_01E01760) {
            func_00208700(pkt, *(void **)(ctx + 0xF8), 1);
            return;
        }
        func_00208700(pkt, *(void **)(ctx + 0x12C), 1);
        return;
    }
    if (o->fn == (void *)b194_01E01760) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)&rot);
    dx = o->vx;
    dy = o->vy;
    dz = o->vz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = o->x + dx;
    pos.y = o->y + dy;
    pos.z = o->z + dz;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}
