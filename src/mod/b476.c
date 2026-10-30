#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b476(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
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

static void func_01E00150_b476(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009F0_b476(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00150_b476 in the
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

static void func_01E00C80_b476(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00150_b476((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00E70_b476(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b476:01E012B0, 321 insns (PAINT_Fragment_9): b046:01E01A60 with the camera turn: draws obj->count (0 = 20)
   sprites of the definition's size along a curve read from three s8 tables (0x64 apart), each turned by the camera
   rotation / 180 (negated x and y) and the definition's angles, world matrix at the object's position turned by the
   definition's angles; mode 0 = depth from the projection, 1 = far z, 2 = -1 */

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
} Obj_b476_01E012B0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b476_01E012B0;

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
} Xyz_b476_01E012B0;

typedef struct {
    f32 u, v;
} Uv_b476_01E012B0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b476_01E012B0 uv;
    u64 pad18;
    Xyz_b476_01E012B0 v[4];
    u64 pad60[6];
} Pk_b476_01E012B0;

typedef struct {
    u64 tag;
    Pk_b476_01E012B0 pk;
} Buf_b476_01E012B0;

static void func_01E00150_b476();

static void func_01E012B0_b476(Obj_b476_01E012B0 *obj, Def_b476_01E012B0 *def, s32 mode, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b476_01E012B0 buf;
    Uv_b476_01E012B0 uv;
    s16 i;
    Pk_b476_01E012B0 *p;
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
    func_01E00150_b476(p, obj->f94, obj->fBE);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    func_00108EF0(m, &s, def->rot, &pos);
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 0, obj->fD8);
        func_00109100(m2, rot, 1, obj->fD8);
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

/* shape b476:01E017C0, 251 insns, 2 copies: a ring of 9 textured quads (radius size to size+20, 2 wide, 40 apart) turned on
   all three axes by the sprite's angles; side 0 draws only the quads behind (x < 0), side 1 only those in
   front, each count+1 times */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b476_01E017C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
    s16 ang;
} Ring_b476_01E017C0;

static void func_01E017C0_b476(Obj_b476_01E017C0 *o, Ring_b476_01E017C0 *s, s32 side) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 n;
    s32 k;
    s32 t;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, NULL, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        t = s->ang + a;
        quad[2].x = s->size * func_00108030(o->xD8, t, 1);
        quad[2].z = s->size * func_00108030(o->xD8, t, 0);
        quad[0].x = (s->size + 20) * func_00108030(o->xD8, t, 1);
        quad[0].z = (s->size + 20) * func_00108030(o->xD8, t, 0);
        t = a + (s->ang + 2);
        quad[3].x = s->size * func_00108030(o->xD8, t, 1);
        quad[3].z = s->size * func_00108030(o->xD8, t, 0);
        quad[1].x = (s->size + 20) * func_00108030(o->xD8, t, 1);
        quad[1].z = (s->size + 20) * func_00108030(o->xD8, t, 0);
        func_00109100(quad, s->rot, 0, o->xD8);
        func_00109100(quad, s->rot, 1, o->xD8);
        func_00109100(quad, s->rot, 2, o->xD8);
        if (side == 0) {
            if (quad[0].x < 0.0f) {
                if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                    for (n = 0; n < o->count + 1; n++) {
                        func_002075F0(p, o->ot, (u32)depth[0]);
                    }
                }
            }
        } else if (quad[0].x > 0.0f && func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
        a += 0x28;
    }
}

/* shape b476:01E01BB0, 283 insns (IWScatteredLine4): b046:01E01A60 with the camera turn: draws obj->count (0 = 20)
   sprites of the definition's size along a curve read from three s8 tables (0x64 apart), each turned by the camera
   rotation / 180 (negated x and y) and then by the definition's angles on three axes, at the definition's position;
   mode 0 draws only quads whose first corner x is below 0, else only those above 0 */

typedef struct {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[0x1E];
    u8 fD8[4];
} Obj_b476_01E01BB0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b476_01E01BB0;

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
} Xyz_b476_01E01BB0;

typedef struct {
    f32 u, v;
} Uv_b476_01E01BB0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b476_01E01BB0 uv;
    u64 pad18;
    Xyz_b476_01E01BB0 v[4];
    u64 pad60[6];
} Pk_b476_01E01BB0;

typedef struct {
    u64 tag;
    Pk_b476_01E01BB0 pk;
} Buf_b476_01E01BB0;

static void func_01E00150_b476();

