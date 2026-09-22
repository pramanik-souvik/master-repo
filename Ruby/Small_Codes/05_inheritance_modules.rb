module Greet
 def hello
 puts "Hello from module!"
 end
end
class Parent; def speak; puts "Parent speaking"; end; end
class Child < Parent; include Greet; end
Child.new.speak; Child.new.hello