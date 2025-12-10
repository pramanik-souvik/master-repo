# Enhanced Summary Statistics for Iris
data(iris)

# Basic summary
s <- summary(iris)
cat("=== Basic Summary ===\n")
print(s)

# Add Mean, Median, and Standard Deviation for numeric columns
numeric_cols <- sapply(iris, is.numeric)
stats <- data.frame(
  Feature = names(iris)[numeric_cols],
  Mean = sapply(iris[, numeric_cols], mean),
  Median = sapply(iris[, numeric_cols], median),
  SD = sapply(iris[, numeric_cols], sd)
)
cat("\n=== Numeric Feature Stats ===\n")
print(stats)

# Count of each species
cat("\n=== Species Counts ===\n")
species_counts <- table(iris$Species)
print(species_counts)

# Save all summaries to a file
capture.output(list(BasicSummary = s, NumericStats = stats, SpeciesCounts = species_counts),
               file = "iris_summary.txt")
cat("\nSaved summary to 'iris_summary.txt'\n")