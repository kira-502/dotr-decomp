#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b499(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
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

static void func_01E00150_b499(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00150_b499 in the
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

static void func_01E009F0_b499(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00150_b499((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E00CB0_b499(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b499_01E00150();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

    func_00207500();
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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b499_01E00150(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b499:01E01200 (B499_W_S), 484 insns, 1 copy (-O3,p): B499_W_S, the scene timer script: colour red,
   counts the frame (0xBB14); the scene angle follows the model turn; ticks 39..65 spawn twin sparks at joints
   0xBAF8/0xBAFA, the point follows joint 0xBAF6; streams before 95; at 77 saves the scene point; at 93 40
   b499:01E01C50 bursts, 93..95 30 b499:01E01AF0 wisps, at 93 60 b499:01E01D30, 85..95 b499:01E01FA0 at the scene
   point */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x2F0 - 0x2E0];
    s32 rot[3];
    u8 pad2FC[0xB930 - 0x2FC];
    Vec4f pt;
    u8 padB940[0xBA70 - 0xB940];
    Vec4f save;
    u8 padBA80[0xBAB4 - 0xBA80];
    u8 col[4];
    u8 padBAB8[0xBAF6 - 0xBAB8];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 padBAFC[8];
    s16 ang;
    u8 padBB06[2];
    s16 hBB08;
    u8 padBB0A[6];
    s16 hBB10;
    u8 padBB12[2];
    s16 count;
    u8 padBB16[0xBC18 - 0xBB16];
    u8 trig[4];
} Ctx_b499_01E01200;

#pragma optimization_level 3

static void func_01E01200_b499(Ctx_b499_01E01200 *g) {
    extern void b499_01E01990(void);
    extern void b499_01E01A10(void);
    extern void b499_01E01AF0(void);
    extern void b499_01E01C50(void);
    extern void b499_01E01D30(void);
    extern void b499_01E01FA0(void);
    extern void b499_01E02110(void);
    extern void b499_01E02370(void);
    extern void b499_01E02550(void);
    extern void b499_01E02770(void);
    extern void b499_01E02B00(void);
    extern void b499_01E035D0(Ctx_b499_01E01200 *, void (*)(void), s32);
    extern void b499_01E03760(Ctx_b499_01E01200 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s16, s32);
    s32 r[4];
    s32 i;
    s32 h;
    s32 z;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    func_001F6160(func_001F53A0(), r);
    g->ang = (s32)(r[1] / 180.0f);
    g->ang -= 180;
    h = (s32)(15.0f * -func_00108030(g->trig, g->ang, 1));
    g->hBB10 = 0;
    g->pos.w = 0.0f;
    if (g->count == 93) {
        b499_01E035D0(g, b499_01E01990, 0);
    }
    if (g->count == 84) {
        b499_01E035D0(g, b499_01E01A10, 0);
    }
    if (g->count == 1) {
        b499_01E03760(g, b499_01E02B00, 0);
    }
    if (g->count >= 39 && g->count < 66) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->j1, &g->pos);
            g->pos.x += (f32)(func_0019A5C8() % 30 - 15);
            b499_01E03760(g, b499_01E02110, 0);
            func_001F5620(func_001F53A0(), g->j2, &g->pos);
            g->pos.x += (f32)(func_0019A5C8() % 30 - 15);
            b499_01E03760(g, b499_01E02110, 0);
        }
    }
    g->col[3] = 0;
    func_001F5620(func_001F53A0(), g->j0, &g->pos);
    if (g->count >= 39 && g->count < 95) {
        b499_01E03760(g, b499_01E02370, 0);
    }
    if (g->count >= 16 && g->count < 95) {
        b499_01E03760(g, b499_01E02550, 0);
    }
    if (g->count == 39) {
        b499_01E035D0(g, b499_01E01A10, 0);
    }
    if (g->count < 95) {
        b499_01E03760(g, b499_01E02770, 0);
    }
    if (g->count < 95) {
        b499_01E03760(g, b499_01E02770, 0);
    }
    if (g->count >= 88 && g->count < 95) {
        b499_01E03760(g, b499_01E02770, 0);
    }
    if (g->count == 77) {
        g->save.x = g->pt.x;
        g->save.y = g->pt.y;
        g->save.z = g->pt.z;
    }
    if (g->count == 93) {
        for (i = 0; i < 40; i++) {
            if (-g->ang < 90) {
                g->rot[0] = func_0019A5C8() % 0x8000 - 0x8000;
            } else {
                z = 0;
                g->rot[0] = func_0019A5C8() % 0x8000 + z;
            }
            g->rot[2] = func_0019A5C8() % 0x8000 + 0x4000;
            g->pos.x = 0.0f;
            g->pos.y = 0.0f;
            g->pos.z = 0.0f;
            b499_01E035D0(g, b499_01E01C50, 0);
        }
    }
    if (g->count == 93 || g->count == 94 || g->count == 95) {
        for (i = 0; i < 30; i++) {
            g->pos.x = g->pt.x + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->pos.y = g->pt.y + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->pos.z = (f32)h + (g->pt.z + (f32)(func_0019A5C8() % 20) - 10.0f);
            g->hBB10 = func_0019A5C8() % 80;
            g->hBB08 = func_0019A5C8() % 360;
            b499_01E035D0(g, b499_01E01AF0, 0);
        }
    }
    if (g->count == 93) {
        for (i = 0; i < 60; i++) {
            g->pos.x = g->pt.x;
            g->pos.y = g->pt.y;
            g->pos.z = g->pt.z + h;
            b499_01E035D0(g, b499_01E01D30, 0);
        }
    }
    if (g->count > 84 && g->count < 96) {
        g->pos.x = g->pt.x;
        g->pos.y = g->pt.y;
        g->pos.z = g->pt.z;
        g->hBB10 = 0;
        g->hBB08 = 0;
        b499_01E035D0(g, b499_01E01FA0, 0);
    }
}
#pragma optimization_level reset

/* shape b004:01E00460, 32 insns, 5 copies: step of a flash: first rises to alpha 0xF0 (then marks itself done rising),
   afterwards fades by 14 until it ends; keeps its colour at 0x9F/0x5F/0x5F */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b004_01E00460;

static s32 func_01E01990_b499(void *arg0, Obj_b004_01E00460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->up == 0) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] = 0xF0;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
    return 0;
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E01A10_b499(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b479:01E01910, 86 insns, 2 copies: a purple wisp: fades in to 0x60 over 10 frames, then out; each frame its x, y
   and z drift by 20 times a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0xBC18];
    u8 trig[1];
} World_b479_01E01910;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b479_01E01910;

