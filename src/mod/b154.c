#include "common.h"

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 p;
} Vtx_b049_01E00100;

typedef struct {
    u8 hdr[0x10];
    Vtx_b049_01E00100 v[4];
} Pkt_b049_01E00100;

static void func_01E00080_b154(Pkt_b049_01E00100 *p, u8 *c, s32 n) {
    s32 k;

    k = c[3] >> 3;
    p->v[0].r = c[2];
    p->v[0].g = c[1];
    p->v[0].b = c[0];
    if (n == 0) {
        p->v[0].a = 0;
    } else {
        p->v[0].a = c[3] - n * k;
    }
    p->v[0].q = 1.0f;
    p->v[1].r = c[2];
    p->v[1].g = c[1];
    p->v[1].b = c[0];
    if (n == 6) {
        p->v[1].a = 0;
    } else {
        p->v[1].a = c[3] - (k + n * k);
    }
    p->v[1].q = 1.0f;
    p->v[2].r = c[2];
    p->v[2].g = c[1];
    p->v[2].b = c[0];
    p->v[2].a = 0;
    p->v[2].q = 1.0f;
    p->v[3].r = c[2];
    p->v[3].g = c[1];
    p->v[3].b = c[0];
    p->v[3].a = 0;
    p->v[3].q = 1.0f;
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

static void func_01E00150_b154(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E001F0_b154(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00150_b154((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00D80_b154(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

/* shape b489:01E00240 (LkPrim_SortLineParticle), 853 insns, 55 copies: each live particle drawn as a camera-facing
   line quad from its position back along its direction (or straight down), texture-animated */

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b489_01E00240;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b489_01E00240;

typedef struct {
    UV_b489_01E00240 uv;
    Xyz_b489_01E00240 xyz;
} Vtx_b489_01E00240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b489_01E00240 v[4];
    u8 tail[0x20];
} Pkt_b489_01E00240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 age;
} Part_b489_01E00240;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    u8 pad28[4];
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b489_01E00240;

#define UV_b489_01E00240(k) ((UV_b489_01E00240 *)(s32)&pkt.v[k].uv)

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E00F40_b154(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_0020D070(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C60(f32);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f t;
    Xyz_b489_01E00240 q[2];
    Pkt_b489_01E00240 pkt __attribute__((aligned(8)));
    f32 dep[2];
    s32 i;
    f32 w;
    f32 dx;
    f32 dy;

    ((Pkt_b489_01E00240 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->tag = 9;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->r;
    pkt.g = e->g;
    pkt.b = e->b;
    pkt.a = e->a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
        UV_b489_01E00240(0)->u = e->u << 4;
        UV_b489_01E00240(0)->v = e->v << 4;
        UV_b489_01E00240(1)->u = e->u << 4;
        UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
        UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(2)->v = e->v << 4;
        UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
    }
    for (i = 0; i < e->count; i++) {
        if (e->parts[i].age >= 0) {
            if (e->parts[i].a < e->a) {
                pkt.a = e->parts[i].a;
            } else {
                pkt.a = e->a;
            }
            if (func_00104520(e->flags, 3) == 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->u = e->u0 + e->w * (e->parts[i].frame % (e->tw / e->w));
                    e->v = e->v0 + e->h * (e->parts[i].frame / (e->tw / e->w));
                } else {
                    e->u = e->u0 + e->w * (e->parts[i].frame / (e->th / e->h));
                    e->v = e->v0 + e->h * (e->parts[i].frame % (e->th / e->h));
                }
                ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
                UV_b489_01E00240(0)->u = e->u << 4;
                UV_b489_01E00240(0)->v = e->v << 4;
                UV_b489_01E00240(1)->u = e->u << 4;
                UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
                UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(2)->v = e->v << 4;
                UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
            }
            if (func_00104520(e->flags, 0x1E) != 0) {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y - e->len;
                t.z = e->parts[i].z;
            } else {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y;
                t.z = e->parts[i].z;
                func_0020D070(&t);
                t.x *= -e->len;
                t.y *= -e->len;
                t.z *= -e->len;
                t.x += e->parts[i].x;
                t.y += e->parts[i].y;
                t.z += e->parts[i].z;
            }
            if (func_00205440(&e->parts[i], cam->view, &q[0], &dep[0]) != 0 && func_00101600(&q[0]) != 0) {
                e->flags |= 0x100000;
            }
            if (func_00205440(&t, cam->view, &q[1], &dep[1]) != 0 && func_00101600(&q[1]) != 0) {
                e->flags |= 0x200000;
            }
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0) {
                dx = func_001A6970(q[0].x - q[1].x);
                dy = func_001A6970(q[0].y - q[1].y);
                w = func_001A6C60(dx * dx + dy * dy);
                w = w * e->width / e->len;
                if (dx > dy) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = q[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = q[1].x;
                    pkt.v[0].xyz.y = (u32)(q[0].y - w);
                    pkt.v[1].xyz.y = (u32)(q[1].y - w);
                    pkt.v[2].xyz.y = (u32)(q[0].y + w);
                    pkt.v[3].xyz.y = (u32)(q[1].y + w);
                } else {
                    pkt.v[0].xyz.x = (u32)(q[0].x - w);
                    pkt.v[1].xyz.x = (u32)(q[1].x - w);
                    pkt.v[2].xyz.x = (u32)(q[0].x + w);
                    pkt.v[3].xyz.x = (u32)(q[1].x + w);
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = q[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = q[1].y;
                }
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = q[0].z;
                if (func_00104520(e->flags, 0) != 0) {
                    func_00208CB0(&pkt, 0xA | ((s64)e->u << 4) | ((s64)(e->u + e->w - 1) << 14) |
                                            ((s64)e->v << 24) | ((s64)(e->v + e->h - 1) << 34));
                }
                func_00208700(&pkt, e->texture, 1);
                if (func_00104520(e->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1]) / 2.0f));
                }
            }
            e->flags &= 0xFFCFFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->parts[i].age++;
            if (e->parts[i].age % e->rate == 0) {
                e->parts[i].frame++;
                if (e->nframes == e->parts[i].frame) {
                    e->parts[i].frame = 0;
                }
            }
        }
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

static s32 func_01E01CA0_b154(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b049:01E02690, 296 insns: two 8-point trails (a, b) shift one step and take the new points; then for each
   of the 7 segments draws two flat quads, mid(a,b)[i] / mid(a,b)[i+1] to a[i] / a[i+1] and to b[i] / b[i+1]
   (colours from the module helper at 01E00100), only when all 4 corners project. */

typedef struct {
    u64 c;
    u64 xyz;
} Vtx_b049_01E02690;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b049_01E02690 v[4];
    u8 tail[8];
} Pkt_b049_01E02690;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 f8[8];
    Vec4f a[8];
    Vec4f b[8];
} Trail_b049_01E02690;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b049_01E02690;

static s32 func_01E02200_b154(Trail_b049_01E02690 *o, Cam_b049_01E02690 *cam, Vec4f *pa, Vec4f *pb) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001036E0(void *, void *, void *);
    s32 list;
    Vec4f ma;
    Vec4f mb;
    f32 dep[4];
    Pkt_b049_01E02690 pkt __attribute__((aligned(8)));
    s32 i;

    list = func_00207F60();
    for (i = 6; i > -1; i--) {
        o->a[i + 1] = o->a[i];
        o->b[i + 1] = o->b[i];
        if (i == 0) {
            o->a[i].x = pa->x;
            o->a[i].y = pa->y;
            o->a[i].z = pa->z;
            o->b[i].x = pb->x;
            o->b[i].y = pb->y;
            o->b[i].z = pb->z;
        }
    }
    ((Pkt_b049_01E02690 *)(s32)&pkt)->count = 0x14;
    ((Pkt_b049_01E02690 *)(s32)&pkt)->tag = 8;
    ((Pkt_b049_01E02690 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_b049_01E02690 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 7; i++) {
        func_001036E0(&o->a[i], &o->b[i], &ma);
        func_001036E0(&o->a[i + 1], &o->b[i + 1], &mb);
        func_01E00080_b154((Pkt_b049_01E00100 *)&pkt, o->f8, i);
        if (func_00205440(&ma, cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
            o->flags |= 0x100000;
        }
        if (func_00205440(&mb, cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->a[i], cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->a[i + 1], cam->view, &pkt.v[3].xyz, &dep[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&pkt, 0, (u32)((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
        func_01E00080_b154((Pkt_b049_01E00100 *)&pkt, o->f8, i);
        if (func_00205440(&ma, cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
            o->flags |= 0x100000;
        }
        if (func_00205440(&mb, cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->b[i], cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->b[i + 1], cam->view, &pkt.v[3].xyz, &dep[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&pkt, 0, (u32)((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
    }
    func_00207FD0(list, (s32)func_00207500(), 0);
    return 0;
}

/* shape b154:01E026A0 (b154), 923 insns, 1 copy: b154 scene manager (b419:01E02B40's form): code >= 0 clears the
   0x18B0 scene (timer 165), seven cameras, five joints, two discs, two 16-point emitters, two 128-particle sprays and
   two eight-point joint trails; else follows four joints (cameras placed at ticks 0x52/0x57), runs the trails on
   0x1F..0x2A and 0x50..0x78, discs and sprays from 0x57/0x52 (sprays respawn on a circle), the flashing fade and the
   emitters; returns 2/1 at ticks 0x7C/0x48, 6 on 0x52..0x7B, 8 when the timer ends */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b154_01E026A0;

typedef struct {
    f32 x, y, z, w;
} Sc_b154_01E026A0;

typedef struct {
    f32 x, y, z;
    s16 hC;
    s16 hE;
} Pt_b154_01E026A0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 padC[4];
    Pt_b154_01E026A0 a[8];
    Pt_b154_01E026A0 b[8];
    s16 h110;
    s16 h112;
    s16 h114;
    s16 h116;
    u8 pad118[8];
} Trail_b154_01E026A0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    f32 x, y, z, w;
    s16 uv[8];
    Pt_b154_01E026A0 pts[16];
    s16 count;
    u8 pad132[4];
    s16 h136;
    s16 h138;
    s16 h13A;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_b154_01E026A0;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b154_01E026A0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Pt_b154_01E026A0 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 life;
    u8 f2F;
} Spray_b154_01E026A0;

typedef struct {
    Crd_b154_01E026A0 cam0;
    Trail_b154_01E026A0 trail1;
    Trail_b154_01E026A0 trail2;
    Crd_b154_01E026A0 cam1;
    Emit_b154_01E026A0 emitB;
    Crd_b154_01E026A0 cam2;
    Emit_b154_01E026A0 emitA;
    Crd_b154_01E026A0 cam3;
    Disc_b154_01E026A0 disc1;
    Crd_b154_01E026A0 cam4;
    Disc_b154_01E026A0 disc2;
    Crd_b154_01E026A0 cam5;
    Spray_b154_01E026A0 spray1;
    Pt_b154_01E026A0 parts1[128];
    Crd_b154_01E026A0 cam6;
    Spray_b154_01E026A0 spray2;
    Pt_b154_01E026A0 parts2[128];
    u8 pad1870[0x10];
    s32 timer;
    s32 t;
    s32 code;
    s32 flags;
    s32 ja;
    s32 jb;
    s32 jc;
    s32 jd;
    s32 je;
    u8 fade;
    u8 pad18A5[0xB];
} Scene_b154_01E026A0;

static s32 func_01E026A0_b154(s32 arg0, s32 code) {
    Scene_b154_01E026A0 *g = (Scene_b154_01E026A0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(s32 *, s32);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00103DB0(void *, void *, void *);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_00104520(s32, s32);
    extern void func_001F6D00(u8);
    extern s32 func_0019A5C8();
    Sc_b154_01E026A0 s;
    Vec4f tmp;
    Vec4f v[2];
    Vec4f w[2];
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 k;
    s32 j;
    s32 m;
    s32 n;
    s32 r;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x18B0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        func_00103890(&g->cam5);
        func_00103890(&g->cam6);
        g->ja = func_001F5560(func_001F53A0(), 0x1B, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x19, 0);
        g->jc = func_001F5560(func_001F53A0(), 0x24, 0);
        g->jd = func_001F5560(func_001F53A0(), 0x22, 0);
        g->je = func_001F5560(func_001F5380(), 1, 1);
        g->timer = 0xA5;
        g->t = 1;
        g->code = code;
        g->flags = 0;
        g->fade = 0x80;
        g->disc1.flags = 0x80000;
        g->disc1.c[2] = 0xA0;
        g->disc1.c[1] = 0x40;
        g->disc1.c[0] = 0x40;
        g->disc1.c[3] = 0xFF;
        g->disc1.radius = 10.0f;
        g->disc1.count = 0x24;
        g->disc1.height = 0;
        g->disc2.flags = 0x80000;
        g->disc2.c[2] = 0xA0;
        g->disc2.c[1] = 0x40;
        g->disc2.c[0] = 0x40;
        g->disc2.c[3] = 0xFF;
        g->disc2.radius = 10.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        func_00103260(tx, 8);
        g->emitA.tex = tx[0];
        g->emitA.flags = 0x80085;
        g->emitA.x = 0.0f;
        g->emitA.y = 0.0f;
        g->emitA.z = 0.0f;
        g->emitA.w = 0.0f;
        g->emitA.uv[4] = 0;
        g->emitA.uv[5] = 0x3C;
        g->emitA.uv[2] = 0xA;
        g->emitA.uv[3] = 0xA;
        g->emitA.uv[6] = 0x80;
        g->emitA.uv[7] = 0x80;
        g->emitA.size = 0.5f;
        g->emitA.count = 0x10;
        g->emitA.h13A = 1;
        g->emitA.h13C = 0;
        g->emitA.h140 = 6;
        g->emitA.h136 = 0xA;
        g->emitA.h138 = 0xA;
        g->emitA.c[2] = 0x80;
        g->emitA.c[1] = 0x80;
        g->emitA.c[0] = 0x80;
        g->emitA.c[3] = 0x80;
        for (k = 0; k < 16; k++) {
            g->emitA.pts[k].x = g->emitA.x + (f32)(func_0019A5C8() % 10 - 5);
            g->emitA.pts[k].y = g->emitA.y + (f32)(func_0019A5C8() % 8 - 2);
            g->emitA.pts[k].z = g->emitA.z;
            g->emitA.pts[k].hE = -g->emitA.h13A * k;
            g->emitA.pts[k].hC = 0;
            g->emitA.h13E = g->emitA.h140 - 1;
        }
        func_00103260(tx, 0xF);
        g->emitB.tex = tx[0];
        g->emitB.flags = 0x80481;
        g->emitB.x = 0.0f;
        g->emitB.y = 0.0f;
        g->emitB.z = 0.0f;
        g->emitB.w = 0.0f;
        g->emitB.uv[4] = 0xF0;
        g->emitB.uv[5] = 0;
        g->emitB.uv[2] = 0x10;
        g->emitB.uv[3] = 0x10;
        g->emitB.uv[6] = 0x100;
        g->emitB.uv[7] = 0x100;
        g->emitB.size = 6.0f;
        g->emitB.count = 0x10;
        g->emitB.h13A = 3;
        g->emitB.h13C = 2;
        g->emitB.h140 = 8;
        g->emitB.h136 = 0xA;
        g->emitB.h138 = 0xA;
        g->emitB.c[2] = 0x40;
        g->emitB.c[1] = 0x80;
        g->emitB.c[0] = 0x60;
        g->emitB.c[3] = 0x30;
        for (k = 0; k < 16; k++) {
            g->emitB.pts[k].x = g->emitB.x + (f32)(func_0019A5C8() % 10 - 5);
            g->emitB.pts[k].y = g->emitB.y + (f32)(func_0019A5C8() % 8 - 2);
            g->emitB.pts[k].z = g->emitB.z;
            g->emitB.pts[k].hE = -g->emitB.h13A * k;
            g->emitB.pts[k].hC = 0;
            g->emitB.h13E = g->emitB.h140 - 1;
        }
        g->spray1.tex = tx[0];
        g->spray1.flags = 0x20000003;
        g->spray1.c[2] = 0xA0;
        g->spray1.c[1] = 0x40;
        g->spray1.c[0] = 0x40;
        g->spray1.c[3] = 0x80;
        g->spray1.f20 = 0.5f;
        g->spray1.f24 = 5.0f;
        g->spray1.uv[0] = 0xB0;
        g->spray1.uv[1] = 0x40;
        g->spray1.uv[2] = 0x20;
        g->spray1.uv[3] = 0x20;
        g->spray1.uv[4] = 0xB0;
        g->spray1.uv[5] = 0x40;
        g->spray1.uv[6] = 0x100;
        g->spray1.uv[7] = 0x100;
        g->spray1.parts = g->parts1;
        g->spray1.radius = 5.0f;
        g->spray1.count = 0x80;
        g->spray1.life = 2;
        g->spray1.f2F = 0;
        { extern s32 b154_01E00D80(void *, s32, f32); b154_01E00D80(&g->spray1, 0xC, 4.0f); }
        g->spray2.tex = tx[0];
        g->spray2.flags = 0x20000003;
        g->spray2.c[2] = 0xA0;
        g->spray2.c[1] = 0x40;
        g->spray2.c[0] = 0x40;
        g->spray2.c[3] = 0x80;
        g->spray2.f20 = 0.5f;
        g->spray2.f24 = 5.0f;
        g->spray2.uv[0] = 0xB0;
        g->spray2.uv[1] = 0x40;
        g->spray2.uv[2] = 0x20;
        g->spray2.uv[3] = 0x20;
        g->spray2.uv[4] = 0xB0;
        g->spray2.uv[5] = 0x40;
        g->spray2.uv[6] = 0x100;
        g->spray2.uv[7] = 0x100;
        g->spray2.parts = g->parts2;
        g->spray2.radius = 5.0f;
        g->spray2.count = 0x80;
        g->spray2.life = 2;
        g->spray2.f2F = 0;
        func_01E00D80_b154((Obj_b015_01E01620 *)&g->spray2, 0xC, 4.0f);
        g->trail1.tex = tx[0];
        g->trail1.flags = 1;
        g->trail1.h110 = 0x8E;
        g->trail1.h112 = 0x54;
        g->trail1.h114 = 0x20;
        g->trail1.h116 = 1;
        g->trail1.c[2] = 0x20;
        g->trail1.c[1] = 0x20;
        g->trail1.c[0] = 0x60;
        g->trail1.c[3] = 0xFF;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        for (i = 0; i < 8; i++) {
            g->trail1.a[i].x = v[0].x;
            g->trail1.a[i].y = v[0].y;
            g->trail1.a[i].z = v[0].z;
            g->trail1.b[i].x = v[1].x;
            g->trail1.b[i].y = v[1].y;
            g->trail1.b[i].z = v[1].z;
        }
        g->trail2.tex = tx[0];
        g->trail2.flags = 1;
        g->trail2.h110 = 0x8E;
        g->trail2.h112 = 0x54;
        g->trail2.h114 = 0x20;
        g->trail2.h116 = 1;
        g->trail2.c[2] = 0x20;
        g->trail2.c[1] = 0x20;
        g->trail2.c[0] = 0x60;
        g->trail2.c[3] = 0xFF;
        func_001F5620(func_001F53A0(), g->jc, &w[0]);
        func_001F5620(func_001F53A0(), g->jd, &w[1]);
        for (i = 0; i < 8; i++) {
            g->trail2.a[i].x = w[0].x;
            g->trail2.a[i].y = w[0].y;
            g->trail2.a[i].z = w[0].z;
            g->trail2.b[i].x = w[1].x;
            g->trail2.b[i].y = w[1].y;
            g->trail2.b[i].z = w[1].z;
        }
        return 0;
    }
    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    func_001F5620(func_001F53A0(), g->jc, &w[0]);
    func_001F5620(func_001F53A0(), g->jd, &w[1]);
    if (g->t == 0x52) {
        func_001F5F90(func_001F5380(), &g->cam2.pos);
        func_001036E0(&v[1], &w[1], &tmp);
        g->cam1.pos = tmp;
        func_00103DB0(&v[0], &v[1], &g->cam6.rot);
        g->cam4.pos = v[1];
        g->cam6.pos = g->cam4.pos;
    }
    if (g->t == 0x57) {
        func_00103DB0(&w[0], &w[1], &g->cam5.rot);
        g->cam3.pos = w[1];
        g->cam5.pos = g->cam3.pos;
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001039A0(&g->cam3);
    func_001039A0(&g->cam4);
    func_001038D0(&g->cam5);
    func_001038D0(&g->cam6);
    if ((g->t >= 0x1F && g->t <= 0x2A) || (g->t >= 0x50 && g->t < 0x79)) {
        func_01E02200_b154((Trail_b049_01E02690 *)&g->trail1, (void *)g, &v[0], &v[1]);
        func_01E02200_b154((Trail_b049_01E02690 *)&g->trail2, (void *)g, &w[0], &w[1]);
    } else {
        for (j = 0; j < 8; j++) {
            g->trail1.a[j].x = v[0].x;
            g->trail1.a[j].y = v[0].y;
            g->trail1.a[j].z = v[0].z;
            g->trail1.b[j].x = v[1].x;
            g->trail1.b[j].y = v[1].y;
            g->trail1.b[j].z = v[1].z;
        }
        for (m = 0; m < 8; m++) {
            g->trail2.a[m].x = w[0].x;
            g->trail2.a[m].y = w[0].y;
            g->trail2.a[m].z = w[0].z;
            g->trail2.b[m].x = w[1].x;
            g->trail2.b[m].y = w[1].y;
            g->trail2.b[m].z = w[1].z;
        }
    }
    if (g->t >= 0x57) {
        if (g->t < 0x7C) {
            func_01E01CA0_b154(ot, (Disc_b540_01E00250 *)&g->disc1, (void *)&g->cam3);
            if (g->t % 2 == 1) {
                g->disc1.c[3] = 0xFF;
            } else {
                g->disc1.c[3] = 0x80;
            }
        }
        func_01E00F40_b154(ot, (void *)&g->spray1, (void *)&g->cam5);
        if (g->t > 0x7C) {
            func_00103470(&g->spray1.c[3], 0, 0x10);
        }
        for (k = 0; k < g->spray1.count; k++) {
            if (g->parts1[k].hE >= 0) {
                g->parts1[k].x *= 1.2f;
                g->parts1[k].y *= 1.2f;
                g->parts1[k].z *= 1.2f;
                if (g->parts1[k].y > 30.0f) {
                    r = 10.0f * g->spray1.radius;
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (f32)(func_0019A5C8() % r);
                    g->parts1[k].y = 4.0f;
                    g->parts1[k].z = d * func_0020B480(a);
                    g->parts1[k].x = d * func_0020B550(a);
                    g->parts1[k].hE = -(func_0019A5C8() % 12);
                }
            }
        }
    }
    if (g->t >= 0x52) {
        if (g->t < 0x7C || g->fade != 0x80) {
            func_001F6D00(g->fade);
            if (func_00104520(g->flags, 0x1F) == 0) {
                if (func_00103470(&g->fade, 0x20, 8) == 0) {
                    g->flags |= 0x80000000;
                }
            } else {
                if (func_001032C0(&g->fade, 0x80, 8) == 0) {
                    g->flags &= 0x7FFFFFFF;
                }
            }
        }
        if (g->t < 0x7C) {
            func_01E01CA0_b154(ot, (Disc_b540_01E00250 *)&g->disc2, (void *)&g->cam4);
            if (g->t % 2 == 0) {
                g->disc2.c[3] = 0xFF;
            } else {
                g->disc2.c[3] = 0x80;
            }
        }
        func_01E00F40_b154(ot, (void *)&g->spray2, (void *)&g->cam6);
        if (g->t > 0x7C) {
            func_00103470(&g->spray2.c[3], 0, 0x10);
        }
        for (k = 0; k < g->spray2.count; k++) {
            if (g->parts2[k].hE >= 0) {
                g->parts2[k].x *= 1.2f;
                g->parts2[k].y *= 1.2f;
                g->parts2[k].z *= 1.2f;
                if (g->parts2[k].y > 30.0f) {
                    r = 10.0f * g->spray2.radius;
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (f32)(func_0019A5C8() % r);
                    g->parts2[k].y = 4.0f;
                    g->parts2[k].z = d * func_0020B480(a);
                    g->parts2[k].x = d * func_0020B550(a);
                    g->parts2[k].hE = -(func_0019A5C8() % 12);
                }
            }
        }
        s.x = s.y = s.z = 1.01f;
        func_01E001F0_b154(ot, (void *)&g->cam2, (void *)&g->emitA, (Vec_b001_01E00A30 *)&s);
        func_00103470(&g->emitA.c[3], 0, 2);
        s.x = s.y = s.z = 1.02f;
        func_01E001F0_b154(ot, (void *)&g->cam1, (void *)&g->emitB, (Vec_b001_01E00A30 *)&s);
        func_00103470(&g->emitB.c[3], 0, 2);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x7C) {
        return 2;
    }
    if (g->t == 0x48) {
        return 1;
    }
    if (g->t >= 0x52 && g->t < 0x7C) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
