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

static void func_01E00080_b539(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b539(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b539 in the
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

static void func_01E00C80_b539(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b539((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00F40_b539(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

static void func_01E012B0_b539(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b539:01E01480, 371 insns: B539_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0xB2BC);
   until 113 the point and the mark (0xB1D0) follow joint 0xB24A and spawn 0x1E01A50 there; frame 87 ten 0x1E01D40,
   frame 1 eighteen 0x1E02270 (index 0xB2B4); frames 101..113 seven 0x1E01F60 stepping a fifth of the joints' depth
   gap; before 100, every 6th frame 0x1E02410 on joint 0xB24E and 0xB250 in turn; frame 113 spawns 0x1E02740,
   two 0x1E02880 (angle 0 / 90), 0x1E02990 and 0x1E02AC0 on the mark; odd frames 113..123 0x1E02990 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f mark;
    u8 padB1E0[0xB248 - 0xB1E0];
    s16 ja;
    s16 jb;
    u8 padB24C[2];
    s16 jc;
    s16 jd;
    u8 padB252[0xB2A6 - 0xB252];
    s16 ang;
    u8 padB2A8[0xB2B4 - 0xB2A8];
    s16 idx;
    u8 padB2B6[6];
    s16 t;
} Scene_b539_01E01480;

static void func_01E01480_b539(Scene_b539_01E01480 *g) {
    extern void b539_01E01A50(void);
    extern void b539_01E01D40(void);
    extern void b539_01E01F60(void);
    extern void b539_01E02270(void);
    extern void b539_01E02410(void);
    extern void b539_01E02740(void);
    extern void b539_01E02880(void);
    extern void b539_01E02990(void);
    extern void b539_01E02AC0(void);
    extern void b539_01E03530(Scene_b539_01E01480 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    s16 i;
    f32 *p;

    g->t++;
    if (g->t < 114) {
        func_001F5620(func_001F53A0(), g->ja, &a);
        func_001F5620(func_001F53A0(), g->jb, p = (f32 *)(u32)&b);
        g->pos.x = p[0];
        g->pos.y = b.y;
        g->pos.z = b.z;
        g->mark.x = g->pos.x;
        g->mark.y = g->pos.y;
        g->mark.z = g->pos.z;
    }
    if (g->t == 87) {
        for (i = 0; i < 10; i++) {
            g->idx = i;
            b539_01E03530(g, b539_01E01D40, 0);
        }
    }
    if (g->t < 114) {
        g->pos = g->mark;
        for (i = 0; i < 1; i++) {
            b539_01E03530(g, b539_01E01A50, 0);
        }
    }
    if (g->t > 100 && g->t < 114) {
        func_001F5620(func_001F53A0(), g->ja, &a);
        func_001F5620(func_001F53A0(), g->jb, &b);
        a.z = (a.z - b.z) / 5.0f;
        g->pos = g->mark;
        for (i = 0; i < 7; i++) {
            b539_01E03530(g, b539_01E01F60, 0);
            g->pos.z += a.z;
        }
    }
    if (g->t == 1) {
        for (i = 0; i < 18; i++) {
            g->idx = i;
            b539_01E03530(g, b539_01E02270, 0);
        }
    }
    if (g->t < 100) {
        if (g->t % 6 == 0) {
            func_001F5620(func_001F53A0(), g->jc, &g->pos);
            g->pos.x += func_0019A5C8() % 10 - 5;
            g->pos.y -= 1.5f;
            b539_01E03530(g, b539_01E02410, 0);
        }
        if (g->t % 6 == 3) {
            func_001F5620(func_001F53A0(), g->jd, &g->pos);
            g->pos.x += func_0019A5C8() % 10 - 5;
            g->pos.y -= 1.5f;
            b539_01E03530(g, b539_01E02410, 0);
        }
    }
    if (g->t == 113) {
        g->pos = g->mark;
        b539_01E03530(g, b539_01E02740, 0);
        g->ang = 0;
        b539_01E03530(g, b539_01E02880, 0);
        g->ang = 90;
        b539_01E03530(g, b539_01E02880, 0);
        b539_01E03530(g, b539_01E02990, 0);
        g->idx = 0;
        b539_01E03530(g, b539_01E02AC0, 0);
    }
    if (g->t >= 113 && g->t < 124 && g->t % 2 == 1) {
        g->pos = g->mark;
        b539_01E03530(g, b539_01E02990, 0);
    }
}

/* shape b539:01E01A50, 186 insns: c063:01E04250 family red (0xFF, 0x40, 0x40) flake 20 square growing 1 to 70, frame 0..2, drift /300, held 5..19 ticks, tumbling on all axes */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b539_01E01A50;

static s32 func_01E01A50_b539(s32 arg0, Fx_b539_01E01A50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 20;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 300.0f;
        o->vel[0] /= 300.0f;
        o->vel[2] /= 300.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->hold = (func_0019A5C8() >> 4) % 15 + 5;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 70) {
            o->w++;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b539:01E01D40, 136 insns: b388:01E005F0 family red glow spinning 0x4000 per tick, placed at the scene's point (until scene count 114) plus h52 fifths of the way from tracked point 3 to tracked point 2; outer alpha up by 24 to 0xC0 for 55 ticks, then down by 15 */

typedef struct {
    u8 pad0[0xB1D0];
    Vec4f at;
    u8 padB1E0[0xB248 - 0xB1E0];
    s16 id2;
    s16 id3;
    u8 padB24C[0xB2BC - 0xB24C];
    s16 count;
} Ctx_b539_01E01D40;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    u8 pad50[2];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b539_01E01D40;

static s32 func_01E01D40_b539(Ctx_b539_01E01D40 *g, Fx_b539_01E01D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];
    f32 f;
    f32 *q;

    if (o->mode == 1) {
        o->f4C = 10.0f;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->w = 10;
        o->h = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    func_001F5620(func_001F53A0(), g->id2, v);
    func_001F5620(func_001F53A0(), g->id3, q = (f32 *)(u32)&v[4]);
    v[0] = (v[0] - q[0]) / 5.0f;
    v[1] = (v[1] - v[5]) / 5.0f;
    v[2] = (v[2] - v[6]) / 5.0f;
    if (o->tick < 55) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x18;
        }
    } else if (o->col2[3] > 16) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    f = o->f52;
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    if (g->count < 114) {
        o->pos = g->at;
        o->pos.x += v[0] * f;
        o->pos.y += v[1] * f;
        o->pos.z += v[2] * f;
    }
    o->tick++;
    return 0;
}

/* shape b539:01E01F60, 194 insns: b539:01E01A50 twin, c063:01E04250 family red (0xFF, 0x40, 0x40) flake 30..59 square growing to 70, frame 0..2, drift /300, held 5..19 ticks, tumbling on all axes */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b539_01E01F60;

static s32 func_01E01F60_b539(s32 arg0, Fx_b539_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = (func_0019A5C8() >> 4) % 30 + 30;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 300.0f;
        o->vel[0] /= 300.0f;
        o->vel[2] /= 300.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->hold = (func_0019A5C8() >> 4) % 15 + 5;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 70) {
            o->w++;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b539:01E02270, 101 insns: a pale ring (height 15) pinned to the scene joint and pushed 2 along its heading (+0x52 x 20, sine table ctx+0xB4C0): in by 16 up to 0x80 for 102 ticks, then out by 19 and ends; spun 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b539_01E02270;

typedef struct {
    u8 pad[0xB24C];
    s16 joint;
    u8 padB24E[0xB4C0 - 0xB24E];
    u8 sin[1];
} Game_b539_01E02270;

static s32 func_01E02270_b539(Game_b539_01E02270 *g, Obj_b539_01E02270 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f4C = 15.0f;
        func_001076F0(o->col2, 0x48, 0x48, 0x48);
        func_001076F0(o->col, 0x60, 0x60, 0x30);
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, &o->x);
    o->z += 2.0f * func_00108030(g->sin, o->h52 * 20, 0);
    o->x += 2.0f * func_00108030(g->sin, o->h52 * 20, 1);
    if (o->t < 102) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x10;
        }
    } else if (o->col2[3] > 0x14) {
        o->col2[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b539:01E02410, 201 insns: b539:01E01F60 twin held 3..12 ticks and sinking 0.4 a tick; b539:01E01A50 twin, c063:01E04250 family red (0xFF, 0x40, 0x40) flake 30..59 square growing to 70, frame 0..2, drift /300, held 5..19 ticks, tumbling on all axes */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b539_01E02410;

static s32 func_01E02410_b539(s32 arg0, Fx_b539_01E02410 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = (func_0019A5C8() >> 4) % 30 + 30;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 300.0f;
        o->vel[0] /= 300.0f;
        o->vel[2] /= 300.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->hold = (func_0019A5C8() >> 4) % 10 + 3;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 70) {
            o->w++;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        o->pos[1] -= 0.4f;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b539:01E02740, 79 insns: a white growing spark (b252:01E03410 family): square size 40 growing by 1 to 70, random angle and
   sub-frame 0..3, random turn once; frame count 25: alpha up by 0x40 to 0x80, then down by 9 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1A];
    s16 sub2;
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 c0[4];
} Obj_b539_01E02740;

static s32 func_01E02740_b539(void *arg0, Obj_b539_01E02740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x28;
        o->h = o->w;
        o->sub = 0;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->hold = 0x19;
        o->sub2 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->w < 0x46) {
            o->w++;
        }
        o->h = o->w;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b539:01E02880, 65 insns: on start f48 6, colour 0xFF grey, second colour (0x80, 0x10, 0x10) with alpha 0, 0x30 = 25.0f,
   0x34 = 130.0f; alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and stops; 0x34 grows by 5.0f after the
   first tick; 0x5A advances 6 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b539_01E02880;

static s32 func_01E02880_b539(s32 arg0, Fx_b539_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->f30 = 25.0f;
        o->f34 = 130.0f;
        o->mode = 2;
        o->col2[3] = 0;
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
    if (o->tick != 0) {
        o->f34 += 5.0f;
    }
    o->tick++;
    o->f5A += 6;
    return 0;
}

/* shape b539:01E02990, 75 insns: a red spinning flash (b236:01E01B70 family): f48 3 growing by 5 with f4C 3 below; second alpha up
   by 0x60 to 0xC0 for 10 frames, then down by 15 until it ends; starts at a quarter x turn */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b539_01E02990;

static s32 func_01E02990_b539(void *arg0, Obj_b539_01E02990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 3.0f;
        func_001076F0(o->c1, 0xFF, 0x30, 0x30);
        func_001076F0(o->c0, 0xFF, 0x40, 0x40);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = 0x4000;
    }
    if (o->t < 0xA) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0x10) {
        o->c1[3] -= 0xF;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t != 0) {
        o->f48 += 5.0f;
    }
    o->f4C = o->f48 - 3.0f;
    o->t++;
    return 0;
}

/* shape b539:01E02AC0, 98 insns: on start colours and hold by kind (0x50); both alphas grow by 0x12 (below 0x80) during the
   hold, then fade by 5 (the first ends the effect) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b539_01E02AC0;

static s32 func_01E02AC0_b539(s32 arg0, Fx_b539_01E02AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0xF0);
            func_001076F0(o->col2, 0x80, 0x40, 0xF0);
            o->hold = 0xE;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
            o->hold = 0x14;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
            func_001076F0(o->col2, 0xF0, 0xE0, 0xFF);
            o->hold = 0x14;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x12;
        }
    } else {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 6) {
            o->col2[3] -= 5;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02C50_b539(void) {
    return 0;
}

/* shape b539:01E02C60 (b539), 564 insns, 1 copy: b539 scene manager in b585:01E02230 form: setup (six joints, two
   type-4 and two type-5 textures, 256 s8 and 30 s16 jitters), step B539_W_S (after frame 102 func_001F57B0(1)) and
   every slot but the empty handler, draw nine handler kinds (flakes, glows, rings, spark, flash, sprite at the camera
   point); scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    union {
        Vec4f v;
        Vec_b016_01E01190 c;
    } pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b539_01E02C60;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
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
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b539_01E02C60 fx[400];
    u8 padB1A0[0x50];
    s32 tex[4];
    u8 padB200[0x10];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x14];
    f32 depth;
    u8 padB238[0x10];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB254[4];
    s16 cam;
    u8 padB25A[0xE];
    s16 jit16[30];
    u8 padB2A4[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BE[0x102];
    u8 crd[0x170];
} Scene_b539_01E02C60;

static s32 func_01E02C60_b539(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001F57B0(s32);
    extern void func_01E01480_b539();
    Scene_b539_01E02C60 *g = (Scene_b539_01E02C60 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 164;
        g->jA = func_001F5560(func_001F53A0(), 0x21, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x22, 0);
        g->jC = func_001F5560(func_001F53A0(), 2, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x5B, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x61, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    if (g->frame > 102) {
        func_001F57B0(1);
    }
    func_01E01480_b539(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02C50_b539) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01A50_b539) {
                g->tex88 = g->tex[0];
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u94.uv[0] = g->fx[k].h56 << 6;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u94.uv[1] = 0x40;
                }
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                func_01E00C80_b539((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D40_b539) {
                g->hB8 = 0x24;
                func_01E00920_b539((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21, &g->fx[k].pos.c);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F60_b539) {
                g->tex88 = g->tex[0];
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u94.uv[0] = g->fx[k].h56 << 6;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u94.uv[1] = 0x40;
                }
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                func_01E00C80_b539((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02270_b539) {
                g->hB8 = 0x24;
                func_01E00920_b539((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21, &g->fx[k].pos.c);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02410_b539) {
                g->tex88 = g->tex[0];
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u94.uv[0] = g->fx[k].h56 << 6;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u94.uv[1] = 0x40;
                }
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                func_01E00C80_b539((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02740_b539) {
                g->tex88 = g->tex[1];
                g->hBE = 0;
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                func_01E00C80_b539((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos.v);
                func_01E00C80_b539((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02880_b539) {
                g->tex88 = g->tex260[15];
                func_00106080(rm2, 0x9A, 0, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hBE = 0;
                v = g->fx[k].pos.v;
                v.w = 0;
                func_01E00F40_b539((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos.v);
                func_01E00F40_b539((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02990_b539) {
                g->hB8 = 0x24;
                func_01E00920_b539((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21, &g->fx[k].pos.c);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02AC0_b539) {
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 50.0f;
                } else {
                    v.z += 50.0f;
                }
                func_00205440(&v, NULL, &pk[0x18], &g->depth);
                if (g->fx[k].h50 == 0) {
                    func_01E012B0_b539((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 1) {
                    func_01E012B0_b539((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
                if (g->fx[k].h50 == 2) {
                    func_01E012B0_b539((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 103) {
        return 1;
    }
    if (g->frame == 162) {
        return 4;
    }
    if (g->frame == 150) {
        return 2;
    }
    if (g->frame > 113 && g->frame < 145) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b539:01E03530, 106 insns, 4 copies: starts a particle: takes the first free one of 400 slots, clears it, gives
   it the emitter's two colours, position and timers and the two caller values; returns 0 when all are busy. */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 t0;
    s16 t1;
    u8 pad54[4];
    s16 used;
    s16 t2;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b539_01E03530;

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad0260[0x40];
    Slot_b539_01E03530 slots[400];
    u8 padB1A0[0x74];
    u8 col[4];
    u8 padB218[0x8E];
    s16 t2;
    u8 padB2A8[0xC];
    s16 t0;
} Emit_b539_01E03530;

static s32 func_01E03530_b539(Emit_b539_01E03530 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b539_01E03530 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 400;
        }
    }
    if (e != NULL) {
        func_001076F0(e->c0, o->col[0], o->col[1], o->col[2]);
        e->c0[3] = o->col[3];
        func_001076F0(e->c1, o->col[0], o->col[1], o->col[2]);
        e->c1[3] = o->col[3];
        func_00106AB0(e, &o->pos, 0);
        e->x = o->pos.x;
        e->y = o->pos.y;
        e->z = o->pos.z;
        e->t0 = o->t0;
        e->t1 = o->t0;
        e->t2 = o->t2;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}
