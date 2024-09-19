import matplotlib.pyplot as plt

def plot_grid_summation_times():
    """
    This function plots the time taken to sum two identical grids for different grid sizes (n x n x n).
    The data is represented for three different grid implementations:
    - 1D Array Grid
    - Vector-based Grid
    - New operator-based Grid
    The function also includes exception handling for potential issues such as data length mismatch.
    """
    try:
        # Sample timing data for summation of grids (in seconds)
        # These arrays contain the time it takes to sum two identical grids for various grid sizes.
        grid_sizes = [10, 50, 100, 200]  # Grid sizes (n x n x n)
        timing_1d_array = [1.4197e-05, 3.5612e-04, 1.3241e-03, 5.4893e-03]  # Timing for 1D array-based grid
        timing_vector = [4.6569e-05, 7.6328e-04, 2.7645e-03, 1.0295e-02]    # Timing for vector-based grid
        timing_new_operator = [1.6368e-05, 4.5123e-04, 1.6324e-03, 6.7829e-03]  # Timing for new-operator-based grid

        # Check if the lengths of the grid_sizes and timing arrays are consistent
        # If the lengths don't match, raise a ValueError.
        if not (len(grid_sizes) == len(timing_1d_array) == len(timing_vector) == len(timing_new_operator)):
            raise ValueError("Timing data and grid sizes arrays must have the same length")

        # Plotting the data
        plt.figure(figsize=(10, 6))  # Create a new figure with a specific size
        plt.plot(grid_sizes, timing_1d_array, label="1D Array Grid", marker="o")  # Plot for 1D array-based grid
        plt.plot(grid_sizes, timing_vector, label="Vector Grid", marker="o")  # Plot for vector-based grid
        plt.plot(grid_sizes, timing_new_operator, label="New Operator Grid", marker="o")  # Plot for new-operator-based grid

        # Adding labels and title to the plot
        plt.title("Time to Add Two Identical Grids for Different Grid Sizes", fontsize=14)  # Plot title
        plt.xlabel("Grid Size (n x n x n)", fontsize=12)  # X-axis label
        plt.ylabel("Time (seconds)", fontsize=12)  # Y-axis label
        plt.grid(True)  # Add grid lines to the plot
        plt.legend()  # Show the legend for the plot

        # Display the plot
        plt.show()

    except ValueError as ve:
        # Handle cases where data length mismatch occurs
        print(f"ValueError: {ve}")
    except Exception as e:
        # Handle any other unexpected errors
        print(f"An unexpected error occurred: {e}")

# Call the function to plot the summation times for different grid sizes
plot_grid_summation_times()
