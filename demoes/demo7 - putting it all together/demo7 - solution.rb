require 'openssl'

KEY_LENGTH = 16 # TODO

def generate_key(seed)
  key = ""
  1.upto(KEY_LENGTH) do
    key += ((seed = (1103515245 * seed + 12345) & 0x7fff_ffff) & 0x0FF).chr
  end

  return key
end

def decrypt(data, key)
  c = OpenSSL::Cipher::AES.new(128, 'CBC') # TODO
  c.decrypt
  c.key = key
  return (c.update(data) + c.final())
end

if(!ARGV[1])
  puts("Usage: ruby ./solution.rb <hex data> <seed>")
  exit
end

data = [ARGV[0]].pack('H*')
seed = ARGV[1].to_i

key = generate_key(seed)
puts("Generated key: #{key.unpack('H*')}")
puts "Decrypted -> " + decrypt(data, key)
