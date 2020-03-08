/* ************************************************************************** */
/*                                                                            */
/*   Project: memeshell420                                ::::::::            */
/*   Members: dpattij, tuperera                         :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_LOOP_H
# define RUNTIME_LOOP_H

# define PROMPT_STRING "\033[31;1m%s\033[0m > "
# define PROMPT_HOME_STRING "\033[31;1m~%s\033[0m > "

# include <table.h>

extern t_vector	g_running_processes;
extern char		**environ;

int				runtime_loop(t_table *env);
int				display_prompt(t_table *env);
int				read_char(char *out);
int				read_line(
				char **line,
				int eof_matters);
int				take_input(char **input);

#endif
