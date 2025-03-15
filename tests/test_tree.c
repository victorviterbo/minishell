/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:24 by vviterbo          #+#    #+#             */
/*   Updated: 2025/03/15 15:13:25 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_tree_building(t_data *data, t_token *token);
void	print_node(void *param);
void	print_node_leaf(void *param);
void	ft_tree_trav_test(t_tree *node, void (*f)(void *));
void	ft_tree_trav_test_leaf(t_tree *node, void (*f)(void *));

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	t_token	*token;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	init_env(data, envp);
	token = lexer(data, "(AAAA+ 1 2 || B) && (C || D)");
	print_tokens(token);
	test_tree_building(data, token);
	return (0);
	/*
	test_tree_building("plain test command");
	test_tree_building("plain test && another command");
	test_tree_building("A (B) || C && D");
	test_tree_building("A <( B && C | D) | E");
	free_env(data);
	*/
}

void	test_tree_building(t_data *data, t_token *token)
{
	t_tree	*tree;

	(void)data;
	tree = ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return ;
	build_tree(token, tree, false);
	ft_tree_trav_test(tree, print_node);
	//tree_error_token(NULL, tree);
	ast_trav(data, tree);
	ft_tree_trav_test_leaf(tree, print_node_leaf);
	tree_error_leaf(NULL, tree);
	//free_env(data);
	token = lexer(data, "(AAAA+ 1 2 || B) && (C || D)");
	make_ast(data, token);
	ft_tree_trav_test_leaf(data->tree, print_node_leaf);
	tree_error_leaf(NULL, data->tree);
	free_env(data);
}

void	print_node(void *param)
{
	t_tree	*tree;
	t_token	*current;

	tree = (t_tree *)param;
	current = ((t_token *)tree->content);
	while (current)
	{
		ft_printf("node = %p, content = %s\n", current, current->str);
		current = current->next;
	}
}

void	print_node_leaf(void *param)
{
	int		i;
	t_tree	*tree;

	i = 0;
	tree = (t_tree *)param;
	if (tree->left || tree->right)
		ft_printf("node content = %s\n", ((t_token *)tree->content)->str);
	else
	{
		while (((t_leaf *)tree->content)->args[i])
		{
			ft_printf("leaf content = %s\n", ((t_leaf *)tree->content)->args[i]);
			i++;
		}
	}
}

void	ft_tree_trav_test(t_tree *node, void (*f)(void *))
{
	f(node);
	if (node->left)
		ft_tree_trav_test(node->left, f);
	if (node->right)
		ft_tree_trav_test(node->right, f);
	return ;
}

void	ft_tree_trav_test_leaf(t_tree *node, void (*f)(void *))
{
	f(node);
	if (node->left)
		ft_tree_trav_test(node->left, f);
	if (node->right)
		ft_tree_trav_test(node->right, f);
	return ;
}
