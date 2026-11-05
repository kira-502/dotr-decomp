#include "common.h"

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

static void func_01E00080_c062(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

/* shape c062:01E004D0, 152 insns: draws the five arms of a star: mode 0 only clears the packet; otherwise the centre is the
   average of the ten star points (two per entry, 0x70-byte entries at +0x5A50), and for each of the five point pairs
   of the module table (0x1E05900) a quad from the two pair points to the centre is sent in the effect's colour */

typedef struct {
    s32 v[5][2];
} Pairs_c062_01E004D0;

typedef struct {
    Vec4f a;
    Vec4f b;
    u8 pad20[0x50];
} Pt_c062_01E004D0;

typedef struct {
    u8 pad0[0x5A50];
    Pt_c062_01E004D0 pt[5];
    u8 pad5C80[0xBCC];
    s32 tex;
} Scene_c062_01E004D0;

extern Pairs_c062_01E004D0 D_01E05900_c062 __attribute__((aligned(16)));

static void func_01E004D0_c062(Scene_c062_01E004D0 *g, u8 *fx, void *pk, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00107990(void *, void *, s32);
    extern void func_00108F90(void *, void *, s32, s32);
    Vec4f q[4];
    Pairs_c062_01E004D0 pr __attribute__((aligned(16)));
    f32 cx;
    f32 cy;
    f32 cz;
    s32 i;
    s32 j;

    pr = D_01E05900_c062;
    if (mode == 0) {
        func_001092E0(pk, 0);
        return;
    }
    cx = (g->pt[0].a.x + g->pt[1].a.x + g->pt[2].a.x + g->pt[3].a.x + g->pt[4].a.x + g->pt[0].b.x + g->pt[1].b.x +
          g->pt[2].b.x + g->pt[3].b.x + g->pt[4].b.x) / 5.0f;
    cy = (g->pt[0].a.y + g->pt[1].a.y + g->pt[2].a.y + g->pt[3].a.y + g->pt[4].a.y + g->pt[0].b.y + g->pt[1].b.y +
          g->pt[2].b.y + g->pt[3].b.y + g->pt[4].b.y) / 5.0f;
    cz = (g->pt[0].a.z + g->pt[1].a.z + g->pt[2].a.z + g->pt[3].a.z + g->pt[4].a.z + g->pt[0].b.z + g->pt[1].b.z +
          g->pt[2].b.z + g->pt[3].b.z + g->pt[4].b.z) / 5.0f;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 2; j++) {
            func_00106DD0(&q[j], g->pt[pr.v[i][j]].a.x + g->pt[pr.v[i][j]].b.x,
                          g->pt[pr.v[i][j]].a.y + g->pt[pr.v[i][j]].b.y,
                          g->pt[pr.v[i][j]].a.z + g->pt[pr.v[i][j]].b.z);
        }
        q[2].x = q[3].x = cx;
        q[2].y = q[3].y = cy;
        q[2].z = q[3].z = cz;
        func_00107990(pk, fx + 0x60, 0);
        func_00108F90(q, pk, 0, g->tex);
    }
}

/* shape c062:01E00730, 446 insns, 1 copy (-O3,p): five-arm star ribbons: mode 0 clears the packet; for each of the
   scene count entries of the module order table (0x1E05948) a quad between the midpoints of its two pair points
   (table 0x1E05930, 0x70-byte points at +0x5A50), pushed 5 along z by the side flag, drawn twice per arm (uv flipped,
   offset by f48, or 1.75 f48 for arms 3/4) into the scene list */

typedef struct {
    s16 v[5][2];
} Pairs_c062_01E00730;

typedef struct {
    s16 v[5];
} Order_c062_01E00730;

typedef struct {
    Vec4f v;
} __attribute__((aligned(16))) Pos_c062_01E00730;

typedef struct {
    f32 s, t;
} Uv_c062_01E00730;

typedef struct {
    Uv_c062_01E00730 uv;
    u8 pad8[8];
} Vtx_c062_01E00730;

typedef struct {
    u8 hdr[0x10];
    Vtx_c062_01E00730 v[4];
} Pk_c062_01E00730;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[0x14];
    u8 c60[4];
    u8 c64[4];
} Obj_c062_01E00730;

