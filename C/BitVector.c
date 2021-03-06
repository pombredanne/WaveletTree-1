// BitVector implementation.
// Created by dsisejkovic on 10.01.16..
//
#include "BitVector.h"

struct BitVector *allocateBitVector(int num_of_chars) {
    int calc_num = num_of_chars / 8;

    if (calc_num == 0) {
        calc_num = 1;
    } else if (num_of_chars % 8 > 0) {
        ++calc_num;
    }

    struct BitVector *bit_vector = (struct BitVector *) malloc(sizeof(struct BitVector));
    bit_vector->bits = (char *) malloc(calc_num * sizeof(char));
    bit_vector->size = num_of_chars;

    return bit_vector;
}

void bitVecSetOnPosition(struct BitVector *bit_vector, int index, bool value) {
    int array_index = index / 8;
    int bit_index = index % 8;

    if (value == TRUE) {
        bit_vector->bits[array_index] |= (1 << (7 - bit_index));
    } else {
        bit_vector->bits[array_index] &= ~(1 << (7 - bit_index));
    }
}

bool bitVecGetOnPosition(struct BitVector *bit_vector, int index) {
    int array_index = index / 8;
    int bit_index = index % 8;

    return (bit_vector->bits[array_index] >> (7 - bit_index)) & 1;
}

char *extractLettersByEncoding(struct BitVector *bit_vector, char *node_chars, bool value, int *length) {
    int num_of_selected = 0;

    for (int i = 0; i < bit_vector->size; ++i) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            ++num_of_selected;
        }
    }

    char *selected = (char *) malloc((num_of_selected + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < bit_vector->size; i++) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            selected[index] = node_chars[i];
            ++index;
        }
    }

    selected[num_of_selected] = '\0';
    *length = num_of_selected;

    return selected;
}

void printBitVector(struct BitVector *bit_vector) {
    int size = bit_vector->size;
    for (int i = 0; i < size; ++i) {
        printf("%d", bitVecGetOnPosition(bit_vector, i));
    }
    printf("\n");
}

void freeBitVector(struct BitVector *bit_vector) {
    free((void *) bit_vector->bits);
    free((void *) bit_vector);
}

char *getBitVectorAsString(struct BitVector *bit_vector) {
    char *str = (char *) malloc((bit_vector->size + 1) * sizeof(char));

    for (int i = 0; i < bit_vector->size; ++i) {
        str[i] = (char) ((bitVecGetOnPosition(bit_vector, i) == TRUE) ? '1' : '0');
    }

    str[bit_vector->size] = '\0';

    return str;
}

int getOccurrenceCount(struct BitVector *bit_vector, int max_position, bool value) {
    if (max_position > bit_vector->size) {
        error("Position can not be greater than bit_vector size.");
    }

    int counter = 0;
    for (int i = 0; i < max_position; ++i) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            ++counter;
        }
    }

    return counter;
}

int calcNthOccurrence(struct BitVector *bit_vector, int nth_occurrence, bool value) {
    int counter = 0;
    int index = -1;

    for (int i = 0; i < bit_vector->size; ++i) {
        if (bitVecGetOnPosition(bit_vector, i) == value) {
            ++counter;
            index = i;
        }

        if (counter == nth_occurrence) {
            break;
        }
    }

    if (counter != nth_occurrence) {
        index = -1;
    }

    return index;
}
