#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b498(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00260_b498(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E002E0_b498(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00730_b498(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b498:01E00B70, 172 insns: the effect scene's step: clears the tint to 0x80/0/0/0, counts the frame (0xACBC) and
   reads joint 0xAC9C; every third frame from 151 to 319 it spawns a 0x1E01C20 two above it (side 1), to 349 a
   0x1E017C0 ten below it (side 0); and every third frame from 150 to 319 a 0x1E01DB0 at the camera point numbered by a
   0..49 counter (0xACB6) */

typedef struct {
    u8 pad0[0x2D0];
    f32 px, py, pz;
    u8 pad2DC[0xA998];
    u8 col[4];
    u8 padAC78[0x24];
    s16 joint;
    u8 padAC9E[0x16];
    s16 side;
    s16 n;
    u8 padACB8[4];
    s16 t;
} Scene_b498_01E00B70;

static void func_01E00B70_b498(Scene_b498_01E00B70 *g) {
    extern void b498_01E017C0(void);
    extern void b498_01E01C20(void);
    extern void b498_01E01DB0(void);
    extern s32 b498_01E030B0(Scene_b498_01E00B70 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    Vec4f v;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F5620(func_001F53A0(), g->joint, &v);
    if (g->t > 150 && g->t < 320 && g->t % 3 == 1) {
        g->px = v.x;
        g->py = 2.0f + v.y;
        g->pz = v.z;
        g->side = 1;
        b498_01E030B0(g, (s32)b498_01E01C20, 0);
    }
    if ((g->t >= 151) & (g->t % 3 == 1)) {
        if (g->t < 350) {
            g->px = v.x;
            g->py = v.y;
            g->pz = v.z;
            g->side = 1;
            g->py = v.y - 10.0f;
            g->side = 0;
            b498_01E030B0(g, (s32)b498_01E017C0, 0);
        }
    }
    if (g->t % 3 == 1 && g->t >= 150 && g->t < 320) {
        if (g->n < 50) {
            func_001F6160(func_001F53A0(), &v);
            g->px = v.x;
            g->py = v.y;
            g->pz = v.z;
            g->side = g->n;
            b498_01E030B0(g, (s32)b498_01E01DB0, 0);
        }
        g->n++;
        if (g->n >= 50) {
            g->n = 0;
        }
    }
}

/* shape b120:01E01240, 129 insns, 2 copies: a grey wisp: set up once (random heading, frame, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0xADC0];
    u8 trig[1];
} World_b120_01E01240;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b120_01E01240;

static s32 func_01E00E20_b498(World_b120_01E01240 *w, Wisp_b120_01E01240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x10, 0x10, 0x10);
    if (o->state == 1) {
        o->h38 = 5;
        o->a3A = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 7;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b120:01E01450, 127 insns: b064:01E01A00 with a full random tilt (0..359) and the sine table at g+0xADC0 (a context field: addiu 0x2DC8 + 0x7FF8) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b120_01E01450;

typedef struct {
    u8 pad0[0xADC0];
    u8 sin[4];
} Ctx_b120_01E01450;

static s32 func_01E01030_b498(Ctx_b120_01E01450 * g, Spark_b120_01E01450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 13) {
        o->f38++;
    }
    if (o->tick % 5 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 13.0f * func_00108030(g->sin, o->dir, 0);
    o->fA = o->fA + 13.0f * func_00108030(g->sin, o->angle, 1);
    o->fC = o->fC + 13.0f * func_00108030(g->sin, o->dir, 1);
    return 0;
}

/* shape b004:01E00460, 32 insns, 5 copies: step of a flash: first rises to alpha 0xF0 (then marks itself done rising),
   afterwards fades by 14 until it ends; keeps its colour at 0x9F/0x5F/0x5F */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b004_01E00460;

static s32 func_01E01230_b498(void *arg0, Obj_b004_01E00460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->up == 0) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] = 0xF0;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
    return 0;
}

