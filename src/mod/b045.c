#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b045(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b045(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b045:01E005A0, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E005A0;

static void func_01E005A0_b045(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E005A0 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

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
    func_01E00150_b045((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
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

static void func_01E00780_b045(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b045((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00B00_b045(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00150_b045((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

/* shape b045:01E00E30, 224 insns: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E00E30;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E00E30 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E00E30;

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
} Obj_b045_01E00E30;

static void func_01E00E30_b045(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E00E30 uv;
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
    n = *(s16 *)(self + 0xB8);
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
    func_01E00150_b045((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, 0, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
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

/* shape b045:01E011B0, 277 insns: draws a row of small camera-facing sprites (4 wide, the sprite's h38 high) into
   the given packet, the camera rotation offset by the sprite's own rotation; each is shaken by a per-entry table
   offset growing along the row, the far corners by 0.7 of it. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b045_01E011B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b045_01E011B0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
} Pkt_b045_01E011B0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b045_01E011B0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[6];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 h38;
} Spr_b045_01E011B0;

static void func_01E011B0_b045(Obj_b045_01E011B0 *o, Spr_b045_01E011B0 *s, Pkt_b045_01E011B0 *p, s8 *tbl) {
    f32 hh;
    extern Rgbaq_b045_01E011B0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;
    f32 w;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_01E00150_b045((Pk_b008_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        hh = s->h38;
        func_00108CE0(quad, w = 4.0f, hh);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += 0.7f * (f * (s->w30 + h));
        quad[3].x += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += 0.7f * (f * (s->w30 + h));
        quad[3].y += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += 0.7f * (f * (s->w30 + h));
        quad[3].z += 0.7f * (f * (s->w30 + h));
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
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

static void func_01E01610_b045(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E018A0_b045(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b045:01E01CE0, 222 insns: the scene script of b045 (b115:01E01450's kind): scene colour red 0x80, counts
   g+0x375E; on tick 54 it spawns 16 b045:01E02D00 rings into ring slots 0..15 (g+0x375A); on tick 93 it moves the
   burst point to the camera, sets slot 1 and spawns 0x1E03050, 8 0x1E02330, 8 0x1E026C0, 3 0x1E02880 and one
   0x1E032D0; from tick 46 to 109 it puts the point on the joint g+0x3748 and spawns a 0x1E024F0 */

typedef struct {
    u8 pad0[0x2D0];
    f32 x;
    f32 y;
    f32 z;
    u8 pad2DC[0x3704 - 0x2DC];
    u8 col[4];
    u8 pad3708[0x3748 - 0x3708];
    s16 joint;
    u8 pad374A[0x375A - 0x374A];
    s16 slot;
    u8 pad375C[2];
    s16 tick;
} Ctx_b045_01E01CE0;

static void func_01E01CE0_b045(Ctx_b045_01E01CE0 *g) {
    extern void b045_01E02330();
    extern void b045_01E024F0();
    extern void b045_01E026C0();
    extern void b045_01E02880();
    extern void b045_01E02D00();
    extern void b045_01E03050();
    extern void b045_01E032D0();
    extern void b045_01E04040(Ctx_b045_01E01CE0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 c[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 54) {
        g->slot = 0;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 1;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 2;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 3;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 4;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 5;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 6;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 7;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 8;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 9;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 10;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 11;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 12;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 13;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 14;
        b045_01E04040(g, b045_01E02D00, 0);
        g->slot = 15;
        b045_01E04040(g, b045_01E02D00, 0);
    }
    if (g->tick == 93) {
        func_001F5620(func_001F53A0(), g->joint, v);
        func_001F5F90(func_001F5380(), c);
        g->x = c[0];
        g->y = c[1];
        g->z = c[2];
        g->slot = 1;
        for (i = 0; i < 1; i++) {
            b045_01E04040(g, b045_01E03050, 0);
        }
        for (i = 0; i < 8; i++) {
            b045_01E04040(g, b045_01E02330, 0);
        }
        for (i = 0; i < 8; i++) {
            b045_01E04040(g, b045_01E026C0, 0);
        }
        for (i = 0; i < 3; i++) {
            b045_01E04040(g, b045_01E02880, 0);
        }
        b045_01E04040(g, b045_01E032D0, 0);
    }
    if (g->tick > 45 && g->tick < 110) {
        func_001F5620(func_001F53A0(), g->joint, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b045_01E04040(g, b045_01E024F0, 0);
    }
}

/* shape b045:01E02060, 84 insns: a yellow glow pinned to one of the scene joints (table ctx+0x3748, picked by its +0x30) for 101 ticks at size 50: in by 12 up to 0x80 once the scene state reaches 16, out by 10 after 102 ticks or when the state drops under 15, and ends */

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
} Glow_b045_01E02060;

typedef struct {
    u8 pad[0x3700];
    s32 state;
    u8 pad3704[0x44];
    s16 joint[1];
} Game_b045_01E02060;

static s32 func_01E02060_b045(Game_b045_01E02060 *g, Glow_b045_01E02060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f v;

    func_001F5620(func_001F53A0(), g->joint[o->h30], &v);
    func_001076F0(o->col, 0xA0, 0x80, 8);
    if (o->mode == 1) {
        o->mode = 2;
    }
    if (o->tick < 102) {
        if (g->state > 15) {
            if (o->col[3] < 0x80) {
                o->col[3] += 12;
            }
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (g->state < 15) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 10;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    if (o->tick < 101) {
        o->h0 = func_001A22C0(v.x);
        o->h2 = func_001A22C0(v.y);
        o->h4 = func_001A22C0(v.z);
        o->h6 = 50;
    }
    return 0;
}

/* shape b045:01E021B0, 95 insns: on start 0x38 = 70, variant 2..3, random rotation 0x14, colour (0x30, 0x28, 8), random
   0x3A, speed 8..27 (0xE), 0x8 0..9, hold 3..9 (0x6); alpha grows by 0x30 (up to 0x60) during the hold,
   then fades by 10 and stops; 0x30 grows by the speed after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b045_01E021B0;

static s32 func_01E021B0_b045(s32 arg0, Fx_b045_01E021B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 70;
        o->f34 = func_0019A5C8() % 2 + 2;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x30, 0x28, 8);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 8;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x61) {
            o->col[3] += 0x30;
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

/* shape b045:01E02330, 110 insns, 2 copies: a grey ember: set up once (random size, turn, speed 25..44, life 3..9); fades in
   for its life, then out; its angle advances by its speed, its frame every other frame up to 6 (b003:01E01780 family) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
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
} Ember_b045_01E02330;

static s32 func_01E02330_b045(void *arg0, Ember_b045_01E02330 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        o->frame = 0;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 25;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x60) {
            o->c0[3] += 0x30;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->frame < 6) {
            o->frame++;
        }
    }
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b045:01E024F0, 113 insns: spark that starts with random spin, speed and life, fades in and out and grows
   every other frame */

typedef struct Fl_b045_01E024F0 {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 spin;
    u8 pad10[8];
    s32 f18;
    u8 pad1C[0xC];
    u8 c28[4];
    u8 c2C[4];
    s16 rot;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Fl_b045_01E024F0;

static s32 func_01E024F0_b045(s32 arg0, Fl_b045_01E024F0 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 50 + 30;
        o->h34 = 0;
        o->f18 = func_0019A5C8() % 0x8000 - 0xFA0;
        func_001076F0(o->c28, 0x30, 0x28, 0x30);
        o->rot = 0;
        o->h3A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 25 + 20;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 3;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->c28[3] < 0x61) {
            o->c28[3] += 0x30;
        }
    } else if (o->c28[3] > 0x10) {
        o->c28[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->rot += o->spin;
    }
    o->age++;
    if (o->age % 2 == 1) {
        if (o->h34 < 6) {
            o->h34++;
        }
    }
    return 0;
}

/* shape b045:01E02330, 110 insns, 2 copies: a grey ember: set up once (random size, turn, speed 25..44, life 3..9); fades in
   for its life, then out; its angle advances by its speed, its frame every other frame up to 6 (b003:01E01780 family) */

static s32 func_01E026C0_b045(void *arg0, Ember_b045_01E02330 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        o->frame = 0;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 25;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x60) {
            o->c0[3] += 0x30;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->frame < 6) {
            o->frame++;
        }
    }
    return 0;
}

/* shape b045:01E02880, 94 insns: a purple spark: frame 10, random sub-frame 0..3, angle, start height 0..4 (old one kept), rise
   20..39, width 0..49, hold 5..24; full alpha until the hold, then down by 32 until it ends; rises once started */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 ang;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 y0;
} Obj_b045_01E02880;

static s32 func_01E02880_b045(void *arg0, Obj_b045_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0x30, 0xC0);
        o->ang = func_0019A5C8() % 360;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 5;
        o->step = func_0019A5C8() % 20 + 0x14;
        o->w = func_0019A5C8() % 50;
        o->hold = func_0019A5C8() % 20 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x20) {
        o->c0[3] -= 0x20;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b018:01E027C0, 97 insns: b018:01E02950 with a second seed and a longer fade start. */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    s32 seed2;
    u8 pad14[4];
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
} Spark_b018_01E027C0;

static s32 func_01E02A00_b045(s32 unused, Spark_b018_01E027C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->seed2 = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 20 + 10;
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

/* shape b045:01E02B90, 90 insns: a spark: on start f38 5, random variant, colour (0x80,0x40,0), random depth,
   direction, spin 3..18, f8 0..9, life 1..3; alpha 0x80 during the life, then fades out by 10 and stops; turns
   by the spin every tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
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
} Spark_b045_01E02B90;

static s32 func_01E02B90_b045(s32 arg0, Spark_b045_01E02B90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 5;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->z = func_0019A5C8() % 0xFFFF;
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->f8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->angle += o->spin;
    o->tick++;
    return 0;
}

/* shape b045:01E02D00, 210 insns: b531:01E04460's ring kind: a pink (0x80, 0x10, 0x80) ring of 10 points in ring slot
   0x30 (ctx+0x2A50, stride 0xA0) around joint ctx+0x3748 (the camera once the scene count ctx+0x375E reaches 93), radius
   h8 5..12 and height hA 44..60, turning 18 a tick; alpha up by 27 to 0xC0 for 12 ticks, down by 9 from count 93;
   from count 90 h38 and the radius grow */

typedef struct {
    Vec4f v[10];
} Ring_b045_01E02D00;

typedef struct {
    u8 pad0[0x2A50];
    Ring_b045_01E02D00 ring[8];
    u8 pad2F50[0x3748 - 0x2F50];
    s16 joint;
    u8 pad374A[0x375E - 0x374A];
    s16 count;
    u8 pad3760[0x3A64 - 0x3760];
    u8 trig[4];
} Ctx_b045_01E02D00;

typedef struct {
    u8 pad0[6];
    s16 size;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 ring;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b045_01E02D00;

static s32 func_01E02D00_b045(Ctx_b045_01E02D00 *g, Obj_b045_01E02D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    extern f32 func_00108030(void *, s16, s32);
    f32 c[4];
    s16 i;
    s16 a = 0;

    if (o->state == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0x80);
        o->size = 9;
        o->col[3] = 0;
        o->hA = func_0019A5C8() % 17 + 44;
        o->h8 = func_0019A5C8() % 8 + 5;
        o->ang = func_0019A5C8() % 360;
        o->h38 = 12;
        o->state = 2;
    }
    if (o->t < 12) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x1B;
        }
    } else if (g->count >= 93) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (g->count < 93) {
        func_001F5620(func_001F53A0(), g->joint, c);
    } else {
        func_001F5F90(func_001F5380(), c);
    }
    for (i = 0; i < 10; i++) {
        g->ring[o->ring].v[i].x = o->h8 * func_00108030(g->trig, o->ang + a, 0);
        g->ring[o->ring].v[i].z = o->h8 * func_00108030(g->trig, o->ang + a, 1);
        g->ring[o->ring].v[i].x += c[0];
        g->ring[o->ring].v[i].z += c[2];
        g->ring[o->ring].v[i].y = o->hA;
        a -= 10;
    }
    if (g->count >= 90) {
        o->h38++;
        o->h8 += 4;
    }
    o->ang += 18;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b045:01E03050, 55 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x40
   for the first 2 ticks, then fades out by 10 and stops */

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
} Flash_b045_01E03050;

static s32 func_01E03050_b045(s32 arg0, Flash_b045_01E03050 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x190;
        func_001076F0(o->col, 0xF0, 0x30, 0xF0);
        func_001076F0(o->col2, 0x10, 0x10, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b045:01E03130, 101 insns: a dark drifting mote: frame 50, random turn and angle; full alpha for 10 frames, then down by
   10 until it ends; sub-frame steps up to 7 every third frame; drifts 4 along its angle */

typedef struct {
    u8 pad0[0x3A64];
    u8 sin[1];
} Game_b045_01E03130;

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b045_01E03130;

static s32 func_01E03130_b045(Game_b045_01E03130 *g, Obj_b045_01E03130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0x32;
        o->sub = 0;
        func_001076F0(o->c0, 0x18, 0x18, 0x18);
        o->turn = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 0xA) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 4.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 4.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b045:01E032D0, 92 insns: a screen fog: on start sets the scene fog block (0x2A00: 128, 4, 4, 4, position from
   the effect, colour (0, 120, 0)); its strength 0x2A28 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 */

typedef struct {
    u8 pad0[0x2A00];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad2A2C[0x3700 - 0x2A2C];
    s32 count;
} Game_b045_01E032D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b045_01E032D0;

static s32 func_01E032D0_b045(Game_b045_01E032D0 *g, Fx_b045_01E032D0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 4.0f;
        g->f2A08 = 4.0f;
        g->f2A0C = 4.0f;
        g->f2A20 = 0.0f;
        g->f2A24 = 120.0f;
        g->strength = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->strength < 1.0f) {
            g->strength += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2A00);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b045:01E03440, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3700 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3700];
    s32 state;
} Game_b045_01E03440;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b045_01E03440;

static s32 func_01E03440_b045(Game_b045_01E03440 *g, Fade_b045_01E03440 *o) {
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

/* shape b045:01E03500, 31 insns: func_001F7170(2, 0, &a, &b, 0) with copies of the module's floats at 0x01E04780 and
   0x01E04788; when the game value at 0x3700 is 10 the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b045_01E03500;

typedef struct {
    u8 pad0[0x3700];
    s32 v;
} Game_b045_01E03500;

typedef struct {
    u8 pad0[0x36];
    s16 f36;
} Fx_b045_01E03500;

extern F_b045_01E03500 D_01E04780_b045;
extern F_b045_01E03500 D_01E04788_b045;

static s32 func_01E03500_b045(Game_b045_01E03500 *g, Fx_b045_01E03500 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b045_01E03500 a;
    F_b045_01E03500 b;

    a = D_01E04780_b045;
    b = D_01E04788_b045;
    func_001F7170(2, 0, &a, &b, 0);
    if (g->v == 10) {
        o->f36 = 0;
    }
    return 0;
}

/* shape b045:01E03580, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-1 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x3350];
    s32 tex5[2];
} Scene_b045_01E03580;

static void func_01E03580_b045(s32 arg0, Scene_b045_01E03580 *o) {
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

/* shape b045:01E03630 (b045), 642 insns, 1 copy: b045 scene manager in b233:01E03D60 form: setup (eight joints,
   textures via b045:01E03580, three s8 jitter tables, the second +-5 with 100..179 cleared), run the script, fill
   trail 0 from joint 0 at frame 1, follow trail 9, step the 150 slots (b045:01E03500 written out), draw ten slot
   kinds; returns 1 / 4 / 2 / 6 at frames 82 / 135 / 105 / 94..99, 8 once the 140-frame countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 f6;
    u8 pad8[0x1C];
    s32 (*fn)();
    u8 c0[4];
    u8 pad2C[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    s16 h3A;
    u8 pad3C[4];
} Slot_b045_01E03630;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[8];
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x238];
    s32 z310[3];
    u8 pad31C[0x24];
    s32 tex[16];
    u8 pad380[0xF8];
    Slot_b045_01E03630 slot[150];
    u8 pad29F8[0x58];
    Vec4f tr[10][10];
    u8 pad3090[0x640];
    s32 tex5[2];
    u8 pad36D8[0x28];
    s32 count;
    u8 pad3704[8];
    s32 ot;
    u8 pad3710[0x38];
    s16 j[8];
    u8 pad3758[4];
    s16 id;
    s16 frame;
    u8 pad3760[2];
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 pad3A62[2];
    u8 crd[0x16C];
} Scene_b045_01E03630;

static s32 func_01E03630_b045(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b045_01E01CE0();
    extern void b045_01E00780();
    extern void b045_01E00E30();
    extern void b045_01E04160();
    extern void b045_01E04270();
    extern void b045_01E01610();
    extern void b045_01E005A0();
    Scene_b045_01E03630 *g = (Scene_b045_01E03630 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    s32 rm8[4];
    s32 rm9[4];
    Vec4f pa;
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 b;
    f32 a;
    s32 i;

    m = 0;
    g->ot80 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3BD0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 140;
        g->z310[0] = 0;
        g->z310[1] = 0;
        g->z310[2] = 0;
        g->j[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 5, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 6, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0xE, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->j[6] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->j[7] = func_001F5560(func_001F53A0(), 0x1A, 0);
        func_01E03580_b045(0, (Scene_b045_01E03580 *)g);
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 10 - 5;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = 0;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit3[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b045_01E01CE0(g, 0);
    if (g->frame == 1) {
        Vec4f *p = g->tr[0];

        func_001F5620(func_001F53A0(), g->j[0], (s32)&pa);
        for (i = 0; i < 9; i++, p++) {
            p->x = pa.x;
            p->y = pa.y;
            p->z = pa.z;
        }
    }
    func_01E00080_b045((Vec_b004_01E00B40 *)g->tr[9], 10, g->j[0]);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E02060_b045) {
                func_01E02060_b045((Game_b045_01E02060 *)g, (Glow_b045_01E02060 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E021B0_b045) {
                func_01E021B0_b045((s32)g, (Fx_b045_01E021B0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02330_b045) {
                func_01E02330_b045(g, (Ember_b045_01E02330 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E024F0_b045) {
                func_01E024F0_b045((s32)g, (Fl_b045_01E024F0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E026C0_b045) {
                func_01E026C0_b045(g, (Ember_b045_01E02330 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02880_b045) {
                func_01E02880_b045(g, (Obj_b045_01E02880 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02A00_b045) {
                func_01E02A00_b045((s32)g, (Spark_b018_01E027C0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02B90_b045) {
                func_01E02B90_b045((s32)g, (Spark_b045_01E02B90 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02D00_b045) {
                func_01E02D00_b045((Ctx_b045_01E02D00 *)g, (Obj_b045_01E02D00 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03050_b045) {
                func_01E03050_b045((s32)g, (Flash_b045_01E03050 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03130_b045) {
                func_01E03130_b045((Game_b045_01E03130 *)g, (Obj_b045_01E03130 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E032D0_b045) {
                func_01E032D0_b045((Game_b045_01E032D0 *)g, (Fx_b045_01E032D0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03440_b045) {
                func_01E03440_b045((Game_b045_01E03440 *)g, (Fade_b045_01E03440 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03500_b045) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04780_b045;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04788_b045;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
                if (g->count == 10) {
                    g->slot[i].used = 0;
                }
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E02060_b045) {
                b045_01E04160(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E021B0_b045) {
                g->tex88 = g->tex[2];
                func_00106080(rm, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 10;
                b045_01E00E30(g, &g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E02330_b045) {
                g->tex88 = g->tex5[0];
                func_00106080(rm2, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 10;
                b045_01E00780(g, &g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E024F0_b045) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hB8 = 4;
                b045_01E00780(g, &g->slot[i], buf, g->jit2);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E026C0_b045) {
                g->tex88 = g->tex5[1];
                func_00106080(rm4, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 10;
                b045_01E00780(g, &g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E02880_b045) {
                g->hB8 = 15;
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                func_01E011B0_b045((Obj_b045_01E011B0 *)g, (Spr_b045_01E011B0 *)&g->slot[i], (Pkt_b045_01E011B0 *)buf, g->jit3);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E02A00_b045) {
                g->tex88 = g->tex[1];
                func_00106080(rm6, 0xA, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                func_01E00B00_b045((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02B90_b045) {
                g->tex88 = g->tex[15];
                func_00106080(rm7, 0x9F, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                func_01E00B00_b045((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02D00_b045) {
                g->tex88 = g->tex5[0];
                g->u94.uv[0] = 1;
                g->u94.uv[1] = 0x10;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 1;
                b045_01E04270(g, &g->slot[i], g->tr[g->slot[i].h30]);
            }
            if (g->slot[i].fn == func_01E03050_b045) {
                g->tex88 = g->tex[15];
                func_00106080(rm8, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm8;
                b045_01E01610(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E03130_b045) {
                g->tex88 = g->tex[2];
                func_00106080(rm9, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm9;
                b045_01E005A0(g, &g->slot[i], buf, 0);
                b045_01E005A0(g, &g->slot[i], buf, 1);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x52) {
        return 1;
    }
    if (g->frame == 0x87) {
        return 4;
    }
    if (g->frame == 0x69) {
        return 2;
    }
    if (g->frame > 0x5D && g->frame < 0x64) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b045:01E04040, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x375A and the two arguments; returns 1 if a
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
} Slot_b045_01E04040;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b045_01E04040 s[150];
    u8 pad29F8[0xD0C];
    u8 r, g, b, a;
    u8 pad3708[0x52];
    s16 v;
} Pool_b045_01E04040;

static s32 func_01E04040_b045(Pool_b045_01E04040 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b045_01E04040 *s = NULL;
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

/* shape b045:01E04160, 67 insns: draws a vertical bar sprite: colour from the object, a two-point column from (x, y, z)
   up by h, projected into the given packet and queued at its depth */

typedef struct {
    s16 x, y, z, h;
    u8 pad8[0x20];
    u8 c0[4];
} Bar_b045_01E04160;

typedef struct {
    u8 pad0[0x18];
    u16 h18;
    u8 pad1A[0xE];
    u16 h28;
} Pkt_b045_01E04160;

typedef struct {
    u8 pad0[0x370C];
    s32 ot;
} Game_b045_01E04160;

static void func_01E04160_b045(Game_b045_01E04160 *g, Bar_b045_01E04160 *b, Pkt_b045_01E04160 *p) {
    extern void func_001091B0(void *, void *, void *);
    extern void func_00195108();
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[2];
    f32 depth __attribute__((aligned(16)));

    func_001091B0(p, b->c0, b->c0);
    func_00195108(q, 0x20);
    q[0].y = b->y;
    q[1].y = q[0].y + b->h;
    q[0].x = b->x;
    q[0].z = b->z;
    q[1].x = b->x;
    q[1].z = b->z;
    func_00205630(q, 0x70000000, NULL, p, &depth);
    p->h28 = p->h18;
    func_002075F0(p, g->ot, (u32)depth);
}

/* OVL_WARM */

/* shape b045:01E04270, 316 insns: b018:01E01320's curved beam, textured, drawn as 2 crossed quads per step. Needs func_01E018A0_b045 in the same file and
   static: the original keeps $a0 (the returned Vec buffer) across each call. */

typedef struct {
    u8 r, g, b, a;
} Col_b045_01E04270;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b045_01E04270 col;
    u8 pad2C[0xC];
    s16 width;
} Beam_b045_01E04270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b045_01E04270;

typedef struct {
    Rgbaq_b045_01E04270 c;
    u64 uv;
    u64 xyz;
} Vtx_b045_01E04270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b045_01E04270 v[4];
    u8 tail[0x20];
} Pkt_b045_01E04270;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b045_01E04270;

static void func_01E04270_b045(Obj_b045_01E04270 *o, Beam_b045_01E04270 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_001094F0(void *);
    extern Rgbaq_b045_01E04270 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b045_01E04270 pkt __attribute__((aligned(8)));
    Col_b045_01E04270 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b045_01E04270 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 h;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_001094F0(p);
    func_00109270(p, 0, 0);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    col = an->col;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E018A0_b045(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E018A0_b045(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E018A0_b045(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E018A0_b045(ctrl, 0, t);
                ab[1] = r2;
            }
            p->v[0].c = func_00107740(&col);
            p->v[1].c = func_00107740(&col);
            x = col.a - (s16)(an->col.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            p->v[2].c = func_00107740(&col);
            p->v[3].c = func_00107740(&col);
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
                    q[0].y += w;
                    q[2].y += w;
                    q[1].y -= w;
                    q[3].y -= w;
                } else if (k == 1) {
                    q[0].x += w;
                    q[2].x += w;
                    q[1].x -= w;
                    q[3].x -= w;
                    q[0].z += w / 2.0f;
                    q[2].z += w / 2.0f;
                    q[1].z -= w / 2.0f;
                    q[3].z -= w / 2.0f;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    func_002075F0(p, target, (u32)depth);
                }
            }
        }
    }
}
