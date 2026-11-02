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

static void func_01E00080_b582(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b582(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
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
        func_01E00080_b582((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
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

static void func_01E00EA0_b582(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
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
        func_01E00080_b582((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
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

/* shape b119:01E00920, 258 insns, 4 copies: draws a flat ring of 18 quads like shape b112:01E00B60, turned by the ring's own
   rotation instead of the camera's; radii converted once. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E00920;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b119_01E00920;

static void func_01E01400_b582(Obj_b119_01E00920 *o, Ring_b119_01E00920 *s, s32 mode, Vec4f pos) {
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
    u8 pkt[0x90];
    s32 t;
    f32 ro;
    f32 ri;
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
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = ro * func_00108030(o->xD8, t, 1);
            quad[0].z = ro * func_00108030(o->xD8, t, 0);
            quad[2].x = ri * func_00108030(o->xD8, t, 1);
            quad[2].z = ri * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
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

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E01810_b582(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
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
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
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
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b582", func_01E01AB0_b582);

/* shape b582:01E02100, 66 insns: a falling spark: above height 20 its 0x26 grows by 0x19 (below 0x32), else shrinks
   by 0x14 to 0; it falls 30 a tick; below 0 the scene takes its position and on even random rolls (scene step
   0x35F4 below 0x12C) runs the module's b582:01E032D0 through b582:01E04440; then it ends */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x35F4 - 0x25C];
    s16 step;
} Scene_b582_01E02100;

typedef struct {
    f32 x, y, z;
    u8 padC[0x1A];
    s16 f26;
    u8 pad28[4];
    s16 mode;
} Fx_b582_01E02100;

static s32 func_01E02100_b582(Scene_b582_01E02100 *g, Fx_b582_01E02100 *o) {
    extern void b582_01E032D0(void);
    extern void b582_01E04440(void *, void *, s32);
    if (!(o->y <= 20.0f)) {
        if (o->f26 < 0x32) {
            o->f26 += 0x19;
        }
    } else if (o->f26 > 0) {
        o->f26 -= 0x14;
    } else {
        o->f26 = 0;
    }
    o->y -= 30.0f;
    if (o->y < 0.0f) {
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        if (func_0019A5C8() % 2 == 0) {
            if (g->step < 0x12C) {
                b582_01E04440(g, b582_01E032D0, 0);
            }
        }
        o->mode = 0;
    }
    return 0;
}

/* shape b582:01E02210, 60 insns: a blue glow: both colours 0x10/0x10/0x80; both alphas up by 12 to 0x80 for 0xC0 frames,
   then down by 9 and it ends when either runs out */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b582_01E02210;

static s32 func_01E02210_b582(void *arg0, Obj_b582_01E02210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x10, 0x10, 0x80);
        func_001076F0(o->c1, 0x10, 0x10, 0x80);
        o->state = 2;
    }
    if (o->t < 0xC1) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0xC;
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
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b582:01E02300, 145 insns: b501:01E02FE0 family grey spark (size 12..23, or half the model scale for kind 0, growing to 60; frame stepping every other tick to 5; fA = old f30, f30 10..109, angle 0..359, step 5..9, f8 0..34, life 2..6): alpha up by 64, then down by 7; rises 1 every other tick */

/* OVL_WARM */

typedef struct {
    s16 x;
    s16 y;
    u8 pad4[2];
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
} Fx_b582_01E02300;

static s32 func_01E02300_b582(s32 arg0, Fx_b582_01E02300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern f32 func_001F5860(s32);

    if (o->mode == 1) {
        if (o->f30 != 0) {
            o->f38 = func_0019A5C8() % 12 + 12;
        } else {
            o->f38 = func_001F5860(func_001F5380()) / 2.0f;
        }
        o->f34 = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 100 + 10;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f38 < 60) {
            o->f38++;
        }
    }
    if (o->tick % 2 == 1) {
        o->y++;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    o->tick++;
    return 0;
}

/* shape b582:01E02550, 73 insns: a dark-red turning glow: frame 36; fades in by 9 up to 0x69 until the game timer reaches
   300, then out by 9 until it ends; its angle and height turn by 4 a frame (mod 360) */

typedef struct {
    u8 pad0[0x35F4];
    s16 timer;
} Game_b582_01E02550;

typedef struct {
    u8 pad0[0xA];
    s16 turn;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b582_01E02550;

static s32 func_01E02550_b582(Game_b582_01E02550 *g, Obj_b582_01E02550 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x24;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 8, 8);
        o->state = 2;
    }
    if (g->timer < 0x12C) {
        if (o->c0[3] < 0x61) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->ang += 4;
    o->turn += 4;
    if (o->ang >= 0x168) {
        o->ang %= 360;
    }
    if (o->turn >= 0x168) {
        o->turn %= 360;
    }
    o->t++;
    return 0;
}

/* shape b582:01E02680, 188 insns: b350:01E00C60 family grey (0x40) puff spanning ctx+0x35DC / 0x35DE: size 70 growing 3, speed 4..8, h8 0..29, hold 5..7, alpha up by 0x20 to 0xA0, then down by 15; every other tick slides by its span and frames up to 6 */

typedef struct {
    u8 pad0[0x35DC];
    s16 id0;
    s16 id1;
} Ctx_b582_01E02680;

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
} Fx_b582_01E02680;

static s32 func_01E02680_b582(Ctx_b582_01E02680 *g, Fx_b582_01E02680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 70;
        o->f34 = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 4;
        o->h8 = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 3 + 5;
        func_001F5620(func_001F53A0(), g->id0, v);
        func_001F5620(func_001F53A0(), g->id1, &v[4]);
        o->hC = v[4] - v[0];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    v[2] /= 40.0f;
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
        o->f38 += 3;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b582:01E02970, 240 insns: b257:01E024F0's random-colour glow on joints ctx+0x35DC/0x35DE, rise 3..12, held
   11..20 ticks fading in by 0x10 to 0x80, then out by 15 */

typedef struct {
    u8 pad0[0x35DC];
    s16 ja;
    s16 jb;
} Game_b582_01E02970;

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
} Glow_b582_01E02970;

static s32 func_01E02970_b582(Game_b582_01E02970 *g, Glow_b582_01E02970 *o) {
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
        o->hE = func_0019A5C8() % 10 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 11;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x10;
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

/* shape b582:01E02D30, 124 insns: a grey smoke puff: on start a random spin start 5..34 / -5..4 / 5..34, angle 0..359,
   alpha 0x80, size 10..69, life 15..64; kind 0 starts at frame 0, kind 1 at life - 2; a random tint 0..9; alpha up by 64
   to 0x80 for 4 ticks, then down by 9 until it ends; it spins by 0x4000 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    s32 i10;
    s32 i14;
    s32 i18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Obj_b582_01E02D30;

static s32 func_01E02D30_b582(void *g, Obj_b582_01E02D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x28;
        func_001076F0(o->c0, 0x70, 0x70, 0x70);
        func_001076F0(o->c1, 0x70, 0x70, 0x70);
        o->i10 = func_0019A5C8() % 30 + 5;
        o->i14 = func_0019A5C8() % 10 - 5;
        o->i18 = func_0019A5C8() % 30 + 5;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->c0[3] = 0x80;
        o->c1[3] = 0;
        o->fA = func_0019A5C8() % 60 + 10;
        o->f38 = func_0019A5C8() % 50 + 15;
        if (o->kind == 0) {
            o->f8 = 0;
        }
        if (o->kind == 1) {
            o->f8 = o->f38 - 2;
        }
        o->fE = func_0019A5C8() % 10;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->i10);
    o->i10 += 0x4000;
    o->t++;
    return 0;
}

/* shape b582:01E02F20, 97 insns: a two-colour glow (size 20; kind 0 white/orange, 1 green, 2 blue) at a random angle, spun 0x4000 a tick: in by 96 up to 0xC0 for 3 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    s32 w10;
    u8 pad14[4];
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
} Glow_b582_01E02F20;

static s32 func_01E02F20_b582(s32 arg0, Glow_b582_01E02F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        if (o->h30 == 0) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0xFF, 0x80, 8);
        } else if (o->h30 == 1) {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 0x10, 0x80, 0x10);
        } else if (o->h30 == 2) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x10, 0x10, 0x80);
        }
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0;
        o->col2[3] = 8;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w10);
    o->w10 += 0x4000;
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b582:01E030B0, 133 insns: a pink glow whose brightness follows how straight the camera looks at the scene point:
   on start it reads the joint point (raised 2), turns it camera-relative and stores the cosine between it and the view
   direction; for 3 ticks both alphas are 128 x that cosine, then they fade by 0xB (ends below 0xD) */

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 mode;
} Fx_b582_01E030B0;

typedef struct {
    u8 pad0[0x3560];
    f32 x, y, z;
    u8 pad356C[0x5C];
    f32 cosv;
    u8 pad35CC[0x18];
    s16 joint;
} Scene_b582_01E030B0;

static s32 func_01E030B0_b582(Scene_b582_01E030B0 *g, Fx_b582_01E030B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 *func_001F9D30(s32);
    extern f32 *func_001F9AD0(s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001A6C60(f32);
    f32 *cam;
    f32 *look;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dot;
    f32 len;

    cam = func_001F9D30(0);
    look = func_001F9AD0(0);
    if (o->mode == 1) {
        func_001076F0(o->c0, 0x80, 0x60, 0x60);
        func_001076F0(o->c1, 0x80, 0x60, 0x60);
        o->mode = 2;
        o->c0[3] = 0;
        o->c1[3] = 0;
        o->hE = func_0019A5C8() % 10;
        func_001F5620(func_001F53A0(), g->joint, &g->x);
        g->y += 2.0f;
        g->x = g->x - cam[0];
        g->y = g->y - cam[1];
        g->z = g->z - cam[2];
        dx = look[0] - cam[0];
        dy = look[1] - cam[1];
        dz = look[2] - cam[2];
        dot = g->x * dx + g->y * dy + g->z * dz;
        len = func_001A6C60(dx * dx + dy * dy + dz * dz);
        g->cosv = dot / (len * func_001A6C60(g->x * g->x + g->y * g->y + g->z * g->z));
    }
    if (o->t < 3) {
        o->c1[3] = o->c0[3] = 128.0f * g->cosv;
    } else {
        if (o->c0[3] > 0xC) {
            o->c0[3] -= 0xB;
        } else {
            o->mode = 0;
        }
        o->c1[3] = o->c0[3];
    }
    o->t++;
    return 0;
}

/* shape b582:01E032D0, 33 insns: a counter-driven fade: starts at 0x80, after tick 61 drops by 19 down to 20, ends after tick 91 once under 20; the tick steps by 15 */

typedef struct {
    u8 pad0[0x28];
    s16 level;
    u8 pad2A[2];
    s16 state;
    u8 pad2E[4];
    s16 tick;
} Fade_b582_01E032D0;

static s32 func_01E032D0_b582(s32 arg0, Fade_b582_01E032D0 *o) {
    if (o->state == 1) {
        o->tick = 0;
        o->state = 2;
        o->level = 0x80;
    }
    if (o->tick > 60) {
        if (o->level > 20) {
            o->level -= 19;
        }
    }
    if (o->tick > 90 && o->level < 20) {
        o->state = 0;
    }
    o->tick += 15;
    return 0;
}

/* shape b582:01E03360, 67 insns: a brown flash (b081:01E02740 shape): set up once (frame 6, size 4 by 55), both alphas up by 0x40 to
   0x80 for 2 frames, then down by 15; it ends when the first runs out */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x1C];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b582_01E03360;

static s32 func_01E03360_b582(void *arg0, Obj_b582_01E03360 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x40, 0x30, 8);
        func_001076F0(o->c1, 0x40, 0x30, 8);
        o->w = 4;
        o->h = 0x37;
        o->state = 2;
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
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0xF;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0xF;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b582:01E03470, 91 insns: drives the scene's light (ctx+0x3580): set it up at the object's position (blue 4/4/4, height 70), raise its level by 0.2 to 1, then lower by 0.1 and end; while alive it is applied (func_001F6C10), else cleared; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b582_01E03470;

typedef struct {
    s32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[4];
    s32 state;
} Light_b582_01E03470;

typedef struct {
    u8 pad[0x3580];
    Light_b582_01E03470 l;
} Game_b582_01E03470;

static s32 func_01E03470_b582(Game_b582_01E03470 *g, Obj_b582_01E03470 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 0;
        g->l.r = 4.0f;
        g->l.g = 4.0f;
        g->l.b = 4.0f;
        g->l.w20 = 0;
        g->l.h = 70.0f;
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

/* shape b582:01E035E0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x35B0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x35B0];
    s32 state;
} Game_b582_01E035E0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b582_01E035E0;

static s32 func_01E035E0_b582(Game_b582_01E035E0 *g, Fade_b582_01E035E0 *o) {
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

static s32 func_01E036A0_b582(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05780_b582;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05788_b582;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b582:01E036F0, 84 insns: a screen tint: on start alpha 0; builds a grey (0x80) full-screen textured sprite
   (0x6BF8,0x71F8 - 0x93F8,0x8DF8, uv 0..0.625 x 0..0.875) in the effect's alpha on the stack and sends it; alpha
   then 0x68 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b582_01E036F0;

typedef struct {
    f32 s, t;
    Xyz_b582_01E036F0 p;
} Tv_b582_01E036F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b582_01E036F0 v[2];
    u8 tail[0x20];
} Tex_b582_01E036F0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[0xA];
    s16 mode;
} Fx_b582_01E036F0;

static s32 func_01E036F0_b582(s32 arg0, Fx_b582_01E036F0 *o) {
    Tex_b582_01E036F0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->col[3] = 0;
        o->mode = 2;
    }
    ((Tex_b582_01E036F0 *)(s32)&pk)->count = 0x26;
    ((Tex_b582_01E036F0 *)(s32)&pk)->tag = 5;
    ((Tex_b582_01E036F0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b582_01E036F0 *)(s32)&pk)->pad = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
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
    pk.v[0].s = 0.0f;
    pk.v[0].t = 0.0f;
    pk.v[1].s = 0.625f;
    pk.v[1].t = 0.875f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    o->col[3] = 0x68;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b582", func_01E03840_b582);

/* OVL_WARM */

/* shape b582:01E04440, 146 insns: takes the first free of 180 slots (0x38 bytes at +0x2A0), places it at the scene
   point with three x/z pairs scattered by -75..74, stores the argument and returns 1 (0 when all are taken) */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    s32 arg;
    s16 x0;
    s16 x1;
    s16 x2;
    s16 z0;
    s16 z1;
    s16 z2;
    u8 pad20[0xC];
    s16 used;
    u8 pad2E[0xA];
} Slot_b582_01E04440;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x44];
    Slot_b582_01E04440 slot[180];
} Scene_b582_01E04440;

static s32 func_01E04440_b582(Scene_b582_01E04440 *g, s32 arg) {
    extern void func_00195108(void *, s32);
    s16 i;
    Slot_b582_01E04440 *s;

    s = NULL;
    for (i = 0; i < 180; i++) {
        if (g->slot[i].used == 0) {
            s = &g->slot[i];
            func_00195108(s, 0x38);
            g->slot[i].used = 1;
            i = 180;
        }
    }
    if (s != NULL) {
        s->x = g->x;
        s->y = g->y;
        s->z = g->z;
        s->x0 = g->x;
        s->z0 = g->z;
        s->x1 = g->x;
        s->z1 = g->z;
        s->x2 = g->x;
        s->z2 = g->z;
        s->x0 += (s16)(func_0019A5C8() % 150 - 75);
        s->z0 += (s16)(func_0019A5C8() % 150 - 75);
        s->x1 += (s16)(func_0019A5C8() % 150 - 75);
        s->z1 += (s16)(func_0019A5C8() % 150 - 75);
        s->x2 += (s16)(func_0019A5C8() % 150 - 75);
        s->z2 += (s16)(func_0019A5C8() % 150 - 75);
        s->arg = arg;
        return 1;
    }
    return 0;
}

/* shape b582:01E04690, 74 insns: twin of b046:01E03E20: take the first free slot of the 45-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x35F0 and 0x35EC and the two arguments; returns 1 if a
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
} Slot_b582_01E04690;

typedef struct {
    u8 pad[0x250];
    u8 m[0x27B0];
    Slot_b582_01E04690 s[45];
    u8 pad3540[0x74];
    u8 r, g, b, a;
    u8 pad35B8[0x34];
    s16 w;
    u8 pad35EE[0x2];
    s16 v;
} Pool_b582_01E04690;

static s32 func_01E04690_b582(Pool_b582_01E04690 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b582_01E04690 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 45; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 45;
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

/* OVL_WARM */

/* shape b582:01E047C0, 210 insns: a red (0xFF, 0x20, 0x20) line strip into the given packet (2 vertices, solid end
   and clear end): the scene colour data (ctx+0x35B4) is set up first (mode 9 when ctx+0x35F2 is set); four segments
   from the anchor (an+0x0): the first stretched by 4x (0x20, 0x26, 0x24), the others offset by the per-segment x/z
   (an+0x14 / an+0x1A) and stretched by 3x; depth in ctx+0x35CC, drawn into ctx+0x35BC */

typedef struct {
    u8 r, g, b, a;
} Col_b582_01E047C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b582_01E047C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    struct {
        Rgbaq_b582_01E047C0 c;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[2];
} Pkt_b582_01E047C0;

typedef struct {
    u8 pad0[0x35B4];
    u8 rgb[8];
    s32 ot;
    u8 pad35C0[0x35CC - 0x35C0];
    f32 depth;
    u8 pad35D0[0x35F2 - 0x35D0];
    s16 mode;
} Obj_b582_01E047C0;

typedef struct {
    Vec4f pos;
    u8 pad10[4];
    s16 dx[3];
    s16 dz[3];
    s16 h20;
    u8 pad22[2];
    s16 h24;
    s16 h26;
} Line_b582_01E047C0;

static void func_01E047C0_b582(Obj_b582_01E047C0 *o, Line_b582_01E047C0 *an, Pkt_b582_01E047C0 *p) {
    extern void func_00107EC0(void *, s32, s32);
    extern Rgbaq_b582_01E047C0 func_00107740(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern Col_b582_01E047C0 D_01E05790_b582;
    Col_b582_01E047C0 c = D_01E05790_b582;
    Vec4f q[4];
    s32 i;

    if (o->mode == 0) {
        func_00107EC0(o->rgb, 0, 0);
    } else {
        func_00107EC0(o->rgb, 0, 9);
    }
    p->count = 0x11;
    p->tag = 4;
    p->regs = 0x4141;
    p->pad = 0;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->v[1].c.q = 1.0f;
    p->v[0].c.q = 1.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    c.a = 0xFF;
    p->v[0].c = func_00107740(&c);
    c.a = 0;
    p->v[1].c = func_00107740(&c);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            q[0] = an->pos;
            q[1] = an->pos;
            q[1].y += an->h26;
            q[1].x += an->h20 * 4;
            q[1].z += an->h24 * 4;
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

/* shape b582:01E04B10 (B582PAINT_RAIN3), 212 insns, 1 copy: b116:01E009A0's sprite draw made four times: the packet
   (passed in) gets its blend from flags >> 4, the module's colour (D_01E05798_b582) with the object's alpha, the
   scene rect corners (shape b003:01E00080) and texture; then four camera-facing sprites of the object's size, the
   first at its point and the others moved by its per-entry x/z offsets, depth by flags & 0xF (projected, far) */

typedef struct {
    f32 x, y, z;
    u8 padC[6];
    s16 dx[3];
    s16 dz[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[6];
    s16 size;
} Obj_b582_01E04B10;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    void *tex;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 frame;
} Game_b582_01E04B10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b582_01E04B10;

typedef struct {
    f32 u, v;
} Uv_b582_01E04B10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b582_01E04B10 uv;
    u64 pad18;
    Xyz_b582_01E04B10 v[4];
} Pk_b582_01E04B10;

typedef struct {
    u8 c[4];
} Col_b582_01E04B10;

static void func_01E04B10_b582(Game_b582_01E04B10 *g, Obj_b582_01E04B10 *o, Pk_b582_01E04B10 *p, s32 flags) {
    extern Col_b582_01E04B10 D_01E05798_b582;
    extern void func_00108EF0();
    Vec4f view[4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[16];
    s32 rot[4];
    Uv_b582_01E04B10 uv;
    Col_b582_01E04B10 col;
    s16 i;
    s32 sel;

    col = D_01E05798_b582;
    sel = flags >> 4;
    col.c[3] = o->col[0];
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &col);
    p->uv = uv;
    func_01E00080_b582((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] = 0x4000;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            a.x = o->x;
            a.y = o->y;
            a.z = o->z;
        } else {
            a.x = o->x + o->dx[i];
            a.y = o->y;
            a.z = o->z + o->dz[i];
        }
        func_00108EF0(m, &s, rot, &a);
        func_00108CE0(view, o->size, o->size);
        if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
            if ((flags & 0xF) == 0) {
                func_002075F0((s32)p, g->ot, func_001A23B0(out[0]));
            } else if ((flags & 0xF) == 1) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, g->ot, 0);
            }
        }
    }
}


