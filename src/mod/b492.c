#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b492(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b492(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b492(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b492((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b492((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00F60_b492(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E012C0_b492(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01630_b492(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/mod/b492", func_01E01A70_b492);

/* shape b492:01E02230, 105 insns: b282:01E01C20 family spinning white spark (random size 10..24, frame 0..2, angle 10..49, spin 16..35, held 3..5 ticks): in by 64 up to 0xC0, then out by 14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b492_01E02230;

static s32 func_01E02230_b492(s32 arg0, Obj_b492_01E02230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 15 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b492:01E023E0, 98 insns: a grey spark: size 10..24, random sub-frame 0..2, height 10..49, angle, rise 16..35, width 0..34,
   hold 3..5; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

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
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b492_01E023E0;

static s32 func_01E023E0_b492(void *arg0, Obj_b492_01E023E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 0xA;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 40 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b492:01E02570, 134 insns: b763:01E02600 family glow in two kinds: kind 0 red/white, size 220, 14 ticks then down by 9; kind 1 dark grey/blue with a random turn, from 80 growing 40 per tick with f4C = 0.6 of it, 8 ticks then down by 15; outer alpha up by 0x60 to 0xC0 while alive */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b492_01E02570;

static s32 func_01E02570_b492(s32 arg0, Fx_b492_01E02570 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 220.0f;
            o->hold = 14;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x40, 0x40);
        }
        if (o->kind == 1) {
            o->hold = 8;
            func_001076F0(o->col2, 0x20, 0x20, 0x68);
            func_001076F0(o->col, 0x18, 0x18, 0x18);
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
            o->f48 = 80.0f;
            o->f4C = 0.6f * o->f48;
        }
        o->f52 = 0;
        o->w = 10;
        o->h = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 10) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 16) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        o->f48 += 40.0f;
        o->f4C = 0.6f * o->f48;
    }
    o->tick++;
    return 0;
}

/* shape b492:01E02790, 59 insns: a grey turning disc: set up once (grey, size 30x30, f34 90, scale 1), fades in by 12
   to 0x80 until the game timer reaches 200, then out by 9 until it ends; turns 0x200 a frame */

typedef struct {
    u8 pad0[0xCBB8];
    s16 timer;
} Game_b492_01E02790;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x1C];
    s32 rot;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 scale;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b492_01E02790;

static s32 func_01E02790_b492(Game_b492_01E02790 *g, Obj_b492_01E02790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h56 = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->h50 = 0;
        o->f34 = 90.0f;
        o->w = 0x1E;
        o->h = 0x1E;
        o->state = 2;
        o->c0[3] = 0;
        o->scale = 1.0f;
    }
    if (g->timer < 0xC8) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->rot += 0x200;
    o->t++;
    return 0;
}

/* shape b492:01E02880, 110 insns: on start f48 6, colour (0xFF, 0xA0, 0xA0), second colour (0xFF, 0x40, 0x40) with alpha 0, f30/f34 by the
   kind 0x50 (4.5f/60.0f, 4.5f/30.0f or 8/400), 0x52 = 0; alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and
   stops; after the first tick f34 grows by 10.0f (kind 0) or 5.0f (kind 1) and 0x52 counts up to 0x19; 0x5A turns 6 a tick */

typedef struct {
    u8 pad0[0x30];
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
} Fx_b492_01E02880;

static s32 func_01E02880_b492(s32 arg0, Fx_b492_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xA0, 0xA0);
        func_001076F0(o->col2, 0xFF, 0x40, 0x40);
        if (o->kind == 0) {
            o->f30 = 4.5f;
            o->f34 = 60.0f;
        }
        if (o->kind == 1) {
            o->f30 = 4.5f;
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
    if (o->kind == 0) {
        if (o->tick != 0) {
            o->f34 += 10.0f;
        }
    }
    if (o->kind == 1) {
        if (o->tick != 0) {
            o->f34 += 5.0f;
        }
    }
    if (o->tick != 0) {
        if (o->f52 < 0x19) {
            o->f52++;
        }
    }
    o->tick++;
    o->f5A += 6;
    return 0;
}

