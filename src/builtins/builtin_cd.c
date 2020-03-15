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

#include <unistd.h>
#include <ministd.h>
#include <libft.h>
#include <table.h>
#include <stdlib.h>

static void	set_oldpwd(t_table *env)
{
	char	*oldpwd[2];

	oldpwd[0] = ft_strdup("OLDPWD");
	oldpwd[1] = getcwd(NULL, 0);
	if (oldpwd[0] == NULL || oldpwd[1] == NULL)
	{
		free(oldpwd[0]);
		free(oldpwd[1]);
	}
	(void)table_insert(env, oldpwd[0], oldpwd[1]);
}

int			cd_main(
		int argc,
		char **argv,
		t_table *env)
{
	char	*dir;

	dir = argc > 1 ? argv[1] : NULL;
	if (argc == 1)
		dir = table_get(env, "HOME");
	else if (argc == 2 && ft_strncmp(argv[1], "-", 2) == 0)
	{
		dir = table_get(env, "OLDPWD");
		if (dir == NULL)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (1);
		}
	}
	set_oldpwd(env);
	if (dir != NULL && chdir(dir) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_perror(dir);
		return (1);
	}
	return (0);
}
