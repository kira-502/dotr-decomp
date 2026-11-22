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

static void func_01E00080_b632(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E00920_b632(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b632_01E00080();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

    func_00207500();
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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b632_01E00080(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b203:01E00D70, 362 insns, 6 copies: twin of b016:01E00920 (x[2] = cam->f5A, func_00108950 mode 2). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b203_01E00D70 {
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
} Cam_b203_01E00D70;

typedef struct Obj_b203_01E00D70 {
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
} Obj_b203_01E00D70;

typedef struct Uv_b203_01E00D70 {
    f32 u, v;
} Uv_b203_01E00D70;

typedef struct Xyz_b203_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b203_01E00D70;

typedef struct Pk_b203_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b203_01E00D70 uv;
    u64 pad18;
    Xyz_b203_01E00D70 v[4];
    u64 pad60[6];
} Pk_b203_01E00D70;

typedef struct Buf_b203_01E00D70 {
    u64 tag;
    Pk_b203_01E00D70 pk;
} Buf_b203_01E00D70;

static void func_01E00E70_b632(Obj_b203_01E00D70 *obj, Cam_b203_01E00D70 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b203_01E00D70 *p;
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
    Buf_b203_01E00D70 buf;
    Uv_b203_01E00D70 uv;

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
    func_01E00080_b632((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
    x[2] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b632((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
            func_00108950(out, x, 2, obj->fD8);
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

static void func_01E01420_b632(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

/* OVL_WARM */

/* shape b279:01E00920: quad ring sprite (b065/b193 family). The draw mode is written inline as (mode & 0xF) in each
   test: -O4 hoists it into a fresh register so the counter i can reuse mode's; a kind local coalesces with mode instead. */

typedef struct {
    f32 x, y, z, w;
} Vec_b279_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b279_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b279_01E00920;

typedef struct {
    u64 st;
    Xyz_b279_01E00920 p;
} Vtx_b279_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b279_01E00920 c;
    Vtx_b279_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b279_01E00920;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x28];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col[4];
} Anim_b279_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b279_01E00920;

extern void b632_01E00080(Pkt_b279_01E00920 *, void *, s32);

static void func_01E01780_b632(Obj_b279_01E00920 *o, Anim_b279_01E00920 *an, s32 mode, Vec_b279_01E00920 pos) {
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b279_01E00920 quad[4];
    Vec_b279_01E00920 at;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    struct {
        u64 pre;
        Pkt_b279_01E00920 pk;
    } buf;
    Col_b279_01E00920 col;
    s16 blend;
    f32 w0;
    s16 width;
    s16 i;
    s16 a;
    s16 j;
    Pkt_b279_01E00920 *p;
    f32 w1;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    j = 0;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, 0, an->rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    width = an->width;
    b632_01E00080(p, o->b94, o->hC0);
    for (i = 0; i < o->count; j += an->step, i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + width);
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
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if ((mode & 0xF) == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b632 in the
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

static void func_01E01BD0_b632(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b632((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b632:01E01E90, 230 insns: the effect scene's step: counts the frame (0x5C30); each new orb (age 0) aims at joint
   0x5BF4 jittered by -10..9 and takes a sixtieth of the gap as its speed (y and z; z set twice), then each orb under
   age 60 moves; frames 115, 130, .., 190 add an orb on joint 0x5BE4 and spawn 0x1E02750, 0x1E03770 and three
   0x1E023C0 there; frames 58..158 spawn 0x1E032E0 and, before frame 100, 0x1E03100 and 0x1E02F70 on the joint; frame
   65 spawns 0x1E038F0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x5A50 - 0x260];
    Vec4f pts[10];
    Vec4f vel[10];
    u8 pad5B90[0x5BE4 - 0x5B90];
    s16 ja;
    u8 pad5BE6[0xE];
    s16 jb;
    u8 pad5BF6[0xE];
    s16 age[10];
    u8 pad5C18[0xE];
    s16 k;
    s16 n;
    u8 pad5C2A[6];
    s16 t;
} Scene_b632_01E01E90;

static void func_01E01E90_b632(Scene_b632_01E01E90 *g) {
    extern void b632_01E023C0(void);
    extern void b632_01E02750(void);
    extern void b632_01E02F70(void);
    extern void b632_01E03100(void);
    extern void b632_01E032E0(void);
    extern void b632_01E03770(void);
    extern void b632_01E038F0(void);
    extern s32 b632_01E045B0(Scene_b632_01E01E90 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[8];
    s16 i;

    g->t++;
    for (i = 0; i < g->n; i++) {
        if (g->age[i] == 0) {
            func_001F5620(func_001F5380(), g->jb, v);
            v[0] += func_0019A5C8() % 20 - 10;
            v[1] += func_0019A5C8() % 20 - 10;
            g->vel[i].z = (v[2] - g->pts[i].z) / 60.0f;
            g->vel[i].y = (v[1] - g->pts[i].y) / 60.0f;
            g->vel[i].z = (v[2] - g->pts[i].z) / 60.0f;
            g->age[i]++;
        }
    }
    for (i = 0; i < g->n; i++) {
        if (g->age[i] != 0 && g->age[i] < 60) {
            g->pts[i].z += g->vel[i].z;
            g->pts[i].y += g->vel[i].y;
            g->pts[i].x += g->vel[i].x;
            g->age[i]++;
        }
    }
    if (g->t == 115 || g->t == 130 || g->t == 145 || g->t == 160 || g->t == 175 || g->t == 190) {
        g->k = g->n;
        func_001F5620(func_001F53A0(), g->ja, &g->pts[g->k]);
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        b632_01E045B0(g, (s32)b632_01E02750, 0);
        b632_01E045B0(g, (s32)b632_01E03770, 0);
        b632_01E045B0(g, (s32)b632_01E023C0, 0);
        b632_01E045B0(g, (s32)b632_01E023C0, 0);
        b632_01E045B0(g, (s32)b632_01E023C0, 0);
        g->n++;
    }
    if (g->t >= 58 && g->t < 159) {
        b632_01E045B0(g, (s32)b632_01E032E0, 0);
        if (g->t < 100) {
            func_001F5620(func_001F53A0(), g->ja, &g->pos);
            b632_01E045B0(g, (s32)b632_01E03100, 0);
            b632_01E045B0(g, (s32)b632_01E02F70, 0);
        }
    }
    if (g->t == 65) {
        b632_01E045B0(g, (s32)b632_01E038F0, 0);
    }
}

/* shape b632:01E02230, 100 insns: on start f48 15, variant 0..6, colour 0x80 grey, random 0x5A, 0xA 0..7, 0xC keeps
   the old 0x50, 0x50 5..24, speed 16..45 (0xE), 0x8 0..34, hold 3..7 (0x6); alpha 0x80 during the hold, then fades by
   8 and stops; 0x50 grows by the speed after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
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
    u8 col2[4];
} Fx_b632_01E02230;

static s32 func_01E02230_b632(s32 arg0, Fx_b632_01E02230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 15.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 20 + 5;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b111:01E02160, 100 insns, 7 copies: spark update, a variant of b018:01E02950 (on spawn: random kind, white
   colour, angle, spin, height, speed, size and lifetime; then fade out after the lifetime, move while
   alive). b193:01E02780 is the same code with 40.0f for the first field. */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 pos;
    u8 pad52[2];
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Spark_b111_01E02160;

static s32 func_01E023C0_b632(s32 unused, Spark_b111_01E02160 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 10.0f;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->angle = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->pos;
        o->pos = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->limit = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 9) {
        o->alpha -= 8;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->pos += o->speed;
    }
    o->age++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[0x10];
    s32 seed[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 pos;
    s16 frame;
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Mote_b111_01E022F0;

static s32 func_01E02550_b632(s32 unused, Mote_b111_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 5 + 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->seed[0] = func_0019A5C8() % 0xFFFF;
        o->seed[1] = func_0019A5C8() % 0xFFFF;
        o->seed[2] = func_0019A5C8() % 0xFFFF;
        o->frame = 1;
        o->pos = func_0019A5C8() % 30 + 10;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->limit = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x60;
    } else if (o->alpha > 12) {
        o->alpha -= 11;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b632:01E02750, 225 insns: b426:01E02370 cousin: pale grey (0xCF) with a red second colour flickering to dull
   red on even ticks, f48 40 growing by 10 up to 100; alpha up for 60 ticks; at tick 60 it spawns ten 0x1E02230 and
   four 0x1E02AE0 (ctx+0x5C26 = 0..3) at its point (ctx+0x5A50 table) and bumps ctx+0x5C2A; ticks 60..64 spawn
   0x1E02E00, ticks up to 60 0x1E03450 and 0x1E035F0 there */

typedef struct {
    f32 x, y, z, w;
} V_b632_01E02750;

typedef struct {
    u8 pad0[0x250];
    V_b632_01E02750 pos;
    u8 pad260[0x5A50 - 0x260];
    V_b632_01E02750 pts[1];
    u8 pad5A60[0x5C26 - 0x5A60];
    s16 sel;
    u8 pad5C28[2];
    s16 count;
} Game_b632_01E02750;

typedef struct {
    u8 pad0[0xE];
    s16 fE;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 pt;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b632_01E02750;

static s32 func_01E02750_b632(Game_b632_01E02750 *g, Fx_b632_01E02750 *o) {
    extern s32 b632_01E02230(void);
    extern s32 b632_01E02AE0(void);
    extern s32 b632_01E02E00(void);
    extern s32 b632_01E03450(void);
    extern s32 b632_01E035F0(void);
    extern s32 b632_01E045B0(Game_b632_01E02750 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f48 = 40.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->fE = func_0019A5C8() % 10 + 1;
        o->mode = 2;
        o->col2[3] = 0;
        o->f5A = 15;
        o->f5C = 15;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xFF, 8, 8);
    } else {
        func_001076F0(o->col2, 0xC0, 8, 8);
    }
    if (o->tick < 60) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick == 60) {
        g->pos = g->pts[o->pt];
        for (i = 0; i < 10; i++) {
            b632_01E045B0(g, b632_01E02230, 0);
        }
        g->sel = 0;
        b632_01E045B0(g, b632_01E02AE0, 0);
        g->sel = 1;
        b632_01E045B0(g, b632_01E02AE0, 0);
        g->sel = 2;
        b632_01E045B0(g, b632_01E02AE0, 0);
        g->sel = 3;
        b632_01E045B0(g, b632_01E02AE0, 0);
        g->count++;
    }
    if (o->tick >= 60 && o->tick < 65) {
        g->pos = g->pts[o->pt];
        b632_01E045B0(g, b632_01E02E00, 0);
    }
    if (o->tick < 61) {
        g->pos = g->pts[o->pt];
        b632_01E045B0(g, b632_01E03450, 0);
        b632_01E045B0(g, b632_01E035F0, 0);
    }
    if (o->tick != 0) {
        if (o->f48 < 100.0f) {
            o->f48 += 10.0f;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b632:01E02AE0, 197 insns: a white/pink flash quad in quarter k (0x50): on start size 20, white colour and a
   pink second colour, turn 0..0x1FFF + 0x4000 k and tilt 0..0x4FFF from the quarter the scene's counter (0x5C2A % 4)
   picks; frames 10; alpha up by 0x60 to 0x120 for 5 ticks, then down by 15; the second colour flickers pink/dull on
   odd ticks; it grows 35 a tick with 0x4C trailing it by 80 */

typedef struct {
    u8 pad0[0x5C2A];
    s16 count;
} Ctx_b632_01E02AE0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[2];
    u8 pad28[0x20];
    f32 size;
    f32 f4C;
    s16 k;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b632_01E02AE0;

static s32 func_01E02AE0_b632(Ctx_b632_01E02AE0 *g, Fx_b632_01E02AE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 q;
    s32 base;

    if (o->mode == 1) {
        o->size = 20.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        q = g->count % 4;
        if (q == 0) {
            base = 0;
        } else if (q == 1) {
            base = 0x4000;
        } else if (q == 2) {
            base = 0x8000;
        } else if (q == 3) {
            base = 0xC000;
        }
        if (o->k == 0) {
            o->rot[1] = func_0019A5C8() % 0x2000;
            o->rot[0] = base + func_0019A5C8() % 0x5000;
        }
        if (o->k == 1) {
            o->rot[1] = func_0019A5C8() % 0x2000 + 0x4000;
            o->rot[0] = base + func_0019A5C8() % 0x5000;
        }
        if (o->k == 2) {
            o->rot[1] = func_0019A5C8() % 0x2000 + 0x8000;
            o->rot[0] = base + func_0019A5C8() % 0x5000;
        }
        if (o->k == 3) {
            o->rot[1] = func_0019A5C8() % 0x2000 + 0xC000;
            o->rot[0] = base + func_0019A5C8() % 0x5000;
        }
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->col2, 0xC0, 0x70, 0x70);
    }
    o->f4C = (o->size += 35.0f) - 80.0f;
    o->tick++;
    return 0;
}

/* shape b632:01E02E00, 90 insns: on start f48 200..499, f4C 0, colour 0x80 grey, second colour (0xFF, 0x80, 0x80)
   with alpha 0, 0x5A/0x5C = 15; alpha grows by 0x30 (below 0x60) for 2 ticks, then fades by 11 and stops; the second
   colour flickers red; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
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
} Fx_b632_01E02E00;

static s32 func_01E02E00_b632(s32 arg0, Fx_b632_01E02E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f + func_0019A5C8() % 300;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x40, 0x40);
    } else {
        func_001076F0(o->col2, 0x60, 0x30, 0x30);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b632:01E02F70, 100 insns: on start f48 10..29, colour (0xCF, 0x80, 0x80), second colour (0x80, 8, 8) with
   alpha 0, random rotation, 0x5A = 45, 0x5C = 5; alpha grows by 0x40 (below 0xC0) for 8 ticks, then fades by 9 and
   stops; f48 shrinks by 1 with f4C 6 above it */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
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
    u8 col2[4];
} Fx_b632_01E02F70;

static s32 func_01E02F70_b632(s32 arg0, Fx_b632_01E02F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 10;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f5A = 45;
        o->f5C = 5;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 -= 1.0f;
    o->f4C = 6.0f + o->f48;
    o->tick++;
    return 0;
}

/* shape b632:01E03100 (B632_OBJ_MOVE_10_), 120 insns, 1 copy: a grey (0x80) mote: speed 3.0, kind 4, random start
   angles, life 300..649 shrinking by 10..29 a tick, frame 1..8, bright (0x60) for 2..4 ticks then fades by 11 until
   it stops; each tick it follows the unit the game names at +0x5BE4 */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    u8 padA[4];
    s16 fE;
    u8 f10[0x10];
    s32 pos[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b632_01E03100;

typedef struct {
    u8 pad[0x5BE4];
    s16 unit;
} Game_b632_01E03100;

static s32 func_01E03100_b632(Game_b632_01E03100 *g, Fx_b632_01E03100 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0();
    extern s32 func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 350 + 300;
        o->f5A = func_0019A5C8() % 360;
        o->fE = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->f6 = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->f6) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 -= o->fE;
    o->tick++;
    func_001F5620(func_001F53A0(), g->unit, o->f10);
    return 0;
}

/* shape b632:01E032E0, 90 insns: b529:01E02240 family: a white/red glow of random size 15..64, spun 0x4000 a tick, its second colour blinking red: in by 48 up to 0x60 for 2 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[0x20];
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
} Obj_b632_01E032E0;

static s32 func_01E032E0_b632(s32 arg0, Obj_b632_01E032E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 15.0f + func_0019A5C8() % 50;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x40, 0x40);
    } else {
        func_001076F0(o->col2, 0x60, 0x30, 0x30);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b632:01E03450, 103 insns: on start 0x8/0xA = 150, variant 0..7, f34 0, both colours (0xFF, 0x80, 0x80)
   (second alpha 0), random 0x5A, 0x5C -90..89; both alphas grow by 0x40 (below 0xC0) for 3 ticks, then the first
   fades by 14 twice a tick and ends it; after the first tick 0x8/0xA shrink by 15 down to 0x14; func_00205C40 on the
   rotation */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b632_01E03450;

static s32 func_01E03450_b632(s32 arg0, Fx_b632_01E03450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 150;
        o->fA = 150;
        o->f56 = func_0019A5C8() % 8;
        o->f34 = 0.0f;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 180 - 90;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->tick != 0) {
        if (o->f8 > 0x14) {
            o->f8 -= 15;
        }
        if (o->fA > 0x14) {
            o->fA -= 15;
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b632:01E035F0, 96 insns: constant variant of b390:01E030F0 (f5A steps by 5) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 rot[4];
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
} Fx_b632_01E035F0;

static s32 func_01E035F0_b632(s32 arg0, Fx_b632_01E035F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 80 + 10;
        o->spin = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f5A += 5;
    o->tick++;
    return 0;
}

/* shape b632:01E03770, 94 insns: b426:01E01E50 twin: white, held 60 ticks */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
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
} Obj_b632_01E03770;

static s32 func_01E03770_b632(s32 arg0, Obj_b632_01E03770 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 25;
        o->hA = 25;
        o->kind = func_0019A5C8() % 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 60) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->kind != 0) {
        o->kind = 0;
    } else {
        o->kind = 1;
    }
    if (o->t != 0) {
        if (o->h8 < 75) {
            o->h8 += 10;
        }
        if (o->hA < 75) {
            o->hA += 10;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b632:01E038F0, 177 insns: b491:01E03360's window in red (0x80/0x10/0x10 blinking with 0x60) at ctx+0x5BC8 /
   point 0x5BE4, drawn once from alpha 0; alpha up by 12 to 0x80 for 150 ticks, then down by 15 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b632_01E038F0;

typedef struct {
    f32 s, t;
    Xyz_b632_01E038F0 p;
} Tv_b632_01E038F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b632_01E038F0 v[2];
} Tex_b632_01E038F0;

typedef struct {
    u8 pad[0x5BC8];
    Tex_b632_01E038F0 *pk;
    u8 pad5BCC[0x5BE4 - 0x5BCC];
    s16 id;
} Game_b632_01E038F0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b632_01E038F0;

static s32 func_01E038F0_b632(Game_b632_01E038F0 *g, Fx_b632_01E038F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;
    f32 v[4];

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->id, v);
    func_001F5F90(func_001F53A0(), v);
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
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0x10);
    } else {
        func_001076F0(o->col, 0x60, 0x10, 0x10);
    }
    if (o->tick < 150) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b632:01E03BC0 (b632), 636 insns, 1 copy: b632 scene manager in b252:01E03F80 form: setup (camera and six
   joints, textures (4,15) and (5,0..2), a 256 s8 jitter with 180..255 set to rand % 8 - 4, a second 256 s8 jitter),
   step b632:01E01E90 and every slot (200 of 0x70) but b632:01E038F0 (counted; any draws them through b632:01E046F0),
   draw jitter quads, rings, sprites and trails; scene code from the frame */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    u8 pad52[0x4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b632_01E03BC0;

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
        s16 uv[8];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b632_01E03BC0 fx[200];
    u8 pad5A20[0x30];
    Vec4f tbl[20];
    s32 tex2[3];
    u8 pad5B9C[0x14];
    s32 count;
    u8 pad5BB4[8];
    s32 ot;
    u8 pad5BC0[0x24];
    s16 j[6];
    u8 pad5BF0[4];
    s16 cam;
    u8 pad5BF6[0x36];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad5E32[2];
    u8 crd[0x16C];
} Scene_b632_01E03BC0;

static s32 func_01E03BC0_b632(s32 arg0, s32 id) {
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
    extern s32 func_0019A5C8(void);
    extern void func_01E01E90_b632();
    extern void func_01E00920_b632();
    extern void func_01E00E70_b632();
    extern void func_01E01420_b632();
    extern void func_01E01780_b632();
    extern void func_01E01BD0_b632();
    extern void b632_01E046F0();
    extern s32 func_01E038F0_b632();
    extern s32 func_01E02230_b632();
    extern s32 func_01E023C0_b632();
    extern s32 func_01E02550_b632();
    extern s32 func_01E02750_b632();
    extern s32 func_01E02AE0_b632();
    extern s32 func_01E02E00_b632();
    extern s32 func_01E02F70_b632();
    extern s32 func_01E03100_b632();
    extern s32 func_01E032E0_b632();
    extern s32 func_01E03450_b632();
    extern s32 func_01E035F0_b632();
    extern s32 func_01E03770_b632();
    Scene_b632_01E03BC0 *g = (Scene_b632_01E03BC0 *)arg0;
    s16 a;
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
    s32 i;
    s16 k;

    a = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x5FA0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 290;
        g->j[0] = func_001F5560(func_001F53A0(), 3, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x35, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s32)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 180; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 8 - 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01E90_b632(g, 0);
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E038F0_b632) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    a++;
                }
            }
        }
    }
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E02230_b632) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hB8 = 10;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00920_b632(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023C0_b632) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[0];
                g->hB8 = 10;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00920_b632(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02550_b632) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E00E70_b632(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02750_b632) {
                v = g->tbl[g->fx[k].h50];
                g->hB8 = 0x18;
                func_01E01420_b632(g, &g->fx[k], 0x21, &v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02AE0_b632) {
                g->hB8 = 0x24;
                v = g->fx[k].pos;
                func_01E01420_b632(g, &g->fx[k], 0x21, &v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02E00_b632) {
                v = g->fx[k].pos;
                g->hB8 = 0x18;
                func_01E01420_b632(g, &g->fx[k], 0x21, &v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F70_b632) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 9;
                func_01E01780_b632(g, &g->fx[k], 0x20, v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03100_b632) {
                g->tex88 = g->tex2[0];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->hB8 = 5;
                g->hB0 = 1;
                func_01E00E70_b632(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E032E0_b632) {
                g->hB8 = 0x18;
                func_001F5620(func_001F53A0(), g->j[0], &v);
                func_01E01420_b632(g, &g->fx[k], 0x21, &v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03450_b632) {
                g->tex88 = g->tex2[1];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01BD0_b632(g, &g->fx[k], 0x11, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E035F0_b632) {
                func_00106080(rm7, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                g->tex88 = g->tex2[0];
                g->hB8 = 10;
                g->hB8 = 6;
                g->hB0 = 0;
                func_01E00E70_b632(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03770_b632) {
                g->tex88 = g->tex2[2];
                func_00106080(rm8, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm8;
                g->u94.uv[0] = g->fx[k].h56 << 6;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x3F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 5;
                v = g->tbl[g->fx[k].h50];
                func_01E01BD0_b632(g, &g->fx[k], 0x21, v);
            }
        }
    }
    if (a) {
        b632_01E046F0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 161) {
        return 1;
    }
    if (g->frame == 278) {
        return 4;
    }
    if (g->frame == 268) {
        return 2;
    }
    if (g->frame > 171 && g->frame < 263) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b632:01E045B0, 80 insns: twin of b034:01E05330: take a free effect slot (0xC8 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b632_01E045B0 {
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
} Slot_b632_01E045B0;

typedef struct Obj_b632_01E045B0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b632_01E045B0 slots[0xC8];
    u8 padB[0x194];
    u8 rgba[4];
    u8 padC[0x6E];
    s16 fB2B0;
} Obj_b632_01E045B0;

static s32 func_01E045B0_b632(Obj_b632_01E045B0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b632_01E045B0 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xC8;
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

/* shape b632:01E046F0, 68 insns: b183:01E029E0 family draw pass: sprite packet on the stack, then every live slot (200 of 0x70 bytes) whose handler is shape b632:01E038F0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b632_01E046F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b632_01E046F0 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b632_01E046F0;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b632_01E046F0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b632_01E046F0 slot[200];
    u8 padEnd[0x5bc4 - 0x2A0 - 200 * 0x70];
    s32 ctx;
    Pkt_b632_01E046F0 *pkt;
} Scene_b632_01E046F0;

static void func_01E046F0_b632(Scene_b632_01E046F0 *s) {
    extern void b632_01E038F0(Scene_b632_01E046F0 *, Slot_b632_01E046F0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b632_01E046F0 pkt __attribute__((aligned(8)));
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
    for (i = 0; i < 200; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b632_01E038F0) {
            b632_01E038F0(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
