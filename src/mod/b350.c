#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b350(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
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

static void func_01E00150_b350(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E005A0_b350(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
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
        func_01E00150_b350((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
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

/* shape b350:01E00B20, 78 insns: scene colour (0x80, 0, 0, 0); count 0x37A2 up; between 0x2D and 0xC7 place the scene
   at model point 0x3784 (y + 2) and run b350:01E00C60 and b350:01E00F20 through b350:01E01C70; below 0x14 place it at
   point 0x3786 and run b350:01E011E0 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x3754 - 0x25C];
    u8 col[4];
    u8 pad3758[0x2C];
    s16 point;
    s16 point2;
    u8 pad3788[0x1A];
    s16 count;
} Scene_b350_01E00B20;

static void func_01E00B20_b350(Scene_b350_01E00B20 *g) {
    extern void b350_01E00C60(void);
    extern void b350_01E00F20(void);
    extern void b350_01E011E0(void);
    extern void b350_01E01C70(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 pt[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count > 0x2C && g->count < 0xC8) {
        func_001F5620(func_001F53A0(), g->point, pt);
        g->pos[0] = pt[0];
        g->pos[1] = 2.0f + pt[1];
        g->pos[2] = pt[2];
        for (i = 0; i < 1; i++) {
            b350_01E01C70(g, b350_01E00C60, 0);
        }
        for (i = 0; i < 1; i++) {
            b350_01E01C70(g, b350_01E00F20, 0);
        }
    }
    if (g->count < 0x14) {
        func_001F5620(func_001F53A0(), g->point2, pt);
        g->pos[0] = pt[0];
        g->pos[1] = pt[1];
        g->pos[2] = pt[2];
        b350_01E01C70(g, b350_01E011E0, 0);
    }
}

/* shape b350:01E00C60, 175 insns: a grey 0x70 smoke puff (size 30 growing 2, frame to 5 every other tick, angle 0..359, speed 5..9, h8 0..24, hold 30..39) spanning the two tracked points (ctx+0x3784 / 0x3786) and closing a fortieth of the camera's depth gap each tick; alpha up by 0x30 to 0x90 during the hold, then down by 9; random turns each tick */

typedef struct {
    u8 pad0[0x3784];
    s16 id0;
    s16 id1;
} Ctx_b350_01E00C60;

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b350_01E00C60;

static s32 func_01E00C60_b350(Ctx_b350_01E00C60 *g, Fx_b350_01E00C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 30;
        o->f34 = 0;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 30;
        func_001F5620(func_001F53A0(), g->id0, v);
        func_001F5620(func_001F53A0(), g->id1, &v[4]);
        o->hC = v[4] - v[0];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    v[2] /= 40.0f;
    o->z = o->z + v[2];
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38 += 2;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b350:01E00F20, 175 insns: a dark 0x20 smoke puff (size 50 growing 1, frame to 5 every other tick, angle 0..359, speed 5..9, h8 0..24, hold 30..39) spanning the two tracked points (ctx+0x3784 / 0x3786) and closing a fortieth of the camera's depth gap each tick; alpha up by 0x20 to 0x60 during the hold, then down by 9; random turns each tick */

typedef struct {
    u8 pad0[0x3784];
    s16 id0;
    s16 id1;
} Ctx_b350_01E00F20;

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b350_01E00F20;

static s32 func_01E00F20_b350(Ctx_b350_01E00F20 *g, Fx_b350_01E00F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 50;
        o->f34 = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 30;
        func_001F5620(func_001F53A0(), g->id0, v);
        func_001F5620(func_001F53A0(), g->id1, &v[4]);
        o->hC = v[4] - v[0];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x3F) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    v[2] /= 40.0f;
    o->z = o->z + v[2];
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38 += 1;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b350:01E011E0, 126 insns: b383:01E03640 variant: size 30 growing by 1 a tick, height from 0, frame 0..24, fade-in 4..13 ticks up by 48 to 0x60 then down by 9 until it ends, kind steps to 5 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
} Glow_b350_01E011E0;

static s32 func_01E011E0_b350(s32 arg0, Glow_b350_01E011E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 30;
        o->kind = 0;
        func_001076F0(o->col, 0x70, 0x70, 0x70);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 4;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
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
        o->f38++;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b350:01E013E0, 92 insns: b582:01E03470 family scene light at ctx+0x3510 (white 5/5/5, range 128, height 140): raised by 0.2 to 1, lowered by 0.1 and ended; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b350_01E013E0;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x214];
    s32 state;
} Light_b350_01E013E0;

typedef struct {
    u8 pad[0x3510];
    Light_b350_01E013E0 l;
} Game_b350_01E013E0;

static s32 func_01E013E0_b350(Game_b350_01E013E0 *g, Obj_b350_01E013E0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 128.0f;
        g->l.r = 5.0f;
        g->l.g = 5.0f;
        g->l.b = 5.0f;
        g->l.w20 = 0;
        g->l.h = 140.0f;
        g->l.level = 0.0f;
        g->l.x = o->x;
        g->l.y = o->y;
        g->l.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->l.level > 0.1f) {
        g->l.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b284:01E02230, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3750 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3750];
    s32 state;
} Game_b284_01E02230;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b284_01E02230;

static s32 func_01E01550_b350(Game_b284_01E02230 *g, Fade_b284_01E02230 *o) {
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

static s32 func_01E01610_b350(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E01E00_b350;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E01E08_b350;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b350:01E01660 (b350), 385 insns, 1 copy: b350's scene manager (b069:01E01210 family): with a scene id (>= 0)
   it clears the scene, resets both camera blocks, keeps the id, sets the 260-frame countdown, takes five model
   handles, loads textures 10..15, 2 and page-5 textures 0..1, fills both 256-entry jitter tables with -15..14 (the
   second one zeroed at 100..179) and eight random 0..3 values; otherwise it runs the module script, at frame 1 sets
   the nine trail points to the first model, steps the trail and every live node (the 01E01610 node inlined: a
   func_001F7170 call), then draws the three sprite kinds with page-5 textures, rect 0x14 and a random frame, counts
   down and returns 1 / 3 / 6 at frames 70 / 250 / 81..244, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Node_b350_01E01660;

typedef struct {
    u8 pad0[0x80];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0[8];
    u8 padD0[8];
    u8 camD8[0x1D8];
    s32 tex[16];
    Node_b350_01E01660 node[200];
    s32 tex5[2];
    u8 pad34F8[0x3560 - 0x34F8];
    Vec4f pt[9];
    u8 trail[0x3750 - 0x35F0];
    s32 count;
    u8 pad3754[8];
    s32 ot;
    u8 pad3760[0x24];
    s16 model[5];
    u8 pad378E[0x12];
    s16 id;
    s16 timer;
    u8 pad37A4[2];
    s8 rnd[256];
    s8 rnd2[256];
    u8 pad39A6[2];
    u8 cam[0x178];
} Scene_b350_01E01660;

static s32 func_01E01660_b350(s32 arg0, s32 id) {
    Scene_b350_01E01660 *g = (Scene_b350_01E01660 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00B20_b350();
    extern void func_01E00080_b350();
    extern void func_01E005A0_b350();
    extern s32 func_01E00C60_b350();
    extern s32 func_01E00F20_b350();
    extern s32 func_01E011E0_b350();
    extern s32 func_01E013E0_b350();
    extern s32 func_01E01550_b350();
    extern s32 func_01E01610_b350();
    s32 n;
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Vec4f t;
    f32 b;
    f32 a;
    s32 i;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3B20);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 260;
        g->model[0] = func_001F5560(func_001F53A0(), 0x13, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0xB, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x40, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x47, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x4E, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 256; i++) {
            g->rnd2[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->rnd2[i] = 0;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E00B20_b350(g, 0);
    if (g->timer == 1) {
        Vec4f *p = g->pt;
        func_001F5620(func_001F53A0(), g->model[0], (s32)&t);
        for (i = 0; i < 9; i++, p++) {
            p->x = t.x;
            p->y = t.y;
            p->z = t.z;
        }
    }
    func_01E00080_b350(g->trail, 10, g->model[0]);
    for (i = 0; i < 200; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E00C60_b350) {
                func_01E00C60_b350(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00F20_b350) {
                func_01E00F20_b350(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E011E0_b350) {
                func_01E011E0_b350(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E013E0_b350) {
                func_01E013E0_b350(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01550_b350) {
                func_01E01550_b350(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01610_b350) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E01E00_b350;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E01E08_b350;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 200; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E00C60_b350) {
                g->tex88 = g->tex5[0];
                func_00106080(&r1, 0x14, g->node[i].h34, 0);
                g->rect = r1;
                g->hB8 = 7;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b350(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E00F20_b350) {
                g->tex88 = g->tex5[1];
                func_00106080(&r2, 0x14, g->node[i].h34, 0);
                g->rect = r2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b350(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E011E0_b350) {
                g->tex88 = g->tex5[0];
                func_00106080(&r3, 0x14, g->node[i].h34, 0);
                g->rect = r3;
                g->hB8 = 6;
                g->hBE = func_0019A5C8() % 4;
                func_01E005A0_b350(g, &g->node[i], 2, g->rnd2);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 70) {
        return 1;
    }
    if (g->timer == 250) {
        return 3;
    }
    if (g->timer > 80 && g->timer < 245) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b350:01E01C70, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x379E and the two arguments; returns 1 if a
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
} Slot_b350_01E01C70;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b350_01E01C70 s[200];
    u8 pad34F0[0x264];
    u8 r, g, b, a;
    u8 pad3758[0x46];
    s16 v;
} Pool_b350_01E01C70;

static s32 func_01E01C70_b350(Pool_b350_01E01C70 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b350_01E01C70 *s = NULL;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
