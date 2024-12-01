#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_file_into_lines(char *path, size_t *line_count)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(path, "r");
  if (fp == NULL) {
    perror("Failed to open file.");
    exit(EXIT_FAILURE);
  }

  size_t bufferSize = 10;
  char **buffer = malloc(bufferSize * sizeof(char *));
  if (buffer == NULL) {
    perror("Failed to allocate buffer");
    fclose(fp);
    exit(EXIT_FAILURE);
  }

  size_t counter = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (counter >= bufferSize) {
      bufferSize *= 2;
      buffer = realloc(buffer, bufferSize * sizeof(char *));
      if (buffer == NULL) {
        perror("Failed to reallocate memory");
        fclose(fp);
        free(line);
        exit(EXIT_FAILURE);
      }
    }
    buffer[counter] = strdup(line);
    if (buffer[counter] == NULL) {
      perror("Failed to duplicate line");
      fclose(fp);
      free(line);
      for (size_t i = 0; i < counter; i++) {
        free(buffer[i]);
      }
      free(buffer);
      exit(EXIT_FAILURE);
    }
    counter++;
  }

  free(line);
  fclose(fp);

  *line_count = counter;

  return buffer;
}

void free_lines(char **lines, size_t line_count)
{
  for (size_t i = 0; i < line_count; i++) {
    free(lines[i]);
  }
  free(lines);
}

typedef struct Position {
  size_t x;
  size_t y;
} Position;

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  size_t line_count = 0;

  char **lines = read_file_into_lines(argv[1], &line_count);

  int **houses = calloc(1000, sizeof(int *));
  for (int i = 0; i < 1000; i++) {
    houses[i] = calloc(1000, sizeof(int));
  }

  Position santa = {500, 500};
  Position robot = {500, 500};

  houses[santa.x][santa.y] = 1;

  size_t unique_houses = 1;

  for (size_t i = 0; i < line_count; i++) {
    char *line = lines[i];
    size_t line_length = strlen(line);

    for (size_t j = 0; j < line_length; j++) {
      // alternate between santa and robot
      Position *current = (j % 2 == 0) ? &santa : &robot;

      switch (line[j]) {
      case '^':
        current->y++;
        break;
      case 'v':
        current->y--;
        break;
      case '<':
        current->x--;
        break;
      case '>':
        current->x++;
        break;
      default:
        continue;
      }

      // mark house
      if (houses[current->x][current->y] == 0) {
        houses[current->x][current->y] = 1;
        unique_houses++;
      }
    }
  }

  printf("Total houses: %zu\n", unique_houses);

  for (int i = 0; i < 1000; i++) {
    free(houses[i]);
  }
  free(houses);
  free_lines(lines, line_count);
  exit(EXIT_SUCCESS);
}
