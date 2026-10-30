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

static void func_01E00080_b546(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b546(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b546((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b546((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b041:01E00CF0, 182 insns: b016:01E00ED0 plus func_00109100(view, {.., .., cam 0x5A}, 2, obj 0xD8) after the view setup; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b546 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b041_01E00CF0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x2A];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b041_01E00CF0;

typedef struct Obj_b041_01E00CF0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b041_01E00CF0;

typedef struct Xyz_b041_01E00CF0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b041_01E00CF0;

typedef struct Uv_b041_01E00CF0 {
    f32 u, v;
} Uv_b041_01E00CF0;

typedef struct Pk_b041_01E00CF0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b041_01E00CF0 uv;
    u64 pad18;
    Xyz_b041_01E00CF0 v[4];
    u64 pad60[6];
} Pk_b041_01E00CF0;

typedef struct Buf_b041_01E00CF0 {
    u64 tag;
    Pk_b041_01E00CF0 pk;
} Buf_b041_01E00CF0;

static void func_01E00ED0_b546(Obj_b041_01E00CF0 *obj, Cam_b041_01E00CF0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 arg[4];
    Buf_b041_01E00CF0 buf;
    Uv_b041_01E00CF0 uv;
    s32 sel;
    s32 mode;
    Pk_b041_01E00CF0 *p = &buf.pk;

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
    func_01E00080_b546((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
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

static void func_01E011B0_b546(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b546:01E01510, 135 insns: scene spawn step: t++; on the first frame it starts handlers 0x1E01F90 and 0x1E01ED0
   (0xC85E 0 then 1); on frames 63..199 three sparks a tick (handler 0x1E01730) at the scene joint, each lifted by
   -1.0..0.9 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xC5D0];
    s16 joint;
    u8 padC832[0x2C];
    s16 hC85E;
    u8 padC860[6];
    s16 t;
} Scene_b546_01E01510;

static void func_01E01510_b546(Scene_b546_01E01510 *g) {
    extern void b546_01E01730(void);
    extern void b546_01E01ED0(void);
    extern void b546_01E01F90(void);
    extern void b546_01E027F0(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 f;

    g->t++;
    if (g->t == 1) {
        b546_01E027F0(g, b546_01E01F90, 0);
        g->hC85E = 0;
        g->hC85E = 1;
        b546_01E027F0(g, b546_01E01ED0, 0);
    }
    if (g->t > 0x3E && g->t < 0xC8) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        f = (func_0019A5C8() >> 4) % 20 - 10;
        f /= 10.0f;
        g->pos.y += f;
        b546_01E027F0(g, b546_01E01730, 0);
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        f = (func_0019A5C8() >> 4) % 20 - 10;
        f /= 10.0f;
        g->pos.y += f;
        b546_01E027F0(g, b546_01E01730, 0);
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        f = (func_0019A5C8() >> 4) % 20 - 10;
        f /= 10.0f;
        g->pos.y += f;
        b546_01E027F0(g, b546_01E01730, 0);
    }
}

/* shape b546:01E01730, 279 insns, 1 copy (B546_OBJ_MOVE_2_): a falling flake: on start size 5, white, random drift
   (x/z -50..49 / 150, spin), rising 2.2 then aimed from joint to model over 30 ticks, random turns; in by 64 up to
   0x80 for 40 ticks, then out by 9; grows to 15, blinks grey; at its burst tick it spawns two sparks
   (b546:01E01B90, b546:01E01D80) at its spot and ends; held at tick 90 once the scene count passes 250 */

typedef struct {
    s16 rx;
    s16 ry;
    s16 rz;
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    f32 vx;
    f32 vy;
    f32 vz;
    f32 f3C;
    u8 pad40[0x12];
    s16 burst;
    s16 tick;
    s16 h56;
    s16 state;
    s16 turn;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b546_01E01730;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xC5D0];
    s16 joint;
    u8 padC832[0x34];
    s16 count;
} Scene_b546_01E01730;

static s32 func_01E01730_b546(Scene_b546_01E01730 *g, Obj_b546_01E01730 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    extern void func_001F5F90(s32, Vec4f *);
    extern void b546_01E01B90();
    extern void b546_01E01D80();
    extern void b546_01E027F0();
    Vec4f a;
    Vec4f b;
    f32 f;

    if (o->state == 1) {
        o->w = 5;
        o->h = 5;
        o->h56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vy /= 150.0f;
        o->vx /= 150.0f;
        o->f3C = func_0019A5C8() % 80 - 40;
        o->f3C /= 10.0f;
        o->vz = 2.2f;
        f = (func_0019A5C8() >> 4) % 50 - 25;
        f /= 20.0f;
        o->pos.y += f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->rz = func_0019A5C8() % 0x800 - 0x400;
        o->ry = func_0019A5C8() % 0x800 - 0x400;
        o->rx = func_0019A5C8() % 0x800 - 0x400;
        o->turn = func_0019A5C8() % 360;
        o->rot[0] = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot[1] = 0x4000;
        o->burst = (func_0019A5C8() >> 4) % 5 + 30;
        func_001F5620(func_001F53A0(), g->joint, &a);
        func_001F5F90(func_001F5380(), &b);
        o->vz = (b.z - a.z) / 30.0f;
    }
    if (o->tick < 40) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->tick != 0) {
        o->pos.z += o->vz;
        o->pos.x += o->vx;
        o->pos.y += o->vy - 0.1f;
        if (o->w < 15) {
            o->w++;
        }
        if (o->h < 15) {
            o->h++;
        }
    }
    if (o->tick == o->burst) {
        g->pos = o->pos;
        b546_01E027F0(g, b546_01E01B90, 0);
        b546_01E027F0(g, b546_01E01D80, 0);
        o->state = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0x70);
    }
    o->tick++;
    if (g->count > 250) {
        o->tick = 90;
    }
    o->turn += 40;
    return 0;
}

/* shape b546:01E01B90, 119 insns: a red/white blinking spark (size 8, frame 4, angle 10..29, spin 4..10, size 1..8) held 20..22 ticks at 0xC0, then out by 11 and ends; held at tick 30 while the scene count is under 35 */

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
    u8 pad2C[8];
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
} Obj_b546_01E01B90;

typedef struct {
    u8 pad[0xC7F0];
    s32 val;
} Game_b546_01E01B90;

static s32 func_01E01B90_b546(Game_b546_01E01B90 *g, Obj_b546_01E01B90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 8.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0x60, 0x60);
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 7 + 4;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 20;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x60, 0x60);
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    if (g->val < 35) {
        o->t = 30;
    }
    o->t++;
    return 0;
}

