# Smart Data Frame Demo
df <- data.frame(
  ID = 1:3,
  Name = c("Souvik", "Pramanik", "Riaz"),
  Score = c(90, 85, 78)
)

cat(" Full Data Frame:\n"); print(df)
cat("\n Scores Only:\n"); print(df$Score)

# Filter high scorers
high_scorers <- subset(df, Score > 80)
cat("\n Students Scoring Above 80:\n"); print(high_scorers)

# Add a performance column (derived feature)
df$Performance <- ifelse(df$Score > 85, "Excellent", "Good")
cat("\n Enhanced Data Frame:\n"); print(df)