/* shape b582:01E04E60, 191 insns, 1 copy: a 25 x 40 field of flat sprites (spacing twice the size, centred) lifted by 20 x the
   cosine of the object's angle 0x3A, each row bobbing by 10 x the cosine of a phase that steps 6 per row; blend by
   flags >> 4 (0 = 0x48, 1 = 0x44, else 0x42). Calls the module's sprite-UV helper (shape b003:01E00080). */

typedef struct Uv_b582_01E04E60 {
    f32 u, v;
} Uv_b582_01E04E60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b582_01E04E60 uv;
} Pk_b582_01E04E60;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    void *tex;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 trig[1];
} Obj_b582_01E04E60;

typedef struct {
    u8 pad0[0xA];
    s16 phase;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
    s16 ang;
} Field_b582_01E04E60;

#pragma opt_propagation off

static void func_01E04E60_b582(Obj_b582_01E04E60 *obj, Field_b582_01E04E60 *o, Pk_b582_01E04E60 *pk, s32 flags) {
    extern void func_00108D20(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    f32 depth[4];
    Uv_b582_01E04E60 uv;
    s32 sel;
    s16 j;
    s16 i;
    s16 w;
    s16 d;
    s16 hx;
    s16 hz;
    s16 a;
    f32 lift;
    f32 h;
    f32 x;

    pk->flags = 0x24;
    pk->size = 9;
    pk->regs = ((u64)4 << 32) | 0x24242421;
    pk->pad4 = 0;
    sel = flags >> 4;
    pk->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(pk, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(pk, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(pk, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, o->col);
    pk->uv = uv;
    func_01E00080_b582((void *)pk, (void *)obj->rect, obj->page);
    func_00208700(pk, obj->tex, 1);
    w = (o->size * 25) >> 1;
    d = (o->size * 40) >> 1;
    lift = 20.0f * func_00108030(obj->trig, o->ang, 0);
    hx = w;
    hz = d;
    a = o->phase;
    for (j = 0; j < 40; j++) {
        h = -1.0f + 10.0f * func_00108030(obj->trig, a, 0);
        for (i = 0; i < 25; i++) {
            func_00108D20(m, o->size, o->size);
            x = (f32)(i * (o->size * 2) - hx);
            func_00107070(m, 0, x + lift);
            func_00107070(m, 2, (f32)(j * (o->size * 2) - hz));
            func_00107070(m, 1, h);
            if (func_00205630((s32)m, 0x70000000, 0, (s32)pk, depth) != 0) {
                func_002075F0((s32)pk, obj->ot, func_001A23B0(depth[0]));
            }
        }
        a += 6;
    }
}
#pragma opt_propagation reset

/* shape b582:01E05160, 193 insns (h1 reads size through a cast so its load is not merged with h0's and the maths is not sunk past the call): a 25 x 40 grid of sprites (the module's static UV helper, shape b003:01E00080), each 0x38 wide and 2x0x38 apart, centred on the object, pushed 30*sin(0x3A) back, its height -10 + 20*sin(row angle) with the row angle starting at 0xA + 60 and stepping 6 */


typedef struct {
    f32 s;
    f32 t;
} St_b582_01E05160;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b582_01E05160 st;
} Pk_b582_01E05160;

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 tex[0x10];
    s16 size;
    s16 ang;
} Fx_b582_01E05160;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    void *tex;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 frame;
    u8 padC0[0x18];
    u8 trig[1];
} Obj_b582_01E05160;

