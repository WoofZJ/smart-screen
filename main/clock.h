#ifndef CLOCK_H
#define CLOCK_H

#include "graphics.h"

class Clock {
public:
    Clock(uint16_t x, uint16_t y, uint16_t r);
    void setTime(uint8_t hour, uint8_t minute, uint8_t second);
    void render(Graphics& gfx);
private:
    uint16_t m_x, m_y, m_r;
    uint8_t m_hour, m_minute, m_second;
};

#endif
