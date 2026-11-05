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

static void func_01E00080_b485(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b485(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E00C80_b485(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b485((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b485((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b485 in the
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

static void func_01E01230_b485(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b485((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b016:01E018F0, 177 insns: b016:01E00ED0 with the view matrix's [2][1] and [3][1] cleared; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b485 in the
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

static void func_01E014F0_b485(Obj_b016_01E018F0 *obj, Cam_b016_01E018F0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b485((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b485:01E017C0, 165 insns: the effect scene's step: counts the frame (0x44FA); on frame 252 it spawns two
   0x1E01A60, a 0x1E02690 and two 0x1E02290, on frame 1 a 0x1E02A00 and a 0x1E025B0; on odd frames 245..270 two
   0x1E01BC0 at joint 0x44C6; from frame 69 to 226 a 0x1E023F0 two below joint 0x44C4; on frame 250 twenty pairs
   of 0x1E01BC0 and 0x1E02040 at joint 0x44C6 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4264];
    s16 j0;
    s16 j1;
    u8 pad44C8[0x32];
    s16 t;
} Scene_b485_01E017C0;

static void func_01E017C0_b485(Scene_b485_01E017C0 *g) {
    extern void b485_01E01A60(void);
    extern void b485_01E01BC0(void);
    extern void b485_01E02040(void);
    extern void b485_01E02290(void);
    extern void b485_01E023F0(void);
    extern void b485_01E025B0(void);
    extern void b485_01E02690(void);
    extern void b485_01E02A00(void);
    extern s32 b485_01E03370(Scene_b485_01E017C0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t == 252) {
        b485_01E03370(g, (s32)b485_01E01A60, 0);
    }
    if (g->t == 252) {
        b485_01E03370(g, (s32)b485_01E01A60, 0);
    }
    if (g->t == 252) {
        b485_01E03370(g, (s32)b485_01E02690, 0);
    }
    if (g->t == 252) {
        b485_01E03370(g, (s32)b485_01E02290, 0);
    }
    if (g->t == 252) {
        b485_01E03370(g, (s32)b485_01E02290, 0);
    }
    if (g->t == 1) {
        b485_01E03370(g, (s32)b485_01E02A00, 0);
    }
    if (g->t == 1) {
        b485_01E03370(g, (s32)b485_01E025B0, 0);
    }
    if (g->t >= 245 && g->t < 271) {
        if (g->t % 2 == 1) {
            for (i = 0; i < 2; i++) {
                func_001F5620(func_001F53A0(), g->j1, &g->pos);
                b485_01E03370(g, (s32)b485_01E01BC0, 0);
            }
        }
    }
    if (g->t >= 69 && g->t < 227) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y -= 2.0f;
        b485_01E03370(g, (s32)b485_01E023F0, 0);
    }
    if (g->t == 250) {
        for (i = 0; i < 20; i++) {
            func_001F5620(func_001F53A0(), g->j1, &g->pos);
            b485_01E03370(g, (s32)b485_01E01BC0, 0);
            b485_01E03370(g, (s32)b485_01E02040, 0);
        }
    }
}

/* shape b485:01E01A60, 87 insns: a grey-blue flickering flash on the model joint: f4C 165, size 10x10; second alpha up by 24 to 0xC0 until the game
   timer reaches 0x122, then down by 12 until it ends; second colour flickers by the timer's parity; random turn */

typedef struct {
    u8 pad0[0x44C4];
    s16 joint;
    u8 pad44C6[0x34];
    s16 timer;
} Game_b485_01E01A60;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b485_01E01A60;

static s32 func_01E01A60_b485(Game_b485_01E01A60 *g, Obj_b485_01E01A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
        o->hold = 0x8C;
        o->f4C = 165.0f;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x122) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x18;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (g->timer % 2 == 1) {
        func_001076F0(o->c1, 0x50, 0x50, 0x80);
    } else {
        func_001076F0(o->c1, 0x60, 0x60, 0xA0);
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b485:01E01BC0, 287 insns: B485_OBJ_MOVE_4_: a smoke puff: set up once (radius 5..24, kind 0..3, x/z jitter
   +-8, spin -8..7, rise -0.25..0.24, grey, angles random) aimed from its point on the ring around the model to it over
   30 ticks; fades in by 0x15 to 0x80 until its life (70..109) runs out, then out by 9; grows 0.3 a tick for 20 ticks,
   drifts for 10 more, then circles the ring by its spin; frame +1 every other tick */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 frame;
    s16 frame4;
    u8 pad0C[2];
    s16 spin;
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0xC];
    f32 vx;
    f32 vy;
    u8 pad38[4];
    f32 vz;
    u8 pad40[8];
    f32 scale;
    f32 r;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 a;
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Obj_b485_01E01BC0;

typedef struct {
    u8 pad00[0x44C4];
    s16 joint;
    u8 pad44C6[0x46FC - 0x44C6];
    u8 trig[1];
} Game_b485_01E01BC0;

static s32 func_01E01BC0_b485(Game_b485_01E01BC0 *g, Obj_b485_01E01BC0 *o) {
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    f32 p[4];
    f32 q[4];
    f32 d;

    if (o->mode == 1) {
        o->frame = 0;
        o->frame4 = o->frame * 4;
        o->scale = 0.0f;
        o->r = 5.0f + (func_0019A5C8() >> 4) % 20;
        o->kind = (func_0019A5C8() >> 4) % 4;
        d = func_0019A5C8() % 160 - 80;
        d /= 10.0f;
        o->x += d;
        d = func_0019A5C8() % 160 - 80;
        d /= 10.0f;
        o->z += d;
        o->spin = func_0019A5C8() % 16 - 8;
        o->vy = (func_0019A5C8() >> 4) % 40 - 20;
        o->vy = o->vy / 80.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->a = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        func_001F5F90(func_001F5380(), p);
        p[0] += o->r * func_00108030(g->trig, o->ang, 1);
        p[2] += o->r * func_00108030(g->trig, o->ang, 0);
        func_001F5620(func_001F53A0(), g->joint, q);
        o->vz = (p[2] - o->z) / 30.0f;
        o->vx = (p[0] - o->x) / 30.0f;
        o->life = (func_0019A5C8() >> 4) % 40 + 70;
    }
    if (o->t < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t < 20) {
        o->y += o->vy;
        o->frame++;
        o->frame4 = o->frame * 4;
        o->scale += 0.3f;
        o->z += o->vz;
        o->x += o->vx;
    } else if (o->t < 30) {
        o->z += o->vz;
        o->x += o->vx;
    } else {
        func_001F5F90(func_001F5380(), p);
        p[0] += o->r * func_00108030(g->trig, o->ang, 1);
        p[2] += o->r * func_00108030(g->trig, o->ang, 0);
        o->x = p[0];
        o->z = p[2];
        o->ang += o->spin;
        if (o->t % 2 == 1) {
            o->frame++;
            o->frame4 = o->frame * 4;
        }
    }
    func_00205C40((s32)&o->rot);
    o->t++;
    o->a += 2;
    return 0;
}

/* shape b191:01E02600, 148 insns: a blue spark at a random position: f48 10..19 (+1 per tick), variant 0..3, f50
   10..29, random f5A, spin 10..21, f8 1..8, life 2..4; alpha 0x80 during the life, then fades by 11 and stops;
   the colour flickers between (0x20,0x20,0x80) and (0x30,0x30,0xA0); f50 grows by the spin each tick */

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
} Fx_b191_01E02600;

static s32 func_01E02040_b485(s32 arg0, Fx_b191_01E02600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 20 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 12 + 10;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->col, 0x30, 0x30, 0xA0);
    }
    o->f50 += o->spin;
    o->f48 += 1.0f;
    o->tick++;
    return 0;
}

/* shape b485:01E02290, 87 insns: a dark-blue flickering flash on the model joint (b485:01E01A60 shape): second alpha up by 0x60 until the game
   timer reaches 10 */

typedef struct {
    u8 pad0[0x44C4];
    s16 joint;
    u8 pad44C6[0x34];
    s16 timer;
} Game_b485_01E02290;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b485_01E02290;

static s32 func_01E02290_b485(Game_b485_01E02290 *g, Obj_b485_01E02290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
        o->hold = 0x8C;
        o->f4C = 165.0f;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0xA) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (g->timer % 2 == 1) {
        func_001076F0(o->c1, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->c1, 0x30, 0x30, 0xA0);
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b485:01E023F0, 109 insns: a blue spark (20 x 90, frames 2..4 then cycling 0..7, random heading) rising a random 0.2..0.99 a tick, held 5..9 ticks: in by 16 up to 0x80, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[8];
    f32 f14;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b485_01E023F0;

static s32 func_01E023F0_b485(s32 arg0, Obj_b485_01E023F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->h8 = 20;
        o->hA = func_001A22C0(4.5f * o->h8);
        o->kind = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0x30, 0x30, 0x80);
        o->mode = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->h6 = (func_0019A5C8() >> 4) % 5 + 5;
        o->f34 = func_0019A5C8() % 80 + 20;
        o->f34 = o->f34 / 100.0f;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f14 += o->f34;
    }
    o->kind++;
    if (o->kind > 7) {
        o->kind = 0;
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b485:01E025B0, 54 insns: volume fade: starts at 0x80; while the game counter at 0x4490 is over 0x1E it drops by
   10 to 0x20, otherwise it rises by 10 (clamped) and stops at 0x80; func_001F6D00 gets 0x80 when the counter is 2,
   else the volume */

typedef struct {
    u8 pad0[0x4490];
    s32 count;
} Game_b485_01E025B0;

typedef struct {
    u8 pad0[0x50];
    s16 v;
    u8 pad52[0x6];
    s16 mode;
} Fx_b485_01E025B0;

static s32 func_01E025B0_b485(Game_b485_01E025B0 *g, Fx_b485_01E025B0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x20) {
            o->v -= 10;
        } else {
            o->v = 0x20;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
            o->mode = 0;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b485:01E02690, 218 insns: b707:01E02D80's blue-grey (0x80/0x80/0xB0) screen veil with a second (horizontal)
   bias 0x4C added to the s offsets; while the scene time (g+0x44FA) is 161..284 the bias swings 10 x cos(0x5A) (0x5A
   turning 10 a tick), at 285 0x5A restarts at 0, from 286 to 459 the second bias swings 10 x cos(0x5C) (turning 20);
   at time 270 the tint turns 0x90/0x70/0x80; while g+0x4490 is over 30 the alpha rises by 10 to 0x50 before time 270
   and falls by 7 to 56 after 310, otherwise it fades by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b485_01E02690;

typedef struct {
    f32 s, t;
    Xyz_b485_01E02690 p;
} Tv_b485_01E02690;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b485_01E02690 v[2];
    u8 tail[0x20];
} Tex_b485_01E02690;

typedef struct {
    u8 pad0[0x4490];
    s32 level;
    u8 pad4494[0x44FA - 0x4494];
    s16 time;
    u8 pad44FC[0x46FC - 0x44FC];
    u8 trig[1];
} Ctx_b485_01E02690;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    s16 ang2;
    u8 pad5E[2];
    u8 col[4];
} Fx_b485_01E02690;

static s32 func_01E02690_b485(Ctx_b485_01E02690 *g, Fx_b485_01E02690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    Tex_b485_01E02690 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xB0);
        o->mode = 2;
    }
    z = 10.0f;
    ((Tex_b485_01E02690 *)(s32)&pk)->flags = 0x26;
    ((Tex_b485_01E02690 *)(s32)&pk)->size = 5;
    ((Tex_b485_01E02690 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b485_01E02690 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].s = (o->f4C + (o->f48 + z)) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (o->f4C + (640.0f + o->f48 - z)) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->time > 160 && g->time < 285) {
        o->f48 = 10.0f * func_00108030(g->trig, o->ang, 0);
        o->ang += 10;
    }
    if (g->time == 285) {
        o->ang = 0;
        o->f48 = 10.0f * func_00108030(g->trig, o->ang, 0);
    }
    if (g->time > 285 && g->time < 460) {
        o->f4C = 10.0f * func_00108030(g->trig, o->ang2, 0);
        o->ang2 += 20;
    }
    if (g->time == 270) {
        func_001076F0(o->col, 0x90, 0x70, 0x80);
    }
    if (g->level > 30) {
        if (g->time < 270) {
            if (o->col[3] < 0x50) {
                o->col[3] += 10;
            }
        }
        if (g->time > 310) {
            if (o->col[3] > 56) {
                o->col[3] -= 7;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b485:01E02A00, 142 insns: b205:01E02120's veil in the scene's packet (0x44A8), grey 0x60, brightening until scene count 300 (0x44FA), then fading by 7 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b485_01E02A00;

typedef struct {
    f32 s, t;
    Xyz_b485_01E02A00 p;
} Tv_b485_01E02A00;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b485_01E02A00 v[2];
} Tex_b485_01E02A00;

typedef struct {
    u8 pad[0x44A8];
    Tex_b485_01E02A00 *pk;
    u8 pad44AC[0x4E];
    s16 v;
} Game_b485_01E02A00;

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
} Fx_b485_01E02A00;

static s32 func_01E02A00_b485(Game_b485_01E02A00 *g, Fx_b485_01E02A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
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
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (g->v < 300) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b485:01E02C40 (b485), 458 insns, 1 copy: the scene manager: set up the scene and five jitter runs, then step
   the 150 effect slots (counting the 0x1E02A00 ones for a later pass) and draw five kinds; returns cue codes by frame
   */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b485_01E02C40;

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
    union {
        s32 rm[4];
        struct {
            s16 x, y, w, h;
        } r;
    } u;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b485_01E02C40 fx[150];
    u8 pad4440[0x30];
    s32 tex[3];
    u8 pad447C[0x14];
    s32 count;
    u8 pad4494[8];
    s32 ot;
    u8 pad44A0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    u8 pad44CE[6];
    s16 cam;
    u8 pad44D6[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b485_01E02C40;

static s32 func_01E02C40_b485(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_001F57B0(s32);
    extern void func_01E017C0_b485();
    extern void func_01E00920_b485();
    extern void func_01E00C80_b485();
    extern void func_01E01230_b485();
    extern void func_01E014F0_b485();
    extern void b485_01E034B0();
    Scene_b485_01E02C40 *g = (Scene_b485_01E02C40 *)arg0;
    s32 k;
    s32 c;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s16 i;

    c = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4870);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 400;
        g->jA = func_001F5560(func_001F53A0(), 0x21, 1);
        g->jB = func_001F5560(func_001F53A0(), 1, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x56, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x60, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 15; k < 16; k++) {
            g->tex260[k] = func_00202BF0(4, k);
        }
        for (k = 0; k < 3; k++) {
            g->tex[k] = func_00202BF0(5, k);
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
        for (i = 180; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 20;
        }
        return 0;
    }
    func_001F57B0(1);
    func_01E017C0_b485(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != func_01E02A00_b485) {
                    g->fx[i].fn(g, &g->fx[i]);
                } else {
                    c = (s16)(c + 1);
                }
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01A60_b485) {
                g->hB8 = 0x24;
                func_01E00920_b485(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01BC0_b485) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->u.r.x = g->fx[i].h56 << 5;
                g->u.r.y = 0;
                g->u.r.w = 0x20;
                g->u.r.h = 0x80;
                g->hBE = 0;
                v.x = g->fx[i].pos.x + 2.0f * (g->fx[i].f48 * func_00108030(g->crd, g->fx[i].h5A + 180, 0));
                v.y = g->fx[i].pos.y + g->fx[i].f48 * func_00108030(g->crd, g->fx[i].h5A, 0);
                v.z = g->fx[i].pos.z;
                func_01E01230_b485(g, &g->fx[i], 0x20, v);
            }
            if (g->fx[i].fn == func_01E02040_b485) {
                g->tex88 = g->tex260[15];
                func_00106080(rm2, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00C80_b485(g, &g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[i].fn == func_01E02290_b485) {
                g->hB8 = 0x24;
                func_01E00920_b485(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E023F0_b485) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->u.r.x = g->fx[i].h56 << 5;
                g->u.r.y = 1;
                g->u.r.w = 0x20;
                g->u.r.h = 0x40;
                func_01E014F0_b485(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
        }
    }
    if (c != 0) {
        b485_01E034B0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 252) {
        return 1;
    }
    if (g->frame == 385) {
        return 4;
    }
    if (g->frame == 375) {
        return 2;
    }
    if (g->frame > 262 && g->frame < 370) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b485:01E03370, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b485_01E03370 {
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
} Slot_b485_01E03370;

typedef struct Obj_b485_01E03370 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b485_01E03370 slots[0x96];
    u8 padB[0x54];
    u8 rgba[4];
    u8 padC[0x5A];
    s16 fB2B0;
} Obj_b485_01E03370;

static s32 func_01E03370_b485(Obj_b485_01E03370 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b485_01E03370 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
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

/* shape b485:01E034B0, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x44A8, ot at
   0x44A4), texture from func_001F53A0, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b485:01E02A00 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b485_01E034B0;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b485_01E034B0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b485_01E034B0 slots[0x96];
    u8 pad4440[0x64];
    s32 ot;
    Pkt_b485_01E034B0 *pk;
} Scene_b485_01E034B0;

static void func_01E034B0_b485(Scene_b485_01E034B0 *g) {
    extern void b485_01E02A00(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b485_01E034B0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b485_01E02A00) {
                b485_01E02A00(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
