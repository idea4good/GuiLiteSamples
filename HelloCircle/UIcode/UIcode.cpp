#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define UI_WIDTH	240
#define UI_HEIGHT	320
#define CIRCLE_X	120
#define CIRCLE_Y	160
#define CIRCLE_BOLD	3
#define PI			3.1415926535
#define SMALL_RADIUS	35
#define BIG_RADIUS		50
static c_surface* s_surface;
static c_display* s_display;

// 3D engine
void multiply(int m, int n, int p, double* a, double* b, double* c)// a[m][n] * b[n][p] = c[m][p]
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

void rotateX(double angle, double* point, double* output)// rotate matrix for X
{
	static double rotation[3][3];
	rotation[0][0] = 1;
	rotation[1][1] = cos(angle);
	rotation[1][2] = 0 - sin(angle);
	rotation[2][1] = sin(angle);
	rotation[2][2] = cos(angle);
	multiply(3, 3, 1, (double*)rotation, point, output);
}

void rotateY(double angle, double* point, double* output)// rotate matrix for Y
{
	static double rotation[3][3];
	rotation[0][0] = cos(angle);
	rotation[0][2] = sin(angle);
	rotation[1][1] = 1;
	rotation[2][0] = 0 - sin(angle);
	rotation[2][2] = cos(angle);
    multiply(3, 3, 1, (double*)rotation, point, output);
}

void projectOnXY(double* point, double* output, double zFactor = 1)
{
	static double projection[2][3];//project on X/Y face
	projection[0][0] = zFactor;//the raio of point.z and camera.z
	projection[1][1] = zFactor;//the raio of point.z and camera.z
    multiply(2, 3, 1, (double*)projection, point, output);
}

