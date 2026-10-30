#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b746(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b746(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
} Vec_b016_01E01190;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b016_01E01190;

typedef struct {
    u8 pad00[0x20];
    Vec_b016_01E01190 rotation;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b016_01E01190;

static void func_01E009B0_b746(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b016_01E01190 c;
    Vec_b016_01E01190 quad[4];
    Vec_b016_01E01190 pos;
    Vec_b016_01E01190 scale;
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
    quad[2].y = data->height;
    quad[3].y = data->height;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b746 in the
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

static void func_01E00D10_b746(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b746((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E00FD0_b746(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
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
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
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
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
        }
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01340_b746(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b363:01E01160, 477 insns: b111:01E00D70's sprite ring without the per-sprite turn: each point-sized
   quad is pushed out along the rotated table offset; mode 0 widens it on screen by size / (depth / (fov / 10))
   (fov from func_001F9A20, 400 when 0) and draws at depth 0; 1 = far z, 2 = -1 */

typedef struct Data_b363_01E01160 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b363_01E01160;

typedef struct Obj_b363_01E01160 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b363_01E01160;

typedef struct Xyz_b363_01E01160 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b363_01E01160;

typedef struct Uv_b363_01E01160 {
    f32 u, v;
} Uv_b363_01E01160;

typedef struct Pk_b363_01E01160 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b363_01E01160 uv;
    u64 pad18;
    Xyz_b363_01E01160 v[4];
    u64 pad60[6];
} Pk_b363_01E01160;

typedef struct Buf_b363_01E01160 {
    u64 tag;
    Pk_b363_01E01160 pk;
} Buf_b363_01E01160;

static void func_01E01780_b746(Obj_b363_01E01160 *obj, Data_b363_01E01160 *data, s32 flags, s8 *tab) {
    f32 size;
    f32 fov;
    extern void b746_01E00110();
    extern void func_00108950();
    extern void func_00108EF0();
    extern f32 func_001F9A20(s32);
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b363_01E01160 buf;
    Uv_b363_01E01160 uv;
    s16 sel;
    s16 i;
    Pk_b363_01E01160 *p;
    s32 mode;
    s8 *row;
    s32 half;

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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b746_01E00110(p, obj->f94, obj->fC0);
    fov = func_001F9A20(0);
    if (fov == 0.0f) {
        fov = 400.0f;
    }
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        size = data->f48;
        func_00108CE0(view, 0.0f, 0.0f);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = (row[data->f8 + 180] / 20.0f) * (data->f50 + half);
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                size /= depth[0] / (fov / 10.0f);
                p->v[0].x = (u32)((f32)(u32)p->v[0].x - size);
                p->v[0].y = (u32)((f32)(u32)p->v[0].y + size);
                p->v[1].x = (u32)((f32)(u32)p->v[1].x + size);
                p->v[1].y = (u32)((f32)(u32)p->v[1].y + size);
                p->v[2].x = (u32)((f32)(u32)p->v[2].x - size);
                p->v[2].y = (u32)((f32)(u32)p->v[2].y - size);
                p->v[3].x = (u32)((f32)(u32)p->v[3].x + size);
                p->v[3].y = (u32)((f32)(u32)p->v[3].y - size);
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
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

static void func_01E01F00_b746(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b065_01E012B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b065_01E012B0;

typedef struct {
    Col_b065_01E012B0 c;
    u64 st;
    u64 xyz;
} Vtx_b065_01E012B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b065_01E012B0 v[4];
    u8 tail[0x20];
} Pkt_b065_01E012B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Anim_b065_01E012B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b065_01E012B0;

static void func_01E020D0_b746(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107740(void *, void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b065_01E012B0 quad[4];
    Vec_b065_01E012B0 at;
    Vec_b065_01E012B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b065_01E012B0 pkt;
    Col_b065_01E012B0 c0;
    Col_b065_01E012B0 c1;
    Col_b065_01E012B0 c2;
    Col_b065_01E012B0 c3;
    s16 blend;
    s32 i;
    s32 a;
    s16 j;
    s16 wd;
    Pkt_b065_01E012B0 *p;
    s32 width;
    f32 w0;
    f32 w1;

    p = &pkt;
    width = an->width;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    blend = mode >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col0, 0);
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    func_00107740(&c0, an->col0);
    p->v[0].c = c0;
    func_00107740(&c1, an->col1);
    p->v[2].c = c1;
    func_00107740(&c2, an->col0);
    p->v[1].c = c2;
    func_00107740(&c3, an->col1);
    p->v[3].c = c3;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    wd = width;
    for (i = 0; i < o->count; i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + wd);
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if ((mode & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if ((mode & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        }
        j += an->step;
    }
}

/* shape b746:01E024E0 (B746_W_S), 382 insns, 1 copy: B746_W_S, the effect scene step: counts the frame (0xCBCC);
   frame 1 spawns 0x1E042C0, 0x1E04080, 0x1E03F70 and four 0x1E036B0 (angles 0/90/45/135, sides 0/0/1/1); 74/95 spawn
   0x1E03D90 on sides 0,1 / 2; each frame vel is an eighth of joint 0xCB58 minus joint 0xCB5C; 70 spawns 0x1E03990; 79
   takes joint 0xCB58 into pt; frames 79..89 copy pt to pos and spawn 0x1E03210, three 0x1E03010 and ten 0x1E02E40;
   from 79 pt.z moves 1 by flag; 40/74 and 48/74 spawn ten 0x1E02AE0 around joints 0xCB5E/0xCB60 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCAD0 - 0x260];
    Vec4f pt;
    u8 padCAE0[0xCAF0 - 0xCAE0];
    f32 vel[3];
    u8 padCAFC[0xCB58 - 0xCAFC];
    s16 joint0;
    u8 padCB5A[2];
    s16 joint1;
    s16 joint2;
    s16 joint3;
    u8 padCB62[0xCBB6 - 0xCB62];
    s16 ang;
    u8 padCBB8[0xCBC4 - 0xCBB8];
    s16 side;
    u8 padCBC6[2];
    s16 flag;
    u8 padCBCA[2];
    s16 t;
} Scene_b746_01E024E0;

static void func_01E024E0_b746(Scene_b746_01E024E0 *g) {
    extern void b746_01E02AE0(void);
    extern void b746_01E02E40(void);
    extern void b746_01E03010(void);
    extern void b746_01E03210(void);
    extern void b746_01E036B0(void);
    extern void b746_01E03990(void);
    extern void b746_01E03D90(void);
    extern void b746_01E03F70(void);
    extern void b746_01E04080(void);
    extern void b746_01E042C0(void);
    extern void b746_01E05080(Scene_b746_01E024E0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];
    s16 i;
    s16 j;

    g->t++;
    if (g->t == 1) {
        b746_01E05080(g, b746_01E042C0, 0);
    }
    if (g->t == 1) {
        b746_01E05080(g, b746_01E04080, 0);
    }
    if (g->t == 74) {
        g->side = 0;
        b746_01E05080(g, b746_01E03D90, 0);
        g->side = 1;
        b746_01E05080(g, b746_01E03D90, 0);
    }
    if (g->t == 95) {
        g->side = 2;
        b746_01E05080(g, b746_01E03D90, 0);
    }
    func_001F5620(func_001F53A0(), g->joint0, &v[0]);
    func_001F5620(func_001F53A0(), g->joint1, &v[1]);
    g->vel[0] = (v[0].x - v[1].x) / 8.0f;
    g->vel[1] = (v[0].y - v[1].y) / 8.0f;
    g->vel[2] = (v[0].z - v[1].z) / 8.0f;
    if (g->t == 1) {
        b746_01E05080(g, b746_01E03F70, 0);
    }
    if (g->t == 70) {
        b746_01E05080(g, b746_01E03990, 0);
    }
    if (g->t == 79) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pt);
    }
    if (g->t >= 79 && g->t < 90) {
        g->pos = g->pt;
        g->side = 0;
        b746_01E05080(g, b746_01E03210, 0);
        for (i = 0; i < 3; i++) {
            b746_01E05080(g, b746_01E03010, 0);
        }
        for (i = 0; i < 10; i++) {
            b746_01E05080(g, b746_01E02E40, 0);
        }
    }
    if (g->t >= 79) {
        if (g->flag) {
            g->pt.z -= 1.0f;
        } else {
            g->pt.z += 1.0f;
        }
    }
    if (g->t == 1) {
        g->ang = 0;
        g->side = 0;
        b746_01E05080(g, b746_01E036B0, 0);
        g->ang = 90;
        g->side = 0;
        b746_01E05080(g, b746_01E036B0, 0);
        g->ang = 45;
        g->side = 1;
        b746_01E05080(g, b746_01E036B0, 0);
        g->ang = 135;
        g->side = 1;
        b746_01E05080(g, b746_01E036B0, 0);
    }
    if (g->t == 40 || g->t == 74) {
        func_001F5620(func_001F53A0(), g->joint2, &g->pos);
        for (i = 0, j = 0; i < 10; j += 36, i++) {
            g->ang = j;
            b746_01E05080(g, b746_01E02AE0, 0);
        }
    }
    if (g->t == 48 || g->t == 74) {
        func_001F5620(func_001F53A0(), g->joint3, &g->pos);
        for (j = 0, i = 0; j < 10; i += 36, j++) {
            g->ang = i;
            b746_01E05080(g, b746_01E02AE0, 0);
        }
    }
}

/* shape b746:01E02AE0, 113 insns: a white drifting spark (b092:01E02420 shape): size 40, sub-frame 2..4, frame 0..3; pushed 2
   along its angle at the start, then drifting 0.5 a frame; alpha up by 0x60 for 6 frames, then down by 19 until it ends; turns */

typedef struct {
    u8 pad0[0xCDD0];
    u8 sin[1];
} Game_b746_01E02AE0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b746_01E02AE0;

static s32 func_01E02AE0_b746(Game_b746_01E02AE0 *g, Obj_b746_01E02AE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x28;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->z += 2.0f * func_00108030(g->sin, o->ang, 0);
        o->x += 2.0f * func_00108030(g->sin, o->ang, 1);
        o->frame = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 6) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0x14) {
        o->c0[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.5f * func_00108030(g->sin, o->ang, 0);
        o->x += 0.5f * func_00108030(g->sin, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b746:01E02CB0, 98 insns: a grey spark: size 20..34, random sub-frame 0..2, height 10..49, angle, rise 16..35, width 0..34,
   hold 3..5; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b746_01E02CB0;

static s32 func_01E02CB0_b746(void *arg0, Obj_b746_01E02CB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 0x14;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 40 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b746:01E02E40, 115 insns: on start 0x8/0xA = 80, variant 2..4, colour (0xAF, 0x7F, 0xFF), random heading 0x5A
   and pitch 0x5C (0..179); alpha grows by 0x60 (below 0xC0) for 6 ticks, then fades by 19 and stops; after the first
   tick it moves 1.5 along the heading (z by the cosine, x by the sine) and 2.5 x the cosine of the pitch in y (game
   table 0xCDD0), and 0x8/0xA grow by 2; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[0xCDD0];
    u8 trig[1];
} Game_b746_01E02E40;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 heading;
    s16 pitch;
    u8 pad5E[2];
    u8 col[4];
} Fx_b746_01E02E40;

static s32 func_01E02E40_b746(Game_b746_01E02E40 *g, Fx_b746_01E02E40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f8 = 80;
        o->fA = o->f8;
        o->f56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xAF, 0x7F, 0xFF);
        o->mode = 2;
        o->heading = (func_0019A5C8() >> 4) % 360;
        o->pitch = (func_0019A5C8() >> 4) % 180;
    }
    if (o->tick < 6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->z += 1.5f * func_00108030(g->trig, o->heading, 0);
        o->x += 1.5f * func_00108030(g->trig, o->heading, 1);
        o->y += 2.5f * func_00108030(g->trig, o->pitch, 0);
        o->f8 += 2;
        o->fA = o->f8;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b746:01E03010, 125 insns: b747:01E02500 family white spark (f48 500 growing 1, frame 0..7, fA = old f50, f50 1..15 growing 70..129 per tick, angle 0..359 turning +-1, f8 0..34): alpha up by 42 to 0x80 for 2..3 ticks, then down by 13 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b746_01E03010;

static s32 func_01E03010_b746(s32 arg0, Fx_b746_01E03010 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 500.0f;
        o->f56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->fA = o->f50;
        o->f50 = func_0019A5C8() % 15 + 1;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 60 + 70;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 2;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f5A++;
        } else {
            o->f5A--;
        }
    }
    o->f48 += 1.0f;
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b065:01E01DB0, 290 insns: B065_OBJ_MOVE_6_: a flashing ring by kind (0 green, 1 pale green, 2 red; colours
   swap on odd scene frames), size 140 growing by 35..42.9 a tick (kinds 1, 2 also rise), full alpha for 8 or 10 ticks
   then fading by 11 */

typedef struct {
    u8 pad00[6];
    s16 life;
    u8 pad08[0x1C];
    s32 rot;
    u8 pad28[8];
    f32 f30;
    f32 rise;
    f32 grow;
    u8 pad3C[0xC];
    f32 size;
    f32 inner;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b746_01E03210;

typedef struct {
    u8 pad[0xCBCC];
    s16 frame;
} Game_b746_01E03210;

static s32 func_01E03210_b746(Game_b746_01E03210 *g, Obj_b746_01E03210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 140.0f;
        o->inner = o->size - 58.0f;
        if (o->kind == 0) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x80, 0x20, 0xC0);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x80, 0x40, 0xFF);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->life = 8;
        }
        if (o->kind == 1) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x60, 0x20, 0x80);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x80, 0x40, 0xFF);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->size = func_0019A5C8() % 600 + 100;
            o->rise = 10.0f;
            o->life = 10;
        }
        if (o->kind == 2) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0xC0, 0x80, 0x80);
                func_001076F0(o->col, 0x10, 0x10, 0x10);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->rise = 10.0f;
            o->life = 10;
        }
        if (o->kind == 0) {
            o->h5A = 10;
            o->h5C = 10;
        }
        if (o->kind == 1) {
            o->h5A = 10;
            o->h5C = 3;
        }
        if (o->kind == 2) {
            o->h5A = 60;
            o->h5C = 60;
        }
        o->grow = func_0019A5C8() % 80 + 350;
        o->grow = o->grow / 10.0f;
        o->f30 = 350.0f;
        o->f30 = o->f30 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot = func_0019A5C8() % 0xFFFF;
    }
    if (o->t < o->life) {
        o->col2[3] = 0x80;
    } else if (o->col2[3] > 6) {
        o->col2[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->size += o->grow;
        o->inner = 0.4f * o->size;
    }
    if (o->kind == 1) {
        o->inner = o->size;
        o->rise += o->grow;
    }
    if (o->kind == 2) {
        o->size += o->grow;
        o->inner = 0.7f * o->size;
        o->rise += o->grow;
    }
    o->t++;
    return 0;
}

/* shape b746:01E036B0, 183 insns: b065:01E02410 in blue (0x80, 0x80, 0xFF over 0x40, 0x40, 0xFF), kinds 2/70, 2/30, 8/400 growing 5 or 2.5, alpha up by 0x40 for 9 ticks; follows ctx+0xCB5A toward ctx+0xCB58 and adds the scene drift (ctx+0xCAF0) */

typedef struct {
    u8 pad0[0xCAF0];
    f32 drift[3];
    u8 padCAFC[0xCB58 - 0xCAFC];
    s16 id1;
    s16 id0;
} Ctx_b746_01E036B0;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b746_01E036B0;

static s32 func_01E036B0_b746(Ctx_b746_01E036B0 *g, Fx_b746_01E036B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];
    f32 t;

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->f30 = 2.0f;
            o->f34 = 70.0f;
        }
        if (o->kind == 1) {
            o->f30 = 2.0f;
            o->f34 = 30.0f;
        }
        if (o->kind == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->f52 = 0;
    }
    if (o->tick < 9) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0 && o->tick != 0) {
        o->f34 += 5.0f;
    }
    if (o->kind == 1 && o->tick != 0) {
        o->f34 += 2.5f;
    }
    if (o->tick != 0) {
        if (o->f52 < 0x19) {
            o->f52++;
        }
    }
    o->tick++;
    o->f5A += 6;
    func_001F5620(func_001F53A0(), g->id0, o->pos);
    func_001F5620(func_001F53A0(), g->id1, v);
    t = o->f52;
    v[0] = (v[0] - o->pos[0]) / 25.0f;
    v[1] = (v[1] - o->pos[1]) / 25.0f;
    v[2] = (v[2] - o->pos[2]) / 25.0f;
    o->pos[0] += v[0] * t;
    o->pos[1] += v[1] * t;
    o->pos[2] += v[2] * t;
    o->pos[0] += g->drift[0];
    o->pos[1] += g->drift[1];
    o->pos[2] += g->drift[2];
    return 0;
}

