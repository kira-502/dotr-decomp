#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b092(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b092(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b092 in the
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

static void func_01E009B0_b092(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b092((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00C70_b092(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b016:01E018F0, 177 insns: b016:01E00ED0 with the view matrix's [2][1] and [3][1] cleared; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b092 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E018F0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E018F0;

typedef struct Obj_b016_01E018F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E018F0;

typedef struct Xyz_b016_01E018F0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E018F0;

typedef struct Uv_b016_01E018F0 {
    f32 u, v;
} Uv_b016_01E018F0;

typedef struct Pk_b016_01E018F0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E018F0 uv;
    u64 pad18;
    Xyz_b016_01E018F0 v[4];
    u64 pad60[6];
} Pk_b016_01E018F0;

typedef struct Buf_b016_01E018F0 {
    u64 tag;
    Pk_b016_01E018F0 pk;
} Buf_b016_01E018F0;

static void func_01E00FE0_b092(Obj_b016_01E018F0 *obj, Cam_b016_01E018F0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E018F0 buf;
    Uv_b016_01E018F0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E018F0 *p = &buf.pk;

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
    func_01E00110_b092((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    view[2][1] = 0.0f;
    view[3][1] = 0.0f;
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E012B0_b092(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b092:01E016F0, 730 insns: B092_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0xCBCE);
   frame 1 0x1E02F80, frame 15 eight 0x1E02260 (two sides, four angles), frames 52/78 a ring of eighteen 0x1E02420
   on joints 0xCB5C and 0xCB5E, 0x1E03090 / 0x1E03310 / 0x1E03600 on frame ranges; the mark (0xCAF0) follows joint
   0xCB60; frame 60 two 0x1E02950 22 either side of it, frames 83..88 six 0x1E02AB0 stepping out (mirrored by 0xCBCA) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCAF0 - 0x260];
    Vec4f mark;
    u8 padCB00[0xCB5C - 0xCB00];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 padCB62[0xCBB6 - 0xCB62];
    s16 ang;
    u8 padCBB8[0xCBC4 - 0xCBB8];
    s16 idx;
    s16 side;
    u8 padCBC8[2];
    s16 flag;
    u8 padCBCC[2];
    s16 t;
} Scene_b092_01E016F0;

static void func_01E016F0_b092(Scene_b092_01E016F0 *g) {
    extern void b092_01E02260(void);
    extern void b092_01E02420(void);
    extern void b092_01E02950(void);
    extern void b092_01E02AB0(void);
    extern void b092_01E02F80(void);
    extern void b092_01E03090(void);
    extern void b092_01E03310(void);
    extern void b092_01E03600(void);
    extern void b092_01E040E0(Scene_b092_01E016F0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 a;

    g->t++;
    if (g->t == 1) {
        b092_01E040E0(g, b092_01E02F80, 0);
    }
    if (g->t == 15) {
        g->side = 0;
        g->ang = 45;
        g->idx = 0;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 135;
        g->idx = 0;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 0;
        g->idx = 1;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 90;
        g->idx = 1;
        b092_01E040E0(g, b092_01E02260, 0);
        g->side = 1;
        g->ang = 90;
        g->idx = 0;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 180;
        g->idx = 0;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 45;
        g->idx = 1;
        b092_01E040E0(g, b092_01E02260, 0);
        g->ang = 135;
        g->idx = 1;
        b092_01E040E0(g, b092_01E02260, 0);
    }
    if (g->t == 52 || g->t == 78) {
        for (i = 0, a = 0; i < 18; i++) {
            func_001F5620(func_001F53A0(), g->ja, &g->pos);
            g->ang = a;
            g->pos.y -= 1.0f;
            b092_01E040E0(g, b092_01E02420, 0);
            a += 20;
        }
        for (a = 0, i = 0; a < 18; a++) {
            func_001F5620(func_001F53A0(), g->jb, &g->pos);
            g->ang = i;
            g->pos.y -= 1.0f;
            b092_01E040E0(g, b092_01E02420, 0);
            i += 20;
        }
    }
    if (g->t >= 78 && g->t < 113 && g->t % 2 == 1) {
        b092_01E040E0(g, b092_01E03090, 0);
    }
    if (g->t >= 32 && g->t < 71 && g->t % 5 == 1) {
        b092_01E040E0(g, b092_01E03090, 0);
    }
    if (g->t < 5) {
        b092_01E040E0(g, b092_01E03310, 0);
    }
    if (g->t < 81) {
        b092_01E040E0(g, b092_01E03600, 0);
    }
    func_001F5620(func_001F53A0(), g->jc, &g->mark);
    if (g->t == 60) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.x -= 22.0f;
        } else {
            g->pos.x += 22.0f;
        }
        g->idx = 0;
        b092_01E040E0(g, b092_01E02950, 0);
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.x += 22.0f;
        } else {
            g->pos.x -= 22.0f;
        }
        g->idx = 1;
        b092_01E040E0(g, b092_01E02950, 0);
    }
    if (g->t == 83) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 4.0f;
        } else {
            g->pos.z += 4.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= 20.0f;
        } else {
            g->pos.x += 20.0f;
        }
        g->idx = 0;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
    if (g->t == 84) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 12.0f;
        } else {
            g->pos.z += 12.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= 10.0f;
        } else {
            g->pos.x += 10.0f;
        }
        g->pos.y += 1.0f;
        g->idx = 1;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
    if (g->t == 85) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 24.0f;
        } else {
            g->pos.z += 24.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= 0.0f;
        } else {
            g->pos.x += 0.0f;
        }
        g->pos.y += 2.0f;
        g->idx = 2;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
    if (g->t == 86) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 24.0f;
        } else {
            g->pos.z += 24.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= -10.0f;
        } else {
            g->pos.x += -10.0f;
        }
        g->pos.y += 3.0f;
        g->idx = 3;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
    if (g->t == 87) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 12.0f;
        } else {
            g->pos.z += 12.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= -20.0f;
        } else {
            g->pos.x += -20.0f;
        }
        g->pos.y += 4.0f;
        g->idx = 4;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
    if (g->t == 88) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        if (g->flag != 0) {
            g->pos.z -= 4.0f;
        } else {
            g->pos.z += 4.0f;
        }
        if (g->flag != 0) {
            g->pos.x -= -30.0f;
        } else {
            g->pos.x += -30.0f;
        }
        g->pos.y += 5.0f;
        g->idx = 5;
        b092_01E040E0(g, b092_01E02AB0, 0);
    }
}

