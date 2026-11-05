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

static void func_01E00080_b094(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E00920_b094(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
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
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
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

static void func_01E00C80_b094(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b094((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b094((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b094:01E01230, 206 insns: b016:01E00ED0 with the view's y column raised by cam h + cam 0x34, then
   func_00109100(view, {cam 0x5C, 0x5A, 0x5C}, 2 and 0, obj 0xD8); draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b094 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b094_01E01230 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x22];
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    Vec4f at;
} Cam_b094_01E01230;

typedef struct Obj_b094_01E01230 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b094_01E01230;

typedef struct Xyz_b094_01E01230 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b094_01E01230;

typedef struct Uv_b094_01E01230 {
    f32 u, v;
} Uv_b094_01E01230;

typedef struct Pk_b094_01E01230 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b094_01E01230 uv;
    u64 pad18;
    Xyz_b094_01E01230 v[4];
    u64 pad60[6];
} Pk_b094_01E01230;

typedef struct Buf_b094_01E01230 {
    u64 tag;
    Pk_b094_01E01230 pk;
} Buf_b094_01E01230;

static void func_01E01230_b094(Obj_b094_01E01230 *obj, Cam_b094_01E01230 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b094_01E01230 buf;
    Uv_b094_01E01230 uv;
    s32 sel;
    s32 k;
    s32 mode;
    Pk_b094_01E01230 *p = &buf.pk;

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
    func_01E00080_b094((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    for (k = 0; k < 4; k++) {
        view[k][1] += cam->h + cam->f34;
    }
    arg[0] = cam->f5C;
    arg[1] = cam->f5A;
    arg[2] = cam->f5C;
    func_00109100(view, arg, 2, obj->fD8);
    func_00109100(view, arg, 0, obj->fD8);
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

/* shape b094:01E01570, 225 insns: the effect scene's step: counts the frame (0x4564); frames 100..200 drift the base
   point's depth by a hundredth of the gap between the camera's two points and turn the sway angle (0x4552) by 8,
   the sway width (0x44D4) shrinking from frame 170 and cleared at 200; the current point is the base swayed by
   width * sin; frame 1 puts the scene point on joint 0x44F0 and the base on joint 0x44F2 at height 26, then spawns
   0x1E01900, 0x1E02290 and 0x1E02480 (selector 0) and, from the current point, 0x1E02290, 0x1E02480 and 0x1E027F0
   (selector 1); frames 203..213 spawn 0x1E01AF0 at a random spot within 20 of it; from frame 66 0x4556 grows by 20
   up to 360 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4480 - 0x260];
    Vec4f cur;
    Vec4f base;
    u8 pad44A0[0x44D4 - 0x44A0];
    f32 amp;
    u8 pad44D8[0x44F0 - 0x44D8];
    s16 ja;
    s16 jb;
    u8 pad44F4[0x4500 - 0x44F4];
    s16 jc;
    u8 pad4502[0x4552 - 0x4502];
    s16 ang;
    u8 pad4554[2];
    s16 h4556;
    u8 pad4558[4];
    s16 sel;
    u8 pad455E[6];
    s16 t;
    u8 pad4566[0x4768 - 0x4566];
    u8 tab[4];
} Scene_b094_01E01570;

static void func_01E01570_b094(Scene_b094_01E01570 *g) {
    extern void b094_01E01900(void);
    extern void b094_01E01AF0(void);
    extern void b094_01E02290(void);
    extern void b094_01E02480(void);
    extern void b094_01E027F0(void);
    extern void b094_01E02FC0(Scene_b094_01E01570 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    Vec4f v[2];
    s16 i;

    g->t++;
    if (g->t >= 100 && g->t <= 200) {
        func_001F5F90(func_001F5380(), &v[0]);
        func_001F5F90(func_001F53A0(), &v[1]);
        func_001F5620(func_001F5380(), g->jc, &v[0]);
        g->base.z += (v[0].z - v[1].z) / 100.0f;
        g->ang += 8;
        if (g->ang >= 360) {
            g->ang %= 360;
        }
        if (g->t >= 170) {
            if (g->amp > 0.0f) {
                g->amp -= 1.0f;
            }
        }
        if (g->t == 200) {
            g->amp = 0.0f;
        }
    }
    g->cur = g->base;
    g->cur.x += g->amp * func_00108030(g->tab, g->ang, 0);
    if (g->t == 1) {
        func_001F5620(func_001F53A0(), g->ja, &g->pos);
        func_001F5620(func_001F53A0(), g->jb, &g->base);
        g->base.y = 26.0f;
        g->cur = g->base;
        b094_01E02FC0(g, b094_01E01900, 0);
        g->sel = 0;
        b094_01E02FC0(g, b094_01E02290, 0);
        b094_01E02FC0(g, b094_01E02480, 0);
        g->pos = g->cur;
        g->sel = 1;
        b094_01E02FC0(g, b094_01E02290, 0);
        b094_01E02FC0(g, b094_01E02480, 0);
        b094_01E02FC0(g, b094_01E027F0, 0);
    }
    if (g->t >= 203 && g->t <= 213) {
        for (i = 0; i < 1; i++) {
            g->pos = g->cur;
            g->pos.x += (f32)(func_0019A5C8() % 40 - 20);
            g->pos.z += (f32)(func_0019A5C8() % 40 - 20);
            b094_01E02FC0(g, b094_01E01AF0, 0);
        }
    }
    if (g->t >= 66) {
        if (g->h4556 <= 359) {
            g->h4556 += 20;
        }
    }
}

/* shape b094:01E01900, 124 insns: a flashing pair (size 20/13, frame 0..6, f8 4..6): both alphas rise by 12 to 0x80 for 20 ticks, then fall by 6 while the scene timer is under 30; colour flips 0x80/0xC0 every tick; f24 0x8000 (0 when the scene flag is set) until the scene count reaches 150, then grows 0x100 */

typedef struct {
    u8 pad0[0x44C0];
    s32 timer;
    u8 pad44C4[0x4560 - 0x44C4];
    s16 flag;
    u8 pad4562[2];
    s16 count;
} Ctx_b094_01E01900;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1A];
    s32 f24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b094_01E01900;

static s32 func_01E01900_b094(Ctx_b094_01E01900 *g, Fx_b094_01E01900 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 7.0f;
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (g->timer < 30) {
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 7) {
            o->col2[3] -= 6;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    if (g->count < 150) {
        if (g->flag != 0) {
            o->f24 = 0;
        } else {
            o->f24 = 0x8000;
        }
    } else {
        o->f24 += 0x100;
    }
    o->tick++;
    return 0;
}

/* shape b094:01E01AF0, 323 insns: a white falling star of the b094 scene: on start 20 x 0x98, 1000 up, random heading
   and tilt -15..14; fades in for 3 ticks, drops 80 a tick until it lands, then (late in the scene, step past 240)
   fades out; on landing tick 16 it spawns an impact (026F0) and two jittered bursts (020E0), on tick 12 a puff at the
   model's joint (02000), on tick 10 a streak (025F0 via 03100) along its heading */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    s32 r260;
    s32 r264;
    u8 pad268[0x4500 - 0x268];
    s16 joint;
    u8 pad4502[0x62];
    s16 step;
    u8 pad4566[0x202];
    u8 table[1];
} Scene_b094_01E01AF0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f v;
    s32 rot[4];
    u8 pad30[4];
    f32 dist;
    u8 pad38[0x1C];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    s16 tilt;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Star_b094_01E01AF0;

static s32 func_01E02000_b094();
static s32 func_01E020E0_b094();
static s32 func_01E025F0_b094();
static s32 func_01E026F0_b094();
static s32 func_01E02FC0_b094();
static s32 func_01E03100_b094();

static s32 func_01E01AF0_b094(Scene_b094_01E01AF0 *g, Star_b094_01E01AF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00205C40();
    extern void func_00108950(void *, void *, s32, void *);
    Vec4f v;
    s32 r[4];
    s32 rr[4];
    s16 i;

    if (o->state == 1) {
        o->w = 20;
        o->h = 0x98;
        o->dist = 1000.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->c1[3] = 0;
        o->ang = func_0019A5C8() % 360;
        o->tilt = func_0019A5C8() % 30 - 15;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    }
    if (o->t != 0) {
        if (o->dist > 0.0f) {
            o->dist -= 80.0f;
        } else if (g->step > 0xF0) {
            if (o->c0[3] > 10) {
                o->c0[3] -= 9;
            } else {
                o->state = 0;
            }
            if (o->c0[3] > 10) {
                o->c0[3] -= 9;
            }
        }
    }
    if (o->t == 16) {
        g->pos = o->v;
        func_01E02FC0_b094(g, func_01E026F0_b094, 0);
        for (i = 0; i < 2; i++) {
            g->pos = o->v;
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.z += func_0019A5C8() % 20 - 10;
            func_01E02FC0_b094(g, func_01E020E0_b094, 0);
        }
    }
    if (o->t == 12) {
        for (i = 0; i < 1; i++) {
            func_001F5620(func_001F5380(), g->joint, &g->pos);
            g->pos.x += func_0019A5C8() % 30 - 15;
            g->pos.z += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            func_01E02FC0_b094(g, func_01E02000_b094, 0);
        }
    }
    if (o->t == 10) {
        g->pos = o->v;
        v.y = o->dist / 10.0f;
        v.x = 0.0f;
        v.z = 0.0f;
        r[0] = o->tilt;
        r[1] = o->ang;
        r[2] = o->tilt;
        func_00205C40(rr);
        r[1] -= rr[1] / 180;
        func_00108950(&v, r, 2, g->table);
        func_00108950(&v, r, 0, g->table);
        g->pos.x += v.x;
        g->pos.y += v.y;
        g->pos.z += v.z;
        g->r264 = o->ang * -180;
        g->r260 = o->tilt * -180;
        func_01E03100_b094(g, func_01E025F0_b094, 0);
    }
    func_00205C40(o->rot);
    o->rot[0] = 0;
    o->t++;
    return 0;
}

/* shape b094:01E02000, 54 insns: a red spinning flash: set up once (scale 80, colours pink and white, size 15x15),
   full alpha for 2 frames, then fades out by 14; turns a quarter each frame after a random turn */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 scale;
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
} Obj_b094_01E02000;

static s32 func_01E02000_b094(void *arg0, Obj_b094_01E02000 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 80.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b094:01E020E0, 107 insns: b282:01E01C20 family spinning white spark (random size 5..19, frame 0..7, angle 5..34, spin 6..20, held 3..11 ticks): in by 64 up to 0xC0, then out by 16 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b094_01E020E0;

static s32 func_01E020E0_b094(s32 arg0, Obj_b094_01E020E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 15 + 5;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h50 = func_0019A5C8() % 30 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 15 + 6;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 9 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x11) {
        o->col[3] -= 0x10;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b094:01E02290, 124 insns: a blinking red-white glow sized by the model's motion: alpha up by 12 to 0x80 for 10 frames,
   then while the game state is below 30 down by 9 until it ends; the colour blinks bright/dim on odd/even frames; kind 1
   follows the model joint at height 26 once the game timer passes 100; size 10 times the model's speed, 80 to 220 */

typedef struct {
    u8 pad0[0x44C0];
    s32 state;
    u8 pad44C4[0x2C];
    s16 joint;
    u8 pad44F2[0x72];
    s16 timer;
} Game_b094_01E02290;

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    u8 pad18[0x1C];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b094_01E02290;

static s32 func_01E02290_b094(Game_b094_01E02290 *g, Obj_b094_01E02290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001F5860(s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->w = 0xF;
        o->h = 0xF;
        o->f34 = 1300.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (g->state < 0x1E) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0x80, 0x40, 0x40);
    }
    if (o->kind == 1) {
        if (g->timer > 0x64) {
            func_001F5620(func_001F53A0(), g->joint, &o->x);
            o->y = 26.0f;
        }
    }
    o->f48 = 180.0f;
    o->f4C = 0.0f;
    o->f48 = 10.0f * func_001F5860(func_001F5380());
    if (!(o->f48 <= 220.0f)) {
        o->f48 = 220.0f;
    }
    if (o->f48 < 80.0f) {
        o->f48 = 80.0f;
    }
    o->t++;
    return 0;
}

/* shape b094:01E02480, 91 insns: a red-white glow sized by the model's motion: alpha up by 12 to 0x80 for 10 frames, then while the
   game state is below 30 down by 9 until it ends; kind 1 follows the model joint at height 26 once the game timer passes 100;
   size 10 times the model's speed, at most 200 */

typedef struct {
    u8 pad0[0x44C0];
    s32 state;
    u8 pad44C4[0x2C];
    s16 joint;
    u8 pad44F2[0x72];
    s16 timer;
} Game_b094_01E02480;

typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    u8 pad18[0x30];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b094_01E02480;

static s32 func_01E02480_b094(Game_b094_01E02480 *g, Obj_b094_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001F5860(s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (g->state < 0x1E) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->kind == 1) {
        if (g->timer > 0x64) {
            func_001F5620(func_001F53A0(), g->joint, &o->x);
            o->y = 26.0f;
        }
    }
    o->f48 = 180.0f;
    o->f4C = 0.0f;
    o->f48 = 10.0f * func_001F5860(func_001F5380());
    if (!(o->f48 <= 200.0f)) {
        o->f48 = 200.0f;
    }
    o->t++;
    return 0;
}

/* shape b094:01E025F0, 63 insns: a blue/white beam growing from 20: front +25 a tick, tail 20 behind; alpha 0x80 for 2 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    s32 w24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b094_01E025F0;

static s32 func_01E025F0_b094(s32 arg0, Obj_b094_01E025F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += 25.0f;
    o->f4C = o->f48 - 20.0f;
    o->t++;
    return 0;
}

/* shape b094:01E026F0, 63 insns: a blue/white beam growing from 20: front +15 a tick, tail 50 behind; alpha 0x80 for 5 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    s32 w24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b094_01E026F0;

static s32 func_01E026F0_b094(s32 arg0, Obj_b094_01E026F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 5) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f48 += 15.0f;
    o->f4C = o->f48 - 50.0f;
    o->t++;
    return 0;
}

/* shape b094:01E027F0, 49 insns: b718:01E03D10 family: volume eased by 10 toward 0x50 once the scene state passes 30, else toward 0x80; full volume and the end at state 3 */

typedef struct {
    u8 pad[0x44C0];
    s32 state;
} Game_b094_01E027F0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b094_01E027F0;

static s32 func_01E027F0_b094(Game_b094_01E027F0 *g, Fade_b094_01E027F0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x50) {
            o->vol -= 10;
        } else {
            o->vol = 0x50;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b094:01E028C0 (b094), 448 insns, 1 copy: the b094 scene manager in b276:01E01760's form: code >= 0 sets up (3
   textures, 0.1 scale, jitter tables, 30 sway, 30 random s16s), else step, run 150 slots of 0x70 and draw them by
   handler; returns 1/3/6/8 by frame and count */

typedef struct Fx_b094_01E028C0 {
    u8 pad0[0x10];
    Vec_b094_01E00920 pos;
    u8 pad20[0x24];
    void *fn;
    u8 pad48[8];
    s16 sel;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b094_01E028C0;

typedef struct Scene_b094_01E028C0 {
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
        s16 h[4];
    } c94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x1D8];
    Fx_b094_01E028C0 fx[150];
    u8 pad4450[0x30];
    Vec_b094_01E00920 cur;
    u8 pad4490[0x10];
    s32 tex[3];
    u8 pad44AC[0x14];
    s32 count;
    u8 pad44C4[8];
    s32 ot;
    u8 pad44D0[4];
    f32 amp;
    u8 pad44D8[0x18];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 pad44F6[0xA];
    s16 cam;
    u8 pad4502[0xE];
    s16 h4510[30];
    u8 pad454C[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad4766[2];
    u8 crd[0x178];
} Scene_b094_01E028C0;

static s32 func_01E028C0_b094(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01570_b094();
    extern void b094_01E03260();
    extern void b094_01E03570();
    Scene_b094_01E028C0 *g = (Scene_b094_01E028C0 *)arg0;
    s32 n;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x48E0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 254;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 2, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (; n < 3; n++) {
            g->tex[n] = func_00202BF0(5, n);
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
            g->jit[i] = 0;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        g->amp = 30.0f;
        for (i = 0; i < 30; i++) {
            g->h4510[i] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E01570_b094(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                ((void (*)(void *, void *))g->fx[i].fn)(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01900_b094) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->c94.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                b094_01E03260(g, &g->fx[i], 0x20, &g->cur);
            }
            if (g->fx[i].fn == func_01E01AF0_b094) {
                g->tex88 = g->tex[1];
                g->c94.h[0] = 1;
                g->c94.h[1] = 1;
                g->c94.h[2] = 0xFF;
                g->c94.h[3] = 0x3F;
                g->hBE = 5;
                c.x = g->fx[i].pos.x;
                c.y = g->fx[i].pos.y;
                c.z = g->fx[i].pos.z;
                func_01E01230_b094((void *)g, (void *)&g->fx[i], 0x11, c);
            }
            if (g->fx[i].fn == func_01E02000_b094) {
                g->hB8 = 0x18;
                func_01E00920_b094((void *)g, (void *)&g->fx[i], 0x20, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E020E0_b094) {
                g->tex88 = g->tex[2];
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->c94.rm = *(Vec4f *)rm2;
                g->hB8 = 5;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00C80_b094((void *)g, (void *)&g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E02290_b094) {
                g->hB8 = 0x18;
                if (g->frame < 150) {
                    if (g->fx[i].sel == 0) {
                        b094_01E03570(g, &g->fx[i], 0x21, &g->cur);
                    }
                    if (g->fx[i].sel == 1) {
                        b094_01E03570(g, &g->fx[i], 0x21, &g->fx[i].pos);
                    }
                } else {
                    if (g->fx[i].sel == 0) {
                        b094_01E03570(g, &g->fx[i], 0x20, &g->cur);
                    }
                    if (g->fx[i].sel == 1) {
                        b094_01E03570(g, &g->fx[i], 0x20, &g->fx[i].pos);
                    }
                }
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E02480_b094) {
                g->hB8 = 0x18;
                if (g->fx[i].sel == 0) {
                    func_01E00920_b094((void *)g, (void *)&g->fx[i], 0x20, &g->cur);
                }
                if (g->fx[i].sel == 1) {
                    func_01E00920_b094((void *)g, (void *)&g->fx[i], 0x20, &g->fx[i].pos);
                }
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E025F0_b094) {
                g->hB8 = 0x18;
                func_01E00920_b094((void *)g, (void *)&g->fx[i], 0x20, &g->fx[i].pos);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E026F0_b094) {
                g->hB8 = 0x18;
                func_01E00920_b094((void *)g, (void *)&g->fx[i], 0x20, &g->fx[i].pos);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 200) {
        return 1;
    }
    if (g->frame == 240) {
        return 3;
    }
    if (g->frame > 210 && g->frame < 235) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b094:01E02FC0, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b094_01E02FC0 {
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
} Slot_b094_01E02FC0;

typedef struct Obj_b094_01E02FC0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x54];
    Slot_b094_01E02FC0 slots[0x96];
    u8 padB[0x74];
    u8 rgba[4];
    u8 padC[0x94];
    s16 fB2B0;
} Obj_b094_01E02FC0;

static s32 func_01E02FC0_b094(Obj_b094_01E02FC0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b094_01E02FC0 *s = NULL;
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

/* shape b094:01E03100, 88 insns: take a free effect slot (0x96 of 0x70 bytes at 0x2B0), clear it, colour both colours from
   the scene colour 0x44C4, attach it to the scene position (0x250) and copy it, the scene vector 0x260 into 0x20, 0x50 from 0x455C, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    f32 x, y, z, w;
} V4_b094_01E03100;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[4];
    V4_b094_01E03100 v20;
    u8 pad30[0x10];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b094_01E03100;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[4];
    V4_b094_01E03100 v260;
    u8 pad270[0x40];
    Slot_b094_01E03100 slots[0x96];
    u8 pad4450[0x44C4 - 0x4450];
    u8 rgba[4];
    u8 pad44C8[0x94];
    s16 f455C;
} Scene_b094_01E03100;

static s32 func_01E03100_b094(Scene_b094_01E03100 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b094_01E03100 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->v20 = g->v260;
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f50 = g->f455C;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b094:01E03260, 196 insns: c063:01E05840 cousin without the scale, only the sectors below the scene's limit (0x4556) are drawn; b756:01E061D0 family burst draw: two-colour packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles o->ang + 20 i - 200 between radii f4C and f48, each with its frame from the scene table through func_00106080 into the rect, depth-tested into the scene ot */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b094_01E03260;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x44CC - 0xC0];
    s32 ot;
    u8 pad44D0[0x4510 - 0x44D0];
    s16 frames[18];
    u8 pad4534[0x4556 - 0x4534];
    s16 lim;
    u8 pad4558[0x4768 - 0x4558];
    u8 trig[1];
} Game_b094_01E03260;

static void func_01E03260_b094(Game_b094_01E03260 *g, Obj_b094_01E03260 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];

    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 a;
    void *p = &buf;
    s16 s;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;
    s32 t;

    *(Vec4f *)pos = *in;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    for (i = 0; i < 18; i++) {
        if (a < g->lim) {
            func_00106080(rm, 0x14, g->frames[i], 0);
            g->rect = *(Vec4f *)rm;
            func_00108500(p, &g->rect, g->frame);
            s = o->ang + a - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[2].x = c * r1;
            q[2].z = sn * r1;
            q[0].x = c * r0;
            q[0].z = sn * r0;
            t = o->ang + 20;
            s = a + t - 200;
            c = func_00108030(g->trig, s, 1);
            sn = func_00108030(g->trig, s, 0);
            q[3].x = c * r1;
            q[3].z = sn * r1;
            q[1].x = c * r0;
            q[1].z = sn * r0;
            if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->ot, (u32)depth[0]);
            }
            a += 20;
        }
    }
}

/* shape b094:01E03570, 224 insns: b016:01E01190's ring band placed at (0, c.y, c.z) with its inner edge (quads 0
   and 1) pushed out by 10 * c.x */

typedef struct {
    f32 x, y, z, w;
} Vec_b094_01E03570;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E03570;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E03570 rotation;
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
} Data_b094_01E03570;

static void func_01E03570_b094(Obj_b094_01E03570 *obj, Data_b094_01E03570 *data, s32 flags, Vec_b094_01E03570 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E03570 c;
    Vec_b094_01E03570 quad[4];
    Vec_b094_01E03570 pos;
    Vec_b094_01E03570 scale;
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
    f32 off;

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
    pos.x = 0.0f;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = data->height;
    quad[3].y = data->height;
    off = 10.0f * c.x;
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
        quad[0].x += off;
        quad[1].x += off;
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
