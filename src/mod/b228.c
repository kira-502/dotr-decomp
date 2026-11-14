#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b228(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b228(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b082_01E00920;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0x0E];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b082_01E00920;

static void func_01E009B0_b228(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
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
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    i = 0;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
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
} Obj_b020_01E00920;

extern void b228_01E00110(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00E10_b228(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b228_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
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

static void func_01E01360_b228(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b228((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b228((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b228:01E01910, 148 insns: the b228 module's event step: counts ticks; keeps its point on the tracked point (ctx+0xBCBC) jittered by -20..19 on each axis and pushed 20 along z by the scene flag; every other tick up to 100 spawns b228:01E01B60 and b228:01E02270 with a slot number cycling 0..119 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xBCBC - 0x25C];
    s16 id;
    u8 padBCBE[0xBCEA - 0xBCBE];
    s16 slot;
    s16 next;
    s16 flag;
    u8 padBCF0[2];
    s16 timer;
} Ctx_b228_01E01910;

static void func_01E01910_b228(Ctx_b228_01E01910 *g) {
    extern s32 b228_01E01B60(void);
    extern s32 b228_01E02270(void);
    extern void b228_01E02F80(Ctx_b228_01E01910 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    s16 i;
    s16 n;

    g->timer++;
    func_001F5620(func_001F53A0(), g->id, g->pos);
    g->pos[0] += func_0019A5C8() % 40 - 20;
    g->pos[1] += func_0019A5C8() % 40 - 20;
    g->pos[2] += func_0019A5C8() % 40 - 20;
    if (g->flag != 0) {
        g->pos[2] -= 20.0f;
    } else {
        g->pos[2] += 20.0f;
    }
    if (g->timer > 0 && g->timer < 101) {
        if (g->timer % 2 == 1) {
            if (g->timer < 100) {
                n = 1;
            } else {
                n = 1;
            }
            for (i = 0; i < n; i++) {
                g->slot = g->next;
                b228_01E02F80(g, b228_01E01B60, 0);
                b228_01E02F80(g, b228_01E02270, 0);
                g->next++;
                if (g->next >= 120) {
                    g->next = 0;
                }
            }
        }
    }
}

/* shape b228:01E01B60, 224 insns: a 7x7 white spark that parks its position in scene slot k (0xB4F0 + 16 k): frame 4;
   both alphas up by 42 to 0xAA for 110 ticks, then the first down by 14 (twice a tick); flickers white/grey, at tick
   115 spawns three 0x1E01EE0 and two 0x1E02070 at the slot, then flickers light/dark grey; turns 5 until tick 83 and
   from tick 84 the slot drifts 5 a tick in z by the scene side (0xBCEE) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB4F0 - 0x260];
    Vec4f pt[1];
    u8 padB500[0xBCEE - 0xB500];
    s16 side;
} Ctx_b228_01E01B60;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[0x24];
    s16 k;
    u8 pad52[2];
    s16 tick;
    s16 frame;
    s16 mode;
    s16 turn;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b228_01E01B60;

static s32 func_01E01B60_b228(Ctx_b228_01E01B60 *g, Fx_b228_01E01B60 *o) {
    extern void b228_01E01EE0(void);
    extern void b228_01E02070(void);
    extern s32 b228_01E02F80(Ctx_b228_01E01B60 *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 7;
        o->h = 7;
        o->frame = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        g->pt[o->k].x = o->x;
        g->pt[o->k].y = o->y;
        g->pt[o->k].z = o->z;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 110) {
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
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    func_00205C40((s32)o->rot);
    if (o->tick == 115) {
        g->pos.x = g->pt[o->k].x;
        g->pos.y = g->pt[o->k].y;
        g->pos.z = g->pt[o->k].z;
        b228_01E02F80(g, (s32)b228_01E01EE0, 0);
        b228_01E02F80(g, (s32)b228_01E01EE0, 0);
        b228_01E02F80(g, (s32)b228_01E01EE0, 0);
        b228_01E02F80(g, (s32)b228_01E02070, 0);
        b228_01E02F80(g, (s32)b228_01E02070, 0);
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->tick < 83) {
        o->turn += 5;
    }
    o->tick++;
    if (o->tick > 83) {
        if (g->side != 0) {
            g->pt[o->k].z -= 5.0f;
        } else {
            g->pt[o->k].z += 5.0f;
        }
    }
    return 0;
}

/* shape b111:01E02160, 100 insns: spark update, a variant of b018:01E02950 (on spawn: random kind, white
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
} Spark_b193_01E02780;

static s32 func_01E01EE0_b228(s32 unused, Spark_b193_01E02780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 40.0f;
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

/* shape b082:01E02050, 127 insns, 7 copies: spark update, a variant of b111:01E02160 / b018:01E02950 (random size,
   kind, yellow colour, three random seeds, height, angle, speed, spin and lifetime on spawn; fade out
   after the lifetime; a frame counter and the height move every update). */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 f20;
    s32 f24;
    s32 f28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 pos;
    s16 f52;
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Spark_b082_01E02050;

static s32 func_01E02070_b228(s32 unused, Spark_b082_01E02050 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0);
        o->f20 = func_0019A5C8() % 0xFFFF;
        o->f24 = func_0019A5C8() % 0xFFFF;
        o->f28 = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->pos = func_0019A5C8() % 150 + 150;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 8 + 1;
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
    o->f52++;
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b228:01E02270, 143 insns: b149:01E01ED0's track trail, h56 4, turning 5 a tick for 83 ticks, flickering grey */

typedef struct {
    Vec4f p[15];
} Track_b228_01E02270;

typedef struct {
    u8 pad0[0x4470];
    Track_b228_01E02270 track[0x50];
    u8 pad[0xB4F0 - 0x4470 - 0x50 * 0xF0];
    Vec4f head[1];
} World_b228_01E02270;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 h8;
    u8 padA[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Trail_b228_01E02270;

static s32 func_01E02270_b228(World_b228_01E02270 *w, Trail_b228_01E02270 *o) {
    extern void b228_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        src = &w->head[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 15; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->frame = 2;
        o->c0[3] = 0;
        o->h8 = 0;
        o->h56 = 4;
        o->size = 4.0f;
        o->state = 2;
    }
    if (o->t < 0x6E) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
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
    if (o->t < 0x53) {
        o->h5A += 5;
    }
    if (o->t < 0x75) {
        b228_01E00080(&w->track[o->idx].p[14], 15, 0, &w->head[o->idx]);
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    }
    if (o->t != 0) {
        if (o->frame < 4) {
            o->frame++;
        }
    }
    o->t++;
    return 0;
}

/* shape b149:01E020F0, 176 insns: a glow whose kind (f50) picks its look: kinds 0/1 are grey with an orange second
   colour, flickering, brightening for 12 ticks; kind 1 also grows to 400 by 15; kind 2 starts at 840, white with a
   brown second colour, brightens by 0x20 for 13 ticks then fades by 9; kinds 0/1 fade by 15 once the game value
   at 0xBCF2 passes 0x140; the position's first word advances 0x4000 each tick */

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
    s16 kind;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b149_01E020F0;

typedef struct {
    u8 pad[0xBCF2];
    s16 v;
} Game_b149_01E020F0;

static s32 func_01E024B0_b228(Game_b149_01E020F0 *g, Fx_b149_01E020F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        if (o->kind == 2) {
            o->f48 = 840.0f;
        }
        if (o->kind < 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0xF0, 0x80, 0x10);
        } else {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x40, 0x10);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind < 2) {
        if (o->tick < 12) {
            o->col[3] += 0x10;
        }
    }
    if (o->kind == 2) {
        if (o->tick < 13) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x20;
            }
        } else if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind < 2) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->col2, 0x80, 8, 0x40);
        }
    }
    if (o->kind == 1) {
        if (o->f48 < 400.0f) {
            o->f48 += 15.0f;
        }
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_00205C40(o->pos);
    o->pos[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b228:01E02770 (b228), 515 insns, 1 copy: the scene manager (b149:01E023B0 form): set up the scene (textures,
   jitter tables), then step the 150 effect slots and draw five kinds (a spark at its parked slot point bobbing on a
   sine, a shaken-part sprite, a band sprite, a rising part at a table point, a ring at a camera position); returns
   cue codes by frame */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[4];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 sel;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b228_01E02770;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xE4];
} Pt_b228_01E02770;

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
    s16 rm[8];
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
    Fx_b228_01E02770 fx[150];
    u8 pad4440[0x30];
    Pt_b228_01E02770 pt[120];
    Vec4f spot[120];
    s32 tex2[2];
    u8 padBC78[0x18];
    s32 count;
    u8 padBC94[8];
    s32 ot;
    u8 padBCA0[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padBCC2[8];
    s16 cam;
    u8 padBCCC[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b228_01E02770;

static s32 func_01E02770_b228(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E01910_b228();
    extern void func_01E01360_b228();
    extern void func_01E00E10_b228();
    extern void func_01E009B0_b228();
    extern s32 func_01E01B60_b228();
    extern s32 func_01E01EE0_b228();
    extern s32 func_01E02070_b228();
    extern s32 func_01E02270_b228();
    extern s32 func_01E024B0_b228();
    extern void b228_01E03110();
    extern void b228_01E03C50();
    Scene_b228_01E02770 *g = (Scene_b228_01E02770 *)arg0;
    s32 k;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xC060);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 250;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 14; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        for (k = 0; k < 2; k++) {
            g->tex2[k] = func_00202BF0(5, k);
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
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01910_b228(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01B60_b228) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->rm[0] = 1;
                g->rm[1] = 1;
                g->rm[2] = 0x3F;
                g->rm[3] = 0x3F;
                g->tex88 = g->tex2[1];
                g->hBE = 0;
                v.x = g->spot[g->fx[i].sel].x;
                v.y = g->spot[g->fx[i].sel].y + 3.0f * func_00108030(g->crd, g->fx[i].h5A, 1);
                v.z = g->spot[g->fx[i].sel].z;
                b228_01E03C50(g, &g->fx[i], 0x20, v);
            }
            if (g->fx[i].fn == func_01E01EE0_b228) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[0];
                g->hB8 = 6;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00E10_b228(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E02070_b228) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E01360_b228(g, &g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[i].fn == func_01E02270_b228) {
                g->tex88 = g->tex2[0];
                func_00106080(rm4, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->rm[3] >>= 1;
                g->rm[1] += g->rm[3];
                g->rm[3] = 1;
                func_001F5F90(func_001F53A0(), &v);
                g->px = 0.0f;
                g->py = 3.0f * func_00108030(g->crd, g->fx[i].h5A, 1);
                g->pz = 0.0f;
                g->hBE = 3;
                if (g->fx[i].h54 > 83) {
                    b228_01E03110(g, &g->fx[i], &g->pt[g->fx[i].sel], 0);
                }
            }
            if (g->fx[i].fn == func_01E024B0_b228) {
                if (g->fx[i].sel == 0) {
                    func_001F5620(func_001F53A0(), g->jA, &v);
                }
                if (g->fx[i].sel == 1) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                if (g->fx[i].sel == 2) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                func_01E009B0_b228(g, &g->fx[i], 0x21, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 100) {
        return 1;
    }
    if (g->frame == 235) {
        return 4;
    }
    if (g->frame == 225) {
        return 3;
    }
    if (g->frame > 110 && g->frame < 220) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b149:01E02BA0, 98 insns, 3 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b149_01E02BA0 {
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
} Slot_b149_01E02BA0;

typedef struct Obj_b149_01E02BA0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b149_01E02BA0 slots[0x96];
    u8 padB[0xbc94 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xbcea - 0xbc94 - 4];
    s16 fB2B0;
} Obj_b149_01E02BA0;

static s32 func_01E02F80_b228(Obj_b149_01E02BA0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b149_01E02BA0 *s = NULL;
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

/* shape b149:01E02D30 (B149PAINT_RAIN12), 717 insns, 4 copies (-O3,p): b411:01E036C0's spline beam, alpha step / (3n)
   and width step / (8n) */

typedef struct {
    f32 x, y, z, w;
} Vec_b149_01E02D30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b149_01E02D30;

typedef struct {
    u8 r, g, b, a;
} Col_b149_01E02D30;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b149_01E02D30;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b149_01E02D30 c;
        u64 st;
        Xyz_b149_01E02D30 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b149_01E02D30;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b149_01E02D30;

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
    Col_b149_01E02D30 col0;
    Col_b149_01E02D30 col1;
} Beam_b149_01E02D30;

static inline Vec_b149_01E02D30 spline_b847_01E00E60(Vec_b149_01E02D30 *p, s32 type, f32 t) {
    Vec_b149_01E02D30 r;
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

#pragma optimization_level 3

/* pts aligned: its spill slot, needed for the match */
static void func_01E03110_b228(Ctx_b149_01E02D30 *c, Beam_b149_01E02D30 *an, Vec_b149_01E02D30 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b149_01E02D30 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b149_01E02D30 ab[2];
    Vec_b149_01E02D30 ctrl[4];
    Vec_b149_01E02D30 prev;
    Vec_b149_01E02D30 q[4];
    Vec_b149_01E02D30 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b149_01E02D30 pkt __attribute__((aligned(8)));
    Col_b149_01E02D30 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b149_01E02D30 *p;
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
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (8.0f * n);
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

#pragma optimization_level reset

/* shape b139:01E03820: sibling of b016:01E00ED0 (one sprite quad, drawn twice). Needs func_01E00110_b228 in the
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

static void func_01E03C50_b228(Obj_b139_01E03820 *obj, Cam_b139_01E03820 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b228((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
