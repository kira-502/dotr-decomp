#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b702(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b702(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b702(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b702 in the
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

static void func_01E00D10_b702(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b702((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b065_01E012B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b065_01E012B0;

typedef struct {
    Col_b065_01E012B0 c;
    u64 st;
    u64 xyz;
} Vtx_b065_01E012B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b065_01E012B0 v[4];
    u8 tail[0x20];
} Pkt_b065_01E012B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Anim_b065_01E012B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b065_01E012B0;

static void func_01E00FD0_b702(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107740(void *, void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b065_01E012B0 quad[4];
    Vec_b065_01E012B0 at;
    Vec_b065_01E012B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b065_01E012B0 pkt;
    Col_b065_01E012B0 c0;
    Col_b065_01E012B0 c1;
    Col_b065_01E012B0 c2;
    Col_b065_01E012B0 c3;
    s16 blend;
    s32 i;
    s32 a;
    s16 j;
    s16 wd;
    Pkt_b065_01E012B0 *p;
    s32 width;
    f32 w0;
    f32 w1;

    p = &pkt;
    width = an->width;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    blend = mode >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col0, 0);
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    func_00107740(&c0, an->col0);
    p->v[0].c = c0;
    func_00107740(&c1, an->col1);
    p->v[2].c = c1;
    func_00107740(&c2, an->col0);
    p->v[1].c = c2;
    func_00107740(&c3, an->col1);
    p->v[3].c = c3;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    wd = width;
    for (i = 0; i < o->count; i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + wd);
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if ((mode & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if ((mode & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        }
        j += an->step;
    }
}

/* shape b702:01E013E0 (B702_W_S), 390 insns, 1 copy: B702_W_S, the effect scene step: counts the frame (0xB3F8);
   spawns 0x1E01A00 on frames 2..249 at joint 0xB384, four more stepping back toward the trail head on 182..189; at 1
   fills the 20-point trail 0xB1D0 and spawns 0x1E029C0, 0x1E02790; shifts the trail on 1..250; from 185 to 250 the
   0x1E01FD0 sides by frame parity and 0x1E01BD0, at 185 0x1E02670, 0x1E02AD0 and ten 0x1E01DE0; 13 0x1E024A0 at joint
   0xB386 on 39/78/122 and 0xB388 on 26/61/100/125 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f hist[20];
    u8 padB310[0xB384 - 0xB310];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 padB38A[0xB3F0 - 0xB38A];
    s16 side;
    u8 padB3F2[0xB3F8 - 0xB3F2];
    s16 t;
} Scene_b702_01E013E0;

static void func_01E013E0_b702(Scene_b702_01E013E0 *g) {
    extern void b702_01E01A00(void);
    extern void b702_01E01BD0(void);
    extern void b702_01E01DE0(void);
    extern void b702_01E01FD0(void);
    extern void b702_01E024A0(void);
    extern void b702_01E02670(void);
    extern void b702_01E02790(void);
    extern void b702_01E029C0(void);
    extern void b702_01E02AD0(void);
    extern void b702_01E03770(Scene_b702_01E013E0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 dx, dy, dz;
    s16 i;

    g->t++;
    if (g->t > 1 && g->t < 250) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        b702_01E03770(g, b702_01E01A00, 0);
    }
    if (g->t > 181 && g->t < 190) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        dx = (g->pos.x - g->hist[0].x) / 4.0f;
        dy = (g->pos.y - g->hist[0].y) / 4.0f;
        dz = (g->pos.z - g->hist[0].z) / 4.0f;
        for (i = 0; i < 4; i++) {
            g->pos.x -= dx;
            g->pos.y -= dy;
            g->pos.z -= dz;
            b702_01E03770(g, b702_01E01A00, 0);
        }
    }
    if (g->t == 1) {
        s16 k;
        Vec4f *p;
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        p = g->hist;
        for (k = 0; k < 19; k++, p++) {
            p->x = g->pos.x;
            p->y = g->pos.y;
            p->z = g->pos.z;
        }
        b702_01E03770(g, b702_01E029C0, 0);
        b702_01E03770(g, b702_01E02790, 0);
    }
    if (g->t > 0 && g->t < 251) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        func_01E00080_b702(&g->hist[19], 20, 0, &g->pos);
    }
    if (g->t >= 185 && g->t < 251) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y -= 20.0f;
        g->side = 0;
        if (g->t % 2 == 1) {
            b702_01E03770(g, b702_01E01FD0, 0);
        }
        g->side = 1;
        if (g->t % 2 == 1) {
            b702_01E03770(g, b702_01E01FD0, 0);
        }
        g->side = 2;
        if (g->t % 2 == 0) {
            b702_01E03770(g, b702_01E01FD0, 0);
        }
        b702_01E03770(g, b702_01E01BD0, 0);
        if (g->t == 185) {
            b702_01E03770(g, b702_01E02670, 0);
        }
        if (g->t == 185) {
            b702_01E03770(g, b702_01E02AD0, 0);
        }
        if (g->t == 185) {
            for (i = 0; i < 10; i++) {
                b702_01E03770(g, b702_01E01DE0, 0);
            }
        }
    }
    if (g->t == 39 || g->t == 78 || g->t == 122) {
        func_001F5620(func_001F53A0(), g->j1, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b702_01E03770(g, b702_01E024A0, 0);
        }
    }
    if (g->t == 26 || g->t == 61 || g->t == 100 || g->t == 125) {
        func_001F5620(func_001F53A0(), g->j2, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b702_01E03770(g, b702_01E024A0, 0);
        }
    }
}

/* shape b702:01E01A00, 114 insns: b282:01E01C20 family dark smoke puff (random size 100..159 growing 1, frame 0..2, angle 5..14, spin 2..6, size 0..34), held 9..16 ticks: in by 64 up to 0xC0, then out by 19 and ends */

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
} Obj_b702_01E01A00;

static s32 func_01E01A00_b702(s32 arg0, Obj_b702_01E01A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 60 + 100;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->h50 = func_0019A5C8() % 10 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 8 + 9;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f48 += 1.0f;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b702:01E01BD0, 131 insns, 3 copies: step of a swirling grey puff (b396:01E01990 family): random size, phase,
   height, turn direction, angle, speed and lifetime; fades in by 0x40, then out by 19; grows, climbs and turns
   by 2 each tick. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    s16 dir;
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b702_01E01BD0;

static s32 func_01E01BD0_b702(void *arg0, Obj_b702_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 60 + 80;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x50, 0x50, 0x50);
        o->h50 = func_0019A5C8() % 10 + 5;
        o->dir = func_0019A5C8() % 2;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 30 + 20;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 8 + 9;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 20) {
        o->c0[3] -= 19;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->size += 1.0f;
    }
    if (o->t != 0) {
        o->h50 += o->speed;
    }
    if (o->dir == 0) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b702_01E01DE0;

static s32 func_01E01DE0_b702(s32 unused, Obj_b702_01E01DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 60 + 200;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h50 = func_0019A5C8() % 10 + 5;
        o->h52 = func_0019A5C8() % 2;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 70 + 60;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 8 + 15;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x40;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 19;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f48 += 5.0f;
    }
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape b702:01E01FD0, 308 insns, 1 copy (B702_OBJ_MOVE_6_): b247:01E027A0 in green and grey: a shock ring of kind
   0..2, growth 35..42.9 a tick, out by 11; kind 0 keeps its inner at 0.2 of the radius and turns 0x80 a tick either way */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x1C];
    s32 turn;
    u8 pad28[8];
    f32 rise;
    f32 f34;
    f32 grow;
    u8 pad3C[0xC];
    f32 r;
    f32 r2;
    s16 kind;
    s16 dir;
    s16 tick;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b702_01E01FD0;

typedef struct {
    u8 pad0[0xB3F8];
    s16 frame;
} Scene_b702_01E01FD0;

static s32 func_01E01FD0_b702(Scene_b702_01E01FD0 *g, Obj_b702_01E01FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->r = 140.0f;
        o->r2 = o->r - 58.0f;
        if (o->kind == 0) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x80, 0xC0, 0x80);
                func_001076F0(o->col, 8, 8, 8);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x80, 0xFF, 0x80);
                func_001076F0(o->col, 0x38, 0x38, 0x38);
            }
            o->life = 8;
        }
        if (o->kind == 1) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x60, 0x80, 0x60);
                func_001076F0(o->col, 8, 8, 8);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x40, 0xFF, 0x40);
                func_001076F0(o->col, 0x38, 0x38, 0x38);
            }
            o->f34 = 10.0f;
            o->life = 10;
        }
        if (o->kind == 2) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x50, 0x50, 0x50);
                func_001076F0(o->col, 0x28, 0x28, 0x28);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x60, 0x60, 0x60);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->f34 = 70.0f;
            o->life = 10;
        }
        if (o->kind == 0) {
            o->h5A = 60;
            o->h5C = 60;
            o->dir = (func_0019A5C8() >> 4) % 2;
        }
        if (o->kind == 1) {
            o->h5A = 10;
            o->h5C = 3;
        }
        if (o->kind == 2) {
            o->h5A = 60;
            o->h5C = 60;
        }
        o->grow = func_0019A5C8() % 80 + 350;
        o->grow /= 10.0f;
        o->rise = 350.0f;
        o->rise /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->turn = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < o->life) {
        o->col2[3] = 0x80;
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        o->r += o->grow;
        o->r2 = 0.2f * o->r;
        if (o->dir == 0) {
            o->turn += 0x80;
        } else {
            o->turn -= 0x80;
        }
    }
    if (o->kind == 1) {
        o->r += o->grow;
        o->r2 = 0.7f * o->r;
        o->f34 += o->grow;
    }
    if (o->kind == 2) {
        o->r += o->grow;
        o->r2 = 0.7f * o->r;
        o->f34 += o->grow;
    }
    o->tick++;
    return 0;
}

