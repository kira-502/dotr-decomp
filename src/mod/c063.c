#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_c063(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
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

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00110_c063(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

extern void c063_01E00110(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00560_c063(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    c063_01E00110(p, o->b94, o->hC0);
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

/* shape c063:01E00AD0, 207 insns: b094:01E00920's ring band with the quads starting at angle j (no base angle):
   edges at j and j + width, j stepping by the step field */

typedef struct {
    f32 x, y, z, w;
} Vec_c063_01E00AD0;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_c063_01E00AD0;

typedef struct {
    u8 pad00[0x20];
    Vec_c063_01E00AD0 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_c063_01E00AD0;

static void func_01E00AD0_c063(Obj_c063_01E00AD0 *obj, Data_c063_01E00AD0 *data, s32 flags, Vec_c063_01E00AD0 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_c063_01E00AD0 c;
    Vec_c063_01E00AD0 quad[4];
    Vec_c063_01E00AD0 pos;
    Vec_c063_01E00AD0 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
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
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = width + j;
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
    }
}

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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_c063 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E00E10_c063(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_c063((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E010D0_c063(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
    }
}

/* shape c061:01E01100 (IWMagicCircleGT4_4), 249 insns, 2 copies: draws an arc band of count textured quads
   (b108:01E00DF0 family): outer and inner radius, each quad spanning the band's span, stepping by its step; gouraud
   from the two colours, texture window from the object; blend from flags >> 4, depth mode flags & 0xF (projected, or
   far after a packet tweak) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c061_01E01100;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_c061_01E01100 c;
        u64 st;
        u64 xyz;
    } v[4];
    u8 tail[0x20];
} Pkt_c061_01E01100;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_c061_01E01100;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 outer;
    f32 inner;
    u8 pad50[0xA];
    s16 step;
    s16 spn;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Band_c061_01E01100;

static void func_01E012A0_c063(s32 arg0, s32 arg1, s32 flags, Vec4f pos) {
    extern Rgbaq_c061_01E01100 func_00107740(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Band_c061_01E01100 *s = (Band_c061_01E01100 *)arg1;
    Obj_c061_01E01100 *o = (Obj_c061_01E01100 *)arg0;
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    Pkt_c061_01E01100 pkt;
    s32 k;
    s16 b;
    s16 span;
    s16 a;
    Pkt_c061_01E01100 *p;
    s32 t;
    f32 ro;
    f32 ri;

    p = &pkt;
    span = s->spn;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    b = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col0, 0);
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p->v[0].c = func_00107740(s->col0);
    p->v[2].c = func_00107740(s->col1);
    p->v[1].c = func_00107740(s->col0);
    p->v[3].c = func_00107740(s->col1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    scale.z = 0.1f;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < o->count; k++) {
        t = a;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = span + a;
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if ((flags & 0xF) == 1 && func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_00109380(p, 1);
            func_002075F0(p, o->ot, 0);
        }
        a += s->step;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E01690_c063);

/* shape c063:01E02340, 190 insns: c061:01E02660's mote, grey 0x80 dimming to 0x30 at tick 33, size 480, frame 0..7,
   angles 0..359, 0x50 50..399, drift -20..19 unscaled; while the scene count (ctx+0x6C3A) is under 500 alpha goes up
   by 0x80 for 53 ticks then down by 9, after that down by 9; rises 6 a tick with its z pinned to the scene's 0x5A98
   plus its drift */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    f32 z;
    u8 pad1C[0x14];
    f32 vel[3];
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 life;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_c063_01E02340;

typedef struct {
    u8 pad0[0x5A98];
    f32 z;
    u8 pad5A9C[0x6C3A - 0x5A9C];
    s16 count;
} Ctx_c063_01E02340;

static s32 func_01E02340_c063(Ctx_c063_01E02340 *g, Fx_c063_01E02340 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 480.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->side = 2;
        } else {
            o->side = 0;
        }
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 350 + 50;
        o->life = func_0019A5C8() % 350 + 100;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->mode = 2;
    }
    if (o->tick == 33) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    }
    if (g->count < 500) {
        if (o->tick < 53) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x80;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->y += 6.0f;
    }
    o->z = g->z + o->vel[2];
    o->tick++;
    return 0;
}

/* shape c063:01E02640, 224 insns: b721:01E020D0 cousin with five kinds (size 10..30 by 5, hold 70..30 by 10), alpha
   steps of 9 and 5; the scene flag at 0x6C36. As b721:01E020D0: a grey (0x50/0x60 flicker) glow pair by kind 0..2: size 14/20/26 with the inner part
   6 smaller, frame 0..6, h8 4..6, hold 55/45/35 ticks fading in by 12 to 0x8C, then out by 9 while growing by 1.5 a tick;
   for its first 10 ticks the angle word 0x24 is 0 or 0x8000 by the scene flag 0x9864, then it turns by 0x80 one way
   or the other by the kind's parity */

typedef struct {
    u8 pad0[0x6C36];
    s16 flag;
} Game_c063_01E02640;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[0x1A];
    s32 w24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    s16 frame;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_c063_01E02640;

static s32 func_01E02640_c063(Game_c063_01E02640 *g, Fx_c063_01E02640 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 10.0f;
            o->f4C = o->f48 - 5.0f;
        } else if (o->kind == 1) {
            o->f48 = 15.0f;
            o->f4C = o->f48 - 5.0f;
        } else if (o->kind == 2) {
            o->f48 = 20.0f;
            o->f4C = o->f48 - 5.0f;
        } else if (o->kind == 3) {
            o->f48 = 25.0f;
            o->f4C = o->f48 - 5.0f;
        } else if (o->kind == 4) {
            o->f48 = 30.0f;
            o->f4C = o->f48 - 5.0f;
        }
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        if (o->kind == 0) {
            o->hold = 70;
        }
        if (o->kind == 1) {
            o->hold = 60;
        }
        if (o->kind == 2) {
            o->hold = 50;
        }
        if (o->kind == 3) {
            o->hold = 40;
        }
        if (o->kind == 4) {
            o->hold = 30;
        }
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 9;
        }
    } else {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 6) {
            o->col2[3] -= 5;
        }
        o->f48 += 1.5f;
        o->f4C = o->f48 - 6.0f;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        func_001076F0(o->col2, 0x50, 0x50, 0x50);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x60, 0x60, 0x60);
    }
    if (o->tick < 10) {
        if (g->flag != 0) {
            o->w24 = 0;
        } else {
            o->w24 = 0x8000;
        }
    } else if (o->kind % 2 == 1) {
        o->w24 += 0x80;
    } else {
        o->w24 -= 0x80;
    }
    o->tick++;
    return 0;
}

