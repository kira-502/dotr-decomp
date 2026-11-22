#include "common.h"

/* shape c020:01E00080, 79 insns: spawn this tick's rain drops: 10/15/20/25 by the weather level (0 otherwise), each at a random x/z in -150..189 and height 170, through shape c020:01E006F0 with handler c020:01E001C0 once the scene state reaches 19 */

typedef struct {
    u8 pad0[0x80];
    f32 x, y, z;
    u8 pad8C[0x3190 - 0x8C];
    s32 state;
    u8 pad3194[0x320E - 0x3194];
    s16 level;
    u8 pad3210[2];
    s16 tick;
    u8 pad3214[6];
    s16 n;
} Ctx_c020_01E00080;

static void func_01E00080_c020(Ctx_c020_01E00080 *ctx) {
    extern void c020_01E001C0();
    extern void c020_01E006F0(Ctx_c020_01E00080 *, void *);
    s32 i;

    ctx->tick++;
    if (ctx->level == 0) {
        ctx->n = 10;
    } else if (ctx->level == 1) {
        ctx->n = 15;
    } else if (ctx->level == 2) {
        ctx->n = 20;
    } else if (ctx->level == 3) {
        ctx->n = 25;
    } else {
        ctx->n = 0;
    }
    for (i = 0; i < ctx->n; i++) {
        ctx->x = func_0019A5C8() % 340 - 150;
        ctx->z = func_0019A5C8() % 340 - 150;
        ctx->y = 170.0f;
        if (ctx->state > 18) {
            c020_01E006F0(ctx, c020_01E001C0);
        }
    }
}

/* shape c020:01E001C0, 80 insns: a falling piece: 0x26 grows by its speed (0x22) below 0x3C; the position moves by
   (-0x20, -0x22, -0x24); once below -30 it hands its position to the scene (0x80) once and, unless the scene flag
   0x320E is set, spawns a c020:01E00300 effect through c020:01E00990; then it ends (also below scene counter 2) */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E001C0;

typedef struct {
    V4_c020_01E001C0 pos;
    u8 pad10[0x10];
    s16 vx;
    s16 vy;
    s16 vz;
    s16 f26;
    u8 pad28[4];
    s16 mode;
    s16 done;
} Fx_c020_01E001C0;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E001C0 pos;
    u8 pad90[0x3190 - 0x90];
    s32 count;
    u8 pad3194[0x7A];
    s16 flag;
} Scene_c020_01E001C0;

