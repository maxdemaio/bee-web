#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// total words in dict.txt
#define MAX_WORDS 370104

struct WordBinaryMap
{
  // general word length max (1 char is 1 byte)
  char word[32];
  // binary representation of word
  uint32_t binary;
};

// Example:
// word: cats (2, 0, 19, 18)
// binary: 00000011000000000000000000000101

// prototyping
uint32_t makeCypher(char *letter);
void makeWordBinaryMap(void);

void makeWordBinaryMap(void)
{
  // if the binary file already exists, return so we don't regenerate
  FILE *binary_file_r = fopen("word_bin_map.bin", "rb");
  if (binary_file_r)
  {
    fclose(binary_file_r);
    return;
  }

  struct WordBinaryMap *word_binaries = NULL;
  int num_words = 0;

  // open the dictionary
  // note: small_dictionary.txt is used in this example
  // but, feel free to use a real dictionary similar to curate.py
  FILE *dict_file = fopen("dict.txt", "r");
  if (!dict_file)
  {
    perror("Failed to open dictionary file");
    fclose(dict_file);
    return;
  }

  // iterate over each word in the dictionary
  // we'll use each word to create the array of WordBinaryMap structs
  char word[32];
  while (fscanf(dict_file, "%s", word) != EOF)
  {
    uint32_t binary_word = 0;

    // convert the word to its 32-bit representation
    for (int i = 0; i < strlen(word); i++)
    {
      binary_word |= (1u << (word[i] - 'a'));
    }

    // allocate memory for the new WordBinaryMap struct
    struct WordBinaryMap *new_word = malloc(sizeof(struct WordBinaryMap));
    if (new_word == NULL)
    {
      perror("Failed to allocate memory for new_word");
      fclose(binary_file_r);
      fclose(dict_file);
      return;
    }

    // set the values of the new WordBinaryMap struct
    strcpy(new_word->word, word);
    new_word->binary = binary_word;

    // append the new WordBinaryMap struct to the dynamically allocated array
    struct WordBinaryMap *new_word_binaries = realloc(word_binaries, sizeof(struct WordBinaryMap) * (num_words + 1));
    if (new_word_binaries == NULL)
    {
      perror("Failed to allocate memory for new_word_binaries");
      fclose(binary_file_r);
      fclose(dict_file);
      return;
    }
    word_binaries = new_word_binaries;
    word_binaries[num_words] = *new_word;
    num_words++;

    free(new_word);
  }

  // create the binary file for writing
  FILE *binary_file_w = fopen("word_bin_map.bin", "wb");
  if (!binary_file_w)
  {
    perror("Failed to open binary file for writing");
    fclose(binary_file_r);
    fclose(dict_file);
    return;
  }

  // write the array of structs to the binary file
  fwrite(word_binaries, sizeof(struct WordBinaryMap), num_words, binary_file_w);

  fclose(binary_file_r);
  fclose(binary_file_w);
  fclose(dict_file);
  free(word_binaries);
}

uint32_t makeCypher(char *letters)
{
  uint32_t cypher = 0;
  for (int i = 0; i < strlen(letters); i++)
  {
    cypher |= (1u << (letters[i] - 'a'));
  }
  return ~cypher;
}

int main(int argc, char *argv[])
{
  makeWordBinaryMap();
  return 0;
}