static s32 func_01E01AF0_b499(World_b479_01E01910 *w, Wisp_b479_01E01910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    o->h38 = 9;
    func_001076F0(o->c0, 0x3F, 0, 0x6F);
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    o->x += 20.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 20.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 20.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b499:01E01C50, 56 insns: a white two-colour shape that grows 4 up to 10 and climbs 2 a tick from 15; ends at 181; past 60 both alphas drop by 12 */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b499_01E01C50;

static s32 func_01E01C50_b499(s32 arg0, Glow_b499_01E01C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h6 < 10) {
        o->h6 += 4;
    }
    o->h2 += 2;
    func_001076F0(o->col, 0xFF, 0xF0, 0xFF);
    if (o->h2 > 180) {
        o->mode = 0;
    }
    if (o->mode == 1) {
        o->h2 = 15;
        o->h6 = 0;
        o->col[3] = 0xC0;
        o->mode = 2;
    }
    if (o->h2 >= 60) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 13) {
            o->col2[3] -= 12;
        }
    }
    return 0;
}

/* shape b499:01E01D30, 155 insns: b004:01E00790 with the scene value at ctx+0xBB04 and the table at ctx+0xBC18 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0xBB04];
    s16 val;
    u8 padBB06[0xBC18 - 0xBB06];
    u8 tab[1];
} Mgr_b499_01E01D30;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b499_01E01D30;

static s32 func_01E01D30_b499(Mgr_b499_01E01D30 *m, Fx_b499_01E01D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 a;
    s16 k;

    a = -m->val;
    if (o->mode == 1) {
        o->f38 = 1;
        o->f34 = func_0019A5C8() % 4;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0xFF, 0xF0, 0);
        } else if (k == 1) {
            func_001076F0(o->col, 0xFF, 0, 0);
        } else if (k == 2) {
            func_001076F0(o->col, 0xFF, 0x80, 0);
        }
        o->f3A = func_0019A5C8() % 180 + 90;
        o->f30 = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->x = o->x + 20.0f * func_00108030(m->tab, a + o->f3A, 0);
    o->y = o->y + 20.0f * func_00108030(m->tab, o->f30, 0);
    o->z = o->z + 20.0f * func_00108030(m->tab, a + o->f3A, 1);
    return 0;
}

/* shape b479:01E01B70, 90 insns, 2 copies: a magenta pulse tied to the scene clock: size 22 (6 early on), fades in, then
   out; its frame climbs to 7, its size shrinks every third frame; dims at clock 96 and ends after it */

