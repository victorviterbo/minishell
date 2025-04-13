/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:10:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/13 10:59:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**substitute_wildcard(t_data *data, char *str)
{
	char	**candidates;
	t_list	**matches;
	char	**sorted_matches;

	candidates = ls_curr_dir(data);
	if (!candidates)
		return (NULL);
	// TODO: check behaviour for hidden files -> only if first character is . -> to investigate
	matches = filter_matches(data, candidates, str);
	ft_free_array((void **)candidates, ft_arrlen(candidates));
	if (!matches)
		return (NULL);
	sorted_matches = sort_join_matches(data, matches);
	return (sorted_matches);
}

char	**ls_curr_dir(t_data *data)
{
	char			**files;
	DIR				*curr_dir;
	struct dirent	*dp;

	files = NULL;
	curr_dir = opendir(".");
	if (!curr_dir)
		return (ft_error(data, "wildcard: could not open directory"),
			free(files), NULL);
	dp = readdir(curr_dir);
	while (dp)
	{
		files = add_fname_to_arr(data, dp->d_name, files);
		if (!files)
			return (closedir(curr_dir), NULL);
		dp = readdir(curr_dir);
	}
	if (errno)
		return (ft_error(data, "wildcard: could not read directory"),
			ft_free_array((void **)files, ft_arrlen(files)),
			closedir(curr_dir), NULL);
	closedir(curr_dir);
	return (files);
}

char	**add_fname_to_arr(t_data *data, const char *fname, char **files)
{
	char	*curr_file;

	curr_file = ft_strdup(fname);
	if (!curr_file)
		return (ft_error(data, "wildcard: memory allocation failed"),
			ft_free_array((void **)files, ft_arrlen(files)), NULL);
	files = ft_array_append(files, curr_file, false);
	if (!files)
		return (ft_error(data, "wildcard: memory allocation failed"),
			free(curr_file), NULL);
	return (files);
}

t_list	**filter_matches(t_data *data, char **candidates, char *pattern)
{
	t_list	**matches;
	t_list	*new_match;

	if (!candidates)
		return (NULL);
	matches = ft_calloc(1, sizeof(t_list *));
	if (!matches)
		return (ft_error(data, "wildcard; memory allocation failed"), NULL);
	while (*candidates)
	{
		if (is_wildcard_match(pattern, *candidates))
		{
			new_match = ft_lstnew_void(*candidates);
			if (!new_match)
				return (ft_error(data, "wildcard: memory allocation failed"),
					ft_lstclear(matches, free), NULL);
			ft_lstadd_back(matches, new_match);
		}
		candidates++;
	}
	return (matches);
}

bool	is_wildcard_match(char *pattern, char *candidate)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*' && pattern[i + 1] == '*')
			i++;
		else if (pattern[i] != '*' && pattern[i] != candidate[j])
			return (false);
		else if (pattern[i] == '*' && !pattern[i + 1])
			return (true);
		else if (pattern[i] == '*' && pattern[i + 1] == candidate[j])
		{
			if (is_wildcard_match(pattern + i + 1, candidate + j))
				return (true);
		}
		i += pattern[i] != '*';
		j += 1;
	}
	return (!candidate[j]);
}

char	**sort_join_matches(t_data *data, t_list **matches)
{
	t_list	*current;
	t_list	*best;
	char	**sorted_args;

	while (matches)
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
		ft_lstpop(matches, best, free);
		if (!sorted_args)
			return (ft_error(data, "wildcard: memory allocation failed"),
				ft_lstclear(matches, free), NULL);
	}
	return (sorted_args);
}
