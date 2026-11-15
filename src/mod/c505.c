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

static void func_01E00080_c505(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b021:01E00120, 81 insns, 7 copies: the four corner colours of a sprite packet from one colour, alpha
   faded by level (corners 0/2 by (5 - level) * 16, corners 1/3 by (4 - level) * 16, never below 0),
   q = 1.0f, fog bytes cleared. A variant of b000:01E00100. */

typedef struct {
    u8 b, g, r, a;
} Src_b021_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    u8 xyz[7];
    u8 fog;
} Vtx_b021_01E00120;

typedef struct {
    u8 tag[0x10];
    Vtx_b021_01E00120 v[4];
} Pk_b021_01E00120;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00120_c505(Pk_b021_01E00120 *p, Src_b021_01E00120 *s, s32 lvl) {
    p->v[0].r = s->r;
    p->v[0].g = s->g;
    p->v[0].b = s->b;
    if (s->a >= (5 - lvl) * 16) {
        p->v[0].a = s->a - (5 - lvl) * 16;
    } else {
        p->v[0].a = 0;
    }
    p->v[0].q = 1.0f;
    p->v[1].r = s->r;
    p->v[1].g = s->g;
    p->v[1].b = s->b;
    if (s->a >= (4 - lvl) * 16) {
        p->v[1].a = s->a - (4 - lvl) * 16;
    } else {
        p->v[1].a = 0;
    }
    p->v[1].q = 1.0f;
    p->v[2].r = s->r;
    p->v[2].g = s->g;
    p->v[2].b = s->b;
    if (s->a >= (5 - lvl) * 16) {
        p->v[2].a = s->a - (5 - lvl) * 16;
    } else {
        p->v[2].a = 0;
    }
    p->v[2].q = 1.0f;
    p->v[3].r = s->r;
    p->v[3].g = s->g;
    p->v[3].b = s->b;
    if (s->a >= (4 - lvl) * 16) {
        p->v[3].a = s->a - (4 - lvl) * 16;
    } else {
        p->v[3].a = 0;
    }
    p->v[3].q = 1.0f;
    p->v[0].fog = 0;
    p->v[1].fog = 0;
    p->v[2].fog = 0;
    p->v[3].fog = 0;
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

static s32 func_01E00270_c505(s32 arg0, Src_b000_01E00400 *c) {
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c505:01E003D0, 298 insns: draws the two quads of a 2-part strip (shape family of b001:01E03860): colour
   from the module's colour helper (shape b000:01E00100, static copy below), per-quad setup by func_00105830,
   corners p[1] or p[0], p[i + 2], p[i * 5], p[i + 3]; texture rect unless flag 0x18; far z under flag 0x13. */

typedef struct {
    u8 b, g, r, a;
} Src_c505_01E003D0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c505_01E003D0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c505_01E003D0 v[4];
    u8 tail[0x20];
} Pkt_c505_01E003D0;

typedef struct {
    s16 u, v, w, h;
    u8 pad8[0x2C];
    Src_c505_01E003D0 color;
    s32 flags;
} Def_c505_01E003D0;

typedef struct {
    void *texture;
    s32 flags;
    u8 pad8[0x18];
    Vec4f p[8];
} Obj_c505_01E003D0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c505_01E003D0;

static s32 func_01E003D0_c505(s32 ot, Def_c505_01E003D0 *d, Obj_c505_01E003D0 *o, Cam_c505_01E003D0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00105830(void *, void *, s32);
    f32 depth[4];
    Pkt_c505_01E003D0 pkt;
    s32 i;

    ((Pkt_c505_01E003D0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(d->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(d->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c505(&pkt, &d->color);
    for (i = 0; i < 2; i++) {
        func_00105830(&pkt, d, i);
        if (i == 0) {
            if (func_00205440(&o->p[1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
        } else {
            if (func_00205440(&o->p[0], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
        }
        if (func_00205440(&o->p[i + 2], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->p[i * 5], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->p[i + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(d->flags, 0x18) != 0) {
            func_00208700(&pkt, o->texture, 0);
        } else {
            if (func_00104520(d->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)d->u << 4) | ((u64)(d->u + d->w - 1) << 14) |
                                        ((u64)d->v << 24) | ((u64)(d->v + d->h - 1) << 34));
            }
            func_00208700(&pkt, o->texture, 1);
        }
        if (func_00104520(d->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, ot, 0);
        } else if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                   func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape c500:01E003D0, 149 insns: set up a 6-corner billboard: copy the module's corner template, store the id and
   half the size, then stretch x or y so the shape keeps the source's aspect (s16 w/h when flag 0 is set and flag
   0x1F is not, f32 w/h otherwise), and write corner = template * size/2 * stretch */

typedef struct {
    Vec4f v[6];
} Six_c500_01E003D0;

typedef struct {
    u8 pad0[4];
    s16 w;
    s16 h;
    f32 fw;
    f32 fh;
    u8 pad10[0x28];
    s32 flags;
} Src_c500_01E003D0;

typedef struct {
    s32 id;
    u8 pad4[4];
    f32 scale;
    u8 padC[4];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[4];
    Vec4f v[6];
} Bb_c500_01E003D0;

extern Six_c500_01E003D0 D_01E042E0_c505;

static s32 func_01E00880_c505(Src_c500_01E003D0 *o, Bb_c500_01E003D0 *out, s32 id, f32 size) {
    Six_c500_01E003D0 q;
    f32 sx;
    f32 sy;
    f32 half;
    s32 i;

    q = D_01E042E0_c505;
    out->f10 = out->f14 = out->f18 = 0;
    out->scale = size / 2.0f;
    out->id = id;
    if (func_00104520(o->flags, 0) != 0 && func_00104520(o->flags, 0x1F) == 0) {
        if (o->w > o->h >> 1) {
            sx = 1.0f;
            sy = o->w / (o->h / 2.0f);
        } else if (o->w < o->h >> 1) {
            sx = o->w / (o->h / 2.0f);
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    } else {
        half = o->fh / 2.0f;
        if (o->fw > half) {
            sy = o->fw / half;
            sx = 1.0f;
        } else if (o->fw < half) {
            sx = o->fw / half;
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    }
    for (i = 0; i < 6; i++) {
        out->v[i].x = sx * (out->scale * q.v[i].x);
        out->v[i].y = sy * (out->scale * q.v[i].y);
        out->v[i].z = out->scale * q.v[i].z;
    }
    return 0;
}

/* shape c500:01E00630, 465 insns: draws two textured quads of a 6-point strip (like b001:01E03860's ring):
   quad i uses points 2i, 4, 2i+1, 5 offset by the strip position, rotated by the object's angle when flag 0x1E
   is set; colour from the module helper c500:01E00080. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c500_01E00630;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c500_01E00630 v[4];
    u8 tail[0x20];
} Pkt_c500_01E00630;

typedef struct {
    s16 u, v, w, h;
    u8 pad8[0x2C];
    u8 color[4];
    s32 flags;
    u8 pad3C[4];
    s32 angle;
} Obj_c500_01E00630;

typedef struct {
    void *texture;
    s32 flags;
    u8 pad8[8];
    Vec4f pos;
    Vec4f pts[6];
} Strip_c500_01E00630;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c500_01E00630;

extern void c505_01E00080(void *, void *);

static s32 func_01E00AE0_c505(s32 ot, Obj_c500_01E00630 *o, Strip_c500_01E00630 *s, Cam_c500_01E00630 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_00104DC0(void *, void *);
    extern void func_0020C750(void *, void *, s32);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    Vec4f p;
    Vec4f rv;
    f32 m[16];
    Pkt_c500_01E00630 pkt;
    s32 i;

    ((Pkt_c500_01E00630 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    c505_01E00080(&pkt, o->color);
    for (i = 0; i < 2; i++) {
        if (func_00104520(o->flags, 0x1F) != 0) {
            func_00104540(&pkt, o, 5);
        } else {
            func_00104DC0(&pkt, o);
        }
        if (func_00104520(o->flags, 0x1E) != 0) {
            rv.x = rv.z = rv.w = 0.0f;
            rv.y = 1.0f;
            func_0020C750(m, &rv, o->angle % 0x10000);
            func_0020CDD0(&p, m, &s->pts[i * 2]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            func_0020CDD0(&p, m, &s->pts[4]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            func_0020CDD0(&p, m, &s->pts[i * 2 + 1]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            func_0020CDD0(&p, m, &s->pts[5]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        } else {
            p.x = s->pos.x + s->pts[i * 2].x;
            p.y = s->pos.y + s->pts[i * 2].y;
            p.z = s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            p.x = s->pos.x + s->pts[4].x;
            p.y = s->pos.y + s->pts[4].y;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            p.x = s->pos.x + s->pts[i * 2 + 1].x;
            p.y = s->pos.y + s->pts[i * 2 + 1].y;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            p.x = s->pos.x + s->pts[5].x;
            p.y = s->pos.y + s->pts[5].y;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        }
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00208700(&pkt, s->texture, 0);
        } else {
            if (func_00104520(o->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->u << 4) | ((u64)(o->u + o->w - 1) << 14) |
                                        ((u64)o->v << 24) | ((u64)(o->v + o->h - 1) << 34));
            }
            func_00208700(&pkt, s->texture, 1);
        }
        if (func_00104520(s->flags, 0x14) != 0 && func_00104520(s->flags, 0x15) != 0 &&
            func_00104520(s->flags, 0x16) != 0 && func_00104520(s->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        s->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b001:01E00A30, 740 insns, 55 copies: draws an emitter's particles as textured quads. Each point moves
   with the velocity (or func_001036A0), turns around the emitter centre while the angle catches up, and gets a
   square of the emitter size, aspect-scaled, either rotated (flag 0x1E) or axis-aligned.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E00A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E00A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E00A30 v[4];
    u8 tail[0x20];
} Pkt_b001_01E00A30;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E00A30;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt_b001_01E00A30;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E00A30 color;
    f32 size;
    f32 cx, cy;
    u8 pad18[8];
    s16 u, v, w, h;
    f32 fw, fh;
    Pt_b001_01E00A30 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
} Emit_b001_01E00A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E00A30;

static s32 func_01E01230_c505(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b001_01E00A30 p;
    Pkt_b001_01E00A30 pkt;
    s32 i;
    f32 dx;
    f32 dy;
    f32 da;
    f32 r;
    f32 kx;
    f32 ky;

    ((Pkt_b001_01E00A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c505((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
    for (i = 0; i < e->count; i++) {
        if (e->cur != e->angle) {
            if (func_00104520(e->flags, 0x1F) != 0) {
                da = e->angle - e->cur;
                dx = e->pts[i].x - e->cx;
                dy = e->pts[i].y - e->cy;
                if (func_00104520(e->flags, 7) != 0) {
                    func_001036A0(&e->pts[i].x, vel);
                    r = 0.017453292f * da;
                    e->pts[i].x = e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r));
                    e->pts[i].y = e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r));
                } else {
                    r = 0.017453292f * da;
                    e->pts[i].x = vel->x + (e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r)));
                    e->pts[i].y = vel->y + (e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r)));
                }
            } else if (func_00104520(e->flags, 7) != 0) {
                func_001036A0(&e->pts[i].x, vel);
            } else {
                e->pts[i].x += vel->x;
                e->pts[i].y += vel->y;
            }
            if (i == e->count - 1) {
                e->cur = e->angle;
            }
        } else if (func_00104520(e->flags, 7) != 0) {
            func_001036A0(&e->pts[i].x, vel);
        } else {
            e->pts[i].x += vel->x;
            e->pts[i].y += vel->y;
        }
        func_00105260(&pkt, e, i);
        if (func_00104520(e->flags, 0) != 0) {
            if (e->w > e->h) {
                kx = 1.0f;
                ky = (f32)e->h / (f32)e->w;
            } else if (e->w < e->h) {
                kx = (f32)e->w / (f32)e->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (e->fw > e->fh) {
                ky = e->fh / e->fw;
                kx = 1.0f;
            } else if (e->fw < e->fh) {
                kx = e->fh / e->fw;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
        if (func_00104520(e->flags, 0x1E) != 0) {
            r = 0.017453292f * ((e->angle + 135) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            r = 0.017453292f * ((e->angle + 45) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            r = 0.017453292f * ((e->angle + 225) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            r = 0.017453292f * ((e->angle + 315) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        } else {
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->u << 4) | ((u64)(e->u + e->w - 1) << 14) |
                                        ((u64)e->v << 24) | ((u64)(e->v + e->h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (e->pts[i].life >= 0 && func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
    }
    if (func_00104520(e->flags, 7) == 0) {
        e->cx += vel->x;
        e->cy += vel->y;
    }
    return 0;
}

/* shape b013:01E010C0, 376 insns, 42 copies: 60-point spark sprite draw (sibling of b001:01E03860).
   Calls the module colour helper at 0x1E00100 (shape b000:01E00100) as a plain extern: nothing is kept
   in a scratch register across that call, so it need not be static in this file. */

typedef struct {
    u8 b, g, r, a;
} Src_b013_01E010C0;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
} Uv_b013_01E010C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_b013_01E010C0 i;
        f32 f[2];
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b013_01E010C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b013_01E010C0 v[4];
    u8 tail[0x20];
} Pkt_b013_01E010C0;

typedef struct {
    f32 x, y, z, w;
} Vec_b013_01E010C0;

typedef struct {
    f32 x, y, z;
} Pt_b013_01E010C0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b013_01E010C0 color;
    f32 r;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Pt_b013_01E010C0 pts[60];
} Spark_b013_01E010C0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b013_01E010C0;

static s32 func_01E01DC0_c505(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
    extern void c505_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103620(void *, s32);
    extern void func_001036A0(void *, s32);
    f32 depth[4];
    Vec_b013_01E010C0 v;
    Pkt_b013_01E010C0 pkt;
    s32 i;

    ((Pkt_b013_01E010C0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    c505_01E00080(&pkt, &sp->color);
    if (func_00104520(sp->flags, 0) != 0) {
        ((Pkt_b013_01E010C0 *)(s32)&pkt)->count |= 0x800;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[0].st)->s = sp->uv.i.u << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[0].st)->t = sp->uv.i.v << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[1].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[1].st)->t = sp->uv.i.v << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[2].st)->s = sp->uv.i.u << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[2].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[3].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[3].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
    } else {
        pkt.v[0].st.f[0] = sp->uv.f.u;
        pkt.v[0].st.f[1] = sp->uv.f.v;
        pkt.v[1].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[1].st.f[1] = sp->uv.f.v;
        pkt.v[2].st.f[0] = sp->uv.f.u;
        pkt.v[2].st.f[1] = sp->uv.f.v + sp->uv.f.h;
        pkt.v[3].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[3].st.f[1] = sp->uv.f.v + sp->uv.f.h;
    }
    for (i = 0; i < 60; i++) {
        if (func_00104520(sp->flags, 0x1F) != 0) {
            func_00103620(&sp->pts[i], mode);
        } else {
            func_001036A0(&sp->pts[i], mode);
        }
        v.x = sp->pts[i].x - sp->r;
        v.y = sp->pts[i].y + sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            sp->flags |= 0x100000;
        }
        v.x = sp->pts[i].x + sp->r;
        v.y = sp->pts[i].y + sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            sp->flags |= 0x200000;
        }
        v.x = sp->pts[i].x - sp->r;
        v.y = sp->pts[i].y - sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            sp->flags |= 0x400000;
        }
        v.x = sp->pts[i].x + sp->r;
        v.y = sp->pts[i].y - sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            sp->flags |= 0x800000;
        }
        func_00208700(&pkt, sp->texture, 0);
        if (func_00104520(sp->flags, 0x14) != 0 && func_00104520(sp->flags, 0x15) != 0 &&
            func_00104520(sp->flags, 0x16) != 0 && func_00104520(sp->flags, 0x17) != 0) {
            if (func_00104520(sp->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        sp->flags &= 0xFF0FFFFF;
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

static s32 func_01E023A0_c505(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c505) and needs that helper
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

static s32 func_01E02660_c505(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c505(&pkt, &ring->color);
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

/* shape b021:01E03DE0, 84 insns: sets up a vertical chain of 6 points: point 0 at height len, the next five
   step down by len / 5 with a random sideways jitter (+-15, the last one +-5). */

typedef struct {
    f32 x, y, z, w;
} Pt_b021_01E03DE0;

typedef struct {
    s32 owner;
    u8 pad4[0x1C];
    Pt_b021_01E03DE0 pts[6];
} Obj_b021_01E03DE0;

static s32 func_01E02B50_c505(Obj_b021_01E03DE0 *o, s32 owner, f32 len) {
    s32 i;
    f32 step;

    step = len / 5.0f;
    o->owner = owner;
    o->pts[0].x = o->pts[0].z = 0;
    o->pts[0].y = len;
    for (i = 0; i < 5; i++) {
        if (i == 4) {
            o->pts[i + 1].x = func_0019A5C8() % 10 - 5;
            o->pts[i + 1].z = func_0019A5C8() % 10 - 5;
        } else {
            o->pts[i + 1].x = func_0019A5C8() % 30 - 15;
            o->pts[i + 1].z = func_0019A5C8() % 30 - 15;
        }
        o->pts[i + 1].y = len - step * (i + 1);
    }
    return 0;
}

/* OVL_WARM */

/* shape b021:01E03F30, 251 insns, 5 copies: draws a short trail (up to 5 segments, fewer as it ages): each segment
   between two of its points is a quad, the second edge shifted right by the trail's width; colour and alpha
   per segment from the module helper (shape b021:01E00120); drawn only when all four corners project. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b021_01E03F30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b021_01E03F30 xyz;
} Vtx_b021_01E03F30;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b021_01E03F30 v[4];
    u8 tail[0x20];
} Pkt_b021_01E03F30;

typedef struct {
    s16 u, v, w, h;
} Rect_b021_01E03F30;

typedef struct {
    void *texture;
    Src_b021_01E00120 color;
    u8 pad08[4];
    s16 n;
    u8 pad0E[2];
    Rect_b021_01E03F30 rect;
    u8 pad18[8];
    Vec4f pos;
    Vec4f pts[5];
} Trail_b021_01E03F30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b021_01E03F30;

static s32 func_01E02CA0_c505(s32 ot __attribute__((aligned(8))), Trail_b021_01E03F30 *o, Cam_b021_01E03F30 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    f32 depth[4];
    Pkt_b021_01E03F30 pkt;
    s32 vis;
    s32 i;

    ((Pkt_b021_01E03F30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b021_01E03F30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b021_01E03F30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b021_01E03F30 *)(s32)&pkt)->pad = 0;
    vis = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 5 - o->n; i++) {
        func_01E00120_c505((Pk_b021_01E00120 *)&pkt, &o->color, i);
        func_00104540(&pkt, &o->rect, 1);
        if (i == 0) {
            if (func_00205440(&o->pos, cam->view, &pkt.v[0].xyz, &depth[0]) != 0) {
                vis |= 0x100000;
            }
            if (func_00205440(&o->pts[i], cam->view, &pkt.v[1].xyz, &depth[1]) != 0) {
                vis |= 0x200000;
            }
            o->pos.x += o->pos.w;
            o->pts[i].x += o->pos.w;
            if (func_00205440(&o->pos, cam->view, &pkt.v[2].xyz, &depth[2]) != 0) {
                vis |= 0x400000;
            }
            if (func_00205440(&o->pts[i], cam->view, &pkt.v[3].xyz, &depth[3]) != 0) {
                vis |= 0x800000;
            }
            o->pos.x -= o->pos.w;
            o->pts[i].x -= o->pos.w;
        } else {
            if (func_00205440(&o->pts[i - 1], cam->view, &pkt.v[0].xyz, &depth[0]) != 0) {
                vis |= 0x100000;
            }
            if (func_00205440(&o->pts[i], cam->view, &pkt.v[1].xyz, &depth[1]) != 0) {
                vis |= 0x200000;
            }
            o->pts[i - 1].x += o->pos.w;
            o->pts[i].x += o->pos.w;
            if (func_00205440(&o->pts[i - 1], cam->view, &pkt.v[2].xyz, &depth[2]) != 0) {
                vis |= 0x400000;
            }
            if (func_00205440(&o->pts[i], cam->view, &pkt.v[3].xyz, &depth[3]) != 0) {
                vis |= 0x800000;
            }
            o->pts[i - 1].x -= o->pos.w;
            o->pts[i].x -= o->pos.w;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                                ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
        func_00208700(&pkt, o->texture, 1);
        if (func_00104520(vis, 0x14) != 0 && func_00104520(vis, 0x15) != 0 && func_00104520(vis, 0x16) != 0 &&
            func_00104520(vis, 0x17) != 0) {
            func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
        vis &= 0xFF0FFFFF;
    }
    return 0;
}

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c505:01E03090, 322 insns: draws a 3-quad strip with fixed texture rows (0/0x500/0xA00 to 0x4F0/0x9F0/0xEF0),
   columns 0x60..0xAF shifted by 0x50 on even d->f48; corners from the object's points; colour from the module's
   colour helper (shape b000:01E00100, static copy below). */

typedef struct {
    u8 b, g, r, a;
} Src_c505_01E03090;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c505_01E03090;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c505_01E03090 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c505_01E03090;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c505_01E03090 v[4];
    u8 tail[0x20];
} Pkt_c505_01E03090;

typedef struct {
    u8 pad0[0x34];
    Src_c505_01E03090 color;
    u8 pad38[0x10];
    s16 f48;
} Def_c505_01E03090;

typedef struct {
    void *texture;
    u8 pad4[0xC];
    Vec4f q;
    Vec4f p[8];
} Obj_c505_01E03090;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c505_01E03090;

static s32 func_01E03090_c505(s32 ot __attribute__((aligned(8))), Def_c505_01E03090 *d __attribute__((aligned(16))), Obj_c505_01E03090 *o, Cam_c505_01E03090 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Pkt_c505_01E03090 pkt;
    s32 i;
    s32 off;

    ((Pkt_c505_01E03090 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c505_01E03090 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c505_01E03090 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c505_01E03090 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00080_c505(&pkt, &d->color);
    for (i = 0; i < 3; i++) {
        off = (d->f48 % 2 == 0) ? 0x50 : 0;
        ((Pkt_c505_01E03090 *)(s32)&pkt)->count |= 0x800;
        if (i == 0) {
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->v = 0;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->v = 0;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->v = 0x4F0;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->v = 0x4F0;
        } else if (i == 1) {
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->v = 0x500;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->v = 0x500;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->v = 0x9F0;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->v = 0x9F0;
        } else {
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[0].uv)->v = 0xA00;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[1].uv)->v = 0xA00;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->u = (off + 0x60) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[2].uv)->v = 0xEF0;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->u = (off + 0xAF) << 4;
            ((Uv_c505_01E03090 *)(s32)&pkt.v[3].uv)->v = 0xEF0;
        }
        func_00205440(&o->p[i], cam->view, &pkt.v[0].uv + 1, &depth[0]);
        if (i == 0) {
            func_00205440(&o->q, cam->view, &pkt.v[1].uv + 1, &depth[1]);
        } else {
            func_00205440(&o->p[i + 1], cam->view, &pkt.v[1].uv + 1, &depth[1]);
        }
        if (i == 0) {
            func_00205440(&o->p[7], cam->view, &pkt.v[2].uv + 1, &depth[2]);
        } else if (i == 1) {
            func_00205440(&o->p[0], cam->view, &pkt.v[2].uv + 1, &depth[2]);
        } else {
            func_00205440(&o->q, cam->view, &pkt.v[2].uv + 1, &depth[2]);
        }
        if (i == 0) {
            func_00205440(&o->p[6], cam->view, &pkt.v[3].uv + 1, &depth[3]);
        } else if (i == 1) {
            func_00205440(&o->q, cam->view, &pkt.v[3].uv + 1, &depth[3]);
        } else {
            func_00205440(&o->p[4], cam->view, &pkt.v[3].uv + 1, &depth[3]);
        }
        func_00208700(&pkt, o->texture, 0);
        func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
    }
    return 0;
}

/* shape c505:01E035A0 (c505), 799 insns, 1 copy: c505's scene manager: code >= 0 clears the 0x1140 scene (count 5,
   timer 30), sets up three lightning trails with dual boards riding them, an 8-point remain outline, a 6-point board,
   a ring, a 60-spark cloud and an 8-sprite board; each tick shakes camera 3 along x or z by its heading, draws the
   trails and boards, and once the count is out the outline, board, growing ring, sparks and fades, flashing the
   screen on even counts; 2 at tick 6, 8 when the timer runs out */

typedef struct {
    u8 b, g, r, a;
} Col_c505_01E035A0;

typedef struct {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c505_01E035A0;

typedef struct {
    s32 texture;
    Col_c505_01E035A0 color;
    u8 pad8[4];
    s16 n;
    u8 padE[2];
    s16 u, v, w, h;
    s16 x18;
    s16 x1A;
    u8 pad1C[4];
    Vec4f pos;
    Vec4f pts[5];
} Trail_c505_01E035A0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c505_01E035A0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c505_01E035A0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x60];
} Bb_c505_01E035A0;

typedef struct {
    Vec4f v[6];
} Tbl6_c505_01E035A0;

typedef struct {
    Vec4f v[8];
} Tbl8_c505_01E035A0;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 padC[4];
    s32 a, b, c;
    u8 pad1C[4];
    Vec4f p[6];
} Pts_c505_01E035A0;

typedef struct {
    s32 tex;
    u8 pad4[8];
    f32 scale;
    f32 x, y, z;
    u8 pad1C[4];
    Vec4f p[8];
} Obj_c505_01E035A0;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Dot_c505_01E035A0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c505_01E035A0 color;
    f32 size;
    f32 cx, cy, cz, cw;
    s16 u, v, w, h;
    s16 s28, s2A, s2C, s2E;
    Dot_c505_01E035A0 pts[16];
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
} Emit_c505_01E035A0;

typedef struct {
    f32 x, y, z;
} V3_c505_01E035A0;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c505_01E035A0 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    V3_c505_01E035A0 p[60];
} Spark_c505_01E035A0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c505_01E035A0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c505_01E035A0;

typedef struct {
    Crd_c505_01E035A0 crd[5];
    Trail_c505_01E035A0 trail[3];
    Mdl_c505_01E035A0 mdl[3];
    Bb_c505_01E035A0 bb[3];
    Mdl_c505_01E035A0 def;
    Pts_c505_01E035A0 pts;
    Emit_c505_01E035A0 emit;
    u8 pad880[0xA0];
    Mdl_c505_01E035A0 def2;
    Obj_c505_01E035A0 obj2;
    Spark_c505_01E035A0 spark;
    Ring_c505_01E035A0 ring;
    f32 sc[4];
    s32 cnt;
    s32 timer;
    s32 t;
    s32 code;
    s32 flags;
    Src_b000_01E00400 color;
    s32 a;
    s32 b;
} Scene_c505_01E035A0;

static s32 func_01E035A0_c505(s32 arg0, s32 code) {
    Scene_c505_01E035A0 *g = (Scene_c505_01E035A0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_001F5380(void);
    extern void func_001E10F0(s32, s32, s32, void *);
    extern void func_00103260(s32 *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00105C40(void *);
    extern s32 func_0019A5C8();
    extern Tbl8_c505_01E035A0 D_01E04340_c505;
    extern Tbl6_c505_01E035A0 D_01E04280_c505;
    s32 m;
    s32 u;
    s32 ot;
    Vec4f v;
    s32 tx[4];
    Tbl8_c505_01E035A0 tbl8;
    Tbl6_c505_01E035A0 tbl6;
    s32 i;
    s32 k;
    s32 n;
    s32 t;
    s32 ang;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1140);
        g->flags = 0;
        g->cnt = 5;
        g->timer = 0x1E;
        g->t = 0;
        g->code = code;
        g->a = func_001F5380() & 0xFF;
        g->b = func_001F5380() >> 8;
        g->sc[0] = 1.02f;
        g->sc[1] = 1.02f;
        g->sc[2] = 1.02f;
        g->color.r = g->color.g = g->color.b = g->color.a = 0x80;
        func_00103890(&g->crd[0]);
        func_00103890(&g->crd[1]);
        func_00103890(&g->crd[2]);
        func_00103890(&g->crd[3]);
        func_00103890(&g->crd[4]);
        g->crd[1].scale.x = g->crd[1].scale.y = g->crd[1].scale.z = 0.1f;
        func_001E10F0(g->a, g->b, 0, &g->crd[0].pos);
        func_001E10F0(g->a, g->b, 0, &g->crd[1].pos);
        func_001E10F0(g->a, g->b, 0, &g->crd[2].pos);
        func_001E10F0(g->a, g->b, 0, &g->crd[3].pos);
        func_001E10F0(g->a, g->b, 0, &g->crd[4].pos);
        func_00103260(tx, 0xE);
        for (i = 0; i < 3; i++) {
            g->trail[i].n = 5;
            g->trail[i].u = 0;
            g->trail[i].v = 0x80;
            g->trail[i].w = 0x20;
            g->trail[i].h = 0x80;
            g->trail[i].x18 = 0;
            g->trail[i].x1A = 0x80;
            g->trail[i].pos.w = 10.0f;
            g->trail[i].color.r = 0x80;
            g->trail[i].color.g = 0x80;
            g->trail[i].color.b = 0x80;
            g->trail[i].color.a = 0x80;
            func_01E02B50_c505((Obj_b021_01E03DE0 *)&g->trail[i], tx[0], 200.0f);
        }
        g->def2.color.r = 0x80;
        g->def2.color.g = 0x80;
        g->def2.color.b = 0x80;
        g->def2.color.a = 0x80;
        g->def2.f30 = 1.0f;
        g->def2.flags = 3;
        g->def2.r[0] = 0x60;
        g->def2.r[1] = 0;
        g->def2.r[2] = 0x50;
        g->def2.r[3] = 0x50;
        g->def2.r[4] = 0x60;
        g->def2.r[5] = 0;
        g->def2.r[6] = 0x100;
        g->def2.r[7] = 0x100;
        g->def2.h48 = 0;
        g->def2.h4A = 1;
        g->def2.h4E = 2;
        g->def2.h52 = 0;
        g->def2.h50 = 0;
        g->def2.h4C = g->def2.h4E - 1;
        t = tx[0];
        tbl8 = D_01E04340_c505;
        g->obj2.x = g->obj2.y = g->obj2.z = 0.0f;
        g->obj2.scale = 30.0f;
        g->obj2.tex = t;
        for (k = 0; k < 8; k++) {
            g->obj2.p[k].x = g->obj2.scale * tbl8.v[k].x;
            g->obj2.p[k].y = g->obj2.scale * tbl8.v[k].y;
            g->obj2.p[k].z = g->obj2.scale * tbl8.v[k].z;
        }
        func_00103260(tx, 3);
        for (i = 0; i < 3; i++) {
            g->mdl[i].flags = 1;
            g->mdl[i].f30 = 1.0f;
            g->mdl[i].color.r = 0x80;
            g->mdl[i].color.g = 0x80;
            g->mdl[i].color.b = 0x80;
            g->mdl[i].color.a = 0x80;
            g->mdl[i].r[0] = 0x40;
            g->mdl[i].r[1] = 0;
            g->mdl[i].r[2] = 0x20;
            g->mdl[i].r[3] = 0x40;
            g->mdl[i].r[4] = 0x40;
            g->mdl[i].r[5] = 0;
            g->mdl[i].r[6] = 0x80;
            g->mdl[i].r[7] = 0x40;
            g->mdl[i].h48 = 0;
            g->mdl[i].h4A = 1;
            g->mdl[i].h4E = 2;
            g->mdl[i].h52 = 999;
            g->mdl[i].h50 = 0;
            g->mdl[i].h4C = g->mdl[i].h4E - 1;
            func_01E00880_c505((Src_c500_01E003D0 *)&g->mdl[i], (Bb_c500_01E003D0 *)&g->bb[i], tx[0], 25.0f);
        }
        func_00103260(tx, 0xF);
        g->def.flags = 3;
        g->def.f30 = 1.0f;
        g->def.color.r = 0x80;
        g->def.color.g = 0x70;
        g->def.color.b = 0x40;
        g->def.color.a = 0x80;
        g->def.r[0] = 0xB0;
        g->def.r[1] = 0x40;
        g->def.r[2] = 0x20;
        g->def.r[3] = 0x20;
        g->def.r[4] = 0xB0;
        g->def.r[5] = 0x40;
        g->def.r[6] = 0x100;
        g->def.r[7] = 0x100;
        g->def.h48 = 0;
        g->def.h4A = 1;
        g->def.h4E = 2;
        g->def.h52 = 0;
        g->def.h50 = 0;
        g->def.h4C = g->def.h4E - 1;
        u = tx[0];
        tbl6 = D_01E04280_c505;
        g->pts.a = g->pts.b = g->pts.c = 0;
        g->pts.scale = 15.0f;
        g->pts.tex = u;
        for (m = 0; m < 6; m++) {
            g->pts.p[m].x = g->pts.scale * tbl6.v[m].x;
            g->pts.p[m].y = g->pts.scale * tbl6.v[m].y;
            g->pts.p[m].z = g->pts.scale * tbl6.v[m].z;
        }
        g->ring.flags = 0x8000;
        g->ring.u = 0x8E;
        g->ring.v = 0;
        g->ring.w = 0x20;
        g->ring.h = 0x40;
        g->ring.color.r = 0x80;
        g->ring.color.g = 0x70;
        g->ring.color.b = 0x40;
        g->ring.color.a = 0x80;
        {
            f32 z = 0.0f;
            func_01E023A0_c505((Ring_b001_01E035A0 *)&g->ring, tx[0], 8.0f, 24.0f, z, 30.0f);
        }
        g->spark.tex = tx[0];
        g->spark.size = 1.5f;
        for (n = 0; n < 60; n++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.p[n].x = func_0019A5C8() % 100 - 50;
                g->spark.p[n].z = func_0019A5C8() % 50;
                g->spark.p[n].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.p[n].x = func_0019A5C8() % 50 - 25;
                g->spark.p[n].y = func_0019A5C8() % 25;
                g->spark.p[n].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 1;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x70;
        g->spark.color.b = 0x40;
        g->spark.color.a = 0x80;
        g->emit.texture = tx[0];
        g->emit.flags = 7;
        g->emit.cx = 0.0f;
        g->emit.cy = 0.0f;
        g->emit.cz = 0.0f;
        g->emit.u = 0x80;
        g->emit.v = 0xC0;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.s28 = 0x80;
        g->emit.s2A = 0xC0;
        g->emit.s2C = 0x80;
        g->emit.s2E = 0x100;
        g->emit.size = 20.0f;
        g->emit.count = 8;
        g->emit.step = 1;
        g->emit.s13C = 1;
        g->emit.s140 = 8;
        g->emit.s136 = 0x1E;
        g->emit.s138 = -0x1E;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x70;
        g->emit.color.b = 0x40;
        g->emit.color.a = 0x80;
        for (i = 0; i < 8; i++) {
            g->emit.pts[i].x = (f32)(func_0019A5C8() % 60 - 30);
            g->emit.pts[i].y = (f32)(func_0019A5C8() % 30);
            g->emit.pts[i].life = -g->emit.step * i;
            g->emit.pts[i].pad = func_00105C40(&g->emit.u);
            g->emit.s13E = g->emit.pts[i].pad + g->emit.s140 - 1;
        }
        return 0;
    }
    func_001039A0(&g->crd[0]);
    func_001039A0(&g->crd[1]);
    func_001038D0(&g->crd[2]);
    func_001039A0(&g->crd[4]);
    ang = func_001039A0(&g->crd[3]);
    g->crd[4].pos.y = 3.0f;
    if (g->def.h50 > 0) {
        g->crd[4].scale.x = g->crd[4].scale.y = 1.5f;
    }
    func_001E10F0(g->a, g->b, 0, &g->crd[3].pos);
    if (g->cnt == 0) {
        ang = ang % 0x10000;
        if ((ang >= 0x2000 && ang < 0x6000) || (ang >= 0xA000 && ang < 0xE000)) {
            if (g->timer % 2 == 0) {
                g->crd[3].pos.x += 0.5f;
            } else if (g->timer % 2 == 1) {
                g->crd[3].pos.x -= 0.5f;
            }
        } else {
            if (g->timer % 2 == 0) {
                g->crd[3].pos.z += 0.5f;
            } else if (g->timer % 2 == 1) {
                g->crd[3].pos.z -= 0.5f;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (g->trail[i].color.a < 0x60) {
            g->trail[i].u = g->trail[i].x18 + g->trail[i].w;
        } else if (g->trail[i].color.a < 0x40) {
            g->trail[i].u = g->trail[i].x18 + g->trail[i].w * 2;
        }
        func_01E02CA0_c505(ot, (Trail_b021_01E03F30 *)&g->trail[i], (Cam_b021_01E03F30 *)&g->crd[3]);
        if (g->trail[i].n != 0) {
            g->bb[i].pos.x = 5.0f + g->trail[i].pts[4 - g->trail[i].n].x;
            g->bb[i].pos.y = g->trail[i].pts[4 - g->trail[i].n].y;
            func_01E00AE0_c505(ot, (Obj_c500_01E00630 *)&g->mdl[i], (Strip_c500_01E00630 *)&g->bb[i],
                               (Cam_c500_01E00630 *)&g->crd[3]);
        }
        if (g->trail[i].n != 0) {
            g->trail[i].n--;
        }
    }
    if (g->cnt == 0) {
        if (g->def2.h52 == 0 || g->def2.h52 == 999) {
            func_01E03090_c505(ot, (Def_c505_01E03090 *)&g->def2, (Obj_c505_01E03090 *)&g->obj2,
                               (Cam_c505_01E03090 *)&g->crd[4]);
        }
        g->def2.h48++;
        func_00103470(&g->def2.color.a, 0, 0x20);
        if (g->def.h52 == 0 || g->def.h52 == 999) {
            func_01E003D0_c505(ot, (Def_c505_01E003D0 *)&g->def, (Obj_c505_01E003D0 *)&g->pts,
                               (Cam_c505_01E003D0 *)&g->crd[4]);
        }
        func_01E02660_c505(ot, (Ring_b001_01E03860 *)&g->ring, (Cam_b001_01E03860 *)&g->crd[2]);
        func_00103470(&g->ring.color.a, 0, 0x20);
        g->crd[2].scale.x = g->crd[2].scale.y = g->crd[2].scale.z += 0.2f;
        if (g->crd[1].scale.x < 1.0f) {
            g->crd[1].scale.x = g->crd[1].scale.y = g->crd[1].scale.z += 0.2f;
        }
        func_01E01DC0_c505(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)&g->crd[1], (s32)g->sc);
        func_00103470(&g->spark.color.a, 0, 8);
        for (i = 0; i < 3; i++) {
            func_00103470(&g->trail[i].color.a, 0, 0x10);
        }
        v.x = v.y = v.z = 0.0f;
        func_01E01230_c505(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->emit, (Vec_b001_01E00A30 *)&v);
        func_00103470(&g->emit.color.a, 0, 8);
    }
    if (g->cnt % 2 == 0 && g->flags != 0x80020400) {
        func_01E00270_c505(ot, &g->color);
    }
    if (g->cnt == 0 && g->flags != 0x80020400) {
        g->flags = 0x80020400;
    }
    if (g->cnt != 0) {
        g->cnt--;
    }
    g->t++;
    g->timer--;
    if (g->t == 6) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
