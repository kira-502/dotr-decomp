#include "common.h"

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

static void func_01E00080_b588(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b588 in the
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

static void func_01E004D0_b588(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b588((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00790_b588(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E00AF0_b588(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b588:01E00E60 (B588_W_S), 293 insns, 1 copy: the b588 module's event step: scene colour red 0x80; counts
   ticks; at 205 (joint 0xA94E) and 220 (joint 0xA950) two b588:01E025F0 at 45 and 135 degrees, b588:01E02500 and 20
   each of b588:01E01B10 and b588:01E01D00; from 131 to 170 two b588:01E01EF0 and b588:01E015B0 on joint 0xA94C; from
   90 to 125 two b588:01E02270 there; at 129 twenty b588:01E01300 there; from 40 to 90 two b588:01E01920 on joint
   0xA952, lowered 7 and pushed 5 along z (back when the game value at 0xA96A is set) */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0xA904 - 0x2E0];
    u8 col[4];
    u8 padA908[0xA94C - 0xA908];
    s16 jC;
    s16 jA;
    s16 jB;
    s16 jD;
    u8 padA954[0xA95E - 0xA954];
    s16 ang;
    u8 padA960[6];
    s16 flag;
    u8 padA968[2];
    s16 v;
    s16 timer;
} Ctx_b588_01E00E60;

static void func_01E00E60_b588(Ctx_b588_01E00E60 *g) {
    extern s32 b588_01E01300(void);
    extern s32 b588_01E015B0(void);
    extern s32 b588_01E01920(void);
    extern s32 b588_01E01B10(void);
    extern s32 b588_01E01D00(void);
    extern s32 b588_01E01EF0(void);
    extern s32 b588_01E02270(void);
    extern s32 b588_01E02500(void);
    extern s32 b588_01E025F0(void);
    extern void b588_01E030A0(Ctx_b588_01E00E60 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 205) {
        func_001F5620(func_001F53A0(), g->jA, &g->pos);
        g->ang = 45;
        g->flag = 0;
        b588_01E030A0(g, b588_01E025F0, 0);
        g->ang = 135;
        g->flag = 1;
        b588_01E030A0(g, b588_01E025F0, 0);
        b588_01E030A0(g, b588_01E02500, 0);
        for (i = 0; i < 20; i++) {
            b588_01E030A0(g, b588_01E01B10, 0);
        }
        for (i = 0; i < 20; i++) {
            b588_01E030A0(g, b588_01E01D00, 0);
        }
    }
    if (g->timer == 220) {
        func_001F5620(func_001F53A0(), g->jB, &g->pos);
        g->ang = 135;
        g->flag = 0;
        b588_01E030A0(g, b588_01E025F0, 0);
        g->ang = 45;
        g->flag = 1;
        b588_01E030A0(g, b588_01E025F0, 0);
        b588_01E030A0(g, b588_01E02500, 0);
        for (i = 0; i < 20; i++) {
            b588_01E030A0(g, b588_01E01B10, 0);
        }
        for (i = 0; i < 20; i++) {
            b588_01E030A0(g, b588_01E01D00, 0);
        }
    }
    if (g->timer >= 131 && g->timer < 171) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
        b588_01E030A0(g, b588_01E01EF0, 0);
        b588_01E030A0(g, b588_01E01EF0, 0);
        b588_01E030A0(g, b588_01E015B0, 0);
    }
    if (g->timer >= 90 && g->timer < 126) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
        b588_01E030A0(g, b588_01E02270, 0);
        b588_01E030A0(g, b588_01E02270, 0);
    }
    if (g->timer == 129) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
        for (i = 0; i < 20; i++) {
            b588_01E030A0(g, b588_01E01300, 0);
        }
    }
    if (g->timer >= 40 && g->timer < 91) {
        func_001F5620(func_001F53A0(), g->jD, &g->pos);
        g->pos.y -= 7.0f;
        if (g->v != 0) {
            g->pos.z -= 5.0f;
        } else {
            g->pos.z += 5.0f;
        }
        b588_01E030A0(g, b588_01E01920, 0);
        b588_01E030A0(g, b588_01E01920, 0);
    }
}

/* shape b588:01E01300, 171 insns: a purple (0x80, 0x40, 0xFF) square flake (size 50 growing 1, kind 2..4, angle 0..359, frame 0..3) drifting (-50..49)/60 per axis and tumbling by random spins; alpha up by 0x40 to 0x80 for 8 ticks, then down by 4 */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
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
} Fx_b588_01E01300;

