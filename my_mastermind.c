#include "my_mastermind.h"

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

//  checks chars in string if it's a valid num in range (0 - n)
//      n can be 1 - 9 (inclusive)
int check_for_nums_n(char* some_string, int n){
    for (int i = 0; i < str_length(some_string); i += 1){
        //  change char to ascii decimal value
        int val = some_string[i] - 0;
        //  compare to valid decimal values
        if (!(val >= 48 && val <= 48 + n)){
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

//  checks if char is between 0 - 8
int check_code_value(char c){
    if (!(c - '0' >= 0 && c - '0' <= 8)){
        return -1;
    }
    return 0;
}

int match_codes(char* code, char* guess, match_data* data){
    int matches = 0;
    int seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int x = 0; x < 4; x += 1){
        int converted = code[x] - '0';
        seen[converted] += 1;
    }
    for (int j = 0; j < 4; j += 1){
        //  full match
        int need = guess[j] - '0';
        if (guess[j] == code[j]){
            data->perfect += 1;
            matches += 1;
            seen[need] -= 1;
        }
    }
    //  look for mismatches
    for (int i = 0; i < 4; i += 1){
        int need = guess[i] - '0';
        if (guess[i] == code[i])
            continue;
        else {
            if (seen[need] > 0) {
                data->incorrect += 1;
                seen[need] -= 1;
            }
        }
    }
    return matches;   
}

//  checks for -c or -t
int parse_user_flags(char* flag1){
    if (my_str_compare(flag1, "-t") == 0)
        return 1;
    else if (my_str_compare(flag1, "-c") == 0)
        return 2;
    return -1;
}

//  checks user attempt param value
int parse_flag_t(char* user_attempts){
    //  number string - character check
    if (check_for_nums_n(user_attempts, 9) < 0)
        return -1;
    return atoi(user_attempts);
}

//  checks user code param value
int parse_flag_c(char* user_code){
//  user input code is not a number
    if (user_code){
        //  length check
        if (str_length(user_code) != 4)
            return -1;
        //  value check
        if (check_for_nums_n(user_code, 8) != 0)
            return -2;
    }
    return 0;
}

int handle_flags(int user_flag, char* av, char** code, mastermind_data data){
    if (user_flag == 1){
        if (parse_flag_t(av) < 0){
            return -2;
        }
        data.user_attempts[0] = atoi(av);
        //  check for non valid values [ < 1 ]
        if (data.user_attempts[0] < 1) {
            return -3;
        }
        return 1;
    }
    //  flag = -c
    else if (user_flag == 2){
        if (parse_flag_c(av) < 0) {
            return -4;
        }
        *code = av;
        return 2;
    }
    //  invalid flag or flag input param
    return -1;
}

char* set_match_value(char* user_code){
    char* match;
    if (!user_code){
        match = generate_4_random_numbers();
    }
    else {
        match = user_code;
    }
    return match;
}

int assign_attempts(int attempt_data){
    if (attempt_data == 0)
        return 10;
    return attempt_data;
}

char* assign_code(char* user_code){
    char* match;
    if (user_code == NULL)
        //  set to random default value
        match = set_match_value(user_code);
    else
        match = user_code;
    return match;
}

int start_game(int user_attempts, char* user_code, mastermind_data data){
    char* match = assign_code(user_code);
    int attempts = assign_attempts(user_attempts);
    char tmp;
    char guess[] = "abcd";
    int read_count = 0;
    int round = 0;
    int read_bytes;
    free(data.user_attempts);
    match_data match_data;
    initial_message();
    while (attempts > 0) {
        round_message(round);
        write(1, ">", 1);
        while ((read_bytes = read(0, &tmp, 1)) > 0){
            if (tmp == '\n'){
                if (read_count != 4){
                    read_count = 0;
                    invalid_input_message();
                    write(1, ">", 1);
                    continue;
                }
                break;
            }
            if (check_code_value(tmp) != 0){
                read_count = 5;
                continue;
            }
            if (read_count < 4)
                guess[read_count] = tmp;
            read_count += 1;
        }
        if (read_bytes == 0){
            printf("exit\n");
            return -2;
        }
        match_data.incorrect = 0;
        match_data.perfect = 0;
        if (match_codes(match, guess, &match_data) == 4){
            win_message();
            return 0;
        }
        else {
            current_progress(match_data.perfect, match_data.incorrect);
            read_count = 0;
        }
        round += 1;
        attempts -= 1;
    }
    //  lose
    printf("ran out of attempts\nGAME OVER!");
    return -1;
}

int main(int ac, char** av){
    mastermind_data data;
    data.user_attempts = malloc(1 * sizeof(int));
    //  default attempts
    data.user_attempts[0] = 10;
    data.user_code = NULL;
    int user_flag;
    int flag_result;
    switch(ac){
        //  nothing to parse/check
        case 1:
            break;
        //  all invalid # of args
        case 2:
        case 4:
        default:
            invalid_input_message();
            free(data.user_attempts);
            return -1;
        //  checks arg 1 + 2 for flag + flag params
        case 3:
            //  check for flag value
            user_flag = parse_user_flags(av[1]);
            if (user_flag < 0) {
                free(data.user_attempts);
                return -2;
            }
            flag_result = handle_flags(user_flag, av[2], &data.user_code, data);
            if (flag_result < 0){
                invalid_input_message();
                free(data.user_attempts);
                return -3;
            }
            break;
        case 5:
            //  checks args 1 + 2, then 3 + 4 for flags + flag params
            for (int i = 0; i < 3; i += 2){
                user_flag = parse_user_flags(av[i + 1]);
                if (user_flag < 0) {
                    free(data.user_attempts);
                    return -4;
                }
                flag_result = handle_flags(user_flag, av[i + 2], &data.user_code, data);
                if (flag_result < 0){
                    invalid_input_message();
                    free(data.user_attempts);
                    return -5;
                }
            }
            break;
    }
    return start_game(data.user_attempts[0], data.user_code, data);
}