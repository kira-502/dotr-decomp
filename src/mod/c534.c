#include "common.h"

/* shape b000:01E00080, 31 insns, 12 copies: colour the two vertices of a line packet; mode 0 = colour on the
   first vertex (second black), else on the second (first black); alpha and q = 1.0 on both */

typedef struct Src_b000_01E00080 {
    u8 b, g, r, a;
} Src_b000_01E00080;

typedef struct Xyz_b000_01E00080 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E00080;

typedef struct Vtx_b000_01E00080 {
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00080 p;
} Vtx_b000_01E00080;

typedef struct Pk_b000_01E00080 {
    u8 head[0x10];
    Vtx_b000_01E00080 v[2];
} Pk_b000_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c534(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
    if (mode == 0) {
        p->v[0].r = s->r;
        p->v[0].g = s->g;
        p->v[0].b = s->b;
        p->v[1].r = 0;
        p->v[1].g = 0;
        p->v[1].b = 0;
    } else {
        p->v[0].r = 0;
        p->v[0].g = 0;
        p->v[0].b = 0;
        p->v[1].r = s->r;
        p->v[1].g = s->g;
        p->v[1].b = s->b;
    }
    p->v[0].a = s->a;
    p->v[0].q = 1.0f;
    p->v[1].a = s->a;
    p->v[1].q = 1.0f;
    p->v[0].p.f = 0;
    p->v[1].p.f = 0;
}

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

