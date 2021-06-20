/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puswa_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:47:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/20 11:32:48 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	puswa_error(char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	#ifdef VERBOSE_PUSH_SWAP
	ft_putendl_fd(msg, STDERR_FILENO);
	#endif
	exit(0);
}

int name_cmp(char *s1, char *s2)
{
	return (0 == ft_strncmp(s1, s2, ft_max(ft_strlen(s1), ft_strlen(s2))));
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
	if (ft_strncmp(nbr_str, test_nb, nb) != 0)
		if (nbr_str[0] != '+' || ft_strncmp(nbr_str + 1, test_nb, nb - 1) != 0)
			ans = 0;
	free(test_nb);
	return (ans);
	
}