/* shape c063:01E029C0, 206 insns: c061:01E02030's flake, yellow (0xFF, 0xFF, 0x40) on odd scene counts (ctx+0x6C3A)
   and orange (0xFF, 0x80, 0x40) on even ones */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_c063_01E029C0;

typedef struct {
    u8 pad0[0x6C3A];
    s16 count;
} Ctx_c063_01E029C0;

static s32 func_01E029C0_c063(Ctx_c063_01E029C0 *g, Fx_c063_01E029C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 200;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        if (g->count % 2 == 1) {
            func_001076F0(o->col, 0xFF, 0xFF, 0x40);
        } else {
            func_001076F0(o->col, 0xFF, 0x80, 0x40);
        }
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->hold = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 300) {
            o->w += 5;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        o->pos[1] -= 1.5f;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape c063:01E02D00, 61 insns: a white spinning flash (b236:01E01B70 family): scale 300, frame count 0x109, size 10x10;
   alpha up by 13 to 0xA0 for that many frames, then down by 12 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c063_01E02D00;

static s32 func_01E02D00_c063(void *arg0, Obj_c063_01E02D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 300.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->hold = 0x109;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0xD;
        }
    } else if (o->c0[3] > 0xD) {
        o->c0[3] -= 0xC;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape c063:01E02E00, 78 insns: on start 0x8/0xA = 0x12C, random flip 0x56, both colours 0x80 grey (second alpha 0);
   both alphas grow by 0x13 (below 0xC0) for 0x108 ticks, then fade by 14 (the first ends it); 0x56 toggles each tick;
   func_00205C40 on the rotation at 0x20 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 flip;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_c063_01E02E00;

static s32 func_01E02E00_c063(s32 arg0, Fx_c063_01E02E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 0x12C;
        o->fA = 0x12C;
        o->flip = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x109) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x13;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x13;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->flip != 0) {
        o->flip = 0;
    } else {
        o->flip = 1;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape c063:01E02F40, 165 insns: b479:01E01EB0 variant: size 50, grey 0x60, frame 0..7, a random parity flag (hA 0 or 2),
   height 70..169, life 100..449, rise 5..14, a random drift of +-20 in each axis, alpha up by 0xC0 for its fade-in, and
   a turn of 3 a tick */

typedef struct {
    u8 pad0000[0x6DEC];
    s16 h6DEC;
} Mgr_c063_01E02F40;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 v10[0x20];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_c063_01E02F40;

static s32 func_01E02F40_c063(Mgr_c063_01E02F40 *m, Obj_c063_01E02F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 50.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->c60, 0x60, 0x60, 0x60);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = (func_0019A5C8() >> 4) % 100 + 70;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 10 + 5;
        o->h8 = (func_0019A5C8() >> 4) % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0xC0;
        }
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h5A += 3;
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape c063:01E031E0, 148 insns: b081:01E03490 family ring with float sizes (f48 from 0 growing 30 per tick, f4C half of it): blue on grey or yellow on black for kind 2, size 30; outer alpha up by 12 to 0x80 for 18 (kind 2: 30) ticks, then down by 9 (kind 2: 7) */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 hold;
    u8 padA[4];
    s16 fE;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_c063_01E031E0;

