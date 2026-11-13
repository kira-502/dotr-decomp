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

static void func_01E00080_b555(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b008_01E004D0;

static void func_01E00920_b555(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00080_b555((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b555:01E00EA0 (IWSmoke6), 180 insns, 1 copy: b046:01E00DD0 family sprite quad with the b016:01E00ED0 depth
   modes: blend by the mode's high nibble (0x48 / 0x44 / 0x42), size 0x38 square turned by 0x10 through the object
   table, low nibble 0 = depth, 1 = far z */

typedef struct Cam_b555_01E00EA0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b555_01E00EA0_unused;

typedef struct Obj_b555_01E00EA0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b555_01E00EA0;

typedef struct Xyz_b555_01E00EA0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b555_01E00EA0;

typedef struct Uv_b555_01E00EA0 {
    f32 u, v;
} Uv_b555_01E00EA0;

typedef struct Pk_b555_01E00EA0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b555_01E00EA0 uv;
    u64 pad18;
    Xyz_b555_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b555_01E00EA0;

typedef struct Buf_b555_01E00EA0 {
    u64 tag;
    Pk_b555_01E00EA0 pk;
} Buf_b555_01E00EA0;


typedef struct Data_b555_01E00EA0 {
    u8 pad0[0x10];
    s32 ang[4];
    u8 pad20[8];
    Vec4f f28;
    s16 f38;
} Data_b555_01E00EA0;

static void func_01E00EA0_b555(Obj_b555_01E00EA0 *obj, Data_b555_01E00EA0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b555_01E00EA0 buf;
    Uv_b555_01E00EA0 uv;
    s32 sel;
    s32 md;
    Pk_b555_01E00EA0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = mode >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->f28);
    p->uv = uv;
    func_01E00080_b555((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->f38, data->f38);
    func_00109100(view, data->ang, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        md = mode & 0xF;
        if (md == 0) {
            func_002075F0((s32)p, obj->f80, (u32)out[0]);
        } else if (md == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E01170_b555(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b555((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b500:01E01850, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b500_01E01850;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b500_01E01850;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b500_01E01850;

typedef struct {
    f32 u, v;
} Uv_b500_01E01850;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b500_01E01850 uv;
    u64 pad18;
    Xyz_b500_01E01850 v[4];
    u64 pad60[6];
} Pk_b500_01E01850;

typedef struct {
    u64 tag;
    Pk_b500_01E01850 pk;
} Buf_b500_01E01850;

static void func_01E016D0_b555(Obj_b500_01E01850 *obj, Def_b500_01E01850 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b500_01E01850 buf;
    Uv_b500_01E01850 uv;
    s16 sel;
    s16 i;
    Pk_b500_01E01850 *p;
    s32 mode;
    s8 *t;
    s32 h;
    f32 f;
    f32 r;
    f32 x;
    f32 y;
    f32 z;
    extern void func_00108EF0();
    extern void func_00109100();

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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b555((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        x = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        y = f * (def->scale + h);
        m2[0][0] += x;
        m2[1][0] += x;
        m2[2][0] += x;
        m2[3][0] += x;
        m2[0][1] += y;
        m2[1][1] += y;
        m2[2][1] += y;
        m2[3][1] += y;
        f = t[def->tab + 180];
        f /= 20.0f;
        z = f * (def->scale + h);
        m2[0][2] += z;
        m2[1][2] += z;
        m2[2][2] += z;
        m2[3][2] += z;
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b555:01E01BE0, 119 insns: scene timer step: start four effects on frame 1, then two bursts at an object
   between frames 51 and 199 and a double burst between frames 34 and 46 */

typedef struct Scn_b555_01E01BE0 {
    u8 pad0[0x250];
    Vec4f org;
    u8 pad260[0x32C0];
    u8 col[4];
    u8 pad3524[0x24];
    s16 id;
    u8 pad354A[0x18];
    s16 timer;
} Scn_b555_01E01BE0;

static void func_01E01BE0_b555(Scn_b555_01E01BE0 *w) {
    extern s32 func_001F53A0();
    extern void func_001F5620();
    extern u8 b555_01E01DC0[];
    extern u8 b555_01E01F90[];
    extern u8 b555_01E022B0[];
    extern u8 b555_01E02830[];
    extern u8 b555_01E029E0[];
    extern u8 b555_01E02BA0[];
    extern u8 b555_01E02CB0[];
    extern void b555_01E03D30(Scn_b555_01E01BE0 *w, void *data, s32 arg);
    s32 i;
    Vec4f v;

    w->col[0] = 0x80;
    w->col[1] = 0;
    w->col[2] = 0;
    w->col[3] = 0;
    w->timer++;
    if (w->timer == 1) {
        b555_01E03D30(w, b555_01E02BA0, 0);
    }
    if (w->timer == 1) {
        b555_01E03D30(w, b555_01E029E0, 0);
    }
    if (w->timer == 1) {
        b555_01E03D30(w, b555_01E02CB0, 0);
    }
    if (w->timer == 1) {
        b555_01E03D30(w, b555_01E01DC0, 0);
    }
    if (w->timer > 0x32 && w->timer < 0xC8) {
        func_001F5620(func_001F53A0(), w->id, &v);
        w->org.x = v.x;
        w->org.y = v.y;
        w->org.z = v.z;
        for (i = 0; i < 1; i++) {
            b555_01E03D30(w, b555_01E01F90, 0);
        }
        for (i = 0; i < 1; i++) {
            b555_01E03D30(w, b555_01E022B0, 0);
        }
    }
    if (w->timer >= 0x22 && w->timer < 0x2F) {
        func_001F5620(func_001F53A0(), w->id, &v);
        w->org.x = v.x;
        w->org.y = v.y;
        w->org.z = v.z;
        for (i = 0; i < 2; i++) {
            b555_01E03D30(w, b555_01E02830, 0);
        }
    }
}

/* shape b555:01E01DC0, 65 insns: a blinking white spark (frame 4, size 2): white on odd ticks, grey on even; in by 80 up to 0xA0 for 30 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b555_01E01DC0;

static s32 func_01E01DC0_b555(s32 arg0, Glow_b555_01E01DC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f38 = 2;
        o->kind = 4;
        o->mode = 2;
    }
    if (o->tick < 30) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
    }
    o->tick++;
    return 0;
}

/* shape b555:01E01ED0, 48 insns: a white one-tick flash at a random frame 0..6 that steps to 6 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
} Glow_b555_01E01ED0;

static s32 func_01E01ED0_b555(s32 arg0, Glow_b555_01E01ED0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        o->f38 = 3;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 1) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else {
        o->mode = 0;
    }
    if (o->kind < 6) {
        o->kind++;
    }
    o->tick++;
    return 0;
}

/* shape b555:01E01F90, 198 insns: b566:01E015D0 cousin, b350:01E00C60 family dark (0x20/0x20/0x08) puff: size 16..25
   growing 2 to 100 (3 more per tick after tick 72), frame 3 cycling 0..5 every 8 ticks from tick 4, speed 5..9, h8 0..24,
   hold 40..74, hC 1..3, z nudged 4 by the scene side (0x3560); sinks toward the second point by 1/72 of the gap (1/100
   after tick 72) */

typedef struct {
    u8 pad0[0x3560];
    s16 side;
} Ctx_b555_01E01F90;

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b555_01E01F90;

static s32 func_01E01F90_b555(Ctx_b555_01E01F90 *g, Fx_b555_01E01F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];
    s32 t;

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 10 + 16;
        o->f34 = 3;
        func_001076F0(o->col, 0x20, 0x20, 8);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 35 + 40;
        o->hC = func_0019A5C8() % 3 + 1;
        if (g->side != 0) {
            o->z -= 4;
        } else {
            o->z += 4;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    *(f32 *)(u32)&v[2] -= v[6];
    t = o->tick;
    if (t != 0) {
        if ((s16)t < 72) {
            *(f32 *)(u32)&v[2] /= 72.0f;
            o->z = o->z + v[2];
        } else {
            *(f32 *)(u32)&v[2] /= 100.0f;
            o->z = o->z + v[2];
            o->f30 += o->speed * 6;
            o->f38 += 3;
        }
    }
    if (o->tick > 3) {
        if (o->tick % 8 == 1) {
            if (o->f34 < 5) {
                o->f34++;
            } else {
                o->f34 = 0;
            }
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->f38 < 100) {
        o->f38 += 2;
    }
    o->tick++;
    return 0;
}

/* shape b555:01E022B0 (B555_OBJ_MOVE_5_), 232 insns: a grey (0x50) puff on joint +0x3548, pushed 4 along z by the
   scene flag: on start size 13..27, kind 0..7, spin 2..6, hold 35..69; brightens by 0x10 below 0x80 while held and the
   scene count (+0x3562) is under 260, then fades by 7, by 9 past 260; grows 2 up to 60, and 2 every other tick up to
   90; climbs an 80th of the camera-to-scene gap; kind cycles 0..5 every 7th tick */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 spin;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 size;
    s16 f3A;
} Fx_b555_01E022B0;

typedef struct {
    u8 pad[0x3548];
    s16 j;
    u8 pad354A[0x16];
    s16 flag;
    s16 count;
} Game_b555_01E022B0;

static s32 func_01E022B0_b555(Game_b555_01E022B0 *g, Fx_b555_01E022B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);
    extern s16 func_001A22C0(f32);
    f32 a[4];
    f32 b[8];

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 15 + 13;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        o->hA = o->f30;
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 35 + 35;
        func_001F5620(func_001F53A0(), g->j, a);
        o->x = func_001A22C0(a[0]);
        o->y = func_001A22C0(a[1]);
        o->z = func_001A22C0(a[2]);
        if (g->flag != 0) {
            o->z -= 4;
        } else {
            o->z += 4;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (g->count < 260) {
            if (o->col[3] < 0x80) {
                o->col[3] += 0x10;
            }
        }
    } else if (g->count < 260) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->count > 260) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        if (o->size < 60) {
            o->size += 2;
        }
    }
    func_001F5F90(func_001F5380(), a);
    func_001F5F90(func_001F53A0(), b);
    if (o->tick != 0) {
        a[2] -= b[2];
        a[2] /= 80.0f;
        o->z = func_001A22C0(o->z + a[2]);
    }
    if (o->tick % 7 == 1) {
        if (o->kind < 5) {
            o->kind++;
        } else {
            o->kind = 0;
        }
    }
    o->f30 += o->spin;
    if (o->size < 90) {
        if (o->tick % 2 == 1) {
            o->size += 2;
        }
    }
    if (o->spin % 2 == 1) {
        o->f3A++;
    } else {
        o->f3A--;
    }
    o->tick++;
    return 0;
}

/* shape b555:01E02650, 117 insns: a dim yellow rising mote: frame 3..7 counting up, sub-frame 3..6, rising from 0 by 1..3 once
   started, width 0..24, hold 4..11, depth 3..6; nudged one unit sideways by the scene side and one up; alpha up by 0x30 to
   0x90 until the hold, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x3560];
    s16 side;
} Game_b555_01E02650;

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 hold;
    s16 w;
    u8 padA[2];
    s16 hC;
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b555_01E02650;

static s32 func_01E02650_b555(Game_b555_01E02650 *g, Obj_b555_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 5 + 3;
        o->sub = func_0019A5C8() % 4 + 3;
        func_001076F0(o->c0, 0x40, 0x40, 0x20);
        o->y = 0;
        o->step = func_0019A5C8() % 3 + 1;
        o->w = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 8 + 4;
        o->hC = func_0019A5C8() % 4 + 3;
        if (g->side != 0) {
            o->h4++;
        } else {
            o->h4--;
        }
        o->h2++;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] <= 0x60) {
            o->c0[3] += 0x30;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->h38++;
    o->t++;
    return 0;
}

/* shape b555:01E02830, 108 insns: a dark grey spark (size 3 growing to 20, frame stepping every other tick to 5) spinning a random 2..6 a tick, size 0..34, 3..5 at +0xC, held 3..7 ticks: in by 18 up to 0x80, then out by 9 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b555_01E02830;

static s32 func_01E02830_b555(s32 arg0, Glow_b555_01E02830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 3;
        o->kind = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->h30 = 0;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 3;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->f38 < 20) {
            o->f38++;
        }
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b555:01E029E0, 111 insns: b582:01E03470 family scene light (ctx+0x34E0, height 140) riding 4 under the scene joint, flickering red 240/160/160 and grey 128 on odd/even ticks: raised by 0.2 to 1 for 200 ticks, then lowered by 0.1 and ended; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b555_01E029E0;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x10];
    s32 state;
} Light_b555_01E029E0;

typedef struct {
    u8 pad[0x34E0];
    Light_b555_01E029E0 l;
    u8 pad3520[0x354A - 0x3520];
    s16 joint;
} Game_b555_01E029E0;

static s32 func_01E029E0_b555(Game_b555_01E029E0 *g, Obj_b555_01E029E0 *o) {
    extern void func_001F6C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    Vec4f v;

    func_001F5620(func_001F53A0(), g->joint, &v);
    if (o->mode == 1) {
        g->l.w0 = 0.0f;
        g->l.r = 16.0f;
        g->l.g = 16.0f;
        g->l.b = 16.0f;
        g->l.w20 = 0;
        g->l.h = 140.0f;
        g->l.level = 0.0f;
        o->mode = 2;
    }
    g->l.x = v.x;
    g->l.y = v.y - 4.0f;
    g->l.z = v.z;
    if (o->tick < 200) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        }
    } else if (g->l.level > 0.1f) {
        g->l.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        g->l.r = 240.0f;
        g->l.g = 160.0f;
        g->l.b = 160.0f;
    } else {
        g->l.r = 128.0f;
        g->l.g = 128.0f;
        g->l.b = 128.0f;
    }
    o->tick++;
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b555:01E02BA0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x351C limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x351C];
    s32 state;
} Game_b555_01E02BA0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b555_01E02BA0;

static s32 func_01E02BA0_b555(Game_b555_01E02BA0 *g, Fade_b555_01E02BA0 *o) {
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
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

static s32 func_01E02C60_b555(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04000_b555;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04008_b555;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b555:01E02CB0, 129 insns: b205:01E02120 family full-screen white sprite in the scene's packet (ctx+0x3514), zoomed by f8: alpha up by 10 to 0x80 for 29 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b555_01E02CB0;

typedef struct {
    f32 s, t;
    Xyz_b555_01E02CB0 p;
} Tv_b555_01E02CB0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b555_01E02CB0 v[2];
} Tex_b555_01E02CB0;

typedef struct {
    u8 pad[0x3514];
    Tex_b555_01E02CB0 *pk;
} Game_b555_01E02CB0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b555_01E02CB0;

static s32 func_01E02CB0_b555(Game_b555_01E02CB0 *g, Fx_b555_01E02CB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
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
    g->pk->v[0].s = f / 1024.0f;
    g->pk->v[0].t = f / 512.0f;
    g->pk->v[1].s = (640.0f - f) / 1024.0f;
    g->pk->v[1].t = (448.0f - f) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 29) {
        if (o->col[3] < 0x80) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b555", func_01E02EC0_b555);

/* shape b555:01E03D30, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x355C and the two arguments; returns 1 if a
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
} Slot_b555_01E03D30;

typedef struct {
    u8 pad[0x250];
    u8 m[0x70];
    Slot_b555_01E03D30 s[200];
    u8 pad34C0[0x60];
    u8 r, g, b, a;
    u8 pad3524[0x38];
    s16 v;
} Pool_b555_01E03D30;

static s32 func_01E03D30_b555(Pool_b555_01E03D30 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b555_01E03D30 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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

/* OVL_WARM */

/* shape b555:01E03E50, 79 insns: the module's draw pass (b116:01E06870 shape): opens a sprite packet on the stack, then runs every
   live slot (200 of 0x40 bytes) whose handler is shape b555:01E02CB0 through it; queues the batch at the scene depth - 2000
   if any slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b555_01E03E50;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b555_01E03E50 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b555_01E03E50;

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 active;
    u8 pad38[8];
} Slot_b555_01E03E50;

typedef struct {
    u8 pad0[0x2C0];
    Slot_b555_01E03E50 slot[200];
    u8 padEnd[0x3510 - 0x2C0 - 200 * 0x40];
    s32 ctx;
    Pkt_b555_01E03E50 *pkt;
    f32 depth;
} Scene_b555_01E03E50;

static void func_01E03E50_b555(Scene_b555_01E03E50 *s) {
    extern void b555_01E02CB0(Scene_b555_01E03E50 *, Slot_b555_01E03E50 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b555_01E03E50 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 200; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b555_01E02CB0) {
                b555_01E02CB0(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), (u32)(s->depth - 2000.0f));
    }
}
