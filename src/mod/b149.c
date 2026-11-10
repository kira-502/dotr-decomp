#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b149(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b149(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
} Obj_b082_01E00920;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0x0E];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b082_01E00920;

static void func_01E009B0_b149(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
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

static void func_01E00E10_b149(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b149_01E00110();
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
    b149_01E00110(p, obj->f94, obj->fC0);
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

/* shape b149:01E01360, 258 insns: b615:01E01880 family scene timer step: from 36 to 70, twice a frame, place the
   scene at model point 0xBCBE (odd frames) or 0xBCC0, jitter x/z by +-20 and start the module's b149:01E01770 in
   the next slot (0..119); from 36 to 100, twice a frame, two b149:01E01C60 bursts around the scene point and model
   point 0xBCBC, jittered by +-10 per axis, through b149:01E02BA0 */

typedef struct Scn_b149_01E01360 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xBCBC - 0x25C];
    s16 pc;
    s16 pa;
    s16 pb;
    u8 padBCC2[0x28];
    s16 cur;
    s16 next;
    u8 padBCEE[4];
    s16 count;
} Scn_b149_01E01360;

static void func_01E01360_b149(Scn_b149_01E01360 *g) {
    extern s32 func_001F53A0();
    extern void func_001F5620();
    extern u8 b149_01E01770[];
    extern u8 b149_01E01C60[];
    extern void b149_01E02BA0(Scn_b149_01E01360 *w, void *data, s32 arg);
    s16 i;
    s16 n;

    g->count++;
    if (g->count >= 36 && g->count < 71 && g->count != 0) {
        if (g->count < 100) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            if (g->count % 2 == 1) {
                func_001F5620(func_001F53A0(), g->pa, g->pos);
            } else {
                func_001F5620(func_001F53A0(), g->pb, g->pos);
            }
            g->pos[0] += func_0019A5C8() % 40 - 20;
            g->pos[2] += func_0019A5C8() % 40 - 20;
            g->cur = g->next;
            b149_01E02BA0(g, b149_01E01770, 0);
            g->next++;
            if (g->next >= 0x78) {
                g->next = 0;
            }
        }
    }
    if (g->count >= 36 && g->count < 101) {
        if (g->count < 100) {
            i = 2;
        } else {
            i = 2;
        }
        for (n = 0; n < i; n++) {
            g->pos[0] += func_0019A5C8() % 20 - 10;
            g->pos[1] += func_0019A5C8() % 20 - 10;
            g->pos[2] += func_0019A5C8() % 20 - 10;
            b149_01E02BA0(g, b149_01E01C60, 0);
            func_001F5620(func_001F53A0(), g->pc, g->pos);
            g->pos[0] += func_0019A5C8() % 20 - 10;
            g->pos[1] += func_0019A5C8() % 20 - 10;
            g->pos[2] += func_0019A5C8() % 20 - 10;
            b149_01E02BA0(g, b149_01E01C60, 0);
        }
    }
}