static s32 func_01E031E0_c063(s32 arg0, Fx_c063_01E031E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (o->kind != 2) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        } else {
            func_001076F0(o->col, 0x80, 0x80, 0x10);
            func_001076F0(o->col2, 0x10, 0x10, 8);
        }
        o->fE = o->kind;
        if (o->kind == 0 || o->kind == 2) {
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
        } else {
            o->rot[0] = 0x4000;
            o->rot[1] = 0;
            o->rot[2] = 0;
        }
        o->w = 30;
        o->h = 30;
        o->mode = 2;
        o->col[3] = 0;
        o->h6 = 0;
        if (o->kind != 2) {
            o->hold = 18;
        } else {
            o->hold = 30;
        }
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (o->kind != 2) {
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->mode = 0;
        }
    } else if (o->col2[3] > 8) {
        o->col2[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->fE != 2) {
        o->f4C = o->f48 - 0.5f * o->f48;
    }
    if (o->h6 < 0) {
        o->f4C = 0.0f;
    }
    if (o->tick != 0) {
        o->f48 += 30.0f;
    }
    o->tick++;
    return 0;
}

/* shape c063:01E03430, 106 insns: a white-yellow expanding flash (b283:01E03260 shape): size 20 growing by 55 with the inner size a
   fifth of it, random turn, sub-frame 4; alpha up by 0x40 for 7 frames, then down by 8 until it ends; second colour flickers */

typedef struct {
    u8 pad0[1];
} Game_c063_01E03430;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c063_01E03430;

