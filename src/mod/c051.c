#include "common.h"

/* shape c051:01E00080, 197 insns: c031:01E00080 family scene start: counts ticks; on tick 3 picks the scene colour by
   its kind (0x2F4: grey, red, green, blue, yellow, magenta, cyan, pink, violet, orange, else grey), clears its alpha,
   spawns c051:01E003A0 once through 0x1E00800 (size 30, 0x2D0 = 0) and six times through 0x1E00EC0 (0x2D0 = 1) on the
   angle pairs 30/270, 270/150, 150/30 and 210/-30, -30/90, 90/210; size 15 for the first three when func_001DE540()
   is 0 and for the last three when it is 1, else 30 */

typedef struct {
    u8 pad0[0x2B4];
    u8 col[4];
    u8 pad2B8[0x10];
    f32 size;
    u8 pad2CC[4];
    f32 f2D0;
    u8 pad2D4[0x16];
    s16 a0;
    s16 a1;
    u8 pad2EE[4];
    s16 h2F2;
    s16 kind;
    u8 pad2F6[2];
    s16 t;
} Ctx_c051_01E00080;

static void func_01E00080_c051(Ctx_c051_01E00080 *g) {
    extern void c051_01E003A0(void);
    extern void c051_01E00800(Ctx_c051_01E00080 *, void (*)(void));
    extern void c051_01E00EC0(Ctx_c051_01E00080 *, void (*)(void));
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001DE540(void);
    s32 n;
    s16 k;

    n = func_001DE540();
    g->t++;
    if (g->t == 3) {
        k = g->kind;
        if (k == 0) {
            func_001076F0(g->col, 0x80, 0x80, 0x80);
        } else if (k == 1) {
            func_001076F0(g->col, 0x80, 0, 0);
        } else if (k == 2) {
            func_001076F0(g->col, 0, 0x80, 0);
        } else if (k == 3) {
            func_001076F0(g->col, 0, 0, 0x80);
        } else if (k == 4) {
            func_001076F0(g->col, 0x80, 0x80, 0);
        } else if (k == 5) {
            func_001076F0(g->col, 0x80, 0, 0x80);
        } else if (k == 6) {
            func_001076F0(g->col, 0, 0x80, 0x80);
        } else if (k == 7) {
            func_001076F0(g->col, 0x80, 0x40, 0x80);
        } else if (k == 8) {
            func_001076F0(g->col, 0x80, 0, 0xFF);
        } else if (k == 9) {
            func_001076F0(g->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(g->col, 0x80, 0x80, 0x80);
        }
        g->col[3] = 0;
        g->size = 30.0f;
        g->f2D0 = 0.0f;
        g->h2F2 = 0;
        c051_01E00800(g, c051_01E003A0);
        g->f2D0 = 1.0f;
        g->h2F2 = 1;
        if (n == 0) {
            g->size = 15.0f;
        } else {
            g->size = 30.0f;
        }
        g->a0 = 30;
        g->a1 = 270;
        c051_01E00EC0(g, c051_01E003A0);
        g->a0 = 270;
        g->a1 = 150;
        c051_01E00EC0(g, c051_01E003A0);
        g->a0 = 150;
        g->a1 = 30;
        c051_01E00EC0(g, c051_01E003A0);
        if (n == 1) {
            g->size = 15.0f;
        } else {
            g->size = 30.0f;
        }
        g->a0 = 210;
        g->a1 = -30;
        c051_01E00EC0(g, c051_01E003A0);
        g->a0 = -30;
        g->a1 = 90;
        c051_01E00EC0(g, c051_01E003A0);
        g->a0 = 90;
        g->a1 = 210;
        c051_01E00EC0(g, c051_01E003A0);
    }
}

/* shape c051:01E003A0, 124 insns: a four-colour flash timed by the scene frame (0x2F8): all four alphas grow by 0x2C
   (below 0xB0) for the first 5 frames; kind 0 fades them by 15 from frame 15 (the last ends it); other kinds grow
   0x20 by 6 on frames 6..12, by 12 on frames 13..15, then by 3 while the alphas fade by 20 */

typedef struct {
    u8 pad0[0x20];
    f32 size;
    u8 c0[4];
    u8 c1[4];
    u8 c2[4];
    u8 c3[4];
    s16 kind;
    s16 mode;
} Fx_c051_01E003A0;

typedef struct {
    u8 pad0[0x2F8];
    s16 frame;
} Scene_c051_01E003A0;

static s32 func_01E003A0_c051(Scene_c051_01E003A0 *g, Fx_c051_01E003A0 *o) {
    if (o->kind == 0) {
        if (g->frame > 14) {
            if (o->c0[3] > 0x19) {
                o->c0[3] -= 15;
            }
            if (o->c1[3] > 0x19) {
                o->c1[3] -= 15;
            }
            if (o->c2[3] > 0x19) {
                o->c2[3] -= 15;
            }
            if (o->c3[3] > 0x19) {
                o->c3[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    } else if (g->frame < 13 && g->frame > 5) {
        o->size += 6.0f;
    } else if (g->frame > 15) {
        o->size += 3.0f;
        if (o->c0[3] > 0x19) {
            o->c0[3] -= 20;
        }
        if (o->c1[3] > 0x19) {
            o->c1[3] -= 20;
        }
        if (o->c2[3] > 0x19) {
            o->c2[3] -= 20;
        }
        if (o->c3[3] > 0x19) {
            o->c3[3] -= 20;
        } else {
            o->mode = 0;
        }
    } else if (g->frame >= 13) {
        o->size += 12.0f;
    }
    if (g->frame < 5) {
        if (o->c0[3] < 0xB0) {
            o->c0[3] += 0x2C;
        }
        if (o->c1[3] < 0xB0) {
            o->c1[3] += 0x2C;
        }
        if (o->c2[3] < 0xB0) {
            o->c2[3] += 0x2C;
        }
        if (o->c3[3] < 0xB0) {
            o->c3[3] += 0x2C;
        }
    }
    return 0;
}

/* shape c051:01E00590, 155 insns, 1 copy: c051's scene manager: with a scene id (>= 0) it clears the scene, installs
   the module's step, loads texture 15, builds the sine table for 0..90 degrees, keeps the id and sets the 36-frame
   countdown; otherwise it runs the step, every live node's update callback, reads the camera point, and draws every
   live node twice at it; it returns 2 once the scene clock (0x2F8) reaches 20 with more than 2 frames left, else 8
   once the countdown runs out */

typedef struct Node_c051_01E00590 {
    u8 pad0[0x10];
    void (*draw)(void *, struct Node_c051_01E00590 *, void *, s32);
    void (*update)(void *, struct Node_c051_01E00590 *);
    u8 pad18[0x1E];
    s16 used;
    u8 pad38[8];
} Node_c051_01E00590;

typedef struct {
    u8 m0[0x40];
    u8 m[0x40];
    u8 pad80[0x30];
    Node_c051_01E00590 node[8];
    s32 count;
    u8 pad2B4[8];
    s32 ot;
    u8 pad2C0[4];
    void (*step)();
    u8 pad2C8[0x2C];
    s16 id;
    u8 pad2F6[2];
    s16 clock;
    u8 pad2FA[6];
    f32 sintab[91];
    s32 tex[16];
} Scene_c051_01E00590;


static s32 func_01E00590_c051(s32 arg0, s32 id) {
    Scene_c051_01E00590 *g = (Scene_c051_01E00590 *)arg0;
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_001E11B0(s32, s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    void (*draw)(void *, Node_c051_01E00590 *, void *, s32);
    f32 w[4];
    f32 v[4];
    u8 buf[0x90];
    s32 n;
    s32 i;
    s32 j;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4B0);
        g->step = func_01E00080_c051;
        for (j = 15; j < 16; j++) {
            g->tex[j] = func_00202BF0(4, j);
        }
        for (i = 0; i < 91; i++) {
            g->sintab[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->id = id;
        g->count = 36;
        return 0;
    }
    {
        extern void c051_01E00080();
        c051_01E00080(g, 0);
    }
    for (i = 0; i < 8; i++) {
        if (g->node[i].used != 0 && g->node[i].update != 0) {
            g->node[i].update(g, &g->node[i]);
        }
    }
    func_001F5BD0(func_001F5380(), v);
    func_001E11B0(func_001F5380() >> 8, func_001F5380() & 0xF, v);
    w[0] = v[0];
    w[1] = v[1];
    w[2] = v[2];
    for (i = 0; i < 8; i++) {
        if (g->node[i].used != 0) {
            n++;
            func_0020EB40(g->m);
            func_0020C940(g, 0, 0, w);
            func_0020BC00(g->m, g);
            draw = g->node[i].draw;
            if (g->node[i].draw != 0) {
                draw(g, &g->node[i], buf, 0);
                draw(g, &g->node[i], buf, 1);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->clock >= 20 && g->count > 2) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}


/* shape c051:01E00800, 83 insns: takes the first free of 8 effect slots (0x40 bytes, b108:01E02FF0 family), marks it with its
   index + 1, colours all four corners from the context, copies two of its values and its frame, and hooks c051:01E00950 */

typedef struct {
    u8 pad0[0x10];
    void (*cb)(void);
    s32 arg;
    f32 f18;
    u8 pad1C[4];
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    u8 c2C[4];
    u8 c30[4];
    s16 f34;
    s16 used;
    u8 pad38[8];
} Slot_c051_01E00800;

typedef struct {
    u8 pad0[0xB0];
    Slot_c051_01E00800 slots[8];
    u8 pad[0x2B4 - 0xB0 - 8 * 0x40];
    u8 rgba[4];
    u8 pad2B8[0x10];
    f32 f2C8;
    u8 pad2CC[4];
    f32 f2D0;
    u8 pad2D4[0x1E];
    s16 f2F2;
} Ctx_c051_01E00800;

static void func_01E00800_c051(Ctx_c051_01E00800 *ctx, s32 arg) {
    extern void c051_01E00950(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c051_01E00800 *s = NULL;
    s16 i;

    for (i = 0; i < 8; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x40);
            ctx->slots[i].used = i + 1;
            i = 8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c24, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c24[3] = ctx->rgba[3];
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_001076F0(s->c30, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c30[3] = ctx->rgba[3];
        s->f20 = ctx->f2D0;
        s->f18 = ctx->f2C8;
        s->f34 = ctx->f2F2;
        s->cb = c051_01E00950;
        s->arg = arg;
    }
}

/* shape c051:01E00950, 189 insns: c051:01E00C50's band drawn as a full ring of 24 quads 15 apart (going backwards),
   outer radius r + 10, inner r, outer edge at height h; mode 0 sets up the packet with frame 3 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c051_01E00950;

typedef struct {
    Rgbaq_c051_01E00950 c;
    f32 s, t;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c051_01E00950;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_c051_01E00950 v[4];
} Pkt_c051_01E00950;

typedef struct {
    u8 pad0[0x40];
    u8 mat[0x2BC - 0x40];
    s32 ot;
    u8 pad2C0[0x18];
    f32 depth;
    u8 pad2DC[0x300 - 0x2DC];
    u8 tab[0x4A8 - 0x300];
    s32 tex;
} Ctx_c051_01E00950;

typedef struct {
    u8 pad0[0x18];
    f32 r;
    u8 pad1C[4];
    f32 h;
    u8 col[4];
    u8 col2[4];
    u8 pad2C[0xC];
    s16 a0;
    s16 a1;
} Fx_c051_01E00950;

static void func_01E00950_c051(Ctx_c051_01E00950 *g, Fx_c051_01E00950 *o, Pkt_c051_01E00950 *p, s32 lit) {
    extern void func_00105D00(void *, s32, s32);
    extern Rgbaq_c051_01E00950 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    Vec4f q[4];
    s16 a;
    s32 k;

    a = 0;
    if (lit == 0) {
        func_00105D00(rm, 3, 0);
        p->flags = 0x34;
        p->size = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->flags |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 0);
        return;
    }
    q[1].y = q[0].y = o->h;
    q[2].y = q[3].y = 0.0f;
    for (k = 0; k < 24; k++) {
        q[0].x = (10.0f + o->r) * func_00108030(g->tab, a, 1);
        q[0].z = (10.0f + o->r) * func_00108030(g->tab, a, 0);
        q[2].x = o->r * func_00108030(g->tab, a, 1);
        q[2].z = o->r * func_00108030(g->tab, a, 0);
        q[1].x = (10.0f + o->r) * func_00108030(g->tab, a + 15, 1);
        q[1].z = (10.0f + o->r) * func_00108030(g->tab, a + 15, 0);
        q[3].x = o->r * func_00108030(g->tab, a + 15, 1);
        q[3].z = o->r * func_00108030(g->tab, a + 15, 0);
        if (func_00205630(q, 0x70000000, g->mat, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, (u32)g->depth);
        }
        a -= 15;
    }
}

/* shape c051:01E00C50, 156 insns: a cylinder band quad between angles o->h38 and o->h3A at radius o->f18, from 0 up to o->f20 (scene table at ctx+0x300, scene matrix at ctx+0x40); the setup pass builds the gouraud packet (bottom colour 0x28, top 0x24, texture page 2) */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c051_01E00C50;

typedef struct {
    Rgbaq_c051_01E00C50 c;
    f32 s, t;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c051_01E00C50;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_c051_01E00C50 v[4];
} Pkt_c051_01E00C50;

typedef struct {
    u8 pad0[0x40];
    u8 mat[0x2BC - 0x40];
    s32 ot;
    u8 pad2C0[0x18];
    f32 depth;
    u8 pad2DC[0x300 - 0x2DC];
    u8 tab[0x4A8 - 0x300];
    s32 tex;
} Ctx_c051_01E00C50;

typedef struct {
    u8 pad0[0x18];
    f32 r;
    u8 pad1C[4];
    f32 h;
    u8 col[4];
    u8 col2[4];
    u8 pad2C[0xC];
    s16 a0;
    s16 a1;
} Fx_c051_01E00C50;

static void func_01E00C50_c051(Ctx_c051_01E00C50 *g, Fx_c051_01E00C50 *o, Pkt_c051_01E00C50 *p, s32 lit) {
    extern void func_00105D00(void *, s32, s32);
    extern Rgbaq_c051_01E00C50 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 rm[4];

    if (lit == 0) {
        func_00105D00(rm, 2, 0);
        p->flags = 0x34;
        p->size = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->flags |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 0);
        return;
    }
    q[0].x = o->r * func_00108030(g->tab, o->a0, 1);
    q[0].z = o->r * func_00108030(g->tab, o->a0, 0);
    q[2].x = o->r * func_00108030(g->tab, o->a0, 1);
    q[2].z = o->r * func_00108030(g->tab, o->a0, 0);
    q[1].x = o->r * func_00108030(g->tab, o->a1, 1);
    q[1].z = o->r * func_00108030(g->tab, o->a1, 0);
    q[3].x = o->r * func_00108030(g->tab, o->a1, 1);
    q[3].z = o->r * func_00108030(g->tab, o->a1, 0);
    q[1].y = q[0].y = o->h;
    q[2].y = q[3].y = 0.0f;
    if (func_00205630(q, 0x70000000, g->mat, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

/* shape c051:01E00EC0, 87 insns: take a free row (8 of 0x40 bytes at 0xB0, mark = index + 1), clear it, four colours
   from the scene colour 0x2B4 with alpha 0x80, 0x20/0x18 from the scene floats 0x2D0/0x2C8, 0x38/0x3A/0x34 from
   0x2EA/0x2EC/0x2F2, callback c051:01E00C50 and arg */

typedef struct {
    u8 pad0[0x10];
    void (*cb)(void);
    s32 arg;
    f32 f18;
    u8 pad1C[4];
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    u8 c2C[4];
    u8 c30[4];
    s16 f34;
    s16 used;
    s16 f38;
    s16 f3A;
    u8 pad3C[4];
} Row_c051_01E00EC0;

typedef struct {
    u8 pad0[0xB0];
    Row_c051_01E00EC0 rows[8];
    u8 pad2B0[4];
    u8 rgb[4];
    u8 pad2B8[0x10];
    f32 f2C8;
    u8 pad2CC[4];
    f32 f2D0;
    u8 pad2D4[0x16];
    s16 f2EA;
    s16 f2EC;
    u8 pad2EE[4];
    s16 f2F2;
} Scene_c051_01E00EC0;

static void func_01E00EC0_c051(Scene_c051_01E00EC0 *g, s32 arg) {
    extern void c051_01E00C50(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c051_01E00EC0 *s = NULL;
    s16 i;

    for (i = 0; i < 8; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x40);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 8;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c24, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c24[3] = 0x80;
        func_001076F0(s->c28, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c28[3] = 0x80;
        func_001076F0(s->c2C, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c2C[3] = 0x80;
        func_001076F0(s->c30, g->rgb[0], g->rgb[1], g->rgb[2]);
        s->c30[3] = 0x80;
        s->f20 = g->f2D0;
        s->f18 = g->f2C8;
        s->f38 = g->f2EA;
        s->f3A = g->f2EC;
        s->f34 = g->f2F2;
        s->cb = c051_01E00C50;
        s->arg = arg;
    }
}
