#include "common.h"

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00080_b489(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

/* shape b489:01E00240 (LkPrim_SortLineParticle), 853 insns, 55 copies: each live particle drawn as a camera-facing
   line quad from its position back along its direction (or straight down), texture-animated */

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b489_01E00240;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b489_01E00240;

typedef struct {
    UV_b489_01E00240 uv;
    Xyz_b489_01E00240 xyz;
} Vtx_b489_01E00240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b489_01E00240 v[4];
    u8 tail[0x20];
} Pkt_b489_01E00240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 age;
} Part_b489_01E00240;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    u8 pad28[4];
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b489_01E00240;

#define UV_b489_01E00240(k) ((UV_b489_01E00240 *)(s32)&pkt.v[k].uv)

static s32 func_01E00240_b489(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_0020D070(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C60(f32);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f t;
    Xyz_b489_01E00240 q[2];
    Pkt_b489_01E00240 pkt __attribute__((aligned(8)));
    f32 dep[2];
    s32 i;
    f32 w;
    f32 dx;
    f32 dy;

    ((Pkt_b489_01E00240 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->tag = 9;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->r;
    pkt.g = e->g;
    pkt.b = e->b;
    pkt.a = e->a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
        UV_b489_01E00240(0)->u = e->u << 4;
        UV_b489_01E00240(0)->v = e->v << 4;
        UV_b489_01E00240(1)->u = e->u << 4;
        UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
        UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(2)->v = e->v << 4;
        UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
    }
    for (i = 0; i < e->count; i++) {
        if (e->parts[i].age >= 0) {
            if (e->parts[i].a < e->a) {
                pkt.a = e->parts[i].a;
            } else {
                pkt.a = e->a;
            }
            if (func_00104520(e->flags, 3) == 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->u = e->u0 + e->w * (e->parts[i].frame % (e->tw / e->w));
                    e->v = e->v0 + e->h * (e->parts[i].frame / (e->tw / e->w));
                } else {
                    e->u = e->u0 + e->w * (e->parts[i].frame / (e->th / e->h));
                    e->v = e->v0 + e->h * (e->parts[i].frame % (e->th / e->h));
                }
                ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
                UV_b489_01E00240(0)->u = e->u << 4;
                UV_b489_01E00240(0)->v = e->v << 4;
                UV_b489_01E00240(1)->u = e->u << 4;
                UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
                UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(2)->v = e->v << 4;
                UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
            }
            if (func_00104520(e->flags, 0x1E) != 0) {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y - e->len;
                t.z = e->parts[i].z;
            } else {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y;
                t.z = e->parts[i].z;
                func_0020D070(&t);
                t.x *= -e->len;
                t.y *= -e->len;
                t.z *= -e->len;
                t.x += e->parts[i].x;
                t.y += e->parts[i].y;
                t.z += e->parts[i].z;
            }
            if (func_00205440(&e->parts[i], cam->view, &q[0], &dep[0]) != 0 && func_00101600(&q[0]) != 0) {
                e->flags |= 0x100000;
            }
            if (func_00205440(&t, cam->view, &q[1], &dep[1]) != 0 && func_00101600(&q[1]) != 0) {
                e->flags |= 0x200000;
            }
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0) {
                dx = func_001A6970(q[0].x - q[1].x);
                dy = func_001A6970(q[0].y - q[1].y);
                w = func_001A6C60(dx * dx + dy * dy);
                w = w * e->width / e->len;
                if (dx > dy) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = q[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = q[1].x;
                    pkt.v[0].xyz.y = (u32)(q[0].y - w);
                    pkt.v[1].xyz.y = (u32)(q[1].y - w);
                    pkt.v[2].xyz.y = (u32)(q[0].y + w);
                    pkt.v[3].xyz.y = (u32)(q[1].y + w);
                } else {
                    pkt.v[0].xyz.x = (u32)(q[0].x - w);
                    pkt.v[1].xyz.x = (u32)(q[1].x - w);
                    pkt.v[2].xyz.x = (u32)(q[0].x + w);
                    pkt.v[3].xyz.x = (u32)(q[1].x + w);
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = q[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = q[1].y;
                }
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = q[0].z;
                if (func_00104520(e->flags, 0) != 0) {
                    func_00208CB0(&pkt, 0xA | ((s64)e->u << 4) | ((s64)(e->u + e->w - 1) << 14) |
                                            ((s64)e->v << 24) | ((s64)(e->v + e->h - 1) << 34));
                }
                func_00208700(&pkt, e->texture, 1);
                if (func_00104520(e->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1]) / 2.0f));
                }
            }
            e->flags &= 0xFFCFFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->parts[i].age++;
            if (e->parts[i].age % e->rate == 0) {
                e->parts[i].frame++;
                if (e->nframes == e->parts[i].frame) {
                    e->parts[i].frame = 0;
                }
            }
        }
    }
    return 0;
}

