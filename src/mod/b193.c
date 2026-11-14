#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b193(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b193(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b193_01E009B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Anim_b193_01E009B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b193_01E009B0;

typedef struct {
    u8 b[0x90];
} Pkt_b193_01E009B0;

static void func_01E009B0_b193(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b193_01E009B0 quad[4];
    Vec_b193_01E009B0 at;
    Vec_b193_01E009B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b193_01E009B0 pkt;
    s32 a;
    s32 k;
    s16 j;
    Pkt_b193_01E009B0 *p;
    s16 blend;
    s32 kind;
    f32 w0;
    f32 w1;

    p = &pkt;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    kind = mode & 0xF;
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    for (k = 0; k < 36; k++) {
        if (k == 0) {
            a = an->step + j;
            quad[0].x = w0 * func_00108030(o->bD8, a, 1);
            quad[0].z = w0 * func_00108030(o->bD8, a, 0);
            quad[2].x = w1 * func_00108030(o->bD8, a, 1);
            quad[2].z = w1 * func_00108030(o->bD8, a, 0);
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        }
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
        j += 10;
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

static void func_01E00E10_b193(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
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

extern void b193_01E00110(Pkt_b020_01E00920 *, void *, s32);

static void func_01E01270_b193(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b193_01E00110(p, o->b94, o->hC0);
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

static void func_01E017C0_b193(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b193((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b193((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

INCLUDE_ASM("asm/nonmatchings/mod/b193", func_01E01D70_b193);

/* shape b193:01E02290, 165 insns: the b193 module's event step: counts ticks; at 25 spawns b193:01E02780 and b193:01E02910 at the second and third tracked points (slots 0, 1); from 39 to 229 follows the first point sliding 8 in z (back if ctx+0xBCEE is set), spawns b193:01E02530 before 76 and b193:01E02B10; from 77 to 229 follows the camera-side point (ctx+0xBCCA) and spawns b193:01E02E50 every third tick; turns 4 a tick, wrapped at 360 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xBCBC - 0x25C];
    s16 id0;
    s16 id1;
    s16 id2;
    u8 padBCC2[0xBCCA - 0xBCC2];
    s16 id3;
    u8 padBCCC[0xBCE0 - 0xBCCC];
    s16 turn;
    u8 padBCE2[0xBCEA - 0xBCE2];
    s16 slot;
    u8 padBCEC[2];
    s16 back;
    u8 padBCF0[2];
    s16 timer;
} Ctx_b193_01E02290;

static void func_01E02290_b193(Ctx_b193_01E02290 *g) {
    extern s32 b193_01E02530(void);
    extern s32 b193_01E02780(void);
    extern s32 b193_01E02910(void);
    extern s32 b193_01E02B10(void);
    extern s32 b193_01E02E50(void);
    extern void b193_01E03A90(Ctx_b193_01E02290 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);

    g->timer++;
    if (g->timer == 25) {
        g->slot = 0;
        func_001F5620(func_001F53A0(), g->id1, g->pos);
        b193_01E03A90(g, b193_01E02780, 0);
        b193_01E03A90(g, b193_01E02910, 0);
        g->slot = 1;
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        b193_01E03A90(g, b193_01E02780, 0);
        b193_01E03A90(g, b193_01E02910, 0);
    }
    if (g->timer > 38 && g->timer < 230) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        if (g->back != 0) {
            g->pos[2] -= 8.0f;
        } else {
            g->pos[2] += 8.0f;
        }
        if (g->timer < 76) {
            b193_01E03A90(g, b193_01E02530, 0);
        }
        b193_01E03A90(g, b193_01E02B10, 0);
    }
    if (g->timer > 76 && g->timer < 230) {
        func_001F5620(func_001F5380(), g->id3, g->pos);
        if (g->timer % 3 == 1) {
            b193_01E03A90(g, b193_01E02E50, 0);
        }
    }
    g->turn += 4;
    if (g->turn > 360) {
        g->turn %= 360;
    }
}

/* shape b193:01E02530, 145 insns: a green rising ring (b206:01E01550's kind): on start size 35, both colours 0x80; alpha up
   by 64 to 0x80 for 2 ticks, then down by 19 until it ends; blinks green 0x80/0x60; spin 0x4000; f34 swings by 5 towards
   +20 (scene flag at g+0xBCEE set) or -20; f30 grows by 0.2 to 10, f38 by 13 to 30; size grows by 35.5 with
   f4C = size - f38; h5C turns by 9 */

typedef struct {
    u8 pad0[0xBCEE];
    s16 flag;
} Game_b193_01E02530;

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 size;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b193_01E02530;

static s32 func_01E02530_b193(Game_b193_01E02530 *g, Obj_b193_01E02530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 35.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 20) {
        o->c1[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x10, 0x80, 0x10);
    } else {
        func_001076F0(o->c0, 0x10, 0x60, 0x10);
    }
    o->rot = 0x4000;
    if (g->flag != 0) {
        if (o->f34 < 20.0f) {
            o->f34 += 5.0f;
        }
    } else if (!(o->f34 <= -20.0f)) {
        o->f34 -= 5.0f;
    }
    if (o->f30 < 10.0f) {
        o->f30 += 0.2f;
    }
    if (o->f38 < 30.0f) {
        o->f38 += 13.0f;
    }
    o->size += 35.5f;
    o->f4C = o->size - o->f38;
    o->h5C += 9;
    o->t++;
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

static s32 func_01E02780_b193(s32 unused, Spark_b193_01E02780 *o) {
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

/* shape b193:01E02910, 127 insns: b144:01E02430 family green spark (f48 10..19, frame 0..3, random turn, h52 counting from 1, f50 150..299 growing 1..3 per tick, angle 0..359, f8 1..8): alpha 0x60 for 2..4 ticks, then down by 11 */

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
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b193_01E02910;

static s32 func_01E02910_b193(s32 arg0, Fx_b193_01E02910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x10, 0x80, 0x00);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 150 + 150;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b193:01E02B10, 139 insns: b749:01E02310's ring glow, size 3/4, spin 0x4000, grey 0x50, held 25, also sliding 6 a tick on y by the scene side flag */

typedef struct {
    u8 pad0000[0xBCE0];
    s16 h70A0;
    u8 padBCE2[0xC];
    s16 side;
} Mgr_b193_01E02B10;

typedef struct {
    u8 pad00[8];
    s16 h8;
    u8 pad0A[0xE];
    f32 f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    u8 pad34[8];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 h54;
    s16 h56;
    s16 h58;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b193_01E02B10;

static s32 func_01E02B10_b193(Mgr_b193_01E02B10 *m, Obj_b193_01E02B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 3.0f;
        o->f4C = 4.0f;
        o->w20 = 0x4000;
        o->h56 = 0;
        o->h58 = 2;
        o->h8 = func_0019A5C8() % 2 + 3;
        o->h5C = m->h70A0;
        func_001076F0(o->c60, 0x50, 0x50, 0x50);
        func_001076F0(o->c64, 0x50, 0x50, 0x50);
    }
    if (o->h54 < 25) {
        if (o->c60[3] < 0x80) {
            o->c60[3] = 0x80;
        }
    } else if (o->c60[3] > 15) {
        o->c60[3] -= 14;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        if (o->f3C < 3.0f) {
            o->f3C += 1.0f;
        }
        if (o->f30 < 15.0f) {
            o->f30 += 1.5f;
        }
        if (o->f4C < 20.0f) {
            o->f4C += 0.8f;
        }
        if (m->side != 0) {
            o->f18 -= 6.0f;
        } else {
            o->f18 += 6.0f;
        }
        o->f48 += 0.8f;
    }
    o->h5C += 9;
    o->h54++;
    return 0;
}

/* shape b193:01E02D40, 67 insns: a grey/yellow glow of size 150 at a random angle, growing 1 and spun 0x4000 a tick: in by 64 up to 0xC0 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
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
} Obj_b193_01E02D40;

static s32 func_01E02D40_b193(s32 arg0, Obj_b193_01E02D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 150.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 0x80, 8);
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 1.0f;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b193:01E02E50, 106 insns: on start f48 130, variant 0..6, colour 0x80 grey, random 0x5A, 0xA 0..7, 0xC keeps
   the old 0x50, 0x50 5..14, speed 13..27 (0xE), 0x8 0..34, hold 3..7 (0x6); alpha 0x80 during the hold, then fades by
   9 and stops; f48 grows by 2; 0x50 grows by the speed after the first tick */

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
} Fx_b193_01E02E50;

static s32 func_01E02E50_b193(s32 arg0, Fx_b193_01E02E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 130.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 10 + 5;
        o->speed = func_0019A5C8() % 15 + 13;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 2.0f;
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b149:01E01ED0, 135 insns, 2 copies: a yellow trail on a world track: set up once (fills the track's 15 history points
   with its current point); both colours fade in for 110 frames, then the first fades out (its fade-out step is
   applied twice); while young the module's shape b149:01E00080 shifts the track; blinks, frame climbs to 4 */

typedef struct {
    Vec4f p[15];
} Track_b149_01E01ED0;

typedef struct {
    u8 pad0[0x4470];
    Track_b149_01E01ED0 track[0x50];
    u8 pad[0xB4F0 - 0x4470 - 0x50 * 0xF0];
    Vec4f head[1];
} World_b149_01E01ED0;

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
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Trail_b149_01E01ED0;

static s32 func_01E03000_b193(World_b149_01E01ED0 *w, Trail_b149_01E01ED0 *o) {
    extern void b193_01E00080(void *, s32, s32, void *);
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
        o->h56 = 0;
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
    if (o->t < 0x75) {
        b193_01E00080(&w->track[o->idx].p[14], 15, 0, &w->head[o->idx]);
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x10);
    } else {
        func_001076F0(o->c0, 0x70, 0x70, 0x10);
    }
    if (o->t != 0) {
        if (o->frame < 4) {
            o->frame++;
        }
    }
    o->t++;
    return 0;
}

/* shape b193:01E03220 (b193), 540 insns, 1 copy: b193 scene manager in b749:01E031E0 form: setup (camera and three
   joints, textures (4,10..15), (4,0), (5,0..2), a 256 s8 jitter with 100..179 set to rand%4, a second 256 jitter),
   step b193:01E02290 and every slot (150 of 0x70), draw b193:01E02530 rings, b193:01E02780/01E02E50 sparks,
   b193:01E02910 sparks on a joint, b193:01E02B10 glows, b193:01E02D40 glows on a joint and b193:01E03000 trails;
   scene code from the timer */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x10];
    f32 f30;
    u8 pad34[0x10];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b193_01E03220;

typedef struct {
    Vec4f p[15];
} Track_b193_01E03220;

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
    Fx_b193_01E03220 fx[150];
    u8 pad4440[0x30];
    Track_b193_01E03220 track[0x50];
    u8 pad8F70[0xBC70 - 0x8F70];
    s32 tex2[3];
    u8 padBC7C[0x14];
    s32 count;
    u8 padBC94[8];
    s32 ot;
    u8 padBCA0[0x1C];
    s16 jA;
    s16 jnt[2];
    u8 padBCC2[8];
    s16 cam;
    u8 padBCCC[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b193_01E03220;

static s32 func_01E03220_b193(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    extern s16 func_001A22C0(f32);
    extern void func_01E02290_b193();
    extern void func_01E01D70_b193();
    extern void func_01E03C30_b193();
    Scene_b193_01E03220 *g = (Scene_b193_01E03220 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    u8 buf[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xC060);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x10A;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jnt[0] = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->jnt[1] = func_001F5560(func_001F53A0(), 0x25, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = func_001A22C0(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E02290_b193(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E02530_b193) {
                v = g->fx[k].pos;
                func_01E009B0_b193((Obj_b193_01E009B0 *)g, (Anim_b193_01E009B0 *)&g->fx[k], 0x20, *(Vec_b193_01E009B0 *)&v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02780_b193) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hB8 = 6;
                g->hC0 = g->fx[k].hA;
                func_001F5620(func_001F53A0(), g->jnt[g->fx[k].h52], &g->px);
                func_01E01270_b193((void *)g, (void *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02910_b193) {
                g->tex88 = g->tex[15];
                func_00106080(rm2, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 10;
                g->hB0 = 1;
                func_001F5620(func_001F53A0(), g->jnt[g->fx[k].h52], &g->fx[k].pos);
                func_01E017C0_b193((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02E50_b193) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex2[1];
                g->hB8 = 5;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E01270_b193((void *)g, (void *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B10_b193) {
                g->tex88 = g->tex2[2];
                func_00106080(rm4, 0x8C, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->px += g->fx[k].f30 * func_00108030(g->crdD8, g->fx[k].h5C, 0);
                g->py += g->fx[k].f30 * func_00108030(g->crdD8, g->fx[k].h5C, 1);
                func_01E01D70_b193(g, &g->fx[k], buf, 0x20);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D40_b193) {
                func_001F5620(func_001F53A0(), g->jnt[g->fx[k].h52], &v);
                func_01E00E10_b193((Obj_b082_01E00920 *)g, (Data_b082_01E00920 *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03000_b193) {
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->u94.uv[3] >>= 1;
                g->u94.uv[1] += g->u94.uv[3];
                func_001F5F90(func_001F53A0(), &v);
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
                g->hBE = 1;
                if (g->fx[k].h54 > 0x53) {
                    func_01E03C30_b193(g, &g->fx[k], &g->track[g->fx[k].h50], 0);
                }
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x46) {
        return 1;
    }
    if (g->frame == 0xFF) {
        return 3;
    }
    if (g->frame > 0x50 && g->frame < 0xF5) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b193:01E03A90, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

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
} Obj_b193_01E03A90;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b193_01E03A90 slot[150];
    u8 padEnd[0xbc94 - 0x2a0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padBC98[0x52];
    s16 val;
} Ctx_b193_01E03A90;

static s32 func_01E03A90_b193(Ctx_b193_01E03A90 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b193_01E03A90 *s;

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
static void func_01E03C30_b193(Ctx_b149_01E02D30 *c, Beam_b149_01E02D30 *an, Vec_b149_01E02D30 *pts __attribute__((aligned(16))), s32 flags) {
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
