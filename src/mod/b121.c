#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b121(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

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

static void func_01E00100_b121(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E009A0_b121(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b081:01E00DE0, 282 insns: half ring of 18 segments (20 table steps each) between an s16 inner and outer
   radius, variant of b082:01E00920 with a smaller data layout; blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b081_01E00DE0;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 inner;
    s16 step;
} Data_b081_01E00DE0;

static void func_01E00DE0_b121(Obj_b081_01E00DE0 *o, Data_b081_01E00DE0 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    outer = data->outer;
    i = 0;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 20);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 20);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 20;
        i++;
    } while (i < 18);
}

/* shape b081:01E016D0, 342 insns, 3 copies: draws a row of small camera-facing sprites at the object position (b008
   family): each shaken by a per-entry table offset turned by an extra axis and added to all four corners;
   blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module helper
   (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b081_01E016D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b081_01E016D0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b081_01E016D0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 mode;
    u8 padC2[0x16];
    u8 xD8[1];
} Obj_b081_01E016D0;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b081_01E016D0;

static void func_01E01250_b121(Obj_b081_01E016D0 *o, Spr_b081_01E016D0 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b081_01E016D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
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
    Pkt_b081_01E016D0 pkt __attribute__((aligned(8)));
    f32 f;
    s16 i;
    s16 b;
    Pkt_b081_01E016D0 *p;
    s32 mode;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b081_01E016D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    p2.x = o->pos.x;
    p2.y = o->pos.y;
    p2.z = o->pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    func_01E00100_b121((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        e.x = f * (s->w30 + h);
        f = j[s->off + 100];
        f /= 20.0f;
        e.y = f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        quad[0].x += e.x;
        quad[1].x += e.x;
        quad[2].x += e.x;
        quad[3].x += e.x;
        quad[0].y += e.y;
        quad[1].y += e.y;
        quad[2].y += e.y;
        quad[3].y += e.y;
        f = j[s->off + 180];
        f /= 20.0f;
        e.z = f * (s->w30 + h);
        quad[0].z += e.z;
        quad[1].z += e.z;
        quad[2].z += e.z;
        quad[3].z += e.z;
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b121:01E017B0, 135 insns: the b121 module's event step: red scene colour, counts ticks; at 61 spawns b121:01E02560; every fifth tick from 137 places up to 8 points at the camera (50 up or down by the scene flag, jittered -3..2.9 on x/y) and spawns b121:01E019D0 and b121:01E021E0 there; every other tick from 61 to 180 spawns b121:01E01DF0 */

typedef struct {
    u8 pad0[0x28D0];
    Vec4f pts[8];
    u8 pad2950[0x3FF4 - 0x2950];
    u8 col[4];
    u8 pad3FF8[0x4028 - 0x3FF8];
    s16 flag;
    u8 pad402A[6];
    s16 n;
    u8 pad4032[4];
    s16 cur;
    u8 pad4038[2];
    s16 timer;
} Ctx_b121_01E017B0;

static void func_01E017B0_b121(Ctx_b121_01E017B0 *g) {
    extern s32 b121_01E019D0(void);
    extern s32 b121_01E01DF0(void);
    extern s32 b121_01E021E0(void);
    extern s32 b121_01E02560(void);
    extern void b121_01E02F60(Ctx_b121_01E017B0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, Vec4f *);
    f32 a;
    s32 b;
    f32 c;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 61) {
        b121_01E02F60(g, b121_01E02560, 0);
    }
    if (g->timer % 5 == 1) {
        if (g->n < 8 && g->timer >= 137) {
            g->cur = g->n;
            func_001F5F90(func_001F53A0(), &g->pts[g->cur]);
            if (g->flag != 0) {
                g->pts[g->cur].z += 50.0f;
            } else {
                g->pts[g->cur].z -= 50.0f;
            }
            a = func_0019A5C8() % 60 - 30;
            b = func_0019A5C8() % 60 - 30;
            a /= 10.0f;
            g->pts[g->cur].x += a;
            c = b;
            c /= 10.0f;
            g->pts[g->cur].y += c;
            b121_01E02F60(g, b121_01E019D0, 0);
            b121_01E02F60(g, b121_01E021E0, 0);
            g->n++;
        }
    }
    if (g->timer >= 61) {
        if (g->timer % 2 == 1 && g->timer < 181) {
            b121_01E02F60(g, b121_01E01DF0, 0);
        }
    }
}

