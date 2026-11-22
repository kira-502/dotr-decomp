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

static void func_01E00080_b770(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b770(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

/* shape b108:01E00DF0, 227 insns, 2 copies: draws a band of 6 quads around a position (outer and inner radius, outer and
   inner height, 4 wide, 60 apart from the band's start angle), two colours, turned by the band's rotation; blend
   from flags >> 4, depth mode flags & 0xF (projected, far after a packet tweak, or front) (b180:01E01230 family) */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b108_01E00DF0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[4];
    f32 h0;
    u8 pad38[4];
    f32 h1;
    u8 pad40[8];
    f32 outer;
    f32 inner;
    u8 pad50[0xA];
    s16 start;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Band_b108_01E00DF0;

static void func_01E00D70_b770(Obj_b108_01E00DF0 *o, Band_b108_01E00DF0 *s, s32 flags, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 k;
    s32 t;
    s16 b;
    s16 a;
    u8 *p;
    s32 mode;
    f32 ro;
    f32 ri;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    mode = flags & 0xF;
    quad[0].y = -s->h0;
    quad[1].y = -s->h0;
    quad[2].y = -s->h1;
    quad[3].y = -s->h1;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 6; k++) {
        t = s->start + a;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = a + (s->start + 4);
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, -1);
        }
        a += 0x3C;
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

static void func_01E01100_b770(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

extern void b770_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E012D0_b770(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b770_01E00080(p, o->b94, o->hC0);
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

/* shape b770:01E01820 (B770_W_S), 221 insns: the scene script of b770: counts g+0x490E; tick 5 spawns 0x1E02490,
   tick 200 two 0x1E02C80 (flag 0, then 1); up to tick 189 two 0x1E01F60 effects on joints 0x48A0 / 0x48A2 (plus
   0x1E022E0 every 8th tick); 190..249 a 0x1E02950 on joint 0x489C; 264..304 a 0x1E020F0 between joint 0x48AA and the
   camera; 190..263 0x1E01BA0 and 0x1E022E0 on joint 0x489E, six 0x1E01BA0 on tick 190; 50..169 a 0x1E01D80 every
   16th tick */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x4640];
    s16 j489C;
    s16 j489E;
    s16 j48A0;
    s16 j48A2;
    u8 pad48A4[6];
    s16 j48AA;
    u8 pad48AC[0x5A];
    s16 flag;
    u8 pad4908[6];
    s16 tick;
} Ctx_b770_01E01820;

static void func_01E01820_b770(Ctx_b770_01E01820 *g) {
    extern void b770_01E01BA0();
    extern void b770_01E01D80();
    extern void b770_01E01F60();
    extern void b770_01E020F0();
    extern void b770_01E022E0();
    extern void b770_01E02490();
    extern void b770_01E02950();
    extern void b770_01E02C80();
    extern void b770_01E03800(Ctx_b770_01E01820 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    s16 i;

    g->tick++;
    if (g->tick == 5) {
        b770_01E03800(g, b770_01E02490, 0);
    }
    if (g->tick == 200) {
        g->flag = 0;
        b770_01E03800(g, b770_01E02C80, 0);
        g->flag = 1;
        b770_01E03800(g, b770_01E02C80, 0);
    }
    if (g->tick >= 0 && g->tick <= 189) {
        func_001F5620(func_001F53A0(), g->j48A0, &g->x);
        g->flag = 0;
        b770_01E03800(g, b770_01E01F60, 0);
        if (g->tick % 8 == 1) {
            b770_01E03800(g, b770_01E022E0, 0);
        }
        func_001F5620(func_001F53A0(), g->j48A2, &g->x);
        g->flag = 0;
        b770_01E03800(g, b770_01E01F60, 0);
        if (g->tick % 8 == 1) {
            b770_01E03800(g, b770_01E022E0, 0);
        }
    }
    if (g->tick >= 190 && g->tick <= 249) {
        func_001F5620(func_001F53A0(), g->j489C, &g->x);
        g->flag = 0;
        b770_01E03800(g, b770_01E02950, 0);
    }
    if (g->tick >= 264 && g->tick <= 304) {
        func_001F5620(func_001F5380(), g->j48AA, v);
        func_001F5F90(func_001F5380(), &g->x);
        g->y = v[1];
        g->flag = 0;
        b770_01E03800(g, b770_01E020F0, 0);
    }
    if (g->tick >= 190 && g->tick <= 263) {
        func_001F5620(func_001F53A0(), g->j489E, &g->x);
        g->flag = 0;
        b770_01E03800(g, b770_01E01BA0, 0);
        b770_01E03800(g, b770_01E022E0, 0);
    }
    if (g->tick == 190) {
        func_001F5620(func_001F53A0(), g->j489E, &g->x);
        g->flag = 1;
        for (i = 0; i < 6; i++) {
            b770_01E03800(g, b770_01E01BA0, 0);
        }
    }
    if (g->tick >= 50 && g->tick <= 169) {
        if (g->tick % 16 == 1) {
            func_001F5620(func_001F53A0(), g->j489E, &g->x);
            g->flag = 1;
            b770_01E03800(g, b770_01E01D80, 0);
        }
    }
}

/* shape b770:01E01BA0, 117 insns, 2 copies: a red spark: set up once (size 4, or 10 when its old angle was 1; random frame,
   speed 5..12 or 9..20, life 3..7); full for its life, then fades out; grows 1 and turns by its speed (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 speed;
    u8 pad10[0x38];
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
} Spark_b770_01E01BA0;

static s32 func_01E01BA0_b770(void *arg0, Spark_b770_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 4.0f;
        if (o->ang == 1) {
            o->size = 10.0f;
        }
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0x10, 0x10);
        o->hA = func_0019A5C8() % 8;
        o->hC = o->ang;
        o->ang = 0;
        o->speed = func_0019A5C8() % 8 + 5;
        if (o->hC == 1) {
            o->speed = func_0019A5C8() % 12 + 9;
        }
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->size += 1.0f;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    return 0;
}

/* shape b770:01E01BA0, 117 insns, 2 copies: a red spark: set up once (size 4, or 10 when its old angle was 1; random frame,
   speed 5..12 or 9..20, life 3..7); full for its life, then fades out; grows 1 and turns by its speed (b225:01E026A0 family, 0x58-state layout) */

static s32 func_01E01D80_b770(void *arg0, Spark_b770_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 4.0f;
        if (o->ang == 1) {
            o->size = 10.0f;
        }
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0x10, 0x10);
        o->hA = func_0019A5C8() % 8;
        o->hC = o->ang;
        o->ang = 0;
        o->speed = func_0019A5C8() % 8 + 5;
        if (o->hC == 1) {
            o->speed = func_0019A5C8() % 12 + 9;
        }
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->size += 1.0f;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    return 0;
}

/* shape b770:01E01F60, 97 insns: on start f48 4, variant 0..3, colour (0xC0, 0x10, 0x10), 0xA 0..7, 0xC keeps the old
   0x50, 0x50 = 0, speed 5..12 (0xE), 0x8 0..34, hold 3..7 (0x6); alpha 0x80 during the hold, then fades by 8 and
   stops; after the first tick f48 grows by 1 and 0x50 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b770_01E01F60;

static s32 func_01E01F60_b770(s32 arg0, Fx_b770_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0x10, 0x10);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = 0;
        o->speed = func_0019A5C8() % 8 + 5;
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
        o->f48 += 1.0f;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b770:01E020F0 (B770_OBJ_MOVE_6_), 122 insns, 1 copy: a white mote: speed 3.0 (10.0 for kind 1), spin
   rand % 4, size 100..249 growing by 2..6 a tick (9..20 for kind 1), bright (0xFF) for 3..7 ticks then fades by 8
   until it stops */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x38];
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
} Fx_b770_01E020F0;

