typedef enum {
    ADD_CHARACTER = 1,
    DEL_CHARACTER,
    CHANGE_MODE,
    MOVE_CURSER,
    START_OF_PROGRAM
} Operation;

typedef struct {
    Operation op;
    int arg;
} Command;
