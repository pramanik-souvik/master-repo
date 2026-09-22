class Car
 def initialize(name)
 @name=name
 end
 def drive
 puts "#{@name} is moving"
 end
end
Car.new("Tesla").drive