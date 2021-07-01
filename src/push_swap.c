/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/07/01 11:23:36 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	choose_algo(t_sort_algo *sort_list, t_stack a, t_stack b, char *ans)
{
	int		i;
	char	*ans2;

	i = -1;
	while (sort_list[++i])
	{
		ans2 = sort_list[i](a->copy(a), b->copy(b));
		if (!ans || count_char(ans, '\n') > count_char(ans2, '\n'))
		{
			free(ans);
			ans = ans2;
		}
		else
			free(ans2);
	}
	ft_putstr_fd(ans, STDOUT_FILENO);
}

void	push_swap(t_stack a, t_stack b)
{
	char		*ans;
	t_sort_algo	sort_algo_list[AMOUNT_OF_SORTS + 1];

	sort_algo_list[0] = insert_sort2;
	sort_algo_list[1] = insert_sort1;
	sort_algo_list[2] = bubble_sort;
	sort_algo_list[3] = NULL;
	ans = NULL;
	if (a->size(a) > 5)
		sort_algo_list[1] = NULL;
	else
		ans = brute_swap2(a, b);
	if (ans)
		ft_putstr_fd(ans, STDOUT_FILENO);
	else
		choose_algo(sort_algo_list, a, b, ans);
	free(ans);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	a = parse_stack(argc, argv);
	b = indexify_stack(a);
	delete_stack(&a);
	a = b;
	b = new_stack(a->maxsize);
	push_swap(a, b);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}
