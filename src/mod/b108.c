#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b108(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

static void func_01E00100_b108(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009A0_b108(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

static void func_01E00DF0_b108(Obj_b108_01E00DF0 *o, Band_b108_01E00DF0 *s, s32 flags, Vec4f pos) {
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

extern void b108_01E00100(Pkt_b020_01E00920 *, void *, s32);

static void func_01E01180_b108(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b108_01E00100(p, o->b94, o->hC0);
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

/* shape b108:01E016D0, 289 insns: the module's spawn step: tick 10 b108:01E02380 at joint 0x696C; ticks 125..210 odd
   b108:01E025B0 there; 125 b108:01E021B0 at joint 0x696E; 269 b108:01E027D0 at joint 0x697A; ticks 210..285 every
   fourth (up to 9) a new point jittered 75 around joint 0x697A, remembered twice, with b108:01E02010 and
   b108:01E01EB0; from 211 each point closes a 23rd of its gap to the joint for 22 ticks; 260 eight b108:01E01CF0;
   211..285 b108:01E01B60 */

typedef struct {
    f32 x, y, z, w;
} V4_b108_01E016D0;

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x63B0 - 0x25C];
    V4_b108_01E016D0 cur[10];
    V4_b108_01E016D0 start[10];
    u8 pad64F0[0x696C - 0x64F0];
    s16 j6C;
    s16 j6E;
    u8 pad6970[0x697A - 0x6970];
    s16 j7A;
    u8 pad697C[0x6AC0 - 0x697C];
    s16 n;
    s16 age[10];
    u8 pad6AD6[0x6ADC - 0x6AD6];
    s16 idx;
    u8 pad6ADE[0x6AE4 - 0x6ADE];
    s16 t;
} Scene_b108_01E016D0;

static s32 func_01E01B60_b108();
static s32 func_01E01CF0_b108();
static s32 func_01E01EB0_b108();
static s32 func_01E02010_b108();
static s32 func_01E021B0_b108();
static s32 func_01E02380_b108();
static s32 func_01E025B0_b108();
static s32 func_01E027D0_b108();
static s32 func_01E02FF0_b108();

static void func_01E016D0_b108(Scene_b108_01E016D0 *s) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    s->t++;
    if (s->t == 10) {
        s->idx = 0;
        func_001F5620(func_001F53A0(), s->j6C, &s->px);
        func_01E02FF0_b108(s, func_01E02380_b108, 0);
    }
    if (s->t >= 0x7D && s->t < 0xD3) {
        if (s->t % 2 == 1) {
            s->idx = 0;
            func_001F5620(func_001F53A0(), s->j6C, &s->px);
            func_01E02FF0_b108(s, func_01E025B0_b108, 0);
        }
    }
    if (s->t == 0x7D) {
        s->idx = 0;
        func_001F5620(func_001F53A0(), s->j6E, &s->px);
        func_01E02FF0_b108(s, func_01E021B0_b108, 0);
    }
    if (s->t == 0x10D) {
        func_001F5620(func_001F5380(), s->j7A, &s->px);
        s->idx = 0;
        func_01E02FF0_b108(s, func_01E027D0_b108, 0);
    }
    if (s->t >= 0xD2 && s->t < 0x11E) {
        if (s->t % 4 == 1 && s->n < 9) {
            s->idx = s->n;
            func_001F5620(func_001F5380(), s->j7A, &s->px);
            s->cur[s->idx].y = s->start[s->idx].y = s->py += func_0019A5C8() % 150 - 75;
            s->cur[s->idx].x = s->start[s->idx].x = s->px += func_0019A5C8() % 150 - 75;
            s->cur[s->idx].z = s->start[s->idx].z = s->pz += func_0019A5C8() % 150 - 75;
            func_01E02FF0_b108(s, func_01E02010_b108, 0);
            func_01E02FF0_b108(s, func_01E01EB0_b108, 0);
            s->n++;
        }
    }
    if (s->t >= 0xD3) {
        for (i = 0; i < s->n; i++) {
            func_001F5620(func_001F5380(), s->j7A, &s->px);
            if (s->age[i] < 0x16) {
                s->cur[i].x += (s->px - s->start[i].x) / 23.0f;
                s->cur[i].y += (s->py - s->start[i].y) / 23.0f;
                s->cur[i].z += (s->pz - s->start[i].z) / 23.0f;
            }
            s->age[i]++;
        }
    }
    if (s->t == 0x104) {
        func_001F5620(func_001F5380(), s->j7A, &s->px);
        for (i = 0; i < 8; i++) {
            func_01E02FF0_b108(s, func_01E01CF0_b108, 0);
        }
    }
    if (s->t >= 0xD3 && s->t < 0x11E) {
        func_001F5620(func_001F5380(), s->j7A, &s->px);
        func_01E02FF0_b108(s, func_01E01B60_b108, 0);
    }
}

/* shape b108:01E01B60, 99 insns: on start f48 5, variant 0..3, colour 0xC0 grey, 0xA 0..7, 0xC keeps the old 0x50,
   0x50 320..469, speed 15..44 (0xE), 0x8 0..34, hold 3..7 (0x6); alpha 0x80 during the hold; after the first tick
   f48 grows by 1 and 0x50 shrinks by the speed, ending the effect once it reaches 0 */

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
} Fx_b108_01E01B60;

