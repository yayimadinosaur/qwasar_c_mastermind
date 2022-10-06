#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //for atoi rand() srand()
#include <time.h>   //time()

typedef struct hey{
    int perfect;
    int incorrect;
} wtf;

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

// int my_str_compare(char* string1, char* string2){
//     int i = 0;
//     int j = 0;
//     while (string1[i] != '\0' && string2[j] != '\0') {
//         if (string1[i] != string2[j])
//             //  characters don't match
//             return -1;
//         i += 1;
//         j += 1;
//     }
//     if (i != j)
//         //  string length doesn't match
//         return -2;
//     return 0;
// }

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
        printf("code val [%c] fails\n", c);
        return -1;
    }
    return 0;
}

int match_codes(char* code, char* guess, wtf* omg){
    int matches = 0;
    int seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 4; i += 1){
        if (guess[i] == code[i]){
            matches += 1;
        }
        //  add to seen array of ints
        else {
            int tmp = code[i] - '0';
            seen[tmp] = seen[tmp] + 1;
        }
    }
    // printf("total matches [%i]\n", matches);
    omg->perfect = matches;
    for (int j = 0; j < 4; j += 1){
        //  already matched
        int converted = guess[j] - '0';
        if (seen[converted] > 0){
            omg->incorrect += 1;
            seen[converted] -= 1;
        }   
    }
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

// char* str_cpy(char* dst, const char* src)
// {
// 	int i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	if (src[i] == '\0')
// 		dst[i] = '\0';
// 	return dst;
// }

int main(int ac, char** av){
    if (ac == 1){
        char* match = generate_4_random_numbers();
        printf("gen 4 ran [%s]\n", match);
        char guess[] = "abcd";
        int index = 0;
        char tmp;
        //  reset to 10 after testing
        int attempts = 3;
        int round = 0;

        wtf pew;
        while (attempts > 0) {
            printf("round %i\n", round);
            while (read(0, &tmp, 1) > 0){
                // printf("tmp [%s]\n", &tmp);
                if (tmp == '\n'){
                    //  incorrect user input
                    if (index != 4){
                        index = 0;
                        mem_set(guess, 0, 4);
                        printf("wrong input! [len]\n");
                        continue;
                    }
                    break;
                }
                //  not valid char
                if (check_code_value(tmp) != 0){
                    //  manually fail user input
                    printf("wrong input! [char]\n");
                    index = 5;
                    continue;
                }
                //  valid char, add to guess
                if (index < 4)
                    guess[index] = tmp;
                index += 1;
            }
            printf("guess [%s]\n", guess);
            pew.incorrect = 0;
            pew.perfect = 0;
            //  check match
            if (match_codes(match, guess, &pew) == 4){
                printf("winner winner chicken dinner! 4 matches!\n");
                index = 0;
                mem_set(guess, 0, 4);
                return 1;
            }
            else {
                printf("perf match [%i]\nincorrect match[%i]\n", pew.perfect, pew.incorrect);
                index = 0;
                mem_set(guess, 0, 4);
            }
            round += 1;
            attempts -= 1;
        }
        if (attempts == 0){
            printf("ran out of attempts\nGAME OVER!");
            return -1;
        }
    }
    return 0;
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