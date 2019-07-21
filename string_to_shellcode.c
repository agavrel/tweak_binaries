#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (ac != 4)
    {
        printf("usage: ./a.out binary_filename address string");
        return 1;
    }

    char *s = av[3];
    char buffer[1024];
    char filename[1024];
    unsigned int byte_pos = (int)strtol(av[2], NULL, 16);
    sprintf(buffer, "printf '");
    strcpy(filename, av[1]);
    printf("mybin='%s' && \n", filename);
    int i;
    for (i = 0; s[i]; i++)
    {
        char c = (char)s[i];
        sprintf(buffer + 8 + i*4, "\\x%x", c);
    }

    printf("%s' | dd of=$mybin bs=1 seek=$((0x%x)) count=%d conv=notrunc\n", buffer, byte_pos, i);
    return 0;
}
