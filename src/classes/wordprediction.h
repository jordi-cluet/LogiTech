#ifndef WORDPREDICTION
#define WORDPREDICTION

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "../helpers/utils.h"
#include "Keyboard.h"
#include "presage.h"

const LedKeyboard::Color backgroundColor= {0x00, 0x00, 0x00};
const LedKeyboard::Color predictionColor= {0xff, 0xff, 0xff};

int wordprediction(LedKeyboard &kbd);

#endif