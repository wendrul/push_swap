#include "push_swap.h"

int	get_last_op(char *instructions, char last_op_buf[])
{
	int	i;
	int	j;

	i = ft_strlen(instructions) - 2;
	if (i < 0)
		return (0);
	while (i > 0 && instructions[i] != '\n')
	{
		i--;
	}
	if (instructions[i] == '\n')
		i++;
	j = 0;
	while (instructions[i] != '\n')
	{
		last_op_buf[j] = instructions[i];
		i++;
		j++;
	}
	last_op_buf[j] = '\0';
	return (1);
}

int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
