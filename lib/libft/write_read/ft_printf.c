/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:01:06 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/14 17:59:06 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf(const char *str, ...);
size_t	print_format(const char **str, va_list argl);
char	*get_radix(char type, va_list argl);
char	*ft_strdup_pf(const char *s1, int null);

int	ft_printf(const char *str, ...)
{
	size_t	printed;
	int		tmp;
	va_list	argl;

	if (!str)
		return (0);
	printed = 0;
	va_start(argl, str);
	while (*(str))
	{
		if (*(str) != '%')
		{
			if (write(1, str++, 1) != -1)
				printed++;
			else
				return (va_end(argl), -1);
			continue ;
		}
		tmp = print_format(&str, argl);
		if (tmp == -1)
			return (va_end(argl), -1);
		printed += tmp;
	}
	va_end(argl);
	return (printed);
}

size_t	print_format(const char **str, va_list argl)
{
	char	*formated;
	long	printed;
	size_t	i;
	char	*substr;

	printed = 0;
	if (!*str)
		return (-1);
	i = 1;
	while (*(*str + i) && !ft_strchr("cspdiuxX%", *(*str + i)))
		i++;
	substr = ft_substr(*str, 0, i + 1);
	if (!substr)
		return (-1);
	formated = get_radix(*(substr + ft_strlen(substr) - 1), argl);
	if (!formated)
		return (free(substr), -1);
	if (ft_strlen(formated))
		printed = write(1, formated, ft_strlen(formated));
	else if (*(substr + ft_strlen(substr) - 1) == 'c')
		printed = write(1, formated, 1);
	*str += i + 1;
	return (free(substr), free(formated), printed);
}

char	*get_radix(char type, va_list argl)
{
	char	*radix;

	radix = NULL;
	if (type == 'c')
		radix = ft_ctoa(va_arg(argl, int));
	else if (type == 's')
		radix = ft_strdup_pf(va_arg(argl, char *), 1);
	else if (type == 'p')
		radix = ft_strjoin_ip("0x", ft_utoa_base((unsigned long)
					va_arg(argl, void *), "0123456789abcdef"), 2);
	else if (type == 'd')
		radix = ft_itoa_base(va_arg(argl, int), "0123456789");
	else if (type == 'i')
		radix = ft_itoa_base(va_arg(argl, int), "0123456789");
	else if (type == 'u')
		radix = ft_utoa_base((unsigned int)va_arg(argl, int), "0123456789");
	else if (type == 'x')
		radix = ft_itoa_base(va_arg(argl, unsigned int), "0123456789abcdef");
	else if (type == 'X')
		radix = ft_itoa_base(va_arg(argl, unsigned int), "0123456789ABCDEF");
	else if (type == '%')
		radix = ft_ctoa('%');
	return (radix);
}

char	*ft_strdup_pf(const char *s1, int null)
{
	char	*duplicate;

	if (!s1 && null)
		return (ft_strdup_pf("(null)", 0));
	if (!s1)
		return (NULL);
	duplicate = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_memmove(duplicate, s1, ft_strlen(s1) + 1);
	return (duplicate);
}
