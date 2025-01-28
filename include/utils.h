/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:04:30 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/28 17:59:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H


# include "minishell.h"

//utils/error_handlings.c
void	ft_perror_exit(const char *message);
void	ft_custom_error_exit(const char *message);
//utils/variables.c
int		init_env(t_data *data, char **envp);
int		new_var(t_list **env, char *str);
int		add_var(t_list **env, char *str, size_t name_len);
int		change_var(t_list *current, char *first_equal, bool append);
char	*get_var(t_data *data, char *varname);
#endif