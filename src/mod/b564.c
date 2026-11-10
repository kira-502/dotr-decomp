#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b564(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00100_b564(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E00550_b564(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00100_b564((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E008D0_b564(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00100_b564((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b564 in the
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

static void func_01E00C00_b564(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00100_b564((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00EC0_b564(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b564:01E01220, 161 insns: b567:01E01770 family event step: red scene colour, counts ticks; at 68 spawns b564:01E014B0 (slot 0); at 72 moves its point to the tracked point, halfway to the camera in z, and spawns 8 b564:01E018A0, 20 b564:01E016F0, 50 b564:01E01A30, b564:01E01CC0 and b564:01E02230; spawns b564:01E02420 for the first 5 ticks; from 47 to 83 drops 5 b564:01E01FD0 at the other tracked point */

typedef struct {
    u8 pad0[0x2D0];
    f32 pos[3];
    u8 pad2DC[0x9964 - 0x2DC];
    u8 col[4];
    u8 pad9968[0x99AC - 0x9968];
    s16 id2;
    u8 pad99AE[2];
    s16 id0;
    u8 pad99B2[0x99C6 - 0x99B2];
    s16 slot;
    u8 pad99C8[4];
    s16 timer;
} Ctx_b564_01E01220;

static void func_01E01220_b564(Ctx_b564_01E01220 *g) {
    extern s32 b564_01E014B0(void);
    extern s32 b564_01E016F0(void);
    extern s32 b564_01E018A0(void);
    extern s32 b564_01E01A30(void);
    extern s32 b564_01E01CC0(void);
    extern s32 b564_01E01FD0(void);
    extern s32 b564_01E02230(void);
    extern s32 b564_01E02420(void);
    extern void b564_01E02F50(Ctx_b564_01E01220 *, s32 (*)(void), s32);
    extern void b564_01E030C0(Ctx_b564_01E01220 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 a[4];
    f32 b[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 68) {
        g->slot = 0;
        b564_01E02F50(g, b564_01E014B0, 0);
    }
    if (g->timer == 72) {
        func_001F5620(func_001F53A0(), g->id0, a);
        func_001F5F90(func_001F5380(), b);
        g->pos[0] = a[0];
        g->pos[1] = a[1];
        g->pos[2] = a[2] + (b[2] - a[2]) / 2.0f;
        g->slot = 1;
        for (i = 0; i < 8; i++) {
            b564_01E02F50(g, b564_01E018A0, 0);
        }
        for (i = 0; i < 20; i++) {
            b564_01E02F50(g, b564_01E016F0, 0);
        }
        for (i = 0; i < 50; i++) {
            b564_01E030C0(g, b564_01E01A30, 0);
        }
        b564_01E030C0(g, b564_01E01CC0, 0);
        b564_01E02F50(g, b564_01E02230, 0);
    }
    if (g->timer < 6) {
        b564_01E030C0(g, b564_01E02420, 0);
    }
    if (g->timer >= 47 && g->timer < 84) {
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        g->pos[1] -= 1.5f;
        for (i = 0; i < 5; i++) {
            b564_01E030C0(g, b564_01E01FD0, 0);
        }
    }
}

/* shape b564:01E014B0, 143 insns: b567:01E019F0's trail with a blue colour (0x20/0x20/0x80), trails at g+0x96B0, joints
   at g+0x99B0 / 0x99AE, full alpha while the counter at g+0x99CC is under 75, hold 5 */

typedef struct {
    Vec4f pt[9];
    Vec4f head;
} Trail_b564_01E014B0;

typedef struct {
    u8 pad0[0x96B0];
    Trail_b564_01E014B0 a;
    Trail_b564_01E014B0 b;
    u8 padT[0x1BE];
    s16 id1;
    s16 id2;
    u8 padJ[0x1A];
    s16 count;
} Ctx_b564_01E014B0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[6];
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b564_01E014B0;

static s32 func_01E014B0_b564(Ctx_b564_01E014B0 *g, Fx_b564_01E014B0 *o) {
    extern void b564_01E00080(void *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];
    s32 i;
    s32 j;
    Vec4f *p;

    func_001076F0(o->col, 0x20, 0x20, 0x80);
    if (o->mode == 1) {
        o->f38 = 5;
        if (o->kind == 0) {
            o->fE = 30;
            func_001F5620(func_001F53A0(), g->id2, v);
            p = g->a.pt;
            for (i = 0; i < 9; i++) {
                p[i].x = v[0];
                p[i].y = v[1];
                p[i].z = v[2];
            }
            func_001F5620(func_001F53A0(), g->id1, v);
            p = g->b.pt;
            for (j = 0; j < 9; j++) {
                p[j].x = v[0];
                p[j].y = v[1];
                p[j].z = v[2];
            }
        }
        if (o->kind == 1) {
            o->fE = 7;
        }
        o->mode = 2;
    }
    if (g->count < 75) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (g->count < 75) {
            func_001F5620(func_001F53A0(), g->id2, v);
            b564_01E00080(&g->a.head, 10, 0, v);
            func_001F5620(func_001F53A0(), g->id1, v);
            b564_01E00080(&g->b.head, 10, 0, v);
        }
    }
    o->hold = 5;
    o->tick++;
    return 0;
}

/* shape b564:01E016F0, 108 insns: variant of b018:01E02610 (col (32, 32, 96), life 4, fade 15): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
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
} Spark_b564_01E016F0;

static s32 func_01E016F0_b564(s32 arg0, Spark_b564_01E016F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xA;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x20, 0x20, 0x60);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->delay = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 4;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->angle += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b564:01E018A0, 97 insns: b417:01E03910 family: a blue spark (size 6, random frame 0..3, two random turns) spinning a random 3..18 a tick, size 0..9, held 4..11 ticks at 0x80, then out by 15 and ends */

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
} Glow_b564_01E018A0;

static s32 func_01E018A0_b564(s32 arg0, Glow_b564_01E018A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x60, 0x60, 0xFF);
        o->w18 = func_0019A5C8() % 65535;
        o->w10 = func_0019A5C8() % 65535;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 8 + 4;
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

/* shape b564:01E01A30, 164 insns: variant of b479:01E020E0 (tumbling spark) with a random size 4..11 that does
   not grow and colour (0x40,0x40,0xFF) ; alpha grows for 10 ticks, fades by 15 */

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
} Spark_b564_01E01A30;

static s32 func_01E01A30_b564(s32 arg0, Spark_b564_01E01A30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 8 + 4;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x40, 0x40, 0xFF);
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
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
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

/* shape b564:01E01CC0, 79 insns: a blue-white spinning flash (b479:01E02380 shape): f4C 120 growing by 0.4; second alpha up by 0x60 to 0xC0 for
   8 frames, then down by 15; ends when the game timer hits 0xC3 */

typedef struct {
    u8 pad0[0x99CC];
    s16 timer;
} Game_b564_01E01CC0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b564_01E01CC0;

static s32 func_01E01CC0_b564(Game_b564_01E01CC0 *g, Obj_b564_01E01CC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 120.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0x40, 0x40, 0xFF);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 8) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0x10) {
        o->c1[3] -= 0xF;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t != 0) {
        o->f4C += 0.4f;
    }
    if (g->timer == 0xC3) {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b564:01E01E00, 115 insns: a white drifting spark (b567:01E024D0 shape): size 130, sub-frame 2..4,
   random angle; pushed 8.6 along it at the start, then drifting 0.8 a frame; alpha up, then down; turns */

typedef struct {
    u8 pad0[0x9BD0];
    u8 sin[1];
} Game_b564_01E01E00;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b564_01E01E00;

static s32 func_01E01E00_b564(Game_b564_01E01E00 *g, Obj_b564_01E01E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x82;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 8.6f * func_00108030(g->sin, o->ang, 0);
        o->x += 8.6f * func_00108030(g->sin, o->ang, 1);
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 0x9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.8f * func_00108030(g->sin, o->ang, 0);
        o->x += 0.8f * func_00108030(g->sin, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b564:01E01FD0, 152 insns: b564:01E01E00's drifting spark, pale blue before scene frame 60 (0x99CC) else blue, fading by 9 before frame 74 and by 19 after, drifting 0.6; frame 74 skips it 6 ticks ahead */

typedef struct {
    u8 pad0[0x99CC];
    s16 frame;
    u8 pad99CE[0x202];
    u8 sin[1];
} Game_b564_01E01FD0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b564_01E01FD0;

static s32 func_01E01FD0_b564(Game_b564_01E01FD0 *g, Obj_b564_01E01FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x82;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        if (g->frame < 60) {
            func_001076F0(o->c0, 0xC0, 0xC0, 0xFF);
        } else {
            func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        }
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 8.6f * func_00108030(g->sin, o->ang, 0);
        o->x += 8.6f * func_00108030(g->sin, o->ang, 1);
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (g->frame < 0x4A) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 0x9;
        } else {
            o->state = 0;
        }
    } else if (o->c0[3] > 0x14) {
        o->c0[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.6f * func_00108030(g->sin, o->ang, 0);
        o->x += 0.6f * func_00108030(g->sin, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    if (g->frame == 0x4A) {
        o->t += 6;
    }
    o->t++;
    return 0;
}

/* shape b564:01E02230, 122 insns (b504:01E015B0 with the light at 0x9660, done flag 0x300 in, mode 0x36, phase 0x30):
   a scene light: on start colour/size 128/4/2/0, height 0/120/0 and the object's position as floats; its strength
   rises by 0.2 up to 1 (then the phase flips) and falls by 0.1 until it ends; func_001F6C10 gets the light (or 0
   once ended); it also ends when the light's done flag is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x2D4];
    s32 done;
} Light_b564_01E02230;

typedef struct {
    u8 pad0[0x9660];
    Light_b564_01E02230 light;
} Game_b564_01E02230;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x2A];
    s16 f50;
    u8 pad32[4];
    s16 mode;
} Fx_b564_01E02230;

static s32 func_01E02230_b564(Game_b564_01E02230 *g, Fx_b564_01E02230 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a[0] = 128.0f;
        g->light.a[1] = 4.0f;
        g->light.a[2] = 2.0f;
        g->light.a[3] = 0.0f;
        g->light.b[0] = 0.0f;
        g->light.b[1] = 120.0f;
        g->light.b[2] = 0.0f;
        g->light.pos[0] = o->x;
        g->light.pos[1] = o->y;
        g->light.pos[2] = o->z;
        o->mode = 2;
        o->f50 = 0;
    }
    if (o->f50 == 0) {
        if (g->light.b[2] < 1.0f) {
            g->light.b[2] += 0.2f;
        } else {
            o->f50 = 1;
        }
    } else if (g->light.b[2] > 0.1f) {
        g->light.b[2] -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->light.done == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b564:01E02420, 184 insns: b482:01E031F0's window in blue-grey (0x38/0x38/0x40) at ctx+0x9978; alpha rises by
   9 until scene frame 80 (0x99CC), then after tick 40 drops by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b564_01E02420;

typedef struct {
    f32 s, t;
    Xyz_b564_01E02420 p;
} Tv_b564_01E02420;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b564_01E02420 v[2];
} Tex_b564_01E02420;

typedef struct {
    u8 pad[0x9978];
    Tex_b564_01E02420 *pk;
    u8 pad997C[0x50];
    s16 frame;
} Game_b564_01E02420;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b564_01E02420;

static s32 func_01E02420_b564(Game_b564_01E02420 *g, Fx_b564_01E02420 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x40);
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
    if (g->frame < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->tick > 40) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b564:01E02700, b734:01E03310 family: textures group 4 cells 0-2 and 11-15, group 5 cells 0-1 (table past 0x8000) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 padT[0x95c0];
    s32 tex5[2];
} Scene_b564_01E02700;

static void func_01E02700_b564(s32 arg0, Scene_b564_01E02700 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 11; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b564:01E027B0 (b564), 485 insns, 1 copy: b564 scene manager in b589:01E02AC0 form: setup (six joints,
   textures, camera turn, two s8 jitter tables), step the four OBJ_MOVE slot kinds, draw the KPOINT_RAIN_2 trail,
   PAINT_Fragment_2 and PAINT_Fragment_3, step the 250 effects by their handlers counting the b564:01E02420 ones (then
   B564_Anchor_PAINT), draw IWMagicSmoke3 three ways and IWMagicCircleG4_8; scene code from the timer */

typedef struct {
    u8 pad0[0xA];
    s16 h0A;
    u8 padC[0x18];
    s32 (*fn)();
    u8 pad28[8];
    s16 h30;
    s16 pad32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b564_01E027B0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b564_01E027B0;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    u8 padC[0x74];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x238];
    s32 w310;
    s32 w314;
    s32 w318;
    u8 pad31C[0x60];
    s32 tex37C;
    Slot_b564_01E027B0 slot[150];
    Fx_b564_01E027B0 fx[250];
    u8 pad9660[0x50];
    Vec4f pts[2][10];
    u8 pad97F0[0x150];
    s32 tex2[2];
    u8 pad9948[0x18];
    s32 count;
    u8 pad9964[8];
    s32 ot;
    u8 pad9970[0x3C];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad99B8[0x10];
    s16 id;
    s16 turn;
    s16 frame;
    u8 pad99CE[2];
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b564_01E027B0;

static s32 func_01E027B0_b564(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01220_b564();
    extern void func_01E02700_b564();
    extern void func_01E00550_b564();
    extern void func_01E008D0_b564();
    extern void func_01E00C00_b564();
    extern void func_01E00EC0_b564();
    extern s32 func_01E014B0_b564();
    extern s32 func_01E016F0_b564();
    extern s32 func_01E018A0_b564();
    extern s32 func_01E01A30_b564();
    extern s32 func_01E01CC0_b564();
    extern s32 func_01E01E00_b564();
    extern s32 func_01E01FD0_b564();
    extern s32 func_01E02230_b564();
    extern s32 func_01E02420_b564();
    extern void b564_01E03250();
    extern void b564_01E036D0();
    Scene_b564_01E027B0 *g = (Scene_b564_01E027B0 *)arg0;
    s16 j;
    s32 n;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    u8 buf[0x90];
    s32 i;

    j = 0;
    n = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x9D40);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 99;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1E, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x1F, 0);
        g->jD = func_001F5560(func_001F53A0(), 4, 0);
        g->jE = func_001F5560(func_001F53A0(), 5, 0);
        g->jF = func_001F5560(func_001F53A0(), 6, 0);
        func_01E02700_b564(0, g);
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    func_01E01220_b564(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E014B0_b564) {
                func_01E014B0_b564(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E016F0_b564) {
                func_01E016F0_b564(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E018A0_b564) {
                func_01E018A0_b564(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02230_b564) {
                func_01E02230_b564(g, &g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E014B0_b564) {
                if (g->slot[i].h30 == 0) {
                    g->f4 = 0.0f;
                }
                if (g->slot[i].h30 == 1) {
                    g->f4 = 1.0f;
                }
                g->f0 = 3.5f;
                if (g->turn != 0) {
                    g->f8 = -6.0f;
                } else {
                    g->f8 = 6.0f;
                }
                if (g->slot[i].h30 == 0) {
                    b564_01E03250(g, &g->slot[i], g->pts[1], g->pts);
                }
            }
            if (g->slot[i].fn == func_01E016F0_b564) {
                g->tex88 = g->tex37C;
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                func_01E00550_b564(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E018A0_b564) {
                g->tex88 = g->tex37C;
                func_00106080(rm2, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                func_01E008D0_b564(g, &g->slot[i], buf, g->jit);
            }
        }
    }
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != func_01E02420_b564) {
                    g->fx[i].fn(g, &g->fx[i]);
                } else {
                    j++;
                }
            }
        }
    }
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01A30_b564) {
                n++;
                g->tex88 = g->tex37C;
                func_00106080(rm3, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E00C00_b564(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == func_01E01CC0_b564) {
                g->hB8 = 0x24;
                func_01E00EC0_b564(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01E00_b564) {
                g->tex88 = g->tex2[0];
                func_00106080(rm4, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                func_01E00C00_b564(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == func_01E01FD0_b564) {
                n++;
                g->tex88 = g->tex2[0];
                func_00106080(rm5, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                func_01E00C00_b564(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
        }
    }
    if (j) {
        b564_01E036D0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x3E) {
        return 1;
    }
    if (g->frame == 0x5F) {
        return 4;
    }
    if (g->frame == 0x48) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b564:01E02F50, 90 insns: takes the first free of 150 effect slots (0x40 bytes, b089:01E030B0 shape), colours it
   from the context, places it at the context's position and stores the frame and both arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 c28[4];
    u8 c2C[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b564_01E02F50;

typedef struct {
    u8 pad0[0x2D0];
    f32 pos[3];
    u8 pad2DC[0xA4];
    Slot_b564_01E02F50 slots[0x96];
    u8 pad[0x9964 - 0x380 - 0x96 * 0x40];
    u8 rgba[4];
    u8 pad9968[0x5E];
    s16 f99C6;
} Ctx_b564_01E02F50;

static s32 func_01E02F50_b564(Ctx_b564_01E02F50 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b564_01E02F50 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x40);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c28, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c28[3] = ctx->rgba[3];
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f30 = ctx->f99C6;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b564:01E030C0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0xfa of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b564_01E030C0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b564_01E030C0;

typedef struct Obj_b564_01E030C0 {
    u8 pad0[0x2d0];
    f32 pos[3];
    u8 padA[0x2900 - 0x2d0 - 12];
    Slot_b564_01E030C0 slots[0xfa];
    u8 padB[0x9964 - 0x2900 - 0xfa * 0x70];
    u8 rgba[4];
    u8 padC[0x99c6 - 0x9964 - 4];
    s16 fB2B0;
} Obj_b564_01E030C0;

static s32 func_01E030C0_b564(Obj_b564_01E030C0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b564_01E030C0 *s = NULL;
    s16 i;

    for (i = 0; i < 0xfa; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xfa;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b564:01E03250 (B564KPOINT_RAIN_2), 287 insns, 1 copy: rain streaks: per segment, a ring of 18 angles x 4
   offset quads drawn between consecutive points, lifted by 0.6 of the height, queued at their depth */

typedef struct {
    u8 r, g, b, a;
} Col_b564_01E03250;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xCC];
    u8 trig[4];
} Own_b564_01E03250;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b564_01E03250 col;
} Fx_b564_01E03250;

typedef struct {
    u32 tag[2];
    u8 pk[0x94];
} Buf_b564_01E03250;

static void func_01E03250_b564(Own_b564_01E03250 *g, Fx_b564_01E03250 *o, Vec4f *pts, Vec4f *base) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630();
    extern void func_002075F0();
    extern s32 func_00207500(void);
    f32 depth[4];
    Vec4f q[4];
    Vec4f v[2];
    Buf_b564_01E03250 buf;
    Col_b564_01E03250 col;
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
                    func_002075F0(p, ot, (u32)depth[0]);
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


/* shape b564:01E036D0, 89 insns: the module's draw pass (b016:01E03880 shape): opens a sprite packet on the stack, then
   runs every live slot (150 of 0x70 bytes) whose handler is shape b564:01E02420 through it; queues the batch only if any
   slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b564_01E036D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b564_01E036D0 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b564_01E036D0;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b564_01E036D0;

typedef struct {
    u8 pad0[0x2900];
    Slot_b564_01E036D0 slot[150];
    u8 padEnd[0x9974 - 0x2900 - 150 * 0x70];
    s32 ctx;
    Pkt_b564_01E036D0 *pkt;
} Scene_b564_01E036D0;

static void func_01E036D0_b564(Scene_b564_01E036D0 *s) {
    extern void b564_01E02420(Scene_b564_01E036D0 *, Slot_b564_01E036D0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b564_01E036D0 pkt __attribute__((aligned(8)));
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
            if (s->slot[i].fn == (void *)b564_01E02420) {
                b564_01E02420(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b564", func_01E03880_b564);
