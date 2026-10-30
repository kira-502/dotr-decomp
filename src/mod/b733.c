#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b733(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b733(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b445:01E00D10, 372 insns, 5 copies: draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b445_01E00D10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b445_01E00D10 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b445_01E00D10;

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
} Obj_b445_01E00D10;

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
    u8 pad5C[4];
    u8 col[4];
} Spr_b445_01E00D10;

static void func_01E009B0_b733(Obj_b445_01E00D10 *o, Spr_b445_01E00D10 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b445_01E00D10 func_00107740(void *);
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
    Pkt_b445_01E00D10 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b445_01E00D10 *p;
    u8 mode;

    p = (Pkt_b445_01E00D10 *)(s32)&pkt;
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
    func_01E00110_b733((Pk_b003_01E00080 *)p, &o->rect, 0);
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
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00110_b733((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
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
        }
        if (o->kind == 1) {
            func_00108950(&e, ax, 0, o->xD8);
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

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E00F80_b733(s32 unused, s16 n, s32 unused2) {
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

static void func_01E010D0_b733(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b733", func_01E01430_b733);

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E01F80_b733(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
    }
}

/* shape b733:01E02150, 238 insns: the effect scene's step: counts the frame (0xC48E); until frame 150 the camera point
   is kept at 0xC350; frames 88..150 spawn 0x1E036C0 and 0x1E02EA0 on joint 0xC40A; frames 21..60 spawn four 0x1E02970
   on joint 0xC40C nudged 0.5 in z by the scene side (0xC48A); frames 166..240 spawn three 0x1E03040 a frame numbered
   by a wrapping 80-count (0xC478), then 0x1E02D30 and 0x1E027D0 at the camera point; frame 165 spawns 0x1E02C30;
   frames 75..300 open up to 36 rings (0xC472) at heights 10 apart through 0x1E02510 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xC350 - 0x260];
    Vec4f cam;
    u8 padC360[0xC40A - 0xC360];
    s16 ja;
    s16 jb;
    u8 padC40E[0x64];
    s16 n;
    s16 h;
    u8 padC476[2];
    s16 cnt;
    u8 padC47A[0xC];
    s16 idx;
    u8 padC488[2];
    s16 side;
    u8 padC48C[2];
    s16 t;
} Scene_b733_01E02150;

static void func_01E02150_b733(Scene_b733_01E02150 *g) {
    extern void b733_01E02510(void);
    extern void b733_01E027D0(void);
    extern void b733_01E02970(void);
    extern void b733_01E02C30(void);
    extern void b733_01E02D30(void);
    extern void b733_01E02EA0(void);
    extern void b733_01E03040(void);
    extern void b733_01E036C0(void);
    extern s32 b733_01E04240(Scene_b733_01E02150 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;

    g->t++;
    if (g->t < 151) {
        func_001F5F90(func_001F5380(), &g->cam);
    }
    if (g->t > 87 && g->t < 151) {
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        b733_01E04240(g, (s32)b733_01E036C0, 0);
        b733_01E04240(g, (s32)b733_01E02EA0, 0);
    }
    if (g->t > 20 && g->t < 61) {
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        if (g->side != 0) {
            g->pos.z -= 0.5f;
        } else {
            g->pos.z += 0.5f;
        }
        b733_01E04240(g, (s32)b733_01E02970, 0);
        b733_01E04240(g, (s32)b733_01E02970, 0);
        b733_01E04240(g, (s32)b733_01E02970, 0);
        b733_01E04240(g, (s32)b733_01E02970, 0);
    }
    if (g->t > 165 && g->t < 241) {
        for (i = 0; i < 3; i++) {
            g->idx = g->cnt;
            b733_01E04240(g, (s32)b733_01E03040, 0);
            g->cnt++;
            if (g->cnt >= 80) {
                g->cnt = 0;
            }
        }
    }
    if (g->t == 165) {
        b733_01E04240(g, (s32)b733_01E02C30, 0);
    }
    if (g->t > 165 && g->t < 241) {
        g->pos = g->cam;
        b733_01E04240(g, (s32)b733_01E02D30, 0);
        b733_01E04240(g, (s32)b733_01E027D0, 0);
    }
    if (g->t >= 75 && g->t < 301) {
        if (g->n < 36) {
            g->h = g->n * 10;
            g->idx = g->n;
            b733_01E04240(g, (s32)b733_01E02510, 0);
            g->n++;
        }
    }
}

/* shape b733:01E02510, 174 insns: b733:01E036C0 family white ring by slot (0x50: under 36 kind 0, under 72 kind 2, under 108 kind 4), frame 4..6, both alphas up by 12 to 0xC0 for 30 ticks, then down by 11 once the scene count (ctx+0xC48E) passes 240; cycles h6 0..5 every 10 ticks; while the scene runs kind 0 is 25 wide (f48 5) and kind 2 7 wide (0.8); from count 161 the first two slot bands turn +2 / -2; odd slots spin +3, even -3 */

typedef struct {
    u8 pad0[0xC48E];
    s16 count;
} Game_b733_01E02510;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[0x3E];
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
} Fx_b733_01E02510;

static s32 func_01E02510_b733(Game_b733_01E02510 *g, Fx_b733_01E02510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 1.5f;
        o->f56 = 0;
        o->mode = 2;
        if (o->f50 < 36) {
            o->kind = 0;
        } else if (o->f50 < 72) {
            o->kind = 2;
        } else if (o->f50 < 108) {
            o->kind = 4;
        }
        o->h8 = func_0019A5C8() % 3 + 4;
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
    } else if (g->count > 240) {
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
            o->f48 = 5.0f;
        } else if (o->kind == 1) {
        } else if (o->kind == 2) {
            o->f4C = 7.0f;
            o->f48 = 0.8f;
        }
    }
    if (g->count > 160) {
        if (o->f50 < 36) {
            o->f5A += 2;
        } else if (o->f50 < 72) {
            o->f5A -= 2;
        }
    }
    if (o->f50 % 2 == 1) {
        o->f5C += 3;
    } else {
        o->f5C -= 3;
    }
    o->tick++;
    return 0;
}

/* shape b178:01E03090, 102 insns, 2 copies: a white glint: set up once (size 2, frame 4, random turn on all axes, angle
   20..239, speed 15..44, life 2..4); full for its life, then fades out (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
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
} Spark_b178_01E03090;

static s32 func_01E027D0_b733(void *arg0, Spark_b178_01E03090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 2.0f;
        o->frame = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = func_0019A5C8() % 220 + 20;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 30 + 15;
        o->h8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b733:01E02970, 113 insns: on start f48 4, variant 4, colour white, rotation -0x4000 when the game flag 0xC48A is
   set else 0x4000, 0x50 3..22, random 0x5A, speed 2..6 (0xE), 0x8 0..29, hold 2..4 (0x6); the tick jumps to 10 while
   the game step 0xC48E is 60; alpha grows by 0x40 (below 0xC0) during the hold, then fades by 15 and stops; after the
   first tick 0x50 grows by the speed */

typedef struct {
    u8 pad0[0xC48A];
    s16 flag;
    u8 padC48C[2];
    s16 step;
} Game_b733_01E02970;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b733_01E02970;

static s32 func_01E02970_b733(Game_b733_01E02970 *g, Fx_b733_01E02970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        if (g->flag != 0) {
            o->rot = -0x4000;
        } else {
            o->rot = 0x4000;
        }
        o->f50 = func_0019A5C8() % 20 + 3;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 2;
        o->f8 = func_0019A5C8() % 30;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (g->step == 60) {
        o->tick = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b733:01E02B40, 59 insns: a grey-purple spinning flash (b236:01E01B70 family): f4C 5, size 30x30; second alpha up by 0x50 to 0xA0 for
   3 frames, then down by 12 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b733_01E02B40;

static s32 func_01E02B40_b733(void *arg0, Obj_b733_01E02B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->f4C = 5.0f;
        func_001076F0(o->c0, 0x70, 0x70, 0x70);
        func_001076F0(o->c1, 0x40, 0x20, 0x30);
        o->w = 0x1E;
        o->h = 0x1E;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 3) {
        if (o->c1[3] < 0xA0) {
            o->c1[3] += 0x50;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b733:01E02C30, 63 insns, 3 copies: step of a two-colour glow: on state 1 sets both colours grey and a lifetime
   of 12; fades both in by 0x2A, then out by 12 until the first ends. */

typedef struct {
    u8 pad00[6];
    s16 life;
    u8 pad08[0x4C];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b733_01E02C30;

static s32 func_01E02C30_b733(void *arg0, Obj_b733_01E02C30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->life = 12;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else {
        if (o->c0[3] > 13) {
            o->c0[3] -= 12;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 13) {
            o->c1[3] -= 12;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b733:01E02D30, 91 insns: on start f48 100.0f, f4C 130.0f + 0..79, colour 0x70 grey, second colour (0x40, 0x20, 0x30)
   with alpha 0, random rotation, 0x5A/0x5C = 30; the second alpha grows by 0x50 (below 0xA0) for 3 ticks, then fades
   by 12 and stops; f4C grows by 20.0f */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b733_01E02D30;

static s32 func_01E02D30_b733(s32 arg0, Fx_b733_01E02D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->f4C = 130.0f + (func_0019A5C8() >> 4) % 80;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        func_001076F0(o->col2, 0x40, 0x20, 0x30);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f5A = 30;
        o->f5C = 30;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->col2[3] > 0xD) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->f4C += 20.0f;
    o->tick++;
    return 0;
}

/* shape b733:01E02EA0, 101 insns: on start f48 3, variant 4, colour white, rotation -0x2000 when the game flag 0xC48A
   is set else 0x2000, 0x50 10..49, random 0x5A, speed 15..44 (0xE), 0x8 0..19, hold 2..4 (0x6); alpha 0xC0 during the
   hold, then fades by 9 and stops; 0x50 grows by the speed after the first tick */

typedef struct {
    u8 pad0[0xC48A];
    s16 flag;
} Game_b733_01E02EA0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b733_01E02EA0;

static s32 func_01E02EA0_b733(Game_b733_01E02EA0 *g, Fx_b733_01E02EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        if (g->flag != 0) {
            o->rot = -0x2000;
        } else {
            o->rot = 0x2000;
        }
        o->f50 = func_0019A5C8() % 40 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 30 + 15;
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b733:01E03040, 416 insns: b847:01E05460 variant of b847:01E04E60 turning: kicked sideways at start, heading turns 165..194 a set-up, random pitch, no climb: a jittery spark trail on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b733_01E03040;

typedef struct {
    u8 pad0[0x5A50];
    Track_b733_01E03040 track[0x40];
    u8 pad[0xBE50 - 0x5A50 - 0x40 * 0x140];
    Vec4f pt[0x84];
    u8 trig[1];
} World_b733_01E03040;

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
} Spark_b733_01E03040;

static s32 func_01E03040_b733(World_b733_01E03040 *w, Spark_b733_01E03040 *o) {
    extern void b733_01E00080(void *, s32, s32, void *);
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
        o->size = func_0019A5C8() % 60 + 3;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 65 + 3;
        o->speed /= 10.0f;
        o->head += (s16)(func_0019A5C8() % 30 + 165);
        o->pitch = (func_0019A5C8() >> 4) % 360;
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
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
    }
    if (o->t < 7) {
        b733_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b733:01E036C0, 118 insns: on start f48 3, variant 4, colour white, rotation -0x2000 when the game flag 0xC48A is
   set else 0x2000, 0x50 10..49 (kind 0x52 = 0) or 10..29 (kind 1), random 0x5A, speed 6..20 (0xE), 0x8 0..19, hold
   2..4 (0x6); alpha 0xC0 during the hold, then fades by 9 and stops; after the first tick 0x50 grows by the speed */

typedef struct {
    u8 pad0[0xC48A];
    s16 flag;
} Game_b733_01E036C0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 kind;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b733_01E036C0;

static s32 func_01E036C0_b733(Game_b733_01E036C0 *g, Fx_b733_01E036C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        if (g->flag != 0) {
            o->rot = -0x2000;
        } else {
            o->rot = 0x2000;
        }
        if (o->kind == 0) {
            o->f50 = func_0019A5C8() % 40 + 10;
        }
        if (o->kind == 1) {
            o->f50 = func_0019A5C8() % 20 + 10;
        }
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 15 + 6;
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E038A0_b733(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b733", func_01E038B0_b733);

/* shape b733:01E04240, 106 insns: takes the first free of 200 effect slots (0x70 bytes, b041:01E02C00 shape),
   clears and marks it, colours both from the scene, places it at the scene point, copies its settings and stores both
   arguments */

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
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b733_01E04240;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b733_01E04240 slot[200];
    u8 padEnd[0xC3D4 - 0x2A0 - 200 * 0x70];
    u8 col[4];
    u8 padC3D8[0x9C];
    s16 hC474;
    u8 padC476[0x10];
    s16 hC486;
} Scene_b733_01E04240;

static s32 func_01E04240_b733(Scene_b733_01E04240 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b733_01E04240 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 200; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 200;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->hC486;
        sl->h52 = s->hC486;
        sl->h5A = s->hC474;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b733:01E043F0 (B733PAINT_RAIN20), 188 insns, 1 copy: b178:01E04D20's one-quad draw with this module's scene
   layout: ordering table g+0xC3DC, frame table g+0xC428, trig g+0xC690 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    f32 r;
    s16 h50;
    u8 pad52[6];
    u8 pad58[2];
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b733_01E043F0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xC3DC - 0xC0];
    s32 ot;
    u8 padC3E0[0xC428 - 0xC3E0];
    s16 tbl[36];
    u8 padC470[0xC690 - 0xC470];
    u8 trig[1];
} Game_b733_01E043F0;

static void func_01E043F0_b733(Game_b733_01E043F0 *g, Obj_b733_01E043F0 *o, s32 mode, Vec4f *in) {
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
    rc = func_01E00F80_b733(0x14, g->tbl[o->h50 % 36], 0);
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
