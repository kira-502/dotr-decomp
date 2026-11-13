#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b756(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00110_b756(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

/* shape b756:01E009B0, 282 insns: IWMagicCircleG4_5, b747:01E00ED0 (b193 family) with the outer ring height read
   from the anim (0x3C) instead of 0 */

typedef struct {
    f32 x, y, z, w;
} Vec_b193_01E009B0_b756;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[4];
    f32 y2;
    u8 pad40[8];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Anim_b193_01E009B0_b756;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b193_01E009B0_b756;

typedef struct {
    u8 b[0x90];
} Pkt_b193_01E009B0_b756;

static void func_01E009B0_b756(Obj_b193_01E009B0_b756 *o, Anim_b193_01E009B0_b756 *an, s32 mode, Vec_b193_01E009B0_b756 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b193_01E009B0_b756 quad[4];
    Vec_b193_01E009B0_b756 at;
    Vec_b193_01E009B0_b756 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b193_01E009B0_b756 pkt;
    s32 a;
    s32 k;
    s16 j;
    Pkt_b193_01E009B0_b756 *p;
    s16 blend;
    s32 kind;
    f32 w0;
    f32 w1;

    p = &pkt;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    kind = mode & 0xF;
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = an->y2;
    quad[3].y = an->y2;
    w0 = an->w0;
    w1 = an->w1;
    for (k = 0; k < 36; k++) {
        if (k == 0) {
            a = an->step + j;
            quad[0].x = w0 * func_00108030(o->bD8, a, 1);
            quad[0].z = w0 * func_00108030(o->bD8, a, 0);
            quad[2].x = w1 * func_00108030(o->bD8, a, 1);
            quad[2].z = w1 * func_00108030(o->bD8, a, 0);
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        }
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
        j += 10;
    }
}

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00E20_b756(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b756((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00110_b756((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b020_01E00920;

extern void b756_01E00110(Pkt_b020_01E00920 *, void *, s32);

static void func_01E013D0_b756(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b756_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b756:01E01920, 551 insns: B756_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0xAD5E);
   frames 1/5 the openers, 90/144/158/163 bursts on joint 0xACEC at a set height, the spin (0xAD50) grows 7 a frame
   from 95 to 360; odd frames 176..380 two 0x1E02360 on a 40-step ring (0xAD58); the mark (0xA870) follows joint
   0xACF0 until 393, then slides 5.5 a frame (side by 0xAD5A) and bursts at 424/434/444; 0x1E03BA0 / 0x1E02AD0 /
   0x1E03170 / 0x1E02E30 on frame ranges from 250 to 439 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xA870 - 0x260];
    Vec4f mark;
    u8 padA880[0xACEC - 0xA880];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 padACF2[0xAD50 - 0xACF2];
    s16 spin;
    u8 padAD52[4];
    s16 side;
    s16 cnt;
    s16 flag;
    u8 padAD5C[2];
    s16 t;
} Scene_b756_01E01920;

static void func_01E01920_b756(Scene_b756_01E01920 *g) {
    extern void b756_01E021C0(void);
    extern void b756_01E02360(void);
    extern void b756_01E02900(void);
    extern void b756_01E02AD0(void);
    extern void b756_01E02CE0(void);
    extern void b756_01E02E30(void);
    extern void b756_01E03170(void);
    extern void b756_01E034F0(void);
    extern void b756_01E03670(void);
    extern void b756_01E03880(void);
    extern void b756_01E039B0(void);
    extern void b756_01E03BA0(void);
    extern void b756_01E03F20(void);
    extern void b756_01E040D0(void);
    extern void b756_01E04260(void);
    extern void b756_01E04330(void);
    extern void b756_01E05060(Scene_b756_01E01920 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t == 5) {
        b756_01E05060(g, b756_01E04330, 0);
    }
    if (g->t == 1) {
        b756_01E05060(g, b756_01E04260, 0);
    }
    if (g->t == 90) {
        g->side = 0;
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y = 33.0f;
        b756_01E05060(g, b756_01E03670, 0);
        b756_01E05060(g, b756_01E02CE0, 0);
    }
    if (g->t == 144) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y = 31.5f;
        g->side = 0;
        g->side = 1;
        b756_01E05060(g, b756_01E03F20, 0);
    }
    if (g->t == 163) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y = 31.5f;
        g->side = 0;
        b756_01E05060(g, b756_01E040D0, 0);
        g->side = 1;
        b756_01E05060(g, b756_01E040D0, 0);
    }
    if (g->t == 158) {
        g->side = 0;
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y = 35.0f;
        for (i = 0; i < 6; i++) {
            b756_01E05060(g, b756_01E021C0, 0);
        }
    }
    if (g->t >= 95) {
        if (g->spin < 360) {
            g->spin += 7;
        }
    }
    if (g->t >= 176 && g->t < 381 && g->t % 2 == 1) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y = 33.0f;
        g->side = g->cnt;
        b756_01E05060(g, b756_01E02360, 0);
        g->cnt++;
        if (g->cnt >= 40) {
            g->cnt = 0;
        }
        g->side = g->cnt;
        b756_01E05060(g, b756_01E02360, 0);
        g->cnt++;
        if (g->cnt >= 40) {
            g->cnt = 0;
        }
    }
    if (g->t >= 190 && g->t < 440 && g->t % 2 == 1) {
        b756_01E05060(g, b756_01E034F0, 0);
    }
    if (g->t > 300 && g->t < 424) {
        g->pos.x = g->mark.x;
        g->pos.y = g->mark.y;
        g->pos.z = g->mark.z;
        if (g->t < 340) {
            if (g->t % 3 == 1) {
                b756_01E05060(g, b756_01E03BA0, 0);
            }
        } else if (g->t % 2 == 1) {
            b756_01E05060(g, b756_01E03BA0, 0);
        }
    }
    if (g->t < 394) {
        func_001F5620(func_001F53A0(), g->j2, &g->mark);
    } else {
        if (g->t < 424) {
            if (g->flag != 0) {
                g->mark.z -= 5.5f;
            } else {
                g->mark.z += 5.5f;
            }
        }
        if (g->t == 424 || g->t == 434 || g->t == 444) {
            g->pos.x = g->mark.x;
            g->pos.y = g->mark.y;
            g->pos.z = g->mark.z;
            b756_01E05060(g, b756_01E03880, 0);
            for (i = 0; i < 12; i++) {
                b756_01E05060(g, b756_01E039B0, 0);
            }
            for (i = 0; i < 8; i++) {
                b756_01E05060(g, b756_01E03BA0, 0);
            }
        }
    }
    if (g->t == 270) {
        b756_01E05060(g, b756_01E02900, 0);
    }
    if (g->t >= 270 && g->t < 425) {
        if (g->t < 340) {
            if (g->t % 2 == 1) {
                b756_01E05060(g, b756_01E02AD0, 0);
            }
        } else {
            b756_01E05060(g, b756_01E02AD0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->j1, &g->pos);
    if (g->t >= 250 && g->t < 391 && g->t % 2 == 1) {
        b756_01E05060(g, b756_01E03170, 0);
    }
    if (g->t >= 250 && g->t < 391) {
        if (g->t < 301) {
            if (g->t % 2 == 1) {
                b756_01E05060(g, b756_01E02E30, 0);
            }
        } else if (g->t < 425) {
            b756_01E05060(g, b756_01E02E30, 0);
        }
    }
}

/* shape b756:01E021C0, 101 insns: on start f48 50, variant 0..6, colour 0xC0 grey, 0xA 0..7, 0xC keeps the old 0x50,
   0x50 0..49, speed (0xE), 0x8 0..34, hold (0x6); alpha 0x80 during the hold, then fades by 8 and stops;
   after the first tick f48 grows by 2.0 and 0x50 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E021C0;

static s32 func_01E021C0_b756(s32 arg0, Fx_b756_01E021C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 50.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 50;
        o->speed = func_0019A5C8() % 20 + 8;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 2.0f;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b756", func_01E02360_b756);

/* shape b756:01E02900, 116 insns: a grey-green glow on the scene point: size 0 growing by 1 to 100 (by 2 more while fading);
   alpha up by 10 for 12 frames, fading by 9 once the scene timer reaches 425; second colour flickers; spins a quarter turn */

typedef struct {
    u8 pad0[0xA870];
    Vec4f pt;
    u8 padA880[0xAD5E - 0xA880];
    s16 timer;
} Game_b756_01E02900;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b756_01E02900;

static s32 func_01E02900_b756(Game_b756_01E02900 *g, Obj_b756_01E02900 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0.0f;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xC) {
        o->c0[3] += 0xA;
    }
    if (g->timer > 0x1A8) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
        o->size += 2.0f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 8, 0x40);
    }
    if (o->size < 100.0f) {
        o->size += 1.0f;
    }
    o->pos = g->pt;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b756:01E02AD0, 131 insns: brown (0x40, 0x20, 0) spark at the scene's point (ctx+0xA870) (f48 6..15, frame 0..3, random turn, h52 counting from 1, f50 from 0 growing 7..12, angle 0..359, f8 1..8): alpha 0x60 for 15..17 ticks, then down by 6 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    f32 pos[4];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b756_01E02AD0;

