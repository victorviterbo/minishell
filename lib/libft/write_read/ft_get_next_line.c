/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:48:53 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_get_next_line(int fd);
static char	*agglutinate(int fd, char *g_lst_files, char *line);
char		*ft_strjoin_gnl(char const *s1, char const *s2, int in_place);

char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	g_lst_files[FD_MAX][(BUFFER_SIZE + 1)];
	char		*current;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_MAX <= fd)
		return (NULL);
	current = g_lst_files[fd];
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strjoin_gnl(line, current, 1);
	if (!line)
		return (NULL);
	if (!ft_strchr(line, '\n'))
		line = agglutinate(fd, current, line);
	ft_memmove(current, ft_strchr(current, '\n') + 1,
		ft_strlen(ft_strchr(current, '\n')));
	return (line);
}

static char	*agglutinate(int fd, char *current, char *line)
{
	size_t	bytes_read;

	while (ft_strchr(line, '\n') == NULL)
	{
		bytes_read = read(fd, current, BUFFER_SIZE);
		if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
			ft_bzero(current, BUFFER_SIZE + 1);
		if (bytes_read == 0 && *line)
			return (line);
		else if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (NULL);
		}
		*(current + bytes_read) = '\0';
		line = ft_strjoin_gnl(line, current, 1);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, int in_place)
{
	char	*joined;
	size_t	s2len;

	if (ft_strchr(s2, '\n'))
		s2len = (size_t)(ft_strchr(s2, '\n') - s2) + 1;
	else
		s2len = ft_strlen(s2);
	joined = ft_calloc(ft_strlen(s1) + s2len + 1, sizeof(char));
	if (!joined && in_place)
	{
		free((void *)s1);
		return (NULL);
	}
	ft_memmove(joined, s1, ft_strlen(s1));
	ft_memmove(joined + ft_strlen(s1), s2, s2len);
	*(joined + ft_strlen(s1) + s2len) = '\0';
	if (in_place)
		free((void *)s1);
	return (joined);
}
