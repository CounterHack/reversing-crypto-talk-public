require 'openssl'
def ecb(data)
  c = OpenSSL::Cipher::DES.new('ECB')
  c.encrypt
  c.key = "AAAAAAAA"
  return (c.update(data) + c.final()).unpack('H*').pop.scan(/(.{16})/).join(' ')
end

def cbc(data)
  c = OpenSSL::Cipher::DES.new('CBC')
  c.encrypt
  c.key = "AAAAAAAA"
  return (c.update(data) + c.final()).unpack('H*').pop.scan(/(.{16})/).join(' ')
end

puts("ECB")
BASE = 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
0.upto(47) do |i|
  test = BASE.clone
  test[i] = 'B'
  puts("Changing byte %02d => #{ecb(test)}" % i)
end
puts()

puts("CBC")
0.upto(47) do |i|
  test = BASE.clone
  test[i] = 'B'
  puts("Changing byte %02d => #{cbc(test)}" % i)
end
puts()