typedef struct {
    u8 pad0[0xA870];
    Vec4f at;
} Ctx_b756_01E02AD0;

static s32 func_01E02AD0_b756(Ctx_b756_01E02AD0 *g, Fx_b756_01E02AD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 6;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x40, 0x20, 0x00);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = 0;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 6 + 7;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 15;
        o->mode = 2;
        *(Vec4f *)o->pos = g->at;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b756:01E02CE0, 83 insns: on start f48 12, both colours 0x80 grey (second alpha 0), random 0x5A, rotation
   0x4000; alpha grows by 9 (below 0x80) for 13 ticks, then once the game step 0xAD5E passes 0x19A both fade by 9 (the
   first ends it); from step 0x96 the angle at 0x24 turns by -0x100 a tick */

typedef struct {
    u8 pad0[0xAD5E];
    s16 step;
} Game_b756_01E02CE0;

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    s32 f24;
    u8 pad28[0x20];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E02CE0;

static s32 func_01E02CE0_b756(Game_b756_01E02CE0 *g, Fx_b756_01E02CE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 12.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot = 0x4000;
    }
    if (o->tick < 13) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (g->step > 0x19A) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xA) {
            o->col2[3] -= 9;
        }
    }
    if (g->step >= 0x96) {
        o->f24 -= 0x100;
    }
    o->tick++;
    return 0;
}

