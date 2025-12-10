# Vector & Matrix Operations - Enhanced
# ----------------------------

# Vector operations
v <- c(1, 2, 3, 4, 5)
cat("Original vector:\n"); print(v)
cat("Vector multiplied by 2:\n"); print(v * 2)
cat("Cumulative sum:\n"); print(cumsum(v))
cat("Vector squared:\n"); print(v^2)
cat("Mean of vector:", mean(v), "\n\n")

# Matrix operations
m <- matrix(1:9, nrow=3)
cat("Original matrix:\n"); print(m)

cat("Transpose of matrix:\n"); print(t(m))
cat("Matrix squared (element-wise):\n"); print(m^2)
cat("Row sums:\n"); print(rowSums(m))
cat("Column means:\n"); print(colMeans(m))

# Matrix multiplication
m2 <- matrix(9:1, nrow=3)
cat("Second matrix:\n"); print(m2)
cat("Matrix multiplication (m %*% m2):\n"); print(m %*% m2)