/* shape b492:01E02A40, 110 insns: on start f48 6, colour (0xFF, 0xFF, 0xFF), second colour (0x40, 0x40, 0xFF) with alpha 0, f30/f34 by the
   kind 0x50 (35.0f/700.0f, 35.0f/500.0f or 8/400), 0x52 = 0; alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and
   stops; after the first tick f34 grows by 50.0f (kind 0) or 30.0f (kind 1) and 0x52 counts up to 0x19; 0x5A turns 6 a tick */

typedef struct {
    u8 pad0[0x30];
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
} Fx_b492_01E02A40;

static s32 func_01E02A40_b492(s32 arg0, Fx_b492_01E02A40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->f30 = 35.0f;
            o->f34 = 700.0f;
        }
        if (o->kind == 1) {
            o->f30 = 35.0f;
            o->f34 = 500.0f;
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
    if (o->kind == 0) {
        if (o->tick != 0) {
            o->f34 += 50.0f;
        }
    }
    if (o->kind == 1) {
        if (o->tick != 0) {
            o->f34 += 30.0f;
        }
    }
    if (o->tick != 0) {
        if (o->f52 < 0x19) {
            o->f52++;
        }
    }
    o->tick++;
    o->f5A += 6;
    return 0;
}

/* shape b492:01E02C00 (B492_OBJ_MOVE_10_), 225 insns, 1 copy (-O3,p): four 20-point joint trails in blue
   (b703:01E02E70's source at -O3): on start each trail is filled with its scene joint's point (the second and third
   joints swapped); fades in by 0x3C until scene frame 184, then out by 9; until frame 185 each trail takes its joint
   point every frame */

typedef struct {
    f32 x, y, z, w;
} Pt_b492_01E02C00;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b492_01E02C00 a[20];
    Pt_b492_01E02C00 b[20];
    Pt_b492_01E02C00 c[20];
    Pt_b492_01E02C00 d[20];
    u8 padB6D0[0x1474];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 padCB50[0x6C];
    s16 frame;
} Scene_b492_01E02C00;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b492_01E02C00;

#pragma optimization_level 3

