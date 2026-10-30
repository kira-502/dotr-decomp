#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b771(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b771(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b771(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b771((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b771((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b771:01E00F60, 216 insns: b094:01E00920's ring band with every quad angle offset by the data's base angle
   (0x52) */

typedef struct {
    f32 x, y, z, w;
} Vec_b771_01E00F60;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b771_01E00F60;

typedef struct {
    u8 pad00[0x20];
    Vec_b771_01E00F60 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[2];
    s16 base;
    u8 pad54[6];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b771_01E00F60;

static void func_01E00F60_b771(Obj_b771_01E00F60 *obj, Data_b771_01E00F60 *data, s32 flags, Vec_b771_01E00F60 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b771_01E00F60 c;
    Vec_b771_01E00F60 quad[4];
    Vec_b771_01E00F60 pos;
    Vec_b771_01E00F60 scale;
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
        a = data->base + (data->step + j);
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = data->base + (j + (data->step + width));
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

static void func_01E012D0_b771(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b771:01E01630 (B771_W_S), 388 insns, 1 copy: B771_W_S, the effect scene step: counts the frame (0xA92E);
   before 155 takes joint 0xA8F8 into 0xA870, at 155 sets a 32-step slide toward joint 0xA908 run until 186; spawns on
   frames 118, 38..70, 118..475 (every other frame 0x1E01C40), ten 0x1E02C10 at 186, a 40-side ring of 0x1E026F0 on
   odd frames 200..475, the growth 0xA8E4 from 400, setup at 1 and 0x1E031B0 at 42 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xA870 - 0x260];
    Vec4f from;
    u8 padA880[0x10];
    Vec4f step;
    u8 padA8A0[0xA8E4 - 0xA8A0];
    f32 grow;
    u8 padA8E8[0xA8F8 - 0xA8E8];
    s16 joint0;
    u8 padA8FA[0xA908 - 0xA8FA];
    s16 joint1;
    u8 padA90A[0xA926 - 0xA90A];
    s16 side;
    s16 ring;
    u8 padA92A[0xA92E - 0xA92A];
    s16 t;
} Scene_b771_01E01630;

static void func_01E01630_b771(Scene_b771_01E01630 *g) {
    extern void b771_01E01C40(void);
    extern void b771_01E01D90(void);
    extern void b771_01E01FB0(void);
    extern void b771_01E02130(void);
    extern void b771_01E022D0(void);
    extern void b771_01E02460(void);
    extern void b771_01E026F0(void);
    extern void b771_01E02C10(void);
    extern void b771_01E02FD0(void);
    extern void b771_01E031B0(void);
    extern void b771_01E03230(void);
    extern void b771_01E03E00(Scene_b771_01E01630 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v[2];
    s16 i;

    g->t++;
    if (g->t < 155) {
        func_001F5620(func_001F53A0(), g->joint0, &g->from);
    } else {
        if (g->t == 155) {
            func_001F5620(func_001F5380(), g->joint1, v);
            g->step.z = (v[0].z - g->from.z) / 32.0f;
            g->step.y = (v[0].y - g->from.y) / 32.0f;
        }
        if (g->t < 186) {
            g->from.z += g->step.z;
            g->from.y += g->step.y;
        }
    }
    if (g->t == 118) {
        b771_01E03E00(g, b771_01E02130, 0);
    }
    if (g->t >= 38 && g->t < 71) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pos);
        g->side = 1;
        b771_01E03E00(g, b771_01E02460, 0);
    }
    if (g->t >= 118 && g->t < 476) {
        if (g->t < 281) {
            g->side = 0;
            b771_01E03E00(g, b771_01E02C10, 0);
            g->side = 1;
            b771_01E03E00(g, b771_01E02C10, 0);
            b771_01E03E00(g, b771_01E022D0, 0);
        }
        func_001F5620(func_001F53A0(), g->joint0, &g->pos);
        g->side = 0;
        b771_01E03E00(g, b771_01E02460, 0);
        if (g->t >= 280) {
            b771_01E03E00(g, b771_01E02460, 0);
        }
        if (g->t % 2 == 0) {
            b771_01E03E00(g, b771_01E01C40, 0);
        }
    }
    if (g->t == 186) {
        g->pos = g->from;
        g->side = 0;
        for (i = 0; i < 10; i++) {
            b771_01E03E00(g, b771_01E02C10, 0);
        }
    }
    if (g->t >= 200 && g->t < 476) {
        if (g->t % 2 == 1) {
            g->side = g->ring;
            b771_01E03E00(g, b771_01E026F0, 0);
            g->ring++;
            if (g->ring >= 40) {
                g->ring = 0;
            }
            g->side = g->ring;
            b771_01E03E00(g, b771_01E026F0, 0);
            g->ring++;
            if (g->ring >= 40) {
                g->ring = 0;
            }
        }
    }
    if (g->t < 400) {
        g->grow = 5.0f;
    } else {
        g->grow += 0.26f;
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y = 37.0f;
        if (g->t < 476) {
            b771_01E03E00(g, b771_01E01D90, 0);
        }
    }
    if (g->t == 1) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y = 37.0f;
        b771_01E03E00(g, b771_01E01FB0, 0);
        b771_01E03E00(g, b771_01E02FD0, 0);
        b771_01E03E00(g, b771_01E03230, 0);
    }
    if (g->t == 42) {
        b771_01E03E00(g, b771_01E031B0, 0);
    }
}

