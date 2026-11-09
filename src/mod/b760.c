#include "common.h"

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00080_b760(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b760 in the
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

static void func_01E004D0_b760(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b760((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00790_b760(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b760_01E00080();
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
    b760_01E00080(p, obj->f94, obj->fC0);
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

INCLUDE_ASM("asm/nonmatchings/mod/b760", func_01E00CE0_b760);

/* shape b760:01E01A10, 206 insns: b521:01E01440's puff with its height kept at twice the width (h8 = hA * 2) */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
    u8 padCBB6[2];
    s16 count;
} Ctx_b760_01E01A10;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b760_01E01A10;

static s32 func_01E01A10_b760(Ctx_b760_01E01A10 *ctx, Obj_b760_01E01A10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->hA = func_0019A5C8() % 6 + 4;
        o->h8 = o->hA * 2;
        o->f48 = 5.0f + (func_0019A5C8() >> 4) % 100;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->h5C = func_0019A5C8() % 20 - 10;
        o->h5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x1000 - 0x800;
        o->h2 = func_0019A5C8() % 0x1000 - 0x800;
        o->h0 = func_0019A5C8() % 0x1000 - 0x800;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 40) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->hA < 16) {
            o->hA += 2;
        }
        o->h8 = o->hA * 2;
    }
    if (o->t != 0) {
        o->y += 2.0f;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    o->h5A += o->h5C;
    return 0;
}

/* shape b521:01E01790, 120 insns, 2 copies: a pale bloom: set up once (random size 100..129, frame 0..7, angle 100..149, speed
   36..55, life 7..16); fades in for its life, then out; turns for 90 frames and grows 6 a frame for 140 (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b521_01E01790;

static s32 func_01E01D50_b760(void *arg0, Spark_b521_01E01790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 100;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        o->ang = func_0019A5C8() % 50 + 100;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 36;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 10 + 7;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t < 0x5A && o->t != 0) {
        o->ang += o->speed;
    }
    if (o->t < 0x8C) {
        o->size += 6.0f;
    }
    o->t++;
    return 0;
}

/* shape b760:01E01F30, 120 insns, 2 copies: a pale bloom: set up once (random size 100..129, frame 0..7, angle 100..149, speed
   36..55, life 7..16); fades in for its life, then out; turns for 90 frames and grows 6 a frame for 140 (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b760_01E01F30;

static s32 func_01E01F30_b760(void *arg0, Spark_b760_01E01F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 100;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        o->ang = func_0019A5C8() % 100 + 200;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 36;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 10 + 7;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t < 0x5A && o->t != 0) {
        o->ang += o->speed;
    }
    if (o->t < 0x8C) {
        o->size += 6.0f;
    }
    o->t++;
    return 0;
}

/* shape b760:01E02110 (B760_OBJ_MOVE_5_), 226 insns: b588:01E01EF0's spark in grey (0xC0): f8/fA 80..119, size
   5..104 growing 1 up to 150, kind (rand >> 4) % 3, drift (rand % 100 - 50) / 400, f5C -10..9, spin rates
   -0x800..0x7FF; brightens by 0x60 below 0xC0 for 60 ticks, then fades by 15; every third tick fA grows by 2 up to
   80; while moving it rises 2.6 and slides 2.4 in z (the sign by the game value at 0xD884) */

typedef struct {
    s16 r[3];
    u8 pad6[2];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 pos[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[6];
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b760_01E02110;

typedef struct {
    u8 pad[0xD884];
    s16 v;
} Game_b760_01E02110;

static s32 func_01E02110_b760(Game_b760_01E02110 *g, Fx_b760_01E02110 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->fA = func_0019A5C8() % 40 + 80;
        o->f8 = o->fA;
        o->size = 5.0f + (func_0019A5C8() >> 4) % 100;
        o->f56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->mode = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->f5C = func_0019A5C8() % 20 - 10;
        o->f5A = func_0019A5C8() % 360;
        func_00205C40(o->pos);
        o->r[2] = func_0019A5C8() % 0x1000 - 0x800;
        o->r[1] = func_0019A5C8() % 0x1000 - 0x800;
        o->r[0] = func_0019A5C8() % 0x1000 - 0x800;
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < 60) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        if (o->fA < 80) {
            o->fA += 2;
        }
        o->f8 = o->fA;
    }
    if (o->tick != 0) {
        o->f14 -= 2.6f;
        if (g->v != 0) {
            o->f18 -= 2.4f;
        } else {
            o->f18 += 2.4f;
        }
    }
    if (o->size < 150.0f) {
        o->size += 1.0f;
    }
    o->tick++;
    func_00205C40(o->pos);
    return 0;
}

/* shape b760:01E024A0, 222 insns: b521:01E01440's puff in white, width 2..7 with height 2.5x, size 5..104 growing
   by 1 to 150, drift /400, spin -0x800..0x7FF, fading in by 21 for 60 ticks; it rises 2.6 a tick and drifts 2.4
   along z by the scene flag (ctx+0xD884) */

typedef struct {
    u8 pad0[0xD884];
    s16 flag;
} Ctx_b760_01E024A0;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b760_01E024A0;

static s32 func_01E024A0_b760(Ctx_b760_01E024A0 *ctx, Obj_b760_01E024A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->hA = func_0019A5C8() % 6 + 2;
        o->h8 = 2.5f * o->hA;
        o->f48 = 5.0f + (func_0019A5C8() >> 4) % 100;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->h5C = func_0019A5C8() % 20 - 10;
        o->h5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x1000 - 0x800;
        o->h2 = func_0019A5C8() % 0x1000 - 0x800;
        o->h0 = func_0019A5C8() % 0x1000 - 0x800;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 60) {
        if (o->col[3] < 0x80) {
            o->col[3] += 21;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y -= 2.6f;
        if (ctx->flag != 0) {
            o->z -= 2.4f;
        } else {
            o->z += 2.4f;
        }
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    if (o->f48 < 150.0f) {
        o->f48 += 1.0f;
    }
    o->t++;
    return 0;
}

/* shape b760:01E02820, 181 insns: b521:01E01440's tumbling flake in white, size 10..17 (height 2.5 x size), alpha
   up by 21 for 10 ticks, then down by 9; it only spins */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
    u8 padCBB6[2];
    s16 count;
} Ctx_b760_01E02820;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b760_01E02820;

static s32 func_01E02820_b760(Ctx_b760_01E02820 *ctx, Obj_b760_01E02820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->hA = func_0019A5C8() % 8 + 10;
        o->h8 = 2.5f * o->hA;
        o->f48 = 5.0f + (func_0019A5C8() >> 4) % 100;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->h5C = func_0019A5C8() % 20 - 10;
        o->h5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x1000 - 0x800;
        o->h2 = func_0019A5C8() % 0x1000 - 0x800;
        o->h0 = func_0019A5C8() % 0x1000 - 0x800;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    return 0;
}

/* shape b760:01E02B00 (b760), 470 insns, 1 copy: the b760 scene manager in b751:01E02240 form: setup (sine table,
   five joints, two type-4 and three type-5 textures, 256 s8 jitters with 100..179 cleared, timer 390), step
   b760:01E00CE0 and every slot, draw six kinds (b760:01E01A10 circling at its radius, b760:01E01D50/01E01F30
   jittered, b760:01E02110, b760:01E024A0/01E02820); scene code from the frame */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b760_01E02B00;

typedef struct {
    u8 pad0[0x20];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[4];
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x1B8];
    s32 tex290[16];
    u8 pad2D0[0x11B0 - 0x2D0];
    Fx_b760_01E02B00 fx[450];
    u8 padD690[0xD7D0 - 0xD690];
    s32 tex[3];
    u8 padD7DC[0x14];
    s32 count;
    u8 padD7F4[8];
    s32 ot;
    u8 padD800[0x58];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    u8 padD862[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padD98A[2];
    u8 trig[4];
} Scene_b760_01E02B00;

static s32 func_01E02B00_b760(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_01E00CE0_b760();
    extern void func_01E00790_b760();
    extern void func_01E004D0_b760();
    Scene_b760_01E02B00 *g = (Scene_b760_01E02B00 *)arg0;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    s32 i;
    s32 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xDB00);
        func_00107C10(g->trig);
        func_00107C10(g->crdD8);
        for (i = 14; i < 16; i++) {
            g->tex290[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1D, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x3C, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x1D, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x3C, 0);
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->id = id;
        g->count = 390;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = 0;
        }
        return 0;
    }
    func_01E00CE0_b760(g, 0);
    for (k = 0; k < 450; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 450; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01A10_b760) {
                g->tex88 = g->tex[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x7F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 0;
                v.x = g->fx[k].pos.x + g->fx[k].f48 * func_00108030(g->trig, g->fx[k].h5A, 1);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z + g->fx[k].f48 * func_00108030(g->trig, g->fx[k].h5A, 0);
                func_01E004D0_b760(g, &g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D50_b760) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex[2];
                g->hB8 = 5;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00790_b760(g, &g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F30_b760) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex[2];
                g->hB8 = 5;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00790_b760(g, &g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02110_b760) {
                g->tex88 = g->tex[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E004D0_b760(g, &g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E024A0_b760) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x7F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E004D0_b760(g, &g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02820_b760) {
                g->tex88 = g->tex[1];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x7F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E004D0_b760(g, &g->fx[k], 0x20, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 150) {
        return 1;
    }
    if (g->frame == 370) {
        return 4;
    }
    if (g->frame == 355) {
        return 2;
    }
    if (g->frame > 160 && g->frame < 350) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b760:01E03260, 82 insns: c035:01E01150 family: take the first free effect slot of 450 (0x70 bytes each, at ctx+0x11B0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b760_01E03260;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x11b0 - 0x25C];
    Obj_b760_01E03260 slot[450];
    u8 padEnd[0xd7f4 - 0x11b0 - 450 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padD7F8[0x8A];
    s16 val;
} Ctx_b760_01E03260;

static s32 func_01E03260_b760(Ctx_b760_01E03260 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b760_01E03260 *s;

    s = NULL;
    for (i = 0; i < 450; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 450;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}