static s32 func_01E03430_c063(Game_c063_01E03430 *g, Obj_c063_01E03430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 20.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->kind = 0;
        o->h5A = 0x3C;
        o->h5C = 3;
        o->sub = 4;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xA0, 0xA0, 0x60);
    } else {
        func_001076F0(o->c1, 0xC0, 0xC0, 0x60);
    }
    o->f48 += 55.0f;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

/* shape c063:01E035E0, 337 insns: a spiralling streak (B737_OBJ_MOVE_10_): set up once at size 100, grey, height 30,
   radius 100 on its angle (sine table ctx+0x6E3C), its 13-point trail (ctx+0x5AB0, slot 0x50) filled; fades in by 19
   to 0xC0 before tick 300, then out by 14; rises 6 a tick (5 up to ctx+0x5A84 after scene tick 626) while the
   radius shrinks 2.6 to 0 (then jumps to tick 400) and the angle turns 20 (slots 0..7) or 10 a tick, sign by slot;
   follows the player (0x6C36 picks the 85 offset side); sparks c063:01E02F40 / c063:01E029C0 on odd ticks by slot;
   flashes 0xC0 / 0xFF; pushes its point into the trail */

typedef struct {
    Vec4f v[13];
} Trail_c063_01E035E0;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x5A84 - 0x260];
    f32 top;
    u8 pad5A88[0x5AB0 - 0x5A88];
    Trail_c063_01E035E0 trail[20];
    u8 pad6AF0[0x6C36 - 0x6AF0];
    s16 h6C36;
    u8 pad6C38[2];
    s16 h6C3A;
    u8 pad6C3C[0x6E3C - 0x6C3C];
    u8 sin[4];
} Ctx_c063_01E035E0;

