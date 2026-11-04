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

static void func_01E00080_b552(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b056:01E00920, 240 insns, 5 copies: draws a row of small camera-facing sprites (count, or 20) at a given position,
   each shaken by a per-entry table offset that grows along the row, turned by an extra axis; one texture
   corner mode for the whole row (module helper, shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b056_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b056_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b056_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b056_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 axis;
} Spr_b056_01E00920;

static void func_01E00920_b552(Obj_b056_01E00920 *o, Spr_b056_01E00920 *s, s8 *tbl, Vec4f pos) {
    extern Rgbaq_b056_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f e;
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b056_01E00920 pkt __attribute__((aligned(8)));
    s8 *j;
    s32 h;
    s16 i;
    s16 n;
    Pkt_b056_01E00920 *p;

    func_00207500();
    p = (Pkt_b056_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    pkt.c.q = 0;
    pkt.v[0].f = 0;
    pkt.v[1].f = 0;
    pkt.v[2].f = 0;
    pkt.v[3].f = 0;
    pkt.c = func_00107740(s->col);
    func_01E00080_b552((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    if (o->count != 0) {
        n = o->count;
    } else {
        n = 20;
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, NULL, &p2);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    ax[2] = s->axis;
    for (i = 0; i < n; i++) {
        func_00108CE0(quad, s->size, s->size);
        func_00109100(quad, rot, 0, o->xD8);
        func_00109100(quad, rot, 1, o->xD8);
        j = tbl + i;
        h = i >> 1;
        e.x = j[s->off] / 20.0f * (s->w30 + h);
        e.y = j[s->off + 100] / 20.0f * (s->w30 + h);
        e.z = j[s->off + 180] / 20.0f * (s->w30 + h);
        func_00108950(&e, ax, 2, o->xD8);
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E00CE0_b552(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b552((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b552:01E01240, 278 insns: the module's spawn step: scene colour red, ticks the timer; from tick 69 to 199
   (except every tenth) it spawns two b552:01E016A0 glows jittered 5 around joint A, one b552:01E01A10 glow 3 above or
   below it, and b552:01E020B0 glows jittered 15 around joint B; from tick 91, on every tenth tick it picks new joints
   (A from 0x11, B from 1), otherwise a b552:01E01D60 speck at joint B */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x3274 - 0x25C];
    u8 rgba[4];
    u8 pad3278[0x329C - 0x3278];
    s16 jointA;
    u8 pad329E[0x32AA - 0x329E];
    s16 jointB;
    u8 pad32AC[0x32B2 - 0x32AC];
    s16 up;
    u8 pad32B4[2];
    s16 t;
} Scene_b552_01E01240;

static s32 func_01E016A0_b552();
static s32 func_01E01A10_b552();
static s32 func_01E01D60_b552();
static s32 func_01E020B0_b552();
static s32 func_01E02CD0_b552();

static void func_01E01240_b552(Scene_b552_01E01240 *s) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F54E0(s32);
    f32 p[4];
    s32 i;

    s->rgba[0] = 0x80;
    s->rgba[1] = 0;
    s->rgba[2] = 0;
    s->rgba[3] = 0;
    s->t++;
    if (s->t > 0x44 && s->t <= 0xC7 && s->t % 10 != 1) {
        func_001F5620(func_001F53A0(), s->jointA, p);
        for (i = 0; i < 2; i++) {
            s->px = p[0] + func_0019A5C8() % 10 - 5.0f;
            s->py = p[1] + func_0019A5C8() % 10 - 5.0f;
            s->pz = p[2];
            func_01E02CD0_b552(s, func_01E016A0_b552, 0);
        }
    }
    if (s->t > 0x44 && s->t <= 0xC7 && s->t % 10 != 1) {
        func_001F5620(func_001F53A0(), s->jointA, p);
        s->px = p[0];
        s->py = p[1] + func_0019A5C8() % 10 - 5.0f;
        if (s->up != 0) {
            s->pz = p[2] + 3.0f + func_0019A5C8() % 10 - 5.0f;
        } else {
            s->pz = p[2] - 3.0f + func_0019A5C8() % 10 - 5.0f;
        }
        func_01E02CD0_b552(s, func_01E01A10_b552, 0);
    }
    if (s->t > 0x5A && s->t <= 0xC7) {
        if (s->t % 10 == 1) {
            s->jointA = func_001F5560(func_001F53A0(), 0x11, 1);
            func_001F54E0(func_001F5380());
            func_0019A5C8();
            s->jointB = func_001F5560(func_001F5380(), 1, 1);
        } else {
            func_001F5620(func_001F5380(), s->jointB, p);
            s->px = p[0];
            s->py = p[1];
            s->pz = p[2];
            func_01E02CD0_b552(s, func_01E01D60_b552, 0);
        }
    }
    if (s->t > 0x44 && s->t <= 0xC7 && s->t % 10 != 1) {
        func_001F5620(func_001F5380(), s->jointB, p);
        s->px = p[0] + func_0019A5C8() % 30 - 15.0f;
        s->py = p[1] + func_0019A5C8() % 30 - 15.0f;
        s->pz = p[2] + func_0019A5C8() % 30 - 15.0f;
        func_01E02CD0_b552(s, func_01E020B0_b552, 0);
    }
}

/* shape b552:01E016A0, 220 insns: b503:01E01E00's glow with rise 7..16, the scene count threshold 210, and a
   sideways drift h4 of -6 or +6 a tick by the scene flag (ctx+0x32B2) */

typedef struct {
    u8 pad0[0x32B2];
    s16 flag;
    u8 pad32B4[2];
    s16 count;
} Game_b552_01E016A0;

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b552_01E016A0;

static s32 func_01E016A0_b552(Game_b552_01E016A0 *g, Glow_b552_01E016A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 15 + 3;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0xB0, 0xB0, 0xB0);
        } else {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        }
        o->h30 = func_0019A5C8() % 150 + 10;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 7;
        o->h8 = func_0019A5C8() % 30;
        o->hA = func_0019A5C8() % 2;
        o->h6 = func_0019A5C8() % 15 + 30;
        o->kind = 0;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 210) {
            if (o->col[3] < 0x80) {
                o->col[3] += 25;
            }
        }
    } else if (g->count < 210) {
        if (o->col[3] > 21) {
            o->col[3] -= 20;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 210) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->kind = func_0019A5C8() % 8;
    if (o->tick % 2 == 1) {
        o->h2 += (s16)(func_0019A5C8() % 3 + 1);
    } else {
        o->h2 -= (s16)(func_0019A5C8() % 4 + 1);
    }
    o->tick++;
    if (o->hA != 0) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    if (g->flag != 0) {
        o->h4 -= 6;
    } else {
        o->h4 += 6;
    }
    return 0;
}

/* shape b552:01E01A10, 209 insns: b503:01E01AB0 in blue (0x20/0x20/0x60), the scene count limit 210 instead of 280 */

typedef struct {
    u8 pad0[0x32AA];
    s16 joint;
    u8 pad32AC[6];
    s16 side;
    u8 pad32B4[2];
    s16 count;
} Game_b552_01E01A10;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b552_01E01A10;

static s32 func_01E01A10_b552(Game_b552_01E01A10 *g, Glow_b552_01E01A10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 20;
        o->kind = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x60);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 6 + 1;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 210) {
            if (o->col[3] < 0x81) {
                o->col[3] += 0x40;
            }
        }
    } else if (g->count < 210) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 210) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        if (o->f38 < 60) {
            o->f38 += 4;
        }
    }
    func_001F5620(func_001F5380(), g->joint, v);
    func_001F5F90(func_001F53A0(), &v[4]);
    if (o->tick != 0) {
        if (g->side != 0) {
            o->h4--;
        } else {
            o->h4++;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->h30 += o->hE;
    if (o->tick % 2 == 1) {
        o->f38 += 2;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    if (o->hE % 2 == 1) {
        o->ang++;
    } else {
        o->ang--;
    }
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b552:01E01D60, 209 insns: b552:01E020B0 family speck: size 3..17, grey 0x80, 0xB0 or white by a 0..2 pick, 0x30 10..159 growing by 0xE (14..27) once moving, random 0x3A turning 2 a tick (direction 0xA 0..1), 0x8 0..29, hold 30..44; alpha up by 0x19 during the hold, down by 20 after it, down by 9 past scene count 210; frame 0..7 each tick, and 0x2 wobbles up 1..3 / down 1..4 on odd / even ticks */

typedef struct {
    u8 pad0[0x32B6];
    s16 count;
} Game_b552_01E01D60;

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Speck_b552_01E01D60;

static s32 func_01E01D60_b552(Game_b552_01E01D60 *g, Speck_b552_01E01D60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 15 + 3;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else if (k == 1) {
            func_001076F0(o->col, 0xB0, 0xB0, 0xB0);
        } else {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        }
        o->h30 = func_0019A5C8() % 150 + 10;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 14 + 14;
        o->h8 = func_0019A5C8() % 30;
        o->hA = func_0019A5C8() % 2;
        o->h6 = func_0019A5C8() % 15 + 30;
        o->kind = 0;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 210) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x19;
            }
        }
    } else if (g->count < 210) {
        if (o->col[3] > 0x15) {
            o->col[3] -= 0x14;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 210) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->kind = func_0019A5C8() % 8;
    if (o->tick % 2 == 1) {
        k = func_0019A5C8() % 3 + 1;
        o->h2 += k;
    } else {
        k = func_0019A5C8() % 4 + 1;
        o->h2 -= k;
    }
    o->tick++;
    if (o->hA != 0) {
        o->ang += 2;
    } else {
        o->ang -= 2;
    }
    return 0;
}

