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

static void func_01E00080_b745(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b745(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b745((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b745((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b745(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b745 in the
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

static void func_01E01230_b745(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b745((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E014F0_b745(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

static void func_01E01900_b745(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

static void func_01E01C70_b745(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b745:01E01E40, 275 insns: b522:01E01D30's scene step for module b745 (tick g+0xB2BC): at tick 1 it spawns
   0x1E035F0 and 0x1E03700; at tick 98 0x1E03320 (side 0) and marks the model; ticks 98..112 burst at the mark at height 35
   (five 0x1E02510, five 0x1E026C0, 0x1E02A70), on tick 98 also four 0x1E02870 (angles 0/90/45/135, sides
   0/0/1/1) and 0x1E034D0; up to tick 98 a spark at joint 0xB24C; at ticks 75 and 95 thirteen 0x1E02F40 at joints 0xB248 and
   0xB24A, 1.5 below */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f mark;
    u8 padB1E0[0xB248 - 0xB1E0];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 padB24E[0xB2A6 - 0xB24E];
    s16 ang;
    u8 padB2A8[0xB2B4 - 0xB2A8];
    s16 side;
    u8 padB2B6[6];
    s16 t;
} Scene_b745_01E01E40;

static void func_01E01E40_b745(Scene_b745_01E01E40 *g) {
    extern void b745_01E02290(void);
    extern void b745_01E02510(void);
    extern void b745_01E026C0(void);
    extern void b745_01E02870(void);
    extern void b745_01E02A70(void);
    extern void b745_01E02F40(void);
    extern void b745_01E03320(void);
    extern void b745_01E034D0(void);
    extern void b745_01E035F0(void);
    extern void b745_01E03700(void);
    extern void b745_01E04500(Scene_b745_01E01E40 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;

    g->t++;
    if (g->t == 1) {
        b745_01E04500(g, b745_01E035F0, 0);
    }
    if (g->t == 1) {
        b745_01E04500(g, b745_01E03700, 0);
    }
    if (g->t == 98) {
        g->side = 0;
        b745_01E04500(g, b745_01E03320, 0);
    }
    if (g->t == 98) {
        func_001F5F90(func_001F5380(), &g->mark);
    }
    if (g->t >= 98 && g->t < 113) {
        g->pos = g->mark;
        g->pos.y = 35.0f;
        for (i = 0; i < 5; i++) {
            b745_01E04500(g, b745_01E02510, 0);
        }
        for (i = 0; i < 5; i++) {
            b745_01E04500(g, b745_01E026C0, 0);
        }
        g->side = 0;
        b745_01E04500(g, b745_01E02A70, 0);
        if (g->t == 98) {
            g->ang = 0;
            g->side = 0;
            b745_01E04500(g, b745_01E02870, 0);
            g->ang = 90;
            g->side = 0;
            b745_01E04500(g, b745_01E02870, 0);
            g->ang = 45;
            g->side = 1;
            b745_01E04500(g, b745_01E02870, 0);
            g->ang = 135;
            g->side = 1;
            b745_01E04500(g, b745_01E02870, 0);
        }
        if (g->t == 98) {
            b745_01E04500(g, b745_01E034D0, 0);
        }
    }
    if (g->t < 99) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        b745_01E04500(g, b745_01E02290, 0);
    }
    if (g->t == 75 || g->t == 95) {
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b745_01E04500(g, b745_01E02F40, 0);
        }
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b745_01E04500(g, b745_01E02F40, 0);
        }
    }
}

/* shape b745:01E02290, 158 insns: b530:01E01D40 family dark (0x18) puff: size 40..59 before scene count 78 (ctx+0xB2BC), else 80..119, growing 1; frame 0..2, f50 5..14 growing half of 5..14 before count 78 and all of it after, angle 0..359, f8 0..34, life 5..12: alpha up by 64 to 0xC0, then down by 19 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0xB2BC];
    s16 count;
} Ctx_b745_01E02290;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b745_01E02290;

static s32 func_01E02290_b745(Ctx_b745_01E02290 *g, Fx_b745_01E02290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 f;

    if (o->mode == 1) {
        if (g->count < 78) {
            o->f48 = func_0019A5C8() % 20 + 40;
        } else {
            o->f48 = func_0019A5C8() % 40 + 80;
        }
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 5;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 8 + 5;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    if (o->tick != 0) {
        if (g->count < 78) {
            f = o->speed;
            f /= 2.0f;
            o->f50 = o->f50 + f;
        } else {
            o->f50 = o->f50 + o->speed;
        }
    }
    o->tick++;
    return 0;
}

/* shape b745:01E02510, 105 insns: a blue spark: size 30..44, random sub-frame 0..2, height 10..19, angle, rise 20..39, width 0..34,
   hold 3..5, rising once started; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

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
} Obj_b745_01E02510;

static s32 func_01E02510_b745(void *arg0, Obj_b745_01E02510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 0x1E;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        o->y = func_0019A5C8() % 10 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x14;
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
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b745:01E026C0, 105 insns: a blue spark: size 10..24, random sub-frame 0..2, height 10..19, angle, rise 20..39, width 0..34,
   hold 3..5, rising once started; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

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
} Obj_b745_01E026C0;

static s32 func_01E026C0_b745(void *arg0, Obj_b745_01E026C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 0xA;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        o->y = func_0019A5C8() % 10 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x14;
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
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b745:01E02870, 127 insns: b590:01E01FA0 with white and red colours, f30 20 and f34 870 (kind 0) or 630 (kind 1) */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b745_01E02870;

static s32 func_01E02870_b745(s32 arg0, Obj_b745_01E02870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0x40, 0x40);
        if (o->h50 == 0) {
            o->f30 = 20.0f;
            o->f34 = 870.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 20.0f;
            o->f34 = 630.0f;
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
    if (o->h50 == 0) {
        if (o->t != 0) {
            o->f34 += 160.0f;
        }
        if (o->t != 0) {
            o->f30 += 1.0f;
        }
    }
    if (o->h50 == 1) {
        if (o->t != 0) {
            o->f34 += 80.0f;
        }
        if (o->t != 0) {
            o->f30 += 0.5f;
        }
    }
    if (o->t != 0) {
        if (o->h52 < 25) {
            o->h52++;
        }
    }
    o->t++;
    return 0;
}

/* shape b745:01E02A70 (B745_OBJ_MOVE_6_), 308 insns, 1 copy: b293:01E022F0's growing ring in blue/green/grey kinds (by the scene side at
   0xB2BC); kind 0 also spins 0x80 a tick one way or the other, kind 2 starts 70 up; fades by 11 */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x1C];
    s32 f24;
    u8 pad28[8];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
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
    u8 col0[4];
    u8 col1[4];
} Fx_b745_01E02A70;

typedef struct {
    u8 pad0[0xB2BC];
    s16 side;
} Game_b745_01E02A70;

static s32 func_01E02A70_b745(Game_b745_01E02A70 *g, Fx_b745_01E02A70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->kind == 0) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x80, 0x80, 0xC0);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x80, 0x80, 0xFF);
                func_001076F0(o->col0, 0x38, 0x38, 0x38);
            }
            o->f6 = 8;
        }
        if (o->kind == 1) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x60, 0x80, 0x60);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x40, 0xFF, 0x40);
                func_001076F0(o->col0, 0x38, 0x38, 0x38);
            }
            o->f34 = 10.0f;
            o->f6 = 10;
        }
        if (o->kind == 2) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x50, 0x50, 0x50);
                func_001076F0(o->col0, 0x28, 0x28, 0x28);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x60, 0x60, 0x60);
                func_001076F0(o->col0, 0x30, 0x30, 0x30);
            }
            o->f34 = 70.0f;
            o->f6 = 10;
        }
        if (o->kind == 0) {
            o->f5A = 15;
            o->f5C = 15;
            o->f52 = (func_0019A5C8() >> 4) % 2;
        }
        if (o->kind == 1) {
            o->f5A = 10;
            o->f5C = 3;
        }
        if (o->kind == 2) {
            o->f5A = 60;
            o->f5C = 60;
        }
        o->f38 = func_0019A5C8() % 80 + 350;
        o->f38 = o->f38 / 10.0f;
        o->f30 = 350.0f;
        o->f30 = o->f30 / 10.0f;
        o->mode = 2;
        o->col1[3] = 0;
        o->f24 = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < o->f6) {
        o->col1[3] = 0x80;
    } else if (o->col1[3] > 12) {
        o->col1[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->f48 += o->f38;
        o->f4C = 0.2f * o->f48;
        if (o->f52 == 0) {
            o->f24 += 0x80;
        } else {
            o->f24 -= 0x80;
        }
    }
    if (o->kind == 1) {
        o->f48 += o->f38;
        o->f4C = 0.7f * o->f48;
        o->f34 += o->f38;
    }
    if (o->kind == 2) {
        o->f48 += o->f38;
        o->f4C = 0.7f * o->f48;
        o->f34 += o->f38;
    }
    o->tick++;
    return 0;
}

