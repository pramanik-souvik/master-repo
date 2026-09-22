begin
 puts 10/0
rescue ZeroDivisionError => e
 puts "Error: #{e.message}"
end