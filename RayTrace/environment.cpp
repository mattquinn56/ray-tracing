#include "environment.h"

sf::Uint8* getImg(int xres, int yres, int sel) {
	if (sel == 1) {
		// Shiny Marbles example

		// Construct materials
		Material graymat(Color(.2), Color(.6), 5, Color(.4));
		Material tanmat(Color(.7, .7, .4), Color(.6), 5, Color(.4));
		Material redmat(Color(.9, .1, .1), Color(.6), 5, Color(.4));
		Material greenmat(Color(.2, .9, .4), Color(.6), 5, Color(.4));

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

		// Define constants
		double rad = .6;

		// Construct materials
		Material graymat(Color(.5), Color(.6), 8, Color(.3));
		Material supershiny(Color(.8), Color(.6), 8, Color(.5));

		// Construct ground
		Position v1(10, 0, 15);
		Position v2(10, 0, -15);
		Position v3(-10, 0, 15);
		Position v4(-10, 0, -15);
		Triangle ground1(v1, v2, v3, graymat);
		Triangle ground2(v3, v2, v4, graymat);

		// Construct spheres
		Position p1(0, rad, 2);
		Position p2(0, rad, -2);
		Sphere sphere1(p1, rad, supershiny);
		Sphere sphere2(p2, rad, supershiny);

		// Construct scene
		std::vector<Sphere> spherelst = { sphere1, sphere2 };
		std::vector<Triangle> trilist = { ground1, ground2 };
		Color bgcolor(.2, .3, .5);
		Scene scene(spherelst, trilist, bgcolor);

		// Construct lights
		Color org(255, 165, 0);
		Color blu(0, 0, 255);
		PointLight pointlight1(Position(0, rad, 13.5), org);
		PointLight pointlight2(Position(0, rad, -13.5), blu);
		std::vector<PointLight> pointlights = { pointlight1, pointlight2 };
		AmbientLight ambientlight(Color(0));

		// Construct camera
		Position eye(8, 5 + rad, 0);
		Position target(0, rad, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 45, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
	else if (sel == 3) {
		// Criss-Cross Rainbow example

		// Define constants
		double onesixth = 1.0472; // 1/6th of a rotation, in radians
		double smallr = 4;
		double bigr = 15;
		double sphr = .6;

		// Construct colors
		Color red(1, 0, 0);
		Color orange(.75, .25, 0);
		Color yellow(.5, .5, 0);
		Color green(0, 1, 0);
		Color blue(0, 0, 1);
		Color indigo(.33, 0, .67);
		Color purple(.5, 0, .5);

		// Construct materials
		Material graymat(Color(.75), Color(.6), 2, Color(.15));
		Material supershiny(Color(.8), Color(.6), 2, Color(.75));

		// Construct ground
		Position v1(15, 0, 15);
		Position v2(15, 0, -15);
		Position v3(-15, 0, 15);
		Position v4(-15, 0, -15);
		Triangle ground1(v1, v2, v3, graymat);
		Triangle ground2(v3, v2, v4, graymat);

		// Construct spheres
		Position p1(smallr * cos(onesixth), sphr, smallr * sin(onesixth));
		Position p2(smallr * cos(2*onesixth), sphr, smallr * sin(2 * onesixth));
		Position p3(smallr * cos(3*onesixth), sphr, smallr * sin(3 * onesixth));
		Position p4(smallr * cos(4*onesixth), sphr, smallr * sin(4 * onesixth));
		Position p5(smallr * cos(5*onesixth), sphr, smallr * sin(5 * onesixth));
		Position p6(smallr * cos(6*onesixth), sphr, smallr * sin(6 * onesixth));
		Sphere s1(p1, sphr, supershiny);
		Sphere s2(p2, sphr, supershiny);
		Sphere s3(p3, sphr, supershiny);
		Sphere s4(p4, sphr, supershiny);
		Sphere s5(p5, sphr, supershiny);
		Sphere s6(p6, sphr, supershiny);

		// Construct scene
		std::vector<Sphere> spherelst = { s1, s2, s3, s4, s5, s6 };
		std::vector<Triangle> trilist = { ground1, ground2 };
		Color bgcolor(.2, .2, .2);
		Scene scene(spherelst, trilist, bgcolor);

		// Construct lights
		Color superbright(255);
		PointLight pl1(Position(bigr * cos(onesixth), sphr, bigr * sin(onesixth)), red * superbright);
		PointLight pl2(Position(bigr * cos(2*onesixth), sphr, bigr * sin(2*onesixth)), orange * superbright);
		PointLight pl3(Position(bigr * cos(3*onesixth), sphr, bigr * sin(3*onesixth)), yellow * superbright);
		PointLight pl4(Position(bigr * cos(4*onesixth), sphr, bigr * sin(4*onesixth)), green * superbright);
		PointLight pl5(Position(bigr * cos(5*onesixth), sphr, bigr * sin(5*onesixth)), blue * superbright);
		PointLight pl6(Position(bigr * cos(6*onesixth), sphr, bigr * sin(6*onesixth)), purple * superbright);
		std::vector<PointLight> pointlights = { pl1, pl2, pl3, pl4, pl5, pl6 };
		AmbientLight ambientlight(Color(.3));

		// Construct camera
		Position eye(6, 15, 0);
		Position target(0, 0, 0);
		Position up(0, 1, 0);
		Camera camera(eye, target, up, 40, (double)xres / yres);

		return render(camera, scene, pointlights, ambientlight, xres, yres);
	}
	else if (sel == 4) {
		// Snowman example

		// Construct materials
		Material groundmat(Color(.85, .85, 1), Color(.6), 20, Color(.3));
		Material snowmat(Color(.85, .85, 1), Color(.6), 20, Color(0));
		Material matteblack(Color(.1, .1, .1), Color(.6), 20, Color(0));

		// Construct spheres
		Position p0(0, -40, 0);
		Sphere ground(p0, 40, groundmat);
		Sphere ball1(Position(0, .4-.2, 0), .4, snowmat);
		Sphere ball2(Position(0, .9 - .2, 0), .275, snowmat);
		Sphere ball3(Position(0, 1.275 - .2, 0), .2, snowmat);
		Sphere eye1(Position(.075, 1.35 - .2, .19), .025, matteblack);
		Sphere eye2(Position(.15, 1.35 - .2, .14), .025, matteblack);

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
	else {
		// Pyramid example

		// Construct ground
		Color sandcol(.3, .275, .2);
		Material sandmat(sandcol, Color(.6), 3, Color(.1));
		Position v1(25, 0, 15);
		Position v2(25, 0, -15);
		Position v3(-25, 0, 15);
		Position v4(-25, 0, -15);
		Triangle sand1(v1, v2, v3, sandmat);
		Triangle sand2(v3, v2, v4, sandmat);

		// Construct triangles for pyramid 1
		Material pyrmat(sandcol * .9, Color(.6), 3, Color(.1));
		Position p1c1(2, 0, 2);
		Position p1c2(2, 0, -2);
		Position p1c3(-2, 0, -2);
		Position p1c4(-2, 0, 2);
		Position p1top(0, 2, 0);
		Triangle p1t1(p1c1, p1c2, p1top, pyrmat);
		Triangle p1t2(p1c2, p1c3, p1top, pyrmat);
		Triangle p1t3(p1c3, p1c4, p1top, pyrmat);
		Triangle p1t4(p1c4, p1c1, p1top, pyrmat);

		// Construct triangles for pyramid 2
		Position p2c1(4, 0, 6);
		Position p2c2(4, 0, 2);
		Position p2c3(0, 0, 2);
		Position p2c4(0, 0, 6);
		Position p2top(2, 2, 4);
		Triangle p2t1(p2c1, p2c2, p2top, pyrmat);
		Triangle p2t2(p2c2, p2c3, p2top, pyrmat);
		Triangle p2t3(p2c3, p2c4, p2top, pyrmat);
		Triangle p2t4(p2c4, p2c1, p2top, pyrmat);

		// Construct scene
		std::vector<Triangle> trilist = { sand1, sand2, p1t1, p1t2, p1t3, p1t4, p2t1, p2t2, p2t3, p2t4 };
		Color bgcolor(.2, .3, .6);
		Scene scene({}, trilist, bgcolor);

		// Construct lights
		Color verybright(255);
		Color peach(1, .8, .8);
		PointLight pointlight(Position(12, 10, 3), verybright * peach);
		std::vector<PointLight> pointlights = { pointlight };
		AmbientLight ambientlight(Color(.425));

		// Construct camera
		Position eye(5, 2, -15);
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