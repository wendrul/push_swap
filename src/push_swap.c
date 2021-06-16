/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:21:45 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 13:35:43 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack a, t_stack b)
{
	print_stack(a);
	printf("inc sorted: %i dec sorted :%i", is_sorted_inc(a), is_sorted_dec(a));
	(void)b;
}

int	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	a = parse_stack(argc, argv);
	b = new_stack(a->maxsize);
	push_swap(a, b);
	return (0);
}