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

static void func_01E00080_b046(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b046(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

/* shape b046:01E00BB0, 133 insns, 4 copies: draws one camera-facing sprite at a position plus a tenth of an offset,
   blend by mode (0 normal, 1, other), texture corners by the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b046_01E00BB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b046_01E00BB0 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b046_01E00BB0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
} Obj_b046_01E00BB0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b046_01E00BB0;

static void func_01E00BB0_b046(Obj_b046_01E00BB0 *o, Spr_b046_01E00BB0 *s, s32 blend) {
    extern Rgbaq_b046_01E00BB0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b046_01E00BB0 pkt __attribute__((aligned(8)));
    Pkt_b046_01E00BB0 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b046_01E00BB0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (blend == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00080_b046((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = s->x + dx;
    pos.y = s->y + dy;
    pos.z = s->z + dz;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, s->size, s->size);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, o->ot, (u32)depth[0]);
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b046 in the
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

static void func_01E00DD0_b046(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b046((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b046:01E00FC0, 343 insns, 4 copies: draws a row of small sprites (count, or 20) at the object position: each a
   standing quad turned by the sprite rotation, shaken by a per-entry table offset that grows along the row, its
   lower edge pinned at +-size/2; blend from the object's float mode, depth mode 0/1/2. Texture corners by the
   module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b046_01E00FC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b046_01E00FC0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b046_01E00FC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[8];
    f32 blend;
    u8 padA8[0x10];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b046_01E00FC0;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f rot;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b046_01E00FC0;

static void func_01E00FC0_b046(Obj_b046_01E00FC0 *o, Spr_b046_01E00FC0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b046_01E00FC0 func_00107740(void *);
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
    Pkt_b046_01E00FC0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 f;
    s16 n;
    Pkt_b046_01E00FC0 *p;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b046_01E00FC0 *)(s32)&pkt;
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
    if (o->blend == 0.0f) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (o->blend == 1.0f) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else if (o->blend == 2.0f) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00080_b046((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    p2.x = o->pos.x;
    p2.y = o->pos.y;
    p2.z = o->pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, &s->rot, 0, o->xD8);
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
        quad[2].z = -(s->size >> 1);
        quad[2].y = 0.0f;
        quad[3].z = s->size >> 1;
        quad[3].y = 0.0f;
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

INCLUDE_ASM("asm/nonmatchings/mod/b046", func_01E01520_b046);

/* shape b046:01E01A60, 283 insns, 10 copies: draws obj->count (0 = 20) sprites along a curve read from three s8
   tables (0x64 apart), each turned on three axes by the definition's angles; mode 0 = depth from the
   projection, 1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static
   function. Sibling of b003:01E00EA0 and b018:01E005A0. */

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
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b046_01E01A60;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b046_01E01A60;

typedef struct {
    union {
        struct {
            u64 x : 16;
            u64 y : 16;
            u64 z : 24;
            u64 fog : 8;
        } b;
        struct {
            u8 pad[7];
            u8 fog;
        } h;
    } xyz;
    u64 reg;
} Xyz_b046_01E01A60;

typedef struct {
    f32 u, v;
} Uv_b046_01E01A60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E01A60 uv;
    u64 pad18;
    Xyz_b046_01E01A60 v[4];
    u64 pad60[6];
} Pk_b046_01E01A60;

typedef struct {
    u64 tag;
    Pk_b046_01E01A60 pk;
} Buf_b046_01E01A60;

static void func_01E01A60_b046(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b046_01E01A60 buf;
    Uv_b046_01E01A60 uv;
    s16 i;
    Pk_b046_01E01A60 *p;
    s16 n;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.uv.v = 0.0f;
    buf.pk.v[0].xyz.h.fog = 0;
    buf.pk.v[1].xyz.h.fog = 0;
    buf.pk.v[2].xyz.h.fog = 0;
    buf.pk.v[3].xyz.h.fog = 0;
    func_00107740(&uv, def->tex);
    buf.pk.uv = uv;
    func_01E00080_b046((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, rot, &pos);
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        func_00107070(m2, 0, f * (def->scale + h));
        f = t[def->tab + 100];
        f /= 20.0f;
        func_00107070(m2, 1, f * (def->scale + h));
        f = t[def->tab + 180];
        f /= 20.0f;
        func_00107070(m2, 2, f * (def->scale + h));
        func_00109100(m2, def->rot, 0, obj->fD8);
        func_00109100(m2, def->rot, 1, obj->fD8);
        func_00109100(m2, def->rot, 2, obj->fD8);
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].xyz.b.z = p->v[1].xyz.b.z = p->v[2].xyz.b.z = p->v[3].xyz.b.z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b046:01E01ED0, 166 insns: the scene script of b046: it sets the scene colour to red 0x80 and counts g+0x365A;
   from tick 80 to 130 it spawns a 0x1E022F0 effect on joints A and B (g+0x363C / 0x363E); on tick 94 it moves the burst
   point to joint C (g+0x3640), raises the flag g+0x3656 and spawns 15 0x1E02450, one 0x1E02770, 10 0x1E02A00, 12
   0x1E02170, two 0x1E02690 and one 0x1E02F80 effects; from 94 to 130 it keeps the point on joint C */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x33B8];
    u8 col[4];
    u8 pad3618[0x24];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 pad3642[0x14];
    s16 flag;
    u8 pad3658[2];
    s16 tick;
} Ctx_b046_01E01ED0;

