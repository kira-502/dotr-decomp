#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b764(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b764(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b764(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E00D10_b764(Obj_b445_01E00D10 *o, Spr_b445_01E00D10 *s, s32 flags, s8 *tbl) {
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
    func_01E00110_b764((Pk_b003_01E00080 *)p, &o->rect, 0);
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
            func_01E00110_b764((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
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
static Rect_b152_01E014F0 func_01E012E0_b764(s32 unused, s16 n, s32 unused2) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b764 in the
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

static void func_01E01430_b764(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b764((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E016F0_b764(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b764", func_01E018C0_b764);

/* shape b764:01E022D0, 91 insns: on start f48 70.0f, f4C 100.0f + 0..79, colour 0x70 grey, second colour (0x40, 0x20, 0x30)
   with alpha 0, random rotation, 0x5A/0x5C = 30; the second alpha grows by 0x50 (below 0xA0) for 3 ticks, then fades
   by 12 and stops; f4C grows by 10.0f */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b764_01E022D0;

static s32 func_01E022D0_b764(s32 arg0, Fx_b764_01E022D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 70.0f;
        o->f4C = 100.0f + (func_0019A5C8() >> 4) % 80;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        func_001076F0(o->col2, 0x40, 0x20, 0x30);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f5A = 30;
        o->f5C = 30;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->col2[3] > 0xD) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->f4C += 10.0f;
    o->tick++;
    return 0;
}

/* shape b764:01E02440, 305 insns: a 60x60 flash in three rows by index (<36, <72, <108): tilt +-0x2000 by row and side
   (ctx+0xDBD8), 4..6 frames; alpha up 12 to 0xC0 for 30 frames, down 11 from frame 411 (ctx+0xDBDC); white on odd
   frames, grey on even; while the scene runs it squeezes in steps (w to 30, h to 20; then w back up to 20, h to 10);
   from frame 281 it spins by row, from 239 the tilts settle by 0x100 a frame */

typedef struct {
    u8 pad0[0xDBD8];
    s16 side;
    u8 padDBDA[2];
    s16 t;
} Game_b764_01E02440;

typedef struct {
    u8 pad0[8];
    s16 life;
    u8 padA[0x16];
    s32 rx;
    s32 ry;
    s32 rz;
    u8 pad2C[0x1C];
    f32 w;
    f32 h;
    s16 idx;
    s16 step;
    s16 t;
    s16 f56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b764_01E02440;

static s32 func_01E02440_b764(Game_b764_01E02440 *g, Obj_b764_01E02440 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 60.0f;
        o->h = 60.0f;
        o->f56 = 0;
        o->state = 2;
        if (o->idx < 36) {
            o->step = 0;
        } else if (o->idx < 72) {
            o->step = 2;
        } else if (o->idx < 108) {
            o->step = 4;
        }
        if (o->idx < 36) {
            o->rz = 0x2000;
        } else if (o->idx < 72) {
            o->rz = -0x2000;
        }
        if (g->side != 0) {
            o->rx = 0x2000;
        } else {
            o->rx = -0x2000;
        }

        o->life = func_0019A5C8() % 3 + 4;
    }
    if (o->t < 30) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 12;
        }
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 12;
        }
    } else if (g->t > 410) {
        if (o->c0[3] > 12) {
            o->c0[3] -= 11;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 12) {
            o->c1[3] -= 11;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
    }
    if (g->t != 0) {
        if (o->step == 0) {
            if (o->w > 30.0f) {
                o->w -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 1) {
            if (o->h > 20.0f) {
                o->h -= 5.0f;
            }
        } else if (o->step == 2) {
            if (o->w > 30.0f) {
                o->w -= 5.0f;
            } else {
                o->step++;
            }
        } else if (o->step == 3) {
            if (o->h > 20.0f) {
                o->h -= 5.0f;
            }
        } else if (o->step == 4) {
            if (o->w < 20.0f) {
                o->w += 2.5f;
            } else {
                o->step++;
            }
        } else if (o->step == 5) {
            if (o->h < 10.0f) {
                o->h += 2.5f;
            }
        }
    }
    if (g->t > 280) {
        if (o->idx < 36) {
            o->ry += 0x300;
        } else if (o->idx < 72) {
            o->ry -= 0x300;
        } else if (o->idx < 108) {
            o->ry += 0x300;
        }
    } else if (g->t > 238) {
        if (o->rz > 0) {
            o->rz -= 0x100;
        }
        if (o->rz < 0) {
            o->rz += 0x100;
        }
        if (o->rx > 0) {
            o->rx -= 0x100;
        }
        if (o->rx < 0) {
            o->rx += 0x100;
        }
    }
    o->t++;
    return 0;
}

/* shape b764:01E02910, 81 insns: a white flickering spark (b252:01E03410 family): size 15, random sub-frame 2..7, f34 0.5; alpha up
   by 0x60 to 0xC0 until the game timer reaches 0x109, then down by 9; colour flickers by frame parity; random turn */

typedef struct {
    u8 pad0[0xDBDC];
    s16 timer;
} Game_b764_01E02910;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b764_01E02910;

static s32 func_01E02910_b764(Game_b764_01E02910 *g, Obj_b764_01E02910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0xF;
        o->h = 0xF;
        o->sub = func_0019A5C8() % 6 + 2;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
    }
    if (g->timer < 0x109) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b764:01E02A60, 58 insns: a white/orange two-colour glow of height 250, spun by 0x4000 a tick: in by 48 up to 0xC0 for 12 ticks, then out by 12 and ends */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    u8 pad14[0xC];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b764_01E02A60;

static s32 func_01E02A60_b764(s32 arg0, Obj_b764_01E02A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 250.0f;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0xFF, 0x80, 0x40);
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 12) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 13) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->t++;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    return 0;
}

/* shape b764:01E02B50, 137 insns: a white spark riding a scene joint: size 5 before scene frame 164, else 10; frame 3;
   spin +-0x4000 by the scene side flag; height 5..14, two turns, rise 3..12 (3..10 later), f8 0..19, held 1..2; alpha
   0xC0 while held, then fades by 15 (ends below 0x11); rises every tick and sits on joint 0xDAF8 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 rise;
    Vec4f pos;
    s32 spin;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[4];
    s16 h;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 mode;
    s16 ang;
    s16 ang2;
    u8 pad5E[2];
    u8 col[4];
} Fx_b764_01E02B50;

typedef struct {
    u8 pad0[0xDAF8];
    s16 joint;
    u8 padDAFA[0xDE];
    s16 side;
    u8 padDBDA[2];
    s16 frame;
} Scene_b764_01E02B50;

static s32 func_01E02B50_b764(Scene_b764_01E02B50 *g, Fx_b764_01E02B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        if (g->frame < 0xA4) {
            o->size = 5.0f;
        } else {
            o->size = 10.0f;
        }
        o->frame = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        if (g->side != 0) {
            o->spin = -0x4000;
        } else {
            o->spin = 0x4000;
        }
        o->h = func_0019A5C8() % 10 + 5;
        o->ang = func_0019A5C8() % 360;
        o->ang2 = func_0019A5C8() % 360;
        if (g->frame < 0xA4) {
            o->rise = func_0019A5C8() % 10 + 3;
        } else {
            o->rise = func_0019A5C8() % 8 + 3;
        }
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
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

static s32 func_01E02D80_b764(void *arg0, Obj_b733_01E02C30 *o) {
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

static s32 func_01E02E80_b764(s32 arg0, Fx_b764_01E02E80 *o) {
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

/* shape b764:01E02FC0 (B764_OBJ_MOVE_9_), 381 insns, 1 copy (-O3,p): a jittery white spark trail on a world track
   (b149:01E01ED0 family): set up once (point reset and nudged by a random kick, the track's 20 points filled with it,
   random size, speed, heading, life); its frame grows for 7 frames then shrinks, full for its life then fades out,
   blinks; each frame the point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts
   the track; the source of shape b445:01E03080, built here at -O3 */

typedef struct {
    Vec4f p[0x14];
} Track_b764_01E02FC0;

/* the world as this module lays it out: its sine table at 0XDEE0 */

typedef struct {
    u8 pad0[0x7030];
    Track_b764_01E02FC0 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0xab];
    u8 trig[1];
} World_b764_01E02FC0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b764_01E02FC0;

