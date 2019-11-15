require 'openssl'

KEY_LENGTH = 0 # TODO: What is the length of the key?

def generate_key(seed)
  key = ""
  1.upto(KEY_LENGTH) do
    key += (seed & 0x0FF).chr # TODO: How's the RNG work?
  end

  return key
end

def decrypt(data, key)
  c = OpenSSL::Cipher::ALG.new(ALG_DETAILS) # TODO: What's the ALG + details?
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
