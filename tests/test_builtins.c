/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 05:19:53 by madelmen          #+#    #+#             */
/*   Updated: 2025/01/27 05:19:53 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void my_echo(int argc, char *argv[]) {
    int i = 1;
    int newline = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        newline = 0;
        i++;
    }

    for (; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    
    if (newline) {
        printf("\n");
    }
}

void my_cd(char *path) {
    if (chdir(path) != 0) {
        perror("cd");
    }
}

void my_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void my_export(char *var) {
    if (putenv(var) != 0) {
        perror("export");
    }
}

void my_unset(char *var) {
    if (unsetenv(var) != 0) {
        perror("unset");
    }
}

void my_env() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void my_exit() {
    exit(0);
}

int main(int argc, char *argv[]) {
    // Simuler des appels de builtins
    if (argc > 1) {
        if (strcmp(argv[1], "echo") == 0) {
            my_echo(argc - 1, argv + 1);
        } else if (strcmp(argv[1], "cd") == 0) {
            if (argc > 2) my_cd(argv[2]);
        } else if (strcmp(argv[1], "pwd") == 0) {
            my_pwd();
        } else if (strcmp(argv[1], "export") == 0) {
            if (argc > 2) my_export(argv[2]);
        } else if (strcmp(argv[1], "unset") == 0) {
            if (argc > 2) my_unset(argv[2]);
        } else if (strcmp(argv[1], "env") == 0) {
            my_env();
        } else if (strcmp(argv[1], "exit") == 0) {
            my_exit();
        } else {
            printf("Commande inconnue : %s\n", argv[1]);
        }
    }

    return 0;
}
