/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:14:56 by ede-thom          #+#    #+#             */
/*   Updated: 2021/07/01 13:08:13 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_aux(t_buf_hist hist, char **line, int fd, char **last_buf)
{
	*last_buf = get_last_from_fd(fd, &hist);
	if (!*last_buf)
		return (-1);
	*line = (char *)malloc(sizeof(char));
	if (!(*line))
		return (-1);
	(*line)[0] = '\0';
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char				buf[BUFFER_SIZE + 1];
	static t_buf_hist	hist = NULL;
	char				*last_buf;
	int					bytes_read;
	int					error_no;

	if (gnl_aux(hist, line, fd, &last_buf) == -1)
		return (-1);
	if (ft_strjoin_endl(line, last_buf, &error_no))
		return (error_no);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read)
	{
		if (bytes_read == -1)
			return (GNL_READ_ERROR);
		buf[bytes_read] = '\0';
		gnl_memmove(last_buf, buf, BUFFER_SIZE + 1);
		if (ft_strjoin_endl(line, last_buf, &error_no))
			return (error_no);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	hist = remove_fd_from_hist(fd, hist);
	return (GNL_EOF_RETURN);
}

char	*joinem(char *s1, char *s2, int s1_len, int s2_len)
{
	char	*new;

	new = (char *)malloc(sizeof(*new) * (1 + s1_len + s2_len));
	if (!new)
		return (NULL);
	gnl_memmove(new, s1, s1_len);
	gnl_memmove(new + s1_len, s2, s2_len);
	new[s1_len + s2_len] = '\0';
	return (new);
}

static int	endl_aux(char *s1, char *s2, char **line, int *line_len)
{
	int	s2_len;

	s1 = *line;
	s2_len = 0;
	*line_len = 0;
	while (s1[*line_len])
		(*line_len)++;
	while (s2[s2_len] && s2[s2_len] != '\n')
		s2_len++;
	return (s2_len);
}

int	ft_strjoin_endl(char **line, char *s2, int *error_no)
{
	int		s2_len;
	int		line_len;
	char	*s1;
	char	*new;

	s1 = NULL;
	s2_len = endl_aux(s1, s2, line, &line_len);
	new = joinem(s1, s2, line_len, s2_len);
	if (!new)
	{
		*error_no = GNL_MALLOC_ERROR;
		return (1);
	}
	free(s1);
	*line = new;
	if (s2[s2_len] == '\n')
	{
		*error_no = GNL_NORMAL_RETURN;
		gnl_memmove(s2, s2 + s2_len + 1, BUFFER_SIZE + 2 - s2_len);
		return (1);
	}
	s2[0] = '\0';
	return (0);
}
