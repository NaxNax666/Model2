//#include "stdafx.h"
#include <iostream>

// Алгоритм проверки попадания значения в плотность вероятности
bool check(double u1, double u2)
{
    if (u1 >= 0 && u1 < 1)
    {
        if (u2 <= 0.125)
            return true;
    }
    if (u1 >= 1 && u1 < 3)
    {
        if (u2 <= 0.25)
            return true;
    }
    if (u1 >= 3 && u1 < 6)
    {
        if (u2 <= (-(1.0/12.0)*u1+0.5))
            return true;
    }
    return false;
}

//генератор случайного числапо методу мультипликативного датчика
double random(double e)
{
    long long int X;
    double U;
    long long int a = 42589, b = 55555;
    long long int m = 9835497;
    X = rand() % (m + 1);
    U = X * e / (double)m;
    for (int i = 0; i < 100; i++)
    {
        X = (a * X + b) % m; //следующее целое число
        U = X * e / (double)m;
    }
    return U;
}

//основной алгоритм
int main()
{
    setlocale(LC_CTYPE, "rus");
    const int M = 24926; //размер последовательности
    const int L = 30; //кол-во отрезков
    int p = 0; //период
    double e = 10000000; //точность
    double x = 0;

    int k[L]= {}; //кол-во попаданий в отрезки
    for (int j = 0; j < L; j++)
    {
        k[j] = 0;
    }
    int i = 0;

    do {
        double u1 = random(e) / e * 6; //число, распределённое на [a, d)
        double u2 = random(e) / e * 0.25; //число, распределённое на [0, h]
        if (i == 0) x = u1;
        if (check(u1, u2) == true) //попадание
        {
            if (i > 0 && p == 0 && u1 == x) p = i;

            for (int g = 0; g < L; g++)
            {
                if (u1 >= (double)6*g / (double)L && u1 < (double)6*(g + 1) / (double)L)
                    k[g]++;
            }
            i++;
        }
    } while (i < M);

    if (p != 0)	std::cout << "Period " << p << "\n";
    //else std::cout << "Period > 40K.\n";
    std::cout << "Gistogram" << "\n";
    for (int j = 0; j < L; j++)
    {
        std::cout << k[j] << "\n";
    }
    return 0;
}
