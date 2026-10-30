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

static void func_01E00080_b580(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b580 in the
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

static void func_01E004D0_b580(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b580((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00790_b580(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b580_01E00080();
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
    b580_01E00080(p, obj->f94, obj->fC0);
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

/* shape b580:01E00CE0 (B580_W_S), 359 insns, 1 copy: B580_W_S, the effect scene step: colour 0x80,0,0,0, counts the
   frame (0x80F6); frame 110 lays out ten ring points (heights -30 step 17, radii 0 then 3, random angles), colour
   0x20 and takes one ring (b580:01E01280); frame 1 puts the target 25 under the camera and the per-frame rise; frames
   170..220 raise it; every frame spins the ten points 4 degrees on the sine table and turns the angle; frames 64..320
   spawn four b580:01E01640 and one b580:01E01990 at the target */

typedef struct {
    f32 x, y, z, w;
} V4_b580_01E00CE0;

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x7F80 - 0x25C];
    V4_b580_01E00CE0 pts[10];
    f32 tx, ty, tz;
    u8 pad802C[4];
    V4_b580_01E00CE0 cam;
    u8 pad8040[8];
    f32 dz;
    u8 pad804C[0x28];
    u8 col[4];
    u8 pad8078[0xC];
    f32 rad[10];
    u8 pad80AC[4];
    s32 b0;
    u8 pad80B4[0x10];
    s16 ang[10];
    u8 pad80D8[2];
    s16 joint;
    u8 pad80DC[0xC];
    s16 rot;
    u8 pad80EA[2];
    s16 eC;
    s16 eE;
    u8 pad80F0[2];
    s16 f2;
    u8 pad80F4[2];
    s16 frame;
    u8 pad80F8[0x81F8 - 0x80F8];
    u8 sin[4];
} Ctx_b580_01E00CE0;

static void func_01E00CE0_b580(Ctx_b580_01E00CE0 *g, s32 arg) {
    extern s32 func_0019A5C8(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A22C0(f32);
    extern s32 func_01E01280_b580();
    extern s32 func_01E01640_b580();
    extern s32 func_01E01990_b580();
    extern s32 b580_01E02070();
    extern s32 b580_01E02210();
    V4_b580_01E00CE0 j;
    V4_b580_01E00CE0 a;
    V4_b580_01E00CE0 b;
    s32 r[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->frame++;
    if (g->frame == 110) {
        for (i = 0; i < 10; i++) {
            g->pts[i].y = i * 17 - 30;
        }
        g->rad[0] = 0.0f;
        for (i = 1; i < 10; i++) {
            g->rad[i] = 3.0f;
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
            g->eE = 1;
            g->b0 = 0;
            g->f2 = 1;
            g->eC = 0;
            b580_01E02070(g, func_01E01280_b580, 0);
        }
    }
    if (g->frame == 1) {
        func_001F5F90(func_001F53A0(), &g->cam);
        g->tx = g->cam.x;
        g->ty = g->cam.y - 25.0f;
        g->tz = g->cam.z;
        func_001F5F90(func_001F53A0(), &a);
        func_001F5F90(func_001F5380(), &b);
        g->dz = (b.z - a.z) / 50.0f;
    }
    if (g->frame >= 170 && g->frame <= 220) {
        g->tz += g->dz;
    }
    func_001F5620(func_001F5380(), g->joint, &j);
    for (i = 0; i < 10; i++) {
        if (i != 0) {
            g->pts[i].x = g->rad[i] * func_00108030(g->sin, g->ang[i], 1);
            g->pts[i].z = g->rad[i] * func_00108030(g->sin, g->ang[i], 0);
        } else {
            g->pts[i].x = g->rad[i] * func_00108030(g->sin, g->ang[i], 1);
            g->pts[i].z = g->rad[i] * func_00108030(g->sin, g->ang[i], 0);
        }
        g->ang[i] += 4;
        if (g->ang[i] >= 360) {
            g->ang[i] %= 360;
        }
    }
    func_001F6160(func_001F53A0(), r);
    g->rot = func_001A22C0(r[1] / 180.0f);
    g->rot -= 180;
    if (g->frame >= 64 && g->frame <= 320) {
        g->px = g->tx;
        g->py = g->ty;
        g->pz = g->tz;
        b580_01E02210(g, func_01E01640_b580, 0);
        b580_01E02210(g, func_01E01640_b580, 0);
        b580_01E02210(g, func_01E01640_b580, 0);
        b580_01E02210(g, func_01E01640_b580, 0);
        g->px = g->tx;
        g->py = g->ty;
        g->pz = g->tz;
        b580_01E02210(g, func_01E01990_b580, 0);
    }
}


/* shape b580:01E01280, 223 insns: b521:01E010C0 in grey 0xA0 with the scene block 0x2BC0 further on; a rising pair (lead 0x4, tail 0x14): fades in by 10 below 50, out by
   14 above; finds the first scene path point (ctx+0x53C0, 8 of them) above the lead and fits two frames to that
   path segment (func_001098E0 into 0x40 and 0x50), growing 0x8A by 7 / 0x8C by 6 up to 20 / 19 per point; the lead
   climbs 4 a tick to 80 with the tail within 18, then the tail alone until it passes the lead (frees its link,
   stops); while state 1 and above 0 it hands itself to the scene and, from scene stage 31 on, starts the module's
   b580:01E02070 (state 2 once it takes) */

typedef struct Link_b580_01E01280 {
    u8 pad0[0x70];
    s32 f70;
} Link_b580_01E01280;

typedef struct Obj_b580_01E01280 {
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
    Link_b580_01E01280 *link;
    u8 pad78[8];
    u8 col0[4];
    u8 col1[4];
    s16 state;
    s16 h8A;
    s16 h8C;
    u8 pad8E[4];
    s16 ang;
} Obj_b580_01E01280;

typedef struct Scn_b580_01E01280 {
    u8 pad0[0x7F80];
    Vec4f pt[8];
    u8 pad5440[0x8070 - 0x8000];
    s32 stage;
    u8 pad54B4[0xC];
    Obj_b580_01E01280 *cur;
    u8 pad54C4[0x28];
    f32 f54EC;
    f32 f54F0;
    u8 pad54F4[0x38];
    s16 f552C;
    s16 f552E;
    u8 pad5530[2];
    s16 f5532;
} Scn_b580_01E01280;

static s32 func_01E01280_b580(Scn_b580_01E01280 *g, Obj_b580_01E01280 *o) {
    extern s32 b580_01E02070(Scn_b580_01E01280 *g, void *fn, s32 arg);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_001098E0(void *, void *, void *, void *, void *);
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    s16 i;

    v.y = 0;
    func_001076F0(o->col0, 0xA0, 0xA0, 0xA0);
    func_001076F0(o->col1, 0xA0, 0xA0, 0xA0);
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
        if (g->stage > 30 && b580_01E02070(g, func_01E01280_b580, 0) != 0) {
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

static s32 func_01E01640_b580(Ctx_b521_01E01440 *ctx, Obj_b521_01E01440 *o) {
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

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b580_01E01990;

static s32 func_01E01990_b580(s32 unused, Obj_b580_01E01990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 30 + 100;
        o->h56 = func_0019A5C8() % 8;
        func_001076F0(o->c60, 0xA0, 0xA0, 0xF0);
        o->h50 = func_0019A5C8() % 50 + 100;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 36;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 10 + 7;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x2A;
        }
    } else if (o->c60[3] > 10) {
        o->c60[3] -= 9;
    } else {
        o->h58 = 0;
    }
    if (o->h54 < 90) {
        if (o->h54 != 0) {
            o->h50 += o->hE;
        }
    }
    if (o->h54 < 140) {
        o->f48 += 6.0f;
    }
    o->h54++;
    return 0;
}

/* shape b580:01E01B70, 318 insns: the scene manager of b580: on a code >= 0 it clears the scene (0x8370 bytes), sets
   up the sine tables, fetches resources and textures (group 4 cells 14-15, group 5 cells 0-3), a 378-tick timer and
   a table of 256 random -15..14 offsets (100..179 cleared); otherwise it runs the step (b580:01E00CE0), steps and
   draws the 25 rings (0x98 bytes at 0x2D0) and steps the 250 effects (0x70 bytes at 0x11B0), drawing the
   b580:01E01640 ones as sprites and the b580:01E01990 ones through b580:01E00790; it returns 1, 4, 2 or 6 on the
   scene frames 205, 360, 340 and 216..334, 8 when the timer runs out */

typedef struct {
    u8 pad0[0x88];
    s16 used;
    u8 pad8A[0xE];
} Ring_b580_01E01B70;

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[0x28];
    s32 (*fn)(void *, void *);
    f32 r;
    u8 pad4C[0xA];
    s16 cell;
    s16 used;
    s16 ang;
    u8 pad5C[0x14];
} Fx_b580_01E01B70;

typedef struct {
    s16 u, v, w, h;
} Rect_b580_01E01B70;

typedef struct {
    u8 pad0[0x20];
    f32 ox, oy, oz;
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    union {
        Vec4f v;
        Rect_b580_01E01B70 r;
    } uv;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[2];
    u8 padBC[2];
    s16 mode;
    s16 cell;
    u8 padC2[0x16];
    u8 tblD8[0x1B8];
    s32 tex[16];
    Ring_b580_01E01B70 ring[25];
    u8 pad11A8[8];
    Fx_b580_01E01B70 fx[250];
    u8 pad7F10[0x8050 - 0x7F10];
    s32 tex5[4];
    u8 pad8060[0x10];
    s32 timer;
    u8 pad8074[8];
    s32 ot2;
    u8 pad8080[0x58];
    s16 res0;
    s16 res1;
    s16 res2;
    s16 res3;
    u8 pad80E0[0x14];
    s16 code;
    s16 frame;
    s8 rnd[0x100];
    u8 sin[4];
} Ctx_b580_01E01B70;

static void func_01E004D0_b580();
static void func_01E00790_b580();
static void func_01E00CE0_b580();
static s32 func_01E01280_b580();
static s32 func_01E01640_b580();
static s32 func_01E01990_b580();
static s32 func_01E023B0_b580();

static s32 func_01E01B70_b580(s32 arg0, s32 code) {
    Ctx_b580_01E01B70 *g = (Ctx_b580_01E01B70 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern Vec4f func_00106080(s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s32 n;
    Vec4f p;
    Vec4f t0;
    Vec4f t1;
    u8 pkt[0x90];
    s32 i;

    n = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x8370);
        func_00107C10(g->sin);
        func_00107C10(g->tblD8);
        g->res0 = func_001F5560(func_001F53A0(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 4; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        g->res1 = func_001F5560(func_001F5380(), 1, 1);
        g->res2 = func_001F5560(func_001F53A0(), 0x37, 0);
        g->res3 = func_001F5560(func_001F53A0(), 0x3D, 0);
        g->code = code;
        g->timer = 378;
        for (i = 0; i < 0x100; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->rnd[i] = 0;
        }
        return 0;
    }
    func_01E00CE0_b580(g, 0);
    for (i = 0; i < 25; i++) {
        if (g->ring[i].used != 0) {
            func_01E01280_b580(g, &g->ring[i]);
        }
    }
    for (i = 0; i < 25; i++) {
        if (g->ring[i].used != 0) {
            func_01E023B0_b580(g, &g->ring[i], pkt, 0);
            func_01E023B0_b580(g, &g->ring[i], pkt, 1);
        }
    }
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 250; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01640_b580) {
                g->texture = g->tex5[1];
                t0 = func_00106080(0x14, g->fx[i].cell, 0);
                g->uv.v = t0;
                g->uv.r.u = 0;
                g->uv.r.v = 0;
                g->uv.r.w = 0x7F;
                g->uv.r.h = 0x3F;
                g->mode = 0;
                p.x = g->fx[i].x + g->fx[i].r * func_00108030(g->sin, g->fx[i].ang, 1);
                p.y = g->fx[i].y;
                p.z = g->fx[i].z + g->fx[i].r * func_00108030(g->sin, g->fx[i].ang, 0);
                func_01E004D0_b580(g, &g->fx[i], 0x10, p);
            }
            if (g->fx[i].fn == func_01E01990_b580) {
                t1 = func_00106080(0x14, g->fx[i].cell, 0);
                g->uv.v = t1;
                g->texture = g->tex5[2];
                g->count = 5;
                g->cell = g->fx[i].hA;
                g->ox = g->fx[i].x;
                g->oy = g->fx[i].y;
                g->oz = g->fx[i].z;
                func_01E00790_b580(g, &g->fx[i], 0x10, g->rnd);
                g->count = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->frame == 205) {
        return 1;
    }
    if (g->frame == 360) {
        return 4;
    }
    if (g->frame == 340) {
        return 2;
    }
    if (g->frame > 215 && g->frame < 335) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b580:01E02070, 89 insns: take a free node (0x19 of 0x98 bytes at 0x2D0), clear it, copy the scene vector
   0x250, 0x92/0x8E from 0x80EC/0x80F2, y = 0x80B0 and 0x14 = y - 18, then push it on the scene's list (0x8080,
   prev 0x70 / next 0x74) with 0x94/0x96 = 1; returns 1 if a node was found */

typedef struct {
    f32 x, y, z, w;
} V4_b580_01E02070;

typedef struct Node_b580_01E02070 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    V4_b580_01E02070 pos;
    u8 pad40[0x30];
    struct Node_b580_01E02070 *prev;
    struct Node_b580_01E02070 *next;
    u8 pad78[0x10];
    s16 used;
    u8 pad8A[4];
    s16 f8E;
    u8 pad90[2];
    s16 f92;
    s16 f94;
    s16 f96;
} Node_b580_01E02070;

typedef struct {
    u8 pad0[0x250];
    V4_b580_01E02070 pos;
    u8 pad260[0x70];
    Node_b580_01E02070 nodes[0x19];
    u8 pad11A8[0x8080 - 0x11A8];
    Node_b580_01E02070 *head;
    u8 pad3924[0x2C];
    f32 y;
    u8 pad3954[0x38];
    s16 f398C;
    u8 pad398E[4];
    s16 f3992;
} Scene_b580_01E02070;

static s32 func_01E02070_b580(Scene_b580_01E02070 *g) {
    extern void func_00195108();
    Node_b580_01E02070 *s = NULL;
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

/* shape b580:01E02210, 102 insns: takes the first free of 250 effect slots (0x70 bytes, b041:01E02C00 shape), clears and
   marks it, colours both from the scene, places it at the scene point, copies a setting twice and stores both arguments */

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
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b580_01E02210;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x11B0 - 0x260];
    Slot_b580_01E02210 slot[250];
    u8 padEnd[0x8074 - 0x11B0 - 250 * 0x70];
    u8 col[4];
    u8 pad8078[0x7A];
    s16 h80F2;
} Scene_b580_01E02210;

static s32 func_01E02210_b580(Scene_b580_01E02210 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b580_01E02210 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 250; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 250;
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
        sl->h50 = s->h80F2;
        sl->h52 = s->h80F2;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b580", func_01E023B0_b580);