/* shape b745:01E02F40, 113 insns: a white drifting spark (b522:01E025A0 shape): size 100, sub-frame 2..4, random angle; pushed
   6.6 along it at the start, then drifting 0.5 a frame; alpha up by 0x40 for 10 frames, then down by 9 until it ends; turns */

typedef struct {
    u8 pad0[0xB4C0];
    u8 sin[1];
} Game_b745_01E02F40;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b745_01E02F40;

static s32 func_01E02F40_b745(Game_b745_01E02F40 *g, Obj_b745_01E02F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x64;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 6.6f * func_00108030(g->sin, o->ang, 0);
        o->x += 6.6f * func_00108030(g->sin, o->ang, 1);
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.5f * func_00108030(g->sin, o->ang, 0);
        o->x += 0.5f * func_00108030(g->sin, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
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

static s32 func_01E03110_b745(void *arg0, Obj_b702_01E01BD0 *o) {
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

/* shape b745:01E03320, 108 insns: on start the kind 0x50 picks both colours and the hold 0x6 (0: (0x9F, 0x5F, 0x5F) for
   10 ticks, 1: (0xE0, 0xB0, 0xF0) / (0xD0, 0xA0, 0xF0) for 32, 2: (0x58, 0x58, 0x78) for 22); both alphas grow by 0x78
   (below 0xF0) during the hold, then fade by 14 (the first ends it, the second clears) */

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
} Fx_b745_01E03320;

static s32 func_01E03320_b745(s32 arg0, Fx_b745_01E03320 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col, 0x9F, 0x5F, 0x5F);
            func_001076F0(o->col2, 0x9F, 0x5F, 0x5F);
            o->hold = 10;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xE0, 0xB0, 0xF0);
            func_001076F0(o->col2, 0xD0, 0xA0, 0xF0);
            o->hold = 0x20;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0x58, 0x58, 0x78);
            func_001076F0(o->col2, 0x58, 0x58, 0x78);
            o->hold = 0x16;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x78;
        }
        if (o->col2[3] < 0xF0) {
            o->col2[3] += 0x78;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xF) {
            o->col2[3] -= 14;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b745:01E034D0, 69 insns: constant variant of b287:01E02C80 (0xE->0x12, 150.0f->120.0f) */

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
} Fx_b745_01E034D0;

