#include <iostream>

#include "Camera.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Window.h"

int main() {
  std::srand(std::time(nullptr));
  Camera camera(Vector(0, 5, -5));
  Window window(320, 200);

  std::vector<Object*> objects = {
      new Cube(Vector(-5, 5, 5), Vector(0, 10, 20)),
      new Cube(Vector(5, 5, 5), Vector(0, 10, 20)),
      new Cube(Vector(0, 0, 5), Vector(10, 0, 20)),
      new Cube(Vector(0, 10, 5), Vector(10, 0, 20)),
      new Cube(Vector(0, 5, 10), Vector(10, 10, 0)),
      new Cube(Vector(0, 5, -5.1), Vector(10, 10, 0)),

      new Sphere(Vector(-1, 2, 7), 2),
      new Cube(Vector(3, 1, 7), Vector(2), Vector(0, 0.5, 0)),
      new Sphere(Vector(-3, 1.5, 3), 1.5),
      new Cube(Vector(1.5, 0.5, 4), Vector(1), Vector(0, -0.3, 0)),
  };
  objects[0]->setColor(255, 192, 127);
  objects[0]->setDiffusionLevel(0.9);
  objects[1]->setColor(127, 192, 255);
  objects[1]->setDiffusionLevel(0.9);
  objects[2]->setDiffusionLevel(0.9);
  objects[3]->setLuminosity(true);
  objects[4]->setDiffusionLevel(0.9);
  objects[5]->setDiffusionLevel(0.9);

  objects[6]->setDiffusionLevel(0.1);
  objects[7]->setColor(64, 192, 192);
  objects[7]->setDiffusionLevel(0.3);
  objects[8]->setColor(255, 192, 192);
  objects[8]->setDiffusionLevel(0.7);
  objects[9]->setColor(255, 127, 127);
  objects[9]->setDiffusionLevel(0.7);

  while (window.isOpen()) {
    auto events = window.eventProcessing();
    for (const auto &event : events) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
          camera.move(Vector(0, 0.01, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::A) {
          camera.move(Vector(-0.01, 0, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::S) {
          camera.move(Vector(0, -0.01, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::D) {
          camera.move(Vector(0.01, 0, 0));
          window.resetSamples();
        }

        if (event.key.code == sf::Keyboard::Left) {
          camera.rotate(Vector(0, 0.01, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::Right) {
          camera.rotate(Vector(0, -0.01, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::Up) {
          camera.rotate(Vector(-0.01, 0, 0));
          window.resetSamples();
        }
        if (event.key.code == sf::Keyboard::Down) {
          camera.rotate(Vector(0.01, 0, 0));
          window.resetSamples();
        }
      }
    }

    if (window.getApproximationTimes() < 65536) {
      std::cout << "Rendering: step " << window.getApproximationTimes() + 1;
      camera.render(window, objects);
      std::cout << " - done" << std::endl;

      if (window.getApproximationTimes() == 4 || window.getApproximationTimes() == 16 ||
      window.getApproximationTimes() == 64 || window.getApproximationTimes() == 256 ||
      window.getApproximationTimes() == 1024 || window.getApproximationTimes() == 4096 ||
      window.getApproximationTimes() == 16384 || window.getApproximationTimes() == 65536)
        window.save("../6_" + std::to_string(window.getApproximationTimes()) + ".ppm");
    }
  }
}