static void func_01E01ED0_b046(Ctx_b046_01E01ED0 *g) {
    extern void b046_01E02170();
    extern void b046_01E022F0();
    extern void b046_01E02450();
    extern void b046_01E02690();
    extern void b046_01E02770();
    extern void b046_01E02A00();
    extern void b046_01E02F80();
    extern void b046_01E03E20(Ctx_b046_01E01ED0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick >= 80 && g->tick < 131) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        for (i = 0; i < 1; i++) {
            b046_01E03E20(g, b046_01E022F0, 0);
        }
        func_001F5620(func_001F53A0(), g->jb, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        for (i = 0; i < 1; i++) {
            b046_01E03E20(g, b046_01E022F0, 0);
        }
    }
    if (g->tick == 94) {
        func_001F5620(func_001F53A0(), g->jc, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 15; i++) {
            b046_01E03E20(g, b046_01E02450, 0);
        }
        for (i = 0; i < 1; i++) {
            b046_01E03E20(g, b046_01E02770, 0);
        }
        for (i = 0; i < 10; i++) {
            b046_01E03E20(g, b046_01E02A00, 0);
        }
        for (i = 0; i < 12; i++) {
            b046_01E03E20(g, b046_01E02170, 0);
        }
        b046_01E03E20(g, b046_01E02690, 0);
        b046_01E03E20(g, b046_01E02690, 0);
        b046_01E03E20(g, b046_01E02F80, 0);
    }
    if (g->tick >= 94 && g->tick < 131) {
        func_001F5620(func_001F53A0(), g->jc, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
    }
}

/* shape b046:01E02170, 93 insns: b417:01E03910 family: a white spark (size 50, random frame 0..7, random roll and angle) spinning a random 70..109 a tick, size 0..9, held 8..16 ticks at 0x80, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
} Glow_b046_01E02170;

static s32 func_01E02170_b046(s32 arg0, Glow_b046_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->w18 = 0;
        o->w18 = func_0019A5C8() % 360;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 40 + 70;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 9 + 8;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b046:01E022F0, 86 insns: a grey jittering flicker (b476:01E02DF0 family): frame 60, random tilt, angle and drift -2..1
   on three axes; full alpha for 7 frames, then down by 15 until it ends; a random sub-frame 0..7 each frame */

typedef struct {
    u8 pad0[8];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 tilt;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b046_01E022F0;

static s32 func_01E022F0_b046(void *arg0, Obj_b046_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->tilt = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->dx = func_0019A5C8() % 4 - 2;
        o->dy = func_0019A5C8() % 4 - 2;
        o->dz = func_0019A5C8() % 4 - 2;
        o->state = 2;
    }
    if (o->t < 7) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->sub = func_0019A5C8() % 8;
    o->t++;
    return 0;
}

/* shape b046:01E02450, 141 insns: b019:01E01F60 family light wisp (0xF0 grey, or yellow for kind 1), table at ctx+0x3A5C: size 200, drift -2..1 on each axis, random frame each tick; full alpha 7 ticks then down by 8; swings 40 along f3A on x/y and 4 by f30 on z */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3A5C];
    u8 tab[1];
} Mgr_b046_01E02450;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b046_01E02450;

