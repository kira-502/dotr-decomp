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

static void func_01E00080_b377(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b377(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b377 in the
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

static void func_01E00C80_b377(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b377((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00F40_b377(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

static void func_01E01350_b377(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b377:01E016C0 (B377_W_S), 376 insns, 1 copy: B377_W_S, the effect scene step (b235:01E01C70 form): counts the
   frame (0xB2BC); frames 28..224 spawn 0x1E01CA0 on sides 0,6,12.. for each of n (n grows every 5th frame up to 11);
   frames 0..11 spawn 0x1E01F60 on side m++; frame 195 takes joint 0xB244 point, 193 the camera point; frames 193..234
   put the point 20 under it and spawn 0x1E02320 on sides 0/1 (odd) and 2 (even); frame 1 spawns four 0x1E027B0
   (angles 0/90/45/135), 0x1E02C80 and 0x1E02A50; frames 118/191 and 141/191 spawn ten 0x1E02150 around joints
   0xB248/0xB24A */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f pt;
    u8 padB1E0[0xB244 - 0xB1E0];
    s16 joint0;
    u8 padB246[2];
    s16 joint1;
    s16 joint2;
    u8 padB24C[0xB2A2 - 0xB24C];
    s16 ang;
    u8 padB2A4[0xB2AE - 0xB2A4];
    s16 m;
    s16 n;
    u8 padB2B2[2];
    s16 side;
    u8 padB2B6[2];
    s16 flag;
    u8 padB2BA[2];
    s16 t;
} Scene_b377_01E016C0;

static void func_01E016C0_b377(Scene_b377_01E016C0 *g) {
    extern void b377_01E01CA0(void);
    extern void b377_01E01F60(void);
    extern void b377_01E02150(void);
    extern void b377_01E02320(void);
    extern void b377_01E027B0(void);
    extern void b377_01E02A50(void);
    extern void b377_01E02C80(void);
    extern void b377_01E036F0(Scene_b377_01E016C0 *, void (*)(void), s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;
    s16 j;

    g->t++;
    if (g->t > 27 && g->t < 225) {
        for (i = 0, j = 0; i < g->n; j += 6, i++) {
            g->side = j;
            b377_01E036F0(g, b377_01E01CA0, 0);
        }
        if (g->t % 5 == 0 && g->n < 11) {
            g->n++;
        }
    }
    if (g->t < 12) {
        g->side = g->m;
        b377_01E036F0(g, b377_01E01F60, 0);
        g->m++;
    }
    if (g->t == 195) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pt);
    }
    if (g->t == 193) {
        func_001F5F90(func_001F5380(), &g->pt);
    }
    if (g->t >= 193 && g->t < 235) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pos);
        g->pos.y = 40.0f;
        if (g->flag) {
            g->pos.z -= 4.0f;
        } else {
            g->pos.z += 4.0f;
        }
        g->pos = g->pt;
        g->pos.y -= 20.0f;
        g->side = 0;
        if (g->t % 2 == 1) {
            b377_01E036F0(g, b377_01E02320, 0);
        }
        g->side = 1;
        if (g->t % 2 == 1) {
            b377_01E036F0(g, b377_01E02320, 0);
        }
        g->side = 2;
        if (g->t % 2 == 0) {
            b377_01E036F0(g, b377_01E02320, 0);
        }
    }
    if (g->t == 1) {
        g->ang = 0;
        g->side = 0;
        b377_01E036F0(g, b377_01E027B0, 0);
        g->ang = 90;
        g->side = 0;
        b377_01E036F0(g, b377_01E027B0, 0);
        g->ang = 45;
        g->side = 1;
        b377_01E036F0(g, b377_01E027B0, 0);
        g->ang = 135;
        g->side = 1;
        b377_01E036F0(g, b377_01E027B0, 0);
        b377_01E036F0(g, b377_01E02C80, 0);
        b377_01E036F0(g, b377_01E02A50, 0);
    }
    if (g->t == 118 || g->t == 191) {
        func_001F5620(func_001F53A0(), g->joint1, &g->pos);
        for (j = 0, i = 0; j < 10; i += 36, j++) {
            g->ang = i;
            b377_01E036F0(g, b377_01E02150, 0);
        }
    }
    if (g->t == 141 || g->t == 191) {
        func_001F5620(func_001F53A0(), g->joint2, &g->pos);
        for (j = 0, i = 0; j < 10; i += 36, j++) {
            g->ang = i;
            b377_01E036F0(g, b377_01E02150, 0);
        }
    }
}

/* shape b377:01E01CA0, 174 insns: b411:01E015C0's spark in dark blue (0x20/0x20/0x80), size 8..27, hold 1..2; each tick
   it sits at joint 0xB244 moved k fiftieths (0x52) of the way to joint 0xB246, and the size grows by 2 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    f32 pos[3];
    u8 pad1C[0x2C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 k;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b377_01E01CA0;

typedef struct {
    u8 pad0[0xB244];
    s16 ja;
    s16 jb;
} Scene_b377_01E01CA0;

static s32 func_01E01CA0_b377(Scene_b377_01E01CA0 *g, Fx_b377_01E01CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    f32 k;

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 8;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->ja, o->pos);
    func_001F5620(func_001F53A0(), g->jb, &v);
    v.x = (v.x - o->pos[0]) / 50.0f;
    v.y = (v.y - o->pos[1]) / 50.0f;
    v.z = (v.z - o->pos[2]) / 50.0f;
    o->pos[0] += v.x * (k = o->k);
    o->pos[1] += v.y * k;
    o->pos[2] += v.z * k;
    func_0019A5C8();
    if (o->tick != 0) {
        o->f48 += 2.0f;
    }
    if (o->tick != 0 && o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b377:01E01F60 (B377_OBJ_MOVE_3_), 124 insns, 1 copy: b235:01E02370's joint-to-joint glow: on start size 30 +
   6 * n, grey 0x40 and purple 0x30/0x10/0x60 colours; alpha up by 19 to 0xC0 for 140 frames, then down by 9 until it
   ends; sits on joint 0 moved n tenths of the way to joint 1, spins by 0x4000 */

typedef struct {
    u8 pad0[0xB244];
    s16 j0;
    s16 j1;
} Game_b377_01E01F60;

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0x28];
    f32 size;
    s16 kind;
    s16 f52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b377_01E01F60;

#pragma opt_propagation off

static s32 func_01E01F60_b377(Game_b377_01E01F60 *g, Obj_b377_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00205C40(void *);
    f32 d[3];
    f32 k;

    if (o->state == 1) {
        k = o->kind;
        o->size = 30.0f + 6.0f * k;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        func_001076F0(o->c1, 0x30, 0x10, 0x60);
        o->f52 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x8C) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x13;
        }
    } else if (o->c1[3] > 0xA) {
        o->c1[3] -= 9;
    } else {
        o->state = 0;
    }
    func_001F5620(func_001F53A0(), g->j0, &o->x);
    func_001F5620(func_001F53A0(), g->j1, d);
    d[0] = (d[0] - o->x) / 10.0f;
    d[1] = (d[1] - o->y) / 10.0f;
    d[2] = (d[2] - o->z) / 10.0f;
    k = o->kind;
    o->x += d[0] * k;
    o->y += d[1] * k;
    o->z += d[2] * k;
    func_00205C40(&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}
#pragma opt_propagation reset


typedef struct {
    u8 pad0000[0xB4C0];
    u8 tab[1];
} Mgr_b377_01E02150;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b377_01E02150;

static s32 func_01E02150_b377(Mgr_b377_01E02150 *m, Obj_b377_01E02150 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 40;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h58 = 2;
        o->f18 += 2.0f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 2.0f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 19;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f18 += 0.5f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.5f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b377:01E02320, 290 insns (B377_OBJ_MOVE_6_): a growing ring by kind (0x50): on start width 140 / height 82,
   colours by kind and the scene's frame parity (purple / blue / pink, lighter on odd frames), hold 8 or 10, sizes
   10/10, 10/3 or 60/60, growth (350..429)/10, spin 35, a random turn; full alpha while held, then fades by 5; each
   tick the width grows (height 0.4 or 0.7 of it) and kinds 1/2 also climb */

typedef struct {
    u8 pad0[0xB2BC];
    s16 frame;
} Game_b377_01E02320;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x1C];
    s32 turn;
    u8 pad28[8];
    f32 spin;
    f32 y;
    f32 grow;
    u8 pad3C[0xC];
    f32 w;
    f32 h;
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
} Obj_b377_01E02320;

