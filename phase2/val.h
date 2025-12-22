/**
 * SimpleLang Compiler - Phase 2
 * Value Types Header
 */

#ifndef VAL_H
#define VAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_UNKNOWN
} Type;

typedef struct {
    Type type;
    
    union {
        int i;
        float f;
        char *s;
        int b;  // boolean
    } data;
    
    char *place;       // For code generation - temp variable name
    char *trueLabel;   // For boolean expressions
    char *falseLabel;  // For boolean expressions
    char *endLabel;    // For control flow
    
    bool is_constant;  // For constant folding
} val;

// Helper function to get type as string
static inline const char* type_to_string(Type t) {
    switch (t) {
        case TYPE_INT:     return "rakam";
        case TYPE_FLOAT:   return "kasr";
        case TYPE_STRING:  return "kalam";
        case TYPE_BOOL:    return "mantiq";
        case TYPE_VOID:    return "fadi";
        default:           return "unknown";
    }
}

// Create a new value with default initialization
static inline val* create_val(Type type) {
    val *v = (val*)malloc(sizeof(val));
    if (!v) {
        fprintf(stderr, "Error: Memory allocation failed for val\n");
        exit(EXIT_FAILURE);
    }
    v->type = type;
    v->place = NULL;
    v->trueLabel = NULL;
    v->falseLabel = NULL;
    v->endLabel = NULL;
    v->is_constant = false;
    
    switch (type) {
        case TYPE_INT:    v->data.i = 0; break;
        case TYPE_FLOAT:  v->data.f = 0.0f; break;
        case TYPE_STRING: v->data.s = strdup(""); break;
        case TYPE_BOOL:   v->data.b = 0; break;
        default:          break;
    }
    return v;
}

// Deep copy a value
static inline val* copy_val(val *src) {
    if (!src) return NULL;
    val *v = create_val(src->type);
    v->is_constant = src->is_constant;
    
    switch (src->type) {
        case TYPE_INT:    v->data.i = src->data.i; break;
        case TYPE_FLOAT:  v->data.f = src->data.f; break;
        case TYPE_STRING: 
            free(v->data.s);
            v->data.s = src->data.s ? strdup(src->data.s) : NULL; 
            break;
        case TYPE_BOOL:   v->data.b = src->data.b; break;
        default: break;
    }
    
    if (src->place) v->place = strdup(src->place);
    if (src->trueLabel) v->trueLabel = strdup(src->trueLabel);
    if (src->falseLabel) v->falseLabel = strdup(src->falseLabel);
    if (src->endLabel) v->endLabel = strdup(src->endLabel);
    
    return v;
}

// Free a value
static inline void free_val(val *v) {
    if (!v) return;
    if (v->type == TYPE_STRING && v->data.s) free(v->data.s);
    if (v->place) free(v->place);
    if (v->trueLabel) free(v->trueLabel);
    if (v->falseLabel) free(v->falseLabel);
    if (v->endLabel) free(v->endLabel);
    free(v);
}

#endif // VAL_H
