#include "clock.h"

using namespace std;

Clock::Clock(uint16_t x, uint16_t y, uint16_t r) :
    m_x(x), m_y(y), m_r(r)
{
}


void Clock::setTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

void Clock::render(Graphics& gfx)
{
    static float pi = 4*atanf(1);
    uint16_t x, y;
    float hour_len = m_r*0.4f;
    float minute_len = m_r*0.75f;
    float second_len = m_r*0.95f;
    float hour_angle = pi/2.f-(m_hour+m_minute/60.f)*pi/6.f;
    float minute_angle = pi/2.f - (m_minute+m_second/60.f)*pi/30.f;
    float second_angle = pi/2.f - m_second*pi/30.f;

    x = m_x + hour_len*cosf(hour_angle);
    y = m_y + hour_len*sinf(hour_angle);
    gfx.drawLine(m_x, m_y, x, y, 0xff0000);

    x = m_x + minute_len*cosf(minute_angle);
    y = m_y + minute_len*sinf(minute_angle);
    gfx.drawLine(m_x, m_y, x, y, 0xff00ff);

    x = m_x + second_len*cosf(second_angle);
    y = m_y + second_len*sinf(second_angle);
    gfx.drawLine(m_x, m_y, x, y, 0xffffff);
    
    gfx.drawPixel(m_x, m_y, 0x00ff00);

    for (int i = 0; i < 12; ++i) {
        float angle = pi/2 - i*pi/6;
        gfx.drawPixel(m_x+m_r*cosf(angle), m_y+m_r*sinf(angle),
                      angle > hour_angle ? 0xff0000 : 0xffff00);
    }
}

