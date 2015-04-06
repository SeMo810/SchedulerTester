import plotly.plotly as PLOT
from plotly.graph_objs import *
import io

INPUT_FILES = [
    "cpu_s_fifo", "cpu_s_other", "cpu_s_rr", "cpu_m_fifo", "cpu_m_other", "cpu_m_rr", "cpu_l_fifo", "cpu_l_other", "cpu_l_rr",
    "io_s_fifo", "io_s_other", "io_s_rr", "io_m_fifo", "io_m_other", "io_m_rr", "io_l_fifo", "io_l_other", "io_l_rr",
    "mx_s_fifo", "mx_s_other", "mx_s_rr", "mx_m_fifo", "mx_m_other", "mx_m_rr", "mx_l_fifo", "mx_l_other", "mx_l_rr"
]

CONTEXT_X_LABELS = [
    "CPU SMALL", "CPU MEDIUM", "CPU LARGE",
    "IO SMALL", "IO MEDIUM", "IO LARGE",
    "MIX SMALL", "MIX MEDIUM", "MIX LARGE"
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

# invol and vol needs to be in the order:
# cpu -> io -> mixed and small -> medium -> large
def make_context_graph(sched, invol, vol):
    vgraph = Bar(
        x = CONTEXT_X_LABELS,
        y = vol,
        name = "Voluntary Switches",
        marker = Marker(
            color = "rgb(255, 0, 0)"
        )
    )
    igraph = Bar(
        x = CONTEXT_X_LABELS,
        y = invol,
        name = "Involuntary Switches",
        marker = Marker(
            color = "rgb(0, 0, 255)"
        )
    )
    data = Data([vgraph, igraph])
    layout = Layout(
        title = "Context Switches for " + sched,
        xaxis = XAxis(
            title = "Program Type and Size",
            titlefont = Font(
                size = 16,
                color = "rgb(0, 0, 0)"
            ),
            tickfont = Font(
                size = 14,
                color = "rgb(0, 0, 0)"
            )
        ),
        yaxis = YAxis(
            title = "Number of Context Switches",
            type = "log",
            rangemode = "tozero",
            titlefont = Font(
                size = 16,
                color = "rgb(0, 0, 0)"
            ),
            tickfont = Font(
                size = 14,
                color = "rgb(0, 0, 0)"
            )
        ),
        legend = Legend(
            x = 0,
            y = 1.0,
            bgcolor = "rgb(255, 255, 255, 0)",
            bordercolor = "rgb(0, 0, 0, 127)"
        ),
        barmode = "group"
    )
    PLOT.image.save_as({'data' : data, 'layout' : layout}, "report/context_" + sched + ".png")

# utime and rtime need the order:
# cpu -> io -> mix and small -> medium -> large
def make_time_graph(sched, utime, rtime):
    vgraph = Bar(
        x = CONTEXT_X_LABELS,
        y = utime,
        name = "User Time",
        marker = Marker(
            color = "rgb(255, 0, 0)"
        )
    )
    igraph = Bar(
        x = CONTEXT_X_LABELS,
        y = rtime,
        name = "Real Time",
        marker = Marker(
            color = "rgb(0, 0, 255)"
        )
    )
    data = Data([vgraph, igraph])
    layout = Layout(
        title = "User and Real Time for " + sched,
        xaxis = XAxis(
            title = "Program Type and Size",
            titlefont = Font(
                size = 16,
                color = "rgb(0, 0, 0)"
            ),
            tickfont = Font(
                size = 14,
                color = "rgb(0, 0, 0)"
            )
        ),
        yaxis = YAxis(
            title = "Time (seconds)",
            titlefont = Font(
                size = 16,
                color = "rgb(0, 0, 0)"
            ),
            tickfont = Font(
                size = 14,
                color = "rgb(0, 0, 0)"
            )
        ),
        legend = Legend(
            x = 0,
            y = 1.0,
            bgcolor = "rgb(255, 255, 255, 0)",
            bordercolor = "rgb(0, 0, 0, 127)"
        ),
        barmode = "group"
    )
    PLOT.image.save_as({'data' : data, 'layout' : layout}, "report/time_" + sched + ".png")

def main():
    results = []
    for filename in INPUT_FILES:
        data = extract_data(filename)
        results.append(data)
    # Make the context switch graphs
    fifo_vol = [ results[0][6], results[3][6], results[6][6], results[9][6], results[12][6], results[15][6], results[18][6], results[21][6], results[24][6] ]
    other_vol = [ results[1][6], results[4][6], results[7][6], results[10][6], results[13][6], results[16][6], results[19][6], results[22][6], results[25][6] ]
    rr_vol = [ results[2][6], results[5][6], results[8][6], results[11][6], results[14][6], results[17][6], results[20][6], results[23][6], results[26][6] ]
    fifo_ivol = [ results[0][7], results[3][7], results[6][7], results[9][7], results[12][7], results[15][7], results[18][7], results[21][7], results[24][7] ]
    other_ivol = [ results[1][7], results[4][7], results[7][7], results[10][7], results[13][7], results[16][7], results[19][7], results[22][7], results[25][7] ]
    rr_ivol = [ results[2][7], results[5][7], results[8][7], results[11][7], results[14][7], results[17][7], results[20][7], results[23][7], results[26][7] ]
    make_context_graph("FIFO", fifo_ivol, fifo_vol)
    make_context_graph("OTHER", other_ivol, other_vol)
    make_context_graph("RR", rr_ivol, rr_vol)
    # Make the time graphs
    fifo_utime = [ results[0][3] / 10, results[3][3] / 100 , results[6][3] / 1000, results[9][3] / 10, results[12][3] / 100, results[15][3] / 1000,
        results[18][3] / 10, results[21][3] / 100, results[24][3] / 1000 ]
    other_utime = [ results[1][3] / 10, results[4][3] / 100, results[7][3] / 1000, results[10][3] / 10, results[13][3] / 100, results[16][3] / 1000,
        results[19][3] / 10, results[22][3] / 100, results[25][3] / 1000 ]
    rr_utime = [ results[2][3] / 10, results[5][3] / 100, results[8][3] / 1000, results[11][3] / 10, results[14][3] / 100, results[17][3] / 1000,
        results[20][3] / 10, results[23][3] / 100, results[26][3] / 1000 ]
    fifo_rtime = [ results[0][5] / 10, results[3][5] / 100 , results[6][5] / 1000, results[9][5] / 10, results[12][5] / 100, results[15][5] / 1000,
        results[18][5] / 10, results[21][5] / 100, results[24][5] / 1000 ]
    other_rtime = [ results[1][5] / 10, results[4][5] / 100, results[7][5] / 1000, results[10][5] / 10, results[13][5] / 100, results[16][5] / 1000,
        results[19][5] / 10, results[22][5] / 100, results[25][5] / 1000 ]
    rr_rtime = [ results[2][5] / 10, results[5][5] / 100, results[8][5] / 1000, results[11][5] / 10, results[14][5] / 100, results[17][5] / 1000,
        results[20][5] / 10, results[23][5] / 100, results[26][5] / 1000 ]
    make_time_graph("FIFO", fifo_utime, fifo_rtime)
    make_time_graph("OTHER", other_utime, other_rtime)
    make_time_graph("RR", rr_utime, rr_rtime)

main()