typedef struct {
    Vec4f a;
    Vec4f b;
    u8 pad20[0x50];
} Pt_c062_01E00730;

typedef struct {
    u8 pad0[0x5A50];
    Pt_c062_01E00730 pt[5];
    u8 pad5C80[0x684C - 0x5C80];
    s32 ot;
    u8 pad6850[0x686C - 0x6850];
    f32 depth;
    u8 pad6870[0x6900 - 0x6870];
    s32 n;
    u8 pad6904[0x693A - 0x6904];
    s16 side;
} Scene_c062_01E00730;

extern Pairs_c062_01E00730 D_01E05930_c062 __attribute__((aligned(16)));
extern Order_c062_01E00730 D_01E05948_c062 __attribute__((aligned(8)));

static inline void uv4_c062_01E00730(Pk_c062_01E00730 *pk, u8 *a, u8 *b) {
    extern Uv_c062_01E00730 func_00107740(void *);

    pk->v[0].uv = func_00107740(a);
    pk->v[1].uv = func_00107740(b);
    pk->v[2].uv = func_00107740(a);
    pk->v[3].uv = func_00107740(b);
}

#pragma optimization_level 3

static void func_01E00730_c062(Scene_c062_01E00730 *g, Obj_c062_01E00730 *o, Pk_c062_01E00730 *pk, s32 mode) {
    extern void func_001092E0(void *, s32);
    extern Pos_c062_01E00730 func_00106DD0(f32, f32, f32);
    extern Uv_c062_01E00730 func_00107740(void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Pos_c062_01E00730 c;
    Pairs_c062_01E00730 pr __attribute__((aligned(16)));
    Order_c062_01E00730 ord __attribute__((aligned(8)));
    Pt_c062_01E00730 *p;
    f32 w;
    f32 w2;
    s16 i;
    s16 k;
    s16 j;
    s16 s;

    w = o->f48;
    pr = D_01E05930_c062;
    ord = D_01E05948_c062;
    if (mode == 0) {
        func_001092E0(pk, 0);
        return;
    }
    w2 = 1.75f * w;
    for (i = 0; i < g->n; i++) {
        p = &g->pt[pr.v[ord.v[i]][0]];
        c = func_00106DD0(p->a.x + p->b.x, p->a.y + p->b.y, p->a.z + p->b.z);
        q[0] = c.v;
        q[1] = c.v;
        p = &g->pt[pr.v[ord.v[i]][1]];
        c = func_00106DD0(p->a.x + p->b.x, p->a.y + p->b.y, p->a.z + p->b.z);
        q[2] = c.v;
        q[3] = c.v;
        func_00107070(q, 2, g->side ? -5.0f : 5.0f);
        s = ord.v[i];
        for (k = 0; k < 2; k++) {
            if (s == 0 || s == 1) {
                if (k == 0) {
                    uv4_c062_01E00730(pk, o->c60, o->c64);
                    q[1].x -= w;
                    q[3].x -= w;
                } else {
                    uv4_c062_01E00730(pk, o->c64, o->c60);
                    func_00107070(q, 0, w);
                }
            }
            if (s == 2) {
                if (k == 0) {
                    uv4_c062_01E00730(pk, o->c60, o->c64);
                    q[1].y -= w;
                    q[3].y -= w;
                } else {
                    uv4_c062_01E00730(pk, o->c64, o->c60);
                    func_00107070(q, 1, w);
                }
            }
            if (s == 3 || s == 4) {
                if (k == 0) {
                    uv4_c062_01E00730(pk, o->c60, o->c64);
                    q[1].x -= w2;
                    q[3].x -= w2;
                } else {
                    uv4_c062_01E00730(pk, o->c64, o->c60);
                    func_00107070(q, 0, w2);
                }
            }
            if (func_00205630(q, 0x70000000, NULL, pk, &g->depth)) {
                for (j = 0; j < 4; j++) {
                    func_002075F0(pk, g->ot, func_001A23B0(g->depth));
                }
            }
        }
    }
}
#pragma optimization_level reset

/* shape c062:01E00E30, 134 insns: a two-pass 12.8 x 18.4 sprite grid: mode 0 sets the material (rect 256,0 256x384, the
   object's two colours, scene texture 0x685C); other modes draw it at each of the scene's points (5 rows of 6 at
   g+0x65D0; 3 per row, 5 once the scene step at g+0x68FC reaches 12), facing +201 or -201 by the flag at g+0x693A */

typedef struct {
    f32 x, y, z, w;
} Vec_c062_01E00E30;

typedef struct {
    s16 x, y, w, h;
} Rect_c062_01E00E30;

typedef struct {
    u8 pad0[0x60];
    u8 c60[4];
    u8 c64[4];
} Obj_c062_01E00E30;

typedef struct {
    u8 pad0[0x65D0];
    Vec_c062_01E00E30 pts[5][6];
    u8 pad67B0[0x9C];
    s32 target;
    u8 pad6850[0xC];
    s32 texture;
    u8 pad6860[0x9C];
    s32 step;
    u8 pad6900[0x3A];
    s16 flip;
} Game_c062_01E00E30;

static void func_01E00E30_c062(Game_c062_01E00E30 *g, Obj_c062_01E00E30 *o, u8 *p, s32 mode) {
    f32 w;
    f32 h;
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00205440(void *, s32, void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 q[16];
    Rect_c062_01E00E30 r[2];
    Vec_c062_01E00E30 t[4];
    Vec_c062_01E00E30 v;
    f32 m[64];
    f32 m2[16];
    f32 depth[7];
    f32 tmp;
    s16 n;
    s32 i;
    s32 j;

    n = 3;
    if (mode == 0) {
        r[0].x = 0x100;
        r[0].y = 0;
        r[0].w = 0x100;
        r[0].h = 0x180;
        func_00109270(p, 0, 0);
        func_00107790(p, o->c60, 1);
        func_00107790(p, o->c64, 2);
        func_00108500(p, r, 3);
        func_00208700(p, g->texture, 1);
    } else {
        if (g->step >= 12) {
            n = 5;
        }
        w = 12.8f;
        h = 18.4f;
        func_00108CE0(q, w, h);
        v.x = 0.0f;
        v.y = 0.0f;
        if (g->flip == 0) {
            v.z = 201.0f;
        } else {
            v.z = -201.0f;
        }
        func_00205440(&v, 0, p + 0x20, &tmp);
        for (j = 0; j < 5; j++) {
            for (i = 0; i < n; i++) {
                t[0] = g->pts[j][i];
                func_0020EB40(m);
                func_0020C940(m2, 0, 0, t);
                func_0020BC00(m, m2);
                if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                    func_002075F0(p, g->target, (u32)depth[0]);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E01050_c062);

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

static void func_01E01870_c062(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

/* shape b707:01E00C70, 362 insns, 2 copies (b445:01E00D10 twin, kind 0 also turned): draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b707_01E00C70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b707_01E00C70 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b707_01E00C70;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b707_01E00C70;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f pos;
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 w50;
    u8 pad52[8];
    s16 axis;
    u8 pad5C[4];
    u8 col[4];
} Spr_b707_01E00C70;

static void func_01E01BD0_c062(Obj_b707_01E00C70 *o, Spr_b707_01E00C70 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b707_01E00C70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f e;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b707_01E00C70 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b707_01E00C70 *p;
    u8 mode;

    p = (Pkt_b707_01E00C70 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00080_c062((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    p2.x = s->pos.x;
    p2.y = s->pos.y;
    p2.z = s->pos.z;
    if (o->kind == 0) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00080_c062((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
            func_00108CE0(quad, s->size, s->size);
            func_00109100(quad, rot, 1, o->xD8);
            func_00109100(quad, rot, 0, o->xD8);
        } else if (o->kind == 1) {
            func_00108CE0(quad, s->size, s->size);
        }
        for (c = 0; c < 3; c++) {
            if (c == 0) {
                off = 0;
            }
            if (c == 1) {
                off = 100;
            }
            if (c == 2) {
                off = 180;
            }
            f = (tbl + i)[s->off + off];
            f /= 20.0f;
            u = f * (f32)(s->w50 + (i >> 1));
            if (c == 0) {
                e.x = u;
            }
            if (c == 1) {
                e.y = u;
            }
            if (c == 2) {
                e.z = u;
            }
        }
        if (o->kind == 0) {
            func_00108950(&e, ax, 0, o->xD8);
        }
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (o->kind == 1) {
            quad[0].y = 0.0f;
            quad[1].y = 0.0f;
            quad[0].x = s->size;
            quad[1].x = -s->size;
            quad[0].z = 0.0f;
            quad[1].z = 0.0f;
        }
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

static void func_01E02180_c062(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape c062:01E024F0, 88 insns: a fading tinted glow: alpha up by 8 to 0x80 for 15 frames (orange on the first), then down by
   5 from frame 50 until it ends; its colour steps through phases (green down to 2, then red down to 2 with blue set to 0xFF,
   then blue down by 2 to 3); ends when the scene timer reaches 270 */

typedef struct {
    u8 pad0[0x693C];
    s16 timer;
} Scene_c062_01E024F0;

typedef struct {
    u8 pad0[0x50];
    s16 phase;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_c062_01E024F0;

static s32 func_01E024F0_c062(Scene_c062_01E024F0 *g, Obj_c062_01E024F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->t < 0xF) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->t == 0) {
            func_001076F0(o->c0, 0x80, 0x60, 0);
        }
    } else if (o->t >= 0x32) {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 5;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (o->phase == 0) {
        if (o->c0[1] > 2) {
            o->c0[1]--;
        } else {
            o->phase = 1;
        }
    } else if (o->phase == 1) {
        o->c0[2] = 0;
        if (o->c0[0] > 2) {
            o->c0[0]--;
        } else {
            o->phase = 2;
            o->c0[2] = 0xFF;
        }
    } else if (o->phase == 2) {
        if (o->c0[2] > 3) {
            o->c0[2] -= 2;
        }
    }
    if (g->timer >= 0x10E) {
        o->state = 0;
    }
    return 0;
}

/* shape c062:01E02650, 73 insns: a grey smoke ring growing 1 a tick up to 7 that flickers (alpha 0xAF / 0x8F) while the scene value is under 270, then out by 9 (second colour by 2) and ends; bumps the scene counter up to 5 */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    u8 pad28[0xC];
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
} Obj_c062_01E02650;

typedef struct {
    u8 pad[0x6900];
    s32 count;
    u8 pad6904[0x38];
    s16 val;
} Game_c062_01E02650;

static s32 func_01E02650_c062(Game_c062_01E02650 *g, Obj_c062_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->f48 < 7.0f) {
        o->f48 += 1.0f;
    }
    func_001076F0(o->col, 0x4F, 0x4F, 0x4F);
    func_001076F0(o->col2, 0x30, 0x30, 0x30);
    if (g->val < 270) {
        if (o->h50 == 0) {
            o->col[3] = 0xAF;
            o->col2[3] = 0x10;
            o->h50 = 1;
        } else {
            o->col[3] = 0x8F;
            o->col2[3] = 0x10;
            o->h50 = 0;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 3) {
            o->col2[3] -= 2;
        }
    }
    if (g->count < 5) {
        g->count++;
    }
    return 0;
}

/* shape c062:01E02780, 229 insns: five dark ribbons trailing the scene's five bodies (ctx+0x5A50, 0x70 apart): on start
   every 6-point trail (ctx+0x65D0, 0x60 apart) is filled with the first body's point (its two vectors summed, pushed
   by the radius ctx+0x68BC along its angle 0x24, 1 up or down by the scene side 0x693A); each tick the size grows by 1
   to 7, both alphas sit at 0x80, every trail shifts back one point and takes its own body's point; ends once the
   scene clock (0x693C) reaches 217 */

typedef struct {
    Vec4f p;
    Vec4f q;
    u8 pad20[4];
    s16 ang;
    u8 pad26[0x4A];
} Body_c062_01E02780;

typedef struct {
    u8 pad0[0x5A50];
    Body_c062_01E02780 body[5];
    u8 pad5C80[0x65D0 - 0x5C80];
    Vec4f tr[5][6];
    u8 pad67B0[0x68BC - 0x67B0];
    f32 rad;
    u8 pad68C0[0x693A - 0x68C0];
    s16 side;
    s16 clock;
    u8 pad693E[0x6B40 - 0x693E];
    u8 trig[1];
} Ctx_c062_01E02780;

typedef struct {
    u8 pad0[0x48];
    f32 size;
    u8 pad4C[0xC];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_c062_01E02780;

static s32 func_01E02780_c062(Ctx_c062_01E02780 *g, Fx_c062_01E02780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    Body_c062_01E02780 *b = g->body;
    s16 i;
    s16 k;
    s16 a;

    if (o->state == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        func_001076F0(o->col2, 0x20, 0x20, 0x20);
        for (i = 0; i < 5; i++) {
            a = b->ang;
            g->tr[i][0].x = b->p.x + b->q.x + g->rad * func_00108030(g->trig, a, 1);
            g->tr[i][0].y = b->p.y + b->q.y + g->rad * func_00108030(g->trig, a, 0);
            if (g->side == 0) {
                g->tr[i][0].z = 1.0f + (b->p.z + b->q.z);
            } else {
                g->tr[i][0].z = b->p.z + b->q.z - 1.0f;
            }
            g->tr[i][1] = g->tr[i][0];
            g->tr[i][2] = g->tr[i][0];
            g->tr[i][3] = g->tr[i][0];
            g->tr[i][4] = g->tr[i][0];
        }
        o->state = 2;
    }
    if (o->size < 7.0f) {
        o->size += 1.0f;
    }
    o->col[3] = 0x80;
    o->col2[3] = 0x80;
    for (i = 0; i < 5; i++) {
        b = &g->body[i];
        for (k = 5; k > 0; k--) {
            g->tr[i][k] = g->tr[i][k - 1];
        }
        a = b->ang;
        g->tr[i][0].x = b->p.x + b->q.x + g->rad * func_00108030(g->trig, a, 1);
        g->tr[i][0].y = b->p.y + b->q.y + g->rad * func_00108030(g->trig, a, 0);
        if (g->side == 0) {
            g->tr[i][0].z = 1.0f + (b->p.z + b->q.z);
        } else {
            g->tr[i][0].z = b->p.z + b->q.z - 1.0f;
        }
    }
    if (g->clock >= 217) {
        o->state = 0;
    }
    return 0;
}

/* shape c062:01E02B20, 198 insns: c063:01E04510's glow pair placed at (0, 70, ctx+0x6808) with size 500, in one of
   three presets (white 22 ticks, warm 15 or 25); fading in by 18 (by 7 for kind 2) to 0x80, then out by 4 (kind 0
   only once the scene count ctx+0x693C passes 320); after 270 it drifts 4 along z, back when ctx+0x693A is 1 */

typedef struct {
    u8 pad0[0x6808];
    f32 z;
    u8 pad680C[0x12E];
    s16 dir;
    s16 count;
} Scene_c062_01E02B20;

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[8];
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 age;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_c062_01E02B20;

static s32 func_01E02B20_c062(Scene_c062_01E02B20 *g, Glow_c062_01E02B20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->z = g->z;
        o->x = 0.0f;
        o->y = 70.0f;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0xF0, 0xF0, 0xF0);
            o->life = 22;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0xF0, 0xD0, 0xA0);
            func_001076F0(o->c1, 0xF0, 0xA0, 0xA0);
            o->life = 15;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0xF0, 0xD0, 0xA0);
            func_001076F0(o->c1, 0xF0, 0xA0, 0xA0);
            o->life = 25;
        }
        o->f48 = 500.0f;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->kind != 2) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 18;
            }
            if (o->c1[3] < 0x80) {
                o->c1[3] += 18;
            }
        }
        if (o->kind == 2) {
            if (o->c0[3] < 0x80) {
                o->c0[3] += 7;
            }
            if (o->c1[3] < 0x80) {
                o->c1[3] += 7;
            }
        }
    } else {
        if (o->kind == 1) {
            if (o->c0[3] > 5) {
                o->c0[3] -= 4;
            } else {
                o->state = 0;
            }
            if (o->c1[3] > 5) {
                o->c1[3] -= 4;
            } else {
                o->c1[3] = 0;
            }
        }
        if (o->kind == 2) {
            if (o->c0[3] > 5) {
                o->c0[3] -= 4;
            } else {
                o->state = 0;
            }
            if (o->c1[3] > 5) {
                o->c1[3] -= 4;
            } else {
                o->c1[3] = 0;
            }
        }
        if (o->kind == 0) {
            if (g->count > 320) {
                if (o->c0[3] > 5) {
                    o->c0[3] -= 4;
                } else {
                    o->state = 0;
                }
                if (o->c1[3] > 5) {
                    o->c1[3] -= 4;
                } else {
                    o->c1[3] = 0;
                }
            }
        }
    }
    if (g->count > 270) {
        if (g->dir == 0) {
            o->z += 4.0f;
        }
        if (g->dir == 1) {
            o->z -= 4.0f;
        }
    }
    o->age++;
    return 0;
}