static s32 func_01E001C0_c020(Scene_c020_01E001C0 *g, Fx_c020_01E001C0 *o) {
    extern void c020_01E00300(void);
    extern void c020_01E00990(void *, s32);
    if (o->f26 < 0x3C) {
        o->f26 += o->vy;
    }
    o->pos.y -= o->vy;
    o->pos.x -= o->vx;
    o->pos.z -= o->vz;
    if (o->pos.y < -30.0f) {
        if (o->done == 0) {
            g->pos = o->pos;
            if (g->flag == 0) {
                c020_01E00990(g, (s32)c020_01E00300);
            }
            o->done = 1;
        }
    }
    if (o->pos.y < -30.0f) {
        o->mode = 0;
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c020:01E00300, 48 insns: a rising wave: height 4 * sine of its angle (table at ctx+0x3250); the angle steps by 30 up to 180 while it grows; past 90 both levels drop by 28 down to 30, ending it */

typedef struct {
    u8 pad0[0x28];
    s16 h28;
    s16 h2A;
    s16 h2C;
    s16 ang;
    s16 h30;
    s16 h32;
    s16 h34;
} Wave_c020_01E00300;

static s32 func_01E00300_c020(u8 *ctx, Wave_c020_01E00300 *o) {
    extern f32 func_00108030(void *, s16, s32);

    o->h30 = 4.0f * func_00108030(ctx + 0x3250, o->ang, 0);
    if (o->ang < 180) {
        o->ang += 30;
        o->h34++;
        o->h32 += 2;
    }
    if (o->ang > 90) {
        if (o->h28 > 30) {
            o->h28 -= 28;
        }
        if (o->h2A > 30) {
            o->h2A -= 28;
        } else {
            o->h2C = 0;
        }
    }
    return 0;
}

/* shape c020:01E003C0 (c020), 203 insns, 1 copy: the c020 module's main step (c017:01E010C0 family): with a code it
   clears the scene, fills the 0..90 degree table and four 9-step tables at i * 40 and i * 40 + 40 degrees, keeps the
   code and a 90-tick timer; otherwise it runs the scene setup, steps the 220 entries (c020:01E001C0 for plain ones;
   others swing 4 x the table at their phase, the phase climbs 30 to 180 while two counters grow, and past 90 both
   sizes shrink by 28 until it ends), then draws each live one twice through c020:01E00A80 or c020:01E00E50; counts
   down and returns 8 at the end */

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[0x14];
    s16 h28;
    s16 h2A;
    s16 used;
    s16 phase;
    s16 h30;
    s16 h32;
    s16 h34;
    u8 pad36[2];
} Ent_c020_01E003C0;

typedef struct {
    u8 pad0[0x170];
    Ent_c020_01E003C0 ent[220];
    s32 timer;
    u8 pad3194[8];
    s32 ot;
    u8 pad31A0[0x320E - 0x31A0];
    s16 code;
    u8 pad3210[0x3250 - 0x3210];
    f32 tab[91];
    f32 s0[10];
    f32 c0[10];
    f32 s1[10];
    f32 c1[10];
} Ctx_c020_01E003C0;

static s32 func_01E003C0_c020(s32 arg0, s32 code) {
    Ctx_c020_01E003C0 *g = (Ctx_c020_01E003C0 *)arg0;
    extern s32 func_00207500(void);
    extern void c020_01E00080(Ctx_c020_01E003C0 *, s32);
    extern void c020_01E001C0(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *);
    extern void c020_01E00A80(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *, void *, s32);
    extern void c020_01E00E50(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *, void *, s32);
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern f32 func_001A6898(f32);
    extern f32 func_00108030(void *, s16, s32);
    s32 n;
    u8 pkt[0x90];
    s32 i;
    f32 t;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3460);
        for (i = 0; i < 91; i++) {
            g->tab[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        for (i = 0; i < 9; i++) {
            t = 3.1415927f * (i * 40) / 180.0f;
            g->s0[i] = func_001A6A88(t);
            g->c0[i] = func_001A6898(t);
            t = 3.1415927f * (i * 40 + 40) / 180.0f;
            g->s1[i] = func_001A6A88(t);
            g->c1[i] = func_001A6898(t);
        }
        g->code = code;
        g->timer = 90;
        return 0;
    }
    c020_01E00080(g, 0);
    for (i = 0; i < 220; i++) {
        if (g->ent[i].used != 0) {
            if (g->ent[i].f10 == 0) {
                c020_01E001C0(g, &g->ent[i]);
            } else {
                g->ent[i].h30 = 4.0f * func_00108030(g->tab, g->ent[i].phase, 0);
                if (g->ent[i].phase < 180) {
                    g->ent[i].phase += 30;
                    g->ent[i].h34 += 1;
                    g->ent[i].h32 += 2;
                }
                if (g->ent[i].phase > 90) {
                    if (g->ent[i].h28 > 30) {
                        g->ent[i].h28 -= 28;
                    }
                    if (g->ent[i].h2A > 30) {
                        g->ent[i].h2A -= 28;
                    } else {
                        g->ent[i].used = 0;
                    }
                }
            }
        }
    }
    for (i = 0; i < 220; i++) {
        if (g->ent[i].used != 0) {
            n++;
            if (g->ent[i].f10 == 0) {
                c020_01E00A80(g, &g->ent[i], pkt, 0);
                c020_01E00A80(g, &g->ent[i], pkt, 1);
            } else {
                c020_01E00E50(g, &g->ent[i], pkt, 0);
                c020_01E00E50(g, &g->ent[i], pkt, 1);
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* OVL_WARM */

/* shape c020:01E006F0, 168 insns: b582:01E04440's slot grab for 220 slots at +0x170 with no argument or result: the
   slot gets colour 0xFF/0, the scene point (0x80) and three x/z pairs scattered by -75..74, a size 24..33, a step
   2..5 (signed %4) and a speed 1..2 */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E006F0;

typedef struct {
    V4_c020_01E006F0 pos;
    u8 pad10[4];
    s16 x0;
    s16 x1;
    s16 x2;
    s16 z0;
    s16 z1;
    s16 z2;
    s16 step;
    s16 size;
    s16 speed;
    u8 pad26[2];
    s16 c28;
    s16 c2A;
    s16 used;
    u8 pad2E[0xA];
} Slot_c020_01E006F0;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E006F0 pt;
    u8 pad90[0xE0];
    Slot_c020_01E006F0 slot[220];
} Scene_c020_01E006F0;

static void func_01E006F0_c020(Scene_c020_01E006F0 *g) {
    extern void func_00195108(void *, s32);
    s16 i;
    Slot_c020_01E006F0 *s;

    s = NULL;
    for (i = 0; i < 220; i++) {
        if (g->slot[i].used == 0) {
            s = &g->slot[i];
            func_00195108(s, 0x38);
            g->slot[i].used = 1;
            i = 220;
        }
    }
    if (s != NULL) {
        s->c28 = 0xFF;
        s->c2A = 0;
        s->pos = g->pt;
        s->x0 = g->pt.x;
        s->z0 = g->pt.z;
        s->x1 = g->pt.x;
        s->z1 = g->pt.z;
        s->x2 = g->pt.x;
        s->z2 = g->pt.z;
        s->x0 += (s16)(func_0019A5C8() % 150 - 75);
        s->z0 += (s16)(func_0019A5C8() % 150 - 75);
        s->x1 += (s16)(func_0019A5C8() % 150 - 75);
        s->z1 += (s16)(func_0019A5C8() % 150 - 75);
        s->x2 += (s16)(func_0019A5C8() % 150 - 75);
        s->z2 += (s16)(func_0019A5C8() % 150 - 75);
        s->size = func_0019A5C8() % 10 + 24;
        s->step = func_0019A5C8() % 4 + 2;
        s->speed = func_0019A5C8() % 2 + 1;
    }
}

/* shape c020:01E00990, 60 insns: take a free slot (0xDC of 0x38 bytes at 0x170), clear it, set 0x28/0x2A = 0x60,
   copy the object's vector at 0x80, store arg and 0x22 = -10 */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E00990;

typedef struct {
    V4_c020_01E00990 pos;
    s32 arg;
    u8 pad14[0xE];
    s16 f22;
    u8 pad24[4];
    s16 f28;
    s16 f2A;
    s16 used;
    u8 pad2E[0xA];
} Slot_c020_01E00990;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E00990 pos;
    u8 pad90[0xE0];
    Slot_c020_01E00990 slots[0xDC];
} Obj_c020_01E00990;

static void func_01E00990_c020(Obj_c020_01E00990 *obj, s32 arg) {
    extern void func_00195108();
    Slot_c020_01E00990 *s = NULL;
    s16 i;

    for (i = 0; i < 0xDC; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x38);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xDC;
        }
    }
    if (s != NULL) {
        s->f28 = 0x60;
        s->f2A = 0x60;
        s->pos = obj->pos;
        s->arg = arg;
        s->f22 = -10;
    }
}

/* OVL_WARM */

/* shape c020:01E00A80, 243 insns: b582:01E047C0's line strip in two passes: with draw 0 it sets up the packet (the
   scene colour data ctx+0x3194, mode 9 when ctx+0x320E is set; the vertex colours from that colour with alphas an+0x28 /
   an+0x2A); otherwise it draws 1, 2 or 3 segments (by the height an+0x26: under 20, under 40, else) from the anchor,
   the first stretched by the segment count, the others offset by the per-segment x/z and stretched by 3; depth in
   ctx+0x31E8, drawn into ctx+0x319C */

typedef struct {
    u8 r, g, b, a;
} Col_c020_01E00A80;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c020_01E00A80;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    struct {
        Rgbaq_c020_01E00A80 c;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[2];
} Pkt_c020_01E00A80;

typedef struct {
    u8 pad0[0x3194];
    u8 rgb[8];
    s32 ot;
    u8 pad31A0[0x31E8 - 0x31A0];
    f32 depth;
    u8 pad31EC[0x320E - 0x31EC];
    s16 mode;
} Obj_c020_01E00A80;

typedef struct {
    Vec4f pos;
    u8 pad10[4];
    s16 dx[3];
    s16 dz[3];
    s16 h20;
    u8 pad22[2];
    s16 h24;
    s16 h26;
    u8 a0;
    u8 pad29;
    u8 a1;
} Line_c020_01E00A80;

static void func_01E00A80_c020(Obj_c020_01E00A80 *o, Line_c020_01E00A80 *an, Pkt_c020_01E00A80 *p, s32 draw) {
    extern void func_00107EC0(void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern Rgbaq_c020_01E00A80 func_00107740(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern Col_c020_01E00A80 D_01E01200_c020;
    Col_c020_01E00A80 c = D_01E01200_c020;
    Vec4f q[4];
    s32 i;
    s16 n;

    if (draw == 0) {
        if (o->mode == 0) {
            func_00107EC0(o->rgb, 0, 0);
        } else {
            func_00107EC0(o->rgb, 0, 9);
        }
        func_001076F0(&c, o->rgb[0], o->rgb[1], o->rgb[2]);
        p->count = 0x11;
        p->tag = 4;
        p->regs = 0x4141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[1].c.q = 1.0f;
        p->v[0].c.q = 1.0f;
        p->v[0].f = 0;
        p->v[1].f = 0;
        c.a = an->a0;
        p->v[0].c = func_00107740(&c);
        c.a = an->a1;
        p->v[1].c = func_00107740(&c);
    } else {
        if (an->h26 < 20) {
            n = 1;
        } else if (an->h26 < 40) {
            n = 2;
        } else {
            n = 3;
        }
        for (i = 0; i < n; i++) {
            if (i == 0) {
                q[0] = an->pos;
                q[1] = an->pos;
                q[1].y += an->h26;
                q[1].x += an->h20 * n;
                q[1].z += an->h24 * n;
            } else {
                q[0] = an->pos;
                q[1] = an->pos;
                q[0].x += an->dx[i - 1];
                q[0].z += an->dz[i - 1];
                q[1].x += an->dx[i - 1];
                q[1].z += an->dz[i - 1];
                q[1].y += an->h26;
                q[1].x += an->h20 * 3;
                q[1].z += an->h24 * 3;
            }
            if (func_00205630(q, 0x70000000, 0, p, &o->depth) != 0) {
                func_002075F0(p, o->ot, (u32)o->depth);
            }
        }
    }
}

/* OVL_WARM */

/* shape c020:01E00E50, 219 insns: two-pass ring strip: mode 0 sets the material (blend 0x48, the scene's colour
   0x3194 with the effect's alpha 0x28 on the inner and 0x2A on the outer corners, q = 1, fog 0); other modes build
   9 quads from the scene's cos/sin tables (0x33BC/0x33E4) between radius h32 and h34 at heights h30 / 0, angle
   step 40, moved to the effect's x/z and drawn once each */

typedef struct {
    f32 x, y, z, w;
} Vec_c020_01E00E50;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c020_01E00E50;

typedef struct {
    Rgbaq_c020_01E00E50 c;
    u8 xyz[8];
} Vtx_c020_01E00E50;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c020_01E00E50 v[4];
} Pkt_c020_01E00E50;

typedef struct {
    f32 x, y, z;
    u8 pad0C[0x1C];
    u8 b28;
    u8 pad29;
    u8 b2A;
    u8 pad2B[5];
    s16 h30;
    s16 h32;
    s16 h34;
} Fx_c020_01E00E50;

typedef struct {
    u8 pad0[0x130];
    Vec_c020_01E00E50 q[4];
    u8 pad170[0x3194 - 0x170];
    u8 b3194[8];
    s32 ot;
    u8 pad31A0[0x48];
    f32 depth;
    u8 pad31EC[0x22];
    s16 h320E;
    u8 pad3210[0x40];
    u8 b3250[0x16C];
    f32 c[10];
    f32 s[10];
} Scene_c020_01E00E50;

static void func_01E00E50_c020(Scene_c020_01E00E50 *g, Fx_c020_01E00E50 *o, Pkt_c020_01E00E50 *p, s32 mode) {
    extern u8 D_01E01208_c020[4];
    extern void func_00107EC0(void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107710(void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    u8 col[4];
    s32 i;
    Scene_c020_01E00E50 *q;
    s32 a;

    *(f32 *)(u32)&col = *(f32 *)(u32)&D_01E01208_c020;
    if (mode == 0) {
        if (g->h320E == 0) {
            func_00107EC0(g->b3194, 0, 0);
        } else {
            func_00107EC0(g->b3194, 0, 9);
        }
        func_001076F0(col, g->b3194[0], g->b3194[1], g->b3194[2]);
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 1.0f;
        p->v[0].xyz[7] = 0;
        p->v[1].xyz[7] = 0;
        p->v[2].xyz[7] = 0;
        p->v[3].xyz[7] = 0;
        col[3] = o->b28;
        func_00107710(&p->v[0].c, col);
        func_00107710(&p->v[1].c, col);
        col[3] = o->b2A;
        func_00107710(&p->v[2].c, col);
        func_00107710(&p->v[3].c, col);
    } else {
        a = 40;
        for (i = 0, q = g; i < 9; i++) {
            g->q[0].x = q->s[0] * o->h32;
            g->q[0].z = q->c[0] * o->h32;
            g->q[1].x = o->h32 * func_00108030(g->b3250, a, 1);
            g->q[1].z = o->h32 * func_00108030(g->b3250, a, 0);
            g->q[0].y = g->q[1].y = o->h30;
            g->q[2].x = q->s[0] * o->h34;
            g->q[2].z = q->c[0] * o->h34;
            g->q[3].x = o->h34 * func_00108030(g->b3250, a, 1);
            g->q[3].z = o->h34 * func_00108030(g->b3250, a, 0);
            g->q[2].y = 0.0f;
            g->q[3].y = 0.0f;
            g->q[0].x += o->x;
            g->q[1].x += o->x;
            g->q[2].x += o->x;
            g->q[3].x += o->x;
            g->q[0].z += o->z;
            g->q[1].z += o->z;
            g->q[2].z += o->z;
            g->q[3].z += o->z;
            if (func_00205630(g->q, 0x70000000, 0, p, &g->depth) != 0) {
                func_002075F0(p, g->ot, (u32)g->depth);
            }
            q = (Scene_c020_01E00E50 *)((f32 *)q + 1);
            a += 40;
        }
    }
}
