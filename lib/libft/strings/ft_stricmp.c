/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:09:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/21 12:04:21 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stricmp(const char *s1, const char *s2);

int	ft_stricmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	return (ft_strnicmp(s1, s2, ft_max(ft_strlen(s1), ft_strlen(s2))));
}
