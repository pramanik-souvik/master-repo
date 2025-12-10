# Smart String Manipulation Demo
text <- "   Hello, R world! Let's learn String Tricks.   "

cat("Original  :", text, "\n")

# Basic cleanup
trimmed <- trimws(text)
upper <- toupper(trimmed)
lower <- tolower(trimmed)
title_case <- tools::toTitleCase(lower)

# Replacement and splitting
replaced <- gsub("R", "Rust", trimmed)
words <- unlist(strsplit(trimmed, "\\s+"))

# Results
cat("Trimmed   :", trimmed, "\n")
cat("Uppercase :", upper, "\n")
cat("Lowercase :", lower, "\n")
cat("TitleCase :", title_case, "\n")
cat("Replaced  :", replaced, "\n")
cat("Words     :", paste(words, collapse = " | "), "\n")

# Small visualization-like output
cat("\nWord Lengths:\n")
print(setNames(nchar(words), words))