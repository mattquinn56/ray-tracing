#include "environment.h"

sf::Uint8* getImg(int xres, int yres, int sel) {
	if (sel == 1) {
		// Shiny Marbles example

		// Construct materials
		Material graymat(Color(.2), Color(.6), 20, Color(.4));
		Material tanmat(Color(.7, .7, .4), Color(.6), 20, Color(.4));
		Material redmat(Color(.9, .1, .1), Color(.6), 20, Color(.4));
		Material greenmat(Color(.2, .9, .4), Color(.6), 20, Color(.4));

		// Construct ground
		Position p0(0, -40, 0);
		Sphere ground(p0, 39.5, graymat);

		// Construct spheres
		Position p1(0, 0, 0);
		Position p2(1.5, 0, -.5);
		Position p3(-.75, 0, 1.75);
		Sphere tansphere(p1, .5, tanmat);
		Sphere redsphere(p2, .5, redmat);
		Sphere greensphere(p3, .5, greenmat);

		// Construct scene
		std::vector<Sphere> spherelst = { ground, tansphere, redsphere, greensphere };
		Color bgcolor(.2, .3, .5);
		Scene scene(spherelst, {}, bgcolor);

		// Construct lights
		Color superbright(255);
		PointLight pointlight(Position(12, 10, 5), superbright);
		std::vector<PointLight> pointlights = { pointlight };
		AmbientLight ambientlight(Color(.3));

		// Construct camera
		Position eye(-3, 2.7, -5);
		Position target(0, 0, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 25, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
	else if (sel == 2) {
		// Orange vs Blue example

		// Construct materials
		Material graymat(Color(.5), Color(.6), 20, Color(.3));
		Material supershiny(Color(.8), Color(.6), 20, Color(.5));

		// Construct ground
		Position v1(10, 0, 15);
		Position v2(10, 0, -15);
		Position v3(-10, 0, 15);
		Position v4(-10, 0, -15);
		Triangle ground1(v1, v2, v3, graymat);
		Triangle ground2(v3, v2, v4, graymat);

		// Construct spheres
		Position p1(0, .6, 2);
		Position p2(0, .6, -2);
		Sphere sphere1(p1, .6, supershiny);
		Sphere sphere2(p2, .6, supershiny);

		// Construct scene
		std::vector<Sphere> spherelst = { sphere1, sphere2 };
		std::vector<Triangle> trilist = { ground1, ground2 };
		Color bgcolor(.2, .3, .5);
		Scene scene(spherelst, trilist, bgcolor);

		// Construct lights
		Color org(255, 165, 0);
		Color blu(0, 0, 255);
		PointLight pointlight1(Position(0, .6, 15), org);
		PointLight pointlight2(Position(0, .6, -15), blu);
		std::vector<PointLight> pointlights = { pointlight1, pointlight2 };
		AmbientLight ambientlight(Color(0));

		// Construct camera
		Position eye(8, 5.6, 0);
		Position target(0, .6, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 35, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
	else if (sel == 3) {
		// Criss-Cross Rainbow example

		// Define constants
		double onesixth = 1.0472; // 1/6th of a rotation, in radians
		double r = 2;

		// Construct colors
		Color red(1, 0, 0);
		Color orange(1, .5, 0);
		Color yellow(1, 1, 0);
		Color green(0, 1, 0);
		Color blue(0, 0, 1);
		Color indigo(.5, 0, 1);
		Color purple(1, 0, 1);

		// Construct materials
		Material graymat(Color(.5), Color(.6), 20, Color(.3));
		Material supershiny(Color(.8), Color(.6), 20, Color(.5));

		// Construct ground
		Position v1(10, 0, 15);
		Position v2(10, 0, -15);
		Position v3(-10, 0, 15);
		Position v4(-10, 0, -15);
		Triangle ground1(v1, v2, v3, graymat);
		Triangle ground2(v3, v2, v4, graymat);

		// Construct spheres
		Position p1(r * cos(onesixth), .6, r * sin(onesixth));
		Position p2(r * cos(2*onesixth), .6, r * sin(2 * onesixth));
		Position p3(r * cos(3*onesixth), .6, r * sin(3 * onesixth));
		Position p4(r * cos(4*onesixth), .6, r * sin(4 * onesixth));
		Position p5(r * cos(5*onesixth), .6, r * sin(5 * onesixth));
		Position p6(r * cos(6*onesixth), .6, r * sin(6 * onesixth));
		Sphere s1(p1, .6, supershiny);
		Sphere s2(p2, .6, supershiny);
		Sphere s3(p3, .6, supershiny);
		Sphere s4(p4, .6, supershiny);
		Sphere s5(p5, .6, supershiny);
		Sphere s6(p6, .6, supershiny);

		// Construct scene
		std::vector<Sphere> spherelst = { s1, s2, s3, s4, s5, s6 };
		std::vector<Triangle> trilist = { ground1, ground2 };
		Color bgcolor(.2, .3, .5);
		Scene scene(spherelst, trilist, bgcolor);

		// Construct lights
		Color superbright(255);
		PointLight pointlight(Position(12, 10, 5), superbright);
		std::vector<PointLight> pointlights = { pointlight };
		AmbientLight ambientlight(Color(.3));

		// Construct camera
		Position eye(8, 5.6, 0);
		Position target(0, .6, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 35, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
	else {
		// Snowman example

		// Construct materials
		Material groundmat(Color(.85, .85, 1), Color(.6), 20, Color(.2));
		Material snowmat(Color(.85, .85, 1), Color(.6), 20, Color(0));
		Material matteblack(Color(.1, .1, .1), Color(.6), 20, Color(0));

		// Construct spheres
		Position p0(0, -40, 0);
		Sphere ground(p0, 40, groundmat);
		Sphere ball1(Position(0, .4, 0), .4, snowmat);
		Sphere ball2(Position(0, .9, 0), .275, snowmat);
		Sphere ball3(Position(0, 1.275, 0), .2, snowmat);
		Sphere eye1(Position(.075, 1.35, .19), .025, matteblack);
		Sphere eye2(Position(.15, 1.35, .14), .025, matteblack);

		// Construct scene
		std::vector<Sphere> spherelst = { ground, ball1, ball2, ball3, eye1, eye2 };
		Color bgcolor(.4, .6, 1);
		Scene scene(spherelst, {}, bgcolor);

		// Construct lights
		Color superbright(188, 188, 255);
		PointLight pointlight(Position(6, 10, 12), superbright);
		std::vector<PointLight> pointlights = { pointlight };
		AmbientLight ambientlight(Color(.5));

		// Construct camera
		Position eye(0, 2, 8);
		Position target(0, .5, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 25, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
}

/*
// Secondary (Allison) example
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