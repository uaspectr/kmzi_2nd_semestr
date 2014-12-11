# coding: utf-8
require './big_integer.so'


def euler_func(n)
	i = 0
	m = 1

	for	i in 2..n/2
		if(n%i == 0)
			n=n/i
			while(n%i==0)
				m=m*i
				n=n/i;
			end
			if (n==1)
				return m*(i-1);
			else
				return m*(i-1)*euler_func(n)
			end
		end
	end
	return n - 1;

end



def generate_number_of_ferma()



	

	i = 1 + rand(10)

	ferm_numb = (2**(2**i)) + 1;



	return ferm_numb;


end


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


def gen_key_A()
	def stage1A
		if File::exists?("pA.txt")
		f= File.open("pA.txt","r")
		p = f.read();
		f.close()
	else
		puts "ERROR pA.txt file not found"
		exit(1)

		end

		if File::exists?("qA.txt")
		f = File.open("qA.txt","r")
		q = f.read()

		f.close
	else
		puts "ERROR qA.txt file not found"
		exit(3)

		end
	puts"A----------------------------------------"
		p = Big_integer::Bnumb.new(p.to_i.to_s)
		q = Big_integer::Bnumb.new(q.to_i.to_s)
		n = Big_integer::Bnumb.new()
		n = p*q;
	eulerfuncA = ((p-Big_integer::Bnumb.new(1))*(q-Big_integer::Bnumb.new(1)))


	
	
	while true
		eA =generate_number_of_ferma();

	eA = Big_integer::Bnumb.new(eA.to_s)	

		if(eA < eulerfuncA)
			if(check(eA,eulerfuncA)==Big_integer::Bnumb.new(1))
				break;
			end
		end
	end

	dA = Big_integer::Bnumb.new()

	dA = Big_integer::Pow(eA,Big_integer::Bnumb.new(((euler_func(eulerfuncA.to_s.to_i)-1).to_s)),eulerfuncA);


	print "Open A key {",eA,",",n,"}\n"
	print "Close A key {",dA,",",n,"}\n"


	return eA,dA,n;


	end

	e,d,n = stage1A()

end

def gen_key_B()
	def stage1B
		if File::exists?("pA.txt")
		f= File.open("pA.txt","r")
		p = f.read()
		f.close()
	else
		puts "ERROR pB.txt file not found"
		exit(2)
		end


		if File::exists?("qA.txt")
		f= File.open("qA.txt","r")
		q= f.read()
		f.close()
	else
		puts "ERROR qB.txt file not found"
		exit(2)
		end
	puts"B----------------------------------------"	
	p = Big_integer::Bnumb.new(p.to_i.to_s)	

	q = Big_integer::Bnumb.new(q.to_i.to_s)
		n = Big_integer::Bnumb.new()
		n = p*q;
	eulerfuncB = ((p-Big_integer::Bnumb.new(1))*(q-Big_integer::Bnumb.new(1)))




	while true
		eB =generate_number_of_ferma();

	eB = Big_integer::Bnumb.new(eB.to_s)	

		if(eB < eulerfuncB)
			if(check(eB,eulerfuncB)==Big_integer::Bnumb.new(1))
				break;
			end
		end
	end
	


	dB = Big_integer::Bnumb.new()

	dB = Big_integer::Pow(eB,Big_integer::Bnumb.new(((euler_func(eulerfuncB.to_s.to_i)-1).to_s)),eulerfuncB);


	print "Open B key {",eB,",",n,"}\n"
	print "Close B key {",dB,",",n,"}\n"


	return eB,dB,n;



	end

	e,d,n = stage1B()

end

def process_signature(d,n,str)
	puts "process-------d"
	puts d
	puts "-------n"
	puts n

	s = Big_integer::Bnumb.new()
	m = Big_integer::Hash(str)
	d = Big_integer::Bnumb.new(d.to_s)
	n = Big_integer::Bnumb.new(n.to_s)
	m = Big_integer::Bnumb.new(m.to_s)
	s = Big_integer::Pow(m,d,n)

	puts "-------m"
	puts m
	puts "-------s"
	puts s

	return s,m

	end

def check_signature(m,s,e,n)


	puts "check-------m"
	puts m

	puts "-------s"
	puts s

	puts "-------e"
	puts e

	puts "-------n"
	puts n

e = Big_integer::Bnumb.new(e.to_s)
n = Big_integer::Bnumb.new(n.to_s)

m1 = Big_integer::Bnumb.new()


m1 = Big_integer::Pow(s,e,n)

puts m1

if(m1.to_s==m.to_s)
	puts "signature is true"
else
	puts "signature is false"
end






end


def main()
	system("clear")
	puts "start"
eA,dA,n=	gen_key_A()

eB,dB,n=	gen_key_B()

	if File::exists?(ARGV[0])
	f=File.open(ARGV[0],"r")
	
	str = f.read();



	f.close();
else
	system("clear")
	puts "ERROR: INPUT FILE NOT FOUND"
	exit(1)
	end

	s,m = process_signature(dA,n,str)

	check_signature(m,s,eA,n)



end

main()













