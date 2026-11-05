#include "common.h"

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00080_b521(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b521 in the
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

static void func_01E004D0_b521(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b521((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00790_b521(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b521_01E00080();
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
    b521_01E00080(p, obj->f94, obj->fC0);
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

/* shape b521:01E00CE0, 248 insns: the scene script of b521: scene colour red 0x80, counts ctx+0x5536; on tick 1 it
   spawns b521:01E01970, takes the camera point (ctx+0x5470), keeps a point 25 below it (ctx+0x5460) and the depth step
   between the two views / 50 (ctx+0x5488); on tick 64 it lays 10 orbit points (ctx+0x53C0) at heights -30 + 17 i,
   radius 3 (the first 0), random angles, dims the colour to 0x20 and spawns b521:01E010C0 at (0, 30, 0); from tick
   170 to 220 the point moves along z by the step; every tick the orbit points turn 4; from tick 64 to 320 it spawns
   b521:01E01440 and b521:01E01790 at the point; the model angle (/180, less 180) goes to ctx+0x5528 */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x53C0 - 0x25C];
    Vec4f pt[10];
    f32 qx, qy, qz;
    u8 pad546C[4];
    f32 cam[4];
    u8 pad5480[8];
    f32 step;
    u8 pad548C[0x54B4 - 0x548C];
    u8 col[4];
    u8 pad54B8[0xC];
    f32 r[10];
    u8 pad54EC[4];
    s32 w54F0;
    u8 pad54F4[0x10];
    s16 ang[10];
    u8 pad5518[2];
    s16 joint;
    u8 pad551C[0xC];
    s16 h5528;
    u8 pad552A[2];
    s16 h552C;
    s16 h552E;
    u8 pad5530[2];
    s16 h5532;
    u8 pad5534[2];
    s16 t;
    u8 pad5538[0x5638 - 0x5538];
    u8 trig[1];
} Ctx_b521_01E00CE0;

static void func_01E00CE0_b521(Ctx_b521_01E00CE0 *g) {
    extern void b521_01E010C0();
    extern void b521_01E01440();
    extern void b521_01E01790();
    extern void b521_01E01970();
    extern void b521_01E02050(Ctx_b521_01E00CE0 *, void *, s32);
    extern void b521_01E021C0(Ctx_b521_01E00CE0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A22C0(f32);
    f32 v[4];
    f32 a[4];
    f32 b[4];
    s32 iv[4];
    s32 i;
    s32 h;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 1) {
        b521_01E021C0(g, b521_01E01970, 0);
    }
    if (g->t == 64) {
        for (i = 0, h = -30; i < 10; i++) {
            g->pt[i].y = h;
            h += 17;
        }
        g->r[0] = 0.0f;
        for (i = 1; i < 10; i++) {
            g->r[i] = 3.0f;
        }
        for (i = 0; i < 10; i++) {
            g->ang[i] = func_0019A5C8() % 360;
        }
        g->col[0] = 0x20;
        g->col[1] = 0x20;
        g->col[2] = 0x20;
        g->px = 0.0f;
        g->py = 30.0f;
        g->pz = 0.0f;
        for (i = 0; i < 1; i++) {
            g->h552E = 1;
            g->w54F0 = 0;
            g->h5532 = 1;
            g->h552C = 0;
            b521_01E02050(g, b521_01E010C0, 0);
        }
    }
    if (g->t == 1) {
        func_001F5F90(func_001F53A0(), g->cam);
        g->qx = g->cam[0];
        g->qy = g->cam[1] - 25.0f;
        g->qz = g->cam[2];
        func_001F5F90(func_001F53A0(), a);
        func_001F5F90(func_001F5380(), b);
        g->step = (b[2] - a[2]) / 50.0f;
    }
    if (g->t >= 170 && g->t < 221) {
        g->qz += g->step;
    }
    func_001F5620(func_001F5380(), g->joint, v);
    for (i = 0; i < 10; i++) {
        if (i != 0) {
            g->pt[i].x = g->r[i] * func_00108030(g->trig, g->ang[i], 1);
            g->pt[i].z = g->r[i] * func_00108030(g->trig, g->ang[i], 0);
        } else {
            g->pt[i].x = g->r[i] * func_00108030(g->trig, g->ang[i], 1);
            g->pt[i].z = g->r[i] * func_00108030(g->trig, g->ang[i], 0);
        }
        g->ang[i] += 4;
        if (g->ang[i] >= 360) {
            g->ang[i] %= 360;
        }
    }
    func_001F6160(func_001F53A0(), iv);
    g->h5528 = func_001A22C0(iv[1] / 180.0f);
    g->h5528 -= 180;
    if (g->t >= 64 && g->t < 321) {
        g->px = g->qx;
        g->py = g->qy;
        g->pz = g->qz;
        b521_01E021C0(g, b521_01E01440, 0);
        g->px = g->qx;
        g->py = g->qy;
        g->pz = g->qz;
        b521_01E021C0(g, b521_01E01790, 0);
    }
}

/* shape b521:01E010C0, 223 insns: a rising pair (lead 0x4, tail 0x14) in grey 0x48: fades in by 10 below 50, out by
   14 above; finds the first scene path point (ctx+0x53C0, 8 of them) above the lead and fits two frames to that
   path segment (func_001098E0 into 0x40 and 0x50), growing 0x8A by 7 / 0x8C by 6 up to 20 / 19 per point; the lead
   climbs 4 a tick to 80 with the tail within 18, then the tail alone until it passes the lead (frees its link,
   stops); while state 1 and above 0 it hands itself to the scene and, from scene stage 31 on, starts the module's
   b521:01E02050 (state 2 once it takes) */

typedef struct Link_b521_01E010C0 {
    u8 pad0[0x70];
    s32 f70;
} Link_b521_01E010C0;

typedef struct Obj_b521_01E010C0 {
    u8 pad0[4];
    f32 lead;
    u8 pad8[0xC];
    f32 tail;
    u8 pad18[0x18];
    s32 f30;
    s32 f34;
    s32 f38;
    u8 pad3C[4];
    Vec4f fa;
    Vec4f fb;
    u8 pad60[0x14];
    Link_b521_01E010C0 *link;
    u8 pad78[8];
    u8 col0[4];
    u8 col1[4];
    s16 state;
    s16 h8A;
    s16 h8C;
    u8 pad8E[4];
    s16 ang;
} Obj_b521_01E010C0;

typedef struct Scn_b521_01E010C0 {
    u8 pad0[0x53C0];
    Vec4f pt[8];
    u8 pad5440[0x54B0 - 0x5440];
    s32 stage;
    u8 pad54B4[0xC];
    Obj_b521_01E010C0 *cur;
    u8 pad54C4[0x28];
    f32 f54EC;
    f32 f54F0;
    u8 pad54F4[0x38];
    s16 f552C;
    s16 f552E;
    u8 pad5530[2];
    s16 f5532;
} Scn_b521_01E010C0;

static s32 func_01E010C0_b521(Scn_b521_01E010C0 *g, Obj_b521_01E010C0 *o) {
    extern s32 b521_01E02050(Scn_b521_01E010C0 *g, void *fn, s32 arg);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_001098E0(void *, void *, void *, void *, void *);
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    s16 i;

    v.y = 0;
    func_001076F0(o->col0, 0x48, 0x48, 0x48);
    func_001076F0(o->col1, 0x48, 0x48, 0x48);
    o->f30 = 0;
    o->f34 = 0;
    o->f38 = 0;
    if (o->lead < 50.0f) {
        if (o->col0[3] < 0x50) {
            o->col0[3] += 10;
        }
        if (o->col1[3] < 0x50) {
            o->col1[3] += 10;
        }
    } else {
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 14;
        }
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 14;
        }
    }
    for (i = 1; i < 8; i++) {
        if (g->pt[i].y > o->lead) {
            v.x = g->pt[0].x;
            v.z = g->pt[0].z;
            func_001098E0(&r1, &v, o, &g->pt[i - 1], &g->pt[i]);
            o->fa = r1;
            func_001098E0(&r2, &v, o, &g->pt[i - 1], &g->pt[i]);
            o->fb = r2;
            if (o->h8A <= i * 20) {
                o->h8A += 7;
            }
            if (o->h8C <= i * 19) {
                o->h8C += 6;
            }
            i = 8;
        }
    }
    if (o->lead <= 80.0f) {
        o->lead += 4.0f;
        if (o->lead - o->tail > 18.0f) {
            o->tail += 4.0f;
        }
    } else {
        o->tail += 4.0f;
        if (o->tail > o->lead) {
            if (o->link != NULL) {
                o->link->f70 = 0;
            }
            o->state = 0;
        }
    }
    if (o->state == 1 && o->tail > 0.0f) {
        g->f54EC = 14.0f;
        g->cur = o;
        g->f552E = 1;
        g->f54F0 = o->tail;
        g->f5532 = 1;
        g->f552C = o->ang - 15;
        if (g->stage > 30 && b521_01E02050(g, func_01E010C0_b521, 0) != 0) {
            o->state = 2;
        }
    }
    return 0;
}

/* shape b521:01E01440, 212 insns: b256:01E02A40 family: a rising spark (size 4..9 growing to 16, scale 5..104, drift /400, random spin and spin speed -2048..2047), fades in for 40 ticks, out by 9; rises 2 a frame and turns */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
    u8 padCBB6[2];
    s16 count;
} Ctx_b521_01E01440;

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
} Obj_b521_01E01440;

