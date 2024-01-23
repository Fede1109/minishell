/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcervill <pcervill@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:02:28 by pcervill          #+#    #+#             */
/*   Updated: 2024/01/23 12:08:14 by pcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(t_tools *tools)
{
	count_pipes(tools->lexer, tools);
	printf("Number of pipes: %d\n", tools->pipes);
	while (tools->lexer)
	{
		if (tools->lexer && tools->lexer->type == PIPE)
			ft_lexerdelone(&tools->lexer, tools->lexer->i);
		tools->lexer = tools->lexer->next;
	}
}
