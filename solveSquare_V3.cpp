#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>


//----------------------------------------------------------------------------------------------------

double Accuracy = 1e-2; ///<This constant specifies the precision of the comparison with zero
const int MaxNumber   = 1000; ///<This constant sets the maximum length of input numbers
const int NUMBER_OF_TEST = 16; ///<This constant sets amount of unit tests

//----------------------------------------------------------------------------------------------------

/**\brief This function solves a capable equation of the second degree
\return Number of roots
\throw Return -1 if the solution is an infinite set of roots
*/
int SovleEquation (double a,     ///<Coefficient a
                   double b,     ///<Coefficient b
                   double c,     ///<Coefficient c
                   double* ans1, ///<First root
                   double* ans2  ///<Second root
                   );

/**\brief This function compares checks if the variable is in the ambit of zero
\return 1 - The variable enters the ambit of zero
\return 2 - The variable don't enters the ambit of zero
*/
int isZero (double value         ///<Comparison number
            );

/**\brief This function expects user input
\return 0 if input is "exit"
\return 1 if input is "help"
\return 2 if input is "info"
\return 3 if input is "calc"
\return 4 if input is "accuracy"
*/
int waitEnter ();

/**\brief This function expects floating point input
*/
double enterDouble();

/**\brief This function checks if a character is a number
*/
int isNumber (char value         ///<Character to check
              );

/**\brief This function lists the available commands
*/
void fHelp();

/**\brief This function gives information about the program
*/
void fInfo();

/**\brief This function calls the equation calculator
*/
void fCalc();

/**\brief This function allows you to change the precision of the comparison with zero
*/
void fAccuracy();

/**\brief This function runs unit tests
*/
int debugTEST ();

//----------------------------------------------------------------------------------------------------

/**\brief Main function
This function loops until it receives a 0 ("exit"). Receives cast codes and calls the necessary functions
*/
int main ()
    {
        printf ("\n\t\tProgram \"Solver Square equation\"\n"
            "\t\tv. 1.0 (c) PrOgRaMeR\n\n"
            "Enter \"help\" for help\n");

    int result = -1;

    while (1)
        {

        result = waitEnter ();

        switch (result) {

            case -1: debugTEST ();
                     break;

            case 0:  return 0;

            case 1:  fHelp();
                     break;

            case 2:  fInfo();
                     break;

            case 3:  fCalc();
                     break;

            case 4:  fAccuracy();
                     break;

            default: ;
            }
        }
    }

//----------------------------------------------------------------------------------------------------

int SovleEquation (double a, double b, double c, double* ans1, double* ans2)
    {
    if (isZero (a)) {
        if (isZero(b)) {
            if (isZero(c)) {
                printf ("Answer:\n"
                        "infinite number of solutions\n\n");
                return -1;
                }
            else {
                printf ("Answer:\n"
                        "no roots\n\n");
                return 0;
                }
            }
        else {
            *ans1 = -c/b;
            if (isZero(c) == 0) {
                printf ("Answer:\n"
                        "x = %lg\n\n", *ans1);
                }
            else
                printf ("Answer:\n"
                        "x = 0\n\n");

            return 1;
            }
        }

    double sqDiscr = (b*b)-(4*a*c);

    if (sqDiscr < 0) {
        printf ("Unsolvable equation\n\n");
        return 0;
        }

    if (isZero (sqDiscr)) {
        *ans1 = -b/(2*a);
        *ans2 = *ans1;

        printf ("Answer:\n"
                "x1 = x2 = %+lg\n\n", *ans1);

        return 1;
        }

    if (sqDiscr > 0) {
        *ans1 = ((sqrt(sqDiscr)-b)/(2*a));
        *ans2 = ((-sqrt(sqDiscr)-b)/(2*a));

        printf ("Answer:\n"
                "x1 = %+lg\n"
                "x2 = %+lg\n\n", *ans1, *ans2);

        return 2;
        }

    printf ("Non-standard sqDiscriminant value\n\n");
    return 0;
    }

//----------------------------------------------------------------------------------------------------

int isZero (double value)
    {
    return (fabs (value) <= Accuracy);
    }

//----------------------------------------------------------------------------------------------------

int waitEnter ()
    {
    char str[11];

    for (int i = 0; i < 11; i++)
        str[i] = '\0';

    for (int i = 0; i < 11; ++i)
        {
        scanf ("%c", &str[i]);

        if (str[i] == '\n')
            break;
        }

    if (strcmp(str, "help\n") == 0)
        return 1;

    if (strcmp(str, "info\n") == 0)
        return 2;

    if (strcmp(str, "calc\n") == 0)
        return 3;

    if (strcmp(str, "accuracy\n") == 0)
        return 4;

    if (strcmp(str, "TesT\n") == 0)
        return -1;

    if (strcmp(str, "exit\n") == 0)
        return 0;
    return -1;
    }

//----------------------------------------------------------------------------------------------------

