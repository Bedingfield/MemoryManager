/*
Program by Jonathan Bedingfield
2/21/20
Matrix using Memory Manager
*/

//#ifndef matrix
//#define matrix

#include "mm.h"

typedef struct matrix
{
	int num_rows;
	int num_cols;
	double* elements;
} matrix;

matrix* matrix_malloc(int num_rows, int num_cols)
{
	int size = sizeof(matrix);//(8 + (num_rows * num_cols * 8));
	int big = (num_cols * num_rows * 8);
	
	matrix* mat = (matrix*) mem_manager_malloc(size);
	
	if(mat != NULL)
	{
		mat->elements = (double *) mem_manager_malloc(big);
		mat->num_rows = num_rows;
		mat->num_cols = num_cols;
	}
	return mat;
}

void matrix_free(matrix* mat)
{
	if(mat != NULL)
	{
		mem_manager_free(mat->elements);
		mem_manager_free(mat);
	}
}

void set_element(matrix* mat, int row, int col, double val)
{
	int index;
	index = (((row-1)*mat->num_cols) + col - 1);
	double* elements = mat->elements;
	
	elements[index] = val;
}

double get_element(matrix* mat, int row, int col)
{
	int index;
	index = (((row-1)*mat->num_cols) + col - 1);
	double toad = mat->elements[index];
	return toad;
}

void display(matrix* mat)//print every double in the matrix
{
	int counter = 0;
	for(int i = 0; i < mat->num_rows; i++)
	{
		for(int j = 0; j < mat->num_cols; j++)
		{
			cout << mat->elements[counter] << " ";
			counter++;
		}
		cout << endl;
	}
}

//left cols has to be the same as right rows for matrix multiplication
matrix* multiply(matrix* left, matrix* right)
{
	int left_rows = left->num_rows;
	int left_cols = left->num_cols;
	int right_rows = right->num_rows;
	int right_cols = right->num_cols;
	matrix* result = matrix_malloc(left_rows, right_cols);
	
	for (int i = 1; i <= left_rows; i++)
	{
		for (int j = 1; j <= right_cols; j++)
		{
			double val = 0;
			for (int k = 1; k <= left_cols; k++)
			{
				double element_left = get_element(left, i, k);
				double element_right = get_element(right, k, j);
				double mul = element_left * element_right;
				val += mul;
			}
			set_element(result, i, j, val);
		}
	}
	
	return result;
}

//#endif