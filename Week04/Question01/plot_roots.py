import matplotlib.pyplot as plt
import pandas as pd

def plot_iterations(filename, method_name):
    # Read the CSV file
    data = pd.read_csv(filename)
    
    # Create the plot
    plt.plot(data['Iteration'], data['Root'], marker='o', label=method_name)
    plt.xlabel('Iteration')
    plt.ylabel('Root')
    plt.title(f'Root vs Iterations for {method_name}')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{method_name}_plot.png')
    plt.show()

# Plot data for both Newton and Secant methods
plot_iterations('newton_function_1.csv', 'Newton Method (Function 1)')
plot_iterations('secant_function_1.csv', 'Secant Method (Function 1)')
