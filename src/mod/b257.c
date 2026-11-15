#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b257(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b257(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

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
} Spr_b008_01E004D0;

static void func_01E005A0_b257(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00150_b257((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
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

/* OVL_WARM: compile warm */

/* shape b112:01E00850, 195 insns: b020:01E00E70 family: 4 rotated quads (func_00108D60 from fx->u/v, z rotation fx->rz) at pos, drawn by depth or at far z */

typedef struct {
    f32 u, v;
} Uv_b112_01E00850;

typedef struct {
    Uv_b112_01E00850 st;
    u64 rgba;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b112_01E00850;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b112_01E00850 v[4];
    u8 tail[0x20];
} Pkt_b112_01E00850;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padcol2[0x18];
    u8 xD8[1];
} Obj_b112_01E00850;

typedef struct {
    u8 pad00[8];
    s16 u;
    s16 v;
    u8 pad0C[0x1C];
    u8 col[4];
    u8 col2[4];
    u8 pad30[8];
    s16 size;
    s16 rz;
} Fx_b112_01E00850;

static void func_01E00B20_b257(Obj_b112_01E00850 *o, Fx_b112_01E00850 *fx, s32 mode, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b112_01E00850 pkt;
    Uv_b112_01E00850 uv0;
    Uv_b112_01E00850 uv1;
    Uv_b112_01E00850 uv2;
    Uv_b112_01E00850 uv3;
    s16 i;
    Pkt_b112_01E00850 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, fx->col2);
    p->v[0].st = uv0;
    func_00107740(&uv1, fx->col2);
    p->v[1].st = uv1;
    func_00107740(&uv2, fx->col2);
    p->v[2].st = uv2;
    func_00107740(&uv3, fx->col);
    p->v[3].st = uv3;
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        }
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00E30_b257(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* OVL_WARM */

/* shape b257:01E01270, 386 insns, 2 copies: a textured curved beam along the module's spline (shape b018:01E00EE0, here at
   b257:01E00E30) through the given points (b018:01E01320 family): 4 sub-steps per segment, each drawn as a
   4-quad cross (two tilted by half the width), gouraud between the two colours, alpha fading along the beam,
   depth far. The spline must be in the same file and static: the original keeps $a0/$a1 across each call. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b257_01E01270;

typedef struct {
    u8 r, g, b, a;
} Col_b257_01E01270;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b257_01E01270;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b257_01E01270 c;
        u64 st;
        Xyz_b257_01E01270 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b257_01E01270;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b257_01E01270;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b257_01E01270 col0;
    Col_b257_01E01270 col1;
    u8 pad30[8];
    s16 width;
} Beam_b257_01E01270;

static void func_01E01270_b257(Ctx_b257_01E01270 *c, Beam_b257_01E01270 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b257_01E01270 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b257_01E01270 pkt __attribute__((aligned(8)));
    Col_b257_01E01270 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b257_01E01270 *p;
    s32 target;
    f32 t;
    f32 w;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E00E30_b257(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E00E30_b257(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E00E30_b257(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E00E30_b257(ctrl, 0, t);
                ab[1] = r2;
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            for (k = 0; k < 4; k++) {
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
                if (k == 0) {
                    q[1].y += w;
                    q[3].y += w;
                } else if (k == 1) {
                    q[1].y -= w;
                    q[3].y -= w;
                } else if (k == 2) {
                    q[1].x += w;
                    q[3].x += w;
                    q[1].z += w / 2.0f;
                    q[3].z += w / 2.0f;
                } else if (k == 3) {
                    q[1].x -= w;
                    q[3].x -= w;
                    q[1].z -= w / 2.0f;
                    q[3].z -= w / 2.0f;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                    func_002075F0(p, target, 0);
                }
            }
        }
    }
}

/* OVL_WARM: compile warm */

/* shape b257:01E01880, 193 insns: b020:01E00E70 family: 4 copies of a camera-facing square of fx->size at pos (0.05 scale), drawn by depth or at far z */

typedef struct {
    f32 u, v;
} Uv_b257_01E01880;

typedef struct {
    Uv_b257_01E01880 st;
    u64 rgba;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b257_01E01880;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b257_01E01880 v[4];
    u8 tail[0x20];
} Pkt_b257_01E01880;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padcol[0x18];
    u8 xD8[1];
} Obj_b257_01E01880;

typedef struct {
    u8 pad00[8];
    s16 u;
    s16 v;
    u8 pad0C[0x1C];
    u8 col[4];
    u8 col2[4];
    u8 pad30[8];
    s16 size;
    s16 rz;
} Fx_b257_01E01880;

static void func_01E01880_b257(Obj_b257_01E01880 *o, Fx_b257_01E01880 *fx, s32 mode, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b257_01E01880 pkt;
    Uv_b257_01E01880 uv0;
    Uv_b257_01E01880 uv1;
    Uv_b257_01E01880 uv2;
    Uv_b257_01E01880 uv3;
    s16 i;
    Pkt_b257_01E01880 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, fx->col);
    p->v[0].st = uv0;
    func_00107740(&uv1, fx->col);
    p->v[1].st = uv1;
    func_00107740(&uv2, fx->col);
    p->v[2].st = uv2;
    func_00107740(&uv3, fx->col);
    p->v[3].st = uv3;
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    for (i = 0; i < 4; i++) {
        func_00108CE0(quad, fx->size, fx->size);
        func_00109100(quad, rot, 2, o->xD8);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        }
    }
}

