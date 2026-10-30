#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00080_c026);

/* shape c026:01E00B10, 54 insns: fades two alphas by the game timer: up 8 to 0x80 for 13 frames, then down 16 to 0x10
   while the phase is below 6, then up 8 to 0xB0; clears the flag below phase 2 */

typedef struct {
    u8 pad0[0x1A40];
    s32 phase;
    u8 pad1A44[0x80];
    s16 timer;
} Game_c026_01E00B10;

typedef struct {
    u8 pad0[0x64];
    u8 c0[4];
    u8 c1[4];
    s16 flag;
} Obj_c026_01E00B10;

static s32 func_01E00B10_c026(Game_c026_01E00B10 *g, Obj_c026_01E00B10 *o) {
    if (g->timer < 0xD) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 8;
        }
    } else if (g->phase < 6) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0x10;
        }
    } else {
        if (o->c0[3] < 0xB0) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0xB0) {
            o->c1[3] += 8;
        }
    }
    if (g->phase < 2) {
        o->flag = 0;
    }
    return 0;
}

/* OVL_WARM */

/* shape c026:01E00BF0, 202 insns: a falling pair (top 0x14, bottom 0x34) turning 6 a tick: its screen spots
   (0x74/0x76) scale by the scene's slot height ctx+0x1A78[0x7C] over ctx+0x1B4E; the top drops 3 a tick down to
   ctx+0x1B4A, the bottom follows within 18 and then alone until it passes the top (frees its link, stops). Once
   0x78 is set and the bottom is above ctx+0x1B4E it hands itself to the scene (ctx+0x1A50.., state 7) through
   the module's c026:01E01270. Alpha fades in for 14 frames and out while ctx+0x1A40 is under 6 */

typedef struct Link_c026_01E00BF0 {
    u8 pad0[0x50];
    s32 f50;
} Link_c026_01E00BF0;

typedef struct Obj_c026_01E00BF0 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0xC];
    f32 f44;
    u8 pad48[0xC];
    Link_c026_01E00BF0 *link;
    u8 pad58[0xC];
    u8 col0[4];
    u8 col1[4];
    s16 f6C;
    s16 ang;
    u8 pad70[4];
    s16 h74;
    s16 h76;
    s16 h78;
    u8 pad7A[2];
    s16 idx;
} Obj_c026_01E00BF0;

typedef struct Scn_c026_01E00BF0 {
    u8 pad0[0x80];
    s32 f80;
    s32 f84;
    s32 f88;
    f32 f8C;
    u8 pad90[0x1A40 - 0x90];
    s32 f1A40;
    u8 pad1A44[3];
    s8 f1A47;
    u8 pad1A48[8];
    Obj_c026_01E00BF0 *f1A50;
    u8 pad1A54[4];
    f32 f1A58;
    f32 f1A5C;
    f32 f1A60;
    u8 pad1A64[0x14];
    f32 h[14];
    f32 f1AB0;
    u8 pad1AB4[2];
    s16 f1AB6;
    u8 pad1AB8[2];
    s16 f1ABA;
    u8 pad1ABC[2];
    s16 f1ABE;
    u8 pad1AC0[4];
    s16 f1AC4;
    u8 pad1AC6[4];
    s16 f1ACA;
    u8 pad1ACC[0x1B4A - 0x1ACC];
    s16 f1B4A;
    u8 pad1B4C[2];
    s16 f1B4E;
} Scn_c026_01E00BF0;

