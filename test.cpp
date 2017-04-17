#include "logutil.h"

//#include <Windows.h>
//
//#define    COLOR_NONE                    "\033[0m"
//#define     FONT_COLOR_RED             "\033[0;31m"
//#define    FONT_COLOR_BLUE            "\033[1;34m"
//
//#define    BACKGROUND_COLOR_RED        "\033[41m"    
//
//#define    BG_RED_FONT_YELLOW        "\033[41;33m"
//
//void SetColor(int ForgC)
//{
//    WORD wColor;
//    //We will need this handle to get the current background attribute
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//
//    //We use csbi for the wAttributes word.
//    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
//    {
//        //Mask out all but the background attribute, and add in the forgournd color
//        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
//        SetConsoleTextAttribute(hStdOut, wColor);
//    }
//}

int main() {
    //SetColor(1);
    //printf(FONT_COLOR_RED "hello world\n" COLOR_NONE);
    //CHECK_IF(1) << "sfasfsdf";
    ////CHECK_IF(0) << "sfasfsdf";
    //CHECK_IF(1) << "sfasfsdf";
    LOG() << "Hello, world";
    INFO() << "Hello, world";
    DEBUG() << "Test DEBUG";
    WARNING() << "WARNING";
    ERROR() << "TEST ERROR";
    FATAL() << "TEST FATAL";
    return 0;
}