/* shape b746:01E03990, 183 insns: b852:01E03070's trail light in lilac (0xC0/0x80/0xFF) feeding three 20-point trails
   from joints 0xCB58, 0xCB5C and 0xCB5A until scene frame 80; alpha up until frame 76 */

typedef struct {
    f32 x, y, z, w;
} Pt_b746_01E03990;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b746_01E03990 a[20];
    Pt_b746_01E03990 b[20];
    Pt_b746_01E03990 c[20];
    u8 padB590[0x15C8];
    s16 ja;
    s16 jc;
    s16 jb;
    u8 padCB5E[0x6E];
    s16 frame;
} Scene_b746_01E03990;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b746_01E03990;

static s32 func_01E03990_b746(Scene_b746_01E03990 *g, Fx_b746_01E03990 *o) {
    extern void b746_01E00080(Pt_b746_01E03990 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    s16 k;
    Pt_b746_01E03990 *q;

    func_001076F0(o->col, 0xC0, 0x80, 0xFF);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->hE = 30;
        func_001F5620(func_001F53A0(), g->ja, p);
        q = g->a;
        for (i = 0; i < 19; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->b;
        for (j = 0; j < 19; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jc, p);
        q = g->c;
        for (k = 0; k < 19; k++) {
            q[k].x = p[0];
            q[k].y = p[1];
            q[k].z = p[2];
        }
        o->mode = 2;
    }
    if (g->frame < 76) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (g->frame < 80) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b746_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b746_01E00080(&g->b[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jc, p);
        b746_01E00080(&g->c[19], 20, 0, p);
    }
    o->h6 = 5;
    o->t++;
    return 0;
}

/* shape b746:01E03C70, 69 insns: constant variant of b287:01E02C80 (0xE->0x14, 150.0f->200.0f, colour (128, 64, 255)) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b746_01E03C70;

static s32 func_01E03C70_b746(s32 arg0, Fx_b746_01E03C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 200.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x14) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        o->size += 0.4f;
    }
    o->tick++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b746:01E03D90, 119 insns: glow pair in one of three colour/life presets; preset 2 brightens its second colour first */

typedef struct Glow_b746_01E03D90 {
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
} Glow_b746_01E03D90;

static s32 func_01E03D90_b746(s32 arg0, Glow_b746_01E03D90 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        if (o->kind == 0) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0xF0, 0xF0, 0xF0);
            o->life = 16;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0xD0, 0xD0, 0x80);
            func_001076F0(o->c1, 0xA0, 0x80, 0xC0);
            o->life = 16;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0xB0, 0xA0, 0xC0);
            func_001076F0(o->c1, 0xB0, 0xA0, 0xC0);
            o->life = 20;
        }
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->kind < 2) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 0x12;
            }
            if (o->c1[3] < 0x80) {
                o->c1[3] += 0x12;
            }
        }
        if (o->kind == 2) {
            if (o->c1[3] < 0x80) {
                o->c1[3] += 0x12;
            } else if (o->c0[3] < 0x80) {
                o->c0[3] += 0x12;
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

/* shape b746:01E03F70, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x33, floor 0x30, state at 0xCB20 below 0x14 */

typedef struct {
    u8 pad[0xCB20];
    s32 state;
} Game_b746_01E03F70;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b746_01E03F70;

static s32 func_01E03F70_b746(Game_b746_01E03F70 *g, Fade_b746_01E03F70 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x33) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x14) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->tick++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b746:01E04080, 144 insns: b432:01E03460 family sprite in its own colour (0x80 set on start) over a fixed texture window (t 0..0.875, s from f48/1024): from scene count 61 f48 grows 5 to 50; alpha up by 16 to 0x40 until count 120 (ctx+0xCBCC), then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b746_01E04080;

typedef struct {
    f32 s, t;
    Xyz_b746_01E04080 p;
} Tv_b746_01E04080;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b746_01E04080 v[2];
    u8 tail[0x20];
} Tex_b746_01E04080;

