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

static void func_01E00080_b597(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b597 in the
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

static void func_01E00920_b597(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b597((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00BE0_b597(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b597((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b597((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E01190_b597(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static Rect_b152_01E014F0 func_01E014F0_b597(s32 unused, s16 n) {
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

/* shape b597:01E01640 (B597_W_S), 460 insns, 1 copy: the scene script: counts the frame (0xA0B2); frame 1 spawns
   b597:01E03040; from 141 the sizes at 0x9FC0/0x9FC4 grow to 80/50; from 15, 36 sparks (b597:01E01D70) and two
   b597:01E02460 a frame until 200 at random spots round joint 0xA030; frames 80..350 b597:01E025B0 at joint 0xA032;
   frame 30 places the point 0x3BB0 (z +-10 by the flag); frames 280..340 two orbiting b597:01E02750 and a
   b597:01E02EA0; frame 175 the b597:01E02A20 pair and eight b597:01E02CC0 */

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
} Scene_b597_01E01640;

static void func_01E01640_b597(Scene_b597_01E01640 *g) {
    extern void b597_01E01D70();
    extern void b597_01E02460();
    extern void b597_01E025B0();
    extern void b597_01E02750();
    extern void b597_01E02A20();
    extern void b597_01E02CC0();
    extern void b597_01E02EA0();
    extern void b597_01E03040();
    extern s32 b597_01E03E50();
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;

    g->frame++;
    if (g->frame == 1) {
        b597_01E03E50(g, b597_01E03040, 0);
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
    if (g->frame >= 15) {
        if (g->cnt < 36) {
            func_001F5620(func_001F53A0(), g->id, &g->pos);
            g->idx = g->cnt;
            g->pos.y = 30.0f;
            g->pos.x += func_0019A5C8() % 60 - 30;
            g->pos.z += func_0019A5C8() % 60 - 30;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b597_01E03E50(g, b597_01E01D70, 0);
            g->cnt++;
        }
    }
    if (g->frame >= 80 && g->frame < 351) {
        func_001F5620(func_001F53A0(), g->id0, &g->pos);
        b597_01E03E50(g, b597_01E025B0, 0);
    }
    if (g->frame >= 15 && g->frame < 201) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->id, &g->pos);
            g->pos.y = 30.0f;
            g->pos.x += func_0019A5C8() % 60 - 30;
            g->pos.z += func_0019A5C8() % 60 - 30;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b597_01E03E50(g, b597_01E02460, 0);
        }
    }
    if (g->frame == 30) {
        func_001F5620(func_001F53A0(), g->id0, &g->p);
        if (g->flag) {
            g->p.z -= 10.0f;
        } else {
            g->p.z += 10.0f;
        }
        g->p.y += 7.0f;
    }
    g->ang += 5;
    if (g->frame >= 280 && g->frame < 341) {
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
            b597_01E03E50(g, b597_01E02750, 0);
        }
        func_001F5620(func_001F5380(), g->id1, &g->pos);
        g->pos.y += func_0019A5C8() % 5;
        b597_01E03E50(g, b597_01E02EA0, 0);
    }
    if (g->frame == 175) {
        g->idx = 1;
        b597_01E03E50(g, b597_01E02A20, 0);
        g->idx = 2;
        b597_01E03E50(g, b597_01E02A20, 0);
        g->pos = g->p;
        for (i = 0; i < 8; i++) {
            b597_01E03E50(g, b597_01E02CC0, 0);
        }
    }
}

/* shape b597:01E01D70 (B597_OBJ_MOVE_4_), 444 insns, 1 copy: B152_OBJ_MOVE_4_ ring spark with frame bounds
   350/35/78/108/205/221/235; the orbit turns -10 or +10 by scene flag hA0AE */

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
    u8 padA0A6[0xA0AE - 0xA0A6];
    s16 hA0AE;
    u8 padA0B0[0xA0B2 - 0xA0B0];
    s16 frame;
    u8 padA0B4[0xA2B4 - 0xA0B4];
    u8 tab[1];
} Ctx_b597_01E01D70;

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
} Fx_b597_01E01D70;

static s32 func_01E01D70_b597(Ctx_b597_01E01D70 *g, Fx_b597_01E01D70 *o) {
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
    if (g->frame < 350) {
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
    if (t > 10 && t < 35) {
        o->pos.y += o->v.y;
    } else if (t >= 78 && t < 108) {
        if (t == 78) {
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
    if (o->tick < 205 && g->frame >= 221 && g->frame < 360) {
        func_001F5620(func_001F53A0(), g->id0, &v[1]);
        v[0].x = 15.0f * func_00108030(g->tab, o->ang, 1);
        v[0].y = 15.0f * func_00108030(g->tab, o->ang, 0);
        o->pos.x = g->pos.x + v[0].x;
        o->pos.y = g->pos.y + v[0].y;
        o->ang += 2;
    }
    if (o->tick >= 205) {
        if (o->tick == 205) {
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
        if (o->tick < 235) {
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
            if (g->hA0AE) {
                o->ang -= 10;
            } else {
                o->ang += 10;
            }
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

static s32 func_01E02460_b597(void *arg0, Obj_b152_01E02530 *o) {
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

static s32 func_01E025B0_b597(s32 unused, Obj_b152_01E02680 *o) {
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

/* shape b597:01E02750, 90 insns: on start 0x8/0xA = 30/60, f48 0, variant 0..7, f34 0.5, both colours (0x20, 0x20,
   0x80) (second alpha 0), 0x5C = 0; both alphas grow by 0x40 (below 0x80) for 20 ticks, then the first fades by 6
   twice a tick and ends it; after the first tick 0x8/0xA grow by 2 and f14 by f34; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[8];
    f32 f14;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b597_01E02750;

static s32 func_01E02750_b597(s32 arg0, Fx_b597_01E02750 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 30;
        o->fA = 60;
        o->f48 = 0.0f;
        o->f56 = func_0019A5C8() % 8;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        func_001076F0(o->col2, 0x20, 0x20, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        o->f5C = 0;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        }
    }
    if (o->tick != 0) {
        o->f8 += 2;
        o->fA += 2;
        o->f14 += o->f34;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
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

static s32 func_01E028C0_b597(void *arg0, Obj_b152_01E02990 *o) {
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

/* shape b597:01E02A20, 168 insns: b152:01E02AF0 with kind 2 white over pink (0xFF, 0x80, 0x80) */

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
} Fx_b597_01E02A20;

static s32 func_01E02A20_b597(s32 arg0, Fx_b597_01E02A20 *o) {
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
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
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

static s32 func_01E02CC0_b597(void *arg0, Spark_b152_01E02D90 *o) {
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

static s32 func_01E02EA0_b597(s32 arg0, Fx_b152_01E02F70 *o) {
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

/* shape b597:01E03040, 130 insns: b594:01E02CB0 with a bluish 0x78/0x78/0x90 sprite starting at 1.5, fading in while the scene timer (s32 at ctx+0x9FF0) is past 20, out after */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b597_01E03040;

typedef struct {
    f32 s, t;
    Xyz_b597_01E03040 p;
} Tv_b597_01E03040;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b597_01E03040 v[2];
    u8 tail[0x20];
} Tex_b597_01E03040;

typedef struct {
    u8 pad0[0x9FF0];
    s32 timer;
} Ctx_b597_01E03040;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b597_01E03040;

static s32 func_01E03040_b597(Ctx_b597_01E03040 *g, Fx_b597_01E03040 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b597_01E03040 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.5f;
        o->mode = 2;
    }
    ((Tex_b597_01E03040 *)(s32)&pk)->flags = 0x26;
    ((Tex_b597_01E03040 *)(s32)&pk)->size = 5;
    ((Tex_b597_01E03040 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b597_01E03040 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0x78;
    pk.b = 0x90;
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
    if (g->timer > 20) {
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

static s32 func_01E03250_b597(Scene_b152_01E03400 *s, Slot_b152_01E03400 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b597", func_01E03580_b597);

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

static s32 func_01E03E50_b597(Obj_b152_01E03FD0 *obj, s32 arg1, s32 arg2) {
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

/* shape b597:01E03FE0, 227 insns: b573:01E04B60's mirrored sprite halves with the ctx point at ctx+0x3BB0,
   a float size o->f48, colour o+0x60, texture ctx+0x9FDC, ot ctx+0x9FFC and rot[1] cleared */

typedef struct {
    f32 u, v;
} Uv_b597_01E03FE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b597_01E03FE0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b597_01E03FE0 uv;
    u64 pad18;
    Xyz_b597_01E03FE0 v[4];
} Pk_b597_01E03FE0;

typedef struct {
    u8 pad0[0x3BB0];
    Vec4f pt;
    u8 pad3BC0[0x9FDC - 0x3BC0];
    s32 tex;
    u8 pad9FE0[0x9FFC - 0x9FE0];
    s32 ot;
} Ctx_b597_01E03FE0;

typedef struct {
    u8 pad0[0x48];
    f32 size;
    u8 pad4C[0x60 - 0x4C];
    u8 col[8];
} Fx_b597_01E03FE0;

static void func_01E03FE0_b597(Ctx_b597_01E03FE0 *g, Fx_b597_01E03FE0 *o, Pk_b597_01E03FE0 *p) {
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 depth[4];
    Rect_b003_01E00080 r __attribute__((aligned(16)));
    f32 m[16];
    s32 rot[4];
    Uv_b597_01E03FE0 uv __attribute__((aligned(8)));

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    func_00107740(&uv, o->col);
    p->uv = uv;
    r.x = 1;
    r.y = 1;
    r.w = 62;
    r.h = 127;
    func_01E00080_b597((Pk_b003_01E00080 *)p, &r, 0);
    func_00208700(p, g->tex, 1);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = 0;
    pos.x = g->pt.x;
    pos.y = g->pt.y;
    pos.z = g->pt.z;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    *(f32 *)(u32)&quad[1].x = 0.0f;
    *(f32 *)(u32)&quad[3].x = 0.0f;
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0(p, g->ot, 0);
        func_002075F0(p, g->ot, 0);
    }
    func_00108CE0(quad, o->size, o->size);
    *(f32 *)(u32)&quad[1].x = 0.0f;
    *(f32 *)(u32)&quad[3].x = 0.0f;
    quad[0].x *= -1.0f;
    quad[2].x *= -1.0f;
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0(p, g->ot, 0);
        func_002075F0(p, g->ot, 0);
    }
}