typedef struct {
    u8 pad00[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    u8 pad56[2];
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
} Obj_b092_01E02260;

static s32 func_01E02260_b092(s32 unused, Obj_b092_01E02260 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->c60, 0xF0, 0xE0, 0xFF);
        func_001076F0(o->c64, 0xFF, 0xFF, 0x80);
        if (o->h50 == 0) {
            o->f30 = 1.5f;
            o->f34 = 40.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 1.5f;
            o->f34 = 20.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 18.0f;
            o->f34 = 400.0f;
        }
        o->h58 = 2;
        o->c64[3] = 0;
    }
    if (o->h54 < 4) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 16) {
        o->c60[3] -= 15;
    } else {
        o->h58 = 0;
    }
    if (o->h50 == 0) {
        if (o->h54 != 0) {
            o->f34 += 5.0f;
        }
    }
    if (o->h50 == 1) {
        if (o->h54 != 0) {
            o->f34 += 2.5f;
        }
    }
    o->h54++;
    if (o->h52 == 0) {
        o->h5A += 2;
    }
    if (o->h52 == 1) {
        o->h5A += 2;
    }
    return 0;
}

/* shape b092:01E02420, 109 insns: a white drifting spark: size 50, sub-frame 2..4, frame 0..3; pushed 2.6 along its angle at the
   start, then drifting 1 a frame; alpha up by 0x60 for 6 frames, then down by 19 until it ends; turns */

typedef struct {
    u8 pad0[0xCDD0];
    u8 sin[1];
} Game_b092_01E02420;

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
} Obj_b092_01E02420;

