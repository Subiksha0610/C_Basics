#include <stdio.h>
#include <ctype.h>

int isupper_space(int c) {
    if (c == EOF)
        return 0;
    if (c < 0 || c > 255)
        return 0;
    return (c >= 'A' && c <= 'Z');
}

static unsigned char upper_table[256] = {0};

void init_upper_table(void) {
    for (int i = 'A'; i <= 'Z'; i++) {
        upper_table[i] = 1;
    }
}

int isupper_time(int c) {
    if (c == EOF)
        return 0;
    if (c < 0 || c > 255)
        return 0;
    return upper_table[(unsigned char)c];
}

int main(void) {
    init_upper_table();

    int test_chars[] = {'A', 'z', 'M', '9', 'b', EOF, -10, 200};
    int n = sizeof(test_chars) / sizeof(test_chars[0]);

    printf("Testing characters:\n");
    for (int i = 0; i < n; i++) {
        int c = test_chars[i];
        printf("Char: %d\n", c);
        printf("  isupper_space: %d\n", isupper_space(c));
        printf("  isupper_time : %d\n", isupper_time(c));
        printf("  ctype isupper: %d\n", isupper(c));
    }

    return 0;
}
