import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Function to plot 2D trajectory
def plot_2d_trajectory(file_2d):
    try:
        print(f"Reading 2D trajectory data from {file_2d}...")
        data_2d = pd.read_csv(file_2d)
        print(f"Data loaded successfully.")
        
        plt.figure()
        plt.plot(data_2d['x'], data_2d['y'], marker='o')
        plt.title('2D Particle Trajectory')
        plt.xlabel('X Position')
        plt.ylabel('Y Position')
        plt.grid(True)
        plt.savefig('images/2d_trajectory_plot.png')
        plt.show()
    except Exception as e:
        print(f"Error loading 2D data: {e}")

# Function to plot 3D trajectory
def plot_3d_trajectory(file_3d):
    try:
        print(f"Reading 3D trajectory data from {file_3d}...")
        data_3d = pd.read_csv(file_3d)
        print(f"Data loaded successfully.")
        
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.plot(data_3d['x'], data_3d['y'], data_3d['z'], marker='o')
        ax.set_title('3D Particle Trajectory')
        ax.set_xlabel('X Position')
        ax.set_ylabel('Y Position')
        ax.set_zlabel('Z Position')
        plt.grid(True)
        plt.savefig('images/3d_trajectory_plot.png')
        plt.show()
    except Exception as e:
        print(f"Error loading 3D data: {e}")

# Main function to plot both 2D and 3D trajectories
if __name__ == "__main__":
    # Define the file names
    file_2d = 'traject_2d.txt'
    file_3d = 'traject_3d.txt'
    
    # Create a directory for images if it doesn't exist
    import os
    if not os.path.exists('images'):
        os.makedirs('images')

    # Plot the trajectories
    plot_2d_trajectory(file_2d)
    plot_3d_trajectory(file_3d)
