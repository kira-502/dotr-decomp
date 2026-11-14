#include "common.h"

/* shape c056:01E00080, 111 insns: sets up the scene's 22 models (ids 0..10 and 256..266): object 0x170 + i x 0x70 gets a
   random size 1..5 (0x54), 0x28 -2..12, 0x34 0x100..0x18FF, 0x38 -0x3FF..0x3FF, is registered with the model (0x4 and
   0x24 cleared), tagged from 0x40E0 + i x 0x10 and coloured; flagged models are switched, and func_00107310 runs for
   models func_001F5EC0 accepts */

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x1C];
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    s32 w34;
    s32 w38;
    u8 pad3C[4];
    f32 scale[3];
    u8 pad4C[8];
    f32 f54;
    u8 pad58[8];
    u8 col[4];
    u8 pad64[0xC];
} Obj_c056_01E00080;

typedef struct {
    u8 tag[0x10];
} Tag_c056_01E00080;

typedef struct {
    u8 pad0[0x170];
    Obj_c056_01E00080 obj[22];
    u8 padB10[0x40E0 - 0xB10];
    Tag_c056_01E00080 tags[22];
} Scene_c056_01E00080;

static void func_01E00080_c056(Scene_c056_01E00080 *g) {
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern s32 func_001F5EC0(s32);
    extern void func_00107310(s32, s32, s32);
    s16 i;
    Obj_c056_01E00080 *p;
    s32 id;

    for (i = 0; i < 22; i++) {
        id = i;
        if (id > 10) {
            id += 0xF5;
        }
        p = &g->obj[i];
        p->f54 = (func_0019A5C8() % 26 + 9) / 6;
        p->w28 = func_0019A5C8() % 8 + 5;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        func_001F5BD0(id, p);
        p->w4 = 0;
        func_001F5B70(id, p);
        p->w24 = 0;
        func_001F5CA0(id, &g->tags[i]);
        func_001F5E40(id, p->col);
        if (func_001F5AF0(id) != 0) {
            func_001F5970(id, 1);
        }
        if (func_001F5EC0(id) != 0) {
            func_00107310(id, 0, 1);
        }
    }
}

/* shape c056:01E00240, 70 insns: sound voice k (k + 0xF5 above 10) while the game counter at 0x4478 is below 10:
   if it plays, set its volume byte to 0x80 and (unless bit k of 0x447C) fade it to 0.15; if it is ready, aim it at
   the game's 16-byte slot 0x40E0[k], clear p->4 and attach p, and (unless bit k) start it (0x18) */

typedef struct {
    u8 pad0[0x40E0];
    u8 slot[0x39][16];
    u8 pad4470[8];
    s32 count;
    u32 mask;
} Game_c056_01E00240;

typedef struct {
    u8 pad0[4];
    s32 f4;
} P_c056_01E00240;

