#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b734(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

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

static void func_01E00100_b734(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E00550_b734(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

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
    func_01E00100_b734((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
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
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

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

static void func_01E008D0_b734(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00100_b734((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b734 in the
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

static void func_01E00C00_b734(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00100_b734((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00EC0_b734(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E01220_b734(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b734_01E00100();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b734_01E00100(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b734:01E01770, 347 insns: B734_W_S, the effect scene's step (b522:01E01D30 form): colour 0x80,0,0,0, counts
   the frame (0x6E0C); frame 148 spawns 0x1E01CE0; frame 158, for joints 0x6DEE / 0x6DF0 / 0x6DF2, puts the point
   halfway in depth toward the camera and spawns bursts of 0x1E02090 / 0x1E01EE0 (plus 0x1E02220 x50, 0x1E02BB0 x4,
   0x1E024B0 on the first, 0x1E02CA0 on the last); frames 105/159 two rounds of thirteen 0x1E025F0 1.5 under joint
   0x6DEC; frames 0..5 0x1E030C0, 47..87 five 0x1E027B0, 0..24 and 132..160 0x1E02970 on it; the sway (0x6D70) is
   100 x the sine of the angle 0x6E02, which turns 5 a frame */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x6D70 - 0x2E0];
    f32 sway;
    u8 pad6D74[0x6DA4 - 0x6D74];
    u8 col[4];
    u8 pad6DA8[0x6DEC - 0x6DA8];
    s16 j0;
    s16 j1;
    s16 j2;
    s16 j3;
    u8 pad6DF4[0x6E02 - 0x6DF4];
    s16 ang;
    u8 pad6E04[2];
    s16 side;
    u8 pad6E08[4];
    s16 t;
    u8 pad6E0E[0x7010 - 0x6E0E];
    u8 trig[1];
} Scene_b734_01E01770;

static void func_01E01770_b734(Scene_b734_01E01770 *g) {
    extern void b734_01E01CE0(void);
    extern void b734_01E01EE0(void);
    extern void b734_01E02090(void);
    extern void b734_01E02220(void);
    extern void b734_01E024B0(void);
    extern void b734_01E025F0(void);
    extern void b734_01E027B0(void);
    extern void b734_01E02970(void);
    extern void b734_01E02BB0(void);
    extern void b734_01E02CA0(void);
    extern void b734_01E030C0(void);
    extern void b734_01E03C60(Scene_b734_01E01770 *, void (*)(void), s32);
    extern void b734_01E03D80(Scene_b734_01E01770 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f a;
    Vec4f b;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 148) {
        g->side = 0;
        b734_01E03C60(g, b734_01E01CE0, 0);
    }
    if (g->t == 158) {
        func_001F5620(func_001F53A0(), g->j1, &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z + (b.z - a.z) / 2.0f;
        g->side = 1;
        for (i = 0; i < 8; i++) {
            b734_01E03C60(g, b734_01E02090, 0);
        }
        for (i = 0; i < 20; i++) {
            b734_01E03C60(g, b734_01E01EE0, 0);
        }
        for (i = 0; i < 50; i++) {
            b734_01E03D80(g, b734_01E02220, 0);
        }
        b734_01E03D80(g, b734_01E02BB0, 0);
        b734_01E03D80(g, b734_01E02BB0, 0);
        b734_01E03D80(g, b734_01E02BB0, 0);
        b734_01E03D80(g, b734_01E02BB0, 0);
        b734_01E03D80(g, b734_01E024B0, 0);
        func_001F5620(func_001F53A0(), g->j2, &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z + (b.z - a.z) / 2.0f;
        g->side = 1;
        for (i = 0; i < 8; i++) {
            b734_01E03C60(g, b734_01E02090, 0);
        }
        for (i = 0; i < 20; i++) {
            b734_01E03C60(g, b734_01E01EE0, 0);
        }
        func_001F5620(func_001F53A0(), g->j3, &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = a.x;
        g->pos.y = a.y;
        g->pos.z = a.z + (b.z - a.z) / 2.0f;
        g->side = 1;
        for (i = 0; i < 8; i++) {
            b734_01E03C60(g, b734_01E02090, 0);
        }
        b734_01E03C60(g, b734_01E02CA0, 0);
    }
    if (g->t == 105 || g->t == 159) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b734_01E03D80(g, b734_01E025F0, 0);
        }
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b734_01E03D80(g, b734_01E025F0, 0);
        }
    }
    if (g->t < 6) {
        b734_01E03D80(g, b734_01E030C0, 0);
    }
    if (g->t >= 47 && g->t < 88) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 5; i++) {
            b734_01E03D80(g, b734_01E027B0, 0);
        }
    }
    if (g->t < 25) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        b734_01E03D80(g, b734_01E02970, 0);
    }
    if (g->t >= 132 && g->t < 161) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        b734_01E03D80(g, b734_01E02970, 0);
    }
    g->sway = 100.0f * func_00108030((s32)g->trig, g->ang, 0);
    g->ang += 5;
    if (g->ang >= 360) {
        g->ang %= 360;
    }
}

/* shape b734:01E01CE0, 127 insns: b397:01E01540 with joints at g+0x6DEC/0x6DEE, hold 30, h6 10, and the trail and the
   full alpha kept while the scene timer at g+0x6E0C is below 160 */

typedef struct {
    f32 x, y, z, w;
} Pt_b734_01E01CE0;

typedef struct {
    u8 pad0[0x6AF0];
    Pt_b734_01E01CE0 a[10];
    Pt_b734_01E01CE0 b[10];
    u8 pad6C30[0x1BC];
    s16 ja;
    s16 jb;
    u8 pad6DF0[0x1C];
    s16 timer;
} Scene_b734_01E01CE0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hold;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 h38;
} Fx_b734_01E01CE0;

static s32 func_01E01CE0_b734(Scene_b734_01E01CE0 *g, Fx_b734_01E01CE0 *o) {
    extern void b734_01E00080(Pt_b734_01E01CE0 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s32 i;
    s32 j;
    Pt_b734_01E01CE0 *q;

    func_001076F0(o->col, 0x80, 0x20, 0xFF);
    if (o->mode == 1) {
        o->h38 = 5;
        if (o->kind == 0) {
            o->hold = 30;
            func_001F5620(func_001F53A0(), g->ja, p);
            q = g->a;
            for (i = 0; i < 9; i++) {
                q[i].x = p[0];
                q[i].y = p[1];
                q[i].z = p[2];
            }
            func_001F5620(func_001F53A0(), g->jb, p);
            q = g->b;
            for (j = 0; j < 9; j++) {
                q[j].x = p[0];
                q[j].y = p[1];
                q[j].z = p[2];
            }
        }
        if (o->kind == 1) {
            o->hold = 7;
        }
        o->mode = 2;
    }
    if (g->timer < 0xA0) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 0x1D;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0 && g->timer < 0xA0) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b734_01E00080(&g->a[9], 10, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b734_01E00080(&g->b[9], 10, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

/* shape b734:01E01EE0, 108 insns: variant of b018:01E02610 (col (40, 16, 8)): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
   delay and lifetime and colour (0x20,0x10,8); fade in by 0x38 while younger than its lifetime, then fade out by
   10 and stop; spin while running */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b734_01E01EE0;

static s32 func_01E01EE0_b734(s32 arg0, Spark_b734_01E01EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xA;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x28, 0x10, 0x8);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->delay = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->angle += o->spin;
    }
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b353_01E016A0;

static s32 func_01E02090_b734(s32 unused, Obj_b353_01E016A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 6;
        o->h34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->h30 = 0;
        o->h3A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 20 + 10;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    o->h30 += o->hE;
    o->h32++;
    return 0;
}

/* shape b353:01E01830, 164 insns: variant of b479:01E020E0 (tumbling spark) with a random size 4..11 that does
   not grow and colour (0x80,0x40,0xFF) */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x18];
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b353_01E01830;

static s32 func_01E02220_b734(s32 arg0, Spark_b353_01E01830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 8 + 4;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b734:01E024B0, 77 insns: constant variant of b205:01E01B90 (colour (255, 64, 64), colour (255, 64, 128)) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
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
} Fx_b734_01E024B0;

typedef struct {
    u8 pad[0x6E0C];
    s16 v;
} Game_b734_01E024B0;

static s32 func_01E024B0_b734(Game_b734_01E024B0 *g, Fx_b734_01E024B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 180.0f;
        func_001076F0(o->col2, 0xFF, 0x40, 0x40);
        func_001076F0(o->col, 0xFF, 0x40, 0x80);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 8) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        o->size += 0.4f;
    }
    if (g->v == 0xC3) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b567:01E02310, 112 insns, 3 copies: step of a white spark thrown out at a random angle: on state 1 jumps 8.6
   along the angle, then drifts 0.8 per tick; fades in by 0x40 for 10 ticks, then out by 9 until it ends. */

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x24];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b567_01E02310;

typedef struct {
    u8 pad[0x7010];
    u8 tbl[1];
} Ctx_b567_01E02310;

static s32 func_01E025F0_b734(Ctx_b567_01E02310 *c, Obj_b567_01E02310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h8 = 130;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 8.6f * func_00108030(c->tbl, o->ang, 0);
        o->x += 8.6f * func_00108030(c->tbl, o->ang, 1);
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.8f * func_00108030(c->tbl, o->ang, 0);
        o->x += 0.8f * func_00108030(c->tbl, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b589:01E02400, 112 insns: a white spark kicked 8.6 along a random angle (sine table at ctx+0x7010), then drifting 0.6 a frame; fades in to 0x80, out by 9 */


typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[4];
    Vec4f rot;
    u8 pad30[0x24];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Obj_b589_01E02400;

static s32 func_01E027B0_b734(s32 arg0, Obj_b589_01E02400 *o) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = 0x82;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 8.6f * func_00108030((void *)(arg0 + 0x7010), o->ang, 0);
        o->x += 8.6f * func_00108030((void *)(arg0 + 0x7010), o->ang, 1);
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.6f * func_00108030((void *)(arg0 + 0x7010), o->ang, 0);
        o->x += 0.6f * func_00108030((void *)(arg0 + 0x7010), o->ang, 1);
    }
    func_00205C40((s32)&o->rot);
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x6DEC];
    s16 h6DEC;
} Mgr_b567_01E02690;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 v10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_b567_01E02690;

static s32 func_01E02970_b734(Mgr_b567_01E02690 *m, Obj_b567_01E02690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = (func_0019A5C8() >> 4) % 100 + 50;
        o->h52 = func_0019A5C8() % 450 + 300;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 5) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 % 2 == 1) {
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c60, 0xC0, 0xC0, 0xC0);
    }
    func_001F5620(func_001F53A0(), m->h6DEC, o->v10);
    o->h54++;
    return 0;
}

/* shape b734:01E02BB0, 57 insns: a white spinning flash: set up once (size 100x100, random angle), fades in by 0x40 for 7
   frames up to 0x80, then out by 11 until it ends; turns at random each frame */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b734_01E02BB0;

static s32 func_01E02BB0_b734(void *arg0, Obj_b734_01E02BB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x64;
        o->h = o->w;
        o->h56 = 0;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b205_01E01CD0;

typedef struct {
    f32 f0, f4, f8, fC;
    Vec_b205_01E01CD0 pos;
    f32 f20, f24, f28;
} Cam_b205_01E01CD0;

typedef struct {
    u8 pad0000[0x6AA0];
    Cam_b205_01E01CD0 cam;
    u8 pad351C[0x6DA0 - 0x6ACC];
    s32 w3610;
} Mgr_b205_01E01CD0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0x2A];
    s16 h30;
    u8 pad32[4];
    s16 h36;
} Obj_b205_01E01CD0;

