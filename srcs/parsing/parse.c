/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:45:49 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/06 11:34:04 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_str(t_data *data, char *str);
char	**split_cmd(t_data *data, char *str, int *quoted);
bool	is_ifs(char c);
int		count_segments(char const *s, int *quoted);
int		go_to_next_ifs(const char *s, size_t i, int *quoted);

char	*parse_str(t_data *data, char *str)
{
	char	*parsed;
	int		*isescaped;

	isescaped = is_quote_escaped(str);
	if (!isescaped)
		ft_print_error("parsing: unfinished quotation");
	parsed = expand_var(data, str, isescaped);
	if (!parsed)
		ft_print_error("parsing: variable expansion failed");
	free(isescaped);
	isescaped = is_quote_escaped(parsed);
	if (!isescaped)
		ft_print_error("parsing: unfinished quotation");
	parsed = remove_quotes_ws(parsed, isescaped, true);
	if (!parsed)
		ft_print_error("parsing: removing of quotations failed");
	free(isescaped);
	return (parsed);
}

char	**split_cmd(t_data *data, char *str, int *quoted)
{
	char	**strarray;
	size_t	i;
	size_t	start;
	size_t	k;

	strarray = ft_calloc(count_segments(str, quoted) + 1, sizeof(char *));
	if (!strarray)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		i = go_to_next_ifs(str, i , quoted);
		if (!str[i])
			break ;
		start = i;
		i = go_to_next_ifs(str, i , quoted);
		strarray[k] = ft_substr(str, start, i - start);
		if (!strarray[k])
			return (ft_free_array((void **)strarray, k), NULL);
		k++;
	}
	strarray[k] = NULL;
	return (strarray);
}

static int	count_segments(char const *s, int *quoted)
{
	unsigned int	count;
	size_t			i;

	i = 0;
	while (s[i] && is_ifs(s[i]))
		i++;
	count = (s[i] != '\0');
	while (s[i])
	{
		if (is_ifs(s[i]) && quoted[i] == IS_NOT_QUOTED
			&& s[i + 1] && !is_ifs(s[i]))
			count++;
		i++;
	}
	return (count);
}

static int	go_to_next_ifs(const char *s, size_t i, int *quoted)
{
	while (s[i] && !is_ifs(s[i]) && quoted[i] == IS_NOT_QUOTED)
		i++;
	return (i);
}

static bool	is_ifs(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (true);
}
