from random import randint

d = randint(1, 10)
n = 2**d
print("P1");
print("{} {}".format(n,n))

for i in range(0,n):
	for i2 in range(0, n):
		print(randint(0,1), end="");
	print("");
	
cmds = ["*", "-", "0", "1", "=", "#"]
lets = ["a", "b", "c", "d"]

for i in range(0, n):
	print(cmds[randint(0, 5)], end="")

	for x in range(0, randint(0, d)):
		print(lets[randint(0,3)], end="")


	print("")




print(".")