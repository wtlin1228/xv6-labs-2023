#include "kernel/types.h"
#include "user/user.h"

#define BUFFER_SIZE 1024

char *deep_copy_string(const char *src)
{
  char *copy = malloc(strlen(src) + 1);
  strcpy(copy, src);
  return copy;
}

void append_stdin_words_to_new_argv(char **new_argv, int next_arg_idx)
{
  char buffer[BUFFER_SIZE];
  int bytes_read;
  int word_len = 0;
  char word[512];
  while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
  {
    for (int i = 0; i < bytes_read; i++)
    {
      if (buffer[i] == '\n')
      {
        // End of a word
        if (word_len > 0)
        {
          word[word_len] = '\0';
          word_len = 0;
          new_argv[next_arg_idx] = deep_copy_string(word);
          next_arg_idx++;
        }
      }
      else
      {
        // Part of a word
        word[word_len++] = buffer[i];
      }
    }
  }
}

int main(int argc, char *argv[])
{
  char *utility = argv[1];
  char **new_argv = malloc(9 * sizeof(char *));
  int next_arg_idx = argc - 1;

  for (int i = 1; i < argc; i++)
  {
    new_argv[i - 1] = argv[i];
  }
  append_stdin_words_to_new_argv(new_argv, next_arg_idx);

  exec(utility, new_argv);
  exit(0);
}
