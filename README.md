boggle
======
Notes about the current state of the boggle program.

Compiler: Visual Studio 2010
Target Platform: Win32

Improvements
	* can be any width & depth for a board as long as all widths are the same length
	* attempts to correct in coming data from dictionary (trim, case, reject non-alpha words)
	* code should be warn free
	* optimization: graph searches stop when word target grows to largest dictionary word size

Limitations
	* when loading a files that encounters a dictionary word longer than 256, the load will stop but continue with a smaller dictionary

Future Improvements
	* could try to use threads to solve it faster, but currently solves in less than 3 seconds for either supplied board (release mode)
	* run metrics on different kinds of dictionaries and graph traversals to find the best algorithms

Frameworks to introduce
	* some kind of unit testing framework
	* some kind of logging framework to manage logging output
	* some kind of options framework to handle runtime configurations
	* some kind of metrics framework to measure the suspected hot spots

