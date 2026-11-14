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

static void func_01E00080_b215(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b215 in the
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

static void func_01E00920_b215(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b215((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E00BE0_b215(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
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

static void func_01E00D30_b215(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b215:01E01090 (B215_W_S), 281 insns, 1 copy: the b215 module's event step: counts ticks; every third tick
   below 235 spawns b215:01E02540; at 1 two b215:01E01500 (flags 0 and 1), b215:01E02390, b215:01E02B70 and
   b215:01E022A0; at 141 b215:01E01A70 and b215:01E02140; from 141 the two ripple radii grow (by 1.5 to 50, by 0.75 to
   80); below 142 two b215:01E01EA0 a tick around joint 0xA028 at height 30 (+-30, +-10 up); from 141 to 255 two
   b215:01E01FF0 a tick around the unit at height 30, spread by the ripple radius */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x9FC0 - 0x260];
    f32 rx;
    f32 rz;
    u8 pad9FC8[0xA028 - 0x9FC8];
    s16 joint;
    u8 padA02A[0xA038 - 0xA02A];
    s16 unit;
    u8 padA03A[0xE66E - 0xA03A];
    s16 flag;
    u8 padE670[6];
    s16 timer;
} Ctx_b215_01E01090;

static void func_01E01090_b215(Ctx_b215_01E01090 *g) {
    extern s32 b215_01E01500(void);
    extern s32 b215_01E01A70(void);
    extern s32 b215_01E01EA0(void);
    extern s32 b215_01E01FF0(void);
    extern s32 b215_01E02140(void);
    extern s32 b215_01E022A0(void);
    extern s32 b215_01E02390(void);
    extern s32 b215_01E02540(void);
    extern s32 b215_01E02B70(void);
    extern void b215_01E03930(Ctx_b215_01E01090 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 r;

    g->timer++;
    if (g->timer % 3 == 1 && g->timer < 235) {
        b215_01E03930(g, b215_01E02540, 0);
    }
    if (g->timer == 1) {
        g->flag = 0;
        b215_01E03930(g, b215_01E01500, 0);
        g->flag = 1;
        b215_01E03930(g, b215_01E01500, 0);
        b215_01E03930(g, b215_01E02390, 0);
        b215_01E03930(g, b215_01E02B70, 0);
    }
    if (g->timer == 141) {
        g->flag = 0;
        b215_01E03930(g, b215_01E01A70, 0);
        b215_01E03930(g, b215_01E02140, 0);
    }
    if (g->timer == 1) {
        b215_01E03930(g, b215_01E022A0, 0);
    }
    if (g->timer >= 141) {
        if (g->rz < 50.0f) {
            g->rz += 1.5f;
        }
        if (g->rx < 80.0f) {
            g->rx += 0.75f;
        }
    }
    if (g->timer < 142) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->joint, &g->pos);
            g->pos.y = 30.0f;
            g->pos.x += func_0019A5C8() % 60 - 30;
            g->pos.z += func_0019A5C8() % 60 - 30;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b215_01E03930(g, b215_01E01EA0, 0);
        }
    }
    if (g->timer >= 141 && g->timer < 256) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F5380(), g->unit, &g->pos);
            g->pos.y = 30.0f;
            r = g->rx;
            if (r < 2) {
                r = 2;
            }
            g->pos.x += func_0019A5C8() % r - (r >> 1);
            g->pos.z += func_0019A5C8() % r - (r >> 1);
            b215_01E03930(g, b215_01E01FF0, 0);
        }
    }
}

