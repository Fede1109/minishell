/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcervill <pcervill@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:22:04 by pcervill          #+#    #+#             */
/*   Updated: 2024/02/28 11:16:23 by pcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_string_info	t_info;
typedef struct s_token			t_token;
typedef struct s_tools			t_tools;

	/*		Executor.c		*/
int	before_execution(t_tools *tools);

#endif