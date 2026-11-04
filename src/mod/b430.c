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

static void func_01E00080_b430(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E00920_b430(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b430 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b046_01E00DD0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b046_01E00DD0_unused;

typedef struct Obj_b046_01E00DD0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b046_01E00DD0;

typedef struct Xyz_b046_01E00DD0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b046_01E00DD0;

typedef struct Uv_b046_01E00DD0 {
    f32 u, v;
} Uv_b046_01E00DD0;

typedef struct Pk_b046_01E00DD0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E00DD0 uv;
    u64 pad18;
    Xyz_b046_01E00DD0 v[4];
    u64 pad60[6];
} Pk_b046_01E00DD0;

typedef struct Buf_b046_01E00DD0 {
    u64 tag;
    Pk_b046_01E00DD0 pk;
} Buf_b046_01E00DD0;


typedef struct Data_b046_01E00DD0 {
    u8 pad0[0x10];
    s32 ang[4];
    u8 pad20[8];
    Vec4f f28;
    s16 f38;
} Data_b046_01E00DD0;

static void func_01E00BB0_b430(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b046_01E00DD0 buf;
    Uv_b046_01E00DD0 uv;
    Pk_b046_01E00DD0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (mode == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (mode == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->f28);
    p->uv = uv;
    func_01E00080_b430((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->f38, data->f38);
    func_00109100(view, data->ang, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b430:01E00DA0, 234 insns: b056:01E00920's row of small camera-facing sprites (count, or 20) without the extra
   axis turn: each is shaken straight by the per-entry table offset that grows along the row; texture corner mode 0
   (module helper, shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b430_01E00DA0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b430_01E00DA0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b430_01E00DA0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b430_01E00DA0;

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
    s16 axis;
} Spr_b430_01E00DA0;

static void func_01E00DA0_b430(Obj_b430_01E00DA0 *o, Spr_b430_01E00DA0 *s, s8 *tbl, Vec4f pos) {
    extern Rgbaq_b430_01E00DA0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b430_01E00DA0 pkt __attribute__((aligned(8)));
    s16 i;
    Pkt_b430_01E00DA0 *p;
    s32 h;
    s8 *j;
    s16 n;
    f32 f;

    func_00207500();
    p = (Pkt_b430_01E00DA0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    pkt.c.q = 0;
    pkt.v[0].f = 0;
    pkt.v[1].f = 0;
    pkt.v[2].f = 0;
    pkt.v[3].f = 0;
    pkt.c = func_00107740(s->col);
    func_01E00080_b430((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    if (o->count != 0) {
        n = o->count;
    } else {
        n = 20;
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 0, o->xD8);
        func_00109100(quad, rot, 1, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 20.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b056:01E00920, 240 insns, 5 copies: draws a row of small camera-facing sprites (count, or 20) at a given position,
   each shaken by a per-entry table offset that grows along the row, turned by an extra axis; one texture
   corner mode for the whole row (module helper, shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b056_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b056_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b056_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b056_01E00920;

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
    s16 axis;
} Spr_b056_01E00920;

static void func_01E01150_b430(Obj_b056_01E00920 *o, Spr_b056_01E00920 *s, s8 *tbl, Vec4f pos) {
    extern Rgbaq_b056_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f e;
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b056_01E00920 pkt __attribute__((aligned(8)));
    s8 *j;
    s32 h;
    s16 i;
    s16 n;
    Pkt_b056_01E00920 *p;

    func_00207500();
    p = (Pkt_b056_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    pkt.c.q = 0;
    pkt.v[0].f = 0;
    pkt.v[1].f = 0;
    pkt.v[2].f = 0;
    pkt.v[3].f = 0;
    pkt.c = func_00107740(s->col);
    func_01E00080_b430((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    if (o->count != 0) {
        n = o->count;
    } else {
        n = 20;
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 0, o->xD8);
        func_00109100(quad, rot, 1, o->xD8);
        j = tbl + i;
        h = i >> 1;
        e.x = j[s->off] / 20.0f * (s->w30 + h);
        e.y = j[s->off + 100] / 20.0f * (s->w30 + h);
        e.z = j[s->off + 180] / 20.0f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* OVL_WARM: compile warm */

/* shape b257:01E01880, 193 insns: b020:01E00E70 family: 4 copies of a camera-facing square of fx->size at pos (0.05 scale), drawn by depth or at far z */

typedef struct {
    f32 u, v;
} Uv_b257_01E01880;

typedef struct {
    Uv_b257_01E01880 st;
    u64 rgba;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b257_01E01880;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b257_01E01880 v[4];
    u8 tail[0x20];
} Pkt_b257_01E01880;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padcol[0x18];
    u8 xD8[1];
} Obj_b257_01E01880;

typedef struct {
    u8 pad00[8];
    s16 u;
    s16 v;
    u8 pad0C[0x1C];
    u8 col[4];
    u8 col2[4];
    u8 pad30[8];
    s16 size;
    s16 rz;
} Fx_b257_01E01880;

static void func_01E01510_b430(Obj_b257_01E01880 *o, Fx_b257_01E01880 *fx, s32 mode, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
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
    Pkt_b257_01E01880 pkt;
    Uv_b257_01E01880 uv0;
    Uv_b257_01E01880 uv1;
    Uv_b257_01E01880 uv2;
    Uv_b257_01E01880 uv3;
    s16 i;
    Pkt_b257_01E01880 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, fx->col);
    p->v[0].st = uv0;
    func_00107740(&uv1, fx->col);
    p->v[1].st = uv1;
    func_00107740(&uv2, fx->col);
    p->v[2].st = uv2;
    func_00107740(&uv3, fx->col);
    p->v[3].st = uv3;
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
    for (i = 0; i < 4; i++) {
        func_00108CE0(quad, fx->size, fx->size);
        func_00109100(quad, rot, 2, o->xD8);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        }
    }
}

/* shape b430:01E01820, 377 insns: the b430 module's event step (B430_W_S): scene colour (0x80, 0, 0, 0); counts
   ticks (ctx+0x3358); at 127 b430:01E02AE0, at 237 b430:01E02970; 126..162 two b430:01E01F20; at 85 b430:01E02610 at
   the third joint (0xEAC, also into 0x3C0, raised 0.15); 127..170 the scene turn 0xE24 grows 0.55; at 237 eight
   b430:01E020B0 at each of two joints (0xEA8, 0xEAA); from 127 the field's quad count (0xEC0) grows by 8 to 342;
   250..345 b430:01E02310 between the player and the camera, stepping along by 0x3354 (counted 235..348);
   259..345 b430:01E02490 and b430:01E027E0 around the camera point */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3C0 - 0x260];
    Vec4f p3C0;
    u8 pad3D0[0xE24 - 0x3D0];
    f32 turn;
    u8 padE28[0xE84 - 0xE28];
    u8 col[4];
    u8 padE88[0xEA8 - 0xE88];
    s16 joint[3];
    u8 padEAE[0xEC0 - 0xEAE];
    s16 count;
    u8 padEC2[0x3354 - 0xEC2];
    s16 step;
    u8 pad3356[2];
    s16 timer;
} Ctx_b430_01E01820;

static void func_01E01820_b430(Ctx_b430_01E01820 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void b430_01E03C90();
    extern s32 b430_01E01F20();
    extern s32 b430_01E020B0();
    extern s32 b430_01E02310();
    extern s32 b430_01E02490();
    extern s32 b430_01E02610();
    extern s32 b430_01E027E0();
    extern s32 b430_01E02970();
    extern s32 b430_01E02AE0();
    Vec4f a;
    Vec4f b;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 127) {
        b430_01E03C90(g, b430_01E02AE0, 0);
    }
    if (g->timer == 237) {
        b430_01E03C90(g, b430_01E02970, 0);
    }
    if (g->timer >= 126 && g->timer < 163) {
        b430_01E03C90(g, b430_01E01F20, 0);
        b430_01E03C90(g, b430_01E01F20, 0);
    }
    if (g->timer == 85) {
        func_001F5620(func_001F53A0(), g->joint[2], &a);
        func_001F5620(func_001F53A0(), g->joint[2], &g->p3C0);
        g->p3C0.y += 0.15f;
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z;
        b430_01E03C90(g, b430_01E02610, 0);
    }
    if (g->timer >= 127 && g->timer < 171) {
        g->turn += 0.55f;
    }
    if (g->timer == 237) {
        func_001F5620(func_001F53A0(), g->joint[0], &a);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z;
        for (i = 0; i < 8; i++) {
            b430_01E03C90(g, b430_01E020B0, 0);
        }
        func_001F5620(func_001F53A0(), g->joint[1], &a);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z;
        for (i = 0; i < 8; i++) {
            b430_01E03C90(g, b430_01E020B0, 0);
        }
    }
    if (g->timer >= 127) {
        if (g->count < 343) {
            g->count += 8;
        } else {
            g->count = 342;
        }
    }
    if (g->timer >= 250 && g->timer < 346) {
        func_001F5F90(func_001F53A0(), &a);
        func_001F5F90(func_001F5380(), &b);
        b.x = (b.x - a.x) / 65.0f;
        b.y = (b.y - a.y) / 65.0f;
        b.z = (b.z - a.z) / 65.0f;
        g->pos.x = a.x + func_0019A5C8() % 80 - 40.0f;
        g->pos.y = 5.0f + a.y + func_0019A5C8() % 80 - 40.0f;
        g->pos.z = a.z + b.z * g->step;
        b430_01E03C90(g, b430_01E02310, 0);
    }
    if (g->timer >= 235 && g->timer < 349) {
        g->step++;
    }
    if (g->timer >= 259 && g->timer < 346) {
        func_001F5F90(func_001F53A0(), &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = b.x + func_0019A5C8() % 30 - 15.0f;
        g->pos.y = b.y + func_0019A5C8() % 30 - 15.0f;
        g->pos.z = b.z + func_0019A5C8() % 30 - 15.0f;
        b430_01E03C90(g, b430_01E02490, 0);
        func_001F5F90(func_001F53A0(), &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = b.x + func_0019A5C8() % 30 - 15.0f;
        g->pos.y = b.y + func_0019A5C8() % 30 - 15.0f;
        g->pos.z = b.z + func_0019A5C8() % 30 - 15.0f;
        b430_01E03C90(g, b430_01E027E0, 0);
    }
}

/* shape b148:01E032D0, 65 insns: step of a fading effect (like b258:01E027A0): on state 1 sets its colour, two
   random angles and state 2; full alpha for 7 ticks, then fades by 15; picks a random frame every tick. */

typedef struct {
    u8 pad0[2];
    s16 tick;
    u8 pad4[0x24];
    u8 col[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b148_01E032D0;

static s32 func_01E01E10_b430(void *arg0, Obj_b148_01E032D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->a30 = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->state = 0;
    }
    o->frame = func_0019A5C8() % 8;
    o->tick++;
    o->t++;
    return 0;
}

/* shape b430:01E01F20, 97 insns: b430:01E020B0 family: a dark spark (size 65, frame re-rolled 0..7 each tick) spinning a random 15..19 a tick from 0..249, size 0..29, held 2..8 ticks: in by 64 up to 0x80, then out by 10 and ends */

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
} Glow_b430_01E01F20;

static s32 func_01E01F20_b430(s32 arg0, Glow_b430_01E01F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 65;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        o->h30 = func_0019A5C8() % 250;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 15;
        o->h8 = func_0019A5C8() % 30;
        o->h6 = func_0019A5C8() % 7 + 2;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->kind = func_0019A5C8() % 8;
    o->tick++;
    return 0;
}

/* shape b430:01E020B0, 96 insns: b573:01E02590 family: a white spark (size 95, random frame 0..7) spinning a random 65..124 a tick from 0..249, size 0..29, held 6..12 ticks: in by 0x80 up to 0x80, then out by 10 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[8];
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
} Glow_b430_01E020B0;

static s32 func_01E020B0_b430(s32 arg0, Glow_b430_01E020B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 95;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h30 = func_0019A5C8() % 250;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 60 + 65;
        o->h8 = func_0019A5C8() % 30;
        o->h6 = func_0019A5C8() % 7 + 6;
        o->kind = func_0019A5C8() % 8;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 11) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b258:01E027A0, 54 insns, 5 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
   state 2; full alpha for the first 5 ticks, then fades by 10 until state 0 */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b258_01E027A0;

static s32 func_01E02230_b430(void *arg0, Obj_b258_01E027A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x1AE;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b430:01E02310, 93 insns: on start 0x38 = 20, colour 0x60 grey, 0x30 150..799, random 0x3A, speed 65..124
   (0xE), 0x8 0..29, hold 6..12 (0x6), 0x34 = 0; alpha grows by 0x80 (below 0x80) during the hold, then fades by 0x14
   and stops; 0x34 counts up to 6 after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
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
} Fx_b430_01E02310;

static s32 func_01E02310_b430(s32 arg0, Fx_b430_01E02310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->f30 = func_0019A5C8() % 650 + 150;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 60 + 65;
        o->f8 = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 7 + 6;
        o->f34 = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 0x15) {
        o->col[3] -= 0x14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f34 < 6) {
            o->f34++;
        }
    }
    o->tick++;
    return 0;
}

/* shape b430:01E02490, 93 insns: a grey high spark: frame 40, height 150..799, random angle, rise 65..124, width 0..29, hold 3..7;
   alpha up by 25 to 0x80 until the hold, then down by 20 until it ends; sub-frame steps up to 6 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b430_01E02490;

static s32 func_01E02490_b430(void *arg0, Obj_b430_01E02490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->y = func_0019A5C8() % 650 + 0x96;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 60 + 0x41;
        o->w = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 5 + 3;
        o->sub = 0;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x19;
        }
    } else if (o->c0[3] > 0x15) {
        o->c0[3] -= 0x14;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->sub < 6) {
            o->sub++;
        }
    }
    o->t++;
    return 0;
}

/* shape b430:01E02610, 113 insns: a grey high spark that also drives the camera: frame 8, height 150..799, random angle, rise
   65..124, width 0..29, hold 8; alpha up by 32 to 0x80 until the hold, then down by 10; once started it swings the camera
   yaw 0.5 one way or the other by the scene side, pulls it back 0.1 and steps its frame */

typedef struct {
    u8 pad0[0x3C4];
    f32 dist;
    f32 yaw;
    u8 pad3CC[0x335A - 0x3CC];
    s16 side;
} Game_b430_01E02610;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b430_01E02610;

static s32 func_01E02610_b430(Game_b430_01E02610 *g, Obj_b430_01E02610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 8;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 650 + 0x96;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 60 + 0x41;
        o->w = func_0019A5C8() % 30;
        o->hold = 8;
        o->sub = 0;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x20;
        }
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (g->side != 0) {
            g->yaw -= 0.5f;
        } else {
            g->yaw += 0.5f;
        }
    }
    if (o->t != 0) {
        g->dist += 0.1f;
        o->h38++;
    }
    o->t++;
    return 0;
}

/* shape b430:01E027E0, 97 insns: a grey spark (size 20, random frame 0..7, random 0..7 at +0xC) at angle 150..799 with spin 65..124 and size 0..29 stored, held 3..7 ticks: in by 25 up to 0x80, then out by 10 and ends */

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
} Glow_b430_01E027E0;

static s32 func_01E027E0_b430(s32 arg0, Glow_b430_01E027E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->h30 = func_0019A5C8() % 650 + 150;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 60 + 65;
        o->h8 = func_0019A5C8() % 30;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->kind = func_0019A5C8() % 8;
        o->hC = func_0019A5C8() % 8;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x19;
        }
    } else if (o->col[3] > 11) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b430:01E02970, 89 insns: a lavender glow (size 60) at a random angle: from scene value 237 it blinks white, counts up and brightens the scene light by 0.01 a tick; from 243 it fades by 6 and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b430_01E02970;

typedef struct {
    u8 pad[0x3B0];
    f32 r, g, b;
    u8 pad3BC[0x3358 - 0x3BC];
    s16 val;
} Game_b430_01E02970;

static s32 func_01E02970_b430(Game_b430_01E02970 *g, Glow_b430_01E02970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        func_001076F0(o->col, 0x50, 0x50, 0x78);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->col[3] = 0x80;
        o->mode = 2;
    }
    if (g->val > 242) {
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        } else {
            o->mode = 0;
        }
    }
    if (g->val >= 237) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x50, 0x50, 0x78);
        } else {
            func_001076F0(o->col, 0xA0, 0xA0, 0xA0);
        }
        o->h30++;
        g->r += 0.01f;
        g->g += 0.01f;
        g->b += 0.01f;
    }
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b430:01E02AE0, 142 insns: a scene-timed glow (scene frame at 0x3358): pale blue, alpha 0x80, f38 60, two random
   turns; fades by 6 after frame 345; turns yellow at frame 237; from frame 236 it keeps 0xEC2 at 342, and from frame
   256 it raises the scene's three 0x3A0 levels by 0.01 while they are below 0.15 (compared as doubles) */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 ang2;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Fx_b430_01E02AE0;

