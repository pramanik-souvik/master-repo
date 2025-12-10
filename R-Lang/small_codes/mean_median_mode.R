# Enhanced Mean / Median / Mode Analysis with Visualization
x <- c(2, 3, 3, 5, 7, 3, 9, 9, 9)

mean_x <- mean(x)
median_x <- median(x)
freq_table <- sort(table(x), decreasing = TRUE)
mode_x <- as.numeric(names(freq_table[freq_table == max(freq_table)]))

cat("=== Descriptive Statistics ===\n")
cat("Data: ", paste(x, collapse = ", "), "\n")
cat("Mean   :", round(mean_x, 2), "\n")
cat("Median :", median_x, "\n")
cat("Mode(s):", paste(mode_x, collapse = ", "), "\n\n")

# Visualization
plot_hist <- function() {
  hist(x, breaks = 5, col = "skyblue", border = "white",
       main = "Distribution of Values",
       xlab = "Values", ylab = "Frequency")
  abline(v = mean_x, col = "red", lwd = 2, lty = 2)
  abline(v = median_x, col = "darkgreen", lwd = 2, lty = 3)
  legend("topright", legend = c("Mean", "Median"),
         col = c("red", "darkgreen"), lwd = 2, lty = c(2, 3))
}

# If running in Rscript, save the plot; otherwise show it
if (!interactive()) {
  png("distribution_plot.png", width = 600, height = 400)
  plot_hist()
  dev.off()
  cat("Saved plot as distribution_plot.png\n")
} else {
  plot_hist()
}