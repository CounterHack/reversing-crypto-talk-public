require 'openssl'

def ecb(data)
  c = OpenSSL::Cipher::DES.new('ECB')
  c.encrypt
  c.key = "AAAAAAAA"
  return (c.update(data) + c.final())
end

def cbc(data)
  c = OpenSSL::Cipher::DES.new('CBC')
  c.encrypt
  c.key = "AAAAAAAA"
  return (c.update(data) + c.final())
end

puts("ECB")
BASE = 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
0.upto(47) do |i|
  test = BASE.clone
  test[i] = 'B'
  puts("Changing byte %02d => #{ecb(test).unpack('H*').pop}" % i)
end
puts()

puts("CBC")
0.upto(47) do |i|
  test = BASE.clone
  test[i] = 'B'
  puts("Changing byte %02d => #{cbc(test).unpack('H*').pop}" % i)
end
puts()

