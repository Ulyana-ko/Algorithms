import os
for i in range(100):
    a = os.system('gcc main.c')
    b = os.system("a.exe input"+str(i)+".txt output"+str(i)+".txt")