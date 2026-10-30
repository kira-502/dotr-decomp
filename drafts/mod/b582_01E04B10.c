#include "common.h"
#include "mod/b582.c"

/* shape b582:01E04B10 (B582PAINT_RAIN3), 212 insns, 1 copy: b116:01E009A0's sprite draw made four times: the packet
   (passed in) gets its blend from flags >> 4, the module's colour (D_01E05798_b582) with the object's alpha, the
   scene rect corners (shape b003:01E00080) and texture; then four camera-facing sprites of the object's size, the
   first at its point and the others moved by its per-entry x/z offsets, depth by flags & 0xF (projected, far) */

typedef struct {
    f32 x, y, z;
    u8 padC[6];
    s16 dx[3];
    s16 dz[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[6];
    s16 size;
} Obj_b582_01E04B10;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    void *tex;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 frame;
} Game_b582_01E04B10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b582_01E04B10;

typedef struct {
    f32 u, v;
} Uv_b582_01E04B10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b582_01E04B10 uv;
    u64 pad18;
    Xyz_b582_01E04B10 v[4];
} Pk_b582_01E04B10;

typedef struct {
    u8 c[4];
} Col_b582_01E04B10;

static void func_01E04B10_b582(Game_b582_01E04B10 *g, Obj_b582_01E04B10 *o, Pk_b582_01E04B10 *p, s32 flags) {
    extern Col_b582_01E04B10 D_01E05798_b582;
    extern void func_00108EF0();
    Vec4f view[4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[16];
    s32 rot[4];
    Uv_b582_01E04B10 uv;
    Col_b582_01E04B10 col;
    s16 i;
    s32 mode;
    s32 sel;

    col = D_01E05798_b582;
    sel = flags >> 4;
    col.c[3] = o->col[0];
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &col);
    p->uv = uv;
    func_01E00080_b582((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    mode = flags & 0xF;
    rot[0] = 0x4000;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            a.x = o->x;
            a.y = o->y;
            a.z = o->z;
        } else {
            a.x = o->x + o->dx[i];
            a.y = o->y;
            a.z = o->z + o->dz[i];
        }
        func_00108EF0(m, &s, rot, &a);
        func_00108CE0(view, o->size, o->size);
        if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
            if (mode == 0) {
                func_002075F0((s32)p, g->ot, func_001A23B0(out[0]));
            } else if (mode == 1) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, g->ot, 0);
            }
        }
    }
}
