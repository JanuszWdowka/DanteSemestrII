//
// Created by root on 5/13/21.
//

#ifndef INC_6_5_CHAR_OPERATIONS_H
#define INC_6_5_CHAR_OPERATIONS_H
char lower_to_upper(char ch);
char upper_to_lower(char ch);
char space_to_dash(char ch);
char reverse_letter(char ch);
char* letter_modifier(const char* input_text, char (*fun)(char));
#endif //INC_6_5_CHAR_OPERATIONS_H
