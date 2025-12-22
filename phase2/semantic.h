/**
 * SimpleLang Compiler - Phase 2
 * Semantic Analyzer Header
 */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "val.h"
#include "symbol_table.h"
#include <stdbool.h>

// Error tracking
extern int semantic_error_count;
extern int semantic_warning_count;

// Type checking functions
bool check_type_compatibility(Type t1, Type t2);
bool check_assignment_type(Type target, Type source);
bool check_arithmetic_types(Type t1, Type t2, Type *result_type);
bool check_comparison_types(Type t1, Type t2);
bool check_logical_types(Type t1, Type t2);

// Semantic error reporting
void semantic_error(int line, const char *format, ...);
void semantic_warning(int line, const char *format, ...);

// Type coercion - returns result type for mixed operations
Type get_result_type(Type t1, Type t2);

// Check if type can be implicitly converted
bool can_implicit_convert(Type from, Type to);

// Function call validation
bool validate_function_call(Symbol *func, Parameter *args, int line);

// Check if break/continue is valid
bool check_loop_context(bool in_loop, int line, const char *stmt);

// Check switch statement
bool check_switch_type(Type t, int line);

#endif // SEMANTIC_H
