#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "raytr.h"

/*
* Computes the renderred image.
* Parameters:
*	xres: the resolution in the x-direction
*	yres: the resolution in the y-direction
*	sel: an integer marking which scene to render
* Return:
*	an RGBA array of size [xres * yres * 4].
*/
sf::Uint8* getImg(int xres, int yres, int sel);

#endif