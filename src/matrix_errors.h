#pragma once

/**
 * @def MATRIX_ERRORS(X)
 * @brief Generator macro containing all matrix error definitions.
 *
 * @param X A macro that defines how each item in the list should be expanded.
 * The X macro is in this form: `X(enum_name, error_string)`.
 *
 * @par Example 1: Generating the Enum
 * @code
 * // 1. Define what X does (extracts the enum_name)
 * #define X(enum_name, error_string) enum_name,
 * * // 2. Call the master list to expand
 * typedef enum {
 * MATRIX_ERRORS(X)
 * } MatrixStatus;
 * * // 3. Clean up
 * #undef X
 * @endcode
 *
 * @par Example 2: Generating the String Array
 * @code
 * // 1. Define what X does differently (extracts the error_string)
 * #define X(enum_name, error_string) error_string,
 * * // 2. Call the master list to expand
 * static const char* const MATRIX_ERROR_MESSAGES[] = {
 * MATRIX_ERRORS(X)
 * };
 * * // 3. Clean up
 * #undef X
 * @endcode
 */
#define MATRIX_ERRORS(X)                                                                                               \
    X(MATRIX_OK, "Operation completed successfully.")                                                                  \
    X(MATRIX_ERR_DIMENSIONS, "Incompatible matrix dimensions for this operation.")                                     \
    X(MATRIX_ERR_NULL_PTR, "A null pointer was passed to the function.")                                               \
    X(MATRIX_ERR_ALLOCATION, "Failed to allocate memory for the matrix.")                                              \
    X(MATRIX_ERR_OUT_OF_BOUNDS, "Attempted to access an index out of matrix bounds.")
