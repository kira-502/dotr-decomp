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

static void func_01E00080_b037(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b037(s32 arg0, Src_b000_01E00400 *c) {
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

/* shape b037:01E00280, 86 insns, 2 copies: lays out count trail points at the emitter position, each jittered in x and y by
   up to the emitter's spread, delayed by a per-point step; their start frame comes from the model's animation
   unless flag 0 is set */

typedef struct {
    f32 x, y, z;
    s16 start;
    s16 delay;
} Pt_b037_01E00280;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[8];
    f32 x, y, z;
    u8 pad1C[4];
    u8 anim[0x10];
    Pt_b037_01E00280 pt[16];
    s16 count;
    u8 pad132[4];
    s16 jx;
    s16 jy;
    s16 step;
    u8 pad13C[2];
    s16 end;
    s16 len;
} Trail_b037_01E00280;

static s32 func_01E00280_b037(Trail_b037_01E00280 *o) {
    extern s16 func_00105C40(void *);
    s32 i;
    s16 j;

    for (i = 0; i < o->count; i++) {
        o->pt[i].x = o->x;
        o->pt[i].y = o->y;
        j = o->jx;
        if (j != 0) {
            o->pt[i].x = o->x + (f32)(func_0019A5C8() % (j * 2) - j);
        }
        j = o->jy;
        if (j != 0) {
            o->pt[i].y = o->y + (f32)(func_0019A5C8() % (j * 2) - j);
        }
        o->pt[i].z = o->z;
        o->pt[i].delay = -o->step * i;
        if (func_00104520(o->flags, 0) != 0) {
            o->pt[i].start = 0;
            o->end = o->len - 1;
        } else {
            o->pt[i].start = func_00105C40(o->anim);
            o->end = o->pt[i].start + o->len - 1;
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

static s32 func_01E003E0_b037(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_b037((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape b037:01E00F70, 77 insns, 10 copies: b001:01E00900 with the colour from the caller (b, g, r, a bytes): one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b037_01E00F70;

typedef struct {
    Hdr_b037_01E00F70 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b037_01E00F70;

static s32 func_01E00F70_b037(u8 *c) {
    Pkt_b037_01E00F70 p __attribute__((aligned(8)));

    ((Hdr_b037_01E00F70 *)(s32)&p)->count = 0x26;
    ((Hdr_b037_01E00F70 *)(s32)&p)->tag = 5;
    ((Hdr_b037_01E00F70 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b037_01E00F70 *)(s32)&p)->pad = 0;
    p.r = c[2];
    p.g = c[1];
    p.b = c[0];
    p.a = c[3];
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    return 0;
}

/* shape b037:01E010B0 (LkPrim_SortSpiral), 457 insns, 1 copy: a spiral band of quads, 30 path points
   scaled by step i, each step drawn above and below the path (height h), half alpha on back faces */

typedef struct {
    u16 c : 14;
    u16 p : 2;
} Tc_b037_01E010B0;

typedef struct {
    Tc_b037_01E010B0 u;
    Tc_b037_01E010B0 v;
    s32 pad;
} Uv_b037_01E010B0;

typedef union {
    Uv_b037_01E010B0 uv;
    struct {
        f32 s, t;
    } st;
} Tex_b037_01E010B0;

typedef struct {
    u16 x, y;
    u32 z;
} Xyz_b037_01E010B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tex_b037_01E010B0 tc;
    Xyz_b037_01E010B0 xyz;
} Vtx_b037_01E010B0;

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b037_01E010B0 v[4];
    u8 tail[0x20];
} Pkt_b037_01E010B0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 col;
    f32 h;
    f32 dy;
    u8 pad14[4];
    f32 scale;
    s32 count;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Vec4f pts[30];
} Obj_b037_01E010B0;

typedef struct {
    u8 pad[0x30];
    f32 m[16];
} Cam_b037_01E010B0;

#define UV(k) ((Uv_b037_01E010B0 *)(s32)&pkt.v[k].tc)

static s32 func_01E010B0_b037(s32 ot, Obj_b037_01E010B0 *o, Cam_b037_01E010B0 *cam) {
    f32 d[4];
    Vec4f v[4];
    Pkt_b037_01E010B0 pkt;
    s32 i;
    s32 j;
    s32 jn;

    ((Pkt_b037_01E010B0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b037_01E010B0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b037_01E010B0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b037_01E010B0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00080_b037((Vtx_b000_01E00100 *)&pkt, &o->col);
    pkt.v[2].a = pkt.v[3].a = 0;
    if (func_00104520(o->flags, 0) != 0) {
        ((Pkt_b037_01E010B0 *)(s32)&pkt)->count |= 0x800;
        UV(0)->u.c = o->r.i.u * 16;
        UV(0)->v.c = o->r.i.v * 16;
        UV(1)->u.c = (o->r.i.u + o->r.i.w - 1) * 16;
        UV(1)->v.c = o->r.i.v * 16;
        UV(2)->u.c = o->r.i.u * 16;
        UV(2)->v.c = (o->r.i.v + o->r.i.h - 1) * 16;
        UV(3)->u.c = (o->r.i.u + o->r.i.w - 1) * 16;
        UV(3)->v.c = (o->r.i.v + o->r.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = o->r.f.s;
        pkt.v[0].tc.st.t = o->r.f.t;
        pkt.v[1].tc.st.s = o->r.f.s + o->r.f.w;
        pkt.v[1].tc.st.t = o->r.f.t;
        pkt.v[2].tc.st.s = o->r.f.s;
        pkt.v[2].tc.st.t = o->r.f.t + o->r.f.h;
        pkt.v[3].tc.st.s = o->r.f.s + o->r.f.w;
        pkt.v[3].tc.st.t = o->r.f.t + o->r.f.h;
    }
    for (i = 0; i < o->count; i++) {
        j = i % 30;
        jn = j + 1;
        if (jn == 30) {
            jn = 0;
        }
        v[0].x = (f32)i * (o->pts[j].x * o->scale);
        v[0].z = (f32)i * (o->pts[j].z * o->scale);
        v[0].y = o->dy * (f32)i;
        if (func_00205440((s32)&v[0], cam->m, &pkt.v[0].xyz.x, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        v[1].x = (f32)(i + 1) * (o->pts[jn].x * o->scale);
        v[1].z = (f32)(i + 1) * (o->pts[jn].z * o->scale);
        v[1].y = o->dy * (f32)(i + 1);
        if (func_00205440((s32)&v[1], cam->m, &pkt.v[1].xyz.x, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        v[2].x = v[0].x;
        v[2].z = v[0].z;
        v[2].y = v[0].y + o->h;
        if (func_00205440((s32)&v[2], cam->m, &pkt.v[2].xyz.x, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        v[3].x = v[1].x;
        v[3].z = v[1].z;
        v[3].y = v[1].y + o->h;
        if (func_00205440((s32)&v[3], cam->m, &pkt.v[3].xyz.x, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if ((pkt.v[2].xyz.x - pkt.v[0].xyz.x) * (pkt.v[1].xyz.y - pkt.v[0].xyz.y) -
                    (pkt.v[2].xyz.y - pkt.v[0].xyz.y) * (pkt.v[1].xyz.x - pkt.v[0].xyz.x) <= 0) {
                pkt.v[0].a = pkt.v[1].a = o->col.a;
            } else {
                pkt.v[0].a = pkt.v[1].a = o->col.a >> 1;
            }
            func_00208700(&pkt, o->texture, 0);
            func_002075F0((s32)&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
        v[2].y = v[0].y - o->h;
        if (func_00205440((s32)&v[2], cam->m, &pkt.v[2].xyz.x, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        v[3].y = v[1].y - o->h;
        if (func_00205440((s32)&v[3], cam->m, &pkt.v[3].xyz.x, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if ((pkt.v[2].xyz.x - pkt.v[0].xyz.x) * (pkt.v[1].xyz.y - pkt.v[0].xyz.y) -
                    (pkt.v[2].xyz.y - pkt.v[0].xyz.y) * (pkt.v[1].xyz.x - pkt.v[0].xyz.x) > 0) {
                pkt.v[0].a = pkt.v[1].a = o->col.a;
            } else {
                pkt.v[0].a = pkt.v[1].a = o->col.a >> 1;
            }
            func_00208700(&pkt, o->texture, 0);
            func_002075F0((s32)&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E01B20;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[4];
    f32 half;
    u8 pad10[0x30];
    Vec_b001_01E01B20 *pts;
    u8 pad44[8];
    f32 radius;
    u8 pad50[0xA];
    s16 count;
} Ring_b001_01E01B20;

static s32 func_01E017E0_b037(Ring_b001_01E01B20 *o, f32 size) {
    s32 i;
    s32 ang;

    o->half = size / 2.0f;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = o->radius * func_0020B550(ang);
            o->pts[i].z = func_0019A5C8() % 20;
            o->pts[i].x = o->radius * func_0020B480(ang);
        } else {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = func_0019A5C8() % 20;
            o->pts[i].z = o->radius * func_0020B480(ang);
            o->pts[i].x = o->radius * func_0020B550(ang);
        }
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

static s32 func_01E01970_b037(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b037((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape b037:01E03260, 111 insns: sets up a ring of 30 points at angles k x pi/15 (k = 1..30): an inner ring of radius
   r1 at height h and an outer ring of radius r2 at height h + dh, laid in the x/y plane or (when func_00104520 says
   the model lacks flag 0x1D) the x/z plane; the header keeps the arguments */

typedef struct {
    s32 kind;
    s32 model;
    u8 pad8[4];
    f32 dh;
    u8 pad10[0x10];
    f32 r1;
    f32 f24;
    f32 f28;
    u8 pad2C[4];
    f32 r2;
    f32 f34;
    f32 f38;
    u8 pad3C[4];
    Vec4f in[30];
    Vec4f out[30];
} Ring_b037_01E03260;

static s32 func_01E03260_b037(Ring_b037_01E03260 *o, s32 kind, f32 r1, f32 r2, f32 h, f32 dh) {
    extern s32 func_00104520(s32, s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    f32 top;
    f32 t;
    s32 i;

    o->kind = kind;
    o->dh = dh;
    o->r1 = r1;
    o->r2 = r2;
    if (func_00104520(o->model, 0x1D) != 0) {
        o->f24 = 0.0f;
        o->f28 = h;
        o->f34 = 0.0f;
        top = h + dh;
        o->f38 = top;
        for (i = 0; i < 30; i++) {
            t = 0.20943952f * (f32)(i + 1);
            o->in[i].x = r1 * func_0020B620(t);
            o->in[i].y = r1 * func_0020B730(t);
            o->in[i].z = h;
            o->out[i].x = r2 * func_0020B620(t);
            o->out[i].y = r2 * func_0020B730(t);
            o->out[i].z = top;
        }
    } else {
        top = h + dh;
        o->f24 = h;
        o->f28 = 0.0f;
        o->f34 = top;
        o->f38 = 0.0f;
        for (i = 0; i < 30; i++) {
            t = 0.20943952f * (f32)(i + 1);
            o->in[i].x = r1 * func_0020B620(t);
            o->in[i].z = r1 * func_0020B730(t);
            o->in[i].y = h;
            o->out[i].x = r2 * func_0020B620(t);
            o->out[i].z = r2 * func_0020B730(t);
            o->out[i].y = top;
        }
    }
    return 0;
}

/* shape b037:01E03420 (LkSortRing2), 491 insns, 1 copy: draws the 30-segment ring built by b037:01E03260 (31 segments
   as a fan of degenerate quads, inner point twice, when flag 0x1E is set), b001:01E03860s form with the colour helper
   hoisted out of the loop */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b037_01E03420;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b037_01E03420 v[4];
    u8 tail[0x20];
} Pkt_b037_01E03420;

typedef struct {
    f32 x, y, z, w;
} Vec_b037_01E03420;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    u8 pad0C[4];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad18[8];
    Vec_b037_01E03420 p0;
    Vec_b037_01E03420 p1;
    Vec_b037_01E03420 in[30];
    Vec_b037_01E03420 out[30];
} Ring_b037_01E03420;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b037_01E03420;

static s32 func_01E03420_b037(s32 obj __attribute__((aligned(8))), Ring_b037_01E03420 *ring, Cam_b037_01E03420 *cam) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    extern s32 func_001A23B0(f32);
    f32 depth[4];
    Pkt_b037_01E03420 pkt;
    s32 i;
    s32 n;

    ((Pkt_b037_01E03420 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b037_01E03420 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b037_01E03420 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b037_01E03420 *)(s32)&pkt)->pad = 0;
    if (func_00104520(ring->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(ring->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b037((Vtx_b000_01E00100 *)&pkt, &ring->color);
    if (func_00104520(ring->flags, 0x1E) != 0) {
        n = 31;
        func_00104540(&pkt, &ring->u, 0);
    } else {
        n = 30;
        func_00104540(&pkt, &ring->u, 2);
    }
    for (i = 0; i < n; i++) {
        if (func_00104520(ring->flags, 0x1E) != 0) {
            if (i != 30) {
                if (i == 0) {
                    if (func_00205440(&ring->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                        ring->flags |= 0x100000;
                    }
                    if (func_00205440(&ring->p0, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                        ring->flags |= 0x200000;
                    }
                } else {
                    if (func_00205440(&ring->in[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                        ring->flags |= 0x100000;
                    }
                    if (func_00205440(&ring->in[i - 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                        ring->flags |= 0x200000;
                    }
                }
                if (i != 29) {
                    if (func_00205440(&ring->out[i + 1], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                        ring->flags |= 0x400000;
                    }
                } else {
                    if (func_00205440(&ring->p1, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                        ring->flags |= 0x400000;
                    }
                }
                if (func_00205440(&ring->out[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                    ring->flags |= 0x800000;
                }
            } else {
                if (func_00205440(&ring->in[28], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                    ring->flags |= 0x100000;
                }
                if (func_00205440(&ring->in[28], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                    ring->flags |= 0x200000;
                }
                if (func_00205440(&ring->out[0], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                    ring->flags |= 0x400000;
                }
                if (func_00205440(&ring->p1, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                    ring->flags |= 0x800000;
                }
            }
        } else {
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


/* shape b037:01E03BD0, 174 insns: projects four rings (radii r0..r1 in thirds) of 128 points each (step 2pi/128) at height h, in the x/y plane or (when func_00104520 says the model lacks flag 0x1D) the x/z plane, storing the screen x/y of each into the object's point table */

typedef struct {
    s16 x, y;
} Sxy_b037_01E03BD0;

typedef struct {
    s32 model;
    u8 pad4[0xC];
    Sxy_b037_01E03BD0 pts[4][128];
} Obj_b037_01E03BD0;

static s32 func_01E03BD0_b037(Obj_b037_01E03BD0 *o, u8 *arg1, f32 r0, f32 r1, f32 h) {
    extern s32 func_00104520(s32, s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern s32 func_00205440(void *, void *, void *, void *);
    f32 c[4];
    f32 q[4];
    f32 r[4];
    s16 xy[4] __attribute__((aligned(8)));
    s32 i;
    s32 j;
    f32 t;
    f32 d;

    if (func_00104520(o->model, 0x1D) != 0) {
        d = (r1 - r0) / 3.0f;
        c[2] = h;
        for (i = 0; i < 4; i++) {
            r[i] = r0 + d * i;
        }
        for (j = 0; j < 128; j++) {
            t = 0.049087387f * j;
            c[0] = func_0020B620(t);
            c[1] = func_0020B730(t);
            for (i = 0; i < 4; i++) {
                q[0] = c[0] * r[i];
                q[1] = c[1] * r[i];
                q[2] = c[2];
                func_00205440(q, arg1 + 0x30, xy, &c[3]);
                o->pts[i][j].x = xy[0];
                o->pts[i][j].y = xy[1];
            }
        }
    } else {
        d = (r1 - r0) / 3.0f;
        c[1] = h;
        for (i = 0; i < 4; i++) {
            r[i] = r0 + d * i;
        }
        for (j = 0; j < 128; j++) {
            t = 0.049087387f * j;
            c[0] = func_0020B620(t);
            c[2] = func_0020B730(t);
            for (i = 0; i < 4; i++) {
                q[0] = c[0] * r[i];
                q[2] = c[2] * r[i];
                q[1] = c[1];
                func_00205440(q, arg1 + 0x30, xy, &c[3]);
                o->pts[i][j].x = xy[0];
                o->pts[i][j].y = xy[1];
            }
        }
    }
    return 0;
}

/* shape b037:01E03E90 (LkEff_SortSpiralShaver), 423 insns, 1 copy: draws three bands of 128 textured quads between
   the four point rings of b037:01E03BD0, texture from the screen (or rotated rings when flag 0x1F), far z when flag
   0x13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b037_01E03E90;

typedef struct {
    u16 c : 14;
    u16 p : 2;
} Tc_b037_01E03E90;

typedef struct {
    Tc_b037_01E03E90 u;
    Tc_b037_01E03E90 v;
    s32 pad;
} Uv_b037_01E03E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b037_01E03E90 uv;
    Xyz_b037_01E03E90 xyz;
} Vtx_b037_01E03E90;

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b037_01E03E90 v[4];
} Pkt_b037_01E03E90;

typedef struct {
    s16 x, y;
} Sxy_b037_01E03E90;

typedef struct {
    s32 model;
    u8 col[4];
    u8 pad8[4];
    s32 z;
    Sxy_b037_01E03E90 pts[4][128];
    s16 rot[4];
} Obj_b037_01E03E90;

static s32 func_01E03E90_b037(Obj_b037_01E03E90 *o) {
    s32 ot;
    s32 i;
    s32 j;
    s32 jn;
    s32 a;
    s32 b;
    s32 k;
    Pkt_b037_01E03E90 pkt;
    u64 pre;
    s32 post[3];

    ot = func_00207F60();
    ((Pkt_b037_01E03E90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b037_01E03E90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b037_01E03E90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b037_01E03E90 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->model, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->model, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->model, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b037((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)o->col);
    func_00208460();
    func_00208800(func_00209E50(), 0, (s32)&pre, (s32)post);
    func_00208460();
    for (k = 0; k < 4; k++) {
        o->rot[k] %= 128;
    }
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 3; i++) {
            jn = j + 1;
            if (jn == 128) {
                jn = 0;
            }
            pkt.v[0].xyz.x = o->pts[i][j].x;
            pkt.v[0].xyz.y = o->pts[i][j].y;
            pkt.v[1].xyz.x = o->pts[i + 1][j].x;
            pkt.v[1].xyz.y = o->pts[i + 1][j].y;
            pkt.v[2].xyz.x = o->pts[i][jn].x;
            pkt.v[2].xyz.y = o->pts[i][jn].y;
            pkt.v[3].xyz.x = o->pts[i + 1][jn].x;
            pkt.v[3].xyz.y = o->pts[i + 1][jn].y;
            if (func_00104520(o->model, 0x1F) != 0) {
                a = (j + o->rot[i]) % 128;
                if (a < 0) {
                    a += 128;
                }
                b = (j + 1 + o->rot[i]) % 128;
                if (b < 0) {
                    b += 128;
                }
                ((Pkt_b037_01E03E90 *)(s32)&pkt)->count |= 0x800;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[0].uv)->u.c = o->pts[i][a].x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[0].uv)->v.c = o->pts[i][a].y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[1].uv)->u.c = o->pts[i + 1][a].x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[1].uv)->v.c = o->pts[i + 1][a].y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[2].uv)->u.c = o->pts[i][b].x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[2].uv)->v.c = o->pts[i][b].y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[3].uv)->u.c = o->pts[i + 1][b].x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[3].uv)->v.c = o->pts[i + 1][b].y - 0x7200;
            } else {
                ((Pkt_b037_01E03E90 *)(s32)&pkt)->count |= 0x800;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[0].uv)->u.c = pkt.v[0].xyz.x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[0].uv)->v.c = pkt.v[0].xyz.y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[1].uv)->u.c = pkt.v[1].xyz.x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[1].uv)->v.c = pkt.v[1].xyz.y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[2].uv)->u.c = pkt.v[2].xyz.x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[2].uv)->v.c = pkt.v[2].xyz.y - 0x7200;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[3].uv)->u.c = pkt.v[3].xyz.x - 0x6C00;
                ((Uv_b037_01E03E90 *)(s32)&pkt.v[3].uv)->v.c = pkt.v[3].xyz.y - 0x7200;
            }
            if (func_00104520(o->model, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                func_002075F0((s32)&pkt, 0, 0);
            } else {
                func_002075F0((s32)&pkt, 0, o->z);
            }
        }
    }
    func_00207FD0(ot, (s32)func_00207500(), 0);
    return 0;
}

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b025_01E01EF0;

typedef struct {
    f32 x, y, z, w;
} Vec_b025_01E01EF0;

typedef struct {
    u8 pad00[7];
    u8 col;
    u8 pad08[0x2E];
    s16 life;
    s16 max;
    s16 used;
} Trail_b025_01E01EF0;

static s32 func_01E04530_b037(Trail_b025_01E01EF0 *o, Pt_b025_01E01EF0 *pts, Vec_b025_01E01EF0 *pos) {
    s32 k;

    if (o->used <= o->max - 1) {
        o->used++;
    }
    for (k = o->used; k > -1; k--) {
        if (pts[k].e > o->life) {
            o->used = k;
        }
    }
    for (k = o->used; k > 0; k--) {
        pts[k].x = pts[k - 1].x;
        pts[k].y = pts[k - 1].y;
        pts[k].z = pts[k - 1].z;
        pts[k].d = pts[k - 1].d;
        pts[k].e = pts[k - 1].e;
        pts[k].c = pts[k - 1].c;
    }
    pts[0].x = pos->x;
    pts[0].y = pos->y;
    pts[0].z = pos->z;
    pts[0].d = 0;
    pts[0].e = 0;
    pts[0].c = o->col;
    return 0;
}

/* shape b025:01E01FD0 (LkEFF_SortFieldThing), 616 insns, 9 copies: b013:01E02BE0's billboard particles with the points
   passed in (pts) and no count multiplier: per point the atlas cell of its frame (row- or column-major), frame advance
   every rate ticks, x jittered by rand() % 4 - 2 when the frame wraps, optional growth with age; depth-sorted unless
   flag 0x13. The fourth corner's depth goes to depth[1] (as in the original). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E01FD0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b025_01E01FD0;

typedef struct {
    Uv_b025_01E01FD0 uv;
    Xyz_b025_01E01FD0 p;
} Vtx_b025_01E01FD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E01FD0 v[4];
    u8 tail[0x20];
} Pk_b025_01E01FD0;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b025_01E01FD0;

typedef struct {
    void *texture;
    u8 b4, b5, b6, b7;
    s32 flags;
    f32 size;
    u8 pad10[4];
    s16 cw;
    s16 ch;
    s16 u0;
    s16 v0;
    s16 aw;
    s16 ah;
    u8 f20[0x10];
    f32 grow;
    u8 pad34[4];
    s16 n0;
    s16 n1;
    s16 frames;
    s16 rate;
} Em_b025_01E01FD0;

typedef struct {
    Vec4f v[4];
} Quad_b025_01E01FD0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E01FD0;

static s32 func_01E04610_b037(s32 obj, Em_b025_01E01FD0 *o, Part_b025_01E01FD0 *pts, Cam_b025_01E01FD0 *cam) {
    extern Quad_b025_01E01FD0 D_01E06180_b037;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00205C90();
    extern void func_00103620();
    s32 n;
    f32 m[16];
    f32 depth[4];
    Quad_b025_01E01FD0 in;
    Vec4f out[4];
    Vec4f pos;
    Pk_b025_01E01FD0 pk __attribute__((aligned(8)));
    s32 i;
    s16 u;
    s16 v;
    f32 s;

    in = D_01E06180_b037;
    in.v[0].x = -o->size;
    in.v[0].y = o->size;
    in.v[1].x = o->size;
    in.v[1].y = o->size;
    in.v[2].x = -o->size;
    in.v[2].y = -o->size;
    in.v[3].x = o->size;
    in.v[3].y = -o->size;
    if (func_00104520(o->flags, 0x1F) != 0) {
        n = o->n0;
    } else {
        n = o->n1;
    }
    func_00205C90(m);
    for (i = 0; i < 4; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pk_b025_01E01FD0 *)(s32)&pk)->flags = 0x24;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->size = 9;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->pad4 = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    pk.r = o->b6;
    pk.g = o->b5;
    pk.b = o->b4;
    pk.q = 1.0f;
    for (i = 0; i < n; i++) {
        if (func_00104520(o->flags, 1) != 0) {
            u = o->u0 + o->cw * (pts[i].frame % (o->aw / o->cw));
            v = o->v0 + o->ch * (pts[i].frame / (o->aw / o->cw));
        } else {
            u = o->u0 + o->cw * (pts[i].frame / (o->ah / o->ch));
            v = o->v0 + o->ch * (pts[i].frame % (o->ah / o->ch));
        }
        if (pts[i].age % o->rate == 0) {
            pts[i].frame++;
            if (pts[i].frame > o->frames - 1) {
                pts[i].frame = 0;
                pts[i].x += func_0019A5C8() % 4 - 2;
            }
        }
        ((Pk_b025_01E01FD0 *)(s32)&pk)->flags |= 0x800;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->v = (v + o->ch - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->v = (v + o->ch - 1) * 16;
        pk.a = pts[i].c;
        if (func_00104520(o->flags, 0xF) != 0) {
            s = o->grow * pts[i].age;
        } else {
            s = 1.0f;
        }
        if (func_00104520(o->flags, 0x10) != 0) {
            func_00103620(&pts[i], o->f20);
        }
        pts[i].age++;
        pos.x = out[0].x * s + pts[i].x;
        pos.y = out[0].y * s + pts[i].y;
        pos.z = out[0].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        pos.x = out[1].x * s + pts[i].x;
        pos.y = out[1].y * s + pts[i].y;
        pos.z = out[1].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        pos.x = out[2].x * s + pts[i].x;
        pos.y = out[2].y * s + pts[i].y;
        pos.z = out[2].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        pos.x = out[3].x * s + pts[i].x;
        pos.y = out[3].y * s + pts[i].y;
        pos.z = out[3].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[1]) != 0) {
            o->flags |= 0x800000;
        }
        func_00208CB0(&pk, (u64)0xA | ((u64)u << 4) | ((u64)(u + o->cw - 1) << 14) | ((u64)v << 24) |
                               ((u64)(v + o->ch - 1) << 34));
        func_00208700(&pk, o->texture, 1);
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}


/* shape b037:01E04FB0 (b037), 989 insns, 1 copy: b037 scene manager: code >= 0 clears the scene, eight cameras, six
   joints, the field particles, two trail emitters, a 256-point spark emitter, twelve rings, the spiral and the shaver
   light; else follows the joints, feeds field particles, waits on func_001F7260 from 248 to 330, fades, draws rings
   from 243 and sparks from 123, then runs b037:01E05F30; returns 2/1/6/8 by tick */

typedef struct Rot_b037_01E04FB0 {
    s32 x, y, z, w;
} Rot_b037_01E04FB0;

typedef struct Crd_b037_01E04FB0 {
    Vec4f scale;
    Rot_b037_01E04FB0 rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b037_01E04FB0;

typedef struct Fld_b037_01E04FB0 {
    s32 tex;
    u8 b, g, r, a;
    s32 flags;
    f32 size;
    s16 s10, s12;
    s16 cw, ch;
    s16 u0, v0;
    s16 aw, ah;
    u8 pad20[0x10];
    f32 grow;
    s16 h34;
    s16 life;
    s16 max;
    s16 used;
    s16 frames;
    s16 rate;
} Fld_b037_01E04FB0;

typedef struct Part_b037_01E04FB0 {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b037_01E04FB0;

typedef struct Spiral_b037_01E04FB0 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 h;
    f32 dy;
    f32 f14;
    f32 scale;
    s32 count;
    s16 u, v, w, hh;
    u8 pad28[8];
    Vec4f pts[30];
} Spiral_b037_01E04FB0;

typedef struct Shav_b037_01E04FB0 {
    s32 model;
    u8 col[4];
    u8 pad8[4];
    s32 z;
    s16 pts[4][128][2];
    s16 rot[4];
    u8 padDF8[8];
} Shav_b037_01E04FB0;

typedef struct Dot_b037_01E04FB0 {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Dot_b037_01E04FB0;

typedef struct Emit2_b037_01E04FB0 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 cx, cy, cz, cw;
    s16 u, v, w, h;
    s16 s28, s2A, s2C, s2E;
    Dot_b037_01E04FB0 pts[16];
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
} Emit2_b037_01E04FB0;

typedef struct Pt_b037_01E04FB0 {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b037_01E04FB0;

typedef struct Emit_b037_01E04FB0 {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 uv[8];
    Pt_b037_01E04FB0 *pts;
    s32 rots;
    s32 x48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b037_01E04FB0;

typedef struct Ring_b037_01E04FB0 {
    s32 type;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b037_01E04FB0;

typedef struct Scene_b037_01E04FB0 {
    Crd_b037_01E04FB0 c0;
    Fld_b037_01E04FB0 fld;
    Part_b037_01E04FB0 pts[0x24];
    Crd_b037_01E04FB0 c2F0;
    Spiral_b037_01E04FB0 spiral;
    Crd_b037_01E04FB0 c570;
    Shav_b037_01E04FB0 shav;
    Crd_b037_01E04FB0 cE00;
    Emit2_b037_01E04FB0 emitA;
    Crd_b037_01E04FB0 cFC0;
    Emit2_b037_01E04FB0 emitB;
    Crd_b037_01E04FB0 c1180;
    Crd_b037_01E04FB0 c11F0;
    Emit_b037_01E04FB0 emit;
    Pt_b037_01E04FB0 pts2[0x100];
    Crd_b037_01E04FB0 c22C0;
    Ring_b037_01E04FB0 ringA[4];
    Ring_b037_01E04FB0 ringB[4];
    Ring_b037_01E04FB0 ringC[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 j[6];
    u8 pad5354[4];
    u8 colA[4];
    u8 colB[4];
    u8 colC[4];
    u8 fade;
    u8 pad5365[0xB];
} Scene_b037_01E04FB0;

static s32 func_01E04FB0_b037(s32 arg0, s32 code) {
    Scene_b037_01E04FB0 *g = (Scene_b037_01E04FB0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F57C0(s32, s32);
    extern void func_001F6D00(s32);
    extern void func_001F7260(s32);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern s32 func_0019A5C8();
    extern void b037_01E05F30();
    Vec4f v[2];
    Vec4f w;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 a;
    f32 ang;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x5370);
        func_00103890(&g->c0);
        func_00103890(&g->c2F0);
        func_00103890(&g->cFC0);
        func_00103890(&g->c570);
        func_00103890(&g->cE00);
        func_00103890(&g->c1180);
        func_00103890(&g->c11F0);
        func_00103890(&g->c22C0);
        g->j[0] = func_001F5560(func_001F53A0(), 0x30, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x31, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x4A, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x52, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x60, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x6A, 0);
        g->timer = 0x154;
        g->t = 1;
        g->code = code;
        g->fade = 0x80;
        g->colA[0] = 0x80;
        g->colA[1] = 0x80;
        g->colA[2] = 0x80;
        g->colA[3] = 0;
        g->colB[2] = 0x30;
        g->colB[1] = 0x60;
        g->colB[0] = 0x80;
        g->colB[3] = 0;
        g->colC[2] = 0x80;
        g->colC[1] = 0x80;
        g->colC[0] = 0x80;
        g->colC[3] = 0x60;
        func_00103290(tx, 0);
        g->emitB.texture = tx[0];
        g->emitB.flags = 7;
        g->emitB.cx = 0.0f;
        g->emitB.cy = 0.0f;
        g->emitB.cz = 0.0f;
        g->emitB.u = 0;
        g->emitB.v = 0;
        g->emitB.w = 0x20;
        g->emitB.h = 0x20;
        g->emitB.s28 = 0;
        g->emitB.s2A = 0;
        g->emitB.s2C = 0x80;
        g->emitB.s2E = 0x40;
        g->emitB.size = 6.0f;
        g->emitB.count = 0x10;
        g->emitB.step = 2;
        g->emitB.s13C = 0;
        g->emitB.s140 = 8;
        g->emitB.s136 = 0xA;
        g->emitB.s138 = 0xA;
        g->emitB.r = 0x80;
        g->emitB.g = 0x80;
        g->emitB.b = 0x80;
        g->emitB.a = 0x40;
        for (i = 0; i < 8; i++) {
            g->emitB.pts[i].x = func_0019A5C8() % 20 - 10;
            g->emitB.pts[i].y = func_0019A5C8() % 20 - 10;
            g->emitB.pts[i].life = -g->emitB.step * i;
            g->emitB.pts[i].pad = 0;
            g->emitB.s13E = g->emitB.s140 - 1;
        }
        g->emit.tex = tx[0];
        g->emit.flags = 0x50000003;
        g->emit.c[2] = 0x80;
        g->emit.c[1] = 0x80;
        g->emit.c[0] = 0x80;
        g->emit.c[3] = 0x80;
        g->emit.size = 1.0f;
        g->emit.rot[0] = 0;
        g->emit.rot[1] = 0x800;
        g->emit.rot[2] = 0;
        g->emit.uv[0] = 0;
        g->emit.uv[1] = 0;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0;
        g->emit.uv[5] = 0;
        g->emit.uv[6] = 0x80;
        g->emit.uv[7] = 0x40;
        g->emit.pts = g->pts2;
        g->emit.rots = 0;
        g->emit.x48 = 0;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        func_01E017E0_b037((Ring_b001_01E01B20 *)&g->emit, 2.0f);
        for (i = 0; i < g->emit.count; i++) {
            g->pts2[i].t = -(func_0019A5C8() % 12);
            g->pts2[i].a = 0;
            g->pts2[i].frame = func_0019A5C8() % 8;
            g->pts2[i].y += 20.0f;
        }
        for (i = 0; i < 4; i++) {
            g->ringA[i].flags = 0x60000000;
            g->ringA[i].u = 0;
            g->ringA[i].v = 0x20;
            g->ringA[i].w = 0x20;
            g->ringA[i].h = 0x10;
            g->ringA[i].r = 0x80;
            g->ringA[i].g = 0x80;
            g->ringA[i].b = 0x80;
            g->ringA[i].a = 0x80;
            g->ringB[i].flags = 0x60000000;
            g->ringB[i].u = 0;
            g->ringB[i].v = 0x20;
            g->ringB[i].w = 0x20;
            g->ringB[i].h = 0x10;
            g->ringB[i].r = 0x80;
            g->ringB[i].g = 0x80;
            g->ringB[i].b = 0x80;
            g->ringB[i].a = 0x80;
        }
        { f32 fs2 = 6.0f; f32 fs3 = 4.0f; f32 fs4 = 0.0f; f32 fs5 = 0.0f; func_01E03260_b037(&g->ringA[0], tx[0], fs2, fs3, fs4, fs5); }
        { f32 fs2 = 3.75f; f32 fs3 = 4.0f; f32 fs5 = 0.0f; func_01E03260_b037(&g->ringB[0], tx[0], fs2, fs3, 0.0f, fs5); }
        { f32 fs2 = 8.0f; f32 fs4 = 0.0f; func_01E03260_b037(&g->ringA[1], tx[0], fs2, 6.0f, fs4, 0.0f); }
        { f32 fs2; f32 fs3; f32 fs4; f32 fs5; fs2 = 5.75f; fs3 = 6.0f; fs4 = 0.0f; fs5 = 0.0f; func_01E03260_b037(&g->ringB[1], tx[0], fs2, fs3, fs4, fs5); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 z = 0.0f; b037_01E03260(&g->ringA[2], tx[0], 10.0f, 8.0f, z, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 fs2; f32 fs3; f32 fs4; f32 fs5; fs5 = 0.0f; fs4 = 0.0f; fs3 = 8.0f; fs2 = 7.75f; b037_01E03260(&g->ringB[2], tx[0], fs2, fs3, fs4, fs5); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 fs2; f32 fs3; fs3 = 10.0f; fs2 = 12.0f; b037_01E03260(&g->ringA[3], tx[0], fs2, fs3, 0.0f, 0.0f); }
        { f32 fs2; f32 fs3; f32 fs4; fs4 = 0.0f; fs3 = 10.0f; fs2 = 9.75f; func_01E03260_b037(&g->ringB[3], tx[0], fs2, fs3, fs4, 0.0f); }
        func_00103260(tx, 0xF);
        for (i = 0; i < 4; i++) {
            g->ringC[i].flags = 0x20000000;
            g->ringC[i].u = 0x8E;
            g->ringC[i].v = 0;
            g->ringC[i].w = 0x20;
            g->ringC[i].h = 0x80;
            g->ringC[i].r = 0x70;
            g->ringC[i].g = 0x40;
            g->ringC[i].b = 0xA0;
            g->ringC[i].a = 0x40;
        }
        { f32 fc; fc = 0.0f; func_01E03260_b037(&g->ringC[0], tx[0], 4.25f, 3.75f, fc, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); b037_01E03260(&g->ringC[1], tx[0], 6.25f, 5.75f, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32); f32 fa; fa = 8.25f; b037_01E03260(&g->ringC[2], tx[0], fa, 7.75f, 0.0f, 0.0f); }
        { extern s32 b037_01E03260(void *, s32, f32, f32, f32, f32);  b037_01E03260(&g->ringC[3], tx[0], 10.25f, 9.75f, 0.0f, 0.0f); }
        g->fld.tex = tx[0];
        g->fld.r = 0x30;
        g->fld.g = 0x60;
        g->fld.b = 0x80;
        g->fld.a = 0x30;
        g->fld.flags = 0x9003;
        g->fld.size = 3.0f;
        g->fld.s10 = 0x80;
        g->fld.s12 = 0xC0;
        g->fld.cw = 0x20;
        g->fld.ch = 0x20;
        g->fld.u0 = 0x80;
        g->fld.v0 = 0xC0;
        g->fld.aw = 0x80;
        g->fld.ah = 0x100;
        g->fld.grow = 0.3f;
        g->fld.h34 = 0;
        g->fld.life = 0x18;
        g->fld.max = 0x24;
        g->fld.used = 0;
        g->fld.frames = 8;
        g->shav.model = 0xA0081000;
        g->shav.col[2] = 0x80;
        g->shav.col[1] = 0x80;
        g->shav.col[0] = 0x80;
        g->shav.col[3] = 0x80;
        g->spiral.tex = tx[0];
        g->spiral.flags = 1;
        g->spiral.r = 0x20;
        g->spiral.g = 0xA0;
        g->spiral.b = 0xB0;
        g->spiral.a = 0xFF;
        g->spiral.h = 0.8f;
        g->spiral.dy = 0.1f;
        g->spiral.f14 = 30.0f;
        g->spiral.scale = 0.05f;
        g->spiral.count = 0;
        g->spiral.u = 0x8E;
        g->spiral.v = 0x54;
        g->spiral.w = 0x20;
        g->spiral.hh = 0x2C;
        for (a = 0; a < 30; a++) {
            ang = 0.20943952f * (f32)a;
            g->spiral.pts[a].x = func_0020B620(ang);
            g->spiral.pts[a].z = func_0020B730(ang);
            g->spiral.pts[a].y = 0.0f;
        }
        func_00103260(tx, 1);
        g->emitA.texture = tx[0];
        g->emitA.flags = 0x403;
        g->emitA.cx = 0.0f;
        g->emitA.cy = 0.0f;
        g->emitA.cz = 0.0f;
        g->emitA.cw = 0.0f;
        g->emitA.s28 = 0;
        g->emitA.s2A = 0;
        g->emitA.w = 0x18;
        g->emitA.h = 0x20;
        g->emitA.s2C = 0x80;
        g->emitA.s2E = 0x40;
        g->emitA.size = 12.0f;
        g->emitA.count = 0x10;
        g->emitA.step = 2;
        g->emitA.s13C = 1;
        g->emitA.s140 = 0xA;
        g->emitA.s136 = 0xA;
        g->emitA.s138 = 0xA;
        g->emitA.r = 0x80;
        g->emitA.g = 0x80;
        g->emitA.b = 0x80;
        g->emitA.a = 0;
        func_01E00280_b037((Trail_b037_01E00280 *)&g->emitA);
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j[0], &v[0]);
    func_001F5620(func_001F53A0(), g->j[1], &v[1]);
    func_001F5F90(func_001F5380(), &g->cFC0.pos);
    func_001F53C0(1, func_001F53A0(), &g->cE00.pos);
    func_001F5620(func_001F53A0(), g->j[0], &g->c1180.pos);
    if (((g->t >= 0x19 && g->t < 0x20) || (g->t >= 0x32 && g->t < 0x41) || (g->t >= 0x4A && g->t < 0x7B)) &&
        g->t % 2 == 0) {
        if (func_0019A5C8() % 2) {
            func_001F5620(func_001F53A0(), g->j[5], &w);
        } else {
            func_001F5620(func_001F53A0(), g->j[4], &w);
        }
        func_01E04530_b037((Trail_b025_01E01EF0 *)&g->fld, (Pt_b025_01E01EF0 *)g->pts, (Vec_b025_01E01EF0 *)&w);
    }
    func_001F5F90(func_001F5380(), &g->c570.pos);
    func_001F5F90(func_001F5380(), &g->c22C0.pos);
    if (g->c22C0.pos.z > 0.0f) {
        g->c22C0.rot.y = 0x8000;
    }
    if (g->t == 0x7B) {
        func_001F5620(func_001F53A0(), g->j[0], &g->c2F0.pos);
    }
    func_00103DB0(&v[0], &v[1], &g->c2F0.rot);
    g->c2F0.pos.x = v[1].x;
    g->c2F0.pos.y = v[1].y;
    g->c2F0.pos.z = v[1].z;
    func_00103DB0(&v[1], &v[0], &g->c1180.rot);
    func_001038D0(&g->c0);
    func_001038D0(&g->c570);
    func_001038D0(&g->c2F0);
    func_001038D0(&g->c1180);
    func_001039A0(&g->cFC0);
    func_001039A0(&g->cE00);
    func_001038D0(&g->c22C0);
    if (g->t >= 0xE9) {
        func_001F57C0(func_001F53A0(), 1);
    }
    if (g->t >= 0xF8 && g->t < 0x14A) {
        func_001F7260(1);
    } else if (g->t == 0x14A) {
        func_001F7260(0);
    }
    func_001F6D00(g->fade);
    if (g->t >= 0x7B && g->t < 0xF8) {
        func_00103470(&g->fade, 0x30, 2);
    }
    if (g->t >= 0x14A) {
        func_001032C0(&g->fade, 0x80, 0x10);
    }
    if (g->t >= 0x125) {
        func_01E00120_b037(ot, (Src_b000_01E00400 *)g->colA);
        func_001032C0(&g->colA[3], 0xFF, 8);
    }
    func_01E00F70_b037(g->colC);
    if (g->t >= 0xE9) {
        func_00103470(&g->colC[3], 0, 6);
    }
    if (g->t < 0xD1) {
        w.x = w.y = w.z = 0.0f;
        func_01E003E0_b037(ot, (Cam_b001_01E00A30 *)&g->cE00, (Emit_b001_01E00A30 *)&g->emitA, (Vec_b001_01E00A30 *)&w);
        if (g->t > 0x5D && g->t < 0x7B) {
            func_001032C0(&g->emitA.a, 0x20, 2);
        } else if (g->t > 0x7B) {
            func_00103470(&g->emitA.a, 0, 2);
        }
    }
    func_01E04610_b037(ot, (Em_b025_01E01FD0 *)&g->fld, (Part_b025_01E01FD0 *)g->pts, (Cam_b025_01E01FD0 *)&g->c0);
    for (i = 0; i < g->fld.used; i++) {
        func_00103470(&g->pts[i].c, 0, 2);
    }
    if (g->t > 0x94) {
        func_00103470(&g->fld.a, 0, 8);
    }
    if (g->t >= 0xF3) {
        for (i = 0; i < 4; i++) {
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringC[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringA[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_01E03420_b037(ot, (Ring_b037_01E03420 *)&g->ringB[i], (Cam_b037_01E03420 *)&g->c22C0);
            func_00103470(&g->ringA[i].a, 0, 8);
            func_00103470(&g->ringB[i].a, 0, 8);
            func_00103470(&g->ringC[i].a, 0, 4);
        }
        if (g->c22C0.pos.z > 0.0f) {
            g->c22C0.rot.z -= 0x300;
        } else {
            g->c22C0.rot.z += 0x300;
        }
        func_001033D0(&g->c22C0, 3.0f, 0.1f);
    }
    if (g->t >= 0x7B) {
        func_01E01970_b037(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->c1180);
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts2[i].t >= 0) {
                g->pts2[i].y -= 2.0f;
                func_001032C0(&g->pts2[i].a, 0x80, 8);
                if (g->pts2[i].y > 0.0f) {
                    g->pts2[i].z *= 0.8f;
                    g->pts2[i].x *= 0.8f;
                }
                if (g->pts2[i].y < 0.0f) {
                    a = func_0019A5C8() % 0x10000;
                    g->pts2[i].z = g->emit.radius * func_0020B480(a);
                    g->pts2[i].x = g->emit.radius * func_0020B550(a);
                    g->pts2[i].y = 20.0f + (f32)(func_0019A5C8() % 10);
                    g->pts2[i].a = 0;
                }
            }
        }
        if (g->t >= 0xD1) {
            func_00103470(&g->emit.c[3], 0, 2);
        }
        b037_01E05F30(g, ot);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x14A) {
        return 2;
    }
    if (g->t == 0xAE) {
        return 1;
    }
    if (g->t >= 0xD1 && g->t < 0x14A) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b037:01E05F30 (b037_Shaver), 141 insns, 1 copy: the b037 module's late-scene step (scene time s32 at
   ctx+0x5334): from 124 to 232 runs b037:01E010B0 with a random dark colour, a counter at 0x37C growing 10 from 184
   and clearing 8 bytes at 0x36B past 300; from 209 runs b037:01E003E0 at the origin (clearing 4 bytes at 0x103B from
   243); from 248 places a light at the scene point (b037:01E03BD0/01E03E90) and spreads three angles by 2, then 1
   (from 293), then 1 every other tick (from 308) */

typedef struct {
    u8 pad0[0x2F0];
    u8 m2F0[0x70];
    u8 m360[8];
    s8 col[3];
    u8 m36B[0x37C - 0x36B];
    s32 n37C;
    u8 pad380[0x570 - 0x380];
    u8 m570[0x70];
    u8 m5E0[0xC];
    s32 w5EC;
    u8 pad5F0[0xDF0 - 0x5F0];
    s16 a0;
    s16 a1;
    s16 a2;
    u8 padDF6[0xFC0 - 0xDF6];
    u8 mFC0[0x20];
    u8 mFE0[0x50];
    u8 m1030[0xB];
    u8 m103B[0x5334 - 0x103B];
    s32 time;
} Ctx_b037_01E05F30;

extern void b037_01E003E0(s32, void *, void *, s32 *);
extern void b037_01E010B0(s32, void *, void *);
extern void b037_01E03BD0(void *, void *, f32, f32, f32);
extern void b037_01E03E90(void *);

static void func_01E05F30_b037(Ctx_b037_01E05F30 *g, s32 arg) {
    extern void func_00103470(void *, s32, s32);
    extern s32 func_00205D10(void *, f32);
    s32 v[4];
    f32 r;

    if (g->time > 123 && g->time < 233) {
        b037_01E010B0(arg, g->m360, g->m2F0);
        g->col[2] = func_0019A5C8() % 128;
        g->col[1] = func_0019A5C8() % 128;
        g->col[0] = func_0019A5C8() % 128;
        if (g->time >= 184) {
            g->n37C += 10;
        }
        if (g->n37C > 300) {
            func_00103470(g->m36B, 0, 8);
        }
    }
    if (g->time >= 209) {
        v[0] = v[1] = v[2] = 0;
        b037_01E003E0(arg, g->mFC0, g->m1030, v);
        if (g->time >= 243) {
            func_00103470(g->m103B, 0, 4);
        }
    }
    if (g->time >= 248) {
        g->w5EC = func_00205D10(g->mFE0, r = 10.0f);
        b037_01E03BD0(g->m5E0, g->m570, 4.0f, 10.0f, 0.0f);
        b037_01E03E90(g->m5E0);
        if (g->time < 293) {
            g->a0 += 2;
            g->a1 -= 2;
            g->a2 += 2;
        } else if (g->time < 308) {
            g->a0 += 1;
            g->a1 -= 1;
            g->a2 += 1;
        } else if (g->time % 2 == 0) {
            g->a0 += 1;
            g->a1 -= 1;
            g->a2 += 1;
        }
    }
}