static s32 func_01E020F0_b770(void *g, Fx_b770_01E020F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        if (o->f50 == 1) {
            o->f48 = 10.0f;
        }
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 150 + 100;
        o->fE = func_0019A5C8() % 5 + 2;
        if (o->fC == 1) {
            o->fE = func_0019A5C8() % 12 + 9;
        }
        o->f8 = func_0019A5C8() % 35;
        o->f6 = func_0019A5C8() % 5 + 3;
        o->f5A = func_0019A5C8() % 3;
        o->mode = 2;
    }
    if (o->tick < o->f6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->fE;
    }
    o->tick++;
    return 0;
}

/* shape b394:01E01AA0, 108 insns: a grey spark: f48 4 (+2 per tick), fA -7..7, fC = the old f50, f50 0, spin 5..12
   (9..20 when fC was 1), f8 0..34, life 3..7; alpha 0x80 during the life, then fades by 8; f50 grows by the spin
   each tick after the first */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x38];
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
} Fx_b394_01E01AA0;

static s32 func_01E022E0_b770(s32 arg0, Fx_b394_01E01AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->f56 = 0;
        func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = 0;
        o->spin = func_0019A5C8() % 8 + 5;
        if (o->fC == 1) {
            o->spin = func_0019A5C8() % 12 + 9;
        }
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 2.0f;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b770:01E02490, 96 insns: a purple two-colour pulse: both alphas in by 12 up to 0x80 for 10 ticks, then until tick 355 they swing down to 0x10 and back up by 12, then out by 8 and end */

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
} Obj_b770_01E02490;

