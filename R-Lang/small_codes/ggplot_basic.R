# ggplot2 enhanced example using mtcars
if (!require(ggplot2)) install.packages("ggplot2", repos = "https://cloud.r-project.org")
library(ggplot2)

# Base plot with color and a linear model fit
p <- ggplot(mtcars, aes(x = hp, y = mpg, color = factor(cyl))) +
  geom_point(size = 3, alpha = 0.7) +
  geom_smooth(method = "lm", se = TRUE, linetype = "dashed") +
  labs(
    title = "Horsepower vs. Miles per Gallon",
    subtitle = "Grouped by Number of Cylinders",
    x = "Horsepower (hp)",
    y = "Miles per Gallon (mpg)",
    color = "Cylinders"
  ) +
  theme_minimal(base_size = 14)

print(p)
ggsave("mtcars_scatter.png", p, width = 7, height = 5)
cat("Saved plot as mtcars_scatter.png\n")