static s32 func_01E00BF0_c026(Scn_c026_01E00BF0 *g, Obj_c026_01E00BF0 *o) {
    extern void c026_01E01270(Scn_c026_01E00BF0 *g, void *fn, s32 arg);
    f32 d;
    f32 lim;
    f32 r;

    d = g->f1B4E;
    o->ang -= 6;
    if (o->ang <= 360) {
        o->ang = o->ang % 360;
    }
    lim = g->f1B4A;
    r = g->h[o->idx] / d;
    o->h74 = r * o->f14;
    if (g->h[o->idx] < 1.0f) {
        o->f6C = 0;
    }
    o->h76 = r * o->f34;
    if (o->f14 >= lim) {
        o->f24 = o->f14 -= 3.0f;
        if (o->f34 - o->f14 >= 18.0f) {
            o->f44 = o->f34 -= 3.0f;
        }
    } else {
        o->f44 = o->f34 -= 3.0f;
        if (o->f34 < o->f14) {
            if (o->link != NULL) {
                o->link->f50 = 0;
            }
            o->f6C = 0;
        }
    }
    if (o->h78 > 0 && o->f34 < g->f1B4E) {
        g->f1A50 = o;
        g->f1A58 = o->h74;
        g->f1A5C = o->h76;
        g->f1A47 = 0;
        g->f1ABA = 1;
        g->f1A60 = o->f34;
        g->f1AB0 = o->idx;
        g->f1ABE = 1;
        g->f84 = 0;
        g->f80 = 0;
        g->f88 = 0;
        g->f8C = o->fC;
        g->f1AB6 = o->ang + 15;
        g->f1ACA = 7;
        c026_01E01270(g, func_01E00BF0_c026, 1);
        o->h78 = 0;
    }
    if (g->f1AC4 < 14) {
        if (o->col0[3] < 0x80) {
            o->col0[3] += 4;
        }
        if (o->col1[3] < 0x80) {
            o->col1[3] += 4;
        }
    }
    if (g->f1A40 < 6) {
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 16;
        }
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 16;
        }
    } else {
        if (o->col0[3] < 0x80) {
            o->col0[3] += 4;
        }
        if (o->col1[3] < 0x80) {
            o->col1[3] += 4;
        }
    }
    if (g->f1A40 < 2) {
        o->f6C = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00F20_c026);

/* shape c026:01E01170, 64 insns: takes the first free of 50 effect slots (0x80 bytes, b108:01E02FF0 family), marks it with
   its index + 1, colours both from the context, hooks c026:01E014F0 with the given argument and remembers it */

typedef struct {
    u8 pad0[0x58];
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    u8 c64[4];
    u8 c68[4];
    s16 used;
    u8 pad6E[0x12];
} Slot_c026_01E01170;

typedef struct {
    u8 pad0[0x140];
    Slot_c026_01E01170 slots[0x32];
    u8 pad[0x1A44 - 0x140 - 0x32 * 0x80];
    u8 rgba[4];
    u8 pad1A48[8];
    Slot_c026_01E01170 *last;
} Ctx_c026_01E01170;

static void func_01E01170_c026(Ctx_c026_01E01170 *ctx, s32 arg) {
    extern void c026_01E014F0(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c026_01E01170 *s = NULL;
    s16 i;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x80);
            ctx->slots[i].used = i + 1;
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_001076F0(s->c68, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c68[3] = ctx->rgba[3];
        s->cb = c026_01E014F0;
        s->arg = arg;
        ctx->last = s;
    }
}

/* shape c026:01E01270, 158 insns: c026 trail link spawner (c017:01E01400 family, 50 slots of 0x80 at ctx+0x140): both colours from the context with alpha 0, its vector, sizes as shorts, four heights (two at the context's height, two 18 above) capped by the context's ceiling, chained after the context's last piece and becomes it; draws with c026:01E01860 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c026_01E01270;

typedef struct Ent_c026_01E01270 {
    Vec4f v;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0xC];
    f32 f44;
    u8 pad48[8];
    struct Ent_c026_01E01270 *prev;
    struct Ent_c026_01E01270 *next;
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    Col_c026_01E01270 col0;
    Col_c026_01E01270 col1;
    s16 used;
    s16 h6E;
    u8 pad70[2];
    s16 h72;
    s16 h74;
    s16 h76;
    s16 h78;
    s16 h7A;
    s16 h7C;
    u8 pad7E[2];
} Ent_c026_01E01270;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0x140 - 0x90];
    Ent_c026_01E01270 ent[50];
    u8 padEnd[0x1A44 - 0x140 - 50 * 0x80];
    u8 rgb[4];
    u8 pad1A48[8];
    Ent_c026_01E01270 *last;
    u8 pad1A54[4];
    f32 f1A58;
    f32 f1A5C;
    f32 f1A60;
    u8 pad1A64[0x1AB0 - 0x1A64];
    f32 f1AB0;
    u8 pad1AB4[2];
    s16 h1AB6;
    u8 pad1AB8[2];
    s16 h1ABA;
    u8 pad1ABC[2];
    s16 h1ABE;
    u8 pad1AC0[0x1B4E - 0x1AC0];
    s16 top;
} Ctx_c026_01E01270;

static void func_01E01270_c026(Ctx_c026_01E01270 *g, s32 arg) {
    extern void c026_01E01860(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c026_01E01270 *e = NULL;
    Ent_c026_01E01270 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 50; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x80);
            g->ent[i].used = i + 1;
            i = 50;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col1.a = 0;
        e->v = g->v;
        e->h74 = (s16)g->f1A58;
        e->h76 = (s16)g->f1A5C;
        e->h72 = (s16)g->f1A60;
        e->h6E = g->h1AB6;
        e->prev = g->last;
        e->h7A = g->h1ABE;
        if (e->prev == NULL) {
            h = g->f1A60;
            e->f14 = e->f24 = h;
            e->f44 = e->f34 = h + d;
        } else {
            h = g->f1A60;
            e->f14 = e->f24 = h;
            e->f44 = e->f34 = h + d;
        }
        if ((f32)g->top < e->f14) {
            e->f14 = g->top;
        }
        if ((f32)g->top < e->f24) {
            e->f24 = g->top;
        }
        if ((f32)g->top < e->f34) {
            e->f34 = g->top;
        }
        if ((f32)g->top < e->f44) {
            e->f44 = g->top;
        }
        e->h7C = (s16)g->f1AB0;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->h78 = g->h1ABA;
        e->cb = c026_01E01860;
        e->arg = arg;
        g->last = e;
    }
}

/* OVL_WARM */

