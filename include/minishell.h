/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:06:35 by pcervill          #+#    #+#             */
/*   Updated: 2024/02/13 17:31:49 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./lexer.h"
# include "./quotes.h"
# include "./parser.h"
# include "./clean.h"
# include "./borrar.h"
# include "./executor.h"
# include "./error.h"

# define NORMAL			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define LIGHT_RED		"\033[91m"
# define GREEN			"\033[32m"
# define LIGHT_GREEN	"\033[92m"
# define YELLOW			"\033[33m"
# define LIGHT_YELLOW	"\033[93m"
# define BLUE			"\033[34m"
# define LIGHT_BLUE		"\033[94m"
# define MAGENTA		"\033[35m"
# define LIGHT_MAGENTA	"\033[95m"
# define CYAN			"\033[36m"
# define LIGHT_CYAN		"\033[96m"
# define WHITE			"\033[37m"
# define GREY			"\033[90m"
# define LIGHT_GREY		"\033[37m"

# define BLACK_BOLD		"\033[1;30m"
# define RED_BOLD		"\033[1;31m"
# define GREEN_BOLD		"\033[1;32m"
# define YELLOW_BOLD	"\033[1;33m"
# define BLUE_BOLD		"\033[1;34m"
# define MAGENTA_BOLD	"\033[1;35m"
# define CYAN_BOLD		"\033[1;36m"
# define WHITE_BOLD		"\033[1;37m"

# define PROMPT_MSG "\033[1;36m$minishell/ \033[0m"

typedef struct s_string_info
{
	char	*s;
	size_t	*i;
	char	current_quote;
}	t_info;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	RREDIR,
	HERE_DOC,
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	int				i;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tools
{
	t_token					*lexer;
	struct s_simple_cmds	*parser;
	char					*arg;
	int						pipes;
	int						*pid;
	char					*pwd;
	char					**env;
	char					*old_pwd;
	char 					**exp;
}	t_tools;

typedef struct s_parser_tools
{
	t_token			*lexer;
	t_token			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_token					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

		/* minishell_loop.c */
void			init_tools(t_tools *tools);
void			minishell_loop(t_tools *tools);

		/* utils.c */
t_simple_cmds	*ft_mini_lstlast(t_simple_cmds *lst);
void			ft_mini_lstadd_back(t_simple_cmds **lst, t_simple_cmds *new);
t_simple_cmds	*ft_mini_lstnew(char **content);
char			**dup_matrix(char **str);
int				save_pwd(t_tools *tools);

		/*Built-ins*/
int				(*check_builtin(char *tokens))(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_cd(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_env(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_pwd(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_export(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_unset(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_exit(t_tools *tools, t_simple_cmds *simple_cmds);
int				ft_echo(t_tools *tools, t_simple_cmds *simple_cmds);

		/*Built-ins utils*/
int				check_if_nb(char *str);
void			ft_join_export(char **exp);
void			ft_replace_var(char **exp, char *var_name, char *var);
void			ft_update_var(char **exp, char **env ,char *var);
int				ft_is_sorted(char **str);
char			**ft_sort_export(char **str);
void			ft_print_export(char **copy);
char			**ft_update_export(char **exp, char **new_exp, char *var);
char			*ft_trim_quotes(char *str);
char			*ft_joinvar(char *str);

		/*	Signals	*/
void			init_signals();
void			rl_replace_line(const char *text, int clear_undo);

#endif
