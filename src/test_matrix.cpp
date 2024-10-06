#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, test_1) {
  S21Matrix a;
  S21Matrix b(a);

  a.S21SetRows(3);
  a.S21SetCols(3);

  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  a(1, 2) = 4.0;

  a(2, 0) = 2.0;
  a(2, 1) = 2.0;
  a(2, 2) = 4.0;

  b = a;

  EXPECT_EQ(a.S21GetRows(), 3);
  EXPECT_EQ(a.S21GetCols(), 3);

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(Constructor, test_2) {
  S21Matrix a = S21Matrix(1, 1);
  S21Matrix b = a;
  b.S21SetCols(9 - a.S21GetCols());
  EXPECT_EQ(9 - a.S21GetCols(), b.S21GetCols());
}

TEST(Constructor, test_3) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;

  S21Matrix b(std::move(a));

  EXPECT_THROW(b(5, 0), std::length_error);
  EXPECT_EQ(tmp.EqMatrix(b), true);
}

TEST(Constructor, test_4) {
  S21Matrix a, b;
  a(0, 0) = 5;
  b(0, 0) = 5 * 5 / 5;
  EXPECT_EQ(a.EqMatrix(b), true);
}

TEST(Eq, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.3;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  b(1, 2) = 6.000003;
  EXPECT_EQ(tmp.S21GetCols(), b.S21GetCols());
  EXPECT_EQ(tmp.EqMatrix(b), false);
}

TEST(Eq, test_2) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix tmp = a;
  S21Matrix b(std::move(a));
  EXPECT_EQ(tmp.S21GetCols(), b.S21GetCols());
  EXPECT_EQ(tmp.EqMatrix(b), true);
}

TEST(Eq, test_3) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  a(1, 2) = 4.0;

  a(2, 0) = 2.0;
  a(2, 1) = 2.0;
  a(2, 2) = 4.0;

  S21Matrix b(2, 2);
  b = a;
  b.S21SetCols(3);
  b.S21SetRows(3);
  b(0, 2) = 4.0;
  b(1, 2) = 4.0;
  b(2, 0) = 2.0;
  b(2, 1) = 2.0;
  b(2, 2) = 4.0;

  EXPECT_EQ(a.S21GetCols(), b.S21GetCols());
  EXPECT_EQ(a.S21GetRows(), b.S21GetRows());
  EXPECT_EQ(a.EqMatrix(b), true);
}

TEST(SumMatrix, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SumMatrix(a);

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SumMatrix, test_2) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.S21SetCols(4);
  EXPECT_THROW(b.SumMatrix(a), std::length_error);
}

TEST(SumMatrix, test_3) {
  S21Matrix a(1, 15);
  S21Matrix b(1, 15);
  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      a(i, j) = i + j * 1.73;
    }
  }

  for (int i = 0; i < b.S21GetRows(); i++) {
    for (int j = 0; j < b.S21GetCols(); j++) {
      b(i, j) = i * 0.25 + j;
    }
  }

  a.SumMatrix(b);

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + (i + j * 1.73));
    }
  }
}

TEST(SubMatrix, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.SubMatrix(a);

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(SubMatrix, test_2) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b.S21SetCols(4);
  EXPECT_THROW(b.SubMatrix(a), std::length_error);
}

TEST(MulNumber, test_1) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b = a;
  b.MulNumber(3);

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(MulMatrix, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);

  b.MulMatrix(a);

  EXPECT_DOUBLE_EQ(b(0, 0), 74);
  EXPECT_DOUBLE_EQ(b(0, 1), 34);
  EXPECT_DOUBLE_EQ(b(0, 2), 20.000059999999998);
  EXPECT_DOUBLE_EQ(b(1, 0), 149.00036);
  EXPECT_DOUBLE_EQ(b(1, 1), 77.000149999999991);
  EXPECT_DOUBLE_EQ(b(1, 2), 74.000149999999991);
  EXPECT_DOUBLE_EQ(b(2, 0), 79);
  EXPECT_DOUBLE_EQ(b(2, 1), 49);
  EXPECT_DOUBLE_EQ(b(2, 2), 78.000149999999991);
}

