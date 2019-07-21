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
    int i;
    for (i = 0; s[i]; i++)
    {
        char c = (char)s[i];
        sprintf(buffer + 8 + i*4, "\\x%x", c);
    }

    char bufferf[1024];
    sprintf(bufferf, "%s' | dd of='%s' bs=1 seek=$((0x%x)) count=%d conv=notrunc\n", buffer, av[1], byte_pos, i);
    printf("%s\n", bufferf);

    system(bufferf);
    return 0;
}
