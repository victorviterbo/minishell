/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_external_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:51:42 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/30 13:51:42 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_child_process(t_data *data, char *path, char **args);
static void	handle_parent_process(t_data *data, pid_t pid);
int			create_process(t_data *data, char *path, char **args);


/* ************************************************************************** */
/*                                                                            */
/*   Gestion du processus enfant.                                             */
/*                                                                            */
/*   Cette fonction remplace le processus actuel par la commande:             */
/*   1. Utilise execve pour charger le nouveau programme                      */
/*   2. En cas d'échec, termine le processus avec EXIT_FAILURE                */
/*                                                                            */
/*   Note: Si execve réussit, cette fonction ne retourne jamais               */
/*   car le processus est remplacé                                            */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - Échec d'execve -> Affiche erreur et exit(EXIT_FAILURE)                 */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : données du shell (pour l'environnement)                         */
/*   - path : chemin de l'exécutable                                          */
/*   - args : arguments de la commande                                        */
/*                                                                            */
/* ************************************************************************** */
static void	handle_child_process(t_data *data, char *path, char **args)
{
	int	status;

	/*
	// je pense que c'est utile de mettre ces signaux en default 
	// pour chaque child process
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	*/
	execve(path, args, data->env);
	if (errno == ENOENT)
		status = 127;
	else if (errno == EACCES)
		status = 126;
	else
		status = EXIT_FAILURE;
	ft_print_error(args[0]);
	exit (status);
}

/* ************************************************************************** */
/*                                                                            */
/*   Gestion du processus parent.                                             */
/*                                                                            */
/*   Cette fonction:                                                          */
/*   1. Attend la fin du processus enfant avec waitpid                        */
/*   2. Analyse le statut de sortie:                                          */
/*      - Terminaison normale -> WEXITSTATUS                                  */
/*      - Terminaison par signal -> WTERMSIG + 128 (à implémenter)            */
/*                                                                            */
/*   Mise à jour:                                                             */
/*   - data->exit_status avec le code de retour approprié                     */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : données du shell pour stocker le statut                         */
/*   - pid  : PID du processus enfant à attendre                              */
/*                                                                            */
/* ************************************************************************** */
static void	handle_parent_process(t_data *data, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
	else
		data->exit_status = EXIT_FAILURE;
}

/* ************************************************************************** */
/*                                                                            */
/*   Création et gestion d'un nouveau processus.                              */
/*                                                                            */
/*   Cette fonction gère le cycle de vie d'une commande:                      */
/*   1. Fork pour créer un nouveau processus                                  */
/*   2. Dans l'enfant:                                                        */
/*      - Exécution de la commande                                            */
/*   3. Dans le parent:                                                       */
/*      - Attente de la fin de l'enfant                                       */
/*      - Récupération du statut                                              */
/*                                                                            */
/*   Gestion d'erreurs:                                                       */
/*   - Échec du fork     -> EXIT_FAILURE                                      */
/*   - Échec d'exécution -> Statut d'erreur dans data->exit_status            */
/*                                                                            */
/*   Paramètres:                                                              */
/*   - data : données du shell                                                */
/*   - path : chemin complet de l'exécutable                                  */
/*   - args : arguments de la commande                                        */
/*                                                                            */
/* ************************************************************************** */
int	create_process(t_data *data, char *path, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_print_error("fork");
		data->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		handle_child_process(data, path, args);
	else
		handle_parent_process(data, pid);
	return (data->exit_status);
}