static void func_01E05160_b582(Obj_b582_01E05160 *g, Fx_b582_01E05160 *o, Pk_b582_01E05160 *pk, s32 mode) {
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    f32 depth[4];
    St_b582_01E05160 uv;
    s16 j;
    s16 i;
    s16 h0;
    s16 h1;
    s16 a;
    f32 back;
    f32 y;
    f32 r;
    s32 k;
    f32 z;

    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    k = mode >> 4;
    pk->nreg |= 0x800;
    if (k == 0) {
        func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    } else if (k == 1) {
        func_002086D0(pk, 0x44 | ((s64)0x80 << 32));
    } else {
        func_002086D0(pk, 0x42 | ((s64)0x80 << 32));
    }
    func_00107740(&uv, o->tex);
    pk->st = uv;
    func_01E00080_b582((Pk_b003_01E00080 *)pk, (Rect_b003_01E00080 *)g->rect, g->frame);
    func_00208700(pk, g->tex, 1);
    h0 = (o->size * 25) >> 1;
    h1 = (((Fx_b582_01E05160 *)(u32)o)->size * 40) >> 1;
    back = 30.0f * func_00108030(g->trig, o->ang, 0);
    a = o->fA + 60;
    for (j = 0; j < 40; j++) {
        y = -10.0f + 20.0f * func_00108030(g->trig, a, 0);
        for (i = 0; i < 25; i++) {
            r = o->size;
            func_00108D20(m, r, r);
            func_00107070(m, 0, i * (o->size * 2) - h0);
            z = j * (o->size * 2) - h1;
            func_00107070(m, 2, z + back);
            func_00107070(m, 1, y);
            if (func_00205630((s32)m, 0x70000000, 0, (s32)pk, depth) != 0) {
                func_002075F0((s32)pk, g->ot, (u32)depth[0]);
            }
        }
        a += 6;
    }
}

/* shape b582:01E05470, 174 insns: b108:01E00DF0 family: a flat ring of 18 quads around a position plus the object's
   offset (0x20), outer radius 0x08 and inner radius 0x38 / 100, 20 apart from the ring's start angle, two colours,
   turned by the ring's rotation, sent at the projected depth */

typedef struct {
    u8 pad00[0x20];
    f32 off[3];
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b582_01E05470;

typedef struct {
    u8 pad00[8];
    s16 outer;
    u8 padA[6];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 inner;
    s16 start;
} Ring_b582_01E05470;

static void func_01E05470_b582(Obj_b582_01E05470 *o, Ring_b582_01E05470 *s, s32 flags, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 k;
    s32 t;
    s16 a;
    u8 *p;
    f32 ro;
    f32 ri;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    p2.x += o->off[0];
    p2.y += o->off[1];
    p2.z += o->off[2];
    func_00108EF0(m, 0, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    ri /= 100.0f;
    for (k = 0; k < 18; k++) {
        t = s->start + a;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = a + (s->start + 20);
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
        a += 20;
    }
}
