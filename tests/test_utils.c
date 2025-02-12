/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:35:18 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/12 17:47:56 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char	**ft_make_test_strarr(char *str);
void	free_env(t_data *data);

char	**ft_make_test_strarr(char *str)
{
	char	**test_arr;

	test_arr = ft_calloc(2, sizeof(char *));
	test_arr[0] = str;
	test_arr[1] = NULL;
	return (test_arr);
}

void	free_env(t_data *data)
{
	ft_lstclear(data->envp, free_var);
	free(data->envp);
	ft_free_array((void **)data->env_arr, ft_arrlen(data->env_arr));
	free(data);
}
