#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b574(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b574(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b016_01E01190;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b016_01E01190;

typedef struct {
    u8 pad00[0x20];
    Vec_b016_01E01190 rotation;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b016_01E01190;

static void func_01E009B0_b574(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b016_01E01190 c;
    Vec_b016_01E01190 quad[4];
    Vec_b016_01E01190 pos;
    Vec_b016_01E01190 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
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
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = data->height;
    quad[3].y = data->height;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
    }
}

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00D10_b574(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b574((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00110_b574((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E012C0_b574(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
}

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E01410_b574(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
    }
}

/* shape b574:01E015E0, 333 insns: the b574 module's event step (B574_W_S): counts ticks (ctx+0xDA98); until 289 the
   point 0xD930 follows the model (0xD9C8); at 290 it sets a 75-tick glide (y, z) toward the other model (0xD9D8) and
   glides until 363; 125..300 pairs of b574:01E01B20 (turn k*10 and +180, slots k and k+36) for k up to 35; 365..400
   two b574:01E02A70 a tick (slot counter 0..79); at 220 two b574:01E02720; 364..400 b574:01E02550 twice and
   b574:01E02910 at the point; 290..400 b574:01E03080 and b574:01E03240; at 290 b574:01E02070 and ten b574:01E02170 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xD930 - 0x260];
    Vec4f p;
    u8 padD940[0x20];
    Vec4f d;
    u8 padD970[0xD9C8 - 0xD970];
    s16 id;
    u8 padD9CA[0xE];
    s16 id2;
    u8 padD9DA[0xDA7A - 0xD9DA];
    s16 k;
    u8 padDA7C[2];
    s16 ang;
    u8 padDA80[2];
    s16 m;
    u8 padDA84[0xC];
    s16 slot;
    u8 padDA92[6];
    s16 timer;
} Ctx_b574_01E015E0;

static void func_01E015E0_b574(Ctx_b574_01E015E0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_01E03D70_b574();
    extern s32 b574_01E01B20();
    extern s32 func_01E02070_b574();
    extern s32 func_01E02170_b574();
    extern s32 func_01E02550_b574();
    extern s32 func_01E02720_b574();
    extern s32 func_01E02910_b574();
    extern s32 b574_01E02A70();
    extern s32 func_01E03080_b574();
    extern s32 func_01E03240_b574();
    Vec4f v[2];
    s16 i;

    g->timer++;
    if (g->timer < 290) {
        func_001F5620(func_001F53A0(), g->id, &g->p);
    } else {
        if (g->timer == 290) {
            func_001F5620(func_001F5380(), g->id2, v);
            g->d.z = (v[0].z - g->p.z) / 75.0f;
            g->d.y = (v[0].y - g->p.y) / 75.0f;
        }
        if (g->timer < 364) {
            g->p.z += g->d.z;
            g->p.y += g->d.y;
        }
    }
    if (g->timer >= 125 && g->timer < 301) {
        if (g->k < 36) {
            g->ang = g->k * 10;
            g->slot = g->k;
            func_01E03D70_b574(g, b574_01E01B20, 0);
            g->ang = g->k * 10 + 180;
            g->slot = g->k + 36;
            func_01E03D70_b574(g, b574_01E01B20, 0);
            g->k++;
        }
    }
    if (g->timer > 364 && g->timer < 401) {
        for (i = 0; i < 2; i++) {
            g->slot = g->m;
            func_01E03D70_b574(g, b574_01E02A70, 0);
            g->m++;
            if (g->m >= 80) {
                g->m = 0;
            }
        }
    }
    if (g->timer == 220) {
        g->slot = 0;
        func_01E03D70_b574(g, func_01E02720_b574, 0);
        g->slot = 36;
        func_01E03D70_b574(g, func_01E02720_b574, 0);
    }
    if (g->timer >= 364 && g->timer < 401) {
        g->pos = g->p;
        g->slot = 0;
        func_01E03D70_b574(g, func_01E02550_b574, 0);
        func_01E03D70_b574(g, func_01E02550_b574, 0);
        func_01E03D70_b574(g, func_01E02910_b574, 0);
    }
    if (g->timer >= 290 && g->timer < 401) {
        g->pos = g->p;
        g->slot = 0;
        func_01E03D70_b574(g, func_01E03080_b574, 0);
        func_01E03D70_b574(g, func_01E03240_b574, 0);
    }
    if (g->timer == 290) {
        g->pos = g->p;
        g->slot = 0;
        func_01E03D70_b574(g, func_01E02070_b574, 0);
        for (i = 0; i < 10; i++) {
            func_01E03D70_b574(g, func_01E02170_b574, 0);
        }
    }
}

/* shape b574:01E01B20, 339 insns: a petal of the ring (B574_OBJ_MOVE_2_): set up once at 60 x 60, grey, mode 0 / 2 /
   4 by slot thirds (36 each), random size 4..6; fades in by 12 to 0xC0 before tick 30, out by 11 after scene tick
   400; from tick 30 every 10th tick the hue phase (0..5) steps and shifts the two colours by 5; while the scene runs
   it shrinks or grows width/height by 2.5 through modes 0..5; after scene tick 290 it spins both turns by 0x300,
   direction by slot third */

typedef struct {
    u8 pad0[0xDA98];
    s16 timer;
} Ctx_b574_01E01B20;

typedef struct {
    u8 pad0[6];
    s16 phase;
    s16 size;
    u8 padA[0x16];
    s32 rot[4];
    u8 pad30[0x18];
    f32 w;
    f32 h;
    s16 slot;
    s16 mode;
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Petal_b574_01E01B20;

static s32 func_01E01B20_b574(Ctx_b574_01E01B20 *g, Petal_b574_01E01B20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 60.0f;
        o->h = 60.0f;
        o->h56 = 0;
        o->state = 2;
        if (o->slot < 36) {
            o->mode = 0;
        } else if (o->slot < 72) {
            o->mode = 2;
        } else if (o->slot < 108) {
            o->mode = 4;
        }
        o->size = func_0019A5C8() % 3 + 4;
        o->rot[0] = 0x4000;
        o->phase = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->t < 30) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 12;
        }
    } else if (g->timer > 400) {
        if (o->col[3] > 12) {
            o->col[3] -= 11;
        } else {
            o->state = 0;
        }
        if (o->col2[3] > 12) {
            o->col2[3] -= 11;
        }
    }
    if (o->t >= 30 && o->t % 10 == 1) {
        o->phase++;
        if (o->phase > 5) {
            o->phase = 0;
        }
    }
    if (o->phase == 0) {
        o->col[0] += 5;
        o->col2[0] += 5;
    } else if (o->phase == 1) {
        o->col[1] += 5;
        o->col2[1] += 5;
    } else if (o->phase == 2) {
        o->col[2] += 5;
        o->col2[2] += 5;
    } else if (o->phase == 3) {
        o->col[0] -= 5;
        o->col2[0] += 5;
    } else if (o->phase == 4) {
        o->col[1] -= 5;
        o->col2[1] += 5;
    } else if (o->phase == 5) {
        o->col[2] -= 5;
        o->col2[2] += 5;
    }
    if (g->timer != 0) {
        if (o->mode == 0) {
            if (o->w > 25.0f) {
                o->w -= 2.5f;
            } else {
                o->mode++;
            }
        } else if (o->mode == 1) {
            if (o->h > 20.0f) {
                o->h -= 2.5f;
            }
        } else if (o->mode == 2) {
            if (o->w > 15.0f) {
                o->w -= 2.5f;
            } else {
                o->mode++;
            }
        } else if (o->mode == 3) {
            if (o->h > 10.0f) {
                o->h -= 2.5f;
            }
        } else if (o->mode == 4) {
            if (o->w < 20.0f) {
                o->w += 2.5f;
            } else {
                o->mode++;
            }
        } else if (o->mode == 5) {
            if (o->h < 10.0f) {
                o->h += 2.5f;
            }
        }
    }
    if (g->timer > 290) {
        if (o->slot < 36) {
            o->rot[1] += 0x300;
        } else if (o->slot < 72) {
            o->rot[1] -= 0x300;
        } else if (o->slot < 108) {
            o->rot[1] += 0x300;
        }
        if (o->slot < 36) {
            o->rot[0] += 0x300;
        } else if (o->slot < 72) {
            o->rot[0] -= 0x300;
        } else if (o->slot < 108) {
            o->rot[0] += 0x300;
        }
    }
    o->t++;
    return 0;
}

/* shape b178:01E03530, 63 insns: a two-colour glow: grey and (0x80,0x80,0x40), life 12; both alphas grow by 0x2A
   (below 0x80) during the life, then fade out by 12; stops when the first is gone */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 vol;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b178_01E03530;

static s32 func_01E02070_b574(s32 arg0, Fx_b178_01E03530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x40);
        o->life = 12;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 0xD) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xD) {
            o->col2[3] -= 12;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b574:01E02170, 108 insns: b282:01E01C20 family spinning spark: white tumbling (size 6, frame 3, three random turns, angle 3..32, spin 35..94, size 0..19, hold 1..2 stored): alpha 0xC0 for 10 ticks, then out by 19 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E02170;

static s32 func_01E02170_b574(s32 arg0, Obj_b574_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        o->kind = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 30 + 3;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 60 + 35;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->t < 10) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b270:01E031B0, 138 insns: b084:01E01A20 family: a white flicker (size 5..34, frames 0..3 then dies at 8, random spin), alternates 0xFF/0xC0 grey every tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[0x16];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b270_01E031B0;

static s32 func_01E02320_b574(void *arg0, Spark_b270_01E031B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 5;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = func_0019A5C8() % 400 + 20;
        o->h5A = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 20;
        o->life = func_0019A5C8() % 3 + 4;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    o->frame++;
    if (o->frame > 7) {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    o->t++;
    return 0;
}

/* shape b574:01E02550, 113 insns: on start f48 6, variant 3, colour white, random rotation, 0x50 3..32, random 0x5A,
   speed 40..99 (0xE), 0x8 0..19, hold 0..2 (0x6); alpha 0x80 while the game step 0xDA98 is below 0x19A, then fades
   by 15 and stops; after the first tick 0x50 grows by the speed */

typedef struct {
    u8 pad0[0xDA98];
    s16 step;
} Game_b574_01E02550;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b574_01E02550;

static s32 func_01E02550_b574(Game_b574_01E02550 *g, Fx_b574_01E02550 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        o->f56 = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 30 + 3;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 60 + 40;
        o->f8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (g->step < 0x19A) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b574:01E02720, 119 insns: a grey ring (kind by +0x50: 300 x 250 or 200 x 150), spin 10/10, turn 0x4000: in by 10 up to 0x80 while the scene value is under 400, then out by 13 and ends; from scene value 291 it sways 0x180 a tick on two axes by its kind */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E02720;

typedef struct {
    u8 pad[0xDA98];
    s16 val;
} Game_b574_01E02720;

static s32 func_01E02720_b574(Game_b574_01E02720 *g, Obj_b574_01E02720 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->h50 < 36) {
            o->f48 = 300.0f;
            o->f4C = 250.0f;
        } else if (o->h50 < 72) {
            o->f48 = 200.0f;
            o->f4C = 150.0f;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->h5A = 10;
        o->h5C = 10;
        o->w20 = 0x4000;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->val < 400) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 10;
        }
    } else if (o->col2[3] > 14) {
        o->col2[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (g->val > 290) {
        if (o->h50 < 36) {
            o->w24 += 0x180;
        } else if (o->h50 < 72) {
            o->w24 -= 0x180;
        } else if (o->h50 < 108) {
            o->w24 += 0x180;
        }
        if (o->h50 < 36) {
            o->w20 += 0x180;
        } else if (o->h50 < 72) {
            o->w20 -= 0x180;
        } else if (o->h50 < 108) {
            o->w20 += 0x180;
        }
    }
    o->t++;
    return 0;
}

/* shape b574:01E02910, 87 insns: a grey/yellow tumbling column (40 wide growing 1, 100 tall growing 55 a tick) at three random turns: in by 80 up to 0xA0 for 3 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E02910;

static s32 func_01E02910_b574(s32 arg0, Obj_b574_01E02910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        o->f4C = 100.0f;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0x40);
        o->h5A = 10;
        o->h5C = 2;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 3) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->f48 += 1.0f;
    o->f4C += 55.0f;
    o->t++;
    return 0;
}

/* shape b574:01E02A70, 387 insns (B574_OBJ_MOVE_10_, b445:01E03680's code): a jittery spark trail (b445:01E03080 twin: random pitch, light-grey blink; bigger and faster than b445's) on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's b574:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b574_01E02A70;

typedef struct {
    u8 pad0[0x7030];
    Track_b574_01E02A70 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0x86];
    u8 padDC90[0xDC9C - 0xDC90];
    u8 trig[1];
} World_b574_01E02A70;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b574_01E02A70;

static s32 func_01E02A70_b574(World_b574_01E02A70 *w, Spark_b574_01E02A70 *o) {
    extern void func_01E00080_b574();
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 130 + 40;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 140 + 25;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        func_01E00080_b574(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b574:01E03080, 112 insns: b764:01E02A60 family ring (grey/purple) of random height 10..79 (25..124 once the scene value reaches 360), growing 1 (or 3) a tick, spun 0x4000: in by 80 up to 0xA0 for 3 ticks, then out by 12 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E03080;

typedef struct {
    u8 pad[0xDA98];
    s16 val;
} Game_b574_01E03080;

static s32 func_01E03080_b574(Game_b574_01E03080 *g, Obj_b574_01E03080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (g->val < 360) {
            o->f4C = 10.0f + (func_0019A5C8() >> 4) % 70;
        } else {
            o->f4C = 25.0f + (func_0019A5C8() >> 4) % 100;
        }
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x40, 0x20, 0x30);
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 3) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->col2[3] > 13) {
        o->col2[3] -= 12;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    if (g->val < 360) {
        o->f4C += 1.0f;
    } else {
        o->f4C += 3.0f;
    }
    o->t++;
    return 0;
}

/* shape b574:01E03240, 101 insns: a white tumbling spark (size 3, frame 3, three random turns, angle 30..129, spin 40..99, size 0..19, hold 1..2 stored): alpha 0x80 for 10 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E03240;

static s32 func_01E03240_b574(s32 arg0, Obj_b574_01E03240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->kind = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 100 + 30;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 60 + 40;
        o->h8 = func_0019A5C8() % 20;
        o->h6 = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->t < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E033E0_b574(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b574", func_01E033F0_b574);

/* shape b574:01E03D70, 82 insns: c035:01E01150 family: take the first free effect slot of 250 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, its angle, the scene value twice and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b574_01E03D70;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b574_01E03D70 slot[250];
    u8 padEnd[0xd994 - 0x2a0 - 250 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padD998[0xE6];
    s16 ang;
    u8 padDA80[0x10];
    s16 val;
} Ctx_b574_01E03D70;

static s32 func_01E03D70_b574(Ctx_b574_01E03D70 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b574_01E03D70 *s;

    s = NULL;
    for (i = 0; i < 250; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 250;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h5A = ctx->ang;
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b574:01E03F20 (B574PAINT_RAIN20), 200 insns, 1 copy: b529:01E03F40's one-segment ring draw with this module's
   scene layout: ordering table g+0xD99C, frame table g+0xD9E8, trig g+0xDC9C */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    s16 h50;
    u8 pad52[8];
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b574_01E03F20;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0xD99C - 0xC0];
    s32 ot;
    u8 padD9A0[0xD9E8 - 0xD9A0];
    s16 tbl[36];
    u8 padDA30[0xDC9C - 0xDA30];
    u8 trig[1];
} Game_b574_01E03F20;

static void func_01E03F20_b574(Game_b574_01E03F20 *g, Obj_b574_01E03F20 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    Rect_b152_01E014F0 rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    rc = func_01E012C0_b574(0x14, g->tbl[o->h50 % 36], 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        a = s + (s16)(o->h5A + 10) - 200; /* the (s16) keeps the +10 apart: needed for the match */
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b574", func_01E04240_b574);