static s32 func_01E02C00_b492(Scene_b492_01E02C00 *g, Fx_b492_01E02C00 *o) {
    extern void b492_01E00080(Pt_b492_01E02C00 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    s16 k;
    s16 m;
    Pt_b492_01E02C00 *q;

    func_001076F0(o->col, 0x20, 0x20, 0xC0);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->hE = 30;
        func_001F5620(func_001F53A0(), g->ja, p);
        q = g->a;
        for (i = 0; i < 19; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jc, p);
        q = g->b;
        for (j = 0; j < 19; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->c;
        for (k = 0; k < 19; k++) {
            q[k].x = p[0];
            q[k].y = p[1];
            q[k].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jd, p);
        q = g->d;
        for (m = 0; m < 19; m++) {
            q[m].x = p[0];
            q[m].y = p[1];
            q[m].z = p[2];
        }
        o->mode = 2;
    }
    if (g->frame < 184) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->frame < 185) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b492_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jc, p);
        b492_01E00080(&g->b[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b492_01E00080(&g->c[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jd, p);
        b492_01E00080(&g->d[19], 20, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

#pragma optimization_level reset

/* shape b492:01E02F90, 69 insns: constant variant of b287:01E02C80 (0xE->4, 150.0f->220.0f) */

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
} Fx_b492_01E02F90;

static s32 func_01E02F90_b492(s32 arg0, Fx_b492_01E02F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 220.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
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

/* shape b287:01E02DA0, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x97, floor 0x30, state at 0xCB10 below 0x1E */

typedef struct {
    u8 pad[0xCB10];
    s32 state;
} Game_b287_01E02DA0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b287_01E02DA0;

static s32 func_01E030B0_b492(Game_b287_01E02DA0 *g, Fade_b287_01E02DA0 *o) {
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

/* shape b492:01E031C0, 150 insns: b354:01E02890 with a grey veil, the zoom growing 0.3 a tick below 5 once the scene
   frame at g+0xCBB8 passes 190, alpha up by 16 to 0x40 until frame 200 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b492_01E031C0;

typedef struct {
    f32 s, t;
    Xyz_b492_01E031C0 p;
} Tv_b492_01E031C0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b492_01E031C0 v[2];
    u8 tail[0x20];
} Tex_b492_01E031C0;

typedef struct {
    u8 pad0[0xCBB8];
    s16 frame;
} Ctx_b492_01E031C0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b492_01E031C0;

static s32 func_01E031C0_b492(Ctx_b492_01E031C0 *g, Fx_b492_01E031C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b492_01E031C0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    ((Tex_b492_01E031C0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b492_01E031C0 *)(s32)&pk)->size = 5;
    ((Tex_b492_01E031C0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b492_01E031C0 *)(s32)&pk)->pad4 = 0;
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
    if (g->frame > 190) {
        if (o->f48 < 5.0f) {
            o->f48 += 0.3f;
        }
    }
    if (g->frame < 200) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b492:01E03430, 292 insns, 1 copy: B492_OBJ_MOVE_203_: a full-screen sprite through the scene's sprite packet:
   grey level cycling 0x60/0x50/0x40/0x30/0x20/0x30/0x40/0x50 over 8 ticks, UVs inset by size/10 (0x8, 0xA), fades in
   by 9 to 0x80 for 220 ticks, then out by 7 and ends */

typedef struct Xyz_b492_01E03430 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b492_01E03430;

typedef struct Spr_b492_01E03430 {
    u8 pad0[0x10];
    u8 r, g, b, a;
    f32 q;
    f32 u0, v0;
    Xyz_b492_01E03430 p0;
    f32 u1, v1;
    Xyz_b492_01E03430 p1;
} Spr_b492_01E03430;

typedef struct Game_b492_01E03430 {
    u8 pad0[0xCB28];
    Spr_b492_01E03430 *spr;
} Game_b492_01E03430;

typedef struct Obj_b492_01E03430 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Obj_b492_01E03430;

static s32 func_01E03430_b492(Game_b492_01E03430 *g, Obj_b492_01E03430 *o) {
    extern void func_001076F0();
    extern void func_002075F0();
    f32 w;
    f32 h;

    w = o->w;
    h = o->h;
    w /= 10.0f;
    h /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->mode = 2;
    }
    if (o->t % 8 == 0) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    if (o->t % 8 == 1) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
    }
    if (o->t % 8 == 2) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->t % 8 == 3) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    }
    if (o->t % 8 == 4) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
    }
    if (o->t % 8 == 5) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    }
    if (o->t % 8 == 6) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->t % 8 == 7) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
    }
    g->spr->r = o->col[0];
    g->spr->g = o->col[1];
    g->spr->b = o->col[2];
    g->spr->a = o->col[3];
    g->spr->q = 1.0f;
    g->spr->p0.x = 0x6BF8;
    g->spr->p0.y = 0x71F8;
    g->spr->p0.z = 0xFFFFFF;
    g->spr->p0.f = 0;
    g->spr->p1.x = 0x93F8;
    g->spr->p1.y = 0x8DF8;
    g->spr->p1.z = 0xFFFFFF;
    g->spr->p1.f = 0;
    g->spr->u0 = w / 1024.0f;
    g->spr->v0 = h / 512.0f;
    g->spr->u1 = (640.0f - w) / 1024.0f;
    g->spr->v1 = (448.0f - h) / 512.0f;
    func_002075F0(g->spr, 0, 0);
    if (o->t < 220) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->t > 40) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b492", func_01E038C0_b492);

/* shape b256:01E04900, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fCBB0, f5A = owner fCBA2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b256_01E04900 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b256_01E04900;

typedef struct Obj_b256_01E04900 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b256_01E04900 slots[400];
    u8 padB[0xCB14 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xCBA2 - 0xCB14 - 4];
    s16 fB;
    u8 padD[0xCBB0 - 0xCBA2 - 2];
    s16 fA;
} Obj_b256_01E04900;

static s32 func_01E040A0_b492(Obj_b256_01E04900 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b256_01E04900 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
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
        s->f50 = obj->fA;
        s->f52 = obj->fA;
        s->f5A = obj->fB;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b492:01E04250 (B492KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b492_01E04250 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b492_01E04250;

typedef struct {
    Rgbaq_b492_01E04250 c;
    u64 xyz;
} Vtx_b492_01E04250;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b492_01E04250 v[4];
    u8 tail[0x40];
} Pkt_b492_01E04250;

typedef struct {
    u8 r, g, b, a;
} C4_b492_01E04250;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b492_01E04250 col;
} Rib_b492_01E04250;

static inline u8 b492_01E04250_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E04250_b492(void *o, Rib_b492_01E04250 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b492_01E04250 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b492_01E04250 pkt __attribute__((aligned(8)));
    C4_b492_01E04250 c0;
    C4_b492_01E04250 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b492_01E04250 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b492_01E04250 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    step = s->col.a;
    step /= (s16)(n * 3);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - step > 0) {
                c1.a = b492_01E04250_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E01630_b492(pp, 0, t);
                B[0] = func_01E01630_b492(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E01630_b492(pp, 0, t);
                B[1] = func_01E01630_b492(pq, 0, t);
            } else {
                A[0] = func_01E01630_b492(a4, 0, t);
                B[0] = func_01E01630_b492(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01630_b492(a4, 0, t);
                B[1] = func_01E01630_b492(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

/* shape b256:01E04FF0, 89 insns, 3 copies: draws all live particles of the module's pool whose callback is the module's
   particle drawer (b256:01E03DC0) into one packet, inside a draw context opened only when one was drawn. */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
} Pkt_b256_01E04FF0;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b256_01E04FF0;

