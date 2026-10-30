#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b034(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00110_b034(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
    }
}

/* shape b034:01E00560, 210 insns: b016:01E01190's ring as 36 flat quads 10 degrees wide from 0x5A, inner radius 0x48 and outer 0x6 (an s16), scaled by the object's 0x10 and turned by the data's 0x20; each quad reuses the previous one's far edge */

typedef struct {
    f32 x, y, z, w;
} Vec_b034_01E00560;

typedef struct {
    u8 pad00[0x10];
    Vec_b034_01E00560 scale;
    u8 pad20[0x60];
    s32 texture;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b034_01E00560;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec_b034_01E00560 rotation;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0xE];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b034_01E00560;

static void func_01E00560_b034(Obj_b034_01E00560 *obj, Data_b034_01E00560 *data, s32 flags, Vec_b034_01E00560 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b034_01E00560 c;
    Vec_b034_01E00560 quad[4];
    Vec_b034_01E00560 pos;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s16 i;
    s16 j;
    s16 a;
    f32 inner;
    f32 outer;
    f32 cs;
    f32 sn;
    u8 *pkt;

    pkt = packet;
    c = *color;
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
    pos.x = c.x;
    pos.y = c.y;
    pos.z = c.z;
    func_00108EF0(matrix, &obj->scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    outer = data->outer;
    inner = data->inner;
    for (i = 0; i < 36; i++) {
        if (!i) {
            a = data->step + j;
            cs = func_00108030(obj->table, a, 1);
            sn = func_00108030(obj->table, a, 0);
            quad[0].x = cs * inner;
            quad[0].z = sn * inner;
            quad[2].x = cs * outer;
            quad[2].z = sn * outer;
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
        }
        a = j + (data->step + 10);
        cs = func_00108030(obj->table, a, 1);
        sn = func_00108030(obj->table, a, 0);
        quad[1].x = cs * inner;
        quad[1].z = sn * inner;
        quad[3].x = cs * outer;
        quad[3].z = sn * outer;
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
        j += 10;
    }
}

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

static void func_01E008B0_b034(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b034((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b034((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00E60_b034(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b034", func_01E01030_b034);

/* shape b034:01E01E70, 73 insns: a blinking yellow glow (yellow on odd ticks, olive on even): in by 12 up to 0x80 for 20 ticks, then out by 9 once the scene state is under 40, and ends */

typedef struct {
    u8 pad0[0x54];
    s16 t;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b034_01E01E70;

typedef struct {
    u8 pad[0xA900];
    s32 state;
} Game_b034_01E01E70;

static s32 func_01E01E70_b034(Game_b034_01E01E70 *g, Obj_b034_01E01E70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->h56 = 10;
        o->mode = 2;
    }
    if (o->t < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
    } else if (g->state < 40) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x40);
    }
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b034:01E01FA0, 110 insns: glow pair (two colours) that fades in for 20 frames, fades out on the scene's cue,
   and blinks between two brightness levels */

typedef struct Glow_b034_01E01FA0 {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 f20;
    u8 pad24[0x24];
    s32 f48;
    u8 pad4C[8];
    s16 age;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_b034_01E01FA0;

typedef struct Scn_b034_01E01FA0 {
    u8 pad0[0xA900];
    s32 cue;
} Scn_b034_01E01FA0;

static s32 func_01E01FA0_b034(Scn_b034_01E01FA0 *w, Glow_b034_01E01FA0 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->f48 = 0;
        o->h56 = func_0019A5C8() % 7;
        o->state = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
    }
    if (o->age < 20) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0xC;
        }
    } else if (w->cue < 40) {
        if (o->c0[3] > 10) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 10) {
            o->c1[3] -= 9;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->age % 2 == 1) {
        func_001076F0(o->c0, 0x40, 0x40, 0x10);
        func_001076F0(o->c1, 0x40, 0x40, 0x10);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x20);
        func_001076F0(o->c1, 0x80, 0x80, 0x20);
    }
    func_00205C40((s32)&o->f20);
    o->f20 = 0;
    o->age++;
    return 0;
}

/* shape b034:01E02160, 73 insns: a blinking two-colour glow (white/red on odd ticks, grey/deep red on even): in by 16 up to 0xA0 for 10 ticks; out by 13 once the scene state is under 40, and ends */

typedef struct {
    u8 pad0[0x54];
    s16 t;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b034_01E02160;

typedef struct {
    u8 pad[0xA900];
    s32 state;
} Game_b034_01E02160;

static s32 func_01E02160_b034(Game_b034_01E02160 *g, Obj_b034_01E02160 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h56 = 0;
        o->mode = 2;
    }
    if (o->t < 10) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x10;
        }
    }
    if (g->state < 40) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x20, 0x20);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0xC0, 0x10, 0x10);
    }
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

