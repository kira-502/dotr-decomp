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

static void func_01E00080_b021(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static void func_01E00120_b021(Pk_b021_01E00120 *p, Src_b021_01E00120 *s, s32 lvl) {
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

static s32 func_01E00270_b021(s32 arg0, Src_b000_01E00400 *c) {
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

static s32 func_01E003D0_b021(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
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
    func_01E00080_b021((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
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

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b013:01E001A0, 205 insns, 40 copies: set up an 8-point effect outline (scale, aspect from the model's
   texture or size, one of two local point tables or random points) */

typedef struct Model_b013_01E001A0 {
    u8 pad0[4];
    s16 w;
    s16 h;
    f32 fw;
    f32 fh;
    u8 pad10[0x28];
    s32 tex;
} Model_b013_01E001A0;

typedef struct Fx_b013_01E001A0 {
    s32 kind;
    u8 pad4[4];
    s32 type;
    f32 scale;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    Vec4f v[8];
} Fx_b013_01E001A0;

#pragma optimization_level 3
typedef struct W_ta_func_01E00C60_b021 {
    Vec4f v[8];
} W_ta_func_01E00C60_b021;

typedef struct W_tb_func_01E00C60_b021 {
    Vec4f v[8];
} W_tb_func_01E00C60_b021;

static s32 func_01E00C60_b021(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
    f32 sx;
    f32 sy;
    s32 i;

    o->f18 = 0.0f;
    o->f14 = 0.0f;
    o->f10 = 0.0f;
    o->scale = scale / 2.0f;
    o->kind = kind;
    if (func_00104520(m->tex, 0) != 0) {
        if (m->w > m->h) {
            sx = 1.0f;
            sy = (f32)m->h / (f32)m->w;
        } else if (m->w < m->h) {
            sx = (f32)m->h / (f32)m->w;
            sy = 1.0f;
        } else {
            sx = sy = 1.0f;
        }
    } else {
        if (!(m->fw <= m->fh)) {
            sy = m->fh / m->fw;
            sx = 1.0f;
        } else if (m->fw < m->fh) {
            sx = m->fh / m->fw;
            sy = 1.0f;
        } else {
            sx = sy = 1.0f;
        }
    }
    if (o->type != 3) {
        if (o->type == 5 || o->type == 6) {
            extern W_ta_func_01E00C60_b021 D_01E05F00_b021;
            W_ta_func_01E00C60_b021 ta_w = D_01E05F00_b021;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00C60_b021 D_01E05F80_b021;
            W_tb_func_01E00C60_b021 tb_w = D_01E05F80_b021;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * tb_w.v[i].x);
                o->v[i].y = sy * (o->scale * tb_w.v[i].y);
                o->v[i].z = o->scale * tb_w.v[i].z;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            o->v[i].x = func_0019A5C8() % 30 - 15;
            o->v[i].y = o->scale;
            o->v[i].z = func_0019A5C8() % 30 - 15;
        }
    }
    return 0;
}
#pragma optimization_level reset

/* func_00205440 is called unprototyped here */

/* shape b013:01E004E0, 757 insns, 40 copies: project the 8-point effect outline set up by b013:01E001A0 as
   quads (8 small squares for type 3, else 4 quads round the centre), flag what landed on screen and draw */

typedef struct Model_b013_01E004E0 {
    s16 x, y, w, h;
    u8 pad8[0x2C];
    Src_b000_01E00100 col;
    s32 tex;
} Model_b013_01E004E0;

typedef struct Fx_b013_01E004E0 {
    s32 kind;
    s32 flags;
    s32 type;
    f32 scale;
    Vec4f c;
    Vec4f v[8];
} Fx_b013_01E004E0;

typedef struct Cam_b013_01E004E0 {
    u8 pad0[0x30];
    u8 view[0x10];
} Cam_b013_01E004E0;

typedef struct Xyz_b013_01E004E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b013_01E004E0;

typedef struct Vtx_b013_01E004E0 {
    u8 rgbaq[8];
    u64 st;
    Xyz_b013_01E004E0 xyz;
} Vtx_b013_01E004E0;

typedef struct Pk_b013_01E004E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b013_01E004E0 v[4];
    u8 pad70[0x20];
} Pk_b013_01E004E0;

static inline void b013_01E004E0_tag(Pk_b013_01E004E0 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00FA0_b021(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
    extern s32 func_00205440();
    s32 i;
    f32 z[4];
    Vec4f pos;
    Pk_b013_01E004E0 pk;

    b013_01E004E0_tag((Pk_b013_01E004E0 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
    if (func_00104520(m->tex, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(m->tex, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b021((Vtx_b000_01E00100 *)&pk, &m->col);
    func_00104DC0(&pk, m);
    if (o->type == 3) {
        for (i = 0; i < 8; i++) {
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y + o->scale;
            pos.z = o->v[i].z;
            if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                o->flags |= 0x100000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y + o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                o->flags |= 0x200000;
            }
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                o->flags |= 0x400000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                o->flags |= 0x800000;
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
                o->flags &= 0xFF0FFFFF;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (o->type == 1 || o->type == 5) {
                pos.x = o->c.x + o->v[i + i + 1].x;
                pos.y = o->c.y + o->v[i + i + 1].y;
                pos.z = o->c.z + o->v[i + i + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i < 2) {
                    pos.x = o->c.x + o->v[2].x;
                    pos.y = o->c.y + o->v[2].y;
                    pos.z = o->c.z + o->v[2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[6].x;
                    pos.y = o->c.y + o->v[6].y;
                    pos.z = o->c.z + o->v[6].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                if (i == 1 || i == 2) {
                    pos.x = o->c.x + o->v[4].x;
                    pos.y = o->c.y + o->v[4].y;
                    pos.z = o->c.z + o->v[4].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            } else if (o->type == 2 || o->type == 6) {
                pos.x = o->c.x + o->v[i * 2 + 1].x;
                pos.y = o->c.y + o->v[i * 2 + 1].y;
                pos.z = o->c.z + o->v[i * 2 + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i != 3) {
                    pos.x = o->c.x + o->v[i * 2 + 2].x;
                    pos.y = o->c.y + o->v[i * 2 + 2].y;
                    pos.z = o->c.z + o->v[i * 2 + 2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&o->v[0], cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                pos.x = o->c.x + o->v[i * 2].x;
                pos.y = o->c.y + o->v[i * 2].y;
                pos.z = o->c.z + o->v[i * 2].z;
                if (func_00205440(&o->v[i * 2], cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                    o->flags |= 0x400000;
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
            }
            o->flags &= 0xFF0FFFFF;
        }
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

static s32 func_01E01B80_b021(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_b021((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

extern void b021_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E02710_b021(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    b021_01E00080(&pkt, &sp->color);
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

static s32 func_01E02CF0_b021(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E06000_b021;
    Tbl_b000_01E032C0 tbl = D_01E06000_b021;
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

static s32 func_01E02E50_b021(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_b021((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* OVL_WARM */

/* shape b021:01E03460, 608 insns, 12 copies: draws a lightning bolt between two points: the line is cut into n pieces
   (at most 16), each inner point shaken by a random jitter, all projected; then each piece is one textured
   quad (random texture corner) as wide as its screen length / 3 (or a fixed width), drawn only when both ends
   are visible and the piece is not past the moving head. Calls the module's colour helper (shape b000:01E00100).
   The spilled ot parameter is aligned(8): that puts its home at 0xB8 like the original (plain s32 gives 0xBC). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b021_01E03460;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b021_01E03460 xyz;
} Vtx_b021_01E03460;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b021_01E03460 v[4];
    u8 tail[0x20];
} Pkt_b021_01E03460;

typedef struct {
    s16 u, v, w, h;
} Rect_b021_01E03460;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    s16 n;
    s16 jitter;
    Rect_b021_01E03460 rect;
    u8 pad18[0x10];
    s16 head;
    u8 pad2A[2];
    f32 width;
} Bolt_b021_01E03460;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b021_01E03460;

static s32 func_01E03460_b021(s32 ot __attribute__((aligned(8))), Bolt_b021_01E03460 *b, Cam_b021_01E03460 *cam, Vec4f *p1, Vec4f *p2) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b021_01E03460 s[17];
    Vec4f mid;
    f32 depth[17];
    Pkt_b021_01E03460 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w;
    f32 len;
    s32 vis;
    s32 k;
    s32 r;

    vis = 0;
    if (b->n > 16) {
        b->n = 16;
    }
    ((Pkt_b021_01E03460 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00080_b021((Vtx_b000_01E00100 *)&pkt, &b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    if (func_00205440(p1, cam->view, &s[0], &depth[0]) != 0) {
        if (func_00101600(&s[0]) != 0) {
            vis |= 1;
        }
    }
    for (k = 1; k < b->n; k++) {
        t = (f32)k / b->n;
        if (b->jitter != 0) {
            mid.x = p1->x + dx * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.y = p1->y + dy * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.z = p1->z + dz * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
        } else {
            mid.x = p1->x + dx * t;
            mid.y = p1->y + dy * t;
            mid.z = p1->z + dz * t;
        }
        if (func_00205440(&mid, cam->view, &s[k], &depth[k]) != 0) {
            if (func_00101600(&s[k]) != 0) {
                vis |= 1 << k;
            }
        }
    }
    if (func_00205440(p2, cam->view, &s[b->n], &depth[b->n]) != 0) {
        if (func_00101600(&s[b->n]) != 0) {
            vis |= 1 << b->n;
        }
    }
    for (k = 0; k < b->n; k++) {
        if (func_00104520(b->flags, 0x1A) != 0 || k <= b->head) {
            r = func_0019A5C8() % 4;
            if (r == 0) {
                func_00104540(&pkt, &b->rect, 1);
            } else if (r == 1) {
                func_00104540(&pkt, &b->rect, 2);
            } else if (r == 2) {
                func_00104540(&pkt, &b->rect, 5);
            } else {
                func_00104540(&pkt, &b->rect, 7);
            }
            dx = func_001A6970((s32)(s[k].x - s[k + 1].x));
            dy = func_001A6970((s32)(s[k].y - s[k + 1].y));
            len = func_001A6C60(dx * dx + dy * dy);
            if (func_00104520(b->flags, 0x1B) != 0) {
                w = b->width;
            } else {
                w = len / 3.0f;
            }
            if (dx > dy) {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[k].x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[k + 1].x;
                pkt.v[0].xyz.y = s[k].y - w;
                pkt.v[1].xyz.y = s[k + 1].y - w;
                pkt.v[2].xyz.y = w + s[k].y;
                pkt.v[3].xyz.y = w + s[k + 1].y;
            } else {
                pkt.v[0].xyz.x = s[k].x - w;
                pkt.v[1].xyz.x = s[k + 1].x - w;
                pkt.v[2].xyz.x = w + s[k].x;
                pkt.v[3].xyz.x = w + s[k + 1].x;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[k].y;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[k + 1].y;
            }
            func_00208CB0(&pkt, 2 | (2 << 2) | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                                    ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
            func_00208700(&pkt, b->texture, 1);
            if (func_00104520(vis, k) != 0 && func_00104520(vis, k + 1) != 0) {
                if (func_00104520(b->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[k].z;
                    pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[k + 1].z;
                    func_002075F0(&pkt, ot, (u32)((depth[k] + depth[k + 1]) / 2.0f));
                }
            }
        }
    }
    b->head++;
    if (b->head > b->n) {
        b->head = 0;
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

static s32 func_01E03DE0_b021(Obj_b021_01E03DE0 *o, s32 owner, f32 len) {
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

static s32 func_01E03F30_b021(s32 ot __attribute__((aligned(8))), Trail_b021_01E03F30 *o, Cam_b021_01E03F30 *cam) {
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
        func_01E00120_b021((Pk_b021_01E00120 *)&pkt, &o->color, i);
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

/* shape b021:01E04320 (b021), 1656 insns, 1 copy (-O2,p): b021 scene manager (b728:01E02C90's -O2 source with b021's
   joints, timings, a third bolt ring, the light, the image and its sprite): code >= 0 sets up the cameras, three
   joints, the light, the image, a sprite outline, four spark sprites, four emitters, 16+16+16 bolts, a 4x3 grid of
   falling trails with their sprites and four flash sprites; else circles four cameras round the target, rings two
   joints with bolt ends, draws the joint bolts until 281 (the two rings from 255), then the trails, sprites and bolts
   to the cameras; the light 151..249, the image and its sprite 206..234, screen flashes 284..397 and from 398;
   re-picks bolt joints until 282; returns 3/1/6/8 by tick */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b021_01E04320;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    s16 n;
    s16 jitter;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 f20;
    f32 f24;
    s16 head;
    u8 pad2A[2];
    f32 f2C;
} Bolt_b021_01E04320;

typedef struct {
    s32 tex;
    u8 b, g, r, a;
    u8 pad8[4];
    s16 n;
    u8 padE[2];
    s16 u, v, w, h;
    s16 h18;
    s16 h1A;
    u8 pad1C[0x10];
    f32 width;
    Vec4f pts[5];
} Trail_b021_01E04320;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 size;
    u8 b, g, r, a;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Spr_b021_01E04320;

typedef struct {
    s32 tex;
    s32 flags;
    f32 scale;
    u8 b, g, r, a;
    f32 x, y, z;
    u8 pad1C[4];
} Part_b021_01E04320;

typedef struct {
    f32 x, y, z;
    s16 hC;
    s16 hE;
} Pt_b021_01E04320;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 cx, cy, cz;
    u8 pad1C[4];
    s16 uv[8];
    Pt_b021_01E04320 pts[16];
    s16 count;
    u8 pad132[4];
    s16 h136;
    s16 h138;
    s16 h13A;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_b021_01E04320;

typedef struct {
    f32 x, y, z;
} P3_b021_01E04320;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 r0;
    s16 u, v, w, h;
    u8 pad18[8];
    P3_b021_01E04320 pts[60];
} Spark_b021_01E04320;

typedef struct {
    Vec4f a;
    Vec4f b;
} Ends_b021_01E04320;

typedef struct {
    u8 b, g, r, a;
} Col_b021_01E04320;

typedef struct {
    f32 a, b, c, d;
    Vec4f pos;
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad2C[4];
} Lt_b021_01E04320;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    s32 rot[64][4];
} Img_b021_01E04320;

typedef struct {
    s32 kind;
    u8 pad4[4];
    s32 type;
    f32 scale;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    Vec4f v[8];
} Fx8_b021_01E04320;

typedef struct {
    Cam_b021_01E04320 cam0;
    Bolt_b021_01E04320 bolt[16];
    Bolt_b021_01E04320 bolt2[16];
    Bolt_b021_01E04320 bolt3[16];
    Cam_b021_01E04320 cam[4];
    Trail_b021_01E04320 trail[4][3];
    Spr_b021_01E04320 spr[4][3];
    Part_b021_01E04320 part[4][3];
    Spr_b021_01E04320 spr2[4];
    Part_b021_01E04320 part2[4];
    Emit_b021_01E04320 emit[4];
    Cam_b021_01E04320 cam1;
    Lt_b021_01E04320 lt;
    Img_b021_01E04320 img;
    Fx8_b021_01E04320 fx8;
    Spr_b021_01E04320 spr3;
    Cam_b021_01E04320 cam2[4];
    Spark_b021_01E04320 spark[4];
    Ends_b021_01E04320 ends[16];
    Vec4f center;
    Vec4f center2;
    Vec4f ring[16];
    Vec4f ring2[16];
    s32 timer;
    s32 t;
    s32 code;
    s32 x361C;
    s32 n;
    s32 pick;
    s32 near;
    s32 j[5];
    Col_b021_01E04320 src;
    f32 rad[4];
    Col_b021_01E04320 col;
    u8 fade;
    u8 pad3659[7];
} Scene_b021_01E04320;

#pragma optimization_level 2

static s32 func_01E04320_b021(s32 arg0, s32 code) {
    Scene_b021_01E04320 *g = (Scene_b021_01E04320 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F54E0(s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F6D00(s32);
    extern void func_001F6580(s32, void *);
    extern void func_001F6C10(void *);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103660(void *, void *);
    extern s32 func_00104520(s32, s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern s32 func_00103390(void *, f32, f32);
    extern s32 func_00103540(f32 *, f32, f32);
    extern s32 func_0019A5C8();
    extern s32 b021_01E05D00();
    extern s32 b021_01E03F30();
    extern s32 b021_01E03DE0(void *, s32, f32);
    extern s32 b021_01E03460();
    extern s32 b021_01E02E50();
    extern s32 b021_01E02CF0(void *, s32, f32);
    extern s32 b021_01E02710();
    extern s32 b021_01E01B80();
    extern s32 b021_01E00FA0();
    extern s32 b021_01E00C60(void *, void *, s32, f32);
    extern s32 b021_01E003D0();
    extern s32 b021_01E00270();
    Vec4f p;
    s32 tx;
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    f32 a;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3660);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        for (i = 0; i < 4; i++) {
            func_00103890(&g->cam2[i]);
            g->cam2[i].x = g->cam2[i].y = g->cam2[i].z = 0.1f;
            func_00103890(&g->cam[i]);
            g->rad[i] = 170.0f;
        }
        g->j[0] = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x19, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x26, 0);
        g->timer = 0x1E0;
        g->t = 1;
        g->code = code;
        g->x361C = 0;
        g->fade = 0x80;
        g->n = func_001F54E0(func_001F53A0()) - 1;
        g->src.r = 0x80;
        g->src.g = 0x80;
        g->src.b = 0x80;
        g->src.a = 0x80;
        g->col.r = 0x30;
        g->col.g = 0x60;
        g->col.b = 0x80;
        g->col.a = 0;
        g->lt.b = 0.5f;
        g->lt.c = 0.75f;
        g->lt.d = 1.0f;
        g->lt.a = 1.0f;
        g->lt.f20 = 0.0f;
        g->lt.f24 = 200.0f;
        g->lt.f28 = 0.0f;
        func_00103260(&tx, 0xF);
        g->img.flags = 0x80001;
        g->img.u = 0x8E;
        g->img.v = 0;
        g->img.w = 0x22;
        g->img.h = 0x40;
        g->img.r = 0x80;
        g->img.g = 0x80;
        g->img.b = 0x80;
        g->img.a = 0x20;
        b021_01E02CF0(&g->img, tx, 1.6f);
        g->spr3.flags = 0x80001;
        g->spr3.uv[0] = 0x80;
        g->spr3.uv[1] = 0;
        g->spr3.uv[2] = 0x20;
        g->spr3.uv[3] = 0x20;
        g->spr3.uv[4] = 0xB0;
        g->spr3.uv[5] = 0x20;
        g->spr3.uv[6] = 0x100;
        g->spr3.uv[7] = 0x100;
        g->spr3.size = 1.0f;
        g->spr3.r = 0x80;
        g->spr3.g = 0x80;
        g->spr3.b = 0x80;
        g->spr3.a = 0x60;
        g->spr3.h48 = 0;
        g->spr3.h4A = 0;
        g->spr3.h4C = 0;
        g->spr3.h4E = 1;
        g->spr3.h50 = 0;
        g->spr3.h52 = 999;
        g->fx8.type = 1;
        b021_01E00C60(&g->spr3, &g->fx8, tx, 20.0f);
        for (i = 0; i < 4; i++) {
            g->spark[i].tex = tx;
            g->spark[i].flags = 1;
            g->spark[i].u = 0xB0;
            g->spark[i].v = 0x40;
            g->spark[i].w = 0x20;
            g->spark[i].h = 0x20;
            g->spark[i].r0 = 0.5f;
            for (k = 0; k < 60; k++) {
                if (func_00104520(g->spark[i].flags, 0x1D)) {
                    g->spark[i].pts[k].x = func_0019A5C8() % 100 - 50;
                    g->spark[i].pts[k].z = func_0019A5C8() % 50;
                    g->spark[i].pts[k].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark[i].pts[k].x = func_0019A5C8() % 50 - 25;
                    g->spark[i].pts[k].y = func_0019A5C8() % 25;
                    g->spark[i].pts[k].z = func_0019A5C8() % 50 - 25;
                }
            }
            g->spark[i].r = 0x40;
            g->spark[i].g = 0x40;
            g->spark[i].b = 0x80;
            g->spark[i].a = 0x80;
        }
        for (i = 0; i < 4; i++) {
            g->emit[i].tex = tx;
            g->emit[i].flags = 7;
            g->emit[i].cx = 0.0f;
            g->emit[i].cy = 10.0f;
            g->emit[i].cz = 0.0f;
            g->emit[i].uv[0] = 0x80;
            g->emit[i].uv[1] = 0xC0;
            g->emit[i].uv[2] = 0x20;
            g->emit[i].uv[3] = 0x20;
            g->emit[i].uv[4] = 0x80;
            g->emit[i].uv[5] = 0xC0;
            g->emit[i].uv[6] = 0x80;
            g->emit[i].uv[7] = 0x100;
            g->emit[i].size = 30.0f;
            g->emit[i].count = 8;
            g->emit[i].h13A = 1;
            g->emit[i].h13C = 1;
            g->emit[i].h140 = 8;
            g->emit[i].h136 = 0x1E;
            g->emit[i].h138 = -0x1E;
            g->emit[i].r = 0x80;
            g->emit[i].g = 0x80;
            g->emit[i].b = 0x80;
            g->emit[i].a = 0x20;
            for (j = 0; j < 16; j++) {
                g->emit[i].pts[j].x = func_0019A5C8() % 80 - 40;
                g->emit[i].pts[j].y = func_0019A5C8() % 80;
                g->emit[i].pts[j].hE = -g->emit[i].h13A * i;
                g->emit[i].pts[j].hC = 0;
                g->emit[i].h13E = g->emit[i].h140 - 1;
            }
        }
        func_00103290(&tx, 0);
        for (i = 0; i < 16; i++) {
            g->bolt[i].tex = tx;
            if (i % 2 == 0) {
                g->bolt[i].flags = 0;
            } else {
                g->bolt[i].flags = 0x80000;
            }
            g->bolt[i].u = 0x80;
            g->bolt[i].v = 0x40;
            g->bolt[i].w = 0x20;
            g->bolt[i].h = 0x40;
            g->bolt[i].r = 0x80;
            g->bolt[i].g = 0x80;
            g->bolt[i].b = 0x80;
            g->bolt[i].a = 0x20;
            g->bolt[i].n = 0x10;
            g->bolt[i].head = -(i + 1);
            g->bolt[i].jitter = 0x14;
            g->bolt[i].f20 = 0.0f;
            g->bolt[i].f24 = 0.0f;
        }
        for (i = 0; i < 16; i++) {
            g->bolt2[i].tex = tx;
            g->bolt2[i].flags = 0xC000000;
            g->bolt2[i].u = i % 3 * 32;
            g->bolt2[i].v = 0;
            g->bolt2[i].w = 0x20;
            g->bolt2[i].h = 0x80;
            g->bolt2[i].r = 0x80;
            g->bolt2[i].g = 0x80;
            g->bolt2[i].b = 0x80;
            g->bolt2[i].a = 0x80;
            g->bolt2[i].n = 6;
            g->bolt2[i].head = 0;
            g->bolt2[i].jitter = 0x1E;
            g->bolt2[i].f20 = 0.0f;
            g->bolt2[i].f24 = 0.0f;
            g->bolt2[i].f2C = 200.0f;
        }
        for (i = 0; i < 16; i++) {
            g->bolt3[i].tex = tx;
            g->bolt3[i].flags = 0xC000000;
            g->bolt3[i].u = i % 3 * 32;
            g->bolt3[i].v = 0;
            g->bolt3[i].w = 0x20;
            g->bolt3[i].h = 0x80;
            g->bolt3[i].r = 0x80;
            g->bolt3[i].g = 0x80;
            g->bolt3[i].b = 0x80;
            g->bolt3[i].a = 0x80;
            g->bolt3[i].n = 6;
            g->bolt3[i].head = 0;
            g->bolt3[i].jitter = 0x1E;
            g->bolt3[i].f20 = 0.0f;
            g->bolt3[i].f24 = 0.0f;
            g->bolt3[i].f2C = 200.0f;
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                g->trail[i][j].n = i * 5 + 5 + j;
                g->trail[i][j].u = 0;
                g->trail[i][j].v = 0;
                g->trail[i][j].w = 0x20;
                g->trail[i][j].h = 0x80;
                g->trail[i][j].h18 = 0;
                g->trail[i][j].h1A = 0;
                g->trail[i][j].width = 20.0f;
                g->trail[i][j].r = 0x80;
                g->trail[i][j].g = 0x80;
                g->trail[i][j].b = 0x80;
                g->trail[i][j].a = 0x80;
                b021_01E03DE0(&g->trail[i][j], tx, 430.0f);
                g->spr[i][j].flags = 1;
                g->spr[i][j].size = 1.0f;
                g->spr[i][j].r = 0x80;
                g->spr[i][j].g = 0x80;
                g->spr[i][j].b = 0x80;
                g->spr[i][j].a = 0x80;
                g->spr[i][j].uv[0] = 0xE0;
                g->spr[i][j].uv[1] = 0;
                g->spr[i][j].uv[2] = 0x20;
                g->spr[i][j].uv[3] = 0x20;
                g->spr[i][j].uv[4] = 0xE0;
                g->spr[i][j].uv[5] = 0;
                g->spr[i][j].uv[6] = 0x100;
                g->spr[i][j].uv[7] = 0x80;
                g->spr[i][j].h48 = 0;
                g->spr[i][j].h4A = 0;
                g->spr[i][j].h4E = 2;
                g->spr[i][j].h52 = 999;
                g->spr[i][j].h50 = 0;
                g->spr[i][j].h4C = 1;
                {
                    s32 t = tx;
                    g->part[i][j].x = g->part[i][j].y = g->part[i][j].z = 0.0f;
                    g->part[i][j].scale = 15.0f;
                    g->part[i][j].tex = t;
                }
                g->part[i][j].r = 0x80;
                g->part[i][j].g = 0x80;
                g->part[i][j].b = 0x80;
                g->part[i][j].a = 0x80;
            }
        }
        for (i = 0; i < 4; i++) {
            g->spr2[i].flags = 1;
            g->spr2[i].size = 1.0f;
            g->spr2[i].r = 0x80;
            g->spr2[i].g = 0x80;
            g->spr2[i].b = 0x80;
            g->spr2[i].a = 0x80;
            g->spr2[i].uv[0] = 0xA0;
            g->spr2[i].uv[1] = 0;
            g->spr2[i].uv[2] = 0x40;
            g->spr2[i].uv[3] = 0x40;
            g->spr2[i].uv[4] = 0xA0;
            g->spr2[i].uv[5] = 0;
            g->spr2[i].uv[6] = 0x100;
            g->spr2[i].uv[7] = 0x80;
            g->spr2[i].h48 = 0;
            g->spr2[i].h4A = 0;
            g->spr2[i].h4E = 1;
            g->spr2[i].h52 = 999;
            g->spr2[i].h50 = 0;
            g->spr2[i].h4C = 0;
            {
                s32 t = tx;
                g->part2[i].x = g->part2[i].y = g->part2[i].z = 0.0f;
                g->part2[i].scale = 20.0f;
                g->part2[i].tex = t;
            }
            g->part2[i].r = 0x80;
            g->part2[i].g = 0x80;
            g->part2[i].b = 0x80;
            g->part2[i].a = 0x80;
        }
        return 0;
    }
    for (i = 0; i < 4; i++) {
        func_001F53C0(1, func_001F5380(), &g->cam[i].pos);
        g->cam[i].pos.z += g->rad[i] * func_0020B620(1.5707964f * i);
        g->cam[i].pos.x += g->rad[i] * func_0020B730(1.5707964f * i);
        g->cam[i].pos.y = 30.0f;
        g->cam2[i].pos = g->cam[i].pos;
    }
    func_001F5620(func_001F53A0(), g->j[1], &g->center);
    func_001F5620(func_001F53A0(), g->j[2], &g->center2);
    for (i = 0; i < 16; i++) {
        g->ring[i].y = 30.0f + g->center.y;
        a = 0.3926991f * i;
        g->ring[i].x = g->center.x + 20.0f * func_0020B620(a);
        g->ring[i].z = g->center.z + 20.0f * func_0020B730(a);
        g->ring2[i].y = 30.0f + g->center2.y;
        g->ring2[i].x = g->center2.x + 20.0f * func_0020B620(a);
        g->ring2[i].z = g->center2.z + 20.0f * func_0020B730(a);
    }
    for (i = 0; i < 16; i++) {
        if (g->t < 0x11B) {
            if (g->bolt[i].head == 0) {
                func_001F5620(func_001F53A0(), g->j[3], &g->ends[i].a);
                func_001F5620(func_001F53A0(), g->j[4], &g->ends[i].b);
                func_00103660(&g->ends[i].a, &g->cam1.pos);
                func_00103660(&g->ends[i].b, &g->cam1.pos);
            }
        } else {
            g->ends[i].a.y = 10.0f;
            g->ends[i].a.x = g->cam[i / 4].pos.x + 100.0f * func_0020B620(1.5707964f * (i % 4));
            g->ends[i].a.z = g->cam[i / 4].pos.z + 100.0f * func_0020B730(1.5707964f * (i % 4));
        }
    }
    func_001F53C0(1, func_001F53A0(), &g->cam1.pos);
    func_001038D0(&g->cam0);
    func_001038D0(&g->cam1);
    for (i = 0; i < 4; i++) {
        func_001039A0(&g->cam2[i]);
        func_001039A0(&g->cam[i]);
    }
    if (g->t < 0x1A4) {
        func_00103470(&g->fade, 0x20, 4);
    } else {
        func_001032C0(&g->fade, 0x80, 4);
    }
    func_001F6D00(g->fade);
    if (g->t > 0x11B && g->t < 0x18E && g->t % 5 == 0) {
        b021_01E00270(ot, &g->src);
    }
    if (g->t == 0x18E) {
        g->src.a = 0xFF;
    }
    if (g->t >= 0x18E) {
        b021_01E00270(ot, &g->src);
        if (g->t >= 0x196) {
            func_00103470(&g->src.a, 0, 4);
        }
    }
    if (g->t == 0x11B) {
        for (i = 0; i < 16; i++) {
            g->bolt[i].flags &= ~0x80000;
            g->bolt[i].flags |= 0x4000000;
            g->bolt[i].a = 0x80;
            g->bolt[i].jitter = 100;
            g->bolt[i].head = 0;
        }
    }
    if (g->t < 0x11A) {
        func_001F6580(func_001F53A0(), &g->col);
        if (g->t % 2 == 0) {
            g->col.a = 0x20;
        } else {
            g->col.a = 0;
        }
        for (i = 0; i < 16; i++) {
            b021_01E03460(ot, &g->bolt[i], &g->cam1, &g->ends[i].a, &g->ends[i].b);
        }
        for (i = 0; i < 8; i++) {
            if (g->t > 0xFE) {
                b021_01E03460(ot, &g->bolt2[i], &g->cam0, &g->center, &g->ring[i]);
                b021_01E03460(ot, &g->bolt3[i], &g->cam0, &g->center2, &g->ring2[i]);
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (g->trail[i][0].n == 0) {
                b021_01E003D0(ot, &g->spr2[i], g->part2, &g->cam[i]);
                func_00103470(&g->spr2[i].a, 0, 8);
                func_00103390(&g->spr2[i].size, 5.0f, 0.2f);
                p.x = p.y = p.z = 0.0f;
                b021_01E01B80(ot, &g->cam[i], &g->emit[i], &p);
                func_00103470(&g->emit[i].a, 0, 2);
                p.x = p.y = p.z = 1.0f;
                b021_01E02710(ot, &g->spark[i], &g->cam2[i], &p);
                func_001033D0(&g->cam2[i], 4.0f, 0.3f);
                func_00103470(&g->spark[i].a, 0, 8);
            } else {
                g->spr2[i].a = 0x80;
                g->spr2[i].size = 1.0f;
                g->emit[i].a = 0x20;
                g->spark[i].a = 0x80;
                g->cam2[i].x = g->cam2[i].y = g->cam2[i].z = 0.1f;
            }
        }
        for (i = 0; i < 16; i++) {
            if (g->trail[i / 4][0].n == 0) {
                b021_01E03460(ot, &g->bolt[i], &g->cam0, &g->cam[i / 4].pos, &g->ends[i].a);
                func_00103470(&g->bolt[i].a, 0, 8);
                if (g->bolt[i].head == g->bolt[i].n) {
                    g->bolt[i].flags |= 0x4000000;
                }
            } else {
                g->bolt[i].a = 0x80;
                g->bolt[i].flags &= ~0x4000000;
            }
        }
    }
    if (g->t > 0x96 && g->t < 0xFA) {
        if (g->t < 0xE6) {
            func_00103390(&g->lt.f28, 1.0f, 0.05f);
        } else {
            {
                f32 lo = 0.0f;
                f32 step = 0.2f;
                func_00103540(&g->lt.f28, lo, step);
            }
        }
        g->lt.pos.x = g->cam1.pos.x;
        g->lt.pos.y = g->cam1.pos.y;
        g->lt.pos.z = g->cam1.pos.z;
        func_001F6C10(&g->lt);
    }
    if (g->t > 0xCD && g->t < 0xEB) {
        if (func_001033D0(&g->cam1, 0.8f, 0.1f) == 0) {
            func_00103470(&g->spr3.a, 0, 6);
            func_00103470(&g->img.a, 0, 2);
        }
        b021_01E00FA0(ot, &g->spr3, &g->fx8, &g->cam1);
        b021_01E02E50(ot, &g->img, &g->cam1);
        for (i = 0; i < 64; i++) {
            g->img.rot[i][0] += 0x80;
            g->img.rot[i][1] += 0x80;
            g->img.rot[i][2] += 0x80;
        }
    }
    if (g->t >= 0x11A && g->t < 0x18F) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                if (g->trail[i][j].a < 0x60) {
                    g->trail[i][j].u = g->trail[i][j].h18 + g->trail[i][j].w;
                } else if (g->trail[i][j].a < 0x40) {
                    g->trail[i][j].u = g->trail[i][j].h18 + g->trail[i][j].w * 2;
                }
                b021_01E03F30(ot, &g->trail[i][j], &g->cam[i]);
                if (g->trail[i][j].n < 6) {
                    g->part[i][j].x = 10.0f + g->trail[i][j].pts[4 - g->trail[i][j].n].x;
                    g->part[i][j].z = g->trail[i][j].pts[4 - g->trail[i][j].n].z;
                    g->part[i][j].y = g->trail[i][j].pts[4 - g->trail[i][j].n].y;
                    if (g->trail[i][j].n == 0) {
                        g->spr[i][j].size = 1.5f;
                    } else {
                        g->spr[i][j].size = 1.0f;
                    }
                    b021_01E003D0(ot, &g->spr[i][j], &g->part[i][j],
                                       &g->cam[i]);
                    g->spr[i][j].a = g->trail[i][j].a;
                }
                if (g->trail[i][j].n != 0) {
                    g->trail[i][j].n--;
                } else if (func_00103470(&g->trail[i][j].a, 0, 8) == 0) {
                    g->trail[i][j].n = 5;
                    g->trail[i][j].a = 0x80;
                    if (j == 2) {
                        func_00103540(&g->rad[i], 20.0f, 30.0f);
                    }
                }
            }
        }
    }
    if (g->t < 0x11B) {
        b021_01E05D00(g, ot);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x1A4) {
        return 3;
    }
    if (g->t == 0x115) {
        return 1;
    }
    if (g->t >= 0x11B && g->t < 0x1A4) {
        return 6;
    }
    if (g->timer <= 0) {
        func_001F6580(func_001F53A0(), 0);
        func_001F6C10(0);
        return 8;
    }
    return 0;
}

#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p */

/* shape b021:01E05D00, 99 insns: for every free card slot (16 of 0x30 bytes) pick a random pair of neighbours from the 30-entry id table and fetch their resources (func_001F5560: ids 29, 25, 38 and the two picks) */

typedef struct {
    u8 pad0[0x18];
    s16 used;
    u8 pad1A[0x16];
} Slot_b021_01E05D00;

typedef struct {
    u8 pad0[0x80];
    Slot_b021_01E05D00 slot[16];
    u8 pad380[0x3624 - 0x380];
    s32 a;
    s32 b;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
} Ctx_b021_01E05D00;

#pragma optimization_level 1
typedef struct W_ids_func_01E05D00_b021 {
    u8 v[30];
} W_ids_func_01E05D00_b021;

static void func_01E05D00_b021(Ctx_b021_01E05D00 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern W_ids_func_01E05D00_b021 D_01E06040_b021;
    W_ids_func_01E05D00_b021 ids_w = D_01E06040_b021;
    s32 i;
    s32 n;

    for (i = 0; i < 16; i++) {
        if (g->slot[i].used == 0) {
            g->a = func_0019A5C8() % 30;
            n = g->a + 1;
            if (n < 30) {
                g->b = n;
            } else {
                g->b = 0;
            }
            g->r0 = func_001F5560(func_001F53A0(), 0x1D, 1);
            g->r1 = func_001F5560(func_001F53A0(), 0x19, 0);
            g->r2 = func_001F5560(func_001F53A0(), 0x26, 0);
            g->r3 = func_001F5560(func_001F53A0(), ids_w.v[g->a], 0);
            g->r4 = func_001F5560(func_001F53A0(), ids_w.v[g->b], 0);
        }
    }
}
#pragma optimization_level reset
