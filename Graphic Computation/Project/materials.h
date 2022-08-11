/* Simão Monteiro Nº 2019215412 */

#ifndef MATERIALS_H
#define MATERIALS_H

// Libraries
#include <windows.h>
#include <GL\Glut.h>

// Prototype
void initMaterials(int material);

// Obsidian Coeficients
GLfloat obsidian_ambient[] = {0.05375, 0.05, 0.06625};
GLfloat obsidian_diffuse[] = {0.18275, 0.17, 0.22525};
GLfloat obsidian_specular[] = {0.332741, 0.328634, 0.346435};
GLfloat obsidian_shine = 38.4;

// Silver Coeficients
GLfloat silver_ambient[] = {0.19225, 0.19225, 0.19225};
GLfloat silver_diffuse[] = {0.50754, 0.50754, 0.50754};
GLfloat silver_specular[] = {0.508273, 0.508273, 0.508273};
GLint silver_shine = 91.2;

#endif
