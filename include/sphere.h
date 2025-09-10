#ifndef SPHERE_H
#define SPHERE_H

#include <SFML/Graphics.hpp>
#include "3dvector.h"

const float PIXELS_PER_UNIT = 300;
const int SPECULAR_POW = 32;

typedef Vector Color;
typedef Vector Dot3d;

class Sphere{
    Dot3d center;
    Color color;
    float radius;

    public:
    Sphere(Dot3d center, float radius, Color color);
    void drawAmbient(sf::RenderWindow& window,
                     Color light_color = {255, 255, 255},
                     float ambient_intensity = 0.1f);
    void drawDiffuse(sf::RenderWindow& window,
                     Dot3d light_pos,
                     Color light_color = {255, 255, 255},
                     float ambient_intensity = 0.1f);
    void drawSpecular(sf::RenderWindow& window,
                      Dot3d light_pos,
                      Dot3d camera_pos,
                      Color light_color = {255, 255, 255},
                      float ambient_intensity = 0.1f,
                      float specular_intensity = 0.5f);

    private:
    bool isDotOnSphere(sf::Vector2f dot2d) const;
    float getZ(sf::Vector2f dot2d) const;
    Color ambient(Color light_color, float ambient_intensity);
    Color diffuse(Vector sphere_norm, Vector light_vec, Dot3d light_pos, Color light_color);
    Color specular(Vector sphere_norm, Vector light_vec, Vector camera_vec, Vector reflect_vec, Color light_color, float specular_intensity);
};

#endif
