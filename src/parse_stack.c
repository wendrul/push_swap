/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:39:42 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/30 18:47:44 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	parse_stack(int argc, char **argv)
{
	t_stack	a;
	int		nb;
	int		i;

	i = argc;
	a = new_stack(argc - 1);
	while (--i > 0)
	{
		if (!is_number(argv[i]))
			puswa_error(ARG_NOT_NUMBER);
		nb = ft_atoi(argv[i]);
		if (is_already_in_stack(nb, a))
			puswa_error(ARG_DUPLICATE);
		a->push(a, nb);
	}
	return (a);
}
