
#include "ex3.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

matrix *new_matrix_helper ();
void create_empty_matrix (matrix *p_matrix);

/**
 * create a new matrix_s on the heap.
 * @param n_rows number of rows in the new matrix_s.
 * @param n_columns number of columns in the new matrix_s.
 * @return A pointer to the new matrix_s struct.
 */
matrix *create_matrix (size_t n_rows, size_t n_columns)
{
    matrix *curr_matrix = new_matrix_helper();
    if (curr_matrix==NULL){return NULL;}

    if ((n_rows == 0)||(n_columns == 0))
    {
        create_empty_matrix (curr_matrix);
        return curr_matrix;
    }
    curr_matrix->data = malloc(sizeof(double*)*n_rows);
    if(curr_matrix->data == NULL)
    {
        free(curr_matrix);
        fprintf(stderr, "%s", "Error: unable to create new matrix!\n");
        return NULL;
    }
    for (size_t i = 0; i < n_rows; i++)
    {
        curr_matrix->data[i] = calloc (n_columns,sizeof(double));
        if(curr_matrix->data[i] == NULL)
        {
            i--;
            for(int j = (int)i; j >= 0; j--)
            {
                free (curr_matrix->data[j]);
            }
            free(curr_matrix->data);
            free(curr_matrix);
            fprintf(stderr, "%s", "Error: unable to create new matrix!\n");
            return NULL;
        }
    }
    curr_matrix ->n_rows = n_rows;
    curr_matrix ->n_columns = n_columns;
    return curr_matrix;
}
/**
 * Helper function which tries to create a new matrix struct
 * @return  a pointer to the new matrix if succeeded, NULL otherwise.
 */
matrix *new_matrix_helper ()
{
    matrix *curr_matrix = malloc(sizeof(matrix));
    if(curr_matrix == NULL)
        {
            fprintf(stderr, "%s", "Error: unable to create new matrix!\n");
            return NULL;
        }
    return curr_matrix;
}

/**
 * Get value based on index.
 * @param matrix
 * @param row_index
 * @param col_index
 * @return matrix_s[row_index, col_index],
 * NULL if the index is out of range.
 */
double *get_by_index (matrix *mat, size_t row_index, size_t col_index)
{
    if(row_index < (mat->n_rows))
    {
        if(col_index < (mat->n_columns))
        {
                return &(mat->data[row_index][col_index]);
        }
    }
    fprintf (stderr, "%s", "Error: non valid search index for given matrix\n");
    return NULL;
}


/**
 * Method slices a given matrix within the bounds of the given indices
 * and returns a new matrix containing the sliced rows and columns.
 * @param matrix
 * @param row_range
 * @param col_range
 * @return the new sliced matrix
 */
matrix *slice (matrix *mat, size_t row_start,
               size_t row_end, size_t col_start, size_t col_end){
    matrix *new_mat = new_matrix_helper();
    if(new_mat == NULL)
    {
            return NULL;
    }
    if((row_start >= (mat->n_rows))||(col_start >= (mat->n_columns))
    ||(mat->data == NULL)
    ||(row_start >= row_end)||(col_start >= col_end)
    ||(mat->n_rows == 0)|| (mat->n_columns == 0))
    {
        create_empty_matrix(new_mat);
        return new_mat;
    }
    size_t row_num;
    if(row_end > (mat->n_rows))
    {
        row_num = (mat->n_rows)-row_start;
        new_mat->data = malloc (sizeof (double *)*(row_num));
        if(new_mat->data == NULL){
            fprintf(stderr, "%s", "Error: unable to create new sliced matrix!\n");
            free(new_mat);
            return NULL;
        }
    }
    else
    {
        row_num = row_end-row_start;
        new_mat->data = malloc (sizeof (double *)*(row_num));
        if(new_mat->data == NULL){
                fprintf(stderr, "%s", "Error: unable to create new sliced matrix!\n");
                free (new_mat);
                return NULL;
            }
    }
    size_t col_num;
    if(col_end > (mat->n_columns))
        {
            col_num = (mat->n_columns)-col_start;
        }
    else
        {
            col_num = col_end-col_start;
        }
    for (size_t i = 0; i < row_num; i++)
    {
        new_mat->data[i] = malloc (col_num* sizeof (double ));
        if(new_mat->data[i] == NULL)
            {
                i--;
                for(int j = (int)i; j >= 0; j--)
                    {
                        free (new_mat->data[j]);
                    }
                free(new_mat->data);
                free(new_mat);
                fprintf(stderr, "%s", "Error: unable to create new sliced matrix!\n");
                return NULL;
            }
        for(size_t j = 0; j < col_num; j++)
        {
            new_mat->data[i][j] = mat->data[row_start+i][col_start+j];
        }
    }
    new_mat->n_rows = row_num;
    new_mat->n_columns = col_num;
    return new_mat;
}
/**
 * Helper function that receives a pointer to a matrix and initializes its
 * fields into an empty matrix.
 * @param p_matrix
 */
