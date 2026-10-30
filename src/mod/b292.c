#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b292(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b292(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b292 in the
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

static void func_01E009B0_b292(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b292((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00C70_b292(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b016:01E018F0, 177 insns: b016:01E00ED0 with the view matrix's [2][1] and [3][1] cleared; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b292 in the
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

static void func_01E010B0_b292(Obj_b016_01E018F0 *obj, Cam_b016_01E018F0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b292((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01380_b292(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b292:01E016F0, 244 insns (B292_W_S): the b292 module's event step: counts ticks; at 50, 71, 90 and 126 a ring
   of ten b292:01E01AC0 (36 degrees apart) at the first tracked joint (ctx+0xCB44), at 60, 80, 100 and 126 another at
   the second (ctx+0xCB46); at 107 b292:01E020B0; every other tick from 123 to 150 b292:01E022F0; from 131 to 135 one
   b292:01E01F30 a tick at the third joint (ctx+0xCB4A), numbered by the scene's counter; at 17 four b292:01E01C90
   (turns 0/90/45/135, slots 0/0/1/1) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCB44 - 0x260];
    s16 id1;
    s16 id2;
    u8 padCB48[2];
    s16 id3;
    u8 padCB4C[0xCBA2 - 0xCB4C];
    s16 turn;
    u8 padCBA4[4];
    s16 count;
    u8 padCBAA[0xCBB2 - 0xCBAA];
    s16 slot;
    u8 padCBB4[0xCBBA - 0xCBB4];
    s16 timer;
} Ctx_b292_01E016F0;


#pragma optimization_level 3

static void func_01E016F0_b292(Ctx_b292_01E016F0 *g) {
    extern s32 b292_01E01AC0(void);
    extern s32 b292_01E01C90(void);
    extern s32 b292_01E01F30(void);
    extern s32 b292_01E020B0(void);
    extern s32 b292_01E022F0(void);
    extern void b292_01E02B60(Ctx_b292_01E016F0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 a;

    g->timer++;
    if (g->timer == 50 || g->timer == 71 || g->timer == 90 || g->timer == 126) {
        func_001F5620(func_001F53A0(), g->id1, &g->pos);
        for (i = 0, a = 0; i < 10; i++) {
            g->turn = a;
            b292_01E02B60(g, b292_01E01AC0, 0);
            a += 36;
        }
    }
    if (g->timer == 60 || g->timer == 80 || g->timer == 100 || g->timer == 126) {
        func_001F5620(func_001F53A0(), g->id2, &g->pos);
        for (a = 0, i = 0; a < 10; a++) {
            g->turn = i;
            b292_01E02B60(g, b292_01E01AC0, 0);
            i += 36;
        }
    }
    if (g->timer == 107) {
        b292_01E02B60(g, b292_01E020B0, 0);
    }
    if (g->timer >= 123 && g->timer < 151) {
        if (g->timer % 2 == 1) {
            b292_01E02B60(g, b292_01E022F0, 0);
        }
    }
    if (g->timer == 131 || g->timer == 132 || g->timer == 133 || g->timer == 134 || g->timer == 135) {
        func_001F5620(func_001F53A0(), g->id3, &g->pos);
        g->slot = g->count;
        b292_01E02B60(g, b292_01E01F30, 0);
        g->count++;
    }
    if (g->timer == 17) {
        g->turn = 0;
        g->slot = 0;
        b292_01E02B60(g, b292_01E01C90, 0);
        g->turn = 90;
        g->slot = 0;
        b292_01E02B60(g, b292_01E01C90, 0);
        g->turn = 45;
        g->slot = 1;
        b292_01E02B60(g, b292_01E01C90, 0);
        g->turn = 135;
        g->slot = 1;
        b292_01E02B60(g, b292_01E01C90, 0);
    }
}
#pragma optimization_level reset

typedef struct {
    u8 pad0000[0xCDBC];
    u8 tab[1];
} Mgr_b292_01E01AC0;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b292_01E01AC0;

static s32 func_01E01AC0_b292(Mgr_b292_01E01AC0 *m, Obj_b292_01E01AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 40;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h58 = 2;
        o->f18 += 2.0f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 2.0f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 19;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f18 += 0.5f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.5f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b292:01E01C90, 165 insns, 2 copies: a blue ring travelling between two model joints by kind (radius grows 30/10/0 a
   frame); fades in over 4 frames, then out; each frame it is placed on the first joint and slides toward the
   second by up to 25/25 of the way */

typedef struct {
    u8 pad0[0xCB48];
    s16 j0;
    s16 j1;
} World_b292_01E01C90;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x10];
    f32 thick;
    f32 radius;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    s16 step;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Ring_b292_01E01C90;

static s32 func_01E01C90_b292(World_b292_01E01C90 *w, Ring_b292_01E01C90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    Vec4f v[2];
    f32 k;

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->thick = 3.0f;
            o->radius = 70.0f;
        }
        if (o->kind == 1) {
            o->thick = 3.0f;
            o->radius = 30.0f;
        }
        if (o->kind == 2) {
            o->thick = 8.0f;
            o->radius = 400.0f;
        }
        o->state = 2;
        o->c1[3] = 0;
        o->step = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->kind == 0 && o->t != 0) {
        o->radius += 30.0f;
    }
    if (o->kind == 1 && o->t != 0) {
        o->radius += 10.0f;
    }
    if (o->t != 0) {
        if (o->step < 0x19) {
            o->step++;
        }
    }
    o->t++;
    o->ang += 6;
    func_001F5620(func_001F53A0(), w->j0, &o->pos);
    func_001F5620(func_001F53A0(), w->j1, v);
    k = o->step;
    v[0].x = (v[0].x - o->pos.x) / 25.0f;
    v[0].y = (v[0].y - o->pos.y) / 25.0f;
    v[0].z = (v[0].z - o->pos.z) / 25.0f;
    o->pos.x += v[0].x * k;
    o->pos.y += v[0].y * k;
    o->pos.z += v[0].z * k;
    return 0;
}

/* shape b292:01E01F30, 95 insns: a white flicker slash: width 50, height growing by 40, random sub-frame 0..2 and angle, a quarter
   turn (three quarters when the side flag is set); alpha up by 0x60 for 5 frames, then down by 9 until it ends; flickers white/grey */

typedef struct {
    u8 pad0[0xCBB6];
    s16 side;
} Game_b292_01E01F30;

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
} Obj_b292_01E01F30;

static s32 func_01E01F30_b292(Game_b292_01E01F30 *g, Obj_b292_01E01F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x32;
        o->h = 0;
        o->sub = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        if (g->side != 0) {
            o->rot[0] = 0xC000;
        } else {
            o->rot[0] = 0x4000;
        }
        o->ang = func_0019A5C8() % 360;
    }
    if (o->t < 5) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h += 0x28;
    o->t++;
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    return 0;
}

/* shape b292:01E020B0, 141 insns: b847:01E04A90's two 20-point joint trails (first 19 filled on start) (at +0xB1D0) in green: hE 30; alpha grows by 0x3C (below 0xF0) until scene frame 140, then fades by 9; the trails follow the joints until frame 138; h6 10 */

typedef struct {
    f32 x, y, z, w;
} Pt_b292_01E020B0;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b292_01E020B0 a[20];
    Pt_b292_01E020B0 b[20];
    u8 padB450[0x16F8];
    s16 ja;
    s16 jb;
    u8 padCB4C[0x6E];
    s16 frame;
} Scene_b292_01E020B0;

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
} Fx_b292_01E020B0;

static s32 func_01E020B0_b292(Scene_b292_01E020B0 *g, Fx_b292_01E020B0 *o) {
    extern void b292_01E00080(Pt_b292_01E020B0 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    Pt_b292_01E020B0 *q;

    func_001076F0(o->col, 0x20, 0xC0, 0x20);
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
        o->mode = 2;
    }
    if (g->frame < 0x8C) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->frame < 0x8A) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b292_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b292_01E00080(&g->b[19], 20, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

/* shape b292:01E022F0, 160 insns: b092:01E03090 in 0x80/0x88/0x80 with alpha up by 6 to 0x20 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b292_01E022F0;

typedef struct {
    f32 s, t;
    Xyz_b292_01E022F0 p;
} Tv_b292_01E022F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b292_01E022F0 v[2];
    u8 tail[0x20];
} Tex_b292_01E022F0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b292_01E022F0;

static s32 func_01E022F0_b292(s32 arg0, Fx_b292_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b292_01E022F0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
        func_001076F0(o->col, 0x80, 0x88, 0x80);
    }
    ((Tex_b292_01E022F0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b292_01E022F0 *)(s32)&pk)->size = 5;
    ((Tex_b292_01E022F0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b292_01E022F0 *)(s32)&pk)->pad4 = 0;
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
        if (o->col[3] < 0x20) {
            o->col[3] += 6;
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

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02570_b292(void) {
    return 0;
}

/* shape b292:01E02580 (b292), 375 insns, 1 copy: b292 scene manager in b098:01E01F30 form: setup (six joints, one
   type-4 and four type-5 textures, 256 s8 and 30 s16 jitters), step b292:01E016F0 and every slot except
   b292:01E02570, draw the b292:01E01AC0 rings, b292:01E01C90 quads, twice each b292:01E01F30 sprite and the
   b292:01E020B0 ribbons; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b292_01E02580;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[8];
    } u;
    u8 padA4[0x1A];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b292_01E02580 fx[400];
    u8 padB1A0[0x30];
    u8 ribA[0x140];
    u8 ribB[0x17E0];
    s32 tex[4];
    u8 padCB00[0x10];
    s32 count;
    u8 padCB14[8];
    s32 ot;
    u8 padCB20[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padCB50[4];
    s16 cam;
    u8 padCB56[0xE];
    s16 jit16[30];
    u8 padCBA0[0x16];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padCCBC[0x100];
    u8 crd[0x174];
} Scene_b292_01E02580;

static s32 func_01E02580_b292(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E016F0_b292();
    extern void b292_01E02D00();
    Scene_b292_01E02580 *g = (Scene_b292_01E02580 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xCF30);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 205;
        g->jA = func_001F5560(func_001F53A0(), 0x41, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x49, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x14, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x15, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 4; i++) {
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
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E016F0_b292(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02570_b292) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01AC0_b292) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hBE = g->fx[k].h52;
                func_01E009B0_b292((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C90_b292) {
                g->tex88 = g->tex260[15];
                func_00106080(rm2, 0x9A, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hBE = 0;
                func_01E01380_b292((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F30_b292) {
                g->tex88 = g->tex[g->fx[k].h50 % 3 + 1];
                g->hBE = 0;
                g->u.uv[0] = 0;
                g->u.uv[1] = 0;
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                func_01E010B0_b292((Obj_b016_01E018F0 *)g, &g->fx[k], 0x21, g->fx[k].pos);
                func_01E010B0_b292((Obj_b016_01E018F0 *)g, &g->fx[k], 0x21, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E020B0_b292) {
                b292_01E02D00(g, &g->fx[k], g->ribA, g->ribB);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 121) {
        return 1;
    }
    if (g->frame == 190) {
        return 4;
    }
    if (g->frame == 170) {
        return 2;
    }
    if (g->frame > 131 && g->frame < 165) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b292:01E02B60, 102 insns: take a free effect slot (0x190 of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0xCB14, attach it to the scene position (0x250) and copy it, 0x50 / 0x5A from 0xCBB2 / 0xCBA2, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b292_01E02B60;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b292_01E02B60 slots[0x190];
    u8 padB1A0[0xCB14 - 0xB1A0];
    u8 rgba[4];
    u8 padCB18[0x8A];
    s16 f5As;
    u8 padCBA4[0xE];
    s16 f50s;
} Scene_b292_01E02B60;

static s32 func_01E02B60_b292(Scene_b292_01E02B60 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b292_01E02B60 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x190;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f50 = g->f50s;
        s->f5A = g->f5As;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b292:01E02D00 (B292KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b292_01E02D00 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b292_01E02D00;

typedef struct {
    Rgbaq_b292_01E02D00 c;
    u64 xyz;
} Vtx_b292_01E02D00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b292_01E02D00 v[4];
    u8 tail[0x40];
} Pkt_b292_01E02D00;

typedef struct {
    u8 r, g, b, a;
} C4_b292_01E02D00;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b292_01E02D00 col;
} Rib_b292_01E02D00;

static inline u8 b292_01E02D00_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E02D00_b292(void *o, Rib_b292_01E02D00 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b292_01E02D00 func_00107740(void *);
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
    Pkt_b292_01E02D00 pkt __attribute__((aligned(8)));
    C4_b292_01E02D00 c0;
    C4_b292_01E02D00 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b292_01E02D00 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b292_01E02D00 *)(s32)&pkt;
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
                c1.a = b292_01E02D00_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E00C70_b292(pp, 0, t);
                B[0] = func_01E00C70_b292(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00C70_b292(pp, 0, t);
                B[1] = func_01E00C70_b292(pq, 0, t);
            } else {
                A[0] = func_01E00C70_b292(a4, 0, t);
                B[0] = func_01E00C70_b292(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00C70_b292(a4, 0, t);
                B[1] = func_01E00C70_b292(b4, 0, t);
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
