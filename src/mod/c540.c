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

static void func_01E00080_c540(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_c540(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
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

static s32 func_01E00330_c540(void *arg0, s32 arg1, f32 *arg2) {
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

/* shape c536:01E00440, 164 insns, 9 copies: draw a model's afterimages: for each older transform in the history
   (newest last), a copy of the model placed there with alpha / (k + 1) (far z), then the model itself */

typedef struct Prim_c536_01E00440 {
    u8 pad0[0x10];
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u8 pad18[3];
    u8 a;
    u8 pad1C[0x14];
} Prim_c536_01E00440;

typedef struct Mdl_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    Vec4f v30;
    u8 pad40[0x38];
    Prim_c536_01E00440 *prims;
    u8 pad7C[6];
    s16 count : 12;
    s16 pad82 : 4;
    u8 pad84[0xC];
} __attribute__((aligned(16))) Mdl_c536_01E00440;

typedef struct Obj_c536_01E00440 {
    Mdl_c536_01E00440 m;
    s32 f90;
} Obj_c536_01E00440;

typedef struct Hist_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c536_01E00440;

static s32 func_01E00440_c540(Obj_c536_01E00440 *o, s32 alpha, s32 n, Hist_c536_01E00440 *hist) {
    extern s32 func_001D9F00();
    extern void func_001DA7A0();
    extern void func_001DBCF0();
    Mdl_c536_01E00440 copy;
    s32 k;
    s32 j;
    s32 r;

    for (k = n - 1; k > 0; k--) {
        copy = o->m;
        copy.v00 = hist[k].v20;
        copy.v10 = hist[k].v10;
        copy.v30 = hist[k].v00;
        r = func_001D9F00(&copy, 1);
        for (j = 0; j < copy.count; j++) {
            copy.prims[j].z = 0xFFFFFE;
            if (alpha) {
                copy.prims[j].a = alpha / (k + 1);
            } else {
                copy.prims[j].a = 0;
            }
        }
        if (k == n - 1) {
            if (r) {
                func_001DA7A0(o->f90, o);
            } else {
                func_001DA7A0(0, o);
            }
        }
        func_001DBCF0(&copy);
    }
    func_001D9F00(o, 1);
    for (j = 0; j < o->m.count; j++) {
        o->m.prims[j].z = 0xFFFFFF;
        o->m.prims[j].a = alpha;
    }
    func_001DBCF0(o);
    return 0;
}

/* shape b001:01E00A30, 740 insns, 55 copies: draws an emitter's particles as textured quads. Each point moves
   with the velocity (or func_001036A0), turns around the emitter centre while the angle catches up, and gets a
   square of the emitter size, aspect-scaled, either rotated (flag 0x1E) or axis-aligned.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E00A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E00A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E00A30 v[4];
    u8 tail[0x20];
} Pkt_b001_01E00A30;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E00A30;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt_b001_01E00A30;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E00A30 color;
    f32 size;
    f32 cx, cy;
    u8 pad18[8];
    s16 u, v, w, h;
    f32 fw, fh;
    Pt_b001_01E00A30 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
} Emit_b001_01E00A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E00A30;

static s32 func_01E006D0_c540(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b001_01E00A30 p;
    Pkt_b001_01E00A30 pkt;
    s32 i;
    f32 dx;
    f32 dy;
    f32 da;
    f32 r;
    f32 kx;
    f32 ky;

    ((Pkt_b001_01E00A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c540((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
    for (i = 0; i < e->count; i++) {
        if (e->cur != e->angle) {
            if (func_00104520(e->flags, 0x1F) != 0) {
                da = e->angle - e->cur;
                dx = e->pts[i].x - e->cx;
                dy = e->pts[i].y - e->cy;
                if (func_00104520(e->flags, 7) != 0) {
                    func_001036A0(&e->pts[i].x, vel);
                    r = 0.017453292f * da;
                    e->pts[i].x = e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r));
                    e->pts[i].y = e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r));
                } else {
                    r = 0.017453292f * da;
                    e->pts[i].x = vel->x + (e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r)));
                    e->pts[i].y = vel->y + (e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r)));
                }
            } else if (func_00104520(e->flags, 7) != 0) {
                func_001036A0(&e->pts[i].x, vel);
            } else {
                e->pts[i].x += vel->x;
                e->pts[i].y += vel->y;
            }
            if (i == e->count - 1) {
                e->cur = e->angle;
            }
        } else if (func_00104520(e->flags, 7) != 0) {
            func_001036A0(&e->pts[i].x, vel);
        } else {
            e->pts[i].x += vel->x;
            e->pts[i].y += vel->y;
        }
        func_00105260(&pkt, e, i);
        if (func_00104520(e->flags, 0) != 0) {
            if (e->w > e->h) {
                kx = 1.0f;
                ky = (f32)e->h / (f32)e->w;
            } else if (e->w < e->h) {
                kx = (f32)e->w / (f32)e->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (e->fw > e->fh) {
                ky = e->fh / e->fw;
                kx = 1.0f;
            } else if (e->fw < e->fh) {
                kx = e->fh / e->fw;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
        if (func_00104520(e->flags, 0x1E) != 0) {
            r = 0.017453292f * ((e->angle + 135) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            r = 0.017453292f * ((e->angle + 45) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            r = 0.017453292f * ((e->angle + 225) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            r = 0.017453292f * ((e->angle + 315) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        } else {
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->u << 4) | ((u64)(e->u + e->w - 1) << 14) |
                                        ((u64)e->v << 24) | ((u64)(e->v + e->h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (e->pts[i].life >= 0 && func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
    }
    if (func_00104520(e->flags, 7) == 0) {
        e->cx += vel->x;
        e->cy += vel->y;
    }
    return 0;
}

/* shape c540:01E01260 (c540), 1025 insns, 1 copy: c540 module main (c536:01E02510's two-unit card form with
   c612:01E014B0's flame emitters): on start copies both unit models, places them at -125/125, -8 (code 1/2 sends them
   in over 20 ticks), sets up two flame emitters (texture 15, 16 points jittered around the origin); each tick turns
   the view, flag 4 draws both emitters scaled 1.01 (fading them from tick 47), then the units step in, B rides toward
   A with afterimages and they leave, releasing each unit as it lands; returns 2 on tick 46, 8 when done */

typedef struct Src_c540_01E01260 {
    Vec4f p0;
    Vec4f p1;
    u8 pad20[0x23];
    u8 f43;
    u8 pad44[0x5C];
} __attribute__((aligned(16))) Src_c540_01E01260;

typedef struct Unit_c540_01E01260 {
    Vec4f pos;
    s32 rot[4];
    s32 v20[4];
    Vec4f v30;
    u8 pad40[0x41];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c540_01E01260;

typedef struct Ctl_c540_01E01260 {
    Vec4f a;
    s32 b[4];
    s32 z[3];
    u8 pad2C[4];
    f32 s[2];
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 on;
    u8 pad4C[4];
} Ctl_c540_01E01260;

typedef struct Hist_c540_01E01260 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c540_01E01260;

typedef struct Col_c540_01E01260 {
    u8 b, g, r, a;
} Col_c540_01E01260;

typedef struct Pt_c540_01E01260 {
    f32 x, y, z;
    s16 hC;
    s16 hE;
} Pt_c540_01E01260;

typedef struct Emit_c540_01E01260 {
    s32 texture;
    s32 flags;
    Col_c540_01E01260 color;
    f32 size;
    f32 cx;
    f32 cy;
    f32 z0;
    s32 w1C;
    s16 rect[8];
    Pt_c540_01E01260 pt[16];
    s16 count;
    u8 pad132[4];
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_c540_01E01260;

typedef struct Cam_c540_01E01260 {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Cam_c540_01E01260;

typedef struct Scene_c540_01E01260 {
    Cam_c540_01E01260 cam;
    Emit_c540_01E01260 e0;
    Emit_c540_01E01260 e1;
    Hist_c540_01E01260 hist[4];
    Unit_c540_01E01260 a;
    Unit_c540_01E01260 b;
    Ctl_c540_01E01260 ctl[2];
    s32 timer;
    s32 life;
    s32 count;
    s32 code;
    s32 flags;
    s32 alphaA;
    s32 alphaB;
    u8 pad6CC[4];
} Scene_c540_01E01260;

static s32 func_01E01260_c540(s32 arg0, s32 code) {
    Scene_c540_01E01260 *g = (Scene_c540_01E01260 *)arg0;
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5B30(s32);
    extern s32 func_001F59D0(s32, s32);
    extern void func_00195108(void *, s32);
    extern void func_00205CB0(void *, f32, f32);
    extern void func_00205C40();
    extern void func_00104490(void *, void *, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00103260(void *, s32);
    extern s32 func_00103470(void *, s32, s32);
    extern s32 c540_01E00440();
    s32 ot;
    s32 idA;
    s32 idB;
    Src_c540_01E01260 *a;
    Src_c540_01E01260 *b;
    Vec4f sc;
    s32 tex[4];
    s32 i;

    ot = (s32)func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Src_c540_01E01260 *)func_001F5B30(idA);
    b = (Src_c540_01E01260 *)func_001F5B30(idB);
    if (a == NULL && b == NULL) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x6D0);
        func_00103890(&g->cam);
        if (a) {
            g->a = *(Unit_c540_01E01260 *)a;
        }
        if (b) {
            g->b = *(Unit_c540_01E01260 *)b;
        }
        if (a) {
            func_001F59D0(idA, 1);
            g->a.b6 = 1;
            g->a.b5 = 1;
        }
        if (b) {
            func_001F59D0(idB, 1);
            g->b.b6 = 1;
            g->b.b5 = 1;
        }
        g->flags = 0;
        g->life = 0x78;
        g->code = code;
        if (g->code == 0 || g->code == 3) {
            g->count = 20;
        } else {
            g->count = 0;
        }
        g->timer = 14;
        if (a) {
            a->f43 = 0;
        }
        if (b) {
            b->f43 = 0;
        }
        g->alphaA = g->alphaB = 0x80;
        g->ctl[0].x = -125.0f;
        g->ctl[0].y = -8.0f;
        g->ctl[1].x = 125.0f;
        g->ctl[1].y = -8.0f;
        if (g->code == 1 || g->code == 2) {
            if (a) {
                g->ctl[0].on = 20;
                func_00205CB0(&g->ctl[0], g->ctl[0].x, g->ctl[0].y);
                func_00205C40(g->ctl[0].z);
                g->ctl[0].z[0] -= g->a.v20[0];
                g->ctl[0].z[1] -= g->a.v20[1];
                g->ctl[0].z[2] -= g->a.v20[2];
                g->ctl[0].b[0] = 0;
                g->ctl[0].b[1] = 0x10000;
                g->ctl[0].b[2] = 0x10000;
                g->ctl[0].s[0] = 0.46875f;
                g->ctl[0].s[1] = 0.48913f;
            }
            if (b) {
                g->ctl[1].on = 20;
                func_00205CB0(&g->ctl[1], g->ctl[1].x, g->ctl[1].y);
                func_00205C40(g->ctl[1].z);
                g->ctl[1].z[0] -= g->b.v20[0];
                g->ctl[1].z[1] -= g->b.v20[1];
                g->ctl[1].z[2] -= g->b.v20[2];
                g->ctl[1].b[0] = 0;
                g->ctl[1].b[1] = 0x10000;
                g->ctl[1].b[2] = 0x10000;
                g->ctl[1].s[0] = 0.46875f;
                g->ctl[1].s[1] = 0.48913f;
            }
        } else {
            if (a) {
                g->flags |= 1;
                g->ctl[0].on = 1;
                func_00205CB0(&g->a, g->ctl[0].x, g->ctl[0].y);
                g->ctl[0].a = a->p0;
                func_00205C40(g->a.v20);
                g->ctl[0].z[0] = g->ctl[0].z[1] = g->ctl[0].z[2] = 0;
                g->a.rot[0] = 0;
                g->a.rot[1] = 0x10000;
                g->a.rot[2] = 0x10000;
                *(Vec4f *)g->ctl[0].b = a->p1;
                g->ctl[0].s[0] = g->ctl[0].s[1] = 0.1f;
                g->a.v30.x = 0.46875f;
                g->a.v30.y = 0.48913f;
            }
            if (b) {
                g->flags |= 2;
                g->ctl[1].on = 1;
                func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
                g->ctl[1].a = b->p0;
                func_00205C40(g->b.v20);
                g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
                g->b.rot[0] = 0;
                g->b.rot[1] = 0x10000;
                g->b.rot[2] = 0x10000;
                *(Vec4f *)g->ctl[1].b = b->p1;
                g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
                g->b.v30.x = 0.46875f;
                g->b.v30.y = 0.48913f;
                for (i = 0; i < 4; i++) {
                    g->hist[i].v20 = g->b.pos;
                    g->hist[i].v10 = *(Vec4f *)g->b.rot;
                    g->hist[i].v00 = g->b.v30;
                }
            }
        }
        func_00103260(tex, 0xF);
        g->e0.texture = tex[0];
        g->e0.flags = 0x81083;
        g->e0.cx = 0.0f;
        g->e0.cy = 0.0f;
        g->e0.z0 = 0.0f;
        g->e0.w1C = 0;
        g->e0.rect[4] = 0x80;
        g->e0.rect[5] = 0xC0;
        g->e0.rect[2] = 0x20;
        g->e0.rect[3] = 0x20;
        g->e0.rect[6] = 0x80;
        g->e0.rect[7] = 0x100;
        g->e0.size = 120.0f;
        g->e0.count = 8;
        g->e0.step = 3;
        g->e0.h13C = 1;
        g->e0.h140 = 8;
        g->e0.h136 = 10;
        g->e0.h138 = 10;
        g->e0.color.r = 0x40;
        g->e0.color.g = 0x20;
        g->e0.color.b = 0x60;
        g->e0.color.a = 0x30;
        for (i = 0; i < 16; i++) {
            g->e0.pt[i].x = g->e0.cx + (func_0019A5C8() % 200 - 100);
            g->e0.pt[i].y = g->e0.cy + (func_0019A5C8() % 160 - 40);
            g->e0.pt[i].z = g->e0.z0;
            g->e0.pt[i].hE = -g->e0.step * i;
            g->e0.pt[i].hC = 0;
            g->e0.h13E = g->e0.h140 - 1;
        }
        g->e1.texture = tex[0];
        g->e1.flags = 0x81083;
        g->e1.cx = 0.0f;
        g->e1.cy = 0.0f;
        g->e1.z0 = 0.0f;
        g->e1.w1C = 0;
        g->e1.rect[4] = 0x80;
        g->e1.rect[5] = 0xC0;
        g->e1.rect[2] = 0x20;
        g->e1.rect[3] = 0x20;
        g->e1.rect[6] = 0x80;
        g->e1.rect[7] = 0x100;
        g->e1.size = 120.0f;
        g->e1.count = 8;
        g->e1.step = 3;
        g->e1.h13C = 1;
        g->e1.h140 = 8;
        g->e1.h136 = 20;
        g->e1.h138 = 20;
        g->e1.color.r = 0x80;
        g->e1.color.g = 0x40;
        g->e1.color.b = 0x80;
        g->e1.color.a = 0x30;
        for (i = 0; i < 16; i++) {
            g->e1.pt[i].x = g->e1.cx + (func_0019A5C8() % 200 - 100);
            g->e1.pt[i].y = g->e1.cy + (func_0019A5C8() % 160 - 40);
            g->e1.pt[i].z = g->e1.z0;
            g->e1.pt[i].hE = -g->e1.step * i;
            g->e1.pt[i].hC = 0;
            g->e1.h13E = g->e1.h140 - 1;
        }
        func_001F53B0(0, (s32)&g->cam.pos);
        return 0;
    }
    func_00103920(&g->cam, -125.0f, -8.0f);
    if (func_00104520(g->flags, 4)) {
        sc.x = sc.y = sc.z = 1.01f;
        func_01E006D0_c540(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e0, (Vec_b001_01E00A30 *)&sc);
        func_01E006D0_c540(ot, (Cam_b001_01E00A30 *)g, (Emit_b001_01E00A30 *)&g->e1, (Vec_b001_01E00A30 *)&sc);
        if (g->count > 0x2E) {
            func_00103470(&g->e0.color.a, 0, 3);
            func_00103470(&g->e1.color.a, 0, 3);
        }
    }
    ot = func_00207F60();
    func_001D99F0();
    if (!func_00104520(g->flags, 4)) {
        if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
            if (g->code < 2) {
                if (a) {
                    func_01E00330_c540(&g->a, g->alphaA, NULL);
                }
                if (b) {
                    c540_01E00440(&g->b, g->alphaB, 4, g->hist);
                }
            } else {
                if (b) {
                    c540_01E00440(&g->b, g->alphaB, 4, g->hist);
                }
                if (a) {
                    func_01E00330_c540(&g->a, g->alphaA, NULL);
                }
            }
            if (g->timer < 7) {
                func_00104490(&g->b, &g->a, g->timer);
            }
            if (g->timer) {
                g->timer--;
            } else {
                g->flags |= 0x10;
                g->timer = 0x1E;
            }
        } else {
            if (a) {
                if (!func_00104520(g->flags, 0)) {
                    if (!func_01E00120_c540((Cam_c536_01E00120 *)&g->a, (Cam_c536_01E00120 *)&g->ctl[0])) {
                        g->flags |= 1;
                        g->a.rot[0] = 0;
                        g->a.rot[1] = 0;
                        g->a.rot[2] = 0;
                    }
                    func_01E00330_c540(&g->a, g->alphaA, NULL);
                }
            } else {
                g->flags |= 1;
            }
            if (b) {
                if (!func_00104520(g->flags, 1)) {
                    if (!func_01E00120_c540((Cam_c536_01E00120 *)&g->b, (Cam_c536_01E00120 *)&g->ctl[1])) {
                        g->flags |= 2;
                        g->b.rot[0] = 0;
                        g->b.rot[1] = 0;
                        g->b.rot[2] = 0;
                        for (i = 0; i < 4; i++) {
                            g->hist[i].v20 = g->b.pos;
                            g->hist[i].v10 = *(Vec4f *)g->b.rot;
                            g->hist[i].v00 = g->b.v30;
                        }
                    }
                    func_01E00330_c540(&g->b, g->alphaB, NULL);
                }
            } else {
                g->flags |= 2;
            }
        }
    } else if (!func_00104520(g->flags, 5)) {
        if (g->code < 2) {
            if (a) {
                g->ctl[0].on = 20;
                g->ctl[0].x = -125.0f;
                g->ctl[0].y = -8.0f;
                func_00205CB0(&g->a, g->ctl[0].x, g->ctl[0].y);
                g->ctl[0].a = a->p0;
                func_00205C40(g->a.v20);
                g->ctl[0].z[0] = g->ctl[0].z[1] = g->ctl[0].z[2] = 0;
                g->a.rot[0] = 0;
                g->a.rot[1] = 0x10000;
                g->a.rot[2] = 0x10000;
                *(Vec4f *)g->ctl[0].b = a->p1;
                g->ctl[0].s[0] = g->ctl[0].s[1] = 0.1f;
                g->a.v30.x = 0.46875f;
                g->a.v30.y = 0.48913f;
                func_01E00330_c540(&g->a, g->alphaA, NULL);
            }
            if (b) {
                func_01E00330_c540(&g->b, g->alphaB, NULL);
                if (g->count > 0x2E) {
                    func_00103500(&g->alphaB, 0, 0x10);
                }
            }
        } else {
            if (b) {
                g->ctl[1].on = 20;
                g->ctl[1].x = -125.0f;
                g->ctl[1].y = -8.0f;
                func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
                g->ctl[1].a = b->p0;
                func_00205C40(g->b.v20);
                g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
                g->b.rot[0] = 0;
                g->b.rot[1] = 0x10000;
                g->b.rot[2] = 0x10000;
                *(Vec4f *)g->ctl[1].b = b->p1;
                g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
                g->b.v30.x = 0.46875f;
                g->b.v30.y = 0.48913f;
                c540_01E00440(&g->b, g->alphaB, 4, g->hist);
            }
            if (a) {
                func_01E00330_c540(&g->a, g->alphaA, NULL);
                if (g->count > 0x2E) {
                    func_00103500(&g->alphaA, 0, 0x10);
                }
            }
        }
        if (g->timer == 0) {
            if (g->code == 0 || g->code == 3) {
                g->flags |= 8;
            } else {
                g->flags |= 0x20;
            }
        } else {
            g->timer--;
        }
    } else {
        if (g->code < 2) {
            if (a) {
                if (!func_00104520(g->flags, 2)) {
                    if (!func_01E00120_c540((Cam_c536_01E00120 *)&g->a, (Cam_c536_01E00120 *)&g->ctl[0])) {
                        g->flags |= 4;
                        g->a.rot[0] = ((Unit_c540_01E01260 *)a)->rot[0];
                        g->a.rot[1] = ((Unit_c540_01E01260 *)a)->rot[1];
                        g->a.rot[2] = ((Unit_c540_01E01260 *)a)->rot[2];
                        func_001F59D0(idA, 0);
                    }
                    func_01E00330_c540(&g->a, g->alphaA, NULL);
                }
            } else {
                g->flags |= 4;
            }
        } else {
            if (b) {
                if (!func_00104520(g->flags, 3)) {
                    if (!func_01E00120_c540((Cam_c536_01E00120 *)&g->b, (Cam_c536_01E00120 *)&g->ctl[1])) {
                        g->flags |= 8;
                        g->b.rot[0] = ((Unit_c540_01E01260 *)b)->rot[0];
                        g->b.rot[1] = ((Unit_c540_01E01260 *)b)->rot[1];
                        g->b.rot[2] = ((Unit_c540_01E01260 *)b)->rot[2];
                        func_001F59D0(idB, 0);
                    }
                    func_01E00330_c540(&g->b, g->alphaB, NULL);
                }
            } else {
                g->flags |= 8;
            }
        }
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    for (i = 3; i >= 0; i--) {
        if (i != 0) {
            g->hist[i].v20 = g->hist[i - 1].v20;
            g->hist[i].v10 = g->hist[i - 1].v10;
            g->hist[i].v00 = g->hist[i - 1].v00;
        } else {
            g->hist[i].v20 = g->b.pos;
            g->hist[i].v10 = *(Vec4f *)g->b.rot;
            g->hist[i].v00 = g->b.v30;
        }
    }
    g->count++;
    g->life--;
    if (func_00104520(g->flags, 2) || func_00104520(g->flags, 3)) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    if (g->count == 0x2E) {
        return 2;
    }
    if (g->life <= 0) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    return 0;
}
