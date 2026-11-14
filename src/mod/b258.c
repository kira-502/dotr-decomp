#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b258(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

static void func_01E00100_b258(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b258:01E009A0, 187 insns: b116:01E009A0's sprite under the camera's own turn (not the object's), the view square
   then turned by the object's rotation (func_00109100 mode 2). Texture corners by the module helper (shape
   b003:01E00080). */

typedef struct Cam_b258_01E009A0 {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Cam_b258_01E009A0;

typedef struct Obj_b258_01E009A0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 trig[1];
} Obj_b258_01E009A0;

typedef struct Xyz_b258_01E009A0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b258_01E009A0;

typedef struct Uv_b258_01E009A0 {
    f32 u, v;
} Uv_b258_01E009A0;

typedef struct Pk_b258_01E009A0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b258_01E009A0 uv;
    u64 pad18;
    Xyz_b258_01E009A0 v[4];
    u64 pad60[6];
} Pk_b258_01E009A0;

typedef struct Buf_b258_01E009A0 {
    u64 tag;
    Pk_b258_01E009A0 pk;
} Buf_b258_01E009A0;

static void func_01E009A0_b258(Obj_b258_01E009A0 *obj, Cam_b258_01E009A0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100(void *, void *, s32, void *);
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b258_01E009A0 buf;
    Uv_b258_01E009A0 uv;
    s32 sel;
    s32 mode;
    Pk_b258_01E009A0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, cam->col);
    p->uv = uv;
    func_01E00100_b258((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, rot, &a);
    func_00108CE0(view, cam->size, cam->size);
    func_00109100(view, cam->rot, 2, obj->trig);
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

/* shape b119:01E00920, 258 insns, 4 copies: draws a flat ring of 18 quads like shape b112:01E00B60, turned by the ring's own
   rotation instead of the camera's; radii converted once. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E00920;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b119_01E00920;

static void func_01E00C90_b258(Obj_b119_01E00920 *o, Ring_b119_01E00920 *s, s32 mode, Vec4f pos) {
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
    s32 t;
    f32 ro;
    f32 ri;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = ro * func_00108030(o->xD8, t, 1);
            quad[0].z = ro * func_00108030(o->xD8, t, 0);
            quad[2].x = ri * func_00108030(o->xD8, t, 1);
            quad[2].z = ri * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

/* shape b116:01E011E0, 282 insns: full ring of 36 segments (10 table steps each) between an s16 inner and outer
   radius, variant of b082:01E00920 with a smaller data layout; blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b116_01E011E0;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 inner;
    s16 step;
} Data_b116_01E011E0;

static void func_01E010A0_b258(Obj_b116_01E011E0 *o, Data_b116_01E011E0 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
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
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    outer = data->outer;
    i = 0;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

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
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E01510_b258(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00100_b258((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b258:01E01A70 (B258_W_S), 576 insns, 1 copy: B258_W_S, the scene step: colour 0x80,0,0,0, counts the frame
   (0x89CA), frame 1 0x1E03830; keeps the two unit points, the four 0x2960 points and four copies of the first; tracks
   joints 0x8998..0x899E until 178, sinks them by the unit step until 240, then eases them to fixed targets set at
   240; frame 1 and 280 bursts of four kinds, from 290 every third frame up to 30 bolts 0x1E02F40/0x1E032B0 with three
   0x1E02A60, then drifts the bolts toward joint 0x89A8 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x28A0 - 0x25C];
    Vec4f p[4];
    Vec4f q[4];
    Vec4f tgt[4];
    Vec4f w[4];
    Vec4f d[30];
    u8 pad2B80[0x8974 - 0x2B80];
    u8 col[4];
    u8 pad8978[0x8998 - 0x8978];
    s16 j[4];
    u8 pad89A0[0x89A8 - 0x89A0];
    s16 jx;
    u8 pad89AA[0x89B8 - 0x89AA];
    s16 n;
    u8 pad89BA[0x89C4 - 0x89BA];
    s16 kind;
    s16 flag;
    u8 pad89C8[2];
    s16 t;
} Scene_b258_01E01A70;

static void func_01E01A70_b258(Scene_b258_01E01A70 *g) {
    extern void b258_01E04E70();
    extern void func_01E02370_b258();
    extern void func_01E02500_b258();
    extern void func_01E02650_b258();
    extern void func_01E02A60_b258();
    extern void func_01E02F40_b258();
    extern void func_01E032B0_b258();
    extern void func_01E034A0_b258();
    extern void func_01E03830_b258();
    extern void func_001F7260(s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    f32 v[2][4];
    s32 k;
    f32 f;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F7260(0);
    if (g->t == 1) {
        b258_01E04E70(g, func_01E03830_b258, 0);
    }
    func_001F5F90(func_001F5380(), v[0]);
    func_001F5F90(func_001F53A0(), v[1]);
    func_001F5F90(func_001F53A0(), &g->w[0]);
    func_001F5F90(func_001F53A0(), &g->w[1]);
    func_001F5F90(func_001F53A0(), &g->w[2]);
    func_001F5F90(func_001F53A0(), &g->w[3]);
    g->q[0] = *(Vec4f *)v[0];
    g->q[1] = *(Vec4f *)v[0];
    g->q[2] = *(Vec4f *)v[0];
    g->q[3] = *(Vec4f *)v[0];
    v[0][0] = (v[1][0] - v[0][0]) / 73.0f;
    v[0][1] = (v[1][1] - v[0][1]) / 73.0f;
    v[0][2] = (v[1][2] - v[0][2]) / 73.0f;
    if (g->t < 0xB2) {
        func_001F5620(func_001F53A0(), g->j[0], &g->p[0]);
        func_001F5620(func_001F53A0(), g->j[1], &g->p[1]);
        func_001F5620(func_001F53A0(), g->j[2], &g->p[2]);
        func_001F5620(func_001F53A0(), g->j[3], &g->p[3]);
    } else if (g->t < 0xF0) {
        if (g->flag != 0) {
            for (i = 0; i < 4; i++) {
                g->p[i].z -= v[0][2];
            }
        } else {
            for (i = 0; i < 4; i++) {
                g->p[i].z -= v[0][2];
            }
        }
    } else {
        if (g->t == 0xF0) {
            func_001F5F90(func_001F5380(), v[0]);
            for (i = 0; i < 4; i++) {
                g->tgt[i] = *(Vec4f *)v[0];
            }
            g->tgt[0].x = 15.0f;
            g->tgt[1].x = -15.0f;
            g->tgt[2].x = 15.0f;
            g->tgt[3].x = -15.0f;
            g->tgt[0].y = 80.0f;
            g->tgt[1].y = 80.0f;
            g->tgt[2].y = 50.0f;
            g->tgt[3].y = 50.0f;
        }
        for (i = 0; i < 4; i++) {
            g->p[i].x += (g->tgt[i].x - g->p[i].x) / 30.0f;
            g->p[i].y += (g->tgt[i].y - g->p[i].y) / 30.0f;
        }
    }
    if (g->t < 2) {
        g->kind = 2;
        b258_01E04E70(g, func_01E02650_b258, 0);
        b258_01E04E70(g, func_01E02500_b258, 0);
        b258_01E04E70(g, func_01E02370_b258, 0);
        g->kind = 3;
        b258_01E04E70(g, func_01E02650_b258, 0);
        b258_01E04E70(g, func_01E02500_b258, 0);
        b258_01E04E70(g, func_01E02370_b258, 0);
        g->kind = 0;
        b258_01E04E70(g, func_01E02650_b258, 0);
        b258_01E04E70(g, func_01E02500_b258, 0);
        b258_01E04E70(g, func_01E02370_b258, 0);
        g->kind = 1;
        b258_01E04E70(g, func_01E02650_b258, 0);
        b258_01E04E70(g, func_01E02500_b258, 0);
        b258_01E04E70(g, func_01E02370_b258, 0);
    }
    if (g->t == 0x118) {
        g->kind = 2;
        b258_01E04E70(g, func_01E034A0_b258, 0);
        g->kind = 3;
        b258_01E04E70(g, func_01E034A0_b258, 0);
        g->kind = 0;
        b258_01E04E70(g, func_01E034A0_b258, 0);
        g->kind = 1;
        b258_01E04E70(g, func_01E034A0_b258, 0);
    }
    if (g->t < 0x187) {
        g->pos[0] = g->p[0].x;
        g->pos[1] = g->p[0].y;
        g->pos[2] = g->p[0].z;
        g->pos[0] = g->p[1].x;
        g->pos[1] = g->p[1].y;
        g->pos[2] = g->p[1].z;
        g->pos[0] = g->p[2].x;
        g->pos[1] = g->p[2].y;
        g->pos[2] = g->p[2].z;
        g->pos[0] = g->p[3].x;
        g->pos[1] = g->p[3].y;
        g->pos[2] = g->p[3].z;
    }
    if (g->t >= 0x122) {
        if (g->n < 30 && g->t % 3 == 1) {
            g->kind = g->n;
            b258_01E04E70(g, func_01E02F40_b258, 0);
            b258_01E04E70(g, func_01E032B0_b258, 0);
            k = g->n % 4;
            g->pos[0] = g->p[k].x;
            g->pos[1] = g->p[k].y;
            g->pos[2] = g->p[k].z;
            b258_01E04E70(g, func_01E02A60_b258, 0);
            b258_01E04E70(g, func_01E02A60_b258, 0);
            b258_01E04E70(g, func_01E02A60_b258, 0);
            g->n++;
        }
    }
    if (g->t > 0x122) {
        func_001F5620(func_001F5380(), g->jx, v[0]);
        for (i = 0; i < g->n; i++) {
            k = i % 4;
            f = (v[0][0] - g->p[k].x) / 6.0f;
            g->d[i].x += f + func_0019A5C8() % 16 - 8.0f;
            g->d[i].y += (v[0][1] - g->p[k].y) / 6.0f + func_0019A5C8() % 16 - 8.0f;
            g->d[i].z += (v[0][2] - g->p[k].z) / 6.0f;
        }
    }
}

/* shape b258:01E02370, 99 insns: on start 0x38 = 50, colours (0xC0, 0x70, 0) / (0x20, 0x10, 0), random 0x3A, variant
   0..7; 0x6 = 0 each tick; alpha 0x80 on the first tick, flickering 0x80/0x70 while the game step 0x89CA is below 0x186, then
   fades by 9 and stops; from step 0xB0 0x38 grows by 5 up to 100; the rotation at 0x10 advances 0x4000 */

typedef struct {
    u8 pad0[0x89CA];
    s16 step;
} Game_b258_01E02370;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b258_01E02370;

static s32 func_01E02370_b258(Game_b258_01E02370 *g, Fx_b258_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        func_001076F0(o->col, 0xC0, 0x70, 0);
        func_001076F0(o->col2, 0x20, 0x10, 0);
        o->f3A = func_0019A5C8() % 360;
        o->f34 = func_0019A5C8() % 8;
        o->mode = 2;
    }
    o->f6 = 0;
    if (o->tick <= 0) {
        o->col[3] = 0x80;
    } else if (g->step < 0x186) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0x80;
        } else {
            o->col[3] = 0x70;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->step > 0xAF) {
        if (o->f38 < 100) {
            o->f38 += 5;
        }
    }
    o->tick++;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    return 0;
}

