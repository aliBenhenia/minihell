/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/19 17:30:43 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_redirections(t_token_list **tokens, char *line)
{
    if (*line == '>')
    {	
        if (*(line + 1) == '>')
        {
            addback(tokens, ">>", APPEND);
            return (line + 2);
        }
        addback(tokens, ">", RIGHTRED);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            addback(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        addback(tokens, "<", LEFTRED);
    }
	return (line + 1);
}

char    *is_wspace(t_token_list **tokens, char *line)
{
    int i;
    i = 0;
    while (ft_strchr(" \t\v\f\r", line[i]) && line[i])
        i++;
    addback(tokens, " ", SPACE);
    return (line + i);
}

char    *is_dollar_pipe(t_token_list **tokens, char *line)
{
    if(*line == '$')
    {
        addback(tokens,"$", DOLLAR);
            return (line + 1);
    }
    else if(*line == '|')
    {
        addback(tokens,"|", PIPE);
            return (line + 1);
    }
	return(0);
}

char    *is_word(t_token_list **tokens, char *line)
{
    int		i;
    char    *word;

    i = 0;
    while (!ft_strchr(" \t\v\f\r><$|", line[i]))
        i++;
	word = malloc(i + 1);
	i = 0;
	while (!ft_strchr(" \t\v\f\r><$|", line[i]))
	{
		
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	addback(tokens, word, WORD);
	return (line + i);
}

t_token_list *tokenizer(char *line)
{
	t_token_list	*tokens;

	tokens = NULL;
    while (*line)
    {
        if (ft_strchr(" \t\v\f\r", *line))
            line = is_wspace(&tokens, line);
        else if (ft_strchr("><", *line))
            line = is_redirections(&tokens, line);
        else if (ft_strchr("$|", *line))
            line = is_dollar_pipe(&tokens, line);
        else
		{
            line = is_word(&tokens, line);
			
		}
    }
	return(tokens);
}

char    *prompt(void)
{
    char	*line;

	line = readline("\x1B[36m""minishell$ ""\001\e[0m\002");
	add_history(line);
	line = remove_additional_spaces(line);
    return (line);
}

int main()
{
    char	*line;
	t_token_list	*token;

    while (1)
    {
		line = prompt();
		token = tokenizer(line);
		while (token)
		{
			printf("%s|\n", token->value);
			token = token->next;
		}
    }
}