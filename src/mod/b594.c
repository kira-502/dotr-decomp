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

static void func_01E00080_b594(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b594:01E00920, 368 insns, 2 copies (b445:01E00D10 twin, two-axis turn): draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b594_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b594_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b594_01E00920;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b594_01E00920;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f pos;
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 w50;
    u8 pad52[8];
    s16 axis;
    s16 axis2;
    u8 pad5E[2];
    u8 col[4];
} Spr_b594_01E00920;

static void func_01E00920_b594(Obj_b594_01E00920 *o, Spr_b594_01E00920 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b594_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f e;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b594_01E00920 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b594_01E00920 *p;
    u8 mode;

    p = (Pkt_b594_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00080_b594((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    p2.x = s->pos.x;
    p2.y = s->pos.y;
    p2.z = s->pos.z;
    if (o->kind == 0) {
        func_00108EF0(m, &o->scale, NULL, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    ax[0] = s->axis2;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00080_b594((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
            func_00108CE0(quad, s->size, s->size);
            func_00109100(quad, rot, 1, o->xD8);
            func_00109100(quad, rot, 0, o->xD8);
        } else if (o->kind == 1) {
            func_00108CE0(quad, s->size, s->size);
        }
        for (c = 0; c < 3; c++) {
            if (c == 0) {
                off = 0;
            }
            if (c == 1) {
                off = 100;
            }
            if (c == 2) {
                off = 180;
            }
            f = (tbl + i)[s->off + off];
            f /= 20.0f;
            u = f * (f32)(s->w50 + (i >> 1));
            if (c == 0) {
                e.x = u;
            }
            if (c == 1) {
                e.y = u;
            }
            if (c == 2) {
                e.z = u;
            }
        }
        if (o->kind == 0) {
            func_00108950(&e, ax, 0, o->xD8);
            func_00108950(&e, ax, 1, o->xD8);
        }
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (o->kind == 1) {
            quad[0].y = 0.0f;
            quad[1].y = 0.0f;
            quad[0].x = s->size;
            quad[1].x = -s->size;
            quad[0].z = 0.0f;
            quad[1].z = 0.0f;
        }
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b594 in the
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

static void func_01E00EE0_b594(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b594((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E011A0_b594(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b094:01E01230, 206 insns: b016:01E00ED0 with the view's y column raised by cam h + cam 0x34, then
   func_00109100(view, {cam 0x5C, 0x5A, 0x5C}, 2 and 0, obj 0xD8); draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b594 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b094_01E01230 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x22];
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    Vec4f at;
} Cam_b094_01E01230;

typedef struct Obj_b094_01E01230 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b094_01E01230;

typedef struct Xyz_b094_01E01230 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b094_01E01230;

typedef struct Uv_b094_01E01230 {
    f32 u, v;
} Uv_b094_01E01230;

typedef struct Pk_b094_01E01230 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b094_01E01230 uv;
    u64 pad18;
    Xyz_b094_01E01230 v[4];
    u64 pad60[6];
} Pk_b094_01E01230;

typedef struct Buf_b094_01E01230 {
    u64 tag;
    Pk_b094_01E01230 pk;
} Buf_b094_01E01230;

static void func_01E01500_b594(Obj_b094_01E01230 *obj, Cam_b094_01E01230 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b094_01E01230 buf;
    Uv_b094_01E01230 uv;
    s32 sel;
    s32 k;
    s32 mode;
    Pk_b094_01E01230 *p = &buf.pk;

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
    func_01E00080_b594((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    for (k = 0; k < 4; k++) {
        view[k][1] += cam->h + cam->f34;
    }
    arg[0] = cam->f5C;
    arg[1] = cam->f5A;
    arg[2] = cam->f5C;
    func_00109100(view, arg, 2, obj->fD8);
    func_00109100(view, arg, 0, obj->fD8);
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

/* shape b594:01E01840 (B594_W_S), 441 insns, 1 copy: the scene script: t++; from 140 to 350 the limit at 0x70A4 grows
   by 2 up to 10 x the model value, capped at 140; on frame 1 the b594:01E02CB0 backdrop and the b594:01E01F30 flash
   at joint 0x70C8 (z +-17 by the flag), which then glides to joint 0 over frames 285..334; every 30 frames from 25 it
   rolls eight random joints, every 4th frame a b594:01E02090 flame at each; rings, side flames, shards and sparks in
   their own frame windows */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x7030 - 0x260];
    Vec4f p;
    u8 pad7040[0x10];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 pad705C[0x70A4 - 0x705C];
    f32 lim;
    u8 pad70A8[0x10];
    s16 j[8];
    s16 jC8;
    u8 pad70CA[0x70F4 - 0x70CA];
    s16 idx;
    u8 pad70F6[2];
    s16 flag;
    u8 pad70FA[2];
    s16 t;
} Scene_b594_01E01840;

static void func_01E01840_b594(Scene_b594_01E01840 *g) {
    extern void b594_01E01F30();
    extern void b594_01E02090();
    extern void b594_01E02280();
    extern void b594_01E023F0();
    extern void b594_01E025E0();
    extern void b594_01E02790();
    extern void b594_01E02950();
    extern void b594_01E02B00();
    extern void b594_01E02CB0();
    extern s32 b594_01E03770();
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_001F5F90(s32, void *);
    Vec4f v[2];
    s32 n;
    s16 i;

    g->t++;
    if (g->t >= 140 && g->t < 351) {
        if (g->lim < 10.0f * func_001F5860(func_001F5380())) {
            g->lim += 2.0f;
        }
        if (g->lim > 140.0f) {
            g->lim = 140.0f;
        }
    }
    if (g->t == 1) {
        b594_01E03770(g, b594_01E02CB0, 0);
    }
    if (g->t < 285) {
        if (g->t == 1) {
            func_001F5620(func_001F5380(), g->jC8, &g->p);
            func_001F5F90(func_001F5380(), &g->p);
            if (g->flag) {
                g->p.z += 17.0f;
            } else {
                g->p.z -= 17.0f;
            }
            g->idx = 0;
            b594_01E03770(g, b594_01E01F30, 0);
        }
    } else {
        if (g->t == 285) {
            func_001F5620(func_001F53A0(), g->j[0], v);
            g->dz = (v[0].z - g->p.z) / 50.0f;
            g->dy = (v[0].y - g->p.y) / 50.0f;
            g->dx = (v[0].x - g->p.x) / 50.0f;
        }
        if (g->t < 335) {
            g->p.z += g->dz;
            g->p.y += g->dy;
            g->p.x += g->dx;
        }
    }
    if (g->t >= 25 && g->t < 335) {
        if (g->t % 30 == 1) {
            for (i = 0; i < 8; i++) {
                n = func_001F54E0(func_001F5380());
                n = (s16)(func_0019A5C8() % n);
                if (n == 0) {
                    n = (s16)(n + 1);
                }
                if (!i) {
                    g->j[i] = func_001F5560(func_001F5380(), (s16)n, 1);
                } else {
                    g->j[i] = func_001F5560(func_001F5380(), (s16)n, 0);
                }
            }
        } else if (g->t % 4 == 0) {
            for (i = 0; i < 8; i++) {
                func_001F5620(func_001F5380(), g->j[i], v);
                g->pos = v[0];
                g->idx = i;
                b594_01E03770(g, b594_01E02090, 0);
            }
        }
    }
    if (g->t >= 25 && g->t < 335) {
        g->idx = 0;
        b594_01E03770(g, b594_01E02280, 0);
    }
    if (g->t >= 337 && g->t < 451) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        g->pos.x += 1.0f;
        g->pos.y -= 1.2f;
        if (g->flag) {
            g->pos.z += 0.7f;
        } else {
            g->pos.z -= 0.7f;
        }
        b594_01E03770(g, b594_01E023F0, 0);
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        g->pos.x -= 1.0f;
        g->pos.y -= 1.2f;
        if (g->flag) {
            g->pos.z += 0.7f;
        } else {
            g->pos.z -= 0.7f;
        }
        b594_01E03770(g, b594_01E023F0, 0);
    }
    if (g->t >= 97 && g->t < 321) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        g->pos.y -= 0.5f;
        b594_01E03770(g, b594_01E025E0, 0);
    }
    if (g->t >= 97 && g->t < 321) {
        g->pos = g->p;
        b594_01E03770(g, b594_01E02B00, 0);
    }
    if (g->t >= 88 && g->t < 321) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        g->pos.y -= 0.5f;
        b594_01E03770(g, b594_01E02950, 0);
    }
    if (g->t >= 137 && g->t < 321) {
        g->pos = g->p;
        b594_01E03770(g, b594_01E02790, 0);
    }
}

/* shape b594:01E01F30, 88 insns: a green flickering spinning flash (b432:01E026D0 family): f4C from the game each frame,
   size 10x10; second alpha up by 0x40 to 0x80 for 4 frames, then once the game timer passes 0x1E5 down by 11 until it
   ends; first colour flickers by frame parity */

typedef struct {
    u8 pad0[0x70A4];
    f32 f4C;
    u8 pad70A8[0x54];
    s16 timer;
} Game_b594_01E01F30;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b594_01E01F30;

static s32 func_01E01F30_b594(Game_b594_01E01F30 *g, Obj_b594_01E01F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = g->f4C;
        func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c0, 0x80, 0xFF, 0x80);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (g->timer > 0x1E5) {
        if (o->c1[3] > 0xC) {
            o->c1[3] -= 0xB;
        } else {
            o->state = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0xC0, 0x80, 0x80);
    }
    o->t++;
    o->f4C = g->f4C;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    return 0;
}

/* shape b594:01E02090, 124 insns: a blue flickering flame: on start size 25, target size 25..54, a random frame and a
   tilt from the game's per-kind table at g+0x70E0; alpha up by 64 to 0x80 for 5 ticks, then down by 9 until it ends; colour
   blinks 0x80/0x80/0xFF and 0x70/0x70/0xC0; frame wraps at 8; after the first tick it rises 0.6 a tick and grows f48 by 0.1 to 0.8 */

typedef struct {
    u8 pad0[0x70E0];
    s16 tilt[1];
} Game_b594_01E02090;

typedef struct {
    u8 pad0[8];
    s16 size;
    s16 size0;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b594_01E02090;

static s32 func_01E02090_b594(Game_b594_01E02090 *g, Fx_b594_01E02090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 25;
        o->size0 = func_0019A5C8() % 30 + 25;
        o->f48 = 0.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->ang = g->tilt[o->kind];
    }
    if (o->t < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0xC0);
    }
    o->frame++;
    if (o->frame > 7) {
        o->frame = 0;
    }
    if (o->t != 0) {
        o->y += 0.6f;
        if (o->f48 < 0.8f) {
            o->f48 += 0.1f;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b594:01E02280, 91 insns: a grey ring of random height 5 .. 4 + the scene limit (ctx+0x70A4), its first colour blinking red: in by 64 up to 0x80 for 4 ticks, then out by 11 and ends; spun 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0x10];
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
} Obj_b594_01E02280;

typedef struct {
    u8 pad[0x70A4];
    f32 lim;
} Game_b594_01E02280;

static s32 func_01E02280_b594(Game_b594_01E02280 *g, Obj_b594_01E02280 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    s16 n;

    n = func_001A22C0(g->lim);
    if (o->mode == 1) {
        o->f4C = 5.0f + func_0019A5C8() % n;
        func_001076F0(o->col2, 0x50, 0x50, 0x50);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
    } else {
        func_001076F0(o->col, 0xC0, 0x30, 0x30);
    }
    o->t++;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    return 0;
}

/* shape b594:01E023F0, 124 insns: a blue flickering flame: on start size 10, target size 10..29, a random frame and a
   tilt from the game's per-kind table at g+0x70E0; alpha up by 64 to 0x80 for 5 ticks, then down by 9 until it ends; colour
   blinks 0x80/0x80/0xFF and 0x70/0x70/0xC0; frame wraps at 8; after the first tick it sinks 0.2 a tick and grows f48 by 0.1 to 0.8 */

typedef struct {
    u8 pad0[0x70E0];
    s16 tilt[1];
} Game_b594_01E023F0;

typedef struct {
    u8 pad0[8];
    s16 size;
    s16 size0;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b594_01E023F0;

static s32 func_01E023F0_b594(Game_b594_01E023F0 *g, Fx_b594_01E023F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 10;
        o->size0 = func_0019A5C8() % 20 + 10;
        o->f48 = 0.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->ang = g->tilt[o->kind];
    }
    if (o->t < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0xC0);
    }
    o->frame++;
    if (o->frame > 7) {
        o->frame = 0;
    }
    if (o->t != 0) {
        o->y -= 0.2f;
        if (o->f48 < 0.8f) {
            o->f48 += 0.1f;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b594:01E025E0, 107 insns: on start f48 5, variant 4, colour white, 0x50 100..199, random 0x5A, 0x5C = 90 when
   the game flag 0x70F8 is set else -90, speed 4..9 (0xE), 0x8 -6..8, hold 2..4 (0x6); alpha grows by 0x2A (below 0x80)
   during the hold, then fades by 11 and stops; after the first tick 0x50 shrinks by the speed while positive */

typedef struct {
    u8 pad0[0x70F8];
    s16 flag;
} Game_b594_01E025E0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
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
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b594_01E025E0;

static s32 func_01E025E0_b594(Game_b594_01E025E0 *g, Fx_b594_01E025E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % 100 + 100;
        o->f5A = func_0019A5C8() % 360;
        if (g->flag != 0) {
            o->f5C = 90;
        } else {
            o->f5C = -90;
        }
        o->speed = func_0019A5C8() % 6 + 4;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f50 > 0) {
            o->f50 -= o->speed;
        }
    }
    o->tick++;
    return 0;
}

/* shape b594:01E02790, 109 insns: b574:01E02170 family: a white tumbling spark (size 5, frame 4, three random turns, angle 40..89 stored, tilt 90, spin 4..9, size 1..8), held 2..4 ticks: in by 42 up to 0x80, then out by 11 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
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
} Obj_b594_01E02790;

static s32 func_01E02790_b594(s32 arg0, Obj_b594_01E02790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 50 + 40;
        o->h5A = func_0019A5C8() % 360;
        o->h5C = 90;
        o->hE = func_0019A5C8() % 6 + 4;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b594:01E02950, 107 insns: a white shard (3 x 84, frame 4, random angle, tilt -30..29) starting 700 out and closing 30 a tick, turned +-0x4000 by the scene flag: both alphas in by 42 up to 0x80 for 3 ticks; once in, out by 9 (twice on the first colour) and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b594_01E02950;

typedef struct {
    u8 pad[0x70F8];
    s16 flip;
} Game_b594_01E02950;

static s32 func_01E02950_b594(Game_b594_01E02950 *g, Obj_b594_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 3;
        o->hA = 84;
        o->kind = 4;
        o->f34 = 700.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 60 - 30;
    }
    if (o->t < 3) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    }
    if (o->t != 0) {
        if (o->f34 > 30.0f) {
            o->f34 -= 30.0f;
        } else {
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            } else {
                o->mode = 0;
            }
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            }
        }
    }
    o->w20 = 0;
    if (g->flip != 0) {
        o->w20 = -0x4000;
    } else {
        o->w20 = 0x4000;
    }
    o->t++;
    return 0;
}

/* shape b594:01E02B00, 107 insns: a white spark (size 10, frame 4, random heading, tilted +-90 by the scene flag) closing from 200..399 by a random 13..32 a tick, size 1..8, held 2..4 ticks: in by 42 up to 0x80, then out by 11 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b594_01E02B00;

typedef struct {
    u8 pad[0x70F8];
    s16 flip;
} Game_b594_01E02B00;

static s32 func_01E02B00_b594(Game_b594_01E02B00 *g, Obj_b594_01E02B00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h50 = func_0019A5C8() % 200 + 200;
        o->h5A = func_0019A5C8() % 360;
        if (g->flip != 0) {
            o->h5C = 90;
        } else {
            o->h5C = -90;
        }
        o->hE = func_0019A5C8() % 20 + 13;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (o->h50 > 0) {
            o->h50 -= o->hE;
        }
    }
    o->t++;
    return 0;
}

/* shape b594:01E02CB0, 126 insns: b016:01E02B40 family full-screen grey (0x78) textured sprite zooming in by f48, alpha up by 8 to 0x50 until the scene count reaches 355, then down by 7 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b594_01E02CB0;

typedef struct {
    f32 s, t;
    Xyz_b594_01E02CB0 p;
} Tv_b594_01E02CB0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b594_01E02CB0 v[2];
    u8 tail[0x20];
} Tex_b594_01E02CB0;

typedef struct {
    u8 pad0[0x70FC];
    s16 count;
} Ctx_b594_01E02CB0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b594_01E02CB0;

static s32 func_01E02CB0_b594(Ctx_b594_01E02CB0 *g, Fx_b594_01E02CB0 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b594_01E02CB0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    ((Tex_b594_01E02CB0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b594_01E02CB0 *)(s32)&pk)->size = 5;
    ((Tex_b594_01E02CB0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b594_01E02CB0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0x78;
    pk.b = 0x78;
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
    if (g->count < 355) {
        if (o->col[3] < 0x50) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02EB0_b594(void) {
    return 0;
}

/* shape b594:01E02EC0 (b594), 555 insns, 1 copy: b594 scene manager (b516:01E03030 form, one s16 counter k for the
   setup, step and draw loops, set to 0 with the count): setup (joint, textures, turn, five s8 jitter fills, eight
   random joints, eight random angles), step every slot but b594:01E02EB0, draw eight kinds; scene code from the timer
   */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b594_01E02EC0;

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
    s32 rm[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b594_01E02EC0 fx[250];
    u8 pad7000[0x30];
    Vec4f pt[3];
    s32 tex[3];
    u8 pad706C[0x14];
    s32 count;
    u8 pad7084[8];
    s32 ot;
    u8 pad7090[0x28];
    s16 jA;
    u8 pad70BA[0xE];
    s16 jt[8];
    u8 pad70D8[8];
    s16 ang[8];
    u8 pad70F0[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 pad73FE[2];
    u8 crd[0x170];
} Scene_b594_01E02EC0;

static s32 func_01E02EC0_b594(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b594_01E01840();
    Scene_b594_01E02EC0 *g = (Scene_b594_01E02EC0 *)arg0;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s32 n;

    k = 0;
    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x7570);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 490;
        g->jA = func_001F5560(func_001F53A0(), 0x14, 1);
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
            g->jit[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 20 + 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit3[k] = (func_0019A5C8() >> 4) % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->jit3[k] = (func_0019A5C8() >> 4) % 20 + 6;
        }
        for (k = 0; k < 8; k++) {
            n = func_001F54E0(func_001F53A0());
            m = func_0019A5C8() % n;
            if (m == 0) {
                m++;
            }
            if (!k) {
                g->jt[k] = func_001F5560(func_001F5380(), 0x14, 1);
            } else {
                g->jt[k] = func_001F5560(func_001F5380(), m, 0);
            }
        }
        for (k = 0; k < 8; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    b594_01E01840(g, 0);
    for (k = 0; k < 250; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL && g->fx[k].fn != (s32 (*)())func_01E02EB0_b594) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 250; k++) {
        if (g->fx[k].used != 0) {
            m++;
            if (g->fx[k].fn == (s32 (*)())func_01E01F30_b594) {
                g->hB8 = 0x24;
                func_01E011A0_b594((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   (Vec_b016_01E01190 *)&g->pt[g->fx[k].h50]);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02090_b594) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00EE0_b594((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02280_b594) {
                g->hB8 = 0x24;
                func_01E011A0_b594((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   (Vec_b016_01E01190 *)&g->pt[g->fx[k].h50]);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023F0_b594) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00EE0_b594((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E025E0_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02790_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02950_b594) {
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->tex88 = g->tex[2];
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01500_b594((Obj_b094_01E01230 *)g, (Cam_b094_01E01230 *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B00_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x20, g->jit3);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x8C) {
        return 1;
    }
    if (g->frame == 0x1DB) {
        return 4;
    }
    if (g->frame == 0x1D1) {
        return 2;
    }
    if (g->frame > 0x96 && g->frame < 0x1CC) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b594:01E03770, 82 insns (b020:01E02D90 shape): takes the first free of 250 effect slots (0x70 bytes, b089:01E030B0 shape), colours it from
   the context, places it at the context's position (copying it in), stores two frames and both arguments */

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
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b594_01E03770;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b594_01E03770 slots[0xFA];
    u8 pad[0x7084 - 0x2A0 - 0xFA * 0x70];
    u8 rgba[4];
    u8 pad7088[0x52];
    s16 f70DA;
    u8 pad70DC[0x18];
    s16 f70F4;
} Ctx_b594_01E03770;

static s32 func_01E03770_b594(Ctx_b594_01E03770 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b594_01E03770 *s = NULL;
    s16 i;

    for (i = 0; i < 0xFA; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x70);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0xFA;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c60[3] = ctx->rgba[3];
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->pos[0] = ctx->pos[0];
        s->pos[1] = ctx->pos[1];
        s->pos[2] = ctx->pos[2];
        s->f5A = ctx->f70DA;
        s->f50 = ctx->f70F4;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}
