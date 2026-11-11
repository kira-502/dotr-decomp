#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b501(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b501(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static Vec_b018_01E00EE0 func_01E009F0_b501(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b119:01E00D30, 199 insns, 3 copies: draws one sprite at a given position plus a tenth of an offset, turned by
   the sprite's rotation; blend from flags >> 4, depth mode flags & 0xF (projected or far). Texture corners by
   the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b119_01E00D30;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b119_01E00D30 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b119_01E00D30;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b119_01E00D30;

typedef struct {
    u8 pad0[8];
    s16 dx, dy, dz;
    u8 padE[2];
    Vec4f rot;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b119_01E00D30;

static void func_01E00E30_b501(Obj_b119_01E00D30 *o, Spr_b119_01E00D30 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b119_01E00D30 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b119_01E00D30 pkt __attribute__((aligned(8)));
    Pkt_b119_01E00D30 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b119_01E00D30 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if ((flags >> 4) == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00150_b501((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    p2.x = pos.x + dx;
    p2.y = pos.y + dy;
    p2.z = pos.z + dz;
    func_00108EF0(m, &scale, rot, &p2);
    func_00108CE0(quad, s->size, s->size);
    func_00109100(quad, &s->rot, 2, o->xD8);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        if ((flags & 0xF) == 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        } else if ((flags & 0xF) == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E01150_b501(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00150_b501((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b081:01E05C10 (B081PAINT_RAIN10), 517 insns, 4 copies: b121:01E033A0 beam form with a world matrix: the
   textured beam along the module spline (b081:01E009A0), 3 sub-steps per segment, each a 2-quad cross drawn through a
   matrix from the beam rotation (0x10) at the context position; width shrinks by width/(4n) per step, alpha fades by
   col0.a/(3n); also reads the camera angle (unused); flags picks the depth (0 real, 1 far, 2 -1) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b081_01E05C10;

typedef struct {
    u8 r, g, b, a;
} Col_b081_01E05C10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b081_01E05C10;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b081_01E05C10 c;
        u64 st;
        Xyz_b081_01E05C10 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b081_01E05C10;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b081_01E05C10;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[8];
    s32 rot[4];
    u8 pad20[8];
    Col_b081_01E05C10 col0;
    Col_b081_01E05C10 col1;
    u8 pad30[8];
    s16 width;
} Beam_b081_01E05C10;

/* pts aligned: its spill slot, needed for the match */
static void func_01E016B0_b501(Ctx_b081_01E05C10 *c, Beam_b081_01E05C10 *an, Vec_b018_01E00EE0 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b081_01E05C10 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00205C40(s32 *);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 prev;
    Vec_b018_01E00EE0 q[4];
    Vec_b018_01E00EE0 pos;
    f32 depth[4];
    s32 rot[4];
    f32 m[16];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b081_01E05C10 pkt __attribute__((aligned(8)));
    Col_b081_01E05C10 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b081_01E05C10 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    w0 = w;
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
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 3; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = func_01E009F0_b501(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.33f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                r1 = func_01E009F0_b501(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = func_01E009F0_b501(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.33f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                r2 = func_01E009F0_b501(ctrl, 0, t);
                ab[1] = r2;
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (4.0f * n);
            for (k = 0; k < 2; k++) {
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
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if (flags == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                } else if (flags == 2) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, -1);
                    }
                }
            }
        }
    }
}

/* shape b112:01E00B60, 296 insns, 5 copies: draws a flat ring of 18 quads (inner and outer radius, 20 table steps
   apart) around a position, two colours; depth mode 0 (projected), 1 (far, after a packet tweak) or else front. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b112_01E00B60;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[0x20];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b112_01E00B60;

static void func_01E01ED0_b501(Obj_b112_01E00B60 *o, Ring_b112_01E00B60 *s, s32 mode, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    u8 pkt[0x90];
    s32 t;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[0].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[2].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[2].z = s->inner * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

/* shape b501:01E02370, 335 insns: B501_W_S, the scene script: black-red tint, counts the scene frame (0x2B5E) and
   spawns the module's movers on it: 12 pairs at both tracked joints on frame 34 and one pair a frame on 34..40 (and
   12 more at one joint each on frames 53 / 55), a trail point at the third joint (ring of 50 at 0x2410) with two
   movers on frames 90..120 (and a third every fourth frame) or one on 50..58, the turning angle (-8 a frame), the
   two on frame 49, six on frame 3 */

typedef struct {
    u8 pad0000[0x250];
    f32 px, py, pz;
    u8 pad025C[0x2410 - 0x25C];
    Vec4f pts[50];
    u8 pad2730[0x2B14 - 0x2730];
    u8 col[4];
    u8 pad2B18[0x2B3C - 0x2B18];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 pad2B42[0xC];
    s16 h4E;
    s16 ang;
    u8 pad2B52[2];
    s16 kind;
    u8 pad2B56[4];
    s16 idx;
    u8 pad2B5C[2];
    s16 frame;
} Ctx_b501_01E02370;

static void func_01E02370_b501(Ctx_b501_01E02370 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void b501_01E04690();
    extern s32 b501_01E028B0();
    extern s32 b501_01E02D10();
    extern s32 b501_01E02DE0();
    extern s32 b501_01E02FE0();
    extern s32 b501_01E03130();
    extern s32 b501_01E03310();
    extern s32 b501_01E03530();
    extern s32 b501_01E03680();
    extern s32 b501_01E03800();
    extern s32 b501_01E03880();
    f32 v[8];
    s16 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->frame++;
    if (g->frame == 20) {
        b501_01E04690(g, b501_01E03800, 0);
    }
    if (g->frame == 90) {
        b501_01E04690(g, b501_01E03880, 0);
    }
    if (g->frame == 34) {
        for (i = 0; i < 12; i++) {
            func_001F5620(func_001F53A0(), g->j0, v);
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2];
            b501_01E04690(g, b501_01E03680, 0);
            func_001F5620(func_001F53A0(), g->j1, v);
            g->px = v[0];
            g->py = v[1];
            g->pz = v[2];
            b501_01E04690(g, b501_01E03680, 0);
        }
    }
    if (g->frame >= 34 && g->frame < 41) {
        g->kind = 1;
        func_001F5620(func_001F53A0(), g->j0, v);
        g->px = v[0];
        g->py = v[1];
        g->pz = v[2];
        b501_01E04690(g, b501_01E03680, 0);
        func_001F5620(func_001F53A0(), g->j1, v);
        g->px = v[0];
        g->py = v[1];
        g->pz = v[2];
        b501_01E04690(g, b501_01E03680, 0);
    }
    if (g->frame == 53 || g->frame == 55) {
        g->kind = 0;
        for (i = 0; i < 12; i++) {
            if (g->frame == 53) {
                func_001F5620(func_001F53A0(), g->j0, v);
                g->px = v[0];
                g->py = v[1];
                g->pz = v[2];
                b501_01E04690(g, b501_01E03680, 0);
            }
            if (g->frame == 55) {
                func_001F5620(func_001F53A0(), g->j1, v);
                g->px = v[0];
                g->py = v[1];
                g->pz = v[2];
                b501_01E04690(g, b501_01E03680, 0);
            }
        }
    }
    if (g->frame >= 90 && g->frame < 121) {
        func_001F5620(func_001F53A0(), g->j2, &g->pts[g->idx]);
        g->kind = g->idx;
        g->h4E = g->ang;
        b501_01E04690(g, b501_01E03530, 0);
        b501_01E04690(g, b501_01E02DE0, 0);
        g->idx++;
        if (g->idx >= 50) {
            g->idx = 0;
        }
        if (g->frame % 4 == 1) {
            b501_01E04690(g, b501_01E02D10, 0);
        }
    }
    if (g->frame >= 50 && g->frame < 59) {
        func_001F5620(func_001F53A0(), g->j2, &g->pts[g->idx]);
        g->kind = g->idx;
        g->h4E = g->ang;
        b501_01E04690(g, b501_01E02FE0, 0);
        g->idx++;
        if (g->idx >= 50) {
            g->idx = 0;
        }
    }
    g->ang -= 8;
    if (g->ang < -359) {
        g->ang %= 360;
    }
    if (g->frame == 49) {
        b501_01E04690(g, b501_01E03310, 0);
    }
    if (g->frame == 49) {
        b501_01E04690(g, b501_01E028B0, 0);
    }
    if (g->frame == 3) {
        for (i = 0; i < 6; i++) {
            g->kind = i;
            b501_01E04690(g, b501_01E03130, 0);
        }
    }
}

/* shape b501:01E028B0, 92 insns: on start colour (0x20, 0x20, 0xF0), the game's 9 trail points (0x2930) all set to
   model point 0x2B46, 0x6 = 8, alpha 0, 0xA 44..60, 0x8 5..12, random 0x3A, 0x38 = 5; alpha 0xC0 for 11 ticks, then
   fades by 0x23 and stops; registers model point 0x2B46 with the game list 0x29C0 (b501:01E00080, kind 10) */

typedef struct {
    u8 pad0[0x2930];
    Vec4f pts[9];
    u8 list[0x2B46 - 0x29C0];
    s16 point;
} Game_b501_01E028B0;

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b501_01E028B0;

static s32 func_01E028B0_b501(Game_b501_01E028B0 *g, Fx_b501_01E028B0 *o) {
    extern void b501_01E00080(void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f pt;
    Vec4f *q;
    s32 i;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0xF0);
        q = g->pts;
        func_001F5620(func_001F53A0(), g->point, &pt);
        for (i = 0; i < 9; i++) {
            q->x = pt.x;
            q->y = pt.y;
            q->z = pt.z;
            q++;
        }
        o->f6 = 8;
        o->col[3] = 0;
        o->fA = func_0019A5C8() % 17 + 0x2C;
        o->f8 = func_0019A5C8() % 8 + 5;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f38 = 5;
        o->mode = 2;
    }
    if (o->tick < 11) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x24) {
        o->col[3] -= 0x23;
    } else {
        o->mode = 0;
    }
    b501_01E00080(g->list, 10, g->point);
    o->tick++;
    return 0;
}

/* shape b501:01E02A20, 187 insns: b297:01E014F0's glow (grey 0x30, or dull red 0x40/0x10/0x10 when 0x30 was set)
   without joints: it drifts with the camera depth (/35), sinks one every other tick while above the camera height
   - 15, and keeps growing by 1 */

typedef struct {
    u8 pad0[0x3514];
    s16 ja;
    s16 jb;
} Game_b501_01E02A20;

typedef struct {
    u8 pad0[2];
    s16 h2;
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
} Glow_b501_01E02A20;

static s32 func_01E02A20_b501(Game_b501_01E02A20 *g, Glow_b501_01E02A20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 40;
        o->kind = 0;
        if (o->h30 == 0) {
            func_001076F0(o->col, 0x30, 0x30, 0x30);
        } else {
            func_001076F0(o->col, 0x40, 0x10, 0x10);
        }
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 20;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 65) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 35.0f;
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->h2 > v[1].y - 15.0f) {
        if (o->tick % 2 == 1) {
            o->h2--;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->f38++;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b501:01E02D10, 52 insns: a dark/yellow two-colour ring at the given angle: alpha 0xA0 for 3 ticks, then out by 35 and ends; grows 30 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b501_01E02D10;

static s32 func_01E02D10_b501(s32 arg0, Glow_b501_01E02D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 30;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x70, 0x70, 0xF0);
        o->w18 = 0x4000;
        o->ang = o->h30;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        o->col[3] = 0xA0;
    } else if (o->col[3] > 0x36) {
        o->col[3] -= 35;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->f38 += 30;
    return 0;
}

/* shape b501:01E02DE0, 128 insns: a red drifting ember: on start a random parity frame, life 20..54 fall speed, frame
   0..34, fade-in 2..4 ticks; alpha 0x80 during the fade-in, then down by 15 until it ends; the frame steps every third
   tick to 7; it blinks grey 0x80 / 0xC0 on odd/even ticks, falls by its speed and turns by 2 a tick */

typedef struct {
    u8 pad0[6];
    s16 fadein;
    s16 frame;
    s16 oldy;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 step;
    s16 mode;
    s16 f38;
    s16 ang;
} Obj_b501_01E02DE0;

static s32 func_01E02DE0_b501(void *g, Obj_b501_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x2E;
        o->step = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->oldy = o->y;
        o->y = 0;
        o->ang = 0;
        o->speed = func_0019A5C8() % 35 + 20;
        o->frame = func_0019A5C8() % 35;
        o->fadein = func_0019A5C8() % 3 + 2;
        o->fC = 0;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->t < o->fadein) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 0xF;
    } else {
        o->mode = 0;
    }
    if (o->t % 3 == 1) {
        if (o->step < 7) {
            o->step++;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    o->y += o->speed;
    if (o->t != 0) {
        o->ang -= 2;
    }
    o->t++;
    return 0;
}

/* shape b501:01E02FE0, 83 insns: on start 0x38 = 6, variant 0..3 (0x34), colour (0x80, 0x10, 0x40), 0xA keeps the old
   0x30 (0x3A cleared), speed 15..49 (0xE), 0x8 0..34, hold 6..8 (0x6); alpha grows by 0x40 (up to 0x80) during the hold, then fades
   by 9 and stops; 0x30 grows by the speed */

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
} Fx_b501_01E02FE0;

static s32 func_01E02FE0_b501(s32 arg0, Fx_b501_01E02FE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x10, 0x40);
        o->fA = o->f30;
        o->f30 = 0;
        o->f3A = 0;
        o->speed = func_0019A5C8() % 35 + 15;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 6;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f30 += o->speed;
    o->tick++;
    return 0;
}

/* shape b501:01E03130, 119 insns: a grey/blue glow (size 60, turn 0x4000, at its own angle) scripted on the scene value: in by 4 up to 0x50 for 18 ticks; flickers 0x40/0x50 until 54, drops by 40 until 69, flashes 0x50 at 69, flickers until 124, then out by 15 and ends; also ends after 211 ticks or at scene value 138 */

typedef struct {
    u8 pad0[0x18];
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
} Glow_b501_01E03130;

typedef struct {
    u8 pad[0x2B5E];
    s16 val;
} Game_b501_01E03130;

static s32 func_01E03130_b501(Game_b501_01E03130 *g, Glow_b501_01E03130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        func_001076F0(o->col2, 0x10, 0x10, 0xC0);
        o->w18 = 0x4000;
        o->ang = o->h30;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 18) {
        if (o->col[3] < 0x50) {
            o->col[3] += 4;
        }
    } else if (g->val < 54) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0x40;
        } else {
            o->col[3] = 0x50;
        }
    } else if (g->val < 69) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x28;
        } else {
            o->col[3] = 0;
        }
    } else if (g->val == 69) {
        o->col[3] = 0x50;
    } else if (g->val < 124) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0x40;
        } else {
            o->col[3] = 0x50;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick > 210) {
        o->mode = 0;
    }
    if (g->val == 138) {
        o->mode = 0;
    }
    return 0;
}