static void func_01E01BB0_b476(Obj_b476_01E01BB0 *obj, Def_b476_01E01BB0 *def, s8 *base, s32 mode) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b476_01E01BB0 buf;
    Uv_b476_01E01BB0 uv;
    s16 i;
    Pk_b476_01E01BB0 *p;
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
    func_01E00150_b476(p, obj->f94, 0);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, 0, &pos);
    rot[1] /= 180;
    rot[0] /= 180;
    rot[1] = -rot[1];
    rot[0] = -rot[0];
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 0, obj->fD8);
        func_00109100(m2, rot, 1, obj->fD8);
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
            if (m2[0][0] < 0.0f) {
                if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                    func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
                }
            }
        } else if (m2[0][0] > 0.0f) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        }
    }
}

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

static void func_01E02020_b476(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
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
    func_01E00150_b476((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b476:01E02490 (B476_W_S), 378 insns, 1 copy: B476_W_S, the effect scene step: sets the colour, counts the
   frame (0x2E3A); frame 51 takes joint 1 into base, 52..64 copy base to pos; frames 190/210 spawn 0x1E02FD0 with flag
   0/1; 57..165 spawn 0x1E02DF0 at joints 0 and 1; 198/218 spawn 0x1E02EF0, five 0x1E02A80+0x1E03370 and 0x1E034D0;
   193..199/213..219 spawn five 0x1E03090+0x1E03220 with a random angle */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Pos_b476_01E02490;

typedef struct {
    u8 pad0[0x250];
    Pos_b476_01E02490 pos;
    u8 pad25C[0x28B0 - 0x25C];
    Vec4f base;
    u8 pad28C0[0x2DF4 - 0x28C0];
    u8 col[4];
    u8 pad2DF8[0x2E1C - 0x2DF8];
    s16 joint[6];
    u8 pad2E28[0x2E2E - 0x2E28];
    s16 angle;
    u8 pad2E30[0x2E36 - 0x2E30];
    s16 flag;
    u8 pad2E38[0x2E3A - 0x2E38];
    s16 t;
} Scene_b476_01E02490;

static void func_01E02490_b476(Scene_b476_01E02490 *g) {
    extern void b476_01E02A80(void);
    extern void b476_01E02DF0(void);
    extern void b476_01E02EF0(void);
    extern void b476_01E02FD0(void);
    extern void b476_01E03090(void);
    extern void b476_01E03220(void);
    extern void b476_01E03370(void);
    extern void b476_01E034D0(void);
    extern void b476_01E041C0(Scene_b476_01E02490 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    Vec4f v;
    s32 r[4];
    s32 r2[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 51) {
        func_001F5620(func_001F53A0(), g->joint[1], &g->base);
    }
    if (g->t > 51 && g->t <= 64) {
        func_001F5620(func_001F53A0(), g->joint[1], &v);
        for (i = 0; i < 6; i++) {
            g->pos.x = g->base.x;
            g->pos.y = g->base.y;
            g->pos.z = g->base.z;
        }
    }
    if (g->t == 190) {
        g->flag = 0;
        b476_01E041C0(g, b476_01E02FD0, 0);
    }
    if (g->t == 210) {
        g->flag = 1;
        b476_01E041C0(g, b476_01E02FD0, 0);
    }
    if (g->t >= 57 && g->t <= 165) {
        func_001F5620(func_001F53A0(), g->joint[0], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b476_01E041C0(g, b476_01E02DF0, 0);
        func_001F5620(func_001F53A0(), g->joint[1], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b476_01E041C0(g, b476_01E02DF0, 0);
    }
    if (g->t <= 106 && g->t >= 23) {
        func_001F5620(func_001F53A0(), g->joint[2], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 0;
        func_001F5620(func_001F53A0(), g->joint[3], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
    }
    if (g->t == 198) {
        func_001F5620(func_001F53A0(), g->joint[2], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b476_01E041C0(g, b476_01E02EF0, 0);
        for (i = 0; i < 5; i++) {
            b476_01E041C0(g, b476_01E02A80, 0);
            b476_01E041C0(g, b476_01E03370, 0);
        }
        b476_01E041C0(g, b476_01E034D0, 0);
    }
    if (g->t >= 193 && g->t <= 199) {
        func_001F5620(func_001F53A0(), g->joint[3], &v);
        for (i = 0; i < 5; i++) {
            g->angle = func_0019A5C8() % 360;
            func_001F6160(func_001F53A0(), r);
            if ((s32)(r[1] / 180.0f)) {
                g->flag = 0;
            } else {
                g->flag = 1;
            }
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b476_01E041C0(g, b476_01E03090, 0);
            b476_01E041C0(g, b476_01E03220, 0);
        }
    }
    if (g->t == 218) {
        func_001F5620(func_001F53A0(), g->joint[4], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b476_01E041C0(g, b476_01E02EF0, 0);
        for (i = 0; i < 5; i++) {
            b476_01E041C0(g, b476_01E02A80, 0);
            b476_01E041C0(g, b476_01E03370, 0);
        }
        b476_01E041C0(g, b476_01E034D0, 0);
    }
    if (g->t >= 213 && g->t <= 219) {
        func_001F5620(func_001F53A0(), g->joint[5], &v);
        for (i = 0; i < 5; i++) {
            g->angle = func_0019A5C8() % 360;
            func_001F6160(func_001F53A0(), r2);
            if ((s32)(r2[1] / 180.0f)) {
                g->flag = 1;
            } else {
                g->flag = 0;
            }
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b476_01E041C0(g, b476_01E03090, 0);
            b476_01E041C0(g, b476_01E03220, 0);
        }
    }
    if (g->t == 68) {
        func_001F5620(func_001F53A0(), g->joint[4], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
    }
}

/* shape b476:01E02A80, 85 insns: b573:01E02590 family: a white spark (size 15, random frame 0..7, angle, size 0..39) spinning a random 10..49 a tick: alpha 0x80 for a random 2..10 ticks, then out by 15 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    s32 w10;
    s32 w14;
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
} Glow_b476_01E02A80;

static s32 func_01E02A80_b476(s32 arg0, Glow_b476_01E02A80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 15;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 40 + 10;
        o->h8 = func_0019A5C8() % 40;
        o->h6 = func_0019A5C8() % 9 + 2;
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

/* shape b417:01E03510, 130 insns, 3 copies: step of a flickering spark: on state 1 picks a random spin and speed and an
   orange or cyan colour; the colour cycles orange / yellow / blue every tick; fades in by 0x40 for 2 ticks,
   then out by 9 until it ends; turns by its speed. */

typedef struct {
    u8 pad00[0xE];
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 ang;
} Obj_b417_01E03510;

static s32 func_01E02BE0_b476(void *arg0, Obj_b417_01E03510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 k;

    if (o->state == 1) {
        o->ang = 10;
        o->rot[0] = func_0019A5C8() % 0x4000 + 0x2000;
        o->rot[1] = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot[2] = func_0019A5C8() % 0x4000 - 0x2000;
        o->h34 = func_0019A5C8() % 7;
        o->state = 2;
        o->speed = func_0019A5C8() % 10 + 2;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c0, 0, 0x80, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    k = o->t % 3;
    if (k == 1) {
        func_001076F0(o->c0, 0x80, 0x40, 0);
    } else if (k == 2) {
        func_001076F0(o->c0, 0x80, 0x80, 0);
    } else {
        func_001076F0(o->c0, 0x10, 0x10, 0x80);
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    return 0;
}

/* shape b476:01E02DF0, 62 insns: a grey flicker: set up once (frame 60, random tilt and angle), full alpha for 12 frames,
   then fades by 15 until it ends; a random sub-frame 0..7 each frame */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 tilt;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b476_01E02DF0;

static s32 func_01E02DF0_b476(void *arg0, Obj_b476_01E02DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->tilt = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 0xC) {
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

static s32 func_01E02EF0_b476(void *arg0, Obj_b258_01E027A0 *o) {
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

/* shape b476:01E02FD0, 46 insns: a red glow at alpha 0x80 until the scene counter reaches 230, then fades by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b476_01E02FD0;

typedef struct {
    u8 pad[0x2E3A];
    s16 val;
} Game_b476_01E02FD0;

static s32 func_01E02FD0_b476(Game_b476_01E02FD0 *g, Glow_b476_01E02FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xFF, 0x20, 0x20);
        o->h6 = 3;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (g->val < 230) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b476:01E03090, 99 insns: a grey streak: frame -10 growing by 4..6 once started, random tilt -0x2000..0x1FFF, turn and
   sub-frame 0..6, width 20; alpha up by 0x40 for 2 frames, then down by 19 once grown past 20, and by 15 when the scene timer
   drops under 10 (b286:01E009B0 shape) */

typedef struct {
    u8 pad0[0x2DF0];
    s32 timer;
} Scene_b476_01E03090;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 grow;
    u8 padA[6];
    s32 rot0;
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b476_01E03090;

static s32 func_01E03090_b476(Scene_b476_01E03090 *g, Obj_b476_01E03090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = -0xA;
        o->rot0 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
        o->grow = func_0019A5C8() % 3 + 4;
        o->h6 = 0x14;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else {
        if (o->h38 > 0x14) {
            if (o->c0[3] > 0x14) {
                o->c0[3] -= 0x13;
            } else {
                o->state = 0;
            }
        }
        if (g->timer < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    if (o->t != 0) {
        o->h38 += o->grow;
    }
    o->t++;
    return 0;
}

/* shape b476:01E03220, 83 insns: on start 0x38 = 20, 0x34 = 1, random rotation 0x18, colour 0x80 grey, 0x3A keeps
   the old 0x30, speed 130..147 (0xE), 0x8 0..9, hold 3..9 (0x6); alpha grows by 0x40 (up to 0x80) during the hold,
   then fades by 10 and stops; 0x30 grows by the speed after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b476_01E03220;

static s32 func_01E03220_b476(s32 arg0, Fx_b476_01E03220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->f34 = 1;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f3A = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 18 + 0x82;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b476:01E03370, 85 insns: b476:01E02A80 twin: frame 0..3, spinning a random 40..75 a tick, held a random 5..14 ticks */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    s32 w10;
    s32 w14;
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
} Glow_b476_01E03370;

static s32 func_01E03370_b476(s32 arg0, Glow_b476_01E03370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 15;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 36 + 40;
        o->h8 = func_0019A5C8() % 40;
        o->h6 = func_0019A5C8() % 10 + 5;
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

/* shape b476:01E034D0, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x2DF0 is 1 */

typedef struct {
    u8 pad0[0x2870];
    f32 l0[4];
    f32 pos[3];
    u8 pad288C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad289C[0x554];
    s32 state;
} Scene_b476_01E034D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b476_01E034D0;

static s32 func_01E034D0_b476(Scene_b476_01E034D0 *g, Obj_b476_01E034D0 *o) {
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

/* shape b443:01E03FF0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2DF0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2DF0];
    s32 state;
} Game_b443_01E03FF0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b443_01E03FF0;

static s32 func_01E03650_b476(Game_b443_01E03FF0 *g, Fade_b443_01E03FF0 *o) {
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

static s32 func_01E03710_b476(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04800_b476;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04808_b476;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b476:01E03760, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-3 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x2AE0];
    s32 tex5[4];
} Scene_b476_01E03760;

static void func_01E03760_b476(s32 arg0, Scene_b476_01E03760 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 4; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b476", func_01E03810_b476);

/* shape b476:01E041C0, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2E36 and the two arguments; returns 1 if a
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
} Slot_b476_01E041C0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b476_01E041C0 s[150];
    u8 pad2870[0x584];
    u8 r, g, b, a;
    u8 pad2DF8[0x3E];
    s16 v;
} Pool_b476_01E041C0;

static s32 func_01E041C0_b476(Pool_b476_01E041C0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b476_01E041C0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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

/* shape b476:01E042E0, 311 insns: b256:01E04AB0's ribbon (4 spline quads per segment between two trails, module
   curve function shape b018:01E00EE0), one colour fading by alpha / (2 * n) per quad on the far edge. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b476_01E042E0;

typedef struct {
    Rgbaq_b476_01E042E0 c;
    u64 xyz;
} Vtx_b476_01E042E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b476_01E042E0 v[4];
    u8 tail[0x40];
} Pkt_b476_01E042E0;

typedef struct {
    u8 r, g, b, a;
} C4_b476_01E042E0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b476_01E042E0 col;
} Rib_b476_01E042E0;

static void func_01E042E0_b476(void *o, Rib_b476_01E042E0 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b476_01E042E0 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b476_01E042E0 pkt __attribute__((aligned(8)));
    C4_b476_01E042E0 col;
    s32 k;
    s32 j;
    s16 n;
    s32 x;
    s32 ot;
    Pkt_b476_01E042E0 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b476_01E042E0 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = s->col;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[0].c = func_00107740(&col);
            p->v[2].c = func_00107740(&col);
            x = col.a - (s16)(s->col.a / (n * 2));
            if (x > 0) {
                col.a = x;
            } else {
                col.a = 0;
            }
            p->v[1].c = func_00107740(&col);
            p->v[3].c = func_00107740(&col);
            if (k != 0) {
                A[0] = func_01E00E70_b476(pp, 0, t);
                B[0] = func_01E00E70_b476(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00E70_b476(pp, 0, t);
                B[1] = func_01E00E70_b476(pq, 0, t);
            } else {
                A[0] = func_01E00E70_b476(a4, 0, t);
                B[0] = func_01E00E70_b476(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00E70_b476(a4, 0, t);
                B[1] = func_01E00E70_b476(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}
