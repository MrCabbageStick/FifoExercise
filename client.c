#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "common.c"

int main(){

    char user_input_buffer[BUFFER_SIZE];
    char reciving_buffer[BUFFER_SIZE];
    int read_user_input_bytes;
    int read_recieved_bytes;

    int fifo_file;

    while(1){

        // Open file for read
        fifo_file = negative_one_error_handler(open(FIFO_FILE_PATH, O_RDONLY), "Unable to open fifo file", exit);

        // Wait for a response
        read_recieved_bytes = negative_one_error_handler(read(fifo_file, reciving_buffer, BUFFER_SIZE), "Unable to read fifo file", exit);
        reciving_buffer[read_recieved_bytes] = '\0'; // Pseudo-clearing the buffer

        printf("Someone else: %s\n", reciving_buffer);

        // Exit if recieved message is "Bye"
        if(strncmp(reciving_buffer, "Bye", 4) == 0) break;

        // Close fifo for read
        close(fifo_file);

        // Open fifo file for write
        int fifo_file = negative_one_error_handler(open(FIFO_FILE_PATH, O_WRONLY), "Unable to open fifo file", exit);

        // Get user input
        printf("You: ");
        fflush(stdout);

        read_user_input_bytes = negative_one_error_handler(read(STDIN_FD, user_input_buffer, BUFFER_SIZE), "Unable to read stdin", exit);
        user_input_buffer[read_user_input_bytes - 1] = '\0'; // Remove \n

        // Write input to fifo file
        negative_one_error_handler(write(fifo_file, user_input_buffer, read_user_input_bytes), "Unable to write to fifo file", exit);

        // Close file for write
        close(fifo_file);

        // Exit if sent message is "Bye"
        if(strncmp(user_input_buffer, "Bye", 4) == 0) break;
    }

    // Clean-up
    unlink(FIFO_FILE_PATH);

    return 0;
}