/* shape b501:01E03310, 134 insns: blue (0x40, 0x40, 0x80) three-trail head: on start fills the scene's three 9-point trails (ctx+0x2750/0x27F0/0x2890) with the three tracked points (ids at ctx+0x2B40..44); alpha 0xC0 for 11 ticks, then down by 35; every tick pushes each point into its trail (b501:01E00080, 10 steps) */

typedef struct {
    Vec4f pt[9];
    Vec4f head;
} Trail_b501_01E03310;

typedef struct {
    u8 pad0[0x2750];
    Trail_b501_01E03310 a;
    Trail_b501_01E03310 b;
    Trail_b501_01E03310 c;
    u8 pad2930[0x2B40 - 0x2930];
    s16 id0;
    s16 id1;
    s16 id2;
} Ctx_b501_01E03310;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b501_01E03310;

static s32 func_01E03310_b501(Ctx_b501_01E03310 *g, Fx_b501_01E03310 *o) {
    extern void b501_01E00080(Vec4f *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    Vec4f va;
    Vec4f vb;
    Vec4f vc;
    Vec4f *p;
    s32 i;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x40, 0x40, 0x80);
        p = g->a.pt;
        func_001F5620(func_001F53A0(), g->id0, &va);
        for (i = 0; i < 9; i++) {
            p[i].x = va.x;
            p[i].y = va.y;
            p[i].z = va.z;
        }
        p = g->b.pt;
        func_001F5620(func_001F53A0(), g->id1, &vb);
        for (i = 0; i < 9; i++) {
            p[i].x = vb.x;
            p[i].y = vb.y;
            p[i].z = vb.z;
        }
        p = g->c.pt;
        func_001F5620(func_001F53A0(), g->id2, &vc);
        for (i = 0; i < 9; i++) {
            p[i].x = vc.x;
            p[i].y = vc.y;
            p[i].z = vc.z;
        }
        o->hold = 6;
        o->col[3] = 0;
        o->fA = func_0019A5C8() % 17 + 44;
        o->f8 = func_0019A5C8() % 8 + 5;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f38 = 30;
        o->mode = 2;
    }
    if (o->tick < 11) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 36) {
        o->col[3] -= 35;
    } else {
        o->mode = 0;
    }
    b501_01E00080(&g->a.head, 10, g->id0);
    b501_01E00080(&g->b.head, 10, g->id1);
    b501_01E00080(&g->c.head, 10, g->id2);
    o->tick++;
    return 0;
}

