
rates = {"USD"=>109.5, "EUR"=>115.3, "INR"=>1.32}
puts "Enter amount in BDT:"
amount = gets.to_f
rates.each {|cur, rate| puts "#{cur}: #{(amount/rate).round(2)}" }