/* shape b702:01E024A0, 113 insns: on start 0x8/0xA = 130, variant 2..4, colour white, random heading 0x5A and a jump of
   6.6 along it (z by the cosine, x by the sine of the game table 0xB6FC); alpha grows by 0x40 (below 0x80) for 10
   ticks, then fades by 9 and stops; after the first tick it moves 0.5 along the heading; func_00205C40 on the
   rotation */

typedef struct {
    u8 pad0[0xB6FC];
    u8 trig[1];
} Game_b702_01E024A0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 heading;
    u8 pad5C[4];
    u8 col[4];
} Fx_b702_01E024A0;

static s32 func_01E024A0_b702(Game_b702_01E024A0 *g, Fx_b702_01E024A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f8 = 130;
        o->fA = o->f8;
        o->f56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->heading = (func_0019A5C8() >> 4) % 360;
        o->z += 6.6f * func_00108030(g->trig, o->heading, 0);
        o->x += 6.6f * func_00108030(g->trig, o->heading, 1);
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->z += 0.5f * func_00108030(g->trig, o->heading, 0);
        o->x += 0.5f * func_00108030(g->trig, o->heading, 1);
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b702:01E02670, 69 insns: constant variant of b287:01E02C80 (0xE->0x1E, 150.0f->500.0f, colour (255, 255, 255), colour (255, 128, 128)) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
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
} Fx_b702_01E02670;

