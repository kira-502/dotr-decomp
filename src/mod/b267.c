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

static void func_01E00080_b267(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

/* shape b267:01E00260 (B267_W_S), 383 insns, 1 copy: B267_W_S, the scene script: colour 0x80,0,0,0, counts the frame
   (0x3E2E); on frames 28/51/73/95/120 places a column beside the camera (x +-3/+-2/0 flipped by the camera angle
   sign, y +2/+2/-2/-2/+4), saves it in one of five slots and starts two b267:01E00E50 columns (angles 0, 90) and one
   b267:01E01610; frame 125 a b267:01E01740 flash; frame 150 saves the joint (0x3E1A) and starts b267:01E00BF0 and
   b267:01E00A80 there; frames 151..494 smoke wisps (b267:01E00F90 at the joint, b267:01E01260 at the saved point),
   from 251 white sparks (b267:01E01500) near the camera; frame 355 the veil b267:01E01930 */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x3C10 - 0x2E0];
    Vec4f slot[5];
    u8 pad3C60[0x3DC0 - 0x3C60];
    Vec4f top;
    u8 pad3DD0[4];
    u8 col[4];
    u8 pad3DD8[0x3E1A - 0x3DD8];
    s16 joint;
    u8 pad3E1C[0x3E22 - 0x3E1C];
    s16 ang;
    u8 pad3E24[0x3E2E - 0x3E24];
    s16 t;
} Scene_b267_01E00260;