typedef struct {
    u8 pad0[0xCBCC];
    s16 count;
} Ctx_b746_01E04080;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b746_01E04080;

static s32 func_01E04080_b746(Ctx_b746_01E04080 *g, Fx_b746_01E04080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b746_01E04080 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    ((Tex_b746_01E04080 *)(s32)&pk)->flags = 0x26;
    ((Tex_b746_01E04080 *)(s32)&pk)->size = 5;
    ((Tex_b746_01E04080 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b746_01E04080 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].t = 0.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = 0.875f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->count > 60) {
        if (o->f48 < 50.0f) {
            o->f48 += 5.0f;
        }
    }
    if (g->count < 120) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b746:01E042C0, 181 insns: b491:01E03360's window (0x90, 0x90, 0x90) in the scene packet at ctx+0xCB38, zoomed by
   f8/10 and fA/10 without tracking anything, drawn once from alpha 0; alpha up by 9 to 0x80 for 110 ticks, then down
   by 7 after tick 40 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b746_01E042C0;

typedef struct {
    f32 s, t;
    Xyz_b746_01E042C0 p;
} Tv_b746_01E042C0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b746_01E042C0 v[2];
} Tex_b746_01E042C0;

typedef struct {
    u8 pad[0xCB38];
    Tex_b746_01E042C0 *pk;
} Game_b746_01E042C0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b746_01E042C0;