/* shape b258:01E02500, 84 insns: a white spark (size 10 growing 2 up to 30 once the scene value reaches 168) at a random angle, frame from its kind + 4: flickers 0x80 / 0x60 until scene value 390, then out by 9 and ends */

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
} Glow_b258_01E02500;

typedef struct {
    u8 pad[0x89CA];
    s16 val;
} Game_b258_01E02500;

static s32 func_01E02500_b258(Game_b258_01E02500 *g, Glow_b258_01E02500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->ang = func_0019A5C8() % 360;
        o->kind = o->h30 + 4;
        o->mode = 2;
    }
    if (o->tick < 1) {
        o->col[3] = 0x80;
    } else if (g->val < 390) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0x80;
        } else {
            o->col[3] = 0x60;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->val >= 168) {
        if (o->f38 < 30) {
            o->f38 += 2;
        }
    }
    o->tick++;
    return 0;
}

/* shape b258:01E02650, 83 insns: a grey blinker: frame 8 growing by 2 up to 30 once the game timer reaches 0xA8, random angle,
   sub-frame from its kind; full alpha on the first frame, blinks 0x80 / 0x60 until the timer reaches 0xAA, then fades by 9 */

typedef struct {
    u8 pad0[0x89CA];
    s16 timer;
} Game_b258_01E02650;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b258_01E02650;