static s32 func_01E02320_b377(Game_b377_01E02320 *g, Obj_b377_01E02320 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 140.0f;
        o->h = o->w - 58.0f;
        if (o->kind == 0) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x80, 0x20, 0xC0);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x80, 0x40, 0xFF);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->hold = 8;
        }
        if (o->kind == 1) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0x60, 0x20, 0x80);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0x80, 0x40, 0xFF);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->y = 10.0f;
            o->hold = 10;
        }
        if (o->kind == 2) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0xC0, 0x80, 0x80);
                func_001076F0(o->col, 0x10, 0x10, 0x10);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->y = 10.0f;
            o->hold = 10;
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
        o->grow /= 10.0f;
        o->spin = 350.0f;
        o->spin /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->turn = func_0019A5C8() % 65535;
    }
    if (o->t < o->hold) {
        o->col2[3] = 0x80;
    } else if (o->col2[3] > 6) {
        o->col2[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->w += o->grow;
        o->h = 0.4f * o->w;
    }
    if (o->kind == 1) {
        o->w += o->grow;
        o->h = 0.7f * o->w;
        o->y += o->grow;
    }
    if (o->kind == 2) {
        o->w += o->grow;
        o->h = 0.7f * o->w;
        o->y += o->grow;
    }
    o->t++;
    return 0;
}

