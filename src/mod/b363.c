#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b363(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b363:01E00110 (POLPAN_UVIN_FT4), 345 insns, 1 copy: texture coordinates of a sprite quad from a rectangle,
   modes 0-3 as b034:01E00110 plus a fifth corner order for mode 5 */

typedef struct Rect_b363_01E00110 {
    s16 x, y, w, h;
} Rect_b363_01E00110;

typedef struct Uv_b363_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b363_01E00110;

typedef struct Pk_b363_01E00110 {
    u8 pad0[0x18];
    Uv_b363_01E00110 c[4];
} Pk_b363_01E00110;

static void func_01E00110_b363(Pk_b363_01E00110 *p, Rect_b363_01E00110 *r, s32 mode) {
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
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
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

static void func_01E00680_b363(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

static void func_01E00850_b363(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

/* shape b363:01E00BB0 (IWMagicGas1), 362 insns, 90 copies: b034:01E008B0's source (shape b016:01E00920): draw an
   object's parts as sprite quads, each part shaken on three axes from a signed byte table (scaled by cam->f50 + part
   / 2); same packet and depth modes as b016:01E00ED0; texture corners by the module helper func_01E00110_b363 */

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

typedef struct Cam_b363_01E00BB0 {
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
} Cam_b363_01E00BB0;

typedef struct Obj_b363_01E00BB0 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b363_01E00110 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b363_01E00BB0;

typedef struct Uv_b363_01E00BB0 {
    f32 u, v;
} Uv_b363_01E00BB0;

typedef struct Xyz_b363_01E00BB0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b363_01E00BB0;

typedef struct Pk_b363_01E00BB0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b363_01E00BB0 uv;
    u64 pad18;
    Xyz_b363_01E00BB0 v[4];
    u64 pad60[6];
} Pk_b363_01E00BB0;

typedef struct Buf_b363_01E00BB0 {
    u64 tag;
    Pk_b363_01E00BB0 pk;
} Buf_b363_01E00BB0;

static void func_01E00BB0_b363(Obj_b363_01E00BB0 *obj, Cam_b363_01E00BB0 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b363_01E00BB0 *p;
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
    Buf_b363_01E00BB0 buf;
    Uv_b363_01E00BB0 uv;

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
    func_01E00110_b363((Pk_b363_01E00110 *)p, &obj->rect, 0);
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
            func_01E00110_b363((Pk_b363_01E00110 *)p, &obj->rect, obj->fC0[i]);
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b363:01E01160, 477 insns: b111:01E00D70's sprite ring without the per-sprite turn: each point-sized
   quad is pushed out along the rotated table offset; mode 0 widens it on screen by size / (depth / (fov / 10))
   (fov from func_001F9A20, 400 when 0) and draws at depth 0; 1 = far z, 2 = -1 */

typedef struct Data_b363_01E01160 {
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
} Data_b363_01E01160;

typedef struct Obj_b363_01E01160 {
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
} Obj_b363_01E01160;

typedef struct Xyz_b363_01E01160 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b363_01E01160;

typedef struct Uv_b363_01E01160 {
    f32 u, v;
} Uv_b363_01E01160;

typedef struct Pk_b363_01E01160 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b363_01E01160 uv;
    u64 pad18;
    Xyz_b363_01E01160 v[4];
    u64 pad60[6];
} Pk_b363_01E01160;

typedef struct Buf_b363_01E01160 {
    u64 tag;
    Pk_b363_01E01160 pk;
} Buf_b363_01E01160;

static void func_01E01160_b363(Obj_b363_01E01160 *obj, Data_b363_01E01160 *data, s32 flags, s8 *tab) {
    f32 size;
    f32 fov;
    extern void b363_01E00110();
    extern void func_00108950();
    extern void func_00108EF0();
    extern f32 func_001F9A20(s32);
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b363_01E01160 buf;
    Uv_b363_01E01160 uv;
    s16 sel;
    s16 i;
    Pk_b363_01E01160 *p;
    s32 mode;
    s8 *row;
    s32 half;

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
    b363_01E00110(p, obj->f94, obj->fC0);
    fov = func_001F9A20(0);
    if (fov == 0.0f) {
        fov = 400.0f;
    }
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        size = data->f48;
        func_00108CE0(view, 0.0f, 0.0f);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = (row[data->f8 + 180] / 20.0f) * (data->f50 + half);
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                size /= depth[0] / (fov / 10.0f);
                p->v[0].x = (u32)((f32)(u32)p->v[0].x - size);
                p->v[0].y = (u32)((f32)(u32)p->v[0].y + size);
                p->v[1].x = (u32)((f32)(u32)p->v[1].x + size);
                p->v[1].y = (u32)((f32)(u32)p->v[1].y + size);
                p->v[2].x = (u32)((f32)(u32)p->v[2].x - size);
                p->v[2].y = (u32)((f32)(u32)p->v[2].y - size);
                p->v[3].x = (u32)((f32)(u32)p->v[3].x + size);
                p->v[3].y = (u32)((f32)(u32)p->v[3].y - size);
                func_002075F0((s32)p, obj->f80, 0);
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

extern void b363_01E00110(Pkt_b279_01E00920 *, void *, s32);

static void func_01E018E0_b363(Obj_b279_01E00920 *o, Anim_b279_01E00920 *an, s32 mode, Vec_b279_01E00920 pos) {
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
    b363_01E00110(p, o->b94, o->hC0);
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

/* shape b363:01E01D30 (IWMagicSmoke2), 206 insns, 4 copies: b849:01E01570's source: b016:01E00ED0 with the view's y
   column raised by cam h + cam 0x34, then func_00109100(view, {cam 0x5C, 0x5A, 0x5C}, 2 and 0, obj 0xD8); one sprite
   quad at an object's position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Texture corners
   by the module helper func_01E00110_b363 (static, defined above) */

typedef struct Cam_b363_01E01D30 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x22];
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    Vec4f at;
} Cam_b363_01E01D30;

typedef struct Obj_b363_01E01D30 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b363_01E01D30;

typedef struct Xyz_b363_01E01D30 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b363_01E01D30;

typedef struct Uv_b363_01E01D30 {
    f32 u, v;
} Uv_b363_01E01D30;

typedef struct Pk_b363_01E01D30 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b363_01E01D30 uv;
    u64 pad18;
    Xyz_b363_01E01D30 v[4];
    u64 pad60[6];
} Pk_b363_01E01D30;

typedef struct Buf_b363_01E01D30 {
    u64 tag;
    Pk_b363_01E01D30 pk;
} Buf_b363_01E01D30;

static void func_01E01D30_b363(Obj_b363_01E01D30 *obj, Cam_b363_01E01D30 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b363_01E01D30 buf;
    Uv_b363_01E01D30 uv;
    s32 sel;
    s32 k;
    s32 mode;
    Pk_b363_01E01D30 *p = &buf.pk;

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
    func_01E00110_b363((Pk_b363_01E00110 *)p, (Rect_b363_01E00110 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    for (k = 0; k < 4; k++) {
        view[k][1] += cam->h + cam->f34;
    }
    arg[0] = cam->f5C;
    arg[1] = cam->f5A;
    arg[2] = cam->f5C;
    func_00109100(view, arg, 2, obj->fD8);
    func_00109100(view, arg, 0, obj->fD8);
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

INCLUDE_ASM("asm/nonmatchings/mod/b363", func_01E02070_b363);

/* shape b363:01E02940, 63 insns: a violet-white rising flash: set up once (f48 20, f4C 58 below it, size 15x15), full
   alpha for 2 frames, then fades by 9 until it ends; f48 rises 18 a frame with f4C 30 below it */

typedef struct {
    u8 pad0[0x48];
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
} Obj_b363_01E02940;

static s32 func_01E02940_b363(void *arg0, Obj_b363_01E02940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xC0, 0x80, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 += 18.0f;
    o->f4C = o->f48 - 30.0f;
    o->t++;
    return 0;
}

/* shape b363:01E02A40, 229 insns: a white flash at the target's model point jittered -10..9 on x and z, height 35,
   frame 13, size 160, random turn 0..359 and tilt -90..89; both alphas up by 42 to 0x80 for 3 ticks; its reach f34
   falls from 1000 by 80 a tick, then it fades by 14; at tick 11 it moves the scene point there plus a tenth of the
   reach along its turn (camera yaw / 180 taken off), sets the scene turn to -180 x its tilt / turn and spawns
   b363:01E02940; the rotation is re-read each tick with x cleared */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xDE60 - 0x260];
    s32 rx;
    s32 ry;
    u8 padDE68[0xE0F8 - 0xDE68];
    u8 table[1];
} Game_b363_01E02A40;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 reach;
    u8 pad38[0x1C];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 turn;
    s16 tilt;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b363_01E02A40;

static s32 func_01E02A40_b363(Game_b363_01E02A40 *g, Fx_b363_01E02A40 *o) {
    extern s32 b363_01E02940(void);
    extern s32 b363_01E05C00(Game_b363_01E02A40 *, s32 (*)(void), s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    f32 v[4];
    s32 rot[4];
    s32 cam[4];

    if (o->mode == 1) {
        o->h8 = 13;
        o->hA = 160;
        func_001F5F90(func_001F5380(), &o->pos);
        o->pos.x += func_0019A5C8() % 20 - 10;
        o->pos.z += func_0019A5C8() % 20 - 10;
        o->pos.y = 35.0f;
        o->reach = 1000.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
        o->turn = func_0019A5C8() % 360;
        o->tilt = func_0019A5C8() % 180 - 90;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    }
    if (o->tick != 0) {
        if (!(o->reach <= 0.0f)) {
            o->reach -= 80.0f;
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
    }
    if (o->tick == 11) {
        g->pos = o->pos;
        *(f32 *)(u32)&v[1] = o->reach / 10.0f;
        v[0] = 0.0f;
        *(f32 *)(u32)&v[2] = 0.0f;
        rot[0] = o->tilt;
        *(s32 *)(u32)&rot[1] = o->turn;
        rot[2] = o->tilt;
        func_00205C40((s32)cam);
        *(s32 *)(u32)&rot[1] -= cam[1] / 180;
        func_00108950(v, rot, 2, g->table);
        func_00108950(v, rot, 0, g->table);
        g->pos.x += v[0];
        g->pos.y = g->pos.y + *(f32 *)(u32)&v[1];
        g->pos.z = g->pos.z + *(f32 *)(u32)&v[2];
        g->ry = o->turn * -180;
        g->rx = o->tilt * -180;
        b363_01E05C00(g, b363_01E02940, 0, 1);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] = 0;
    o->tick++;
    return 0;
}

/* shape b363:01E02DE0, 100 insns: a pink spark (b434:01E02210 shape): size 2..7, random sub-frame 0..7, height 100..199, angle,
   rise 20..39, width 0..34, hold 3..16; alpha up by 0x60 to 0xC0 until the hold, then down by 14 until it ends */

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
} Obj_b363_01E02DE0;

static s32 func_01E02DE0_b363(void *arg0, Obj_b363_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 6 + 2;
        o->sub = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0xFF, 0xCF, 0xCF);
        o->y = func_0019A5C8() % 100 + 0x64;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x14;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 14 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b363:01E02F70, 107 insns: on start f48 10, colour (0x80, 0x40, 0xFF) (first set to (0xCF, 0x80, 0x80)), second
   colour (0x80, 8, 8) with alpha 0, rotation x/z -0x2000..0x1FFF and random y, 0x5A = 45, 0x5C = 1; alpha grows by
   0x40 (below 0xC0) for 8 ticks, then fades by 9 and stops; f48 grows by 7.5 for 4 ticks, then by 7.8 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b363_01E02F70;

static s32 func_01E02F70_b363(s32 arg0, Fx_b363_01E02F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 8, 8);
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0x4000 - 0x2000;
        o->f5A = 45;
        o->f5C = 1;
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
    if (o->tick < 4) {
        o->f48 += 7.5f;
    } else {
        o->f48 += 7.8f;
    }
    o->tick++;
    return 0;
}

/* shape b363:01E03120 (B363_OBJ_MOVE_6_), 238 insns: a spark that travels from joint A (g+0xDEC0) toward joint B
   (g+0xDEC2) in 140 steps, size 100 growing 2 a tick, purple 0x40/0x20/0x80, sinking 1.3 a tick after scene frame 160,
   stepping 1..n per tick with n = frame - 100 clamped to 1..15 (chatA, 16 Oct) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x2C];
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
} Fx_b363_01E03120;

typedef struct {
    u8 pad0[0xDEC0];
    s16 ja;
    s16 jb;
    u8 padDEC4[0xDEF6 - 0xDEC4];
    s16 frame;
} Scene_b363_01E03120;

static s32 func_01E03120_b363(Scene_b363_01E03120 *g, Fx_b363_01E03120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[2][4];
    f32 p[4];
    f32 k;
    s16 n;

    func_001F5620(func_001F53A0(), g->ja, v[0]);
    func_001F5620(func_001F53A0(), g->jb, v[1]);
    v[1][0] = (v[1][0] - v[0][0]) / 140.0f;
    v[1][1] = (v[1][1] - v[0][1]) / 140.0f;
    v[1][2] = (v[1][2] - v[0][2]) / 140.0f;
    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->f56 = 0;
        func_001076F0(o->col, 0x40, 0x20, 0x80);
        o->fA = o->f50;
        o->f50 = func_0019A5C8() % 15 + 1;
        o->f5A = func_0019A5C8() % 360;
        o->fE = func_0019A5C8() % 3 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 6 + 2;
        o->fC = func_0019A5C8() % 2;
        o->f52 = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    k = o->f52;
    func_001F5620(func_001F53A0(), g->ja, p);
    o->x = p[0] + v[1][0] * k;
    o->y = p[1] + v[1][1] * k;
    o->z = p[2] + v[1][2] * k;
    if (g->frame > 160) {
        o->y -= 1.3f;
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f5A += 5;
        } else {
            o->f5A -= 5;
        }
    }
    o->f48 += 2.0f;
    if (o->tick != 0) {
        o->f50 += o->fE;
    }
    n = g->frame - 100;
    if (n <= 0) {
        n = 1;
    }
    if (n > 15) {
        n = 15;
    }
    o->f52 += (s16)(func_0019A5C8() % n + 1);
    o->tick++;
    return 0;
}

/* shape b363:01E034E0, 150 insns: b746:01E03010's turning spark, size 100, frame 0, blue before scene frame 107 (0xDEF6) else red, speed 2..9, drifting 0..0.9 a tick on 0x14, turning 5 a tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    u8 pad18[0x30];
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
} Fx_b363_01E034E0;

typedef struct {
    u8 pad0[0xDEF6];
    s16 frame;
} Scene_b363_01E034E0;

static s32 func_01E034E0_b363(Scene_b363_01E034E0 *g, Fx_b363_01E034E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 f;

    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->f56 = 0;
        if (g->frame < 0x6B) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else {
            func_001076F0(o->col, 0x80, 0x20, 0x20);
        }
        o->fA = o->f50;
        o->f50 = func_0019A5C8() % 15 + 1;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 8 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 2;
        o->fC = func_0019A5C8() % 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    f = (f32)(func_0019A5C8() % 10) / 10.0f;
    if (o->tick != 0) {
        o->y += f;
    }
    if (o->tick != 0) {
        if (o->fC == 0) {
            o->f5A += 5;
        } else {
            o->f5A -= 5;
        }
    }
    o->f48 += 1.0f;
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b363:01E03740, 187 insns: a grey shock ring of kind 0x52: kind 0 turns randomly on y, starts at size 230
   growing by 15 to 400 and drifts outward on x by 1..5; kind 1 turns randomly on all axes, starts at 80 and grows by
   25; both rise from height 90 by 0..6 a tick and end past 270; alpha jumps by 0x60 for 7 ticks */

typedef struct {
    u8 pad0[0x10];
    f32 x;
    u8 pad14[0xC];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 h;
    s16 kind;
    s16 t;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Ring_b363_01E03740;

static s32 func_01E03740_b363(s32 arg0, Ring_b363_01E03740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->rot[1] = func_0019A5C8() % 65535;
            o->size = 230.0f;
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            o->h = 90;
        }
        if (o->kind == 1) {
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
            o->size = 80.0f;
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            o->h = 90;
        }
        o->h56 = 0;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->t < 7) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 16) {
        o->col[3] += 15;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->h < 270) {
            o->h += (s16)(func_0019A5C8() % 7);
        } else {
            o->mode = 0;
        }
        if (o->size < 400.0f) {
            o->size += 15.0f;
        }
        if (o->x > 0.0f) {
            o->x += func_0019A5C8() % 5 + 1;
        } else {
            o->x -= func_0019A5C8() % 5 + 1;
        }
    }
    if (o->kind == 1) {
        if (o->h < 270) {
            o->h += (s16)(func_0019A5C8() % 7);
        } else {
            o->mode = 0;
        }
        o->size += 25.0f;
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b363", func_01E03A30_b363);

/* shape b363:01E04090 (B363_OBJ_MOVE_10_), 385 insns, 1 copy: b270:01E03900 jittery spark trail
   with a 30-point track: start kick %30-15, size 5..54, speed 3..87, pitch without >>4 and its sine taken with 1,
   0x40/0x20 blink, kick %40-20 */

typedef struct {
    Vec4f p[0x1E];
} Track_b363_01E04090;

typedef struct {
    u8 pad0[0x5190];
    Track_b363_01E04090 track[0x46];
    Vec4f pt[0xC2];
    u8 pad_E0F0[8];
    u8 trig[1];
} World_b363_01E04090;

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
} Spark_b363_01E04090;

