#include "IO.h"

bool IO::savePPM(const std::string& fileName, const uint16_t width, const uint16_t height, const uint8_t* frame) {
  std::ofstream file(fileName);
  if (!file.is_open()) return false;

  // Saving
  file << "P6\n" << width << " " << height << "\n255\n";
  for (size_t i = 0; i < height; ++i) {
    for (size_t j = 0; j < width; ++j) {
      size_t index = ((height - i - 1) * width + j) * 3;
      file << frame[index] << frame[index + 1] << frame[index + 2];
    }
  }

  file.close();
  return true;
}

bool IO::saveState(const std::string& fileName, const Json& objects,
               const uint16_t width, const uint16_t height,
               const uint64_t* framesSum, const size_t& approximationTimes) {
  std::ofstream file(fileName);
  if (!file.is_open()) return false;

  // File version
  file << "RaytracingState " << 0 << '\n';

  // Saving objects json
  file << objects.dump() << '\n';

  // Saving window info
  file << width << ' ' << height << ' ' << approximationTimes << '\n';
  for (size_t i = 0; i < width * height * 3; ++i) {
    file << framesSum[i] << ' ';
  }

  file.close();
  return true;
}

bool IO::loadState(const std::string& fileName, Json& objects,
                   uint16_t& width, uint16_t& height,
                   uint64_t*& framesSum, size_t& approximationTimes) {
  std::ifstream file(fileName);
  if (!file.is_open()) return false;

  // File version
  std::string header;
  uint64_t fileVer;
  file >> header >> fileVer;
  if (header != "RaytracingState" || fileVer != 0) {
    file.close();
    return false;
  }

  // Loading objects json
  file >> objects;

  // Loading window info
  file >> width >> height >> approximationTimes;
  framesSum = new uint64_t[width * height * 3];
  for (size_t i = 0; i < width * height * 3; ++i) {
    file >> framesSum[i];
  }

  file.close();
  return true;
}
