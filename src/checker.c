#include "push_swap.h"
#include "get_next_line.h"

int	checker(t_stack a, t_stack b)
{
	int		ret;
	char	*line;

	ret = get_next_line(STDIN_FILENO, &line);
	while (ret)
	{
		if (ret == -1)
			error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
		if (!execute_op(a, b, line))
			puswa_error(INVALID_OP);
		free(line);
		ret = get_next_line(STDIN_FILENO, &line);
	}
	return (is_sorted_inc(a) && b->is_empty(b));
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc == 1)
		return (0);
	a = parse_stack(argc, argv);
	b = new_stack(a->maxsize);
	if (checker(a, b))
		ft_putendl_fd("OK", STDOUT_FILENO);
	else
		ft_putendl_fd("KO", STDOUT_FILENO);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}