/* shape c062:01E02E40, 137 insns: three-kind ring glow: kind 0 white over grey, held 12, size 600; kind 1 blue under grey,
   held 5, growing from 600 by 10; kind 2 grey under white, held 10, growing from 1800 by 10; the second alpha grows by
   0x50 (below 0xA0) while held, then fades by 12 (kind 1: by 7); turns 0x20 by 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    s32 w48;
    f32 size;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_c062_01E02E40;

static s32 func_01E02E40_c062(s32 arg0, Fx_c062_01E02E40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w48 = 0;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
            o->hold = 12;
        }
        if (o->kind == 1) {
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
            func_001076F0(o->col, 0x40, 0x40, 0x80);
            o->hold = 5;
            o->size = 600.0f;
        }
        if (o->kind == 2) {
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0x40, 0x40, 0x40);
            o->hold = 10;
            o->size = 1800.0f;
        }
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->kind != 1) {
        if (o->col2[3] > 0xD) {
            o->col2[3] -= 12;
        } else {
            o->mode = 0;
        }
    } else if (o->col2[3] > 8) {
        o->col2[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->size = 600.0f;
    }
    if (o->kind == 1) {
        o->size += 10.0f;
    }
    if (o->kind == 2) {
        o->size += 10.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape c062:01E03070, 103 insns: a red falling spark (b434:01E02210 shape): size 35, random sub-frame 0..3, height 3000..4999
   falling by 200..399 once started until under 31, angle, width 0..34, hold 3..5; alpha up by 0x40 to 0xC0 until the hold, then down by 14 */

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
} Obj_c062_01E03070;

