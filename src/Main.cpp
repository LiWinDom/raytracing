#include <chrono>
#include <fstream>
#include <iostream>
#include <cstdint>

#include "lib/json.hpp"

#include "Camera.h"
#include "IO.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Window.h"

using Json = nlohmann::json;

Json parseArgs(const int argc, const char* argv[]) {
  Json parameters = {
      {"width", 1280},
      {"height", 720},
      {"showWindow", true}
  };

  for (size_t i = 1; i < argc; ++i) {
    if (!std::strcmp(argv[i], "--width") || !std::strcmp(argv[i], "-w")) {
      parameters["width"] = std::stoi(argv[i + 1]);
      ++i;
    }
    else if (!std::strcmp(argv[i], "--height") || !std::strcmp(argv[i], "-h")) {
      parameters["height"] = std::stoi(argv[i + 1]);
      ++i;
    }
    else if (!std::strcmp(argv[i], "--noWindow")) {
      parameters["showWindow"] = false;
    }
    else {
      parameters["fileName"] = argv[i];
    }
  }
  return parameters;
}

void parseObjectsJson(const Json& json, Camera*& camera, std::vector<IObject*>& objects) {
  if (!json.contains("Camera")){
    throw std::runtime_error(R"(Cannot find "Camera" object. Please check your objects file)");
  }
  if (!json.contains("Objects")){
    throw std::runtime_error(R"(Cannot find "Objects" object. Please check your objects file)");
  }

  // Camera parsing
  if (!json["Camera"].contains("Position")) {
    throw std::runtime_error(R"("Camera" - not found "Position" property. Please check your objects file)");
  }
  if (!json["Camera"]["Position"].contains("x") || !json["Camera"]["Position"].contains("y") || !json["Camera"]["Position"].contains("z")) {
    throw std::runtime_error(R"("Camera" -> "Position" - missing coordinate. Please check your objects file)");
  }
  Vector cameraPos(json["Camera"]["Position"]["x"].get<double>(), json["Camera"]["Position"]["y"].get<double>(), json["Camera"]["Position"]["z"].get<double>());
  Vector cameraAngle(0);
  if (json["Camera"].contains("Angle")) {
    if (!json["Camera"]["Angle"].contains("x") || !json["Camera"]["Angle"].contains("y") || !json["Camera"]["Angle"].contains("z")) {
      throw std::runtime_error(R"("Camera" -> "Angle" - missing coordinate. Please check your objects file)");
    }
    cameraAngle = Vector(json["Camera"]["Angle"]["x"].get<double>(), json["Camera"]["Angle"]["y"].get<double>(), json["Camera"]["Angle"]["z"].get<double>());
  }
  camera = new Camera(cameraPos, cameraAngle);

  // Objects parsing
  objects.resize(json["Objects"].size());
  for (size_t i = 0; i < json["Objects"].size(); ++i) {
    Json current = json["Objects"][i];
    if (!current.contains("Name")) {
      throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] - not found "Name" property. Please check your objects file)");
    }
    if (!current.contains("Position")) {
      throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] - not found "Position" property. Please check your objects file)");
    }
    if (!current["Position"].contains("x") || !current["Position"].contains("y") || !current["Position"].contains("z")) {
      throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] -> "Position" - missing coordinate. Please check your objects file)");
    }
    std::string name = current["Name"];
    Vector pos(current["Position"]["x"].get<double>(), current["Position"]["y"].get<double>(), current["Position"]["z"].get<double>());
    Vector angle(0);
    Vector color(255, 255, 255);
    double diffusionLevel = 0;
    bool luminosity = false;

    if (current.contains("Angle")) {
      if (!current["Angle"].contains("x") || !current["Angle"].contains("y") || !current["Angle"].contains("z")) {
        throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] -> "Angle" - missing coordinate. Please check your objects file)");
      }
      angle = Vector(current["Angle"]["x"].get<double>(), current["Angle"]["y"].get<double>(), current["Angle"]["z"].get<double>());
    }
    if (current.contains("Color")) {
      if (!current["Color"].contains("red") || !current["Color"].contains("green") || !current["Color"].contains("blue")) {
        throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] -> "Color" - missing color channel. Please check your objects file)");
      }
      color = Vector(current["Color"]["red"].get<uint8_t>(), current["Color"]["green"].get<uint8_t>(), current["Color"]["blue"].get<uint8_t>());
    }
    if (current.contains("DiffusionLevel")) {
      diffusionLevel = current["DiffusionLevel"].get<double>();
    }
    if (current.contains("Luminosity")) {
      luminosity = current["Luminosity"].get<bool>();
    }

    // Object specified
    if (name == "Sphere") {
      if (!current.contains("Radius")) {
        throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] - not found "Radius" property. Please check your objects file)");
      }
      double radius = current["Radius"].get<double>();

      objects[i] = new Sphere(pos, radius);
      objects[i]->setColor(color.getX(), color.getY(), color.getZ());
      objects[i]->setDiffusionLevel(diffusionLevel);
      objects[i]->setLuminosity(luminosity);
    }
    else if (name == "Cube") {
      if (!current.contains("Size")) {
        throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] - not found "Size" property. Please check your objects file)");
      }
      if (!current["Size"].contains("x") || !current["Size"].contains("y") || !current["Size"].contains("z")) {
        throw std::runtime_error(R"("Objects" -> [)" + std::to_string(i) + R"(] -> "Size" - missing coordinate. Please check your objects file)");
      }
      Vector size(current["Size"]["x"].get<double>(), current["Size"]["y"].get<double>(), current["Size"]["z"].get<double>());

      objects[i] = new Cube(pos, size, angle);
      objects[i]->setColor(color.getX(), color.getY(), color.getZ());
      objects[i]->setDiffusionLevel(diffusionLevel);
      objects[i]->setLuminosity(luminosity);
    }
    else {
      throw std::runtime_error(R"("IObject" -> [)" + std::to_string(i) + R"(] -> "Name" - unknown shape. Please check your objects file)");
    }
  }
}