/* shape b489:01E00FA0 (b489), 378 insns, 1 copy: b489 scene manager: setup (a 256-point line-particle fountain
   scattered on a ring), then the joints and colour flashes between frames 0x5C and 0xEB, the particles drawn, risen
   and respawned above 200 */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Pt_b489_01E00FA0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Pt_b489_01E00FA0 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    f32 radius;
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00FA0;

typedef struct {
    u8 crd[0x70];
    Vec4f scale;
    Vec4f dir;
    Vec4f joint;
    u8 padA0[0x40];
    Emit_b489_01E00FA0 emit;
    Pt_b489_01E00FA0 pts[256];
    u8 crd2[0x20];
    Vec4f v1130;
    u8 pad1140[0x40];
    u8 crd3[0x20];
    Vec4f v11A0;
    u8 pad11B0[0x40];
    Vec4f v11F0;
    s32 count;
    s32 frame;
    s32 id;
    u8 col[4];
    s32 jA;
    u8 b1214;
    u8 pad1215[0xB];
} Scene_b489_01E00FA0;

static s32 func_01E00FA0_b489(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern u8 *func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6580(s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, u8);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern s32 b489_01E00240();
    Scene_b489_01E00FA0 *g = (Scene_b489_01E00FA0 *)arg0;
    u8 *ot;
    Vec4f t[2];
    s32 tex[4];
    s32 i;
    s32 a;
    f32 r;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1220);
        func_00103890(g);
        func_00103890(g->crd2);
        func_00103890(&g->scale);
        func_00103890(g->crd3);
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->count = 0x100;
        g->frame = 1;
        g->id = code;
        g->b1214 = 0x80;
        g->col[3] = 0x80;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        func_00103290(tex, 0);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x60000003;
        g->emit.r = 0x80;
        g->emit.g = 0x80;
        g->emit.b = 0x80;
        g->emit.a = 0;
        g->emit.width = 0.2f;
        g->emit.len = 22.0f;
        g->emit.u = 0;
        g->emit.v = 0;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0;
        g->emit.v0 = 0;
        g->emit.tw = 0x80;
        g->emit.th = 0x40;
        g->emit.parts = g->pts;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        func_01E00080_b489((Obj_b015_01E01620 *)&g->emit, 0xC, r = 3.0f);
        for (i = 0; i < g->emit.count; i++) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % 60);
            g->emit.parts[i].y = 0.1f * (f32)(func_0019A5C8() % 2000);
            g->emit.parts[i].z = r * func_0020B480(a);
            g->emit.parts[i].x = r * func_0020B550(a);
            g->emit.parts[i].c = 0;
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->v11F0);
    func_001F5620(func_001F53A0(), g->jA, &g->joint);
    func_001F5F90(func_001F5380(), &t[0]);
    func_001F5620(func_001F53A0(), g->jA, &t[1]);
    func_00103DB0(&t[0], &t[1], &g->dir);
    func_001F5620(func_001F53A0(), g->jA, &g->v11A0);
    func_001F5620(func_001F53A0(), g->jA, &g->v1130);
    func_001038D0(g);
    func_001039A0(g->crd2);
    func_001038D0(&g->scale);
    func_001038D0(g->crd3);
    if (g->frame > 0x5B && g->frame <= 0xEB) {
        func_001F6580(func_001F5380(), g->col);
        g->col[2] = func_0019A5C8() % 128;
        g->col[1] = func_0019A5C8() % 128;
        g->col[0] = func_0019A5C8() % 128;
    }
    if (g->frame == 0xEC) {
        func_001F6580(func_001F5380(), 0);
    }
    b489_01E00240(ot, &g->emit, &g->scale);
    if (g->frame > 0xEC) {
        func_00103470(&g->emit.a, 0, 8);
    } else if (g->frame > 0x14 && g->frame <= 0xEB) {
        func_001032C0(&g->emit.a, 0x80, 8);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->pts[i].t >= 0) {
            g->pts[i].y += 4.0f;
            func_001032C0(&g->pts[i].c, 0x80, 0x10);
            if (g->pts[i].y > 200.0f) {
                a = func_0019A5C8() % 0x10000;
                r = 0.1f * (f32)(func_0019A5C8() % 60);
                g->emit.parts[i].y = 0.1f * (f32)(func_0019A5C8() % 30);
                g->emit.parts[i].z = r * func_0020B480(a);
                g->emit.parts[i].x = r * func_0020B550(a);
                g->pts[i].c = 0;
                g->pts[i].t = 0;
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 0xEC) {
        return 2;
    }
    if (g->frame == 0x51) {
        return 1;
    }
    if (g->frame >= 0x5B && g->frame <= 0xEB) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