static s32 func_01E03070_c062(void *arg0, Obj_c062_01E03070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 35.0f;
        o->sub = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->y = func_0019A5C8() % 2000 + 0xBB8;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 200 + 0xC8;
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
        if (o->y > 0x1E) {
            o->y -= o->step;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape c062:01E03210, 115 insns: far spark (depth 800, growing) with random radius, spin and life */

typedef struct Sp_c062_01E03210 {
    u8 pad0[6];
    s16 life;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 spin;
    u8 pad10[0x38];
    f32 depth;
    u8 pad4C[4];
    s16 rad;
    u8 pad52[2];
    s16 age;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Sp_c062_01E03210;

static s32 func_01E03210_c062(s32 arg0, Sp_c062_01E03210 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->depth = 800.0f;
        o->h56 = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->hA = o->rad;
        o->rad = func_0019A5C8() % 15 + 1;
        o->ang = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 80 + 80;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 10 + 8;
        o->hC = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->depth += 1.0f;
    }
    if (o->age != 0) {
        o->rad += o->spin;
    }
    o->age++;
    return 0;
}

/* shape c062:01E033E0, 92 insns: b732:01E03BC0 family shock wave (grey/red, scale 6, 200 wide): kind 0 from 2000 growing 140 a tick, kind 1 from 1200 growing 80; in by 64 up to 0x80 for 12 ticks, then out by 7 and ends; spins 6 a tick */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_c062_01E033E0;

static s32 func_01E033E0_c062(s32 arg0, Obj_c062_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0x10, 0x10);
        if (o->h50 == 0) {
            o->f30 = 200.0f;
            o->f34 = 2000.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 200.0f;
            o->f34 = 1200.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 140.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 80.0f;
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

/* shape c062:01E03550, 161 insns: b363:01E04D90 family sprite in its own colour (0xA0, 0x80, 0x80; 0x90/0x70/0x80 at scene count 241) zooming out by f48: alpha up by 10 to 0x50 before count 216, eased down by 6 to 0x40 after 216, until tick 280; then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c062_01E03550;

typedef struct {
    f32 s, t;
    Xyz_c062_01E03550 p;
} Tv_c062_01E03550;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_c062_01E03550 v[2];
    u8 tail[0x20];
} Tex_c062_01E03550;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_c062_01E03550;

typedef struct {
    u8 pad0[0x693C];
    s16 count;
} Ctx_c062_01E03550;

static s32 func_01E03550_c062(Ctx_c062_01E03550 *g, Fx_c062_01E03550 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_c062_01E03550 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0xA0, 0x80, 0x80);
        o->mode = 2;
    }
    z = 0.0f;
    ((Tex_c062_01E03550 *)(s32)&pk)->flags = 0x26;
    ((Tex_c062_01E03550 *)(s32)&pk)->size = 5;
    ((Tex_c062_01E03550 *)(s32)&pk)->regs = 0x42421;
    ((Tex_c062_01E03550 *)(s32)&pk)->pad4 = 0;
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
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->count == 241) {
        func_001076F0(o->col, 0x90, 0x70, 0x80);
    }
    if (o->tick < 280) {
        if (g->count < 216) {
            if (o->col[3] < 0x50) {
                o->col[3] += 10;
            }
        }
        if (g->count > 216) {
            if (o->col[3] > 0x40) {
                o->col[3] -= 6;
            }
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape c062:01E037E0, 127 insns: five star points around a centre: each point is cleared to (0, 0, c.z), then placed at
   angle 90 / 18 / 162 / -54 / 234 (the middle four mirrored by the side flag) on a circle of radius c.x around c.y */

typedef struct {
    u8 pad0[0xD8];
    u8 sin[1];
} Scene_c062_01E037E0;

static s32 func_01E037E0_c062(Scene_c062_01E037E0 *g, Vec4f *out, Vec4f *src, s32 side) {
    extern void func_00106DD0(void *, f32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f c;
    f32 cz;
    f32 cy;
    f32 z0;
    s16 a;
    s16 i;

    c = *src;
    cz = c.z;
    cy = c.y;
    for (i = 0; i < 5; i++) {
        z0 = 0.0f;
        func_00106DD0(out, z0, z0, cz);
        if (i == 0) {
            a = 90;
        } else if (i == 1) {
            if (side == 0) {
                a = 18;
            } else {
                a = 162;
            }
        } else if (i == 2) {
            if (side == 0) {
                a = 162;
            } else {
                a = 18;
            }
        } else if (i == 3) {
            if (side == 0) {
                a = -54;
            } else {
                a = 234;
            }
        } else if (i == 4) {
            if (side == 0) {
                a = 234;
            } else {
                a = -54;
            }
        }
        out->y = cy + c.x * func_00108030(g->sin, a, 0);
        out->x = c.x * func_00108030(g->sin, a, 1);
        if (i < 5) {
            out++;
        }
    }
    return 0;
}

/* shape c062:01E039E0, 127 insns, 1 copy: scene setup: five model ids picked from a random word 3-bit fields (+0x100
   in mode 1); lights/slots 0..10 and 256..266 switched on and placed; then each of the five entries gets a random
   turn, its model frame, position, a 0x4000 rotation, colour (alpha 0x80) and a tenth scale */

typedef struct {
    s32 w0;
    s32 w4;
    u8 pad8[0x1C];
    s32 turn;
    u8 pad28[8];
    s32 rot[4];
    Vec4f scale;
    u8 pad50[0x10];
    u8 col[4];
    s32 w64;
    u8 pad68[8];
} Ent_c062_01E039E0;

typedef struct {
    u8 pad0[0x5A50];
    Ent_c062_01E039E0 ent[5];
    u8 pad5C80[0x7E0];
    Vec4f light[22];
    u8 pad65C0[0x2BC];
    s32 ids[5];
    u8 pad6890[0xC];
    s32 cnt[5];
    u8 pad68B0[0x8A];
    s16 mode;
} Scene_c062_01E039E0;

static void func_01E039E0_c062(Scene_c062_01E039E0 *g) {
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5D10(s32, void *);
    s32 r;
    s16 i;
    s32 k;
    Ent_c062_01E039E0 *e;

    r = func_001F5380();
    if (g->mode == 0) {
        g->ids[0] = 0;
        g->ids[2] = (r >> 6) & 7;
        g->ids[1] = (r >> 9) & 7;
        g->ids[4] = r & 7;
        g->ids[3] = (r >> 3) & 7;
    } else if (g->mode == 1) {
        g->ids[0] = 0x100;
        g->ids[2] = ((r >> 6) & 7) + 0x100;
        g->ids[1] = ((r >> 9) & 7) + 0x100;
        g->ids[4] = (r & 7) + 0x100;
        g->ids[3] = ((r >> 3) & 7) + 0x100;
    }
    for (i = 0; i < 22; i++) {
        k = i;
        if (k > 10) {
            k += 0xF5;
        }
        func_001F5970(k, 1);
        func_001F5CA0(k, &g->light[i]);
    }
    for (i = 0; i < 5; i++) {
        r = g->ids[i];
        e = &g->ent[i];
        g->ent[i].w64 = 0;
        e->turn = func_0019A5C8() % 360;
        g->cnt[i] = 30;
        func_001F5BD0(r, e);
        e->w4 = 0;
        func_001F5B70(r, e);
        func_001F5CA0(r, e->rot);
        e->rot[1] = 0;
        e->rot[0] = 0x4000;
        func_001F5C40(r, e->rot);
        func_001F5E40(r, e->col);
        e->col[3] = 0x80;
        e->scale.x = 0.1f;
        e->scale.y = 0.1f;
        e->scale.z = 0.1f;
        func_001F5D10(r, &e->scale);
    }
}


INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E03BE0_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E04470_c062);

/* shape c062:01E05520, 82 insns: c035:01E01150 family: take the first free effect slot of 200 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_c062_01E05520;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_c062_01E05520 slot[200];
    u8 padEnd[0x6844 - 0x2a0 - 200 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad6848[0xE0];
    s16 ang;
    u8 pad692A[0xA];
    s16 h30;
} Ctx_c062_01E05520;

static s32 func_01E05520_c062(Ctx_c062_01E05520 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_c062_01E05520 *s;

    s = NULL;
    for (i = 0; i < 200; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 200;
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

/* shape c062:01E05670, 138 insns: two-colour sprite quad at an object's position (b016:01E00920 packet): blend from flags >> 4, size o->f48; mode (flags & 0xF) 0 = far z, else the given depth */

/* OVL_WARM */

typedef struct {
    f32 u, v;
} Uv_c062_01E05670;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_c062_01E05670;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_c062_01E05670 uv;
    Xyz_c062_01E05670 v[4];
    u64 pad58[7];
} Pk_c062_01E05670;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 size;
    u8 pad4C[0x14];
    u8 col[4];
    u8 col2[4];
} Obj_c062_01E05670;

static void func_01E05670_c062(s32 arg0, Obj_c062_01E05670 *o, s32 flags, f32 depth) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f v;
    f32 d[4];
    f32 m[16];
    Pk_c062_01E05670 pk;
    s32 ot;
    Pk_c062_01E05670 *p;
    s16 sel;

    ot = (s32)func_00207500();
    p = (Pk_c062_01E05670 *)(u32)&pk;
    func_00107990(p, o->col, 1);
    func_00107990(p, o->col2, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v.x = o->x;
    v.y = o->y;
    v.z = o->z;
    func_00108EF0(m, NULL, NULL, &v);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, d) != 0) {
        if ((flags & 0xF) == 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, ot, 0);
            return;
        }
        func_002075F0(p, ot, (u32)depth);
    }
}
