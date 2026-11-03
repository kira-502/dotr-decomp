#include "common.h"

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

static void func_01E00080_b394(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

extern void b394_01E00080(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00920_b394(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    b394_01E00080(p, o->b94, o->hC0);
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

static void func_01E00E70_b394(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b394((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b394((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b394:01E01420, 273 insns: b731:01E01C10 family scene timer step: tracks joint 0x86A4 into ctx+0x8610 until
   155, then glides it (y and z) a 32nd of the way to the camera point of joint 0x86B4 per tick until 185; at 152
   starts b394:01E01E40; from 96 to 474 two b394:01E01870 at joints 0x86A4 / 0x86A6; at 221..239 and 292..309 two
   b394:01E01AA0 at joints 0x86A8 / 0x86AA; at 292..409 three b394:01E01C50 at random spots, all through b394:01E026D0 */

typedef struct Scn_b394_01E01420 {
    u8 pad0[0x250];
    f32 org[3];
    u8 pad25C[0x8610 - 0x25C];
    Vec4f p;
    Vec4f vel;
    u8 pad8630[0x86A4 - 0x8630];
    s16 j0;
    s16 j1;
    s16 j2;
    s16 j3;
    u8 pad86AC[8];
    s16 cam;
    u8 pad86B6[0x24];
    s16 timer;
} Scn_b394_01E01420;

static void func_01E01420_b394(Scn_b394_01E01420 *g) {
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void func_001F5620();
    extern u8 b394_01E01870[];
    extern u8 b394_01E01AA0[];
    extern u8 b394_01E01C50[];
    extern u8 b394_01E01E40[];
    extern void b394_01E026D0(Scn_b394_01E01420 *w, void *data, s32 arg);
    f32 v[8];
    s16 i;

    g->timer++;
    if (g->timer < 155) {
        func_001F5620(func_001F53A0(), g->j0, &g->p);
    } else {
        if (g->timer == 155) {
            func_001F5620(func_001F5380(), g->cam, v);
            g->vel.z = (v[2] - g->p.z) / 32.0f;
            g->vel.y = (v[1] - g->p.y) / 32.0f;
        }
        if (g->timer < 186) {
            g->p.z += g->vel.z;
            g->p.y += g->vel.y;
        }
    }
    if (g->timer == 152) {
        b394_01E026D0(g, b394_01E01E40, 0);
    }
    if (g->timer > 95 && g->timer < 475) {
        func_001F5620(func_001F53A0(), g->j0, g->org);
        b394_01E026D0(g, b394_01E01870, 0);
    }
    if (g->timer > 95 && g->timer < 475) {
        func_001F5620(func_001F53A0(), g->j1, g->org);
        b394_01E026D0(g, b394_01E01870, 0);
    }
    if (g->timer > 220 && g->timer < 240) {
        func_001F5620(func_001F53A0(), g->j2, g->org);
        b394_01E026D0(g, b394_01E01AA0, 0);
        func_001F5620(func_001F53A0(), g->j3, g->org);
        b394_01E026D0(g, b394_01E01AA0, 0);
    }
    if (g->timer > 291 && g->timer < 310) {
        func_001F5620(func_001F53A0(), g->j2, g->org);
        b394_01E026D0(g, b394_01E01AA0, 0);
        func_001F5620(func_001F53A0(), g->j3, g->org);
        b394_01E026D0(g, b394_01E01AA0, 0);
    }
    if (g->timer > 291 && g->timer < 410) {
        for (i = 0; i < 3; i++) {
            g->org[0] = func_0019A5C8() % 60 - 30;
            g->org[1] = func_0019A5C8() % 40 + 20;
            g->org[2] = func_0019A5C8() % 20 - 10;
            b394_01E026D0(g, b394_01E01C50, 0);
        }
    }
}

/* shape b394:01E01870, 139 insns: b362:01E022B0's spark, size 3, frame 0..7, height 0..14, rise 1..3, flickering white / grey */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b394_01E01870;

static s32 func_01E01870_b394(s32 arg0, Obj_b394_01E01870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 15;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b394:01E01AA0, 108 insns: a grey spark: f48 4 (+2 per tick), fA -7..7, fC = the old f50, f50 0, spin 5..12
   (9..20 when fC was 1), f8 0..34, life 3..7; alpha 0x80 during the life, then fades by 8; f50 grows by the spin
   each tick after the first */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x38];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b394_01E01AA0;

static s32 func_01E01AA0_b394(s32 arg0, Fx_b394_01E01AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->f56 = 0;
        func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = 0;
        o->spin = func_0019A5C8() % 8 + 5;
        if (o->fC == 1) {
            o->spin = func_0019A5C8() % 12 + 9;
        }
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
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
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b394:01E01C50, 123 insns: b394:01E01AA0 twin, life 25..29, and f38 = (camera z - f18) / 25 so it reaches the camera over 25 ticks */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[8];
    f32 z;
    u8 pad1C[0x1C];
    f32 dz;
    u8 pad3C[0xC];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b394_01E01C50;

static s32 func_01E01C50_b394(s32 arg0, Fx_b394_01E01C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    f32 v[4];

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->f56 = 0;
        func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = 0;
        o->spin = func_0019A5C8() % 8 + 5;
        if (o->fC == 1) {
            o->spin = func_0019A5C8() % 12 + 9;
        }
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 25;
        func_001F5F90(func_001F5380(), v);
        o->dz = (v[2] - o->z) / 25.0f;
        o->mode = 2;
    }
    if (o->tick < o->life) {
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
        o->f50 += o->spin;
        o->z += o->dz;
    }
    o->tick++;
    return 0;
}

/* shape b394:01E01E40, 144 insns: b594:01E02CB0 with a 0xA0/0x70/0xA0 sprite and an angle h5A from 90 turning 12 per tick (kept under 360); alpha up by 6 to 0x60 until scene count 470 (ctx+0x86DA), then down by 3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b394_01E01E40;

typedef struct {
    f32 s, t;
    Xyz_b394_01E01E40 p;
} Tv_b394_01E01E40;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b394_01E01E40 v[2];
    u8 tail[0x20];
} Tex_b394_01E01E40;

typedef struct {
    u8 pad0[0x86DA];
    s16 count;
} Ctx_b394_01E01E40;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b394_01E01E40;

static s32 func_01E01E40_b394(Ctx_b394_01E01E40 *g, Fx_b394_01E01E40 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b394_01E01E40 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->ang = 90;
        o->mode = 2;
    }
    ((Tex_b394_01E01E40 *)(s32)&pk)->flags = 0x26;
    ((Tex_b394_01E01E40 *)(s32)&pk)->size = 5;
    ((Tex_b394_01E01E40 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b394_01E01E40 *)(s32)&pk)->pad4 = 0;
    pk.r = 0xA0;
    pk.g = 0x70;
    pk.b = 0xA0;
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    o->ang += 12;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    if (g->count < 470) {
        if (o->col[3] < 0x60) {
            o->col[3] += 6;
        }
    } else if (o->col[3] > 4) {
        o->col[3] -= 3;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b394:01E02080 (b394), 403 insns, 1 copy: the module scene manager (b615:01E022D0 form): with a scene id it
   clears the scene, sets the 570-frame countdown, reads seven model ids, textures 4:15 and 5:0..1, the camera turn,
   scale 0.1 and the jitter tables; otherwise it runs the scene script b394:01E01420, every effect handler, draws the
   three effect kinds, counts down and returns the next step by frame (290, 540, 535, 301..529) or 8 when the
   countdown runs out */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b394_01E02080;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b394_01E02080 fx[300];
    u8 pad85E0[0x8630 - 0x85E0];
    s32 tex2[2];
    u8 pad8638[0x38];
    s32 count;
    u8 pad8674[8];
    s32 ot;
    u8 pad8680[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad86B0[4];
    s16 cam;
    u8 pad86B6[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b394_01E02080;

static s32 func_01E02080_b394(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01420_b394();
    Scene_b394_01E02080 *g = (Scene_b394_01E02080 *)arg0;
    s32 k;
    s32 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x8A50);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 570;
        g->jA = func_001F5560(func_001F53A0(), 0x13, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x25, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x40, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x48, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 15; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        for (k = 0; k < 2; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 20 + 4;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    func_01E01420_b394(g, 0);
    for (i = 0; i < 300; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 300; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01870_b394) {
                g->tex88 = g->tex2[0];
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00E70_b394((void *)g, (void *)&g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[i].fn == func_01E01AA0_b394) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[1];
                g->hB8 = 1;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b394((void *)g, (void *)&g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01C50_b394) {
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->tex88 = g->tex2[1];
                g->hB8 = 1;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b394((void *)g, (void *)&g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 290) {
        return 1;
    }
    if (g->frame == 540) {
        return 4;
    }
    if (g->frame == 535) {
        return 2;
    }
    if (g->frame > 300 && g->frame < 530) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b394:01E026D0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x12c of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b394_01E026D0 {
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
} Slot_b394_01E026D0;

typedef struct Obj_b394_01E026D0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b394_01E026D0 slots[0x12c];
    u8 padB[0x8674 - 0x2a0 - 0x12c * 0x70];
    u8 rgba[4];
    u8 padC[0x86d2 - 0x8674 - 4];
    s16 fB2B0;
} Obj_b394_01E026D0;

static s32 func_01E026D0_b394(Obj_b394_01E026D0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b394_01E026D0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x12c; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x12c;
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
