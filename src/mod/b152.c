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

static void func_01E00080_b152(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b152 in the
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

static void func_01E00920_b152(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b152((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00BE0_b152(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b152((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b152((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E01190_b152(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E014F0_b152(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
}

/* shape b152:01E01640 (B152_W_S), 518 insns, 1 copy (-O3,p): B152_W_S, the scene timer script: counts the frame
   (0xA0B2); frame 1 and 36 spawn b152:01E031F0/01E03110, 81..159 b152:01E03400; from 141 the sizes at 0x9FC0/0x9FC4
   grow to 80/50; from 83, 36 sparks (b152:01E01E60); 80..350 b152:01E02680 at joint 0xA032 and 80..200 two
   b152:01E02530 a frame; frame 183 places the point 0x3BB0; 370..425 two orbiting b152:01E02820 and a b152:01E02F70;
   odd frames 267..281 b152:01E02990; frame 290 the b152:01E02AF0 pair and eight b152:01E02D90 (b597:01E01640 form) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3BB0 - 0x260];
    Vec4f p;
    u8 pad3BC0[0x9FC0 - 0x3BC0];
    f32 w;
    f32 h;
    u8 pad9FC8[0xA030 - 0x9FC8];
    s16 id;
    s16 id0;
    u8 padA034[0xA040 - 0xA034];
    s16 id1;
    u8 padA042[0xA09A - 0xA042];
    s16 cnt;
    u8 padA09C[0xA0A4 - 0xA09C];
    s16 ang;
    u8 padA0A6[0xA0AA - 0xA0A6];
    s16 idx;
    u8 padA0AC[0xA0AE - 0xA0AC];
    s16 flag;
    u8 padA0B0[0xA0B2 - 0xA0B0];
    s16 frame;
    u8 padA0B4[0xA2B4 - 0xA0B4];
    u8 tab[1];
} Scene_b152_01E01640;

#pragma optimization_level 3

static void func_01E01640_b152(Scene_b152_01E01640 *g) {
    extern void b152_01E01E60();
    extern void b152_01E02530();
    extern void b152_01E02680();
    extern void b152_01E02820();
    extern void b152_01E02990();
    extern void b152_01E02AF0();
    extern void b152_01E02D90();
    extern void b152_01E02F70();
    extern void b152_01E03110();
    extern void b152_01E031F0();
    extern void b152_01E03400();
    extern s32 b152_01E03FD0();
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;

    g->frame++;
    if (g->frame == 1) {
        b152_01E03FD0(g, b152_01E031F0, 0);
    }
    if (g->frame == 36) {
        b152_01E03FD0(g, b152_01E03110, 0);
    }
    if (g->frame >= 81 && g->frame < 160) {
        b152_01E03FD0(g, b152_01E03400, 0);
    }
    if (g->frame == 141) {
        g->idx = 0;
    }
    if (g->frame >= 141) {
        if (g->h < 50.0f) {
            g->h += 1.5f;
        }
        if (g->w < 80.0f) {
            g->w += 1.0f;
        }
    }
    if (g->frame >= 83) {
        if (g->cnt < 36) {
            func_001F5620(func_001F53A0(), g->id, &g->pos);
            g->idx = g->cnt;
            g->pos.y = 30.0f;
            g->pos.x += func_0019A5C8() % 60 - 30;
            g->pos.z += func_0019A5C8() % 60 - 30;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b152_01E03FD0(g, b152_01E01E60, 0);
            g->cnt++;
        }
    }
    if (g->frame >= 80 && g->frame < 351) {
        func_001F5620(func_001F53A0(), g->id0, &g->pos);
        b152_01E03FD0(g, b152_01E02680, 0);
    }
    if (g->frame >= 80 && g->frame < 201) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->id, &g->pos);
            g->pos.y = 30.0f;
            g->pos.x += func_0019A5C8() % 60 - 30;
            g->pos.z += func_0019A5C8() % 60 - 30;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b152_01E03FD0(g, b152_01E02530, 0);
        }
    }
    if (g->frame == 183) {
        func_001F5620(func_001F53A0(), g->id0, &g->p);
        if (g->flag) {
            g->p.z -= 10.0f;
        } else {
            g->p.z += 10.0f;
        }
        g->p.y += 8.0f;
    }
    g->ang += 5;
    if (g->frame >= 370 && g->frame < 426) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F5380(), g->id, &g->pos);
            g->pos.y = 40.0f;
            if (i == 0) {
                g->pos.x += 10.0f * func_00108030(g->tab, g->ang, 1);
                g->pos.z += 10.0f * func_00108030(g->tab, g->ang, 0);
            }
            if (i == 1) {
                g->pos.x += 10.0f * func_00108030(g->tab, g->ang + 180, 1);
                g->pos.z += 10.0f * func_00108030(g->tab, g->ang + 180, 0);
            }
            b152_01E03FD0(g, b152_01E02820, 0);
        }
        func_001F5620(func_001F5380(), g->id1, &g->pos);
        g->pos.y += func_0019A5C8() % 5;
        b152_01E03FD0(g, b152_01E02F70, 0);
    }
    if (g->frame == 267 || g->frame == 269 || g->frame == 271 || g->frame == 273 ||
        g->frame == 275 || g->frame == 277 || g->frame == 279 || g->frame == 281) {
        b152_01E03FD0(g, b152_01E02990, 0);
    }
    if (g->frame == 290) {
        g->idx = 1;
        b152_01E03FD0(g, b152_01E02AF0, 0);
        g->idx = 2;
        b152_01E03FD0(g, b152_01E02AF0, 0);
        g->pos = g->p;
        for (i = 0; i < 8; i++) {
            b152_01E03FD0(g, b152_01E02D90, 0);
        }
    }
}

#pragma optimization_level reset

/* shape b152:01E01E60 (B152_OBJ_MOVE_4_), 435 insns, 1 copy: a ring spark: fades in by 10 to 0x80 before scene
   frame 430, then out by 4; flickers 0xC0/0xFF; rises 1.2 a tick (ticks 11-44), flies over 30 ticks from 103 to its
   spot around the scene point (radius 15, angle h50 * 10), circles it in frames 256-359; from tick 240 flies to the
   tracked target and orbits it at radius func_001F5380() / 13 (10..60), bobbing up to 8 */

typedef struct {
    u8 pad0[0x3BB0];
    Vec4f pos;
    u8 pad3BC0[0xA01C - 0x3BC0];
    f32 r;
    u8 padA020[0xA032 - 0xA020];
    s16 id0;
    u8 padA034[0xA040 - 0xA034];
    s16 id1;
    u8 padA042[0xA0A4 - 0xA042];
    s16 hA0A4;
    u8 padA0A6[0xA0B2 - 0xA0A6];
    s16 frame;
    u8 padA0B4[0xA2B4 - 0xA0B4];
    u8 tab[1];
} Ctx_b152_01E01E60;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    Vec4f v;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 tick;
    s16 h56;
    s16 mode;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b152_01E01E60;

static s32 func_01E01E60_b152(Ctx_b152_01E01E60 *g, Fx_b152_01E01E60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);
    Vec4f v[2];
    s16 t;

    if (o->mode == 1) {
        o->h8 = 10;
        o->hA = 10;
        o->f48 = 0.0f;
        o->h56 = (func_0019A5C8() >> 4) % 8;
        o->v.y = 1.2f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->h52 = o->h50;
        o->mode = 2;
        o->col2[3] = 0;
        o->h5C = 0;
    }
    if (g->frame < 430) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 10;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        }
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    }
    t = o->tick;
    if (t > 10 && t < 45) {
        o->pos.y += o->v.y;
    } else if (t >= 103 && t < 133) {
        if (t == 103) {
            v[1] = g->pos;
            v[0].x = 15.0f * func_00108030(g->tab, o->h50 * 10, 1);
            v[0].y = 15.0f * func_00108030(g->tab, o->h50 * 10, 0);
            o->v.x = (v[1].x + v[0].x - o->pos.x) / 30.0f;
            o->v.y = (v[1].y + v[0].y - o->pos.y) / 30.0f;
            o->v.z = (v[1].z - o->pos.z) / 30.0f;
            o->ang = o->h50 * 10;
        }
        o->pos.x += o->v.x;
        o->pos.y += o->v.y;
        o->pos.z += o->v.z;
    }
    if (o->tick < 240 && g->frame >= 256 && g->frame < 360) {
        func_001F5620(func_001F53A0(), g->id0, &v[1]);
        v[0].x = 15.0f * func_00108030(g->tab, o->ang, 1);
        v[0].y = 15.0f * func_00108030(g->tab, o->ang, 0);
        o->pos.x = g->pos.x + v[0].x;
        o->pos.y = g->pos.y + v[0].y;
        o->ang += 2;
    }
    if (o->tick >= 240) {
        if (o->tick == 240) {
            g->r = func_001F5380() / 13.0f;
            if (g->r > 60.0f) {
                g->r = 60.0f;
            }
            if (g->r < 10.0f) {
                g->r = 10.0f;
            }
            o->ang = 0;
            func_001F5620(func_001F5380(), g->id1, &v[1]);
            v[0].x = g->r * func_00108030(g->tab, o->ang, 1);
            v[0].z = g->r * func_00108030(g->tab, o->ang, 0);
            o->v.x = (v[1].x + v[0].x - o->pos.x) / 30.0f;
            o->v.y = (v[1].y - o->pos.y) / 30.0f;
            o->v.z = (v[1].z + v[0].z - o->pos.z) / 30.0f;
        }
        if (o->tick < 270) {
            o->pos.x += o->v.x;
            o->pos.y += o->v.y;
            o->pos.z += o->v.z;
        } else {
            func_001F5620(func_001F5380(), g->id1, &v[1]);
            v[0].x = g->r * func_00108030(g->tab, o->ang, 1);
            v[0].z = g->r * func_00108030(g->tab, o->ang, 0);
            o->pos.x = v[1].x + v[0].x;
            o->pos.z = v[1].z + v[0].z;
            o->pos.y = v[1].y + o->f48 * func_00108030(g->tab, o->ang + g->hA0A4 * 4, 0);
            o->ang -= 10;
            if (o->f48 < 8.0f) {
                o->f48 += 0.5f;
            }
        }
    }
    func_00205C40(o->rot);
    o->tick++;
    return 0;
}

/* shape b152:01E02530, 84 insns, 2 copies: a rising white puff: set up once (random phase 0..7, climb 2.5 a frame), both
   colours fade in over 10 frames, then the first fades out (its fade-out step is applied twice); turns each
   frame (b016:01E01FF0 family) */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    u8 x20[0x14];
    f32 climb;
    u8 pad38[0x10];
    s32 w48;
    u8 pad4C[8];
    s16 t;
    s16 phase;
    s16 state;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b152_01E02530;

static s32 func_01E02530_b152(void *arg0, Obj_b152_01E02530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = 10;
        o->hA = 6;
        o->w48 = 0;
        o->phase = func_0019A5C8() % 8;
        o->climb = 2.5f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->c1[3] = 0;
        o->h5C = 0;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        }
    }
    if (o->t != 0) {
        o->y += o->climb;
    }
    func_00205C40((s32)o->x20);
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[0x16];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b152_01E02680;

static s32 func_01E02680_b152(s32 unused, Obj_b152_01E02680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 2 + 1;
        o->h56 = 4;
        func_001076F0(o->c60, 0xC0, 0xC0, 0xC0);
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->h50 = func_0019A5C8() % 80 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 4 + 3;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h54++;
    return 0;
}

/* shape b152:01E02820, 90 insns: a dark rising spark (b215:01E01FF0 family): size 30 by 60 growing by 2, random sub-frame 0..7, rises by f34 0.5;
   both alphas up by 0x40 to 0x80 for 20 frames, then the first down by 6 twice a frame until it ends; random turn */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    s16 hE;
    u8 pad10[4];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b152_01E02820;

static s32 func_01E02820_b152(void *arg0, Obj_b152_01E02820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x1E;
        o->h = 0x3C;
        o->f48 = 0.0f;
        o->sub = func_0019A5C8() % 8;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0x20, 0x20, 0x20);
        o->state = 2;
        o->c1[3] = 0;
        o->h5C = 0;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 7) {
            o->c0[3] -= 6;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 7) {
            o->c0[3] -= 6;
        }
    }
    if (o->t != 0) {
        o->w += 2;
        o->h += 2;
        o->y += o->f34;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b152:01E02990, 85 insns, 2 copies: a slow grey haze: fades in over 50 frames, then out while drifting; flickers
   between two greys each frame; its angle opens 5 a frame up to 90 (b016:01E01FF0 family) */

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[0x38];
    f32 ang;
    u8 pad4C[8];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b152_01E02990;

static s32 func_01E02990_b152(void *arg0, Obj_b152_01E02990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->ang = 0.0f;
        func_001076F0(o->c0, 0x10, 0x10, 0x10);
        o->h56 = 0;
        o->hE = 1;
        o->state = 2;
    }
    if (o->t < 0x32) {
        if (o->c0[3] < 0x90) {
            o->c0[3] += 0xE;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        o->ang += 0.5f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
    }
    if (o->ang < 90.0f) {
        o->ang += 5.0f;
    }
    o->t++;
    return 0;
}

/* shape b152:01E02AF0, 168 insns: b529:01E023B0 with kind 1 350 wide over pink, kind 2 160 wide dark red over grey, and the turn's second word cleared */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b152_01E02AF0;

static s32 func_01E02AF0_b152(s32 arg0, Fx_b152_01E02AF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 30.0f;
            o->f4C = 0.0f;
            o->hold = 300;
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        if (o->kind == 1) {
            o->f48 = 350.0f;
            o->f4C = 0.0f;
            o->hold = 12;
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0xFF, 0xC0, 0xC0);
        }
        if (o->kind == 2) {
            o->f48 = 160.0f;
            o->f4C = 0.0f;
            o->hold = 12;
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
            func_001076F0(o->col, 0x40, 0x10, 0x10);
        }
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->kind == 0) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 14;
            }
        }
        if (o->kind == 1) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x40;
            }
        }
        if (o->kind == 2) {
            if (o->col2[3] < 0xC0) {
                o->col2[3] += 0x40;
            }
        }
    } else {
        if (o->kind == 0 || o->kind == 1) {
            if (o->col[3] > 12) {
                o->col[3] -= 11;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 2) {
            if (o->col2[3] > 16) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
        } else {
            func_001076F0(o->col, 0x70, 0x70, 0x70);
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] = 0x4000;
    o->rot[1] = 0;
    o->tick++;
    return 0;
}

/* shape b152:01E02D90, 120 insns, 2 copies: a white glint: set up once (random size 8..22, frame 4, random turn on all axes,
   angle 20..49, speed 15..34, life 5..14); full for its life, then fades out; turns by its speed (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    s16 h52;
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b152_01E02D90;

static s32 func_01E02D90_b152(void *arg0, Spark_b152_01E02D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 8;
        o->frame = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h52 = 1;
        o->ang = func_0019A5C8() % 30 + 20;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 15;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->h52++;
    o->ang += o->speed;
    o->t++;
    return 0;
}

/* shape b152:01E02F70, 103 insns: a white spark at a random position: f48 5..11, f56 4, f50 60..259, random f5A, f8
   1..8, life 3..7; alpha 0x80 during the life, then fades by 11 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
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
} Fx_b152_01E02F70;

static s32 func_01E02F70_b152(s32 arg0, Fx_b152_01E02F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 7 + 5;
        o->f56 = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 200 + 60;
        o->f5A = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b152:01E03110, 54 insns: volume fade by its own timer (b003:01E02330 family, layout at 0x50): for 0xFA frames
   down 10 to 0x30, then up 10 to 0x80; state 3 at 0x9FF0 sets the volume to 0x80 and ends the fade */

typedef struct {
    u8 pad[0x9FF0];
    s32 state;
} Game_b152_01E03110;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b152_01E03110;

static s32 func_01E03110_b152(Game_b152_01E03110 *g, Fade_b152_01E03110 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0xFA) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b152:01E031F0, 130 insns: b281:01E02230's full-screen veil, (0x90, 0x78, 0x78), zoom from 1.5, fading in until scene
   count 420 (0xA0B2) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b152_01E031F0;

typedef struct {
    f32 s, t;
    Xyz_b152_01E031F0 p;
} Tv_b152_01E031F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b152_01E031F0 v[2];
    u8 tail[0x20];
} Tex_b152_01E031F0;

