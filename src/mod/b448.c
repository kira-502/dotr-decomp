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

static void func_01E00080_b448(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

extern void b448_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b448(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    b448_01E00080(p, o->b94, o->hC0);
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

static void func_01E00E90_b448(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b448:01E01200, 83 insns: counts the scene timer; on frames 0x70..0x104 spawns three b448:01E01350 effects at the model
   joint, and on frame 25 two b448:01E016E0 effects (angles 0 and 90) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB228 - 0x260];
    s16 joint;
    u8 padB22A[0x20];
    s16 ang;
    u8 padB24C[0x12];
    s16 t;
} Scene_b448_01E01200;

static void func_01E01200_b448(Scene_b448_01E01200 *s) {
    extern void b448_01E01350(void);
    extern void b448_01E016E0(void);
    extern s32 b448_01E01E50(Scene_b448_01E01200 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    s->t++;
    if (s->t >= 0x70 && s->t < 0x105) {
        if (s->t < 0x64) {
            n = 3;
        } else {
            n = 3;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), s->joint, &s->pos);
            b448_01E01E50(s, b448_01E01350, 0);
        }
    }
    if (s->t == 0x19) {
        s->ang = 0;
        b448_01E01E50(s, b448_01E016E0, 0);
        s->ang = 0x5A;
        b448_01E01E50(s, b448_01E016E0, 0);
    }
}

/* shape b448:01E01350 (B448_OBJ_MOVE_2_), 226 insns: a white glow: size 30 growing 1.5, kind (rand >> 4) % 8, spin
   10..29, random drift (-20..19) / 60 applied from tick 11 to 69, a z climb of an 80th of the camera-to-joint (game
   +0xB228) gap; brightens by 0xC0 below 0xC0 for 100 ticks, then fades by 8; f5A grows by 3 up to 180; once the game
   value at 0xB25E passes 300 it jumps to the fade */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 spin;
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x14];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 rise;
    u8 pad40[8];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b448_01E01350;

typedef struct {
    u8 pad[0xB228];
    s16 j;
    u8 padB22A[0x34];
    s16 v;
} Game_b448_01E01350;

static s32 func_01E01350_b448(Game_b448_01E01350 *g, Fx_b448_01E01350 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 c[4];

    if (o->mode == 1) {
        o->size = 30.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = 45;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->f50;
        o->f50 = 0;
        o->f52 = func_0019A5C8() % 350 + 100;
        o->spin = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->dx = func_0019A5C8() % 40 - 20;
        o->dy = func_0019A5C8() % 40 - 20;
        o->dz = func_0019A5C8() % 40 - 20;
        o->dx /= 60.0f;
        o->dy /= 60.0f;
        o->dz /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), g->j, b);
        o->rise = (a[2] - b[2]) / 80.0f;
        o->mode = 2;
    }
    if (o->tick < 100) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick > 10 && o->tick < 70) {
        o->x += o->dx;
        o->y += o->dy;
        o->z += o->dz;
    }
    func_001F5F90(func_001F5380(), c);
    if (o->tick != 0) {
        o->z += o->rise;
        o->size += 1.5f;
    }
    if (o->tick != 0) {
        if (o->f5A < 180) {
            o->f5A += 3;
        }
    }
    if (g->v > 300) {
        o->tick = 100;
    }
    o->tick++;
    return 0;
}

/* shape b448:01E016E0, 65 insns: on start f48 6, colour 0x80 grey, second colour (0x80, 0x10, 0x10) with alpha 0, 0x30 = 6.5f,
   0x34 = 50.0f; alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and stops; 0x34 grows by 10.0f after the
   first tick; 0x5A advances 6 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b448_01E016E0;

static s32 func_01E016E0_b448(s32 arg0, Fx_b448_01E016E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->f30 = 6.5f;
        o->f34 = 50.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f34 += 10.0f;
    }
    o->tick++;
    o->f5A += 6;
    return 0;
}

/* shape b448:01E017F0 (b448), 408 insns, 1 copy: the module scene manager (b276:01E01760 / b618:01E01210 form): with
   a scene id it clears the scene, keeps the two camera words, sets the 330-frame countdown, reads four model ids,
   textures 4:15 and 5:0..1, the camera turn, scale 0.1 and the jitter tables; otherwise it runs the scene script
   b448:01E01200, every effect handler, draws the b448:01E01350 glows (bobbed by the sine table) and the b448:01E016E0
   eyes at joints B and C, counts down and returns the next step by frame (160, 320, 171..314) or 8 when the countdown
   runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b448_01E017F0;

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
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x178];
    Vec4f spawn;
    s32 w260[16];
    Fx_b448_01E017F0 fx[400];
    u8 padB1A0[0x30];
    s32 tex[2];
    u8 padB1D8[0x18];
    s32 count;
    u8 padB1F4[8];
    s32 ot;
    u8 padB200[4];
    s32 cam1;
    s32 cam2;
    u8 padB20C[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padB22E[0xA];
    s16 cam;
    u8 padB23A[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b448_01E017F0;

static s32 func_01E017F0_b448(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F9AD0(s32);
    extern s32 func_001F9D30(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E01200_b448();
    extern void func_01E00920_b448();
    Scene_b448_01E017F0 *g = (Scene_b448_01E017F0 *)arg0;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    s16 i;
    s32 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    g->cam1 = func_001F9AD0(0);
    g->cam2 = func_001F9D30(0);
    if (id >= 0) {
        func_00195108(g, 0xB5D0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 330;
        g->jA = func_001F5560(func_001F53A0(), 0x40, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x41, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x42, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 15; k < 16; k++) {
            g->w260[k] = func_00202BF0(4, k);
        }
        for (k = 0; k < 2; k++) {
            g->tex[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 4;
        }
        for (i = 180; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01200_b448(g, 0);
    for (i = 0; i < 400; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 400; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == (void *)func_01E01350_b448) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 1;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                g->py -= 40.0f * func_00108030(g->crd, 0x2D, 0);
                g->py += 40.0f * func_00108030(g->crd, g->fx[i].h5A, 0);
                g->hBE = 0;
                func_01E00920_b448(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (void *)func_01E016E0_b448) {
                func_001F5620(func_001F53A0(), g->jB, &v);
                g->tex88 = g->w260[15];
                func_00106080(rm2, 0x9A, 0, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                v.w = 0;
                func_01E00E90_b448((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
                func_001F5620(func_001F53A0(), g->jC, &v);
                func_01E00E90_b448((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[i], 0, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 160) {
        return 1;
    }
    if (g->frame == 320) {
        return 3;
    }
    if (g->frame > 170 && g->frame < 315) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b448:01E01E50, 82 insns: c035:01E01150 family: take the first free effect slot of 400 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

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
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b448_01E01E50;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b448_01E01E50 slot[400];
    u8 padEnd[0xb1f4 - 0x2a0 - 400 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padB1F8[0x52];
    s16 ang;
    u8 padB24C[0xA];
    s16 h30;
} Ctx_b448_01E01E50;

static s32 func_01E01E50_b448(Ctx_b448_01E01E50 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b448_01E01E50 *s;

    s = NULL;
    for (i = 0; i < 400; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 400;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h50 = ctx->h30;
        s->h5A = ctx->ang;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}