/* shape b257:01E01B90, 135 insns: scene spawn step: red scene colour; t++; on frames 78..282 one each of handlers
   0x1E01EB0, 0x1E021E0 and 0x1E024F0 at joint A raised 2; frames 37..54 one 0x1E028B0 at joint B raised 2; frame 20
   fires 0x1E02BC0 twice (0x371A 0 then 90), 0x1E02CF0 and 0x1E02DC0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3464];
    u8 col[4];
    u8 pad36C8[0x40];
    s16 ja;
    u8 pad370A[2];
    s16 jb;
    u8 pad370E[0xC];
    s16 ang;
    u8 pad371C[0xA];
    s16 t;
} Scene_b257_01E01B90;

static void func_01E01B90_b257(Scene_b257_01E01B90 *g) {
    extern void b257_01E01EB0(void);
    extern void b257_01E021E0(void);
    extern void b257_01E024F0(void);
    extern void b257_01E028B0(void);
    extern void b257_01E02BC0(void);
    extern void b257_01E02CF0(void);
    extern void b257_01E02DC0(void);
    extern void b257_01E04400(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t >= 0x4E && g->t < 0x11B) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 2.0f + v.y;
        g->pos.z = v.z;
        for (i = 0; i < 1; i++) {
            b257_01E04400(g, b257_01E01EB0, 0);
        }
        for (i = 0; i < 1; i++) {
            b257_01E04400(g, b257_01E021E0, 0);
        }
        for (i = 0; i < 1; i++) {
            b257_01E04400(g, b257_01E024F0, 0);
        }
    }
    if (g->t >= 0x25 && g->t < 0x37) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        g->pos.x = v.x;
        g->pos.y = 2.0f + v.y;
        g->pos.z = v.z;
        for (i = 0; i < 1; i++) {
            b257_01E04400(g, b257_01E028B0, 0);
        }
    }
    if (g->t == 0x14) {
        g->ang = 0;
        b257_01E04400(g, b257_01E02BC0, 0);
        g->ang += 0x5A;
        b257_01E04400(g, b257_01E02BC0, 0);
    }
    if (g->t == 0x14) {
        b257_01E04400(g, b257_01E02CF0, 0);
    }
    if (g->t == 0x14) {
        b257_01E04400(g, b257_01E02DC0, 0);
    }
}

/* shape b257:01E01DB0, 64 insns: an orange spark (size 50 or 70 by the scene value, random frame 0..3) climbing 6 a tick and growing 20: in by 80 up to 0xA0 for 2 ticks, then out by 15 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b257_01E01DB0;

typedef struct {
    u8 pad[0x3726];
    s16 val;
} Game_b257_01E01DB0;

static s32 func_01E01DB0_b257(Game_b257_01E01DB0 *g, Glow_b257_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (g->val < 80) {
            o->f38 = 50;
        } else {
            o->f38 = 70;
        }
        o->kind = func_0019A5C8() % 4;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->hA += 6;
    o->tick++;
    o->f38 += 20;
    return 0;
}

/* shape b257:01E01EB0, 202 insns: b257:01E021E0's glow in grey 0x70 with a random frame 0..3, start size 53 (63 once
   g+0x3726 reaches 80) growing by 1, rise 5..9, h8 0..9, held 17..26 ticks fading in by 0x40 */