#pragma optimization_level 3

static s32 func_01E02FC0_b764(World_b764_01E02FC0 *w, Spark_b764_01E02FC0 *o) {
    extern void b764_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 2.0f;
        w->pt[o->idx].y += o->v.y / 2.0f;
        w->pt[o->idx].z += o->v.z / 2.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 150 + 30;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 85 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = 0x5A;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        b764_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

#pragma optimization_level reset

/* shape b764:01E035C0 (B764_OBJ_MOVE_10_), 387 insns, 1 copy (-O3,p): a jittery spark trail (b445:01E03080 twin:
   smaller, random pitch, grey blink) on a world track (b149:01E01ED0 family): set up once (point reset and nudged by
   a random kick, the track's 20 points filled with it, random size, speed, heading, life); its frame grows for 7
   frames then shrinks, full for its life then fades out, blinks; each frame the point drifts along its heading and
   jitters, while the module's shape b445:01E00080 shifts the track; the source of shape b445:01E03680, built here at
   -O3 */

typedef struct {
    Vec4f p[0x14];
} Track_b764_01E035C0;

/* the world as this module lays it out: its sine table at 0XDEE0 */

typedef struct {
    u8 pad0[0x7030];
    Track_b764_01E035C0 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0xab];
    u8 trig[1];
} World_b764_01E035C0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b764_01E035C0;

