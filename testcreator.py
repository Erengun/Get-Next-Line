fd = open("test.txt", "w")
for i in range(0,1000,1):
	fd.write(f"satir : {i}\n")
fd.close()