static void func_01E00260_b267(Scene_b267_01E00260 *g) {
    extern s32 func_0019A5C8(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F9D30(s32);
    extern s32 func_001A22C0(f32);
    extern s32 b267_01E02530();
    extern s32 b267_01E00A80();
    extern s32 b267_01E00BF0();
    extern s32 b267_01E00E50();
    extern s32 b267_01E00F90();
    extern s32 b267_01E01260();
    extern s32 b267_01E01500();
    extern s32 b267_01E01610();
    extern s32 b267_01E01740();
    extern s32 b267_01E01930();
    Vec4f p;
    s32 r[4];
    s32 q[4];
    f32 off;
    s16 rot;
    s32 i;

    func_001F6160(func_001F53A0(), r);
    rot = func_001A22C0(r[1] / 180.0f);
    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F5F90(func_001F53A0(), &p);
    if (g->t == 28 || g->t == 51 || g->t == 73 || g->t == 95 || g->t == 120) {
        if (rot) {
            if (g->t == 28) {
                g->pos.x = -3.0f;
            }
            if (g->t == 51) {
                g->pos.x = 3.0f;
            }
            if (g->t == 73) {
                g->pos.x = -2.0f;
            }
            if (g->t == 95) {
                g->pos.x = 2.0f;
            }
            if (g->t == 120) {
                g->pos.x = 0.0f;
            }
        } else {
            if (g->t == 28) {
                g->pos.x = 3.0f;
            }
            if (g->t == 51) {
                g->pos.x = -3.0f;
            }
            if (g->t == 73) {
                g->pos.x = 2.0f;
            }
            if (g->t == 95) {
                g->pos.x = -2.0f;
            }
            if (g->t == 120) {
                g->pos.x = 0.0f;
            }
        }
        if (g->t == 28) {
            off = 2.0f;
        }
        if (g->t == 51) {
            off = 2.0f;
        }
        if (g->t == 73) {
            off = -2.0f;
        }
        if (g->t == 95) {
            off = -2.0f;
        }
        if (g->t == 120) {
            off = 4.0f;
        }
        g->pos.y = p.y + off;
        g->pos.z = p.z;
        if (g->t == 28) {
            g->slot[0] = g->pos;
        }
        if (g->t == 51) {
            g->slot[1] = g->pos;
        }
        if (g->t == 73) {
            g->slot[2] = g->pos;
        }
        if (g->t == 95) {
            g->slot[3] = g->pos;
        }
        if (g->t == 120) {
            g->slot[4] = g->pos;
        }
        g->ang = 0;
        b267_01E02530(g, b267_01E00E50, 0);
        g->ang = 90;
        b267_01E02530(g, b267_01E00E50, 0);
        b267_01E02530(g, b267_01E01610, 0);
    }
    if (g->t == 125) {
        b267_01E02530(g, b267_01E01740, 0);
    }
    func_001F5620(func_001F53A0(), g->joint, &p);
    if (g->t == 150) {
        func_001F5620(func_001F53A0(), g->joint, &g->top);
    }
    if (g->t == 150) {
        func_001F6160(func_001F53A0(), q);
        for (i = 0; i < 1; i++) {
            g->pos.x = p.x;
            g->pos.y = p.y;
            g->pos.z = p.z;
            b267_01E02530(g, b267_01E00BF0, 0);
        }
    }
    if (g->t == 150) {
        g->pos.x = p.x;
        g->pos.y = p.y;
        g->pos.z = p.z;
        b267_01E02530(g, b267_01E00A80, 0);
    }
    func_001F9D30(0);
    if (g->t > 150 && g->t < 495) {
        g->pos.x = p.x;
        g->pos.y = p.y;
        g->pos.z = p.z;
        b267_01E02530(g, b267_01E00F90, 0);
    }
    if (g->t > 150 && g->t < 495) {
        g->pos.x = g->top.x;
        g->pos.y = g->top.y;
        g->pos.z = g->top.z;
        b267_01E02530(g, b267_01E01260, 0);
    }
    if (g->t > 250 && g->t < 495) {
        func_001F5F90(func_001F5380(), &p);
        g->pos.x = p.x + func_0019A5C8() % 30 - 15.0f;
        g->pos.y = p.y + func_0019A5C8() % 30 - 15.0f;
        g->pos.z = p.z;
        b267_01E02530(g, b267_01E01500, 0);
    }
    if (g->t == 355) {
        b267_01E02530(g, b267_01E01930, 0);
    }
}

/* shape b194:01E00C60, 134 insns, 2 copies: a violet wisp (b018:01E01F60 twin): set up once (random heading, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18, its frame every third up to 7; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x3E34];
    u8 trig[1];
} World_b194_01E00C60;

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
} Wisp_b194_01E00C60;

static s32 func_01E00860_b267(World_b194_01E00C60 *w, Wisp_b194_01E00C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
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
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b267:01E00A80, 92 insns: a dark smoke puff (size 90) at a random angle sinking 4 a tick to -30, turning 1: in by 8 up to 0xA0 for 20 ticks; out by 13 once the scene counter is under 20, and ends; from scene value 281 it spins 0x30 more a tick up to 0x600 and regrows by 4 to 90 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b267_01E00A80;

typedef struct {
    u8 pad[0x3DD0];
    s32 count;
    u8 pad3DD4[0x5A];
    s16 val;
} Game_b267_01E00A80;

static s32 func_01E00A80_b267(Game_b267_01E00A80 *g, Glow_b267_01E00A80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x1F, 0x1F, 0x1F);
    if (o->mode == 1) {
        o->f38 = 90;
        o->ang = func_0019A5C8() % 360;
        o->kind = 0;
        o->h30 = 0;
        o->mode = 2;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 8;
        }
    } else if (g->count < 20) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
    }
    if (g->val > 280) {
        if (o->ang < 0x600) {
            o->ang += 0x30;
        }
    }
    if (g->val > 280) {
        if (o->f38 < 90) {
            o->f38 += 4;
        } else {
            o->f38 = 90;
        }
    }
    if (o->h30 > -30) {
        o->h30 -= 4;
    }
    o->tick++;
    o->ang++;
    return 0;
}

/* shape b267:01E00BF0, 152 insns: a breathing grey glow: starts black, alpha up by 7 (to 0x90) and grey up by 4 (to 0x60)
   for 20 ticks; while the scene timer (0x3DD0) is above 20 it pulses its grey between 0x30 and 0xC0 by 4 a tick once
   its size reached 50, and below 20 it fades by 13; size grows by 2 to 50, and after scene frame 280 (0x3E2E) 0x3A
   grows by 0x30 to 0x600 and the size by 1 to 90 */

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 dir;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 h3A;
} Fx_b267_01E00BF0;

typedef struct {
    u8 pad0[0x3DD0];
    s32 timer;
    u8 pad3DD4[0x5A];
    s16 frame;
} Scene_b267_01E00BF0;