typedef struct {
    u8 pad0[0x3A0];
    f32 lv[3];
    u8 pad3AC[0xB16];
    s16 hEC2;
    u8 padEC4[0x2494];
    s16 frame;
} Scene_b430_01E02AE0;

static s32 func_01E02AE0_b430(Scene_b430_01E02AE0 *g, Fx_b430_01E02AE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        func_001076F0(o->col, 0x50, 0x50, 0x78);
        o->ang2 = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->col[3] = 0x80;
        o->mode = 2;
    }
    if (g->frame > 0x159) {
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        } else {
            o->mode = 0;
        }
    }
    if (g->frame == 0xED) {
        func_001076F0(o->col, 0xA0, 0xA0, 0xF0);
    }
    o->t++;
    if (g->frame > 0xEB) {
        if (g->hEC2 < 0x156) {
            g->hEC2 += 0x156;
        }
        if (g->hEC2 > 0x156) {
            g->hEC2 = 0x156;
        }
        if (g->frame > 0xFF) {
            if (g->lv[0] < 0.15) {
                g->lv[0] += 0.01f;
            }
            if (g->lv[1] < 0.15) {
                g->lv[1] += 0.01f;
            }
            if (g->lv[2] < 0.15) {
                g->lv[2] += 0.01f;
            }
        }
    }
    return 0;
}