static s32 func_01E02650_b258(Game_b258_01E02650 *g, Obj_b258_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 8;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->sub = o->kind;
        o->state = 2;
    }
    if (o->t < 1) {
        o->c0[3] = 0x80;
    } else if (g->timer < 0xAA) {
        if (o->t % 2 == 1) {
            o->c0[3] = 0x80;
        } else {
            o->c0[3] = 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (g->timer >= 0xA8) {
        if (o->h38 < 0x1E) {
            o->h38 += 2;
        }
    }
    o->t++;
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

static s32 func_01E027A0_b258(void *arg0, Obj_b258_01E027A0 *o) {
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

/* shape b258:01E02880, 117 insns: on start colour white, random 0x3A, variant 0..7, 0xE 0..1, 0x6 0..10, lifetime 5..24
   (0x1C); alpha 0x80 on the first tick, then white on ticks whose parity matches 0xE else 0x80 grey; once the game step
   0x89CA reaches 0xA8 0x38 is re-rolled 10..69 each tick; after the first tick 0x30 counts up and it stops past the
   lifetime */

typedef struct {
    u8 pad0[0x89CA];
    s16 step;
} Game_b258_01E02880;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[6];
    s16 fE;
    u8 pad10[0xC];
    s32 life;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b258_01E02880;

static s32 func_01E02880_b258(Game_b258_01E02880 *g, Fx_b258_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 life;

    if (o->mode == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f3A = func_0019A5C8() % 360;
        o->f34 = func_0019A5C8() % 8;
        o->fE = func_0019A5C8() % 2;
        o->f6 = func_0019A5C8() % 11;
        o->life = func_0019A5C8() % 20 + 5;
        o->mode = 2;
    }
    if (o->tick <= 0) {
        o->col[3] = 0x80;
    } else if (o->tick % 2 == o->fE) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    life = o->life;
    if (g->step >= 0xA8) {
        o->f38 = func_0019A5C8() % 60 + 10;
    }
    if (o->tick != 0) {
        o->f30++;
    }
    if (o->f30 > life) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b258:01E02A60, 105 insns: on start 0x38 = 15, variant 3, colour (0x80, 0x80, 8), 0xA keeps the old 0x30, 0x30
   10..29, random 0x3A, speed 5..14 (0xE), 0x8 0..34, hold 2..6 (0x6); alpha grows by 0x40 (up to 0x80) during the
   hold, then fades by 11 and stops; after the first tick 0x30 grows by the speed; 0x38 grows by 3 every other tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[2];
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
} Fx_b258_01E02A60;

static s32 func_01E02A60_b258(s32 arg0, Fx_b258_01E02A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 15;
        o->f34 = 3;
        func_001076F0(o->col, 0x80, 0x80, 8);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 20 + 10;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 5;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick % 2 == 1) {
        o->f38 += 3;
    }
    o->tick++;
    return 0;
}

/* shape b258:01E02C10, 92 insns: b573:01E02590 family: a pale yellow spark (size 5) spinning a random 32..41 a tick from a random 30..179 (old angle moved to +0xA), random size 0..34, held 2..6 ticks: in by 64 up to 0x80, then out by 11 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b258_01E02C10;

static s32 func_01E02C10_b258(s32 arg0, Glow_b258_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 5;
        o->kind = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0x40);
        o->hA = o->h30;
        o->h30 = func_0019A5C8() % 150 + 30;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 32;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 2;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b258:01E02D80, 109 insns: a pale spark: frame 40..69, random sub-frame 0..3 stepping up to 7 every other frame, start
   height 100..299 (old one kept), angle, rise 5..9, width 0..34, hold 1..2; alpha 0xC0 until the hold, then down by 29 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 y0;
    u8 padC[2];
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
} Obj_b258_01E02D80;

static s32 func_01E02D80_b258(void *arg0, Obj_b258_01E02D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 30 + 0x28;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        o->y0 = o->y;
        o->y = func_0019A5C8() % 200 + 0x64;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 5 + 5;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 1;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->t++;
    return 0;
}

/* shape b258:01E02F40, 220 insns: one trail effect's step: on state 1 the trail of slot h30 (49 points) and its
   head are set from anchor h30 % 4 (state 2, life 30); grow h6 up to 10 for 7 ticks, then shrink it; alpha 0xC0
   for 7 ticks, then fade by 9 (state 0 below 11) and life -3; colour 0x80 on even ticks, 0xF0 on odd; draw the
   trail while young; at tick 7 spawn 0x1E033B0, four 0x1E02D80 and fifteen 0x1E02C10 from the trail start */

typedef struct {
    f32 x, y, z, w;
} Vec_b258_01E02F40;

typedef struct {
    Vec_b258_01E02F40 p[50];
} Trail_b258_01E02F40;

typedef struct {
    u8 pad0[0x250];
    Vec_b258_01E02F40 pos;
    u8 pad260[0x28A0 - 0x260];
    Vec_b258_01E02F40 anchor[16];
    Vec_b258_01E02F40 head[0x1E];
    Trail_b258_01E02F40 trail[0x1C];
    u8 pad[0x89C4 - 0x2B80 - 0x1C * 0x320];
    s16 slot;
} Scene_b258_01E02F40;

typedef struct {
    u8 pad0[6];
    s16 size;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[4];
    s16 id;
    s16 tick;
    u8 pad34[2];
    s16 state;
    s16 life;
} Fx_b258_01E02F40;

static s32 func_01E02F40_b258(Scene_b258_01E02F40 *g, Fx_b258_01E02F40 *o) {
    extern void b258_01E00080(void *, s32, s32, void *);
    extern s32 b258_01E04E70(void *, s32, s32);
    extern void b258_01E033B0(void);
    extern void b258_01E02D80(void);
    extern void b258_01E02C10(void);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 m;
    s32 k;
    s16 i;
    Vec_b258_01E02F40 *d;

    m = o->id % 4;
    if (o->state == 1) {
        o->size = 1;
        o->col[3] = 0;
        d = g->trail[o->id].p;
        for (k = 0; k < 49; k++) {
            d->x = g->anchor[m].x;
            d->y = g->anchor[m].y;
            d->z = g->anchor[m].z;
            d++;
        }
        g->head[o->id] = g->anchor[m];
        o->life = 30;
        o->state = 2;
    }
    if (o->tick <= 6) {
        if (o->size <= 9) {
            o->size++;
        }
    } else {
        if (o->size > 0) {
            o->size--;
        }
    }
    if (o->tick <= 6) {
        o->col[3] = 0xC0;
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->life > 0) {
            o->life -= 3;
        }
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
    }
    if (o->tick <= 6) {
        b258_01E00080(&g->trail[o->id].p[49], 0x32, 0, &g->head[o->id]);
    }
    if (o->tick == 7) {
        g->slot = o->id;
        b258_01E04E70(g, (s32)b258_01E033B0, 0);
        b258_01E04E70(g, (s32)b258_01E02D80, 0);
        b258_01E04E70(g, (s32)b258_01E02D80, 0);
        b258_01E04E70(g, (s32)b258_01E02D80, 0);
        b258_01E04E70(g, (s32)b258_01E02D80, 0);
        g->pos.x = g->trail[o->id].p[0].x;
        g->pos.y = g->trail[o->id].p[0].y;
        g->pos.z = g->trail[o->id].p[0].z;
        for (i = 0; i < 15; i++) {
            b258_01E04E70(g, (s32)b258_01E02C10, 0);
        }
    }
    o->tick++;
    return 0;
}

/* shape b258:01E032B0, 63 insns: on start 0x38 = 0x32, colour 0xF0 grey, second colour (0xF0, 0x80, 0x10) with alpha
   0, random 0x3A; alpha grows by 0x60 (below 0xC) for 5 ticks, then fades by 15 and stops; the rotation at 0x10
   advances 0x4000 each tick */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b258_01E032B0;

static s32 func_01E032B0_b258(s32 arg0, Fx_b258_01E032B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x32;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0x80, 0x10);
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b258:01E033B0, 58 insns: a white/orange two-colour glow of size 220 at a random angle, spun by 0x4000 a tick: alpha 0xA0 for 3 ticks, then out by 29 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    u8 pad8[8];
    s32 w10;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b258_01E033B0;

static s32 func_01E033B0_b258(s32 arg0, Glow_b258_01E033B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xDC;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x80, 0x40, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        o->col[3] = 0xA0;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w10);
    o->w10 += 0x4000;
    o->tick++;
    return 0;
}

