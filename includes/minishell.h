/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:40:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 00:24:14 by dmodrzej         ###   ########.fr       */
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

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_group
{
	char	*str;
	char	*in_file_name;
	char	*out_file_name;
}	t_group;

typedef struct s_shell
{
	char		**env;
	int			exit_code;
	int			last_exit_code;
	t_env_var	**env_vars;
	t_group		**pipe_groups;
}	t_shell;

// env
t_env_var	*new_env_var(char *key, char *value);
void		add_env_var(t_env_var **env_vars, t_env_var *new);
t_env_var	*last_env_var(t_env_var *var);
void		free_env_var(t_env_var *var);
void		free_all_env_vars(t_env_var **env_vars);
int			set_env_var(t_shell *shell, char *key, char *value);
char		*get_env_var(t_shell *shell, char *key);
void		remove_env_var(t_shell *shell, char *key);
void		print_env_var(t_env_var *var);

// builtins
int			cd_builtin(t_shell *shell, char **args);
int			echo_builtin(t_shell *shell, char **args);
int			env_builtin(t_shell *shell);
int			export_builtin(t_shell *shell, char **args);
int			unset_builtin(t_shell *shell, char **args);
int			pwd_builtin(t_shell *shell);
int			exit_builtin(t_shell *shell, char **args);
int			exec_builtins(t_shell *shell, char **args);

// commands
int			parse_command(t_shell *shell, char *line);

// helpers
void		ft_free_split(char **split);

// groups.c
t_group		**group_input(char *line);
void		print_groups(t_group **groups);
void		parse_groups(t_group **groups);

// shell.c
int			run_shell(t_shell *shell);
void		free_shell(t_shell *shell);
t_shell		init_shell(char **env);

// readline_wrapper.c
char		*ft_read_line(char *line);

// signal_handlers.c
void		sigint_handler(int sig_num);

#endif
