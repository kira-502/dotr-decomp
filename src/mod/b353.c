#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b353(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00100_b353(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E00550_b353(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00100_b353((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b353 in the
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

static void func_01E00880_b353(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00100_b353((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00B40_b353(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b353:01E00EA0, 92 insns: sets the scene colour to red 0x80 and counts its timer; at 0x44 spawns two b353:01E01010 effects
   (sides 0 and 1); at 0x4B puts the effect point at the model joint (height halfway to the model's centre) and spawns eight
   b353:01E016A0, fifty b353:01E01830, one b353:01E01AC0 and one b353:01E01C00 effect */

typedef struct {
    u8 pad0[0x2D0];
    f32 x, y, z;
    u8 pad2DC[0x6DC4 - 0x2DC];
    u8 r, g, b, a;
    u8 pad6DC8[0x46];
    s16 joint;
    u8 pad6E10[0x16];
    s16 side;
    u8 pad6E28[4];
    s16 t;
} Scene_b353_01E00EA0;

static void func_01E00EA0_b353(Scene_b353_01E00EA0 *s) {
    extern void b353_01E01010(void);
    extern void b353_01E016A0(void);
    extern void b353_01E01830(void);
    extern void b353_01E01AC0(void);
    extern void b353_01E01C00(void);
    extern s32 b353_01E02400(Scene_b353_01E00EA0 *, void *, s32);
    extern s32 b353_01E02520(Scene_b353_01E00EA0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f a;
    Vec4f c;
    s32 i;

    s->r = 0x80;
    s->g = 0;
    s->b = 0;
    s->a = 0;
    s->t++;
    if (s->t == 0x44) {
        s->side = 0;
        b353_01E02400(s, b353_01E01010, 0);
        s->side = 1;
        b353_01E02400(s, b353_01E01010, 0);
    }
    if (s->t == 0x4B) {
        func_001F5620(func_001F53A0(), s->joint, &a);
        func_001F5F90(func_001F5380(), &c);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z + (c.z - a.z) / 2.0f;
        s->side = 1;
        for (i = 0; i < 8; i++) {
            b353_01E02400(s, b353_01E016A0, 0);
        }
        for (i = 0; i < 0x32; i++) {
            b353_01E02520(s, b353_01E01830, 0);
        }
        b353_01E02520(s, b353_01E01AC0, 0);
        b353_01E02400(s, b353_01E01C00, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b353", func_01E01010_b353);

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b353_01E016A0;

static s32 func_01E016A0_b353(s32 unused, Obj_b353_01E016A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 6;
        o->h34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->h30 = 0;
        o->h3A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 20 + 10;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    o->h30 += o->hE;
    o->h32++;
    return 0;
}

/* shape b353:01E01830, 164 insns: variant of b479:01E020E0 (tumbling spark) with a random size 4..11 that does
   not grow and colour (0x80,0x40,0xFF) */

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
    u8 pad3C[0x18];
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b353_01E01830;

static s32 func_01E01830_b353(s32 arg0, Spark_b353_01E01830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = func_0019A5C8() % 8 + 4;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
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
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b353:01E01AC0, 77 insns: b205:01E01B90 with the game value at 0x6E2C and colour (0x80,0x40,0xFF); a spinning, growing flash: on start size 180, colours white and (0x80,0xFF,0x80),
   f5A/f5C 10; the second alpha grows by 0x60 (below 0xC0) for 8 ticks, then fades out by 15 and stops; turns by
   0x4000 and grows by 0.4 every tick after the first; ends when the game value 0x6E2C is 0xC3 */

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
} Fx_b353_01E01AC0;

typedef struct {
    u8 pad[0x6E2C];
    s16 v;
} Game_b353_01E01AC0;

static s32 func_01E01AC0_b353(Game_b353_01E01AC0 *g, Fx_b353_01E01AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 180.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 8) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
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
    if (g->v == 0xC3) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b353:01E01C00, 93 insns: a screen fog: on start sets the scene fog block (0x6AA0: 128, 4, 2, 0, position from
   the effect, colour (0, 120, 0)); its strength 0x6AC8 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 */

typedef struct {
    u8 pad0[0x6AA0];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad6ACC[0x6DC0 - 0x6ACC];
    s32 count;
} Game_b353_01E01C00;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b353_01E01C00;

static s32 func_01E01C00_b353(Game_b353_01E01C00 *g, Fx_b353_01E01C00 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 4.0f;
        g->f2A08 = 2.0f;
        g->f2A0C = 0.0f;
        g->f2A20 = 0.0f;
        g->f2A24 = 120.0f;
        g->strength = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->strength < 1.0f) {
            g->strength += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2A00);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01D80_b353(void) {
    return 0;
}

/* shape b353:01E01D90, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 11-15, group 5
   cells 0-1 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x6A20];
    s32 tex5[2];
} Scene_b353_01E01D90;

static void func_01E01D90_b353(s32 arg0, Scene_b353_01E01D90 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 11; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b353:01E01E40 (b353), 366 insns, 1 copy: b353 scene manager in b098:01E01F30 form: setup (six joints, two 256
   s8 jitter tables, the second partly overwritten 100..179), step b353:01E00EA0 and the 0x40 slots (b353:01E01010,
   016A0, 01C00 by name), draw the rain (b353:01E02660) and b353:01E016A0 pieces, step the 0x70 effects (counting the
   b353:01E01D80 ones), draw the b353:01E01830 sparks and b353:01E01AC0 flash; scene code from the timer */

typedef struct {
    u8 pad0[0x24];
    s32 (*fn)();
    u8 pad28[8];
    s16 h30;
    u8 pad32[2];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b353_01E01E40;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Fx_b353_01E01E40;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    u8 padC[0x14];
    Vec4f v20;
    u8 pad30[0x50];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x238];
    s32 w310;
    s32 w314;
    s32 w318;
    u8 pad31C[0x60];
    s32 tex37C;
    Slot_b353_01E01E40 slot[150];
    Fx_b353_01E01E40 fx[150];
    u8 pad6AA0[0x50];
    Vec4f pts[4][10];
    u8 pad6D70[0x10];
    Vec4f joint;
    u8 pad6D90[0x30];
    s32 count;
    u8 pad6DC4[8];
    s32 ot;
    u8 pad6DD0[0x3C];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad6E18[0x10];
    s16 id;
    s16 turn;
    s16 frame;
    u8 pad6E2E[2];
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b353_01E01E40;

static s32 func_01E01E40_b353(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b353_01E01010();
    extern void b353_01E02660();
    extern void func_01E00EA0_b353();
    extern void func_01E01D90_b353();
    extern void func_01E00550_b353();
    extern void func_01E00880_b353();
    extern void func_01E00B40_b353();
    extern s32 func_01E016A0_b353();
    extern s32 func_01E01C00_b353();
    Scene_b353_01E01E40 *g = (Scene_b353_01E01E40 *)arg0;
    s16 n;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 ang[4];
    u8 buf[0x90];
    s32 i;

    n = 0;
    m = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x71A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 120;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1D, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x20, 0);
        g->jD = func_001F5560(func_001F53A0(), 4, 0);
        g->jE = func_001F5560(func_001F53A0(), 5, 0);
        g->jF = func_001F5560(func_001F53A0(), 6, 0);
        func_01E01D90_b353(0, g);
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    func_01E00EA0_b353(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (s32 (*)())b353_01E01010) {
                b353_01E01010(g, &g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E016A0_b353) {
                func_01E016A0_b353(g, &g->slot[i]);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E01C00_b353) {
                func_01E01C00_b353(g, &g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (s32 (*)())b353_01E01010) {
                if (g->slot[i].h30 == 0) {
                    g->f4 = 0.0f;
                }
                if (g->slot[i].h30 == 1) {
                    g->f4 = 1.0f;
                }
                if (g->frame < 0x4C) {
                    func_001F5620(func_001F53A0(), g->jA, &g->joint);
                }
                g->v20 = g->joint;
                g->f0 = 2.5f;
                if (g->turn != 0) {
                    g->f8 = -3.5f;
                } else {
                    g->f8 = 3.5f;
                }
                b353_01E02660(g, &g->slot[i], g->pts[g->slot[i].h30], g->pts);
            }
            if (g->slot[i].fn == (s32 (*)())func_01E016A0_b353) {
                g->tex88 = g->tex37C;
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                func_01E00550_b353(g, &g->slot[i], buf, g->jit);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != (s32 (*)())func_01E01D80_b353) {
                    g->fx[i].fn(g, &g->fx[i]);
                } else {
                    n++;
                }
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            m++;
            if (g->fx[i].fn == (s32 (*)())func_01E01830_b353) {
                m++;
                g->tex88 = g->tex37C;
                func_00106080(rm2, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                func_01E00880_b353(g, &g->fx[i], 0x20, g->fx[i].pos);
            }
            if (g->fx[i].fn == (s32 (*)())func_01E01AC0_b353) {
                g->hB8 = 0x24;
                func_01E00B40_b353(g, &g->fx[i], 0x21, &g->fx[i].pos);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x41) {
        return 1;
    }
    if (g->frame == 0x73) {
        return 4;
    }
    if (g->frame == 0x4B) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b353:01E02400, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x6E26 and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b353_01E02400;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0xB0];
    Slot_b353_01E02400 s[150];
    u8 pad2900[0x44C4];
    u8 r, g, b, a;
    u8 pad6DC8[0x5E];
    s16 v;
} Pool_b353_01E02400;

static s32 func_01E02400_b353(Pool_b353_01E02400 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b353_01E02400 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b353:01E02520, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b353_01E02520 {
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
} Slot_b353_01E02520;

typedef struct Obj_b353_01E02520 {
    u8 pad0[0x2D0];
    f32 pos[3];
    u8 padA[0x2624];
    Slot_b353_01E02520 slots[0x96];
    u8 padB[0x324];
    u8 rgba[4];
    u8 padC[0x5E];
    s16 fB2B0;
} Obj_b353_01E02520;

static s32 func_01E02520_b353(Obj_b353_01E02520 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b353_01E02520 *s = NULL;
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

/* shape b353:01E02660 (B353KPOINT_RAIN_2), 285 insns, 1 copy: rain streaks: per segment, a ring of 18 angles x 4
   offset quads drawn between consecutive points */

typedef struct {
    u8 r, g, b, a;
} Col_b353_01E02660;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0x14];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0xAC];
    u8 trig[4];
} Own_b353_01E02660;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b353_01E02660 col;
} Fx_b353_01E02660;

typedef struct {
    u32 tag[2];
    u8 pk[0x94];
} Buf_b353_01E02660;

static void func_01E02660_b353(Own_b353_01E02660 *g, Fx_b353_01E02660 *o, Vec4f *pts, Vec4f *base) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00108EF0();
    extern void func_00107990();
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630();
    extern void func_002075F0();
    f32 depth[4];
    Vec4f q[4];
    Vec4f v[2];
    u8 mtx[0x40];
    Vec4f pos;
    Buf_b353_01E02660 buf;
    Col_b353_01E02660 col;
    s16 n;
    s32 j;
    u8 *p;
    s32 ot;
    s32 i;
    s32 k;
    s32 last;
    s32 cnt;
    s16 a;
    s32 ang;
    f32 t;
    f32 r;
    f32 z;
    f32 h;

    ot = (s32)func_00207500();
    n = o->n;
    t = 0.0f;
    p = buf.pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    pos.x = g->px;
    pos.y = g->py;
    pos.z = g->pz;
    func_00108EF0(mtx, 0, 0, &pos);
    cnt = n;
    col = o->col;
    v[0] = *pts;
    v[1] = *base;
    v[0].x -= v[1].x;
    v[0].y -= v[1].y;
    v[0].z -= v[1].z;
    v[0].x = g->x;
    v[0].y = -v[0].y;
    v[0].z = g->z;
    i = 0;
    last = cnt - 1;
    h = v[0].z;
    goto test;
loop:
    {
        a = 0;
        func_00107990(p, &col, 1);
        col.a -= o->col.a / cnt;
        func_00107990(p, &col, 2);
        for (k = 0, ang = -90; k < 18; k++, ang += 10) {
            r = v[0].x * func_00108030(g->trig, ang, 0);
            z = h * func_00108030(g->trig, ang, 1);
            for (j = 0; j < 4; j++) {
                q[0].x = pts->x;
                q[0].y = pts->y;
                q[0].z = pts->z;
                q[1].x = pts->x;
                q[1].y = pts->y;
                q[1].z = pts->z;
                q[2].x = pts[1].x;
                q[2].y = pts[1].y;
                q[2].z = pts[1].z;
                q[3].x = pts[1].x;
                q[3].y = pts[1].y;
                q[3].z = pts[1].z;
                func_00107070(q, 0, r);
                func_00107070(q, 2, z);
                if (j == 0) {
                    q[0].z += 0.05f;
                    q[2].z += 0.05f;
                } else if (j == 1) {
                    q[0].z -= 0.05f;
                    q[2].z -= 0.05f;
                } else if (j == 2) {
                    q[0].x += 0.05f;
                    q[2].x += 0.05f;
                } else if (j == 3) {
                    q[0].x -= 0.05f;
                    q[2].x -= 0.05f;
                }
                if (func_00205630(q, 0x70000000, mtx, p, depth)) {
                    func_002075F0(p, ot, (u32)depth[0]);
                }
                a += 30;
            }
        }
        pts++;
        t += 1.0f;
        i++;
    }
test:
    if (i < last) goto loop;
}