static s32 func_01E01440_b521(Ctx_b521_01E01440 *ctx, Obj_b521_01E01440 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->hA = func_0019A5C8() % 6 + 4;
        o->h8 = o->hA * 2;
        o->f48 = 5.0f + (func_0019A5C8() >> 4) % 100;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f34 /= 400.0f;
        o->f30 /= 400.0f;
        o->h5C = func_0019A5C8() % 20 - 10;
        o->h5A = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x1000 - 0x800;
        o->h2 = func_0019A5C8() % 0x1000 - 0x800;
        o->h0 = func_0019A5C8() % 0x1000 - 0x800;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
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
        if (o->hA < 16) {
            o->hA += 2;
        }
        o->h8 = 2.5f * o->hA;
    }
    if (o->t != 0) {
        o->y += 2.0f;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    o->h5A += o->h5C;
    return 0;
}

/* shape b521:01E01790, 120 insns, 2 copies: a pale bloom: set up once (random size 100..129, frame 0..7, angle 100..149, speed
   36..55, life 7..16); fades in for its life, then out; turns for 90 frames and grows 6 a frame for 140 (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b521_01E01790;

static s32 func_01E01790_b521(void *arg0, Spark_b521_01E01790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 100;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        o->ang = func_0019A5C8() % 50 + 100;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 36;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 10 + 7;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t < 0x5A && o->t != 0) {
        o->ang += o->speed;
    }
    if (o->t < 0x8C) {
        o->size += 6.0f;
    }
    o->t++;
    return 0;
}

/* shape b521:01E01970, 152 insns: b763:01E032F0 with a blue-grey tint (0x80/0x80/0xB0), offsets biased by 20 (as
   b721:01E03800), and the alpha driven by the scene: once the step at g+0x54B0 passes 20 it rises by 10 to 0x50 before
   scene time 216 (g+0x5536) and falls by 6 to 64 after; before that it fades by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b521_01E01970;

typedef struct {
    f32 s, t;
    Xyz_b521_01E01970 p;
} Tv_b521_01E01970;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b521_01E01970 v[2];
    u8 tail[0x20];
} Tex_b521_01E01970;

typedef struct {
    u8 pad0[0x54B0];
    s32 timer;
    u8 pad54B4[0x82];
    s16 time;
} Ctx_b521_01E01970;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b521_01E01970;

static s32 func_01E01970_b521(Ctx_b521_01E01970 *g, Fx_b521_01E01970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b521_01E01970 pk __attribute__((aligned(8)));
    f32 z;
    s32 tm;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xB0);
        o->mode = 2;
    }
    z = 20.0f;
    ((Tex_b521_01E01970 *)(s32)&pk)->flags = 0x26;
    ((Tex_b521_01E01970 *)(s32)&pk)->size = 5;
    ((Tex_b521_01E01970 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b521_01E01970 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    tm = g->time;
    if (g->timer > 20) {
        if (tm < 216) {
            if (o->col[3] < 0x50) {
                o->col[3] += 10;
            }
        }
        if (g->time > 216) {
            if (o->col[3] > 64) {
                o->col[3] -= 6;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b521", func_01E01BD0_b521);

/* shape b521:01E02050, 89 insns: b056:01E038A0 twin: take the first free trail node of 25 (0x98 bytes), copy the scene position, ids and height (minus 18 below), link it after the current head and make it the head */

