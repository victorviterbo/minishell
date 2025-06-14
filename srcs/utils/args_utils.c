/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:02:21 by vviterbo          #+#    #+#             */
/*   Updated: 2025/04/26 02:17:28 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_arrs(char **arr1, char **arr2, t_Inplace_Type inplace)
{
	if (arr1 && (inplace == FREE_S1 || inplace == FREE_S1S2))
		ft_free_array((void **)arr1, ft_arrlen(arr1));
	if (arr2 && (inplace == FREE_S2 || inplace == FREE_S1S2))
		ft_free_array((void **)arr2, ft_arrlen(arr2));
	return ;
}

static void	append_arr(char **arr1, char **arr2)
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

static void	remove_empty_strs(char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]))
		{
			arr[j] = arr[i];
			j++;
		}
		else
			free(arr[i]);
		i++;
	}
	arr[j] = NULL;
	return ;
}

char	**merge_strarr(t_data *data, char **arr1, char **arr2,
	t_Inplace_Type inplace)
{
	char	**joined_arr;

	if (!arr1 || !arr2)
		return (free_arrs(arr1, arr2, inplace), NULL);
	remove_empty_strs(arr1);
	remove_empty_strs(arr2);
	joined_arr = ft_calloc(ft_arrlen(arr1) + ft_arrlen(arr2) + 1,
			sizeof(char *));
	if (!joined_arr)
		return (ft_error(data, "argument merge: memory allocation failed"),
			free_arrs(arr1, arr2, inplace), NULL);
	append_arr(joined_arr, arr1);
	append_arr(joined_arr, arr2);
	if (inplace == FREE_S1 || inplace == FREE_S1S2)
		free(arr1);
	if (inplace == FREE_S2 || inplace == FREE_S1S2)
		free(arr2);
	return (joined_arr);
}
