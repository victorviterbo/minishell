/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:24 by vviterbo          #+#    #+#             */
/*   Updated: 2025/02/20 15:52:34 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	print_node(void *content);
void	test_tree_building(char *str);

int	main(void)
{
	test_tree_building("(A || B) && (C || D)");
	return (0);
	test_tree_building("plain test command");
	test_tree_building("plain test && another command");
	test_tree_building("A (B) || C && D");
	test_tree_building("A ( B && C | D) E");
}

void	print_node(void *content)
{
	ft_printf("node content = %s\n", content);
}

void	test_tree_building(char *str)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	build_tree(str, tree);
	ft_tree_trav(tree, print_node, IN_ORDER);
	ft_tree_clear(tree, free);
}
