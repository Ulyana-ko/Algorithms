import os
for i in range(100):
    a = os.system('gcc main.c')
    if i < 10:
        b = os.system("a.exe input00"+str(i)+".txt output00"+str(i)+".txt")
    if (i < 100) and (i >= 10):
        b = os.system("a.exe input0"+str(i)+".txt output0"+str(i)+".txt")
    print(b)