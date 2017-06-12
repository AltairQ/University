restart;
with(ListTools): #potrzebne do wyszukiwania elementów w listach
with(combinat): #potrzebne do permutacji listy parametrów


D_VanderGauss := proc(hyp) #tożsamość gaussa
	local toret, a, b, c;
	
	if numelems(hyp[1]) <> 2 or numelems(hyp[2]) <> 1 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];
	c := hyp[2][1];

	toret := GAMMA(c)*GAMMA(c-a-b) / (GAMMA(c-a)*GAMMA(c-b));
	return simplify(simplify(toret), GAMMA);
end proc:

D_Saalchutz := proc(hyp)
	local a,b,c,n, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];
	n := -hyp[1][3];
	c := hyp[2][1];

	if not type(n, nonnegint) then
		return "NOPE";
	end if;

	if hyp[2][2] <> 1+a+b-c-n then
		return "NOPE";
	end if;

	toret := pochhammer(c-a,n)*pochhammer(c-b,n) / ( pochhammer(c,n)*pochhammer(c-a-b,n) );
	return simplify(simplify(toret),GAMMA);	

end proc:


D_Kummer := proc(hyp)
	local a,b, toret;
	
	if numelems(hyp[1]) <> 2 or numelems(hyp[2]) <> 1 or hyp[3] <> -1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];

	if hyp[2][1] <> 1+a-b then
		return "NOPE";
	end if;

	toret := GAMMA(1+a-b)*GAMMA(1+a/2) / (GAMMA(1+a)*GAMMA(1+a/2-b));
	return simplify(simplify(toret),GAMMA);	

end proc:

D_Gauss := proc(hyp)
	local a,b, toret;
	
	if numelems(hyp[1]) <> 2 or numelems(hyp[2]) <> 1 or hyp[3] <> 1/2 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];

	if hyp[2][2] <> (a+b+1)/2 then
		return "NOPE";
	end if;

	toret := GAMMA(1/2)*GAMMA((a+b+1)/2) / (GAMMA((a+1)/2) * GAMMA((b+1)/2));
	return simplify(simplify(toret),GAMMA);	

end proc:


D_Bailey11 := proc(hyp)
	local a,c, toret;
	
	if numelems(hyp[1]) <> 2 or numelems(hyp[2]) <> 1 or hyp[3] <> 1/2 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	c := hyp[2][1];

	if hyp[1][2] <> 1-a then
		return "NOPE";
	end if;

	toret := GAMMA(c/2)*GAMMA((c+1)/2) / ( GAMMA((a+c)/2) * GAMMA((1-a+c)/2) );
	return simplify(simplify(toret),GAMMA);	

end proc:

D_Dixon := proc(hyp)
	local a,b,c, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];
	c := hyp[1][3];

	if hyp[2][1] <> 1+a-b   or  hyp[2][2] <> 1+a-c then
		return "NOPE";
	end if;

	toret := GAMMA(1+a/2) * GAMMA(1+a-b) * GAMMA(1+a-c)*GAMMA(1+a/2-b-c) /
			(GAMMA(1+a) * GAMMA(1+a/2-b) * GAMMA(1+a/2-c) *GAMMA(1+a-b-c));
	return simplify(simplify(toret),GAMMA);	

end proc:

D_WatsonWhipple := proc(hyp)
	local a,b,c, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];
	c := hyp[1][3];

	if hyp[2][1] <> (a+b+1)/2  or  hyp[2][2] <> 2*c then
		return "NOPE";
	end if;

	toret := GAMMA(1/2)*GAMMA((1+2*c)/2)*GAMMA((1+a+b)/2)*GAMMA((1-a-b+2*c)/2) / 
			(GAMMA((1+a)/2)*GAMMA((1+b)/2)*GAMMA((1-a+2*c)/2)*GAMMA((1-b+2*c)/2));
	return simplify(simplify(toret),GAMMA);	

end proc: 

