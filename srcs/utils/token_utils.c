/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/09 13:22:45 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content);
void	free_tokens(t_token *head);

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
