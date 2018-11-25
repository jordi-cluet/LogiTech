#include "heatmap.h"
using namespace std;

int heatKey(LedKeyboard &kbd, LedKeyboard::KeyValue &key) {
    uint8_t increase = 0x15;
    if(defaultColor.green) {
        if(key.color.green > increase) {
            key.color.green -= increase;
        }
        else {
            key.color.green = 0;
        }
    }
    if(defaultColor.blue) {
        if(key.color.blue > increase) {
            key.color.blue -= increase;
        }
        else {
            key.color.blue = 0;
        }
    }
    if(defaultColor.red) {
        if(key.color.red > increase) {
            key.color.red -= increase;
        }
        else {
            key.color.red = 0;
        }
    }


    if(heatColor.green) {
        if (key.color.green + increase > 0xff) {
            key.color.green = 0xff;
        } else {
            key.color.green += increase;
        }
    }
    if(heatColor.blue) {
        if (key.color.blue + increase > 0xff) {
            key.color.blue = 0xff;
        } else {
            key.color.blue += increase;
        }
    }
    if(heatColor.red) {
        if (key.color.red + increase > 0xff) {
            key.color.red = 0xff;
        } else {
            key.color.red += increase;
        }
    }

    if(! kbd.setKey(key)) return 1;
    if(! kbd.commit()) return 1;

}

int coolKey(LedKeyboard &kbd, LedKeyboard::KeyValue &key) {
    uint8_t decrease = 0x08;
    if (key.color.red <= defaultColor.red) {
        if(key.color.red + decrease > defaultColor.red) {
            key.color.red = defaultColor.red;
        }
        else {
            key.color.red += decrease;
        }
    }else {
        key.color.red -= decrease;
    }
    if (key.color.green <= defaultColor.green) {
        if(key.color.green + decrease > defaultColor.green) {
            key.color.green = defaultColor.green;
        }
        else {
            key.color.green += decrease;
        }
    }else {
        key.color.green -= decrease;
    }
    if (key.color.blue <= defaultColor.blue) {
        if(key.color.blue + decrease > defaultColor.blue) {
            key.color.blue = defaultColor.blue;
        }
        else {
            key.color.blue += decrease;
        }
    }else {
        key.color.blue -= decrease;
    }

    if(! kbd.setKey(key)) return 1;
    if(! kbd.commit()) return 1;
}


int heatmap(LedKeyboard &kbd, string arg2)
{   

    //init
    uint8_t delay;
    uint8_t decreasDelay = 10;
    utils::parseUInt8(arg2, delay);
    if (! kbd.open()) return 1;
    kbd.setAllKeys(defaultColor);
    if(! kbd.commit()) return 1;

    LedKeyboard::KeyValueArray heatArray(36);
    LedKeyboard::KeyValueArray heatArray(36);
    for (uint i=0; i < heatArray.size(); i++) {

        LedKeyboard::Key key;
	    
        string token;
        if (i < 10) {
            token = '0' + i;
        }
        else {
            token = 'a' + i - 10;
        }

        if (! utils::parseKey(token, key)) return 1;
        heatArray[i] = { key, defaultColor };
    }
    
    initscr();
    timeout(0);


    char c;
    int index = -1;
    time_t lastKeyPress = time(nullptr);
    time_t lastDecrease = time(nullptr);

    while (true) {
        if (time(nullptr) - lastKeyPress > delay) {
            for (uint i=0; i < heatArray.size(); i++) {
                coolKey(kbd, heatArray[i]);
            }
            time_t lastDecrease = time(nullptr);
        }
        c = getch();
        
        if ('0' <= c && c <= '9') {
            index = c - '0';
        }
        else if ('A' <= c && c <= 'Z') {
            index = c - 'A' + 10;
        }
        else if ('a' <= c && c <= 'z') {
            index = c - 'a' + 10;
        }

        if (index >= 0) {
            if(! heatKey(kbd, heatArray[index])) return 1;
            lastKeyPress = time(nullptr);
            index = -1;
        }
    }
}