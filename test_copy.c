#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //for atoi rand() srand()
#include <time.h>   //time()

typedef struct hey{
    int perfect;
    int incorrect;
} wtf;

typedef struct game_data{
    int user_attempts;
    char* user_code;
} mastermind_data;

void initial_message(void){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
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
    // printf("length start\n");
    while (s1[i] != '\0')
        i += 1; 
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

//  checks chars in string if it's a valid num in range (0-8)
int check_for_nums(char* some_string){
    for (int i = 0; i < str_length(some_string); i += 1){
        //  change char to ascii decimal value
        int val = some_string[i] - 0;
        //  compare to valid decimal values
        if (!(val >= 48 && val <= 56)){
            return -1;
        }
    }
    return 0;
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

//  checks for user input values 0 - 8
    // int check_code_values(char* num_str){
    //     // printf("starting check code val [%s]\n", num_str);
    //     int tmp_remove_after = str_length(num_str);
    //     // printf("strlen pew pewpew[%i]\n", tmp_remove_after);
    //     if (tmp_remove_after != 4) {
    //         // printf("incorrect len [%i]\n", str_length(num_str));
    //         return -3;
    //     }
    //     // printf ("starting custom index val check\n");
    //     int converted;
    //     for (int i = 0; num_str[i] != '\0'; i += 1){
    //         //  char val isn't 0 - 8 in ascii value via decimal
    //         converted = num_str[i] - '0';
    //         // printf("converted index [%i] [%i]\n", i, converted);        
    //         if (!(converted >= 0 && converted < 9))
    //         {
    //             // printf("custom index fail index [%i] val [%c]\n", i, num_str[i]);
    //             return -1;
    //         }
    //     }
    //     // printf("check_code_val fin\n");
    //     return 0;
    // }

// int check_code_values(char* s1){
//     for (int i = 0; i < 4; i += 1){
//         if (!(s1[i] - '0' >= 0 && s1[i] - '0' <= 8)){
//             printf("index [%i] fails\n", i);
//             return -1;
//         }
//     }
//     return 0;
// }

//  checks if char is between 0 - 8
int check_code_value(char c){
    if (!(c - '0' >= 0 && c - '0' <= 8)){
        // printf("code val [%c] fails\n", c);
        return -1;
    }
    return 0;
}

int match_codes(char* code, char* guess, wtf* omg){
    int matches = 0;
    int seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int x = 0; x < 4; x += 1){
        int converted = code[x] - '0';
        seen[converted] += 1;
    }
    // write(1, "[", 1);
    printf("just seen\n");
    for (int y = 0; y < 9; y += 1){
        printf(" %d, ", seen[y]);
    }
    printf("\n");
    // write(1, "]", 1);
    // for (int i = 0; i < 4; i += 1){
    //     if (guess[i] == code[i]){
    //         matches += 1;
    //     }
    //     //  add to seen array of ints
    //     else {
    //         int tmp = code[i] - '0';
    //         seen[tmp] = seen[tmp] + 1;
    //     }
    // }
    // // printf("total matches [%i]\n", matches);
    // omg->perfect = matches;
    // for (int j = 0; j < 4; j += 1){
    //     //  already matched
    //     int converted = guess[j] - '0';
    //     if (seen[converted] > 0){
    //         omg->incorrect += 1;
    //         seen[converted] -= 1;
    //     }   
    // }
    for (int j = 0; j < 4; j += 1){
        //  full match
        int need = guess[j] - '0';
        printf("need [%d]\n", need);
        if (guess[j] == code[j]){
            omg->perfect += 1;
            matches += 1;
            seen[need] -= 1;
        // }
        // //  doesn't match
        // else if (guess[j] != code[j]) {
        //     //  check guess if in seen
        //     if (seen[need] > 0)
        //         printf("check seen val [%d]", seen[need]);
        //         omg->incorrect += 1;
        //         seen[need] -= 1;
        }
    }
    //  look for mismatches
    for (int i = 0; i < 4; i += 1){
        int need = guess[i] - '0';
        printf("need [%d]\n", need);
        if (guess[i] == code[i])
            continue;
        else {
            if (seen[need] > 0) {
                omg->incorrect += 1;
                seen[need] -= 1;
            }
        }
    }
    printf("seen end\n");
    for (int y = 0; y < 9; y += 1){
        printf(" %d, ", seen[y]);
    }
    printf("\n");
    return matches;   
}

// char* str_n_duplicate(char *s1, int length){
//     printf("passed in [%s]\n", s1);
//     int i = 0;
//     // int length = str_length(s1);
//     // printf("pew\n");
//     // printf("length pass [%i]", length);
//     char *tmp;
//     tmp = (char*)malloc((length) * sizeof(char));
//     tmp[length] = '\0';
//     // printf("malloc passed %i", tmp != NULL);
//     while (length > 0) {
//         tmp[i] = s1[i];
//         i += 1;
//         length -= 1;
//     }
//     // printf("str_dup pass\n");
//     return tmp;
// }

// char* str_join(char* s1, char* s2){
//     char	*buff;
// 	char	*result;
//     int total_length;
// 	if (!s1 || !s2)
// 		return (NULL);
//     printf("s1 [%s] s2 [%s]\n", s1, s2);
//     total_length = str_length(s1) + str_length(s2) + 1;
//     printf("str join total len [%d]\n", total_length);
// 	if (!(buff = (char*)malloc(sizeof(char) * (total_length))))
// 		return (NULL);
//     //head
//     buff[total_length] = '\0';
// 	result = buff;
// 	while (*s1)
// 		*buff++ = *s1++;
// 	while (*s2)
// 		*buff++ = *s2++;
// 	*buff = '\0';
//     printf("result [%s]\n", result);
// 	return (result);
// }

void* mem_set(void *s1, int c, int length){
    unsigned char *dst = s1;
    while (length > 0){
        *dst = (unsigned char)c;
        length -= 1;
    }
    return s1;
}

char* str_cpy(char* dst, const char* src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] == '\0')
		dst[i] = '\0';
	return dst;
}

