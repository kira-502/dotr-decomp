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

static void func_01E00080_c611(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b000:01E00400, 87 insns, 46 copies: one flat-coloured full-screen quad (GS sprite packet, far z). The tag
   is written through a pointer that went through u32 (a plain &pk gets folded into $sp offsets). */

typedef struct Xyz_b000_01E00400 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b000_01E00400;

typedef struct Pk_b000_01E00400 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00400 v[4];
} Pk_b000_01E00400;

typedef struct Src_b000_01E00400 {
    u8 b, g, r, a;
} Src_b000_01E00400;

static inline void b000_01E00400_tag(Pk_b000_01E00400 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00120_c611(s32 arg0, Src_b000_01E00400 *c) {
    Pk_b000_01E00400 pk;

    b000_01E00400_tag((Pk_b000_01E00400 *)(u32)&pk, 5, 4, 0x44441);
    func_002086D0((Pk_b000_01E00400 *)(u32)&pk, ((u64)0x80 << 32) | 0x48);
    pk.r = c->r;
    pk.g = c->g;
    pk.b = c->b;
    pk.a = c->a;
    pk.q = 1.0f;
    pk.v[0].x = 0x6000;
    pk.v[0].y = 0x7000;
    pk.v[0].z = 0xFFFFFF;
    pk.v[0].fog = 0;
    pk.v[1].x = 0xA000;
    pk.v[1].y = 0x7000;
    pk.v[1].z = 0xFFFFFF;
    pk.v[1].fog = 0;
    pk.v[2].x = 0x6000;
    pk.v[2].y = 0x9000;
    pk.v[2].z = 0xFFFFFF;
    pk.v[2].fog = 0;
    pk.v[3].x = 0xA000;
    pk.v[3].y = 0x9000;
    pk.v[3].z = 0xFFFFFF;
    pk.v[3].fog = 0;
    func_002075F0((s32)&pk, arg0, 0);
    return 0;
}

/* shape b025:01E016F0, 509 insns, 17 copies: draws a cloud of sprite quads whose offsets follow a wave table: per point,
   amplitude from |tab[i]| / 10, x/y/z from tab[k], tab[k+1], tab[k+2] (or their absolute values, or 0, per
   flag bits), scaled by the frame count; depth-sorted unless flag 0x13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E016F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b025_01E016F0;

typedef struct {
    u64 uv;
    Xyz_b025_01E016F0 p;
} Vtx_b025_01E016F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E016F0 v[4];
    u8 tail[0x20];
} Pk_b025_01E016F0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b8, b9, bA, bB;
    s8 *tab;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 size;
    f32 amp;
    s16 count;
    s16 frame;
    u8 phase;
} Wave_b025_01E016F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E016F0;

static s32 func_01E00280_c611(s32 obj, Wave_b025_01E016F0 *w, Cam_b025_01E016F0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00195070(s32);
    Vec4f pos;
    f32 depth[4];
    Pk_b025_01E016F0 pk __attribute__((aligned(8)));
    s32 i;
    s32 k;
    f32 amp;
    f32 x;
    f32 y;
    f32 z;

    if (w->frame > 0) {
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags = 0x24;
        ((Pk_b025_01E016F0 *)(s32)&pk)->size = 9;
        ((Pk_b025_01E016F0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b025_01E016F0 *)(s32)&pk)->pad4 = 0;
        if (func_00104520(w->flags, 0xC) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
        } else if (func_00104520(w->flags, 0xB) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
        } else if (func_00104520(w->flags, 0xA) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
        } else {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
        }
        pk.r = w->bA;
        pk.g = w->b9;
        pk.b = w->b8;
        pk.a = w->bB;
        pk.q = 1.0f;
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags |= 0x800;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->v = (w->v + w->h - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->v = (w->v + w->h - 1) * 16;
        for (i = 0; i < w->count; i++) {
            k = (u8)(w->phase + i);
            amp = w->amp * (0.1f * func_00195070(w->tab[i]));
            if (w->flags & 0x08000000) {
                x = 0.0f;
            } else if (w->flags & 0x01000000) {
                x = w->frame * (amp * func_00195070(w->tab[(u8)k]));
            } else {
                x = w->frame * (amp * w->tab[(u8)k]);
            }
            if (w->flags & 0x10000000) {
                y = 0.0f;
            } else if (w->flags & 0x02000000) {
                y = w->frame * (amp * func_00195070(w->tab[(u8)(k + 1)]));
            } else {
                y = w->frame * (amp * w->tab[(u8)(k + 1)]);
            }
            if (w->flags & 0x20000000) {
                z = 0.0f;
            } else if (w->flags & 0x04000000) {
                z = w->frame * (amp * func_00195070(w->tab[(u8)(k + 2)]));
            } else {
                z = w->frame * (amp * w->tab[(u8)(k + 2)]);
            }
            pos.x = x - w->size;
            pos.y = y + w->size;
            pos.z = z;
            if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
                w->flags |= 0x100000;
            }
            pos.x = x + w->size;
            pos.y = y + w->size;
            if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
                w->flags |= 0x200000;
            }
            pos.x = x - w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
                w->flags |= 0x400000;
            }
            pos.x = x + w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[3]) != 0) {
                w->flags |= 0x800000;
            }
            func_00208700(&pk, w->texture, 0);
            if (func_00104520(w->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else if (func_00104520(w->flags, 0x14) != 0 && func_00104520(w->flags, 0x15) != 0 &&
                       func_00104520(w->flags, 0x16) != 0 && func_00104520(w->flags, 0x17) != 0) {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
            w->flags &= 0xFF0FFFFF;
        }
    }
    w->frame++;
    return 0;
}

/* shape c611:01E00A80, 369 insns, 2 copies (LkSortSlash): b000:01E03420's sprite quad for a slash: blend by flags 11/10,
   colour into the four vertices, UVs from the integer or float rectangle; the two lower corners slide in y toward
   -10 x the slash's scale at 4 x the scale a frame; one matrix from the slash's rotation, each corner projected
   (flags 20..23 when on screen); flag 19 draws it at the far z, else all four on screen draw at their mean depth */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c611_01E00A80;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_c611_01E00A80;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c611_01E00A80 v[4];
    u8 tail[0x20];
} Pkt_c611_01E00A80;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    f32 scale;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec4f p[4];
    Vec4f rot[1];
} Slash_c611_01E00A80;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c611_01E00A80;

