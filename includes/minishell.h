/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:40:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/09/01 23:58:03 by dkolida          ###   ########.fr       */
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
# include <fcntl.h>

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
	int			tokens_count;
	int			out_fd;
}	t_shell;

typedef struct s_tokenizer
{
	char	**tokens;
	int		index;
	char	*token;
	int		in_double_q;
	int		in_single_q;
	int		*not_interpolate;
}	t_tokenizer;

// tokenizer
t_tokenizer	*get_tokens(t_shell *shell, char *input);
t_tokenizer	*tokenizer_init(int token_count);
int			free_tokenizer(t_tokenizer *tokenizer);
void		interpolate(t_shell *shell, t_tokenizer *data);

// env
t_env_var	*new_env_var(char *key, char *value);
void		add_env_var(t_env_var **env_vars, t_env_var *new);
t_env_var	*last_env_var(t_env_var *var);
void		free_env_var(t_env_var *var);
void		free_all_env_vars(t_env_var **env_vars);
int			set_env_var(t_shell *shell, char *key, char *value);
char		*get_env_var(t_shell *shell, char *key);
void		remove_env_var(t_shell *shell, char *key);
void		set_shell_env_vars(t_shell *shell, char **env);
char		**env_vars_to_env(t_env_var **env_vars);

// builtins
int			cd_builtin(t_shell *shell, char **args);
int			exit_builtin(t_shell *shell, char **args);
int			echo_builtin(t_shell *shell, char **args);
int			env_builtin(t_shell *shell);
int			export_builtin(t_shell *shell, char **args);
int			unset_builtin(t_shell *shell, char **args);
int			pwd_builtin(t_shell *shell);

// drivers
char		*ft_read_line(char *line);
t_shell		*init_shell(char **env);
int			run_shell(t_shell *shell);
void		free_shell(t_shell *shell);
void		sigint_handler(int sig_num);
void		ignore_sigquit(void);
void		set_signals_interactive(void);
void		set_signals_for_execution(void);
int			exec_builtin(t_shell *shell, char **args);
int			is_builtin(char *command);

// lexer
void		group_input(t_shell *shell, t_tokenizer *data);
void		print_groups(t_group **groups);
void		free_groups(t_group **groups, int tokens_count);

// helpers
void		ft_free_split(char **split);
char		*ft_strjoin_char(char *s1, char c);
char		*char_to_str(char c);
char		*ft_strjoin_and_free(char *str1, char *str2);

// execve
int			execve_path(t_shell *shell, char **args);
char		**envp_path(char **envp);
char		*get_path(char **path, char *cmd);
char		*set_path(t_shell *shell, char **args);
int			is_absolute_or_relative_path(char *cmd);

// pipe_helpers
void		make_pipe(int *pipefd);
int			make_fork(void);
void		exec_command(t_shell *shell, char **args);

int			is_builtin(char *command);

//shell
void		shell_exec(t_shell *shell, t_tokenizer *tokens);

int			shell_exec_in_child(t_shell *shell, int *pipe_fd, int in_fd, int i);
void		shell_print_output(int terminal_fd, int *pipe_fd);

#endif
