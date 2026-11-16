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

static void func_01E00080_b773(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b773:01E00120, 129 insns: draw a 2-point screen line in the object's colour (bytes 4..7 as b, g, r, a) from
   (x0, y0) to (x1, y1) around the screen centre; blend 0x44 when the object has flag 0xC, 0x42 with flag 0xA, else
   0x48; it is drawn twice when the object has flag 0x1C */

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
} Hdr_b773_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b773_01E00120;

typedef struct {
    Hdr_b773_01E00120 h;
    Vtx_b773_01E00120 v[2];
    u8 tail[8];
} Pkt_b773_01E00120;

typedef struct {
    s32 id;
    u8 b;
    u8 g;
    u8 r;
    u8 a;
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
} Line_b773_01E00120;

static s32 func_01E00120_b773(s32 tex, Line_b773_01E00120 *o) {
    extern s32 func_00104520(s32, s32);
    Pkt_b773_01E00120 p __attribute__((aligned(8)));

    ((Hdr_b773_01E00120 *)(s32)&p)->count = 0x11;
    ((Hdr_b773_01E00120 *)(s32)&p)->tag = 4;
    ((Hdr_b773_01E00120 *)(s32)&p)->regs = 0x4141;
    ((Hdr_b773_01E00120 *)(s32)&p)->pad = 0;
    if (func_00104520(o->id, 0xC)) {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->id, 0xA)) {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x48);
    }
    ((Hdr_b773_01E00120 *)(s32)&p)->count |= 0x400;
    p.v[0].r = o->r;
    p.v[0].g = o->g;
    p.v[0].b = o->b;
    p.v[0].a = o->a;
    p.v[0].q = 1.0f;
    p.v[1].r = o->r;
    p.v[1].g = o->g;
    p.v[1].b = o->b;
    p.v[1].a = o->a;
    p.v[1].q = 1.0f;
    p.v[0].x = (o->x0 + 0x6C0) << 4;
    p.v[0].y = (o->y0 + 0x720) << 4;
    p.v[0].z = 0xFFFFFF;
    p.v[0].f = 0;
    p.v[1].x = (o->x1 + 0x6C0) << 4;
    p.v[1].y = (o->y1 + 0x720) << 4;
    p.v[1].z = 0xFFFFFF;
    p.v[1].f = 0;
    func_002075F0((s32)&p, tex, 0);
    if (func_00104520(o->id, 0x1C)) {
        func_002075F0((s32)&p, tex, 0);
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

static s32 func_01E00330_b773(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E00890_b773(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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
static s32 func_01E00A50_b773(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
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

/* shape b773:01E017B0 (LkPrim_SortQuadrBillBoard), 363 insns, 1 copy: draws a square billboard as four quads fanned
   around the centre: 8 rim points (from a template, sized by the half-width) rotated by the sprite rotation,
   projected per quad, depth-sorted unless flag 0x13 */

typedef struct {
    u8 b, g, r, a;
} Src_b773_01E017B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b773_01E017B0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b773_01E017B0 v[4];
    u8 tail[0x20];
} Pkt_b773_01E017B0;

typedef struct {
    f32 x, y, z, w;
} Vec_b773_01E017B0;

typedef struct {
    Vec_b773_01E017B0 v[9];
} Quad9_b773_01E017B0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b773_01E017B0 color;
    f32 size;
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad18[8];
    Vec_b773_01E017B0 rot;
} Spr_b773_01E017B0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b773_01E017B0;

static s32 func_01E017B0_b773(s32 obj, Spr_b773_01E017B0 *spr, Cam_b773_01E017B0 *cam) {
    extern Quad9_b773_01E017B0 D_01E05F80_b773;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad9_b773_01E017B0 in;
    Vec_b773_01E017B0 out[9];
    f32 m[16];
    f32 depth[4];
    Pkt_b773_01E017B0 pkt;
    s32 i;

    in = D_01E05F80_b773;
    in.v[0].x = -spr->size;
    in.v[1].x = -spr->size;
    in.v[1].y = spr->size;
    in.v[2].y = spr->size;
    in.v[3].x = spr->size;
    in.v[3].y = spr->size;
    in.v[4].x = spr->size;
    in.v[5].x = spr->size;
    in.v[5].y = -spr->size;
    in.v[6].y = -spr->size;
    in.v[7].x = -spr->size;
    in.v[7].y = -spr->size;
    func_0020C630(m, &spr->rot);
    for (i = 0; i < 8; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pkt_b773_01E017B0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b773_01E017B0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b773_01E017B0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b773_01E017B0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b773((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    func_00104540(&pkt, &spr->u, 0);
    for (i = 0; i < 4; i++) {
        if (func_00205440(&out[i + i + 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        if (i < 2) {
            if (func_00205440(&out[2], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                spr->flags |= 0x200000;
            }
        } else {
            if (func_00205440(&out[6], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                spr->flags |= 0x200000;
            }
        }
        if (i == 1 || i == 2) {
            if (func_00205440(&out[4], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                spr->flags |= 0x400000;
            }
        } else {
            if (func_00205440(&out[0], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                spr->flags |= 0x400000;
            }
        }
        if (func_00205440(m, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
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

/* shape b000:01E02A30, 546 insns, 18 copies: draws one particle as a textured quad of the sprite's size, aspect-scaled,
   rotated by the sprite angle (flag 0x1F) or axis-aligned; depth-sorted unless flag 0x13.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E02A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E02A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E02A30 v[4];
    u8 tail[0x20];
} Pkt_b000_01E02A30;

typedef struct {
    s16 u, v, w, h;
    f32 fw, fh;
    u8 pad10[0x20];
    f32 size;
    Src_b000_01E02A30 color;
    s32 flags;
    u8 pad3C[8];
    s32 angle;
} Spr_b000_01E02A30;

typedef struct {
    void *texture;
    s32 flags;
    f32 scale;
    u8 padC[4];
    f32 x, y, z;
} Part_b000_01E02A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E02A30;

static s32 func_01E01D60_b773(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00104DC0(void *, void *);
    f32 depth[4];
    Vec4f c;
    Pkt_b000_01E02A30 pkt;
    f32 kx;
    f32 ky;
    f32 r;
    f32 cs;
    f32 sn;
    f32 sz;
    f32 hx;
    f32 hy;

    ((Pkt_b000_01E02A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(s->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(s->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(s->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b773((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
    func_00104DC0(&pkt, s);
    if (func_00104520(s->flags, 5) == 0) {
        if (func_00104520(s->flags, 0) != 0) {
            if (s->w > s->h) {
                kx = 1.0f;
                ky = (f32)s->h / (f32)s->w;
            } else if (s->w < s->h) {
                kx = (f32)s->w / (f32)s->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (s->fw > s->fh) {
                ky = s->fh / s->fw;
                kx = 1.0f;
            } else if (s->fw < s->fh) {
                kx = s->fw / s->fh;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
    } else {
        kx = 1.0f;
        ky = (f32)s->h / (f32)s->w;
    }
    if (func_00104520(s->flags, 0x1F) != 0) {
        r = 0.017453292f * (s->angle % 360);
        cs = func_0020B620(r);
        sn = func_0020B730(r);
        sz = p->scale * s->size;
        hy = ky * sz;
        hx = kx * sz;
        c.x = p->x + (cs * -hx - sn * hy);
        c.y = p->y + (sn * -hx + cs * hy);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + (cs * hx - sn * hy);
        c.y = p->y + (sn * hx + cs * hy);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x + (cs * -hx - sn * -hy);
        c.y = p->y + (sn * -hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + (cs * hx - sn * -hy);
        c.y = p->y + (sn * hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    } else {
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    }
    if (func_00104520(s->flags, 0x18) != 0) {
        func_00208700(&pkt, p->texture, 0);
    } else {
        if (func_00104520(s->flags, 0) != 0) {
            func_00208CB0(&pkt, (u64)0xA | ((u64)s->u << 4) | ((u64)(s->u + s->w - 1) << 14) |
                                    ((u64)s->v << 24) | ((u64)(s->v + s->h - 1) << 34));
        }
        func_00208700(&pkt, p->texture, 1);
    }
    if (func_00104520(p->flags, 0x14) != 0 && func_00104520(p->flags, 0x15) != 0 &&
        func_00104520(p->flags, 0x16) != 0 && func_00104520(p->flags, 0x17) != 0) {
        if (func_00104520(s->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, obj, 0);
        } else {
            func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
    }
    p->flags &= 0xFF0FFFFF;
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

static s32 func_01E025F0_b773(s32 obj, Spr_b007_01E017F0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E06010_b773;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Pkt_b007_01E017F0 pkt;
    s32 i;

    in = D_01E06010_b773;
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
    func_01E00080_b773((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* OVL_WARM */

/* shape b773:01E02B80, 177 insns: b773:01E00120's line packet drawn as horizontal scanlines across the screen
   (x 0x6000..0xA000): rows step by 0x04 + 3 from y 0x720 in groups of three, colour from the first to the second
   (the second copies the first unless bit 9 is set), each sent twice with bit 0x1C */

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
} Hdr_b773_01E02B80;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b773_01E02B80;

typedef struct {
    Hdr_b773_01E02B80 h;
    Vtx_b773_01E02B80 v[2];
    u8 tail[8];
} Pkt_b773_01E02B80;

typedef struct {
    u8 b, g, r, a;
} Col_b773_01E02B80;

typedef struct {
    s32 id;
    s32 gap;
    Col_b773_01E02B80 c;
    Col_b773_01E02B80 c2;
} Line_b773_01E02B80;

static s32 func_01E02B80_b773(s32 tex, Line_b773_01E02B80 *o) {
    extern s32 func_00104520(s32, s32);
    Pkt_b773_01E02B80 p __attribute__((aligned(8)));
    s32 n;
    s32 step;
    s32 i;
    s32 j;
    u16 y;

    step = o->gap + 3;
    n = 448 / step;
    ((Hdr_b773_01E02B80 *)(s32)&p)->count = 0x11;
    ((Hdr_b773_01E02B80 *)(s32)&p)->tag = 4;
    ((Hdr_b773_01E02B80 *)(s32)&p)->regs = 0x4141;
    ((Hdr_b773_01E02B80 *)(s32)&p)->pad = 0;
    if (func_00104520(o->id, 0xC)) {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->id, 0xA)) {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p, ((u64)0x80 << 32) | 0x48);
    }
    ((Hdr_b773_01E02B80 *)(s32)&p)->count |= 0x400;
    if (func_00104520(o->id, 9) == 0) {
        o->c2 = o->c;
    }
    p.v[0].r = o->c.r;
    p.v[0].g = o->c.g;
    p.v[0].b = o->c.b;
    p.v[0].a = o->c.a;
    p.v[0].q = 1.0f;
    p.v[1].r = o->c2.r;
    p.v[1].g = o->c2.g;
    p.v[1].b = o->c2.b;
    p.v[1].a = o->c2.a;
    p.v[1].q = 1.0f;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            y = i * step + 0x720 + j;
            p.v[0].x = 0x6000;
            p.v[0].y = y << 4;
            p.v[0].z = 0xFFFFFF;
            p.v[0].f = 0;
            p.v[1].x = 0xA000;
            p.v[1].y = y << 4;
            p.v[1].z = 0xFFFFFF;
            p.v[1].f = 0;
            func_002075F0((s32)&p, tex, 0);
            if (func_00104520(o->id, 0x1C)) {
                func_002075F0((s32)&p, tex, 0);
            }
        }
    }
    return 0;
}

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b025_01E01EF0;

typedef struct {
    f32 x, y, z, w;
} Vec_b025_01E01EF0;

typedef struct {
    u8 pad00[7];
    u8 col;
    u8 pad08[0x2E];
    s16 life;
    s16 max;
    s16 used;
} Trail_b025_01E01EF0;

static s32 func_01E02E50_b773(Trail_b025_01E01EF0 *o, Pt_b025_01E01EF0 *pts, Vec_b025_01E01EF0 *pos) {
    s32 k;

    if (o->used <= o->max - 1) {
        o->used++;
    }
    for (k = o->used; k > -1; k--) {
        if (pts[k].e > o->life) {
            o->used = k;
        }
    }
    for (k = o->used; k > 0; k--) {
        pts[k].x = pts[k - 1].x;
        pts[k].y = pts[k - 1].y;
        pts[k].z = pts[k - 1].z;
        pts[k].d = pts[k - 1].d;
        pts[k].e = pts[k - 1].e;
        pts[k].c = pts[k - 1].c;
    }
    pts[0].x = pos->x;
    pts[0].y = pos->y;
    pts[0].z = pos->z;
    pts[0].d = 0;
    pts[0].e = 0;
    pts[0].c = o->col;
    return 0;
}

/* shape b025:01E01FD0 (LkEFF_SortFieldThing), 616 insns, 9 copies: b013:01E02BE0's billboard particles with the points
   passed in (pts) and no count multiplier: per point the atlas cell of its frame (row- or column-major), frame advance
   every rate ticks, x jittered by rand() % 4 - 2 when the frame wraps, optional growth with age; depth-sorted unless
   flag 0x13. The fourth corner's depth goes to depth[1] (as in the original). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E01FD0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b025_01E01FD0;

typedef struct {
    Uv_b025_01E01FD0 uv;
    Xyz_b025_01E01FD0 p;
} Vtx_b025_01E01FD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E01FD0 v[4];
    u8 tail[0x20];
} Pk_b025_01E01FD0;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b025_01E01FD0;

typedef struct {
    void *texture;
    u8 b4, b5, b6, b7;
    s32 flags;
    f32 size;
    u8 pad10[4];
    s16 cw;
    s16 ch;
    s16 u0;
    s16 v0;
    s16 aw;
    s16 ah;
    u8 f20[0x10];
    f32 grow;
    u8 pad34[4];
    s16 n0;
    s16 n1;
    s16 frames;
    s16 rate;
} Em_b025_01E01FD0;

typedef struct {
    Vec4f v[4];
} Quad_b025_01E01FD0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E01FD0;

static s32 func_01E02F30_b773(s32 obj, Em_b025_01E01FD0 *o, Part_b025_01E01FD0 *pts, Cam_b025_01E01FD0 *cam) {
    extern Quad_b025_01E01FD0 D_01E06090_b773;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00205C90();
    extern void func_00103620();
    s32 n;
    f32 m[16];
    f32 depth[4];
    Quad_b025_01E01FD0 in;
    Vec4f out[4];
    Vec4f pos;
    Pk_b025_01E01FD0 pk __attribute__((aligned(8)));
    s32 i;
    s16 u;
    s16 v;
    f32 s;

    in = D_01E06090_b773;
    in.v[0].x = -o->size;
    in.v[0].y = o->size;
    in.v[1].x = o->size;
    in.v[1].y = o->size;
    in.v[2].x = -o->size;
    in.v[2].y = -o->size;
    in.v[3].x = o->size;
    in.v[3].y = -o->size;
    if (func_00104520(o->flags, 0x1F) != 0) {
        n = o->n0;
    } else {
        n = o->n1;
    }
    func_00205C90(m);
    for (i = 0; i < 4; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pk_b025_01E01FD0 *)(s32)&pk)->flags = 0x24;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->size = 9;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->pad4 = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    pk.r = o->b6;
    pk.g = o->b5;
    pk.b = o->b4;
    pk.q = 1.0f;
    for (i = 0; i < n; i++) {
        if (func_00104520(o->flags, 1) != 0) {
            u = o->u0 + o->cw * (pts[i].frame % (o->aw / o->cw));
            v = o->v0 + o->ch * (pts[i].frame / (o->aw / o->cw));
        } else {
            u = o->u0 + o->cw * (pts[i].frame / (o->ah / o->ch));
            v = o->v0 + o->ch * (pts[i].frame % (o->ah / o->ch));
        }
        if (pts[i].age % o->rate == 0) {
            pts[i].frame++;
            if (pts[i].frame > o->frames - 1) {
                pts[i].frame = 0;
                pts[i].x += func_0019A5C8() % 4 - 2;
            }
        }
        ((Pk_b025_01E01FD0 *)(s32)&pk)->flags |= 0x800;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->v = (v + o->ch - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->v = (v + o->ch - 1) * 16;
        pk.a = pts[i].c;
        if (func_00104520(o->flags, 0xF) != 0) {
            s = o->grow * pts[i].age;
        } else {
            s = 1.0f;
        }
        if (func_00104520(o->flags, 0x10) != 0) {
            func_00103620(&pts[i], o->f20);
        }
        pts[i].age++;
        pos.x = out[0].x * s + pts[i].x;
        pos.y = out[0].y * s + pts[i].y;
        pos.z = out[0].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        pos.x = out[1].x * s + pts[i].x;
        pos.y = out[1].y * s + pts[i].y;
        pos.z = out[1].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        pos.x = out[2].x * s + pts[i].x;
        pos.y = out[2].y * s + pts[i].y;
        pos.z = out[2].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        pos.x = out[3].x * s + pts[i].x;
        pos.y = out[3].y * s + pts[i].y;
        pos.z = out[3].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[1]) != 0) {
            o->flags |= 0x800000;
        }
        func_00208CB0(&pk, (u64)0xA | ((u64)u << 4) | ((u64)(u + o->cw - 1) << 14) | ((u64)v << 24) |
                               ((u64)(v + o->ch - 1) << 34));
        func_00208700(&pk, o->texture, 1);
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b773:01E038D0 (LkSortMarker), 381 insns, 1 copy: draws a marker sprite as two stacked quads above and below
   the centre: 8 corners sized by half the texture size times the scale, offset by y, rotated about z, projected per
   quad, depth-sorted unless flag 0x13 */

typedef struct {
    void *texture;
    s32 flags;
    Src_b007_01E017F0 color;
    f32 y;
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad18[8];
    s32 rz;
    f32 scale;
} Mark_b773_01E038D0;

typedef struct {
    s32 x, y, z, w;
} Rot_b773_01E038D0;

static s32 func_01E038D0_b773(s32 obj, Mark_b773_01E038D0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E060D0_b773;
    extern Rot_b773_01E038D0 D_01E06150_b773;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Rot_b773_01E038D0 rot;
    Pkt_b007_01E017F0 pkt;
    f32 w;
    f32 h;
    s32 i;

    w = spr->scale * (spr->tw >> 1);
    h = spr->scale * (spr->th >> 1);
    in = D_01E060D0_b773;
    in.v[0].x = -w;
    in.v[0].y = spr->y + h;
    in.v[1].x = w;
    in.v[1].y = spr->y + h;
    in.v[2].x = -w;
    in.v[2].y = spr->y - h;
    in.v[3].x = w;
    in.v[3].y = spr->y - h;
    in.v[4].x = -w;
    in.v[4].y = -spr->y + h;
    in.v[5].x = w;
    in.v[5].y = -spr->y + h;
    in.v[6].x = -w;
    in.v[6].y = -spr->y - h;
    in.v[7].x = w;
    in.v[7].y = -spr->y - h;
    rot = D_01E06150_b773;
    rot.z = spr->rz;
    func_0020C630(m, &rot);
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
    func_01E00080_b773((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    for (i = 0; i < 2; i++) {
        if (i != 0) {
            func_00104540(&pkt, &spr->u, 0);
        } else {
            func_00104540(&pkt, &spr->u, 3);
        }
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

static s32 func_01E03ED0_b773(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
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
static s32 func_01E04020_b773(s32 ot __attribute__((aligned(8))), Laser_b117_01E00270 *o, Pt_b117_01E00270 *pts, Cam_b117_01E00270 *cam __attribute__((aligned(8)))) {
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
    func_01E00080_b773((void *)&pkt, (void *)o->color);
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

/* shape b773:01E049E0, 1358 insns, 1 copy: b773 scene manager (written from the asm in b274:01E02B40's Lk form): code
   >= 0 sets up the laser, the trail, the screen lines, two discs, two emitters, seven band sprites, two spinning
   quads, two eyes and two markers; else the trail follows joint 0x66 on 100..124, eyes from 142,
   markers/lines/bands/quads slide in on 166..316, the laser homes from 340, discs flash on 340..377 and from 386,
   emitter 1 once the laser lands; returns 2/1/6/8 by tick */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b773_01E049E0;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Pt_b773_01E049E0;

typedef struct {
    s32 tex;
    u8 c[4];
    s32 flags;
    f32 size;
    s16 uv[8];
    u8 pad20[2];
    s16 h22;
    s16 h24;
    s16 h26;
    s16 h28;
    s16 count;
    s16 h2C;
    u8 pad2E[2];
} Laser_b773_01E049E0;

typedef struct {
    s32 tex;
    u8 c[4];
    s32 flags;
    f32 size;
    s16 uv[8];
    u8 pad20[0x10];
    f32 rate;
    s16 a;
    s16 b;
    s16 c34;
    s16 count;
    s16 e;
    u8 pad3E[2];
} Spot_b773_01E049E0;

typedef struct {
    s32 id;
    u8 c[4];
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
} Seg_b773_01E049E0;

typedef struct {
    s32 id;
    s32 gap;
    u8 c[4];
    u8 padC[4];
    Seg_b773_01E049E0 s[2];
} Line_b773_01E049E0;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b773_01E049E0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Pt_b773_01E049E0 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 life;
    u8 f2F;
} Emit_b773_01E049E0;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Aux_b773_01E049E0;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 scale;
    u8 c[4];
    s32 mode;
    u8 pad3C[8];
    s32 rot;
    s16 s[6];
    u8 pad54[0xC];
} Band_b773_01E049E0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    s16 uv[4];
    u8 pad18[8];
    s32 rot[3];
    u8 pad2C[4];
} Quad_b773_01E049E0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 w;
    f32 h;
    f32 w2;
    f32 h2;
    u8 pad1C[4];
    s16 uv[4];
    u8 pad28[8];
    s32 rot[3];
    u8 pad3C[4];
} Eye_b773_01E049E0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 y;
    s16 uv[8];
    s32 rz;
    f32 scale;
    u8 pad28[8];
} Mark_b773_01E049E0;

typedef struct {
    Crd_b773_01E049E0 c0;
    Laser_b773_01E049E0 laser;
    Pt_b773_01E049E0 lpts[32];
    Spot_b773_01E049E0 trail;
    Pt_b773_01E049E0 tpts[32];
    Line_b773_01E049E0 line;
    Crd_b773_01E049E0 cam1;
    Crd_b773_01E049E0 cam2;
    Crd_b773_01E049E0 cam3;
    Disc_b773_01E049E0 disc1;
    Disc_b773_01E049E0 disc2;
    Crd_b773_01E049E0 cam4;
    Emit_b773_01E049E0 emit1;
    Pt_b773_01E049E0 parts1[256];
    u8 pad1720[0x70];
    Emit_b773_01E049E0 emit2;
    Pt_b773_01E049E0 parts2[64];
    Crd_b773_01E049E0 cA;
    Aux_b773_01E049E0 auxA;
    Band_b773_01E049E0 bandA;
    Crd_b773_01E049E0 cB;
    Quad_b773_01E049E0 quad1;
    Quad_b773_01E049E0 quad2;
    Crd_b773_01E049E0 cC;
    Aux_b773_01E049E0 auxC;
    Band_b773_01E049E0 bandC;
    Crd_b773_01E049E0 cD;
    Aux_b773_01E049E0 auxD;
    Band_b773_01E049E0 bandD;
    Crd_b773_01E049E0 cE;
    Aux_b773_01E049E0 auxE;
    Band_b773_01E049E0 bandE;
    Crd_b773_01E049E0 cF;
    Aux_b773_01E049E0 auxF;
    Band_b773_01E049E0 bandF;
    Crd_b773_01E049E0 cG;
    Aux_b773_01E049E0 auxG;
    Band_b773_01E049E0 bandG;
    Crd_b773_01E049E0 cH;
    Aux_b773_01E049E0 auxH;
    Band_b773_01E049E0 bandH;
    Crd_b773_01E049E0 cI;
    Eye_b773_01E049E0 eye1;
    Crd_b773_01E049E0 cJ;
    Eye_b773_01E049E0 eye2;
    Crd_b773_01E049E0 cK;
    Mark_b773_01E049E0 mark1;
    Mark_b773_01E049E0 mark2;
    s32 timer;
    s32 t;
    s32 code;
    s32 cnt;
    s32 j[5];
    f32 ang;
    f32 xa;
    f32 xb;
    u8 fade;
    u8 pad2581[0xF];
} Scene_b773_01E049E0;

static s32 func_01E049E0_b773(s32 arg0, s32 code) {
    Scene_b773_01E049E0 *g = (Scene_b773_01E049E0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern void func_00103920(void *, f32, f32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern s32 func_001A22C0(f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern s32 func_00103390(f32 *, f32, f32);
    extern s32 func_00103540(f32 *, f32, f32);
    extern s32 func_00103300(s16 *, s32, s32);
    extern s32 func_0019A5C8();
    Vec4f v[2];
    s32 tx[4];   /* texture ids from func_00103260/90; later reused as the joint position buffer */
    s32 *p;
    s32 ot;
    s32 i;
    s32 r;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2590);
        func_00103890(&g->c0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        func_00103890(&g->cA);
        func_00103890(&g->cB);
        func_00103890(&g->cC);
        func_00103890(&g->cD);
        func_00103890(&g->cH);
        func_00103890(&g->cE);
        func_00103890(&g->cF);
        func_00103890(&g->cG);
        func_00103890(&g->cI);
        func_00103890(&g->cJ);
        func_00103890(&g->cK);
        g->j[0] = func_001F5560(func_001F53A0(), 0x57, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x56, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x47, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x66, 0);
        g->timer = 0x1AA;
        g->t = 1;
        g->code = code;
        g->cnt = 0xA;
        g->xa = 150.0f;
        g->xb = -150.0f;
        g->ang = 50.625f;
        g->fade = 0x80;
        g->line.id = 0x1000;
        g->line.gap = 3;
        g->line.c[2] = 0x80;
        g->line.c[1] = 0x60;
        g->line.c[0] = 0x60;
        g->line.c[3] = 0x20;
        g->line.s[0].id = 0x10000000;
        g->line.s[0].c[2] = 0xF8;
        g->line.s[0].c[1] = 0x38;
        g->line.s[0].c[0] = 0x10;
        g->line.s[0].c[3] = 0x80;
        g->line.s[0].x0 = 0x140;
        g->line.s[0].y0 = 0xE0;
        g->line.s[0].x1 = 0x1D6;
        g->line.s[0].y1 = 0x7A;
        g->line.s[1].id = 0;
        g->line.s[1].c[2] = 0xF8;
        g->line.s[1].c[1] = 0x38;
        g->line.s[1].c[0] = 0x10;
        g->line.s[1].c[3] = 0x80;
        g->line.s[1].x0 = 0x1D6;
        g->line.s[1].y0 = 0x7A;
        g->line.s[1].x1 = 0x26C;
        g->line.s[1].y1 = 0x7A;
        g->disc1.flags = 0x80000;
        g->disc1.c[2] = 0x80;
        g->disc1.c[1] = 0xE0;
        g->disc1.c[0] = 0x80;
        g->disc1.c[3] = 0x80;
        g->disc1.radius = 2.0f;
        g->disc1.count = 0x24;
        g->disc1.height = 0;
        g->disc2.flags = 0x80000;
        g->disc2.c[2] = 0x80;
        g->disc2.c[1] = 0xE0;
        g->disc2.c[0] = 0x80;
        g->disc2.c[3] = 0xFF;
        g->disc2.radius = 1.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        func_00103260(tx, 0xF);
        g->laser.tex = tx[0];
        g->laser.flags = 0x8003;
        g->laser.c[2] = 0x70;
        g->laser.c[1] = 0xD0;
        g->laser.c[0] = 0xA0;
        g->laser.c[3] = 0x80;
        g->laser.uv[0] = 0xC8;
        g->laser.uv[1] = 0x20;
        g->laser.uv[2] = 7;
        g->laser.uv[3] = 0x20;
        g->laser.uv[4] = 0xC8;
        g->laser.uv[5] = 0x20;
        g->laser.uv[6] = 0x100;
        g->laser.uv[7] = 0x100;
        g->laser.size = 30.0f;
        g->laser.h22 = 8;
        g->laser.h24 = 0;
        g->laser.h26 = 0x1E;
        g->laser.h28 = 0x20;
        g->laser.count = 0;
        g->laser.h2C = 1;
        g->trail.tex = tx[0];
        g->trail.flags = 0x9003;
        g->trail.c[2] = 0x80;
        g->trail.c[1] = 0x80;
        g->trail.c[0] = 0x80;
        g->trail.c[3] = 0x30;
        g->trail.size = 3.0f;
        g->trail.uv[0] = 0x80;
        g->trail.uv[1] = 0xC0;
        g->trail.uv[2] = 0x20;
        g->trail.uv[3] = 0x20;
        g->trail.uv[4] = 0x80;
        g->trail.uv[5] = 0xC0;
        g->trail.uv[6] = 0x80;
        g->trail.uv[7] = 0x100;
        g->trail.rate = 0.2f;
        g->trail.a = 0;
        g->trail.b = 0x10;
        g->trail.c34 = 0x20;
        g->trail.count = 0;
        g->trail.e = 8;
        func_00103290(tx, 0);
        g->bandC.mode = 0x80080001;
        g->bandC.scale = 1.0f;
        g->bandC.uv[0] = 0;
        g->bandC.uv[1] = 0x40;
        g->bandC.uv[2] = 0x28;
        g->bandC.uv[3] = 0x14;
        g->bandC.uv[4] = 0;
        g->bandC.uv[5] = 0x40;
        g->bandC.uv[6] = 0x80;
        g->bandC.uv[7] = 0x40;
        g->bandC.rot = 0;
        g->bandC.s[0] = 0;
        g->bandC.s[1] = 1;
        g->bandC.s[2] = 5;
        g->bandC.s[3] = 6;
        g->bandC.s[4] = 0;
        g->bandC.s[5] = 999;
        r = tx[0];
        g->auxC.z = 0.0f;
        g->auxC.y = 0.0f;
        g->auxC.x = 0.0f;
        g->auxC.scale = 40.0f;
        g->auxC.tex = r;
        g->auxC.c[2] = 0x80;
        g->auxC.c[1] = 0x80;
        g->auxC.c[0] = 0x80;
        g->auxC.c[3] = 0x80;
        g->bandC.c[2] = 0x80;
        g->bandC.c[1] = 0x80;
        g->bandC.c[0] = 0x80;
        g->bandC.c[3] = 0x80;
        g->bandD.mode = 0x80080001;
        g->bandD.scale = 1.0f;
        g->bandD.uv[0] = 0x50;
        g->bandD.uv[1] = 0x40;
        g->bandD.uv[2] = 0x20;
        g->bandD.uv[3] = 0x40;
        g->bandD.uv[4] = 0x50;
        g->bandD.uv[5] = 0x40;
        g->bandD.uv[6] = 0x80;
        g->bandD.uv[7] = 0x40;
        g->bandD.rot = 0;
        g->bandD.s[0] = 0;
        g->bandD.s[1] = 0;
        g->bandD.s[2] = 0;
        g->bandD.s[3] = 1;
        g->bandD.s[4] = 0;
        g->bandD.s[5] = 999;
        r = tx[0];
        g->auxD.z = 0.0f;
        g->auxD.y = 0.0f;
        g->auxD.x = 0.0f;
        g->auxD.scale = 60.0f;
        g->auxD.tex = r;
        g->auxD.c[2] = 0x80;
        g->auxD.c[1] = 0x80;
        g->auxD.c[0] = 0x80;
        g->auxD.c[3] = 0x80;
        g->bandD.c[2] = 0x80;
        g->bandD.c[1] = 0x80;
        g->bandD.c[0] = 0x80;
        g->bandD.c[3] = 0x80;
        func_00103290(tx, 0);
        g->bandA.mode = 0x80080003;
        g->bandA.scale = 1.0f;
        g->bandA.uv[0] = 0x40;
        g->bandA.uv[1] = 0;
        g->bandA.uv[2] = 0x40;
        g->bandA.uv[3] = 0x40;
        g->bandA.uv[4] = 0x40;
        g->bandA.uv[5] = 0;
        g->bandA.uv[6] = 0x80;
        g->bandA.uv[7] = 0x40;
        g->bandA.rot = 0;
        g->bandA.s[0] = 0;
        g->bandA.s[1] = 0;
        g->bandA.s[2] = 0;
        g->bandA.s[3] = 1;
        g->bandA.s[4] = 0;
        g->bandA.s[5] = 999;
        r = tx[0];
        g->auxA.z = 0.0f;
        g->auxA.y = 0.0f;
        g->auxA.x = 0.0f;
        g->auxA.scale = 100.0f;
        g->auxA.tex = r;
        g->auxA.c[2] = 0x80;
        g->auxA.c[1] = 0x80;
        g->auxA.c[0] = 0x80;
        g->auxA.c[3] = 0x80;
        g->bandA.c[2] = 0x80;
        g->bandA.c[1] = 0x80;
        g->bandA.c[0] = 0x80;
        g->bandA.c[3] = 0x80;
        g->quad1.tex = tx[0];
        g->quad1.flags = 0x80000;
        g->quad1.c[2] = 0x80;
        g->quad1.c[1] = 0x80;
        g->quad1.c[0] = 0x80;
        g->quad1.c[3] = 0x80;
        g->quad1.size = 165.0f;
        g->quad1.uv[0] = 0;
        g->quad1.uv[1] = 0;
        g->quad1.uv[2] = 0x40;
        g->quad1.uv[3] = 0x40;
        g->quad1.rot[0] = 0;
        g->quad1.rot[1] = 0;
        g->quad1.rot[2] = 0xF00;
        func_00103290(tx, 1);
        g->quad2.tex = tx[0];
        g->quad2.flags = 0x80000;
        g->quad2.c[2] = 0x80;
        g->quad2.c[1] = 0x80;
        g->quad2.c[0] = 0x80;
        g->quad2.c[3] = 0x80;
        g->quad2.size = 85.0f;
        g->quad2.uv[0] = 0;
        g->quad2.uv[1] = 0;
        g->quad2.uv[2] = 0x40;
        g->quad2.uv[3] = 0x40;
        g->quad2.rot[0] = 0;
        g->quad2.rot[1] = 0;
        g->quad2.rot[2] = -0xF00;
        g->bandH.mode = 0x80080003;
        g->bandH.scale = 1.0f;
        g->bandH.uv[0] = 0x60;
        g->bandH.uv[1] = 0xA;
        g->bandH.uv[2] = 0x14;
        g->bandH.uv[3] = 0x28;
        g->bandH.uv[4] = 0x60;
        g->bandH.uv[5] = 0xA;
        g->bandH.uv[6] = 0x80;
        g->bandH.uv[7] = 0x40;
        g->bandH.rot = -0x5A;
        g->bandH.s[0] = 0;
        g->bandH.s[1] = 0;
        g->bandH.s[2] = 0;
        g->bandH.s[3] = 1;
        g->bandH.s[4] = 0;
        g->bandH.s[5] = 999;
        r = tx[0];
        g->auxH.z = 0.0f;
        g->auxH.y = 0.0f;
        g->auxH.x = 0.0f;
        g->auxH.scale = 30.0f;
        g->auxH.tex = r;
        g->auxH.c[2] = 0x80;
        g->auxH.c[1] = 0x80;
        g->auxH.c[0] = 0x80;
        g->auxH.c[3] = 0x80;
        g->bandH.c[2] = 0x80;
        g->bandH.c[1] = 0x80;
        g->bandH.c[0] = 0x80;
        g->bandH.c[3] = 0x80;
        g->bandE.mode = 0x80080023;
        g->bandE.scale = 1.0f;
        g->bandE.uv[0] = 0x40;
        g->bandE.uv[1] = 0xA;
        g->bandE.uv[2] = 0x20;
        g->bandE.uv[3] = 0;
        g->bandE.uv[4] = 0x40;
        g->bandE.uv[5] = 0xA;
        g->bandE.uv[6] = 0x80;
        g->bandE.uv[7] = 0x40;
        g->bandE.rot = 0;
        g->bandE.s[0] = 0;
        g->bandE.s[1] = 0;
        g->bandE.s[2] = 0;
        g->bandE.s[3] = 1;
        g->bandE.s[4] = 0;
        g->bandE.s[5] = 999;
        r = tx[0];
        g->auxE.z = 0.0f;
        g->auxE.y = 0.0f;
        g->auxE.x = 0.0f;
        g->auxE.scale = 30.0f;
        g->auxE.tex = r;
        g->auxE.c[2] = 0x80;
        g->auxE.c[1] = 0x80;
        g->auxE.c[0] = 0x80;
        g->auxE.c[3] = 0x80;
        g->bandE.c[2] = 0x80;
        g->bandE.c[1] = 0x80;
        g->bandE.c[0] = 0x80;
        g->bandE.c[3] = 0x80;
        g->bandF.mode = 0x80080023;
        g->bandF.scale = 1.0f;
        g->bandF.uv[0] = 0x40;
        g->bandF.uv[1] = 0xA;
        g->bandF.uv[2] = 0x20;
        g->bandF.uv[3] = 5;
        g->bandF.uv[4] = 0x40;
        g->bandF.uv[5] = 0xA;
        g->bandF.uv[6] = 0x80;
        g->bandF.uv[7] = 0x40;
        g->bandF.rot = 0;
        g->bandF.s[0] = 0;
        g->bandF.s[1] = 0;
        g->bandF.s[2] = 0;
        g->bandF.s[3] = 1;
        g->bandF.s[4] = 0;
        g->bandF.s[5] = 999;
        r = tx[0];
        g->auxF.z = 0.0f;
        g->auxF.y = 0.0f;
        g->auxF.x = 0.0f;
        g->auxF.scale = 30.0f;
        g->auxF.tex = r;
        g->auxF.c[2] = 0x80;
        g->auxF.c[1] = 0x80;
        g->auxF.c[0] = 0x80;
        g->auxF.c[3] = 0x80;
        g->bandF.c[2] = 0x80;
        g->bandF.c[1] = 0x80;
        g->bandF.c[0] = 0x80;
        g->bandF.c[3] = 0x80;
        g->bandG.mode = 0x80080023;
        g->bandG.scale = 1.0f;
        g->bandG.uv[0] = 0x40;
        g->bandG.uv[1] = 0;
        g->bandG.uv[2] = 0x40;
        g->bandG.uv[3] = 0xA;
        g->bandG.uv[4] = 0x40;
        g->bandG.uv[5] = 0;
        g->bandG.uv[6] = 0x80;
        g->bandG.uv[7] = 0x40;
        g->bandG.rot = 0;
        g->bandG.s[0] = 0;
        g->bandG.s[1] = 0;
        g->bandG.s[2] = 0;
        g->bandG.s[3] = 1;
        g->bandG.s[4] = 0;
        g->bandG.s[5] = 999;
        r = tx[0];
        g->auxG.z = 0.0f;
        g->auxG.y = 0.0f;
        g->auxG.x = 0.0f;
        g->auxG.scale = 60.0f;
        g->auxG.tex = r;
        g->auxG.c[2] = 0x80;
        g->auxG.c[1] = 0x80;
        g->auxG.c[0] = 0x80;
        g->auxG.c[3] = 0x80;
        g->bandG.c[2] = 0x80;
        g->bandG.c[1] = 0x80;
        g->bandG.c[0] = 0x80;
        g->bandG.c[3] = 0x80;
        g->mark1.tex = tx[0];
        g->mark1.flags = 0x80000;
        g->mark1.scale = 1.0f;
        g->mark1.rz = 0;
        g->mark1.y = 85.0f;
        g->mark1.c[2] = 0x80;
        g->mark1.c[1] = 0x80;
        g->mark1.c[0] = 0x80;
        g->mark1.c[3] = 0x80;
        g->mark1.uv[0] = 0x60;
        g->mark1.uv[1] = 0x32;
        g->mark1.uv[2] = 0x20;
        g->mark1.uv[3] = 0xE;
        g->mark1.uv[4] = 0x60;
        g->mark1.uv[5] = 0x32;
        g->mark1.uv[6] = 0x80;
        g->mark1.uv[7] = 0x40;
        g->mark2.tex = tx[0];
        g->mark2.flags = 0x80000;
        g->mark2.scale = 1.0f;
        g->mark2.rz = 0x4000;
        g->mark2.y = 85.0f;
        g->mark2.c[2] = 0x80;
        g->mark2.c[1] = 0x80;
        g->mark2.c[0] = 0x80;
        g->mark2.c[3] = 0x80;
        g->mark2.uv[0] = 0x60;
        g->mark2.uv[1] = 0x32;
        g->mark2.uv[2] = 0x20;
        g->mark2.uv[3] = 0xE;
        g->mark2.uv[4] = 0x60;
        g->mark2.uv[5] = 0x32;
        g->mark2.uv[6] = 0x80;
        g->mark2.uv[7] = 0x40;
        func_00103290(tx, 3);
        g->emit1.tex = tx[0];
        g->emit1.flags = 0x20000003;
        g->emit1.c[2] = 0x80;
        g->emit1.c[1] = 0x80;
        g->emit1.c[0] = 0x80;
        g->emit1.c[3] = 0x80;
        g->emit1.f20 = 1.0f;
        g->emit1.f24 = 6.0f;
        g->emit1.uv[0] = 0;
        g->emit1.uv[1] = 0;
        g->emit1.uv[2] = 0x20;
        g->emit1.uv[3] = 0x20;
        g->emit1.uv[4] = 0;
        g->emit1.uv[5] = 0;
        g->emit1.uv[6] = 0x80;
        g->emit1.uv[7] = 0x40;
        g->emit1.parts = g->parts1;
        g->emit1.radius = 10.0f;
        g->emit1.count = 0x100;
        g->emit1.life = 5;
        g->emit1.f2F = 0;
        { extern s32 b773_01E00890(void *, s32, f32); b773_01E00890(&g->emit1, 0xC, 3.0f); }
        g->emit2.tex = tx[0];
        g->emit2.flags = 0x20000003;
        g->emit2.c[2] = 0x80;
        g->emit2.c[1] = 0x80;
        g->emit2.c[0] = 0x80;
        g->emit2.c[3] = 0x80;
        g->emit2.f20 = 1.0f;
        g->emit2.f24 = 6.0f;
        g->emit2.uv[0] = 0;
        g->emit2.uv[1] = 0;
        g->emit2.uv[2] = 0x20;
        g->emit2.uv[3] = 0x20;
        g->emit2.uv[4] = 0;
        g->emit2.uv[5] = 0;
        g->emit2.uv[6] = 0x80;
        g->emit2.uv[7] = 0x40;
        g->emit2.parts = g->parts2;
        g->emit2.radius = 10.0f;
        g->emit2.count = 0x40;
        g->emit2.life = 5;
        g->emit2.f2F = 0;
        { extern s32 b773_01E00890(void *, s32, f32); b773_01E00890(&g->emit2, 0xC, 3.0f); }
        func_00103290(tx, 2);
        g->eye1.tex = tx[0];
        g->eye1.flags = 0;
        g->eye1.c[2] = 0x80;
        g->eye1.c[1] = 0x80;
        g->eye1.c[0] = 0x80;
        g->eye1.c[3] = 0x80;
        g->eye1.w = 0.25f;
        g->eye1.h = 2.0f;
        g->eye1.w2 = 0.25f;
        g->eye1.h2 = 0.5f;
        g->eye1.uv[0] = 0;
        g->eye1.uv[1] = 0x20;
        g->eye1.uv[2] = 0x20;
        g->eye1.uv[3] = 0x20;
        g->eye1.rot[0] = 0;
        g->eye1.rot[1] = 0;
        g->eye1.rot[2] = 0;
        g->eye2.tex = tx[0];
        g->eye2.flags = 0;
        g->eye2.c[2] = 0x80;
        g->eye2.c[1] = 0x80;
        g->eye2.c[0] = 0x80;
        g->eye2.c[3] = 0x80;
        g->eye2.w = 0.25f;
        g->eye2.h = 2.0f;
        g->eye2.w2 = 0.25f;
        g->eye2.h2 = 0.5f;
        g->eye2.uv[0] = 0;
        g->eye2.uv[1] = 0x20;
        g->eye2.uv[2] = 0x20;
        g->eye2.uv[3] = 0x20;
        g->eye2.rot[0] = 0;
        g->eye2.rot[1] = 0;
        g->eye2.rot[2] = 0;
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->cam2.pos);
    func_001F5620(func_001F53A0(), g->j[2], &g->cI.pos);
    func_001F5620(func_001F53A0(), g->j[3], &g->cJ.pos);
    if (g->cnt == 0) {
        func_001F5F90(func_001F53A0(), &v[0]);
        func_001F5F90(func_001F5380(), &v[1]);
        func_001F5F90(func_001F5380(), &g->cam4.pos);
        func_00103DB0(&v[0], &v[1], &g->cam4.rot);
    } else if (g->t == 0x154) {
        func_001F5620(func_001F53A0(), g->j[0], &g->cam3.pos);
        func_001F5620(func_001F53A0(), g->j[0], &v[0]);
        func_001F5620(func_001F53A0(), g->j[1], &v[1]);
        func_001F5620(func_001F53A0(), g->j[0], &g->cam4.pos);
        func_00103DB0(&v[0], &v[1], &g->cam4.rot);
    }
    if (g->t == 0x17C) {
        func_001F5F90(func_001F5380(), &g->cam3.pos);
        func_001F5F90(func_001F53A0(), &v[0]);
        func_001F5F90(func_001F5380(), &v[1]);
        func_001036E0(&v[0], &v[1], &g->cam1.pos);
        g->cnt = 0xA;
        g->laser.count = 0;
        g->laser.size = 60.0f;
    }
    if (g->t == 0x154) {
        func_001F5620(func_001F53A0(), g->j[0], &g->cam1.pos);
    }
    if (g->t >= 0x154) {
        func_01E03ED0_b773((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->lpts, (f32 *)&g->cam1.pos);
        func_00104490(&g->cam1.pos, &g->cam2.pos, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
        }
    }
    if (g->t >= 0x64 && g->t < 0x7D) {
        func_001F5620(func_001F53A0(), g->j[4], p = tx);
        func_01E02E50_b773((Trail_b025_01E01EF0 *)&g->trail, (Pt_b025_01E01EF0 *)g->tpts, (Vec_b025_01E01EF0 *)p);
    }
    func_001038D0(&g->c0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001039A0(&g->cam3);
    func_00103920(&g->cA, g->xa, 0.0f);
    func_00103920(&g->cB, g->xb, 0.0f);
    func_00103920(&g->cC, -220.0f, 90.0f);
    func_00103920(&g->cD, -220.0f, 0.0f);
    func_00103920(&g->cH, -220.0f, -90.0f);
    func_00103920(&g->cE, -220.0f, g->ang);
    func_00103920(&g->cF, -220.0f, -55.0f);
    func_00103920(&g->cG, 220.0f, -120.0f);
    func_001038D0(&g->cam4);
    func_001039A0(&g->cI);
    func_001039A0(&g->cJ);
    func_00103920(&g->cK, g->xa, 0.0f);
    if (g->t >= 0x8E) {
        func_01E025F0_b773(ot, (Spr_b007_01E017F0 *)&g->eye1, (Cam_b007_01E017F0 *)&g->cI);
        func_01E025F0_b773(ot, (Spr_b007_01E017F0 *)&g->eye2, (Cam_b007_01E017F0 *)&g->cJ);
    }
    if (g->t >= 0xA6 && g->t < 0x13D) {
        func_01E038D0_b773(ot, (Mark_b773_01E038D0 *)&g->mark1, (Cam_b007_01E017F0 *)&g->cK);
        func_01E038D0_b773(ot, (Mark_b773_01E038D0 *)&g->mark2, (Cam_b007_01E017F0 *)&g->cK);
        func_01E02B80_b773(ot, (Line_b773_01E02B80 *)&g->line);
        func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandA, (Part_b000_01E02A30 *)&g->auxA, (Cam_b000_01E02A30 *)&g->cA);
        func_01E017B0_b773(ot, (Spr_b773_01E017B0 *)&g->quad1, (Cam_b773_01E017B0 *)&g->cB);
        if (g->t / 10 % 3 != 0) {
            func_01E017B0_b773(ot, (Spr_b773_01E017B0 *)&g->quad2, (Cam_b773_01E017B0 *)&g->cB);
        }
        if (g->quad1.rot[2] != 0) {
            g->quad1.rot[2] -= 0x80;
        }
        if (g->quad2.rot[2] != 0) {
            g->quad2.rot[2] += 0x80;
        }
        func_00103540(&g->xa, 0.0f, 5.0f);
        if (func_00103390(&g->xb, 0.0f, 5.0f) == 0) {
            func_00103470(&g->quad1.c[3], 0x20, 0x10);
            if (g->t % 10 < 5) {
                func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandG, (Part_b000_01E02A30 *)&g->auxG, (Cam_b000_01E02A30 *)&g->cG);
            }
            func_01E00120_b773(ot, (Line_b773_01E00120 *)&g->line.s[0]);
            func_01E00120_b773(ot, (Line_b773_01E00120 *)&g->line.s[1]);
            func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandD, (Part_b000_01E02A30 *)&g->auxD, (Cam_b000_01E02A30 *)&g->cD);
            func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandE, (Part_b000_01E02A30 *)&g->auxE, (Cam_b000_01E02A30 *)&g->cE);
            func_00103540(&g->ang, 0.0f, 2.8125f);
            if (func_00103300(&g->bandE.uv[3], 0x36, 3) == 0) {
                if (g->t % 3 != 0) {
                    func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandH, (Part_b000_01E02A30 *)&g->auxH, (Cam_b000_01E02A30 *)&g->cH);
                    func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandF, (Part_b000_01E02A30 *)&g->auxF, (Cam_b000_01E02A30 *)&g->cF);
                }
                if (g->t / 10 % 2 != 0) {
                    g->mark1.y = g->mark2.y = 80.0f;
                } else {
                    g->mark1.y = g->mark2.y = 85.0f;
                }
            }
            func_01E01D60_b773(ot, (Spr_b000_01E02A30 *)&g->bandC, (Part_b000_01E02A30 *)&g->auxC, (Cam_b000_01E02A30 *)&g->cC);
        }
    }
    if (g->t == 0xA5) {
        g->fade = 0x40;
    }
    if (g->t == 0x13D) {
        g->fade = 0x80;
    }
    if (g->t >= 0x64 && g->t < 0x91) {
        func_01E02F30_b773(ot, (Em_b025_01E01FD0 *)&g->trail, (Part_b025_01E01FD0 *)g->tpts, (Cam_b025_01E01FD0 *)&g->c0);
        for (i = 0; i < g->trail.count; i++) {
            func_00103470(&g->tpts[i].c, 0, 2);
        }
    }
    if (g->t >= 0x154 && g->t < 0x17A) {
        func_01E00330_b773(ot, (Disc_b540_01E00250 *)&g->disc1, (Cam_b540_01E00250 *)&g->cam3);
        func_01E00330_b773(ot, (Disc_b540_01E00250 *)&g->disc2, (Cam_b540_01E00250 *)&g->cam3);
        if (func_001033D0(&g->cam3, 5.0f, 0.5f) == 0) {
            func_00103470(&g->disc1.c[3], 0, 8);
            func_00103470(&g->disc2.c[3], 0, 8);
        }
        func_01E00A50_b773(ot, (Emit_b489_01E00240 *)&g->emit2, (Cam_b489_01E00240 *)&g->cam4);
        func_00103470(&g->emit2.c[3], 0, 0x10);
        for (i = 0; i < g->emit2.count; i++) {
            g->parts2[i].x *= 1.2f;
            g->parts2[i].y *= 1.2f;
            g->parts2[i].z *= 1.2f;
        }
    }
    if (g->t == 0x182) {
        g->cam3.x = g->cam3.y = g->cam3.z = 1.0f;
        g->disc1.c[3] = 0x80;
        g->disc2.c[3] = 0xFF;
    }
    if (g->t >= 0x182) {
        func_01E00330_b773(ot, (Disc_b540_01E00250 *)&g->disc1, (Cam_b540_01E00250 *)&g->cam3);
        func_01E00330_b773(ot, (Disc_b540_01E00250 *)&g->disc2, (Cam_b540_01E00250 *)&g->cam3);
        func_001033D0(&g->cam3, 50.0f, 0.5f);
        if (g->cam3.x > 10.0f) {
            func_00103470(&g->disc1.c[3], 0, 8);
            func_00103470(&g->disc2.c[3], 0, 0x10);
        }
    }
    if (g->cnt == 0) {
        func_01E00A50_b773(ot, (Emit_b489_01E00240 *)&g->emit1, (Cam_b489_01E00240 *)&g->cam4);
        for (i = 0; i < g->emit1.count; i++) {
            if (g->parts1[i].t >= 0) {
                g->parts1[i].x *= 1.4f;
                g->parts1[i].y *= 1.4f;
                g->parts1[i].z *= 1.4f;
                if (g->parts1[i].y > 20.0f) {
                    r = func_001A22C0(10.0f * g->emit1.radius);
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (f32)(func_0019A5C8() % r);
                    g->parts1[i].y = 4.0f;
                    g->parts1[i].z = d * func_0020B480(a);
                    g->parts1[i].x = d * func_0020B550(a);
                    g->parts1[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
        if (g->t > 0x19A) {
            func_00103470(&g->emit1.c[3], 0, 8);
        }
    }
    if (g->t > 0x154) {
        func_01E04020_b773(ot, (Laser_b117_01E00270 *)&g->laser, (Pt_b117_01E00270 *)g->lpts, (Cam_b117_01E00270 *)&g->c0);
        if (g->cnt == 0) {
            func_00103540(&g->laser.size, 0.0f, 3.0f);
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x19A) {
        return 2;
    }
    if (g->t == 0x178) {
        return 1;
    }
    if (g->t >= 0x182 && g->t < 0x19A) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
