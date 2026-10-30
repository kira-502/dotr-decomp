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

static void func_01E00080_c531(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b013:01E001A0, 205 insns, 40 copies: set up an 8-point effect outline (scale, aspect from the model's
   texture or size, one of two local point tables or random points) */

typedef struct Model_b013_01E001A0 {
    u8 pad0[4];
    s16 w;
    s16 h;
    f32 fw;
    f32 fh;
    u8 pad10[0x28];
    s32 tex;
} Model_b013_01E001A0;

typedef struct Fx_b013_01E001A0 {
    s32 kind;
    u8 pad4[4];
    s32 type;
    f32 scale;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    Vec4f v[8];
} Fx_b013_01E001A0;

#pragma optimization_level 3
typedef struct W_ta_func_01E00120_c531 {
    Vec4f v[8];
} W_ta_func_01E00120_c531;

typedef struct W_tb_func_01E00120_c531 {
    Vec4f v[8];
} W_tb_func_01E00120_c531;

static s32 func_01E00120_c531(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
    f32 sx;
    f32 sy;
    s32 i;

    o->f18 = 0.0f;
    o->f14 = 0.0f;
    o->f10 = 0.0f;
    o->scale = scale / 2.0f;
    o->kind = kind;
    if (func_00104520(m->tex, 0) != 0) {
        if (m->w > m->h) {
            sx = 1.0f;
            sy = (f32)m->h / (f32)m->w;
        } else if (m->w < m->h) {
            sx = (f32)m->h / (f32)m->w;
            sy = 1.0f;
        } else {
            sx = sy = 1.0f;
        }
    } else {
        if (!(m->fw <= m->fh)) {
            sy = m->fh / m->fw;
            sx = 1.0f;
        } else if (m->fw < m->fh) {
            sx = m->fh / m->fw;
            sy = 1.0f;
        } else {
            sx = sy = 1.0f;
        }
    }
    if (o->type != 3) {
        if (o->type == 5 || o->type == 6) {
            extern W_ta_func_01E00120_c531 D_01E01500_c531;
            W_ta_func_01E00120_c531 ta_w = D_01E01500_c531;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00120_c531 D_01E01580_c531;
            W_tb_func_01E00120_c531 tb_w = D_01E01580_c531;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * tb_w.v[i].x);
                o->v[i].y = sy * (o->scale * tb_w.v[i].y);
                o->v[i].z = o->scale * tb_w.v[i].z;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            o->v[i].x = func_0019A5C8() % 30 - 15;
            o->v[i].y = o->scale;
            o->v[i].z = func_0019A5C8() % 30 - 15;
        }
    }
    return 0;
}
#pragma optimization_level reset

/* func_00205440 is called unprototyped here */

/* shape b013:01E004E0, 757 insns, 40 copies: project the 8-point effect outline set up by b013:01E001A0 as
   quads (8 small squares for type 3, else 4 quads round the centre), flag what landed on screen and draw */

typedef struct Model_b013_01E004E0 {
    s16 x, y, w, h;
    u8 pad8[0x2C];
    Src_b000_01E00100 col;
    s32 tex;
} Model_b013_01E004E0;

typedef struct Fx_b013_01E004E0 {
    s32 kind;
    s32 flags;
    s32 type;
    f32 scale;
    Vec4f c;
    Vec4f v[8];
} Fx_b013_01E004E0;

typedef struct Cam_b013_01E004E0 {
    u8 pad0[0x30];
    u8 view[0x10];
} Cam_b013_01E004E0;

typedef struct Xyz_b013_01E004E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b013_01E004E0;

typedef struct Vtx_b013_01E004E0 {
    u8 rgbaq[8];
    u64 st;
    Xyz_b013_01E004E0 xyz;
} Vtx_b013_01E004E0;

typedef struct Pk_b013_01E004E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b013_01E004E0 v[4];
    u8 pad70[0x20];
} Pk_b013_01E004E0;