/* shape b149:01E01770, 211 insns: b149:01E01C60 cousin (size 10, alpha up for 80 ticks); from tick 31 to 69 it is
   pushed 4.7 a tick in z by the scene side (0xBCEE), sinks 1.1 and grows 0.5; from tick 71 it turns 5, rises by hE
   and grows 3. As b149:01E01C60: b479:01E01EB0 variant: size 20, a drift of -1.5..1.4 a tick in y, height 10..29
   growing by 15 (and the drift) for 12 ticks up to its limit 100..249, rise 40..79; on tick 72 it hands its position to the scene
   (m+0x250) and fires the module's 0x1E01AC0 effect; h5C turns by 7 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad260[0xBCEE - 0x260];
    s16 side;
} Mgr_b149_01E01770;

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
} Obj_b149_01E01770;

static s32 func_01E01770_b149(Mgr_b149_01E01770 *m, Obj_b149_01E01770 *o) {
    extern void b149_01E01AC0();
    extern void b149_01E02BA0(Mgr_b149_01E01770 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->f34 = func_0019A5C8() % 30 - 15;
        o->f34 /= 10.0f;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h52 = func_0019A5C8() % 150 + 100;
        o->hE = func_0019A5C8() % 40 + 40;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 80) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 == 72) {
        m->pos = o->pos;
        b149_01E02BA0(m, b149_01E01AC0, 0);
    }
    if (o->h54 < 12) {
        if (o->h50 < o->h52) {
            o->h50 += 15;
        }
        o->pos.y += o->f34;
    }
    o->h5C += 7;
    if (o->h54 > 30 && o->h54 < 70) {
        if (m->side != 0) {
            o->pos.z -= 4.7f;
        } else {
            o->pos.z += 4.7f;
        }
        o->pos.y -= 1.1f;
        o->f48 += 0.5f;
    }
    if (o->h54 > 70) {
        o->h5A += 5;
        o->h50 += o->hE;
        o->f48 += 3.0f;
    }
    o->h54++;
    return 0;
}

/* shape b149:01E01AC0, 102 insns: a grey spark (b203:01E027D0 shape): size 40, random sub-frame 0..3, angle, frame 0..7,
   start height 10..59 (old one kept), rise 16..45 once started, width 0..34, hold 3..7; full alpha until the hold, then down by 8 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 frame;
    s16 y0;
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
} Obj_b149_01E01AC0;

static s32 func_01E01AC0_b149(void *arg0, Obj_b149_01E01AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 40.0f;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 8;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 50 + 0xA;
        o->step = func_0019A5C8() % 30 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b149:01E01C60, 156 insns: b479:01E01EB0 variant: size 20, a drift of -1.5..1.4 a tick in y, height 10..29
   growing by 15 (and the drift) for 12 ticks up to its limit 100..249, rise 40..79; on tick 72 it hands its position to the scene
   (m+0x250) and fires the module's 0x1E01AC0 effect; h5C turns by 7 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
} Mgr_b149_01E01C60;

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
} Obj_b149_01E01C60;

static s32 func_01E01C60_b149(Mgr_b149_01E01C60 *m, Obj_b149_01E01C60 *o) {
    extern void b149_01E01AC0();
    extern void b149_01E02BA0(Mgr_b149_01E01C60 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = 20.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->f34 = func_0019A5C8() % 30 - 15;
        o->f34 /= 10.0f;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h52 = func_0019A5C8() % 150 + 100;
        o->hE = func_0019A5C8() % 40 + 40;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 3) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 == 72) {
        m->pos = o->pos;
        b149_01E02BA0(m, b149_01E01AC0, 0);
    }
    if (o->h54 < 12) {
        if (o->h50 < o->h52) {
            o->h50 += 15;
        }
        o->pos.y += o->f34;
    }
    o->h5C += 7;
    o->h54++;
    return 0;
}

/* shape b149:01E01ED0, 135 insns, 2 copies: a yellow trail on a world track: set up once (fills the track's 15 history points
   with its current point); both colours fade in for 110 frames, then the first fades out (its fade-out step is
   applied twice); while young the module's shape b149:01E00080 shifts the track; blinks, frame climbs to 4 */

typedef struct {
    Vec4f p[15];
} Track_b149_01E01ED0;

typedef struct {
    u8 pad0[0x4470];
    Track_b149_01E01ED0 track[0x50];
    u8 pad[0xB4F0 - 0x4470 - 0x50 * 0xF0];
    Vec4f head[1];
} World_b149_01E01ED0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 h8;
    u8 padA[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Trail_b149_01E01ED0;

static s32 func_01E01ED0_b149(World_b149_01E01ED0 *w, Trail_b149_01E01ED0 *o) {
    extern void b149_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        src = &w->head[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 15; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->frame = 2;
        o->c0[3] = 0;
        o->h8 = 0;
        o->h56 = 0;
        o->size = 4.0f;
        o->state = 2;
    }
    if (o->t < 0x6E) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        }
    }
    if (o->t < 0x75) {
        b149_01E00080(&w->track[o->idx].p[14], 15, 0, &w->head[o->idx]);
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x10);
    } else {
        func_001076F0(o->c0, 0x70, 0x70, 0x10);
    }
    if (o->t != 0) {
        if (o->frame < 4) {
            o->frame++;
        }
    }
    o->t++;
    return 0;
}

