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

static void func_01E00080_b244(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b244(void) {
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

static s32 func_01E00250_b244(s32 arg0, Src_b000_01E00400 *c) {
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

static s32 func_01E003B0_b244(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E00910_b244(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
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
    func_01E00080_b244((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
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

static s32 func_01E011A0_b244(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b244", func_01E01360_b244);

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

static s32 func_01E020C0_b244(Trail_b025_01E01EF0 *o, Pt_b025_01E01EF0 *pts, Vec_b025_01E01EF0 *pos) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b244", func_01E021A0_b244);

/* shape b244:01E02B40 (b244), 344 insns, 1 copy: b244 scene manager: with a code it clears the scene (0x47D0), resets
   its 19 matrices, keeps joint 0x2F, a 202-tick timer, the code, colour (0x70,0xB0,0xE0,0xFF), six groups starting
   30+25i and fading 60+25i, their points, bands, spots and line particles (LkPrim_SetLineParticle, 12, 4.0);
   otherwise it moves the six actors, runs the auto-blur from tick 30 to 184 and the flash after, steps every group,
   and returns 2 / 1 at ticks 185 / 50, 6 from 60 to 184, 8 when the timer ends */

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
    s16 d;
    s16 e;
    u8 pad3E[2];
} Spot_b244_01E02B40;

typedef struct {
    s32 zero;
    u8 c[4];
    f32 scale;
    s16 n;
    s16 k;
} Pt_b244_01E02B40;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 scale;
    u8 c[4];
    s32 mode;
    u8 pad3C[0xC];
    s16 s[6];
    u8 pad54[0xC];
} Band_b244_01E02B40;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Aux_b244_01E02B40;

typedef struct {
    u8 pad0[0x20];
    u8 m[0x50];
} Mat_b244_01E02B40;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 life;
    u8 f2F;
} Grp_b244_01E02B40;

typedef struct {
    u8 m0[0x70];
    Spot_b244_01E02B40 spot[6];
    u8 *list[6];
    u8 pad208[8];
    u8 buf[6][0x180];
    Mat_b244_01E02B40 ma[6];
    Pt_b244_01E02B40 pt[6];
    Band_b244_01E02B40 band[6];
    Aux_b244_01E02B40 aux[6];
    Mat_b244_01E02B40 mb[6];
    Mat_b244_01E02B40 mc[6];
    Grp_b244_01E02B40 grp[6];
    u8 parts[6][0x800];
    s32 flag[6];
    s32 start[6];
    s32 fade[6];
    s32 timer;
    s32 t;
    s32 code;
    s32 joint;
    u8 c[4];
} Scene_b244_01E02B40;

/* scatters one group's line particles (inline: written as a direct call the group address loads before 4.0f) */
static inline void Set_b244_01E02B40(void *p) {
    func_01E011A0_b244((Obj_b015_01E01620 *)p, 12, 4.0f);
}

static s32 func_01E02B40_b244(s32 arg0, s32 code) {
    Scene_b244_01E02B40 *g = (Scene_b244_01E02B40 *)arg0;
    extern void b244_01E030A0(Scene_b244_01E02B40 *, s32, s32);
    extern void b244_01E031E0(Scene_b244_01E02B40 *, s32, s32);
    extern void b244_01E03300(Scene_b244_01E02B40 *, s32, s32);
    extern void b244_01E035B0(Scene_b244_01E02B40 *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00103290(s32 *, s32);
    extern void func_00103470(u8 *, s32, s32);
    s32 tx[4];
    s32 t;
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x47D0);
        func_00103890(g);
        for (i = 0; i < 6; i++) {
            func_00103890(&g->ma[i]);
            func_00103890(&g->mb[i]);
            func_00103890(&g->mc[i]);
        }
        g->joint = func_001F5560(func_001F53A0(), 0x2F, 1);
        g->timer = 202;
        g->t = 1;
        g->code = code;
        g->c[2] = 0xE0;
        g->c[1] = 0xB0;
        g->c[0] = 0x70;
        g->c[3] = 0xFF;
        for (i = 0; i < 6; i++) {
            g->flag[i] = 30;
            g->start[i] = i * 25 + 30;
            g->fade[i] = i * 25 + 60;
        }
        for (i = 0; i < 6; i++) {
            g->pt[i].zero = 0;
            g->pt[i].c[2] = 0xE0;
            g->pt[i].c[1] = 0xB0;
            g->pt[i].c[0] = 0x70;
            g->pt[i].c[3] = 0xFF;
            g->pt[i].scale = 4.0f;
            g->pt[i].n = 0x24;
            g->pt[i].k = 0;
        }
        func_00103290(tx, 0);
        for (i = 0; i < 6; i++) {
            g->band[i].mode = 3;
            g->band[i].uv[0] = 0;
            g->band[i].uv[1] = 0;
            g->band[i].uv[2] = 0x40;
            g->band[i].uv[3] = 0x40;
            g->band[i].uv[4] = 0;
            g->band[i].uv[5] = 0;
            g->band[i].uv[6] = 0x80;
            g->band[i].uv[7] = 0x80;
            g->band[i].scale = 1.0f;
            g->band[i].c[2] = 0x80;
            g->band[i].c[1] = 0x80;
            g->band[i].c[0] = 0x80;
            g->band[i].c[3] = 0x80;
            g->band[i].s[0] = 0;
            g->band[i].s[1] = 2;
            g->band[i].s[2] = 3;
            g->band[i].s[3] = 4;
            g->band[i].s[4] = 0;
            g->band[i].s[5] = 999;
            t = tx[0];
            g->aux[i].z = 0.0f;
            g->aux[i].y = 0.0f;
            g->aux[i].x = 0.0f;
            g->aux[i].scale = 3.0f;
            g->aux[i].tex = t;
            g->aux[i].c[2] = 0x80;
            g->aux[i].c[1] = 0x80;
            g->aux[i].c[0] = 0x80;
            g->aux[i].c[3] = 0x80;
        }
        func_00103290(tx, 1);
        g->list[0] = g->buf[0];
        g->list[1] = g->buf[1];
        g->list[2] = g->buf[2];
        g->list[3] = g->buf[3];
        g->list[4] = g->buf[4];
        g->list[5] = g->buf[5];
        for (i = 0; i < 6; i++) {
            g->spot[i].tex = tx[0];
            g->spot[i].c[2] = 0x80;
            g->spot[i].c[1] = 0x80;
            g->spot[i].c[0] = 0x80;
            g->spot[i].c[3] = 0x80;
            g->spot[i].flags = 0x8003;
            g->spot[i].size = 20.0f;
            g->spot[i].uv[0] = 0x60;
            g->spot[i].uv[1] = 0;
            g->spot[i].uv[2] = 0x20;
            g->spot[i].uv[3] = 0x20;
            g->spot[i].uv[4] = 0x60;
            g->spot[i].uv[5] = 0;
            g->spot[i].uv[6] = 0x80;
            g->spot[i].uv[7] = 0x40;
            g->spot[i].rate = 0.05f;
            g->spot[i].a = 0;
            g->spot[i].b = 0x10;
            g->spot[i].c34 = 0x18;
            g->spot[i].d = 0;
            g->spot[i].e = 1;
        }
        g->grp[0].parts = g->parts[0];
        g->grp[1].parts = g->parts[1];
        g->grp[2].parts = g->parts[2];
        g->grp[3].parts = g->parts[3];
        g->grp[4].parts = g->parts[4];
        g->grp[5].parts = g->parts[5];
        for (i = 0; i < 6; i++) {
            g->grp[i].tex = tx[0];
            g->grp[i].flags = 0x20000003;
            g->grp[i].c[2] = 0x80;
            g->grp[i].c[1] = 0x80;
            g->grp[i].c[0] = 0x80;
            g->grp[i].c[3] = 0x80;
            g->grp[i].f20 = 0.3f;
            g->grp[i].f24 = 10.0f;
            g->grp[i].uv[0] = 0;
            g->grp[i].uv[1] = 0;
            g->grp[i].uv[2] = 0x20;
            g->grp[i].uv[3] = 0x20;
            g->grp[i].uv[4] = 0;
            g->grp[i].uv[5] = 0;
            g->grp[i].uv[6] = 0x80;
            g->grp[i].uv[7] = 0x40;
            g->grp[i].radius = 5.0f;
            g->grp[i].count = 0x80;
            g->grp[i].life = 8;
            g->grp[i].f2F = 0;
            Set_b244_01E02B40(&g->grp[i]);
        }
        return 0;
    }
    for (i = 0; i < 6; i++) {
        func_001F5F90(func_001F5380(), g->mb[i].m);
        b244_01E030A0(g, ot, i);
    }
    func_001038D0(g);
    for (i = 0; i < 6; i++) {
        func_001039A0(&g->ma[i]);
        func_001039A0(&g->mb[i]);
        func_001038D0(&g->mc[i]);
    }
    if (g->t >= 30 && g->t < 185) {
        func_01E00120_b244();
    }
    if (g->t >= 185) {
        func_01E00250_b244(ot, (Src_b000_01E00400 *)g->c);
        func_00103470(&g->c[3], 0, 0x10);
    }
    for (i = 0; i < 6; i++) {
        b244_01E031E0(g, ot, i);
        b244_01E03300(g, ot, i);
        b244_01E035B0(g, ot, i);
    }
    g->t++;
    g->timer--;
    if (g->t == 185) {
        return 2;
    }
    if (g->t == 50) {
        return 1;
    }
    if (g->t >= 60 && g->t < 185) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}


/* shape b244:01E030A0, 78 insns: move one of the scene's actors: before its start time it sits on the scene joint, after it it steps along its path (func_00104490 with a countdown) and runs shape b244:01E020C0; then copies its position and applies the camera (func_00103DB0) */

typedef struct {
    f32 x, y, z, w;
} V4_b244_01E030A0;

typedef struct {
    V4_b244_01E030A0 p;
    u8 pad10[0x60];
} Ent_b244_01E030A0;

typedef struct {
    u8 pad0[0x10];
    V4_b244_01E030A0 p;
    u8 pad20[0x50];
} Cam_b244_01E030A0;

typedef struct {
    u8 pad0[0x40];
} Path_b244_01E030A0;

typedef union {
    struct {
        u8 pad[0x70];
        Path_b244_01E030A0 path[6];
        s32 kind[6];
    } d;
    struct {
        u8 pad[0xB30];
        Ent_b244_01E030A0 a[6];
    } a;
    struct {
        u8 pad[0x1130];
        Ent_b244_01E030A0 b[5];
    } b;
    struct {
        u8 pad[0x13C0];
        Cam_b244_01E030A0 c[6];
    } c;
    struct {
        u8 pad[0x4770];
        s32 t[6];
        s32 start[6];
        u8 pad47A0[0x1C];
        s32 now;
        u8 pad47C0[4];
        s32 joint;
    } s;
} Scene_b244_01E030A0;

static void func_01E030A0_b244(Scene_b244_01E030A0 *g, s32 arg1, s32 i) {
    extern void b244_01E020C0(Path_b244_01E030A0 *, s32, Ent_b244_01E030A0 *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    V4_b244_01E030A0 m;

    if (g->s.now < g->s.start[i]) {
        func_001F5620(func_001F53A0(), g->s.joint, &g->a.a[i]);
    } else {
        func_00104490(&g->a.a[i], &g->b.b[i], g->s.t[i]);
        if (g->s.t[i] != 0) {
            g->s.t[i]--;
        }
        b244_01E020C0(&g->d.path[i], g->d.kind[i], &g->a.a[i]);
    }
    func_001F5F90(func_001F53A0(), &m);
    g->c.c[i].p = g->a.a[i].p;
    func_00103DB0(&m, &g->b.b[i], &g->c.c[i]);
}

/* shape b244:01E031E0, 70 insns: updates effect group i once the scene timer reaches its start - 1: builds its matrix
   from its point (b244:01E003B0) and its band (b244:01E00910); past its fade time shrinks the matrix and fades both
   alphas (16 and 8 a frame) */

typedef struct {
    u8 pad0[7];
    u8 a;
    u8 pad8[8];
} Pt_b244_01E031E0;

typedef struct {
    u8 pad0[0x37];
    u8 a;
    u8 pad38[0x28];
} Band_b244_01E031E0;

typedef struct {
    u8 pad0[0xB10];
    f32 m[6][0x1C];
    Pt_b244_01E031E0 pt[6];
    Band_b244_01E031E0 band[6];
    u8 aux[6][0x20];
    u8 pad1110[0x4788 - 0x1110];
    s32 start[6];
    s32 fade[6];
    u8 pad47B8[4];
    s32 t;
} Scene_b244_01E031E0;

static void func_01E031E0_b244(Scene_b244_01E031E0 *s, s32 arg1, s32 i) {
    extern void b244_01E003B0(s32, void *, f32 *);
    extern void b244_01E00910(s32, void *, void *, f32 *);
    extern void func_001033D0(f32 *, f32, f32);
    extern void func_00103470(u8 *, u8, s32);

    if (s->t >= s->start[i] - 1) {
        b244_01E003B0(arg1, &s->pt[i], s->m[i]);
        b244_01E00910(arg1, &s->band[i], s->aux[i], s->m[i]);
        if (s->t >= s->fade[i]) {
            f32 r = 5.0f;

            func_001033D0(s->m[i], r, 0.2f);
            func_00103470(&s->pt[i].a, 0, 0x10);
            func_00103470(&s->band[i].a, 0, 8);
        }
    }
}

/* shape b244:01E03300, 171 insns: one burst group's step: from its start time (ctx+0x4788 per group) to scene time 184 updates the group (b244:01E01360), clears its flags after ctx+0x47A0, scales every live point by 1.2 and re-throws those above 30 (height 4, a random 0..10*f28 tenths along a random angle, delay 0..11); then updates the second list (b244:01E021A0) and clears each of its entries' flags */

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 e;
} Pt_b244_01E03300;

typedef struct {
    u8 pad0[0xB];
    u8 c;
    Pt_b244_01E03300 *pts;
    u8 pad10[0x18];
    f32 f28;
    s16 n;
    u8 pad2E[2];
} Grp_b244_01E03300;

typedef struct {
    u8 pad0[0x3A];
    s16 n;
    u8 pad3C[4];
} Grp2_b244_01E03300;

typedef struct {
    u8 pad0[0xC];
    u8 c[4];
} Ent_b244_01E03300;

typedef struct {
    u8 pad0[0x70];
    Grp2_b244_01E03300 g2[6];
    Ent_b244_01E03300 *ents[6];
    u8 pad208[0x13B0 - 0x208];
    u8 x[6][0x70];
    Grp_b244_01E03300 grp[6];
    u8 pad1770[0x4788 - 0x1770];
    s32 start[6];
    s32 t2[6];
    u8 pad47B8[4];
    s32 time;
} Ctx_b244_01E03300;

static void func_01E03300_b244(Ctx_b244_01E03300 *g, s32 arg1, s32 k) {
    extern void b244_01E01360(s32, Grp_b244_01E03300 *, void *);
    extern void b244_01E021A0(s32, Grp2_b244_01E03300 *, Ent_b244_01E03300 *, Ctx_b244_01E03300 *);
    extern void func_00103470(void *, s32, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    s32 i;
    s32 r;
    s32 h;
    s32 a;
    f32 f;

    if (g->time >= g->start[k] && g->time < 185) {
        b244_01E01360(arg1, &g->grp[k], g->x[k]);
        i = 0;
        if (g->time > g->t2[k]) {
            func_00103470(&g->grp[k].c, 0, 8);
        }
        for (i = 0; i < g->grp[k].n; i++) {
            if (g->grp[k].pts[i].e >= 0) {
                g->grp[k].pts[i].x *= 1.2f;
                g->grp[k].pts[i].y *= 1.2f;
                g->grp[k].pts[i].z *= 1.2f;
                if (g->grp[k].pts[i].y > 30.0f) {
                    r = 10.0f * g->grp[k].f28;
                    a = func_0019A5C8() % 0x10000;
                    f = 0.1f * (func_0019A5C8() % r);
                    g->grp[k].pts[i].y = 4.0f;
                    g->grp[k].pts[i].z = f * func_0020B480(a);
                    g->grp[k].pts[i].x = f * func_0020B550(a);
                    g->grp[k].pts[i].e = -(func_0019A5C8() % 12);
                }
            }
        }
        b244_01E021A0(arg1, &g->g2[k], g->ents[k], g);
        for (i = 0; i < g->g2[k].n; i++) {
            func_00103470(g->ents[k][i].c, 0, 8);
        }
    }
}

/* shape b244:01E035B0, 45 insns: if slot idx's flag (s32 at 0x4770) is clear, reset its animation (0x70-byte rows at
   0xB10, 10.0 / 1.0) and clear its three byte tables (0x10 rows at 0xDB7, 0x60 rows at 0xE47, 0x40 rows at 0x77) */

typedef struct {
    u8 pad0[0x4770];
    s32 flag[1];
} Game_b244_01E035B0;

static void func_01E035B0_b244(Game_b244_01E035B0 *g, s32 arg1, s32 idx) {
    extern void func_001033D0(f32, f32, void *);
    extern void func_00103470(void *, s32, s32);
    f32 s;

    if (g->flag[idx] == 0) {
        func_001033D0(10.0f, s = 1.0f, (u8 *)g + idx * 0x70 + 0xB10);
        func_00103470((u8 *)g + idx * 0x10 + 0xDB7, 0, 0x10);
        func_00103470((u8 *)g + idx * 0x60 + 0xE47, 0, 8);
        func_00103470((u8 *)g + idx * 0x40 + 0x77, 0, 5);
    }
}
