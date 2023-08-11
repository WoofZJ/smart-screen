#include <rom/ets_sys.h>
#include "graphics.h"
#include "clock.h"

using namespace std;

Graphics gfx(64, 64, 1);

extern "C" void app_main(void)
{
    Clock clock(14, 62-12, 12);
    while (1) {
        for (size_t hour = 3; hour < 12; ++hour) {
            for (size_t min = 46; min < 60; ++min) {
                for (size_t sec = 0; sec < 60; ++sec) {
                    clock.setTime(hour, min, sec);
                    gfx.startDrawing();
                    clock.render(gfx);
                    gfx.endDrawing();
                    ets_delay_us(1000000);
                }
            }
        }
    }
}