typedef struct {
    f32 x, y, z, w;
} V4_b521_01E02050;

typedef struct Node_b521_01E02050 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    V4_b521_01E02050 pos;
    u8 pad40[0x30];
    struct Node_b521_01E02050 *prev;
    struct Node_b521_01E02050 *next;
    u8 pad78[0x10];
    s16 used;
    u8 pad8A[4];
    s16 f8E;
    u8 pad90[2];
    s16 f92;
    s16 f94;
    s16 f96;
} Node_b521_01E02050;

typedef struct {
    u8 pad0[0x250];
    V4_b521_01E02050 pos;
    u8 pad260[0x70];
    Node_b521_01E02050 nodes[0x19];
    u8 pad11A8[0x54C0 - 0x11A8];
    Node_b521_01E02050 *head;
    u8 pad3924[0x2C];
    f32 y;
    u8 pad3954[0x38];
    s16 f398C;
    u8 pad398E[4];
    s16 f3992;
} Scene_b521_01E02050;

static s32 func_01E02050_b521(Scene_b521_01E02050 *g) {
    extern void func_00195108();
    Node_b521_01E02050 *s = NULL;
    s16 i;

    for (i = 0; i < 0x19; i++) {
        if (g->nodes[i].used == 0) {
            func_00195108(&g->nodes[i], 0x98);
            g->nodes[i].used = 1;
            s = &g->nodes[i];
            i = 0x19;
        }
    }
    if (s != NULL) {
        s->pos = g->pos;
        s->f92 = g->f398C;
        s->prev = g->head;
        s->f8E = g->f3992;
        if (s->prev == NULL) {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        } else {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        }
        s->prev = g->head;
        if (s->prev != NULL) {
            s->prev->next = s;
        }
        s->f94 = 1;
        s->f96 = 1;
        g->head = s;
        return 1;
    }
    return 0;
}