typedef struct {
    u8 pad0[6];
    s16 len;
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 r;
    s16 idx;
    u8 pad52[2];
    s16 t;
    s16 flip;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Streak_c063_01E035E0;

static s32 func_01E035E0_c063(Ctx_c063_01E035E0 *g, Streak_c063_01E035E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(s32, s32, s32);
    extern void func_001F1FD0(s32, void *);
    extern void func_01E00080_c063();
    extern void c063_01E05750();
    extern s32 func_01E029C0_c063();
    extern s32 func_01E02F40_c063();
    Vec4f v;
    Vec4f *p;
    s16 i;

    if (o->state == 1) {
        o->w = 100;
        o->h = 100;
        o->flip = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->state = 2;
        o->col2[3] = 0;
        o->f48 = 13.0f;
        o->r = 100.0f;
        o->pos.y = 30.0f;
        o->pos.z = o->r * func_00108030((s32)g->sin, o->ang, 0);
        o->pos.x = o->r * func_00108030((s32)g->sin, o->ang, 1);
        p = g->trail[o->idx].v;
        for (i = 0; i < 13; i++) {
            p[i].x = o->pos.x;
            p[i].y = o->pos.y;
            p[i].z = o->pos.z;
        }
    }
    if (o->t < 300) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 19;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 19;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->state = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->flip != 0) {
        o->flip = 0;
    } else {
        o->flip = 1;
    }
    if (o->t != 0) {
        if (g->h6C3A > 625) {
            if (g->top > o->pos.y) {
                o->pos.y += 5.0f;
            }
        } else {
            o->pos.y += 6.0f;
        }
        o->pos.z = o->r * func_00108030((s32)g->sin, o->ang, 0);
        o->pos.x = o->r * func_00108030((s32)g->sin, o->ang, 1);
        if (o->r > 0.0f) {
            o->r -= 2.6f;
        } else {
            o->t = 400;
        }
        if (o->idx < 8) {
            if (o->idx % 2 != 0) {
                o->ang += 20;
            } else {
                o->ang -= 20;
            }
        } else {
            if (o->idx % 2 != 0) {
                o->ang += 10;
            } else {
                o->ang -= 10;
            }
        }
    }
    func_001F1FD0(32, &v);
    if (g->h6C36 != 0) {
        o->pos.z += v.z - 85.0f;
    } else {
        o->pos.z += 85.0f + v.z;
    }
    o->pos.x += v.x;
    if (o->t < 300) {
        g->pos = o->pos;
        if (o->t % 2 == 1) {
            if (o->idx % 2 == 1 && o->t > 5) {
                c063_01E05750(g, func_01E02F40_c063, 0);
            }
            if (o->idx % 2 == 0 && o->t > 5) {
                c063_01E05750(g, func_01E029C0_c063, 0);
            }
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    }
    func_01E00080_c063(&g->trail[o->idx].v[12], 13, 0, &o->pos);
    func_00205C40((s32)o->rot);
    if (o->t != 0 && o->len < 12) {
        o->len++;
    }
    o->t++;
    return 0;
}

/* shape c063:01E03B30, 157 insns: a flash ring's step, kind 0 or 1 (0x50): on start (state 1) it sets the colours
   (0x80 grey or 0xC0 grey over 0x20), copies the kind to 0x0E, takes the camera turn plus 0x4000 and radius 800 or
   1000, sets 0x5A/0x5C to 20, alpha 0 and an 8-frame rise; while rising the alpha grows by 0x2A to 0x80 (or 0x40 to
   0xC0), then fades by 9 (or 15) until it ends; after the first frame the radius grows by 70 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 rise;
    u8 padA[4];
    s16 kind2;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Ring_c063_01E03B30;

static s32 func_01E03B30_c063(void *g, Ring_c063_01E03B30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->r = 0.0f;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0x20, 0x20, 0x20);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0x20, 0x20, 0x20);
        }
        o->kind2 = o->kind;
        if (o->kind == 0) {
            func_00205C40((s32)o->rot);
            o->rot[0] += 0x4000;
            o->r = 800.0f;
        }
        if (o->kind == 1) {
            func_00205C40((s32)o->rot);
            o->rot[0] += 0x4000;
            o->r = 1000.0f;
        }
        o->h5A = 20;
        o->h5C = 20;
        o->state = 2;
        o->col[3] = 0;
        o->h6 = 0;
        if (o->kind == 0) {
            o->rise = 8;
        }
        if (o->kind == 1) {
            o->rise = 8;
        }
    }
    if (o->t < o->rise) {
        if (o->kind == 0) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x2A;
            }
        }
        if (o->kind == 1) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x40;
            }
        }
    } else {
        if (o->kind == 0) {
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            } else {
                o->state = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col[3] > 16) {
                o->col[3] -= 15;
            } else {
                o->state = 0;
            }
        }
    }
    if (o->kind == 0 && o->t != 0) {
        o->r += 70.0f;
    }
    if (o->kind == 1 && o->t != 0) {
        o->r += 70.0f;
    }
    o->t++;
    return 0;
}

/* shape c063:01E03DB0, 88 insns: a yellow tumbling spark: random turn on all three axes, scale from the scene, angle 90 climbing
   by 0..6 a frame until 270 (then it ends); alpha up by 0x80 for 8 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x5A64];
    f32 scale;
} Scene_c063_01E03DB0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 scale;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_c063_01E03DB0;

static s32 func_01E03DB0_c063(Scene_c063_01E03DB0 *g, Obj_c063_01E03DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h56 = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0x40);
        o->ang = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
        o->scale = g->scale;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x80;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->ang < 0x10E) {
        o->ang += (s16)(func_0019A5C8() % 7);
    } else {
        o->state = 0;
    }
    return 0;
}

/* shape c063:01E03F10, 207 insns: c063:01E03430's flash in two kinds (0x50): kind 0 blue-white (0x80, 0x80, 0xFF), size 20
   growing by 80 with the inner size a fifth, spinning on all axes, alpha up for 15 ticks; kind 1 white, size 3000
   shrinking by 250 with the inner size half, alpha up for 7 ticks; second colour flickers (grey-yellow / blue) */

typedef struct {
    u8 pad0[1];
} Game_c063_01E03F10;

typedef struct {
    s16 spin[3];
    s16 h6;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c063_01E03F10;

static s32 func_01E03F10_c063(Game_c063_01E03F10 *g, Obj_c063_01E03F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 20.0f;
            o->f4C = 0.0f;
            func_001076F0(o->c0, 0x80, 0x80, 0xFF);
            o->h5A = 0x3C;
            o->h5C = 3;
            o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
            o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
            o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
            o->h6 = 15;
        }
        if (o->kind == 1) {
            o->f48 = 3000.0f;
            o->f4C = 0.0f;
            func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
            o->h5A = 0x3C;
            o->h5C = 2;
            o->sub = 3;
            o->h6 = 7;
        }
        o->sub = 4;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < o->h6) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0xA0, 0xA0, 0x60);
        } else {
            func_001076F0(o->c1, 0xC0, 0xC0, 0x60);
        }
        o->f48 += 80.0f;
        o->f4C = 0.2f * o->f48;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
    }
    if (o->kind == 1) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0x60, 0x60, 0xA0);
        } else {
            func_001076F0(o->c1, 0x60, 0x60, 0xC0);
        }
        o->f48 -= 250.0f;
        o->f4C = 0.5f * o->f48;
    }
    o->t++;
    return 0;
}