// Draw circle
int drawCircle(int x, int y, int r, unsigned int color,  int arcAngle = 360, double* points = 0)
{
	const double pi = PI / 180;
	int tmpX, tmpY, lastX, lastY;
	lastX = lastY = 0;
	int sumDiffPoint = 0;

	if (arcAngle != 360)
	{
		for (double angle = 0.5; angle < arcAngle; angle += 0.5)//Bigger circle, Smaller angle step
		{
			tmpX = r * cos(angle * pi);
			tmpY = r * sin(angle * pi);
			if (tmpX == lastX && tmpY == lastY)
			{
				continue;
			}
			lastX = tmpX;
			lastY = tmpY;
			s_surface->draw_pixel(x + tmpX, y + tmpY, color, Z_ORDER_LEVEL_0);
		}
		return 0;
	}

	for (double angle = 0.5; angle < 90; angle += 0.5)//Bigger circle, Smaller angle step
	{
		tmpX = r * cos(angle * pi);
		tmpY = r * sin(angle * pi);
		if (tmpX == lastX && tmpY == lastY)
		{
			continue;
		}
		lastX = tmpX;
		lastY = tmpY;

		if (points)
		{
			int index = sumDiffPoint * 3;
			points[index++] = x + tmpX;
			points[index++] = y + tmpY;
			points[index++] = 0;

			points[index++] = x - tmpX;
			points[index++] = y + tmpY;
			points[index++] = 0;

			points[index++] = x + tmpX;
			points[index++] = y - tmpY;
			points[index++] = 0;

			points[index++] = x - tmpX;
			points[index++] = y - tmpY;
			points[index++] = 0;
		}
		else
		{
			s_surface->draw_pixel(x + tmpX, y + tmpY, color, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(x - tmpX, y + tmpY, color, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(x + tmpX, y - tmpY, color, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(x - tmpX, y - tmpY, color, Z_ORDER_LEVEL_0);
		}
		sumDiffPoint += 4;
	}
	return sumDiffPoint;
}

// Circle
class Circle
{
public:
	Circle(int x, int y, int radius, unsigned int rgb, int bold, bool isRoateX = true)
	{
		this->radius = radius;
		this->isRoateX = isRoateX;
		this->rgb = rgb;
		this->x = x;
		this->y = y;
		this->bold = bold;
		curRadius = 0;
		totalPixels = drawCircle(0, 0, radius, 0, 360, (double*)points);
	}
	void draw(int x, int y, bool isErase)
	{
		for (int i = 0; i < totalPixels; i++)
		{
			s_surface->draw_pixel(points2d[i][0] + x, points2d[i][1] + y, (isErase) ? 0 : rgb, Z_ORDER_LEVEL_0);
		}
	}
	void rotate(double angle)
	{
		draw(x, y, true);//erase footprint
		double rotateOut1[3][1];
		for (int i = 0; i < totalPixels; i++)
		{
			isRoateX ? rotateX(angle, points[i], (double*)rotateOut1) : rotateY(angle, points[i], (double*)rotateOut1);
			projectOnXY((double*)rotateOut1, (double*)points2d[i]);
		}
		draw(x, y, false);//refresh circle
	}
	void updateRadius(int step)
	{
		int newRadus = radius + step;
		if (curRadius == newRadus)
		{
			return;
		}

		for (int i = 0; i < bold; i++)
		{
			int tmpRadius = (newRadus - i);
			if (tmpRadius <= curRadius && tmpRadius > (curRadius - bold))
			{
				continue;
			}
			drawCircle(x, y, tmpRadius, rgb);
		}
		
		for (int i = 0; i < bold; i++)
		{
			int tmpRadius = (curRadius - i);
			if (tmpRadius <= newRadus && tmpRadius > (newRadus - bold))
			{
				continue;
			}
			drawCircle(x, y, tmpRadius, 0);
		}

		curRadius = newRadus;
	}

	double points[364][3];
	double points2d[364][2];
	int radius, curRadius, bold;
	int x, y, totalPixels;
	unsigned int rgb;
	bool isRoateX;
};

// Demo
Circle theSmallCircle(CIRCLE_X, CIRCLE_Y, SMALL_RADIUS, GL_RGB(25, 68, 97), 8);
Circle theBigCircle(CIRCLE_X, CIRCLE_Y, BIG_RADIUS, GL_RGB(59, 152, 215), 8, false);

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	static c_display display(phy_fb, screen_width, screen_height, &surface, driver);
	s_surface = &surface;
	s_display = &display;
	
	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	double time = 0.0;
	while (time < PI * 2)
	{
		drawCircle(CIRCLE_X, CIRCLE_Y, SMALL_RADIUS, GL_RGB(25, 68, 97),  time * 180 / PI);
		drawCircle(CIRCLE_X, CIRCLE_Y, BIG_RADIUS, GL_RGB(59, 152, 215), time * 180 / PI);
		time += 0.2;
		thread_sleep(40);
	}

	time = 0.0;
	while(1) {
		if (time >= PI * 4)
		{
			s_surface->fill_rect((CIRCLE_X - BIG_RADIUS), (CIRCLE_Y - BIG_RADIUS), (CIRCLE_X + BIG_RADIUS), (CIRCLE_Y + BIG_RADIUS), 0, Z_ORDER_LEVEL_0);
			theSmallCircle.curRadius = 0;
			theBigCircle.curRadius = 0;
			time = 0;
		}
		else if(time >= PI * 3)
		{
			s_surface->fill_rect((CIRCLE_X - BIG_RADIUS), (CIRCLE_Y - BIG_RADIUS), (CIRCLE_X + BIG_RADIUS), (CIRCLE_Y + BIG_RADIUS), 0, Z_ORDER_LEVEL_0);
			theSmallCircle.rotate(time);
			theBigCircle.rotate(time);
		}
		else
		{
			theSmallCircle.updateRadius(3 * sin(time));
			theBigCircle.updateRadius(3 * sin(time + PI));
		}		
		time += 0.3;
		thread_sleep(40);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloCircle(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	create_ui(phy_fb, width, height, color_bytes, driver);
}

extern "C" void* getUiOfHelloCircle(int* width, int* height, bool force_update)
{
    return s_display->get_updated_fb(width, height, force_update);
}