/* shape b259:01E02760, 83 insns, 2 copies: a blinking marker: set up once (white and red, size 80); the second colour fades in
   for the first frames, then out; it blinks between yellow and dim each frame while turning (b016:01E01FF0
   family) */

typedef struct {
    u8 pad0[6];
    s16 fade;
    u8 pad8[0x18];
    s32 rot;
    u8 pad24[0x24];
    s32 w48;
    f32 size;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b259_01E02760;

static s32 func_01E01D80_b546(void *arg0, Obj_b259_01E02760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w48 = 0;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xC0, 0x40, 0x40);
        o->fade = 4;
        o->size = 80.0f;
        o->h5C = o->h5A = 0x14;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < o->fade) {
        if (o->c1[3] < 0xA0) {
            o->c1[3] += 0x50;
        }
    } else if (o->c1[3] > 0x14) {
        o->c1[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b546:01E01ED0, 48 insns: variant of b445:01E03C90 (volume fade): game state at 0xC7F0, floor 0x20 */

typedef struct {
    u8 pad[0xC7F0];
    s32 state;
} Game_b546_01E01ED0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b546_01E01ED0;

static s32 func_01E01ED0_b546(Game_b546_01E01ED0 *g, Fade_b546_01E01ED0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
        if (o->vol > 0x20) {
            o->vol -= 10;
        } else {
            o->vol = 0x20;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    func_001F6D00((u8)o->vol);
    return 0;
}

/* shape b546:01E01F90, 147 insns: b259:01E02970 with the scene packet at ctx+0xC810 and 240 ticks */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b546_01E01F90;

typedef struct {
    f32 s, t;
    Xyz_b546_01E01F90 p;
} Tv_b546_01E01F90;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b546_01E01F90 v[2];
} Tex_b546_01E01F90;

typedef struct {
    u8 pad[0xC810];
    Tex_b546_01E01F90 *pk;
} Game_b546_01E01F90;

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b546_01E01F90;

static s32 func_01E01F90_b546(Game_b546_01E01F90 *g, Fx_b546_01E01F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 240) {
        if (o->col[3] < 0x70) {
            o->col[3] += 18;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b546:01E021E0 (b546), 386 insns, 1 copy: the module scene manager (b236:01E01D80 form): with a scene id it
   clears the scene, sets the 270-frame countdown, reads six joints, textures 4:15 and 5:0..1, the camera turn, scale
   0.1 and two jitter tables; otherwise it runs b546:01E01510, every handler but b546:01E01F90 (counting those), draws
   the three effect kinds, calls b546:01E02980 if any were counted, counts down and returns the next step by frame
   (124, 260, 250, 135..244) or 8 when the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b546_01E021E0;

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
    Fx_b546_01E021E0 fx[450];
    u8 padC780[0x50];
    s32 tex[2];
    u8 padC7D8[0x18];
    s32 count;
    u8 padC7F4[8];
    s32 ot;
    u8 padC800[4];
    s32 cam1;
    s32 cam2;
    u8 padC80C[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padC83C[4];
    s16 cam;
    u8 padC842[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x178];
} Scene_b546_01E021E0;

static s32 func_01E021E0_b546(s32 arg0, s32 id) {
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
    extern void func_01E01510_b546();
    extern void b546_01E02980();
    Scene_b546_01E021E0 *g = (Scene_b546_01E021E0 *)arg0;
    s16 m;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->cam1 = func_001F9AD0(0);
    g->cam2 = func_001F9D30(0);
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xCBE0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 270;
        g->jA = func_001F5560(func_001F53A0(), 0x10, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1E, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x01, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
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
            g->jit[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = 0;
        }
        return 0;
    }
    func_01E01510_b546(g, 0);
    for (k = 0; k < 450; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E01F90_b546) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    m++;
                }
            }
        }
    }
    for (k = 0; k < 450; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01730_b546) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hBE = 0;
                func_01E00ED0_b546((Obj_b041_01E00CF0 *)g, (Cam_b041_01E00CF0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01B90_b546) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hB8 = 3;
                g->hB0 = 0;
                func_01E00920_b546((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D80_b546) {
                g->hB8 = 0x12;
                func_01E011B0_b546((void *)g, (void *)&g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
        }
    }
    if (m) {
        b546_01E02980(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 124) {
        return 1;
    }
    if (g->frame == 260) {
        return 4;
    }
    if (g->frame == 250) {
        return 2;
    }
    if (g->frame > 134 && g->frame < 245) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b546:01E027F0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x1c2 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b546_01E027F0 {
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
} Slot_b546_01E027F0;

typedef struct Obj_b546_01E027F0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b546_01E027F0 slots[0x1c2];
    u8 padB[0xc7f4 - 0x2a0 - 0x1c2 * 0x70];
    u8 rgba[4];
    u8 padC[0xc85e - 0xc7f4 - 4];
    s16 fB2B0;
} Obj_b546_01E027F0;

static s32 func_01E027F0_b546(Obj_b546_01E027F0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b546_01E027F0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1c2; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x1c2;
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

/* shape b546:01E02980, 89 insns: the module's draw pass (b016:01E03880 shape): opens a sprite packet on the stack, then
   runs every live slot (450 of 0x70 bytes) live and whose handler is shape b546:01E01F90 through it; queues the batch only if any
   slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b546_01E02980;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b546_01E02980 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b546_01E02980;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b546_01E02980;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b546_01E02980 slot[450];
    u8 padEnd[0xC80C - 0x2A0 - 450 * 0x70];
    s32 ctx;
    Pkt_b546_01E02980 *pkt;
} Scene_b546_01E02980;

static void func_01E02980_b546(Scene_b546_01E02980 *s) {
    extern void b546_01E01F90(Scene_b546_01E02980 *, Slot_b546_01E02980 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b546_01E02980 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 450; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b546_01E01F90) {
            n++;
            b546_01E01F90(s, &s->slot[i]);
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
