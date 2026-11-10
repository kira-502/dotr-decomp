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

static void func_01E00080_b513(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b513(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00080_b513((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00CA0_b513(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00080_b513((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00FD0_b513(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b513 in the
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

static void func_01E01260_b513(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b513((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b513:01E01450, 267 insns (B513_W_S): the module's spawn step: scene colour red, ticks the timer; at 51 reads
   joint 0x36CA into 0x3520 and from 52 to 64 copies it to the spawn point; spawns two b513:01E01880 before 179 and
   two b513:01E021D0 before 204; on six ticks sixteen b513:01E01A10 at joint 0x36D2, on five more sixteen at joint
   0x36D0; at 178 (joint 0x36CC) and 203 (joint 0x36CE) eight b513:01E02050, then eight b513:01E01EB0, thirty
   b513:01E01D00, one b513:01E01B70 and one b513:01E02360 */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x3520 - 0x25C];
    f32 qx, qy, qz;
    u8 pad352C[0x36A4 - 0x352C];
    u8 rgba[4];
    u8 pad36A8[0x36CA - 0x36A8];
    s16 j0;
    s16 j1;
    s16 j2;
    s16 j3;
    s16 j4;
    u8 pad36D4[0x36E2 - 0x36D4];
    s16 flag;
    u8 pad36E4[2];
    s16 t;
} Scene_b513_01E01450;

static s32 func_01E01880_b513();
static s32 func_01E01A10_b513();
static s32 func_01E01B70_b513();
static s32 func_01E01D00_b513();
static s32 func_01E01EB0_b513();
static s32 func_01E02050_b513();
static s32 func_01E021D0_b513();
static s32 func_01E02360_b513();
static s32 func_01E02E60_b513();

static void func_01E01450_b513(Scene_b513_01E01450 *s) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;

    s->rgba[0] = 0x80;
    s->rgba[1] = 0;
    s->rgba[2] = 0;
    s->rgba[3] = 0;
    s->t++;
    if (s->t == 51) {
        func_001F5620(func_001F53A0(), s->j0, &s->qx);
    }
    if (s->t > 51 && s->t < 65) {
        func_001F5620(func_001F53A0(), s->j0, v);
        for (i = 0; i < 6; i++) {
            s->px = s->qx;
            s->py = s->qy;
            s->pz = s->qz;
        }
    }
    if (s->t < 179) {
        func_01E02E60_b513(s, func_01E01880_b513, 0);
        func_01E02E60_b513(s, func_01E01880_b513, 0);
    }
    if (s->t < 204) {
        func_01E02E60_b513(s, func_01E021D0_b513, 0);
        func_01E02E60_b513(s, func_01E021D0_b513, 0);
    }
    if (s->t == 18 || s->t == 44 || s->t == 75 || s->t == 101 || s->t == 131 || s->t == 152) {
        func_001F5620(func_001F53A0(), s->j4, v);
        s->px = v[0];
        s->py = v[1];
        s->pz = v[2];
        for (i = 0; i < 16; i++) {
            func_01E02E60_b513(s, func_01E01A10_b513, 0);
        }
    }
    if (s->t == 31 || s->t == 58 || s->t == 87 || s->t == 114 || s->t == 143) {
        func_001F5620(func_001F53A0(), s->j3, v);
        s->px = v[0];
        s->py = v[1];
        s->pz = v[2];
        for (i = 0; i < 16; i++) {
            func_01E02E60_b513(s, func_01E01A10_b513, 0);
        }
    }
    if (s->t == 178 || s->t == 203) {
        if (s->t == 178) {
            func_001F5620(func_001F53A0(), s->j1, v);
        }
        if (s->t == 203) {
            func_001F5620(func_001F53A0(), s->j2, v);
        }
        s->px = v[0];
        s->py = v[1];
        s->pz = v[2];
        s->flag = 1;
        for (i = 0; i < 8; i++) {
            func_01E02E60_b513(s, func_01E02050_b513, 0);
        }
    }
    if (s->t == 178 || s->t == 203) {
        if (s->t == 178) {
            func_001F5620(func_001F53A0(), s->j1, v);
        }
        if (s->t == 203) {
            func_001F5620(func_001F53A0(), s->j2, v);
        }
        s->px = v[0];
        s->py = v[1];
        s->pz = v[2];
        s->flag = 1;
        for (i = 0; i < 8; i++) {
            func_01E02E60_b513(s, func_01E01EB0_b513, 0);
        }
        for (i = 0; i < 30; i++) {
            func_01E02E60_b513(s, func_01E01D00_b513, 0);
        }
        func_01E02E60_b513(s, func_01E01B70_b513, 0);
        func_01E02E60_b513(s, func_01E02360_b513, 0);
    }
}

/* shape b513:01E01880, 99 insns: a red spark on a model joint (first): frame 10, random sub-frame 0..3 with rise 17 less half of it,
   y turn, width 0..9, hold 1..3; full alpha until the hold, then down by 10 until it ends; takes the joint position each frame */

typedef struct {
    u8 pad0[0x36C8];
    s16 joint;
} Game_b513_01E01880;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 sub;
} Obj_b513_01E01880;

static s32 func_01E01880_b513(Game_b513_01E01880 *g, Obj_b513_01E01880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = func_0019A5C8() % 4;
        o->h34 = 2;
        func_001076F0(o->c0, 0x80, 0x20, 0x20);
        o->rot2 = func_0019A5C8() % 65535;
        o->h = 0;
        o->step = 0x11 - (o->sub >> 1);
        o->w = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->h += o->step;
    o->t++;
    func_001F5620(func_001F53A0(), g->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    return 0;
}

/* shape b513:01E01A10, 87 insns: b115:01E01980 family drifting white spark (sine table ctx+0x37E8) */

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
} Glow_b513_01E01A10;

typedef struct {
    u8 pad[0x37E8];
    u8 sin[1];
} Game_b513_01E01A10;

static s32 func_01E01A10_b513(Game_b513_01E01A10 *g, Glow_b513_01E01A10 *o) {
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

/* shape b513:01E01B70, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0xC0
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
} Flash_b513_01E01B70;

static s32 func_01E01B70_b513(s32 arg0, Flash_b513_01E01B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14A;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x20, 0x10, 0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 5) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b018:01E02560, 42 insns, 6 copies: an orange flash: colour, then fade after 75 frames (variant of b018:01E02480) */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b018_01E02560;

static s32 func_01E01C50_b513(void *arg0, Obj_b018_01E02560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x80, 0x50, 0);
    if (o->state == 1) {
        o->h38 = 5;
        o->state = 2;
    }
    if (o->t < 0x4B) {
        o->c0[3] = 0x50;
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f6 = 10;
    o->t++;
    return 0;
}

/* shape b513:01E01D00, 108 insns: variant of b018:01E02610 (f38 20, col (128, 16, 16), spin (26, 13)): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
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
} Spark_b513_01E01D00;

static s32 func_01E01D00_b513(s32 arg0, Spark_b513_01E01D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 26 + 13;
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

/* shape b513:01E01EB0, 103 insns: b564:01E018A0 family: a red spark (size 12, random frame 0..3, two random turns) spinning a random 8..23 a tick from 0..15, size 0..9, held 5..14 ticks at 0x80, then out by 15 and ends */

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
} Glow_b513_01E01EB0;

static s32 func_01E01EB0_b513(s32 arg0, Glow_b513_01E01EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 12;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->w18 = func_0019A5C8() % 65535;
        o->w10 = func_0019A5C8() % 65535;
        o->h30 = func_0019A5C8() % 16;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 8;
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

/* shape b513:01E02050, 96 insns: b417:01E03910 family: an orange spark (size 12, random frame 0..3, random roll and angle) spinning a random 8..23 a tick from 0..15, size 0..9, held 1..3 ticks at 0x80, then out by 10 and ends */

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
} Glow_b513_01E02050;

static s32 func_01E02050_b513(s32 arg0, Glow_b513_01E02050 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 12;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->w18 = func_0019A5C8() % 65535;
        o->h30 = func_0019A5C8() % 16;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 8;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->h30 += o->hE;
    o->tick++;
    return 0;
}

/* shape b513:01E021D0, 99 insns: a red spark on a model joint (second): frame 10, random sub-frame 0..3 with rise 17 less half of it,
   y turn, width 0..9, hold 1..3; full alpha until the hold, then down by 10 until it ends; takes the joint position each frame */

typedef struct {
    u8 pad0[0x36CA];
    s16 joint;
} Game_b513_01E021D0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 sub;
} Obj_b513_01E021D0;

static s32 func_01E021D0_b513(Game_b513_01E021D0 *g, Obj_b513_01E021D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = func_0019A5C8() % 4;
        o->h34 = 2;
        func_001076F0(o->c0, 0x80, 0x20, 0x20);
        o->rot2 = func_0019A5C8() % 65535;
        o->h = 0;
        o->step = 0x11 - (o->sub >> 1);
        o->w = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->h += o->step;
    o->t++;
    func_001F5620(func_001F53A0(), g->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    return 0;
}

/* shape b513:01E02360, 93 insns: a screen fog: on start sets the scene fog block (0x34E0: 128, 4.0, 2.0, 0.0, position from
   the effect, colour (0, 120.0, 0)); its strength 0x3508 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 (0x36A0) */

typedef struct {
    u8 pad0[0x34E0];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad350C[0x36A0 - 0x350C];
    s32 count;
} Game_b513_01E02360;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[0x4];
    s16 mode;
} Fx_b513_01E02360;

static s32 func_01E02360_b513(Game_b513_01E02360 *g, Fx_b513_01E02360 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 4.0f;
        g->f2A08 = 2.0f;
        g->f2A0C = 0.0f;
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

/* shape b513:01E024E0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x36A0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x36A0];
    s32 state;
} Game_b513_01E024E0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b513_01E024E0;

static s32 func_01E024E0_b513(Game_b513_01E024E0 *g, Fade_b513_01E024E0 *o) {
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

static s32 func_01E025A0_b513(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03380_b513;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03388_b513;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b513:01E025F0, 40 insns: look up the textures: group 4 cells 0-2 and 4 cells 13-15 into the table at 0x2A0,
   group 5 cell 0 into 0x3680 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2A0];
    s32 tex[16];
    u8 pad2E0[0x3680 - 0x2E0];
    s32 tex5[1];
} Scene_b513_01E025F0;

static void func_01E025F0_b513(s32 arg0, Scene_b513_01E025F0 *o) {
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

/* shape b513:01E02690 (b513), 500 insns, 1 copy: b513 scene manager (b115:01E02290 form): with a scene id (>= 0) it
   clears the scene, keeps the id, sets the 268-frame countdown, takes six joint handles and the root joint, looks up
   the textures and fills a 256-byte random table (-15..14); otherwise it runs the script, steps the 200 slots
   (B513_OBJ_MOVE_6_ and B513_OBJ_MOVE_201_ written out in place), draws every live slot with its texture and frame,
   counts down and returns 1 / 4 / 2 at frames 168 / 250 / 220, 6 in 179..214, 8 once the countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 f6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[0x16];
    s32 (*fn)();
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    u8 pad3A[6];
} Slot_b513_01E02690;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x34];
    u8 crdD8[0x1C8];
    s32 tex[16];
    Slot_b513_01E02690 slot[200];
    u8 pad34E0[0x1A0];
    s32 tex5;
    u8 pad3684[0x1C];
    s32 count;
    u8 pad36A4[8];
    s32 ot;
    u8 pad36B0[0x18];
    s16 j[6];
    u8 pad36D4[2];
    s16 jG;
    u8 pad36D8[0xC];
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 crd[0x178];
} Scene_b513_01E02690;

static s32 func_01E02690_b513(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_01E01450_b513();
    extern void func_01E00FD0_b513();
    extern void b513_01E02F80();
    Scene_b513_01E02690 *g = (Scene_b513_01E02690 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;
    f32 dx;
    f32 dz;

    m = 0;
    g->ot80 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3960);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x10C;
        g->j[0] = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x62, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x20, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x68, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0xA5, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0xB0, 0);
        g->jG = func_001F5560(func_001F5380(), 1, 1);
        func_01E025F0_b513(0, (Scene_b513_01E025F0 *)g);
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01450_b513(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E01880_b513) {
                func_01E01880_b513((Game_b513_01E01880 *)g, (Obj_b513_01E01880 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01A10_b513) {
                func_01E01A10_b513((Game_b513_01E01A10 *)g, (Glow_b513_01E01A10 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01B70_b513) {
                func_01E01B70_b513((s32)g, (Flash_b513_01E01B70 *)&g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01C50_b513) {
                func_001076F0(g->slot[i].c0, 0x80, 0x50, 0);
                if (g->slot[i].used == 1) {
                    g->slot[i].h38 = 5;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x4B) {
                    g->slot[i].c0[3] = 0x50;
                } else if (g->slot[i].c0[3] > 10) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].f6 = 10;
                g->slot[i].t++;
            }
            if (g->slot[i].fn == func_01E01D00_b513) {
                func_01E01D00_b513((s32)g, (Spark_b513_01E01D00 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01EB0_b513) {
                func_01E01EB0_b513((s32)g, (Glow_b513_01E01EB0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02050_b513) {
                func_01E02050_b513((s32)g, (Glow_b513_01E02050 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E021D0_b513) {
                func_01E021D0_b513((Game_b513_01E021D0 *)g, (Obj_b513_01E021D0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02360_b513) {
                func_01E02360_b513((Game_b513_01E02360 *)g, (Fx_b513_01E02360 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E024E0_b513) {
                func_01E024E0_b513((Game_b513_01E024E0 *)g, (Fade_b513_01E024E0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E025A0_b513) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E03380_b513;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E03388_b513;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E01880_b513) {
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                b513_01E02F80(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E01A10_b513) {
                g->tex88 = g->tex5;
                func_00106080(rm2, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                c.x = g->slot[i].x;
                c.y = g->slot[i].y;
                c.z = g->slot[i].z;
                dx = g->slot[i].h8;
                dz = g->slot[i].hC;
                dx /= 10.0f;
                dz /= 10.0f;
                c.x += dx;
                c.z += dz;
                func_01E01260_b513((Obj_b046_01E00DD0 *)g, (Data_b046_01E00DD0 *)&g->slot[i], 0, c);
            }
            if (g->slot[i].fn == func_01E01B70_b513) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E00FD0_b513(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E01D00_b513) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                func_01E00920_b513((u8 *)g, (Obj_b018_01E005A0 *)&g->slot[i], (Pk_b018_01E005A0 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E01EB0_b513) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0xA, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                func_01E00CA0_b513((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02050_b513) {
                g->tex88 = g->tex[15];
                func_00106080(rm6, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                func_01E00CA0_b513((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E021D0_b513) {
                g->tex88 = g->tex[15];
                func_00106080(rm7, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm7;
                b513_01E02F80(g, &g->slot[i], buf, g->jit);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xA8) {
        return 1;
    }
    if (g->frame == 0xFA) {
        return 4;
    }
    if (g->frame == 0xDC) {
        return 2;
    }
    if (g->frame > 0xB2 && g->frame < 0xD7) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b513:01E02E60, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x36E2 and the two arguments; returns 1 if a
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
} Slot_b513_01E02E60;

typedef struct {
    u8 pad[0x250];
    u8 m[0x90];
    Slot_b513_01E02E60 s[200];
    u8 pad34E0[0x1C4];
    u8 r, g, b, a;
    u8 pad36A8[0x3A];
    s16 v;
} Pool_b513_01E02E60;

static s32 func_01E02E60_b513(Pool_b513_01E02E60 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b513_01E02E60 *s = NULL;
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

/* OVL_WARM */

/* shape b052:01E03730, 245 insns, 3 copies: draws a row of 20 thin bars at the sprite's position into the caller's
   packet (b225:01E04BF0 family): each shaken by a per-entry table offset, far edge pinned at +-1, drawn far;
   texture corners by the module helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b052_01E03730;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b052_01E03730 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
} Pkt_b052_01E03730;

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
} Obj_b052_01E03730;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[2];
    s16 w;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b052_01E03730;

static void func_01E02F80_b513(Obj_b052_01E03730 *o, Spr_b052_01E03730 *s, Pkt_b052_01E03730 *p, s8 *tbl) {
    extern Rgbaq_b052_01E03730 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    s32 h;
    s8 *j;
    f32 f;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_01E00080_b513((Pk_b008_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
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
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[0].x = 1.0f;
        quad[1].x = -1.0f;
        quad[0].z = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}