static s32 func_01E00BF0_b267(Scene_b267_01E00BF0 *g, Fx_b267_01E00BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 4;
        func_001076F0(o->col, 0, 0, 0);
        o->frame = 0;
        o->hE = 1;
        o->mode = 2;
    }
    if (o->t < 20) {
        if (o->col[3] < 0x90) {
            o->col[3] += 7;
        }
        if (o->col[0] < 0x60) {
            o->col[0] += 4;
        }
        if (o->col[1] < 0x60) {
            o->col[1] += 4;
        }
        if (o->col[2] < 0x60) {
            o->col[2] += 4;
        }
    }
    if (g->timer > 20) {
        if (o->dir == 0) {
            if (o->size >= 50) {
                if (o->col[0] < 0xC0) {
                    o->col[0] += 4;
                }
                if (o->col[1] < 0xC0) {
                    o->col[1] += 4;
                }
                if (o->col[2] < 0xC0) {
                    o->col[2] += 4;
                } else {
                    o->dir = 1;
                }
            }
        } else if (o->dir == 1) {
            if (o->col[0] > 0x30) {
                o->col[0] -= 4;
            }
            if (o->col[1] > 0x30) {
                o->col[1] -= 4;
            }
            if (o->col[2] > 0x30) {
                o->col[2] -= 4;
            } else {
                o->dir = 0;
            }
        }
    }
    if (g->timer < 20) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
    }
    if (o->size < 50) {
        o->size += 2;
    }
    if (g->frame > 0x118) {
        if (o->h3A < 0x600) {
            o->h3A += 0x30;
        }
    }
    if (g->frame > 0x118) {
        if (o->size < 90) {
            o->size++;
        }
    }
    o->t++;
    return 0;
}

/* shape b267:01E00E50, 77 insns: a blue column: frame 46, size 2 growing by 5 in height, direction from its angle; both alphas
   up by 0x40 for 2 frames, then down by 13 until the first runs out */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b267_01E00E50;

static s32 func_01E00E50_b267(void *arg0, Obj_b267_01E00E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x2E;
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->w = 2;
        o->h = 2;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
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
    if (o->dir == 0) {
        o->h += 5;
    } else {
        o->h += 5;
    }
    o->t++;
    return 0;
}

/* shape b267:01E00F90, 178 insns: b267:01E01260's smoke wisp in dark grey 0x2F (set every tick): random size 2..8, cap
   30..79, no scene angle; fades by 5 after tick 45; the rise goes to 13 before climbing by 4; the angle turns back by 2
   (3 from scene frame 280), and it fades by 12 once the scene timer is under 17 */

typedef struct {
    u8 pad0[6];
    s16 lean;
    u8 pad8[6];
    s16 cap;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 rise;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
    s16 ang;
} Wisp_b267_01E00F90;

typedef struct {
    u8 pad0[0x3DD0];
    s32 timer;
    u8 pad3DD4[0x5A];
    s16 frame;
} Scene_b267_01E00F90;

static s32 func_01E00F90_b267(Scene_b267_01E00F90 *g, Wisp_b267_01E00F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x2F, 0x2F, 0x2F);
    if (o->state == 1) {
        o->size = func_0019A5C8() % 7 + 2;
        o->ang = func_0019A5C8() % 360;
        o->lean = func_0019A5C8() % 2;
        o->frame = func_0019A5C8() % 7;
        o->rise = 0;
        o->cap = func_0019A5C8() % 50 + 30;
        o->state = 2;
    }
    if (o->t < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 20;
        }
    } else if (o->t > 45) {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->size < 5) {
            o->size++;
        }
    }
    if (o->lean < 10) {
        if (o->t % 2 == 1) {
            o->lean++;
        }
    } else {
        if (o->rise < 13) {
            o->rise++;
        } else {
            o->rise += 4;
            if (o->cap > o->size) {
                if (o->t % 2 == 1) {
                    o->size++;
                }
            }
        }
        if (o->ang < -359) {
            o->ang %= 360;
        }
    }
    if (g->frame < 280) {
        o->ang -= 2;
    } else {
        o->ang -= 3;
    }
    if (g->timer < 17) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b267:01E01260, 165 insns: a smoke wisp's step: on start it takes size 4, grey 0x16, the scene's angle (0x3E26),
   a random lean 0..1 and frame 0..6, a rise from -20 and a 70 size cap; alpha grows by 12 to 0x60 for 8 frames, then
   fades by 5 after frame 68 and by 12 once the scene timer is under 17; every other frame the size grows to 5 and the
   lean to 10; once leaned it rises to 6, then turns grey 0x30, climbs by 4 and keeps growing to the cap; the angle
   wraps under -359 and turns by 6 (back while still rising) */

typedef struct {
    u8 pad0[6];
    s16 lean;
    u8 pad8[6];
    s16 cap;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 rise;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
    s16 ang;
} Wisp_b267_01E01260;

