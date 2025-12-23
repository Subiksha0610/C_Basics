#include <stdio.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main() {
    char c = 'C';
    printf("%c\n", lower(c));
    return 0;
}