D_Whipple := proc(hyp)
	local a,c,e, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	c := hyp[1][3];
	e := hyp[2][1];

	if hyp[1][2] <> 1-a  or  hyp[2][2] <> 1+2*c-e then
		return "NOPE";
	end if;

	toret := Pi * 2^(1-2*c) * GAMMA(e) *GAMMA(1+2*c-e) /
			(GAMMA((a+e)/2)*GAMMA((a+1+2*c-e)/2)*GAMMA((1-a+e)/2)*GAMMA((2+2*c-a-e)/2));
	return simplify(simplify(toret),GAMMA);	

end proc: 


D_Whipple2 := proc(hyp)
	local a,d,e, toret;
	
	if numelems(hyp[1]) <> 4 or numelems(hyp[2]) <> 3 or hyp[3] <> -1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	d := hyp[1][3];
	e := hyp[2][4];

	if hyp[1][2] <> 1+a/2  or  hyp[2][1] <> a/2 or hyp[2][2] <> 1+a-d or hyp[2][3] <> 1+a-e then
		return "NOPE";
	end if;

	toret := GAMMA(1+a-d)*GAMMA(1+a-e)/
			(GAMMA(1+a)*GAMMA(1+a-d-e));
	return simplify(simplify(toret),GAMMA);	

end proc: 

D_Bailey31 := proc(hyp)
	local a,w,n, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	n := -hyp[1][3];
	w := hyp[2][2];

	if not type(n, nonnegint) then
		return "NOPE";
	end if;

	if hyp[1][2] <> 1+a/2  or  hyp[2][1] <> a/2  then
		return "NOPE";
	end if;

	toret := (w-a-1-n)*pochhammer(w-a,n-1) / pochhammer(w,n);
	return simplify(simplify(toret),GAMMA);	

end proc:

D_Bailey32 := proc(hyp)
	local a,b,n, toret;
	
	if numelems(hyp[1]) <> 3 or numelems(hyp[2]) <> 2 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][2];
	n := -hyp[1][3];

	if not type(n, nonnegint) then
		return "NOPE";
	end if;

	if hyp[2][1] <> 1+a-b  or  hyp[2][2] <> 1-2*b-n  then
		return "NOPE";
	end if;

	toret := pochhammer(a-2*b,n) * pochhammer(-b, n) /
			(pochhammer(1+a-b,n)*pochhammer(a/2-b,n)*pochhammer(-2*b,n) );
			
	return simplify(simplify(toret),GAMMA);	

end proc:


D_Bailey33 := proc(hyp)
	local a,b,n, toret;
	
	if numelems(hyp[1]) <> 4 or numelems(hyp[2]) <> 3 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][3];
	n := -hyp[1][4];

	if not type(n, nonnegint) then
		return "NOPE";
	end if;

	if hyp[1][2] <> 1 + a/2  or  hyp[2][1] <> a/2 or hyp[2][2] <> 1+a-b or hyp[2][3] <>1+2*b-n  then
		return "NOPE";
	end if;

	toret := pochhammer(a-2*b,n)*pochhammer(-b,n) /
			(pochhammer(1+a-b,n)*pochhammer(-2*b,n) );
			
	return simplify(simplify(toret),GAMMA);	

end proc:


D_Bailey34 := proc(hyp)
	local a,b,n, toret;
	
	if numelems(hyp[1]) <> 4 or numelems(hyp[2]) <> 3 or hyp[3] <> 1 then
		return "NOPE";
	end if;

	a := hyp[1][1];
	b := hyp[1][3];
	n := -hyp[1][4];

	if not type(n, nonnegint) then
		return "NOPE";
	end if;

	if hyp[1][2] <> 1 + a/2  or  hyp[2][1] <> a/2 or hyp[2][2] <> 1+a-b or hyp[2][3] <> 2+2*b-n  then
		return "NOPE";
	end if;

	toret := pochhammer(a-2*n-1, n) * pochhammer(1/2 +a/2 -b, n) * pochhammer(-b-1, n) / 
			(pochhammer(1+a-b,n)*pochhammer(a/2-b-1/2,n)*pochhammer(-2*b-1,n) );
			
	return simplify(simplify(toret),GAMMA);	

end proc:



Hyp_Database := [D_VanderGauss, D_Saalchutz, D_Kummer, D_Gauss, D_Bailey11, D_Dixon, D_WatsonWhipple, 
			 D_Whipple, D_Whipple2, D_Bailey31, D_Bailey32, D_Bailey33, D_Bailey34];


