cmake_minimum_required(VERSION 3.21.0)
project(windarkmode
  VERSION 1.0.0
  DESCRIPTION "Windows Dark Mode support"
  HOMEPAGE_URL https://github.com/emanspeaks/windarkmode
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

## configure CMake module search paths that depend on the project
## proj src dir is location of this file
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CompileCommands)
include(DefaultBuildType)
include(DefaultInstallPath)
include(ForceUnicode)
include(DefineWindows)
include(HideVSCodeVars)

add_subdirectory(uxtheme-stub)
add_subdirectory(windarkmode)
