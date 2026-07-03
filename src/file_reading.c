#include "header.h"

/* there's no way there is more than 65535 words (can be changed to 32bit */
uint16_t get_num_lines(char *file_path)
{
	if (verbose)
	{
		printf("reading the number of words in : %s\n", file_path);
	}

	/* open file path in reading mode */
	FILE *word_file = fopen(file_path, "r");

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

char (*read_words(char *file_path, uint32_t *num_words))[6]
{
	if (verbose)
	{
		printf("reading the word list at : %s\n", file_path);
	}

	/* allocate memory for all words
	 * multiply the size of 1 word by the number of words to get the total size */
	size_t file_buffer_size = (*num_words * sizeof(char[7]));	/* for reading from the file directly */
	char (*file_buf)[7] = malloc(file_buffer_size);

	size_t word_list_size = (*num_words * sizeof(char[7]));
	char (*ptr)[INDEX_LETTERS_WORD] = malloc(word_list_size);

	if (ptr == NULL)
	{
		err(MALLOC_ERR);
	}

	FILE *file = fopen(file_path, "r");

	if (file == NULL)
	{
		err(NO_SUCH_FILE);
	}
	
	for (uint16_t i = 0; i < *num_words; i++) 
	{
		if (fgets(file_buf[i], 7, file) == NULL) 
		{
			break;
		}

		file_buf[i][INDEX_LETTERS_WORD] = '\0';
		file_buf[i][NUM_LETTERS_WORD] = '\0';

		strncpy(ptr[i], file_buf[i], 6);
	}
	free(file_buf);
	
	fclose(file);	/* close file after use */

	/* the memory needs to be freed later after use */
	return ptr;
}
