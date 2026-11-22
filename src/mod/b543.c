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

static void func_01E00080_b543(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E00120_b543(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

/* shape b117:01E00270, 624 insns, 28 copies (-O3,p): LkEFF_SortLaser: draws a laser trail through cnt points (0x10
   bytes each), every point aged first: each piece between two projected points is four textured quads (above, below,
   right, left of the line) as wide as func_001018E0(base, depth), skipped unless both corners are on screen; alpha =
   min(object alpha, point alpha), first piece fades in from 0. Colour from the module helper b117:01E00080. Both
   spilled parameters are aligned(8) to put their homes at 0xE8/0xE0. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b117_01E00270;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b117_01E00270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b117_01E00270 uv;
    Xyz_b117_01E00270 xyz;
} Vtx_b117_01E00270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b117_01E00270 v[4];
    u8 tail[0x20];
} Pkt_b117_01E00270;

typedef struct {
    s16 u, v, w, h;
} Rect_b117_01E00270;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b117_01E00270 rect;
    u8 pad18[0xC];
    s16 tick;
    u8 pad26[2];
    s16 n1;
    s16 n2;
} Laser_b117_01E00270;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b117_01E00270;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b117_01E00270;

#pragma optimization_level 3

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E00270_b543(s32 ot __attribute__((aligned(8))), Laser_b117_01E00270 *o, Pt_b117_01E00270 *pts, Cam_b117_01E00270 *cam __attribute__((aligned(8)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b117_01E00270 s[2];
    Vec4f w;
    Pkt_b117_01E00270 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    s32 j;
    s32 cnt;
    f32 w0;
    f32 w1;

    if (func_00104520(o->flags, 0x1F) != 0) {
        cnt = o->n1;
    } else {
        cnt = o->n2;
    }
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b543((void *)&pkt, (void *)o->color);
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
    for (i = 0; i < cnt + 1; i++) {
        pts[i].age++;
    }
    for (i = 1; i < cnt; i++) {
        w.x = pts[i - 1].x;
        w.y = pts[i - 1].y;
        w.z = pts[i - 1].z;
        if (func_00205440(&w, cam->view, &s[0], &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        w.x = pts[i].x;
        w.y = pts[i].y;
        w.z = pts[i].z;
        if (func_00205440(&w, cam->view, &s[1], &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            w0 = func_001018E0(o->base, depth[0]);
            w1 = func_001018E0(o->base, depth[1]);
            if (o->a >= pts[i - 1].a) {
                pkt.v[0].a = pkt.v[2].a = pts[i - 1].a;
            } else {
                pkt.v[0].a = pkt.v[2].a = o->a;
            }
            if (o->a >= pts[i].a) {
                pkt.v[1].a = pkt.v[3].a = pts[i].a;
            } else {
                pkt.v[1].a = pkt.v[3].a = o->a;
            }
            if (i == 1) {
                pkt.v[0].a = pkt.v[2].a = 0;
            }
            for (j = 0; j < 4; j++) {
                if (j < 2) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                    if (j == 0) {
                        pkt.v[0].xyz.y = s[0].y + w0;
                        pkt.v[1].xyz.y = s[1].y + w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                    if (j == 1) {
                        pkt.v[0].xyz.y = s[0].y - w0;
                        pkt.v[1].xyz.y = s[1].y - w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                } else {
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                    if (j == 2) {
                        pkt.v[0].xyz.x = s[0].x + w0;
                        pkt.v[1].xyz.x = s[1].x + w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                    if (j == 3) {
                        pkt.v[0].xyz.x = s[0].x - w0;
                        pkt.v[1].xyz.x = s[1].x - w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                }
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                                        ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
                func_00208700(&pkt, o->texture, 1);
                if (func_00101600(&pkt.v[0].xyz) != 0 && func_00101600(&pkt.v[1].xyz) != 0) {
                    if (func_00104520(o->flags, 0x13) != 0) {
                        pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                        func_002075F0(&pkt, ot, 0);
                    } else {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[0].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1]) / 2.0f));
                    }
                }
            }
        }
        o->flags &= 0xFFCFFFFF;
    }
    o->tick++;
    return 0;
}
#pragma optimization_level reset

/* shape b543:01E00C30, 4285 insns, 1 copy (-O3,p): b543 scene manager, b488:01E00080's relative: seven joints, a
   screen blur and a burst at the target (0x90), blade/spark clusters on ten points (0x81), falling streaks (0x50,
   0x64), flashes at the unit, star rings (0x57, 0x6A), a render-to-texture quad (0x3C) and a laser trail from joint 0
   (0x82); returns 1 / 6 / 2 / 8 at 0x86 / 0x91..0xBF / 0xC0 / 0xE1 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b543_01E00C30;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b543_01E00C30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b543_01E00C30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b543_01E00C30 c;
    Uv_b543_01E00C30 uv0;
    Xyz_b543_01E00C30 p0;
    Uv_b543_01E00C30 uv1;
    Xyz_b543_01E00C30 p1;
    u64 pad38;
    u64 txa;
    u64 txb;
    u64 tail;
} Spr_b543_01E00C30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b543_01E00C30 c;
        Uv_b543_01E00C30 uv;
        Xyz_b543_01E00C30 p;
    } v[3];
    u64 pad58;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Tri_b543_01E00C30;

typedef struct {
    Rgbaq_b543_01E00C30 c;
    f32 s, t;
    Xyz_b543_01E00C30 p;
} Tv_b543_01E00C30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Tv_b543_01E00C30 v[4];
    u64 pad70;
    u64 tex0;
    u64 tex1;
    u64 tail;
} Quad_b543_01E00C30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b543_01E00C30 c;
    struct {
        Uv_b543_01E00C30 uv;
        Xyz_b543_01E00C30 p;
    } v[4];
    u8 tail[0x20];
} Spr4_b543_01E00C30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_b543_01E00C30 c;
        Xyz_b543_01E00C30 p;
    } v[2];
    u64 tail;
} Line_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    s32 rot[10];
    Vec4f pos[10];
} Blade_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[10][64];
    u8 pad288[8];
    Vec4f pos[10];
    Vec4f v[10][64];
} Spark_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u16 c[64];
    u8 pad88[8];
    Vec4f pos;
    Vec4f v[64];
    Vec4f w[128];
    u8 c2[64];
    Vec4f v3[64];
} Burst_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 pad8[8];
    Vec4f pos;
    Vec4f v[32];
} Streak_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    u8 c[8];
    Vec4f pos;
    Vec4f v[8];
} Flash_b543_01E00C30;

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 t;
    f32 s;
    u8 padC[4];
    Vec4f pos;
} Ring_b543_01E00C30;

typedef struct {
    s32 tex;
    u8 r, g, b, a;
    s32 flags;
    f32 w;
    s16 rc[8];
    u8 pad20[2];
    s16 k22;
    s16 k24;
    s16 k26;
    s16 k28;
    s16 count;
    s16 k2C;
    u8 pad2E[2];
} Trail_b543_01E00C30;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} TrailPt_b543_01E00C30;

typedef struct {
    s32 t;
    s32 unitA;
    s32 unitB;
    s32 obj;
    s32 tex[4];
    Vec4f tgt;
    Vec4f pos;
    Vec4f scr;
    s32 jn[6];
    u8 pad68[8];
    Vec4f jp[6];
    Vec4f off[6];
    s32 jn2;
    u8 pad134[0xC];
    Vec4f jp2;
    s32 cur;
    u8 pad154[0xC];
    Vec4f grid[8][16][4];
    u8 gc[8][16];
    Blade_b543_01E00C30 blade[1];
    s32 ns;
    u8 pad22B4[0xC];
    Spark_b543_01E00C30 spark[1];
    s32 nb;
    u8 pad4DF4[0xC];
    Burst_b543_01E00C30 burst[1];
    u8 on3;
    u8 pad5EE1[3];
    s32 t3;
    s32 nk;
    u8 pad5EEC[4];
    Streak_b543_01E00C30 streak[32];
    Flash_b543_01E00C30 flash[16];
    Vec4f star[4][4];
    Ring_b543_01E00C30 ring[1][2];
    u8 on4;
    u8 padAE31[3];
    s32 t4;
    u8 padAE38[8];
    u8 cam[0x90];
    u8 cam2[0x70];
    Trail_b543_01E00C30 tr;
    TrailPt_b543_01E00C30 pts[32];
    Vec4f tp;
    u8 kind;
} Scene_b543_01E00C30;

typedef struct {
    f32 m[4][4];
} __attribute__((aligned(16))) Mtx_b543_01E00C30;

#pragma optimization_level 3

static s32 func_01E00C30_b543(s32 arg0, s32 code) {
    Scene_b543_01E00C30 *g = (Scene_b543_01E00C30 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_00100D00(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B480(s32);
    extern void func_00205CA0(void *);
    extern void func_00100E00(void *, s32, s32);
    extern void func_00100E40(void *, void *);
    extern f32 func_00100D50(s32, s32, s32);
    extern s32 func_00101050(s32, s32, s32);
    extern void func_00101080(void *, f32);
    extern void func_00187B18(void *, void *, void *);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B48(void *, void *, f32);
    extern void func_00187B60(void *, void *, void *);
    extern void func_001878E0(void *, void *, void *);
    extern void func_0020CB20(void *, void *);
    extern u64 func_00208D00(s32);
    extern void func_002086D0(void *, u64);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern void func_0020EB40(void *);
    extern void func_0020BBB0(void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00205630(void *, void *, void *, void *, f32 *);
    extern s32 func_002058D0(void *, void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_001F70A0(s32, s32, void *, void *, void *, void *);
    extern f32 func_001A6C48(f32, f32);
    extern void func_001F6D00(s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_00103290(s32 *, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_00104490(void *, void *, s32);
    extern void b543_01E00120();
    extern void b543_01E00270();
    extern void b543_01E04F30();
    extern void b543_01E04FF0();
    extern Vec4f D_28B960[];
    extern u8 D_0030FF00[];
    extern s32 D_01E05100_b543;
    s32 ret;
    s32 ot;
    s32 l;
    s32 b;
    u8 a2;
    s32 buf;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 c;
    s32 n;
    s32 x;
    s32 y;
    s32 ang;
    u8 alpha;
    u8 a3;
    f32 r;
    f32 s;
    f32 h;
    f32 f;
    f32 u0;
    f32 w1;
    f32 w0;
    f32 u1;
    f32 m[4][4];
    f32 m2[4][4];
    f32 m3[4][4];
    Vec4f cn[4];
    Vec4f out[4];
    Mtx_b543_01E00C30 m4;
    Vec4f v;
    Vec4f v2;
    s32 tx[4];
    Line_b543_01E00C30 ln __attribute__((aligned(8)));
    Spr_b543_01E00C30 spr __attribute__((aligned(8)));
    Spr4_b543_01E00C30 spr2 __attribute__((aligned(8)));
    Tri_b543_01E00C30 tri __attribute__((aligned(8)));
    Quad_b543_01E00C30 pk __attribute__((aligned(8)));
    Xyz_b543_01E00C30 xyz;
    f32 depth;

    ret = 0;
    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB190);
        g->t = 0;
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        g->obj = func_00100D00(g->unitA);
        g->tex[0] = func_00202BF0(5, 0);
        g->tex[1] = func_00202BF0(5, 1);
        g->tex[2] = func_00202BF0(5, 2);
        g->tex[3] = func_00202BF0(5, 3);
        func_001F5F90(g->unitB, &g->tgt);
        g->jn[0] = func_001F5560(g->unitA, 5, 1);
        g->jn[1] = func_001F5560(g->unitA, 6, 0);
        g->jn[2] = func_001F5560(g->unitA, 0xF, 0);
        g->jn[3] = func_001F5560(g->unitA, 0xB, 0);
        g->jn[4] = func_001F5560(g->unitA, 0x24, 0);
        g->jn[5] = func_001F5560(g->unitA, 0xC, 0);
        g->jn2 = func_001F5560(g->unitA, 0x28, 0);
        g->cur = j = 0;
        for (n = 0; n < 8; n++) {
            s = -26.7f * (n + 1) / 8.0f;
            f = -1.0f * (-26.7f * n / 7.0f * g->obj);
            h = 11.7f * (8 - (n + 1)) / 7.0f;
            for (i = 0; i < 16; i++) {
                ang = ((i << 16) >> 4) + ((n << 13) >> 3) & 0xFFFF;
                v.x = h * func_0020B550(ang);
                v.y = h * func_0020B480(ang);
                v.z = f;
                v.w = 1.0f;
                func_00100E40(&m4, &v);
                func_00100E00(&m4, (func_0019A5C8() >> 23) % 256 << 16 >> 8, 2);
                g->grid[n][i][0].x = -1.7f;
                g->grid[n][i][0].y = 0.0f;
                g->grid[n][i][0].z = 0.0f;
                g->grid[n][i][0].w = 1.0f;
                g->grid[n][i][1].x = 1.7f;
                g->grid[n][i][1].y = 0.0f;
                g->grid[n][i][1].z = 0.0f;
                g->grid[n][i][1].w = 1.0f;
                g->grid[n][i][2].x = -1.7f;
                g->grid[n][i][2].y = 0.0f;
                g->grid[n][i][2].z = s;
                g->grid[n][i][2].w = 1.0f;
                g->grid[n][i][3].x = 1.7f;
                g->grid[n][i][3].y = 0.0f;
                g->grid[n][i][3].z = s;
                g->grid[n][i][3].w = 1.0f;
                for (k = 0; k < 4; k++) {
                    func_001878E0(&g->grid[n][i][k], &m4, &g->grid[n][i][k]);
                }
                g->gc[n][i] = (func_0019A5C8() >> 23) % 4 + 4;
            }
        }
        for (i = 0; i < 1; i++) {
            g->blade[i].on = 0;
        }
        g->ns = 0;
        for (i = 0; i < 1; i++) {
            g->spark[i].on = 0;
        }
        g->nb = q = 0;
        for (i = 0; i < 1; i++) {
            g->burst[i].on = 0;
        }
        g->on3 = 0;
        g->nk = 0;
        for (i = 0; i < 32; i++) {
            g->streak[i].on = 0;
        }
        for (i = 0; i < 16; i++) {
            g->flash[i].on = 0;
        }
        s = 0.05f;
        for (i = 0; i < 4; i++) {
            h = 2.5f * (1.0f - 0.4f * (i % 2));
            cn[0].x = -s;
            cn[0].y = -h;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = s;
            cn[1].y = -h;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            cn[2].x = -s;
            cn[2].y = h;
            cn[2].z = 0.0f;
            cn[2].w = 1.0f;
            cn[3].x = s;
            cn[3].y = h;
            cn[3].z = 0.0f;
            cn[3].w = 1.0f;
            func_0020BBB0(&m4);
            func_00100E00(&m4, (i << 15) >> 2, 2);
            for (k = 0; k < 4; k++) {
                func_001878E0(&g->star[i][k], &m4, &cn[k]);
            }
        }
        for (i = 0; i < 1; i++) {
            for (k = 0; k < 2; k++) {
                g->ring[i][k].on = 0;
            }
        }
        g->on4 = 0;
        func_00103890(g->cam2);
        func_00103290(tx, 4);
        g->tr.tex = tx[0];
        g->tr.flags = 0x8003;
        g->tr.b = 0x80;
        g->tr.g = 0x80;
        g->tr.r = 0x80;
        g->tr.a = 0x80;
        g->tr.rc[0] = 0x10;
        g->tr.rc[1] = 0;
        g->tr.rc[2] = 0x10;
        g->tr.rc[3] = 0x20;
        g->tr.rc[4] = 0x10;
        g->tr.rc[5] = 0;
        g->tr.rc[6] = 0x80;
        g->tr.rc[7] = 0x40;
        g->tr.w = 60.0f;
        g->tr.k22 = 0x30;
        g->tr.k24 = 0;
        g->tr.k26 = 0x32;
        g->tr.k28 = 0x20;
        g->tr.count = 0;
        g->tr.k2C = 1;
        g->kind = 6;
        return 0;
    }
    func_00205CA0(m3);
    func_001F53C0(1, g->unitA, &g->pos);
    for (k = 0; k < 6; k++) {
        func_001F5620(g->unitA, g->jn[k], &g->jp[k]);
    }
    func_001F5620(g->unitA, g->jn2, &g->jp2);
    g->off[0].x = 3.8f;
    g->off[0].y = 0.0f;
    g->off[0].z = 0.0f;
    g->off[0].w = 1.0f;
    g->off[1].x = -3.8f;
    g->off[1].y = 0.0f;
    g->off[1].z = 0.0f;
    g->off[1].w = 1.0f;
    g->off[2].x = 2.0f;
    g->off[2].y = 1.6f;
    g->off[2].z = 0.0f;
    g->off[2].w = 1.0f;
    g->off[3].x = -2.0f;
    g->off[3].y = 1.6f;
    g->off[3].z = 0.0f;
    g->off[3].w = 1.0f;
    g->off[4].x = 2.0f;
    g->off[4].y = -1.6f;
    g->off[4].z = 0.0f;
    g->off[4].w = 1.0f;
    g->off[5].x = -2.0f;
    g->off[5].y = -1.6f;
    g->off[5].z = 0.0f;
    g->off[5].w = 1.0f;
    for (k = 0; k < 6; k++) {
        func_00187B00(&g->off[k], &g->off[k], &g->jp[0]);
    }
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    func_00205440(&g->tgt, m, &xyz, &depth);
    g->scr.x = (s32)(xyz.x >> 4) - 0x6C0;
    g->scr.y = (s32)(xyz.y >> 4) - 0x720;
    g->scr.z = func_0017B340(xyz.z);
    g->scr.w = 1.0f;
    if (g->scr.x < 0.0f) {
        g->scr.x = 0.0f;
    }
    if (g->scr.x > 640.0f) {
        g->scr.x = 640.0f;
    }
    if (g->scr.y < 0.0f) {
        g->scr.y = 0.0f;
    }
    if (g->scr.y > 448.0f) {
        g->scr.y = 448.0f;
    }

    if (g->t == 0x90) {
        g->on3 = 1;
        g->t3 = 0;
    }
    if (g->on3 == 1) {
        ((Tri_b543_01E00C30 *)(s32)&tri)->flags = 0x33;
        ((Tri_b543_01E00C30 *)(s32)&tri)->size = 9;
        ((Tri_b543_01E00C30 *)(s32)&tri)->regs = ((u64)4 << 32) | 0x21421421;
        ((Tri_b543_01E00C30 *)(s32)&tri)->pad4 = 0;
        ((Tri_b543_01E00C30 *)(s32)&tri)->flags |= 0x800;
        func_002086D0(&tri, func_00208D00(0));
        func_00208CB0(&tri, ((u64)0x700 << 32) | 0xA0000A);
        buf = func_00207F60();
        func_00208460();
        func_00208800(func_00209E50(), 1, &tri.tex0, &tri.tex1);
        func_00208460();
        alpha = (0x30 - g->t3) * 0x40 / 48;
        tri.v[0].c.r = 0x80;
        tri.v[0].c.g = 0x80;
        tri.v[0].c.b = 0x80;
        tri.v[0].c.a = alpha;
        tri.v[0].c.q = 1.0f;
        tri.v[1].c = tri.v[0].c;
        tri.v[2].c = tri.v[0].c;
        for (j = 0; j < 8; j++) {
            r = 1.0f + 0.15f * (8 - j) / 8.0f;
            for (i = 0; i < 8; i++) {
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[0].uv)->u = x << 4;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[0].uv)->v = y << 4;
                x = (s32)D_28B960[i].x;
                y = (s32)D_28B960[i].y;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[1].uv)->u = x << 4;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[1].uv)->v = y << 4;
                x = (s32)D_28B960[i + 1].x;
                y = (s32)D_28B960[i + 1].y;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[2].uv)->u = x << 4;
                ((Uv_b543_01E00C30 *)(s32)&tri.v[2].uv)->v = y << 4;
                func_00187B18((void *)&out[0], &D_28B960[i], (void *)&g->scr);
                func_00187B18(&out[1], &D_28B960[i + 1], &g->scr);
                func_00187B48(&out[0], &out[0], r);
                func_00187B48(&out[1], &out[1], r);
                func_00187B00(&out[0], &out[0], &g->scr);
                func_00187B00(&out[1], &out[1], &g->scr);
                x = (s32)g->scr.x;
                y = (s32)g->scr.y;
                tri.v[0].p.x = (x + 0x6C0) << 4;
                tri.v[0].p.y = (y + 0x720) << 4;
                tri.v[0].p.z = 0xFFFFF8;
                tri.v[0].p.f = 0;
                x = (s32)out[0].x;
                y = (s32)out[0].y;
                tri.v[1].p.x = (x + 0x6C0) << 4;
                tri.v[1].p.y = (y + 0x720) << 4;
                tri.v[1].p.z = 0xFFFFF8;
                tri.v[1].p.f = 0;
                x = (s32)out[1].x;
                y = (s32)out[1].y;
                tri.v[2].p.x = (x + 0x6C0) << 4;
                tri.v[2].p.y = (y + 0x720) << 4;
                tri.v[2].p.z = 0xFFFFF8;
                tri.v[2].p.f = 0;
                func_002075F0(&tri, 0, 0);
            }
        }
        func_00207FD0(buf, ot, 0);
        g->t3++;
        if (g->t3 > 48) {
            g->on3 = 0;
        }
    }

    if (g->t == 0x81) {
        i = g->cur;
        (void)i;
        g->blade[i].on = 1;
        g->blade[i].t = 0;
        c = g->ns;
        (void)c;
        g->spark[c].on = 1;
        g->spark[c].t = 0;
        for (j = 0; j < 10; j++) {
            switch (j) {
            case 0:
                v = g->jp[1];
                break;
            case 1:
                v = g->jp[2];
                break;
            case 2:
                v = g->jp[3];
                break;
            case 3:
                v = g->jp[4];
                break;
            case 4:
                v = g->off[0];
                break;
            case 5:
                v = g->off[1];
                break;
            case 6:
                v = g->off[2];
                break;
            case 7:
                v = g->off[3];
                break;
            case 8:
                v = g->off[4];
                break;
            case 9:
                v = g->off[5];
                break;
            }
            g->blade[i].rot[j] = (func_0019A5C8() >> 23) % 256 << 16 >> 8;
            g->blade[i].pos[j] = v;
            g->spark[c].pos[j] = v;
            for (n = 0; n < 64; n++) {
                g->spark[c].c[j][n] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->spark[c].v[j][n], 0.7f);
            }
        }
        g->cur++;
        if (g->cur >= 1) {
            g->cur = 0;
        }
        g->ns++;
        if (g->ns >= 1) {
            g->ns = l = 0;
        }
    }

    ((Quad_b543_01E00C30 *)(s32)&pk)->flags = 0x34;
    ((Quad_b543_01E00C30 *)(s32)&pk)->size = 0xC;
    ((Quad_b543_01E00C30 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Quad_b543_01E00C30 *)(s32)&pk)->pad4 = 0;
    func_00208700(&pk, g->tex[1], 1);
    func_002086D0(&pk, func_00208D00(1));
    func_00208CB0(&pk, 0);
    for (j = 0; j < 1; j++) {
        if (g->blade[j].on == 0) {
            continue;
        }
        alpha = (10 - g->blade[j].t) * 0x56 / 10;
        pk.v[0].c.r = 0x30;
        pk.v[0].c.g = 0x40;
        pk.v[0].c.b = 0xFF;
        pk.v[0].c.a = alpha;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        if (j < 4) {
            f = 1.5f;
        } else {
            f = 1.0f;
        }
        s = (0.5f + 0.5f * g->blade[j].t / 10.0f) * f;
        v.x = s;
        v.y = s;
        v.z = s;
        v.w = 1.0f;
        for (b = 0; b < 10; b++) {
            func_0020EB40(m);
            func_0020BBB0(m2);
            func_00187B60(m2, m2, &g->blade[j].pos[b]);
            func_00100E00(m2, 0, 0);
            func_00100E00(m2, g->blade[j].rot[b], 2);
            func_0020CB20(m2, &v);
            func_0020BC00(m, m2);
            for (q = 0; q < 8; q++) {
                for (c = 0; c < 16; c++) {
                    n = g->gc[q][c];
                    x = n % 4 * 32;
                    y = (n >> 2) * 32;
                    u0 = x / 128.0f;
                    u1 = (32.0f + x) / 128.0f;
                    w1 = y / 64.0f;
                    w0 = (16.0f + y) / 64.0f;
                    pk.v[0].s = u0;
                    pk.v[0].t = w0;
                    pk.v[1].s = u1;
                    pk.v[1].t = w0;
                    pk.v[2].s = u0;
                    pk.v[2].t = w1;
                    pk.v[3].s = u1;
                    pk.v[3].t = w1;
                    if (func_002058D0(&g->grid[q][c][0], D_0030FF00, m, &pk, &depth) == 1) {
                        func_002075F0(&pk, ot, (u32)depth);
                    }
                }
            }
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 70.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        alpha = (u32)(100.0f * (1.0f - func_00100D50(g->blade[j].t, 10, 1)));
        (void)alpha;
        spr.c.r = 0x32;
        spr.c.g = 0x6A;
        spr.c.b = 0xFF;
        spr.c.a = alpha;
        spr.c.q = 1.0f;
        for (i = 0; i < 10; i++) {
            v = g->blade[j].pos[i];
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = 96;
            y = 0;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        g->blade[j].t++;
        if (g->blade[j].t > 10) {
            g->blade[j].on = 0;
        }
    }

    ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
    ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
    ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
    ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
    func_00208700(&spr, g->tex[0], 1);
    func_00208CB0(&spr, 5);
    func_002086D0(&spr, func_00208D00(0));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 1; j++) {
        if (g->spark[j].on == 0) {
            continue;
        }
        r = 3.3f * (0.5f + 0.5f * g->spark[j].t / 32.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        a3 = (0x20 - g->spark[j].t) * 0x40 >> 5;
        spr.c.r = 0xBC;
        spr.c.g = 0xBC;
        spr.c.b = 0xBC;
        spr.c.a = a3;
        spr.c.q = 1.0f;
        s = func_00100D50(g->spark[j].t, 0x20, 1);
        for (q = 0; q < 10; q++) {
            for (k = 0; k < 64; k++) {
                func_00187B48(&v, &g->spark[j].v[q][k], s);
                func_00187B00(&v, &v, &g->spark[j].pos[q]);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                x = g->spark[j].c[q][k] % 4 * 32;
                y = (g->spark[j].c[q][k] >> 2) * 32;
                ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = x << 4;
                ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = y << 4;
                ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = (x + 32) << 4;
                ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = (y + 32) << 4;
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->spark[j].t++;
        if (g->spark[j].t > 32) {
            g->spark[j].on = 0;
        }
    }

    if (g->t == 0x90) {
        for (q = 0; q < 1; q++) {
            g->nb = q;
            g->burst[g->nb].on = 1;
            g->burst[g->nb].t = 1;
            g->burst[g->nb].pos.x = 0.0f;
            g->burst[g->nb].pos.y = 0.0f;
            g->burst[g->nb].pos.z = 0.0f;
            g->burst[g->nb].pos.w = 1.0f;
            func_00187B00(&g->burst[g->nb].pos, &g->burst[g->nb].pos, &g->tgt);
            for (i = 0; i < 64; i++) {
                g->burst[g->nb].c[i] = (func_0019A5C8() >> 23) % 8;
                func_00101080(&g->burst[g->nb].v[i], 2.7f);
            }
            for (i = 0; i < 128; i++) {
                func_00101080(&g->burst[g->nb].w[i], 3.75f);
            }
            for (i = 0; i < 64; i++) {
                g->burst[g->nb].c2[i] = (func_0019A5C8() >> 23) % 3 + 5;
                func_00101080(&g->burst[g->nb].v3[i], 2.7f);
            }
        }
    }

    for (j = 0; j < 1; j++) {
        if (g->burst[j].on == 0) {
            continue;
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[2], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 18.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        /* a fade with its strength set to 0: a plain 0 would be propagated into the loop */
        a3 = (0x30 - g->burst[j].t) * 0 / 48;
        spr.c.r = 0x38;
        spr.c.g = 0x6C;
        spr.c.b = 0xFF;
        spr.c.a = a3;
        spr.c.q = 1.0f;
        s = func_00100D50(g->burst[j].t, 0x30, 1);
        for (k = 0; k < 64; k++) {
            func_00187B48(&v, &g->burst[j].v3[k], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c2[k] % 4 * 32;
            y = (g->burst[j].c2[k] >> 2) * 32;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 15.0f * (0.8f + 0.2f * g->burst[j].t / 48.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        a3 = (0x30 - g->burst[j].t) * 0 / 48;
        a2 = (0x30 - g->burst[j].t) * 0 / 48;
        for (k = 0; k < 64; k++) {
            s = func_00100D50(g->burst[j].t, 0x30, 1);
            if (k % 2 == 0) {
                s *= 0.8f;
                func_002086D0(&spr, func_00208D00(2));
                spr.c.r = 0x80;
                spr.c.g = 0xFF;
                spr.c.b = 0xFF;
                spr.c.a = a2;
                spr.c.q = 1.0f;
            } else {
                func_002086D0(&spr, func_00208D00(1));
                spr.c.r = 0x1E;
                spr.c.g = 0x5A;
                spr.c.b = 0xFF;
                spr.c.a = a3;
                spr.c.q = 1.0f;
            }
            func_00187B48(&v, &g->burst[j].v[k], s);
            func_00187B00(&v, &v, &g->burst[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            x = g->burst[j].c[k] % 4 * 32;
            y = (g->burst[j].c[k] >> 2) * 32;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        func_0020EB40(m);
        func_00187B60(m2, m3, &g->burst[j].pos);
        f = 0.2f + 0.8f * func_00100D50(g->burst[j].t, 0x30, 1);
        v.x = f;
        v.y = f;
        v.z = f;
        v.w = 1.0f;
        func_0020CB20(m2, &v);
        func_0020BC00(m, m2);
        a3 = (u32)(200.0f * ((0x30 - g->burst[j].t) / 48.0f));
        (void)a3;
        spr.c.r = 0x3A;
        spr.c.g = 0x5E;
        spr.c.b = 0xFF;
        spr.c.a = a3;
        spr.c.q = 1.0f;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = 0x200;
        r = 195.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        if (func_00205630(cn, D_0030FF00, m, &spr, &depth) == 1) {
            spr.p0.z = 0xFFFFF8;
            spr.p1.z = spr.p0.z;
            func_002075F0(&spr, ot, 0);
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[1], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(1));
        ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = 0x600;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = 0;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = 0x800;
        ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = 0x200;
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 1.0f;
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        h = (0x30 - g->burst[j].t) / 48.0f;
        f = func_00100D50(g->burst[j].t, 0x30, 1);
        for (l = 0; l < 128; l++) {
            for (q = 0; q < 6; q++) {
                a3 = (u32)(h * ((q + 6) * 0xFF / 12));
                (void)a3;
                spr.c.r = 0x80;
                spr.c.g = 0xF0;
                spr.c.b = 0xFF;
                spr.c.a = a3;
                spr.c.q = 1.0f;
                func_00187B48(&v, &g->burst[j].w[l], f + 0.007f * q);
                func_00187B00(&v, &v, &g->burst[j].pos);
                func_00187B00(&out[0], &cn[0], &v);
                func_00187B00(&out[1], &cn[1], (void *)&v);
                if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                    func_002075F0(&spr, ot, (u32)depth);
                }
            }
        }
        g->burst[j].t++;
        if (g->burst[j].t > 0x30) {
            g->burst[j].on = 0;
        }
    }

    n = -1;
    if (g->t > 0x4F && g->t < 0x5B) {
        n = 0;
        v = g->jp[5];
    }
    if (g->t > 0x63 && g->t < 0x6E) {
        n = 1;
        v = g->jp[0];
    }
    if (n >= 0) {
        i = g->nk;
        (void)i;
        g->streak[i].on = 1;
        g->streak[i].t = 0;
        g->streak[i].pos = v;
        for (k = 0; k < 32; k++) {
            func_00101080(&g->streak[i].v[k], 0.2f);
        }
        g->nk++;
        if (g->nk >= 32) {
            g->nk = 0;
        }
    }

    ((Line_b543_01E00C30 *)(s32)&ln)->flags = 0x11;
    ((Line_b543_01E00C30 *)(s32)&ln)->size = 4;
    ((Line_b543_01E00C30 *)(s32)&ln)->regs = 0x4141;
    ((Line_b543_01E00C30 *)(s32)&ln)->pad4 = 0;
    func_002086D0(&ln, func_00208D00(1));
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 32; j++) {
        if (g->streak[j].on == 0) {
            continue;
        }
        h = (8 - g->streak[j].t) / 8.0f;
        f = g->streak[j].t / 8.0f;
        for (k = 0; k < 32; k++) {
            for (q = 0; q < 4; q++) {
                if (q == 0) {
                    a3 = (u32)(h * (255.0f * func_0020B550((q << 14) >> 2)));
                    (void)a3;
                    ln.v[0].c.r = 0xFF;
                    ln.v[0].c.g = 0x78;
                    ln.v[0].c.b = 0x1E;
                    ln.v[0].c.a = a3;
                    ln.v[0].c.q = 1.0f;
                    a2 = (u32)(h * (255.0f * func_0020B550(((q + 1) << 14) >> 2)));
                    ln.v[1].c.r = 0xFF;
                    ln.v[1].c.g = 0x78;
                    ln.v[1].c.b = 0x1E;
                    ln.v[1].c.a = a2;
                    ln.v[1].c.q = 1.0f;
                    s = f + 0.05f * q;
                    func_00187B48(&v, &g->streak[j].v[k], s);
                    func_00187B00(&v, &v, &g->streak[j].pos);
                    v.y += 250.0f * (0.5f * (-0.0108962776f * func_001A6C48(s, 2.0f)));
                    s = f + 0.05f * (q + 1);
                    func_00187B48(&v2, &g->streak[j].v[k], s);
                    func_00187B00(&v2, &v2, &g->streak[j].pos);
                    v2.y += 250.0f * (0.5f * (-0.0108962776f * func_001A6C48(s, 2.0f)));
                } else {
                    ln.v[0].c.r = 0xFF;
                    ln.v[0].c.g = 0x78;
                    ln.v[0].c.b = 0x1E;
                    ln.v[0].c.a = a2;
                    ln.v[0].c.q = 1.0f;
                    a2 = (u32)(h * (255.0f * func_0020B550(((q + 1) << 14) >> 2)));
                    ln.v[1].c.r = 0xFF;
                    ln.v[1].c.g = 0x78;
                    ln.v[1].c.b = 0x1E;
                    ln.v[1].c.a = a2;
                    ln.v[1].c.q = 1.0f;
                    v = v2;
                    s = f + 0.05f * (q + 1);
                    func_00187B48(&v2, &g->streak[j].v[k], s);
                    func_00187B00(&v2, &v2, &g->streak[j].pos);
                    v2.y += 250.0f * (0.5f * (-0.0108962776f * func_001A6C48(s, 2.0f)));
                }
                out[0] = v;
                out[1] = v2;
                if (func_00205630(out, D_0030FF00, m, &ln, &depth) == 1) {
                    func_002075F0(&ln, ot, (u32)depth);
                }
            }
        }
        g->streak[j].t++;
        if (g->streak[j].t > 8) {
            g->streak[j].on = 0;
        }
    }

    if (g->t > 0 && g->t < 0x35) {
        n = g->t % 16;
        g->flash[n].on = 1;
        g->flash[n].t = 0;
        g->flash[n].pos = g->pos;
        g->flash[n].pos.y += -5.0f;
        for (k = 0; k < 8; k++) {
            g->flash[n].c[k] = (func_0019A5C8() >> 23) % 8;
            func_00101080(&g->flash[n].v[k], 0.7f);
            g->flash[n].v[k].y *= 0.7f;
        }
    }
    for (j = 0; j < 16; j++) {
        if (g->flash[j].on == 0) {
            continue;
        }
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
        ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
        ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
        ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
        ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
        func_00208700(&spr, g->tex[0], 1);
        func_00208CB0(&spr, 5);
        func_002086D0(&spr, func_00208D00(0));
        func_0020EB40(m);
        func_0020BBB0(m2);
        func_0020BC00(m, m2);
        r = 5.0f * (0.5f + 0.5f * g->flash[j].t / 16.0f);
        cn[0].x = -r;
        cn[0].y = -r;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = r;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        func_001878E0(&cn[0], m3, &cn[0]);
        func_001878E0(&cn[1], m3, &cn[1]);
        a3 = (0x10 - g->flash[j].t) * 0x40 >> 4;
        spr.c.r = 0xFF;
        spr.c.g = 0xFF;
        spr.c.b = 0xFF;
        spr.c.a = a3;
        spr.c.q = 1.0f;
        s = 0.1f + 0.9f * func_00100D50(g->flash[j].t, 0x10, 1);
        for (k = 0; k < 8; k++) {
            x = g->flash[j].c[k] % 4 * 32;
            y = (g->flash[j].c[k] >> 2) * 32;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = x << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = y << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = (x + 32) << 4;
            ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = (y + 32) << 4;
            func_00187B48(&v, &g->flash[j].v[k], s);
            func_00187B00(&v, &v, &g->flash[j].pos);
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                func_002075F0(&spr, ot, (u32)depth);
            }
        }
        g->flash[j].t++;
        if (g->flash[j].t > 16) {
            g->flash[j].on = 0;
        }
    }

    n = -1;
    switch (g->t) {
    case 0x57:
        n = 0;
        v = g->jp[2];
        break;
    case 0x6A:
        n = 1;
        v = g->jp[1];
        break;
    }
    if (n >= 0) {
        g->ring[0][n].on = 1;
        g->ring[0][n].t = 0;
        g->ring[0][n].s = 1.0f;
        g->ring[0][n].pos = v;
    }

    ((Spr4_b543_01E00C30 *)(s32)&spr2)->flags = 0x24;
    ((Spr4_b543_01E00C30 *)(s32)&spr2)->size = 9;
    ((Spr4_b543_01E00C30 *)(s32)&spr2)->regs = ((u64)4 << 32) | 0x24242421;
    ((Spr4_b543_01E00C30 *)(s32)&spr2)->pad4 = 0;
    ((Spr4_b543_01E00C30 *)(s32)&spr2)->flags |= 0x800;
    func_002086D0(&spr2, func_00208D00(1));
    func_00208700(&spr2, g->tex[1], 1);
    func_00208CB0(&spr2, 5);
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[0].uv)->u = 0;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[0].uv)->v = 0x200;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[1].uv)->u = 0x200;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[1].uv)->v = 0x200;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[2].uv)->u = 0;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[2].uv)->v = 0x400;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[3].uv)->u = 0x200;
    ((Uv_b543_01E00C30 *)(s32)&spr2.v[3].uv)->v = 0x400;
    ((Spr_b543_01E00C30 *)(s32)&spr)->flags = 0x26;
    ((Spr_b543_01E00C30 *)(s32)&spr)->size = 5;
    ((Spr_b543_01E00C30 *)(s32)&spr)->regs = 0x42421;
    ((Spr_b543_01E00C30 *)(s32)&spr)->pad4 = 0;
    ((Spr_b543_01E00C30 *)(s32)&spr)->flags |= 0x800;
    func_002086D0(&spr, func_00208D00(1));
    func_00208700(&spr, g->tex[1], 1);
    func_00208CB0(&spr, 5);
    ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->u = 0x600;
    ((Uv_b543_01E00C30 *)(s32)&spr.uv0)->v = 0;
    ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->u = 0x800;
    ((Uv_b543_01E00C30 *)(s32)&spr.uv1)->v = 0x200;
    func_0020EB40(m);
    func_0020BBB0(m2);
    func_0020BC00(m, m2);
    for (j = 0; j < 1; j++) {
        for (c = 0; c < 2; c++) {
            if (g->ring[j][c].on == 0) {
                continue;
            }
            a3 = (u32)(255.0f * func_0020B480((g->ring[j][c].t << 14) >> 3));
            (void)a3;
            spr2.c.r = 0xFF;
            spr2.c.g = 0xE8;
            spr2.c.b = 0xD8;
            spr2.c.a = a3;
            spr2.c.q = 1.0f;
            s = g->ring[j][c].s;
            for (k = 0; k < 4; k++) {
                for (l = 0; l < 4; l++) {
                    func_00187B48(&cn[l], &g->star[k][l], s);
                    func_001878E0(&cn[l], m3, &cn[l]);
                    func_00187B00(&out[l], &cn[l], &g->ring[j][c].pos);
                }
                if (func_00205630(out, D_0030FF00, m, &spr2, &depth) == 1) {
                    spr2.v[0].p.z = 0xFFFFF8;
                    spr2.v[1].p.z = spr2.v[0].p.z;
                    spr2.v[2].p.z = spr2.v[0].p.z;
                    spr2.v[3].p.z = spr2.v[0].p.z;
                    func_002075F0(&spr2, ot, 0);
                }
            }
            r = 1.5f * g->ring[j][c].s;
            cn[0].x = -r;
            cn[0].y = -r;
            cn[0].z = 0.0f;
            cn[0].w = 1.0f;
            cn[1].x = r;
            cn[1].y = r;
            cn[1].z = 0.0f;
            cn[1].w = 1.0f;
            func_001878E0(&cn[0], m3, &cn[0]);
            func_001878E0(&cn[1], m3, &cn[1]);
            a3 = (u32)(255.0f * func_0020B480((g->ring[j][c].t << 14) >> 3));
            (void)a3;
            spr.c.r = 0xFF;
            spr.c.g = 0xE8;
            spr.c.b = 0xD8;
            spr.c.a = a3;
            spr.c.q = 1.0f;
            v = g->ring[j][c].pos;
            func_00187B00(&out[0], &cn[0], &v);
            func_00187B00(&out[1], &cn[1], (void *)&v);
            if (func_00205630(out, D_0030FF00, m, &spr, &depth) == 1) {
                spr.p0.z = 0xFFFFF8;
                spr.p1.z = spr.p0.z;
                func_002075F0(&spr, ot, 0);
            }
            g->ring[j][c].t++;
            if (g->ring[j][c].t > 8) {
                g->ring[j][c].on = 0;
            }
        }
    }

    if (g->t == 0x3C) {
        g->on4 = 1;
        g->t4 = 0;
    }
    if (g->on4 == 1) {
        ((Quad_b543_01E00C30 *)(s32)&pk)->flags = 0x34;
        ((Quad_b543_01E00C30 *)(s32)&pk)->size = 0xC;
        ((Quad_b543_01E00C30 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Quad_b543_01E00C30 *)(s32)&pk)->pad4 = 0;
        r = 1.5f * g->obj;
        cn[0].x = -r;
        cn[0].y = 1.05f;
        cn[0].z = 0.0f;
        cn[0].w = 1.0f;
        cn[1].x = r;
        cn[1].y = 1.05f;
        cn[1].z = 0.0f;
        cn[1].w = 1.0f;
        cn[2].x = -r;
        cn[2].y = -1.05f;
        cn[2].z = 0.0f;
        cn[2].w = 1.0f;
        cn[3].x = r;
        cn[3].y = -1.05f;
        cn[3].z = 0.0f;
        cn[3].w = 1.0f;
        func_0020EB40(m);
        func_0020BBB0(m2);
        v = g->jp2;
        v.z += -1.0f * g->obj;
        func_00187B60(m2, m2, &v);
        func_0020BC00(m, m2);
        func_002086D0(&pk, func_00208D00(1));
        func_00208700(&pk, g->tex[3], 1);
        func_00208CB0(&pk, 5);
        pk.v[0].s = 1.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 0.0f;
        pk.v[1].t = 0.0f;
        pk.v[2].s = 1.0f;
        pk.v[2].t = 1.0f;
        pk.v[3].s = 0.0f;
        pk.v[3].t = 1.0f;
        a3 = (u32)(128.0f * (0.5f + 0.5f * (g->t4 % 2)) / 3.0f);
        (void)a3;
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = a3;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
            func_002075F0(&pk, ot, 0);
        }
        buf = func_00207F60();
        func_00208460();
        D_01E05100_b543 = (s32)g;
        func_001F70A0(g->unitB, 1, &pk.tex0, &pk.tex1, b543_01E04F30, b543_01E04FF0);
        func_00208460();
        func_002086D0(&pk, func_00208D00(0));
        func_00208CB0(&pk, ((u64)0x700 << 32) | 0xA0000A);
        a3 = (u32)(128.0f * (0.5f + 0.5f * (g->t4 % 2)));
        (void)a3;
        pk.v[0].c.r = 0x80;
        pk.v[0].c.g = 0x80;
        pk.v[0].c.b = 0x80;
        pk.v[0].c.a = a3;
        pk.v[0].c.q = 1.0f;
        pk.v[1].c = pk.v[0].c;
        pk.v[2].c = pk.v[0].c;
        pk.v[3].c = pk.v[0].c;
        pk.v[0].s = 0.0f;
        pk.v[0].t = 0.0f;
        pk.v[1].s = 0.625f;
        pk.v[1].t = 0.0f;
        pk.v[2].s = 0.0f;
        pk.v[2].t = 0.875f;
        pk.v[3].s = 0.625f;
        pk.v[3].t = 0.875f;
        if (func_002058D0(cn, D_0030FF00, m, &pk, &depth) == 1) {
            func_002075F0(&pk, 0, 0);
        }
        func_00207FD0(buf, ot, 0);
        g->t4++;
        if (g->t4 > 20) {
            g->on4 = 0;
        }
    }

    if (g->t == 0x82) {
        func_001F5620(func_001F53A0(), g->jn[0], &g->tp);
    }
    if (g->t >= 0x82) {
        b543_01E00120(&g->tr, g->pts, &g->tp);
        func_00104490(&g->tp, &g->tgt, g->kind);
    }
    func_001038D0(g->cam2);
    if (g->t >= 0x82) {
        b543_01E00270(ot, &g->tr, g->pts, g->cam2);
        for (i = 0; i < g->tr.count; i++) {
            func_00103470(&g->pts[i].c, 0, 5);
        }
    }

    func_001F6D00((u8)((func_00101050(0xE0 - g->t, 0, 32) * (func_00101050(g->t, 0, 32) * -80) >> 10) + 0x80));
    if (g->t == 0x86) {
        ret = 1;
    } else {
        if (g->t > 0x90 && g->t < 0xC0) {
            ret = 6;
        }
        if (g->t == 0xC0) {
            ret = 2;
        }
    }
    g->t++;
    if (g->t > 0xE0) {
        ret = 8;
    }
    return ret;
}