/* shape c063:01E04250, 175 insns: b588:01E01300 family grey (0x40) flake 400 x 1600, frame cycling 0..7 from 0..2, held 10 ticks, sinking 1.5 a tick and spinning only on y */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_c063_01E04250;

static s32 func_01E04250_c063(s32 arg0, Fx_c063_01E04250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 400;
        o->h = o->w * 4;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->hold = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind < 7) {
        o->kind++;
    } else {
        o->kind = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        o->pos[1] -= 1.5f;
    }
    o->rot[1] += o->spin[1];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape c063:01E04510, 115 insns: glow pair in one of three colour/life presets, fading in and out */

typedef struct Glow_c063_01E04510 {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 age;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_c063_01E04510;

static s32 func_01E04510_c063(s32 arg0, Glow_c063_01E04510 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        if (o->kind == 0) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0xF0, 0xF0, 0xF0);
            o->life = 20;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0xD0, 0xD0, 0x80);
            func_001076F0(o->c1, 0xC0, 0xC0, 0x80);
            o->life = 20;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0xF0, 0xE0, 0xFF);
            func_001076F0(o->c1, 0xF0, 0xE0, 0xFF);
            o->life = 30;
        }
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->kind != 2) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 7;
            }
            if (o->c1[3] < 0x80) {
                o->c1[3] += 7;
            }
        } else {
            if (o->c0[3] < 0xC0) {
                o->c0[3] += 0xC;
            }
            if (o->c1[3] < 0xC0) {
                o->c1[3] += 0xC;
            }
        }
    } else {
        if (o->c0[3] > 5) {
            o->c0[3] -= 4;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 5) {
            o->c1[3] -= 4;
        } else {
            o->c1[3] = 0;
        }
    }
    o->age++;
    return 0;
}

/* shape c063:01E046E0, 48 insns: b718:01E03D10 family: volume eased by 10 toward 0x30 once the scene state passes 30, else toward 0x80; counts its tick */

typedef struct {
    u8 pad[0x6B30];
    s32 state;
} Game_c063_01E046E0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_c063_01E046E0;

static s32 func_01E046E0_c063(Game_c063_01E046E0 *g, Fade_c063_01E046E0 *o) {
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
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->t++;
    func_001F6D00((u8)o->vol);
    return 0;
}