/* shape b258:01E034A0, 131 insns: a white/grey double flash timed by the game counter at g+0x89CA: on start size 32,
   white and grey colours, a random angle and frame 0..7; both alphas up by 32 for 5 ticks, then the white one blinks
   0x80/0x70 until the counter reaches 390, after which both fade by 9 until it ends; the colours blink bright/dim on
   the counter's parity; it spins by 0x4000 */

typedef struct {
    u8 pad0[0x89CA];
    s16 count;
} Game_b258_01E034A0;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[8];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Obj_b258_01E034A0;

static s32 func_01E034A0_b258(Game_b258_01E034A0 *g, Obj_b258_01E034A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 0x20;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 8;
        o->mode = 2;
    }
    o->f6 = 0;
    if (o->t < 5) {
        o->c1[3] += 0x20;
        o->c0[3] += 0x20;
    } else if (g->count < 390) {
        if (o->t % 2 == 1) {
            o->c1[3] = 0x80;
        } else {
            o->c1[3] = 0x70;
        }
    } else {
        if (o->c1[3] > 10) {
            o->c1[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->c0[3] > 10) {
            o->c0[3] -= 9;
        }
    }
    if (g->count % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    }
    o->t++;
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    return 0;
}

/* shape b258:01E036B0, 95 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x8970 is 1 */