/* shape b377:01E027B0, 165 insns: b292:01E01C90 with the joints at 0xB244 */

typedef struct {
    u8 pad0[0xB244];
    s16 j0;
    s16 j1;
} World_b377_01E027B0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x10];
    f32 thick;
    f32 radius;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    s16 step;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Ring_b377_01E027B0;

static s32 func_01E027B0_b377(World_b377_01E027B0 *w, Ring_b377_01E027B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    Vec4f v[2];
    f32 k;

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->thick = 3.0f;
            o->radius = 70.0f;
        }
        if (o->kind == 1) {
            o->thick = 3.0f;
            o->radius = 30.0f;
        }
        if (o->kind == 2) {
            o->thick = 8.0f;
            o->radius = 400.0f;
        }
        o->state = 2;
        o->c1[3] = 0;
        o->step = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->kind == 0 && o->t != 0) {
        o->radius += 30.0f;
    }
    if (o->kind == 1 && o->t != 0) {
        o->radius += 10.0f;
    }
    if (o->t != 0) {
        if (o->step < 0x19) {
            o->step++;
        }
    }
    o->t++;
    o->ang += 6;
    func_001F5620(func_001F53A0(), w->j0, &o->pos);
    func_001F5620(func_001F53A0(), w->j1, v);
    k = o->step;
    v[0].x = (v[0].x - o->pos.x) / 25.0f;
    v[0].y = (v[0].y - o->pos.y) / 25.0f;
    v[0].z = (v[0].z - o->pos.z) / 25.0f;
    o->pos.x += v[0].x * k;
    o->pos.y += v[0].y * k;
    o->pos.z += v[0].z * k;
    return 0;
}

