loop do
 puts "1. Say hi\n2. Exit"
 choice = gets.to_i
 break if choice==2
 puts "Hi!" if choice==1
end