TEST(MulMatrix, test_2) {
  S21Matrix a(1, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  S21Matrix b(3, 1);
  b(0, 0) = 2.0;
  b(1, 0) = 11.0;
  b(2, 0) = 12.0;

  a.MulMatrix(b);

  EXPECT_DOUBLE_EQ(a(0, 0), 74);
}

TEST(MulMatrix, test_3) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  S21Matrix result_full(4, 3);
  double res = 5.123f;

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      a(i, j) = 1.21030120f;
      b(i, j) = res * a(i, j);
    }
  }

  EXPECT_THROW(a.MulMatrix(b), std::length_error);
  b.S21SetRows(3);

  result_full = a * b;

  for (int i = 0; i < result_full.S21GetRows(); i++) {
    for (int j = 0; j < result_full.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(result_full(i, j), 22.512955999024761);
    }
  }
}

TEST(Transpose, test_1) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  S21Matrix result_full(3, 3);
  S21Matrix result1;
  S21Matrix result2;

  a(0, 0) = 0;
  a(0, 1) = 1;
  a(1, 0) = 2;
  a(1, 1) = 8;
  a(2, 0) = 7;
  a(2, 1) = 3;

  b(0, 0) = 5;
  b(0, 1) = 1;
  b(0, 2) = 2;
  b(1, 0) = 3;
  b(1, 1) = 7;
  b(1, 2) = 3;

  result1 = a * b;

  result_full(0, 0) = 3;
  result_full(0, 1) = 34;
  result_full(0, 2) = 44;
  result_full(1, 0) = 7;
  result_full(1, 1) = 58;
  result_full(1, 2) = 28;
  result_full(2, 0) = 3;
  result_full(2, 1) = 28;
  result_full(2, 2) = 23;

  result2 = result1.Transpose();
  EXPECT_EQ(result_full.EqMatrix(result2), true);
}

TEST(Transpose, test_2) {
  S21Matrix a(3, 5);
  S21Matrix result;

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(0, 4) = 5;
  a(1, 0) = 6;
  a(1, 1) = 7;
  a(1, 2) = 8;
  a(1, 3) = 9;
  a(1, 4) = 10;
  a(2, 0) = 11;
  a(2, 1) = 12;
  a(2, 2) = 13;
  a(2, 3) = 14;
  a(2, 4) = 15;

  result = a.Transpose();

  EXPECT_EQ(result.S21GetRows(), 5);
  EXPECT_EQ(result.S21GetCols(), 3);

  EXPECT_DOUBLE_EQ(a(0, 0), result(0, 0));
  EXPECT_DOUBLE_EQ(a(0, 1), result(1, 0));
  EXPECT_DOUBLE_EQ(a(0, 2), result(2, 0));
  EXPECT_DOUBLE_EQ(a(0, 3), result(3, 0));
  EXPECT_DOUBLE_EQ(a(0, 4), result(4, 0));

  EXPECT_DOUBLE_EQ(a(1, 0), result(0, 1));
  EXPECT_DOUBLE_EQ(a(1, 1), result(1, 1));
  EXPECT_DOUBLE_EQ(a(1, 2), result(2, 1));
  EXPECT_DOUBLE_EQ(a(1, 3), result(3, 1));
  EXPECT_DOUBLE_EQ(a(1, 4), result(4, 1));

  EXPECT_DOUBLE_EQ(a(2, 0), result(0, 2));
  EXPECT_DOUBLE_EQ(a(2, 1), result(1, 2));
  EXPECT_DOUBLE_EQ(a(2, 2), result(2, 2));
  EXPECT_DOUBLE_EQ(a(2, 3), result(3, 2));
  EXPECT_DOUBLE_EQ(a(2, 4), result(4, 2));
}

TEST(Transpose, test_3) {
  S21Matrix a(0, 5);
  EXPECT_THROW(a.Transpose(), std::length_error);
}

TEST(Determinant, test_1) {
  S21Matrix a(0, 0);
  EXPECT_THROW(a.Determinant(), std::length_error);
}

TEST(Determinant, test_2) {
  S21Matrix a(1, 2);
  EXPECT_THROW(a.Determinant(), std::length_error);
}

TEST(Determinant, test_3) {
  S21Matrix a(1, 1);
  a(0, 0) = 2.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 2.0);
}

