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

static void func_01E00080_b425(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b425 in the
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

static void func_01E00920_b425(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b425((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

extern void b425_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00BE0_b425(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    b425_01E00080(p, o->b94, o->hC0);
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

/* shape b425:01E01150, 322 insns: the module's spawn step: follows joint 0xDFA4; ticks 68..250 spawn one (odd tick)
   or two b425:01E01660 puffs and one b425:01E01C80 puff 3.5 lower and 4 to one side; ticks 130..295 every 15th start
   one of 20 rising rings (size 10..17, height -15, random angle); every live ring spawns a b425:01E01B10 with its
   size/angle/height, rises 1.5 until past 18 and turns 10 one way (even) or the other */

typedef struct {
    f32 x, y, z, w;
} V4_b425_01E01150;

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0xDD90 - 0x25C];
    V4_b425_01E01150 h[20];
    u8 padDED0[0xDEF4 - 0xDED0];
    f32 fh;
    u8 padDEF8[0xDF3C - 0xDEF8];
    f32 fsz;
    u8 padDF40[4];
    f32 size[20];
    u8 padDF94[0xDFA4 - 0xDF94];
    s16 joint;
    u8 padDFA6[0xE002 - 0xDFA6];
    s16 fang;
    u8 padE004[4];
    s16 ang[20];
    s16 live[20];
    s16 k;
    u8 padE05A[6];
    s16 cur;
    u8 padE062[2];
    s16 side;
    u8 padE066[2];
    s16 t;
} Scene_b425_01E01150;

static s32 func_01E01660_b425();
static s32 func_01E01B10_b425();
static s32 func_01E01C80_b425();
static s32 func_01E02B60_b425();

static void func_01E01150_b425(Scene_b425_01E01150 *s) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    s->t++;
    func_001F5620(func_001F53A0(), s->joint, &s->px);
    if (s->t >= 0x44 && s->t < 0xFB) {
        if (s->t % 2 == 1) {
            n = 1;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), s->joint, &s->px);
            s->py -= 3.5f;
            if (s->side != 0) {
                s->pz -= 4.0f;
            } else {
                s->pz += 4.0f;
            }
            func_01E02B60_b425(s, func_01E01660_b425, 0);
        }
        for (i = 0; i < 1; i++) {
            func_001F5620(func_001F53A0(), s->joint, &s->px);
            s->py -= 3.5f;
            if (s->side != 0) {
                s->pz -= 4.0f;
            } else {
                s->pz += 4.0f;
            }
            func_01E02B60_b425(s, func_01E01C80_b425, 0);
        }
    }
    if (s->t >= 0x82 && s->t < 0x128) {
        if (s->t % 15 == 1 && s->k < 20) {
            s->live[s->k]++;
            s->size[s->k] = 10.0f + (func_0019A5C8() >> 4) % 8;
            s->h[s->k].y = -15.0f;
            s->ang[s->k] = (func_0019A5C8() >> 4) % 360;
            s->k++;
            if (s->k >= 20) {
                s->k = 0;
            }
        }
    }
    for (i = 0; i < 20; i++) {
        if (s->live[i] != 0) {
            s->cur = i;
            s->fsz = s->size[i];
            s->fang = s->ang[i];
            s->fh = s->h[i].y;
            func_01E02B60_b425(s, func_01E01B10_b425, 0);
            s->h[i].y += 1.5f;
            if (s->h[i].y > 18.0f) {
                s->live[i] = 0;
            }
            if (i % 2 == 0) {
                s->ang[i] += 10;
            } else {
                s->ang[i] -= 10;
            }
        }
    }
}

/* shape b425:01E01660, 297 insns: b425:01E01C80's puff in white (0xFF, 0xFF, 0x80, alpha in by 0xC0 for 75 ticks,
   out by 11): sheet 1 picks a random frame 0..3 each tick, sheet 0 steps the frame every fourth tick up to 8 and back
   down to 0; frame step 100..449; asks the camera position once more each tick (unused) */

typedef struct {
    u8 pad0[0xDFA4];
    s16 v;
    u8 padDFA6[0xE068 - 0xDFA6];
    s16 count;
} Ctx_b425_01E01660;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b425_01E01660;