/* shape b771:01E01C40, 84 insns: a grey beam growing 25 a tick from 10 (tail 15 behind), its second colour blinking green: in by 64 up to 0xC0 for 4 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b771_01E01C40;

static s32 func_01E01C40_b771(s32 arg0, Obj_b771_01E01C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 0xC0, 0x80);
    }
    o->f48 += 25.0f;
    o->f4C = o->f48 - 15.0f;
    o->t++;
    return 0;
}

/* OVL_WARM */

/* shape b771:01E01D90, 134 insns: a rising spark scaled by the scene value at g+0xA8E4 (s): on start size 10, h56 5, grey
   0x80, random spins, height 6s + rand % 5s, a random angle, speed 1..3, frame 1..8, fade-in 1..3 ticks; alpha up by 64
   to 0xC0 during the fade-in, then down by 13 until it ends; it rises by 2.5 a tick */

typedef struct {
    u8 pad0[0xA8E4];
    f32 scale;
} Game_b771_01E01D90;

typedef struct {
    u8 pad0[6];
    s16 fadein;
    s16 frame;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    f32 y;
    u8 pad18[8];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b771_01E01D90;

static s32 func_01E01D90_b771(Game_b771_01E01D90 *g, Obj_b771_01E01D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->size = 10.0f;
        o->h56 = 5;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        k = 5.0f * g->scale;
        o->h50 = 6.0f * g->scale + func_0019A5C8() % k;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->frame = func_0019A5C8() % 8 + 1;
        o->fadein = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->t < o->fadein) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 0xD;
    } else {
        o->mode = 0;
    }
    o->y += 2.5f;
    o->t++;
    return 0;
}

/* shape b771:01E01FB0, 96 insns: a grey ring sized 10 x the scene scale (ctx+0xA8E4), its second colour blinking green: in by 64 up to 0xC0 for 4 ticks; out by 11 once the scene value reaches 486, and ends */

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b771_01E01FB0;

typedef struct {
    u8 pad[0xA8E4];
    f32 scale;
    u8 padA8E8[0x46];
    s16 val;
} Game_b771_01E01FB0;

static s32 func_01E01FB0_b771(Game_b771_01E01FB0 *g, Obj_b771_01E01FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f * g->scale;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (g->val > 485) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 0xC0, 0x80);
    }
    o->f48 = 10.0f * g->scale;
    o->t++;
    return 0;
}

/* shape b771:01E02130, 104 insns: a grey-green flicker flash (b406:01E027F0 shape): size 110 shrinking by 5 to 60 once the scene
   timer passes 280; alpha up by 12 to 0x80 while the timer is under 480, then down by 11; second colour flickers green; spins */

typedef struct {
    u8 pad0[0xA92E];
    s16 timer;
} Game_b771_01E02130;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b771_01E02130;