#pragma optimization_level reset

/* shape b543:01E04F30, 45 insns: refresh the scene's camera (0xAE40, func_0020DEF0), copy it, aim the copy along
   (0, 50, 0) / (0, 0, -c) with c the scene's s32 at 0xC, load it (func_0020E360) and func_0020EC60(arg) */

typedef struct {
    f32 m[16];
    Vec4f a;
    Vec4f b;
    __int128 pad60[3];
} Cam_b543_01E04F30;

typedef struct {
    u8 pad0[0xC];
    s32 c;
    u8 pad10[0xAE40 - 0x10];
    Cam_b543_01E04F30 cam;
} Scene_b543_01E04F30;

extern Scene_b543_01E04F30 *D_01E05100_b543;

static void func_01E04F30_b543(s32 arg) {
    Scene_b543_01E04F30 *s;
    Cam_b543_01E04F30 cam;

    s = D_01E05100_b543;
    func_0020DEF0(&s->cam);
    cam = s->cam;
    cam.a.x = 0.0f;
    cam.a.y = 50.0f;
    cam.a.z = 0.0f;
    cam.a.w = 1.0f;
    cam.b.x = 0.0f;
    cam.b.y = 0.0f;
    cam.b.z = -1.0f * s->c;
    cam.b.w = 1.0f;
    func_0020E360(&cam);
    func_0020EC60(arg);
}

/* shape b543:01E04FF0, 15 insns, 1 copy: load the scene's own camera as the view (unchanged, unlike
   func_01E04F30_b543's) and pass the packet on (func_0020EC60) */

static void func_01E04FF0_b543(s32 arg) {
    func_0020E360(&D_01E05100_b543->cam);
    func_0020EC60(arg);
}
