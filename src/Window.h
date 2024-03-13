#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

#include "Vector.h"

class Window {
 public:
  Window(const uint16_t width, const uint16_t height, const bool showWindow = true) : _showWindow(showWindow) {
    changeSize(width, height);
    if (!showWindow) return;

    _window = new sf::Window(
        sf::VideoMode(width, height),
        "Raytracing",
        sf::Style::Close
    );

    glEnable(GL_TEXTURE_2D);
    _window->setVerticalSyncEnabled(true);
  }

  bool isOpen() const {
    if (!_showWindow) return true;
    return _window->isOpen();
  }

  uint16_t getWidth() const { return _width; }

  uint16_t getHeight() const { return _height; }

  const uint8_t* getFrame() const { return _frame; }

  const uint64_t* getFramesSum() const { return _framesSum; }

  size_t getApproximationTimes() const { return _approximationTimes; }

  void setApproximation(uint64_t* framesSum, const size_t approximationTimes) {
    delete _framesSum;
    _framesSum = framesSum;
    _approximationTimes = approximationTimes;
  };


  void setPixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

  void setPixel(uint16_t x, uint16_t y, const Vector& color);

  void addSample();

  void resetSamples();

  std::vector<sf::Event> eventProcessing();

  void draw() const;

 private:
  bool _showWindow;
  sf::Window* _window;

  uint8_t *_frame = nullptr;
  uint16_t _width = 0, _height = 0;

  uint64_t *_framesSum = nullptr;
  size_t _approximationTimes = 0;

  void changeSize(uint16_t width, uint16_t height);
};
