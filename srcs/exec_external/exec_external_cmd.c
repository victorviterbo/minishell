/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:47 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/29 11:10:47 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_parent_process(t_data *data, pid_t pid);
static void	handle_child_process(t_data *data, char *path, char **args);
static char	*get_cmd_path(char *cmd, char **paths);
int			execute_external_cmd(t_data *data, char **args);

/* ************************************************************************** */
/*                                                                            */
/*   Recherche du chemin complet d'une commande.                              */
/*                                                                            */
/*   Pour chaque dossier dans PATH:                                           */
/*   1. Construit le chemin: dossier + "/" + commande                         */
/*   2. Vérifie existence et permissions d'exécution                          */
/*   3. Retourne le premier chemin valide trouvé                              */
/*                                                                            */
/*   Gestion mémoire:                                                         */
/*   - Libère les allocations temporaires (tmp)                               */
/*   - Libère cmd_path si le chemin n'est pas valide                          */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - Échec malloc -> NULL                                                   */
/*   - Commande non trouvée -> NULL                                           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - cmd   : nom de la commande à chercher                                  */
/*   - paths : tableau des dossiers PATH à explorer                           */
/*                                                                            */
/* ************************************************************************** */
static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (ft_error_print("malloc"), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (ft_exit_error("malloc"), NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*   Recherche et exécution d'une commande via PATH.                          */
/*                                                                            */
/*   Processus de recherche:                                                  */
/*   1. Récupération et découpage de PATH                                     */
/*   2. Pour chaque dossier dans PATH:                                        */
/*      - Construction du chemin complet                                      */
/*      - Vérification existence et permissions                               */
/*                                                                            */
/*   Une fois trouvée:                                                        */
/*   - Création d'un processus pour l'exécution                               */
/*   - Attente de la terminaison                                              */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - PATH non trouvé      -> 127                                            */
/*   - Commande introuvable -> 127                                            */
/*   - Erreur malloc        -> 127                                            */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : données du shell                                                */
/*   - args : arguments de la commande                                        */
/*                                                                            */
/* ************************************************************************** */
static int	handle_path_search(t_data *data, char **args)
{
	char	**paths;
	char	*cmd_path;
	int		status;

	paths = ft_split(get_var(data, "PATH"), ':');
	if (!paths)
		return (ft_error_print("PATH"), 127);
	cmd_path = get_cmd_path(args[0], paths);
	ft_free_split(paths);
	if (!cmd_path)
		return (ft_print_error(args[0]), 127);
	status = create_process(data, cmd_path, args);
	return (free(cmd_path), status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Gestion des chemins absolus pour une commande.                           */
/*                                                                            */
/*   Vérifie si une commande avec chemin absolu (/bin/ls) est:                */
/*   1. Existante (F_OK)                                                      */
/*   2. Exécutable (X_OK)                                                     */
/*                                                                            */
/*   Si la commande est valide:                                               */
/*   - Crée un nouveau processus pour l'exécuter                              */
/*   - Attend sa terminaison                                                  */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - Commande inexistante  -> 127                                           */
/*   - Droits insuffisants   -> 127                                           */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : données du shell                                                */
/*   - args : arguments de la commande                                        */
/*                                                                            */
/* ************************************************************************** */
static int	handle_abs_path(t_data *data, char **args)
{
	struct stat	path_stat;

	if (stat(args[0], &path_stat) == 0)
	{
		if ((path_stat.st_mode & S_IFDIR) == S_IFDIR)
			return (ft_print_error("is a directory"), 126);
	}
	if (access(args[0], F_OK | X_OK) == 0)
		return (create_process(data, args[0], args));
	return (ft_print_error(args[0]), 127);
}

/* ************************************************************************** */
/*                                                                            */
/*   Exécution d'une commande externe dans le shell.                          */
/*                                                                            */
/*   Point d'entrée principal pour l'exécution des commandes externes.        */
/*   Cette fonction gère deux cas:                                            */
/*   1. Chemins absolus (/bin/ls):                                            */
/*      - Vérifie directement l'existence et les permissions                  */
/*                                                                            */
/*   2. Commandes simples (ls):                                               */
/*      - Recherche dans les dossiers de PATH                                 */
/*      - Construit le chemin complet                                         */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - Arguments invalides    -> 127                                          */
/*   - Commande non trouvée   -> 127                                          */
/*   - PATH non trouvé        -> 127                                          */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : structure contenant l'environnement et les statuts              */
/*   - args : tableau des arguments (args[0] est la commande)                 */
/*                                                                            */
/* ************************************************************************** */
int	exec_external_cmd(t_data *data, char **args)
{
	if (ft_strchr(args[0], '/'))
		return (handle_abs_path(data, args));
	return (handle_path_search(data, args));
}
