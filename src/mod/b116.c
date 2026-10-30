#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b116(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00100_b116(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b116:01E009A0, 182 insns: b183:01E00E70's sprite with the camera's rotation reset by func_00205C40 first, a
   square view of the camera's size and the colour at camera+0x28 (b016:01E00ED0 kind, fixed blends (sel 0 = 0x42, 1 = 0x44, else 0x48)); draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b116 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b116_01E009A0 {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Cam_b116_01E009A0;

typedef struct Obj_b116_01E009A0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b116_01E009A0;

typedef struct Xyz_b116_01E009A0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b116_01E009A0;

typedef struct Uv_b116_01E009A0 {
    f32 u, v;
} Uv_b116_01E009A0;

typedef struct Pk_b116_01E009A0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b116_01E009A0 uv;
    u64 pad18;
    Xyz_b116_01E009A0 v[4];
    u64 pad60[6];
} Pk_b116_01E009A0;

typedef struct Buf_b116_01E009A0 {
    u64 tag;
    Pk_b116_01E009A0 pk;
} Buf_b116_01E009A0;

static void func_01E009A0_b116(Obj_b116_01E009A0 *obj, Cam_b116_01E009A0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b116_01E009A0 buf;
    Uv_b116_01E009A0 uv;
    s32 sel;
    s32 mode;
    Pk_b116_01E009A0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, cam->col);
    p->uv = uv;
    func_01E00100_b116((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)cam->rot);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, cam->rot, &a);
    func_00108CE0(view, cam->size, cam->size);
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

/* shape b081:01E016D0, 342 insns, 3 copies: draws a row of small camera-facing sprites at the object position (b008
   family): each shaken by a per-entry table offset turned by an extra axis and added to all four corners;
   blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module helper
   (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b081_01E016D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b081_01E016D0 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b081_01E016D0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 mode;
    u8 padC2[0x16];
    u8 xD8[1];
} Obj_b081_01E016D0;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b081_01E016D0;

static void func_01E00C80_b116(Obj_b081_01E016D0 *o, Spr_b081_01E016D0 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b081_01E016D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f e;
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b081_01E016D0 pkt __attribute__((aligned(8)));
    f32 f;
    s16 i;
    s16 b;
    Pkt_b081_01E016D0 *p;
    s32 mode;
    s32 h;
    s8 *j;

    func_00207500();
    p = (Pkt_b081_01E016D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    p2.x = o->pos.x;
    p2.y = o->pos.y;
    p2.z = o->pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    func_01E00100_b116((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        e.x = f * (s->w30 + h);
        f = j[s->off + 100];
        f /= 20.0f;
        e.y = f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        quad[0].x += e.x;
        quad[1].x += e.x;
        quad[2].x += e.x;
        quad[3].x += e.x;
        quad[0].y += e.y;
        quad[1].y += e.y;
        quad[2].y += e.y;
        quad[3].y += e.y;
        f = j[s->off + 180];
        f /= 20.0f;
        e.z = f * (s->w30 + h);
        quad[0].z += e.z;
        quad[1].z += e.z;
        quad[2].z += e.z;
        quad[3].z += e.z;
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

/* shape b116:01E011E0, 282 insns: full ring of 36 segments (10 table steps each) between an s16 inner and outer
   radius, variant of b082:01E00920 with a smaller data layout; blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b116_01E011E0;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 inner;
    s16 step;
} Data_b116_01E011E0;

static void func_01E011E0_b116(Obj_b116_01E011E0 *o, Data_b116_01E011E0 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
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
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    outer = data->outer;
    i = 0;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E01650_b116);

/* shape b116:01E01CE0, 105 insns: on start 0x38 = 60, variant 0..6, colour (0x20, 0x10, 0x10), 0xA 0..7, 0xC keeps the old 0x30, 0x30
   0..19, speed 16..45 (0xE), 0x8 0..34, hold 3..7 (0x6), 0x3A 0..2; alpha 0x80 during the hold, then fades by 8 and
   stops; after the first tick 0x38 grows by 8 and 0x30 by the speed */

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
} Fx_b116_01E01CE0;