//  checks for -c or -t
int parse_user_flags(char* flag1){
    // printf("flag [%s]", flag1);
    // if (flag1)
    //     return my_str_compare(flag1, "-t") == 0 ? 1 : -1;
    //     // if (my_str_compare(flag1, "-t") != 0)
    //     //     return -1;
    //     // return 1;
    // if (flag2)
    //     return my_str_compare(flag2, "-c") == 0 ? 2 : -2;
    //     // if (my_str_compare(flag2, "-c") != 0)
    //     //     return -2;
    //     // return 2;
    if (my_str_compare(flag1, "-t") == 0)
        return 1;
    else if (my_str_compare(flag1, "-c") == 0)
        return 2;
    return -1;
}

//  checks flag param input for valid values for -c [ 0000 - 8888 ] or -t [ > 0 ]
int parse_user_flag_params(char* user_code, char* user_attempts){
    //  user input code is not a number
    if (user_code)
        //length check
        if (str_length(user_code) != 4)
            return -1;
        if (check_for_nums(user_code) != 0)
            return -2;
    if (user_attempts){
        //  user_attempts is not a number
        if (check_for_nums(user_attempts) != 0)
            return -3;
    }
    //  success
    return 0;
}

// int parse_user_attempts(char* user_attempts){
//     int num_check;
//     if (atoi(user_attempts) == 0)
//         return -1;
// }

int handle_flags(int user_flag, char* av, mastermind_data data){
    printf("handling flags [%d]\n", user_flag);
    //  flag = -t
    if (user_flag == 1){
        printf("flag is 1\n");
        if (parse_user_flag_params(NULL, av) < 0) {
            printf("flag t chk fail\n");
            // invalid_input_message();
            return -2;
        }
        data.user_attempts = atoi(av);
        if (data.user_attempts < 1)
            return -3;
        printf("data user_attempt [%d]", data.user_attempts);
        return 1;
    }
    //  flag = -c
    else if (user_flag == 2){
        printf("flag is 2\n");
        if (parse_user_flag_params(av, NULL) < 0) {
            printf("flag c chk fail\n");
            // invalid_input_message();
            return -4;
        }
        data.user_code = av;
        printf("data usercode [%s]\n", data.user_code);
        return 2;
    }
    //  invalid flag or flag input param
    // printf("invalid flag input user flag[%d]\n", user_flag);
    // // invalid_input_message();
    return -1;
}

