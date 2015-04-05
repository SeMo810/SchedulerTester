# SchedulerTester
A series of programs that gathers runtime data from different scheduling processes, and generates data and graphs based on the data. It also includes my final report. This is for the CSCI 3753 class.

### Structure of Repo
* `test.sh` - Runs the tests, and generates the output files.
* `programs` - The source code for the programs.
* `report` - The directory where all of my final files and report is.

### How to Run
All of this should be done from the root directory.

* Run `./test.sh`, this will run the tests on each program, with each count of children, and with each scheduler policy.
  * This will output files to a `results` folder.
* Run `python graph.py`, this will generate the final graphs and put them into the report directory.
  * **NOTE**: You need to install plot.ly in the python libraries, using `sudo pip install plotly` for this to work.