static s32 func_01E042C0_b746(Game_b746_01E042C0 *g, Fx_b746_01E042C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x90, 0x90, 0x90);
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = fx / 1024.0f;
    g->pk->v[0].t = fy / 512.0f;
    g->pk->v[1].s = (640.0f - fx) / 1024.0f;
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 110) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->tick > 40) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b746", func_01E045A0_b746);

/* shape b746:01E05080, 106 insns: takes the first free of 400 effect slots (0x70 bytes, b041:01E02C00 shape),
   clears and marks it, colours both from the scene, places it at the scene point, copies its settings and stores both
   arguments */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b746_01E05080;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b746_01E05080 slot[400];
    u8 padEnd[0xCB24 - 0x2A0 - 400 * 0x70];
    u8 col[4];
    u8 padCB28[0x8E];
    s16 hCBB6;
    u8 padCBB8[0xC];
    s16 hCBC4;
} Scene_b746_01E05080;

static s32 func_01E05080_b746(Scene_b746_01E05080 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b746_01E05080 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 400; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 400;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->hCBC4;
        sl->h52 = s->hCBC4;
        sl->h5A = s->hCBB6;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b746:01E05230 (B746KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b746_01E05230 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b746_01E05230;

typedef struct {
    Rgbaq_b746_01E05230 c;
    u64 xyz;
} Vtx_b746_01E05230;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b746_01E05230 v[4];
    u8 tail[0x40];
} Pkt_b746_01E05230;

typedef struct {
    u8 r, g, b, a;
} C4_b746_01E05230;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b746_01E05230 col;
} Rib_b746_01E05230;

