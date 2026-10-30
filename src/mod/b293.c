#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b293(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b293(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b293(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b293((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b293((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00F60_b293(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E012C0_b293(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

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

static void func_01E01700_b293(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
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

/* shape b293:01E01B10, 186 insns: b287:01E01D30 family event step: spawns b293:01E02780 and b293:01E02C10 at tick 1, b293:01E02D20 at 66; from 61 to 110 sits 15 below the mark (ctx+0xCAD0, tracking ctx+0xCB4C until 72) and 15 to one side, spawning b293:01E022F0 in slot 0 (and slot 1 from 68), b293:01E01E00 from 72, b293:01E02140 from 70 and b293:01E02B10 at 70; from 61 to 72 spawns b293:01E01FB0 at both hand points (ctx+0xCB44 / 0xCB48) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCAD0 - 0x260];
    Vec4f mark;
    u8 padCAE0[0xCB44 - 0xCAE0];
    s16 id0;
    u8 padCB46[2];
    s16 id1;
    u8 padCB4A[2];
    s16 id2;
    u8 padCB4E[0xCBB0 - 0xCB4E];
    s16 slot;
    u8 padCBB2[2];
    s16 back;
    u8 padCBB6[2];
    s16 timer;
} Ctx_b293_01E01B10;

static void func_01E01B10_b293(Ctx_b293_01E01B10 *g) {
    extern s32 b293_01E01E00(void);
    extern s32 b293_01E01FB0(void);
    extern s32 b293_01E02140(void);
    extern s32 b293_01E022F0(void);
    extern s32 b293_01E02780(void);
    extern s32 b293_01E02B10(void);
    extern s32 b293_01E02C10(void);
    extern s32 b293_01E02D20(void);
    extern void b293_01E03940(Ctx_b293_01E01B10 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    g->timer++;
    if (g->timer == 1) {
        b293_01E03940(g, b293_01E02780, 0);
    }
    if (g->timer == 1) {
        b293_01E03940(g, b293_01E02C10, 0);
    }
    if (g->timer == 66) {
        b293_01E03940(g, b293_01E02D20, 0);
    }
    if (g->timer >= 61 && g->timer < 111) {
        if (g->timer < 73) {
            func_001F5620(func_001F53A0(), g->id2, &g->mark);
        }
        g->pos = g->mark;
        g->pos.y -= 15.0f;
        if (g->back != 0) {
            g->pos.z -= 15.0f;
        } else {
            g->pos.z += 15.0f;
        }
        g->slot = 0;
        b293_01E03940(g, b293_01E022F0, 0);
        g->slot = 1;
        if (g->timer >= 68) {
            b293_01E03940(g, b293_01E022F0, 0);
        }
        if (g->timer >= 72) {
            b293_01E03940(g, b293_01E01E00, 0);
        }
        if (g->timer >= 70) {
            b293_01E03940(g, b293_01E02140, 0);
        }
        if (g->timer == 70) {
            b293_01E03940(g, b293_01E02B10, 0);
        }
    }
    if (g->timer >= 61 && g->timer < 73) {
        func_001F5620(func_001F53A0(), g->id0, &g->pos);
        b293_01E03940(g, b293_01E01FB0, 0);
        func_001F5620(func_001F53A0(), g->id1, &g->pos);
        b293_01E03940(g, b293_01E01FB0, 0);
    }
}

/* shape b293:01E01E00, 105 insns: b282:01E01C20 family spinning spark (random size 15..34, frame 0..2, angle 10..49, spin 26..45, held 3..5 ticks): in by 64 up to 0xC0, then out by 14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b293_01E01E00;

static s32 func_01E01E00_b293(s32 arg0, Obj_b293_01E01E00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 15;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 26;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b293:01E01FB0, 98 insns: a white spark (random size 10..29, frame 0..2, heading, angle 10..49, spin 16..35 and size 0..34 stored) held 3..5 ticks: in by 64 up to 0xC0, then out by 14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b293_01E01FB0;

static s32 func_01E01FB0_b293(s32 arg0, Obj_b293_01E01FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b293:01E02140, 105 insns: b282:01E01C20 family spinning spark (random size 160..209, frame 0..2, angle 10..49, spin 26..45, held 3..5 ticks): in by 64 up to 0xC0, then out by 14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b293_01E02140;

static s32 func_01E02140_b293(s32 arg0, Obj_b293_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 50 + 160;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 26;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b293:01E022F0 (B293_OBJ_MOVE_6_), 290 insns, 1 copy: a growing ring in one of three kinds, coloured by the
   scene's side (even/odd): kind 0 green-grey, kind 1 dark green, kind 2 red, each with its own life (8 or 10 ticks
   bright) and sizes; it grows by 35..42.9 a tick (the inner size 0.4 or 0.7 of it), kinds 1 and 2 also rise, and it
   fades by 5 until it stops */

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
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Fx_b293_01E022F0;

typedef struct {
    u8 pad0[0xCBB8];
    s16 side;
} Game_b293_01E022F0;

static s32 func_01E022F0_b293(Game_b293_01E022F0 *g, Fx_b293_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->kind == 0) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x80, 0xC0, 0x80);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0xB0, 0xFF, 0xB0);
                func_001076F0(o->col0, 0x30, 0x38, 0x38);
            }
            o->f6 = 8;
        }
        if (o->kind == 1) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x40, 0x80, 0x40);
                func_001076F0(o->col0, 0, 0, 0);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x60, 0xCF, 0x60);
                func_001076F0(o->col0, 0x30, 0x30, 0x30);
            }
            o->f34 = 10.0f;
            o->f6 = 10;
        }
        if (o->kind == 2) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0xC0, 0x80, 0x80);
                func_001076F0(o->col0, 0x10, 0x10, 0x10);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0xFF, 0xA0, 0xA0);
                func_001076F0(o->col0, 0x30, 0x30, 0x30);
            }
            o->f34 = 10.0f;
            o->f6 = 10;
        }
        if (o->kind == 0) {
            o->f5A = 10;
            o->f5C = 10;
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
    } else if (o->col1[3] > 6) {
        o->col1[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->f48 += o->f38;
        o->f4C = 0.4f * o->f48;
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

/* shape b293:01E02780, 225 insns: b746:01E03990's trail light in green (0x20/0xC0/0x20) feeding four 20-point
   trails from joints 0xCB44..0xCB4A until scene frame 75; alpha up until frame 74 */

typedef struct {
    f32 x, y, z, w;
} Pt_b293_01E02780;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b293_01E02780 a[20];
    Pt_b293_01E02780 b[20];
    Pt_b293_01E02780 c[20];
    Pt_b293_01E02780 d[20];
    u8 padB6D0[0x1474];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 padCB4C[0x6C];
    s16 frame;
} Scene_b293_01E02780;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b293_01E02780;

static s32 func_01E02780_b293(Scene_b293_01E02780 *g, Fx_b293_01E02780 *o) {
    extern void b293_01E00080(Pt_b293_01E02780 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    s16 k;
    s16 l;
    Pt_b293_01E02780 *q;

    func_001076F0(o->col, 0x20, 0xC0, 0x20);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->hE = 30;
        func_001F5620(func_001F53A0(), g->ja, p);
        q = g->a;
        for (i = 0; i < 19; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->b;
        for (j = 0; j < 19; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jc, p);
        q = g->c;
        for (k = 0; k < 19; k++) {
            q[k].x = p[0];
            q[k].y = p[1];
            q[k].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jd, p);
        q = g->d;
        for (l = 0; l < 19; l++) {
            q[l].x = p[0];
            q[l].y = p[1];
            q[l].z = p[2];
        }
        o->mode = 2;
    }
    if (g->frame < 74) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->frame < 75) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b293_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b293_01E00080(&g->b[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jc, p);
        b293_01E00080(&g->c[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jd, p);
        b293_01E00080(&g->d[19], 20, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

/* shape b293:01E02B10, 64 insns: b764:01E02A60 family ring (white/blue, height 200): in by 48 up to 0xC0 while the scene value is under 115, then out by 15 and ends */

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
} Obj_b293_01E02B10;

typedef struct {
    u8 pad[0xCBB8];
    s16 val;
} Game_b293_01E02B10;

static s32 func_01E02B10_b293(Game_b293_01E02B10 *g, Obj_b293_01E02B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f4C = 200.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xC0);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->val < 115) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b287:01E02DA0, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x97, floor 0x30, state at 0xCB10 below 0x1E */

typedef struct {
    u8 pad[0xCB10];
    s32 state;
} Game_b287_01E02DA0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b287_01E02DA0;

static s32 func_01E02C10_b293(Game_b287_01E02DA0 *g, Fade_b287_01E02DA0 *o) {
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

/* shape b293:01E02D20, 179 insns: b702:01E02AD0's veil (0x80/0x88/0x80, 0x84/0x94/0x84 on scene frame 68) on the scene
   frame at 0xCBB8: from frame 66 it zooms by 0.6 to 4 and its alpha also climbs by 12 to 0x60; it fades from frame 135 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b293_01E02D20;

typedef struct {
    f32 s, t;
    Xyz_b293_01E02D20 p;
} Tv_b293_01E02D20;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b293_01E02D20 v[2];
    u8 tail[0x20];
} Tex_b293_01E02D20;

typedef struct {
    u8 pad0[0xCBB8];
    s16 count;
} Ctx_b293_01E02D20;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b293_01E02D20;

static s32 func_01E02D20_b293(Ctx_b293_01E02D20 *g, Fx_b293_01E02D20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b293_01E02D20 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x88, 0x80);
        o->mode = 2;
    }
    if (g->count == 68) {
        func_001076F0(o->col, 0x84, 0x94, 0x84);
    }
    ((Tex_b293_01E02D20 *)(s32)&pk)->flags = 0x26;
    ((Tex_b293_01E02D20 *)(s32)&pk)->size = 5;
    ((Tex_b293_01E02D20 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b293_01E02D20 *)(s32)&pk)->pad4 = 0;
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
    if (g->count > 65) {
        if (o->f48 < 4.0f) {
            o->f48 += 0.6f;
        }
    }
    if (g->count < 135) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
        if (g->count > 65) {
            if (o->col[3] < 0x60) {
                o->col[3] += 12;
            }
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

static s32 func_01E02FF0_b293(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b293", func_01E03000_b293);

/* shape b293:01E03940, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b293_01E03940 {
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
} Slot_b293_01E03940;

typedef struct Obj_b293_01E03940 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b293_01E03940 slots[0x190];
    u8 padB[0xcb14 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xcbb0 - 0xcb14 - 4];
    s16 fB2B0;
} Obj_b293_01E03940;

static s32 func_01E03940_b293(Obj_b293_01E03940 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b293_01E03940 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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

/* shape b293:01E03AD0 (B293KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b293_01E03AD0 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b293_01E03AD0;

typedef struct {
    Rgbaq_b293_01E03AD0 c;
    u64 xyz;
} Vtx_b293_01E03AD0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b293_01E03AD0 v[4];
    u8 tail[0x40];
} Pkt_b293_01E03AD0;

typedef struct {
    u8 r, g, b, a;
} C4_b293_01E03AD0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b293_01E03AD0 col;
} Rib_b293_01E03AD0;

static inline u8 b293_01E03AD0_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E03AD0_b293(void *o, Rib_b293_01E03AD0 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b293_01E03AD0 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b293_01E03AD0 pkt __attribute__((aligned(8)));
    C4_b293_01E03AD0 c0;
    C4_b293_01E03AD0 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b293_01E03AD0 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b293_01E03AD0 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    step = s->col.a;
    step /= (s16)(n * 3);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - step > 0) {
                c1.a = b293_01E03AD0_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E012C0_b293(pp, 0, t);
                B[0] = func_01E012C0_b293(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E012C0_b293(pp, 0, t);
                B[1] = func_01E012C0_b293(pq, 0, t);
            } else {
                A[0] = func_01E012C0_b293(a4, 0, t);
                B[0] = func_01E012C0_b293(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E012C0_b293(a4, 0, t);
                B[1] = func_01E012C0_b293(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b293", func_01E04080_b293);
