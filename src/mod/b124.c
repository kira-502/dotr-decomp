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

static void func_01E00080_b124(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b124(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
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
    func_01E00080_b124((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b124 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b124_01E00D90_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b124_01E00D90_unused;

typedef struct Obj_b124_01E00D90 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b124_01E00D90;

typedef struct Xyz_b124_01E00D90 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b124_01E00D90;

typedef struct Uv_b124_01E00D90 {
    f32 u, v;
} Uv_b124_01E00D90;

typedef struct Pk_b124_01E00D90 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b124_01E00D90 uv;
    u64 pad18;
    Xyz_b124_01E00D90 v[4];
    u64 pad60[6];
} Pk_b124_01E00D90;

typedef struct Buf_b124_01E00D90 {
    u64 tag;
    Pk_b124_01E00D90 pk;
} Buf_b124_01E00D90;


typedef struct Data_b124_01E00D90 {
    u8 pad0[0x10];
    s32 wh[2];
    u8 padB[0x10];
    Vec4f uv;
} Data_b124_01E00D90;

static void func_01E00D90_b124(Obj_b124_01E00D90 *obj, Data_b124_01E00D90 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b124_01E00D90 buf;
    Uv_b124_01E00D90 uv;
    Pk_b124_01E00D90 *p = &buf.pk;

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
    func_00107740(&uv, &data->uv);
    p->uv = uv;
    func_01E00080_b124((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] = 0x4000;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->wh[0], data->wh[1]);
    func_00109100(view, data->wh, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
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

static void func_01E00F80_b124(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

/* shape b124:01E01210, 185 insns: the scene script of b124 (b361:01E00920's kind): red scene colour 0x80, counts
   g+0x3822; from tick 222 to 345 it spawns 0x1E01C00 each tick; at 222 also 0x1E01F50 and, 60 above the camera's view
   point, 0x1E017D0; at 220 0x1E01A30; from 258 to 340 it spawns 4..12 sparks around the joint g+0x3804 (x +-30,
   y -42..17, z +-15); at 68 the burst point jumps to the joint g+0x380C (and 0x381C is set), and from 80 to 100 it
   follows that joint */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x3578];
    u8 col[4];
    u8 pad37D8[0x2C];
    s16 joint;
    u8 pad3806[6];
    s16 joint2;
    u8 pad380E[0xE];
    s16 h381C;
    u8 pad381E[4];
    s16 tick;
} Ctx_b124_01E01210;

static void func_01E01210_b124(Ctx_b124_01E01210 *g) {
    extern void b124_01E01680();
    extern void b124_01E017D0();
    extern void b124_01E01A30();
    extern void b124_01E01C00();
    extern void b124_01E01F50();
    extern void b124_01E027F0(Ctx_b124_01E01210 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    s32 i;
    s32 n;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick >= 222 && g->tick < 346) {
        b124_01E027F0(g, b124_01E01C00, 0);
    }
    if (g->tick == 222) {
        b124_01E027F0(g, b124_01E01F50, 0);
    }
    if (g->tick == 222) {
        func_001F5F90(func_001F53A0(), v);
        g->x = v[0];
        g->y = 60.0f + v[1];
        g->z = v[2];
        b124_01E027F0(g, b124_01E017D0, 0);
    }
    if (g->tick == 220) {
        b124_01E027F0(g, b124_01E01A30, 0);
    }
    if (g->tick >= 258 && g->tick < 341) {
        func_001F5620(func_001F53A0(), g->joint, v);
        n = func_0019A5C8() % 9 + 4;
        for (i = 0; i < n; i++) {
            g->x = v[0] + func_0019A5C8() % 60 - 30.0f;
            g->y = v[1] + func_0019A5C8() % 60 - 30.0f - 12.0f;
            g->z = v[2] + func_0019A5C8() % 30 - 15.0f;
            b124_01E027F0(g, b124_01E01680, 0);
        }
    }
    if (g->tick == 68) {
        func_001F5620(func_001F53A0(), g->joint2, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->h381C = 1;
    }
    if (g->tick >= 80 && g->tick < 101) {
        func_001F5620(func_001F53A0(), g->joint2, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
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

static s32 func_01E01500_b124(void *arg0, Obj_b124_01E01500 *o) {
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

/* shape b124:01E01680, 83 insns: a white streak (size 50) at random angles, flying 7 a tick sideways (direction from the scene flag) and 2 down: alpha 0x80 for 11 ticks, then out by 24 and ends */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
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
} Glow_b124_01E01680;

typedef struct {
    u8 pad[0x381E];
    s16 flip;
} Game_b124_01E01680;

static s32 func_01E01680_b124(Game_b124_01E01680 *g, Glow_b124_01E01680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        o->w10 = 50;
        o->w14 = 10;
        if (g->flip != 0) {
            o->w18 = 25;
        } else {
            o->w18 = -25;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 180;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 11) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x19) {
        o->col[3] -= 0x18;
    } else {
        o->mode = 0;
    }
    o->kind = 2;
    if (g->flip != 0) {
        o->h4 -= 7;
    } else {
        o->h4 += 7;
    }
    o->h2 -= 2;
    o->tick++;
    return 0;
}

/* shape b124:01E017D0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0x80
   for the first 120 ticks, then fades out by 10 and stops */

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
} Flash_b124_01E017D0;

static s32 func_01E017D0_b124(s32 arg0, Flash_b124_01E017D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x726;
        func_001076F0(o->col, 0xC0, 0x70, 0);
        func_001076F0(o->col2, 0x20, 0x10, 0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 0x78) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b124:01E018B0, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x37D0 is 1 */

typedef struct {
    u8 pad0[0x3760];
    f32 l0[4];
    f32 pos[3];
    u8 pad377C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad378C[0x44];
    s32 state;
} Scene_b124_01E018B0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b124_01E018B0;

static s32 func_01E018B0_b124(Scene_b124_01E018B0 *g, Obj_b124_01E018B0 *o) {
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

/* shape b124:01E01A30, 51 insns: volume fade by its own timer (b003:01E02330 family): for 0x82 frames down 10 to 0x30, then up 10 to
   0x80, where the fade ends */

typedef struct {
    u8 pad[0x37D0];
    s32 state;
} Game_b124_01E01A30;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    s16 t;
    u8 pad34[2];
    s16 mode;
} Fade_b124_01E01A30;

static s32 func_01E01A30_b124(Game_b124_01E01A30 *g, Fade_b124_01E01A30 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0x82) {
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
            o->mode = 0;
        }
    }
    o->t++;
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b124:01E01B00, 61 insns: a pulsing screen tint: its alpha rises by 30 to 0xC0 and falls back to 0x40 in turn;
   two colours from the module's table with all three channels set to the alpha, sent to the scene filter */

typedef struct {
    u8 r, g, b, a;
} Col_b124_01E01B00;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b124_01E01B00;

static s32 func_01E01B00_b124(void *arg0, Obj_b124_01E01B00 *o) {
    extern Col_b124_01E01B00 D_01E02A80_b124;
    extern Col_b124_01E01B00 D_01E02A88_b124;
    extern void func_001F7170(s32, s32, void *, void *, s32);
    Col_b124_01E01B00 a;
    Col_b124_01E01B00 b;

    a = D_01E02A80_b124;
    b = D_01E02A88_b124;
    if (o->state == 1) {
        o->up = 0;
        o->c0[3] = 0;
    }
    if (o->up == 0) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x1E;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 0x40) {
        o->c0[3] -= 0x1E;
    } else {
        o->up = 0;
    }
    a.b = o->c0[3];
    b.b = o->c0[3];
    a.g = o->c0[3];
    b.g = o->c0[3];
    a.r = o->c0[3];
    b.r = o->c0[3];
    func_001F7170(3, 1, &a, &b, 1);
    return 0;
}

/* OVL_WARM */

/* shape b593:01E02E10, 174 insns: b183:01E01F30 with the packet at ctx+0x45EC and the tracked point at ctx+0x4608 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b124_01E01C00;

typedef struct {
    f32 s, t;
    Xyz_b124_01E01C00 p;
} Tv_b124_01E01C00;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b124_01E01C00 v[2];
} Tex_b124_01E01C00;

typedef struct {
    u8 pad[0x37E8];
    f32 depth;
    u8 pad37EC[0x14];
    Tex_b124_01E01C00 *pk;
    s16 id;
} Game_b124_01E01C00;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b124_01E01C00;

static s32 func_01E01C00_b124(Game_b124_01E01C00 *g, Fx_b124_01E01C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    extern void func_00205440(void *, void *, void *, f32 *);
    f32 fx;
    f32 fy;
    f32 v[4];
    u64 z;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0x78;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->id, v);
    func_001F5F90(func_001F53A0(), v);
    func_00205440(v, NULL, &g->pk->v[0].p, &g->depth);
    z = g->pk->v[0].p.z;
    z -= 4000;
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
    g->pk->v[1].t = (448.0f - 3.0f * fy) / 512.0f;
    g->pk->v[0].p.z = z;
    g->pk->v[1].p.z = z;
    func_002075F0((s32)g->pk, 0, (u32)(g->depth - 2000.0f));
    func_002075F0((s32)g->pk, 0, (u32)(g->depth - 2000.0f));
    o->f8 += (s16)(func_0019A5C8() % 30 + 100);
    o->fA += (s16)(func_0019A5C8() % 30 + 100);
    if (o->tick != 0) {
        if (o->col[3] > 40) {
            o->col[3] -= 49;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b124_01E01F50;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b124_01E01F50;

typedef struct {
    f32 s, t;
    Xyz_b124_01E01F50 p;
} Vtx_b124_01E01F50;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b124_01E01F50 c;
    Vtx_b124_01E01F50 v[2];
    u64 tail;
} Pkt_b124_01E01F50;

typedef struct {
    u8 pad0000[0x3800];
    Pkt_b124_01E01F50 *pkt;
} Mgr_b124_01E01F50;

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 h32;
    u8 pad34[2];
    s16 h36;
} Obj_b124_01E01F50;

static s32 func_01E01F50_b124(Mgr_b124_01E01F50 *m, Obj_b124_01E01F50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);

    if (o->h36 == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h36 = 2;
    }
    m->pkt->c.r = o->col[0];
    m->pkt->c.g = o->col[1];
    m->pkt->c.b = o->col[2];
    m->pkt->c.a = o->col[3];
    m->pkt->c.q = 1.0f;
    m->pkt->v[0].p.x = 0x6BF8;
    m->pkt->v[0].p.y = 0x71F8;
    m->pkt->v[0].p.z = 0xFFFFFF;
    m->pkt->v[0].p.f = 0;
    m->pkt->v[1].p.x = 0x93F8;
    m->pkt->v[1].p.y = 0x8DF8;
    m->pkt->v[1].p.z = 0xFFFFFF;
    m->pkt->v[1].p.f = 0;
    m->pkt->v[0].s = 0.0f;
    m->pkt->v[0].t = 0.0f;
    m->pkt->v[1].s = 0.625f;
    m->pkt->v[1].t = 0.875f;
    func_002075F0(m->pkt, 0, 0);
    if (o->h32 < 135) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    return 0;
}

/* shape b124:01E02110, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x2A0];
    s32 tex[16];
    u8 pad2E0[0x34D0];
    s32 tex5[3];
} Scene_b124_01E02110;

static void func_01E02110_b124(s32 arg0, Scene_b124_01E02110 *o) {
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

/* shape b124:01E021C0 (b124), 393 insns, 1 copy: the module main (b490:01E020F0 form): on start clears the 0x3B90
   scene, two cameras, 462 ticks, eight joints, the textures, a +-15 jitter table and a second table (0 for 100, 0..4
   for 80, then 0..3 signed by the facing); each tick runs the 210 slots six movers, counting the two kinds drawn by
   the module draw pass, then draws three kinds; ends 2 at step 345, 6 in 231..339, 8 when the timer runs out */

typedef struct {
    s16 x, y, z;
    u8 pad06[0x1E];
    void *fn;
    u8 pad28[0xC];
    s16 rot;
    s16 used;
    u8 pad38[8];
} Slot_b124_01E021C0;

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
    u8 camD8[0x208];
    Slot_b124_01E021C0 slot[210];
    u8 pad3760[0x54];
    s32 texA;
    s32 texB;
    u8 pad37BC[0x14];
    s32 timer;
    u8 pad37D4[8];
    s32 ot;
    u8 pad37E0[0x24];
    s16 joint[8];
    u8 pad3814[0xA];
    s16 face;
    s16 code;
    s16 step;
    s8 jit[256];
    s8 jit2[256];
    u8 pad3A24[0x16C];
} Ctx_b124_01E021C0;

static s32 func_01E021C0_b124(s32 arg0, s32 code) {
    Ctx_b124_01E021C0 *g = (Ctx_b124_01E021C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E01210_b124();
    extern void func_01E00F80_b124();
    extern void b124_01E02910();
    Vec4f v;
    Vec4f m;
    Vec4f m2;
    s32 r1[4];
    s32 r2[4];
    u8 w[0x90];
    s32 n;
    s32 c;
    s32 i;
    s32 face;

    n = 0;
    c = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3B90);
        func_00107C10(g->pad3A24);
        func_00107C10(g->camD8);
        g->code = code;
        g->timer = 462;
        g->joint[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x36, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x37, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x1F, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->joint[6] = func_001F5560(func_001F53A0(), 0x36, 0);
        g->joint[7] = func_001F5560(func_001F53A0(), 0x37, 0);
        func_01E02110_b124(0, (void *)g);
        func_001F6160(func_001F53A0(), r1);
        g->face = r1[1] / 180.0f;
        for (i = 0; i < 256; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 100; i++) {
            g->jit2[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 5;
        }
        func_001F6160(func_001F53A0(), r2);
        face = r2[1] / 180.0f;
        for (i = 180; i < 256; i++) {
            if (face != 0) {
                g->jit2[i] = func_0019A5C8() % 4;
            } else {
                g->jit2[i] = -(func_0019A5C8() % 4);
            }
        }
        return 0;
    }
    func_01E01210_b124(g, 0);
    for (i = 0; i < 210; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E01500_b124) {
                func_01E01500_b124((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01680_b124) {
                func_01E01680_b124((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E017D0_b124) {
                func_01E017D0_b124((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E018B0_b124) {
                func_01E018B0_b124((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01A30_b124) {
                func_01E01A30_b124((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01B00_b124) {
                func_01E01B00_b124((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01C00_b124) {
                n = (s16)(n + 1);
            }
            if (g->slot[i].fn == func_01E01F50_b124) {
                n = (s16)(n + 1);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 210; i++) {
        if (g->slot[i].used != 0) {
            c++;
            if (g->slot[i].fn == func_01E01500_b124) {
                g->tex88 = g->texA;
                func_00106080(&m, 0x14, g->slot[i].rot, 0);
                g->m94 = m;
                g->mode = 10;
                g->x = g->slot[i].x;
                g->y = g->slot[i].y;
                g->z = g->slot[i].z;
                func_01E00920_b124((void *)g, (void *)&g->slot[i], 0, g->jit);
                g->mode = 0;
            }
            if (g->slot[i].fn == func_01E01680_b124) {
                g->tex88 = g->texB;
                func_00106080(&m2, 0x14, g->slot[i].rot, 0);
                g->m94 = m2;
                v.x = g->slot[i].x;
                v.y = g->slot[i].y;
                v.z = g->slot[i].z;
                func_01E00D90_b124((void *)g, (void *)&g->slot[i], 0, v);
            }
            if (g->slot[i].fn == func_01E017D0_b124) {
                func_01E00F80_b124(g, &g->slot[i], w, 0);
            }
        }
    }
    if (n != 0) {
        b124_01E02910(g);
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 345) {
        return 2;
    }
    if (g->step > 230 && g->step < 340) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b124:01E027F0, 72 insns: twin of b046:01E03E20: take the first free slot of the 210-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x381C and the two arguments; returns 1 if a
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
} Slot_b124_01E027F0;

typedef struct {
    u8 pad[0x250];
    u8 m[0x90];
    Slot_b124_01E027F0 s[210];
    u8 pad3760[0x74];
    u8 r, g, b, a;
    u8 pad37D8[0x44];
    s16 v;
} Pool_b124_01E027F0;

static s32 func_01E027F0_b124(Pool_b124_01E027F0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b124_01E027F0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 210; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 210;
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

/* shape b124:01E02910, 82 insns: the module's draw pass (b116:01E06870 shape): opens a sprite packet on the stack, then runs every
   live slot (210 of 0x40 bytes) through its handler b124:01E01C00 or b124:01E01F50; always queues the batch at the scene
   depth - 2000. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b124_01E02910;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b124_01E02910 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b124_01E02910;

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 active;
    u8 pad38[8];
} Slot_b124_01E02910;

typedef struct {
    u8 pad0[0x2E0];
    Slot_b124_01E02910 slot[210];
    u8 padEnd[0x37E8 - 0x2E0 - 210 * 0x40];
    f32 depth;
    u8 pad37EC[0x10];
    s32 ctx;
    Pkt_b124_01E02910 *pkt;
} Scene_b124_01E02910;

static void func_01E02910_b124(Scene_b124_01E02910 *s) {
    extern void b124_01E01C00(Scene_b124_01E02910 *, Slot_b124_01E02910 *);
    extern void b124_01E01F50(Scene_b124_01E02910 *, Slot_b124_01E02910 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b124_01E02910 pkt __attribute__((aligned(8)));
    s32 i;

    s->pkt = &pkt;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 210; i++) {
        if (s->slot[i].active != 0) {
            if (s->slot[i].fn == (void *)b124_01E01C00) {
                b124_01E01C00(s, &s->slot[i]);
            }
            if (s->slot[i].fn == (void *)b124_01E01F50) {
                b124_01E01F50(s, &s->slot[i]);
            }
        }
    }
    func_00207FD0(s->ctx, func_00207500(), (u32)(s->depth - 2000.0f));
}
