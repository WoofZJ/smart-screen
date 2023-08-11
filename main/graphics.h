#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

class Graphics {
public:
    Graphics(uint16_t width, uint16_t height, uint16_t chain);
    ~Graphics();
    void drawPixel(int16_t x, int16_t y, uint32_t c);
    void drawLine(int16_t x_from, int16_t y_from,
                  int16_t x_to,   int16_t y_to,
                  uint32_t c);
    void startDrawing();
    void endDrawing();
private:
    MatrixPanel_I2S_DMA *m_display;
    uint16_t m_width, m_height;
};

#endif
