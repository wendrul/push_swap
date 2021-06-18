/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 15:09:41 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void add_instruction(char instructions[], char **operations, int op_nu)
{
	int i;
	int j;

	i = -1;
	while (operations[op_nu][++i])
	{

	instructions[ft_strlen(instructions)]
	}
}

void replace_instruction(char instructions[])
{

}

char *brute_swap(t_stack a, t_stack b, char instructions[], char **operations, int depth)
{
	if (depth > a->maxsize * 2 + 2)
		return (NULL);
	if (is_sorted_inc(a))
		return (instructions);
	add_instruction(instructions);
	while (brute_swap() == NULL)
	{

	}
}

void	push_swap(t_stack a, t_stack b)
{
	if (a->maxsize <= 5)
		brute_swap(a, b);
	else
	{

	}
}

int	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	a = parse_stack(argc, argv);
	b = new_stack(a->maxsize);
	push_swap(a, b);
	delete_stack(&b);
	delete_stack(&a);
	return (0);
}