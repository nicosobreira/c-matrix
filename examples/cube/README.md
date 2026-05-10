# 3D Render Cube

Renders a 3D Cube on the terminal, using ASCII characters.

## Angles Notation

- The angle between y and z is called *gama* $\gama$
- Between x and y is called *theta* $\theta$
- And between x and z is called *beta* $\beta$
- The original angle of a Point P is called *alpha* $\alpha$

## Rotation Matrices

Based on the angle notation above, the matrices are:

### X and Y rotation

$$
\begin{bmatrix}
cos(\theta) & -sen(\theta) & 0\\
sen(\theta) & cos(\theta) & 0\\
0 & 0 & 1
\end{bmatrix}
$$