static s32 func_01E034D0_b745(s32 arg0, Fx_b745_01E034D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 120.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x12) {
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

/* shape b465:01E01F30, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x33, floor 0x30, state at 0xB210 below 0x14 */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b465_01E01F30;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b465_01E01F30;

static s32 func_01E035F0_b745(Game_b465_01E01F30 *g, Fade_b465_01E01F30 *o) {
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

/* shape b745:01E03700, 177 insns: b702:01E02AD0's zooming veil in pale blue (0x80/0x80/0x90, brighter 0x98/0x98/0xB8 on
   scene frame 95); from frame 96 it zooms by 1 to 10; alpha rises until frame 122, then fades by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b745_01E03700;

typedef struct {
    f32 s, t;
    Xyz_b745_01E03700 p;
} Tv_b745_01E03700;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b745_01E03700 v[2];
    u8 tail[0x20];
} Tex_b745_01E03700;

typedef struct {
    u8 pad0[0xB2BC];
    s16 count;
} Ctx_b745_01E03700;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b745_01E03700;

static s32 func_01E03700_b745(Ctx_b745_01E03700 *g, Fx_b745_01E03700 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b745_01E03700 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    if (g->count == 95) {
        func_001076F0(o->col, 0x98, 0x98, 0xB8);
    }
    ((Tex_b745_01E03700 *)(s32)&pk)->flags = 0x26;
    ((Tex_b745_01E03700 *)(s32)&pk)->size = 5;
    ((Tex_b745_01E03700 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b745_01E03700 *)(s32)&pk)->pad4 = 0;
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
    if (g->count < 95) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    }
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->count > 95) {
        if (o->f48 < 10.0f) {
            o->f48 += 1.0f;
        }
    }
    if (g->count < 122) {
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

static s32 func_01E039D0_b745(void) {
    return 0;
}

/* shape b745:01E039E0 (b745), 712 insns, 1 copy: b746:01E045A0's scene manager form: setup (six joints and a camera,
   one type-4 and three type-5 textures, two s8 jitter tables, 30 random s16 0..7, angle from the turn), step
   b745:01E01E40 and every slot except 01E039D0, draw nine kinds of slot; scene code from the timer (1 / 4 / 2 at 98 /
   145 / 130, 6 in 99..124, 8 once the 150-frame countdown runs out) */

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
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b745_01E039E0;

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
    Fx_b745_01E039E0 fx[400];
    u8 padB1A0[0xB1F0 - 0xB1A0];
    s32 tex[3];
    u8 padB1FC[0xB210 - 0xB1FC];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0xB234 - 0xB220];
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
    s8 jit2[0x100];
    u8 padB4BE[2];
    u8 crd[0x170];
} Scene_b745_01E039E0;

