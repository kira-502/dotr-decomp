#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b191(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

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

static void func_01E00110_b191(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b191(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E00D10_b191(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b191((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b191((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b191 in the
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

static void func_01E012C0_b191(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b191((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b191:01E01580, 316 insns: the b191 scene's script: on tick 190 it spawns the opening set (02050 twice, 02E20,
   02850 twice, 02D30); every third tick from 166 to 290 two trail sparks (01A70) at the joint with a 40-step ring
   index, then a 02B50; every tenth tick from 196 to 260 two 021D0 at the joint and 02600 on every tick there; on tick
   188 twenty 021D0 + 02600 pairs; on ticks 131/141/151/161 twenty 029D0 at each of two more joints */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xA8BC - 0x260];
    s16 joint;
    u8 padA8BE[4];
    s16 jointL;
    s16 jointR;
    u8 padA8C6[0x24];
    s16 ring;
    s16 ringNext;
    u8 padA8EE[4];
    s16 tick;
} Ctx_b191_01E01580;

static s32 func_01E01A70_b191();
static s32 func_01E02050_b191();
static s32 func_01E021D0_b191();
static s32 func_01E02600_b191();
static s32 func_01E02850_b191();
static s32 func_01E029D0_b191();
static s32 func_01E02B50_b191();
static s32 func_01E02D30_b191();
static s32 func_01E02E20_b191();
static s32 func_01E03AD0_b191();

static void func_01E01580_b191(Ctx_b191_01E01580 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    g->tick++;
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02050_b191, 0);
    }
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02050_b191, 0);
    }
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02E20_b191, 0);
    }
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02850_b191, 0);
    }
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02850_b191, 0);
    }
    if (g->tick == 0xBE) {
        func_01E03AD0_b191(g, func_01E02D30_b191, 0);
    }
    if (g->tick >= 0xA6 && g->tick < 0x123 && g->tick % 3 == 1) {
        if (g->tick < 100) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->joint, &g->pos);
            g->ring = g->ringNext;
            func_01E03AD0_b191(g, func_01E01A70_b191, 0);
            g->ringNext++;
            if (g->ringNext >= 40) {
                g->ringNext = 0;
            }
        }
        func_01E03AD0_b191(g, func_01E02B50_b191, 0);
    }
    if (g->tick >= 0xC4 && g->tick < 0x105 && g->tick % 10 == 1) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->joint, &g->pos);
            func_01E03AD0_b191(g, func_01E021D0_b191, 0);
        }
    }
    if (g->tick >= 0xC4 && g->tick < 0x105) {
        func_01E03AD0_b191(g, func_01E02600_b191, 0);
    }
    if (g->tick == 0xBC) {
        for (i = 0; i < 20; i++) {
            func_001F5620(func_001F53A0(), g->joint, &g->pos);
            func_01E03AD0_b191(g, func_01E021D0_b191, 0);
            func_01E03AD0_b191(g, func_01E02600_b191, 0);
        }
    }
    if (g->tick == 0x83 || g->tick == 0x8D || g->tick == 0x97 || g->tick == 0xA1) {
        for (i = 0; i < 20; i++) {
            func_001F5620(func_001F53A0(), g->jointL, &g->pos);
            func_01E03AD0_b191(g, func_01E029D0_b191, 0);
        }
        for (i = 0; i < 20; i++) {
            func_001F5620(func_001F53A0(), g->jointR, &g->pos);
            func_01E03AD0_b191(g, func_01E029D0_b191, 0);
        }
    }
}

/* shape b191:01E01A70 (B191_OBJ_MOVE_2_), 373 insns, 1 copy: a blue double trail band: on start radius 18..67 and 18
   (the second row 30 degrees back, 50 up), grey 0x58, both trails (0x280-byte slots at 0x4470, 20
   points) filled with the start point; fades in by 0x15 while tick < 7 and the scene count >= 0xBF, else out by 5;
   each tick the heading turns 12 and both trails take a new point, the second -5..39 (every 10th tick) or -5..-1 up,
   colour blinks blue, band count to 14; from scene count 0x123 the tick is held at 7 */

typedef struct {
    Vec4f a[20];
    Vec4f b[20];
} Trail_b191_01E01A70;

typedef struct {
    u8 pad0[0x4470];
    Trail_b191_01E01A70 slot[1];
    u8 pad46F0[0xA8F2 - 0x46F0];
    s16 count;
    u8 padA8F4[0xAAF4 - 0xA8F4];
    u8 sin[4];
} Game_b191_01E01A70;

