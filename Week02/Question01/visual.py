import pandas as pd
import matplotlib.pyplot as plt

# Function to plot 2D trajectory
def plot_2d_trajectory(file_2d):
    # Debug: Check if the file exists and is readable
    print(f"Reading 2D trajectory data from {file_2d}...")
    
    # Load 2D trajectory data from CSV file
    try:
        data_2d = pd.read_csv(file_2d)
        print("2D data loaded successfully:")
        print(data_2d.head())  # Print first few rows for debugging
    except Exception as e:
        print(f"Error loading 2D data: {e}")
        return
    
    # Extract time, x, and y from the data
    time = data_2d['time']
    x = data_2d['x']
    y = data_2d['y']
    
    # Create the plot for the 2D trajectory
    plt.figure()
    plt.plot(x, y, label='2D Trajectory', marker='o')
    plt.title('2D Particle Trajectory')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.grid(True)
    plt.legend()
    
    # Save the plot as an image
    plt.savefig('trajectory_2d_plot.png')
    print("2D trajectory plot saved as 'trajectory_2d_plot.png'")
    plt.show()

# Function to plot 3D trajectory (2D projection ignoring z-axis)
def plot_3d_trajectory(file_3d):
    # Debug: Check if the file exists and is readable
    print(f"Reading 3D trajectory data from {file_3d}...")
    
    # Load 3D trajectory data from CSV file
    try:
        data_3d = pd.read_csv(file_3d)
        print("3D data loaded successfully:")
        print(data_3d.head())  # Print first few rows for debugging
    except Exception as e:
        print(f"Error loading 3D data: {e}")
        return
    
    # Extract time, x, y, and z from the data
    time = data_3d['time']
    x = data_3d['x']
    y = data_3d['y']
    z = data_3d['z']
    
    # Create the plot for the 3D trajectory (2D projection)
    plt.figure()
    plt.plot(x, y, label='3D Trajectory (2D projection)', marker='o')
    plt.title('3D Particle Trajectory (2D Projection)')
    plt.xlabel('X Position')
    plt.ylabel('Y Position')
    plt.grid(True)
    plt.legend()
    
    # Save the plot as an image
    plt.savefig('trajectory_3d_plot.png')
    print("3D trajectory plot saved as 'trajectory_3d_plot.png'")
    plt.show()

# Main function to generate plots
if __name__ == '__main__':
    # File names for the 2D and 3D trajectory data
    file_2d = 'traject_2d.txt'
    file_3d = 'traject_3d.txt'
    
    # Plot the 2D and 3D trajectories
    plot_2d_trajectory(file_2d)
    plot_3d_trajectory(file_3d)
