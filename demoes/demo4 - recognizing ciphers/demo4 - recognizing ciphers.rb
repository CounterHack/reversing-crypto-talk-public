require 'openssl'

def rc4(data)
  c = OpenSSL::Cipher::RC4.new()
  c.encrypt
  c.key = "AAAAAAAAAAAAAAAA"
  return (c.update(data) + c.final())
end

def des(data)
  c = OpenSSL::Cipher::DES.new()
  c.encrypt
  c.key = "AAAAAAAA"
  return (c.update(data) + c.final())
end

def aes(data)
  c = OpenSSL::Cipher::AES.new(128, 'CBC')
  c.encrypt
  c.key = "AAAAAAAAAAAAAAAA"
  return (c.update(data) + c.final())
end

puts("RC4...")
1.upto(33) do |i|
  puts("#{i} bytes in, #{rc4("A" * i).length} bytes out")
end
puts()

puts("DES...")
1.upto(33) do |i|
  puts("#{i} bytes in, #{des("A" * i).length} bytes out")
end
puts()

puts("AES...")
1.upto(33) do |i|
  puts("#{i} bytes in, #{aes("A" * i).length} bytes out")
end
puts()

