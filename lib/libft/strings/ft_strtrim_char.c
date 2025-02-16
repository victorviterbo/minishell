/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:22:58 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_char(char	*str, char c, bool inplace);

char	*ft_strtrim_char(char	*str, char c, bool inplace)
{
	char	*cstr;
	char	*trimmed;

	cstr = ft_ctoa(c);
	trimmed = ft_strtrim(str, cstr);
	free(cstr);
	if (inplace)
		free(str);
	return (trimmed);
}
