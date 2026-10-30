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

static void func_01E00080_b548(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b038_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b038_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b038_01E00920;

typedef struct {
    u64 st;
    Xyz_b038_01E00920 p;
} Vtx_b038_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b038_01E00920 c;
    Vtx_b038_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b038_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b038_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b038_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    s16 tilt;
    u8 pad5E[2];
    u8 col[1];
} Anim_b038_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b038_01E00920;

extern void b548_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b548(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b038_01E00920 quad[4];
    Vec_b038_01E00920 d;
    Vec_b038_01E00920 pos;
    Vec_b038_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b038_01E00920 r;
    struct {
        u64 pre;
        Pkt_b038_01E00920 pk;
    } buf;
    Col_b038_01E00920 col;
    s16 i;
    Pkt_b038_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.rot[2] = an->tilt;
    r.v[1] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b548_01E00080(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 2, o->bD8);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 0, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b548:01E00E90, 118 insns: scene timer step: from tick 62 to 250 spawns two drifting puffs (module 01E01070)
   per tick at the tracked object, nudged sideways by the scene's side flag; at ticks 23 and 43 two bursts
   (01E014C0) a little higher. */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xAFC8];
    s16 obj;
    u8 padB22A[0x2C];
    s16 b256;
    u8 padB258[2];
    s16 side;
    u8 padB25C[2];
    s16 t;
} Scene_b548_01E00E90;

static void func_01E00E90_b548(Scene_b548_01E00E90 *g) {
    extern void b548_01E01070(void);
    extern void b548_01E014C0(void);
    extern void b548_01E01E50(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    g->t++;
    g->b256 = 0;
    if (g->t >= 62 && g->t < 251) {
        if (g->t < 100) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->obj, &g->pos);
            g->pos.y -= 1.0f;
            if (g->side != 0) {
                g->pos.z += 2.0f;
            } else {
                g->pos.z -= 2.0f;
            }
            b548_01E01E50(g, b548_01E01070, 0);
        }
    }
    if (g->t == 23 || g->t == 43) {
        func_001F5620(func_001F53A0(), g->obj, &g->pos);
        g->pos.y -= 4.0f;
        b548_01E01E50(g, b548_01E014C0, 0);
        b548_01E01E50(g, b548_01E014C0, 0);
    }
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b548:01E01070, 275 insns: a violet (0x80, 0x20, 0xFF) puff of size 70 growing 0.5 a tick: drift (-20..19) /
   60 and / 70 between ticks 6 and 39 and after 85, a fall toward point ctx->v over 80 ticks until tick 84; fades in
   for 95 ticks while the scene counter is below 290 and out by 11 after it; its swing angle 0x5C counts 45..140, and
   at 140 it moves the scene point to its own (height 42) and spawns 0x1E01670 (always before scene time 170, one in
   four times before 290); either way it ends */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB228 - 0x260];
    s16 v;
    u8 padB22A[0x34];
    s16 count;
    u8 padB260[0xB460 - 0xB260];
    u8 trig[1];
} Ctx_b548_01E01070;

typedef struct {
    u8 pad00[8];
    s16 h8;
    u8 padA[6];
    Vec4f pos;
    u8 pad20[0x10];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b548_01E01070;

static s32 func_01E01070_b548(Ctx_b548_01E01070 *ctx, Obj_b548_01E01070 *o) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern s32 b548_01E01670(void);
    extern s32 b548_01E01E50(Ctx_b548_01E01070 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];

    if (o->state == 1) {
        o->f48 = 70.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x20, 0xFF);
        o->h5C = 45;
        o->h50 = 0;
        o->h52 = 0;
        o->h8 = func_0019A5C8() % 35;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->f30 /= 60.0f;
        o->f34 /= 70.0f;
        o->f38 /= 70.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->f4C = (a[2] - b[2]) / 80.0f;
        o->state = 2;
    }
    if (o->t < 95) {
        if (ctx->count < 290) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0xC0;
            }
        }
    } else if (ctx->count < 290) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->state = 0;
        }
    }
    if (o->t > 5 && o->t < 40) {
        o->pos.x += o->f30;
        o->pos.z += o->f38;
    }
    if (o->t != 0) {
        if ((s16)o->t < 85) {
            o->pos.z += o->f4C;
        }
        o->f48 += 0.5f;
    }
    if (ctx->count > 290) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->state = 0;
        }
    }
    if (o->h5C < 140) {
        o->h5C++;
    }
    if (o->h5C == 140) {
        ctx->pos = o->pos;
        ctx->pos.y -= 120.0f * func_00108030(ctx->trig, 45, 0);
        ctx->pos.y += 120.0f * func_00108030(ctx->trig, o->h5C, 0);
        ctx->pos.y = 42.0f;
        if (ctx->count < 170) {
            b548_01E01E50(ctx, b548_01E01670, 0);
        } else if (ctx->count < 290) {
            if ((func_0019A5C8() >> 4) % 4 == 0) {
                b548_01E01E50(ctx, b548_01E01670, 0);
            }
        }
        o->state = 0;
    }
    if (o->t > 85) {
        o->pos.x += o->f30;
        o->pos.z += o->f38;
    }
    o->t++;
    return 0;
}

