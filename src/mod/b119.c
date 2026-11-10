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

static void func_01E00080_b119(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b119:01E00920, 258 insns, 4 copies: draws a flat ring of 18 quads like shape b112:01E00B60, turned by the ring's own
   rotation instead of the camera's; radii converted once. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E00920;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b119_01E00920;

static void func_01E00920_b119(Obj_b119_01E00920 *o, Ring_b119_01E00920 *s, s32 mode, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 t;
    f32 ro;
    f32 ri;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = ro * func_00108030(o->xD8, t, 1);
            quad[0].z = ro * func_00108030(o->xD8, t, 0);
            quad[2].x = ri * func_00108030(o->xD8, t, 1);
            quad[2].z = ri * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

/* OVL_WARM */

/* shape b119:01E00D30, 199 insns, 3 copies: draws one sprite at a given position plus a tenth of an offset, turned by
   the sprite's rotation; blend from flags >> 4, depth mode flags & 0xF (projected or far). Texture corners by
   the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b119_01E00D30;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b119_01E00D30 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b119_01E00D30;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b119_01E00D30;

typedef struct {
    u8 pad0[8];
    s16 dx, dy, dz;
    u8 padE[2];
    Vec4f rot;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b119_01E00D30;

static void func_01E00D30_b119(Obj_b119_01E00D30 *o, Spr_b119_01E00D30 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b119_01E00D30 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b119_01E00D30 pkt __attribute__((aligned(8)));
    Pkt_b119_01E00D30 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b119_01E00D30 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if ((flags >> 4) == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E00080_b119((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    p2.x = pos.x + dx;
    p2.y = pos.y + dy;
    p2.z = pos.z + dz;
    func_00108EF0(m, &scale, rot, &p2);
    func_00108CE0(quad, s->size, s->size);
    func_00109100(quad, &s->rot, 2, o->xD8);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        if ((flags & 0xF) == 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        } else if ((flags & 0xF) == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b119:01E01050 (IWFlame5), 489 insns, 1 copy (-O3,p): b363:01E01160's sprite ring (IWMagicFragment_2) at -O3
   with an s16 size and mode 0 drawn at its depth when past 10 */

typedef struct Data_b119_01E01050 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1E];
    u8 f28[8];
    s16 f50;
    u8 pad32[6];
    s16 size;
    s16 step;
} Data_b119_01E01050;

typedef struct Obj_b119_01E01050 {
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
} Obj_b119_01E01050;

typedef struct Xyz_b119_01E01050 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b119_01E01050;

typedef struct Uv_b119_01E01050 {
    f32 u, v;
} Uv_b119_01E01050;

typedef struct Pk_b119_01E01050 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b119_01E01050 uv;
    u64 pad18;
    Xyz_b119_01E01050 v[4];
    u64 pad60[6];
} Pk_b119_01E01050;

typedef struct Buf_b119_01E01050 {
    u64 tag;
    Pk_b119_01E01050 pk;
} Buf_b119_01E01050;

#pragma optimization_level 3

static void func_01E01050_b119(Obj_b119_01E01050 *obj, Data_b119_01E01050 *data, s32 flags, s8 *tab) {
    f32 size;
    f32 fov;
    extern void func_01E00080_b119();
    extern void func_00108950();
    extern void func_00108EF0();
    extern f32 func_001F9A20(s32);
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b119_01E01050 buf;
    Uv_b119_01E01050 uv;
    s16 sel;
    s16 i;
    Pk_b119_01E01050 *p;
    s32 mode;
    s8 *row;
    s32 half;

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
    func_00107740(&uv, data->f28);
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
    func_01E00080_b119(p, obj->f94, obj->fC0);
    fov = func_001F9A20(0);
    if (fov == 0.0f) {
        fov = 400.0f;
    }
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        size = data->size;
        func_00108CE0(view, 0.0f, 0.0f);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = (row[data->f8 + 180] / 20.0f) * (data->f50 + half);
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                size /= depth[0] / (fov / 10.0f);
                p->v[0].x = (u32)((f32)(u32)p->v[0].x - size);
                p->v[0].y = (u32)((f32)(u32)p->v[0].y + size);
                p->v[1].x = (u32)((f32)(u32)p->v[1].x + size);
                p->v[1].y = (u32)((f32)(u32)p->v[1].y + size);
                p->v[2].x = (u32)((f32)(u32)p->v[2].x - size);
                p->v[2].y = (u32)((f32)(u32)p->v[2].y - size);
                p->v[3].x = (u32)((f32)(u32)p->v[3].x + size);
                p->v[3].y = (u32)((f32)(u32)p->v[3].y - size);
                if (depth[0] > 10.0f) {
                    func_002075F0((s32)p, obj->f80, (u32)depth[0]);
                }
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

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E01800_b119);

