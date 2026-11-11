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

static void func_01E00080_b569(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b569 in the
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

static void func_01E00920_b569(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b569((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E00BE0_b569(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

/* shape b569:01E00FE0, 173 insns: b756:01E061D0 family burst draw: corner colours by the mode's high nibble (0: three of col2 then col, 1: two each), the scene rect (g+0x94, frame g+0xBE) and texture (g+0x88); scale 0.05 at the point with a random-free turn, then four quads of f30 x f34 turned by h5A in z through g+0xD8, depth-tested into g+0x80 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b569_01E00FE0;

typedef struct {
    Rgbaq_b569_01E00FE0 c;
    u64 st;
    u64 xyz;
} Vtx_b569_01E00FE0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b569_01E00FE0 v[4];
} Pkt_b569_01E00FE0;

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x22];
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b569_01E00FE0;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x18];
    u8 mD8[1];
} Game_b569_01E00FE0;

static void func_01E00FE0_b569(Game_b569_01E00FE0 *g, Obj_b569_01E00FE0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b569_01E00FE0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108D60(void *, s32, s32, s16);
    extern void func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 sc[4];
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    struct {
        Pkt_b569_01E00FE0 pk;
        u8 tail[0x20];
    } buf;
    s16 i;
    Pkt_b569_01E00FE0 *p = &buf.pk;
    s32 k;

    *(Vec4f *)pos = *in;
    func_00109270(p, 0, 0);
    k = mode >> 4;
    if (k == 0) {
        p->v[0].c = func_00107740(o->col2);
        p->v[1].c = func_00107740(o->col2);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col);
    } else if (k == 1) {
        p->v[0].c = func_00107740(o->col2);
        p->v[1].c = func_00107740(o->col2);
        p->v[2].c = func_00107740(o->col);
        p->v[3].c = func_00107740(o->col);
    }
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    sc[0] = 0.05f;
    sc[1] = 0.05f;
    sc[2] = 0.05f;
    func_00205C40((s32)rot);
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, sc, rot, v);
    rot[2] = o->h5A;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(q, o->f30, o->f34, i);
        func_00109100(q, rot, 2, g->mD8);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
    }
}

/* shape b569:01E012A0 (B569_W_S), 513 insns, 1 copy: B569_W_S, the scene timer script: counts the frame (0xB2B8);
   eight windows (35..43, 51..60, 72..81, 93..102, 114..124, 156..161, 175..183, 197..200) put the spawn point on
   joint 0xB244 and spawn three 0x1E021B0 each frame, three more on joint 0xB246 (162..167, 184..190, 200..205); frame
   207 reads joint 0xB248 into 0xB1D0; 207..220 copy it to the spawn point, spawn four 0x1E01E90 and two 0x1E01C60,
   and on 207 four 0x1E01AB0 at angles 0/90/45/135 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f v;
    u8 padB1E0[0xB244 - 0xB1E0];
    s16 j[3];
    u8 padB24A[0xB2A2 - 0xB24A];
    s16 ang;
    u8 padB2A4[0xB2B0 - 0xB2A4];
    s16 side;
    u8 padB2B2[0xB2B8 - 0xB2B2];
    s16 t;
} Scene_b569_01E012A0;

static void func_01E012A0_b569(Scene_b569_01E012A0 *g) {
    extern void b569_01E01AB0();
    extern void b569_01E01C60();
    extern void b569_01E01E90();
    extern void b569_01E021B0();
    extern void b569_01E02B80();
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t >= 35 && g->t < 44) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 51 && g->t < 61) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 72 && g->t < 82) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 93 && g->t < 103) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 114 && g->t < 125) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 156 && g->t < 162) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 175 && g->t < 184) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 197 && g->t < 201) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 162 && g->t < 168) {
        func_001F5620(func_001F53A0(), g->j[1], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 184 && g->t < 191) {
        func_001F5620(func_001F53A0(), g->j[1], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t >= 200 && g->t < 206) {
        func_001F5620(func_001F53A0(), g->j[1], &g->pos);
        for (i = 0; i < 3; i++) {
            b569_01E02B80(g, b569_01E021B0, 0);
        }
    }
    if (g->t == 207) {
        func_001F5620(func_001F53A0(), g->j[2], &g->v);
    }
    if (g->t >= 207 && g->t < 221) {
        g->pos = g->v;
        for (i = 0; i < 4; i++) {
            b569_01E02B80(g, b569_01E01E90, 0);
        }
        g->side = 0;
        for (i = 0; i < 2; i++) {
            b569_01E02B80(g, b569_01E01C60, 0);
        }
        if (g->t == 207) {
            g->ang = 0;
            g->side = 0;
            b569_01E02B80(g, b569_01E01AB0, 0);
            g->ang = 90;
            g->side = 0;
            b569_01E02B80(g, b569_01E01AB0, 0);
            g->ang = 45;
            g->side = 1;
            b569_01E02B80(g, b569_01E01AB0, 0);
            g->ang = 135;
            g->side = 1;
            b569_01E02B80(g, b569_01E01AB0, 0);
        }
    }
}

/* shape b569:01E01AB0, 107 insns: c062:01E033E0 family shock wave (white/blue, scale 6): kind 0 from 200 growing 120 (width 15 +0.3), kind 1 from 120 growing 60 (15 +0.3), kind 2 400 x 8 fixed; in by 64 up to 0x80 for 12 ticks, then out by 7 and ends; spins 6 a tick */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b569_01E01AB0;

static s32 func_01E01AB0_b569(s32 arg0, Obj_b569_01E01AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->h50 == 0) {
            o->f30 = 15.0f;
            o->f34 = 200.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 15.0f;
            o->f34 = 120.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->h52 = 0;
    }
    if (o->t < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0) {
        o->f34 += 120.0f;
        o->f30 += 0.3f;
    }
    if (o->h50 == 1) {
        o->f34 += 60.0f;
        o->f30 += 0.3f;
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

/* shape b569:01E01C60, 139 insns: b763:01E02200's growing puff in three kinds (purple / blue / green over grey 0x30), size 200, growth 55..59.9, fading by 14, f4C 0.3 of the size */

typedef struct {
    u8 pad00[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b569_01E01C60;

static s32 func_01E01C60_b569(void *arg0, Obj_b569_01E01C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 3;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0xC0, 0x80, 0xFF);
            func_001076F0(o->col2, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->col, 0xA0, 0xA0, 0xFF);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        }
        if (o->h50 == 2) {
            func_001076F0(o->col, 0x80, 0xFF, 0x80);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        }
        o->h5A = 30;
        o->h5C = 30;
        o->f34 = func_0019A5C8() % 300 + 550;
        o->f34 /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = 0.3f * o->f48;
    o->t++;
    return 0;
}

/* shape b569:01E01E90, 199 insns: b506:01E01240's flake in grey 0x80, 130 square growing 5 to 200, frame 0..2 and a
   random f52 0..3, held 12 ticks, drifting 0.8 a tick in z against the scene side flag (ctx+0xB2B4) */

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
} Fx_b569_01E01E90;

typedef struct {
    u8 pad0[0xB2B4];
    s16 side;
} Ctx_b569_01E01E90;

static s32 func_01E01E90_b569(Ctx_b569_01E01E90 *g, Fx_b569_01E01E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 130;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
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
    }
    if (o->tick < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 200) {
            o->w += 5;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        if (g->side != 0) {
            o->pos[2] -= 0.8f;
        } else {
            o->pos[2] += 0.8f;
        }
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b569:01E021B0, 202 insns: b569:01E01E90's flake 50 x 25 growing 3 to 100 (h stays half of w), rising
   0..49/60, drift /60 and /80 in z, moving 0.8 a tick along the scene side flag (ctx+0xB2B4) */

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
} Fx_b569_01E021B0;

typedef struct {
    u8 pad0[0xB2B4];
    s16 side;
} Ctx_b569_01E021B0;

static s32 func_01E021B0_b569(Ctx_b569_01E021B0 *g, Fx_b569_01E021B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 50;
        o->h = o->w >> 1;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 80.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 100) {
            o->w += 3;
        }
        o->h = o->w >> 1;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        if (g->side != 0) {
            o->pos[2] += 0.8f;
        } else {
            o->pos[2] -= 0.8f;
        }
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E024E0_b569(void) {
    return 0;
}

/* shape b569:01E024F0 (b569), 419 insns, 1 copy: b569 scene manager in b631:01E01EF0 form: setup (seven joints, two
   type-4 and one type-5 textures, 256 s8 and 30 s16 jitters), step b569:01E012A0 and every slot except b569:01E024E0,
   draw the b569:01E01AB0 eye, b569:01E01C60 ring and b569:01E01E90/01E021B0 smoke; scene code from the timer */

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
} Fx_b569_01E024F0;

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
    union {
        s32 rm[4];
        s16 uv[8];
    } u;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b569_01E024F0 fx[400];
    u8 padB1A0[0x50];
    s32 tex[1];
    u8 padB1F4[0x1C];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB250[4];
    s16 cam;
    u8 padB256[0xE];
    s16 jit16[30];
    u8 padB2A0[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BA[0x102];
    u8 crd[0x174];
} Scene_b569_01E024F0;

static s32 func_01E024F0_b569(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E012A0_b569();
    Scene_b569_01E024F0 *g = (Scene_b569_01E024F0 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 260;
        g->jA = func_001F5560(func_001F53A0(), 0x2F, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x37, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x13, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 1; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E012A0_b569(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E024E0_b569) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01AB0_b569) {
                g->tex88 = g->tex260[15];
                func_00106080(rm, 0x9A, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hBE = 0;
                func_01E00FE0_b569((Game_b569_01E00FE0 *)g, (Obj_b569_01E00FE0 *)&g->fx[k], 0, &g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C60_b569) {
                func_00106080(rm2, 0x96, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex260[15];
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 12;
                g->hBE = 0;
                func_01E00BE0_b569((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E90_b569) {
                g->tex88 = g->tex[0];
                func_00106080(rm3, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u.uv[0] = g->fx[k].h56 << 6;
                    g->u.uv[1] = 0;
                } else {
                    g->u.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u.uv[1] = 0x40;
                }
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                func_01E00920_b569((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021B0_b569) {
                g->tex88 = g->tex[0];
                func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm4;
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u.uv[0] = g->fx[k].h56 << 6;
                    g->u.uv[1] = 0;
                } else {
                    g->u.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u.uv[1] = 0x40;
                }
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                func_01E00920_b569((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x11, g->fx[k].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 197) {
        return 1;
    }
    if (g->frame == 255) {
        return 4;
    }
    if (g->frame == 207) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b569:01E02B80, 102 insns: takes the first free of 400 effect slots (0x70 bytes, b041:01E02C00 shape), clears and
   marks it, colours both from the scene, places it at the scene point, copies two settings and stores both arguments */

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
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b569_01E02B80;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b569_01E02B80 slot[400];
    u8 padEnd[0xB214 - 0x2A0 - 400 * 0x70];
    u8 col[4];
    u8 padB218[0x8A];
    s16 hB2A2;
    u8 padB2A4[0xC];
    s16 hB2B0;
} Scene_b569_01E02B80;

static s32 func_01E02B80_b569(Scene_b569_01E02B80 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b569_01E02B80 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 400; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 400;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->hB2B0;
        sl->h5A = s->hB2A2;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}