/* shape b430:01E02D20, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0xE80 is 1 */

typedef struct {
    u8 pad0[0xE30];
    f32 l0[4];
    f32 pos[3];
    u8 padE4C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 padE5C[0x24];
    s32 state;
} Scene_b430_01E02D20;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b430_01E02D20;

static s32 func_01E02D20_b430(Scene_b430_01E02D20 *g, Obj_b430_01E02D20 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 2.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 120.0f;
        g->power = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->live = 2;
        o->down = 0;
    }
    if (o->down == 0) {
        if (g->power < 1.0f) {
            g->power += 0.2f;
        } else {
            o->down = 1;
        }
    } else if (!(g->power <= 0.1f)) {
        g->power -= 0.1f;
    } else {
        o->live = 0;
    }
    if (o->live == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(g->l0);
    }
    if (g->state == 1) {
        o->live = 0;
    }
    return 0;
}

/* shape b430:01E02EA0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0xE80 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0xE80];
    s32 state;
} Game_b430_01E02EA0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b430_01E02EA0;

static s32 func_01E02EA0_b430(Game_b430_01E02EA0 *g, Fade_b430_01E02EA0 *o) {
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

static s32 func_01E02F60_b430(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04F00_b430;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04F08_b430;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b430", func_01E02FB0_b430);

/* shape b430:01E03C90, 72 insns: twin of b046:01E03E20: take the first free slot of the 40-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0xEBE and the two arguments; returns 1 if a
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
    u8 pad38[0x8];
} Slot_b430_01E03C90;

typedef struct {
    u8 pad[0x250];
    u8 m[0x1C0];
    Slot_b430_01E03C90 s[40];
    u8 padE10[0x74];
    u8 r, g, b, a;
    u8 padE88[0x36];
    s16 v;
} Pool_b430_01E03C90;

static s32 func_01E03C90_b430(Pool_b430_01E03C90 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b430_01E03C90 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 40; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 40;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b430:01E03DB0 (B430PAINT_RAIN100), 430 insns, 1 copy: B430PAINT_RAIN100: draws the 18x18 field (rings 1..18,
   the last quad of a ring wrapping to column 0) as textured quads up to the scene count (0xEC0), each corner relative
   to its first point, scaled by 0x3A0, from tick 236 bent by the per-quad angles (0x1734, 0x1A04), turned by 0xE10
   and lifted by the per-quad heights (0xEC4) times its offsets (0x1194, 0x1464, 0x2DB4) over 100; from tick 236 the
   first 0xEC2 quads grow and turn */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b430_01E03DB0;