static s32 func_01E01B60_b108(s32 arg0, Fx_b108_01E01B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 150 + 320;
        o->speed = func_0019A5C8() % 30 + 15;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    if (o->tick != 0) {
        if (o->f50 > 0) {
            o->f50 -= o->speed;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b108:01E01CF0, 109 insns: a grey-red flicker ring: size 30 (growing by 12.3 for kind 0), inner 2.5, random turn on all
   three axes and angle; alpha up by 21 to 0x80 until frame 35, then down by 9 until it ends; second colour flickers */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b108_01E01CF0;

static s32 func_01E01CF0_b108(void *arg0, Obj_b108_01E01CF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 30.0f;
        o->f4C = 2.5f;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0xF0, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x23) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x15;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        o->f48 += 12.3f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 8, 0x40);
    }
    o->t++;
    return 0;
}

/* shape b108:01E01EB0, 87 insns: a white/orange glow of size 20 spun 0x4000 a tick, growing 3.3 a tick after 26 ticks; unless held its second colour blinks blue/purple: in by 16 for 50 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b108_01E01EB0;

static s32 func_01E01EB0_b108(s32 arg0, Obj_b108_01E01EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x40, 0x10);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 50) {
        o->col[3] += 0x10;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->t > 25) {
        o->f48 += 3.3f;
    }
    if (o->h50 == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->col2, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->col2, 0x80, 8, 0x40);
        }
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b108:01E02010, 102 insns: a blue-white trail (b357:01E03F50 family, 50-point rows): size 10, width 8 growing by 2 to 48;
   fills its trail row with its start point, holds alpha 0xC0 until frame 80, then fades by 5 until it ends; rebuilds the
   trail tail from its point each frame; flickers blue/white */

typedef struct {
    f32 x, y, z, w;
} V4_b108_01E02010;

typedef struct {
    u8 pad0[0x4470];
    V4_b108_01E02010 trail[10][50];
    V4_b108_01E02010 pts[10];
    V4_b108_01E02010 starts[10];
} Game_b108_01E02010;

typedef struct {
    u8 pad0[6];
    s16 w;
    u8 pad8[0x40];
    f32 size;
    u8 pad4C[4];
    s16 row;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b108_01E02010;

static s32 func_01E02010_b108(Game_b108_01E02010 *g, Obj_b108_01E02010 *o) {
    extern void b108_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    V4_b108_01E02010 *p;
    V4_b108_01E02010 *q;

    if (o->state == 1) {
        o->w = 8;
        o->c0[3] = 0;
        p = &g->starts[o->row];
        q = g->trail[o->row];
        for (i = 0; i < 0x31; i++) {
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
            q++;
        }
        o->size = 10.0f;
        o->state = 2;
    }
    if (o->w < 0x30) {
        o->w += 2;
    }
    if (o->t < 0x50) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xF0, 0x40, 0x40);
    } else {
        func_001076F0(o->c0, 0xF0, 0xF0, 0x40);
    }
    b108_01E00080(&g->trail[o->row][0x31], 0x32, 0, &g->pts[o->row]);
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b108:01E021B0, 113 insns: glow pair pinned to a scene object, fading in for 20 frames and out on the scene
   timer, blinking between two brightness levels */

