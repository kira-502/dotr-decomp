#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b847(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
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

static void func_01E00110_b847(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E009B0_b847(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
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

static void func_01E00B00_b847(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b847", func_01E00E60_b847);

/* shape b594:01E00920, 368 insns, 2 copies (b445:01E00D10 twin, two-axis turn): draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b594_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b594_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b594_01E00920;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b594_01E00920;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f pos;
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 w50;
    u8 pad52[8];
    s16 axis;
    s16 axis2;
    u8 pad5E[2];
    u8 col[4];
} Spr_b594_01E00920;

static void func_01E019B0_b847(Obj_b594_01E00920 *o, Spr_b594_01E00920 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b594_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f e;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b594_01E00920 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b594_01E00920 *p;
    u8 mode;

    p = (Pkt_b594_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00110_b847((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    p2.x = s->pos.x;
    p2.y = s->pos.y;
    p2.z = s->pos.z;
    if (o->kind == 0) {
        func_00108EF0(m, &o->scale, NULL, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    ax[0] = s->axis2;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00110_b847((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
            func_00108CE0(quad, s->size, s->size);
            func_00109100(quad, rot, 1, o->xD8);
            func_00109100(quad, rot, 0, o->xD8);
        } else if (o->kind == 1) {
            func_00108CE0(quad, s->size, s->size);
        }
        for (c = 0; c < 3; c++) {
            if (c == 0) {
                off = 0;
            }
            if (c == 1) {
                off = 100;
            }
            if (c == 2) {
                off = 180;
            }
            f = (tbl + i)[s->off + off];
            f /= 20.0f;
            u = f * (f32)(s->w50 + (i >> 1));
            if (c == 0) {
                e.x = u;
            }
            if (c == 1) {
                e.y = u;
            }
            if (c == 2) {
                e.z = u;
            }
        }
        if (o->kind == 0) {
            func_00108950(&e, ax, 0, o->xD8);
            func_00108950(&e, ax, 1, o->xD8);
        }
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (o->kind == 1) {
            quad[0].y = 0.0f;
            quad[1].y = 0.0f;
            quad[0].x = s->size;
            quad[1].x = -s->size;
            quad[0].z = 0.0f;
            quad[1].z = 0.0f;
        }
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

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E01F70_b847(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b847", func_01E02370_b847);

/* shape b847:01E02D30, 1025 insns: B847_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0xD6EC);
   frames 72..160 look up joint pairs and spawn 0x1E042E0 bursts / 0x1E04C90 on them; the mark (0xD570) follows joint
   0xD666 until 542, then glides toward the camera joint 0xD674 until 652; frames 380..500 a fan of 36 0x1E03F80 pairs
   (angle by the flag 0xD6E8), 0x1E05460 / 0x1E04E60 on an 80-step ring (0xD6D4), 0x1E03D40 / 0x1E046A0 / 0x1E05B20 /
   0x1E05DC0 on the mark over 520..780; frame 250 twelve 0x1E04820; the sway (0xD650) is 20 x the sine of the spin */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xD570 - 0x260];
    Vec4f mark;
    Vec4f mark2;
    u8 padD590[0xD5C0 - 0xD590];
    Vec4f copy;
    u8 padD5D0[0xD5F0 - 0xD5D0];
    Vec4f vel;
    u8 padD600[0xD648 - 0xD600];
    f32 grow;
    f32 zoff;
    f32 sway;
    u8 padD654[0xD664 - 0xD654];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 padD66A[0xD674 - 0xD66A];
    s16 jcam;
    u8 padD676[0xD6CE - 0xD676];
    s16 cnt;
    s16 ang;
    u8 padD6D2[2];
    s16 ring;
    u8 padD6D6[0xD6DE - 0xD6D6];
    s16 spin;
    u8 padD6E0[4];
    s16 side;
    u8 padD6E6[2];
    s16 flag;
    u8 padD6EA[2];
    s16 t;
    u8 padD6EE[0xD8F0 - 0xD6EE];
    u8 trig[1];
} Scene_b847_01E02D30;

static void func_01E02D30_b847(Scene_b847_01E02D30 *g) {
    extern void b847_01E042E0(void);
    extern void b847_01E03D40(void);
    extern void b847_01E03F80(void);
    extern void b847_01E046A0(void);
    extern void b847_01E04820(void);
    extern void b847_01E04A90(void);
    extern void b847_01E04C90(void);
    extern void b847_01E04E60(void);
    extern void b847_01E05460(void);
    extern void b847_01E05B20(void);
    extern void b847_01E05D00(void);
    extern void b847_01E05DC0(void);
    extern void b847_01E05FB0(void);
    extern void b847_01E06E00(Scene_b847_01E02D30 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v[2];
    s16 i;

    g->t++;
    if (g->t == 72) {
        g->ja = func_001F5560(func_001F53A0(), 9, 1);
        g->jb = func_001F5560(func_001F53A0(), 18, 0);
    }
    if (g->t == 74) {
        g->ja = func_001F5560(func_001F53A0(), 10, 1);
        g->jb = func_001F5560(func_001F53A0(), 19, 0);
    }
    if (g->t == 90) {
        g->ja = func_001F5560(func_001F53A0(), 4, 1);
        g->jb = func_001F5560(func_001F53A0(), 23, 0);
    }
    if (g->t == 108) {
        g->ja = func_001F5560(func_001F53A0(), 6, 1);
        g->jb = func_001F5560(func_001F53A0(), 24, 0);
    }
    if (g->t == 73 || g->t == 84 || g->t == 99 || g->t == 109) {
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        g->side = 1;
        for (i = 0; i < 10; i++) {
            b847_01E06E00(g, b847_01E042E0, 0);
        }
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        g->side = 1;
        for (i = 0; i < 10; i++) {
            b847_01E06E00(g, b847_01E042E0, 0);
        }
    }
    if (g->t == 124) {
        g->ja = func_001F5560(func_001F53A0(), 16, 1);
    }
    if (g->t >= 125 && g->t < 149) {
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        g->pos.y -= 4.5f;
        g->side = 0;
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
    }
    if (g->t == 160) {
        g->ja = func_001F5560(func_001F53A0(), 1, 1);
        g->jb = func_001F5560(func_001F53A0(), 29, 0);
        g->jc = func_001F5560(func_001F53A0(), 30, 0);
    }
    if (g->t < 543) {
        func_001F5620(func_001F53A0(), g->jb, &g->mark);
        func_001F5620(func_001F53A0(), g->jb, &g->mark2);
    } else {
        if (g->t == 543) {
            func_001F5620(func_001F5380(), g->jcam, v);
            func_001F5F90(func_001F5380(), v);
            g->vel.z = (v[0].z - g->mark.z) / 115.0f;
            func_001F5620(func_001F5380(), g->jcam, v);
            g->vel.y = (v[0].y - g->mark.y) / 120.0f;
            g->vel.x = (v[0].x - g->mark.x) / 120.0f;
        }
        if (g->t < 653) {
            g->mark.z += g->vel.z;
            g->mark.y += g->vel.y;
            g->mark.x += g->vel.x;
        }
    }
    if (g->t >= 380 && g->t < 501 && g->t % 3 == 1 && g->cnt < 36) {
        if (g->flag != 0) {
            g->ang = g->cnt * -10;
        } else {
            g->ang = g->cnt * 10 - 140;
        }
        g->side = g->cnt;
        b847_01E06E00(g, b847_01E03F80, 0);
        if (g->flag != 0) {
            g->ang = g->cnt * -10;
        } else {
            g->ang = g->cnt * 10 - 140;
        }
        g->side = g->cnt + 36;
        b847_01E06E00(g, b847_01E03F80, 0);
        g->cnt++;
    }
    if (g->t > 500 && g->t < 534) {
        for (i = 0; i < 3; i++) {
            g->side = g->ring;
            b847_01E06E00(g, b847_01E05460, 0);
            g->ring++;
            if (g->ring >= 80) {
                g->ring = 0;
            }
        }
    }
    if (g->t == 520) {
        g->side = 0;
        b847_01E06E00(g, b847_01E03D40, 0);
    }
    if (g->t >= 520 && g->t < 781 && g->t % 3 == 1) {
        g->side = 1;
        b847_01E06E00(g, b847_01E03D40, 0);
    }
    if (g->t >= 645 && g->t < 771 && g->t % 3 == 1) {
        g->pos = g->mark;
        if (g->flag != 0) {
            g->pos.z -= g->zoff;
        } else {
            g->pos.z += g->zoff;
        }
        b847_01E06E00(g, b847_01E046A0, 0);
        b847_01E06E00(g, b847_01E046A0, 0);
        g->side = 1;
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
        b847_01E06E00(g, b847_01E04C90, 0);
        for (i = 0; i < 7; i++) {
            g->side = g->ring;
            b847_01E06E00(g, b847_01E04E60, 0);
            g->ring++;
            if (g->ring >= 80) {
                g->ring = 0;
            }
        }
    }
    if (g->t >= 645 && g->t < 771 && g->t % 6 == 1) {
        b847_01E06E00(g, b847_01E05DC0, 0);
    }
    if (g->t >= 545 && g->t < 771 && g->t % 3 == 1) {
        g->pos = g->mark;
        if (g->flag != 0) {
            g->pos.z -= g->zoff;
        } else {
            g->pos.z += g->zoff;
        }
        b847_01E06E00(g, b847_01E05B20, 0);
        b847_01E06E00(g, b847_01E05B20, 0);
    }
    if (g->t >= 525) {
        if (g->grow < 120.0f) {
            g->grow += 3.5f;
        }
    }
    if (g->t == 1) {
        g->side = 0;
    }
    if (g->t == 1) {
        b847_01E06E00(g, b847_01E05D00, 0);
    }
    if (g->t >= 380 && g->t < 501) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        g->side = 0;
        b847_01E06E00(g, b847_01E04820, 0);
    }
    if (g->t >= 152 && g->t < 159) {
        g->side = 1;
        b847_01E06E00(g, b847_01E05FB0, 0);
    }
    if (g->t == 250) {
        g->side = 4;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 5;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 6;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 7;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 8;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 9;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 10;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 11;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 12;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 13;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 14;
        b847_01E06E00(g, b847_01E04820, 0);
        g->side = 15;
        b847_01E06E00(g, b847_01E04820, 0);
    }
    if (g->t == 368) {
        b847_01E06E00(g, b847_01E04A90, 0);
    }
    if (g->t < 531) {
        g->copy = g->mark;
    }
    if (g->t >= 533 && g->t < 651) {
        g->spin += 18;
    }
    g->sway = 20.0f * func_00108030((s32)g->trig, g->spin, 0);
}

/* shape b847:01E03D40, 141 insns: a grey/purple ring at the scene height (g+0xD648 + g+0xD650): on start f48 0, grey 0x70
   and purple 0x80/0x40/0xFF; kind 0 holds 30 ticks at 70 above, kind 1 5 ticks at 20..59 above; the purple alpha rises
   by 10 (kind 0) or 80 (kind 1) to 0xA0 while held, then falls by 12 (kind 0 once the scene timer at g+0xD6EC passes 770);
   kind 0 follows the scene height; it spins by 0x4000 */

typedef struct {
    u8 pad0[0xD648];
    f32 za;
    u8 padD64C[4];
    f32 zc;
    u8 padD654[0x98];
    s16 timer;
} Game_b847_01E03D40;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    f32 h;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 hh;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b847_01E03D40;

static s32 func_01E03D40_b847(Game_b847_01E03D40 *g, Obj_b847_01E03D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x70, 0x70, 0x70);
        func_001076F0(o->c1, 0x80, 0x40, 0xFF);
        if (o->kind == 0) {
            o->hold = 30;
            o->h = 70.0f;
        } else if (o->kind == 1) {
            o->hold = 5;
            o->h = g->zc + (g->za + (20.0f + func_0019A5C8() % 40));
        }
        o->w = 10;
        o->hh = 10;
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->kind == 0) {
            if (o->c1[3] < 0xA0) {
                o->c1[3] += 10;
            }
        }
        if (o->kind == 1) {
            if (o->c1[3] < 0xA0) {
                o->c1[3] += 0x50;
            }
        }
    } else {
        if (o->kind == 0) {
            if (g->timer > 770) {
                if (o->c1[3] > 13) {
                    o->c1[3] -= 12;
                } else {
                    o->mode = 0;
                }
            }
        }
        if (o->kind == 1) {
            if (o->c1[3] > 13) {
                o->c1[3] -= 12;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        o->h = 70.0f + g->za + g->zc;
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b847:01E03F80, 215 insns: b733:01E02510 family white ring by slot (0x50: under 36 kind 0, under 72 kind 2,
   under 108 kind 4), f56 0..7, random spin direction h8 and speed hE 2..7, random f5C; both alphas up by 12 to 0xC0
   for 30 ticks, then down by 11 once the scene count (ctx+0xD6EC) passes 750; cycles h6 0..5 every 10 ticks; while the
   scene runs kind 0 is 25 wide (f48 3.5) and kind 2 14 wide (2.5); from count 514 the first two slot bands turn
   +0x100 / -0x100; it sits on the scene point (ctx+0xD570) until count 514; from count 501 it spins by hE */

typedef struct {
    u8 pad0[0xD570];
    Vec4f pt;
    u8 padD580[0xD6EC - 0xD580];
    s16 count;
} Game_b847_01E03F80;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    Vec4f pos;
    u8 pad20[8];
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 f50;
    s16 kind;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b847_01E03F80;

static s32 func_01E03F80_b847(Game_b847_01E03F80 *g, Fx_b847_01E03F80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 1.5f;
        o->f56 = func_0019A5C8() % 8;
        o->mode = 2;
        if (o->f50 < 36) {
            o->kind = 0;
        } else if (o->f50 < 72) {
            o->kind = 2;
        } else if (o->f50 < 108) {
            o->kind = 4;
        }
        o->h8 = (func_0019A5C8() >> 4) % 2;
        o->hE = (func_0019A5C8() >> 4) % 6 + 2;
        o->f5C = (func_0019A5C8() >> 4) % 360;
        o->h6 = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    }
    if (o->tick < 30) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 12;
        }
    } else if (g->count > 750) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 12) {
            o->col2[3] -= 11;
        }
    }
    if (o->tick >= 30) {
        if (o->tick % 10 == 1) {
            o->h6++;
            if (o->h6 > 5) {
                o->h6 = 0;
            }
        }
    }
    if (g->count != 0) {
        if (o->kind == 0) {
            o->f4C = 25.0f;
            o->f48 = 3.5f;
        } else if (o->kind == 1) {
        } else if (o->kind == 2) {
            o->f4C = 14.0f;
            o->f48 = 2.5f;
        }
    }
    if (g->count > 513) {
        if (o->f50 < 36) {
            o->w28 += 0x100;
        } else if (o->f50 < 72) {
            o->w28 -= 0x100;
        }
    }
    if (g->count < 515) {
        o->pos = g->pt;
    }
    if (g->count > 500) {
        if (o->h8 == 1) {
            o->f5C += o->hE;
        } else {
            o->f5C -= o->hE;
        }
    }
    o->tick++;
    return 0;
}

