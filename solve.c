#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// total words in dict.txt
#define MAX_WORDS 370104

struct WordBinaryMap {
    // general word length max
    char word[32];
    // binary representation of word
    uint32_t binary;
};

// prototyping
uint32_t makeCypher(char *letter);
void solve(char *letters, char required_letter);

uint32_t makeCypher(char *letters) {
  uint32_t cypher = 0;
    for (int i = 0; i < strlen(letters); i++) {
        cypher |= (1u << (letters[i] - 'a'));
    }
    return ~cypher;
}

void solve(char *letters, char required_letter) {
    uint32_t cypher = makeCypher(letters);

    FILE* fpWb = fopen("word_bin_map.bin", "rb");
    if (!fpWb) {
        perror("Failed to open binary file");
        fclose(fpWb);
        return;
    }

    // 2 step verification
    struct WordBinaryMap word_binary;
    while (fread(&word_binary, sizeof(word_binary), 1, fpWb) == 1) {
      // check contains subset <= given letters
      if ((cypher & word_binary.binary) == 0) {
        // check required letter
        if ((word_binary.binary & (1u << (required_letter - 'a'))) != 0) {
          printf("%s is a valid word!\n", word_binary.word);
        }
      }
    }

    fclose(fpWb);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("usage: %s <string> <character>\n", argv[0]);
    exit(1);
  }

  if (strlen(argv[2]) != 1) {
    printf("error: second argument must be a single character.\n");
    exit(2);
  }

  char *letters = argv[1];
  char required_letter = argv[2][0];

  solve(letters, required_letter);
  return 0;
}