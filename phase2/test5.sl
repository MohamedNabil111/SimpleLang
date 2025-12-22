// SimpleLang Test File 5 - Comprehensive Example
// A more complete program demonstrating all features

// ========================================
// Constants
// ========================================
sabit rakam MAX_ITERATIONS = 10;
sabit kasr PI = 3.14159265;

// ========================================
// Global Variables
// ========================================
rakam globalCounter = 0;
kalam programName = "SimpleLang Demo";

// ========================================
// Helper Functions
// ========================================

// Calculate factorial (iterative)
shoghla rakam factorial(rakam n) {
    rakam result = 1;
    rakam i = 1;
    tool ma (i <= n) {
        result = result * i;
        i = i + 1;
    }
    ragga3 result;
}

// Check if number is even
shoghla mantiq isEven(rakam num) {
    // Using modulo operator
    rakam remainder = num % 2;
    law (remainder == 0) {
        ragga3 sa7;
    }
    ragga3 ghalat;
}

// Calculate circle area
shoghla kasr circleArea(kasr radius) {
    ragga3 PI * radius * radius;
}

// ========================================
// Main Program
// ========================================

etba3 programName;
etba3 "===================";

// Test factorial
rakam num = 5;
rakam fact = factorial(num);
etba3 "Factorial result:";
etba3 fact;

// Test even/odd
lef (rakam i = 1; i <= 5; i++) {
    law (isEven(i)) {
        etba3 "Even:";
        etba3 i;
    } wella {
        etba3 "Odd:";
        etba3 i;
    }
}

// Test circle area
kasr r = 5.0;
kasr area = circleArea(r);
etba3 "Circle area:";
etba3 area;

// Nested loops with break
rakam outer = 0;
tool ma (outer < 3) {
    rakam inner = 0;
    tool ma (inner < 3) {
        law (inner == 2) {
            ekhla3;
        }
        etba3 inner;
        inner = inner + 1;
    }
    outer = outer + 1;
}

// Switch demonstration
rakam day = 3;
ekhtar (day) {
    7ala 1:
        etba3 "Monday";
        ekhla3;
    7ala 2:
        etba3 "Tuesday";
        ekhla3;
    7ala 3:
        etba3 "Wednesday";
        ekhla3;
    7ala 4:
        etba3 "Thursday";
        ekhla3;
    7ala 5:
        etba3 "Friday";
        ekhla3;
    asasya:
        etba3 "Weekend";
}

etba3 "===================";
etba3 "Program completed!";
