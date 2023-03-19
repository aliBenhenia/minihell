#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int count(char *line)
{
    int i;
    int j;
    int c;

    i = 0;
    j = ft_strlen(line) - 1;
    c = 0;
    while (line[i] && line[i] == 32)
        i++;
    while (line[j] && line[j] == 32)
    {
        j--;
        c++;
    }
    return (c + i);
}

int all_spaces(char *line, int i)
{
    while (line[i])
    {
        if (line[i] != 32)
            return (0);
        i++;
    }
    return (1);
}

char    *skip_wspaces(char *line)
{
    int     i;
    int     j;
    char    *new;
    
    i = 0;
    j = 0;
	if (!line)
		return (NULL);
    new = malloc(ft_strlen(line) - count(line) + 1);
    while (line[i] && line[i] == 32)
        i++;
    while (line[i] && !all_spaces(line, i))
        new[j++] = line[i++];
    free(line);
    new[j] = '\0';
    return (new);
}

int	inside_quotes(char *line, int i)
{
	int	tmp;
	int	found;

	tmp = i;
	while (tmp >= 0)
	{
		if (line[tmp] != 34 && line[tmp] != 39)
			tmp--;
		else if(line[tmp] == 34 || line[tmp] == 39)
		{
			found = 1;
			break ;
		}
	}
	while (line[i] && found == 1)
	{
		if (line[i] != 34 && line[i] != 39)
			i++;
		else
			return (1);
	}
	return (0);
}

char	*ft_strchr(char *str, int c)
{
	int		i;
	char	*ptr;

	if (c == '\0')
		return ((char *)str + ft_strlen(str));
	ptr = (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			ptr = (char *) str + i;
		i++;
	}
	return (ptr);
}

t_token_list *new_token(char *value, int type)
{
    t_token_list    *new;

    new = malloc(sizeof(t_token_list));
    new->type = type;
    new->value = value;
    new->next = NULL;
    return (new);
}

void    addback(t_token_list **tokens, char *value, int type)
{
    t_token_list    *curr;

    curr = *tokens;
    if (!*tokens)
        *tokens = new_token(value, type);
    else
    {
        while (curr->next)
            curr = curr->next;
        curr->next = new_token(value, type);
    }
}