typedef struct {
    u8 pad0[0x3708];
    s16 ja;
    s16 jb;
    u8 pad370C[0x1A];
    s16 h3726;
} Game_b257_01E01EB0;

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
} Glow_b257_01E01EB0;

static s32 func_01E01EB0_b257(Game_b257_01E01EB0 *g, Glow_b257_01E01EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        if (g->h3726 < 80) {
            o->f38 = 53;
        } else {
            o->f38 = 63;
        }
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 17;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
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
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        o->h0 += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
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

/* shape b257:01E021E0, 195 insns: b566:01E018E0's glow with joints g+0x3708/0x370A and its start size 55, or 65
   once the scene value g+0x3726 reaches 80 */

typedef struct {
    u8 pad0[0x3708];
    s16 ja;
    s16 jb;
    u8 pad370C[0x1A];
    s16 h3726;
} Game_b257_01E021E0;

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
} Glow_b257_01E021E0;

static s32 func_01E021E0_b257(Game_b257_01E021E0 *g, Glow_b257_01E021E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        if (g->h3726 < 80) {
            o->f38 = 55;
        } else {
            o->f38 = 65;
        }
        o->kind = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 4;
        o->h8 = func_0019A5C8() % 30;
        o->h6 = func_0019A5C8() % 3 + 5;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x20;
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
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        o->h0 += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 3;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b257:01E024F0, 240 insns: b257:01E01EB0 cousin: size 100, a green, violet or red glow at random, h30 100..149,
   speed 5..14, hold 24..33; the first tick it jumps 17 depth steps toward the camera. As b257:01E01EB0: b257:01E021E0's glow in grey 0x70 with a random frame 0..3, start size 53 (63 once
   g+0x3726 reaches 80) growing by 1, rise 5..9, h8 0..9, held 17..26 ticks fading in by 0x40 */

typedef struct {
    u8 pad0[0x3708];
    s16 ja;
    s16 jb;
    u8 pad370C[0x1A];
    s16 h3726;
} Game_b257_01E024F0;

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
} Glow_b257_01E024F0;

