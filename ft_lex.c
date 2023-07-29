/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:14:27 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 15:35:24 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char *s, char **res, int *i)
{
	int	rest;

	rest = 0;
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
	{
		res[*i] = ft_substr(s, 0, 2);
		(*i)++;
		rest += 2;
	}
	else if (s[0] == '|' || s[0] == '<' || s[0] == '>')
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	else
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	return (rest);
}

static char	**split_args(char *s)
{
		int		i;
	int		len;
	char	**res;
    char    quote;
	int		special;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char *));
	i = 0;
	while (*s)
	{
		len = 0;
		while (s[len] && s[len] != '<' && s[len] != '>' && s[len] != '|')
        {
            if (is_quote(s[len]))
            {
                quote = s[len++];
                while (s[len] && s[len] != quote)
                    len++;
            }
			len++;
        }
		if (len > 0)
		{
			res[i++] = ft_substr(s, 0, len);
			s += len;
		}
		else
		{
			special = special_case(s, res, &i);
			s += special;
		}
	}
	return (res);
}

void	add_lex(char *str, t_list **lst)
{
	char    **arg;
    int     i;

    arg = NULL;
    arg = split_args(str);
    i = 0;
    while (arg[i])
        ft_add_back_token(lst, ft_new_token(arg[i++]));
    ft_free_str(arg);
}

t_list	*ft_lex(char **dst)
{
	t_list  *lst;
    int     i;

    lst = NULL;
    i = 0;
    while (dst[i])
    {
        if (ft_strchr(dst[i], '|') || ft_strchr(dst[i], '>')
            || ft_strchr(dst[i], '<'))
            add_lex(dst[i], &lst);
        else
            ft_add_back_token(&lst, ft_new_token(dst[i]));
        i++;
    }
    return (lst);
}
