#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <string.h>
#include <iostream>

using namespace std;

static struct termios stored_settings;

void set_keypress(void)
{
    struct termios new_settings;

    tcgetattr(0,&stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}
int main() {
    set_keypress();
    char a;
    cin >> a;
    cout << "ВОТ ТЫ И ПОПАЛСЯ!!!!" << endl;
    int i = 0;
    for (int i = 0; i <= 5; ++i) {
        cout << "input a number:" << endl;
        cin >> i;
        cout << "The number you input is:" << i << endl;
    }
    reset_keypress();  
}
