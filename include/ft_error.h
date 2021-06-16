/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendrul <wendrul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:53:14 by wendrul           #+#    #+#             */
/*   Updated: 2021/06/16 12:12:32 by wendrul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define DEFAULT_ERROR 1
# define FATAL_ERROR 2

int error_exit(char *msg, int exit_code);

#endif