static s32 func_01E02670_b702(s32 arg0, Fx_b702_01E02670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 500.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x1E) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        o->size += 0.4f;
    }
    o->tick++;
    return 0;
}

/* shape b702:01E02790, 137 insns: b757:01E029A0's joint-following scene light in (128, 10, 5, 5), joint 0xB388, 180 ticks, ends when 0xB350 is 2 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b702_01E02790;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b702_01E02790 light;
    u8 padB1CC[0x184];
    s32 flag;
    u8 padB354[0x34];
    s16 joint;
} Scene_b702_01E02790;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x34];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fx_b702_01E02790;

static s32 func_01E02790_b702(Scene_b702_01E02790 *g, Fx_b702_01E02790 *o) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    Vec4f v[2];

    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 10.0f;
        g->light.c[2] = 5.0f;
        g->light.c[3] = 5.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 123.0f;
        g->light.level = 0.0f;
        g->light.pos.x = o->x;
        g->light.pos.y = o->y;
        g->light.pos.z = o->z;
        o->mode = 2;
        o->h50 = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, v);
    g->light.pos.x = v[0].x;
    g->light.pos.y = v[0].y;
    g->light.pos.z = v[0].z;
    if (o->t < 0xB4) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.3f;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.3f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 2) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b702:01E029C0, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x97, floor 0x30, state at 0xB350 below 0x1E */

typedef struct {
    u8 pad[0xB350];
    s32 state;
} Game_b702_01E029C0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b702_01E029C0;

static s32 func_01E029C0_b702(Game_b702_01E029C0 *g, Fade_b702_01E029C0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x97) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->tick++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b702:01E02AD0, 156 insns: b432:01E03460 in 0x88/0x80/0x80 at 2.5, growing 0.2 to 6 after scene count 185 (ctx+0xB3F8); alpha up by 22 to 0x58 until count 260, then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b702_01E02AD0;

typedef struct {
    f32 s, t;
    Xyz_b702_01E02AD0 p;
} Tv_b702_01E02AD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b702_01E02AD0 v[2];
    u8 tail[0x20];
} Tex_b702_01E02AD0;

typedef struct {
    u8 pad0[0xB3F8];
    s16 count;
} Ctx_b702_01E02AD0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b702_01E02AD0;

static s32 func_01E02AD0_b702(Ctx_b702_01E02AD0 *g, Fx_b702_01E02AD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b702_01E02AD0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x88, 0x80, 0x80);
        o->mode = 2;
    }
    ((Tex_b702_01E02AD0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b702_01E02AD0 *)(s32)&pk)->size = 5;
    ((Tex_b702_01E02AD0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b702_01E02AD0 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
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
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->count > 185) {
        if (o->f48 < 6.0f) {
            o->f48 += 0.2f;
        }
    }
    if (g->count < 260) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02D40_b702(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b702", func_01E02D50_b702);

/* shape b702:01E03770, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b702_01E03770 {
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
} Slot_b702_01E03770;

typedef struct Obj_b702_01E03770 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b702_01E03770 slots[0x190];
    u8 padB[0xb354 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb3f0 - 0xb354 - 4];
    s16 fB2B0;
} Obj_b702_01E03770;

static s32 func_01E03770_b702(Obj_b702_01E03770 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b702_01E03770 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E03900_b702(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b702((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00110_b702((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}