static s32 func_01E00240_c056(Game_c056_01E00240 *g, P_c056_01E00240 *p, s32 k) {
    extern s32 func_001F5EC0(s32);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    extern void func_00107370(s32, s32, f32);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_00107650(s32, s32);
    u8 v[4];
    s32 ch;

    ch = k;
    if (k > 10) {
        ch = k + 0xF5;
    }
    if (g->count < 10) {
        if (func_001F5EC0(ch) != 0) {
            func_001F6490(ch, v);
            v[3] = 0x80;
            func_001F63E0(ch, v);
            if (!((g->mask >> k) & 1)) {
                func_00107370(ch, 0, 0.15f);
            }
        }
        if (func_001F5AF0(ch) != 0) {
            func_001F5C40(ch, g->slot[k]);
            p->f4 = 0;
            func_001F5B70(ch, p);
            if (!((g->mask >> k) & 1)) {
                func_00107650(ch, 0x18);
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00360_c056);

/* shape c056:01E00800, 258 insns: scene manager. code >= 0 initialises (clear 0x4730 bytes, textures 14-15 and 2,
   the 12-step sin/cos tables at 0, 30 .. and 30, 60 .., code, timer 0x88, the step function, the pad state);
   otherwise runs the scene step, then (from phase 8 on) every live slot's update, a one-shot hook, and every live
   slot's two draw passes with its own (or for callback 0x1E03FE0 the scene's) transform; before phase 8 the 22
   cards are shown by the pad bits, after it the 22 objects run their 0x1E00360 (timer > 10) or 0x1E00240 step;
   the timer counts down, 2 at 8, 8 when done */

typedef struct {
    u8 pad0[0x60];
    f32 pos[4];
    u8 pad70[0x28];
    s32 (*draw)(void *, void *, void *, s32);
    void (*fn)(void *, void *);
    u8 padA0[4];
    s16 used;
    u8 padA6[0x1A];
} Slot_c056_01E00800;

typedef struct {
    u8 b[0x70];
} Obj_c056_01E00800;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x40];
    u8 pad80[0x10];
    s32 tex[16];
    u8 padD0[0x10];
    u8 rot[0x10];
    u8 padF0[0x170 - 0xF0];
    Obj_c056_01E00800 obj[22];
    u8 padB10[0xC60 - 0x170 - 22 * 0x70];
    Slot_c056_01E00800 slot[70];
    u8 pad40E0[0x4478 - 0xC60 - 70 * 0xC0];
    s32 timer;
    u32 bits;
    u8 pad4480[8];
    s32 ot;
    u8 pad448C[8];
    void (*hook)(void *);
    u8 pad4498[0x26];
    s16 code;
    u8 pad44C0[2];
    s16 phase;
    u8 pad44C4[0xC];
    u8 b44D0[0x190];
    f32 s[12];
    f32 c[12];
    f32 s2[12];
    f32 c2[12];
} Ctx_c056_01E00800;

static s32 func_01E00800_c056(s32 arg0, s32 code) {
    Ctx_c056_01E00800 *g = (Ctx_c056_01E00800 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00107C10(void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern s32 func_001F5380();
    extern void func_00107180(s32, s32, s32, s32);
    extern void func_00107280(s32, void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void c056_01E00080(void *);
    extern void c056_01E03090(void *, s32);
    extern void c056_01E00240(void *, void *, s32);
    extern void c056_01E00360(void *, void *, s32);
    extern void c056_01E03FE0(void *, void *);
    s32 n;
    u8 pkt[0x90];
    s32 (*draw)(void *, void *, void *, s32);
    s32 i;
    s16 k;
    s32 d;
    Ctx_c056_01E00800 *q;
    s32 d2;
    s32 m;
    f32 a;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x4730);
        for (k = 14; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        g->tex[2] = func_00202BF0(4, 2);
        func_00107C10(g->b44D0);
        d2 = 30;
        for (i = 0, d = 0, q = g; i < 12; i++) {
            a = 3.1415927f * d / 180.0f;
            q->s[0] = func_001A6898(a);
            q->c[0] = func_001A6A88(a);
            a = 3.1415927f * d2 / 180.0f;
            q->s2[0] = func_001A6898(a);
            q->c2[0] = func_001A6A88(a);
            d += 30;
            q = (Ctx_c056_01E00800 *)((f32 *)q + 1);
            d2 += 30;
        }
        g->code = code;
        g->timer = 0x88;
        c056_01E00080(g);
        g->bits = func_001F5380();
        return 0;
    }
    c056_01E03090(g, 0);
    if (g->phase >= 8) {
        for (i = 0; i < 70; i++) {
            if (g->slot[i].used != 0) {
                if (g->slot[i].fn != NULL) {
                    g->slot[i].fn(g, &g->slot[i]);
                }
            }
        }
        if (g->hook != NULL) {
            g->hook(g);
            g->hook = NULL;
        }
        for (i = 0; i < 70; i++) {
            if (g->slot[i].used != 0) {
                n++;
                func_0020EB40(g->m40);
                if (g->slot[i].fn == c056_01E03FE0) {
                    func_0020C940(g, NULL, g->rot, NULL);
                } else {
                    func_0020C940(g, NULL, NULL, g->slot[i].pos);
                }
                func_0020BC00(g->m40, g);
                draw = g->slot[i].draw;
                if (draw != NULL) {
                    draw(g, &g->slot[i], pkt, 0);
                    draw(g, &g->slot[i], pkt, 1);
                }
            }
        }
    }
    if (g->phase <= 7) {
        for (i = 0; i < 22; i++) {
            m = i;
            if (i > 10) {
                m = i + 245;
            }
            func_00107180(m, 0, g->timer, 1);
            if (!((g->bits >> (21 - i)) & 1)) {
                func_00107280(m, &g->obj[i], 0);
            }
        }
    } else if (g->timer > 10) {
        for (i = 0; i < 22; i++) {
            c056_01E00360(g, &g->obj[i], i);
        }
    } else {
        for (i = 0; i < 22; i++) {
            c056_01E00240(g, &g->obj[i], i);
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->timer == 8) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape c056:01E00C10, 15 insns: spawn an effect entity from the context's pool (kind 0x46) and store arg in it */

typedef struct Ent_c056_01E00C10 {
    u8 pad0[0x9C];
    s32 arg;
} Ent_c056_01E00C10;

typedef struct Ctx_c056_01E00C10 {
    u8 pad0[0xC60];
    u8 pool[1];
} Ctx_c056_01E00C10;

static void func_01E00C10_c056(Ctx_c056_01E00C10 *ctx, s32 arg) {
    Ent_c056_01E00C10 *e = (Ent_c056_01E00C10 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        e->arg = arg;
    }
}

/* shape c056:01E00C50, 54 insns, 1 copy: spawn an effect entity, random angle % 360; its callback is
   c056:01E02560 */

typedef struct Col_c056_01E00C50 {
    u8 r, g, b, a;
} Col_c056_01E00C50;

typedef struct Ent_c056_01E00C50 {
    u8 pad0[0x64];
    f32 f64;
    u8 pad68[0x30];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E00C50 col0;
    Col_c056_01E00C50 col1;
    u8 padB4[4];
    s16 fB8;
    u8 padBA[2];
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00C50;

typedef struct Ctx_c056_01E00C50 {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    u8 pad44BA[2];
    s16 f44BC;
} Ctx_c056_01E00C50;

extern void c056_01E02560(void);

static void func_01E00C50_c056(Ctx_c056_01E00C50 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c056_01E00C50 *e = (Ent_c056_01E00C50 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = 0;
        e->f64 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBC = ctx->f44BC;
        e->fBE = func_0019A5C8() % 360;
        e->cb = c056_01E02560;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
    }
}

/* shape c056:01E00D30, 127 insns: c056:01E012A0's trail link with the scene's colour (ctx+0x4480), the height split
   by kind (0 and 1 get a floor 22 below, never under 0), ctx+0x44B8 copied, and the module's 0x1E015A0 callback */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E00D30;

typedef struct Ent_c056_01E00D30 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[8];
    Vec4f a;
    u8 pad50[0x10];
    Vec4f v;
    Vec4f b;
    u8 pad80[0x10];
    struct Ent_c056_01E00D30 *prev;
    struct Ent_c056_01E00D30 *next;
    void (*cb)(void);
    s32 arg;
    u8 padA0[6];
    s16 fA6;
    u8 padA8[4];
    Col_c056_01E00D30 col0;
    Col_c056_01E00D30 col1;
    u8 padB4[4];
    s16 fB8;
    s16 fBA;
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00D30;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E00D30 *last;
    u8 pad4490[0x449C - 0x4490];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    s16 f44BA;
    s16 f44BC;
    u8 pad44BE[0xA];
    s16 f44C8;
} Ctx_c056_01E00D30;

static void func_01E00D30_c056(Ctx_c056_01E00D30 *ctx, s32 arg) {
    extern void c056_01E015A0(void);
    extern void func_001076F0();
    Ent_c056_01E00D30 *e = (Ent_c056_01E00D30 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E00D30 *p;
    f32 h;

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->prev = ctx->last;
        e->fA6 = ctx->f44C8;
        if (e->fA6 == 0) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 22.0f;
            if (e->f24 < 0.0f) {
                e->f34 = e->f24 = 0.0f;
            }
        } else if (e->fA6 == 1) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 22.0f;
            if (e->f24 < 0.0f) {
                e->f34 = e->f24 = 0.0f;
            }
        }
        e->prev = ctx->last;
        p = e->prev;
        if (p != NULL) {
            e->a = p->a;
            e->b = p->b;
            p->next = e;
        }
        e->fB8 = ctx->f44B8;
        e->cb = c056_01E015A0;
        e->arg = arg;
        e->fBC = ctx->f44BC;
        e->fBE = 1;
        ctx->last = e;
    }
}

/* shape c056:01E00F30, 106 insns: spawns one blue effect (handler c056:01E02020) from the scene pool: colours it with the scene
   alpha, scales it, puts it at the anchor point (copying x and z first when the mode is 0), picks a random flip and angle and
   copies the mode, a setting and the argument */

typedef struct {
    f32 x, y, z, w;
} V4_c056_01E00F30;

typedef struct {
    f32 x, y, z;
} V3_c056_01E00F30;

typedef struct {
    u8 pad0[0x118];
    V4_c056_01E00F30 pt;
} Anchor_c056_01E00F30;

typedef struct {
    u8 pad0[0x40];
    V4_c056_01E00F30 pos;
    u8 pad50[0x20];
    V4_c056_01E00F30 at;
    u8 pad80[0x10];
    s32 mode;
    u8 pad94[4];
    void *fn;
    s32 arg;
    f32 flip;
    u8 padA4[2];
    s16 hA6;
    u8 padA8[4];
    u8 c0[4];
    u8 c1[4];
    u8 padB4[4];
    s16 ang;
    s16 hBA;
} Fx_c056_01E00F30;

typedef struct {
    u8 pad0[0xC60];
    u8 pool[0x4270 - 0xC60];
    Anchor_c056_01E00F30 anchor;
    u8 pad[0x4483 - 0x4270 - sizeof(Anchor_c056_01E00F30)];
    u8 alpha;
    u8 pad4484[8];
    s32 mode;
    u8 pad4490[0xC];
    f32 sx, sy, sz;
    u8 pad44A8[0x12];
    s16 h44BA;
    u8 pad44BC[0xC];
    s16 h44C8;
} Scene_c056_01E00F30;

static void func_01E00F30_c056(Scene_c056_01E00F30 *g, s32 arg) {
    extern void c056_01E02020(void);
    extern Fx_c056_01E00F30 *func_00106A00(void *, void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107E40(f32, f32, f32, void *);
    Anchor_c056_01E00F30 *a;
    Fx_c056_01E00F30 *p;

    a = &g->anchor;
    if (a != NULL) {
        p = func_00106A00(g, g->pool, 0x46, 0);
        if (p != NULL) {
            func_001076F0(p->c0, 0xF0, 0xF0, 0x80);
            p->c0[3] = g->alpha;
            p->c1[3] = g->alpha;
            func_00107E40(g->sx, g->sy, g->sz, p);
            if (g->mode == 0) {
                p->at.x = a->pt.x;
                p->at.z = a->pt.z;
                p->at = a->pt;
                p->pos = p->at;
            } else {
                p->at = a->pt;
                p->pos = p->at;
            }
            p->flip = func_0019A5C8() % 2;
            p->hBA = g->h44BA;
            p->ang = func_0019A5C8() % 360;
            p->mode = g->mode;
            p->hA6 = g->h44C8;
            p->arg = arg;
            p->fn = c056_01E02020;
        }
    }
}

/* shape c056:01E010E0, 53 insns: spawns a green glow (c056:01E00C50 family): colours 0x20/0x38/0x24 with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02E10 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E010E0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E010E0 col0;
    Col_c056_01E010E0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E010E0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E010E0;

static void func_01E010E0_c056(Ctx_c056_01E010E0 *ctx, s32 arg) {
    extern void c056_01E02E10(void);
    extern void func_001076F0();
    Ent_c056_01E010E0 *e = (Ent_c056_01E010E0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x20, 0x38, 0x24);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x20, 0x38, 0x24);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02E10;
        e->arg = arg;
    }
}

/* shape c056:01E011C0, 53 insns: spawns a dark glow (c056:01E00C50 family): colours 0x18 grey with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02BE0 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E011C0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E011C0 col0;
    Col_c056_01E011C0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E011C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E011C0;

static void func_01E011C0_c056(Ctx_c056_01E011C0 *ctx, s32 arg) {
    extern void c056_01E02BE0(void);
    extern void func_001076F0();
    Ent_c056_01E011C0 *e = (Ent_c056_01E011C0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x18, 0x18, 0x18);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x18, 0x18, 0x18);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02BE0;
        e->arg = arg;
    }
}

/* shape c056:01E012A0, 123 insns: c056:01E010E0 family trail link: spawns a dark grey (0x15) piece with the context's alpha and vector, at the context's position, ground height 18 below it (0 when that falls below 0); chained after the context's last piece, copying its two vectors, and becomes the new last piece; draws with c056:01E022F0 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E012A0;

typedef struct Ent_c056_01E012A0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[8];
    Vec4f a;
    u8 pad50[0x10];
    Vec4f v;
    Vec4f b;
    u8 pad80[0x10];
    struct Ent_c056_01E012A0 *prev;
    struct Ent_c056_01E012A0 *next;
    void (*cb)(void);
    s32 arg;
    u8 padA0[6];
    s16 fA6;
    u8 padA8[4];
    Col_c056_01E012A0 col0;
    Col_c056_01E012A0 col1;
    u8 padB4[6];
    s16 fBA;
    s16 fBC;
    s16 fBE;
} Ent_c056_01E012A0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E012A0 *last;
    u8 pad4490[0x449C - 0x4490];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
    s16 f44BC;
    u8 pad44BE[0xA];
    s16 f44C8;
} Ctx_c056_01E012A0;

static void func_01E012A0_c056(Ctx_c056_01E012A0 *ctx, s32 arg) {
    extern void c056_01E022F0(void);
    extern void func_001076F0();
    Ent_c056_01E012A0 *e = (Ent_c056_01E012A0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E012A0 *p;
    f32 h;

    if (e != NULL) {
        func_001076F0(&e->col0, 0x15, 0x15, 0x15);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x15, 0x15, 0x15);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->prev = ctx->last;
        e->fA6 = ctx->f44C8;
        if (e->prev == NULL) {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 18.0f;
        } else {
            h = ctx->pos[2];
            e->f4 = e->f14 = h;
            e->f34 = e->f24 = h - 18.0f;
        }
        if (ctx->pos[2] - 18.0f >= 0.0f) {
            e->f34 = e->f24 = e->f4 - 18.0f;
        } else {
            e->f34 = e->f24 = 0.0f;
        }
        e->prev = ctx->last;
        p = e->prev;
        if (p != NULL) {
            e->a = p->a;
            e->b = p->b;
            p->next = e;
        }
        e->cb = c056_01E022F0;
        e->arg = arg;
        e->fBC = ctx->f44BC;
        e->fBE = 1;
        ctx->last = e;
    }
}

/* shape c056:01E01490, 66 insns: spawns a grey glow (c056:01E00C50 family): colours 0x20 with the context's alpha, height
   from the context, placed at the context's position; links to the context's parent effect (copying its vector and
   pointing it back), draws with c056:01E02790, frame 7 */

typedef struct Ent_c056_01E01490 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x58];
    Vec4f v;
    u8 pad80[0x10];
    struct Ent_c056_01E01490 *parent;
    struct Ent_c056_01E01490 *child;
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 padB4[4];
    s16 fB8;
    s16 fBA;
    u8 padBC[2];
    s16 fBE;
} Ent_c056_01E01490;

typedef struct {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E01490 *parent;
    u8 pad4490[0xC];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    s16 f44BA;
} Ctx_c056_01E01490;

static void func_01E01490_c056(Ctx_c056_01E01490 *ctx, s32 arg) {
    extern void c056_01E02790(void);
    extern void func_001076F0();
    Ent_c056_01E01490 *e = (Ent_c056_01E01490 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E01490 *p;

    if (e != NULL) {
        func_001076F0(e->col0, 0x20, 0x20, 0x20);
        e->col0[3] = ctx->rgba[3];
        func_001076F0(e->col1, 0x20, 0x20, 0x20);
        e->col1[3] = ctx->rgba[3];
        e->fBA = ctx->f44BA;
        e->f14 = e->f4 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->parent = ctx->parent;
        p = e->parent;
        if (p != NULL) {
            e->v = p->v;
            p->child = e;
        }
        e->cb = c056_01E02790;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
        e->fBE = 7;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E015A0_c056);

/* shape c056:01E02020, 178 insns: c056:01E02560 family flat diamond: mode 0 picks frame 1 from func_00105D00 when 0xA0 is set (scene texture g+0xCC) or texture 0x14 at its angle (g+0x98), colour 0xAC; other modes set the camera at the object (random-free turn g+0xD0, no roll) and lay its four corners at 135/45/225/315 degrees, x radius 0xAA + 5 and z radius 0xAA, depth-tested into g+0x4488 */

typedef struct {
    u8 pad0[0x40];
    u8 m[0x58];
    s32 tex98;
    u8 pad9C[0x30];
    s32 texCC;
    s32 rot[2];
    s32 wD8;
    u8 padDC[0x4488 - 0xDC];
    s32 target;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 scale[1];
} Game_c056_01E02020;

typedef struct {
    Vec4f q[4];
    u8 pad40[0x20];
    Vec4f at;
    u8 pad70[0x30];
    f32 fA0;
    u8 padA4[6];
    s16 r;
    u8 col[0x10];
    s16 hBC;
} Ring_c056_01E02020;

static void func_01E02020_c056(Game_c056_01E02020 *g, Ring_c056_01E02020 *o, void *p, s32 mode) {
    extern void func_00105D00(void *, s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];

    if (mode == 0) {
        if (o->fA0) {
            func_00105D00(rm, 1, o->hBC);
        } else {
            func_00106080(rm, 0x14, o->hBC, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        if (o->fA0) {
            func_00208700(p, g->texCC, 1);
            return;
        }
        func_00208700(p, g->tex98, 1);
        return;
    }
    func_00205C40((s32)g->rot);
    g->wD8 = 0;
    func_0020EB40(g->m);
    func_0020C940(g, NULL, g->rot, &o->at);
    func_0020BC00(g->m, g);
    o->q[0].x = (f32)(o->r + 5) * func_00108030(g->scale, 135, 1);
    o->q[0].y = (f32)o->r * func_00108030(g->scale, 135, 0);
    o->q[0].z = 0.0f;
    o->q[1].x = (f32)(o->r + 5) * func_00108030(g->scale, 45, 1);
    o->q[1].y = (f32)o->r * func_00108030(g->scale, 45, 0);
    o->q[1].z = 0.0f;
    o->q[2].x = (f32)(o->r + 5) * func_00108030(g->scale, 225, 1);
    o->q[2].y = (f32)o->r * func_00108030(g->scale, 225, 0);
    o->q[2].z = 0.0f;
    o->q[3].x = (f32)(o->r + 5) * func_00108030(g->scale, 315, 1);
    o->q[3].y = (f32)o->r * func_00108030(g->scale, 315, 0);
    o->q[3].z = 0.0f;
    if (func_00205630(o->q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->target, (u32)g->depth);
    }
}

/* shape c056:01E022F0, 154 insns: three segments of a ring around a parent: mode 0 sets the material (frame 0x97, both
   colours, the first one blanked when there is no parent); otherwise for each third of the circle (120 apart) the
   outer edge follows the parent's ring (its angle, radius and height, through its matrix) or its own, the inner edge
   its own ring at radius 0xAA, and the segment is sent at the scene depth */

typedef struct Fx_c056_01E022F0 {
    Vec4f q[4];
    Vec4f v40;
    u8 pad50[0x20];
    f32 m70[8];
    struct Fx_c056_01E022F0 *parent;
    u8 pad94[0x14];
    s16 hA8;
    s16 hAA;
    u8 col[4];
    u8 col2[4];
    u8 padB4[6];
    s16 ang;
} Fx_c056_01E022F0;

typedef struct {
    u8 pad0[0x40];
    f32 m40[16];
    u8 pad80[0x4C];
    s32 tex;
    u8 padD0[0x43B8];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 sin[1];
} Scene_c056_01E022F0;

static void func_01E022F0_c056(Scene_c056_01E022F0 *g, Fx_c056_01E022F0 *o, void *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00106CF0(void *, s16, s32, void *);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    f32 rm[4];
    s32 i;
    Fx_c056_01E022F0 *p;
    s16 a;

    p = o->parent;
    a = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(pk, 0, 0);
        if (p == NULL) {
            o->col[3] = 0;
        }
        func_00107790(pk, o->col, 1);
        func_00107790(pk, o->col2, 2);
        func_00108500(pk, rm, 1);
        func_00208700(pk, g->tex, 1);
        return;
    }
    for (i = 0; i < 3; i++) {
        if (p != NULL) {
            func_00106CF0(&o->q[0], a + p->ang, p->hAA, g->sin);
            func_00106CF0(&o->q[1], a + p->ang + 15, p->hAA, g->sin);
            o->q[1].y = o->q[0].y = p->q[2].y;
            func_00107DD0(o, p->m70, o->m70, 0);
        } else {
            func_00106CF0(&o->q[0], a + o->ang, o->hA8, g->sin);
            func_00106CF0(&o->q[1], a + o->ang + 15, o->hA8, g->sin);
        }
        func_00106CF0(&o->q[2], a + o->ang, o->hAA, g->sin);
        func_00106CF0(&o->q[3], a + o->ang + 15, o->hAA, g->sin);
        func_00106FA0(o, o->m70, 0);
        func_00107DD0(&o->q[2], o->m70, &o->v40, 0);
        if (func_00205630(o, 0x70000000, g->m40, pk, &g->depth) != 0) {
            func_002075F0(pk, g->ot, func_001A23B0(g->depth));
        }
        a += 120;
    }
}

/* shape c056:01E02560, 139 insns: b194:01E02AB0's two-pass material with a 12-segment ring: mode 0 sets the material
   (frame 0x97, the object's two colours, scene texture 0xCC); other modes turn by the scene's rotation entry for the
   object, set the ring's height to twice its depth from the top, and draw 12 segments of 30 degrees between the radii at
   0xA8 and 0xAA (scale g+0x44D0, depth 0x44A8, packet list 0x4488) */

typedef struct {
    f32 x, y, z, w;
} Vec_c056_01E02560;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02560;

typedef struct {
    Rgbaq_c056_01E02560 c;
    u64 st;
    u64 xyz;
} Vtx_c056_01E02560;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c056_01E02560 v[4];
} Pkt_c056_01E02560;


typedef struct {
    Vec_c056_01E02560 q[4];
    u8 pad40[0x60];
    f32 top;
    u8 padA4[4];
    s16 r0;
    s16 r1;
    u8 col[4];
    u8 col2[4];
    u8 padB4[8];
    s16 rot;
} Ring_c056_01E02560;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0x4C];
    s32 texture;
    u8 padD0[0x30];
    Vec_c056_01E02560 rots[1];
    u8 pad110[0x4378];
    s32 target;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    f32 scale;
} Game_c056_01E02560;

static void func_01E02560_c056(Game_c056_01E02560 *g, Ring_c056_01E02560 *an, Pkt_c056_01E02560 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c056_01E02560 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106CF0(void *, s16, s32, f32 *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 rm[4];
    f32 m[16];
    f32 d;
    s32 i;

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
        func_0020C940(m, 0, &g->rots[an->rot], 0);
        func_0020BC00(g->m, m);
        d = 2.0f * (an->q[0].y - an->top);
        an->q[3].y = an->q[2].y = d;
        for (i = 0; i < 12; i++) {
            func_00106CF0(&an->q[0], i * 30, an->r0, &g->scale);
            func_00106CF0(&an->q[1], i * 30 + 30, an->r0, &g->scale);
            func_00106CF0(&an->q[2], i * 30, an->r1, &g->scale);
            func_00106CF0(&an->q[3], i * 30 + 30, an->r1, &g->scale);
            if (func_00205630(an->q, 0x70000000, g->m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape c056:01E02790 (PAINT_PA17), 276 insns, 1 copy: three segments of a ring around a parent: mode 0 sets the
   material (frame 0x97; the outer colour from the parent's, or its own with alpha 0 when there is none; the inner one
   its own, or with alpha 0 unless flagged); otherwise for each of three segments (100 apart) the outer edge follows
   the parent's ring (its angle less 15, radius and height) or its own, the inner edge its own ring, and the segment is
   sent at the scene depth */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E02790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02790;

typedef struct {
    u8 pad0[0x10];
    Rgbaq_c056_01E02790 c10;
    u8 pad18[0x10];
    Rgbaq_c056_01E02790 c28;
    u8 pad30[0x10];
    Rgbaq_c056_01E02790 c40;
    u8 pad48[0x10];
    Rgbaq_c056_01E02790 c58;
} Pkt_c056_01E02790;

typedef struct Fx_c056_01E02790 {
    Vec4f q[4];
    u8 pad40[0x50];
    struct Fx_c056_01E02790 *parent;
    s32 w94;
    u8 pad98[8];
    f32 fA0;
    u8 padA4[6];
    s16 hAA;
    Col_c056_01E02790 col;
    Col_c056_01E02790 col2;
    u8 padB4[6];
    s16 ang;
} Fx_c056_01E02790;

typedef struct {
    u8 pad0[0x40];
    f32 m40[16];
    u8 pad80[0x4C];
    s32 tex;
    u8 padD0[0x43B8];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 sin[1];
} Scene_c056_01E02790;

static void func_01E02790_c056(Scene_c056_01E02790 *g, Fx_c056_01E02790 *o, Pkt_c056_01E02790 *pk, s32 mode) {
    extern Col_c056_01E02790 D_01E05400_c056;
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c056_01E02790 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Col_c056_01E02790 c;
    f32 rm[4];
    s32 i;
    Fx_c056_01E02790 *p;
    s16 a;

    p = o->parent;
    a = 0;
    c = D_01E05400_c056;
    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(pk, 0, 0);
        if (p == NULL) {
            c = o->col;
            c.a = 0;
            pk->c10 = func_00107740(&c);
            pk->c40 = func_00107740(&c);
        } else {
            pk->c10 = func_00107740(&p->col2);
            pk->c40 = func_00107740(&p->col2);
        }
        if (o->w94 != 0) {
            pk->c28 = func_00107740(&o->col2);
            pk->c58 = func_00107740(&o->col2);
        } else {
            c = o->col2;
            c.a = 0;
            pk->c28 = func_00107740(&c);
            pk->c58 = func_00107740(&c);
        }
        func_00108500(pk, rm, 0);
        func_00208700(pk, g->tex, 1);
        return;
    }
    for (i = 0; i < 3; i++) {
        if (p != NULL) {
            o->q[0].x = p->hAA * func_00108030(g->sin, p->ang + a - 15, 1);
            o->q[0].z = p->hAA * func_00108030(g->sin, p->ang + a - 15, 0);
            o->q[2].x = o->q[0].x;
            o->q[2].z = o->q[0].z;
        } else {
            o->q[0].x = o->hAA * func_00108030(g->sin, o->ang + a, 1);
            o->q[0].z = o->hAA * func_00108030(g->sin, o->ang + a, 0);
            o->q[2].x = o->q[0].x;
            o->q[2].z = o->q[0].z;
        }
        o->q[1].x = o->hAA * func_00108030(g->sin, o->ang - 15 + a, 1);
        o->q[1].z = o->hAA * func_00108030(g->sin, o->ang - 15 + a, 0);
        o->q[3].x = o->q[1].x;
        o->q[3].z = o->q[1].z;
        if (p != NULL) {
            o->q[2].y = p->q[1].y - p->fA0;
        } else {
            o->q[2].y = o->q[0].y - o->fA0;
        }
        o->q[3].y = o->q[0].y - o->fA0;
        if (func_00205630(o, 0x70000000, g->m40, pk, &g->depth) != 0) {
            func_002075F0(pk, g->ot, (u32)g->depth);
        }
        a += 100;
    }
}

/* shape c056:01E02BE0, 139 insns: a ring of twelve flat quads: mode 0 sets the four corner colours (two of each of
   the effect's colours); otherwise the quad's inner edge sits at the centre (y 10) and its outer corners sweep a
   radius-150 circle 30 degrees apart from the effect's angle, each quad sent at the scene depth */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02BE0;

typedef struct {
    Rgbaq_c056_01E02BE0 c;
    u64 st;
} Vtx_c056_01E02BE0;

typedef struct {
    u8 pad0[0x10];
    Vtx_c056_01E02BE0 v[4];
} Pkt_c056_01E02BE0;

typedef struct {
    Vec4f q[4];
    u8 pad40[0x6C];
    u8 col[4];
    u8 col2[4];
    u8 padB4[6];
    s16 ang;
} Fx_c056_01E02BE0;

typedef struct {
    u8 pad0[0x4488];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 sin[1];
} Scene_c056_01E02BE0;

static void func_01E02BE0_c056(Scene_c056_01E02BE0 *g, Fx_c056_01E02BE0 *o, Pkt_c056_01E02BE0 *p, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern Rgbaq_c056_01E02BE0 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    s32 i;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_001092E0(p, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        return;
    }
    o->q[0].x = 0.0f;
    o->q[0].z = 0.0f;
    o->q[1].x = o->q[0].x;
    o->q[1].z = o->q[0].z;
    o->q[0].y = 10.0f;
    o->q[1].y = 10.0f;
    o->q[2].y = 10.0f;
    o->q[3].y = 10.0f;
    for (i = 0; i < 12; i++) {
        o->q[2].x = 150.0f * func_00108030(g->sin, o->ang + a, 1);
        o->q[2].z = 150.0f * func_00108030(g->sin, o->ang + a, 0);
        o->q[3].x = 150.0f * func_00108030(g->sin, o->ang + 30 + a, 1);
        o->q[3].z = 150.0f * func_00108030(g->sin, o->ang + 30 + a, 0);
        if (func_00205630(o, 0x70000000, 0, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, func_001A23B0(g->depth));
        }
        a += 30;
    }
}

/* shape c056:01E02E10, 158 insns: c056:01E02BE0's ring as a 12-segment band at the scene's ring point: mode 0 sets the
   corner colours; other modes place the scene matrix at the point (g+0x4388), keep the top edge at the object's height
   and the bottom at 0, and draw 12 segments of 30 degrees between radii 170 (top) and 25 (bottom) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c056_01E02E10;

typedef struct {
    Rgbaq_c056_01E02E10 c;
    u64 st;
} Vtx_c056_01E02E10;

typedef struct {
    u8 pad0[0x10];
    Vtx_c056_01E02E10 v[4];
} Pkt_c056_01E02E10;

typedef struct {
    Vec4f q[4];
    u8 pad40[0x60];
    f32 top;
    u8 padA4[8];
    u8 col[4];
    u8 col2[4];
    u8 padB4[6];
    s16 ang;
} Fx_c056_01E02E10;

typedef struct {
    u8 pad0[0x118];
    Vec4f pos;
} Sub_c056_01E02E10;

typedef struct {
    u8 m0[0x40];
    u8 m[0x40];
    u8 pad80[0x41F0];
    Sub_c056_01E02E10 sub;
    u8 pad4398[0xF0];
    s32 ot;
    u8 pad448C[0x1C];
    f32 depth;
    u8 pad44AC[0x24];
    u8 sin[1];
} Scene_c056_01E02E10;

static void func_01E02E10_c056(Scene_c056_01E02E10 *g, Fx_c056_01E02E10 *o, Pkt_c056_01E02E10 *p, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern Rgbaq_c056_01E02E10 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    Sub_c056_01E02E10 *s = &g->sub;
    s32 i;
    s16 a;
    f32 s0;
    f32 c0;
    f32 s1;
    f32 c1;

    a = 0;
    if (mode == 0) {
        func_001092E0(p, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        return;
    }
    func_0020EB40(g->m);
    func_0020C940(g, 0, 0, &s->pos);
    func_0020BC00(g->m, g);
    o->q[0].y = o->top;
    o->q[1].y = o->top;
    o->q[2].y = 0.0f;
    o->q[3].y = 0.0f;
    for (i = 0; i < 12; i++) {
        s0 = func_00108030(g->sin, o->ang + a, 1);
        c0 = func_00108030(g->sin, o->ang + a, 0);
        s1 = func_00108030(g->sin, o->ang + 30 + a, 1);
        c1 = func_00108030(g->sin, o->ang + 30 + a, 0);
        o->q[2].x = 25.0f * s0;
        o->q[2].z = 25.0f * c0;
        o->q[3].x = 25.0f * s1;
        o->q[3].z = 25.0f * c1;
        o->q[0].x = 170.0f * s0;
        o->q[0].z = 170.0f * c0;
        o->q[1].x = 170.0f * s1;
        o->q[1].z = 170.0f * c1;
        if (func_00205630(o, 0x70000000, g->m, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, func_001A23B0(g->depth));
        }
        a += 30;
    }
}

/* shape c056:01E03090 (C056_W_S), 660 insns, 1 copy: C056_W_S, the scene step: counts the frame (0x44C2); at 1 sets
   five path rings (radius 20 at 0/90/180/270/0 degrees, x/z from sin/cos of the old angle), three 0x1E04830 pieces,
   two five-piece climber chains (0x1E04900, 0x1E04FE0), the path heights (30 apart) and ring heights, three random
   turns, three lights (70/90/110) with 0x1E03DA0, the 0x1E04CF0 ring, three 0x1E044B0 sparks, a 17-piece 0x1E03FE0
   chain, then 0x1E04830 and 0x1E04780; from step 21 on odd steps one more spark; 0xE4 drops by 0x100; the first piece
   call goes through a no-prototype alias */

typedef struct {
    f32 x, y, z;
    u8 padC[8];
    s16 ang;
    s16 rad;
    u8 pad18[4];
} Rp_c056_01E03090;

typedef struct {
    Vec4f p;
    f32 a, b;
} Pt_c056_01E03090;

typedef struct {
    Rp_c056_01E03090 r[8];
    u8 padE0[0x118 - 0xE0];
    Pt_c056_01E03090 pt[10];
} Path_c056_01E03090;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xE4 - 0x90];
    s32 wE4;
    u8 padE8[0x100 - 0xE8];
    s32 rot[3][4];
    u8 pad130[0x4270 - 0x130];
    Path_c056_01E03090 path;
    s32 step;
    u8 pad447C[4];
    u8 rgba[4];
    u8 pad4484[8];
    void *owner;
    u8 pad4490[0xC];
    f32 f449C;
    f32 f44A0;
    f32 f44A4;
    u8 pad44A8[0x10];
    s16 h44B8;
    s16 h44BA;
    s16 h44BC;
    u8 pad44BE[4];
    s16 h44C2;
    u8 pad44C4[4];
    s16 h44C8;
} Scene_c056_01E03090;

static void func_01E03090_c056(Scene_c056_01E03090 *g) {
    extern void c056_01E03AE0();
    extern void c056_01E03DA0();
    extern void c056_01E03FE0();
    extern void c056_01E044B0();
    extern void c056_01E04780();
    extern void c056_01E04830();
    extern void c056_01E04900();
    extern void c056_01E04CF0();
    extern void c056_01E04FE0();
    extern void c056_01E011C0();
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107EA0(void *, f32, f32, f32);
    Path_c056_01E03090 *p;
    s32 i;

    g->h44C2++;
    if (g->h44C2 == 1) {
        func_01E00C10_c056((void *)g, (s32)c056_01E03AE0);
        p = &g->path;
        p->r[0].x = p->r[0].rad * func_001A6898(3.1415927f * p->r[0].ang / 180.0f);
        p->r[0].z = p->r[0].rad * func_001A6A88(3.1415927f * p->r[0].ang / 180.0f);
        p->r[0].ang = 0;
        p->r[0].rad = 20;
        p->r[1].x = p->r[1].rad * func_001A6898(3.1415927f * p->r[1].ang / 180.0f);
        p->r[1].z = p->r[1].rad * func_001A6A88(3.1415927f * p->r[1].ang / 180.0f);
        p->r[1].ang = 90;
        p->r[1].rad = 20;
        p->r[2].x = p->r[2].rad * func_001A6898(3.1415927f * p->r[2].ang / 180.0f);
        p->r[2].z = p->r[2].rad * func_001A6A88(3.1415927f * p->r[2].ang / 180.0f);
        p->r[2].ang = 180;
        p->r[2].rad = 20;
        p->r[3].x = p->r[3].rad * func_001A6898(3.1415927f * p->r[3].ang / 180.0f);
        p->r[3].z = p->r[3].rad * func_001A6A88(3.1415927f * p->r[3].ang / 180.0f);
        p->r[3].ang = 270;
        p->r[3].rad = 20;
        p->r[4].x = p->r[4].rad * func_001A6898(3.1415927f * p->r[4].ang / 180.0f);
        p->r[4].z = p->r[4].rad * func_001A6A88(3.1415927f * p->r[4].ang / 180.0f);
        p->r[4].ang = 0;
        p->r[4].rad = 20;
        g->h44C8 = 0;
        g->h44BA = 0;
        g->owner = NULL;
        g->f44A4 = 50.0f;
        c056_01E011C0(g, c056_01E04830);
        g->h44C8 = 1;
        g->h44BA = 120;
        g->owner = NULL;
        g->f44A4 = 40.0f;
        func_01E011C0_c056((void *)g, (s32)c056_01E04830);
        g->h44C8 = 2;
        g->h44BA = 250;
        g->owner = NULL;
        func_01E011C0_c056((void *)g, (s32)c056_01E04830);
        g->f449C = 30.0f;
        g->owner = NULL;
        for (i = 5; i > 0; i--) {
            g->f449C = 3 * i + 3;
            g->f44A0 = g->f449C - 3.0f;
            if (i != 1) {
                g->h44BC = 0;
            } else {
                g->h44BC = 1;
            }
            g->f44A4 = 25 * i;
            g->h44C8 = 1;
            g->v.y = 0.0f;
            g->v.x = 0.0f;
            g->v.z = 0.0f;
            g->rgba[3] = 0;
            g->h44BA = 15 * i;
            func_01E012A0_c056((void *)g, (s32)c056_01E04900);
        }
        g->owner = NULL;
        for (i = 5; i > 0; i--) {
            g->f449C = 3 * i + 7;
            g->f44A0 = g->f449C - 3.0f;
            if (i != 1) {
                g->h44BC = 0;
            } else {
                g->h44BC = 1;
            }
            g->f44A4 = 25 * i;
            g->h44C8 = 1;
            g->v.y = 0.0f;
            g->v.x = 0.0f;
            g->v.z = 0.0f;
            g->rgba[3] = 0;
            g->h44BA = 15 * i + 90;
            func_01E012A0_c056((void *)g, (s32)c056_01E04FE0);
        }
        g->v.x = 100.0f;
        g->v.y = 50.0f;
        g->v.z = 0.0f;
        g->owner = NULL;
        g->h44C8 = 0;
        g->h44B8 = 2;
        g->v.x = 0.0f;
        g->v.y = 10.0f;
        g->v.z = 0.0f;
        p->pt[0].p.y = 0.0f;
        p->pt[1].p.y = 30.0f + p->pt[0].p.y;
        p->pt[2].p.y = 30.0f + p->pt[1].p.y;
        p->pt[3].p.y = 30.0f + p->pt[2].p.y;
        p->pt[4].p.y = 30.0f + p->pt[3].p.y;
        p->pt[5].p.y = 30.0f + p->pt[4].p.y;
        p->pt[6].p.y = 30.0f + p->pt[5].p.y;
        p->pt[7].p.y = 30.0f + p->pt[6].p.y;
        p->pt[8].p.y = 30.0f + p->pt[7].p.y;
        p->pt[9].p.y = 30.0f + p->pt[8].p.y;
        p->r[0].y = 0.0f;
        p->r[1].y = 20.0f;
        p->r[2].y = 40.0f;
        p->r[3].y = 60.0f;
        p->r[4].y = 90.0f;
        p->r[5].y = 110.0f;
        p->r[6].y = 120.0f;
        p->r[7].y = 140.0f;
        g->rot[0][1] = func_0019A5C8() * 182 % 360;
        g->rot[1][1] = func_0019A5C8() * 182 % 360;
        g->rot[2][1] = func_0019A5C8() * 182 % 360;
        func_001076F0(g->rgba, 0x10, 0x10, 0x10);
        g->v.y = 40.0f;
        g->h44B8 = 70;
        g->h44BC = 0;
        func_00107EA0(g, g->h44B8, g->h44B8, 5.0f);
        func_01E00C50_c056((void *)g, (s32)c056_01E03DA0);
        g->h44BC = 1;
        g->v.y = 60.0f;
        g->h44B8 = 90;
        func_00107EA0(g, g->h44B8, g->h44B8, 5.0f);
        func_01E00C50_c056((void *)g, (s32)c056_01E03DA0);
        g->h44BC = 2;
        g->v.y = 80.0f;
        g->h44B8 = 110;
        func_00107EA0(g, g->h44B8, g->h44B8, 5.0f);
        func_01E00C50_c056((void *)g, (s32)c056_01E03DA0);
        g->v.y = 70.0f;
        g->h44B8 = 100;
        g->owner = NULL;
        g->h44C8 = 0;
        g->rgba[3] = 0;
        g->h44BA = 90;
        g->f44A4 = 20.0f;
        g->f44A0 = 90.0f;
        func_00107EA0(g, 100.0f, 80.0f, 50.0f);
        func_01E01490_c056((void *)g, (s32)c056_01E04CF0);
        g->f44A4 = 5.0f;
        for (i = 0; i < 3; i++) {
            g->h44BA = func_0019A5C8() % 360;
            g->f449C = 15.0f;
            g->f44A0 = 15.0f;
            g->rgba[3] = 0x20;
            func_01E00F30_c056((void *)g, (s32)c056_01E044B0);
        }
        g->f449C = 10.0f;
        g->owner = NULL;
        func_001076F0(g->rgba, 0x30, 0x30, 0x30);
        for (i = 17; i > 0; i--) {
            g->f449C = 2 * i + 1;
            g->f44A0 = i + 1;
            if (i != 1) {
                g->h44BC = 0;
            } else {
                g->h44BC = 1;
            }
            g->f44A4 = 13 * i;
            g->h44C8 = 1;
            g->v.y = 0.0f;
            g->rgba[3] = 0;
            if (g->h44B8 == 0) {
                g->h44B8 = 1;
            } else {
                g->h44B8 = 0;
            }
            g->v.x = 0.0f;
            g->v.z = 0.0f;
            g->h44BA = 10 * i;
            func_01E00D30_c056((void *)g, (s32)c056_01E03FE0);
        }
        g->f44A0 = 7.0f;
        g->rgba[3] = 0;
        func_01E011C0_c056((void *)g, (s32)c056_01E04830);
        func_01E010E0_c056((void *)g, (s32)c056_01E04780);
    }
    if (g->step > 20 && g->step % 2 == 1) {
        for (i = 0; i < 1; i++) {
            g->h44BA = func_0019A5C8() % 360;
            g->f449C = 5.0f;
            g->f44A0 = 5.0f;
            g->rgba[3] = 0x10;
            if (g->step > 13) {
                func_01E00F30_c056((void *)g, (s32)c056_01E044B0);
            }
        }
    }
    g->wE4 -= 0x100;
}

/* shape c056:01E03AE0, 175 insns: swings the six orbit arms of the scene object (ctx+0x4270, angles at +0x12C.. step 0x18) by +3/-8/+11/-12/+18/-9 a tick with radii 15 (doubled)/7/7/9/9/10, x by the sine and z by the cosine from the game table (ctx+0x44D0); clears the caller's 0xA4 while ctx+0x4478 is under 11 */

typedef struct {
    f32 x;
    u8 pad4[4];
    f32 z;
    u8 padC[8];
    s16 ang;
    s16 r;
} Arm_c056_01E03AE0;

typedef struct {
    u8 pad0[0x118];
    Arm_c056_01E03AE0 arm[6];
} Obj_c056_01E03AE0;

typedef struct {
    u8 pad0[0x4270];
    Obj_c056_01E03AE0 obj;
    u8 pad[0x4478 - 0x4270 - 0x1A8];
    s32 w4478;
    u8 pad447C[0x44D0 - 0x447C];
    u8 trig[1];
} Ctx_c056_01E03AE0;

typedef struct {
    u8 pad0[0xA4];
    s16 hA4;
} Fx_c056_01E03AE0;

static s32 func_01E03AE0_c056(Ctx_c056_01E03AE0 *g, Fx_c056_01E03AE0 *o) {
    extern f32 func_00108030(void *, s16, s32);
    Obj_c056_01E03AE0 *p;

    p = &g->obj;
    if (p == NULL) {
        return 0;
    }
    {
        p->arm[0].x = (f32)(p->arm[0].r * 2) * func_00108030(g->trig, p->arm[0].ang, 1);
        p->arm[0].z = (f32)(p->arm[0].r * 2) * func_00108030(g->trig, p->arm[0].ang, 0);
        p->arm[0].ang += 3;
        p->arm[0].r = 15;
        p->arm[1].x = p->arm[1].r * func_00108030(g->trig, p->arm[1].ang, 1);
        p->arm[1].z = p->arm[1].r * func_00108030(g->trig, p->arm[1].ang, 0);
        p->arm[1].ang -= 8;
        p->arm[1].r = 7;
        p->arm[2].x = p->arm[2].r * func_00108030(g->trig, p->arm[2].ang, 1);
        p->arm[2].z = p->arm[2].r * func_00108030(g->trig, p->arm[2].ang, 0);
        p->arm[2].ang += 11;
        p->arm[2].r = 7;
        p->arm[3].x = p->arm[3].r * func_00108030(g->trig, p->arm[3].ang, 1);
        p->arm[3].z = p->arm[3].r * func_00108030(g->trig, p->arm[3].ang, 0);
        p->arm[3].ang -= 12;
        p->arm[3].r = 9;
        p->arm[4].x = p->arm[4].r * func_00108030(g->trig, p->arm[4].ang, 1);
        p->arm[4].z = p->arm[4].r * func_00108030(g->trig, p->arm[4].ang, 0);
        p->arm[4].ang += 18;
        p->arm[4].r = 9;
        p->arm[5].x = p->arm[5].r * func_00108030(g->trig, p->arm[5].ang, 1);
        p->arm[5].z = p->arm[5].r * func_00108030(g->trig, p->arm[5].ang, 0);
        p->arm[5].ang -= 9;
        p->arm[5].r = 10;
        if (g->w4478 < 11) {
            o->hA4 = 0;
        }
    }
    return 0;
}

/* shape c056:01E03DA0, 142 insns: a rider on the scene's eight-point path (24-byte points at +0x4388): spins 0x300 a
   tick, its angle 0xBA turns 4..28 a tick; it finds the first path segment rising above its height and takes its x/z
   from it (func_001098E0); the scene entry it owns sinks 0x250 and sways 3072 x sin(0xBE), 0xBE turning 4 a tick;
   early in the scene count it calls func_00106BC0 and grows 0xA8/0xAA by 3 until func_00106B90 says done */

typedef struct {
    f32 x, y, z;
    u8 padC[0xC];
} Pt_c056_01E03DA0;

typedef struct {
    u8 pad0[0x118];
    Pt_c056_01E03DA0 pt[8];
} Path_c056_01E03DA0;

typedef struct {
    s32 w100;
    s32 w104;
    u8 pad108[8];
} Ent_c056_01E03DA0;

typedef struct {
    u8 pad0[0x100];
    Ent_c056_01E03DA0 ent[1];
    u8 pad110[0x4160];
    Path_c056_01E03DA0 path;
    u8 pad4448[0x30];
    s32 timer;
    u8 pad447C[0x46];
    s16 count;
    u8 pad44C4[0xC];
    u8 sin[1];
} Scene_c056_01E03DA0;

typedef struct {
    u8 pad0[4];
    f32 y;
    u8 pad8[0x4C];
    s32 spin;
    u8 pad58[8];
    f32 x60;
    u8 pad64[4];
    f32 z68;
    u8 pad6C[0x38];
    s16 hA4;
    u8 padA6[2];
    s16 hA8;
    s16 hAA;
    u8 padAC[0xE];
    s16 ang;
    s16 idx;
    s16 sway;
} Fx_c056_01E03DA0;

static s32 func_01E03DA0_c056(Scene_c056_01E03DA0 *g, Fx_c056_01E03DA0 *o) {
    extern void func_001098E0(void *, void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A22C0(f32);
    extern void func_00106BC0(void *, s32, s32);
    extern s32 func_00106B90(void *, s32, s32);
    Vec4f out;
    f32 v[4];
    Path_c056_01E03DA0 *p;
    s32 i;

    v[0] = v[1] = v[2] = 0.0f;
    p = &g->path;
    o->spin += 0x300;
    o->ang += (s16)(func_0019A5C8() % 25 + 4);
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    for (i = 1; i < 8; i++) {
        if (p->pt[i].y > o->y) {
            v[0] = p->pt[0].x;
            v[2] = p->pt[0].z;
            func_001098E0(&out, v, o, &p->pt[i - 1], &p->pt[i]);
            i = 8;
            o->x60 = out.x;
            o->z68 = out.z;
        }
    }
    g->ent[o->idx].w104 -= 0x250;
    g->ent[o->idx].w100 = func_001A22C0(3072.0f * func_00108030(g->sin, o->sway, 0));
    o->sway += 4;
    if (o->sway >= 360) {
        o->sway %= 360;
    }
    if (g->count < 16) {
        func_00106BC0(o, 0x17, 0xA0);
    }
    if (g->timer < 21) {
        o->hA8 += 3;
        o->hAA = o->hA8;
        if (func_00106B90(o, 0x12, 0x14) != 0) {
            o->hA4 = 0;
        }
    }
    if (g->timer < 11) {
        o->hA4 = 0;
    }
    return 0;
}

/* shape c056:01E03FE0 (C056_OBJ_MOVE_3_), 308 insns, 1 copy: a curtain that climbs the scene object's eight joints:
   it spins 0x400 a tick; at the first joint above it, it takes both edges from the joint pair and (from scene tick
   8) widens towards that joint's size; its top climbs by 6 up to joint 6's height and its bottom follows within 20
   (the bottom stops it once it catches up); it fades by 15 near the top (after scene tick 16) or once the game counter
   is under 21 (growing by 3); while it is the leader it hands the scene its size, colour, height and edge, and
   spawns the scene trail */

typedef struct {
    f32 x, y, z;
    u8 padC[0xC];
} Joint_c056_01E03FE0;

typedef struct {
    u8 pad0[0x118];
    Joint_c056_01E03FE0 pt[8];
} Anchor_c056_01E03FE0;

typedef struct {
    u8 pad0[0x90];
    s32 w90;
} Link_c056_01E03FE0;

typedef struct {
    f32 x, y, z, w;
} V4_c056_01E03FE0;

typedef struct {
    V4_c056_01E03FE0 q[4];
    V4_c056_01E03FE0 v40;
    s32 f50;
    s32 f54;
    s32 f58;
    u8 pad5C[0x14];
    V4_c056_01E03FE0 v70;
    u8 pad80[0x14];
    Link_c056_01E03FE0 *link;
    u8 pad98[0xC];
    s16 hA4;
    u8 padA6[2];
    s16 hA8;
    s16 hAA;
    u8 col0[4];
    u8 col1[4];
    u8 padB4[4];
    s16 hB8;
    s16 hBA;
    s16 hBC;
} Fx_c056_01E03FE0;

typedef struct {
    u8 pad0[0x80];
    s32 f80;
    s32 f84;
    s32 f88;
    u8 pad8C[0x64];
    V4_c056_01E03FE0 vF0;
    u8 pad100[0x4270 - 0x100];
    Anchor_c056_01E03FE0 anchor;
    u8 pad[0x4478 - 0x4270 - sizeof(Anchor_c056_01E03FE0)];
    s32 count;
    u8 pad447C[7];
    u8 alpha;
    u8 pad4484[8];
    Fx_c056_01E03FE0 *leader;
    u8 pad4490[0xC];
    f32 f449C;
    f32 f44A0;
    f32 f44A4;
    u8 pad44A8[0x10];
    s16 h44B8;
    s16 h44BA;
    s16 h44BC;
    u8 pad44BE[4];
    s16 h44C2;
    u8 pad44C4[4];
    s16 h44C8;
} Scene_c056_01E03FE0;

static s32 func_01E03FE0_c056(Scene_c056_01E03FE0 *g, Fx_c056_01E03FE0 *o) {
    extern V4_c056_01E03FE0 func_001098E0(void *, void *, void *, void *);
    extern void func_00106BC0(void *, s32, s32);
    extern void func_01E00D30_c056(void *, void *);
    Anchor_c056_01E03FE0 *a;
    V4_c056_01E03FE0 v;
    s32 i;
    Joint_c056_01E03FE0 *p;
    Joint_c056_01E03FE0 *q;
    f32 top;

    a = &g->anchor;
    v.y = 0.0f;
    if (a == NULL) {
        return 0;
    }
    o->f54 += 0x400;
    o->hBA = 0;
    o->f50 = 0;
    o->f58 = 0;
    for (i = 1; i < 8; i++) {
        if (a->pt[i].y > o->q[0].y) {
            v.x = a->pt[0].x;
            p = &a->pt[i];
            q = &a->pt[i - 1];
            v.z = a->pt[0].z;
            o->v70 = func_001098E0(&v, o, q, p);
            o->v40 = func_001098E0(&v, o, q, p);
            if (g->h44C2 > 7) {
                if (o->hA8 <= i * 10 + 9) {
                    o->hA8 += 2;
                }
                if (o->hAA <= i * 9 + 5) {
                    o->hAA += 2;
                }
            }
            i = 8;
        }
    }
    top = a->pt[i - 2].y;
    if (o->q[0].y < top) {
        o->q[0].y += 6.0f;
        o->q[1].y = o->q[0].y;
        if (o->q[0].y - o->q[2].y >= 20.0f) {
            o->q[2].y += 6.0f;
            o->q[3].y = o->q[2].y;
        }
    } else {
        o->q[2].y += 6.0f;
        o->q[3].y = o->q[2].y;
        if (o->q[2].y > o->q[0].y) {
            o->q[3].y = o->q[2].y = o->q[0].y;
            if (o->link != NULL) {
                o->link->w90 = 0;
            }
            o->hA4 = 0;
        }
    }
    if (g->h44C2 < 16) {
        if (o->q[0].y < top - 20.0f) {
            func_00106BC0(o, 20, 160);
        }
    } else if (o->q[0].y > top - 30.0f) {
        if (o->col0[3] > 16) {
            o->col0[3] -= 15;
        }
        if (o->col1[3] > 16) {
            o->col1[3] -= 15;
        }
    }
    if (g->count < 21) {
        o->hA8 += 3;
        o->hAA += 3;
        if (o->col0[3] > 16) {
            o->col0[3] -= 15;
        }
        if (o->col1[3] > 16) {
            o->col1[3] -= 15;
        } else {
            o->hA4 = 0;
        }
    }
    if (o->hBC > 0 && o->q[2].y > 0.0f) {
        g->leader = o;
        if (g->h44C2 > 105) {
            g->f449C = o->hAA;
        } else if (o->hAA > 7) {
            g->f449C = o->hAA - 2;
        } else {
            g->f449C = 6.0f;
        }
        if (g->h44C2 > 105) {
            g->f44A0 = o->hAA;
        } else {
            g->f44A0 = 4.0f;
        }
        g->alpha = o->col0[3];
        g->h44BC = 1;
        if (o->hB8 == 0) {
            g->h44B8 = 1;
        } else {
            g->h44B8 = 0;
        }
        g->f44A4 = o->q[2].y;
        g->h44C8 = 1;
        g->vF0 = o->v40;
        g->f84 = 0;
        g->f80 = 0;
        g->f88 = 0;
        g->h44BA = o->hBA;
        func_01E00D30_c056(g, func_01E03FE0_c056);
        o->hBC = 0;
    }
    if (g->count < 11) {
        o->hA4 = 0;
    }
    return 0;
}

/* shape c056:01E044B0, 178 insns: c056:01E03DA0 family orbiter: while its wait (0xBE) is out steps its phase (0xA6: 0 -> 1, then frames 0xBC to 7 and phase 3) and waits 1..2 again; turn 0xB8 = 4, radius 0xAA +3 and 0xA8 +1..3 a tick; phase 3 -> 4 fades by 9 and ends; from scene timer 22 fades in by 14 to 0xA0, under 17 fades out by 15; sits at radius 0xA8 along 0xBA + 0xB8 plus the path's 0x118/0x120 swing along the scene turn / 360 (g+0xE4) */

typedef struct {
    u8 pad0[0x118];
    f32 f118;
    u8 pad11C[4];
    f32 f120;
} Path_c056_01E044B0;

typedef struct {
    u8 pad0[0xE4];
    s32 turn;
    u8 padE8[0x4270 - 0xE8];
    Path_c056_01E044B0 path;
    u8 pad[0x4478 - 0x4270 - 0x124];
    s32 timer;
    u8 pad447C[0x44D0 - 0x447C];
    u8 sin[1];
} Scene_c056_01E044B0;

typedef struct {
    u8 pad0[0x60];
    f32 x60;
    u8 pad64[4];
    f32 z68;
    u8 pad6C[0x38];
    s16 hA4;
    s16 phase;
    s16 hA8;
    s16 hAA;
    u8 col[4];
    u8 padB0[8];
    s16 hB8;
    s16 hBA;
    s16 frame;
    s16 wait;
} Fx_c056_01E044B0;

static s32 func_01E044B0_c056(Scene_c056_01E044B0 *g, Fx_c056_01E044B0 *o) {
    extern f32 func_00108030(void *, s16, s32);
    Path_c056_01E044B0 *p;
    f32 s;
    f32 c;
    s16 a;

    p = &g->path;
    if (o->wait == 0) {
        if (o->phase == 0) {
            o->phase++;
        } else if (o->phase == 1) {
            if (o->frame < 7) {
                o->frame++;
            } else {
                o->phase = 3;
                o->frame = 0;
            }
        }
        o->wait = func_0019A5C8() % 2 + 1;
    }
    o->hB8 = 4;
    o->hAA += 3;
    o->hA8 += (s16)(func_0019A5C8() % 3 + 1);
    if (o->phase == 3) {
        o->phase++;
    } else if (o->phase == 4) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->hA4 = 0;
        }
    }
    if (g->timer > 21 && o->phase != 4) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 14;
        }
    }
    if (g->timer < 17) {
        if (o->col[3] > 16) {
            o->col[3] -= 15;
        } else {
            o->hA4 = 0;
        }
    }
    s = func_00108030(g->sin, (s16)(o->hBA + o->hB8), 0);
    c = func_00108030(g->sin, (s16)(o->hBA + o->hB8), 1);
    o->x60 = c * o->hA8;
    o->z68 = s * o->hA8;
    a = g->turn / 360;
    o->x60 += p->f118 * func_00108030(g->sin, a, 1);
    o->z68 += p->f120 * func_00108030(g->sin, a, 0);
    if (o->wait != 0) {
        o->wait--;
    }
    if (g->timer < 11) {
        o->hA4 = 0;
    }
    return 0;
}

/* shape c056:01E04780, 42 insns: a sprite that fades in by 16 to 0x30 while the scene value is under 16, out by 15 while the counter is under 21, holds size 190 and ends when the counter is under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 pad447C[0x46];
    s16 val;
} Ctx_c056_01E04780;

typedef struct {
    u8 pad0[0xA0];
    f32 size;
    s16 state;
    u8 padA6[0xD];
    u8 alpha;
    u8 padB4[6];
    u8 bA[1];
} Obj_c056_01E04780;

static s32 func_01E04780_c056(Ctx_c056_01E04780 *ctx, Obj_c056_01E04780 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 16) {
        if (o->alpha < 0x21) {
            o->alpha += 0x10;
        }
    }
    if (ctx->count < 21) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
    }
    o->size = 190.0f;
    if (ctx->count < 11) {
        o->state = 0;
    }
    return 0;
}

/* shape c056:01E04830, 52 insns: c056:01E04780 two-alpha twin: in by 32/16 while the scene value is under 16, out by 15 while the counter is under 21, ends under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 padC[0x46];
    s16 val;
} Ctx_c056_01E04830;

typedef struct {
    u8 pad0[0xA4];
    s16 state;
    u8 padA6[0x9];
    u8 alpha;
    u8 padB0[0x3];
    u8 alpha2;
    u8 padB4[0x6];
    u8 bA[1];
} Obj_c056_01E04830;

static s32 func_01E04830_c056(Ctx_c056_01E04830 *ctx, Obj_c056_01E04830 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 0x10) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x20;
        }
        if (o->alpha2 < 0x21) {
            o->alpha2 += 0x10;
        }
    }
    if (ctx->count < 0x15) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
        if (o->alpha2 > 0x10) {
            o->alpha2 -= 15;
        }
    }
    if (ctx->count < 0xb) {
        o->state = 0;
    }
    return 0;
}

/* shape c056:01E04900, 252 insns: a climber on the scene path (g+0x4270, 0x18-byte points from +0x118): its turn
   0xBA grows by 6 + g->h44C2 % 10 (mod 360); the first path point above it sets its two frames through
   func_001098E0 and raises 0xA8 / 0xAA by 7 / 6 while they are at most 13 x the point index; it climbs 3 a tick (its
   top following 18 below), then the top climbs on and stops it when above; while 0xBC is set and the top is above 0 it
   hands itself to the scene (g+0x448C ...) and, past scene step 13, respawns this handler; early steps grow it and
   blink it */

typedef struct {
    Vec4f p;
    f32 a, b;
} Pt_c056_01E04900;

typedef struct {
    u8 pad0[0x118];
    Pt_c056_01E04900 pt[9];
} Path_c056_01E04900;

typedef struct {
    u8 pad0[0x90];
    s32 w90;
} Link_c056_01E04900;

typedef struct {
    Vec4f v[4];
    Vec4f a40;
    u8 pad50[0x20];
    Vec4f a70;
    u8 pad80[0x14];
    Link_c056_01E04900 *link;
    u8 pad98[0xC];
    s16 hA4;
    u8 padA6[2];
    s16 hA8;
    s16 hAA;
    u8 padAC[3];
    u8 bAF;
    u8 padB0[0xA];
    s16 hBA;
    s16 hBC;
} Obj_c056_01E04900;

typedef struct {
    u8 pad0[0x80];
    s32 w80;
    s32 w84;
    s32 w88;
    u8 pad8C[0x64];
    Vec4f vF0;
    u8 pad100[0x4270 - 0x100];
    Path_c056_01E04900 path;
    u8 pad4400[0x4478 - 0x4270 - sizeof(Path_c056_01E04900)];
    s32 step;
    u8 pad447C[7];
    u8 b4483;
    u8 pad4484[8];
    Obj_c056_01E04900 *cur;
    u8 pad4490[0xC];
    f32 f449C;
    f32 f44A0;
    f32 f44A4;
    u8 pad44A8[0x12];
    s16 h44BA;
    s16 h44BC;
    u8 pad44BE[4];
    s16 h44C2;
    u8 pad44C4[4];
    s16 h44C8;
} G_c056_01E04900;

static s32 func_01E04900_c056(G_c056_01E04900 *g, Obj_c056_01E04900 *o) {
    extern void c056_01E012A0(G_c056_01E04900 *, s32 (*)());
    extern void func_001098E0(Vec4f *, Vec4f *, Obj_c056_01E04900 *, Pt_c056_01E04900 *, Pt_c056_01E04900 *);
    extern void func_00106BC0(void *, s32, s32);
    extern s32 func_00106B90(void *, s32, s32);
    Path_c056_01E04900 *path;
    s32 i;
    Pt_c056_01E04900 *cur;
    Pt_c056_01E04900 *prev;
    Vec4f a;
    Vec4f r1;
    Vec4f r2;

    path = &g->path;
    a.y = 0.0f;
    if (path == NULL) {
        return 0;
    }
    o->hBA += (s16)(g->h44C2 % 10 + 6);
    if (o->hBA >= 360) {
        o->hBA %= 360;
    }
    for (i = 1; i < 8; i++) {
        if (path->pt[i].p.y > o->v[0].y) {
            cur = &path->pt[i];
            a.x = path->pt[0].p.x;
            prev = &path->pt[i - 1];
            a.z = path->pt[0].p.z;
            func_001098E0(&r1, &a, o, prev, cur);
            o->a70 = r1;
            func_001098E0(&r2, &a, o, prev, cur);
            o->a40 = r2;
            if (o->hA8 <= i * 13) {
                o->hA8 += 7;
            }
            if (o->hAA <= i * 13) {
                o->hAA += 6;
            }
            i = 8;
        }
    }
    if (o->v[0].y <= path->pt[i - 4].p.y) {
        o->v[1].y = o->v[0].y += 3.0f;
        if (o->v[0].y - o->v[2].y >= 18.0f) {
            o->v[3].y = o->v[2].y += 3.0f;
        }
    } else {
        o->v[3].y = o->v[2].y += 3.0f;
        if (o->v[2].y > o->v[0].y) {
            if (o->link != NULL) {
                o->link->w90 = 0;
            }
            o->hA4 = 0;
        }
    }
    if (o->hBC > 0 && o->v[2].y > 0.0f) {
        g->cur = o;
        g->f449C = o->hAA;
        g->f44A0 = o->hAA - 3;
        g->b4483 = o->bAF;
        g->h44BC = 1;
        g->f44A4 = o->v[2].y;
        g->h44C8 = 1;
        g->vF0 = path->pt[0].p;
        g->w84 = 0;
        g->w80 = 0;
        g->w88 = 0;
        g->h44BA = o->hBA + 15;
        if (g->step > 13) {
            c056_01E012A0(g, func_01E04900_c056);
        }
        o->hBC = 0;
    }
    if (g->h44C2 < 16) {
        func_00106BC0(o, 0x17, 0xA0);
    }
    if (g->step < 21) {
        o->hA8 += 3;
        o->hAA += 3;
        if (func_00106B90(o, 0xE, 0xF) != 0) {
            o->hA4 = 0;
        }
    }
    if (g->step < 11) {
        o->hA4 = 0;
    }
    return 0;
}

/* shape c056:01E04CF0, 188 insns: c056:01E03DA0 family hovering ring: bobs 2 along a 6-a-tick sine (func_001A6A88) at 0x4/0x14, shrinks 0xA8 to 10 and 0xA0 to 10, then 0xAA to 12; once shrunk sinks 4 to 50 fading both alphas by 15, then frees itself (clearing its owner's 0x90); on wait 1 hands itself to the scene light (0x448C, level 90, 70, colour 100/80/50) and from scene time 19 spawns c056:01E01490; early (count < 16) it calls func_00106BC0, before time 21 grows 0xA8/0xAA by 3 until func_00106B90 says done, after that fades in by 19 to 100 */

typedef struct {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0x4478 - 0x88];
    s32 timer;
    u8 pad447C[7];
    u8 c4483;
    u8 pad4484[8];
    void *owner;
    u8 pad4490[0x44B8 - 0x4490];
    s16 h44B8;
    s16 h44BA;
    u8 pad44BC[6];
    s16 count;
} Scene_c056_01E04CF0;

