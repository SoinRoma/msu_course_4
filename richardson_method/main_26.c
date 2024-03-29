// 26. Метод сведение уравнения к системе второго порядка,
// нахождения решения этой системы ДУ методом аппроксимации
// Ричардсона и используя метод пристрелки (с методом деления пополам)
// для решения уравнения.

// Описание метода.
// Программа решает задачу поиска функции y(x) при заданном диф.ур. второго порядка вида:
// y''+p(x)*y'+q(x)*y = f(x)
// с условиями y(a) = c, y(b) = d на [a, b].
// Берём замену z = y' и получаем систему:
//     { y' = z
//     { z' = -p(x)z - q(x)y + f(x)
// с начальными значениями на левой границе y(a) = c, z(a) = t, где t - параметр.

// Методом пристрелки подбирается значение параметра t для уравнения F(t) - d = 0, где
// F(t) - значение приближения в точке b, найденное методом Аппроксимации Ричардсона.

// Интерфейсный модуль программы

#include "odu_26.h"

int main() {
    SetConsoleOutputCP(CP_UTF8); // Для отображения кирилицы

/*1*/      //double a = 0, b = 1;  //  Задаём начало отрезка
/*2*/      //double a = 0, b = 2;  //  Задаём начало отрезка
/*3*/      double a = 0, b = 3;  //  Задаём начало отрезка
/*4*/      //double a = 2, b = 5;  //  Задаём начало отрезка
/*5*/      //double a = 0.5, b = 1.5;  //  Задаём начало отрезка
/*6*/      //double a = 0, b = 1;  //  Задаём начало отрезка   //    не работает
/*7*/      //double a = 1, b = 3;  //  Задаём начало отрезка

    double *answers = (double *) (size_t) (double *) malloc((9000) * sizeof(double));
    double *tempMemory = (double *) (size_t) (double *) malloc((9000) * sizeof(double));
    double c = y(a), d = y(b); // условия
    double h = 0.1, e = 1e-6;  // задаём шаг и точность
    int n = (int) ((b - a) / h), value = 0;

    FILE  *outfile = fopen("C:\\Users\\Professional\\Desktop\\Task-1\\dataout.csv", "w");  // выходной файл;
    clock_t start, end; // время для работы программы

    start = clock();
    value = odu_26(a, b, c, d, e, n, answers, tempMemory);
    end = clock();

    printf("Время работы программы: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);  // время работы программы
    printf("Количество итераций: %d\n \n", n + 1);      // количество итераций

    fprintf( outfile,"x,y,y_pred\n"); // задаём имена столбцам для выходного файла.
    for (int j = 0; j < value+1; j++) { // значения функции в найденных узлах
    if (j%(value / n) == 0) {
        fprintf(outfile, "%lf,%1.9f,%1.9f\n",  a+j*(b-a)/value,y(a+j*(b-a)/value),answers[j]); // запись в файл
      }
    }


    fclose(outfile);//закрываем выходной файл
    free(answers);//освобождаем память
    free(tempMemory);//освобождаем память
    system("python C:/Users/Professional/Desktop/Task-1/plot_26.py"); //командноя строка для графика
    return 0;
}