cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(READ "${CMAKE_SOURCE_DIR}/VERSION" VER_RAW)

string(STRIP ${VER_RAW} VERSION)

project(
  caper
  DESCRIPTION "Alternative to hyprpaper, to implement non-interactive widgets"
  VERSION ${VERSION})

set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")

message(STATUS "Building caper...")

configure_file(systemd/caper.service.in systemd/caper.service @ONLY)

include_directories(.)

set(CMAKE_CXX_STANDARD 23)

# sets unstable WLRoots features
add_compile_options(-DWLR_USE_UNSTABLE)
add_compile_options(-Wall -Wextra -Wno-unused-parameter -Wno-unused-value
		    -Wno-missing-field-initializers -Wno-narrowing)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(hyprwayland-scanner 0.4.0 REQUIRED)

pkg_check_modules(
  deps
  REQUIRED
  IMPORTED_TARGET
  wayland-client
  wayland-protocols
  cairo
  pango
  pangocairo
  libjpeg
  libwebp
  libjxl
  libjxl_cms
  libjxl_threads
  hyprlang>=0.2.0
  hyprutils>=0.2.0
  hyprgraphics)

file(GLOB_RECURSE SRCFILES "src/*.cpp")

add_executable(caper ${SRCFILES})

pkg_get_variable()

