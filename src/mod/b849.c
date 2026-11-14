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

static void func_01E00080_b849(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b849(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b445:01E00D10, 372 insns, 5 copies: draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b445_01E00D10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b445_01E00D10 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b445_01E00D10;

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
} Obj_b445_01E00D10;

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
    u8 pad5C[4];
    u8 col[4];
} Spr_b445_01E00D10;

static void func_01E00C80_b849(Obj_b445_01E00D10 *o, Spr_b445_01E00D10 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b445_01E00D10 func_00107740(void *);
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
    Pkt_b445_01E00D10 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b445_01E00D10 *p;
    u8 mode;

    p = (Pkt_b445_01E00D10 *)(s32)&pkt;
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
    func_01E00080_b849((Pk_b003_01E00080 *)p, &o->rect, 0);
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
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00080_b849((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
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
        }
        if (o->kind == 1) {
            func_00108950(&e, ax, 0, o->xD8);
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

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E01250_b849(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
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

static void func_01E013A0_b849(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b094:01E01230, 206 insns: b016:01E00ED0 with the view's y column raised by cam h + cam 0x34, then
   func_00109100(view, {cam 0x5C, 0x5A, 0x5C}, 2 and 0, obj 0xD8); draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b849 in the
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

static void func_01E01570_b849(Obj_b094_01E01230 *obj, Cam_b094_01E01230 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b849((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b849:01E018B0 (B849_W_S), 515 insns, 1 copy: B849_W_S, the scene timer script: counts the frame (0xF20E);
   frame 1 reads joint 0xF128 into five points and moves their z by +-10 by side 0xF20A; frame 220 reads it into eight
   more; frame 306 spawns 0x1E031B0; 35..420 spawns five 0x1E02280 a frame while 0xF1DA < 36; odd frames 127..420 put
   the spawn point on the joint and spawn 0x1E02F30 and 0x1E02CD0 while 0xF1E4 < 480 (step 30, 0x1E030B0 at the end);
   frame 127 spawns five 0x1E020C0 and five 0x1E029D0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xEF10 - 0x260];
    Vec4f a[5];
    u8 padEF60[0xF030 - 0xEF60];
    Vec4f b[8];
    u8 padF0B0[0xF128 - 0xF0B0];
    s16 j;
    u8 padF12A[0xF1DA - 0xF12A];
    s16 n;
    u8 padF1DC[2];
    s16 arg;
    u8 padF1E0[4];
    s16 k;
    s16 m;
    u8 padF1E8[0xF206 - 0xF1E8];
    s16 sel;
    u8 padF208[2];
    s16 side;
    u8 padF20C[2];
    s16 t;
} Scene_b849_01E018B0;

static void func_01E018B0_b849(Scene_b849_01E018B0 *g) {
    extern void b849_01E020C0();
    extern void b849_01E02280();
    extern void b849_01E029D0();
    extern void b849_01E02CD0();
    extern void b849_01E02F30();
    extern void b849_01E030B0();
    extern void b849_01E031B0();
    extern void b849_01E03DC0();
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t == 1) {
        func_001F5620(func_001F53A0(), g->j, &g->a[0]);
        func_001F5620(func_001F53A0(), g->j, &g->a[1]);
        func_001F5620(func_001F53A0(), g->j, &g->a[2]);
        func_001F5620(func_001F53A0(), g->j, &g->a[3]);
        func_001F5620(func_001F53A0(), g->j, &g->a[4]);
        if (g->side) {
            g->a[0].z += 10.0f;
            g->a[1].z += 10.0f;
            g->a[2].z += 10.0f;
            g->a[3].z += 10.0f;
            g->a[4].z += 10.0f;
        } else {
            g->a[0].z -= 10.0f;
            g->a[1].z -= 10.0f;
            g->a[2].z -= 10.0f;
            g->a[3].z -= 10.0f;
            g->a[4].z -= 10.0f;
        }
    }
    if (g->t == 220) {
        for (i = 0; i < 8; i++) {
            func_001F5620(func_001F53A0(), g->j, &g->b[i]);
        }
    }
    if (g->t == 306) {
        b849_01E03DC0(g, b849_01E031B0, 0);
    }
    if (g->t >= 35 && g->t < 421) {
        if (g->n < 36) {
            g->arg = g->n * 10;
            g->sel = g->n;
            b849_01E03DC0(g, b849_01E02280, 0);
            g->arg = g->n * 10 + 90;
            g->sel = g->n + 36;
            b849_01E03DC0(g, b849_01E02280, 0);
            g->arg = g->n * 10 + 180;
            g->sel = g->n + 72;
            b849_01E03DC0(g, b849_01E02280, 0);
            g->arg = g->n * 10 + 270;
            g->sel = g->n + 108;
            b849_01E03DC0(g, b849_01E02280, 0);
            g->arg = g->n * 10;
            g->sel = g->n + 144;
            b849_01E03DC0(g, b849_01E02280, 0);
            g->n++;
        }
    }
    if (g->t >= 127 && g->t < 421) {
        if (g->t % 2 == 1) {
            if (g->k < 480) {
                func_001F5620(func_001F53A0(), g->j, &g->pos);
                if (g->side) {
                    g->sel = g->k;
                } else {
                    g->sel = 180 - g->k;
                }
                g->arg = g->k;
                b849_01E03DC0(g, b849_01E02F30, 0);
                g->arg = g->k;
                g->sel = g->m;
                b849_01E03DC0(g, b849_01E02CD0, 0);
                g->k += 30;
                if (g->k >= 480) {
                    b849_01E03DC0(g, b849_01E030B0, 0);
                }
                g->m++;
            }
        }
    }
    if (g->t == 127) {
        g->sel = 0;
        b849_01E03DC0(g, b849_01E020C0, 0);
        g->sel = 1;
        b849_01E03DC0(g, b849_01E020C0, 0);
        g->sel = 2;
        b849_01E03DC0(g, b849_01E020C0, 0);
        g->sel = 3;
        b849_01E03DC0(g, b849_01E020C0, 0);
        g->sel = 4;
        b849_01E03DC0(g, b849_01E020C0, 0);
        g->sel = 0;
        b849_01E03DC0(g, b849_01E029D0, 0);
        g->sel = 1;
        b849_01E03DC0(g, b849_01E029D0, 0);
        g->sel = 2;
        b849_01E03DC0(g, b849_01E029D0, 0);
        g->sel = 3;
        b849_01E03DC0(g, b849_01E029D0, 0);
        g->sel = 4;
        b849_01E03DC0(g, b849_01E029D0, 0);
    }
}

/* shape b849:01E020C0, 111 insns: on start f48 0, f4C 30.0f, hold 200 (0x6), colours (0x80, 0x80, 0x40) and (0x80, 0x80, 0x80) (second alpha 0),
   0x5A/0x5C = 15; the second alpha grows by 0x30 (below 0xC0) during the hold, then fades by 11 and stops; the rotation
   at 0x20 advances 0x4000; it sits on the game point 0xF128 and moves 0x50 fifths of the way from that point to point
   0xF12A */

typedef struct {
    u8 pad0[0xF128];
    s16 pt;
    s16 pt2[2];
} Game_b849_01E020C0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b849_01E020C0;

static s32 func_01E020C0_b849(Game_b849_01E020C0 *g, Fx_b849_01E020C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    f32 f;
    Vec4f *pb;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 30.0f;
        o->hold = 200;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0x80, 0x80, 0x40);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0xC) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    f = o->f50;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    func_001F5620(func_001F53A0(), g->pt, &o->pos);
    func_001F5620(func_001F53A0(), g->pt, &a);
    func_001F5620(func_001F53A0(), g->pt2[0], pb = &b);
    o->pos.x += f * ((pb->x - a.x) / 5.0f);
    o->pos.y += f * ((b.y - a.y) / 5.0f);
    o->tick++;
    return 0;
}

/* shape b849:01E02280 (B849_OBJ_MOVE_2_), 467 insns, 1 copy: a blinking petal of a five-way star: on start 60 x 60,
   its arm (f50 / 36) picks the shrink step, spin 0x4000, hold 4..6, delay 0..99; fades in by 12 for 30 ticks, out by
   11 after scene tick 475; while the scene runs it shrinks f48/f4C by 5 step by step, turns 0x180 either way from
   tick 128, sits on its arm point 0xEF10 until 306 + delay, then drifts 2 along z */

typedef struct {
    u8 pad0[0xEF10];
    Vec4f pts[5];
    u8 padEF60[0xF20A - 0xEF60];
    s16 flag;
    u8 padF20C[2];
    s16 t;
} Game_b849_01E02280;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[6];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    s16 step;
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b849_01E02280;

static s32 func_01E02280_b849(Game_b849_01E02280 *g, Fx_b849_01E02280 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);

    if (o->mode == 1) {
        o->f48 = 60.0f;
        o->f4C = 60.0f;
        o->f56 = 0;
        o->mode = 2;
        if (o->f50 < 36) {
            o->step = 0;
        } else if (o->f50 < 72) {
            o->step = 2;
        } else if (o->f50 < 108) {
            o->step = 4;
        } else if (o->f50 < 144) {
            o->step = 6;
        } else if (o->f50 < 180) {
            o->step = 8;
        }
        o->rot[0] = 0x4000;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = (func_0019A5C8() >> 4) % 100;
    }
    if (o->tick < 30) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 12;
        }
    } else if (g->t > 475) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 12) {
            o->col2[3] -= 11;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    }
    if (g->t) {
        if (o->step == 0) {
            if (o->f48 > 15.0f) {
                o->f48 -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 1) {
            if (o->f4C > 5.0f) {
                o->f4C -= 5.0f;
            }
        } else if (o->step == 2) {
            if (o->f48 > 25.0f) {
                o->f48 -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 3) {
            if (o->f4C > 15.0f) {
                o->f4C -= 5.0f;
            }
        } else if (o->step == 4) {
            if (o->f48 > 35.0f) {
                o->f48 -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 5) {
            if (o->f4C > 25.0f) {
                o->f4C -= 5.0f;
            }
        } else if (o->step == 6) {
            if (o->f48 > 45.0f) {
                o->f48 -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 7) {
            if (o->f4C > 35.0f) {
                o->f4C -= 5.0f;
            }
        } else if (o->step == 8) {
            if (o->f48 > 55.0f) {
                o->f48 -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 9) {
            if (o->f4C > 45.0f) {
                o->f4C -= 5.0f;
            }
        }
    }
    if (g->t > 127 && g->t < o->h6 + 306) {
        if (o->f50 < 36) {
            o->rot[2] -= 0x180;
        } else if (o->f50 < 72) {
            o->rot[2] += 0x180;
        } else if (o->f50 < 108) {
            o->rot[2] -= 0x180;
        } else if (o->f50 < 144) {
            o->rot[2] += 0x180;
        } else if (o->f50 < 180) {
            o->rot[2] -= 0x180;
        }
    }
    if (g->t < o->h6 + 306) {
        if (o->f50 < 36) {
            o->pos = g->pts[0];
        } else if (o->f50 < 72) {
            o->pos = g->pts[1];
        } else if (o->f50 < 108) {
            o->pos = g->pts[2];
        } else if (o->f50 < 144) {
            o->pos = g->pts[3];
        } else if (o->f50 < 180) {
            o->pos = g->pts[4];
        }
    } else if (g->flag) {
        o->pos.z -= 2.0f;
    } else {
        o->pos.z += 2.0f;
    }
    o->tick++;
    return 0;
}

/* shape b849:01E029D0, 111 insns: on start f48 0, f4C 15.0f, hold 200 (0x6), colours (0x80, 0x10, 0x10) and (0x80, 0x10, 0x10) (second alpha 0),
   0x5A/0x5C = 15; the second alpha grows by 0x30 (below 0xC0) during the hold, then fades by 11 and stops; the rotation
   at 0x20 advances 0x4000; it sits on the game point 0xF128 and moves 0x50 fifths of the way from that point to point
   0xF12C */

typedef struct {
    u8 pad0[0xF128];
    s16 pt;
    s16 pt2[2];
} Game_b849_01E029D0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b849_01E029D0;

static s32 func_01E029D0_b849(Game_b849_01E029D0 *g, Fx_b849_01E029D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    f32 f;
    Vec4f *pb;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 15.0f;
        o->hold = 200;
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        func_001076F0(o->col, 0x80, 0x10, 0x10);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0xC) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    f = o->f50;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    func_001F5620(func_001F53A0(), g->pt, &o->pos);
    func_001F5620(func_001F53A0(), g->pt, &a);
    func_001F5620(func_001F53A0(), g->pt2[1], pb = &b);
    o->pos.x += f * ((pb->x - a.x) / 5.0f);
    o->pos.y += f * ((b.y - a.y) / 5.0f);
    o->tick++;
    return 0;
}

/* shape b764:01E02E80, 80 insns: a random white spark: f48 2, f56 4, f50 8..37, random f5A/f5C angles, f8 0..19,
   life 1..2; alpha 0xC0 during the life, then fades out by 15 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x18];
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
} Fx_b764_01E02E80;

static s32 func_01E02B90_b849(s32 arg0, Fx_b764_01E02E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 2.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % 30 + 8;
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b849:01E02CD0, 145 insns: b849:01E029D0 family marker (size 15, frame = f50, size f34 43.5) on the tracked point (ctx+0xF128), drifting 0.5 along z by the scene flag and sinking 0.25; turns start at 180 or 0; both alphas up by 42 for 3 ticks, then down by 9 once scene count 351 is reached; flickers 0x80/0x70 */

typedef struct {
    u8 pad0[0xF128];
    s16 pt;
    u8 padF12A[0xF20A - 0xF12A];
    s16 flag;
    u8 padF20C[2];
    s16 count;
} Game_b849_01E02CD0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x18];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b849_01E02CD0;

static s32 func_01E02CD0_b849(Game_b849_01E02CD0 *g, Fx_b849_01E02CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->h8 = 15;
        o->hA = 15;
        o->f56 = o->f50;
        o->f34 = 43.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        if (g->flag != 0) {
            o->f5C = o->f5A - 56;
            o->f5A = 180;
        } else {
            o->f5C = o->f5A - 56;
            o->f5A = 0;
        }
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else if (g->count > 350) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0x70);
    }
    o->rot[0] = 0;
    func_001F5620(func_001F53A0(), g->pt, &o->pos);
    if (g->flag != 0) {
        o->pos.z += 0.5f;
    } else {
        o->pos.z -= 0.5f;
    }
    o->pos.y -= 0.25f;
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02F20_b849(void) {
    return 0;
}

/* shape b849:01E02F30, 94 insns: on start f48 0, f4C 30, hold 5, second colour white (alpha 0), colour (0x80, 0x80,
   0x40), 0x5A/0x5C = 15; the second alpha grows by 0x30 (below 0xC0) during the hold, then fades by 11 and stops; the
   rotation at 0x20 advances 0x4000; follows model point 0xF128 pushed 6 along heading 0x50 (game table 0xF510) */

typedef struct {
    u8 pad0[0xF128];
    s16 point;
    u8 padF12A[0xF510 - 0xF12A];
    u8 trig[1];
} Game_b849_01E02F30;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    f32 pos[4];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 heading;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b849_01E02F30;

static s32 func_01E02F30_b849(Game_b849_01E02F30 *g, Fx_b849_01E02F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 30.0f;
        o->hold = 5;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0x80, 0x80, 0x40);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0xC) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    func_001F5620(func_001F53A0(), g->point, o->pos);
    o->pos[0] += 6.0f * func_00108030(g->trig, o->heading, 1);
    o->pos[1] += 6.0f * func_00108030(g->trig, o->heading, 0);
    o->tick++;
    return 0;
}

