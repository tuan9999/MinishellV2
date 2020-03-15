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

/*
** displays the prompt as set in the defines:
** - PROMPT_STRING
** - PROMPT_HOME_STRING
**
** if the environment variable HOME is set,
** PROMPT_HOME_STRING is used to display the prompt with printf,
** where the second argument passed to printf is the path of the working
**  directory, for the part that does not match the value of the HOME variable.
** however, if nothing matched the value of environment variable HOME,
** PROMPT_STRING is instead used to display the prompt.
** if the environment variable HOME is not set,
** it will use PROMPT_STRING to display the prompt.
**
** tl;dr:
** if HOME is set to /bruh, and the defines are set as follows:
** - # define PROMPT_STRING "%s"
** - # define PROMPT_HOME_STRING "~%s"
** then:
** if the working directory is /bruh/hello
**  ft_printf("~%s", "/hello") is called.
** if working directory is /hello/world
**  ft_printf("%s", "/hello/world") is called.
** if HOME is unset, and the working directory is /bruh/hello
**  ft_printf("%s", "/bruh/hello") is called.
*/

int		display_prompt(t_table *env)
{
	char	*current_directory;
	char	*home;

	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		ft_perror("unable to get working directory");
		return (DISPLAY_PROMPT_CWD_FAIL);
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
	return (DISPLAY_PROMPT_SUCCESS);
}