typedef struct {
    u8 pad0[0x90];
    s32 w90;
} Own_c056_01E04CF0;

typedef struct {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 y14;
    u8 pad18[0x7C];
    Own_c056_01E04CF0 *own;
    u8 pad98[8];
    f32 fA0;
    s16 hA4;
    u8 padA6[2];
    s16 hA8;
    s16 hAA;
    u8 colAC[4];
    u8 colB0[4];
    u8 padB4[6];
    s16 ang;
    u8 padBC[2];
    s16 wait;
} Fx_c056_01E04CF0;

extern void c056_01E01490(Scene_c056_01E04CF0 *, s32 (*)(Scene_c056_01E04CF0 *, Fx_c056_01E04CF0 *));

#pragma opt_propagation off

static s32 func_01E04CF0_c056(Scene_c056_01E04CF0 *g, Fx_c056_01E04CF0 *o) {
    f32 w;
    extern f32 func_001A6A88(f32);
    extern void func_00107EA0(void *, f32, f32, f32);
    extern void func_00106BC0(void *, s32, s32);
    extern s32 func_00106B90(void *, s32, s32);

    o->ang += 6;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    o->y14 = o->y = o->y + 2.0f * func_001A6A88(3.1415927f * o->ang / 180.0f);
    if (o->hA8 > 10) {
        o->hA8 -= 2;
    }
    if (o->fA0 > 10.0f) {
        o->fA0 -= 2.0f;
    }
    if (o->hAA > 12) {
        o->hAA -= 2;
    } else if (o->y > 50.0f) {
        o->y14 = o->y = o->y - 4.0f;
        if (o->colAC[3] > 16) {
            o->colAC[3] -= 15;
        }
        if (o->colB0[3] > 16) {
            o->colB0[3] -= 15;
        }
    } else {
        if (o->own != NULL) {
            if (o->own != NULL) {
                o->own->w90 = 0;
            }
            o->hA4 = 0;
        }
        o->hA4 = 0;
    }
    if (o->wait == 1) {
        g->owner = o;
        g->h44BA = 90;
        g->f84 = 70.0f;
        g->c4483 = 0;
        g->h44B8 = 100;
        w = 80.0f;
        func_00107EA0(g, 100.0f, w, 50.0f);
        if (g->timer > 18) {
            c056_01E01490(g, func_01E04CF0_c056);
        }
    }
    if (g->count < 16) {
        func_00106BC0(o, 15, 0x80);
    } else if (g->timer < 21) {
        o->hA8 += 3;
        o->hAA += 3;
        if (func_00106B90(o, 14, 15) != 0) {
            o->hA4 = 0;
        }
    } else if (o->hAA > 12) {
        if (o->colAC[3] < 100) {
            o->colAC[3] += 19;
        }
        if (o->colB0[3] < 100) {
            o->colB0[3] += 19;
        }
    }
    if (o->wait != 0) {
        o->wait--;
    }
    if (g->timer < 11) {
        o->hA4 = 0;
    }
    return 0;
}
#pragma opt_propagation reset

