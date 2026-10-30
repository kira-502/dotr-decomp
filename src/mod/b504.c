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

static void func_01E00080_b504(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b504(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b504_01E00080();
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
    b504_01E00080(p, obj->f94, obj->fC0);
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

/* shape b504:01E00E70 (B504_W_S), 232 insns: the scene script of b504: colour 0x80/0/0/0, counts g+0xB716; ticks
   38..180 spawn 0x1E01980; tick 38 spawns 0x1E02470, moves the point to joint 0xB6F8 and spawns 0x1E017A0; ticks
   50..200 spawn 6..14 0x1E01210 jittered around the joint; ticks 38..200 a 0x1E013F0 jittered around the camera;
   then reads the joint into g+0xB690 */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0xB690 - 0x25C];
    f32 p[4];
    u8 padB6A0[0x24];
    u8 col[4];
    u8 padB6C8[0x30];
    s16 joint;
    u8 padB6FA[0x1C];
    s16 tick;
} Ctx_b504_01E00E70;

static void func_01E00E70_b504(Ctx_b504_01E00E70 *g) {
    extern void b504_01E01210();
    extern void b504_01E013F0();
    extern void b504_01E017A0();
    extern void b504_01E01980();
    extern void b504_01E02470();
    extern void b504_01E02E00(Ctx_b504_01E00E70 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    s32 i;
    s32 n;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick >= 38 && g->tick <= 180) {
        b504_01E02E00(g, b504_01E01980, 0);
    }
    if (g->tick == 38) {
        b504_01E02E00(g, b504_01E02470, 0);
    }
    if (g->tick == 38) {
        func_001F5620(func_001F53A0(), g->joint, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
    }
    if (g->tick == 38) {
        b504_01E02E00(g, b504_01E017A0, 0);
    }
    if (g->tick >= 50 && g->tick <= 200) {
        func_001F5620(func_001F53A0(), g->joint, v);
        n = func_0019A5C8() % 9 + 6;
        for (i = 0; i < n; i++) {
            g->x = v[0] + func_0019A5C8() % 60 - 30.0f;
            g->y = v[1] + func_0019A5C8() % 30 - 20.0f;
            g->z = v[2] + func_0019A5C8() % 30 - 15.0f;
            b504_01E02E00(g, b504_01E01210, 0);
        }
    }
    if (g->tick >= 38 && g->tick <= 200) {
        func_001F5F90(func_001F5380(), v);
        g->x = v[0] + func_0019A5C8() % 30 - 15.0f;
        g->y = v[1] + func_0019A5C8() % 30 - 15.0f;
        g->z = v[2] + func_0019A5C8() % 30 - 15.0f;
        b504_01E02E00(g, b504_01E013F0, 0);
    }
    func_001F5620(func_001F53A0(), g->joint, g->p);
}

/* shape b504:01E01210, 118 insns: sweeping blade flash: on start size 50, rot (50, 8, +-6 by the game's side flag),
   grey, random f50 and heading; solid alpha for 11 ticks then -0xF; it slides 15 sideways (away from the side) and
   rises 1.5 per tick, flickering grey/light grey on alternate ticks. */

typedef struct {
    u8 pad0[0xB712];
    s16 side;
} Game_b504_01E01210;

typedef struct {
    u8 pad0[0x14];
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 heading;
    u8 pad5C[4];
    u8 col[4];
} Fx_b504_01E01210;

static s32 func_01E01210_b504(Game_b504_01E01210 *g, Fx_b504_01E01210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 50.0f;
        o->rot[0] = 50;
        o->rot[1] = 8;
        if (g->side != 0) {
            o->rot[2] = 6;
        } else {
            o->rot[2] = -6;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 180;
        o->heading = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 11) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 0xF;
    } else {
        o->mode = 0;
    }
    o->f56 = 2;
    if (g->side != 0) {
        o->z -= 15.0f;
    } else {
        o->z += 15.0f;
    }
    o->y -= 1.5f;
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    o->tick++;
    return 0;
}

/* shape b504:01E013F0, 112 insns: a grey rising spark (b203:01E027D0 shape): size 10, random sub-frame 0..6, two angles, frame
   0..7, start height 10..29 (old one kept), rise 20..44 once started, width 0..34, hold 3..7; alpha up by 32, then down by 8 */

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
    s16 ang2;
    u8 pad5E[2];
    u8 c0[4];
} Obj_b504_01E013F0;

static s32 func_01E013F0_b504(void *arg0, Obj_b504_01E013F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->sub = func_0019A5C8() % 7;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->ang2 = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 8;
        o->y0 = o->y;
        o->y = 0;
        o->y = func_0019A5C8() % 20 + 0xA;
        o->step = func_0019A5C8() % 25 + 0x14;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x20;
        }
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

/* shape b504:01E015B0, 122 insns: a scene light at 0xB640: on start colour/size 128/4/2/0, height 0/120/0 and the effect's
   position as floats; its strength 0xB668 rises by 0.2 up to 1 (then 0x50 = 1) and falls by 0.1 until it ends
   the effect; func_001F6C10 gets the light (or 0 once ended); it also ends when the light's 0xB6C0 flag is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x54];
    s32 done;
} Light_b504_01E015B0;

typedef struct {
    u8 pad0[0xB640];
    Light_b504_01E015B0 light;
} Game_b504_01E015B0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x4A];
    s16 f50;
    u8 pad52[6];
    s16 mode;
} Fx_b504_01E015B0;

static s32 func_01E015B0_b504(Game_b504_01E015B0 *g, Fx_b504_01E015B0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a[0] = 128.0f;
        g->light.a[1] = 4.0f;
        g->light.a[2] = 2.0f;
        g->light.a[3] = 0.0f;
        g->light.b[0] = 0.0f;
        g->light.b[1] = 120.0f;
        g->light.b[2] = 0.0f;
        g->light.pos[0] = o->x;
        g->light.pos[1] = o->y;
        g->light.pos[2] = o->z;
        o->mode = 2;
        o->f50 = 0;
    }
    if (o->f50 == 0) {
        if (g->light.b[2] < 1.0f) {
            g->light.b[2] += 0.2f;
        } else {
            o->f50 = 1;
        }
    } else if (g->light.b[2] > 0.1f) {
        g->light.b[2] -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->light.done == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b504:01E017A0, 55 insns: volume fade by game state (b124:01E01A30 layout at 0x50): state at 0xB6C0 limit 0x14, down 10 to 0x30,
   up 10 to 0x80 where the fade ends; counts its frames */

typedef struct {
    u8 pad[0xB6C0];
    s32 state;
} Game_b504_01E017A0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b504_01E017A0;

static s32 func_01E017A0_b504(Game_b504_01E017A0 *g, Fade_b504_01E017A0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
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
            o->mode = 0;
        }
    }
    o->t++;
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

typedef struct {
    u8 r, g, b, a;
} Col_b361_01E01040;

typedef struct {
    u8 pad00[0x50];
    s16 h50;
    u8 pad52[6];
    s16 h58;
    u8 pad5A[9];
    u8 b63;
} Obj_b361_01E01040;

extern Col_b361_01E01040 D_01E03380_b504;
extern Col_b361_01E01040 D_01E03388_b504;

