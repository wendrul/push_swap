/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puswa_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:47:10 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/29 14:48:36 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int puswa_error(char *msg)
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

int is_number(char *nbr_str)
{
	int nb;
	char *test_nb;
	int ans;

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

char *join_delete(char *str1, char *str2)
{
	char *ret;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	ret = ft_strjoin(str1, str2);
	if (!ret)
		error_exit(MALLOC_FAIL_ERROR, FATAL_ERROR);
	free(str1);
	free(str2);
	str1 = NULL;
	str2 = NULL;
	return (ret);
}

char *exec_and_str_op(t_stack a, t_stack b, char *op, char *ans)
{
	char buf[20];
	int i;

	current_ops++;
	i = -1;
	while (op[++i])
		buf[i] = op[i];
	buf[i] = '\n';
	buf[i + 1] = '\0';
	execute_op(a, b, op);

	// fprintf(stderr, "%s:\n", op);
	// fprintf(stderr, "    a:\n");
	// print_stack(a);
	// fprintf(stderr, "    b:\n");
	// print_stack(b);

	return (join_delete(ans, ft_strdup(buf)));
}

int get_index(int *arr, int size, int element)
{
	int i;
	int amount_smaller;

	i = -1;
	amount_smaller = 0;
	while (++i < size)
	{
		if (arr[i] < element)
			amount_smaller++;
	}
	return (amount_smaller);
}

t_stack indexify_stack(t_stack s)
{
	t_stack idx;
	int i;

	idx = s->copy(s);
	i = -1;
	while (++i < s->size(s))
	{
		idx->items[i] = get_index(s->items, s->size(s), s->items[i]) + 1;
	}
	return (idx);
}