TEST(Determinant, test_4) {
  double temp[2][2] = {{-1, 4}, {-5, 2}};
  S21Matrix a(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a(i, j) = temp[i][j];
    }
  }
  EXPECT_DOUBLE_EQ(a.Determinant(), 18.0);
}

TEST(Determinant, test_5) {
  S21Matrix a(3, 3);
  a(0, 0) = 73;
  a(0, 1) = 7;
  a(0, 2) = 6;
  a(1, 0) = 110;
  a(1, 1) = 16;
  a(1, 2) = 19;
  a(2, 0) = 148;
  a(2, 1) = 10;
  a(2, 2) = 7;

  EXPECT_DOUBLE_EQ(a.Determinant(), 992.0);
}

TEST(Determinant, test_6) {
  S21Matrix a(2, 2);
  a(0, 0) = -677700.0;
  a(0, 1) = 654.0;
  a(1, 0) = 2.0;
  a(1, 1) = -0.00001;

  S21Matrix b = a;
  EXPECT_DOUBLE_EQ(b.Determinant(), -1301.223);
}

TEST(Determinant, test_7) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  EXPECT_DOUBLE_EQ(a.Determinant(), 0);
}

TEST(Inverse, test_1) {
  S21Matrix a(4, 4);
  a(0, 0) = -1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 7.0;
  a(0, 3) = 9.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  a(1, 3) = 0.0;
  a(2, 0) = 47.0;
  a(2, 1) = 13.0;
  a(2, 2) = 17.0;
  a(2, 3) = 21.0;
  a(3, 0) = 22.0;
  a(3, 1) = 7.0;
  a(3, 2) = 1.0;
  a(3, 3) = 3.0;

  S21Matrix result(4, 4);
  result(0, 0) = 0.0;
  result(0, 1) = 1.0;
  result(0, 2) = 0.0;
  result(0, 3) = 0.0;
  result(1, 0) = -5.0 / 23.0;
  result(1, 1) = -121.0 / 23.0;
  result(1, 2) = 2.0 / 23.0;
  result(1, 3) = 1.0 / 23.0;
  result(2, 0) = -18.0 / 23.0;
  result(2, 1) = -379.0 / 46.0;
  result(2, 2) = 19.0 / 46.0;
  result(2, 3) = -25.0 / 46.0;
  result(3, 0) = 53.0 / 69.0;
  result(3, 1) = 1061.0 / 138.0;
  result(3, 2) = -47.0 / 138.0;
  result(3, 3) = 19.0 / 46.0;

  S21Matrix b = a.InverseMatrix();

  EXPECT_EQ(b.EqMatrix(result), true);
}

TEST(Inverse, test_2) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  a(2, 0) = 7.0;
  a(2, 1) = 8.0;
  a(2, 2) = 9.0;
  EXPECT_THROW(a.InverseMatrix(), std::length_error);
  S21Matrix b(0, 0);
  EXPECT_THROW(b.InverseMatrix(), std::length_error);
}

TEST(Calc, test_1) {
  S21Matrix a(4, 4);
  a(0, 0) = 112.0;
  a(0, 1) = 243.0;
  a(0, 2) = 3.0;
  a(0, 3) = -8.0;
  a(1, 0) = 47.0;
  a(1, 1) = 51.0;
  a(1, 2) = -66.0;
  a(1, 3) = 99.0;
  a(2, 0) = -74.0;
  a(2, 1) = 85.0;
  a(2, 2) = 97.0;
  a(2, 3) = 63.0;
  a(3, 0) = -13.0;
  a(3, 1) = 79.0;
  a(3, 2) = -99.0;
  a(3, 3) = -121.0;

  S21Matrix result(4, 4);
  result(0, 0) = -2879514.0;
  result(0, 1) = -1236631.0;
  result(0, 2) = -1685096.0;
  result(0, 3) = 880697.0;
  result(1, 0) = 1162090.0;
  result(1, 1) = -714015.0;
  result(1, 2) = 4046255.0;
  result(1, 3) = -3901600.0;
  result(2, 0) = 4362897.0;
  result(2, 1) = -2049432.0;
  result(2, 2) = -532912.0;
  result(2, 3) = -1370781.0;
  result(3, 0) = 3412773.0;
  result(3, 1) = -1569493.0;
  result(3, 2) = 3144517.0;
  result(3, 3) = 1284666.0;

  S21Matrix b;
  b = a.CalcComplements();
  EXPECT_EQ(b.EqMatrix(result), true);
}
TEST(Calc, test_2) {
  S21Matrix a(2, 2);
  S21Matrix b(0, 5);
  S21Matrix result(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  result(0, 0) = 4.0;
  result(0, 1) = -3.0;
  result(1, 0) = -2.0;
  result(1, 1) = 1.0;

  b = a.CalcComplements();

  for (int i = 0; i < b.S21GetRows(); i++) {
    for (int j = 0; j < b.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(b(i, j), result(i, j));
    }
  }
}

TEST(SumOperator, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b + a;

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }

  b = b - a;
  b += a;

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) - a(i, j));
    }
  }
}

