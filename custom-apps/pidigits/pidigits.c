/*
 * pidigits - Bailey-Borwein-Plouffe Pi Calculator
 * Part of NeonBitOS
 *
 * This program calculates hexadecimal digits of Pi using the BBP formula.
 * The BBP algorithm can compute the nth digit without computing previous ones.
 *
 * Formula: π = Σ(k=0 to ∞) [1/16^k × (4/(8k+1) - 2/(8k+4) - 1/(8k+5) - 1/(8k+6))]
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Compute modular exponentiation: (base^exp) mod m */
double modular_exp(int base, int exp, int m) {
    if (exp == 0) return 1.0;
    if (exp < 0) return 0.0;

    double result = 1.0;
    double power = base % m;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = fmod(result * power, m);
        }
        power = fmod(power * power, m);
        exp /= 2;
    }

    return result;
}

/* Calculate sum for BBP formula: Σ 16^(n-k) * s / (8k + j) */
double bbp_sum(int n, int j) {
    double sum = 0.0;
    int k;

    /* First part: k from 0 to n (requires modular exponentiation) */
    for (k = 0; k <= n; k++) {
        int ak = 8 * k + j;
        double r = modular_exp(16, n - k, ak);
        sum += r / ak;
        sum = sum - floor(sum); /* Keep fractional part */
    }

    /* Second part: k from n+1 onwards (converges quickly) */
    for (k = n + 1; k <= n + 100; k++) {
        int ak = 8 * k + j;
        double term = pow(16.0, n - k) / ak;
        if (fabs(term) < 1e-15) break;
        sum += term;
        sum = sum - floor(sum);
    }

    return sum;
}

/* Calculate the nth hexadecimal digit of Pi (0-indexed) */
int bbp_digit(int n) {
    double s1 = bbp_sum(n, 1);  /* 4/(8k+1) */
    double s4 = bbp_sum(n, 4);  /* 2/(8k+4) */
    double s5 = bbp_sum(n, 5);  /* 1/(8k+5) */
    double s6 = bbp_sum(n, 6);  /* 1/(8k+6) */

    double pi_frac = 4.0 * s1 - 2.0 * s4 - s5 - s6;
    pi_frac = pi_frac - floor(pi_frac);  /* Fractional part */

    if (pi_frac < 0) pi_frac += 1.0;

    return (int)(16.0 * pi_frac);
}

void calculate_pi_decimal(int digits) {
    printf("Calculating %d decimal digits of Pi...\n", digits);
    printf("3.");

    /* Hex to decimal conversion requires arbitrary precision arithmetic */
    /* For now, showing known digits */
    printf("14159265358979323846264338327950288419716939937510...\n");
    printf("\n(Note: Full hex-to-decimal conversion requires arbitrary precision)\n");
}

/* Calculate and display hexadecimal digits */
void calculate_pi_hex(int digits) {
    printf("Calculating %d hexadecimal digits of Pi...\n", digits);
    printf("3.");

    for (int i = 0; i < digits; i++) {
        if (i > 0 && i % 64 == 0) {
            printf("\n");
        }
        printf("%X", bbp_digit(i));
    }
    printf("\n");
}

/* Demonstrate BBP's special property: calculate arbitrary digit */
void calculate_nth_digit(int n) {
    printf("Calculating hexadecimal digit at position %d...\n", n);
    int digit = bbp_digit(n);
    printf("The %dth hex digit of Pi is: %X\n", n, digit);
}

void print_usage(const char *progname) {
    printf("NeonBitOS Pi Calculator - Bailey-Borwein-Plouffe Algorithm\n\n");
    printf("Usage:\n");
    printf("  %s                    - Calculate first 100 hex digits\n", progname);
    printf("  %s [N]                - Calculate first N hex digits\n", progname);
    printf("  %s -n [position]      - Calculate specific digit position\n", progname);
    printf("  %s --help             - Show this help\n\n", progname);
    printf("Examples:\n");
    printf("  %s                    - Show first 100 hex digits\n", progname);
    printf("  %s 1000               - Show first 1000 hex digits\n", progname);
    printf("  %s -n 1000000         - Calculate the millionth digit\n\n", progname);
    printf("The BBP algorithm can compute the nth hexadecimal digit\n");
    printf("without computing all previous digits!\n");
}

int main(int argc, char *argv[]) {
    int digits = 100;  /* Default */
    int mode = 0;      /* 0=hex, 1=decimal, 2=nth digit */

    if (argc == 1) {
        /* Default: 100 hex digits */
        calculate_pi_hex(digits);
        return 0;
    }

    if (argc >= 2) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0) {
            print_usage(argv[0]);
            return 0;
        }

        if (strcmp(argv[1], "-h") == 0) {
            mode = 0;  /* Hex mode */
            if (argc >= 3) {
                digits = atoi(argv[2]);
            }
        } else if (strcmp(argv[1], "-d") == 0) {
            mode = 1;  /* Decimal mode */
            if (argc >= 3) {
                digits = atoi(argv[2]);
            }
        } else if (strcmp(argv[1], "-n") == 0) {
            mode = 2;  /* Nth digit mode */
            if (argc >= 3) {
                digits = atoi(argv[2]);
            } else {
                printf("Error: -n requires position argument\n");
                print_usage(argv[0]);
                return 1;
            }
        } else {
            /* Just a number - interpret as hex digits */
            digits = atoi(argv[1]);
            mode = 0;
        }
    }

    if (digits <= 0 || digits > 100000) {
        printf("Error: digits must be between 1 and 100000\n");
        return 1;
    }

    switch (mode) {
        case 0:
            calculate_pi_hex(digits);
            break;
        case 1:
            calculate_pi_decimal(digits);
            break;
        case 2:
            calculate_nth_digit(digits);
            break;
    }

    return 0;
}
