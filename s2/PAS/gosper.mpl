restart;


findABC := proc(in_r, k)
	local Z, f, g, a, b, c, R, buf, h, r_list, int_list, p, q, s, s_list, i, j, r, d;

	Z := 1;

	r := simplify(in_r);
	
	f := numer(r);
	g := denom(r);

	buf := lcoeff(f, k);
	Z := Z * buf;
	f := f / buf;

	buf := lcoeff(g, k);
	Z := Z / buf;
	g := g / buf;

	R := resultant(f, subs(k=k+h, g), k);


	r_list := solve(R=0, h);

	
	int_list := [];

	for buf in r_list do:
		if type(buf, nonnegint) then:
			int_list := [op(int_list), buf];
		end if;
	end do:

	int_list := sort(int_list);


	p := f;
	q := g;
	s_list := [];

	for buf in int_list do:
		s := gcd(p, subs(k=k+buf, q));
		s_list := [op(s_list), s];
		p := p / s;
		q := q / subs(k=k-buf, s);
	end do:

	a := Z*p;
	b := q;
	c := 1;

	for i from 1 to numelems(int_list) do:
		for j from 1 to int_list[i] do:
			c := c * subs(k=k-j, s_list[i]);
		end do:
	end do:


	return [simplify(a), simplify(b), simplify(c)];	

end proc:

genPoly := proc(k, d)
	local x, cofs, i;

	cofs := [];

	x := 0;

	for i from 0 to d do:
		x := x + z[i] * k^i;
		cofs := [op(cofs), z[i]];
	end do:

	return [x, cofs];
end proc:

findExample := proc(eqs)
	local i, sublist, neqs, nneqs;

	sublist := [];
	neqs := [];
	nneqs := [];
	
	for i in eqs do:
		if lhs(i) = rhs(i) then:
			sublist := [op(sublist), lhs(i) = 1];	
		end if:
		neqs := [op(neqs), i];
	end do:

	for i in neqs do:
		nneqs := [op(nneqs), lhs(i) = subs(sublist, rhs(i))];		
	end do:

	return nneqs;
	
end proc:

GosperSum := proc(t, rang)
	local k, range_from, range_to, has_range, r, abc_list, D, a, b, c, intD, i, x, cofs, sol, d, z;
	
	if type(rang, symbol) then:
		k          := rang;
		has_range  := false;
	else
		k          := lhs(rang);
		range_from := lhs(rhs(rang));
		range_to   := rhs(rhs(rang));
		has_range  := true;		
	end if;

	r := simplify(subs(k = k+1, t) / t);
#	print(r);

#	TO CHECK if rational or something else

	if not type(r, ratpoly( rational, k)) then:
		error "t is not a proper hypergeometric term!";
	end if;

	abc_list := findABC(r, k);
	a := abc_list[1];
	b := abc_list[2];
	c := abc_list[3];

	if simplify((a*subs(k=k+1, c) /(b*c))/r) <> 1 then:
		error "ABC wrong";
	end if;

#	print(abc_list);
#	print(resultant(a, subs(k=k+h, b), k));

	D := {};
	
	if (degree(a, k) <> degree(b, k)) or (lcoeff(a, k) <> lcoeff(b, k)) then:
		D := {degree(c, k) - max(degree(a,k), degree(b,k))};
	else:
		D:= {degree(c, k) - degree(a,k)+1, (coeff(subs(k= k-1, b), k, degree(subs(k= k-1, b), k)-1 ) - coeff(a, k, degree(a,k)-1))/lcoeff(a,k)};
	end if:

	intD := {};

	for i in D do:
		if type(i, nonnegint) then:
			intD:= {op(intD), i};
		end if:
	end do:

	if numelems(intD) = 0 then:
		error "no polynomial recurrence solutions!";
	end if;

	d := max(intD);
#	print(d);

	x := genPoly(k, d);
	cofs := x[2];
	x := x[1];
#	print(x);

#	print(expand(a*subs(k=k+1, x) - subs(k=k-1, b) * x) );
#	print(c);

	sol := solve(a * subs(k=k+1, x) - (subs(k=k-1, b) * x) = c, cofs);
#	print(sol);

	if numelems(sol) = 0 then:
		error "no polynomial recurrence solutions!";
	end if;

#	print(sol);
	sol := findExample(sol[1]);
#	print(sol);

	x := subs(sol, x);



	z := subs(k=k-1, b)*x*t/c;

	if simplify(subs(k=k+1, z) - z - t) <> 0 then:
		error "Z error";
	end if;



	if has_range then:
		return simplify(subs(k=range_to +1, z) - subs(k=range_from, z));
	else:
		return simplify(z);
	end if;

	
		

end proc: