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

static void func_01E00080_b103(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b001:01E00900, 73 insns, 54 copies: one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b001_01E00900;

typedef struct {
    Hdr_b001_01E00900 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b001_01E00900;

static s32 func_01E00120_b103(void) {
    Pkt_b001_01E00900 p __attribute__((aligned(8)));

    ((Hdr_b001_01E00900 *)(s32)&p)->count = 0x26;
    ((Hdr_b001_01E00900 *)(s32)&p)->tag = 5;
    ((Hdr_b001_01E00900 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b001_01E00900 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0x60;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    return 0;
}

/* shape b000:01E00400, 87 insns, 46 copies: one flat-coloured full-screen quad (GS sprite packet, far z). The tag
   is written through a pointer that went through u32 (a plain &pk gets folded into $sp offsets). */

typedef struct Xyz_b000_01E00400 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b000_01E00400;

typedef struct Pk_b000_01E00400 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00400 v[4];
} Pk_b000_01E00400;

typedef struct Src_b000_01E00400 {
    u8 b, g, r, a;
} Src_b000_01E00400;

static inline void b000_01E00400_tag(Pk_b000_01E00400 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00250_b103(s32 arg0, Src_b000_01E00400 *c) {
    Pk_b000_01E00400 pk;

    b000_01E00400_tag((Pk_b000_01E00400 *)(u32)&pk, 5, 4, 0x44441);
    func_002086D0((Pk_b000_01E00400 *)(u32)&pk, ((u64)0x80 << 32) | 0x48);
    pk.r = c->r;
    pk.g = c->g;
    pk.b = c->b;
    pk.a = c->a;
    pk.q = 1.0f;
    pk.v[0].x = 0x6000;
    pk.v[0].y = 0x7000;
    pk.v[0].z = 0xFFFFFF;
    pk.v[0].fog = 0;
    pk.v[1].x = 0xA000;
    pk.v[1].y = 0x7000;
    pk.v[1].z = 0xFFFFFF;
    pk.v[1].fog = 0;
    pk.v[2].x = 0x6000;
    pk.v[2].y = 0x9000;
    pk.v[2].z = 0xFFFFFF;
    pk.v[2].fog = 0;
    pk.v[3].x = 0xA000;
    pk.v[3].y = 0x9000;
    pk.v[3].z = 0xFFFFFF;
    pk.v[3].fog = 0;
    func_002075F0((s32)&pk, arg0, 0);
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

static s32 func_01E003B0_b103(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E00910_b103(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
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
    func_01E00080_b103((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
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

static s32 func_01E011A0_b103(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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
static s32 func_01E01360_b103(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
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

static s32 func_01E020C0_b103(Trail_b025_01E01EF0 *o, Pt_b025_01E01EF0 *pts, Vec_b025_01E01EF0 *pos) {
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

static s32 func_01E021A0_b103(s32 obj, Em_b025_01E01FD0 *o, Part_b025_01E01FD0 *pts, Cam_b025_01E01FD0 *cam) {
    extern Quad_b025_01E01FD0 D_01E03500_b103;
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

    in = D_01E03500_b103;
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

/* shape b103:01E02B40 (b103), 616 insns, 1 copy: b103 scene manager: code >= 0 sets up the trail, the disc, the band
   sprite and two 128-particle emitters; else follows joints (then drifts the camera), flashes from 90 to 157, fades
   the screen from 310, draws disc/band from 146, the first emitter and trail in 292..325, the second from 292;
   returns 2/1/6/8 by tick */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b103_01E02B40;

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
} Spot_b103_01E02B40;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Pt_b103_01E02B40;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b103_01E02B40;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 scale;
    u8 c[4];
    s32 mode;
    u8 pad3C[0xC];
    s16 s[6];
    u8 pad54[0xC];
} Band_b103_01E02B40;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Aux_b103_01E02B40;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Pt_b103_01E02B40 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 life;
    u8 f2F;
} Emit_b103_01E02B40;

typedef struct {
    Crd_b103_01E02B40 m0;
    Spot_b103_01E02B40 trail;
    Pt_b103_01E02B40 pts[24];
    Crd_b103_01E02B40 cam1;
    Disc_b103_01E02B40 disc;
    Band_b103_01E02B40 band;
    Aux_b103_01E02B40 aux;
    Crd_b103_01E02B40 cam2;
    Crd_b103_01E02B40 cam3;
    Emit_b103_01E02B40 emit1;
    Pt_b103_01E02B40 parts1[128];
    Crd_b103_01E02B40 cam4;
    Emit_b103_01E02B40 emit2;
    Pt_b103_01E02B40 parts2[128];
    s32 timer;
    s32 t;
    s32 code;
    s32 cnt;
    s32 ja;
    s32 jb;
    u8 c[4];
    u8 pad14FC[4];
} Scene_b103_01E02B40;

static s32 func_01E02B40_b103(s32 arg0, s32 code) {
    Scene_b103_01E02B40 *g = (Scene_b103_01E02B40 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103290(s32 *, s32);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_001043F0(void *, f32);
    extern s32 func_001A22C0(f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001033D0(void *, f32, f32);
    extern s32 func_0019A5C8();
    Vec4f v[2];
    Vec4f p;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 r;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1500);
        func_00103890(&g->m0);
        func_00103890(&g->cam1);
        g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        g->ja = func_001F5560(func_001F53A0(), 0xB, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x1A, 0);
        g->timer = 0x154;
        g->t = 1;
        g->code = code;
        g->cnt = 0x12;
        g->c[2] = 0xC0;
        g->c[1] = 0x80;
        g->c[0] = 0xA0;
        g->c[3] = 0;
        g->disc.flags = 0;
        g->disc.c[2] = 0xA0;
        g->disc.c[1] = 0x60;
        g->disc.c[0] = 0x80;
        g->disc.c[3] = 0;
        g->disc.radius = 4.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        func_00103290(tx, 2);
        g->band.mode = 3;
        g->band.uv[0] = 0;
        g->band.uv[1] = 0;
        g->band.uv[2] = 0x40;
        g->band.uv[3] = 0x40;
        g->band.uv[4] = 0;
        g->band.uv[5] = 0;
        g->band.uv[6] = 0x80;
        g->band.uv[7] = 0x80;
        g->band.scale = 1.0f;
        g->band.c[2] = 0x80;
        g->band.c[1] = 0x80;
        g->band.c[0] = 0x80;
        g->band.c[3] = 0;
        g->band.s[0] = 0;
        g->band.s[1] = 2;
        g->band.s[2] = 3;
        g->band.s[3] = 4;
        g->band.s[4] = 0;
        g->band.s[5] = 999;
        r = tx[0];
        g->aux.z = 0.0f;
        g->aux.y = 0.0f;
        g->aux.x = 0.0f;
        g->aux.scale = 3.0f;
        g->aux.tex = r;
        g->aux.c[2] = 0x80;
        g->aux.c[1] = 0x80;
        g->aux.c[0] = 0x80;
        g->aux.c[3] = 0x80;
        func_00103290(tx, 0);
        g->trail.tex = tx[0];
        g->trail.c[2] = 0x80;
        g->trail.c[1] = 0x80;
        g->trail.c[0] = 0x80;
        g->trail.c[3] = 0x50;
        g->trail.flags = 0x8003;
        g->trail.size = 20.0f;
        g->trail.uv[0] = 0x9C;
        g->trail.uv[1] = 0;
        g->trail.uv[2] = 0x40;
        g->trail.uv[3] = 0x40;
        g->trail.uv[4] = 0x9C;
        g->trail.uv[5] = 0;
        g->trail.uv[6] = 0x100;
        g->trail.uv[7] = 0x80;
        g->trail.rate = 0.1f;
        g->trail.a = 0;
        g->trail.b = 0x10;
        g->trail.c34 = 0x18;
        g->trail.count = 0;
        g->trail.e = 1;
        func_00103290(tx, 1);
        g->emit1.tex = tx[0];
        g->emit1.flags = 0x20000003;
        g->emit1.c[2] = 0x80;
        g->emit1.c[1] = 0x80;
        g->emit1.c[0] = 0x80;
        g->emit1.c[3] = 0x80;
        g->emit1.f20 = 0.5f;
        g->emit1.f24 = 5.0f;
        g->emit1.uv[0] = 0;
        g->emit1.uv[1] = 0;
        g->emit1.uv[2] = 0x20;
        g->emit1.uv[3] = 0x20;
        g->emit1.uv[4] = 0;
        g->emit1.uv[5] = 0;
        g->emit1.uv[6] = 0x80;
        g->emit1.uv[7] = 0x40;
        g->emit1.parts = g->parts1;
        g->emit1.radius = 5.0f;
        g->emit1.count = 0x80;
        g->emit1.life = 8;
        g->emit1.f2F = 0;
        func_01E011A0_b103((Obj_b015_01E01620 *)&g->emit1, 0xC, 4.0f);
        g->emit2.tex = tx[0];
        g->emit2.flags = 3;
        g->emit2.c[2] = 0x80;
        g->emit2.c[1] = 0x80;
        g->emit2.c[0] = 0x80;
        g->emit2.c[3] = 0;
        g->emit2.f20 = 0.5f;
        g->emit2.f24 = 5.0f;
        g->emit2.uv[0] = 0;
        g->emit2.uv[1] = 0;
        g->emit2.uv[2] = 0x20;
        g->emit2.uv[3] = 0x20;
        g->emit2.uv[4] = 0;
        g->emit2.uv[5] = 0;
        g->emit2.uv[6] = 0x80;
        g->emit2.uv[7] = 0x40;
        g->emit2.parts = g->parts2;
        g->emit2.radius = 5.0f;
        g->emit2.count = 0x80;
        g->emit2.life = 8;
        g->emit2.f2F = 0;
        func_01E011A0_b103((Obj_b015_01E01620 *)&g->emit2, 0xC, 4.0f);
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->cam2.pos);
    if (g->t < 0x124) {
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        func_001036E0(&v[0], &v[1], &g->cam1.pos);
    } else {
        func_00104490(&g->cam1.pos, &g->cam2.pos, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
        }
        func_01E020C0_b103((Trail_b025_01E01EF0 *)&g->trail, (Pt_b025_01E01EF0 *)g->pts,
                           (Vec_b025_01E01EF0 *)&g->cam1.pos);
    }
    func_001F5F90(func_001F53A0(), &v[0]);
    g->cam4.pos = g->cam1.pos;
    g->cam3.pos = g->cam4.pos;
    func_00103DB0(&v[0], &g->cam2.pos, &g->cam3.rot);
    func_001038D0(&g->m0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001038D0(&g->cam3);
    func_001038D0(&g->cam4);
    if (g->t >= 0x5A && g->t < 0x9E) {
        func_01E00120_b103();
    }
    if (g->t >= 0x136) {
        func_01E00250_b103(ot, (Src_b000_01E00400 *)g->c);
        if (g->t < 0x146) {
            func_001032C0(&g->c[3], 0xFF, 0x10);
        } else {
            func_00103470(&g->c[3], 0, 0x20);
        }
    }
    if (g->t > 0x91) {
        func_01E003B0_b103(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam1);
        func_01E00910_b103(ot, (Spr_b000_01E02A30 *)&g->band, (Part_b000_01E02A30 *)&g->aux,
                           (Cam_b000_01E02A30 *)&g->cam1);
        if (g->t < 0x124) {
            { f32 x = 1.0f; f32 h = 0.05f; func_001033D0(&g->cam1, x, h); }
            func_001032C0(&g->disc.c[3], 0xFF, 0x20);
            func_001032C0(&g->band.c[3], 0x80, 0x10);
        }
    }
    if (g->t >= 0x124 && g->t < 0x146) {
        func_01E01360_b103(ot, (Emit_b489_01E00240 *)&g->emit1, (Cam_b489_01E00240 *)&g->cam3);
        if (g->t > 0x146) {
            func_00103470(&g->emit1.c[3], 0, 8);
        }
        for (i = 0; i < g->emit1.count; i++) {
            if (g->parts1[i].t >= 0) {
                g->parts1[i].x *= 1.2f;
                g->parts1[i].y *= 1.2f;
                g->parts1[i].z *= 1.2f;
                if (g->parts1[i].y > 30.0f) {
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
        func_01E021A0_b103(ot, (Em_b025_01E01FD0 *)&g->trail, (Part_b025_01E01FD0 *)g->pts,
                           (Cam_b025_01E01FD0 *)&g->m0);
        for (i = 0; i < g->trail.count; i++) {
            func_00103470(&g->pts[i].c, 0, 5);
        }
    }
    if (g->t == 0x146) {
        g->emit2.c[3] = 0x80;
        for (i = 0; i < g->emit2.count; i++) {
            g->parts2[i].c = 0x80;
        }
    }
    if (g->t >= 0x124) {
        func_01E01360_b103(ot, (Emit_b489_01E00240 *)&g->emit2, (Cam_b489_01E00240 *)&g->cam4);
        if (g->t > 0x146) {
            func_00103470(&g->emit2.c[3], 0, 8);
        }
        for (i = 0; i < g->emit2.count; i++) {
            if (g->parts2[i].t >= 0) {
                g->parts2[i].x *= 1.4f;
                g->parts2[i].y *= 1.4f;
                g->parts2[i].z *= 1.4f;
                if (g->parts2[i].t > 8) {
                    func_001043F0(&p, 1.0f);
                    g->parts2[i].y = p.y;
                    g->parts2[i].z = p.z;
                    g->parts2[i].x = p.x;
                    g->parts2[i].t = -(func_0019A5C8() % 12);
                    g->parts2[i].c = g->emit2.c[3];
                }
            }
        }
    }
    if (g->cnt == 0) {
        func_001033D0(&g->cam1, 10.0f, 1.0f);
        func_00103470(&g->disc.c[3], 0, 0x10);
        func_00103470(&g->band.c[3], 0, 8);
        func_00103470(&g->trail.c[3], 0, 5);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x146) {
        return 2;
    }
    if (g->t == 0x12C) {
        return 1;
    }
    if (g->t >= 0x136 && g->t < 0x146) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