/* shape b847:01E042E0, 123 insns: on start size 5..14, variant 0..3, grey colour, y 10..29, a random turn (0x5A on frame 0,
   0x5C on frame 1), step 20..44, w 1..8, hold 13..22; alpha 0x80 while held, then fades by 0xB (ends below 0xD);
   frame++, y += step */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 y;
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 ang2;
    u8 pad5E[2];
    u8 c0[4];
} Obj_b847_01E042E0;

static s32 func_01E042E0_b847(void *arg0, Obj_b847_01E042E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 5;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 20 + 0xA;
        if (o->frame == 0) {
            o->ang = (func_0019A5C8() >> 4) % 360;
        }
        if (o->frame == 1) {
            o->ang2 = (func_0019A5C8() >> 4) % 360;
        }
        o->step = func_0019A5C8() % 25 + 0x14;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 10 + 0xD;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b847:01E044D0, 113 insns: a white spark (b631:01E01D30 family): size 4, sub-frame 4, a quarter turn one way or the other
   by the scene side, height 3..22 rising by 2..6, angle, width 0..29, hold 2..4; jumps to fading when the scene timer hits 60 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x10];
    s32 rot0;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b847_01E044D0;

typedef struct {
    u8 pad0[0xD6E8];
    s16 side;
    u8 padD6EA[2];
    s16 timer;
} Game_b847_01E044D0;

