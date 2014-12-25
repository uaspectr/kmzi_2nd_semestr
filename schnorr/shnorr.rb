# coding: utf-8
require './big_integer.so'

def check(a,b)

	res =Big_integer::Bnumb.new(0)
	q = Big_integer::Bnumb.new(0)
	r = Big_integer::Bnumb.new(0)
	z = Big_integer::Bnumb.new(0)
	zero = Big_integer::Bnumb.new(0.to_s)

	a = Big_integer::Bnumb.new(a.to_s)
	b = Big_integer::Bnumb.new(b.to_s)

	begin

	q = a / b
	r = a % b
	a = b
	b = r
	r = a - (b* Big_integer::Bnumb.new(2.to_s))

	end while(b!=zero)

	return a;

end





def generate_key()

p = Big_integer::Bnumb.new()
p.readtxt("p.txt")

puts p

q = Big_integer::Bnumb.new()
q.readtxt("q.txt")

f = File.open("q.txt","r")

q1=f.read()

f.close()

puts q,q1

begin

g = rand(1084536)

end while(g==1)


tmp = Big_integer::Bnumb.new(g.to_s)

while true

	if(check(tmp^q,p) == Big_integer::Bnumb.new(1.to_s))
	break;
	end

	tmp = tmp + 1;

end



g = Big_integer::Bnumb.new(tmp.to_s)
w = 2 + rand((q1.to_i - 1 - 2))

r = 2 + rand(q1.to_i - 1 - 2)


w = Big_integer::Bnumb.new(w.to_s)
r = Big_integer::Bnumb.new(r.to_s)

x = Big_integer::Pow(g,r,p)
puts x

y = Big_integer::Pow(g,p-Big_integer::Bnumb.new(1.to_s)-w,p)

puts y





return p,q,g,w,r,y,x




end

def process_signature(x,g,r,p,m,w,q)

s1 = Big_integer::Hash(m.to_s + x.to_s)

s1 = Big_integer::Bnumb.new(s1)

s2 = (Big_integer::Bnumb.new(r) + Big_integer::Bnumb.new(w)*s1) % Big_integer::Bnumb.new(q)

puts "---------------process_signature-----------"


print "\nm = ",m

print "\nx = ",x

print "\nr = ",r

print "\nw = ",w

print "\nq = ",q

print "\ns1 = ",s1



s2 = Big_integer::Bnumb.new(s2.to_s)

print "\ns2 = ",s2

puts "\n---------------"

return s1,s2

end

def check_signature(s1,s2,g,y,p,m)

	puts"----------check_signature--------------"

	print "\ng = ",g
	print "\ns2 = ",s2
	print "\np = ",p
	print "\ny = ",y
	print "\nm = ",m

	print "\ns1 --------\n"
	puts s1
	print "\n-=------\n"
	


	res = (Big_integer::Pow(g,s2,p) * Big_integer::Pow(y,s1,p)) % p
	
	puts"---------------------------"
	puts s1
	puts Big_integer::Hash(m.to_s + res.to_s)
	puts "-----------------------------"


	if(s1.to_s == Big_integer::Hash(m.to_s + res.to_s))
		puts "signature is true"
	else
		puts "signature is false"
	end




end


def main()
p,q,g,w,r,y,x = generate_key()

f = File.open("text.txt","r")

text = f.read()

puts text



s1,s2 = process_signature(x,g,r,p,Big_integer::Hash(text),w,q)


puts "s1,s2",s1,s2

check_signature(s1,s2,g,y,p,Big_integer::Hash(text))



end

main()

