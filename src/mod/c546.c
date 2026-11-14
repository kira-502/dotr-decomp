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

static void func_01E00080_c546(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_c546(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_c546((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

extern void c546_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E00CB0_c546(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c546_01E00080(&pkt, &sp->color);
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

static s32 func_01E01290_c546(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c546) and needs that helper
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

static s32 func_01E01550_c546(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c546(&pkt, &ring->color);
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

/* shape c525:01E020F0, 82 insns, 2 copies: sets up a burst: half the given size, the given value, then for each of count
   entries a random speed (0.5..1.5) and two random directions (any heading, a 40..90 degree pitch) as sin/cos */

typedef struct {
    s32 w0, w4, w8;
    f32 speed;
    f32 s0, c0;
    f32 s1, c1;
} Ent_c525_01E020F0;

typedef struct {
    u8 pad0[0xC];
    f32 half;
    u8 pad10[0x10];
    Ent_c525_01E020F0 ent[16];
    s32 w220;
    s32 w224;
    f32 f228;
    s16 count;
} Burst_c525_01E020F0;

static s32 func_01E01A40_c546(Burst_c525_01E020F0 *o, f32 size, f32 v) {
    extern f32 func_0020B730(f32);
    extern f32 func_0020B620(f32);
    s32 i;
    f32 a;

    o->f228 = v;
    o->half = size / 2.0f;
    o->w220 = o->w224 = 0;
    for (i = 0; i < o->count; i++) {
        o->ent[i].w0 = o->ent[i].w4 = o->ent[i].w8 = 0;
        o->ent[i].speed = 0.1f * (func_0019A5C8() % 11 + 5);
        a = 0.017453292f * (func_0019A5C8() % 360);
        o->ent[i].s0 = func_0020B730(a);
        o->ent[i].c0 = func_0020B620(a);
        a = 0.017453292f * (func_0019A5C8() % 50 + 40);
        o->ent[i].s1 = func_0020B730(a);
        o->ent[i].c1 = func_0020B620(a);
    }
    return 0;
}

/* shape c525:01E02240, 603 insns: draws c525:01E020F0's burst: each entry flies on a fixed arc (speed 7 along its two
   directions, falling 0.3267 * t^2 / 2) and is drawn as a textured square of half the burst size times its own
   speed, rotated (flag 0x1E) or axis-aligned, while above the ground; the texture rect is in texels (flag 0)
   or in float STQ; calls the module's colour helper (shape b000:01E00100) as a static function */

typedef struct {
    u64 u : 14;
    u64 pad14 : 2;
    u64 v : 14;
    u64 pad30 : 34;
} Uv_c525_01E02240;

typedef union {
    Uv_c525_01E02240 i;
    struct {
        f32 s, t;
    } f;
} St_c525_01E02240;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    St_c525_01E02240 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vtx_c525_01E02240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c525_01E02240 v[4];
    u8 tail[0x20];
} Pkt_c525_01E02240;

typedef struct {
    f32 x, y, z;
    f32 speed;
    f32 s0, c0;
    f32 s1, c1;
} Ent_c525_01E02240;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    f32 half;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Ent_c525_01E02240 ent[16];
    s32 t;
    s32 angle;
    f32 f228;
    s16 count;
} Burst_c525_01E02240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c525_01E02240;

static s32 func_01E01B90_c546(s32 obj, Burst_c525_01E02240 *o, Cam_c525_01E02240 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f p;
    f32 depth[4];
    Pkt_c525_01E02240 pkt;
    s32 i;
    f32 r;

    ((Pkt_c525_01E02240 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c525_01E02240 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c525_01E02240 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c525_01E02240 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    func_01E00080_c546((Vtx_b000_01E00100 *)&pkt, &o->color);
    if (func_00104520(o->flags, 0) != 0) {
        ((Pkt_c525_01E02240 *)(s32)&pkt)->count |= 0x800;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[0].st)->u = o->r.i.u * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[0].st)->v = o->r.i.v * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[1].st)->u = (o->r.i.u + o->r.i.w - 1) * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[1].st)->v = o->r.i.v * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[2].st)->u = o->r.i.u * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[2].st)->v = (o->r.i.v + o->r.i.h - 1) * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[3].st)->u = (o->r.i.u + o->r.i.w - 1) * 16;
        ((Uv_c525_01E02240 *)(s32)&pkt.v[3].st)->v = (o->r.i.v + o->r.i.h - 1) * 16;
    } else {
        pkt.v[0].st.f.s = o->r.f.s;
        pkt.v[0].st.f.t = o->r.f.t;
        pkt.v[1].st.f.s = o->r.f.s + o->r.f.w;
        pkt.v[1].st.f.t = o->r.f.t;
        pkt.v[2].st.f.s = o->r.f.s;
        pkt.v[2].st.f.t = o->r.f.t + o->r.f.h;
        pkt.v[3].st.f.s = o->r.f.s + o->r.f.w;
        pkt.v[3].st.f.t = o->r.f.t + o->r.f.h;
    }
    for (i = 0; i < o->count; i++) {
        o->ent[i].y = 7.0f * o->t * o->ent[i].s1 - 0.32666665f * o->t * o->t / 2.0f;
        o->ent[i].z = o->ent[i].c0 * (7.0f * o->t * o->ent[i].c1);
        o->ent[i].x = o->ent[i].s0 * (7.0f * o->t * o->ent[i].c1);
        if (func_00104520(o->flags, 0x1E) != 0) {
            r = 0.017453292f * ((o->angle + 135) % 360);
            p.x = o->ent[i].x + o->ent[i].speed * (o->half * func_0020B620(r));
            p.y = o->ent[i].y + o->ent[i].speed * (o->half * func_0020B730(r));
            p.z = o->ent[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
            r = 0.017453292f * ((o->angle + 45) % 360);
            p.x = o->ent[i].x + o->ent[i].speed * (o->half * func_0020B620(r));
            p.y = o->ent[i].y + o->ent[i].speed * (o->half * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                o->flags |= 0x200000;
            }
            r = 0.017453292f * ((o->angle + 225) % 360);
            p.x = o->ent[i].x + o->ent[i].speed * (o->half * func_0020B620(r));
            p.y = o->ent[i].y + o->ent[i].speed * (o->half * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                o->flags |= 0x400000;
            }
            r = 0.017453292f * ((o->angle + 315) % 360);
            p.x = o->ent[i].x + o->ent[i].speed * (o->half * func_0020B620(r));
            p.y = o->ent[i].y + o->ent[i].speed * (o->half * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                o->flags |= 0x800000;
            }
        } else {
            p.x = o->ent[i].x - o->half * o->ent[i].speed;
            p.y = o->ent[i].y + o->half * o->ent[i].speed;
            p.z = o->ent[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
            p.x = o->ent[i].x + o->half * o->ent[i].speed;
            p.y = o->ent[i].y + o->half * o->ent[i].speed;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                o->flags |= 0x200000;
            }
            p.x = o->ent[i].x - o->half * o->ent[i].speed;
            p.y = o->ent[i].y - o->half * o->ent[i].speed;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                o->flags |= 0x400000;
            }
            p.x = o->ent[i].x + o->half * o->ent[i].speed;
            p.y = o->ent[i].y - o->half * o->ent[i].speed;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                o->flags |= 0x800000;
            }
        }
        func_00208700(&pkt, o->texture, 0);
        if (!(o->ent[i].y <= 0.0f) && func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    o->t++;
    return 0;
}

