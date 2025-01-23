# Minishell

Minishell est un projet de l'École 42 qui consiste à créer une version simplifiée d'un shell UNIX. Ce projet permet de se familiariser avec les concepts de base des systèmes d'exploitation tels que la gestion des processus, l'interprétation de commandes, la manipulation des fichiers, et la communication inter-processus.

---

## 🛠️ Fonctionnalités

Minishell implémente les fonctionnalités suivantes :

- Lecture et exécution de commandes simples.
- Gestion des chemins relatifs et absolus.
- Redirections d'entrée (`<`) et de sortie (`>`).
- Pipes (`|`) pour connecter plusieurs commandes.
- Variables d'environnement.
- Implémentation de quelques **builtins** :
  - `echo` avec option `-n`
  - `cd` avec gestion des erreurs
  - `pwd` pour afficher le répertoire courant
  - `export` pour gérer les variables d'environnement
  - `unset` pour supprimer des variables d'environnement
  - `env` pour afficher l'environnement
  - `exit` pour quitter le shell
- Gestion des signaux :
  - `Ctrl+C` pour arrêter une commande en cours.
  - `Ctrl+D` pour quitter le shell.
  - `Ctrl+\` pour ignorer les interruptions.

---

## 🚀 Installation et Compilation

Pour compiler le projet, exécutez les commandes suivantes dans le répertoire principal :

```bash
git clone https://github.com/votre-utilisateur/minishell.git
cd minishell
make
```

L'exécutable sera généré sous le nom `minishell`.

---

## 📜 Utilisation

Lancez Minishell en exécutant :

```bash
./minishell
```

Exemple d'utilisation :

```bash
minishell > echo "Bienvenue dans Minishell"
Bienvenue dans Minishell
minishell > pwd
/home/votre_utilisateur/minishell
minishell > export VAR=test
minishell > echo $VAR
test
minishell > exit
```

---

## 🔍 Détails Techniques

### 📂 Structure du Projet

- `src/` : Contient les fichiers sources du programme.
- `includes/` : Contient les fichiers d'en-tête.
- `lib/` : Bibliothèques personnalisées (exemple : libft).
- `Makefile` : Script pour compiler le projet.

### 📑 Normes Respectées

Le projet respecte strictement les **normes de l'École 42** :
- Pas de variables globales.
- Maximum de 25 lignes par fonction.
- Maximum de 5 variables par fonction.
- Gestion rigoureuse des erreurs et des retours de fonction.

### 🚦 Gestion des Signaux

- `Ctrl+C` : Affiche un prompt propre (ne quitte pas le shell).
- `Ctrl+D` : Quitte le shell proprement.
- `Ctrl+\` : Ignore l'interruption et n'affiche rien.

---

## 📋 Exigences du Projet

Voici les principales attentes pour **Minishell** :

1. Ne pas recréer toutes les fonctionnalités de `bash` ou `zsh`.
2. Utiliser les appels système suivants :
   - `fork`
   - `execve`
   - `pipe`
   - `dup2`
   - `signal`
   - `wait` et `waitpid`
   - `getcwd`, `chdir`, `stat`, etc.
3. Gérer correctement la mémoire avec **valgrind** ou un outil similaire.

---

## 🧪 Tests

Pour tester le shell, vous pouvez utiliser les commandes suivantes :

```bash
# Lancer une commande simple
echo "hello world"

# Tester les pipes
echo "hello" | grep "h"

# Tester les redirections
echo "hello" > file.txt
cat < file.txt

# Tester les builtins
cd ..
pwd
export TEST=42
echo $TEST
unset TEST
env
```

---

## 🛡️ Gestion des Erreurs

Minishell gère les cas d'erreur suivants :
- Commandes non reconnues (`command not found`).
- Mauvais chemins pour les fichiers ou dossiers.
- Redirections invalides.
- Syntaxe incorrecte (`|`, `>` ou `<` mal placés).

---

## 🤝 Contributeurs

- **Nom Prénom** - [GitHub](https://github.com/votre-utilisateur)
- **Nom Prénom** - [GitHub](https://github.com/votre-utilisateur)

---

## 📝 Licence

Ce projet est réalisé dans le cadre du cursus de l'École 42 et est soumis aux règles de son **règlement pédagogique**.

---

## 📚 Ressources Utiles

- [Manuels Linux](https://man7.org/linux/man-pages/)
- [GNU Bash Documentation](https://www.gnu.org/software/bash/manual/)
- [42 Docs](https://github.com/42Docs/42Docs)

---
