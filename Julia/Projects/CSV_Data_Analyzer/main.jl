using CSV, DataFrames
df = CSV.read("data.csv", DataFrame)
println("Mean of first column: ", mean(df[:,1]))