TryAll := proc(hyp)
	local tr, pr;

	for pr in Hyp_Database do:
		tr := pr(hyp);
		if tr <> "NOPE" then
			return tr;
		end if;
	end do;

	return "NOPE";

end proc:


Sum2Hyp := proc(term, in2)
	local i, var, ran, beg, fin, buf, ratio, cof, t, list_up, list_down, hyp_x;
	t := term;
	var := lhs(in2); #zmienna po której sumujemy
	ran := rhs(in2); #zakres
	beg := lhs(ran); #początek zakresu
	fin := rhs(ran); #koniec zakresu

	if fin < beg then
		buf := beg;
		beg := fin;
		fin := buf;
		buf := 'buf';
	end if;

#	if(beg = -infinity and fin = infinity) then #cóż, zakładamy że szereg hyp.geo. jest od 0 do +inf
#									    #niby to jest równoliczne, ale trudniejsze do obsłużenia
#		error "Summation limits cannot be both infinite!";
#	end if;

	fin := fin - beg; #normalizacja przedziału do 0..fin-beg	
	t := subs(var = var - beg, t);	
	beg := 0;

	for i from 0 to min(fin, 1000) while eval(t, var = i) = 0 do: #szukam miejsca gdzie wyrażenie != 0
		end do:

	if eval(t, var = i) = 0 then
		error "I don't know how to sum 0...";
	end if;
	

	t := subs(var = var + i, t); #przesuwam początek
	fin := fin - i; #skracam koniec
#	print(cof);

	if( fin <> infinity) then #aplikuję koniec tak jak pan Koepf nakazał
		t := subs(var = fin - var , t);
	end if;


	cof := simplify(simplify(eval(t, var = 0)),GAMMA); #współczynnik przy 0-wym wyrazie
		
	

	ratio := subs(var=var+1, t)/t;
	ratio := simplify(simplify(factor(ratio)), GAMMA);

#	print(ratio);
#	print(numer(ratio));
#	print(denom(ratio));

	if(not type(numer(ratio), polynom(anything, var)) or not type(denom(ratio), polynom(anything, var))) then
		error "Not a hypergeometric term!";
	end if;

	list_up :=  [solve(numer(ratio) = 0, var)] *~ (-1); #Maple ma strasznie toporne funkcje faktoryzujące, 100x lepiej użyć solve)
	list_down := [solve(denom(ratio) = 0, var)] *~ (-1); # *~ mnoży każdy element z osobna

	i := 'i';
	
	for i in list_up do: #być może na około, ale usuwam tutaj wyrażenia (k+i)
		ratio := ratio / (var + i); #bo chcę odzyskać współczynnik, czyli 'x' w szeregu
	end do;

	for i in list_down do:
		ratio := ratio*(var + i);
	end do;

	hyp_x := simplify(simplify(ratio), GAMMA);
	

	if(not member(1, list_down)) then #tutaj dodaję (k+1) do mianownika i licznika
		list_up := [op(list_up), 1];
	else
		list_down := subsop(Search(1, list_down)=NULL, list_down); #a tu ew odejmuję, nie znalazłem lepszego sposobu
	end if;

	return [cof, list_up, list_down, hyp_x];

end proc:


DatabaseSum := proc(term, in2)
	local hyp, c_sum, comp, cof, p, all_permuted, x, y;

	comp := Sum2Hyp(term, in2); #najpierw kompresja


	cof := comp[1]; #tutaj rozpakowuję to tak, żeby dalej przekazywać tylko faktyczny szereg hyp.geo.
	hyp := [comp[2], comp[3], comp[4]];


	all_permuted := [];

	for x in permute(hyp[1]) do: #tutaj permutuję parametry, żeby potem się nie przejmować kolejnością
		for y in permute(hyp[2]) do:
			all_permuted := [op(all_permuted), [x,y,hyp[3]]];
		end do;
	end do;

#	print(all_permuted);

	for x in all_permuted do:
		y := TryAll(x);
		if y <> "NOPE" then
			return simplify(factor(simplify(cof*y)),GAMMA);	
		end if;

	end do;


	print("I don't know how to calculate that...");
#	print(all_permuted);

end proc: