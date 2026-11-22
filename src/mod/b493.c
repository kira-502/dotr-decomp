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

static void func_01E00080_b493(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b493(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
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

extern void b493_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00D80_b493(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b493_01E00080(p, o->b94, o->hC0);
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

static void func_01E012D0_b493(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b493((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b493((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b108_01E009A0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0x0A];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b108_01E009A0;

static void func_01E01880_b493(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b493 in the
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

static void func_01E01CD0_b493(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b493((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b493:01E01F90, 156 insns: b228:01E01910 family event step: counts ticks; at 100 spawns b493:01E03460 for slots 0 and 1; keeps its point on the tracked point (ctx+0xBCBC) jittered -2..1 on each axis; every other tick from 63 to 100 spawns b493:01E02200 with a slot number cycling 0..119 and a random kind 0..4 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xBCBC - 0x25C];
    s16 id;
    u8 padBCBE[0xBCEA - 0xBCBE];
    s16 slot;
    s16 kind;
    s16 next;
    u8 padBCF0[4];
    s16 timer;
} Ctx_b493_01E01F90;

static void func_01E01F90_b493(Ctx_b493_01E01F90 *g) {
    extern s32 b493_01E02200(void);
    extern s32 b493_01E03460(void);
    extern void b493_01E04150(Ctx_b493_01E01F90 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    s16 i;
    s16 n;

    g->timer++;
    if (g->timer == 100) {
        g->slot = 0;
        b493_01E04150(g, b493_01E03460, 0);
        g->slot = 1;
        b493_01E04150(g, b493_01E03460, 0);
    }
    func_001F5620(func_001F53A0(), g->id, g->pos);
    g->pos[0] += func_0019A5C8() % 4 - 2;
    g->pos[1] += func_0019A5C8() % 4 - 2;
    g->pos[2] += func_0019A5C8() % 4 - 2;
    if (g->timer >= 63 && g->timer < 101) {
        if (g->timer % 2 == 1) {
            if (g->timer < 100) {
                n = 1;
            } else {
                n = 1;
            }
            for (i = 0; i < n; i++) {
                g->slot = g->next;
                g->kind = func_0019A5C8() % 5;
                b493_01E04150(g, b493_01E02200, 0);
                g->next++;
                if (g->next >= 120) {
                    g->next = 0;
                }
            }
        }
    }
}

/* shape b493:01E02200 (B493_OBJ_MOVE_2_), 590 insns, 1 copy: a kind-coloured flare (red, green, blue, yellow, purple)
   on point slot of the scene's 120-point track: on start size 2, drift -8..7/35; before tick 100 of the scene it
   follows tracked joint 0/1 by slot parity, jittered; flashes by tick parity; at tick 88 spawns five 01E02B40, two
   01E02DF0 and one 01E03310 there; then drifts in z by the scene side and grows */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xB4F0 - 0x25C];
    f32 pts[120][4];
    u8 padBCF0[0xBCBC - (0xB4F0 + 120 * 16)];
    s16 id0;
    s16 id1;
    u8 padBCC0[0xBCEC - 0xBCC0];
    s16 kind;
    u8 padBCEE[2];
    s16 side;
    u8 padBCF2[2];
    s16 timer;
} Ctx_b493_01E02200;

typedef struct {
    u8 pad00[0x10];
    f32 p[4];
    u8 v20[0x10];
    f32 vx;
    f32 vy;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 slot;
    s16 kind;
    s16 tick;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
} Obj_b493_01E02200;

static s32 func_01E02200_b493(Ctx_b493_01E02200 *g, Obj_b493_01E02200 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00205C40(void *);
    extern s32 b493_01E02B40(void);
    extern s32 b493_01E02DF0(void);
    extern s32 b493_01E03310(void);
    extern void b493_01E04150(Ctx_b493_01E02200 *, s32 (*)(void), s32);
    f32 x;
    f32 y;

    if (o->mode == 1) {
        o->size = 2.0f;
        if (o->kind == 0) {
            func_001076F0(o->c60, 0x80, 8, 8);
            func_001076F0(o->c64, 0x80, 8, 8);
        } else if (o->kind == 1) {
            func_001076F0(o->c60, 8, 0x80, 8);
            func_001076F0(o->c64, 8, 0x80, 8);
        } else if (o->kind == 2) {
            func_001076F0(o->c60, 8, 8, 0x80);
            func_001076F0(o->c64, 8, 8, 0x80);
        } else if (o->kind == 3) {
            func_001076F0(o->c60, 0x80, 0x80, 8);
            func_001076F0(o->c64, 0x80, 0x80, 8);
        } else if (o->kind == 4) {
            func_001076F0(o->c60, 0x40, 8, 0x80);
            func_001076F0(o->c64, 0x40, 8, 0x80);
        }
        o->vx = func_0019A5C8() % 16 - 8;
        o->vy = func_0019A5C8() % 16 - 8;
        o->vx = o->vx / 35.0f;
        o->vy = o->vy / 35.0f;
        g->pts[o->slot][0] = o->p[0];
        g->pts[o->slot][1] = o->p[1];
        g->pts[o->slot][2] = o->p[2];
        o->mode = 2;
        o->c64[3] = 0;
    }
    if (g->timer < 100) {
        if (o->slot % 2 == 1) {
            func_001F5620(func_001F53A0(), g->id0, o->p);
        } else {
            func_001F5620(func_001F53A0(), g->id1, o->p);
        }
        x = func_0019A5C8() % 20 - 10;
        y = func_0019A5C8() % 20;
        x /= 20.0f;
        y /= 20.0f;
        g->pts[o->slot][0] = o->p[0] + x;
        g->pts[o->slot][1] = o->p[1] + y;
        g->pts[o->slot][2] = o->p[2];
    } else {
        g->pts[o->slot][1] += o->vy / 2.0f;
        g->pts[o->slot][0] += o->vx / 2.0f;
    }
    if (o->tick < 95) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 42;
        }
        if (o->c64[3] < 0x80) {
            o->c64[3] += 42;
        }
    } else {
        if (o->c60[3] > 25) {
            o->c60[3] -= 24;
        } else {
            o->mode = 0;
        }
        if (o->c60[3] > 25) {
            o->c60[3] -= 24;
        }
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->c60, 0xFF, 0x40, 0x40);
        } else {
            func_001076F0(o->c60, 0x80, 8, 8);
        }
    } else if (o->kind == 1) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->c60, 8, 0xFF, 8);
        } else {
            func_001076F0(o->c60, 0x40, 0x80, 0x40);
        }
    } else if (o->kind == 2) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->c60, 0x40, 0x40, 0xFF);
        } else {
            func_001076F0(o->c60, 8, 8, 0x80);
        }
    } else if (o->kind == 3) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->c60, 0xFF, 0xFF, 0x40);
        } else {
            func_001076F0(o->c60, 0x80, 0x80, 8);
        }
    } else if (o->kind == 4) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->c60, 0x80, 0x10, 0xFF);
        } else {
            func_001076F0(o->c60, 0x40, 8, 0x80);
        }
    }
    func_00205C40(o->v20);
    if (o->tick == 88) {
        g->pos[0] = g->pts[o->slot][0];
        g->pos[1] = g->pts[o->slot][1];
        g->pos[2] = g->pts[o->slot][2];
        g->kind = o->kind;
        b493_01E04150(g, b493_01E02B40, 0);
        b493_01E04150(g, b493_01E02B40, 0);
        b493_01E04150(g, b493_01E02B40, 0);
        b493_01E04150(g, b493_01E02B40, 0);
        b493_01E04150(g, b493_01E02B40, 0);
        b493_01E04150(g, b493_01E02DF0, 0);
        b493_01E04150(g, b493_01E02DF0, 0);
        b493_01E04150(g, b493_01E03310, 0);
    }
    if (g->timer >= 99 && g->timer < 131) {
        if (g->side) {
            g->pts[o->slot][2] -= 0.1f;
        } else {
            g->pts[o->slot][2] += 0.1f;
        }
    }
    o->tick++;
    if (o->tick > 40) {
        if (g->side) {
            g->pts[o->slot][2] -= 3.6f;
        } else {
            g->pts[o->slot][2] += 3.6f;
        }
        o->size += 0.5f;
    }
    if (g->timer > 100) {
        if (o->size < 20.0f && o->tick < 40) {
            o->size += 0.4f;
        }
    }
    return 0;
}

/* shape b493:01E02B40, 170 insns: b479:01E01EB0 variant: size 10, frame 0..3, both colours by kind (red, green, blue,
   yellow, purple), height 10..59 rising 20..59, alpha 0x80 for its fade-in, then down by 8 */

typedef struct {
    u8 pad0000[0x6DEC];
    s16 h6DEC;
} Mgr_b493_01E02B40;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 v10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b493_01E02B40;

static s32 func_01E02B40_b493(Mgr_b493_01E02B40 *m, Obj_b493_01E02B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 4;
        if (o->h52 == 0) {
            func_001076F0(o->c60, 0x80, 8, 8);
            func_001076F0(o->c64, 0x80, 8, 8);
        } else if (o->h52 == 1) {
            func_001076F0(o->c60, 8, 0x80, 8);
            func_001076F0(o->c64, 8, 0x80, 8);
        } else if (o->h52 == 2) {
            func_001076F0(o->c60, 8, 8, 0x80);
            func_001076F0(o->c64, 8, 8, 0x80);
        } else if (o->h52 == 3) {
            func_001076F0(o->c60, 0x80, 0x80, 8);
            func_001076F0(o->c64, 0x80, 0x80, 8);
        } else if (o->h52 == 4) {
            func_001076F0(o->c60, 0x40, 8, 0x80);
            func_001076F0(o->c64, 0x40, 8, 0x80);
        }
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->hE = func_0019A5C8() % 40 + 20;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape b493:01E02DF0, 195 insns: b493:01E02B40's kind-coloured spark (red, green, blue, yellow, purple from h52),
   size 13..22, frame 0..3, random turn, h52 then counts ticks; height 170..319 rising 1..3, h8 1..8, held 2..4 ticks
   at alpha 0x60, then down by 11 */

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
} Obj_b493_01E02DF0;

static s32 func_01E02DF0_b493(s32 arg0, Obj_b493_01E02DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 10 + 13;
        o->h56 = func_0019A5C8() % 4;
        if (o->h52 == 0) {
            func_001076F0(o->c60, 0x80, 8, 8);
            func_001076F0(o->c64, 0x80, 8, 8);
        } else if (o->h52 == 1) {
            func_001076F0(o->c60, 8, 0x80, 8);
            func_001076F0(o->c64, 8, 0x80, 8);
        } else if (o->h52 == 2) {
            func_001076F0(o->c60, 8, 8, 0x80);
            func_001076F0(o->c64, 8, 8, 0x80);
        } else if (o->h52 == 3) {
            func_001076F0(o->c60, 0x80, 0x80, 8);
            func_001076F0(o->c64, 0x80, 0x80, 8);
        } else if (o->h52 == 4) {
            func_001076F0(o->c60, 0x40, 8, 0x80);
            func_001076F0(o->c64, 0x40, 8, 0x80);
        }
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h52 = 1;
        o->h50 = func_0019A5C8() % 150 + 170;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0x60;
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h52++;
    o->h50 += o->hE;
    o->h54++;
    return 0;
}

/* shape b493:01E03100, 129 insns: b163:01E025A0 family spinning glow (size 100 growing 1, light grey 0xCF over one of five tints picked by f52: red, green, blue, yellow, purple): alpha up by 64 for 4 ticks, then down by 9; spins 0x4000 per tick */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[6];
    s16 tint;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b493_01E03100;

static s32 func_01E03100_b493(s32 arg0, Fx_b493_01E03100 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 100.0f;
        if (o->tint == 0) {
            func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
            func_001076F0(o->col2, 0x80, 8, 8);
        } else if (o->tint == 1) {
            func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
            func_001076F0(o->col2, 8, 0x80, 8);
        } else if (o->tint == 2) {
            func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
            func_001076F0(o->col2, 8, 8, 0x80);
        } else if (o->tint == 3) {
            func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
            func_001076F0(o->col2, 0x80, 0x80, 8);
        } else if (o->tint == 4) {
            func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
            func_001076F0(o->col2, 0x40, 8, 0x80);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 1.0f;
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b493:01E03310, 80 insns: a growing grey glow: on start f8/fA 80, f48 5, f56 0; alpha grows by 0x60 (below
   0xC0) for 5 ticks, then fades out by 9 and stops; from tick 2 f56 steps up every other tick (max 5); f8/fA grow
   by 1 every tick after the first */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    u8 padC[0x14];
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
} Fx_b493_01E03310;

static s32 func_01E03310_b493(s32 arg0, Fx_b493_01E03310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 80;
        o->fA = 80;
        o->f48 = 5.0f;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick > 1 && o->tick % 2 == 1) {
        o->f56++;
    }
    if (o->f56 > 5) {
        o->f56 = 5;
    }
    if (o->tick != 0) {
        o->f8++;
        o->fA++;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03450_b493(void) {
    return 0;
}

/* shape b493:01E03460, 98 insns: a white-grey flicker glow on a model joint (b743:01E033E0 shape): size 35, random angle;
   alpha up by 16 until frame 63, then down by 9 until it ends; follows the joint; second colour flickers; spins a quarter turn */

typedef struct {
    u8 pad0[0xBCBC];
    s16 joint[1];
} Game_b493_01E03460;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 jidx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b493_01E03460;

static s32 func_01E03460_b493(Game_b493_01E03460 *g, Obj_b493_01E03460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 35.0f;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0x60, 0x60, 0x60);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x3F) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x10;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    func_001F5620(func_001F53A0(), g->joint[o->jidx], &o->pos);
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0x70, 0x70, 0x70);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b493:01E035F0, 176 insns: variant of b149:01E020F0 (game value at 0xBCF4): a glow whose kind (f50) picks its look: kinds 0/1 are grey with an orange second
   colour, flickering, brightening for 12 ticks; kind 1 also grows to 400 by 15; kind 2 starts at 840, white with a
   brown second colour, brightens by 0x20 for 13 ticks then fades by 9; kinds 0/1 fade by 15 once the game value
   at 0xBCF4 passes 0x140; the position's first word advances 0x4000 each tick */

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
} Fx_b493_01E035F0;

typedef struct {
    u8 pad[0xBCF4];
    s16 v;
} Game_b493_01E035F0;

static s32 func_01E035F0_b493(Game_b493_01E035F0 *g, Fx_b493_01E035F0 *o) {
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

/* shape b493:01E038B0 (b493), 551 insns, 1 copy: b228:01E02770's scene manager form: setup (clear 0xC070, four
   func_001F5560 ids, texture slots, jitter tables), else run the 150 slot handlers and draw eight slot kinds; returns
   by scene frame */

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
} Fx_b493_01E038B0;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xE4];
} Pt_b493_01E038B0;

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
    Fx_b493_01E038B0 fx[150];
    u8 pad4440[0x30];
    Pt_b493_01E038B0 pt[120];
    Vec4f spot[120];
    s32 tex2[1];
    u8 padBC74[0x1C];
    s32 count;
    u8 padBC94[8];
    s32 ot;
    u8 padBCA0[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padBCC2[8];
    s16 cam;
    u8 padBCCC[0x24];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padBEF6[2];
    u8 crd[0x178];
} Scene_b493_01E038B0;

static s32 func_01E038B0_b493(s32 arg0, s32 id) {
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
    extern s32 func_01E02200_b493();
    extern void b493_01E01F90();
    extern void b493_01E00920();
    extern void b493_01E00D80();
    extern void b493_01E012D0();
    extern void b493_01E01880();
    extern void b493_01E01CD0();
    extern void b493_01E042F0();
    extern void b493_01E04E30();
    Scene_b493_01E038B0 *g = (Scene_b493_01E038B0 *)arg0;
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
        func_00195108(g, 0xC070);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 230;
        g->jA = func_001F5560(func_001F53A0(), 0x10, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x39, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 14; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (k = 0; k < 1; k++) {
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
    b493_01E01F90(g, 0);
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
            if (g->fx[i].fn == (s32 (*)())func_01E02200_b493) {
                func_00106080(rm, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex[15];
                g->hBE = 0;
                v.x = g->spot[g->fx[i].sel].x;
                v.y = g->spot[g->fx[i].sel].y;
                v.z = g->spot[g->fx[i].sel].z;
                b493_01E04E30(g, &g->fx[i], 0x20, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02B40_b493) {
                func_00106080(rm2, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex[15];
                g->hB8 = 6;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                b493_01E00D80(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02DF0_b493) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 1;
                b493_01E012D0(g, &g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E03100_b493) {
                v = g->fx[i].pos;
                b493_01E00920(g, &g->fx[i], 0x21, v);
                b493_01E00920(g, &g->fx[i], 0x21, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E03310_b493) {
                g->tex88 = g->tex2[0];
                g->rm[0] = g->fx[i].h56 << 6;
                g->rm[1] = 0;
                g->rm[2] = 0x3F;
                g->rm[3] = 0x3F;
                g->hBE = 0;
                b493_01E01CD0(g, &g->fx[i], 0x21, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E03450_b493) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x97, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->rm[3] >>= 1;
                g->rm[1] += g->rm[3];
                func_001F5F90(func_001F53A0(), &v);
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
                g->hBE = 1;
                if (g->fx[i].h54 > 83) {
                    b493_01E042F0(g, &g->fx[i], &g->pt[g->fx[i].sel], 0);
                }
            }
            if (g->fx[i].fn == (s32 (*)())func_01E03460_b493) {
                v = g->fx[i].pos;
                b493_01E01880(g, &g->fx[i], 0x21, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E035F0_b493) {
                if (g->fx[i].sel == 0) {
                    func_001F5620(func_001F53A0(), g->jA, &v);
                }
                if (g->fx[i].sel == 1) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                if (g->fx[i].sel == 2) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                b493_01E00920(g, &g->fx[i], 0x21, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 150) {
        return 1;
    }
    if (g->frame == 220) {
        return 4;
    }
    if (g->frame == 205) {
        return 2;
    }
    if (g->frame > 160 && g->frame < 200) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b493:01E04150, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two scene values and both arguments; returns 1 when it got one */

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
} Obj_b493_01E04150;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b493_01E04150 slot[150];
    u8 padEnd[0xbc94 - 0x2a0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padBC98[0x52];
    s16 v0;
    s16 v1;
} Ctx_b493_01E04150;

static s32 func_01E04150_b493(Ctx_b493_01E04150 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b493_01E04150 *s;

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
        s->h50 = ctx->v0;
        s->h52 = ctx->v1;
        s->w40 = arg2;
        s->w44 = arg1;
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
static void func_01E042F0_b493(Ctx_b149_01E02D30 *c, Beam_b149_01E02D30 *an, Vec_b149_01E02D30 *pts __attribute__((aligned(16))), s32 flags) {
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

/* shape b493:01E04E30, 191 insns: b139:01E03820's sprite drawn twice with a square view of the object's float size
   (0x48). Needs func_01E00080_b493 in the same file and static. */

typedef struct Cam_b493_01E04E30 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[0x14];
    Vec4f at;
} Cam_b493_01E04E30;

typedef struct Obj_b493_01E04E30 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b493_01E04E30;

typedef struct Xyz_b493_01E04E30 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b493_01E04E30;

typedef struct Uv_b493_01E04E30 {
    f32 u, v;
} Uv_b493_01E04E30;

typedef struct Pk_b493_01E04E30 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b493_01E04E30 uv;
    u64 pad18;
    Xyz_b493_01E04E30 v[4];
    u64 pad60[6];
} Pk_b493_01E04E30;

typedef struct Buf_b493_01E04E30 {
    u64 tag;
    Pk_b493_01E04E30 pk;
} Buf_b493_01E04E30;

static void func_01E04E30_b493(Obj_b493_01E04E30 *obj, Cam_b493_01E04E30 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b493_01E04E30 buf;
    Uv_b493_01E04E30 uv;
    s32 sel;
    s32 mode;
    Pk_b493_01E04E30 *p = &buf.pk;

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
    func_01E00080_b493((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->size, cam->size);
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
