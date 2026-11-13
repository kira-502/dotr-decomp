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

static void func_01E00080_b477(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b477(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b477 in the
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

static void func_01E00BB0_b477(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b477((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00DA0_b477(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
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
    func_01E00080_b477((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01210_b477(Obj_b476_01E017C0 *o, Ring_b476_01E017C0 *s, s32 side) {
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

/* shape b477:01E01600, 172 insns: the effect scene's step: clears the tint to 0x80/0/0/0 and counts the frame (0x365A);
   before frame 137 the spawn point follows joint 0x3646; on 68 it moves to joint 0x3644 (side 1), and from 80 to 100
   it keeps following it; on frames 78, 84 and 90 it takes joint 0x363C pushed away from joint 0x363E by their
   distance and spawns eight 0x1E018B0, a 0x1E01D50 and three 0x1E01E30 for each side */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x33B8];
    u8 col[4];
    u8 pad3618[0x24];
    s16 j3C;
    s16 j3E;
    u8 pad3640[4];
    s16 j44;
    s16 j46;
    u8 pad3648[0xE];
    s16 side;
    u8 pad3658[2];
    s16 t;
} Scene_b477_01E01600;

static void func_01E01600_b477(Scene_b477_01E01600 *g) {
    extern void b477_01E018B0(void);
    extern void b477_01E01D50(void);
    extern void b477_01E01E30(void);
    extern s32 b477_01E02B70(Scene_b477_01E01600 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f v[2];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t < 137) {
        func_001F5620(func_001F53A0(), g->j46, &a);
        g->px = a.x;
        g->py = a.y;
        g->pz = a.z;
    }
    if (g->t == 68) {
        func_001F5620(func_001F53A0(), g->j44, &a);
        g->px = a.x;
        g->py = a.y;
        g->pz = a.z;
        g->side = 1;
    }
    if (g->t >= 80 && g->t < 101) {
        func_001F5620(func_001F53A0(), g->j44, &a);
        g->px = a.x;
        g->py = a.y;
        g->pz = a.z;
        g->px = a.x;
        g->py = a.y;
        g->pz = a.z;
        g->side = 0;
        g->side = 1;
    }
    if (g->t == 78 || g->t == 84 || g->t == 90) {
        func_001F5620(func_001F53A0(), g->j3C, &v[0]);
        func_001F5620(func_001F53A0(), g->j3E, &v[1]);
        v[1].x = v[0].x - v[1].x;
        v[1].y = v[0].y - v[1].y;
        v[1].z = v[0].z - v[1].z;
        g->px = v[0].x + v[1].x;
        g->py = v[0].y + v[1].y;
        g->pz = v[0].z + v[1].z;
        for (i = 0; i < 8; i++) {
            b477_01E02B70(g, (s32)b477_01E018B0, 0);
        }
        b477_01E02B70(g, (s32)b477_01E01D50, 0);
        g->side = 0;
        for (i = 0; i < 3; i++) {
            b477_01E02B70(g, (s32)b477_01E01E30, 0);
        }
        g->side = 1;
        for (i = 0; i < 3; i++) {
            b477_01E02B70(g, (s32)b477_01E01E30, 0);
        }
    }
}

/* shape b124:01E01500, 93 insns, 3 copies: step of a drifting spark: on state 1 picks a random phase, angle, speed and
   lifetime and a grey colour; full alpha while young, then fades by 15 until it ends; drifts by its speed. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
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
} Obj_b124_01E01500;

static s32 func_01E018B0_b477(void *arg0, Obj_b124_01E01500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 20;
        o->h34 = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->w18 = 0;
        o->w18 = func_0019A5C8() % 360;
        o->pos = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 40 + 70;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 9 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    o->t++;
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

static s32 func_01E01A30_b477(void *arg0, Obj_b417_01E03510 *o) {
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

static s32 func_01E01C40_b477(void *arg0, Obj_b148_01E032D0 *o) {
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

static s32 func_01E01D50_b477(void *arg0, Obj_b258_01E027A0 *o) {
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

/* shape b477:01E01E30, 79 insns, 2 copies: a tumbling spark: set up once with a random drift and spin, a random climb rate;
   fades in over 2 frames, then once it has climbed past 20 fades out (b003:01E01780 family) */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 rate;
    u8 padA[6];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b477_01E01E30;

static s32 func_01E01E30_b477(void *arg0, Obj_b477_01E01E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = -10;
        o->w10 = func_0019A5C8() % 20 - 10;
        o->w14 = func_0019A5C8() % 360;
        o->w18 = 0;
        o->h34 = 0;
        o->state = 2;
        o->rate = func_0019A5C8() % 3 + 4;
        o->h6 = 0x14;
        func_001076F0(o->c0, 0x80, 0x20, 0x20);
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->h38 > 0x14) {
        if (o->c0[3] > 0x14) {
            o->c0[3] -= 0x13;
        } else {
            o->state = 0;
        }
    }
    if (o->t != 0) {
        o->h38 += o->rate;
    }
    o->t++;
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

static s32 func_01E01F70_b477(Mgr_b148_01E04020 *m, Obj_b148_01E04020 *o) {
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

static s32 func_01E020F0_b477(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
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

static s32 func_01E021B0_b477(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02D00_b477;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02D08_b477;
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

static void func_01E02200_b477(s32 arg0, Scene_b046_01E03200 *o) {
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

/* shape b477:01E022B0 (b477), 558 insns, 1 copy: b477 scene manager (b124:01E021C0 form): on start clears the 0x3BD0
   scene, two cameras, 145 ticks, eight joints, the textures, a +-15 jitter table and three more (0 for 100, then 0..4
   / 0..5 / 0..2 for 80, then 0..3, 5..24 signed by the facing, or -1..0 pushed 2 by the facing); each tick runs the
   script and the 200 slots' eight movers (the light one inline), draws four kinds; ends 1 / 4 / 2 at steps 68 / 103 /
   93, 6 in 78..89, 8 when the timer runs out */

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
} Slot_b477_01E022B0;

typedef struct {
    u8 pad0000[0x20];
    f32 x, y, z;
    u8 pad002C[0x54];
    s32 ot2;
    u8 pad0084[4];
    s32 tex88;
    u8 pad008C[8];
    Vec4f m94;
    u8 pad00A4[0x14];
    s16 mode;
    u8 pad00BA[0x1E];
    u8 camD8[0x1D8];
    s32 tex[16];
    Slot_b477_01E022B0 slot[200];
    u8 pad34F0[0x100];
    s32 tex5[3];
    u8 pad35FC[0x14];
    s32 timer;
    u8 pad3614[8];
    s32 ot;
    u8 pad3620[0x1C];
    s16 joint[8];
    u8 pad364C[0xC];
    s16 code;
    s16 step;
    s8 jit[256];
    s8 jitA[256];
    s8 jitB[256];
    s8 jitC[256];
    u8 cam3A5C[0x174];
} Ctx_b477_01E022B0;

static s32 func_01E022B0_b477(s32 arg0, s32 code) {
    Ctx_b477_01E022B0 *g = (Ctx_b477_01E022B0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E01600_b477();
    extern void func_01E00920_b477();
    Vec4f v;
    Vec4f m;
    Vec4f m2;
    Vec4f m3;
    Vec4f m4;
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
        g->timer = 145;
        g->joint[0] = func_001F5560(func_001F53A0(), 0xE, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x18, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x22, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->joint[6] = func_001F5560(func_001F53A0(), 0x36, 0);
        g->joint[7] = func_001F5560(func_001F53A0(), 0x37, 0);
        func_01E02200_b477(0, (void *)g);
        for (i = 0; i < 256; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
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
    func_01E01600_b477(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E018B0_b477) {
                func_01E018B0_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01A30_b477) {
                func_01E01A30_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01C40_b477) {
                func_01E01C40_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01D50_b477) {
                func_01E01D50_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01E30_b477) {
                func_01E01E30_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01F70_b477) {
                func_01E01F70_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E020F0_b477) {
                func_01E020F0_b477((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E021B0_b477) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E02D00_b477;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E02D08_b477;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            c++;
            if (g->slot[i].fn == func_01E018B0_b477) {
                g->tex88 = g->tex5[2];
                func_00106080(&m, 0x14, g->slot[i].rot, 0);
                g->m94 = m;
                g->mode = 10;
                g->x = g->slot[i].x;
                g->y = g->slot[i].y;
                g->z = g->slot[i].z;
                func_01E00DA0_b477((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->mode = 0;
            }
            if (g->slot[i].fn == func_01E01C40_b477) {
                g->tex88 = g->tex5[0];
                func_00106080(&m2, 0x14, g->slot[i].rot, 0);
                g->m94 = m2;
                v.x = g->slot[i].x;
                v.y = g->slot[i].y;
                v.z = g->slot[i].z;
                func_01E00BB0_b477((void *)g, (void *)&g->slot[i], 0, v);
            }
            if (g->slot[i].fn == func_01E01D50_b477) {
                g->tex88 = g->tex[15];
                func_00106080(&m3, 0x9B, g->slot[i].rot, 0);
                g->m94 = m3;
                func_01E00920_b477(g, &g->slot[i], w, 0);
            }
            if (g->slot[i].fn == func_01E01E30_b477) {
                g->tex88 = g->tex[15];
                func_00106080(&m4, 0x97, g->slot[i].rot, 0);
                g->m94 = m4;
                g->mode = 1;
                func_01E01210_b477((void *)g, (void *)&g->slot[i], g->slot[i].side);
                g->mode = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 0x44) {
        return 1;
    }
    if (g->step == 0x67) {
        return 4;
    }
    if (g->step == 0x5D) {
        return 2;
    }
    if (g->step >= 0x4E && g->step < 0x5A) {
        return 6;
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

static s32 func_01E02B70_b477(Pool_b046_01E03E20 *o, s32 a, s32 b) {
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
