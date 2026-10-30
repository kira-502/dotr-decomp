#include "common.h"

/* shape c034:01E00080, 132 insns: scene step: grey scene colour (alpha 0), 0xDDA 20; on the first frame the colour is
   picked by the scene's colour kind (0..9: white, white, green, blue, yellow, magenta, cyan, pink, purple, orange; else
   white), the scene size set to 200 and the effect chain started (c034:01E00610, handler 0x1E00290); 0xF4 = -20 */

typedef struct {
    u8 pad0[0x80];
    f32 size;
    u8 pad84[0x70];
    s32 wF4;
    u8 padF8[0xC80];
    u8 col[4];
    u8 padD7C[8];
    s32 wD84;
    u8 padD88[0x44];
    s16 kind;
    u8 padDCE[2];
    s16 t;
    u8 padDD2[8];
    s16 hDDA;
} Scene_c034_01E00080;

static void func_01E00080_c034(Scene_c034_01E00080 *g) {
    extern void c034_01E00290();
    extern void c034_01E00610(Scene_c034_01E00080 *, void *);
    extern void func_001076F0(void *, s32, s32, s32);

    g->col[0] = 0x80;
    g->col[1] = 0x80;
    g->col[2] = 0x80;
    g->col[3] = 0;
    g->hDDA = 20;
    g->t++;
    if (g->t == 1) {
        if (g->kind == 0) {
            func_001076F0(g->col, 0xFF, 0xFF, 0xFF);
        } else if (g->kind == 1) {
            func_001076F0(g->col, 0xFF, 0xFF, 0xFF);
        } else if (g->kind == 2) {
            func_001076F0(g->col, 0, 0xFF, 0);
        } else if (g->kind == 3) {
            func_001076F0(g->col, 0, 0, 0xFF);
        } else if (g->kind == 4) {
            func_001076F0(g->col, 0xFF, 0xFF, 0);
        } else if (g->kind == 5) {
            func_001076F0(g->col, 0xFF, 0, 0xFF);
        } else if (g->kind == 6) {
            func_001076F0(g->col, 0, 0xFF, 0xFF);
        } else if (g->kind == 7) {
            func_001076F0(g->col, 0xFF, 0x80, 0xFF);
        } else if (g->kind == 8) {
            func_001076F0(g->col, 0x80, 0, 0xFF);
        } else if (g->kind == 9) {
            func_001076F0(g->col, 0xFF, 0x80, 0);
        } else {
            func_001076F0(g->col, 0xFF, 0xFF, 0xFF);
        }
        g->size = 200.0f;
        g->wD84 = 0;
        c034_01E00610(g, c034_01E00290);
    }
    g->wF4 = -20;
}

/* shape c034:01E00290, 45 insns: both alphas grow by 0x20 (below 0xB0) until the game step at 0xDD0 reaches 0x12;
   then phase 0 sets 0x1E = 3 and moves to phase 1, which fades both by 0x10 and stops */

typedef struct {
    u8 pad0[0xDD0];
    s16 step;
} Game_c034_01E00290;

typedef struct {
    u8 pad0[0x14];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f1E;
    s16 phase;
} Fx_c034_01E00290;

static s32 func_01E00290_c034(Game_c034_01E00290 *g, Fx_c034_01E00290 *o) {
    if (g->step < 0x12) {
        if (o->col[3] < 0xB0) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0xB0) {
            o->col2[3] += 0x20;
        }
    } else if (o->phase == 0) {
        o->f1E = 3;
        o->phase = 1;
    } else if (o->phase == 1) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape c034:01E00350 (c034), 176 insns, 1 copy: c015:01E002E0 family scene step: on a code (>= 0) clears the scene,
   fills a 91-entry table (ctx+0xDDC) with func_001A6A88 of each degree in radians, keeps the code and a 43-tick
   timer; else steps it (c034:01E00080) and, from stage 9, runs the 10 slots' step callbacks, aims the camera 50
   above the model's anchor (func_001E11B0) and 32 to one side, sets the light levels 0.6/0.3/0.6 and draws each slot
   twice; under stage 8 burns 22 func_001F5380 calls; returns 8 when the timer runs out */

typedef struct {
    f32 x, y, z, w;
} V4_c034_01E00350;