typedef struct {
    u8 pad0[0x3DD0];
    s32 timer;
    u8 pad3DD4[0x52];
    s16 ang;
} Scene_b267_01E01260;

static s32 func_01E01260_b267(Scene_b267_01E01260 *g, Wisp_b267_01E01260 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 4;
        func_001076F0(o->col, 0x16, 0x16, 0x16);
        o->ang = g->ang;
        o->lean = func_0019A5C8() % 2;
        o->frame = func_0019A5C8() % 7;
        o->rise = -20;
        o->cap = 70;
        o->state = 2;
    }
    if (o->t < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else {
        if (o->t > 68) {
            if (o->col[3] > 6) {
                o->col[3] -= 5;
            } else {
                o->state = 0;
            }
        }
        if (g->timer < 17) {
            if (o->col[3] > 13) {
                o->col[3] -= 12;
            } else {
                o->state = 0;
            }
        }
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->size < 5) {
            o->size++;
        }
    }
    if (o->lean < 10) {
        if (o->t % 2 == 1) {
            o->lean++;
        }
    } else {
        if (o->rise < 6) {
            o->rise++;
        } else {
            func_001076F0(o->col, 0x30, 0x30, 0x30);
            o->rise += 4;
            if (o->cap > o->size) {
                if (o->t % 2 == 1) {
                    o->size++;
                }
            }
        }
        if (o->ang < -359) {
            o->ang %= 360;
        }
    }
    if (o->rise < 6) {
        o->ang -= 6;
    } else {
        o->ang += 6;
    }
    return 0;
}

/* shape b267:01E01500, 68 insns: a white spark of size 100 at a random frame that steps every other tick up to 7, growing 10 a tick: in by 24 up to 0x60 for 4 ticks, then out by 19 and ends */

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
} Glow_b267_01E01500;

static s32 func_01E01500_b267(s32 arg0, Glow_b267_01E01500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 100;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x18;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 != 0) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f38 += 10;
    o->tick++;
    return 0;
}

/* shape b267:01E01610, 75 insns: colour 0x4F grey; on start 0x38 = 6, random 0x3A, 0x34 = 2, size 1 (0x30); alpha
   grows by 0x14 (below 0xA0) for 8 ticks, then once the game step at 0x3E2E passes 0x96 fades by 5 and stops; the
   size grows for the first two ticks, then shrinks back to 2 */

typedef struct {
    u8 pad0[0x3E2E];
    s16 step;
} Game_b267_01E01610;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 size;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b267_01E01610;

static s32 func_01E01610_b267(Game_b267_01E01610 *g, Fx_b267_01E01610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x4F, 0x4F, 0x4F);
    if (o->mode == 1) {
        o->f38 = 6;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 2;
        o->size = 1;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x14;
        }
    } else if (g->step > 0x96) {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    if (o->tick < 3) {
        o->size++;
    } else if (o->size > 2) {
        o->size--;
    }
    return 0;
}

/* shape b267:01E01740, 55 insns: a grey flash: set up once (grey, frame 10), fades in by 6 for 20 frames, then once
   the game timer passes 0x96 fades out by 9 until it ends */

typedef struct {
    u8 pad0[0x3E2E];
    s16 timer;
} Game_b267_01E01740;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
} Obj_b267_01E01740;

static s32 func_01E01740_b267(Game_b267_01E01740 *g, Obj_b267_01E01740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->h34 = 0xA;
        o->state = 2;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 6;
        }
    } else if (g->timer > 0x96) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b194:01E01A20, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3DD0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3DD0];
    s32 state;
} Game_b194_01E01A20;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b194_01E01A20;

