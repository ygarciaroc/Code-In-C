#include <stdio.h>
#include <math.h>

// Compound interest factor (F/P, i, n)
double F_given_P(double P, double i, int n) {
    return P * pow(1 + i, n);
}

// Present worth factor (P/F, i, n)
double P_given_F(double F, double i, int n) {
    return F / pow(1 + i, n);
}

// Capital recovery factor (A/P, i, n)
double A_given_P(double P, double i, int n) {
    return P * (i * pow(1 + i, n)) / (pow(1 + i, n) - 1);
}

// Present worth of uniform series (P/A, i, n)
double P_given_A(double A, double i, int n) {
    return A * ( (pow(1+i,n) - 1) / (i * pow(1+i,n)) );
}

// Arithmetic gradient (P/G, i, n)
double P_given_G(double G, double i, int n) {
    return G * ( (1.0 / i) - (n / (pow(1+i, n) - 1)) );
}

int main() {
    double P = 1000.0;   // Present value
    double i = 0.10;     // Interest rate (10%)
    int n = 5;           // Number of periods

    double F = F_given_P(P, i, n);
    double A = A_given_P(P, i, n);

    printf("Future worth (F) of %.2f at %.2f%% for %d years = %.2f\n", P, i*100, n, F);
    printf("Equivalent annual cost (A) = %.2f\n", A);

    return 0;
}
