/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:20:33 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/14 22:52:14 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_join_matches(t_data *data, t_list **matches)
{
	t_list	*current;
	t_list	*best;
	char	**sorted_args;

	current = *matches;
	sorted_args = NULL;
	while (current)
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
		ft_lstpop(matches, best, no_free);
		if (!sorted_args)
			return (ft_error(data, "wildcard: memory allocation failed"),
				ft_lstclear(matches, free), NULL);
	}
	return (sorted_args);
}

char	**merge_strarr(t_data *data, char **arr1, char **arr2,
			t_Inplace_Type inplace)
{
	char	**joined_arr;

	if (!arr1 || !arr2)
		return (merge_error(arr1, arr2, inplace), NULL);
	joined_arr = ft_calloc(ft_arrlen(arr1) + ft_arrlen(arr2) + 1,
			sizeof(char *));
	if (!joined_arr)
		return (ft_error(data, "argument merge: memory allocation failed"),
			merge_error(arr1, arr2, inplace), NULL);
	append_arr(joined_arr, arr1);
	append_arr(joined_arr, arr2);
	if (inplace == FREE_S1 || inplace == FREE_S1S2)
		free(arr1);
	if (inplace == FREE_S2 || inplace == FREE_S1S2)
		free(arr2);
	return (joined_arr);
}

void	merge_error(char **arr1, char **arr2, t_Inplace_Type inplace)
{
	if (arr1 && (inplace == FREE_S1 || inplace == FREE_S1S2))
		ft_free_array((void **)arr1, ft_arrlen(arr1));
	if (arr2 && (inplace == FREE_S2 || inplace == FREE_S1S2))
		ft_free_array((void **)arr2, ft_arrlen(arr2));
	return ;
}

void	append_arr(char **arr1, char **arr2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (arr1[i])
		i++;
	while (arr2[j])
	{
		arr1[i] = arr2[j];
		i++;
		j++;
	}
	return ;
}

void	no_free(void *content)
{
	(void)content;
	return ;
}