/* shape c063:01E047A0, 198 insns: b745:01E03700's veil in pale red (0x80/0x78/0x78) with zoom 0, recoloured on scene
   counts 504, 625, 635 and 715 and zoomed to 3 on 735; alpha up by 11 to 0x48 while ctx+0x6B30 is over 20, then
   down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c063_01E047A0;

typedef struct {
    f32 s, t;
    Xyz_c063_01E047A0 p;
} Tv_c063_01E047A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_c063_01E047A0 v[2];
    u8 tail[0x20];
} Tex_c063_01E047A0;

typedef struct {
    u8 pad0[0x6B30];
    s32 timer;
    u8 pad6B34[0x106];
    s16 count;
} Ctx_c063_01E047A0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_c063_01E047A0;

static s32 func_01E047A0_c063(Ctx_c063_01E047A0 *g, Fx_c063_01E047A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_c063_01E047A0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x80, 0x78, 0x78);
        o->mode = 2;
    }
    if (g->count == 504) {
        func_001076F0(o->col, 0xB8, 0x80, 0x80);
    }
    if (g->count == 625) {
        func_001076F0(o->col, 0x90, 0x90, 0x90);
    }
    if (g->count == 635) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (g->count == 715) {
        func_001076F0(o->col, 0xB8, 0x80, 0xC8);
    }
    if (g->count == 735) {
        o->f48 = 3.0f;
    }
    ((Tex_c063_01E047A0 *)(s32)&pk)->flags = 0x26;
    ((Tex_c063_01E047A0 *)(s32)&pk)->size = 5;
    ((Tex_c063_01E047A0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_c063_01E047A0 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    if (g->count < 625) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else if (g->count >= 625 && g->count < 636) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    }
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->timer > 20) {
        if (o->col[3] < 0x48) {
            o->col[3] += 11;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c063", func_01E04AC0_c063);

/* shape c063:01E05750, 60 insns: take a free slot (0xC8 of 0x70 bytes at 0x2A0), clear it, copy the object's
   position (0x250), 0x5A and 0x50 from the object (0x6C26, 0x6C32), store arg; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x28];
    s32 arg;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    s16 f5A;
    u8 pad5C[0x14];
} Slot_c063_01E05750;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_c063_01E05750 slots[0xC8];
    u8 pad5A20[0x6C26 - 0x5A20];
    s16 f6C26;
    u8 pad6C28[0xA];
    s16 f6C32;
} Obj_c063_01E05750;

static s32 func_01E05750_c063(Obj_c063_01E05750 *obj, s32 arg) {
    extern void func_00195108();
    Slot_c063_01E05750 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xC8;
        }
    }
    if (s != NULL) {
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f5A = obj->f6C26;
        s->f50 = obj->f6C32;
        s->arg = arg;
        return 1;
    }
    return 0;
}

/* shape c063:01E05840, 194 insns: b108:01E03130 cousin (scaled 10x, angles a - 200, scene tables at 0x6BE8/0x6B98/0x6E3C); b756:01E061D0 family burst draw: two-colour packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles o->ang + 20 i - 200 between radii f4C and f48, each with its frame from the scene table through func_00106080 into the rect, depth-tested into the scene ot */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_c063_01E05840;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x6B98 - 0xC0];
    s32 ot;
    u8 pad6B9C[0x6BE8 - 0x6B9C];
    s16 frames[18];
    u8 pad6C0C[0x6E3C - 0x6C0C];
    u8 trig[1];
} Game_c063_01E05840;

