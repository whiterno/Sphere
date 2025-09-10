#include "sphere.h"

#include <stdio.h>

Sphere::Sphere(Dot3d center, float radius, Color color): center(center), radius(radius), color(color){}

bool Sphere::isDotOnSphere(sf::Vector2f dot2d) const{
    return ((dot2d.x * dot2d.x + dot2d.y * dot2d.y) <= radius * radius);
}

float Sphere::getZ(sf::Vector2f dot2d) const{
    return std::sqrt(radius * radius - dot2d.x * dot2d.x - dot2d.y * dot2d.y);
}

Color Sphere::ambient(Color light_color, float ambient_intensity){
    Color ambient = ambient_intensity * !light_color;

    return ambient * color;
}

Color Sphere::diffuse(Dot3d dot, Dot3d light_pos, Color light_color, float ambient_intensity){
    Vector sphere_norm = !(dot - center);
    Vector light_vec = !(light_pos - dot);

    float diff = std::max(0.0f, light_vec | sphere_norm);
    Color diffuse = diff * !light_color;

    Color ambient = ambient_intensity * !light_color;

    return (ambient + diffuse) * color;
}

void Sphere::drawAmbient(sf::RenderWindow& window, Color light_color, float ambient_intensity){
    sf::Vector2u size = window.getSize();
    std::vector<sf::Vertex> screen(size.x * size.y);

    for (int y = 0; y < size.y; y++){
        for (int x = 0; x < size.x; x++){
            screen[size.x * y + x] = {{(float)x, (float)y}, sf::Color::Black, {(float)x, (float)y}};
            sf::Vector2f dot = {(float)(x - size.x / 2.f) / PIXELS_PER_UNIT, (float)(y - size.y / 2.f) / PIXELS_PER_UNIT};

            if (!isDotOnSphere(dot)) continue;

            Color result = ambient(light_color, ambient_intensity);

            screen[size.x * y + x].color = sf::Color(int(result.x), int(result.y), int(result.z));
        }
    }

    window.draw(screen.data(), size.x * size.y, sf::PrimitiveType::Points);
}

void Sphere::drawDiffuse(sf::RenderWindow& window, Dot3d light_pos, Color light_color, float ambient_intensity){
    sf::Vector2u size = window.getSize();
    std::vector<sf::Vertex> screen(size.x * size.y);

    for (int y = 0; y < size.y; y++){
        for (int x = 0; x < size.x; x++){
            screen[size.x * y + x] = {{(float)x, (float)y}, sf::Color::Black, {(float)x, (float)y}};
            sf::Vector2f dot_2d = {(float)(x - size.x / 2.f) / PIXELS_PER_UNIT, (float)(y - size.y / 2.f) / PIXELS_PER_UNIT};

            if (!isDotOnSphere(dot_2d)) continue;

            Dot3d dot = {dot_2d.x, dot_2d.y, getZ(dot_2d)};

            Color result = diffuse(dot, light_pos, light_color, ambient_intensity);

            screen[size.x * y + x].color = sf::Color(int(result.x), int(result.y), int(result.z));
        }
    }

    window.draw(screen.data(), size.x * size.y, sf::PrimitiveType::Points);
}

void Sphere::drawSpecular(sf::RenderWindow& window, Dot3d light_pos, Dot3d camera_pos, Color light_color, float ambient_intensity, float specular_intensity){
    sf::Vector2u size = window.getSize();
    std::vector<sf::Vertex> screen(size.x * size.y);

    for (int y = 0; y < size.y; y++){
        for (int x = 0; x < size.x; x++){
            screen[size.x * y + x] = {{(float)x, (float)y}, sf::Color::Black, {(float)x, (float)y}};
            sf::Vector2f dot_2d = {(float)(x - size.x / 2.f) / PIXELS_PER_UNIT, (float)(y - size.y / 2.f) / PIXELS_PER_UNIT};

            if (!isDotOnSphere(dot_2d)) continue;

            Dot3d dot = {dot_2d.x, dot_2d.y, getZ(dot_2d)};

            Vector sphere_norm = !(dot - center);
            Vector light_vec = !(light_pos - dot);
            Vector camera_vec = !(camera_pos - dot);
            Vector reflect_vec = light_vec.reflect(sphere_norm);

            float diff = std::max(0.0f, light_vec | sphere_norm);
            Color diffuse = diff * !light_color;

            Color ambient = ambient_intensity * !light_color;

            float spec = std::pow(std::max(camera_vec | reflect_vec, 0.f), SPECULAR_POW);
            Color specular = specular_intensity * spec * !light_color;

            Color result = (ambient + diffuse + specular) * color;

            screen[size.x * y + x].color = sf::Color(int(result.x), int(result.y), int(result.z));
        }
    }

    window.draw(screen.data(), size.x * size.y, sf::PrimitiveType::Points);
}
