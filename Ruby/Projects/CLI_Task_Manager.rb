
tasks = []
loop do
  puts "\n1. Add Task\n2. List Tasks\n3. Remove Task\n4. Exit"
  choice = gets.to_i
  case choice
  when 1
    print "Enter task: "
    tasks << gets.chomp
  when 2
    puts "Tasks:"
    tasks.each_with_index {|t,i| puts "#{i+1}. #{t}"}
  when 3
    print "Enter task number to remove: "
    num = gets.to_i
    tasks.delete_at(num-1)
  when 4
    break
  end
end