static s32 func_01E04090_b363(World_b363_01E04090 *w, Spark_b363_01E04090 *o) {
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
        o->v.x = func_0019A5C8() % 30 - 15;
        o->v.y = func_0019A5C8() % 30 - 15;
        o->v.z = func_0019A5C8() % 30 - 15;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x1E; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 50 + 5;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 85 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = func_0019A5C8() % 360;
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
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    } else {
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
    }
    o->v.x = func_0019A5C8() % 40 - 20;
    o->v.y = func_0019A5C8() % 40 - 20;
    o->v.z = func_0019A5C8() % 40 - 20;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 1);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        func_01E00080_b363(&w->track[o->idx].p[0x1D], 0x1E, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b363:01E046A0, 120 insns: constant variant of b611:01E01BD0 (50->100, 16->20, 0x40->0x60, 6.0f->3.0f, colour (255, 207, 207)) */

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
} Fx_b363_01E046A0;

static s32 func_01E046A0_b363(s32 arg0, Fx_b363_01E046A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 30 + 70;
        o->f56 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xCF, 0xCF);
        o->f50 = func_0019A5C8() % 100 + 100;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 20 + 20;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 14 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick < 0x5A) {
        if (o->tick != 0) {
            o->f50 += o->spin;
        }
    }
    if (o->tick < 0x8C) {
        o->f48 += 3.0f;
    }
    o->tick++;
    return 0;
}

