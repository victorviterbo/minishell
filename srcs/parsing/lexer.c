/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:27:53 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/26 22:04:05 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_token_type(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (STDOUT_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (STDIN_HEREDOC);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '>')
		return (STDOUT);
	else if (*str == '<')
		return (STDIN);
	else if (*str == '(')
		return (OPENPAR);
	else if (*str == ')')
		return (CLOSEPAR);
	else
		return (WORD);
}

static void	find_token_end(char *str, size_t *j, char type)
{
	char	quote;

	if (type != WORD)
	{
		(*j)++;
		if (type == STDIN_HEREDOC || type == STDOUT_APPEND
			|| type == AND || type == OR)
			(*j)++;
		return ;
	}
	while (str[*j] && !ft_isspace(str[*j])
		&& ft_strchr("|()<>", str[*j]) == NULL
		&& ft_strncmp(str + *j, "&&", 2))
	{
		if (str[*j] == '\'' || str[*j] == '"')
		{
			quote = str[*j];
			(*j)++;
			while (str[*j] && str[*j] != quote)
				(*j)++;
		}
		if (str[*j])
			(*j)++;
	}
	return ;
}

static void	lexer_error(t_data *data, t_token *current)
{
	ft_error(data, "lexer: memory allocation failed");
	free_tokens(data->tokens);
	data->tokens = NULL;
	free_token(current);
}

void	lexer(t_data *data, char *str)
{
	t_token	*current;
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]))
		{
			i++;
			continue ;
		}
		j = i;
		current = ft_calloc(1, sizeof(t_token));
		if (!current)
			return (lexer_error(data, current));
		current->type = get_token_type(&str[j]);
		current->heredoc_fd = -1;
		find_token_end(str, &j, current->type);
		current->str = ft_substr(str, i, j - i);
		if (!current->str)
			return (lexer_error(data, current));
		push_back_token(&data->tokens, current);
		i = j;
	}
}
