/** @file Logo.hpp
 * @brief Draws the JGHS Robotics logo on the V5 screen.
 */ 

#ifndef INULOGO_H
#define INULOGO_H

#include "inu/logo.c"
#include "pros/apix.h"

namespace inu {
	class Logo {
	public:
		/**
		 * How to create a logo as a c file:
		 * 1. Compress the image so that it is 272 pixels high or lower.
		 * 2. Feed the image to this to get the .c file:
		 * https://lvgl.io/tools/imageconverter
		 * 3. Replace lvgm.h with pros/apix.h in the .c file
		 * 4. At the very bottom, where the struct is in the .c file, organize
		 * the data so that is fits like so: 
		 * https://github.com/lvgl/lvgl/blob/c9b97feea87b820a68de0b78c6adb61a1527e042/src/lv_draw/lv_img_buf.h#L123-L142
		*/ 
		Logo() = default;

		static void Draw() {
			lv_obj_t * img_src = lv_img_create(lv_scr_act(), NULL);
			lv_img_set_src(img_src, &inuLogo);  
			lv_obj_set_pos(img_src, 104, 0);

			DrawRectangle(0, 0, 104, 272, LV_COLOR_WHITE);
			DrawRectangle(480 - 104, 0, 104, 272, LV_COLOR_WHITE);
		}

		static void DrawRectangle(int x, int y, int width, int height, lv_color_t color) {
			// Code belongs to jpearman
			// https://www.vexforum.com/t/lvgl-how-to-draw-a-rectangle-using-lvgl/50977/5
			lv_obj_t * obj1 = lv_obj_create(lv_scr_act(), NULL);

			lv_style_t *style1 = (lv_style_t *)malloc( sizeof( lv_style_t ));
			lv_style_copy(style1, &lv_style_plain_color);
			style1->body.main_color = color;
			style1->body.grad_color = color;

			lv_obj_set_style(obj1, style1);
			lv_obj_set_pos(obj1, x, y);
			lv_obj_set_size(obj1, width, height);
		}

	};
}

#endif