/* shape b120:01E016D0, 109 insns, 2 copies: a blue wisp: set up once with two random angles; full for 10 frames, then
   fades out; each frame its x, y and z drift by 9 times a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0xADC0];
    u8 trig[1];
} World_b120_01E016D0;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b120_01E016D0;

static s32 func_01E012B0_b498(World_b120_01E016D0 *w, Wisp_b120_01E016D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h38 = 1;
        o->frame = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->c0, 0x1F, 0x1F, 0xFF);
        o->a30 = func_0019A5C8() % 360;
        o->a3A = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 10) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    o->x += 9.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 9.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 9.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b120:01E01890, 44 insns: colour (0x1F,0x10,0x8F); on start f38 5; passes the game value 0xAC9C to
   func_001F5620; alpha 0x80, tick 7; stops when the game state 0xAC70 is 0x32 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b120_01E01890;

typedef struct {
    u8 pad[0xAC70];
    s32 state;
    u8 padAC74[0x28];
    s16 val;
} Game_b120_01E01890;

static s32 func_01E01470_b498(Game_b120_01E01890 *g, Glow_b120_01E01890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 buf[4];

    func_001076F0(o->col, 0x1F, 0x10, 0x8F);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->val, buf);
    o->col[3] = 0x80;
    o->tick = 7;
    if (g->state == 0x32) {
        o->mode = 0;
    }
    return 0;
}

/* shape b120:01E01940, 167 insns: a sparkle that follows a model point: random rotation on start; fades by 11
   (once tick 0x32 is passed when the game counter at 0xAC70 is over 0x1E); bobs its z by 5 x the sine of the
   model's angle; on odd frames its spread grows by 4 up to 0x24; placed at the model point (y + 2) and jittered
   by the spread */

typedef struct {
    s16 x, y, z;
    s16 spread;
    u8 pad08[8];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 f32;
    s16 f34;
    s16 mode;
    s16 tick;
    s16 f3A;
} Fx_b120_01E01940;

typedef struct {
    u8 pad00[0xAC70];
    s32 count;
    u8 padAC74[0x28];
    s16 point;
    u8 padAC9E[0xADC0 - 0xAC9E];
    u8 trig[1];
} Game_b120_01E01940;