typedef struct {
    u8 pad0[0xBB14];
    s16 clock;
} World_b479_01E01B70;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
} Pulse_b479_01E01B70;

static s32 func_01E01FA0_b499(World_b479_01E01B70 *w, Pulse_b479_01E01B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x9F, 0, 0x3F);
    if (o->state == 1) {
        o->c0[3] = 0;
        o->frame = 0;
        if (w->clock < 0x5E) {
            o->size = 6;
        } else {
            o->size = 0x16;
        }
        o->state = 2;
    }
    if (o->t < 2) {
        o->c0[3] += 0x50;
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    if (o->frame < 7) {
        o->frame++;
    }
    if (o->t % 3 == 1) {
        if (o->size != 0) {
            o->size--;
        }
    }
    o->t++;
    if (w->clock == 0x60) {
        o->c0[3] = 0x20;
    }
    if (w->clock >= 0x61) {
        o->state = 0;
    }
    return 0;
}

/* shape b499:01E02110, 151 insns: b570:01E02680 in purple (0x40, 0x10, 0x80), size 3..5, alpha up for 20 ticks, spinning by its own random spins each tick */

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
} Spark_b499_01E02110;

static s32 func_01E02110_b499(s32 arg0, Spark_b499_01E02110 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 3 + 3;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x40, 0x10, 0x80);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 400.0f;
        o->vel[0] /= 400.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
    }
    if (o->tick < 20) {
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
        o->pos[1] += o->vel[1] - 0.09f;
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b499:01E02370, 119 insns: b479:01E01CE0 twin: a grey flickering spark (35 x 35 shrinking 2 a tick, frame toggling from random 0/1) on the scene joint, blinking light: both alphas in by 64 up to 0xC0 for 3 ticks, then out by 9 (twice on the first) and ends */

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
} Obj_b499_01E02370;

typedef struct {
    u8 pad[0xBAF4];
    s16 joint;
} Game_b499_01E02370;

static s32 func_01E02370_b499(Game_b499_01E02370 *g, Obj_b499_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->h8 = 35;
        o->hA = 35;
        o->kind = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        func_001F5620(func_001F53A0(), g->joint, &o->x);
    }
    if (o->t < 3) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        }
    }
    if (o->kind != 0) {
        o->kind = 0;
    } else {
        o->kind = 1;
    }
    if (o->t != 0) {
        o->h8 -= 2;
        o->hA -= 2;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b499:01E02550, 133 insns: b567:01E02690's flickering grey spark without the joint follow, h50 5..29 */

typedef struct {
    u8 pad0000[0x6DEC];
    s16 h6DEC;
} Mgr_b499_01E02550;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 v10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_b499_01E02550;

static s32 func_01E02550_b499(Mgr_b499_01E02550 *m, Obj_b499_01E02550 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = (func_0019A5C8() >> 4) % 25 + 5;
        o->h52 = func_0019A5C8() % 450 + 300;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 5) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 % 2 == 1) {
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c60, 0xC0, 0xC0, 0xC0);
    }
    o->h54++;
    return 0;
}

/* shape b499:01E02770, 227 insns: b479:01E024C0's drifting spark with a start size of 20 + rand % 20 below
   counter 88 and colour (0x60,0x60,0x60) */

typedef struct {
    u8 pad0[0xBB14];
    s16 count;
} Ctx_b499_01E02770;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0x18];
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b499_01E02770;