void create_empty_matrix (matrix *p_matrix)
{
    p_matrix->data = NULL;
    p_matrix->n_columns = 0;
    p_matrix->n_rows = 0;
}

/**
 * concatenates two matrices vertically
 * @param top
 * @param bottom
 * @return concatenated matrix
 */
matrix *concatenate_vertically (matrix *top, matrix *bottom)
{
    if(top->n_columns != bottom->n_columns)
    {
        fprintf(stderr, "%s", "Error: unable to concatenate vertically matrices with "
                              "different num of columns!\n");
        return NULL;
    }

    matrix *new_matrix = new_matrix_helper();
    if (new_matrix == NULL){return NULL;}
    if(((top->data == NULL)||((top->n_columns == 0)&&(top->n_rows == 0)))||
    ((bottom->data == NULL)||((bottom->n_columns == 0)&&(bottom->n_rows == 0))))
        {
            create_empty_matrix (new_matrix);
            return new_matrix;
        }
    size_t row_num = (top->n_rows) + (bottom->n_rows);
    new_matrix->data = malloc (sizeof (double *)*row_num);
    if (new_matrix->data == NULL)
    {
        fprintf(stderr, "%s", "Error: unable to concatenate matrices vertically right now!\n");
        return NULL;
    }
    for(size_t i = 0; i < row_num; i++){
        new_matrix->data[i] = malloc (sizeof (double)*(top->n_columns));
        if(new_matrix->data[i] == NULL)
        {
            i--;
            for(int j = (int)i; j >= 0; j--)
                {
                    free (new_matrix->data[j]);
                }
            free(new_matrix->data);
            free(new_matrix);
            fprintf(stderr, "%s", "Error: unable to create new sliced matrix!\n");
            return NULL;
        }
        for(size_t j = 0; j < top->n_columns; j++)
        {
            if(i < (top->n_rows))
            {
                new_matrix->data[i][j] = top->data[i][j];
            }
            else
            {
                new_matrix->data[i][j] = bottom->data[i-(top->n_rows)][j];
            }

        }
    }
    new_matrix->n_rows = row_num;
    new_matrix->n_columns = top->n_columns;
    return new_matrix;
}

/**
 * concatenates two matrices horizontally
 * @param left
 * @param right
 * @return concatenated matrix pointer
 */
