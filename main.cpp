// Copyright (c) 2017 Daniel Mabugat
// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php


#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
uint8_t get_edit_distance(const char *string_1, const char *string_2);

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: Pass two strings as command line arguments "
			"to compare the edit distance between them.\n");
		exit(1);
	}

	uint8_t result = get_edit_distance(argv[1], argv[2]);
	printf("Edit distance between '%s' and '%s' is %d\n", argv[1], argv[2], result);
}


//Receives an input of two strings and returns the Levenshtein distance between
//them as an unsigned integer. Function dynamically allocates a two dimensional
//array it later frees before the function returns.
uint8_t get_edit_distance(const char *string_1, const char *string_2) {
	uint8_t str_len_1 = strlen(string_1);
	uint8_t str_len_2 = strlen(string_2);
	uint8_t i, j;

	// Create data matrix
	uint8_t **data_mat = new uint8_t *[str_len_1 + 1];
	for (i = 0; i <= str_len_1; i += 1)
		data_mat[i] = new uint8_t[str_len_2 + 1];

	// Do work
	for (i = 0; i <= str_len_1; i += 1)
		for (j = 0; j <= str_len_2; j += 1) {
			if (i == 0)
				data_mat[i][j] = j;
			else if (j == 0)
				data_mat[i][j] = i;
			else if (string_1[i-1] == string_2[j-1])
				data_mat[i][j] = data_mat[i-1][j-1];
			else
				data_mat[i][j] = 1 + std::min(std::min(data_mat[i-1][j], data_mat[i][j-1]),data_mat[i-1][j-1]);
		}
	uint8_t result = data_mat[str_len_1][str_len_2];
	delete data_mat;
	return result;
}
