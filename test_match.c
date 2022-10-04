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

int check_code_values(char* s1){
    for (int i = 0; i < 4; i += 1){
        if (!(s1[i] - '0' >= 0 && s1[i] - '0' <= 8)){
            printf("index [%i] fails\n", i);
            return -1;
        }
    }
    return 0;
}

int match_codes(char* code, char* guess, wtf* omg){
    // printf("start match ocdes\n");
    int matches = 0;
    int seen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    // printf("1st loop\n");
    for (int i = 0; i < 4; i += 1){
        if (guess[i] == code[i]){
            matches += 1;
            // printf("match found! index[%i] guess [%i] code [%i]\n", i, guess[i] - '0', code[i] - '0');
            //  -1 = matches
            // code[i] = -1;
            // guess[i] = -1;
        }
        //  add to seen array of ints
        else {
            // printf("atoi 1 fail\n");
            int tmp = code[i] - '0';
            // printf("test [%i]\n", tmp);
            seen[tmp] = seen[tmp] + 1;
            // printf("code[%i] val[%i] seen val [%i]\n", i, tmp, seen[tmp]);
            // printf("atoi1 pass?\n");
        }
    }
    // printf("total matches [%i]\n", matches);
    omg->perfect = matches;
    // printf("omg.perf matches[%i]\n", omg->perfect);
    //  print array of ints
    // printf("[");
    // for (int i = 0; i < 9; i += 1) {
    //     printf("%i", seen[i]);
    //     if (i != 8)
    //         printf(", ");
    // }
    // printf("]\n");
    //  check array of ints for seen nums
    // printf("2nd loop\n");
    for (int j = 0; j < 4; j += 1){
        //  already matched
        int converted = guess[j] - '0';
        // printf("guess idx[%i] val[%i]\n", j, converted);
        // printf("start seen atoi2 val [%i]\n", seen[guess[j] - '0']);
        // printf("seen[%i] val [%i]\n", converted, seen[converted]);
        if (seen[converted] > 0){
            // printf("omg inc fail\n");
            omg->incorrect += 1;
            // printf("omg incorrect [%i]\n", omg->incorrect);
            // printf("seen ref start\n");
            seen[converted] -= 1;
            // printf("seen ref fail?\n");
        }   
    }
    // printf("total incorrect[%i]\n", omg->incorrect);
    return matches;   
}

char* str_n_duplicate(char *s1, int length){
    printf("passed in [%s]\n", s1);
    int i = 0;
    // int length = str_length(s1);
    printf("pew\n");
    // printf("length pass [%i]", length);
    char *tmp;
    tmp = (char*)malloc((length) * sizeof(char));
    tmp[length] = '\0';
    // printf("malloc passed %i", tmp != NULL);
    printf("hmm");
    while (length > 0) {
        tmp[i] = s1[i];
        i += 1;
        length -= 1;
    }
    printf("str_dup pass\n");
    return tmp;
}

char* str_join(char* s1, char* s2){
    char	*buff;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	if (!(buff = (char*)malloc(sizeof(char) * (str_length(s1) +
						str_length(s2) + 1))))
		return (NULL);
    //head
	result = buff;
	while (*s1)
		*buff++ = *s1++;
	while (*s2)
		*buff++ = *s2++;
	*buff = '\0';
    printf("result [%s]\n", result);
	return (result);
}

int main(int ac, char** av){
    if (ac == 1){
        char* match = generate_4_random_numbers();
        printf("gen 4 ran [%s]\n", match);
        char* guess;
        char* hold;
        char tmp;
        int x;
        //  reset to 10 after testing
        int attempts = 3;
        int round = 0;

        wtf pew;
        while (attempts > 0) {
            printf("round %i\n", round);
            // x = read(0, guess, sizeof(guess));
            while (read(0, &tmp, 1) > 0){
                if (tmp == '\n')
                {
                    printf("end of stdin\n");
                    break;
                }
                //  guess does not exist
                if (!guess){
                    hold = str_n_duplicate(&tmp, 1);
                    printf("guess now exists [%s]\n", hold);
                    printf("guess length [%i]\n\n", str_length(hold));
                    continue;
                }
                //  guess exists
                else {
                    printf("guess exists\n");
                    guess = str_join(hold, &tmp);
                    printf("guess extended [%s]\n", guess);
                    printf("guess length [%i]\n\n", str_length(guess));
                }
                if (str_length(hold) == 4){
                    guess = hold;
                    free(hold);
                }
            }
            printf("length is [%i]\n", str_length(guess));
            if (x != 5){
                printf("wrong input! [x]\n");
                continue;
            }
            guess[4] = '\0';
            if (str_length(guess) != 4){
                printf("wrong input! [len]\n");
                continue;
            }
            // tmp = str_n_duplicate(guess, 5);
            // free(guess);
            printf("guess [%s]\n", guess);
            // printf("tmp [%s]\n", tmp);
            // x = read(0, guess, 1);
                //handle EOF / ctrl D
            // if (x == 0){
            //     printf("ctrl d\n");
            //     exit(0);
            //     }
            printf("x is [%i]\n", x);
            
            printf("guess[%s]\n", guess);
            //  guess parse pass
            if (check_code_values(guess) == 0){
                //  set default values for incorrect + perfect
                pew.incorrect = 0;
                pew.perfect = 0;
                printf("rand4 [%s]\nguess [%s]\n", match, guess);
                //  check match
                if (match_codes(match, guess, &pew) == 4){
                    printf("winner winner chicken dinner! 4 matches!\n");
                    return 1;
                }
                printf("perf match [%i]\nincorrect match[%i]\n", pew.perfect, pew.incorrect);
            }
            else {
                printf("match fail\n");
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