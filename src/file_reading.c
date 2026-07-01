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
	
	fclose(word_file);	/* close file */

	return line_count;
}

char (*read_words(char **file_path, uint16_t *num_words))[INDEX_LETTERS_WORD]
{

	/* allocate memory for all words
	 * multiply the size of 1 word by the number of words to get the total size */
	size_t word_list_size = (*num_words * sizeof(char[INDEX_LETTERS_WORD]));
	char (*ptr)[INDEX_LETTERS_WORD] = malloc(word_list_size);

	FILE *file = fopen(*file_path, "r");
	
	for (uint16_t i = 0; i < *num_words; i++) 
	{
		if (fgets(ptr[i], INDEX_LETTERS_WORD, file) == NULL) 
		{
			break;
		}

		size_t len = strlen(ptr[i]);
		if (len > 0 && ptr[i][len - 1] == '\n') 
		{
			ptr[i][len - 1] = '\0';
		}
	}
	
	fclose(file);	/* close file after use */

	/* the memory needs to be freed later after use */
	return ptr;
}
