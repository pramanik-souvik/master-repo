if(!require(shiny)) install.packages('shiny', repos='https://cloud.r-project.org')
if(!require(ggplot2)) install.packages('ggplot2', repos='https://cloud.r-project.org')
if(!require(dplyr)) install.packages('dplyr', repos='https://cloud.r-project.org')
if(!require(readr)) install.packages('readr', repos='https://cloud.r-project.org')
if(!require(GGally)) install.packages('GGally', repos='https://cloud.r-project.org')

library(shiny)
library(ggplot2)
library(dplyr)
library(readr)
library(GGally)

# ---- UI ----
ui <- fluidPage(
  titlePanel("Professional Interactive Data Visualizer"),
  
  sidebarLayout(
    sidebarPanel(
      selectInput("dataset", "Choose sample dataset:", choices = c("iris", "mtcars")),
      fileInput("upload_csv", "Or upload CSV:", accept = c(".csv")),
      hr(),
      
      uiOutput("x_var_ui"),
      uiOutput("y_var_ui"),
      uiOutput("color_var_ui"),
      uiOutput("facet_row_ui"),
      uiOutput("facet_col_ui"),
      
      selectInput("plot_type", "Plot type:", choices = c("Scatter", "Boxplot", "Histogram", "Density")),
      
      hr(),
      sliderInput("point_size", "Point size:", min=1, max=5, value=2),
      sliderInput("alpha_val", "Transparency (alpha):", min=0.1, max=1, value=0.8),
      
      downloadButton("download_plot", "Download Plot"),
      downloadButton("download_filtered", "Download Filtered Data")
    ),
    
    mainPanel(
      tabsetPanel(
        tabPanel("Plot", plotOutput("main_plot", height = "600px")),
        tabPanel("Data Preview", tableOutput("preview_table")),
        tabPanel("Summary Stats", verbatimTextOutput("summary_stats")),
        tabPanel("Correlation Matrix", plotOutput("corr_plot", height = "600px"))
      )
    )
  )
)

# ---- Server ----
server <- function(input, output, session) {
  
  # Reactive: dataset
  dataset_reactive <- reactive({
    if(!is.null(input$upload_csv)) {
      read_csv(input$upload_csv$datapath, show_col_types = FALSE)
    } else {
      switch(input$dataset,
             "iris" = iris,
             "mtcars" = mtcars)
    }
  })
  
  # Update variable selection based on dataset
  observe({
    df <- dataset_reactive()
    num_vars <- names(df)[sapply(df, is.numeric)]
    cat_vars <- names(df)[sapply(df, function(x) is.factor(x) || is.character(x))]
    
    output$x_var_ui <- renderUI({
      selectInput("x_var", "X Variable:", choices = names(df), selected = num_vars[1])
    })
    
    output$y_var_ui <- renderUI({
      selectInput("y_var", "Y Variable:", choices = c(None = "", names(df)), selected = num_vars[2])
    })
    
    output$color_var_ui <- renderUI({
      selectInput("color_var", "Color by:", choices = c(None = "", cat_vars), selected = cat_vars[1])
    })
    
    output$facet_row_ui <- renderUI({
      selectInput("facet_row", "Facet Row:", choices = c(None = "", cat_vars), selected = "")
    })
    
    output$facet_col_ui <- renderUI({
      selectInput("facet_col", "Facet Column:", choices = c(None = "", cat_vars), selected = "")
    })
  })
  
  # Main Plot
  output$main_plot <- renderPlot({
    df <- dataset_reactive()
    req(input$x_var)
    
    p <- ggplot(df, aes_string(x = input$x_var))
    
    # Determine plot type
    if(input$plot_type == "Scatter") {
      req(input$y_var)
      p <- p + geom_point(aes_string(y=input$y_var, color=input$color_var), size=input$point_size, alpha=input$alpha_val)
    } else if(input$plot_type == "Boxplot") {
      req(input$y_var)
      p <- p + geom_boxplot(aes_string(y=input$y_var, x=input$x_var, fill=input$color_var))
    } else if(input$plot_type == "Histogram") {
      p <- p + geom_histogram(aes_string(fill=input$color_var), bins = 30, alpha=input$alpha_val)
    } else if(input$plot_type == "Density") {
      p <- p + geom_density(aes_string(fill=input$color_var), alpha=input$alpha_val)
    }
    
    # Facets
    if(input$facet_row != "" || input$facet_col != "") {
      facets <- paste(ifelse(input$facet_row == "", ".", input$facet_row),
                      ifelse(input$facet_col == "", ".", input$facet_col),
                      sep="~")
      p <- p + facet_grid(as.formula(facets))
    }
    
    p + theme_minimal() + labs(title = paste(input$plot_type, "Plot"))
  })
  
  # Data preview
  output$preview_table <- renderTable({
    head(dataset_reactive(), 20)
  })
  
  # Summary stats
  output$summary_stats <- renderPrint({
    df <- dataset_reactive()
    summary(df)
  })
  
  # Correlation matrix plot
  output$corr_plot <- renderPlot({
    df <- dataset_reactive()
    num_df <- df[, sapply(df, is.numeric), drop=FALSE]
    if(ncol(num_df) > 1) {
      GGally::ggcorr(num_df, label = TRUE)
    }
  })
  
  # Download handlers
  output$download_plot <- downloadHandler(
    filename = function() { paste0("plot_", Sys.Date(), ".png") },
    content = function(file) {
      ggsave(file, plot = last_plot(), width = 8, height = 6)
    }
  )
  
  output$download_filtered <- downloadHandler(
    filename = function() { paste0("filtered_data_", Sys.Date(), ".csv") },
    content = function(file) {
      write_csv(dataset_reactive(), file)
    }
  )
}

# ---- Run App ----
shinyApp(ui, server)