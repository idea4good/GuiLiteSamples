#define GUILITE_ON	//Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 3D engine
void multiply(int m, int n, int p, float* a, float* b, float* c)// a[m][n] * b[n][p] = c[m][p]
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			c[i * p + j] = 0;
			for (int k = 0; k < n; k++) {
				c[i * p + j] += a[i * n + k] * b[k * p + j];
			}
		}
	}
}

void rotateX(float angle, float* point, float* output)// rotate matrix for X
{
	static float rotation[3][3];
	rotation[0][0] = 1;
	rotation[1][1] = cos(angle);
	rotation[1][2] = 0 - sin(angle);
	rotation[2][1] = sin(angle);
	rotation[2][2] = cos(angle);
	multiply(3, 3, 1, (float*)rotation, point, output);
}

void rotateY(float angle, float* point, float* output)// rotate matrix for Y
{
	static float rotation[3][3];
	rotation[0][0] = cos(angle);
	rotation[0][2] = sin(angle);
	rotation[1][1] = 1;
	rotation[2][0] = 0 - sin(angle);
	rotation[2][2] = cos(angle);
    multiply(3, 3, 1, (float*)rotation, point, output);
}

void rotateZ(float angle, float* point, float* output)// rotate matrix for Z
{
	static float rotation[3][3];
	rotation[0][0] = cos(angle);
	rotation[0][1] = 0 - sin(angle);
	rotation[1][0] = sin(angle);
	rotation[1][1] = cos(angle);
	rotation[2][2] = 1;	
    multiply(3, 3, 1, (float*)rotation, point, output);
}

void projectOnXY(float* point, float* output, float zFactor = 1)
{
	static float projection[2][3];//project on X/Y face
	projection[0][0] = zFactor;//the raio of point.z and camera.z
	projection[1][1] = zFactor;//the raio of point.z and camera.z
    multiply(2, 3, 1, (float*)projection, point, output);
}

#define UI_WIDTH	240
#define UI_HEIGHT	320
#define SPACE		13
#define ROW			15
#define COL			15
#define POINT_CNT	ROW * COL
#define AMPLITUDE	50
static c_surface* s_surface;
static c_display* s_display;

class Cwave
{
public:
	Cwave()
	{
		rotate_angle = 0;//1.57;
		angle = 0;
		memset(points2d, 0, sizeof(points2d));
		for (int y = 0; y < ROW; y++)
		{
			for (int x = 0; x < COL; x++)
			{
				points[y * COL + x][0] = x * SPACE - (UI_WIDTH / 2);
				points[y * COL + x][1] = y * SPACE - (UI_WIDTH / 2);
			}
		}
	}
	virtual void draw(int x, int y, bool isErase)
	{
		for (int i = 0; i < POINT_CNT; i++)
		{
			float factor = (1 + points[i][2] / AMPLITUDE) / 2;
			unsigned int color = GL_RGB(210 * factor, 130 * factor, 255 *  factor);
			s_surface->fill_rect(points2d[i][0] + x - 1, points2d[i][1] + y - 1, points2d[i][0] + x + 1, points2d[i][1] + y + 1, (isErase) ? 0 : color, Z_ORDER_LEVEL_0);
		}
	}
	virtual void swing(float rotate_angle_diff)
	{
		if (rotate_angle_diff == 0.0)
		{
			angle += 0.1;
			for (int y = 0; y < ROW; y++)
			{
				for (int x = 0; x < COL; x++)
				{
					float offset = sqrt((x - COL / 2) * (x - COL / 2) + (y - ROW / 2) * (y - ROW / 2)) / 2;
					points[y * COL + x][2] = sin(angle + offset) * AMPLITUDE;
				}
			}
		}
		else
		{
			rotate_angle += rotate_angle_diff;
			if (rotate_angle > 1.0)
			{
				rotate_angle = 1.0;
			}
			if (rotate_angle < 0.0)
			{
				rotate_angle = 0.0;
			}
		}

		float rotateOut1[3][1];
		for (int i = 0; i < POINT_CNT; i++)
		{
			rotateX(rotate_angle, points[i], (float*)rotateOut1);
			float zFactor = UI_WIDTH / (UI_WIDTH - rotateOut1[2][0]);
			projectOnXY((float*)rotateOut1, (float*)points2d[i], zFactor);
		}
	}
private:
	static float points[POINT_CNT][3];
	float points2d[POINT_CNT][2];
	float angle, rotate_angle;
};

float Cwave::points[POINT_CNT][3];//x, y, z

// Demo
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	static c_display display(phy_fb, screen_width, screen_height, &surface, driver);
	s_surface = &surface;
	s_display = &display;
		
	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	
	Cwave theCwave;
	unsigned int step = 0;
	while(1) {
		theCwave.draw(30 + (UI_WIDTH / 2), UI_HEIGHT / 2, true);//erase footprint

		if (step > 400)
		{
			step = 0;
		}
		else if (step > 300)
		{
			theCwave.swing(-0.01);
		}
		else if (step > 200)
		{
			theCwave.swing(0.0);
		}
		else if (step > 100)
		{
			theCwave.swing(0.01);
		}
		else
		{
			theCwave.swing(0.0);
		}
		
		theCwave.draw(30 + (UI_WIDTH / 2), UI_HEIGHT / 2, false);//refresh Cwave
		thread_sleep(25);
		step++;
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHello3Dwave(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	create_ui(phy_fb, width, height, color_bytes, driver);
}

extern "C" void* getUiOfHello3Dwave(int* width, int* height, bool force_update)
{
    return s_display->get_updated_fb(width, height, force_update);
}
