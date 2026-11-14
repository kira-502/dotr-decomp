#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b500(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b500(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E009F0_b500(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

/* shape b046:01E01A60, 283 insns, 10 copies: draws obj->count (0 = 20) sprites along a curve read from three s8
   tables (0x64 apart), each turned on three axes by the definition's angles; mode 0 = depth from the
   projection, 1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static
   function. Sibling of b003:01E00EA0 and b018:01E005A0. */

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
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b046_01E01A60;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b046_01E01A60;

typedef struct {
    union {
        struct {
            u64 x : 16;
            u64 y : 16;
            u64 z : 24;
            u64 fog : 8;
        } b;
        struct {
            u8 pad[7];
            u8 fog;
        } h;
    } xyz;
    u64 reg;
} Xyz_b046_01E01A60;

typedef struct {
    f32 u, v;
} Uv_b046_01E01A60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E01A60 uv;
    u64 pad18;
    Xyz_b046_01E01A60 v[4];
    u64 pad60[6];
} Pk_b046_01E01A60;

typedef struct {
    u64 tag;
    Pk_b046_01E01A60 pk;
} Buf_b046_01E01A60;

static void func_01E00C80_b500(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b046_01E01A60 buf;
    Uv_b046_01E01A60 uv;
    s16 i;
    Pk_b046_01E01A60 *p;
    s16 n;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.uv.v = 0.0f;
    buf.pk.v[0].xyz.h.fog = 0;
    buf.pk.v[1].xyz.h.fog = 0;
    buf.pk.v[2].xyz.h.fog = 0;
    buf.pk.v[3].xyz.h.fog = 0;
    func_00107740(&uv, def->tex);
    buf.pk.uv = uv;
    func_01E00150_b500((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, rot, &pos);
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        func_00107070(m2, 0, f * (def->scale + h));
        f = t[def->tab + 100];
        f /= 20.0f;
        func_00107070(m2, 1, f * (def->scale + h));
        f = t[def->tab + 180];
        f /= 20.0f;
        func_00107070(m2, 2, f * (def->scale + h));
        func_00109100(m2, def->rot, 0, obj->fD8);
        func_00109100(m2, def->rot, 1, obj->fD8);
        func_00109100(m2, def->rot, 2, obj->fD8);
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].xyz.b.z = p->v[1].xyz.b.z = p->v[2].xyz.b.z = p->v[3].xyz.b.z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
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

static void func_01E010F0_b500(Obj_b119_01E00D30 *o, Spr_b119_01E00D30 *s, s32 flags, Vec4f pos) {
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
    func_01E00150_b500((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01410_b500(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b500:01E01850, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
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
} Obj_b500_01E01850;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b500_01E01850;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b500_01E01850;

typedef struct {
    f32 u, v;
} Uv_b500_01E01850;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b500_01E01850 uv;
    u64 pad18;
    Xyz_b500_01E01850 v[4];
    u64 pad60[6];
} Pk_b500_01E01850;

typedef struct {
    u64 tag;
    Pk_b500_01E01850 pk;
} Buf_b500_01E01850;

static void func_01E01850_b500(Obj_b500_01E01850 *obj, Def_b500_01E01850 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b500_01E01850 buf;
    Uv_b500_01E01850 uv;
    s16 sel;
    s16 i;
    Pk_b500_01E01850 *p;
    s32 mode;
    s8 *t;
    s32 h;
    f32 f;
    f32 r;
    f32 x;
    f32 y;
    f32 z;
    extern void func_00108EF0();
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
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00150_b500((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        x = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        y = f * (def->scale + h);
        m2[0][0] += x;
        m2[1][0] += x;
        m2[2][0] += x;
        m2[3][0] += x;
        m2[0][1] += y;
        m2[1][1] += y;
        m2[2][1] += y;
        m2[3][1] += y;
        f = t[def->tab + 180];
        f /= 20.0f;
        z = f * (def->scale + h);
        m2[0][2] += z;
        m2[1][2] += z;
        m2[2][2] += z;
        m2[3][2] += z;
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

/* OVL_WARM */

/* shape b500:01E01D60, 262 insns: b383:01E052A0's ring of six camera-facing sprites in an upright circle (y/z, radius
   0x06, 60 apart from the start angle 0x3A) in its own packet: blend 0x48, 0x44 or 0x42 by flags >> 4; mode
   (flags & 0xF) 0 sends at the projected depth, 1 also pins z to the far plane. Calls the module's sprite-UV helper
   (shape b003:01E00080) as a static function. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b500_01E01D60;

typedef struct {
    f32 u, v;
} Uv_b500_01E01D60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b500_01E01D60 uv;
    u64 pad18;
    Xyz_b500_01E01D60 v[4];
    u64 pad60[6];
} Pk_b500_01E01D60;

typedef struct {
    u64 tag;
    Pk_b500_01E01D60 pk;
} Buf_b500_01E01D60;

typedef struct {
    s16 x, y, z;
    s16 rad;
    u8 pad8[8];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    u8 pad30[8];
    s16 size;
    s16 ang;
} Obj_b500_01E01D60;

static void func_01E01D60_b500(u8 *self, Obj_b500_01E01D60 *obj, s32 flags) {
    extern void func_00108EF0();
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    Vec4f pos;
    f32 world[16];
    f32 depth[4];
    s32 rot[4];
    Buf_b500_01E01D60 buf;
    Uv_b500_01E01D60 uv;
    s32 k;
    s32 t;
    s32 sel;
    s16 a;
    f32 r;
    Pk_b500_01E01D60 *p;
    s32 mode;

    a = 0;
    p = (Pk_b500_01E01D60 *)(u32)&buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.uv.v = 0.0f;
    buf.pk.v[0].fog = 0;
    buf.pk.v[1].fog = 0;
    buf.pk.v[2].fog = 0;
    sel = flags >> 4;
    buf.pk.v[3].fog = 0;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, obj->tex);
    p->uv = uv;
    func_01E00150_b500((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)(self + 0x94), *(s16 *)(self + 0xBE));
    func_00208700(p, *(void **)(self + 0x88), 1);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    func_00108EF0(world, 0, &obj->rx, &pos);
    mode = flags & 0xF;
    pos.x = 0.0f;
    for (k = 0; k < 6; k++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        t = obj->ang + a;
        pos.z = obj->rad * func_00108030(self + 0xD8, t, 1);
        pos.y = obj->rad * func_00108030(self + 0xD8, t, 0);
        func_00107070(m, 0, pos.x);
        func_00107070(m, 1, pos.y);
        func_00107070(m, 2, pos.z);
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)p, depth) != 0) {
            if (mode == 0) {
                func_002075F0((s32)p, *(s32 *)(self + 0x80), (u32)depth[0]);
            } else if (mode == 1) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, *(s32 *)(self + 0x80), (u32)depth[0]);
            }
        }
        a += 60;
    }
}

/* shape b500:01E02180, 269 insns: the b500 module's event step (B500_W_S): scene colour (0x80, 0, 0, 0); counts ticks;
   at tick 31 spawns the trail head b500:01E025C0 and b500:01E03910; at ticks 221/268/274/280 (tracked point 0x3BDE)
   and 243/271/277 (0x3BE2) it moves the scene point there and spawns b500:01E02AF0, ten b500:01E02830, seven
   b500:01E02D10, five b500:01E03260 (slot 0) and b500:01E033E0; at 90/121/150/180 (0x3BE4) and 77/105/135/165/193
   (0x3BE6) it spawns twelve b500:01E03260 there (slot 0); from tick 80 to 100 it follows point 0x3BE4 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[4];
    u8 pad260[0x3BB4 - 0x260];
    u8 col[4];
    u8 pad3BB8[0x3BDE - 0x3BB8];
    s16 id1;
    s16 id2;
    s16 id3;
    s16 id4;
    s16 id5;
    u8 pad3BE8[0x3BF6 - 0x3BE8];
    s16 slot;
    u8 pad3BF8[4];
    s16 timer;
} Ctx_b500_01E02180;

static void func_01E02180_b500(Ctx_b500_01E02180 *g) {
    extern s32 b500_01E025C0(void);
    extern s32 b500_01E02830(void);
    extern s32 b500_01E02AF0(void);
    extern s32 b500_01E02D10(void);
    extern s32 b500_01E03260(void);
    extern s32 b500_01E033E0(void);
    extern s32 b500_01E03910(void);
    extern void b500_01E046A0(Ctx_b500_01E02180 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 31) {
        b500_01E046A0(g, b500_01E025C0, 0);
    }
    if (g->timer == 31) {
        b500_01E046A0(g, b500_01E03910, 0);
    }
    if (g->timer == 221 || g->timer == 268 || g->timer == 274 || g->timer == 280) {
        func_001F5620(func_001F53A0(), g->id1, v);
        g->pos[0] = v[0];
        g->pos[1] = v[1];
        g->pos[2] = v[2];
        b500_01E046A0(g, b500_01E02AF0, 0);
        for (i = 0; i < 10; i++) {
            b500_01E046A0(g, b500_01E02830, 0);
        }
        for (i = 0; i < 7; i++) {
            b500_01E046A0(g, b500_01E02D10, 0);
        }
        g->slot = 0;
        for (i = 0; i < 5; i++) {
            b500_01E046A0(g, b500_01E03260, 0);
        }
        b500_01E046A0(g, b500_01E033E0, 0);
    }
    if (g->timer == 243 || g->timer == 271 || g->timer == 277) {
        func_001F5620(func_001F53A0(), g->id3, v);
        g->pos[0] = v[0];
        g->pos[1] = v[1];
        g->pos[2] = v[2];
        b500_01E046A0(g, b500_01E02AF0, 0);
        for (i = 0; i < 10; i++) {
            b500_01E046A0(g, b500_01E02830, 0);
        }
        for (i = 0; i < 7; i++) {
            b500_01E046A0(g, b500_01E02D10, 0);
        }
        g->slot = 0;
        for (i = 0; i < 5; i++) {
            b500_01E046A0(g, b500_01E03260, 0);
        }
        b500_01E046A0(g, b500_01E033E0, 0);
    }
    if (g->timer == 90 || g->timer == 121 || g->timer == 150 || g->timer == 180) {
        g->slot = 0;
        for (i = 0; i < 12; i++) {
            func_001F5620(func_001F53A0(), g->id4, v);
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            b500_01E046A0(g, b500_01E03260, 0);
        }
    }
    if (g->timer == 77 || g->timer == 105 || g->timer == 135 || g->timer == 165 || g->timer == 193) {
        g->slot = 0;
        for (i = 0; i < 12; i++) {
            func_001F5620(func_001F53A0(), g->id5, v);
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            b500_01E046A0(g, b500_01E03260, 0);
        }
    }
    if (g->timer >= 80 && g->timer < 101) {
        func_001F5620(func_001F53A0(), g->id4, v);
        g->pos[0] = v[0];
        g->pos[1] = v[1];
        g->pos[2] = v[2];
        g->pos[0] = v[0];
        g->pos[1] = v[1];
        g->pos[2] = v[2];
        g->slot = 0;
        g->slot = 1;
    }
}

/* shape b500:01E025C0, 155 insns: b501:01E03310 family red (0x40, 0x10, 0x10) four-trail head: on start fills four 9-point trails (ctx+0x3540.. 0xA0 apart) with the four tracked points (ids at ctx+0x3BDC..E2); alpha 0x60 for 190 ticks, then down by 19; every tick pushes each point into its trail (b500:01E00080, 10 steps) */

typedef struct {
    Vec4f pt[9];
    Vec4f head;
} Trail_b500_01E025C0;

typedef struct {
    u8 pad0[0x3540];
    Trail_b500_01E025C0 a;
    Trail_b500_01E025C0 b;
    Trail_b500_01E025C0 c;
    Trail_b500_01E025C0 d;
    u8 pad37C0[0x3BDC - 0x37C0];
    s16 id0;
    s16 id1;
    s16 id2;
    s16 id3;
} Ctx_b500_01E025C0;

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
} Fx_b500_01E025C0;

static s32 func_01E025C0_b500(Ctx_b500_01E025C0 *g, Fx_b500_01E025C0 *o) {
    extern void b500_01E00080(Vec4f *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    Vec4f va;
    Vec4f vb;
    Vec4f vc;
    Vec4f vd;
    Vec4f *p;
    s32 i;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x40, 0x10, 0x10);
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
        p = g->d.pt;
        func_001F5620(func_001F53A0(), g->id3, &vd);
        for (i = 0; i < 9; i++) {
            p[i].x = vd.x;
            p[i].y = vd.y;
            p[i].z = vd.z;
        }
        o->hold = 5;
        o->col[3] = 0;
        o->fA = func_0019A5C8() % 17 + 44;
        o->f8 = func_0019A5C8() % 8 + 5;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f38 = 5;
        o->mode = 2;
    }
    if (o->tick < 190) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    b500_01E00080(&g->a.head, 10, g->id0);
    b500_01E00080(&g->b.head, 10, g->id1);
    b500_01E00080(&g->c.head, 10, g->id2);
    b500_01E00080(&g->d.head, 10, g->id3);
    o->tick++;
    return 0;
}

/* shape b500:01E02830, 108 insns: a spark at a random position: f38 16, variant 0..7, colour set twice (the
   grey one wins), angle 300..349, random direction, spin 10..27, f8 0..9, fC 10, life 2; alpha grows by 0x58 (below
   0xB1) during the life, then fades by 13 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[2];
    s16 fC;
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b500_01E02830;

static s32 func_01E02830_b500(s32 arg0, Spark_b500_01E02830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 16;
        o->kind = func_0019A5C8() % 8;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0xA0, 0xA0, 0x10);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->angle = func_0019A5C8() % 50 + 300;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 18 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->fC = 10;
        o->life = 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xB1) {
            o->col[3] += 0x58;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b148:01E032D0, 65 insns: step of a fading effect (like b258:01E027A0): on state 1 sets its colour, two
   random angles and state 2; full alpha for 7 ticks, then fades by 15; picks a random frame every tick. */

typedef struct {
    u8 pad0[2];
    s16 tick;
    u8 pad4[0x24];
    u8 col[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b148_01E032D0;

static s32 func_01E029E0_b500(void *arg0, Obj_b148_01E032D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->a30 = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->state = 0;
    }
    o->frame = func_0019A5C8() % 8;
    o->tick++;
    o->t++;
    return 0;
}

/* shape b500:01E02AF0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0x80
   for the first 5 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b500_01E02AF0;

static s32 func_01E02AF0_b500(s32 arg0, Flash_b500_01E02AF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x1AE;
        func_001076F0(o->col, 0xC0, 0x30, 0);
        func_001076F0(o->col2, 0x40, 0x10, 0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 5) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b477:01E01E30, 79 insns, 2 copies: a tumbling spark: set up once with a random drift and spin, a random climb rate;
   fades in over 2 frames, then once it has climbed past 20 fades out (b003:01E01780 family) */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 rate;
    u8 padA[6];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b477_01E01E30;

static s32 func_01E02BD0_b500(void *arg0, Obj_b477_01E01E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = -10;
        o->w10 = func_0019A5C8() % 20 - 10;
        o->w14 = func_0019A5C8() % 360;
        o->w18 = 0;
        o->h34 = 0;
        o->state = 2;
        o->rate = func_0019A5C8() % 3 + 4;
        o->h6 = 0x14;
        func_001076F0(o->c0, 0x80, 0x20, 0x20);
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->h38 > 0x14) {
        if (o->c0[3] > 0x14) {
            o->c0[3] -= 0x13;
        } else {
            o->state = 0;
        }
    }
    if (o->t != 0) {
        o->h38 += o->rate;
    }
    o->t++;
    return 0;
}

/* shape b500:01E02D10, 93 insns: b046:01E02170 twin: a white spark (size 20, random frame 0..7, random roll and angle) spinning a random 20..59 a tick, size 0..9, held 2..10 ticks at 0x80, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
} Glow_b500_01E02D10;

static s32 func_01E02D10_b500(s32 arg0, Glow_b500_01E02D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->w18 = 0;
        o->w18 = func_0019A5C8() % 360;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 40 + 20;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 9 + 2;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b052:01E023C0, 97 insns, 3 copies: step of a drifting ember: on state 1 picks random seeds, angle, speed and
   lifetime and an orange colour; full alpha while young, then fades by 15 until it ends; drifts by its speed. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b052_01E023C0;

static s32 func_01E02E90_b500(void *arg0, Obj_b052_01E023C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 2;
        o->h34 = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->t++;
    return 0;
}

/* shape b500:01E03020, 141 insns: b555:01E02830's glow that, once past its hold, sits on scene joint 0x3BE8 pushed 3 sideways by the scene side flag */

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b500_01E03020;

typedef struct {
    u8 pad0[0x3BE8];
    s16 joint;
    u8 pad3BEA[0xE];
    s16 side;
} Scene_b500_01E03020;

static s32 func_01E03020_b500(Scene_b500_01E03020 *g, Glow_b500_01E03020 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f v;

    if (o->mode == 1) {
        o->f38 = 3;
        o->kind = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->h30 = 0;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 3;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick > o->h6) {
        func_001F5620(func_001F53A0(), g->joint, &v);
        o->x = func_001A22C0(v.x);
        o->y = func_001A22C0(v.y);
        o->z = func_001A22C0(v.z);
        if (g->side != 0) {
            o->z -= 3;
        } else {
            o->z += 3;
        }
    }
    if (o->tick != 0) {
        if (o->f38 < 20) {
            o->f38++;
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
    o->tick++;
    return 0;
}

/* shape b500:01E03260, 96 insns: b115:01E01980 family: a pink spark (size 60, frame 5); flagged ones get a random tilt and drift 10 a tick along their angle (sine table ctx+0x4100), unflagged ones stay put: alpha 0x80 for 7 ticks, then out by 15 and ends */

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
} Glow_b500_01E03260;

typedef struct {
    u8 pad[0x4100];
    u8 sin[1];
} Game_b500_01E03260;

static s32 func_01E03260_b500(Game_b500_01E03260 *g, Glow_b500_01E03260 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = 5;
        func_001076F0(o->col, 0x80, 0x60, 0x60);
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

/* shape b500:01E033E0, 71 insns: reads the model angle (func_001F6160); on start 0x38 = 10, random 0x3A, step 2,
   colour 0x80 grey; alpha 0x80 on the first tick, then fades by 0x12 and stops; 0x34 counts up to 7 and 0x6 grows by
   the step after the first tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 step;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b500_01E033E0;

static s32 func_01E033E0_b500(s32 arg0, Fx_b500_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    func_001F6160(func_001F53A0(), ang);
    if (o->mode == 1) {
        o->f38 = 10;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->step = 2;
        o->f6 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->tick <= 0) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 0x13) {
        o->col[3] -= 0x12;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f6 += o->step;
    }
    o->tick++;
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b500_01E03500;

typedef struct {
    u8 pad0000[0x3BDC];
    s16 joints[1];
} Mgr_b500_01E03500;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 pad0C[2];
    s16 hE;
    u8 pad10[8];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b500_01E03500;

static s32 func_01E03500_b500(Mgr_b500_01E03500 *m, Obj_b500_01E03500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec_b500_01E03500 v;

    if (o->h36 == 1) {
        o->h38 = 14;
        o->h34 = 1;
        o->w18 = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->hA = o->h30;
        o->h30 = func_0019A5C8() % 100;
        o->h3A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 30 + 140;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 2 + 3;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->h36 = 0;
    }
    if (o->h32 != 0) {
        o->h30 += o->hE;
    }
    o->h32++;
    func_001F5620(func_001F53A0(), m->joints[o->hA], &v);
    o->x = v.x;
    o->y = v.y;
    o->z = v.z;
    return 0;
}

/* shape b500:01E036D0, 92 insns: b582:01E03470 family scene light at ctx+0x34F0 (orange 4/2/0, range 128, height 120): raised by 0.2 to 1, lowered by 0.1 and ended; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b500_01E036D0;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x694];
    s32 state;
} Light_b500_01E036D0;

typedef struct {
    u8 pad[0x34f0];
    Light_b500_01E036D0 l;
} Game_b500_01E036D0;

static s32 func_01E036D0_b500(Game_b500_01E036D0 *g, Obj_b500_01E036D0 *o) {
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

/* shape b500:01E03850, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3BB0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3BB0];
    s32 state;
} Game_b500_01E03850;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b500_01E03850;

static s32 func_01E03850_b500(Game_b500_01E03850 *g, Fade_b500_01E03850 *o) {
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

/* shape b119:01E041C0, 31 insns: calls func_001F7170(2, 0, &a, &b, 0) with the module's two floats, stops the
   effect after 10 ticks */

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b119_01E041C0;

typedef struct {
    f32 v;
} F1_b119_01E041C0;

extern F1_b119_01E041C0 D_01E05100_b500;
extern F1_b119_01E041C0 D_01E05108_b500;

static s32 func_01E03910_b500(s32 arg0, Fx_b119_01E041C0 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b119_01E041C0 a;
    F1_b119_01E041C0 b;

    a = D_01E05100_b500;
    b = D_01E05108_b500;
    func_001F7170(2, 0, &a, &b, 0);
    if (o->tick >= 10) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b500:01E03990, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-3 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x38A0];
    s32 tex5[4];
} Scene_b500_01E03990;

static void func_01E03990_b500(s32 arg0, Scene_b500_01E03990 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 4; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b500", func_01E03A40_b500);

/* shape b500:01E046A0, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3BF6 and the two arguments; returns 1 if a
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
} Slot_b500_01E046A0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b500_01E046A0 s[200];
    u8 pad34F0[0x6C4];
    u8 r, g, b, a;
    u8 pad3BB8[0x3E];
    s16 v;
} Pool_b500_01E046A0;

static s32 func_01E046A0_b500(Pool_b500_01E046A0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b500_01E046A0 *s = NULL;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b500:01E047C0 (B500PAINT_RAIN13), 347 insns, 1 copy: b501:01E047C0's ribbon (4 spline quads per segment
   between two trails) with the far-edge alpha ramping up by alpha / (2n) per quad for the first half, then down */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b500_01E047C0;

typedef struct {
    Rgbaq_b500_01E047C0 c;
    u64 xyz;
} Vtx_b500_01E047C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b500_01E047C0 v[4];
    u8 tail[0x40];
} Pkt_b500_01E047C0;

typedef struct {
    u8 r, g, b, a;
} C4_b500_01E047C0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b500_01E047C0 col;
} Rib_b500_01E047C0;

static void func_01E047C0_b500(void *o, Rib_b500_01E047C0 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b500_01E047C0 func_00107740(void *);
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
    Pkt_b500_01E047C0 pkt __attribute__((aligned(8)));
    C4_b500_01E047C0 col;
    s32 k;
    s32 j;
    s16 n;
    s16 d;
    s32 ot __attribute__((aligned(8)));
    Pkt_b500_01E047C0 *p;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b500_01E047C0 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = s->col;
    col.a = 0;
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
        for (j = 0; j < 4; j++) {
            p->v[0].c = func_00107740(&col);
            p->v[2].c = func_00107740(&col);
            d = s->col.a / (n * 2);
            if (k * 4 + j < (n * 4) >> 1) {
                if (col.a + d < 0xFF) {
                    col.a = col.a + d;
                } else {
                    col.a = 0xFF;
                }
            } else {
                if (col.a - d > 0) {
                    col.a = col.a - d;
                } else {
                    col.a = 0;
                }
            }
            p->v[1].c = func_00107740(&col);
            p->v[3].c = func_00107740(&col);
            if (k != 0) {
                A[0] = func_01E01410_b500(pa + (k - 1), 0, t);
                B[0] = func_01E01410_b500(pb + (k - 1), 0, t);
                t += 0.25f;
                A[1] = func_01E01410_b500(pa + (k - 1), 0, t);
                B[1] = func_01E01410_b500(pb + (k - 1), 0, t);
            } else {
                A[0] = func_01E01410_b500(a4, 0, t);
                B[0] = func_01E01410_b500(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01410_b500(a4, 0, t);
                B[1] = func_01E01410_b500(b4, 0, t);
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

/* shape b225:01E04BF0, 220 insns, 3 copies: draws a row of thin bars (count of them) at the sprite's position into the
   caller's packet: each shaken by a per-entry table offset that grows along the row, turned by the sprite's
   rotation, its far edge pinned at +-w; two colours top/bottom. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b225_01E04BF0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b225_01E04BF0 c;
        u64 uv;
        u64 xyz;
    } v[4];
} Pkt_b225_01E04BF0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b225_01E04BF0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[2];
    s16 w;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b225_01E04BF0;

static void func_01E04D30_b500(Obj_b225_01E04BF0 *o, Spr_b225_01E04BF0 *s, Pkt_b225_01E04BF0 *p, s8 *tbl) {
    extern Rgbaq_b225_01E04BF0 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    s32 rot[4];
    f32 depth[4];
    s16 i;
    s32 h;
    s8 *j;
    f32 f;
    f32 w;
    f32 nw;

    func_00207500();
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(s->col1);
    p->v[1].c = func_00107740(s->col1);
    p->v[2].c = func_00107740(s->col0);
    p->v[3].c = func_00107740(s->col0);
    func_00108500(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, rot, &pos);
    w = s->w;
    nw = -w;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 10.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 10.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 10.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        func_00109100(quad, s->rot, 2, o->xD8);
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        quad[2].x = w;
        quad[3].x = nw;
        quad[2].z = 0.0f;
        quad[3].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}
