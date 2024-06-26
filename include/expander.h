/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:23:21 by pcervill          #+#    #+#             */
/*   Updated: 2024/04/22 14:57:36 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_string_info	t_info;
typedef struct s_token			t_token;
typedef struct s_tools			t_tools;
typedef struct s_token			t_token;
typedef struct s_simple_cmds	t_simple_cmds;

/* EXPANDER.C */
char			*check_env(char *str, char **env, int *i);
char			*detect_dollar_sign(char *str, char **env, int g_error);
char			**expander(char **str, t_tools *tools);
char			*expander_str(char *str, t_tools *tools);
t_simple_cmds	*check_expander(t_tools *tools, t_simple_cmds *cmd);

/* EXPANDER_UTILS.C */
int				ft_strlenmod(char *str, int start);
int				dollar_sign(char *str);
int				cmp_quotes(char str, int flag);
char			*delete_quotes(char *str, int single_q, int double_q);

/* EXPANDER_UTILS_2.C */
char			**empty_str(char **str);
char			*check_dolar(char *str, char **env, int *i, int g_error);
int				dollar_in_quotes(char *str, int *i, char flag);

#endif