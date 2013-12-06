Breakdown of Tasks:

Terrain Generator: Tyler
	Uses simplex noise to generate a randomized map. Height map and water level is sent to Ricky's cellular automata program.

Forest.py: Ricky
	Generates a forest using cellular automata rules. Gui ties together all 3 parts of the program.

Forest Renderer (newforest): Tyler handled processing the tree data  from the forest generator, and we 	collaborated on spawning the correct trees in each square of the map.

