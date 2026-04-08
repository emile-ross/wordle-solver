#include "header.h"

int main(int argc, char *argv[])
{
    test(argc);
    return 0;
}

void test(int num_arg)
{
    printf("You entered %d command line argument", num_arg);
    if (num_arg >= 2)
    {
	printf("s");
    }

    printf("\n");
}