static s32 func_01E01660_b425(Ctx_b425_01E01660 *ctx, Obj_b425_01E01660 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 c[4];

    if (o->state == 1) {
        o->f48 = 25.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        o->h6 = 1;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->f30 /= 50.0f;
        o->f34 /= 60.0f;
        o->f38 /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->f3C = (a[2] - b[2]) / 60.0f;
        o->state = 2;
    }
    if (o->f48 < 45.0f) {
        o->f48 += 1.5f;
    }
    if (o->t < 75) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t > 10 && o->t < 70) {
        o->x += 1.4f * o->f30;
        o->z += o->f38;
    }
    if (o->h6 == 1) {
        o->h56 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h6 == 0) {
        if (o->h5A == 0) {
            if (o->t % 4 == 1) {
                o->h56++;
            }
            if (o->h56 > 7) {
                o->h5A = 1;
            }
        } else {
            if (o->t % 4 == 1) {
                o->h56--;
            }
            if (o->h56 <= 0) {
                o->h5A = 0;
            }
        }
    }
    func_001F5F90(func_001F5380(), c);
    if (o->t != 0) {
        o->z += o->f3C;
        o->f48 += 1.5f;
        if (o->y > 35.0f) {
            o->y -= 2.0f;
        }
    }
    if (ctx->count > 290) {
        o->t = 100;
    }
    o->t++;
    return 0;
}

/* shape b425:01E01B10, 89 insns: a yellow flicker (130 x 130 growing 3 a tick up to 160, frame re-rolled 0..3 each tick): in by 96 up to 0xC0 for 5 ticks, then out by 9 and ends; its clock jumps to 20 once the scene value reaches 296 */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[4];
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b425_01E01B10;

typedef struct {
    u8 pad[0xE068];
    s16 val;
} Game_b425_01E01B10;

static s32 func_01E01B10_b425(Game_b425_01E01B10 *g, Obj_b425_01E01B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 130;
        o->hA = 130;
        o->kind = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->mode = 2;
    }
    if (o->t < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (o->h8 < 160) {
            o->h8 += 3;
        }
        if (o->hA < 160) {
            o->hA += 3;
        }
    }
    o->kind = (func_0019A5C8() >> 4) % 4;
    func_00205C40((s32)&o->w20);
    if (g->val > 295) {
        o->t = 20;
    }
    o->t++;
    return 0;
}

/* shape b425:01E01C80, 265 insns: b038:01E01090's smoke puff in olive (0x30, 0x30, 0x10): size 25 growing 1.5 a tick
   up to 45 (and 1.5 more while moving), random sheet 0..3, frame step every 10..24 ticks, drift (-20..19) / 50 x 1.4
   on x and / 60 on z between ticks 11 and 69, a fall toward point ctx->v over 60 ticks, sinking 2 while above 35;
   fades in for 75 ticks, out by 4; the scene counter past 290 ends it */

typedef struct {
    u8 pad0[0xDFA4];
    s16 v;
    u8 padDFA6[0xE068 - 0xDFA6];
    s16 count;
} Ctx_b425_01E01C80;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b425_01E01C80;

static s32 func_01E01C80_b425(Ctx_b425_01E01C80 *ctx, Obj_b425_01E01C80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];

    if (o->state == 1) {
        o->f48 = 25.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        o->h6 = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->col, 0x30, 0x30, 0x10);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = (func_0019A5C8() >> 4) % 15 + 10;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->f30 = func_0019A5C8() % 40 - 20;
        o->f34 = func_0019A5C8() % 40 - 20;
        o->f38 = func_0019A5C8() % 40 - 20;
        o->f30 /= 50.0f;
        o->f34 /= 60.0f;
        o->f38 /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->f3C = (a[2] - b[2]) / 60.0f;
        o->state = 2;
    }
    if (o->f48 < 45.0f) {
        o->f48 += 1.5f;
    }
    if (o->t < 75) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->state = 0;
    }
    if (o->t > 10 && o->t < 70) {
        o->x += 1.4f * o->f30;
        o->z += o->f38;
    }
    if (o->t % o->h52 == 1) {
        o->h56++;
    }
    if (o->h56 > 7) {
        o->h56 = 0;
    }
    if (o->t != 0) {
        o->z += o->f3C;
        o->f48 += 1.5f;
        if (o->y > 35.0f) {
            o->y -= 2.0f;
        }
        o->h50 += 5;
    }
    if (ctx->count > 290) {
        o->t = 100;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E020B0_b425(void) {
    return 0;
}

/* shape b425:01E020C0 (b425), 677 insns, 1 copy: b178:01E042E0's scene manager on 500 slots: setup (six joints,
   jitter tables, the 30 slot sizes filled to 40 past their 20, which overwrites the joint ids), else the spawn step,
   the slot handlers, then draws the three puff/ring kinds (the ring three times, 120 apart); the draw calls through
   aliases */

typedef struct {
    u8 pad0[6];
    s16 h06;
    u8 pad8[8];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0xC];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b425_01E020C0;

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
        s16 h[8];
    } c;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b425_01E020C0 fx[500];
    u8 padDD60[0x1A0];
    s32 tex[3];
    u8 padDF0C[0x14];
    s32 count;
    u8 padDF24[8];
    s32 ot;
    u8 padDF30[0x14];
    union {
        f32 size[30];
        struct {
            u8 pad[0x60];
            s16 jA;
            s16 jB;
            s16 jC;
            s16 jD;
            s16 jE;
            s16 jF;
            u8 pad6C[4];
            s16 cam;
        } j;
    } u;
    u8 padDFBC[8];
    s16 rnd[30];
    u8 padE000[8];
    s16 ang[20];
    u8 padE030[0x34];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padE26A[2];
    u8 crd[0x170];
    u8 padE3DC[4];
} Scene_b425_01E020C0;

