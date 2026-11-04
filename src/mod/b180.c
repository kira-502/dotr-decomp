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

static void func_01E00080_b180(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b180(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b180((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b180((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b180(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b180:01E01230, 216 insns, 3 copies: draws an arc band of count quads (outer and inner radius, start angle, step
   and spacing from the band) around a position, two colours, turned by the band's rotation; blend from flags
   >> 4, depth mode flags & 0xF (projected, or far after a packet tweak). */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b180_01E01230;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[4];
    f32 h;
    u8 pad38[0x10];
    f32 outer;
    f32 inner;
    u8 pad50[2];
    s16 start;
    u8 pad54[6];
    s16 gap;
    s16 step;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Band_b180_01E01230;

static void func_01E01230_b180(Obj_b180_01E01230 *o, Band_b180_01E01230 *s, s32 flags, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 k;
    s32 t;
    s16 b;
    s16 a;
    u8 *p;
    s16 step;
    f32 ro;
    f32 ri;

    p = pkt;
    step = s->step;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = s->h;
    quad[3].y = s->h;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < o->count; k++) {
        t = a + s->start;
        quad[0].x = ro * func_00108030(o->xD8, t, 1);
        quad[0].z = ro * func_00108030(o->xD8, t, 0);
        quad[2].x = ri * func_00108030(o->xD8, t, 1);
        quad[2].z = ri * func_00108030(o->xD8, t, 0);
        t = s->start + (step + a);
        quad[1].x = ro * func_00108030(o->xD8, t, 1);
        quad[1].z = ro * func_00108030(o->xD8, t, 0);
        quad[3].x = ri * func_00108030(o->xD8, t, 1);
        quad[3].z = ri * func_00108030(o->xD8, t, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        }
        a += s->gap;
    }
}

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E01590_b180(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
    }
}

/* shape b180:01E01760, 209 insns: the effect scene's step (b735:01E01AD0 family): counts the frame (0xB2BE); from 151 to
   199 it marks joint 0xB248 at 0xB1D0, lifts the mark 3.3 a frame and moves the scene point there; from 11 to 199 it
   spawns 0x1E01AB0 on the joint (0x1E01D00 at frame 10); at frame 1 it spawns 0x1E022E0 and 0x1E021D0; up to frame 200
   it spawns 0x1E01EB0 at the camera point jittered by -10..9; from 20 to 199, every third frame it spawns 0x1E02040
   with the side (0xB2B6) alternating by the 0xB2AC count */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f mark;
    u8 padB1E0[0xB248 - 0xB1E0];
    s16 joint;
    u8 padB24A[0x62];
    s16 count;
    u8 padB2AE[8];
    s16 side;
    u8 padB2B8[6];
    s16 t;
} Scene_b180_01E01760;

static void func_01E01760_b180(Scene_b180_01E01760 *g) {
    extern void b180_01E01AB0(void);
    extern void b180_01E01D00(void);
    extern void b180_01E01EB0(void);
    extern void b180_01E02040(void);
    extern void b180_01E021D0(void);
    extern void b180_01E022E0(void);
    extern s32 b180_01E02C80(Scene_b180_01E01760 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);

    g->t++;
    if (g->t > 150 && g->t < 200) {
        func_001F5620(func_001F53A0(), g->joint, &g->mark);
        g->mark.y += 3.3f;
        g->pos = g->mark;
    }
    if (g->t > 10 && g->t < 200) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        b180_01E02C80(g, (s32)b180_01E01AB0, 0);
    }
    if (g->t == 10) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        b180_01E02C80(g, (s32)b180_01E01D00, 0);
    }
    if (g->t == 1) {
        b180_01E02C80(g, (s32)b180_01E022E0, 0);
    }
    if (g->t == 1) {
        b180_01E02C80(g, (s32)b180_01E021D0, 0);
    }
    if (g->t < 201) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.x += func_0019A5C8() % 20 - 10;
        g->pos.y += func_0019A5C8() % 20 - 10;
        g->pos.z += func_0019A5C8() % 20 - 10;
        b180_01E02C80(g, (s32)b180_01E01EB0, 0);
    }
    if (g->t > 19 && g->t < 200 && g->t % 3 == 1) {
        g->side = g->count % 2;
        b180_01E02C80(g, (s32)b180_01E02040, 0);
        g->count++;
    }
}

/* shape b180:01E01AB0, 147 insns: b646:01E02110's glow in purple-blue placed on joint 0xB248 on start, pushed 5 sideways by the scene side flag, always drifting by 9 x f38 and 0.5 x f30 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
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
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b180_01E01AB0;

typedef struct {
    u8 pad[0xB248];
    s16 joint;
    u8 padB24A[0x70];
    s16 side;
} Game_b180_01E01AB0;

static s32 func_01E01AB0_b180(Game_b180_01E01AB0 *g, Obj_b180_01E01AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f4C = 11.0f;
        o->f48 = 11.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->h52 = func_0019A5C8() % 360;
        o->h5A = 60;
        o->h5C = 6;
        o->mode = 2;
        o->col2[3] = 0;
        o->f34 = -(func_0019A5C8() % 30 + 15);
        o->f30 = func_0019A5C8() % 30 + 25;
        o->f38 = func_0019A5C8() % 10 + 15;
        if (g->side != 0) {
            o->w20 = 0x4000;
        } else {
            o->w20 = 0xC000;
        }
        func_001F5620(func_001F53A0(), g->joint, &o->x);
        if (g->side != 0) {
            o->z -= 5.0f;
        } else {
            o->z += 5.0f;
        }
    }
    if (o->t < 4) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f34 -= 9.0f * o->f38;
    o->f4C += 0.5f * o->f30;
    o->t++;
    return 0;
}

/* shape b180:01E01D00, 108 insns: a white-blue glow on a model joint: size 30 growing by 10 to 100; second alpha up by 0x60 to
   0xC0 until frame 200, then down by 9 until it ends; spins a quarter turn; follows the joint, shifted 5 back or forth by side */

typedef struct {
    u8 pad0[0xB248];
    s16 joint;
    u8 padB24A[0x70];
    s16 side;
} Game_b180_01E01D00;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b180_01E01D00;

static s32 func_01E01D00_b180(Game_b180_01E01D00 *g, Obj_b180_01E01D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f4C = 30.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0x40, 0x40, 0xFF);
        o->h52 = 0;
        o->h5A = 0xA;
        o->h5C = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xC8) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xA) {
        o->c1[3] -= 9;
    } else {
        o->state = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    if (o->f4C < 100.0f) {
        o->f4C += 10.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    if (g->side != 0) {
        o->pos.z -= 5.0f;
    } else {
        o->pos.z += 5.0f;
    }
    o->t++;
    return 0;
}

/* shape b180:01E01EB0, 98 insns: a grey puff: set up once (size 6..20, frame 0..2, start 50..249, growth 16..35, life 3..5); fades in by 0x40 for its life, then out by 14 */

typedef struct {
    u8 pad00[6];
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
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b180_01E01EB0;

static s32 func_01E01EB0_b180(void *arg0, Obj_b180_01E01EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = func_0019A5C8() % 15 + 6;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 200 + 50;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b180:01E02040, 98 insns: a two-colour fade by kind (0 blue/black, 1 black/red, 2 pale blue both; hold 4, 4 or 22): both
   alphas up by 32 until the hold, then down by 7, the first ending it and the second stopping at 0 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b180_01E02040;

static s32 func_01E02040_b180(void *arg0, Obj_b180_01E02040 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            func_001076F0(o->c0, 0, 0, 0x80);
            func_001076F0(o->c1, 0, 0, 0);
            o->hold = 4;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0, 0, 0);
            func_001076F0(o->c1, 0x80, 0, 0);
            o->hold = 4;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0x58, 0x58, 0x78);
            func_001076F0(o->c1, 0x58, 0x58, 0x78);
            o->hold = 0x16;
        }
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x20;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x20;
        }
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 8) {
            o->c1[3] -= 7;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b180:01E021D0, 66 insns: volume fade for a scene: starts at 0x80, fades down by 10 (floor 0x30) for the
   first 0x97 ticks, then back up by 10 (cap 0x80) while the game state is below 0x1E; state 3 forces full volume */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b180_01E021D0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b180_01E021D0;

static s32 func_01E021D0_b180(Game_b180_01E021D0 *g, Fade_b180_01E021D0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x97) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->tick++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b180:01E022E0, 181 insns: b152:01E03400's full-screen overlay (colour 0xFF/0xFF/0xFF) with a fixed inset: one sprite over the
   whole screen, its texture window inset by the slot's width and height; alpha up by 9 to 0x80 for 200 ticks, then
   down by 7 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b180_01E022E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b180_01E022E0 p;
    } v[2];
} Pkt_b180_01E022E0;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b180_01E022E0;

