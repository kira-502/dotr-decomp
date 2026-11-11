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

static void func_01E00080_b590(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b590(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b590((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b590((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b590(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E01230_b590(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
        }
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

static void func_01E015A0_b590(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b590:01E01770, 197 insns: the b590 module's event step (B590_W_S): counts ticks; at tick 1 spawns
   b590:01E02450; from 42 to 100 spawns b590:01E01C40 at each of the four tracked points (ctx+0xB248..0xB24E);
   from 130 to 250 follows the fifth tracked point (ctx+0xB250); at 168 moves to the target's model point at
   height 50 and spawns b590:01E02330, b590:01E021A0 (slot 1), four b590:01E01FA0 (turns 0/90/45/135, slots
   0/0/1/1) and twenty b590:01E01DF0 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xB248 - 0x25C];
    s16 id[5];
    u8 padB252[0xB2A6 - 0xB252];
    s16 turn;
    u8 padB2A8[0xB2B4 - 0xB2A8];
    s16 slot;
    u8 padB2B6[0xB2BC - 0xB2B6];
    s16 timer;
} Ctx_b590_01E01770;

static void func_01E01770_b590(Ctx_b590_01E01770 *g) {
    extern s32 b590_01E01C40(void);
    extern s32 b590_01E01DF0(void);
    extern s32 b590_01E01FA0(void);
    extern s32 b590_01E021A0(void);
    extern s32 b590_01E02330(void);
    extern s32 b590_01E02450(void);
    extern void b590_01E02E70(Ctx_b590_01E01770 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    s16 i;

    g->timer++;
    if (g->timer == 1) {
        b590_01E02E70(g, b590_01E02450, 0);
    }
    if (g->timer >= 42 && g->timer < 101) {
        func_001F5620(func_001F53A0(), g->id[0], g->pos);
        b590_01E02E70(g, b590_01E01C40, 0);
        func_001F5620(func_001F53A0(), g->id[1], g->pos);
        b590_01E02E70(g, b590_01E01C40, 0);
        func_001F5620(func_001F53A0(), g->id[2], g->pos);
        b590_01E02E70(g, b590_01E01C40, 0);
        func_001F5620(func_001F53A0(), g->id[3], g->pos);
        b590_01E02E70(g, b590_01E01C40, 0);
    }
    if (g->timer >= 130 && g->timer < 251) {
        func_001F5620(func_001F53A0(), g->id[4], g->pos);
    }
    if (g->timer == 168) {
        func_001F5F90(func_001F5380(), g->pos);
        g->pos[1] = 50.0f;
        b590_01E02E70(g, b590_01E02330, 0);
        g->slot = 1;
        b590_01E02E70(g, b590_01E021A0, 0);
        g->turn = 0;
        g->slot = 0;
        b590_01E02E70(g, b590_01E01FA0, 0);
        g->turn = 90;
        g->slot = 0;
        b590_01E02E70(g, b590_01E01FA0, 0);
        g->turn = 45;
        g->slot = 1;
        b590_01E02E70(g, b590_01E01FA0, 0);
        g->turn = 135;
        g->slot = 1;
        b590_01E02E70(g, b590_01E01FA0, 0);
        for (i = 0; i < 20; i++) {
            b590_01E02E70(g, b590_01E01DF0, 0);
        }
    }
}

/* shape b590:01E01A90, 105 insns: a small grey spark: f48 2..4, variant 0..2, f50 5..9, spin 1..3, life 3..5; alpha grows
   by 0x40 (below 0xC0) during the life, then fades by 14; f50 grows by the spin each tick after the first */

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
} Fx_b590_01E01A90;

static s32 func_01E01A90_b590(s32 arg0, Fx_b590_01E01A90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 3 + 2;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 5 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b590:01E01A90, 105 insns: a small grey spark: f48 2..4, variant 0..2, f50 5..9, spin 1..3, life 3..5; alpha grows
   by 0x40 (below 0xC0) during the life, then fades by 14; f50 grows by the spin each tick after the first */

static s32 func_01E01C40_b590(s32 arg0, Fx_b590_01E01A90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 3 + 2;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 5 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b590:01E01DF0, 108 insns: b282:01E01C20 family spinning spark: grey, random size 10..15, frame 0..2, angle 5..9, spin 100..199, size 0..34, held 8..15 ticks, turning 3 a tick: in by 64 up to 0xC0, then out by 14 and ends */

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
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b590_01E01DF0;

static s32 func_01E01DF0_b590(s32 arg0, Obj_b590_01E01DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 6 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 5 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 100 + 100;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 8 + 8;
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
    o->h5A += 3;
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b590:01E01FA0, 125 insns: b588:01E025F0 family (red/blue): kind 0 from 300 growing 160 and width 10 growing 1, kind 1 from 200 growing 80 and width 10 growing 0.5, kind 2 400 width 8 fixed; frame counter to 25 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b590_01E01FA0;

static s32 func_01E01FA0_b590(s32 arg0, Obj_b590_01E01FA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->h50 == 0) {
            o->f30 = 10.0f;
            o->f34 = 300.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 10.0f;
            o->f34 = 200.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->h52 = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0) {
        if (o->t != 0) {
            o->f34 += 160.0f;
        }
        if (o->t != 0) {
            o->f30 += 1.0f;
        }
    }
    if (o->h50 == 1) {
        if (o->t != 0) {
            o->f34 += 80.0f;
        }
        if (o->t != 0) {
            o->f30 += 0.5f;
        }
    }
    if (o->t != 0) {
        if (o->h52 < 25) {
            o->h52++;
        }
    }
    o->t++;
    return 0;
}

/* shape b590:01E021A0, 98 insns: on start colours and hold by kind (0x50); both alphas grow by 0x2A (below 0x80) during the
   hold, then fade by 7 (the first ends the effect) */

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
} Fx_b590_01E021A0;

static s32 func_01E021A0_b590(s32 arg0, Fx_b590_01E021A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->hold = 0xF;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0x60, 0x60, 0xC0);
            func_001076F0(o->col2, 0x60, 0x60, 0xC0);
            o->hold = 0xD;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0x58, 0x58, 0x78);
            func_001076F0(o->col2, 0x58, 0x58, 0x78);
            o->hold = 0x16;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b590:01E02330, 69 insns: constant variant of b287:01E02C80 (150.0f->130.0f) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
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
} Fx_b590_01E02330;

static s32 func_01E02330_b590(s32 arg0, Fx_b590_01E02330 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 130.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xE) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        o->size += 0.4f;
    }
    o->tick++;
    return 0;
}

/* shape b590:01E02450, 136 insns: b763:01E032F0's full-screen veil, brightening until scene frame 185 (s16 at 0xB2BC) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b590_01E02450;

typedef struct {
    f32 s, t;
    Xyz_b590_01E02450 p;
} Tv_b590_01E02450;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b590_01E02450 v[2];
    u8 tail[0x20];
} Tex_b590_01E02450;

typedef struct {
    u8 pad0[0xB2BC];
    s16 frame;
} Ctx_b590_01E02450;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b590_01E02450;

static s32 func_01E02450_b590(Ctx_b590_01E02450 *g, Fx_b590_01E02450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b590_01E02450 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    ((Tex_b590_01E02450 *)(s32)&pk)->flags = 0x26;
    ((Tex_b590_01E02450 *)(s32)&pk)->size = 5;
    ((Tex_b590_01E02450 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b590_01E02450 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->frame < 0xB9) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02670_b590(void) {
    return 0;
}

/* shape b590:01E02680 (b590), 506 insns, 1 copy: b590 scene manager in b529:01E03630 / b492:01E038C0 form: setup (six
   joints, one type-4 and two type-5 textures, 256 s8 and 30 s16 jitters), step B590_W_S and every slot but the empty
   handler, draw IWMagicGas1 (three kinds), IWMagicEye1, the IWMagicSPRIM1 sprite at the camera point (by kind) and
   IWMagicCircleG4_8; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    union {
        Vec4f v;
        Vec_b016_01E01190 c;
    } pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b590_01E02680;

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
    Fx_b590_01E02680 fx[400];
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
    u8 padB2A4[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BE[0x102];
    u8 crd[0x170];
} Scene_b590_01E02680;

static s32 func_01E02680_b590(s32 arg0, s32 id) {
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
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_01E01770_b590();
    Scene_b590_01E02680 *g = (Scene_b590_01E02680 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 210;
        g->jA = func_001F5560(func_001F53A0(), 6, 1);
        g->jB = func_001F5560(func_001F53A0(), 0xA, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xE, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x12, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2C, 0);
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
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_01E01770_b590(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02670_b590) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01A90_b590) {
                g->tex88 = g->tex[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b590((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C40_b590) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b590((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01DF0_b590) {
                g->tex88 = g->tex[0];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 1;
                func_01E00920_b590((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01FA0_b590) {
                g->tex88 = g->tex260[15];
                func_00106080(rm4, 0x9A, 0, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hBE = 0;
                func_01E01230_b590((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos.v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021A0_b590) {
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 50.0f;
                } else {
                    v.z += 50.0f;
                }
                func_00205440(&v, NULL, &pk[0x18], &g->depth);
                if (g->fx[k].h50 == 0) {
                    func_01E015A0_b590((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
                if (g->fx[k].h50 == 1) {
                    func_01E015A0_b590((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 2) {
                    func_01E015A0_b590((s32)g, (u8 *)&g->fx[k], 0x20, g->depth);
                }
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02330_b590) {
                g->hB8 = 0x24;
                func_01E00ED0_b590((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21, &g->fx[k].pos.c);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 178) {
        return 1;
    }
    if (g->frame == 205) {
        return 4;
    }
    if (g->frame == 185) {
        return 2;
    }
    if (g->frame > 168 && g->frame < 180) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b539:01E03530, 106 insns, 4 copies: starts a particle: takes the first free one of 400 slots, clears it, gives
   it the emitter's two colours, position and timers and the two caller values; returns 0 when all are busy. */

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
} Slot_b539_01E03530;

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad0260[0x40];
    Slot_b539_01E03530 slots[400];
    u8 padB1A0[0x74];
    u8 col[4];
    u8 padB218[0x8E];
    s16 t2;
    u8 padB2A8[0xC];
    s16 t0;
} Emit_b539_01E03530;

static s32 func_01E02E70_b590(Emit_b539_01E03530 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b539_01E03530 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 400;
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
        e->t1 = o->t0;
        e->t2 = o->t2;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}
