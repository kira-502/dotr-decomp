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

static void func_01E00080_b414(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b414(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b414 in the
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

static void func_01E00C80_b414(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b414((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00F40_b414(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E012B0_b414(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

/* shape b414:01E016B0, 342 insns: B414_W_S, the scene script: counts the scene frame (0xB2BA) and spawns the module's
   movers on it: two on frame 1, one on 193, four rings at the first joint on 158 and two more on 59, the two kinds of
   aura every frame before 141, one at each of five joints (0xB248) on frames 116..144, two more every frame before
   133, a mover between two joints on 194..229, and on 220 a burst of 40 + 20 + the flash */

typedef struct {
    u8 pad0000[0x250];
    Vec4f p;
    u8 pad0260[0xB244 - 0x260];
    s16 j0;
    u8 padB246[2];
    s16 joints[5];
    u8 padB252[0xB2A2 - 0xB252];
    s16 ang;
    u8 padB2A4[0xC];
    s16 kind;
    u8 padB2B2[8];
    s16 frame;
} Ctx_b414_01E016B0;

static void func_01E016B0_b414(Ctx_b414_01E016B0 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void b414_01E04110();
    extern s32 b414_01E01C10();
    extern s32 b414_01E01E00();
    extern s32 b414_01E01FF0();
    extern s32 b414_01E021C0();
    extern s32 b414_01E02420();
    extern s32 b414_01E026F0();
    extern s32 b414_01E029C0();
    extern s32 b414_01E02C20();
    extern s32 b414_01E02D80();
    extern s32 b414_01E02E70();
    extern s32 b414_01E03070();
    extern s32 b414_01E03390();
    extern s32 b414_01E03510();
    s16 i;

    g->frame++;
    if (g->frame == 1) {
        b414_01E04110(g, b414_01E03390, 0);
    }
    if (g->frame == 1) {
        b414_01E04110(g, b414_01E03070, 0);
    }
    if (g->frame == 193) {
        b414_01E04110(g, b414_01E03510, 0);
    }
    if (g->frame == 158) {
        func_001F5620(func_001F53A0(), g->j0, &g->p);
        g->ang = 0;
        g->kind = 0;
        b414_01E04110(g, b414_01E01C10, 0);
        g->ang = 90;
        g->kind = 0;
        b414_01E04110(g, b414_01E01C10, 0);
        g->ang = 45;
        g->kind = 1;
        b414_01E04110(g, b414_01E01C10, 0);
        g->ang = 135;
        g->kind = 1;
        b414_01E04110(g, b414_01E01C10, 0);
    }
    if (g->frame == 59) {
        func_001F5620(func_001F53A0(), g->j0, &g->p);
        g->ang = 0;
        g->kind = 2;
        b414_01E04110(g, b414_01E01C10, 0);
        g->ang = 90;
        g->kind = 2;
        b414_01E04110(g, b414_01E01C10, 0);
    }
    if (g->frame < 141) {
        for (i = 0; i < 2; i++) {
            g->kind = i;
            if (i == 0) {
                b414_01E04110(g, b414_01E01E00, 0);
            } else {
                b414_01E04110(g, b414_01E01FF0, 0);
            }
        }
    }
    if (g->frame < 145 && g->frame > 115) {
        for (i = 0; i < 5; i++) {
            func_001F5620(func_001F53A0(), g->joints[i], &g->p);
            b414_01E04110(g, b414_01E021C0, 0);
        }
    }
    if (g->frame < 133) {
        for (i = 0; i < 1; i++) {
            b414_01E04110(g, b414_01E02420, 0);
        }
    }
    if (g->frame < 133) {
        for (i = 0; i < 1; i++) {
            b414_01E04110(g, b414_01E026F0, 0);
        }
    }
    if (g->frame > 193 && g->frame < 230) {
        func_001F5620(func_001F53A0(), g->joints[3], &g->p);
        func_001F5620(func_001F53A0(), g->j0, &g->p);
        b414_01E04110(g, b414_01E029C0, 0);
    }
    if (g->frame == 220) {
        func_001F5620(func_001F53A0(), g->j0, &g->p);
        for (i = 0; i < 40; i++) {
            b414_01E04110(g, b414_01E02E70, 0);
        }
        for (i = 0; i < 20; i++) {
            b414_01E04110(g, b414_01E02C20, 0);
        }
        b414_01E04110(g, b414_01E02D80, 0);
    }
}

/* shape b414:01E01C10, 123 insns: b588:01E025F0 family (orange 0xF0/0xE0 + 0x80/0x40): kind 0 from 1000 growing 60, kind 1 from 250 growing 20, kind 2 from 100 growing 5 in grey/blue and turning 6 per tick */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b414_01E01C10;

static s32 func_01E01C10_b414(s32 arg0, Obj_b414_01E01C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
        func_001076F0(o->col2, 0x80, 0x40, 0xFF);
        if (o->h50 == 0) {
            o->f30 = 18.0f;
            o->f34 = 1000.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 18.0f;
            o->f34 = 250.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 6.0f;
            o->f34 = 100.0f;
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 60.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 20.0f;
    }
    if (o->h50 == 2) {
        if (o->t != 0) {
            o->f34 += 5.0f;
        }
        o->ang += 6;
    }
    o->t++;
    return 0;
}

/* shape b414:01E01E00, 119 insns: a white/red ring (size 15, spin 60/6, random angle, turned +-0x1000 by the scene side flag) on the scene joint, rising 30..79 then 13 a tick (65 and growing 2 once the scene value reaches 115, else growing 0.5): in by 96 up to 0xC0 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b414_01E01E00;

typedef struct {
    u8 pad[0xB250];
    s16 joint;
    u8 padB252[0x64];
    s16 side;
    u8 padB2B8[2];
    s16 val;
} Game_b414_01E01E00;

static s32 func_01E01E00_b414(Game_b414_01E01E00 *g, Obj_b414_01E01E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f4C = 15.0f;
        o->f48 = 15.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->h52 = func_0019A5C8() % 360;
        o->h5A = 60;
        o->h5C = 6;
        o->mode = 2;
        o->col2[3] = 0;
        o->f34 = -(func_0019A5C8() % 50 + 30);
        if (g->side != 0) {
            o->w20 = -0x1000;
        } else {
            o->w20 = 0x1000;
        }
    }
    if (o->t < 4) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->val < 115) {
        o->f34 -= 13.0f;
        o->f4C += 0.5f;
    } else {
        o->f34 -= 65.0f;
        o->f4C += 2.0f;
    }
    func_001F5620(func_001F53A0(), g->joint, &o->x);
    o->t++;
    return 0;
}

/* shape b414:01E01FF0, 113 insns: a white-red falling ring: sizes 11 (the outer growing by 0.5, by 2 once the scene timer reaches
   115), random angle, a sixteenth turn one way or the other by the scene side, falling from -15..-44 by 5 (35 late); second
   alpha up by 0x60 for 4 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0xB2B6];
    s16 side;
    u8 padB2B8[2];
    s16 timer;
} Game_b414_01E01FF0;

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    u8 pad24[0x10];
    f32 fall;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 ang;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b414_01E01FF0;

static s32 func_01E01FF0_b414(Game_b414_01E01FF0 *g, Obj_b414_01E01FF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 11.0f;
        o->f48 = 11.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0xFF, 0x40, 0x40);
        o->ang = func_0019A5C8() % 360;
        o->h5A = 0x3C;
        o->h5C = 6;
        o->state = 2;
        o->c1[3] = 0;
        o->fall = -(func_0019A5C8() % 30 + 0xF);
        if (g->side != 0) {
            o->rot0 = -0x1000;
        } else {
            o->rot0 = 0x1000;
        }
    }
    if (o->t < 4) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xA) {
        o->c1[3] -= 9;
    } else {
        o->state = 0;
    }
    if (g->timer < 0x73) {
        o->fall -= 5.0f;
        o->f4C += 0.5f;
    } else {
        o->fall -= 35.0f;
        o->f4C += 2.0f;
    }
    o->t++;
    return 0;
}

/* shape b414:01E021C0, 150 insns: b432:01E02FA0's tumbling chip in red (0xFF, 0x40, 0x40), frame 0..2, drift / 100, held 10, fading by 9, growing by 5 to 100 (0xA follows) */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b414_01E021C0;

static s32 func_01E021C0_b414(s32 arg0, Fx_b414_01E021C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 30;
        o->size0 = o->size;
        o->frame = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 100.0f;
        o->vx /= 100.0f;
        o->vz /= 100.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (o->size < 100) {
            o->size += 5;
        }
        o->size0 = o->size;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b414:01E02420, 177 insns: a red (0xFF, 0x40, 0x40) streak 18 x 10, frame 0..2, drifting (-50..49)/100 with random spins; alpha up by 0x40 to 0x80 for 10 ticks, then down by 9; grows 5, 10 or 60 (and 2 wider) by the scene level (ctx+0xB2BA: under 90 / 121); turned 0x7000 / 0x9000 by the scene flag (ctx+0xB2B6) */

typedef struct {
    u8 pad0[0xB2B6];
    s16 flag;
    u8 padF[0xB2BA - 0xB2B6 - 2];
    s16 level;
} Ctx_b414_01E02420;

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b414_01E02420;

static s32 func_01E02420_b414(Ctx_b414_01E02420 *g, Fx_b414_01E02420 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 18;
        o->h = 10;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 100.0f;
        o->vel[0] /= 100.0f;
        o->vel[2] /= 100.0f;
        o->f5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (g->level < 90) {
            o->h += 5;
        } else if (g->level < 121) {
            o->h += 10;
        } else {
            o->h += 60;
            o->w += 2;
        }
    }
    o->rot[1] = 0;
    o->rot[2] = 0;
    if (g->flag != 0) {
        o->rot[0] = 0x7000;
    } else {
        o->rot[0] = 0x9000;
    }
    o->tick++;
    return 0;
}

/* shape b414:01E026F0, 177 insns: b414:01E021C0's chip in grey 0x80, size 25, 0xA from 10 growing 10 (20 from scene
   frame 90, then 70 with the size growing 2 from 121); it keeps only a yaw of 0x7000 or 0x9000 by the scene flag */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b414_01E026F0;

typedef struct {
    u8 pad0[0xB2B6];
    s16 flag;
    u8 padB2B8[2];
    s16 frame;
} Scene_b414_01E026F0;

static s32 func_01E026F0_b414(Scene_b414_01E026F0 *g, Fx_b414_01E026F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 25;
        o->size0 = 10;
        o->frame = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 100.0f;
        o->vx /= 100.0f;
        o->vz /= 100.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (g->frame < 90) {
            o->size0 += 10;
        } else if (g->frame < 121) {
            o->size0 += 20;
        } else {
            o->size0 += 70;
            o->size += 2;
        }
    }
    o->rot[1] = 0;
    o->rot[2] = 0;
    if (g->flag != 0) {
        o->rot[0] = 0x7000;
    } else {
        o->rot[0] = 0x9000;
    }
    o->t++;
    return 0;
}

/* shape b414:01E029C0, 152 insns: b414:01E021C0 with size 70 growing to 140, size0 twice the size, a dark red colour
   (0x80/0x40/0x40), and a fade-out by 5 */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b414_01E029C0;

static s32 func_01E029C0_b414(s32 arg0, Fx_b414_01E029C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 70;
        o->size0 = o->size * 2;
        o->frame = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x40, 0x40);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 100.0f;
        o->vx /= 100.0f;
        o->vz /= 100.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (o->size < 140) {
            o->size += 5;
        }
        o->size0 = o->size * 2;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b414:01E02C20, 85 insns: b499:01E01C50 family: a white tumbling shape at three random turns that grows 7 up to 130 and climbs 2 a tick from 5 (size from 10, +1 a tick); ends at 181; past 60 both alphas drop by 9 */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    u8 pad8[0x18];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[0xC];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b414_01E02C20;

static s32 func_01E02C20_b414(s32 arg0, Obj_b414_01E02C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h6 < 130) {
        o->h6 += 7;
    }
    o->h2 += 2;
    func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    if (o->h2 > 180) {
        o->mode = 0;
    }
    if (o->mode == 1) {
        o->h2 = 5;
        o->h0 = 0;
        o->h4 = 0;
        o->h6 = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->col[3] = 0xC0;
        o->f48 = 10.0f;
        o->mode = 2;
    }
    if (o->h2 >= 60) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        }
    }
    o->f48 += 1.0f;
    return 0;
}

/* shape b414:01E02D80, 59 insns: constant variant of b415:01E022B0 (colour (128, 128, 128), colour (128, 64, 64)) */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 vol;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b414_01E02D80;

static s32 func_01E02D80_b414(s32 arg0, Fx_b414_01E02D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 220.0f;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0x80, 0x40, 0x40);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xE) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 0xA) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b414:01E02E70, 125 insns: constant variant of b354:01E020F0 (50->80, 100->160, 8->18, 80.0f->120.0f, colour (192, 128, 128), colour (192, 128, 128), colour (255, 160, 160), colour (48, 48, 48)) */

typedef struct {
    u8 pad00[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b414_01E02E70;

static s32 func_01E02E70_b414(void *arg0, Obj_b414_01E02E70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 120.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0xC0, 0x80, 0x80);
            func_001076F0(o->col2, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->col, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        }
        o->h5A = 30;
        o->h5C = 30;
        o->f34 = func_0019A5C8() % 80 + 160;
        o->f34 /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 18) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

/* shape b414:01E03070, 197 insns: b388:01E007F0's scene light (128, 4, 0, 0): before scene value 221 it sits 1.5x
   beyond the effect point, away from joint 0xB246 (the effect point follows joint 0xB250), radius grows by 5 to 100;
   before 251 the level grows by 0.05 to 1, then c[1] flickers 4/5 every other tick; after that the level drops by 0.1
   and the light ends; also ends when 0xB210 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b414_01E03070;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b414_01E03070 light;
    u8 padB1CC[0x44];
    s32 flag;
    u8 padB214[0x32];
    s16 joint2;
    u8 padB248[8];
    s16 joint;
    u8 padB252[0x68];
    s16 val;
} Scene_b414_01E03070;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x34];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fx_b414_01E03070;

static s32 func_01E03070_b414(Scene_b414_01E03070 *g, Fx_b414_01E03070 *o) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    f32 d[4];

    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 4.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 10.0f;
        g->light.level = 0.0f;
        o->mode = 2;
        o->h50 = 0;
    }
    if (g->val < 221) {
        func_001F5620(func_001F53A0(), g->joint, &o->x);
        func_001F5620(func_001F53A0(), g->joint2, d);
        d[0] = 1.5f * (o->x - d[0]);
        d[1] = 1.5f * (o->y - d[1]);
        d[2] = 1.5f * (o->z - d[2]);
        g->light.pos.x = o->x + d[0];
        g->light.pos.y = o->y + d[1];
        g->light.pos.z = o->z + d[2];
        if (g->light.fC4 < 100.0f) {
            g->light.fC4 += 5.0f;
        }
    }
    if (g->val < 251) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.05f;
        } else if (o->t % 2 == 1) {
            g->light.c[1] = 4.0f;
        } else {
            g->light.c[1] = 5.0f;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    o->t++;
    return 0;
}

/* shape b414:01E03390, 95 insns: a screen-darkness level: starts at 0x80, drops by 10 to 0x20 until frame 140, by 2 to 0x10 until
   190, rises by 3 to 0x30 until 210, then back up by 10 to 0x80 while the scene timer is under 30; sets the level each frame,
   ending at full when the scene timer hits 3 */

typedef struct {
    u8 pad0[0xB210];
    s32 timer;
} Scene_b414_01E03390;

typedef struct {
    u8 pad0[0x50];
    s16 level;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
} Obj_b414_01E03390;

static s32 func_01E03390_b414(Scene_b414_01E03390 *g, Obj_b414_01E03390 *o) {
    extern void func_001F6D00(s32);

    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (o->t < 0xD2) {
        if (o->t < 0x8C) {
            if (o->level > 0x20) {
                o->level -= 0xA;
            } else {
                o->level = 0x20;
            }
        } else if (o->t < 0xBE) {
            if (o->level > 0x10) {
                o->level -= 2;
            } else {
                o->level = 0x10;
            }
        } else if (o->t < 0xD2) {
            if (o->level < 0x30) {
                o->level += 3;
            } else {
                o->level = 0x30;
            }
        }
    } else if (g->timer < 0x1E) {
        if (o->level < 0x80) {
            o->level += 0xA;
        } else {
            o->level = 0x80;
        }
        if (o->level > 0x80) {
            o->level = 0x80;
        }
    }
    o->t++;
    if (g->timer == 3) {
        func_001F6D00(0x80);
        o->state = 0;
    } else {
        func_001F6D00((u8)o->level);
    }
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b414:01E03510, 117 insns: draw a fixed screen sprite (one texture cell, far depth) in the object's colour;
   fades in once the scene counter passes 20 */

typedef struct Xyz_b414_01E03510 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b414_01E03510;

typedef struct Pk_b414_01E03510 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    Xyz_b414_01E03510 v0;
    f32 s1, t1;
    Xyz_b414_01E03510 v1;
    u8 pad40[0x20];
} Pk_b414_01E03510;

typedef struct Sp_b414_01E03510 {
    u8 pad0[0x48];
    s32 f48;
    u8 pad4C[8];
    s16 age;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Sp_b414_01E03510;

typedef struct Scn_b414_01E03510 {
    u8 pad0[0xB210];
    s32 count;
} Scn_b414_01E03510;

static inline void b414_01E03510_tag(Pk_b414_01E03510 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E03510_b414(Scn_b414_01E03510 *w, Sp_b414_01E03510 *o) {
    extern s32 func_001076F0();
    Pk_b414_01E03510 pk __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0;
        func_001076F0(o->col, 0x98, 0x80, 0x80);
        o->state = 2;
    }
    b414_01E03510_tag((Pk_b414_01E03510 *)(u32)&pk, 5, 0x26, 0x42421);
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v0.x = 0x6BF8;
    pk.v0.y = 0x71F8;
    pk.v0.z = 0xFFFFFF;
    pk.v0.fog = 0;
    pk.v1.x = 0x93F8;
    pk.v1.y = 0x8DF8;
    pk.v1.z = 0xFFFFFF;
    pk.v1.fog = 0;
    pk.s0 = 0.0f;
    pk.t0 = 0.0f;
    pk.s1 = 0.625f;
    pk.t1 = 0.875f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (w->count > 0x14) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x14;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->age++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E036F0_b414(void) {
    return 0;
}

/* shape b414:01E03700 (b414), 643 insns, 1 copy: b414 scene manager in b413:01E03E70 form: setup (seven joints, 256
   s8 and 30 s16 jitters), step every slot but 01E036F0, draw ten handler kinds; scene code from the frame */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    s16 h52;
    u8 pad54[0x2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b414_01E03700;

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
    union {
        s32 rm[4];
        s16 uv[4];
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b414_01E03700 fx[400];
    u8 padB1A0[0x50];
    s32 tex[3];
    u8 padB1FC[0x14];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    s16 jG;
    u8 padB252[2];
    s16 cam;
    u8 padB256[0xE];
    s16 jit16[30];
    u8 padB2A0[0x16];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BC[0x100];
    u8 crd[0x174];
} Scene_b414_01E03700;

static s32 func_01E03700_b414(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern s32 func_01E036F0_b414();
    extern s32 func_01E01C10_b414();
    extern s32 func_01E01E00_b414();
    extern s32 func_01E01FF0_b414();
    extern s32 func_01E021C0_b414();
    extern s32 func_01E02420_b414();
    extern s32 func_01E026F0_b414();
    extern s32 func_01E029C0_b414();
    extern s32 func_01E02C20_b414();
    extern s32 func_01E02D80_b414();
    extern s32 func_01E02E70_b414();
    extern void b414_01E016B0();
    extern void func_01E00F40_b414();
    extern void func_01E00C80_b414();
    extern void func_01E00920_b414();
    extern void func_01E012B0_b414();
    extern void b414_01E042C0();
    extern void b414_01E04620();
    extern void b414_01E04810();
    Scene_b414_01E03700 *g = (Scene_b414_01E03700 *)arg0;
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
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 300;
        g->jA = func_001F5560(func_001F53A0(), 0xC, 1);
        g->jB = func_001F5560(func_001F53A0(), 3, 0);
        g->jC = func_001F5560(func_001F53A0(), 4, 0);
        g->jD = func_001F5560(func_001F53A0(), 5, 0);
        g->jE = func_001F5560(func_001F53A0(), 6, 0);
        g->jF = func_001F5560(func_001F53A0(), 7, 0);
        g->jG = func_001F5560(func_001F53A0(), 8, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
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
    b414_01E016B0(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E036F0_b414) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01C10_b414) {
                g->tex88 = g->tex260[15];
                func_00106080(rm, 0x9A, 0, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hBE = 0;
                if (g->fx[k].h50 < 2) {
                    func_01E00F40_b414(g, &g->fx[k], 0, g->fx[k].pos);
                    func_01E00F40_b414(g, &g->fx[k], 0, g->fx[k].pos);
                } else if (g->fx[k].h50 == 2) {
                    func_01E00F40_b414(g, &g->fx[k], 0, g->fx[k].pos);
                }
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E00_b414) {
                g->hB8 = 6;
                b414_01E042C0(g, &g->fx[k], 0x21, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01FF0_b414) {
                g->hB8 = 6;
                func_001F5620(func_001F53A0(), g->jF, &g->fx[k].pos);
                b414_01E042C0(g, &g->fx[k], 0x21, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jE, &g->fx[k].pos);
                b414_01E042C0(g, &g->fx[k], 0x21, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jD, &g->fx[k].pos);
                b414_01E042C0(g, &g->fx[k], 0x21, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jC, &g->fx[k].pos);
                b414_01E042C0(g, &g->fx[k], 0x21, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021C0_b414) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u94.uv[0] = g->fx[k].h56 << 6;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u94.uv[1] = 0x40;
                }
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                func_01E00C80_b414(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02420_b414) {
                g->tex88 = g->tex[2];
                g->hBE = 0;
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                func_001F5620(func_001F53A0(), g->jF, &g->fx[k].pos);
                b414_01E04620(g, &g->fx[k], 0x20, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jE, &g->fx[k].pos);
                b414_01E04620(g, &g->fx[k], 0x20, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jD, &g->fx[k].pos);
                b414_01E04620(g, &g->fx[k], 0x20, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jC, &g->fx[k].pos);
                b414_01E04620(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E026F0_b414) {
                g->tex88 = g->tex[2];
                g->hBE = 0;
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                func_001F5620(func_001F53A0(), g->jG, &g->fx[k].pos);
                b414_01E04620(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E029C0_b414) {
                g->tex88 = g->tex[2];
                g->hBE = 0;
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                func_01E00C80_b414(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02C20_b414) {
                g->tex88 = g->tex[2];
                g->hBE = 0;
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                b414_01E04810(g, &g->fx[k], 0);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D80_b414) {
                g->hB8 = 0x24;
                func_01E00920_b414(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02E70_b414) {
                func_00106080(rm3, 0x96, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex260[15];
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 12;
                g->hBE = 0;
                func_01E012B0_b414(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 195) {
        return 1;
    }
    if (g->frame == 290) {
        return 4;
    }
    if (g->frame == 265) {
        return 2;
    }
    if (g->frame > 205 && g->frame < 260) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b098:01E024A0, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fB2B0, f5A = owner fB2A2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b098_01E024A0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b098_01E024A0;

typedef struct Obj_b098_01E024A0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b098_01E024A0 slots[400];
    u8 padB[0xB214 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xB2A2 - 0xB214 - 4];
    s16 fB;
    u8 padD[0xB2B0 - 0xB2A2 - 2];
    s16 fA;
} Obj_b098_01E024A0;

static s32 func_01E04110_b414(Obj_b098_01E024A0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b098_01E024A0 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
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
        s->f50 = obj->fA;
        s->f52 = obj->fA;
        s->f5A = obj->fB;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b180:01E01230, 216 insns, 3 copies: draws an arc band of count quads (outer and inner radius, start angle, step
   and spacing from the band) around a position, two colours, turned by the band's rotation; blend from flags
   >> 4, depth mode flags & 0xF (projected, or far after a packet tweak). */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b180_01E01230;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[4];
    f32 h;
    u8 pad38[0x10];
    f32 outer;
    f32 inner;
    u8 pad50[2];
    s16 start;
    u8 pad54[6];
    s16 gap;
    s16 step;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Band_b180_01E01230;

static void func_01E042C0_b414(Obj_b180_01E01230 *o, Band_b180_01E01230 *s, s32 flags, Vec4f pos) {
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
    s32 k;
    s32 t;
    s16 b;
    s16 a;
    u8 *p;
    s16 step;
    f32 ro;
    f32 ri;

    p = pkt;
    step = s->step;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = s->h;
    quad[3].y = s->h;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < o->count; k++) {
        t = a + s->start;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = s->start + (step + a);
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        }
        a += s->gap;
    }
}

/* shape b413:01E04920, 123 insns: b016:01E00ED0 sprite turned by {0, cam 0x5A, 0} via func_00109100 (mode 0),
   view [2][1] and [3][1] cleared, always drawn with the projected depth; draws one sprite quad at a position. */

typedef struct Cam_b413_01E04920 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x2A];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b413_01E04920;

typedef struct Obj_b413_01E04920 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b413_01E04920;

typedef struct Xyz_b413_01E04920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b413_01E04920;

typedef struct Uv_b413_01E04920 {
    f32 u, v;
} Uv_b413_01E04920;

typedef struct Pk_b413_01E04920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b413_01E04920 uv;
    u64 pad18;
    Xyz_b413_01E04920 v[4];
    u64 pad60[6];
} Pk_b413_01E04920;

typedef struct Buf_b413_01E04920 {
    u64 tag;
    Pk_b413_01E04920 pk;
} Buf_b413_01E04920;

static void func_01E04620_b414(Obj_b413_01E04920 *obj, Cam_b413_01E04920 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b413_01E04920 buf;
    Uv_b413_01E04920 uv;
    s32 sel;
    Pk_b413_01E04920 *p = &buf.pk;

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
    func_01E00080_b414((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    arg[0] = 0;
    arg[1] = cam->f5A;
    arg[2] = 0;
    func_00109100(view, arg, 0, obj->fD8);
    view[2][1] = 0.0f;
    view[3][1] = 0.0f;
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b414:01E04810, 227 insns: b756:01E061D0-style local packet quad: colours 0x60 (top) and 0x64 (bottom), the
   scene's rect (g+0x94, frame g+0xBE) and texture (g+0x88); one quad at the object's point (s16 x/y/z), 0x48 wide and
   hanging 0x6 down, its heights kept within 0..300, turned by the object's rotation at its position (0x10); depth-tested
   into g+0x80 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b414_01E04810;

typedef struct {
    Rgbaq_b414_01E04810 c;
    u64 st;
    u64 xyz;
} Vtx_b414_01E04810;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b414_01E04810 v[4];
} Pkt_b414_01E04810;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    f32 px, py, pz;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x18];
    f32 w;
    u8 pad4C[0x14];
    u8 col[4];
    u8 col2[4];
} Obj_b414_01E04810;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
} Game_b414_01E04810;

static void func_01E04810_b414(Game_b414_01E04810 *g, Obj_b414_01E04810 *o) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b414_01E04810 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    f32 depth[4];
    struct {
        Pkt_b414_01E04810 pk;
        u8 tail[0x20];
    } buf;
    Pkt_b414_01E04810 *p = &buf.pk;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col2);
    p->v[3].c = func_00107740(o->col2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    v[0] = o->px;
    v[1] = o->py;
    v[2] = o->pz;
    func_00108EF0(m, 0, o->rot, v);
    q[0].x = o->x;
    q[0].y = o->y;
    q[0].z = o->z;
    q[1] = q[0];
    q[1].x += o->w;
    q[2].x = o->x;
    q[2].y = o->y;
    q[2].z = o->z;
    q[2].y -= o->h6;
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    q[3] = q[2];
    q[3].x += o->w;
    if (q[0].y > 300.0f) {
        q[0].y = 300.0f;
    }
    if (q[1].y > 300.0f) {
        q[1].y = 300.0f;
    }
    if (q[2].y > 300.0f) {
        q[2].y = 300.0f;
    }
    if (q[3].y > 300.0f) {
        q[3].y = 300.0f;
    }
    if (q[0].y < 0.0f) {
        q[0].y = 0.0f;
    }
    if (q[1].y < 0.0f) {
        q[1].y = 0.0f;
    }
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    if (q[3].y < 0.0f) {
        q[3].y = 0.0f;
    }
    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, g->ot, (u32)depth[0]);
    }
}