/* shape b215:01E01500 (B215_OBJ_MOVE_2_), 346 insns, 1 copy: a ripple wave (side by its kind, turned 0x2000 one way
   or the other) over one row of b215:01E01A70's grid: brightens by 12 until tick 144, then fades by 9, blinks grey;
   the cells behind its front settle (counter down, the two phases and the third by 10 shrink to 0), the cells ahead
   advance by its two phase steps and 10 (wrapping at 360); the front moves one cell a tick after tick 30 (it spins
   once it reaches the end after tick 80); it stops at scene tick 141 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1A];
    s32 f24;
    s32 f28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    s16 front;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Fx_b215_01E01500;

typedef struct {
    u8 pad0[0xB460];
    s16 a[20][40];
    u8 padBAA0[0xC0E0 - 0xBAA0];
    s16 b[20][40];
    u8 padC720[0xCD60 - 0xC720];
    s16 c[20][40];
    u8 padD3A0[0xD9E0 - 0xD3A0];
    s16 d[20][40];
    u8 padE020[0xE676 - 0xE020];
    s16 timer;
} Game_b215_01E01500;

static s32 func_01E01500_b215(Game_b215_01E01500 *g, Fx_b215_01E01500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->f34 = 1.2f;
        o->f5C = func_0019A5C8() % 8 + 4;
        o->f5A = func_0019A5C8() % 8 + 4;
        o->front = 0;
        if (o->kind == 0) {
            o->f28 = 0x2000;
        }
        if (o->kind == 1) {
            o->f28 = -0x2000;
        }
    }
    if (o->tick < 145) {
        if (o->col0[3] < 0x80) {
            o->col0[3] += 12;
        }
        if (o->col1[3] < 0x80) {
            o->col1[3] += 12;
        }
    } else {
        if (o->col0[3] > 10) {
            o->col0[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col1[3] > 10) {
            o->col1[3] -= 9;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col1, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col1, 0xFF, 0xFF, 0xFF);
    }
    for (i = 0; i < o->front; i++) {
        if (g->d[o->kind][i] > 0) {
            g->d[o->kind][i]--;
        }
        if (g->a[o->kind][i] > o->f5A) {
            g->a[o->kind][i] -= o->f5A;
        } else {
            g->a[o->kind][i] = 0;
        }
        if (g->b[o->kind][i] > o->f5C) {
            g->b[o->kind][i] -= o->f5C;
        } else {
            g->b[o->kind][i] = 0;
        }
        if (g->c[o->kind][i] > 10) {
            g->c[o->kind][i] -= 10;
        } else {
            g->c[o->kind][i] = 0;
        }
    }
    for (i = o->front; i < 36; i++) {
        g->a[o->kind][i] += o->f5A;
        g->b[o->kind][i] += o->f5C;
        g->c[o->kind][i] += 10;
        if (g->a[o->kind][i] >= 360) {
            g->a[o->kind][i] %= 360;
        }
        if (g->b[o->kind][i] >= 360) {
            g->b[o->kind][i] %= 360;
        }
        if (g->c[o->kind][i] >= 360) {
            g->c[o->kind][i] %= 360;
        }
    }
    if (o->tick > 80 && o->front == 36) {
        o->f24 += 0x200;
    }
    if (o->tick > 30) {
        if (o->front < 36) {
            o->front++;
        }
    }
    if (g->timer == 141) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b215", func_01E01A70_b215);

/* shape b215:01E01EA0, 83 insns: a white two-colour puff (4 x 4, random frame 0..7, scale 2.5) rising by its scale each tick: in by 96 up to 0xC0 for 10 ticks, then out by 7 (twice on the first colour) and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[8];
    f32 f14;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b215_01E01EA0;

static s32 func_01E01EA0_b215(s32 arg0, Obj_b215_01E01EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 4;
        o->hA = 4;
        o->f48 = 0.0f;
        o->kind = func_0019A5C8() % 8;
        o->f34 = 2.5f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
        o->h5C = 0;
    }
    if (o->t < 10) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        }
    }
    if (o->t != 0) {
        o->f14 += o->f34;
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b215:01E01FF0, 83 insns: a white rising spark (b252:01E03410 family): size 10, f48 0, random sub-frame 0..7, f34 2.5 as its
   rise; both alphas up by 0x60 to 0xC0 for 10 frames, then the first down by 7 twice a frame until it ends; random turn */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b215_01E01FF0;

