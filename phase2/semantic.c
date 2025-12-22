/**
 * SimpleLang Compiler - Phase 2
 * Semantic Analyzer Implementation
 */

#include "semantic.h"
#include <stdio.h>
#include <stdarg.h>

int semantic_error_count = 0;
int semantic_warning_count = 0;

// Report a semantic error
void semantic_error(int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    fprintf(stderr, "Semantic Error at line %d: ", line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    
    va_end(args);
    semantic_error_count++;
}

// Report a semantic warning
void semantic_warning(int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    fprintf(stderr, "Warning at line %d: ", line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    
    va_end(args);
    semantic_warning_count++;
}

// Check if two types are compatible
bool check_type_compatibility(Type t1, Type t2) {
    if (t1 == t2) return true;
    
    // Allow int-float compatibility
    if ((t1 == TYPE_INT && t2 == TYPE_FLOAT) || 
        (t1 == TYPE_FLOAT && t2 == TYPE_INT)) {
        return true;
    }
    
    return false;
}

// Check if assignment is type-valid
bool check_assignment_type(Type target, Type source) {
    if (target == source) return true;
    
    // Allow implicit conversions
    if (target == TYPE_FLOAT && source == TYPE_INT) return true;  // int -> float
    if (target == TYPE_INT && source == TYPE_FLOAT) return true;   // float -> int (with truncation)
    
    return false;
}

// Check types for arithmetic operations
bool check_arithmetic_types(Type t1, Type t2, Type *result_type) {
    // Both must be numeric
    if ((t1 != TYPE_INT && t1 != TYPE_FLOAT) ||
        (t2 != TYPE_INT && t2 != TYPE_FLOAT)) {
        return false;
    }
    
    // Result type is float if either operand is float
    if (result_type) {
        *result_type = (t1 == TYPE_FLOAT || t2 == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
    }
    
    return true;
}

// Check types for comparison operations
bool check_comparison_types(Type t1, Type t2) {
    // Numeric types can be compared with each other
    if ((t1 == TYPE_INT || t1 == TYPE_FLOAT) &&
        (t2 == TYPE_INT || t2 == TYPE_FLOAT)) {
        return true;
    }
    
    // Same types can be compared (except void)
    if (t1 == t2 && t1 != TYPE_VOID) {
        return true;
    }
    
    return false;
}

// Check types for logical operations
bool check_logical_types(Type t1, Type t2) {
    // Both must be boolean
    return (t1 == TYPE_BOOL && t2 == TYPE_BOOL);
}

// Get result type for mixed type operations
Type get_result_type(Type t1, Type t2) {
    if (t1 == TYPE_FLOAT || t2 == TYPE_FLOAT) return TYPE_FLOAT;
    return t1;  // Default to first type
}

// Check if implicit conversion is allowed
bool can_implicit_convert(Type from, Type to) {
    if (from == to) return true;
    
    // int -> float is safe
    if (from == TYPE_INT && to == TYPE_FLOAT) return true;
    
    // float -> int with warning (truncation)
    if (from == TYPE_FLOAT && to == TYPE_INT) return true;
    
    return false;
}

// Validate a function call
bool validate_function_call(Symbol *func, Parameter *args, int line) {
    if (!func) {
        semantic_error(line, "Function not found");
        return false;
    }
    
    if (func->sym_type != SYM_FUNCTION) {
        semantic_error(line, "'%s' is not a function", func->name);
        return false;
    }
    
    // Count arguments
    int arg_count = count_params(args);
    
    if (arg_count != func->param_count) {
        semantic_error(line, "Function '%s' expects %d arguments, got %d",
                      func->name, func->param_count, arg_count);
        return false;
    }
    
    // Type check each argument
    Parameter *expected = func->params;
    Parameter *actual = args;
    int arg_num = 1;
    
    while (expected && actual) {
        if (!check_assignment_type(expected->value->type, actual->value->type)) {
            semantic_error(line, "Argument %d of function '%s': type mismatch (expected %s, got %s)",
                          arg_num, func->name,
                          type_to_string(expected->value->type),
                          type_to_string(actual->value->type));
            return false;
        }
        expected = expected->next;
        actual = actual->next;
        arg_num++;
    }
    
    return true;
}

// Check if break/continue is inside a loop
bool check_loop_context(bool in_loop, int line, const char *stmt) {
    if (!in_loop) {
        semantic_error(line, "'%s' statement not within a loop or switch", stmt);
        return false;
    }
    return true;
}

// Check switch expression type
bool check_switch_type(Type t, int line) {
    if (t != TYPE_INT && t != TYPE_STRING) {
        semantic_error(line, "Switch expression must be integer or string type");
        return false;
    }
    return true;
}
