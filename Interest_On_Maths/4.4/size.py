# -*- coding:utf-8 -*-
import numpy as np
import random
from numpy.linalg import *

if __name__ == '__main__':
	signal = 1
	rounds = 1
	while signal:
		mats = np.ones((4,4))
		sig = -1
		for i in range(4):
			for j in range(3):
				mats[i][j] = random.uniform(10,20)
		if det(mats) > 0:
			sig = 1

		nodes = []
		sigs = []
		for i in range(3):
			nodes.append(random.uniform(19,20))
		for i in range(4):
			temp_mat = mats.copy()
			for j in range(3):
				temp_mat[i][j] = nodes[j]
			if det(temp_mat) > 0:
				sigs.append(1)
			else:
				sigs.append(-1)

		for i in range(4):
			if sigs[i] != sig:
				signal = 1
				break
			elif i == 3:
				signal = 0
		rounds += 1

	print("After %d rounds,finally we find it!"%(rounds))