static s32 func_01E01CE0_b116(s32 arg0, Fx_b116_01E01CE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->f34 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x10, 0x10);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f30;
        o->f30 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->f3A = func_0019A5C8() % 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += 8;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E01E90_b116(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b116:01E01F70, 254 insns: b284:01E01D30's glow in grey, held 37..61 ticks, that also drives the scene's
   point tables (0x44C4 x, 0x476C depth, slot o->hA): the slot starts at the glow's point less 0.7 in x, then each
   tick the depth follows the camera drift /95 and x drops 0.8; growing by 4 after scene count 341, its angle turning
   2 one way or the other by the spin's parity */

typedef struct {
    u8 pad0[0x44C4];
    f32 fx[170];
    f32 fz[181];
    u8 pad4A40[2];
    s16 ja;
    s16 jb;
    u8 pad4A46[0x1C];
    s16 count;
} Game_b116_01E01F70;

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b116_01E01F70;

static s32 func_01E01F70_b116(Game_b116_01E01F70 *g, Glow_b116_01E01F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 12;
        o->kind = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->hA = o->h30;
        g->fx[o->hA] = o->h2;
        g->fz[o->hA] = o->h4;
        g->fx[o->hA] -= 0.7f;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 25 + 37;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, (Vec4f *)(u32)&v[1]);
        o->hC = func_001A22C0(((Vec4f *)(u32)&v[1])->x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (g->count > 341) {
        o->f38 += 4;
    }
    if (o->tick != 0) {
        if (o->f38 < 60) {
            o->f38 += 2;
        }
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    if (o->tick != 0) {
        *(f32 *)(u32)&v[0].z -= v[1].z;
        *(f32 *)(u32)&v[0].z /= 95.0f;
        g->fz[o->hA] += v[0].z;
    }
    g->fx[o->hA] -= 0.8f;
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->h30 += o->hE;
    if (o->tick % 2 == 1) {
        o->f38 += 2;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    if (o->hE % 2 == 1) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b116:01E02370, 175 insns: b008:01E01660's glow aimed between two joints: grey 0x70 of size 50, rise 5..9, holds for
   30..39 ticks fading in by 0x20 to 0x40; on start hC is the angle from joint g+0x4A42 to g+0x4A44, each tick h4 turns
   by a fortieth of the camera depth difference between func_001F5380's and func_001F53A0's views, and h30 grows by
   the rise */

typedef struct {
    u8 pad0[0x4A42];
    s16 ja;
    s16 jb;
} Game_b116_01E02370;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b116_01E02370;

static s32 func_01E02370_b116(Game_b116_01E02370 *g, Glow_b116_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 50;
        o->kind = 0;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 30;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 40.0f;
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b116:01E02630, 240 insns: b257:01E024F0 twin (joints 0x4A42/0x4A44, softer alpha); b257:01E01EB0 cousin: size 100, a green, violet or red glow at random, h30 100..149,
   speed 3..12, hold 11..20; the first tick it jumps 17 depth steps toward the camera. As b257:01E01EB0: b257:01E021E0's glow in grey 0x70 with a random frame 0..3, start size 53 (63 once
   g+0x3726 reaches 80) growing by 1, rise 5..9, h8 0..9, held 17..26 ticks fading in by 0x40 */

typedef struct {
    u8 pad0[0x4A42];
    s16 ja;
    s16 jb;
    u8 pad370C[0x1A];
    s16 h3726;
} Game_b116_01E02630;

typedef struct {
    s16 h0;
    u8 pad2[2];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
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
} Glow_b116_01E02630;

static s32 func_01E02630_b116(Game_b116_01E02630 *g, Glow_b116_01E02630 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];
    s32 k;

    if (o->mode == 1) {
        o->f38 = 100;
        o->kind = 0;
        k = (s16)(func_0019A5C8() % 3);
        if (k == 0) {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
        } else if ((s16)k == 1) {
            func_001076F0(o->col, 0x40, 0, 0x80);
        } else {
            func_001076F0(o->col, 0x80, 0x10, 0x10);
        }
        o->h30 = func_0019A5C8() % 50 + 100;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 11;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 16;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    *(f32 *)(u32)&v[0].z /= 40.0f;
    if (o->tick == 0) {
        o->h4 = func_001A22C0(o->h4 + 17.0f * v[0].z);
    }
    o->h4 = func_001A22C0(o->h4 + v[0].z);
    if (o->tick % 2 == 1) {
        o->h0 += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 3) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 1;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad00[2];
    s16 h2;
    u8 pad04[2];
    s16 h6;
    s16 h8;
    u8 pad0A[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
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
} Obj_b003_01E01C70;

static s32 func_01E029F0_b116(s32 unused, Obj_b003_01E01C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 45;
        o->h34 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 300 + 130;
        o->h3A = func_0019A5C8() % 360;
        o->hE = 0;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 2;
        o->h6 = func_0019A5C8() % 10 + 15;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h32 != 0) {
        if (o->h38 < 90) {
            o->h38 += 2;
        }
    }
    if (o->h32 % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->h32 != 0) {
        o->h30 += o->hE;
    }
    if (o->h32 != 0) {
        o->h38 += 2;
    }
    o->h2++;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->h32++;
    return 0;
}

/* shape b003:01E01EC0, 146 insns, 4 copies: step of a rising puff: on state 1 sets a grey colour, random start, angle,
   size, layers and lifetime; fades in by 0x12, then out by 9 until it ends; grows, climbs and spins randomly. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[2];
    s16 layers;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b003_01E01EC0;

static s32 func_01E02C40_b116(void *arg0, Obj_b003_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0x2D;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->pos = func_0019A5C8() % 300 + 130;
        o->ang = func_0019A5C8() % 360;
        o->speed = 0;
        o->h8 = func_0019A5C8() % 35;
        o->layers = func_0019A5C8() % 3 + 2;
        o->life = func_0019A5C8() % 10 + 15;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x12;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 0x5A) {
            o->size += 2;
        }
    }
    if (o->t % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    if (o->t != 0) {
        o->size += 2;
    }
    o->y++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

/* shape b116:01E02E90, 190 insns: one of five orbiting lights (number 0x30): light 0 is the big centre (size 32,
   radius 0), lights 1..4 start a quarter turn apart at radius 13.2; from scene frame 368 each places its scene point
   (g+0x2D80) on its circle (raised by the centre's height g+0x4A34), drifts it 2 a frame along z (back with the scene
   flag) until frame 411, shrinks its radius by 0.3 to 0 and turns by 8 */

typedef struct {
    u8 pad0[0x2D80];
    Vec4f pts[5];
    u8 pad2DD0[0x1C50];
    f32 rad[6];
    u8 pad4A38[0x28];
    s16 flag;
    s16 frame;
    u8 pad4A64[0x100];
    u8 trig[1];
} Scene_b116_01E02E90;

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 k;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 ang;
} Light_b116_01E02E90;

static s32 func_01E02E90_b116(Scene_b116_01E02E90 *g, Light_b116_01E02E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        if (o->k == 0) {
            o->size = 32;
        } else {
            o->size = 13;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        if (o->k == 1) {
            o->ang = 0;
        }
        if (o->k == 2) {
            o->ang = 180;
        }
        if (o->k == 3) {
            o->ang = 90;
        }
        if (o->k == 4) {
            o->ang = 270;
        }
        if (o->k == 0) {
            g->rad[o->k] = 0.0f;
        } else {
            g->rad[o->k] = 13.2f;
        }
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        o->col[3] += 0x40;
        o->col2[3] += 0x40;
    }
    if (g->frame > 367) {
        g->pts[o->k].x = g->rad[o->k] * func_00108030(g->trig, o->ang, 0);
    }
    if (g->frame > 367) {
        g->pts[o->k].y = g->rad[o->k] * func_00108030(g->trig, o->ang, 1);
    }
    if (g->frame > 367) {
        g->pts[o->k].y += g->rad[5];
    }
    if (g->frame > 367 && g->frame < 411) {
        if (g->flag != 0) {
            g->pts[o->k].z -= 2.0f;
        } else {
            g->pts[o->k].z += 2.0f;
        }
    }
    if (g->frame > 367) {
        if (g->rad[o->k] > 0.0f) {
            g->rad[o->k] -= 0.3f;
        }
    }
    if (g->frame > 367) {
        o->t++;
    }
    func_00205C40((s32)o->rot);
    if (g->frame > 367) {
        o->ang += 8;
    }
    return 0;
}

/* shape b116:01E03190, 115 insns, 1 copy: a red/yellow trail (b108:01E02010's form, 70-point rows): width 8 growing
   by 2 to 48 once the scene timer (0x4A62) reaches 367; fills its trail row with its point, holds alpha 0xC0 until the
   timer reaches 447, then fades by 5 until it ends; rebuilds the trail tail from its point each frame; flickers */

typedef struct {
    f32 x, y, z, w;
} V4_b116_01E03190;

typedef struct {
    u8 pad0[0x2D80];
    V4_b116_01E03190 pts[10];
    u8 pad2E20[0x50];
    V4_b116_01E03190 trail[5][70];
    u8 pad4450[0x4A62 - 0x4450];
    s16 timer;
} Game_b116_01E03190;

typedef struct {
    u8 pad0[6];
    s16 w;
    u8 pad8[0x20];
    u8 c0[4];
    u8 pad2C[4];
    s16 row;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b116_01E03190;

static s32 func_01E03190_b116(Game_b116_01E03190 *g, Obj_b116_01E03190 *o) {
    extern void b116_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    V4_b116_01E03190 *p;
    V4_b116_01E03190 *q;

    if (o->state == 1) {
        o->w = 8;
        o->c0[3] = 0;
        p = &g->pts[o->row];
        q = g->trail[o->row];
        for (i = 0; i < 0x31; i++) {
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
            q++;
        }
        o->h38 = 10;
        o->state = 2;
    }
    if (g->timer >= 367) {
        if (o->w < 0x30) {
            o->w += 2;
        }
    }
    if (g->timer < 447) {
        o->c0[3] = 0xC0;
    } else {
        if (o->c0[3] > 6) {
            o->c0[3] -= 5;
        } else {
            o->state = 0;
        }
        if (o->h38 > 0) {
            o->h38--;
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xF0, 0x40, 0x40);
    } else {
        func_001076F0(o->c0, 0xF0, 0xF0, 0x40);
    }
    b116_01E00080(&g->trail[o->row][0x31], 0x32, 0, &g->pts[o->row]);
    if (g->timer >= 367) {
        o->t++;
    }
    return 0;
}

/* shape b116:01E03360, 214 insns: one of five scene markers (0x30 = its slot): size 32 (slot 0) or 13, grey 0x80,
   fades in by 10 for 12 ticks, out by 7 once the scene timer passes 455; flickers 0x80 / 0x60 on odd / even ticks
   (before it starts, in step with the scene timer's parity); from tick 13 to 42 moves its slot's scene point
   (ctx+0x2E20) a 30th of the gap between ctx+0x2D30 and ctx+0x2DD0 each tick; its clock starts at scene time 266
   (slot 0), 236 (1, 2) or 256 (3, 4); random rotation each tick */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 slot;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
} Mark_b116_01E03360;

typedef struct {
    u8 pad0[0x2D30];
    Vec4f to[10];
    Vec4f from[5];
    Vec4f at[5];
    u8 pad2E70[0x4A62 - 0x2E70];
    s16 timer;
} Scn_b116_01E03360;

static s32 func_01E03360_b116(Scn_b116_01E03360 *g, Mark_b116_01E03360 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->slot == 0) {
            o->size = 0x20;
        } else {
            o->size = 13;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 10;
        }
    } else if (g->timer > 455) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    if (o->tick > 12 && o->tick < 43) {
        g->at[o->slot].x += (g->to[o->slot].x - g->from[o->slot].x) / 30.0f;
        g->at[o->slot].y += (g->to[o->slot].y - g->from[o->slot].y) / 30.0f;
        g->at[o->slot].z += (g->to[o->slot].z - g->from[o->slot].z) / 30.0f;
    }
    if (o->tick == 0) {
        if (g->timer % 2 == o->slot % 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else {
            func_001076F0(o->col, 0x60, 0x60, 0x60);
        }
    }
    if (g->timer > 200) {
        if (g->timer > 265 && o->slot == 0) {
            o->tick++;
        }
        if (g->timer > 235 && o->slot == 1) {
            o->tick++;
        }
        if (g->timer > 235 && o->slot == 2) {
            o->tick++;
        }
        if (g->timer > 255 && o->slot == 3) {
            o->tick++;
        }
        if (g->timer > 255 && o->slot == 4) {
            o->tick++;
        }
    }
    func_00205C40((s32)o->rot);
    return 0;
}

/* shape b116:01E036C0, 108 insns: on start 0x38 = 50, both colours 0x80 grey (second alpha 0), 0x8/0xA = 100/200, 0xE
   = 1 when 0x3A is set, 0x18 = 0 for kind 1, 0x10 = 0x4000; both alphas grow by 10 for 12 ticks, then once the game
   step 0x4A62 reaches 0x147 they fade by 13 (the first ends it); after tick 20 0x10 winds down by 0x200 to 0 */

typedef struct {
    u8 pad0[0x4A62];
    s16 step;
} Game_b116_01E036C0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b116_01E036C0;

static s32 func_01E036C0_b116(Game_b116_01E036C0 *g, Fx_b116_01E036C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->f8 = 100;
        o->fA = 200;
        if (o->f3A == 0) {
            o->fE = 0;
        } else {
            o->fE = 1;
        }
        o->mode = 2;
        if (o->kind == 1) {
            o->w18 = 0;
        }
        o->w10 = 0x4000;
        o->col2[3] = 0;
    }
    if (o->tick < 12) {
        o->col[3] += 10;
        o->col2[3] += 10;
    } else if (g->step >= 0x147) {
        if (o->col[3] > 0xE) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xE) {
            o->col2[3] -= 13;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->kind == 0) {
        if (o->tick > 0x14) {
            if (o->w10 > 0) {
                o->w10 -= 0x200;
            } else {
                o->w10 = 0;
            }
        }
    } else if (o->tick > 0x14) {
        if (o->w10 > 0) {
            o->w10 -= 0x200;
        } else {
            o->w10 = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b116:01E03870, 74 insns: a white two-colour glow (size 185, 200 x 200, mirrored when it has an angle): in by 7 for 18 ticks; out by 13 once the scene value reaches 327, and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[8];
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b116_01E03870;

typedef struct {
    u8 pad[0x4A62];
    s16 val;
} Game_b116_01E03870;

static s32 func_01E03870_b116(Game_b116_01E03870 *g, Glow_b116_01E03870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->used == 1) {
        o->f38 = 185;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->h8 = 200;
        o->hA = 200;
        if (o->ang == 0) {
            o->hE = 0;
        } else {
            o->hE = 1;
        }
        o->used = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 18) {
        o->col[3] += 7;
        o->col2[3] += 7;
    } else if (g->val >= 327) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->used = 0;
        }
        if (o->col2[3] > 14) {
            o->col2[3] -= 13;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b116:01E039A0, 62 insns: a white-green burst (b116:01E03D70 shape): frame 5 rising by 10, its h6 trailing 5
   behind; alpha up by 0x60 for 2 frames, then down by 10 until it ends; x turn a quarter */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E039A0;

static s32 func_01E039A0_b116(void *arg0, Obj_b116_01E039A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 5;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->rot = 0x4000;
    o->h6 = o->h38 - 5;
    o->h38 += 0xA;
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b116_01E03AA0;

static s32 func_01E03AA0_b116(s32 unused, Obj_b116_01E03AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->h36 == 1) {
        if (o->h30 == 0) {
            o->h38 = 500;
            func_001076F0(o->c28, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c2C, 0xF0, 0x80, 0x10);
        } else if (o->h30 == 1) {
            o->h38 = 210;
            func_001076F0(o->c2C, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c28, 0xF0, 0x80, 0x10);
        }
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
        o->c2C[3] = 0;
    }
    if (o->h32 < 12) {
        if (o->h30 == 0) {
            if (o->c28[3] < 0xC0) {
                o->c28[3] += 0x18;
            }
        }
        if (o->h30 == 1) {
            if (o->c28[3] < 0xC0) {
                o->c2C[3] += 0x18;
            }
        }
    } else {
        if (o->h30 == 0) {
            if (o->c28[3] > 10) {
                o->c28[3] -= 9;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h30 == 1) {
            if (o->c2C[3] > 10) {
                o->c2C[3] -= 9;
            } else {
                o->h36 = 0;
            }
        }
    }
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->h32++;
    return 0;
}

/* shape b116:01E03C60, 67 insns: a white-green spinning burst (b116:01E03D70 shape): frame 40, random angle; alpha up by
   0x60 for 2 frames, then once the game timer passes 0x1B4 down by 9 until it ends; random turn plus a quarter */

typedef struct {
    u8 pad0[0x4A62];
    s16 timer;
} Game_b116_01E03C60;

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E03C60;

static s32 func_01E03C60_b116(Game_b116_01E03C60 *g, Obj_b116_01E03C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (g->timer > 0x1B4) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b116:01E03D70, 59 insns: a white-green spinning burst: set up once (frame 100, random angle), alpha up by 0x60
   for 2 frames, then down by 10 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b116_01E03D70;

static s32 func_01E03D70_b116(void *arg0, Obj_b116_01E03D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x64;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x60;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b116:01E03E60, 92 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 70, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x44A0 is 1 */

typedef struct {
    u8 pad0[0x4470];
    f32 l0[4];
    f32 pos[3];
    u8 pad448C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad449C[0x4];
    s32 state;
} Scene_b116_01E03E60;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b116_01E03E60;

static s32 func_01E03E60_b116(Scene_b116_01E03E60 *g, Obj_b116_01E03E60 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 0.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 2.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 70.0f;
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

/* shape b116:01E03FD0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x44A0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x44A0];
    s32 state;
} Game_b116_01E03FD0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b116_01E03FD0;

static s32 func_01E03FD0_b116(Game_b116_01E03FD0 *g, Fade_b116_01E03FD0 *o) {
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

/* shape b003:01E023F0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E06A00_b116;
extern f32 D_01E06A08_b116;

static s32 func_01E04090_b116(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E06A00_b116;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E06A08_b116;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
    return 0;
}

/* shape b116:01E040E0, 132 insns: b555:01E02CB0 with the scene packet at ctx+0x4A18; while fading the zoom f8 grows 7 per tick */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b116_01E040E0;

typedef struct {
    f32 s, t;
    Xyz_b116_01E040E0 p;
} Tv_b116_01E040E0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b116_01E040E0 v[2];
} Tex_b116_01E040E0;

typedef struct {
    u8 pad[0x4A18];
    Tex_b116_01E040E0 *pk;
} Game_b116_01E040E0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b116_01E040E0;

static s32 func_01E040E0_b116(Game_b116_01E040E0 *g, Fx_b116_01E040E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
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
    g->pk->v[0].s = f / 1024.0f;
    g->pk->v[0].t = f / 512.0f;
    g->pk->v[1].s = (640.0f - f) / 1024.0f;
    g->pk->v[1].t = (448.0f - f) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 29) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        o->f8 += 7;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E042F0_b116);

/* shape b116:01E05410, 72 insns: twin of b046:01E03E20: take the first free slot of the 170-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x4A5C and the two arguments; returns 1 if a
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
} Slot_b116_01E05410;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b116_01E05410 s[170];
    u8 pad2D20[0x1784];
    u8 r, g, b, a;
    u8 pad44A8[0x5B4];
    s16 v;
} Pool_b116_01E05410;

static s32 func_01E05410_b116(Pool_b116_01E05410 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b116_01E05410 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 170; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 170;
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

/* shape b116:01E05530, 226 insns: b233:01E01BC0's four quads (one colour, scale 0.1, turned by the effect's own
   rotation): each quad has its corners swapped in x and is shifted by +-pts[0].x / +-pts[0].y into its quadrant;
   far z */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b116_01E05530;

typedef struct {
    Rgbaq_b116_01E05530 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b116_01E05530;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b116_01E05530 v[4];
    u8 tail[0x20];
} Pkt_b116_01E05530;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b116_01E05530;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[4];
    u8 rot[0x18];
    u8 col[4];
    u8 colA[4];
    s16 point;
    u8 pad32[6];
    s16 size;
    s16 rz;
} Fx_b116_01E05530;

static void func_01E05530_b116(Obj_b116_01E05530 *o, Fx_b116_01E05530 *fx, Pkt_b116_01E05530 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b116_01E05530 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00107070(void *, s32, f32);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    f32 sw;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->col);
    p->v[1].c = func_00107740(fx->col);
    p->v[2].c = func_00107740(fx->col);
    p->v[3].c = func_00107740(fx->col);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, fx->rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->size, fx->size, i);
        sw = quad[0].x;
        quad[0].x = quad[1].x;
        quad[1].x = sw;
        sw = quad[2].x;
        quad[2].x = quad[3].x;
        quad[3].x = sw;
        if (i == 0) {
            func_00107070(quad, 0, -o->pts[0].x);
            func_00107070(quad, 1, o->pts[0].y);
        } else if (i == 1) {
            func_00107070(quad, 0, o->pts[0].x);
            func_00107070(quad, 1, o->pts[0].y);
        } else if (i == 2) {
            func_00107070(quad, 0, -o->pts[0].x);
            func_00107070(quad, 1, -o->pts[0].y);
        } else if (i == 3) {
            func_00107070(quad, 0, o->pts[0].x);
            func_00107070(quad, 1, -o->pts[0].y);
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b116:01E058C0, 271 insns: draws a sprite and its mirror image (two passes) at the given position: colour
   from the object, texture corners from the owner's rectangle (0x94, in 256ths, flipped sideways when the object's
   0x30 is set), world matrix scale 0.1 with the object's rotation; the second pass mirrors the quad (y negated,
   corners swapped) and the offset (owner 0x20/0x24) is applied with the signs of the pass and the flip */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b116_01E058C0;

typedef struct {
    Rgbaq_b116_01E058C0 c;
    f32 s, t;
    u64 xyz;
} Vtx_b116_01E058C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b116_01E058C0 v[4];
} Pkt_b116_01E058C0;

typedef struct {
    u8 pad0[0x20];
    f32 ox;
    f32 oy;
    u8 pad28[0x58];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
} Self_b116_01E058C0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 flip;
} Obj_b116_01E058C0;

static void func_01E058C0_b116(Self_b116_01E058C0 *self, Obj_b116_01E058C0 *obj, Pkt_b116_01E058C0 *pk, Vec4f *at) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b116_01E058C0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_002058D0(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f pos;
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    f32 a;
    f32 b;
    f32 c;
    s16 i;

    pos = *at;
    func_00109270(pk, 0, 0);
    pk->v[0].c = func_00107740(obj->col);
    pk->v[1].c = func_00107740(obj->col);
    pk->v[2].c = func_00107740(obj->col);
    pk->v[3].c = func_00107740(obj->col);
    pk->count &= ~0x800;
    func_00208700(pk, self->texture, 1);
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, obj->rot, &t);
    for (i = 0; i < 2; i++) {
        if (obj->flip == 0) {
            pk->v[0].s = pk->v[2].s = self->u / 256.0f;
            pk->v[1].s = pk->v[3].s = (self->u + self->w) / 256.0f;
            pk->v[0].t = pk->v[1].t = self->v / 256.0f;
            pk->v[2].t = pk->v[3].t = (self->v + self->h) / 256.0f;
        } else {
            pk->v[0].s = pk->v[2].s = (self->u + self->w) / 256.0f;
            pk->v[1].s = pk->v[3].s = self->u / 256.0f;
            pk->v[0].t = pk->v[1].t = self->v / 256.0f;
            pk->v[2].t = pk->v[3].t = (self->v + self->h) / 256.0f;
        }
        func_00108CE0(quad, obj->w, obj->h);
        quad[2].y = quad[3].y = 0.0f;
        if (i == 1) {
            quad[0].y = quad[1].y *= -1.0f;
            a = quad[0].x;
            b = quad[2].x;
            c = quad[3].x;
            quad[0].x = quad[1].x;
            quad[1].x = a;
            quad[2].x = c;
            quad[3].x = b;
        }
        if (obj->flip == 0) {
            if (i == 0) {
                func_00107070(quad, 0, self->ox);
                func_00107070(quad, 1, self->oy);
            } else if (i == 1) {
                func_00107070(quad, 0, -self->ox);
                func_00107070(quad, 1, -self->oy);
            }
        } else if (i == 0) {
            func_00107070(quad, 0, -self->ox);
            func_00107070(quad, 1, self->oy);
        } else if (i == 1) {
            func_00107070(quad, 0, self->ox);
            func_00107070(quad, 1, -self->oy);
        }
        if (func_002058D0(quad, 0x70000000, m, pk, depth) != 0) {
            func_002075F0(pk, self->ot, (u32)depth[0]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b116", func_01E05D00_b116);

/* OVL_WARM */

/* shape b116:01E06870, 79 insns: the module's draw pass (b593:01E039C0 shape): opens a sprite packet on the stack, then runs every
   live slot (170 of 0x40 bytes) whose handler is shape b116:01E040E0 through it; queues the batch at the scene depth - 2000
   if any slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b116_01E06870;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b116_01E06870 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b116_01E06870;

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 active;
    u8 pad38[8];
} Slot_b116_01E06870;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b116_01E06870 slot[170];
    u8 padEnd[0x4A14 - 0x2A0 - 170 * 0x40];
    s32 ctx;
    Pkt_b116_01E06870 *pkt;
    f32 depth;
} Scene_b116_01E06870;

static void func_01E06870_b116(Scene_b116_01E06870 *s) {
    extern void b116_01E040E0(Scene_b116_01E06870 *, Slot_b116_01E06870 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b116_01E06870 pkt __attribute__((aligned(8)));
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
    for (i = 0; i < 170; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b116_01E040E0) {
                b116_01E040E0(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), (u32)(s->depth - 2000.0f));
    }
}
