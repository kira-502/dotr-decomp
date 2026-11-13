#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b433(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b433(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b433(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b433((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b433((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b433 in the
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

static void func_01E00F60_b433(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b433((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01220_b433(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b016:01E018F0, 177 insns: b016:01E00ED0 with the view matrix's [2][1] and [3][1] cleared; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b433 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E018F0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E018F0;

typedef struct Obj_b016_01E018F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E018F0;

typedef struct Xyz_b016_01E018F0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E018F0;

typedef struct Uv_b016_01E018F0 {
    f32 u, v;
} Uv_b016_01E018F0;

typedef struct Pk_b016_01E018F0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E018F0 uv;
    u64 pad18;
    Xyz_b016_01E018F0 v[4];
    u64 pad60[6];
} Pk_b016_01E018F0;

typedef struct Buf_b016_01E018F0 {
    u64 tag;
    Pk_b016_01E018F0 pk;
} Buf_b016_01E018F0;

static void func_01E01580_b433(Obj_b016_01E018F0 *obj, Cam_b016_01E018F0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E018F0 buf;
    Uv_b016_01E018F0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E018F0 *p = &buf.pk;

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
    func_01E00110_b433((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    view[2][1] = 0.0f;
    view[3][1] = 0.0f;
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

INCLUDE_ASM("asm/nonmatchings/mod/b433", func_01E01850_b433);

/* shape b433:01E02170, 120 insns: constant variant of b611:01E01BD0 (f48 100..129, spin 26..45, life 7..20, alpha +0x2A below 0x80, fade 9, colour (0xFF,0xA0,0xA0)) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
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
} Fx_b433_01E02170;

static s32 func_01E02170_b433(s32 arg0, Fx_b433_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 30 + 100;
        o->f56 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xA0, 0xA0);
        o->f50 = func_0019A5C8() % 50 + 100;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 20 + 26;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 14 + 7;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick < 0x5A) {
        if (o->tick != 0) {
            o->f50 += o->spin;
        }
    }
    if (o->tick < 0x8C) {
        o->f48 += 6.0f;
    }
    o->tick++;
    return 0;
}

/* shape b433:01E02350, 178 insns: a grey (0x80) ring 15 x 15, frame 4, placed at the effect point in its slot's scene entry (ctx+0xE0B0), with a random 0..359 turn (ctx+0xEABC) and radius 5.0..36.9 (ctx+0xE8A4) per slot, f5C 4..17; both alphas up by 42 to 0x80 for 48 ticks, then down by 14; flickers white/grey; spins 5 while the slot turn falls 18; ends past scene count 170 (ctx+0xEBC2) */

typedef struct {
    u8 pad0[0xE0B0];
    Vec4f pts[1];
    u8 padE0C0[0xE8A4 - 0xE0C0];
    f32 rad[1];
    u8 padE8A8[0xEABC - 0xE8A8];
    s16 ang[1];
    u8 padEABE[0xEBC2 - 0xEABE];
    s16 count;
} Ctx_b433_01E02350;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x20];
    s16 slot;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b433_01E02350;

static s32 func_01E02350_b433(Ctx_b433_01E02350 *g, Fx_b433_01E02350 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 15;
        o->h = 15;
        o->f56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        g->pts[o->slot].x = o->pos[0];
        g->pts[o->slot].y = o->pos[1];
        g->pts[o->slot].z = o->pos[2];
        o->mode = 2;
        o->col2[3] = 0;
        g->ang[o->slot] = (func_0019A5C8() >> 4) % 360;
        g->rad[o->slot] = (func_0019A5C8() >> 4) % 320 + 50;
        g->rad[o->slot] /= 10.0f;
        o->f5C = (func_0019A5C8() >> 4) % 14 + 4;
    }
    if (o->tick < 48) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 15) {
            o->col2[3] -= 14;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40((s32)o->rot);
    o->f5A += 5;
    g->ang[o->slot] -= 18;
    o->tick++;
    if (g->count >= 171) {
        o->mode = 0;
    }
    return 0;
}

/* shape b433:01E02620, 113 insns: a red rising spark (b433:01E027F0 shape): size 10..19, random sub-frame 0..3 and y turn, frame
   from 1, height 100..199 rising by 10..24, angle, width 1..8, hold 13..22; full alpha until the hold, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x14];
    s32 rot1;
    u8 pad28[0x20];
    f32 size;
    u8 pad4C[4];
    s16 y;
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b433_01E02620;

static s32 func_01E02620_b433(void *arg0, Obj_b433_01E02620 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 0xA;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->rot1 = func_0019A5C8() % 65535;
        o->frame = 1;
        o->y = func_0019A5C8() % 100 + 0x64;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 15 + 0xA;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 10 + 0xD;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b433:01E027F0, 106 insns: a red rising spark: size 10..19, random sub-frame 0..3, frame from 1 counting up, height
   10..29 rising by 10..24, angle, width 1..8, hold 13..22; full alpha until the hold, then down by 11 until it ends */

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
    s16 frame;
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b433_01E027F0;

static s32 func_01E027F0_b433(void *arg0, Obj_b433_01E027F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 0xA;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->frame = 1;
        o->y = func_0019A5C8() % 20 + 0xA;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->step = func_0019A5C8() % 15 + 0xA;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 10 + 0xD;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b433:01E029A0, 70 insns: a pink growing spark (b252:01E03410 shape): size 70 */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b433_01E029A0;

static s32 func_01E029A0_b433(void *arg0, Obj_b433_01E029A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x46;
        o->h = 0x46;
        o->sub = func_0019A5C8() % 6 + 2;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xA0, 0xAF);
        o->state = 2;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->w < 0x5A) {
            o->w++;
        }
        if (o->h < 0x5A) {
            o->h++;
        }
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b433:01E02AC0, 96 insns: a red spark (size 70, random frame 0..7, random heading) spinning a random 10..24 a tick from 10..29, size 1..8, held 6..10 ticks at 0x80, then out by 11 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b433_01E02AC0;

static s32 func_01E02AC0_b433(s32 arg0, Obj_b433_01E02AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 70.0f;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->h52 = 1;
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->hE = func_0019A5C8() % 15 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 5 + 6;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->h52++;
    o->h50 += o->hE;
    o->t++;
    return 0;
}

/* shape b433:01E02C40, 79 insns: a pink drifting spark (b252:01E03410 family): size 70 growing by 1, random sub-frame 2..7, f34 0.5;
   alpha up by 0x60 to 0xC0 for 3 frames, then down by 9 until it ends; drifts 0.5 in x by direction; random turn */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    u8 pad14[0xC];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x18];
    s16 dir;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b433_01E02C40;

static s32 func_01E02C40_b433(void *arg0, Obj_b433_01E02C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x46;
        o->h = 0x46;
        o->sub = func_0019A5C8() % 6 + 2;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xA0, 0xAF);
        o->state = 2;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->w++;
        o->h++;
    }
    if (o->dir == 0) {
        o->x += 0.5f;
    } else {
        o->x -= 0.5f;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b433:01E02D80, 204 insns: b743:01E02D60's white trail spark with b433's scene tables (trail 0x7030 + 0xF0 k,
   point 0xE0B0, radius 0xE8A4, angle 0xEABC, trig 0xEDC4); alphas rise for 48 ticks, and it ends once the scene
   count ctx+0xEBC2 reaches 171 */

typedef struct {
    u8 pad0[0x7030];
    Vec4f tr[1][15];
    u8 pad7120[0xE0B0 - 0x7120];
    Vec4f pt[1];
    u8 padE0C0[0xE8A4 - 0xE0C0];
    f32 rad[1];
    u8 padE8A8[0xEABC - 0xE8A8];
    s16 ang[1];
    u8 padEABE[0xEBC2 - 0xEABE];
    s16 count;
    u8 padEBC4[0xEDC4 - 0xEBC4];
    u8 trig[1];
} Ctx_b433_01E02D80;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 h8;
    u8 padA[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 k;
    u8 pad52[2];
    s16 tick;
    s16 h56;
    s16 mode;
    s16 turn;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b433_01E02D80;

static s32 func_01E02D80_b433(Ctx_b433_01E02D80 *g, Fx_b433_01E02D80 *o) {
    extern void b433_01E00080(Vec4f *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[4];
    s16 k;
    s16 i;
    Vec4f *p;

    k = o->k;
    v[0] = g->pt[k].x + g->rad[k] * func_00108030(g->trig, g->ang[k], 1);
    v[1] = g->pt[o->k].y;
    k = o->k;
    v[2] = g->pt[k].z + g->rad[k] * func_00108030(g->trig, g->ang[k], 0);
    if (o->mode == 1) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        p = g->tr[o->k];
        for (i = 0; i < 15; i++) {
            p[i].x = v[0];
            p[i].y = v[1];
            p[i].z = v[2];
        }
        o->frame = 2;
        o->col[3] = 0;
        o->h8 = 0;
        o->h56 = 4;
        o->size = 7.0f;
        o->mode = 2;
    }
    if (o->tick < 48) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 15) {
            o->col2[3] -= 14;
        }
    }
    if (o->tick < 83) {
        o->turn += 5;
    }
    if (o->tick < 117) {
        b433_01E00080(&g->tr[o->k][14], 15, 0, v);
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    if (o->tick != 0) {
        if (o->frame < 8) {
            o->frame++;
        }
    }
    o->tick++;
    if (g->count >= 171) {
        o->mode = 0;
    }
    return 0;
}

/* shape b433:01E030B0, 59 insns: b764:01E02A60 family spinning ring (pink, height 200): in by 32 up to 0x80 for 12 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x28];
    f32 f4C;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b433_01E030B0;

static s32 func_01E030B0_b433(s32 arg0, Obj_b433_01E030B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f4C = 200.0f;
        func_001076F0(o->col2, 0xFF, 0xC0, 0xC0);
        func_001076F0(o->col, 0xFF, 0xC0, 0xC0);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 12) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x20;
        }
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b433:01E031A0, 79 insns: a pink swelling spark (b252:01E03410 family): size 35 by 70, sub-frame 4, f34 0.5; alpha up by 0x60
   to 0xC0 for 10 frames, then down by 15 until it ends; height swells by 20 sin(angle) while the angle climbs 15 to 180 */

typedef struct {
    u8 pad0[0xEDC4];
    u8 trig[1];
} Game_b433_01E031A0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b433_01E031A0;

static s32 func_01E031A0_b433(Game_b433_01E031A0 *g, Obj_b433_01E031A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x23;
        o->h = 0x46;
        o->sub = 4;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xA0, 0xAF);
        o->state = 2;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->h = o->h + 20.0f * func_00108030(g->trig, o->ang, 0);
    }
    if (o->ang < 0xB4) {
        o->ang += 0xF;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b433:01E032E0, 80 insns: a white-red spinning flash by kind: f4C 150 / 100, frame count 20 / 62, size 10x10; second
   alpha up by 0x50 to 0xA0 for that many frames, then down by 12 until it ends; random turn */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b433_01E032E0;

static s32 func_01E032E0_b433(void *arg0, Obj_b433_01E032E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 0.0f;
        if (o->h50 == 0) {
            func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->c1, 0xC0, 0x40, 0x40);
            o->hold = 0x14;
            o->f4C = 150.0f;
        }
        if (o->h50 == 1) {
            func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->c1, 0xC0, 0x70, 0x70);
            o->hold = 0x3E;
            o->f4C = 100.0f;
        }
        o->w2 = 0xA;
        o->h2 = 0xA;
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
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b433:01E03420, 62 insns: volume fade (b215:01E022A0 shape): down 10 to 0x30 until the game timer at 0xEBC2 reaches 0xDC, then up
   10 capped at 0x80; state 3 at 0xE880 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0xE880];
    s32 state;
    u8 padE884[0xEBC2 - 0xE884];
    s16 timer;
} Game_b433_01E03420;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b433_01E03420;

