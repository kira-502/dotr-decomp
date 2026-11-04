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

static void func_01E00080_b400(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b400(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b400((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b400((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b041:01E00FD0, 177 insns: b041:01E00CF0 with the view size from the camera's floats 0x30/0x34; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b400 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b041_01E00FD0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    f32 fw;
    f32 fh;
    u8 pad38[0x22];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b041_01E00FD0;

typedef struct Obj_b041_01E00FD0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b041_01E00FD0;

typedef struct Xyz_b041_01E00FD0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b041_01E00FD0;

typedef struct Uv_b041_01E00FD0 {
    f32 u, v;
} Uv_b041_01E00FD0;

typedef struct Pk_b041_01E00FD0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b041_01E00FD0 uv;
    u64 pad18;
    Xyz_b041_01E00FD0 v[4];
    u64 pad60[6];
} Pk_b041_01E00FD0;

typedef struct Buf_b041_01E00FD0 {
    u64 tag;
    Pk_b041_01E00FD0 pk;
} Buf_b041_01E00FD0;

static void func_01E00ED0_b400(Obj_b041_01E00FD0 *obj, Cam_b041_01E00FD0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b041_01E00FD0 buf;
    Uv_b041_01E00FD0 uv;
    s32 sel;
    s32 mode;
    Pk_b041_01E00FD0 *p = &buf.pk;

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
    func_01E00080_b400((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->fw, cam->fh);
    arg[2] = cam->f5A;
    func_00109100(view, arg, 2, obj->fD8);
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

static void func_01E011A0_b400(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E01500_b400(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b400:01E016D0, 166 insns: the effect scene's step: counts the frame (0x4522); before frame 155 the orb (0x4470)
   follows joint 0x44EC, on 155 it aims at the other model's joint 0x44FC over 25 frames and glides there until 176;
   from 18 to 176 it spawns two 0x1E01970 (sides 0 and 1) and a 0x1E01BA0 at the orb; from 20 the glow 0x44D4 grows
   by 2 to 100; on 176 it bursts ten 0x1E02190, ten 0x1E01F80, a 0x1E01D30 and a 0x1E01E30 at the orb */

typedef struct {
    f32 x, y, z, w;
} V4_b400_01E016D0;

typedef struct {
    u8 pad0[0x250];
    V4_b400_01E016D0 pos;
    u8 pad260[0x4210];
    V4_b400_01E016D0 orb;
    u8 pad4480[4];
    f32 vy;
    f32 vz;
    u8 pad448C[0x48];
    f32 glow;
    u8 pad44D8[0x14];
    s16 j0;
    u8 pad44EE[0xE];
    s16 j1;
    u8 pad44FE[0x1C];
    s16 side;
    u8 pad451C[6];
    s16 t;
} Scene_b400_01E016D0;

static void func_01E016D0_b400(Scene_b400_01E016D0 *g) {
    extern void b400_01E01970(void);
    extern void b400_01E01BA0(void);
    extern void b400_01E01D30(void);
    extern void b400_01E01E30(void);
    extern void b400_01E01F80(void);
    extern void b400_01E02190(void);
    extern s32 b400_01E02A60(Scene_b400_01E016D0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];
    s16 i;

    g->t++;
    if (g->t < 155) {
        func_001F5620(func_001F53A0(), g->j0, &g->orb);
    } else {
        if (g->t == 155) {
            func_001F5620(func_001F5380(), g->j1, &v[0]);
            g->vz = (v[0].z - g->orb.z) / 25.0f;
            g->vy = (v[0].y - g->orb.y) / 25.0f;
        }
        if (g->t < 176) {
            g->orb.z += g->vz;
            g->orb.y += g->vy;
        }
    }
    if (g->t >= 18 && g->t < 177) {
        g->side = 0;
        b400_01E02A60(g, (s32)b400_01E01970, 0);
        g->side = 1;
        b400_01E02A60(g, (s32)b400_01E01970, 0);
        g->pos = g->orb;
        b400_01E02A60(g, (s32)b400_01E01BA0, 0);
    }
    if (g->t >= 20 && g->t < 177) {
        if (g->glow < 100.0f) {
            g->glow += 2.0f;
        }
    }
    if (g->t == 176) {
        g->pos = g->orb;
        g->side = 0;
        for (i = 0; i < 10; i++) {
            b400_01E02A60(g, (s32)b400_01E02190, 0);
        }
        for (i = 0; i < 10; i++) {
            b400_01E02A60(g, (s32)b400_01E01F80, 0);
        }
        b400_01E02A60(g, (s32)b400_01E01D30, 0);
        b400_01E02A60(g, (s32)b400_01E01E30, 0);
    }
}

/* shape b400:01E01970, 137 insns: a dark glow that grows towards the scene's limit (g+0x44D4): on start size 5, a random
   frame, colour 0x10, h52 50; alpha up by 10 for 15 ticks, then down by 8 until it ends; after the first tick f30 and f34
   grow towards the limit (by 3 and 3 before scene time 140, by 5 and 2.5 after); for 15 ticks it sits on the scene point
   g+0x4470; it spins, and its clock runs twice as fast from scene time 178 */

typedef struct {
    u8 pad0[0x4470];
    Vec4f v;
    u8 pad4480[0x54];
    f32 lim;
    u8 pad44D8[0x4A];
    s16 time;
} Game_b400_01E01970;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b400_01E01970;

static s32 func_01E01970_b400(Game_b400_01E01970 *g, Obj_b400_01E01970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 5.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->c0, 0x10, 0x10, 0x10);
        o->mode = 2;
        o->h52 = 50;
        o->h5A = 0;
    }
    if (o->t < 15) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 10;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        if (g->time < 140) {
            if (!(g->lim <= o->f30)) {
                o->f30 += 3.0f;
            }
        } else if (!(g->lim <= o->f30)) {
            o->f30 += 5.0f;
        }
        if (g->time < 140) {
            if (!(g->lim <= o->f34)) {
                o->f34 += 3.0f;
            }
        } else if (!(g->lim <= o->f34)) {
            o->f34 += 2.5f;
        }
    }
    if (o->t < 15) {
        o->pos = g->v;
    }
    func_00205C40((s32)o->rot);
    if (g->time < 178) {
        o->t += 1;
    } else {
        o->t += 2;
    }
    return 0;
}

/* shape b400:01E01BA0, 98 insns: a white spark (random size 10..19, frame 0..2, heading, angle 10..49, spin 16..35 and size 0..34 stored) held 3..5 ticks: in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b400_01E01BA0;

static s32 func_01E01BA0_b400(s32 arg0, Obj_b400_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b400:01E01D30, 63 insns: constant variant of b178:01E03530 (colour (128, 64, 64)) */

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
} Fx_b400_01E01D30;

static s32 func_01E01D30_b400(s32 arg0, Fx_b400_01E01D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x40, 0x40);
        o->life = 12;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 0xD) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xD) {
            o->col2[3] -= 12;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b400:01E01E30, 81 insns: a pink flickering spinning flash (b432:01E026D0 family): f4C 300, size 10x10; second alpha up by 0x60 to
   0xC0 for 12 frames, then down by 11 until it ends; first colour flickers by frame parity */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b400_01E01E30;

static s32 func_01E01E30_b400(void *arg0, Obj_b400_01E01E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 300.0f;
        o->f4C = 300.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xC) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xC) {
        o->c1[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0xC0, 0x80, 0x80);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b400:01E01F80, 130 insns: b193:01E02910 family white spark (f48 15..24, f50 7..26 growing 10..29 after the first tick), alpha 0xF0 for 10..14 ticks then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b400_01E01F80;

static s32 func_01E01F80_b400(s32 arg0, Fx_b400_01E01F80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 15;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 20 + 7;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 5 + 10;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xF0;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b400:01E02190, 127 insns: constant variant of b016:01E02940 (spark set-up) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 x;
    s32 y;
    s32 z;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 dir;
    u8 pad5C[4];
    u8 col[4];
} Spark_b400_01E02190;

static s32 func_01E02190_b400(s32 arg0, Spark_b400_01E02190 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0x50, 0x50);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 200 + 200;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 10;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 5 + 5;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02390_b400(void) {
    return 0;
}

/* shape b400:01E023A0 (b400), 430 insns, 1 copy: the effect scene manager: on a code >= 0 clears the 0x4890-byte
   scene, sets up its joints, textures and jitter tables; else steps the scene (0x1E016D0), runs the 150 effect slots
   and draws each kind; returns the cue for frames 168, 220, 195, 179..189, and 8 when the count runs out */

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
} Fx_b400_01E023A0;

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
        struct {
            s16 x, y, w, h;
        } r;
    } u;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b400_01E023A0 fx[150];
    u8 pad4440[0x30];
    Vec_b016_01E01190 orb;
    u8 pad4480[0x10];
    s32 tex[3];
    u8 pad449C[0x14];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x18];
    f32 depth;
    u8 pad44DC[0x10];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad44F8[4];
    s16 cam;
    u8 pad44FE[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b400_01E023A0;

static s32 func_01E023A0_b400(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern void func_01E016D0_b400();
    Scene_b400_01E023A0 *g = (Scene_b400_01E023A0 *)arg0;
    s16 n;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    struct { u8 a[0x18]; u8 o[0x70]; } out;
    s32 i;
    s16 k;

    n = 0;
    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4890);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 225;
        g->jA = func_001F5560(func_001F53A0(), 0x36, 1);
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
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E016D0_b400(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02390_b400) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    n++;
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            m++;
            if (g->fx[k].fn == (s32 (*)())func_01E01970_b400) {
                g->tex88 = g->tex[g->fx[k].h50];
                g->u.r.x = 0;
                g->u.r.y = 0;
                g->u.r.w = 0x7F;
                g->u.r.h = 0x7F;
                g->hBE = g->fx[k].h56;
                func_01E00ED0_b400((Obj_b041_01E00FD0 *)g, (Cam_b041_01E00FD0 *)&g->fx[k], 0x21, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01BA0_b400) {
                g->tex88 = g->tex[2];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b400((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D30_b400) {
                func_001F5F90(func_001F53A0(), &v);
                if (g->turn != 0) {
                    v.z += 60.0f;
                } else {
                    v.z -= 60.0f;
                }
                func_00205440(&v, NULL, out.o, &g->depth);
                func_01E01500_b400((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E30_b400) {
                g->hB8 = 0x24;
                func_01E011A0_b400((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   &g->orb);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F80_b400) {
                g->tex88 = g->tex[2];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00920_b400((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02190_b400) {
                g->tex88 = g->tex[0];
                g->u.r.x = 0;
                g->u.r.y = 0;
                g->u.r.w = 0x7F;
                g->u.r.h = 0x7F;
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E00920_b400((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 168) {
        return 1;
    }
    if (g->frame == 220) {
        return 4;
    }
    if (g->frame == 195) {
        return 2;
    }
    if (g->frame > 178 && g->frame < 190) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b016:01E03740, 80 insns, 3 copies: starts a particle: takes the first free one of 150 slots, clears it, gives it
   the emitter's colour (twice), position and timer and the two caller values; returns 0 when all are busy
   (150-slot variant of shape b539:01E03530). */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 t0;
    s16 t1;
    u8 pad54[4];
    s16 used;
    s16 t2;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b016_01E03740;

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad0260[0x40];
    Slot_b016_01E03740 slots[150];
    u8 pad4440[0x74];
    u8 col[4];
    u8 pad44B8[0x62];
    s16 t0;
} Emit_b016_01E03740;

static s32 func_01E02A60_b400(Emit_b016_01E03740 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b016_01E03740 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 150; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 150;
        }
    }
    if (e != NULL) {
        func_001076F0(e->c0, o->col[0], o->col[1], o->col[2]);
        e->c0[3] = o->col[3];
        func_001076F0(e->c1, o->col[0], o->col[1], o->col[2]);
        e->c1[3] = o->col[3];
        func_00106AB0(e, &o->pos, 0);
        e->x = o->pos.x;
        e->y = o->pos.y;
        e->z = o->pos.z;
        e->t0 = o->t0;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}