static s32 func_01E044D0_b847(Game_b847_01E044D0 *g, Obj_b847_01E044D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 4.0f;
        o->sub = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        if (g->side != 0) {
            o->rot0 = -0x4000;
        } else {
            o->rot0 = 0x4000;
        }
        o->y = func_0019A5C8() % 20 + 3;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 5 + 2;
        o->w = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (g->timer == 0x3C) {
        o->t = 0xA;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b847:01E046A0, 94 insns: b845:01E02570 twin: grey beam from 100 growing 55 a tick (tail 300 behind): alpha 0x80 for 13 ticks */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b847_01E046A0;

static s32 func_01E046A0_b847(s32 arg0, Obj_b847_01E046A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->h5A = 15;
        o->h5C = 15;
        o->f34 = 550.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 13) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 300.0f;
    o->w24 += 0x100;
    o->t++;
    return 0;
}

/* shape b847:01E04820, 155 insns: b849:01E029D0 family glow in two kinds: kind 0 grey/yellow, size 70, 5 ticks of alpha +53; kinds 1+ dark/yellow, size 100, 500 ticks of +13, placed (kind-1)/15 of the way from tracked point 0 to point 1 (ctx+0xD666/8); then down by 12; spins 0x4000 per tick */

typedef struct {
    u8 pad0[0xD666];
    s16 pt;
    s16 pt2;
} Game_b847_01E04820;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b847_01E04820;

static s32 func_01E04820_b847(Game_b847_01E04820 *g, Fx_b847_01E04820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    f32 f;
    Vec4f *pb;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (o->f50 == 0) {
            func_001076F0(o->col, 0x70, 0x70, 0x70);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x40);
            o->hold = 5;
            o->f4C = 70.0f;
        }
        if (o->f50 > 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x20);
            func_001076F0(o->col2, 0x80, 0x80, 0x20);
            o->hold = 500;
            o->f4C = 100.0f;
        }
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->f50 == 0) {
            if (o->col2[3] < 0xA0) {
                o->col2[3] += 0x35;
            }
        }
        if (o->f50 > 0) {
            if (o->col2[3] < 0xA0) {
                o->col2[3] += 0xD;
            }
        }
    } else if (o->col2[3] > 13) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->f50 > 0) {
        f = o->f50 - 1;
        func_001F5620(func_001F53A0(), g->pt, &o->pos);
        func_001F5620(func_001F53A0(), g->pt, &a);
        func_001F5620(func_001F53A0(), g->pt2, pb = &b);
        o->pos.x += f * ((pb->x - a.x) / 15.0f);
        o->pos.y += f * ((b.y - a.y) / 15.0f);
        o->pos.z += f * ((b.z - a.z) / 15.0f);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b847:01E04A90, 127 insns: b397:01E01540's yellow trail with 40 points: on start size 5 and both 40-point trails
   (g+0xCB70, g+0xCDF0) set to the joints at g+0xD666/0xD668; alpha 0xC0 for 200 ticks, then down by 9 until it ends;
   each tick both trails get the joints' new positions through the module's trail function */

typedef struct {
    f32 x, y, z, w;
} Pt_b847_01E04A90;

typedef struct {
    u8 pad0[0xCB70];
    Pt_b847_01E04A90 a[40];
    Pt_b847_01E04A90 b[40];
    u8 padD070[0x5F6];
    s16 ja;
    s16 jb;
} Scene_b847_01E04A90;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x40];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b847_01E04A90;

