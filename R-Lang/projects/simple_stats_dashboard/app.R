# Enhanced Stats Dashboard - mtcars dataset
if(!require(shiny)) install.packages('shiny', repos='https://cloud.r-project.org')
if(!require(ggplot2)) install.packages('ggplot2', repos='https://cloud.r-project.org')
if(!require(dplyr)) install.packages('dplyr', repos='https://cloud.r-project.org')

library(shiny)
library(ggplot2)
library(dplyr)

# UI
ui <- fluidPage(
  titlePanel("Enhanced Stats Dashboard - mtcars"),
  
  sidebarLayout(
    sidebarPanel(
      selectInput("num_var", "Select Numeric Variable:", 
                  choices = names(mtcars)[sapply(mtcars, is.numeric)], selected = "hp"),
      sliderInput("bins", "Number of Bins for Histogram:", min=5, max=50, value=20),
      checkboxInput("show_mean", "Show Mean Line", value = TRUE),
      checkboxInput("show_median", "Show Median Line", value = TRUE),
      hr(),
      selectInput("group_var", "Group by (Categorical):", 
                  choices = c(None = "", names(mtcars)[sapply(mtcars, function(x) is.factor(x) || is.character(x))])),
      checkboxInput("show_boxplot", "Show Boxplot by Group", value = TRUE)
    ),
    
    mainPanel(
      tabsetPanel(
        tabPanel("Histogram", plotOutput("histPlot")),
        tabPanel("Summary Statistics", verbatimTextOutput("summaryStats")),
        tabPanel("Boxplot", plotOutput("boxPlot"))
      )
    )
  )
)

# Server
server <- function(input, output) {
  
  # Histogram Plot
  output$histPlot <- renderPlot({
    p <- ggplot(mtcars, aes_string(x = input$num_var)) +
      geom_histogram(bins = input$bins, fill = "steelblue", color = "black", alpha = 0.7) +
      theme_minimal() +
      labs(title = paste("Histogram of", input$num_var), x = input$num_var, y = "Count")
    
    if(input$show_mean) {
      mean_val <- mean(mtcars[[input$num_var]], na.rm = TRUE)
      p <- p + geom_vline(xintercept = mean_val, color="red", linetype="dashed", size=1) +
        annotate("text", x=mean_val, y=max(ggplot_build(p)$data[[1]]$count), 
                 label=paste("Mean:", round(mean_val,2)), color="red", vjust=-0.5)
    }
    
    if(input$show_median) {
      med_val <- median(mtcars[[input$num_var]], na.rm = TRUE)
      p <- p + geom_vline(xintercept = med_val, color="green", linetype="dashed", size=1) +
        annotate("text", x=med_val, y=max(ggplot_build(p)$data[[1]]$count)/1.1, 
                 label=paste("Median:", round(med_val,2)), color="green", vjust=-0.5)
    }
    
    p
  })
  
  # Summary Stats
  output$summaryStats <- renderPrint({
    summary(mtcars)
  })
  
  # Boxplot
  output$boxPlot <- renderPlot({
    req(input$show_boxplot)
    req(input$group_var)
    if(input$group_var != "") {
      ggplot(mtcars, aes_string(x = input$group_var, y = input$num_var, fill = input$group_var)) +
        geom_boxplot(alpha=0.7) +
        theme_minimal() +
        labs(title = paste("Boxplot of", input$num_var, "by", input$group_var), x = input$group_var, y = input$num_var)
    } else {
      ggplot(mtcars, aes_string(y = input$num_var)) +
        geom_boxplot(fill="steelblue", alpha=0.7) +
        theme_minimal() +
        labs(title = paste("Boxplot of", input$num_var), y = input$num_var)
    }
  })
  
}

# Run App
shinyApp(ui, server)