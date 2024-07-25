/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:40:52 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/26 01:04:23 by dkolida          ###   ########.fr       */
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

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

// Lexer
typedef struct s_tokenizer
{
	char	**tokens;
	int		index;
	char	*token;
	int		in_double_q;
	int		in_single_q;
}	t_tokenizer;

typedef struct s_group
{
	char	*str;
	char	*in_file_name;
	char	*out_file_name;
}	t_group;

typedef struct s_shell
{
	// char		**env;
	t_env_var	**env_vars;
	int			last_exit_code;
	t_group		**pipe_groups;
}	t_shell;

// tokenizer
char	**tokenize(char *input);

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

// drivers
char		*ft_read_line(char *line);
t_shell		*init_shell(void);
int			run_shell(t_shell *shell);
void		free_shell(t_shell *shell);
void		sigint_handler(int sig_num);

// lexer
t_group		**group_input(char *line);
void		print_groups(t_group **groups);
void		free_groups(t_group **groups);

// helpers
void	ft_free_split(char **split);
char	*ft_strjoin_char(char *s1, char c);
char	*char_to_str(char c);

#endif
