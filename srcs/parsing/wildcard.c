/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:10:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/27 18:18:15 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**wildcard_handle(t_data *data, char *parsed, int *isescaped,
	t_token_type type)
{
	char	**parsed_arr;

	parsed_arr = NULL;
	if (type < STDIN_HEREDOC && ft_strchr(parsed, '*'))
	{
		parsed_arr = substitute_wildcard(data, parsed, isescaped);
		if (data->exit_status == EXIT_FAILURE)
			return (free(parsed), NULL);
	}
	if (STDOUT <= type && type <= STDIN && parsed_arr
		&& ft_arrlen(parsed_arr) > 1)
		return (ft_error(data, "*: ambiguous redirect"), free(parsed),
			ft_free_array((void **)parsed_arr, ft_arrlen(parsed_arr)), NULL);
	if (!parsed_arr)
	{
		parsed_arr = ft_str_to_arr(parsed);
		if (!parsed_arr)
			return (ft_error(data, "parsing: memory allocation failed"),
				free(parsed), NULL);
	}
	else
		free(parsed);
	return (parsed_arr);
}

char	**substitute_wildcard(t_data *data, char *str, int *isescaped)
{
	char	**candidates;
	char	**sorted_matches;

	candidates = ls_curr_dir(data);
	if (!candidates)
		return (NULL);
	sorted_matches = filter_sort_matches(data, candidates, str, isescaped);
	ft_free_array((void **)candidates, ft_arrlen(candidates));
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
		while (dp && (!ft_strcmp(dp->d_name, ".")
				|| !ft_strcmp(dp->d_name, "..")))
			dp = readdir(curr_dir);
		files = add_fname_to_arr(data, dp->d_name, files);
		if (!files)
			return (closedir(curr_dir), NULL);
		dp = readdir(curr_dir);
	}
	if (errno)
		return (ft_error(data, "wildcard: could not read directory"),
			ft_free_array((void **)files, ft_arrlen(files)),
			closedir(curr_dir), NULL);
	return (closedir(curr_dir), files);
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

char	**filter_sort_matches(t_data *data, char **candidates, char *pattern,
		int *isescaped)
{
	t_list	**matches;
	size_t	i;

	matches = ft_calloc(1, sizeof(t_list *));
	if (!matches)
		return (ft_error(data, "wildcard: memory allocation failed"), NULL);
	i = 0;
	while (candidates[i])
	{
		if ((candidates[i][0] == '.'
			&& pattern[2 * !ft_strncmp(pattern, "./", 2)] != '.'))
		{
			i++;
			continue ;
		}
		else if (is_wildcard_match(pattern, candidates[i], isescaped))
		{
			if (handle_match(data, matches, candidates[i], pattern)
				== EXIT_FAILURE)
				return (ft_lstclear(matches, free), NULL);
		}
		i++;
	}
	return (sort_matches(data, matches));
}
