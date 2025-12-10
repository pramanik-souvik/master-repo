# Install necessary packages if not already installed
if(!require(shiny)) install.packages('shiny', repos='https://cloud.r-project.org')
if(!require(dplyr)) install.packages('dplyr', repos='https://cloud.r-project.org')
if(!require(readr)) install.packages('readr', repos='https://cloud.r-project.org')
if(!require(httr)) install.packages('httr', repos='https://cloud.r-project.org')

library(shiny)
library(dplyr)
library(readr)
library(httr)

# ---- UI ----
ui <- fluidPage(
  titlePanel("Professional CSV Data Cleaner"),
  
  sidebarLayout(
    sidebarPanel(
      textInput("csv_url", "CSV URL (optional):", ""),
      fileInput("csv_file", "Or upload CSV file:"),
      checkboxInput("trim_ws", "Trim whitespace", TRUE),
      checkboxInput("remove_empty", "Remove empty rows", TRUE),
      checkboxInput("remove_dup", "Remove duplicates", TRUE),
      textInput("na_replace", "Replace empty cells with:", ""),
      downloadButton("download_clean", "Download Cleaned CSV")
    ),
    
    mainPanel(
      tabsetPanel(
        tabPanel("Preview", tableOutput("preview_table")),
        tabPanel("Cleaning Report", verbatimTextOutput("report"))
      )
    )
  )
)

# ---- Server ----
server <- function(input, output, session) {
  
  # Reactive: read data
  raw_data <- reactive({
    if(input$csv_url != "") {
      tmp <- tempfile(fileext = ".csv")
      GET(input$csv_url, write_disk(tmp, overwrite = TRUE))
      df <- read_csv(tmp, show_col_types = FALSE)
    } else if(!is.null(input$csv_file)) {
      df <- read_csv(input$csv_file$datapath, show_col_types = FALSE)
    } else {
      return(NULL)
    }
    df
  })
  
  # Reactive: clean data
  cleaned_data <- reactive({
    df <- raw_data()
    if(is.null(df)) return(NULL)
    
    if(input$trim_ws) {
      trim <- function(x) if(is.character(x)) trimws(x) else x
      df <- as.data.frame(lapply(df, trim), stringsAsFactors = FALSE)
    }
    
    if(input$remove_empty) {
      df <- df[!apply(df, 1, function(r) all(is.na(r) | r=='')), ]
    }
    
    if(input$remove_dup) {
      df <- df[!duplicated(df), ]
    }
    
    if(input$na_replace != "") {
      for(col in names(df)) {
        df[[col]][df[[col]] == ""] <- input$na_replace
      }
    }
    
    df
  })
  
  # Preview table
  output$preview_table <- renderTable({
    head(cleaned_data(), 20)
  })
  
  # Cleaning report
  output$report <- renderPrint({
    df <- raw_data()
    cdf <- cleaned_data()
    if(is.null(df)) return("No data loaded yet.")
    
    cat("=== Cleaning Report ===\n")
    cat("Original rows:", nrow(df), "\n")
    cat("Cleaned rows:", nrow(cdf), "\n")
    cat("Columns:", paste(names(cdf), collapse=", "), "\n\n")
    cat("Column summaries:\n")
    print(summary(cdf))
  })
  
  # Download handler
  output$download_clean <- downloadHandler(
    filename = function() { "cleaned_data.csv" },
    content = function(file) {
      write_csv(cleaned_data(), file)
    }
  )
}

# ---- Run App ----
shinyApp(ui, server)