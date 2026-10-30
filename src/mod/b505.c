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

static void func_01E00080_b505(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b056:01E00920, 240 insns, 5 copies: draws a row of small camera-facing sprites (count, or 20) at a given position,
   each shaken by a per-entry table offset that grows along the row, turned by an extra axis; one texture
   corner mode for the whole row (module helper, shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b056_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b056_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b056_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b056_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b056_01E00920;

static void func_01E00920_b505(Obj_b056_01E00920 *o, Spr_b056_01E00920 *s, s8 *tbl, Vec4f pos) {
    extern Rgbaq_b056_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f e;
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b056_01E00920 pkt __attribute__((aligned(8)));
    s8 *j;
    s32 h;
    s16 i;
    s16 n;
    Pkt_b056_01E00920 *p;

    func_00207500();
    p = (Pkt_b056_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    pkt.c.q = 0;
    pkt.v[0].f = 0;
    pkt.v[1].f = 0;
    pkt.v[2].f = 0;
    pkt.v[3].f = 0;
    pkt.c = func_00107740(s->col);
    func_01E00080_b505((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    if (o->count != 0) {
        n = o->count;
    } else {
        n = 20;
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 0, o->xD8);
        func_00109100(quad, rot, 1, o->xD8);
        j = tbl + i;
        h = i >> 1;
        e.x = j[s->off] / 20.0f * (s->w30 + h);
        e.y = j[s->off + 100] / 20.0f * (s->w30 + h);
        e.z = j[s->off + 180] / 20.0f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b505:01E00CE0, 69 insns: sets the scene colour to red 0x80 and counts its timer; on frame 1 spawns a
   b505:01E010C0 effect, and on frames 1..199 spawns a b505:01E00E00 effect at each of two model joints (b566:01E014D0
   family) */

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2B84 - 0x25C];
    u8 r, g, b, a;
    u8 pad2B88[0x24];
    s16 joint0;
    s16 joint1;
    u8 pad2BB0[0x1A];
    s16 t;
} Scene_b505_01E00CE0;

static void func_01E00CE0_b505(Scene_b505_01E00CE0 *s) {
    extern void b505_01E00E00(void);
    extern void b505_01E010C0(void);
    extern s32 b505_01E01920(Scene_b505_01E00CE0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;

    s->r = 0x80;
    s->g = 0;
    s->b = 0;
    s->a = 0;
    s->t++;
    if (s->t == 1) {
        b505_01E01920(s, b505_01E010C0, 0);
    }
    if (s->t > 0 && s->t < 0xC8) {
        func_001F5620(func_001F53A0(), s->joint0, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        b505_01E01920(s, b505_01E00E00, 0);
        func_001F5620(func_001F53A0(), s->joint1, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        b505_01E01920(s, b505_01E00E00, 0);
    }
}

/* shape b505:01E00E00, 176 insns: b056:01E02890 family grey spark: frame 7..26, height 10..159 rising 7..16 a tick,
   random angle turning 2 one way or the other, width 0..29, hold 30..44; alpha up by 25 to 0x80, then down by 20; the
   sub-frame steps to 6 except every 15th tick, it jitters up/down 1..4 every tick and moves 4 a tick along z, back
   when the scene flag (0x2BC6) is set */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 z;
    s16 hold;
    s16 w;
    s16 dir;
    u8 padC[2];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b505_01E00E00;

typedef struct {
    u8 pad0[0x2BC6];
    s16 flag;
} Scene_b505_01E00E00;

static s32 func_01E00E00_b505(Scene_b505_01E00E00 *g, Obj_b505_01E00E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 20 + 7;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 150 + 10;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 10 + 7;
        o->w = func_0019A5C8() % 30;
        o->dir = func_0019A5C8() % 2;
        o->hold = func_0019A5C8() % 15 + 30;
        o->sub = 0;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x19;
        }
    } else if (o->c0[3] > 0x15) {
        o->c0[3] -= 0x14;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    if (o->t % 15 != 0) {
        if (o->sub < 6) {
            o->sub++;
        }
    }
    if (o->t % 2 == 1) {
        o->h2 += (s16)(func_0019A5C8() % 4 + 1);
    } else {
        o->h2 -= (s16)(func_0019A5C8() % 4 + 1);
    }
    o->t++;
    if (o->dir != 0) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    if (g->flag != 0) {
        o->z -= 4;
    } else {
        o->z += 4;
    }
    return 0;
}

/* shape b505:01E010C0, 37 insns: pulse: alpha grows by 10 up to 0xA0, then (phase 1) fades by 10; at the bottom it rises
   again, clearing 0x36 once the game value at 0x2BCA passes 0xD2; colour (0x5F, 0x3F, 0x3F) */

typedef struct {
    u8 pad0[0x2BCA];
    s16 v;
} Game_b505_01E010C0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 phase;
    u8 pad32[4];
    s16 f36;
} Fx_b505_01E010C0;

static s32 func_01E010C0_b505(Game_b505_01E010C0 *g, Fx_b505_01E010C0 *o) {
    if (o->phase == 0) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 10;
        } else {
            o->phase = 1;
        }
    } else if (o->col[3] > 0xB) {
        o->col[3] -= 10;
    } else {
        if (g->v > 0xD2) {
            o->f36 = 0;
        }
        o->phase = 0;
    }
    func_001076F0(o->col, 0x5F, 0x3F, 0x3F);
    return 0;
}

/* shape b505:01E01160, 92 insns: b582:01E03470 family scene light at ctx+0x2880 (orange 4/2/0, range 128, height 120): raised by 0.2 to 1, lowered by 0.1 and ended; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b505_01E01160;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x2d4];
    s32 state;
} Light_b505_01E01160;

typedef struct {
    u8 pad[0x2880];
    Light_b505_01E01160 l;
} Game_b505_01E01160;

static s32 func_01E01160_b505(Game_b505_01E01160 *g, Obj_b505_01E01160 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 128.0f;
        g->l.r = 4.0f;
        g->l.g = 2.0f;
        g->l.b = 0.0f;
        g->l.w20 = 0;
        g->l.h = 120.0f;
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

/* shape b505:01E012E0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2B80 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2B80];
    s32 state;
} Game_b505_01E012E0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b505_01E012E0;

static s32 func_01E012E0_b505(Game_b505_01E012E0 *g, Fade_b505_01E012E0 *o) {
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

static s32 func_01E013A0_b505(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E01A80_b505;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E01A88_b505;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b505:01E013F0 (b505), 329 insns, 1 copy: scene manager: init models/textures, step and draw 150 effects,
   return phase by timer */

typedef struct Fx_b505_01E013F0 {
    s16 x, y, z;
    u8 pad6[0x1E];
    void *fn;
    u8 col[4];
    u8 pad2C[4];
    s16 phase;
    u8 pad32[2];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b505_01E013F0;

typedef struct Q_b505_01E013F0 {
    f32 a, b, c, d;
} Q_b505_01E013F0;

typedef struct Scene_b505_01E013F0 {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    Q_b505_01E013F0 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 camD8[0x2C0 - 0xD8];
    s32 tex[16];
    Fx_b505_01E013F0 fx[150];
    u8 pad2880[0x2B60 - 0x2880];
    s32 tex2[8];
    s32 state;
    u8 pad2B84[8];
    s32 ot2;
    u8 pad2B90[0x1C];
    s16 model[5];
    u8 pad2BB6[4];
    s16 model5;
    u8 pad2BBC[0xA];
    s16 flag;
    s16 id;
    s16 timer;
    s8 rnd[256];
    u8 cam[0x174];
} Scene_b505_01E013F0;

static s32 func_01E013F0_b505(s32 arg0, s32 id) {
    Scene_b505_01E013F0 *g = (Scene_b505_01E013F0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_01E00CE0_b505();
    extern s32 func_01E00E00_b505();
    extern s32 func_01E010C0_b505();
    extern s32 func_01E01160_b505();
    extern s32 func_01E012E0_b505();
    extern s32 func_01E013A0_b505();
    extern void func_01E00920_b505();
    s32 n;
    Vec4f v;
    Q_b505_01E013F0 r;
    s32 info[4];
    u8 m[0x90] __attribute__((aligned(8)));
    s32 ot;
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x2E40);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->state = 255;
        g->model[0] = func_001F5560(func_001F53A0(), 0x11, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x15, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x39, 0);
        g->model5 = func_001F5560(func_001F5380(), 1, 0);
        for (i = 11; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 1; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), info);
        g->flag = (s32)(info[1] / 180.0f);
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E00CE0_b505(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E00E00_b505) {
                func_01E00E00_b505(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E010C0_b505) {
                if (g->fx[i].phase == 0) {
                    if (g->fx[i].col[3] < 0xA0) {
                        g->fx[i].col[3] += 10;
                    } else {
                        g->fx[i].phase = 1;
                    }
                } else if (g->fx[i].col[3] > 0xB) {
                    g->fx[i].col[3] -= 10;
                } else {
                    if (g->timer > 0xD2) {
                        g->fx[i].used = 0;
                    }
                    g->fx[i].phase = 0;
                }
                func_001076F0(g->fx[i].col, 0x5F, 0x3F, 0x3F);
            }
            if (g->fx[i].fn == func_01E01160_b505) {
                func_01E01160_b505(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E012E0_b505) {
                func_01E012E0_b505(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E013A0_b505) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E01A80_b505;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E01A88_b505;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00E00_b505) {
                g->texture = g->tex2[0];
                func_00106080(&r, 0x14, g->fx[i].h34, 0);
                g->rect = r;
                v.x = g->fx[i].x;
                v.y = g->fx[i].y;
                v.z = g->fx[i].z;
                g->count = 3;
                g->mode = 0;
                func_01E00920_b505(g, &g->fx[i], g->rnd, v);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E010C0_b505) {
                ot = g->ot2;
                func_00107990(m, g->fx[i].col, 0);
                func_001092E0(m, 0);
                func_001094F0(m);
                func_002075F0(m, ot, 0);
            }
        }
    }
    if (g->state != 0) {
        g->state--;
    }
    if (g->timer == 90) {
        return 1;
    }
    if (g->timer == 230) {
        return 4;
    }
    if (g->timer == 220) {
        return 2;
    }
    if (g->timer > 100 && g->timer < 215) {
        return 6;
    }
    if (g->state <= 0) {
        return 8;
    }
    return 0;
}

/* shape b505:01E01920, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2BC4 and the two arguments; returns 1 if a
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
} Slot_b505_01E01920;

typedef struct {
    u8 pad[0x250];
    u8 m[0xB0];
    Slot_b505_01E01920 s[150];
    u8 pad2880[0x304];
    u8 r, g, b, a;
    u8 pad2B88[0x3C];
    s16 v;
} Pool_b505_01E01920;

static s32 func_01E01920_b505(Pool_b505_01E01920 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b505_01E01920 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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
