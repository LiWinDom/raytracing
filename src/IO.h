#pragma once

#include "lib/json.hpp"

#include <cstdint>
#include <fstream>

using Json = nlohmann::json;

namespace IO {
  bool savePPM(const std::string& fileName, const uint16_t width, const uint16_t height, const uint8_t* frame);

  bool saveState(const std::string& fileName, const Json& objects,
                 const const uint16_t width, const uint16_t height,
                 const uint64_t* framesSum, const size_t& approximationTimes);

  bool loadState(const std::string& fileName, Json& objects,
                 uint16_t& width, uint16_t& height,
                 uint64_t*& framesSum, size_t& approximationTimes);
};