/* shape b756:01E02E30, 205 insns: b756:01E021C0's sprite riding between two joints (0xACEE, 0xACF0): on start f48 10,
   variant 0..6, colour 0x20 grey, 0xA 0..7, 0xC keeps the old 0x50, 0x50 0..19, speed 1..3, 0x8 0..34, hold 7..11;
   alpha 0x80 during the hold, then fades by 9 and stops; after the first tick f48 grows by 3.5; each tick it sits at
   the first joint, moved back by step 0x52 twentieths of the way to the second (one twentieth on the first tick) */

typedef struct {
    u8 pad0[0xACEE];
    s16 id0;
    s16 id1;
} Ctx_b756_01E02E30;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 f48;
    f32 f4C;
    s16 f50;
    s16 step;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b756_01E02E30;

static s32 func_01E02E30_b756(Ctx_b756_01E02E30 *g, Fx_b756_01E02E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 f = o->step;
    f32 v[8];
    f32 *q;

    func_001F5620(func_001F53A0(), g->id0, v);
    func_001F5620(func_001F53A0(), g->id1, q = (f32 *)(u32)&v[4]);
    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 7;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 3.5f;
    }
    if (o->tick == 0) {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
        o->x -= (v[0] - q[0]) / 20.0f;
        o->y -= (v[1] - v[5]) / 20.0f;
        o->z -= (v[2] - v[6]) / 20.0f;
    } else {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
        v[0] = (v[0] - q[0]) / 20.0f;
        v[1] = (v[1] - v[5]) / 20.0f;
        v[2] = (v[2] - v[6]) / 20.0f;
        o->x -= v[0] * f;
        o->y -= v[1] * f;
        o->z -= v[2] * f;
    }
    o->step++;
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b756:01E03170 (B756_OBJ_MOVE_9_), 221 insns: a dark-red mote between two joints (game +0xACEE / +0xACF0):
   on start a random size 2..9, kind 0..3, colour (0x20, 0x10, 0), random angles, spin 6..11, f8 1..8, hold 15..17;
   alpha 0x60 while held, then fades by 6; each tick it sits on joint A and steps back toward joint B by a 30th of
   the gap (times its age after the first tick) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 spin;
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 pos[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 age;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b756_01E03170;

typedef struct {
    u8 pad[0xACEE];
    s16 ja;
    s16 jb;
} Game_b756_01E03170;

static s32 func_01E03170_b756(Game_b756_01E03170 *g, Fx_b756_01E03170 *o) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    f32 t;
    f32 v[8];
    f32 *q;

    t = o->age;
    func_001F5620(func_001F53A0(), g->ja, v);
    func_001F5620(func_001F53A0(), g->jb, q = (f32 *)(u32)&v[4]);
    if (o->mode == 1) {
        o->size = func_0019A5C8() % 8 + 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x20, 0x10, 0);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->age = 1;
        o->f50 = 0;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 6 + 6;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 15;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    if (o->tick == 0) {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
        o->x -= (v[0] - q[0]) / 30.0f;
        o->y -= (v[1] - v[5]) / 30.0f;
        o->z -= (v[2] - v[6]) / 30.0f;
    } else {
        o->x = v[0];
        o->y = v[1];
        o->z = v[2];
        v[0] = (v[0] - q[0]) / 30.0f;
        v[1] = (v[1] - v[5]) / 30.0f;
        v[2] = (v[2] - v[6]) / 30.0f;
        o->x -= v[0] * t;
        o->y -= v[1] * t;
        o->z -= v[2] * t;
    }
    o->age++;
    o->f50 += o->spin;
    o->tick++;
    return 0;
}