/* shape c056:01E04FE0, 252 insns: a climber on the scene path (g+0x4270, 0x18-byte points from +0x118): its turn
   0xBA grows by 6 + g->h44C2 % 10 (mod 360); the first path point above it sets its two frames through
   func_001098E0 and raises 0xA8 / 0xAA by 18 / 17 while they are at most 25 x the point index; it climbs 3 a tick (its
   top following 18 below), then the top climbs on and stops it when above; while 0xBC is set and the top is above 0 it
   hands itself to the scene (g+0x448C ...) and, past scene step 8, respawns this handler; early steps grow it and
   blink it */

typedef struct {
    Vec4f p;
    f32 a, b;
} Pt_c056_01E04FE0;

typedef struct {
    u8 pad0[0x118];
    Pt_c056_01E04FE0 pt[9];
} Path_c056_01E04FE0;

typedef struct {
    u8 pad0[0x90];
    s32 w90;
} Link_c056_01E04FE0;

typedef struct {
    Vec4f v[4];
    Vec4f a40;
    u8 pad50[0x20];
    Vec4f a70;
    u8 pad80[0x14];
    Link_c056_01E04FE0 *link;
    u8 pad98[0xC];
    s16 hA4;
    u8 padA6[2];
    s16 hA8;
    s16 hAA;
    u8 padAC[3];
    u8 bAF;
    u8 padB0[0xA];
    s16 hBA;
    s16 hBC;
} Obj_c056_01E04FE0;

