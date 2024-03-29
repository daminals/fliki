#include <stdlib.h>

#include "debug.h"
#include "fliki.h"
#include "global.h"
#include "funcs.h"

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the various options that were specified will be
 * encoded in the global variable 'global_options', where it will be
 * accessible elsewhere in the program.  For details of the required
 * encoding, see the assignment handout.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * @modifies global variable "global_options" to contain an encoded
 * representation of the selected program options.
 * @modifies global variable "diff_filename" to point to the name of the file
 * containing the diffs to be used.
 */

// declare a function before you can define it lol
char *get_arr_char(char **arr, int i) { return *(arr + i); }
static int is_file(char *str1);

int validargs(int argc, char **argv) {
  // print every argument in argv
  // int j = 0;
  // while (j<argc) {
  //   printf("%d: %s\n", j, get_arr_char(argv, j));
  //   j++;
  // }

  // checks if there are no arguments. if there are none, return failure
  if (argc == 1) {
    return -1;  // exit failure
  }

  // checks if -h exists. if it does, return success
  if (strEqlz(get_arr_char(argv, 1), "-h")) {
    global_options = global_options | HELP_OPTION;
    return 0;  // exit success
  }

  int i = 1;
  while (i < argc - 1) {
    // printf("\n %s ",get_arr_char(argv, i));
    if (strEqlz(get_arr_char(argv, i), "-n") == 1) {
      global_options = global_options | NO_PATCH_OPTION;
      // printf("-n: %ld", global_options);
    } else if (strEqlz(get_arr_char(argv, i), "-q") == 1) {
      global_options = global_options | QUIET_OPTION;
      // printf("-q: %ld",global_options);
    } else if (strEqlz(get_arr_char(argv, i), "-h") == 1) {
      if (i != 1) {
        return -1;  // exit failure
      }
    } else {
      global_options = 0x0; // reset if bad option
      return -1;  // exit failure
      // option that doesn't exist
    }
    i++;
  }

  // if -h doesn't exist, check if the last argument is a file then open the file
  if (!is_file(get_arr_char(argv, argc - 1))) {  // last argument
    return -1;
  } else {
    diff_filename = get_arr_char(argv, argc - 1);
  }
  return 0;
}

int strEqlz(char *str1, char *str2) {
  if (strLen(str1) > strLen(str2)) {
    return 0;
  }
  int i = 0;
  while (*(str1 + i) == *(str2 + i) && *(str1 + i) != '\0') {
    i++;
  }
  if (i != strLen(str1)) {
    return 0;
  }
  return 1;
}

int strLen(char *str1) {
  int i = 0;
  while (*(str1 + i) != '\0') {
    i++;
  }
  return i;
}

static int is_file(char *filename) {
  return *(filename + 0) != '-';
}