static s32 func_01E01520_b498(Game_b120_01E01940 *g, Fx_b120_01E01940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_001F5620(s32, s32, void *);
    s32 ang[4];
    f32 pt[4];

    func_001076F0(o->col, 0x70, 0x10, 8);
    if (o->mode == 1) {
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f34 = 2;
        o->tick = 0;
        o->mode = 2;
        o->spread = 2;
        o->col[3] = 0x60;
    }
    if (g->count > 0x1E) {
        if (o->tick > 0x32) {
            if (o->col[3] > 0xC) {
                o->col[3] -= 11;
            } else {
                o->mode = 0;
            }
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->tick++;
    func_001F6160(func_001F53A0(), ang);
    o->z = o->z + 5.0f * func_00108030(g->trig, ang[1] / 180, 1);
    if (o->f32 % 2 == 1) {
        if (o->spread < 0x24) {
            o->spread += 4;
        }
    }
    func_001F5620(func_001F53A0(), g->point, pt);
    o->x = pt[0];
    o->y = 2.0f + pt[1];
    o->x += (s16)(func_0019A5C8() % o->spread - (o->spread >> 1));
    o->y += (s16)(func_0019A5C8() % o->spread - (o->spread >> 1));
    o->f3A += 12;
    return 0;
}

/* shape b498:01E017C0, 174 insns: b120:01E01940 family: a blue smoke column (dark after its second step): turned
   -0x4000 on start at alpha 0x80 and spread 2; while the game counter at 0xAC70 is over 30 and it is under 30 ticks
   old it fades by 16 only once the spread passes 80, otherwise always; the spread grows by 2, z bobs by 7 x the sine
   of the camera's yaw, and every fourth tick it spawns two 0x1E00E20 puffs at a random angle, x jittered by the
   spread */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 step;
    s16 t;
    s16 h34;
    s16 mode;
    s16 spread;
    s16 f3A;
} Fx_b498_01E017C0;

typedef struct {
    u8 pad0[0x2D0];
    f32 px, py, pz;
    u8 pad2DC[0xA994];
    s32 count;
    u8 padAC74[0x3A];
    s16 ang;
    u8 padACB0[0x110];
    u8 trig[1];
} Game_b498_01E017C0;

static s32 func_01E017C0_b498(Game_b498_01E017C0 *g, Fx_b498_01E017C0 *o) {
    extern void b498_01E00E20(void);
    extern s32 b498_01E030B0(Game_b498_01E017C0 *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    s32 ang[4];
    s16 i;

    if (o->step < 2) {
        func_001076F0(o->col, 8, 8, 0x80);
    } else {
        func_001076F0(o->col, 0x10, 0x10, 0x20);
    }
    if (o->mode == 1) {
        o->rot[0] = -0x4000;
        o->rot[1] = 0;
        o->rot[2] = 0;
        o->h34 = 0;
        o->spread = 2;
        o->mode = 2;
        o->col[3] = 0x80;
    }
    if (g->count > 30 && o->t < 30) {
        if (o->spread > 80) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 16;
            } else {
                o->mode = 0;
            }
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 16;
    } else {
        o->mode = 0;
    }
    o->spread += 2;
    func_001F6160(func_001F53A0(), ang);
    o->step++;
    o->z = o->z + 7.0f * func_00108030(g->trig, ang[1] / 180, 1);
    o->t++;
    o->f3A += 12;
    if (o->t % 4 == 1) {
        for (i = 0; i < 2; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = o->x + (func_0019A5C8() % o->spread - (o->spread >> 1)) * 2;
            g->py = o->y;
            g->pz = o->z;
            b498_01E030B0(g, (s32)b498_01E00E20, 0);
        }
    }
    return 0;
}

/* shape b120:01E01EA0, 46 insns: colour (0x20,0x20,0); on start f38 = f30, alpha 0x80; alpha drops by 0x40 (while
   below 0x80) for 2 ticks, then fades out by 12 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b120_01E01EA0;

static s32 func_01E01A80_b498(s32 arg0, Glow_b120_01E01EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x20, 0x20, 0);
    if (o->mode == 1) {
        o->f38 = o->f30;
        o->mode = 2;
        o->col[3] = 0x80;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] -= 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b120:01E01F60, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x40
   for the first 2 ticks, then fades out by 12 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b120_01E01F60;

static s32 func_01E01B40_b498(s32 arg0, Flash_b120_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x10, 0x10, 8);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b498:01E01C20, 99 insns: a blue rising spark: frame 10, random sub-frame 0..3, half turn unless the scene flag is set,
   start height 5..14 (old one kept), rise 30..49, width 0..49, hold 30..49; alpha up by 12 until the hold, then down by 10 */

typedef struct {
    u8 pad0[0xACB8];
    s16 flag;
} Scene_b498_01E01C20;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 y0;
} Obj_b498_01E01C20;

static s32 func_01E01C20_b498(Scene_b498_01E01C20 *g, Obj_b498_01E01C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x20, 0x20, 0xC0);
        if (g->flag != 0) {
            o->rot1 = 0;
        } else {
            o->rot1 = 0x8000;
        }
        o->rot0 = 0;
        o->rot2 = 0;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 10 + 5;
        o->step = func_0019A5C8() % 20 + 0x1E;
        o->w = func_0019A5C8() % 50;
        o->hold = func_0019A5C8() % 20 + 0x1E;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] += 0xC;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->y += o->step;
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b498", func_01E01DB0_b498);

/* shape b120:01E02750, 80 insns, 2 copies: a blue swell: set up once (two blue colours, growth 3 or 5 a frame by whether it
   started turned), fades in over 2 frames, then both colours fade out (b003:01E01780 family) */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 size;
    u8 padC[2];
    s16 slow;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b120_01E02750;

