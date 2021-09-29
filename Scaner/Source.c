#include <stdio.h>
#include "lexemes.h"
#include "Constant.h"
#include "Macros.h"
#include "string.h"




int main(int argc, char* argv[]) {

	char keyword[20][CounLexem] = { "class", "public", "boolean", "double", "for", "true", "false"};
	int keyword_lexem[CounLexem] = { t_class, t_am_public, t_bool, t_double, t_double, t_bool_true, t_bool_false};
	
	char buffer = 0;
	char* start_identificator;

	char program_text[MaxProgramSize] = {0};
	char translate_result[MaxProgramSize] = {0};

	char* cur_point_in_text = &program_text;
	char* cur_point_in_result = &translate_result;

	char file_not_end;
	
	FILE* program_file;
	FILE* scanered_file;

	if (argc <= 3) {
		printf_s("pleace input filenames");
		return 1;
	}

	int a = fopen_s(&program_file, argv[1], "r");
	fopen_s(&program_file, argv[1], "r");
	if (program_file != 0){
		fread(program_text, 1, MaxProgramSize, program_file);
		fclose(program_file);
	}
	else {
		printf_s("not_faund %s", argv[1]);
		return 1;
	}



	file_not_end = 1;

	while (file_not_end) {
		forget_letter(cur_point_in_text, is_ignore(*cur_point_in_text), is_ignore(*cur_point_in_text))
		else
		forget_letter(cur_point_in_text, *cur_point_in_text == '/' && *(cur_point_in_text + 1) == '/', *cur_point_in_text != '\n' && *cur_point_in_text != '\0')
		else
		not_limit_translation(cur_point_in_text, cur_point_in_result, is_number(*cur_point_in_text), is_number(*cur_point_in_text), t_number)
		else
		keyword_translation(
			cur_point_in_text,
			cur_point_in_result,
			&buffer,
			start_identificator,
			is_latter(*cur_point_in_text),
			is_latter(*cur_point_in_text) || is_number(*cur_point_in_text),
			t_identificator,
			keyword,
			keyword_lexem,
			CounLexem
			)
		else{
			switch (*cur_point_in_text) {
				simple_switch_translation(cur_point_in_result, '+', t_plus)
				simple_switch_translation(cur_point_in_result, '-', t_minus)
				simple_switch_translation(cur_point_in_result, '*', t_asterix)
				simple_switch_translation(cur_point_in_result, '/', t_fraction)
				simple_switch_translation(cur_point_in_result, '%', t_mod)
				simple_switch_translation(cur_point_in_result, '~', t_plus)
				simple_switch_translation(cur_point_in_result, '(', t_left_prnt)
				simple_switch_translation(cur_point_in_result, ')', t_right_prnt)
				simple_switch_translation(cur_point_in_result, '{', t_left_brack)
				simple_switch_translation(cur_point_in_result, '}', t_right_brack)
				simple_switch_translation(cur_point_in_result, '.', t_dot)
				simple_switch_translation(cur_point_in_result, ',', t_com)
				simple_switch_translation(cur_point_in_result, ';', t_semicolon)
				fork_switch_translation(cur_point_in_text, cur_point_in_result, '=', t_assign, '=', t_equal)
				fork_switch_translation(cur_point_in_text, cur_point_in_result, '<', t_less, '=', t_less_equal)
				fork_switch_translation(cur_point_in_text, cur_point_in_result, '!', t_not, '=', t_not_equal)
				fork_switch_translation(cur_point_in_text, cur_point_in_result, '>', t_more, '=', t_more_equal)
				switch_endl(cur_point_in_result, t_end, file_not_end)
				switch_error(cur_point_in_result,t_error)
		}
		cur_point_in_text++;
	}

	fopen_s(&scanered_file, argv[2], "w");
	if (scanered_file != NULL) {
		fputs(translate_result, scanered_file);
		fclose(scanered_file);
	}
	else {
		printf_s("error on write file %s", argv[2]);
		return 1;
	}

	if (argc > 3)
		for(char* ponter = &translate_result; *ponter != '\0'; ponter++)
			printf_s("%d ", *ponter);
}