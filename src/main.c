#include "header.h"

int main(int argc, char *argv[])
{
    parse_command(argc, argv);
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

void parse_command(int num_arg, char *argument[])
{
    if (num_arg < 2)
    {
	printf("You haven't used any argments in your command");
	exit(1);
    }
    for (int i = 0; i < num_arg; i++)
    {
	printf("%s\n", argument[i]);
    }

    // set the amount of filtered words but inclusively
    int inc_filtered_num = NUM_WORDS;

    for (int i = 0; i < NUM_WORDS; i++)
    {
	if ('Z' == words[i][0])
	{
	    printf("True for %d\n", i);
	}
    }

    //for (int i = 0; i < 
}