double enterDouble()
    {
    char Symbol    = 0;
    int  nSymbol   = 0;

    char nyNumber[MaxNumber];

    int cMinus     = 0,
        negative   = 1,
        cBeforeDot = 0,
        cAfterDot  = 0,
        isDot      = 0;

    int flag       = 0;

    double Number     = 0,
           Tenpow     = 1;

    while (flag == 0)   //repeat until we get the number
        {
        flag       = 1;
        Symbol     = 0;
        nSymbol    = 0;
        cMinus     = 0;
        isDot      = 0;
        cBeforeDot = 0;
        cAfterDot  = 0;

        for (int i = 0; i < MaxNumber; i++)
                nyNumber[i] = EOF;

        for (int k = 0; k != MaxNumber; k++)  //user input
            {
            scanf("%c", &Symbol);

            if (Symbol == '\n')
                break;

            nyNumber[k] = Symbol;
            nSymbol++;
            }

        for (int p = 0; p < nSymbol; p++)   //check user's input
            {

            if ((nyNumber[p] == '-') && (p == 0))
                    negative = -1;

            if (isDot == 1) {
                if ((isNumber(nyNumber[p]) == 0) && (nyNumber[p] != '\n') && (nyNumber[p] != '-')) {
                    flag = 0;
                    }
                }

            if (isDot == 0) {
                if ((isNumber(nyNumber[p]) == 0) && (nyNumber[p] != '\n') && (nyNumber[p] != '.') && (nyNumber[p] != '-')) {
                    flag = 0;
                    }
                }

            if (cMinus > 1)
                flag = 0;

            if (((isNumber(nyNumber[p]) != 0)) && (isDot == 0))
                cBeforeDot++;

            if (nyNumber[p] == '.')
                isDot++;

            if (nyNumber[p] == '-')
                cMinus++;

            if (((isNumber(nyNumber[p]) != 0)) && (isDot == 1))
                cAfterDot++;
            }

        if (flag == 0)
            printf ("Its not a number \n");
        }
    int start = 1;

    if (negative == 1)
        start = 0;

    for (int t = 0; t < cBeforeDot; t++)
        {
        Tenpow = 1;
        for (int r = 0; r < (cBeforeDot - t - 1); r++)
            Tenpow = Tenpow * 10;

        Number = Tenpow * (nyNumber[t + start] - '0') + Number;
        }

    for (int t = 0; t < cAfterDot; t++)
        {
        Tenpow = 1;
        for (int r = 0; r < (t + 1); r++)
            Tenpow = Tenpow * 0.1;

        Number = Tenpow * (nyNumber[t + cBeforeDot + 1 + start] - '0') + Number;
        }

    Number = Number * negative;

    return Number;

    }

//----------------------------------------------------------------------------------------------------

int isNumber (char value)
    {
    if (value >= '0' && value <= '9')
        return 1;
    return 0;
    }

//----------------------------------------------------------------------------------------------------

void fHelp()
    {
    printf ("\nList of possible commands:\n"
            "\"help\" - summon this list\n"
            "\"info\" - gives information about the purpose of the program, gives a description of constants and their values\n"
            "\"calc\" - solves the equation\n"
            "\"cnst\" - allows you to change the values of constants\n"
            "\"exit\" - exits the program\n\n");
    }

//----------------------------------------------------------------------------------------------------

void fInfo()
    {
    printf ("\nThis program is needed to solve quadratic (and linear) equations. \n\n"
            "The following constants are applied here:\n"
            "Accuracy = %lg - determines the precision of the comparison with zero\n"
            "MaxNumber = %d - defines the maximum number of characters in a number\n\n", Accuracy, MaxNumber);
    }

//----------------------------------------------------------------------------------------------------

void fCalc()
    {

    double  x1   = 0,
            x2   = 0,
            cof1 = 0,
            cof2 = 0,
            cof3 = 0;

    printf ("Write a:  ");
    cof1 = enterDouble();
    printf ("Write b:  ");
    cof2 = enterDouble();
    printf ("Write c:  ");
    cof3 = enterDouble();
    printf ("\n");

    SovleEquation (cof1, cof2, cof3, &x1, &x2);

    }

//----------------------------------------------------------------------------------------------------

void fAccuracy()
    {
    double CNG = 0;

    printf ("\nValue of constant:\n"
            "Accuracy = %lg\n"
            "New Accuracy\'s value: ", Accuracy);

    CNG = enterDouble();

    if (CNG > 0)
        Accuracy = CNG;
    else
        printf ("Accuracy\'s value must be positive");


    printf ("\nValue of constant:\n"
            "Accuracy = %lg\n\n", Accuracy);

    }

//----------------------------------------------------------------------------------------------------

int debugTEST ()
    {
		FILE* input;
		FILE* output;

		input = fopen("input.txt", "r");
		//assert(input != NULL);

		if (input == NULL)
			{
				fprintf(stderr, "This file is empty!");
				return 1;
			}

		output = fopen("output.txt", "w");

		double a = 0, b = 0, c = 0;
		int i = 0;

		for (i = 0; i < NUMBER_OF_TEST; i++)
			{

			double x1 = 0, x2 = 0;
			int roots = 0;

			fscanf(input, "%lg %lg %lg", &a, &b, &c);

			roots = SovleEquation(a, b, c, &x1, &x2);

			switch(roots)
				{
					case 0: fprintf(output, "No roots\n"); break;
					case 1: fprintf(output, "%lg\n", x1); break;
					case 2: fprintf(output, "%lg %lg\n", x1, x2); break;
					case -1: fprintf(output, "infinite\n");
					default: ;
				}
			}
		printf("All tests are done\n\n");
		fclose(input);
		fclose(output);
		return 0;
	}