/* shape c026:01E014F0, 220 insns: c015:01E00620 family two-pass sprite: mode 0 sets the material (frame 0x98, the
   scene colour copied into both object colours, two corners each, scene texture 0xDC); other modes place four 40x20
   quads (func_00108D60 corner i) at the camera point with a spin, each pushed to the far plane and drawn once (depth
   0x1A98, packet list 0x1A4C) */

typedef struct {
    f32 x, y, z, w;
} Vec_c026_01E014F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c026_01E014F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c026_01E014F0;

typedef struct {
    Rgbaq_c026_01E014F0 c;
    u64 st;
    Xyz_c026_01E014F0 p;
} Vtx_c026_01E014F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c026_01E014F0 v[4];
} Pkt_c026_01E014F0;

typedef struct {
    u8 pad0[0x64];
    u8 col[4];
    u8 col2[4];
} Obj_c026_01E014F0;

typedef struct {
    u8 pad0[0xDC];
    s32 texture;
    u8 padE0[0x1A4C - 0xE0];
    s32 target;
    u8 pad1A50[0x1A98 - 0x1A50];
    f32 depth;
    u8 pad1A9C[0x1BE8 - 0x1A9C];
    u8 rgb[4];
} Game_c026_01E014F0;

static void func_01E014F0_c026(Game_c026_01E014F0 *g, Obj_c026_01E014F0 *o, Pkt_c026_01E014F0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c026_01E014F0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern Vec_c026_01E014F0 *func_001F9D30(s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00108D60(void *, s32, s32, s16);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 q[16];
    f32 rm[4];
    f32 m[16];
    f32 m2[16];
    s32 rot[4];
    Vec_c026_01E014F0 pos;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x98, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        o->col[0] = g->rgb[0];
        o->col[1] = g->rgb[1];
        o->col[2] = g->rgb[2];
        o->col2[0] = g->rgb[0];
        o->col2[1] = g->rgb[1];
        o->col2[2] = g->rgb[2];
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
        return;
    }
    pos = *func_001F9D30(0);
    func_0020EB40(m);
    func_00205C40((s32)rot);
    func_0020C940(m2, 0, rot, &pos);
    func_0020BC00(m, m2);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            func_00108D60(q, 40, 20, i);
        } else if (i == 1) {
            func_00108D60(q, 40, 20, i);
        } else if (i == 2) {
            func_00108D60(q, 40, 20, i);
        } else if (i == 3) {
            func_00108D60(q, 40, 20, i);
        }
        if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
            p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
            func_002075F0(p, g->target, (u32)g->depth);
        }
    }
}

