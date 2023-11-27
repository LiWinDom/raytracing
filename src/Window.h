#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

#include "Vector.h"

class Window {
 public:
  Window(uint16_t width, uint16_t height) {
    window_ = new sf::Window(
        sf::VideoMode(width, height),
        "Raytracing",
        sf::Style::Close
    );

    changeSize(width, height);

    glEnable(GL_TEXTURE_2D);
    window_->setVerticalSyncEnabled(true);
  }

  bool isOpen() const { return window_->isOpen(); }

  uint16_t getWidth() const { return width_; }

  uint16_t getHeight() const { return height_; }

  size_t getApproximationTimes() const { return approximationTimes_; }


  void setPixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

  void setPixel(uint16_t x, uint16_t y, const Vector& color);

  void addSample();

  void resetSamples();

  std::vector<sf::Event> eventProcessing();

  void draw() const;

  void save(const std::string& fileName) const;

 private:
  sf::Window* window_;

  uint8_t *frame_ = nullptr;
  uint16_t width_ = 0, height_ = 0;

  uint64_t *framesSum_ = nullptr;
  size_t approximationTimes_ = 0;

  void changeSize(uint16_t width, uint16_t height);
};
