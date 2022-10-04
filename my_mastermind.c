
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
#include <unistd.h> //read
#include <stdlib.h> //for atoi rand() srand()
#include <time.h>   //time()
// #include <cstddef>   ???

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

int str_length(char *s1){
    int i = 0;
    printf("length start\n");
    while (s1[i] != '\0')
        {
            // printf("index[%i] [%i]\n", i, s1[i]);
        i += 1;
        }
    // printf("length end [%i]\n", i);
    return i;
}

char* generate_4_random_numbers(){
    char *tmp = (char*)malloc(sizeof(char) * 5);
    tmp[4] = '\0';
    time_t t;
    //  initialize random number generator?
    srand((unsigned) time(&t));
    for (int i = 0; i < 4; i += 1) {
        //  create random number 0 - 8 and cast to char
        tmp[i] = (char)((rand() % 10) + 48);
        //  lazy reset 9 to 8
        if (tmp[i] == '9')
            tmp[i] = '8';
    }
    return tmp;
}

int my_str_compare(char* string1, char* string2){
    int i = 0;
    int j = 0;
    while (string1[i] != '\0' && string2[j] != '\0') {
        if (string1[i] != string2[j])
            //  characters don't match
            return -1;
        i += 1;
        j += 1;
    }
    if (i != j)
        //  string length doesn't match
        return -2;
    return 0;
}

int check_attempt_value(char* num_str){
    int value = atoi(num_str);
    //  not a number or negative number
    if (value <= 0)
        return -1;
    return value;
}

//  checks for user input values 0 - 8
int check_code_values(char* num_str){
    // printf("starting check code val [%s]\n", num_str);
    int tmp_remove_after = str_length(num_str);
    // printf("strlen pew pewpew[%i]\n", tmp_remove_after);
    if (tmp_remove_after != 4) {
        // printf("incorrect len [%i]\n", str_length(num_str));
        return -3;
    }
    // printf ("starting custom index val check\n");
    int converted;
    for (int i = 0; num_str[i] != '\0'; i += 1){
        //  char val isn't 0 - 8 in ascii value via decimal
        converted = num_str[i] - '0';
        // printf("converted index [%i] [%i]\n", i, converted);        
        if (!(converted >= 0 && converted < 9))
        {
            // printf("custom index fail index [%i] val [%c]\n", i, num_str[i]);
            return -1;
        }
    }
    // printf("check_code_val fin\n");
    return 0;
}

//  not sure if needed?
//  checks arg 3 and 5 for flag string i.e. "-c" for 3, "-t" for 5
int parse_user_parameters(char* user_parameters, char* flag){
    int result = my_str_compare(user_parameters, flag);
    if (result < 0)
        return -1;
    return result;
}

int start_game(char* code, char* attempts, int ac){
    initial_message();
    return 1;   //TODO added to remove problem notification, please fix after
}

//  remove later, not necessary for project
char* str_duplicate(char *s1){
    printf("passed in [%s]\n", s1);
    int i = 0;
    // int length = str_length(s1);
    int length = 5;
    printf("pew\n");
    // printf("length pass [%i]", length);
    char *tmp;
    tmp = (char*)malloc((length) * sizeof(char));
    tmp[length] = '\0';
    // printf("malloc passed %i", tmp != NULL);
    printf("hmm");
    while (length > 0) {
        tmp[i] = s1[i];
        s1 += 1;
    }
    printf("str_dup pass\n");
    return tmp;
}

int main(int ac, char** av){
    printf("total args [%i]\n", ac);
    if (ac == 1) {
        int x;
        char pew[] = "abcd";
        // printf("pew is [%s]\nlast [%i]\n", pew, pew[4]);
        printf("reading user input\n");
        //  default attempts
        int attempts = 10;
        char* code = generate_4_random_numbers();
        printf("random4 [%s]\n", code);
        while ((x = read(0, pew, sizeof(pew))) > 0){
            pew[x - 1] = '\0';
            // printf("input [%s]\nx = [%i]", pew, x);
            if (attempts < 1) {
                printf("Game Over!\n");
                return -1;
            }
            round_message(attempts);
            if (x != 5){
                // printf("[ %i / 5 ] read bytes\n", x);
                invalid_input_message();
                attempts -= 1;
                continue;
            }
            if (check_code_values(pew) == 0){
                printf("check_code_val passes [%s]\n", pew);
                //  check code match w/ user input
                if (my_str_compare(code, pew) == 0)
                {
                    win_message();
                    //  match!
                    break;
                }
                attempts -= 1;
                break;
            }
            else {
                invalid_input_message();
                continue;
            }
            invalid_input_message();
        }
        //  read error
        if (x < 0){
            printf("read error\n");
            return -1;
        }
        printf("hmm input is\n[%s]\n", pew);
    }
    // printf("test [%s]\n", av[0]);
    // switch(ac){     //parse?
    //     // //  program
    //     // case 0:
    //     // printf("[%s]", av[0]);
    //     // break;

    //     //  arg 1 - random code
    //     case 1:
    //     printf("[%s]\n", av[0]);
    //     start_game(NULL, NULL, 0);
    //     break;

    //     case 2: //random code
    //     printf("[%s][%s]", av[0], av[1]);
    //     break;

    //     case 3: //user specifies code or attempts
    //     printf("[%s][%s][%s]", av[0], av[1], av[2]);
    //     break;

    //     case 4: //  only 3 args, invalid
    //     printf("[%s][%s][%s][%s]", av[0], av[1], av[2], av[3]);
    //     break;

    //     case 5: //random code + attempts
    //     printf("[%s][%s][%s][%s][%s]", av[0], av[1], av[2], av[3], av[4]);

    //     //6 or more args
    //     default:
    //     printf("over 5 args AC [%i]", ac);
    //     break;
    // }
    return 0;
}