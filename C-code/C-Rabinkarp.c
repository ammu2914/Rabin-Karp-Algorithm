#include <stdio.h>
#include <string.h>

#define d 10

void rabinKarp(char pattern[], char input[], int p) {
  int m = strlen(pattern);
  int n = strlen(input);
  int i, j;
  int ph = 0;
  int th = 0;
  int hash = 1;

  for (i = 0; i < m - 1; i++)
    hash = (hash * d) % p;

  // Calculate hash value for pattern and input
  for (i = 0; i < m; i++) {
    ph = (d * ph + pattern[i]) % p;
    th = (d * th + input[i]) % p;
  }

  // Slide the pattern over text one by one
  for (i = 0; i <= n - m; i++) {
     // Check the hash values of current substring of input
        // and pattern. If the hash values match then only
        // check for characters one by one
    if (ph == th) {
        //Check for characters one by one 
      for (j = 0; j < m; j++) {
        if (input[i + j] != pattern[j])
          break;
      }

      if (j == m)
        printf("Pattern is found at position:  %d \n", i + 1);
       
    }
    // Calculate hash value for next substring of input:
        // Remove leading digit, add trailing digit

    if (i < n - m) {
      th = (d * (th - input[i] * hash) + input[i + m]) % p;
            // We might get negative value of t, converting
            // it to positive
      if (th < 0)
        th = (th + p);
    }
    
    
  }
  
}

int main() {
  FILE *file;
  char input[1000]; // Assuming maximum length of input
  char pattern[100]; // Assuming maximum length of pattern
  int p = 13;

  // Open the file for reading
  file = fopen("input.txt", "r");
  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  // Read input string from file
  fscanf(file, "%s", input);

  // Read pattern string from file
  fscanf(file, "%s", pattern);

  fclose(file);

  // Perform pattern matching
  rabinKarp(pattern, input, p);

  return 0;
}
