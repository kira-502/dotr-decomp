#include "common.h"

/* shape b058:01E023F0 (B058PAINT_RAIN5), 179 insns, 1 copy: a narrowing ribbon along one of the module's seven point
   rows (by the object's row 0x30); mode 0 only sets up the packet's texture; otherwise 7 flat quads between each
   point and the next, 20 wide at the start and 2 narrower at each point, drawn via func_00108F90 */

typedef struct {
    u8 pad0[0x10C];
    void *tex;
    u8 pad110[0x3100 - 0x110];
    Vec4f rows[7][8];
} Game_b058_01E023F0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    Vec4f rot;
    u8 pad20[8];
    u8 col[8];
    s16 row;
    u8 pad32[2];
    s16 page;
} Obj_b058_01E023F0;

static void func_01E023F0_b058(Game_b058_01E023F0 *g, Obj_b058_01E023F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    u8 *ot;
    Vec4f *a;
    Vec4f *b;
    s16 i;
    f32 w;
    f32 h;

    ot = func_00207500();
    w = 20.0f;
    if (mode == 0) {
        func_00106080(td, 0x96, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, g->tex, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, &o->rot, &pos);
    if (o->row == 0) {
        a = &g->rows[0][1];
        b = &g->rows[0][0];
    }
    if (o->row == 1) {
        a = &g->rows[1][1];
        b = &g->rows[1][0];
    }
    if (o->row == 2) {
        a = &g->rows[2][1];
        b = &g->rows[2][0];
    }
    if (o->row == 3) {
        a = &g->rows[3][1];
        b = &g->rows[3][0];
    }
    if (o->row == 4) {
        a = &g->rows[4][1];
        b = &g->rows[4][0];
    }
    if (o->row == 5) {
        a = &g->rows[5][1];
        b = &g->rows[5][0];
    }
    if (o->row == 6) {
        a = &g->rows[6][1];
        b = &g->rows[6][0];
    }
    quad[0].y = quad[1].y = quad[2].y = quad[3].y = 0.0f;
    for (i = 0; i < 7; i++) {
        h = w / 2.0f;
        quad[0].x = a->x;
        quad[1].x = a->x;
        quad[2].x = b->x;
        quad[3].x = b->x;
        quad[2].z = b->z - h;
        quad[3].z = b->z + h;
        w -= 2.0f;
        h = w / 2.0f;
        quad[0].z = a->z - h;
        quad[1].z = a->z + h;
        a++;
        b++;
        func_00108F90(quad, pkt, m, ot);
    }
}
