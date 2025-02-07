/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:25:55 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/07 11:00:02 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_boolarray(bool *arr, char *str);

int	main(void)
{
	char	*test_str1;
	bool	*isquoted;

	test_str1 = ft_strdup("Lets try this \"string\"");
	isquoted = is_quoted(test_str1, '"', '"');
	print_boolarray(isquoted, test_str1);
	free(test_str1);
	free(isquoted);
	test_str1 = ft_strdup("\"What if it starts\" with a quoted \"string\"");
	isquoted = is_quoted(test_str1, '"', '"');
	print_boolarray(isquoted, test_str1);
	free(test_str1);
	free(isquoted);
	test_str1 = ft_strdup("and with 'other quoting chars'?");
	isquoted = is_quoted(test_str1, '\'', '\'');
	print_boolarray(isquoted, test_str1);
	free(test_str1);
	free(isquoted);
	test_str1 = ft_strdup("and \"unfinished quotes ?");
	if (is_quoted(test_str1, '"', '"'))
		return (free(isquoted), EXIT_FAILURE);
	free(test_str1);
	test_str1 = ft_strdup("what about {braces}");
	isquoted = is_quoted(test_str1, '{', '}');
	print_boolarray(isquoted, test_str1);
	free(test_str1);
	free(isquoted);
	test_str1 = ft_strdup("and in reverse {braces} now");
	if (is_quoted(test_str1, '}', '{'))
		return (free(isquoted), EXIT_FAILURE);
	free(test_str1);
	return (EXIT_SUCCESS);
}

void	print_boolarray(bool *arr, char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		ft_printf("%c", str[i]);
		if (i + 1 < ft_strlen(str))
			ft_printf(", ");
		i++;
	}
	ft_printf("\n", arr[i]);
	i = 0;
	while (i < ft_strlen(str))
	{
		ft_printf("%i", arr[i]);
		if (i + 1 < ft_strlen(str))
			ft_printf(", ");
		i++;
	}
	ft_printf("\n\n");
}
