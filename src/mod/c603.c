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

static void func_01E00080_c603(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c602:01E01620, 510 insns: draws a 23 x 16 grid of textured tiles: each tile's alpha from a per-tile table,
   its texture cell (tw / 16 by th / 23) from (u0, v0), a square of half-size half around its point (z only under
   flag 0x1E, else additive blend when z > 0); the first tile also binds the object's texture (func_001DA7A0). */

typedef struct {
    u8 b, g, r, a;
} Src_c602_01E01620;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c602_01E01620;

typedef struct {
    u64 v;
} Q_c602_01E01620;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c602_01E01620 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c602_01E01620;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c602_01E01620 v[4];
    u8 pad70[8];
    Q_c602_01E01620 t0, t1, t2;
} Pkt_c602_01E01620;

typedef struct {
    f32 x, y, z;
} Pt_c602_01E01620;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    Src_c602_01E01620 col;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c602_01E01620 pos[23][16];
    u8 pad1160[0x6C0];
    u8 alpha[23][16];
} Grid_c602_01E01620;

typedef struct {
    u8 pad0[0x60];
    Q_c602_01E01620 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c602_01E01620;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c602_01E01620;

static s32 func_01E00120_c603(Obj_c602_01E01620 *o, Cam_c602_01E01620 *cam, Grid_c602_01E01620 *g) {
    extern void c603_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001D9F00(void *, s32);
    extern void func_001DA7A0(s32, void *);
    s32 r;
    s32 fl;
    s32 du;
    s32 c;
    s32 dv;
    f32 dep[4];
    Vec4f p[3];
    Pkt_c602_01E01620 pkt;

    fl = func_001D9F00(o, 1);
    ((Pkt_c602_01E01620 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->pad = 0;
    if (func_00104520(g->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(g->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    du = g->tw >> 4;
    dv = g->th / 23;
    for (r = 0; r < 23; r++) {
        for (c = 0; c < 16; c++) {
            g->col.a = g->alpha[r][c];
            c603_01E00080(&pkt, &g->col);
            g->u = g->u0 + (s16)(c * du);
            g->v = g->v0 + (s16)(r * dv);
            ((Pkt_c602_01E01620 *)(s32)&pkt)->count |= 0x800;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->v = (g->v + dv - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->v = (g->v + dv - 1) << 4;
            if (func_00104520(g->flags, 0x1E) == 0 && !(g->pos[r][c].z <= 0.0f)) {
                func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
            }
            p[0].x = g->pos[r][c].x - g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[0].uv + 1, &dep[0]) != 0) {
                g->flags |= 0x100000;
            }
            p[0].x = g->pos[r][c].x + g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[1].uv + 1, &dep[1]) != 0) {
                g->flags |= 0x200000;
            }
            p[1].x = g->pos[r][c].x - g->half;
            p[1].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[1].z = g->pos[r][c].z;
            } else {
                p[1].z = 0.0f;
            }
            if (func_00205440(&p[1], cam->view, &pkt.v[2].uv + 1, &dep[2]) != 0) {
                g->flags |= 0x400000;
            }
            p[2].x = g->pos[r][c].x + g->half;
            p[2].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[2].z = g->pos[r][c].z;
            } else {
                p[2].z = 0.0f;
            }
            if (func_00205440(&p[2], cam->view, &pkt.v[3].uv + 1, &dep[3]) != 0) {
                g->flags |= 0x800000;
            }
            pkt.t0 = o->t0;
            pkt.t1 = o->t1;
            pkt.t2 = o->t2;
            if (r == 0 && c == 0) {
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
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c603", func_01E00920_c603);

/* shape c603:01E00E10 (c603), 365 insns, 1 copy: the c603 module main: on start copies the unit's object, sets up a
   23 x 16 (code 0) or 8 x 8 grid of card tiles (texture 3/2) in rows from y 17.6, timer 60; each tick picks the unit
   colour, draws the grid (LkSortDividedCard or LkSortDividedCard2), jitters every tile by t, fades each tile by 2,
   adds t << 9 to field 0x14; 8 when the last tile fades out or the timer ends, 2 at tick 53 */

typedef struct {
    f32 x __attribute__((aligned(16)));
    f32 y, z;
    u8 pad0C[0x75];
    s8 b0 : 5;
    s8 f5 : 1;
    s8 f6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} Obj_c603_01E00E10;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[4];
    u8 pos[0x50];
    Grid_c602_01E01620 grid;
    u8 pad1A00[0x90];
    Obj_c603_01E00E10 obj;
    u8 col[4];
    s32 w1B34;
    s32 timer;
    s32 code;
    s32 t;
    f32 half[2];
    s32 rows[2];
    s32 cols[2];
    f32 step[2];
    u8 pad1B64[0xC];
} Scene_c603_01E00E10;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[0x27];
    s8 b43;
} Ent_c603_01E00E10;

static s32 func_01E00E10_c603(s32 arg0, s32 code) {
    Scene_c603_01E00E10 *g = (Scene_c603_01E00E10 *)arg0;
    extern s32 func_001F5380(void);
    extern Ent_c603_01E00E10 *func_001F5B30(s32);
    extern s32 c603_01E00920();
    s32 i;
    s32 j;
    s32 ch;
    Ent_c603_01E00E10 *e;
    s32 ot;

    func_00207500();
    ch = func_001F5380();
    e = func_001F5B30(ch);
    if (e == 0) {
        return 8;
    }
    if (code >= 0) {
        func_00195108((s32)g, 0x1B70);
        func_00103890(g);
        g->obj = *(Obj_c603_01E00E10 *)e;
        func_001F5970(ch, 1);
        g->obj.f6 = 1;
        g->obj.f5 = 1;
        g->t = 1;
        g->w1B34 = 0;
        g->timer = 0x3C;
        g->code = code;
        e->b43 = 0;
        g->obj.x = g->obj.y = g->obj.z = 0;
        g->half[0] = 0.8f;
        g->half[1] = 1.6f;
        g->rows[0] = 0x17;
        g->rows[1] = 8;
        g->cols[0] = 0x10;
        g->cols[1] = 8;
        g->step[0] = -2.0f;
        g->step[1] = -2.875f;
        *(s32 *)g->grid.pad0 = func_00202BF0(3, 2);
        g->grid.flags = 0x40000801;
        g->grid.half = g->half[g->code];
        g->grid.u = 0;
        g->grid.v = 0;
        g->grid.u0 = 0;
        g->grid.v0 = 0;
        g->grid.tw = 0x100;
        g->grid.th = 0x170;
        g->grid.col.b = g->grid.col.g = g->grid.col.r = 0x80;
        for (i = 0; i < g->rows[g->code]; i++) {
            for (j = 0; j < g->cols[g->code]; j++) {
                g->grid.pos[i][j].x = -12.0f + 2.0f * g->grid.half * j;
                g->grid.pos[i][j].z = 0.0f;
                g->grid.pos[i][j].y = 17.6f + i * (g->step[g->code] * g->grid.half);
                g->grid.alpha[i][j] = 0x80;
            }
        }
        func_001F53B0(0, (s32)g->pos);
        g->f10 = e->f10;
        g->f14 = e->f14;
        g->f18 = e->f18;
        return 0;
    }
    func_001038D0(g);
    if (func_001F5EC0(ch) != 0) {
        func_001F6490(ch, g->col);
        func_00103470(&g->col[3], 0, 4);
        func_001F63E0(ch, (s32)g->col);
    }
    ot = func_00207F60();
    func_001D99F0();
    if (g->code == 0) {
        func_01E00120_c603((Obj_c602_01E01620 *)&g->obj, (Cam_c602_01E01620 *)g, &g->grid);
    } else {
        c603_01E00920(&g->obj, g, &g->grid);
    }
    for (i = 0; i < g->rows[g->code]; i++) {
        for (j = 0; j < g->cols[g->code]; j++) {
            g->grid.pos[i][j].z += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
            g->grid.pos[i][j].x += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
            g->grid.pos[i][j].y += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
            if (i == 0 && j == 0) {
                g->f14 += g->t << 9;
            }
            if (func_00103470(&g->grid.alpha[i][j], 0, 2) == 0 && i == g->rows[g->code] - 1 &&
                j == g->cols[g->code] - 1) {
                return 8;
            }
            if (g->grid.alpha[g->rows[g->code] - 1][g->cols[g->code] - 1] <= 0x60) {
                g->grid.flags = 0x40000001;
            }
        }
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    g->t++;
    g->timer--;
    if (g->t == 0x35) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
