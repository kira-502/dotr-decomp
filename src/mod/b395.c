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

static void func_01E00080_b395(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b395(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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
static s32 func_01E002E0_b395(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
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

static s32 func_01E01040_b395(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_b395) and needs that helper
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

static s32 func_01E01300_b395(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_b395(&pkt, &ring->color);
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

/* shape b007:01E017F0, 355 insns, 16 copies: draws a sprite as two crossed quads: 8 corners (from a template, sized by
   two width/height pairs) rotated by the sprite's rotation, projected per quad, depth-sorted unless flag 0x13 */

typedef struct {
    u8 b, g, r, a;
} Src_b007_01E017F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b007_01E017F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b007_01E017F0 v[4];
    u8 tail[0x20];
} Pkt_b007_01E017F0;

typedef struct {
    f32 x, y, z, w;
} Vec_b007_01E017F0;

typedef struct {
    Vec_b007_01E017F0 v[8];
} Quad8_b007_01E017F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b007_01E017F0 color;
    f32 w;
    f32 h;
    f32 w2;
    f32 h2;
    u8 pad1C[4];
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad28[8];
    Vec_b007_01E017F0 rot;
} Spr_b007_01E017F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b007_01E017F0;

static s32 func_01E017F0_b395(s32 obj, Spr_b007_01E017F0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E04B80_b395;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Pkt_b007_01E017F0 pkt;
    s32 i;

    in = D_01E04B80_b395;
    in.v[0].x = -spr->w;
    in.v[0].y = spr->h;
    in.v[1].x = spr->w;
    in.v[1].y = spr->h;
    in.v[2].x = -spr->w;
    in.v[2].y = -spr->h;
    in.v[3].x = spr->w;
    in.v[3].y = -spr->h;
    in.v[4].x = -spr->h2;
    in.v[4].y = spr->w2;
    in.v[5].x = spr->h2;
    in.v[5].y = spr->w2;
    in.v[6].x = -spr->h2;
    in.v[6].y = -spr->w2;
    in.v[7].x = spr->h2;
    in.v[7].y = -spr->w2;
    func_0020C630(m, &spr->rot);
    for (i = 0; i < 8; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b395((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    func_00104540(&pkt, &spr->u, 0);
    for (i = 0; i < 2; i++) {
        if (func_00205440(&out[i * 4], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        if (func_00205440(&out[i * 4 + 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        if (func_00205440(&out[i * 4 + 2], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        if (func_00205440(&out[i * 4 + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)spr->u << 4) | ((u64)(spr->u + spr->tw - 1) << 14) |
                                ((u64)spr->v << 24) | ((u64)(spr->v + spr->th - 1) << 34));
        func_00208700(&pkt, spr->texture, 1);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
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

static s32 func_01E01D80_b395(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

typedef struct V4_b000_01E032C0 {
    f32 x, y, z, w;
} V4_b000_01E032C0;

typedef struct Rnd_b000_01E032C0 {
    s32 a, b, c, d;
} Rnd_b000_01E032C0;

typedef struct Obj_b000_01E032C0 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    V4_b000_01E032C0 v[4];
    Rnd_b000_01E032C0 r[64];
} Obj_b000_01E032C0;

typedef struct Tbl_b000_01E032C0 {
    V4_b000_01E032C0 v[4];
} Tbl_b000_01E032C0;

static s32 func_01E022E0_b395(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E04C00_b395;
    Tbl_b000_01E032C0 tbl = D_01E04C00_b395;
    s32 flag;
    s32 n;
    s32 i;

    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl.v[i].x;
        obj->v[i].y = obj->scale * tbl.v[i].y;
        obj->v[i].z = obj->scale * tbl.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].a = func_0019A5C8() % 0x10000;
        obj->r[i].b = func_0019A5C8() % 0x10000;
        obj->r[i].c = func_0019A5C8() % 0x10000;
    }
    return 0;
}

/* shape b000:01E03420, 387 insns, 68 copies: draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E03420;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E03420;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E03420;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E03420 v[4];
    u8 tail[0x20];
} Pkt_b000_01E03420;

typedef struct {
    f32 x, y, z, w;
} Vec_b000_01E03420;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E03420 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec_b000_01E03420 p[4];
    Vec_b000_01E03420 rot[1];
} Spr_b000_01E03420;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E03420;

static s32 func_01E02440_b395(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b000_01E03420 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b000_01E03420 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b395((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b000_01E03420 *)(s32)&pkt)->count |= 0x800;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = spr->rect.f.s;
        pkt.v[0].tc.st.t = spr->rect.f.t;
        pkt.v[1].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[1].tc.st.t = spr->rect.f.t;
        pkt.v[2].tc.st.s = spr->rect.f.s;
        pkt.v[2].tc.st.t = spr->rect.f.t + spr->rect.f.h;
        pkt.v[3].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[3].tc.st.t = spr->rect.f.t + spr->rect.f.h;
    }
    for (i = 0; i < n[0]; i++) {
        func_0020C630(m, &spr->rot[i]);
        func_0020CDD0(&out, m, &spr->p[0]);
        if (func_00205440(&out, cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        func_0020CDD0(&out, m, &spr->p[1]);
        if (func_00205440(&out, cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        func_0020CDD0(&out, m, &spr->p[2]);
        if (func_00205440(&out, cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        func_0020CDD0(&out, m, &spr->p[3]);
        if (func_00205440(&out, cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208700(&pkt, spr->texture, 0);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else if (func_00104520(spr->flags, 0x12) != 0) {
                func_002075F0(&pkt, obj, 0xFFFFFF);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E02A50_b395(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

/* shape b117:01E00270, 624 insns, 28 copies (-O3,p): LkEFF_SortLaser: draws a laser trail through cnt points (0x10
   bytes each), every point aged first: each piece between two projected points is four textured quads (above, below,
   right, left of the line) as wide as func_001018E0(base, depth), skipped unless both corners are on screen; alpha =
   min(object alpha, point alpha), first piece fades in from 0. Colour from the module helper b117:01E00080. Both
   spilled parameters are aligned(8) to put their homes at 0xE8/0xE0. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b117_01E00270;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b117_01E00270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b117_01E00270 uv;
    Xyz_b117_01E00270 xyz;
} Vtx_b117_01E00270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b117_01E00270 v[4];
    u8 tail[0x20];
} Pkt_b117_01E00270;

typedef struct {
    s16 u, v, w, h;
} Rect_b117_01E00270;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b117_01E00270 rect;
    u8 pad18[0xC];
    s16 tick;
    u8 pad26[2];
    s16 n1;
    s16 n2;
} Laser_b117_01E00270;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b117_01E00270;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b117_01E00270;

#pragma optimization_level 3

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E02BA0_b395(s32 ot __attribute__((aligned(8))), Laser_b117_01E00270 *o, Pt_b117_01E00270 *pts, Cam_b117_01E00270 *cam __attribute__((aligned(8)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b117_01E00270 s[2];
    Vec4f w;
    Pkt_b117_01E00270 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    s32 j;
    s32 cnt;
    f32 w0;
    f32 w1;

    if (func_00104520(o->flags, 0x1F) != 0) {
        cnt = o->n1;
    } else {
        cnt = o->n2;
    }
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b395((void *)&pkt, (void *)o->color);
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
    for (i = 0; i < cnt + 1; i++) {
        pts[i].age++;
    }
    for (i = 1; i < cnt; i++) {
        w.x = pts[i - 1].x;
        w.y = pts[i - 1].y;
        w.z = pts[i - 1].z;
        if (func_00205440(&w, cam->view, &s[0], &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        w.x = pts[i].x;
        w.y = pts[i].y;
        w.z = pts[i].z;
        if (func_00205440(&w, cam->view, &s[1], &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            w0 = func_001018E0(o->base, depth[0]);
            w1 = func_001018E0(o->base, depth[1]);
            if (o->a >= pts[i - 1].a) {
                pkt.v[0].a = pkt.v[2].a = pts[i - 1].a;
            } else {
                pkt.v[0].a = pkt.v[2].a = o->a;
            }
            if (o->a >= pts[i].a) {
                pkt.v[1].a = pkt.v[3].a = pts[i].a;
            } else {
                pkt.v[1].a = pkt.v[3].a = o->a;
            }
            if (i == 1) {
                pkt.v[0].a = pkt.v[2].a = 0;
            }
            for (j = 0; j < 4; j++) {
                if (j < 2) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                    if (j == 0) {
                        pkt.v[0].xyz.y = s[0].y + w0;
                        pkt.v[1].xyz.y = s[1].y + w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                    if (j == 1) {
                        pkt.v[0].xyz.y = s[0].y - w0;
                        pkt.v[1].xyz.y = s[1].y - w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                } else {
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                    if (j == 2) {
                        pkt.v[0].xyz.x = s[0].x + w0;
                        pkt.v[1].xyz.x = s[1].x + w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                    if (j == 3) {
                        pkt.v[0].xyz.x = s[0].x - w0;
                        pkt.v[1].xyz.x = s[1].x - w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                }
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                                        ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
                func_00208700(&pkt, o->texture, 1);
                if (func_00101600(&pkt.v[0].xyz) != 0 && func_00101600(&pkt.v[1].xyz) != 0) {
                    if (func_00104520(o->flags, 0x13) != 0) {
                        pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                        func_002075F0(&pkt, ot, 0);
                    } else {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[0].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1]) / 2.0f));
                    }
                }
            }
        }
        o->flags &= 0xFFCFFFFF;
    }
    o->tick++;
    return 0;
}
#pragma optimization_level reset

/* OVL_WARM */

/* shape b101:01E021A0, 492 insns: draws a beam between two points: the line is cut into n pieces (at most 32),
   all points projected; each visible piece up to the moving head is drawn as four quads (above, below, right,
   left of the line) as wide as func_001018E0(width, depth). Colour from the module helper b101:01E00080.
   Both spilled params are aligned(8): that puts their homes at 0xD8/0xD0 like the original. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b101_01E021A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b101_01E021A0 xyz;
} Vtx_b101_01E021A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b101_01E021A0 v[4];
    u8 tail[0x20];
} Pkt_b101_01E021A0;

typedef struct {
    s16 u, v, w, h;
} Rect_b101_01E021A0;

typedef struct {
    void *texture;
    s32 flags;
    u8 color[4];
    f32 width;
    Rect_b101_01E021A0 rect;
    u8 pad18[0x10];
    s16 n;
    u8 pad2A[2];
    s16 head;
} Beam_b101_01E021A0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b101_01E021A0;

extern void b395_01E00080(void *, void *);

static s32 func_01E03560_b395(s32 ot __attribute__((aligned(8))), Beam_b101_01E021A0 *b, Cam_b101_01E021A0 *cam __attribute__((aligned(8))), Vec4f *p1, Vec4f *p2) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern f32 func_001018E0(f32, f32);
    Vec4f pts[33];
    Xyz_b101_01E021A0 s[33];
    f32 depth[33];
    Pkt_b101_01E021A0 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w0;
    f32 w1;
    s32 vis;
    s32 i;
    s32 j;

    vis = 0;
    if (b->n > 32) {
        b->n = 32;
    }
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, (u64)0xA | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                            ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
    func_00208700(&pkt, b->texture, 1);
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    b395_01E00080(&pkt, b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    for (i = 0; i < b->n + 1; i++) {
        if (i == b->n) {
            pts[b->n] = *p2;
        } else {
            t = (f32)i / b->n;
            pts[i].x = p1->x + dx * t;
            pts[i].y = p1->y + dy * t;
            pts[i].z = p1->z + dz * t;
        }
        if (func_00205440(&pts[i], cam->view, &s[i], &depth[i]) != 0) {
            vis |= 1 << i;
        }
    }
    for (i = 0; i < b->n; i++) {
        if (i <= b->head) {
            func_00104540(&pkt, &b->rect, 0);
            if (func_00104520(vis, i) != 0 && func_00104520(vis, i + 1) != 0) {
                w0 = func_001018E0(b->width, depth[i]);
                w1 = func_001018E0(b->width, depth[i + 1]);
                for (j = 0; j < 4; j++) {
                    if (j < 2) {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[i].x;
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[i + 1].x;
                        if (j == 0) {
                            pkt.v[0].xyz.y = w0 + s[i].y;
                            pkt.v[1].xyz.y = w1 + s[i + 1].y;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                        if (j == 1) {
                            pkt.v[0].xyz.y = s[i].y - w0;
                            pkt.v[1].xyz.y = s[i + 1].y - w1;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                    } else {
                        pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[i].y;
                        pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[i + 1].y;
                        if (j == 2) {
                            pkt.v[0].xyz.x = w0 + s[i].x;
                            pkt.v[1].xyz.x = w1 + s[i + 1].x;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                        if (j == 3) {
                            pkt.v[0].xyz.x = s[i].x - w0;
                            pkt.v[1].xyz.x = s[i + 1].x - w1;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                    }
                    if (func_00101600(&pkt.v[0].xyz) != 0) {
                        b->flags |= 0x100000;
                    }
                    if (func_00101600(&pkt.v[1].xyz) != 0) {
                        b->flags |= 0x200000;
                    }
                    if (func_00104520(b->flags, 0x14) != 0 && func_00104520(b->flags, 0x15) != 0) {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[i].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[i + 1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[i] + depth[i + 1]) / 2.0f));
                    }
                    b->flags &= 0xFFCFFFFF;
                }
            }
        }
    }
    b->head++;
    if (b->head >= b->n) {
        if (func_00104520(b->flags, 0x1A) != 0) {
            b->head = b->n;
        } else {
            b->head = 0;
        }
    }
    return 0;
}

/* shape b395:01E03D10 (b395), 898 insns, 1 copy: b043:01E048C0's scene manager with a beam, a glow sprite, a fourth
   ring and a second joint */

typedef struct Rot_b395_01E03D10 {
    s32 x, y, z, w;
} Rot_b395_01E03D10;

typedef struct Crd_b395_01E03D10 {
    Vec4f scale;
    Rot_b395_01E03D10 rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b395_01E03D10;

typedef struct Laser_b395_01E03D10 {
    s32 texture;
    u8 b, g, r, a;
    s32 flags;
    f32 base;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    s16 h20;
    s16 h22;
    s16 tick;
    s16 h26;
    s16 n1;
    s16 n2;
    s16 h2C;
    u8 pad2E[2];
} Laser_b395_01E03D10;

typedef struct Dot_b395_01E03D10 {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Dot_b395_01E03D10;

typedef struct Emit2_b395_01E03D10 {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 cx, cy, cz, cw;
    s16 u, v, w, h;
    s16 s28, s2A, s2C, s2E;
    Dot_b395_01E03D10 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 s136;
    s16 s138;
    s16 step;
    s16 s13C;
    s16 s13E;
    s16 s140;
    u8 pad142[0xE];
} Emit2_b395_01E03D10;

typedef struct Ring_b395_01E03D10 {
    s32 type;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b395_01E03D10;

typedef struct Spr_b395_01E03D10 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rot_b395_01E03D10 rot[64];
} Spr_b395_01E03D10;

typedef struct Beam_b395_01E03D10 {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    f32 width;
    s16 u, v, w, h;
    u8 pad18[8];
    s32 i20;
    s32 i24;
    s16 n;
    s16 len;
    s16 head;
    u8 pad2E[0x12];
} Beam_b395_01E03D10;

typedef struct Glow_b395_01E03D10 {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    f32 w, h, w2, h2;
    u8 pad1C[4];
    s16 u, v, tw, th;
    u8 pad28[8];
    f32 rx, ry, rz;
    u8 pad3C[4];
} Glow_b395_01E03D10;

typedef struct Emit_b395_01E03D10 {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    f32 radius;
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b395_01E03D10;

typedef struct Scene_b395_01E03D10 {
    Crd_b395_01E03D10 cam0;
    Laser_b395_01E03D10 laser;
    Pt_b117_01E00270 pts[32];
    Beam_b395_01E03D10 beam;
    Crd_b395_01E03D10 cam;
    Emit_b395_01E03D10 emit;
    Part_b489_01E00240 parts[256];
    Crd_b395_01E03D10 crdB;
    Glow_b395_01E03D10 glow;
    Crd_b395_01E03D10 crdD;
    Disc_b540_01E00250 disc1;
    Emit2_b395_01E03D10 emit2;
    Crd_b395_01E03D10 crdR[3];
    Ring_b395_01E03D10 ring[3];
    Crd_b395_01E03D10 crdE;
    Ring_b395_01E03D10 ring2;
    Crd_b395_01E03D10 crdF;
    Disc_b540_01E00250 disc2;
    Crd_b395_01E03D10 crdL;
    Spr_b395_01E03D10 spr;
    Vec4f v;
    s32 cnt;
    s32 timer;
    s32 t;
    s32 code;
    s32 jA;
    s32 pad2D34;
    s32 jB;
    u8 pad2D3C[4];
} Scene_b395_01E03D10;

static s32 func_01E03D10_b395(s32 arg0, s32 code) {
    Scene_b395_01E03D10 *g = (Scene_b395_01E03D10 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(s32 *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_001033D0(f32 *, f32, f32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern s32 func_0019A5C8();
    s32 ot;
    Vec4f w;
    Vec4f p[2];
    s32 tx[4];
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2D40);
        func_00103890(&g->cam0);
        func_00103890(&g->crdB);
        func_00103890(&g->cam);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->crdR[i]);
        }
        func_00103890(&g->crdE);
        func_00103890(&g->crdF);
        func_00103890(&g->crdD);
        func_00103890(&g->crdL);
        g->jA = func_001F5560(func_001F53A0(), 0xF, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x10, 0);
        g->timer = 0x160;
        g->t = 1;
        g->code = code;
        g->cnt = 0x10;
        g->disc1.flags = 0x80000;
        g->disc1.r = 0xA0;
        g->disc1.g = 0xD0;
        g->disc1.b = 0x70;
        g->disc1.a = 0xFF;
        g->disc1.radius = 30.0f;
        g->disc1.count = 0x24;
        g->disc1.height = 0;
        g->disc2.flags = 0x80000;
        g->disc2.r = 0xA0;
        g->disc2.g = 0xD0;
        g->disc2.b = 0x70;
        g->disc2.a = 0;
        g->disc2.radius = 4.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        func_00103260(tx, 0xF);
        g->laser.texture = tx[0];
        g->laser.flags = 0x8003;
        g->laser.r = 0xA0;
        g->laser.g = 0xD0;
        g->laser.b = 0x70;
        g->laser.a = 0;
        g->laser.u = 0xC8;
        g->laser.v = 0x20;
        g->laser.w = 7;
        g->laser.h = 0x20;
        g->laser.u0 = 0xC8;
        g->laser.v0 = 0x20;
        g->laser.tw = 0x100;
        g->laser.th = 0x100;
        g->laser.base = 20.0f;
        g->laser.h22 = 8;
        g->laser.tick = 0;
        g->laser.h26 = 0x8A;
        g->laser.n1 = 0x20;
        g->laser.n2 = 0;
        g->laser.h2C = 1;
        g->beam.texture = (void *)tx[0];
        g->beam.flags = 0x4000000;
        g->beam.width = 20.0f;
        g->beam.u = 0xC8;
        g->beam.v = 0x20;
        g->beam.w = 7;
        g->beam.h = 0x20;
        g->beam.r = 0xA0;
        g->beam.g = 0xD0;
        g->beam.b = 0x70;
        g->beam.a = 0x80;
        g->beam.n = 0x1C;
        g->beam.head = -3;
        g->beam.len = 0x28;
        g->beam.i20 = 0;
        g->beam.i24 = 0;
        g->emit.texture = (void *)tx[0];
        g->emit.flags = 3;
        g->emit.r = 0xA0;
        g->emit.g = 0xD0;
        g->emit.b = 0x70;
        g->emit.a = 0x80;
        g->emit.width = 0.5f;
        g->emit.len = 3.0f;
        g->emit.u = 0xB0;
        g->emit.v = 0x60;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0xB0;
        g->emit.v0 = 0x60;
        g->emit.tw = 0x100;
        g->emit.th = 0x100;
        g->emit.parts = g->parts;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 1;
        g->emit.rate = 0;
        func_01E00120_b395(&g->emit, 12, 3.0f);
        g->glow.texture = (void *)tx[0];
        g->glow.flags = 0x80000;
        g->glow.r = 0xA0;
        g->glow.g = 0xD0;
        g->glow.b = 0x70;
        g->glow.a = 0;
        g->glow.w = 0.5f;
        g->glow.h = 8.0f;
        g->glow.w2 = 0.5f;
        g->glow.h2 = 4.0f;
        g->glow.u = 0xB0;
        g->glow.v = 0x40;
        g->glow.tw = 0x20;
        g->glow.th = 0x20;
        g->glow.rx = 0.0f;
        g->glow.ry = 0.0f;
        g->glow.rz = 0.0f;
        g->emit2.texture = (void *)tx[0];
        g->emit2.flags = 0x85;
        g->emit2.cx = 0.0f;
        g->emit2.cy = 0.0f;
        g->emit2.cz = 0.0f;
        g->emit2.cw = 0.0f;
        g->emit2.s28 = 0xF0;
        g->emit2.s2A = 0;
        g->emit2.w = 0x10;
        g->emit2.h = 0x10;
        g->emit2.s2C = 0x100;
        g->emit2.s2E = 0x100;
        g->emit2.size = 20.0f;
        g->emit2.count = 0x10;
        g->emit2.step = 1;
        g->emit2.s13C = 1;
        g->emit2.s140 = 8;
        g->emit2.s136 = 0xA;
        g->emit2.s138 = 0xA;
        g->emit2.r = 0x80;
        g->emit2.g = 0x80;
        g->emit2.b = 0x80;
        g->emit2.a = 0x20;
        for (i = 0; i < g->emit2.count; i++) {
            g->emit2.pts[i].x = g->emit2.cx + (f32)(func_0019A5C8() % 20 - 10);
            g->emit2.pts[i].y = g->emit2.cy + (f32)(func_0019A5C8() % 20 - 10);
            g->emit2.pts[i].z = g->emit2.cz;
            g->emit2.pts[i].life = -g->emit2.step * i;
            g->emit2.pts[i].pad = 0;
            g->emit2.s13E = g->emit2.s140 - 1;
        }
        for (i = 0; i < 3; i++) {
            g->ring[i].flags = 0;
            g->ring[i].u = 0x8E;
            g->ring[i].v = 0;
            g->ring[i].w = 0x20;
            g->ring[i].h = 0x80;
            g->ring[i].r = 0xA0;
            g->ring[i].g = 0xD0;
            g->ring[i].b = 0x70;
            g->ring[i].a = 0x80;
            {
                f32 z = 0.0f;
                { extern s32 b395_01E01040(void *, s32, f32, f32, f32, f32); f32 fs2; f32 fs3; fs3 = 12.5f; fs2 = 11.5f; b395_01E01040(&g->ring[i], tx[0], fs2, fs3, z, z); }
            }
        }
        g->ring2.flags = 0;
        g->ring2.u = 0x8E;
        g->ring2.v = 0;
        g->ring2.w = 0x20;
        g->ring2.h = 0x80;
        g->ring2.r = 0xA0;
        g->ring2.g = 0xD0;
        g->ring2.b = 0x70;
        g->ring2.a = 0x80;
        {
            f32 z = 0.0f;
            { f32 fs2; f32 fs3; fs3 = 3.0f; fs2 = 2.7f; func_01E01040_b395((Ring_b001_01E035A0 *)&g->ring2, tx[0], fs2, fs3, z, z); }
        }
        g->spr.flags = 1;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.r = 0xA0;
        g->spr.g = 0xD0;
        g->spr.b = 0x70;
        g->spr.a = 0x20;
        { extern s32 b395_01E022E0(void *, s32, f32); f32 fs2 = 0.5f; b395_01E022E0(&g->spr, tx[0], fs2); }
        for (i = 0; i < 64; i++) {
            g->spr.rot[i].x = func_0019A5C8() % 0x4000 - 0x2000;
            g->spr.rot[i].y = func_0019A5C8() % 0x10000;
            g->spr.rot[i].z = 0;
        }
        g->crdL.scale.x = g->crdL.scale.y = g->crdL.scale.z = 0.1f;
        g->crdE.scale.x = g->crdE.scale.y = g->crdE.scale.z = 0.0f;
        g->crdR[0].scale.x = g->crdR[0].scale.y = g->crdR[0].scale.z = 0.0f;
        g->crdR[1].scale.x = g->crdR[1].scale.y = g->crdR[1].scale.z = 0.5f;
        g->crdR[2].scale.x = g->crdR[2].scale.y = g->crdR[2].scale.z = 1.0f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->jA, &p[0]);
    func_001F5620(func_001F53A0(), g->jB, &p[1]);
    func_001F5620(func_001F53A0(), g->jA, &g->crdL.pos);
    func_00103DB0(&p[0], &p[1], &g->crdL.rot);
    g->crdE.pos = g->crdL.pos;
    g->crdE.rot = g->crdL.rot;
    func_001F5620(func_001F53A0(), g->jA, &g->crdF.pos);
    func_001F5F90(func_001F5380(), &g->v);
    func_001F5F90(func_001F5380(), &g->crdD.pos);
    func_001F5F90(func_001F5380(), &g->cam.pos);
    for (i = 0; i < 3; i++) {
        func_001F5F90(func_001F5380(), &g->crdR[i].pos);
    }
    func_001F5F90(func_001F53A0(), &p[0]);
    func_001F5F90(func_001F5380(), &p[1]);
    func_00103DB0(&p[0], &p[1], &g->cam.rot);
    if (g->t < 0x62) {
        func_001F5620(func_001F53A0(), g->jA, &g->crdB.pos);
    }
    if (g->t >= 0x61) {
        func_01E02A50_b395((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->pts, (f32 *)&g->crdB.pos);
        func_00104490(&g->crdB.pos, &g->v, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
        }
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->crdB);
    func_001038D0(&g->cam);
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->crdR[i]);
    }
    func_001038D0(&g->crdE);
    func_001039A0(&g->crdF);
    func_001039A0(&g->crdD);
    func_001038D0(&g->crdL);
    g->disc1.r = g->disc2.r = g->laser.r = g->beam.r = g->emit.r = g->spr.r = g->ring2.r = g->glow.r = g->emit2.r =
        func_0019A5C8() % 0xA0;
    g->disc1.g = g->disc2.g = g->laser.g = g->beam.g = g->emit.g = g->spr.g = g->ring2.g = g->glow.g = g->emit2.g =
        func_0019A5C8() % 0xD0;
    g->disc1.b = g->disc2.b = g->laser.b = g->beam.b = g->emit.b = g->spr.b = g->ring2.b = g->glow.b = g->emit2.b =
        func_0019A5C8() % 0x70;
    if (g->t >= 0x7B) {
        func_01E01D80_b395(ot, (Disc_b540_01E00250 *)&g->disc1, (Cam_b540_01E00250 *)&g->crdD);
        if (g->t >= 0x14A) {
            func_00103470(&g->disc1.a, 0, 0x10);
        } else if (g->t % 2 == 0) {
            g->disc1.a = 0xFF;
        } else {
            g->disc1.a = 0x80;
        }
    }
    if (g->t >= 0x61 && g->t < 0xEC) {
        func_01E017F0_b395(ot, (Spr_b007_01E017F0 *)&g->glow, (Cam_b007_01E017F0 *)&g->crdF);
        func_001032C0(&g->glow.a, 0x80, 0x10);
    }
    func_01E01D80_b395(ot, (Disc_b540_01E00250 *)&g->disc2, (Cam_b540_01E00250 *)&g->crdF);
    func_01E02440_b395(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->crdL);
    if (g->t >= 0x24 && g->t < 0x5A) {
        if (func_001033D0((f32 *)&g->crdL, 1.0f, 0.05f) == 0) {
            func_00103470(&g->spr.a, 0, 1);
            func_00103470(&g->disc2.a, 0, 0x10);
        } else {
            func_001032C0(&g->disc2.a, 0x80, 0x10);
        }
    } else if (g->t >= 0x61) {
        if (g->t == 0x61) {
            g->spr.a = 0x20;
        }
        func_00103470(&g->spr.a, 0, 1);
        func_001032C0(&g->disc2.a, 0x80, 0x10);
    }
    if (g->t >= 0x7B) {
        for (i = 0; i < 3; i++) {
            func_01E01300_b395(ot, (Ring_b001_01E03860 *)&g->ring[i], (Cam_b001_01E03860 *)&g->crdR[i]);
            func_00103470(&g->ring[i].a, 0, 8);
            if (func_001033D0((f32 *)&g->crdR[i], 2.0f, 0.1f) == 0) {
                g->crdR[i].scale.x = g->crdR[i].scale.y = g->crdR[i].scale.z = 0.1f;
                g->crdR[i].rot.x = func_0019A5C8() % 0x10000;
                g->crdR[i].rot.y = func_0019A5C8() % 0x10000;
                g->crdR[i].rot.z = func_0019A5C8() % 0x10000;
                if (g->t < 0x14A) {
                    g->ring[i].a = 0x80;
                }
            }
        }
        func_01E002E0_b395(ot, (Emit_b489_01E00240 *)&g->emit, (Cam_b489_01E00240 *)&g->cam);
        if (g->t > 0x14A) {
            func_00103470(&g->emit.a, 0, 8);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->parts[i].age >= 0) {
                g->parts[i].x *= 1.4f;
                g->parts[i].y *= 1.4f;
                g->parts[i].z *= 1.4f;
                if (g->parts[i].age > 8) {
                    func_001043F0(&w, 1.0f);
                    g->parts[i].y = w.y;
                    g->parts[i].z = w.z;
                    g->parts[i].x = w.x;
                    g->parts[i].age = -(func_0019A5C8() % 12);
                }
            }
        }
    }
    if (g->t > 0x61) {
        func_01E01300_b395(ot, (Ring_b001_01E03860 *)&g->ring2, (Cam_b001_01E03860 *)&g->crdE);
        if (func_001033D0((f32 *)&g->crdE, 1.0f, 0.2f) == 0) {
            g->crdE.scale.x = g->crdE.scale.y = g->crdE.scale.z = 0.0f;
        }
        if (g->t == 0xEC) {
            g->laser.a = 0x80;
            for (i = 0; i < g->laser.n1 + 1; i++) {
                g->pts[i].a = 0x80;
            }
        }
        func_01E02BA0_b395(ot, (Laser_b117_01E00270 *)&g->laser, g->pts, (Cam_b117_01E00270 *)g);
        if (g->t < 0xEC) {
            func_01E03560_b395(ot, (Beam_b101_01E021A0 *)&g->beam, (Cam_b101_01E021A0 *)g, &g->crdF.pos, &g->v);
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x14A) {
        return 2;
    }
    if (g->t == 0x71) {
        return 1;
    }
    if (g->t >= 0x7B && g->t < 0x14A) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
