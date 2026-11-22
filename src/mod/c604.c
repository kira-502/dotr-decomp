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

static void func_01E00080_c604(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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
typedef struct W_ta_func_01E00120_c604 {
    Vec4f v[8];
} W_ta_func_01E00120_c604;

typedef struct W_tb_func_01E00120_c604 {
    Vec4f v[8];
} W_tb_func_01E00120_c604;

static s32 func_01E00120_c604(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00120_c604 D_01E04500_c604;
            W_ta_func_01E00120_c604 ta_w = D_01E04500_c604;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00120_c604 D_01E04580_c604;
            W_tb_func_01E00120_c604 tb_w = D_01E04580_c604;

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

static s32 func_01E00460_c604(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00080_c604((Vtx_b000_01E00100 *)&pk, &m->col);
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

static s32 func_01E01040_c604(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c604) and needs that helper
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

static s32 func_01E01300_c604(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c604(&pkt, &ring->color);
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

typedef struct Cam_c536_01E00120 {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    s32 steps;
} Cam_c536_01E00120;

static s32 func_01E017F0_c604(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
    f32 k;
    f32 px;
    f32 py;
    f32 pz;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 b1;
    s32 b2;

    if (t->steps != 0) {
        k = 1.0f / t->steps;
        py = k * (t->f30 - c->f30);
        pz = k * (t->f34 - c->f34);
        c->f30 += py;
        c->f34 += pz;
        a0 = k * (t->a[0] - c->a[0]);
        a1 = k * (t->a[1] - c->a[1]);
        a2 = k * (t->a[2] - c->a[2]);
        c->a[0] += a0;
        c->a[1] += a1;
        c->a[2] += a2;
        a2 = k * (t->b[0] - c->b[0]);
        a0 = k * (t->b[1] - c->b[1]);
        a1 = k * (t->b[2] - c->b[2]);
        c->b[0] += a2;
        c->b[1] += a0;
        c->b[2] += a1;
        px = k * (t->pos[0] - c->pos[0]);
        py = k * (t->pos[1] - c->pos[1]);
        pz = k * (t->pos[2] - c->pos[2]);
        c->pos[0] += px;
        c->pos[1] += py;
        c->pos[2] += pz;
    }
    t->steps--;
    return t->steps;
}

/* shape c536:01E00330: module copy of main-program func_0027F180 (rules/ta_misc.c): reset every vertex colour to white with the given alpha, then refresh the model. */

typedef struct Vertex_c536_01E00330 {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[3];
    u8 alpha;
    u8 pad1C[0x14];
} Vertex_c536_01E00330;

typedef struct Count_c536_01E00330 {
    s16 count : 12;
    s16 reserved : 4;
} Count_c536_01E00330;

typedef struct Object_c536_01E00330 {
    u8 pad0[0x78];
    Vertex_c536_01E00330 *vertices;
    s32 field7C;
    s16 field80;
    Count_c536_01E00330 field82;
    u8 pad84[0xC];
    s32 field90;
} Object_c536_01E00330;

static s32 func_01E01A00_c604(void *arg0, s32 arg1, f32 *arg2) {
    Object_c536_01E00330 *object = arg0;
    s32 result;
    s32 i;

    if (arg2 != NULL) {
        result = func_001DA2B0(object, 0, arg2[0], arg2[1]);
    } else {
        result = func_001D9F00(object, 1);
    }
    for (i = 0; i < object->field82.count; i++) {
        object->vertices[i].color = 0xFFFFFF;
        object->vertices[i].alpha = arg1;
    }
    if (result != 0) {
        func_001DA7A0(object->field90, (s32) object);
    } else {
        func_001DA7A0(0, (s32) object);
    }
    func_001DBCF0((s32) object);
    return 0;
}

typedef struct {
    u8 pad00[0xC];
    s16 x;
    s16 y;
    u8 pad10[6];
    s16 width;
    u8 pad18[2];
    s16 base;
    u8 pad1C[4];
    s16 digit[5];
    s16 pos[5];
    s16 h34;
    s16 h36;
    s32 w38;
} Num_c508_01E013C0;

static s32 func_01E01B10_c604(Num_c508_01E013C0 *o, s16 x, s16 y, s32 n) {
    s32 k;

    o->x = x;
    o->y = y;
    o->h36 = 0;
    o->h34 = 0;
    o->w38 = 0;
    if (n >= 0) {
        o->digit[0] = 11;
    } else {
        o->digit[0] = 10;
        n = -n;
    }
    if (n > 999) {
        o->digit[1] = n / 1000;
        o->digit[2] = n % 1000 / 100;
        o->digit[3] = n % 100 / 10;
        o->digit[4] = n % 10;
    } else if (n > 99) {
        o->digit[1] = n / 100;
        o->digit[2] = n % 100 / 10;
        o->digit[3] = n % 10;
        o->digit[4] = -1;
    } else if (n > 9) {
        o->digit[1] = n / 10;
        o->digit[2] = n % 10;
        o->digit[3] = -1;
        o->digit[4] = -1;
    } else {
        o->digit[1] = n % 10;
        o->digit[2] = -1;
        o->digit[3] = -1;
        o->digit[4] = -1;
    }
    for (k = 0; k < 5; k++) {
        o->pos[k] = o->base + o->width * o->digit[k];
    }
    return 0;
}

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    s32 pad;
} Uv_c508_01E015C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c508_01E015C0;

typedef struct {
    Uv_c508_01E015C0 uv;
    Xyz_c508_01E015C0 p;
} Vtx_c508_01E015C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_c508_01E015C0 v[4];
    u8 tail[0x20];
} Pkt_c508_01E015C0;

typedef struct {
    u8 b, g, r, a;
} Src_c508_01E015C0;

typedef struct {
    void *tex;
    s32 flags;
    Src_c508_01E015C0 c;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 du;
    s16 dv;
    s16 u0;
    s16 v0;
    u8 pad1C[4];
    s16 digit[5];
    s16 anim[5];
    s16 x;
    s16 h36;
    s32 frame;
} Num_c508_01E015C0;

typedef struct {
    s32 x;
    s32 y;
    s32 pad;
    s32 off;
} Pos_c508_01E015C0;

static s32 func_01E01D10_c604(s32 obj __attribute__((aligned(8))), Num_c508_01E015C0 *o, Pos_c508_01E015C0 *pos) {
    extern s32 func_00104520(s32, s32);
    Pkt_c508_01E015C0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 x;
    s32 half;
    s32 n;
    s32 t;

    if (o->digit[2] < 0) {
        n = 2;
        x = o->x - o->w;
    } else if (o->digit[3] < 0) {
        n = 3;
        x = o->x - (o->w + (o->w >> 1));
    } else if (o->digit[4] < 0) {
        n = 4;
        x = o->x - o->w * 2;
    } else {
        n = 5;
        x = o->x - ((o->w >> 1) + o->w * 2);
    }
    half = o->h >> 1;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->count = 0x24;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->tag = 9;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0x12) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    }
    pkt.r = o->c.r;
    pkt.g = o->c.g;
    pkt.b = o->c.b;
    pkt.a = o->c.a;
    pkt.q = 1.0f;
    for (i = 0; i < n; i++) {
        o->u = o->u0;
        if (func_00104520(o->flags, 9) != 0 && func_00104520(o->flags, i + 10) == 0) {
            o->v = o->anim[i];
            if (o->v >= o->dv * 12) {
                o->anim[i] = 0;
                o->v = 0;
            }
            o->anim[i] += 8;
        } else {
            o->v = o->v0 + o->dv * o->digit[i];
        }
        ((Pkt_c508_01E015C0 *)(s32)&pkt)->count |= 0x800;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[0].uv)->u = o->u * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[0].uv)->v = o->v * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[1].uv)->u = (o->u + o->du) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[1].uv)->v = o->v * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[2].uv)->u = o->u * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[2].uv)->v = (o->v + o->dv) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[3].uv)->u = (o->u + o->du) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[3].uv)->v = (o->v + o->dv) * 16;
        if (func_00104520(o->flags, 0x1C) != 0) {
            if (n % 2 == 0) {
                if ((t = x + o->w * i) <= -o->w * 2) {
                    pos->off = -pos->y;
                } else if (t <= -o->w) {
                    pos->off = -pos->y >> 1;
                } else if (t >= o->w) {
                    pos->off = pos->y;
                } else if (t >= 0) {
                    pos->off = pos->y >> 1;
                } else {
                    pos->off = 0;
                }
            } else {
                s32 d;
                if (-(o->w + (o->w >> 1)) > (d = x + o->w * i)) {
                    pos->off = -pos->y;
                } else if (d < -o->w >> 1) {
                    pos->off = -pos->y >> 1;
                } else if (d >= o->w + (o->w >> 1)) {
                    pos->off = pos->y;
                } else if (d >= o->w >> 1) {
                    pos->off = pos->y >> 1;
                } else {
                    pos->off = 0;
                }
            }
        }
        pkt.v[0].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * i))) << 4;
        pkt.v[0].p.y = (pos->y + 0x800 - half) << 4;
        pkt.v[0].p.z = 0xFFFFFF;
        pkt.v[0].p.f = 0;
        pkt.v[1].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * (i + 1)))) << 4;
        pkt.v[1].p.y = (pos->y + 0x800 - half) << 4;
        pkt.v[1].p.z = 0xFFFFFF;
        pkt.v[1].p.f = 0;
        pkt.v[2].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * i))) << 4;
        pkt.v[2].p.y = (pos->y + 0x800 + half) << 4;
        pkt.v[2].p.z = 0xFFFFFF;
        pkt.v[2].p.f = 0;
        pkt.v[3].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * (i + 1)))) << 4;
        pkt.v[3].p.y = (pos->y + 0x800 + half) << 4;
        pkt.v[3].p.z = 0xFFFFFF;
        pkt.v[3].p.f = 0;
        func_00208700(&pkt, o->tex, 0);
        func_002075F0((s32)&pkt, obj, 0);
    }
    o->frame++;
    if (func_00104520(o->flags, 0xF) == 0) {
        if (o->frame == 4) {
            o->flags |= 0x400;
        } else if (o->frame == 8) {
            o->flags |= 0x800;
        } else if (o->frame == 12) {
            o->flags |= 0x1000;
        } else if (o->frame == 16) {
            o->flags |= 0x2000;
        } else if (o->frame == 20) {
            o->flags |= 0x4000;
        }
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

extern void c604_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E024B0_c604(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c604_01E00080(&pkt, &sp->color);
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

static s32 func_01E02A90_c604(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E04600_c604;
    Tbl_b000_01E032C0 tbl = D_01E04600_c604;
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

static s32 func_01E02BF0_c604(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_c604((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* shape c604:01E03200 (LkSortSlash), 369 insns, 2 copies: c611:01E00A80's source (b000:01E03420's sprite quad for a
   slash): blend by flags 11/10, colour into the four vertices, UVs from the integer or float rectangle; the two lower
   corners slide in y toward -10 x the slash's scale at 4 x the scale a frame; one matrix from the slash's rotation,
   each corner projected (flags 20..23 when on screen); flag 19 draws it at the far z, else all four on screen draw at
   their mean depth */

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
} Vtx_c604_01E03200;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_c604_01E03200;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c604_01E03200 v[4];
    u8 tail[0x20];
} Pkt_c604_01E03200;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    f32 scale;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec4f p[4];
    Vec4f rot[1];
} Slash_c604_01E03200;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c604_01E03200;

static s32 func_01E03200_c604(s32 obj, Slash_c604_01E03200 *spr, Cam_c604_01E03200 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00103540(void *, f32, f32);
    Vec4f out;
    f32 m[16];
    f32 depth[4];
    f32 step;
    Pkt_c604_01E03200 pkt;

    ((Pkt_c604_01E03200 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c604_01E03200 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c604((Vtx_b000_01E00100 *)&pkt, &spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_c604_01E03200 *)(s32)&pkt)->count |= 0x800;
        ((UV_c604_01E03200 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_c604_01E03200 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
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
    func_00103540(&spr->p[2].y, -10.0f * spr->scale, 4.0f * spr->scale);
    step = 4.0f * spr->scale;
    func_00103540(&spr->p[3].y, -10.0f * spr->scale, step);
    func_0020C630(m, spr->rot);
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
    if (func_00104520(spr->flags, 0x13) != 0) {
        pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
        func_002075F0(&pkt, obj, 0);
    } else if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
               func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
        func_002075F0(&pkt, obj, func_001A23B0((depth[3] + (depth[2] + (depth[0] + depth[1]))) / 4.0f));
    }
    spr->flags &= 0xFF0FFFFF;
    return 0;
}


/* shape c604:01E037D0 (c604), 819 insns, 1 copy: the c604 module main (two-unit c601:01E02860 form): needs unit A; on
   start clears the 0x1400 scene, copies and flags both units' cards, aims them at -150/150 (code bit 18: in one
   step), 60 ticks, then (also on restart) a slash sprite set up inline (scale 20), a number from code's low half, a
   sprite (scale 15), two rings (120/115 and 120/130), an 8-point outline (scale 200) and a 60-point spark cloud; each
   tick turns the views, once both cards land draws the number, the slash in random colours and the effects, grows
   them by 0.2 to 1 then fades them, ending with 8 or flipping to the other side (flag 0x1F) and setting up again;
   moves and draws the cards; 2 at tick 20, 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_c604_01E037D0;

typedef struct {
    s32 a, b, c, d;
} Rnd_c604_01E037D0;

typedef struct {
    f32 x, y, z, w;
} V4_c604_01E037D0;

typedef struct {
    V4_c604_01E037D0 v[4];
} Tbl_c604_01E037D0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c604_01E037D0 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    V4_c604_01E037D0 p[4];
    s32 rot[4];
} Slash_c604_01E037D0;

typedef struct {
    s32 kind;
    s32 flags;
    Col_c604_01E037D0 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rnd_c604_01E037D0 r[64];
} Spr_c604_01E037D0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c604_01E037D0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c604_01E037D0;

typedef struct {
    s32 kind;
    s32 flags;
    s32 type;
    u8 padC[0x94];
} Fx_c604_01E037D0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c604_01E037D0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c604_01E037D0;

typedef struct {
    f32 x, y, z;
} Pt_c604_01E037D0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c604_01E037D0 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_c604_01E037D0 pts[60];
} Spark_c604_01E037D0;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c604_01E037D0 c;
    u8 padC[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    u8 pad20[0x20];
} Num_c604_01E037D0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 off;
} Pos_c604_01E037D0;

typedef struct {
    u8 pad00[0x43];
    u8 f43;
} Src_c604_01E037D0;

typedef struct {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0x45];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c604_01E037D0;

typedef struct {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 steps;
    u8 pad4C[4];
} Ctl_c604_01E037D0;

typedef struct {
    f32 x, y, z;
    u8 padC[0x64];
    u8 cam1[0x70];
    Slash_c604_01E037D0 slash;
    Spr_c604_01E037D0 spr;
    Fx_c604_01E037D0 fx;
    Mdl_c604_01E037D0 mdl;
    Ring_c604_01E037D0 ring0;
    Ring_c604_01E037D0 ring1;
    Spark_c604_01E037D0 spark;
    Num_c604_01E037D0 num;
    Pos_c604_01E037D0 pos;
    Unit_c604_01E037D0 cardA;
    Unit_c604_01E037D0 cardB;
    Ctl_c604_01E037D0 ctlA;
    Ctl_c604_01E037D0 ctlB;
    f32 vx, vy, vz;
    u8 pad13DC[4];
    s32 tex;
    s32 timer;
    f32 dist;
    s32 alpha;
    s32 side;
    s32 tick;
    s32 flags;
    s32 n;
} Scene_c604_01E037D0;

static s32 func_01E037D0_c604(s32 arg0, s32 code) {
    Scene_c604_01E037D0 *g = (Scene_c604_01E037D0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103260(void *, s32);
    extern s32 func_00103470(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00205C40();
    extern Tbl_c604_01E037D0 D_01E04640_c604;
    Tbl_c604_01E037D0 tbl;
    s32 ot;
    s32 idA;
    s32 idB;
    Src_c604_01E037D0 *a;
    Src_c604_01E037D0 *b;
    s32 rv;
    s32 fast;
    s32 i;
    s32 j;
    f32 h;
    f32 y;

    ot = (s32)func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Src_c604_01E037D0 *)func_001F5B30(idA);
    b = (Src_c604_01E037D0 *)func_001F5B30(idB);
    rv = 0;
    h = 0.0f;
    y = 0.0f;
    if (a == NULL) {
        return 8;
    }
    if (a == NULL && b == NULL) {
        return 8;
    }
    if (code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x1400);
        func_00103890(g);
        func_00103890(g->cam1);
        g->cardA = *(Unit_c604_01E037D0 *)a;
        if (b) {
            g->cardB = *(Unit_c604_01E037D0 *)b;
        }
        func_001F59D0(idA, 1);
        g->cardA.b6 = 1;
        g->cardA.b5 = 1;
        if (b) {
            func_001F59D0(idB, 1);
            g->cardB.b6 = 1;
            g->cardB.b5 = 1;
        }
        g->flags = 0;
        g->tick = 0;
        g->side = (code >> 16) & 3;
        a->f43 = 0;
        if (b) {
            b->f43 = 0;
        }
        g->alpha = 0x80;
        fast = (code >> 18) & 1;
        if (fast) {
            g->ctlA.steps = 1;
        } else {
            g->ctlA.steps = 20;
        }
        g->ctlA.x = -150.0f;
        g->ctlA.y = 0.0f;
        func_00205CB0(&g->ctlA, g->ctlA.x, g->ctlA.y);
        func_00205C40(g->ctlA.b);
        g->ctlA.b[0] -= g->cardA.b[0];
        g->ctlA.b[1] -= g->cardA.b[1];
        g->ctlA.b[2] -= g->cardA.b[2];
        g->ctlA.a[0] = 0;
        g->ctlA.a[1] = 0x10000;
        g->ctlA.a[2] = 0x10000;
        g->ctlA.f30 = g->ctlA.f34 = 1.0f;
        if (b) {
            if (fast) {
                g->ctlB.steps = 1;
            } else {
                g->ctlB.steps = 20;
            }
            g->ctlB.x = 150.0f;
            g->ctlB.y = 0.0f;
            func_00205CB0(&g->ctlB, g->ctlB.x, g->ctlB.y);
            func_00205C40(g->ctlB.b);
            g->ctlB.b[0] -= g->cardB.b[0];
            g->ctlB.b[1] -= g->cardB.b[1];
            g->ctlB.b[2] -= g->cardB.b[2];
            g->ctlB.a[0] = 0;
            g->ctlB.a[1] = 0x10000;
            g->ctlB.a[2] = 0x10000;
            g->ctlB.f30 = g->ctlB.f34 = 1.0f;
        }
        g->timer = 60;
        g->n = code & 0xFFFF;
    restart:
        func_00103260(&g->tex, 0xF);
        g->slash.flags = 0x80001;
        g->slash.u = 0x8E;
        g->slash.v = 0;
        g->slash.w = 0x22;
        g->slash.h = 0x40;
        g->slash.color.r = 0x80;
        g->slash.color.g = 0x80;
        g->slash.color.b = 0xE0;
        g->slash.color.a = 0x80;
        {
            s32 kind = g->tex;
            tbl = D_01E04640_c604;
            g->slash.scale = 20.0f;
            g->slash.texture = kind;
        }
        for (i = 0; i < 4; i++) {
            g->slash.p[i].x = g->slash.scale * tbl.v[i].x;
            g->slash.p[i].y = g->slash.scale * tbl.v[i].y;
            g->slash.p[i].z = g->slash.scale * tbl.v[i].z;
        }
        g->slash.rot[2] = -0x2000;
        g->num.flags = 0x40000;
        g->num.tex = g->tex;
        g->num.u = 0;
        g->num.v = 0;
        g->num.w = 0xA;
        g->num.h = 0x10;
        g->num.u0 = 0;
        g->num.v0 = 8;
        g->num.tw = 0x100;
        g->num.th = 0x100;
        g->num.c.r = 0xB0;
        g->num.c.g = 0x50;
        g->num.c.b = 0x60;
        g->num.c.a = 0x80;
        func_01E01B10_c604((Num_c508_01E013C0 *)&g->num, 0x1E, 0x30, -g->n);
        if (g->side == 0) {
            g->pos.x = 150;
        } else {
            g->pos.x = -150;
        }
        g->pos.y = g->pos.z = 0;
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.color.r = 0xB0;
        g->spr.color.g = 0x50;
        g->spr.color.b = 0x60;
        g->spr.color.a = 0x20;
        func_01E02A90_c604((Obj_b000_01E032C0 *)&g->spr, g->tex, 15.0f);
        g->ring0.flags = 0x20080000;
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.color.r = 0xB0;
        g->ring0.color.g = 0x50;
        g->ring0.color.b = 0x60;
        g->ring0.color.a = 0x20;
        func_01E01040_c604((Ring_b001_01E035A0 *)&g->ring0, g->tex, 120.0f, 115.0f, 0.0f, 0.0f);
        g->ring1.flags = 0x20080000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0xB0;
        g->ring1.color.g = 0x50;
        g->ring1.color.b = 0x60;
        g->ring1.color.a = 0x30;
        func_01E01040_c604((Ring_b001_01E035A0 *)&g->ring1, g->tex, 120.0f, 130.0f, y, h);
        g->mdl.flags = 0x80001;
        g->mdl.r[0] = 0x80;
        g->mdl.r[1] = 0;
        g->mdl.r[2] = 0x20;
        g->mdl.r[3] = 0x20;
        g->mdl.r[4] = 0xB0;
        g->mdl.r[5] = 0x20;
        g->mdl.r[6] = 0x100;
        g->mdl.r[7] = 0x100;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0xB0;
        g->mdl.color.g = 0x50;
        g->mdl.color.b = 0x60;
        g->mdl.color.a = 0x60;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        g->fx.type = 1;
        func_01E00120_c604((Model_b013_01E001A0 *)&g->mdl, (Fx_b013_01E001A0 *)&g->fx, g->tex, 200.0f);
        g->spark.texture = g->tex;
        g->spark.flags = 0x20080001;
        g->spark.size = 2.5f;
        {
            s32 k;

            for (k = 0; k < 60; k++) {
                if (func_00104520(g->spark.flags, 0x1D)) {
                    g->spark.pts[k].x = func_0019A5C8() % 100 - 50;
                    g->spark.pts[k].z = func_0019A5C8() % 50;
                    g->spark.pts[k].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark.pts[k].x = func_0019A5C8() % 50 - 25;
                    g->spark.pts[k].y = func_0019A5C8() % 25;
                    g->spark.pts[k].z = func_0019A5C8() % 50 - 25;
                }
            }
        }
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0xB0;
        g->spark.color.g = 0x50;
        g->spark.color.b = 0x60;
        g->spark.color.a = 0x80;
        g->vx = 1.17f;
        g->vy = 1.17f;
        g->vz = 1.17f;
        g->x = g->y = g->z = 0.1f;
        if (func_00104520(g->flags, 0x1F)) {
            goto spin;
        }
        return 0;
    }
    if (func_00104520(g->flags, 0x1F)) {
        g->dist = -150.0f;
    } else {
        g->dist = 150.0f;
    }
    func_00103920(g, g->dist, 0.0f);
    func_00103920(g->cam1, g->dist, 0.0f);
    if (b == NULL) {
        g->flags |= 2;
    }
    if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
        if (g->side == 0) {
            func_01E01D10_c604(ot, (Num_c508_01E015C0 *)&g->num, (Pos_c508_01E015C0 *)&g->pos);
        } else if (func_00104520(g->flags, 0x1F) && g->side != 2) {
            func_01E01D10_c604(ot, (Num_c508_01E015C0 *)&g->num, (Pos_c508_01E015C0 *)&g->pos);
        }
        g->slash.color.r = func_0019A5C8() % 255;
        g->slash.color.g = func_0019A5C8() % 255;
        g->slash.color.b = func_0019A5C8() % 255;
        func_01E03200_c604(ot, (Slash_c604_01E03200 *)&g->slash, (Cam_c604_01E03200 *)g->cam1);
        func_01E024B0_c604(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)g, (s32)&g->vx);
        func_01E01300_c604(ot, (Ring_b001_01E03860 *)&g->ring0, (Cam_b001_01E03860 *)g);
        func_01E01300_c604(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)g);
        func_01E00460_c604(ot, (Model_b013_01E004E0 *)&g->mdl, (Fx_b013_01E004E0 *)&g->fx, (Cam_b013_01E004E0 *)g);
        func_01E02BF0_c604(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)g);
        if (g->x < 1.0f) {
            if (!func_001033D0(&g->x, 1.0f, 0.2f)) {
                rv = 2;
            }
        } else {
            g->x += 0.005f;
            g->y += 0.005f;
            g->z += 0.005f;
            if (g->slash.p[3].y == -10.0f * g->slash.scale) {
                func_00103470(&g->slash.color.a, 0, 0x10);
            }
            func_00103470(&g->spark.color.a, 0, 4);
            func_00103470(&g->spr.color.a, 0, 4);
            func_00103470(&g->ring0.color.a, 0, 4);
            func_00103470(&g->ring1.color.a, 0, 4);
            func_00103470(&g->num.c.a, 0, 8);
            if (!func_00103470(&g->mdl.color.a, 0, 6)) {
                if (g->side == 0 || g->side == 3) {
                    rv = 8;
                } else if (!func_00104520(g->flags, 0x1F)) {
                    g->flags |= 0x80000000;
                    goto restart;
                }
            }
        }
    spin:
        for (j = 0; j < 64; j++) {
            g->spr.r[j].a += 0x80;
            g->spr.r[j].b += 0x80;
            g->spr.r[j].c += 0x80;
        }
    }
    ot = func_00207F60();
    func_001D99F0();
    if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
        func_01E01A00_c604(&g->cardA, g->alpha, &g->ctlA.x);
        if (b) {
            func_01E01A00_c604(&g->cardB, g->alpha, &g->ctlB.x);
        }
    } else {
        if (!func_00104520(g->flags, 0)) {
            if (!func_01E017F0_c604((Cam_c536_01E00120 *)&g->cardA, (Cam_c536_01E00120 *)&g->ctlA)) {
                g->flags |= 1;
                g->cardA.a[0] = 0;
                g->cardA.a[1] = 0;
                g->cardA.a[2] = 0;
            }
            func_01E01A00_c604(&g->cardA, g->alpha, NULL);
        }
        if (b && !func_00104520(g->flags, 1)) {
            if (!func_01E017F0_c604((Cam_c536_01E00120 *)&g->cardB, (Cam_c536_01E00120 *)&g->ctlB)) {
                g->flags |= 2;
                g->cardB.a[0] = 0;
                g->cardB.a[1] = 0;
                g->cardB.a[2] = 0;
            }
            func_01E01A00_c604(&g->cardB, g->alpha, NULL);
        }
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    g->tick++;
    if (g->tick == 20) {
        rv = 2;
    }
    if (--g->timer == 0) {
        rv = 8;
    }
    return rv;
}
