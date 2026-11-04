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

static void func_01E00080_b751(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b751(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b751 in the
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

static void func_01E00C80_b751(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b751((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b065_01E012B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b065_01E012B0;

typedef struct {
    Col_b065_01E012B0 c;
    u64 st;
    u64 xyz;
} Vtx_b065_01E012B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b065_01E012B0 v[4];
    u8 tail[0x20];
} Pkt_b065_01E012B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Anim_b065_01E012B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b065_01E012B0;

static void func_01E00F40_b751(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107740(void *, void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b065_01E012B0 quad[4];
    Vec_b065_01E012B0 at;
    Vec_b065_01E012B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b065_01E012B0 pkt;
    Col_b065_01E012B0 c0;
    Col_b065_01E012B0 c1;
    Col_b065_01E012B0 c2;
    Col_b065_01E012B0 c3;
    s16 blend;
    s32 i;
    s32 a;
    s16 j;
    s16 wd;
    Pkt_b065_01E012B0 *p;
    s32 width;
    f32 w0;
    f32 w1;

    p = &pkt;
    width = an->width;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    blend = mode >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col0, 0);
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    func_00107740(&c0, an->col0);
    p->v[0].c = c0;
    func_00107740(&c1, an->col1);
    p->v[2].c = c1;
    func_00107740(&c2, an->col0);
    p->v[1].c = c2;
    func_00107740(&c3, an->col1);
    p->v[3].c = c3;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    wd = width;
    for (i = 0; i < o->count; i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + wd);
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if ((mode & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if ((mode & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        }
        j += an->step;
    }
}

/* shape b751:01E01350, 220 insns: the effect scene's step (b735:01E01AD0 family): counts the frame (0xB2B8); frame 99
   spawns twelve 0x1E016C0 on each of joints 0xB244 and 0xB246, frame 103 on joints 0xB248 and 0xB24A; frame 118 spawns
   0x1E01890, twelve 0x1E01BF0 and twelve 0x1E01E30 on joint 0xB24C; frames 107..118 spawn three 0x1E01980 there; frame
   107 spawns 0x1E02070 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB244 - 0x260];
    s16 j[5];
    u8 padB24E[0x6A];
    s16 t;
} Scene_b751_01E01350;

static void func_01E01350_b751(Scene_b751_01E01350 *g) {
    extern void b751_01E016C0(void);
    extern void b751_01E01890(void);
    extern void b751_01E01980(void);
    extern void b751_01E01BF0(void);
    extern void b751_01E01E30(void);
    extern void b751_01E02070(void);
    extern s32 b751_01E02920(Scene_b751_01E01350 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t == 99) {
        func_001F5620(func_001F53A0(), g->j[0], &g->pos);
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E016C0, 0);
        }
        func_001F5620(func_001F53A0(), g->j[1], &g->pos);
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E016C0, 0);
        }
    }
    if (g->t == 103) {
        func_001F5620(func_001F53A0(), g->j[2], &g->pos);
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E016C0, 0);
        }
        func_001F5620(func_001F53A0(), g->j[3], &g->pos);
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E016C0, 0);
        }
    }
    if (g->t == 118) {
        func_001F5620(func_001F53A0(), g->j[4], &g->pos);
        b751_01E02920(g, (s32)b751_01E01890, 0);
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E01BF0, 0);
        }
        for (i = 0; i < 12; i++) {
            b751_01E02920(g, (s32)b751_01E01E30, 0);
        }
    }
    if (g->t < 119) {
        if (g->t >= 107) {
            func_001F5620(func_001F53A0(), g->j[4], &g->pos);
            b751_01E02920(g, (s32)b751_01E01980, 0);
            b751_01E02920(g, (s32)b751_01E01980, 0);
            b751_01E02920(g, (s32)b751_01E01980, 0);
        }
    }
    if (g->t == 107) {
        b751_01E02920(g, (s32)b751_01E02070, 0);
    }
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b751:01E016C0, 115 insns: spark thrown 8.6 units out at a random angle, drifting 0.6 a frame after that */

typedef struct Sp_b751_01E016C0 {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x24];
    s16 age;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Sp_b751_01E016C0;

typedef struct Scn_b751_01E016C0 {
    u8 pad0[0xB4BC];
    u8 table[0x10];
} Scn_b751_01E016C0;

static s32 func_01E016C0_b751(Scn_b751_01E016C0 *w, Sp_b751_01E016C0 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->h8 = 0x78;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
        o->z += 8.6f * func_00108030((s32)w->table, o->ang, 0);
        o->x += 8.6f * func_00108030((s32)w->table, o->ang, 1);
    }
    if (o->age < 6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->z += 0.6f * func_00108030((s32)w->table, o->ang, 0);
        o->x += 0.6f * func_00108030((s32)w->table, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->age++;
    return 0;
}

/* shape b751:01E01890, 59 insns: constant variant of b415:01E022B0 (colour (255, 192, 192), colour (255, 128, 64)) */

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
} Fx_b751_01E01890;

static s32 func_01E01890_b751(s32 arg0, Fx_b751_01E01890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 220.0f;
        func_001076F0(o->col2, 0xFF, 0xC0, 0xC0);
        func_001076F0(o->col, 0xFF, 0x80, 0x40);
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

/* shape b751:01E01980, 156 insns: b751:01E01BF0 family rising flash with the colours swapped (outer red or pink on black/grey), random height width 6..61, rising (150..229)/10 per tick with f34 growing alongside from 100, tilted +-0x4000 by the scene flag (ctx+0xB2B4) and turning rot[2] 0x100 per tick; full alpha 8 ticks then down by 5; f4C = 0.8 of the height */

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b751_01E01980;

typedef struct {
    u8 pad0[0xB2B4];
    s16 flag;
} Ctx_b751_01E01980;

static s32 func_01E01980_b751(Ctx_b751_01E01980 *g, Obj_b751_01E01980 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c1, 0xC0, 0x20, 0x20);
            func_001076F0(o->c0, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c1, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->c0, 0x30, 0x30, 0x30);
        }
        o->w = 60;
        o->h = (func_0019A5C8() >> 4) % 56 + 6;
        o->f38 = func_0019A5C8() % 80 + 150;
        o->f38 /= 10.0f;
        o->f30 = func_0019A5C8() % 80 + 150;
        o->f30 /= 10.0f;
        o->f34 = 100.0f;
        o->state = 2;
        o->c1[3] = 0;
        if (g->flag != 0) {
            o->rot0 = 0x4000;
        } else {
            o->rot0 = -0x4000;
        }
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c1[3] = 0x80;
    } else if (o->c1[3] > 6) {
        o->c1[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f38;
    o->f4C = 0.8f * o->f48;
    o->f34 += o->f38;
    o->rot2 += 0x100;
    o->t++;
    return 0;
}

/* shape b751:01E01BF0, 143 insns: b418:01E02340 family rising flash (red on black or light red on grey 0x30), size 60, from 140 rising (120..169)/10 per tick, f30 (150..229)/10, f34 100, f4C = 0.1 of the height; full alpha 8 ticks then down by 3 */

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b751_01E01BF0;

static s32 func_01E01BF0_b751(void *arg0, Obj_b751_01E01BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c0, 0xC0, 0x20, 0x20);
            func_001076F0(o->c1, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c0, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->c1, 0x30, 0x30, 0x30);
        }
        o->w = 60;
        o->h = 60;
        o->f38 = func_0019A5C8() % 50 + 120;
        o->f38 /= 10.0f;
        o->f30 = func_0019A5C8() % 80 + 150;
        o->f30 /= 10.0f;
        o->f34 = 100.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 4) {
        o->c0[3] -= 3;
    } else {
        o->state = 0;
    }
    o->f48 += o->f38;
    o->f4C = 0.1f * o->f48;
    o->t++;
    return 0;
}

/* shape b751:01E01E30, 141 insns: b750:01E02770 variant: size 140, blue or white-blue colours, grey 0x40/0x30 shades,
   h5C 10, growth 12.0..16.9 a tick, f30 15.0..22.9, f34 100, alpha 0x80 for 8 ticks then down by 3, f4C 0.1 */

typedef struct {
    u8 pad00[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 h54;
    u8 pad56[2];
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b751_01E01E30;

static s32 func_01E01E30_b751(s32 unused, Obj_b751_01E01E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 140.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c60, 0x20, 0x20, 0xC0);
            func_001076F0(o->c64, 0x40, 0x40, 0x40);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c60, 0xA0, 0xA0, 0xFF);
            func_001076F0(o->c64, 0x30, 0x30, 0x30);
        }
        o->h5A = 60;
        o->h5C = 10;
        o->f38 = func_0019A5C8() % 50 + 120;
        o->f38 /= 10.0f;
        o->f30 = func_0019A5C8() % 80 + 150;
        o->f30 /= 10.0f;
        o->f34 = 100.0f;
        o->h58 = 2;
        o->c64[3] = 0;
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
    }
    if (o->h54 < 8) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 4) {
        o->c60[3] -= 3;
    } else {
        o->h58 = 0;
    }
    o->f48 += o->f38;
    o->f4C = 0.1f;
    o->h54++;
    return 0;
}

