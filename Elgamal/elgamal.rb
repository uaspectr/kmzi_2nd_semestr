# coding: utf-8
require './big_integer.so'


def encode_elgamal(p,g,y)




def find_y(str,y,k,p)

b = Big_integer::Bnumb.new()

tmp = Big_integer::Bnumb.new(str)

b = Big_integer::Pow(y,k,p)

b = b *tmp

return b.to_s;


end


if File::exists?(ARGV[1])
f = File.open(ARGV[1],"r") 
else
puts "input text_file not found!!!"
exit(2)
end

a = f.read();

puts"Input text \n-------------------"

puts a

f.close();



len = (a.to_s).size()



s= ""

(a.to_s).each_byte{|c|s=s+c.to_s(10)+" "}
string = s.split(pattern=' ')


k = 2 + rand((p.to_s.to_i-1)-1)

k = Big_integer::Bnumb.new(k.to_s)

a = Big_integer::Bnumb.new()

a = Big_integer::Pow(g,k,p)

final_string=""

for i in 0..len-1


final_string = final_string + find_y(string[i] ,y,k,p)+ " ";

end

return final_string, a.to_s;

end


def elgamal_decode(string,a,x,p,path)


a = Big_integer::Bnumb.new(a);

x = Big_integer::Bnumb.new(x);



p = Big_integer::Bnumb.new(p - Big_integer::Bnumb.new(1));



encode_array= string.split(pattern=' ')

b = encode_array;

len = encode_array.size();


px = p - x;

decode_array=""


for i in 0..len - 1
	decode_array = decode_array + ((((Big_integer::Pow(a,px,p+Big_integer::Bnumb.new(1)))*Big_integer::Bnumb.new(b[i])) % (p+Big_integer::Bnumb.new(1)))).to_s+" " 
end


	final_decode="";

	final_decode=decode_array.split(pattern=' ')


	puts"decode:\n------------------"

f = File.open(path,"w")


for i in 0..len-1
print (final_decode[i].to_i).chr
f.print (final_decode[i].to_i).chr

end
f.close();

puts "\n"

end


def key_generate(path)


y = Big_integer::Bnumb.new()

if File::exists?(ARGV[0])
f = File.open(path,"r")
p = f.read()
f.close()
else
	puts "input modulus_file not found!!!"
exit(2)
	end

p = Big_integer::Bnumb.new(p.to_s)





i = 0;


while true

	g = 2 + rand((p.to_s.to_i-1)-1)
	if((p.to_s.to_i-1)%g) !=1;
		break;

	end

end



x = (2 + rand((p.to_s.to_i - 1)-1))



g = Big_integer::Bnumb.new(g.to_s);

x = Big_integer::Bnumb.new(x.to_s);

y = Big_integer::Pow(g,x,p)



print "key"
print "("
print p
print ","
print g
print ","
print y
puts ")"

return p,g,y,x


end



def main()




if ARGV.size() != 3

	puts "Wrong count of arguments\nUSAGE: ruby ./script_name.rb modulus_file.txt text_file.txt output_file.txt"
	exit(1);
	
end
	system("clear")
	encode_string = "";
	a = "";
	p,g,y,x = key_generate(ARGV[0])
	encode_string,a = encode_elgamal(p,g,y)
	puts"----------------"
	print"encode:" "(" ,"[",a,"]",",[",encode_string,"])\n";
	elgamal_decode(encode_string,a,x,p,ARGV[2])
	


end

main()