typedef struct Glow_b108_01E021B0 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    Vec4f pos;
    s32 f20;
    u8 pad24[4];
    s32 f28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 age;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_b108_01E021B0;

typedef struct Scn_b108_01E021B0 {
    u8 pad0[0x696E];
    s16 id;
    u8 pad6970[0x174];
    s16 timer;
} Scn_b108_01E021B0;

static s32 func_01E021B0_b108(Scn_b108_01E021B0 *w, Glow_b108_01E021B0 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    if (o->state == 1) {
        o->f48 = 9.0f;
        o->f4C = o->f48 - 3.0f;
        o->h56 = func_0019A5C8() % 7;
        o->state = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
    }
    if (o->age < 20) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0xC;
        }
    } else if (w->timer > 0xD2) {
        if (o->c0[3] > 10) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->age % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
    }
    o->f20 = 0x4000;
    func_001F5620(func_001F53A0(), w->id, &o->pos);
    o->f28 += 0x100;
    o->age++;
    return 0;
}

/* shape b108:01E02380, 137 insns: spinning glow in two kinds: kind 0 (size 20, grey over green) alpha +16 for 12 ticks, then down by 9 once scene count 211 is passed, outer colour flashing red/purple; kind 1 (size 300, white over orange) alpha up by 27 to 0xC0 for 12 ticks, then down by 9; spins 0x4000 per tick */

typedef struct {
    u8 pad0[0x6AE4];
    s16 count;
} Ctx_b108_01E02380;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b108_01E02380;

static s32 func_01E02380_b108(Ctx_b108_01E02380 *g, Fx_b108_01E02380 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        if (o->kind == 1) {
            o->f48 = 300.0f;
        }
        if (o->kind == 0) {
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
    if (o->kind == 0) {
        if (o->tick < 12) {
            o->col[3] += 0x10;
        } else if (g->count > 210) {
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        if (o->tick < 12) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x1B;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->col2, 0x80, 8, 0x40);
        }
    }
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b108:01E025B0, 134 insns: a spinning glow in two kinds: kind 0 grows 4 from 10 (f4C 2.5), alpha up by 21 to 0x80 for 12 ticks then down by 9; kind 1 grows 10 from 90 (f4C 90), alpha +16 for 12 ticks; the outer colour flashes red/purple every tick; rot[0] fixed at 0x4000, rot[2] turns 0x200 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b108_01E025B0;

static s32 func_01E025B0_b108(s32 arg0, Fx_b108_01E025B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 10.0f;
            o->f4C = 2.5f;
        }
        if (o->kind == 1) {
            o->f48 = 90.0f;
            o->f4C = 90.0f;
        }
        o->rot[2] = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0xF0, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind == 0) {
        if (o->tick < 12) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x15;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind == 1 && o->tick < 12) {
        o->col[3] += 0x10;
    }
    if (o->kind == 0) {
        o->f48 += 4.0f;
    }
    if (o->kind == 1) {
        o->f48 += 10.0f;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 8, 0x40);
    }
    o->rot[0] = 0x4000;
    o->rot[2] += 0x200;
    o->tick++;
    return 0;
}

/* shape b108:01E027D0, 70 insns: a dark/teal glow of size 200 at a random angle, growing 12 and spun 0x4000 a tick: in by 32 up to 0xC0 for 37 ticks (unless held), then out by 9 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b108_01E027D0;

static s32 func_01E027D0_b108(s32 arg0, Obj_b108_01E027D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0x40, 0x40);
        o->col2[3] = 0;
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->t < 37) {
        if (o->h50 == 0) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x20;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 12.0f;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b108:01E028F0 (b108), 447 insns, 1 copy: b108 scene manager in b522:01E02D40 form: setup (four joints, seven
   type-4 and two type-5 textures, 256 s8 and 30 s16 jitters), step b108:01E016D0 and every slot, draw the eight
   effect kinds (b108:01E01B60 flames, b108:01E01EB0 circles at both trail ends, b108:01E02010 trails, b108:01E021B0
   burst on joint 6E, b108:01E02380/25B0 on joint 6C or 6E); scene code from the timer */

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
} Fx_b108_01E028F0;

