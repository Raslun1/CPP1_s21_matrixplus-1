#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 1;
  cols_ = 1;
  S21MakeMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (rows < 0 || cols < 0) {
    throw std::length_error("incorrect matrix");
  }
  S21MakeMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  if (other.matrix_) {
    S21MakeMatrix();
    S21CopyMatrix(other.matrix_, other.rows_, other.cols_);
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  S21MakeMatrix();
  S21CopyMatrix(other.matrix_, other.rows_, other.cols_);
  other.S21DelMatrix();
}

S21Matrix::~S21Matrix() { S21DelMatrix(); }

void S21Matrix::S21MakeMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  S21FillingMatrix();
}

void S21Matrix::S21FillingMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

void S21Matrix::S21DelMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }

  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::S21CopyMatrix(double** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = matrix[i][j];
    }
  }
}

int S21Matrix::S21GetRows() const noexcept { return rows_; }

int S21Matrix::S21GetCols() const noexcept { return cols_; }

void S21Matrix::S21SetRows(int rows) {
  if (rows < 0) {
    throw std::length_error("Invalid rows");
  } else {
    S21Matrix temp_matrix = *this;
    S21DelMatrix();
    this->rows_ = rows;
    cols_ = temp_matrix.cols_;
    S21MakeMatrix();
    S21CopyMatrix(temp_matrix.matrix_, std::min(this->rows_, temp_matrix.rows_),
                  cols_);
  }
}

void S21Matrix::S21SetCols(int cols) {
  if (cols < 0) {
    throw std::length_error("Invalid cols");
  } else {
    S21Matrix temp_matrix = *this;
    S21DelMatrix();
    rows_ = temp_matrix.rows_;
    this->cols_ = cols;
    S21MakeMatrix();
    S21CopyMatrix(temp_matrix.matrix_, rows_,
                  std::min(this->cols_, temp_matrix.cols_));
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = (rows_ == other.rows_ && cols_ == other.cols_) ? true : false;

  if (res) {
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_ && res; j++) {
        res = (std::abs(matrix_[i][j] - other.matrix_[i][j]) < 1e-7) ? true
                                                                     : false;
      }
    }
  }

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error("incorrect matrix");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error("incorrect matrix");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::length_error("incorrect matrix");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ < 1 || other.rows_ < 1 || cols_ < 1 || other.cols_ < 1 ||
      cols_ != other.rows_) {
    throw std::length_error("incorrect matrix");
  }

  S21Matrix resultMatrix(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        resultMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  S21SetCols(resultMatrix.cols_);
  S21CopyMatrix(resultMatrix.matrix_, resultMatrix.rows_, resultMatrix.cols_);
}

S21Matrix S21Matrix::Transpose() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::length_error("incorrect matrix");
  }

  S21Matrix resultMatrix(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      resultMatrix.matrix_[j][i] = matrix_[i][j];
    }
  }

  return resultMatrix;
}

double S21Matrix::S21Minor(S21Matrix& matrix, int crossed_row,
                           int crossed_col) {
  S21Matrix temp_matrix(matrix.rows_ - 1, matrix.cols_ - 1);
  int row = 0, col = 0;

  for (int i = 0; i < matrix.rows_; i++) {
    for (int j = 0; j < matrix.cols_ && i != crossed_row; j++) {
      if (j == crossed_col) {
        col++;
        continue;
      }
      temp_matrix.matrix_[row][j - col] = matrix.matrix_[i][j];
    }
    if (i != crossed_row) {
      row++;
    }
    col = 0;
  }

  double determinant = temp_matrix.Determinant();

  return determinant;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ < 1 || cols_ < 1 || rows_ != cols_) {
    throw std::length_error("incorrect matrix");
  }

  S21Matrix final_m(rows_, cols_);
  S21Matrix temp_matrix = *this;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      final_m.matrix_[i][j] = S21Minor(temp_matrix, i, j) * pow(-1, i + j);
    }
  }

  return final_m;
}

double S21Matrix::Determinant() {
  if (rows_ < 1 || cols_ < 1 || rows_ != cols_) {
    throw std::length_error("incorrect matrix");
  }

  double determinant = 0.0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant =
        (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  } else {
    int sign = 1;
    for (int i = 0; i < cols_; i++) {
      double minor = S21Minor(*this, 0, i);
      determinant += sign * matrix_[0][i] * minor;
      sign = -sign;
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = 0.0;
  determinant = Determinant();

  if (determinant == 0.0) {
    throw std::length_error("Determinant = 0");
  }

  S21Matrix mat_min = CalcComplements();
  S21Matrix res_matrix = mat_min.Transpose();

  for (int i = 0; i < res_matrix.cols_; i++) {
    for (int j = 0; j < res_matrix.rows_; j++) {
      res_matrix.matrix_[i][j] *= (1.0 / determinant);
    }
  }
  return res_matrix;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21DelMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    S21MakeMatrix();
    S21CopyMatrix(other.matrix_, rows_, cols_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    S21DelMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    S21MakeMatrix();
    S21CopyMatrix(other.matrix_, rows_, cols_);
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res = *this;
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(const double num, S21Matrix& other) {
  other *= num;
  return other;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= this->rows_ || j >= this->cols_) {
    throw std::length_error("Index out of range");
  }
  return this->matrix_[i][j];
}