/* shape b121:01E019D0, 264 insns: the point object b121:01E017B0 spawns: grey, fades in from tick 4 and out by 34
   after 32; blinks by tick parity; its point (pts[o->h30]) closes a 33rd of the camera's depth gap until tick 32 while
   it spins 0x4000 against the scene flag; until tick 30 it drops two trail points (the first 3 lower) into the
   scene's ring at 0x3350 and spawns b121:01E02030 for each; at tick 30 it drops eight camera points into the ring at
   0x3990 and spawns b121:01E023B0 for each */

typedef struct {
    u8 pad0[0x28D0];
    Vec4f pts[8];
    u8 pad2950[0x3350 - 0x2950];
    Vec4f ring[100];
    Vec4f ring2[100];
    u8 pad3FD0[0x4028 - 0x3FD0];
    s16 flag;
    u8 pad402A[2];
    s16 n;
    s16 n2;
    u8 pad4030[6];
    s16 cur;
} Ctx_b121_01E019D0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[8];
    s32 w14;
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 idx;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b121_01E019D0;

static s32 func_01E019D0_b121(Ctx_b121_01E019D0 *g, Obj_b121_01E019D0 *o) {
    extern s32 b121_01E02030(void);
    extern s32 b121_01E023B0(void);
    extern void b121_01E02F60(Ctx_b121_01E019D0 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, Vec4f *);
    Vec4f v[2];
    s16 i;

    func_001F5F90(func_001F53A0(), &v[0]);
    func_001F5F90(func_001F5380(), &v[1]);
    if (o->mode == 1) {
        o->h8 = 127;
        o->hA = 31;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 32) {
        if (o->tick > 3) {
            if (o->col[3] < 0x80) {
                o->col[3] += 10;
            }
        }
        if (o->tick > 3) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 10;
            }
        }
    } else {
        if (o->col[3] > 35) {
            o->col[3] -= 34;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 35) {
            o->col[3] -= 34;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    o->tick++;
    *(f32 *)(u32)&v[0].z = (v[1].z - v[0].z) / 33.0f;
    if (g->flag != 0) {
        o->w14 = -0x4000;
        if (o->tick < 32) {
            g->pts[o->idx].z += v[0].z;
        }
    } else {
        o->w14 = 0x4000;
        if (o->tick < 32) {
            g->pts[o->idx].z += v[0].z;
        }
    }
    if (o->tick < 30) {
        for (i = 0; i < 2; i++) {
            g->ring[g->n].x = g->pts[o->idx].x;
            g->ring[g->n].y = g->pts[o->idx].y;
            g->ring[g->n].z = g->pts[o->idx].z;
            if (!i) {
                g->ring[g->n].z -= 3.0f;
            }
            g->cur = g->n;
            b121_01E02F60(g, b121_01E02030, 0);
            g->n++;
            if (g->n >= 100) {
                g->n = 0;
            }
        }
    }
    if (o->tick == 30) {
        func_001F5F90(func_001F5380(), &v[0]);
        for (i = 0; i < 8; i++) {
            g->ring2[g->n2].x = v[0].x;
            g->ring2[g->n2].y = v[0].y;
            g->ring2[g->n2].z = *(f32 *)(u32)&v[0].z;
            g->cur = g->n2;
            b121_01E02F60(g, b121_01E023B0, 0);
            g->n2++;
            if (g->n2 >= 100) {
                g->n2 = 0;
            }
        }
    }
    return 0;
}

/* shape b121:01E01DF0, 143 insns: a dark falling flake: size 8 growing by 0..2 to 16, frame 0..6 (stepped every third
   tick for kind 0), 0xA 0..7, kind from the old height, height 20..119 falling 1..3 a tick (ends at 0), f8 0..34, held
   2..4 at alpha 0x80, turning -1 a tick; ends at scene frame 211 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 kind;
    s16 fall;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b121_01E01DF0;

typedef struct {
    u8 pad0[0x403A];
    s16 frame;
} Scene_b121_01E01DF0;

static s32 func_01E01DF0_b121(Scene_b121_01E01DF0 *g, Fx_b121_01E01DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 8;
        o->frame = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->fA = func_0019A5C8() % 8;
        o->kind = o->h;
        o->h = func_0019A5C8() % 100 + 20;
        o->fall = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 2;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        o->col[3] = 0x80;
    }
    if (o->kind == 0 && o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    if (o->t != 0) {
        if (o->h > 0) {
            o->h -= o->fall;
        } else {
            o->mode = 0;
        }
    }
    if (o->t != 0) {
        o->ang--;
    }
    if (o->size < 0x11) {
        o->size += (s16)(func_0019A5C8() % 3);
    }
    o->t++;
    if (g->frame > 0xD2) {
        o->mode = 0;
    }
    return 0;
}

/* shape b121:01E02030, 108 insns: on start 0x38 = 38, variant 0..6, colour 0x20 grey, 0xA 0..7, 0xC keeps the old 0x30,
   0x30 0..19, speed 2..11 (0xE), 0x8 0..34, hold 0..2 (0x6), random 0x3A; alpha 0x80 during the hold, then fades by 29
   and stops; after the first tick 0x38 shrinks by 4 down to 0 and 0x3A turns by -7 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b121_01E02030;

static s32 func_01E02030_b121(s32 arg0, Fx_b121_01E02030 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 38;
        o->f34 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 1;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f38 != 0) {
            o->f38 -= 4;
        }
    }
    if (o->tick != 0) {
        if (o->tick != 0) {
            o->f3A -= 7;
        }
    }
    o->tick++;
    return 0;
}

/* shape b121:01E021E0 (B121_OBJ_MOVE_5_), 116 insns, 1 copy: a red/yellow trail (b108:01E02010's form, 20-point rows):
   width 5; fills its trail row with its point, holds alpha 0x80 for 30 frames, then fades by 49 until it ends;
   rebuilds the trail tail from its point each frame; flickers; its point drifts 4 a frame in z, the way the scene
   flag (0x4028) says, and its angle turns to match */

typedef struct {
    f32 x, y, z, w;
} V4_b121_01E021E0;

typedef struct {
    u8 pad0[0x28D0];
    V4_b121_01E021E0 pts[8];
    V4_b121_01E021E0 trail[10][20];
    u8 pad35D0[0x4028 - 0x35D0];
    s16 flag;
} Game_b121_01E021E0;

typedef struct {
    u8 pad0[6];
    s16 w;
    u8 pad8[0xC];
    s32 ang;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[4];
    s16 row;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b121_01E021E0;

static s32 func_01E021E0_b121(Game_b121_01E021E0 *g, Obj_b121_01E021E0 *o) {
    extern void b121_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    V4_b121_01E021E0 *p;
    V4_b121_01E021E0 *q;

    if (o->state == 1) {
        o->w = 5;
        o->c0[3] = 0;
        p = &g->pts[o->row];
        q = g->trail[o->row];
        for (i = 0; i < 0x13; i++) {
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
            q++;
        }
        o->h38 = 0x23;
        o->state = 2;
    }
    if (o->t < 0x1E) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x28) {
        o->c0[3] -= 0x31;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0x60, 0x10, 0x10);
    } else {
        func_001076F0(o->c0, 0x60, 0x60, 0x10);
    }
    b121_01E00080(&g->trail[o->row][0x13], 0x14, 0, &g->pts[o->row]);
    if (g->flag != 0) {
        o->ang = -0x4000;
        g->pts[o->row].z -= 4.0f;
    } else {
        o->ang = 0x4000;
        g->pts[o->row].z += 4.0f;
    }
    o->t++;
    return 0;
}

