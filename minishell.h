#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>


#define SPACE 0
#define APPEND 1
#define HEREDOC 2
#define RIGHTRED 3
#define LEFTRED 4
#define DOLLAR 5
#define PIPE 6
#define S_QUOTE 7
#define D_QUOTE 8
#define WORD 9

typedef struct line
{
    char        *value;
    int         type;
    struct line *next;
}t_token_list;

int     ft_strcmp(char *s1, char *s2);
int     ft_strlen(char *str);
int		count(char *line);
int		inside_quotes(char *line, int i);
int     all_spaces(char *line, int i);
int     inside_quotes(char *line, int i);
char    *handle_quotes(char *line);
char    *check_redirections(char *line);
char    *check_pipe(char *line);
char    *skip_wspaces(char *line);
char *remove_additional_spaces(char *line);
char	*ft_strchr(char *str, int c);
void    addback(t_token_list **tokens, char *value, int type);


#endif