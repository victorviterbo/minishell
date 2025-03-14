/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:26:45 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/14 19:31:55 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_error(t_data *data, t_token *head, t_token *current);
void	free_token(void *content);
void	free_tokens(t_token *head);

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
