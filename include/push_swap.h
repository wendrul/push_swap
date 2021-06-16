/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:19:55 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 13:14:09 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "stack.h"
# include "ft_error.h"


/**
 * Use for debuging
**/
# define VERBOSE_PUSH_SWAP
# define ARG_NOT_NUMBER "argument is not a number"
# define ARG_DUPLICATE "argument is duplicate"


int			puswa_error(char *msg);
int			is_number(char *nbr_str);
int			is_already_in_stack(int nb, t_stack s);

t_stack		parse_stack(int argc, char **argv);

#endif