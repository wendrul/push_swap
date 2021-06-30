/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 18:56:09 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/30 19:00:17 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ft_error.h"
#include <stdio.h>

int	size(t_stack self)
{
	return (self->top + 1);
}

int	is_empty(t_stack self)
{
	return (self->top == -1);
}

int	is_full(t_stack self)
{
	return (self->top == self->maxsize - 1);
}

void	push(t_stack self, int val)
{
	if (is_full(self))
		error_exit(ERR_FULL_STACK_PUSH, DEFAULT_ERROR);
	self->items[++self->top] = val;
}

int	peek(t_stack self)
{
	if (!is_empty(self))
		return (self->items[self->top]);
	return (error_exit(ERR_EMPTY_STACK_PEEK, DEFAULT_ERROR));
}
