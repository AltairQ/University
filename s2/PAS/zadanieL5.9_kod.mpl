restart;
with(PolynomialTools):

internalRec := proc(F, in_I, in_J, n, k) 
	local c_sum, p_list, i, j;

	c_sum := 0;
	p_list := [];
	
	for i from 0 to in_I do:
		for j from 0 to in_J do:
			c_sum := c_sum + a(i,j)*F(n+j,k+i);
			p_list:= [op(p_list), a(i,j)];
		end do:
	end do:

	c_sum := simplify(simplify(c_sum / F(n,k)), GAMMA);
	
	[c_sum, p_list];


end proc:

findExample := proc(eqs)
	local i, sublist, neqs, nneqs;

	sublist := [];
	neqs := [];
	nneqs := [];
	
	for i in eqs do:
		if lhs(i) = rhs(i) then:
			sublist := [op(sublist), lhs(i) = 1];			
		else:
			neqs := [op(neqs), i];
		end if:		
	end do:

	for i in neqs do:
		nneqs := [op(nneqs), lhs(i) = subs(sublist, rhs(i))];		
	end do:

	return nneqs;
	
end proc:

findNontrivial := proc(eqs, vars)
	local var_count, b_sol, i, eq;

	var_count := nops(vars);

	for i from 1 to var_count do:
		b_sol := solve([op(eqs), vars[i] = 1], vars);
		if nops(b_sol) > 0 then: # TODO substitution rules
			return findExample(b_sol[1]);
		end if:
	end do:

	return "NOPE";
		
	


end proc:


coefsToFexp := proc(eqs, n, k)
	local eq, buf, coe;

	buf := 0;
	
	for eq in eqs do:
		coe := [op(lhs(eq))];
		
		buf:= buf + rhs(eq) * F(n + coe[2], k + coe[1]);
	end do:

	return buf = 0;	


end proc:

coefsToSexp := proc(eqs, S, n, k, JJ)
	local eq, buf, coe, vec, i;

	vec := Vector[row](1..(JJ+1));
#	print(vec);

	buf := 0;
	
	for eq in eqs do:
		coe := [op(lhs(eq))];		
		vec[coe[2]+1] := vec[coe[2]+1] + rhs(eq);
	end do:

#	print(vec);

	for i from 0 to JJ do:
		buf:= buf + vec[i+1]*S(n+i);
	end do:
	
	return buf = 0;	


end proc:



CelineRec := proc(in_F, in_S, in_n, in_k)
	local n, k, ratio, II, JJ, c_sum, F, sol, ir_res, res_num, c_vec, eq_list, ter, i, fexp, sexp;
	n := in_n;
	k := in_k;
	F := in_F;
	

	ratio := F(n+1,k)/F(n,k);
	ratio := simplify(ratio);
	
	if(not type(numer(ratio), polynom(anything, var)) or not type(denom(ratio), polynom(anything, var))) then
		error "Not a hypergeometric term (with respect to n)!";
	end if;

	ratio := F(n,k+1)/F(n,k);
	ratio := simplify(ratio);
	
	if(not type(numer(ratio), polynom(anything, var)) or not type(denom(ratio), polynom(anything, var))) then
		error "Not a hypergeometric term (with respect to k)!";
	end if;


	for JJ from 1 to 6 do: # startuję od 1, bo musimy mieć co najmniej dwa wyrazy z n.
#		print("JJ: " || (convert(JJ, string)));
		for II from 0 to JJ do:
			ir_res := internalRec(F, II, JJ, n, k);
#			print(ir_res);
			res_num := collect(numer(ir_res[1]),k);

#			print(res_num);

			c_vec := CoefficientList(res_num, k);

#			print(c_vec);
			
			eq_list := [];

			for ter in c_vec do:
				eq_list := [op(eq_list), ter = 0];
			end do;

#			print(eq_list);

			sol := findNontrivial(eq_list, ir_res[2]);
			
			if sol <> "NOPE" then
#				print("found something");
#				print(sol);
				fexp := coefsToFexp(sol, n, k);
				print(fexp);
				sexp := coefsToSexp(sol, S, n, k, JJ);
#				print(sexp);
				return sexp;
			end if:
			
		end do;
		
	end do:

	error "could not find a reccurrence";
	

end proc:

smakro := proc(x) #wrapper żeby nie pisać ciągle tego samego
	return simplify(simplify(x,GAMMA));
end proc: