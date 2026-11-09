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

static void func_01E00080_b282(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b282(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b282((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b282((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b282(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E01230_b282(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b282:01E015A0, 305 insns: the b282 module's event step (B282_W_S): counts ticks (ctx+0xB2B8); at tick 1
   spawns b282:01E025A0, b282:01E026B0 and four b282:01E01DB0 rings at the hand (turns 0, 90 / slot 0, 45, 135 /
   slot 1); at 28, 38, 44 thirty b282:01E01F60 and one b282:01E01C20 just under the second point (0xB244); 108..160
   b282:01E01A70 there, 134..160 b282:01E01C20 at the third point (0xB246); at 121 and 144 a burst (ten, one
   b282:01E02480, thirty b282:01E021F0) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB244 - 0x260];
    s16 id2;
    s16 id3;
    s16 id;
    u8 padB24A[0xB2A2 - 0xB24A];
    s16 turn;
    u8 padB2A4[0xB2B0 - 0xB2A4];
    s16 slot;
    u8 padB2B2[6];
    s16 timer;
} Ctx_b282_01E015A0;

static void func_01E015A0_b282(Ctx_b282_01E015A0 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_01E032B0_b282();
    extern s32 func_01E01A70_b282();
    extern s32 func_01E01C20_b282();
    extern s32 func_01E01DB0_b282();
    extern s32 func_01E01F60_b282();
    extern s32 func_01E021F0_b282();
    extern s32 func_01E02480_b282();
    extern s32 func_01E025A0_b282();
    extern s32 b282_01E026B0();
    Vec4f v[2];
    s16 i;

    g->timer++;
    if (g->timer == 1) {
        func_01E032B0_b282(g, func_01E025A0_b282, 0);
    }
    if (g->timer == 1) {
        func_01E032B0_b282(g, b282_01E026B0, 0);
    }
    if (g->timer == 1) {
        func_001F5620(func_001F53A0(), g->id, &g->pos);
        g->turn = 0;
        g->slot = 0;
        func_01E032B0_b282(g, func_01E01DB0_b282, 0);
        g->turn = 90;
        g->slot = 0;
        func_01E032B0_b282(g, func_01E01DB0_b282, 0);
        g->turn = 45;
        g->slot = 1;
        func_01E032B0_b282(g, func_01E01DB0_b282, 0);
        g->turn = 135;
        g->slot = 1;
        func_01E032B0_b282(g, func_01E01DB0_b282, 0);
    }
    if (g->timer == 28 || g->timer == 38 || g->timer == 44) {
        func_001F5F90(func_001F53A0(), &g->pos);
        func_001F5620(func_001F53A0(), g->id2, v);
        g->pos.y = v[0].y - 1.0f;
        g->slot = 0;
        for (i = 0; i < 30; i++) {
            func_01E032B0_b282(g, func_01E01F60_b282, 0);
        }
        func_01E032B0_b282(g, func_01E01C20_b282, 0);
    }
    if (g->timer >= 108 && g->timer < 161) {
        func_001F5620(func_001F53A0(), g->id2, &g->pos);
        func_01E032B0_b282(g, func_01E01A70_b282, 0);
    }
    if (g->timer == 121) {
        func_001F5620(func_001F53A0(), g->id2, &g->pos);
        for (i = 0; i < 10; i++) {
            func_01E032B0_b282(g, func_01E01C20_b282, 0);
        }
        func_01E032B0_b282(g, func_01E02480_b282, 0);
        g->slot = 0;
        for (i = 0; i < 30; i++) {
            func_01E032B0_b282(g, func_01E021F0_b282, 0);
        }
    }
    if (g->timer >= 134 && g->timer < 161) {
        func_001F5620(func_001F53A0(), g->id3, &g->pos);
        func_01E032B0_b282(g, func_01E01C20_b282, 0);
    }
    if (g->timer == 144) {
        func_001F5620(func_001F53A0(), g->id3, &g->pos);
        for (i = 0; i < 10; i++) {
            func_01E032B0_b282(g, func_01E01A70_b282, 0);
        }
        func_01E032B0_b282(g, func_01E02480_b282, 0);
        g->slot = 0;
        for (i = 0; i < 30; i++) {
            func_01E032B0_b282(g, func_01E021F0_b282, 0);
        }
    }
}

/* shape b282:01E01A70, 105 insns: b282:01E01C20 family spinning spark (random size 50..99, frame 0..2, angle 10..49, spin 20..39, held 7..11 ticks): in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b282_01E01A70;

static s32 func_01E01A70_b282(s32 arg0, Obj_b282_01E01A70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 50 + 50;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 20;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 7;
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
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b282:01E01C20, 98 insns: a white spark (random size 10..29, frame 0..2, heading, angle 10..49, spin 16..35 and size 0..34 stored) held 7..11 ticks: in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b282_01E01C20;

static s32 func_01E01C20_b282(s32 arg0, Obj_b282_01E01C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 7;
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

/* shape b282:01E01DB0, 107 insns: on start f48 6, colour (0xFF, 0x60, 0x60), second colour (0xFF, 0x40, 0x40) with
   alpha 0, f30/f34 = 3/50, 3/20 or 8/400 by the kind 0x50, 0x52 = 0; alpha grows by 0x40 (below 0x80) for 4 ticks, then
   fades by 9 and stops; after the first tick f34 grows by 15 (kind 0) or 5 (kind 1) and 0x52 counts up to 0x19 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b282_01E01DB0;

static s32 func_01E01DB0_b282(s32 arg0, Fx_b282_01E01DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0x60, 0x60);
        func_001076F0(o->col2, 0xFF, 0x40, 0x40);
        if (o->kind == 0) {
            o->f30 = 3.0f;
            o->f34 = 50.0f;
        }
        if (o->kind == 1) {
            o->f30 = 3.0f;
            o->f34 = 20.0f;
        }
        if (o->kind == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->f52 = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->tick != 0) {
            o->f34 += 15.0f;
        }
    }
    if (o->kind == 1) {
        if (o->tick != 0) {
            o->f34 += 5.0f;
        }
    }
    if (o->tick != 0) {
        if (o->f52 < 0x19) {
            o->f52++;
        }
    }
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b282:01E01F60, 162 insns: b413:01E029E0 in blue (0x40/0x40/0xFF), w 1, height 30 rising 10 a tick, hC from 0
   rising 3.0 a tick (as a float), hold 10 */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    u8 padE[2];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Spark_b282_01E01F60;

static s32 func_01E01F60_b282(s32 arg0, Spark_b282_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 1;
        o->h = 30;
        o->hC = 0;
        o->kind = 2;
        func_001076F0(o->col, 0x40, 0x40, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 20.0f;
        o->vel[0] /= 20.0f;
        o->vel[2] /= 20.0f;
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->hold = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h += 10;
        o->hC += 3.0f;
    }
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b282:01E021F0, 163 insns: b413:01E029E0 in blue (0x40/0x40/0xFF), w 5, height 100 rising 15 a tick, hC from 0
   rising 10.0 a tick (as a float), hold 10 */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    u8 padE[2];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Spark_b282_01E021F0;

static s32 func_01E021F0_b282(s32 arg0, Spark_b282_01E021F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 5;
        o->h = 100;
        o->hC = 0;
        o->kind = 2;
        func_001076F0(o->col, 0x40, 0x40, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 20.0f;
        o->vel[0] /= 20.0f;
        o->vel[2] /= 20.0f;
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->hold = 10;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h += 15;
        o->hC += 10.0f;
    }
    o->tick++;
    return 0;
}

/* shape b282:01E02480, 69 insns: constant variant of b287:01E02C80 (0xE->0xA, 150.0f->200.0f) */

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
} Fx_b282_01E02480;

static s32 func_01E02480_b282(s32 arg0, Fx_b282_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 200.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xA) {
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

static s32 func_01E025A0_b282(Game_b180_01E021D0 *g, Fade_b180_01E021D0 *o) {
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

/* shape b282:01E026B0, 292 insns: a full-screen flash sprite (B282_OBJ_MOVE_203): grey level stepping
   0x60,0x50,0x40,0x30,0x20,0x30,0x40,0x50 over 8 ticks; draws the scene's sprite packet (ctx+0xB228) across the screen
   with texture offset 0x08/0x0A tenths; alpha up 9 to 0x80 before tick 120, then down 7 and ends */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
} Pkt_b282_01E026B0;

typedef struct {
    u8 pad0[0xB228];
    Pkt_b282_01E026B0 *pkt;
} Ctx_b282_01E026B0;

typedef struct {
    u8 pad0[8];
    s16 sx;
    s16 ty;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Obj_b282_01E026B0;

static s32 func_01E026B0_b282(Ctx_b282_01E026B0 *g, Obj_b282_01E026B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0();
    f32 s;
    f32 t;

    s = o->sx;
    t = o->ty;
    s /= 10.0f;
    t /= 10.0f;
    if (o->state == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->state = 2;
    }
    if (o->t % 8 == 0) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    if (o->t % 8 == 1) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
    }
    if (o->t % 8 == 2) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->t % 8 == 3) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    }
    if (o->t % 8 == 4) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
    }
    if (o->t % 8 == 5) {
        func_001076F0(o->col, 0x30, 0x30, 0x30);
    }
    if (o->t % 8 == 6) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->t % 8 == 7) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
    }
    g->pkt->r = o->col[0];
    g->pkt->g = o->col[1];
    g->pkt->b = o->col[2];
    g->pkt->a = o->col[3];
    g->pkt->q = 1.0f;
    g->pkt->x0 = 0x6BF8;
    g->pkt->y0 = 0x71F8;
    g->pkt->z0 = 0xFFFFFF;
    g->pkt->f0 = 0;
    g->pkt->x1 = 0x93F8;
    g->pkt->y1 = 0x8DF8;
    g->pkt->z1 = 0xFFFFFF;
    g->pkt->f1 = 0;
    g->pkt->s0 = s / 1024.0f;
    g->pkt->t0 = t / 512.0f;
    g->pkt->s1 = (640.0f - s) / 1024.0f;
    g->pkt->t1 = (448.0f - t) / 512.0f;
    func_002075F0(g->pkt, 0, 0);
    if (o->t < 120) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->t > 40) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b282:01E02B40 (b282), 475 insns, 1 copy: b282 scene manager in b465:01E02330 form: setup (six joints, two
   type-4 and one type-5 textures, 256 s8 and 30 s16 jitters), step W_S and every slot but the b282:01E026B0 anchors,
   draw the b282:01E01A70/01C20 gas, b282:01E01DB0 eyes at two joints, b282:01E01F60/021F0 smoke and b282:01E02480
   circle, then the anchor paint; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b282_01E02B40;

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
    Fx_b282_01E02B40 fx[400];
    u8 padB1A0[0x50];
    s32 tex[4];
    u8 padB200[0x10];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB250[4];
    s16 cam;
    u8 padB256[0xE];
    s16 jit16[30];
    u8 padB2A0[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3BA[0x102];
    u8 crd[0x174];
} Scene_b282_01E02B40;

static s32 func_01E02B40_b282(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E015A0_b282();
    extern void b282_01E03460();
    extern void b282_01E03770();
    Scene_b282_01E02B40 *g = (Scene_b282_01E02B40 *)arg0;
    s16 n;
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
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 190;
        g->jA = func_001F5560(func_001F53A0(), 3, 1);
        g->jB = func_001F5560(func_001F53A0(), 4, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->jD = func_001F5560(func_001F53A0(), 0xE, 0);
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
    func_01E015A0_b282(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E026B0_b282) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01A70_b282) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b282((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C20_b282) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b282((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01DB0_b282) {
                g->tex88 = g->tex260[15];
                func_00106080(rm3, 0x9A, 0, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hBE = 0;
                func_001F5620(func_001F53A0(), g->jC, &g->fx[k].pos);
                func_01E01230_b282((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos);
                func_001F5620(func_001F53A0(), g->jD, &g->fx[k].pos);
                func_01E01230_b282((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F60_b282) {
                g->tex88 = g->tex260[15];
                func_00106080(rm4, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hBE = 0;
                g->hB0 = 1;
                b282_01E03460(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021F0_b282) {
                g->tex88 = g->tex260[15];
                func_00106080(rm5, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->hBE = 0;
                g->hB0 = 1;
                b282_01E03460(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02480_b282) {
                g->hB8 = 0x24;
                func_01E00ED0_b282((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   &g->fx[k].pos);
                g->hB8 = 0;
            }
        }
    }
    b282_01E03770(g);
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 111) {
        return 1;
    }
    if (g->frame == 185) {
        return 4;
    }
    if (g->frame == 160) {
        return 2;
    }
    if (g->frame > 121 && g->frame < 155) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b098:01E024A0, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fB2B0, f5A = owner fB2A2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b098_01E024A0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b098_01E024A0;

typedef struct Obj_b098_01E024A0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b098_01E024A0 slots[400];
    u8 padB[0xB214 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xB2A2 - 0xB214 - 4];
    s16 fB;
    u8 padD[0xB2B0 - 0xB2A2 - 2];
    s16 fA;
} Obj_b098_01E024A0;

static s32 func_01E032B0_b282(Obj_b098_01E024A0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b098_01E024A0 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
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
        s->f50 = obj->fA;
        s->f52 = obj->fA;
        s->f5A = obj->fB;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b282:01E03460, 195 insns, 3 copies: draws crossed sprite planes at a position: kind 0 one ring of two planes 90
   apart, kind 1 ten rings 36 apart of one plane each; blend from flags >> 4. Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b282_01E03460;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b282_01E03460 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b282_01E03460;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[0xC];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b282_01E03460;

typedef struct {
    u8 pad00[8];
    s16 w, h, y;
    u8 padE[0x12];
    Vec4f rot;
    u8 pad30[0x2A];
    s16 a5A;
    s16 a5C;
    u8 pad5E[2];
    u8 col[4];
} Spr_b282_01E03460;

static void func_01E03460_b282(Obj_b282_01E03460 *o, Spr_b282_01E03460 *s, s32 flags, Vec4f pos) {
    extern Rgbaq_b282_01E03460 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 r1[4];
    s32 r2[4];
    Pkt_b282_01E03460 pkt __attribute__((aligned(8)));
    Pkt_b282_01E03460 *p;
    s32 b;
    s32 n;
    s32 j;
    s32 m2;
    s32 i;
    f32 y;

    b = (flags >> 4) & 0xF;
    p = (Pkt_b282_01E03460 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00080_b282((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    r1[0] = 0;
    r1[2] = 0;
    if (o->kind == 0) {
        n = 1;
    }
    if (o->kind == 1) {
        n = 10;
    }
    if (o->kind == 0) {
        m2 = 2;
    }
    if (o->kind == 1) {
        m2 = 1;
    }
    for (i = 0; i < n; i++) {
        r2[1] = 0;
        r2[0] = s->a5C + i * 36;
        r2[2] = 0;
        y = s->y;
        for (j = 0; j < m2; j++) {
            func_00108CE0(quad, s->w, s->h);
            r1[0] = 0;
            r1[1] = s->a5A + j * 90;
            r1[2] = 0;
            quad[2].y = 0.0f;
            quad[3].y = 0.0f;
            func_00109100(quad, r1, 0, o->xD8);
            func_00107070(quad, 1, y);
            func_00109100(quad, r2, 1, o->xD8);
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
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

extern void b282_01E026B0(Ctx_b098_01E02650 *ctx, Obj_b098_01E02650 *o);

static void func_01E03770_b282(Ctx_b098_01E02650 *ctx) {
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
            if (ctx->objs[i].draw == b282_01E026B0) {
                b282_01E026B0(ctx, &ctx->objs[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(ctx->list, (s32)func_00207500(), 0);
    }
}
