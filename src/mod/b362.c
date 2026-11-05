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

static void func_01E00080_b362(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b362(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
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

static void func_01E00D80_b362(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b362((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b362((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b362 in the
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

static void func_01E01330_b362(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b362((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b362:01E015F0, 327 insns: the b362 module's event step (B362_W_S): counts ticks (ctx+0xB278); at 69 it takes
   the player and camera points and picks the side (0 or 2) by the player's x and the flag 0xB274; on odd ticks
   69..155 one b362:01E01B10 at the model point (0xB240) jittered by -20..19; every third tick 1..200 two
   b362:01E01EE0 at the two joints (0xB242) jittered by a fifth of that; every third tick to 234 b362:01E028A0; at 1
   b362:01E026A0 and b362:01E025A0; until 225 b362:01E020F0 at the model point */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB220 - 0x260];
    Vec4f *pa;
    Vec4f *pb;
    u8 padB228[0xB240 - 0xB228];
    s16 id;
    s16 joint[2];
    u8 padB246[0xB260 - 0xB246];
    s16 side;
    u8 padB262[0xB274 - 0xB262];
    s16 flag;
    u8 padB276[2];
    s16 timer;
} Ctx_b362_01E015F0;

static void func_01E015F0_b362(Ctx_b362_01E015F0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern Vec4f *func_001F9D30(s32);
    extern void func_01E03290_b362();
    extern s32 func_01E01B10_b362();
    extern s32 func_01E01EE0_b362();
    extern s32 func_01E020F0_b362();
    extern s32 func_01E025A0_b362();
    extern s32 func_01E026A0_b362();
    extern s32 func_01E028A0_b362();
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s16 n;

    g->timer++;
    if (g->timer == 69) {
        g->pa = func_001F9AD0(0);
        g->pb = func_001F9D30(0);
        if (g->flag != 0) {
            if (g->pa->x > 0.0f) {
                g->side = 0;
            } else {
                g->side = 2;
            }
        } else {
            if (g->pa->x > 0.0f) {
                g->side = 2;
            } else {
                g->side = 0;
            }
        }
    }
    if (g->timer >= 69 && g->timer < 156 && g->timer % 2 == 1) {
        if (g->timer < 100) {
            n = 1;
        } else {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->id, &g->pos);
            g->pos.x += func_0019A5C8() % 40 - 20;
            g->pos.y += func_0019A5C8() % 40 - 20;
            g->pos.z += func_0019A5C8() % 40 - 20;
            func_01E03290_b362(g, func_01E01B10_b362, 0);
        }
    }
    if (g->timer > 0 && g->timer < 201 && g->timer % 3 == 1) {
        if (g->timer < 100) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->joint[i], &g->pos);
            x = func_0019A5C8() % 40 - 20;
            y = func_0019A5C8() % 40 - 20;
            z = func_0019A5C8() % 40 - 20;
            x /= 5.0f;
            y /= 5.0f;
            z /= 5.0f;
            g->pos.x += x;
            g->pos.y += y;
            g->pos.z += z;
            func_01E03290_b362(g, func_01E01EE0_b362, 0);
        }
    }
    if (g->timer % 3 == 1 && g->timer < 235) {
        func_01E03290_b362(g, func_01E028A0_b362, 0);
    }
    if (g->timer == 1) {
        func_01E03290_b362(g, func_01E026A0_b362, 0);
    }
    if (g->timer == 1) {
        func_01E03290_b362(g, func_01E025A0_b362, 0);
    }
    if (g->timer < 226) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y = 35.0f;
        func_001F5620(func_001F53A0(), g->id, &g->pos);
        func_01E03290_b362(g, func_01E020F0_b362, 0);
    }
}

/* shape b362:01E01B10, 242 insns: b428:01E01A70's spark (size 20, grey) that picks a camera point jittered by
   (-50..49)/7, then from tick 51 flies to it in steps of a 20th (depth an 18.5th) of the gap; at tick 70 it ends,
   puts the scene point on itself and spawns 0x1E022B0 and 0x1E02490; fades in by 10 until tick 90 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB260 - 0x260];
    s16 hB260;
} Ctx_b362_01E01B10;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b362_01E01B10;

static s32 func_01E01B10_b362(Ctx_b362_01E01B10 *ctx, Obj_b362_01E01B10 *o) {
    extern void b362_01E022B0(void);
    extern void b362_01E02490(void);
    extern void b362_01E03290(Ctx_b362_01E01B10 *, void (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 dx;
    f32 dy;

    if (o->state == 1) {
        o->h8 = 20;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        o->h52 = (func_0019A5C8() >> 4) % 2;
        if (o->h52 == 0) {
            o->h52 = ctx->hB260;
        } else {
            o->h52 = ctx->hB260;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        func_001F5F90(func_001F5380(), v);
        dx = (func_0019A5C8() >> 4) % 100 - 50;
        dy = (func_0019A5C8() >> 4) % 100 - 50;
        dx /= 7.0f;
        v[0] += dx;
        dy /= 7.0f;
        v[1] += dy;
        o->f30 = (v[0] - o->pos.x) / 20.0f;
        o->f34 = (v[1] - o->pos.y) / 20.0f;
        o->f38 = (v[2] - o->pos.z) / 18.5f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 90) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h56++;
    if (o->h56 >= 3) {
        o->h56 = 0;
    }
    func_00205C40((s32)o->rot);
    if (o->t > 50 && o->t < 70) {
        o->pos.x += o->f30;
        o->pos.y += o->f34;
        o->pos.z += o->f38;
    } else if (o->t == 70) {
        o->state = 0;
        ctx->pos = o->pos;
        b362_01E03290(ctx, b362_01E022B0, 0);
        b362_01E03290(ctx, b362_01E02490, 0);
    }
    o->t++;
    return 0;
}

/* shape b362:01E01EE0, 131 insns: b362:01E020F0 with a start height of 20..119 while the game counter at g+0xB278 is
   under 70, else 10..109 */

typedef struct {
    u8 pad0[0xB278];
    s16 count;
} Game_b362_01E01EE0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b362_01E01EE0;

static s32 func_01E01EE0_b362(Game_b362_01E01EE0 *g, Obj_b362_01E01EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 6.0f;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        if (g->count < 70) {
            o->y = func_0019A5C8() % 100 + 20;
        } else {
            o->y = func_0019A5C8() % 100 + 10;
        }
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 3 + 1;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b362:01E020F0, 112 insns: a white tumbling spark (b041:01E01C40 shape): size 6, random sub-frame 0..3 and turn on all three
   axes, height 10..59, angle, step 1..3, width 1..8, hold 2..4; alpha up by 42 to 0x80 until the hold, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b362_01E020F0;

static s32 func_01E020F0_b362(void *arg0, Obj_b362_01E020F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 6.0f;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->y = func_0019A5C8() % 50 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 3 + 1;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b362:01E022B0, 119 insns: b574:01E02170 family: a white tumbling spark (size 30, random frame 0..3, three random turns, angle 5..14, spin 20..59, size 1..8) held 2..4 ticks: in by 42 up to 0x80, then out by 11 and ends */

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
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b362_01E022B0;

static s32 func_01E022B0_b362(s32 arg0, Obj_b362_01E022B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 30.0f;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 10 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 40 + 20;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b362:01E02490, 67 insns: a white-green growing spinning flash (b202:01E022A0 shape): scale 50 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b362_01E02490;

static s32 func_01E02490_b362(void *arg0, Obj_b362_01E02490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 50.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 8, 0x80, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xD) {
        o->c0[3] -= 0xC;
    } else {
        o->state = 0;
    }
    o->scale += 1.0f;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b362:01E025A0, 63 insns: volume fade by game state (b058:01E017A0 shape, layout at 0x50): state at 0xB200 limit
   0x19, down 10 to 0x70, up 10 to 0x80 where the fade ends; counts frames; state 3 plays at 0x80 and ends it */

typedef struct {
    u8 pad[0xB200];
    s32 state;
} Game_b362_01E025A0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b362_01E025A0;

static s32 func_01E025A0_b362(Game_b362_01E025A0 *g, Fade_b362_01E025A0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x19) {
        if (o->vol > 0x70) {
            o->vol -= 10;
        } else {
            o->vol = 0x70;
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
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b362:01E026A0, 125 insns: b016:01E02B40 with a pale green full-screen tint (0x78/0xA0/0x78), start offset 10,
   blend 0x44, alpha up by 10 to 0x50 for 235 ticks, then down by 4 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b362_01E026A0;

typedef struct {
    f32 s, t;
    Xyz_b362_01E026A0 p;
} Tv_b362_01E026A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b362_01E026A0 v[2];
    u8 tail[0x20];
} Tex_b362_01E026A0;

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
} Fx_b362_01E026A0;

static s32 func_01E026A0_b362(s32 arg0, Fx_b362_01E026A0 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b362_01E026A0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->mode = 2;
    }
    ((Tex_b362_01E026A0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b362_01E026A0 *)(s32)&pk)->size = 5;
    ((Tex_b362_01E026A0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b362_01E026A0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0xA0;
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
    if (o->tick < 0xEB) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0xA;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b362:01E028A0, 190 insns: b746:01E042C0's window in dark grey 0x28 at ctx+0xB218 that zooms out by 55 each way
   every tick after the first; alpha up by 42 for 3 ticks, then down by 12 after tick 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b362_01E028A0;

typedef struct {
    f32 s, t;
    Xyz_b362_01E028A0 p;
} Tv_b362_01E028A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b362_01E028A0 v[2];
} Tex_b362_01E028A0;

typedef struct {
    u8 pad[0xB218];
    Tex_b362_01E028A0 *pk;
} Game_b362_01E028A0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b362_01E028A0;

static s32 func_01E028A0_b362(Game_b362_01E028A0 *g, Fx_b362_01E028A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x28, 0x28, 0x28);
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
    g->pk->v[0].s = fx / 1024.0f;
    g->pk->v[0].t = fy / 512.0f;
    g->pk->v[1].s = (640.0f - fx) / 1024.0f;
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick != 0) {
        o->f8 += 55;
        o->fA += 55;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->tick > 4) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b362:01E02BA0 (b362), 442 insns, 1 copy: b362 scene manager in b465:01E02330 form on its own layout: setup
   (three joints, two type-5 textures, two 256 s8 jitter rows with set spans), step b362:01E015F0 and every slot,
   counting the b362:01E028A0 anchors, draw the 01E01B10 smoke, 01E01EE0/020F0/022B0 gas and 01E02490 circle, then the
   anchor paint if any; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xA];
    s16 h52;
    u8 pad54[0x2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b362_01E02BA0;

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
        s16 uv[4];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    u8 pad260[0x50];
    Fx_b362_01E02BA0 fx[400];
    u8 padB1B0[0x30];
    s32 tex[2];
    u8 padB1E8[0x18];
    s32 count;
    u8 padB204[8];
    s32 ot;
    u8 padB210[0x30];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padB246[0xA];
    s16 cam;
    u8 padB252[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padB47A[2];
    u8 crd[0x174];
} Scene_b362_01E02BA0;

static s32 func_01E02BA0_b362(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E015F0_b362();
    extern void func_01E00920_b362();
    extern void func_01E00D80_b362();
    extern void func_01E01330_b362();
    extern void b362_01E03420();
    Scene_b362_01E02BA0 *g = (Scene_b362_01E02BA0 *)arg0;
    s16 a;
    s16 n;
    Vec4f pos;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;

    a = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB5F0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 260;
        g->jA = func_001F5560(func_001F53A0(), 0x55, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x5F, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x5A, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
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
        for (k = 180; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = 0;
        }
        return 0;
    }
    func_01E015F0_b362(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E028A0_b362) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    a++;
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01B10_b362) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->u94.uv[0] = g->fx[k].h56 << 6;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x40;
                g->u94.uv[3] = 0x40;
                g->hBE = g->fx[k].h52;
                func_01E01330_b362(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01EE0_b362) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00D80_b362(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E020F0_b362) {
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00D80_b362(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E022B0_b362) {
                g->tex88 = g->tex[1];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00D80_b362(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02490_b362) {
                pos = g->fx[k].pos;
                func_01E00920_b362(g, &g->fx[k], 0x21, pos);
            }
        }
    }
    if (a) {
        b362_01E03420(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 130) {
        return 1;
    }
    if (g->frame == 250) {
        return 4;
    }
    if (g->frame == 235) {
        return 3;
    }
    if (g->frame > 140 && g->frame < 230) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b362:01E03290, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b362_01E03290 {
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
} Slot_b362_01E03290;

typedef struct Obj_b362_01E03290 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2b0 - 0x250 - 12];
    Slot_b362_01E03290 slots[0x190];
    u8 padB[0xb204 - 0x2b0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb270 - 0xb204 - 4];
    s16 fB2B0;
} Obj_b362_01E03290;

static s32 func_01E03290_b362(Obj_b362_01E03290 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b362_01E03290 *s = NULL;
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

/* shape b362:01E03420, 89 insns: b003:01E02FB0 family draw pass: counts every live slot (400 of 0x70 bytes, at +0x2B0) and draws the ones whose handler is shape b362:01E028A0; the packet is sent only when any slot is live */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b362_01E03420;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b362_01E03420 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b362_01E03420;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b362_01E03420;

typedef struct {
    u8 pad0[0x2B0];
    Slot_b362_01E03420 slot[400];
    u8 padEnd[0xB214 - 0x2B0 - 400 * 0x70];
    s32 ctx;
    Pkt_b362_01E03420 *pkt;
} Scene_b362_01E03420;

static void func_01E03420_b362(Scene_b362_01E03420 *s) {
    extern void b362_01E028A0(Scene_b362_01E03420 *, Slot_b362_01E03420 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b362_01E03420 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    s->pkt = &pkt;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b362_01E028A0) {
                b362_01E028A0(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
