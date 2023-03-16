/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:29:19 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/03/16 15:30:47 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

#include "util/util.h"

static size_t	delim(const char *s)
{
	if (s[0] == '|' && s[1] == '|')
		return (2);
	if (s[0] == '&' && s[1] == '&')
		return (3);
	if (s[0] == '<' && s[1] == '<')
		return (4);
	if (s[0] == '>' && s[1] == '>')
		return (5);
	if (s[0] == '|')
		return (1);
	if (s[0] == '<' || s[0] == '>')
		return (6);
	return (0);
}

static size_t	nextcmd(char *line)
{
	size_t	i;

	i = 0;
	while (delim(line))
	{
		
	}
	return (i);
}

static size_t	nextcount(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && !whitespace(line[i]) && !delim(line + i))
		++i;
	return (i);
}

static void	counttypes(char *line, size_t *types)
{
	size_t	i;

	i = 0;
	while (*line)
	{
		while (whitespace(*line) || *line == '\'' || *line == '"')
			++line;
		if (!*line)
			break ;
		++types[gettype(line + i)];
		line += nextarg(line);
	}
}

static size_t	strcpyq(char *dst, const char *src)
{
	size_t	i;
	char	t;

	i = 0;
	while (src[i])
	{
		t = gettype(src);
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (i);
}

static char	*getfullcmd(char *line)
{
	char	*com;
	size_t	i;
	size_t	l;

	while (*(line) && whitespace(line[i]))
		++line ;
	l = nextarg(line);
	i = -1;
	return (com);
}

void	sortcmd(t_cmd *cmd, char *line, size_t *c)
{
	size_t	t;

	t = delim(line);
	if (t > 0 && t <= 2)
	{
		
	}
}

t_cmd	*buildcmd(char *line)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	c[3];

	cmd = malloc(sizeof(t_cmd));
	skipwhite(&line);
	while (*line)
	{
		i = nextarg(line);
		sortcmd(cmd, line, c);
		skipwhite(&line);
	}
	return (cmd);
}

void freecmd(t_cmd *cmd)
{
	if (cmd->next)
		freecmd(cmd->next);
	free(cmd);
}