static s32 func_01E01820_b267(Game_b194_01E01A20 *g, Fade_b194_01E01A20 *o) {
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

static s32 func_01E018E0_b267(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03D00_b267;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03D08_b267;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b267:01E01930, 123 insns: a grey full-screen veil (b064:01E02F10 shape): alpha up by 4 to 0x30 for 12 frames, up by 8 to
   0x60 late in the scene, down by 12 once the scene timer drops under 17, gone when it hits 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b267_01E01930;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b267_01E01930 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b267_01E01930;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b267_01E01930;

typedef struct {
    u8 pad0[0x3DD0];
    s32 timer;
    u8 pad3DD4[0x5A];
    s16 t2;
} Scene_b267_01E01930;

static s32 func_01E01930_b267(Scene_b267_01E01930 *g, Obj_b267_01E01930 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b267_01E01930 pkt __attribute__((aligned(8)));

    ((Pkt_b267_01E01930 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b267_01E01930 *)(s32)&pkt)->tag = 5;
    ((Pkt_b267_01E01930 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b267_01E01930 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x80;
    pkt.b = 0x80;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b267_01E01930 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (o->t < 0xC) {
        if (o->c0[3] < 0x30) {
            o->c0[3] += 4;
        }
    }
    if (g->t2 >= 0x18C && g->timer > 0x11) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 8;
        }
    }
    if (g->timer < 0x11) {
        if (o->c0[3] > 0xD) {
            o->c0[3] -= 0xC;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (g->timer == 9) {
        o->state = 0;
    }
    return 0;
}

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

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
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E01B20_b267(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
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
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
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

/* shape b267:01E01DC0, 41 insns: look up the textures: group 4 cells 0-4, group 4 cells 14-15, group 5
   cells 0-1 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x320];
    s32 tex[16];
    u8 pad360[0x3A40];
    s32 tex5[2];
} Scene_b267_01E01DC0;

static void func_01E01DC0_b267(s32 arg0, Scene_b267_01E01DC0 *o) {
    s32 i;

    for (i = 0; i < 5; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01E70_b267);

/* shape b267:01E02530, 74 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3E2A and 0x3E22 and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b267_01E02530;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x204];
    Slot_b267_01E02530 s[220];
    u8 pad3BD4[0x200];
    u8 r, g, b, a;
    u8 pad3DD8[0x4A];
    s16 w;
    u8 pad3E24[0x6];
    s16 v;
} Pool_b267_01E02530;

static s32 func_01E02530_b267(Pool_b267_01E02530 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b267_01E02530 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 220; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 220;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b267:01E02660, 154 insns: a two-pass 0.1-scaled sprite strip: mode 0 sets the material (rect 1,1 126x62, mode 10,
   the object's colour, scene texture 0x3DA4); other modes place it at the object's position plus a tenth of its drift,
   turn it by the object's spin, and draw count x 2 quads (func_00108D60 with the size and the half), each mirrored in y */

typedef struct {
    s16 x, y, w, h;
} Rect_b267_01E02660;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[2];
    s16 dx;
    s16 dy;
    s16 dz;
    s16 count;
    u8 pad10[8];
    s32 spin;
    u8 pad1C[0xC];
    u8 c28[4];
    u8 pad2C[0xC];
    s16 size;
} Obj_b267_01E02660;

typedef struct {
    u8 pad0[0x3DA4];
    s32 texture;
} Game_b267_01E02660;

static void func_01E02660_b267(Game_b267_01E02660 *g, Obj_b267_01E02660 *o, void *p, s32 mode) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 q[16];
    Vec4f v;
    Vec4f sc;
    Rect_b267_01E02660 r[2];
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ctx;
    s16 i;
    s16 j;

    ctx = (s32)func_00207500();
    if (mode == 0) {
        r[0].x = 1;
        r[0].y = 1;
        r[0].w = 0x7E;
        r[0].h = 0x3E;
        func_00109270(p, 0, 0);
        func_00107790(p, o->c28, 0);
        func_00108500(p, r, 10);
        func_00208700(p, g->texture, 1);
    } else {
        func_00205C40((s32)rot);
        sc.x = 0.1f;
        sc.y = 0.1f;
        sc.z = 0.1f;
        v.x = o->x + o->dx / 10;
        v.y = o->y + o->dy / 10;
        v.z = o->z + o->dz / 10;
        rot[0] = 0;
        rot[1] = 0;
        rot[2] += o->spin;
        func_00108EF0(m, &sc, rot, &v);
        for (i = 0; i < o->count; i++) {
            for (j = 0; j < 2; j++) {
                func_00108D60(q, o->size, o->size, j);
                q[9] = -q[1];
                q[13] = -q[5];
                if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                    func_00109380(p, 0);
                    func_002075F0(p, ctx, (u32)depth[0]);
                }
            }
        }
    }
}

/* shape b267:01E028D0, 232 insns: a flat ring of 36 quads (10 apart on the trig table at g+0x3E34) from radius r to
   r + 20, the outer edge raised to the object's h30, scaled 0.1 at the object's position plus a tenth of its offset;
   mode 0 sets up the packet (additive blend 0x80/0x42, the object's two colours) */

typedef struct {
    f32 x, y, z, w;
} V4_b267_01E028D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 h8, hA, hC;
    u8 padE[0xA];
    s32 turn;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    u8 pad32[6];
    s16 r;
} Obj_b267_01E028D0;

typedef struct {
    u8 pad0[0x3E34];
    u8 trig[1];
} Game_b267_01E028D0;

static void func_01E028D0_b267(Game_b267_01E028D0 *g, Obj_b267_01E028D0 *o, void *p, s32 mode) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002086D0(void *, u64);
    extern void func_00107990(void *, void *, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    V4_b267_01E028D0 quad[4];
    V4_b267_01E028D0 pos;
    V4_b267_01E028D0 scale;
    f32 z[4];
    f32 m[16];
    s32 rot[4];
    s32 t;
    s16 i;
    s16 j;

    t = func_00207500();
    j = 0;
    if (mode == 0) {
        func_001092E0(p, 0);
        func_001094F0(p);
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        func_00107990(p, o->col, 1);
        func_00107990(p, o->col2, 2);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        pos.x = o->x + o->h8 / 10;
        pos.y = o->y + o->hA / 10;
        pos.z = o->z + o->hC / 10;
        func_00205C40(rot);
        rot[0] = 0;
        rot[1] = 0;
        rot[2] += o->turn;
        func_00108EF0(m, &scale, rot, &pos);
        for (i = 0; i < 36; i++) {
            quad[0].z = 0.0f;
            quad[0].x = o->r * func_00108030(g->trig, j, 0);
            quad[0].y = o->r * func_00108030(g->trig, j, 1);
            quad[1].z = 0.0f;
            quad[1].x = o->r * func_00108030(g->trig, j + 10, 0);
            quad[1].y = o->r * func_00108030(g->trig, j + 10, 1);
            quad[2].z = o->h30;
            quad[2].x = (o->r + 20) * func_00108030(g->trig, j, 0);
            quad[2].y = (o->r + 20) * func_00108030(g->trig, j, 1);
            quad[3].z = o->h30;
            quad[3].x = (o->r + 20) * func_00108030(g->trig, j + 10, 0);
            quad[3].y = (o->r + 20) * func_00108030(g->trig, j + 10, 1);
            if (func_00205630(quad, 0x70000000, m, p, z) != 0) {
                func_002075F0(p, t, -1);
            }
            j += 10;
        }
    }
}

/* shape b267:01E02C70, 170 insns: b573:01E04EE0's two-pass sprite for b267: mode 0 sets the material (frame 0x9B, or 0x14
   for objects run by b267:01E01610, the object's colour, scene texture 0x35C or 0x3DA0); other modes place it at the
   object plus a tenth of its drift (the depth keeps the y drift tenth twice divided, as in the original), turn it, and draw
   one quad for b267:01E01610 objects or repeat func_00108F90 for the others */

typedef struct {
    u8 pad0[0x35C];
    s32 tex0;
    u8 pad360[0x3A40];
    s32 tex1;
} Game_b267_01E02C70;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[2];
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x16];
    void *fn;
    u8 c28[4];
    u8 pad2C[4];
    s16 count;
    u8 pad32[2];
    s16 frame;
    u8 pad36[2];
    s16 size;
} Obj_b267_01E02C70;