static s32 func_01E02450_b046(Mgr_b046_01E02450 *m, Fx_b046_01E02450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f38 = 200;
        if (o->f30 == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        } else {
            func_001076F0(o->col, 0xF0, 0xF0, 0x20);
        }
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
        o->x = func_0019A5C8() % 4 - 2;
        o->y = func_0019A5C8() % 4 - 2;
        o->z = func_0019A5C8() % 4 - 2;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f34 = func_0019A5C8() % 8;
    o->x = o->x + 40.0f * func_00108030(m->tab, o->f3A, 0);
    o->z = o->z + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->y = o->y + 40.0f * func_00108030(m->tab, o->f3A, 1);
    o->tick++;
    return 0;
}

/* shape b046:01E02690, 53 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0x80
   for the first 5 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b046_01E02690;

static s32 func_01E02690_b046(s32 arg0, Flash_b046_01E02690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x1AE;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 5) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b046:01E02770, 71 insns: on start rotation 0x4000, step 1..3 (0x8), 0x6 = 8, both colours (0xF0, 0xF0, 0x20);
   alpha 0x80 on the first tick, fades by 14 once 0x38 passes 5; 0x38 grows by the step, 0x6 by 3 */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 step;
    u8 padA[6];
    s32 rot;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b046_01E02770;

static s32 func_01E02770_b046(s32 arg0, Fx_b046_01E02770 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->rot = 0x4000;
        o->f34 = 1;
        o->mode = 2;
        o->step = func_0019A5C8() % 3 + 1;
        o->f6 = 8;
        func_001076F0(o->col, 0xF0, 0xF0, 0x20);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x20);
    }
    if (o->tick <= 0) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->f38 > 5) {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        o->f38 += o->step;
    }
    o->f6 += 3;
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 col[3];
    u8 alpha;
    u8 pad2C[4];
    s16 pos;
    s16 age;
    s16 kind;
    s16 state;
    s16 mode;
    s16 angle;
} Spark_b018_01E02950;

