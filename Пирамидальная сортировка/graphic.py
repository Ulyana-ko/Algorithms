import matplotlib.pyplot as plt

f1 = open("size.txt", "r")
x = list(map(int, f1.read().split()))
f2 = open("time.txt","r")
y = list(map(int, f2.read().split()))
r = 1
while r == 1:
    r = 0
    for i in range(len(x)-1):
        if x[i]>x[i+1]:
            x[i], x[i+1] = x[i+1], x[i]
            y[i], y[i+1] = y[i+1], y[i]
            r = 1

plt.plot(x,y)
plt.xlabel("number of elements")
plt.ylabel("time, Nanoseconds/10000000")
plt.show()

f1.close()
f2.close()