static s32 func_01E01300_b588(s32 arg0, Fx_b588_01E01300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 50;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
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
    if (o->tick < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        o->w++;
        o->h = o->w;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b588:01E015B0, 218 insns: b256:01E02540's spark in green (0x40, 0xFF, 0x40), 50..89 wide growing by 5 to
   130 every third tick, drift /400 in x/y, sinking 0.09 a tick and moving 3 along z by the scene flag (ctx+0xA96A);
   fades in for 40 ticks then out by 9 */

typedef struct {
    u8 pad0[0xA96A];
    s16 flag;
} Ctx_b588_01E015B0;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b588_01E015B0;

static s32 func_01E015B0_b588(Ctx_b588_01E015B0 *ctx, Obj_b588_01E015B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = func_0019A5C8() % 40 + 50;
        o->hA = o->h8 + 4;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x40, 0xFF, 0x40);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h52 = func_0019A5C8() % 4;
    }
    if (o->t < 40) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->h8 < 130) {
            o->h8 += 5;
        }
        o->hA = o->h8;
    }
    if (o->t != 0) {
        if (ctx->flag != 0) {
            o->z -= 3.0f;
        } else {
            o->z += 3.0f;
        }
        o->x += o->f30;
        o->y += o->f34 - 0.09f;
    }
    func_00205C40((s32)o->rot);
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    return 0;
}

/* shape b588:01E01920, 123 insns: b256:01E02DF0 family spark (size 80, white, kick 8.6, drift 0.6 on z/x, random frame 0..3) */

typedef struct {
    u8 pad0000[0xAB70];
    u8 tab[1];
} Mgr_b588_01E01920;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b588_01E01920;

static s32 func_01E01920_b588(Mgr_b588_01E01920 *m, Obj_b588_01E01920 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 0x50;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h58 = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->f18 += 8.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 8.6f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 0x13;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f18 += 0.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.6f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b588:01E01B10, 123 insns: b256:01E02DF0 family spark (size 130, green, kick 3.6, drift 1.6 on y/x, random frame 0..3) */

typedef struct {
    u8 pad0000[0xAB70];
    u8 tab[1];
} Mgr_b588_01E01B10;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b588_01E01B10;

static s32 func_01E01B10_b588(Mgr_b588_01E01B10 *m, Obj_b588_01E01B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 0x82;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0x40, 0xFF, 0x40);
        o->h58 = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->f18 += 3.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 3.6f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 0x13;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f14 += 1.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 1.6f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b588:01E01D00, 123 insns: b256:01E02DF0 family spark (size 130, orange, kick 3.6, drift 1.8 on y/x, random frame 0..3) */

typedef struct {
    u8 pad0000[0xAB70];
    u8 tab[1];
} Mgr_b588_01E01D00;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b588_01E01D00;

static s32 func_01E01D00_b588(Mgr_b588_01E01D00 *m, Obj_b588_01E01D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 0x82;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0x80, 0x10, 0xFF);
        o->h58 = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->f18 += 3.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 3.6f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 0x13;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f14 += 1.8f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 1.8f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b588:01E01EF0 (B588_OBJ_MOVE_10_), 221 insns: a blue spark: size 50..79 (+4 for fA), kind (rand >> 4) % 3,
   colour (0x10, 0x10, 0xFF), drift (rand % 100 - 50) / 400 in x and y, random spin rates -0x400..0x3FF on all three
   axes and a random start angle; brightens by 0x40 below 0x80 for 50 ticks, then fades by 9; every third tick it
   grows by 5 up to 150; while moving it slides 2.7 in z (the sign by the game value at 0xA96A) and sinks 0.09 */

typedef struct {
    s16 r[3];
    u8 pad6[2];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 pos[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x1A];
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b588_01E01EF0;

typedef struct {
    u8 pad[0xA96A];
    s16 v;
} Game_b588_01E01EF0;

static s32 func_01E01EF0_b588(Game_b588_01E01EF0 *g, Fx_b588_01E01EF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f8 = func_0019A5C8() % 30 + 50;
        o->fA = o->f8 + 4;
        o->f56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x10, 0x10, 0xFF);
        o->mode = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40(o->pos);
        o->r[2] = func_0019A5C8() % 0x800 - 0x400;
        o->r[1] = func_0019A5C8() % 0x800 - 0x400;
        o->r[0] = func_0019A5C8() % 0x800 - 0x400;
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = func_0019A5C8() % 4;
    }
    if (o->tick < 50) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        if (o->f8 < 150) {
            o->f8 += 5;
        }
        o->fA = o->f8;
    }
    if (o->tick != 0) {
        if (g->v != 0) {
            o->f18 -= 2.7f;
        } else {
            o->f18 += 2.7f;
        }
        o->f10 += o->f30;
        o->f14 += o->f34 - 0.09f;
    }
    func_00205C40(o->pos);
    o->pos[2] += o->r[2];
    o->pos[1] += o->r[1];
    o->pos[0] += o->r[0];
    o->tick++;
    return 0;
}