static inline void b013_01E004E0_tag(Pk_b013_01E004E0 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00460_c531(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
    extern s32 func_00205440();
    s32 i;
    f32 z[4];
    Vec4f pos;
    Pk_b013_01E004E0 pk;

    b013_01E004E0_tag((Pk_b013_01E004E0 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
    if (func_00104520(m->tex, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(m->tex, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c531((Vtx_b000_01E00100 *)&pk, &m->col);
    func_00104DC0(&pk, m);
    if (o->type == 3) {
        for (i = 0; i < 8; i++) {
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y + o->scale;
            pos.z = o->v[i].z;
            if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                o->flags |= 0x100000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y + o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                o->flags |= 0x200000;
            }
            pos.x = o->v[i].x - o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                o->flags |= 0x400000;
            }
            pos.x = o->v[i].x + o->scale;
            pos.y = o->v[i].y - o->scale;
            if (func_00205440(&pos, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                o->flags |= 0x800000;
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
                o->flags &= 0xFF0FFFFF;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (o->type == 1 || o->type == 5) {
                pos.x = o->c.x + o->v[i + i + 1].x;
                pos.y = o->c.y + o->v[i + i + 1].y;
                pos.z = o->c.z + o->v[i + i + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i < 2) {
                    pos.x = o->c.x + o->v[2].x;
                    pos.y = o->c.y + o->v[2].y;
                    pos.z = o->c.z + o->v[2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[6].x;
                    pos.y = o->c.y + o->v[6].y;
                    pos.z = o->c.z + o->v[6].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                if (i == 1 || i == 2) {
                    pos.x = o->c.x + o->v[4].x;
                    pos.y = o->c.y + o->v[4].y;
                    pos.z = o->c.z + o->v[4].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&pos, cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                        o->flags |= 0x400000;
                    }
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            } else if (o->type == 2 || o->type == 6) {
                pos.x = o->c.x + o->v[i * 2 + 1].x;
                pos.y = o->c.y + o->v[i * 2 + 1].y;
                pos.z = o->c.z + o->v[i * 2 + 1].z;
                if (func_00205440(&pos, cam->view, &pk.v[0].xyz, &z[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (i != 3) {
                    pos.x = o->c.x + o->v[i * 2 + 2].x;
                    pos.y = o->c.y + o->v[i * 2 + 2].y;
                    pos.z = o->c.z + o->v[i * 2 + 2].z;
                    if (func_00205440(&pos, cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                } else {
                    pos.x = o->c.x + o->v[0].x;
                    pos.y = o->c.y + o->v[0].y;
                    pos.z = o->c.z + o->v[0].z;
                    if (func_00205440(&o->v[0], cam->view, &pk.v[1].xyz, &z[1]) != 0) {
                        o->flags |= 0x200000;
                    }
                }
                pos.x = o->c.x + o->v[i * 2].x;
                pos.y = o->c.y + o->v[i * 2].y;
                pos.z = o->c.z + o->v[i * 2].z;
                if (func_00205440(&o->v[i * 2], cam->view, &pk.v[2].xyz, &z[2]) != 0) {
                    o->flags |= 0x400000;
                }
                if (func_00205440(&o->c, cam->view, &pk.v[3].xyz, &z[3]) != 0) {
                    o->flags |= 0x800000;
                }
            }
            if (func_00104520(m->tex, 0x18) != 0) {
                func_00208700(&pk, (void *)o->kind, 0);
            } else {
                if (func_00104520(m->tex, 0) != 0) {
                    func_00208CB0(&pk, (u64)2 | ((u64)2 << 2) | ((u64)m->x << 4) | ((u64)(m->x + m->w - 1) << 14) |
                                           ((u64)m->y << 24) | ((u64)(m->y + m->h - 1) << 34));
                }
                func_00208700(&pk, (void *)o->kind, 1);
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                if (func_00104520(m->tex, 0x13) != 0) {
                    pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0((s32)&pk, id, 0);
                } else {
                    func_002075F0((s32)&pk, id, (u32)((z[0] + z[1] + z[2] + z[3]) / 4.0f));
                }
            }
            o->flags &= 0xFF0FFFFF;
        }
    }
    return 0;
}

/* shape c531:01E01040 (c531), 273 insns, 1 copy: the c531 module's main step: with a code it clears the scene, keeps
   a 20-tick timer and the target model (busy), and sets up three animated boards: each coordinate gets the effect
   position (from the target or, for model 0, the other side), scale 2.6, turn 0x4000 and a height of 10 x (k + 1)
   (models past 5) or 10 x (k + 4); each board's animation is rect 32 x 32 from a 128 x 64 sheet, grey, 2 frames,
   texture 6, set up by c531:01E00120 at size 50..59; otherwise it draws the boards (c531:01E00460) fading them in by
   0x20 and growing for 12 ticks, then shrinking by 0.2 and fading out, and on the last board it squashes the model
   (scale x/z down by 0.3, y up by 0.6) and fades the card by 0x30; returns 2 on tick 17 and 8 when the timer ends */

typedef struct {
    f32 sx, sy, sz;
    u8 padC[4];
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c531_01E01040;

typedef struct {
    u8 pad0[8];
    s32 w8;
    u8 padC[0x94];
} Board_c531_01E01040;

typedef struct {
    s16 rect[8];
    u8 pad10[0x20];
    f32 f30;
    u8 b, g, r, a;
    s32 w38;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Anim_c531_01E01040;

typedef struct {
    Crd_c531_01E01040 crd[3];
    Board_c531_01E01040 board[3];
    Anim_c531_01E01040 anim[3];
    f32 msc[4];
    u8 crgba[4];
    s32 model;
    s32 timer;
    u8 pad46C[4];
    s32 tick;
} Scene_c531_01E01040;

extern void c531_01E00120(Anim_c531_01E01040 *, Board_c531_01E01040 *, s32, f32);
extern void c531_01E00460(s32, Anim_c531_01E01040 *, Board_c531_01E01040 *, Crd_c531_01E01040 *);

static s32 func_01E01040_c531(s32 arg0, s32 code) {
    Scene_c531_01E01040 *g = (Scene_c531_01E01040 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_00103890(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_001038D0(void *);
    extern void func_001032C0(void *, u32, u32);
    extern void func_00103540(void *, f32, f32);
    extern void func_00103470(void *, u32, s32);
    extern void func_00103390(void *, f32, f32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F6340(s32, void *);
    extern void func_001F62B0(s32, void *);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    f32 one;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x480);
        g->timer = 20;
        g->tick = 0;
        g->model = func_001F5380();
        func_001F5970(g->model, 1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->crd[i]);
            if ((u8)g->model == 0) {
                func_001F53B0(1, &g->crd[i].pos);
            } else {
                func_001F53B0(0, &g->crd[i].pos);
            }
        }
        func_00103260(&tex, 6);
        for (i = 0; i < 3; i++) {
            g->anim[i].w38 = 1;
            g->anim[i].rect[0] = 0;
            g->anim[i].rect[1] = 0;
            g->anim[i].rect[2] = 0x20;
            g->anim[i].rect[3] = 0x20;
            g->anim[i].rect[4] = 0;
            g->anim[i].rect[5] = 0;
            g->anim[i].rect[6] = 0x80;
            g->anim[i].rect[7] = 0x40;
            g->anim[i].f30 = 1.0f;
            g->anim[i].r = 0x80;
            g->anim[i].g = 0x80;
            g->anim[i].b = 0x80;
            g->anim[i].a = 0;
            g->anim[i].h48 = 0;
            g->anim[i].h4A = 0;
            g->anim[i].h4E = 2;
            g->anim[i].h4C = g->anim[i].h4E - 1;
            g->anim[i].h50 = 0;
            g->anim[i].h52 = 999;
            g->board[i].w8 = 1;
            c531_01E00120(&g->anim[i], &g->board[i], tex, 50.0f + func_0019A5C8() % 10);
            g->crd[i].sx = g->crd[i].sy = g->crd[i].sz = 2.6f;
            g->crd[i].rot[0] = 0x4000;
            if ((u8)g->model > 5) {
                g->crd[i].pos.y = 10.0f * (i + 1);
            } else {
                g->crd[i].pos.y = 10.0f * (i + 4);
            }
        }
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->crd[i]);
        g->crd[i].rot[0] = 0x4000;
        c531_01E00460(ot, &g->anim[i], &g->board[i], &g->crd[i]);
        if (g->tick < 12) {
            func_001032C0(&g->anim[i].a, 0x80, 0x20);
            one = 1.0f;
            func_00103540(&g->crd[i].sx, 1.0f, 0.3f);
            func_00103540(&g->crd[i].sy, one, 0.3f);
            func_00103540(&g->crd[i].sz, 1.0f, 0.3f);
        } else {
            g->crd[i].sx -= 0.2f;
            g->crd[i].sy -= 0.2f;
            g->crd[i].sz -= 0.2f;
            func_00103470(&g->anim[i].a, 0, 0x20);
            if (i == 2) {
                if (func_001F5EC0(g->model) != 0) {
                    func_001F6340(g->model, g->msc);
                    func_00103540(&g->msc[0], 0.0f, 0.3f);
                    func_00103540(&g->msc[2], 0.0f, 0.3f);
                    func_00103390(&g->msc[1], 3.0f, 0.6f);
                    func_001F62B0(g->model, g->msc);
                }
                if (func_001F5AF0(g->model) != 0) {
                    func_001F5E40(g->model, g->crgba);
                    func_00103470(&g->crgba[3], 0, 0x30);
                    func_001F5DE0(g->model, g->crgba);
                }
            }
        }
    }
    g->tick++;
    g->timer--;
    if (g->tick == 17) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

