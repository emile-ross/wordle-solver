#include "header.h"

/* there's no way there is more than 65535 words (can be changed to 32bit */
uint16_t get_num_lines(char **file_path)
{
	/* open file path in reading mode */
	FILE *word_file = fopen(*file_path, "r");

	uint16_t line_count = 0; /* max size of 65535 (65535 lines) */

	/* checks if the file can be opened and if it exists */
	if (word_file == NULL)
	{
		err(NO_SUCH_FILE);
	}

	char char_read = '\0';
	for (char_read = (char)fgetc(word_file); char_read != EOF; char_read = (char)fgetc(word_file))
	{
		if (char_read == '\n')    
		{
			line_count++;
		}
	}

	/* count the last line even though it might end in EOF instead of \n */
	if (line_count > 0 || fgetc(word_file) != EOF)
	{
		line_count++;
	}

	fclose(word_file);	/* close file */

	return line_count;
}

char (*read_words(char **file_path, uint16_t *num_words))[7]
{

	/* allocate memory for all words
	 * multiply the size of 1 word by the number of words to get the total size */
	size_t word_list_size = (*num_words * sizeof(char[7]));
	char (*ptr)[7] = malloc(word_list_size);

	FILE *file = fopen(*file_path, "r");
	
	for (uint16_t i = 0; i < *num_words; i++) 
	{
		if (fgets(ptr[i], 7, file) == NULL) 
		{
			break;
		}

		/* replace last character (before NULL terminator) when it's a newline */
		size_t len = strlen(ptr[i]);
		if (len > 0 && ptr[i][len - 1] == '\n') 
		{
			ptr[i][len - 1] = '\0';
		}
		if (len > 0 && ptr[i][len - 1] == '\r')
		{
			ptr[i][len - 1] = '\0';
		}

	}
	
	fclose(file);	/* close file after use */

	/* the memory needs to be freed later after use */
	return ptr;
}

