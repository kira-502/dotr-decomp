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

static void func_01E00080_c600(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
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

static void func_01E00100_c600(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E001A0_c600(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
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

static s32 func_01E003B0_c600(void *arg0, s32 arg1, f32 *arg2) {
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

/* shape c536:01E00440, 164 insns, 9 copies: draw a model's afterimages: for each older transform in the history
   (newest last), a copy of the model placed there with alpha / (k + 1) (far z), then the model itself */

typedef struct Prim_c536_01E00440 {
    u8 pad0[0x10];
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u8 pad18[3];
    u8 a;
    u8 pad1C[0x14];
} Prim_c536_01E00440;

typedef struct Mdl_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    Vec4f v30;
    u8 pad40[0x38];
    Prim_c536_01E00440 *prims;
    u8 pad7C[6];
    s16 count : 12;
    s16 pad82 : 4;
    u8 pad84[0xC];
} __attribute__((aligned(16))) Mdl_c536_01E00440;

typedef struct Obj_c536_01E00440 {
    Mdl_c536_01E00440 m;
    s32 f90;
} Obj_c536_01E00440;

typedef struct Hist_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c536_01E00440;

static s32 func_01E004C0_c600(Obj_c536_01E00440 *o, s32 alpha, s32 n, Hist_c536_01E00440 *hist) {
    extern s32 func_001D9F00();
    extern void func_001DA7A0();
    extern void func_001DBCF0();
    Mdl_c536_01E00440 copy;
    s32 k;
    s32 j;
    s32 r;

    for (k = n - 1; k > 0; k--) {
        copy = o->m;
        copy.v00 = hist[k].v20;
        copy.v10 = hist[k].v10;
        copy.v30 = hist[k].v00;
        r = func_001D9F00(&copy, 1);
        for (j = 0; j < copy.count; j++) {
            copy.prims[j].z = 0xFFFFFE;
            if (alpha) {
                copy.prims[j].a = alpha / (k + 1);
            } else {
                copy.prims[j].a = 0;
            }
        }
        if (k == n - 1) {
            if (r) {
                func_001DA7A0(o->f90, o);
            } else {
                func_001DA7A0(0, o);
            }
        }
        func_001DBCF0(&copy);
    }
    func_001D9F00(o, 1);
    for (j = 0; j < o->m.count; j++) {
        o->m.prims[j].z = 0xFFFFFF;
        o->m.prims[j].a = alpha;
    }
    func_001DBCF0(o);
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

static s32 func_01E00750_c600(s32 arg0, Src_b000_01E00400 *c) {
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

extern void c600_01E00100(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E008B0_c600(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c600_01E00100(&pkt, &sp->color);
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
typedef struct W_ta_func_01E00E90_c600 {
    Vec4f v[8];
} W_ta_func_01E00E90_c600;

typedef struct W_tb_func_01E00E90_c600 {
    Vec4f v[8];
} W_tb_func_01E00E90_c600;

static s32 func_01E00E90_c600(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00E90_c600 D_01E05580_c600;
            W_ta_func_01E00E90_c600 ta_w = D_01E05580_c600;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00E90_c600 D_01E05600_c600;
            W_tb_func_01E00E90_c600 tb_w = D_01E05600_c600;

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

static s32 func_01E011D0_c600(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00100_c600((Vtx_b000_01E00100 *)&pk, &m->col);
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

static s32 func_01E01DB0_c600(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00100_c600) and needs that helper
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

static s32 func_01E02070_c600(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00100_c600(&pkt, &ring->color);
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

/* shape b127:01E02D70, 112 insns: b001:01E01B20 family: 60 points on a ring of random radius 0..19 (in x/y or x/z by flag 0x1D) plus a random 16-bit rotation triple each */


typedef struct {
    f32 x, y, z;
} V3_b127_01E02D70;

typedef struct {
    s32 a, b, c, d;
} R4_b127_01E02D70;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[4];
    f32 half;
    u8 pad10[0x20];
    R4_b127_01E02D70 rot[60];
    V3_b127_01E02D70 pts[60];
} Obj_b127_01E02D70;

static s32 func_01E02560_c600(Obj_b127_01E02D70 *o, f32 size) {
    s32 i;
    s32 ang;

    o->half = size / 2.0f;
    for (i = 0; i < 60; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].z = func_0019A5C8() % 20;
            o->pts[i].y = o->pts[i].z * func_0020B550(ang);
            o->pts[i].x = o->pts[i].z * func_0020B480(ang);
        } else {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = func_0019A5C8() % 20;
            o->pts[i].z = o->pts[i].y * func_0020B480(ang);
            o->pts[i].x = o->pts[i].y * func_0020B550(ang);
        }
        o->rot[i].a = func_0019A5C8() % 0x10000;
        o->rot[i].b = func_0019A5C8() % 0x10000;
        o->rot[i].c = func_0019A5C8() % 0x10000;
    }
    return 0;
}

/* OVL_WARM */

/* shape b105:01E00120, 479 insns, 10 copies. Calls the module colour helper at 0x1E00080 (shape b000:01E00100)
   as a plain extern: nothing is kept in a scratch register across that call. */


typedef struct {
    u8 b, g, r, a;
} Src_b105_01E00120;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
} Uv_b105_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_b105_01E00120 i;
        f32 f[2];
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b105_01E00120;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b105_01E00120 v[4];
    u8 tail[0x20];
} Pkt_b105_01E00120;

typedef struct {
    f32 x, y, z, w;
} Vec_b105_01E00120;

typedef struct {
    f32 x, y, z;
} Pt_b105_01E00120;

typedef struct {
    void *texture;
    s32 flags;
    Src_b105_01E00120 color;
    f32 r;
    f32 spin[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Vec_b105_01E00120 rots[60];
    Pt_b105_01E00120 pts[60];
} Spark_b105_01E00120;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b105_01E00120;

static s32 func_01E02720_c600(s32 obj, Spark_b105_01E00120 *sp, Cam_b105_01E00120 *cam, s32 mode) {
    extern void c600_01E00100(Pkt_b105_01E00120 *p, Src_b105_01E00120 *s);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103620(void *, void *);
    extern void func_001036A0(void *, s32);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    f32 m[16];
    Vec_b105_01E00120 a;
    Vec_b105_01E00120 b;
    Pkt_b105_01E00120 pkt;
    s32 i;
    f32 rx;
    f32 ry;

    ((Pkt_b105_01E00120 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->pad = 0;
    if (func_00104520(sp->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(sp->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(sp->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    c600_01E00100(&pkt, &sp->color);
    if (func_00104520(sp->flags, 0) != 0) {
        ((Pkt_b105_01E00120 *)(s32)&pkt)->count |= 0x800;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
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
    if (func_00104520(sp->flags, 0x1E) != 0) {
        func_0020C630(m, sp->spin);
        for (i = 0; i < 60; i++) {
            b.x = sp->pts[i].x;
            b.y = sp->pts[i].y;
            b.z = sp->pts[i].z;
            func_0020CDD0(&a, m, &b);
            sp->pts[i].x = a.x;
            sp->pts[i].y = a.y;
            sp->pts[i].z = a.z;
        }
    }
    if (sp->uv.i.w == sp->uv.i.h) {
        rx = ry = sp->r;
    } else if (sp->uv.i.h < sp->uv.i.w) {
        rx = sp->r;
        ry = rx * ((f32)sp->uv.i.h / sp->uv.i.w);
    } else {
        ry = sp->r;
        rx = ry * ((f32)sp->uv.i.w / sp->uv.i.h);
    }
    for (i = 0; i < 60; i++) {
        func_001036A0(&sp->pts[i], mode);
        func_0020C630(m, &sp->rots[i]);
        a.x = -rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            sp->flags |= 0x100000;
        }
        a.x = rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            sp->flags |= 0x200000;
        }
        a.x = -rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            sp->flags |= 0x400000;
        }
        a.x = rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            sp->flags |= 0x800000;
        }
        func_00208700(&pkt, sp->texture, 0);
        if (func_00104520(sp->flags, 0x14) != 0 && func_00104520(sp->flags, 0x15) != 0 &&
            func_00104520(sp->flags, 0x16) != 0 && func_00104520(sp->flags, 0x17) != 0) {
            if (func_00104520(sp->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
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

static s32 func_01E02EA0_c600(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E05680_c600;
    Tbl_b000_01E032C0 tbl = D_01E05680_c600;
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

static s32 func_01E03000_c600(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00100_c600((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

static s32 func_01E03610_c600(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
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

static s32 func_01E03860_c600(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
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
            func_01E00080_c600((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_c600((Pk_b000_01E00080 *)&pk, &o->color, 1);
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

/* shape c600:01E03DC0 (c600), 1309 insns, 1 copy (-O3,p): c600 module main in c543:01E03480's two-unit card form with
   a fourth view and a 60-point spark layer at 0x2000 (texture 0xC, b127:01E02D70's seeding), pale yellow colours;
   float arguments as block locals, statics with float parameters through prototyped aliases, the scene step (below)
   through a no-prototype alias */

typedef struct Src_c600_01E03DC0 {
    Vec4f p0;
    Vec4f p1;
    u8 pad20[0x23];
    u8 f43;
    u8 pad44[0x5C];
} __attribute__((aligned(16))) Src_c600_01E03DC0;

typedef struct Unit_c600_01E03DC0 {
    Vec4f pos;
    union {
        s32 i[4];
        Vec4f v;
    } rot;
    s32 v20[4];
    Vec4f v30;
    u8 pad40[0x41];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c600_01E03DC0;

typedef struct Ctl_c600_01E03DC0 {
    Vec4f a;
    union {
        s32 i[4];
        Vec4f v;
    } b;
    s32 z[3];
    u8 pad2C[4];
    f32 s[2];
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 on;
    u8 pad4C[4];
} Ctl_c600_01E03DC0;

typedef struct Hist_c600_01E03DC0 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c600_01E03DC0;

typedef struct Crd_c600_01E03DC0 {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c600_01E03DC0;

typedef struct Col_c600_01E03DC0 {
    u8 b, g, r, a;
} Col_c600_01E03DC0;

typedef struct Spr_c600_01E03DC0 {
    s32 kind;
    s32 flags;
    Col_c600_01E03DC0 c;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[0x448];
} Spr_c600_01E03DC0;

typedef struct Fx_c600_01E03DC0 {
    s32 kind;
    u8 pad4[4];
    s32 type;
    u8 padC[0x94];
} Fx_c600_01E03DC0;

typedef struct Mdl_c600_01E03DC0 {
    s16 h0, h2, h4, h6, h8, hA, hC, hE;
    u8 pad10[0x20];
    f32 f30;
    Col_c600_01E03DC0 c;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c600_01E03DC0;

typedef struct Ring_c600_01E03DC0 {
    s32 type;
    s32 flags;
    Col_c600_01E03DC0 c;
    f32 height;
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c600_01E03DC0;

typedef struct Pt_c600_01E03DC0 {
    f32 x, y, z;
} Pt_c600_01E03DC0;

typedef struct Spark_c600_01E03DC0 {
    s32 tex;
    s32 flags;
    Col_c600_01E03DC0 c;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_c600_01E03DC0 pts[60];
} Spark_c600_01E03DC0;

typedef struct Rain_c600_01E03DC0 {
    s32 flags;
    Col_c600_01E03DC0 c;
    f32 len;
    s32 count;
    Vec4f pts[64];
} Rain_c600_01E03DC0;

typedef struct Spk_c600_01E03DC0 {
    s32 tex;
    s32 flags;
    Col_c600_01E03DC0 c;
    f32 size;
    s32 r[3];
    u8 pad1C[4];
    s16 u, v, w, h;
    u8 pad28[0x698];
} Spk_c600_01E03DC0;

typedef struct Scene_c600_01E03DC0 {
    Crd_c600_01E03DC0 cam0;
    Fx_c600_01E03DC0 fx;
    Mdl_c600_01E03DC0 mdl;
    Ring_c600_01E03DC0 ring1;
    Ring_c600_01E03DC0 ring2;
    Crd_c600_01E03DC0 cam1;
    Spr_c600_01E03DC0 spr;
    Spark_c600_01E03DC0 spark;
    Crd_c600_01E03DC0 cam2;
    Rain_c600_01E03DC0 rain[2];
    s32 cnt[2];
    u8 pad19C8[8];
    Hist_c600_01E03DC0 histA[4];
    Hist_c600_01E03DC0 histB[4];
    Unit_c600_01E03DC0 a;
    Unit_c600_01E03DC0 b;
    Ctl_c600_01E03DC0 ctl[2];
    Vec4f p[2];
    s32 wait;
    s32 timer;
    s32 life;
    s32 count;
    s32 code;
    s32 flags;
    s32 alpha;
    Col_c600_01E03DC0 col;
    f32 ox;
    f32 oy;
    u8 pad1F78[8];
    f32 radius;
    s32 ang;
    s32 step;
    u8 pad1F8C[4];
    Crd_c600_01E03DC0 cam3;
    Spk_c600_01E03DC0 spk;
    f32 sc[4];
} Scene_c600_01E03DC0;

#pragma optimization_level 3

static s32 func_01E03DC0_c600(s32 arg0, s32 code) {
    Scene_c600_01E03DC0 *g = (Scene_c600_01E03DC0 *)arg0;
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5B30(s32);
    extern s32 func_001F59D0(s32, s32);
    extern void func_00195108(void *, s32);
    extern void func_00205CB0(void *, f32, f32);
    extern void func_00205C40();
    extern void func_00104490(void *, void *, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00103260(void *, s32);
    extern s32 c600_01E05240();
    extern s32 c600_01E004C0();
    s32 ot;
    s32 idA;
    s32 idB;
    Src_c600_01E03DC0 *a;
    Src_c600_01E03DC0 *b;
    s32 tex[4];
    s32 i;
    s32 k;

    ot = (s32)func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Src_c600_01E03DC0 *)func_001F5B30(idA);
    b = (Src_c600_01E03DC0 *)func_001F5B30(idB);
    if (a == NULL && b == NULL) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x26D0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        if (a) {
            g->a = *(Unit_c600_01E03DC0 *)a;
        }
        if (b) {
            g->b = *(Unit_c600_01E03DC0 *)b;
        }
        if (a) {
            func_001F59D0(idA, 1);
            g->a.b6 = 1;
            g->a.b5 = 1;
        }
        if (b) {
            func_001F59D0(idB, 1);
            g->b.b6 = 1;
            g->b.b5 = 1;
        }
        g->flags = 0;
        g->life = 0x96;
        g->code = code;
        if (g->code == 0) {
            g->count = 20;
        } else {
            g->count = 0;
        }
        g->wait = 0x12;
        g->timer = 0x10;
        g->radius = 100.0f;
        g->step = 0x100;
        g->col.r = 0x80;
        g->col.g = 0x80;
        g->col.b = 0x80;
        g->col.a = 0xFF;
        g->sc[0] = g->sc[1] = g->sc[2] = 1.0f;
        if (a) {
            a->f43 = 0;
        }
        if (b) {
            b->f43 = 0;
        }
        g->alpha = 0x80;
        { extern void func_00205CB0(void *, f32, f32); func_00205CB0(&g->p[0], -225.0f, -8.0f); }
        { extern void func_00205CB0(void *, f32, f32); f32 fs1; f32 fs2; fs2 = -8.0f; fs1 = -25.0f; func_00205CB0(&g->p[1], fs1, fs2); }
        g->ctl[0].x = -125.0f;
        g->ctl[0].y = -8.0f;
        g->ctl[1].x = 125.0f;
        g->ctl[1].y = -8.0f;
        if (g->code > 0) {
            if (a) {
                g->ctl[0].on = 20;
                func_00205CB0(&g->ctl[0], g->ctl[0].x, g->ctl[0].y);
                func_00205C40(g->ctl[0].z);
                g->ctl[0].z[0] -= g->a.v20[0];
                g->ctl[0].z[1] -= g->a.v20[1];
                g->ctl[0].z[2] -= g->a.v20[2];
                g->ctl[0].b.i[0] = 0;
                g->ctl[0].b.i[1] = 0x10000;
                g->ctl[0].b.i[2] = 0x10000;
                g->ctl[0].s[0] = 0.46875f;
                g->ctl[0].s[1] = 0.48913f;
            }
            if (b) {
                g->ctl[1].on = 20;
                func_00205CB0(&g->ctl[1], g->ctl[1].x, g->ctl[1].y);
                func_00205C40(g->ctl[1].z);
                g->ctl[1].z[0] -= g->b.v20[0];
                g->ctl[1].z[1] -= g->b.v20[1];
                g->ctl[1].z[2] -= g->b.v20[2];
                g->ctl[1].b.i[0] = 0;
                g->ctl[1].b.i[1] = 0x10000;
                g->ctl[1].b.i[2] = 0x10000;
                g->ctl[1].s[0] = 0.46875f;
                g->ctl[1].s[1] = 0.48913f;
            }
        } else {
            if (a) {
                g->flags |= 1;
                g->ctl[0].on = 1;
                func_00205CB0(&g->a, g->ctl[0].x, g->ctl[0].y);
                g->ctl[0].a = a->p0;
                func_00205C40(g->a.v20);
                g->ctl[0].z[0] = g->ctl[0].z[1] = g->ctl[0].z[2] = 0;
                g->a.rot.i[0] = 0;
                g->a.rot.i[1] = 0x10000;
                g->a.rot.i[2] = 0x10000;
                g->ctl[0].b.v = a->p1;
                g->ctl[0].s[0] = g->ctl[0].s[1] = 0.1f;
                g->a.v30.x = 0.46875f;
                g->a.v30.y = 0.48913f;
                for (i = 0; i < 4; i++) {
                    g->histA[i].v20 = g->a.pos;
                    g->histA[i].v10 = g->a.rot.v;
                    g->histA[i].v00 = g->a.v30;
                }
            }
            if (b) {
                g->flags |= 2;
                g->ctl[1].on = 1;
                func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
                g->ctl[1].a = b->p0;
                func_00205C40(g->b.v20);
                g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
                g->b.rot.i[0] = 0;
                g->b.rot.i[1] = 0x10000;
                g->b.rot.i[2] = 0x10000;
                g->ctl[1].b.v = b->p1;
                g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
                g->b.v30.x = 0.46875f;
                g->b.v30.y = 0.48913f;
                for (i = 0; i < 4; i++) {
                    g->histB[i].v20 = g->b.pos;
                    g->histB[i].v10 = g->b.rot.v;
                    g->histB[i].v00 = g->b.v30;
                }
            }
        }
        for (i = 0; i < 2; i++) {
            g->rain[i].flags = 0x70080001;
            g->rain[i].c.r = 0xA0;
            g->rain[i].c.g = 0xA0;
            g->rain[i].c.b = 0x80;
            g->rain[i].c.a = 0;
            { extern s32 c600_01E03610(void *, s32, f32); f32 fs2 = 80.0f; c600_01E03610(&g->rain[i], 0x40, fs2); }
        }
        func_00103260(tex, 0xF);
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.c.r = 0xA0;
        g->spr.c.g = 0xA0;
        g->spr.c.b = 0x80;
        g->spr.c.a = 0x40;
        { extern s32 c600_01E02EA0(void *, s32, f32); f32 fs2 = 15.0f; c600_01E02EA0(&g->spr, tex[0], fs2); }
        g->ring1.flags = 0x20080000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.c.r = 0xA0;
        g->ring1.c.g = 0xA0;
        g->ring1.c.b = 0x80;
        g->ring1.c.a = 0x20;
        { f32 fs2 = 120.0f; f32 fs3 = 115.0f; f32 fs4 = 0.0f; f32 fs5 = 0.0f; func_01E01DB0_c600((Ring_b001_01E035A0 *)&g->ring1, tex[0], fs2, fs3, fs4, fs5); }
        g->ring2.flags = 0x20080000;
        g->ring2.u = 0x8E;
        g->ring2.v = 0;
        g->ring2.w = 0x20;
        g->ring2.h = 0x40;
        g->ring2.c.r = 0xA0;
        g->ring2.c.g = 0xA0;
        g->ring2.c.b = 0x80;
        g->ring2.c.a = 0x20;
        { extern s32 c600_01E01DB0(void *, s32, f32, f32, f32, f32); f32 fsr = 0.0f; c600_01E01DB0(&g->ring2, tex[0], 120.0f, 130.0f, fsr, fsr); }
        g->mdl.flags = 0x80001;
        g->mdl.h0 = 0x80;
        g->mdl.h2 = 0;
        g->mdl.h4 = 0x20;
        g->mdl.h6 = 0x20;
        g->mdl.h8 = 0xB0;
        g->mdl.hA = 0x20;
        g->mdl.hC = 0x100;
        g->mdl.hE = 0x100;
        g->mdl.f30 = 1.0f;
        g->mdl.c.r = 0xA0;
        g->mdl.c.g = 0xA0;
        g->mdl.c.b = 0x80;
        g->mdl.c.a = 0x60;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 0x3E7;
        g->fx.type = 1;
        func_01E00E90_c600((Model_b013_01E001A0 *)&g->mdl, (Fx_b013_01E001A0 *)&g->fx, tex[0], 200.0f);
        g->spark.tex = tex[0];
        g->spark.size = 3.0f;
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
        g->spark.flags = 0x20080001;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.c.r = 0xA0;
        g->spark.c.g = 0xA0;
        g->spark.c.b = 0x80;
        g->spark.c.a = 0x80;
        func_00103260(tex, 0xC);
        g->spk.tex = tex[0];
        g->spk.flags = 0x60080001;
        g->spk.u = 0;
        g->spk.v = 0;
        g->spk.w = 0x80;
        g->spk.h = 0x40;
        g->spk.c.r = 0x80;
        g->spk.c.g = 0x80;
        g->spk.c.b = 0x80;
        g->spk.c.a = 0x80;
        g->spk.r[0] = 0;
        g->spk.r[1] = 0;
        g->spk.r[2] = 0x1000;
        func_01E02560_c600((Obj_b127_01E02D70 *)&g->spk, 5.0f);
        g->cam0.scale.x = g->cam0.scale.y = g->cam0.scale.z = 0.1f;
        g->cam1.scale.x = g->cam1.scale.y = g->cam1.scale.z = 0.1f;
        return 0;
    }
    func_00103920(&g->cam0, -125.0f, -8.0f);
    func_00103920(&g->cam1, -125.0f, -8.0f);
    func_00103920(&g->cam2, -125.0f, -8.0f);
    func_00103920(&g->cam3, -125.0f, -8.0f);
    if (g->count >= 100) {
        func_01E00750_c600(ot, (Src_b000_01E00400 *)&g->col);
        func_00103470(&g->col.a, 0, 0x10);
    }
    if (func_00104520(g->flags, 4)) {
        c600_01E05240(g, ot);
    }
    ot = func_00207F60();
    func_001D99F0();
    if (!func_00104520(g->flags, 4)) {
        if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
            if (g->code == 2) {
                if (b) {
                    c600_01E004C0(&g->b, g->alpha, 4, g->histB);
                }
                if (a) {
                    c600_01E004C0(&g->a, g->alpha, 4, g->histA);
                }
            } else {
                if (a) {
                    c600_01E004C0(&g->a, g->alpha, 4, g->histA);
                }
                if (b) {
                    c600_01E004C0(&g->b, g->alpha, 4, g->histB);
                }
            }
            if (g->timer < 11) {
                func_00104490(&g->a, &g->p[0], g->timer);
                func_00104490(&g->b, &g->p[1], g->timer);
            }
            if (g->timer) {
                g->timer--;
            } else {
                g->flags |= 0x10;
                g->timer = 1;
            }
        } else {
            if (a) {
                if (!func_00104520(g->flags, 0)) {
                    if (!func_01E001A0_c600((Cam_c536_01E00120 *)&g->a, (Cam_c536_01E00120 *)&g->ctl[0])) {
                        g->flags |= 1;
                        g->a.rot.i[0] = 0;
                        g->a.rot.i[1] = 0;
                        g->a.rot.i[2] = 0;
                        for (i = 0; i < 4; i++) {
                            g->histA[i].v20 = g->a.pos;
                            g->histA[i].v10 = g->a.rot.v;
                            g->histA[i].v00 = g->a.v30;
                        }
                    }
                    func_01E003B0_c600(&g->a, g->alpha, NULL);
                }
            } else {
                g->flags |= 1;
            }
            if (b) {
                if (!func_00104520(g->flags, 1)) {
                    if (!func_01E001A0_c600((Cam_c536_01E00120 *)&g->b, (Cam_c536_01E00120 *)&g->ctl[1])) {
                        g->flags |= 2;
                        g->b.rot.i[0] = 0;
                        g->b.rot.i[1] = 0;
                        g->b.rot.i[2] = 0;
                        for (i = 0; i < 4; i++) {
                            g->histB[i].v20 = g->b.pos;
                            g->histB[i].v10 = g->b.rot.v;
                            g->histB[i].v00 = g->b.v30;
                        }
                    }
                    func_01E003B0_c600(&g->b, g->alpha, NULL);
                }
            } else {
                g->flags |= 2;
            }
        }
    } else if (!func_00104520(g->flags, 5)) {
        if (g->code == 2) {
            if (a) {
                g->ctl[0].on = 20;
                g->ctl[0].x = -125.0f;
                g->ctl[0].y = -8.0f;
                g->ctl[0].a = b->p0;
                func_00205C40(g->a.v20);
                g->ctl[0].z[0] = g->ctl[0].z[1] = g->ctl[0].z[2] = 0;
                g->a.rot.i[0] = 0;
                g->a.rot.i[1] = 0x10000;
                g->a.rot.i[2] = 0x10000;
                g->ctl[0].b.v = a->p1;
                g->ctl[0].s[0] = g->ctl[0].s[1] = 0.1f;
                g->a.v30.x = 0.46875f;
                g->a.v30.y = 0.48913f;
            }
            if (b) {
                c600_01E004C0(&g->b, g->alpha, 4, g->histB);
            }
            if (a) {
                c600_01E004C0(&g->a, g->alpha, 4, g->histA);
            }
        } else {
            if (b) {
                g->ctl[1].on = 20;
                g->ctl[1].x = -125.0f;
                g->ctl[1].y = -8.0f;
                g->ctl[1].a = b->p0;
                func_00205C40(g->b.v20);
                g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
                g->b.rot.i[0] = 0;
                g->b.rot.i[1] = 0x10000;
                g->b.rot.i[2] = 0x10000;
                g->ctl[1].b.v = b->p1;
                g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
                g->b.v30.x = 0.46875f;
                g->b.v30.y = 0.48913f;
            }
            if (a) {
                c600_01E004C0(&g->a, g->alpha, 4, g->histA);
            }
            if (b) {
                c600_01E004C0(&g->b, g->alpha, 4, g->histB);
            }
        }
        if (g->timer == 0) {
            if (g->wait == 0) {
                if (g->code == 0) {
                    g->flags |= 8;
                } else {
                    g->flags |= 0x20;
                }
            } else {
                g->wait--;
            }
        } else {
            g->timer--;
            if (g->timer == 0) {
                g->timer = 1;
                g->ox = g->radius * func_0020B480(g->ang);
                g->oy = g->radius * func_0020B550(g->ang);
                g->ang -= g->step;
                func_00103350(&g->step, 0x1000, 0x100);
                if (!func_00103540(&g->radius, 0.0f, 1.5f)) {
                    g->timer = 0;
                }
                func_00205CB0(&g->p[0], -125.0f - g->ox, -8.0f - g->oy);
                func_00205CB0(&g->p[1], -125.0f + g->ox, -8.0f + g->oy);
                func_00104490(&g->a, &g->p[0], g->timer);
                func_00104490(&g->b, &g->p[1], g->timer);
            }
        }
    } else {
        if (g->code == 2) {
            if (a) {
                if (!func_00104520(g->flags, 2)) {
                    if (!func_01E001A0_c600((Cam_c536_01E00120 *)&g->a, (Cam_c536_01E00120 *)&g->ctl[0])) {
                        g->flags |= 4;
                        g->a.rot.i[0] = ((Unit_c600_01E03DC0 *)a)->rot.i[0];
                        g->a.rot.i[1] = ((Unit_c600_01E03DC0 *)a)->rot.i[1];
                        g->a.rot.i[2] = ((Unit_c600_01E03DC0 *)a)->rot.i[2];
                    }
                    func_01E003B0_c600(&g->a, g->alpha, NULL);
                }
            } else {
                g->flags |= 4;
            }
        } else {
            if (!func_00104520(g->flags, 3)) {
                if (b) {
                    if (!func_01E001A0_c600((Cam_c536_01E00120 *)&g->b, (Cam_c536_01E00120 *)&g->ctl[1])) {
                        g->flags |= 8;
                        g->b.rot.i[0] = ((Unit_c600_01E03DC0 *)b)->rot.i[0];
                        g->b.rot.i[1] = ((Unit_c600_01E03DC0 *)b)->rot.i[1];
                        g->b.rot.i[2] = ((Unit_c600_01E03DC0 *)b)->rot.i[2];
                    }
                    func_01E003B0_c600(&g->b, g->alpha, NULL);
                }
            } else {
                g->flags |= 8;
            }
        }
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    for (i = 3; i >= 0; i--) {
        if (i != 0) {
            g->histA[i].v20 = g->histA[i - 1].v20;
            g->histA[i].v10 = g->histA[i - 1].v10;
            g->histA[i].v00 = g->histA[i - 1].v00;
            g->histB[i].v20 = g->histB[i - 1].v20;
            g->histB[i].v10 = g->histB[i - 1].v10;
            g->histB[i].v00 = g->histB[i - 1].v00;
        } else {
            g->histA[i].v20 = g->a.pos;
            g->histA[i].v10 = g->a.rot.v;
            g->histA[i].v00 = g->a.v30;
            g->histB[i].v20 = g->b.pos;
            g->histB[i].v10 = g->b.rot.v;
            g->histB[i].v00 = g->b.v30;
        }
    }
    g->count++;
    g->life--;
    if (func_00104520(g->flags, 2) || func_00104520(g->flags, 3)) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    if (g->count == 100) {
        return 2;
    }
    if (g->life <= 0) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    return 0;
}

#pragma optimization_level reset

/* shape c600:01E05240 (c600_Flash), 194 insns, 1 copy: c600 scene step (c543:01E04870 form): runs the 60-spark layer
   and spins its points, eases its scale to 10 (clearing its colour when done), then runs the layers; before step 100
   eases the scene scale, after that draws the 1.3-scaled overlay, eases its scale, grows the scene by 0.005 and
   clears four colour blocks; spins the 64 particles, runs both rain blocks, flashes each block and restarts it every
   11 frames */

typedef struct {
    f32 f[3];
    u8 pad00C[0x64];
    u8 b70[0xA0];
    u8 b110[0x60];
    u8 b170[0x400];
    u8 b570[0x400];
    u8 b970[0x70];
    u8 b9E0[0x60];
    s32 arr[64][4];
    u8 bE40[0x2F0];
    u8 b1130[0x70];
    u8 blk[2][0x410];
    s32 cnt[2];
    u8 pad19C8[0x594];
    s32 step;
    u8 pad1F60[0x30];
    u8 b1F90[0x70];
    u8 b2000[0x30];
    s32 arr2[60][4];
    u8 pad23F0[0x2D0];
    u8 b26C0[1];
} Scene_c600_01E05240;

static inline s32 Step_c600_01E05240(void *p, f32 target, f32 step) {
    return func_001033D0((f32 *)p, target, step);
}

static inline void Seed_c600_01E05240(void *p) {
    func_01E03610_c600((Obj_b000_01E04EC0 *)p, 0x40, 80.0f);
}

static void func_01E05240_c600(Scene_c600_01E05240 *g, s32 ot) {
    extern void func_00103470(void *, s32, s32);
    extern void func_001032C0(void *, s32, s32);
    f32 sc[4];
    s32 i;

    func_01E02720_c600(ot, (void *)g->b2000, (void *)g->b1F90, (s32)g->b26C0);
    for (i = 0; i < 60; i++) {
        g->arr2[i][0] += 0x1000;
        g->arr2[i][1] += 0x1000;
        g->arr2[i][2] += 0x1000;
    }
    if (Step_c600_01E05240(g->b1F90, 10.0f, 0.5f) == 0) {
        func_00103470(&g->b2000[0xB], 0, 4);
    }
    func_01E02070_c600(ot, (void *)g->b170, (void *)g);
    func_01E02070_c600(ot, (void *)g->b570, (void *)g);
    func_01E011D0_c600(ot, (void *)g->b110, (void *)g->b70, (void *)g);
    func_01E03000_c600(ot, (void *)g->b9E0, (void *)g->b970);
    if (g->step < 100) {
        func_001033D0(g, 1.0f, 0.02f);
    } else {
        sc[0] = sc[1] = sc[2] = 1.3f;
        func_01E008B0_c600(ot, (void *)g->bE40, (void *)g->b970, (s32)sc);
        func_001033D0(g->b970, 1.0f, 0.3f);
        g->f[0] += 0.005f;
        g->f[1] += 0.005f;
        g->f[2] += 0.005f;
        func_00103470(&g->b9E0[0xB], 0, 4);
        func_00103470(&g->b170[0xB], 0, 2);
        func_00103470(&g->b570[0xB], 0, 2);
        func_00103470(&g->b110[0x37], 0, 3);
    }
    for (i = 0; i < 64; i++) {
        g->arr[i][0] += 0x80;
        g->arr[i][1] += 0x80;
        g->arr[i][2] += 0x80;
    }
    {
        f32 r = 20.0f;
        func_01E03860_c600(ot, (void *)g->blk[0], (void *)g->b1130, r);
        func_01E03860_c600(ot, (void *)g->blk[1], (void *)g->b1130, r);
    }
    for (i = 0; i < 2; i++) {
        if (g->step < 100) {
            if (g->cnt[i] < 5) {
                func_001032C0(&g->blk[i][7], 0xFF, 0x40);
            } else {
                func_00103470(&g->blk[i][7], 0, 0x20);
            }
        }
        if (g->cnt[i] > 10) {
            g->cnt[i] = 0;
            g->blk[i][7] = 0;
            Seed_c600_01E05240(g->blk[i]);
        }
    }
    g->cnt[0]++;
    g->cnt[1]++;
}