static void func_01E02C70_b267(Game_b267_01E02C70 *g, Obj_b267_01E02C70 *o, void *p, s32 mode) {
    extern void b267_01E01610();
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108F90(void *, void *, void *, s32);
    f32 q[16];
    f32 v[4];
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 ctx;
    f32 f;
    s16 i;

    ctx = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x9B, o->frame, rm);
        if (o->fn == (void *)b267_01E01610) {
            func_00106080(rm, 0x14, o->frame, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->c28, 0);
        func_00108500(p, rm, 0);
        if (o->fn == (void *)b267_01E01610) {
            func_00208700(p, g->tex1, 1);
        } else {
            func_00208700(p, g->tex0, 1);
        }
    } else {
        func_00205C40((s32)rot);
        f = o->dx;
        f /= 10.0f;
        v[0] = o->x;
        v[0] += f;
        f = o->dy;
        f /= 10.0f;
        v[1] = o->y;
        v[1] += f;
        v[2] = o->dz;
        f /= 10.0f;
        v[2] = o->z;
        v[2] += f;
        sc.x = 0.1f;
        sc.y = 0.1f;
        sc.z = 0.1f;
        func_00108EF0(m, &sc, rot, v);
        func_00108CE0(q, o->size, o->size);
        if (o->fn == (void *)b267_01E01610) {
            if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                if (o->fn == (void *)b267_01E01610) {
                    func_00109380(p, 0);
                }
                func_002075F0(p, ctx, (u32)depth[0]);
            }
        } else {
            for (i = 0; i < o->count; i++) {
                func_00108F90(q, p, m, ctx);
            }
        }
    }
}

