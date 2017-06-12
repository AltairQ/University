import subprocess

def exeN(n):
	p = subprocess.Popen(['a.exe'], stdout=subprocess.PIPE, stderr=subprocess.PIPE,stdin=subprocess.PIPE)
	out, err = p.communicate(str(n).encode('ascii'))
	return out

def testN(n):
	toparse = exeN(n)
	toparse = str(toparse)[2:-5]
	toparse = toparse.replace("^","**")
	# print(toparse)
	res = eval(toparse)
	# print(res)
	if n != res:
		return 1
	else:
		return 0

for n in range(2**30, 2**31):
	print(n)
	if testN(n) == 1:
	 	print('kupka')
	 	break