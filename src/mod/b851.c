#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b851(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00120_b851(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

/* shape b489:01E00240 (LkPrim_SortLineParticle), 853 insns, 55 copies: each live particle drawn as a camera-facing
   line quad from its position back along its direction (or straight down), texture-animated */

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b489_01E00240;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b489_01E00240;

typedef struct {
    UV_b489_01E00240 uv;
    Xyz_b489_01E00240 xyz;
} Vtx_b489_01E00240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b489_01E00240 v[4];
    u8 tail[0x20];
} Pkt_b489_01E00240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 age;
} Part_b489_01E00240;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    u8 pad28[4];
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b489_01E00240;

#define UV_b489_01E00240(k) ((UV_b489_01E00240 *)(s32)&pkt.v[k].uv)

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E002E0_b851(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_0020D070(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C60(f32);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f t;
    Xyz_b489_01E00240 q[2];
    Pkt_b489_01E00240 pkt __attribute__((aligned(8)));
    f32 dep[2];
    s32 i;
    f32 w;
    f32 dx;
    f32 dy;

    ((Pkt_b489_01E00240 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->tag = 9;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->r;
    pkt.g = e->g;
    pkt.b = e->b;
    pkt.a = e->a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
        UV_b489_01E00240(0)->u = e->u << 4;
        UV_b489_01E00240(0)->v = e->v << 4;
        UV_b489_01E00240(1)->u = e->u << 4;
        UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
        UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(2)->v = e->v << 4;
        UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
    }
    for (i = 0; i < e->count; i++) {
        if (e->parts[i].age >= 0) {
            if (e->parts[i].a < e->a) {
                pkt.a = e->parts[i].a;
            } else {
                pkt.a = e->a;
            }
            if (func_00104520(e->flags, 3) == 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->u = e->u0 + e->w * (e->parts[i].frame % (e->tw / e->w));
                    e->v = e->v0 + e->h * (e->parts[i].frame / (e->tw / e->w));
                } else {
                    e->u = e->u0 + e->w * (e->parts[i].frame / (e->th / e->h));
                    e->v = e->v0 + e->h * (e->parts[i].frame % (e->th / e->h));
                }
                ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
                UV_b489_01E00240(0)->u = e->u << 4;
                UV_b489_01E00240(0)->v = e->v << 4;
                UV_b489_01E00240(1)->u = e->u << 4;
                UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
                UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(2)->v = e->v << 4;
                UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
            }
            if (func_00104520(e->flags, 0x1E) != 0) {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y - e->len;
                t.z = e->parts[i].z;
            } else {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y;
                t.z = e->parts[i].z;
                func_0020D070(&t);
                t.x *= -e->len;
                t.y *= -e->len;
                t.z *= -e->len;
                t.x += e->parts[i].x;
                t.y += e->parts[i].y;
                t.z += e->parts[i].z;
            }
            if (func_00205440(&e->parts[i], cam->view, &q[0], &dep[0]) != 0 && func_00101600(&q[0]) != 0) {
                e->flags |= 0x100000;
            }
            if (func_00205440(&t, cam->view, &q[1], &dep[1]) != 0 && func_00101600(&q[1]) != 0) {
                e->flags |= 0x200000;
            }
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0) {
                dx = func_001A6970(q[0].x - q[1].x);
                dy = func_001A6970(q[0].y - q[1].y);
                w = func_001A6C60(dx * dx + dy * dy);
                w = w * e->width / e->len;
                if (dx > dy) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = q[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = q[1].x;
                    pkt.v[0].xyz.y = (u32)(q[0].y - w);
                    pkt.v[1].xyz.y = (u32)(q[1].y - w);
                    pkt.v[2].xyz.y = (u32)(q[0].y + w);
                    pkt.v[3].xyz.y = (u32)(q[1].y + w);
                } else {
                    pkt.v[0].xyz.x = (u32)(q[0].x - w);
                    pkt.v[1].xyz.x = (u32)(q[1].x - w);
                    pkt.v[2].xyz.x = (u32)(q[0].x + w);
                    pkt.v[3].xyz.x = (u32)(q[1].x + w);
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = q[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = q[1].y;
                }
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = q[0].z;
                if (func_00104520(e->flags, 0) != 0) {
                    func_00208CB0(&pkt, 0xA | ((s64)e->u << 4) | ((s64)(e->u + e->w - 1) << 14) |
                                            ((s64)e->v << 24) | ((s64)(e->v + e->h - 1) << 34));
                }
                func_00208700(&pkt, e->texture, 1);
                if (func_00104520(e->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1]) / 2.0f));
                }
            }
            e->flags &= 0xFFCFFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->parts[i].age++;
            if (e->parts[i].age % e->rate == 0) {
                e->parts[i].frame++;
                if (e->nframes == e->parts[i].frame) {
                    e->parts[i].frame = 0;
                }
            }
        }
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E035A0;