#pragma optimization_level 3

static s32 func_01E035C0_b764(World_b764_01E035C0 *w, Spark_b764_01E035C0 *o) {
    extern void b764_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 150 + 30;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 85 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        b764_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

#pragma optimization_level reset

/* shape b764:01E03BD0, 103 insns: a yellow-white glow by kind (0: size 50 for 50 frames, 1: 18 for 4, 2: 20 for 4, with rise 2):
   second alpha up by 0x30 to 0xC0 until the hold, then down by 11 until it ends; spins a quarter turn */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[4];
    f32 rise;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b764_01E03BD0;

static s32 func_01E03BD0_b764(void *arg0, Obj_b764_01E03BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 0.0f;
            o->f4C = 50.0f;
            o->hold = 0x32;
        } else if (o->kind == 1) {
            o->f48 = 0.0f;
            o->f4C = 18.0f;
            o->rise = 2.0f;
            o->hold = 4;
        } else if (o->kind == 2) {
            o->f48 = 0.0f;
            o->f4C = 20.0f;
            o->rise = 2.0f;
            o->hold = 4;
        }
        if (o->kind == 0) {
            func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->c0, 0x80, 0x80, 0x40);
        }
        if (o->kind == 1) {
            func_001076F0(o->c1, 0x40, 0x40, 0x40);
            func_001076F0(o->c0, 0x40, 0x40, 0x20);
        }
        o->h5A = 0xF;
        o->h5C = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x30;
        }
    } else if (o->c1[3] > 0xC) {
        o->c1[3] -= 0xB;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b764:01E03D70, 80 insns: on start f48 10, variant 4, colour 0x80 grey, random 0x50 30..129, 0x5A and 0x5C
   0..359, 0x8 0..19, hold 1..2 (0x6); alpha 0xC0 during the hold, then fades by 15 and stops */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[0x3E];
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
} Fx_b764_01E03D70;

static s32 func_01E03D70_b764(s32 arg0, Fx_b764_01E03D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 100 + 30;
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03EB0_b764(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b764", func_01E03EC0_b764);

/* shape b764:01E04D30, 106 insns: take a free effect slot (0xFA of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0xDAC4, attach it to the scene position (0x250) and copy it, 0x5A, 0x50, 0x52 from 0xDBAE / 0xDBD4 / 0xDBD4, store the two
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
} Slot_b764_01E04D30;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b764_01E04D30 slots[0xFA];
    u8 pad7000[0xDAC4 - 0x7000];
    u8 rgba[4];
    u8 padDAC8[0xE6];
    s16 fDBAE;
    u8 padDBB0[0x24];
    s16 fDBD4;
} Scene_b764_01E04D30;

static s32 func_01E04D30_b764(Scene_b764_01E04D30 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b764_01E04D30 *s = NULL;
    s16 i;

    for (i = 0; i < 0xFA; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0xFA;
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
        s->f5A = g->fDBAE;
        s->f50 = g->fDBD4;
        s->f52 = g->fDBD4;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b764:01E04EE0 (B764PAINT_RAIN20), 200 insns, 1 copy: b529:01E03F40's one-segment ring draw with this module's
   scene layout: ordering table g+0xDACC, frame table g+0xDB18, trig g+0xDEE0 */

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
} Obj_b764_01E04EE0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xDACC - 0xC0];
    s32 ot;
    u8 padDAD0[0xDB18 - 0xDAD0];
    s16 tbl[36];
    u8 padDB60[0xDEE0 - 0xDB60];
    u8 trig[1];
} Game_b764_01E04EE0;

static void func_01E04EE0_b764(Game_b764_01E04EE0 *g, Obj_b764_01E04EE0 *o, s32 mode, Vec4f *in) {
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
    rc = func_01E012E0_b764(0x14, g->tbl[o->h50 % 36], 0);
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

INCLUDE_ASM("asm/nonmatchings/mod/b764", func_01E05200_b764);