/* shape b751:01E02070, 112 insns: b550:01E03D30 family: draws the bar sprite in its own colour (set to 0x90/0x80/0x80), alpha in by 20 up to 0x50 for 30 ticks, then out by 9 and ends */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b751_01E02070;

typedef struct {
    Hdr_b751_01E02070 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b751_01E02070;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b751_01E02070;

static s32 func_01E02070_b751(s32 arg0, Obj_b751_01E02070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    Pkt_b751_01E02070 p __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x90, 0x80, 0x80);
        o->mode = 2;
    }
    ((Hdr_b751_01E02070 *)(s32)&p)->count = 0x26;
    ((Hdr_b751_01E02070 *)(s32)&p)->tag = 5;
    ((Hdr_b751_01E02070 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b751_01E02070 *)(s32)&p)->pad = 0;
    p.r = o->col[0];
    p.g = o->col[1];
    p.b = o->col[2];
    p.a = o->col[3];
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    if (o->t < 30) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x14;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02230_b751(void) {
    return 0;
}

/* shape b751:01E02240 (b751), 437 insns, 1 copy: b751 scene manager in b396:01E01F00 form: setup (five joints, two
   type-4 and two type-5 textures, 256 s8 and 30 s16 jitters), step b751:01E01350 and every slot except b751:01E02230,
   draw the b751:01E016C0 smoke, b751:01E01890 circle and b751:01E01980/01E01BF0/01E01E30 circles; scene code from the
   timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b751_01E02240;

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
        s16 uv[4];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b751_01E02240 fx[400];
    u8 padB1A0[0x50];
    s32 tex[3];
    u8 padB1FC[0x14];
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
} Scene_b751_01E02240;

static s32 func_01E02240_b751(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01350_b751();
    extern void func_01E00920_b751();
    extern void func_01E00C80_b751();
    extern void func_01E00F40_b751();
    Scene_b751_01E02240 *g = (Scene_b751_01E02240 *)arg0;
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
        g->count = 190;
        g->jA = func_001F5560(func_001F53A0(), 0x2C, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x36, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x42, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x4C, 0);
        g->jE = func_001F5560(func_001F53A0(), 0xF, 0);
        for (i = 14; i < 16; i++) {
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
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E01350_b751(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02230_b751) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E016C0_b751) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                func_01E00C80_b751(g, &g->fx[k], 0x10, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01890_b751) {
                g->hB8 = 0x24;
                func_01E00920_b751(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01980_b751) {
                func_00106080(rm2, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex260[15];
                g->tex88 = g->tex[1];
                g->tex88 = g->tex[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x80;
                g->u94.uv[3] = 0x80;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 6;
                g->hBE = 0;
                func_01E00F40_b751(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01BF0_b751) {
                func_00106080(rm3, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex260[15];
                g->tex88 = g->tex[1];
                g->tex88 = g->tex[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x80;
                g->u94.uv[3] = 0x80;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 6;
                g->hBE = 0;
                func_01E00F40_b751(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E30_b751) {
                func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->tex88 = g->tex260[15];
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 6;
                g->hBE = 0;
                func_01E00F40_b751(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 108) {
        return 1;
    }
    if (g->frame == 185) {
        return 4;
    }
    if (g->frame == 160) {
        return 2;
    }
    if (g->frame > 118 && g->frame < 155) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b236:01E02330, 98 insns, 15 copies: take a free effect slot (400 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b236_01E02330 {
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
} Slot_b236_01E02330;

typedef struct Obj_b236_01E02330 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b236_01E02330 slots[400];
    u8 padB1A0[0x74];
    u8 rgba[4];
    u8 padB218[0x98];
    s16 fB2B0;
} Obj_b236_01E02330;

static s32 func_01E02920_b751(Obj_b236_01E02330 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b236_01E02330 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
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
