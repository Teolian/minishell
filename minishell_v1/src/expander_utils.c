/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npugach <npugach@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:05:00 by juwang            #+#    #+#             */
/*   Updated: 2025/09/03 15:29:31 by npugach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_char(char **s, char c)
{
	int		len;
	char	*new;

	len = 0;
	if (*s)
		len = ft_strlen(*s);
	new = malloc(len + 2);
	if (!new)
		return ;
	if (*s)
		ft_memcpy(new, *s, len);
	new[len] = c;
	new[len + 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

static int	get_var_len(const char *arg)
{
	int	len;

	len = 0;
	if (*arg == '?')
		return (1);
	if (ft_isalpha(*arg) || *arg == '_')
	{
		while (ft_isalnum(arg[len]) || arg[len] == '_')
			len++;
	}
	return (len);
}

static void	append_var_value(char *var_name, t_shell *shell, char **result)
{
	char	*value;

	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		value = ft_itoa(shell->exit_status);
		append_str(result, value);
		free(value);
	}
	else
	{
		value = get_env_value(shell->env_list, var_name);
		append_str(result, value);
	}
}

static void	handle_variable(t_expand_state *st, t_shell *shell)
{
	char	*var_name;
	int		len;

	st->arg++;
	if (*st->arg == '\0' || ft_strchr(" \t\n'\"", *st->arg))
	{
		append_char(&st->result, '$');
		st->arg--;
		return ;
	}
	len = get_var_len(st->arg);
	var_name = ft_substr(st->arg, 0, len);
	append_var_value(var_name, shell, &st->result);
	free(var_name);
	st->arg += len - 1;
}

char	*perform_expansion(const char *arg, t_shell *shell)
{
	t_expand_state	st;

	st.arg = arg;
	st.result = ft_calloc(1, sizeof(char));
	st.quote_state = 0;
	while (*st.arg)
	{
		if (st.quote_state == 0 && (*st.arg == '\'' || *st.arg == '"'))
			st.quote_state = *st.arg;
		else if (st.quote_state != 0 && *st.arg == st.quote_state)
			st.quote_state = 0;
		else if (*st.arg == '$' && st.quote_state != '\'')
			handle_variable(&st, shell);
		else
			append_char(&st.result, *st.arg);
		st.arg++;
	}
	return (st.result);
}
