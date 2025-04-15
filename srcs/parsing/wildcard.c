/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:10:09 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/15 15:10:51 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**wildcard_handle(t_data *data, char *parsed, int *isescaped,
	t_token_type type)
{
	char	**parsed_arr;

	parsed_arr = NULL;
	if ((type == STDIN || type == WORD) && ft_strchr(parsed, '*'))
	{
		parsed_arr = substitute_wildcard(data, parsed, isescaped);
		if (data->exit_status == EXIT_FAILURE)
			return (free(parsed), NULL);
	}
	if (!parsed_arr && data->exit_status == EXIT_SUCCESS)
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
{// TODO: check behaviour for hidden files -> only if first character is .
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

char	**filter_sort_matches(t_data *data, char **candidates, char *pattern,
		int *isescaped)
{
	t_list	**matches;
	size_t	i;

	matches = ft_calloc(1, sizeof(t_list *));
	if (!matches)
		return (ft_error(data, "wildcard; memory allocation failed"),
			ft_free_array((void **)candidates, ft_arrlen(candidates)), NULL);
	i = 0;
	while (candidates[i])
	{
		if (candidates[i][0] == '.' && pattern[0] != '.')
		{
			i++;
			continue ;
		}
		else if (is_wildcard_match(pattern, candidates[i], isescaped))
		{
			if (handle_match(data, matches, candidates[i]) == EXIT_FAILURE)
				return (ft_lstclear(matches, free), NULL);	
		}
		i++;
	}
	return (sort_matches(data, matches));
}

bool	is_wildcard_match(char *pattern, char *candidate, int *isescaped)
{
	int		i;
	int		j;
	bool	is_wildcard;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		is_wildcard = (pattern[i] == '*' && isescaped != IS_NOT_QUOTED);
		if (is_wildcard && pattern[i + 1] && pattern[i + 1] == '*')
			i++;
		else if (!is_wildcard && pattern[i] != candidate[j])
			return (false);
		else if (is_wildcard && !pattern[i + 1])
			return (true);
		else if (is_wildcard && pattern[i + 1] == candidate[j])
		{
			if (is_wildcard_match(pattern + i + 1, candidate + j, isescaped))
				return (true);
		}
		i += (pattern[i] != '*' || i == -1);
		j += 1;
	}
	return (!candidate[j]);
}
