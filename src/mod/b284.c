#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b284(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b284(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b008_01E004D0;

static void func_01E009F0_b284(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
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
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00150_b284((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
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

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

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
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E00F70_b284(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00150_b284((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b284:01E014D0, 83 insns: sets the scene colour to red 0x80 and counts its timer; on frames 0x47..0x112 spawns one
   b284:01E01D30 and one b284:01E01620 effect at the model joint, and on frames 0x43..0x112 one b284:01E019A0 (b566:01E014D0
   family) */

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x3754 - 0x25C];
    u8 r, g, b, a;
    u8 pad3758[0x24];
    s16 joint;
    u8 pad377E[0x1A];
    s16 t;
} Scene_b284_01E014D0;

static void func_01E014D0_b284(Scene_b284_01E014D0 *s) {
    extern void b284_01E01620(void);
    extern void b284_01E019A0(void);
    extern void b284_01E01D30(void);
    extern s32 b284_01E02C90(Scene_b284_01E014D0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    s32 i;

    s->r = 0x80;
    s->g = 0;
    s->b = 0;
    s->a = 0;
    s->t++;
    if (s->t > 0x46 && s->t < 0x113) {
        func_001F5620(func_001F53A0(), s->joint, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        for (i = 0; i < 1; i++) {
            b284_01E02C90(s, b284_01E01D30, 0);
        }
        for (i = 0; i < 1; i++) {
            b284_01E02C90(s, b284_01E01620, 0);
        }
    }
    if (s->t > 0x42 && s->t < 0x113) {
        func_001F5620(func_001F53A0(), s->joint, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        for (i = 0; i < 1; i++) {
            b284_01E02C90(s, b284_01E019A0, 0);
        }
    }
}

/* shape b284:01E01620, 217 insns: b566:01E015D0 cousin, dark red (0x70/0x10/0x10) puff of size 40 (growing 1, then 3
   after tick 24), frame 0 or 1 up to 5, speed 5..9, h8 0..24, hold 26..35; alpha up by 0x60 to 0xC0 while the scene
   count (0x3798) is under 300, then down by 9; sinks toward the second point by 1/25 of the gap (1/45 after tick 24);
   every other tick slides by hC */

typedef struct {
    u8 pad0[0x3798];
    s16 count;
} Ctx_b284_01E01620;

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b284_01E01620;

static s32 func_01E01620_b284(Ctx_b284_01E01620 *g, Fx_b284_01E01620 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 40;
        o->f34 = (func_0019A5C8() >> 4) % 2;
        func_001076F0(o->col, 0x70, 0x10, 0x10);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 26;
        o->hC = 0;
        o->mode = 2;
    }
    if (g->count < 300) {
        if (o->tick < o->hold) {
            if (o->col[3] <= 0x60) {
                o->col[3] += 0x60;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    *(f32 *)(u32)&v[2] -= v[6];
    if (o->tick < 24) {
        *(f32 *)(u32)&v[2] /= 25.0f;
        o->z = o->z + v[2];
        o->f38 += 1;
    } else {
        *(f32 *)(u32)&v[2] /= 45.0f;
        o->z = o->z + v[2];
        o->f38 += 3;
    }
    if (o->tick % 2 == 1) {
        o->x += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01990_b284(void) {
    return 0;
}

/* shape b284:01E019A0, 228 insns: b297:01E011F0's glow in violet (0x80, 0x20, 0xFF), size 12..23 growing by 2 to
   60 (and by 1 every third tick), rise 3..7, held 10..19 ticks fading in by 0x80 while the scene count ctx+0x3798 is
   under 300, then out by 7 (by 9 past 300); joints ctx+0x377C/0x377E; depth drift /100 after the first tick */

typedef struct {
    u8 pad0[0x377C];
    s16 ja;
    s16 jb;
    u8 pad3780[0x18];
    s16 count;
} Game_b284_01E019A0;

typedef struct {
    u8 pad0[4];
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
} Glow_b284_01E019A0;

static s32 func_01E019A0_b284(Game_b284_01E019A0 *g, Glow_b284_01E019A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 12;
        o->kind = (func_0019A5C8() >> 4) % 2;
        func_001076F0(o->col, 0x80, 0x20, 0xFF);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 3;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 10 + 10;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, (Vec4f *)(u32)&v[1]);
        o->hC = func_001A22C0(((Vec4f *)(u32)&v[1])->x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 300) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x80;
            }
        }
    } else if (g->count < 300) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 300) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
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
        *(f32 *)(u32)&v[0].z /= 100.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->h30 += o->hE;
    if (o->tick % 3 == 1) {
        o->f38++;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b284:01E01D30, 228 insns: b284:01E019A0's violet glow held 32..56 ticks, depth drift /40, growing by 1 on
   odd ticks */

typedef struct {
    u8 pad0[0x377C];
    s16 ja;
    s16 jb;
    u8 pad3780[0x18];
    s16 count;
} Game_b284_01E01D30;

typedef struct {
    u8 pad0[4];
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
} Glow_b284_01E01D30;

static s32 func_01E01D30_b284(Game_b284_01E01D30 *g, Glow_b284_01E01D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 12;
        o->kind = (func_0019A5C8() >> 4) % 2;
        func_001076F0(o->col, 0x80, 0x20, 0xFF);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 3;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 25 + 32;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, (Vec4f *)(u32)&v[1]);
        o->hC = func_001A22C0(((Vec4f *)(u32)&v[1])->x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 300) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x80;
            }
        }
    } else if (g->count < 300) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 300) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
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
        *(f32 *)(u32)&v[0].z /= 40.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->h30 += o->hE;
    if (o->tick % 2 == 1) {
        o->f38++;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b284:01E020C0, 91 insns, 2 copies: a scene light flash: sets the scene's light block once (colour 4,4,4, range 70,
   at the object's position), its strength rises by 0.2 to 1 then falls by 0.1; the light is switched off when
   the flash ends or the scene says so */

typedef struct {
    s32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 range;
    f32 strength;
} Light_b284_01E020C0;

typedef struct {
    u8 pad0[0x3510];
    Light_b284_01E020C0 light;
    u8 pad353C[0x214];
    s32 w3750;
} World_b284_01E020C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 falling;
    u8 pad32[4];
    s16 state;
} Flash_b284_01E020C0;

static s32 func_01E020C0_b284(World_b284_01E020C0 *w, Flash_b284_01E020C0 *o) {
    extern void func_001F6C10(void *);

    if (o->state == 1) {
        w->light.w0 = 0;
        w->light.b = w->light.g = w->light.r = 4.0f;
        w->light.w20 = 0;
        w->light.range = 70.0f;
        w->light.strength = 0.0f;
        w->light.x = o->x;
        w->light.y = o->y;
        w->light.z = o->z;
        o->state = 2;
        o->falling = 0;
    }
    if (o->falling == 0) {
        if (w->light.strength < 1.0f) {
            w->light.strength += 0.2f;
        } else {
            o->falling = 1;
        }
    } else if (w->light.strength > 0.1f) {
        w->light.strength -= 0.1f;
    } else {
        o->state = 0;
    }
    if (o->state == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&w->light);
    }
    if (w->w3750 == 1) {
        o->state = 0;
    }
    return 0;
}

/* shape b284:01E02230, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3750 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3750];
    s32 state;
} Game_b284_01E02230;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b284_01E02230;

static s32 func_01E02230_b284(Game_b284_01E02230 *g, Fade_b284_01E02230 *o) {
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

static s32 func_01E022F0_b284(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b284;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b284;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b284:01E02340, 103 insns: a grey full-screen veil (b081:01E044C0 shape): one sprite over the whole screen at the object
   alpha, sent at once; alpha 0x68 while the scene timer is under 300, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b284_01E02340;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b284_01E02340 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b284_01E02340;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b284_01E02340;

typedef struct {
    u8 pad0[0x3798];
    s16 timer;
} Scene_b284_01E02340;

static s32 func_01E02340_b284(Scene_b284_01E02340 *g, Obj_b284_01E02340 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b284_01E02340 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->c0[3] = 0;
        o->state = 2;
    }
    ((Pkt_b284_01E02340 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b284_01E02340 *)(s32)&pkt)->tag = 5;
    ((Pkt_b284_01E02340 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b284_01E02340 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x80;
    pkt.b = 0x80;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b284_01E02340 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (g->timer < 0x12C) {
        o->c0[3] = 0x68;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b284:01E024E0 (b284), 492 insns, 1 copy: scene manager in b566:01E02760 form: setup loads 5 models, 3
   textures and a random table; else steps 7 handlers over 200 nodes and draws 4 kinds, returns a cue by timer */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x1E];
    void *fn;
    u8 pad28[0xA];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Node_b284_01E024E0;

typedef struct {
    u8 pad0[0x20];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x80 - 0x2C];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0[8];
    u8 padD0[8];
    u8 camD8[0x1B8];
    u8 pad290[0x20];
    s32 tex[16];
    Node_b284_01E024E0 node[200];
    s32 tex5[3];
    u8 pad34FC[0x3560 - 0x34FC];
    Vec4f pt[9];
    u8 trail[0x3750 - 0x35F0];
    s32 count;
    u8 pad3754[8];
    s32 ot;
    u8 pad3760[0x1C];
    s16 model[5];
    u8 pad3786[0x10];
    s16 id;
    s16 timer;
    s8 rnd[256];
    u8 pad389A[0x102];
    u8 cam[0x174];
} Scene_b284_01E024E0;

static s32 func_01E024E0_b284(s32 arg0, s32 id) {
    Scene_b284_01E024E0 *g = (Scene_b284_01E024E0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E014D0_b284();
    extern void func_01E00080_b284();
    extern void func_01E009F0_b284();
    extern void func_01E00F70_b284();
    extern s32 func_01E01620_b284();
    extern s32 func_01E01990_b284();
    extern s32 func_01E019A0_b284();
    extern s32 func_01E01D30_b284();
    extern s32 func_01E020C0_b284();
    extern s32 func_01E02230_b284();
    extern s32 func_01E022F0_b284();
    extern s32 func_01E02340_b284();
    s32 n;
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Vec4f r4;
    Vec4f t;
    f32 b;
    f32 a;
    s32 i;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3B10);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 339;
        g->model[0] = func_001F5560(func_001F53A0(), 0x1C, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x3A, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x40, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x47, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x4E, 0);
        for (i = 0; i < 3; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E014D0_b284(g, 0);
    if (g->timer == 1) {
        Vec4f *p = g->pt;
        func_001F5620(func_001F53A0(), g->model[0], (s32)&t);
        for (i = 0; i < 9; i++, p++) {
            p->x = t.x;
            p->y = t.y;
            p->z = t.z;
        }
    }
    func_01E00080_b284(g->trail, 10, g->model[0]);
    for (i = 0; i < 200; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E01620_b284) {
                func_01E01620_b284(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E019A0_b284) {
                func_01E019A0_b284(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01D30_b284) {
                func_01E01D30_b284(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E020C0_b284) {
                func_01E020C0_b284(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E02230_b284) {
                func_01E02230_b284(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E022F0_b284) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b284;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b284;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
            if (g->node[i].fn == func_01E02340_b284) {
                func_01E02340_b284(g, &g->node[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 200; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E01620_b284) {
                g->tex88 = g->tex5[2];
                func_00106080(&r1, 0x14, g->node[i].h34, 0);
                g->rect = r1;
                g->hB8 = 3;
                g->hBE = (func_0019A5C8() >> 4) % 4;
                g->hC0[0] = (func_0019A5C8() >> 4) % 4;
                func_01E009F0_b284(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E01990_b284) {
                g->tex88 = g->tex5[2];
                func_00106080(&r2, 0x14, g->node[i].h34, 0);
                g->rect = r2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                func_01E009F0_b284(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E019A0_b284) {
                g->tex88 = g->tex5[2];
                g->px = g->node[i].x;
                g->py = g->node[i].y;
                g->pz = g->node[i].z;
                func_00106080(&r3, 0x14, g->node[i].h34, 0);
                g->rect = r3;
                if (g->node[i].h32 > 3) {
                    g->hB8 = 3;
                    g->hBE = (func_0019A5C8() >> 4) % 4;
                    g->hC0[0] = (func_0019A5C8() >> 4) % 4;
                    g->px = g->node[i].x;
                    g->py = g->node[i].y;
                    g->pz = g->node[i].z;
                    func_01E00F70_b284(g, &g->node[i], 0x20, g->rnd);
                    g->hB8 = 0;
                }
            }
            if (g->node[i].fn == func_01E01D30_b284) {
                g->tex88 = g->tex5[2];
                g->px = g->node[i].x;
                g->py = g->node[i].y;
                g->pz = g->node[i].z;
                func_00106080(&r4, 0x14, g->node[i].h34, 0);
                g->rect = r4;
                if (g->node[i].h32 > 3) {
                    g->hB8 = 3;
                    g->hBE = (func_0019A5C8() >> 4) % 4;
                    g->hC0[0] = (func_0019A5C8() >> 4) % 4;
                    g->px = g->node[i].x;
                    g->py = g->node[i].y;
                    g->pz = g->node[i].z;
                    func_01E00F70_b284(g, &g->node[i], 0x20, g->rnd);
                    g->hB8 = 0;
                }
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 60) {
        return 1;
    }
    if (g->timer == 320) {
        return 4;
    }
    if (g->timer == 300) {
        return 2;
    }
    if (g->timer > 70 && g->timer < 295) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b284:01E02C90, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3794 and the two arguments; returns 1 if a
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
} Slot_b284_01E02C90;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b284_01E02C90 s[200];
    u8 pad34F0[0x264];
    u8 r, g, b, a;
    u8 pad3758[0x3C];
    s16 v;
} Pool_b284_01E02C90;

static s32 func_01E02C90_b284(Pool_b284_01E02C90 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b284_01E02C90 *s = NULL;
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
