/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:05:58 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/23 07:30:14 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <table.h>

int		is_builtin(const char *name);
int		run_builtin(
		t_vector *args,
		t_vector *pipe_stack,
		const int pipes[2],
		t_table *env);

/*
** BUILTINS
*/

int		echo_main(
		int argc,
		char **argv);
int		exit_main(
		int argc,
		char **argv);
int		cd_main(
		int argc,
		char **argv);
int		pwd_main(
		int argc,
		char **argv);
int		env_main(
		int argc,
		char **argv,
		t_table *env);

#endif