static s32 func_01E02330_b498(void *arg0, Obj_b120_01E02750 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->h8 = 2;
        o->size = 2;
        if (o->ang == 0) {
            o->slow = 0;
        } else {
            o->slow = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x40;
        o->c1[3] += 0x40;
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xE) {
            o->c1[3] -= 0xD;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->slow == 0) {
        o->size += 5;
    } else {
        o->size += 3;
    }
    o->t++;
    o->ang += 10;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b498", func_01E02470_b498);

/* shape b120:01E034D0, 94 insns, 2 copies: spawns an effect into the first free slot (150 of 0x40 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument
   (b082:01E02FF0 family, small slots) */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    u8 c0[4];
    u8 c1[4];
    s16 h30;
    u8 pad32[4];
    s16 active;
    u8 pad38[2];
    s16 h3A;
    u8 pad3C[4];
} Slot_b120_01E034D0;

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x300];
    Slot_b120_01E034D0 slot[150];
    u8 pad2B60[0xAC74 - 0x5E0 - 150 * 0x40];
    u8 col[4];
    u8 padAC78[0x36];
    s16 hACAE;
    u8 padACB0[4];
    s16 hACB4;
} Scene_b120_01E034D0;

static s32 func_01E030B0_b498(Scene_b120_01E034D0 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b120_01E034D0 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x40);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 150;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->h30 = s->hACB4;
        sl->h3A = s->hACAE;
        sl->w20 = arg;
        sl->w24 = fn;
        return 1;
    }
    return 0;
}

/* shape b120:01E03650, 103 insns: b053:01E022F0 family (one textured camera-facing square; texture 0x99, page at ctx+0x35C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b120_01E03650;

static void func_01E03230_b498(u8 *ctx, Obj_b120_01E03650 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x99, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x35C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b120:01E037F0, 103 insns: b053:01E022F0 family (one textured camera-facing square; texture 0x14, page at ctx+0x328) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b120_01E037F0;

static void func_01E033D0_b498(u8 *ctx, Obj_b120_01E037F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x328), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b120:01E03990, 103 insns: b053:01E022F0 family (one textured camera-facing square; texture 0x9C, page at ctx+0x35C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b120_01E03990;

static void func_01E03570_b498(u8 *ctx, Obj_b120_01E03990 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x9C, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x35C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b498:01E03710 (B498PAINT_RAIN5), 174 insns, 2 copies: b120:01E03B30's source: mode 0 sets up the drawing
   state (a 0x8D matrix from the anim's angle at 0x34, colour, the game's texture at 0x358); otherwise draws a ring of
   18 quads 20 apart around the anim's point, the inner edge at radius 0 (still multiplied out), into the game's
   target with its depth */

typedef struct {
    f32 x, y, z, w;
} Vec_b498_01E03710;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b498_01E03710;

typedef struct {
    u8 pad00[0x358];
    s32 texture;
    u8 pad35C[0xAC7C - 0x35C];
    s32 target;
    u8 padAC80[0xC];
    f32 depth;
    u8 padAC90[0xADC0 - 0xAC90];
    u8 trig[1];
} Game_b498_01E03710;

#pragma opt_propagation off

static void func_01E03710_b498(Game_b498_01E03710 *g, Anim_b498_01E03710 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b498_01E03710 quad[4];
    Vec_b498_01E03710 pos;
    f32 m[16];
    f32 rm[4];
    f32 inner;
    s32 k;
    s16 j;
    s16 a;

    j = 0;
    if (mode == 0) {
        func_00106080(rm, 0x8D, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 1);
        func_00208700(p, g->texture, 1);
    } else {
        pos.x = an->x;
        pos.y = an->y;
        pos.z = an->z;
        func_00108EF0(m, 0, an->rot, &pos);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        inner = 0.0f;
        k = 0;
        do {
            a = an->start + j;
            quad[2].x = an->radius * func_00108030(g->trig, a, 1);
            quad[2].z = an->radius * func_00108030(g->trig, a, 0);
            quad[0].x = inner * func_00108030(g->trig, a, 1);
            quad[0].z = inner * func_00108030(g->trig, a, 0);
            a = an->start + 20 + j;
            quad[3].x = an->radius * func_00108030(g->trig, a, 1);
            quad[3].z = an->radius * func_00108030(g->trig, a, 0);
            quad[1].x = inner * func_00108030(g->trig, a, 1);
            quad[1].z = inner * func_00108030(g->trig, a, 0);
            if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
            j += 20;
        } while (++k < 18);
    }
}
#pragma opt_propagation reset

