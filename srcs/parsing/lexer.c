/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:27:53 by vbronov           #+#    #+#             */
/*   Updated: 2025/03/07 13:28:35 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)content;
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
	token->next = NULL;
	free(token);
}

static void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

static t_token	*lexer_error(t_data *data, t_token *head, t_token *current)
{
	data->exit_status = errno;
	ft_fprintf(STDERR_FILENO, "lexer: %s\n", strerror(data->exit_status));
	free_tokens(head);
	free_token(current);
	return (NULL);
}

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

static void	find_word_end(char *str, size_t *j)
{
	char    quote;

	while (str[*j] && !ft_isspace(str[*j]) && ft_strchr("|&()<>", str[*j]) == NULL)
	{
		//TODO: validate quotes edge cases, e.g. quotes escaping
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
}

static void	find_sep_end(char type, size_t *j)
{
	(*j)++;
	if (type == STDIN_HEREDOC || type == STDOUT_APPEND || type == AND || type == OR)
		(*j)++;
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
		if (current->type == WORD)
			find_word_end(str, &j);
		else
			find_sep_end(current->type, &j);
		current->str = ft_substr(str, i, j - i);
		if (!current->str)
			return (lexer_error(data, head, current));
		add_back_token(&head, current);
		i = j;
	}
	return (head);
}