typedef struct Slot_c034_01E00350 {
    u8 pad0[8];
    void (*draw)(void *, struct Slot_c034_01E00350 *, void *, s32);
    void (*fn)(void *, struct Slot_c034_01E00350 *);
    u8 pad10[0xC];
    s16 used;
    u8 pad1E[6];
} Slot_c034_01E00350;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x90];
    f32 fD0;
    f32 fD4;
    f32 fD8;
    u8 padDC[0x110 - 0xDC];
    Slot_c034_01E00350 slot[10];
    u8 pad278[0xD74 - 0x278];
    s32 timer;
    u8 padD78[8];
    s32 ot;
    u8 padD84[0xDCC - 0xD84];
    s16 code;
    u8 padDCE[2];
    s16 stage;
    u8 padDD2[0xDDC - 0xDD2];
    f32 tbl[91];
} Ctx_c034_01E00350;

extern void c034_01E00080(Ctx_c034_01E00350 *, s32);

static s32 func_01E00350_c034(s32 arg0, s32 code) {
    Ctx_c034_01E00350 *g = (Ctx_c034_01E00350 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_001E11B0(s32, s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    V4_c034_01E00350 a;
    V4_c034_01E00350 b;
    u8 pkt[0x90];
    s32 i;
    s32 k;
    void (*d)(void *, Slot_c034_01E00350 *, void *, s32);

    g->ot = func_00207500();
    if (code >= 0) {
        b.x = b.y = b.z = 0.0f;
        func_00195108(g, 0xF50);
        for (i = 0; i < 91; i++) {
            g->tbl[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->code = code;
        g->timer = 43;
        return 0;
    }
    c034_01E00080(g, 0);
    if (g->stage > 8) {
        for (i = 0; i < 10; i++) {
            if (g->slot[i].used != 0) {
                if (g->slot[i].fn != NULL) {
                    g->slot[i].fn(g, &g->slot[i]);
                }
            }
        }
        func_001F5BD0(func_001F5380(), &a);
        k = func_001F5380() >> 8;
        func_001E11B0(k, func_001F5380() & 0xF, &a);
        b.x = a.x;
        b.y = a.y;
        b.z = a.z;
        b.y += 50.0f;
        if (func_001F5380() >> 8 == 0) {
            b.z -= 32.0f;
        } else {
            b.z += 32.0f;
        }
        g->fD8 = 0.6f;
        g->fD0 = 0.6f;
        g->fD4 = 0.3f;
        func_0020EB40(g->cam);
        func_0020C940(g, NULL, NULL, &b);
        func_0020BC00(g->cam, g);
        for (i = 0; i < 10; i++) {
            if (g->slot[i].used != 0) {
                d = g->slot[i].draw;
                if (g->slot[i].draw != NULL) {
                    d(g, &g->slot[i], pkt, 0);
                    d(g, &g->slot[i], pkt, 1);
                }
            }
        }
    }
    if (g->stage < 8) {
        for (i = 0; i < 22; i++) {
            func_001F5380();
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}


/* shape c034:01E00610, 75 insns: take the first free light slot of 10 (0x24 bytes each, at ctx+0x110), clear it, mark it with its index + 1, give it the scene colour twice, handler shape c034:01E00740 and the argument; the scene keeps it as current */

typedef struct {
    u8 pad0[8];
    s32 fn;
    s32 arg;
    u8 pad10[4];
    u8 col[4];
    u8 col2[4];
    s16 used;
    s16 h1E;
    u8 pad20[4];
} Slot_c034_01E00610;

typedef struct {
    u8 pad0[0x110];
    Slot_c034_01E00610 slot[10];
    u8 pad278[0xD70 - 0x278];
    u8 cur[4];
    u8 pad74[4];
    u8 rgba[4];
    u8 padD7C[8];
    Slot_c034_01E00610 *last;
} Ctx_c034_01E00610;

static void func_01E00610_c034(Ctx_c034_01E00610 *ctx, s32 arg) {
    extern void c034_01E00740();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Slot_c034_01E00610 *s;

    s = NULL;
    for (i = 0; i < 10; i++) {
        if (ctx->slot[i].used == 0) {
            s = &ctx->slot[i];
            func_00195108(s, 0x24);
            ctx->slot[i].used = i + 1;
            i = 10;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->col[3] = ctx->rgba[3];
        func_001076F0(s->col2, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->col2[3] = ctx->rgba[3];
        s->h1E = 1;
        ctx->cur[0] = ctx->rgba[0];
        ctx->cur[1] = ctx->rgba[1];
        ctx->cur[2] = ctx->rgba[2];
        ctx->cur[3] = 0;
        s->fn = (s32)c034_01E00740;
        s->arg = arg;
        ctx->last = s;
    }
}

/* shape c034:01E00740, 266 insns: the c034 light slot's draw (handler set by c034:01E00610): mode 0 builds a 4-corner
   colour packet from the scene's current colour; otherwise it draws a 9 x 18 dome of quads (rings of radius
   35 - 0.389 x latitude, height 16 x sin, 20 degrees apart), turned 90 or -90 by the camera's side, its alpha rising
   by a ninth of the slot's alpha per ring, each quad submitted 0x1E times (slot field) */

typedef struct {
    u8 pad0[0x14];
    u8 col[4];
    u8 pad18[6];
    s16 count;
} Slot_c034_01E00740;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16, y : 16, z : 24, f : 8;
} Vtx_c034_01E00740;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c034_01E00740 v[4];
} Pkt_c034_01E00740;

typedef struct {
    u8 pad0[0x40];
    f32 m[16];
    u8 pad80[0x70];
    s32 turn;
    u8 padF4[0xD70 - 0xF4];
    u8 cur[4];
    u8 padD74[0xC];
    s32 ot;
    u8 padD84[0xDB0 - 0xD84];
    f32 depth;
    u8 padDB4[0xDDC - 0xDB4];
    u8 trig[1];
} Ctx_c034_01E00740;

static void func_01E00740_c034(Ctx_c034_01E00740 *g, Slot_c034_01E00740 *s, Pkt_c034_01E00740 *p, s32 mode) {
    extern void func_00107710(void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F5380(void);
    extern void func_00108950(void *, s32 *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    s16 a;
    s16 b;
    s32 j;
    s32 k;
    s32 n;
    s32 a20;
    f32 y;

    a = 0;
    b = 0;
    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        func_00107710(&p->v[0], g->cur);
        func_00107710(&p->v[1], g->cur);
        func_00107710(&p->v[2], g->cur);
        func_00107710(&p->v[3], g->cur);
        p->v[0].q = p->v[1].q = p->v[2].q = p->v[3].q = 1.0f;
        p->v[0].f = 0;
        p->v[1].f = 0;
        p->v[2].f = 0;
        p->v[3].f = 0;
        return;
    }
    for (k = 0; k < 9; k++) {
        for (j = 0; j < 18; j++) {
            a20 = a + 20;
            q[0].x = (35.0f - 0.3888889f * (b + 10)) * func_00108030(g->trig, a20, 1);
            q[0].z = (35.0f - 0.3888889f * (b + 10)) * func_00108030(g->trig, a20, 0);
            q[2].x = (35.0f - 0.3888889f * b) * func_00108030(g->trig, a20, 1);
            q[2].z = (35.0f - 0.3888889f * b) * func_00108030(g->trig, a20, 0);
            q[1].x = (35.0f - 0.3888889f * (b + 10)) * func_00108030(g->trig, a, 1);
            q[1].z = (35.0f - 0.3888889f * (b + 10)) * func_00108030(g->trig, a, 0);
            q[3].x = (35.0f - 0.3888889f * b) * func_00108030(g->trig, a, 1);
            q[3].z = (35.0f - 0.3888889f * b) * func_00108030(g->trig, a, 0);
            y = 16.0f * func_00108030(g->trig, b + 10, 0);
            q[0].y = y;
            q[1].y = y;
            y = 16.0f * func_00108030(g->trig, b, 0);
            q[3].y = y;
            q[2].y = y;
            if ((func_001F5380() >> 8) == 0) {
                g->turn = 90;
            } else {
                g->turn = -90;
            }
            func_00108950(&q[0], &g->turn, 1, g->trig);
            func_00108950(&q[1], &g->turn, 1, g->trig);
            func_00108950(&q[2], &g->turn, 1, g->trig);
            func_00108950(&q[3], &g->turn, 1, g->trig);
            g->cur[3] = (k + 1) * (s->col[3] / 9);
            func_00107710(&p->v[0], g->cur);
            func_00107710(&p->v[1], g->cur);
            g->cur[3] = k * (s->col[3] / 9);
            func_00107710(&p->v[2], g->cur);
            func_00107710(&p->v[3], g->cur);
            if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
                for (n = 0; n < s->count; n++) {
                    func_002075F0(p, g->ot, (u32)g->depth);
                }
            }
            a += 20;
        }
        b += 10;
    }
}
