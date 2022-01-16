#pragma once
#ifndef UTILS_H
#define UTILS_H

struct Color {
public:
	double r;
	double g;
	double b;
	/*
	* Constructs the RGB color.
	* Parameters:
	*	r: the red part, can range from 0 to 1
	*	g: the green part, can range from 0 to 1
	*	b: the blue part, can range from 0 to 1
	*/
	Color(double r, double g, double b);

	/*
	* Constructs a black/gray/white RGB color.
	* Parameters:
	*	v: the brightness, from 0 to 1
	*/
	Color(double v);

	// Constructs a color with null RGB values
	Color();

	// Adds this color and c, element-wise
	Color operator+(Color c);

	// Multiplies this color and c, element-wise
	Color operator*(Color c);

	// Divides by double d, element-wise
	Color operator/(double d);
};

struct Position {
public:
	double x;
	double y;
	double z;
	/*
	* Constructs a 3D position.
	* Parameters:
	*	x: the x-coordinate
	* 	y: the y-coordinate
	* 	z: the z-coordinate
	*/
	Position(double x, double y, double z);

	// Constructs a position with null xyz values
	Position();

	// Returns this position multipled by -1
	Position negative();

	// Returns the normalized position
	Position normalize();

	// Returns the dot product of this position and p
	double dot(Position p);

	// Returns the magnitude of this position
	double magn();

	// Returns the cross product of this position and p
	Position cross(Position p);

	// Adds this position and p/i, element-wise
	Position operator+(Position p);
	Position operator+(double i);

	// Subtracts this position and p, element-wise
	Position operator-(Position p);

	// Multiplies this position and p/i, element-wise
	Position operator*(Position p);
	Position operator*(double i);

	// Divides by double d, element-wise
	Position operator/(double d);
};

void print(Position p);
void print(Color c);


#endif