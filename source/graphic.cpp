
#include "graphic.h"

void pp2d_draw_texture_scale_blend(size_t id, int x, int y, float scaleX, float scaleY, u32 color)
{
	pp2d_texture_select(id, x, y);
	pp2d_texture_blend(color);
	pp2d_texture_scale(scaleX, scaleY);
	pp2d_texture_draw();		
}

void pp2d_draw_texture_part_blend(size_t id, int x, int y, int xbegin, int ybegin, int width, int height, u32 color)
{
	pp2d_texture_select_part(id, x, y, xbegin, ybegin, width, height);
	pp2d_texture_blend(color);
	pp2d_texture_draw();		
}

void pp2d_draw_texture_part_scale(size_t id, int x, int y, int xbegin, int ybegin, int width, int height, float scaleX, float scaleY)
{
	pp2d_texture_select_part(id, x, y, xbegin, ybegin, width, height);
	pp2d_texture_scale(scaleX, scaleY);
	pp2d_texture_draw();
}

void pp2d_draw_texture_part_scale_blend(size_t id, int x, int y, int xbegin, int ybegin, int width, int height, float scaleX, float scaleY, u32 color)
{
	pp2d_texture_select_part(id, x, y, xbegin, ybegin, width, height);
	pp2d_texture_blend(color);
	pp2d_texture_scale(scaleX, scaleY);
	pp2d_texture_draw();		
}

void pp2d_draw_texture_rotate_flip_blend(size_t id, int x, int y, float angle, flipType fliptype, u32 color)
{
	pp2d_texture_select(id, x, y);
	pp2d_texture_rotate(angle);
	pp2d_texture_flip(fliptype);
	pp2d_texture_blend(color);
	pp2d_texture_draw();
}

//void pp2d_free_texture(size_t id)
//{
//	if (id >= MAX_TEXTURES)
//		return;
//	
//	if (!textures[id].allocated)
//		return;
//	
//	C3D_TexDelete(&textures[id].tex);
//	textures[id].width = 0;
//	textures[id].height = 0;
//	textures[id].allocated = false;
//}

size_t loadingbgtex = 1;
size_t topbgtex = 2;
size_t subbgtex = 3;
size_t greenbuttontex = 4;
size_t bluebuttontex = 5;
size_t redbuttontex = 6;
size_t orangebuttontex = 7;
size_t dot = 8;
size_t pageframe = 9;
size_t mainmenutoptex = 10;
size_t mainmenubottomtex = 11;
size_t pksmbottomtex = 12;
size_t pksmtoptex = 13;
size_t twltoptex = 14;
size_t twlbottomtex = 15;

void graphicsInit(void) {
}