static s32 func_01E024F0_b257(Game_b257_01E024F0 *g, Glow_b257_01E024F0 *o) {
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
        o->hE = func_0019A5C8() % 10 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 24;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0xC1) {
            o->col[3] += 24;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
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

/* shape b257:01E028B0, 194 insns: b008:01E00FB0's puff in grey 0x70, size 70 growing 1, variant 0..3 counting up to 6 every other tick, speed 5..9, 0x8 0..9, hold 3..4; 0xC = the x gap between the tracked points ctx+0x3708 and ctx+0x370C, added to x every other tick; alpha up by 0x40 during the hold, then down by 15; closes a 100th of the camera depth gap */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b257_01E028B0;

typedef struct {
    u8 pad0[0x3708];
    s16 id0;
    u8 pad370A[2];
    s16 id1;
} Ctx_b257_01E028B0;

static s32 func_01E028B0_b257(Ctx_b257_01E028B0 *g, Fx_b257_01E028B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 70;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 2 + 3;
        func_001F5620(func_001F53A0(), g->id0, v);
        func_001F5620(func_001F53A0(), g->id1, &v[4]);
        o->hC = v[4] - v[0];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    v[2] /= 100.0f;
    o->z = o->z + v[2];
    if (o->tick % 2 == 1) {
        o->x += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 6) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b257:01E02BC0, 76 insns: a grey-red rising flash: frame 6, size 20 by 80 growing by 10; both alphas up by 0x40 to 0x80 for 2
   frames, then down by 9; ends when the first runs out; turns 7 a frame */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x1C];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b257_01E02BC0;

static s32 func_01E02BC0_b257(void *arg0, Obj_b257_01E02BC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0xC0, 8, 8);
        o->w = 0x14;
        o->h34 = 1;
        o->h = 0x50;
        o->state = 2;
        o->c0[3] = 0;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xA) {
            o->c1[3] -= 9;
        } else {
            o->c1[3] = 0;
        }
    }
    o->h += 0xA;
    o->t++;
    o->ang += 7;
    return 0;
}

/* shape b257:01E02CF0, 49 insns: b027:01E01600 twin: a red two-colour glow of size 20 at alpha 0x80 for 175 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
} Glow_b257_01E02CF0;

static s32 func_01E02CF0_b257(s32 arg0, Glow_b257_01E02CF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xC0, 0x10, 0x10);
        func_001076F0(o->col2, 0xC0, 0x10, 0x10);
        o->h6 = 9;
        o->col[3] = 0;
        o->kind = 1;
        o->f38 = 20;
        o->mode = 2;
    }
    if (o->tick < 175) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b257:01E02DC0, 44 insns: grey glow: on start colour 0x20, alpha 0, 0x38 = 100; alpha grows by 9 up to 0x60
   for 0x140 ticks, then fades by 9 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b257_01E02DC0;

static s32 func_01E02DC0_b257(s32 arg0, Fx_b257_01E02DC0 *o) {
    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->col[3] = 0;
        o->f38 = 100;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E03430, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b207_01E03430;

static s32 func_01E02E70_b257(s32 arg0, Glow_b207_01E03430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E034E0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x20, 0x20, 0x20) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b207_01E034E0;

static s32 func_01E02F20_b257(s32 arg0, Glow_b207_01E034E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b257:01E02FD0, 123 insns: a yellow-white circling glow on a model joint: frame 40, angle from its start value; alpha up by 4 for
   18 frames, then flickering 0x40/0x50; sits on the joint, circling 3 around it as the angle turns 10 a frame; ends at frame 211 */

typedef struct {
    u8 pad0[0x3708];
    s16 joint;
    u8 pad370A[0x122];
    u8 sin[1];
} Game_b257_01E02FD0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 c1[4];
    s16 ang0;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b257_01E02FD0;