typedef struct {
    Rgbaq_b430_01E03DB0 c;
    u64 st;
    u64 xyz;
} Vtx_b430_01E03DB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b430_01E03DB0 v[4];
} Pkt_b430_01E03DB0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
} Obj_b430_01E03DB0;

typedef struct {
    u8 pad0[0x3A0];
    f32 sc[4];
    u8 pad3B0[0x5C];
    s32 tex;
    u8 pad410[0xE10 - 0x410];
    f32 turn[3];
    u8 padE1C[0xE8C - 0xE1C];
    s32 ot;
    u8 padE90[8];
    f32 depth;
    u8 padE9C[0x24];
    s16 count;
    s16 grow;
    s16 h[360];
    s16 dx[360];
    s16 dz[360];
    s16 a0[360];
    s16 a1[360];
    f32 x[20][18];
    f32 y[20][18];
    f32 z[20][18];
    f32 hy[324];
    u8 pad32C4[0x3358 - 0x32C4];
    s16 timer;
    u8 pad335A[0x365C - 0x335A];
    u8 bend[4];
} Ctx_b430_01E03DB0;

static void func_01E03DB0_b430(Ctx_b430_01E03DB0 *g, Obj_b430_01E03DB0 *o,
                               Pkt_b430_01E03DB0 *p __attribute__((aligned(8)))) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b430_01E03DB0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_00106E90(void *, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    s16 cnt;
    s32 i;
    s32 j;
    Vec4f q[4];
    s16 rect[8];
    s32 iv[4];
    Vec4f a;
    Vec4f b;
    Vec4f c;

    cnt = 0;
    func_00106080(rect, 0x9C, 0, rect);
    rect[0] += 2;
    rect[1] += 2;
    rect[2] -= 2;
    rect[3] -= 2;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col);
    p->v[3].c = func_00107740(o->col);
    func_00108500(p, rect, 0);
    func_00208700(p, g->tex, 1);
    func_001F5F90(func_001F53A0(), &a);
    func_001F5F90(func_001F5380(), &b);
    a.z = -(a.z - b.z) / 60.0f;
    for (i = 1; i < 19; i++) {
        for (j = 0; j < 18; j++) {
            c.x = g->x[i][j];
            c.y = g->y[i][j];
            c.z = g->z[i][j];
            if (cnt < g->count) {
                q[0].x = g->x[i][j] - c.x;
                q[0].z = g->z[i][j] - c.z;
                if (j != 17) {
                    q[1].x = g->x[i][j + 1] - c.x;
                    q[1].z = g->z[i][j + 1] - c.z;
                } else {
                    q[1].x = g->x[i][0] - c.x;
                    q[1].z = g->z[i][0] - c.z;
                }
                q[2].x = g->x[i + 1][j] - c.x;
                q[2].z = g->z[i + 1][j] - c.z;
                if (j != 17) {
                    q[3].x = g->x[i + 1][j + 1] - c.x;
                    q[3].z = g->z[i + 1][j + 1] - c.z;
                } else {
                    q[3].x = g->x[i + 1][0] - c.x;
                    q[3].z = g->z[i + 1][0] - c.z;
                }
                q[0].y = g->y[i][j] - c.y;
                if (j != 17) {
                    q[1].y = g->y[i][j + 1] - c.y;
                } else {
                    q[1].y = g->y[i][0] - c.y;
                }
                q[2].y = g->y[i + 1][j] - c.y;
                if (j != 17) {
                    q[3].y = g->y[i + 1][j + 1] - c.y;
                } else {
                    q[3].y = g->y[i + 1][0] - c.y;
                }
                c.x *= g->sc[0];
                c.y *= g->sc[1];
                c.z *= g->sc[2];
                func_00106E90(&q[0], g->sc);
                func_00106E90(&q[1], g->sc);
                func_00106E90(&q[2], g->sc);
                func_00106E90(&q[3], g->sc);
                if (g->timer > 235) {
                    iv[1] = (f32)g->a0[cnt];
                    func_00108950(&q[0], iv, 0, g->bend);
                    func_00108950(&q[1], iv, 0, g->bend);
                    func_00108950(&q[2], iv, 0, g->bend);
                    func_00108950(&q[3], iv, 0, g->bend);
                    iv[0] = (f32)g->a1[cnt];
                    func_00108950(&q[0], iv, 1, g->bend);
                    func_00108950(&q[1], iv, 1, g->bend);
                    func_00108950(&q[2], iv, 1, g->bend);
                    func_00108950(&q[3], iv, 1, g->bend);
                }
                func_00107070(&q[0], 0, g->turn[0]);
                func_00107070(&q[0], 1, g->turn[1]);
                func_00107070(&q[0], 2, g->turn[2]);
                func_00106B50(&q[0], &c);
                func_00106B50(&q[1], &c);
                func_00106B50(&q[2], &c);
                func_00106B50(&q[3], &c);
                func_00107070(&q[0], 2, g->hy[cnt] * g->h[cnt] / 100.0f);
                func_00107070(&q[0], 0, g->dx[cnt] * g->h[cnt] / 100);
                func_00107070(&q[0], 1, g->dz[cnt] * g->h[cnt] / 100);
                if (func_00205630(q, 0x70000000, 0, p, &g->depth) != 0) {
                    func_002075F0(p, g->ot, func_001A23B0(g->depth));
                }
            }
            if (g->timer > 235 && cnt < g->grow) {
                g->h[cnt]++;
                if (cnt < 100) {
                    g->a0[cnt] += 14;
                    g->a1[cnt] += 8;
                } else if (cnt < 200) {
                    g->a0[cnt] -= 14;
                    g->a1[cnt] += 8;
                } else {
                    g->a0[cnt] += 14;
                    g->a1[cnt] -= 8;
                }
            }
            cnt++;
        }
    }
}