/* shape b501:01E03530, 82 insns: on start 0x38 = 6, variant 0..3 (0x34), colour (0x80, 0x10, 0x40), 0xA keeps the old
   0x30, speed 15..49 (0xE), 0x8 0..34, hold 6..8 (0x6); alpha grows by 0x40 (up to 0x80) during the hold, then fades
   by 9 and stops; 0x30 grows by the speed */

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
} Fx_b501_01E03530;

static s32 func_01E03530_b501(s32 arg0, Fx_b501_01E03530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x10, 0x40);
        o->fA = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 35 + 15;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 6;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f30 += o->speed;
    o->tick++;
    return 0;
}

/* shape b501:01E03680, 96 insns: b115:01E01980 family: a white spark (size 60, frame 5); flagged ones get a random tilt and drift 10 a tick along their angle (sine table ctx+0x2E60), unflagged ones stay put: alpha 0x80 for 7 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[8];
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
} Glow_b501_01E03680;

typedef struct {
    u8 pad[0x2e60];
    u8 sin[1];
} Game_b501_01E03680;

static s32 func_01E03680_b501(Game_b501_01E03680 *g, Glow_b501_01E03680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = 5;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        if (o->h30 == 0) {
            o->h30 = func_0019A5C8() % 360;
        } else {
            o->h30 = 0;
        }
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->h30 != 0) {
        o->h8 = func_001A22C0(o->h8 + 10.0f * func_00108030(g->sin, o->ang, 0));
        o->hC = func_001A22C0(o->hC + 10.0f * func_00108030(g->sin, o->ang, 1));
    }
    o->tick++;
    return 0;
}

/* shape b501:01E03800, 31 insns: b018:01E02DB0 family: func_001F7170(2, 0) with the module's two floats, then ends the object when the scene counter is 150 */

