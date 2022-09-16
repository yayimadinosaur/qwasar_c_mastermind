
// you must create a Makefile, and the ouput is the command itself
// It will contain rule all/clean/fclean (re => fclean + all)

// You can use:

// printf(3)
// write(2)
// read(2)
// rand() (/ srand())
// time()
// atoi()
// You can NOT use:
// Any functions/syscalls which does not appear in the previous list
// Yes, it includes exit
// Consider writing a README.md to describe your project and how it works.

// Your mastermind needs to handle the sequence Ctrl + d. It's End Of File.
// It's consider as a normal execution.

#include <stdio.h>  //printf
#include <unistd.h> //read?
#include <stdlib.h> //for atoi

void initial_message(void){
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
}

void win_message(void){
    printf("Congratz! You did it!\n");
}

void round_message(int round_number){
    printf("---\nRound %d\n", round_number);
}

void invalid_input_message(void){
    printf("Wrong input!\n");
}

void current_progress(int correct, int wrong){
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", correct, wrong);
}

int read_user_input(void){
    //read stdin
        //if length != 4
            //fail
            //return -1
        //if user input isn't all numbers (valid nums 0-9)
            //fail
            //return -2
}

void start_game(char* code, int attempts){

}

int my_str_compare(char* string1, char* string2){

}

int check_attempt_value(char* num_str){
    int value = atoi(num_str);
    //  not a number or negative number
    if (value <= 0)
        return -1;
    return 0;
}

int check_code_values(char* num_str){
    for(int i = 0; num_str[i] != '\0'; i += 1) {
        int value = atoi(num_str[i]);
        //  checks value 1 - 9
        if (!(value > 0 && value <= 9)) {
            //  checks value 0
            if (num_str[i] != '0')
                return -1;
        }
    }
    return 0;
}

int parse_user_parameters(char* user_parameters){
    if (my_str_compare(user_parameters, "-c") == 0)
        return 1;
    else if (my_str_compare(user_parameters, "-t") == 0)
        return 2;
}

int main(int ac, char** av){
    printf("total args [%i]\n", ac);
    printf("test [%s]\n", av[0]);
    switch(ac){
        // //  program
        // case 0:
        // printf("[%s]", av[0]);
        // break;

        //  arg 1 - random code
        case 1:
        printf("[%s]", av[0]);
        break;

        case 2: //random code
        printf("[%s][%s]", av[0], av[1]);
        break;

        case 3: //user specifies code or attempts
        printf("[%s][%s][%s]", av[0], av[1], av[2]);
        break;

        case 4: //  only 3 args, invalid
        printf("[%s][%s][%s][%s]", av[0], av[1], av[2], av[3]);
        break;

        case 5: //random code + attempts
        printf("[%s][%s][%s][%s][%s]", av[0], av[1], av[2], av[3], av[4]);

        //6 or more args
        default:
        printf("over 5 args AC [%i]", ac);
        break;
    }
    return 0;
}