#pragma once

/**
 * @def MATRIX_ERRORS(X)
 * @brief Generator macro containing all matrix error definitions.
 *
 * @param X A macro in the form `X(enum_name, error_string)`.
 */
#define MATRIX_ERRORS(X)                                                           \
    X(MATRIX_OK, "Operation completed successfully.")                              \
    X(MATRIX_ERR_DIMENSIONS, "Incompatible matrix dimensions for this operation.") \
    X(MATRIX_ERR_NULL_PTR, "A null pointer was passed to the function.")           \
    X(MATRIX_ERR_ALLOCATION, "Failed to allocate memory for the matrix.")          \
    X(MATRIX_ERR_NOT_INVERTIBLE, "The matrix is not invertible")                   \
    X(MATRIX_ERR_OUT_OF_BOUNDS, "Attempted to access an index out of matrix bounds.")