/* shape b363:01E04880, 182 insns, 1 copy: B363_OBJ_MOVE_40_: on start sets the colours, size and life by kind (kind 2
   also rolls three random angles); fades in by 0x40 while young, then out by 11 and ends; kind 1 follows the scene's
   point, kind 2 grows; colour blinks every other tick; kinds 0/1 spin */

typedef struct Game_b363_01E04880 {
    u8 pad0[0xDE50];
    Vec4f pos;
} Game_b363_01E04880;

typedef struct Obj_b363_01E04880 {
    u8 pad0[6];
    s16 life;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    f32 h4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 w5A;
    s16 w5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b363_01E04880;

static s32 func_01E04880_b363(Game_b363_01E04880 *g, Obj_b363_01E04880 *o) {
    extern void func_001076F0();
    extern s32 func_0019A5C8();
    extern void func_00205C40();

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->size = 550.0f;
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            o->life = 15;
        } else if (o->kind == 1) {
            o->size = 80.0f;
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            o->life = 25;
        } else if (o->kind == 2) {
            o->size = 80.0f;
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            o->rot[0] = func_0019A5C8() % 0xFFFF;
            o->rot[1] = func_0019A5C8() % 0xFFFF;
            o->rot[2] = func_0019A5C8() % 0xFFFF;
            o->life = 10;
        }
        o->w5A = 15;
        o->w5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 1) {
        o->pos = g->pos;
    }
    if (o->kind == 2) {
        o->size += 8.0f;
        o->h4C += (o->size - 2.0f) / 3.0f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->col2, 0xC0, 0x70, 0x70);
    }
    if (o->kind != 2) {
        func_00205C40(o->rot);
        o->rot[0] += 0x4000;
    }
    o->t++;
    return 0;
}