/* shape b377:01E02A50, 136 insns: b490:01E00E90's scene light at g+0xB1A0 on a model joint: on start colour 128/400/2/0,
   height 0/123/0 and the effect's position; each tick the light follows the joint at g+0xB244; its strength rises by
   0.3 up to 1 for 210 ticks, then falls by 0.3 until it ends; func_001F6C10 gets the light (or 0 once ended); it
   also ends when the scene word at g+0xB210 is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x44];
    s32 state;
} Light_b377_01E02A50;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b377_01E02A50 light;
    u8 padB214[0x30];
    s16 joint;
} Game_b377_01E02A50;

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
} Fx_b377_01E02A50;

static s32 func_01E02A50_b377(Game_b377_01E02A50 *g, Fx_b377_01E02A50 *o) {
    extern void func_001F6C10(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[8];

    if (o->mode == 1) {
        g->light.a[0] = 128.0f;
        g->light.a[1] = 400.0f;
        g->light.a[2] = 2.0f;
        g->light.a[3] = 0.0f;
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
    if (o->t < 210) {
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
    if (g->light.state == 1) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b377:01E02C80, 179 insns: b702:01E02AD0's veil (0x80/0x70/0x90, 0x90/0x80/0xA0 on scene frame 190) on the scene
   frame at 0xB2BC: from frame 191 it zooms by 0.3 to 5 and its alpha also climbs by 26 to 0x68; it fades from frame 250 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b377_01E02C80;

typedef struct {
    f32 s, t;
    Xyz_b377_01E02C80 p;
} Tv_b377_01E02C80;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b377_01E02C80 v[2];
    u8 tail[0x20];
} Tex_b377_01E02C80;

typedef struct {
    u8 pad0[0xB2BC];
    s16 count;
} Ctx_b377_01E02C80;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b377_01E02C80;

static s32 func_01E02C80_b377(Ctx_b377_01E02C80 *g, Fx_b377_01E02C80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b377_01E02C80 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x70, 0x90);
        o->mode = 2;
    }
    if (g->count == 190) {
        func_001076F0(o->col, 0x90, 0x80, 0xA0);
    }
    ((Tex_b377_01E02C80 *)(s32)&pk)->flags = 0x26;
    ((Tex_b377_01E02C80 *)(s32)&pk)->size = 5;
    ((Tex_b377_01E02C80 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b377_01E02C80 *)(s32)&pk)->pad4 = 0;
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
    if (g->count > 190) {
        if (o->f48 < 5.0f) {
            o->f48 += 0.3f;
        }
    }
    if (g->count < 250) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
        if (g->count > 190) {
            if (o->col[3] < 0x68) {
                o->col[3] += 26;
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

static s32 func_01E02F50_b377(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b377", func_01E02F60_b377);

/* shape b377:01E036F0, 106 insns: takes the first free of 400 effect slots (0x70 bytes, b041:01E02C00 shape),
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
} Slot_b377_01E036F0;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b377_01E036F0 slot[400];
    u8 padEnd[0xB214 - 0x2A0 - 400 * 0x70];
    u8 col[4];
    u8 padB218[0x8A];
    s16 hB2A2;
    u8 padB2A4[0x10];
    s16 hB2B4;
} Scene_b377_01E036F0;

static s32 func_01E036F0_b377(Scene_b377_01E036F0 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b377_01E036F0 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 400; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 400;
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
        sl->h50 = s->hB2B4;
        sl->h52 = s->hB2B4;
        sl->h5A = s->hB2A2;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b377:01E038A0 (IW377_MagicGas1), 364 insns, 1 copy: b363:01E00BB0 (IWMagicGas1) with the view x scale doubled
   in mode 0 (cam->f48 * 2); texture corners by the module helper func_01E00080_b377 */


typedef struct Cam_b377_01E038A0 {
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
} Cam_b377_01E038A0;

typedef struct Obj_b377_01E038A0 {
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
} Obj_b377_01E038A0;

typedef struct Uv_b377_01E038A0 {
    f32 u, v;
} Uv_b377_01E038A0;

typedef struct Xyz_b377_01E038A0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b377_01E038A0;

typedef struct Pk_b377_01E038A0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b377_01E038A0 uv;
    u64 pad18;
    Xyz_b377_01E038A0 v[4];
    u64 pad60[6];
} Pk_b377_01E038A0;

typedef struct Buf_b377_01E038A0 {
    u64 tag;
    Pk_b377_01E038A0 pk;
} Buf_b377_01E038A0;

static void func_01E038A0_b377(Obj_b377_01E038A0 *obj, Cam_b377_01E038A0 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b377_01E038A0 *p;
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
    Buf_b377_01E038A0 buf;
    Uv_b377_01E038A0 uv;

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
    func_01E00080_b377((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b377((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, 2.0f * cam->f48);
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
