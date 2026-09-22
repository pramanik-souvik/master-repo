
contacts = {}
loop do
  puts "\n1. Add Contact\n2. Search Contact\n3. Show All\n4. Exit"
  choice = gets.to_i
  case choice
  when 1
    print "Name: "; name = gets.chomp
    print "Phone: "; phone = gets.chomp
    contacts[name] = phone
  when 2
    print "Enter name: "; name = gets.chomp
    puts contacts[name] || "Not found"
  when 3
    contacts.each {|n,p| puts "#{n}: #{p}" }
  when 4
    break
  end
end
