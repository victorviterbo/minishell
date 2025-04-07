/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/06 22:01:09 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_error(t_data *data, t_token *head, t_token *current)
{
	data->exit_status = errno;
	//ft_fprintf(STDERR_FILENO, "lexer: %s\n", strerror(data->exit_status));
	free_tokens(head);
	free_token(current);
	return (NULL);
}

void	free_token(void *content)
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

void	free_tokens(t_token *head)
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

t_token	*copy_token(t_data *data, t_token *token)
{
	t_token	*new_tok;

	new_tok = ft_calloc(1, sizeof(t_token));
	if (!new_tok)
		return (ft_error(data, "malloc: memory allocation failed"), NULL);
	new_tok->str = ft_strdup(token->str);
	if (!new_tok->str)
	{
		ft_error(data, "malloc: memory allocation failed");
		free(new_tok);
		return (NULL);
	}
	new_tok->type = token->type;
	return (new_tok);
}

void	push_back_token(t_token **list, t_token *token)
{
	t_token	*index;

	if (!*list)
		*list = token;
	else
	{
		index = *list;
		while (index->next)
			index = index->next;
		index->next = token;
	}
}
