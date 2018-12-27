/*=====================================================================================================================================
FileName: Le_Pointer_Oct2018.c
FileType: C Source File
Author : Dung Le
Created On : 10/11/2018 9:00:00 AM
Last Modified On : 11/18/2018 11:04:25 PM
Description : Counts lines and triangles using user-inputted points on a coordinate plane.
Editor: Notepad++ Ver. 7.5.9
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 		1
#define FALSE 		0

/*
	Starts program with description
*/
void starter()
{
	printf("This program calculates how many lines and points are possible on a cartesian plane\n");
	printf("User inputs points on the cartesian plane, program returns total of points, lines, and triangles that are possible\n");
}	

/*
	Allows user to enter the amount of points 
*/
void amount_points(int *pts)
{
points:	
	printf("\nHow many points do you want to graph? ");
	scanf(" %d", pts);
	if(pts < 0){
		printf("You cannot graph a negative number of points, please try again\n");
		goto points;
	}	
}

/*
	Allows user to plot desired number of points on X Y coordinate
*/
void locate_point(float *x, float *y, int rep)
{
	printf("Point %d location:\n", rep + 1);
	printf("x = ");
	scanf(" %f", x);
	printf("y = ");
	scanf(" %f", y);	
}

/*
	Calculates A, B, and C values given two points
*/
void calc_abc(float x1, float y1, float x2, float y2, float *a, float *b, float *c)
{
	*a = y2 - y1;
	*b = x1 - x2;
	*c = x2 * y1 - x1 * y2;
}	

/*
	Checks for points congruency
*/
int check_dup_pts(float x1, float y1, float x2, float y2)
{
	if((x1 == x2) && (y1 == y2))
		return TRUE;
	else
		return FALSE;
}	

/*
	Checks for line congruency using A, B, and C values
*/
int check_dup_lines(float a1, float b1, float c1, float a2, float b2, float c2)
{
	float a1_cmp, b1_cmp, c1_cmp, a2_cmp, b2_cmp, c2_cmp;
	
	if((a1 == 0) && (a2 == 0) && (c1 == 0) && (c2 == 0)){
		return TRUE;
	}	
	if((b1 == 0) && (b2 == 0) && (c1 == 0) && (c2 == 0)){
		return TRUE;
	}
	if((a1 != 0) && (a2 != 0)){
		a1_cmp = a1 * a2;
		b1_cmp = b1 * a2;
		c1_cmp = c1 * a2;
		
		a2_cmp = a2 * a1;
		b2_cmp = b2 * a1;
		c2_cmp = c2 * a1;
	} else{
		if((b1 != 0) && (b2 != 0)){
			a1_cmp = a1 * b2;
			b1_cmp = b1 * b2;
			c1_cmp = c1 * b2;
			
			a2_cmp = a2 * b1;
			b2_cmp = b2 * b1;
			c2_cmp = c2 * b1;
		} else{
			return FALSE;
		}	
	}
	if((a1_cmp == a2_cmp) && (b1_cmp == b2_cmp) && (c1_cmp == c2_cmp)){
		return TRUE;
	}	
	else
		return FALSE;
}	

