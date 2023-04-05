/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenvalidation3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:52 by francoma          #+#    #+#             */
/*   Updated: 2023/04/05 07:50:30 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "tokenvalidation.h"
#include "util/util.h"
#include "data.h"
#include "env.h"

int	is_redir(t_token *token)
{
	return (is_type(token, tdin | tdout | tapp | thdoc));
}

static int	is_delimpin(t_token *token)
{
	return (is_type(token, tpipe | tor | tand | tpin));
}

static void	print_token_error(t_token *t)
{
	if (!t)
		return ;
	while (t->type == tws)
		t++;
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (!t->type)
		write(2, "newline", 7);
	else
		write(2, t->val, t->len);
	write(2, "'\n", 2);
}

static t_token	*find_token_error(t_token *toks)
{
	size_t	i;
	int		open_p;

	open_p = 0;
	i = -1;
	while (toks[++i].type)
	{
		open_p += is_type(toks + i, tpin) - is_type(toks + i, tpout);
		if (open_p < 0)
			return (toks + i);
		if (is_delimpin(toks + i) && ((!i && !is_type(toks + i, tpin))
				|| (!next_to_word(toks + i) && !next_to_redir(toks + i)
					&& !next_to(toks + i, tpin))))
			return (toks + i + 1);
		else if (is_redir(toks + i) && !next_to_word(toks + i))
			return (toks + i + 1);
		else if (is_type(toks + i, tpout)
			&& (next_to_word(toks + i) || next_to(toks + i, tpin)))
			return (toks + i + 1);
		else if (is_word(toks + i) && next_to(toks + i, tpin))
			return (toks + i + 1);
	}
	if (open_p)
		return (toks + i);
	return (NULL);
}

int	token_error(t_token *toks)
{
	t_token	*t;

	t = find_token_error(toks);
	if (t)
	{
		print_token_error(t);
		update_env(&(getdata()->local_env), "?=258");
		return (1);
	}
	return (0);
}

// #include <stdio.h>
// void	test(char *line, int success)
// {
// 	if (token_error(tokenize(line)) == success)
// 		printf("Error: %s\n", line);
// }

// int main()
// {
// 	test("|| echo", 1);
// 	test("a|| >", 1);
// 	test("a|| >          e", 0);
// 	test("a||>e", 0);
// 	test("(e)", 0);
// 	test("((e)", 1);
// 	test("( ( ( )   (e)            ))", 1);
// 	test("( ( (   (e)            )))", 0);
// 	test("( ( (   (e)      |      )))", 1);
// 	// mot suivi de (
// 	test("echo (ok)", 1);
// 	test("echo ok (> o)", 1);
// 	// ) suivi de mot ou (
// 	test("(echo) ok > o", 1);
// 	test("(e)(a)", 1);
// 	test("echo ok > (o)", 1);
// 	test("(echo ok) > o", 0);
// 	test("(<o cat)", 0);
// 	test("e && ((e))", 0);
// 	test("e && (e)", 0);
// 	test("(e &&) (e)", 1);
// }
