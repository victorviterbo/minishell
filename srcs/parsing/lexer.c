/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:27:53 by vbronov           #+#    #+#             */
/*   Updated: 2025/04/07 13:29:36 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		get_token_type(char *str);
static void		find_token_end(char *str, size_t *j, char type);
static void		add_back_token(t_token **head, t_token *current);
t_token			*lexer(t_data *data, char *str);

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
		&& ft_strchr("|&()<>", str[*j]) == NULL)
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

static void	add_back_token(t_token **head, t_token *current)
{
	t_token	*last;

	if (!head)
		return ;
	if (!*head)
	{
		*head = current;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = current;
}

t_token	*lexer(t_data *data, char *str)
{
	t_token	*head;
	t_token	*current;
	size_t	i;
	size_t	j;

	head = NULL;
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
			return (lexer_error(data, head, current));
		current->type = get_token_type(&str[j]);
		find_token_end(str, &j, current->type);
		current->str = ft_substr(str, i, j - i);
		if (!current->str)
			return (lexer_error(data, head, current));
		add_back_token(&head, current);
		i = j;
	}
	return (head);
}