typedef struct {
    u8 pad0[6];
    s16 n;
    s16 h8;
    u8 padA[0x2A];
    f32 y;
    u8 pad38[0x10];
    f32 r;
    f32 r2;
    s16 idx;
    s16 h52;
    s16 t;
    s16 h56;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b191_01E01A70;

static s32 func_01E01A70_b191(Game_b191_01E01A70 *g, Obj_b191_01E01A70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    Vec4f v;
    Vec4f cam;
    f32 f;
    f32 r;
    Vec4f *p;
    s16 i;

    func_001F5F90(func_001F53A0(), &cam.x);
    cam.x = cam.x;
    cam.z = cam.z;
    if (o->mode == 1) {
        o->y = 50.0f;
        f = o->y;
        o->h8 = func_0019A5C8() % 2;
        o->r = func_0019A5C8() % 50 + 18;
        o->r2 = 18.0f;
        func_001076F0(o->col2, 0x58, 0x58, 0x58);
        v.y = 0.0f;
        o->ang = func_0019A5C8() % 360;
        if (v.x) {
            r = o->r;
        } else {
            r = o->r;
        }
        v.z = r * func_00108030(g->sin, o->ang, 0);
        v.x = r * func_00108030(g->sin, o->ang, 1);
        for (i = 0, p = g->slot[o->idx].a; i < 19; i++, p++) {
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
        }
        if (v.x) {
            r = o->r2;
        } else {
            r = o->r2;
        }
        v.z = r * func_00108030(g->sin, o->ang - 30, 0);
        v.x = r * func_00108030(g->sin, o->ang - 30, 1);
        v.y = f;
        for (i = 0, p = g->slot[o->idx].b; i < 19; i++, p++) {
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
        }
        o->n = 2;
        o->col[3] = 0;
        o->h8 = 0;
        o->h56 = 0;
        o->r = 5.0f;
        o->mode = 2;
    }
    if (o->t < 7 && g->count >= 0xBF) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->t % 10 == 1) {
        f = func_0019A5C8() % 45 - 5;
    } else {
        f = func_0019A5C8() % 5 - 5;
    }
    o->ang += 12;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    v.y = 0.0f;
    if (v.x) {
        r = o->r;
    } else {
        r = o->r;
    }
    v.z = r * func_00108030(g->sin, o->ang, 0);
    v.x = r * func_00108030(g->sin, o->ang, 1);
    func_01E00080_b191(&g->slot[o->idx].a[19], 20, 0, &v);
    v.y = 5.0f + f;
    if (v.x) {
        r = o->r2;
    } else {
        r = o->r2;
    }
    v.z = r * func_00108030(g->sin, o->ang - 30, 0);
    v.x = r * func_00108030(g->sin, o->ang - 30, 1);
    func_01E00080_b191(&g->slot[o->idx].b[19], 20, 0, &v);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x10, 0x10, 0x50);
    } else {
        func_001076F0(o->col, 8, 8, 0x40);
    }
    if (o->t != 0) {
        if (o->n < 14) {
            o->n++;
        }
    }
    o->t++;
    if (g->count > 0x122) {
        o->t = 7;
    }
    return 0;
}

/* shape b191:01E02050, 93 insns: a grey-blue flickering flash on the model joint: f4C 165, size 10x10; second alpha up by 24 to 0xC0 until the game
   timer reaches 0x122, then down by 12 until it ends; second colour flickers by the timer's parity; random turn */

typedef struct {
    u8 pad0[0xA8BC];
    s16 joint;
    u8 padA8BE[0x34];
    s16 timer;
} Game_b191_01E02050;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
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
} Obj_b191_01E02050;

