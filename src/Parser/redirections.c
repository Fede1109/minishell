/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcervill <pcervill@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:01:32 by pcervill          #+#    #+#             */
/*   Updated: 2024/02/01 12:22:20 by pcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*token_new_cmd(char *str, int token, int i)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(str);
	new->type = token;
	new->i = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	new_redirection(t_token *tmp, t_parser_tools *parser_tools)
{
	t_token	*node;
	int		i;

	i = 0;
	node = token_new_cmd(tmp->next->token, tmp->type, i);
	if (!node)
		return ; // falta funcion error
	ft_add_token_last(&parser_tools->redirections, node);
	ft_lexerdelone(&parser_tools->lexer, tmp->i);
	ft_lexerdelone(&parser_tools->lexer, tmp->next->i);
	parser_tools->num_redirections++;
}

void	redirection_add(t_parser_tools *parser_tools)
{
	t_token	*tmp;

	tmp = parser_tools->lexer;
	while (tmp && tmp->type == WORD)
		tmp = tmp->next;
	if (!tmp || tmp->type == PIPE)
		return ;
	if (tmp->type >= REDIR_IN && tmp->type <= RREDIR)
		new_redirection(tmp, parser_tools);
	redirection_add(parser_tools);
}