extern f32 D_01E04D00_b501;
extern f32 D_01E04D08_b501;

typedef struct {
    u8 pad0[0x2B5E];
    s16 v;
} Ctx_b501_01E03800;

typedef struct {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[2];
    s16 h36;
    u8 pad38[0x1C];
    s16 h54;
    u8 pad56[2];
    s16 h58;
} Obj_b501_01E03800;

static s32 func_01E03800_b501(Ctx_b501_01E03800 *ctx, Obj_b501_01E03800 *o) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04D00_b501;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04D08_b501;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    if (ctx->v == 150) {
        o->h36 = 0;
    }
    return 0;
}

/* shape b501:01E03880, 103 insns: b582:01E03470 family scene light at ctx+0x2340 (orange 4/2/0, height 120) whose range flickers 128/192: raised by 0.2 to 1 for 21 ticks, then lowered by 0.1 and ended; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b501_01E03880;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x7a4];
    s32 state;
} Light_b501_01E03880;

typedef struct {
    u8 pad[0x2340];
    Light_b501_01E03880 l;
} Game_b501_01E03880;

static s32 func_01E03880_b501(Game_b501_01E03880 *g, Obj_b501_01E03880 *o) {
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
    if (o->tick < 21) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        }
    } else if (g->l.level > 0.1f) {
        g->l.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        g->l.w0 = 128.0f;
    } else {
        g->l.w0 = 192.0f;
    }
    o->tick++;
    if (g->l.state == 1) {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b501", func_01E03A20_b501);

/* shape b501:01E04690, 74 insns: twin of b046:01E03E20: take the first free slot of the 130-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x2B54 and 0x2B4E and the two arguments; returns 1 if a
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
} Slot_b501_01E04690;

typedef struct {
    u8 pad[0x250];
    u8 m[0x70];
    Slot_b501_01E04690 s[130];
    u8 pad2340[0x7D4];
    u8 r, g, b, a;
    u8 pad2B18[0x36];
    s16 w;
    u8 pad2B50[0x4];
    s16 v;
} Pool_b501_01E04690;

static s32 func_01E04690_b501(Pool_b501_01E04690 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b501_01E04690 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 130; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 130;
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

/* shape b476:01E042E0, 311 insns: b256:01E04AB0's ribbon (4 spline quads per segment between two trails, module
   curve function shape b018:01E00EE0), one colour fading by alpha / (2 * n) per quad on the far edge. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b476_01E042E0;

typedef struct {
    Rgbaq_b476_01E042E0 c;
    u64 xyz;
} Vtx_b476_01E042E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b476_01E042E0 v[4];
    u8 tail[0x40];
} Pkt_b476_01E042E0;

typedef struct {
    u8 r, g, b, a;
} C4_b476_01E042E0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b476_01E042E0 col;
} Rib_b476_01E042E0;

static void func_01E047C0_b501(void *o, Rib_b476_01E042E0 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b476_01E042E0 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b476_01E042E0 pkt __attribute__((aligned(8)));
    C4_b476_01E042E0 col;
    s32 k;
    s32 j;
    s16 n;
    s32 x;
    s32 ot;
    Pkt_b476_01E042E0 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b476_01E042E0 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = s->col;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[0].c = func_00107740(&col);
            p->v[2].c = func_00107740(&col);
            x = col.a - (s16)(s->col.a / (n * 2));
            if (x > 0) {
                col.a = x;
            } else {
                col.a = 0;
            }
            p->v[1].c = func_00107740(&col);
            p->v[3].c = func_00107740(&col);
            if (k != 0) {
                A[0] = func_01E009F0_b501(pp, 0, t);
                B[0] = func_01E009F0_b501(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E009F0_b501(pp, 0, t);
                B[1] = func_01E009F0_b501(pq, 0, t);
            } else {
                A[0] = func_01E009F0_b501(a4, 0, t);
                B[0] = func_01E009F0_b501(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E009F0_b501(a4, 0, t);
                B[1] = func_01E009F0_b501(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}