static s32 func_01E02FD0_b257(Game_b257_01E02FD0 *g, Obj_b257_01E02FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    func_00108030(g->sin, o->ang, 0);
    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0xC0, 0xC0, 0);
        o->ang = o->ang0;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x12) {
        o->c0[3] += 4;
    } else if (o->t % 2 == 1) {
        o->c0[3] = 0x40;
    } else {
        o->c0[3] = 0x50;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    o->x = func_001A22C0(o->x + 3.0f * func_00108030(g->sin, o->ang, 0));
    o->z = func_001A22C0(o->z + 3.0f * func_00108030(g->sin, o->ang, 1));
    o->t++;
    if (o->t > 0xD2) {
        o->state = 0;
    }
    o->ang += 0xA;
    if (o->ang >= 0x168) {
        o->ang %= 360;
    }
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

static s32 func_01E031C0_b257(s32 arg0, Flash_b257_01E031C0 *o) {
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

/* shape b257:01E032A0, 173 insns: b482:01E02E40 family scene flash light (ctx+0x3520, 0xC4 70) at the effect's point: warms by 42/21/10 toward orange while the level rises 0.2 to 1, then cools by 16/16/8 and dims 0.1 to 0.1; ends when ctx+0x36C0 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b257_01E032A0;

typedef struct {
    u8 pad0[0x3520];
    Light_b257_01E032A0 light;
    u8 padL[0x36C0 - 0x3520 - 0x2C];
    s32 flag;
} Scene_b257_01E032A0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b257_01E032A0;

static s32 func_01E032A0_b257(Scene_b257_01E032A0 *g, Fx_b257_01E032A0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.c[0] = 0.0f;
        g->light.c[1] = 0.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 70.0f;
        g->light.level = 0.0f;
        g->light.pos.x = o->x;
        g->light.pos.y = o->y;
        g->light.pos.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.2f;
        } else {
            o->phase = 1;
        }
        if (g->light.c[0] < 128.0f) {
            g->light.c[0] += 42.0f;
        } else {
            g->light.c[0] = 128.0f;
        }
        if (g->light.c[1] < 64.0f) {
            g->light.c[1] += 21.0f;
        } else {
            g->light.c[1] = 128.0f;
        }
        if (g->light.c[2] < 32.0f) {
            g->light.c[2] += 10.0f;
        } else {
            g->light.c[2] = 64.0f;
        }
    } else {
        if (g->light.level > 0.1f) {
            g->light.level -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (g->light.c[0] > 16.0f) {
            g->light.c[0] -= 16.0f;
        } else {
            g->light.c[0] = 0.0f;
        }
        if (g->light.c[1] > 16.0f) {
            g->light.c[1] -= 16.0f;
        } else {
            g->light.c[1] = 0.0f;
        }
        if (g->light.c[2] > 8.0f) {
            g->light.c[2] -= 8.0f;
        } else {
            g->light.c[2] = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b257:01E03560, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x36C0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x36C0];
    s32 state;
} Game_b257_01E03560;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b257_01E03560;

static s32 func_01E03560_b257(Game_b257_01E03560 *g, Fade_b257_01E03560 *o) {
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

static s32 func_01E03620_b257(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04580_b257;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04588_b257;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b257:01E03670 (b257), 865 insns, 1 copy: scene manager: two passes over 200 slots, camera-side picks the
   trail joint, three inline fade handlers */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x1C];
    void *fn;
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    u8 pad3A[6];
} Slot_b257_01E03670;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Rot_b257_01E03670;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        Vec4f rm;
        s16 uv[8];
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x1B8];
    s32 z290[3];
    u8 pad29C[0x24];
    s32 tex[16];
    Slot_b257_01E03670 slot[200];
    s32 tex5[4];
    u8 pad3510[0x60];
    Vec4f tr[20];
    u8 pad36B0[0x10];
    s32 count;
    u8 pad36C4[8];
    s32 ot;
    u8 pad36D0[0x38];
    s16 j[5];
    u8 pad3712[0x12];
    s16 id;
    s16 state;
    u8 pad3728[2];
    s8 jit[0x100];
    u8 pad382A[2];
    u8 crd[0x174];
} Scene_b257_01E03670;

