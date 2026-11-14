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

static void func_01E00080_b747(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b747(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b747((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b747((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b193_01E009B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Anim_b193_01E009B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b193_01E009B0;

typedef struct {
    u8 b[0x90];
} Pkt_b193_01E009B0;

static void func_01E00ED0_b747(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b193_01E009B0 quad[4];
    Vec_b193_01E009B0 at;
    Vec_b193_01E009B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b193_01E009B0 pkt;
    s32 a;
    s32 k;
    s16 j;
    Pkt_b193_01E009B0 *p;
    s16 blend;
    s32 kind;
    f32 w0;
    f32 w1;

    p = &pkt;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    kind = mode & 0xF;
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    for (k = 0; k < 36; k++) {
        if (k == 0) {
            a = an->step + j;
            quad[0].x = w0 * func_00108030(o->bD8, a, 1);
            quad[0].z = w0 * func_00108030(o->bD8, a, 0);
            quad[2].x = w1 * func_00108030(o->bD8, a, 1);
            quad[2].z = w1 * func_00108030(o->bD8, a, 0);
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        }
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
        j += 10;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E01330_b747(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
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
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
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

static void func_01E01690_b747(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b747 in the
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

static void func_01E01A00_b747(Obj_b020_01E011E0 *obj, Cam_b020_01E011E0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b747((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b747:01E01D00, 281 insns: B747_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0x451A);
   until 155 the follow point sits on joint 0x44E4, at 155 it gets a 32-frame glide toward the camera joint
   0x44F4, gliding until 186, where the scene point takes it; frame 100 looks up three joints (0x11, 0x1C, 0x26),
   frame 40 spawns two 0x1E026D0 (side 0 angle 0, side 1 angle 90) and 0x1E02860; frames 109..360 spawn 0x1E02170
   on the three joints in turn; frame 109 spawns 0x1E02D40 and 0x1E02B40; every 4th frame of 159..380 spawns
   0x1E02420 and 0x1E02500 jittered around the camera joint; the spin (0x450C) turns 2 a frame */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Vec4f p;
    Vec4f vel;
    u8 pad4490[0x44E4 - 0x4490];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 pad44EA[0x44F4 - 0x44EA];
    s16 jcam;
    u8 pad44F6[0x4506 - 0x44F6];
    s16 ang;
    u8 pad4508[0x450C - 0x4508];
    s16 spin;
    u8 pad450E[0x4512 - 0x450E];
    s16 side;
    u8 pad4514[0x451A - 0x4514];
    s16 t;
} Scene_b747_01E01D00;

static void func_01E01D00_b747(Scene_b747_01E01D00 *g) {
    extern void b747_01E02170(void);
    extern void b747_01E02420(void);
    extern void b747_01E02500(void);
    extern void b747_01E026D0(void);
    extern void b747_01E02860(void);
    extern void b747_01E02B40(void);
    extern void b747_01E02D40(void);
    extern void b747_01E03A50(Scene_b747_01E01D00 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];
    s32 k;

    g->t++;
    if (g->t < 155) {
        func_001F5620(func_001F53A0(), g->ja, &g->p);
    } else {
        if (g->t == 155) {
            func_001F5620(func_001F5380(), g->jcam, v);
            g->vel.z = (v[0].z - g->p.z) / 32.0f;
            g->vel.y = (v[0].y - g->p.y) / 32.0f;
        }
        if (g->t < 186) {
            g->p.z += g->vel.z;
            g->p.y += g->vel.y;
        }
    }
    if (g->t == 186) {
        g->pos = g->p;
        g->side = 0;
    }
    if (g->t == 100) {
        g->ja = func_001F5560(func_001F53A0(), 0x11, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jc = func_001F5560(func_001F53A0(), 0x26, 0);
    }
    if (g->t == 40) {
        g->side = 0;
        g->ang = 0;
        b747_01E03A50(g, b747_01E026D0, 0);
        g->side = 1;
        g->ang = 90;
        b747_01E03A50(g, b747_01E026D0, 0);
        b747_01E03A50(g, b747_01E02860, 0);
    }
    if (g->t >= 109 && g->t <= 360) {
        k = g->t % 3;
        if (k == 0) {
            g->side = 0;
            func_001F5620(func_001F53A0(), g->ja, &g->pos);
            b747_01E03A50(g, b747_01E02170, 0);
        } else if (k == 1) {
            g->side = 1;
            func_001F5620(func_001F53A0(), g->jb, &g->pos);
            b747_01E03A50(g, b747_01E02170, 0);
        } else if (k == 2) {
            g->side = 2;
            func_001F5620(func_001F53A0(), g->jc, &g->pos);
            b747_01E03A50(g, b747_01E02170, 0);
        }
    }
    if (g->t == 109) {
        b747_01E03A50(g, b747_01E02D40, 0);
    }
    if (g->t == 109) {
        b747_01E03A50(g, b747_01E02B40, 0);
    }
    if (g->t >= 159 && g->t <= 380 && g->t % 4 == 0) {
        func_001F5620(func_001F5380(), g->jcam, v);
        g->pos = v[0];
        g->pos.x += func_0019A5C8() % 16 - 8;
        g->pos.y += func_0019A5C8() % 16 - 8;
        g->pos.z += func_0019A5C8() % 10 - 5;
        b747_01E03A50(g, b747_01E02420, 0);
        b747_01E03A50(g, b747_01E02500, 0);
    }
    g->spin += 2;
    if (g->spin >= 360) {
        g->spin %= 360;
    }
}

/* shape b747:01E02170, 170 insns: b193:01E02530's ring in green (0x80/0xFF/0x80 blinking with 0x60/0xC0/0x60): size 7, h5C
   from the scene (g+0x450C), a 35-tick fade-in, f34 swinging by 1.6 to +-50 and f38 growing by 0.2 to 10; after the first tick
   the size grows by 6 with f4C = size - 13 (flag g+0x4516 set) or - 14, and the height moves by 5 */

typedef struct {
    u8 pad0[0x450C];
    s16 h450C;
    u8 pad450E[8];
    s16 flag;
} Game_b747_01E02170;

typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 size;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b747_01E02170;

static s32 func_01E02170_b747(Game_b747_01E02170 *g, Obj_b747_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 7.0f;
        func_001076F0(o->c0, 0x80, 0xFF, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->h5C = g->h450C;
        o->c1[3] = 0;
    }
    if (o->t < 35) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 10) {
        o->c1[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0xFF, 0x80);
    } else {
        func_001076F0(o->c0, 0x60, 0xC0, 0x60);
    }
    o->rot = 0x4000;
    if (g->flag != 0) {
        if (o->f34 < 50.0f) {
            o->f34 += 1.6f;
        }
    } else if (!(o->f34 <= -50.0f)) {
        o->f34 -= 1.6f;
    }
    if (o->f38 < 10.0f) {
        o->f38 += 0.2f;
    }
    if (o->t != 0) {
        o->size += 6.0f;
        if (g->flag != 0) {
            o->f4C = o->size - 13.0f;
        } else {
            o->f4C = o->size - 14.0f;
        }
    }
    o->h5C += 9;
    o->t++;
    if (o->t != 0) {
        if (g->flag != 0) {
            o->y -= 5.0f;
        } else {
            o->y += 5.0f;
        }
    }
    return 0;
}

/* shape b747:01E02420, 54 insns: variant of b402:01E02B70 (spinning flash), size 50, held alpha 0xC0 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
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
} Flash_b747_01E02420;

static s32 func_01E02420_b747(s32 arg0, Flash_b747_01E02420 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 50.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b747:01E02500, 115 insns: on start f48 15..24, variant 4, colour 0x80 grey, random rotation, 0x50 10..59,
   random 0x5A, speed 20..49 (0xE), 0x8 -6..8, hold 0..4 (0x6); alpha 0x60 during the hold, then fades by 11 and stops;
   0x50 grows by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
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
} Fx_b747_01E02500;

static s32 func_01E02500_b747(s32 arg0, Fx_b747_01E02500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 15;
        o->f56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 50 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 30 + 20;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b747:01E026D0, 98 insns: a grey-green spinning ring by kind (0: width 4.5, height 10 growing by 8, flat; 1: width 4,
   height 5 growing by 5, turned 90): size 6; alpha up by 0x40 for 4 frames, then down by 9 until it ends; turns by 6 */

typedef struct {
    u8 pad0[0x30];
    f32 w;
    f32 h;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b747_01E026D0;

static s32 func_01E026D0_b747(void *arg0, Obj_b747_01E026D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0x10, 0xFF, 0x10);
        if (o->kind == 0) {
            o->w = 4.5f;
            o->h = 10.0f;
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->w = 4.0f;
            o->h = 5.0f;
            o->ang = 0x5A;
        }
        o->state = 2;
        o->c1[3] = 0;
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
        o->h += 8.0f;
    }
    if (o->kind == 1 && o->t != 0) {
        o->h += 5.0f;
    }
    if (o->t != 0) {
        o->ang += 6;
    }
    o->t++;
    return 0;
}

/* shape b747:01E02860, 56 insns: white burst: on start f48 20 then 100, both colours white, 0x8/0xA = 5, variant 4,
   second alpha 0; alpha grows by 0x60 (below 0xC0) for 4 ticks, then fades by 14 and stops */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x3C];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b747_01E02860;

static s32 func_01E02860_b747(s32 arg0, Fx_b747_01E02860 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->f8 = 5;
        o->fA = 5;
        o->f48 = 100.0f;
        o->f56 = 4;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b016:01E02940, 127 insns: a drifting spark: on start pick a random size, variant, position, start value,
   angle, speed, delay and lifetime and colour (0xC0,0x50,0x50); full alpha while younger than its lifetime, then
   fade out by 11 and stop; the value 0x50 grows by the speed every tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 x;
    s32 y;
    s32 z;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 dir;
    u8 pad5C[4];
    u8 col[4];
} Spark_b016_01E02940;

static s32 func_01E02940_b747(s32 arg0, Spark_b016_01E02940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0x50, 0x50);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 200 + 200;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b747:01E02B40, 127 insns: b594:01E02CB0 with a green-grey tint (0x78/0x80/0x78), start offset 1, and the
   fade-out once the game counter at g+0x451A reaches 395 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b747_01E02B40;

typedef struct {
    f32 s, t;
    Xyz_b747_01E02B40 p;
} Tv_b747_01E02B40;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b747_01E02B40 v[2];
    u8 tail[0x20];
} Tex_b747_01E02B40;

typedef struct {
    u8 pad0[0x451A];
    s16 count;
} Ctx_b747_01E02B40;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b747_01E02B40;

static s32 func_01E02B40_b747(Ctx_b747_01E02B40 *g, Fx_b747_01E02B40 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b747_01E02B40 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
    }
    ((Tex_b747_01E02B40 *)(s32)&pk)->flags = 0x26;
    ((Tex_b747_01E02B40 *)(s32)&pk)->size = 5;
    ((Tex_b747_01E02B40 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b747_01E02B40 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0x80;
    pk.b = 0x78;
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
    if (g->count < 395) {
        if (o->col[3] < 0x50) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b747:01E02D40, 160 insns: b491:01E03360 family pale green (0xC0, 0xFF, 0xC0) window in the scene packet (ctx+0x44C8), drawn once: alpha pulses (up by 8 to 0x80, down by 11 to 12) for 200 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b747_01E02D40;

typedef struct {
    f32 s, t;
    Xyz_b747_01E02D40 p;
} Tv_b747_01E02D40;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b747_01E02D40 v[2];
} Tex_b747_01E02D40;

typedef struct {
    u8 pad[0x44C8];
    Tex_b747_01E02D40 *pk;
} Game_b747_01E02D40;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x44];
    s16 phase;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b747_01E02D40;

static s32 func_01E02D40_b747(Game_b747_01E02D40 *g, Fx_b747_01E02D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xC0, 0xFF, 0xC0);
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = fx / 1024.0f;
    g->pk->v[0].t = fy / 512.0f;
    g->pk->v[1].s = (640.0f - fx) / 1024.0f;
    g->pk->v[1].t = (448.0f - 3.0f * fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 200) {
        if (o->phase == 0) {
            if (o->col[3] < 0x80) {
                o->col[3] += 8;
            } else {
                o->phase = 1;
            }
        } else if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->phase = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b747:01E02FC0 (b747), 674 insns, 1 copy: b747 scene manager in b491:01E035E0 form: setup (four joints, one
   type-4 and two type-5 textures, two s8 jitter tables), step 01E01D00 and every live slot (counting the 02D40 ones,
   drawn by 03BA0), draw the 02170/02420/02500/026D0/02860 effects; scene code from the timer (1 / 4 / 2 at 121 / 405
   / 395, 6 in 132..389, 8 once the 419-frame countdown runs out) */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x18];
    f32 f38;
    u8 pad3C[8];
    s32 (*fn)();
    u8 pad48[8];
    s16 kind;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b747_01E02FC0;

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
    s32 rm[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b747_01E02FC0 fx[150];
    u8 pad4440[0x50];
    s32 tex[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    u8 pad44EC[8];
    s16 cam;
    u8 pad44F6[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b747_01E02FC0;

static s32 func_01E02FC0_b747(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern s32 func_01E02170_b747();
    extern s32 func_01E02420_b747();
    extern s32 func_01E02500_b747();
    extern s32 func_01E026D0_b747();
    extern s32 func_01E02860_b747();
    extern s32 func_01E02940_b747();
    extern s32 func_01E02D40_b747();
    extern void b747_01E01D00();
    extern void b747_01E00ED0();
    extern void b747_01E01330();
    extern void b747_01E00920();
    extern void b747_01E01690();
    extern void b747_01E01A00();
    extern void b747_01E03BA0();
    Scene_b747_01E02FC0 *g = (Scene_b747_01E02FC0 *)arg0;
    s16 m;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4890);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 419;
        g->jA = func_001F5560(func_001F53A0(), 0x1A, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x11, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x27, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
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
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    b747_01E01D00(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != func_01E02D40_b747) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    m++;
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == func_01E02170_b747) {
                v = g->fx[k].pos;
                if (g->fx[k].kind == 1) {
                    v.y += 3.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                if (g->fx[k].kind == 0) {
                    v.x += 6.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                if (g->fx[k].kind == 2) {
                    v.x -= 6.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                b747_01E00ED0(g, &g->fx[k], 0x20, &v);
            }
            if (g->fx[k].fn == func_01E02420_b747) {
                g->hB8 = 0x18;
                b747_01E01330(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == func_01E02500_b747) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 10;
                g->hB0 = 0;
                b747_01E00920(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == func_01E026D0_b747) {
                func_001F5620(func_001F53A0(), g->jA, &v);
                g->tex88 = g->tex260[15];
                func_00106080(rm2, 0x9A, 0, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                v.w = 0.0f;
                b747_01E01690(g, &g->fx[k], 0, &v);
                func_001F5620(func_001F53A0(), g->jB, &v);
                b747_01E01690(g, &g->fx[k], 0, &v);
                func_001F5620(func_001F53A0(), g->jC, &v);
                v.x -= 1.0f;
                if (g->turn != 0) {
                    v.y += 0.5f;
                }
                b747_01E01690(g, &g->fx[k], 0, &v);
                func_001F5620(func_001F53A0(), g->jC, &v);
                v.x += 1.0f;
                if (g->turn == 0) {
                    v.y += 0.5f;
                }
                b747_01E01690(g, &g->fx[k], 0, &v);
                func_001F5620(func_001F53A0(), g->jD, &v);
                v.x -= 1.0f;
                if (g->turn == 0) {
                    v.y += 0.5f;
                }
                b747_01E01690(g, &g->fx[k], 0, &v);
                func_001F5620(func_001F53A0(), g->jD, &v);
                v.x += 1.0f;
                if (g->turn != 0) {
                    v.y += 0.5f;
                }
                b747_01E01690(g, &g->fx[k], 0, &v);
            }
            if (g->fx[k].fn == func_01E02860_b747) {
                func_001F5620(func_001F53A0(), g->jA, &v);
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, 0, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hBE = 0;
                v.w = 0.0f;
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
                func_001F5620(func_001F53A0(), g->jB, &v);
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
                func_001F5620(func_001F53A0(), g->jC, &v);
                v.x -= 1.0f;
                if (g->turn != 0) {
                    v.y += 0.5f;
                }
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
                func_001F5620(func_001F53A0(), g->jC, &v);
                v.x += 1.0f;
                if (g->turn == 0) {
                    v.y += 0.5f;
                }
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
                func_001F5620(func_001F53A0(), g->jD, &v);
                v.x -= 1.0f;
                if (g->turn == 0) {
                    v.y += 0.5f;
                }
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
                func_001F5620(func_001F53A0(), g->jD, &v);
                v.x += 1.0f;
                if (g->turn != 0) {
                    v.y += 0.5f;
                }
                b747_01E01A00(g, &g->fx[k], 0x21, &v);
            }
            if (g->fx[k].fn == func_01E02940_b747) {
                g->tex88 = g->tex260[15];
                func_00106080(rm4, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hB8 = 10;
                g->hB0 = 1;
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (m) {
        b747_01E03BA0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 121) {
        return 1;
    }
    if (g->frame == 405) {
        return 4;
    }
    if (g->frame == 395) {
        return 2;
    }
    if (g->frame > 131 && g->frame < 390) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b747:01E03A50, 82 insns (b020:01E02D90 shape): takes the first free of 150 effect slots (0x70 bytes, b089:01E030B0 shape), colours it from
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
} Slot_b747_01E03A50;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b747_01E03A50 slots[0x96];
    u8 pad[0x44B4 - 0x2A0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 pad44B8[0x4E];
    s16 f4506;
    u8 pad4508[0xA];
    s16 f4512;
} Ctx_b747_01E03A50;

static s32 func_01E03A50_b747(Ctx_b747_01E03A50 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b747_01E03A50 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x70);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x96;
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
        s->f5A = ctx->f4506;
        s->f50 = ctx->f4512;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

/* shape b747:01E03BA0, 68 insns: b183:01E029E0 family draw pass: sprite packet on the stack, then every live slot (150 of 0x70 bytes) whose handler is shape b747:01E02D40 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b747_01E03BA0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b747_01E03BA0 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b747_01E03BA0;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b747_01E03BA0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b747_01E03BA0 slot[150];
    u8 padEnd[0x44c4 - 0x2A0 - 150 * 0x70];
    s32 ctx;
    Pkt_b747_01E03BA0 *pkt;
} Scene_b747_01E03BA0;

static void func_01E03BA0_b747(Scene_b747_01E03BA0 *s) {
    extern void b747_01E02D40(Scene_b747_01E03BA0 *, Slot_b747_01E03BA0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b747_01E03BA0 pkt __attribute__((aligned(8)));
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
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b747_01E02D40) {
            b747_01E02D40(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