/* shape b548:01E014C0, 107 insns: b593:01E020C0 family: a white spark (size 100 growing 1, random frame 0..3) spinning a random 8..20 a tick from 50..99 (old angle moved to +0xC), random 0..7 at +0xA, size 0..34, held 3..7 ticks at 0xC0, then out by 11 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b548_01E014C0;

static s32 func_01E014C0_b548(s32 arg0, Obj_b548_01E014C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 50;
        o->hE = func_0019A5C8() % 13 + 8;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->f48 += 1.0f;
    o->t++;
    return 0;
}

/* shape b548:01E01670, 111 insns: b593:01E020C0 family: a purple spark (size 140 growing 2, random frame 0..3) spinning a random 15..32 a tick from 30..59, size 0..34, held 8..17 ticks: in by 96 up to 0xC0, then out by 11 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b548_01E01670;

static s32 func_01E01670_b548(s32 arg0, Obj_b548_01E01670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 140.0f;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x10, 0xFF);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 30 + 30;
        o->hE = func_0019A5C8() % 18 + 15;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 10 + 8;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->f48 += 2.0f;
    o->t++;
    return 0;
}

/* shape b548:01E01830 (b548), 392 insns, 1 copy: the module scene manager (b276:01E01760 form): with a scene id it
   clears the scene, sets the 325-frame countdown, reads three joints, textures 4:14..15 and 5:0..1, the camera turn,
   scale 0.1 and the jitter table; otherwise it runs the scene script b548:01E00E90, every effect handler, draws the
   three effect kinds (the first bobbing on the sine table), counts down and returns the next step by frame (130, 310,
   141..304) or 8 when the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b548_01E01830;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b548_01E01830 fx[400];
    u8 padB1A0[0x30];
    s32 tex[2];
    u8 padB1D8[0x18];
    s32 count;
    u8 padB1F4[8];
    s32 ot;
    u8 padB200[4];
    s32 cam1;
    s32 cam2;
    u8 padB20C[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padB22E[0xA];
    s16 cam;
    u8 padB23A[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b548_01E01830;

static s32 func_01E01830_b548(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F9AD0(s32);
    extern s32 func_001F9D30(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_01E00E90_b548();
    extern void func_01E00920_b548();
    Scene_b548_01E01830 *g = (Scene_b548_01E01830 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    g->cam1 = func_001F9AD0(0);
    g->cam2 = func_001F9D30(0);
    if (id >= 0) {
        func_00195108(g, 0xB5D0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 325;
        g->jA = func_001F5560(func_001F53A0(), 0x14, 1);
        g->jB = func_001F5560(func_001F53A0(), 4, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
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
            g->jit[k] = 0;
        }
        return 0;
    }
    func_01E00E90_b548(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01070_b548) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 1;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->py -= 120.0f * func_00108030(g->crd, 0x2D, 0);
                g->py += 120.0f * func_00108030(g->crd, g->fx[k].h5C, 0);
                g->fx[k].h50 = 0;
                g->hBE = 0;
                func_01E00920_b548(g, &g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E014C0_b548) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 10;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hBE = 0;
                func_01E00920_b548(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01670_b548) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 3;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hBE = 0;
                func_01E00920_b548(g, &g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 130) {
        return 1;
    }
    if (g->frame == 310) {
        return 3;
    }
    if (g->frame > 140 && g->frame < 305) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b038:01E01E10, 98 insns, 8 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b038_01E01E10 {
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
} Slot_b038_01E01E10;

typedef struct Obj_b038_01E01E10 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b038_01E01E10 slots[0x190];
    u8 padB[0xb1f4 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb256 - 0xb1f4 - 4];
    s16 fB2B0;
} Obj_b038_01E01E10;

static s32 func_01E01E50_b548(Obj_b038_01E01E10 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b038_01E01E10 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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