/* shape b267:01E02F20, 294 insns, 1 copy: b267:01E033C0's ring wall as three panels 120 apart: texture page 30, an
   additive blend (0x80, 0x42), the bottom edge 10 wide, the top edge from +4 to +14 one unit wider at height h + h6 */

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    u8 pad32[2];
    s16 sub;
    u8 pad36[2];
    s16 r;
    s16 ang;
} Obj_b267_01E02F20;

typedef struct {
    u8 pad0[0x32C];
    void *tex;
    u8 pad330[0x3E34 - 0x330];
    u8 sin[1];
} Scene_b267_01E02F20;

static void func_01E02F20_b267(Scene_b267_01E02F20 *g, Obj_b267_01E02F20 *o, void *pk, s32 mode) {
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002086D0(void *, s64);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f pos;
    s16 rect[8];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 cam[4];
    s32 ot;
    s32 side;
    s16 i;
    s16 a;
    s16 t;
    f32 d;

    ot = (s32)func_00207500();
    func_001F6160(func_001F53A0(), cam);
    side = (s16)(cam[1] / 180.0f);
    a = 0;
    if (mode == 0) {
        func_00106080(rect, 0x1E, o->sub, rect);
        func_00109270(pk, 0, 0);
        func_00107790(pk, o->col, 0);
        func_00108500(pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
        func_002086D0(pk, 0x8000000042LL);
        func_00205C40((s32)rot);
        rot[1] = 0;
        if (side != 0) {
            rot[0] = -0x4000;
        } else {
            rot[0] = 0x4000;
        }
        d = o->dx;
        d /= 10.0f;
        pos.x = o->x;
        pos.x += d;
        d = o->dy;
        d /= 10.0f;
        pos.y = o->y;
        pos.y += d;
        pos.z = o->dz;
        d /= 10.0f;
        pos.z = o->z;
        pos.z += d;
        func_00108EF0(m, NULL, rot, &pos);
        for (i = 0; i < 3; i++) {
            t = a;
            q[0].y = o->h;
            q[0].x = o->r * func_00108030(g->sin, o->ang + t, 0);
            q[0].z = o->r * func_00108030(g->sin, o->ang + t, 1);
            q[1].y = o->h;
            q[1].x = o->r * func_00108030(g->sin, t + (o->ang + 10), 0);
            q[1].z = o->r * func_00108030(g->sin, t + (o->ang + 10), 1);
            q[2].y = o->h + o->h6;
            q[2].x = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 4), 0);
            q[2].z = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 4), 1);
            q[3].y = o->h + o->h6;
            q[3].x = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 14), 0);
            q[3].z = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 14), 1);
            if (func_00205630(q, 0x70000000, m, pk, depth) != 0) {
                func_00109380(pk, 1);
                func_002075F0(pk, ot, 0);
            }
            a += 120;
        }
    }
}

/* shape b267:01E033C0, 284 insns, 1 copy: a six-panel ring wall: mode 0 builds the packet (texture page 20 frame from
   the object, its colour, the scene texture); otherwise it stands the ring up (turned -0x4000 or 0x4000 by the camera's
   side) at the object's point plus a tenth of its speed, and draws six panels 60 apart, 34 wide, from height h to
   h + 25, the top edge one unit wider */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    u8 pad32[2];
    s16 sub;
    u8 pad36[2];
    s16 r;
    s16 ang;
} Obj_b267_01E033C0;

typedef struct {
    u8 pad0[0x320];
    void *tex;
    u8 pad324[0x3E34 - 0x324];
    u8 sin[1];
} Scene_b267_01E033C0;

