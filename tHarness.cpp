/*
Program by Jonathan Bedingfield
2/21/20
Test Harness for Matrix,Memory Manager
*/

#include "matrix.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("%ld",sizeof(mmfree_t));
	int numBytes;
	cout << endl << "Enter the number of bytes to be used: ";
	cin >> numBytes;
	
	vector<matrix*> lenny;
	
	init_mem(numBytes);
	traverse_free_list();
	
	
	
	matrix* goop = matrix_malloc(2,2);
	traverse_free_list();
	set_element(goop,1,1,2.2);
	set_element(goop,1,2,2.3);
	set_element(goop,2,1,2.4);
	set_element(goop,2,2,2.5);
	matrix* goop2 = matrix_malloc(2,2);
	set_element(goop2,1,1,2.2);
	set_element(goop2,1,2,2.3);
	set_element(goop2,2,1,2.4);
	set_element(goop2,2,2,2.5);
	//cout << "afterCoreDump" << endl;
	matrix* temp = multiply(goop2,goop);
	display(temp);
	//display(goop);
	//traverse_free_list();
	matrix_free(goop);
	traverse_free_list();
	matrix_free(goop2);
	traverse_free_list();
	matrix_free(temp);
	traverse_free_list();
	
	goop = matrix_malloc(3,5);
	set_element(goop,1,1,1.0);
	set_element(goop,1,2,2.0);
	set_element(goop,1,3,3.0);
	set_element(goop,1,4,4.0);
	set_element(goop,1,5,5.0);
	
	set_element(goop,2,1,1.0);
	set_element(goop,2,2,2.0);
	set_element(goop,2,3,3.0);
	set_element(goop,2,4,4.0);
	set_element(goop,2,5,5.0);
	
	set_element(goop,3,1,1.0);
	set_element(goop,3,2,2.0);
	set_element(goop,3,3,3.0);
	set_element(goop,3,4,4.0);
	set_element(goop,3,5,5.0);
	display(goop);
	matrix_free(goop);
	
	traverse_free_list();
	matrix* temp2 = matrix_malloc(20,20);
	matrix_free(temp2);
	
	for(int i = 0; i < 50; i++)
	{
		lenny.push_back(matrix_malloc(2,3));
		cout << "at #" << i << endl;
		traverse_free_list();
	}
	
	traverse_free_list();
	
	for(int i = 0; i < 50; i++)
	{
		matrix_free(lenny[i]);
		traverse_free_list();
	}
	
	traverse_free_list();
	
	return 0;
}