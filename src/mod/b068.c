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

static void func_01E00080_b068(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b068:01E00920 (IWGas3), 355 insns, 2 copies: b069:01E004D0 (b008:01E004D0 with func_00205C40 called twice and
   separate x/y sizes): draws a row of small camera-facing sprites, each shaken by a per-entry table offset that grows
   along the row; depth mode 0 (projected), 1 (far) or 2 (front); texture corners via the module UV helper (shape
   b003:01E00080) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b068_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b068_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b068_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b068_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    s16 sy;
    s16 sx;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b068_01E00920;

static void func_01E00920_b068(Obj_b068_01E00920 *o, Spr_b068_01E00920 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b068_01E00920 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b068_01E00920 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b068_01E00920 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b068_01E00920 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00080_b068((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
        func_00108CE0(quad, s->sx, s->sy);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

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

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

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
} Spr_b008_01E004D0;

static void func_01E00EB0_b068(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00080_b068((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b068:01E01430, 268 insns: the b068 scene's step: colour 0x80/0/0/0, counts the tick (0x3616); tick 45 resets
   0x3610/0x360A; from tick 100 while over 67 are in use (0x35B0) spawns 0x1E01870 on joints 0x35F8 and 0x35FA; ticks
   up to 20 spawn 0x1E024E0 there, ticks 100..105 0x1E01E70 one higher; tick 1 puts the point on joints 0x35FA then
   0x35FE jittered by -3..2 (chatA, 16 Oct) */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x35B0 - 0x25C];
    s32 n;
    u8 col[4];
    u8 pad35B8[0x35F8 - 0x35B8];
    s16 j[4];
    u8 pad3600[0x360A - 0x3600];
    s16 f360A;
    u8 pad360C[4];
    s16 f3610;
    u8 pad3612[4];
    s16 tick;
} Scene_b068_01E01430;

static void func_01E01430_b068(Scene_b068_01E01430 *g) {
    extern void b068_01E01870();
    extern void b068_01E01E70();
    extern void b068_01E024E0();
    extern void b068_01E02EA0(Scene_b068_01E01430 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 45) {
        g->f3610 = 0;
        g->f360A = 0;
        g->f360A = 90;
        g->f3610 = 1;
        g->f360A = 0;
        g->f360A = 90;
    }
    if (g->tick >= 100 && g->n > 67) {
        func_001F5620(func_001F53A0(), g->j[0], v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E01870, 0);
        func_001F5620(func_001F53A0(), g->j[1], v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E01870, 0);
    }
    if (g->tick <= 20) {
        func_001F5620(func_001F53A0(), g->j[0], v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E024E0, 0);
        func_001F5620(func_001F53A0(), g->j[1], v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E024E0, 0);
    }
    if (g->tick >= 100 && g->tick <= 105) {
        func_001F5620(func_001F53A0(), g->j[0], v);
        g->x = v[0];
        g->y = v[1] + 1.0f;
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E01E70, 0);
        func_001F5620(func_001F53A0(), g->j[1], v);
        g->x = v[0];
        g->y = v[1] + 1.0f;
        g->z = v[2];
        g->f3610 = 0;
        b068_01E02EA0(g, b068_01E01E70, 0);
    }
    if (g->tick == 1) {
        func_001F5620(func_001F53A0(), g->j[1], v);
        g->x = v[0] + func_0019A5C8() % 6 - 3.0f;
        g->y = v[1] + func_0019A5C8() % 6 - 3.0f;
        g->z = v[2] + func_0019A5C8() % 6 - 3.0f;
        g->f3610 = 0;
        func_001F5620(func_001F53A0(), g->j[3], v);
        g->x = v[0] + func_0019A5C8() % 6 - 3.0f;
        g->y = v[1] + func_0019A5C8() % 6 - 3.0f;
        g->z = v[2] + func_0019A5C8() % 6 - 3.0f;
        g->f3610 = 0;
    }
}

/* shape b068:01E01870, 245 insns: b068:01E01E70 cousin: kind 1 up to 4, size 10 x 50, held 45..54 ticks, fading in
   by 12 from the second tick, drifting by 1/50 (1/40 after tick 10); at tick 45 one in five hands its position to the
   scene and spawns b068:01E01C50. As b068:01E01E70: b068:01E024E0's glow with f38 70, size 15 x 50 growing by 4, rise 7..11, fading in
   by 0x30; depth drift /90 for 10 ticks then /80, and it sinks 1 every fifth tick */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b068_01E01870;

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x3610 - 0x25C];
    s16 h3610;
} Ctx_b068_01E01870;

static s32 func_01E01870_b068(Ctx_b068_01E01870 *g, Glow_b068_01E01870 *o) {
    extern void b068_01E01C50(void);
    extern s32 b068_01E02EA0(Ctx_b068_01E01870 *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 70;
        o->kind = 1;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->col[3] = 0;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 7;
        o->hC = 50;
        o->hA = 10;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 45;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->tick != 0) {
            if (o->col[3] < 97) {
                o->col[3] += 12;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 10) {
        *(f32 *)(u32)&v[0].z /= 50.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 40.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick == 45) {
        if (func_0019A5C8() % 5 == 1) {
            g->px = o->h0;
            g->py = o->h2;
            g->pz = o->h4;
            g->h3610 = 0;
            b068_01E02EA0(g, (s32)b068_01E01C50, 0);
        }
    }
    if (o->tick % 5 == 1) {
        o->h2--;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 4) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->hC += 4;
        o->hA += 4;
        if (o->tick > 10) {
            if (o->h8 > o->hA) {
                o->hA += 4;
            }
        }
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b068:01E01C50, 133 insns: b350:01E011E0's glow, near-white (0xF0), size 120 growing 8 a tick, height
   200..599 rising 20..29, 0xA 10 / 0xC 50, held 15..24; alpha grows by 0xD (to 0x60) */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b068_01E01C50;

static s32 func_01E01C50_b068(s32 arg0, Glow_b068_01E01C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 120;
        o->kind = 0;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        o->h30 = func_0019A5C8() % 400 + 200;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 20;
        o->hC = 50;
        o->hA = 10;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 15;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0xD;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->f38 += 8;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b068:01E01E70, 205 insns: b068:01E024E0's glow with f38 70, size 15 x 50 growing by 4, rise 7..11, fading in
   by 0x30; depth drift /90 for 10 ticks then /80, and it sinks 1 every fifth tick */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b068_01E01E70;

static s32 func_01E01E70_b068(s32 arg0, Glow_b068_01E01E70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 70;
        o->kind = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 7;
        o->hC = 50;
        o->hA = 15;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 5;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 97) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 10) {
        *(f32 *)(u32)&v[0].z /= 90.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 80.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 5 == 1) {
        o->h2--;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->hC += 4;
        o->hA += 4;
        if (o->tick > 10) {
            if (o->h8 > o->hA) {
                o->hA += 4;
            }
        }
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b068:01E021B0, 204 insns: b068:01E024E0 cousin: white 0xF0 glow (kind 0, f38 30), size 15 x 50 growing by 4
   (hA by 4 more after tick 10 while under h8), fading in by 48 to 97 for 4..9 ticks, rising 1 every fifth tick; it drifts
   with the camera depth by 1/90 of the gap (1/80 after tick 10) */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b068_01E021B0;

static s32 func_01E021B0_b068(s32 arg0, Glow_b068_01E021B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 30;
        o->kind = 0;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 7;
        o->hC = 50;
        o->hA = 15;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 6 + 4;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 97) {
            o->col[3] += 48;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 10) {
        *(f32 *)(u32)&v[0].z /= 90.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 80.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 5 == 1) {
        o->h2--;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->hC += 4;
        o->hA += 4;
        if (o->tick > 10) {
            if (o->h8 > o->hA) {
                o->hA += 4;
            }
        }
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b068:01E024E0, 193 insns: b501:01E02A20's glow in grey 0x80 (kind 4, f38 35), size 8 x 23 growing by 2 (hA
   by 4 more after tick 10 while under h8), fading in by 24 to 97 for 5..14 ticks; it drifts with the camera depth
   (/120 for the first 10 ticks, /130 after), h30 grows by hE (6..12) and every other tick kind steps up to 5 */

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b068_01E024E0;

static s32 func_01E024E0_b068(s32 arg0, Glow_b068_01E024E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 35;
        o->kind = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 7 + 6;
        o->hC = 23;
        o->hA = 8;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 5;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 97) {
            o->col[3] += 24;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 10) {
        *(f32 *)(u32)&v[0].z /= 120.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 130.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->hC += 2;
        o->hA += 2;
        if (o->tick > 10) {
            if (o->h8 > o->hA) {
                o->hA += 4;
            }
        }
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b068", func_01E027F0_b068);

/* shape b068:01E02EA0, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3610 and 0x360A and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b068_01E02EA0;

typedef struct {
    u8 pad[0x250];
    u8 m[0x70];
    Slot_b068_01E02EA0 s[200];
    u8 pad34C0[0xF4];
    u8 r, g, b, a;
    u8 pad35B8[0x52];
    s16 w;
    u8 pad360C[0x4];
    s16 v;
} Pool_b068_01E02EA0;

static s32 func_01E02EA0_b068(Pool_b068_01E02EA0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b068_01E02EA0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
