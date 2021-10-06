#include <stdio.h>
#include "Constant.h"
#include "LXM.h"

void listening(char* program_text, LXM* lexemes, int count_lexem, char* filename) {
	int a = 0;
	int b = 0;
	char out_text[MAX_SIZ_LEXEM] = { 0 };
	FILE* scanered_file;

	fopen_s(&scanered_file, filename, "w");
	if (scanered_file != NULL) {
		for (int i = 0; i < count_lexem; i++) {
			if (lexemes[i].end_move - lexemes[i].start_move > MAX_SIZ_LEXEM) {
				out_text[0] = 'o';
				out_text[1] = 0;
			}
			else {
				get_text_lxms(program_text, out_text, lexemes[i]);
			}
			get_string_and_column(program_text, lexemes[i], &a, &b);
			fprintf_s(scanered_file, "type: %30s |%30s | string: %4d | column: %4d |\n", get_lexem_name(lexemes[i].type_lexam), &out_text, b, a);
		}
		fclose(scanered_file);
	}
	else {
		printf_s("error on write file %s", filename);
	}
}

int main(int argc, char* argv[]) {


	char program_text[MAX_PROGRAMM_SIZE] = {0};


	FILE* program_file;
	FILE* scanered_file;

	if (argc < 2)
		return 1;

	fopen_s(&program_file, argv[1], "r");
	if (program_file != 0){
		fread(program_text, 1, MAX_PROGRAMM_SIZE, program_file);
		fclose(program_file);
	}
	else {
		printf_s("not_faund %s", argv[1]);
		return 1;
	}

	LXM lexemes[MAX_PROGRAMM_SIZE] = {0};
	int count_lexem = get_file_lxms(&program_text, &lexemes);


	fopen_s(&scanered_file, argv[2], "w");
	if (scanered_file != NULL) {
		fwrite((void*)lexemes, sizeof(LXM), count_lexem, scanered_file);
		fclose(scanered_file);
	}
	else {
		printf_s("error on write file %s", argv[2]);
		return 1;
	}
	

	if (argc > 3) {
		listening(program_text, lexemes, count_lexem, argv[3]);
	}
}