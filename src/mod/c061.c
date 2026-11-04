#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_c061(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00110_c061(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
    }
}

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E00560_c061(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
        }
    }
}

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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_c061 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E008D0_c061(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_c061((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b038_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b038_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b038_01E00920;

typedef struct {
    u64 st;
    Xyz_b038_01E00920 p;
} Vtx_b038_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b038_01E00920 c;
    Vtx_b038_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b038_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b038_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b038_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    s16 tilt;
    u8 pad5E[2];
    u8 col[1];
} Anim_b038_01E00920;

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
} Obj_b038_01E00920;

extern void c061_01E00110(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00B90_c061(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    Vec_b038_01E00920 quad[4];
    Vec_b038_01E00920 d;
    Vec_b038_01E00920 pos;
    Vec_b038_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b038_01E00920 r;
    struct {
        u64 pre;
        Pkt_b038_01E00920 pk;
    } buf;
    Col_b038_01E00920 col;
    s16 i;
    Pkt_b038_01E00920 *p;
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
    r.rot[2] = an->tilt;
    r.v[1] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    c061_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 2, o->bD8);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 0, o->bD8);
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

INCLUDE_ASM("asm/nonmatchings/mod/c061", func_01E01100_c061);

/* shape c061:01E014F0 (B855_W_S), 427 insns, 1 copy: B855_W_S, the scene script: colour 0x80,0,0,0, counts the frame
   (0x68C8); loads joints and animations at 300..580, hides the side units at 663..803, spawns the empty handler
   (301), two shock waves (364), a 10-point spine of rising columns (753) and flashes (780..860); spins the spine and
   drags the point 0x56A0 toward joint 6 */

typedef struct {
    u8 pad0[0x250];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad25C[0x5670 - 0x25C];
    f32 k[3];
    u8 pad567C[0x56A0 - 0x567C];
    Vec4f a;
    u8 pad56B0[0x5710 - 0x56B0];
    Vec4f spine[10];
    Vec4f b;
    u8 pad57C0[0x6844 - 0x57C0];
    u8 r;
    u8 g;
    u8 bl;
    u8 al;
    u8 pad6848[0x6854 - 0x6848];
    f32 rad[10];
    u8 pad687C[4];
    s32 y;
    u8 pad6884[0x6894 - 0x6884];
    s16 ang[10];
    u8 pad68A8[2];
    s16 j1;
    s16 j2;
    u8 pad68AE[6];
    s16 j6;
    u8 pad68B6[6];
    s16 hBC;
    s16 hBE;
    u8 pad68C0[2];
    s16 hC2;
    s16 side;
    u8 pad68C6[2];
    s16 t;
    u8 pad68CA[0x69CC - 0x68CA];
    u8 trig[4];
} Scene_c061_01E014F0;

static void func_01E014F0_c061(Scene_c061_01E014F0 *g) {
    extern s32 func_001F2DD0(s32, s32, s32);
    extern s32 func_001F1550(s32, s32);
    extern s32 func_001F5970(s32, s32);
    extern void func_00261680(s32);
    extern void func_001F2EC0(s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern s32 c061_01E02CF0();
    extern s32 c061_01E01BA0();
    extern s32 c061_01E01F20();
    extern s32 c061_01E02320();
    extern s32 c061_01E033A0();
    extern s32 c061_01E03510();
    Vec4f v;
    s32 i;

    g->r = 0x80;
    g->g = 0;
    g->bl = 0;
    g->al = 0;
    g->t++;
    if (g->t == 330) {
        func_001F2DD0(0x20, 0xE, 0);
        func_001F2DD0(0x20, 0xF, 1);
    }
    if (g->t == 400) {
        func_001F2DD0(0x20, 0x23, 0);
        func_001F2DD0(0x20, 0x24, 1);
        func_001F2DD0(0x20, 0x27, 2);
        func_001F2DD0(0x20, 0x4C, 3);
        func_001F2DD0(0x20, 0x4D, 4);
        func_001F2DD0(0x20, 0x50, 5);
    }
    if (g->t == 580) {
        func_001F2DD0(0x20, 0x74, 0);
        func_001F2DD0(0x20, 0x81, 1);
        func_001F2DD0(0x20, 0x24, 2);
        func_001F2DD0(0x20, 0x50, 3);
        func_001F2DD0(0x20, 0xE, 4);
        func_001F2DD0(0x20, 0xF, 5);
        func_001F2DD0(0x20, 0x23, 6);
    }
    if (g->t == 300) {
        func_001F1550(0x20, 2);
    }
    if (g->t >= 663 && g->t < 804) {
        if (g->side == 0) {
            for (i = 0x100; i < 0x106; i++) {
                func_001F5970(i, 0);
                func_00261680(i);
            }
        } else if (g->side == 1) {
            for (i = 0; i < 6; i++) {
                func_001F5970(i, 0);
                func_00261680(i);
            }
        }
    }
    if (g->t == 301) {
        c061_01E03510(g, c061_01E02CF0, 0);
    }
    if (g->t == 753) {
        for (i = 0; i < 10; i++) {
            g->spine[i].y = i * 17 - 30;
        }
        g->rad[0] = 0.0f;
        for (i = 1; i < 10; i++) {
            g->rad[i] = 3.0f;
        }
        for (i = 0; i < 10; i++) {
            g->ang[i] = func_0019A5C8() % 360;
        }
        g->r = 0x20;
        g->g = 0x20;
        g->bl = 0x20;
        g->px = 0.0f;
        g->py = 30.0f;
        g->pz = 0.0f;
        for (i = 0; i < 1; i++) {
            g->hBE = 1;
            g->y = 0;
            g->hC2 = 1;
            g->hBC = 0;
            c061_01E033A0(g, c061_01E01BA0, 0);
        }
    }
    func_001F2EC0(0x20, g->j1, &v);
    for (i = 0; i < 10; i++) {
        if (i != 0) {
            g->spine[i].x = g->rad[i] * func_00108030(g->trig, g->ang[i], 1);
            g->spine[i].z = g->rad[i] * func_00108030(g->trig, g->ang[i], 0);
        } else {
            g->spine[i].x = g->rad[i] * func_00108030(g->trig, g->ang[i], 1);
            g->spine[i].z = g->rad[i] * func_00108030(g->trig, g->ang[i], 0);
        }
        g->ang[i] += 4;
        if (g->ang[i] >= 360) {
            g->ang[i] %= 360;
        }
    }
    if (g->t == 625 || (g->t >= 689 && g->t < 881)) {
        func_001F2EC0(0x20, g->j2, &g->a);
        func_001F2EC0(0x20, g->j6, &v);
        g->a.x += g->k[0] * (g->a.x - v.x);
        g->a.y += g->k[1] * (g->a.y - v.y);
        g->a.z += g->k[2] * (g->a.z - v.z);
        g->a.y += 25.0f;
        if (g->t >= 727) {
            if (g->k[0] < 1.0f) {
                g->k[0] += 0.01f;
            }
            if (g->k[1] < 1.0f) {
                g->k[1] += 0.01f;
            }
            if (g->k[2] < 1.0f) {
                g->k[2] += 0.01f;
            }
        }
    }
    g->b = g->a;
    if (g->t == 364) {
        g->hBC = 0;
        c061_01E03510(g, c061_01E01F20, 0);
        g->hBC = 90;
        c061_01E03510(g, c061_01E01F20, 0);
    }
    if (g->t == 757) {
        g->px = g->b.x;
        g->py = g->b.y;
        g->pz = g->b.z;
        for (i = 0; i < 16; i++) {
            g->hC2 = i;
            g->hBC = i * 45;
        }
    }
    if (g->t >= 780 && g->t < 861) {
        g->px = g->b.x;
        g->py = g->b.y;
        g->pz = g->b.z;
        g->hC2 = 0;
        c061_01E03510(g, c061_01E02320, 0);
    }
}

/* shape c061:01E01BA0, 223 insns: b056:01E012E0's rising column on the scene's 8-point spine (g+0x5710): both colours
   (0x78, 0x78, 0x20), no spin; alpha in by 10 to 0x50 below height 100, else out by 14; the first spine point above its
   top gives the two side points and widens 0x8A by 7 / 0x8C by 6 up to 20 / 19 per point; the top grows by 4 up to 80
   with the base kept within 18, then the base until it reaches the top, which ends its parent link; in state 1, with a
   base above 0, it publishes itself and the base to the scene (g+0x6850..0x68C2) and, while the scene count 0x68C8 is
   under 880, asks the module to run it (c061:01E033A0), entering state 2 */

typedef struct {
    u8 pad0[0x70];
    s32 w70;
} Link_c061_01E01BA0;

typedef struct {
    u8 pad0[4];
    f32 top;
    u8 pad8[0xC];
    f32 base;
    u8 pad18[0x18];
    s32 w30;
    s32 w34;
    s32 w38;
    u8 pad3C[4];
    Vec4f a;
    Vec4f b;
    u8 pad60[0x14];
    Link_c061_01E01BA0 *link;
    u8 pad78[8];
    u8 c80[4];
    u8 c84[4];
    s16 state;
    s16 h8A;
    s16 h8C;
    u8 pad8E[4];
    s16 ang;
} Obj_c061_01E01BA0;

typedef struct {
    u8 pad0[0x5710];
    Vec4f pts[8];
    u8 pad5790[0x6850 - 0x5790];
    Obj_c061_01E01BA0 *obj;
    u8 pad6854[0x28];
    f32 size;
    f32 base;
    u8 pad6884[0x38];
    s16 ang;
    s16 h68BE;
    u8 pad68C0[2];
    s16 h68C2;
    u8 pad68C4[4];
    s16 step;
} Scene_c061_01E01BA0;

static s32 func_01E01BA0_c061(Scene_c061_01E01BA0 *g, Obj_c061_01E01BA0 *o) {
    extern s32 c061_01E033A0(Scene_c061_01E01BA0 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern Vec4f func_001098E0(void *, void *, void *, void *);
    f32 v[4];
    s16 i;

    v[1] = 0.0f;
    func_001076F0(o->c80, 0x78, 0x78, 0x20);
    func_001076F0(o->c84, 0x78, 0x78, 0x20);
    o->w30 = 0;
    o->w34 = 0;
    o->w38 = 0;
    if (o->top < 100.0f) {
        if (o->c80[3] < 0x50) {
            o->c80[3] += 10;
        }
        if (o->c84[3] < 0x50) {
            o->c84[3] += 10;
        }
    } else {
        if (o->c80[3] > 16) {
            o->c80[3] -= 14;
        }
        if (o->c84[3] > 16) {
            o->c84[3] -= 14;
        }
    }
    for (i = 1; i < 8; i++) {
        if (!(g->pts[i].y <= o->top)) {
            v[0] = g->pts[0].x;
            v[2] = g->pts[0].z;
            o->a = func_001098E0(v, o, &g->pts[i - 1], &g->pts[i]);
            o->b = func_001098E0(v, o, &g->pts[i - 1], &g->pts[i]);
            if (o->h8A <= i * 20) {
                o->h8A += 7;
            }
            if (o->h8C <= i * 19) {
                o->h8C += 6;
            }
            i = 8;
        }
    }
    if (o->top <= 80.0f) {
        o->top += 4.0f;
        if (!(o->top - o->base <= 18.0f)) {
            o->base += 4.0f;
        }
    } else {
        o->base += 4.0f;
        if (!(o->base <= o->top)) {
            if (o->link != 0) {
                o->link->w70 = 0;
            }
            o->state = 0;
        }
    }
    if (o->state == 1) {
        if (!(o->base <= 0.0f)) {
            g->size = 14.0f;
            g->obj = o;
            g->h68BE = 1;
            g->base = o->base;
            g->h68C2 = 1;
            g->ang = o->ang - 15;
            if (g->step < 880) {
                if (c061_01E033A0(g, func_01E01BA0_c061, 0)) {
                    o->state = 2;
                }
            }
        }
    }
    return 0;
}

/* shape c061:01E01F20, 65 insns: a spinning shock wave (grey/red, from 300 growing 26): in by 64 up to 0x80 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_c061_01E01F20;

static s32 func_01E01F20_c061(s32 arg0, Obj_c061_01E01F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        func_001076F0(o->col2, 0xFF, 0x20, 0x20);
        o->f30 = 8.0f;
        o->f34 = 300.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f34 += 26.0f;
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

/* shape c061:01E02030, 185 insns: c063:01E04250 family yellow (0xFF, 0xFF, 0x40) flake 200 square growing 5 to 300, frame 0..2, sinking 1.5 and tumbling on all axes */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_c061_01E02030;

static s32 func_01E02030_c061(s32 arg0, Fx_c061_01E02030 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 200;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->hold = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 300) {
            o->w += 5;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        o->pos[1] -= 1.5f;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape c061:01E02320, 207 insns: c063:01E03430's flash in two kinds (0x50): kind 0 blue-white (0x80, 0x80, 0xFF), size 20
   growing by 180 with the inner size a fifth, spinning on all axes, alpha up for 15 ticks; kind 1 white, size 3000
   shrinking by 250 with the inner size half, alpha up for 7 ticks; second colour flickers (grey-yellow / blue) */

typedef struct {
    u8 pad0[1];
} Game_c061_01E02320;

typedef struct {
    s16 spin[3];
    s16 h6;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_c061_01E02320;

static s32 func_01E02320_c061(Game_c061_01E02320 *g, Obj_c061_01E02320 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 20.0f;
            o->f4C = 0.0f;
            func_001076F0(o->c0, 0x80, 0x80, 0xFF);
            o->h5A = 0x3C;
            o->h5C = 3;
            o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
            o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
            o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
            o->h6 = 15;
        }
        if (o->kind == 1) {
            o->f48 = 3000.0f;
            o->f4C = 0.0f;
            func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
            o->h5A = 0x3C;
            o->h5C = 2;
            o->sub = 3;
            o->h6 = 7;
        }
        o->sub = 4;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < o->h6) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0xA0, 0xA0, 0x60);
        } else {
            func_001076F0(o->c1, 0xC0, 0xC0, 0x60);
        }
        o->f48 += 180.0f;
        o->f4C = 0.2f * o->f48;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
    }
    if (o->kind == 1) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0x60, 0x60, 0xA0);
        } else {
            func_001076F0(o->c1, 0x60, 0x60, 0xC0);
        }
        o->f48 -= 250.0f;
        o->f4C = 0.5f * o->f48;
    }
    o->t++;
    return 0;
}