/* shape b149:01E020F0, 176 insns: a glow whose kind (f50) picks its look: kinds 0/1 are grey with an orange second
   colour, flickering, brightening for 12 ticks; kind 1 also grows to 400 by 15; kind 2 starts at 840, white with a
   brown second colour, brightens by 0x20 for 13 ticks then fades by 9; kinds 0/1 fade by 15 once the game value
   at 0xBCF2 passes 0x140; the position's first word advances 0x4000 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 kind;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b149_01E020F0;

typedef struct {
    u8 pad[0xBCF2];
    s16 v;
} Game_b149_01E020F0;

static s32 func_01E020F0_b149(Game_b149_01E020F0 *g, Fx_b149_01E020F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        if (o->kind == 2) {
            o->f48 = 840.0f;
        }
        if (o->kind < 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0xF0, 0x80, 0x10);
        } else {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x40, 0x10);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind < 2) {
        if (o->tick < 12) {
            o->col[3] += 0x10;
        }
    }
    if (o->kind == 2) {
        if (o->tick < 13) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x20;
            }
        } else if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind < 2) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->col2, 0x80, 8, 0x40);
        }
    }
    if (o->kind == 1) {
        if (o->f48 < 400.0f) {
            o->f48 += 15.0f;
        }
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_00205C40(o->pos);
    o->pos[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b149:01E023B0 (b149), 505 insns, 1 copy: the scene manager: set up the scene (textures, jitter tables), then
   step the 150 effect slots and draw five kinds (three shaken-part sprites, two bobbing on a sine, a band at a table
   point, a ring at a camera position); returns cue codes by frame */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[4];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 sel;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b149_01E023B0;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xE4];
} Pt_b149_01E023B0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s16 rm[8];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b149_01E023B0 fx[150];
    u8 pad4440[0x30];
    Pt_b149_01E023B0 pt[128];
    s32 tex2[2];
    u8 padBC78[0x18];
    s32 count;
    u8 padBC94[8];
    s32 ot;
    u8 padBCA0[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padBCC2[8];
    s16 cam;
    u8 padBCCC[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b149_01E023B0;

static s32 func_01E023B0_b149(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E01360_b149();
    extern void func_01E00E10_b149();
    extern void func_01E009B0_b149();
    extern s32 func_01E01770_b149();
    extern s32 func_01E01AC0_b149();
    extern s32 func_01E01C60_b149();
    extern s32 func_01E01ED0_b149();
    extern s32 func_01E020F0_b149();
    extern void b149_01E02D30();
    Scene_b149_01E023B0 *g = (Scene_b149_01E023B0 *)arg0;
    s32 k;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xC060);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 190;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x19, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 10; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (k = 0; k < 2; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 4;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01360_b149(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01770_b149) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[1];
                g->hB8 = 6;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y + 7.0f * func_00108030(g->crdD8, g->fx[i].h5C, 0);
                g->pz = g->fx[i].pos.z;
                func_01E00E10_b149(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01AC0_b149) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[1];
                g->hB8 = 6;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00E10_b149(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01C60_b149) {
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->tex88 = g->tex2[1];
                g->hB8 = 6;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y + 7.0f * func_00108030(g->crdD8, g->fx[i].h5C, 0);
                g->pz = g->fx[i].pos.z;
                func_01E00E10_b149(g, &g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01ED0_b149) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x97, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->rm[3] >>= 1;
                g->rm[1] += g->rm[3];
                func_001F5F90(func_001F53A0(), &v);
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
                g->hBE = 1;
                if (g->fx[i].h54 > 83) {
                    b149_01E02D30(g, &g->fx[i], &g->pt[g->fx[i].sel], 0);
                }
            }
            if (g->fx[i].fn == func_01E020F0_b149) {
                if (g->fx[i].sel == 0) {
                    func_001F5620(func_001F53A0(), g->jA, &v);
                }
                if (g->fx[i].sel == 1) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                if (g->fx[i].sel == 2) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                func_01E009B0_b149(g, &g->fx[i], 0x21, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 85) {
        return 1;
    }
    if (g->frame == 180) {
        return 4;
    }
    if (g->frame == 165) {
        return 2;
    }
    if (g->frame > 95 && g->frame < 155) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b149:01E02BA0, 98 insns, 3 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b149_01E02BA0 {
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
} Slot_b149_01E02BA0;

typedef struct Obj_b149_01E02BA0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b149_01E02BA0 slots[0x96];
    u8 padB[0xbc94 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xbcea - 0xbc94 - 4];
    s16 fB2B0;
} Obj_b149_01E02BA0;

static s32 func_01E02BA0_b149(Obj_b149_01E02BA0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b149_01E02BA0 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b149", func_01E02D30_b149);