typedef struct {
    u8 pad0000[0x2A0];
    Slot_b256_01E04FF0 slots[400];
    u8 padB1A0[0x1984];
    s32 ctx;
    Pkt_b256_01E04FF0 *pkt;
} Pool_b256_01E04FF0;

static void func_01E047C0_b492(Pool_b256_01E04FF0 *o) {
    extern s32 func_00207F60(void);
    extern s32 func_00208460();
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_00207FD0(s32, void *, s32);
    extern void b492_01E03430(void *, void *);
    Pkt_b256_01E04FF0 pkt __attribute__((aligned(8)));
    s32 a[2];
    s32 b[4] __attribute__((aligned(8)));
    s32 i;
    s32 n;

    o->pkt = &pkt;
    n = 0;
    o->ctx = func_00207F60();
    o->pkt->count = 0x26;
    o->pkt->tag = 5;
    o->pkt->regs = 0x42421;
    o->pkt->pad = 0;
    func_00208460();
    func_002086D0(o->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, a, b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used != 0) {
            n++;
            if (o->slots[i].cb == b492_01E03430) {
                b492_01E03430(o, &o->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(o->ctx, func_00207500(), 0);
    }
}

/* shape b492:01E04930, 151 insns: four-part textured quad (func_00108D60 parts, size h8 x hA) at the given point, scaled 0.5 and turned by the object's rotation, all four corners in the object's colour; blend from flags >> 4; depth from the projection */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b492_01E04930;

typedef struct {
    Rgbaq_b492_01E04930 c;
    f32 s, t;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b492_01E04930;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b492_01E04930 v[4];
    u8 tail[0x20];
} Pkt_b492_01E04930;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex;
} Ctx_b492_01E04930;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x30];
    u8 col[4];
} Fx_b492_01E04930;

static void func_01E04930_b492(Ctx_b492_01E04930 *g, Fx_b492_01E04930 *o, Vec4f *at, s32 flags) {
    f32 hs;
    extern Rgbaq_b492_01E04930 func_00107740(void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f pos;
    Vec4f quad[4];
    Vec4f t;
    Vec4f sc;
    f32 m[16];
    f32 depth[4];
    Pkt_b492_01E04930 pk;
    Pkt_b492_01E04930 *p;
    s16 sel;
    s32 i;

    pos = *at;
    p = (Pkt_b492_01E04930 *)(u32)&pk;
    p->count = 0x34;
    p->tag = 0xC;
    p->regs = ((u64)0x4214 << 32) | 0x21421421;
    p->pad = 0;
    pk.v[0].c = func_00107740(o->col);
    pk.v[1].c = func_00107740(o->col);
    pk.v[2].c = func_00107740(o->col);
    pk.v[3].c = func_00107740(o->col);
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00208700(p, g->tex, 0);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    hs = 0.5f;
    func_00106DD0(&sc, hs, hs, hs);
    func_00108EF0(m, &sc, o->rot, &t);
    p->v[0].s = 0.0f;
    p->v[0].t = 0.0f;
    p->v[1].s = 1.0f;
    p->v[1].t = 0.0f;
    p->v[2].s = 0.0f;
    p->v[2].t = 1.0f;
    p->v[3].s = 1.0f;
    p->v[3].t = 1.0f;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, o->w, o->h, (s16)i);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
    }
}