static s32 func_01E02490_b770(s32 arg0, Obj_b770_01E02490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0x40);
        func_001076F0(o->col2, 0x80, 0x10, 0x40);
        o->h50 = 0;
        o->mode = 2;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (o->t < 355) {
        if (o->h50 == 0) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 12;
            }
            if (o->col2[3] > 0x10) {
                o->col2[3] -= 12;
            } else {
                o->h50 = 1;
            }
        } else {
            if (o->col[3] < 0x80) {
                o->col[3] += 12;
            }
            if (o->col2[3] < 0x80) {
                o->col2[3] += 12;
            } else {
                o->h50 = 0;
            }
        }
    } else {
        if (o->col[3] > 9) {
            o->col[3] -= 8;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 9) {
            o->col2[3] -= 8;
        }
    }
    o->t++;
    return 0;
}

/* shape b770:01E02610, 87 insns: a blinking grey two-colour shape (17 x 11, random frame 0..6, random 4..6 at +8): both alphas in by 12 up to 0x80 for 20 ticks; white on odd ticks, light grey on even */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b770_01E02610;

static s32 func_01E02610_b770(s32 arg0, Obj_b770_01E02610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 17.0f;
        o->f4C = o->f48 - 6.0f;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
    }
    if (o->t < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    o->t++;
    return 0;
}

/* shape b756:01E03D40, 119 insns, 2 copies: a two-kind flare: kind 0 a small grey one fading in with a flickering
   orange/violet second colour, kind 1 a large white one fading in then out; turns each frame (b402:01E02710
   family) */

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Flare_b756_01E03D40;

static s32 func_01E02770_b770(void *arg0, Flare_b756_01E03D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 40.0f;
        if (o->kind == 1) {
            o->size = 300.0f;
        }
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x80, 0x80);
            func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        } else {
            func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->c1, 0x80, 0x40, 0x10);
        }
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->kind == 0 && o->t < 0xC) {
        o->c0[3] += 0x10;
    }
    if (o->kind == 1) {
        if (o->t < 0xC) {
            if (o->c0[3] < 0xC0) {
                o->c0[3] += 0x1B;
            }
        } else if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        }
    }
    if (o->kind == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->c1, 0x80, 8, 0x40);
        }
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b770:01E02950, 109 insns: a red/white ring (40 x 10.5 for kind 0) spun 0x4000 a tick and rolled 0x200 from a random roll, growing 4, its second colour blinking purple: in by 21 up to 0x80 for 6 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[4];
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b770_01E02950;

static s32 func_01E02950_b770(s32 arg0, Obj_b770_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->h50 == 0) {
            o->f48 = 40.0f;
            o->f4C = 10.5f;
        }
        func_00205C40((s32)&o->w20);
        o->w20 += 0x4000;
        o->w28 = func_0019A5C8() % 65535;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0xF0, 0x48, 0x48);
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 6) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x15;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 4.0f;
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 8, 0x40);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->w28 += 0x200;
    o->t++;
    return 0;
}

/* shape b770:01E02B10, 90 insns: a grey/red ring (90 x 60) at a random angle held at turn 0x4000; kind 0 fades in its first colour, kind 1 its second (colours swapped), by 32 for 12 ticks; then the first colour fades by 11 */

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
} Obj_b770_01E02B10;

static s32 func_01E02B10_b770(s32 arg0, Obj_b770_01E02B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 90.0f;
        o->f4C = o->f48 - 30.0f;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0xF0, 0x20, 0x20);
            o->col2[3] = 0;
        } else if (o->h50 == 1) {
            func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col, 0xF0, 0x20, 0x20);
            o->col[3] = 0;
        }
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->t < 12) {
        if (o->h50 == 0) {
            o->col[3] += 0x20;
        }
        if (o->h50 == 1) {
            o->col2[3] += 0x20;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    }
    func_00205C40((s32)&o->w20);
    o->w20 = 0x4000;
    o->t++;
    return 0;
}

