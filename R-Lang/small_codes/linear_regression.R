# Enhanced Linear Regression on mtcars
if (!require(ggplot2)) install.packages("ggplot2", repos = "https://cloud.r-project.org")
library(ggplot2)

# Fit model
model <- lm(mpg ~ wt + hp, data = mtcars)
summary_model <- summary(model)
cat("=== Linear Regression Summary ===\n")
print(summary_model)

# Save coefficients and R²
coef_df <- data.frame(Coefficient = names(coef(model)), Estimate = coef(model))
coef_df$R_Squared <- summary_model$r.squared
write.csv(coef_df, "lm_results.csv", row.names = FALSE)
cat("\nModel coefficients and R² saved to lm_results.csv\n")

# Plot fitted vs residuals for diagnostics
ggplot(data = data.frame(fitted = fitted(model), residuals = resid(model)), 
       aes(x = fitted, y = residuals)) +
  geom_point(color = "steelblue", size = 3, alpha = 0.7) +
  geom_hline(yintercept = 0, linetype = "dashed", color = "darkred") +
  labs(
    title = "Residuals vs Fitted Values",
    subtitle = "Checking linear model assumptions",
    x = "Fitted Values",
    y = "Residuals"
  ) +
  theme_minimal(base_size = 14)

ggsave("lm_diagnostics.png", width = 7, height = 5)
cat("Diagnostic plot saved as lm_diagnostics.png\n")