static s32 func_01E02CA0_b734(Mgr_b205_01E01CD0 *m, Obj_b205_01E01CD0 *o) {
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

/* shape b205:01E01E50, 47 insns: volume fade by game state: starts at 0x80; while the state is 0x1F or more fade
   down by 10 (floor 0x30), else back up by 10 (cap 0x80); the volume is set the same way whether the state is 1
   or not */

typedef struct {
    u8 pad[0x6DA0];
    s32 state;
} Game_b205_01E01E50;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b205_01E01E50;

static s32 func_01E02E20_b734(Game_b205_01E01E50 *g, Fade_b205_01E01E50 *o) {
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

static s32 func_01E02EE0_b734(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04480_b734;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04488_b734;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b205_01E01F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b205_01E01F90;

typedef struct {
    f32 s, t;
    Xyz_b205_01E01F90 p;
} Vtx_b205_01E01F90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b205_01E01F90 c;
    Vtx_b205_01E01F90 v[2];
    u64 tail;
} Pkt_b205_01E01F90;

typedef struct {
    u8 pad0000[0x6D70];
    f32 f6D70;
} Mgr_b205_01E01F90;

static inline void tag_b205_01E01F90(Pkt_b205_01E01F90 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E02F30_b734(Mgr_b205_01E01F90 *m) {
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b205_01E01F90 pkt __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    s32 s;
    s16 h;

    s = func_00207F60();
    h = m->f6D70;
    tag_b205_01E01F90((Pkt_b205_01E01F90 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0x80;
    pkt.c.a = 0x80;
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = (h + 0x6C0) * 16 - 8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = (h + 0x940) * 16 - 8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_00208460();
    func_00208800(func_00209E50(), 0, &a, b);
    func_00208460();
    func_002075F0(&pkt, 0, 0);
    func_00207FD0(s, func_00207500(), 0);
    return 0;
}

/* shape b205:01E02120, 146 insns: a full-screen textured overlay (0x6BF8,0x71F8 - 0x93F8,0x8DF8) in the effect's
   colour, written straight into the scene's packet (game 0x6DB8), window scrolled by f8/10 and fA/10; alpha grows
   by 9 (below 0x80) while the game value 0x6E0C is below 0xB4, then after tick 0x28 fades by 9 and stops */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b205_01E02120;

typedef struct {
    f32 s, t;
    Xyz_b205_01E02120 p;
} Tv_b205_01E02120;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b205_01E02120 v[2];
} Tex_b205_01E02120;

typedef struct {
    u8 pad[0x6DB8];
    Tex_b205_01E02120 *pk;
    u8 pad6DBC[0x50];
    s16 v;
} Game_b205_01E02120;

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
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
} Fx_b205_01E02120;

static s32 func_01E030C0_b734(Game_b205_01E02120 *g, Fx_b205_01E02120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x30);
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = fx / 1024.0f;
    g->pk->v[0].t = fy / 512.0f;
    g->pk->v[1].s = (640.0f - fx) / 1024.0f;
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (g->v < 0xB4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->tick > 0x28) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b734:01E03310, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 14-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x6A00];
    s32 tex5[3];
} Scene_b734_01E03310;

static void func_01E03310_b734(s32 arg0, Scene_b734_01E03310 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b734", func_01E033C0_b734);

/* shape b205:01E02AB0, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x6E06 and the two arguments; returns 1 if a
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
} Slot_b205_01E02AB0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0xB0];
    Slot_b205_01E02AB0 s[150];
    u8 pad2900[0x44A4];
    u8 r, g, b, a;
    u8 pad6DA8[0x5E];
    s16 v;
} Pool_b205_01E02AB0;

static s32 func_01E03C60_b734(Pool_b205_01E02AB0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b205_01E02AB0 *s = NULL;
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

/* shape b205:01E02BD0, 80 insns, 3 copies: starts a particle: takes the first free one of 150 slots, clears it, gives it
   the emitter's colour (twice), position and timer and the two caller values; returns 0 when all are busy
   (150-slot variant of shape b539:01E03530). */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 t0;
    s16 t1;
    u8 pad54[4];
    s16 used;
    s16 t2;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b205_01E02BD0;

typedef struct {
    u8 pad0000[0x2D0];
    Vec4f pos;
    u8 pad02E0[0x2620];
    Slot_b205_01E02BD0 slots[150];
    u8 pad6AA0[0x304];
    u8 col[4];
    u8 pad6DA8[0x5E];
    s16 t0;
} Emit_b205_01E02BD0;

static s32 func_01E03D80_b734(Emit_b205_01E02BD0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b205_01E02BD0 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 150; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 150;
        }
    }
    if (e != NULL) {
        func_001076F0(e->c0, o->col[0], o->col[1], o->col[2]);
        e->c0[3] = o->col[3];
        func_001076F0(e->c1, o->col[0], o->col[1], o->col[2]);
        e->c1[3] = o->col[3];
        func_00106AB0(e, &o->pos, 0);
        e->x = o->pos.x;
        e->y = o->pos.y;
        e->z = o->pos.z;
        e->t0 = o->t0;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}

/* shape b734:01E03EC0 (B734KPOINT_RAIN_2), 289 insns, 1 copy: rain streaks: per segment, a ring of 18 angles x 4
   offset quads drawn between consecutive points, lifted by 0.6 of the height */

typedef struct {
    u8 r, g, b, a;
} Col_b734_01E03EC0;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xCC];
    u8 trig[4];
} Own_b734_01E03EC0;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b734_01E03EC0 col;
} Fx_b734_01E03EC0;