/* shape b119:01E021F0, 179 insns: b119:01E026D0's spark keeping its picked colour, size 100, f30 1..25, life 2..3;
   alpha up by 42 to 0x80, then down by 13; it also nudges the scene point numbered fA (g+0x34D0) up by 0..1 and
   turns 5 a tick */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E021F0;

typedef struct {
    u8 pad0[0x34D0];
    Vec4f pt[1];
} Scene_b119_01E021F0;

static s32 func_01E021F0_b119(Scene_b119_01E021F0 *g, Fx_b119_01E021F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = 100;
        o->f34 = 0;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (k == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 25 + 1;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 2;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->y += (s16)(func_0019A5C8() % 2);
    }
    if (o->tick != 0) {
        g->pt[o->fA].y += func_0019A5C8() % 2;
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f3A += 5;
        } else {
            o->f3A -= 5;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b119:01E024C0, 131 insns: a rising spark in a random colour (blue, red or yellow): keeps its start height in
   0xA, turn 0..359, rise 2..11, f8 0..34, hold 3..4; alpha grows by 0x2A (below 0x80) while held, then fades by 0xD
   (ends below 0xF); after the first tick it jitters y by -1..1 and rises */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 h0;
    s16 fC;
    s16 rise;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 ang;
} Fx_b119_01E024C0;

static s32 func_01E024C0_b119(s32 arg0, Fx_b119_01E024C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 c;

    if (o->mode == 1) {
        o->f38 = 0x28;
        o->f34 = 0;
        c = func_0019A5C8() % 3;
        if (c == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (c == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (c == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        o->h0 = o->h;
        o->h = 0;
        o->ang = func_0019A5C8() % 360;
        o->rise = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 3;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 0xE) {
        o->col[3] -= 0xD;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->y += (s16)(func_0019A5C8() % 2);
    }
    if (o->t != 0) {
        o->h += o->rise;
    }
    o->t++;
    return 0;
}

/* shape b119:01E026D0, 176 insns: b119:01E032A0's spark (the colour pick is overwritten by grey 0x80), size 200, frame
   0..7 to start, f30 100..499 growing 2..11 a tick, life 2..5; alpha up by 64 to 0xC0, then down by 19; it wobbles
   up 0..1 and turns 1 a tick */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E026D0;

static s32 func_01E026D0_b119(s32 arg0, Fx_b119_01E026D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = 200;
        o->f34 = func_0019A5C8() % 8;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (k == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 400 + 100;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 4 + 2;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    o->f34++;
    if (o->f34 > 7) {
        o->f34 = 0;
    }
    if (o->tick != 0) {
        o->y += (s16)(func_0019A5C8() % 2);
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f3A += 1;
        } else {
            o->f3A -= 1;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b119:01E02990, 146 insns: a dark spinning puff with a random dim tint (blue, red, yellow, green, orange or
   purple): size 80 growing 10..14 a tick, turn 0..359; the tint alpha jumps by 0x80 (below 0x80) for 20 ticks, then
   fades by 9 (ends below 11); spins 0x4000 a tick */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b119_01E02990;

static s32 func_01E02990_b119(s32 arg0, Fx_b119_01E02990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 c;

    if (o->mode == 1) {
        o->size = 80;
        func_001076F0(o->col, 8, 8, 8);
        func_001076F0(o->col2, 0x10, 0x10, 0x40);
        c = func_0019A5C8() % 6;
        if (c == 0) {
            func_001076F0(o->col2, 8, 8, 0x20);
        } else if (c == 1) {
            func_001076F0(o->col2, 0x20, 8, 8);
        } else if (c == 2) {
            func_001076F0(o->col2, 0x20, 0x20, 8);
        } else if (c == 3) {
            func_001076F0(o->col2, 8, 0x20, 8);
        } else if (c == 4) {
            func_001076F0(o->col2, 0x20, 0x10, 8);
        } else if (c == 5) {
            func_001076F0(o->col2, 0x10, 8, 0x20);
        }
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0;
        o->col2[3] = 0;
    }
    if (o->t < 20) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x80;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t != 0) {
        o->size += (s16)(func_0019A5C8() % 5 + 10);
    }
    o->t++;
    return 0;
}

/* shape b119:01E02BE0, 224 insns: a red, green or blue (by kind h30) beam between two scene points (ctx+0x3E30 + 32 k):
   size 50..129; its base sits at a random (-15..14, 100, -15..14) and its tip 30 high on an ellipse of radii 5..34
   (x) and 5..34 (z) at an angle turning by -5..4 (never 0) a tick; alpha up by 10 to 0x8A for 20 ticks, then
   flickers 0x90/0x70 until tick 250, then fades by 9 while the size shrinks by 2 */

typedef struct {
    Vec4f a;
    Vec4f b;
} Pair_b119_01E02BE0;

typedef struct {
    u8 pad0[0x3E30];
    Pair_b119_01E02BE0 pt[3];
    u8 pad3E90[0x4420 - 0x3E90];
    u8 trig[1];
} Ctx_b119_01E02BE0;

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b119_01E02BE0;

static s32 func_01E02BE0_b119(Ctx_b119_01E02BE0 *g, Fx_b119_01E02BE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 80 + 50;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x10, 0x10);
            func_001076F0(o->col2, 0x80, 0x10, 0x10);
        } else if (o->kind == 1) {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 0x10, 0x80, 0x10);
        } else if (o->kind == 2) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x10, 0x10, 0x80);
        }
        o->w10 = func_0019A5C8() % 30 + 5;
        o->w14 = func_0019A5C8() % 10 - 5;
        o->w18 = func_0019A5C8() % 30 + 5;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0;
        o->col2[3] = 0;
        o->hE = func_0019A5C8() % 10;
        g->pt[o->kind].a.x = func_0019A5C8() % 30 - 15;
        g->pt[o->kind].a.z = func_0019A5C8() % 30 - 15;
        if (o->w14 == 0) {
            o->w14 = 1;
        }
    }
    if (o->tick < 250) {
        if (o->tick < 20) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 10;
            }
        } else if (o->tick % 2 == 1) {
            o->col2[3] = 0x90;
        } else {
            o->col2[3] = 0x70;
        }
    } else {
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->mode = 0;
        }
        o->size -= 2;
        if (o->size < 0) {
            o->size = 0;
        }
    }
    g->pt[o->kind].a.y = 100.0f;
    g->pt[o->kind].b.y = 30.0f;
    g->pt[o->kind].b.x = o->w10 * func_00108030(g->trig, o->ang, 0);
    g->pt[o->kind].b.z = o->w18 * func_00108030(g->trig, o->ang, 1);
    o->ang += o->w14;
    o->tick++;
    return 0;
}

