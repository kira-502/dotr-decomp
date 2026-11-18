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

static void func_01E00080_c512(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

extern Six_c500_01E003D0 D_01E01F80_c512;

static s32 func_01E00120_c512(Src_c500_01E003D0 *o, Bb_c500_01E003D0 *out, s32 id, f32 size) {
    Six_c500_01E003D0 q;
    f32 sx;
    f32 sy;
    f32 half;
    s32 i;

    q = D_01E01F80_c512;
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

extern void c512_01E00080(void *, void *);

static s32 func_01E00380_c512(s32 ot, Obj_c500_01E00630 *o, Strip_c500_01E00630 *s, Cam_c500_01E00630 *cam) {
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
    c512_01E00080(&pkt, o->color);
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

static s32 func_01E00AD0_c512(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
    extern void c512_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);
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
    c512_01E00080(&pkt, &sp->color);
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

static s32 func_01E010B0_c512(s32 ot __attribute__((aligned(8))), Def_c505_01E03090 *d __attribute__((aligned(16))), Obj_c505_01E03090 *o, Cam_c505_01E03090 *cam) {
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
    func_01E00080_c512(&pkt, &d->color);
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

/* shape c512:01E015C0 (c512), 618 insns, 1 copy: falling-object scatter: three axes with func_00103390, block-local
   float arguments set the load order */

typedef struct {
    u8 b, g, r, a;
} Col_c512_01E015C0;

typedef struct {
    f32 x, y, z, w;
} Scl_c512_01E015C0;

typedef struct {
    Scl_c512_01E015C0 s;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c512_01E015C0;

typedef struct {
    s16 r[8];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad2C[4];
    f32 f30;
    Col_c512_01E015C0 color;
    s32 flags;
    u8 pad3C[4];
    s32 spin;
    u8 pad44[4];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c512_01E015C0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c512_01E015C0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Def_c512_01E015C0;

typedef struct {
    Vec4f v[8];
} Tbl_c512_01E015C0;

typedef struct {
    s32 tex;
    u8 pad4[8];
    f32 scale;
    s32 a, b, c;
    u8 pad1C[4];
    Vec4f p[8];
} Pts_c512_01E015C0;

typedef struct {
    f32 x, y, z;
} V3_c512_01E015C0;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c512_01E015C0 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    V3_c512_01E015C0 p[60];
} Spark_c512_01E015C0;

typedef struct {
    Crd_c512_01E015C0 a[3];
    Crd_c512_01E015C0 b[3];
    Crd_c512_01E015C0 c[3];
    Mdl_c512_01E015C0 obj[3];
    u8 bb[3][0x80];
    Def_c512_01E015C0 def;
    Pts_c512_01E015C0 pts;
    Spark_c512_01E015C0 spark;
    f32 speed;
    s32 timer;
    s32 code;
    s32 frame;
    s32 flags;
    u8 padA94[0xC];
} Scene_c512_01E015C0;

static s32 func_01E015C0_c512(s32 arg0, s32 code) {
    Scene_c512_01E015C0 *g = (Scene_c512_01E015C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00103260(void *, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_001A6C18(f32, f32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_001032C0(void *, s32, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_00103390(void *, f32, f32);
    extern s32 c512_01E00120(void *, void *, s32, f32);
    extern s32 c512_01E00380();
    extern s32 c512_01E00AD0();
    extern s32 c512_01E010B0();
    extern Tbl_c512_01E015C0 D_01E01FE0_c512;
    s32 tex __attribute__((aligned(16)));
    Tbl_c512_01E015C0 tbl;
    V3_c512_01E015C0 s;
    s32 ot;
    s32 t;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    f32 r;
    f32 dz;
    f32 dx;
    f32 h;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xAA0);
        g->flags = 0;
        g->speed = 0.0f;
        g->frame = 0;
        g->timer = 0x3C;
        g->code = code;
        for (i = 0; i < 3; i++) {
            func_00103890(&g->b[i]);
            func_00103890(&g->a[i]);
            func_001F53B0(0, &g->a[i].pos);
            func_00103890(&g->c[i]);
            func_001F53B0(0, &g->c[i].pos);
        }
        func_00103260(&tex, 8);
        for (i = 0; i < 3; i++) {
            g->obj[i].f30 = 1.0f;
            g->obj[i].flags = 0x40000001;
            g->obj[i].r[0] = 0;
            g->obj[i].r[1] = 0;
            g->obj[i].r[2] = 0x20;
            g->obj[i].r[3] = 0x80;
            g->obj[i].r[4] = 0x20;
            g->obj[i].r[5] = 0;
            g->obj[i].r[6] = 0x80;
            g->obj[i].r[7] = 0x80;
            g->obj[i].h48 = 0;
            g->obj[i].h4A = 1;
            g->obj[i].h4E = 3;
            g->obj[i].h52 = 999;
            g->obj[i].h50 = 0;
            g->obj[i].h4C = g->obj[i].h4E - 1;
            c512_01E00120(&g->obj[i], g->bb[i], tex, 30.0f);
            g->obj[i].color.r = 0x80;
            g->obj[i].color.g = 0x80;
            g->obj[i].color.b = 0x80;
            g->obj[i].color.a = 0;
            g->obj[i].spin = i * 0x2000;
            g->obj[i].rot[1] = (i * 0x5555 + (func_0019A5C8() % 0x3000 - 0x1800)) % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % 100 + 30);
            dz = r * -func_0020B480(g->obj[i].rot[1]);
            dx = r * -func_0020B550(g->obj[i].rot[1]);
            g->obj[i].rot[2] = 0;
            g->obj[i].rot[0] = -(0x4000 - (s32)(65536.0f * (func_001A6C18(15.0f, r) / 6.2831855f)));
            g->obj[i].vx = dx / 4.0f;
            g->obj[i].vz = dz / 4.0f;
            g->obj[i].vy = 5.0f;
            func_001F53B0(0, &g->b[i].pos);
            h = 0.0f;
            g->b[i].pos.x += dx + 60.0 * g->obj[i].vx;
            g->b[i].pos.z += dz + 60.0 * g->obj[i].vz;
            g->b[i].pos.y += h + 60.0f * g->obj[i].vy;
        }
        func_00103260(&tex, 0xE);
        g->def.color.r = 0x80;
        g->def.color.g = 0x80;
        g->def.color.b = 0x80;
        g->def.color.a = 0x80;
        g->def.f30 = 1.0f;
        g->def.flags = 3;
        g->def.r[0] = 0x60;
        g->def.r[1] = 0;
        g->def.r[2] = 0x50;
        g->def.r[3] = 0x50;
        g->def.r[4] = 0x60;
        g->def.r[5] = 0;
        g->def.r[6] = 0x100;
        g->def.r[7] = 0x100;
        g->def.h48 = 0;
        g->def.h4A = 1;
        g->def.h4E = 2;
        g->def.h52 = 0;
        g->def.h50 = 0;
        g->def.h4C = g->def.h4E - 1;
        t = tex;
        tbl = D_01E01FE0_c512;
        g->pts.a = g->pts.b = g->pts.c = 0;
        g->pts.scale = 30.0f;
        g->pts.tex = t;
        for (k = 0; k < 8; k++) {
            g->pts.p[k].x = g->pts.scale * tbl.v[k].x;
            g->pts.p[k].y = g->pts.scale * tbl.v[k].y;
            g->pts.p[k].z = g->pts.scale * tbl.v[k].z;
        }
        for (i = 0; i < 3; i++) {
            g->a[i].s.x = g->a[i].s.y = g->a[i].s.y = 0.1f * (f32)i;
            g->a[i].rot[1] = g->c[i].rot[1] = (i * 0x5555 + (func_0019A5C8() % 0x3000 - 0x1800)) % 0x10000;
            g->c[i].s.x = g->c[i].s.y = g->c[i].s.y = 0.5f;
        }
        func_00103260(&tex, 0xF);
        g->spark.tex = tex;
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
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->c[i]);
        func_001038D0(&g->b[i]);
        func_001038D0(&g->a[i]);
        c512_01E00380(ot, &g->obj[i], g->bb[i], &g->b[i]);
        if (g->frame > 0x28) {
            func_00103470(&g->obj[i].color.a, 0, 8);
        }
        if (g->frame < 0x3C) {
            if (!func_00104520(g->flags, i + 10) && !func_001032C0(&g->obj[i].color.a, 0x80, 8)) {
                g->flags |= 1 << (i + 10);
            }
            if (g->b[i].pos.y > g->obj[i].vy * g->speed) {
                g->obj[i].spin += 0x1000;
                g->b[i].pos.x -= g->obj[i].vx * g->speed;
                g->b[i].pos.z -= g->obj[i].vz * g->speed;
                g->b[i].pos.y -= g->obj[i].vy * g->speed;
            } else {
                if (g->def.h52 == 0 || g->def.h52 == 999) {
                    c512_01E010B0(ot, &g->def, &g->pts, &g->a[i]);
                }
                g->def.h48++;
                func_00103390(&g->a[i].s.x, 1.5f, 0.3f);
                { f32 fs1 = 1.5f; f32 fs2 = 0.3f; func_00103390(&g->a[i].s.y, fs1, fs2); }
                { f32 fs1 = 1.5f; func_00103390(&g->a[i].s.z, fs1, 0.3f); }
                func_00103470(&g->def.color.a, 0, 4);
                s.y = s.x = s.z = 1.02f;
                if (g->c[i].s.x < 1.0f) {
                    g->c[i].s.x = g->c[i].s.y = g->c[i].s.z += 0.1f;
                }
                c512_01E00AD0(ot, &g->spark, &g->c[i], &s);
                func_00103470(&g->spark.color.a, 0, 4);
            }
            g->b[i].rot[0] = g->obj[i].rot[0];
            g->b[i].rot[1] = g->obj[i].rot[1];
            g->b[i].rot[2] = g->obj[i].rot[2];
        }
    }
    g->speed += 0.15f;
    g->frame++;
    g->timer--;
    if (g->frame == 0x1D) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
