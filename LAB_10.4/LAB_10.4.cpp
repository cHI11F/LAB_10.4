#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Функція для зчитування матриці з файлу
vector<vector<int>> readMatrixFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        throw runtime_error("Error opening file: " + filename);
    }

    int rows, cols;
    fin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(fin >> matrix[i][j])) {
                fin.close();
                throw runtime_error("Error reading matrix from file: " + filename);
            }
        }
    }

    fin.close();
    return matrix;
}

// Функція для виведення матриці на екран
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Функція для збереження матриці у файл
void saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        throw runtime_error("Error opening file: " + filename);
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    fout << rows << " " << cols << endl;
    for (const auto& row : matrix) {
        for (int element : row) {
            fout << element << " ";
        }
        fout << endl;
    }

    fout.close();
}

// Функція для обчислення добутку двох матриць
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    if (cols1 != rows2) {
        throw invalid_argument("Matrices dimensions mismatch for multiplication");
    }

    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    string filename1, filename2, outputFilename;

    cout << "Enter first matrix filename: ";
    getline(cin, filename1);
    cout << "Enter second matrix filename: ";
    getline(cin, filename2);

    // Читання матриць з файлів
    vector<vector<int>> matrix1, matrix2;
    try {
        matrix1 = readMatrixFromFile(filename1);
        matrix2 = readMatrixFromFile(filename2);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Виведення матриць на екран
    cout << "Matrix 1:" << endl;
    printMatrix(matrix1);
    cout << "Matrix 2:" << endl;
    printMatrix(matrix2);

    // Обчислення добутку матриць
    vector<vector<int>> resultMatrix;
    try {
        resultMatrix = multiplyMatrices(matrix1, matrix2);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Виведення результату на екран
    cout << "Result Matrix:" << endl;
    printMatrix(resultMatrix);

    // Збереження результату у файл
    cout << "Enter output filename: ";
    cin >> outputFilename;
    try {
        saveMatrixToFile(resultMatrix, outputFilename);
        cout << "Result matrix has been saved to file: " << outputFilename << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}