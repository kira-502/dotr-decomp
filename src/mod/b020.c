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

static void func_01E00080_b020(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b020_01E00920;

extern void b020_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00920_b020(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b020_01E00080(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
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

static void func_01E00E70_b020(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b020:01E011E0, 189 insns: b016:01E00ED0 with fixed blends (sel 0 = 0x42, 1 = 0x44, else 0x48) plus func_00109100(view, {.., .., cam 0x5A}, 2, obj 0xD8) after the view setup; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b020 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b020_01E011E0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x2A];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b020_01E011E0;

typedef struct Obj_b020_01E011E0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b020_01E011E0;

typedef struct Xyz_b020_01E011E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b020_01E011E0;

typedef struct Uv_b020_01E011E0 {
    f32 u, v;
} Uv_b020_01E011E0;

typedef struct Pk_b020_01E011E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b020_01E011E0 uv;
    u64 pad18;
    Xyz_b020_01E011E0 v[4];
    u64 pad60[6];
} Pk_b020_01E011E0;

typedef struct Buf_b020_01E011E0 {
    u64 tag;
    Pk_b020_01E011E0 pk;
} Buf_b020_01E011E0;

static void func_01E011E0_b020(Obj_b020_01E011E0 *obj, Cam_b020_01E011E0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b020_01E011E0 buf;
    Uv_b020_01E011E0 uv;
    s32 sel;
    s32 mode;
    Pk_b020_01E011E0 *p = &buf.pk;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b020((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    arg[2] = cam->f5A;
    func_00109100(view, arg, 2, obj->fD8);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b020 in the
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

static void func_01E014E0_b020(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b020((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b020:01E017A0, 233 insns: the b020 module's event step (b708:01E012D0 family): counts the frame (0x70B2); at
   1 spawns b020:01E022D0 at angles 0 and 90 (0x709E) and b020:01E023E0; each frame the point (0x250) sits on joint
   0x707C jittered by -10..9; from 160 to 310 spawns b020:01E01FC0 and 2 (4 from frame 100) b020:01E01B50 with the
   rolling slot 0x70AC (0..119, copied to 0x70AA); from 134 to 183 spawns 3 b020:01E01E70 at joint 0x7080 jittered and
   moved 50 along z (forward with the flag 0x70AE); b020:01E024C0 at 128 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x707C - 0x260];
    s16 j7C;
    u8 pad707E[2];
    s16 j80;
    u8 pad7082[0x709E - 0x7082];
    s16 ang;
    u8 pad70A0[0x70AA - 0x70A0];
    s16 slot;
    s16 roll;
    s16 flag;
    u8 pad70B0[2];
    s16 t;
} Scene_b020_01E017A0;

static void func_01E017A0_b020(Scene_b020_01E017A0 *g) {
    extern s32 b020_01E01B50(void);
    extern s32 b020_01E01E70(void);
    extern s32 b020_01E01FC0(void);
    extern s32 b020_01E022D0(void);
    extern s32 b020_01E023E0(void);
    extern s32 b020_01E024C0(void);
    extern void b020_01E02D90(Scene_b020_01E017A0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    g->t++;
    if (g->t == 1) {
        g->ang = 0;
        b020_01E02D90(g, b020_01E022D0, 0);
        g->ang = 90;
        b020_01E02D90(g, b020_01E022D0, 0);
        b020_01E02D90(g, b020_01E023E0, 0);
    }
    func_001F5620(func_001F53A0(), g->j7C, &g->pos);
    g->pos.x += func_0019A5C8() % 20 - 10;
    g->pos.y += func_0019A5C8() % 20 - 10;
    g->pos.z += func_0019A5C8() % 20 - 10;
    if (g->t >= 160 && g->t < 311) {
        b020_01E02D90(g, b020_01E01FC0, 0);
    }
    if (g->t >= 160 && g->t < 311 && g->t != 0) {
        if (g->t < 100) {
            n = 2;
        } else {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            g->slot = g->roll;
            b020_01E02D90(g, b020_01E01B50, 0);
            g->roll++;
            if (g->roll >= 120) {
                g->roll = 0;
            }
        }
    }
    if (g->t >= 134 && g->t < 184) {
        for (i = 0; i < 3; i++) {
            func_001F5620(func_001F53A0(), g->j80, &g->pos);
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            g->pos.z += func_0019A5C8() % 20 - 10;
            if (g->flag != 0) {
                g->pos.z += 50.0f;
            } else {
                g->pos.z -= 50.0f;
            }
            b020_01E02D90(g, b020_01E01E70, 0);
        }
    }
    if (g->t == 128) {
        b020_01E02D90(g, b020_01E024C0, 0);
    }
}

/* shape b020:01E01B50, 199 insns: b020:01E01FC0's drifting sprite with two grey (0x80) colours: on start size 5..34,
   0xE 0..7, variant 0..2, random drift (f10/f18 -20..19, f14 30, f30/f34/f38 random /10), random angle, second alpha 0;
   both alphas grow by 0x2A (below 0x80) for 16 ticks, then the first fades by 14 twice a tick and the sprite stops
   below 16; the rotation is handed to func_00205C40; after the first tick the angle turns by 4, f18 moves by f38 (down
   when the game flag 0x70AE is set) plus f34, f10 by f30 */

typedef struct {
    u8 pad0[0x70AE];
    s16 flag;
} Game_b020_01E01B50;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 fE;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0x18];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b020_01E01B50;

static s32 func_01E01B50_b020(Game_b020_01E01B50 *g, Fx_b020_01E01B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = func_0019A5C8() % 30 + 5;
        o->fA = o->f8;
        o->fE = func_0019A5C8() % 8;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->f10 = func_0019A5C8() % 40 - 20;
        o->f14 = 30.0f;
        o->f18 = func_0019A5C8() % 40 - 20;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 30;
        o->f38 = func_0019A5C8() % 100 + 30;
        o->f30 /= 10.0f;
        o->f34 /= 10.0f;
        o->f38 /= 10.0f;
        o->mode = 2;
        o->f5A = func_0019A5C8() % 360;
        o->col2[3] = 0;
    }
    if (o->tick < 16) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    if (o->tick != 0) {
        o->f5A += 4;
        if (o->f5A >= 360) {
            o->f5A %= 360;
        }
        if (g->flag != 0) {
            o->f18 -= o->f38;
        } else {
            o->f18 += o->f38;
        }
        o->f18 += o->f34;
        o->f10 += o->f30;
    }
    return 0;
}

/* shape b020:01E01E70, 81 insns: on start 0x8 = 10, 0xA = 1, variant 2..7, f34 0.5, colour white; alpha grows by 0x60
   (below 0xC0) for 15 ticks, then fades by 9 and stops; after the first tick f18 moves by 5 (down when the game flag
   0x70AE is set) 0x24 = 0x4000; stops once the game step 0x70B2 reaches 0xB8 */

typedef struct {
    u8 pad0[0x70AE];
    s16 flag;
    u8 pad70B0[2];
    s16 step;
} Game_b020_01E01E70;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0xC];
    f32 f18;
    u8 pad1C[8];
    s32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x1C];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b020_01E01E70;

static s32 func_01E01E70_b020(Game_b020_01E01E70 *g, Fx_b020_01E01E70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 10;
        o->fA = 1;
        o->f56 = func_0019A5C8() % 6 + 2;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
    }
    if (o->tick < 15) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (g->flag != 0) {
            o->f18 -= 5.0f;
        } else {
            o->f18 += 5.0f;
        }
    }
    o->f24 = 0x4000;
    o->tick++;
    if (g->step >= 0xB8) {
        o->mode = 0;
    }
    return 0;
}

/* shape b020:01E01FC0, 196 insns: on start f48 130, variant 0..6, colour (192, 192, 192), random angle/frame, 0x50
   5..14, random drift (f10/f18 -20..19, f14 30, f30/f34/f38 random /10), speed 9..23, hold 7..11; alpha 0x80 while
   held, then fades by 7 and stops; f48 grows by 2; after the first tick 0x50 += speed, f18 moves by f38 (down when
   the game flag 0x70AE is set) plus f34, f10 by f30 */

typedef struct {
    u8 pad0[0x70AE];
    s16 flag;
} Game_b020_01E01FC0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
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
} Fx_b020_01E01FC0;

