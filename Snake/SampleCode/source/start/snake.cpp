#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "core_include/display.h"
#include "gui_include/slide_group.h"
#include "gui_include/gesture.h"
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE		20
#define GRASS_COLOR		GLT_RGB(170, 215, 81)

int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
static c_slide_root	s_root;
static c_surface*	s_surface;
void* s_phy_fb;

static void get_screen_size(short *top, short *left, short *bottom, short *right)
{
	*top = *left = 0;
	*right = SCREEN_WIDTH - 1;
	*bottom = SCREEN_HEIGHT - 1;
}

#define MAX_LENGTH			256
#define INI_SNAKE_LENGTH	10
#define INVALIDE_POS		-1

enum DIRECTION
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	MAX_DIRECTION
};
static DIRECTION s_player_direction = RIGHT;

class c_snake
{
public:
	c_snake();
	~c_snake() {}
	void run();
	bool is_be_bitten(short x, short y);
	int set_length(unsigned int len);
	unsigned int get_length() { return m_length; }
	bool got_food(unsigned int food_x, unsigned food_y);
	void get_head_pos(short *x, short *y) { *x = m_x[0]; *y = m_y[0]; }
protected:
	void draw();
	virtual void move();
	void set_direct(enum DIRECTION direct);
	void update_direction();

	enum DIRECTION m_direction;
	unsigned int m_length;
	short m_x[MAX_LENGTH];
	short m_y[MAX_LENGTH];
	short m_x_footprint;
	short m_y_footprint;
};

c_snake::c_snake()
{
	set_length(INI_SNAKE_LENGTH);
	
	short top, left, bottom, right;
	get_screen_size(&top, &left, &bottom, &right);
	
	m_direction = RIGHT;
	memset(m_x, 0, sizeof(m_x));
	memset(m_y, 0, sizeof(m_y));
	m_x[0] = (right / 2);
	m_y[0] = (bottom / 2);
	m_x_footprint = m_y_footprint = INVALIDE_POS;
}

int c_snake::set_length(unsigned int len)
{
	if (len >= MAX_LENGTH)
	{
		return -1;
	}

	for (unsigned int i = (m_length - 1); i < len; i++)
	{
		m_x[i] = m_x[m_length - 1];
		m_y[i] = m_y[m_length - 1];
	}
	m_length = len;
	return 0;
}

void c_snake::set_direct(enum DIRECTION direct)
{//no backwrad
	switch (m_direction)
	{
	case LEFT:
		if (direct != RIGHT) { m_direction = direct; } break;
	case RIGHT:
		if (direct != LEFT) { m_direction = direct; } break;
	case UP:
		if (direct != DOWN) { m_direction = direct; } break;
	case DOWN:
		if (direct != UP) { m_direction = direct; } break;
	default:
		break;
	}
}

static void draw_body(int x, int y, unsigned int rgb)
{
	s_surface->fill_rect(x, y, (x + BLOCK_SIZE), (y + BLOCK_SIZE), rgb, Z_ORDER_LEVEL_0);
}

void c_snake::draw()
{	//clear foot print
	if ((INVALIDE_POS != m_x_footprint) && (INVALIDE_POS != m_y_footprint))
	{
		draw_body(m_x_footprint, m_y_footprint, GRASS_COLOR);
	}

	//draw body
	if (m_length > 1)
	{
		draw_body(m_x[1], m_y[1], GLT_RGB(47, 92, 197));
	}

	//draw head
	if ((INVALIDE_POS == m_x[0]) || (INVALIDE_POS == m_y[0]))
	{
		return;
	}
	draw_body(m_x[0], m_y[0], GLT_RGB(77, 123, 244));
}

void c_snake::move()
{
	m_x_footprint = m_x[(m_length - 1)];
	m_y_footprint = m_y[(m_length - 1)];
	for (size_t i = (m_length - 1); i > 0; i--)
	{
		m_x[i] = m_x[i - 1];
		m_y[i] = m_y[i - 1];
	}

	if (m_direction == RIGHT)
	{
		m_x[0] += BLOCK_SIZE;
	}
	else if (m_direction == DOWN)
	{
		m_y[0] += BLOCK_SIZE;
	}
	else if (m_direction == UP)
	{
		m_y[0] -= BLOCK_SIZE;
	}
	else if (m_direction == LEFT)
	{
		m_x[0] -= BLOCK_SIZE;
	}

	short top, left, bottom, right;
	get_screen_size(&top, &left, &bottom, &right);
	if (m_x[0] >= right - BLOCK_SIZE)
	{
		m_x[0] = left;
	}
	else if (m_x[0] <= left)
	{
		m_x[0] = right - BLOCK_SIZE;
	}
	else if (m_y[0] <= top)
	{
		m_y[0] = bottom - BLOCK_SIZE;
	}
	else if(m_y[0] >= bottom - BLOCK_SIZE)
	{
		m_y[0] = top;
	}
}

void c_snake::update_direction()
{
	set_direct(s_player_direction);
}

bool c_snake::is_be_bitten(short x, short y)
{
	for (size_t i = 1; i < m_length; i++)
	{
		if ((x == m_x[i]) && (y == m_y[i]))
		{
			return true;
		}
	}
	return false;
}

bool c_snake::got_food(unsigned int food_x, unsigned food_y)
{
	if ((food_x > m_x[0]) && (food_x < m_x[0] + BLOCK_SIZE) &&
		(food_y > m_y[0]) && (food_y < m_y[0] + BLOCK_SIZE))
	{
		return true;
	}
	return false;
}

void c_snake::run()
{
	update_direction();
	move();
	draw();
}

void game_loop()
{
	c_snake the_snake;
	while (1)
	{
		thread_sleep(100);
		the_snake.run();
	}
}

void create_ui()
{
	c_display* display = new c_display(s_phy_fb, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	s_surface = display->create_surface(&s_root, Z_ORDER_LEVEL_0);
	s_surface->set_active(true);

	s_surface->fill_rect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, GRASS_COLOR, Z_ORDER_LEVEL_0);
}

//////////////////// UWP/Android interface ////////////////////////////
extern "C" int run_native(int width, int height, void* phy_fb)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	if (!phy_fb)
	{
		ASSERT(FALSE);
	}
	
	s_phy_fb = phy_fb;
	create_ui();
	game_loop();
	return 0;
}

extern "C" void* get_frame_buffer(int display_id, int* width, int* height)
{
	return c_display::get_frame_buffer(0, width, height);
}

extern "C" int send_hid_msg(void* buf, int len, int display_id)
{
	static MSG_INFO s_press_msg;

	if (len != sizeof(MSG_INFO))
	{
		ASSERT(FALSE);
	}

	MSG_INFO* msg = (MSG_INFO*)buf;
	if (msg->dwMsgId == 0x4700 && (s_press_msg.dwMsgId == 0))
	{//presss
		memcpy(&s_press_msg, msg, sizeof(MSG_INFO));
	}
	else if (msg->dwMsgId == 0x4600)
	{//release
		int dx = msg->dwParam1 - s_press_msg.dwParam1;
		int dy = msg->dwParam2 - s_press_msg.dwParam2;
		if (abs(dx) > abs(dy))
		{
			s_player_direction = (dx > 0) ? RIGHT : LEFT;
		}
		else
		{
			s_player_direction = (dy > 0) ? DOWN : UP;
		}
		s_press_msg.dwMsgId = 0;
	}
	return 0;
}

int snap_shot(int display)
{
	return c_display::snap_shot(display);
}