static s32 func_01E02050_b191(Game_b191_01E02050 *g, Obj_b191_01E02050 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
        o->hold = 0x8C;
        o->f4C = 165.0f;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x122) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x18;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (g->timer % 2 == 1) {
        func_001076F0(o->c1, 0x50, 0x50, 0x80);
    } else {
        func_001076F0(o->c1, 0x60, 0x60, 0xA0);
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b191:01E021D0, 266 insns: a grey wisp circling the model: random radius 5..24, sheet 0..3, start jitter
   +-8 in x and z, turn rate -8..7, rise (10..49) / 80 for 20 ticks while it grows; then it glides for 45 ticks toward
   its spot on the circle around the model (radius 0x4C, angle 0x5C), then rides the circle turning 0x0E a tick;
   fades in for 150 ticks, then fades by 9 while shrinking */

typedef struct {
    u8 pad0[0xA8BC];
    s16 joint;
    u8 padA8BE[0xAAF4 - 0xA8BE];
    u8 trig[1];
} G_b191_01E021D0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b191_01E021D0;

static s32 func_01E021D0_b191(G_b191_01E021D0 *g, Fx_b191_01E021D0 *o) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, f32 *);
    f32 a[4];
    f32 b[4];
    f32 d;

    if (o->state == 1) {
        o->h8 = 0;
        o->hA = o->h8 * 4;
        o->f48 = 0.0f;
        o->f4C = 5.0f + (f32)((func_0019A5C8() >> 4) % 20);
        o->h56 = (func_0019A5C8() >> 4) % 4;
        d = func_0019A5C8() % 160 - 80;
        d /= 10.0f;
        o->x += d;
        d = func_0019A5C8() % 160 - 80;
        d /= 10.0f;
        o->z += d;
        o->hE = func_0019A5C8() % 16 - 8;
        o->f34 = (func_0019A5C8() >> 4) % 40 + 10;
        o->f34 /= 80.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        func_001F5F90(func_001F5380(), a);
        a[0] += o->f4C * func_00108030(g->trig, o->h5C, 1);
        *(f32 *)(u32)&a[2] += o->f4C * func_00108030(g->trig, o->h5C, 0);
        func_001F5620(func_001F53A0(), g->joint, b);
        o->f3C = (*(f32 *)(u32)&a[2] - o->z) / 45.0f;
        o->f30 = (a[0] - o->x) / 45.0f;
    }
    if (o->t < 150) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->h8 != 0) {
            o->h8 -= 4;
        }
        o->hA += 16;
    }
    if (o->t < 20) {
        o->y += o->f34;
        o->h8++;
        o->hA = o->h8 * 4;
        o->f48 += 0.3f;
    } else if (o->t < 65) {
        o->z += o->f3C;
        o->x += o->f30;
    } else {
        func_001F5F90(func_001F5380(), a);
        a[0] += o->f4C * func_00108030(g->trig, o->h5C, 1);
        *(f32 *)(u32)&a[2] += o->f4C * func_00108030(g->trig, o->h5C, 0);
        o->x = a[0];
        o->z = *(f32 *)(u32)&a[2];
        o->h5C += o->hE;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    o->h5A += 2;
    return 0;
}

/* shape b191:01E02600, 148 insns: a blue spark at a random position: f48 10..19 (+1 per tick), variant 0..3, f50
   10..29, random f5A, spin 10..21, f8 1..8, life 2..4; alpha 0x80 during the life, then fades by 11 and stops;
   the colour flickers between (0x20,0x20,0x80) and (0x30,0x30,0xA0); f50 grows by the spin each tick */

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
} Fx_b191_01E02600;

static s32 func_01E02600_b191(s32 arg0, Fx_b191_01E02600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 20 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 12 + 10;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->col, 0x30, 0x30, 0xA0);
    }
    o->f50 += o->spin;
    o->f48 += 1.0f;
    o->tick++;
    return 0;
}

/* shape b191:01E02850, 93 insns: a dark-blue flickering flash on the model joint (b485:01E01A60 shape): second alpha up by 0x60 until the game
   timer reaches 10 */

typedef struct {
    u8 pad0[0xA8BC];
    s16 joint;
    u8 padA8BE[0x34];
    s16 timer;
} Game_b191_01E02850;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
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
} Obj_b191_01E02850;

