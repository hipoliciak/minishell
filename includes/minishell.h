/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:40:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 02:34:00 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_group
{
	char	*str;
	char	*in_file_name;
	char	*out_file_name;
}	t_group;
typedef struct s_shell
{
	char	**env;
	int		exit_code;
	t_group	**pipe_groups;
}	t_shell;

char	**tokenize(char *input);

//helpers
void	ft_free_split(char **split);

// groups.c
t_group	**group_input(char *line);
void	print_groups(t_group **groups);
void	parse_groups(t_group **groups);

// shell.c
int		run_shell(t_shell *shell);
void	free_shell(t_shell *shell);
t_shell	init_shell(char **env);

// readline_wraper.c
char	*ft_read_line(char *line);

// signal_handlers.c
void	sigint_handler(int sig_num);

// Builtins
char	*get_env_var(char **env, char *var);
int		builtin_cd(t_shell *shell, char **args);
int		builtin_echo(t_shell *shell, char **args);
int		builtin_env(t_shell *shell, char **args);
int		builtin_exit(t_shell *shell, char **args);
int		builtin_pwd(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int		set_env(t_shell *shell, char *key, char *value);
int		builtin_export(t_shell *shell, char **args);

#endif
