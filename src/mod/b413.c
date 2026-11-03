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

static void func_01E00080_b413(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b413(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b413((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b413((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b413(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b413 in the
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

static void func_01E01230_b413(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b413((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E014F0_b413(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

static void func_01E01860_b413(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b413", func_01E01C60_b413);

/* shape b413:01E023D0, 110 insns: c062:01E033E0 family shock wave (yellow, scale 6): kind 0 from 470 growing 30 (width 40.5), kind 1 from 350 growing 10, kind 2 400 x 8 fixed; in by 64 up to 0x80 for 4 ticks, then out by 9 and ends; +0x52 counts to 25; spins 6 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
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
} Obj_b413_01E023D0;

static s32 func_01E023D0_b413(s32 arg0, Obj_b413_01E023D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        func_001076F0(o->col2, 0xFF, 0xFF, 0x40);
        if (o->h50 == 0) {
            o->f30 = 40.5f;
            o->f34 = 470.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 40.5f;
            o->f34 = 350.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->h52 = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 30.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 10.0f;
    }
    if (o->t != 0) {
        if (o->h52 < 25) {
            o->h52++;
        }
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b287_01E01FF0;

static s32 func_01E02590_b413(s32 unused, Obj_b287_01E01FF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 15 + 6;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 7;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x40;
        }
    } else if (o->c60[3] > 15) {
        o->c60[3] -= 14;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape b413:01E02740, 167 insns: b413:01E029E0 with size 2 x 40 growing 6 and hC growing 3.0 through a float */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    u8 padE[2];
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
    u8 pad5A[6];
    u8 col[4];
} Spark_b413_01E02740;

static s32 func_01E02740_b413(s32 arg0, Spark_b413_01E02740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 d;

    if (o->mode == 1) {
        o->w = 2;
        o->h = 40;
        o->hC = func_0019A5C8() % 5;
        o->kind = 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 20.0f;
        o->vel[0] /= 20.0f;
        o->vel[2] /= 20.0f;
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->hold = 6;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h += 6;
        d = 3.0f;
        o->hC = o->hC + d;
    }
    o->tick++;
    return 0;
}

/* shape b413:01E029E0, 161 insns: b205:01E01900 family yellow spark (size 2 x 10 growing 2, frame 2, hC 0..4 growing 3, drift in /20, random spins, frame f52 0..3, random turn) held 6 ticks: alpha up by 64 to 0x80, then down by 9 */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    u8 padE[2];
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
    u8 pad5A[6];
    u8 col[4];
} Spark_b413_01E029E0;

static s32 func_01E029E0_b413(s32 arg0, Spark_b413_01E029E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 2;
        o->h = 10;
        o->hC = func_0019A5C8() % 5;
        o->kind = 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 20.0f;
        o->vel[0] /= 20.0f;
        o->vel[2] /= 20.0f;
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->hold = 6;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h += 2;
        o->hC += 3;
    }
    o->tick++;
    return 0;
}

/* shape b413:01E02C70, 177 insns: a red (0xFF, 0x40, 0x40) streak 18 x 13, frame 0..2, drifting (-50..49)/100 with random spins; alpha up by 0x40 to 0x80 for 10 ticks, then down by 9; grows 5, 10 or 60 (and 3 wider) by the scene level (ctx+0xB2CC: under 90 / 121); turned +-0x4000 by the scene flag (ctx+0xB2C8) */

typedef struct {
    u8 pad0[0xB2C8];
    s16 flag;
    u8 padF[0xB2CC - 0xB2C8 - 2];
    s16 level;
} Ctx_b413_01E02C70;

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b413_01E02C70;

static s32 func_01E02C70_b413(Ctx_b413_01E02C70 *g, Fx_b413_01E02C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 18;
        o->h = 13;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 100.0f;
        o->vel[0] /= 100.0f;
        o->vel[2] /= 100.0f;
        o->f5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (g->level < 90) {
            o->h += 5;
        } else if (g->level < 121) {
            o->h += 10;
        } else {
            o->h += 60;
            o->w += 3;
        }
    }
    o->rot[1] = 0;
    o->rot[2] = 0;
    if (g->flag != 0) {
        o->rot[0] = 0x4000;
    } else {
        o->rot[0] = -0x4000;
    }
    o->tick++;
    return 0;
}

/* shape b413:01E02F40, 174 insns: b759:01E02D90's puff at size 100 in dull red (0x60/0x30/0x30), alpha grows for 8
   ticks, and it drifts by its velocity */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x14];
    s16 sel;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b413_01E02F40;

static s32 func_01E02F40_b413(s32 arg0, Spark_b413_01E02F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 100;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0x60, 0x30, 0x30);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        if (o->sel == 0) {
            o->vel[1] /= 25.0f;
            o->vel[0] /= 25.0f;
            o->vel[2] /= 25.0f;
        } else if (o->sel == 1) {
            o->vel[1] /= 45.0f;
            o->vel[0] /= 45.0f;
            o->vel[2] /= 45.0f;
        }
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->pos[0] += o->vel[0];
    o->pos[1] += o->vel[1];
    o->pos[2] += o->vel[2];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b413:01E03200, 117 insns: on start f48 120 with f4C 58 below it, colours by the kind 0x50 (0: (0x50, 0x30, 0x30) / (8, 8, 8),
   1: (0x30, 0x20, 0x40) / (0x18, 0x18, 0x18)), second alpha 0, 0x5A/0x5C = 30, rise speed 20..27.9 (f34), random rotation; alpha 0x80 for 8
   ticks, then fades by 5 and stops; f48 rises by the speed with f4C = 0.2 x f48 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[8];
    f32 speed;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b413_01E03200;

static s32 func_01E03200_b413(s32 arg0, Fx_b413_01E03200 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 120.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x50, 0x30, 0x30);
            func_001076F0(o->col2, 8, 8, 8);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0x30, 0x20, 0x40);
            func_001076F0(o->col2, 0x18, 0x18, 0x18);
        }
        o->f5A = 30;
        o->f5C = 30;
        o->speed = func_0019A5C8() % 80 + 200;
        o->speed /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < 8) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->f48 += o->speed;
    o->f4C = 0.2f * o->f48;
    o->tick++;
    return 0;
}

/* shape b413:01E033E0, 69 insns: constant variant of b287:01E02C80 (0xE->0xA, 150.0f->50.0f, colour (32, 192, 192), colour (255, 255, 128)) */

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
} Fx_b413_01E033E0;

static s32 func_01E033E0_b413(s32 arg0, Fx_b413_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 50.0f;
        func_001076F0(o->col2, 0x20, 0xC0, 0xC0);
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xA) {
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

/* shape b413:01E03500, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x83, floor 0x50, state at 0xB220 below 0x14 */

typedef struct {
    u8 pad[0xB220];
    s32 state;
} Game_b413_01E03500;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b413_01E03500;

static s32 func_01E03500_b413(Game_b413_01E03500 *g, Fade_b413_01E03500 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x83) {
        if (o->vol > 0x50) {
            o->vol -= 10;
        } else {
            o->vol = 0x50;
        }
    } else if (g->state < 0x14) {
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

typedef struct {
    u8 pad0000[0xB258];
    s16 joint[0x38];
    s16 flip;
} Mgr_b413_01E03610;

typedef struct {
    u8 pad00[0xA];
    s16 hA;
    u8 pad0C[4];
    f32 pos[2];
    f32 f18;
    u8 pad1C[0x18];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    u8 pad56[2];
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
} Obj_b413_01E03610;

static s32 func_01E03610_b413(Mgr_b413_01E03610 *m, Obj_b413_01E03610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->c60[3] = 0;
        o->c64[3] = 0x80;
        func_001076F0(o->c60, 0xC0, 0x80, 0x80);
        func_001076F0(o->c64, 0xC0, 0x80, 0x80);
        o->h58 = 2;
        func_001F5620(func_001F53A0(), m->joint[0], o->pos);
        if (m->flip != 0) {
            o->f34 = 7.0f;
        } else {
            o->f34 = -7.0f;
        }
        o->h5A = func_0019A5C8() % 360;
    }
    func_001F5620(func_001F53A0(), m->joint[o->h50], o->pos);
    if (m->flip != 0) {
        o->f18 -= 0.9f;
    } else {
        o->f18 += 0.9f;
    }
    o->f48 = 2.0f;
    o->hA += 6;
    if (o->h54 >= 6) {
        if (o->c60[3] > 30) {
            o->c60[3] -= 29;
        } else {
            o->h58 = 0;
        }
        if (o->c64[3] > 30) {
            o->c64[3] -= 29;
        } else {
            o->h58 = 0;
        }
    }
    o->h54++;
    return 0;
}

/* shape b413:01E037E0 (B413_OBJ_MOVE_203_1), 418 insns, 1 copy: c056:01E02BE0 ring as a wall: 36 quads of 10 degrees
   at radius 0x48 (height 0x34 to 0), at the object position; each sent quad gets screen texture coordinates from its
   corners, clamped to 640 x 448 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b413_01E037E0;

typedef struct {
    Rgbaq_b413_01E037E0 c;
    f32 s, t;
    u16 x, y;
    u32 z;
} Vtx_b413_01E037E0;

typedef struct {
    u8 pad0[0x10];
    Vtx_b413_01E037E0 v[4];
} Pkt_b413_01E037E0;

typedef struct {
    u8 pad0[0xA];
    s16 sx;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[0x34 - 0x1C];
    f32 z0;
    u8 pad38[0x48 - 0x38];
    f32 r;
    u8 pad4C[0x5A - 0x4C];
    s16 ang;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Obj_b413_01E037E0;

typedef struct {
    u8 pad0[0xB23C];
    Pkt_b413_01E037E0 *pk;
    u8 padB240[0xB4D0 - 0xB240];
    u8 sin[4];
} Scene_b413_01E037E0;

static s32 func_01E037E0_b413(Scene_b413_01E037E0 *g, Obj_b413_01E037E0 *o) {
    extern Rgbaq_b413_01E037E0 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f d;
    Vec4f q[4];
    Vec4f t;
    f32 m[16];
    f32 r;
    f32 c;
    f32 s;
    f32 x;
    f32 y;
    f32 u;
    f32 v;
    s16 i;
    s16 a;
    s16 k;

    a = 0;
    g->pk->v[0].c = func_00107740(o->col0);
    g->pk->v[1].c = func_00107740(o->col0);
    g->pk->v[2].c = func_00107740(o->col1);
    g->pk->v[3].c = func_00107740(o->col1);
    t.x = o->x;
    t.y = o->y;
    t.z = o->z;
    func_00108EF0(m, 0, 0, &t);
    r = o->r;
    q[0].z = o->z0;
    q[1].z = o->z0;
    q[2].z = 0.0f;
    q[3].z = 0.0f;
    for (i = 0; i < 36; i++) {
        k = o->ang + a;
        c = func_00108030(g->sin, k, 1);
        s = func_00108030(g->sin, k, 0);
        x = c * r;
        y = s * r;
        q[2].x = x;
        q[2].y = y;
        q[0].x = x;
        q[0].y = y;
        k = a + (o->ang + 10);
        c = func_00108030(g->sin, k, 1);
        s = func_00108030(g->sin, k, 0);
        x = c * r;
        y = s * r;
        q[3].x = x;
        q[3].y = y;
        q[1].x = x;
        q[1].y = y;
        a += 10;
        if (func_00205630(q, 0x70000000, m, g->pk, &d.x) != 0) {
            u = (((o->sx + 0x6C0) * 16 - 8) - g->pk->v[0].x);
            v = (0x71F8 - g->pk->v[0].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[0].s = u / 1024.0f;
            g->pk->v[0].t = v / 512.0f;
            u = (((o->sx + 0x6C0) * 16 - 8) - g->pk->v[1].x);
            v = (0x71F8 - g->pk->v[1].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[1].s = u / 1024.0f;
            g->pk->v[1].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[2].x);
            v = (0x71F8 - g->pk->v[2].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[2].s = u / 1024.0f;
            g->pk->v[2].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[3].x);
            v = (0x71F8 - g->pk->v[3].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[3].s = u / 1024.0f;
            g->pk->v[3].t = v / 512.0f;
            func_002075F0(g->pk, 0, 0);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b413", func_01E03E70_b413);

/* shape b413:01E04770, 106 insns: takes the first free of 400 effect slots (0x70 bytes, b041:01E02C00 shape),
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
} Slot_b413_01E04770;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b413_01E04770 slot[400];
    u8 padEnd[0xB224 - 0x2A0 - 400 * 0x70];
    u8 col[4];
    u8 padB228[0x8E];
    s16 hB2B6;
    u8 padB2B8[0xC];
    s16 hB2C4;
} Scene_b413_01E04770;

static s32 func_01E04770_b413(Scene_b413_01E04770 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b413_01E04770 *sl;
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
        sl->h50 = s->hB2C4;
        sl->h52 = s->hB2C4;
        sl->h5A = s->hB2B6;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b413:01E04920, 123 insns: b016:01E00ED0 sprite turned by {0, cam 0x5A, 0} via func_00109100 (mode 0),
   view [2][1] and [3][1] cleared, always drawn with the projected depth; draws one sprite quad at a position. */

typedef struct Cam_b413_01E04920 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x2A];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b413_01E04920;

typedef struct Obj_b413_01E04920 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b413_01E04920;

typedef struct Xyz_b413_01E04920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b413_01E04920;

typedef struct Uv_b413_01E04920 {
    f32 u, v;
} Uv_b413_01E04920;

typedef struct Pk_b413_01E04920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b413_01E04920 uv;
    u64 pad18;
    Xyz_b413_01E04920 v[4];
    u64 pad60[6];
} Pk_b413_01E04920;

typedef struct Buf_b413_01E04920 {
    u64 tag;
    Pk_b413_01E04920 pk;
} Buf_b413_01E04920;

static void func_01E04920_b413(Obj_b413_01E04920 *obj, Cam_b413_01E04920 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b413_01E04920 buf;
    Uv_b413_01E04920 uv;
    s32 sel;
    Pk_b413_01E04920 *p = &buf.pk;

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
    func_01E00080_b413((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    arg[0] = 0;
    arg[1] = cam->f5A;
    arg[2] = 0;
    func_00109100(view, arg, 0, obj->fD8);
    view[2][1] = 0.0f;
    view[3][1] = 0.0f;
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b282:01E03460, 195 insns, 3 copies: draws crossed sprite planes at a position: kind 0 one ring of two planes 90
   apart, kind 1 ten rings 36 apart of one plane each; blend from flags >> 4. Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b282_01E03460;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b282_01E03460 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b282_01E03460;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[0xC];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b282_01E03460;

typedef struct {
    u8 pad00[8];
    s16 w, h, y;
    u8 padE[0x12];
    Vec4f rot;
    u8 pad30[0x2A];
    s16 a5A;
    s16 a5C;
    u8 pad5E[2];
    u8 col[4];
} Spr_b282_01E03460;

static void func_01E04B10_b413(Obj_b282_01E03460 *o, Spr_b282_01E03460 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b282_01E03460 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 r1[4];
    s32 r2[4];
    Pkt_b282_01E03460 pkt __attribute__((aligned(8)));
    Pkt_b282_01E03460 *p;
    s32 b;
    s32 n;
    s32 j;
    s32 m2;
    s32 i;
    f32 y;

    b = (flags >> 4) & 0xF;
    p = (Pkt_b282_01E03460 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00080_b413((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    r1[0] = 0;
    r1[2] = 0;
    if (o->kind == 0) {
        n = 1;
    }
    if (o->kind == 1) {
        n = 10;
    }
    if (o->kind == 0) {
        m2 = 2;
    }
    if (o->kind == 1) {
        m2 = 1;
    }
    for (i = 0; i < n; i++) {
        r2[1] = 0;
        r2[0] = s->a5C + i * 36;
        r2[2] = 0;
        y = s->y;
        for (j = 0; j < m2; j++) {
            func_00108CE0(quad, s->w, s->h);
            r1[0] = 0;
            r1[1] = s->a5A + j * 90;
            r1[2] = 0;
            quad[2].y = 0.0f;
            quad[3].y = 0.0f;
            func_00109100(quad, r1, 0, o->xD8);
            func_00107070(quad, 1, y);
            func_00109100(quad, r2, 1, o->xD8);
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
}

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x48];
} PktA_b413_01E04E20;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x68];
    u64 a;
    s32 b[4];
} PktB_b413_01E04E20;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 state;
    u8 pad5A[0x16];
} Ent_b413_01E04E20;

typedef struct {
    u8 pad0000[0x2A0];
    Ent_b413_01E04E20 ents[400];
    u8 pad[0xB234 - 0x2A0 - 400 * 0x70];
    s32 list;
    PktA_b413_01E04E20 *pa;
    PktB_b413_01E04E20 *pb;
} Mgr_b413_01E04E20;

static void func_01E04E20_b413(Mgr_b413_01E04E20 *m) {
    extern void b413_01E03610(Mgr_b413_01E04E20 *, Ent_b413_01E04E20 *);
    extern void b413_01E037E0(Mgr_b413_01E04E20 *, Ent_b413_01E04E20 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    PktA_b413_01E04E20 a __attribute__((aligned(8)));
    PktB_b413_01E04E20 b __attribute__((aligned(8)));
    PktB_b413_01E04E20 *p;
    s32 i;

    m->pa = &a;
    m->pb = &b;
    m->list = func_00207F60();
    m->pa->count = 0x26;
    m->pa->tag = 5;
    m->pa->regs = 0x42421;
    m->pa->pad = 0;
    m->pb->count = 0x34;
    m->pb->tag = 0xC;
    m->pb->regs = ((u64)0x4214 << 32) | 0x21421421;
    m->pb->pad = 0;
    func_00208460();
    func_002086D0(m->pb, ((u64)0x80 << 32) | 0x44);
    p = m->pb;
    func_00208800(func_00209E50(), 0, &p->a, p->b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (m->ents[i].state == 0) {
            continue;
        }
        if (m->ents[i].cb == (void *)b413_01E03610) {
            b413_01E03610(m, &m->ents[i]);
            b413_01E037E0(m, &m->ents[i]);
        }
    }
    func_00207FD0(m->list, func_00207500(), 0);
}
