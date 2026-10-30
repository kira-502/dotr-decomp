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

static void func_01E00080_b259(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b259(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b259((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b259((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b259 in the
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

static void func_01E00ED0_b259(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b259((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b041:01E00CF0, 182 insns: b016:01E00ED0 plus func_00109100(view, {.., .., cam 0x5A}, 2, obj 0xD8) after the view setup; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b259 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b041_01E00CF0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x2A];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b041_01E00CF0;

typedef struct Obj_b041_01E00CF0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b041_01E00CF0;

typedef struct Xyz_b041_01E00CF0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b041_01E00CF0;

typedef struct Uv_b041_01E00CF0 {
    f32 u, v;
} Uv_b041_01E00CF0;

typedef struct Pk_b041_01E00CF0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b041_01E00CF0 uv;
    u64 pad18;
    Xyz_b041_01E00CF0 v[4];
    u64 pad60[6];
} Pk_b041_01E00CF0;

typedef struct Buf_b041_01E00CF0 {
    u64 tag;
    Pk_b041_01E00CF0 pk;
} Buf_b041_01E00CF0;

static void func_01E01190_b259(Obj_b041_01E00CF0 *obj, Cam_b041_01E00CF0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b041_01E00CF0 buf;
    Uv_b041_01E00CF0 uv;
    s32 sel;
    s32 mode;
    Pk_b041_01E00CF0 *p = &buf.pk;

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
    func_01E00080_b259((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01470_b259(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E017D0_b259(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b259:01E019A0 (B259_W_S), 122 insns, 1 copy: the scene script: counts the scene frame (0x86C6); on frame 1
   it spawns b259:01E02970 and (slot 1) b259:01E028B0; on frame 56 b259:01E02150 and b259:01E02250; from frame 91 to 239
   one b259:01E01B90 at each of the two joints a frame, and from frame 11 to 159 one b259:01E02590 at each */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x8690 - 0x25C];
    s16 joint0;
    s16 joint1;
    u8 pad8694[0x86BE - 0x8694];
    s16 idx;
    u8 pad86C0[0x86C6 - 0x86C0];
    s16 t;
} Scene_b259_01E019A0;

static s32 func_01E01B90_b259();
static s32 func_01E02150_b259();
static s32 func_01E02250_b259();
static s32 func_01E02590_b259();
static s32 func_01E028B0_b259();
static s32 func_01E02970_b259();
static s32 func_01E033C0_b259();

static void func_01E019A0_b259(Scene_b259_01E019A0 *s) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    s->t++;
    if (s->t == 1) {
        func_01E033C0_b259(s, func_01E02970_b259, 0);
        s->idx = 0; /* both stores are in the original */
        s->idx = 1;
        func_01E033C0_b259(s, func_01E028B0_b259, 0);
    }
    if (s->t == 56) {
        func_01E033C0_b259(s, func_01E02150_b259, 0);
        func_01E033C0_b259(s, func_01E02250_b259, 0);
    }
    if (s->t > 90 && s->t < 240) {
        func_001F5620(func_001F53A0(), s->joint0, &s->px);
        func_01E033C0_b259(s, func_01E01B90_b259, 0);
        func_001F5620(func_001F53A0(), s->joint1, &s->px);
        func_01E033C0_b259(s, func_01E01B90_b259, 0);
    }
    if (s->t > 10 && s->t < 160) {
        func_001F5620(func_001F53A0(), s->joint0, &s->px);
        func_01E033C0_b259(s, func_01E02590_b259, 0);
        func_001F5620(func_001F53A0(), s->joint1, &s->px);
        func_01E033C0_b259(s, func_01E02590_b259, 0);
    }
}

/* shape b259:01E01B90, 269 insns: b428:01E014F0's grey puff, 10 square growing to 25, drift /400, sliding along z
   by the scene flag (ctx+0x86C2) at a speed growing from 2.2 by 0.1 to 4.5, sinking 0.4; on tick 44 it copies its
   position to ctx+0x250, spawns b259:01E023D0 and b259:01E02760 once the scene count (ctx+0x86C6) reaches 159, and
   ends; blinks grey; past count 300 its tick jumps to 90 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x86C2 - 0x260];
    s16 flip;
    u8 pad86C4[2];
    s16 count;
} Ctx_b259_01E01B90;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b259_01E01B90;

static s32 func_01E01B90_b259(Ctx_b259_01E01B90 *ctx, Obj_b259_01E01B90 *o) {
    extern s32 b259_01E023D0(void);
    extern s32 b259_01E02760(void);
    extern s32 b259_01E033C0(Ctx_b259_01E01B90 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    f32 d;

    if (o->state == 1) {
        o->hA = o->h8 = 10;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->f38 = 2.2f;
        d = (func_0019A5C8() >> 4) % 50 - 25;
        d /= 20.0f;
        o->pos.y += d;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->h5A = func_0019A5C8() % 360;
        o->rot[0] = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot[1] = 0x4000;
    }
    if (o->t < 50) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (ctx->flip != 0) {
            o->pos.z -= o->f38;
        } else {
            o->pos.z += o->f38;
        }
        if (o->f38 < 4.5f) {
            o->f38 += 0.1f;
        }
        o->pos.x += o->f30;
        o->pos.y += o->f34 - 0.4f;
        if (o->h8 < 25) {
            o->h8++;
        }
        if (o->hA < 25) {
            o->hA++;
        }
    }
    if (o->t == 44) {
        ctx->pos = o->pos;
        if (ctx->count >= 159) {
            b259_01E033C0(ctx, b259_01E023D0, 0);
            b259_01E033C0(ctx, b259_01E02760, 0);
        }
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0x70);
    }
    o->t++;
    if (ctx->count > 300) {
        o->t = 90;
    }
    o->h5A += 40;
    return 0;
}

/* shape b259:01E01FD0, 96 insns: a red-yellow flicker glow on a model joint: size 0/40, hold 250; second alpha up by 0x50 until the
   hold, then down by 12 until it ends; second colour flickers by frame parity; spins a quarter turn and follows the joint */

typedef struct {
    u8 pad0[0x8690];
    s16 joint[1];
} Game_b259_01E01FD0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 jidx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b259_01E01FD0;

static s32 func_01E01FD0_b259(Game_b259_01E01FD0 *g, Obj_b259_01E01FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0xC0, 0x40, 0x40);
        o->hold = 0xFA;
        o->f4C = 40.0f;
        o->h5A = 0xA;
        o->h5C = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->c1[3] < 0xA0) {
            o->c1[3] += 0x50;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    func_001F5620(func_001F53A0(), g->joint[o->jidx], &o->pos);
    return 0;
}

/* shape b259:01E02150, 63 insns: grey glow with two colours: on start both 0x80 grey, hold 0x6 = 10; both alphas
   grow by 0x2A (below 0x80) during the hold, then fade by 12 (the first one ends the effect) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x4C];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b259_01E02150;

static s32 func_01E02150_b259(s32 arg0, Fx_b259_01E02150 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->hold = 10;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 0xD) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xD) {
            o->col2[3] -= 12;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b259:01E02250, 94 insns: follows model point 0x8690 rising by f34; on start 0x8/0xA = 28, f34 3, variant 0,
   colour 0x80 grey, turned 0x8000 when the game flag 0x86C2 is set; alpha grows by 0x2A (below 0x80) for 8 ticks,
   then fades by 9 and stops while 0x8/0xA count down and f34 slows by 0.1 */

typedef struct {
    u8 pad0[0x8690];
    s16 point;
    u8 pad8692[0x30];
    s16 flag;
} Game_b259_01E02250;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 pos[4];
    u8 pad20[4];
    s32 f24;
    u8 pad28[0xC];
    f32 rise;
    u8 pad38[0x1C];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b259_01E02250;

static s32 func_01E02250_b259(Game_b259_01E02250 *g, Fx_b259_01E02250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f8 = 28;
        o->fA = 28;
        o->rise = 3.0f;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        if (g->flag != 0) {
            o->f24 = 0x8000;
        } else {
            o->f24 = 0;
        }
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->f8 > 0) {
            o->f8--;
        }
        if (o->fA > 0) {
            o->fA--;
        }
        if (!(o->rise <= 0.0f)) {
            o->rise -= 0.1f;
        }
    }
    func_001F5620(func_001F53A0(), g->point, o->pos);
    o->pos[1] += o->rise;
    o->tick++;
    return 0;
}

/* shape b259:01E023D0, 110 insns: b282:01E01C20 family blinking red spark (size 8, frame 4, angle 10..29, spin 4..10, size 1..8), alpha 0xC0 held 20..22 ticks, then out by 11 and ends */

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
} Obj_b259_01E023D0;

static s32 func_01E023D0_b259(s32 arg0, Obj_b259_01E023D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 8.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0x60, 0x60);
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 7 + 4;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 20;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x60, 0x60);
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b259:01E02590, 114 insns: blinking spark with random radius, angle and life; dies when the scene timer
   passes 240 */

typedef struct Sp_b259_01E02590 {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 spin;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 rad;
    u8 pad52[2];
    s16 age;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Sp_b259_01E02590;

typedef struct Scn_b259_01E02590 {
    u8 pad0[0x86C6];
    s16 timer;
} Scn_b259_01E02590;

static s32 func_01E02590_b259(Scn_b259_01E02590 *w, Sp_b259_01E02590 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->f48 = 2.0f;
        o->h56 = 3;
        func_001076F0(o->col, 0xFF, 0x60, 0x60);
        o->rad = func_0019A5C8() % 8 + 4;
        o->ang = func_0019A5C8() % 360;
        o->spin = 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 5;
        o->state = 2;
    }
    if (o->age < o->life) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 12) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->age % 2 == 1) {
        func_001076F0(o->col, 0xCF, 0xCF, 0xFF);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x80);
    }
    if (o->age != 0) {
        o->rad += o->spin;
    }
    o->age++;
    if (w->timer >= 0xF1) {
        o->state = 0;
    }
    return 0;
}

/* shape b259:01E02760, 83 insns, 2 copies: a blinking marker: set up once (white and red, size 80); the second colour fades in
   for the first frames, then out; it blinks between yellow and dim each frame while turning (b016:01E01FF0
   family) */

typedef struct {
    u8 pad0[6];
    s16 fade;
    u8 pad8[0x18];
    s32 rot;
    u8 pad24[0x24];
    s32 w48;
    f32 size;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b259_01E02760;

static s32 func_01E02760_b259(void *arg0, Obj_b259_01E02760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w48 = 0;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xC0, 0x40, 0x40);
        o->fade = 4;
        o->size = 80.0f;
        o->h5C = o->h5A = 0x14;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->fade) {
        if (o->c1[3] < 0xA0) {
            o->c1[3] += 0x50;
        }
    } else if (o->c1[3] > 0x14) {
        o->c1[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b259:01E028B0, 48 insns: variant of b445:01E03C90 (volume fade): game state at 0x8650, floor 0x20 */

typedef struct {
    u8 pad[0x8650];
    s32 state;
} Game_b259_01E028B0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b259_01E028B0;

static s32 func_01E028B0_b259(Game_b259_01E028B0 *g, Fade_b259_01E028B0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
        if (o->vol > 0x20) {
            o->vol -= 10;
        } else {
            o->vol = 0x20;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    func_001F6D00((u8)o->vol);
    return 0;
}

/* shape b259:01E02970, 147 insns: b232:01E01130 family still grey (0x80) full-screen window in the scene packet (ctx+0x8670), alpha up by 18 to 0x70 for 250 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b259_01E02970;

typedef struct {
    f32 s, t;
    Xyz_b259_01E02970 p;
} Tv_b259_01E02970;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b259_01E02970 v[2];
} Tex_b259_01E02970;

typedef struct {
    u8 pad[0x8670];
    Tex_b259_01E02970 *pk;
} Game_b259_01E02970;

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b259_01E02970;

static s32 func_01E02970_b259(Game_b259_01E02970 *g, Fx_b259_01E02970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
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
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 250) {
        if (o->col[3] < 0x70) {
            o->col[3] += 18;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b259", func_01E02BC0_b259);

/* shape b259:01E033C0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x12c of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b259_01E033C0 {
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
} Slot_b259_01E033C0;

typedef struct Obj_b259_01E033C0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b259_01E033C0 slots[0x12c];
    u8 padB[0x8654 - 0x2a0 - 0x12c * 0x70];
    u8 rgba[4];
    u8 padC[0x86be - 0x8654 - 4];
    s16 fB2B0;
} Obj_b259_01E033C0;

static s32 func_01E033C0_b259(Obj_b259_01E033C0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b259_01E033C0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x12c; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x12c;
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

/* shape b259:01E03550, 89 insns: b183:01E029E0 family draw pass that counts: every live slot (300 of 0x70 bytes) whose handler is shape b259:01E02970 is drawn and counted; the packet is sent only when something drew */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b259_01E03550;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b259_01E03550 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b259_01E03550;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b259_01E03550;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b259_01E03550 slot[300];
    u8 padEnd[0x866C - 0x2A0 - 300 * 0x70];
    s32 ctx;
    Pkt_b259_01E03550 *pkt;
} Scene_b259_01E03550;

static void func_01E03550_b259(Scene_b259_01E03550 *s) {
    extern void b259_01E02970(Scene_b259_01E03550 *, Slot_b259_01E03550 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b259_01E03550 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
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
    for (i = 0; i < 300; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b259_01E02970) {
            n++;
            b259_01E02970(s, &s->slot[i]);
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
