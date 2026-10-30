#include "common.h"

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

static void func_01E00080_b707(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

static void func_01E004D0_b707(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b041:01E004D0, 156 insns, 2 copies: draws one full-screen textured quad in the sprite's colour (all four corners),
   blend from flags >> 4, texture window from the object, depth from the caller */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b041_01E004D0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b041_01E004D0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b041_01E004D0 c;
        u64 st;
        Xyz_b041_01E004D0 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b041_01E004D0;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b041_01E004D0;

typedef struct {
    u8 pad00[0x60];
    u8 col[4];
} Spr_b041_01E004D0;

static void func_01E006A0_b707(Obj_b041_01E004D0 *o, Spr_b041_01E004D0 *s, s32 flags, f32 depth) {
    extern Rgbaq_b041_01E004D0 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Pkt_b041_01E004D0 pkt;
    Pkt_b041_01E004D0 *p;
    u8 *ot;
    s16 b;
    s16 hw;
    s16 hh;

    ot = func_00207500();
    p = &pkt;
    func_00109270(p, 0, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->v[0].c = func_00107740(s->col);
    p->v[1].c = func_00107740(s->col);
    p->v[2].c = func_00107740(s->col);
    p->v[3].c = func_00107740(s->col);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    func_00108CE0(quad, 100.0f, 100.0f);
    hw = 320;
    hh = 240;
    p->v[0].p.x = (0x800 - hw) * 16;
    p->v[0].p.y = (0x800 - hh) * 16;
    p->v[0].p.z = 0xFFFFFF;
    p->v[0].p.f = 0;
    p->v[1].p.x = (0x800 + hw) * 16;
    p->v[1].p.y = (0x800 - hh) * 16;
    p->v[1].p.z = 0xFFFFFF;
    p->v[1].p.f = 0;
    p->v[2].p.x = (0x800 - hw) * 16;
    p->v[2].p.y = (0x800 + hh) * 16;
    p->v[2].p.z = 0xFFFFFF;
    p->v[2].p.f = 0;
    p->v[3].p.x = (0x800 + hw) * 16;
    p->v[3].p.y = (0x800 + hh) * 16;
    p->v[3].p.z = 0xFFFFFF;
    p->v[3].p.f = 0;
    func_002075F0(p, (s32)ot, (u32)depth);
}

typedef struct {
    f32 x, y, z, w;
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E00910_b707(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
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

/* shape b707:01E00C70 (IWMagicGas5), 362 insns, 2 copies: c062:01E01BD0's source (b445:01E00D10 twin, kind 0 also
   turned): draws a row of small sprites (one per entry) at a position: kind 0 camera-facing quads turned by the
   emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along the row; blend from
   flags >> 4, depth mode flags & 0xF (projected, far, front); texture corners by the module helper func_01E00080_b707
   */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b707_01E00C70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b707_01E00C70 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b707_01E00C70;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b034_01E00110 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b707_01E00C70;

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
} Spr_b707_01E00C70;

static void func_01E00C70_b707(Obj_b707_01E00C70 *o, Spr_b707_01E00C70 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b707_01E00C70 func_00107740(void *);
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
    Pkt_b707_01E00C70 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b707_01E00C70 *p;
    u8 mode;

    p = (Pkt_b707_01E00C70 *)(s32)&pkt;
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
    func_01E00080_b707((Pk_b034_01E00110 *)p, &o->rect, 0);
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
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00080_b707((Pk_b034_01E00110 *)p, &o->rect, o->ids[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b707 in the
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

static void func_01E01220_b707(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b707((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b707:01E014E0 (B707_W_S), 400 insns, 1 copy: B707_W_S, the effect scene step: counts the frame (0x8776);
   before 160 takes joint 0x8740 twice and 0x8742 into the trail point 0x86C0 led by 0x8724, then slides it by 6.8
   (side flag 0x8772) to 183 and turns 0x8720 by 32 to 187 and by 5 to 229; setup at 1, two 0x1E02B00 at 185, on
   93..294 0x1E01B20 and two 0x1E02240, every third frame 0x1E01D30 to 180 and 0x1E01ED0 on 216..280, 0x1E02070 at
   190; from 54 turns 0x8720 by 1.5 to 109 and by 3 to 149 and grows 0x8724 by 0.02 up to 1 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x86C0 - 0x260];
    Vec4f a;
    u8 pad86D0[0x8720 - 0x86D0];
    f32 ang;
    f32 k;
    u8 pad8728[0x8740 - 0x8728];
    s16 j0;
    s16 j1;
    u8 pad8744[0x876E - 0x8744];
    s16 side;
    u8 pad8770[2];
    s16 flag;
    u8 pad8774[2];
    s16 t;
} Scene_b707_01E014E0;

static void func_01E014E0_b707(Scene_b707_01E014E0 *g) {
    extern void b707_01E01B20(void);
    extern void b707_01E01D30(void);
    extern void b707_01E01ED0(void);
    extern void b707_01E02070(void);
    extern void b707_01E02240(void);
    extern void b707_01E02580(void);
    extern void b707_01E02810(void);
    extern void b707_01E02B00(void);
    extern void b707_01E02C90(void);
    extern void b707_01E02D80(void);
    extern void b707_01E03C40(Scene_b707_01E014E0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;

    g->t++;
    if (g->t < 160) {
        func_001F5620(func_001F53A0(), g->j0, &g->a);
        func_001F5620(func_001F53A0(), g->j0, &v);
        func_001F5620(func_001F53A0(), g->j1, &g->pos);
        g->a.y = g->pos.y;
        g->a.z = g->pos.z;
        g->a.y += g->k * (g->a.y - v.y);
        g->a.z += g->k * (g->a.z - v.z);
    } else if (g->t < 184) {
        if (g->flag) {
            g->a.z -= 6.8f;
        } else {
            g->a.z += 6.8f;
        }
        g->a.y -= 0.2f;
    } else if (g->t < 188) {
        g->ang += 32.0f;
    } else if (g->t < 230) {
        g->ang += 5.0f;
    }
    if (g->t == 1) {
        b707_01E03C40(g, b707_01E02D80, 0);
    }
    if (g->t == 1) {
        b707_01E03C40(g, b707_01E02C90, 0);
    }
    if (g->t == 1) {
        b707_01E03C40(g, b707_01E02580, 0);
    }
    if (g->t == 1) {
        b707_01E03C40(g, b707_01E02C90, 0);
        g->side = 0;
        b707_01E03C40(g, b707_01E02810, 0);
        g->side = 1;
    }
    if (g->t == 185) {
        g->side = 0;
        b707_01E03C40(g, b707_01E02B00, 0);
        g->side = 1;
        b707_01E03C40(g, b707_01E02B00, 0);
        g->side = 2;
    }
    if (g->t >= 53 && g->t < 301) {
        g->side = 0;
        g->side = 1;
        if (g->t >= 93 && g->t < 295) {
            b707_01E03C40(g, b707_01E01B20, 0);
        }
        if (g->t >= 93) {
            g->side = 0;
            if (g->t < 295) {
                b707_01E03C40(g, b707_01E02240, 0);
            }
            g->side = 1;
            if (g->t < 295) {
                b707_01E03C40(g, b707_01E02240, 0);
            }
            if (g->t % 3 == 1 && g->t < 181) {
                b707_01E03C40(g, b707_01E01D30, 0);
            }
            if (g->t >= 216 && g->t % 3 == 1 && g->t < 281) {
                b707_01E03C40(g, b707_01E01ED0, 0);
            }
        }
    }
    if (g->t == 190) {
        b707_01E03C40(g, b707_01E02070, 0);
    }
    if (g->t > 53) {
        if (g->t < 110) {
            g->ang += 1.5f;
        } else if (g->t < 150) {
            g->ang += 3.0f;
        }
        if (g->k < 1.0f) {
            g->k += 0.02f;
        }
    }
}

/* shape b707:01E01B20, 131 insns: white spark (size 10, frame 0..3, f50 10.. + random below twice the scene scale at ctx+0x8720, angle 0..359, f8 0..34): alpha up by 64 to 0xC0 for 3..5 ticks, then down by 14; after scene count 240 f50 grows 15..34 per tick; between 161 and 209 rot[2] turns -0x300 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    f32 pos[4];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b707_01E01B20;

typedef struct {
    u8 pad0[0x8720];
    f32 scale;
    u8 pad8724[0x8776 - 0x8724];
    s16 count;
} Ctx_b707_01E01B20;

static s32 func_01E01B20_b707(Ctx_b707_01E01B20 *g, Fx_b707_01E01B20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 r;

    r = 2.0f * g->scale;
    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % r + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 15;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (g->count > 240) {
        if (o->tick != 0) {
            o->f50 += o->speed;
        }
    }
    if (g->count > 160 && g->count < 210) {
        o->rot[2] -= 0x300;
    }
    o->tick++;
    return 0;
}

/* shape b707:01E01D30, 104 insns: a white orbiting spark: size 10, random sub-frame 2..7 and orbit angle, scale 0.5; alpha up by
   0x60 for 15 frames, then down by 9 until it ends; sits on the scene point, circling it at a radius from 30 shrinking by 1 */

typedef struct {
    u8 pad0[0x86C0];
    Vec4f pt;
    u8 pad86D0[0x2A8];
    u8 sin[1];
} Game_b707_01E01D30;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 scale;
    u8 pad38[0x10];
    f32 radius;
    u8 pad4C[8];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[2];
    s16 orbit;
    u8 pad5E[2];
    u8 c0[4];
} Obj_b707_01E01D30;

static s32 func_01E01D30_b707(Game_b707_01E01D30 *g, Obj_b707_01E01D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0xA;
        o->h = 0xA;
        o->sub = func_0019A5C8() % 6 + 2;
        o->scale = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->orbit = func_0019A5C8() % 360;
        o->radius = 30.0f;
    }
    if (o->t < 0xF) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->pos = g->pt;
    o->pos.x += o->radius * func_00108030(g->sin, o->orbit, 1);
    o->pos.y += o->radius * func_00108030(g->sin, o->orbit, 0);
    o->orbit += 2;
    o->radius -= 1.0f;
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b707:01E01ED0, 103 insns: on start 0x8/0xA = 10, variant 2..7, f34 0.5, colour white, random heading 0x5C,
   radius f48 0; alpha grows by 0x60 (below 0xC0) for 15 ticks, then fades by 9 and stops; it orbits the game point
   0x86C0 at radius f48 (cosine / sine of the game table 0x8978), the heading turning 2 and the radius growing 1 a
   tick; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[0x86C0];
    Vec4f point;
    u8 pad86D0[0x8978 - 0x86D0];
    u8 trig[1];
} Game_b707_01E01ED0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 radius;
    u8 pad4C[8];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[2];
    s16 heading;
    u8 pad5E[2];
    u8 col[4];
} Fx_b707_01E01ED0;

static s32 func_01E01ED0_b707(Game_b707_01E01ED0 *g, Fx_b707_01E01ED0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f8 = 10;
        o->fA = 10;
        o->f56 = func_0019A5C8() % 6 + 2;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->heading = func_0019A5C8() % 360;
        o->radius = 0.0f;
    }
    if (o->tick < 15) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->pos = g->point;
    o->pos.x += o->radius * func_00108030(g->trig, o->heading, 1);
    o->pos.y += o->radius * func_00108030(g->trig, o->heading, 0);
    o->heading += 2;
    o->radius += 1.0f;
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b707:01E02070, 115 insns: on start 0x8/0xA = 45, variant 0..1, both colours 0x80 grey (second alpha 0); both
   alphas grow by 0x40 (below 0xC0) for 90 ticks, then fade by 9 (the first ends it); the variant flips each tick; after
   the first tick 0x8/0xA grow by 10 up to 0x5F; the colour flickers 0x80 / 0x60 grey; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b707_01E02070;

static s32 func_01E02070_b707(s32 arg0, Fx_b707_01E02070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 45;
        o->fA = 45;
        o->f56 = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x5A) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xA) {
            o->col2[3] -= 9;
        }
    }
    if (o->f56 != 0) {
        o->f56 = 0;
    } else {
        o->f56 = 1;
    }
    if (o->tick != 0) {
        if (o->f8 < 0x5F) {
            o->f8 += 10;
        }
        if (o->fA < 0x5F) {
            o->fA += 10;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b707:01E02240, 205 insns: c063:01E031E0-style ring in two kinds: kind 0 purple/grey, random spin, size 0
   growing by the scene scale (ctx+0x8720) / 20, hold 18, fades by 9; kind 1 red/grey, random spin, size 500 shrinking by
   the scale / 10, hold 10, fades by 7; inner size 0x4C is half (kind 0) or 0.6 (kind 1) of the size; alpha in by 12 */

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
} Fx_b707_01E02240;

typedef struct {
    u8 pad0[0x8720];
    f32 scale;
} Ctx_b707_01E02240;

static s32 func_01E02240_b707(Ctx_b707_01E02240 *g, Fx_b707_01E02240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x20, 0x10, 0x40);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        } else {
            func_001076F0(o->col, 0x40, 0, 0);
            func_001076F0(o->col2, 0x40, 0x40, 0x40);
        }
        o->fE = o->kind;
        if (o->kind == 0) {
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
        }
        if (o->kind == 1) {
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
            o->f48 = 500.0f;
        }
        o->w = 20;
        o->h = 20;
        o->mode = 2;
        o->col[3] = 0;
        o->h6 = 0;
        if (o->kind == 0) {
            o->hold = 18;
        }
        if (o->kind == 1) {
            o->hold = 10;
        }
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (o->kind == 0) {
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
    if (o->kind == 0) {
        o->f4C = o->f48 - 0.5f * o->f48;
        if (o->h6 < 0) {
            o->f4C = 0.0f;
        }
        if (o->tick != 0) {
            o->f48 += g->scale / 20.0f;
        }
    }
    if (o->kind == 1) {
        o->f4C = o->f48 - 0.4f * o->f48;
        if (o->h6 < 0) {
            o->f4C = 0.0f;
        }
        if (o->tick != 0) {
            o->f48 -= g->scale / 10.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b707:01E02580, 66 insns: on start f48 0, colour white, second colour (0x10, 0x10, 0x80) with alpha 0, hold
   0x6 = 0x12C, 0x5A/0x5C = 10; the second alpha grows by 0x50 (below 0xA0) during the hold, then fades by 12 and
   stops; f4C follows the game value at 0x8720; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x8720];
    f32 v;
} Game_b707_01E02580;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
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
} Fx_b707_01E02580;

static s32 func_01E02580_b707(Game_b707_01E02580 *g, Fx_b707_01E02580 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x10, 0x10, 0x80);
        o->hold = 0x12C;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->col2[3] > 0xD) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->f4C = g->v;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b707:01E02690, 95 insns: a grey tumbling shard: random turn on all three axes, height 90 rising by 0..6 until 270, size
   from the scene falling by 1 a frame; full alpha for 8 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x8720];
    f32 size;
} Scene_b707_01E02690;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b707_01E02690;

static s32 func_01E02690_b707(Scene_b707_01E02690 *g, Obj_b707_01E02690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->sub = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
        o->size = g->size;
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
    if (o->y < 0x10E) {
        o->y += (s16)(func_0019A5C8() % 7);
    } else {
        o->state = 0;
    }
    o->size -= 1.0f;
    return 0;
}

/* shape b041:01E01DF0, 113 insns: a dim two-colour glow: fades both colours in by 4 up to 0x60 for 22 frames, then out by 7 while the scene's counter is under 30; its frame counter runs 0..127 up or down by o->h50 */


typedef struct {
    u8 pad0[0x8700];
    s32 count;
} Ctx_b041_01E01DF0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[0x46];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b041_01E01DF0;

static s32 func_01E02810_b707(Ctx_b041_01E01DF0 *ctx, Obj_b041_01E01DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        func_001076F0(o->col2, 0x20, 0x20, 0x20);
        o->h6 = 22;
        o->h8 = func_0019A5C8() % 128;
        o->state = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x60) {
            o->col[3] += 4;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 4;
        }
    } else if (ctx->count < 30) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->h50 == 0) {
        o->h8++;
        if (o->h8 >= 128) {
            o->h8 %= 128;
        }
    }
    if (o->h50 == 1) {
        o->h8--;
        if (o->h8 <= 0) {
            o->h8 = 128 - o->h8 % 128;
        }
    }
    o->t++;
    return 0;
}