static s32 func_01E04A90_b847(Scene_b847_01E04A90 *g, Fx_b847_01E04A90 *o) {
    extern void b847_01E00080(Pt_b847_01E04A90 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    Pt_b847_01E04A90 *q;

    func_001076F0(o->col, 0xFF, 0xFF, 0x10);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        func_001F5620(func_001F53A0(), g->ja, p);
        q = g->a;
        for (i = 0; i < 40; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->b;
        for (j = 0; j < 40; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        o->mode = 2;
    }
    if (o->t < 200) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->ja, p);
    b847_01E00080(&g->a[39], 40, 0, p);
    func_001F5620(func_001F53A0(), g->jb, p);
    b847_01E00080(&g->b[39], 40, 0, p);
    o->h6 = 0x26;
    o->t++;
    return 0;
}

/* shape b847:01E04C90, 114 insns: a two-kind ring (kind 0 grey/green, height 200, random roll and tilt +-0x2000; kind 1 white/orange, height 600, three random turns), width 10, held 6 ticks: in by 53 up to 0xA0, then out by 12 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b847_01E04C90;

static s32 func_01E04C90_b847(s32 arg0, Obj_b847_01E04C90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0x70, 0x70, 0x70);
            func_001076F0(o->col2, 0x30, 0xC0, 0x30);
            o->h6 = 6;
            o->f4C = 200.0f;
            o->w24 = func_0019A5C8() % 65535;
            o->w20 = func_0019A5C8() % 0x4000 - 0x2000;
        }
        if (o->h50 == 1) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0xC0, 0x80, 0xFF);
            o->h6 = 6;
            o->f4C = 600.0f;
            o->w24 = func_0019A5C8() % 65535;
            o->w20 = func_0019A5C8() % 65535;
            o->w28 = func_0019A5C8() % 65535;
        }
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->h6) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x35;
        }
    } else if (o->col2[3] > 13) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b847:01E04E60, 381 insns: b445:01E03080 with other colours/offsets: a jittery spark trail on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b847_01E04E60;

typedef struct {
    u8 pad0[0x6770];
    Track_b847_01E04E60 track[0x40];
    u8 pad[0xD070 - 0x6770 - 0x40 * 0x140];
    Vec4f pt[0x88];
    u8 trig[1];
} World_b847_01E04E60;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b847_01E04E60;

static s32 func_01E04E60_b847(World_b847_01E04E60 *w, Spark_b847_01E04E60 *o) {
    extern void b847_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 2.0f;
        w->pt[o->idx].y += o->v.y / 2.0f;
        w->pt[o->idx].z += o->v.z / 2.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 150 + 100;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 125 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = 0x5A;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xC0, 0x80, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x60, 0xC0);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        b847_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b847:01E05460, 432 insns: b847:01E04E60 turning: kicked sideways at start, heading turns 165..194 a set-up, pitch +-45 by the world flag: a jittery spark trail on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b847_01E05460;

typedef struct {
    u8 pad0[0x6770];
    Track_b847_01E05460 track[0x40];
    u8 pad[0xD070 - 0x6770 - 0x40 * 0x140];
    Vec4f pt[0x67];
    u8 padD6E0[8];
    s16 dir;
    u8 padD6EA[0xD8F0 - 0xD6EA];
    u8 trig[1];
} World_b847_01E05460;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    s16 sub;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b847_01E05460;

static s32 func_01E05460_b847(World_b847_01E05460 *w, Spark_b847_01E05460 *o) {
    extern void b847_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        o->sub = o->idx % 6;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        o->head = (func_0019A5C8() >> 4) % 360;
        w->pt[o->idx].x += 25.0f * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += 25.0f * func_00108030(w->trig, o->head, 0);
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 80 + 40;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 65 + 3;
        o->speed /= 10.0f;
        o->head += (s16)(func_0019A5C8() % 30 + 165);
        if (w->dir != 0) {
            o->pitch = -0x2D;
        } else {
            o->pitch = 0x2D;
        }
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
    }
    if (o->t < 7) {
        b847_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b847:01E05B20, 119 insns: blinking spark with random radius, two angles, spin and life */

typedef struct Sp_b847_01E05B20 {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 spin;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 rad;
    s16 h52;
    s16 age;
    s16 h56;
    s16 state;
    s16 ang;
    s16 ang2;
    u8 pad5E[2];
    u8 col[4];
} Sp_b847_01E05B20;

static s32 func_01E05B20_b847(s32 arg0, Sp_b847_01E05B20 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->f48 = 40.0f;
        o->h56 = 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->rad = func_0019A5C8() % 100 + 30;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->ang2 = (func_0019A5C8() >> 4) % 360;
        o->spin = func_0019A5C8() % 15 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 10 + 10;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->age % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    o->h52++;
    o->age++;
    return 0;
}

/* shape b847:01E05D00, 48 insns: variant of b445:01E03C90 (volume fade): game state at 0xD620, floor 0x20 */

typedef struct {
    u8 pad[0xD620];
    s32 state;
} Game_b847_01E05D00;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b847_01E05D00;

static s32 func_01E05D00_b847(Game_b847_01E05D00 *g, Fade_b847_01E05D00 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
        if (o->vol > 0x20) {
            o->vol -= 10;
        } else {
            o->vol = 0x20;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    func_001F6D00((u8)o->vol);
    return 0;
}

/* shape b847:01E05DC0, 124 insns: b016:01E02B40's full-screen veil in purple (0x40, 0x20, 0x80), alpha up for 5 ticks */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b847_01E05DC0;

typedef struct {
    f32 s, t;
    Xyz_b847_01E05DC0 p;
} Tv_b847_01E05DC0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b847_01E05DC0 v[2];
    u8 tail[0x20];
} Tex_b847_01E05DC0;

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b847_01E05DC0;

static s32 func_01E05DC0_b847(s32 arg0, Fx_b847_01E05DC0 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b847_01E05DC0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    ((Tex_b847_01E05DC0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b847_01E05DC0 *)(s32)&pk)->size = 5;
    ((Tex_b847_01E05DC0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b847_01E05DC0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x40;
    pk.g = 0x20;
    pk.b = 0x80;
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->tick < 5) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x28;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b847:01E05FB0, 215 insns: b252:01E03CA0's full-screen overlay in two kinds: one sprite over the whole screen,
   its texture window inset by three times a tenth of the slot's width on every side (bottom too); kind 0 grey 0xC0
   fading in by 10 to 0x80 for 30 ticks; kind 1 dark grey 0x40 at alpha 0xC0, which from scene count 162 (ctx+0xD6EC)
   and tick 7 widens the inset by 25 a tick and fades by 13 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b847_01E05FB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b847_01E05FB0 p;
    } v[2];
} Pkt_b847_01E05FB0;

typedef struct {
    u8 pad0[8];
    s16 w;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b847_01E05FB0;

typedef struct {
    u8 pad0[0xD638];
    Pkt_b847_01E05FB0 *pkt;
    u8 padD63C[0xD6EC - 0xD63C];
    s16 count;
} Scene_b847_01E05FB0;

static s32 func_01E05FB0_b847(Scene_b847_01E05FB0 *s, Slot_b847_01E05FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 w;
    f32 h;

    w = o->w;
    h = o->w;
    w /= 10.0f;
    h /= 10.0f;
    if (o->state == 1) {
        if (o->kind == 0) {
            o->c0[3] = 0;
            func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        }
        if (o->kind == 1) {
            o->c0[3] = 0xC0;
            func_001076F0(o->c0, 0x40, 0x40, 0x40);
        }
        o->state = 2;
    }
    s->pkt->r = o->c0[0];
    s->pkt->g = o->c0[1];
    s->pkt->b = o->c0[2];
    s->pkt->a = o->c0[3];
    s->pkt->q = 1.0f;
    s->pkt->v[0].p.x = 0x6BF8;
    s->pkt->v[0].p.y = 0x71F8;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[0].p.f = 0;
    s->pkt->v[1].p.x = 0x93F8;
    s->pkt->v[1].p.y = 0x8DF8;
    s->pkt->v[1].p.z = 0xFFFFFF;
    s->pkt->v[1].p.f = 0;
    s->pkt->v[0].s = 3.0f * w / 1024.0f;
    s->pkt->v[0].t = 3.0f * h / 512.0f;
    s->pkt->v[1].s = (640.0f - 3.0f * w) / 1024.0f;
    s->pkt->v[1].t = (448.0f - 3.0f * h) / 512.0f;
    func_002075F0(s->pkt, 0, 0);
    if (o->kind == 0) {
        if (o->t < 30) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 10;
            }
        }
    }
    if (o->kind == 1) {
        if (s->count >= 162) {
            if (o->t >= 7) {
                o->w += 25;
                if (o->c0[3] > 14) {
                    o->c0[3] -= 13;
                } else {
                    o->state = 0;
                }
            }
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b847", func_01E06310_b847);

/* shape b847:01E06E00, 106 insns: take a free effect slot (0xE6 of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0xD624, attach it to the scene position (0x250) and copy it, 0x50, 0x52, 0x5A from 0xD6E4 / 0xD6E4 / 0xD6D0, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b847_01E06E00;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b847_01E06E00 slots[0xE6];
    u8 pad6740[0xD624 - 0x6740];
    u8 rgba[4];
    u8 padD628[0xA8];
    s16 fD6D0;
    u8 padD6D2[0x12];
    s16 fD6E4;
} Scene_b847_01E06E00;

static s32 func_01E06E00_b847(Scene_b847_01E06E00 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b847_01E06E00 *s = NULL;
    s16 i;

    for (i = 0; i < 0xE6; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0xE6;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f50 = g->fD6E4;
        s->f52 = g->fD6E4;
        s->f5A = g->fD6D0;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b847:01E06FB0 (B847PAINT_RAIN20), 178 insns, 1 copy: b232:01E01B90's draw with one quad: two-colour packet,
   the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; the frame
   rect comes from b847:01E009B0 (20 frames, by the object's 0x56); one quad of size f48, twisted by 0x5C, pushed f4C
   out at angle 0x5A - 200 (trig g+0xD8F0), depth-tested into the scene's ordering table */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    f32 r;
    u8 pad50[6];
    s16 h56;
    u8 pad58[2];
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b847_01E06FB0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xD62C - 0xC0];
    s32 ot;
    u8 padD630[0xD8F0 - 0xD630];
    u8 trig[1];
} Game_b847_01E06FB0;

static void func_01E06FB0_b847(Game_b847_01E06FB0 *g, Obj_b847_01E06FB0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    Rect_b152_01E014F0 rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r = o->r;
    tw[2] = o->h5C;
    rc = func_01E009B0_b847(0x14, o->h56, 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = r * func_00108030(g->trig, a, 1);
        sn = r * func_00108030(g->trig, a, 0);
        func_00108CE0(q, o->size, o->size);
        func_00109100(q, tw, 2, g->trig);
        func_00107070(q, 0, c);
        func_00107070(q, 1, sn);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}

/* shape b847:01E07280, 84 insns: b183:01E029E0 family draw pass: sprite packet on the stack, then every live slot (230 of 0x70 bytes) whose handler is shape b847:01E05FB0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b847_01E07280;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b847_01E07280 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b847_01E07280;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b847_01E07280;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b847_01E07280 slot[230];
    u8 padEnd[0xD634 - 0x2A0 - 230 * 0x70];
    s32 ctx;
    Pkt_b847_01E07280 *pkt;
} Scene_b847_01E07280;

static void func_01E07280_b847(Scene_b847_01E07280 *s) {
    extern void b847_01E05FB0(Scene_b847_01E07280 *, Slot_b847_01E07280 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b847_01E07280 pkt __attribute__((aligned(8)));
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
    for (i = 0; i < 230; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b847_01E05FB0) {
            b847_01E05FB0(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
