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

static void func_01E00080_c533(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

extern Six_c500_01E003D0 D_01E03980_c533;

static s32 func_01E00120_c533(Src_c500_01E003D0 *o, Bb_c500_01E003D0 *out, s32 id, f32 size) {
    Six_c500_01E003D0 q;
    f32 sx;
    f32 sy;
    f32 half;
    s32 i;

    q = D_01E03980_c533;
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

extern void c533_01E00080(void *, void *);

static s32 func_01E00380_c533(s32 ot, Obj_c500_01E00630 *o, Strip_c500_01E00630 *s, Cam_c500_01E00630 *cam) {
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
    c533_01E00080(&pkt, o->color);
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
typedef struct W_ta_func_01E00AD0_c533 {
    Vec4f v[8];
} W_ta_func_01E00AD0_c533;

typedef struct W_tb_func_01E00AD0_c533 {
    Vec4f v[8];
} W_tb_func_01E00AD0_c533;

static s32 func_01E00AD0_c533(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00AD0_c533 D_01E039E0_c533;
            W_ta_func_01E00AD0_c533 ta_w = D_01E039E0_c533;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00AD0_c533 D_01E03A60_c533;
            W_tb_func_01E00AD0_c533 tb_w = D_01E03A60_c533;

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

static s32 func_01E00E10_c533(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00080_c533((Vtx_b000_01E00100 *)&pk, &m->col);
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

static s32 func_01E019F0_c533(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c533) and needs that helper
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

static s32 func_01E01CB0_c533(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c533(&pkt, &ring->color);
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

/* shape c518:01E02910, 108 insns: lay out a 10 x 6 grid of points from the module's x and y tables, scaled by
   the given size (x mirrored when flip is set); each point gets a random variant 0..7 and a random value 0..4;
   func_0019A5B0 is called with the point's index first */

typedef struct {
    f32 x[10];
} Xs_c518_01E02910;

typedef struct {
    f32 y[6];
} Ys_c518_01E02910;

typedef struct {
    f32 x, y;
    u8 pad8[4];
    u8 b;
    u8 kind;
    s16 v;
} Pt_c518_01E02910;

typedef struct {
    u8 pad0[0xC];
    f32 scale;
    u8 pad10[0x10];
    Pt_c518_01E02910 p[60];
    u8 pad3E0[0xA];
    s16 f3EA;
} Grid_c518_01E02910;

extern Xs_c518_01E02910 D_01E03AE0_c533;
extern Ys_c518_01E02910 D_01E03B10_c533;

static s32 func_01E021A0_c533(Grid_c518_01E02910 *o, s32 flip, f32 scale) {
    extern void func_0019A5B0(s32);
    Xs_c518_01E02910 xs;
    Ys_c518_01E02910 ys;
    s32 k;
    s32 j;
    s32 i;

    xs = D_01E03AE0_c533;
    ys = D_01E03B10_c533;
    o->scale = scale;
    o->f3EA = 0;
    for (i = 0; i < 60;) {
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 10; k++) {
                func_0019A5B0(i);
                if (flip == 0) {
                    o->p[i].x = o->scale * xs.x[k];
                } else {
                    o->p[i].x = o->scale * xs.x[9 - k];
                }
                o->p[i].y = o->scale * ys.y[j];
                o->p[i].b = 0;
                o->p[i].kind = func_0019A5C8() % 8;
                o->p[i].v = func_0019A5C8() % 5;
                i++;
            }
        }
    }
    return 0;
}

/* shape c518:01E02AC0, 453 insns, 2 copies: draws up to 60 glyph cells as textured squares (each picks its tile from the
   atlas by its character, placed at its scaled position), visibility flagged on the object (bits 20..23); fades
   each shown cell in, then shows one more cell per frame up to 60 (the original passes the cell count, not the
   flags, to the flag test there). Colour by the module helper (shape b000:01E00100). */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_c518_01E02AC0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c518_01E02AC0 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c518_01E02AC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c518_01E02AC0 v[4];
    u8 tail[0x20];
} Pkt_c518_01E02AC0;

typedef struct {
    f32 x, y;
    u8 pad8[4];
    u8 a;
    u8 ch;
    u8 padE[2];
} Cell_c518_01E02AC0;

typedef struct {
    void *texture;
    s32 flags;
    u8 col[4];
    f32 size;
    s16 u, v, w, h;
    s16 u0, v0;
    s16 aw;
    u8 pad1E[2];
    Cell_c518_01E02AC0 cells[60];
    u8 pad3E0[0xA];
    s16 count;
} Text_c518_01E02AC0;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_c518_01E02AC0;

static s32 func_01E02350_c533(s32 ot, Text_c518_01E02AC0 *o, Cam_c518_01E02AC0 *cam, f32 scale) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 d[4];
    Vec4f p;
    Pkt_c518_01E02AC0 pkt;
    s32 i;

    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c518_01E02AC0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 60; i++) {
        func_01E00080_c533((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)o->col);
        if (func_00104520(o->flags, 0x10) == 0) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->cells[i].a;
        }
        o->u = o->u0 + o->w * (o->cells[i].ch % (o->aw / o->w));
        o->v = o->v0 + o->h * (o->cells[i].ch / (o->aw / o->w));
        ((Pkt_c518_01E02AC0 *)(s32)&pkt)->count |= 0x800;
        pkt.v[0].st.s = o->u * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[0].st)->t = o->v * 16;
        pkt.v[1].st.s = (o->u + o->w - 1) * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[1].st)->t = o->v * 16;
        pkt.v[2].st.s = o->u * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[2].st)->t = (o->v + o->h - 1) * 16;
        pkt.v[3].st.s = (o->u + o->w - 1) * 16;
        ((Uv_c518_01E02AC0 *)(s32)&pkt.v[3].st)->t = (o->v + o->h - 1) * 16;
        p.x = o->cells[i].x * scale;
        p.y = o->cells[i].y * scale;
        p.z = 10.0f;
        if (func_00205440(&p, cam->m, &pkt.v[0].st + 1, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        p.x = scale * (o->cells[i].x + o->size);
        p.y = o->cells[i].y * scale;
        if (func_00205440(&p, cam->m, &pkt.v[1].st + 1, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        p.x = o->cells[i].x * scale;
        p.y = scale * (o->cells[i].y - o->size);
        if (func_00205440(&p, cam->m, &pkt.v[2].st + 1, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        p.x = scale * (o->cells[i].x + o->size);
        p.y = scale * (o->cells[i].y - o->size);
        if (func_00205440(&p, cam->m, &pkt.v[3].st + 1, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00208700(&pkt, o->texture, 0);
        } else {
            func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)o->u << 4) | 0xA | ((u64)(o->u + o->w - 1) << 14)) |
                                    ((u64)(o->v + o->h - 1) << 34));
            func_00208700(&pkt, o->texture, 1);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    for (i = 0; i < o->count; i++) {
        if (o->cells[i].a < 0x80) {
            o->cells[i].a += 0x20;
        } else {
            o->cells[i].a = 0x80;
        }
    }
    if (func_00104520(o->count, 0x10) == 0) {
        if (o->count < 60) {
            o->count++;
        } else {
            o->count = 60;
            o->flags |= 0x10000;
        }
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

static s32 func_01E02A70_c533(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E03B30_c533;
    Tbl_b000_01E032C0 tbl = D_01E03B30_c533;
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

static s32 func_01E02BD0_c533(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_c533((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* shape c533:01E031E0 (c533), 476 insns, 1 copy: the c533 module main: on start clears the 0x1430 scene (wait 120,
   timer 93), a back outline (scale 60), a dual board (texture 4, size 280), a text grid (texture 3, scale 4.8), a
   light sprite (scale 20), two rings (160/155 and 160/170) and an outline (scale 260 through an inline setter), scale
   0.1; each tick fades the back in, then draws text, rings, outline and sprite, growing by 0.2 up to 1 then by 0.005
   while fading; after flag 1 the back and board fade; 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_c533_01E031E0;

typedef struct {
    s32 a, b, c, d;
} Rnd_c533_01E031E0;

typedef struct {
    s32 kind;
    s32 flags;
    Col_c533_01E031E0 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rnd_c533_01E031E0 r[64];
} Spr_c533_01E031E0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c533_01E031E0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c533_01E031E0;

typedef struct {
    s32 kind;
    s32 flags;
    s32 type;
    u8 padC[0x94];
} Fx_c533_01E031E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c533_01E031E0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c533_01E031E0;

typedef struct {
    f32 x, y;
    u8 pad8[6];
    s16 v;
} Pt_c533_01E031E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c533_01E031E0 color;
    f32 size;
    s16 u, v, w, h;
    s16 u0, v0;
    s16 aw, h1E;
    Pt_c533_01E031E0 p[60];
    s16 k0, k1, k2, k3, k4, count;
    u8 pad3EC[4];
} Text_c533_01E031E0;

typedef struct {
    f32 x, y, z;
    u8 padC[0x64];
    f32 cx, cy, cz;
    u8 pad7C[0x64];
    Mdl_c533_01E031E0 back;
    Fx_c533_01E031E0 bfx;
    Mdl_c533_01E031E0 src;
    u8 bb[0x80];
    union {
        Text_c533_01E031E0 text;
        Grid_c518_01E02910 grid;
        Text_c518_01E02AC0 tx;
    } u;
    Spr_c533_01E031E0 spr;
    Fx_c533_01E031E0 fx;
    Mdl_c533_01E031E0 mdl;
    Ring_c533_01E031E0 ring0;
    Ring_c533_01E031E0 ring1;
    s32 wait;
    s32 timer;
    s32 code;
    s32 flags;
    u8 a;
    u8 pad1421[0xF];
} Scene_c533_01E031E0;

static inline void Set_c533_01E031E0(Mdl_c533_01E031E0 *p, Fx_c533_01E031E0 *f, s32 tex) {
    func_01E00AD0_c533((Model_b013_01E001A0 *)(s32)p, (Fx_b013_01E001A0 *)f, tex, 260.0f);
}

static s32 func_01E031E0_c533(s32 arg0, s32 code) {
    Scene_c533_01E031E0 *g = (Scene_c533_01E031E0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_00103920(void *, f32, f32);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 j;
    f32 h;
    f32 y;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1430);
        g->flags = 0;
        g->wait = 120;
        g->a = 0x80;
        g->timer = 93;
        g->code = code;
        func_00103890(g);
        func_00103890(&g->cx);
        func_00103260(&tex, 0xF);
        g->back.f30 = 1.0f;
        g->back.flags = 0x80001;
        g->back.r[0] = 0;
        g->back.r[1] = 0;
        g->back.r[2] = 0x40;
        g->back.r[3] = 0x40;
        g->back.r[4] = 0x80;
        g->back.r[5] = 0x80;
        g->back.r[6] = 0x100;
        g->back.r[7] = 0x100;
        g->back.h48 = 0;
        g->back.h4A = 1;
        g->back.h4E = 1;
        g->back.h52 = 999;
        g->back.h50 = 0;
        g->back.h4C = g->back.h4E - 1U;
        g->bfx.type = 1;
        func_01E00AD0_c533((Model_b013_01E001A0 *)(s32)&g->back, (Fx_b013_01E001A0 *)&g->bfx, tex, 60.0f);
        g->back.color.r = 0x80;
        g->back.color.r = 0x80;
        g->back.color.r = 0x80;
        g->back.color.a = 0;
        func_00103260(&tex, 4);
        g->src.f30 = 1.0f;
        g->src.flags = 0x80080001;
        g->src.r[0] = 0;
        g->src.r[1] = 0;
        g->src.r[2] = 0x80;
        g->src.r[3] = 0x40;
        g->src.r[4] = 0;
        g->src.r[5] = 0;
        g->src.r[6] = 0x80;
        g->src.r[7] = 0x40;
        g->src.h48 = 0;
        g->src.h4A = 1;
        g->src.h4E = 1;
        g->src.h52 = 999;
        g->src.h50 = 0;
        g->src.h4C = g->src.h4E - 1;
        func_01E00120_c533((Src_c500_01E003D0 *)&g->src, (Bb_c500_01E003D0 *)g->bb, tex, 280.0f);
        g->src.color.r = 0x80;
        g->src.color.g = 0x80;
        g->src.color.b = 0x80;
        g->src.color.a = 0;
        func_00103260(&tex, 3);
        g->u.text.texture = tex;
        g->u.text.flags = 0x80000;
        g->u.text.color.r = 0x80;
        g->u.text.color.g = 0x80;
        g->u.text.color.b = 0x80;
        g->u.text.color.a = 0x80;
        g->u.text.u = 0;
        g->u.text.v = 0;
        g->u.text.w = 0x10;
        g->u.text.h = 0x10;
        g->u.text.u0 = 0;
        g->u.text.v0 = 0x20;
        g->u.text.aw = 0x40;
        g->u.text.h1E = 0x40;
        g->u.text.k0 = 4;
        g->u.text.k1 = 0;
        g->u.text.k2 = 0;
        g->u.text.k3 = 0;
        g->u.text.k4 = 8;
        g->u.text.count = 0;
        func_01E021A0_c533(&g->u.grid, 0, 4.8f);
        func_00103260(&tex, 0xF);
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.color.r = 0x80;
        g->spr.color.g = 0xE0;
        g->spr.color.b = 0xE0;
        g->spr.color.a = 0x20;
        func_01E02A70_c533((Obj_b000_01E032C0 *)&g->spr, tex, 20.0f);
        g->ring0.flags = 0x20080000;
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.color.r = 0x80;
        g->ring0.color.g = 0xE0;
        g->ring0.color.b = 0xE0;
        g->ring0.color.a = 0x20;
        h = y = 0.0f;
        func_01E019F0_c533((Ring_b001_01E035A0 *)&g->ring0, tex, 160.0f, 155.0f, y, h);
        g->ring1.flags = 0x20080000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0x80;
        g->ring1.color.g = 0xE0;
        g->ring1.color.b = 0xE0;
        g->ring1.color.a = 0x20;
        h = y = 0.0f;
        func_01E019F0_c533((Ring_b001_01E035A0 *)&g->ring1, tex, 160.0f, 170.0f, h, y);
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
        g->mdl.color.r = 0x80;
        g->mdl.color.g = 0xE0;
        g->mdl.color.b = 0xE0;
        g->mdl.color.a = 0x60;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        g->fx.type = 1;
        Set_c533_01E031E0(&g->mdl, &g->fx, tex);
        g->cx = g->cy = g->cz = 0.1f;
        return 0;
    }
    h = 0.0f;
    y = 0.0f;
    func_00103920(g, y, h);
    func_00103920(&g->cx, y, h);
    if (func_00104520(g->flags, 0)) {
        func_01E02350_c533(ot, &g->u.tx, (Cam_c518_01E02AC0 *)g, 5.0f);
        if (g->u.text.count == 60) {
            func_01E01CB0_c533(ot, (Ring_b001_01E03860 *)&g->ring0, (Cam_b001_01E03860 *)&g->cx);
            func_01E01CB0_c533(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)&g->cx);
            func_01E00E10_c533(ot, (Model_b013_01E004E0 *)&g->mdl, (Fx_b013_01E004E0 *)&g->fx,
                               (Cam_b013_01E004E0 *)&g->cx);
            func_01E02BD0_c533(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->cx);
            if (g->cx <= 1.0f) {
                g->cx += 0.2f;
                g->cy += 0.2f;
                g->cz += 0.2f;
            } else {
                g->flags |= 2;
                g->cx += 0.005f;
                g->cy += 0.005f;
                g->cz += 0.005f;
                if (g->spr.color.a > 8) {
                    g->spr.color.a -= 8;
                } else {
                    g->spr.color.a = 0;
                }
                if (g->ring0.color.a > 8) {
                    g->ring0.color.a -= 8;
                } else {
                    g->ring0.color.a = 0;
                }
                if (g->ring1.color.a > 8) {
                    g->ring1.color.a -= 8;
                } else {
                    g->ring1.color.a = 0;
                }
                if (g->mdl.color.a > 10) {
                    g->mdl.color.a -= 10;
                } else {
                    g->mdl.color.a = 0;
                }
                func_001032C0(&g->a, 0x80, 8);
            }
            for (j = 0; j < 64; j++) {
                g->spr.r[j].a += 0x80;
                g->spr.r[j].b += 0x80;
                g->spr.r[j].c += 0x80;
            }
            if (func_00104520(g->flags, 1)) {
                if (g->back.color.a > 8) {
                    g->back.color.a -= 8;
                } else {
                    g->back.color.a = 0;
                }
                if (g->src.color.a > 8) {
                    g->src.color.a -= 8;
                } else {
                    g->src.color.a = 0;
                }
                if (g->u.text.color.a > 16) {
                    g->u.text.color.a -= 16;
                } else {
                    g->u.text.color.a = 0;
                }
            }
        }
    }
    func_001F6CF0(g->a);
    func_01E00E10_c533(ot, (Model_b013_01E004E0 *)&g->back, (Fx_b013_01E004E0 *)&g->bfx, (Cam_b013_01E004E0 *)g);
    func_01E00380_c533(ot, (Obj_c500_01E00630 *)&g->src, (Strip_c500_01E00630 *)g->bb, (Cam_c500_01E00630 *)g);
    if (!func_00104520(g->flags, 0)) {
        func_00103470(&g->a, 0x20, 8);
        if (g->back.color.a < 0x40) {
            g->back.color.a += 4;
        } else {
            g->back.color.a = 0x40;
            g->flags |= 1;
        }
        if (g->src.color.a < 0x80) {
            g->src.color.a += 8;
        } else {
            g->src.color.a = 0x80;
        }
    }
    if (g->wait) {
        g->wait--;
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
