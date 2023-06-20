
#include <iostream>
#include "Display.h"
#include "raylib.h"

const Color backgroud_color = {0, 0, 0, 255};
const Color pixel_color = {245, 245, 245, 255};
const int display_height = 32;
const int display_width = 64;
int display_buffer[64][32];
int scale;


Display::Display(int video_scale) {
    scale = video_scale;
   InitWindow(display_width*scale, display_height*scale, "CHIP8 Emulator");
   BeginDrawing();
   ClearBackground(backgroud_color);
   EndDrawing();
}

Display::~Display() {
    CloseWindow();
}


//void DrawRectangle(int posX, int posY, int width, int height, Color color);
void Display::UpdateScreen(unsigned int vid_array[]) {
    UpdateBuffer(vid_array);
    BeginDrawing();
        for (int x = 0; x < display_width; ++x) {
            for (int y = 0; y < display_height; ++y){
                Color color_to_draw = (display_buffer[x][y] == 1) ? pixel_color : backgroud_color;
                DrawRectangle(x*scale, y*scale, scale, scale, pixel_color);
            }
        }
    EndDrawing();
}

void Display::UpdateBuffer(unsigned int vid_array[]) {
    for (int rows = 0; rows < 32; ++rows) {
        for (int columns = 0; columns < 64; ++columns) {
            display_buffer[columns][rows] = vid_array[rows*display_width + columns]; //Conversion from 1D to 2D
        }
    }
}



