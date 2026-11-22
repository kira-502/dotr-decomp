#include "common.h"

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

static s32 func_01E00080_c501(s32 arg0, Src_b000_01E00400 *c) {
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

/* shape c501:01E001E0, 459 insns, 2 copies: draws a frame of 4 gouraud quads around an object's 4 corner points (c610:01E00120
   family: outer edge pushed out by 1/6 in x and z only), and when the object's alpha is 0xFF a second frame of
   the plain corners against corners lifted by the object's height; visibility flagged on the object (bits
   20..23), drawn when all four project */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c501_01E001E0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    struct {
        u8 r, g, b, a;
        f32 q;
        Xyz_c501_01E001E0 p;
    } v[4];
    u8 tail[8];
} Pkt_c501_01E001E0;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 b, g, r, a;
    f32 h;
    Vec4f pts[4];
} Frame_c501_01E001E0;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_c501_01E001E0;

static s32 func_01E001E0_c501(s32 ot, Frame_c501_01E001E0 *o, Cam_c501_01E001E0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 d[4];
    Vec4f p;
    Pkt_c501_01E001E0 pkt __attribute__((aligned(8)));
    s32 k;
    s32 prev;

    ((Pkt_c501_01E001E0 *)(s32)&pkt)->count = 0x14;
    ((Pkt_c501_01E001E0 *)(s32)&pkt)->tag = 8;
    ((Pkt_c501_01E001E0 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_c501_01E001E0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.v[0].r = 0;
    pkt.v[0].g = 0;
    pkt.v[0].b = 0;
    pkt.v[0].a = o->a;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = 0;
    pkt.v[1].g = 0;
    pkt.v[1].b = 0;
    pkt.v[1].a = o->a;
    pkt.v[1].q = 1.0f;
    if (func_00104520(o->flags, 0xC) != 0) {
        pkt.v[2].r = func_0019A5C8() % 128;
        pkt.v[2].g = func_0019A5C8() % 128;
        pkt.v[2].b = func_0019A5C8() % 128;
        pkt.v[2].a = o->a;
        pkt.v[2].q = 1.0f;
        pkt.v[3].r = func_0019A5C8() % 128;
        pkt.v[3].g = func_0019A5C8() % 128;
        pkt.v[3].b = func_0019A5C8() % 128;
        pkt.v[3].a = o->a;
        pkt.v[3].q = 1.0f;
    } else {
        pkt.v[2].r = o->r;
        pkt.v[2].g = o->g;
        pkt.v[2].b = o->b;
        pkt.v[2].a = o->a;
        pkt.v[2].q = 1.0f;
        pkt.v[3].r = o->r;
        pkt.v[3].g = o->g;
        pkt.v[3].b = o->b;
        pkt.v[3].a = o->a;
        pkt.v[3].q = 1.0f;
    }
    for (k = 3; k > -1; k--) {
        if (k == 0) {
            prev = 3;
        } else {
            prev = k - 1;
        }
        p.x = o->pts[k].x + o->pts[k].x / 6.0f;
        p.y = o->pts[k].y;
        p.z = o->pts[k].z + o->pts[k].z / 6.0f;
        if (func_00205440(&p, cam->m, &pkt.v[0].p, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        p.x = o->pts[prev].x + o->pts[prev].x / 6.0f;
        p.y = o->pts[prev].y;
        p.z = o->pts[prev].z + o->pts[prev].z / 6.0f;
        if (func_00205440(&p, cam->m, &pkt.v[1].p, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        p.x = o->pts[k].x;
        p.y = o->pts[k].y;
        p.z = o->pts[k].z;
        if (func_00205440(&p, cam->m, &pkt.v[2].p, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        p.x = o->pts[prev].x;
        p.y = o->pts[prev].y;
        p.z = o->pts[prev].z;
        if (func_00205440(&p, cam->m, &pkt.v[3].p, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
    }
    if (o->a == 0xFF) {
        for (k = 3; k > -1; k--) {
            if (k == 0) {
                prev = 3;
            } else {
                prev = k - 1;
            }
            p.x = o->pts[k].x;
            p.y = o->pts[k].y + o->h;
            p.z = o->pts[k].z;
            if (func_00205440(&p, cam->m, &pkt.v[0].p, &d[0]) != 0) {
                o->flags |= 0x100000;
            }
            p.x = o->pts[prev].x;
            p.y = o->pts[prev].y + o->h;
            p.z = o->pts[prev].z;
            if (func_00205440(&p, cam->m, &pkt.v[1].p, &d[1]) != 0) {
                o->flags |= 0x200000;
            }
            p.x = o->pts[k].x;
            p.y = o->pts[k].y;
            p.z = o->pts[k].z;
            if (func_00205440(&p, cam->m, &pkt.v[2].p, &d[2]) != 0) {
                o->flags |= 0x400000;
            }
            p.x = o->pts[prev].x;
            p.y = o->pts[prev].y;
            p.z = o->pts[prev].z;
            if (func_00205440(&p, cam->m, &pkt.v[3].p, &d[3]) != 0) {
                o->flags |= 0x800000;
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
            o->flags &= 0xFF0FFFFF;
        }
    }
    return 0;
}

/* shape c501:01E00910, 165 insns, 1 copy: c501's scene manager: with a scene id (>= 0) it sets up the scene (60-frame
   countdown, grey colour, the sprite and its 24-scaled quad template, the camera view numbers); otherwise it steps
   it: from frame 8 it draws the sprite fading in by 16, grows the glow by 2 to 30 once full, fades the colour out in
   the last 8 frames; returns 2 on frame 32 and 8 when the countdown runs out. The scene comes in as `s32 arg0` cast
   to a local (puts g in s0 before ot) */

typedef struct Quad_c501_01E00910 {
    Vec4f v[4];
} Quad_c501_01E00910;

typedef struct Scene_c501_01E00910 {
    u8 pad0[0x20];
    Vec4f v20;
    u8 pad30[0x40];
    s32 w70;
    s32 w74;
    u8 col78[4];
    f32 glow;
    Vec4f quad[4];
    u8 padC0[0x40];
    u32 flags;
    s32 count;
    s32 frame;
    s32 id;
    s32 cam0;
    s32 cam1;
    u8 col[4];
} Scene_c501_01E00910;

static s32 func_01E00910_c501(s32 arg0, s32 id) {
    Scene_c501_01E00910 *g = (Scene_c501_01E00910 *)arg0;
    extern Quad_c501_01E00910 D_01E00C00_c501;
    extern s32 func_001F5380();
    extern s32 func_00103260();
    s32 t[4];
    Quad_c501_01E00910 q;
    s32 ot;
    s32 i;

    ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108((s32)g, 0x120);
        g->flags = 0;
        g->count = 60;
        g->frame = 0;
        g->id = id;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        g->col[3] = 0xFF;
        func_00103890(g);
        func_00103260(t, 0);
        g->w70 = t[0];
        g->w74 = 0;
        g->col78[2] = 0x40;
        g->col78[1] = 0x50;
        g->col78[0] = 0x60;
        g->col78[3] = 0;
        q = D_01E00C00_c501;
        for (i = 0; i < 4; i++) {
            g->quad[i].x = 24.0f * q.v[i].x;
            g->quad[i].y = q.v[i].y;
            g->quad[i].z = 24.0f * q.v[i].z;
        }
        g->glow = 0.0f;
        g->cam0 = func_001F5380() & 0xFF;
        g->cam1 = func_001F5380() >> 8;
        func_001E10F0(g->cam0, g->cam1, 0, &g->v20);
        return 0;
    }
    func_001038D0(g);
    if (g->count > 7) {
        func_01E001E0_c501(ot, (void *)&g->w70, (void *)g);
        if (g->col78[3] < 0xF0) {
            g->col78[3] += 16;
        } else {
            g->col78[3] = 0xFF;
        }
    }
    if (!func_00104520(g->flags, 0x1F)) {
        if (g->col78[3] == 0xFF) {
            if (g->glow < 30.0f) {
                g->glow += 2.0f;
            } else {
                g->glow = 30.0f;
            }
            if (g->count < 8) {
                if (!func_00103470(&g->col[3], 0, 0x20)) {
                    g->flags |= 0x80000000;
                }
                func_01E00080_c501(ot, (void *)g->col);
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 32) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