/* shape b121:01E023B0, 105 insns: on start 0x38 = 60, variant 0..6, colour (0x20, 0x20, 0x20), 0xA 0..7, 0xC keeps the old 0x30, 0x30
   0..19, speed 16..45 (0xE), 0x8 0..34, hold 3..7 (0x6), 0x3A 0..2; alpha 0x80 during the hold, then fades by 8 and
   stops; after the first tick 0x38 grows by 8 and 0x30 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b121_01E023B0;

static s32 func_01E023B0_b121(s32 arg0, Fx_b121_01E023B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->f34 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->f3A = func_0019A5C8() % 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += 8;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b121:01E02560, 90 insns: on start 0x38 = 50, colour 0x60 grey, second colour (0x80, 0x10, 0x10) with alpha
   8, random 0x3A; for 18 ticks the alphas grow by 3 (below 0x20) and 12 (below 0x80); the colour flickers grey; below
   game step 0x403A = 100 the rotation is 0x4000; past step 0xD2 it ends */

typedef struct {
    u8 pad0[0x403A];
    s16 step;
} Game_b121_01E02560;

typedef struct {
    u8 pad0[0x10];
    s32 rot;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b121_01E02560;

static s32 func_01E02560_b121(Game_b121_01E02560 *g, Fx_b121_01E02560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 8;
    }
    if (o->tick < 18) {
        if (o->col[3] < 0x20) {
            o->col[3] += 3;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (g->step < 100) {
        o->rot = 0x4000;
    }
    o->tick++;
    if (g->step > 0xD2) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b121", func_01E026D0_b121);

/* shape b121:01E02F60, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x4036 and 0x4032 and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b121_01E02F60;

typedef struct {
    u8 pad[0x250];
    u8 m[0xCC];
    Slot_b121_01E02F60 s[150];
    u8 pad289C[0x1758];
    u8 r, g, b, a;
    u8 pad3FF8[0x3A];
    s16 w;
    u8 pad4034[0x2];
    s16 v;
} Pool_b121_01E02F60;

static s32 func_01E02F60_b121(Pool_b121_01E02F60 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b121_01E02F60 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b139:01E03820: sibling of b016:01E00ED0 (one sprite quad, drawn twice). Needs func_01E00100_b121 in the
   same file and static (the original reuses $a0 across the call). */

typedef struct Cam_b121_01E03090 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[8];
    u8 col[4];
} Cam_b121_01E03090;

typedef struct Obj_b121_01E03090 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b121_01E03090;

typedef struct Xyz_b121_01E03090 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b121_01E03090;

typedef struct Uv_b121_01E03090 {
    f32 u, v;
} Uv_b121_01E03090;

typedef struct Pk_b121_01E03090 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b121_01E03090 uv;
    u64 pad18;
    Xyz_b121_01E03090 v[4];
    u64 pad60[6];
} Pk_b121_01E03090;

typedef struct Buf_b121_01E03090 {
    u64 tag;
    Pk_b121_01E03090 pk;
} Buf_b121_01E03090;

static void func_01E03090_b121(Obj_b121_01E03090 *obj, Cam_b121_01E03090 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b121_01E03090 buf;
    Uv_b121_01E03090 uv;
    s32 sel;
    s32 mode;
    Pk_b121_01E03090 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, cam->col);
    p->uv = uv;
    func_01E00100_b121((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b121", func_01E033A0_b121);