/* shape b119:01E02F60, 98 insns: a long coloured glow: frame 280, red, green or blue by its kind, random angle; alpha flickers
   0x80/0x70 by frame parity until frame 230, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b119_01E02F60;

static s32 func_01E02F60_b119(void *arg0, Obj_b119_01E02F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x118;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x10, 0x10);
            func_001076F0(o->c1, 0x80, 0x10, 0x10);
        } else if (o->kind == 1) {
            func_001076F0(o->c0, 0x10, 0x80, 0x10);
            func_001076F0(o->c1, 0x10, 0x80, 0x10);
        } else if (o->kind == 2) {
            func_001076F0(o->c0, 0x10, 0x10, 0x80);
            func_001076F0(o->c1, 0x10, 0x10, 0x80);
        }
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c0[3] = 0x80;
        o->c1[3] = 0;
    }
    if (o->t < 0xE6) {
        if (o->t % 2 == 1) {
            o->c0[3] = 0x80;
        } else {
            o->c0[3] = 0x70;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E030F0, 106 insns: on start 0x38 = 50, both colours red, green or blue by the kind 0x30 (0..2), random
   0x3A, alpha 0x80 and second alpha 0; alpha flickers 0x80 / 0xC0 for 260 ticks, then fades by 9 and stops; 0x38 counts
   down while it fades; func_00205C40 on the rotation at 0x10, which advances 0x4000 */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E030F0;