static s32 func_01E020C0_b425(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8();
    extern void b425_01E01150();
    extern void b425_01E00920();
    extern void b425_01E00BE0();
    Scene_b425_01E020C0 *g = (Scene_b425_01E020C0 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE3E0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x154;
        g->u.j.jA = func_001F5560(func_001F53A0(), 0x1E, 1);
        g->u.j.jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->u.j.jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->u.j.jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->u.j.jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->u.j.jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->u.j.cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
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
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 30; k++) {
            g->rnd[k] = func_0019A5C8() % 8;
        }
        for (k = 0; k < 30; k++) {
            g->u.size[k] = 40.0f;
        }
        for (k = 0; k < 20; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    b425_01E01150(g, 0);
    for (k = 0; k < 500; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E020B0_b425) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 500; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01660_b425) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                if (g->fx[k].h56 < 2) {
                    g->c.h[0] = g->fx[k].h56 << 6;
                    g->c.h[1] = 0;
                } else {
                    g->c.h[0] = (g->fx[k].h56 - 2) << 6;
                    g->c.h[1] = 0;
                }
                g->c.h[2] = 0x3F;
                g->c.h[3] = 0x3F;
                if (g->fx[k].h06 == 0) {
                    func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                    *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                    g->tex88 = g->tex[2];
                } else {
                    g->tex88 = g->tex[1];
                }
                g->hC0 = 5;
                g->hB8 = 1;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hBE = 0;
                b425_01E00BE0(g, &g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01B10_b425) {
                g->tex88 = g->tex[1];
                if (g->fx[k].h56 < 2) {
                    g->c.h[0] = g->fx[k].h56 << 6;
                    g->c.h[1] = 0;
                } else {
                    g->c.h[0] = (g->fx[k].h56 - 2) << 6;
                    g->c.h[1] = 0;
                }
                g->c.h[2] = 0x3F;
                g->c.h[3] = 0x3F;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y += g->fx[k].f34;
                b425_01E00920(g, &g->fx[k], 0x10, &v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 120, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 120, 0);
                v.y += g->fx[k].f34;
                b425_01E00920(g, &g->fx[k], 0x10, &v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 240, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 240, 0);
                v.y += g->fx[k].f34;
                b425_01E00920(g, &g->fx[k], 0x10, &v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C80_b425) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex[2];
                g->hC0 = g->fx[k].h06;
                g->hB8 = 3;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b425_01E00BE0(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x6F) {
        return 1;
    }
    if (g->frame == 0x145) {
        return 4;
    }
    if (g->frame == 0x13B) {
        return 5;
    }
    if (g->frame > 0x79 && g->frame < 0x136) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b425:01E02B60, 114 insns, 2 copies: spawns an effect into the first free slot (500 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x18];
    f32 f34;
    u8 pad38[8];
    s32 w40;
    s32 w44;
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b425_01E02B60;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b425_01E02B60 slot[500];
    u8 padDD60[0xDEF4 - 0x2A0 - 500 * 0x70];
    f32 fDEF4;
    u8 padDEF8[0x2C];
    u8 col[4];
    u8 padDF28[0x14];
    f32 fDF3C;
    u8 padDF40[0xC2];
    s16 hE002;
    u8 padE004[0x5C];
    s16 hE060;
} Scene_b425_01E02B60;

static s32 func_01E02B60_b425(Scene_b425_01E02B60 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b425_01E02B60 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 500; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 500;
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
        sl->h50 = s->hE060;
        sl->h52 = s->hE060;
        sl->h5A = s->hE002;
        sl->f34 = s->fDEF4;
        sl->f48 = s->fDF3C;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}