typedef struct {
    u32 tag[2];
    u8 pk[0x94];
} Buf_b734_01E03EC0;

static void func_01E03EC0_b734(Own_b734_01E03EC0 *g, Fx_b734_01E03EC0 *o, Vec4f *pts, Vec4f *base) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630();
    extern void func_00109380();
    extern void func_002075F0();
    extern s32 func_00207500(void);
    f32 depth[4];
    Vec4f q[4];
    Vec4f v[2];
    Buf_b734_01E03EC0 buf;
    Col_b734_01E03EC0 col;
    s16 n;
    s32 j;
    u8 *p;
    s32 ot;
    s32 i;
    s32 k;
    s32 last;
    s32 cnt;
    s16 a;
    s32 ang;
    f32 t;
    f32 r;
    f32 z;
    f32 w;
    f32 y;
    f32 h;

    ot = func_00207500();
    n = o->n;
    t = 0.0f;
    p = buf.pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    cnt = n;
    col = o->col;
    v[0] = *pts;
    v[1] = *base;
    v[0].x -= v[1].x;
    v[0].y -= v[1].y;
    v[0].z -= v[1].z;
    v[0].x = g->x;
    v[0].y = -v[0].y;
    v[0].z = g->z;
    i = 0;
    h = v[0].z;
    y = v[0].y;
    w = 0.6f * h;
    last = cnt - 1;
    goto test;
