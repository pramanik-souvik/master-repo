# Smart Factor Demo (Fixed & Polished)
levels_order <- c("low", "medium", "high")

# Create an ordered factor
priority <- factor(
  c("low", "medium", "high", "low", "high", "medium"),
  levels = levels_order,
  ordered = TRUE
)

cat("Original Ordered Factor:\n"); print(priority)
cat("\nSummary:\n"); print(summary(priority))

# Demonstrate ordering logic
cat("\nCheck which priorities are above 'medium':\n")
print(priority > "medium")

# To relevel (requires unordered factor)
priority_unordered <- factor(priority, ordered = FALSE)
priority_ref <- relevel(priority_unordered, ref = "high")
cat("\nLevels after releveling (reference = 'high'):\n"); print(levels(priority_ref))