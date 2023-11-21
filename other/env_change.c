/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:10:51 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_substring(char *line, int start, int end)
{
	int		length;
	char	*result;

	length = end - start;
	result = malloc(length + 1);
	if (result == NULL)
		ft_error("Malloc error", 1);
	result[0] = '\0';
	if (start >= end || start < 0 || end > ft_strlen(line))
		return (result);
	ft_strlcpy(result, &line[start], length + 1);
	result[length] = '\0';
	return (result);
}

char	*get_env_value(char *key, char **envp, int exit_code)
{
	int		len;
	char	**env_iter;

	if (!key)
		return (ft_strdup(""));
	if (key[0] == '?')
		return (get_env_value2(key, exit_code));
	len = ft_strlen(key);
	env_iter = envp;
	while (*env_iter != NULL)
	{
		if (ft_strncmp(*env_iter, key, len) == 0 && (*env_iter)[len] == '=')
			return (ft_strdup(&(*env_iter)[len + 1]));
		env_iter++;
	}
	return (ft_strdup(""));
}

char	*replace_var(char *str, int start, char **envp, int exit_code)
{
	char	*value_var;
	char	*name_var;

	name_var = copy_substring(str, start + 1, start + length_var(str, start));
	if (name_var[0] == '\0')
	{
		free(name_var);
		return (ft_strdup("$"));
	}
	value_var = get_env_value(name_var, envp, exit_code);
	free(name_var);
	return (value_var);
}

char	*replace_var_relatif(char *str, int start, char **envp, int exit_code)
{
	char	*value_var;
	char	*name_var;

	(void)str;
	(void)start;
	name_var = ft_strdup("HOME");
	value_var = get_env_value(name_var, envp, exit_code);
	free(name_var);
	return (value_var);
}

char	*replace_var_in_str_new(char *str, char **envp, int exit_code, int i)
{
	int		ir;
	char	*new_str;
	char	*env_changed;

	ir = 0;
	new_str = setup_malloc(str);
	while (str[i] != '\0')
	{
		if ((str[i] == '$' && str[i + 1] != '\0') && str[0] != QUOTE)
		{
			env_changed = replace_var(str, i, envp, exit_code);
			new_str = replace3(&ir, &i, new_str, env_changed);
			i += length_var(str, i);
		}
		else if ((str[i] == '~' && str[i + 1] != '\0')
			&& (str[0] != QUOTE && str[0] != DOUBLE_QUOTE))
		{
			env_changed = replace_var_relatif(str, i, envp, exit_code);
			new_str = replace2(&i, &ir, new_str, env_changed);
		}
		else
			replace_var_in_str_new2(&i, &ir, new_str, str);
	}
	new_str[ir] = '\0';
	return (new_str);
}
