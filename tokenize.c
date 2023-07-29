/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:06:41 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/22 14:12:45 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *copy_word(char *str, int *n)
{
    char    quote;
    int		i;
    int		len;
    int		y;

	y = *n;
    i = *n;
    len = 0;
    while (str[i] && str[i] != SPACE)
    {
        if (is_quote(str[i]))
        {
            len++;
            quote = str[i++];
            while (str[i] && str[i] != quote)
            {
                len++;
                i++;
            }
        }
        i++;
        len++;
    }
    *n += len;
    return (ft_substr(str, y, len));
}

char	**split_string(char *s, char c)
{
	char    **word;
    int     i;
    int     j;

    i = count_words(s, c);
    word = ft_calloc(i + 1, sizeof(char *));
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] != SPACE)
            word[j++] = copy_word(s, &i);
        else
            i++;
    }
	if (!j)
		return (NULL);
    word[j] = NULL;
    return (word);
}