/* shape c061:01E02660, 182 insns: b386:01E02480 family grey (0x60) mote, size 300, frame 0..7, angles 0..359, 0x50 50..399, drift -20..19 unscaled; while the scene count (ctx+0x68C8) is under 500 alpha goes up by 0xC0 for 55 ticks then down by 11, after that down by 9; rises 3.3 a tick with its z pinned to the scene's 0x56B8 plus its drift */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    f32 z;
    u8 pad1C[0x14];
    f32 vel[3];
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 life;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_c061_01E02660;

typedef struct {
    u8 pad0[0x56B8];
    f32 z;
    u8 pad56BC[0x68C8 - 0x56BC];
    s16 count;
} Ctx_c061_01E02660;

static s32 func_01E02660_c061(Ctx_c061_01E02660 *g, Fx_c061_01E02660 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 300.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->side = 2;
        } else {
            o->side = 0;
        }
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 350 + 50;
        o->life = func_0019A5C8() % 350 + 100;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->mode = 2;
    }
    if (g->count < 500) {
        if (o->tick < 55) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0xC0;
            }
        } else if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->y += 3.3f;
    }
    o->z = g->z + o->vel[2];
    o->tick++;
    return 0;
}

/* shape c061:01E02940, 235 insns (B855_OBJ_MOVE_10_): a swinging light with a 13-point trail in the scene's trail
   table (g+0x57E0, 0xD0 per object): on start size 100, a random blink phase, both colours grey, the second one
   clear, scale 13 and step 4, and the whole trail set to its position; for 300 ticks both alphas grow by 0x13 (below
   0xC0), then the first fades by 14 and the object stops; the blink flag flips each tick; after the first tick it
   moves along its heading by the step, the heading swinging 20 (first 8 objects) or 10 either way by parity; z
   moves by 8 with the scene flag at g+0x68C6; for 300 ticks the scene light (g+0x250) follows it; colour 0xC0 on
   even ticks and 0xFF on odd ones; the trail shifts in the newest point (module K_Point_INPos), the rotation is
   normalised and the size grows to 12 */

