import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function to plot 2D particle trajectory from a CSV file
def plot_2d_trajectory(file_2d):
    """
    Reads 2D trajectory data from the specified file and plots the trajectory.
    Saves the plot as a PNG file in the 'images' directory.
    
    Args:
        file_2d (str): The name of the file containing 2D trajectory data.
    
    Raises:
        Exception: If there is an error reading the data or plotting the trajectory.
    """
    try:
        print(f"Reading 2D trajectory data from {file_2d}...")
        data_2d = pd.read_csv(file_2d)  # Load the 2D trajectory data
        print(f"Data loaded successfully.")
        
        # Plot the 2D trajectory
        plt.figure()
        plt.plot(data_2d['x'], data_2d['y'], marker='o')  # Plot x vs. y
        plt.title('2D Particle Trajectory')
        plt.xlabel('X Position')
        plt.ylabel('Y Position')
        plt.grid(True)
        
        # Save the plot as an image file
        plt.savefig('images/2d_trajectory_plot.png')
        
        # Display the plot
        plt.show()
    except Exception as e:
        print(f"Error loading 2D data: {e}")  # Print error message if data loading fails

# Function to plot 3D particle trajectory from a CSV file
def plot_3d_trajectory(file_3d):
    """
    Reads 3D trajectory data from the specified file and plots the trajectory in 3D.
    Saves the plot as a PNG file in the 'images' directory.
    
    Args:
        file_3d (str): The name of the file containing 3D trajectory data.
    
    Raises:
        Exception: If there is an error reading the data or plotting the trajectory.
    """
    try:
        print(f"Reading 3D trajectory data from {file_3d}...")
        data_3d = pd.read_csv(file_3d)  # Load the 3D trajectory data
        print(f"Data loaded successfully.")
        
        # Create a 3D plot
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')  # Create a 3D axis
        ax.plot(data_3d['x'], data_3d['y'], data_3d['z'], marker='o')  # Plot x, y, z
        
        # Set plot labels and title
        ax.set_title('3D Particle Trajectory')
        ax.set_xlabel('X Position')
        ax.set_ylabel('Y Position')
        ax.set_zlabel('Z Position')
        
        plt.grid(True)
        
        # Save the plot as an image file
        plt.savefig('images/3d_trajectory_plot.png')
        
        # Display the plot
        plt.show()
    except Exception as e:
        print(f"Error loading 3D data: {e}")  # Print error message if data loading fails

# Main function to plot both 2D and 3D trajectories
if __name__ == "__main__":
    """
    Main script to read and plot both 2D and 3D particle trajectories. 
    The trajectory data is read from two files: 'traject_2d.txt' and 'traject_3d.txt'. 
    The plots are saved as images in the 'images' directory.
    """
    # Define the file names
    file_2d = 'traject_2d.txt'  # Name of the 2D data file
    file_3d = 'traject_3d.txt'  # Name of the 3D data file
    
    # Create a directory for images if it doesn't exist
    import os
    if not os.path.exists('images'):
        os.makedirs('images')  # Create 'images' folder for saving the plots

    # Plot the 2D and 3D trajectories
    plot_2d_trajectory(file_2d)
    plot_3d_trajectory(file_3d)
