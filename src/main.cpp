#include <SFML/Graphics.hpp>

#include "3dvector.h"
#include "sphere.h"

const int MAIN_WINDOW_WIDTH = 1000;
const int MAIN_WINDOW_HEIGHT = 800;

void updateLightPos(Dot3d& light_pos){
    static float time = 0.0f;
    float speed = 0.15f;
    time += speed;

    float radius = 6.f;

    light_pos.x = radius * std::cos(time);
    light_pos.y = -2.f + 2.f * std::sin(time * 2.0f);
}

int main(){
    sf::RenderWindow window(sf::VideoMode({MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT}), "My window");

    Dot3d light_pos = {3, 2, 4};
    Dot3d center = {0, 0, 0};
    Dot3d camera_pos = {0, 0, 4};
    float radius = 1;
    Color sphere_color = {255, 0, 0};

    Sphere sphere(center, radius, sphere_color);

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        updateLightPos(light_pos);
        sphere.drawSpecular(window, light_pos, camera_pos);

        window.display();
    }
}