/* shape b707:01E029E0, 69 insns: a red blinking flare: on state 1 takes the game's point; on state 2 grows (f48 by 8,
   f4C by the old f48); second colour blinks by frame parity; spins while not growing */

typedef struct {
    u8 pad0[0x86D0];
    Vec4f p;
} Game_b707_01E029E0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 state;
    u8 pad52[2];
    s16 t;
    u8 pad56[0xE];
    u8 c1[4];
} Obj_b707_01E029E0;

static s32 func_01E029E0_b707(Game_b707_01E029E0 *g, Obj_b707_01E029E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->pos = g->p;
    }
    if (o->state == 2) {
        o->f48 += 8.0f;
        o->f4C += o->f48 - 8.0f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0xC0, 0x70, 0x70);
    }
    if (o->state != 2) {
        func_00205C40((s32)o->rot);
        o->rot[0] += 0x4000;
    }
    o->t++;
    return 0;
}

/* shape b707:01E02B00, 98 insns: b283:01E036C0 family three-kind two-colour glow (grey, lilac, lavender; held 32/32/22): in by 25 up to 0x80, then out by 4 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b707_01E02B00;

static s32 func_01E02B00_b707(s32 arg0, Obj_b707_01E02B00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->h6 = 32;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xE0, 0xB0, 0xF0);
            func_001076F0(o->col2, 0xD0, 0xA0, 0xF0);
            o->h6 = 32;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0x58, 0x58, 0x78);
            func_001076F0(o->col2, 0x58, 0x58, 0x78);
            o->h6 = 22;
        }
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x19;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x19;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 5) {
            o->col2[3] -= 4;
        } else {
            o->col2[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b707:01E02C90, 58 insns: b718:01E03D10 family volume fader: down by 10 to 0x20 once the scene state passes 30, else up to 0x80 (ending there); full volume at state 2 */