typedef struct {
    u8 pad0[0x80];
    s32 w80;
    s32 w84;
    s32 w88;
    u8 pad8C[0x64];
    Vec4f vF0;
    u8 pad100[0x4270 - 0x100];
    Path_c056_01E04FE0 path;
    u8 pad4400[0x4478 - 0x4270 - sizeof(Path_c056_01E04FE0)];
    s32 step;
    u8 pad447C[7];
    u8 b4483;
    u8 pad4484[8];
    Obj_c056_01E04FE0 *cur;
    u8 pad4490[0xC];
    f32 f449C;
    f32 f44A0;
    f32 f44A4;
    u8 pad44A8[0x12];
    s16 h44BA;
    s16 h44BC;
    u8 pad44BE[4];
    s16 h44C2;
    u8 pad44C4[4];
    s16 h44C8;
} G_c056_01E04FE0;

static s32 func_01E04FE0_c056(G_c056_01E04FE0 *g, Obj_c056_01E04FE0 *o) {
    extern void c056_01E012A0(G_c056_01E04FE0 *, s32 (*)());
    extern void func_001098E0(Vec4f *, Vec4f *, Obj_c056_01E04FE0 *, Pt_c056_01E04FE0 *, Pt_c056_01E04FE0 *);
    extern void func_00106BC0(void *, s32, s32);
    extern s32 func_00106B90(void *, s32, s32);
    Path_c056_01E04FE0 *path;
    s32 i;
    Pt_c056_01E04FE0 *cur;
    Pt_c056_01E04FE0 *prev;
    Vec4f a;
    Vec4f r1;
    Vec4f r2;

    path = &g->path;
    a.y = 0.0f;
    if (path == NULL) {
        return 0;
    }
    o->hBA += (s16)(g->h44C2 % 10 + 6);
    if (o->hBA >= 360) {
        o->hBA %= 360;
    }
    for (i = 1; i < 8; i++) {
        if (path->pt[i].p.y > o->v[0].y) {
            cur = &path->pt[i];
            a.x = path->pt[0].p.x;
            prev = &path->pt[i - 1];
            a.z = path->pt[0].p.z;
            func_001098E0(&r1, &a, o, prev, cur);
            o->a70 = r1;
            func_001098E0(&r2, &a, o, prev, cur);
            o->a40 = r2;
            if (o->hA8 <= i * 25) {
                o->hA8 += 18;
            }
            if (o->hAA <= i * 25) {
                o->hAA += 17;
            }
            i = 8;
        }
    }
    if (o->v[0].y <= path->pt[i - 4].p.y) {
        o->v[1].y = o->v[0].y += 3.0f;
        if (o->v[0].y - o->v[2].y >= 18.0f) {
            o->v[3].y = o->v[2].y += 3.0f;
        }
    } else {
        o->v[3].y = o->v[2].y += 3.0f;
        if (o->v[2].y > o->v[0].y) {
            if (o->link != NULL) {
                o->link->w90 = 0;
            }
            o->hA4 = 0;
        }
    }
    if (o->hBC > 0 && o->v[2].y > 0.0f) {
        g->cur = o;
        g->f449C = o->hAA;
        g->f44A0 = o->hAA - 3;
        g->b4483 = o->bAF;
        g->h44BC = 1;
        g->f44A4 = o->v[2].y;
        g->h44C8 = 1;
        g->vF0 = path->pt[0].p;
        g->w84 = 0;
        g->w80 = 0;
        g->w88 = 0;
        g->h44BA = o->hBA + 15;
        if (g->step > 8) {
            c056_01E012A0(g, func_01E04FE0_c056);
        }
        o->hBC = 0;
    }
    if (g->h44C2 < 16) {
        func_00106BC0(o, 0x17, 0xA0);
    }
    if (g->step < 21) {
        o->hA8 += 3;
        o->hAA += 3;
        if (func_00106B90(o, 0xE, 0xF) != 0) {
            o->hA4 = 0;
        }
    }
    if (g->step < 11) {
        o->hA4 = 0;
    }
    return 0;
}
