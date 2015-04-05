import plotly.plotly as PLOT
from plotly.graph_objs import *
import io

INPUT_FILES = [
    "cpu_s_fifo", "cpu_s_other", "cpu_s_rr", "cpu_m_fifo", "cpu_m_other", "cpu_m_rr", "cpu_l_fifo", "cpu_l_other", "cpu_l_rr",
    "io_s_fifo", "io_s_other", "io_s_rr", "io_m_fifo", "io_m_other", "io_m_rr", "io_l_fifo", "io_l_other", "io_l_rr",
    "mx_s_fifo", "mx_s_other", "mx_s_rr", "mx_m_fifo", "mx_m_other", "mx_m_rr", "mx_l_fifo", "mx_l_other", "mx_l_rr"
]

# This function reads in the data from the file, and returns it in the form of:
# [ program type (string), size (string), sched type (string), user time (float), kernel time (float), real time (float), voluntary switches (integer), involuntary switches (integer)]
def extract_data(name):
    data = None
    with open("results/" + name + ".res", "r") as data_file:
        data = data_file.read()
    if data == None or data == "":
        print("Failed to read data from the file", name)
        return None
    data = data.split("\n")
    fileSplit = name.split('_')
    _ptype = fileSplit[0]
    _psize = fileSplit[1]
    _psched = fileSplit[2]
    # User time
    pos = data[1].rfind(":")
    _pusertime = float(data[1][pos+2:len(data[1])])
    # Kernel time
    pos = data[2].rfind(":")
    _pkerntime = float(data[2][pos+2:len(data[2])])
    # Real time
    pos = data[4].rfind(":")
    realMinute = int(data[4][pos-1:pos])
    realSecond = int(data[4][pos+1:pos+3])
    realMSecond = int(data[4][pos+4:pos+6])
    _prealtime = (realMinute * 60) + realSecond + (realMSecond * 0.01)
    # Voluntary switches
    pos = data[13].rfind(":")
    _pvolswitch = int(data[13][pos+1:len(data[13])])
    # Involuntary switches
    pos = data[14].rfind(":")
    _pivolswitch = int(data[14][pos+1:len(data[14])])
    return [ _ptype, _psize, _psched, _pusertime, _pkerntime, _prealtime, _pvolswitch, _pivolswitch ]

def main():
    results = []
    for filename in INPUT_FILES:
        data = extract_data(filename)
        print(data)
        results.append(data)

main()