loop:
    {
        a = 0;
        func_00107990(p, &col, 1);
        col.a -= o->col.a / cnt;
        func_00107990(p, &col, 2);
        for (k = 0, ang = -90; k < 18; k++, ang += 10) {
            r = v[0].x * func_00108030(g->trig, ang, 0);
            z = h * func_00108030(g->trig, ang, 1) - w;
            for (j = 0; j < 4; j++) {
                q[0].x = pts->x;
                q[0].y = pts->y;
                q[0].z = pts->z;
                q[1].x = pts->x;
                q[1].y = pts->y;
                q[1].z = pts->z;
                q[2].x = pts[1].x;
                q[2].y = pts[1].y;
                q[2].z = pts[1].z;
                q[3].x = pts[1].x;
                q[3].y = pts[1].y;
                q[3].z = pts[1].z;
                func_00107070(q, 0, r);
                func_00107070(q, 2, z);
                func_00107070(q, 1, y);
                if (j == 0) {
                    q[0].z += 0.2f;
                    q[2].z += 0.2f;
                } else if (j == 1) {
                    q[0].z -= 0.2f;
                    q[2].z -= 0.2f;
                } else if (j == 2) {
                    q[0].x += 0.2f;
                    q[2].x += 0.2f;
                } else if (j == 3) {
                    q[0].x -= 0.2f;
                    q[2].x -= 0.2f;
                }
                if (func_00205630(q, 0x70000000, 0, p, depth)) {
                    func_00109380(p, 1);
                    func_002075F0(p, ot, 0);
                }
                a += 30;
            }
        }
        pts++;
        t += 1.0f;
        i++;
    }
test:
    if (i < last) goto loop;
}

/* shape b734:01E04350, 73 insns: the module's draw pass (b016:01E03880 shape): opens a sprite packet on the stack, then
   runs every live slot (150 of 0x70 bytes) whose handler is shape b734:01E030C0 through it; queues the batch only if any
   slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b734_01E04350;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b734_01E04350 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b734_01E04350;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b734_01E04350;

typedef struct {
    u8 pad0[0x2900];
    Slot_b734_01E04350 slot[150];
    u8 padEnd[0x6DB4 - 0x2900 - 150 * 0x70];
    s32 ctx;
    Pkt_b734_01E04350 *pkt;
} Scene_b734_01E04350;

static void func_01E04350_b734(Scene_b734_01E04350 *s) {
    extern void b734_01E030C0(Scene_b734_01E04350 *, Slot_b734_01E04350 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b734_01E04350 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b734_01E030C0) {
                b734_01E030C0(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