typedef struct {
    Vec4f pt[13];
} Trail_c061_01E02940;

typedef struct {
    u8 pad0[0x250];
    Vec4f light;
    u8 pad260[0x57E0 - 0x260];
    Trail_c061_01E02940 trail[20];
    u8 pad6820[0x68C6 - 0x6820];
    s16 flag;
    u8 pad68C8[0x69CC - 0x68C8];
    u8 trig[1];
} Scene_c061_01E02940;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 step;
    s16 id;
    u8 pad52[2];
    s16 t;
    s16 blink;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_c061_01E02940;

static s32 func_01E02940_c061(Scene_c061_01E02940 *g, Obj_c061_01E02940 *o) {
    extern s32 c061_01E00080(Vec4f *, s32, s32, Vec4f *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f *p;
    s16 i;

    if (o->state == 1) {
        o->h8 = 100;
        o->hA = 100;
        o->blink = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->state = 2;
        o->col2[3] = 0;
        o->f48 = 13.0f;
        o->step = 4.0f;
        p = g->trail[o->id].pt;
        for (i = 0; i < 13; i++) {
            p[i].x = o->pos.x;
            p[i].y = o->pos.y;
            p[i].z = o->pos.z;
        }
    }
    if (o->t < 300) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x13;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x13;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->state = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->blink) {
        o->blink = 0;
    } else {
        o->blink = 1;
    }
    if (o->t != 0) {
        o->pos.y += o->step * func_00108030(g->trig, o->ang, 0);
        o->pos.x += o->step * func_00108030(g->trig, o->ang, 1);
        if (o->id < 8) {
            if (o->id % 2 != 0) {
                o->ang += 20;
            } else {
                o->ang -= 20;
            }
        } else {
            if (o->id % 2 != 0) {
                o->ang += 10;
            } else {
                o->ang -= 10;
            }
        }
    }
    if (g->flag != 0) {
        o->pos.z -= 8.0f;
    } else {
        o->pos.z += 8.0f;
    }
    if (o->t < 300) {
        g->light = o->pos;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    }
    c061_01E00080(&g->trail[o->id].pt[12], 13, 0, &o->pos);
    func_00205C40((s32)o->rot);
    if (o->t != 0) {
        if (o->h6 < 12) {
            o->h6++;
        }
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02CF0_c061(void) {
    return 0;
}

/* shape c061:01E02D00 (c061), 421 insns, 1 copy: c061 scene manager (b272:01E013C0 form): code >= 0 sets up
   (textures, joint ids 0..6, side flags, 256 jitters -15..14 with 100..179 zeroed, count 953), else run the script,
   step the 30 nodes and the 150 effects, draw the nodes (c061:01E03660 twice) and the five effect kinds; returns 8
   when the count runs out */

typedef struct {
    u8 pad0[0x88];
    s16 used;
    u8 pad8A[0xE];
} Node_c061_01E02D00;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_c061_01E02D00;

typedef struct {
    u8 pad0[0xD0];
} Trail_c061_01E02D00;

typedef struct {
    u8 pad0[0x20];
    f32 cx;
    f32 cy;
    f32 cz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 w[4];
        s16 h[8];
    } rm;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x1B8];
    s32 tex[16];
    Node_c061_01E02D00 node[30];
    Fx_c061_01E02D00 fx[150];
    u8 pad5640[0x1A0];
    Trail_c061_01E02D00 trail[20];
    s32 tex5[5];
    u8 pad6834[0xC];
    s32 count;
    u8 pad6844[8];
    s32 ot;
    u8 pad6850[0x58];
    s16 j[7];
    u8 pad68B6[0xE];
    s16 side;
    s16 side2;
    u8 pad68C8[2];
    s8 jit[0x100];
    u8 pad69CA[2];
    u8 crd[0x174];
} Scene_c061_01E02D00;