static s32 func_01E02770_b499(Ctx_b499_01E02770 *ctx, Obj_b499_01E02770 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (ctx->count < 88) {
            o->h8 = func_0019A5C8() % 20 + 20;
            o->hA = o->h8;
        } else {
            o->h8 = func_0019A5C8() % 20 + 50;
            o->hA = o->h8;
            o->y += func_0019A5C8() % 10 - 5;
            o->z += func_0019A5C8() % 10 - 5;
        }
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f38 = func_0019A5C8() % 100 - 50;
        o->f34 /= 200.0f;
        o->f30 /= 200.0f;
        o->f38 /= 200.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
    }
    if (o->t < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    if (ctx->count < 88) {
        if (o->t % 3 == 1) {
            o->h8 += 2;
            o->hA = o->h8;
        }
    } else {
        o->h8 += 2;
        o->hA = o->h8;
    }
    if (o->t != 0) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b499:01E02B00, 31 insns: b018:01E02DB0 family: func_001F7170(1, 0) with the module's two floats, then ends the object when the scene counter is 115 */

extern f32 D_01E04500_b499;
extern f32 D_01E04508_b499;

typedef struct {
    u8 pad0[0xBB14];
    s16 v;
} Ctx_b499_01E02B00;

typedef struct {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[2];
    s16 h36;
    u8 pad38[0x1C];
    s16 h54;
    u8 pad56[2];
    s16 h58;
} Obj_b499_01E02B00;

static s32 func_01E02B00_b499(Ctx_b499_01E02B00 *ctx, Obj_b499_01E02B00 *o) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04500_b499;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04508_b499;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 0);
    if (ctx->v == 115) {
        o->h58 = 0;
    }
    return 0;
}

/* shape b499:01E02B90 (b499), 656 insns, 1 copy: b499 module main: b479:01E02980's form; on frame 0 fills both joint
   trails, steps them each frame, steps and draws the 200 small slots and 300 effect slots, returns 1 / 4 / 2 by
   frame, 8 once the 135-frame countdown runs out */

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x16];
    s32 (*fn)();
    u8 c0[4];
    u8 pad2C[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    s16 h3A;
    u8 pad3C[4];
} Slot_b499_01E02B90;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xC];
    s16 h54;
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b499_01E02B90;

typedef struct {
    f32 x, y, z, w;
} Trail_b499_01E02B90;

typedef struct {
    u8 pad0[0x20];
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
    } c;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x238];
    s32 tex260[16];
    u8 pad350[0xA0];
    Slot_b499_01E02B90 slot[200];
    Fx_b499_01E02B90 fx[300];
    Trail_b499_01E02B90 trailA[10];
    Trail_b499_01E02B90 trailB[10];
    u8 padBA70[0x10];
    Vec4f save;
    s32 tex[4];
    u8 padBAA0[0x10];
    s32 count;
    u8 padBAB4[8];
    s32 ot;
    u8 padBAC0[0x34];
    s16 j[4];
    u8 padBAFC[0x16];
    s16 id;
    s16 frame;
    u8 padBB16[2];
    s8 jit[0x100];
    u8 crd[0x178];
} Scene_b499_01E02B90;