static void func_01E05840_c063(Game_c063_01E05840 *g, Obj_c063_01E05840 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 sc[4];
    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 a;
    void *p = &buf;
    s16 s;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;
    s32 t;

    *(Vec4f *)pos = *in;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    sc[0] = sc[1] = sc[2] = 10.0f;
    func_00108EF0(m, sc, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    for (i = 0; i < 18; i++) {
        func_00106080(rm, 0x14, g->frames[i], 0);
        g->rect = *(Vec4f *)rm;
        func_00108500(p, &g->rect, g->frame);
        s = o->ang + a - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        t = o->ang + 20;
        s = a + t - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        a += 20;
    }
}

/* shape c061:01E03D80 (B855PAINT_RAIN12), 697 insns, 2 copies: b411:01E036C0's beam along the module spline with no
   rotation, alpha down by col0.a/(2n), width down by w0/(2.5n), flags 0/1 pick the depth (computed / max) */

typedef struct {
    f32 x, y, z, w;
} Vec_c061_01E03D80;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c061_01E03D80;

typedef struct {
    u8 r, g, b, a;
} Col_c061_01E03D80;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c061_01E03D80;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_c061_01E03D80 c;
        u64 st;
        Xyz_c061_01E03D80 p;
    } v[4];
    u8 tail[0x20];
} Pkt_c061_01E03D80;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_c061_01E03D80;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[6];
    s16 start;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 width;
    u8 pad4C[0x14];
    Col_c061_01E03D80 col0;
    Col_c061_01E03D80 col1;
} Beam_c061_01E03D80;

static inline Vec_c061_01E03D80 spline_b847_01E00E60(Vec_c061_01E03D80 *p, s32 type, f32 t) {
    Vec_c061_01E03D80 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

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

/* pts aligned: its spill slot, needed for the match */

static void func_01E05B50_c063(Ctx_c061_01E03D80 *c, Beam_c061_01E03D80 *an, Vec_c061_01E03D80 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_c061_01E03D80 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_c061_01E03D80 ab[2];
    Vec_c061_01E03D80 ctrl[4];
    Vec_c061_01E03D80 prev;
    Vec_c061_01E03D80 q[4];
    Vec_c061_01E03D80 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_c061_01E03D80 pkt __attribute__((aligned(8)));
    Col_c061_01E03D80 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_c061_01E03D80 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    n = an->count;
    w /= 10.0f;
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
    func_00108EF0(m, 0, 0, &pos);
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 2; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(ctrl, 0, t);
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 2));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (2.5f * n);
            for (k = 0; k < 2; k++) {
                func_00109A70(&q[0], &ab[0]);
                func_00109A70(&q[1], &ab[0]);
                func_00109A70(&q[2], &ab[1]);
                func_00109A70(&q[3], &ab[1]);
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
                        func_002075F0(p, target, (u32)depth[0]);
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                }
            }
        }
    }
}

/* shape b363:01E06930, 264 insns, 4 copies: draws a band of 12 quads (two rings, radius and height from the table at two
   angles 20 apart) around a position, scaled by size / 1500, turned by the object's rotation; blend from
   flags >> 4. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b363_01E06930;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[8];
    s16 start;
    u8 pad5C[4];
    u8 col[4];
} Band_b363_01E06930;

static void func_01E06640_c063(Obj_b363_01E06930 *o, Band_b363_01E06930 *s, Vec4f pos, s32 flags) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    f32 r0;
    s32 k;
    s16 b;
    s16 a;
    s16 t;
    u8 *p;
    f32 r1;
    f32 sc;

    p = pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    sc = s->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 90.0f * func_00108030(o->xD8, s->h50, 0);
    quad[1].y = quad[0].y;
    quad[2].y = 90.0f * func_00108030(o->xD8, s->h50 + 20, 0);
    quad[3].y = quad[2].y;
    r0 = 90.0f * func_00108030(o->xD8, s->h50, 1);
    r1 = 90.0f * func_00108030(o->xD8, s->h50 + 20, 1);
    a = 0;
    for (k = 0; k < 12; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[2].x = r1 * func_00108030(o->xD8, t, 1);
            quad[2].z = r1 * func_00108030(o->xD8, t, 0);
            quad[0].x = r0 * func_00108030(o->xD8, t, 1);
            quad[0].z = r0 * func_00108030(o->xD8, t, 0);
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        } else {
            quad[2].x = quad[3].x;
            quad[2].z = quad[3].z;
            quad[0].x = quad[1].x;
            quad[0].z = quad[1].z;
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
        a += 30;
    }
}
