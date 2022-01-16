#include <vector>
#include <math.h>
#include "raytr.h"

const double inf = std::numeric_limits<double>::infinity();
const double ep = .00001;

// Ray functions
Ray::Ray(Position origin, Position direction, double start, double end) {
    this->origin = origin;
    this->direction = direction;
    this->start = start;
    this->end = end;
}

// Material functions
Material::Material(Color kd, Color ks, int p, Color km, Color ka) {
    this->kd = kd;
    this->ks = ks;
    this->p = p;
    this->km = km;
    this->ka = ka.r == NULL ? kd : ka;
}

// Hit functions
Hit::Hit(double t, Position point, Position normal, Material material) {
    this->t = t;
    this->point = point;
    this->normal = normal;
    this->material = material;
}

// Sphere functions
Sphere::Sphere(Position center, double radius, Material material) {
    this->center = center;
    this->radius = radius;
    this->material = material;
}
Hit Sphere::intersect(Ray ray) {
    Position oc = ray.origin - this->center;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * oc.dot(ray.direction);
    double c = oc.dot(oc) - (this->radius * this->radius);
    double discrim = b*b - 4*a*c;
    double insmult = oc.dot(ray.direction);
    double insquare = insmult*insmult - a*c;
    if (discrim < 0) {
        return Hit(inf);
    }
    else {
        double t = NULL;
        double t1 = (ray.direction.negative().dot(oc) - sqrt(insquare)) / a;
        double t2 = (ray.direction.negative().dot(oc) + sqrt(insquare)) / a;
        bool t1bad = false;
        bool t2bad = false;
        if (t1 < ray.start || t1 > ray.end) {
            t = t2;
            t1bad = true;
        }
        if (t2 < ray.start || t2 > ray.end) {
            t = t1;
            t2bad = true;
        }
        if (!t1bad && !t2bad) {
            t = t1 < t2 ? t1 : t2;
        }
        else if (t1bad and t2bad) {
            return Hit(inf);
        }
        Position point = ray.origin + (ray.direction * t);
        Position normal = (point - this->center).normalize();
        return Hit(t, point, normal, this->material);
    }
}

// Camera functions
Camera::Camera(Position eye, Position target, Position up, double vfov, double aspect) {
    this->eye = eye;
    this->target = target;
    this->up = up;
    this->vfov = vfov;
    this->aspect = aspect;
}
Ray Camera::generate_ray(double xpt, double ypt) {
    double degree_to_rad = .0174533;
    Position w = (this->target - this->eye).negative().normalize();
    Position u = this->up.cross(w).normalize();
    Position v = w.cross(u).normalize();

    double h = 2 * tan(degree_to_rad * this->vfov / 2);
    double wide = this->aspect * h;
    double u_small = xpt * wide;
    double v_small = ypt * h;
    u_small -= wide / 2;
    v_small -= h / 2;
    Position direction = (u*u_small) + (v*v_small) + w.negative();
    return Ray(this->eye, direction);
}

// PointLight functions
PointLight::PointLight(Position pos, Color intensity) {
    this->pos = pos;
    this->intensity = intensity;
}
Color PointLight::illuminate(Ray ray, Hit hit) {
    // Compute term 1 and term 2 of Blinn-Phong, then add
    Position diff = this->pos - hit.point;
    Position l = (diff).normalize();
    double lan = (diff).magn();
    double dota = hit.normal.dot(l);
    double abvzeroa = dota > 0 ? dota : 0;
    Color term1 = (this->intensity * abvzeroa) / (lan * lan);

    Position vl_add = ray.direction.negative() + l;
    Position h = (vl_add).normalize() / (vl_add).magn();
    double dotb = hit.normal.dot(h);
    double abvzerob = dotb > 0 ? dotb : 0;
    Color term2 = hit.material.kd + (hit.material.ks * pow(abvzerob, hit.material.p));
    
    return term1 * term2;
}

// AmbientLight functions
AmbientLight::AmbientLight(Color intensity) {
    this->intensity = intensity;
}
Color AmbientLight::illuminate(Hit hit) {
    return hit.material.ka * this->intensity;
}

// Scene functions
Scene::Scene(std::vector<Sphere> spheres, Color bgcolor) {
    this->spheres = spheres;
    this->bgcolor = bgcolor;
}
Hit Scene::intersect(Ray ray) {
    // Create list of all objects intersected by ray
    std::vector<Hit> hitlist = {};
    for (Sphere sph : this->spheres) {
        hitlist.push_back(sph.intersect(ray));
    }
    // Within this list, return the hit with the smallelst t
    double min_t = inf;
    double temp_t;
    int min_index = -1;
    for (int i = 0; i < hitlist.size(); ++i) {
        temp_t = hitlist[i].t;
        if (temp_t < min_t) {
            min_t = temp_t;
            min_index = i;
        }
    }
    if (min_t == inf) {
        return Hit(inf);
    }
    return hitlist[min_index];
}

// Shading and render functions
Color shade(Ray ray, Hit hit, Scene scene, std::vector<PointLight> pointlights, AmbientLight ambientlight, int depth) {
    if (hit.t == inf) {
        return scene.bgcolor;
    }
    // Light stuff
    Color totalcolor(0);
    Position adjpoint(hit.point + (hit.normal * ep));
    for (PointLight pl : pointlights) {
        Position dirpoint(pl.pos - adjpoint);
        Ray shaderay(adjpoint, dirpoint);
        Hit shadehit = scene.intersect(shaderay);
        if (shadehit.t == inf) {
            totalcolor = totalcolor + pl.illuminate(ray, hit);
        }
    }
    totalcolor = totalcolor + ambientlight.illuminate(hit);

    // Mirror stuff
    if (depth > 1) {
        double innerdot = hit.normal.dot(ray.direction.negative());
        Position r = ray.direction + (hit.normal * (2 * innerdot));
        Ray recray(adjpoint, r);
        Hit rechit = scene.intersect(recray);
        Color mirrored = shade(recray, rechit, scene, pointlights, ambientlight, depth - 1) * hit.material.km;;
        return totalcolor + mirrored;
    }
    return totalcolor;
}

sf::Uint8* render(Camera &camera, Scene scene, std::vector<PointLight> pointlights, AmbientLight ambientlight, int xres, int yres) {
    sf::Uint8* pixels = new sf::Uint8[xres * yres * 4];
    int ind;
    for (int j = 0; j < yres; ++j) {
        for (int i = 0; i < xres; ++i) {
            ind = (4 * j * xres) + (4 * i);
            Ray ray = camera.generate_ray((i + .5) / xres, (abs(j - yres) + .5) / yres);
            Hit hit = scene.intersect(ray);
            Color color = shade(ray, hit, scene, pointlights, ambientlight);
            pixels[ind] = color.r > 1 ? 255 : color.r * 255;
            pixels[ind+1] = color.g > 1 ? 255 : color.g * 255;
            pixels[ind+2] = color.b > 1 ? 255 : color.b * 255;
            pixels[ind+3] = 255;
        }
    }
    return pixels;
}