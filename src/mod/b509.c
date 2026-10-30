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

static void func_01E00080_b509(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
} Obj_b108_01E009A0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0x0A];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b108_01E009A0;

static void func_01E00920_b509(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

static void func_01E00D70_b509(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b509_01E00080();
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
    b509_01E00080(p, obj->f94, obj->fC0);
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

static void func_01E012C0_b509(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b509((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b509((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E01870_b509(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
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
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
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

/* shape b509:01E01BD0, 176 insns: the b509 module's event step (b232:01E00480's kind): counts ticks; until 154 follows
   the tracked point (ctx+0x44E4) with its marker (ctx+0x4470), at 155 aims it at the other point over 32 ticks and
   moves it until 185; spawns b509:01E02E40 at tick 1; at 186 the effect position takes the marker; from 52 to 141
   spawns b509:01E02A60 on the first point and from 141 to 250 b509:01E027C0 on the other, turning 3 each tick; from 165
   to 262 every 4th tick spawns b509:01E02D60 and b509:01E02BB0 within 10 of the other point */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Vec4f m;
    u8 pad4480[4];
    f32 dy;
    f32 dz;
    u8 pad448C[0x44E4 - 0x448C];
    s16 id0;
    u8 pad44E6[0x44F4 - 0x44E6];
    s16 id1;
    u8 pad44F6[0x450E - 0x44F6];
    s16 turn;
    u8 pad4510[4];
    s16 slot;
    u8 pad4516[6];
    s16 timer;
} Ctx_b509_01E01BD0;

static void func_01E01BD0_b509(Ctx_b509_01E01BD0 *g) {
    extern s32 b509_01E027C0(void);
    extern s32 b509_01E02A60(void);
    extern s32 b509_01E02BB0(void);
    extern s32 b509_01E02D60(void);
    extern s32 b509_01E02E40(void);
    extern void b509_01E03650(Ctx_b509_01E01BD0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[8];

    g->timer++;
    if (g->timer < 155) {
        func_001F5620(func_001F53A0(), g->id0, &g->m);
    } else {
        if (g->timer == 155) {
            func_001F5620(func_001F5380(), g->id1, v);
            g->dz = (v[2] - g->m.z) / 32.0f;
            g->dy = (v[1] - g->m.y) / 32.0f;
        }
        if (g->timer < 186) {
            g->m.z += g->dz;
            g->m.y += g->dy;
        }
    }
    if (g->timer == 1) {
        b509_01E03650(g, b509_01E02E40, 0);
    }
    if (g->timer == 186) {
        g->pos = g->m;
        g->slot = 0;
    }
    if (g->timer >= 52 && g->timer < 142) {
        func_001F5620(func_001F53A0(), g->id0, &g->pos);
        b509_01E03650(g, b509_01E02A60, 0);
        g->turn += 3;
    }
    if (g->timer >= 141 && g->timer < 251) {
        func_001F5620(func_001F5380(), g->id1, &g->pos);
        b509_01E03650(g, b509_01E027C0, 0);
        g->turn += 3;
    }
    if (g->timer >= 165 && g->timer < 263) {
        if (g->timer % 4 == 1) {
            func_001F5620(func_001F5380(), g->id1, &g->pos);
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            b509_01E03650(g, b509_01E02D60, 0);
            b509_01E03650(g, b509_01E02BB0, 0);
        }
    }
}

/* shape b509:01E01E90, 273 insns: b111:01E01D30 with this module's table and side; b149:01E01770 cousin: size 10, grey 0x80, random frame 0..6, turn, spin and hA 0..7,
   height from 0 growing by 15 up to its limit 100..449 while it fades in by 0x20 for 147 ticks, then fades by 8 and
   ends; at tick 135 it hands its position to the scene and fires the module's b509:01E022E0 effect three times and b509:01E02910 once, then
   b509:01E02670 six times in ten at a point jittered -15..14; its swing f34 is 3 x the table sine of h5C; from tick 96
   to 130 it is pushed 5 a tick in z by the scene side (0x4518) and sinks 1 while above the target's height - 10; from
   tick 141 it turns 5, rises by hE and 1 and grows 1; h5C turns by 6 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad260[0x4518 - 0x260];
    s16 side;
    u8 pad451A[0x4720 - 0x451A];
    u8 table[1];
} Mgr_b509_01E01E90;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0x10];
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
} Obj_b509_01E01E90;

static s32 func_01E01E90_b509(Mgr_b509_01E01E90 *m, Obj_b509_01E01E90 *o) {
    extern void b509_01E022E0();
    extern void b509_01E02670();
    extern void b509_01E02910();
    extern void b509_01E03650(Mgr_b509_01E01E90 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    f32 v[4];

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 147) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
        if (o->h52 > o->h50) {
            o->h50 += 15;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 == 135) {
        m->pos = o->pos;
        b509_01E03650(m, b509_01E022E0, 0);
        b509_01E03650(m, b509_01E022E0, 0);
        b509_01E03650(m, b509_01E022E0, 0);
        b509_01E03650(m, b509_01E02910, 0);
        m->pos.x += func_0019A5C8() % 30 - 15;
        m->pos.y += func_0019A5C8() % 30 - 15;
        m->pos.z += func_0019A5C8() % 30 - 15;
        if (func_0019A5C8() % 10 < 6) {
            b509_01E03650(m, b509_01E02670, 0);
        }
    }
    func_001F5F90(func_001F5380(), v);
    o->f34 = 3.0f * func_00108030(m->table, o->h5C, 1);
    if (o->h54 > 95 && o->h54 < 131) {
        if (m->side != 0) {
            o->pos.z -= 5.0f;
        } else {
            o->pos.z += 5.0f;
        }
        if (v[1] - 10.0f < o->pos.y) {
            o->pos.y -= 1.0f;
        }
    }
    if (o->h54 > 140) {
        o->h5A += 5;
        o->h50 += o->hE;
        o->pos.y += 1.0f;
        o->f48 += 1.0f;
    }
    o->h5C += 6;
    o->h54++;
    return 0;
}

/* shape b111:01E02160, 100 insns, 7 copies: spark update, a variant of b018:01E02950 (on spawn: random kind, white
   colour, angle, spin, height, speed, size and lifetime; then fade out after the lifetime, move while
   alive). b193:01E02780 is the same code with 40.0f for the first field. */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 pos;
    u8 pad52[2];
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Spark_b111_01E02160;

static s32 func_01E022E0_b509(s32 unused, Spark_b111_01E02160 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 10.0f;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->angle = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->pos;
        o->pos = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->limit = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 9) {
        o->alpha -= 8;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->pos += o->speed;
    }
    o->age++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[0x10];
    s32 seed[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 pos;
    s16 frame;
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Mote_b111_01E022F0;

static s32 func_01E02470_b509(s32 unused, Mote_b111_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 5 + 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->seed[0] = func_0019A5C8() % 0xFFFF;
        o->seed[1] = func_0019A5C8() % 0xFFFF;
        o->seed[2] = func_0019A5C8() % 0xFFFF;
        o->frame = 1;
        o->pos = func_0019A5C8() % 30 + 10;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->limit = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x60;
    } else if (o->alpha > 12) {
        o->alpha -= 11;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b189:01E02700, 84 insns, 3 copies: step of a blinking flash (variant of shape b547:01E02400): size 100, second
   colour blinks red every other tick; fades in by 0x40 until tick 186, then out by 14; spins a quarter turn. */

typedef struct {
    u8 pad00[0x20];
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
} Obj_b189_01E02700;

static s32 func_01E02670_b509(void *arg0, Obj_b189_01E02700 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 100.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 8, 8);
    } else {
        func_001076F0(o->c1, 0xC0, 8, 8);
    }
    if (o->t < 186) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b509:01E027C0, 84 insns: a grey beam falling from 900 by a random 25..59.9 a tick (tail 65 behind), spun 0x4000: alpha 0x80 for 2 ticks, ends once under 120 */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
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
} Obj_b509_01E027C0;

static s32 func_01E027C0_b509(s32 arg0, Obj_b509_01E027C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 900.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->h50 = 1;
        o->h5A = 5;
        o->h5C = 5;
        o->f34 = func_0019A5C8() % 350 + 250;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        o->col[3] = 0x80;
    } else if (o->f48 < 120.0f) {
        o->mode = 0;
    }
    o->f48 -= o->f34;
    o->f4C = o->f48 - 65.0f;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b402:01E02710, 84 insns, 2 copies: a red flare: set up once (size 500, random angle); fades in over 4 frames, then
   out; its second colour flickers between two reds each frame while turning (b016:01E01FF0 family) */

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0x24];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b402_01E02710;

static s32 func_01E02910_b509(void *arg0, Obj_b402_01E02710 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 500.0f;
        func_001076F0(o->c0, 0xFF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 8, 8);
    } else {
        func_001076F0(o->c1, 0xC0, 8, 8);
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b509:01E02A60, 82 insns: on start f48 20, f4C 58 below it, both colours 0x40 grey (second alpha 0),
   0x5A/0x5C = 5, rise speed 10..34.9 (f34); alpha 0x80 for 2 ticks, then fades by 14 and stops; f48 rises by the
   speed with f4C 30 below it; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[4];
    f32 speed;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b509_01E02A60;

static s32 func_01E02A60_b509(s32 arg0, Fx_b509_01E02A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->f50 = 0;
        o->f5A = 5;
        o->f5C = 5;
        o->speed = func_0019A5C8() % 250 + 100;
        o->speed /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->speed;
    o->f4C = o->f48 - 30.0f;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b402:01E029C0, 107 insns, 2 copies: a white spark: set up once (random size 8..17, frame, angle, speed 15..39, life
   4..7); fades in for its life, then out; turns by its speed (b225:01E026A0 family, 0x58-state layout) */

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
} Spark_b402_01E029C0;

static s32 func_01E02BB0_b509(void *arg0, Spark_b402_01E029C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 8;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->ang = func_0019A5C8() % 30 + 5;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 25 + 15;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 4 + 4;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x11) {
        o->c0[3] -= 0x10;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    o->t++;
    return 0;
}

/* shape b402:01E02B70, 54 insns: a spinning flash: on start size 110, white and (0x80,0xFF,0x80) colours, f5A/f5C
   15, second alpha 0; alpha 0x80 for 3 ticks, then fades out by 11 and stops; the rotation turns by 0x4000 each
   tick */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Flash_b402_01E02B70;

static s32 func_01E02D60_b509(s32 arg0, Flash_b402_01E02B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 110.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0xFF, 0x80);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b402:01E02C50, 31 insns: calls func_001F7170(3, 0, &a, &b, 0) with the module's two floats, stops the
   effect after 0x91 ticks */

typedef struct {
    u8 pad0[0x54];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b402_01E02C50;

typedef struct {
    f32 v;
} F1_b402_01E02C50;

extern F1_b402_01E02C50 D_01E03C80_b509;
extern F1_b402_01E02C50 D_01E03C88_b509;

static s32 func_01E02E40_b509(s32 arg0, Fx_b402_01E02C50 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F1_b402_01E02C50 a;
    F1_b402_01E02C50 b;

    a = D_01E03C80_b509;
    b = D_01E03C88_b509;
    func_001F7170(3, 0, &a, &b, 0);
    o->tick++;
    if (o->tick >= 0x91) {
        o->mode = 0;
    }
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02EC0_b509(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b509", func_01E02ED0_b509);

/* shape b402:01E034C0, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b402_01E034C0 {
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
} Slot_b402_01E034C0;

typedef struct Obj_b402_01E034C0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b402_01E034C0 slots[0x96];
    u8 padB[0x44b4 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0x4514 - 0x44b4 - 4];
    s16 fB2B0;
} Obj_b402_01E034C0;

static s32 func_01E03650_b509(Obj_b402_01E034C0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b402_01E034C0 *s = NULL;
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

/* shape b509:01E03790 (B509PAINT_RAIN20), 305 insns, 1 copy: b402:01E03600's wobbling band drawer with a fixed 0.1
   scale */

typedef struct Cam_b509_01E03790 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    s16 kind;
    u8 pad52[8];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b509_01E03790;

typedef struct Obj_b509_01E03790 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x450C - 0xC0];
    s16 wob;
    s16 ang0;
    u8 pad4510[0x4720 - 0x4510];
    u8 table[0x10];
} Obj_b509_01E03790;

typedef struct Uv_b509_01E03790 {
    f32 u, v;
} Uv_b509_01E03790;

typedef struct Vtx_b509_01E03790 {
    Uv_b509_01E03790 st;
    u64 rgba;
    u64 xyz;
} Vtx_b509_01E03790;

typedef struct Pk_b509_01E03790 {
    u8 hdr[0x10];
    Vtx_b509_01E03790 v[4];
    u8 pad70[0x20];
} Pk_b509_01E03790;

static void func_01E03790_b509(Obj_b509_01E03790 *o, Cam_b509_01E03790 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    f32 h;
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    Pk_b509_01E03790 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b509_01E03790 pk;
    Uv_b509_01E03790 uv0;
    Uv_b509_01E03790 uv1;
    Uv_b509_01E03790 uv2;
    Uv_b509_01E03790 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    func_00108500(p, o->rect, 0);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    pk.v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    pk.v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    pk.v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    pk.v[3].st = uv3;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    o->wob = 0;
    ang = o->ang0;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        if (cam->kind == 0) {
            h = 12.0f * func_00108030(o->table, o->wob, 0);
        } else if (cam->kind == 1) {
            h = 20.0f * func_00108030(o->table, o->wob, 0);
        }
        if (cam->kind == 0) {
            o->wob += 20;
        } else if (cam->kind == 1) {
            o->wob += 40;
        }
        pts[0].x = h + w0 * func_00108030(o->table, idx, 1);
        pts[0].z = h + w0 * func_00108030(o->table, idx, 0);
        pts[2].x = h + w1 * func_00108030(o->table, idx, 1);
        pts[2].z = h + w1 * func_00108030(o->table, idx, 0);
        if (cam->kind == 0) {
            h = 12.0f * func_00108030(o->table, o->wob, 0);
        } else if (cam->kind == 1) {
            h = 20.0f * func_00108030(o->table, o->wob, 0);
        }
        idx = k + (cam->step + (s16)n);
        pts[1].x = h + w0 * func_00108030(o->table, idx, 1);
        pts[1].z = h + w0 * func_00108030(o->table, idx, 0);
        pts[3].x = h + w1 * func_00108030(o->table, idx, 1);
        pts[3].z = h + w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}
