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
#define AFDOLLAR 10

typedef struct line
{
    char        *value;
    int         type;
    struct line *next;
}t_token_list;

typedef struct tools
{
    int after_variable;
}t_tools;

// Tokenizer Utils
t_token_list *tokenizer(char *line);
char    *is_redirections(t_token_list **tokens, char *line);
char    *is_wspace(t_token_list **tokens, char *line);
char    *is_dollar_pipe(t_token_list **tokens, char *line);
char    *is_word(t_token_list **tokens, char *line);
char    *is_squote(t_token_list **tokens, char *line, int *open);
char	*is_dquote(t_token_list **tokens, char *line, int *open, t_tools *tools);
char	*afdollar(t_token_list **tokens, char *line, t_tools *tools);

// Syntax
void    syntax_red(t_token_list **tokens);
void    syntax_pipe(t_token_list **tokens);

int	ft_isalnum(int c);
int is_open_quote(char *line, char quote);
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
void	ft_lstclear(t_token_list	**lst);
void    addback(t_token_list **tokens, char *value, int type);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void free_node(t_token_list **tokens);
t_token_list *new_token(char *value, int type);
#endif