static s32 func_01E02850_b191(Game_b191_01E02850 *g, Obj_b191_01E02850 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
        o->hold = 0x8C;
        o->f4C = 165.0f;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0xA) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xD) {
        o->c1[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (g->timer % 2 == 1) {
        func_001076F0(o->c1, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->c1, 0x30, 0x30, 0xA0);
    }
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b191:01E029D0, 93 insns: a grey swaying spark (b354:01E01C30 shape): size 35, random sub-frame 2..4 and angle; alpha up by
   0x40 to 0x80 for 10 frames, then down by 9 until it ends; sways by 2.2 sin / cos of its angle in z and x; random turn */

typedef struct {
    u8 pad0[0xAAF4];
    u8 trig[1];
} Game_b191_01E029D0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b191_01E029D0;

static s32 func_01E029D0_b191(Game_b191_01E029D0 *g, Obj_b191_01E029D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->w = 0x23;
        o->h = o->w;
        o->sub = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->state = 2;
        o->ang = (func_0019A5C8() >> 4) % 360;
    }
    if (o->t < 0xA) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->z += 2.2f * func_00108030(g->trig, o->ang, 0);
        o->x += 2.2f * func_00108030(g->trig, o->ang, 1);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b034:01E02290, 120 insns, 2 copies: a grey bloom: set up once (random size 100..129, frame 0..7, angle 100..149, speed
   26..45, life 7..20); fades in for its life, then out; turns for 90 frames and grows 6 a frame for 140 (b225:01E026A0 family, 0x58-state layout) */

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
} Spark_b034_01E02290;

static s32 func_01E02B50_b191(void *arg0, Spark_b034_01E02290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 100;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0xA0, 0xA0, 0xA0);
        o->ang = func_0019A5C8() % 50 + 100;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 26;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 14 + 7;
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

/* shape b191:01E02D30, 58 insns: volume fade by game state (b058:01E017A0 shape, layout at 0x50): state at 0xA890 limit
   0x1E, down 10 to 0x20, up 10 to 0x80 where the fade ends; state 2 plays at 0x80 */

typedef struct {
    u8 pad[0xA890];
    s32 state;
} Game_b191_01E02D30;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b191_01E02D30;

static s32 func_01E02D30_b191(Game_b191_01E02D30 *g, Fade_b191_01E02D30 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
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
    if (g->state == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b191:01E02E20, 232 insns: b485:01E02690's blue-grey screen veil with the scene time at g+0xA8F2 and the
   trig table at g+0xAAF4: bias swings 161..259, restarts at 260, second bias 261..459; tint 0x90/0x70/0x80 at time 241;
   before time 400 the alpha rises by 10 to 0x50 before 216 and falls by 6 to 64 after 216, then fades by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b191_01E02E20;

typedef struct {
    f32 s, t;
    Xyz_b191_01E02E20 p;
} Tv_b191_01E02E20;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b191_01E02E20 v[2];
    u8 tail[0x20];
} Tex_b191_01E02E20;

typedef struct {
    u8 pad0[0xA8F2];
    s16 time;
    u8 padA8F4[0xAAF4 - 0xA8F4];
    u8 trig[1];
} Ctx_b191_01E02E20;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    s16 ang2;
    u8 pad5E[2];
    u8 col[4];
} Fx_b191_01E02E20;

static s32 func_01E02E20_b191(Ctx_b191_01E02E20 *g, Fx_b191_01E02E20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    Tex_b191_01E02E20 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0x80, 0x80, 0xB0);
        o->mode = 2;
    }
    z = 10.0f;
    ((Tex_b191_01E02E20 *)(s32)&pk)->flags = 0x26;
    ((Tex_b191_01E02E20 *)(s32)&pk)->size = 5;
    ((Tex_b191_01E02E20 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b191_01E02E20 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].s = (o->f4C + (o->f48 + z)) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (o->f4C + (640.0f + o->f48 - z)) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->time > 160 && g->time < 260) {
        o->f48 = 10.0f * func_00108030(g->trig, o->ang, 0);
        o->ang += 10;
    }
    if (g->time == 260) {
        o->ang = 0;
        o->f48 = 10.0f * func_00108030(g->trig, o->ang, 0);
    }
    if (g->time > 260 && g->time < 460) {
        o->f4C = 10.0f * func_00108030(g->trig, o->ang2, 0);
        o->ang2 += 20;
    }
    if (g->time == 241) {
        func_001076F0(o->col, 0x90, 0x70, 0x80);
    }
    if (g->time < 400) {
        if (g->time < 216) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b191", func_01E031C0_b191);

/* shape b191:01E03AD0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b191_01E03AD0 {
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
} Slot_b191_01E03AD0;

typedef struct Obj_b191_01E03AD0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b191_01E03AD0 slots[0x96];
    u8 padB[0xa894 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xa8ea - 0xa894 - 4];
    s16 fB2B0;
} Obj_b191_01E03AD0;

static s32 func_01E03AD0_b191(Obj_b191_01E03AD0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b191_01E03AD0 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b191", func_01E03C60_b191);
