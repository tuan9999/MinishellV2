/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tuperera <tuperera@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:26:22 by tuperera       #+#    #+#                */
/*   Updated: 2019/11/08 15:29:48 by tuperera      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static	int		getrow(char	const *s, char c)
{
	int		j;
	int		row;

	row = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] && s[j] == c)
			j++;
		while (s[j] != c && s[j])
			j++;
		row++;
	}
	if (s[j - 1] == c)
		row--;
	return (row);
}

static	int		getcol(char const *s, char c)
{
	int		col;

	col = 0;
	while (s[col] != c && s[col])
		col++;
	return (col);
}

static	void	*freearr(char **result, int count)
{
	while (count >= 0)
	{
		if (result[count])
			free(result[count]);
		count--;
	}
	if (result)
		free(result);
	return (NULL);
}

static	char	*addword(char *result, const char *s, char c)
{
	int		col;

	col = 0;
	while (s[col] != c && s[col])
	{
		result[col] = s[col];
		col++;
	}
	result[col] = '\0';
	return (result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		row;

	result = (!s) ? NULL : (char **)malloc(sizeof(char *) * (getrow(s, c) + 1));
	if (!result)
		return (NULL);
	row = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		result[row] = (char *)malloc(getcol(s, c) + 1);
		if (!result[row])
			return (freearr(result, row));
		result[row] = addword(result[row], s, c);
		while (*s != c && *s)
			s++;
		row++;
	}
	result[row] = NULL;
	return (result);
}
