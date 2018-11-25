#ifndef HEATMAP
#define HEATMAP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <future>
#include <ncurses.h>

#include "../helpers/utils.h"
#include "Keyboard.h"


const LedKeyboard::Color defaultColor= {0x00, 0xff, 0x00};
const LedKeyboard::Color heatColor= {0x00, 0x00, 0xff};
const uint8_t increase = 0x2f;
const uint8_t decrease = 0x08;


int heatmap(LedKeyboard &kbd, std::string arg2);

#endif