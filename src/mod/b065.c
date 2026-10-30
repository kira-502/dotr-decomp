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

static void func_01E00080_b065(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b065(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b065 in the
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

static void func_01E00C80_b065(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b065((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E00F40_b065(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
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

static void func_01E012B0_b065(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

/* shape b065:01E016C0, 311 insns: B065_W_S, the scene script: counts the scene frame (0xB2BA) and spawns the module's
   movers on it: joint glows on frames 36..46, four rings + the fade + the light on frame 1, the three flashing rings
   (kinds 0, 1 on odd frames, 2 on even) at the model point on frames 57..80, the veil on 53, the swirl on 57 and 13
   sparks at either tracked joint on frames 17/30/56 and 24/36/56 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f p;
    u8 pad0260[0xB1D0 - 0x260];
    Vec4f home;
    u8 padB1E0[0xB244 - 0xB1E0];
    s16 j0;
    s16 j1;
    u8 padB248[0xB2A2 - 0xB248];
    s16 ang;
    u8 padB2A4[4];
    s16 n;
    u8 padB2AA[8];
    s16 kind;
    u8 padB2B4[6];
    s16 frame;
} Ctx_b065_01E016C0;

static void func_01E016C0_b065(Ctx_b065_01E016C0 *g) {
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void b065_01E03490();
    extern s32 b065_01E01BA0();
    extern s32 b065_01E01DB0();
    extern s32 b065_01E02240();
    extern s32 b065_01E02410();
    extern s32 b065_01E026B0();
    extern s32 b065_01E027A0();
    extern s32 b065_01E029C0();
    extern s32 b065_01E02AD0();
    s16 i;

    g->frame++;
    if (g->frame > 35 && g->frame < 47) {
        g->kind = g->n;
        b065_01E03490(g, b065_01E01BA0, 0);
        g->n++;
    }
    if (g->frame == 1) {
        g->ang = 0;
        g->kind = 0;
        b065_01E03490(g, b065_01E02410, 0);
        g->ang = 90;
        g->kind = 0;
        b065_01E03490(g, b065_01E02410, 0);
        g->ang = 45;
        g->kind = 1;
        b065_01E03490(g, b065_01E02410, 0);
        g->ang = 135;
        g->kind = 1;
        b065_01E03490(g, b065_01E02410, 0);
        b065_01E03490(g, b065_01E029C0, 0);
        b065_01E03490(g, b065_01E027A0, 0);
    }
    if (g->frame == 57) {
        func_001F5F90(func_001F5380(), &g->home);
    }
    if (g->frame >= 57 && g->frame < 81) {
        g->p = g->home;
        func_001F5F90(func_001F5380(), &g->p);
        g->p.y -= 15.0f;
        g->kind = 0;
        if (g->frame % 2 == 1) {
            b065_01E03490(g, b065_01E01DB0, 0);
        }
        g->kind = 1;
        if (g->frame % 2 == 1) {
            b065_01E03490(g, b065_01E01DB0, 0);
        }
        g->kind = 2;
        if (g->frame % 2 == 0) {
            b065_01E03490(g, b065_01E01DB0, 0);
        }
        if (g->frame == 57) {
            b065_01E03490(g, b065_01E026B0, 0);
        }
    }
    if (g->frame == 53) {
        b065_01E03490(g, b065_01E02AD0, 0);
    }
    if (g->frame == 17 || g->frame == 30 || g->frame == 56) {
        func_001F5620(func_001F53A0(), g->j0, &g->p);
        g->p.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b065_01E03490(g, b065_01E02240, 0);
        }
    }
    if (g->frame == 24 || g->frame == 36 || g->frame == 56) {
        func_001F5620(func_001F53A0(), g->j1, &g->p);
        g->p.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b065_01E03490(g, b065_01E02240, 0);
        }
    }
}

/* shape b065:01E01BA0 (B065_OBJ_MOVE_2_), 131 insns, 1 copy: b235:01E02370's joint-to-joint glow: size 15 + 5 * n,
   dark grey (0x18) over (0x20, 0x30, 0x20), alpha up by 0x30 for 60 ticks; ends when the scene frame (0xB2BA) passes
   0x43 */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0x28];
    f32 f4C;
    s16 n;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b065_01E01BA0;

typedef struct {
    u8 pad[0xB248];
    s16 j0;
    s16 j1;
    u8 padB24C[0x6E];
    s16 frame;
} Game_b065_01E01BA0;

#pragma opt_propagation off

static s32 func_01E01BA0_b065(Game_b065_01E01BA0 *g, Obj_b065_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 d[3];
    f32 k;

    if (o->mode == 1) {
        k = o->n;
        o->f4C = 15.0f + 5.0f * k;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        func_001076F0(o->col2, 0x20, 0x30, 0x20);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 0x3C) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->j0, &o->x);
    func_001F5620(func_001F53A0(), g->j1, d);
    d[0] = (d[0] - o->x) / 10.0f;
    d[1] = (d[1] - o->y) / 10.0f;
    d[2] = (d[2] - o->z) / 10.0f;
    k = o->n;
    o->x += d[0] * k;
    o->y += d[1] * k;
    o->z += d[2] * k;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    if (g->frame > 0x43) {
        o->mode = 0;
    }
    return 0;
}
#pragma opt_propagation reset

/* shape b065:01E01DB0, 290 insns: B065_OBJ_MOVE_6_: a flashing ring by kind (0 green, 1 pale green, 2 red; colours
   swap on odd scene frames), size 140 growing by 35..42.9 a tick (kinds 1, 2 also rise), full alpha for 8 or 10 ticks
   then fading by 11 */

typedef struct {
    u8 pad00[6];
    s16 life;
    u8 pad08[0x1C];
    s32 rot;
    u8 pad28[8];
    f32 f30;
    f32 rise;
    f32 grow;
    u8 pad3C[0xC];
    f32 size;
    f32 inner;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b065_01E01DB0;

typedef struct {
    u8 pad[0xB2BA];
    s16 frame;
} Game_b065_01E01DB0;

static s32 func_01E01DB0_b065(Game_b065_01E01DB0 *g, Obj_b065_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 140.0f;
        o->inner = o->size - 58.0f;
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
            o->rise = 10.0f;
            o->life = 10;
        }
        if (o->kind == 2) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x50, 0x30, 0x30);
                func_001076F0(o->col, 8, 8, 8);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x60, 0x28, 0x28);
                func_001076F0(o->col, 0x20, 0x20, 0x20);
            }
            o->rise = 10.0f;
            o->life = 10;
        }
        if (o->kind == 0) {
            o->h5A = 10;
            o->h5C = 10;
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
        o->grow = o->grow / 10.0f;
        o->f30 = 350.0f;
        o->f30 = o->f30 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot = func_0019A5C8() % 0xFFFF;
    }
    if (o->t < o->life) {
        o->col2[3] = 0x80;
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->size += o->grow;
        o->inner = 0.4f * o->size;
    }
    if (o->kind == 1) {
        o->size += o->grow;
        o->inner = 0.7f * o->size;
        o->rise += o->grow;
    }
    if (o->kind == 2) {
        o->size += o->grow;
        o->inner = 0.7f * o->size;
        o->rise += o->grow;
    }
    o->t++;
    return 0;
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b065:01E02240, 113 insns: b589:01E02400 with a kick of 6.6, drift 0.5, sine table at ctx+0xB4BC */


typedef struct {
    u8 pad0[0xB4BC];
    u8 sin[4];
} Ctx_b065_01E02240;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[4];
    Vec4f rot;
    u8 pad30[0x24];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Obj_b065_01E02240;

static s32 func_01E02240_b065(Ctx_b065_01E02240 *ctx, Obj_b065_01E02240 *o) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = 0x82;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 6.6f * func_00108030(ctx->sin, o->ang, 0);
        o->x += 6.6f * func_00108030(ctx->sin, o->ang, 1);
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.5f * func_00108030(ctx->sin, o->ang, 0);
        o->x += 0.5f * func_00108030(ctx->sin, o->ang, 1);
    }
    func_00205C40((s32)&o->rot);
    o->t++;
    return 0;
}

