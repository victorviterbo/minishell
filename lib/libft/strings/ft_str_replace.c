/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:28:17 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str_replace(char *str, char *to_repl, char *repl_w);
static char	*init(char *str, char *to_repl, char *repl_w, size_t *newsize);

char	*ft_str_replace(char *str, char *to_repl, char *repl_w)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	newsize;

	i = 0;
	j = 0;
	newstr = init(str, to_repl, repl_w, &newsize);
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if (ft_strncmp(str + i, to_repl, ft_strlen(to_repl)) == 0
			&& ft_strlen(to_repl))
		{
			ft_strlcpy(newstr + j, repl_w, newsize - j);
			j += ft_strlen(repl_w);
			i += ft_strlen(to_repl);
			continue ;
		}
		newstr[j] = str[i];
		i++;
		j++;
	}
	return (newstr);
}

static char	*init(char *str, char *to_repl, char *repl_w, size_t *newsize)
{
	char	*newstr;

	if (!str || !to_repl || !repl_w)
		return (NULL);
	if (ft_strlen(to_repl))
		*newsize = (ft_strlen(repl_w) - ft_strlen(to_repl))
			* ft_count_strocc(str, to_repl, true) + ft_strlen(str) + 1;
	else
		*newsize = ft_strlen(str) + 1;
	newstr = ft_calloc(*newsize, sizeof(char));
	return (newstr);
}