static s32 func_01E02890_b046(s32 unused, Spark_b018_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 16) {
        o->alpha -= 10;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b046:01E02A00, 95 insns: on start colours (0x8F, 0x4F, 0x10) / (0x40, 0x10, 0x40), the rotation faces the
   model angle side (-0x4000 / 0x4000), size 0x5A, alpha 0; alpha grows by 0x50 (below 0x50) for 4 ticks, then fades
   by 6 and stops; 0x38 = 600; the size grows by 3..10 a tick up to 0x10E, then it ends */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 size;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b046_01E02A00;

static s32 func_01E02A00_b046(s32 arg0, Fx_b046_01E02A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    if (o->mode == 1) {
        func_001076F0(o->col, 0x8F, 0x4F, 0x10);
        func_001076F0(o->col2, 0x40, 0x10, 0x40);
        func_001F6160(func_001F53A0(), ang);
        if ((s32)(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = 0x4000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0;
        o->f34 = 0;
        o->size = 0x5A;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x50;
        }
    } else if (o->col[3] > 7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    o->f38 = 600;
    o->tick++;
    if (o->size < 0x10E) {
        o->size += (s16)(func_0019A5C8() % 8 + 3);
    } else {
        o->mode = 0;
    }
    return 0;
}

/* shape b046:01E02B80, 137 insns, 4 copies: step of a drifting light (variant of b046:01E02DB0): starts at 0 with
   random angle, speed and lifetime; fades in by 0x40, then out by 10; follows a scene point, lowered by 10 and
   pulled along z by a 25th of the gap between two scene positions. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    s16 idx;
    s16 hE_;
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b046_01E02B80;

typedef struct {
    u8 pad[0x3640];
    s16 pts[1];
} Ctx_b046_01E02B80;

static s32 func_01E02B80_b046(Ctx_b046_01E02B80 *c, Obj_b046_01E02B80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    Vec4f d;
    Vec4f e;

    if (o->state == 1) {
        o->h38 = 0xC;
        o->h34 = 1;
        o->seed = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->c0, 0x50, 0x50, 0x50);
        o->idx = o->pos;
        o->pos = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 18 + 100;
        o->h8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 4 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    o->t++;
    func_001F5620(func_001F53A0(), c->pts[o->idx], &v);
    func_001F5F90(func_001F53A0(), &d);
    func_001F5F90(func_001F5380(), &e);
    d.z = e.z - d.z;
    d.z = d.z / 25.0f;
    o->x = v.x;
    o->y = v.y - 10.0f;
    o->z = v.z + d.z;
    return 0;
}

/* shape b046:01E02DB0, 116 insns, 4 copies: step of a drifting light: on state 1 picks random timers, angle, speed and
   lifetime and a grey colour; fades in by 0x40 while young, then out by 15 until it ends; follows a point of
   the scene (func_001F5620) picked by its index. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    s16 idx;
    s16 hE_;
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b046_01E02DB0;

typedef struct {
    u8 pad[0x363C];
    s16 pts[1];
} Ctx_b046_01E02DB0;

static s32 func_01E02DB0_b046(Ctx_b046_01E02DB0 *c, Obj_b046_01E02DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;

    if (o->state == 1) {
        o->h38 = 0xE;
        o->h34 = 1;
        o->seed = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->c0, 0x50, 0x50, 0x50);
        o->idx = o->pos;
        o->pos = func_0019A5C8() % 100;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 30 + 140;
        o->h8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 2 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    o->t++;
    func_001F5620(func_001F53A0(), c->pts[o->idx], &v);
    o->x = v.x;
    o->y = v.y;
    o->z = v.z;
    return 0;
}

/* shape b046:01E02F80, 92 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x3610 is 1 */

typedef struct {
    u8 pad0[0x34F0];
    f32 l0[4];
    f32 pos[3];
    u8 pad350C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad351C[0xF4];
    s32 state;
} Scene_b046_01E02F80;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b046_01E02F80;

static s32 func_01E02F80_b046(Scene_b046_01E02F80 *g, Obj_b046_01E02F80 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 4.0f;
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

/* shape b270:01E04340, 47 insns, 1 copy: fade a level toward 0x40 or 0x80 by the scene timer */

typedef struct Ctx_b046_01E030F0 {
    u8 pad[0x3610];
    s32 timer;
} Ctx_b046_01E030F0;

typedef struct Obj_b046_01E030F0 {
    u8 pad0[0x30];
    s16 level;
    u8 pad32[4];
    s16 state;
} Obj_b046_01E030F0;

static s32 func_01E030F0_b046(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (ctx->timer > 0x1E) {
        if (o->level > 0x30) {
            o->level -= 10;
        } else {
            o->level = 0x30;
        }
    } else {
        if (o->level < 0x80) {
            o->level += 10;
        } else {
            o->level = 0x80;
        }
    }
    if (ctx->timer == 1) {
        func_001F6D00((u8)o->level);
    } else {
        func_001F6D00((u8)o->level);
    }
    return 0;
}

static s32 func_01E031B0_b046(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04300_b046;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04308_b046;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b046:01E03200, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x3300];
    s32 tex5[3];
} Scene_b046_01E03200;

static void func_01E03200_b046(s32 arg0, Scene_b046_01E03200 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b046:01E032B0 (b046), 730 insns, 1 copy: b046 scene manager (b484:01E021D0 form): on start clears the scene,
   five joints, textures and four jitter tables; else steps 12 handlers over 200 slots and draws 8 kinds */

typedef struct {
    s16 x, y, z;
    u8 pad06[0x1E];
    void *fn;
    u8 pad28[8];
    s16 side;
    u8 pad32[2];
    s16 rot;
    s16 used;
    u8 pad38[8];
} Slot_b046_01E032B0;

typedef struct {
    u8 pad0000[0x20];
    f32 x, y, z;
    u8 pad002C[0x54];
    s32 ot2;
    u8 pad0084[4];
    s32 tex88;
    u8 pad008C[8];
    union {
        Vec4f v;
        struct {
            s16 a;
            s16 pad[2];
            s16 b;
        } h;
    } m94;
    s32 wA4;
    u8 pad00A8[0x10];
    s16 mode;
    u8 pad00BA[4];
    s16 hBE;
    u8 pad00C0[0x18];
    u8 camD8[0x1D8];
    s32 tex[16];
    Slot_b046_01E032B0 slot[200];
    u8 pad34F0[0x100];
    s32 tex5[3];
    u8 pad35FC[0x14];
    s32 timer;
    u8 pad3614[8];
    s32 ot;
    u8 pad3620[0x1C];
    s16 joint[5];
    u8 pad3646[0x12];
    s16 code;
    s16 step;
    s8 jit[256];
    s8 jitA[256];
    s8 jitB[256];
    s8 jitC[256];
    u8 cam3A5C[0x174];
} Ctx_b046_01E032B0;

static s32 func_01E032B0_b046(s32 arg0, s32 code) {
    Ctx_b046_01E032B0 *g = (Ctx_b046_01E032B0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern s32 func_01E02170_b046();
    extern s32 func_01E022F0_b046();
    extern s32 func_01E02450_b046();
    extern s32 func_01E02690_b046();
    extern s32 func_01E02770_b046();
    extern s32 func_01E02890_b046();
    extern s32 func_01E02A00_b046();
    extern s32 func_01E02B80_b046();
    extern s32 func_01E02DB0_b046();
    extern s32 func_01E02F80_b046();
    extern s32 func_01E030F0_b046();
    extern s32 func_01E031B0_b046();
    extern void b046_01E03200();
    extern void b046_01E01ED0();
    extern void b046_01E01A60();
    extern void b046_01E00DD0(void *, void *, s32, Vec4f);
    extern void b046_01E00BB0();
    extern void b046_01E00920();
    extern void b046_01E01520();
    extern void b046_01E03F40();
    extern void b046_01E00FC0();
    Vec4f v;
    Vec4f m;
    Vec4f m2;
    Vec4f m3;
    Vec4f m4;
    Vec4f m5;
    Vec4f m6;
    s32 r1[4];
    s32 r2[4];
    s32 r3[4];
    u8 w[0x90] __attribute__((aligned(8)));
    s32 c;
    s32 i;
    s32 face;

    c = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3BD0);
        func_00107C10(g->cam3A5C);
        func_00107C10(g->camD8);
        g->code = code;
        g->timer = 163;
        g->joint[0] = func_001F5560(func_001F53A0(), 0xA, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x15, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x25, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x3C, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x25, 0);
        b046_01E03200(0, (void *)g);
        for (i = 0; i < 256; i++) {
            g->jit[i] = func_0019A5C8() % 10 - 5;
        }
        for (i = 180; i < 256; i++) {
            g->jit[i] = 0;
        }
        for (i = 0; i < 100; i++) {
            g->jitA[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jitA[i] = func_0019A5C8() % 5;
        }
        func_001F6160(func_001F53A0(), r1);
        face = r1[1] / 180.0f;
        for (i = 180; i < 256; i++) {
            if (face != 0) {
                g->jitA[i] = func_0019A5C8() % 4;
            } else {
                g->jitA[i] = -(func_0019A5C8() % 4);
            }
        }
        for (i = 0; i < 100; i++) {
            g->jitB[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jitB[i] = func_0019A5C8() % 6;
        }
        func_001F6160(func_001F53A0(), r2);
        face = r2[1] / 180.0f;
        for (i = 180; i < 256; i++) {
            if (face != 0) {
                g->jitB[i] = func_0019A5C8() % 20 + 5;
            } else {
                g->jitB[i] = -(func_0019A5C8() % 20 + 5);
            }
        }
        for (i = 0; i < 100; i++) {
            g->jitC[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jitC[i] = func_0019A5C8() % 3;
        }
        for (i = 180; i < 256; i++) {
            g->jitC[i] = func_0019A5C8() % 2 - 1;
            func_001F6160(func_001F53A0(), r3);
            if ((s32)(r3[1] / 180.0f) != 0) {
                g->jitC[i] += 2;
            } else {
                g->jitC[i] -= 2;
            }
        }
        return 0;
    }
    b046_01E01ED0(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E02170_b046) {
                func_01E02170_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E022F0_b046) {
                func_01E022F0_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02450_b046) {
                func_01E02450_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02690_b046) {
                func_01E02690_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02770_b046) {
                func_01E02770_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02890_b046) {
                func_01E02890_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02A00_b046) {
                func_01E02A00_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02B80_b046) {
                func_01E02B80_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02DB0_b046) {
                func_01E02DB0_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02F80_b046) {
                func_01E02F80_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E030F0_b046) {
                func_01E030F0_b046((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E031B0_b046) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E04300_b046;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E04308_b046;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            c++;
            if (g->slot[i].fn == func_01E02170_b046) {
                g->tex88 = g->tex5[2];
                func_00106080(&m, 0x14, g->slot[i].rot, 0);
                g->m94.v = m;
                g->mode = 10;
                g->x = g->slot[i].x;
                g->y = g->slot[i].y;
                g->z = g->slot[i].z;
                b046_01E01A60((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->mode = 0;
            }
            if (g->slot[i].fn == func_01E022F0_b046) {
                g->tex88 = g->tex5[0];
                func_00106080(&m2, 0x14, g->slot[i].rot, 0);
                g->m94.v = m2;
                v.x = g->slot[i].x;
                v.y = g->slot[i].y;
                v.z = g->slot[i].z;
                b046_01E00DD0((void *)g, (void *)&g->slot[i], 1, v);
                b046_01E00DD0((void *)g, (void *)&g->slot[i], 1, v);
                b046_01E00DD0((void *)g, (void *)&g->slot[i], 1, v);
            }
            if (g->slot[i].fn == func_01E02450_b046) {
                g->tex88 = g->tex5[0];
                func_00106080(&m3, 0x14, g->slot[i].rot, 0);
                g->m94.v = m3;
                v.x = g->slot[i].x;
                v.y = g->slot[i].y;
                v.z = g->slot[i].z;
                b046_01E00BB0((void *)g, (void *)&g->slot[i], 0);
            }
            if (g->slot[i].fn == func_01E02690_b046) {
                b046_01E00920(g, &g->slot[i], w, 0);
            }
            if (g->slot[i].fn == func_01E02770_b046) {
                g->tex88 = g->tex[15];
                func_00106080(&m4, 0x97, g->slot[i].rot, 0);
                g->m94.v = m4;
                g->m94.h.a = 0xA0;
                g->m94.h.b >>= 1;
                g->mode = 10;
                b046_01E01520(g, &g->slot[i], w, 0);
                g->mode = 0;
            }
            if (g->slot[i].fn == func_01E02A00_b046) {
                b046_01E03F40(g, &g->slot[i], w, 0);
                b046_01E03F40(g, &g->slot[i], w, 1);
            }
            if (g->slot[i].fn == func_01E02B80_b046) {
                g->tex88 = g->tex5[1];
                func_00106080(&m5, 0x14, g->slot[i].rot, 0);
                g->m94.v = m5;
                g->mode = 5;
                g->hBE = func_0019A5C8() % 8;
                g->wA4 = 0;
                g->x = g->slot[i].x;
                g->y = g->slot[i].y;
                g->z = g->slot[i].z;
                b046_01E00FC0((void *)g, (void *)&g->slot[i], 0, g->jitB);
                g->mode = 0;
            }
            if (g->slot[i].fn == func_01E02DB0_b046) {
                g->tex88 = g->tex5[1];
                func_00106080(&m6, 0x14, g->slot[i].rot, 0);
                g->m94.v = m6;
                g->m94.h.b >>= 1;
                g->mode = 10;
                g->hBE = 0;
                g->wA4 = 0;
                g->x = g->slot[i].x;
                g->y = g->slot[i].y;
                g->z = g->slot[i].z;
                b046_01E00FC0((void *)g, (void *)&g->slot[i], 0, g->jitC);
                g->mode = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 0x54) {
        return 1;
    }
    if (g->step == 0x96) {
        return 4;
    }
    if (g->step == 0x5E) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b046:01E03E20, 72 insns: take the first free slot of the 200-slot pool, clear it, give it the scene's
   colour twice, the scene matrix, the scene's value 0x3656 and the two arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b046_01E03E20;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b046_01E03E20 s[200];
    u8 pad34F0[0x124];
    u8 r, g, b, a;
    u8 pad3618[0x3E];
    s16 v;
} Pool_b046_01E03E20;

static s32 func_01E03E20_b046(Pool_b046_01E03E20 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b046_01E03E20 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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

/* shape b046:01E03F40, 210 insns, 2 copies: a spherical band of 18 quads (latitudes from the object's tilt and tilt+20, each
   segment 10 wide, 20 apart), scaled by size/1500, turned by the object's rotation; mode 0 only sets up the
   packet (texture 0x97) */

typedef struct {
    u8 pad0[0x2EC];
    void *texture;
    u8 pad2F0[0x332C];
    s32 ot;
    u8 pad3620[0xC];
    f32 dep;
    u8 pad3630[0x42C];
    u8 trig[1];
} Ctx_b046_01E03F40;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 tilt;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Band_b046_01E03F40;

static void func_01E03F40_b046(Ctx_b046_01E03F40 *c, Band_b046_01E03F40 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x10];
    s32 k;
    s32 j;
    s16 a;
    s16 t;
    f32 sc;
    f32 r0;
    f32 r1;
    f32 y;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc = o->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        quad[0].y = 90.0f * func_00108030(c->trig, o->tilt, 0) - 90.0f;
        quad[1].y = quad[0].y;
        quad[2].y = 90.0f * func_00108030(c->trig, o->tilt + 0x14, 0) - 90.0f;
        quad[3].y = quad[2].y;
        r0 = 90.0f * func_00108030(c->trig, o->tilt, 1);
        r1 = 90.0f * func_00108030(c->trig, o->tilt + 0x14, 1);
        a = 0;
        for (k = 0; k < 18; k++) {
            t = o->ang + a;
            quad[2].x = r1 * func_00108030(c->trig, t, 1);
            quad[2].z = r1 * func_00108030(c->trig, t, 0);
            quad[0].x = r0 * func_00108030(c->trig, t, 1);
            quad[0].z = r0 * func_00108030(c->trig, t, 0);
            t = o->ang + 10 + a;
            quad[3].x = r1 * func_00108030(c->trig, t, 1);
            quad[3].z = r1 * func_00108030(c->trig, t, 0);
            quad[1].x = r0 * func_00108030(c->trig, t, 1);
            quad[1].z = r0 * func_00108030(c->trig, t, 0);
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 0x14;
        }
    }
    }
}
