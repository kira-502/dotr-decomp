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

static void func_01E00080_b247(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b247(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b247((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b247((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b247(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E01230_b247(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

static void func_01E01640_b247(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b247:01E019B0, 367 insns, 1 copy (B247_W_S): the module's scene step: counts frames; at 167 it takes the model
   point (5 higher); 153..179 five b247:01E02C50 bursts of kind 0 and one of kind 1 at joint A a frame; 71..139 a
   b247:01E027A0 ring of kind 0 every third frame and kinds 1 and 2 every other frame at joint B, drifting 4 a frame
   to the scene's side; at 70 a b247:01E03300; 37..139 the spawn point follows joint C; at 167 a b247:01E01F70 at the
   model point and, 167..177, two b247:01E02530 and five b247:01E02FC0 a frame; at 60 a b247:01E01F70 and 40
   b247:01E02FC0 at joint C */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xAF70];
    Vec4f pt;
    u8 padB1E0[0x64];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padB24A[0x58];
    s16 h;
    u8 padB2A4[0xC];
    s16 kind;
    u8 padB2B2[2];
    s16 side;
    u8 padB2B6[2];
    s16 frame;
} Scene_b247_01E019B0;

static void func_01E019B0_b247(Scene_b247_01E019B0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    extern void func_001F5F90(s32, Vec4f *);
    extern s32 func_01E03E80_b247();
    extern s32 func_01E01F70_b247();
    extern s32 func_01E02530_b247();
    extern s32 func_01E027A0_b247();
    extern s32 func_01E02C50_b247();
    extern s32 func_01E02FC0_b247();
    extern s32 func_01E03300_b247();
    s16 i;

    g->frame++;
    if (g->frame == 167) {
        func_001F5F90(func_001F5380(), &g->pt);
        g->pt.y += 5.0f;
    }
    if (g->frame > 152 && g->frame < 180) {
        func_001F5620(func_001F53A0(), g->jA, &g->pos);
        g->kind = 0;
        for (i = 0; i < 5; i++) {
            func_01E03E80_b247(g, func_01E02C50_b247, 0);
        }
        g->kind = 1;
        for (i = 0; i < 1; i++) {
            func_01E03E80_b247(g, func_01E02C50_b247, 0);
        }
    }
    if (g->frame > 70 && g->frame < 140) {
        func_001F5620(func_001F53A0(), g->jB, &g->pos);
        g->pos.y = 40.0f;
        if (g->side != 0) {
            g->pos.z -= 4.0f;
        } else {
            g->pos.z += 4.0f;
        }
        g->kind = 0;
        if (g->frame % 3 == 1) {
            func_01E03E80_b247(g, func_01E027A0_b247, 0);
        }
        g->kind = 1;
        if (g->frame % 2 == 1) {
            func_01E03E80_b247(g, func_01E027A0_b247, 0);
        }
        g->kind = 2;
        if (g->frame % 2 == 1) {
            func_01E03E80_b247(g, func_01E027A0_b247, 0);
        }
    }
    if (g->frame == 70) {
        func_01E03E80_b247(g, func_01E03300_b247, 0);
    }
    if (g->frame > 36 && g->frame < 140) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
    }
    if (g->frame == 167) {
        g->pos = g->pt;
        g->kind = 0;
        func_01E03E80_b247(g, func_01E01F70_b247, 0);
    }
    if (g->frame >= 167 && g->frame < 178) {
        g->pos = g->pt;
        for (i = 0; i < 2; i++) {
            func_01E03E80_b247(g, func_01E02530_b247, 0);
        }
        g->kind = 1;
        for (i = 0; i < 5; i++) {
            func_01E03E80_b247(g, func_01E02FC0_b247, 0);
        }
    }
    if (g->frame == 60) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
        g->h = 0;
        g->kind = 0;
        g->h = 90;
        g->kind = 0;
        g->h = 45;
        g->kind = 1;
        g->h = 135;
        g->kind = 1;
        g->kind = 1;
        func_01E03E80_b247(g, func_01E01F70_b247, 0);
        g->kind = 0;
        for (i = 0; i < 40; i++) {
            func_01E03E80_b247(g, func_01E02FC0_b247, 0);
        }
    }
}

/* shape b247:01E01F70, 117 insns: on start by the kind 0x50 (0: f4C 220, hold 14, colours (0xFF, 0x40, 0x40) / white;
   1: hold 3, both (0xFF, 0x80, 0x80)), 0x52 = 0, 0x5A/0x5C = 10, second alpha 0; the second alpha grows by 0x60 (below
   0xC0) during the hold, then fades by 9 (kind 0) or 15 (kind 1) and stops; kind 1 sits on the game point 0xB248 and
   f48 grows by 25; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0xB248];
    s16 pt;
} Game_b247_01E01F70;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b247_01E01F70;

static s32 func_01E01F70_b247(Game_b247_01E01F70 *g, Fx_b247_01E01F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 220.0f;
            o->hold = 14;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x40, 0x40);
        }
        if (o->kind == 1) {
            o->hold = 3;
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
        }
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 0x10) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        func_001F5620(func_001F53A0(), g->pt, &o->pos);
        o->f48 += 25.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b247:01E02150, 116 insns: a red rising spark on a model joint (b631:01E01D30 shape): size 2..4, sub-frame 0..2, height
   5..14, angle, rise 6..15 once started, width 0..34, hold 3..5; alpha up by 42 to 0x80, then down by 14; follows the joint */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    Vec4f pos;
    u8 pad20[0x28];
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
} Obj_b247_01E02150;

typedef struct {
    u8 pad0[0xB248];
    s16 joint;
} Game_b247_01E02150;

static s32 func_01E02150_b247(Game_b247_01E02150 *g, Obj_b247_01E02150 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 3 + 2;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->y = func_0019A5C8() % 10 + 5;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 10 + 6;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b247:01E02320, 129 insns, 2 copies: a blue ring by kind (0 wide and fast, 1 medium, 2 small and pale): set up once
   (thickness, radius); fades in over 6 frames, then out; its radius grows 60/20/5 a frame, turning 6 */

typedef struct {
    u8 pad0[0x30];
    f32 thick;
    f32 radius;
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
} Ring_b247_01E02320;

static s32 func_01E02320_b247(void *arg0, Ring_b247_01E02320 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0x60, 0x60, 0xFF);
        func_001076F0(o->c1, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->thick = 28.0f;
            o->radius = 1600.0f;
        }
        if (o->kind == 1) {
            o->thick = 28.0f;
            o->radius = 500.0f;
        }
        if (o->kind == 2) {
            o->thick = 6.0f;
            o->radius = 100.0f;
            func_001076F0(o->c0, 0x80, 0x80, 0xC0);
            func_001076F0(o->c1, 0x40, 0x40, 0xFF);
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 6) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        if (o->t != 0) {
            o->radius += 60.0f;
        }
        o->ang += 6;
    }
    if (o->kind == 1) {
        if (o->t != 0) {
            o->radius += 20.0f;
        }
        o->ang += 6;
    }
    if (o->kind == 2) {
        if (o->t != 0) {
            o->radius += 5.0f;
        }
        o->ang += 6;
    }
    o->t++;
    return 0;
}

/* shape b247:01E02530, 153 insns: b751:01E01BF0 rising (70..119)/10 per tick, ended once the scene count (ctx+0xB2B8) reaches 226 */

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b247_01E02530;

typedef struct {
    u8 pad0[0xB2B8];
    s16 count;
} Ctx_b247_01E02530;

static s32 func_01E02530_b247(Ctx_b247_01E02530 *g, Obj_b247_01E02530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c0, 0xC0, 0x20, 0x20);
            func_001076F0(o->c1, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c0, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->c1, 0x30, 0x30, 0x30);
        }
        o->w = 60;
        o->h = 60;
        o->f38 = func_0019A5C8() % 50 + 70;
        o->f38 /= 10.0f;
        o->f30 = func_0019A5C8() % 80 + 150;
        o->f30 /= 10.0f;
        o->f34 = 100.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 4) {
        o->c0[3] -= 3;
    } else {
        o->state = 0;
    }
    o->f48 += o->f38;
    o->f4C = 0.1f * o->f48;
    o->t++;
    if (g->count > 225) {
        o->state = 0;
    }
    return 0;
}

