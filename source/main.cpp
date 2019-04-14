// Makes use of the citro2d example
#include <citro2d.h>
#include "gui_sheet.h"
#include "colors.hpp"

static C2D_SpriteSheet gui_sheet;

int main() {
    // Init libs
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    gui_sheet = C2D_SpriteSheetLoad("romfs:/gfx/gui_sheet.t3x");
    if (!gui_sheet) svcBreak(USERBREAK_PANIC);

    while (aptMainLoop())
    {
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break;

        // Render images
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(255, 255, 255, 0));
        C2D_TargetClear(bottom, C2D_Color32(255, 255, 255, 0));
        C2D_SceneBegin(top);
        C2D_DrawRectSolid(0, 0, 0.5f, 400, 240, COLOR_DARKBLUE);
        C2D_DrawImageAt(C2D_SpriteSheetGetImage(gui_sheet, gui_sheet_top_bg_idx), 0, 0, 0.6f, NULL, 1.0f, 1.0f);
        C2D_SceneBegin(bottom);
        C2D_DrawRectSolid(0, 0, 0.5f, 320, 240, COLOR_DARKBLUE);
        C3D_FrameEnd(0);
    }

    C2D_SpriteSheetFree(gui_sheet);
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();
    return 0;
}