static s32 func_01E02290_b034(void *arg0, Spark_b034_01E02290 *o) {
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

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    u8 pad56[2];
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
} Obj_b034_01E02470;

static s32 func_01E02470_b034(s32 unused, Obj_b034_01E02470 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 20.0f;
        if (o->h50 != 2) {
            func_001076F0(o->c60, 0x10, 0x10, 0xF0);
            func_001076F0(o->c64, 0xF0, 0xF0, 0xF0);
        } else {
            func_001076F0(o->c60, 0x10, 0x80, 0x80);
            func_001076F0(o->c64, 0x10, 0x10, 0x10);
        }
        o->hE = o->h50;
        o->h5A = func_0019A5C8() % 360;
        o->h58 = 2;
        o->c60[3] = 0;
        o->h6 = 0;
        if (o->h50 != 2) {
            o->h8 = 18;
        } else {
            o->h8 = 30;
        }
    }
    if (o->h54 < o->h8) {
        if (o->c64[3] < 0x80) {
            o->c64[3] += 12;
        }
    } else if (o->h50 != 2) {
        if (o->c64[3] > 10) {
            o->c64[3] -= 9;
        } else {
            o->h58 = 0;
        }
    } else {
        if (o->c64[3] > 8) {
            o->c64[3] -= 7;
        } else {
            o->h58 = 0;
        }
    }
    if (o->hE != 2) {
        o->h6 = o->f48 - 45.0f;
    }
    if (o->h6 < 0) {
        o->h6 = 0;
    }
    if (o->h54 != 0) {
        o->f48 += 10.0f;
    }
    o->h54++;
    return 0;
}

/* shape b034:01E02650, 81 insns: a grey-red blinker: fades in by 16 to 0xA0 while the game timer is below 200 and the stage
   counter is at least 360; fades by 13 while the game state is below 40; colours blink by frame parity */

typedef struct {
    u8 pad0[0xA900];
    s32 state;
    u8 padA904[0xFC];
    s16 count;
    u8 padAA02[0x10];
    s16 timer;
} Game_b034_01E02650;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b034_01E02650;

static s32 func_01E02650_b034(Game_b034_01E02650 *g, Obj_b034_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->sub = 0;
        o->state = 2;
    }
    if (g->timer < 0xC8) {
        if (g->count >= 0x168) {
            if (o->c0[3] < 0xA0) {
                o->c0[3] += 0x10;
            }
        }
    }
    if (g->state < 0x28) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x20, 0x20);
    } else {
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        func_001076F0(o->c1, 0xC0, 0x10, 0x10);
    }
    o->t++;
    return 0;
}

/* shape b034:01E027A0, 115 insns: an orange tumbling spark (b041:01E01C40 shape): size 1..8, random sub-frame 0..3 and turn on all
   three axes, rising from 0 by 3..18, angle, width 1..8, hold 1..3; full alpha until the hold, then down by 15 */

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
} Obj_b034_01E027A0;