typedef struct {
    u8 pad0[0x10];
    f32 sx, sy, sz;
    u8 pad1C[4];
    f32 x20, y20, z20;
    u8 pad2C[0x80 - 0x2C];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 h[8];
    } r;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b108_01E028F0 fx[150];
    u8 pad4440[0x30];
    Vec4f row[10][50];
    u8 pad63B0[0x6560 - 0x63B0];
    s32 tex[2];
    u8 pad6568[0x18];
    s32 count;
    u8 pad6584[8];
    s32 ot;
    u8 pad6590[0x696C - 0x6590];
    s16 j6C;
    s16 j6E;
    s16 j70;
    u8 pad6972[8];
    s16 cam;
    u8 pad697C[0x10];
    s16 jit16[30];
    u8 pad69C8[0x6AE0 - 0x69C8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 pad6BE6[0x6CE8 - 0x6BE6];
    u8 crd[0x178];
} Scene_b108_01E028F0;

static void func_01E03130_b108();

static s32 func_01E028F0_b108(s32 arg0, s32 id) {
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
    extern void func_01E016D0_b108();
    extern void b108_01E03430();
    Scene_b108_01E028F0 *g = (Scene_b108_01E028F0 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x6E60);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 365;
        g->j6C = func_001F5560(func_001F53A0(), 0x67, 1);
        g->j6E = func_001F5560(func_001F53A0(), 1, 0);
        g->j70 = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        g->tex260[0] = func_00202BF0(4, 0);
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 60 - 30;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 15;
        }
        return 0;
    }
    func_01E016D0_b108(g, 0);
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
            if (g->fx[k].fn == (s32 (*)())func_01E01B60_b108) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->r.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[1];
                g->hB8 = 6;
                g->hC0 = g->fx[k].h0A;
                g->x20 = g->fx[k].pos.x;
                g->y20 = g->fx[k].pos.y;
                g->z20 = g->fx[k].pos.z;
                func_01E01180_b108((void *)g, (void *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01CF0_b108) {
                func_01E00DF0_b108((Obj_b108_01E00DF0 *)g, (Band_b108_01E00DF0 *)&g->fx[k], 0x21, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01EB0_b108) {
                func_01E009A0_b108((Obj_b108_01E009A0 *)g, (Data_b108_01E009A0 *)&g->fx[k], 0x21,
                                   g->row[g->fx[k].h50][0]);
                func_01E009A0_b108((Obj_b108_01E009A0 *)g, (Data_b108_01E009A0 *)&g->fx[k], 0x21,
                                   g->row[g->fx[k].h50][49]);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02010_b108) {
                g->tex88 = g->tex260[15];
                g->r.h[0] = 1;
                g->r.h[1] = 0x10;
                g->r.h[2] = 0x1F;
                g->r.h[3] = 1;
                func_00106080(rm2, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->r.rm = *(Vec4f *)rm2;
                g->r.h[2] = 1;
                g->x20 = 0.0f;
                g->y20 = 0.0f;
                g->z20 = 0.0f;
                g->hBE = 1;
                b108_01E03430(g, &g->fx[k], g->row[g->fx[k].h50], 0);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021B0_b108) {
                g->tex88 = g->tex[0];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->r.rm = *(Vec4f *)rm3;
                g->hB8 = 1;
                g->hBE = 0;
                func_001F5620(func_001F53A0(), g->j6E, &v);
                func_01E03130_b108(g, &g->fx[k], 0x20, &g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02380_b108) {
                if (g->fx[k].h50 == 0) {
                    func_001F5620(func_001F53A0(), g->j6C, &v);
                }
                if (g->fx[k].h50 == 1) {
                    func_001F5620(func_001F53A0(), g->j6E, &v);
                }
                func_01E009A0_b108((Obj_b108_01E009A0 *)g, (Data_b108_01E009A0 *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E025B0_b108) {
                if (g->fx[k].h50 == 0) {
                    func_001F5620(func_001F53A0(), g->j6C, &v);
                }
                if (g->fx[k].h50 == 1) {
                    func_001F5620(func_001F53A0(), g->j6E, &v);
                    v.y -= 1.5f;
                }
                func_01E00DF0_b108((Obj_b108_01E00DF0 *)g, (Band_b108_01E00DF0 *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E027D0_b108) {
                func_01E009A0_b108((Obj_b108_01E009A0 *)g, (Data_b108_01E009A0 *)&g->fx[k], 0x21, g->fx[k].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 205) {
        return 1;
    }
    if (g->frame == 350) {
        return 4;
    }
    if (g->frame == 310) {
        return 2;
    }
    if (g->frame > 215 && g->frame < 305) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b108:01E02FF0, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b108_01E02FF0 {
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
} Slot_b108_01E02FF0;

typedef struct Obj_b108_01E02FF0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b108_01E02FF0 slots[0x96];
    u8 padB[0x2144];
    u8 rgba[4];
    u8 padC[0x554];
    s16 fB2B0;
} Obj_b108_01E02FF0;

static s32 func_01E02FF0_b108(Obj_b108_01E02FF0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b108_01E02FF0 *s = NULL;
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

/* shape b108:01E03130, 192 insns: b756:01E061D0 family burst draw: two-colour packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles -(0x5A + 90 + 20 i) between radii f4C and f48 (g+0x6CE8), each with its frame from the scene table (g+0x698C) through func_00106080 into the rect, depth-tested into g+0x658C */

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
} Obj_b108_01E03130;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x658C - 0xC0];
    s32 ot;
    u8 pad6590[0x698C - 0x6590];
    s16 frames[18];
    u8 pad69B0[0x6CE8 - 0x69B0];
    u8 trig[1];
} Game_b108_01E03130;

static void func_01E03130_b108(Game_b108_01E03130 *g, Obj_b108_01E03130 *o, s32 mode, Vec4f *in) {
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
        func_00106080(rm, 0x14, g->frames[i], 0);
        g->rect = *(Vec4f *)rm;
        func_00108500(p, &g->rect, g->frame);
        s = -(o->ang + a + 90);
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        t = o->ang + 20;
        s = -(a + t + 90);
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

/* shape b108:01E03430 (B108PAINT_RAIN21), 730 insns, 1 copy: B411PAINT_RAIN12's beam (b411:01E036C0) with the point
   copies written inline, alpha down by col0.a/(3n), width down by w0/(8n) */

typedef struct {
    f32 x, y, z, w;
} Vec_b108_01E03430;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b108_01E03430;

typedef struct {
    u8 r, g, b, a;
} Col_b108_01E03430;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b108_01E03430;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b108_01E03430 c;
        u64 st;
        Xyz_b108_01E03430 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b108_01E03430;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b108_01E03430;

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
    Col_b108_01E03430 col0;
    Col_b108_01E03430 col1;
} Beam_b108_01E03430;

static inline Vec_b108_01E03430 spline_b108_01E03430(Vec_b108_01E03430 *p, s32 type, f32 t) {
    Vec_b108_01E03430 r;
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

static void func_01E03430_b108(Ctx_b108_01E03430 *c, Beam_b108_01E03430 *an, Vec_b108_01E03430 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b108_01E03430 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b108_01E03430 ab[2];
    Vec_b108_01E03430 ctrl[4];
    Vec_b108_01E03430 prev;
    Vec_b108_01E03430 q[4];
    Vec_b108_01E03430 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b108_01E03430 pkt __attribute__((aligned(8)));
    Col_b108_01E03430 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b108_01E03430 *p;
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
                    ab[0] = spline_b108_01E03430(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b108_01E03430(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b108_01E03430(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b108_01E03430(ctrl, 0, t);
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
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
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