/* shape b363:01E04B60, 82 insns: b283:01E036C0 twin (white, or blue/teal for kind 1): in by 18 up to 0x80 for 22 ticks, then out by 4 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b363_01E04B60;

static s32 func_01E04B60_b363(s32 arg0, Obj_b363_01E04B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->h6 = 22;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xF0, 0xD0, 0xA0);
            func_001076F0(o->col2, 0xF0, 0xA0, 0xA0);
            o->h6 = 22;
        }
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x12;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 5) {
            o->col2[3] -= 4;
        } else {
            o->col2[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b363:01E04CB0, 53 insns: volume fade by game state (b003:01E02330 family, layout at 0x50): state at 0xDE90
   limit 0x1E, floor 0x50, down 10, up 10, cap 0x80; state 2 sets the volume to 0x80 and ends the fade */

typedef struct {
    u8 pad[0xDE90];
    s32 state;
} Game_b363_01E04CB0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b363_01E04CB0;

static s32 func_01E04CB0_b363(Game_b363_01E04CB0 *g, Fade_b363_01E04CB0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x50) {
            o->vol -= 10;
        } else {
            o->vol = 0x50;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 2) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b363:01E04D90, 127 insns: b594:01E02CB0 with a 0x80 grey sprite zooming OUT by f48, alpha up by 10 to 0x50 for 244 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b363_01E04D90;