static s32 func_01E02130_b771(Game_b771_01E02130 *g, Obj_b771_01E02130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 110.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        func_001076F0(o->c1, 0x80, 0xFF, 0x80);
        o->h5A = 0xF;
        o->h5C = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x1E0) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0xFF, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 0xC0, 0x80);
    }
    if (g->timer > 0x118) {
        if (o->size > 60.0f) {
            o->size -= 5.0f;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b771:01E022D0, 99 insns: on start f48 20..99, f4C 0, colour 0x48 grey, second colour (0x40, 0x80, 0x40) with
   alpha 0, 0x5A/0x5C = 15; alpha grows by 0x30 (below 0x60) for 2 ticks, then fades by 11 and stops; the second
   colour flickers green; f48 grows by 1 after the first tick; the rotation at 0x20 advances 0x4000 */

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
} Fx_b771_01E022D0;

static s32 func_01E022D0_b771(s32 arg0, Fx_b771_01E022D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f + func_0019A5C8() % 80;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0x48, 0x48, 0x48);
        func_001076F0(o->col2, 0x40, 0x80, 0x40);
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
        func_001076F0(o->col2, 0x20, 0x80, 0x20);
    } else {
        func_001076F0(o->col2, 0x20, 0x40, 0x20);
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b771:01E02460, 163 insns: a dust mote's step, kind 0 or 1 (0x52): on start it picks a size 6..11, a frame 0..3,
   grey 0x80 (or 0xC0), random turns, a radius 10..39 (or 10..29) growing by 10..12 a tick, a start angle, a step
   1..8 and a 2..4-tick hold at alpha 0x60, then fades by 11; kind 0 also circles by 3 and sinks 1.5 a tick */

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
} Mote_b771_01E02460;

static s32 func_01E02460_b771(s32 arg0, Mote_b771_01E02460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 6 + 6;
        o->frame = func_0019A5C8() % 4;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        }
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        if (o->kind == 0) {
            o->r = func_0019A5C8() % 30 + 10;
        }
        if (o->kind == 1) {
            o->r = func_0019A5C8() % 20 + 10;
        }
        o->ang = func_0019A5C8() % 360;
        o->grow = func_0019A5C8() % 3 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->ang += 3;
        o->pos[1] -= 1.5f;
    }
    o->r += o->grow;
    o->tick++;
    return 0;
}

/* shape b771:01E026F0, 326 insns (B771_OBJ_MOVE_9_): a green swirl band: on start its height is the scene base plus
   2..7, a random heading and turn side, radius the scene scale, and its two trails (0x280-byte slots at 0x4470, 20
   points each) filled with the start point (the second 30 degrees back and height / 10 up); fades in by 0x15 for 10
   ticks, then out by 9; each tick the heading turns 12 and both trails take a new point (b034:01E00080), the colour
   blinks green, the band count grows to 18 and from tick 5 it rises 1.5 */

typedef struct {
    Vec4f a[20];
    Vec4f b[20];
} Trail_b771_01E026F0;

typedef struct {
    u8 pad0[0x4470];
    Trail_b771_01E026F0 slot[1];
    u8 pad46F0[0xA8E4 - 0x46F0];
    f32 scale;
    u8 padA8E8[0xA922 - 0xA8E8];
    s16 base;
    u8 padA924[0xAB30 - 0xA924];
    u8 sin[4];
} Game_b771_01E026F0;

typedef struct {
    u8 pad0[6];
    s16 n;
    s16 h8;
    s16 h;
    u8 padC[0x28];
    f32 y;
    u8 pad38[0x10];
    f32 r;
    u8 pad4C[4];
    s16 idx;
    s16 dir;
    s16 t;
    s16 h56;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b771_01E026F0;

static s32 func_01E00080_b771();

static s32 func_01E026F0_b771(Game_b771_01E026F0 *g, Obj_b771_01E026F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    f32 f;
    f32 r;
    s16 h;
    Vec4f *p;
    s16 i;

    if (o->mode == 1) {
        h = g->base + (func_0019A5C8() % 6 + 2);
        o->h = h;
        f = h;
        f /= 10.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        v.y = 0.0f;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->dir = (func_0019A5C8() >> 4) % 2;
        r = g->scale;
        o->r = r;
        v.z = r * func_00108030(g->sin, o->ang, 0);
        v.x = r * func_00108030(g->sin, o->ang, 1);
        for (i = 0, p = g->slot[o->idx].a; i < 19; i++, p++) {
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
        }
        v.z = r * func_00108030(g->sin, o->ang - 30, 0);
        v.x = r * func_00108030(g->sin, o->ang - 30, 1);
        v.y = f;
        for (i = 0, p = g->slot[o->idx].b; i < 19; i++, p++) {
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
        }
        o->n = 2;
        o->col[3] = 0;
        o->h8 = 0;
        o->h56 = 0;
        o->mode = 2;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    f = o->h + o->y;
    f /= 10.0f;
    if (o->dir != 0) {
        o->ang += 12;
    } else {
        o->ang -= 12;
    }
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    v.y = o->h8 + o->y;
    r = o->r;
    v.z = r * func_00108030(g->sin, o->ang, 0);
    v.x = r * func_00108030(g->sin, o->ang, 1);
    func_01E00080_b771(&g->slot[o->idx].a[19], 20, 0, &v);
    v.y = o->y + (f + o->h8);
    v.z = r * func_00108030(g->sin, o->ang - 30, 0);
    v.x = r * func_00108030(g->sin, o->ang - 30, 1);
    func_01E00080_b771(&g->slot[o->idx].b[19], 20, 0, &v);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x50, 0x20);
    } else {
        func_001076F0(o->col, 0x10, 0x40, 0x10);
    }
    if (o->t != 0) {
        if (o->n < 18) {
            o->n++;
        }
    }
    if (o->t > 4) {
        o->y += 1.5f;
    }
    o->t++;
    return 0;
}

