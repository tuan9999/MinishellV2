/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpattij <dpattij@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:26:13 by dpattij           #+#    #+#             */
/*   Updated: 2020/01/23 05:37:21 by dpattij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <vector.h>

typedef struct	s_table_entry
{
	char		*key;
	char		*value;
}				t_table_entry;

# define ULL_MAX -1UL

typedef t_vector	t_table;

t_bool			table_new(t_table *self);
char			*table_get(t_table *self, char *key);
t_table_entry	*table_get_entry(t_table *self, char *key);
t_bool			table_insert(t_table *self, char *key, char *value);
void			table_destroy(t_table *self);

#endif
