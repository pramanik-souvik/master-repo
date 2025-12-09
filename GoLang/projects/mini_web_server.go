package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

// JSON response structure
type Response struct {
	Message string `json:"message"`
	Time    string `json:"time"`
}

// Root handler
func rootHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/plain")
	fmt.Fprintf(w, "Welcome to Mini Go Server!\n")
	logRequest(r)
}

// Health check handler
func healthHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	resp := Response{
		Message: "Server is healthy",
		Time:    time.Now().Format(time.RFC3339),
	}
	json.NewEncoder(w).Encode(resp)
	logRequest(r)
}

// Custom hello endpoint
func helloHandler(w http.ResponseWriter, r *http.Request) {
	name := r.URL.Query().Get("name")
	if name == "" {
		name = "Guest"
	}
	resp := Response{
		Message: fmt.Sprintf("Hello, %s!", name),
		Time:    time.Now().Format(time.RFC3339),
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(resp)
	logRequest(r)
}

// Helper function for logging requests
func logRequest(r *http.Request) {
	log.Printf("[%s] %s %s %s\n", time.Now().Format("2006-01-02 15:04:05"), r.RemoteAddr, r.Method, r.URL.Path)
}

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", rootHandler)
	mux.HandleFunc("/health", healthHandler)
	mux.HandleFunc("/hello", helloHandler)

	serverAddr := ":8080"
	fmt.Printf("Mini Go Server running at http://localhost%s\n", serverAddr)
	if err := http.ListenAndServe(serverAddr, mux); err != nil {
		log.Fatalf("Server failed: %v", err)
	}
}