typedef struct {
    s32 type;
    s32 id;
    u8 pad08[4];
    f32 height;
    u8 pad10[0x10];
    f32 inner;
    f32 a24;
    f32 a28;
    u8 pad2C[4];
    f32 outer;
    f32 b34;
    f32 b38;
    u8 pad3C[4];
    Vec_b001_01E035A0 in[30];
    Vec_b001_01E035A0 out[30];
} Ring_b001_01E035A0;

static s32 func_01E01040_b851(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
    extern s32 func_001A22C0(f32);
    Vec_b001_01E035A0 *in;
    s32 i;
    f32 span;
    f32 top;
    f32 span2;
    f32 top2;
    f32 angle;
    s32 r;

    o->type = type;
    o->height = height;
    o->inner = inner;
    o->outer = outer;
    if (func_00104520(o->id, 0x1D) != 0) {
        o->a24 = 0.0f;
        top = y + height;
        o->a28 = y;
        o->b34 = 0.0f;
        span = 2.0f * height;
        o->b38 = top;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].y = inner * func_0020B730(angle);
            o->in[i].z = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].y = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].z = top + ((r % func_001A22C0(span) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].z = top;
            }
        }
    } else {
        top2 = y + height;
        o->a24 = y;
        o->a28 = 0.0f;
        o->b34 = top2;
        span2 = 2.0f * height;
        o->b38 = 0.0f;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].z = inner * func_0020B730(angle);
            o->in[i].y = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].z = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].y = top2 + ((r % func_001A22C0(span2) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].y = top2;
            }
        }
    }
    return 0;
}

/* shape b001:01E03860, 316 insns, 72 copies: draws the 30-segment ring built by b001:01E035A0.
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_b851) and needs that helper
   defined EARLIER in the same file as a static function: MWCC keeps &pkt in a0 across the call only then.
   The static copy below is that helper (identical code to ovl-matched/b000_01E00100.c). */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E03860;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E03860;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E03860 v[4];
    u8 tail[0x20];
} Pkt_b001_01E03860;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E03860;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E03860 color;
    u8 pad0C[4];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad18[8];
    Vec_b001_01E03860 p0;
    Vec_b001_01E03860 p1;
    Vec_b001_01E03860 in[30];
    Vec_b001_01E03860 out[30];
} Ring_b001_01E03860;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E03860;



static inline void init_b001_01E03860(Pkt_b001_01E03860 *p) {
    p->count = 0x34;
    p->tag = 0xC;
    p->regs = ((u64)0x4214 << 32) | 0x21421421;
    p->pad = 0;
}