typedef struct {
    f32 s, t;
    Xyz_b363_01E04D90 p;
} Tv_b363_01E04D90;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b363_01E04D90 v[2];
    u8 tail[0x20];
} Tex_b363_01E04D90;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b363_01E04D90;

static s32 func_01E04D90_b363(s32 arg0, Fx_b363_01E04D90 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b363_01E04D90 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    z = 0.0f;
    ((Tex_b363_01E04D90 *)(s32)&pk)->flags = 0x26;
    ((Tex_b363_01E04D90 *)(s32)&pk)->size = 5;
    ((Tex_b363_01E04D90 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b363_01E04D90 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
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
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->tick < 244) {
        if (o->col[3] < 0x50) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b363", func_01E04F90_b363);

/* shape b363:01E05C00, 117 insns: take a free effect slot (0xB4 of 0x70 bytes at 0x2A0), clear it, colour both colours
   from the scene colour 0xDE94, attach it to the scene position (0x250) and copy it, 0x50 and 0x52 from 0xDEEE, store
   the two arguments, and with a3 == 1 copy the scene rotation 0xDE60; returns 1 if a slot was found */

typedef struct {
    f32 x, y, z, w;
} Rot_b363_01E05C00;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[4];
    Rot_b363_01E05C00 rot;
    u8 pad30[0x10];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b363_01E05C00;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b363_01E05C00 slots[0xB4];
    u8 pad5160[0xDE60 - 0x5160];
    Rot_b363_01E05C00 rot;
    u8 padDE70[0xDE94 - 0xDE70];
    u8 rgba[4];
    u8 padDE98[0xDEEE - 0xDE98];
    s16 fDEEE;
} Scene_b363_01E05C00;

static s32 func_01E05C00_b363(Scene_b363_01E05C00 *g, s32 a1, s32 a2, s32 a3) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b363_01E05C00 *s = NULL;
    s16 i;

    for (i = 0; i < 0xB4; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0xB4;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f50 = g->fDEEE;
        s->f52 = g->fDEEE;
        s->a2 = a2;
        s->a1 = a1;
        if (a3 == 1) {
            s->rot = g->rot;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b363", func_01E05DE0_b363);

/* shape b363:01E06930, 264 insns, 4 copies: draws a band of 12 quads (two rings, radius and height from the table at two
   angles 20 apart) around a position, scaled by size / 1500, turned by the object's rotation; blend from
   flags >> 4. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b363_01E06930;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[8];
    s16 start;
    u8 pad5C[4];
    u8 col[4];
} Band_b363_01E06930;

static void func_01E06930_b363(Obj_b363_01E06930 *o, Band_b363_01E06930 *s, Vec4f pos, s32 flags) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    f32 r0;
    s32 k;
    s16 b;
    s16 a;
    s16 t;
    u8 *p;
    f32 r1;
    f32 sc;

    p = pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    sc = s->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 90.0f * func_00108030(o->xD8, s->h50, 0);
    quad[1].y = quad[0].y;
    quad[2].y = 90.0f * func_00108030(o->xD8, s->h50 + 20, 0);
    quad[3].y = quad[2].y;
    r0 = 90.0f * func_00108030(o->xD8, s->h50, 1);
    r1 = 90.0f * func_00108030(o->xD8, s->h50 + 20, 1);
    a = 0;
    for (k = 0; k < 12; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[2].x = r1 * func_00108030(o->xD8, t, 1);
            quad[2].z = r1 * func_00108030(o->xD8, t, 0);
            quad[0].x = r0 * func_00108030(o->xD8, t, 1);
            quad[0].z = r0 * func_00108030(o->xD8, t, 0);
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        } else {
            quad[2].x = quad[3].x;
            quad[2].z = quad[3].z;
            quad[0].x = quad[1].x;
            quad[0].z = quad[1].z;
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
        a += 30;
    }
}