typedef struct {
    u8 pad0[0x2870];
    f32 l0[4];
    f32 pos[3];
    u8 pad288C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad289C[0x60D4];
    s32 state;
} Scene_b258_01E036B0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b258_01E036B0;

static s32 func_01E036B0_b258(Scene_b258_01E036B0 *g, Obj_b258_01E036B0 *o) {
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

/* shape b258:01E03830, 51 insns: constant variant of b205:01E01E50 (volume fade by game state, b003:01E02330 family): state at 0x8970
   limit 0x1E, floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x8970];
    s32 state;
} Game_b258_01E03830;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b258_01E03830;

static s32 func_01E03830_b258(Game_b258_01E03830 *g, Fade_b258_01E03830 *o) {
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

static s32 func_01E03900_b258(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05B80_b258;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05B88_b258;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b258:01E03950, b734:01E03310 family: textures group 4 cells 0-2 and 13-15, group 5 cells 0-4 (table past 0x8000) */

typedef struct {
    u8 pad0[0x2b0];
    s32 tex[16];
    u8 padT[0x8660];
    s32 tex5[5];
} Scene_b258_01E03950;

static void func_01E03950_b258(s32 arg0, Scene_b258_01E03950 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 5; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b258", func_01E03A00_b258);

/* shape b258:01E04E70, 90 insns: c035:01E01150 family: take the first free glow slot of 150 (0x40 bytes each, at ctx+0x2F0), clear it, give it the scene colour twice, the scene position, its angle and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b258_01E04E70;

typedef struct {
    u8 pad0[0x250];
    u8 pos[0xA0];
    Glow_b258_01E04E70 slot[150];
    u8 padEnd[0x8974 - 0x2F0 - 150 * 0x40];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad8978[0x4C];
    s16 h30;
} Ctx_b258_01E04E70;

static s32 func_01E04E70_b258(Ctx_b258_01E04E70 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Glow_b258_01E04E70 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].mode == 0) {
            func_00195108(&ctx->slot[i], 0x40);
            ctx->slot[i].mode = 1;
            s = &ctx->slot[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, ctx->pos, 0);
        s->h30 = ctx->h30;
        s->w20 = arg2;
        s->w24 = arg1;
        return 1;
    }
    return 0;
}

/* shape b258:01E04FE0 (B258PAINT_RAIN20), 730 insns, 1 copy: B108PAINT_RAIN21's beam (b108:01E03430) from the
   object's start point, one step of 1.5 (clamped to 1) per segment, s16 width */

typedef struct {
    f32 x, y, z, w;
} Vec_b258_01E04FE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b258_01E04FE0;

typedef struct {
    u8 r, g, b, a;
} Col_b258_01E04FE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b258_01E04FE0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b258_01E04FE0 c;
        u64 st;
        Xyz_b258_01E04FE0 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b258_01E04FE0;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b258_01E04FE0;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[6];
    s16 start;
    s32 rot[4];
    u8 pad20[8];
    Col_b258_01E04FE0 col0;
    Col_b258_01E04FE0 col1;
    u8 pad30[8];
    s16 width;
} Beam_b258_01E04FE0;

static inline Vec_b258_01E04FE0 spline_b258_01E04FE0(Vec_b258_01E04FE0 *p, s32 type, f32 t) {
    Vec_b258_01E04FE0 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

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

/* pts aligned: its spill slot, needed for the match */

static void func_01E04FE0_b258(Ctx_b258_01E04FE0 *c, Beam_b258_01E04FE0 *an, Vec_b258_01E04FE0 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b258_01E04FE0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b258_01E04FE0 ab[2];
    Vec_b258_01E04FE0 ctrl[4];
    Vec_b258_01E04FE0 prev;
    Vec_b258_01E04FE0 q[4];
    Vec_b258_01E04FE0 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b258_01E04FE0 pkt __attribute__((aligned(8)));
    Col_b258_01E04FE0 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b258_01E04FE0 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    n = an->count;
    w /= 10.0f;
    w0 = w;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    for (i = an->start; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 1; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b258_01E04FE0(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b258_01E04FE0(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b258_01E04FE0(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b258_01E04FE0(ctrl, 0, t);
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (8.0f * n);
            for (k = 0; k < 2; k++) {
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
                if (k == 0) {
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if (flags == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                } else if (flags == 2) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, -1);
                    }
                }
            }
        }
    }
}
