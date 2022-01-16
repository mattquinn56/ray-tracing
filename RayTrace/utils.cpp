#include <cmath>
#include <stdio.h>
#include "utils.h"

// Color functions
Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
Color::Color(double v) {
    this->r = v;
    this->g = v;
    this->b = v;
}
Color::Color() {
    this->r = NULL;
    this->g = NULL;
    this->b = NULL;
}
Color Color::operator+(Color c) {
    return Color(this->r + c.r, this->g + c.g, this->b + c.b);
}
Color Color::operator*(Color c) {
    return Color(this->r * c.r, this->g * c.g, this->b * c.b);
}
Color Color::operator/(double d) {
    return Color(this->r / d, this->g / d, this->b / d);
}

// Position functions
Position::Position(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
Position::Position() {
    this->x = NULL;
    this->y = NULL;
    this->z = NULL;
}
Position Position::negative() {
    return Position(-1 * this->x, -1 * this->y, -1 * this->z);
}
Position Position::normalize() {
    double magn = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    return Position(this->x / magn, this->y / magn, this->z / magn);
}
double Position::dot(Position p) {
    Position mult(this->x * p.x, this->y * p.y, this->z * p.z);
    return mult.x + mult.y + mult.z;
}
double Position::magn() {
    return sqrt(this->dot(*this));
}
Position Position::cross(Position p) {
    Position out = Position(0, 0, 0);
    out.x = this->y * p.z - this->z * p.y;
    out.y = this->z * p.x - this->x * p.z;
    out.z = this->x * p.y - this->y * p.x;
    return out;
}
Position Position::operator+(Position p) {
    return Position(this->x + p.x, this->y + p.y, this->z + p.z);
}
Position Position::operator+(double i) {
    return Position(this->x + i, this->y + i, this->z + i);
}
Position Position::operator-(Position p) {
    return Position(this->x - p.x, this->y - p.y, this->z - p.z);
}
Position Position::operator*(Position p) {
    return Position(this->x * p.x, this->y * p.y, this->z * p.z);
}
Position Position::operator*(double i) {
    return Position(this->x * i, this->y * i, this->z * i);
}
Position Position::operator/(double d) {
    return Position(this->x / d, this->y / d, this->z / d);
}

void print(Position p) {
    printf("(%f, %f, %f)", p.x, p.y, p.z);
}
void print(Color c) {
    printf("(%f, %f, %f)", c.r, c.g, c.b);
}