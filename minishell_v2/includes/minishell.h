/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 19:27:13 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- Project Headers --- */
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft.h"

/* --- External Libraries --- */
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/* --- Macros --- */
# define PROMPT "minishell> "
# define O_HEREDOC 0x1000
# define PARENT_PROMPT 0
# define CHILD_EXEC 1

/* --- Data Structures --- */
typedef struct s_expand_state
{
	const char		*arg;
	char			*result;
	char			quote_state;
}					t_expand_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_NEWLINE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

/* --- Abstract Syntax Tree (AST) Structures --- */
typedef enum e_node_type
{
	NODE_EXEC,
	NODE_PIPE,
	NODE_REDIR,
	NODE_SEQ,
	NODE_AND,
	NODE_OR
}					t_node_type;

typedef struct s_cmd
{
	t_node_type		type;
}					t_cmd;

typedef struct s_exec_cmd
{
	t_node_type		type;
	char			**argv;
}					t_exec_cmd;

typedef struct s_redir_cmd
{
	t_node_type		type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
}					t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_node_type		type;
	t_cmd			*left;
	t_cmd			*right;
}					t_pipe_cmd;

typedef struct s_seq_cmd
{
	t_node_type		type;
	t_cmd			*left;
	t_cmd			*right;
}					t_seq_cmd;

typedef struct s_and_cmd
{
	t_node_type		type;
	t_cmd			*left;
	t_cmd			*right;
}					t_and_cmd;

typedef struct s_or_cmd
{
	t_node_type		type;
	t_cmd			*left;
	t_cmd			*right;
}					t_or_cmd;

/* --- Shell State Structures --- */
typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_shell
{
	t_list			*env_list;
	int				exit_status;
}					t_shell;

/* --- Function Prototypes --- */

/* init.c */
void				init_shell(t_shell *shell, char **envp);
void				free_shell(t_shell *shell);
void				set_env_value(t_shell *shell, char *key, char *value);

/* init_utils.c */
void				update_existing_env(t_env *env_var, char *value);
void				create_new_env(t_shell *shell, char *key, char *value);
void				parse_and_set_env(t_shell *shell, char *envp_line);

/* signals.c */
void				setup_signals(int mode);

/* lexer.c */
t_token				*lexer(const char *line, t_shell *shell);
void				free_tokens(t_token *tokens);
t_token				*new_token(t_token_type type, char *value);
void				add_token_back(t_token **tokens, t_token *new);

/* lexer_utils2.c */
int					handle_greater(const char *s, int i, t_token **toks);
int					handle_less(const char *s, int i, t_token **toks);
int					handle_and_or(const char *s, int i, t_token **toks);

/* lexer utils */
t_token_type		peek_type(t_token **tokens);

/* parser.c */
t_cmd				*parse_command(t_token **tokens, t_shell *shell);
void				free_ast(t_cmd *cmd);

/* parser_utils.c */
t_cmd				*new_exec_cmd(void);
t_cmd				*new_redir_cmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd				*new_pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd				*new_seq_cmd(t_cmd *left, t_cmd *right);
void				consume_token(t_token **tokens);

/* parser_constructors.c */
t_cmd				*new_and_cmd(t_cmd *left, t_cmd *right);
t_cmd				*new_or_cmd(t_cmd *left, t_cmd *right);

/* parser_utils3.c */
t_cmd				*handle_redirection(t_token **tokens, t_shell *shell,
						t_cmd *cmd);
void				*parser_error(char *s, t_shell *shell, t_cmd *cmd);

/* parser_utils4.c */
void				add_arg_to_exec_cmd(t_exec_cmd *ecmd, char *arg);

/* parser_logic_free.c */
void				free_and_cmd(t_and_cmd *acmd);
void				free_or_cmd(t_or_cmd *ocmd);

/* executor.c */
void				execute_ast(t_cmd *cmd, t_shell *shell);
void				execute_simple_command(t_cmd *cmd, t_shell *shell,
						int in_pipe);
void				execute_in_child(t_exec_cmd *cmd, t_shell *shell);
int					apply_redirections(t_list *redir_list, t_shell *shell);

/* executor_logic.c */
void				execute_and_cmd(t_and_cmd *cmd, t_shell *shell);
void				execute_or_cmd(t_or_cmd *cmd, t_shell *shell);
void				execute_seq_cmd(t_seq_cmd *cmd, t_shell *shell);

/* executor2.c */
void				execute_pipe_cmd(t_pipe_cmd *cmd, t_shell *shell);
void				execute_forked_command(t_exec_cmd *ecmd, t_list *redir_list,
						t_shell *shell);
int					handle_heredoc(t_redir_cmd *cmd);
void				ft_split_free(char **split_array);

/* executor_utils.c */
char				*find_command_path(const char *cmd, t_shell *shell);
char				**env_list_to_array(t_list *env_list);
char				*get_env_value(t_list *env_list, const char *key);
t_env				*get_env_by_key(t_list *env_list, const char *key);

/* executor_utils2.c */
void				handle_command_not_found(char *cmd);
void				handle_directory_error(char *path);
int					handle_single_redirection(t_redir_cmd *redir,
						t_shell *shell);

/* executor_utils3.c */
int					is_builtin(const char *name);
int					is_parent_builtin(const char *name);
int					dispatch_builtin(t_exec_cmd *cmd, t_shell *shell);

/* executor_utils4.c */
void				execute_parent_builtin(t_exec_cmd *ecmd, t_list *redir_list,
						t_shell *shell);
void				prepare_and_exec_command(t_exec_cmd *cmd, t_shell *shell);

/* builtins */
int					ft_echo(char **args);
int					ft_cd(char **args, t_shell *shell);
int					ft_pwd(void);
int					ft_export(char **args, t_shell *shell);
int					ft_unset(char **args, t_shell *shell);
int					ft_env(t_shell *shell);
void				ft_exit(char **args, t_shell *shell);

/* cd_utils.c */
char				*get_cd_path(char **args, t_shell *shell);
int					do_chdir(char *path, t_shell *shell);

/* export_utils.c */
void				print_sorted_env(t_shell *shell);

/* exit_utils.c */
int					is_numeric(const char *s);
void				handle_numeric_arg_required(char *arg);
void				handle_too_many_args(t_shell *shell);

/* expander.c */
void				expand_command_args(t_exec_cmd *cmd, t_shell *shell);
char				*perform_expansion(const char *str, t_shell *shell);

/* expander_split.c */
char				**ft_lst_to_array(t_list *lst);
void				add_token_to_list(t_list **list, char *token);
char				*handle_tilde_expansion(char *arg, t_shell *shell);
int					is_quoted(char *str);
t_list				*split_string_to_list(char *expanded_str);

/* expander_utils.c */
int					is_special_char(char c);
char				*get_var_name(char *str);
char				*get_env_value_by_name(char *name, t_shell *shell);
void				append_str(char **s1, char *s2);

#endif
