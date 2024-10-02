import pandas as pd
import matplotlib.pyplot as plt

def plot_iterations(filename, method_name):
    # Read the CSV file and skip the first row (headers)
    data = pd.read_csv(filename, skiprows=1, header=None)

    # Print the data to make sure it's being read correctly
    print(data)

    # Plot the iterations vs root values
    plt.plot(data[0], data[1], marker='o', label=method_name)  # Column 0 = Iteration, Column 1 = Root
    plt.xlabel('Iteration')
    plt.ylabel('Root')
    plt.title(f'Root vs Iterations for {method_name}')
    plt.legend()
    plt.show()

# Example: Call the plotting function for different methods
plot_iterations('newton_function_2.csv', 'Newton Method (Function 2)')
plot_iterations('secant_function_2.csv', 'Secant Method (Function 2)')
