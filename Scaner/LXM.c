#include "LXM.h"
#include "lexemes.h"
#include "string.h"
#include "Constant.h"


#define is_number(letter) '0' <= letter && letter <= '9'

#define is_latter(letter) 'a' <= letter && letter <= 'z' || 'A' <= letter && letter <= 'Z' || letter == '_'|| letter == '$'

#define is_ignore(letter) letter == ' ' || letter == '\n' || letter == '\t' || letter == '\r'

#define skip_signs(cursore, condition) for (; condition; cursore++);

#define case_and_reurn_lexem(lexem) case lexem: return #lexem;

#define case_and_translate(cursore, end_lexem,cell, sign,  lexem) \
		case sign:\
			cell = lexem;\
			end_lexem = cursore + 1;\
			break;\

#define case_end_chouse_translate(cursore, end_lexem, cell, sign_first, lexem_first, sign_second, lexem_second)\
	case sign_first:\
		if(*(cursore + 1) == sign_second){\
			cell = lexem_second ;\
			end_lexem = cursore + 2;\
		}else{\
			cell = lexem_first;\
			end_lexem = cursore + 1;\
		}\
		break;


char keywords[MAX_SIZ_LEXEM][COUNT_KEYWORD] = { "class", "public", "boolean", "double", "for", "true", "false" };
int keywords_lexem[COUNT_KEYWORD] = { t_class, t_am_public, t_bool, t_double, t_double, t_bool_true, t_bool_false };


char* skip_ignorable_signs(char* cursore)
{
	char* start = cursore;
	do{
		start = cursore;
		skip_signs(cursore, is_ignore(*cursore));
		if (*cursore == '/' && *(cursore + 1) == '/')
			skip_signs(cursore, *cursore != '\n' && *cursore != '\0');
	} while(start != cursore);
	return cursore;
}

char numeric_lexem(char* cursore, OUT char** end_lexem) {
	*end_lexem = cursore;
	skip_signs((*end_lexem), is_number(**end_lexem));
	return t_number;
}

char named_lexem(char* cursore, OUT char** end_lexem) {
	*end_lexem = cursore;
	skip_signs((*end_lexem), is_number(**end_lexem) || is_latter(**end_lexem));
	char bufer = **end_lexem;
	**end_lexem = '\0';

	for (int i = 0; i < COUNT_KEYWORD; i++) {
		if (strcmp(cursore, keywords[i]) == 0) {
			**end_lexem = bufer;
			return keywords_lexem[i];
		}
	}
	**end_lexem = bufer;
	return t_identificator;
}

int get_file_lxms(char* start, OUT LXM* lexem_array) {
	LXM* start_lxm_array = lexem_array;
	char* cursore = start;
	*lexem_array = get_lxm(start, &cursore);
	while ((*lexem_array).type_lexam != t_end)
	{
		lexem_array++;
		*lexem_array = get_lxm(start, &cursore);
	}
	return lexem_array - start_lxm_array;
}

void get_string_and_column(char* program, LXM lxm, OUT int* column, OUT int* string)
{
	*column = 0;
	*string = 0;
	for (int i = 0; i < lxm.start_move; i++) {
		*column += 1;
		if (program[i] == '\n') {
			*string += 1;
			*column = 0;
		}
	}
}

void get_text_lxms(char* string, OUT char* buffer, LXM lxm)
{
	char buffer_char = string[lxm.end_move];
	string[lxm.end_move] = '\0';
	strcpy_s(buffer, MAX_SIZ_LEXEM, string + lxm.start_move);
	string[lxm.end_move] = buffer_char;
}

