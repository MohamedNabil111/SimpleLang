// SimpleLang Test File 3 - Functions
// Tests: Function declarations, parameters, return statements

// Simple function with no parameters
shoghla rakam getAnswer() {
    ragga3 42;
}

// Function with parameters
shoghla rakam add(rakam a, rakam b) {
    ragga3 a + b;
}

// Function with multiple parameters
shoghla kasr average(kasr x, kasr y, kasr z) {
    kasr sum = x + y + z;
    ragga3 sum / 3.0;
}

// Boolean function
shoghla mantiq isPositive(rakam num) {
    law (num > 0) {
        ragga3 sa7;
    }
    ragga3 ghalat;
}

// Main program
rakam result = add(10, 20);
etba3 result;

kasr avg = average(10.0, 20.0, 30.0);
etba3 avg;

mantiq check = isPositive(5);
etba3 check;

etba3 "Function tests completed!";
