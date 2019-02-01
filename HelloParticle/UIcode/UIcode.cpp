#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/bitmap.h"
#include "core_include/word.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "core_include/wave_ctrl.h"
#include "core_include/wave_buffer.h"
#include "gui_include/my_resource.h"
#include "gui_include/button.h"
#include <stdlib.h>
#include <string.h>

#define UI_WIDTH 240
#define UI_HEIGHT 320
#define EMITTER_X 120
#define EMITTER_Y 250
#define ACC_X 0
#define ACC_Y 1
#define PARTICAL_WITH	3
#define PARTICAL_HEIGHT 3

static c_surface* s_surface;

class c_particle {
public:
	c_particle(){
		initialize();
	}
	void initialize() {
		m_x = EMITTER_X; m_y = EMITTER_Y;
		m_x_velocity = (rand() % 7) - 3; m_y_velocity = -15 - (rand() % 4);
	}
	void move() {
		s_surface->fill_rect(m_x, m_y, m_x + PARTICAL_WITH - 1, m_y + PARTICAL_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);//clear previous image
		m_x_velocity += ACC_X; m_y_velocity += ACC_Y;
		m_x += m_x_velocity; m_y += m_y_velocity;
		if (m_x < 0 || (m_x + PARTICAL_WITH - 1) >= UI_WIDTH || m_y < 0 || (m_y + PARTICAL_HEIGHT - 1) >= UI_HEIGHT) {
			initialize();
		}
	}
	void draw() {
		int red = rand() % 5 * 63;
		int green = rand() % 5 * 63;
		int blue = rand() % 5 * 63;
		s_surface->fill_rect(m_x, m_y, m_x + PARTICAL_WITH - 1, m_y + PARTICAL_HEIGHT - 1, GL_RGB(red, green, blue), Z_ORDER_LEVEL_0);//draw current image
	}
	int m_x, m_y, m_x_velocity, m_y_velocity;
};

//////////////////////// start UI ////////////////////////
extern const FONT_INFO Microsoft_YaHei_28;
void load_resource() {
	c_my_resource::add_font(FONT_DEFAULT, &Microsoft_YaHei_28);
}

c_particle particle_array[100];
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	load_resource();
	c_display display = c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1, gfx_op);
	s_surface = display.alloc_surface((void*)1, Z_ORDER_LEVEL_0);
	s_surface->set_active(true);

	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "\xe7\xa5\x9d\x47\x75\x69\x4c\x69\x74\x65\xe5\xbc\x80\xe5\x8f\x91\xe8\x80\x85\:", 10, 10, c_my_resource::get_font(FONT_DEFAULT), GL_RGB(255, 0, 0), GL_ARGB(0, 0, 0, 0));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "\xe5\xa4\xa9\xe5\xa5\xb3\xe6\x95\xa3\xe8\x8a\xb1\xef\xbc\x8c\xe6\x96\xb0\xe5\xb9\xb4\xe5\xbf\xab\xe4\xb9\x90\xe2\x9d\xa4", 10, 48, c_my_resource::get_font(FONT_DEFAULT), GL_RGB(255, 0, 0), GL_ARGB(0, 0, 0, 0));
	
	while(1) {
		for (int i = 0; i < sizeof(particle_array)/sizeof(c_particle); i++) {
			particle_array[i].move();
			particle_array[i].draw();
		}
		thread_sleep(50);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloParticle(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}