/* shape b430:01E04470 (B430PAINT_RAIN101), 376 insns, 1 copy: B430PAINT_RAIN101: B430PAINT_RAIN100 (b430:01E03DB0)
   drawing the field turned by the scene matrix (0x3B0), then moved by its own scaled point times the object height
   (0x30), y a fifth */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b430_01E04470;

typedef struct {
    Rgbaq_b430_01E04470 c;
    u64 st;
    u64 xyz;
} Vtx_b430_01E04470;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b430_01E04470 v[4];
} Pkt_b430_01E04470;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
} Obj_b430_01E04470;

typedef struct {
    u8 pad0[0x3A0];
    f32 sc[4];
    u8 m[0x40];
    u8 pad3F0[0x1C];
    s32 tex;
    u8 pad410[0xE10 - 0x410];
    f32 turn[3];
    u8 padE1C[0xE8C - 0xE1C];
    s32 ot;
    u8 padE90[8];
    f32 depth;
    u8 padE9C[0x24];
    s16 count;
    s16 grow;
    s16 h[360];
    s16 dx[360];
    s16 dz[360];
    s16 a0[360];
    s16 a1[360];
    f32 x[20][18];
    f32 y[20][18];
    f32 z[20][18];
    f32 hy[324];
    u8 pad32C4[0x3358 - 0x32C4];
    s16 timer;
    u8 pad335A[0x365C - 0x335A];
    u8 bend[4];
} Ctx_b430_01E04470;