/* shape c546:01E02500 (c546), 703 insns, 1 copy: c546 scene manager (c525:01E033D0's form without the fireball): code
   >= 0 sets up three cameras, a 60-tick timer, an 8-entry burst, two 8-point emitters, two rings (0.1/24/0/28,
   5/30/2/10) and a 60-point spark (size 1.5 for code 1); else draws spark, burst, rings and emitters while growing
   cameras 1 and 2 (to 1 or 2 by code); returns 2 at tick 6, 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_c546_01E02500;

typedef struct {
    f32 x, y, z;
    u8 padC[0x14];
    u8 pos[4];
    f32 f24;
    u8 pad28[0x48];
} Cam_c546_01E02500;

typedef struct {
    f32 x, y, z;
} SPt_c546_01E02500;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c546_01E02500 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    SPt_c546_01E02500 pts[60];
} Spark_c546_01E02500;

typedef struct {
    f32 x, y, z;
    s16 hC;
    s16 hE;
} Pt_c546_01E02500;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c546_01E02500 color;
    f32 size;
    f32 cx;
    f32 cy;
    f32 z0;
    s32 w1C;
    s16 rect[8];
    Pt_c546_01E02500 pt[16];
    s16 count;
    u8 pad132[4];
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_c546_01E02500;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c546_01E02500 color;
    u8 padC[4];
    s16 u, v, w, h;
    s16 u2, v2, w2, h2;
    u8 pad20[0x204];
    s32 angle;
    u8 pad228[4];
    s16 count;
    u8 pad22E[2];
} Burst_c546_01E02500;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c546_01E02500 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c546_01E02500;

typedef struct {
    Cam_c546_01E02500 cam0;
    Cam_c546_01E02500 cam1;
    Cam_c546_01E02500 cam2;
    Spark_c546_01E02500 spark;
    Emit_c546_01E02500 e1;
    Emit_c546_01E02500 e2;
    Burst_c546_01E02500 burst;
    Ring_c546_01E02500 ring0;
    Ring_c546_01E02500 ring1;
    Vec4f sc;
    s32 timer;
    s32 t;
    s32 code;
    s32 flags;
    s32 w1130;
    s32 w1134;
    u8 pad1138[8];
} Scene_c546_01E02500;

static s32 func_01E02500_c546(s32 arg0, s32 code) {
    Scene_c546_01E02500 *g = (Scene_c546_01E02500 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_001039A0(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F5380(void);
    extern s32 func_00104520(s32, s32);
    extern void func_001E10F0(s32, s32, s32, void *);
    extern void func_00103470(void *, s32, s32);
    extern s32 func_0019A5C8();
    Vec4f a;
    Vec4f b;
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 j;
    s32 m;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1140);
        g->flags = 0;
        g->t = 0;
        func_00103890(g);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        g->timer = 60;
        g->code = code;
        g->sc.x = 1.02f;
        g->sc.y = 1.02f;
        g->sc.z = 1.02f;
        g->w1130 = func_001F5380() & 0xFF;
        g->w1134 = func_001F5380() >> 8;
        func_00103260(&tex, 7);
        g->burst.texture = tex;
        g->burst.flags = 0x40000001;
        g->burst.u = 0x40;
        g->burst.v = 0;
        g->burst.w = 0x20;
        g->burst.h = 0x20;
        g->burst.color.r = 0x60;
        g->burst.color.g = 0x70;
        g->burst.color.b = 0x70;
        g->burst.color.a = 0x80;
        g->burst.count = 8;
        func_01E01A40_c546((Burst_c525_01E020F0 *)&g->burst, 5.0f, 7.0f);
        func_00103260(&tex, 0);
        g->e1.texture = tex;
        g->e1.flags = 7;
        g->e1.cx = 0.0f;
        if (g->code == 1) {
            g->e1.z0 = g->e1.cy = 20.0f;
        } else {
            g->e1.z0 = g->e1.cy = 10.0f;
        }
        g->e1.w1C = 0;
        g->e1.rect[4] = 0;
        g->e1.rect[5] = 0;
        g->e1.rect[2] = 0x20;
        g->e1.rect[3] = 0x20;
        g->e1.rect[6] = 0x80;
        g->e1.rect[7] = 0x40;
        g->e1.size = 20.0f;
        g->e1.count = 8;
        g->e1.step = 3;
        g->e1.h13C = 1;
        g->e1.h140 = 8;
        g->e1.h136 = 10;
        g->e1.h138 = 10;
        g->e1.color.r = 0x80;
        g->e1.color.g = 0x80;
        g->e1.color.b = 0x80;
        g->e1.color.a = 0x80;
        for (j = 0; j < g->e1.count; j++) {
            g->e1.pt[j].x = g->e1.cx + (func_0019A5C8() % 20 - 10);
            g->e1.pt[j].y = g->e1.cy + (func_0019A5C8() % 16 - 4);
            g->e1.pt[j].z = g->e1.z0;
            g->e1.pt[j].hE = -g->e1.step * j;
            g->e1.pt[j].hC = 0;
            g->e1.h13E = g->e1.h140 - 1;
        }
        func_00103260(&tex, 0xF);
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.flags = 0x8000;
        g->ring0.color.r = 0xA0;
        g->ring0.color.g = 0x60;
        g->ring0.color.b = 0x50;
        g->ring0.color.a = 0x60;
        {
            f32 q1 = 24.0f;
            f32 q2 = 0.0f;
            {
                f32 q3 = 28.0f;
                func_01E01290_c546((Ring_b001_01E035A0 *)&g->ring0, tex, 0.1f, q1, q2, q3);
            }
        }
        g->ring1.flags = 0x8000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0xA0;
        g->ring1.color.g = 0x60;
        g->ring1.color.b = 0x50;
        g->ring1.color.a = 0x60;
        {
            extern s32 c546_01E01290(void *, s32, f32, f32, f32, f32);
            f32 q1 = 30.0f;
            f32 q2 = 2.0f;
            f32 q3 = 10.0f;
            c546_01E01290(&g->ring1, tex, 5.0f, q1, q2, q3);
        }
        g->spark.texture = tex;
        if (g->code == 1) {
            g->spark.size = 1.5f;
            for (i = 0; i < 60; i++) {
                if (func_00104520(g->spark.flags, 0x1D)) {
                    g->spark.pts[i].x = func_0019A5C8() % 100 - 50;
                    g->spark.pts[i].z = func_0019A5C8() % 50;
                    g->spark.pts[i].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark.pts[i].x = func_0019A5C8() % 50 - 25;
                    g->spark.pts[i].y = func_0019A5C8() % 25;
                    g->spark.pts[i].z = func_0019A5C8() % 50 - 25;
                }
            }
        } else {
            g->spark.size = 1.0f;
            for (m = 0; m < 60; m++) {
                if (func_00104520(g->spark.flags, 0x1D)) {
                    g->spark.pts[m].x = func_0019A5C8() % 100 - 50;
                    g->spark.pts[m].z = func_0019A5C8() % 50;
                    g->spark.pts[m].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark.pts[m].x = func_0019A5C8() % 50 - 25;
                    g->spark.pts[m].y = func_0019A5C8() % 25;
                    g->spark.pts[m].z = func_0019A5C8() % 50 - 25;
                }
            }
        }
        g->spark.flags = 1;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x60;
        g->spark.color.b = 0x40;
        g->spark.color.a = 0x80;
        g->e2.texture = tex;
        g->e2.flags = 0x85;
        g->e2.cx = 0.0f;
        g->e2.cy = 20.0f;
        g->e2.z0 = 0.0f;
        g->e2.w1C = 0;
        g->e2.rect[4] = 0xF0;
        g->e2.rect[5] = 0;
        g->e2.rect[2] = 0x10;
        g->e2.rect[3] = 0x10;
        g->e2.rect[6] = 0x100;
        g->e2.rect[7] = 0x100;
        g->e2.size = 10.0f;
        g->e2.count = 8;
        g->e2.step = 3;
        g->e2.h13C = 1;
        g->e2.h140 = 8;
        g->e2.h136 = 30;
        g->e2.h138 = 30;
        g->e2.color.r = 0x80;
        g->e2.color.g = 0x80;
        g->e2.color.b = 0x80;
        g->e2.color.a = 0x60;
        for (i = 0; i < g->e2.count; i++) {
            g->e2.pt[i].x = g->e2.cx + (func_0019A5C8() % 20 - 10);
            g->e2.pt[i].y = g->e2.cy + (func_0019A5C8() % 16 - 4);
            g->e2.pt[i].z = g->e2.z0;
            g->e2.pt[i].hE = -g->e2.step * i;
            g->e2.pt[i].hC = 0;
            g->e2.h13E = g->e2.h140 - 1;
        }
        if (g->code == 0) {
            g->cam2.x = g->cam2.y = g->cam2.z = g->cam1.x = g->cam1.y = g->cam1.z = 0.1f;
        } else {
            g->cam0.x = g->cam0.y = g->cam0.z = 2.0f;
            g->cam2.x = g->cam2.y = g->cam2.z = g->cam1.x = g->cam1.y = g->cam1.z = 1.1f;
        }
        func_001E10F0(g->w1130, g->w1134, 0, g->cam0.pos);
        func_001E10F0(g->w1130, g->w1134, 0, g->cam1.pos);
        func_001E10F0(g->w1130, g->w1134, 0, g->cam2.pos);
        return 0;
    }
    g->cam1.f24 = 3.0f;
    b.x = b.y = b.z = 1.01f;
    a.x = a.y = a.z = 0.0f;
    func_001039A0(g);
    func_001039A0(&g->cam1);
    func_001038D0(&g->cam2);
    func_01E00CB0_c546(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)&g->cam1, (s32)&g->sc);
    func_00103470(&g->spark.color.a, 0, 10);
    func_01E01B90_c546(ot, (Burst_c525_01E02240 *)&g->burst, (Cam_c525_01E02240 *)g);
    func_00103470(&g->burst.color.a, 0, 3);
    g->burst.angle += 30;
    func_01E01550_c546(ot, (Ring_b001_01E03860 *)&g->ring0, (Cam_b001_01E03860 *)&g->cam2);
    func_00103470(&g->ring0.color.a, 0, 16);
    func_01E01550_c546(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)&g->cam2);
    func_00103470(&g->ring1.color.a, 0, 16);
    if (g->code == 0) {
        if (g->cam1.x < 1.0f) {
            g->cam1.x = g->cam1.y = g->cam1.z += 0.2f;
        }
        if (g->cam2.x < 1.0f) {
            g->cam2.x = g->cam2.y = g->cam2.z += 0.2f;
        } else {
            g->cam2.x = g->cam2.y = g->cam2.z += 0.05f;
        }
    } else {
        if (g->cam1.x < 2.0f) {
            g->cam1.x = g->cam1.y = g->cam1.z += 0.2f;
        }
        if (g->cam2.x < 2.0f) {
            g->cam2.x = g->cam2.y = g->cam2.z += 0.2f;
        } else {
            g->cam2.x = g->cam2.y = g->cam2.z += 0.05f;
        }
    }
    func_01E00120_c546(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e1, (Vec_b001_01E00A30 *)&a);
    func_00103470(&g->e1.color.a, 0, 8);
    func_01E00120_c546(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e2, (Vec_b001_01E00A30 *)&b);
    func_00103470(&g->e2.color.a, 0, 2);
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