/* shape b120:01E03DF0, 170 insns: mode 0 sets up the packet (a 0x9C matrix, the anim's colour on all four corners,
   the game's texture at 0x35C); otherwise builds the game's matrix (0x290) from the anim's two positions and two
   rotations, the second scaled (h30 / 4, 1, 1), and draws the game's four quads at 0x360 */

typedef struct {
    f32 x, y, z, w;
} Vec_b120_01E03DF0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b120_01E03DF0;

typedef struct {
    Rgbaq_b120_01E03DF0 c;
    u64 st;
    u64 xyz;
} Vtx_b120_01E03DF0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b120_01E03DF0 v[4];
} Pkt_b120_01E03DF0;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 x2, y2, z2;
    u8 pad0E[2];
    s32 r0;
    s32 r1;
    s32 r2;
    u8 pad1C[0xC];
    u8 col[8];
    s16 h30;
} Anim_b120_01E03DF0;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0x8C];
    s32 texture;
    Vec_b120_01E03DF0 quad[4][4];
    u8 pad460[0xAC7C - 0x460];
    s32 target;
    u8 padAC80[0xC];
    f32 depth;
} Game_b120_01E03DF0;

static void func_01E039D0_b498(Game_b120_01E03DF0 *g, Anim_b120_01E03DF0 *an, Pkt_b120_01E03DF0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b120_01E03DF0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b120_01E03DF0 pos;
    f32 rm[4];
    s32 rot[4];
    Vec_b120_01E03DF0 sc;
    f32 t;
    f32 m[16];
    s16 i;

    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col);
        p->v[3].c = func_00107740(an->col);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020EB40(g->m);
        func_00106DD0(&pos, an->x, an->y, an->z);
        t = an->h30;
        t /= 4.0f;
        sc.x = t;
        sc.y = 1.0f;
        sc.z = 1.0f;
        rot[0] = an->r0;
        rot[1] = 0;
        rot[2] = an->r2;
        func_0020C940(m, 0, rot, &pos);
        func_00106DD0(&pos, an->x2, an->y2, an->z2);
        func_0020BC00(g->m, m);
        rot[0] = 0;
        rot[1] = an->r1;
        rot[2] = 0;
        func_0020C940(m, &sc, rot, 0);
        func_0020BC00(g->m, m);
        for (i = 0; i < 4; i++) {
            if (func_00205630(g->quad[i], 0x70000000, g->m, p, &g->depth) != 0) {
                func_00109380(p, 0);
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape b120:01E040A0, 108 insns, 2 copies: one textured square of an object (b053:01E022F0 family, texture 0x99, size / 20);
   mode 0 only sets up the packet's texture, otherwise position = pos + vel / 10, camera-facing, drawn via
   func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b120_01E040A0;

static void func_01E03C80_b498(u8 *ctx, Obj_b120_01E040A0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x99, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x35C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size / 20.0f;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

typedef struct {
    f32 x, y, z, w;
} Vec_b073_01E03970;

typedef struct {
    u8 pad00[0x28];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    u8 pad32[6];
    s16 radius;
    s16 start;
} Anim_b073_01E03970;

typedef struct {
    u8 pad00[0x20];
    Vec_b073_01E03970 pts[6];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b073_01E03970;

static void func_01E03E30_b498(Obj_b073_01E03970 *o, Anim_b073_01E03970 *an, void *p) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b073_01E03970 quad[4];
    Vec_b073_01E03970 at;
    Vec_b073_01E03970 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    func_00107990(p, an->c28, 1);
    func_00107990(p, an->c2C, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(rot);
    rot[0] += 0x4000;
    at.x = o->pts[an->h30].x;
    at.y = o->pts[an->h30].y;
    at.z = o->pts[an->h30].z;
    func_00108EF0(m, &scale, rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            func_00109380(p, 1);
            func_002075F0(p, o->target, (u32)depth);
        }
        j += 20;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b498", func_01E04080_b498);

/* shape b120:01E046E0, 265 insns: variant of b045:01E011B0 (sprite row into the given packet): square sprites of
   the sprite's h38, the camera rotation only (sprite rotation passed to the world matrix), z shake / 10 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b120_01E046E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b120_01E046E0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
} Pkt_b120_01E046E0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b120_01E046E0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[6];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 h38;
} Spr_b120_01E046E0;

static void func_01E042C0_b498(Obj_b120_01E046E0 *o, Spr_b120_01E046E0 *s, Pkt_b120_01E046E0 *p, s8 *tbl) {
    extern Rgbaq_b120_01E046E0 func_00107740(void *);
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
    s16 i;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;
    f32 w;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_01E002E0_b498((Pk_b008_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, s->rot, &pos);
    for (i = 0; i < o->count; i++) {
        w = s->h38;
        func_00108CE0(quad, w, w);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += 0.7f * (f * (s->w30 + h));
        quad[3].x += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += 0.7f * (f * (s->w30 + h));
        quad[3].y += 0.7f * (f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 10.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += 0.7f * (f * (s->w30 + h));
        quad[3].z += 0.7f * (f * (s->w30 + h));
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b069:01E01A70, 166 insns: draws 4 copies of a gradient quad (colour A on three corners, B on the last)
   at one of the object's points (fx->point), each turned by the effect's rotation; far z. The packet is passed
   in. Same family as b020:01E00E70. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b069_01E01A70;

typedef struct {
    Rgbaq_b069_01E01A70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b069_01E01A70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b069_01E01A70 v[4];
    u8 tail[0x20];
} Pkt_b069_01E01A70;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b069_01E01A70;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b069_01E01A70;

static void func_01E046F0_b498(Obj_b069_01E01A70 *o, Fx_b069_01E01A70 *fx, Pkt_b069_01E01A70 *p) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b069_01E01A70 func_00107740(void *);
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
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = o->pts[fx->point].x;
    t.y = o->pts[fx->point].y;
    t.z = o->pts[fx->point].z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b120:01E04DB0, 361 insns: textured ribbon between two point trails (family of b476:01E042E0): 4 spline quads
   per segment (module curve function, shape b018:01E00EE0), lifted 40 up; near/far colours from two colours that
   share a fading alpha; each quad drawn twice. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b120_01E04DB0;

typedef struct {
    Rgbaq_b120_01E04DB0 c;
    u64 uv;
    u64 xyz;
} Vtx_b120_01E04DB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b120_01E04DB0 v[4];
    u8 tail[0x20];
} Pkt_b120_01E04DB0;

typedef struct {
    u8 r, g, b, a;
} C4_b120_01E04DB0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b120_01E04DB0 col0;
    C4_b120_01E04DB0 col1;
} Rib_b120_01E04DB0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
} Obj_b120_01E04DB0;

static void func_01E04990_b498(Obj_b120_01E04DB0 *o, Rib_b120_01E04DB0 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b120_01E04DB0 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 v;
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    f32 m[16];
    Pkt_b120_01E04DB0 pkt __attribute__((aligned(8)));
    C4_b120_01E04DB0 c0;
    C4_b120_01E04DB0 c1;
    s32 k;
    s32 j;
    s32 i;
    s16 n;
    s32 x;
    Pkt_b120_01E04DB0 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    n = s->n;
    v.x = 0.0f;
    v.y = 40.0f;
    v.z = 0.0f;
    func_00108EF0(m, NULL, NULL, &v);
    p = (Pkt_b120_01E04DB0 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, &s->col0, 0);
    func_00108500(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    c0 = s->col0;
    c1 = s->col1;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            c1.a = c0.a;
            p->v[0].c = func_00107740(&c0);
            p->v[2].c = func_00107740(&c1);
            x = c0.a - (s16)(s->col0.a / (n * 2));
            if (x > 0) {
                c0.a = x;
            } else {
                c0.a = 0;
            }
            c1.a = c0.a;
            p->v[1].c = func_00107740(&c0);
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                for (i = 0; i < 2; i++) {
                    A[i] = func_01E00730_b498(pp, 0, t);
                    B[i] = func_01E00730_b498(pq, 0, t);
                    if (i == 0) {
                        t += 0.25f;
                    }
                }
            } else {
                for (i = 0; i < 2; i++) {
                    A[i] = func_01E00730_b498(a4, 0, t);
                    B[i] = func_01E00730_b498(b4, 0, t);
                    if (i == 0) {
                        t += 0.25f;
                    }
                }
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
}
