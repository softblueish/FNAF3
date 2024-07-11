#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif
#include "graphics.hpp"
#include "objects.hpp"
#include "game.hpp"

int getScreenSize(int pos);

#endif