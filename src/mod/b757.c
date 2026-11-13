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

static void func_01E00080_b757(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b757(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b757((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b757((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b757(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b757 in the
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

static void func_01E01230_b757(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b757((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E014F0_b757(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

/* shape b757:01E01900 (B757_W_S), 320 insns, 1 copy: the b757 module's event step: counts ticks; at 1 b757:01E02BC0
   and b757:01E029A0; at 161 b757:01E02CD0; at 68, 110, 127, 144 and 192 thirteen b757:01E024A0 on joint 0xB244 (1.5
   lower), at 118, 136 and 192 on joint 0xB246; at 195 the ring point goes to joint 0xB248, pushed 4 along z (back
   when the game value at 0xB2B4 is set); from 195 to 220 the three b757:01E01FD0 ring kinds (0 and 1 on odd ticks, 2
   on even ones) and b757:01E02670 at that point (b757:01E02880 once at 195); below 221 b757:01E01E00 on joint
   0xB24A */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f pt;
    u8 padB1E0[0xB244 - 0xB1E0];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    u8 padB24C[0xB2B0 - 0xB24C];
    s16 kind;
    u8 padB2B2[2];
    s16 v;
    u8 padB2B6[2];
    s16 timer;
} Ctx_b757_01E01900;

static void func_01E01900_b757(Ctx_b757_01E01900 *g) {
    extern s32 b757_01E01E00(void);
    extern s32 b757_01E01FD0(void);
    extern s32 b757_01E024A0(void);
    extern s32 b757_01E02670(void);
    extern s32 b757_01E02880(void);
    extern s32 b757_01E029A0(void);
    extern s32 b757_01E02BC0(void);
    extern s32 b757_01E02CD0(void);
    extern void b757_01E03790(Ctx_b757_01E01900 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;

    g->timer++;
    if (g->timer == 1) {
        b757_01E03790(g, b757_01E02BC0, 0);
    }
    if (g->timer == 1) {
        b757_01E03790(g, b757_01E029A0, 0);
    }
    if (g->timer == 161) {
        b757_01E03790(g, b757_01E02CD0, 0);
    }
    if (g->timer == 68 || g->timer == 110 || g->timer == 127 || g->timer == 144 || g->timer == 192) {
        func_001F5620(func_001F53A0(), g->jA, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b757_01E03790(g, b757_01E024A0, 0);
        }
    }
    if (g->timer == 118 || g->timer == 136 || g->timer == 192) {
        func_001F5620(func_001F53A0(), g->jB, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b757_01E03790(g, b757_01E024A0, 0);
        }
    }
    if (g->timer == 195) {
        func_001F5620(func_001F53A0(), g->jC, &g->pt);
        if (g->v != 0) {
            g->pt.z -= 4.0f;
        } else {
            g->pt.z += 4.0f;
        }
    }
    if (g->timer >= 195 && g->timer < 221) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y -= 20.0f;
        if (g->v != 0) {
            g->pos.z -= 5.0f;
        } else {
            g->pos.z += 5.0f;
        }
        g->pos.x = g->pt.x;
        g->pos.y = g->pt.y;
        g->pos.z = g->pt.z;
        g->kind = 0;
        if (g->timer % 2 == 1) {
            b757_01E03790(g, b757_01E01FD0, 0);
        }
        g->kind = 1;
        if (g->timer % 2 == 1) {
            b757_01E03790(g, b757_01E01FD0, 0);
        }
        g->kind = 2;
        if (g->timer % 2 == 0) {
            b757_01E03790(g, b757_01E01FD0, 0);
        }
        b757_01E03790(g, b757_01E02670, 0);
        if (g->timer == 195) {
            b757_01E03790(g, b757_01E02880, 0);
        }
    }
    if (g->timer < 221) {
        func_001F5620(func_001F53A0(), g->jD, &g->pos);
        b757_01E03790(g, b757_01E01E00, 0);
    }
}

/* shape b757:01E01E00, 114 insns: b702:01E01A00 twin: random size 80..119, spin 5..14, held 5..12 ticks */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
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
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b757_01E01E00;

static s32 func_01E01E00_b757(s32 arg0, Obj_b757_01E01E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 40 + 80;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->h50 = func_0019A5C8() % 10 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 5;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 8 + 5;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f48 += 1.0f;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b757:01E01FD0 (B757_OBJ_MOVE_6_), 308 insns, 1 copy: b293:01E022F0's growing ring in green/green/grey kinds (by the scene side at
   0xB2B8); kind 0 also spins 0x80 a tick one way or the other, kind 2 starts 70 up; fades by 11 */

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
} Fx_b757_01E01FD0;

typedef struct {
    u8 pad0[0xB2B8];
    s16 side;
} Game_b757_01E01FD0;

static s32 func_01E01FD0_b757(Game_b757_01E01FD0 *g, Fx_b757_01E01FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->kind == 0) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x80, 0xC0, 0x80);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x80, 0xFF, 0x80);
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

/* shape b606:01E01D00, 113 insns, 2 copies: a white drifter: set up once (size 100, random frame 2..4 and heading, pushed 6.6
   along it); fades in over 10 frames, then out; drifts 0.5 a frame along its heading (world trig table);
   turns each frame (b422:01E01790 family) */

typedef struct {
    u8 pad0[0xB4BC];
    u8 trig[1];
} World_b606_01E01D00;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    u8 x20[0x34];
    s16 t;
    s16 frame;
    s16 state;
    s16 head;
    u8 pad5C[4];
    u8 c0[4];
} Drift_b606_01E01D00;

static s32 func_01E024A0_b757(World_b606_01E01D00 *w, Drift_b606_01E01D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h8 = 0x64;
        o->hA = o->h8;
        o->frame = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->head = (func_0019A5C8() >> 4) % 360;
        o->z += 6.6f * func_00108030(w->trig, o->head, 0);
        o->x += 6.6f * func_00108030(w->trig, o->head, 1);
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 0.5f * func_00108030(w->trig, o->head, 0);
        o->x += 0.5f * func_00108030(w->trig, o->head, 1);
    }
    func_00205C40((s32)o->x20);
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

static s32 func_01E02670_b757(void *arg0, Obj_b702_01E01BD0 *o) {
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

/* shape b757:01E02880, 69 insns: constant variant of b287:01E02C80 (0xE->0x22, 150.0f->200.0f) */

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
} Fx_b757_01E02880;

static s32 func_01E02880_b757(s32 arg0, Fx_b757_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 200.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x22) {
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

/* shape b757:01E029A0, 136 insns: a scene light that follows joint 0xB248: on start colour (128, 100, 100, 100),
   0xB1C0 0, 0xB1C4 123, level 0, placed at the effect position; it brightens by 0.3 (to 1) for 210 ticks, then dims by
   0.3 and ends at 0.1; the light is handed to func_001F6C10 while alive (NULL once ended); ends when 0xB210 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b757_01E029A0;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b757_01E029A0 light;
    u8 padB1CC[0x44];
    s32 flag;
    u8 padB214[0x34];
    s16 joint;
} Scene_b757_01E029A0;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x34];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fx_b757_01E029A0;

static s32 func_01E029A0_b757(Scene_b757_01E029A0 *g, Fx_b757_01E029A0 *o) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6C10(void *);
    Vec4f v[2];

    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 100.0f;
        g->light.c[2] = 100.0f;
        g->light.c[3] = 100.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 123.0f;
        g->light.level = 0.0f;
        g->light.pos.x = o->x;
        g->light.pos.y = o->y;
        g->light.pos.z = o->z;
        o->mode = 2;
        o->h50 = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, v);
    g->light.pos.x = v[0].x;
    g->light.pos.y = v[0].y;
    g->light.pos.z = v[0].z;
    if (o->t < 0xD2) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.3f;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.3f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b180:01E021D0, 66 insns: volume fade for a scene: starts at 0x80, fades down by 10 (floor 0x30) for the
   first 0x97 ticks, then back up by 10 (cap 0x80) while the game state is below 0x1E; state 3 forces full volume */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b180_01E021D0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b180_01E021D0;

static s32 func_01E02BC0_b757(Game_b180_01E021D0 *g, Fade_b180_01E021D0 *o) {
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

/* shape b757:01E02CD0, 136 insns: b763:01E032F0's full-screen veil, brightening until scene frame 250 (s16 at 0xB2B8) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b757_01E02CD0;

typedef struct {
    f32 s, t;
    Xyz_b757_01E02CD0 p;
} Tv_b757_01E02CD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b757_01E02CD0 v[2];
    u8 tail[0x20];
} Tex_b757_01E02CD0;

typedef struct {
    u8 pad0[0xB2B8];
    s16 frame;
} Ctx_b757_01E02CD0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b757_01E02CD0;

static s32 func_01E02CD0_b757(Ctx_b757_01E02CD0 *g, Fx_b757_01E02CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b757_01E02CD0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    ((Tex_b757_01E02CD0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b757_01E02CD0 *)(s32)&pk)->size = 5;
    ((Tex_b757_01E02CD0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b757_01E02CD0 *)(s32)&pk)->pad4 = 0;
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
    if (g->frame < 0xFA) {
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

static s32 func_01E02EF0_b757(void) {
    return 0;
}

/* shape b757:01E02F00 (b757), 545 insns, 1 copy: b757 scene manager in b750:01E02F60 form: setup (six joints and a
   camera, one type-4 and two type-5 textures, two s8 jitter tables and 30 random s16 0..7, angle from the turn), step
   b757:01E01900 and every slot but the empty handler, draw five kinds (two jittered sprite kinds, the green ring with
   three looks, the white drifter, the constant ring), scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b757_01E02F00;

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
    Fx_b757_01E02F00 fx[400];
    u8 padB1A0[0x30];
    Vec4f colB1D0;
    u8 padB1E0[0x10];
    s32 tex[3];
    u8 padB1FC[0x14];
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
    s16 rnd[30];
    u8 padB2A0[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padB4BA[2];
    u8 crd[0x174];
} Scene_b757_01E02F00;

static s32 func_01E02F00_b757(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void func_01E01900_b757();
    extern void func_01E00ED0_b757();
    extern void func_01E00920_b757();
    extern void func_01E01230_b757();
    extern void func_01E014F0_b757();
    extern s32 func_01E02EF0_b757();
    extern s32 func_01E01E00_b757();
    extern s32 func_01E01FD0_b757();
    extern s32 func_01E024A0_b757();
    extern s32 func_01E02670_b757();
    extern s32 func_01E02880_b757();
    Scene_b757_01E02F00 *g = (Scene_b757_01E02F00 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s32 (*fn)();

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 270;
        g->jA = func_001F5560(func_001F53A0(), 0xE, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x23, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x24, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
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
            g->jit2[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = func_0019A5C8() % 30;
        }
        for (k = 0; k < 30; k++) {
            g->rnd[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E01900_b757(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            fn = g->fx[k].fn;
            if (fn != NULL) {
                if (fn != func_01E02EF0_b757) {
                    fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == func_01E01E00_b757) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[1];
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                g->hB8 = 2;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b757(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == func_01E01FD0_b757) {
                if (g->fx[k].h50 == 0) {
                    func_00106080(rm2, 0x97, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                    g->tex88 = g->tex260[15];
                }
                if (g->fx[k].h50 == 1) {
                    func_00106080(rm3, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                    g->tex88 = g->tex260[15];
                }
                if (g->fx[k].h50 == 2) {
                    g->tex88 = g->tex[1];
                    g->hBE = 0;
                    g->u94.uv[0] = g->fx[k].h56 << 5;
                    g->u94.uv[1] = 0;
                    g->u94.uv[2] = 0x20;
                    g->u94.uv[3] = 0x40;
                }
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x24;
                if (g->fx[k].h50 == 0) {
                    g->hB8 = 0x18;
                }
                if (g->fx[k].h50 == 2) {
                    g->hB8 = 6;
                }
                g->hBE = 0;
                func_01E014F0_b757(g, &g->fx[k], 0x20, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == func_01E024A0_b757) {
                g->tex88 = g->tex[0];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hBE = 0;
                func_01E01230_b757(g, &g->fx[k], 0x10, &g->fx[k].pos);
            }
            if (g->fx[k].fn == func_01E02670_b757) {
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->tex88 = g->tex[1];
                g->u94.uv[0] = g->fx[k].h56 << 5;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x20;
                g->u94.uv[3] = 0x40;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b757(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == func_01E02880_b757) {
                g->hB8 = 0x24;
                func_01E00ED0_b757(g, &g->fx[k], 0x21, &g->colB1D0);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xB5) {
        return 1;
    }
    if (g->frame == 0x109) {
        return 4;
    }
    if (g->frame == 0xF0) {
        return 2;
    }
    if (g->frame > 0xBF && g->frame < 0xEB) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b236:01E02330, 98 insns, 15 copies: take a free effect slot (400 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b236_01E02330 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b236_01E02330;

typedef struct Obj_b236_01E02330 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b236_01E02330 slots[400];
    u8 padB1A0[0x74];
    u8 rgba[4];
    u8 padB218[0x98];
    s16 fB2B0;
} Obj_b236_01E02330;

static s32 func_01E03790_b757(Obj_b236_01E02330 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b236_01E02330 *s = NULL;
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
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}
