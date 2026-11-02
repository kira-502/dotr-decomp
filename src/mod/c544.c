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

static void func_01E00080_c544(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static void func_01E00120_c544(Pk_b021_01E00120 *p, Src_b021_01E00120 *s, s32 lvl) {
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

static s32 func_01E00270_c544(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
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
    func_01E00080_c544((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
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
typedef struct W_ta_func_01E00B00_c544 {
    Vec4f v[8];
} W_ta_func_01E00B00_c544;

typedef struct W_tb_func_01E00B00_c544 {
    Vec4f v[8];
} W_tb_func_01E00B00_c544;

static s32 func_01E00B00_c544(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00B00_c544 D_01E02500_c544;
            W_ta_func_01E00B00_c544 ta_w = D_01E02500_c544;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00B00_c544 D_01E02580_c544;
            W_tb_func_01E00B00_c544 tb_w = D_01E02580_c544;

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

static s32 func_01E00E40_c544(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00080_c544((Vtx_b000_01E00100 *)&pk, &m->col);
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

static s32 func_01E01A20_c544(Obj_b021_01E03DE0 *o, s32 owner, f32 len) {
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

static s32 func_01E01B70_c544(s32 ot __attribute__((aligned(8))), Trail_b021_01E03F30 *o, Cam_b021_01E03F30 *cam) {
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
        func_01E00120_c544((Pk_b021_01E00120 *)&pkt, &o->color, i);
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

/* shape c544:01E01F60 (c544), 331 insns, 1 copy: c544's scene manager: with a code it clears the scene (5-tick count,
   46-tick timer, grey 0x80), reads the effect position, sets up 8 blue trails (texture 15, delays 5, 7, .., 19), a
   blue glow sprite and a white second sprite on texture 11; otherwise it steps the model and its emitter, fades the
   scene grey after tick 36, and while the emitter is lit redraws each trail (the glow follows a trail's last point
   when its delay runs out), re-rolling a trail's points once it fades; returns 8 when the timer ends */

typedef struct Pt_c544_01E01F60 {
    f32 x, y, z, w;
} Pt_c544_01E01F60;

typedef struct Trail_c544_01E01F60 {
    u8 hdr[4];
    u8 b, g, r, a;
    u8 pad8[4];
    s16 delay;
    u8 padE[2];
    s16 h80;
    s16 h82;
    s16 h84;
    s16 h86;
    s16 h88;
    s16 h8A;
    u8 pad1C[0x10];
    f32 f9C;
    Pt_c544_01E01F60 pts[5];
} Trail_c544_01E01F60;

typedef struct Emit_c544_01E01F60 {
    s16 rect[8];
    u8 pad10[0x20];
    f32 scale;
    u8 b, g, r, a;
    s32 w38;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Emit_c544_01E01F60;

typedef struct Game_c544_01E01F60 {
    u8 pad0[0x20];
    u8 pos[0x50];
    Trail_c544_01E01F60 trail[8];
    u8 d470[8];
    s32 w478;
    u8 pad47C[8];
    f32 f484;
    u8 pad488[0x88];
    Emit_c544_01E01F60 e2;
    s32 tex;
    u8 pad574[4];
    f32 size;
    u8 b, g, r, a;
    f32 at[3];
    u8 pad58C[4];
    Emit_c544_01E01F60 e1;
    s32 count;
    s32 timer;
    s32 code;
    s32 w5FC;
    u8 grey;
} Game_c544_01E01F60;

static s32 func_01E01F60_c544(s32 arg0, s32 code) {
    Game_c544_01E01F60 *g = (Game_c544_01E01F60 *)arg0;
    extern void func_00103260();
    extern void func_001F53B0();
    extern void func_001F6CF0();
    extern s32 func_00103470();
    extern s32 func_001032C0();
    extern void c544_01E00B00(void *, void *, s32, f32);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 j;

    ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108((s32)g, 0x610);
        g->w5FC = 0;
        g->count = 5;
        g->timer = 46;
        g->code = code;
        g->grey = 0x80;
        func_00103890(g);
        func_001F53B0(0, g->pos);
        func_00103260(&tex, 0xF);
        for (i = 0; i < 8; i++) {
            g->trail[i].h80 = 10;
            g->trail[i].h82 = 0;
            g->trail[i].h84 = 0x2C;
            g->trail[i].h86 = 0x80;
            g->trail[i].h88 = 10;
            g->trail[i].h8A = 0;
            g->trail[i].f9C = 11.0f;
            g->trail[i].r = 0x60;
            g->trail[i].g = 0x60;
            g->trail[i].b = 0xB0;
            g->trail[i].a = 0x80;
            func_01E01A20_c544((void *)&g->trail[i], tex, 160.0f);
            g->trail[i].delay = i * 2 + 5;
        }
        g->e1.scale = 1.0f;
        g->e1.w38 = 3;
        g->e1.rect[0] = 0xB0;
        g->e1.rect[1] = 0x40;
        g->e1.rect[2] = 0x20;
        g->e1.rect[3] = 0x20;
        g->e1.rect[4] = 0xB0;
        g->e1.rect[5] = 0x40;
        g->e1.rect[6] = 0x80;
        g->e1.rect[7] = 0x40;
        g->e1.h48 = 0;
        g->e1.h4A = 0;
        g->e1.h4E = 2;
        g->e1.h52 = 999;
        g->e1.h50 = 0;
        g->e1.h4C = g->e1.h4E - 1;
        g->e1.r = 0x60;
        g->e1.g = 0x60;
        g->e1.b = 0xB0;
        g->e1.a = 0x80;
        i = tex;
        g->at[2] = 0.0f;
        g->at[1] = 0.0f;
        g->at[0] = 0.0f;
        g->size = 10.0f;
        g->tex = i;
        g->r = 0x80;
        g->g = 0x80;
        g->b = 0x80;
        g->a = 0x80;
        g->at[1] = 5.5f;
        func_00103260(&tex, 0xB);
        g->e2.scale = 1.0f;
        g->e2.w38 = 3;
        g->e2.rect[0] = 0;
        g->e2.rect[1] = 0;
        g->e2.rect[2] = 0x40;
        g->e2.rect[3] = 0x40;
        g->e2.rect[4] = 0;
        g->e2.rect[5] = 0;
        g->e2.rect[6] = 0x80;
        g->e2.rect[7] = 0x40;
        g->e2.h48 = 0;
        g->e2.h4A = 1;
        g->e2.h4E = 1;
        g->e2.h52 = 999;
        g->e2.h50 = 0;
        g->e2.h4C = g->e2.h4E - 1;
        g->e2.r = 0x80;
        g->e2.g = 0x80;
        g->e2.b = 0x80;
        g->e2.a = 0;
        g->w478 = 1;
        c544_01E00B00(&g->e2, g->d470, tex, 50.0f);
        g->f484 = 160.0f;
        return 0;
    }
    func_001039A0(g);
    func_001F6CF0(g->grey);
    func_01E00E40_c544(ot, (void *)&g->e2, (void *)g->d470, (void *)g);
    if (g->timer > 36) {
        func_00103470(&g->grey, 0x20, 0x10);
    }
    if (g->timer < 10) {
        func_00103470(&g->e2.a, 0, 0x10);
        func_001032C0(&g->grey, 0x80, 0x10);
    } else if (!func_001032C0(&g->e2.a, 0x80, 0x10)) {
        for (i = 0; i < 8; i++) {
            if (g->trail[i].a < 0x60) {
                g->trail[i].h80 = g->trail[i].h88 + g->trail[i].h84;
            } else if (g->trail[i].a < 0x40) {
                g->trail[i].h80 = g->trail[i].h88 + g->trail[i].h84 * 2;
            }
            if (g->trail[i].delay == 0) {
                g->at[1] = 5.5f - g->trail[i].pts[4].z;
                g->at[0] = g->trail[i].pts[4].x;
                g->at[2] = g->trail[i].pts[4].z;
                g->e1.a = g->trail[i].a;
                func_01E00270_c544(ot, (void *)&g->e1, (void *)&g->tex, (void *)g);
            }
            func_01E01B70_c544(ot, (void *)&g->trail[i], (void *)g);
            if (g->trail[i].delay) {
                g->trail[i].delay--;
            } else if (!func_00103470(&g->trail[i].a, 0, 0x10)) {
                g->trail[i].delay = 5;
                g->trail[i].a = 0x80;
                for (j = 0; j < 5; j++) {
                    if (j == 4) {
                        g->trail[i].pts[j].x = func_0019A5C8() % 30 - 15;
                        g->trail[i].pts[j].z = func_0019A5C8() % 30 - 15;
                    } else {
                        g->trail[i].pts[j].x = func_0019A5C8() % 40 - 20;
                        g->trail[i].pts[j].z = func_0019A5C8() % 30 - 15;
                    }
                }
            }
        }
    }
    if (g->count) {
        g->count--;
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

