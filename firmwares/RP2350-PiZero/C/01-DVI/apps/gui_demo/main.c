#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"
#include "hardware/vreg.h"

#include "dvi.h"
#include "dvi_serialiser.h"
#include "common_dvi_pin_configs.h"
#include "tmds_encode.h" 

#include <stdio.h>
#include <stdarg.h>

#include "GUI_Paint.h"

// DVDD 1.2V (1.1V seems ok too)
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define VREG_VSEL VREG_VOLTAGE_1_10
#define DVI_TIMING dvi_timing_640x480p_60hz

// RGB111 bitplaned framebuffer
#define PLANE_SIZE_BYTES (FRAME_WIDTH * FRAME_HEIGHT / 8)
#define Scale3_RED 0x4
#define Scale3_GREEN 0x2
#define Scale3_BLUE 0x1
#define Scale3_BLACK 0x0
#define Scale3_WHITE 0x7
uint8_t framebuf[3 * PLANE_SIZE_BYTES];

struct dvi_inst dvi0;

void core1_main()
{
	dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
	dvi_start(&dvi0);
	while(true)
	{
		for (uint y = 0; y < FRAME_HEIGHT; ++y)
		{
			uint32_t *tmdsbuf=0;
			queue_remove_blocking_u32(&dvi0.q_tmds_free, &tmdsbuf);
			for (uint component = 0; component < 3; ++component)
			{
				tmds_encode_1bpp(
					(const uint32_t *)&framebuf[y * FRAME_WIDTH / 8 + component * PLANE_SIZE_BYTES],
					tmdsbuf + component * FRAME_WIDTH / DVI_SYMBOLS_PER_WORD,
					FRAME_WIDTH);
			}
			queue_add_blocking_u32(&dvi0.q_tmds_valid, &tmdsbuf);
		}
	}
}

int main()
{
	vreg_set_voltage(VREG_VSEL);
	sleep_ms(10);
	set_sys_clock_khz(DVI_TIMING.bit_clk_khz, true);

	setup_default_uart();

	pio_set_gpio_base(DVI_DEFAULT_SERIAL_CONFIG.pio,16);

	dvi0.timing = &DVI_TIMING;
	dvi0.ser_cfg = DVI_DEFAULT_SERIAL_CONFIG;
	dvi_init(&dvi0, next_striped_spin_lock_num(), next_striped_spin_lock_num());
	Paint_NewImage(framebuf, FRAME_WIDTH, FRAME_HEIGHT, 0, Scale3_WHITE);
	Paint_SetScale(3);
	multicore_launch_core1(core1_main);
	while(1)
	{
		double x= 0;
		Paint_Clear(Scale3_WHITE);
		sleep_ms(500);
		Paint_Clear(Scale3_RED);
		sleep_ms(500);
		Paint_Clear(Scale3_RED|Scale3_GREEN);
		sleep_ms(500);
		Paint_Clear(Scale3_GREEN);
		sleep_ms(500);
		Paint_Clear(Scale3_BLUE|Scale3_GREEN);
		sleep_ms(500);
		Paint_Clear(Scale3_BLUE);
		sleep_ms(500);
		Paint_Clear(Scale3_BLUE|Scale3_RED);
		sleep_ms(500);
		Paint_Clear(Scale3_BLACK);
		sleep_ms(500);

		Paint_Clear(Scale3_WHITE);
		Paint_DrawPoint(2, 1, Scale3_WHITE, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP); // 240 240
        Paint_DrawPoint(2, 6, Scale3_WHITE, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
        Paint_DrawPoint(2, 11, Scale3_WHITE, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
        Paint_DrawPoint(2, 16, Scale3_WHITE, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
        Paint_DrawPoint(2, 21, Scale3_WHITE, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);
        Paint_DrawLine(10, 5, 40, 35, Scale3_RED, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
        Paint_DrawLine(10, 35, 40, 5, Scale3_RED, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

        Paint_DrawLine(80, 20, 110, 20, Scale3_GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
        Paint_DrawLine(95, 5, 95, 35, Scale3_GREEN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

        Paint_DrawRectangle(10, 5, 40, 35, Scale3_BLUE, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
        Paint_DrawRectangle(45, 5, 75, 35, Scale3_BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

        Paint_DrawCircle(95, 20, 15, Scale3_BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
        Paint_DrawCircle(130, 20, 15, Scale3_BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

        Paint_DrawNum(50, 40, 9.87654321, &Font20, 3, Scale3_WHITE, Scale3_BLACK);
        Paint_DrawString_EN(1, 40, "ABC", &Font20, 0x000f, 0xfff0);
        Paint_DrawString_CN(1, 60, "��ӭʹ��", &Font24CN, Scale3_WHITE, Scale3_BLUE);
        Paint_DrawString_EN(1, 100, "RP2350-PiZero", &Font16, Scale3_RED, Scale3_WHITE);
		Paint_DrawString_EN(1, 203, "Que chotada de ejemplo", &Font16, Scale3_BLUE, Scale3_GREEN);
		for(uint16_t cnt=0;cnt<5000;cnt++)
		{
			x+=0.001;
			Paint_DrawNum(200, 200, x, &Font24, 3, Scale3_WHITE, Scale3_BLACK);
			sleep_ms(1);
		}
	}
}
