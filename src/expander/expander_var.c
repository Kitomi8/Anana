// Fonction pour récupérer la valeur de la variable ou gérer $?
static char	*get_var_value(char *var_name, t_env *env)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
	{
		// Idéalement, utilisez une variable globale ou stockée pour le dernier exit status
		return (ft_itoa(g_signal)); 
	}
	value = get_env_value(env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

// Extrait le nom de la variable (ex: "USER" dans "$USER")
static char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++; // Skip '$'
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

// Fonction principale qui parcourt la chaîne et remplace les $VAR
static char	*expand_string(char *str, t_env *env)
{
	char	*new_str;
	char	*tmp;
	char	*var_name;
	char	*var_value;
	int		i;
	int		start;
	int		in_s_quote; // Dans simple quote ' '

	new_str = ft_strdup("");
	i = 0;
	in_s_quote = 0;
	while (str[i])
	{
		// Gestion des états de quotes (on ne touche pas aux variables dans '')
		if (str[i] == '\'')
			in_s_quote = !in_s_quote;
		else if (str[i] == '\"' && !in_s_quote)
			; // On est dans des double quotes, l'expansion est permise

		// Détection d'une variable valide
		if (str[i] == '$' && !in_s_quote && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			var_name = extract_var_name(str, &i);
			var_value = get_var_value(var_name, env);
			tmp = ft_strjoin(new_str, var_value);
			free(new_str);
			free(var_name);
			free(var_value);
			new_str = tmp;
			continue ; // On a déjà avancé i dans extract_var_name
		}
		
		// Ajout caractère par caractère si ce n'est pas une variable
		char c[2] = {str[i], 0};
		tmp = ft_strjoin(new_str, c);
		free(new_str);
		new_str = tmp;
		i++;
	}
	return (new_str);
}

// Votre fonction existante pour retirer les quotes (inchangée mais nécessaire)
char	*remove_quotes(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"'))
	{
		new_str = ft_substr(str, 1, len - 2);
		free(str);
		return (new_str);
	}
	return (str);
}

// La fonction appelée par le main
void	ft_expand(t_token *token_list, t_env *env)
{
	t_token	*curr;
	char	*expanded;

	curr = token_list;
	while (curr)
	{
		if (curr->type == WORD)
		{
			// 1. D'abord on expand les variables (ex: "$USER" -> "rtoky-fa")
			expanded = expand_string(curr->content, env);
			free(curr->content);
			
			// 2. Ensuite on retire les quotes (ex: "rtoky-fa" -> rtoky-fa)
			curr->content = remove_quotes(expanded);
		}
		curr = curr->next;
	}
}