static s32 func_01E01880_b504(s32 unused, Obj_b361_01E01040 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    Col_b361_01E01040 c0;
    Col_b361_01E01040 c1;

    *(f32 *)(u32)&c0 = *(f32 *)(u32)&D_01E03380_b504;
    *(f32 *)(u32)&c1 = *(f32 *)(u32)&D_01E03388_b504;
    if (o->h58 == 1) {
        o->h50 = 0;
        o->b63 = 0;
    }
    if (o->h50 == 0) {
        if (o->b63 < 0xC0) {
            o->b63 += 0x1E;
        } else {
            o->h50 = 1;
        }
    } else {
        if (o->b63 > 0x40) {
            o->b63 -= 0x1E;
        } else {
            o->h50 = 0;
        }
    }
    c0.b = o->b63;
    c1.b = o->b63;
    c0.g = o->b63;
    c1.g = o->b63;
    c0.r = o->b63;
    c1.r = o->b63;
    func_001F7170(3, 1, &c0, &c1, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b504", func_01E01980_b504);

/* shape b504:01E02470, 229 insns: b361:01E01A00 twin with the scene packet at 0xB6D4 and its clock at 0xB716 (ends at
   184); a white full-screen flash written into the scene's shared packet (0x5F54): each of
   the four corners takes the flash colour, the screen corners (0x6BF8/0x93F8 by 0x71F8/0x8DF8, far depth) and the
   texture corners 0..0.625 by 0..0.875; alpha grows by 16 to 0xC0 until scene frame 200, then fades by 19; the
   flash ends at frame 166 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b504_01E02470;

typedef struct {
    Rgbaq_b504_01E02470 c;
    f32 s, t;
    u64 x : 16, y : 16, z : 24, f : 8;
} Vtx_b504_01E02470;

typedef struct {
    u8 hdr[0x10];
    Vtx_b504_01E02470 v[4];
} Pkt_b504_01E02470;

typedef struct {
    u8 pad0[0xB6D4];
    Pkt_b504_01E02470 *pk;
    u8 pad5F58[0x3E];
    s16 t;
} Scene_b504_01E02470;

typedef struct {
    u8 pad0[0x54];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Flash_b504_01E02470;

static s32 func_01E02470_b504(Scene_b504_01E02470 *g, Flash_b504_01E02470 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern Rgbaq_b504_01E02470 func_00107740(void *);

    if (o->state == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
    }
    g->pk->v[0].c = func_00107740(o->col);
    g->pk->v[1].c = func_00107740(o->col);
    g->pk->v[2].c = func_00107740(o->col);
    g->pk->v[3].c = func_00107740(o->col);
    g->pk->v[0].x = 0x6BF8;
    g->pk->v[0].y = 0x71F8;
    g->pk->v[0].z = 0xFFFFFF;
    g->pk->v[0].f = 0;
    g->pk->v[1].x = 0x93F8;
    g->pk->v[1].y = 0x71F8;
    g->pk->v[1].z = 0xFFFFFF;
    g->pk->v[1].f = 0;
    g->pk->v[2].x = 0x6BF8;
    g->pk->v[2].y = 0x8DF8;
    g->pk->v[2].z = 0xFFFFFF;
    g->pk->v[2].f = 0;
    g->pk->v[3].x = 0x93F8;
    g->pk->v[3].y = 0x8DF8;
    g->pk->v[3].z = 0xFFFFFF;
    g->pk->v[3].f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.0f;
    g->pk->v[2].s = 0.0f;
    g->pk->v[2].t = 0.875f;
    g->pk->v[3].s = 0.625f;
    g->pk->v[3].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    if (g->t < 200) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->state = 0;
    }
    if (g->t >= 184) {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b504:01E02810 (b504), 379 insns, 1 copy: the module's main (b490:01E020F0 family): on start clears the 0xBA90
   context, two cameras, 240 ticks, three joints, texture 5:0, the facing, the jitter tables; each tick runs the 410
   slots' five movers, counting the two kinds that need the extra pass, then draws the two drawn kinds; ends 1 at step
   60, 4 at 230, 2 at 210, 6 in 71..204, 8 when the timer runs out */

typedef struct {
    u8 pad00[0xA];
    s16 fA;
    u8 pad0C[4];
    f32 x, y, z;
    u8 pad1C[0x18];
    f32 dy;
    u8 pad38[0xC];
    void *fn;
    u8 pad48[0xE];
    s16 rot;
    s16 used;
    u8 pad5A[0x16];
} Slot_b504_01E02810;

typedef struct {
    u8 pad0000[0x20];
    f32 px, py, pz;
    u8 pad002C[0x54];
    s32 ot2;
    u8 pad0084[4];
    s32 tex88;
    u8 pad008C[8];
    Vec4f m94;
    u8 pad00A4[0x14];
    s16 mode;
    u8 pad00BA[6];
    s16 fC0;
    u8 pad00C2[0x16];
    u8 camD8[0x208];
    Slot_b504_01E02810 slot[410];
    u8 padB640[0x60];
    s32 tex5[8];
    s32 timer;
    u8 padB6C4[8];
    s32 ot;
    u8 padB6D0[0x28];
    s16 joint[3];
    u8 padB6FE[0x14];
    s16 face;
    s16 code;
    s16 step;
    s8 jit[256];
    s8 jit2[256];
    u8 padB918[1];
} Ctx_b504_01E02810;

static s32 func_01E02810_b504(s32 arg0, s32 code) {
    Ctx_b504_01E02810 *g = (Ctx_b504_01E02810 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E00920_b504();
    extern void func_01E00E70_b504();
    extern s32 func_01E01210_b504();
    extern s32 func_01E013F0_b504();
    extern s32 func_01E015B0_b504();
    extern s32 func_01E017A0_b504();
    extern s32 func_01E01880_b504();
    extern s32 b504_01E01980();
    extern s32 func_01E02470_b504();
    extern void b504_01E02F90();
    extern void b504_01E03180();
    Vec4f v;
    Vec4f m;
    Vec4f m2;
    s32 r1[4];
    s32 r2[4];
    s32 n;
    s32 c;
    s32 i;
    s32 face;

    n = 0;
    c = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xBA90);
        func_00107C10(g->padB918);
        func_00107C10(g->camD8);
        g->code = code;
        g->timer = 240;
        g->joint[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 1, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 1, 0);
        for (i = 0; i < 1; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), r1);
        g->face = r1[1] / 180.0f;
        for (i = 0; i < 256; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 100; i++) {
            g->jit2[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 5;
        }
        func_001F6160(func_001F53A0(), r2);
        face = r2[1] / 180.0f;
        for (i = 180; i < 256; i++) {
            if (face != 0) {
                g->jit2[i] = func_0019A5C8() % 4;
            } else {
                g->jit2[i] = -(func_0019A5C8() % 4);
            }
        }
        return 0;
    }
    func_01E00E70_b504(g, 0);
    for (i = 0; i < 410; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E01210_b504) {
                func_01E01210_b504(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E013F0_b504) {
                func_01E013F0_b504(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E015B0_b504) {
                func_01E015B0_b504(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E017A0_b504) {
                func_01E017A0_b504(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01880_b504) {
                func_01E01880_b504(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b504_01E01980) {
                n = (s16)(n + 1);
            }
            if (g->slot[i].fn == func_01E02470_b504) {
                n = (s16)(n + 1);
            }
        }
    }
    for (i = 0; i < 410; i++) {
        if (g->slot[i].used != 0) {
            c++;
            if (g->slot[i].fn == func_01E01210_b504) {
                g->tex88 = g->tex5[0];
                func_00106080(&m, 0x14, g->slot[i].rot, 0);
                g->m94 = m;
                v.x = g->slot[i].x;
                v.y = g->slot[i].y;
                v.z = g->slot[i].z;
                b504_01E02F90(g, &g->slot[i], 0, v);
            }
            if (g->slot[i].fn == func_01E013F0_b504) {
                func_00106080(&m2, 0x14, g->slot[i].rot, 0);
                g->m94 = m2;
                g->tex88 = g->tex5[0];
                g->mode = 6;
                g->fC0 = g->slot[i].fA;
                g->px = g->slot[i].x;
                g->py = g->slot[i].y + g->slot[i].dy;
                g->pz = g->slot[i].z;
                func_01E00920_b504(g, &g->slot[i], 0x20, g->jit);
                g->mode = 0;
            }
        }
    }
    if (n != 0) {
        b504_01E03180(g);
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 60) {
        return 1;
    }
    if (g->step == 230) {
        return 4;
    }
    if (g->step == 210) {
        return 2;
    }
    if (g->step > 70 && g->step < 205) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b504:01E02E00, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x19a of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b504_01E02E00 {
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
} Slot_b504_01E02E00;

typedef struct Obj_b504_01E02E00 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2e0 - 0x250 - 12];
    Slot_b504_01E02E00 slots[0x19a];
    u8 padB[0xb6c4 - 0x2e0 - 0x19a * 0x70];
    u8 rgba[4];
    u8 padC[0xb710 - 0xb6c4 - 4];
    s16 fB2B0;
} Obj_b504_01E02E00;

static s32 func_01E02E00_b504(Obj_b504_01E02E00 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b504_01E02E00 *s = NULL;
    s16 i;

    for (i = 0; i < 0x19a; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x19a;
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b504 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b361_01E022E0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b361_01E022E0_unused;

typedef struct Obj_b361_01E022E0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b361_01E022E0;

typedef struct Xyz_b361_01E022E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b361_01E022E0;

typedef struct Uv_b361_01E022E0 {
    f32 u, v;
} Uv_b361_01E022E0;

typedef struct Pk_b361_01E022E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b361_01E022E0 uv;
    u64 pad18;
    Xyz_b361_01E022E0 v[4];
    u64 pad60[6];
} Pk_b361_01E022E0;

typedef struct Buf_b361_01E022E0 {
    u64 tag;
    Pk_b361_01E022E0 pk;
} Buf_b361_01E022E0;


typedef struct Data_b361_01E022E0 {
    u8 pad0[0x20];
    s32 wh[2];
    u8 padB[0x38];
    Vec4f uv;
} Data_b361_01E022E0;

static void func_01E02F90_b504(Obj_b361_01E022E0 *obj, Data_b361_01E022E0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b361_01E022E0 buf;
    Uv_b361_01E022E0 uv;
    Pk_b361_01E022E0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (mode == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (mode == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->uv);
    p->uv = uv;
    func_01E00080_b504((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] = 0x4000;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->wh[0], data->wh[1]);
    func_00109100(view, data->wh, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b504:01E03180, 117 insns: the module's draw pass with two packets on the stack (b092:01E04800 family): opens a 12-reg
   packet, then runs every live slot (410 of 0x70 bytes) whose handler is b504:01E01980, then those whose handler is
   b504:01E02470; queues the batch only if any slot drew */

typedef struct {
    u8 b[0x58];
} PktA_b504_01E03180;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x68];
    u64 t78;
    u64 t80;
    u8 tail[8];
} PktB_b504_01E03180;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b504_01E03180;

typedef struct {
    u8 pad0[0x2E0];
    Slot_b504_01E03180 slot[410];
    u8 padEnd[0xB6D4 - 0x2E0 - 410 * 0x70];
    PktB_b504_01E03180 *pkb;
    u8 padB6D8[0x18];
    s32 ctx;
    PktA_b504_01E03180 *pka;
} Scene_b504_01E03180;

static void func_01E03180_b504(Scene_b504_01E03180 *s) {
    extern void b504_01E01980(Scene_b504_01E03180 *, Slot_b504_01E03180 *);
    extern void b504_01E02470(Scene_b504_01E03180 *, Slot_b504_01E03180 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    PktA_b504_01E03180 pka __attribute__((aligned(8)));
    PktB_b504_01E03180 pkb __attribute__((aligned(8)));
    PktB_b504_01E03180 *b;
    s32 i;
    s32 n;

    s->pka = &pka;
    s->pkb = &pkb;
    n = 0;
    s->ctx = func_00207F60();
    s->pkb->count = 0x34;
    s->pkb->tag = 0xC;
    s->pkb->regs = 0x421421421421;
    s->pkb->pad = 0;
    func_00208460();
    func_002086D0(s->pkb, ((u64)0x80 << 32) | 0x48);
    b = s->pkb;
    func_001F7060(func_001F53A0(), 0, &b->t78, &b->t80);
    func_00208460();
    for (i = 0; i < 410; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b504_01E01980) {
            n++;
            b504_01E01980(s, &s->slot[i]);
        }
    }
    for (i = 0; i < 410; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b504_01E02470) {
            n++;
            b504_01E02470(s, &s->slot[i]);
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
