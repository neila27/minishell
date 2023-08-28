#include "minishell.h"

// take string line and split it into token in a list of word
t_word	*lexer(char *line)
{
	t_word	*start_word;
	t_word	*current_word;
	t_word	*previous_word;
	int		first;
	int		i;

	i = 0;
	first = 1;
	while (line[i])
	{
		//skip space
		while (ft_isspace(line[i]))
			i++;
		//if the line is over stop
		if (line[i] == '\0')
			break;
		
		//split into the var a word
		current_word = split_new_element(line, ' ', i);
		//add the length of the word return for skip it in the line
		i += ft_strlen(current_word->text);

		//special case if it is the first of the list
		if (first == 0)
		{
			previous_word->next = current_word;
			current_word->previous = previous_word;
		}
		else
			start_word = current_word;
		previous_word = current_word;
		first = 0;
	}

	//checking if token at the end and error
	if (current_word->token == DOUBLE_GREATER || current_word->token == DOUBLE_LESSER || current_word->token == GREATER || current_word->token == LESSER || current_word->token == PIPE)
		ft_error("bash: syntax error near unexpected token");
	//checking if token at the start and error
	if (start_word->token == PIPE)
		ft_error("bash: syntax error near unexpected token");

	current_word->next = NULL;
	current_word = start_word;
	//checking if more than one token in a row
	token_error(current_word);
	return (start_word);
}

t_word	*split_new_element(char *line, char c, int start)
{
	t_word	*result;
	int		end;
	enum 	token quote;

	//init my word to return
	result = (t_word *)malloc(sizeof(t_word));
	result->next = NULL;
	result->previous = NULL;
	quote = IS_NULL;
	end = start;
	
	if (is_special_char(line[start]))
	{
		//printf("ENTER SPECIAL quote : %c\n", quote);
		//if quote go while the end of the quote
		quote = quote_status(quote, line[end++]);
		while (quote != IS_NULL && line[end])
		{
			//printf("ENTER\n");
			quote = quote_status(quote, line[end++]);
		}
		
		//verify if it is double redirection
		if (line[start] == '>' && line[start + 1] == '>')
			end++;
		if (line[start] == '<' && line[start + 1] == '<')
		{
			end++;
			//HERE 
		}
	}
	else
	{
		//while it is not a token or a space continue
		while (line[end] != c && line[end] && is_special_char(line[end]) != 1)
			end++;
	}
	//cut the text from the start position to the end and get "word"
	result->text = ft_substr(line, start, end - start);
	//printf("%s\n", result->text);
	//set the word type of token (if nothing special will be OTHER) can return error if wrong token is detected
	result->token = setup_token(result->text);
	//return the result to my lexer
	return (result);
}

//check and return if the char send is a special char
int	is_special_char(char character)
{
	int	result;

	result = 0;
	if (character == '>' || character == '<' || character == '|'
		|| character == '\"' || character == '\'')
		result = 1;
	return (result);
}

//return the token value of the char* 
enum token setup_token(char *word)
{
	if (word[0] == '\'')
			return (QUOTE);
	if (word[0] == '\"')
			return (DOUBLE_QUOTE);
	if (word[0] == '>')
	{
		if (word[1] == '>' && word[2] == '\0')
			return (DOUBLE_GREATER);
		else if (word[1] == '\0')
			return (GREATER);
		else
			ft_error("bash: syntax error near unexpected token");
	}
	if (word[0] == '<')
	{
		if (word[1] == '<' &&  word[2] == '\0')
			return (DOUBLE_LESSER);
		else if (word[1] == '\0')
			return (LESSER);
		else
			ft_error("bash: syntax error near unexpected token");
	}
	if (word[0] == '|')
	{
		if (word[1] == '|')
			ft_error("bash: syntax error near unexpected token");
		return (PIPE);
	}
	return (OTHER);
}

//checking if more than one token in a row
int	token_error(t_word *current_word)
{
	int	repeat;

	repeat = 0;
	while (current_word != NULL)
	{
		if (current_word->token == GREATER || current_word->token == LESSER ||  current_word->token == PIPE )
			repeat++;
		else 
			repeat = 0;
		if (repeat == 2)
			ft_error("bash: syntax error near unexpected token");
		current_word = current_word->next;
	}
	return (1);
}

int number_of_pipe(t_word *word)
{	
	int	count;

	count = 2;
	while (word != NULL)
	{
		if (word->token == PIPE)
			count++;
		word = word->next;
	}
	return (count);
}

int number_of_parameter(t_word *word)
{	
	int count;

	count = 2;
	while (word->token != PIPE)
	{
		count++;
		word = word->next;
		if (!word)
			break;
	}
	return (count);
}
