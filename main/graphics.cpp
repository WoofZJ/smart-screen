#include "graphics.h"

using namespace std;

Graphics::Graphics(uint16_t width, uint16_t height, uint16_t chain) :
    m_width(width), m_height(height)
{
    HUB75_I2S_CFG mxconfig(m_width, m_height, chain);
    mxconfig.gpio.e = 17;
    mxconfig.double_buff = true;
    mxconfig.clkphase = false;
    m_display = new MatrixPanel_I2S_DMA(mxconfig);
    m_display->begin();
    m_display->setBrightness(80);
    m_display->clearScreen();
}

Graphics::~Graphics()
{
}

void Graphics::drawPixel(int16_t x, int16_t y, uint32_t c)
{
    if (x >= 0 && y >= 0 && x < m_width && y < m_height) {
        m_display->drawPixelRGB888(63-x, y, c >> 16, (c >> 8) & 0xff, c & 0xff);
    }
}

void
Graphics::drawLine(
        int16_t x_from, int16_t y_from,
        int16_t x_to,   int16_t y_to,
        uint32_t c)
{
    if (x_to == x_from) {
        uint16_t y_min = y_from > y_to ? y_to : y_from;
        uint16_t y_max = y_from < y_to ? y_to : y_from;
        for (uint16_t y = y_min; y <= y_max; ++y) {
            drawPixel(x_to, y, c);
        }
        return;
    }
    if (y_to == y_from) {
        uint16_t x_min = x_from > x_to ? x_to : x_from;
        uint16_t x_max = x_from < x_to ? x_to : x_from;
        for (uint16_t x = x_min; x <= x_max; ++x) {
            drawPixel(x, y_to, c);
        }
        return;
    }

    if (x_from > x_to) {
        uint16_t temp = x_to;
        x_to = x_from;
        x_from = temp;
        temp = y_to;
        y_to = y_from;
        y_from = temp;
    }
    for (int16_t x = x_from; x <= x_to; x += 1) {
        drawPixel(x, y_from+((float)y_to-y_from)/(x_to-x_from)*(x-x_from)+0.5, c);
    }

    if (y_from > y_to) {
        uint16_t temp = x_to;
        x_to = x_from;
        x_from = temp;
        temp = y_to;
        y_to = y_from;
        y_from = temp;
    }
    for (int16_t y = y_from; y <= y_to; y += 1) {
        drawPixel(x_from+((float)x_to-x_from)/(y_to-y_from)*(y-y_from)+0.5, y, c);
    }
}

void Graphics::startDrawing()
{
    m_display->clearScreen();
}

void Graphics::endDrawing()
{
    m_display->flipDMABuffer();
}

