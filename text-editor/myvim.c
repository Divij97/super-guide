#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include "texteditor.h"

struct termios orig;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig);
    struct termios raw = orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    atexit(disableRawMode);
}

int deleteLastCharacter() {
    int x, y;
    getyx(stdscr, y, x);
    int lastch = mvinch(y, x - 1);
    delch();
    return lastch;
}

Command lastcommand = {START_OF_PROGRAM, 0};

void undo() {
    
}

void execute_ctrl_character(int currch) {
    switch currch:
        case CTRL_Z:
            undo();
        case CTRL_Q:
            exit();
}

void executecommand(int currch) {
    switch (currch) {
        case KEY_BACKSPACE: 
            lastcommand.op = DEL_CHARACTER;
            lastcommand.arg = deleteLastCharacter();
            printw("%d", lastcommand.arg);
            break;
        
        // All CTRL + 'ch' map to numbers b/w 0 - 31
        // so currch & 31 will be equal to currch 
        case currch & 31: 
            execute_ctrl_character(currch);
            break;
        default: 
            lastcommand.op = ADD_CHARACTER;
            lastcommand.arg = currch;
            addch(currch);
        
    }
}

int main() {

    // Initializes screen
    initscr();
    
    // equivalent to removing Canonical mode
    raw();

    // Doesn't echo characters in terminal
    noecho();

    // Allows control character to not do any thing special
    keypad(stdscr, TRUE);
    
    int ch;
    while (ch != 'q') {
        ch = getch();
        executecommand(ch);
    }

    refresh();
    endwin();
    return 0;
}