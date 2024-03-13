#include <fstream>

#include "Window.h"

void Window::setPixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  _frame[(y * _width + x) * 3] = red;
  _frame[(y * _width + x) * 3 + 1] = green;
  _frame[(y * _width + x) * 3 + 2] = blue;
}

void Window::setPixel(uint16_t x, uint16_t y, const Vector& color) {
  setPixel(x, y, color.getX(), color.getY(), color.getZ());
}

void Window::addSample() {
  ++_approximationTimes;
  for (size_t i = 0; i < _width * _height * 3; ++i) {
    _framesSum[i] += _frame[i];
    _frame[i] = std::min(_framesSum[i] / _approximationTimes, (uint64_t)255);
  }
}

void Window::resetSamples() {
  for (size_t i = 0; i < _width * _height * 3; ++i) {
    _framesSum[i] = 0;
  }
  _approximationTimes = 0;
}

std::vector<sf::Event> Window::eventProcessing() {
  if (!_showWindow) return {};
  std::vector<sf::Event> events;
  sf::Event event;

  while (_window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      _window->close();
      return {};
    }
    else if (event.type == sf::Event::Resized) {
      _window->setSize(sf::Vector2u(_width, _height));
      //changeSize(_window->getSize().x, _window->getSize().y);
    }
    else {
      events.push_back(event);
    }
  }
  return events;
}

void Window::draw() const {
  if (!_showWindow) return;
  glDrawPixels(_width, _height, GL_RGB, GL_UNSIGNED_BYTE, _frame);
  _window->display();
}


void Window::changeSize(uint16_t width, uint16_t height) {
  delete _frame;
  delete _framesSum;
  _frame = new uint8_t[width * height * 3];
  _framesSum = new uint64_t[width * height * 3];

  _width = width;
  _height = height;

  resetSamples();
}