TEST(SubOperator, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b = b - a;

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }

  b = b + a;
  b -= a;

  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j), b(i, j) + a(i, j));
    }
  }
}

TEST(MulNumOperator, test_1) {
  S21Matrix a(3, 4);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  S21Matrix tmp = b;
  b = b * 3;
  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b = 3 * b;
  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }

  b = tmp;
  b *= 3;
  for (int i = 0; i < a.S21GetRows(); i++) {
    for (int j = 0; j < a.S21GetCols(); j++) {
      EXPECT_DOUBLE_EQ(a(i, j) * 3, b(i, j));
    }
  }
}

TEST(EqOperator, test_1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  EXPECT_EQ(a.S21GetCols(), b.S21GetCols());

  EXPECT_EQ(b == a, true);
}

TEST(EqOperator, test_2) {
  S21Matrix a(3, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(0, 2) = 4.0;

  a(1, 0) = 11.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.00003;

  a(2, 0) = 12.0;
  a(2, 1) = 5.0;
  a(2, 2) = 0.0;

  S21Matrix b(a);
  b(0, 0) = a(0, 0) - 1.00001;
  b(1, 2) = a(1, 2) - 0.00001;
  b(2, 2) = a(2, 2) + 0.00001;

  EXPECT_EQ(b == a, false);
}

void InitMatrix(S21Matrix *matrix, double num) {
  for (int i = 0; i < matrix->S21GetRows(); i++) {
    for (int j = 0; j < matrix->S21GetCols(); j++) {
      (*matrix)(i, j) = num;
    }
  }
}

void InitMatrix2(S21Matrix *matrix, double num) {
  for (int i = 0; i < matrix->S21GetRows(); i++) {
    for (int j = 0; j < matrix->S21GetCols(); j++) {
      (*matrix)(i, j) = num;
      num++;
    }
  }
}

void InitMatrix3(S21Matrix *matrix) {
  double num = 1;
  for (int i = 0; i < matrix->S21GetRows(); i++) {
    for (int j = 0; j < matrix->S21GetCols(); j++) {
      if (i == 0 && j > 0)
        (*matrix)(i, j) = 3;
      else
        (*matrix)(i, j) = num;
      num++;
    }
  }
}

TEST(Operation, eqMatrix) {
  S21Matrix matrix1;
  matrix1.S21SetRows(3);
  matrix1.S21SetCols(3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.4765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix2) {
  S21Matrix matrix1 = S21Matrix(3, 3);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.4765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix3) {
  S21Matrix matrix1 = S21Matrix(3, 4);
  S21Matrix matrix2 = S21Matrix(3, 3);
  InitMatrix(&matrix1, 48.5765765);
  InitMatrix(&matrix2, 48.5765765);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, sumMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 18.4765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.553153);
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sum));
}

TEST(Operation, sumMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sum = S21Matrix(5, 5);
  InitMatrix(&matrix1, 25.7765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sum, 33.4765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sum));
}

TEST(Operation, subMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 35.6000000);
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sub));
}

TEST(Operation, subMatrix2) {
  S21Matrix matrix1 = S21Matrix(5, 5);
  S21Matrix matrix2 = S21Matrix(5, 5);
  S21Matrix sub = S21Matrix(5, 5);
  InitMatrix(&matrix1, 50.6765765);
  InitMatrix(&matrix2, 15.0765765);
  InitMatrix(&sub, 11.5765765);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sub));
}

