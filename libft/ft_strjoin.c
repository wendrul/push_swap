/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 19:16:06 by ede-thom          #+#    #+#             */
/*   Updated: 2021/06/22 10:08:30 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	char	*start;

	ret = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	start = ret;
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = '\0';
	return (start);
}