char* set_match_value(char* user_code){
    char* match;
    if (!user_code){
        match = generate_4_random_numbers();
        printf("gen 4 ran [%s]\n", match);
    }
    else {
        match = user_code;
        printf("user code = [%s]", match);
    }
    return match;
}

int start_game(int user_attempts, char* user_code){
    //  no user 4 digit code, generate random one
    char* match = set_match_value(user_code);
    //  set to random default value
    char guess[] = "abcd";
    int read_index = 0;
    char tmp;
    //  reset to 10 after testing
    int attempts = user_attempts == 0 ? attempts = 10 : user_attempts;
    printf("attempts [%d]\n", attempts);
    int round = 0;
    int read_bytes;
    wtf pew;
    initial_message();
    while (attempts > 0) {
        round_message(round);
        // printf("round %i\n", round);
        write(1, ">", 1);
        while ((read_bytes = read(0, &tmp, 1)) > 0){
            // printf("tmp [%c]", tmp);
            // if (tmp == 0)
            //     return -2;
            // printf("tmp [%s]\n", &tmp);
            if (tmp == '\n'){
                //  incorrect user input
                if (read_index != 4){
                    read_index = 0;
                    mem_set(guess, 0, 4);
                    // printf("wrong input! [len]\n");
                    invalid_input_message();
                    write(1, ">", 1);
                    continue;
                }
                break;
            }
            //  not valid char
            if (check_code_value(tmp) != 0){
                //  manually fail user input
                // printf("wrong input! [char]\n");
                // invalid_input_message();
                read_index = 5;
                // write(1, ">", 1);
                continue;
            }
            //  valid char, add to guess
            if (read_index < 4)
                guess[read_index] = tmp;
            read_index += 1;
        }
        if (read_bytes == 0)
            return -2;
        printf("guess [%s]\n", guess);
        pew.incorrect = 0;
        pew.perfect = 0;
        //  check match
        if (match_codes(match, guess, &pew) == 4){
            // printf("winner winner chicken dinner! 4 matches!\n");
            win_message();
            read_index = 0;
            mem_set(guess, 0, 4);
            return 0;
        }
        else {
            // printf("perf match [%i]\nincorrect match[%i]\n", pew.perfect, pew.incorrect);
            current_progress(pew.perfect, pew.incorrect);
            read_index = 0;
            mem_set(guess, 0, 4);
        }
        round += 1;
        attempts -= 1;
    }
    // if (attempts == 0){
        printf("ran out of attempts\nGAME OVER!");
        // win_message();
        return -1;
    // }
}

int main(int ac, char** av){
    //  test printing
    printf("ac == [%d]\n", ac);
    for (int i = 0; i < ac; i += 1){
        printf("[%d] [%s]\n", i, av[i]);
    }
    //  end of test printing
    // char* user_code;
    //  default attempts
    mastermind_data data;
    data.user_attempts = 10;
    int user_flag;
    switch(ac){
        case 1:
            data.user_code = NULL;
            break;
        //  all invalid # of args
        case 2:
        case 4:
        default:
            printf("incorrect params [%d]\n", ac);
            return -1;
        case 3:
            //  check for flag value
            user_flag = parse_user_flags(av[1]);
            printf("user flag = [%d]\n", user_flag);
            if (handle_flags(user_flag, av[2], data) < 0){
                invalid_input_message();
                return -2;
            }
            break;
        case 5:
            printf("5 params\n");
            break;
    }
    printf("starting game?\n");
    return start_game(data.user_attempts, data.user_code);
}


// code
// 1 1 1 1
// guess
// 1234
// m x x x

// 1 1 1 1
// 1 2 3 1
// m x x m

// 1 2 2 1
// 2 1 1 2
// seen = {
//     1: 2,
//     2: 2,
//     3 ...,
// }