static void func_01E04470_b430(Ctx_b430_01E04470 *g, Obj_b430_01E04470 *o,
                               Pkt_b430_01E04470 *p __attribute__((aligned(8)))) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b430_01E04470 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_00106E90(void *, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    s16 cnt;
    s32 i;
    s32 j;
    Vec4f q[4];
    s16 rect[8];
    s32 iv[4];
    Vec4f a;
    Vec4f b;
    Vec4f c;

    cnt = 0;
    func_00106080(rect, 0x9C, 0, rect);
    rect[0] += 2;
    rect[1] += 2;
    rect[2] -= 2;
    rect[3] -= 2;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col);
    p->v[3].c = func_00107740(o->col);
    func_00108500(p, rect, 0);
    func_00208700(p, g->tex, 1);
    func_001F5F90(func_001F53A0(), &a);
    func_001F5F90(func_001F5380(), &b);
    a.z = -(a.z - b.z) / 60.0f;
    for (i = 1; i < 19; i++) {
        for (j = 0; j < 18; j++) {
            c.x = g->x[i][j];
            c.y = g->y[i][j];
            c.z = g->z[i][j];
            if (cnt < g->count) {
                q[0].x = g->x[i][j] - c.x;
                q[0].z = g->z[i][j] - c.z;
                if (j != 17) {
                    q[1].x = g->x[i][j + 1] - c.x;
                    q[1].z = g->z[i][j + 1] - c.z;
                } else {
                    q[1].x = g->x[i][0] - c.x;
                    q[1].z = g->z[i][0] - c.z;
                }
                q[2].x = g->x[i + 1][j] - c.x;
                q[2].z = g->z[i + 1][j] - c.z;
                if (j != 17) {
                    q[3].x = g->x[i + 1][j + 1] - c.x;
                    q[3].z = g->z[i + 1][j + 1] - c.z;
                } else {
                    q[3].x = g->x[i + 1][0] - c.x;
                    q[3].z = g->z[i + 1][0] - c.z;
                }
                q[0].y = g->y[i][j] - c.y;
                if (j != 17) {
                    q[1].y = g->y[i][j + 1] - c.y;
                } else {
                    q[1].y = g->y[i][0] - c.y;
                }
                q[2].y = g->y[i + 1][j] - c.y;
                if (j != 17) {
                    q[3].y = g->y[i + 1][j + 1] - c.y;
                } else {
                    q[3].y = g->y[i + 1][0] - c.y;
                }
                c.x *= g->sc[0];
                c.y *= g->sc[1];
                c.z *= g->sc[2];
                func_00106E90(&q[0], g->m);
                func_00106E90(&q[1], g->m);
                func_00106E90(&q[2], g->m);
                func_00106E90(&q[3], g->m);
                if (g->timer > 235) {
                    iv[1] = (f32)g->a0[cnt];
                    func_00108950(&q[0], iv, 0, g->bend);
                    func_00108950(&q[1], iv, 0, g->bend);
                    func_00108950(&q[2], iv, 0, g->bend);
                    func_00108950(&q[3], iv, 0, g->bend);
                    iv[0] = (f32)g->a1[cnt];
                    func_00108950(&q[0], iv, 1, g->bend);
                    func_00108950(&q[1], iv, 1, g->bend);
                    func_00108950(&q[2], iv, 1, g->bend);
                    func_00108950(&q[3], iv, 1, g->bend);
                }
                func_00107070(&q[0], 0, g->turn[0]);
                func_00107070(&q[0], 1, g->turn[1]);
                func_00107070(&q[0], 2, g->turn[2]);
                func_00106B50(&q[0], &c);
                func_00106B50(&q[1], &c);
                func_00106B50(&q[2], &c);
                func_00106B50(&q[3], &c);
                c.y /= 5.0f;
                func_00107070(&q[0], 0, c.x * o->h);
                func_00107070(&q[0], 1, c.y * o->h);
                func_00107070(&q[0], 2, c.z * o->h);
                if (func_00205630(q, 0x70000000, 0, p, &g->depth) != 0) {
                    func_002075F0(p, g->ot, func_001A23B0(g->depth));
                }
            }
            cnt++;
        }
    }
}

