#include "Prog1.h"

/*Из входного потока вводится прямоугольная сильно разреженная матрица целых чисел [aij], i = 1, …, m, j = 1, …, n.  Значения m и n заранее не известны и вводятся из входного потока.

Сформировать новую матрицу, поместив в ее i-ую строку только те числа из i-ой строки исходной матрицы, сумма цифр которых совпадает с суммой цифр последнего числа в этой же строке.

Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.
 * */

int main() {
    Prog1::Matrix matrix, dop_matrix;
    Prog1::start(matrix);
    std::cout << "First matrix " << std::endl;
    Prog1::print(matrix);
    dop_matrix = Prog1::additional_task(matrix);
    std::cout << "Second matrix " << std::endl;
    Prog1::print(dop_matrix);
    Prog1::erase(matrix);
    Prog1::erase(dop_matrix);
    return 0;
}
