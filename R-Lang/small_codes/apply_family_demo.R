# Create a sample matrix
set.seed(123)  # reproducible results
m <- matrix(sample(1:20, 12), nrow = 3, byrow = TRUE)
cat("Matrix m:\n")
print(m)

# --- apply() examples ---
cat("\nRow sums using apply():\n")
print(apply(m, 1, sum))

cat("\nColumn means using apply():\n")
print(apply(m, 2, mean))

# --- lapply() & sapply() with a list ---
l <- list(
  scores = c(88, 92, 76, 81, 95),
  ages   = c(21, 25, 19, 22, 20),
  weights = c(65, 70, 68, 75, 72)
)

cat("\nList l:\n")
print(l)

# lapply() returns a list
cat("\nTotal of each element (lapply):\n")
print(lapply(l, sum))

# sapply() simplifies the result to a vector
cat("\nTotal of each element (sapply):\n")
print(sapply(l, sum))

# --- Advanced twist: using custom functions ---
cat("\nAverage and Standard Deviation for each element:\n")
stats <- sapply(l, function(x) c(Mean = mean(x), SD = sd(x)))
print(stats)

# --- Bonus: using vapply() for safer type control ---
cat("\nSafely computing maximum value in each element using vapply():\n")
max_values <- vapply(l, max, numeric(1))
print(max_values)

cat("\nDone! You've explored apply(), lapply(), sapply(), and vapply().\n")