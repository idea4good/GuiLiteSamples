#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <math.h>

#define MOLECULE_TOTAL 10
#define BOND_TOTAL 45 //BOND_TOTAL = 1 + 2 + ... + (MOLECULE_TOTAL - 1)

const int UI_WIDTH = 240;
const int UI_HEIGHT = 320;
const int VELOCITY = 2;
const int BOND_MAX_DISTANCE = 80;

static c_surface* s_surface;
static c_display* s_display;

class Molecule
{
public:
	Molecule()
	{
		x = rand() % UI_WIDTH;
		y = rand() % UI_HEIGHT;
		vx = VELOCITY * ((0 == rand() % 2) ? -1 : 1);
		vy = VELOCITY * ((0 == rand() % 2) ? -1 : 1);
		color = GL_RGB(rand() % 5 * 32 + 127, rand() % 5 * 32 + 127, rand() % 5 * 32 + 127);
	}

	void move()
	{
		draw(0);
		if (x <= 0 || x >= UI_WIDTH)
		{
			vx = (0 - vx);
		}
		if (y < 0 || y >= UI_HEIGHT)
		{
			vy = (0 - vy);
		}
		x += vx;
		y += vy;
		draw(color);
	}

	void draw(unsigned int color)
	{
		s_surface->draw_pixel(x - 2, y - 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x - 1, y - 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x, y - 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 1, y - 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 2, y - 2, color, Z_ORDER_LEVEL_0);

		s_surface->draw_pixel(x - 3, y - 1, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 3, y - 1, color, Z_ORDER_LEVEL_0);

		s_surface->draw_pixel(x - 3, y, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 3, y, color, Z_ORDER_LEVEL_0);

		s_surface->draw_pixel(x - 3, y + 1, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 3, y + 1, color, Z_ORDER_LEVEL_0);

		s_surface->draw_pixel(x - 2, y + 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x - 1, y + 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x, y + 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 1, y + 2, color, Z_ORDER_LEVEL_0);
		s_surface->draw_pixel(x + 2, y + 2, color, Z_ORDER_LEVEL_0);
	}

	float x, y, vx, vy;
	unsigned int color;
};

class Bond
{
public:
	Bond()
	{
		m0 = m1 = 0;
		x0 = y0 = x1 = y1 = 0;
	}

	static void createBond(Molecule* m0, Molecule* m1)
	{
		float distance = sqrtf((m0->x - m1->x) * (m0->x - m1->x) + (m0->y - m1->y) * (m0->y - m1->y));

		int index = -1;
		for (int i = 0; i < BOND_TOTAL; i++)
		{
			if ((bonds[i].m0 == m0 && bonds[i].m1 == m1) || (bonds[i].m0 == m1 && bonds[i].m1 == m0))
			{
				index = i;
				break;
			}
		}

		if (index >= 0)
		{//has been registered
			if (distance > BOND_MAX_DISTANCE)
			{//unregister
				s_surface->draw_line(bonds[index].x0, bonds[index].y0, bonds[index].x1, bonds[index].y1, GL_RGB(0, 0, 0), Z_ORDER_LEVEL_0);
				bonds[index].m0 = bonds[index].m1 = 0;
				return;
			}
			else
			{//update bond & draw
				s_surface->draw_line(bonds[index].x0, bonds[index].y0, bonds[index].x1, bonds[index].y1, GL_RGB(0, 0, 0), Z_ORDER_LEVEL_0);
				s_surface->draw_line(m0->x, m0->y, m1->x, m1->y, color, Z_ORDER_LEVEL_0);
				bonds[index].x0 = m0->x;
				bonds[index].y0 = m0->y;
				bonds[index].x1 = m1->x;
				bonds[index].y1 = m1->y;
			}
			return;
		}

		if (distance > BOND_MAX_DISTANCE)
		{
			return;
		}
		//register new bond
		index = -1;
		for (int i = 0; i < BOND_TOTAL; i++)
		{
			if (bonds[i].m0 == 0 && bonds[i].m1 == 0)
			{
				index = i;
				break;
			}
		}
		if (index < 0)
		{//bonds full
			ASSERT(false);
			return;
		}

		//register
		bonds[index].m0 = m0;
		bonds[index].m1 = m1;
		bonds[index].x0 = m0->x;
		bonds[index].y0 = m0->y;
		bonds[index].x1 = m1->x;
		bonds[index].y1 = m1->y;
		s_surface->draw_line(m0->x, m0->y, m1->x, m1->y, color, Z_ORDER_LEVEL_0);
	}

	Molecule *m0, *m1;
	float x0, y0, x1, y1;
	static const unsigned int color = GL_RGB(0, 162, 232);
	static Bond bonds[BOND_TOTAL];
};

Bond Bond::bonds[BOND_TOTAL];

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct DISPLAY_DRIVER* driver)
{
	static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	static c_display display(phy_fb, screen_width, screen_height, &surface, driver);
	s_surface = &surface;
	s_display = &display;

	//background
	s_surface->fill_rect(0, 0, UI_WIDTH, UI_HEIGHT, 0, Z_ORDER_LEVEL_0);

	Molecule molecules[MOLECULE_TOTAL];
	while(1)
	{
		for (int i = 0; i < MOLECULE_TOTAL; i++)
		{
			molecules[i].move();
		}
		
		for (int i = 0; i < MOLECULE_TOTAL; i++)
		{
			for (int sub_i = i + 1; sub_i < MOLECULE_TOTAL; sub_i++)
			{
				Bond::createBond(&molecules[i], &molecules[sub_i]);
			}
		}
		thread_sleep(40);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloMolecule(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver)
{
	create_ui(phy_fb, width, height, color_bytes, driver);
}

extern void* getUiOfHelloMolecule(int* width, int* height, bool force_update = false)
{
	if (s_display)
	{
		return s_display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}
