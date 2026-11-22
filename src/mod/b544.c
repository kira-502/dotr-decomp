#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b544(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00100_b544(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00550_b544(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b544 in the
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

static void func_01E00990_b544(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00100_b544((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b016_01E01190;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b016_01E01190;

typedef struct {
    u8 pad00[0x20];
    Vec_b016_01E01190 rotation;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b016_01E01190;

static void func_01E00C50_b544(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b016_01E01190 c;
    Vec_b016_01E01190 quad[4];
    Vec_b016_01E01190 pos;
    Vec_b016_01E01190 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = data->height;
    quad[3].y = data->height;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
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

static void func_01E00FB0_b544(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b544:01E01320, 242 insns: the b544 module's event step: red scene colour, counts ticks (0xA96C); at 85 spawns
   b544:01E01F70 (slot 0, then slot 1); at 1 b544:01E02870; at 89 puts the point (0x2D0) on joint 0xA94E and spawns
   b544:01E01BB0, 40 b544:01E01CA0 and four b544:01E01DE0 (angle 0x95E 0/90/45/135, slots 0/1/2/2); before 75 spawns
   b544:01E016F0 then b544:01E01950 at joints 0xA950 and 0xA952, x jittered by -10..9 */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0xA904 - 0x2E0];
    u8 col[4];
    u8 padA908[0xA94E - 0xA908];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 padA954[0xA95E - 0xA954];
    s16 ang;
    u8 padA960[6];
    s16 slot;
    u8 padA968[4];
    s16 count;
} Ctx_b544_01E01320;

static void func_01E01320_b544(Ctx_b544_01E01320 *g) {
    extern s32 b544_01E016F0(void);
    extern s32 b544_01E01950(void);
    extern s32 b544_01E01BB0(void);
    extern s32 b544_01E01CA0(void);
    extern s32 b544_01E01DE0(void);
    extern s32 b544_01E01F70(void);
    extern s32 b544_01E02870(void);
    extern void b544_01E031D0(Ctx_b544_01E01320 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count == 85) {
        g->slot = 0;
        b544_01E031D0(g, b544_01E01F70, 0);
        g->slot = 1;
    }
    if (g->count == 1) {
        b544_01E031D0(g, b544_01E02870, 0);
    }
    if (g->count == 89) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        b544_01E031D0(g, b544_01E01BB0, 0);
        for (i = 0; i < 40; i++) {
            b544_01E031D0(g, b544_01E01CA0, 0);
        }
        g->ang = 0;
        g->slot = 0;
        b544_01E031D0(g, b544_01E01DE0, 0);
        g->ang = 90;
        g->slot = 1;
        b544_01E031D0(g, b544_01E01DE0, 0);
        g->ang = 45;
        g->slot = 2;
        b544_01E031D0(g, b544_01E01DE0, 0);
        g->ang = 135;
        g->slot = 2;
        b544_01E031D0(g, b544_01E01DE0, 0);
    }
    if (g->count < 75) {
        func_001F5620(func_001F53A0(), g->j1, &g->pos);
        g->pos.x += func_0019A5C8() % 20 - 10;
        b544_01E031D0(g, b544_01E016F0, 0);
        func_001F5620(func_001F53A0(), g->j2, &g->pos);
        g->pos.x += func_0019A5C8() % 20 - 10;
        b544_01E031D0(g, b544_01E016F0, 0);
        func_001F5620(func_001F53A0(), g->j1, &g->pos);
        g->pos.x += func_0019A5C8() % 20 - 10;
        b544_01E031D0(g, b544_01E01950, 0);
        func_001F5620(func_001F53A0(), g->j2, &g->pos);
        g->pos.x += func_0019A5C8() % 20 - 10;
        b544_01E031D0(g, b544_01E01950, 0);
    }
}

/* shape b544:01E016F0, 151 insns: b354:01E022F0's tumbling chip in red (0xFF, 0x40, 0x40), size 100 (half kept in 0xA) */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b544_01E016F0;

static s32 func_01E016F0_b544(s32 arg0, Fx_b544_01E016F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 100;
        o->size0 = o->size >> 1;
        o->frame = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 60.0f;
        o->vx /= 60.0f;
        o->vz /= 60.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->rot[2] += o->tz;
    o->rot[1] += o->ty;
    o->rot[0] += o->tx;
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b544:01E01950, 152 insns: b533:01E02090's dark grey tumbling chip, size 200 (half kept in 0xA) */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b544_01E01950;

static s32 func_01E01950_b544(s32 arg0, Fx_b544_01E01950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 200;
        o->size0 = o->size >> 1;
        o->frame = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 60.0f;
        o->vx /= 60.0f;
        o->vz /= 60.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->rot[2] += o->tz;
    o->rot[1] += o->ty;
    o->rot[0] += o->tx;
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b415:01E022B0, 59 insns: a spinning flash: on start size 220, colours white and (0xFF,0x40,0x40), f5A/f5C
   10, second alpha 0; it grows by 0x60 (below 0xC0) for 14 ticks, then fades out by 9 and stops; the
   rotation turns by 0x4000 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 vol;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b415_01E022B0;

static s32 func_01E01BB0_b544(s32 arg0, Fx_b415_01E022B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 220.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xE) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 0xA) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b544:01E01CA0, 79 insns: a white rising ring (b004:01E006B0 shape at 0x60): grows by 4 up to 70, rises 2 a frame from 5 and
   ends past 180, random turn on all three axes; fades both alphas by 12 from height 60 */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 size;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[0x2C];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b544_01E01CA0;

static s32 func_01E01CA0_b544(void *arg0, Obj_b544_01E01CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->size < 0x46) {
        o->size += 4;
    }
    o->y += 2;
    func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    if (o->y > 0xB4) {
        o->state = 0;
    }
    if (o->state == 1) {
        o->y = 5;
        o->x = 0;
        o->z = 0;
        o->size = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->c0[3] = 0xC0;
        o->state = 2;
    }
    if (o->y >= 0x3C) {
        if (o->c0[3] > 0xD) {
            o->c0[3] -= 0xC;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xD) {
            o->c1[3] -= 0xC;
        }
    }
    return 0;
}

/* shape b544:01E01DE0, 97 insns: b481:01E02690 twin (white/red): kind 0 from 800 growing 80, kind 1 from 500 growing 60, kind 2 400 fixed */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b544_01E01DE0;

static s32 func_01E01DE0_b544(s32 arg0, Obj_b544_01E01DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        if (o->h50 == 0) {
            o->f30 = 18.0f;
            o->f34 = 800.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 18.0f;
            o->f34 = 500.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 18.0f;
            o->f34 = 400.0f;
        }
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
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 80.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 60.0f;
    }
    o->t++;
    return 0;
}

/* shape b544:01E01F70 (B544_OBJ_MOVE_15_), 575 insns, 1 copy: b495:01E02140 with 20-point trails at 0x8FD0: on start
   fill trails 0-7 or 10-17 from joints 0xA94C/0xA94E or 0xA950/0xA952, each next trail 1.4 lower; push the joint
   positions into them until scene frame 98, alpha full until frame 97 then fading by 9 */

typedef struct {
    f32 x, y, z, w;
} Pt_b544_01E01F70;

typedef struct {
    u8 pad0[0x8FD0];
    Pt_b544_01E01F70 t[18][20];
    u8 padA650[0x2FC];
    s16 j[4];
    u8 padECD4[0x18];
    s16 frame;
} Scene_b544_01E01F70;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 side;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b544_01E01F70;

static inline void fill_b544_01E01F70(Pt_b544_01E01F70 *q, Vec4f *p) {
    s32 i;

    for (i = 0; i < 19; i++, q++) {
        q->x = p->x;
        q->y = p->y;
        q->z = p->z;
    }
}

static s32 func_01E01F70_b544(Scene_b544_01E01F70 *g, Fx_b544_01E01F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f p;
    s32 i;
    Pt_b544_01E01F70 *q;

    func_001076F0(o->col, 0xC0, 0x20, 0x20);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        if (o->side == 0) {
            o->hE = 30;
            func_001F5620(func_001F53A0(), g->j[0], &p);
            fill_b544_01E01F70(g->t[0], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[1], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[2], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[3], &p);
            func_001F5620(func_001F53A0(), g->j[1], &p);
            fill_b544_01E01F70(g->t[4], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[5], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[6], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[7], &p);
        }
        if (o->side == 1) {
            o->hE = 30;
            func_001F5620(func_001F53A0(), g->j[2], &p);
            fill_b544_01E01F70(g->t[10], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[11], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[12], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[13], &p);
            func_001F5620(func_001F53A0(), g->j[3], &p);
            fill_b544_01E01F70(g->t[14], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[15], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[16], &p);
            p.y -= 1.4f;
            fill_b544_01E01F70(g->t[17], &p);
        }
        o->mode = 2;
    }
    if (g->frame < 97) {
        o->col[3] = 0xFF;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->side == 0) {
        if (g->frame < 98) {
            func_001F5620(func_001F53A0(), g->j[0], &p);
            func_01E00080_b544((Vec4f *)&g->t[0][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[1][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[2][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[3][19], 20, 0, &p);
            func_001F5620(func_001F53A0(), g->j[1], &p);
            func_01E00080_b544((Vec4f *)&g->t[4][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[5][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[6][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[7][19], 20, 0, &p);
        }
    }
    if (o->side == 1) {
        if (g->frame < 98) {
            func_001F5620(func_001F53A0(), g->j[2], &p);
            func_01E00080_b544((Vec4f *)&g->t[10][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[11][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[12][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[13][19], 20, 0, &p);
            func_001F5620(func_001F53A0(), g->j[3], &p);
            func_01E00080_b544((Vec4f *)&g->t[14][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[15][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[16][19], 20, 0, &p);
            p.y -= 1.4f;
            func_01E00080_b544((Vec4f *)&g->t[17][19], 20, 0, &p);
        }
    }
    o->h6 = 13;
    o->t++;
    return 0;
}

/* shape b544:01E02870, 117 insns: a grey full-screen veil in its own colour (b215:01E02390 shape): one sprite over the whole
   screen; alpha up by 20 to 0x50 while the scene timer is over 20, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b544_01E02870;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b544_01E02870 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b544_01E02870;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b544_01E02870;

typedef struct {
    u8 pad0[0xA900];
    s32 timer;
} Scene_b544_01E02870;

static s32 func_01E02870_b544(Scene_b544_01E02870 *g, Obj_b544_01E02870 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_001076F0(void *, s32, s32, s32);
    Pkt_b544_01E02870 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->state = 2;
    }
    ((Pkt_b544_01E02870 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b544_01E02870 *)(s32)&pkt)->tag = 5;
    ((Pkt_b544_01E02870 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b544_01E02870 *)(s32)&pkt)->pad = 0;
    pkt.r = o->c0[0];
    pkt.g = o->c0[1];
    pkt.b = o->c0[2];
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b544_01E02870 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (g->timer > 0x14) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x14;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02A50_b544(void) {
    return 0;
}

/* shape b544:01E02A60, b734:01E03310 family: textures group 4 cells 0-2 and 14-15, group 5 cells 0-1 (table past 0x8000) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 padT[0xa560];
    s32 tex5[2];
} Scene_b544_01E02A60;

static void func_01E02A60_b544(s32 arg0, Scene_b544_01E02A60 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b544:01E02B10 (b544), 431 insns, 1 copy: b544 scene manager in b205:01E02420 / b631:01E01EF0 form: setup (six
   joints, textures, camera turn, two s8 jitter tables), step the 320 slots by their handlers counting the
   b544:01E02A50 ones, draw the two IWMagicSmoke3 sprite kinds, the IWMagicCircleG4_8 ring, PAINT_RAIN3, the
   IWMagicEye1 pair and the KPOINT_RAIN_3 ribbons (rows 0..2 or 10..12 with the rows 4 below); scene code from the
   timer */

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
} Fx_b544_01E02B10;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[8];
    } u;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x238];
    s32 w310;
    s32 w314;
    s32 w318;
    u8 pad31C[0x24];
    s32 tex[16];
    Fx_b544_01E02B10 fx[320];
    u8 pad8F80[0x50];
    Vec4f rows[17][20];
    u8 padA510[0xA8E0 - 0xA510];
    s32 tex2[2];
    u8 padA8E8[0x18];
    s32 count;
    u8 padA904[8];
    s32 ot;
    u8 padA910[0x3C];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padA958[0x10];
    s16 id;
    s16 turn;
    s16 frame;
    u8 padA96E[2];
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b544_01E02B10;

static s32 func_01E02B10_b544(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01320_b544();
    extern void func_01E00C50_b544();
    extern void func_01E02A60_b544();
    extern s32 func_01E01F70_b544();
    extern void b544_01E038C0();
    extern void b544_01E03370();
    Scene_b544_01E02B10 *g = (Scene_b544_01E02B10 *)arg0;
    s16 c;
    s32 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 k;
    s32 i;

    c = 0;
    n = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xACE0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 150;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        g->jA = func_001F5560(func_001F53A0(), 0x2C, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x2D, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xF, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x4A, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x50, 0);
        func_01E02A60_b544(0, g);
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    func_01E01320_b544(g, 0);
    for (i = 0; i < 320; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != (s32 (*)())func_01E02A50_b544) {
                    g->fx[i].fn(g, &g->fx[i]);
                } else {
                    c++;
                }
            }
        }
    }
    for (i = 0; i < 320; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == (s32 (*)())func_01E016F0_b544) {
                g->tex88 = g->tex2[0];
                func_00106080(rm, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hBE = g->fx[i].h52;
                if (g->fx[i].h56 < 2) {
                    g->u.uv[0] = g->fx[i].h56 << 6;
                    g->u.uv[1] = 0;
                } else {
                    g->u.uv[0] = (g->fx[i].h56 - 2) << 6;
                    g->u.uv[1] = 0x40;
                }
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                func_01E00990_b544((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01950_b544) {
                g->tex88 = g->tex2[1];
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hBE = g->fx[i].h52;
                func_01E00990_b544((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01BB0_b544) {
                g->hB8 = 0x24;
                func_01E00C50_b544(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01CA0_b544) {
                b544_01E038C0(g, &g->fx[i], buf, 0);
                b544_01E038C0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01DE0_b544) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9A, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->hBE = 0;
                func_01E00FB0_b544((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, g->fx[i].pos);
                func_01E00FB0_b544((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, g->fx[i].pos);
            }
            if (g->fx[i].fn == func_01E01F70_b544) {
                if (g->fx[i].h50 == 0) {
                    for (k = 0; k < 3; k++) {
                        b544_01E03370(g, &g->fx[i], g->rows[k], g->rows[k + 4]);
                    }
                }
                if (g->fx[i].h50 == 1) {
                    for (k = 10; k < 13; k++) {
                        b544_01E03370(g, &g->fx[i], g->rows[k], g->rows[k + 4]);
                    }
                }
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x51) {
        return 1;
    }
    if (g->frame == 0x91) {
        return 4;
    }
    if (g->frame == 0x7D) {
        return 2;
    }
    if (g->frame > 91 && g->frame < 120) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b544:01E031D0, 102 insns: b003:01E02E90 family: take the first free slot of the 320-slot pool, clear it,
   give it the scene's colour twice, the scene matrix and position, two scene values and the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 v50;
    u8 pad52[6];
    s16 used;
    s16 v5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b544_01E031D0;

typedef struct {
    u8 pad0[0x2D0];
    f32 x, y, z;
    u8 pad2DC[0xA4];
    Slot_b544_01E031D0 s[320];
    u8 pad8F80[0x1984];
    u8 r, g, b, a;
    u8 padA908[0x56];
    s16 v5E;
    u8 padA960[6];
    s16 v66;
} Pool_b544_01E031D0;

static s32 func_01E031D0_b544(Pool_b544_01E031D0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b544_01E031D0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 320; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x70);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 320;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, &o->x, 0);
        ret = 1;
        s->x = o->x;
        s->y = o->y;
        s->z = o->z;
        s->v50 = o->v66;
        s->v5A = o->v5E;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b544:01E03370 (B544KPOINT_RAIN_3), 340 insns, 1 copy: the B495KPOINT_RAIN_3 ribbon (b495:01E03750, quad
   corners copied as xyz fields) with the far edge fading by 3 per quad while above 4, as b481:01E05050 */

typedef struct Rgbaq_b544_01E03370 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b544_01E03370;

typedef struct {
    Rgbaq_b544_01E03370 c;
    u64 xyz;
} Vtx_b544_01E03370;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b544_01E03370 v[4];
    u8 tail[0x40];
} Pkt_b544_01E03370;

typedef struct {
    u8 r, g, b, a;
} C4_b544_01E03370;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b544_01E03370 col;
} Rib_b544_01E03370;

static inline u8 b544_01E03370_fade(s32 x) {
    s16 r = x;

    r -= 3;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E03370_b544(void *o, Rib_b544_01E03370 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b544_01E03370 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b544_01E03370 pkt __attribute__((aligned(8)));
    C4_b544_01E03370 c0;
    C4_b544_01E03370 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    Pkt_b544_01E03370 *p;
    s32 ot;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b544_01E03370 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - 4 > 0) {
                c1.a = b544_01E03370_fade(al);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E00550_b544(pp, 0, t);
                B[0] = func_01E00550_b544(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00550_b544(pp, 0, t);
                B[1] = func_01E00550_b544(pq, 0, t);
            } else {
                A[0] = func_01E00550_b544(a4, 0, t);
                B[0] = func_01E00550_b544(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00550_b544(a4, 0, t);
                B[1] = func_01E00550_b544(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}


/* shape b544:01E038C0, 253 insns: b499:01E03F70's hanging quad with texture 0x14 (page an->h56), colours at 0x60/0x64,
   the matrix from the anim's own float point (0x10) and rotation (0x20), the quad 4.7 wide, its lower edge kept
   above 0 right away; scene texture 0xA8E4, depth 0xA93C, into 0xA90C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b544_01E038C0;

typedef struct {
    Rgbaq_b544_01E038C0 c;
    u64 st;
    u64 xyz;
} Vtx_b544_01E038C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b544_01E038C0 v[4];
} Pkt_b544_01E038C0;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    f32 px, py, pz;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x26];
    s16 page;
    u8 pad58[8];
    u8 col[4];
    u8 col2[4];
} Anim_b544_01E038C0;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0x8FD0 - 0x2D0];
    u8 cam[0x150];
    u8 pad9120[0xA8E4 - 0x9120];
    s32 tex;
    u8 padA8E8[0xA90C - 0xA8E8];
    s32 ot;
    u8 padA910[0xA93C - 0xA910];
    f32 depth;
} Scene_b544_01E038C0;

static void func_01E038C0_b544(Scene_b544_01E038C0 *g, Anim_b544_01E038C0 *an, Pkt_b544_01E038C0 *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b544_01E038C0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00107130(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    f32 rm[4];

    if (lit == 0) {
        func_00106080(rm, 0x14, an->page, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_0020EB40(g->m);
    func_00107130(g->cam, v, 1);
    v[0] = an->px;
    v[1] = an->py;
    v[2] = an->pz;
    func_0020C940(m, 0, an->rot, v);
    func_0020BC00(g->m, m);
    q[0].x = an->x;
    q[0].y = an->y;
    q[0].z = an->z;
    q[1] = q[0];
    q[1].x += 4.7f;
    q[2].x = an->x;
    q[2].y = an->y;
    q[2].z = an->z;
    q[2].y -= an->h6;
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    q[3] = q[2];
    q[3].x += 4.7f;
    if (q[0].y > 200.0f) {
        q[0].y = 200.0f;
    }
    if (q[1].y > 200.0f) {
        q[1].y = 200.0f;
    }
    if (q[2].y > 200.0f) {
        q[2].y = 200.0f;
    }
    if (q[3].y > 200.0f) {
        q[3].y = 200.0f;
    }
    if (q[0].y < 0.0f) {
        q[0].y = 0.0f;
    }
    if (q[1].y < 0.0f) {
        q[1].y = 0.0f;
    }
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    if (q[3].y < 0.0f) {
        q[3].y = 0.0f;
    }
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}
