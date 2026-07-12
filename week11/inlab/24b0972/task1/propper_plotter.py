import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import os

# Ignore
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

# Ignore
def compress_workload_names(workloads):
    compressed = []
    for i in workloads:
        if(i == "PageRankDelta"):
            compressed.append("PRDelta".lower())
        elif(i == "BellmanFord"):
            compressed.append("BF".lower())
        elif("xalancbmk" in i):
            compressed.append("xalanck")
        elif("perlbench" in i):
            compressed.append("perl")
        else:
            compressed.append(i.lower())
    return compressed

# Ignore
def print_ascii_table(heading, group_labels, data):
    # Determine if group_labels is empty (single group case)
    if not group_labels:
        group_labels = ["Value"]
    
    # Determine column widths
    col_widths = [max(len(bench) for bench in data.keys())]  # First column width
    col_widths += [max(len(f"{value:.5f}") for value in values) for values in zip(*data.values())]
    
    # Generate table separator
    separator = "=+=".join("=" * width for width in col_widths)
    
    # Print heading
    print("% " + heading)
    print("% " + separator)
    
    # Print header
    header = f"{'Benchmark'.ljust(col_widths[0])} || " + " | ".join(group_labels[i].ljust(col_widths[i + 1]) for i in range(len(group_labels)))
    print("% " + header)
    print("% " + separator)
    
    # Print each row
    for benchmark, values in data.items():
        row = f"{benchmark.ljust(col_widths[0])} || " + " | ".join(f"{values[i]:<{col_widths[i + 1]}.5f}" for i in range(len(values)))
        print("% "  + row)

# Ignore
def plot_multibar(data,group_labels ,savepath, is_mpki,ylabel="",round_to = 0.05, ytick_trim=1,delta_round = 0.01,delta_factor = 1):
    # Extracting the keys (workload names) and the values (list of measurements) from the data
    # Extract keys
    workloads = list(data.keys())

    # Remove and handle "average" and "geomean"
    special_keys = []
    for key in ["average", "geomean"]:
        if key in workloads:
            workloads.remove(key)
            special_keys.append(key)

    # Sort workloads and append special keys at the end
    if(is_number(workloads[0])):
        workloads = [float(workload) for workload in workloads]
    workloads_sorted = sorted(workloads) + special_keys
    workloads_sorted = [str(workload) for workload in workloads_sorted]

    # Get the indices that map workloads_sorted back to data
    ind = [list(data.keys()).index(w) for w in workloads_sorted]

    # Convert workloads to numpy array if needed
    workloads = np.array(workloads_sorted)

    # Reorder the values using ind
    values = np.array(list(data.values()))[ind]
    maximum = np.max(values)
    minimum = np.min(values)

    print(group_labels)
    print(data)
    print_ascii_table(os.path.basename(savepath),group_labels, data)
    print("Max:" , maximum)
    print("Min:", minimum)
    n_bars = len(workloads)
    n_sets = values.shape[1]  
    bar_width = min(min(0.3,0.8/ n_sets),n_bars*(0.04))  # Width of each bar, divided by the number of sets
    
    index = np.arange(n_bars)
    fig, ax = plt.subplots(figsize=(12, 6),constrained_layout = True)  # Fixed plot size (12x6 inches)
    
    # Plot each set of bars with grayscale colors
    for i in range(n_sets):
        # Grayscale shading: Ensure valid scaling for multiple sets
        gray_shade = 0.5 if n_sets == 1 else 1 - (i / max(1, n_sets))

        # Center bars around the index
        bar_position = index + (i - (n_sets - 1) / 2) * bar_width
        # Plot bars with edge coloring
        ax.bar(bar_position, values[:, i], bar_width, 
            label=(group_labels[i] if group_labels else ""), 
            color=str(gray_shade,), edgecolor='black', linewidth=1.5,zorder=5)
    # Add labels, title, and custom x-axis tick labels
    if ylabel=="":
        ylabel = "LLC MPKI" if is_mpki else "Speedup"
    ax.set_ylabel(ylabel, fontsize=28)

    tick_count = 10
   
    delta = int(((maximum - minimum )/tick_count)/delta_round)*delta_round*delta_factor

    print("Delta:", delta)
    plt.ylim(0.8, maximum + delta)
    ax.set_yticks(np.arange(0.8, maximum + delta, delta))

    
    ax.tick_params(axis='y', labelsize=20, labelcolor='black')
    plt.setp(ax.get_yticklabels(), fontweight=500)
    ax.set_xticks(index)
    ax.set_xticklabels(compress_workload_names(workloads), fontsize=26,rotation=60, ha='center',fontweight=500)  # Center labels under each group of bars
   
    ax.yaxis.set_major_formatter(FormatStrFormatter(f'%.{ytick_trim}f'))

    # Add a grid with dotted lines on the y-axis
    for spine in ax.spines.values():
        spine.set_zorder(10)
        spine.set_edgecolor('black')  # Set color of the border
        spine.set_linewidth(3)  # Set the thickness of the border

    # Add legend at the top of the plot
    
    if(n_sets >1):
        legend = ax.legend(loc='center',bbox_to_anchor=(0.5,1.15), ncol=n_sets,fontsize=26,edgecolor='black',fancybox=False, bbox_transform=ax.transAxes)
        legend.get_frame().set_linewidth(2)
        fig.subplots_adjust(top=0.8,left=0.1, right=0.9)
    else:
        legend = ax.legend(loc='center',bbox_to_anchor=(0.5,1.15), ncol=n_sets,fontsize=26,edgecolor='black',fancybox=False, bbox_transform=ax.transAxes)
        legend.get_frame().set_linewidth(0)
        fig.subplots_adjust(top=0.8,left=0.1, right=0.9)
    # Adjust layout to avoid overlap
    # plt.tight_layout()
    if(not is_mpki):
       plt.axhline(y=1, color='r', linestyle='dotted', linewidth=1.5)
    ax.grid(axis='y', linestyle=':', linewidth=1, color='black', alpha=0.5, zorder=1)
    ax.set_axisbelow(True)

    # plt.text(1.87,4,"0.01",fontsize=26,rotation=90)
    # plt.text(8.87,4,"0.01",fontsize=26,rotation=90)
    # plt.text(4.87,4,"0.05",fontsize=26,rotation=90)
    # Save the plot to the specified path
    plt.savefig(savepath,dpi = 800,bbox_inches='tight')
 
# Change here and replace with your actual data
# random_data["x"][i] = (IPC_BT=x, in workload i)/(IPC_BT=0, in workload i)
# i = 0 => bwaves, i = 1 => gcc, i = 2 => sssp, i = 3 => mcf
random_data = {
    "0.0": [1,1,1,1],
    "0.2": [1.00072, 1.00058, 1.12263, 1.17919],
    "0.4": [1.00072, 1.00058, 1.12437, 1.17893],
    "0.6": [1.00072,1.00058,1.10361,1.17855],
    "0.8": [1.00072,1.00058,1.10189,1.05747],
    "1.0": [1.00072,1.00058,1.10188,1.05731]    
}

# Try to make your plot as professional looking as possible
# The 'delta factor' here controls the difference between your consecutive yticks (0.2 in the given sample figure)
# Your code will print out "Delta: x", if you want delta to be y instead, delta_factor should be y/x
# In the case of the sample data, by default, delta was 0.16, I wanted it to be 0.2, hence delta factor is 0.2/0.16
# 'Round to' rounds all the values to the closest multiple of whatever you put in
plot_multibar(random_data, ["bwaves","gcc","sssp","mcf"],"./ipc_vs_bypass.pdf",is_mpki=False, delta_factor=10, round_to=0.2)