char* get_lexem_name(unsigned char lexem_type)
{
	switch (lexem_type)
	{
		case_and_reurn_lexem(t_identificator)
		case_and_reurn_lexem(t_number)
		case_and_reurn_lexem(t_class)
		case_and_reurn_lexem(t_am_public)
		case_and_reurn_lexem(t_void)
		case_and_reurn_lexem(t_bool)
		case_and_reurn_lexem(t_double)
		case_and_reurn_lexem(t_for)
		case_and_reurn_lexem(t_bool_true)
		case_and_reurn_lexem(t_bool_false)
		case_and_reurn_lexem(t_assign)
		case_and_reurn_lexem(t_equal)
		case_and_reurn_lexem(t_less_equal)
		case_and_reurn_lexem(t_more_equal)
		case_and_reurn_lexem(t_not_equal)
		case_and_reurn_lexem(t_less)
		case_and_reurn_lexem(t_more)
		case_and_reurn_lexem(t_plus)
		case_and_reurn_lexem(t_minus)
		case_and_reurn_lexem(t_asterix)
		case_and_reurn_lexem(t_fraction)
		case_and_reurn_lexem(t_mod)
		case_and_reurn_lexem(t_not)
		case_and_reurn_lexem(t_binar_not)
		case_and_reurn_lexem(t_left_prnt)
		case_and_reurn_lexem(t_right_prnt)
		case_and_reurn_lexem(t_left_brack)
		case_and_reurn_lexem(t_right_brack)
		case_and_reurn_lexem(t_dot)
		case_and_reurn_lexem(t_com)
		case_and_reurn_lexem(t_semicolon)
		case_and_reurn_lexem(t_end)
		case_and_reurn_lexem(t_error)
	}
}

LXM get_lxm(char* start, char** cursore) {
	char *end = 0;
	LXM lxm;

	*cursore = skip_ignorable_signs(*cursore);

	if (is_number(**cursore)) {
		lxm.type_lexam = numeric_lexem(*cursore, &end);
	}
	else if (is_latter(**cursore)) {
		lxm.type_lexam = named_lexem(*cursore, &end);
	}
	else {
		switch (**cursore)
		{
		case_and_translate((*cursore), end, lxm.type_lexam, '+', t_plus)
		case_and_translate((*cursore), end, lxm.type_lexam, '-', t_minus)
		case_and_translate((*cursore), end, lxm.type_lexam, '*', t_asterix)
		case_and_translate((*cursore), end, lxm.type_lexam, '/', t_fraction)
		case_and_translate((*cursore), end, lxm.type_lexam, '%', t_mod)
		case_and_translate((*cursore), end, lxm.type_lexam, '~', t_binar_not)
		case_and_translate((*cursore), end, lxm.type_lexam, '(', t_left_prnt)
		case_and_translate((*cursore), end, lxm.type_lexam, ')', t_right_prnt)
		case_and_translate((*cursore), end, lxm.type_lexam, '{', t_left_brack)
		case_and_translate((*cursore), end, lxm.type_lexam, '}', t_right_brack)
		case_and_translate((*cursore), end, lxm.type_lexam, '.', t_dot)
		case_and_translate((*cursore), end, lxm.type_lexam, ',', t_com)
		case_and_translate((*cursore), end, lxm.type_lexam, ';', t_semicolon)
		case_and_translate((*cursore), end, lxm.type_lexam, '\0', t_end)
		case_end_chouse_translate((*cursore), end, lxm.type_lexam, '=', t_assign, '=', t_equal)
		case_end_chouse_translate((*cursore), end, lxm.type_lexam, '<', t_less, '=', t_less_equal)
		case_end_chouse_translate((*cursore), end, lxm.type_lexam, '!', t_not, '=', t_not_equal)
		case_end_chouse_translate((*cursore), end, lxm.type_lexam, '>', t_more, '=', t_more_equal)
		default:
			lxm.type_lexam = t_error;
			end = *cursore + 1;
			break;
		}
	}
	if (end - *cursore > MAX_SIZ_LEXEM) {
		lxm.type_lexam = t_error;
	}


	lxm.start_move = *cursore - start;
	lxm.end_move = end - start;
	*cursore = end;
	return lxm;
}