/* shape b247:01E027A0, 297 insns, 1 copy (B247_OBJ_MOVE_6_): a red shock ring of kind 0..2: on start radius 140
   (inner 82), red on black or pink on grey by the scene frame's parity, life 8 or 10, growth 15..22.9 a tick, a random
   turn; full alpha for its life, then out by 5; kind 0 keeps its inner at 0.4 of the radius, 1 and 2 at 0.7 and rise
   by the growth; all end at scene frame 157 */

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
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b247_01E027A0;

typedef struct {
    u8 pad0[0xB2B8];
    s16 frame;
} Scene_b247_01E027A0;

static s32 func_01E027A0_b247(Scene_b247_01E027A0 *g, Obj_b247_01E027A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->r = 140.0f;
        o->r2 = o->r - 58.0f;
        if (o->kind == 0) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0xC0, 0x20, 0x20);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->life = 8;
        }
        if (o->kind == 1) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0xC0, 0x20, 0x20);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->f34 = 10.0f;
            o->life = 10;
        }
        if (o->kind == 2) {
            if (g->frame % 2 == 0) {
                func_001076F0(o->col2, 0xC0, 0x20, 0x20);
                func_001076F0(o->col, 0, 0, 0);
            }
            if (g->frame % 2 == 1) {
                func_001076F0(o->col2, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col, 0x30, 0x30, 0x30);
            }
            o->f34 = 10.0f;
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
        o->grow = func_0019A5C8() % 80 + 150;
        o->grow /= 10.0f;
        o->rise = 350.0f;
        o->rise /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->turn = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < o->life) {
        o->col2[3] = 0x80;
    } else if (o->col2[3] > 6) {
        o->col2[3] -= 5;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        o->r += o->grow;
        o->r2 = 0.4f * o->r;
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
    if (g->frame >= 157) {
        o->state = 0;
    }
    return 0;
}