typedef struct {
    u8 pad0[0xA0B2];
    s16 count;
} Ctx_b152_01E031F0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b152_01E031F0;

static s32 func_01E031F0_b152(Ctx_b152_01E031F0 *g, Fx_b152_01E031F0 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b152_01E031F0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.5f;
        o->mode = 2;
    }
    ((Tex_b152_01E031F0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b152_01E031F0 *)(s32)&pk)->size = 5;
    ((Tex_b152_01E031F0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b152_01E031F0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x90;
    pk.g = 0x78;
    pk.b = 0x78;
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
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->count < 420) {
        if (o->col[3] < 0x50) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b152:01E03400, 202 insns, 2 copies: a full-screen red overlay drawn into the scene's packet (b016:01E02D30 family):
   one sprite over the whole screen, its texture window inset by the slot's width and height, which grow by a
   random 23..37 a frame; full on the first frame, then fades out */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b152_01E03400;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b152_01E03400 p;
    } v[2];
} Pkt_b152_01E03400;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b152_01E03400;

typedef struct {
    u8 pad0[0xA008];
    Pkt_b152_01E03400 *pkt;
} Scene_b152_01E03400;

static s32 func_01E03400_b152(Scene_b152_01E03400 *s, Slot_b152_01E03400 *o) {
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
        func_001076F0(o->c0, 0x40, 8, 8);
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
    o->w += (s16)(func_0019A5C8() % 15 + 23);
    o->h += (s16)(func_0019A5C8() % 15 + 23);
    if (o->t <= 0) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b152:01E03730 (b152), 551 insns, 1 copy: scene manager: setup (six func_001F5560 ids, one type-4 and four
   type-5 textures, two s8 jitter tables, 36 random 0..7 values), else run the 130 slot handlers (counting the
   01E03400 ones, then its pass) and draw eight slot kinds; returns by scene frame */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b152_01E03730;

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
        Rect_b152_01E014F0 rc;
    } c;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b152_01E03730 fx[130];
    u8 pad3B80[0x30];
    Vec4f pt;
    u8 pad3BC0[0x9FD0 - 0x3BC0];
    s32 tex[4];
    u8 pad9FE0[0x10];
    s32 count;
    u8 pad9FF4[8];
    s32 ot;
    u8 padA000[0x30];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padA03C[4];
    s16 cam;
    u8 padA042[0xE];
    s16 rnd[0x24];
    u8 padA098[0x16];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b152_01E03730;