static s32 func_01E039E0_b745(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern s32 func_0019A5C8(void);
    extern void b745_01E01E40();
    Scene_b745_01E039E0 *g = (Scene_b745_01E039E0 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    s32 rm8[4];
    s32 ang[4];
    struct { u8 a[0x18]; u8 o[0x70]; } out;
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
        g->count = 150;
        g->jA = func_001F5560(func_001F53A0(), 0xA, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x13, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x2A, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x31, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
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
            g->jit2[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = func_0019A5C8() % 30;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    b745_01E01E40(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E039D0_b745) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E02290_b745) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[0];
                g->u94.uv[0] = g->fx[k].h56 * 32;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                g->hB8 = 2;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b745((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02510_b745) {
                g->tex88 = g->tex[2];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b745((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E026C0_b745) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 1;
                func_01E00920_b745((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02870_b745) {
                g->tex88 = g->tex260[15];
                func_00106080(rm4, 0x9A, 0, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hBE = 0;
                func_01E01900_b745((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02A70_b745) {
                if (g->fx[k].kind == 0) {
                    func_00106080(rm5, 0x97, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                    g->tex88 = g->tex260[15];
                }
                if (g->fx[k].kind == 1) {
                    func_00106080(rm6, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
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
                if (g->fx[k].kind == 0) {
                    g->hB8 = 0x18;
                }
                if (g->fx[k].kind == 2) {
                    g->hB8 = 6;
                }
                g->hBE = 0;
                func_01E014F0_b745((Obj_b065_01E012B0 *)g, (Anim_b065_01E012B0 *)&g->fx[k], 0x20, g->fx[k].pos.p);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F40_b745) {
                g->tex88 = g->tex[1];
                func_00106080(rm7, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                g->hBE = 0;
                func_01E01230_b745((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03110_b745) {
                func_00106080(rm8, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm8;
                g->tex88 = g->tex[0];
                g->u94.uv[0] = g->fx[k].h56 * 32;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b745((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03320_b745) {
                func_001F5F90(func_001F5380(), &v);
                v.z -= 30.0f;
                func_00205440(&v, NULL, out.o, &g->depth);
                if (g->fx[k].kind == 0) {
                    func_01E01C70_b745((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
                if (g->fx[k].kind == 1) {
                    func_01E01C70_b745((s32)g, (u8 *)&g->fx[k], 0x10, g->depth);
                }
                if (g->fx[k].kind == 2) {
                    func_01E01C70_b745((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
            }
            if (g->fx[k].fn == (s32 (*)())func_01E034D0_b745) {
                g->hB8 = 0x24;
                func_01E00ED0_b745((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21, &g->fx[k].pos.c);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x62) {
        return 1;
    }
    if (g->frame == 0x91) {
        return 4;
    }
    if (g->frame == 0x82) {
        return 2;
    }
    if (g->frame > 0x62 && g->frame < 0x7D) {
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

static s32 func_01E04500_b745(Emit_b539_01E03530 *o, s32 a, s32 b) {
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
