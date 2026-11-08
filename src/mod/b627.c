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

static void func_01E00080_b627(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00920_b627(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b627((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b627((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b627 in the
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

static void func_01E00ED0_b627(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b627((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01190_b627(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b627:01E014F0, 207 insns: the b627 module's event step: counts ticks (0x45A2); before 70 the point (0x4470)
   follows joint 0x4544 raised by 3; at 70 takes a z step of 1/50 of the way to joint 0x4554 of the camera model; until
   120 walks z by that step (at 100 drops 30 * sin(0x456E), after 100 rises by 0x4494 and turns by 5); then the point is
   re-read from joint 0x4544, copied to 0x4480 and the spawn point; spawns b627:01E01DB0 and b627:01E01830 at 1,
   b627:01E01C40 and b627:01E01A30 (and from 70 b627:01E01F40) before 331; at 328 a burst of 36 b627:01E02060 (angles
   0, 10, ...), 15 b627:01E02210, 20 b627:01E02480, b627:01E02380 and b627:01E02640 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Vec4f a;
    Vec4f b;
    u8 pad4490[4];
    f32 rise;
    f32 step;
    u8 pad449C[0x4544 - 0x449C];
    s16 id0;
    u8 pad4546[0x4554 - 0x4546];
    s16 id1;
    u8 pad4556[0x456E - 0x4556];
    s16 ang;
    u8 pad4570[0x459A - 0x4570];
    s16 fan;
    u8 pad459C[0x45A2 - 0x459C];
    s16 timer;
    u8 pad45A4[0x47A4 - 0x45A4];
    u8 trig[4];
} Ctx_b627_01E014F0;

static void func_01E014F0_b627(Ctx_b627_01E014F0 *g) {
    extern s32 b627_01E01830(void);
    extern s32 b627_01E01A30(void);
    extern s32 b627_01E01C40(void);
    extern s32 b627_01E01DB0(void);
    extern s32 b627_01E01F40(void);
    extern s32 b627_01E02060(void);
    extern s32 b627_01E02210(void);
    extern s32 b627_01E02380(void);
    extern s32 b627_01E02480(void);
    extern s32 b627_01E02640(void);
    extern void b627_01E03010(Ctx_b627_01E014F0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[8];
    s16 i;
    s16 a;

    g->timer++;
    if (g->timer < 70) {
        func_001F5620(func_001F53A0(), g->id0, &g->a);
        g->a.y += 3.0f;
    } else {
        if (g->timer == 70) {
            func_001F5620(func_001F5380(), g->id1, v);
            g->step = (v[2] - g->a.z) / 50.0f;
        }
        if (g->timer < 120) {
            g->a.z += g->step;
            if (g->timer == 100) {
                g->a.y -= 30.0f * func_00108030(g->trig, g->ang, 0);
            }
            if (g->timer > 100) {
                g->a.y += g->rise;
                g->ang += 5;
            }
        }
    }
    func_001F5620(func_001F53A0(), g->id0, &g->a);
    g->b = g->a;
    if (g->timer == 1) {
        b627_01E03010(g, b627_01E01DB0, 0);
        b627_01E03010(g, b627_01E01830, 0);
    }
    g->pos = g->b;
    if (g->timer < 331) {
        b627_01E03010(g, b627_01E01C40, 0);
        b627_01E03010(g, b627_01E01A30, 0);
        if (g->timer >= 70) {
            b627_01E03010(g, b627_01E01F40, 0);
        }
    }
    if (g->timer == 328) {
        for (i = 0, a = 0; i < 36; i++) {
            g->fan = a;
            b627_01E03010(g, b627_01E02060, 0);
            a += 10;
        }
        for (i = 0; i < 15; i++) {
            b627_01E03010(g, b627_01E02210, 0);
        }
        for (i = 0; i < 20; i++) {
            b627_01E03010(g, b627_01E02480, 0);
        }
        b627_01E03010(g, b627_01E02380, 0);
        b627_01E03010(g, b627_01E02640, 0);
    }
}

/* shape b627:01E01830, 128 insns: b632:01E03450's grey flash timed by the game counter at g+0x45A2: on start size 25,
   colours 0x60; f56 toggles each tick; alpha up by 10 to 0x80 (both colours) until the counter reaches 330, then down
   by 14 until it ends; the colour blinks 0xFF / 0xAF on even/odd ticks; past 70 the size grows by 5 up to 50 */

typedef struct {
    u8 pad0[0x45A2];
    s16 count;
} Game_b627_01E01830;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b627_01E01830;

static s32 func_01E01830_b627(Game_b627_01E01830 *g, Fx_b627_01E01830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 25;
        o->fA = 25;
        o->f56 = 0;
        o->f34 = 0.0f;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x60, 0x60, 0x60);
        o->mode = 2;
        o->col2[3] = 0;
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 180 - 90;
    }
    if (o->f56 != 0) {
        o->f56 = 0;
    } else {
        o->f56 = 1;
    }
    if (g->count < 330) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 10;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xAF, 0xAF, 0xAF);
    }
    if (g->count > 70) {
        if (o->f8 < 50) {
            o->f8 += 5;
        }
        if (o->fA < 50) {
            o->fA += 5;
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b627:01E01A30, 129 insns: b627:01E02480 variant: size 2..4 while the game counter at g+0x45A2 is under 100,
   else 4..6; speed 40..99, fade-in 5..8 ticks at 0x80, then down by 15 until it ends; no rise */

typedef struct {
    u8 pad0[0x45A2];
    s16 count;
} Game_b627_01E01A30;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b627_01E01A30;

static s32 func_01E01A30_b627(Game_b627_01E01A30 *g, Obj_b627_01E01A30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (g->count < 100) {
            o->f48 = func_0019A5C8() % 3 + 2;
        } else {
            o->f48 = func_0019A5C8() % 3 + 4;
        }
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 45 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 60 + 40;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 4 + 5;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b627:01E01C40, 91 insns: a grey/red ring (height 1..20, or 2..41 once the scene value reaches 70; scale 2), held 3 ticks: in by 96 up to 0xC0, then out by 11 and ends; spun 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b627_01E01C40;

typedef struct {
    u8 pad[0x45A2];
    s16 val;
} Game_b627_01E01C40;

static s32 func_01E01C40_b627(Game_b627_01E01C40 *g, Obj_b627_01E01C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (g->val < 70) {
            o->f4C = 1.0f + func_0019A5C8() % 20;
        } else {
            o->f4C = 2.0f + func_0019A5C8() % 40;
        }
        o->f34 = 2.0f;
        o->h6 = 3;
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        func_001076F0(o->col, 0x40, 0x10, 0x10);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->h6) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b627:01E01DB0, 99 insns: a white-red flicker flash (b406:01E027F0 shape): size 40 growing by 3 to 75 once the scene
   timer passes 70; second colour flickers red; alpha up by 0x40 while the timer is under 330, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x45A2];
    s16 timer;
} Game_b627_01E01DB0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b627_01E01DB0;

static s32 func_01E01DB0_b627(Game_b627_01E01DB0 *g, Obj_b627_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 40.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->h5A = 0xF;
        o->h5C = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 8, 8);
    } else {
        func_001076F0(o->c1, 0xC0, 8, 8);
    }
    if (g->timer < 0x14A) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (g->timer > 0x46) {
        if (o->size < 75.0f) {
            o->size += 3.0f;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b627:01E01F40, 72 insns: a pink-grey growing spark: size 50, random sub-frame 2..6; both alphas up by 0x40 to 0x80
   for 3 frames, then the first down by 13 twice a frame until it ends; random turn */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    s32 h34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b627_01E01F40;

static s32 func_01E01F40_b627(void *arg0, Obj_b627_01E01F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x32;
        o->h = 0x32;
        o->sub = func_0019A5C8() % 5 + 2;
        o->h34 = 0;
        func_001076F0(o->c0, 0xFF, 0xC0, 0xC0);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        }
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b627:01E02060, 108 insns: on start 0x8/0xA = 100, variant 0..7, velocity f30/f34 = 1.5 x (sine, cosine) of the
   heading 0x50 (game table 0x47A4), both colours (0xFF, 0x80, 0x80) (second alpha 0), 0x5C = 0; both alphas grow by
   0x40 (below 0xC0) for 12 ticks, then the first fades by 14 twice a tick and ends it; after the first tick 0x8/0xA grow
   by 15; it moves by its velocity; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[0x47A4];
    u8 trig[1];
} Game_b627_01E02060;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 x;
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    f32 vx;
    f32 vy;
    u8 pad38[0x18];
    s16 heading;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b627_01E02060;

static s32 func_01E02060_b627(Game_b627_01E02060 *g, Fx_b627_01E02060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f8 = 100;
        o->fA = 100;
        o->f56 = func_0019A5C8() % 8;
        o->vx = 1.5f * func_00108030(g->trig, o->heading, 1);
        o->vy = 1.5f * func_00108030(g->trig, o->heading, 0);
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        o->f5C = 0;
    }
    if (o->tick < 12) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->tick != 0) {
        o->f8 += 15;
        o->fA += 15;
    }
    o->x += o->vx;
    o->y += o->vy;
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b627:01E02210, 92 insns: on start f48 20, f4C 220, f34 2, hold 5, colour white, second colour (0xFF, 0x80,
   0x80) with alpha 0, 0x5A = 15, 0x5C = 1, random rotation; the second alpha grows by 0x40 (below 0xC0) during the
   hold, then fades by 14 and stops; f48 grows by 6 and f4C by 10 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b627_01E02210;

static s32 func_01E02210_b627(s32 arg0, Fx_b627_01E02210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = 220.0f;
        o->f34 = 2.0f;
        o->hold = 5;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        o->f5A = 15;
        o->f5C = 1;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 0xF) {
        o->col2[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += 6.0f;
    o->f4C += 10.0f;
    o->tick++;
    return 0;
}

/* shape b627:01E02380, 64 insns: a pink-white spinning flash (b144:01E03210 family): f4C 250, f34 2, frame count 10,
   size 15x15; second alpha up by 0x60 to 0xC0 for that many frames, then down by 11 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b627_01E02380;

static s32 func_01E02380_b627(void *arg0, Obj_b627_01E02380 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->f4C = 250.0f;
        o->f34 = 2.0f;
        o->hold = 0xA;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xC) {
        o->c1[3] -= 0xB;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b627:01E02480, 109 insns: b574:01E02170 family: a white tumbling spark (size 10, frame 4, three random turns, angle 5..49, spin 15..44, size 0..19), alpha 0xC0 held 7..10 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b627_01E02480;

static s32 func_01E02480_b627(s32 arg0, Obj_b627_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 45 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 30 + 15;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 4 + 7;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b144:01E034D0, 153 insns, 2 copies: a full-screen zoom flash: draws one textured sprite over the whole screen, its
   texture window shrinking in by the zoom value; fades in over 10 frames while the zoom grows by 0.3 (to 100),
   then fades out while it shrinks back to 0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b144_01E034D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b144_01E034D0 p;
    } v[2];
    u8 tail[0x20];
} Pkt_b144_01E034D0;

typedef struct {
    u8 pad0[0x48];
    f32 zoom;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Flash_b144_01E034D0;

static s32 func_01E02640_b627(void *arg0, Flash_b144_01E034D0 *o) {
    extern void func_002087A0(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b144_01E034D0 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->zoom = 1.0f;
        o->state = 2;
    }
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x7F;
    pkt.b = 0x7F;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = o->zoom / 1024.0f;
    pkt.v[0].t = o->zoom / 512.0f;
    pkt.v[1].s = (640.0f - o->zoom) / 1024.0f;
    pkt.v[1].t = (448.0f - o->zoom) / 512.0f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, (s32)func_00207500(), 0);
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 0x13;
        }
        if (o->zoom < 100.0f) {
            o->zoom += 0.3f;
        }
    } else {
        if (o->c0[3] > 7) {
            o->c0[3] -= 6;
        } else {
            o->state = 0;
        }
        if (o->zoom > 0.0f) {
            o->zoom -= 0.3f;
        } else {
            o->zoom = 0.0f;
        }
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E028B0_b627(void) {
    return 0;
}

/* shape b627:01E028C0 (b627), 467 insns, 1 copy: b627 scene manager in b434:01E02570 form: setup (six joints, one
   type-4 and three type-5 textures, two 256 s8 jitter tables, angle 270), step b627:01E014F0 and every slot but the
   empty handler, draw each kind (flash and spark sprites, ring and flicker bands at 0x4480, tumbling sparks); scene
   code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b627_01E028C0;

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
    Fx_b627_01E028C0 fx[150];
    u8 pad4440[0x40];
    Vec4f pt;
    u8 pad4490[0x10];
    s32 tex[3];
    u8 pad44AC[0x14];
    s32 count;
    u8 pad44C4[8];
    s32 ot;
    u8 pad44D0[0x74];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad4550[4];
    s16 cam;
    u8 pad4556[0x18];
    s16 ang;
    u8 pad4570[0x2E];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b627_01E028C0;

static s32 func_01E028C0_b627(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E014F0_b627();
    extern void func_01E01190_b627();
    extern void func_01E00920_b627();
    extern void func_01E00ED0_b627();
    Scene_b627_01E028C0 *g = (Scene_b627_01E028C0 *)arg0;
    s16 n;
    Vec4f p;
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
    if (id >= 0) {
        func_00195108(g, 0x4910);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 365;
        g->jA = func_001F5560(func_001F53A0(), 0x35, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
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
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        g->ang = 270;
        return 0;
    }
    func_01E014F0_b627(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E028B0_b627) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01830_b627) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->u94.uv[0] = g->fx[k].h56 << 6;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x3F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 5;
                p = g->pt;
                func_01E00ED0_b627(g, &g->fx[k], 0x21, &p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01A30_b627) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b627(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C40_b627) {
                g->hB8 = 0x18;
                func_01E01190_b627(g, &g->fx[k], 0x20, &g->pt);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01DB0_b627) {
                g->hB8 = 0x18;
                func_01E01190_b627(g, &g->fx[k], 0x20, &g->pt);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F40_b627) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hBE = 5;
                p = g->fx[k].pos;
                func_01E00ED0_b627(g, &g->fx[k], 0x21, &p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02060_b627) {
                g->tex88 = g->tex[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hBE = 5;
                p.x = g->fx[k].pos.x;
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                func_01E00ED0_b627(g, &g->fx[k], 0x10, &p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02210_b627) {
                g->hB8 = 0x18;
                func_01E01190_b627(g, &g->fx[k], 0x20, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02380_b627) {
                g->hB8 = 0x18;
                func_01E01190_b627(g, &g->fx[k], 0x21, &g->pt);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02480_b627) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b627(g, &g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 318) {
        return 1;
    }
    if (g->frame == 353) {
        return 4;
    }
    if (g->frame == 343) {
        return 2;
    }
    if (g->frame > 328 && g->frame < 338) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b627:01E03010, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b627_01E03010 {
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
} Slot_b627_01E03010;

typedef struct Obj_b627_01E03010 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b627_01E03010 slots[0x96];
    u8 padB[0x84];
    u8 rgba[4];
    u8 padC[0xD2];
    s16 fB2B0;
} Obj_b627_01E03010;

static s32 func_01E03010_b627(Obj_b627_01E03010 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b627_01E03010 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
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
