#include <stdio.h>
#include <unistd.h>

int str_length(char *s1){
    int i = 0;
    printf("length start\n");
    while (s1[i] != '\0')
        {
            printf("index[%i] [%i]\n", i, s1[i]);
        i += 1;
        }
    printf("length end [%i]\n", i);
    return i;
}

void test1(char* s1){
    // printf("[%s]\n",s1);
    int i = 0;
    while (s1[i] != '\0') {
        // printf("%c", s1[i]);
        i += 1;
    }
    // printf("\nend[%c] val[%i]", s1[i], s1[i]);
}

int main(void) {
    char test[] = "abcd";
    str_length(test);
    test1(test);
    printf("test start [%s]", test);
    int x = read(0, test, 5);
    test[4] = '\0';
    printf("read [%i] bytes\n", x);
    printf("test buff [%s]", test);
}