/* shape b588:01E02270, 161 insns: b482:01E02180 in purple (0x80, 0x40, 0xFF), size 50 x 25, sinking 1 per tick and spinning by its random spins */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
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
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b588_01E02270;

static s32 func_01E02270_b588(s32 arg0, Spark_b588_01E02270 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 50;
        o->h = o->w >> 1;
        o->kind = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[1] -= 1.0f;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b588:01E02500, 59 insns: constant variant of b415:01E022B0 (220.0f->140.0f, colour (192, 255, 192), colour (64, 255, 64)) */

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
} Fx_b588_01E02500;

static s32 func_01E02500_b588(s32 arg0, Fx_b588_01E02500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 140.0f;
        func_001076F0(o->col2, 0xC0, 0xFF, 0xC0);
        func_001076F0(o->col, 0x40, 0xFF, 0x40);
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

/* shape b588:01E025F0, 97 insns: b481:01E02690 twin (green): kind 0 from 1000 growing 40, kind 1 from 250 growing 20, kind 2 400 fixed */

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
} Obj_b588_01E025F0;

static s32 func_01E025F0_b588(s32 arg0, Obj_b588_01E025F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0x80, 0xFF, 0x80);
        func_001076F0(o->col2, 0x10, 0xFF, 0x10);
        if (o->h50 == 0) {
            o->f30 = 18.0f;
            o->f34 = 1000.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 18.0f;
            o->f34 = 250.0f;
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
        o->f34 += 40.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 20.0f;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02780_b588(void) {
    return 0;
}

/* shape b588:01E02790, b734:01E03310 family: textures group 4 cells 0-2 and 14-15, group 5 cells 0-2 (table past 0x8000) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 padT[0xa560];
    s32 tex5[3];
} Scene_b588_01E02790;

static void func_01E02790_b588(s32 arg0, Scene_b588_01E02790 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b588:01E02840 (b588), 533 insns, 1 copy: b588 scene manager in b544:01E02B10 form: setup (six joints,
   textures, camera turn, two s8 jitter tables), step the 320 slots counting the b588:01E02780 ones, draw the seven
   IWMagicSmoke3 sprite kinds, the IWMagicCircleG4_8 ring and the IWMagicEye1 pair; scene code from the timer */

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
} Fx_b588_01E02840;

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
    Fx_b588_01E02840 fx[320];
    u8 pad8F80[0xA8E0 - 0x8F80];
    s32 tex2[3];
    u8 padA8EC[0x14];
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
} Scene_b588_01E02840;

static s32 func_01E02840_b588(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00E60_b588();
    extern void func_01E00790_b588();
    extern void func_01E02790_b588();
    Scene_b588_01E02840 *g = (Scene_b588_01E02840 *)arg0;
    s16 c;
    s32 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
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
        g->count = 270;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        g->jA = func_001F5560(func_001F53A0(), 0x11, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x58, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x5F, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x1, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x4A, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x50, 0);
        func_01E02790_b588(0, g);
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
    func_01E00E60_b588(g, 0);
    for (i = 0; i < 320; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != (s32 (*)())func_01E02780_b588) {
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
            if (g->fx[i].fn == (s32 (*)())func_01E01300_b588) {
                g->tex88 = g->tex2[1];
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
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E015B0_b588) {
                g->tex88 = g->tex2[1];
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
                g->hBE = g->fx[i].h52;
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01920_b588) {
                g->tex88 = g->tex2[2];
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hBE = g->fx[i].h52;
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x10, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01B10_b588) {
                g->tex88 = g->tex2[2];
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->hBE = g->fx[i].h52;
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x11, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01D00_b588) {
                g->tex88 = g->tex2[1];
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
                g->hBE = g->fx[i].h52;
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01EF0_b588) {
                g->tex88 = g->tex2[0];
                func_00106080(rm4, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm4;
                g->hBE = g->fx[i].h52;
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02270_b588) {
                g->tex88 = g->tex2[1];
                func_00106080(rm5, 0x9B, g->fx[i].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm5;
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
                func_01E004D0_b588((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02500_b588) {
                g->hB8 = 0x24;
                func_01E00790_b588(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E025F0_b588) {
                g->tex88 = g->tex[15];
                func_00106080(rm6, 0x9A, 0, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm6;
                g->hBE = 0;
                func_01E00AF0_b588((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, g->fx[i].pos);
                func_01E00AF0_b588((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, g->fx[i].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x8C) {
        return 1;
    }
    if (g->frame == 0x104) {
        return 4;
    }
    if (g->frame == 0xF0) {
        return 2;
    }
    if (g->frame > 0x91 && g->frame < 0xEB) {
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

static s32 func_01E030A0_b588(Pool_b544_01E031D0 *o, s32 a, s32 b) {
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
