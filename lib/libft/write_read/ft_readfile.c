/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:07:17 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readfile(int fd);

char	*ft_readfile(int fd)
{
	int		byte_read;
	char	*buffer;
	char	*fcontent;

	if (fd <= 0)
		return (NULL);
	byte_read = BUFFER_SIZE;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	fcontent = ft_calloc(1, sizeof(char));
	while (byte_read == BUFFER_SIZE)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		fcontent = ft_strjoin_ip(fcontent, buffer, 1);
	}
	free(buffer);
	return (fcontent);
}
