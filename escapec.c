#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define program_name escapec

int print_usage(const char *program) {

  fprintf(stderr,
          "Usage: %s [OPTIONS] [FILE]\n"
          "Escapes text so that it can be used for string literals (C / C++).\n"
          "Options:\n"
          "  -s, --split-lines     Break output on newlines.\n"
          "  -p, --percent         Do not escape %% \n"
          "  -n, --null            End output with null terminator, not a "
          "new-line (the default).\n"
          "  -h, --help            Display this help message.\n"
          "\nIf FILE is not specified, data is read from standard input.\n",
          program);

  return 0;
}

void convert_to_cstr(FILE *input, FILE *output, bool split_lines,
                     bool escape_percent) {
  int c;
  bool first_line = true;

  fprintf(output, "\"");

  while ((c = fgetc(input)) != EOF) {

    switch (c) {
    case '\f':
      fprintf(output, "\\f");
      break;
    case '\n':
      if (split_lines) {
        fprintf(output, "\\n\"\n\"");
        first_line = false;
      } else {
        fprintf(output, "\\n");
      }
      break;
    case '\r':
      fprintf(output, "\\r");
      break;
    case '\t':
      fprintf(output, "\\t");
      break;
    case '\"':
      fprintf(output, "\\\"");
      break;
    case '\\':
      fprintf(output, "\\\\");
      break;
    case '%':
      if (!escape_percent) {
        fprintf(output, "%%");
      } else {
        fprintf(output, "%%%%");
      }
      break;
    default:
      fputc(c, output);
      break;
    }
  }

  fprintf(output, "\"");
}

/* Main */
int main(int argc, char *argv[]) {
  bool split_lines = false;
  bool percent = true;
  bool null_term = false;
  FILE *input = stdin;

  struct option long_options[] = {{"split-lines", no_argument, 0, 's'},
                                  {"percent", no_argument, 0, 'p'},
                                  {"null", no_argument, 0, 'n'},
                                  {"help", no_argument, 0, 'h'},
                                  {0, 0, 0, 0}};

  int opt;
  int option_index = 0;

  while ((opt = getopt_long(argc, argv, "spnh", long_options, &option_index)) !=
         -1) {
    switch (opt) {
    case 's':
      split_lines = true;
      break;
    case 'p':
      percent = false;
      break;
    case 'n':
      null_term = true;
      break;
    case 'h':
      print_usage(argv[0]);
      return 0;
    default:
      print_usage(argv[0]);
      return 1;
    }
  }

  /* Check if we have a filename as an argument */
  if (optind < argc) {
    input = fopen(argv[optind], "r");
    if (!input) {
      fprintf(stderr, "Error: Could not open file '%s'\n", argv[optind]);
      return 1;
    }
  }

  convert_to_cstr(input, stdout, split_lines, percent);

  if (input != stdin) {
    fclose(input);
  }

  if (!null_term) {
    fputc('\n', stdout);
  }
  fputc('\0', stdout);

  fflush(stdout);

  return 0;
}
