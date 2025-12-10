# Smart CSV Import/Export Demo
df <- data.frame(ID = 1:5, Letter = LETTERS[1:5])
cat("Original Data:\n"); print(df)

# Write to CSV
write.csv(df, "demo_data.csv", row.names = FALSE)

# Read it back
df_loaded <- read.csv("demo_data.csv")
cat("\nData Reloaded from CSV:\n"); print(df_loaded)

# Quick check
cat("\nData match check:", identical(df, df_loaded), "\n")