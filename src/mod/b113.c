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

static void func_01E00080_b113(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b113(s32 arg0, Src_b000_01E00400 *c) {
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
typedef struct W_ta_func_01E00280_b113 {
    Vec4f v[8];
} W_ta_func_01E00280_b113;

typedef struct W_tb_func_01E00280_b113 {
    Vec4f v[8];
} W_tb_func_01E00280_b113;

static s32 func_01E00280_b113(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00280_b113 D_01E04880_b113;
            W_ta_func_01E00280_b113 ta_w = D_01E04880_b113;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00280_b113 D_01E04900_b113;
            W_tb_func_01E00280_b113 tb_w = D_01E04900_b113;

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

static s32 func_01E005C0_b113(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00080_b113((Vtx_b000_01E00100 *)&pk, &m->col);
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

extern void b113_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E011A0_b113(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    b113_01E00080(&pkt, &sp->color);
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

static s32 func_01E01780_b113(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

/* shape b000:01E01140, 1595 insns, 70 copies: draws an emitter's particles. Each particle is either a camera-facing
   sprite (strip packet, 9 regs) sized by distance, or with flag 0x1F a quad (12 regs) turned by its own rotation;
   UV or ST frames animate per particle; flag 2 respawns a particle on a circle when its animation wraps.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E01140;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E01140;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E01140;

typedef union {
    UV_b000_01E01140 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b000_01E01140;

typedef struct {
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx1_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx1_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt1_b000_01E01140;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx2_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx2_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt2_b000_01E01140;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b000_01E01140;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E01140 color;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    union {
        struct {
            s16 u, v, w, h;
            s16 u0, v0, tw, th;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Pt_b000_01E01140 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b000_01E01140;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E01140;

#define UV1(k) ((UV_b000_01E01140 *)(s32)&p1.v[k].tc)
#define UV2(k) ((UV_b000_01E01140 *)(s32)&p2.v[k].tc)

static s32 func_01E01CE0_b113(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
    extern s32 func_002058D0(void *, s32, void *, void *, f32 *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f c[4];
    Vec4f off;
    Vec4f tmp;
    Vec4f pos;
    Pkt1_b000_01E01140 p1 __attribute__((aligned(8)));
    Pkt2_b000_01E01140 p2 __attribute__((aligned(8)));
    f32 nx;
    f32 ny;
    f32 sx;
    f32 sy;
    s32 i;
    f32 hx;
    f32 hy;
    f32 dz;
    s32 a;

    ((Pkt1_b000_01E01140 *)(s32)&p1)->count = 0x24;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->tag = 9;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->pad = 0;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->count = 0x34;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->tag = 0xC;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (e->r.i.w == e->r.i.h) {
        sy = e->size;
        sx = sy;
    } else if (e->r.i.h < e->r.i.w) {
        sx = e->size;
        sy = sx * ((f32)e->r.i.h / (f32)e->r.i.w);
    } else {
        sy = e->size;
        sx = sy * ((f32)e->r.i.w / (f32)e->r.i.h);
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x44);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x88);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x42);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x48);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x48);
    }
    p1.r = e->color.r;
    p1.g = e->color.g;
    p1.b = e->color.b;
    *(u8 *)(s32)&p1.a = e->color.a;
    p1.q = 1.0f;
    func_01E00080_b113((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
            ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
            UV2(0)->u = e->r.i.u * 16;
            UV2(0)->v = e->r.i.v * 16;
            UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(1)->v = e->r.i.v * 16;
            UV2(2)->u = e->r.i.u * 16;
            UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
        } else {
            p1.v[0].tc.st.s = e->r.f.s;
            p1.v[0].tc.st.t = e->r.f.t;
            p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[1].tc.st.t = e->r.f.t;
            p1.v[2].tc.st.s = e->r.f.s;
            p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[0].tc.st.s = e->r.f.s;
            p2.v[0].tc.st.t = e->r.f.t;
            p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[1].tc.st.t = e->r.f.t;
            p2.v[2].tc.st.s = e->r.f.s;
            p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
        }
    }
    if (func_00104520(e->flags, 0x1C) != 0) {
        func_0020C630(m, &e->rot);
        for (i = 0; i < e->count; i++) {
            tmp.x = e->pts[i].x;
            tmp.y = e->pts[i].y;
            tmp.z = e->pts[i].z;
            func_0020CDD0(&off, m, &tmp);
            e->pts[i].x = off.x;
            e->pts[i].y = off.y;
            e->pts[i].z = off.z;
        }
    }
    nx = -sx;
    ny = -sy;
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->color.a;
        }
        if (func_00104520(e->flags, 3) == 0) {
            if (func_00104520(e->flags, 0) != 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame % (e->r.i.tw / e->r.i.w));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame / (e->r.i.tw / e->r.i.w));
                } else {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame / (e->r.i.th / e->r.i.h));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame % (e->r.i.th / e->r.i.h));
                }
                ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
                ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
                UV2(0)->u = e->r.i.u * 16;
                UV2(0)->v = e->r.i.v * 16;
                UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(1)->v = e->r.i.v * 16;
                UV2(2)->u = e->r.i.u * 16;
                UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                p1.v[0].tc.st.s = e->r.f.s;
                p1.v[0].tc.st.t = e->r.f.t;
                p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[1].tc.st.t = e->r.f.t;
                p1.v[2].tc.st.s = e->r.f.s;
                p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[0].tc.st.s = e->r.f.s;
                p2.v[0].tc.st.t = e->r.f.t;
                p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[1].tc.st.t = e->r.f.t;
                p2.v[2].tc.st.s = e->r.f.s;
                p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&p1, e->texture, 0);
            func_00208700(&p2, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&p1, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
                func_00208CB0(&p2, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&p1, e->texture, 1);
            func_00208700(&p2, e->texture, 1);
        }
        pos.x = e->pts[i].x;
        pos.y = e->pts[i].y;
        pos.z = e->pts[i].z;
        if (func_00104520(e->flags, 0x1A) != 0) {
            dz = -(e->amp * func_0020B550(e->freq * e->pts[i].t));
            pos.z += dz;
        }
        if (func_00104520(e->flags, 0x1F) != 0) {
            func_0020C630(m, &e->rots[i]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx = sx + sx * e->grow * e->pts[i].t;
                hy = sy + sy * e->grow * e->pts[i].t;
                off.x = -hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = -hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            } else {
                off.x = nx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = nx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            }
        } else {
            if (func_00205440(&pos, cam->view, &p1.v[0].xyz, depth) != 0 && func_00101600(&p1.v[0].xyz) != 0) {
                e->flags |= 0xF00000;
            }
            depth[1] = depth[2] = depth[3] = depth[0];
            hx = 20.0f * func_001018E0(sx, depth[0]);
            hy = 20.0f * func_001018E0(sy, depth[0]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx += sx * e->grow * e->pts[i].t;
                hy += sy * e->grow * e->pts[i].t;
            }
            p1.v[1].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[1].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[2].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[2].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[3].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[3].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[0].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[0].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = p1.v[0].xyz.z;
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
                func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
                if (func_00104520(e->flags, 0x13) != 0) {
                    p1.v[0].xyz.z = p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = 0xFFFFFF;
                    if (e->pts[i].t >= 0) {
                        func_002075F0(&p1, obj, 0);
                    }
                } else if (e->pts[i].t >= 0) {
                    func_002075F0(&p1, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
            e->flags &= 0xFF0FFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
                    if (func_00104520(e->flags, 2) != 0) {
                        if (func_00104520(e->flags, 0x1D) != 0) {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = e->radius * func_0020B550(a);
                            e->pts[i].z = func_0019A5C8() % 20;
                            e->pts[i].x = e->radius * func_0020B480(a);
                        } else {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = func_0019A5C8() % 20;
                            e->pts[i].z = e->radius * func_0020B480(a);
                            e->pts[i].x = e->radius * func_0020B550(a);
                        }
                    }
                }
            }
        }
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

static s32 func_01E035D0_b113(s32 ot __attribute__((aligned(8))), Bolt_b021_01E03460 *b, Cam_b021_01E03460 *cam, Vec4f *p1, Vec4f *p2) {
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
    func_01E00080_b113((Vtx_b000_01E00100 *)&pkt, &b->color);
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

/* shape b113:01E03F50 (b113), 577 insns, 1 copy: the b113 module main in b049:01E032E0 form: on start clears the
   0x1000 scene (timer 220), three cameras, two joints, a 128-point emitter, a 60-point spark, a disc, a model and
   eight bolts; each tick follows the joints until tick 159 (then eases the camera), draws the flash from tick 174,
   sparks from 175, emitter/disc/model/bolts from 25, fades out when the ease ends; 3 at tick 190, 1 at 164, 6 in
   174..189, 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_b113_01E03F50;

typedef struct {
    f32 x, y, z;
    u8 padC[0x14];
    f32 pos[4];
    u8 pad30[0x40];
} Cam_b113_01E03F50;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b113_01E03F50 color;
    s16 h7C, h7E;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 f90;
    f32 f94;
    s16 h98;
    u8 pad2A[6];
} Bolt_b113_01E03F50;

typedef struct {
    s32 flags;
    Col_b113_01E03F50 color;
    f32 size;
    s16 h26C;
    s16 h26E;
} Disc_b113_01E03F50;

typedef struct {
    s32 kind;
    s32 flags;
    s32 type;
    u8 padC[0x94];
} Fx_b113_01E03F50;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_b113_01E03F50 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_b113_01E03F50;

typedef struct {
    f32 f0, f4, f8, fC;
    f32 pos[4];
    f32 f20, f24, f28;
    u8 pad2C[4];
} Snd_b113_01E03F50;

typedef struct {
    f32 x, y, z;
    u8 c, d;
    s16 h;
} Pt_b113_01E03F50;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b113_01E03F50 color;
    f32 size;
    u8 pad10[0x10];
    s32 k[3];
    u8 pad2C[4];
    s16 s[8];
    Pt_b113_01E03F50 *pts;
    s32 w44;
    s32 w48;
    f32 len;
    u8 pad50[0xA];
    s16 count;
    s16 h5C;
    s16 h5E;
    Pt_b113_01E03F50 p[128];
} Emit_b113_01E03F50;

typedef struct {
    f32 x, y, z;
} Xyz_b113_01E03F50;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b113_01E03F50 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Xyz_b113_01E03F50 pts[60];
} Spark_b113_01E03F50;

typedef struct {
    Cam_b113_01E03F50 cam0;
    Bolt_b113_01E03F50 bolt[8];
    Cam_b113_01E03F50 cam1;
    Disc_b113_01E03F50 disc;
    Fx_b113_01E03F50 fx;
    Mdl_b113_01E03F50 mdl;
    Snd_b113_01E03F50 snd;
    Emit_b113_01E03F50 emit;
    Cam_b113_01E03F50 cam2;
    Spark_b113_01E03F50 spark;
    Vec4f dir[8];
    s32 timer;
    s32 t;
    s32 code;
    s32 cnt;
    s32 j[2];
    Col_b113_01E03F50 col;
    u8 padFFC[4];
} Scene_b113_01E03F50;

static s32 func_01E03F50_b113(s32 arg0, s32 code) {
    Scene_b113_01E03F50 *g = (Scene_b113_01E03F50 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103290(void *, s32);
    extern void func_00103260(void *, s32);
    extern s32 func_001043F0(void *, f32);
    extern void func_001039A0(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103660(void *, void *);
    extern void func_00103620(void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_001032C0(void *, s32, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_001033D0(void *, f32, f32);
    extern void func_00103390(void *, f32, f32);
    extern void func_001F6C10();
    extern s32 b113_01E00280(void *, void *, s32, f32);
    extern s32 func_01E00120_b113();
    extern s32 func_01E005C0_b113();
    extern s32 func_01E011A0_b113();
    extern s32 func_01E01780_b113();
    extern s32 func_01E01CE0_b113();
    extern s32 func_01E035D0_b113();
    Vec4f vel;
    Vec4f tmp;
    Vec4f v[2];
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 k;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1000);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        g->j[0] = func_001F5560(func_001F53A0(), 0x12, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->timer = 220;
        g->t = 1;
        g->code = code;
        g->cnt = 16;
        g->col.g = 0x80;
        g->col.r = 0x80;
        g->col.b = 0xE0;
        g->col.a = 0;
        func_00103290(&tex, 1);
        g->emit.texture = tex;
        g->emit.flags = 0x70000003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x80;
        g->emit.size = 0.5f;
        g->emit.k[0] = 0x800;
        g->emit.k[1] = 0x800;
        g->emit.k[2] = 0x800;
        g->emit.s[0] = 0;
        g->emit.s[1] = 0;
        g->emit.s[2] = 0x20;
        g->emit.s[3] = 0x20;
        g->emit.s[4] = 0;
        g->emit.s[5] = 0;
        g->emit.s[6] = 0x80;
        g->emit.s[7] = 0x40;
        g->emit.pts = g->emit.p;
        g->emit.w44 = 0;
        g->emit.w48 = 0;
        g->emit.len = 15.0f;
        g->emit.count = 0x80;
        g->emit.h5C = 8;
        g->emit.h5E = 0;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&tmp, 4.0f);
            g->emit.p[i].x = tmp.x;
            g->emit.p[i].y = tmp.y;
            g->emit.p[i].z = tmp.z;
            g->emit.p[i].h = -(func_0019A5C8() % 12);
            g->emit.p[i].c = 0x30;
            g->emit.p[i].d = 0;
        }
        func_00103260(&tex, 0xF);
        g->spark.texture = tex;
        g->spark.flags = 0x20080001;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.size = 0.5f;
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
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x80;
        g->spark.color.b = 0xE0;
        g->spark.color.a = 0x80;
        g->disc.flags = 0;
        g->disc.color.r = 0x80;
        g->disc.color.g = 0x80;
        g->disc.color.b = 0xE0;
        g->disc.color.a = 0;
        g->disc.size = 5.0f;
        g->disc.h26C = 0x24;
        g->disc.h26E = 0;
        g->mdl.flags = 0x401;
        g->mdl.r[0] = 0xB0;
        g->mdl.r[1] = 0x20;
        g->mdl.r[2] = 0x20;
        g->mdl.r[3] = 0x20;
        g->mdl.r[4] = 0xB0;
        g->mdl.r[5] = 0x20;
        g->mdl.r[6] = 0x100;
        g->mdl.r[7] = 0x100;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0x80;
        g->mdl.color.g = 0x80;
        g->mdl.color.b = 0xE0;
        g->mdl.color.a = 0;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        g->fx.type = 1;
        b113_01E00280(&g->mdl, &g->fx, tex, 8.0f);
        g->snd.f4 = 0.5f;
        g->snd.f8 = 0.75f;
        g->snd.fC = 1.0f;
        g->snd.f0 = 1.0f;
        g->snd.f20 = 0.0f;
        g->snd.f24 = 40.0f;
        g->snd.f28 = 0.0f;
        func_00103290(&tex, 0);
        for (i = 0; i < 8; i++) {
            g->bolt[i].texture = tex;
            g->bolt[i].flags = 0;
            g->bolt[i].u = 0x80;
            g->bolt[i].v = 0x40;
            g->bolt[i].w = 0x20;
            g->bolt[i].h = 0x40;
            g->bolt[i].color.r = 0x80;
            g->bolt[i].color.g = 0x80;
            g->bolt[i].color.b = 0x80;
            g->bolt[i].color.a = 0x40;
            g->bolt[i].h7C = 0x10;
            g->bolt[i].h98 = -(i + 1);
            g->bolt[i].h7E = 0x14;
            g->bolt[i].f90 = 0.0f;
            g->bolt[i].f94 = 0.0f;
            func_001043F0(&g->dir[i], 6.0f);
        }
        g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        g->cam2.x = g->cam2.y = g->cam2.z = 0.1f;
        return 0;
    }
    func_001F5F90(func_001F5380(), g->cam2.pos);
    if (g->t < 159) {
        func_001F5620(func_001F53A0(), g->j[0], g->cam1.pos);
        func_001F5620(func_001F53A0(), g->j[0], &v[0]);
        func_001F5620(func_001F53A0(), g->j[1], &v[1]);
        func_00103660(&v[0], &v[1]);
        func_00103620(g->cam1.pos, &v[0]);
    } else {
        func_00104490(g->cam1.pos, g->cam2.pos, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
        }
    }
    g->snd.pos[0] = g->cam1.pos[0];
    g->snd.pos[1] = g->cam1.pos[1];
    g->snd.pos[2] = g->cam1.pos[2];
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    if (g->t >= 174) {
        func_01E00120_b113(ot, &g->col);
        if (g->t < 190) {
            func_001032C0(&g->col.a, 0xFF, 0x10);
        } else {
            func_00103470(&g->col.a, 0, 0x20);
        }
    }
    if (g->t > 174) {
        if (g->cam2.x < 0.5f) {
            g->cam2.x = g->cam2.y = g->cam2.z += 0.2f;
        }
        vel.x = vel.y = vel.z = 1.05f;
        func_01E011A0_b113(ot, &g->spark, &g->cam2, &vel);
        func_00103470(&g->spark.color.a, 0, 8);
    }
    if (g->t > 24) {
        if (g->t < 190) {
            func_01E01CE0_b113(ot, &g->emit, &g->cam1);
        }
        func_01E01780_b113(ot, &g->disc, &g->cam1);
        func_01E005C0_b113(ot, &g->mdl, &g->fx, &g->cam1);
        if (g->t < 190) {
            func_001F6C10(&g->snd);
        }
        if (g->t < 100) {
            {
                f32 r = 1.0f;
                func_001033D0(&g->cam1, r, 0.05f);
            }
            func_001032C0(&g->mdl.color.a, 0x80, 0x10);
            func_001032C0(&g->disc.color.a, 0xFF, 0x20);
            func_00103390(&g->snd.f28, 20.0f, 2.0f);
        }
        vel.x = vel.y = vel.z = 0.0f;
        for (i = 0; i < 8; i++) {
            func_01E035D0_b113(ot, &g->bolt[i], &g->cam1, &vel, &g->dir[i]);
            if (g->bolt[i].h98 == 0) {
                func_001043F0(&g->dir[i], 6.0f);
            }
        }
    }
    if (g->cnt == 0) {
        func_001033D0(&g->cam1, 10.0f, 1.0f);
        func_00103470(&g->mdl.color.a, 0, 8);
        func_00103470(&g->disc.color.a, 0, 0x10);
        for (i = 0; i < 8; i++) {
            func_00103470(&g->bolt[i].color.a, 0, 4);
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 190) {
        func_001F6C10(0);
        return 3;
    }
    if (g->t == 164) {
        return 1;
    }
    if (g->t >= 174 && g->t < 190) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