static void func_01E00100_c534(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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
typedef struct W_ta_func_01E001A0_c534 {
    Vec4f v[8];
} W_ta_func_01E001A0_c534;

typedef struct W_tb_func_01E001A0_c534 {
    Vec4f v[8];
} W_tb_func_01E001A0_c534;

static s32 func_01E001A0_c534(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E001A0_c534 D_01E04C00_c534;
            W_ta_func_01E001A0_c534 ta_w = D_01E04C00_c534;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E001A0_c534 D_01E04C80_c534;
            W_tb_func_01E001A0_c534 tb_w = D_01E04C80_c534;

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

static s32 func_01E004E0_c534(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00100_c534((Vtx_b000_01E00100 *)&pk, &m->col);
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

static s32 func_01E010C0_c534(Num_c508_01E013C0 *o, s16 x, s16 y, s32 n) {
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

static s32 func_01E012C0_c534(s32 obj __attribute__((aligned(8))), Num_c508_01E015C0 *o, Pos_c508_01E015C0 *pos) {
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

extern void c534_01E00100(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E01A60_c534(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c534_01E00100(&pkt, &sp->color);
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

static s32 func_01E02040_c534(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00100_c534) and needs that helper
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

static s32 func_01E02300_c534(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00100_c534(&pkt, &ring->color);
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

/* shape c534:01E027F0 (LkSortLevelmark), 399 insns, 1 copy: draws a row of n level marks (b001:01E03860's sprite
   packet, colour via c534:01E00100, blend by flags 0xB / 0xA, texel UVs written through c560:01E01E40's uv inline):
   each mark a square of half-size 0xC around its point, sent when all four corners land (flags 0x14..0x17); a mark
   whose counter is 9999 sits in its slot of the row (x = (2i - (n - 1)) * size, y -15, z 120), otherwise it eases
   toward z 600 at 150 and parks at 9999 once there */

typedef struct {
    u8 b, g, r, a;
} Src_c534_01E027F0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c534_01E027F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c534_01E027F0 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c534_01E027F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c534_01E027F0 v[4];
    u8 tail[0x20];
} Pkt_c534_01E027F0;

typedef struct {
    f32 x, y, z;
    u8 padC[2];
    s16 cnt;
} Pt_c534_01E027F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_c534_01E027F0 color;
    f32 size;
    u8 pad10[0x10];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad28[8];
    Pt_c534_01E027F0 pt[16];
    s16 n;
} Mark_c534_01E027F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c534_01E027F0;

static inline void uv_c534_01E027F0(Pkt_c534_01E027F0 *p, Mark_c534_01E027F0 *m) {
    ((Uv_c534_01E027F0 *)&p->v[0].uv)->u = m->u << 4;
    ((Uv_c534_01E027F0 *)&p->v[0].uv)->v = m->v << 4;
    ((Uv_c534_01E027F0 *)&p->v[1].uv)->u = (m->u + m->w - 1) << 4;
    ((Uv_c534_01E027F0 *)&p->v[1].uv)->v = m->v << 4;
    ((Uv_c534_01E027F0 *)&p->v[2].uv)->u = m->u << 4;
    ((Uv_c534_01E027F0 *)&p->v[2].uv)->v = (m->v + m->h - 1) << 4;
    ((Uv_c534_01E027F0 *)&p->v[3].uv)->u = (m->u + m->w - 1) << 4;
    ((Uv_c534_01E027F0 *)&p->v[3].uv)->v = (m->v + m->h - 1) << 4;
}

static s32 func_01E027F0_c534(s32 obj __attribute__((aligned(8))), Cam_c534_01E027F0 *cam, Mark_c534_01E027F0 *m) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00103390(void *, f32, f32);
    extern void func_01E00100_c534();
    f32 depth[4];
    Vec4f p;
    Pkt_c534_01E027F0 pkt;
    s32 i;

    ((Pkt_c534_01E027F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(m->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(m->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_c534(&pkt, &m->color);
    ((Pkt_c534_01E027F0 *)(s32)&pkt)->count |= 0x800;
    uv_c534_01E027F0(&pkt, m);
    for (i = 0; i < m->n; i++) {
        p.x = m->pt[i].x - m->size;
        p.y = m->pt[i].y + m->size;
        p.z = m->pt[i].z;
        if (func_00205440(&p, cam->view, &pkt.v[0].uv + 1, &depth[0]) != 0) {
            m->flags |= 0x100000;
        }
        p.x = m->pt[i].x + m->size;
        p.y = m->pt[i].y + m->size;
        if (func_00205440(&p, cam->view, &pkt.v[1].uv + 1, &depth[1]) != 0) {
            m->flags |= 0x200000;
        }
        p.x = m->pt[i].x - m->size;
        p.y = m->pt[i].y - m->size;
        if (func_00205440(&p, cam->view, &pkt.v[2].uv + 1, &depth[2]) != 0) {
            m->flags |= 0x400000;
        }
        p.x = m->pt[i].x + m->size;
        p.y = m->pt[i].y - m->size;
        if (func_00205440(&p, cam->view, &pkt.v[3].uv + 1, &depth[3]) != 0) {
            m->flags |= 0x800000;
        }
        if (func_00104520(m->flags, 0x18) != 0) {
            func_00208700(&pkt, m->texture, 0);
        } else {
            if (func_00104520(m->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)m->u << 4) | ((u64)(m->u + m->w - 1) << 14) |
                                        ((u64)m->v << 24) | ((u64)(m->v + m->h - 1) << 34));
            }
            func_00208700(&pkt, m->texture, 1);
        }
        if (func_00104520(m->flags, 0x14) != 0 && func_00104520(m->flags, 0x15) != 0 &&
            func_00104520(m->flags, 0x16) != 0 && func_00104520(m->flags, 0x17) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, obj, 0);
        }
        m->flags &= 0xFF0FFFFF;
        if (m->pt[i].cnt == 9999) {
            m->pt[i].x = -m->size * (m->n - 1) + m->size * (i * 2);
            m->pt[i].y = -15.0f;
            m->pt[i].z = 120.0f;
        } else if (func_00103390(&m->pt[i].z, 600.0f, 150.0f) == 0) {
            m->pt[i].cnt = 9999;
        } else {
            m->pt[i].cnt++;
        }
    }
    return 0;
}

/* shape b000:01E04EC0, 148 insns, 12 copies: seed n points with random positions: flag 0x1D set and v < 0:
   +-50 / +-50 / 0..50, flag set and v >= 0: +-240 / +-240 / 240..480, flag clear: tenths of +-240 / 0..240 */

typedef struct Pt_b000_01E04EC0 {
    f32 x, y, z, w;
} Pt_b000_01E04EC0;

typedef struct Obj_b000_01E04EC0 {
    s32 flags;
    u8 pad4[4];
    f32 f8;
    s32 count;
    Pt_b000_01E04EC0 pts[1];
} Obj_b000_01E04EC0;

static s32 func_01E02E30_c534(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
    extern f32 func_001A6970(f32);
    extern s32 func_0019A5C8();
    s32 i;

    o->f8 = func_001A6970(v);
    o->count = n;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (v < 0.0f) {
                o->pts[i].x = func_0019A5C8() % 100 - 50;
                o->pts[i].y = func_0019A5C8() % 100 - 50;
                o->pts[i].z = func_0019A5C8() % 50;
            } else {
                o->pts[i].x = func_0019A5C8() % 480 - 240;
                o->pts[i].y = func_0019A5C8() % 480 - 240;
                o->pts[i].z = func_0019A5C8() % 240 + 240;
            }
        } else {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
    }
    return 0;
}

/* shape b000:01E05110, 344 insns, 12 copies: draws falling streaks (rain/snow): each point is drawn as a line
   from it along its normalised direction, then moved; points that fall past the floor are reseeded (the two
   ranges of b000:01E04EC0); drawn twice with flag 0x1C. Calls the module's line colour helper (b000:01E00080),
   included above as a static function. */

typedef struct Pt_b000_01E05110 {
    f32 x, y, z, w;
} Pt_b000_01E05110;

typedef struct Obj_b000_01E05110 {
    s32 flags;
    Src_b000_01E00080 color;
    f32 len;
    s32 count;
    Pt_b000_01E05110 pts[1];
} Obj_b000_01E05110;

typedef struct Cam_b000_01E05110 {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E05110;

typedef struct LPk_b000_01E05110 {
    s16 size;
    s16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b000_01E00080 v[2];
} LPk_b000_01E05110;

static s32 func_01E03080_c534(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020D070();
    extern s32 func_0019A5C8();
    Vec4f a;
    Vec4f b;
    LPk_b000_01E05110 pk;
    f32 depth[2];
    s32 i;

    ((LPk_b000_01E05110 *)(s32)&pk)->flags = 0x11;
    ((LPk_b000_01E05110 *)(s32)&pk)->size = 4;
    ((LPk_b000_01E05110 *)(s32)&pk)->regs = 0x4141;
    ((LPk_b000_01E05110 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < o->count; i++) {
        if (!(v < 0.0f)) {
            func_01E00080_c534((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_c534((Pk_b000_01E00080 *)&pk, &o->color, 1);
        }
        a.x = b.x = o->pts[i].x;
        a.y = b.y = o->pts[i].y;
        a.z = b.z = o->pts[i].z;
        if (func_00205440(&a, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        func_0020D070(&a);
        b.x += a.x * o->len;
        b.y += a.y * o->len;
        b.z += a.z * o->len;
        if (func_00205440(&b, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        o->pts[i].x -= a.x * v;
        o->pts[i].y -= a.y * v;
        o->pts[i].z -= a.z * v;
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (!(o->pts[i].z < 300.0f)) {
                o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].y = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].z = 0.1f * (func_0019A5C8() % 240);
            }
        } else if (o->pts[i].y <= 0.0f) {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, 0);
                }
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                }
            }
        }
        o->flags &= 0xFF0FFFFF;
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

static s32 func_01E035E0_c534(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E04D00_c534;
    Tbl_b000_01E032C0 tbl = D_01E04D00_c534;
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

static s32 func_01E03740_c534(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00100_c534((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* shape c534:01E03D50 (c534), 913 insns, 1 copy: c534 scene manager (c508:01E04B50's skeleton): code >= 0 sets up a
   row of n level marks (n = code, 1..12 random above 12, negated for the second player), two spark sprays with
   falling streaks, the light sprite, three rings, the outline model and the LP number (green gain / red loss); else
   draws them, respawns each spray every 15 frames, fades in to 10 and out from 81, and flags the number digits once
   their marks have landed */

typedef struct {
    u8 b, g, r, a;
} Col_c534_01E03D50;

typedef struct {
    f32 x, y, z;
    u8 padC[0x64];
} Cam_c534_01E03D50;

typedef struct {
    f32 x, y, z;
} Sp_c534_01E03D50;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c534_01E03D50 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Sp_c534_01E03D50 pts[60];
} Spark_c534_01E03D50;

typedef struct {
    s32 flags;
    Col_c534_01E03D50 color;
    f32 len;
    s32 count;
    Vec4f pts[64];
} Rain_c534_01E03D50;

typedef struct {
    s32 a, b, c, d;
} Rnd_c534_01E03D50;

typedef struct {
    s32 kind;
    s32 flags;
    Col_c534_01E03D50 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rnd_c534_01E03D50 r[64];
} Spr_c534_01E03D50;

typedef struct {
    s32 kind;
    s32 flags;
    s32 type;
    u8 padC[0x94];
} Fx_c534_01E03D50;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c534_01E03D50 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c534_01E03D50;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c534_01E03D50 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c534_01E03D50;

typedef struct {
    f32 x, y, z;
    u8 padC[2];
    s16 cnt;
} Pt_c534_01E03D50;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c534_01E03D50 color;
    f32 size;
    f32 x, y, z, w;
    s16 u, v, w2, h;
    u8 pad28[4];
    s16 h2C, h2E;
    Pt_c534_01E03D50 pt[16];
    s16 n;
    u8 pad132[4];
    s16 sx;
    s16 sy;
    s16 step;
    s16 h13C;
    u8 pad13E[2];
    s16 h140;
    u8 pad142[0xE];
} Mark_c534_01E03D50;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c534_01E03D50 color;
    s16 x, y;
    s16 uv[8];
    u8 pad20[0x20];
} Num_c534_01E03D50;

typedef struct {
    s32 x, y, z, w;
} Pos_c534_01E03D50;

typedef struct {
    Cam_c534_01E03D50 cam0;
    Cam_c534_01E03D50 cam1;
    Spark_c534_01E03D50 spark[2];
    Rain_c534_01E03D50 rain[2];
    Spr_c534_01E03D50 spr;
    Fx_c534_01E03D50 fx;
    Mdl_c534_01E03D50 mdl;
    Ring_c534_01E03D50 ring0;
    Ring_c534_01E03D50 ring1;
    Ring_c534_01E03D50 ring2;
    Mark_c534_01E03D50 mark;
    Num_c534_01E03D50 num;
    Vec4f vel;
    Pos_c534_01E03D50 pos;
    s32 timer;
    s32 code;
    s32 t;
    s32 cnt[2];
    u8 alpha;
} Scene_c534_01E03D50;

static s32 func_01E03D50_c534(s32 arg0, s32 code) {
    Scene_c534_01E03D50 *g = (Scene_c534_01E03D50 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F5380();
    extern void func_001F6CF0(u8);
    extern void func_00103890(void *);
    extern void func_00103920(void *, f32, f32);
    extern void func_00103260(s32 *, s32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103390(void *, f32, f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, u8);
    extern s32 func_0019A5C8();
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 j;
    s32 w;
    s32 m;
    s32 n;
    s32 k;
    u8 cr;
    u8 cg;
    u8 cb;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2210);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        g->timer = 0x5A;
        g->code = code;
        g->alpha = 0x80;
        g->t = 0;
        g->cnt[0] = 0;
        g->cnt[1] = 7;
        g->vel.x = 1.15f;
        g->vel.y = 1.15f;
        g->vel.z = 1.15f;
        if (code > 12) {
            code = func_0019A5C8() % 12 + 1;
        }
        if (func_001F5380() == 1) {
            code = -code;
        }
        if (code >= 0) {
            cr = 0x60;
            cg = 0xB0;
            cb = 0x70;
        } else {
            cr = 0xB0;
            cg = 0x50;
            cb = 0x60;
        }
        g->pos.x = g->pos.z = g->pos.w = 0;
        g->pos.y = -35;
        func_00103260(tx, 6);
        g->mark.tex = tx[0];
        g->mark.flags = 0x80801;
        g->mark.x = 0.0f;
        g->mark.y = 0.0f;
        g->mark.z = 0.0f;
        g->mark.w = 0.0f;
        g->mark.u = 0x60;
        g->mark.v = 0;
        g->mark.w2 = 0x20;
        g->mark.h = 0x20;
        g->mark.h2C = 0x80;
        g->mark.h2E = 0x40;
        g->mark.size = 10.0f;
        g->mark.n = code;
        g->mark.step = 5;
        g->mark.h13C = 1;
        g->mark.h140 = 1;
        g->mark.sx = 0x96;
        g->mark.sy = 0x96;
        g->mark.color.r = 0x80;
        g->mark.color.g = 0x80;
        g->mark.color.b = 0x80;
        g->mark.color.a = 0x80;
        for (k = 0; k < g->mark.n; k++) {
            g->mark.pt[k].x = g->mark.x;
            g->mark.pt[k].y = g->mark.y;
            w = g->mark.sx;
            if (w) {
                g->mark.pt[k].x = g->mark.x + (f32)(func_0019A5C8() % (w * 2) - w);
            }
            n = g->mark.sy;
            if (n) {
                g->mark.pt[k].y = g->mark.y + (f32)(func_0019A5C8() % (n * 2) - n);
            }
            g->mark.pt[k].cnt = -g->mark.step * k;
            g->mark.pt[k].z = g->mark.z + 100.0f * g->mark.pt[k].cnt - 1000.0f;
        }
        func_00103260(tx, 0xF);
        for (i = 0; i < 2; i++) {
            g->spark[i].tex = tx[0];
            g->spark[i].size = 2.0f;
            for (j = 0; j < 60; j++) {
                if (func_00104520(g->spark[i].flags, 0x1D)) {
                    g->spark[i].pts[j].x = func_0019A5C8() % 100 - 50;
                    g->spark[i].pts[j].z = func_0019A5C8() % 50;
                    g->spark[i].pts[j].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark[i].pts[j].x = func_0019A5C8() % 50 - 25;
                    g->spark[i].pts[j].y = func_0019A5C8() % 25;
                    g->spark[i].pts[j].z = func_0019A5C8() % 50 - 25;
                }
            }
            g->spark[i].flags = 0x20080001;
            g->spark[i].u = 0xB0;
            g->spark[i].v = 0x40;
            g->spark[i].w = 0x20;
            g->spark[i].h = 0x20;
            g->spark[i].color.r = 0x80;
            g->spark[i].color.g = 0xE0;
            g->spark[i].color.b = 0xA0;
            g->spark[i].color.a = 0x80;
            g->rain[i].flags = 0x60080001;
            g->rain[i].color.r = 0x80;
            g->rain[i].color.g = 0xE0;
            g->rain[i].color.b = 0xA0;
            g->rain[i].color.a = 0;
            func_01E02E30_c534(&g->rain[i], 0x40, 80.0f);
        }
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.color.r = 0x60;
        g->spr.color.g = 0xD0;
        g->spr.color.b = 0x70;
        g->spr.color.a = 0;
        func_01E035E0_c534((Obj_b000_01E032C0 *)&g->spr, tx[0], 3.0f);
        g->ring0.flags = 0x20080000;
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.color.r = 0x60;
        g->ring0.color.g = 0xD0;
        g->ring0.color.b = 0x70;
        g->ring0.color.a = 0;
        { f32 fs2 = 22.5f; f32 fs3 = 21.0f; f32 fs4 = 0.0f; f32 fs5 = 0.0f; func_01E02040_c534((Ring_b001_01E035A0 *)&g->ring0, tx[0], fs2, fs3, fs4, fs5); }
        g->ring1.flags = 0x20080000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0x60;
        g->ring1.color.g = 0xD0;
        g->ring1.color.b = 0x70;
        g->ring1.color.a = 0;
        { f32 fs3; f32 fs4; f32 fs5; fs5 = 0.0f; fs4 = 0.0f; fs3 = 24.0f; func_01E02040_c534((Ring_b001_01E035A0 *)&g->ring1, tx[0], 22.5f, fs3, fs4, fs5); }
        g->ring2.flags = 0x20080000;
        g->ring2.u = 0x8E;
        g->ring2.v = 0;
        g->ring2.w = 0x20;
        g->ring2.h = 0x80;
        g->ring2.color.r = 0x60;
        g->ring2.color.g = 0xD0;
        g->ring2.color.b = 0x70;
        g->ring2.color.a = 0;
        { extern s32 c534_01E02040(void *, s32, f32, f32, f32, f32); f32 fs2 = 240.0f; f32 fs3 = 280.0f; f32 fs5 = 0.0f; c534_01E02040(&g->ring2, tx[0], fs2, fs3, 0.0f, fs5); }
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
        g->mdl.color.r = 0x60;
        g->mdl.color.g = 0xD0;
        g->mdl.color.b = 0x70;
        g->mdl.color.a = 0;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        g->fx.type = 1;
        { f32 fs3 = 37.5f; func_01E001A0_c534((Model_b013_01E001A0 *)&g->mdl, (Fx_b013_01E001A0 *)&g->fx, tx[0], fs3); }
        g->num.flags = 0x40200;
        g->num.tex = tx[0];
        g->num.uv[0] = 0;
        g->num.uv[1] = 0;
        g->num.uv[2] = 0xA;
        g->num.uv[3] = 0x10;
        g->num.uv[4] = 0;
        g->num.uv[5] = 8;
        g->num.uv[6] = 0x100;
        g->num.uv[7] = 0x100;
        g->num.color.r = cr;
        g->num.color.g = cg;
        g->num.color.b = cb;
        g->num.color.a = 0x80;
        func_01E010C0_c534((Num_c508_01E013C0 *)&g->num, 0x1E, 0x30, code);
        if (code >= 4) {
            g->num.flags |= 0x8000;
        }
        g->cam0.x = g->cam0.y = g->cam0.z = 0.1f;
        g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        return 0;
    }
    { extern void func_00103920(void *, f32, f32); f32 fs1 = 0.0f; func_00103920(&g->cam0, fs1, 0.0f); }
    { extern void func_00103920(void *, f32, f32); f32 fs2 = 0.0f; func_00103920(&g->cam1, 0.0f, fs2); }
    func_001F6CF0(g->alpha);
    func_01E02300_c534(ot, (Ring_b001_01E03860 *)&g->ring0, (Cam_b001_01E03860 *)&g->cam0);
    func_01E02300_c534(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)&g->cam0);
    func_01E02300_c534(ot, (Ring_b001_01E03860 *)&g->ring2, (Cam_b001_01E03860 *)&g->cam1);
    func_01E004E0_c534(ot, (Model_b013_01E004E0 *)&g->mdl, (Fx_b013_01E004E0 *)&g->fx,
                       (Cam_b013_01E004E0 *)&g->cam0);
    func_01E03740_c534(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->cam0);
    if (g->t < 10) {
        func_00103470(&g->alpha, 0x20, 8);
        func_001032C0(&g->spr.color.a, 0x20, 3);
        func_001032C0(&g->ring0.color.a, 0x20, 3);
        func_001032C0(&g->ring1.color.a, 0x30, 3);
        func_001032C0(&g->mdl.color.a, 0x60, 6);
        func_001032C0(&g->ring2.color.a, 0x10, 3);
    }
    if (g->t > 4) {
        { extern s32 c534_01E03080(s32, void *, void *, f32); c534_01E03080(ot, &g->rain[0], &g->cam0, -20.0f); }
        { extern s32 c534_01E03080(s32, void *, void *, f32); f32 fs3 = -20.0f; c534_01E03080(ot, &g->rain[1], &g->cam0, fs3); }
        func_01E01A60_c534(ot, (Spark_b013_01E010C0 *)&g->spark[0], (Cam_b013_01E010C0 *)&g->cam0, (s32)&g->vel);
        func_01E01A60_c534(ot, (Spark_b013_01E010C0 *)&g->spark[1], (Cam_b013_01E010C0 *)&g->cam0, (s32)&g->vel);
        if (g->t > 10) {
            func_01E027F0_c534(ot, (Cam_c534_01E027F0 *)&g->cam0, (Mark_c534_01E027F0 *)&g->mark);
        }
        for (i = 0; i < 2; i++) {
            if (g->t < 80) {
                if (g->cnt[i] < 10) {
                    func_001032C0(&g->rain[i].color.a, 0xFF, 0x40);
                    func_001032C0(&g->spark[i].color.a, 0xFF, 0x40);
                } else {
                    func_00103470(&g->rain[i].color.a, 0, 0x20);
                    func_00103470(&g->spark[i].color.a, 0, 0x20);
                }
            }
            if (g->cnt[i] > 14) {
                g->cnt[i] = 0;
                g->rain[i].color.a = 0;
                g->spark[i].color.a = 0;
                { extern s32 c534_01E02E30(void *, s32, f32); c534_01E02E30(&g->rain[i], 0x40, 80.0f); }
                g->spark[i].size = 2.0f;
                for (m = 0; m < 60; m++) {
                    if (func_00104520(g->spark[i].flags, 0x1D)) {
                        g->spark[i].pts[m].x = func_0019A5C8() % 100 - 50;
                        g->spark[i].pts[m].z = func_0019A5C8() % 50;
                        g->spark[i].pts[m].y = func_0019A5C8() % 100 - 50;
                    } else {
                        g->spark[i].pts[m].x = func_0019A5C8() % 50 - 25;
                        g->spark[i].pts[m].y = func_0019A5C8() % 25;
                        g->spark[i].pts[m].z = func_0019A5C8() % 50 - 25;
                    }
                }
            }
        }
        g->cnt[0]++;
        g->cnt[1]++;
    }
    if (g->t > 80) {
        func_001032C0(&g->alpha, 0x80, 8);
        func_00103470(&g->spr.color.a, 0, 0x10);
        func_00103470(&g->ring0.color.a, 0, 0x10);
        func_00103470(&g->ring1.color.a, 0, 0x10);
        func_00103470(&g->ring2.color.a, 0, 0x10);
        func_00103470(&g->mdl.color.a, 0, 0x10);
        func_00103470(&g->mark.color.a, 0, 0x10);
        func_00103470(&g->num.color.a, 0, 0x10);
        for (k = 0; k < 2; k++) {
            func_00103470(&g->rain[k].color.a, 0, 0x20);
            func_00103470(&g->spark[k].color.a, 0, 0x20);
        }
    }
    if (func_00104520(g->num.flags, 0xF)) {
        if (g->mark.n < 10) {
            if (g->mark.pt[g->mark.n - 2].cnt == 9999) {
                g->num.flags |= 0x400;
            }
            if (g->mark.pt[g->mark.n - 1].cnt == 9999) {
                g->num.flags |= 0x800;
            }
        } else {
            if (g->mark.pt[g->mark.n - 3].cnt == 9999) {
                g->num.flags |= 0x400;
            }
            if (g->mark.pt[g->mark.n - 2].cnt == 9999) {
                g->num.flags |= 0x800;
            }
            if (g->mark.pt[g->mark.n - 1].cnt == 9999) {
                g->num.flags |= 0x1000;
            }
        }
    }
    if (g->t > 30) {
        func_01E012C0_c534(ot, (Num_c508_01E015C0 *)&g->num, (Pos_c508_01E015C0 *)&g->pos);
    }
    { extern s32 func_00103390(void *, f32, f32); f32 fs1; f32 fs2; fs2 = 0.4f; fs1 = 1.0f; func_00103390(&g->cam0.x, fs1, fs2); }
    func_00103390(&g->cam0.y, 1.0f, 0.4f);
    func_00103390(&g->cam0.z, 1.0f, 0.4f);
    if (func_00103390(&g->cam1.x, 1.2f, 0.1f) == 0) {
        g->cam1.x = 0.1f;
    }
    if (func_00103390(&g->cam1.y, 1.2f, 0.1f) == 0) {
        g->cam1.y = 0.1f;
    }
    if (func_00103390(&g->cam1.z, 1.2f, 0.1f) == 0) {
        g->cam1.z = 0.1f;
    }
    for (i = 0; i < 64; i++) {
        g->spr.r[i].a += 0x80;
        g->spr.r[i].b += 0x80;
        g->spr.r[i].c += 0x80;
    }
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