/* shape b771:01E02C10, 240 insns: b144:01E02030's ember in green (0x50, 0xC0, 0x50) on the tracked point
   (ctx+0xA8F8): kind 0 size 2..6, kind 1 size 6..10; before scene count 280 kind 0 sits 50..149 up rising 5..24 and
   kind 1 10..39 rising 10..12, later kind 0 30..79 rising 5..14 and kind 1 10..24 rising 4..6; random spin on all
   three axes; alpha 0x60 for its life, then down by 11 until it ends; it rises by its speed before count 220, by twice
   it until 280 */

typedef struct {
    u8 pad0[0xA8F8];
    s16 id;
    u8 padA8FA[0xA92E - 0xA8FA];
    s16 count;
} Ctx_b771_01E02C10;

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 rise;
    f32 pos[4];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 h;
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Obj_b771_01E02C10;

static s32 func_01E02C10_b771(Ctx_b771_01E02C10 *g, Obj_b771_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->size = func_0019A5C8() % 5 + 2;
        }
        if (o->kind == 1) {
            o->size = func_0019A5C8() % 5 + 6;
        }
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x50, 0xC0, 0x50);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        if (g->count < 280) {
            if (o->kind == 0) {
                o->h = func_0019A5C8() % 100 + 50;
                o->rise = func_0019A5C8() % 20 + 5;
            }
            if (o->kind == 1) {
                o->h = func_0019A5C8() % 30 + 10;
                o->rise = func_0019A5C8() % 3 + 10;
            }
        } else {
            if (o->kind == 0) {
                o->h = func_0019A5C8() % 50 + 30;
                o->rise = func_0019A5C8() % 10 + 5;
            }
            if (o->kind == 1) {
                o->h = func_0019A5C8() % 15 + 10;
                o->rise = func_0019A5C8() % 3 + 4;
            }
        }
        o->ang = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->life) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->id, o->pos);
    if (g->count < 220) {
        o->h += o->rise;
    } else if (g->count < 280) {
        o->h += o->rise * 2;
    }
    o->t++;
    return 0;
}

/* shape b771:01E02FD0, 120 insns: a glow that fades in by 0x40 over its first four ticks and, once the scene count
   passes 485, fades out by 11; size 10 x the scene scale on its first tick (stored twice), then 8 x the scale; its
   second colour blinks green (0x80, 0xFF, 0x80) on odd ticks, paler (0x80, 0xC0, 0x80) on even; rises 3 a tick
   after count 400 */

typedef struct {
    u8 pad0[0xA8E4];
    f32 scale;
    u8 padA8E8[0xA92E - 0xA8E8];
    s16 count;
} Ctx_b771_01E02FD0;

typedef struct {
    u8 pad0[0x34];
    f32 h;
    u8 pad38[0x10];
    f32 w;
    f32 size;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Obj_b771_01E02FD0;

static s32 func_01E02FD0_b771(Ctx_b771_01E02FD0 *g, Obj_b771_01E02FD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 10.0f * g->scale;
        o->size = 10.0f * g->scale;
        func_001076F0(o->col1, 0x80, 0x80, 0x80);
        func_001076F0(o->col0, 0x80, 0xFF, 0x80);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->h = 30.0f;
        o->mode = 2;
        o->col1[3] = 0;
    }
    if (o->t < 4) {
        if (o->col1[3] < 0x80) {
            o->col1[3] += 0x40;
        }
    } else if (g->count > 485) {
        if (o->col1[3] > 12) {
            o->col1[3] -= 11;
        } else {
            o->mode = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col0, 0x80, 0xFF, 0x80);
    } else {
        func_001076F0(o->col0, 0x80, 0xC0, 0x80);
    }
    o->size = 8.0f * g->scale;
    o->w = 8.0f * g->scale;
    if (g->count > 400) {
        o->h += 3.0f;
    }
    o->t++;
    return 0;
}

