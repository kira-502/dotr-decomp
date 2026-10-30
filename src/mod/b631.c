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

static void func_01E00080_b631(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b631(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b631((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b631((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b631 in the
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

static void func_01E00ED0_b631(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b631((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b041:01E00CF0, 182 insns: b016:01E00ED0 plus func_00109100(view, {.., .., cam 0x5A}, 2, obj 0xD8) after the view setup; draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b631 in the
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

static void func_01E01190_b631(Obj_b041_01E00CF0 *obj, Cam_b041_01E00CF0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b631((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b631:01E01470, 133 insns: the b631 module's event step: counts ticks; from 47 to 169 it moves its point to the tracked point and spawns three b631:01E01920; from 41 to 169 it snaps the point to each of the three tracked points, jitters x by -8..7 and spawns a b631:01E01690 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xB244 - 0x25C];
    s16 id0;
    s16 id1;
    s16 id2;
    u8 padB24A[0xB2B8 - 0xB24A];
    s16 timer;
} Ctx_b631_01E01470;

static void func_01E01470_b631(Ctx_b631_01E01470 *g) {
    extern s32 b631_01E01690(void);
    extern s32 b631_01E01920(void);
    extern void b631_01E02520(Ctx_b631_01E01470 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);

    g->timer++;
    if (g->timer > 46 && g->timer < 170) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        b631_01E02520(g, b631_01E01920, 0);
        b631_01E02520(g, b631_01E01920, 0);
        b631_01E02520(g, b631_01E01920, 0);
    }
    if (g->timer > 40 && g->timer < 170) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        g->pos[0] += func_0019A5C8() % 16 - 8;
        b631_01E02520(g, b631_01E01690, 0);
        func_001F5620(func_001F53A0(), g->id1, g->pos);
        g->pos[0] += func_0019A5C8() % 16 - 8;
        b631_01E02520(g, b631_01E01690, 0);
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        g->pos[0] += func_0019A5C8() % 16 - 8;
        b631_01E02520(g, b631_01E01690, 0);
    }
}

/* shape b631:01E01690, 163 insns: b564:01E01A30's tumbling spark at size 50 in grey 0x40 with a slower drift (/120)
   and a random frame 0..3; alpha grows for 5 ticks, fades by 9; no turn refresh */

typedef struct {
    s16 spin[3];
    u8 pad6[2];
    s16 w;
    s16 h;
    u8 padC[4];
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
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b631_01E01690;

static s32 func_01E01690_b631(s32 arg0, Spark_b631_01E01690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 50;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 120.0f;
        o->vel[0] /= 120.0f;
        o->vel[2] /= 120.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    o->tick++;
    return 0;
}

/* shape b631:01E01920, 257 insns: b422:01E01950 family spark: grey, size 8..23, variant (rand>>4)%3, drift -0.62..0.61
   (x/y, an 80th) and -0.5..0.49 (z, a 100th), random turn 0x5A turning (rand>>4)%20 - 10 a tick, spin -0x400..0x3FF
   per axis, frame (rand>>4)%4, hold 32..41; alpha up by 0x40 during the hold, down by 9 after it (and from scene time
   180); once moving it drifts and slides 5 along z (sign by ctx+0xB2B4); on tick 30 (before scene time 180) it
   hands its position to the scene and starts the module's b631:01E01D30 through b631:01E02520 */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 dir;
    s16 ddir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b631_01E01920;

typedef struct {
    u8 pad0[0x250];
    Vec4f org;
    u8 pad260[0xB2B4 - 0x260];
    s16 flip;
    u8 padB2B6[2];
    s16 timer;
} Scn_b631_01E01920;

static s32 func_01E01920_b631(Scn_b631_01E01920 *g, Spark_b631_01E01920 *o) {
    extern u8 b631_01E01D30[];
    extern void b631_01E02520(Scn_b631_01E01920 *g, void *data, s32 arg);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = (func_0019A5C8() >> 4) % 16 + 8;
        o->fA = o->f8;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 80.0f;
        o->vel[0] /= 80.0f;
        o->vel[2] /= 100.0f;
        o->dir = func_0019A5C8() % 360;
        o->ddir = (func_0019A5C8() >> 4) % 20 - 10;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->f52 = (func_0019A5C8() >> 4) % 4;
        o->hold = func_0019A5C8() % 10 + 32;
    }
    if (g->timer < 180) {
        if (o->tick < o->hold) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x40;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos.x += o->vel[0];
        o->pos.y += o->vel[1];
        o->pos.z += o->vel[2];
        if (g->flip != 0) {
            o->pos.z -= 5.0f;
        } else {
            o->pos.z += 5.0f;
        }
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    if (g->timer < 180) {
        if (o->tick == 30) {
            g->org = o->pos;
            b631_01E02520(g, b631_01E01D30, 0);
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    o->dir += o->ddir;
    return 0;
}

/* shape b631:01E01D30, 105 insns: a grey spark: size 5..19, random sub-frame 0..2, height 10..24, angle, rise 16..35, width 0..34,
   hold 3..5, rising once started; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x38];
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
} Obj_b631_01E01D30;

static s32 func_01E01D30_b631(void *arg0, Obj_b631_01E01D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 15 + 5;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 15 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01EE0_b631(void) {
    return 0;
}

/* shape b631:01E01EF0 (b631), 393 insns, 1 copy: b631 scene manager in b292:01E02580 form: setup (six joints, two
   type-4 and two type-5 textures, 256 s8 and 30 s16 jitters), step b631:01E01470 and every slot except b631:01E01EE0,
   draw the b631:01E01690 sparks, b631:01E01920 sparks and b631:01E01D30 sprites; scene code from the timer */

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
} Fx_b631_01E01EF0;

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
        s16 uv[8];
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
    Fx_b631_01E01EF0 fx[400];
    u8 padB1A0[0x50];
    s32 tex[2];
    u8 padB1F8[0x18];
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
} Scene_b631_01E01EF0;

static s32 func_01E01EF0_b631(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01470_b631();
    Scene_b631_01E01EF0 *g = (Scene_b631_01E01EF0 *)arg0;
    s16 n;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
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
        g->count = 210;
        g->jA = func_001F5560(func_001F53A0(), 0x10, 1);
        g->jB = func_001F5560(func_001F53A0(), 0xD, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xC, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
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
    func_01E01470_b631(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E01EE0_b631) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01690_b631) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm;
                g->hBE = g->fx[k].h52;
                if (g->fx[k].h56 < 2) {
                    g->u.uv[0] = g->fx[k].h56 << 6;
                    g->u.uv[1] = 0;
                } else {
                    g->u.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u.uv[1] = 0x40;
                }
                g->u.uv[2] = 0x40;
                g->u.uv[3] = 0x40;
                func_01E00ED0_b631((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01920_b631) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm2;
                g->hBE = g->fx[k].h52;
                g->u.uv[0] = g->fx[k].h56 << 5;
                g->u.uv[1] = 0;
                g->u.uv[2] = 0x20;
                g->u.uv[3] = 0x20;
                func_01E01190_b631((Obj_b041_01E00CF0 *)g, (Cam_b041_01E00CF0 *)&g->fx[k], 0x10, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D30_b631) {
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u.rm = *(Vec4f *)rm3;
                g->hBE = g->fx[k].h52;
                g->hB8 = 8;
                g->hBE = 0;
                g->hB0 = 0;
                func_01E00920_b631((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x10, g->jit);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 80) {
        return 1;
    }
    if (g->frame == 200) {
        return 4;
    }
    if (g->frame == 185) {
        return 2;
    }
    if (g->frame > 90 && g->frame < 180) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b236:01E02330, 98 insns, 15 copies: take a free effect slot (400 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b236_01E02330 {
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
} Slot_b236_01E02330;

typedef struct Obj_b236_01E02330 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b236_01E02330 slots[400];
    u8 padB1A0[0x74];
    u8 rgba[4];
    u8 padB218[0x98];
    s16 fB2B0;
} Obj_b236_01E02330;

static s32 func_01E02520_b631(Obj_b236_01E02330 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b236_01E02330 *s = NULL;
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
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}