static s32 func_01E027A0_b034(void *arg0, Obj_b034_01E027A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 8 + 1;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 16 + 3;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b034:01E02970, 378 insns, 1 copy: a red double trail band: on start 0xA = scene count + 5..54, radii from the
   scene (0xA920, +0xA924 / +0xA930), grey 0x70, both trails (0x280-byte slots at 0x4470, 20 points) filled with the
   start point, the second row 30 degrees back and 0xA/10 up; fades in by 0x15 while tick < 10, else out by 9; each
   tick the heading turns 12 and both trails take a new point at height 0x8, colour blinks red, band count to 18 */

typedef struct {
    Vec4f a[20];
    Vec4f b[20];
} Trail_b034_01E02970;

typedef struct {
    u8 pad0[0x4470];
    Trail_b034_01E02970 slot[1];
    u8 pad46F0[0xA920 - 0x46F0];
    f32 ra;
    f32 rb;
    u8 padA928[8];
    f32 rc;
    u8 padA934[0xAA06 - 0xA934];
    s16 count;
    u8 padAA08[0xAD14 - 0xAA08];
    u8 sin[4];
} Game_b034_01E02970;

typedef struct {
    u8 pad0[6];
    s16 n;
    s16 h8;
    s16 hA;
    u8 padC[0x48 - 0xC];
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
} Obj_b034_01E02970;

static s32 func_01E02970_b034(Game_b034_01E02970 *g, Obj_b034_01E02970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    f32 f;
    f32 r;
    Vec4f *p;
    s16 i;

    if (o->mode == 1) {
        f = o->hA = g->count + (func_0019A5C8() % 50 + 5);
        o->h8 = func_0019A5C8() % 2;
        f /= 10.0f;
        func_001076F0(o->col2, 0x70, 0x70, 0x70);
        v.y = 0.0f;
        o->ang = func_0019A5C8() % 360;
        if (v.x) {
            r = g->ra;
        } else {
            r = g->ra + g->rb;
        }
        v.z = r * func_00108030(g->sin, o->ang, 0);
        v.x = r * func_00108030(g->sin, o->ang, 1);
        for (i = 0, p = g->slot[o->idx].a; i < 19; i++, p++) {
            p->x = v.x;
            p->y = v.y;
            p->z = v.z;
        }
        if (v.x) {
            r = g->ra + g->rc;
        } else {
            r = g->rc + (g->ra + g->rb);
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
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x15;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    f = o->hA;
    f /= 10.0f;
    o->ang += 12;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    v.y = o->h8;
    if (v.x) {
        r = g->ra;
    } else {
        r = g->ra + g->rb;
    }
    v.z = r * func_00108030(g->sin, o->ang, 0);
    v.x = r * func_00108030(g->sin, o->ang, 1);
    func_01E00080_b034(&g->slot[o->idx].a[19], 20, 0, &v);
    v.y = f + o->h8;
    if (v.x) {
        r = g->ra + g->rc;
    } else {
        r = g->rc + (g->ra + g->rb);
    }
    v.z = r * func_00108030(g->sin, o->ang - 30, 0);
    v.x = r * func_00108030(g->sin, o->ang - 30, 1);
    func_01E00080_b034(&g->slot[o->idx].b[19], 20, 0, &v);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x50, 0x10, 0x20);
    } else {
        func_001076F0(o->col, 0x40, 8, 0x10);
    }
    if (o->t != 0) {
        if (o->n < 18) {
            o->n++;
        }
    }
    o->t++;
    return 0;
}

/* shape b034:01E02F60, 185 insns: a fire glow, kind 0 (size 4, inner 0.4, holds 10 ticks) or 1 (size 20, holds 26):
   white with an orange rim (0x80/0x40/0x10), three random angle words; alpha up by 0x40 to 0xC0 for the hold, then
   down by 4; kind 0 grows by 2.45 and its inner part by 0.25 to 15, kind 1 grows by 0.15 with the inner part 7 smaller,
   rises 1.2 a tick, turns two angles by 0x100 and flickers to 0xC0 white and a 0xA0/0x60/0x30 rim every other
   tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[6];
    s16 kind;
    u8 pad10[4];
    f32 f14;
    u8 pad18[8];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b034_01E02F60;

static s32 func_01E02F60_b034(s32 arg0, Fx_b034_01E02F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->kind = o->f50;
        if (o->kind == 0) {
            o->f48 = 4.0f;
            o->f4C = 0.4f;
        } else if (o->kind == 1) {
            o->f48 = 20.0f;
            o->f4C = 0.0f;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x40, 0x10);
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
        o->col2[3] = 0;
        if (o->kind == 0) {
            o->hold = 10;
        }
        if (o->kind == 1) {
            o->hold = 26;
        }
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->f48 += 2.45f;
        if (o->tick != 0) {
            if (o->f4C < 15.0f) {
                o->f4C += 0.25f;
            }
        }
    } else if (o->kind == 1) {
        o->f48 += 0.15f;
        o->f4C = o->f48 - 7.0f;
        if (o->tick != 0) {
            o->f14 += 1.2f;
        }
        o->w24 += 0x100;
        o->w28 += 0x100;
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0x80, 0x40, 0x10);
        } else {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0xA0, 0x60, 0x30);
        }
    }
    o->tick++;
    return 0;
}

/* shape b034:01E03250, 194 insns: b747:01E02500 family mote by kind (0x50: size 15/20, speed 5..10, 10..19 or 150..299, kind 2 dark 0x10 grey), variant 0..3, kind kept in 0xA, 0x50 0..29, random 0x5A, 0x8 0..34, hold 15..24 (3..6 when 0x50 is 2); alpha up by 0x2A to 0x80 during the hold, then down by 5 (8 for kind 2); kind 2 rises 1 and grows 1.8 a tick, the others turn by their speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[2];
    s16 speed;
    f32 pos[3];
    u8 pad1C[0x2C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b034_01E03250;

static s32 func_01E03250_b034(s32 arg0, Fx_b034_01E03250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 15.0f;
        if (o->f50 == 1) {
            o->f48 = 20.0f;
        }
        if (o->f50 == 2) {
            o->f48 = 20.0f;
        }
        if (o->f50 == 0) {
            o->speed = func_0019A5C8() % 6 + 5;
        }
        if (o->f50 == 1) {
            o->speed = func_0019A5C8() % 10 + 10;
        }
        if (o->f50 == 2) {
            o->speed = func_0019A5C8() % 150 + 150;
        }
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        if (o->f50 == 2) {
            func_001076F0(o->col, 0x10, 0x10, 0x10);
        }
        o->fA = o->f50;
        o->f50 = func_0019A5C8() % 30;
        o->f5A = func_0019A5C8() % 360;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 10 + 15;
        if (o->f50 == 2) {
            o->hold = func_0019A5C8() % 3 + 4;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->fA != 2) {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->fA != 2 && o->tick != 0) {
        o->f50 += o->speed;
    }
    if (o->fA == 2) {
        o->pos[1] += 1.0f;
        o->f48 += 1.8f;
    }
    o->tick++;
    return 0;
}

/* shape b034:01E03560, 184 insns: a two-colour flash of kind 0x50: kind 0 pale yellow over cream for 70 ticks (alpha up
   by 32 to 0x80 for 45 ticks, then easing down by 12 to 0x60), kind 1 magenta for 160 ticks (up by 24 to 0x60), kind 2
   near-white for 16 ticks (up by 18 to 0x80); afterwards both alphas fade by 7 (kind 2 by 4) and it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Flash_b034_01E03560;

static s32 func_01E03560_b034(s32 arg0, Flash_b034_01E03560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xFF, 0, 0xFF);
            func_001076F0(o->col2, 0xFF, 0, 0xFF);
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
        }
        if (o->kind == 0) {
            o->hold = 70;
        }
        if (o->kind == 1) {
            o->hold = 160;
        }
        if (o->kind == 2) {
            o->hold = 16;
        }
        o->mode = 2;
    }
    if (o->t < o->hold) {
        if (o->kind == 0) {
            if (o->t < 45) {
                if (o->col[3] < 0x80) {
                    o->col[3] += 0x20;
                }
                if (o->col2[3] < 0x80) {
                    o->col2[3] += 0x20;
                }
            } else if (o->t < 50) {
                if (o->col[3] > 0x60) {
                    o->col[3] -= 12;
                }
                if (o->col2[3] > 0x60) {
                    o->col2[3] -= 12;
                }
            }
        } else if (o->kind == 1) {
            if (o->col[3] < 0x60) {
                o->col[3] += 0x18;
            }
            if (o->col2[3] < 0x60) {
                o->col2[3] += 0x18;
            }
        } else if (o->kind == 2) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x12;
            }
            if (o->col2[3] < 0x80) {
                o->col2[3] += 0x12;
            }
        }
    } else if (o->kind != 2) {
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
    o->t++;
    return 0;
}

/* shape b034:01E03840, 130 insns: b144:01E02430-style spark: size 30..69, purple or orange at random, spin from 0,
   speed 35..50, held 13..15 at alpha 0x80, then fades by 15 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b034_01E03840;

static s32 func_01E03840_b034(s32 arg0, Fx_b034_01E03840 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 40 + 30;
        o->f56 = func_0019A5C8() % 4;
        if (func_0019A5C8() % 2 == 0) {
            func_001076F0(o->col, 0x40, 0x10, 0x80);
        } else {
            func_001076F0(o->col, 0x80, 0x40, 0x10);
        }
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = 0;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 35;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 13;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b034:01E03A50, 63 insns: a red rising ring (20 x 3) that turns 0x100 and climbs 1.2 a tick: in by 64 up to 0x80 for 26 ticks, then out by 4 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    s32 w24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b034_01E03A50;

static s32 func_01E03A50_b034(s32 arg0, Obj_b034_01E03A50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->hE = o->h50;
        o->f48 = 20.0f;
        o->f4C = 3.0f;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->mode = 2;
        o->col2[3] = 0;
        o->h6 = 0;
    }
    if (o->t < 26) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->w24 += 0x100;
    o->f14 += 1.2f;
    o->t++;
    return 0;
}

/* shape b034:01E03B50, 266 insns: a five-kind glow (kind 0x50 = 0, 1, 2, 10, 11): size 200 / 1000 / 800 / 230 / 110,
   white, grey or mid colour with a blue or red second colour; it fades in for 18 / 6 / 18 / 6 / 100 ticks by
   12 (second colour) / 42 / 7 / 32 / 24 (to 0x60), then fades out by 9 / 9 / 9 after scene time 500 / 6 / 4; kinds 10
   and 11 spin a quarter turn a tick */

typedef struct {
    u8 pad0[0xAA12];
    s16 time;
} G_b034_01E03B50;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 len;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b034_01E03B50;

static s32 func_01E03B50_b034(G_b034_01E03B50 *g, Fx_b034_01E03B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 200.0f;
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0x10, 0x10, 0xF0);
        } else if (o->kind == 1) {
            o->f48 = 1000.0f;
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0x80, 0x10, 0x10);
        } else if (o->kind == 2) {
            o->f48 = 800.0f;
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
            func_001076F0(o->col2, 0x80, 0x10, 0x10);
        } else if (o->kind == 10) {
            o->f48 = 230.0f;
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0x10, 0x10, 0xF0);
        } else if (o->kind == 11) {
            o->f48 = 110.0f;
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0x10, 0x10, 0xF0);
        }
        o->hE = o->kind;
        o->state = 2;
        o->h6 = 0;
        if (o->kind == 0) {
            o->len = 18;
        } else if (o->kind == 1) {
            o->len = 6;
        } else if (o->kind == 2) {
            o->len = 18;
        } else if (o->kind == 10) {
            o->len = 6;
        } else if (o->kind == 11) {
            o->len = 100;
        }
    }
    if (o->t < o->len) {
        if (o->kind == 0) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 12;
            }
        }
        if (o->kind == 1) {
            if (o->col[3] < 0x80) {
                o->col[3] += 42;
            }
        }
        if (o->kind == 2) {
            if (o->col[3] < 0x80) {
                o->col[3] += 7;
            }
        }
        if (o->kind == 10) {
            if (o->col[3] < 0x80) {
                o->col[3] += 32;
            }
        }
        if (o->kind == 11) {
            if (o->col[3] < 0x60) {
                o->col[3] += 24;
            }
        }
    } else if (o->kind == 0) {
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->state = 0;
        }
    } else if (o->kind == 1) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
    } else if (o->kind == 2) {
        if (g->time > 500) {
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            } else {
                o->state = 0;
            }
        }
    } else if (o->kind == 10) {
        if (o->col[3] > 7) {
            o->col[3] -= 6;
        } else {
            o->state = 0;
        }
    } else if (o->kind == 11) {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->state = 0;
        }
    }
    if (o->kind == 10 || o->kind == 11) {
        func_00205C40((s32)o->rot);
        o->rot[0] += 0x4000;
    }
    o->t++;
    return 0;
}

