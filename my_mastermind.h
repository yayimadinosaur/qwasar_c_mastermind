#ifndef my_mastermind_h
# define my_mastermind_h

#include <stdio.h>      //  printf
# include <unistd.h>    //  write
# include <stdlib.h>	//  malloc + free
#include <stdlib.h>     //  atoi, rand(), srand()
#include <time.h>       //  time()

typedef struct match_info{
    int perfect;
    int incorrect;
} match_data;

typedef struct game_data{
    int* user_attempts;
    char* user_code;
} mastermind_data;

#endif