/* shape b247:01E02C50, 219 insns: b751:01E01980's rising flash with the kind (0x50) given by the spawner: colours red
   on black or pink on grey by the parity of the scene count (ctx+0xB2B8), width 60, height 6 (kind 0) or 20 (kind 1),
   f34 starting at 100 (kind 0) or 400 (kind 1); rising (150..229)/10 per tick, tilted +-0x4000 by the scene flag
   (ctx+0xB2B4), turning rot[2] 0x100 per tick; full alpha 8 ticks then down by 5; f4C = 0.8 of the height */

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b247_01E02C50;

typedef struct {
    u8 pad0[0xB2B4];
    s16 flag;
    u8 padB2B6[2];
    s16 count;
} Ctx_b247_01E02C50;

static s32 func_01E02C50_b247(Ctx_b247_01E02C50 *g, Obj_b247_01E02C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->h50 == 0) {
            if (g->count % 2 == 0) {
                func_001076F0(o->c1, 0xC0, 0x20, 0x20);
                func_001076F0(o->c0, 0, 0, 0);
            }
            if (g->count % 2 == 1) {
                func_001076F0(o->c1, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->c0, 0x30, 0x30, 0x30);
            }
            o->w = 60;
            o->h = 6;
        }
        if (o->h50 == 1) {
            if (g->count % 2 == 0) {
                func_001076F0(o->c1, 0xC0, 0x20, 0x20);
                func_001076F0(o->c0, 0, 0, 0);
            }
            if (g->count % 2 == 1) {
                func_001076F0(o->c1, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->c0, 0x30, 0x30, 0x30);
            }
            o->w = 60;
            o->h = 20;
        }
        o->f38 = func_0019A5C8() % 80 + 150;
        o->f38 /= 10.0f;
        o->f30 = func_0019A5C8() % 80 + 150;
        o->f30 /= 10.0f;
        if (o->h50 == 0) {
            o->f34 = 100.0f;
        }
        if (o->h50 == 1) {
            o->f34 = 400.0f;
        }
        o->state = 2;
        o->c1[3] = 0;
        if (g->flag != 0) {
            o->rot0 = 0x4000;
        } else {
            o->rot0 = -0x4000;
        }
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c1[3] = 0x80;
    } else if (o->c1[3] > 6) {
        o->c1[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f38;
    o->f4C = 0.8f * o->f48;
    o->f34 += o->f38;
    o->rot2 += 0x100;
    o->t++;
    return 0;
}

/* shape b247:01E02FC0, 207 insns: b465:01E01880's tumbling spark, size 10 growing 40 in height, in white (kind 0, held
   10 ticks) or violet (0x80, 0x40, 0xFF; kind 1, held 22), drift (-50..49)/20, random turn and spin; hC follows the
   z drift; it ends once the scene count ctx+0xB2B8 passes 225 */

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
    u8 pad3C[0x14];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Spark_b247_01E02FC0;

typedef struct {
    u8 pad0[0xB2B8];
    s16 count;
} Ctx_b247_01E02FC0;

static s32 func_01E02FC0_b247(Ctx_b247_01E02FC0 *g, Spark_b247_01E02FC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001A22C0(f32);

    if (o->mode == 1) {
        o->h = o->w = 10;
        o->hC = 0;
        o->kind = (func_0019A5C8() >> 4) % 3;
        if (o->f50 == 0) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        }
        if (o->f50 == 1) {
            func_001076F0(o->col, 0x80, 0x40, 0xFF);
        }
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 20.0f;
        o->vel[0] /= 20.0f;
        o->vel[2] /= 20.0f;
        o->f5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        if (o->f50 == 0) {
            o->hold = 10;
        }
        if (o->f50 == 1) {
            o->hold = 22;
        }
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
        o->h += 40;
    }
    o->hC = func_001A22C0(o->hC + o->vel[2]);
    o->tick++;
    if (g->count > 225) {
        o->mode = 0;
    }
    return 0;
}

