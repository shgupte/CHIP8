#pragma once
#include <iostream>
#include "raylib.h"

class Display {

    private:
    void UpdateBuffer(unsigned int vid_array[]);

    public:
    Display(int scale);
    ~Display();

    void UpdateScreen(unsigned int vid_array[64*32]);

};