static s32 func_01E02420_b092(Game_b092_01E02420 *g, Obj_b092_01E02420 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x32;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->z += 2.6f * func_00108030(g->sin, o->ang, 0);
        o->x += 2.6f * func_00108030(g->sin, o->ang, 1);
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
        o->z += func_00108030(g->sin, o->ang, 0);
        o->x += func_00108030(g->sin, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b092:01E025E0, 218 insns: b256:01E02540's drifting spark with the scene counter at ctx+0xCBCE */

typedef struct {
    u8 pad0[0xCBCE];
    s16 count;
} Ctx_b092_01E025E0;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b092_01E025E0;

static s32 func_01E025E0_b092(Ctx_b092_01E025E0 *ctx, Obj_b092_01E025E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = func_0019A5C8() % 3 + 3;
        o->hA = o->h8 + 4;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f38 = func_0019A5C8() % 100 - 50;
        o->f34 /= 100.0f;
        o->f30 /= 100.0f;
        o->f38 /= 100.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->h8 < 11) {
            o->h8++;
        }
        if (o->hA < o->h8 + 4) {
            o->hA++;
        }
    }
    if (o->t != 0) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    if (ctx->count > 445) {
        o->t = 90;
    }
    return 0;
}

/* shape b092:01E02950, 87 insns: a white flickering growing spark (b252:01E03410 family): square size 200 growing by 2, random
   sub-frame 0..2 and angle; alpha up by 0x60 to 0xC0 for 10 frames, then down by 9 until it ends; random turn; colour
   flickers by frame parity */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 c0[4];
} Obj_b092_01E02950;

static s32 func_01E02950_b092(void *arg0, Obj_b092_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0xC8;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = func_0019A5C8() % 360;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    o->w += 2;
    o->h = o->w;
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    return 0;
}

/* shape b092:01E02AB0, 100 insns: on start 0x8/0xA = 70/80, variant 0..2, colour white, rotation 0xC000 when the game
   flag 0xCBCA is set else 0x4000, random 0x5C; alpha grows by 0x60 (below 0xC0) for 8 ticks, then fades by 9 and
   stops; from tick 3 0xA grows by 40; the colour flickers grey */

typedef struct {
    u8 pad0[0xCBCA];
    s16 flag;
} Game_b092_01E02AB0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot;
    u8 pad24[0x30];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b092_01E02AB0;

static s32 func_01E02AB0_b092(Game_b092_01E02AB0 *g, Fx_b092_01E02AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 70;
        o->fA = 80;
        o->f56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        if (g->flag != 0) {
            o->rot = 0xC000;
        } else {
            o->rot = 0x4000;
        }
        o->f5C = func_0019A5C8() % 360;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick > 2) {
        o->fA += 40;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    return 0;
}

/* shape b092:01E02C40, 206 insns: b415:01E02A90's two joint trails in red (0xC0, 0x20, 0x20): trail A follows
   joint 0xCB64, trail B the point mirrored past it from joint 0xCB62 (p + 2 (q - p)); frame at 0xCBCE, alpha up by
   0x3C to 0xF0 until frame 100, then down by 9; trails move until frame 88; h6 10 */

typedef struct {
    f32 x, y, z, w;
} Pt_b092_01E02C40;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b092_01E02C40 a[20];
    Pt_b092_01E02C40 b[20];
    u8 padB450[0xCB62 - 0xB450];
    s16 ja;
    s16 jb;
    u8 padCB66[0xCBCE - 0xCB66];
    s16 frame;
} Scene_b092_01E02C40;

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
} Fx_b092_01E02C40;

