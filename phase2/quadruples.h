/**
 * SimpleLang Compiler - Phase 2
 * Quadruples Header
 * 
 * Implements three-address code generation using quadruples.
 * Format: (operator, arg1, arg2, result)
 */

#ifndef QUADRUPLES_H
#define QUADRUPLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUADS 2000

typedef struct {
    char op[20];       // Operation
    char arg1[64];     // First operand
    char arg2[64];     // Second operand
    char result[64];   // Result/destination
} Quadruple;

// Global quadruple array and counter
extern Quadruple quads[MAX_QUADS];
extern int quad_count;

// Temporary and label counters
extern int temp_count;
extern int label_count;

// Add a quadruple
void add_quad(const char *op, const char *arg1, const char *arg2, const char *result);

// Print all quadruples
void print_quads(void);

// Print quadruples to file
void print_quads_to_file(FILE *fp);

// Generate a new temporary variable name
char* new_temp(void);

// Generate a new label name
char* new_label(void);

// Get current quadruple index (for backpatching)
int get_next_quad(void);

// Backpatch a list of quadruple indices with a label
void backpatch(int *list, int list_size, const char *label);

#endif // QUADRUPLES_H