/* shape b034:01E03F80, 51 insns: b718:01E03D10 family volume fader (to 0x30 after scene state 30), full volume at state 2 */

typedef struct {
    u8 pad[0xa900];
    s32 state;
} Game_b034_01E03F80;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 padV[0x6];
    s16 mode;
} Fade_b034_01E03F80;

static s32 func_01E03F80_b034(Game_b034_01E03F80 *g, Fade_b034_01E03F80 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
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
    if (g->state == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b034:01E04050, 31 insns: func_001F7170(3, 2, &a, &b, 0) with copies of the module's floats at 0x01E06E00 and
   0x01E06E08; the effect stops after tick 0x40; return 0 */

typedef struct {
    f32 v;
} F_b034_01E04050;

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b034_01E04050;

extern F_b034_01E04050 D_01E06E00_b034;
extern F_b034_01E04050 D_01E06E08_b034;

static s32 func_01E04050_b034(s32 arg0, Fx_b034_01E04050 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b034_01E04050 a;
    F_b034_01E04050 b;

    a = D_01E06E00_b034;
    b = D_01E06E08_b034;
    func_001F7170(3, 2, &a, &b, 0);
    o->tick++;
    if (o->tick >= 0x41) {
        o->mode = 0;
    }
    return 0;
}

/* shape b034:01E040D0, 146 insns: b041:01E020B0's purple veil with a 14 zoom offset; the zoom follows 14 x sin of 0x5A (turning 4 a tick, table at scene +0xAD14); brightens by 10 (below 0x40) for 144 ticks, then fades by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b034_01E040D0;

typedef struct {
    f32 s, t;
    Xyz_b034_01E040D0 p;
} Tv_b034_01E040D0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b034_01E040D0 v[2];
    u8 tail[0x20];
} Tex_b034_01E040D0;

typedef struct {
    u8 pad0[0xAD14];
    u8 sin[1];
} Ctx_b034_01E040D0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b034_01E040D0;

static s32 func_01E040D0_b034(Ctx_b034_01E040D0 *g, Fx_b034_01E040D0 *o) {
    extern void func_002087A0(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    Tex_b034_01E040D0 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    z = 14.0f;
    ((Tex_b034_01E040D0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b034_01E040D0 *)(s32)&pk)->size = 5;
    ((Tex_b034_01E040D0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b034_01E040D0 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x70;
    pk.g = 0x60;
    pk.b = 0x80;
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
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    o->f48 = 14.0f * func_00108030(g->sin, o->ang, 0);
    o->ang += 4;
    if (o->tick < 0x90) {
        if (o->col[3] < 0x40) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b034", func_01E04320_b034);

/* shape b034:01E05330, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b034_01E05330 {
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
} Slot_b034_01E05330;

typedef struct Obj_b034_01E05330 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b034_01E05330 slots[0x96];
    u8 padB[0xa904 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xaa0a - 0xa904 - 4];
    s16 fB2B0;
} Obj_b034_01E05330;

static s32 func_01E05330_b034(Obj_b034_01E05330 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b034_01E05330 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b034", func_01E054C0_b034);

INCLUDE_ASM("asm/nonmatchings/mod/b034", func_01E05A90_b034);

typedef struct {
    f32 x, y, z, w;
} Vec_b034_01E06010;

typedef struct {
    s16 a, b;
} Pair_b034_01E06010;

typedef struct {
    u8 pad0[0xA870];
    Vec_b034_01E06010 pos;
    Vec_b034_01E06010 tab[8];
    u8 padA900[0xC];
    s32 tex;
    u8 padA910[0x10];
    f32 radius;
    f32 extra;
    u8 padA928[0xC];
    f32 h[6];
    u8 padA94C[0xA9E4 - 0xA94C];
    Pair_b034_01E06010 pair[6];
    u8 padA9FC[6];
    s16 height;
    s16 rings;
    u8 padAA06[8];
    s16 flag;
    u8 padAA10[0xAD14 - 0xAA10];
    u8 trig[4];
} Scene_b034_01E06010;

typedef struct {
    u8 pad0[0x60];
    u8 col[4];
} Obj_b034_01E06010;

extern void b034_01E06CF0(Vec_b034_01E06010 *, Vec_b034_01E06010 *, Vec_b034_01E06010 *, f32, f32);

static void func_01E06010_b034(Scene_b034_01E06010 *g, Obj_b034_01E06010 *o, void *p) {
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_001091B0(void *, void *, void *);
    extern void func_00195108(void *, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b034_01E06010 quad[2];
    Vec_b034_01E06010 pos;
    Vec_b034_01E06010 out;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 ang[2];
    s16 i;
    s16 j;
    s16 k;
    f32 d;
    f32 r;

    rot[0] = 0;
    rot[2] = 0;
    if (g->flag != 0) {
        rot[1] = 0;
    } else {
        rot[1] = 0x8000;
    }
    pos.x = g->pos.x;
    pos.y = g->pos.y;
    pos.z = g->pos.z;
    func_00108EF0(m, NULL, rot, &pos);
    func_001091B0(p, o->col, o->col);
    for (i = 0; i < 6; i++) {
        d = g->height;
        func_00195108(quad, 0x20);
        d -= g->h[i];
        if (d > 10.0f) {
            d = 10.0f;
        }
        if (g->height > g->h[i]) {
            quad[0] = g->tab[g->pair[i].a];
            quad[1] = g->tab[g->pair[i].b];
            b034_01E06CF0(&out, &quad[0], &quad[1], 10.0f, d);
            quad[1].x = out.x;
            quad[1].y = out.y;
            quad[1].z = out.z;
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->tex, (u32)depth[0]);
        }
    }
    func_00195108(quad, 0x20);
    ang[0] = -90;
    ang[1] = -90;
    for (i = 0; i < g->rings; i++) {
        for (k = 0; k < 2; k++) {
            if (k) {
                r = g->radius + g->extra;
            } else {
                r = g->radius;
            }
            for (j = 0; j < 2; j++) {
                quad[j].z = r * func_00108030(g->trig, -ang[k], 0);
                quad[j].x = r * func_00108030(g->trig, -ang[k], 1);
                if (!j) {
                    ang[k] += 5;
                }
            }
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->tex, (u32)depth[0]);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b034", func_01E06420_b034);

/* shape b034:01E06CF0, 60 insns: lerp of a 4-float point: out = a + (b - a) / n * t (xyz) */

typedef struct {
    f32 x, y, z, w;
} V4_b034_01E06CF0;

static void func_01E06CF0_b034(V4_b034_01E06CF0 *out, V4_b034_01E06CF0 *a, V4_b034_01E06CF0 *b, f32 n, f32 t) {
    V4_b034_01E06CF0 s;
    V4_b034_01E06CF0 e;
    V4_b034_01E06CF0 d;

    s = *a;
    e = *b;
    d.x = (e.x - s.x) / n;
    d.y = (e.y - s.y) / n;
    d.z = (e.z - s.z) / n;
    d.x = s.x + d.x * t;
    d.y = s.y + d.y * t;
    d.z = s.z + d.z * t;
    *out = d;
}
