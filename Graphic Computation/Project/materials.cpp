/* Simão Monteiro Nº 2019215412 */

// Libraries
#include "materials.h"

void initMaterials(int material)
{
    switch (material)
    {

    // Obsidian
    case 0:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidian_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidian_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidian_specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidian_shine);
        break;

    // Silver
    case 1:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silver_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silver_specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silver_shine);
        break;
    }
}
