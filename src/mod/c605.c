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

static void func_01E00080_c605(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_c605(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
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

static s32 func_01E00330_c605(void *arg0, s32 arg1, f32 *arg2) {
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

static s32 func_01E00440_c605(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_c605((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E00FD0_c605(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_c605((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape c605:01E028C0 (LkSortEraseCard), 352 insns, 1 copy: c602:01E01620-style card quad wiped from the bottom:
   lower corners at height 184 - h, UVs cut to the visible rows (h / 368), the object's three texture words copied
   into the packet tail, drawn at far z or the corners' mean depth once all four corners project */

typedef struct {
    u8 b, g, r, a;
} Src_c605_01E028C0;

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
} Vtx_c605_01E028C0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_c605_01E028C0;

typedef struct {
    u64 v;
} Save1_c605_01E028C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c605_01E028C0 v[4];
    u8 pad70[8];
    Save1_c605_01E028C0 t0, t1, t2;
} Pkt_c605_01E028C0;

typedef struct {
    Vec4f v[4];
} Tbl_c605_01E028C0;

typedef struct {
    u8 pad0[0x60];
    Save1_c605_01E028C0 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c605_01E028C0;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 h;
    Src_c605_01E028C0 color;
    s16 u, v, w, hh;
} Spr_c605_01E028C0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c605_01E028C0;

static void func_01E00080_c605();

static s32 func_01E028C0_c605(Obj_c605_01E028C0 *o, Cam_c605_01E028C0 *cam, Spr_c605_01E028C0 *spr) {
    extern Tbl_c605_01E028C0 D_01E03E00_c605;
    extern s32 func_001D9F00();
    extern void func_001DA7A0();
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Tbl_c605_01E028C0 pts;
    Pkt_c605_01E028C0 pkt;
    s32 lit;
    f32 f;
    f32 k;

    f = 184.0f - spr->h;
    pts = D_01E03E00_c605;
    pts.v[2].y = f;
    pts.v[3].y = f;
    lit = func_001D9F00(o, 1);
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c605(&pkt, &spr->color);
    k = spr->hh * (spr->h / 368.0f);
    ((Pkt_c605_01E028C0 *)(s32)&pkt)->count |= 0x800;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[0].tc)->u = spr->u * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[0].tc)->v = spr->v * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[1].tc)->u = (spr->u + spr->w - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[1].tc)->v = spr->v * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[2].tc)->u = spr->u * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[2].tc)->v = (spr->v + (s32)k - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[3].tc)->u = (spr->u + spr->w - 1) * 16;
    ((UV_c605_01E028C0 *)(s32)&pkt.v[3].tc)->v = (spr->v + (s32)k - 1) * 16;
    if (func_00205440(&pts.v[0], cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
        spr->flags |= 0x100000;
    }
    if (func_00205440(&pts.v[1], cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
        spr->flags |= 0x200000;
    }
    if (func_00205440(&pts.v[2], cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
        spr->flags |= 0x400000;
    }
    if (func_00205440(&pts.v[3], cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
        spr->flags |= 0x800000;
    }
    if (lit != 0) {
        func_001DA7A0(o->f90, o);
    } else {
        func_001DA7A0(0, o);
    }
    pkt.t0 = o->t0;
    pkt.t1 = o->t1;
    pkt.t2 = o->t2;
    if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
        func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
        if (func_00104520(spr->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, 0, 0);
        } else {
            func_002075F0(&pkt, 0, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
    }
    spr->flags &= 0xFF0FFFFF;
    return 0;
}

/* shape c605:01E02E40 (c605), 881 insns, 1 copy: the c605 module main (c604:01E037D0's two-unit card form): needs
   unit A; on start copies and flags both units' cards, aims them at -150/150, sets up two 16-point emitters, the two
   erase sprites (h 368) and two 256-flake emitters; each tick turns the views, side 2/3 and 1/3 draw emitter, flakes
   (c605_CrushCard through an alias) and the erasing card shrinking by 18.4, then flips the cards back when bit
   0x1F/0x1E is set; 8 when the timer ends or after tick 35 on side 0; float arguments as block locals */

typedef struct {
    u8 b, g, r, a;
} Col_c605_01E02E40;

typedef struct {
    f32 x, y, z;
    u8 padC[0x64];
} Crd_c605_01E02E40;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 h;
    Col_c605_01E02E40 color;
    s16 u, v, w, hh;
    s16 u0, v0;
    u8 pad1C[0x1A04];
} Erase_c605_01E02E40;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_c605_01E02E40;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c605_01E02E40 color;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_c605_01E02E40 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Em1_c605_01E02E40;

typedef struct {
    s32 x, y, z, w;
} I4_c605_01E02E40;

typedef struct {
    Vec4f pos;
    I4_c605_01E02E40 a;
    s32 b[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x49];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c605_01E02E40;

typedef struct {
    Vec4f pos;
    I4_c605_01E02E40 a;
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 steps;
    u8 pad4C[4];
} Ctl_c605_01E02E40;

typedef struct {
    f32 x, y;
    s32 z;
    u8 a;
    u8 b;
    s16 t;
} Flake_c605_01E02E40;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 f20, f24, f28;
    u8 pad2C[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Flake_c605_01E02E40 *parts;
    s32 f44;
    s32 f48;
    f32 radius;
    f32 f50;
    u8 pad54[6];
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_c605_01E02E40;

typedef struct {
    u8 pad00[0x10];
    s32 a[3];
    u8 pad1C[0x27];
    u8 f43;
} Src_c605_01E02E40;

typedef struct {
    Crd_c605_01E02E40 cam0;
    Crd_c605_01E02E40 cam1;
    Crd_c605_01E02E40 cam2;
    Erase_c605_01E02E40 sprA;
    Erase_c605_01E02E40 sprB;
    Em1_c605_01E02E40 emA;
    Em1_c605_01E02E40 emB;
    Unit_c605_01E02E40 cardA;
    Unit_c605_01E02E40 cardB;
    Ctl_c605_01E02E40 ctlA;
    Ctl_c605_01E02E40 ctlB;
    Emit_c605_01E02E40 emitA;
    Emit_c605_01E02E40 emitB;
    Flake_c605_01E02E40 ptsA[0x100];
    Flake_c605_01E02E40 ptsB[0x100];
    s32 tex;
    f32 dist;
    s32 timer;
    s32 side;
    s32 alpha;
    s32 tick;
    s32 flags;
    u8 pad5AEC[8];
    s32 w5AF4;
    s32 w5AF8;
    s32 cntA;
    s32 cntB;
    u8 pad5B04[0xC];
} Scene_c605_01E02E40;

static s32 func_01E02E40_c605(s32 arg0, s32 code) {
    Scene_c605_01E02E40 *g = (Scene_c605_01E02E40 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103260(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00205C40();
    extern void c605_01E03C10();
    Vec4f v;
    s32 ot;
    s32 idA;
    s32 idB;
    Src_c605_01E02E40 *a;
    Src_c605_01E02E40 *b;
    s32 rv;
    s32 i;
    s32 fp;

    ot = (s32)func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Src_c605_01E02E40 *)func_001F5B30(idA);
    b = (Src_c605_01E02E40 *)func_001F5B30(idB);
    rv = 0;
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
        func_00195108(g, 0x5B10);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        if (a) {
            g->cardA = *(Unit_c605_01E02E40 *)a;
        }
        if (b) {
            g->cardB = *(Unit_c605_01E02E40 *)b;
        }
        if (a) {
            func_001F59D0(idA, 1);
            g->cardA.b6 = 1;
            g->cardA.b5 = 1;
        }
        if (b) {
            func_001F59D0(idB, 1);
            g->cardB.b6 = 1;
            g->cardB.b5 = 1;
        }
        g->side = code;
        g->flags = 0;
        g->tick = 0;
        if (a) {
            a->f43 = 0;
        }
        if (b) {
            b->f43 = 0;
        }
        g->alpha = 0x80;
        g->w5AF4 = g->w5AF8 = 0x10;
        g->cntA = g->cntB = 0x17;
        g->ctlA.steps = 0x14;
        g->ctlA.x = -150.0f;
        g->ctlA.y = 0.0f;
        func_00205CB0(&g->cardA, g->ctlA.x, g->ctlA.y);
        g->ctlA.pos = ((Unit_c605_01E02E40 *)a)->pos;
        func_00205C40(g->cardA.b);
        g->ctlA.b[0] = g->ctlA.b[1] = g->ctlA.b[2] = 0;
        g->cardA.a.x = 0;
        g->cardA.a.y = 0x10000;
        g->cardA.a.z = 0x10000;
        g->ctlA.a = ((Unit_c605_01E02E40 *)a)->a;
        g->ctlA.f30 = g->ctlA.f34 = 0.1f;
        g->cardA.f30 = g->cardA.f34 = 1.0f;
        if (b) {
            g->ctlB.steps = 0x14;
            g->ctlB.x = 150.0f;
            g->ctlB.y = 0.0f;
            func_00205CB0(&g->cardB, g->ctlB.x, g->ctlB.y);
            g->ctlB.pos = ((Unit_c605_01E02E40 *)b)->pos;
            func_00205C40(g->cardB.b);
            g->ctlB.b[0] = g->ctlB.b[1] = g->ctlB.b[2] = 0;
            g->cardB.a.x = 0;
            g->cardB.a.y = 0x10000;
            g->cardB.a.z = 0x10000;
            g->ctlB.a = ((Unit_c605_01E02E40 *)b)->a;
            g->ctlB.f30 = g->ctlB.f34 = 0.1f;
            g->cardB.f30 = g->cardB.f34 = 1.0f;
        }
        g->timer = 0x32;
        func_00103260(&g->tex, 1);
        g->emA.flags = g->emB.flags = 0x40080001;
        g->emA.tex = g->emB.tex = g->tex;
        g->emA.x = g->emB.x = 0.0f;
        g->emA.y = g->emB.y = -150.0f;
        g->emA.z = g->emB.z = 0.0f;
        g->emA.w1C = g->emB.w1C = 0;
        g->emA.h20 = g->emB.h20 = 0;
        g->emA.h22 = g->emB.h22 = 0;
        g->emA.w = g->emB.w = 0x18;
        g->emA.h = g->emB.h = 0x20;
        g->emA.tu = g->emB.tu = 0;
        g->emA.tv = g->emB.tv = 0;
        g->emA.tw = g->emB.tw = 0x80;
        g->emA.th = g->emB.th = 0x40;
        g->emA.size = g->emB.size = 100.0f;
        g->emA.count = g->emB.count = 0x10;
        g->emA.step = g->emB.step = 0;
        g->emA.h13C = g->emB.h13C = 1;
        g->emA.h140 = g->emB.h140 = 0xA;
        g->emA.color.r = g->emB.color.r = 0x80;
        g->emA.color.g = g->emB.color.g = 0x80;
        g->emA.color.b = g->emB.color.b = 0x80;
        g->emA.color.a = g->emB.color.a = 0x40;
        g->emA.angle = g->emB.angle = 0;
        for (i = 0; i < g->emB.count; i++) {
            g->emA.pts[i].x = g->emB.pts[i].x = g->emB.x + -160.0f + 20.0f * i;
            g->emA.pts[i].y = g->emB.pts[i].y = g->emB.y + (func_0019A5C8() % 32 - 16);
            g->emA.pts[i].z = g->emB.pts[i].z = g->emB.z;
            g->emA.pts[i].life = -g->emA.step * i;
            g->emB.pts[i].life = -g->emB.step * i;
            g->emA.pts[i].pad = func_0019A5C8() % 10;
            g->emB.pts[i].pad = func_0019A5C8() % 10;
            g->emA.h13E = g->emA.h140 - 1;
            g->emB.h13E = g->emB.h140 - 1;
        }
        g->sprA.flags = g->sprB.flags = 0x80801;
        g->sprA.h = g->sprB.h = 368.0f;
        g->sprA.u = g->sprB.u = 0;
        g->sprA.v = g->sprB.v = 0;
        g->sprA.u0 = g->sprB.u0 = 0;
        g->sprA.v0 = g->sprB.v0 = 0;
        g->sprA.w = g->sprB.w = 0x100;
        g->sprA.hh = g->sprB.hh = 0x170;
        g->sprA.color.r = g->sprB.color.r = 0x80;
        g->sprA.color.g = g->sprB.color.g = 0x80;
        g->sprA.color.b = g->sprB.color.b = 0x80;
        g->sprA.color.a = g->sprB.color.a = 0x80;
        g->emitA.tex = g->tex;
        g->emitA.flags = 0x50080003;
        g->emitA.r = 0x80;
        g->emitA.g = 0x80;
        g->emitA.b = 0x80;
        g->emitA.a = 0x80;
        g->emitA.size = 6.0f;
        g->emitA.f20 = 0;
        g->emitA.f24 = 0;
        g->emitA.f28 = 0;
        g->emitA.u = 0;
        g->emitA.v = 0;
        g->emitA.w = 0x20;
        g->emitA.h = 0x20;
        g->emitA.u0 = 0;
        g->emitA.v0 = 0;
        g->emitA.tw = 0x80;
        g->emitA.th = 0x40;
        g->emitA.parts = g->ptsA;
        g->emitA.f44 = 0;
        g->emitA.f48 = 0;
        g->emitA.radius = 15.0f;
        g->emitA.count = 0x100;
        g->emitA.nframes = 8;
        g->emitA.rate = 8;
        for (i = 0; i < g->emitA.count; i++) {
            g->ptsA[i].x = 0.1f * (func_0019A5C8() % 2560 - 1280);
            g->ptsA[i].y = (184.0f - g->sprA.h) + 0.1f * (func_0019A5C8() % 920);
            g->ptsA[i].z = 0;
            g->ptsA[i].t = -(func_0019A5C8() % 12);
            g->ptsA[i].a = 0x80;
            g->ptsA[i].b = 0;
        }
        g->emitB.tex = g->tex;
        g->emitB.flags = 0x50080003;
        g->emitB.r = 0x80;
        g->emitB.g = 0x80;
        g->emitB.b = 0x80;
        g->emitB.a = 0x80;
        g->emitB.size = 6.0f;
        g->emitB.f20 = 0;
        g->emitB.f24 = 0;
        g->emitB.f28 = 0;
        g->emitB.u = 0;
        g->emitB.v = 0;
        g->emitB.w = 0x20;
        g->emitB.h = 0x20;
        g->emitB.u0 = 0;
        g->emitB.v0 = 0;
        g->emitB.tw = 0x80;
        g->emitB.th = 0x40;
        g->emitB.parts = g->ptsB;
        g->emitB.f44 = 0;
        g->emitB.f48 = 0;
        g->emitB.radius = 15.0f;
        g->emitB.count = 0x100;
        g->emitB.nframes = 8;
        g->emitB.rate = 8;
        for (i = 0; i < g->emitB.count; i++) {
            g->ptsB[i].x = 0.1f * (func_0019A5C8() % 2560 - 1280);
            g->ptsB[i].y = (184.0f - g->sprB.h) + 0.1f * (func_0019A5C8() % 920);
            g->ptsB[i].z = 0;
            g->ptsB[i].t = -(func_0019A5C8() % 12);
            g->ptsB[i].a = 0x80;
            g->ptsB[i].b = 0;
        }
        g->cam0.x = g->cam0.y = g->cam0.z = 0.1f;
        return 0;
    }
    if (func_00104520(g->flags, 0x1F)) {
        g->dist = -150.0f;
    } else {
        g->dist = 150.0f;
    }
    { f32 fs2 = 0.0f; func_00103920(&g->cam0, g->dist, fs2); }
    { f32 fs1; f32 fs2; fs1 = -150.0f; fs2 = 0.0f; func_00103920(&g->cam1, fs1, fs2); }
    { f32 fs2 = 0.0f; func_00103920(&g->cam2, 150.0f, fs2); }
    if (g->side == 0) {
        g->flags |= 0xC0000000;
    }
    if (b == NULL && g->side == 1 && g->tick > 0x14) {
        g->flags |= 0x40000000;
    }
    if (b == NULL && g->side == 3 && g->tick > 0x14) {
        g->flags |= 0x40000000;
    }
    v.x = v.z = 0.0f;
    v.y = 16.0f;
    if (g->side == 2 || g->side == 3) {
        if (g->emA.y < 202.0f) {
            v.y = 16.0f;
        } else {
            v.y = 0.0f;
            func_00103470(&g->emA.color.a, 0, 8);
        }
        func_01E00440_c605(ot, (Cam_b001_01E00A30 *)&g->cam1, (Emit_b001_01E00A30 *)&g->emA,
                           (Vec_b001_01E00A30 *)&v);
        func_01E00FD0_c605(ot, (Emit_b000_01E01140 *)&g->emitA, (Cam_b000_01E01140 *)&g->cam1);
        c605_01E03C10(&g->sprA, &g->emitA, g->ptsA);
    }
    v.y = 16.0f;
    if (g->side == 1 || g->side == 3) {
        if (g->emB.y < 202.0f) {
            v.y = 16.0f;
        } else {
            v.y = 0.0f;
            func_00103470(&g->emB.color.a, 0, 8);
        }
        func_01E00440_c605(ot, (Cam_b001_01E00A30 *)&g->cam2, (Emit_b001_01E00A30 *)&g->emB,
                           (Vec_b001_01E00A30 *)&v);
        func_01E00FD0_c605(ot, (Emit_b000_01E01140 *)&g->emitB, (Cam_b000_01E01140 *)&g->cam2);
        c605_01E03C10(&g->sprB, &g->emitB, g->ptsB);
    }
    fp = func_00207F60();
    func_001D99F0();
    if (b) {
        if (g->side == 1 || g->side == 3) {
            func_01E028C0_c605((Obj_c605_01E028C0 *)&g->cardB, (Cam_c605_01E028C0 *)&g->cam2,
                               (Spr_c605_01E028C0 *)&g->sprB);
            { f32 fs2 = 18.4f; func_00103540(&g->sprB.h, 0.0f, fs2); }
            if (func_00104520(g->flags, 0x1E) == 0) {
                g->cntB--;
                if (g->cntB < 0) {
                    g->flags |= 0x40000000;
                }
            }
        }
    }
    if (g->side == 2 || g->side == 3) {
        func_01E028C0_c605((Obj_c605_01E028C0 *)&g->cardA, (Cam_c605_01E028C0 *)&g->cam1,
                           (Spr_c605_01E028C0 *)&g->sprA);
        { f32 fs1 = 0.0f; f32 fs2 = 18.4f; func_00103540(&g->sprA.h, fs1, fs2); }
        if (func_00104520(g->flags, 0x1F) == 0) {
            g->cntA--;
            if (g->cntA < 0) {
                g->flags |= 0x80000000;
            }
        }
    }
    if (b && (g->side == 2 || g->side == 0)) {
        if (func_00104520(g->flags, 0x1F)) {
            if (func_00104520(g->flags, 1) == 0) {
                if (func_01E00120_c605((Cam_c536_01E00120 *)&g->cardB, (Cam_c536_01E00120 *)&g->ctlB) == 0) {
                    g->flags |= 2;
                    g->cardB.a.x = b->a[0];
                    g->cardB.a.y = b->a[1];
                    g->cardB.a.z = b->a[2];
                    func_001F59D0(idB, 0);
                }
                func_01E00330_c605(&g->cardB, g->alpha, 0);
            }
        } else {
            func_01E00330_c605(&g->cardB, g->alpha, &g->ctlB.x);
        }
    }
    if (g->side == 1 || g->side == 0) {
        if (func_00104520(g->flags, 0x1E)) {
            if (func_00104520(g->flags, 0) == 0) {
                if (func_01E00120_c605((Cam_c536_01E00120 *)&g->cardA, (Cam_c536_01E00120 *)&g->ctlA) == 0) {
                    g->flags |= 1;
                    g->cardA.a.x = a->a[0];
                    g->cardA.a.y = a->a[1];
                    g->cardA.a.z = a->a[2];
                    func_001F59D0(idA, 0);
                }
                func_01E00330_c605(&g->cardA, g->alpha, 0);
            }
        } else {
            func_01E00330_c605(&g->cardA, g->alpha, &g->ctlA.x);
        }
    }
    func_001D9DD0();
    func_00207FD0(fp, (s32)func_00207500(), 0);
    g->tick++;
    if (--g->timer == 0) {
        rv = 8;
    }
    if (g->side == 0 && g->tick > 0x23) {
        rv = 8;
    }
    return rv;
}

/* shape c605:01E03C10, 116 insns: steps the falling flakes: each live flake sinks by 4, 5 or 6 (by its index) and clears its
   flags; each dead one is respawned at a random spot near the top at full alpha; clears the block flags when the scroll is 0 */

typedef struct {
    f32 x;
    f32 y;
    s32 z;
    u8 a;
    u8 b;
    s16 live;
} Flake_c605_01E03C10;

typedef struct {
    u8 pad0[8];
    f32 scroll;
} Scene_c605_01E03C10;

typedef struct {
    u8 pad0[0xB];
    u8 flags[0x4F];
    s16 count;
} Block_c605_01E03C10;

static void func_01E03C10_c605(Scene_c605_01E03C10 *s, Block_c605_01E03C10 *b, Flake_c605_01E03C10 *f) {
    extern void func_00103470(void *, u8, s32);
    s32 i;
    s32 live;

    for (i = 0; i < b->count; i++) {
        live = f->live;
        if (live != 0) {
            if (i % 3 == 0) {
                f->y -= 4.0f;
            } else if (i % 3 == 1) {
                f->y -= 5.0f;
            } else {
                f->y -= 6.0f;
            }
            func_00103470(&f->a, 0, 8);
        } else if ((s16)live == 0) {
            f->x = 0.1f * (f32)(func_0019A5C8() % 2560 - 0x500);
            f->y = (184.0f - s->scroll) + 0.1f * (f32)(func_0019A5C8() % 920);
            f->z = 0;
            f->live = 0;
            f->a = 0x80;
            f->b = 0;
        }
        f++;
    }
    if (s->scroll == 0.0f) {
        func_00103470(b->flags, 0, 0x20);
    }
}
