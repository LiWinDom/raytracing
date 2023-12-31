#include <fstream>

#include "Window.h"

void Window::setPixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  frame_[(y * width_ + x) * 3] = red;
  frame_[(y * width_ + x) * 3 + 1] = green;
  frame_[(y * width_ + x) * 3 + 2] = blue;
}

void Window::setPixel(uint16_t x, uint16_t y, const Vector& color) {
  setPixel(x, y, color.getX(), color.getY(), color.getZ());
}

void Window::addSample() {
  ++approximationTimes_;
  for (size_t i = 0; i < width_ * height_ * 3; ++i) {
    framesSum_[i] += frame_[i];
    frame_[i] = std::min(framesSum_[i] / approximationTimes_, (uint64_t)255);
  }
}

void Window::resetSamples() {
  for (size_t i = 0; i < width_ * height_ * 3; ++i) {
    framesSum_[i] = 0;
  }
  approximationTimes_ = 0;
}

std::vector<sf::Event> Window::eventProcessing() {
  if (!showWindow_) return {};
  std::vector<sf::Event> events;
  sf::Event event;

  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
      return {};
    }
    else if (event.type == sf::Event::Resized) {
      window_->setSize(sf::Vector2u(width_, height_));
      //changeSize(window_->getSize().x, window_->getSize().y);
    }
    else {
      events.push_back(event);
    }
  }
  return events;
}

void Window::draw() const {
  if (!showWindow_) return;
  glDrawPixels(width_, height_, GL_RGB, GL_UNSIGNED_BYTE, frame_);
  window_->display();
}


void Window::changeSize(uint16_t width, uint16_t height) {
  delete frame_;
  delete framesSum_;
  frame_ = new uint8_t[width * height * 3];
  framesSum_ = new uint64_t[width * height * 3];

  width_ = width;
  height_ = height;

  resetSamples();
}
