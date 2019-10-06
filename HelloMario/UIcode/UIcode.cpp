#include "GuiLite.h"

#define UI_WIDTH			240
#define UI_BOTTOM_HEIGHT	76
#define MARIO_WITH			16
#define MARIO_HEIGHT		32
#define FULL_STEP			9
#define MARIO_INIT_X		0
#define MARIO_INIT_Y		(UI_BOTTOM_HEIGHT - 1)
#define RYU_X				85
#define RYU_Y				90
#define ACC_X				0
#define ACC_Y				1
extern const BITMAP_INFO title_bmp, background_bmp, step1_bmp, step2_bmp, step3_bmp, jump_bmp,
frame_00_bmp, frame_01_bmp, frame_02_bmp, frame_03_bmp, frame_04_bmp, frame_05_bmp, frame_06_bmp,
frame_07_bmp, frame_08_bmp, frame_09_bmp, frame_10_bmp, frame_11_bmp, frame_12_bmp, frame_13_bmp;

static BITMAP_INFO s_frames[] = { frame_00_bmp, frame_01_bmp, frame_02_bmp,  frame_03_bmp,  frame_04_bmp,  frame_05_bmp,
							frame_06_bmp,  frame_07_bmp,  frame_08_bmp,  frame_09_bmp,  frame_10_bmp,  frame_11_bmp,
							frame_12_bmp, frame_13_bmp };
static c_surface* s_surface_top;
static c_surface* s_surface_bottom;

void draw_easter_egg()
{
	for (int i = 0; i < sizeof(s_frames) / sizeof(BITMAP_INFO); i++)
	{
		c_theme::add_bitmap(BITMAP_CUSTOM1, &s_frames[i]);
		c_bitmap::draw_bitmap(s_surface_top, Z_ORDER_LEVEL_0, c_theme::get_bmp(BITMAP_CUSTOM1), RYU_X, RYU_Y, GL_RGB(85, 136, 221));
		thread_sleep(20);
	}
	s_surface_top->fill_rect(RYU_X, RYU_Y, RYU_X + frame_00_bmp.width - 1, RYU_Y + frame_00_bmp.height - 1, GL_RGB(131, 110, 83), Z_ORDER_LEVEL_0);
}

class c_mario {
public:
	c_mario(){
		m_x = MARIO_INIT_X; m_y = MARIO_INIT_Y; m_step = 0;
		m_is_jump = false;
		m_x_velocity = 3; m_y_velocity = 0;
	}
	void jump() {
		m_is_jump = true;
		m_y_velocity = -9;
	}
	void move() {
		if (m_step++ == FULL_STEP) { m_step = 0; }
		m_x_velocity += ACC_X;
		m_x += m_x_velocity;
		if (m_is_jump) {
			m_y_velocity += ACC_Y;
			m_y += m_y_velocity;
		}
		if ((m_x + MARIO_WITH - 1) >= UI_WIDTH) {
			m_x = 0;
		}
		if (m_y >= UI_BOTTOM_HEIGHT) {
			m_y = MARIO_INIT_Y;
			m_y_velocity = 0;
			m_is_jump = false;
		}
		if (m_y < MARIO_HEIGHT) {
			m_y = MARIO_HEIGHT;
			m_y_velocity = 0;
		}

		//Just joking
		if (m_x == 93)
		{
			jump();
		}
		if (m_x == 117)
		{
			draw_easter_egg();
		}
	}
	void draw() {
		const BITMAP_INFO* mario_bmp;
		if (m_is_jump) {
			mario_bmp = &jump_bmp;
		} else {
			if (m_step < (FULL_STEP / 3)) {
				mario_bmp = &step1_bmp;
			} else if (m_step < (FULL_STEP * 2/ 3)) {
				mario_bmp = &step2_bmp;
			} else {
				mario_bmp = &step3_bmp;
			}
		}
		c_rect mario_rect(m_x, m_y - mario_bmp->height, m_x + mario_bmp->width - 1, m_y);
		s_surface_bottom->set_frame_layer_visible_rect(mario_rect, Z_ORDER_LEVEL_1);
		c_bitmap::draw_bitmap(s_surface_bottom, Z_ORDER_LEVEL_1, mario_bmp, m_x, m_y - mario_bmp->height, GL_RGB(255, 255, 255));
	}
	int m_x, m_y, m_x_velocity, m_y_velocity;
	unsigned int m_step;
	bool m_is_jump;
};

//////////////////////// start UI ////////////////////////
c_mario the_mario;
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op_top, struct EXTERNAL_GFX_OP* gfx_op_bottom) {
	c_display display_top = c_display(phy_fb, screen_width, screen_height, UI_WIDTH, (screen_height - UI_BOTTOM_HEIGHT), color_bytes, 1, gfx_op_top);
	s_surface_top = display_top.alloc_surface(Z_ORDER_LEVEL_0);
	s_surface_top->set_active(true);
	s_surface_top->fill_rect(0, 0, UI_WIDTH - 1, screen_height - UI_BOTTOM_HEIGHT - 1, GL_RGB(131, 110, 83), Z_ORDER_LEVEL_0);
	c_bitmap::draw_bitmap(s_surface_top, Z_ORDER_LEVEL_0, &title_bmp, 30, 20);

	c_display display_bottom = c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_BOTTOM_HEIGHT, color_bytes, 1, gfx_op_bottom);
	s_surface_bottom = display_bottom.alloc_surface(Z_ORDER_LEVEL_1);
	s_surface_bottom->set_active(true);
	s_surface_bottom->fill_rect(0, 0, UI_WIDTH - 1, UI_BOTTOM_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	c_bitmap::draw_bitmap(s_surface_bottom, Z_ORDER_LEVEL_0, &background_bmp, 3, 0);

	while(1) {
		the_mario.draw();
		the_mario.move();
		thread_sleep(50);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloMario(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op_top, struct EXTERNAL_GFX_OP* gfx_op_bottom) {
	create_ui(phy_fb, width, height, color_bytes, gfx_op_top, gfx_op_bottom);
}

void sendTouch2HelloMario(int x, int y, bool is_down)
{
	if (is_down) { the_mario.jump(); }
}
