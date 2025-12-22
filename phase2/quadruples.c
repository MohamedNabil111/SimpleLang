/**
 * SimpleLang Compiler - Phase 2
 * Quadruples Implementation
 */

#include "quadruples.h"

// Global definitions
Quadruple quads[MAX_QUADS];
int quad_count = 0;
int temp_count = 0;
int label_count = 0;

// Add a quadruple
void add_quad(const char *op, const char *arg1, const char *arg2, const char *result) {
    if (quad_count >= MAX_QUADS) {
        fprintf(stderr, "Error: Maximum number of quadruples exceeded\n");
        return;
    }
    
    strncpy(quads[quad_count].op, op ? op : "", sizeof(quads[quad_count].op) - 1);
    strncpy(quads[quad_count].arg1, arg1 ? arg1 : "", sizeof(quads[quad_count].arg1) - 1);
    strncpy(quads[quad_count].arg2, arg2 ? arg2 : "", sizeof(quads[quad_count].arg2) - 1);
    strncpy(quads[quad_count].result, result ? result : "", sizeof(quads[quad_count].result) - 1);
    
    // Null-terminate
    quads[quad_count].op[sizeof(quads[quad_count].op) - 1] = '\0';
    quads[quad_count].arg1[sizeof(quads[quad_count].arg1) - 1] = '\0';
    quads[quad_count].arg2[sizeof(quads[quad_count].arg2) - 1] = '\0';
    quads[quad_count].result[sizeof(quads[quad_count].result) - 1] = '\0';
    
    quad_count++;
}

// Print all quadruples to stdout
void print_quads(void) {
    printf("\n=== Generated Quadruples ===\n");
    printf("%-6s %-12s %-15s %-15s %-15s\n", 
           "Index", "Operator", "Arg1", "Arg2", "Result");
    printf("--------------------------------------------------------------------\n");
    
    for (int i = 0; i < quad_count; i++) {
        printf("%-6d %-12s %-15s %-15s %-15s\n",
               i,
               quads[i].op,
               quads[i].arg1[0] ? quads[i].arg1 : "_",
               quads[i].arg2[0] ? quads[i].arg2 : "_",
               quads[i].result[0] ? quads[i].result : "_");
    }
    printf("\nTotal quadruples: %d\n", quad_count);
}

// Print quadruples to file
void print_quads_to_file(FILE *fp) {
    if (!fp) return;
    
    fprintf(fp, "\n=== Generated Quadruples ===\n");
    fprintf(fp, "%-6s %-12s %-15s %-15s %-15s\n", 
            "Index", "Operator", "Arg1", "Arg2", "Result");
    fprintf(fp, "--------------------------------------------------------------------\n");
    
    for (int i = 0; i < quad_count; i++) {
        fprintf(fp, "%-6d %-12s %-15s %-15s %-15s\n",
                i,
                quads[i].op,
                quads[i].arg1[0] ? quads[i].arg1 : "_",
                quads[i].arg2[0] ? quads[i].arg2 : "_",
                quads[i].result[0] ? quads[i].result : "_");
    }
    fprintf(fp, "\nTotal quadruples: %d\n", quad_count);
}

// Generate a new temporary variable name
char* new_temp(void) {
    char *temp = (char*)malloc(20);
    if (!temp) {
        fprintf(stderr, "Error: Memory allocation failed for temp\n");
        exit(EXIT_FAILURE);
    }
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

// Generate a new label name
char* new_label(void) {
    char *label = (char*)malloc(20);
    if (!label) {
        fprintf(stderr, "Error: Memory allocation failed for label\n");
        exit(EXIT_FAILURE);
    }
    sprintf(label, "L%d", label_count++);
    return label;
}

// Get current quadruple index
int get_next_quad(void) {
    return quad_count;
}

// Backpatch a list of quadruple indices with a label
void backpatch(int *list, int list_size, const char *label) {
    if (!list || !label) return;
    
    for (int i = 0; i < list_size; i++) {
        int idx = list[i];
        if (idx >= 0 && idx < quad_count) {
            strncpy(quads[idx].result, label, sizeof(quads[idx].result) - 1);
            quads[idx].result[sizeof(quads[idx].result) - 1] = '\0';
        }
    }
}