/* shape b733:01E02C30, 63 insns, 3 copies: step of a two-colour glow: on state 1 sets both colours grey and a lifetime
   of 12; fades both in by 0x2A, then out by 12 until the first ends. */

typedef struct {
    u8 pad00[6];
    s16 life;
    u8 pad08[0x4C];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b733_01E02C30;

static s32 func_01E030B0_b849(void *arg0, Obj_b733_01E02C30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->life = 12;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else {
        if (o->c0[3] > 13) {
            o->c0[3] -= 12;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 13) {
            o->c1[3] -= 12;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b849:01E031B0, 129 insns: b594:01E02CB0 with a blue-grey tint (0x78/0x78/0xA0), alpha up by 5, and the
   fade-out once the game counter at g+0xF20E reaches 475 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b849_01E031B0;

typedef struct {
    f32 s, t;
    Xyz_b849_01E031B0 p;
} Tv_b849_01E031B0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b849_01E031B0 v[2];
    u8 tail[0x20];
} Tex_b849_01E031B0;

typedef struct {
    u8 pad0[0xF20E];
    s16 count;
} Ctx_b849_01E031B0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b849_01E031B0;

static s32 func_01E031B0_b849(Ctx_b849_01E031B0 *g, Fx_b849_01E031B0 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b849_01E031B0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    ((Tex_b849_01E031B0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b849_01E031B0 *)(s32)&pk)->size = 5;
    ((Tex_b849_01E031B0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b849_01E031B0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0x78;
    pk.b = 0xA0;
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
    if (g->count < 475) {
        if (o->col[3] < 0x50) {
            o->col[3] += 5;
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

static s32 func_01E033C0_b849(void) {
    return 0;
}

/* shape b849:01E033D0 (b849), 636 insns, 1 copy: b849 scene manager in b574:01E033F0 form: setup (clear 0xF680, six
   joints (the last set three times) and the camera, textures (4,15) and (5,0..2), three 30-wide s8 jitter tables (the
   first zeroed at 100..179, the second set to 10..29 there), 36 random 0..7 values, eight cleared shorts), step
   b849:01E018B0 and every slot (300 of 0x70) but b849:01E033C0, draw rings, sprites, jitter quads, a cell sprite and
   a level-scaled sprite; scene code from the frame */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b849_01E033D0;

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
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b849_01E033D0 fx[300];
    u8 pad85E0[0xF0D0 - 0x85E0];
    s32 tex2[3];
    u8 padF0DC[0x14];
    s32 count;
    u8 padF0F4[8];
    s32 ot;
    u8 padF100[0x14];
    f32 level;
    u8 padF118[0x10];
    s16 j[6];
    u8 padF134[4];
    s16 cam;
    u8 padF13A[0xE];
    s16 rnd[0x24];
    u8 padF190[0x54];
    s16 hF1E4;
    u8 padF1E6[8];
    s16 z[8];
    u8 padF1FE[0xC];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 crd[0x170];
} Scene_b849_01E033D0;

static s32 func_01E033D0_b849(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_0019A5C8(void);
    extern void func_01E018B0_b849();
    extern void func_01E00920_b849();
    extern void func_01E00C80_b849();
    extern void func_01E01570_b849();
    extern void func_01E013A0_b849(s32, u8 *, s32, f32);
    extern void b849_01E03F70();
    extern s32 func_01E033C0_b849();
    extern s32 func_01E020C0_b849();
    extern s32 func_01E02280_b849();
    extern s32 func_01E029D0_b849();
    extern s32 func_01E02B90_b849();
    extern s32 func_01E02CD0_b849();
    extern s32 func_01E02F20_b849();
    extern s32 func_01E02F30_b849();
    extern s32 func_01E030B0_b849();
    Scene_b849_01E033D0 *g = (Scene_b849_01E033D0 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xF680);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 499;
        g->j[0] = func_001F5560(func_001F53A0(), 0xA5, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0xAC, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xA9, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0xB0, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0xB1, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xB2, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xB3, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xB4, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s32)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = (func_0019A5C8() >> 4) % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = 0;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = (func_0019A5C8() >> 4) % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = (func_0019A5C8() >> 4) % 20 + 10;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit3[k] = (func_0019A5C8() >> 4) % 30 - 15;
        }
        for (k = 0; k < 0x24; k++) {
            g->rnd[k] = func_0019A5C8() % 8;
        }
        g->z[0] = 0;
        g->z[1] = 0;
        g->z[2] = 0;
        g->z[3] = 0;
        g->z[4] = 0;
        g->z[5] = 0;
        g->z[6] = 0;
        g->z[7] = 0;
        g->hF1E4 = 90;
        return 0;
    }
    func_01E018B0_b849(g, 0);
    for (k = 0; k < 300; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E033C0_b849) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 300; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E020C0_b849) {
                g->hB8 = 0x18;
                func_01E00920_b849(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02280_b849) {
                g->tex88 = g->tex2[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                g->u94.uv[3]++;
                b849_01E03F70(g, &g->fx[k], 0x20, &g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E029D0_b849) {
                g->hB8 = 0x18;
                func_01E00920_b849(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B90_b849) {
                g->tex88 = g->tex2[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00C80_b849(g, &g->fx[k], 0x20, g->jit3);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02CD0_b849) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex2[2];
                if (g->fx[k].h56 < 6) {
                    g->u94.uv[0] = g->fx[k].h56 << 5;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 6) << 5;
                    g->u94.uv[1] = 0x20;
                }
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x1F;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01570_b849(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F20_b849) {
                g->tex88 = g->tex2[1];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 10;
                g->hB0 = 0;
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F30_b849) {
                g->hB8 = 0x18;
                func_01E00920_b849(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E030B0_b849) {
                func_001F5F90(func_001F53A0(), &v);
                if (g->turn) {
                    v.z -= 2.0f;
                } else {
                    v.z += 2.0f;
                }
                func_00205440(&v, NULL, &pk[0x18], &g->level);
                func_01E013A0_b849((s32)g, (u8 *)&g->fx[k], 0x21, g->level);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 310) {
        return 1;
    }
    if (g->frame == 496) {
        return 4;
    }
    if (g->frame == 485) {
        return 2;
    }
    if (g->frame > 320 && g->frame < 480) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b849:01E03DC0, 106 insns: take a free effect slot (0x12C of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0xF0F4, attach it to the scene position (0x250) and copy it, 0x5A, 0x50, 0x52 from 0xF1DE / 0xF206 / 0xF206, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b849_01E03DC0;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b849_01E03DC0 slots[0x12C];
    u8 pad85E0[0xF0F4 - 0x85E0];
    u8 rgba[4];
    u8 padF0F8[0xE6];
    s16 fF1DE;
    u8 padF1E0[0x26];
    s16 fF206;
} Scene_b849_01E03DC0;

static s32 func_01E03DC0_b849(Scene_b849_01E03DC0 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b849_01E03DC0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x12C; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x12C;
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
        s->f5A = g->fF1DE;
        s->f50 = g->fF206;
        s->f52 = g->fF206;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b849:01E03F70 (B849PAINT_RAIN20), 200 insns, 1 copy: b529:01E03F40's one-segment ring draw with this module's
   scene layout: ordering table g+0xF0FC, frame table g+0xF148, trig g+0xF510 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    s16 h50;
    u8 pad52[8];
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b849_01E03F70;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xF0FC - 0xC0];
    s32 ot;
    u8 padF100[0xF148 - 0xF100];
    s16 tbl[36];
    u8 padF190[0xF510 - 0xF190];
    u8 trig[1];
} Game_b849_01E03F70;

static void func_01E03F70_b849(Game_b849_01E03F70 *g, Obj_b849_01E03F70 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    Rect_b152_01E014F0 rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
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
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    rc = func_01E01250_b849(0x14, g->tbl[o->h50 % 36], 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        a = s + (s16)(o->h5A + 10) - 200; /* the (s16) keeps the +10 apart: needed for the match */
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}