static s32 func_01E02C40_b092(Scene_b092_01E02C40 *g, Fx_b092_01E02C40 *o) {
    extern void b092_01E00080(Pt_b092_01E02C40 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    f32 d[4];
    s16 i;
    s16 j;
    Pt_b092_01E02C40 *q;

    func_001076F0(o->col, 0xC0, 0x20, 0x20);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->hE = 30;
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->a;
        for (i = 0; i < 19; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->ja, d);
        d[0] = 2.0f * (d[0] - p[0]);
        d[1] = 2.0f * (d[1] - p[1]);
        d[2] = 2.0f * (d[2] - p[2]);
        p[0] = p[0] + d[0];
        p[1] = p[1] + d[1];
        p[2] = p[2] + d[2];
        q = g->b;
        for (j = 0; j < 19; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        o->mode = 2;
    }
    if (g->frame < 100) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->frame < 88) {
        func_001F5620(func_001F53A0(), g->jb, p);
        b092_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->ja, d);
        d[0] = 2.0f * (d[0] - p[0]);
        d[1] = 2.0f * (d[1] - p[1]);
        d[2] = 2.0f * (d[2] - p[2]);
        p[0] = p[0] + d[0];
        p[1] = p[1] + d[1];
        p[2] = p[2] + d[2];
        b092_01E00080(&g->b[19], 20, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

/* shape b092:01E02F80, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x33, floor 0x30, state at 0xCB20 below 0x1E */

typedef struct {
    u8 pad[0xCB20];
    s32 state;
} Game_b092_01E02F80;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b092_01E02F80;

static s32 func_01E02F80_b092(Game_b092_01E02F80 *g, Fade_b092_01E02F80 *o) {
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
    } else if (g->state < 0x1E) {
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

/* shape b092:01E03090, 160 insns: b432:01E03460 family sprite in 0x90/0x70/0x80 zooming in 0.3 per tick to 100 with alpha up by 4 to 0x18 for 15 ticks, then zooming out 0.2 to 0 with alpha down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b092_01E03090;

typedef struct {
    f32 s, t;
    Xyz_b092_01E03090 p;
} Tv_b092_01E03090;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b092_01E03090 v[2];
    u8 tail[0x20];
} Tex_b092_01E03090;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b092_01E03090;

static s32 func_01E03090_b092(s32 arg0, Fx_b092_01E03090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b092_01E03090 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
        func_001076F0(o->col, 0x90, 0x70, 0x80);
    }
    ((Tex_b092_01E03090 *)(s32)&pk)->flags = 0x26;
    ((Tex_b092_01E03090 *)(s32)&pk)->size = 5;
    ((Tex_b092_01E03090 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b092_01E03090 *)(s32)&pk)->pad4 = 0;
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
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->tick < 15) {
        if (o->col[3] < 0x18) {
            o->col[3] += 4;
        }
        if (o->f48 < 100.0f) {
            o->f48 += 0.3f;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->f48 > 0.0f) {
            o->f48 -= 0.2f;
        } else {
            o->f48 = 0.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b092:01E03310, 187 insns: b256:01E03DC0 in red (0x80, 0x20, 0x20) through ctx+0xCB38, fading out from scene count 125 (ctx+0xCBCE) and ending at 135 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b092_01E03310;

typedef struct {
    f32 s, t;
    Xyz_b092_01E03310 p;
} Tv_b092_01E03310;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b092_01E03310 v[2];
} Tex_b092_01E03310;

typedef struct {
    u8 pad[0xCB38];
    Tex_b092_01E03310 *pk;
    u8 padCB3C[0xCBCE - 0xCB3C];
    s16 count;
} Game_b092_01E03310;

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
} Fx_b092_01E03310;

static s32 func_01E03310_b092(Game_b092_01E03310 *g, Fx_b092_01E03310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
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
    if (g->count < 125) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (g->count >= 135) {
        o->mode = 0;
    }
    return 0;
}

/* shape b092:01E03600, 210 insns: b152:01E03400's full-screen overlay in grey 0x40 at alpha 0x78 (packet at
   ctx+0xCB38), the texture inset growing by 60..99 a frame; after the first frame it fades by 49 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b092_01E03600;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b092_01E03600 p;
    } v[2];
} Pkt_b092_01E03600;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b092_01E03600;

typedef struct {
    u8 pad0[0xCB38];
    Pkt_b092_01E03600 *pkt;
} Scene_b092_01E03600;

static s32 func_01E03600_b092(Scene_b092_01E03600 *s, Slot_b092_01E03600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 w;
    f32 h;

    w = o->w;
    h = o->h;
    w /= 10.0f;
    h /= 10.0f;
    if (o->state == 1) {
        o->c0[3] = 0x78;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->state = 2;
    }
    s->pkt->r = o->c0[0];
    s->pkt->g = o->c0[1];
    s->pkt->b = o->c0[2];
    s->pkt->a = o->c0[3];
    s->pkt->q = 1.0f;
    s->pkt->v[0].p.x = 0x6BF8;
    s->pkt->v[0].p.y = 0x71F8;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[0].p.f = 0;
    s->pkt->v[1].p.x = 0x93F8;
    s->pkt->v[1].p.y = 0x8DF8;
    s->pkt->v[1].p.z = 0xFFFFFF;
    s->pkt->v[1].p.f = 0;
    s->pkt->v[0].s = w / 1024.0f;
    s->pkt->v[0].t = h / 512.0f;
    s->pkt->v[1].s = (640.0f - w) / 1024.0f;
    s->pkt->v[1].t = (448.0f - h) / 512.0f;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[1].p.z = 0xFFFFFF;
    func_002075F0(s->pkt, 0, 0);
    o->w += (s16)(func_0019A5C8() % 40 + 60);
    o->h += (s16)(func_0019A5C8() % 40 + 60);
    if (o->t != 0) {
        if (o->c0[3] > 40) {
            o->c0[3] -= 49;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b092", func_01E03950_b092);

/* shape b092:01E040E0, 106 insns: takes the first free of 400 effect slots (0x70 bytes, b569:01E02B80 shape), clears and
   marks it, colours both from the scene, places it at the scene point, copies three settings and stores both arguments */

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
} Slot_b092_01E040E0;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b092_01E040E0 slot[400];
    u8 padEnd[0xCB24 - 0x2A0 - 400 * 0x70];
    u8 col[4];
    u8 padCB28[0x8E];
    s16 hCBB6;
    u8 padCBB8[0xC];
    s16 hCBC4;
    s16 hCBC6;
} Scene_b092_01E040E0;

static s32 func_01E040E0_b092(Scene_b092_01E040E0 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b092_01E040E0 *sl;
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
        sl->h52 = s->hCBC6;
        sl->h5A = s->hCBB6;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b092:01E04290 (B092KPOINT_RAIN_3), 347 insns, 9 copies: draws a ribbon between two point trails like
   b256:01E04AB0, 4 spline quads per segment; the far edge fades by the colour alpha / (3n) each quad */

typedef struct Rgbaq_b092_01E04290 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b092_01E04290;

typedef struct {
    Rgbaq_b092_01E04290 c;
    u64 xyz;
} Vtx_b092_01E04290;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b092_01E04290 v[4];
    u8 tail[0x40];
} Pkt_b092_01E04290;

typedef struct {
    u8 r, g, b, a;
} C4_b092_01E04290;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b092_01E04290 col;
} Rib_b092_01E04290;

