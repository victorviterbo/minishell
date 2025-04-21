/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:01:12 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/21 09:36:03 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_free(void *content)
{
	(void)content;
	return ;
}

char	**sort_matches(t_data *data, t_list **matches)
{
	t_list	*current;
	t_list	*best;
	char	**sorted_args;

	sorted_args = NULL;
	while (*matches)
	{
		current = *matches;
		best = current;
		while (current)
		{
			if (ft_strcmp(current->content, best->content) < 0)
				best = current;
			current = current->next;
		}
		sorted_args = ft_array_append(sorted_args, best->content, false);
		if (!sorted_args)
			return (ft_error(data, "wildcard: memory allocation failed"),
				ft_lstclear(matches, free), NULL);
		ft_lstpop(matches, best, no_free);
	}
	free(matches);
	return (sorted_args);
}
