#include <stdio.h>
#include <math.h>
#include <assert.h>

//----------------------------------------------------------------------------------------------------

#define Prec_isZero 1e-2

//----------------------------------------------------------------------------------------------------

int SovleSquare (double a, double b, double c, double* ans1, double* ans2);

/*  function SolveSquare:
    a, b ,c    - coefficients of square equation(SE)
    ans1, ans2 - address of answers of SE
    return     - answer amount
*/

int isZero (double value);

/*  function isZero:
    checking a variable for zero by comparing it with zero with a certain precision (const - Prec_isZero)
*/

//----------------------------------------------------------------------------------------------------

int main ()
    {
    double  x1   = 0,
            x2   = 0,
            cof1 = 0,
            cof2 = 0,
            cof3 = 0;

    printf ("Write a:  ");
    scanf  ("%lg", &cof1);
    printf ("Write b:  ");
    scanf  ("%lg", &cof2);
    printf ("Write c:  ");
    scanf  ("%lg", &cof3);

    if (SovleSquare (cof1, cof2, cof3, &x1, &x2) != 0)
        {
        printf ("Sum of answers: %+lg\n", (x1+x2));
        }

    return 0;
    }

//----------------------------------------------------------------------------------------------------

int SovleSquare (double a, double b, double c, double* ans1, double* ans2)
    {

    assert (&ans1 != NULL);
    assert (&ans2 != NULL);
    assert (&ans1 != &ans2);

    if (isZero (a))
    {
    printf ("Isn't a square equation. First coefficient is almost 0\n");
    return 0;
    }

    double discr = (b*b)-(4*a*c);

    if (discr < 0)
        {
        printf ("Unsolvable equation\n");
        return 0;
        }

    if (isZero (discr))
        {
        *ans1 = -b/(2*a);
        *ans2 = *ans1;

        printf ("Answer: \n x1 = x2 = %+lg\n", *ans1);

        return 1;
        }

    if (discr > 0)
        {
        *ans1 = ((sqrt(discr)-b)/(2*a));
        *ans2 = ((-sqrt(discr)-b)/(2*a));

        printf ("Answer:\n"
                "x1 = %+lg\n"
                "x2 = %+lg\n", *ans1, *ans2);

        return 2;
        }

    printf ("Non-standard discriminant value");
    return 0;
    }

//----------------------------------------------------------------------------------------------------

int isZero (double value)
    {
    return (fabs (value) < Prec_isZero);
    }
