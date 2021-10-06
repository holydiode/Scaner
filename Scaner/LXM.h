#define OUT

typedef struct
{
	unsigned char type_lexam;
	unsigned int start_move;
	unsigned int end_move;
}LXM;


char* skip_ignorable_signs(char* cursore);

char numeric_lexem(char* cursore, OUT char** end_lexem);

char named_lexem(char* cursore, OUT char** end_lexem);

LXM get_lxm(char* start, char** cursore);

int get_file_lxms(char* start, OUT LXM* lexem_array);

void get_string_and_column(char* program_text,LXM lxm,OUT int* column, OUT int* string);

void get_text_lxms(char* string, OUT char* buffer, LXM lxm);

char* get_lexem_name(unsigned char lexem_type);