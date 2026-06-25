#include "header.h"

uint16_t get_num_lines(char *file_path)
{
	/* open file path in reading mode */
	FILE *word_file = fopen(file_path, "r");

	uint16_t line_count = 0; /* max size of 65535 (65535 lines) */
	char char_read = '\0';
	for (char_read = (char)fgetc(word_file); char_read != EOF; char_read = (char)fgetc(word_file))
	{
		if (char_read == '\n')
		{
			line_count++;
		}
	}
	
	fclose(word_file);	/* close file */
	printf("The file %s has %d lines\n ", file_path, line_count);
	
	return line_count;
}