/* shape b247:01E03300, 147 insns: b432:01E03460 in 0x98/0x80/0x80 (0xA8 at scene count 160), alpha up by 22 to 0x58 until count 180 (ctx+0xB2B8), then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b247_01E03300;

typedef struct {
    f32 s, t;
    Xyz_b247_01E03300 p;
} Tv_b247_01E03300;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b247_01E03300 v[2];
    u8 tail[0x20];
} Tex_b247_01E03300;

typedef struct {
    u8 pad0[0xB2B8];
    s16 count;
} Ctx_b247_01E03300;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b247_01E03300;

static s32 func_01E03300_b247(Ctx_b247_01E03300 *g, Fx_b247_01E03300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b247_01E03300 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x98, 0x80, 0x80);
        o->mode = 2;
    }
    if (g->count == 160) {
        func_001076F0(o->col, 0xA8, 0x80, 0x80);
    }
    ((Tex_b247_01E03300 *)(s32)&pk)->flags = 0x26;
    ((Tex_b247_01E03300 *)(s32)&pk)->size = 5;
    ((Tex_b247_01E03300 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b247_01E03300 *)(s32)&pk)->pad4 = 0;
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
    if (g->count < 180) {
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

static s32 func_01E03550_b247(void) {
    return 0;
}

/* shape b247:01E03560 (b247), 581 insns, 1 copy: b247 scene manager in b235:01E035A0 form: setup (six joints and a
   camera, two type-4 and two type-5 textures, 256 s8 and 30 s16 jitters, 230-frame countdown), step b247:01E019B0 and
   every live slot except b247:01E03550, draw circle G4 by kind, magic gas, eye, GT4 rings (02530, 027A0 by kind,
   02C50 by kind) and the 02FC0 sprite plane; scene code from the timer (1 / 4 / 2 at 159 / 227 / 220, 6 in 170..214,
   8 once the countdown runs out) */