/* shape b552:01E020B0, 185 insns: b116:01E02370's kind of glow, blue (0x20/0x20/0x60) of size 12..23: alpha up by 0x40 (to 0xC0) for
   40..64 ticks while the scene count 0x32B6 is under 210, then down by 7 (by 9 once the count passes 210); the size
   grows by 2 to 60 and by 2 more every other tick, the frame steps to 5, h30 sweeps by hE and the angle turns with
   hE's parity */

typedef struct {
    u8 pad0[0x32B6];
    s16 count;
} Game_b552_01E020B0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b552_01E020B0;

static s32 func_01E020B0_b552(Game_b552_01E020B0 *g, Glow_b552_01E020B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 12;
        o->kind = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x60);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 25 + 40;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 210) {
            if (o->col[3] < 0x81) {
                o->col[3] += 0x40;
            }
        }
    } else if (g->count < 210) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 210) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        if (o->f38 < 60) {
            o->f38 += 2;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->h30 += o->hE;
    if (o->tick % 2 == 1) {
        o->f38 += 2;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    if (o->hE % 2 == 1) {
        o->ang++;
    } else {
        o->ang--;
    }
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b552:01E023A0, 93 insns: a screen fog: on start sets the scene fog block (0x3220: 128, 4.0, 2.0, 0.0, position from
   the effect, colour (0, 120.0, 0)); its strength 0x3248 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 (0x3270) */

typedef struct {
    u8 pad0[0x3220];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad324C[0x3270 - 0x324C];
    s32 count;
} Game_b552_01E023A0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[0x4];
    s16 mode;
} Fx_b552_01E023A0;

static s32 func_01E023A0_b552(Game_b552_01E023A0 *g, Fx_b552_01E023A0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 4.0f;
        g->f2A08 = 2.0f;
        g->f2A0C = 0.0f;
        g->f2A20 = 0.0f;
        g->f2A24 = 120.0f;
        g->strength = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->strength < 1.0f) {
            g->strength += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2A00);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b552:01E02520, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3270 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3270];
    s32 state;
} Game_b552_01E02520;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b552_01E02520;