static s32 func_01E030F0_b119(s32 arg0, Fx_b119_01E030F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        } else if (o->kind == 1) {
            func_001076F0(o->col, 0x80, 0xFF, 0x80);
            func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        } else if (o->kind == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0x80;
        o->col2[3] = 0;
    }
    if (o->tick < 0x104) {
        if (o->tick % 2 == 1) {
            o->col[3] = 0xC0;
        } else {
            o->col[3] = 0x80;
        }
    } else {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        o->f38--;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b119:01E032A0, 154 insns: a coloured spark (blue, red or yellow; size 300, frame cycling 0..7, fA = old f30, f30 400..599 shrinking 20..39 per tick and ending below 0, angle 0..359 turning 5 one way or the other, f8 0..34, life 6..11): alpha up by 42 to 0x80, then down by 13 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E032A0;

static s32 func_01E032A0_b119(s32 arg0, Fx_b119_01E032A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = 300;
        o->f34 = 0;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (k == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 200 + 400;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 20;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 6 + 6;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->f34++;
    if (o->f34 > 7) {
        o->f34 = 0;
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f3A += 5;
        } else {
            o->f3A -= 5;
        }
    }
    if (o->f30 < 0) {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 -= o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b119:01E03510, 96 insns: on start 0x38 = 60, variant 5, colour (0x80, 0x60, 0x60), 0x30 toggles between 0 and
   a random angle, random heading 0x3A; alpha 0x80 for 7 ticks, then fades by 15 and stops; while 0x30 is set it
   drifts 10 along the heading (0x8 by the sine, 0xC by the cosine of the game table 0x4420) */

typedef struct {
    u8 pad0[0x4420];
    u8 trig[1];
} Game_b119_01E03510;

typedef struct {
    u8 pad0[8];
    s16 x;
    u8 padA[2];
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b119_01E03510;

static s32 func_01E03510_b119(Game_b119_01E03510 *g, Fx_b119_01E03510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->f34 = 5;
        func_001076F0(o->col, 0x80, 0x60, 0x60);
        if (o->f30 == 0) {
            o->f30 = func_0019A5C8() % 360;
        } else {
            o->f30 = 0;
        }
        o->heading = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->f30 != 0) {
        o->x = o->x + 10.0f * func_00108030(g->trig, o->heading, 0);
        o->z = o->z + 10.0f * func_00108030(g->trig, o->heading, 1);
    }
    o->tick++;
    return 0;
}

/* shape b119:01E03690, 93 insns: a grey spark: frame 200, start height 130..629 (old one kept), random angle, rise 30..59, width
   0..34, hold 2..3, side 0..1; alpha up by 42 to 0x80 until the hold, then down by 13 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 y0;
    s16 side;
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b119_01E03690;

static s32 func_01E03690_b119(void *arg0, Obj_b119_01E03690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xC8;
        o->sub = 0;
        func_0019A5C8();
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y0 = o->y;
        o->y = func_0019A5C8() % 500 + 0x82;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 30 + 0x1E;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 2;
        o->side = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 0xD;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E03810, 124 insns: a drifting particle: on start a random life 400..599, angle 0..359, fall speed 20..39,
   frame 0..34, fade-in time 6..11 and parity; alpha up by 42 to 0x80 during the fade-in, then down by 13 until it ends;
   the frame counter steps on odd frames and wraps at 8; it ends when the life runs out */

typedef struct {
    u8 pad0[6];
    s16 fadein;
    s16 frame;
    s16 oldlife;
    s16 parity;
    s16 fall;
    u8 pad10[0x18];
    u8 c[4];
    u8 pad2C[4];
    s16 life;
    s16 t;
    s16 step;
    s16 state;
    s16 f38;
    s16 angle;
} Obj_b119_01E03810;

static s32 func_01E03810_b119(void *g, Obj_b119_01E03810 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_0019A5C8(void);

    if (o->state == 1) {
        o->f38 = 300;
        o->step = 0;
        func_0019A5C8();
        func_001076F0(o->c, 0x80, 0x80, 0x80);
        o->oldlife = o->life;
        o->life = func_0019A5C8() % 200 + 400;
        o->angle = func_0019A5C8() % 360;
        o->fall = func_0019A5C8() % 20 + 20;
        o->frame = func_0019A5C8() % 35;
        o->fadein = func_0019A5C8() % 6 + 6;
        o->parity = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->t < o->fadein) {
        if (o->c[3] < 0x80) {
            o->c[3] += 0x2A;
        }
    } else if (o->c[3] > 0xE) {
        o->c[3] -= 0xD;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        o->step++;
    }
    if (o->step > 7) {
        o->step = 0;
    }
    if (o->t != 0 && o->life < 0) {
        o->state = 0;
    }
    if (o->t != 0) {
        o->life -= o->fall;
    }
    o->t++;
    return 0;
}

/* shape b119:01E03A00, 130 insns: grey puff (b582:01E02D30 family): random spin words, turn, size 25..74, f38 a third of
   it plus 0..19, fE 0..9; alpha grows by 10 (below 0x80) until scene count 270, then fades by 9 (ends below 11);
   spins 0x4000 a tick */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    s32 i10;
    s32 i14;
    s32 i18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Obj_b119_01E03A00;

typedef struct {
    u8 pad0[0x3F1C];
    s16 count;
} Scene_b119_01E03A00;

static s32 func_01E03A00_b119(Scene_b119_01E03A00 *g, Obj_b119_01E03A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 70 + 3;
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
        func_001076F0(o->c1, 0x60, 0x60, 0x60);
        o->i10 = func_0019A5C8() % 30 + 5;
        o->i14 = func_0019A5C8() % 10 - 5;
        o->i18 = func_0019A5C8() % 30 + 5;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->fA = func_0019A5C8() % 50 + 25;
        o->f38 = o->fA / 3;
        o->f38 += (s16)(func_0019A5C8() % 20);
        o->fE = func_0019A5C8() % 10;
    }
    if (g->count < 0x10E) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 10;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->i10);
    o->i10 += 0x4000;
    o->t++;
    return 0;
}

/* shape b119:01E03C10, 176 insns: b119:01E026D0 with life 3..6 and an upward wobble of 0..5 */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b119_01E03C10;

static s32 func_01E03C10_b119(s32 arg0, Fx_b119_01E03C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = 200;
        o->f34 = func_0019A5C8() % 8;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        } else if (k == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 400 + 100;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 4 + 3;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    o->f34++;
    if (o->f34 > 7) {
        o->f34 = 0;
    }
    if (o->tick != 0) {
        o->y += (s16)(func_0019A5C8() % 6);
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f3A += 1;
        } else {
            o->f3A -= 1;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b119:01E03ED0, 138 insns: b757:01E029A0-family scene light in (128, 8, 0, 0), placed past joint B (twice the
   A-to-B step from A); for 300 ticks it pulses by 0.1 between 0.1 and 1, then dims by 0.1 and ends; handed to
   func_001F6C10 while alive; ends when 0x3ED0 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b119_01E03ED0;

typedef struct {
    u8 pad0[0x34A0];
    Light_b119_01E03ED0 light;
    u8 pad34CC[0xA04];
    s32 flag;
    u8 pad3ED4[0x32];
    s16 ja;
    s16 jb;
} Scene_b119_01E03ED0;

typedef struct {
    u8 pad0[0x30];
    s16 dir;
    s16 t;
    u8 pad34[2];
    s16 mode;
} Fx_b119_01E03ED0;

static s32 func_01E03ED0_b119(Scene_b119_01E03ED0 *g, Fx_b119_01E03ED0 *o) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 8.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 120.0f;
        g->light.level = 0.0f;
        o->mode = 2;
        o->dir = 0;
    }
    dx = v[1].x - v[0].x;
    dy = v[1].y - v[0].y;
    dz = v[1].z - v[0].z;
    g->light.pos.x = v[0].x + 2.0f * dx;
    g->light.pos.y = v[0].y + 2.0f * dy;
    g->light.pos.z = v[0].z + 2.0f * dz;
    if (o->t < 0x12C) {
        if (o->dir == 0) {
            if (g->light.level < 1.0f) {
                g->light.level += 0.1f;
            } else {
                o->dir = 1;
            }
        } else if (g->light.level > 0.1f) {
            g->light.level -= 0.1f;
        } else {
            o->dir = 0;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b119:01E04100, 47 insns: b718:01E03D10 family: a volume eased by 10 toward 0x30 once the scene state passes 30 (else toward 0x80); full volume at state 1 */

typedef struct {
    u8 pad[0x3ED0];
    s32 state;
} Game_b119_01E04100;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b119_01E04100;

static s32 func_01E04100_b119(Game_b119_01E04100 *g, Fade_b119_01E04100 *o) {
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
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b119:01E041C0, 31 insns: calls func_001F7170(2, 0, &a, &b, 0) with the module's two floats, stops the
   effect after 10 ticks */

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b119_01E041C0;

typedef struct {
    f32 v;
} F1_b119_01E041C0;

extern F1_b119_01E041C0 D_01E05980_b119;
extern F1_b119_01E041C0 D_01E05988_b119;

static s32 func_01E041C0_b119(s32 arg0, Fx_b119_01E041C0 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b119_01E041C0 a;
    F1_b119_01E041C0 b;

    a = D_01E05980_b119;
    b = D_01E05988_b119;
    func_001F7170(2, 0, &a, &b, 0);
    if (o->tick >= 10) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b119", func_01E04240_b119);

/* shape b119:01E05220, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3F14 and the two arguments; returns 1 if a
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
} Slot_b119_01E05220;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b119_01E05220 s[200];
    u8 pad34A0[0xA34];
    u8 r, g, b, a;
    u8 pad3ED8[0x3C];
    s16 v;
} Pool_b119_01E05220;

static s32 func_01E05220_b119(Pool_b119_01E05220 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b119_01E05220 *s = NULL;
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

/* shape b119:01E05340, 216 insns: b119:01E056A0's disc as a ring between the object's two points (0x20 inner, 0x30
   outer, radius h38 / 10 around the outer one): 18 wedges, 20 apart from the band's start angle, two colours, at the
   position with no scale or turn; depth mode by flags (projected, far after a packet tweak, or front) */

typedef struct {
    u8 pad00[0x20];
    Vec4f a;
    Vec4f b;
    u8 pad40[0x40];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E05340;

typedef struct {
    u8 pad00[0x28];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 r;
    s16 start;
} Band_b119_01E05340;

static void func_01E05340_b119(Obj_b119_01E05340 *o, Band_b119_01E05340 *s, s32 flags, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 k;
    s32 t;
    s16 a;
    u8 *p;
    f32 r;
    f32 ro;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, 0, 0, &p2);
    quad[0].y = o->a.y;
    quad[1].y = o->a.y;
    quad[2].y = o->b.y;
    quad[3].y = o->b.y;
    ro = 0.0f;
    r = s->r;
    r /= 10.0f;
    for (k = 0; k < 18; k++) {
        t = s->start + a;
        quad[0].x = o->a.x + ro * func_00108030(o->xD8, t, 1);
        quad[0].z = o->a.z + ro * func_00108030(o->xD8, t, 0);
        quad[2].x = o->b.x + r * func_00108030(o->xD8, t, 1);
        quad[2].z = o->b.z + r * func_00108030(o->xD8, t, 0);
        t = a + (s->start + 20);
        quad[1].x = o->a.x + ro * func_00108030(o->xD8, t, 1);
        quad[1].z = o->a.z + ro * func_00108030(o->xD8, t, 0);
        quad[3].x = o->b.x + r * func_00108030(o->xD8, t, 1);
        quad[3].z = o->b.z + r * func_00108030(o->xD8, t, 0);
        if (flags == 0) {
            if (func_00205630(quad, 0x70000000, 0, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (flags == 1) {
            if (func_00205630(quad, 0x70000000, 0, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, 0, p, depth) != 0) {
            func_002075F0(p, o->ot, -1);
        }
        a += 20;
    }
}

/* shape b119:01E056A0, 173 insns: b108:01E00DF0's band as a flat disc: 18 wedges (20 apart from the band's start
   angle) from the centre out to radius h38 / 10, two colours, turned by the band's rotation at the position plus the
   object's offset; each wedge drawn far after a packet tweak */

typedef struct {
    u8 pad00[0x20];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E056A0;

typedef struct {
    u8 pad00[0x10];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 r;
    s16 start;
} Band_b119_01E056A0;

static void func_01E056A0_b119(Obj_b119_01E056A0 *o, Band_b119_01E056A0 *s, s32 flags, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 k;
    s32 t;
    s16 a;
    u8 *p;
    f32 r;
    f32 ro;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    p2.x += o->dx;
    p2.y += o->dy;
    p2.z += o->dz;
    func_00108EF0(m, 0, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = 0.0f;
    r = s->r;
    r /= 10.0f;
    for (k = 0; k < 18; k++) {
        t = s->start + a;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = r * func_00108030(o->xD8, t, 1);
        quad[2].z = r * func_00108030(o->xD8, t, 0);
        t = a + (s->start + 20);
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = r * func_00108030(o->xD8, t, 1);
        quad[3].z = r * func_00108030(o->xD8, t, 0);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_00109380(p, 1);
            func_002075F0(p, o->ot, 0);
        }
        a += 20;
    }
}
