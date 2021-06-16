/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puswa_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:47:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 13:25:46 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	puswa_error(char *msg)
{
	ft_putendl_fd("Error", STDIN_FILENO);
	#ifdef VERBOSE_PUSH_SWAP
	ft_putendl_fd(msg, STDIN_FILENO);
	#endif
	exit(0);
}

int	is_number(char *nbr_str)
{
	int		nb;
	char	*test_nb;
	int		ans;

	nb = ft_atoi(nbr_str);
	test_nb = ft_itoa(nb);
	if (test_nb == NULL)
		error_exit(ITOA_MALLOC_FAIL, FATAL_ERROR);
	ans = 1;
	nb = ft_max(ft_strlen(nbr_str), ft_strlen(test_nb));
	printf("them -%s- vs me -%s-\n", nbr_str, test_nb);
	if (ft_strncmp(nbr_str, test_nb, nb) != 0)
		if (nbr_str[0] != '+' || ft_strncmp(nbr_str + 1, test_nb, nb - 1) != 0)
			ans = 0;
	free(test_nb);
	return (ans);
	
}

int	is_already_in_stack(int nb, t_stack s)
{
	int	i;

	i = s->top;
	while (i >= 0)
	{
		if (nb == s->items[i])
			return (1);
		i--;
	}
	return (0);
}