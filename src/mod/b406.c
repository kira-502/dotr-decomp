#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b406(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b406(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b406(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b082_01E00920;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0x0E];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b082_01E00920;

static void func_01E00B80_b406(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
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
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    i = 0;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
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

static void func_01E00FE0_b406(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b406((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b406((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b406:01E01590, 288 insns, 1 copy (B406_W_S): the module's scene step: counts frames; the effect point follows
   joint A's x and joint B's z (from frame 100 it drifts 0.08 / 4.5 a frame toward the side the scene faces), copied to
   the second point until 133 and taking B's height until 183; until 191 two glints at joints B and C, from 171 the
   spawn point follows it with sparks until 250 and a radius growing 10 to 800; one-off spawns at 75, 100, 133, 170 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x7240];
    Vec4f pt;
    Vec4f pt2;
    u8 pad74C0[0x180];
    f32 radius;
    u8 pad7644[0x10];
    s16 jointB;
    s16 jointC;
    s16 jointA;
    u8 pad765A[0x28];
    s16 kind;
    u8 pad7684[2];
    s16 side;
    u8 pad7688[2];
    s16 frame;
} Scene_b406_01E01590;

static void func_01E01590_b406(Scene_b406_01E01590 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, Vec4f *);
    extern s32 func_01E03640_b406();
    extern s32 func_01E01A10_b406();
    extern s32 func_01E01BC0_b406();
    extern s32 func_01E01DA0_b406();
    extern s32 func_01E022D0_b406();
    extern s32 func_01E027F0_b406();
    extern s32 func_01E02980_b406();
    extern s32 func_01E02B80_b406();
    extern s32 func_01E02CF0_b406();
    extern s32 b406_01E02630();
    Vec4f a;
    Vec4f b[2];

    g->frame++;
    func_001F5620(func_001F53A0(), g->jointA, &a);
    func_001F5620(func_001F53A0(), g->jointB, b);
    g->pt.x = a.x;
    if (g->frame < 100) {
        g->pt.z = b[0].z;
    } else if (g->frame < 133) {
        if (g->side != 0) {
            g->pt.z -= 0.08f;
        } else {
            g->pt.z += 0.08f;
        }
    } else if (g->frame < 170) {
        if (g->side != 0) {
            g->pt.z -= 4.5f;
        } else {
            g->pt.z += 4.5f;
        }
    }
    if (g->frame < 133) {
        g->pt2 = g->pt;
    }
    if (g->frame < 183) {
        g->pt.y = b[0].y;
    }
    if (g->frame < 191) {
        func_001F5620(func_001F53A0(), g->jointB, &g->pos);
        func_01E03640_b406(g, func_01E01A10_b406, 0);
        func_001F5620(func_001F53A0(), g->jointC, &g->pos);
        func_01E03640_b406(g, func_01E01A10_b406, 0);
    }
    if (g->frame > 170) {
        g->pos = g->pt;
        if (g->frame < 250) {
            func_01E03640_b406(g, func_01E01BC0_b406, 0);
        }
        if (g->radius < 800.0f) {
            g->radius += 10.0f;
        }
    }
    if (g->frame == 170) {
        g->pos = g->pt;
        func_01E03640_b406(g, func_01E02B80_b406, 0);
        func_01E03640_b406(g, func_01E02B80_b406, 0);
        func_01E03640_b406(g, func_01E01DA0_b406, 0);
        func_01E03640_b406(g, func_01E01DA0_b406, 0);
        func_01E03640_b406(g, func_01E01DA0_b406, 0);
        func_01E03640_b406(g, func_01E01DA0_b406, 0);
        func_01E03640_b406(g, func_01E01DA0_b406, 0);
    }
    if (g->frame == 100) {
        g->kind = 0;
        func_01E03640_b406(g, func_01E02980_b406, 0);
        g->kind = 1;
    }
    if (g->frame == 75) {
        g->kind = 0;
        func_01E03640_b406(g, func_01E027F0_b406, 0);
        g->kind = 1;
        func_01E03640_b406(g, func_01E027F0_b406, 0);
    }
    if (g->frame == 133) {
        func_01E03640_b406(g, b406_01E02630, 0);
        g->kind = 0;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
        g->kind = 1;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
        g->kind = 2;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
        g->kind = 3;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
        g->kind = 4;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
        g->kind = 5;
        func_01E03640_b406(g, func_01E022D0_b406, 0);
    }
    if (g->frame == 170) {
        g->kind = 0;
        func_01E03640_b406(g, func_01E02CF0_b406, 0);
        g->kind = 1;
    }
}

/* shape b084:01E01A20, 107 insns, 2 copies: a grey glint: set up once (size 10, frame 4, random turn on all axes, angle
   10..59, speed 1..3, life 1..3); fades in for its life, then out (b225:01E026A0 family, 0x58-state layout) */

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
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b084_01E01A20;

static s32 func_01E01A10_b406(void *arg0, Spark_b084_01E01A20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->frame = 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = func_0019A5C8() % 50 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x14) {
        o->c0[3] -= 0x13;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b084:01E01BD0, 120 insns, 2 copies: a grey glint: set up once (size 20, frame 4, random turn on all axes, angle from
   the world value / 1.4 plus 0..99, speed 1..3, life 1..3); fades in for its life, then out (b084:01E01A20 twin) (b225:01E026A0 family, 0x58-state layout) */

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
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b084_01E01BD0;

typedef struct {
    u8 pad0[0x7640];
    f32 v;
} World_b084_01E01BD0;

static s32 func_01E01BC0_b406(World_b084_01E01BD0 *w, Spark_b084_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 base;

    base = w->v / 1.4f;
    if (o->state == 1) {
        o->size = 20.0f;
        o->frame = 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = base + func_0019A5C8() % 100;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x14) {
        o->c0[3] -= 0x13;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b084:01E01DB0, 124 insns: a dark spark at a random position: f48 20, f56 4, f50 = game value 0x7640 / 1.4
   plus 0..99, random f5A, spin 20..49, f8 1..8, life 80..82; alpha grows by 0x40 (below 0xC0) during the life,
   then fades by 19 and stops; f50 grows by the spin each tick */

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
} Fx_b084_01E01DB0;

typedef struct {
    u8 pad[0x7640];
    f32 v;
} Game_b084_01E01DB0;

static s32 func_01E01DA0_b406(Game_b084_01E01DB0 *g, Fx_b084_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 base;

    base = g->v / 1.4f;
    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = base + func_0019A5C8() % 100;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 30 + 20;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 80;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    o->f50 += o->spin;
    o->tick++;
    return 0;
}

/* shape b084:01E01FA0, 205 insns, 2 copies: a red spiral trail on a world track (b149:01E01ED0 family): set up once (fills the
   track's 69 points with the head point); the end point circles the head on a widening spiral, rising or sinking
   by the scene flag, while the module's shape b084:01E00080 shifts the track; blinks red each frame */

typedef struct {
    Vec4f p[0x46];
} Track_b084_01E01FA0;

typedef struct {
    u8 pad0[0x1D10];
    Track_b084_01E01FA0 track[0x14];
    u8 pad[0x74A0 - 0x1D10 - 0x14 * 0x460];
    Vec4f head;
    u8 pad74B0[0x10];
    Vec4f end[0x1C];
    u8 pad7680[6];
    s16 rise;
    u8 pad7688[0x204];
    u8 trig[1];
} World_b084_01E01FA0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    u8 pad8[0x28];
    f32 r;
    u8 pad34[0x14];
    f32 size;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Spiral_b084_01E01FA0;

static s32 func_01E01F90_b406(World_b084_01E01FA0 *w, Spiral_b084_01E01FA0 *o) {
    extern void b406_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f *dst;
    s16 i;

    if (o->state == 1) {
        o->frame = 8;
        o->c0[3] = 0;
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x45; i++) {
            dst->x = w->head.x;
            dst->y = w->head.y;
            dst->z = w->head.z;
            dst++;
        }
        w->end[o->idx].x = w->head.x;
        w->end[o->idx].y = w->head.y;
        w->end[o->idx].z = w->head.z;
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->size = 100.0f;
        o->state = 2;
    }
    if (o->frame < 0x44) {
        o->frame++;
    }
    if (o->t < 0x1E) {
        o->c0[3] = 0xC0;
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->size > 0.0f) {
            o->size -= 1.0f;
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0x1F, 0x1F);
    } else {
        func_001076F0(o->c0, 0xF0, 0x10, 0x10);
    }
    if (o->t != 0) {
        if (w->rise != 0) {
            w->end[o->idx].z += 0.5f;
        } else {
            w->end[o->idx].z -= 0.5f;
        }
        w->end[o->idx].x = w->head.x + o->r * func_00108030(w->trig, o->ang, 1);
        w->end[o->idx].y = w->head.y + o->r * func_00108030(w->trig, o->ang, 0);
        o->ang++;
        o->r += 2.0f;
    }
    if (o->t < 0x32) {
        b406_01E00080(&w->track[o->idx].p[0x45], 0x46, 0, &w->end[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b406:01E022D0, 216 insns: b084:01E01FA0 cousin: size 30, alpha held at 0xC0 while the scene clock (0x768A)
   is under 185, blinking red/dark red, the spiral rising 4.5 a frame against the scene flag until the clock reaches 170,
   turning 5 a frame and widening by 1 up to radius 8. As b084:01E01FA0: a red spiral trail on a world track (b149:01E01ED0 family): set up once (fills the
   track's 69 points with the head point); the end point circles the head on a widening spiral, rising or sinking
   by the scene flag, while the module's shape b084:01E00080 shifts the track; blinks red each frame */

typedef struct {
    Vec4f p[0x46];
} Track_b406_01E022D0;

typedef struct {
    u8 pad0[0x1D10];
    Track_b406_01E022D0 track[0x14];
    u8 pad[0x74A0 - 0x1D10 - 0x14 * 0x460];
    Vec4f head;
    u8 pad74B0[0x10];
    Vec4f end[0x1C];
    u8 pad7680[6];
    s16 rise;
    u8 pad7688[2];
    s16 clock;
    u8 pad768C[0x200];
    u8 trig[1];
} World_b406_01E022D0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    u8 pad8[0x28];
    f32 r;
    u8 pad34[0x14];
    f32 size;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Spiral_b406_01E022D0;

static s32 func_01E022D0_b406(World_b406_01E022D0 *w, Spiral_b406_01E022D0 *o) {
    extern void b406_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f *dst;
    s16 i;

    if (o->state == 1) {
        o->frame = 8;
        o->c0[3] = 0;
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x45; i++) {
            dst->x = w->head.x;
            dst->y = w->head.y;
            dst->z = w->head.z;
            dst++;
        }
        w->end[o->idx].x = w->head.x;
        w->end[o->idx].y = w->head.y;
        w->end[o->idx].z = w->head.z;
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->size = 30.0f;
        o->state = 2;
    }
    if (o->frame < 0x44) {
        o->frame++;
    }
    if (w->clock < 185) {
        o->c0[3] = 0xC0;
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->size > 0.0f) {
            o->size -= 1.0f;
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0x10, 0x10);
    } else {
        func_001076F0(o->c0, 0x80, 0x10, 0x10);
    }
    if (o->t != 0) {
        if (w->clock < 170) {
            if (w->rise != 0) {
                w->end[o->idx].z -= 4.5f;
            } else {
                w->end[o->idx].z += 4.5f;
            }
        }
        w->end[o->idx].x = w->head.x + o->r * func_00108030(w->trig, o->ang, 1);
        w->end[o->idx].y = w->head.y + o->r * func_00108030(w->trig, o->ang, 0);
        o->ang += 5;
        if (o->r < 8.0f) {
            o->r += 1.0f;
        }
    }
    if (o->t < 0x32) {
        b406_01E00080(&w->track[o->idx].p[0x45], 0x46, 0, &w->end[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b406:01E02630 (B406_OBJ_MOVE_10_), 111 insns, 1 copy (-O3,p): the spiral trail of b084:01E01FA0 in red
   (colours 0x80,0x10,0x10 and 0xFF,0x10,0x10), with this module's own sizes and timings; the source of shape
   b084:01E022E0, built here at -O3 */

typedef struct {
    f32 x, y, z, w;
} Vec_b406_01E02630;

typedef struct {
    u8 pad0000[0x18B0];
    Vec_b406_01E02630 trail[69];
    u8 b1D00[0x74A0 - 0x1D00];
    f32 pos[3];
    u8 pad74AC[0x768A - 0x74AC];
    s16 h768A;
} Mgr_b406_01E02630;

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x40];
    f32 f48;
    u8 pad4C[8];
    s16 h54;
    u8 pad56[2];
    s16 h58;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
} Obj_b406_01E02630;

#pragma optimization_level 3

static s32 func_01E02630_b406(Mgr_b406_01E02630 *m, Obj_b406_01E02630 *o) {
    extern void b406_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Vec_b406_01E02630 *p;

    if (o->h58 == 1) {
        o->h6 = 8;
        o->c60[3] = 0;
        for (i = 0, p = m->trail; i < 69; i++, p++) {
            p->x = m->pos[0];
            p->y = m->pos[1];
            p->z = m->pos[2];
        }
        func_001076F0(o->c64, 0x80, 0x10, 0x10);
        o->f48 = 100.0f;
        o->h58 = 2;
    }
    if (o->h6 < 68) {
        o->h6++;
    }
    if (m->h768A < 185) {
        o->c60[3] = 0xC0;
    } else {
        if (o->c60[3] > 8) {
            o->c60[3] -= 7;
        } else {
            o->h58 = 0;
        }
        if (o->f48 > 0.0f) {
            o->f48 -= 1.0f;
        }
    }
    if (o->h54 % 2 == 0) {
        func_001076F0(o->c60, 0xFF, 0x10, 0x10);
    } else {
        func_001076F0(o->c60, 0x80, 0x10, 0x10);
    }
    if (o->h54 < 50) {
        b406_01E00080(m->b1D00, 70, 0, m->pos);
    }
    o->h54++;
    return 0;
}

#pragma optimization_level reset

/* shape b406:01E027F0, 99 insns: a grey-red flicker flash: size 200, random angle; alpha up by 14 to 0xC0 until frame 140, then
   down by 8 until it ends; second colour flickers red; shrinks by 10 to 100 once the scene timer reaches 173; spins */

typedef struct {
    u8 pad0[0x768A];
    s16 timer;
} Game_b406_01E027F0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b406_01E027F0;

static s32 func_01E027F0_b406(Game_b406_01E027F0 *g, Obj_b406_01E027F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 200.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x8C) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0xE;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
    } else {
        func_001076F0(o->c1, 0xF0, 0x20, 0x20);
    }
    if (g->timer > 0xAC) {
        if (o->size > 100.0f) {
            o->size -= 10.0f;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b406:01E02980, 125 insns: constant variant of b084:01E02990 (0x107->0xB4, second 0x23->0xA, second 300.0f->330.0f, colour (128, 16, 16)) */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b406_01E02980;

typedef struct {
    u8 pad0[0x768A];
    s16 frame;
} Scene_b406_01E02980;

static s32 func_01E02980_b406(Scene_b406_01E02980 *g, Fx_b406_01E02980 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 50.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->frame < 0xB4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0 && o->t > 0xA) {
        if (o->size < 300.0f) {
            o->size += 10.0f;
        }
    }
    if (o->kind == 1) {
        if (g->frame < 0xAC) {
            if (o->t > 0x23) {
                if (o->size < 330.0f) {
                    o->size += 10.0f;
                }
            }
        } else if (o->size > 100.0f) {
            o->size -= 10.0f;
        }
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b406:01E02B80, 89 insns: a white glow sized by the scene (ctx+0x7640) at a random angle, spun 0x4000 a tick, its second colour blinking red: in by 42 up to 0x80 for 80 ticks, then out by 8 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b406_01E02B80;

typedef struct {
    u8 pad[0x7640];
    f32 size;
} Game_b406_01E02B80;

static s32 func_01E02B80_b406(Game_b406_01E02B80 *g, Obj_b406_01E02B80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = g->size;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f48 = g->size;
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
    } else {
        func_001076F0(o->col2, 0xA0, 0x10, 0x10);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b406:01E02CF0, 82 insns: on start kind 0 is white-ish (both 0xF0, hold 0x1A), kind 1 yellow (0xD0/0xC0 with
   blue 0x80, hold 0x10); both alphas grow by 0x12 (below 0x80) during the hold, then fade by 4 (the first ends it) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b406_01E02CF0;

static s32 func_01E02CF0_b406(s32 arg0, Fx_b406_01E02CF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->hold = 0x1A;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
            o->hold = 0x10;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x12;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 5) {
            o->col2[3] -= 4;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b406", func_01E02E40_b406);

typedef struct {
    f32 x, y, z, w;
} Vec_b084_01E03610;

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    u8 pad52[6];
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Ent_b084_01E03610;

typedef struct {
    u8 pad0000[0x250];
    Vec_b084_01E03610 v250;
    u8 pad0260[0x40];
    Ent_b084_01E03610 ent[50];
    u8 pad1CC0[0x7624 - 0x2A0 - 50 * 0x70];
    u8 r, g, b, a;
    u8 pad7628[0x5A];
    s16 h7682;
} Obj_b084_01E03610;

static s32 func_01E03640_b406(Obj_b084_01E03610 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Ent_b084_01E03610 *e;
    s16 i;

    e = 0;
    for (i = 0; i < 50; i++) {
        if (o->ent[i].active == 0) {
            func_00195108(&o->ent[i], 0x70);
            o->ent[i].active = 1;
            e = &o->ent[i];
            i = 50;
        }
    }
    if (e != 0) {
    func_001076F0(e->c0, o->r, o->g, o->b);
    e->c0[3] = o->a;
    func_001076F0(e->c1, o->r, o->g, o->b);
    e->c1[3] = o->a;
    func_00106AB0(e, &o->v250, 0);
    e->x = o->v250.x;
    e->y = o->v250.y;
    e->z = o->v250.z;
    e->h50 = o->h7682;
    e->w40 = b;
    e->w44 = a;
    return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b406", func_01E03780_b406);
