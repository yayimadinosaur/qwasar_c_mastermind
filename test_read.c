#include <stdio.h>
#include <unistd.h>
#include <string.h>

int my_strlen(char* s1) {
    int i = 0;
    while (s1[i] != '\0')
        i += 1;
    return i;
}

int main(int ac, char **av){
    printf("ac = %i\n", ac);
    char test[6];
    int x;
    if (ac == 1) {
        while (x != 1) {
            x = read(0, test, sizeof(test));
            printf("x[%d]\n", x);
            if (my_strlen(test) > 5 || x == 1) {
                return - 1;
            }
            printf("[%s]\n", test);
            printf("test len [%lu]\n", strlen(test));
        }
        printf("x fin [%i]", x);
    }
    return 0;
}