static inline u8 b092_01E04290_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E04290_b092(void *o, Rib_b092_01E04290 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b092_01E04290 func_00107740(void *);
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
    Pkt_b092_01E04290 pkt __attribute__((aligned(8)));
    C4_b092_01E04290 c0;
    C4_b092_01E04290 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b092_01E04290 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b092_01E04290 *)(s32)&pkt;
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
                c1.a = b092_01E04290_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E012B0_b092(pp, 0, t);
                B[0] = func_01E012B0_b092(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E012B0_b092(pp, 0, t);
                B[1] = func_01E012B0_b092(pq, 0, t);
            } else {
                A[0] = func_01E012B0_b092(a4, 0, t);
                B[0] = func_01E012B0_b092(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E012B0_b092(a4, 0, t);
                B[1] = func_01E012B0_b092(b4, 0, t);
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

/* shape b092:01E04800, 97 insns: the module's draw pass (b016:01E03880 shape): opens a sprite packet on the stack, then
   runs every live slot (400 of 0x70 bytes) whose handler is shape b092:01E03310 through it; queues the batch only if any
   slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b092_01E04800;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b092_01E04800 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b092_01E04800;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b092_01E04800;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b092_01E04800 slot[400];
    u8 padEnd[0xCB34 - 0x2A0 - 400 * 0x70];
    s32 ctx;
    Pkt_b092_01E04800 *pkt;
} Scene_b092_01E04800;

static void func_01E04800_b092(Scene_b092_01E04800 *s) {
    extern void b092_01E03310(Scene_b092_01E04800 *, Slot_b092_01E04800 *);
    extern void b092_01E03600(Scene_b092_01E04800 *, Slot_b092_01E04800 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b092_01E04800 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b092_01E03310) {
                b092_01E03310(s, &s->slot[i]);
            }
            if (s->slot[i].fn == (void *)b092_01E03600) {
                b092_01E03600(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