static s32 func_01E01FF0_b215(void *arg0, Obj_b215_01E01FF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0xA;
        o->h = 0xA;
        o->f48 = 0.0f;
        o->sub = func_0019A5C8() % 8;
        o->f34 = 2.5f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->c1[3] = 0;
        o->h5C = 0;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        }
    }
    if (o->t != 0) {
        o->y += o->f34;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b215:01E02140, 88 insns: a white ring (height 6 x the scene scale at ctx+0x9FC0), its first colour blinking blue: in by 64 up to 0x80 for 4 ticks; out by 11 once the scene value reaches 246, and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b215_01E02140;

typedef struct {
    u8 pad[0x9FC0];
    f32 scale;
    u8 pad9FC4[0xE676 - 0x9FC4];
    s16 val;
} Game_b215_01E02140;

static s32 func_01E02140_b215(Game_b215_01E02140 *g, Obj_b215_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (g->val > 245) {
        if (o->col2[3] > 12) {
            o->col2[3] -= 11;
        } else {
            o->mode = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0xC0);
    }
    o->f4C = 6.0f * g->scale;
    o->t++;
    return 0;
}

/* shape b215:01E022A0, 60 insns: volume fade by its own timer (b003:01E02330 family, layout at 0x50): for 0xFA frames
   down 10 to 0x40, then up 10 capped at 0x80; state 3 at 0x9FF0 sets the volume to 0x80 and ends the fade */

typedef struct {
    u8 pad[0x9FF0];
    s32 state;
} Game_b215_01E022A0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b215_01E022A0;

static s32 func_01E022A0_b215(Game_b215_01E022A0 *g, Fade_b215_01E022A0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0xFA) {
        if (o->vol > 0x40) {
            o->vol -= 10;
        } else {
            o->vol = 0x40;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b215:01E02390, 106 insns: a blue-grey full-screen veil (b081:01E044C0 shape): one sprite over the whole screen
   at the object alpha, sent at once; alpha up by 10 to 0x50 until frame 244, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b215_01E02390;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b215_01E02390 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b215_01E02390;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b215_01E02390;

static s32 func_01E02390_b215(void *arg0, Obj_b215_01E02390 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b215_01E02390 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->state = 2;
    }
    ((Pkt_b215_01E02390 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b215_01E02390 *)(s32)&pkt)->tag = 5;
    ((Pkt_b215_01E02390 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b215_01E02390 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x78;
    pkt.g = 0x78;
    pkt.b = 0xA0;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b215_01E02390 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
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
    if (o->t < 0xF4) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0xA;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b215:01E02540, 69 insns: a grey glow at the model joint: set up once (alphas 0 / 0xFF, placed at the joint with
   height 33, f34 from the game, random angle); takes the game's scale each frame and fades by 9 after 6 frames */

typedef struct {
    u8 pad0[0x9FC0];
    f32 scale;
    f32 f34;
    u8 pad9FC8[0x70];
    s16 joint;
} Game_b215_01E02540;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0x10];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b215_01E02540;

static s32 func_01E02540_b215(Game_b215_01E02540 *g, Obj_b215_01E02540 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->c0[3] = 0;
        o->c1[3] = 0xFF;
        func_001076F0(o->c0, 0x38, 0x38, 0x38);
        func_001076F0(o->c1, 0xCF, 0xCF, 0xCF);
        o->state = 2;
        func_001F5620(func_001F5380(), g->joint, &o->pos);
        o->pos.y = 33.0f;
        o->f34 = g->f34;
        o->ang = func_0019A5C8() % 360;
    }
    o->scale = g->scale;
    if (o->t >= 6) {
        if (o->c1[3] > 0xA) {
            o->c1[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b215", func_01E02660_b215);

/* shape b215:01E02B70, 184 insns: b252:01E03CA0's overlay in white at ctx+0xA008; alpha up by 8 to 0x80 for 200
   ticks (marking 0x50 once full), then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b215_01E02B70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b215_01E02B70 p;
    } v[2];
} Pkt_b215_01E02B70;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x44];
    s16 full;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b215_01E02B70;

typedef struct {
    u8 pad0[0xA008];
    Pkt_b215_01E02B70 *pkt;
} Scene_b215_01E02B70;

static s32 func_01E02B70_b215(Scene_b215_01E02B70 *s, Slot_b215_01E02B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 h;
    f32 w;

    w = o->w;
    h = o->h;
    w /= 10.0f;
    h /= 10.0f;
    if (o->state == 1) {
        o->c0[3] = 0;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
    }
    s->pkt->r = o->c0[0];
    s->pkt->g = o->c0[1];
    s->pkt->b = o->c0[2];
    s->pkt->a = o->c0[3];
    s->pkt->q = 1.0f;
    s->pkt->v[0].p.x = 0x6BF8;
    s->pkt->v[0].p.y = 0x71F8;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[0].p.f = 0;
    s->pkt->v[1].p.x = 0x93F8;
    s->pkt->v[1].p.y = 0x8DF8;
    s->pkt->v[1].p.z = 0xFFFFFF;
    s->pkt->v[1].p.f = 0;
    s->pkt->v[0].s = w / 1024.0f;
    s->pkt->v[0].t = h / 512.0f;
    s->pkt->v[1].s = (640.0f - w) / 1024.0f;
    s->pkt->v[1].t = (448.0f - 3.0f * h) / 512.0f;
    func_002075F0(s->pkt, 0, 0);
    if (o->t < 200) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        } else {
            o->full = 1;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b215:01E02E50 (b215), 696 insns, 1 copy: b215 scene manager (130 slots; the step and draw loops share the
   setup's outer counter a, zeroed first at the top, the slot count is the inner counter k): setup (six joints and a
   camera, one type-4 and two type-5 textures, s8 jitter tables, two 36-entry random s16 0..7 tables, a 40x40 grid of
   rand()%80/10, 2x40 random vectors /10, 2x36 random angles and 10s); step 01E01090 and every slot (counting the
   01E02540/01E02B70 ones, then 01E04520 if any), draw five kinds of slot; scene code from the timer. Needs
   func_01E00BE0_b215 to take a third unused s32 (the asm passes a3 = 0, as in its b152 twin) */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b215_01E02E50;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        Rect_b152_01E014F0 rc;
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b215_01E02E50 fx[130];
    u8 pad3B80[0x40];
    Vec4f vv[2][40];
    u8 pad40C0[0x9FD0 - 0x40C0];
    s32 tex[2];
    u8 pad9FD8[0x18];
    s32 count;
    u8 pad9FF4[8];
    s32 ot;
    u8 padA000[0x28];
    s16 j[6];
    u8 padA034[4];
    s16 cam;
    u8 padA03A[0xE];
    s16 grid[50][50];
    s16 h1[36];
    s16 h2[36];
    s16 ra[40][40];
    s16 rb[40][40];
    s16 rc[40][40];
    s16 rd[40][40];
    u8 padE660[0x12];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x178];
} Scene_b215_01E02E50;

static s32 func_01E02E50_b215(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern s32 func_01E01A70_b215();
    extern void b215_01E01090();
    extern void b215_01E00D30();
    extern void b215_01E03AC0();
    extern void b215_01E04010();
    extern void b215_01E04520();
    Scene_b215_01E02E50 *g = (Scene_b215_01E02E50 *)arg0;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    Rect_b152_01E014F0 rc;
    Rect_b152_01E014F0 rc2;
    s32 ang[4];
    s32 i;
    s16 k;
    s16 a;

    a = 0;
    m = 0;
    k = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE9F0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 270;
        g->j[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x35, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
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
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 36; k++) {
            g->h1[k] = func_0019A5C8() % 8;
        }
        for (k = 0; k < 36; k++) {
            g->h2[k] = func_0019A5C8() % 8;
        }
        for (a = 0; a < 40; a++) {
            for (k = 0; k < 40; k++) {
                g->grid[a][k] = func_0019A5C8() % 80;
                g->grid[a][k] = g->grid[a][k] / 10;
            }
        }
        for (k = 0; k < 2; k++) {
            for (a = 0; a < 40; a++) {
                g->vv[k][a].x = func_0019A5C8() % 30 - 15;
                g->vv[k][a].y = func_0019A5C8() % 30 - 15;
                g->vv[k][a].z = func_0019A5C8() % 30 - 15;
                g->vv[k][a].x /= 10.0f;
                g->vv[k][a].y /= 10.0f;
                g->vv[k][a].z /= 10.0f;
            }
        }
        for (k = 0; k < 2; k++) {
            for (a = 0; a < 36; a++) {
                g->ra[k][a] = func_0019A5C8() % 360;
                g->rb[k][a] = func_0019A5C8() % 360;
                g->rc[k][a] = func_0019A5C8() % 360;
                g->rd[k][a] = 10;
            }
        }
        return 0;
    }
    b215_01E01090(g, 0);
    for (a = 0; a < 130; a++) {
        if (g->fx[a].used != 0) {
            if (g->fx[a].fn != NULL) {
                if (g->fx[a].fn != (s32 (*)())func_01E02540_b215 && g->fx[a].fn != (s32 (*)())func_01E02B70_b215) {
                    g->fx[a].fn(g, &g->fx[a]);
                } else {
                    m++;
                }
            }
        }
    }
    for (a = 0; a < 130; a++) {
        if (g->fx[a].used != 0) {
            k++;
            if (g->fx[a].fn == (s32 (*)())func_01E01500_b215) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[a].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                func_001F5620(func_001F53A0(), g->j[0], &v);
                v.y -= 2.5f;
                b215_01E03AC0(g, &g->fx[a], 0x20, &v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01A70_b215) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[a].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 1;
                g->hBE = 0;
                func_001F5620(func_001F5380(), g->cam, &v);
                v.y = 33.0f;
                b215_01E04010(g, &g->fx[a], 0x20, &v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01EA0_b215) {
                g->tex88 = g->tex[1];
                rc = func_01E00BE0_b215(0, g->fx[a].h56, 0);
                g->u94.rc = rc;
                g->hBE = 0;
                v.x = g->fx[a].pos.x;
                v.y = g->fx[a].pos.y;
                v.z = g->fx[a].pos.z;
                func_01E00920_b215((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[a], 0x20, v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01FF0_b215) {
                g->tex88 = g->tex[1];
                rc2 = func_01E00BE0_b215(0, g->fx[a].h56, 0);
                g->u94.rc = rc2;
                g->hBE = 0;
                v.x = g->fx[a].pos.x;
                v.y = g->fx[a].pos.y;
                v.z = g->fx[a].pos.z;
                func_01E00920_b215((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[a], 0x20, v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E02140_b215) {
                g->hB8 = 0x24;
                func_001F5620(func_001F5380(), g->cam, &v);
                v.y = 33.0f;
                b215_01E00D30(g, &g->fx[a], 0x20, &v);
                g->hB8 = 0;
            }
        }
    }
    if (m) {
        b215_01E04520(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x8A) {
        return 1;
    }
    if (g->frame == 0x104) {
        return 4;
    }
    if (g->frame == 0xFF) {
        return 2;
    }
    if (g->frame > 0x94 && g->frame < 0xFA) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b215:01E03930, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x82 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b215_01E03930 {
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
} Slot_b215_01E03930;

typedef struct Obj_b215_01E03930 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b215_01E03930 slots[0x82];
    u8 padB[0x9ff4 - 0x2a0 - 0x82 * 0x70];
    u8 rgba[4];
    u8 padC[0xe66e - 0x9ff4 - 4];
    s16 fB2B0;
} Obj_b215_01E03930;

static s32 func_01E03930_b215(Obj_b215_01E03930 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b215_01E03930 *s = NULL;
    s16 i;

    for (i = 0; i < 0x82; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x82;
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

/* shape b215:01E03AC0 (B215PAINT_RAIN20), 337 insns, 1 copy: draws a ring of 36 quads (angle step 10, radius f48,
   height +-f34) for the grid row of the object kind: per quad its frame from the scene table into the rect, turned
   about its middle edge by the three phase tables, then moved by the row's grid point times the fourth table */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[0xE];
    u8 col0[4];
    u8 col1[4];
} Obj_b215_01E03AC0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x3BC0 - 0xC0];
    Vec4f grid[20][40];
    u8 pad6DC0[0x9FFC - 0x6DC0];
    s32 ot;
    u8 padA000[0xB3D0 - 0xA000];
    s16 frames[72];
    s16 a[20][40];
    u8 padBAA0[0xC0E0 - 0xBAA0];
    s16 b[20][40];
    u8 padC720[0xCD60 - 0xC720];
    s16 c[20][40];
    u8 padD3A0[0xD9E0 - 0xD3A0];
    s16 d[20][40];
    u8 padE020[0xE878 - 0xE020];
    u8 trig[1];
} Game_b215_01E03AC0;

typedef struct {
    u8 hdr[0x10];
    u8 v[0x60];
    u8 tail[0x20];
} Pk_b215_01E03AC0;

static void func_01E03AC0_b215(Game_b215_01E03AC0 *g, Obj_b215_01E03AC0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f pos;
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    Vec4f rm;
    Pk_b215_01E03AC0 pk __attribute__((aligned(8)));
    s16 i;
    s32 k;
    s16 n;
    s16 s;
    s16 a;
    Pk_b215_01E03AC0 *p;
    f32 h;
    f32 r;
    f32 c0;
    f32 s0;
    f32 c1;
    f32 s1;
    f32 dx;
    f32 dz;

    pos = *in;
    a = 0;
    p = &pk;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col0, 1);
    func_00107790(p, o->col1, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos.x;
    v[1] = pos.y;
    v[2] = pos.z;
    func_00108EF0(m, 0, o->rot, v);
    r = o->f48;
    for (i = 0; i < 36; i++) {
        func_00106080(&rm, 0x14, g->frames[i], 0);
        g->rect = rm;
        func_00108500(p, &g->rect, g->frame);
        q[0].y = o->f34;
        q[1].y = o->f34;
        q[2].y = -o->f34;
        q[3].y = -o->f34;
        h = g->d[o->kind][i];
        tw[0] = g->a[o->kind][i];
        tw[1] = g->b[o->kind][i];
        tw[2] = g->c[o->kind][i];
        c0 = func_00108030(g->trig, a, 1);
        s0 = func_00108030(g->trig, a, 0);
        c1 = func_00108030(g->trig, a + 5, 1);
        s1 = func_00108030(g->trig, a + 5, 0);
        q[2].x = c0 * r;
        q[2].z = s0 * r;
        q[0].x = c0 * r;
        q[0].z = s0 * r;
        s = a + 10;
        c0 = func_00108030(g->trig, s, 1);
        s0 = func_00108030(g->trig, s, 0);
        q[3].x = c0 * r;
        q[3].z = s0 * r;
        q[1].x = c0 * r;
        q[1].z = s0 * r;
        dx = c1 * r;
        dz = s1 * r;
        for (n = 0; n < 4; n++) {
            q[n].x -= dx;
            q[n].z -= dz;
        }
        func_00109100(q, tw, 1, g->trig);
        func_00109100(q, tw, 0, g->trig);
        for (n = 0; n < 4; n++) {
            q[n].x += dx + g->grid[o->kind][i].x * h;
            q[n].z += dz + g->grid[o->kind][i].z * h;
            q[n].y += dz + g->grid[o->kind][i].y * h;
        }
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, func_001A23B0(depth[0]));
        }
        a += 10;
    }
}


/* shape b215:01E04010 (B215PAINT_RAIN21), 323 insns, 1 copy: draws b215:01E01A70's 20 by 28 ripple grid: per cell its
   frame from the scene table into the rect, a quad scaled by f48, turned by the two phase tables, moved to the grid
   point; the first and last rows fade to alpha 0 on one side */

typedef struct Rgbaq_b215_01E04010 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b215_01E04010;

typedef struct {
    u8 r, g, b, a;
} C4_b215_01E04010;

typedef struct {
    Rgbaq_b215_01E04010 c;
    u64 rgba;
    u64 xyz;
} Vtx_b215_01E04010;

typedef struct {
    u8 hdr[0x10];
    Vtx_b215_01E04010 v[4];
    u8 tail[0x20];
} Pk_b215_01E04010;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[0x14];
    C4_b215_01E04010 col0;
    C4_b215_01E04010 col1;
} Obj_b215_01E04010;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x3BC0 - 0xC0];
    Vec4f grid[20][40];
    u8 pad6DC0[0x9FFC - 0x6DC0];
    s32 ot;
    u8 padA000[0xA048 - 0xA000];
    s16 frames[20][50];
    u8 padA818[0xB460 - 0xA818];
    s16 a[20][40];
    u8 padBAA0[0xC0E0 - 0xBAA0];
    s16 b[20][40];
    u8 padC720[0xE878 - 0xC720];
    u8 trig[1];
} Game_b215_01E04010;

static void func_01E04010_b215(Game_b215_01E04010 *g, Obj_b215_01E04010 *o, s32 mode, Vec4f *in) {
    extern Rgbaq_b215_01E04010 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00108D20(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f pos;
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    Vec4f rm;
    Pk_b215_01E04010 pk __attribute__((aligned(8)));
    C4_b215_01E04010 c;
    s16 i;
    s16 j;
    s16 a;
    Pk_b215_01E04010 *p;
    s32 k;

    pos = *in;
    c = o->col0;
    p = &pk;
    c.a = 0;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, &o->col0, 1);
    func_00107790(p, &o->col1, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos.x;
    v[1] = pos.y;
    v[2] = pos.z;
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 20; i++) {
        if (i == 0) {
            p->v[0].c = func_00107740(&c);
            p->v[1].c = func_00107740(&o->col0);
            p->v[2].c = func_00107740(&c);
            p->v[3].c = func_00107740(&o->col0);
        }
        if (i == 1) {
            p->v[0].c = func_00107740(&o->col0);
            p->v[1].c = func_00107740(&o->col0);
            p->v[2].c = func_00107740(&o->col0);
            p->v[3].c = func_00107740(&o->col0);
        }
        if (i == 19) {
            p->v[0].c = func_00107740(&o->col0);
            p->v[1].c = func_00107740(&c);
            p->v[2].c = func_00107740(&o->col0);
            p->v[3].c = func_00107740(&c);
        }
        for (j = 0; j < 28; j++) {
            func_00106080(&rm, 0x14, g->frames[i][j], 0);
            g->rect = rm;
            func_00108500(p, &g->rect, g->frame);
            func_00108D20(q, o->f48, o->f48);
            tw[0] = g->a[i][j];
            tw[1] = g->b[i][j];
            func_00109100(q, tw, 1, g->trig);
            func_00109100(q, tw, 0, g->trig);
            func_00107070(q, 0, g->grid[i][j].x);
            func_00107070(q, 2, g->grid[i][j].z);
            func_00107070(q, 1, g->grid[i][j].y);
            if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->ot, func_001A23B0(depth[0]));
            }
            a += 10;
        }
    }
}


/* shape b215:01E04520, 172 insns: b413:01E04E20 family effect pass over 130 entities: sets up the two packets, draws every live b215:01E02540 entity (then b215:01E02660 on it), then re-sends packet A with the model lights (func_001F7060) and draws every live b215:01E02B70 entity */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u8 t48[0x10];
} PktA_b215_01E04520;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x68];
    u64 a;
    s32 b[4];
} PktB_b215_01E04520;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 state;
    u8 pad5A[0x16];
} Ent_b215_01E04520;