/* shape b756:01E034F0, 95 insns: a dark flash with a red-purple flicker: size 0 growing by 0.3 up to 1.2 once started, random angle;
   alpha up by 42 for 3 frames, then down by 12 until it ends; second colour flickers by frame parity */

typedef struct {
    u8 pad0[0x48];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b756_01E034F0;

static s32 func_01E034F0_b756(void *arg0, Obj_b756_01E034F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0.0f;
        func_001076F0(o->c0, 0x28, 0x28, 0x28);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xD) {
        o->c0[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 1.2f) {
            o->size += 0.3f;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xC0, 8, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 8, 0x40);
    }
    o->t++;
    return 0;
}

/* shape b756:01E03670, 130 insns: b094:01E01900's flickering pair: size 17 (f4C 11), fading by 9 after scene count 410,
   spin held at 0 / 0x8000 by the scene flag before count 150, then 0x100 a tick */

typedef struct {
    u8 pad0[0xAD5A];
    s16 flag;
    u8 pad4562[2];
    s16 count;
} Ctx_b756_01E03670;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1A];
    s32 f24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E03670;

static s32 func_01E03670_b756(Ctx_b756_01E03670 *g, Fx_b756_01E03670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 17.0f;
        o->f4C = o->f48 - 6.0f;
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (g->count > 0x19A) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    if (g->count < 150) {
        if (g->flag != 0) {
            o->f24 = 0;
        } else {
            o->f24 = 0x8000;
        }
    } else {
        o->f24 += 0x100;
    }
    o->tick++;
    return 0;
}

/* shape b756:01E03880, 74 insns: a white-orange growing spinning flash: scale 550 growing by 10 from frame 13, random
   angle; alpha up by 32 to 0x80 for 15 frames, then down by 6 until it ends; random turn plus a quarter */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b756_01E03880;