/* shape b065:01E02410, 165 insns: b282:01E01DB0 family ring (white, blue glow; kinds 70/30/400 wide, growing 30 or 10) moving from the first tracked point (ctx+0xB248) toward the second (ctx+0xB24A) by f52/25 of the gap, f52 counting to 25; spins 6 */

typedef struct {
    u8 pad0[0xB248];
    s16 id0;
    s16 id1;
} Ctx_b065_01E02410;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b065_01E02410;

static s32 func_01E02410_b065(Ctx_b065_01E02410 *g, Fx_b065_01E02410 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];
    f32 t;

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->f30 = 3.0f;
            o->f34 = 70.0f;
        }
        if (o->kind == 1) {
            o->f30 = 3.0f;
            o->f34 = 30.0f;
        }
        if (o->kind == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->f52 = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0 && o->tick != 0) {
        o->f34 += 30.0f;
    }
    if (o->kind == 1 && o->tick != 0) {
        o->f34 += 10.0f;
    }
    if (o->tick != 0) {
        if (o->f52 < 0x19) {
            o->f52++;
        }
    }
    o->tick++;
    o->f5A += 6;
    func_001F5620(func_001F53A0(), g->id0, o->pos);
    func_001F5620(func_001F53A0(), g->id1, v);
    t = o->f52;
    v[0] = (v[0] - o->pos[0]) / 25.0f;
    v[1] = (v[1] - o->pos[1]) / 25.0f;
    v[2] = (v[2] - o->pos[2]) / 25.0f;
    o->pos[0] += v[0] * t;
    o->pos[1] += v[1] * t;
    o->pos[2] += v[2] * t;
    return 0;
}

