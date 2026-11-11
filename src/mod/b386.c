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

static void func_01E00080_b386(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

extern void b386_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b386(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    b386_01E00080(p, o->b94, o->hC0);
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E00E90_b386(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b386_01E00080();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b386_01E00080(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b386:01E013E0, 180 insns: the b386 module's event step: counts ticks; from 81 to 225 spawns three b386:01E016B0 and three b386:01E01D10 a tick at the tracked point (ctx+0xB228); before 82 spawns b386:01E01AC0 and b386:01E02480 there; from 150 to 250 spawns b386:01E02110 at the camera */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xB228 - 0x25C];
    s16 id;
    u8 padB22A[0xB25E - 0xB22A];
    s16 timer;
} Ctx_b386_01E013E0;

static void func_01E013E0_b386(Ctx_b386_01E013E0 *g) {
    extern s32 b386_01E016B0(void);
    extern s32 b386_01E01AC0(void);
    extern s32 b386_01E01D10(void);
    extern s32 b386_01E02110(void);
    extern s32 b386_01E02480(void);
    extern void b386_01E02F80(Ctx_b386_01E013E0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    s16 i;
    s16 n;

    g->timer++;
    if (g->timer >= 81 && g->timer < 226) {
        if (g->timer < 100) {
            n = 3;
        } else {
            n = 3;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->id, g->pos);
            b386_01E02F80(g, b386_01E016B0, 0);
        }
    }
    if (g->timer < 82) {
        func_001F5620(func_001F53A0(), g->id, g->pos);
        b386_01E02F80(g, b386_01E01AC0, 0);
    }
    if (g->timer >= 81 && g->timer < 226) {
        if (g->timer < 100) {
            n = 3;
        } else {
            n = 3;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->id, g->pos);
            b386_01E02F80(g, b386_01E01D10, 0);
        }
    }
    if (g->timer >= 150 && g->timer < 251) {
        for (i = 0; i < 1; i++) {
            func_001F5F90(func_001F5380(), g->pos);
            b386_01E02F80(g, b386_01E02110, 0);
        }
    }
    if (g->timer < 82) {
        for (i = 0; i < 1; i++) {
            func_001F5620(func_001F53A0(), g->id, g->pos);
            b386_01E02F80(g, b386_01E02480, 0);
        }
    }
}

/* shape b386:01E016B0, 257 insns: b618:01E00E90's spark in pale yellow (0xCF/0xCF/0x40), size 30 growing 0.8 and 0x5A 70 growing 3 to 160 while held, hold 80..99 ((rand>>4)%20); the camera-depth drift only during the hold, then it rises 1.5 a tick; alpha up to 0xC0 during the hold, then down by 12; scene time past 250 jumps to the fade */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 pos[3];
    u8 pad1C[0x14];
    f32 vel[3];
    f32 dz;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 tick;
    s16 frame;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b386_01E016B0;

typedef struct {
    u8 pad0[0xB228];
    s16 joint;
    u8 padB22A[0x34];
    s16 timer;
} Scn_b386_01E016B0;

static s32 func_01E016B0_b386(Scn_b386_01E016B0 *g, Fx_b386_01E016B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[8];

    if (o->mode == 1) {
        o->f48 = 30.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xCF, 0xCF, 0x40);
        o->f5A = 70;
        o->f5C = func_0019A5C8() % 360;
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
        o->h6 = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->vel[0] /= 60.0f;
        o->vel[1] /= 60.0f;
        o->vel[2] /= 60.0f;
        func_001F5F90(func_001F5380(), v);
        func_001F5620(func_001F53A0(), g->joint, &v[4]);
        o->dz = (v[2] - v[6]) / 80.0f;
        o->h6 = (func_0019A5C8() >> 4) % 20 + 80;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->tick > 10 && o->tick < 70) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    if (o->tick) {
        if (o->tick < o->h6) {
            o->pos[2] += o->dz;
        }
        if (o->tick >= o->h6) {
            o->pos[1] += 1.5f;
        }
        if (o->tick < o->h6) {
            o->f48 += 0.8f;
        }
    }
    if (o->tick != 0) {
        if (o->f5A < 160) {
            o->f5A += 3;
        }
    }
    if (g->timer > 250) {
        o->tick = 100;
    }
    o->tick++;
    return 0;
}

/* shape b386:01E01AC0, 148 insns: b394:01E01AA0 family yellow spark (size 6, frame 0..3, angle 0..359 turning 10, fA 0..7, fC = old f50, f50 2..6 growing 1..4, f8 0..34, life 3..7) rising 0..9/15 (rerolled each tick); colour flips yellow/gold every tick; full alpha then down by 8 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[4];
    f32 y;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b386_01E01AC0;

static s32 func_01E01AC0_b386(s32 arg0, Fx_b386_01E01AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x40);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 5 + 2;
        o->spin = func_0019A5C8() % 4 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x40);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0x20);
    }
    o->f34 = func_0019A5C8() % 10;
    o->f34 /= 15.0f;
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    if (o->tick != 0) {
        o->y += o->f34;
    }
    o->f5A += 10;
    o->tick++;
    return 0;
}

/* shape b386:01E01D10, 254 insns: b386:01E02110's blinking spark with f50 10..59 growing by its speed, held 10..19
   ticks while it closes an eightieth of the depth gap between the camera and the joint ctx+0xB228 each tick; past
   scene count 250 its tick jumps to 100 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    f32 z;
    u8 pad1C[0x14];
    f32 vel[3];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 life;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b386_01E01D10;

typedef struct {
    u8 pad0[0xB228];
    s16 joint;
    u8 padB22A[0xB25E - 0xB22A];
    s16 count;
} Ctx_b386_01E01D10;

static s32 func_01E01D10_b386(Ctx_b386_01E01D10 *g, Fx_b386_01E01D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 c[4];
    s32 t;

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = 70;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->side = 2;
        } else {
            o->side = 0;
        }
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 50 + 10;
        o->life = func_0019A5C8() % 350 + 100;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->vel[0] /= 60.0f;
        o->vel[1] /= 60.0f;
        o->vel[2] /= 60.0f;
        func_001F5F90(func_001F5380(), a);
        func_001F5620(func_001F53A0(), g->joint, b);
        o->f3C = (a[2] - b[2]) / 80.0f;
        o->hold = (func_0019A5C8() >> 4) % 10 + 10;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (g->count % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    func_001F5F90(func_001F5380(), c);
    t = o->tick;
    if (t != 0) {
        if ((s16)t < o->hold) {
            o->z += o->f3C;
        }
    }
    if (o->tick != 0) {
        if (o->f5A < 160) {
            o->f5A += 3;
        }
    }
    o->f50 += o->speed;
    if (g->count > 250) {
        o->tick = 100;
    }
    o->tick++;
    return 0;
}

/* shape b386:01E02110, 217 insns: b386:01E02480 cousin: white, size 10, f50 30..479; it blinks white/grey with the
   scene count (0xB25E) parity, drifts by f3C in z while held, then rises 1.5 a tick; f5A climbs by 3 to 160 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    f32 z;
    u8 pad1C[0x14];
    f32 vel[3];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 life;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b386_01E02110;

typedef struct {
    u8 pad0[0xB25E];
    s16 count;
} Ctx_b386_01E02110;

static s32 func_01E02110_b386(Ctx_b386_01E02110 *g, Fx_b386_01E02110 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 t;

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = 70;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->side = 2;
        } else {
            o->side = 0;
        }
        o->fC = o->f50;
        o->f50 = (func_0019A5C8() >> 4) % 450 + 30;
        o->life = func_0019A5C8() % 350 + 100;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->vel[0] /= 60.0f;
        o->vel[1] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (g->count % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    t = o->tick;
    if (t != 0) {
        if ((s16)t < o->hold) {
            o->z += o->f3C;
        }
        if (o->tick >= o->hold) {
            o->y += 1.5f;
        }
    }
    if (o->tick != 0) {
        if (o->f5A < 160) {
            o->f5A += 3;
        }
    }
    o->tick++;
    return 0;
}

/* shape b386:01E02480, 177 insns: b852:01E026F0 family pale-yellow (0xCF, 0xCF, 0x40) mote: size 20 growing 0.8 during the hold, frame 0..7, turn 70, angle 0..359, side 0 or 2, keeps the old 0x50 in 0xC, life 100..449, speed 10..29, 0x8 0..34, hold 3..7, drift (-20..19)/60; alpha up by 0xC0 to 0xC0 during the hold, then down by 12 while rising 0.5 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    u8 pad10[4];
    f32 y;
    u8 pad18[0x18];
    f32 vel[3];
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 life;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b386_01E02480;

static s32 func_01E02480_b386(s32 arg0, Fx_b386_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 t;

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->kind = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xCF, 0xCF, 0x40);
        o->f5A = 70;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->side = 2;
        } else {
            o->side = 0;
        }
        o->fC = o->f50;
        o->f50 = 0;
        o->life = func_0019A5C8() % 350 + 100;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->vel[0] /= 60.0f;
        o->vel[1] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    t = o->tick;
    if (t != 0) {
        if ((s16)t >= o->hold) {
            o->y += 0.5f;
        }
        if (o->tick < o->hold) {
            o->f48 += 0.8f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b386:01E02750 (b386), 524 insns, 1 copy: the module main: sets up the scene and jitter table, else steps the
   400 effect slots and draws the five effect kinds (three bobbing on the sine table), counts down and returns the
   next step by frame (100, 265, 111..259) or 8 when the countdown runs out */

typedef struct {
    u8 pad0[0xA];
    s16 h0A;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b386_01E02750;

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
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b386_01E02750 fx[400];
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
    u8 padB360[0x100];
    u8 crd[0x170];
} Scene_b386_01E02750;

static s32 func_01E02750_b386(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F9AD0(s32);
    extern s32 func_001F9D30(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_01E013E0_b386();
    extern void func_01E00920_b386();
    Scene_b386_01E02750 *g = (Scene_b386_01E02750 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    s32 i;
    s16 k;

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
        g->count = 275;
        g->jA = func_001F5560(func_001F53A0(), 0xA, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
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
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E013E0_b386(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E016B0_b386) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 1;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->py -= 40.0f * func_00108030(g->crd, 0x46, 0);
                g->py += 40.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                g->hBE = 0;
                func_01E00920_b386(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01AC0_b386) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex[1];
                g->hB8 = 6;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00E90_b386((void *)g, (void *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D10_b386) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hC0 = 5;
                g->tex88 = g->tex[1];
                g->hB8 = 2;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->py -= 40.0f * func_00108030(g->crd, 0x46, 0);
                g->py += 40.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                g->hBE = 0;
                func_01E00920_b386(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02110_b386) {
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hC0 = 5;
                g->tex88 = g->tex[1];
                g->hB8 = 2;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hBE = 0;
                func_01E00920_b386(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02480_b386) {
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 1;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->py -= 40.0f * func_00108030(g->crd, 0x46, 0);
                g->py += 40.0f * func_00108030(g->crd, g->fx[k].h5A, 0);
                g->hBE = 0;
                func_01E00920_b386(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 100) {
        return 1;
    }
    if (g->frame == 265) {
        return 3;
    }
    if (g->frame > 110 && g->frame < 260) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b038:01E01E10, 98 insns, 8 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b038_01E01E10 {
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
} Slot_b038_01E01E10;

typedef struct Obj_b038_01E01E10 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b038_01E01E10 slots[0x190];
    u8 padB[0xb1f4 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb256 - 0xb1f4 - 4];
    s16 fB2B0;
} Obj_b038_01E01E10;

static s32 func_01E02F80_b386(Obj_b038_01E01E10 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b038_01E01E10 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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