static s32 func_01E02B90_b499(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b499_01E01200();
    extern void b499_01E038F0();
    extern void b499_01E03DD0();
    extern void b499_01E03F70();
    extern void b499_01E04350();
    Scene_b499_01E02B90 *g = (Scene_b499_01E02B90 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    Vec4f p0;
    Vec4f p1;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 o;
    s32 i;
    Trail_b499_01E02B90 *tr;

    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xBD90);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x87;
        g->j[0] = func_001F5560(func_001F53A0(), 0x2C, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x2D, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x45, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x4C, 0);
        g->tex260[15] = func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    if (g->frame == 0) {
        tr = g->trailA;
        func_001F5620(func_001F53A0(), g->j[0], &p0);
        for (i = 0; i < 10; i++) {
            tr->x = p0.x;
            tr->y = p0.y;
            tr->z = p0.z;
            tr++;
        }
    }
    if (g->frame == 0) {
        tr = g->trailB;
        func_001F5620(func_001F53A0(), g->j[1], &p1);
        for (i = 0; i < 10; i++) {
            tr->x = p1.x;
            tr->y = p1.y;
            tr->z = p1.z;
            tr++;
        }
    }
    func_01E00080_b499(&g->trailA[9], 10, g->j[0]);
    func_01E00080_b499(&g->trailB[9], 10, g->j[1]);
    if (g->frame == 0x5E) {
        func_001F5620(func_001F53A0(), g->j[1], &g->save);
    }
    b499_01E01200(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == (s32 (*)())func_01E01990_b499) {
                if (g->slot[i].h30 == 0) {
                    if (g->slot[i].c0[3] < 0xF0) {
                        g->slot[i].c0[3] = 0xF0;
                    } else {
                        g->slot[i].h30 = 1;
                    }
                } else if (g->slot[i].c0[3] > 15) {
                    g->slot[i].c0[3] -= 14;
                } else {
                    g->slot[i].used = 0;
                }
                func_001076F0(g->slot[i].c0, 0x9F, 0x5F, 0x5F);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01A10_b499) {
                func_01E01A10_b499(g, &g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01AF0_b499) {
                g->slot[i].h38 = 9;
                func_001076F0(g->slot[i].c0, 0x3F, 0, 0x6F);
                if (g->slot[i].t < 10) {
                    if (g->slot[i].c0[3] < 0x60) {
                        g->slot[i].c0[3] += 9;
                    }
                } else if (g->slot[i].c0[3] > 0x10) {
                    g->slot[i].c0[3] -= 10;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
                g->slot[i].x = (s32)(g->slot[i].x + 20.0f * func_00108030(g->crd, g->slot[i].h3A, 0));
                g->slot[i].y = (s32)(g->slot[i].y + 20.0f * func_00108030(g->crd, g->slot[i].h30, 1));
                g->slot[i].z = (s32)(g->slot[i].z + 20.0f * func_00108030(g->crd, g->slot[i].h3A, 1));
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01C50_b499) {
                func_01E01C50_b499((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01D30_b499) {
                func_01E01D30_b499(g, &g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01FA0_b499) {
                func_01E01FA0_b499(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (s32 (*)())func_01E01990_b499) {
                o = g->ot;
                func_00107990(buf, g->slot[i].c0, 0);
                func_001092E0(buf, 0);
                func_001094F0(buf);
                func_002075F0(buf, o, 0);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01A10_b499) {
                b499_01E038F0(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01AF0_b499) {
                b499_01E03DD0(g, &g->slot[i], buf, 0);
                b499_01E03DD0(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01C50_b499) {
                b499_01E03F70(g, &g->slot[i], buf, 0);
                b499_01E03F70(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01D30_b499) {
                b499_01E03DD0(g, &g->slot[i], buf, 0);
                b499_01E03DD0(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01FA0_b499) {
                b499_01E04350(g, &g->slot[i], buf, 0);
                b499_01E04350(g, &g->slot[i], buf, 1);
            }
        }
    }
    for (i = 0; i < 300; i++) {
        if (g->fx[i].used != 0) {
            m++;
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 300; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == (s32 (*)())func_01E02110_b499) {
                g->tex88 = g->tex260[15];
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                func_01E009F0_b499(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02370_b499) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->c.h[0] = g->slot[i].h34 << 6;
                g->c.h[1] = 0;
                g->c.h[2] = 0x3F;
                g->c.h[3] = 0x3F;
                g->hBE = 5;
                c = g->fx[i].pos;
                if (g->fx[i].h54 < 3) {
                    func_01E009F0_b499(g, &g->fx[i], 0x21, c);
                } else {
                    func_01E009F0_b499(g, &g->fx[i], 0x20, c);
                }
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02550_b499) {
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex[1];
                g->hB8 = 6;
                g->hC0 = g->slot[i].y;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00CB0_b499(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == (s32 (*)())func_01E02770_b499) {
                func_00106080(rm4, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->tex88 = g->tex[2];
                func_01E009F0_b499(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x54) {
        return 1;
    }
    if (g->frame == 0x7D) {
        return 4;
    }
    if (g->frame == 0x5E) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b479:01E03300, 100 insns, 2 copies: spawns an effect into the first free slot (200 of 0x40 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument
   (b082:01E02FF0 family, small slots) */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    u8 c0[4];
    u8 c1[4];
    s16 h30;
    u8 pad32[4];
    s16 active;
    u8 pad38[2];
    s16 h3A;
    u8 pad3C[4];
} Slot_b479_01E03300;

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x10];
    s32 rot[3];
    u8 pad2FC[0xF4];
    Slot_b479_01E03300 slot[200];
    u8 pad35F0[0xBAB4 - 0x3F0 - 200 * 0x40];
    u8 col[4];
    u8 padBAB8[0x50];
    s16 hBB08;
    u8 padBB0A[6];
    s16 hBB10;
} Scene_b479_01E03300;

static s32 func_01E035D0_b499(Scene_b479_01E03300 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b479_01E03300 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 200; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x40);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 200;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->rot[0] = s->rot[0];
        sl->rot[1] = s->rot[1];
        sl->rot[2] = s->rot[2];
        sl->h3A = s->hBB08;
        sl->h30 = s->hBB10;
        sl->w20 = arg;
        sl->w24 = fn;
        return 1;
    }
    return 0;
}

/* shape b479:01E03490, 98 insns, 2 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x12c of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b479_01E03490 {
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
} Slot_b479_01E03490;

typedef struct Obj_b479_01E03490 {
    u8 pad0[0x2d0];
    f32 pos[3];
    u8 padA[0x35f0 - 0x2d0 - 12];
    Slot_b479_01E03490 slots[0x12c];
    u8 padB[0xbab4 - 0x35f0 - 0x12c * 0x70];
    u8 rgba[4];
    u8 padC[0xbb10 - 0xbab4 - 4];
    s16 fB2B0;
} Obj_b479_01E03490;

static s32 func_01E03760_b499(Obj_b479_01E03490 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b479_01E03490 *s = NULL;
    s16 i;

    for (i = 0; i < 0x12c; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x12c;
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

/* shape b499:01E038F0 (B499PAINT_RAIN), 310 insns, 1 copy: B499PAINT_RAIN: a tube along the scene's point trail
   (ctx+0xB930, 10 points): per segment 18 quads around it, the near ring radius t and the far one t + w (w = 0.3, t
   from 2 growing by 0.3 a segment), alpha fading by col.a / 10 */

typedef struct Rgba_b499_01E038F0 {
    u8 r, g, b, a;
} Rgba_b499_01E038F0;

typedef struct Fx_b499_01E038F0 {
    u8 pad0[0x28];
    Rgba_b499_01E038F0 col;
    u8 pad2C[6];
    s16 n;
} Fx_b499_01E038F0;

typedef struct Game_b499_01E038F0 {
    u8 pad0[0xB930];
    Vec4f pts[16];
    u8 padBA30[0xBC18 - 0xBA30];
    u8 trig[1];
} Game_b499_01E038F0;

static void func_01E038F0_b499(Game_b499_01E038F0 *g, Fx_b499_01E038F0 *o) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630();
    extern void func_00109380();
    extern void func_002075F0();
    f32 depth[4];
    Vec4f q[4];
    u8 pk[0x90] __attribute__((aligned(8)));
    Rgba_b499_01E038F0 col;
    f32 t;
    f32 w;
    s32 k;
    s32 j;
    u8 *p;
    s32 ot __attribute__((aligned(8)));
    s16 a;

    ot = (s32)func_00207500();
    t = 2.0f;
    w = 0.3f;
    p = pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = o->col;
    for (k = 0; k < 9; k++) {
        a = 0;
        func_00107990(p, &col, 1);
        col.a -= o->col.a / 10;
        func_00107990(p, &col, 2);
        for (j = 0; j < 18; j++) {
            q[0].x = g->pts[k].x;
            q[0].y = g->pts[k].y;
            q[0].z = g->pts[k].z;
            q[1].x = g->pts[k].x;
            q[1].y = g->pts[k].y;
            q[1].z = g->pts[k].z;
            q[0].y += t * func_00108030(g->trig, a, 1);
            q[0].x += t * func_00108030(g->trig, a, 0);
            q[0].z += t * func_00108030(g->trig, a, 1);
            q[1].y += t * func_00108030(g->trig, a + 20, 1);
            q[1].x += t * func_00108030(g->trig, a + 20, 0);
            q[1].z += t * func_00108030(g->trig, a + 20, 1);
            q[2].x = g->pts[k + 1].x;
            q[2].y = g->pts[k + 1].y;
            q[2].z = g->pts[k + 1].z;
            q[3].x = g->pts[k + 1].x;
            q[3].y = g->pts[k + 1].y;
            q[3].z = g->pts[k + 1].z;
            q[2].y += (t + w) * func_00108030(g->trig, a, 1);
            q[2].x += (t + w) * func_00108030(g->trig, a, 0);
            q[2].z += (t + w) * func_00108030(g->trig, a, 1);
            q[3].y += (t + w) * func_00108030(g->trig, a + 20, 1);
            q[3].x += (t + w) * func_00108030(g->trig, a + 20, 0);
            q[3].z += (t + w) * func_00108030(g->trig, a + 20, 1);
            if (func_00205630(q, 0x70000000, 0, p, depth)) {
                func_00109380(p, 1);
                func_002075F0(p, ot, 0);
            }
            a += 20;
        }
        t += 0.3f;
    }
}

/* shape b499:01E03DD0, 103 insns: b004:01E01860 twin two-pass sprite draw (texture id 0x9B, scene texture at +0x34C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b499_01E03DD0;

typedef struct {
    u8 pad0[0x34C];
    s32 tex;
} Scene_b499_01E03DD0;

static void func_01E03DD0_b499(Scene_b499_01E03DD0 *g, Fx_b499_01E03DD0 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9B, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m, 0, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

/* shape b499:01E03F70, 247 insns: b004:01E01A00's hanging quad for module b499: setup pass with the scene texture 0x34C;
   draw pass builds the scene matrix (0x290) from the scene point 0xBA80 (copied into a local) and the anim's
   rotation, one quad 1 wide at the anim's s16 point hanging 0x6 down, heights kept within 0..200, depth in 0xBAE4, into
   0xBABC */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b499_01E03F70;

typedef struct {
    Rgbaq_b499_01E03F70 c;
    u64 st;
    u64 xyz;
} Vtx_b499_01E03F70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b499_01E03F70 v[4];
} Pkt_b499_01E03F70;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[4];
    s16 h34;
} Anim_b499_01E03F70;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0x7C];
    s32 tex;
    u8 pad350[0xB930 - 0x350];
    u8 cam[0x150];
    Vec4f point;
    u8 padBA90[0x2C];
    s32 ot;
    u8 padBAC0[0x24];
    f32 depth;
} Scene_b499_01E03F70;

static void func_01E03F70_b499(Scene_b499_01E03F70 *g, Anim_b499_01E03F70 *an, Pkt_b499_01E03F70 *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b499_01E03F70 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00107130(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    f32 rm[4];

    if (lit == 0) {
        func_00106080(rm, 0x9C, an->h34, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_0020EB40(g->m);
    func_00107130(g->cam, v, 1);
    v[0] = g->point.x;
    v[1] = g->point.y;
    v[2] = g->point.z;
    func_0020C940(m, 0, an->rot, v);
    func_0020BC00(g->m, m);
    q[0].x = an->x;
    q[0].y = an->y;
    q[0].z = an->z;
    q[1] = q[0];
    q[1].x += 1.0f;
    q[2].x = an->x;
    q[2].y = an->y;
    q[2].z = an->z;
    q[2].y -= an->h6;
    q[3] = q[2];
    q[3].x += 1.0f;
    if (q[0].y > 200.0f) {
        q[0].y = 200.0f;
    }
    if (q[1].y > 200.0f) {
        q[1].y = 200.0f;
    }
    if (q[2].y > 200.0f) {
        q[2].y = 200.0f;
    }
    if (q[3].y > 200.0f) {
        q[3].y = 200.0f;
    }
    if (q[0].y < 0.0f) {
        q[0].y = 0.0f;
    }
    if (q[1].y < 0.0f) {
        q[1].y = 0.0f;
    }
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    if (q[3].y < 0.0f) {
        q[3].y = 0.0f;
    }
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

/* shape b479:01E03A40, 94 insns: a billboard: with flag 0 set the packet up (texture cell 0x99/f34 of the
   scene, colour, texture); otherwise place it at the effect's position (size f38), and send it with the scene's
   depth when it projects */

typedef struct {
    u8 pad0[0x34C];
    void *texture;
    u8 pad350[0xB76C];
    s32 ot;
    u8 padBAC0[0x24];
    f32 depth;
} Obj_b479_01E03A40;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 col[0xC];
    s16 f34;
    u8 pad36[2];
    s16 size;
} Fx_b479_01E03A40;

static void func_01E04350_b499(Obj_b479_01E03A40 *o, Fx_b479_01E03A40 *fx, void *p, s32 flag) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    f32 view[16];
    Vec4f pos;
    u8 uv[0x10];
    f32 m[16];
    s32 rot[4];

    func_00207500();
    if (flag == 0) {
        func_00106080(uv, 0x99, fx->f34, uv);
        func_00109270(p, 0, 0);
        func_00107790(p, fx->col, 0);
        func_00108500(p, uv, 0);
        func_00208700(p, o->texture, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = fx->x;
        pos.y = fx->y;
        pos.z = fx->z;
        func_00108EF0(m, 0, rot, &pos);
        func_00108CE0(view, fx->size, fx->size);
        if (func_00205630(view, 0x70000000, m, p, &o->depth) != 0) {
            func_00109380(p, 0);
            func_002075F0((s32)p, o->ot, (u32)o->depth);
        }
    }
}