int main(const int argc, const char* argv[]) {
  Json args = parseArgs(argc, argv);

  // Reading objects file
  if (!args.contains("fileName")) {
    throw std::runtime_error("No object json file specified");
  }
  std::ifstream file(args["fileName"].get<std::string>());
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file \"" + args["fileName"].get<std::string>() + "\"");
  }

  Json objectsJson;
  uint64_t* framesSum = nullptr;
  size_t approximationTimes;
  try {
    file >> objectsJson;
    file.close();
  }
  catch (const nlohmann::json_abi_v3_11_2::detail::parse_error& err) {
    // Not an object file
    file.close();

    uint16_t width, height;
    if (!IO::loadState(args["fileName"].get<std::string>(), objectsJson,
                       width, height,
                       framesSum, approximationTimes)) {
      throw std::runtime_error("Cannot open file \"" + args["fileName"].get<std::string>() + "\"");
    }
    args["width"] = width;
    args["height"] = height;
  }

  Camera* camera;
  std::vector<IObject*> objects;
  parseObjectsJson(objectsJson, camera, objects);

  // Everything is ok
  std::srand(std::time(nullptr));
  std::cout.setf(std::ios::unitbuf);
  Window window(args["width"].get<uint16_t>(), args["height"].get<uint16_t>(), args["showWindow"].get<bool>());
  if (framesSum != nullptr) {
    window.setApproximation(framesSum, approximationTimes);
  }
  auto start = std::chrono::steady_clock::now();

  while (window.isOpen()) {
    std::cout << "Rendering: step " << window.getApproximationTimes() + 1;

    auto stepStart = std::chrono::steady_clock::now();
    camera->render(window, objects);
    auto stepEnd = std::chrono::steady_clock::now();

    std::cout << " - done in " << std::chrono::duration_cast<std::chrono::milliseconds>(stepEnd - stepStart).count()
              << "ms";
    std::cout << " (total: " << std::chrono::duration_cast<std::chrono::seconds>(stepEnd - start).count() << "s)"
              << '\n';

    std::cout << "Saving state...\r";
    if (!IO::saveState("latest.rts", objectsJson,
                       window.getWidth(), window.getHeight(),
                       window.getFramesSum(), window.getApproximationTimes())) {
      std::cout << R"(Failed to save to "latest.rts")" << '\n';
    }
    std::cout << "Saving image...\r";
    if (!IO::savePPM("latest.ppm", window.getWidth(), window.getHeight(), window.getFrame())) {
      std::cout << R"(Failed to save to "latest.ppm")" << '\n';
    }

    switch (window.getApproximationTimes()) {
    case 4:
    case 16:
    case 64:
    case 256:
    case 1024:
    case 4096:
    case 16386:
    case 65536:
      const std::string fileName = std::to_string(window.getApproximationTimes()) + "_steps.ppm";
      if (IO::savePPM(fileName, window.getWidth(), window.getHeight(), window.getFrame())) {
        std::cout << "Saved to \"" << fileName << "\"" << '\n';
      }
      else {
        std::cout << "Failed to save to \"" << fileName << "\"" << '\n';
      }
    }

    window.eventProcessing();
  }
}