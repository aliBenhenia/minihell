/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:01:28 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/20 17:20:04 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_token_list **tokens)
{
	write(1, "parse error\n", ft_strlen("parse error\n"));
	ft_lstclear(tokens);
}


void    syntax_red(t_token_list **tokens)
{
    t_token_list	*t_tokens;

	t_tokens = *tokens;
	if(t_tokens != NULL)
	{
		if ((t_tokens->value[0] == '>' || t_tokens->value[0] == '<') 
			&& !t_tokens->next ) // ila kan bo7do
		{
			print_error(tokens);
			return ;
		}
		while (t_tokens)
		{
			if ((t_tokens->value[ft_strlen(t_tokens->value - 1)] == '>'
				|| t_tokens->value[ft_strlen(t_tokens->value - 1)] == '<')
			&& !t_tokens->next) // ila kan f lakher
			{
				print_error(tokens);
				return ;
			}
			else if ((t_tokens->next) && (t_tokens->value[0] == '>' || t_tokens->value[0] == '<')
			&& t_tokens->next->value[0] == 32) // >> >
			{
				if (t_tokens->next->next->value[0] == '>' || t_tokens->next->next->value[0] == '<')
				{
					print_error(tokens);
					return ;
				}
				else if (t_tokens->next->next->value[0] == '|')
				{
					print_error(tokens);
					return ;
				}
			}
			else if(t_tokens->value[0] == '>' && t_tokens->value[1] == '>' 
				&& t_tokens->next->value[0] == '>' ) // >>>
			{
				print_error(tokens);
				return ;
			}
			else if(t_tokens->value[0] == '<' && t_tokens->value[1] == '<' 
				&& t_tokens->next->value[0] == '<' ) // >>>
			{
				print_error(tokens);
				return ;
			}
			else if ((t_tokens->value[0] == '>' && t_tokens->next->value[0] == '<') 
					|| (t_tokens->value[0] == '<' && t_tokens->next->value[0] == '>'))
			{
				print_error(tokens);
					return ;
			}
			t_tokens = t_tokens->next;
		}
	}
}

void    syntax_pipe(t_token_list **tokens)
{
	t_token_list	*t_tokens;
	
	t_tokens = *tokens;
	if (!*tokens)
		return ;
	if (t_tokens->value[0] == '|')
	{
		print_error(tokens);
		return ;
	}
	while(t_tokens)
	{
		if (t_tokens->value[0] == '|' && !t_tokens->next)
		{
			print_error(tokens);
			return ;
		}
		else if (t_tokens->value[0] == '|' && t_tokens->next->value[0] == '|')
		{
			print_error(tokens);
			return ;
		}
		else if (t_tokens->value[0] == '|' && t_tokens->next->value[0] == 32 
				&& t_tokens->next->next->value[0] == '|')
		{
			print_error(tokens);
			return ;		
		}
		t_tokens = t_tokens->next;
	}
}