/* shape b521:01E021C0, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x11B0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

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
} Obj_b521_01E021C0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x11b0 - 0x25C];
    Obj_b521_01E021C0 slot[150];
    u8 padEnd[0x54b4 - 0x11b0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad54B8[0x7A];
    s16 val;
} Ctx_b521_01E021C0;

static s32 func_01E021C0_b521(Ctx_b521_01E021C0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b521_01E021C0 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 150;
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
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b521:01E02310 (B521PAINT_RAIN), 446 insns, 1 copy (-O3,p): B521PAINT_RAIN: b056:01E03B40 at -O3 on its own
   scene layout, each of the four matrices drawn twice: first with the glow texture (0x5490) and a fixed rect (0, 0,
   0x1F, 0x7F), then with the texture at 0x2CC and rect 0x96 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b521_01E02310;

typedef struct {
    Rgbaq_b521_01E02310 c;
    f32 s, t;
    u64 xyz;
} Vtx_b521_01E02310;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b521_01E02310 v[4];
} Pkt_b521_01E02310;

typedef union {
    Vec4f v;
    struct {
        s16 x, y, w, h;
    } r;
} Rc_b521_01E02310;

typedef struct {
    f32 m[16];
} Mat_b521_01E02310;

typedef struct Ring_b521_01E02310 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 y2;
    u8 pad18[0x28];
    Vec4f pos;
    Vec4f rot;
    u8 pad60[0x10];
    struct Ring_b521_01E02310 *parent;
    u8 pad74[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 pad88[2];
    s16 r0;
    s16 r1;
    u8 pad8E[4];
    s16 ang;
} Ring_b521_01E02310;

typedef struct {
    u8 pad0[0x2C8];
    void *texture;
    void *tex2CC;
    u8 pad2D0[0x5460 - 0x2D0];
    Vec4f eye;
    u8 pad5470[0x5490 - 0x5470];
    void *glow;
    u8 pad5494[0x54BC - 0x5494];
    s32 ot;
    u8 pad54C0[0x54F4 - 0x54C0];
    f32 depth;
    u8 pad54F8[0x5638 - 0x54F8];
    u8 sin[4];
} Scene_b521_01E02310;

#pragma optimization_level 3

static void func_01E02310_b521(Scene_b521_01E02310 *g, Ring_b521_01E02310 *o, Pkt_b521_01E02310 *pk, s32 mode) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b521_01E02310 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern Mat_b521_01E02310 func_00108EF0(void *, s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f sc;
    Rc_b521_01E02310 c;
    Mat_b521_01E02310 m[5];
    s32 i;
    s32 j;
    Ring_b521_01E02310 *pa;
    s16 k;
    s16 a;

    pa = o->parent;
    a = 0;
    if (mode == 0) {
        func_00109270(pk, 0, 0);
        pk->v[0].c = func_00107740(o->col0);
        pk->v[1].c = func_00107740(o->col0);
        pk->v[2].c = func_00107740(o->col1);
        pk->v[3].c = func_00107740(o->col1);
        return;
    }
    sc.x = 2.0f;
    sc.y = 0.0f;
    sc.z = 2.0f;
    func_00208700(pk, g->texture, 1);
    func_00106080(&c, 0x8C, 0, &c);
    func_00108500(pk, &c, 0);
    m[0] = func_00108EF0(&sc, 0, &g->eye);
    sc.x = 1.4f;
    sc.y = 0.5f;
    sc.z = 1.4f;
    m[1] = func_00108EF0(&sc, 0, &g->eye);
    sc.x = 1.2f;
    sc.y = 1.0f;
    sc.z = 1.2f;
    m[2] = func_00108EF0(&sc, 0, &g->eye);
    sc.x = 0.8f;
    sc.y = 1.5f;
    sc.z = 0.8f;
    m[3] = func_00108EF0(&sc, 0, &g->eye);
    sc.x = 0.5f;
    sc.y = 2.0f;
    sc.z = 0.5f;
    m[4] = func_00108EF0(&sc, 0, &g->eye);
    for (i = 0; i < 12; i++) {
        if (pa != NULL) {
            k = a + pa->ang;
            q[0].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[0].z = pa->r1 * func_00108030(g->sin, k, 0);
            k = a + pa->ang - 30;
            q[1].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[1].z = pa->r1 * func_00108030(g->sin, k, 0);
            o->y = pa->y2;
            if (pa != NULL) {
                func_00107DD0(q, &pa->pos, &o->pos, 0);
            }
        } else {
            q[0].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 1);
            q[0].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 0);
            q[1].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang - 30), 1);
            q[1].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang - 30), 0);
        }
        k = a + o->ang;
        q[2].x = o->r1 * func_00108030(g->sin, k, 1);
        q[2].z = o->r1 * func_00108030(g->sin, k, 0);
        k = a + o->ang - 30;
        q[3].x = o->r1 * func_00108030(g->sin, k, 1);
        q[3].z = o->r1 * func_00108030(g->sin, k, 0);
        q[0].y = o->y;
        q[1].y = o->y;
        q[2].y = o->y2;
        q[3].y = o->y2;
        for (j = 0; j < 4; j++) {
            if (q[j].y < 0.0f) {
                q[j].y = 0.0f;
            }
        }
        func_00106FA0(q, &o->pos, 0);
        func_00107DD0(&q[2], &o->pos, &o->rot, 0);
        for (j = 0; j < 4; j++) {
            func_00208700(pk, g->glow, 1);
            c.r.x = 0;
            c.r.y = 0;
            c.r.w = 0x1F;
            c.r.h = 0x7F;
            func_00108500(pk, &c, 0);
            if (func_00205630(q, 0x70000000, &m[j], pk, &g->depth) != 0) {
                func_002075F0(pk, g->ot, (u32)g->depth);
            }
            func_00208700(pk, g->tex2CC, 1);
            func_00106080(&c, 0x96, 0, &c);
            func_00108500(pk, &c, 0);
            if (func_00205630(q, 0x70000000, &m[j], pk, &g->depth) != 0) {
                func_002075F0(pk, g->ot, (u32)g->depth);
            }
        }
        a += 30;
    }
}

#pragma optimization_level reset
