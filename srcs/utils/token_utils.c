/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/17 19:33:22 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	push_back_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		ft_printf("Token: %s, Type: %d\n", current->str, current->type);
		current = current->next;
	}
}