static s32 func_01E02D00_c061(s32 arg0, s32 code) {
    Scene_c061_01E02D00 *g = (Scene_c061_01E02D00 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F2EC0(s32, s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E014F0_c061();
    extern void func_01E01100_c061();
    extern void c061_01E03660();
    extern void c061_01E03D80();
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    u8 buf[0x90];
    s32 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x6B40);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 5; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        {
            s32 k;

            for (k = 0; k < 7; k++) {
                g->j[k] = k;
            }
        }
        if (func_001F53A0() == 0) {
            g->side = 0;
        } else {
            g->side = 1;
        }
        g->count = 953;
        if (g->side == 0) {
            g->side2 = 1;
        } else {
            g->side2 = 0;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = 0;
        }
        return 0;
    }
    func_01E014F0_c061(g, 0);
    for (i = 0; i < 30; i++) {
        if (g->node[i].used != 0) {
            func_01E01BA0_c061((Scene_c061_01E01BA0 *)g, (Obj_c061_01E01BA0 *)&g->node[i]);
        }
    }
    for (i = 0; i < 30; i++) {
        if (g->node[i].used != 0) {
            n++;
            c061_01E03660(g, &g->node[i], buf, 0);
            c061_01E03660(g, &g->node[i], buf, 1);
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == (s32 (*)())func_01E01F20_c061) {
                func_001F2EC0(0x20, g->j[1], &v);
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9A, 0, NULL);
                *(Vec4f *)g->rm.w = *(Vec4f *)rm;
                g->hBE = 0;
                v.w = 0.0f;
                func_01E00560_c061((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
                func_01E00560_c061((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
                func_001F2EC0(0x20, g->j[0], &v);
                v.w = 0.0f;
                func_01E00560_c061((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
                func_01E00560_c061((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02030_c061) {
                g->tex88 = g->tex5[4];
                g->hBE = g->fx[i].h52;
                if (g->fx[i].h56 < 2) {
                    g->rm.h[0] = g->fx[i].h56 << 6;
                    g->rm.h[1] = 0;
                } else {
                    g->rm.h[0] = (g->fx[i].h56 - 2) << 6;
                    g->rm.h[1] = 0x40;
                }
                g->rm.h[2] = 0x40;
                g->rm.h[3] = 0x40;
                func_01E008D0_c061((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x21, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02320_c061) {
                if (g->fx[i].h50 == 0) {
                    g->tex88 = g->tex[15];
                    func_00106080(rm2, 0x97, 0, NULL);
                    *(Vec4f *)g->rm.w = *(Vec4f *)rm2;
                }
                if (g->fx[i].h50 == 1) {
                    g->tex88 = g->tex[15];
                    func_00106080(rm3, 0x9B, g->fx[i].h56, NULL);
                    *(Vec4f *)g->rm.w = *(Vec4f *)rm3;
                }
                v = g->fx[i].pos;
                g->hB8 = 6;
                func_01E01100_c061(g, &g->fx[i], 0x20, v);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02660_c061) {
                func_00106080(rm4, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm.w = *(Vec4f *)rm4;
                g->hC0 = 0;
                g->tex88 = g->tex5[0];
                g->hB8 = 5;
                g->cx = g->fx[i].pos.x;
                g->cy = g->fx[i].pos.y;
                g->cz = g->fx[i].pos.z;
                g->hBE = 0;
                func_01E00B90_c061((void *)g, (void *)&g->fx[i], 0x10, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02940_c061) {
                g->tex88 = g->tex5[3];
                func_00106080(rm5, 0x14, 3, NULL);
                *(Vec4f *)g->rm.w = *(Vec4f *)rm5;
                g->hBE = 0;
                v.x = g->fx[i].pos.x;
                v.y = g->fx[i].pos.y;
                v.z = g->fx[i].pos.z;
                func_01E008D0_c061((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, v);
                g->tex88 = g->tex5[3];
                func_00106080(rm6, 0x14, 3, NULL);
                *(Vec4f *)g->rm.w = *(Vec4f *)rm6;
                g->rm.h[0] += 15;
                g->rm.h[2] = 1;
                g->cx = 0.0f;
                g->cy = 0.0f;
                g->cz = 0.0f;
                g->hBE = 1;
                c061_01E03D80(g, &g->fx[i], &g->trail[g->fx[i].h50], 0);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape c061:01E033A0, 89 insns: take a free node (0x1E of 0x98 bytes at 0x2D0), clear it, copy the scene vector
   0x250, 0x92/0x8E from 0x68BC/0x68C2, y = 0x6880 and 0x14 = y - 18, then push it on the scene's list (0x6850,
   prev 0x70 / next 0x74) with 0x94/0x96 = 1; returns 1 if a node was found */

typedef struct {
    f32 x, y, z, w;
} V4_c061_01E033A0;

typedef struct Node_c061_01E033A0 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    V4_c061_01E033A0 pos;
    u8 pad40[0x30];
    struct Node_c061_01E033A0 *prev;
    struct Node_c061_01E033A0 *next;
    u8 pad78[0x10];
    s16 used;
    u8 pad8A[4];
    s16 f8E;
    u8 pad90[2];
    s16 f92;
    s16 f94;
    s16 f96;
} Node_c061_01E033A0;

typedef struct {
    u8 pad0[0x250];
    V4_c061_01E033A0 pos;
    u8 pad260[0x70];
    Node_c061_01E033A0 nodes[0x1E];
    u8 pad14A0[0x6850 - 0x14A0];
    Node_c061_01E033A0 *head;
    u8 pad3924[0x2C];
    f32 y;
    u8 pad3954[0x38];
    s16 f398C;
    u8 pad398E[4];
    s16 f3992;
} Scene_c061_01E033A0;

static s32 func_01E033A0_c061(Scene_c061_01E033A0 *g) {
    extern void func_00195108();
    Node_c061_01E033A0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1E; i++) {
        if (g->nodes[i].used == 0) {
            func_00195108(&g->nodes[i], 0x98);
            g->nodes[i].used = 1;
            s = &g->nodes[i];
            i = 0x1E;
        }
    }
    if (s != NULL) {
        s->pos = g->pos;
        s->f92 = g->f398C;
        s->prev = g->head;
        s->f8E = g->f3992;
        if (s->prev == NULL) {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        } else {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        }
        s->prev = g->head;
        if (s->prev != NULL) {
            s->prev->next = s;
        }
        s->f94 = 1;
        s->f96 = 1;
        g->head = s;
        return 1;
    }
    return 0;
}

/* shape c061:01E03510, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x14A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_c061_01E03510;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x14a0 - 0x25C];
    Obj_c061_01E03510 slot[150];
    u8 padEnd[0x6844 - 0x14a0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad6848[0x74];
    s16 ang;
    u8 pad68BE[0x4];
    s16 h30;
} Ctx_c061_01E03510;

static s32 func_01E03510_c061(Ctx_c061_01E03510 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_c061_01E03510 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h5A = ctx->ang;
        s->h50 = ctx->h30;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c061", func_01E03660_c061);

INCLUDE_ASM("asm/nonmatchings/mod/c061", func_01E03D80_c061);