static s32 func_01E03880_b756(void *arg0, Obj_b756_01E03880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 550.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0x80, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xF) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x20;
        }
    } else if (o->c0[3] > 7) {
        o->c0[3] -= 6;
    } else {
        o->state = 0;
    }
    if (o->t > 0xC) {
        o->scale += 10.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b756:01E039B0, 123 insns: on start f48 40, 0x4C 0, variant 0..6, 0x8 4..6, three random words 0x20/0x24/0x28;
   both alphas grow by 0x15 (below 0x80) for 9 ticks, then fade by 8 (the first ends it); both colours flicker
   0x80 / 0xC0 grey; f48 grows by 2 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x16];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    s32 w4C;
    u8 pad50[4];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E039B0;

static s32 func_01E039B0_b756(s32 arg0, Fx_b756_01E039B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        o->w4C = 0;
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->tick < 9) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x15;
        }
    } else {
        if (o->col[3] > 9) {
            o->col[3] -= 8;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 9) {
            o->col2[3] -= 8;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    o->f48 += 2.0f;
    o->tick++;
    return 0;
}

/* shape b756:01E03BA0, 101 insns: on start f48 50, variant 0..6, colour 0x18 grey, 0xA 0..7, 0xC keeps the old 0x50,
   0x50 0..19, speed (0xE), 0x8 0..34, hold (0x6); alpha 0x80 during the hold, then fades by 12 and stops;
   after the first tick f48 grows by 1.5 and 0x50 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E03BA0;

static s32 func_01E03BA0_b756(s32 arg0, Fx_b756_01E03BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 50.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 20;
        o->speed = func_0019A5C8() % 8 + 6;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 1.5f;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b756:01E03D40, 119 insns, 2 copies: a two-kind flare: kind 0 a small grey one fading in with a flickering
   orange/violet second colour, kind 1 a large white one fading in then out; turns each frame (b402:01E02710
   family) */

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Flare_b756_01E03D40;

static s32 func_01E03D40_b756(void *arg0, Flare_b756_01E03D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 40.0f;
        if (o->kind == 1) {
            o->size = 300.0f;
        }
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x80, 0x80, 0x80);
            func_001076F0(o->c1, 0xF0, 0x80, 0x10);
        } else {
            func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->c1, 0x80, 0x40, 0x10);
        }
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->kind == 0 && o->t < 0xC) {
        o->c0[3] += 0x10;
    }
    if (o->kind == 1) {
        if (o->t < 0xC) {
            if (o->c0[3] < 0xC0) {
                o->c0[3] += 0x1B;
            }
        } else if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        }
    }
    if (o->kind == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->c1, 0x80, 8, 0x40);
        }
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b756:01E03F20, 106 insns: on start f48/f4C 0/110 (kind 0x50 = 0) or 150/250 (kind 1), colour 0x40 grey, second
   colour (0xF0, 8, 8) with alpha 0, random 0x5A; for kinds 0..1 the alpha grows by 0x10 for 12 ticks, then once the
   game step 0xAD5E passes 0x19A both alphas fade by 9 and it stops; the second colour flickers red / purple */

typedef struct {
    u8 pad0[0xAD5E];
    s16 step;
} Game_b756_01E03F20;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E03F20;

static s32 func_01E03F20_b756(Game_b756_01E03F20 *g, Fx_b756_01E03F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 0.0f;
            o->f4C = 110.0f;
        }
        if (o->kind == 1) {
            o->f48 = 150.0f;
            o->f4C = 250.0f;
        }
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0xF0, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind < 2) {
        if (o->tick < 12) {
            o->col[3] += 0x10;
        } else if (g->step > 0x19A) {
            if (o->col[3] > 0xA) {
                o->col[3] -= 9;
            } else {
                o->mode = 0;
            }
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            }
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 8, 0x40);
    }
    o->tick++;
    return 0;
}

/* shape b756:01E040D0, 100 insns: on start f48/f4C 110 (kind 0) or 250 (kind 1) with f34 0, colour 0x80 grey, second
   colour (0xF0, 8, 8) with alpha 0, random 0x5A; alpha grows by 0x15 (below 0xC0) for 12 ticks, then fades by 3 and
   stops; f34 grows by 10 after the first tick; the second colour flickers */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b756_01E040D0;

static s32 func_01E040D0_b756(s32 arg0, Fx_b756_01E040D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->f50 == 0) {
            o->f48 = 110.0f;
            o->f4C = 110.0f;
            o->f34 = 0.0f;
        }
        if (o->f50 == 1) {
            o->f48 = 250.0f;
            o->f4C = 250.0f;
            o->f34 = 0.0f;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0xF0, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 12) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 4) {
        o->col[3] -= 3;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f34 += 10.0f;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xF0, 8, 0x80);
    } else {
        func_001076F0(o->col2, 0x80, 8, 0x40);
    }
    o->tick++;
    return 0;
}

/* shape b756:01E04260, 51 insns: volume fade: starts at 0x80; while the game counter at 0xA900 is over 0x1E it drops by
   10 to 0x30, otherwise it rises by 10 to 0x80; passed to func_001F6D00 (the same call either way) */

typedef struct {
    u8 pad0[0xA900];
    s32 count;
} Game_b756_01E04260;

typedef struct {
    u8 pad0[0x50];
    s16 v;
    u8 pad52[0x6];
    s16 mode;
} Fx_b756_01E04260;