static inline u8 b746_01E05230_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E05230_b746(void *o, Rib_b746_01E05230 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b746_01E05230 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b746_01E05230 pkt __attribute__((aligned(8)));
    C4_b746_01E05230 c0;
    C4_b746_01E05230 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b746_01E05230 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b746_01E05230 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    step = s->col.a;
    step /= (s16)(n * 3);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - step > 0) {
                c1.a = b746_01E05230_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E01340_b746(pp, 0, t);
                B[0] = func_01E01340_b746(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E01340_b746(pp, 0, t);
                B[1] = func_01E01340_b746(pq, 0, t);
            } else {
                A[0] = func_01E01340_b746(a4, 0, t);
                B[0] = func_01E01340_b746(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01340_b746(a4, 0, t);
                B[1] = func_01E01340_b746(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

/* shape b746:01E057A0, 89 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0xCB38, ot at
   0xCB34), texture from func_001F53A0, then every used slot (0x190 of 0x70 bytes at 0x2A0) whose
   callback is b746:01E042C0 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b746_01E057A0;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b746_01E057A0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b746_01E057A0 slots[0x190];
    u8 padB1A0[0x1994];
    s32 ot;
    Pkt_b746_01E057A0 *pk;
} Scene_b746_01E057A0;

static void func_01E057A0_b746(Scene_b746_01E057A0 *g) {
    extern void b746_01E042C0(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b746_01E057A0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x190; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b746_01E042C0) {
                b746_01E042C0(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