int main()
{
	int num_pts, num_lines, index, duplicate, pts_ctr, lines_ctr, tri_ctr;
	
	float x, y;
	float *x_ori, *y_ori;	//Stores user-inputted x and y coordinate values 
	float *x_ori_ptr, *y_ori_ptr;	//Pointers to x and y coordinate arrays
	
	float *x_fin, *y_fin;	//Stores non-duplicated x and y coordinate values 
	float *x_fin_ptr_cmp, *y_fin_ptr_cmp;	//Comparing pointers in x_fin and y_fin arrays
	float *x_fin_ptr, *x2_fin_ptr, *y_fin_ptr, *y2_fin_ptr, *x3_fin_ptr, *y3_fin_ptr;	//Pointers to x_fin and y_fin
	float *x_fin_end, *y_fin_end; //Final index of array
	
	float *A_ori, *B_ori, *C_ori;	//Stores all possible combinations of lines made from user-inputted points
	float *A_ori_ptr, *B_ori_ptr, *C_ori_ptr;	//Pointers to original A, B, and C arrays
	
	float *A_fin, *B_fin, *C_fin;	//Stores all possible non-repeating lines, or final A, B, and C values
	float *A_fin_ptr, *B_fin_ptr, *C_fin_ptr;	//Points to A_fin, B_fin, C_fin
	float *A_fin_ptr_cmp, *B_fin_ptr_cmp, *C_fin_ptr_cmp;	//Comparing pointer in A_fin, B_fin, and C_fin
	
	float A1_value, B1_value, C1_value, A2_value, B2_value, C2_value;
 	
	//Points, Lines, Triangles counter set to 0
	pts_ctr = 0;
	lines_ctr = 0;
	tri_ctr = 0;
	
	starter();
	amount_points(&num_pts);
	
/*
	Put x & y coordinates in separate arrays
*/
	/*Assigning 2 arrays to store x and y coordinates separately*/
	x_ori = malloc(num_pts * sizeof(float));																	//malloc 1
	y_ori = malloc(num_pts * sizeof(float));																	//malloc 2
	
	/*Storing user-inputted values into x and y arrays*/
	for(index = 0; index < num_pts; index++){
		locate_point(&x, &y, index);
		*(x_ori + index) = x;
		*(y_ori + index) = y;
	}
	
/*
	Eliminate all repeated points and store final x & y arrays
*/	
	/*Assigns two new arrays contain non-repeating x and y values*/
	x_fin = malloc(num_pts * sizeof(float)); 																	//malloc 3
	y_fin = malloc(num_pts * sizeof(float)); 																	//malloc 4
	
	//Assigns pointers to first values of each array   
	x_ori_ptr = x_ori; 
	y_ori_ptr = y_ori;
	x_fin_ptr = x_fin;
	y_fin_ptr = y_fin;
	
	//Assigning first x and y coordinate values of original array to final x and y arrays
	*x_fin_ptr++ = *x_ori_ptr++;
	*y_fin_ptr++ = *y_ori_ptr++;
	pts_ctr++;
	
	for(index = 1; index < num_pts; index++){
		for(x_fin_ptr_cmp = x_fin, y_fin_ptr_cmp = y_fin; x_fin_ptr_cmp < x_fin_ptr; x_fin_ptr_cmp++, y_fin_ptr_cmp++){
			//Checks duplicate for points. Assigns duplicate to true if points are the same
			duplicate = check_dup_pts(*x_ori_ptr, *y_ori_ptr, *x_fin_ptr_cmp, *y_fin_ptr_cmp);
			if(duplicate)
				break;	
		}	
		/*Adds values from x_ori and y_ori to x_fin and y_fin if duplicate is false*/
		if(!duplicate){
			//value in x_ori and y_ori is moved to x_fin and y_fin; x_fin and y_fin moves onto next value
			*x_fin_ptr++ = *x_ori_ptr;	
			*y_fin_ptr++ = *y_ori_ptr;
			pts_ctr++;
		}
		/*Moves on to next comparing value*/
		x_ori_ptr++;
		y_ori_ptr++;
	}	
	/*Assigning ending pointers to final indexes*/
	x_fin_end = x_fin_ptr;
	y_fin_end = y_fin_ptr;
	
	/*Resets x_fin and y_fin pointers*/
	x_ori_ptr = x_ori;
	y_ori_ptr = y_ori;
	x_fin_ptr = x_fin;
	y_fin_ptr = y_fin;
	
	x_fin_ptr_cmp = x_fin;
	y_fin_ptr_cmp = y_fin;
	
	free(y_ori);
	free(x_ori);	
/*
	Finds all possible lines between two points and puts them into 3 separate arrays based on equation Ax + By + C = 0
*/	
	if(pts_ctr >= 2){
		/*Finding total number of lines, including duplicates. Follows form num_lines = (n * (n - 1))/2*/
		num_lines = (pts_ctr * (pts_ctr - 1))/2;
		
		/*Assigns A, B, and C arrays with maximum size of total lines possible*/
		A_ori = malloc(num_lines * sizeof(float));																//malloc 5
		B_ori = malloc(num_lines * sizeof(float));																//malloc 6
		C_ori = malloc(num_lines * sizeof(float));																//malloc 7
		
		/*Assigning pointers to first index of each array*/
		A_ori_ptr = A_ori;
		B_ori_ptr = B_ori;
		C_ori_ptr = C_ori;
		
		for(index = 0; index < pts_ctr; index++){
			/*Finds equation of straight lines using all possible combinations of points*/
			for(x2_fin_ptr = x_fin_ptr + 1, y2_fin_ptr = y_fin_ptr + 1; x2_fin_ptr < x_fin_end; x2_fin_ptr++, y2_fin_ptr++){
				calc_abc(*x_fin_ptr, *y_fin_ptr, *x2_fin_ptr, *y2_fin_ptr, A_ori_ptr, B_ori_ptr, C_ori_ptr);
				A_ori_ptr++;
				B_ori_ptr++;
				C_ori_ptr++;
			}	
			x_fin_ptr++;
			y_fin_ptr++;
		}		 

/*
	Eliminates all repeated points and puts them into new A, B and C arrays
*/	
	
		/*Assigns final A, B, and C arrays with maximum size of total lines possible*/
		A_fin = malloc(num_lines * sizeof(float)); 																//malloc 8
		B_fin = malloc(num_lines * sizeof(float));																//malloc 9
		C_fin = malloc(num_lines * sizeof(float));																//malloc 10
			
		/*Initiate A_fin_ptr, B_fin_ptr, C_fin_ptr to first index values of A_fin, B_fin, C_fin*/
		A_fin_ptr = A_fin;
		B_fin_ptr = B_fin;
		C_fin_ptr = C_fin;
		
		/*Reset pointers*/
		A_ori_ptr = A_ori;
		B_ori_ptr = B_ori;
		C_ori_ptr = C_ori;
		
		/*Set first values of original A, B, and C arrays, increases line pointer*/
		*A_fin_ptr++ = *A_ori_ptr++;
		*B_fin_ptr++ = *B_ori_ptr++;
		*C_fin_ptr++ = *C_ori_ptr++;
		lines_ctr++;

		for(index = 0; index < num_lines - 1; index++){
			for(A_fin_ptr_cmp = A_fin, B_fin_ptr_cmp = B_fin, C_fin_ptr_cmp = C_fin; A_fin_ptr_cmp < A_fin_ptr; A_fin_ptr_cmp++, B_fin_ptr_cmp++, C_fin_ptr_cmp++){
				//Checks for duplicate, assigns duplicate to true or false
				duplicate = check_dup_lines(*A_ori_ptr, *B_ori_ptr, *C_ori_ptr, *A_fin_ptr_cmp, *B_fin_ptr_cmp, *C_fin_ptr_cmp);	
				if(duplicate)
					break;
			}	
			if(!duplicate){
				*A_fin_ptr++ = *A_ori_ptr;
				*B_fin_ptr++ = *B_ori_ptr;
				*C_fin_ptr++ = *C_ori_ptr;
				
				lines_ctr++;
			}
			
			A_ori_ptr++;
			B_ori_ptr++;
			C_ori_ptr++;
		}	
		
		/*Reset Pointers*/
		A_ori_ptr = A_ori;
		B_ori_ptr = B_ori;
		A_
	} 
	//Free up allocated memory
	free(C_fin);
	free(B_fin);
	free(A_fin);
	free(C_ori);
	free(B_ori);
	free(A_ori);
	

/*
	Finds all possible triangles within the user-inputted points. Only executes if there are 3 or more different points
*/
	if(pts_ctr >= 3){
		for(x_fin_ptr = x_fin, y_fin_ptr = y_fin; x_fin_ptr < x_fin_end - 2; x_fin_ptr++, y_fin_ptr++){
			for(x2_fin_ptr = x_fin_ptr + 1, y2_fin_ptr = y_fin_ptr + 1; x2_fin_ptr < x_fin_end - 1; x2_fin_ptr++, y2_fin_ptr++){
				for(x3_fin_ptr = x2_fin_ptr + 1, y3_fin_ptr = y2_fin_ptr + 1; x3_fin_ptr < x_fin_end; x3_fin_ptr++, y3_fin_ptr++){
					/*
						Finds A, B, and C values of 2 lines from 3 points.
						If two lines are the same, then triangle cannot be made out of 3 points
					*/
					calc_abc(*x_fin_ptr, *y_fin_ptr, *x2_fin_ptr, *y2_fin_ptr, &A1_value, &B1_value, &C1_value);
					calc_abc(*x2_fin_ptr, *y2_fin_ptr, *x3_fin_ptr, *y3_fin_ptr, &A2_value, &B2_value, &C2_value);
					
					//Check for duplicate, assigns duplicate to true or false
					duplicate = check_dup_lines(A1_value, B1_value, C1_value, A2_value, B2_value, C2_value);
					if(!duplicate)
						tri_ctr++;
				}
			}
		}
	}
	printf("There are %d different point(s)\nThere can be %d line(s) made\nThere can be %d triangle(s) made\n", pts_ctr, lines_ctr, tri_ctr);
	
	free(y_fin);
	free(x_fin);
	
	return 0;
}	

 