typedef struct {
    u8 pad0[0xB228];
    Pkt_b180_01E022E0 *pkt;
} Scene_b180_01E022E0;

static s32 func_01E022E0_b180(Scene_b180_01E022E0 *s, Slot_b180_01E022E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 w;
    f32 h;

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
    s->pkt->v[1].t = (448.0f - h) / 512.0f;
    func_002075F0(s->pkt, 0, 0);
    if (o->t < 200) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 9;
        }
    } else if (o->t > 40) {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b180:01E025C0 (b180), 429 insns, 1 copy: b180 scene manager in b098:01E01F30 form: setup (six joints, two
   type-4 and one type-5 textures, 256 s8 and 30 s16 jitters), step b180:01E01760 and every slot (counting the
   b180:01E022E0 overlays instead of stepping them), draw the b180:01E01AB0 bands on joint A, b180:01E01D00 circles,
   b180:01E01EB0 sprites and b180:01E02040 quads at the projected camera depth, the overlay pass b180:01E02E10 if any;
   scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b180_01E025C0;

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
    s32 rm[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b180_01E025C0 fx[400];
    u8 padB1A0[0x50];
    s32 tex[4];
    u8 padB200[0x10];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x14];
    f32 depth;
    u8 padB238[0x10];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB254[4];
    s16 cam;
    u8 padB25A[0xE];
    s16 jit16[30];
    u8 padB2A4[0x16];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3C0[0x100];
    u8 crd[0x170];
} Scene_b180_01E025C0;

