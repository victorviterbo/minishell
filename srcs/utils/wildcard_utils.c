/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:20:33 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/26 15:24:53 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_match(t_data *data, t_list **matches, char *new_match)
{
	t_list	*new_match_node;
	char	*tmp;

	tmp = ft_strdup(new_match);
	if (!tmp)
		return (ft_error(data, "wildcard: memory allocation failed"),
			EXIT_FAILURE);
	new_match_node = ft_lstnew_void(tmp);
	if (!new_match_node)
		return (ft_error(data, "wildcard: memory allocation failed"),
			free(tmp), EXIT_FAILURE);
	ft_lstadd_back(matches, new_match_node);
	return (EXIT_SUCCESS);
}

bool	is_wildcard_match(char *pattern, char *candidate, int *isescaped)
{
	int		i;
	int		j;
	bool	is_wildcard;

	i = 0;
	j = 0;
	while (pattern[i] && candidate[j])
	{
		is_wildcard = (pattern[i] == '*' && isescaped[i] == IS_NOT_QUOTED);
		while (is_wildcard && pattern[i + 1] && pattern[i + 1] == '*')
			i++;
		if (!is_wildcard && pattern[i] != candidate[j])
			return (false);
		else if (is_wildcard && pattern[i + 1] == candidate[j])
		{
			if (is_wildcard_match(pattern + i + 1, candidate + j, isescaped))
				return (true);
		}
		i += (pattern[i] != '*');
		j += 1;
	}
	if ((pattern[i] == '*' && isescaped[i] == IS_NOT_QUOTED) && !pattern[i + 1])
		return (true);
	return (!candidate[j] && !pattern[i]);
}

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
			if (ft_stricmp(current->content, best->content) < 0)
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
