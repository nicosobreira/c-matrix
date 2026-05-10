# 3D Render Cube

Renders a 3D Cube on the terminal, using ASCII characters.

## Angles Notation

- Between x and y is called *theta* $\theta$
- between x and z is called *beta* $\beta$
- Between y and z is called *gamma* $\gamma$

## Rotation Matrices

Based on the angle notation above, the matrices are:

### X and Y rotation

$$
\begin{matrix}
cos(\theta) & -sen(\theta) & 0 \\
sen(\theta) & cos(\theta)  & 0 \\
0           & 0            & 1
\end{matrix}
$$

### X and Z rotation

$$
\begin{matrix}
cos(\beta)  & 0 & sen(\beta) \\
0           & 1 & 0          \\
-sen(\beta) & 0 & cos(\beta)
\end{matrix}
$$

### Y and Z rotation

$$
\begin{matrix}
1 & 0           & 0            \\
0 & cos(\gamma) & -sen(\gamma) \\
0 & sen(\gamma) & cos(\gamma)
\end{matrix}
$$