/* shape b065:01E026B0, 59 insns: constant variant of b415:01E022B0 (0xE->0x1E, 0x60->0x30, 0xA->0x10, 9->15, 220.0f->200.0f, colour (192, 192, 192), colour (128, 255, 128)) */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 vol;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b065_01E026B0;

static s32 func_01E026B0_b065(s32 arg0, Fx_b065_01E026B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 200.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0xFF, 0x80);
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
    o->tick++;
    return 0;
}

/* shape b065:01E027A0, 136 insns: b490:01E00E90's scene light at g+0xB1A0 on a model joint: on start colour 128/10/10/10,
   height 0/123/0 and the effect's position; each tick the light follows the joint at g+0xB24A; its strength rises by
   0.3 up to 1 for 60 ticks, then falls by 0.3 until it ends; func_001F6C10 gets the light (or 0 once ended); it
   also ends when the scene word at g+0xB210 is 2 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x44];
    s32 state;
} Light_b065_01E027A0;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b065_01E027A0 light;
    u8 padB214[0x36];
    s16 joint;
} Game_b065_01E027A0;

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x34];
    s16 f50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fx_b065_01E027A0;

static s32 func_01E027A0_b065(Game_b065_01E027A0 *g, Fx_b065_01E027A0 *o) {
    extern void func_001F6C10(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[8];

    if (o->mode == 1) {
        g->light.a[0] = 128.0f;
        g->light.a[1] = 10.0f;
        g->light.a[2] = 10.0f;
        g->light.a[3] = 10.0f;
        g->light.b[0] = 0.0f;
        g->light.b[1] = 123.0f;
        g->light.b[2] = 0.0f;
        g->light.pos[0] = o->x;
        g->light.pos[1] = o->y;
        g->light.pos[2] = o->z;
        o->mode = 2;
        o->f50 = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, p);
    g->light.pos[0] = p[0];
    g->light.pos[1] = p[1];
    g->light.pos[2] = p[2];
    if (o->t < 60) {
        if (g->light.b[2] < 1.0f) {
            g->light.b[2] += 0.3f;
        }
    } else if (g->light.b[2] > 0.1f) {
        g->light.b[2] -= 0.3f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->light.state == 2) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b065:01E029C0, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x33, floor 0x30, state at 0xB210 below 0x1E */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b065_01E029C0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b065_01E029C0;

static s32 func_01E029C0_b065(Game_b065_01E029C0 *g, Fade_b065_01E029C0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x33) {
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

/* shape b065:01E02AD0, 179 insns: b702:01E02AD0's veil (0x80/0x88/0x80, 0x80/0x90/0x80 on scene frame 54) on the scene
   frame at 0xB2BA: from frame 55 it zooms by 0.6 to 4 and its alpha also climbs by 12 to 0x60; it fades from frame 80 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b065_01E02AD0;

typedef struct {
    f32 s, t;
    Xyz_b065_01E02AD0 p;
} Tv_b065_01E02AD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b065_01E02AD0 v[2];
    u8 tail[0x20];
} Tex_b065_01E02AD0;

typedef struct {
    u8 pad0[0xB2BA];
    s16 count;
} Ctx_b065_01E02AD0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b065_01E02AD0;

static s32 func_01E02AD0_b065(Ctx_b065_01E02AD0 *g, Fx_b065_01E02AD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b065_01E02AD0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x88, 0x80);
        o->mode = 2;
    }
    if (g->count == 54) {
        func_001076F0(o->col, 0x80, 0x90, 0x80);
    }
    ((Tex_b065_01E02AD0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b065_01E02AD0 *)(s32)&pk)->size = 5;
    ((Tex_b065_01E02AD0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b065_01E02AD0 *)(s32)&pk)->pad4 = 0;
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
    if (g->count > 54) {
        if (o->f48 < 4.0f) {
            o->f48 += 0.6f;
        }
    }
    if (g->count < 80) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
        if (g->count > 54) {
            if (o->col[3] < 0x60) {
                o->col[3] += 12;
            }
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

static s32 func_01E02DA0_b065(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b065", func_01E02DB0_b065);

/* shape b065:01E03490, 106 insns: b003:01E02E90 family (like b544:01E031D0): take the first free slot of the 400-slot pool,
   clear it, give it the scene's colour twice, the scene matrix and position, scene values and the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 v50;
    s16 v52;
    u8 pad54[4];
    s16 used;
    s16 v5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b065_01E03490;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x44];
    Slot_b065_01E03490 s[400];
    u8 padEND[0x74];
    u8 r, g, b, a;
    u8 padC4[0x8a];
    s16 vA;
    u8 padA2[0xe];
    s16 vB;
} Pool_b065_01E03490;

static s32 func_01E03490_b065(Pool_b065_01E03490 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b065_01E03490 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 400; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x70);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 400;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, &o->x, 0);
        ret = 1;
        s->x = o->x;
        s->y = o->y;
        s->z = o->z;
        s->v50 = o->vB;
        s->v52 = o->vB;
        s->v5A = o->vA;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
