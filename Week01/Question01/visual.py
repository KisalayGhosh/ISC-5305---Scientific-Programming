import matplotlib.pyplot as plt
import csv

# File to read the heat distribution data
input_file = 'heat_distribution.csv'

# Initialize lists for x and T(x)
x = []
T = []


print(f"Reading data from {input_file}...")

# Read data from CSV file
with open(input_file, 'r') as file:
    reader = csv.reader(file)
    next(reader)  
    for row in reader:
        x.append(float(row[0]))
        T.append(float(row[1]))


print(f"Data read successfully. Number of points: {len(x)}")

# Plot the heat distribution
plt.plot(x, T, label='T(x) = 1 - x^2')
plt.xlabel('x')
plt.ylabel('Temperature (T)')
plt.title('1D Heat Distribution')
plt.grid(True)
plt.legend()
plt.savefig('heat_distribution_plot.png')  # Save plot to a file


print(f"Plot saved as 'heat_distribution_plot.png'")

plt.show()
