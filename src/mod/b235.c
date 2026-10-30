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

static void func_01E00080_b235(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b235(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b235((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b235((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b235(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b235 in the
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

static void func_01E01230_b235(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b235((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E014F0_b235(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

static void func_01E01860_b235(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

/* shape b235:01E01C70 (B235_W_S), 327 insns, 1 copy: B235_W_S, the effect scene step (b286:01E004D0 form): counts the
   frame (0xB2BA); frame 1 spawns 0x1E03200, 0x1E03310, 0x1E02FE0 and four 0x1E02B70 (angles 0/90/45/135, sides
   0/0/1/1); frames 0..11 spawn 0x1E02370 on side n++; frames 118..138 put the point 13 under the model, spawn three
   0x1E02190, 0x1E026E0 on sides 0/1 (odd frames) and 2 (even) and 0x1E02560; frames 118..130 again point and
   0x1E02560; frames 50/72 and 61/82 put the point 1.5 under joint 0xB248 and spawn thirteen 0x1E02E10 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB248 - 0x260];
    s16 joint;
    u8 padB24A[0xB2A2 - 0xB24A];
    s16 ang;
    u8 padB2A4[2];
    s16 n;
    u8 padB2A8[0xB2B2 - 0xB2A8];
    s16 side;
    u8 padB2B4[0xB2BA - 0xB2B4];
    s16 t;
} Scene_b235_01E01C70;

static void func_01E01C70_b235(Scene_b235_01E01C70 *g) {
    extern void b235_01E02190(void);
    extern void b235_01E02370(void);
    extern void b235_01E02560(void);
    extern void b235_01E026E0(void);
    extern void b235_01E02B70(void);
    extern void b235_01E02E10(void);
    extern void b235_01E02FE0(void);
    extern void b235_01E03200(void);
    extern void b235_01E03310(void);
    extern void b235_01E03DE0(Scene_b235_01E01C70 *, void (*)(void), s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;

    g->t++;
    if (g->t == 1) {
        b235_01E03DE0(g, b235_01E03200, 0);
    }
    if (g->t == 1) {
        b235_01E03DE0(g, b235_01E03310, 0);
    }
    if (g->t == 1) {
        b235_01E03DE0(g, b235_01E02FE0, 0);
    }
    if (g->t < 12) {
        g->side = g->n;
        b235_01E03DE0(g, b235_01E02370, 0);
        g->n++;
    }
    if (g->t == 1) {
        g->ang = 0;
        g->side = 0;
        b235_01E03DE0(g, b235_01E02B70, 0);
        g->ang = 90;
        g->side = 0;
        b235_01E03DE0(g, b235_01E02B70, 0);
        g->ang = 45;
        g->side = 1;
        b235_01E03DE0(g, b235_01E02B70, 0);
        g->ang = 135;
        g->side = 1;
        b235_01E03DE0(g, b235_01E02B70, 0);
    }
    if (g->t >= 118 && g->t < 139) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y -= 13.0f;
        for (i = 1; i < 4; i++) {
            b235_01E03DE0(g, b235_01E02190, 0);
        }
        g->side = 0;
        if (g->t % 2 == 1) {
            b235_01E03DE0(g, b235_01E026E0, 0);
        }
        g->side = 1;
        if (g->t % 2 == 1) {
            b235_01E03DE0(g, b235_01E026E0, 0);
        }
        g->side = 2;
        if (g->t % 2 == 0) {
            b235_01E03DE0(g, b235_01E026E0, 0);
        }
        b235_01E03DE0(g, b235_01E02560, 0);
    }
    if (g->t >= 118 && g->t < 131) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y -= 13.0f;
        b235_01E03DE0(g, b235_01E02560, 0);
    }
    if (g->t == 50 || g->t == 72) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b235_01E03DE0(g, b235_01E02E10, 0);
        }
    }
    if (g->t == 61 || g->t == 82) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b235_01E03DE0(g, b235_01E02E10, 0);
        }
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b235_01E02190;

typedef struct {
    u8 pad0000[0xD930];
    Vec_b235_01E02190 pts[1];
} Mgr_b235_01E02190;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    Vec_b235_01E02190 pos;
    u8 pad20[0x28];
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
} Obj_b235_01E02190;

static s32 func_01E02190_b235(s32 unused, Obj_b235_01E02190 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 20 + 15;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->c60, 0x80, 0x60, 0x70);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h52 = (func_0019A5C8() >> 8) % 10 - 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 40 + 26;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
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
    o->h5A += o->h52;
    o->h54++;
    return 0;
}

/* shape b235:01E02370, 124 insns: a glow sliding between two model joints: on start size 15 + 5 per kind, colours 24/24/24
   and 48/16/32, alpha up by 19 to 0xC0 for 140 frames, then down by 9 until it ends; each frame it sits on joint 0 and moves
   a tenth of the way to joint 1 per kind step, and spins by 0x4000 */

typedef struct {
    u8 pad0[0xB244];
    s16 j0;
    s16 j1;
} Game_b235_01E02370;

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
} Obj_b235_01E02370;

#pragma opt_propagation off

static s32 func_01E02370_b235(Game_b235_01E02370 *g, Obj_b235_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00205C40(void *);
    f32 d[3];
    f32 k;

    if (o->state == 1) {
        k = o->kind;
        o->size = 15.0f + 5.0f * k;
        func_001076F0(o->c0, 0x18, 0x18, 0x18);
        func_001076F0(o->c1, 0x30, 0x10, 0x20);
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

/* shape b235:01E02560, 96 insns: a red-grey expanding ring: sizes 11 growing by 10 with the outer one four times it, random angle
   and turn, rise 15..44 growing by 20; alpha up by 0x60 for 4 frames, then down by 19 until it ends */

typedef struct {
    u8 pad0[0x24];
    s32 rot1;
    u8 pad28[0xC];
    f32 rise;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 ang;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b235_01E02560;

static s32 func_01E02560_b235(void *arg0, Obj_b235_01E02560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = o->f4C = 11.0f;
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        func_001076F0(o->c0, 0x80, 0x40, 0x40);
        o->ang = func_0019A5C8() % 360;
        o->h5A = 0x3C;
        o->h5C = 6;
        o->state = 2;
        o->c1[3] = 0;
        o->rise = func_0019A5C8() % 30 + 0xF;
        o->rot1 = func_0019A5C8() % 65535;
    }
    if (o->t < 4) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0x14) {
        o->c1[3] -= 0x13;
    } else {
        o->state = 0;
    }
    o->rise += 20.0f;
    o->f48 += 10.0f;
    o->f4C = 4.0f * o->f48;
    o->t++;
    return 0;
}

/* shape b235:01E026E0, 290 insns: a growing ring in three kinds; on start size 140 (inner 82), colours by kind and by
   the scene's odd/even flag at ctx+0xB2BA (violet/blue, dark/light purple, pink/light pink), a fade-in time of 8 or 10,
   quad sizes 10x10 / 10x3 / 60x60, growth (450..529)/10 and spin speed 35, random angle; then full alpha until the
   fade-in time, fading by 5 after, and the ring grows (inner 0.4 or 0.7 of it; kinds 1 and 2 also widen) */

typedef struct {
    u8 pad0[0xB2BA];
    s16 flip;
} Game_b235_01E026E0;

typedef struct {
    u8 pad0[6];
    s16 fade;
    u8 pad8[0x1C];
    s32 rot;
    u8 pad28[8];
    f32 spin;
    f32 wide;
    f32 grow;
    u8 pad3C[0xC];
    f32 size;
    f32 inner;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b235_01E026E0;

static s32 func_01E026E0_b235(Game_b235_01E026E0 *g, Obj_b235_01E026E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 140.0f;
        o->inner = o->size - 58.0f;
        if (o->kind == 0) {
            if (g->flip % 2 == 0) {
                func_001076F0(o->c1, 0x80, 0x20, 0xC0);
                func_001076F0(o->c0, 0, 0, 0);
            }
            if (g->flip % 2 == 1) {
                func_001076F0(o->c1, 0x80, 0x40, 0xFF);
                func_001076F0(o->c0, 0x30, 0x30, 0x30);
            }
            o->fade = 8;
        }
        if (o->kind == 1) {
            if (g->flip % 2 == 0) {
                func_001076F0(o->c1, 0x60, 0x20, 0x80);
                func_001076F0(o->c0, 0, 0, 0);
            }
            if (g->flip % 2 == 1) {
                func_001076F0(o->c1, 0x80, 0x40, 0xFF);
                func_001076F0(o->c0, 0x30, 0x30, 0x30);
            }
            o->wide = 100.0f;
            o->fade = 10;
        }
        if (o->kind == 2) {
            if (g->flip % 2 == 0) {
                func_001076F0(o->c1, 0xC0, 0x80, 0x80);
                func_001076F0(o->c0, 0x10, 0x10, 0x10);
            }
            if (g->flip % 2 == 1) {
                func_001076F0(o->c1, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->c0, 0x30, 0x30, 0x30);
            }
            o->wide = 100.0f;
            o->fade = 10;
        }
        if (o->kind == 0) {
            o->w = 10;
            o->h = 10;
        }
        if (o->kind == 1) {
            o->w = 10;
            o->h = 3;
        }
        if (o->kind == 2) {
            o->w = 60;
            o->h = 60;
        }
        o->grow = func_0019A5C8() % 80 + 450;
        o->grow /= 10.0f;
        o->spin = 350.0f;
        o->spin /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot = func_0019A5C8() % 0xFFFF;
    }
    if (o->t < o->fade) {
        o->c1[3] = 0x80;
    } else if (o->c1[3] > 6) {
        o->c1[3] -= 5;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        o->size += o->grow;
        o->inner = 0.4f * o->size;
    }
    if (o->kind == 1) {
        o->size += o->grow;
        o->inner = 0.7f * o->size;
        o->wide += o->grow;
    }
    if (o->kind == 2) {
        o->size += o->grow;
        o->inner = 0.7f * o->size;
        o->wide += o->grow;
    }
    o->t++;
    return 0;
}

/* shape b235:01E02B70, 165 insns: b065:01E02410 in pink (0xFF, 0x40, 0x80) with points at ctx+0xB244 / 0xB246 */

typedef struct {
    u8 pad0[0xB244];
    s16 id0;
    s16 id1;
} Ctx_b235_01E02B70;

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
} Fx_b235_01E02B70;

static s32 func_01E02B70_b235(Ctx_b235_01E02B70 *g, Fx_b235_01E02B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];
    f32 t;

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0x40, 0x80);
        func_001076F0(o->col2, 0xFF, 0x40, 0x80);
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

static s32 func_01E02E10_b235(Ctx_b065_01E02240 *ctx, Obj_b065_01E02240 *o) {
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

/* shape b235:01E02FE0, 136 insns: b490:01E00E90's scene light at g+0xB1A0 on a model joint: on start colour 128/10/10/10,
   height 0/123/0 and the effect's position; each tick the light follows the joint at g+0xB246; its strength rises by
   0.3 up to 1 for 160 ticks, then falls by 0.3 until it ends; func_001F6C10 gets the light (or 0 once ended); it
   also ends when the scene word at g+0xB210 is 2 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x44];
    s32 state;
} Light_b235_01E02FE0;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b235_01E02FE0 light;
    u8 padB214[0x32];
    s16 joint;
} Game_b235_01E02FE0;

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
} Fx_b235_01E02FE0;

static s32 func_01E02FE0_b235(Game_b235_01E02FE0 *g, Fx_b235_01E02FE0 *o) {
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
    if (o->t < 160) {
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

/* shape b235:01E03200, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x28, floor 0x40, state at 0xB210 below 0x1E */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b235_01E03200;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b235_01E03200;

static s32 func_01E03200_b235(Game_b235_01E03200 *g, Fade_b235_01E03200 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x28) {
        if (o->vol > 0x40) {
            o->vol -= 10;
        } else {
            o->vol = 0x40;
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

/* shape b235:01E03310, 159 insns: b247:01E03300 in 0x90/0x78/0x80 (0xA0/0x80/0x90 at scene count 118, ctx+0xB2BA);
   until count 145 the alpha rises by 16 to 0x40 and, past 118, by 26 to 0x68; after that it falls by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b235_01E03310;

typedef struct {
    f32 s, t;
    Xyz_b235_01E03310 p;
} Tv_b235_01E03310;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b235_01E03310 v[2];
    u8 tail[0x20];
} Tex_b235_01E03310;

typedef struct {
    u8 pad0[0xB2BA];
    s16 count;
} Ctx_b235_01E03310;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b235_01E03310;

static s32 func_01E03310_b235(Ctx_b235_01E03310 *g, Fx_b235_01E03310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b235_01E03310 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x90, 0x78, 0x80);
        o->mode = 2;
    }
    if (g->count == 118) {
        func_001076F0(o->col, 0xA0, 0x80, 0x90);
    }
    ((Tex_b235_01E03310 *)(s32)&pk)->flags = 0x26;
    ((Tex_b235_01E03310 *)(s32)&pk)->size = 5;
    ((Tex_b235_01E03310 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b235_01E03310 *)(s32)&pk)->pad4 = 0;
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
    if (g->count < 145) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x10;
        }
        if (g->count > 118) {
            if (o->col[3] < 0x68) {
                o->col[3] += 0x1A;
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

static s32 func_01E03590_b235(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b235", func_01E035A0_b235);

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

static s32 func_01E03DE0_b235(Pool_b065_01E03490 *o, s32 a, s32 b) {
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