typedef struct {
    u8 pad0[0x10];
    union {
        Vec4f v;
        Vec_b065_01E012B0 p;
        Vec_b016_01E01190 c;
    } pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 kind;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b247_01E03560;

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
        s16 uv[4];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b247_01E03560 fx[400];
    u8 padB1A0[0x50];
    s32 tex[2];
    u8 padB1F8[0x18];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB250[4];
    s16 cam;
    u8 padB256[0xE];
    s16 jit16[30];
    u8 padB2A0[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BA[0x102];
    u8 crd[0x174];
} Scene_b247_01E03560;

static s32 func_01E03560_b247(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001F57B0(s32);
    extern void func_01E019B0_b247();
    extern void b247_01E04030();
    Scene_b247_01E03560 *g = (Scene_b247_01E03560 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
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
        g->count = 230;
        g->jA = func_001F5560(func_001F53A0(), 0x47, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x38, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x16, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
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
    func_001F57B0(1);
    func_01E019B0_b247(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03550_b247) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01F70_b247) {
                g->hB8 = 0x24;
                if (g->fx[k].kind == 0) {
                    func_01E00ED0_b247((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                       &g->fx[k].pos.c);
                }
                if (g->fx[k].kind == 1) {
                    func_01E00ED0_b247((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x20,
                                       &g->fx[k].pos.c);
                }
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02150_b247) {
                g->tex88 = g->tex[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 1;
                func_01E00920_b247((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02320_b247) {
                g->tex88 = g->tex260[15];
                func_00106080(rm, 0x9A, 0, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hBE = 0;
                func_01E01640_b247((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02530_b247) {
                func_00106080(rm2, 0x9C, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex260[15];
                g->tex88 = g->tex[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x80;
                g->u94.uv[3] = 0x80;
                g->hB8 = 0;
                g->px = g->fx[k].pos.v.x;
                g->py = g->fx[k].pos.v.y;
                g->pz = g->fx[k].pos.v.z;
                g->hB8 = 6;
                g->hBE = 0;
                func_01E01230_b247((Obj_b065_01E012B0 *)g, (Anim_b065_01E012B0 *)&g->fx[k], 0x20,
                                   g->fx[k].pos.p);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E027A0_b247) {
                if (g->fx[k].kind == 0) {
                    func_00106080(rm3, 0x97, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                    g->tex88 = g->tex260[15];
                }
                if (g->fx[k].kind == 1) {
                    func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                    g->tex88 = g->tex260[15];
                }
                if (g->fx[k].kind == 2) {
                    g->tex88 = g->tex[0];
                    g->hBE = 0;
                    g->u94.uv[0] = g->fx[k].h56 * 32;
                    g->u94.uv[1] = 0;
                    g->u94.uv[2] = 0x20;
                    g->u94.uv[3] = 0x40;
                }
                g->hB8 = 0;
                g->px = g->fx[k].pos.v.x;
                g->py = g->fx[k].pos.v.y;
                g->pz = g->fx[k].pos.v.z;
                g->hB8 = 0x24;
                if (g->fx[k].kind == 2) {
                    g->hB8 = 6;
                }
                g->hBE = 0;
                func_01E01230_b247((Obj_b065_01E012B0 *)g, (Anim_b065_01E012B0 *)&g->fx[k], 0x20,
                                   g->fx[k].pos.p);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02C50_b247) {
                if (g->fx[k].kind == 0) {
                    func_00106080(rm5, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                    g->tex88 = g->tex260[15];
                } else if (g->fx[k].kind == 1) {
                    g->tex88 = g->tex[0];
                    g->hBE = 0;
                    g->u94.uv[0] = g->fx[k].h56 * 32;
                    g->u94.uv[1] = 0;
                    g->u94.uv[2] = 0x20;
                    g->u94.uv[3] = 0x40;
                }
                g->hB8 = 0;
                g->px = g->fx[k].pos.v.x;
                g->py = g->fx[k].pos.v.y;
                g->pz = g->fx[k].pos.v.z;
                g->hB8 = 6;
                g->hBE = 0;
                func_01E01230_b247((Obj_b065_01E012B0 *)g, (Anim_b065_01E012B0 *)&g->fx[k], 0x21,
                                   g->fx[k].pos.p);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02FC0_b247) {
                g->tex88 = g->tex[1];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->hBE = 0;
                b247_01E04030(g, &g->fx[k], 0x20, g->fx[k].pos.v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x9F) {
        return 1;
    }
    if (g->frame == 0xE3) {
        return 4;
    }
    if (g->frame == 0xDC) {
        return 2;
    }
    if (g->frame > 0xA9 && g->frame < 0xD7) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b098:01E024A0, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fB2B0, f5A = owner fB2A2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b098_01E024A0 {
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
} Slot_b098_01E024A0;

typedef struct Obj_b098_01E024A0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b098_01E024A0 slots[400];
    u8 padB[0xB214 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xB2A2 - 0xB214 - 4];
    s16 fB;
    u8 padD[0xB2B0 - 0xB2A2 - 2];
    s16 fA;
} Obj_b098_01E024A0;

static s32 func_01E03E80_b247(Obj_b098_01E024A0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b098_01E024A0 *s = NULL;
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

/* shape b247:01E04030, 129 insns, 2 copies: draws one upright sprite plane at a position (b282:01E03460 family): sized by
   the sprite, turned by its yaw, lifted by its height; blend from flags >> 4. Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b247_01E04030;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b247_01E04030 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b247_01E04030;

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
} Obj_b247_01E04030;

typedef struct {
    u8 pad00[8];
    s16 w, h, y;
    u8 padE[0x12];
    Vec4f rot;
    u8 pad30[0x2A];
    s16 a5A;
    u8 pad5C[4];
    u8 col[4];
} Spr_b247_01E04030;

static void func_01E04030_b247(Obj_b247_01E04030 *o, Spr_b247_01E04030 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b247_01E04030 func_00107740(void *);
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
    Pkt_b247_01E04030 pkt __attribute__((aligned(8)));
    Pkt_b247_01E04030 *p;
    s32 b;

    b = (flags >> 4) & 0xF;
    p = (Pkt_b247_01E04030 *)(s32)&pkt;
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
    func_01E00080_b247((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    func_00108CE0(quad, s->w, s->h);
    r1[0] = 0;
    r1[1] = s->a5A;
    r1[2] = 0;
    func_00109100(quad, r1, 0, o->xD8);
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    func_00107070(quad, 2, s->y);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, o->ot, (u32)depth[0]);
    }
}
