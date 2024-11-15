import pandas as pd
import matplotlib.pyplot as plt

# Load the updated CSV data
data = pd.read_csv("benchmark_results.csv")

# Plot Execution Time Comparison
plt.figure(figsize=(10, 6))
for function_name in data["Function"].unique():
    subset = data[data["Function"] == function_name]
    plt.bar(subset["Method"], subset["ExecutionTime"], label=function_name)
plt.xlabel("Integration Method")
plt.ylabel("Execution Time (s)")
plt.title("Execution Time Comparison of Integration Methods")
plt.xticks(rotation=45)
plt.legend(title="Function")
plt.tight_layout()
plt.savefig("updated_execution_time_comparison.png")
plt.show()

# Plot Error Comparison
plt.figure(figsize=(10, 6))
for function_name in data["Function"].unique():
    subset = data[data["Function"] == function_name]
    plt.bar(subset["Method"], subset["Error"], label=function_name)
plt.xlabel("Integration Method")
plt.ylabel("Error")
plt.title("Error Comparison of Integration Methods")
plt.xticks(rotation=45)
plt.legend(title="Function")
plt.tight_layout()
plt.savefig("updated_error_comparison.png")
plt.show()