typedef struct {
    u8 pad0000[0x2A0];
    Ent_b215_01E04520 ents[130];
    u8 pad[0xA004 - 0x2A0 - 130 * 0x70];
    s32 list;
    PktA_b215_01E04520 *pa;
    PktB_b215_01E04520 *pb;
} Mgr_b215_01E04520;

static void func_01E04520_b215(Mgr_b215_01E04520 *m) {
    extern void b215_01E02540(Mgr_b215_01E04520 *, Ent_b215_01E04520 *);
    extern void b215_01E02660(Mgr_b215_01E04520 *, Ent_b215_01E04520 *);
    extern void b215_01E02B70(Mgr_b215_01E04520 *, Ent_b215_01E04520 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    PktA_b215_01E04520 a __attribute__((aligned(8)));
    PktB_b215_01E04520 b __attribute__((aligned(8)));
    PktB_b215_01E04520 *p;
    s32 i;

    m->pa = &a;
    m->pb = &b;
    m->list = func_00207F60();
    m->pa->count = 0x26;
    m->pa->tag = 5;
    m->pa->regs = 0x42421;
    m->pa->pad = 0;
    m->pb->count = 0x34;
    m->pb->tag = 0xC;
    m->pb->regs = ((u64)0x4214 << 32) | 0x21421421;
    m->pb->pad = 0;
    func_00208460();
    func_002086D0(m->pb, ((u64)0x80 << 32) | 0x48);
    p = m->pb;
    func_00208800(func_00209E50(), 0, &p->a, p->b);
    func_00208460();
    for (i = 0; i < 130; i++) {
        if (m->ents[i].state != 0 && m->ents[i].cb == (void *)b215_01E02540) {
            b215_01E02540(m, &m->ents[i]);
            b215_01E02660(m, &m->ents[i]);
        }
    }
    m->pa->count = 0x26;
    m->pa->tag = 5;
    m->pa->regs = 0x42421;
    m->pa->pad = 0;
    func_00208460();
    func_002086D0(m->pa, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &a.t40, &a.t48);
    func_00208460();
    for (i = 0; i < 130; i++) {
        if (m->ents[i].state != 0 && m->ents[i].cb == (void *)b215_01E02B70) {
            b215_01E02B70(m, &m->ents[i]);
        }
    }
    func_00207FD0(m->list, func_00207500(), 0);
}
