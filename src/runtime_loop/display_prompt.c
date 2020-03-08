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

#include <ft_printf.h>
#include <libft.h>
#include <runtime_loop.h>
#include <unistd.h>
#include <stdlib.h>

int		display_prompt(t_table *env)
{
	char	*current_directory;
	char	*home;

	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		ft_perror("unable to get working directory");
		return (1);
	}
	home = table_get(env, "HOME");
	if (home != NULL)
	{
		if (ft_strncmp(current_directory, home, ft_strlen(home)) == 0)
			ft_printf(PROMPT_HOME_STRING, current_directory + ft_strlen(home));
		else
			ft_printf(PROMPT_STRING, current_directory);
	}
	else
		ft_printf(PROMPT_STRING, current_directory);
	free(current_directory);
	return (0);
}