/* shape b770:01E02C80, 144 insns: b232:01E01130 with the scene packet at ctx+0x44B8, the sine table at ctx+0x4B10,
   colour 0x28 and a 90-tick fade-in */

/* OVL_WARM */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b770_01E02C80;

typedef struct {
    f32 s, t;
    Xyz_b770_01E02C80 p;
} Tv_b770_01E02C80;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b770_01E02C80 v[2];
} Tex_b770_01E02C80;

typedef struct {
    u8 pad[0x44B8];
    Tex_b770_01E02C80 *pk;
    u8 pad44BC[0x4B10 - 0x44BC];
    u8 tab[1];
} Game_b770_01E02C80;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b770_01E02C80;

static s32 func_01E02C80_b770(Game_b770_01E02C80 *g, Fx_b770_01E02C80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x28, 0x28, 0x28);
        if (o->kind == 0) {
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->ang = 180;
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = (f + 0x6C0) * 16 - 8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = (f + 0x940) * 16 - 8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    func_002075F0((s32)g->pk, 0, 0);
    o->f8 = 10.0f * func_00108030(g->tab, o->ang, 1);
    o->ang += 25;
    if (o->tick < 90) {
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

/* shape b770:01E02EC0 (b770), 589 insns, 1 copy: b770 scene manager in b041:01E022D0 form: setup (five joints and a
   camera, 7 type-4 and two type-5 textures, angle from the turn, a 256 s8 jitter table and 30 s16 randoms), step
   every slot counting the 01E02C80 ones, draw ten kinds; scene code from the timer */

typedef struct {
    u8 pad0[0xA];
    s16 h0A;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b770_01E02EC0;

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
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b770_01E02EC0 fx[150];
    u8 pad4440[0x30];
    f32 f4470;
    u8 pad4474[0xC];
    s32 tex[2];
    u8 pad4488[0x18];
    s32 count;
    u8 pad44A4[8];
    s32 ot;
    u8 pad44B0[0x3D4];
    f32 level;
    u8 pad4888[0x14];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    u8 pad48A6[4];
    s16 cam;
    u8 pad48AC[0x10];
    s16 r30[30];
    u8 pad48F8[0x12];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 pad4A10[0x100];
    u8 crd[0x170];
} Scene_b770_01E02EC0;

static s32 func_01E02EC0_b770(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern f32 *func_001F9AD0(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_0019A5C8(void);
    extern void b770_01E01820();
    extern void b770_01E012D0();
    extern void b770_01E03940();
    extern void b770_01E03C50();
    Scene_b770_01E02EC0 *g = (Scene_b770_01E02EC0 *)arg0;
    s16 m;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    u8 pk[0x90];
    f32 *p;
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4C80);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 369;
        g->jA = func_001F5560(func_001F53A0(), 0x41, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x43, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x24, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x4E, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x40, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        g->tex260[0] = func_00202BF0(4, 0);
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s32)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 30; k++) {
            g->r30[k] = func_0019A5C8() % 15;
        }
        return 0;
    }
    b770_01E01820(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02C80_b770) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    m++;
                }
            }
        }
    }
    p = func_001F9AD0(0);
    if (g->frame == 2) {
        g->f4470 = *p;
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01BA0_b770) {
                func_00106080(rm, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex260[15];
                g->hB8 = 6;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b770_01E012D0(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D80_b770) {
                func_00106080(rm2, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex260[15];
                g->hB8 = 1;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b770_01E012D0(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E022E0_b770) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->tex88 = g->tex[1];
                g->hB8 = 1;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b770_01E012D0(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F60_b770) {
                func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->tex88 = g->tex260[15];
                g->hB8 = 1;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b770_01E012D0(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E020F0_b770) {
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->tex88 = g->tex[0];
                g->hB8 = 10;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b770_01E012D0(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02490_b770) {
                func_001F5F90(func_001F53A0(), &v);
                if (g->f4470 > 0.0f) {
                    v.x = -500.0f;
                } else {
                    v.x = 500.0f;
                }
                func_00205440(&v, NULL, &pk[0x18], &g->level);
                func_01E01100_b770((s32)g, (u8 *)&g->fx[k], 0x21, g->level);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02610_b770) {
                g->tex88 = g->tex[0];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                g->hB8 = 1;
                g->hBE = 0;
                b770_01E03940(g, &g->fx[k], 0x20, &g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02770_b770) {
                if (g->fx[k].h50 == 0) {
                    func_001F5620(func_001F53A0(), g->jA, &v);
                }
                if (g->fx[k].h50 == 1) {
                    func_001F5620(func_001F53A0(), g->jB, &v);
                }
                func_01E00920_b770((void *)g, (void *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02950_b770) {
                func_001F5620(func_001F53A0(), g->jA, &v);
                if (g->turn) {
                    v.z += 1.1f;
                } else {
                    v.z -= 1.1f;
                }
                v.y += 0.4f;
                func_01E00D70_b770((void *)g, (void *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B10_b770) {
                func_01E00920_b770((void *)g, (void *)&g->fx[k], 0x21, g->fx[k].pos);
            }
        }
    }
    if (m) {
        b770_01E03C50(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xAF) {
        return 1;
    }
    if (g->frame == 0x140) {
        return 4;
    }
    if (g->frame == 0x136) {
        return 2;
    }
    if (g->frame > 0xB9 && g->frame < 0x12C) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b770:01E03800, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b770_01E03800 {
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
} Slot_b770_01E03800;

typedef struct Obj_b770_01E03800 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b770_01E03800 slots[0x96];
    u8 padB[0x64];
    u8 rgba[4];
    u8 padC[0x45E];
    s16 fB2B0;
} Obj_b770_01E03800;

static s32 func_01E03800_b770(Obj_b770_01E03800 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b770_01E03800 *s = NULL;
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

/* shape b770:01E03940, 196 insns: b094:01E03260 twin (scene fields moved), c063:01E05840 cousin without the scale, only the sectors below the scene's limit (0x4900) are drawn; b756:01E061D0 family burst draw: two-colour packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles o->ang + 20 i - 200 between radii f4C and f48, each with its frame from the scene table through func_00106080 into the rect, depth-tested into the scene ot */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b770_01E03940;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x44AC - 0xC0];
    s32 ot;
    u8 pad44B0[0x48BC - 0x44B0];
    s16 frames[18];
    u8 pad48E0[0x4900 - 0x48E0];
    s16 lim;
    u8 pad4902[0x4B10 - 0x4902];
    u8 trig[1];
} Game_b770_01E03940;

static void func_01E03940_b770(Game_b770_01E03940 *g, Obj_b770_01E03940 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];

    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 a;
    void *p = &buf;
    s16 s;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;
    s32 t;

    *(Vec4f *)pos = *in;
    a = 0;
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
    for (i = 0; i < 18; i++) {
        if (a < g->lim) {
            func_00106080(rm, 0x14, g->frames[i], 0);
            g->rect = *(Vec4f *)rm;
            func_00108500(p, &g->rect, g->frame);
            s = o->ang + a - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[2].x = c * r1;
            q[2].z = sn * r1;
            q[0].x = c * r0;
            q[0].z = sn * r0;
            t = o->ang + 20;
            s = a + t - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[3].x = c * r1;
            q[3].z = sn * r1;
            q[1].x = c * r0;
            q[1].z = sn * r0;
            if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->ot, (u32)depth[0]);
            }
            a += 20;
        }
    }
}

/* shape b770:01E03C50, 92 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x44B8, ot at
   0x44B4), texture from func_001F5380, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b770:01E02C80 is drawn by it; before step 0x490E reaches 0xE6 the packet's first corner is projected from model point 0x489E (depth 0x4888); close
   the ot at that depth if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b770_01E03C50;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b770_01E03C50;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b770_01E03C50 slots[0x96];
    u8 pad4440[0x74];
    s32 ot;
    Pkt_b770_01E03C50 *pk;
    u8 pad44BC[0x3CC];
    f32 depth;
    u8 pad488C[0x12];
    s16 point;
    u8 pad48A0[0x6E];
    s16 step;
} Scene_b770_01E03C50;

static void func_01E03C50_b770(Scene_b770_01E03C50 *g) {
    extern void b770_01E02C80(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F5380(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00207FD0(s32, s32, s32);
    Vec4f pt;
    Pkt_b770_01E03C50 pkt __attribute__((aligned(8)));
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
    func_001F7060(func_001F5380(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    if (g->step < 0xE6) {
        func_001F5620(func_001F53A0(), g->point, &pt);
        func_00205440(&pt, 0, (u8 *)g->pk + 0x20, &g->depth);
    }
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b770_01E02C80) {
                b770_01E02C80(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), (u32)g->depth);
    }
}