static s32 func_01E02520_b552(Game_b552_01E02520 *g, Fade_b552_01E02520 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

static s32 func_01E025E0_b552(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b552;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b552;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b552:01E02630 (b552), 424 insns, 1 copy: B552 scene manager (b503:01E02440 form): set up models, two texture
   sets and the shake table, then step 190 objects of seven kinds (the 201 handler written out) and draw the four glow
   kinds, and return the phase by timer */

typedef struct Fx_b552_01E02630 {
    s16 x, y, z;
    u8 pad6[0x1E];
    void *fn;
    u8 pad28[0xA];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b552_01E02630;

typedef struct Q_b552_01E02630 {
    f32 a, b, c, d;
} Q_b552_01E02630;

typedef struct Scene_b552_01E02630 {
    u8 pad0[0x20];
    f32 px, py, pz;
    u8 pad2C[0x80 - 0x2C];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    Q_b552_01E02630 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 camD8[0x260 - 0xD8];
    s32 tex[16];
    Fx_b552_01E02630 fx[190];
    u8 pad3220[0x3250 - 0x3220];
    s32 tex2[2];
    u8 pad3258[0x3270 - 0x3258];
    s32 state;
    u8 pad3274[8];
    s32 ot2;
    u8 pad3280[0x329C - 0x3280];
    s16 model0;
    u8 pad329E[0x32AA - 0x329E];
    s16 model5;
    u8 pad32AC[6];
    s16 flag;
    s16 id;
    s16 timer;
    s8 rnd[256];
    u8 cam[0x3530 - 0x33B8];
} Scene_b552_01E02630;

static s32 func_01E02630_b552(s32 arg0, s32 id) {
    Scene_b552_01E02630 *g = (Scene_b552_01E02630 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern s32 func_01E023A0_b552();
    extern s32 func_01E02520_b552();
    extern s32 func_01E025E0_b552();
    extern void func_01E01240_b552();
    extern s32 func_01E016A0_b552();
    extern s32 func_01E01A10_b552();
    extern s32 func_01E01D60_b552();
    extern s32 func_01E020B0_b552();
    extern void func_01E00920_b552();
    extern void func_01E00CE0_b552();
    s32 n;
    Vec4f v;
    Q_b552_01E02630 r0;
    Q_b552_01E02630 r1;
    Q_b552_01E02630 r2;
    Q_b552_01E02630 r3;
    s32 info[4];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3530);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->state = 0xFA;
        g->model0 = func_001F5560(func_001F53A0(), 0x11, 1);
        g->model5 = func_001F5560(func_001F5380(), 1, 1);
        for (i = 11; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), info);
        g->flag = (s32)(info[1] / 180.0f);
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01240_b552(g, 0);
    for (i = 0; i < 190; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E016A0_b552) {
                func_01E016A0_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01A10_b552) {
                func_01E01A10_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01D60_b552) {
                func_01E01D60_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E020B0_b552) {
                func_01E020B0_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E023A0_b552) {
                func_01E023A0_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02520_b552) {
                func_01E02520_b552(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E025E0_b552) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b552;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b552;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 190; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E016A0_b552) {
                g->texture = g->tex2[0];
                func_00106080(&r0, 0x14, g->fx[i].h34, 0);
                g->rect = r0;
                v.x = g->fx[i].x;
                v.y = g->fx[i].y;
                v.z = g->fx[i].z;
                g->count = 5;
                g->mode = 0;
                func_01E00920_b552(g, &g->fx[i], g->rnd, v);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E01A10_b552) {
                g->texture = g->tex2[1];
                func_00106080(&r1, 0x14, g->fx[i].h34, 0);
                g->rect = r1;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->fx[i].y;
                    g->pz = g->fx[i].z;
                    func_01E00CE0_b552(g, &g->fx[i], 0x20, g->rnd);
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E01D60_b552) {
                g->texture = g->tex2[0];
                func_00106080(&r2, 0x14, g->fx[i].h34, 0);
                g->rect = r2;
                v.x = g->fx[i].x;
                v.y = g->fx[i].y;
                v.z = g->fx[i].z;
                g->count = 5;
                g->mode = 0;
                func_01E00920_b552(g, &g->fx[i], g->rnd, v);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E020B0_b552) {
                g->texture = g->tex2[1];
                func_00106080(&r3, 0x14, g->fx[i].h34, 0);
                g->rect = r3;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->fx[i].y;
                    g->pz = g->fx[i].z;
                    func_01E00CE0_b552(g, &g->fx[i], 0x20, g->rnd);
                    g->count = 0;
                }
            }
        }
    }
    if (g->state != 0) {
        g->state--;
    }
    if (g->timer == 0x3A) {
        return 1;
    }
    if (g->timer == 230) {
        return 4;
    }
    if (g->timer == 220) {
        return 2;
    }
    if (g->timer > 0x44 && g->timer < 0xD7) {
        return 6;
    }
    if (g->state <= 0) {
        return 8;
    }
    return 0;
}

/* shape b503:01E02A20, 72 insns: twin of b046:01E03E20: take the first free slot of the 190-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x32B0 and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b503_01E02A20;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b503_01E02A20 s[190];
    u8 pad3220[0x54];
    u8 r, g, b, a;
    u8 pad3278[0x38];
    s16 v;
} Pool_b503_01E02A20;

static s32 func_01E02CD0_b552(Pool_b503_01E02A20 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b503_01E02A20 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 190; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 190;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