static s32 func_01E04260_b756(Game_b756_01E04260 *g, Fx_b756_01E04260 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else if (o->v < 0x80) {
        o->v += 10;
    } else {
        o->v = 0x80;
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b756:01E04330, 31 insns: variant of b402:01E02C50 (func_001F7170(3, ...), stops after 0xA5 ticks) */

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b756_01E04330;

typedef struct {
    f32 v;
} F1_b756_01E04330;

extern F1_b756_01E04330 D_01E06480_b756;
extern F1_b756_01E04330 D_01E06488_b756;

static s32 func_01E04330_b756(s32 arg0, Fx_b756_01E04330 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b756_01E04330 a;
    F1_b756_01E04330 b;

    a = D_01E06480_b756;
    b = D_01E06488_b756;
    func_001F7170(3, 0, &a, &b, 0);
    o->tick++;
    if (o->tick >= 0xA5) {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b756", func_01E043B0_b756);

/* shape b756:01E05060, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b756_01E05060 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b756_01E05060;

typedef struct Obj_b756_01E05060 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b756_01E05060 slots[0x96];
    u8 padB[0xa904 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xad56 - 0xa904 - 4];
    s16 fB2B0;
} Obj_b756_01E05060;

static s32 func_01E05060_b756(Obj_b756_01E05060 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b756_01E05060 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b756:01E051F0, 206 insns: b721:01E055D0's 18-quad ring with b756's scene tables (ot 0xA90C, frames 0xAD0C,
   trig 0xAF60), drawing only the quads whose angle step is still under the scene value at 0xAD50 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b756_01E051F0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xA90C - 0xC0];
    s32 ot;
    u8 padA910[0xAD0C - 0xA910];
    s16 frames[18];
    u8 padAD30[0xAD50 - 0xAD30];
    s16 limit;
    u8 padAD52[0xAF60 - 0xAD52];
    u8 trig[1];
} Game_b756_01E051F0;

static void func_01E051F0_b756(Game_b756_01E051F0 *g, Obj_b756_01E051F0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];

    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 a;
    void *p = &buf;
    s16 s;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;
    s32 t;

    *(Vec4f *)pos = *in;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    for (i = 0; i < 18; i++) {
        if (a < g->limit) {
            func_00106080(rm, 0x14, g->frames[i], 0);
            g->rect = *(Vec4f *)rm;
            func_00108500(p, &g->rect, g->frame);
            s = o->ang + a - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[2].x = c * r1;
            q[2].z = sn * r1;
            q[0].x = c * r0;
            q[0].z = sn * r0;
            t = o->ang + 20;
            s = a + t - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[3].x = c * r1;
            q[3].z = sn * r1;
            q[1].x = c * r0;
            q[1].z = sn * r0;
            if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->ot, (u32)depth[0]);
            }
            a += 20;
        }
    }
}

/* shape b756:01E05530 (B756PAINT_RAIN21), 560 insns, 2 copies: textured ribbon between two point trails
   (b120:01E04DB0 form): 2 quads per segment along the inlined module spline (steps of 0.5), alpha fading by
   col0.a/(2n), drawn at the computed depth */

typedef struct {
    f32 x, y, z, w;
} Vec_b756_01E05530;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b756_01E05530;

typedef struct {
    Rgbaq_b756_01E05530 c;
    u64 uv;
    u64 xyz;
} Vtx_b756_01E05530;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b756_01E05530 v[4];
    u8 tail[0x20];
} Pkt_b756_01E05530;

typedef struct {
    u8 r, g, b, a;
} C4_b756_01E05530;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b756_01E05530 col0;
    C4_b756_01E05530 col1;
} Rib_b756_01E05530;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
} Obj_b756_01E05530;

static inline Vec_b756_01E05530 spline_b756_01E05530(Vec_b756_01E05530 *p, s32 type, f32 t) {
    Vec_b756_01E05530 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

static void func_01E05530_b756(Obj_b756_01E05530 *o, Rib_b756_01E05530 *s, Vec_b756_01E05530 *pa, Vec_b756_01E05530 *pb) {
    extern Rgbaq_b756_01E05530 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b756_01E05530 quad[4];
    Vec_b756_01E05530 v;
    Vec_b756_01E05530 A[2];
    Vec_b756_01E05530 B[2];
    Vec_b756_01E05530 a4[4];
    Vec_b756_01E05530 b4[4];
    f32 m[16];
    Pkt_b756_01E05530 pkt __attribute__((aligned(8)));
    C4_b756_01E05530 c0;
    C4_b756_01E05530 c1;
    s32 k;
    s32 j;
    s32 i;
    s16 n;
    s32 x;
    Pkt_b756_01E05530 *p;
    f32 t;

    n = s->n;
    v.x = o->x;
    v.y = o->y;
    v.z = o->z;
    func_00108EF0(m, NULL, NULL, &v);
    p = &pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, &s->col0, 0);
    func_00108500(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    c0 = s->col0;
    c1 = s->col1;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        for (j = 0; j < 2; j++) {
            c1.a = c0.a;
            p->v[0].c = func_00107740(&c0);
            p->v[2].c = func_00107740(&c1);
            x = c0.a - (s16)(s->col0.a / (n * 2));
            if (x > 0) {
                c0.a = x;
            } else {
                c0.a = 0;
            }
            c1.a = c0.a;
            p->v[1].c = func_00107740(&c0);
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                for (i = 0; i < 2; i++) {
                    A[i] = spline_b756_01E05530(&pa[k - 1], 0, t);
                    B[i] = spline_b756_01E05530(&pb[k - 1], 0, t);
                    if (i == 0) {
                        t += 0.5f;
                    }
                    if (t > 9.0f) {
                        t = 1.0f;
                    }
                }
            } else {
                for (i = 0; i < 2; i++) {
                    A[i] = spline_b756_01E05530(a4, 0, t);
                    B[i] = spline_b756_01E05530(b4, 0, t);
                    if (i == 0) {
                        t += 0.5f;
                    }
                    if (t > 9.0f) {
                        t = 1.0f;
                    }
                }
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
}

/* shape b756:01E05DF0, 248 insns: b108:01E009A0-style band between the object's two points (0x20 bottom, 0x30 top):
   two flat quads, one pushed out by the data's (0x48, 0x4C) offset and one by its negative; colours 0x64/0x60
   alternating on the corners; blend from flags >> 4, at the position (by value) turned by the data's rotation; depth
   mode flags & 0xF (projected, far after a packet tweak, or front) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b756_01E05DF0;

typedef struct {
    Rgbaq_b756_01E05DF0 c;
    u64 xyz;
} Vtx_b756_01E05DF0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b756_01E05DF0 v[4];
} Pkt_b756_01E05DF0;

typedef struct {
    u8 pad00[0x20];
    f32 x0, y0, z0;
    u8 pad2C[4];
    f32 x1, y1, z1;
    u8 pad3C[0x44];
    s32 ot;
} Obj_b756_01E05DF0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 dx;
    f32 dz;
    u8 pad50[0x10];
    u8 col[4];
    u8 col2[4];
} Data_b756_01E05DF0;

static void func_01E05DF0_b756(Obj_b756_01E05DF0 *o, Data_b756_01E05DF0 *data, s32 flags, Vec4f pos) {
    extern Rgbaq_b756_01E05DF0 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f t;
    f32 m[16];
    f32 depth[4];
    struct {
        Pkt_b756_01E05DF0 pk;
        u8 tail[0x40];
    } buf;
    s32 i;
    s16 j;
    s16 alpha;
    Pkt_b756_01E05DF0 *p;
    s32 mode;
    f32 a;
    f32 b;
    f32 na;
    f32 nb;

    p = &buf.pk;
    j = 0;
    p->v[0].c = func_00107740(data->col2);
    p->v[1].c = func_00107740(data->col);
    p->v[2].c = func_00107740(data->col2);
    p->v[3].c = func_00107740(data->col);
    func_001092E0(p, 0);
    func_001094F0(p);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, 0, &data->rot, &t);
    mode = flags & 0xF;
    quad[0].y = o->y0;
    quad[1].y = o->y0;
    quad[2].y = o->y1;
    quad[3].y = o->y1;
    a = data->dx;
    b = data->dz;
    na = -a;
    nb = -b;
    for (i = 0; i < 2; i++) {
        quad[0].y = o->y0;
        quad[1].y = o->y0;
        quad[2].y = o->y1;
        quad[3].y = o->y1;
        if (i == 0) {
            quad[0].x = o->x0 + a;
            quad[0].z = o->z0 + b;
            quad[1].x = o->x0;
            quad[1].z = o->z0;
            quad[2].x = o->x1 + a;
            quad[2].z = o->z1 + b;
            quad[3].x = o->x1;
            quad[3].z = o->z1;
        }
        if (i == 1) {
            quad[0].x = na + o->x0;
            quad[0].z = nb + o->z0;
            quad[1].x = o->x0;
            quad[1].z = o->z0;
            quad[2].x = na + o->x1;
            quad[2].z = nb + o->z1;
            quad[3].x = o->x1;
            quad[3].z = o->z1;
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, -1);
        }
        j += 60;
    }
}

/* shape b756:01E061D0, 170 insns: draw a 4-quad sprite burst at a point with a local packet: the object's colour on all
   corners, the scene's rect (g+0x94, frame g+0xBE) and texture (g+0x88), blend 0x42 or a scaled 0x40 by the mode's high
   nibble; it places the burst at the point turned by the object, resets the rect to frame 0x14, and draws four quads of
   the object's size (depth-tested, packet list g+0xA90C) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b756_01E061D0;

typedef struct {
    Rgbaq_b756_01E061D0 c;
    u64 st;
    u64 xyz;
} Vtx_b756_01E061D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b756_01E061D0 v[4];
} Pkt_b756_01E061D0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[0x14];
    u8 col[4];
} Obj_b756_01E061D0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xA84C];
    s32 ot;
} Game_b756_01E061D0;

static void func_01E061D0_b756(Game_b756_01E061D0 *g, Obj_b756_01E061D0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b756_01E061D0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        Pkt_b756_01E061D0 pk;
        u8 tail[0x20];
    } buf;
    Pkt_b756_01E061D0 *p = &buf.pk;
    s32 k;
    s16 i;

    *(Vec4f *)pos = *in;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col);
    p->v[3].c = func_00107740(o->col);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    func_00106080(rm, 0x14, 0, 0);
    g->rect = *(Vec4f *)rm;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 4; i++) {
        func_00108D60(q, o->size, o->size, i);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
    }
}