static void func_01E033C0_b267(Scene_b267_01E033C0 *g, Obj_b267_01E033C0 *o, void *pk, s32 mode) {
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f pos;
    s16 rect[8];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 cam[4];
    s32 ot;
    s32 side;
    s16 i;
    s16 a;
    s16 t;
    f32 d;

    ot = (s32)func_00207500();
    func_001F6160(func_001F53A0(), cam);
    side = (s16)(cam[1] / 180.0f);
    a = 0;
    if (mode == 0) {
        func_00106080(rect, 0x14, o->sub, rect);
        func_00109270(pk, 0, 0);
        func_00107790(pk, o->col, 0);
        func_00108500(pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        rot[1] = 0;
        if (side != 0) {
            rot[0] = -0x4000;
        } else {
            rot[0] = 0x4000;
        }
        d = o->dx;
        d /= 10.0f;
        pos.x = o->x;
        pos.x += d;
        d = o->dy;
        d /= 10.0f;
        pos.y = o->y;
        pos.y += d;
        pos.z = o->dz;
        d /= 10.0f;
        pos.z = o->z;
        pos.z += d;
        func_00108EF0(m, NULL, rot, &pos);
        for (i = 0; i < 6; i++) {
            t = a;
            q[0].y = o->h;
            q[0].x = o->r * func_00108030(g->sin, o->ang + t, 0);
            q[0].z = o->r * func_00108030(g->sin, o->ang + t, 1);
            q[1].y = o->h;
            q[1].x = o->r * func_00108030(g->sin, t + (o->ang + 34), 0);
            q[1].z = o->r * func_00108030(g->sin, t + (o->ang + 34), 1);
            q[2].y = o->h + 25;
            q[2].x = (o->r + 1) * func_00108030(g->sin, t + o->ang, 0);
            q[2].z = (o->r + 1) * func_00108030(g->sin, t + o->ang, 1);
            q[3].y = o->h + 25;
            q[3].x = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 34), 0);
            q[3].z = (o->r + 1) * func_00108030(g->sin, t + (o->ang + 34), 1);
            if (func_00205630(q, 0x70000000, m, pk, depth) != 0) {
                func_00109380(pk, 1);
                func_002075F0(pk, ot, 0);
            }
            a += 60;
        }
    }
}

/* shape b267:01E03830, 145 insns: b117:01E02C00 family sprite draw: texture 0x14 (0x50 and the second scene texture for callback b267:01E01610), position + speed/10 in integers, scaled 0.1 */

/* OVL_WARM */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x16];
    void *cb;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b267_01E03830;

typedef struct {
    u8 pad0[0x320];
    s32 tex;
    u8 pad324[0x1C];
    s32 tex2;
} Scene_b267_01E03830;

static void func_01E03830_b267(Scene_b267_01E03830 *g, Fx_b267_01E03830 *o, void *p, s32 lit) {
    extern void b267_01E01610(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    f32 z[4];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x14, o->h34, rm);
        if (o->cb == b267_01E01610) {
            func_00106080(rm, 0x50, o->h34, rm);
        }
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        if (o->cb == b267_01E01610) {
            func_00208700(p, g->tex2, 1);
            return;
        }
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, z) != 0) {
        if (o->cb == b267_01E01610) {
            func_00109380(p, 0);
        }
        func_002075F0((s32)p, v, (u32)z[0]);
    }
}

/* shape b267:01E03A80, 139 insns: draws the five edges of the scene's star (points at +0x3C10) as lines in the
   effect's colour: 4-1, 4-0, 1-3, 0-2, 3-2, each sent with the scene's line texture (0x3DDC) */

typedef struct {
    f32 x, y, z, w;
} V4_b267_01E03A80;

typedef struct {
    V4_b267_01E03A80 a;
    V4_b267_01E03A80 b;
} Line_b267_01E03A80;

typedef struct {
    u8 pad0[0x3C10];
    V4_b267_01E03A80 pt[5];
    u8 pad3C60[0x17C];
    s32 tex;
} Scene_b267_01E03A80;

static void func_01E03A80_b267(Scene_b267_01E03A80 *g, u8 *fx, void *pk) {
    extern void func_001091B0(void *, void *, void *);
    extern void func_00195108(void *, s32);
    extern void func_00109050(void *, void *, s32, s32);
    Line_b267_01E03A80 line;
    s32 i;

    func_001091B0(pk, fx + 0x28, fx + 0x28);
    for (i = 0; i < 5; i++) {
        func_00195108(&line, 0x20);
        if (i == 0) {
            line.a = g->pt[4];
            line.b = g->pt[1];
        }
        if (i == 1) {
            line.a = g->pt[4];
            line.b = g->pt[0];
        }
        if (i == 2) {
            line.a = g->pt[1];
            line.b = g->pt[3];
        }
        if (i == 3) {
            line.a = g->pt[0];
            line.b = g->pt[2];
        }
        if (i == 4) {
            line.a = g->pt[3];
            line.b = g->pt[2];
        }
        func_00109050(&line, pk, 0, g->tex);
    }
}
