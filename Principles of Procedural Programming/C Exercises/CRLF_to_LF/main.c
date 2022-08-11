#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *fich;
    FILE *fich2;
    char c;
    fich = fopen(argv[2], "r");
    fich2 = fopen(argv[3], "w");
    if (argv[1] == "-i") {
        while ((c = getc(fich)) != EOF) {
            if (c == '\r') {
                putc('\n', fich2);
                c = getc(fich);
                if (c == EOF) break;
                if (c == '\n') continue;
            }
            putc(c, fich2);
        }
    } else if (argv[1] == "-c") {
        while ((c = getc(fich)) != EOF) {
            if (c == '\n') {
                putc('\r', fich2);
                putc('\n', fich2);
                c = getc(fich);
                if (c == EOF) break;
                if (c == '\n') continue;
            }
            putc(c, fich2);
        }
    }
    fclose(fich);
    fclose(fich2);
    return 0;
}
