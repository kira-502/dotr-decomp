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

static void func_01E00080_b281(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b281(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b281((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b281((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b193_01E009B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    u8 pad5C[4];
    u8 col0[4];
    u8 col1[4];
} Anim_b193_01E009B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b193_01E009B0;

typedef struct {
    u8 b[0x90];
} Pkt_b193_01E009B0;

static void func_01E00ED0_b281(Obj_b193_01E009B0 *o, Anim_b193_01E009B0 *an, s32 mode, Vec_b193_01E009B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b193_01E009B0 quad[4];
    Vec_b193_01E009B0 at;
    Vec_b193_01E009B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b193_01E009B0 pkt;
    s32 a;
    s32 k;
    s16 j;
    Pkt_b193_01E009B0 *p;
    s16 blend;
    s32 kind;
    f32 w0;
    f32 w1;

    p = &pkt;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    kind = mode & 0xF;
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    for (k = 0; k < 36; k++) {
        if (k == 0) {
            a = an->step + j;
            quad[0].x = w0 * func_00108030(o->bD8, a, 1);
            quad[0].z = w0 * func_00108030(o->bD8, a, 0);
            quad[2].x = w1 * func_00108030(o->bD8, a, 1);
            quad[2].z = w1 * func_00108030(o->bD8, a, 0);
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (an->step + 10);
            quad[1].x = w0 * func_00108030(o->bD8, a, 1);
            quad[1].z = w0 * func_00108030(o->bD8, a, 0);
            quad[3].x = w1 * func_00108030(o->bD8, a, 1);
            quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        }
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
        j += 10;
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b281 in the
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

static void func_01E01330_b281(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b281((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b281:01E015F0, 246 insns: the effect scene's step (b509:01E01BD0 family): counts the frame (0x451C); until 154
   the marker (0x4470) follows joint 0x44E4, at 155 it measures a 32-step drift toward joint 0x44F4 in y and z and moves
   until 185; at 186 the scene point takes the marker; frame 40 sets the slot/turn pair twice; frames 212..330 spawn
   0x1E019D0 at the camera point (5 up, 5 left or right by the frame's parity); frames 41..310 spawn 0x1E01C90 on joint
   0x44E6; frame 1 spawns 0x1E02230; frames 230..350, every fourth, spawn 0x1E01E40 on each of the 8 joints from
   0x44F4; both turns (0x450C/0x450E) advance 6 a frame */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Vec4f m;
    u8 pad4480[4];
    f32 dy;
    f32 dz;
    u8 pad448C[0x44E4 - 0x448C];
    s16 ja;
    s16 jb;
    u8 pad44E8[0xC];
    s16 ids[8];
    u8 pad4504[2];
    s16 ang2;
    u8 pad4508[4];
    s16 turn2;
    s16 turn;
    u8 pad4510[4];
    s16 slot;
    u8 pad4516[6];
    s16 timer;
} Ctx_b281_01E015F0;

static void func_01E015F0_b281(Ctx_b281_01E015F0 *g) {
    extern s32 b281_01E019D0(void);
    extern s32 b281_01E01C90(void);
    extern s32 b281_01E01E40(void);
    extern s32 b281_01E02230(void);
    extern void b281_01E02AB0(Ctx_b281_01E015F0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v[2];
    s16 i;
    s32 k;

    g->timer++;
    if (g->timer < 155) {
        func_001F5620(func_001F53A0(), g->ja, &g->m);
    } else {
        if (g->timer == 155) {
            func_001F5620(func_001F5380(), g->ids[0], &v[0]);
            g->dz = (v[0].z - g->m.z) / 32.0f;
            g->dy = (v[0].y - g->m.y) / 32.0f;
        }
        if (g->timer < 186) {
            g->m.z += g->dz;
            g->m.y += g->dy;
        }
    }
    if (g->timer == 186) {
        g->pos = g->m;
        g->slot = 0;
    }
    if (g->timer == 40) {
        g->slot = 0;
        g->ang2 = 0;
        g->slot = 1;
        g->ang2 = 90;
    }
    if (g->timer >= 212 && g->timer < 331) {
        func_001F5620(func_001F53A0(), g->jb, &v[0]);
        k = g->timer % 2;
        if (k == 0) {
            g->slot = 0;
            func_001F5F90(func_001F53A0(), &g->pos);
            g->pos.y += 5.0f;
            g->pos.x -= 5.0f;
            b281_01E02AB0(g, b281_01E019D0, 0);
        } else if (k == 1) {
            g->slot = 1;
            func_001F5F90(func_001F53A0(), &g->pos);
            g->pos.y += 5.0f;
            g->pos.x += 5.0f;
            b281_01E02AB0(g, b281_01E019D0, 0);
        }
    }
    if (g->timer >= 41 && g->timer < 311) {
        g->slot = 0;
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        b281_01E02AB0(g, b281_01E01C90, 0);
    }
    if (g->timer == 1) {
        b281_01E02AB0(g, b281_01E02230, 0);
    }
    if (g->timer >= 230 && g->timer < 351 && g->timer % 4 == 0) {
        for (i = 0; i < 8; i++) {
            func_001F5620(func_001F5380(), g->ids[i], &v[0]);
            g->pos = v[0];
            b281_01E02AB0(g, b281_01E01E40, 0);
        }
    }
    g->turn2 += 6;
    if (g->turn2 >= 360) {
        g->turn2 %= 360;
    }
    g->turn += 6;
    if (g->turn >= 360) {
        g->turn %= 360;
    }
}

/* shape b281:01E019D0, 174 insns: b747:01E02170's ring in red (0xFF/0x50/0x50 blinking with 0xC0/0x30/0x30): size 3,
   h5C from the scene's table by kind (g+0x450C), size grows by 6.5 with f4C = size - 3, and the fade starts once the
   scene frame (g+0x451C) reaches 351 */

typedef struct {
    u8 pad0[0x450C];
    s16 h450C[6];
    s16 flag;
    u8 pad451A[2];
    s16 frame;
} Game_b281_01E019D0;

typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 size;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b281_01E019D0;

static s32 func_01E019D0_b281(Game_b281_01E019D0 *g, Obj_b281_01E019D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 3.0f;
        func_001076F0(o->c1, 0xFF, 0x50, 0x50);
        o->mode = 2;
        o->h5C = g->h450C[o->kind];
        o->c1[3] = 0;
    }
    if (o->t < 35) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 10) {
        o->c1[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0x50, 0x50);
    } else {
        func_001076F0(o->c0, 0xC0, 0x30, 0x30);
    }
    o->rot = 0x4000;
    if (g->flag != 0) {
        if (o->f34 < 50.0f) {
            o->f34 += 1.6f;
        }
    } else if (!(o->f34 <= -50.0f)) {
        o->f34 -= 1.6f;
    }
    if (o->f38 < 10.0f) {
        o->f38 += 0.2f;
    }
    if (o->t != 0) {
        o->size += 6.5f;
        if (g->flag != 0) {
            o->f4C = o->size - 3.0f;
        } else {
            o->f4C = o->size - 3.0f;
        }
    }
    o->h5C += 9;
    o->t++;
    if (o->t != 0) {
        if (g->flag != 0) {
            o->y -= 5.0f;
        } else {
            o->y += 5.0f;
        }
    }
    if (g->frame > 350) {
        o->t = 35;
    }
    return 0;
}

/* shape b281:01E01C90, 108 insns: a grey spark (b434:01E02210 shape): size 1..3, random sub-frame 0..7 stepping (reset under 7),
   height 2..16, angle, rise 16..35, width 0..34, hold 3..5; alpha up by 0x40 to 0xC0 until the hold, then down by 14 */

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
} Obj_b281_01E01C90;

static s32 func_01E01C90_b281(void *arg0, Obj_b281_01E01C90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 3 + 1;
        o->sub = func_0019A5C8() % 8;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 15 + 2;
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
    o->sub++;
    if (o->sub < 7) {
        o->sub = 0;
    }
    o->t++;
    return 0;
}

/* shape b281:01E01E40, 124 insns: on start size 30..59 (kept in 0xA), frame 0..7, grey colour, turn 0..359; alpha grows
   by 0x40 (below 0x80) for 7 ticks, then fades by 9 (ends below 11); colour flickers blue 0xFF / 0xC0; frame cycles
   0..7, size grows by one every third tick up to 35; after the first tick it rises 0.7 a tick; turns 0x20 */

typedef struct {
    u8 pad0[8];
    s16 size;
    s16 size0;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x30];
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b281_01E01E40;

static s32 func_01E01E40_b281(s32 arg0, Fx_b281_01E01E40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 30 + 30;
        o->size0 = o->size;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->ang = func_0019A5C8() % 360;
    }
    if (o->t < 7) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0xFF);
    } else {
        func_001076F0(o->col, 0x30, 0x30, 0xC0);
    }
    o->frame++;
    if (o->frame > 7) {
        o->frame = 0;
    }
    if (o->t % 3 == 1) {
        if (o->size < 0x23) {
            o->size++;
        }
    }
    if (o->t != 0) {
        o->y += 0.7f;
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b016:01E02940, 127 insns: a drifting spark: on start pick a random size, variant, position, start value,
   angle, speed, delay and lifetime and colour (0xC0,0x50,0x50); full alpha while younger than its lifetime, then
   fade out by 11 and stop; the value 0x50 grows by the speed every tick */

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
} Spark_b016_01E02940;

static s32 func_01E02030_b281(s32 arg0, Spark_b016_01E02940 *o) {
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
        o->speed = func_0019A5C8() % 3 + 1;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
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

/* shape b281:01E02230, 128 insns: b594:01E02CB0 with a reddish (0xA0, 0x78, 0x78) sprite starting at 1, scene count at ctx+0x451C */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b281_01E02230;

typedef struct {
    f32 s, t;
    Xyz_b281_01E02230 p;
} Tv_b281_01E02230;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b281_01E02230 v[2];
    u8 tail[0x20];
} Tex_b281_01E02230;

typedef struct {
    u8 pad0[0x451C];
    s16 count;
} Ctx_b281_01E02230;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b281_01E02230;

static s32 func_01E02230_b281(Ctx_b281_01E02230 *g, Fx_b281_01E02230 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b281_01E02230 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.0f;
        o->mode = 2;
    }
    ((Tex_b281_01E02230 *)(s32)&pk)->flags = 0x26;
    ((Tex_b281_01E02230 *)(s32)&pk)->size = 5;
    ((Tex_b281_01E02230 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b281_01E02230 *)(s32)&pk)->pad4 = 0;
    pk.r = 0xA0;
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
    if (g->count < 355) {
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

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02430_b281(void) {
    return 0;
}

/* shape b281:01E02440 (b281), 411 insns, 1 copy: b281 scene manager (b631:01E01EF0 form, one s16 counter k for the
   setup, step and draw loops, set to 0 with the count): setup (two joints, type-4 texture 15 and two type-5 textures,
   two 256 s8 jitter tables, eight random joints), step b281:01E015F0 and every slot except b281:01E02430, draw the
   b281:01E019D0 circles, b281:01E01C90 and b281:01E02030 gas and b281:01E01E40 smoke; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x18];
    f32 f38;
    u8 pad3C[8];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b281_01E02440;

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
    Fx_b281_01E02440 fx[150];
    u8 pad4440[0x50];
    s32 tex[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 jA;
    s16 jB;
    u8 pad44E8[0xC];
    s16 js[8];
    u8 pad4504[8];
    s16 h450C;
    s16 h450E;
    u8 pad4510[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad471E[2];
    u8 crd[0x170];
} Scene_b281_01E02440;

static s32 func_01E02440_b281(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E015F0_b281();
    extern void func_01E00ED0_b281();
    extern void func_01E00920_b281();
    Scene_b281_01E02440 *g = (Scene_b281_01E02440 *)arg0;
    s16 n;
    Vec4f p;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s32 (*fn)();
    s32 m;

    k = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4890);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 374;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x3F, 0);
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
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 8; k++) {
            m = func_001F54E0(func_001F5380());
            n = func_0019A5C8() % m;
            if (n == 0) {
                n++;
            }
            if (!k) {
                g->js[k] = func_001F5560(func_001F5380(), n, 1);
            } else {
                g->js[k] = func_001F5560(func_001F5380(), n, 0);
            }
        }
        g->h450C = 270;
        g->h450E = 90;
        return 0;
    }
    func_01E015F0_b281(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            fn = g->fx[k].fn;
            if (fn && fn != (s32 (*)())func_01E02430_b281) {
                fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E019D0_b281) {
                p = g->fx[k].pos;
                if (g->fx[k].h50 == 0) {
                    p.x += 10.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                if (g->fx[k].h50 == 1) {
                    p.x -= 10.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                func_01E00ED0_b281((void *)g, (void *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C90_b281) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b281((void *)g, (void *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E40_b281) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                p.x = g->fx[k].pos.x;
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                func_01E01330_b281((void *)g, (void *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02030_b281) {
                g->tex88 = g->tex260[15];
                func_00106080(rm3, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E00920_b281(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 220) {
        return 1;
    }
    if (g->frame == 360) {
        return 4;
    }
    if (g->frame == 355) {
        return 2;
    }
    if (g->frame > 230 && g->frame < 350) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b281:01E02AB0, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    u8 pad52[6];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b281_01E02AB0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2A0 - 0x25C];
    Obj_b281_01E02AB0 slot[150];
    u8 padEnd[0x44b4 - 0x2A0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padA[0x4506 - 0x44b4 - 4];
    s16 ang;
    u8 padB[0x4514 - 0x4506 - 2];
    s16 h30;
} Ctx_b281_01E02AB0;

static s32 func_01E02AB0_b281(Ctx_b281_01E02AB0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b281_01E02AB0 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h5A = ctx->ang;
        s->h50 = ctx->h30;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}