/* shape c026:01E01860 (C026PAINT_RAIN2), 357 insns, 1 copy: mode 0 sets the drawing state (a 0x9C matrix, packet
   header, the scene colour 0x1BEC copied into both object colours, top colours from the previous segment 0x68 or own
   0x64, bottom from own 0x68, scene texture 0xDC); otherwise a 12-step band 20 degrees apart in the object quad:
   inner edge from the previous segment (radius 0x76, height 0x34) or its own radius 0x74, outer edge at radius 0x76,
   drawn at the far plane when on screen, the next angle from the scene table 0x1AD2 row (s16)0x0C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c026_01E01860;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c026_01E01860;

typedef struct {
    Rgbaq_c026_01E01860 c;
    u64 st;
    Xyz_c026_01E01860 p;
} Vtx_c026_01E01860;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c026_01E01860 v[4];
} Pkt_c026_01E01860;

typedef struct {
    u8 r, g, b, a;
} Col_c026_01E01860;

typedef struct Ent_c026_01E01860 {
    Vec4f v;
    Vec4f q[4];
    struct Ent_c026_01E01860 *prev;
    struct Ent_c026_01E01860 *next;
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    Col_c026_01E01860 col0;
    Col_c026_01E01860 col1;
    s16 used;
    s16 h6E;
    u8 pad70[2];
    s16 h72;
    s16 h74;
    s16 h76;
    s16 h78;
    s16 h7A;
    s16 h7C;
    u8 pad7E[2];
} Ent_c026_01E01860;

typedef struct {
    u8 pad0[0x40];
    f32 m[16];
    u8 pad80[0x10];
    s32 f90;
    u8 pad94[0xDC - 0x94];
    s32 texture;
    u8 padE0[0x1A4C - 0xE0];
    s32 target;
    u8 pad1A50[0x1A98 - 0x1A50];
    f32 depth;
    u8 pad1A9C[0x1AD2 - 0x1A9C];
    s16 tab[1][12];
    u8 pad1AEA[0x1BEC - 0x1AEA];
    u8 rgb[4];
    u8 pad1BF0[0x1C18 - 0x1BF0];
    u8 trig[1];
} Scene_c026_01E01860;

static void func_01E01860_c026(Scene_c026_01E01860 *g, Ent_c026_01E01860 *o, Pkt_c026_01E01860 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c026_01E01860 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    Ent_c026_01E01860 *prev = o->prev;
    f32 rm[4];
    s16 a = 0;
    s16 ang;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        o->col0.r = g->rgb[0];
        o->col0.g = g->rgb[1];
        o->col0.b = g->rgb[2];
        o->col1.r = g->rgb[0];
        o->col1.g = g->rgb[1];
        o->col1.b = g->rgb[2];
        if (prev != NULL) {
            p->v[0].c = func_00107740(&prev->col1);
            p->v[1].c = func_00107740(&prev->col1);
        } else {
            p->v[0].c = func_00107740(&o->col0);
            p->v[1].c = func_00107740(&o->col0);
        }
        p->v[2].c = func_00107740(&o->col1);
        p->v[3].c = func_00107740(&o->col1);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        for (i = 0; i < 12; i++) {
            if (prev != NULL) {
                ang = a + prev->h6E;
                o->q[0].x = prev->h76 * func_00108030(g->trig, ang, 1);
                o->q[0].z = prev->h76 * func_00108030(g->trig, ang, 0);
                ang = a + prev->h6E + 20;
                o->q[1].x = prev->h76 * func_00108030(g->trig, ang, 1);
                o->q[1].z = prev->h76 * func_00108030(g->trig, ang, 0);
                o->q[1].y = o->q[0].y = prev->q[2].y;
            } else {
                o->q[0].x = o->h74 * func_00108030(g->trig, a + o->h6E, 1);
                o->q[0].z = o->h74 * func_00108030(g->trig, a + o->h6E, 0);
                o->q[1].x = o->h74 * func_00108030(g->trig, a + o->h6E + 20, 1);
                o->q[1].z = o->h74 * func_00108030(g->trig, a + o->h6E + 20, 0);
            }
            ang = a + o->h6E;
            o->q[2].x = o->h76 * func_00108030(g->trig, ang, 1);
            o->q[2].z = o->h76 * func_00108030(g->trig, ang, 0);
            ang = a + o->h6E + 20;
            o->q[3].x = o->h76 * func_00108030(g->trig, ang, 1);
            o->q[3].z = o->h76 * func_00108030(g->trig, ang, 0);
            g->f90 = 0x5A;
            if (func_00205630(o->q, 0x70000000, g->m, p, &g->depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, g->target, (u32)g->depth);
            }
            a = g->tab[(s16)(s32)o->v.w][i];
        }
    }
}
