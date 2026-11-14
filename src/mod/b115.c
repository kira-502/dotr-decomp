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

static void func_01E00080_b115(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b115(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00080_b115((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00CA0_b115(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00080_b115((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00FD0_b115(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b115 in the
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

static void func_01E01260_b115(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b115((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b115:01E01450, 156 insns: the scene script of b115: it sets the scene colour to red 0x80 and counts g+0x3730;
   until tick 110 it spawns two 0x1E016C0 effects a tick; from 45 to 98 it puts the burst point on joints A and B
   (g+0x3724 / 0x3726) and spawns a 0x1E01980 effect on each; on tick 108 it puts the point on joint C (g+0x371C), reads
   the camera, raises the scene flag g+0x372C and spawns 8 0x1E01F00, 8 0x1E01D70 and 30 0x1E01BC0 effects, then the
   0x1E01AE0 and 0x1E02070 ones */

typedef struct {
    u8 pad0[0x2D0];
    f32 x;
    f32 y;
    f32 z;
    u8 pad2DC[0x3418];
    u8 col[4];
    u8 pad36F8[0x24];
    s16 jc;
    u8 pad371E[6];
    s16 ja;
    s16 jb;
    u8 pad3728[4];
    s16 flag;
    u8 pad372E[2];
    s16 tick;
} Ctx_b115_01E01450;

static void func_01E01450_b115(Ctx_b115_01E01450 *g) {
    extern void b115_01E016C0();
    extern void b115_01E01980();
    extern void b115_01E01AE0();
    extern void b115_01E01BC0();
    extern void b115_01E01D70();
    extern void b115_01E01F00();
    extern void b115_01E02070();
    extern void b115_01E028F0(Ctx_b115_01E01450 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 cam[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick < 110) {
        b115_01E028F0(g, b115_01E016C0, 0);
        b115_01E028F0(g, b115_01E016C0, 0);
    }
    if (g->tick >= 45 && g->tick < 99) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b115_01E028F0(g, b115_01E01980, 0);
        func_001F5620(func_001F53A0(), g->jb, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b115_01E028F0(g, b115_01E01980, 0);
    }
    if (g->tick == 108) {
        func_001F5620(func_001F53A0(), g->jc, v);
        func_001F5F90(func_001F5380(), cam);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b115_01E028F0(g, b115_01E01F00, 0);
        }
    }
    if (g->tick == 108) {
        func_001F5620(func_001F53A0(), g->jc, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b115_01E028F0(g, b115_01E01D70, 0);
        }
        for (i = 0; i < 30; i++) {
            b115_01E028F0(g, b115_01E01BC0, 0);
        }
        b115_01E028F0(g, b115_01E01AE0, 0);
        b115_01E028F0(g, b115_01E02070, 0);
    }
}

/* shape b115:01E016C0, 173 insns: b393:01E023B0's red mote between joints 0x371C/0x371E; after its hold it fades by
   10 before scene frame 108 and by 8 after (ends below 0x11 / 0xA), and rises twice as fast from frame 106 */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 rise;
    u8 pad10[8];
    s32 spin;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 k;
} Fx_b115_01E016C0;

typedef struct {
    u8 pad0[0x371C];
    s16 ja;
    s16 jb;
    u8 pad3720[0x10];
    s16 frame;
} Scene_b115_01E016C0;

static s32 func_01E016C0_b115(Scene_b115_01E016C0 *g, Fx_b115_01E016C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    if (o->mode == 1) {
        o->size = 6;
        o->k = func_0019A5C8() % 4;
        o->frame = 2;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->spin = func_0019A5C8() % 65535;
        o->h = 0;
        o->rise = 7 - (o->k >> 1);
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        o->col[3] = 0x80;
    } else if (g->frame < 108) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 10;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (g->frame < 106) {
        o->h += o->rise;
    } else {
        o->h += o->rise * 2;
    }
    o->t++;
    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    dx = v[1].x - v[0].x;
    dy = v[1].y - v[0].y;
    dz = v[1].z - v[0].z;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    o->x = func_001A22C0(v[0].x + dx * o->k);
    o->y = func_001A22C0(v[0].y + dy * o->k);
    o->z = func_001A22C0(v[0].z + dz * o->k);
    return 0;
}

/* shape b115:01E01980, 87 insns: a white spark (size 60, frame 5) at two random angles drifting 16 a tick along its angle (sine table ctx+0x3834): alpha 0x80 for 7 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[2];
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
} Glow_b115_01E01980;

typedef struct {
    u8 pad[0x3834];
    u8 sin[1];
} Game_b115_01E01980;

static s32 func_01E01980_b115(Game_b115_01E01980 *g, Glow_b115_01E01980 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = 5;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 16.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 16.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b018:01E02480, 54 insns, 11 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
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
} Obj_b018_01E02480;

static s32 func_01E01AE0_b115(void *arg0, Obj_b018_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x14A;
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

/* shape b115:01E01BC0, 108 insns: variant of b018:01E02610 (col (128, 16, 16)): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
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
} Spark_b115_01E01BC0;

static s32 func_01E01BC0_b115(s32 arg0, Spark_b115_01E01BC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xA;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
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

/* shape b115:01E01D70, 97 insns: a red spark: set up once (random frame, spin, speed 3..18, life 5..14); full alpha for its life, then fades by 15; turns by its speed */

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
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b115_01E01D70;

static s32 func_01E01D70_b115(void *arg0, Obj_b115_01E01D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 2;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->w18 = func_0019A5C8() % 65535;
        o->w10 = func_0019A5C8() % 65535;
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->state = 0;
    }
    o->ang += o->hE;
    o->t++;
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

static s32 func_01E01F00_b115(s32 unused, Spark_b018_01E02950 *o) {
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

/* shape b115:01E02070, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x36F0 is 1 */

typedef struct {
    u8 pad0[0x3650];
    f32 l0[4];
    f32 pos[3];
    u8 pad366C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad367C[0x74];
    s32 state;
} Scene_b115_01E02070;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b115_01E02070;

static s32 func_01E02070_b115(Scene_b115_01E02070 *g, Obj_b115_01E02070 *o) {
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

/* shape b115:01E021F0, 40 insns: look up the textures: group 4 cells 0-2 and 13-15 into the table at 0x310, group 5
   cell 0 into 0x36D0 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x310];
    s32 tex[16];
    u8 pad350[0x36D0 - 0x350];
    s32 tex5[1];
} Scene_b115_01E021F0;

static void func_01E021F0_b115(s32 arg0, Scene_b115_01E021F0 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 1; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b115:01E02290 (b115), 408 insns, 1 copy: b115 scene manager (b397:01E02450 form): code >= 0 sets up the scene
   (joints, textures, 256 jitters -15..14), else run the script, step the 200 slots, draw them (the 016C0 motes on
   four joint points) and return the frame events */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x1E];
    s32 (*fn)();
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b115_01E02290;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x34];
    u8 crdD8[0x238];
    s32 tex[16];
    u8 pad350[0xF8];
    Slot_b115_01E02290 slot[200];
    u8 pad3648[0x38];
    Vec4f pts[4];
    u8 pad36C0[0x10];
    s32 tex5;
    u8 pad36D4[0x1C];
    s32 count;
    u8 pad36F4[8];
    s32 ot;
    u8 pad3700[0x1C];
    s16 j[6];
    u8 pad3728[2];
    s16 jG;
    u8 pad372C[2];
    s16 id;
    s16 frame;
    u8 pad3732[2];
    s8 jit[0x100];
    u8 crd[0x16C];
} Scene_b115_01E02290;

static s32 func_01E02290_b115(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b115_01E02A10();
    extern void func_01E00920_b115();
    extern void func_01E00CA0_b115();
    extern void func_01E00FD0_b115();
    extern void func_01E01260_b115();
    extern void func_01E01450_b115();
    extern void func_01E021F0_b115();
    extern s32 func_01E016C0_b115();
    extern s32 func_01E01980_b115();
    extern s32 func_01E01AE0_b115();
    extern s32 func_01E01BC0_b115();
    extern s32 func_01E01D70_b115();
    extern s32 func_01E01F00_b115();
    extern s32 func_01E02070_b115();
    Scene_b115_01E02290 *g = (Scene_b115_01E02290 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    u8 buf[0x90];
    s32 i;
    s32 k;

    m = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x39A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0xAA;
        g->j[0] = func_001F5560(func_001F53A0(), 0x14, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x1D, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x26, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x65, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x5B, 0);
        g->jG = func_001F5560(func_001F5380(), 1, 1);
        func_01E021F0_b115(0, g);
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01450_b115(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E016C0_b115) {
                func_01E016C0_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01980_b115) {
                func_01E01980_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01AE0_b115) {
                func_01E01AE0_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01BC0_b115) {
                func_01E01BC0_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01D70_b115) {
                func_01E01D70_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01F00_b115) {
                func_01E01F00_b115(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02070_b115) {
                func_01E02070_b115(g, &g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E016C0_b115) {
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                for (k = 0; k < 4; k++) {
                    if (g->frame < 0x6C) {
                        func_001F5620(func_001F53A0(), g->j[k], &g->pts[k]);
                    }
                    b115_01E02A10(g, &g->slot[i], &g->pts[k], g->jit);
                }
            }
            if (g->slot[i].fn == func_01E01980_b115) {
                g->tex88 = g->tex5;
                func_00106080(rm2, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                c.x = g->slot[i].x;
                c.y = g->slot[i].y;
                c.z = g->slot[i].z;
                func_01E01260_b115(g, &g->slot[i], 0, c);
            }
            if (g->slot[i].fn == func_01E01AE0_b115) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E00FD0_b115(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E01BC0_b115) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                func_01E00920_b115(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E01D70_b115) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0xA, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                func_01E00CA0_b115(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E01F00_b115) {
                g->tex88 = g->tex[15];
                func_00106080(rm6, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                func_01E00CA0_b115(g, &g->slot[i], buf, g->jit);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x62) {
        return 1;
    }
    if (g->frame == 0x87) {
        return 4;
    }
    if (g->frame == 0x78) {
        return 2;
    }
    if (g->frame > 0x6C && g->frame < 0x73) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b115:01E028F0, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x372C and the two arguments; returns 1 if a
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
} Slot_b115_01E028F0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x178];
    Slot_b115_01E028F0 s[200];
    u8 pad3648[0xAC];
    u8 r, g, b, a;
    u8 pad36F8[0x34];
    s16 v;
} Pool_b115_01E028F0;

static s32 func_01E028F0_b115(Pool_b115_01E028F0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b115_01E028F0 *s = NULL;
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

/* shape b115:01E02A10 (B115PAINT_RAIN8), 267 insns, 1 copy: b052:01E03730 cousin with its own packet: draws a row of
   13 thin bars at the given point (third argument) shaken by the per-entry table offsets, the far edge pinned at
   +-2.5 (+-5.5 once the scene clock 0x3730 reaches 107); before clock 47 they are drawn far, then at their depth;
   texture corners by the module helper (shape b003:01E00080) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b115_01E02A10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b115_01E02A10 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x30];
} Pkt_b115_01E02A10;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x10];
    u8 padA4[0x36FC - 0xA4];
    s32 ot;
    u8 pad3700[0x3730 - 0x3700];
    s16 clock;
} Obj_b115_01E02A10;

typedef struct {
    u8 pad0[8];
    s16 off;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b115_01E02A10;
static void func_01E00080_b115();

static void func_01E02A10_b115(Obj_b115_01E02A10 *o, Spr_b115_01E02A10 *s, Vec4f *at, s8 *tbl) {
    extern Rgbaq_b115_01E02A10 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f c;
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    struct {
        u64 tag;
        Pkt_b115_01E02A10 pk;
    } buf;
    s16 i;
    Pkt_b115_01E02A10 *p;
    s32 h;
    s8 *j;
    f32 f;

    c = *at;
    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.c.q = 0;
    buf.pk.v[0].f = 0;
    buf.pk.v[1].f = 0;
    buf.pk.v[2].f = 0;
    buf.pk.v[3].f = 0;
    buf.pk.c = func_00107740(s->col);
    func_01E00080_b115(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    pos.x = c.x;
    pos.y = c.y;
    pos.z = c.z;
    func_00108EF0(m, &scale, rot, &pos);
    for (i = 0; i < 13; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 50];
        f /= 20.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        if (o->clock < 107) {
            f = 2.5f;
        } else {
            f = 5.5f;
        }
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[0].x = f;
        quad[1].x = -f;
        quad[0].z = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            if (o->clock < 47) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            } else {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
}