static s32 func_01E00A80_c611(s32 obj, Slash_c611_01E00A80 *spr, Cam_c611_01E00A80 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00103540(void *, f32, f32);
    Vec4f out;
    f32 m[16];
    f32 depth[4];
    f32 step;
    Pkt_c611_01E00A80 pkt;

    ((Pkt_c611_01E00A80 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c611_01E00A80 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c611_01E00A80 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c611_01E00A80 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c611((Vtx_b000_01E00100 *)&pkt, &spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_c611_01E00A80 *)(s32)&pkt)->count |= 0x800;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_c611_01E00A80 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = spr->rect.f.s;
        pkt.v[0].tc.st.t = spr->rect.f.t;
        pkt.v[1].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[1].tc.st.t = spr->rect.f.t;
        pkt.v[2].tc.st.s = spr->rect.f.s;
        pkt.v[2].tc.st.t = spr->rect.f.t + spr->rect.f.h;
        pkt.v[3].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[3].tc.st.t = spr->rect.f.t + spr->rect.f.h;
    }
    func_00103540(&spr->p[2].y, -10.0f * spr->scale, 4.0f * spr->scale);
    step = 4.0f * spr->scale;
    func_00103540(&spr->p[3].y, -10.0f * spr->scale, step);
    func_0020C630(m, spr->rot);
    func_0020CDD0(&out, m, &spr->p[0]);
    if (func_00205440(&out, cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
        spr->flags |= 0x100000;
    }
    func_0020CDD0(&out, m, &spr->p[1]);
    if (func_00205440(&out, cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
        spr->flags |= 0x200000;
    }
    func_0020CDD0(&out, m, &spr->p[2]);
    if (func_00205440(&out, cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
        spr->flags |= 0x400000;
    }
    func_0020CDD0(&out, m, &spr->p[3]);
    if (func_00205440(&out, cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
        spr->flags |= 0x800000;
    }
    func_00208700(&pkt, spr->texture, 0);
    if (func_00104520(spr->flags, 0x13) != 0) {
        pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
        func_002075F0(&pkt, obj, 0);
    } else if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
               func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
        func_002075F0(&pkt, obj, func_001A23B0((depth[3] + (depth[2] + (depth[0] + depth[1]))) / 4.0f));
    }
    spr->flags &= 0xFF0FFFFF;
    return 0;
}

/* shape c611:01E01050 (c611), 207 insns, 1 copy: the c611 scene manager: on a code (>= 0) clears the scene (0x2A0),
   sets up the slash (texture 15, rect 0x8E,0 0x22x0x40, corners = 20 x the module table, z turn -0x3000), a 256-entry
   random wave table and the wave cloud (rect 0xB0,0x40 32x32, size 3, amp 0.1), a 60-tick timer; else flickers both
   colours randomly, from tick 5 draws the flash, the wave cloud and fades them, draws the slash, returns 8 when the
   timer runs out */

typedef struct Tbl_c611_01E01050 {
    Vec4f v[4];
} Tbl_c611_01E01050;

typedef struct Sl_c611_01E01050 {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    s32 rot[4];
} Sl_c611_01E01050;

typedef struct Scene_c611_01E01050 {
    u8 cam[0x70];
    Wave_b025_01E016F0 w;
    f32 cam2[4];
    u8 padB0[0x60];
    Sl_c611_01E01050 sl;
    Src_b000_01E00400 col;
    s32 flags;
    s32 timer;
    s32 code;
    s32 t;
    s8 tab[0x100];
    u8 pad294[0xC];
} Scene_c611_01E01050;

static s32 func_01E01050_c611(s32 arg0, s32 code) {
    Scene_c611_01E01050 *g = (Scene_c611_01E01050 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_00103920(void *, f32, f32);
    extern s32 func_00103470(void *, s32, s32);
    extern Tbl_c611_01E01050 D_01E01400_c611;
    s32 tex __attribute__((aligned(16)));
    Tbl_c611_01E01050 tbl;
    s32 ot;
    s32 i;
    void *texp;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2A0);
        func_00103890(g);
        func_00103890(g->cam2);
        g->flags = 0;
        g->timer = 60;
        g->code = code;
        g->t = 0;
        g->col.b = g->col.g = g->col.r = 0x80;
        g->col.a = 0xFF;
        func_00103260(&tex, 15);
        g->sl.flags = 0x80001;
        g->sl.u = 0x8E;
        g->sl.v = 0;
        g->sl.w = 0x22;
        g->sl.h = 0x40;
        g->sl.color.g = g->sl.color.r = 0x80;
        g->sl.color.b = 0xE0;
        g->sl.color.a = 0x80;
        texp = (void *)tex;
        tbl = D_01E01400_c611;
        g->sl.scale = 20.0f;
        g->sl.texture = texp;
        for (i = 0; i < 4; i++) {
            g->sl.p[i].x = g->sl.scale * tbl.v[i].x;
            g->sl.p[i].y = g->sl.scale * tbl.v[i].y;
            g->sl.p[i].z = g->sl.scale * tbl.v[i].z;
        }
        g->sl.rot[2] = -0x2000;
        g->sl.rot[2] = -0x3000;
        for (i = 0; i < 0x100; i++) {
            g->tab[i] = func_0019A5C8() >> 4;
        }
        g->w.texture = (void *)tex;
        g->w.tab = g->tab;
        g->w.flags = 0x20080000;
        g->w.u = 0xB0;
        g->w.v = 0x40;
        g->w.w = 0x20;
        g->w.h = 0x20;
        g->w.bA = 0x80;
        g->w.b9 = 0x80;
        g->w.b8 = 0x80;
        g->w.bB = 0x80;
        g->w.size = 3.0f;
        g->w.amp = 0.1f;
        g->w.frame = 0;
        g->w.count = 0x100;
        g->w.phase = i + 7;
        g->cam2[0] = 2.0f;
        g->cam2[2] = 1.0f;
        g->cam2[1] = 1.0f;
        return 0;
    }
    func_00103920(g, 0.0f, 0.0f);
    func_00103920(g->cam2, 80.0f, 0.0f);
    g->sl.color.r = g->w.bA = func_0019A5C8() % 255;
    g->sl.color.g = g->w.b9 = func_0019A5C8() % 255;
    g->sl.color.b = g->w.b8 = func_0019A5C8() % 255;
    if (g->t >= 5) {
        func_01E00120_c611(ot, &g->col);
        func_00103470(&g->col.a, 0, 8);
        func_00103470(&g->sl.color.a, 0, 8);
        func_01E00280_c611(ot, &g->w, (Cam_b025_01E016F0 *)g);
        func_00103470(&g->w.bB, 0, 8);
    }
    func_01E00A80_c611(ot, (Slash_c611_01E00A80 *)&g->sl, (Cam_c611_01E00A80 *)g->cam2);
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

