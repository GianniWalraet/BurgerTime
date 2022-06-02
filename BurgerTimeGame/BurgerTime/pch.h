// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <fstream>
#include <memory> // smart pointers
#include <vector>
#include <map>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#include "MiniginAPI.h"

#define GRID_SIZE 16