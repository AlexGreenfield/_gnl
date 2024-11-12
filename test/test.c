
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*string;
	int		i;

// Test 1 Loreipsum one jump
	printf("\n------Loreipsum with only one new line------\n\n");
	i = 0;
	fd = open("loreipsum_one_jump.txt", O_RDONLY);
	while (i < 6)
	{
		string = get_next_line(fd);
		printf("%s", string);
		free (string);
		i++;
	}
	free (string);
// Test 1 Loreipsum two jumps
	printf("\n\n------Loreipsum with two new lines------\n\n");
	i = 0;
	fd = open("loreipsum_two_jumps.txt", O_RDONLY);
	while (i < 10)
	{
		string = get_next_line(fd);
		printf("%s", string);
		free (string);
		i++;
	}
	free (string);
// Test 2 Mistborn
	fd = open("mistborn.txt", O_RDONLY);
	i = 0;
	printf("\n\n------First chapter of the best book ever writen by man-----\n\n");
	while (i < 185)
	{
		string = get_next_line(fd);
		printf("%s", string);
		free (string);
		i++;
	}
	free (string);
// Test 3 Mistborn one line
	fd = open("mistborn_no_jumps.txt", O_RDONLY);
	printf("\n\n------First chapter of the best book ever writen by man but I read fast------\n\n");
	string = get_next_line(fd);
	printf("%s", string);
	free (string);

	return (0);
}