static s32 func_01E025C0_b180(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern void b180_01E02E10();
    extern void func_01E01760_b180();
    Scene_b180_01E025C0 *g = (Scene_b180_01E025C0 *)arg0;
    s16 n;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 ang[4];
    struct { u8 a[0x18]; u8 o[0x70]; } out;
    s32 i;
    s16 k;

    n = 0;
    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 245;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 1; i++) {
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
    func_01E01760_b180(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E022E0_b180) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    n++;
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            m++;
            if (g->fx[k].fn == (s32 (*)())func_01E01AB0_b180) {
                g->hB8 = 6;
                func_001F5620(func_001F53A0(), g->jA, &g->fx[k].pos);
                func_01E01230_b180((Obj_b180_01E01230 *)g, (Band_b180_01E01230 *)&g->fx[k], 0x21, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D00_b180) {
                g->hB8 = 0x24;
                func_01E00ED0_b180((Obj_b016_01E01190 *)g, (void *)&g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01EB0_b180) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b180((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02040_b180) {
                func_001F5F90(func_001F5380(), &v);
                if (g->turn != 0) {
                    v.z -= 50.0f;
                } else {
                    v.z += 50.0f;
                }
                func_00205440(&v, NULL, out.o, &g->depth);
                if (g->fx[k].h50 == 0) {
                    func_01E01590_b180((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 1) {
                    func_01E01590_b180((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 2) {
                    func_01E01590_b180((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
            }
        }
    }
    if (n) {
        b180_01E02E10(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 70) {
        return 1;
    }
    if (g->frame == 230) {
        return 4;
    }
    if (g->frame == 205) {
        return 2;
    }
    if (g->frame > 80 && g->frame < 200) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b180:01E02C80, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b180_01E02C80 {
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
} Slot_b180_01E02C80;

typedef struct Obj_b180_01E02C80 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b180_01E02C80 slots[0x190];
    u8 padB[0xb214 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb2b6 - 0xb214 - 4];
    s16 fB2B0;
} Obj_b180_01E02C80;

static s32 func_01E02C80_b180(Obj_b180_01E02C80 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b180_01E02C80 *s = NULL;
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

/* shape b098:01E02650, 89 insns, 7 copies: draws the module's live objects: sets up a sprite packet on the stack,
   then for each of the 400 objects (0x70 bytes) that is active and uses the module's draw routine
   (b098:01E01C50), calls it; sends the list if any object was active. */

typedef struct {
    s16 n;
    s16 nreg;
    s32 pad4;
    u64 regs;
    u8 rest[0x30];
} Pk_b098_01E02650;

typedef struct Obj_b098_01E02650 {
    u8 pad0[0x44];
    void *draw;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Obj_b098_01E02650;

typedef struct {
    u8 pad0[0x2A0];
    Obj_b098_01E02650 objs[400];
    u8 padB1A0[0x84];
    s32 list;
    Pk_b098_01E02650 *pk;
} Ctx_b098_01E02650;

typedef struct {
    u64 tag;
    Pk_b098_01E02650 pk;
    s32 a[2];
    s32 b[2];
} Buf_b098_01E02650;

extern void b180_01E022E0(Ctx_b098_01E02650 *ctx, Obj_b098_01E02650 *o);

static void func_01E02E10_b180(Ctx_b098_01E02650 *ctx) {
    extern s32 func_001F53A0();
    Buf_b098_01E02650 buf;
    s32 i;
    s32 n;

    ctx->pk = &buf.pk;
    n = 0;
    ctx->list = func_00207F60();
    ctx->pk->nreg = 0x26;
    ctx->pk->n = 5;
    ctx->pk->regs = 0x42421;
    ctx->pk->pad4 = 0;
    func_00208460();
    func_002086D0(ctx->pk, 0x48 | ((s64)0x80 << 32));
    func_001F7060(func_001F53A0(), 0, (s32)buf.a, (s32)buf.b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (ctx->objs[i].active != 0) {
            n++;
            if (ctx->objs[i].draw == b180_01E022E0) {
                b180_01E022E0(ctx, &ctx->objs[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(ctx->list, (s32)func_00207500(), 0);
    }
}
