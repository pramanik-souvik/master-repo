require "net/http"
url = URI("https://example.com")
res = Net::HTTP.get_response(url)
puts res.code