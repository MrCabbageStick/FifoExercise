#ifndef COMMON_C_FILE
#define COMMON_C_FILE

#include <stdlib.h>
#include <stdio.h>

///// SETUP /////

#define FIFO_FILE_PATH "./fifo.file"
#define FIFO_FILE_MODE 0666
#define STDIN_FD 0
#define STDOUT_FD 1
#define BUFFER_SIZE 2048


///// ERROR HANDLING /////

int error_handler(int code, int error_code, const char* error_msg, void(*on_error)(int code)){
    if(code == error_code){
        perror(error_msg);

        if(on_error != NULL) on_error(code);
    }

    return code;
}

int negative_one_error_handler(int code, const char* error_msg, void(*on_error)(int code)){
    return error_handler(code, -1, error_msg, on_error); 
}


#endif // !COMMON_C_FILE