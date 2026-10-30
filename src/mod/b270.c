#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b270(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b270(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b270(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E00D10_b270(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b270_01E00110();
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
    b270_01E00110(p, obj->f94, obj->fC0);
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

static void func_01E01260_b270(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b270((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b270((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E01810_b270(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b270 in the
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

static void func_01E01960_b270(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b270((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E01C20_b270(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b270", func_01E02020_b270);

/* shape b270:01E02940, 258 insns: b529:01E01E90's grow-in effect with three start stages (by f50: 0, 2, 4), the six
   stages growing by 2.5 to 40/30/30/20/20/10, colours 0xFF on odd ticks else 0x80, fade-out after scene tick 460,
   and from tick 400 a 0x300 turn per step (-0x300 for the middle third) */

/* shape b529:01E01E90, 236 insns: a two-colour grey glow (0x80 / 0x70 flicker) whose stage (0x52: from 0x50, 0 below
   36, 2 below 72) grows 0x48 by 0.5 to 10 (stage 0) or 6 (stage 2), then 0x4C to 7 / 4; fades in by 8 for 30 ticks,
   out by 11 past scene time 300; before scene time 176 it spins randomly with x locked at 0x4000, after that its
   z angle turns by 256 + 0x30 (sign by 0x50), and 0x30 grows by 32 to 512 from scene time 241 */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 rot[3];
    u8 pad2C[4];
    f32 f30;
    u8 pad34[0x14];
    f32 f48;
    f32 f4C;
    s16 f50;
    s16 stage;
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col0[4];
    u8 col1[4];
} Fx_b270_01E02940;

typedef struct {
    u8 pad0[0xDA94];
    s16 timer;
} Scn_b270_01E02940;

static s32 func_01E02940_b270(Scn_b270_01E02940 *g, Fx_b270_01E02940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 0.0f;
        o->f56 = 0;
        o->mode = 2;
        if (o->f50 < 36) {
            o->stage = 0;
        } else if (o->f50 < 72) {
            o->stage = 2;
        } else if (o->f50 < 108) {
            o->stage = 4;
        }
        o->h8 = func_0019A5C8() % 3 + 4;
    }
    if (o->tick < 30) {
        if (o->col0[3] < 0x80) {
            o->col0[3] += 8;
        }
        if (o->col1[3] < 0x80) {
            o->col1[3] += 8;
        }
    } else if (g->timer > 460) {
        if (o->col0[3] > 12) {
            o->col0[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col1[3] > 12) {
            o->col1[3] -= 11;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col1, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0x80, 0x80, 0x80);
    }
    if (g->timer != 0) {
        k = o->stage;
        if (k == 0) {
            if (o->f48 < 40.0f) {
                o->f48 += 2.5f;
            } else {
                o->stage = k + 1;
            }
        } else if (k == 1) {
            if (o->f4C < 30.0f) {
                o->f4C += 2.5f;
            }
        } else if (k == 2) {
            if (o->f48 < 30.0f) {
                o->f48 += 2.5f;
            } else {
                o->stage = k + 1;
            }
        } else if (k == 3) {
            if (o->f4C < 20.0f) {
                o->f4C += 2.5f;
            }
        } else if (k == 4) {
            if (o->f48 < 20.0f) {
                o->f48 += 2.5f;
            } else {
                o->stage = k + 1;
            }
        } else if (k == 5) {
            if (o->f4C < 10.0f) {
                o->f4C += 2.5f;
            }
        }
    }
    if (g->timer > 400) {
        if (o->f50 < 36) {
            o->rot[1] += 0x300;
        } else if (o->f50 < 72) {
            o->rot[1] -= 0x300;
        } else if (o->f50 < 108) {
            o->rot[1] += 0x300;
        }
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

static s32 func_01E02D50_b270(s32 unused, Spark_b111_01E02160 *o) {
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

/* shape b270:01E02EE0, 179 insns: b771:01E02460's mote as a spark, kind 0 (white) or 1 (orange 0xFF/0x80/0x10): on start
   it picks a size 5..14, frame 4, random turns, a radius 10..39 (or 15..64), a start angle, a growth 40..99, h8 0..19
   and a 4..6-tick hold at alpha 0xC0, then fades by 15; kind 0 flickers white/grey, its radius grows and its size grows
   by 1 a tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 grow;
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 r;
    s16 kind;
    s16 tick;
    s16 frame;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Mote_b270_01E02EE0;

static s32 func_01E02EE0_b270(s32 arg0, Mote_b270_01E02EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 10 + 5;
        o->frame = 4;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xFF, 0x80, 0x10);
        }
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        if (o->kind == 0) {
            o->r = func_0019A5C8() % 30 + 10;
        }
        if (o->kind == 1) {
            o->r = func_0019A5C8() % 50 + 15;
        }
        o->ang = func_0019A5C8() % 360;
        o->grow = func_0019A5C8() % 60 + 40;
        o->h8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 3 + 4;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        } else {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        }
        o->r += o->grow;
        if (o->tick != 0) {
            o->size += 1.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b270:01E031B0, 138 insns: b084:01E01A20 family: a white flicker (size 5..34, frames 0..3 then dies at 8, random spin), alternates 0xFF/0xC0 grey every tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[0x16];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b270_01E031B0;

static s32 func_01E031B0_b270(void *arg0, Spark_b270_01E031B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 5;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = func_0019A5C8() % 400 + 20;
        o->h5A = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 3 + 4;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    o->frame++;
    if (o->frame > 7) {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    o->t++;
    return 0;
}

/* shape b270:01E033E0, 102 insns: on start f48 1, variant 4, colour white, random rotation, 0x50 5..84, random 0x5A,
   speed 40..99 (0xE), 0x8 0..19, hold 1..2 (0x6); alpha 0x80 during the hold, then fades by 15 and stops */

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
} Fx_b270_01E033E0;

static s32 func_01E033E0_b270(s32 arg0, Fx_b270_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 80 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 60 + 40;
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b270:01E03580, 125 insns: a growing yellow-white ring: on start size 20 and height 80 (kind 0) or 100 (kind 1),
   f34 = 2, fade-in 3 ticks, random spins; alpha up by 42 to 0x80 during the fade-in, then down by 13 until it ends; each tick
   the size grows by 6 and the height by 10 (kind 0) or 80 (kind 1) */

typedef struct {
    u8 pad0[6];
    s16 fadein;
    u8 pad8[0x18];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 size;
    f32 height;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b270_01E03580;

static s32 func_01E03580_b270(void *g, Obj_b270_01E03580 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->size = 20.0f;
            o->height = 80.0f;
            o->f34 = 2.0f;
            o->fadein = 3;
        }
        if (o->kind == 1) {
            o->size = 20.0f;
            o->height = 100.0f;
            o->f34 = 2.0f;
            o->fadein = 3;
        }
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x40);
        o->w = 0xF;
        o->h = 2;
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->fadein) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else if (o->c1[3] > 0xE) {
        o->c1[3] -= 0xD;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->size += 6.0f;
        o->height += 10.0f;
    }
    if (o->kind == 1) {
        o->size += 6.0f;
        o->height += 80.0f;
    }
    o->t++;
    return 0;
}

/* shape b270:01E03780, 95 insns: a pale-yellow growing ring: size 200 growing by 10, random angle and tilt -90..89; both alphas up
   by 29 under 0x58 for 3 frames, then down by 14 until it ends; sub-frame 5 then 4; turns */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    s32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 tilt;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b270_01E03780;

static s32 func_01E03780_b270(void *arg0, Obj_b270_01E03780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0xC8;
        o->h = 0xC8;
        o->sub = 0;
        o->f34 = 0;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xC0);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xC0);
        o->state = 2;
        o->c1[3] = 0;
        o->ang = func_0019A5C8() % 360;
        o->tilt = func_0019A5C8() % 180 - 0x5A;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x58) {
            o->c0[3] += 0x1D;
        }
        if (o->c1[3] < 0x58) {
            o->c1[3] += 0x1D;
        }
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        }
    }
    if (o->sub != 0) {
        o->sub = 4;
    } else {
        o->sub = 5;
    }
    o->w += 0xA;
    o->h += 0xA;
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b270:01E03900 (B270_OBJ_MOVE_10_), 387 insns, 1 copy: b445:01E03680's jittery spark trail on a world
   track, bigger (size 30..179, speed 3..87), brighter (0x80 blink) and drifting by a tenth of its kick; the module's
   b270:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b270_01E03900;

typedef struct {
    u8 pad0[0x7030];
    Track_b270_01E03900 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0x86];
    u8 pad_DC90[8];
    u8 trig[1];
} World_b270_01E03900;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b270_01E03900;

static s32 func_01E03900_b270(World_b270_01E03900 *w, Spark_b270_01E03900 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 150 + 30;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 85 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        func_01E00080_b270(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b270:01E03F10, 161 insns: a glow in three kinds: 0 spins and widens 6 to 150 while growing 40 from 300; 1 lies flat, rerolls its turn and grows 40 from 150; 2 grows 100 from 20 with its width 70 behind; red/white for 0-1, gold/grey for 2; outer alpha up by 0x60 to 0xC0 for 12 (kind 2: 4) ticks, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b270_01E03F10;

static s32 func_01E03F10_b270(s32 arg0, Fx_b270_01E03F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 0.0f;
            o->f4C = 300.0f;
            o->f34 = 2.0f;
            o->hold = 12;
        } else if (o->kind == 1) {
            o->f48 = 0.0f;
            o->f4C = 150.0f;
            o->f34 = 2.0f;
            o->hold = 12;
        } else if (o->kind == 2) {
            o->f48 = 0.0f;
            o->f4C = 20.0f;
            o->f34 = 2.0f;
            o->hold = 4;
        }
        if (o->kind == 0 || o->kind == 1) {
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
        }
        if (o->kind == 2) {
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
            func_001076F0(o->col, 0x80, 0x80, 0x40);
        }
        o->w = 15;
        o->h = 15;
        o->rot[1] = func_0019A5C8() % 65535;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->rot[1] += 0x200;
        if (o->f48 < 150.0f) {
            o->f48 += 6.0f;
        }
        o->f4C += 40.0f;
    } else if (o->kind == 1) {
        func_00205C40(o->rot);
        o->rot[0] = 0x4000;
        o->f4C += 40.0f;
    } else if (o->kind == 2) {
        o->f4C += 100.0f;
        o->f48 = o->f4C - 70.0f;
    }
    o->tick++;
    return 0;
}

/* shape b270:01E041A0, 102 insns: on start f48 120, f4C 58 below it, colour (0xFF, 0xFF, 0x80), second colour black
   (alpha 0), variant 2, 0x5A = 30, 0x5C = 1, rise speed 2..4.9 (f34), random rotation; alpha 0x80 for 6 ticks, then
   fades by 5 and stops; f48 rises by the speed with f4C = 0.05 x f48 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[8];
    f32 speed;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b270_01E041A0;

static s32 func_01E041A0_b270(s32 arg0, Fx_b270_01E041A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 120.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        func_001076F0(o->col2, 0, 0, 0);
        o->f56 = 2;
        o->f5A = 30;
        o->f5C = 1;
        o->speed = func_0019A5C8() % 30 + 20;
        o->speed /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < 6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->f48 += o->speed;
    o->f4C = 0.05f * o->f48;
    o->tick++;
    return 0;
}

/* shape b270:01E04340, 47 insns, 1 copy: fade a level toward 0x40 or 0x80 by the scene timer */

typedef struct Ctx_b270_01E04340 {
    u8 pad[0xD990];
    s32 timer;
} Ctx_b270_01E04340;

typedef struct Obj_b270_01E04340 {
    u8 pad0[0x50];
    s16 level;
    u8 pad52[6];
    s16 state;
} Obj_b270_01E04340;

static s32 func_01E04340_b270(Ctx_b270_01E04340 *ctx, Obj_b270_01E04340 *o) {
    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (ctx->timer > 0x14) {
        if (o->level > 0x40) {
            o->level -= 10;
        } else {
            o->level = 0x40;
        }
    } else {
        if (o->level < 0x80) {
            o->level += 10;
        } else {
            o->level = 0x80;
        }
        if (o->level > 0x80) {
            o->level = 0x80;
        }
    }
    func_001F6D00((u8)o->level);
    return 0;
}

/* shape b270:01E04400, 130 insns: b594:01E02CB0 with a 0x90/0x90/0x78 sprite starting at 1, scene count at ctx+0xDA94, fading out from 460 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b270_01E04400;

typedef struct {
    f32 s, t;
    Xyz_b270_01E04400 p;
} Tv_b270_01E04400;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b270_01E04400 v[2];
    u8 tail[0x20];
} Tex_b270_01E04400;

typedef struct {
    u8 pad0[0xDA94];
    s16 count;
} Ctx_b270_01E04400;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b270_01E04400;

static s32 func_01E04400_b270(Ctx_b270_01E04400 *g, Fx_b270_01E04400 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b270_01E04400 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
    }
    ((Tex_b270_01E04400 *)(s32)&pk)->flags = 0x26;
    ((Tex_b270_01E04400 *)(s32)&pk)->size = 5;
    ((Tex_b270_01E04400 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b270_01E04400 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x90;
    pk.g = 0x90;
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
    if (g->count < 460) {
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

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E04610_b270(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b270", func_01E04620_b270);

/* shape b270:01E05090, 106 insns: takes the first free of 250 effect slots (0x70 bytes, b041:01E02C00 shape),
   clears and marks it, colours both from the scene, places it at the scene point, copies its settings and stores both
   arguments */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b270_01E05090;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b270_01E05090 slot[250];
    u8 padEnd[0xD994 - 0x2A0 - 250 * 0x70];
    u8 col[4];
    u8 padD998[0xE2];
    s16 hDA7A;
    u8 padDA7C[0x10];
    s16 hDA8C;
} Scene_b270_01E05090;

static s32 func_01E05090_b270(Scene_b270_01E05090 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b270_01E05090 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 250; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 250;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h5A = s->hDA7A;
        sl->h50 = s->hDA8C;
        sl->h52 = s->hDA8C;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b270:01E05240 (B270PAINT_RAIN20), 200 insns, 1 copy: b529:01E03F40's one-segment ring draw with this module's
   scene layout: ordering table g+0xD99C, frame table g+0xD9E4, trig g+0xDC98 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    s16 h50;
    u8 pad52[8];
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b270_01E05240;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xD99C - 0xC0];
    s32 ot;
    u8 padD9A0[0xD9E4 - 0xD9A0];
    s16 tbl[36];
    u8 padDA2C[0xDC98 - 0xDA2C];
    u8 trig[1];
} Game_b270_01E05240;

static void func_01E05240_b270(Game_b270_01E05240 *g, Obj_b270_01E05240 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    Rect_b152_01E014F0 rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    rc = func_01E01810_b270(0x14, g->tbl[o->h50 % 36], 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        a = s + (s16)(o->h5A + 10) - 200; /* the (s16) keeps the +10 apart: needed for the match */
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b270", func_01E05560_b270);