static s32 func_01E03670_b257(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00205C40(void *);
    extern void func_001F6160(s32, void *);
    extern f32 *func_001F9D30(s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001F7170(s32, s32, s32, s32, s32);
    extern void b257_01E01B90();
    Scene_b257_01E03670 *g = (Scene_b257_01E03670 *)arg0;
    f32 *cam;
    s32 m;
    Rot_b257_01E03670 r;
    Vec4f pos;
    Vec4f rm;
    Vec4f rm2;
    Vec4f rm3;
    Vec4f rm4;
    Vec4f rm5;
    Vec4f rm6;
    Vec4f rm7;
    Vec4f pa;
    Vec4f pa2;
    Vec4f pa3;
    Vec4f pa4;
    f32 b;
    f32 a;
    s32 i;

    m = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x39A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x140;
        g->z290[0] = 0;
        g->z290[1] = 0;
        g->z290[2] = 0;
        g->j[0] = func_001F5560(func_001F53A0(), 0x32, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x31, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x37, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x36, 0);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 4; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b257_01E01B90(g, 0);
    func_00205C40(&r);
    func_001F6160(func_001F53A0(), &r);
    cam = func_001F9D30(0);
    if (r.y < 0x4000) {
        if (*cam < 0.0f) {
            if (g->state == 20) {
                Vec4f *p = g->tr;

                func_001F5620(func_001F53A0(), g->j[3], &pa);
                for (i = 0; i < 9; i++, p++) {
                    p->x = pa.x;
                    p->y = pa.y;
                    p->z = pa.z;
                }
            }
            func_01E00080_b257((void *)&g->tr[9], 10, g->j[3]);
        } else {
            if (g->state == 20) {
                Vec4f *p = g->tr;

                func_001F5620(func_001F53A0(), g->j[4], &pa2);
                for (i = 0; i < 9; i++, p++) {
                    p->x = pa2.x;
                    p->y = pa2.y;
                    p->z = pa2.z;
                }
            }
            func_01E00080_b257((void *)&g->tr[9], 10, g->j[4]);
        }
    } else {
        if (*cam > 0.0f) {
            if (g->state == 20) {
                Vec4f *p = g->tr;

                func_001F5620(func_001F53A0(), g->j[3], &pa3);
                for (i = 0; i < 9; i++, p++) {
                    p->x = pa3.x;
                    p->y = pa3.y;
                    p->z = pa3.z;
                }
            }
            func_01E00080_b257((void *)&g->tr[9], 10, g->j[3]);
        } else {
            if (g->state == 20) {
                Vec4f *p = g->tr;

                func_001F5620(func_001F53A0(), g->j[4], &pa4);
                for (i = 0; i < 9; i++, p++) {
                    p->x = pa4.x;
                    p->y = pa4.y;
                    p->z = pa4.z;
                }
            }
            func_01E00080_b257((void *)&g->tr[9], 10, g->j[4]);
        }
    }
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (void *)func_01E01DB0_b257) {
                func_01E01DB0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E01EB0_b257) {
                func_01E01EB0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E021E0_b257) {
                func_01E021E0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E024F0_b257) {
                func_01E024F0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E028B0_b257) {
                func_01E028B0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02BC0_b257) {
                func_01E02BC0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02CF0_b257) {
                func_01E02CF0_b257((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02DC0_b257) {
                if (g->slot[i].used == 1) {
                    func_001076F0(g->slot[i].c0, 0x20, 0x20, 0x20);
                    g->slot[i].c0[3] = 0;
                    g->slot[i].h38 = 100;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x140) {
                    if (g->slot[i].c0[3] < 0x60) {
                        g->slot[i].c0[3] += 9;
                    }
                } else if (g->slot[i].c0[3] > 0xA) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == (void *)func_01E02E70_b257) {
                if (g->slot[i].used == 1) {
                    func_001076F0(g->slot[i].c0, 0x60, 0x60, 0x60);
                    g->slot[i].life = 9;
                    g->slot[i].c0[3] = 0x80;
                    g->slot[i].h38 = 6;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x140) {
                    g->slot[i].c0[3] = 0x80;
                } else if (g->slot[i].c0[3] > 0xA) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == (void *)func_01E02F20_b257) {
                if (g->slot[i].used == 1) {
                    func_001076F0(g->slot[i].c0, 0x20, 0x20, 0x20);
                    g->slot[i].life = 9;
                    g->slot[i].c0[3] = 0x80;
                    g->slot[i].h38 = 6;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x140) {
                    g->slot[i].c0[3] = 0x80;
                } else if (g->slot[i].c0[3] > 0xA) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == (void *)func_01E02FD0_b257) {
                func_01E02FD0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E031C0_b257) {
                func_01E031C0_b257((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E032A0_b257) {
                func_01E032A0_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E03560_b257) {
                func_01E03560_b257((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E03620_b257) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04580_b257;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04588_b257;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == (void *)func_01E01EB0_b257) {
                g->tex88 = g->tex5[0];
                func_00106080(&rm, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b257((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == (void *)func_01E021E0_b257) {
                g->tex88 = g->tex5[1];
                func_00106080(&rm2, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b257((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == (void *)func_01E024F0_b257) {
                g->tex88 = g->tex5[2];
                func_00106080(&rm3, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm3;
                g->hB8 = 6;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b257((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == (void *)func_01E028B0_b257) {
                g->tex88 = g->tex5[2];
                func_00106080(&rm4, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm4;
                g->hB8 = 1;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b257((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == (void *)func_01E02BC0_b257) {
                g->tex88 = g->tex[15];
                func_00106080(&rm5, 0x9A, g->slot[i].h34, NULL);
                g->u94.rm = rm5;
                if (r.y < 0x4000) {
                    if (*cam < 0.0f) {
                        func_001F5620(func_001F53A0(), g->j[3], &pos);
                    } else {
                        func_001F5620(func_001F53A0(), g->j[4], &pos);
                    }
                } else {
                    if (*cam > 0.0f) {
                        func_001F5620(func_001F53A0(), g->j[3], &pos);
                    } else {
                        func_001F5620(func_001F53A0(), g->j[4], &pos);
                    }
                }
                g->hBE = 0;
                func_01E00B20_b257((void *)g, (void *)&g->slot[i], 1, pos);
            }
            if (g->slot[i].fn == (void *)func_01E02CF0_b257) {
                g->tex88 = g->tex[15];
                g->tex88 = g->tex5[3];
                func_00106080(&rm6, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm6;
                g->hBE = 0;
                g->u94.uv[0] = 0xF;
                g->u94.uv[1] = 0x10;
                g->u94.uv[2] = 0xF;
                g->u94.uv[3] = 1;
                func_01E01270_b257((void *)g, (void *)&g->slot[i], (void *)g->tr);
            }
            if (g->slot[i].fn == (void *)func_01E02DC0_b257) {
                g->tex88 = g->tex5[3];
                func_00106080(&rm7, 0x14, g->slot[i].h34, NULL);
                g->u94.rm = rm7;
                if (r.y < 0x4000) {
                    if (*cam < 0.0f) {
                        func_001F5620(func_001F53A0(), g->j[3], &pos);
                    } else {
                        func_001F5620(func_001F53A0(), g->j[4], &pos);
                    }
                } else {
                    if (*cam > 0.0f) {
                        func_001F5620(func_001F53A0(), g->j[3], &pos);
                    } else {
                        func_001F5620(func_001F53A0(), g->j[4], &pos);
                    }
                }
                g->hBE = 0;
                func_01E01880_b257((void *)g, (void *)&g->slot[i], 1, pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->state == 90) {
        return 1;
    }
    if (g->state == 0x131) {
        return 3;
    }
    if (g->state > 100 && g->state < 300) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b257:01E04400, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3722 and 0x371A and the two arguments; returns 1 if a
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
} Slot_b257_01E04400;

typedef struct {
    u8 pad[0x250];
    u8 m[0xB0];
    Slot_b257_01E04400 s[200];
    u8 pad3500[0x1C4];
    u8 r, g, b, a;
    u8 pad36C8[0x52];
    s16 w;
    u8 pad371C[0x6];
    s16 v;
} Pool_b257_01E04400;

static s32 func_01E04400_b257(Pool_b257_01E04400 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b257_01E04400 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
