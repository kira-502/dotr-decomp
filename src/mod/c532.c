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

static void func_01E00080_c532(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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
typedef struct W_ta_func_01E00120_c532 {
    Vec4f v[8];
} W_ta_func_01E00120_c532;

typedef struct W_tb_func_01E00120_c532 {
    Vec4f v[8];
} W_tb_func_01E00120_c532;

static s32 func_01E00120_c532(Model_b013_01E001A0 *m, Fx_b013_01E001A0 *o, s32 kind, f32 scale) {
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
            extern W_ta_func_01E00120_c532 D_01E01480_c532;
            W_ta_func_01E00120_c532 ta_w = D_01E01480_c532;

            for (i = 0; i < 8; i++) {
                o->v[i].x = sx * (o->scale * ta_w.v[i].x);
                o->v[i].y = sy * (o->scale * ta_w.v[i].y);
                o->v[i].z = o->scale * ta_w.v[i].z;
            }
        } else {
            extern W_tb_func_01E00120_c532 D_01E01500_c532;
            W_tb_func_01E00120_c532 tb_w = D_01E01500_c532;

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

static s32 func_01E00460_c532(s32 id, Model_b013_01E004E0 *m, Fx_b013_01E004E0 *o, Cam_b013_01E004E0 *cam) {
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
    func_01E00080_c532((Vtx_b000_01E00100 *)&pk, &m->col);
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

/* shape c532:01E01040 (c532), 263 insns, 1 copy: c532's scene manager (c514:01E01040 family) with three boards: with
   a scene id (>= 0) it clears the scene, sets a 20-frame countdown, binds the camera's model and sets up three sprite
   objects and rects (texture 6, anims at 50..59, scale 0.1, heights 10/20/30 or 40/50/60); otherwise it eases the
   scales to 1 for 12 ticks (the last board also eases the model and fades its colour), then grows them by 0.3 and
   fades them out; returns 8 when the countdown runs out */

typedef struct {
    f32 sc[3];
    u8 padC[4];
    s32 w10;
    u8 pad14[0xC];
    Vec4f pos;
    u8 pad30[0x40];
} Obj_c532_01E01040;

typedef struct {
    s32 v[4];
    u8 pad10[0x90];
} Anim_c532_01E01040;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    u8 col[4];
    s32 w38;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Rect_c532_01E01040;

typedef struct {
    Obj_c532_01E01040 obj[3];
    Anim_c532_01E01040 anim[3];
    Rect_c532_01E01040 rect[3];
    f32 p[3];
    u8 pad45C[4];
    u8 col[4];
    s32 model;
    s32 count;
    u8 pad46C[4];
    s32 tick;
} Scene_c532_01E01040;

extern void c532_01E00120(void *, void *, s32, f32);
extern void c532_01E00460(s32, void *, void *, void *);

static s32 func_01E01040_c532(s32 arg0, s32 id) {
    Scene_c532_01E01040 *g = (Scene_c532_01E01040 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_00103260(void *, s32);
    extern void func_001F53B0(s32, void *);
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_00103390(f32 *, f32, f32);
    extern void func_00103540(f32 *, f32, f32);
    extern void func_00103470(u8 *, s32, s32);
    extern void func_001032C0(u8 *, s32, s32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F6340(s32, f32 *);
    extern void func_001F62B0(s32, f32 *);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5E40(s32, u8 *);
    extern void func_001F5DE0(s32, u8 *);
    s32 t[4];
    s32 ot;
    s32 i;
    f32 one;

    ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x480);
        g->count = 20;
        g->tick = 0;
        g->model = func_001F5380();
        func_001F5970(g->model, 1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->obj[i]);
            if (*(u8 *)&g->model == 0) {
                func_001F53B0(1, &g->obj[i].pos);
            } else {
                func_001F53B0(0, &g->obj[i].pos);
            }
        }
        func_00103260(t, 6);
        for (i = 0; i < 3; i++) {
            g->rect[i].w38 = 1;
            g->rect[i].r[0] = 0;
            g->rect[i].r[1] = 0;
            g->rect[i].r[2] = 0x20;
            g->rect[i].r[3] = 0x20;
            g->rect[i].r[4] = 0;
            g->rect[i].r[5] = 0;
            g->rect[i].r[6] = 0x80;
            g->rect[i].r[7] = 0x40;
            g->rect[i].f30 = 1.0f;
            g->rect[i].col[0] = g->rect[i].col[1] = g->rect[i].col[2] = 0x80;
            g->rect[i].col[3] = 0x80;
            g->rect[i].h48 = 0;
            g->rect[i].h4A = 0;
            g->rect[i].h4E = 2;
            g->rect[i].h4C = g->rect[i].h4E - 1;
            g->rect[i].h50 = 0;
            g->rect[i].h52 = 999;
            g->anim[i].v[2] = 1;
            c532_01E00120(g->rect[i].r, &g->anim[i], t[0], 50.0f + func_0019A5C8() % 10);
            g->obj[i].sc[0] = g->obj[i].sc[1] = g->obj[i].sc[2] = 0.1f;
            g->obj[i].w10 = 0x4000;
            if (*(u8 *)&g->model > 5) {
                g->obj[i].pos.y = 10.0f * (i + 1);
            } else {
                g->obj[i].pos.y = 10.0f * (i + 4);
            }
        }
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->obj[i]);
        g->obj[i].w10 = 0x4000;
        c532_01E00460(ot, g->rect[i].r, &g->anim[i], &g->obj[i]);
        if (g->tick < 12) {
            one = 1.0f;
            func_00103390(&g->obj[i].sc[0], 1.0f, 0.2f);
            func_00103390(&g->obj[i].sc[1], 1.0f, 0.2f);
            func_00103390(&g->obj[i].sc[2], one, 0.2f);
            if (i == 2) {
                if (func_001F5EC0(g->model) != 0) {
                    func_001F6340(g->model, g->p);
                    func_00103390(&g->p[0], 1.0f, 0.3f);
                    func_00103390(&g->p[2], 1.0f, 0.3f);
                    func_00103540(&g->p[1], 1.0f, 0.6f);
                    func_001F62B0(g->model, g->p);
                }
                if (func_001F5AF0(g->model) != 0) {
                    func_001F5E40(g->model, g->col);
                    func_001032C0(&g->col[3], 0x80, 0x30);
                    func_001F5DE0(g->model, g->col);
                }
            }
        } else {
            g->obj[i].sc[0] += 0.3f;
            g->obj[i].sc[1] += 0.3f;
            g->obj[i].sc[2] += 0.3f;
            func_00103470(&g->rect[i].col[3], 0, 0x20);
        }
    }
    g->tick++;
    if (--g->count <= 0) {
        return 8;
    }
    return 0;
}

