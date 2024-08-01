/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:40:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/01 15:53:11 by dkolida          ###   ########.fr       */
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
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_command
{
	char	*path;
	int		in_fd;
	int		out_fd;
	char	***cmd;
	char	**envp;
	char	**envp_path;
}	t_command;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_group
{
	char	**args;
	char	*in_file_name;
	char	*out_file_name;
	int		arg_i;
}	t_group;

typedef struct s_shell
{
	char		**env;
	t_env_var	**env_vars;
	int			last_exit_code;
	t_group		**groups;
	int			group_i;
}	t_shell;

// tokenizer
char		**get_tokens(t_shell *shell, char *input);

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
void		set_shell_env_vars(t_shell *shell);
char		**env_vars_to_env(t_env_var **env_vars);

// builtins
int			cd_builtin(t_shell *shell, char **args);
int			echo_builtin(t_shell *shell, char **args);
int			env_builtin(t_shell *shell);
int			export_builtin(t_shell *shell, char **args);
int			unset_builtin(t_shell *shell, char **args);
int			pwd_builtin(t_shell *shell);
int			exit_builtin(t_shell *shell, char **args);

// drivers
char		*ft_read_line(char *line);
t_shell		*init_shell(void);
int			run_shell(t_shell *shell);
void		free_shell(t_shell *shell);
void		sigint_handler(int sig_num);
int			exec_command(t_shell *shell, char **args);

// lexer
void		group_input(t_shell *shell, char **tokens);
void		print_groups(t_group **groups);
void		free_groups(t_group **groups);

// helpers
void		ft_free_split(char **split);
char		*ft_strjoin_char(char *s1, char c);
char		*char_to_str(char c);
char		*ft_strjoin_and_free(char *str1, char *str2);

// execve
int			execve_path(t_shell *shell, char **args);
char		**envp_path(char **envp);
char		*get_path(char **path, char *cmd);

#endif
