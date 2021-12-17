#include "lcd.h"
void clear(int x, int y){
    lcdPosition(0, 0);
    lcdString("                ");
    lcdPosition(1, 0);
    lcdString("                ");
    lcdPosition(x, y);
}