/* shape b771:01E031B0, 31 insns: variant of b402:01E02C50 (func_001F7170(3, ...), stops after 0x23 ticks) */

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b771_01E031B0;

typedef struct {
    f32 v;
} F1_b771_01E031B0;

extern F1_b771_01E031B0 D_01E04A00_b771;
extern F1_b771_01E031B0 D_01E04A08_b771;

static s32 func_01E031B0_b771(s32 arg0, Fx_b771_01E031B0 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b771_01E031B0 a;
    F1_b771_01E031B0 b;

    a = D_01E04A00_b771;
    b = D_01E04A08_b771;
    func_001F7170(3, 0, &a, &b, 0);
    o->tick++;
    if (o->tick >= 0x23) {
        o->mode = 0;
    }
    return 0;
}

/* shape b771:01E03230, 196 insns: b252:01E03CA0 cousin: green (0x10/0xC0/0x10), also places the scene point on joint
   0xA8F8, and holds while the scene clock (0xA92E) is under 485; b152:01E03400's full-screen overlay with a fixed inset, the bottom inset three times the height: one sprite over the
   whole screen, its texture window inset by the slot's width and height; alpha up by 10 to 0x80 while the clock runs, then
   down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b771_01E03230;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b771_01E03230 p;
    } v[2];
} Pkt_b771_01E03230;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b771_01E03230;

typedef struct {
    u8 pad0[0xA8D8];
    Pkt_b771_01E03230 *pkt;
    u8 padA8DC[0x1C];
    s16 joint;
    u8 padA8FA[0x34];
    s16 clock;
} Scene_b771_01E03230;

static s32 func_01E03230_b771(Scene_b771_01E03230 *s, Slot_b771_01E03230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 h;
    f32 w;

    w = o->w;
    h = o->h;
    w /= 10.0f;
    h /= 10.0f;
    if (o->state == 1) {
        o->c0[3] = 0;
        func_001076F0(o->c0, 0x10, 0xC0, 0x10);
        o->state = 2;
    }
    func_001F5620(func_001F53A0(), s->joint, v);
    func_001F5F90(func_001F53A0(), v);
    s->pkt->r = o->c0[0];
    s->pkt->g = o->c0[1];
    s->pkt->b = o->c0[2];
    s->pkt->a = o->c0[3];
    s->pkt->q = 1.0f;
    s->pkt->v[0].p.x = 0x6BF8;
    s->pkt->v[0].p.y = 0x71F8;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[0].p.f = 0;
    s->pkt->v[1].p.x = 0x93F8;
    s->pkt->v[1].p.y = 0x8DF8;
    s->pkt->v[1].p.z = 0xFFFFFF;
    s->pkt->v[1].p.f = 0;
    s->pkt->v[0].s = w / 1024.0f;
    s->pkt->v[0].t = h / 512.0f;
    s->pkt->v[1].s = (640.0f - w) / 1024.0f;
    s->pkt->v[1].t = (448.0f - 3.0f * h) / 512.0f;
    func_002075F0(s->pkt, 0, 0);
    if (s->clock < 485) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 10;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b771", func_01E03540_b771);

/* shape b771:01E03E00, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

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
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b771_01E03E00;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b771_01E03E00 slot[150];
    u8 padEnd[0xa8c4 - 0x2a0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padA8C8[0x5E];
    s16 val;
} Ctx_b771_01E03E00;

static s32 func_01E03E00_b771(Ctx_b771_01E03E00 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b771_01E03E00 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b771", func_01E03FA0_b771);

/* shape b771:01E04860, 84 insns: b183:01E029E0 family draw pass (scene handle from func_001F5380): sprite packet on the stack, then every live slot (150 of 0x70 bytes) whose handler is shape b771:01E03230 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b771_01E04860;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b771_01E04860 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b771_01E04860;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b771_01E04860;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b771_01E04860 slot[150];
    u8 padEnd[0xA8D4 - 0x2A0 - 150 * 0x70];
    s32 ctx;
    Pkt_b771_01E04860 *pkt;
} Scene_b771_01E04860;

static void func_01E04860_b771(Scene_b771_01E04860 *s) {
    extern void b771_01E03230(Scene_b771_01E04860 *, Slot_b771_01E04860 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F5380(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b771_01E04860 pkt __attribute__((aligned(8)));
    s32 i;

    s->pkt = &pkt;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F5380(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b771_01E03230) {
            b771_01E03230(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