static s32 func_01E01300_b851(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    f32 depth[4];
    Pkt_b001_01E03860 pkt;
    s32 i;
    Pkt_b001_01E03860 *hdr;

    ((Pkt_b001_01E03860 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->pad = 0;
    if (func_00104520(ring->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(ring->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    for (i = 0; i < 30; i++) {
        func_01E00080_b851(&pkt, &ring->color);
        func_00104540(&pkt, &ring->u, 2);
        if (i == 0) {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        } else {
            if (func_00205440(&ring->in[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->out[i - 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        }
        if (i != 29) {
            if (func_00205440(&ring->in[i], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->out[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        } else {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)ring->u << 4) | ((u64)(ring->u + ring->w - 1) << 14) |
                                ((u64)ring->v << 24) | ((u64)(ring->v + ring->h - 1) << 34));
        func_00208700(&pkt, ring->texture, 1);
        if (func_00104520(ring->flags, 0x14) != 0 && func_00104520(ring->flags, 0x15) != 0 &&
            func_00104520(ring->flags, 0x16) != 0 && func_00104520(ring->flags, 0x17) != 0) {
            if (func_00104520(ring->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        ring->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b540:01E00250 (LkPrim_SortSpot), 341 insns, 66 copies: a flat disc drawn as count triangles from the centre
   (the colour and its alpha) to the rim (alpha 0); flags 0x100000..0x400000 record which vertices projected, flag
   bits 0x13/0x12 force the far or the near z */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b540_01E00250;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b540_01E00250 xyz;
} Vtx_b540_01E00250;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b540_01E00250 v[3];
    u8 tail[8];
} Pkt_b540_01E00250;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b540_01E00250;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b540_01E00250;

static s32 func_01E017F0_b851(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f c[3];
    Pkt_b540_01E00250 pkt __attribute__((aligned(8)));
    f32 dep[3];
    f32 step;
    f32 a;
    s32 i;

    step = 6.2831855f / d->count;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->count = 0x13;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->tag = 6;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->regs = 0x414141;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->pad = 0;
    if (func_00104520(d->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(d->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.v[0].r = d->r;
    pkt.v[0].g = d->g;
    pkt.v[0].b = d->b;
    pkt.v[0].a = d->a;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = d->r;
    pkt.v[1].g = d->g;
    pkt.v[1].b = d->b;
    pkt.v[1].a = 0;
    pkt.v[1].q = 1.0f;
    pkt.v[2].r = d->r;
    pkt.v[2].g = d->g;
    pkt.v[2].b = d->b;
    pkt.v[2].a = 0;
    pkt.v[2].q = 1.0f;
    c[0].y = 0.0f;
    c[0].x = 0.0f;
    c[0].z = c[1].z = c[2].z = 0.1f * d->height;
    for (i = 0; i < d->count; i++) {
        if (func_00205440(&c[0], cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
            d->flags |= 0x100000;
        }
        a = step * i;
        c[1].x = d->radius * func_0020B620(a);
        c[1].y = d->radius * func_0020B730(a);
        if (func_00205440(&c[1], cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
            d->flags |= 0x200000;
        }
        if (i == d->count - 1) {
            c[2].x = d->radius;
            c[2].y = 0.0f;
        } else {
            a = step * (i + 1);
            c[2].x = d->radius * func_0020B620(a);
            c[2].y = d->radius * func_0020B730(a);
        }
        if (func_00205440(&c[2], cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
            d->flags |= 0x400000;
        }
        if (func_00104520(d->flags, 0x14) != 0 && func_00104520(d->flags, 0x15) != 0 &&
            func_00104520(d->flags, 0x16) != 0) {
            if (func_00104520(d->flags, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0);
                }
            } else if (func_00104520(d->flags, 0x12) != 0) {
                func_002075F0(&pkt, ot, 0xFFFFFF);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                }
            } else {
                func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                }
            }
        }
        d->flags &= 0xFF8FFFFF;
    }
    return 0;
}

/* shape b000:01E01140, 1595 insns, 70 copies: draws an emitter's particles. Each particle is either a camera-facing
   sprite (strip packet, 9 regs) sized by distance, or with flag 0x1F a quad (12 regs) turned by its own rotation;
   UV or ST frames animate per particle; flag 2 respawns a particle on a circle when its animation wraps.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E01140;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E01140;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E01140;

typedef union {
    UV_b000_01E01140 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b000_01E01140;

typedef struct {
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx1_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx1_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt1_b000_01E01140;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx2_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx2_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt2_b000_01E01140;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b000_01E01140;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E01140 color;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    union {
        struct {
            s16 u, v, w, h;
            s16 u0, v0, tw, th;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Pt_b000_01E01140 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b000_01E01140;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E01140;

#define UV1(k) ((UV_b000_01E01140 *)(s32)&p1.v[k].tc)
#define UV2(k) ((UV_b000_01E01140 *)(s32)&p2.v[k].tc)

static s32 func_01E01D50_b851(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
    extern s32 func_002058D0(void *, s32, void *, void *, f32 *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f c[4];
    Vec4f off;
    Vec4f tmp;
    Vec4f pos;
    Pkt1_b000_01E01140 p1 __attribute__((aligned(8)));
    Pkt2_b000_01E01140 p2 __attribute__((aligned(8)));
    f32 nx;
    f32 ny;
    f32 sx;
    f32 sy;
    s32 i;
    f32 hx;
    f32 hy;
    f32 dz;
    s32 a;

    ((Pkt1_b000_01E01140 *)(s32)&p1)->count = 0x24;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->tag = 9;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->pad = 0;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->count = 0x34;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->tag = 0xC;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (e->r.i.w == e->r.i.h) {
        sy = e->size;
        sx = sy;
    } else if (e->r.i.h < e->r.i.w) {
        sx = e->size;
        sy = sx * ((f32)e->r.i.h / (f32)e->r.i.w);
    } else {
        sy = e->size;
        sx = sy * ((f32)e->r.i.w / (f32)e->r.i.h);
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x44);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x88);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x42);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x48);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x48);
    }
    p1.r = e->color.r;
    p1.g = e->color.g;
    p1.b = e->color.b;
    *(u8 *)(s32)&p1.a = e->color.a;
    p1.q = 1.0f;
    func_01E00080_b851((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
            ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
            UV2(0)->u = e->r.i.u * 16;
            UV2(0)->v = e->r.i.v * 16;
            UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(1)->v = e->r.i.v * 16;
            UV2(2)->u = e->r.i.u * 16;
            UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
        } else {
            p1.v[0].tc.st.s = e->r.f.s;
            p1.v[0].tc.st.t = e->r.f.t;
            p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[1].tc.st.t = e->r.f.t;
            p1.v[2].tc.st.s = e->r.f.s;
            p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[0].tc.st.s = e->r.f.s;
            p2.v[0].tc.st.t = e->r.f.t;
            p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[1].tc.st.t = e->r.f.t;
            p2.v[2].tc.st.s = e->r.f.s;
            p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
        }
    }
    if (func_00104520(e->flags, 0x1C) != 0) {
        func_0020C630(m, &e->rot);
        for (i = 0; i < e->count; i++) {
            tmp.x = e->pts[i].x;
            tmp.y = e->pts[i].y;
            tmp.z = e->pts[i].z;
            func_0020CDD0(&off, m, &tmp);
            e->pts[i].x = off.x;
            e->pts[i].y = off.y;
            e->pts[i].z = off.z;
        }
    }
    nx = -sx;
    ny = -sy;
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->color.a;
        }
        if (func_00104520(e->flags, 3) == 0) {
            if (func_00104520(e->flags, 0) != 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame % (e->r.i.tw / e->r.i.w));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame / (e->r.i.tw / e->r.i.w));
                } else {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame / (e->r.i.th / e->r.i.h));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame % (e->r.i.th / e->r.i.h));
                }
                ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
                ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
                UV2(0)->u = e->r.i.u * 16;
                UV2(0)->v = e->r.i.v * 16;
                UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(1)->v = e->r.i.v * 16;
                UV2(2)->u = e->r.i.u * 16;
                UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                p1.v[0].tc.st.s = e->r.f.s;
                p1.v[0].tc.st.t = e->r.f.t;
                p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[1].tc.st.t = e->r.f.t;
                p1.v[2].tc.st.s = e->r.f.s;
                p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[0].tc.st.s = e->r.f.s;
                p2.v[0].tc.st.t = e->r.f.t;
                p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[1].tc.st.t = e->r.f.t;
                p2.v[2].tc.st.s = e->r.f.s;
                p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&p1, e->texture, 0);
            func_00208700(&p2, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&p1, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
                func_00208CB0(&p2, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&p1, e->texture, 1);
            func_00208700(&p2, e->texture, 1);
        }
        pos.x = e->pts[i].x;
        pos.y = e->pts[i].y;
        pos.z = e->pts[i].z;
        if (func_00104520(e->flags, 0x1A) != 0) {
            dz = -(e->amp * func_0020B550(e->freq * e->pts[i].t));
            pos.z += dz;
        }
        if (func_00104520(e->flags, 0x1F) != 0) {
            func_0020C630(m, &e->rots[i]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx = sx + sx * e->grow * e->pts[i].t;
                hy = sy + sy * e->grow * e->pts[i].t;
                off.x = -hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = -hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            } else {
                off.x = nx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = nx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            }
        } else {
            if (func_00205440(&pos, cam->view, &p1.v[0].xyz, depth) != 0 && func_00101600(&p1.v[0].xyz) != 0) {
                e->flags |= 0xF00000;
            }
            depth[1] = depth[2] = depth[3] = depth[0];
            hx = 20.0f * func_001018E0(sx, depth[0]);
            hy = 20.0f * func_001018E0(sy, depth[0]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx += sx * e->grow * e->pts[i].t;
                hy += sy * e->grow * e->pts[i].t;
            }
            p1.v[1].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[1].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[2].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[2].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[3].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[3].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[0].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[0].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = p1.v[0].xyz.z;
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
                func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
                if (func_00104520(e->flags, 0x13) != 0) {
                    p1.v[0].xyz.z = p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = 0xFFFFFF;
                    if (e->pts[i].t >= 0) {
                        func_002075F0(&p1, obj, 0);
                    }
                } else if (e->pts[i].t >= 0) {
                    func_002075F0(&p1, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
            e->flags &= 0xFF0FFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
                    if (func_00104520(e->flags, 2) != 0) {
                        if (func_00104520(e->flags, 0x1D) != 0) {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = e->radius * func_0020B550(a);
                            e->pts[i].z = func_0019A5C8() % 20;
                            e->pts[i].x = e->radius * func_0020B480(a);
                        } else {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = func_0019A5C8() % 20;
                            e->pts[i].z = e->radius * func_0020B480(a);
                            e->pts[i].x = e->radius * func_0020B550(a);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* shape b851:01E03640 (b851), 1158 insns, 1 copy: b851 scene manager (b557:01E03CB0's form): setup (line-particle
   burst, disc, three rings, three sprays), joints place them, colours flicker at random, sprays rise and respawn,
   burst grows x1.3 and respawns on a sphere, rings regrow; returns 2/1/6/8 by tick */

typedef struct Crd_b851_01E03640 {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b851_01E03640;

typedef struct Disc_b851_01E03640 {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b851_01E03640;

typedef struct Part_b851_01E03640 {
    f32 x, y, z;
    u8 a, d;
    s16 t;
} Part_b851_01E03640;

typedef struct Fx_b851_01E03640 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 rx, ry, rz;
    u8 pad2C[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Part_b851_01E03640 *parts;
    s32 rots;
    s32 f48;
    f32 radius;
    u8 pad50[0xA];
    s16 count;
    s16 nframes;
    s16 rate;
} Fx_b851_01E03640;

typedef struct Emit_b851_01E03640 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    Part_b851_01E03640 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    f32 radius;
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b851_01E03640;

typedef struct Ring_b851_01E03640 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b851_01E03640;

typedef struct Scene_b851_01E03640 {
    Crd_b851_01E03640 c0;
    Crd_b851_01E03640 c1;
    Emit_b851_01E03640 emit;
    Part_b851_01E03640 ep[0x100];
    Crd_b851_01E03640 c2;
    Crd_b851_01E03640 c3;
    Disc_b851_01E03640 disc;
    Crd_b851_01E03640 cB[3];
    Ring_b851_01E03640 ring[3];
    Crd_b851_01E03640 c4;
    Fx_b851_01E03640 fx1;
    Part_b851_01E03640 p1[0x80];
    Crd_b851_01E03640 c5;
    Fx_b851_01E03640 fx2;
    Part_b851_01E03640 p2[0x80];
    Crd_b851_01E03640 c6;
    Fx_b851_01E03640 fx3;
    Part_b851_01E03640 p3[0x80];
    s32 timer;
    s32 t;
    s32 code;
    s32 j0;
    s32 j1;
    s32 j2;
    u8 fade;
    u8 pad39D9[7];
} Scene_b851_01E03640;

static s32 func_01E03640_b851(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001F6D00(s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern void func_001043F0(void *, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern s32 b851_01E00120(void *, s32, f32);
    extern s32 b851_01E002E0();
    extern s32 b851_01E01040(void *, s32, f32, f32, f32, f32);
    extern s32 b851_01E01300();
    extern s32 b851_01E017F0();
    extern s32 b851_01E01D50();
    Scene_b851_01E03640 *g = (Scene_b851_01E03640 *)arg0;
    s32 ot;
    Vec4f w;
    Vec4f v[2];
    s32 tex[4];
    s32 i;
    s32 a;
    f32 r;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x39E0);
        func_00103890(&g->c0);
        func_00103890(&g->c2);
        func_00103890(&g->c1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->cB[i]);
        }
        func_00103890(&g->c3);
        func_00103890(&g->c4);
        func_00103890(&g->c5);
        func_00103890(&g->c6);
        g->j0 = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->j1 = func_001F5560(func_001F53A0(), 0x85, 0);
        g->j2 = func_001F5560(func_001F53A0(), 0x84, 0);
        g->timer = 0x178;
        g->t = 1;
        g->code = code;
        g->fade = 0x80;
        g->disc.flags = 0x80000;
        g->disc.r = 0x80;
        g->disc.g = 0x80;
        g->disc.b = 0x80;
        g->disc.a = 0xFF;
        g->disc.radius = 30.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        func_00103260(tex, 0xF);
        g->emit.tex = tex[0];
        g->emit.flags = 3;
        g->emit.r = 0x80;
        g->emit.g = 0x80;
        g->emit.b = 0x80;
        g->emit.a = 0x80;
        g->emit.width = 0.2f;
        g->emit.len = 10.0f;
        g->emit.u = 0xB0;
        g->emit.v = 0x60;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0xB0;
        g->emit.v0 = 0x60;
        g->emit.tw = 0x100;
        g->emit.th = 0x100;
        g->emit.parts = g->ep;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 1;
        g->emit.rate = 0;
        b851_01E00120(&g->emit, 0xC, 3.0f);
        for (i = 0; i < 3; i++) {
            g->ring[i].flags = 0;
            g->ring[i].u = 0x8E;
            g->ring[i].v = 0;
            g->ring[i].w = 0x20;
            g->ring[i].h = 0x80;
            g->ring[i].r = 0xD0;
            g->ring[i].g = 0x70;
            g->ring[i].b = 0xA0;
            g->ring[i].a = 0x80;
            b851_01E01040(&g->ring[i], tex[0], 11.5f, 12.5f, 0.0f, 0.0f);
        }
        g->fx1.tex = tex[0];
        g->fx1.flags = 0x70000001;
        g->fx1.r = 0x80;
        g->fx1.g = 0x80;
        g->fx1.b = 0x80;
        g->fx1.a = 0;
        g->fx1.size = 2.0f;
        g->fx1.rx = 0;
        g->fx1.ry = 0;
        g->fx1.rz = 0;
        g->fx1.u = 0;
        g->fx1.v = 0xE4;
        g->fx1.w = 0xA;
        g->fx1.h = 0xA;
        g->fx1.u0 = 0;
        g->fx1.v0 = 0xE4;
        g->fx1.tw = 0x100;
        g->fx1.th = 0x100;
        g->fx1.parts = g->p1;
        g->fx1.rots = 0;
        g->fx1.f48 = 0;
        g->fx1.radius = 2.0f;
        g->fx1.count = 0x80;
        g->fx1.nframes = 2;
        g->fx1.rate = 0;
        for (i = 0; i < g->fx1.count; i++) {
            g->p1[i].t = 0;
            g->p1[i].a = 0;
            g->p1[i].d = 0;
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (func_0019A5C8() % 40 - 20);
            g->p1[i].z = r * func_0020B480(a);
            g->p1[i].x = r * func_0020B550(a);
            g->p1[i].y = 0.1f * -(f32)(func_0019A5C8() % 500);
        }
        func_00103290(tex, 0);
        g->fx2.tex = tex[0];
        g->fx2.flags = 0x70000003;
        g->fx2.r = 0x80;
        g->fx2.g = 0x80;
        g->fx2.b = 0x80;
        g->fx2.a = 0x80;
        g->fx2.size = 2.5f;
        g->fx2.rx = 0;
        g->fx2.ry = 0x400;
        g->fx2.rz = 0;
        g->fx2.u = 0;
        g->fx2.v = 0x30;
        g->fx2.w = 0x20;
        g->fx2.h = 0x20;
        g->fx2.u0 = 0;
        g->fx2.v0 = 0x30;
        g->fx2.tw = 0x100;
        g->fx2.th = 0x100;
        g->fx2.parts = g->p2;
        g->fx2.rots = 0;
        g->fx2.f48 = 0;
        g->fx2.radius = 2.0f;
        g->fx2.count = 0x80;
        g->fx2.nframes = 8;
        g->fx2.rate = 100;
        for (i = 0; i < g->fx2.count; i++) {
            g->p2[i].t = 1;
            g->p2[i].a = 0;
            g->p2[i].d = func_0019A5C8() % 8;
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (func_0019A5C8() % 60 - 30);
            g->p2[i].z = r * func_0020B480(a);
            g->p2[i].x = r * func_0020B550(a);
            g->p2[i].y = 0.1f * (func_0019A5C8() % 400 - 200);
        }
        g->fx3.tex = tex[0];
        g->fx3.flags = 0x70000003;
        g->fx3.r = 0x80;
        g->fx3.g = 0x80;
        g->fx3.b = 0x80;
        g->fx3.a = 0x80;
        g->fx3.size = 3.5f;
        g->fx3.rx = 0;
        g->fx3.ry = 0x400;
        g->fx3.rz = 0;
        g->fx3.u = 0;
        g->fx3.v = 0x30;
        g->fx3.w = 0x20;
        g->fx3.h = 0x20;
        g->fx3.u0 = 0;
        g->fx3.v0 = 0x30;
        g->fx3.tw = 0x100;
        g->fx3.th = 0x100;
        g->fx3.parts = g->p3;
        g->fx3.rots = 0;
        g->fx3.f48 = 0;
        g->fx3.radius = 2.0f;
        g->fx3.count = 0x80;
        g->fx3.nframes = 8;
        g->fx3.rate = 100;
        for (i = 0; i < g->fx3.count; i++) {
            g->p3[i].t = 1;
            g->p3[i].a = 0;
            g->p3[i].d = func_0019A5C8() % 8;
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (func_0019A5C8() % 60 - 30);
            g->p3[i].z = r * func_0020B480(a);
            g->p3[i].x = r * func_0020B550(a);
            g->p3[i].y = 0.1f * (func_0019A5C8() % 400 - 200);
        }
        g->cB[0].scale.z = 0.0f;
        g->cB[0].scale.y = 0.0f;
        g->cB[0].scale.x = 0.0f;
        g->cB[1].scale.z = 0.5f;
        g->cB[1].scale.y = 0.5f;
        g->cB[1].scale.x = 0.5f;
        g->cB[2].scale.z = 1.0f;
        g->cB[2].scale.y = 1.0f;
        g->cB[2].scale.x = 1.0f;
        g->c5.scale.z = 3.0f;
        g->c5.scale.y = 3.0f;
        g->c5.scale.x = 3.0f;
        g->c6.scale.z = 5.0f;
        g->c6.scale.y = 5.0f;
        g->c6.scale.x = 5.0f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j1, &v[0]);
    func_001F5620(func_001F53A0(), g->j2, &v[1]);
    func_001F5620(func_001F53A0(), g->j1, &g->c4.pos);
    func_00103DB0(&v[0], &v[1], g->c4.rot);
    func_001F53C0(1, func_001F53A0(), &g->c5.pos);
    func_001F53C0(1, func_001F5380(), &g->c6.pos);
    g->c6.rot[0] = 0x8000;
    func_001F53C0(1, func_001F5380(), &g->c3.pos);
    func_001F53C0(1, func_001F5380(), &g->c1.pos);
    for (i = 0; i < 3; i++) {
        func_001F53C0(1, func_001F5380(), &g->cB[i].pos);
    }
    func_001038D0(&g->c0);
    func_001039A0(&g->c2);
    func_001038D0(&g->c1);
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->cB[i]);
    }
    func_001039A0(&g->c3);
    func_001038D0(&g->c4);
    func_001038D0(&g->c5);
    func_001038D0(&g->c6);
    if (g->t >= 0x168) {
        func_001032C0(&g->fade, 0x80, 4);
    } else {
        func_00103470(&g->fade, 0x20, 4);
    }
    func_001F6D00(g->fade);
    g->disc.r = g->ring[0].r = g->ring[1].r = g->ring[2].r = g->emit.r = g->fx1.r = func_0019A5C8() % 128;
    g->disc.g = g->ring[0].g = g->ring[1].g = g->ring[2].g = g->emit.g = g->fx1.g = func_0019A5C8() % 128;
    g->disc.b = g->ring[0].b = g->ring[1].b = g->ring[2].b = g->emit.b = g->fx1.b = func_0019A5C8() % 128;
    b851_01E01D50(ot, &g->fx1, &g->c4);
    if (g->t >= 0x32) {
        func_001032C0(&g->fx1.a, 0x80, 8);
    }
    for (i = 0; i < g->fx1.count; i++) {
        if (g->p1[i].t >= 0) {
            g->p1[i].y += 3.0f;
            func_00103470(&g->p1[i].a, 0, 8);
            if (g->p1[i].y < 50.0f) {
                g->p1[i].z *= 1.2f;
                g->p1[i].x *= 1.2f;
            }
            if (!(g->p1[i].y < 50.0f)) {
                a = func_0019A5C8() % 0x10000;
                r = 0.1f * (func_0019A5C8() % 40 - 20);
                g->p1[i].z = r * func_0020B480(a);
                g->p1[i].x = r * func_0020B550(a);
                g->p1[i].y = 0.1f * -(f32)(func_0019A5C8() % 30);
                g->p1[i].a = 0x80;
            }
        }
    }
    if (g->t >= 0x50) {
        b851_01E01D50(ot, &g->fx2, &g->c5);
        if (g->t >= 0x168) {
            func_00103470(&g->fx2.a, 0, 8);
        }
        for (i = 0; i < g->fx2.count; i++) {
            if (g->p2[i].t >= 0) {
                g->p2[i].y += 1.0f;
                if (g->p2[i].a != 0) {
                    if (g->p2[i].y > 0.0f) {
                        func_00103470(&g->p2[i].a, 0, 8);
                    } else {
                        func_001032C0(&g->p2[i].a, 0x80, 8);
                    }
                }
                if (g->p2[i].y < 20.0f) {
                    g->p2[i].z *= 1.05f;
                    g->p2[i].x *= 1.05f;
                }
                if (!(g->p2[i].y < 20.0f)) {
                    a = func_0019A5C8() % 0x10000;
                    r = 0.1f * (func_0019A5C8() % 60 - 30);
                    g->p2[i].z = r * func_0020B480(a);
                    g->p2[i].x = r * func_0020B550(a);
                    g->p2[i].y = -20.0f + 0.1f * (func_0019A5C8() % 60 - 30);
                    g->p2[i].a = 1;
                    g->p2[i].d = func_0019A5C8() % 8;
                }
            }
        }
        b851_01E01D50(ot, &g->fx3, &g->c6);
        if (g->t >= 0x168) {
            func_00103470(&g->fx3.a, 0, 8);
        }
        for (i = 0; i < g->fx3.count; i++) {
            if (g->p3[i].t >= 0) {
                g->p3[i].y += 1.0f;
                if (g->p3[i].a != 0) {
                    if (g->p3[i].y > 0.0f) {
                        func_00103470(&g->p3[i].a, 0, 8);
                    } else {
                        func_001032C0(&g->p3[i].a, 0x80, 8);
                    }
                }
                if (g->p3[i].y < 20.0f) {
                    g->p3[i].z *= 1.05f;
                    g->p3[i].x *= 1.05f;
                }
                if (!(g->p3[i].y < 20.0f)) {
                    a = func_0019A5C8() % 0x10000;
                    r = 0.1f * (func_0019A5C8() % 60 - 30);
                    g->p3[i].z = r * func_0020B480(a);
                    g->p3[i].x = r * func_0020B550(a);
                    g->p3[i].y = -20.0f + 0.1f * (func_0019A5C8() % 60 - 30);
                    g->p3[i].a = 1;
                    g->p3[i].d = func_0019A5C8() % 8;
                }
            }
        }
    }
    if (g->t >= 0x7B) {
        b851_01E017F0(ot, &g->disc, &g->c3);
        if (g->t >= 0x168) {
            func_00103470(&g->disc.a, 0, 0x10);
        } else if (g->t % 2 == 0) {
            g->disc.a = 0xFF;
        } else {
            g->disc.a = 0x80;
        }
    }
    if (g->t >= 0x7B) {
        for (i = 0; i < 3; i++) {
            b851_01E01300(ot, &g->ring[i], &g->cB[i]);
            func_00103470(&g->ring[i].a, 0, 8);
            if (func_001033D0(&g->cB[i], 2.0f, 0.1f) == 0) {
                g->cB[i].scale.x = g->cB[i].scale.y = g->cB[i].scale.z = 0.1f;
                g->cB[i].rot[0] = func_0019A5C8() % 0x10000;
                g->cB[i].rot[1] = func_0019A5C8() % 0x10000;
                g->cB[i].rot[2] = func_0019A5C8() % 0x10000;
                if (g->t < 0x168) {
                    g->ring[i].a = 0x80;
                }
            }
        }
        b851_01E002E0(ot, &g->emit, &g->c1);
        if (g->t > 0x168) {
            func_00103470(&g->emit.a, 0, 8);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->ep[i].t >= 0) {
                g->ep[i].x *= 1.3f;
                g->ep[i].y *= 1.3f;
                g->ep[i].z *= 1.3f;
                if (g->ep[i].t > 16) {
                    func_001043F0(&w, 1.0f);
                    g->ep[i].y = w.y;
                    g->ep[i].z = w.z;
                    g->ep[i].x = w.x;
                    g->ep[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x168) {
        return 2;
    }
    if (g->t == 0x71) {
        return 1;
    }
    if (g->t >= 0x7B && g->t < 0x168) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
