#include "Matrix.h"



Matrix :: Matrix ()
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			mat[r][c] = 0.0f;
		}
	}
	mat[0][0] = 1.0f;
	mat[1][1] = 1.0f;
	mat[2][2] = 1.0f;
	mat[3][3] = 1.0f;
}

Matrix :: Matrix (float x)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			mat[r][c] = 0.0f;
		}
	}
	mat[0][0] = x;
	mat[1][1] = x;
	mat[2][2] = x;
	mat[3][3] = x;
}

Matrix :: Matrix (float x, float y, float z, float w)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			mat[r][c] = 0.0f;
		}
	}
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;
	mat[3][3] = w;
}

Matrix :: Matrix (float x0, float x1, float x2, float x3, 
				float y0, float y1, float y2, float y3,
				float z0, float z1, float z2, float z3,
				float w0, float w1, float w2, float w3)
{
	mat[0][0] = x0;
	mat[0][1] = x1;
	mat[0][2] = x2;
	mat[0][3] = x3;
	mat[1][0] = y0;
	mat[1][1] = y1;
	mat[1][2] = y2;
	mat[1][3] = y3;
	mat[2][0] = z0;
	mat[2][1] = z1;
	mat[2][2] = z2;
	mat[2][3] = z3;
	mat[3][0] = w0;
	mat[3][1] = w1;
	mat[3][2] = w2;
	mat[3][3] = w3;
}

Matrix :: Matrix (float m[4][4])
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			mat[r][c] = m[r][c];
		}
	}
}

Matrix Matrix :: add (const Matrix& m1, const Matrix& m2)
{
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			newMatrix.mat[r][c] = m1.mat[r][c] + m2.mat[r][c];
		}
	}
	return newMatrix;
	
}

Matrix Matrix :: subtract (const Matrix& m1, const Matrix& m2)
{
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			newMatrix.mat[r][c] = m1.mat[r][c] - m2.mat[r][c];
		}
	}
	return newMatrix;
}

Matrix Matrix :: multiply (float mul, const Matrix& m)
{
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			newMatrix.mat[r][c] = m.mat[r][c] * mul;
		}
	}
	return newMatrix;
}

Matrix Matrix :: divide (float div, const Matrix& m)
{
	if (div == 0)
	{
		return m;
	}
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			newMatrix.mat[r][c] = m.mat[r][c] / div;
		}
	}
	return newMatrix;
}

Matrix Matrix :: transpose (const Matrix& m)
{
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			newMatrix.mat[r][c] = m.mat[c][r];
		}
	}
	return newMatrix;
}

Matrix Matrix :: multiplyMatrix (const Matrix& m1, const Matrix& m2)
{
	Matrix newMatrix = Matrix(0.0f);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			for (int x = 0; x < 4; x++)
			{
				newMatrix.mat[r][c] += m1.mat[r][x] * m2.mat[x][c];
			}
		}
	}
	return newMatrix;
}

Vector Matrix :: multiplyVector (const Matrix& m, const Vector& v)
{
	Matrix vec = Matrix(v.x, v.y, v.z, 0.0f, 
						0.0f, 0.0f, 0.0f, 0.0f, 
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f);
	Matrix multiplied = Matrix :: multiplyMatrix(m, vec);
	return Vector(multiplied.mat[0][1], multiplied.mat[0][1], multiplied.mat[0][2]);
}

Vector Matrix :: multiplyVector (const Vector& v, const Matrix& m)
{
	Matrix vec = Matrix(v.x, 0.0f, 0.0f, 0.0f, 
						v.y, 0.0f, 0.0f, 0.0f, 
						v.z, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f);
	Matrix multiplied = Matrix :: multiplyMatrix(vec, m);
	return Vector(multiplied.mat[0][0], multiplied.mat[1][0], multiplied.mat[2][0]);
}

Matrix Matrix :: cofactor (const Matrix& m, int row, int col, int size)
{
	Matrix newMatrix = Matrix();
	int tempRow = 0;
	for (int r = 0; r < size; r++)
	{
		int tempCol = 0;
		for (int c = 0; c < size; c++)
		{
			if (r != row && c != col)
			{
				newMatrix.mat[tempRow][tempCol] = m.mat[r][c];
			}
			if (c != col)
			{
				tempCol++;
			}
		}
		if (r != row)
		{
			tempRow++;
		}
	}
	return newMatrix;
}

float Matrix :: determinant (const Matrix& m, int size)
{
	float det = 0;
	if (size == 2)
	{
		det = (m.mat[0][0] * m.mat[1][1]) - (m.mat[0][1] * m.mat[1][0]);
	}
	else
	{
		for (int col = 0; col < size; col++)
		{
			Matrix cof = Matrix :: cofactor(m, 0, col, size);

			det += pow(-1, col) * m.mat[0][col] * Matrix :: determinant(cof, size - 1);
		}
	}
	return det;
}

Matrix Matrix :: inverse (const Matrix& m)
{
	float temp[4][4];
	float determinant = Matrix :: determinant(m, 4);
	if (determinant == 0)
	{
		return temp;
	}
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			Matrix cof = Matrix :: cofactor(m, r, c, 4);
			temp[r][c] = Matrix :: determinant(cof, 3);
		}
	}
	Matrix tempMatrix = Matrix(temp);
	Matrix tempTransposed = Matrix :: transpose(tempMatrix);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			tempTransposed.mat[r][c] *= pow(-1, r + c);
		}
	}
	return Matrix :: divide (determinant, tempTransposed);
}

/*
debugging: print matrix
for (int r = 0; r < 4; r++)
{
	for (int c = 0; c < 4; c++)
	{
		//cout << " r: " << r << " c: " << c << " | " << matrix.mat[r][c];
		cout << " " << matrix.mat[r][c];
	}
	cout << endl;
}
*/

			