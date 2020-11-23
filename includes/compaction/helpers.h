#ifndef HELPERS_H
#define HELPERS_H

/**
 * Prints usage to stdout
 * @param executable_name the name of currently being executed binary
 */
void print_usage(const char* executable_name);

/**
 * Returns a string with instructions to get help
 * @param executable_name the name of currently being executed binary
 * @returns message to output when a command is not found
 */
const char* not_found(const char* executable_name);

/**
 * Compares two strings
 * @param a first string to compare
 * @param b second string to compare
 * @returns 1 if equal, otherwise 0
 */
unsigned int str_eq(const char* a, const char* b);

/**
 * Compares two strings
 * @param a first string to compare
 * @param b second string to compare
 * @returns 1 if not equal, otherwise 0
 */
unsigned int str_ne(const char* a, const char* b);

/**
 * Compares sections of two different strings
 * @param a first string to compare
 * @param b second string to compare
 * @param start_at_a position to start comparison at string a
 * @param start_at_b position to start comparison at string b
 * @param length how many chars to compare
 * @returns 1 if the substrings are equal, otherwise 0
 */
unsigned int substr_eq(const char* a,
                       const char* b,
                       int start_at_a,
                       int start_at_b,
                       int length);

/**
 * @param value string to slice
 * @param pos position to start slicing
 * @param length n of chars to take
 * @param pointer to output slice
 * @returns n of read charaters
 */
int str_slice(const char* value, int pos, int length, char* target);

/**
 * Verifies if a character is a number
 * @param character
 * @returns 1 if number, otherwise 0
 */
unsigned int is_number(char character);

/**
 * Scans for the next number in string
 * @param word the string to search
 * @param cursor position to begin searching
 * @param number pointer to output result
 * @returns last position of cursor (and scanned number on *number)
 */
int scan_number(const char* word, int cursor, int* number);

/**
 * Scans for a non-numeric (sub)string in string
 * @param word the string to search
 * @param cursor position to begin searching
 * @param string pointer to output result
 * @returns last position of cursor (and scanned string to *string)
 */
int scan_string(const char* word, int cursor, char* string);

#endif  // HELPERS_H
