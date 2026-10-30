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

static void func_01E00080_b503(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b503(Obj_b056_01E00920 *o, Spr_b056_01E00920 *s, s8 *tbl, Vec4f pos) {
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
    func_01E00080_b503((Pk_b003_01E00080 *)p, &o->rect, o->mode);
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

static void func_01E00CE0_b503(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
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
        func_01E00080_b503((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
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

/* shape b503:01E01240, 319 insns: B503_W_S, the effect scene's step (b522:01E01D30 form): colour 0x80,0,0,0, counts
   the frame (0x32B6); in frames 51..89, 111..129 and 153..264 (153..274 for the second) except every 10th+1, two
   0x1E01740 jittered 5 around joint 0x329C, and one 0x1E01AB0 a step toward or away by the flag 0x32B2; frames
   131..274 look the joints up again every 10th+1 frame, else sit on joint 0x32AA and spawn 0x1E01E00 on odd frames;
   frames 149..274 spawn 0x1E02150 jittered 15 around it on even frames */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3274 - 0x260];
    u8 col[4];
    u8 pad3278[0x329C - 0x3278];
    s16 j;
    u8 pad329E[0x32AA - 0x329E];
    s16 jk;
    u8 pad32AC[0x32B2 - 0x32AC];
    s16 flag;
    u8 pad32B4[2];
    s16 t;
} Scene_b503_01E01240;

static void func_01E01240_b503(Scene_b503_01E01240 *g) {
    extern void b503_01E01740(void);
    extern void b503_01E01AB0(void);
    extern void b503_01E01E00(void);
    extern void b503_01E02150(void);
    extern void b503_01E02A20(Scene_b503_01E01240 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (((g->t > 50 && g->t < 90) || (g->t > 110 && g->t < 130) || (g->t > 152 && g->t < 265)) && g->t % 10 != 1) {
        func_001F5620(func_001F53A0(), g->j, &v);
        for (i = 0; i < 2; i++) {
            g->pos.x = v.x + func_0019A5C8() % 10 - 5.0f;
            g->pos.y = v.y + func_0019A5C8() % 10 - 5.0f;
            g->pos.z = v.z;
            b503_01E02A20(g, b503_01E01740, 0);
        }
    }
    if (((g->t > 50 && g->t < 90) || (g->t > 110 && g->t < 130) || (g->t > 152 && g->t < 275)) && g->t % 10 != 1) {
        func_001F5620(func_001F53A0(), g->j, &v);
        g->pos.x = v.x;
        g->pos.y = v.y + func_0019A5C8() % 10 - 5.0f;
        if (g->flag != 0) {
            g->pos.z = 1.0f + v.z + func_0019A5C8() % 10 - 5.0f;
        } else {
            g->pos.z = v.z - 1.0f + func_0019A5C8() % 10 - 5.0f;
        }
        b503_01E02A20(g, b503_01E01AB0, 0);
    }
    if (g->t > 130 && g->t < 275) {
        if (g->t % 10 == 1) {
            g->j = func_001F5560(func_001F53A0(), 0x11, 1);
            func_001F54E0(func_001F5380());
            func_0019A5C8();
            g->jk = func_001F5560(func_001F5380(), 1, 1);
        } else {
            func_001F5620(func_001F5380(), g->jk, &v);
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            if (g->t % 2 == 1) {
                b503_01E02A20(g, b503_01E01E00, 0);
            }
        }
    }
    if (g->t > 148 && g->t < 275 && g->t % 10 != 1) {
        func_001F5620(func_001F5380(), g->jk, &v);
        g->pos.x = v.x + func_0019A5C8() % 30 - 15.0f;
        g->pos.y = v.y + func_0019A5C8() % 30 - 15.0f;
        g->pos.z = v.z + func_0019A5C8() % 30 - 15.0f;
        if (g->t % 2 == 0) {
            b503_01E02A20(g, b503_01E02150, 0);
        }
    }
}

/* shape b503:01E01740, 220 insns: b503:01E01E00's glow with rise 7..16, the scene count threshold 280, and a
   sideways drift h4 of -6 or +6 a tick by the scene flag (ctx+0x32B2) */

typedef struct {
    u8 pad0[0x32B2];
    s16 flag;
    u8 pad32B4[2];
    s16 count;
} Game_b503_01E01740;

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
} Glow_b503_01E01740;

static s32 func_01E01740_b503(Game_b503_01E01740 *g, Glow_b503_01E01740 *o) {
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
        if (g->count < 280) {
            if (o->col[3] < 0x80) {
                o->col[3] += 25;
            }
        }
    } else if (g->count < 280) {
        if (o->col[3] > 21) {
            o->col[3] -= 20;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 280) {
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

/* shape b503:01E01AB0, 209 insns: b503:01E02150 cousin, red (0x60/0x20/0x20) glow of size 20..31 held 1..6 ticks,
   growing by 4 to 60; it also tracks the scene's joint (0x32AA) and the camera, and once moving nudges its z by 1
   toward the scene side (0x32B2); otherwise as b503:01E02150 */

typedef struct {
    u8 pad0[0x32AA];
    s16 joint;
    u8 pad32AC[6];
    s16 side;
    u8 pad32B4[2];
    s16 count;
} Game_b503_01E01AB0;

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
} Glow_b503_01E01AB0;

static s32 func_01E01AB0_b503(Game_b503_01E01AB0 *g, Glow_b503_01E01AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 20;
        o->kind = 0;
        func_001076F0(o->col, 0x60, 0x20, 0x20);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 6 + 1;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 280) {
            if (o->col[3] < 0x81) {
                o->col[3] += 0x40;
            }
        }
    } else if (g->count < 280) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 280) {
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

/* shape b503:01E01E00, 209 insns: b503:01E02150 family spark: size 3..17, grey, light grey or white at random, h30
   10..159 sweeping by 14..27, h8 0..29, turning +-2 a tick (hA), hold 30..44; alpha up by 25 to 0x98 while the scene
   count 0x32B6 is under 280, then down by 20 (by 9 once the count passes 280); random frame 0..7, rising 1..3 on odd
   ticks and sinking 1..4 on even ones */

typedef struct {
    u8 pad0[0x32B6];
    s16 count;
} Game_b503_01E01E00;

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
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
} Glow_b503_01E01E00;

static s32 func_01E01E00_b503(Game_b503_01E01E00 *g, Glow_b503_01E01E00 *o) {
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
        if (g->count < 280) {
            if (o->col[3] < 0x80) {
                o->col[3] += 25;
            }
        }
    } else if (g->count < 280) {
        if (o->col[3] > 21) {
            o->col[3] -= 20;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 280) {
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
    return 0;
}

/* shape b503:01E02150, 185 insns: b116:01E02370's kind of glow, red (0x60/0x20/0x20) of size 12..23: alpha up by 0x40 (to 0xC0) for
   40..64 ticks while the scene count 0x32B6 is under 280, then down by 7 (by 9 once the count passes 280); the size
   grows by 2 to 60 and by 2 more every other tick, the frame steps to 5, h30 sweeps by hE and the angle turns with
   hE's parity */

typedef struct {
    u8 pad0[0x32B6];
    s16 count;
} Game_b503_01E02150;

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
} Glow_b503_01E02150;

static s32 func_01E02150_b503(Game_b503_01E02150 *g, Glow_b503_01E02150 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 12 + 12;
        o->kind = 0;
        func_001076F0(o->col, 0x60, 0x20, 0x20);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 25 + 40;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (g->count < 280) {
            if (o->col[3] < 0x81) {
                o->col[3] += 0x40;
            }
        }
    } else if (g->count < 280) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 280) {
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

/* shape b503:01E02440 (b503), 376 insns, 1 copy: B503 scene manager (b505:01E013F0 form): set up models, textures and
   the shake table, then step and draw 190 glows of four kinds and return the phase by timer */

typedef struct Fx_b503_01E02440 {
    s16 x, y, z;
    u8 pad6[0x1E];
    void *fn;
    u8 pad28[0xA];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b503_01E02440;

typedef struct Q_b503_01E02440 {
    f32 a, b, c, d;
} Q_b503_01E02440;

typedef struct Scene_b503_01E02440 {
    u8 pad0[0x20];
    f32 px, py, pz;
    u8 pad2C[0x80 - 0x2C];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    Q_b503_01E02440 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 camD8[0x2A0 - 0xD8];
    Fx_b503_01E02440 fx[190];
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
} Scene_b503_01E02440;

static s32 func_01E02440_b503(s32 arg0, s32 id) {
    Scene_b503_01E02440 *g = (Scene_b503_01E02440 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E01240_b503();
    extern s32 func_01E01740_b503();
    extern s32 func_01E01AB0_b503();
    extern s32 func_01E01E00_b503();
    extern s32 func_01E02150_b503();
    extern void func_01E00920_b503();
    extern void func_01E00CE0_b503();
    s32 n;
    Vec4f v;
    Q_b503_01E02440 r0;
    Q_b503_01E02440 r1;
    Q_b503_01E02440 r2;
    Q_b503_01E02440 r3;
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
        g->state = 0x134;
        g->model0 = func_001F5560(func_001F53A0(), 0xB, 1);
        g->model5 = func_001F5560(func_001F5380(), 1, 1);
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
    func_01E01240_b503(g, 0);
    for (i = 0; i < 190; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E01740_b503) {
                func_01E01740_b503(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01AB0_b503) {
                func_01E01AB0_b503(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01E00_b503) {
                func_01E01E00_b503(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02150_b503) {
                func_01E02150_b503(g, &g->fx[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 190; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01740_b503) {
                g->texture = g->tex2[0];
                func_00106080(&r0, 0x14, g->fx[i].h34, 0);
                g->rect = r0;
                v.x = g->fx[i].x;
                v.y = g->fx[i].y;
                v.z = g->fx[i].z;
                g->count = 5;
                g->mode = 0;
                func_01E00920_b503(g, &g->fx[i], g->rnd, v);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E01AB0_b503) {
                g->texture = g->tex2[1];
                func_00106080(&r1, 0x14, g->fx[i].h34, 0);
                g->rect = r1;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->fx[i].y;
                    g->pz = g->fx[i].z;
                    func_01E00CE0_b503(g, &g->fx[i], 0x20, g->rnd);
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E01E00_b503) {
                g->texture = g->tex2[0];
                func_00106080(&r2, 0x14, g->fx[i].h34, 0);
                g->rect = r2;
                v.x = g->fx[i].x;
                v.y = g->fx[i].y;
                v.z = g->fx[i].z;
                g->count = 5;
                g->mode = 0;
                func_01E00920_b503(g, &g->fx[i], g->rnd, v);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E02150_b503) {
                g->texture = g->tex2[1];
                func_00106080(&r3, 0x14, g->fx[i].h34, 0);
                g->rect = r3;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->fx[i].y;
                    g->pz = g->fx[i].z;
                    func_01E00CE0_b503(g, &g->fx[i], 0x20, g->rnd);
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
    if (g->timer == 300) {
        return 4;
    }
    if (g->timer == 290) {
        return 2;
    }
    if (g->timer > 0x44 && g->timer < 0x11D) {
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

static s32 func_01E02A20_b503(Pool_b503_01E02A20 *o, s32 a, s32 b) {
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
