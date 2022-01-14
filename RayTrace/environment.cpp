#include "environment.h"

// Red tan green example

// Construct materials
Material tanmat(Color(.7, .7, .4), Color(.6), 20, Color(.4));
Material graymat(Color(.2, .2, .2), Color(.6), 20, Color(.4));
Material redmat(Color(.9, .1, .1), Color(.6), 20, Color(.4));
Material greenmat(Color(.2, .9, .4), Color(.6), 20, Color(.4));

// Construct spheres
Position p1(0, 0, 0);
Position p2(0, -40, 0);
Position p3(1.5, 0, -.5);
Position p4(-.75, 0, 1.75);
Sphere tansphere(p1, .5, tanmat);
Sphere graysphere(p2, 39.5, graymat);
Sphere redsphere(p3, .5, redmat);
Sphere greensphere(p4, .5, greenmat);

// Construct scene
std::vector<Sphere> spherelst = { tansphere, graysphere, redsphere, greensphere };
Color bgcolor(.2, .3, .5);
Scene scene(spherelst, bgcolor);

// Construct lights
Color superbright(255);
PointLight pointlight(Position(12, 10, 5), superbright);

std::vector<PointLight> pointlights = { pointlight };
AmbientLight ambientlight(Color(.3));

// Construct camera
Position eye(-3, 2.7, -5);
Position target(0, 0, 0);
Position up(0, 1, 0);
Camera camera(eye, target, up, 25);

sf::Uint8* getImg(int xres, int yres) {
	camera.aspect = (double) xres / yres;
	return render(camera, scene, pointlights, ambientlight, xres, yres);
}

/*
// Allison example
// Construct materials
Material graymat(Color(41. / 255, 239. / 255, 41. / 255), Color(0), 20, Color(.2));
Material mat1(Color(157. / 255, 38. / 255, 236. / 255), Color(0), 20, Color(.3));
Material mat2(Color(236. / 255, 229. / 255, 38. / 255), Color(0), 20, Color(0));

// Construct spheres
Position p2(0, -40, 0);
Position p3(1.5, 0, -.5);
Position p4(-.75, 0, 1.75);
Sphere graysphere(p2, 39.5, graymat);
Sphere yellow(p3, 1.5, mat2);
Sphere purple(p4, .1666667, mat1);

// Construct scene
std::vector<Sphere> spherelst = { graysphere, yellow, purple };
Color bgcolor(38. / 255, 236. / 255, 223. / 255);
Scene scene(spherelst, bgcolor);

// Construct lights
Color superbright(255);
PointLight pointlight(Position(-8, .25, 12), superbright);
std::vector<PointLight> pointlights = { pointlight };
AmbientLight ambientlight(Color(.1, .1, .1));

// Construct camera
Position eye(3, 2.7, 5);
Position target(0, 0, 0);
Position up(0, 1, 0);
Camera camera(eye, target, up, 25);
*/