TEST(Operation, mulMatrix) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix matrix2 = S21Matrix(4, 6);
  S21Matrix mul = S21Matrix(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&mul, -16);
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix mul = S21Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  matrix1.MulNumber(16);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber2) {
  S21Matrix matrix1 = S21Matrix(5, 4);
  S21Matrix mul = S21Matrix(5, 4);
  InitMatrix(&matrix1, -1);
  InitMatrix(&mul, -16);
  S21Matrix result = S21Matrix(16 * matrix1);
  EXPECT_TRUE(result.EqMatrix(mul));
}

TEST(Operation, transpose) {
  S21Matrix matrix = S21Matrix(7, 3);
  S21Matrix res = S21Matrix(3, 7);
  InitMatrix(&matrix, -1);
  InitMatrix(&res, -1);
  S21Matrix transpose = matrix.Transpose();
  EXPECT_TRUE(transpose.EqMatrix(res));
}

TEST(Operation, calcComplements) {
  S21Matrix matrix = S21Matrix(3, 3);
  S21Matrix dop = S21Matrix(3, 3);
  InitMatrix2(&matrix, 1);
  dop(0, 0) = -3.0;
  dop(0, 1) = 6.0;
  dop(0, 2) = -3.0;
  dop(1, 0) = 6.0;
  dop(1, 1) = -12;
  dop(1, 2) = 6;
  dop(2, 0) = -3;
  dop(2, 1) = 6;
  dop(2, 2) = -3;
  S21Matrix res = matrix.CalcComplements();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, inverseMatrix) {
  S21Matrix matrix = S21Matrix(3, 3);
  InitMatrix3(&matrix);
  S21Matrix dop = S21Matrix(3, 3);
  dop(0, 0) = -1.0 / 2.0;
  dop(0, 1) = -1.0 / 2.0;
  dop(0, 2) = 1.0 / 2.0;
  dop(1, 0) = 1.0;
  dop(1, 1) = -2.0;
  dop(1, 2) = 1.0;
  dop(2, 0) = -1.0 / 2.0;
  dop(2, 1) = 13.0 / 6.0;
  dop(2, 2) = -7.0 / 6.0;
  S21Matrix res = matrix.InverseMatrix();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, operatorSum) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  S21Matrix sum = matrix1 + matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSum2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 3;
  dop(1, 0) = 5;
  dop(1, 1) = 7;
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(dop));
}

TEST(Operation, operatorSub) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  S21Matrix sum = matrix1 - matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSub2) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix2(&matrix1, 1);
  InitMatrix2(&matrix2, 0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulMatrix) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  S21Matrix mul = matrix1 * matrix2;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulMatrix2) {
  S21Matrix matrix1(5, 4);
  S21Matrix matrix2(4, 6);
  S21Matrix dop(5, 6);
  InitMatrix(&matrix1, -1);
  InitMatrix(&matrix2, 4);
  InitMatrix(&dop, -16);
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulNumber) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  S21Matrix mul = matrix * 4;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulNumber2) {
  S21Matrix matrix(2, 2);
  S21Matrix dop(2, 2);
  InitMatrix(&matrix, 1);
  InitMatrix(&dop, 4);
  matrix *= 4;
  EXPECT_TRUE(matrix == dop);
}

TEST(GetAndSet, setSize) {
  S21Matrix matrix1(3, 6);
  S21Matrix matrix2(5, 4);
  matrix2.S21SetRows(3);
  matrix2.S21SetCols(6);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, getRows) {
  S21Matrix matrix(4, 7);
  int rows = matrix.S21GetRows();
  EXPECT_TRUE(rows == 4);
}

TEST(GetAndSet, getCols) {
  S21Matrix matrix(4, 7);
  int cols = matrix.S21GetCols();
  EXPECT_TRUE(cols == 7);
}

TEST(Construct, moveMatrix) {
  S21Matrix matrix(4, 5);
  InitMatrix2(&matrix, 1);
  S21Matrix dop(matrix);
  S21Matrix result(std::move(matrix));
  EXPECT_TRUE(result == dop);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}