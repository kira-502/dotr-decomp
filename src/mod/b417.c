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

static void func_01E00080_b417(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;
typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;
typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E00920_b417(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b417((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
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

static void func_01E00C50_b417(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
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
    func_01E00080_b417((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E010C0_b417(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b417 in the
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

static void func_01E01350_b417(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b417((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b148:01E01540, 325 insns: b046:01E00FC0 family: a row of small sprites (count, or 20) at the object position, each
   shaken by the table offsets and turned on all three axes by the sprite rotation; depth mode 0/1/2. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b148_01E01540;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b148_01E01540 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b148_01E01540;

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
} Obj_b148_01E01540;

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
} Spr_b148_01E01540;

static void func_01E01540_b417(Obj_b148_01E01540 *o, Spr_b148_01E01540 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b148_01E01540 func_00107740(void *);
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
    Pkt_b148_01E01540 pkt __attribute__((aligned(8)));
    s16 i;
    f32 f;
    s16 n;
    Pkt_b148_01E01540 *p;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b148_01E01540 *)(s32)&pkt;
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
    func_01E00080_b417((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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
    p2.x = o->pos.x;
    p2.y = o->pos.y;
    p2.z = o->pos.z;
    func_00108EF0(m, &scale, rot, &p2);
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
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
        func_00109100(quad, &s->rot, 0, o->xD8);
        func_00109100(quad, &s->rot, 1, o->xD8);
        func_00109100(quad, &s->rot, 2, o->xD8);
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

static void func_01E01A60_b417(Obj_b046_01E00FC0 *o, Spr_b046_01E00FC0 *s, s32 mode, s8 *tbl) {
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
    func_01E00080_b417((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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

/* shape b148:01E01FC0, 345 insns (b046:01E00FC0 with the side corners' x zeroed): draws a row of small sprites (count, or 20) at the object position: each a
   standing quad turned by the sprite rotation, shaken by a per-entry table offset that grows along the row, its
   lower edge pinned at +-size/2; blend from the object's float mode, depth mode 0/1/2. Texture corners by the
   module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b148_01E01FC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b148_01E01FC0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b148_01E01FC0;

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
} Obj_b148_01E01FC0;

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
} Spr_b148_01E01FC0;

static void func_01E01FC0_b417(Obj_b148_01E01FC0 *o, Spr_b148_01E01FC0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b148_01E01FC0 func_00107740(void *);
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
    Pkt_b148_01E01FC0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 f;
    s16 n;
    Pkt_b148_01E01FC0 *p;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b148_01E01FC0 *)(s32)&pkt;
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
    func_01E00080_b417((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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
        quad[2].x = 0.0f;
        quad[3].z = s->size >> 1;
        quad[3].y = 0.0f;
        quad[3].x = 0.0f;
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

/* OVL_WARM */

/* shape b064:01E00C10, 200 insns: variant of b027:01E02590 (ring of quads around a point): two colour sets,
   ring width from the anim (s16 at 6) instead of 20, 18 segments 20 apart */

typedef struct {
    f32 x, y, z, w;
} Vec_b148_01E02530;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b148_01E02530;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b148_01E02530;

static void func_01E02530_b417(Obj_b148_01E02530 *o, Anim_b148_01E02530 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b148_01E02530 quad[4];
    Vec_b148_01E02530 pos;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col + 4, 2);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    func_00108EF0(m, 0, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 40;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b417", func_01E02790_b417);

/* shape b417:01E02CD0 (B417_W_S), 432 insns, 1 copy (-O3,p): B417_W_S, the scene script: sets the colour, counts the
   frame (0x365A); frame 51 takes joint 1 into base, 52..64 copy base to pos; up to 136 spawn 0x1E03720 at joints 0/1;
   23..36 and 23..45 spawn 0x1E04070/0x1E03EF0 at joints 2/3 lifted 15/10; 5..7 spawn 0x1E042A0; frame 47 spawns the
   burst; 68 and 68..70 spawn 0x1E03390/0x1E03510 */

#pragma optimization_level 3

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Pos_b417_01E02CD0;

typedef struct {
    u8 pad0[0x250];
    Pos_b417_01E02CD0 pos;
    u8 pad25C[0x3530 - 0x25C];
    Vec4f base;
    u8 pad3540[0x3614 - 0x3540];
    u8 col[4];
    u8 pad3618[0x363C - 0x3618];
    s16 joint[5];
    u8 pad3646[0x3656 - 0x3646];
    s16 flag;
    u8 pad3658[0x365A - 0x3658];
    s16 t;
} Scene_b417_01E02CD0;

static void func_01E02CD0_b417(Scene_b417_01E02CD0 *g) {
    extern void b417_01E03390(void);
    extern void b417_01E03510(void);
    extern void b417_01E03720(void);
    extern void b417_01E03830(void);
    extern void b417_01E03910(void);
    extern void b417_01E03A80(void);
    extern void b417_01E03BF0(void);
    extern void b417_01E03D80(void);
    extern void b417_01E03EF0(void);
    extern void b417_01E04070(void);
    extern void b417_01E042A0(void);
    extern void b417_01E04470(void);
    extern void b417_01E05590(Scene_b417_01E02CD0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    Vec4f m;
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
    if (g->t <= 136) {
        func_001F5620(func_001F53A0(), g->joint[0], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b417_01E05590(g, b417_01E03720, 0);
        func_001F5620(func_001F53A0(), g->joint[1], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b417_01E05590(g, b417_01E03720, 0);
    }
    if (g->t <= 36 && g->t >= 23) {
        func_001F5620(func_001F53A0(), g->joint[2], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 15.0f;
        g->pos.z = v.z;
        g->flag = 0;
        b417_01E05590(g, b417_01E04070, 0);
        func_001F5620(func_001F53A0(), g->joint[3], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 15.0f;
        g->pos.z = v.z;
        g->flag = 1;
        b417_01E05590(g, b417_01E04070, 0);
    }
    if (g->t <= 45 && g->t >= 23) {
        func_001F5620(func_001F53A0(), g->joint[2], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 10.0f;
        g->pos.z = v.z;
        b417_01E05590(g, b417_01E03EF0, 0);
        func_001F5620(func_001F53A0(), g->joint[3], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 10.0f;
        g->pos.z = v.z;
        b417_01E05590(g, b417_01E03EF0, 0);
    }
    if (g->t <= 7 && g->t >= 5) {
        func_001F5620(func_001F53A0(), g->joint[0], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 15.0f;
        g->pos.z = v.z;
        g->flag = 0;
        b417_01E05590(g, b417_01E042A0, 0);
        func_001F5620(func_001F53A0(), g->joint[1], &v);
        g->pos.x = v.x;
        g->pos.y = v.y - 15.0f;
        g->pos.z = v.z;
        g->flag = 1;
        b417_01E05590(g, b417_01E042A0, 0);
    }
    if (g->t == 26) {
        func_001F5620(func_001F53A0(), g->joint[2], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
        g->pos.y = 1.0f + v.y;
    }
    if (g->t == 47) {
        func_001F5620(func_001F53A0(), g->joint[0], &v);
        func_001F5F90(func_001F5380(), &m);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
    }
    if (g->t == 47) {
        func_001F5620(func_001F53A0(), g->joint[4], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b417_01E05590(g, b417_01E03BF0, 0);
        }
        for (i = 0; i < 8; i++) {
            b417_01E05590(g, b417_01E03910, 0);
        }
        for (i = 0; i < 1; i++) {
            b417_01E05590(g, b417_01E03A80, 0);
        }
        for (i = 0; i < 10; i++) {
            b417_01E05590(g, b417_01E03D80, 0);
        }
        b417_01E05590(g, b417_01E03830, 0);
        b417_01E05590(g, b417_01E04470, 0);
    }
    if (g->t == 68) {
        func_001F5620(func_001F53A0(), g->joint[4], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->flag = 1;
        b417_01E05590(g, b417_01E03830, 0);
        for (i = 0; i < 10; i++) {
            b417_01E05590(g, b417_01E03390, 0);
        }
        b417_01E05590(g, b417_01E04470, 0);
    }
    if (g->t == 68 || g->t == 69 || g->t == 70) {
        func_001F5620(func_001F53A0(), g->joint[4], &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        for (i = 0; i < 3; i++) {
            b417_01E05590(g, b417_01E03510, 0);
        }
    }
}
#pragma optimization_level reset

/* shape b417:01E03390, 96 insns: b573:01E02590 family: a grey spark (size 54, frame 1, random roll) spinning a random 80..109 a tick from 0..99 (old angle moved to +0xA), size 0..19, held 1..2 ticks: in by 64 up to 0x80, then out by 15 and ends */

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
} Glow_b417_01E03390;

static s32 func_01E03390_b417(s32 arg0, Glow_b417_01E03390 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 54;
        o->kind = 1;
        o->w18 = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->hA = o->h30;
        o->h30 = func_0019A5C8() % 100;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 30 + 80;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
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

static s32 func_01E03510_b417(void *arg0, Obj_b417_01E03510 *o) {
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

static s32 func_01E03720_b417(void *arg0, Obj_b148_01E032D0 *o) {
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

static s32 func_01E03830_b417(void *arg0, Obj_b258_01E027A0 *o) {
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

/* shape b417:01E03910, 90 insns: b225:01E02540 family: an orange spark (size 20, random frame 0..3, random turn and angle) spinning a random 3..18 a tick, size 0..9, held 5..14 ticks at 0x80, then out by 15 and ends */

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
} Glow_b417_01E03910;

static s32 func_01E03910_b417(s32 arg0, Glow_b417_01E03910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->w18 = 0;
        o->w10 = func_0019A5C8() % 360;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
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
    o->h30 += o->hE;
    o->tick++;
    return 0;
}

/* shape b417:01E03A80, 92 insns: a flickering yellow-orange spark: x turn a quarter, sub-frame 1, growth 1..3, height 8 rising by
   3; full alpha on the first frame, then down by 19 once grown past 10; colour flickers by frame parity */

typedef struct {
    u8 pad0[6];
    s16 y;
    s16 grow;
    u8 padA[6];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 size;
} Obj_b417_01E03A80;

static s32 func_01E03A80_b417(void *arg0, Obj_b417_01E03A80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0;
        o->rot = 0x4000;
        o->sub = 1;
        o->state = 2;
        o->grow = func_0019A5C8() % 3 + 1;
        o->y = 8;
        func_001076F0(o->c0, 0xF0, 0x10, 0x20);
        func_001076F0(o->c1, 0xF0, 0x10, 0x20);
    }
    if (o->t < 1) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x80;
        }
    } else if (o->size > 0xA) {
        if (o->c0[3] > 0x14) {
            o->c0[3] -= 0x13;
        } else {
            o->state = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x10);
    } else {
        func_001076F0(o->c0, 0x88, 0xF0, 8);
    }
    if (o->t != 0) {
        o->size += o->grow;
    }
    o->y += 3;
    o->t++;
    return 0;
}

/* shape b052:01E023C0, 97 insns, 3 copies: step of a drifting ember: on state 1 picks random seeds, angle, speed and
   lifetime and an orange colour; full alpha while young, then fades by 15 until it ends; drifts by its speed. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b052_01E023C0;

static s32 func_01E03BF0_b417(void *arg0, Obj_b052_01E023C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 2;
        o->h34 = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->t++;
    return 0;
}

/* shape b417:01E03D80, 90 insns: a dark-red tumbling glow: x turn a quarter one way or the other by the model's facing, angle 90
   climbing by 0..6 a frame until 270 (then it ends), frame 500; alpha up by 0x50 to 0x50 for 8 frames, then down by 9 */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b417_01E03D80;

static s32 func_01E03D80_b417(void *arg0, Obj_b417_01E03D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 v[4];

    func_001076F0(o->c0, 0x3F, 0x10, 8);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), v);
        if ((s32)((f32)v[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = 0x4000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0;
        o->h34 = 0;
        o->ang = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 0x1F4;
    o->t++;
    if (o->ang < 0x10E) {
        o->ang += (s16)(func_0019A5C8() % 7);
    } else {
        o->state = 0;
    }
    return 0;
}

/* shape b148:01E03AA0, 93 insns, 2 copies: a fast white ember: set up once (frame 3, random turn, speed 60..77, size, life
   2..5); fades in for its life, then out; turns by its speed and grows 2 a frame (b225:01E026A0 family) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    s16 grow;
    u8 padC[2];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 h3A;
} Ember_b148_01E03AA0;

static s32 func_01E03EF0_b417(void *arg0, Ember_b148_01E03AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 100;
        o->frame = 3;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 18 + 60;
        o->h8 = func_0019A5C8() % 20;
        o->grow = 0;
        o->life = func_0019A5C8() % 4 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->grow += 2;
    o->t++;
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

static s32 func_01E04070_b417(Ctx_b046_01E02B80 *c, Obj_b046_01E02B80 *o) {
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

static s32 func_01E042A0_b417(Ctx_b046_01E02DB0 *c, Obj_b046_01E02DB0 *o) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b148_01E04020;

typedef struct {
    f32 f0, f4, f8, fC;
    Vec_b148_01E04020 pos;
    f32 f20, f24, f28;
} Cam_b148_01E04020;

typedef struct {
    u8 pad0000[0x34F0];
    Cam_b148_01E04020 cam;
    u8 pad351C[0x3610 - 0x351C];
    s32 w3610;
} Mgr_b148_01E04020;

typedef struct {
    s16 x, y, z;
    u8 pad06[0x2A];
    s16 h30;
    u8 pad32[4];
    s16 h36;
} Obj_b148_01E04020;

static s32 func_01E04470_b417(Mgr_b148_01E04020 *m, Obj_b148_01E04020 *o) {
    extern void func_001F6C10(void *);

    if (o->h36 == 1) {
        m->cam.f0 = 128.0f;
        m->cam.f4 = 4.0f;
        m->cam.f8 = 2.0f;
        m->cam.fC = 0.0f;
        m->cam.f20 = 0.0f;
        m->cam.f24 = 120.0f;
        m->cam.f28 = 0.0f;
        m->cam.pos.x = o->x;
        m->cam.pos.y = o->y;
        m->cam.pos.z = o->z;
        o->h36 = 2;
        o->h30 = 0;
    }
    if (o->h30 == 0) {
        if (m->cam.f28 < 1.0f) {
            m->cam.f28 += 0.2f;
        } else {
            o->h30 = 1;
        }
    } else {
        if (m->cam.f28 > 0.1f) {
            m->cam.f28 -= 0.1f;
        } else {
            o->h36 = 0;
        }
    }
    if (o->h36 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&m->cam);
    }
    if (m->w3610 == 1) {
        o->h36 = 0;
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

static s32 func_01E045F0_b417(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
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

static s32 func_01E046B0_b417(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05A00_b417;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05A08_b417;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b417:01E04700, 41 insns: look up the textures: group 4 cells 0-2 and 13-15, group 5 cells 0-1 */

typedef struct {
    u8 pad0[0x2B0];
    s32 tex[16];
    u8 pad2F0[0x3300];
    s32 tex5[2];
} Scene_b417_01E04700;

static void func_01E04700_b417(s32 arg0, Scene_b417_01E04700 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b417", func_01E047B0_b417);

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

static s32 func_01E05590_b417(Pool_b046_01E03E20 *o, s32 a, s32 b) {
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

/* shape b148:01E05240, 210 insns: b046:01E03F40 family: a dome band of 12 sectors 30 apart */

typedef struct {
    u8 pad0[0x2EC];
    void *texture;
    u8 pad2F0[0x332C];
    s32 ot;
    u8 pad3620[0xC];
    f32 dep;
    u8 pad3630[0x42C];
    u8 trig[1];
} Ctx_b148_01E05240;

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
} Band_b148_01E05240;

static void func_01E056B0_b417(Ctx_b148_01E05240 *c, Band_b148_01E05240 *o, void *p, s32 mode) {
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
        for (k = 0; k < 12; k++) {
            t = o->ang + a;
            quad[2].x = r1 * func_00108030(c->trig, t, 1);
            quad[2].z = r1 * func_00108030(c->trig, t, 0);
            quad[0].x = r0 * func_00108030(c->trig, t, 1);
            quad[0].z = r0 * func_00108030(c->trig, t, 0);
            t = o->ang + 30 + a;
            quad[3].x = r1 * func_00108030(c->trig, t, 1);
            quad[3].z = r1 * func_00108030(c->trig, t, 0);
            quad[1].x = r0 * func_00108030(c->trig, t, 1);
            quad[1].z = r0 * func_00108030(c->trig, t, 0);
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 0x1E;
        }
    }
    }
}