matrix *concatenate_horizontally (matrix *left, matrix *right)
{
    if(left->n_rows != right->n_rows)
        {
            fprintf(stderr, "%s", "Error: unable to concatenate horizontally matrices with "
                                  "different num of rows!\n");
            return NULL;
        }
    matrix *new_matrix = new_matrix_helper();
    if (new_matrix == NULL){return NULL;}
    if(((left->data == NULL)||((left->n_columns == 0)&&(left->n_rows == 0)))||
       ((right->data == NULL)||((right->n_columns == 0)&&(right->n_rows == 0))))
        {
            create_empty_matrix (new_matrix);
            return new_matrix;
        }
    size_t col_num = (left->n_columns) + (right->n_columns);
    new_matrix->data = malloc (sizeof (double *)*(right->n_rows));
    if (new_matrix->data == NULL)
        {
            fprintf(stderr, "%s", "Error: unable to concatenate matrices"
                                  " vertically right now!\n");
            return NULL;
        }
    for(size_t i = 0; i < (left->n_rows) ; i++){
            new_matrix->data[i] = malloc (sizeof (double)*((left->n_columns)+
                (right->n_columns)));
            if(new_matrix->data[i] == NULL)
                {
                    i--;
                    for(int j = (int)i; j >= 0; j--)
                        {
                            free (new_matrix->data[j]);
                        }
                    free(new_matrix->data);
                    free(new_matrix);
                    fprintf(stderr, "%s", "Error: unable to create new sliced matrix!\n");
                    return NULL;
                }
            for(size_t j = 0; j < col_num; j++)
                {
                    if(j < (left->n_columns))
                        {
                            new_matrix->data[i][j] = left->data[i][j];
                        }
                    else
                        {
                            new_matrix->data[i][j] = right->data[i][j-(left->n_columns)];
                        }

                }
        }
    new_matrix->n_rows = (left->n_rows) ;
    new_matrix->n_columns = col_num;
    return new_matrix;
}

/**
 * transpose matrix
 * @param matrix
 * @return transposed matrix, NULL if error occurred.
 */
matrix *transpose (matrix *mat)
{
    matrix *new_matrix = new_matrix_helper();
    if(new_matrix == NULL){return NULL;}

    if((mat->data == NULL)||((mat->n_columns == 0)&&(mat->n_rows == 0)))
    {
        create_empty_matrix (new_matrix);
        return new_matrix;
    }
    new_matrix->data = malloc (sizeof (double *) * (mat->n_columns));
    if(new_matrix->data == NULL){
        free(new_matrix);
        fprintf(stderr, "%s", "Error: unable to transpose matrix right now!\n");
        return NULL;
    }
    for(size_t i = 0; i < mat->n_columns; i++)
    {
        new_matrix->data[i] = malloc ((mat->n_rows)*sizeof(double));
        if(new_matrix->data[i] == NULL)
        {
            i--;
            for(int j = (int)i; j >= 0; j--)
                {
                    free (new_matrix->data[j]);
                }
            free(new_matrix->data);
            free(new_matrix);
            fprintf(stderr, "%s", "Error: unable to create new matrix!\n");
            return NULL;
        }
        for(size_t j = 0; j < (mat->n_rows); j++){
            new_matrix->data[i][j] = mat->data[j][i];
        }
    }
    new_matrix ->n_rows = mat->n_columns;
    new_matrix ->n_columns = mat->n_rows;
    return new_matrix;
}
/**
 * returns raveled array with all the matrix entries.
 * @param matrix
 * @return raveled array
 */
double *ravel (matrix *mat){
    if((mat->data == NULL)||(mat->n_columns == 0)||(mat->n_rows == 0))
    {
        fprintf(stderr, "%s", "Error: unable to create new raveled array from empty matrix!\n");
        return NULL;
    }
    double *arr = malloc (sizeof (double )*(mat->n_columns)*(mat->n_rows));
    if (arr == NULL)
    {
        fprintf(stderr, "%s", "Error: unable to create new raveled array!\n");
        return NULL;
    }
    for(size_t i = 0; i < mat->n_rows; i++)
    {
        for(size_t j = 0; j < mat->n_columns; j++)
        {
            arr[j+((mat->n_columns)*i)] = mat->data[i][j];
        }
    }
    return arr;
}
/**
 * frees given matrix memory
 * @param matrix
 */
void free_matrix (matrix *mat)
{

    if(mat->data != NULL)
    {
        for(size_t i = 0; i < (mat->n_rows); i++)
        {
            if(mat->data[i] == NULL)
            {
                continue;
            }
            free(mat->data[i]);
        }
    }
    free(mat->data);
    free(mat);
}



