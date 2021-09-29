#define is_number(letter) '0' <= letter && letter <= '9'

#define is_latter(letter) 'a' <= letter && letter <= 'z' || 'A' <= letter && letter <= 'Z' || letter == '_'|| letter == '$'

#define is_ignore(letter) letter == ' ' || letter == '\n' || letter == '\t' || letter == '\r'

#define write_lexem(pointer, lexem) *pointer = lexem; cur_point_in_result++;

#define skip_letter(pointer, condition) for (; condition; pointer++); pointer--;

#define not_limit_translation(pointer, out_pointer, in_condition, skip_kondition, lexem)\
	if (in_condition) {\
		skip_letter(pointer, skip_kondition)\
		write_lexem(out_pointer, lexem)\
	}

#define forget_letter(pointer, in_condition, skip_kondition)\
	if (in_condition) {\
		skip_letter(pointer, skip_kondition)\
	}


#define simple_switch_translation(pointer, letter, lexem)\
	case letter:\
		*pointer = lexem;\
		pointer++; break;

#define fork_switch_translation(pointer, out_pointer, first_letter, first_lexem, second_letter, second_lexem)\
	case first_letter:\
		pointer++;\
		if(*pointer == second_letter){\
			write_lexem(out_pointer, second_lexem)\
		}else{\
			pointer--;\
			write_lexem(out_pointer, first_lexem)\
		}\
		break;


#define switch_endl(pointer, lexem, flag)\
	case '\0':\
		write_lexem(pointer, t_end)\
		write_lexem(pointer, '\0')\
		flag = 0;\
		break;


#define switch_error(pointer, lexem)\
			default:\
				write_lexem(pointer, lexem)\
				break;\
			}

#define keyword_translation(pointer, pointer_out,bufer,start_identificator, in_condition, skip_kondition, lexem, keywords, lexems, count)\
	if (in_condition) {\
		start_identificator = pointer;\
		skip_letter(pointer, skip_kondition)\
		*pointer_out = lexem;\
		pointer++;\
		*bufer = *pointer;\
		*pointer = '\0';\
		for(int i = 0; i < count; i++){\
			if(strcmp(start_identificator, keywords[i]) == 0){\
				*pointer_out = lexems[i];\
				break;\
			}\
		}\
		pointer_out++;\
		*pointer = *bufer; \
		pointer--;\
	}