static s32 func_01E03730_b152(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b152_01E01640();
    extern void b152_01E04160();
    extern void b152_01E04530();
    extern void b152_01E01190();
    Scene_b152_01E03730 *g = (Scene_b152_01E03730 *)arg0;
    s16 m;
    s16 n;
    Vec4f v;
    Rect_b152_01E014F0 rc;
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xA420);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x1C8;
        g->jA = func_001F5560(func_001F53A0(), 0x01, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x63, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x62, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 4; i++) {
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
        for (k = 0; k < 0x24; k++) {
            g->rnd[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    b152_01E01640(g, 0);
    for (k = 0; k < 130; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03400_b152) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    m++;
                }
            }
        }
    }
    for (k = 0; k < 130; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01E60_b152) {
                g->tex88 = g->tex[0];
                rc = func_01E014F0_b152(0, g->fx[k].h56, 0);
                g->c.rc = rc;
                g->hBE = g->rnd[g->fx[k].h52];
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b152((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02530_b152) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b152((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02680_b152) {
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->hB8 = 3;
                g->hB0 = 0;
                func_01E00BE0_b152((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02820_b152) {
                g->tex88 = g->tex[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->c.h[0] = g->fx[k].h56 << 5;
                g->c.h[1] = 0;
                g->c.h[2] = 0x20;
                g->c.h[3] = 0x3F;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b152((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02990_b152) {
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                b152_01E04160(g, &g->fx[k], pk, 0);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02AF0_b152) {
                g->hB8 = 0x18;
                b152_01E01190(g, &g->fx[k], 0x21, &g->pt);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D90_b152) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm5;
                g->hB8 = 8;
                g->hB0 = 0;
                func_01E00BE0_b152((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F70_b152) {
                g->tex88 = g->tex[1];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm6;
                g->hB8 = 8;
                g->hB0 = 0;
                func_01E00BE0_b152((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (m) {
        b152_01E04530(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x163) {
        return 1;
    }
    if (g->frame == 0x1C2) {
        return 3;
    }
    if (g->frame > 0x16D && g->frame < 0x1BD) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b152:01E03FD0, 98 insns, 2 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x82 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b152_01E03FD0 {
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
} Slot_b152_01E03FD0;

typedef struct Obj_b152_01E03FD0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b152_01E03FD0 slots[0x82];
    u8 padB[0x9ff4 - 0x2a0 - 0x82 * 0x70];
    u8 rgba[4];
    u8 padC[0xa0aa - 0x9ff4 - 4];
    s16 fB2B0;
} Obj_b152_01E03FD0;

static s32 func_01E03FD0_b152(Obj_b152_01E03FD0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b152_01E03FD0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x82; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x82;
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

/* shape b152:01E04160, 244 insns (B152PAINT_RAIN30): b597:01E03FE0's mirrored halves at the ctx point (ctx+0x3BB0),
   scale 0.1, size o->f48, drawn as a textured quad packet of its own (12 regs: colour o+0x60 at every corner, q and
   the corner's s/t divided by its depth, far z, no fog), texture ctx+0x9FDC, ot ctx+0x9FFC */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b152_01E04160;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b152_01E04160;

typedef struct {
    Rgbaq_b152_01E04160 c;
    f32 s, t;
    Xyz_b152_01E04160 xyz;
} Vtx_b152_01E04160;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b152_01E04160 v[4];
    u8 tail[0x20];
} Pkt_b152_01E04160;

static inline void tag_b152_01E04160(Pkt_b152_01E04160 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

typedef struct {
    u8 pad0[0x3BB0];
    Vec4f pt;
    u8 pad3BC0[0x9FDC - 0x3BC0];
    s32 tex;
    u8 pad9FE0[0x9FFC - 0x9FE0];
    s32 ot;
} Ctx_b152_01E04160;

typedef struct {
    u8 pad0[0x48];
    f32 size;
    u8 pad4C[0x60 - 0x4C];
    u8 col[8];
} Fx_b152_01E04160;

static void func_01E04160_b152(Ctx_b152_01E04160 *g, Fx_b152_01E04160 *o) {
    extern Rgbaq_b152_01E04160 func_00107740(void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    f32 d[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b152_01E04160 pkt;
    s32 k;

    tag_b152_01E04160((Pkt_b152_01E04160 *)(u32)&pkt, 0x34, 0xC, ((u64)0x4214 << 32) | 0x21421421);
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = 0;
    pos.x = g->pt.x;
    pos.y = g->pt.y;
    pos.z = g->pt.z;
    func_00108EF0(m, &sc, rot, &pos);
    for (k = 0; k < 2; k++) {
        func_00108CE0(q, o->size, o->size);
        if (k == 0) {
            q[1].x = 0.0f;
            q[3].x = 0.0f;
        } else if (k == 1) {
            q[1].x = 0.0f;
            q[3].x = 0.0f;
            q[0].x *= -1.0f;
            q[2].x *= -1.0f;
        }
        if (func_00205440(&q[0], m, &pkt.v[0].xyz, &d[0]) != 0 &&
            func_00205440(&q[1], m, &pkt.v[1].xyz, &d[1]) != 0 &&
            func_00205440(&q[2], m, &pkt.v[2].xyz, &d[2]) != 0 &&
            func_00205440(&q[3], m, &pkt.v[3].xyz, &d[3]) != 0) {
            pkt.v[0].c = func_00107740(o->col);
            pkt.v[1].c = func_00107740(o->col);
            pkt.v[2].c = func_00107740(o->col);
            pkt.v[3].c = func_00107740(o->col);
            pkt.v[0].c.q = 1.0f / d[0];
            pkt.v[1].c.q = 1.0f / d[1];
            pkt.v[2].c.q = 1.0f / d[2];
            pkt.v[3].c.q = 1.0f / d[3];
            pkt.v[0].xyz.z = 0xFFFFFF;
            pkt.v[0].xyz.f = 0;
            pkt.v[1].xyz.z = 0xFFFFFF;
            pkt.v[1].xyz.f = 0;
            pkt.v[2].xyz.z = 0xFFFFFF;
            pkt.v[2].xyz.f = 0;
            pkt.v[3].xyz.z = 0xFFFFFF;
            pkt.v[3].xyz.f = 0;
            pkt.v[0].s = 0.0f / d[0];
            pkt.v[0].t = 0.0f / d[0];
            pkt.v[1].s = 1.0f / d[1];
            pkt.v[1].t = 0.0f / d[1];
            pkt.v[2].s = 0.0f / d[2];
            pkt.v[2].t = 1.0f / d[2];
            pkt.v[3].s = 1.0f / d[3];
            pkt.v[3].t = 1.0f / d[3];
            func_00208700(&pkt, g->tex, 0);
            func_002075F0(&pkt, g->ot, 0);
        }
    }
}

/* shape b152:01E04530, 153 insns: the scene's draw pass: hands the scene two stack packets (a 5-reg sprite header and a
   12-reg strip header), opens a draw context, takes the camera's light, projects the camera point (raised or lowered
   30 by the scene flag) for the scene depth, then draws every live effect whose handler is the module's 0x1E03400 and
   closes the context at that depth */

typedef struct {
    s16 n;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b152_01E04530;

typedef struct {
    Hdr_b152_01E04530 h;
    u8 body[0x30];
} Pk1_b152_01E04530;

typedef struct {
    Hdr_b152_01E04530 h;
    u8 body[0x10];
} Pk2_b152_01E04530;

typedef struct {
    u8 pad0[0x44];
    s32 fn;
    u8 pad48[0x10];
    s16 live;
    u8 pad5A[0x16];
} Ent_b152_01E04530;

typedef struct {
    u8 pad0[0x2A0];
    Ent_b152_01E04530 ent[130];
    u8 pad3B80[0x6484];
    s32 ctx;
    Pk1_b152_01E04530 *pk1;
    Pk2_b152_01E04530 *pk2;
    u8 padA010[8];
    f32 depth;
    u8 padA01C[0x92];
    s16 flag;
} Scene_b152_01E04530;

static void func_01E04530_b152(Scene_b152_01E04530 *g) {
    extern void b152_01E03400(Scene_b152_01E04530 *, Ent_b152_01E04530 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00205440(void *, void *, void *, f32 *);
    extern void func_00207FD0(s32, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f v;
    struct {
        u64 tag;
        Pk1_b152_01E04530 pk;
        u8 o98[8];
    } b1;
    u8 oA0[0x10];
    Pk2_b152_01E04530 pk2;
    u8 out[0x70];
    s32 i;
    s32 ot;

    g->pk1 = &b1.pk;
    g->pk2 = &pk2;
    g->ctx = func_00207F60();
    g->pk1->h.count = 0x26;
    g->pk1->h.n = 5;
    g->pk1->h.regs = 0x42421;
    g->pk1->h.pad = 0;
    g->pk2->h.count = 0x34;
    g->pk2->h.n = 0xC;
    g->pk2->h.regs = 0x21421421 | ((s64)0x4214 << 32);
    g->pk2->h.pad = 0;
    func_00208460();
    func_002086D0(g->pk1, 0x48 | ((s64)0x80 << 32));
    func_001F7060(func_001F53A0(), 0, b1.o98, oA0);
    func_002086D0(g->pk2, 0x48 | ((s64)0x80 << 32));
    func_001F5F90(func_001F53A0(), &v);
    if (g->flag != 0) {
        v.z += 30.0f;
    } else {
        v.z -= 30.0f;
    }
    func_00205440(&v, NULL, out, &g->depth);
    func_00208460();
    for (i = 0; i < 130; i++) {
        if (g->ent[i].live != 0 && g->ent[i].fn == (s32)b152_01E03400) {
            b152_01E03400(g, &g->ent[i]);
        }
    }
    ot = (s32)func_00207500();
    func_00207FD0(g->ctx, ot, func_001A23B0(g->depth));
}
