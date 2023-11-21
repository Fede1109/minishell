/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcervill <pcervill@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:26:45 by pcervill          #+#    #+#             */
/*   Updated: 2023/11/21 11:16:05 by pcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	create_token(char *input, t_token *token)
{
	int	i;
	int	j;
	int	k;
	int	token_index;

	token->tokens = calloc(token->count + 1, sizeof(char *));
	i = 0;
	token_index = 0;
	while (input[i])
	{
		//token_operator(input, token, i, token_index);
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
		{
			token->tokens[token_index] = (char *)calloc(3, sizeof(char));
			token->tokens[token_index][0] = input[i];
			token->tokens[token_index][1] = input[i + 1];
			token_index++;
			i += 2;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			token->tokens[token_index] = (char *)calloc(2, sizeof(char));
			token->tokens[token_index][0] = input[i++];
			token_index++;
		}
		if (input[i] != '|' && input[i] != '<' && input[i] != '>')
		{
			j = i;
			k = 0;
			token->len = 0;
			while (input[i] && input[i] != '|'
				&& input[i] != '<' && input[i] != '>')
			{
				token->len++;
				i++;
			}
			token->tokens[token_index] = calloc((token->len + 1), sizeof(char));
			while (k < (token->len))
				token->tokens[token_index][k++] = input[j++];
			token_index++;
		}
	}
	return ;
}

void	ft_strlen_token(char *input, t_token *token)
{
	int	i;

	i = 0;
	token->count = 0;
	while (input[i])
	{
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
		{
			token->count++;
			i += 1;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			token->count++;
		else if ((input[i] != '|' && input[i] != '<' && input[i] != '>')
			&& (input[i + 1] == '|' || input[i + 1] == '<'
				|| input[i + 1] == '>' || !input[i + 1]))
			token->count++;
		i++;
	}
	return ;
}

int	lexer(char *input, t_token *token)
{
	ft_strlen_token(input, token);
	create_token(input, token);
	return (0);
}