static s32 func_01E03420_b433(Game_b433_01E03420 *g, Fade_b433_01E03420 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->timer < 0xDC) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b433:01E03520, 133 insns: b233:01E03980's zooming full-screen veil in pink (0xA0, 0x78, 0x78), on the
   standard 0x60-colour effect layout */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b433_01E03520;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b433_01E03520;

typedef struct {
    f32 s, t;
    Xyz_b433_01E03520 p;
} Vtx_b433_01E03520;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b433_01E03520 c;
    Vtx_b433_01E03520 v[2];
    u8 tail[0x20];
} Pkt_b433_01E03520;

typedef struct {
    u8 pad00[0x50];
    s16 h30;
    u8 pad52[2];
    s16 h32;
    u8 pad56[2];
    s16 h36;
    u8 pad5A[6];
    u8 col[4];
} Obj_b433_01E03520;

static inline void tag_b433_01E03520(Pkt_b433_01E03520 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E03520_b433(s32 unused, Obj_b433_01E03520 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b433_01E03520 pkt __attribute__((aligned(8)));
    f32 n;

    n = o->h30;
    tag_b433_01E03520((Pkt_b433_01E03520 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0xA0;
    pkt.c.g = 0x78;
    pkt.c.b = 0x78;
    pkt.c.a = o->col[3];
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    if (o->h30 == 0) {
        pkt.v[0].s = n / 1024.0f;
        pkt.v[0].t = n / 512.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    } else {
        pkt.v[0].s = n / 1024.0f;
        pkt.v[0].t = n / 512.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    }
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, func_00207500(), 0);
    if (o->h32 < 0x41) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    if (o->h30 < 30) {
        o->h30++;
    }
    return 0;
}

/* shape b433:01E03740, 182 insns: b546:01E01F90's screen sheet in red (0x80 blinking 0x60) at ctx+0xE898 whose top edge
   rises 16 lines per unit of its height (0x08, growing by 5 to 20); alpha up by 10 for 4 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b433_01E03740;

typedef struct {
    f32 s, t;
    Xyz_b433_01E03740 p;
} Tv_b433_01E03740;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b433_01E03740 v[2];
} Tex_b433_01E03740;

typedef struct {
    u8 pad[0xE898];
    Tex_b433_01E03740 *pk;
} Game_b433_01E03740;

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b433_01E03740;

static s32 func_01E03740_b433(Game_b433_01E03740 *g, Fx_b433_01E03740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 h;

    h = o->h8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x80, 0, 0);
        o->f48 = 10.0f;
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = (0x720 - h) * 16 - 8;
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
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0, 0);
    } else {
        func_001076F0(o->col, 0x60, 0, 0);
    }
    if (o->h8 < 20) {
        o->h8 += 5;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b433", func_01E03A20_b433);

/* shape b433:01E04550, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0xfa of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b433_01E04550 {
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
} Slot_b433_01E04550;

typedef struct Obj_b433_01E04550 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b433_01E04550 slots[0xfa];
    u8 padB[0xe884 - 0x2a0 - 0xfa * 0x70];
    u8 rgba[4];
    u8 padC[0xebba - 0xe884 - 4];
    s16 fB2B0;
} Obj_b433_01E04550;

static s32 func_01E04550_b433(Obj_b433_01E04550 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b433_01E04550 *s = NULL;
    s16 i;

    for (i = 0; i < 0xfa; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xfa;
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

/* shape b411:01E036C0 (B411PAINT_RAIN12), 717 insns, 5 copies: b847:01E00E60's beam along the module spline from
   point 0, 2 steps of 0.5 per segment, alpha down by col0.a/n, width down by w0/(2n), flags 0/1/2 pick the depth
   (computed / max / -1) */

typedef struct {
    f32 x, y, z, w;
} Vec_b411_01E036C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b411_01E036C0;

typedef struct {
    u8 r, g, b, a;
} Col_b411_01E036C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b411_01E036C0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b411_01E036C0 c;
        u64 st;
        Xyz_b411_01E036C0 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b411_01E036C0;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b411_01E036C0;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[6];
    s16 start;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 width;
    u8 pad4C[0x14];
    Col_b411_01E036C0 col0;
    Col_b411_01E036C0 col1;
} Beam_b411_01E036C0;

static inline Vec_b411_01E036C0 spline_b847_01E00E60(Vec_b411_01E036C0 *p, s32 type, f32 t) {
    Vec_b411_01E036C0 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

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

/* pts aligned: its spill slot, needed for the match */

static void func_01E046E0_b433(Ctx_b411_01E036C0 *c, Beam_b411_01E036C0 *an, Vec_b411_01E036C0 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b411_01E036C0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b411_01E036C0 ab[2];
    Vec_b411_01E036C0 ctrl[4];
    Vec_b411_01E036C0 prev;
    Vec_b411_01E036C0 q[4];
    Vec_b411_01E036C0 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b411_01E036C0 pkt __attribute__((aligned(8)));
    Col_b411_01E036C0 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b411_01E036C0 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    n = an->count;
    w /= 10.0f;
    w0 = w;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 2; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(ctrl, 0, t);
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / n);
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (2.0f * n);
            for (k = 0; k < 2; k++) {
                func_00109A70(&q[0], &ab[0]);
                func_00109A70(&q[1], &ab[0]);
                func_00109A70(&q[2], &ab[1]);
                func_00109A70(&q[3], &ab[1]);
                if (k == 0) {
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if (flags == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                } else if (flags == 2) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, -1);
                    }
                }
            }
        }
    }
}

/* shape b139:01E03820: sibling of b016:01E00ED0 (one sprite quad, drawn twice). Needs func_01E00110_b433 in the
   same file and static (the original reuses $a0 across the call). */

typedef struct Cam_b139_01E03820 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b139_01E03820;

typedef struct Obj_b139_01E03820 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b139_01E03820;

typedef struct Xyz_b139_01E03820 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b139_01E03820;

typedef struct Uv_b139_01E03820 {
    f32 u, v;
} Uv_b139_01E03820;

typedef struct Pk_b139_01E03820 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b139_01E03820 uv;
    u64 pad18;
    Xyz_b139_01E03820 v[4];
    u64 pad60[6];
} Pk_b139_01E03820;

typedef struct Buf_b139_01E03820 {
    u64 tag;
    Pk_b139_01E03820 pk;
} Buf_b139_01E03820;

static void func_01E05220_b433(Obj_b139_01E03820 *obj, Cam_b139_01E03820 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b139_01E03820 buf;
    Uv_b139_01E03820 uv;
    s32 sel;
    s32 mode;
    Pk_b139_01E03820 *p = &buf.pk;

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
    func_01E00110_b433((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}
