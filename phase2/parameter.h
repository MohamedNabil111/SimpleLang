/**
 * SimpleLang Compiler - Phase 2
 * Function Parameter Header
 */

#ifndef PARAMETER_H
#define PARAMETER_H

#include "val.h"

typedef struct Parameter {
    char *name;
    val *value;
    struct Parameter *next;
} Parameter;

#endif // PARAMETER_H