/* shape b430:01E04A50, 284 insns: builds a 20 x 18 jagged ring field: ring i at radius growing 15 a ring (then
   shrinking 5 past ring 9, random 25..39 on rings 1..14, clamped 0..100, 0 on the first and the last two) every 20
   degrees; then jitters each ring by a random shift and a random spread; then random heights from -160 by 16 */

typedef struct {
    u8 pad0[0x1CD4];
    f32 x[20][18];
    f32 z[20][18];
    f32 y[20][18];
} Map_b430_01E04A50;

static void func_01E04A50_b430(Map_b430_01E04A50 *g) {
    s32 i;
    s32 j;
    s16 ang;
    s16 rad;
    s16 w;
    s16 size;
    s16 dx;
    s16 dy;
    s16 rx;
    s16 ry;
    s16 h;
    f32 a;

    ang = 0;
    rad = 0;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 18; j++) {
            a = 3.1415927f * ang / 180.0f;
            g->x[i][j] = rad * func_001A6898(a);
            g->y[i][j] = rad * func_001A6A88(a);
            ang += 20;
        }
        ang = 0;
        if (i < 9) {
            rad += 15;
        } else {
            rad -= 5;
        }
        if (i > 0 && i < 15) {
            rad = func_0019A5C8() % 15 + 25;
        }
        if (rad >= 100) {
            rad = 100;
        }
        if (rad <= 0) {
            rad = 0;
        }
        if (i == 0 || i >= 18) {
            rad = 0;
        }
    }
    w = 1;
    for (i = 0; i < 20; i++) {
        dx = func_0019A5C8() % 10 - 5;
        dy = func_0019A5C8() % 10 - 5;
        size = w;
        for (j = 0; j < 18; j++) {
            rx = func_0019A5C8() % size;
            ry = func_0019A5C8() % size;
            g->x[i][j] += dx + (rx - (size >> 1));
            g->y[i][j] += dy + (ry - (size >> 1));
        }
        if (i < 10) {
            if (size < 30) {
                w += 3;
            }
            if (i >= 2) {
                w = func_0019A5C8() % 10 + 2;
            }
        } else {
            if (size > 8) {
                w -= 7;
            }
            if (i < 18) {
                w = func_0019A5C8() % 10 + 2;
            }
        }
        if (i == 18) {
            w = 1;
        }
        if (w <= 0) {
            w = 1;
        }
    }
    h = -160;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 18; j++) {
            g->z[i][j] = h + func_0019A5C8() % 20 - 10;
        }
        if (i < 19) {
            h += 16;
        }
    }
}