typedef struct {
    u8 pad[0x8700];
    s32 state;
} Game_b707_01E02C90;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b707_01E02C90;

static s32 func_01E02C90_b707(Game_b707_01E02C90 *g, Fade_b707_01E02C90 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x20) {
            o->vol -= 10;
        } else {
            o->vol = 0x20;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    if (g->state == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b707:01E02D80, 190 insns: b521:01E01970's blue-grey (0x80/0x80/0xB0) screen veil with offsets biased by 10; while
   the scene time (g+0x8776) is 161..209 the bias swings 10 x cos(0x5A) (0x5A turning 10 a tick), at time 241 the tint
   turns 0x90/0x70/0x80; for 300 ticks the alpha rises by 10 to 0x50 before time 216 and falls by 6 to 64 after, then it
   fades by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b707_01E02D80;

typedef struct {
    f32 s, t;
    Xyz_b707_01E02D80 p;
} Tv_b707_01E02D80;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b707_01E02D80 v[2];
    u8 tail[0x20];
} Tex_b707_01E02D80;

typedef struct {
    u8 pad0[0x8776];
    s16 time;
    u8 pad8778[0x200];
    u8 trig[1];
} Ctx_b707_01E02D80;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b707_01E02D80;

static s32 func_01E02D80_b707(Ctx_b707_01E02D80 *g, Fx_b707_01E02D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    Tex_b707_01E02D80 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xB0);
        o->mode = 2;
    }
    z = 10.0f;
    ((Tex_b707_01E02D80 *)(s32)&pk)->flags = 0x26;
    ((Tex_b707_01E02D80 *)(s32)&pk)->size = 5;
    ((Tex_b707_01E02D80 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b707_01E02D80 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->time > 160 && g->time < 210) {
        o->f48 = 10.0f * func_00108030(g->trig, o->ang, 0);
        o->ang += 10;
    }
    if (g->time == 241) {
        func_001076F0(o->col, 0x90, 0x70, 0x80);
    }
    if (o->tick < 300) {
        if (g->time < 216) {
            if (o->col[3] < 0x50) {
                o->col[3] += 10;
            }
        }
        if (g->time > 216) {
            if (o->col[3] > 64) {
                o->col[3] -= 6;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b707", func_01E03080_b707);

/* shape b041:01E02C00, 102 insns, 2 copies: spawns an effect into the first free slot (170 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

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
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b041_01E02C00;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b041_01E02C00 slot[170];
    u8 pad4500[0x8704 - 0x2A0 - 170 * 0x70];
    u8 col[4];
    u8 pad8708[0x66];
    s16 h876E;
} Scene_b041_01E02C00;

static s32 func_01E03C40_b707(Scene_b041_01E02C00 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b041_01E02C00 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 170; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 170;
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
        sl->h50 = s->h876E;
        sl->h52 = s->h876E;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
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

static void func_01E03DE0_b707(Obj_b363_01E06930 *o, Band_b363_01E06930 *s, Vec4f pos, s32 flags) {
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
