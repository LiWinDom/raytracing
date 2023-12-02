cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME Raytracing)
project(${PROJECT_NAME} LANGUAGES CXX)

# Executables
set(EXECUTABLES src/Main.cpp src/Window.cpp src/Window.h src/Vector.cpp src/Vector.h src/Camera.cpp src/Camera.h src/IObject.cpp src/IObject.h src/Objects/Sphere.cpp src/Objects/Sphere.h src/Objects/Cube.cpp src/Objects/Cube.h src/lib/json.hpp src/IO.cpp src/IO.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_TYPE})

# Linking
set(SFML_LIBRARIES
    sfml-system
    sfml-graphics
    sfml-window
    # sfml-audio
)
set(BUILD_SHARED_LIBS OFF)

# Checking ethernet connection to be able to compile offline
if (WIN32)
  execute_process(
      COMMAND ping google.com -n 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
else()
  execute_process(
      COMMAND ping google.com -c 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
endif()
if (NO_CONNECTION GREATER 0)
  set(FETCHCONTENT_FULLY_DISCONNECTED ON)
  message(WARNING "Fetch offline mode: requires already populated _deps")
else()
  set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
endif()

# Fetching SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_INCLUDE_DIR})

# Adding executables
if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
  add_executable(${PROJECT_NAME} WIN32 ${EXECUTABLES})
else ()
  add_executable(${PROJECT_NAME} ${EXECUTABLES})
endif ()

# It's recommended to build frameworks on MacOS
if (APPLE)
  set(SFML_BUILD_FRAMEWORKS TRUE)
elseif (WIN32)
  set(LINK_FLAGS -static)
  set(SFML_STATIC_LIBRARIES TRUE)
endif ()

# Configuring executable
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES} ${LINK_FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}"
    CLEAN_DIRECT_OUTPUT 1
)

# Copying OpenAL on Windows
if (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
  add_custom_command(
      TARGET ${PROJECT_NAME}
      COMMENT "Copy OpenAL DLL"
      PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
      VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
