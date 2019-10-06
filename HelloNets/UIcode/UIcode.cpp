#include "GuiLite.h"
#include <math.h>

#if (defined __linux__) || (defined WIN32)
	#define POINT_COL		25
	#define POINT_ROW		20
	#define X_SPACE			18
	#define Y_SPACE			25
	#define STRING_LENGHT	12
#else
	#define POINT_COL		20
	#define POINT_ROW		24
	#define X_SPACE			9
	#define Y_SPACE			14
	#define STRING_LENGHT	4
#endif

#define FRICTION		0.98
#define GRAVITY_ACC		0.05
#define DELTA_TIME		0.1

static c_display* s_display;
static c_surface* s_surface;

class c_point
{
public:
	void set(float x, float y, bool fixed)
	{
		m_x = m_last_x = x; m_y = m_last_y = y; m_fixed = fixed;
		m_vx = m_vy = 0;
	}
	void update_location(float dt)
	{
		if (m_fixed) { return; }
		m_last_x = m_x; m_last_y = m_y;
		s_surface->draw_pixel(m_x, m_y, GL_RGB(0, 0, 0), Z_ORDER_LEVEL_0);
		m_vx *= FRICTION; m_vy *= FRICTION;
		m_x += m_vx * dt; m_y += m_vy * dt;
		s_surface->draw_pixel(m_x, m_y, GL_RGB(255, 255, 255), Z_ORDER_LEVEL_0);
	}
	float distance(c_point* p)
	{
		float dx = m_x - p->m_x;
		float dy = m_y - p->m_y;
		return sqrt(dx*dx + dy*dy);
	}

	float m_x, m_y, m_vx, m_vy;
	float m_last_x, m_last_y;
	bool m_fixed;
};

class c_string
{
public:
	void set(c_point* p1, c_point* p2, float length)
	{
		m_p1 = p1; m_p2 = p2; m_length = length;
	}
	void update_point_velocity()
	{
		float force = (m_p1->distance(m_p2) - m_length) / 2;
		float dx = m_p1->m_x - m_p2->m_x;
		float dy = m_p1->m_y - m_p2->m_y;
		float d = sqrt(dx*dx + dy*dy);

		float nx = dx / d; float ny = dy / d;
		if (!m_p1->m_fixed)
		{
			m_p1->m_vx -= nx * force;
			m_p1->m_vy -= ny * force;
			m_p1->m_vy += GRAVITY_ACC;
		}
		if (!m_p2->m_fixed)
		{
			m_p2->m_vx += nx * force;
			m_p2->m_vy += ny * force;
			m_p2->m_vy += GRAVITY_ACC;
		}
	}
	void draw()
	{
		if (m_p1->m_x == m_p1->m_last_x && m_p1->m_y == m_p1->m_last_y &&
			m_p2->m_x == m_p2->m_last_x && m_p2->m_y == m_p2->m_last_y)
		{
			return;
		}
		s_surface->draw_line(m_p1->m_last_x, m_p1->m_last_y, m_p2->m_last_x, m_p2->m_last_y, GL_RGB(0, 0, 0), Z_ORDER_LEVEL_0);
		s_surface->draw_line(m_p1->m_x, m_p1->m_y, m_p2->m_x, m_p2->m_y, GL_RGB(255, 255, 255), Z_ORDER_LEVEL_0);
	}
private:
	c_point* m_p1, * m_p2;
	float m_length;
};

c_point points[POINT_COL][POINT_ROW];
c_string strings[(POINT_COL - 1) * POINT_ROW + POINT_COL * (POINT_ROW - 1)];

void trigger(int x, int y, bool is_down)
{
	if (is_down)
	{
		points[POINT_COL / 2][POINT_ROW / 2].m_x = points[POINT_COL / 2][POINT_ROW / 2].m_last_x = x;
		points[POINT_COL / 2][POINT_ROW / 2].m_y = points[POINT_COL / 2][POINT_ROW / 2].m_last_y = y;
		points[POINT_COL / 2][POINT_ROW / 2].m_fixed = true;
	}
	else
	{
		points[POINT_COL / 2][POINT_ROW / 2].m_fixed = false;
	}
}

void run(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	s_display = new c_display(phy_fb, screen_width, screen_height, screen_width, screen_height, color_bytes, 1, gfx_op);
	s_surface = s_display->alloc_surface(Z_ORDER_LEVEL_0);
	s_surface->set_active(true);
	s_surface->fill_rect(0, 0, screen_width - 1, screen_height - 1, GL_RGB(0, 0, 0), Z_ORDER_LEVEL_0);

	//init points
	for (int y = 0; y < POINT_ROW; y++)
	{
		for (int x = 0; x < POINT_COL; x++)
		{
			points[x][y].set(X_SPACE * 2 + x * X_SPACE, Y_SPACE * 2 + y * Y_SPACE, y == 0);
		}
	}

	//init strings
	int sum = 0;
	for (int y = 0; y < POINT_ROW; y++)
	{
		for (int x = 0; x < POINT_COL - 1; x++)
		{
			strings[sum++].set(&points[x][y], &points[x + 1][y], STRING_LENGHT);
		}
	}
	for (int y = 0; y < POINT_ROW - 1; y++)
	{
		for (int x = 0; x < POINT_COL; x++)
		{
			strings[sum++].set(&points[x][y], &points[x][y + 1], STRING_LENGHT);
		}
	}
	ASSERT(sum == sizeof(strings) / sizeof(c_string));

	//update
	while (1)
	{
		for (int i = 0; i < sum; i++)
		{
			strings[i].update_point_velocity();
		}

		for (int y = 0; y < POINT_ROW; y++)
		{
			for (int x = 0; x < POINT_COL; x++)
			{
				points[x][y].update_location(DELTA_TIME);
			}
		}

		for (int i = 0; i < sum; i++)
		{
		#if (defined __linux__) || (defined WIN32)
			strings[i].draw();
		#endif
		}
		thread_sleep(10);
		// Auto trigger for MCU
	#if (defined __linux__) || (defined WIN32)
	#else
		static int count;
		if (++count % 500 == 0)
		{
			trigger(0, 0, true);
			trigger(0, 0, false);
		}
	#endif
	}
}
//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloNets(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	run(phy_fb, width, height, color_bytes, gfx_op);
}

void sendTouch2HelloNets(int x, int y, bool is_down)
{
	trigger(x, y, is_down);
}

void* getUiOfHelloNets(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloNets()
{
	return s_display->snap_shot("snap_short.bmp");
}