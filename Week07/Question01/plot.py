import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('polynomial_evaluation.txt', skiprows=1)
x = data[:, 0]
p_x = data[:, 1]
p_prime = data[:, 2]
p_double_prime = data[:, 3]
p_triple_prime = data[:, 4]
p_quadruple_prime = data[:, 5]
p_quintuple_prime = data[:, 6]

plt.figure(figsize=(10, 6))
plt.plot(x, p_x, label="P(x)")
plt.plot(x, p_prime, label="P'(x)")
plt.plot(x, p_double_prime, label="P''(x)")
plt.plot(x, p_triple_prime, label="P'''(x)")
plt.plot(x, p_quadruple_prime, label="P''''(x)")
plt.plot(x, p_quintuple_prime, label="P'''''(x)")
plt.xlabel("x")
plt.ylabel("Value")
plt.legend()
plt.title("Polynomial and Its Derivatives")
plt.grid()
plt.savefig("polynomial_plot.pdf")
plt.show()