static s32 func_01E01FC0_b020(Game_b020_01E01FC0 *g, Fx_b020_01E01FC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 130.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f10 = func_0019A5C8() % 40 - 20;
        o->f14 = 30.0f;
        o->f18 = func_0019A5C8() % 40 - 20;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 30;
        o->f38 = func_0019A5C8() % 100 + 30;
        o->f30 /= 10.0f;
        o->f34 /= 10.0f;
        o->f38 /= 10.0f;
        o->speed = func_0019A5C8() % 15 + 9;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 7;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->f48 += 2.0f;
    if (o->tick != 0) {
        o->f50 += o->speed;
        if (g->flag != 0) {
            o->f18 -= o->f38;
        } else {
            o->f18 += o->f38;
        }
        o->f18 += o->f34;
        o->f10 += o->f30;
    }
    o->tick++;
    return 0;
}

/* shape b020:01E022D0, 65 insns: on start f48 6, colour 0x80 grey, second colour (0x80, 0x10, 0x10) with alpha 0, 0x30 = 1.5f,
   0x34 = 5.0f; alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and stops; 0x34 grows by 4.0f after the
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
} Fx_b020_01E022D0;

static s32 func_01E022D0_b020(s32 arg0, Fx_b020_01E022D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->f30 = 1.5f;
        o->f34 = 5.0f;
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
        o->f34 += 4.0f;
    }
    o->tick++;
    o->f5A += 6;
    return 0;
}

/* shape b020:01E023E0, 53 insns: a white flash: set up once (white colours, size 2x2, scale 100), fades in by 0x60
   for 4 frames up to 0xC0, then out by 9 until it ends */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x3C];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b020_01E023E0;

static s32 func_01E023E0_b020(void *arg0, Obj_b020_01E023E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 6.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->w = 2;
        o->h = 2;
        o->scale = 100.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b020:01E024C0, 134 insns: b747:01E02B40 with the tint taken from the object's own colour (set to 0x90/0x78/0x78
   on start), and the fade-out once the game counter at g+0x70B2 reaches 325 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E024C0;

typedef struct {
    f32 s, t;
    Xyz_b020_01E024C0 p;
} Tv_b020_01E024C0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b020_01E024C0 v[2];
    u8 tail[0x20];
} Tex_b020_01E024C0;

typedef struct {
    u8 pad0[0x70B2];
    s16 count;
} Ctx_b020_01E024C0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b020_01E024C0;

static s32 func_01E024C0_b020(Ctx_b020_01E024C0 *g, Fx_b020_01E024C0 *o) {
    extern void func_002087A0(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    Tex_b020_01E024C0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
        func_001076F0(o->col, 0x90, 0x78, 0x78);
    }
    ((Tex_b020_01E024C0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b020_01E024C0 *)(s32)&pk)->size = 5;
    ((Tex_b020_01E024C0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b020_01E024C0 *)(s32)&pk)->pad4 = 0;
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
    if (g->count < 325) {
        if (o->col[3] < 0x50) {
            o->col[3] += 5;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b020:01E026E0 (b020), 427 insns, 1 copy: the b020 scene manager (b547:01E02510 / b292:01E02580 form): with a
   scene id it clears the scene, sets the 350-frame countdown, joints 0x15..0x17 and the camera, textures 4:15, 4:7
   and 5:0..2, the camera turn, scale 0.1 and the jitter tables; otherwise it runs the scene script b020:01E017A0 and
   every slot handler (250 of 0x70 bytes), draws sprites, gas, flames and the two eye kinds at joints A and B, counts
   down and returns the next step by frame (130, 335, 325, 141..319) or 8 when the countdown ends */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x1C];
    f32 f3C;
    u8 pad40[4];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b020_01E026E0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
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
        s16 uv[8];
    } u;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b020_01E026E0 fx[250];
    u8 pad7000[0x30];
    s32 tex2[3];
    u8 pad703C[0x14];
    s32 count;
    u8 pad7054[8];
    s32 ot;
    u8 pad7060[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 pad7082[8];
    s16 cam;
    u8 pad708C[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b020_01E026E0;

static void func_01E02EE0_b020(Obj_b020_01E011E0 *obj, Cam_b020_01E011E0 *cam, s32 flags, Vec4f c);

static s32 func_01E026E0_b020(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E017A0_b020();
    Scene_b020_01E026E0 *g = (Scene_b020_01E026E0 *)arg0;
    s32 k;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x7420);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 350;
        g->jA = func_001F5560(func_001F53A0(), 0x15, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x16, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x17, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 15; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        g->tex[7] = func_00202BF0(4, 7);
        for (k = 0; k < 3; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 4;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E017A0_b020(g, 0);
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == (s32 (*)())func_01E01B50_b020) {
                g->tex88 = g->tex[7];
                g->hBE = g->fx[i].f3C;
                g->u.uv[0] = 1;
                g->u.uv[1] = 1;
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                v.x = g->fx[i].pos.x;
                v.y = g->fx[i].pos.y;
                v.z = g->fx[i].pos.z;
                func_01E02EE0_b020((void *)g, (void *)&g->fx[i], 0x10, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01E70_b020) {
                g->tex88 = g->tex2[2];
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hBE = 5;
                v.x = g->fx[i].pos.x;
                v.y = g->fx[i].pos.y;
                v.z = g->fx[i].pos.z;
                func_01E014E0_b020((void *)g, (void *)&g->fx[i], 0x20, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01FC0_b020) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[0];
                g->hB8 = 5;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b020((void *)g, (void *)&g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E022D0_b020) {
                func_001F5620(func_001F53A0(), g->jA, &v);
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9A, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->hBE = 0;
                v.w = 0.0f;
                func_01E00E70_b020((void *)g, (void *)&g->fx[i], 0, v);
                func_001F5620(func_001F53A0(), g->jB, &v);
                func_01E00E70_b020((void *)g, (void *)&g->fx[i], 0, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E023E0_b020) {
                func_001F5620(func_001F53A0(), g->jA, &v);
                g->tex88 = g->tex2[1];
                func_00106080(rm4, 0x14, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm4;
                g->hBE = 0;
                v.w = 0.0f;
                func_01E011E0_b020((void *)g, (void *)&g->fx[i], 0x21, v);
                func_001F5620(func_001F53A0(), g->jB, &v);
                func_01E011E0_b020((void *)g, (void *)&g->fx[i], 0x21, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 130) {
        return 1;
    }
    if (g->frame == 335) {
        return 4;
    }
    if (g->frame == 325) {
        return 2;
    }
    if (g->frame > 140 && g->frame < 320) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b020:01E02D90, 82 insns: takes the first free of 250 effect slots (0x70 bytes, b089:01E030B0 shape), colours it from
   the context, places it at the context's position (copying it in), stores two frames and both arguments */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b020_01E02D90;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b020_01E02D90 slots[0xFA];
    u8 pad[0x7054 - 0x2A0 - 0xFA * 0x70];
    u8 rgba[4];
    u8 pad7058[0x46];
    s16 f709E;
    u8 pad70A0[0xA];
    s16 f70AA;
} Ctx_b020_01E02D90;

static s32 func_01E02D90_b020(Ctx_b020_01E02D90 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b020_01E02D90 *s = NULL;
    s16 i;

    for (i = 0; i < 0xFA; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x70);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0xFA;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c60[3] = ctx->rgba[3];
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->pos[0] = ctx->pos[0];
        s->pos[1] = ctx->pos[1];
        s->pos[2] = ctx->pos[2];
        s->f5A = ctx->f709E;
        s->f50 = ctx->f70AA;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b020:01E011E0, 189 insns: b016:01E00ED0 with fixed blends (sel 0 = 0x42, 1 = 0x44, else 0x48) plus func_00109100(view, {.., .., cam 0x5A}, 2, obj 0xD8) after the view setup; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b020 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

static void func_01E02EE0_b020(Obj_b020_01E011E0 *obj, Cam_b020_01E011E0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b020_01E011E0 buf;
    Uv_b020_01E011E0 uv;
    s32 sel;
    s32 mode;
    Pk_b020_01E011E0 *p = &buf.pk;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b020((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    arg[2] = cam->f5A;
    func_00109100(view, arg, 2, obj->fD8);
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

INCLUDE_ASM("asm/nonmatchings/mod/b020", func_01E03200_b020);
