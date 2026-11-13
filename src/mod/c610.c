#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c610(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* shape c610:01E00120, 374 insns, 2 copies: draws a frame of 4 gouraud quads around an object's 4 corner points (each quad
   from a corner and the previous one, outer edge pushed out by 1/6, inner edge black, outer edge in the object's
   colour or random greys by flag 0xC); each corner's visibility is flagged on the object (bits 20..23) and a quad
   is drawn only when all four of its points project; blend by flags 0xB/0xA, depth far by flag 0x13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c610_01E00120;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    struct {
        u8 r, g, b, a;
        f32 q;
        Xyz_c610_01E00120 p;
    } v[4];
    u8 tail[8];
} Pkt_c610_01E00120;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 b, g, r, a;
    u8 padC[4];
    Vec4f pts[4];
} Frame_c610_01E00120;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_c610_01E00120;

static s32 func_01E00120_c610(s32 ot, Frame_c610_01E00120 *o, Cam_c610_01E00120 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 d[4];
    Vec4f p;
    Pkt_c610_01E00120 pkt __attribute__((aligned(8)));
    s32 k;
    s32 prev;

    ((Pkt_c610_01E00120 *)(s32)&pkt)->count = 0x14;
    ((Pkt_c610_01E00120 *)(s32)&pkt)->tag = 8;
    ((Pkt_c610_01E00120 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_c610_01E00120 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.v[0].r = 0;
    pkt.v[0].g = 0;
    pkt.v[0].b = 0;
    pkt.v[0].a = o->a;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = 0;
    pkt.v[1].g = 0;
    pkt.v[1].b = 0;
    pkt.v[1].a = o->a;
    pkt.v[1].q = 1.0f;
    if (func_00104520(o->flags, 0xC) != 0) {
        pkt.v[2].r = func_0019A5C8() % 128;
        pkt.v[2].g = func_0019A5C8() % 128;
        pkt.v[2].b = func_0019A5C8() % 128;
        pkt.v[2].a = o->a;
        pkt.v[2].q = 1.0f;
        pkt.v[3].r = func_0019A5C8() % 128;
        pkt.v[3].g = func_0019A5C8() % 128;
        pkt.v[3].b = func_0019A5C8() % 128;
        pkt.v[3].a = o->a;
        pkt.v[3].q = 1.0f;
    } else {
        pkt.v[2].r = o->r;
        pkt.v[2].g = o->g;
        pkt.v[2].b = o->b;
        pkt.v[2].a = o->a;
        pkt.v[2].q = 1.0f;
        pkt.v[3].r = o->r;
        pkt.v[3].g = o->g;
        pkt.v[3].b = o->b;
        pkt.v[3].a = o->a;
        pkt.v[3].q = 1.0f;
    }
    for (k = 3; k > -1; k--) {
        if (k == 0) {
            prev = 3;
        } else {
            prev = k - 1;
        }
        p.x = o->pts[k].x + o->pts[k].x / 6.0f;
        p.y = o->pts[k].y + o->pts[k].y / 6.0f;
        p.z = o->pts[k].z + o->pts[k].z / 6.0f;
        if (func_00205440(&p, cam->m, &pkt.v[0].p, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        p.x = o->pts[prev].x + o->pts[prev].x / 6.0f;
        p.y = o->pts[prev].y + o->pts[prev].y / 6.0f;
        p.z = o->pts[prev].z + o->pts[prev].z / 6.0f;
        if (func_00205440(&p, cam->m, &pkt.v[1].p, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        p.x = o->pts[k].x;
        p.y = o->pts[k].y;
        p.z = o->pts[k].z;
        if (func_00205440(&p, cam->m, &pkt.v[2].p, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        p.x = o->pts[prev].x;
        p.y = o->pts[prev].y;
        p.z = o->pts[prev].z;
        if (func_00205440(&p, cam->m, &pkt.v[3].p, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

typedef struct Cam_c536_01E00120 {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    s32 steps;
} Cam_c536_01E00120;

static s32 func_01E00700_c610(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
    f32 k;
    f32 px;
    f32 py;
    f32 pz;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 b1;
    s32 b2;

    if (t->steps != 0) {
        k = 1.0f / t->steps;
        py = k * (t->f30 - c->f30);
        pz = k * (t->f34 - c->f34);
        c->f30 += py;
        c->f34 += pz;
        a0 = k * (t->a[0] - c->a[0]);
        a1 = k * (t->a[1] - c->a[1]);
        a2 = k * (t->a[2] - c->a[2]);
        c->a[0] += a0;
        c->a[1] += a1;
        c->a[2] += a2;
        a2 = k * (t->b[0] - c->b[0]);
        a0 = k * (t->b[1] - c->b[1]);
        a1 = k * (t->b[2] - c->b[2]);
        c->b[0] += a2;
        c->b[1] += a0;
        c->b[2] += a1;
        px = k * (t->pos[0] - c->pos[0]);
        py = k * (t->pos[1] - c->pos[1]);
        pz = k * (t->pos[2] - c->pos[2]);
        c->pos[0] += px;
        c->pos[1] += py;
        c->pos[2] += pz;
    }
    t->steps--;
    return t->steps;
}

/* shape c536:01E00330: module copy of main-program func_0027F180 (rules/ta_misc.c): reset every vertex colour to white with the given alpha, then refresh the model. */

typedef struct Vertex_c536_01E00330 {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[3];
    u8 alpha;
    u8 pad1C[0x14];
} Vertex_c536_01E00330;

typedef struct Count_c536_01E00330 {
    s16 count : 12;
    s16 reserved : 4;
} Count_c536_01E00330;

typedef struct Object_c536_01E00330 {
    u8 pad0[0x78];
    Vertex_c536_01E00330 *vertices;
    s32 field7C;
    s16 field80;
    Count_c536_01E00330 field82;
    u8 pad84[0xC];
    s32 field90;
} Object_c536_01E00330;

static s32 func_01E00910_c610(void *arg0, s32 arg1, f32 *arg2) {
    Object_c536_01E00330 *object = arg0;
    s32 result;
    s32 i;

    if (arg2 != NULL) {
        result = func_001DA2B0(object, 0, arg2[0], arg2[1]);
    } else {
        result = func_001D9F00(object, 1);
    }
    for (i = 0; i < object->field82.count; i++) {
        object->vertices[i].color = 0xFFFFFF;
        object->vertices[i].alpha = arg1;
    }
    if (result != 0) {
        func_001DA7A0(object->field90, (s32) object);
    } else {
        func_001DA7A0(0, (s32) object);
    }
    func_001DBCF0((s32) object);
    return 0;
}

/* shape c610:01E00A20 (LkSortRasterCard), 471 insns, 1 copy: draws a 23-row strip of textured quads
   (LkSortDividedCard's one-column form): row r spans pos[r][0] to pos[r + 1][0], 256 wide, the full texture width,
   th / 23 per row */

typedef struct {
    u8 b, g, r, a;
} Src_c610_01E00A20;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c610_01E00A20;

typedef struct {
    u64 v;
} Q_c610_01E00A20;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c610_01E00A20 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c610_01E00A20;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c610_01E00A20 v[4];
    u8 pad70[8];
    Q_c610_01E00A20 t0, t1, t2;
} Pkt_c610_01E00A20;

typedef struct {
    f32 x, y, z;
} Pt_c610_01E00A20;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    Src_c610_01E00A20 col;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c610_01E00A20 pos[24][16];
} Grid_c610_01E00A20;

typedef struct {
    u8 pad0[0x60];
    Q_c610_01E00A20 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c610_01E00A20;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c610_01E00A20;

static s32 func_01E00A20_c610(Obj_c610_01E00A20 *o, Cam_c610_01E00A20 *cam, Grid_c610_01E00A20 *g) {
    extern void c610_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001D9F00(void *, s32);
    extern void func_001DA7A0(s32, void *);
    s32 dv;
    s32 r;
    s32 du;
    s32 fl;
    f32 dep[4];
    Vec4f p[3];
    Pkt_c610_01E00A20 pkt;

    fl = func_001D9F00(o, 1);
    ((Pkt_c610_01E00A20 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c610_01E00A20 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c610_01E00A20 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c610_01E00A20 *)(s32)&pkt)->pad = 0;
    if (func_00104520(g->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(g->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    }
    du = g->tw;
    dv = g->th / 23;
    for (r = 0; r < 23; r++) {
        c610_01E00080(&pkt, &g->col);
        g->u = g->u0;
        g->v = g->v0 + (s16)(r * dv);
        ((Pkt_c610_01E00A20 *)(s32)&pkt)->count |= 0x800;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[0].uv)->u = g->u << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[0].uv)->v = g->v << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[1].uv)->u = (g->u + du - 1) << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[1].uv)->v = g->v << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[2].uv)->u = g->u << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[2].uv)->v = (g->v + dv - 1) << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[3].uv)->u = (g->u + du - 1) << 4;
        ((Uv_c610_01E00A20 *)(s32)&pkt.v[3].uv)->v = (g->v + dv - 1) << 4;
        if (func_00104520(g->flags, 0x1E) == 0 && !(g->pos[r][0].z <= 0.0f)) {
            func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
        }
        p[0].x = g->pos[r][0].x - 128.0f;
        p[0].y = g->pos[r][0].y;
        if (func_00104520(g->flags, 0x1E) != 0) {
            p[0].z = g->pos[r][0].z;
        } else {
            p[0].z = 0.0f;
        }
        if (func_00205440(&p[0], cam->view, &pkt.v[0].uv + 1, &dep[0]) != 0) {
            g->flags |= 0x100000;
        }
        p[0].x = g->pos[r][0].x + 128.0f;
        p[0].y = g->pos[r][0].y;
        if (func_00104520(g->flags, 0x1E) != 0) {
            p[0].z = g->pos[r][0].z;
        } else {
            p[0].z = 0.0f;
        }
        if (func_00205440(&p[0], cam->view, &pkt.v[1].uv + 1, &dep[1]) != 0) {
            g->flags |= 0x200000;
        }
        p[1].x = g->pos[r + 1][0].x - 128.0f;
        p[1].y = g->pos[r + 1][0].y;
        if (func_00104520(g->flags, 0x1E) != 0) {
            p[1].z = g->pos[r][0].z;
        } else {
            p[1].z = 0.0f;
        }
        if (func_00205440(&p[1], cam->view, &pkt.v[2].uv + 1, &dep[2]) != 0) {
            g->flags |= 0x400000;
        }
        p[2].x = g->pos[r + 1][0].x + 128.0f;
        p[2].y = g->pos[r + 1][0].y;
        if (func_00104520(g->flags, 0x1E) != 0) {
            p[2].z = g->pos[r][0].z;
        } else {
            p[2].z = 0.0f;
        }
        if (func_00205440(&p[2], cam->view, &pkt.v[3].uv + 1, &dep[3]) != 0) {
            g->flags |= 0x800000;
        }
        pkt.t0 = o->t0;
        pkt.t1 = o->t1;
        pkt.t2 = o->t2;
        if (r == 0) {
            if (fl != 0) {
                func_001DA7A0(o->f90, o);
            } else {
                func_001DA7A0(0, o);
            }
        }
        if (func_00104520(g->flags, 0x14) != 0) {
            if (func_00104520(g->flags, 0x15) != 0 && func_00104520(g->flags, 0x16) != 0 &&
                func_00104520(g->flags, 0x17) != 0) {
                if (func_00104520(g->flags, 0x13) != 0) {
                    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                    func_002075F0(&pkt, 0, 0);
                } else {
                    func_002075F0(&pkt, 0, func_001A23B0((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
                }
            }
        }
        g->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape c610:01E01180 (c610), 552 insns, 1 copy: two-unit scene: setup copies both duel units, aims each at a side
   point and fills a frame and a 24-row card strip; else steps the units in, waves the strip by a growing sine, then
   fades the frame and sends unit B back; returns 8 when the timer runs out */

typedef struct {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0xB];
    u8 f43;
    u8 pad44[0x3D];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c610_01E01180;

typedef struct {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 steps;
    u8 pad4C[4];
} Ctl_c610_01E01180;

typedef struct {
    f32 x, y, z;
} Pt_c610_01E01180;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    u8 b, g, r, a;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c610_01E01180 pos[24][16];
} Grid_c610_01E01180;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 b, g, r, a;
    u8 padC[4];
    Vec4f pts[4];
} Frame_c610_01E01180;

typedef struct {
    Vec4f v[4];
} Tbl_c610_01E01180;

typedef struct {
    u8 cam0[0x70];
    Frame_c610_01E01180 frame;
    u8 padC0[0x40];
    u8 cam1[0x70];
    Grid_c610_01E01180 grid;
    u8 pad1390[0x600];
    u8 al[24][16];
    u8 pad1B10[0x80];
    Unit_c610_01E01180 a;
    Unit_c610_01E01180 b;
    Ctl_c610_01E01180 ctl[2];
    s32 timer;
    f32 dist;
    s32 alpha;
    s32 code;
    s32 tick;
    s32 flags;
    u8 pad1D88[4];
    s32 ph;
    s32 dph;
    f32 off;
    f32 amp;
    u8 pad1D9C[4];
} Scene_c610_01E01180;

static s32 func_01E01180_c610(s32 arg0, s32 code) {
    Scene_c610_01E01180 *g = (Scene_c610_01E01180 *)arg0;
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_00195108();
    extern void func_00205C40();
    extern s32 c610_01E00700();
    extern s32 c610_01E00910();
    extern s32 c610_01E00A20();
    extern s32 c610_01E00120();
    extern Tbl_c610_01E01180 D_01E01A80_c610;
    Tbl_c610_01E01180 c;
    s32 otm;
    s32 idA;
    s32 idB;
    Unit_c610_01E01180 *a;
    Unit_c610_01E01180 *b;
    s32 ot;
    s32 rv;
    s32 k;
    s32 j;

    otm = (s32)func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Unit_c610_01E01180 *)func_001F5B30(idA);
    b = (Unit_c610_01E01180 *)func_001F5B30(idB);
    rv = 0;
    if (a == NULL || b == NULL) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x1DA0);
        func_00103890(g->cam0);
        func_00103890(g->cam1);
        g->a = *a;
        if (b) {
            g->b = *b;
        }
        func_001F5970(idA, 1);
        g->a.b6 = 1;
        g->a.b5 = 1;
        func_001F5970(idB, 1);
        g->b.b6 = 1;
        g->b.b5 = 1;
        g->flags = 0;
        g->tick = 0;
        g->code = code >> 16;
        g->dist = -150.0f;
        a->f43 = 0;
        b->f43 = 0;
        g->alpha = 0x80;
        g->ctl[0].steps = 20;
        g->ctl[0].x = -150.0f;
        g->ctl[0].y = 0.0f;
        func_00205CB0(&g->ctl[0], g->ctl[0].x, g->ctl[0].y);
        func_00205C40(g->ctl[0].b);
        g->ctl[0].b[0] -= g->a.b[0];
        g->ctl[0].b[1] -= g->a.b[1];
        g->ctl[0].b[2] -= g->a.b[2];
        g->ctl[0].a[0] = 0;
        g->ctl[0].a[1] = 0x10000;
        g->ctl[0].a[2] = 0x10000;
        g->ctl[0].f30 = g->ctl[0].f34 = 1.0f;
        g->ctl[1].steps = 20;
        g->ctl[1].x = 150.0f;
        g->ctl[1].y = 0.0f;
        func_00205CB0(&g->ctl[1], g->ctl[1].x, g->ctl[1].y);
        func_00205C40(g->ctl[1].b);
        g->ctl[1].b[0] -= g->b.b[0];
        g->ctl[1].b[1] -= g->b.b[1];
        g->ctl[1].b[2] -= g->b.b[2];
        g->ctl[1].a[0] = 0;
        g->ctl[1].a[1] = 0x10000;
        g->ctl[1].a[2] = 0x10000;
        g->ctl[1].f30 = g->ctl[1].f34 = 1.0f;
        g->timer = 0x113;
        g->frame.flags = 0x80000;
        g->frame.r = 0x80;
        g->frame.g = 0x30;
        g->frame.b = 0x60;
        g->frame.a = 0xFF;
        c = D_01E01A80_c610;
        c.v[0].x = -128.0f;
        c.v[0].y = 184.0f;
        c.v[0].z = 0.0f;
        c.v[1].x = 128.0f;
        c.v[1].y = 184.0f;
        c.v[1].z = 0.0f;
        c.v[2].x = 128.0f;
        c.v[2].y = -184.0f;
        c.v[2].z = -0.0f;
        c.v[3].x = -128.0f;
        c.v[3].y = -184.0f;
        c.v[3].z = -0.0f;
        for (k = 0; k < 4; k++) {
            g->frame.pts[k].x = c.v[k].x;
            g->frame.pts[k].y = c.v[k].y;
            g->frame.pts[k].z = c.v[k].z;
        }
        g->grid.flags = 0x80801;
        g->grid.half = 8.0f;
        g->grid.u = 0;
        g->grid.v = 0;
        g->grid.u0 = 0;
        g->grid.v0 = 0;
        g->grid.tw = 0x100;
        g->grid.th = 0x170;
        g->grid.a = g->grid.b = g->grid.g = g->grid.r = 0x80;
        for (j = 0; j < 24; j++) {
            g->grid.pos[j][0].z = 0.0f;
            g->grid.pos[j][0].x = 0.0f;
            g->grid.pos[j][0].y = 184.0f + -2.0f * g->grid.half * j;
            g->al[j][0] = 0x80;
        }
        return 0;
    }
    {
        f32 x = 150.0f;
        f32 h = 0.0f;
        func_00103920(g->cam0, x, h);
    }
    func_00103920(g->cam1, g->dist, 0.0f);
    ot = func_00207F60();
    func_001D99F0();
    if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
        if (!func_00104520(g->flags, 0x1F)) {
            c610_01E00910(&g->b, g->alpha, &g->ctl[1].x);
        } else if (!func_00104520(g->flags, 0x1E)) {
            if (!c610_01E00700(&g->b, &g->ctl[1])) {
                g->flags |= 0x40000000;
                g->b.a[0] = b->a[0];
                g->b.a[1] = b->a[1];
                g->b.a[2] = b->a[2];
                func_001F5970(idB, 0);
            }
            c610_01E00910(&g->b, g->alpha, NULL);
        }
        if (!func_00104520(g->flags, 0x1C)) {
            c610_01E00A20(&g->a, g->cam1, &g->grid);
            for (k = 0; k < 24; k++) {
                g->grid.pos[k][0].x = 20.0f * func_0020B550(g->ph + g->dph * k);
                g->off = g->amp * (k * k);
                g->grid.pos[k][0].x += g->off;
            }
            g->ph += g->dph;
            if (!func_00104520(g->flags, 0x1D)) {
                if (!func_00103350(&g->dph, 0x1000, 0x100)) {
                    if (!func_00103390(&g->amp, 0.52083f, 0.01f)) {
                        g->flags |= 0x20000000;
                        g->grid.flags &= ~0x800;
                    }
                }
            } else {
                func_00103540(&g->amp, 0.0f, 0.01f);
                if (!func_00103390(&g->dist, 150.0f, 5.0f)) {
                    func_00103500(&g->dph, 0, 0x40);
                }
                if (!func_00103470(&g->grid.a, 0, 1)) {
                    g->flags |= 0x10000000;
                }
            }
        }
    } else {
        if (!func_00104520(g->flags, 0)) {
            if (!c610_01E00700(&g->a, &g->ctl[0])) {
                g->flags |= 1;
                g->a.a[0] = 0;
                g->a.a[1] = 0;
                g->a.a[2] = 0;
            }
            c610_01E00910(&g->a, g->alpha, NULL);
        }
        if (!func_00104520(g->flags, 1)) {
            if (!c610_01E00700(&g->b, &g->ctl[1])) {
                g->flags |= 2;
                g->b.a[0] = 0;
                g->b.a[1] = 0;
                g->b.a[2] = 0;
            }
            c610_01E00910(&g->b, g->alpha, NULL);
        }
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    if (!func_00104520(g->flags, 0x1F) && func_00104520(g->flags, 0x1C)) {
        c610_01E00120(otm, &g->frame, g->cam0);
        if (!func_00103470(&g->frame.a, 0, 8)) {
            g->flags |= 0x80000000;
            g->ctl[1].steps = 20;
            g->ctl[1].x = 150.0f;
            g->ctl[1].y = 0.0f;
            func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
            *(Vec4f *)g->ctl[1].pos = *(Vec4f *)b->pos;
            func_00205C40(g->b.b);
            g->ctl[1].b[0] = g->ctl[1].b[1] = g->ctl[1].b[2] = 0;
            g->b.a[0] = 0;
            g->b.a[1] = 0x10000;
            g->b.a[2] = 0x10000;
            *(Vec4f *)g->ctl[1].a = *(Vec4f *)b->a;
            g->ctl[1].f30 = g->ctl[1].f34 = 0.1f;
            g->b.f30 = g->b.f34 = 1.0f;
        }
    }
    g->tick++;
    if (--g->timer == 0) {
        func_001F5970(idB, 0);
        rv = 8;
    }
    return rv;
}
