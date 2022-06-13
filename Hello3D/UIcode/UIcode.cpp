#define GUILITE_ON	//Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define UI_WIDTH	240
#define UI_HEIGHT	320
#define SHAPE_SIZE	50
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

void rotateZ(double angle, double* point, double* output)// rotate matrix for Z
{
	static double rotation[3][3];
	rotation[0][0] = cos(angle);
	rotation[0][1] = 0 - sin(angle);
	rotation[1][0] = sin(angle);
	rotation[1][1] = cos(angle);
	rotation[2][2] = 1;	
    multiply(3, 3, 1, (double*)rotation, point, output);
}

void projectOnXY(double* point, double* output, double zFactor = 1)
{
	static double projection[2][3];//project on X/Y face
	projection[0][0] = zFactor;//the raio of point.z and camera.z
	projection[1][1] = zFactor;//the raio of point.z and camera.z
    multiply(2, 3, 1, (double*)projection, point, output);
}

// Shape
class Shape {
public:
	Shape() { angle = 0.5; }
	virtual void draw(int x, int y, bool isErase) = 0;
	virtual void rotate() = 0;
protected:
	double angle;
};

class Cube : public Shape
{
public:
	Cube()
	{
		memset(points2d, 0, sizeof(points2d));
	}
	virtual void draw(int x, int y, bool isErase)
	{
		for (int i = 0; i < 4; i++)
		{
			s_surface->draw_line(points2d[i][0] + x, points2d[i][1] + y, points2d[(i + 1) % 4][0] + x, points2d[(i + 1) % 4][1] + y, (isErase) ? 0 : 0xffff0000, Z_ORDER_LEVEL_0);
			s_surface->draw_line(points2d[i + 4][0] + x, points2d[i + 4][1] + y, points2d[((i + 1) % 4) + 4][0] + x, points2d[((i + 1) % 4) + 4][1] + y, (isErase) ? 0 : 0xff00ff00, Z_ORDER_LEVEL_0);
			s_surface->draw_line(points2d[i][0] + x, points2d[i][1] + y, points2d[(i + 4)][0] + x, points2d[(i + 4)][1] + y, (isErase) ? 0 : 0xffffff00, Z_ORDER_LEVEL_0);
		}
	}
	virtual void rotate()
	{
		double rotateOut1[3][1], rotateOut2[3][1], rotateOut3[3][1];
		for (int i = 0; i < 8; i++)
		{
			rotateX(angle, points[i], (double*)rotateOut1);
			rotateY(angle, (double*)rotateOut1, (double*)rotateOut2);
			rotateZ(angle, (double*)rotateOut2, (double*)rotateOut3);
			projectOnXY((double*)rotateOut3, (double*)points2d[i]);
		}
		angle += 0.1;
	}
private:
	static double points[8][3];
	double points2d[8][2];
};

double Cube::points[8][3] = {
	{-SHAPE_SIZE, -SHAPE_SIZE, -SHAPE_SIZE},// x, y, z
	{SHAPE_SIZE, -SHAPE_SIZE, -SHAPE_SIZE},
	{SHAPE_SIZE, SHAPE_SIZE, -SHAPE_SIZE},
	{-SHAPE_SIZE, SHAPE_SIZE, -SHAPE_SIZE},
	{-SHAPE_SIZE, -SHAPE_SIZE, SHAPE_SIZE},
	{SHAPE_SIZE, -SHAPE_SIZE, SHAPE_SIZE},
	{SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE},
	{-SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE}
};

class Pyramid : public Shape
{
public:
	Pyramid()
	{
		memset(points2d, 0, sizeof(points2d));
	}
	virtual void draw(int x, int y, bool isErase)
	{
		s_surface->draw_line(points2d[0][0] + x, points2d[0][1] + y, points2d[1][0] + x, points2d[1][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[0][0] + x, points2d[0][1] + y, points2d[2][0] + x, points2d[2][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[0][0] + x, points2d[0][1] + y, points2d[3][0] + x, points2d[3][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[0][0] + x, points2d[0][1] + y, points2d[4][0] + x, points2d[4][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);

		s_surface->draw_line(points2d[1][0] + x, points2d[1][1] + y, points2d[2][0] + x, points2d[2][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[2][0] + x, points2d[2][1] + y, points2d[3][0] + x, points2d[3][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[3][0] + x, points2d[3][1] + y, points2d[4][0] + x, points2d[4][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
		s_surface->draw_line(points2d[4][0] + x, points2d[4][1] + y, points2d[1][0] + x, points2d[1][1] + y, (isErase) ? 0 : 0xff007acc, Z_ORDER_LEVEL_0);
	}

	virtual void rotate()
	{
		double rotateOut1[3][1], rotateOut2[3][1];
		for (int i = 0; i < 5; i++)
		{
			rotateY(angle, points[i], (double*)rotateOut1);
			rotateX(0.1, (double*)rotateOut1, (double*)rotateOut2);
			double zFactor = SHAPE_SIZE / (2.2 * SHAPE_SIZE - rotateOut2[2][0]);
			projectOnXY((double*)rotateOut2, (double*)points2d[i], zFactor);
		}
		angle += 0.1;
	}
private:
	static double points[5][3];
	double points2d[5][2];
};

double Pyramid::points[5][3] = {
	{0, -SHAPE_SIZE, 0},// top
	{-SHAPE_SIZE, SHAPE_SIZE, -SHAPE_SIZE},
	{SHAPE_SIZE, SHAPE_SIZE, -SHAPE_SIZE},
	{SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE},
	{-SHAPE_SIZE, SHAPE_SIZE, SHAPE_SIZE}	
};

// Demo
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	static c_display display(phy_fb, screen_width, screen_height, &surface, driver);
	s_surface = &surface;
	s_display = &display;

	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	
	Cube theCube; Pyramid thePyramid;
	while(1) {
		theCube.draw(120, 100, true);//erase footprint
		theCube.rotate();
		theCube.draw(120, 100, false);//refresh cube

		thePyramid.draw(120, 250, true);//erase footprint
		thePyramid.rotate();
		thePyramid.draw(120, 250, false);//refresh pyramid
		thread_sleep(50);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHello3D(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	create_ui(phy_fb, width, height, color_bytes, driver);
}

extern "C" void* getUiOfHello3D(int* width, int* height, bool force_update)
{
    return s_display->get_updated_fb(width, height, force_update);
}
