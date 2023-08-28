#include "minishell.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	index;

// 	index = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[index] == s2[index] && s1[index] != '\0' && index < n - 1)
// 		index++;
// 	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
// }

int	ft_isspace(int c) 
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

// char	*ft_strdup(char*s1)
// {
// 	int		i;
// 	char	*s2;

// 	i = 0;
// 	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
// 	if (!s2)
// 		return (0);
// 	while (s1[i] != '\0')
// 	{
// 		s2[i] = s1[i];
// 		i++;
// 	}
// 	s2[i] = '\0';
// 	return (s2);
// }

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		i2;
// 	char	*dest;

// 	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!dest)
// 		return (0);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	i2 = 0;
// 	while (s2[i2] != '\0')
// 	{
// 		dest[i] = s2[i2];
// 		i++;
// 		i2++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

void	free_str_array(char **str_array)
{
	int	index;

	index = 0;
	while (str_array[index] != NULL)
	{
		free(str_array[index]);
		index++;
	}
	free(str_array);
}

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	if ((unsigned int)ft_strlen(s) <= start || !s)
// 		return (ft_strdup(""));
// 	if (start + len < (unsigned int)ft_strlen(s))
// 		result = (char *)malloc(sizeof(char) * (len + 2));
// 	else
// 		result = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 2));
// 	if (!result)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (i >= start && j < len)
// 		{
// 			result[j] = s[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	result[j] = 0;
// 	return (result);
// }

void ft_error(char *msg)
{
	printf("Error : %s\n", msg);
	//exit(1);
}


//check if i am inside a quote or not (update statue of quote)
enum token	quote_status(enum token quote, char character)
{
	if (quote == QUOTE && character == QUOTE)
		quote = IS_NULL;
	else if (quote == DOUBLE_QUOTE && character == DOUBLE_QUOTE)
		quote = IS_NULL;
	else if (quote == IS_NULL && character == QUOTE)
		quote = QUOTE;
	else if (quote == IS_NULL && character == DOUBLE_QUOTE)
		quote = DOUBLE_QUOTE;
	return (quote);
}

//remove the quote from string
char	*remove_quote(char *text)
{
	char	*final;
	int		i;
	int		j;

	final = (char *)malloc(sizeof(char) * (ft_strlen(text) + 100));
	if (!final)
		return (NULL);
	i = 1;
	j = 0;
	while (text[i] != '\0')
	{
		final[j] = text[i];
		i++;
		j++;
	}
	final[j - 1] = '\0';
	free(text);
	return (final);
}