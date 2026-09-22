secret = rand(1:10)
println("Guess a number 1-10:")
guess = parse(Int, readline())
println(guess==secret ? "Correct!" : "Wrong! The number was $secret")
