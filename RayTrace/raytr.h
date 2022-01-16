#pragma once
#ifndef RAYTR_H
#define RAYTR_H

#include <SFML/Graphics.hpp>
#include "utils.h"

struct Ray {
public:
	Position origin;
	Position direction;
	double start;
	double end;
	/*
	* Constructs the ray.
	* Parameters:
	*	origin: the 3D point representing the ray's origin
	*	direction: the 3D point representing the ray's direction
	*	start: a scalar representing the t-value where the ray starts
	*	end: a scalar representing the t-value where the ray ends
	*/
	Ray(Position origin, Position direction, double start = 0, double end = std::numeric_limits<double>::infinity());;
};

struct Material {
public:
	Color kd;
	Color ks;
	int p;
	Color km;
	Color ka;
	/*
	* Constructs the material.
	* Parameters:
	*	kd: the color of the diffuse coefficient
	*	ks: the color of the specular coefficient
	*	p: the specular exponent
	*	km: the color of the mirror coefficient
	*	ka: the color of the ambient coefficient
	*/
	Material(Color kd = Color(), Color ks = Color(0), int p = 20, Color km = Color(0), Color ka = Color());
};

struct Hit {
public:
	double t;
	Position point;
	Position normal;
	Material material;
	/*
	* Constructs the hit.
	* Parameters:
	*	t: a scalar representing the t-intersection along the ray
	*	point: where the intersection occurs
	*	normal: the outward-facing normal vector from the intersection
	*	material: the material of the surface hit
	*/
	Hit(double t = NULL, Position point = Position(), Position normal = Position(), Material material = Material());
};

class Sphere {
public:
	Position center;
	double radius;
	Material material;
	/*
	* Constructs the sphere.
	* Parameters:
	*	center: the 3D point center of the sphere
	*	radius: the scalar radius of the sphere
	*	material: the material of the sphere
	*/
	Sphere(Position center, double radius, Material material);

	/*
	* Computes the first intersection between a ray and this sphere.
	* Parameters:
	*	ray: the ray used for intersection
	* Return:
	*	the Hit for this ray-object intersection.
	*/
	Hit intersect(Ray ray);
};

class Camera {
public:
	Position eye;
	Position target;
	Position up;
	double aspect;
	double vfov;
	/*
	* Constructs the camera.
	* Parameters:
	*	eye: the 3D location of the camera
	*	target: the 3D point at which the camera is facing
	*	up: the 3D point that represents the direction of up
	*	aspect: the ratio of the width to the height of the field of view
	*	vfov: the vertical field of view, in radians
	*/
	Camera(Position eye, Position target, Position up, double vfov, double aspect = 90);

	/*
	* Creates a ray to represent a point in the viewpoint.
	* Parameters:
	*	xpt: how far along the x-axis the point is, from 0 to 1
	*	ypt: how far along the y-axis the point is, from 0 to 1
	* Return:
	*	the Ray that corresponds to this location.
	*/
	Ray generate_ray(double xpt, double ypt);
};

class PointLight {
public:
	Position pos;
	Color intensity;
	/*
	* Constructs the point light.
	* Parameters:
	*	position: the position of the point light
	*	intensity: the color of the point light's intensity
	*/
	PointLight(Position pos, Color intensity);

	/*
	* Computes the shading due to this light at this ray-object intersection.
	* Parameters:
	*	ray: the ray that hit the object
	*	hit: the data for this ray-object intersection
	* Return:
	*	the Color representing the shading due to this point light.
	*/
	Color illuminate(Ray ray, Hit hit);
};

class AmbientLight {
public:
	Color intensity;
	/*
	* Constructs the ambient light.
	* Parameters:
	*	intensity: the colored intensity of the ambient light
	*/
	AmbientLight(Color intensity);

	/*
	* Computes the shading due to this light at this ray-object intersection.
	* Parameters:
	*	hit: the data for this ray-object intersection
	* Return:
	*	the Color representing the shading due to this ambient light.
	*/
	Color illuminate(Hit hit);
};

class Scene {
public:
	std::vector<Sphere> spheres;
	Color bgcolor;
	/*
	* Constructs the scene.
	* Parameters:
	*	spheres: a vector of all spheres in the scene
	*	bgcolor: the background color of the scene
	*/
	Scene(std::vector<Sphere> spheres, Color bgcolor);

	/*
	* Computes the first intersection between a ray and an object in the scene.
	* Parameters:
	*	ray: the ray
	* Return:
	*	the Hit for this ray-object intersection.
	*/
	Hit intersect(Ray ray);
};
	

/*
* Calculates shading where a ray hits an object.
* Parameters:
*	ray: the ray that hit the object
*	hit: the data for this ray-object intersection
*	scene: the scene
*	pointlights: a vector of all pointlights
*	ambientlight: the ambient light
*	depth: the current recursion depth for computing reflections
* Return:
*	the Color representing the shading at this point.
*/
Color shade(Ray ray, Hit hit, Scene scene, std::vector<PointLight> pointlights, AmbientLight ambientlight, int depth = 4);

/*
* Creates an array of RGBA pixels representing the ray-traced image.
* Parameters:
*	camera: indicates the perspective
*	scene: depicts all objects to be seen
*	pointlights: a vector of all pointlights
*	ambientlight: the ambient light
*   xres: the number of pixels in the x-dimension
*   yres: the number of pixels in the y-dimension
* Return:
*   an RGBA array of size [xres * yres * 4].
*/
sf::Uint8* render(Camera &camera, Scene scene, std::vector<PointLight> pointlights, AmbientLight ambientlight, int xres, int yres);

#endif