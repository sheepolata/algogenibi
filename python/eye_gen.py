#!/usr/bin/env python

import math
import random
import itertools

# random.seed(1875) #Math Domain Error with 666, 1875

w = 1.5 #cm, largeur max de l'oeil
I = math.exp(6) #Intensite lumineuse

CROSSOVER_RATE 	= 0.20
MUTATION_RATE 	= 0.01
MUTATION_CHANCE = 0.05
POP_SIZE		= 100
NB_GEN			= 100
PRECISION		= 0.00001

NB_MUTATION = 0
ID = 0

refract = {}

# TODO deal with the data in indice_refraction
def read_refract():
	global refract
	file = open("../indice_refraction_facile.dat", "r")
	# file = open("indice_refraction.dat", "r")
	i = 0
	for l in file:
		if i > 0:
			tmp = l.split()
			#Arbitrary take the first match in the file (the lowest value)
			if not float(tmp[1]) in refract :
				refract[round(float(tmp[1]), 3)] = float(tmp[0])
		i += 1

class parameter():
	def __init__(self, val, min, max, min_excl=True, max_excl=True):
		#TODO handel exclusive interval (prec 0.00001)
		if(not(min < max)):
			raise ValueError('Not a valid interval')
		if(not(val >= min and val <= max)):
			raise ValueError('Value not in interval')
		self.max 	= max
		self.min 	= min
		self.value 	= val

	def isValid(self):
		# print "value = ",self.value, "min = ",self.min
		if self.value > self.max:
			return False
		if self.value < self.min:
			# print self.value
			# print "EZIFHRZEIHFAIEFH"
			return False
		return True

	def display(self):
		print self.min, "<=", self.value, "<=", self.max

	def mutate(self): #TODO case 0.0
		change = (MUTATION_RATE/2.) - random.random() * MUTATION_RATE
		self.value *= 1 + change
		#TODO strict and death

class eye_to_be():
	def __init__(self):
		global ID
		self.id = ID
		ID += 1
		self.rho_c 	= parameter(10000., w/2., 10000.)
		self.i 		= parameter(0., 0., w/2.)
		self.phi_1	= parameter(0., 0., math.pi/2.)
		self.n0		= parameter(1.350, 1.350, 1.550) ##TODO return to default value (.dat issue)

	def paramAllValid(self):
		if not self.n0.isValid():
			return False
		if not self.rho_c.isValid():
			return False
		if not self.i.isValid():
			return False
		if not self.phi_1.isValid():
			return False
		return True

	def display(self):
		print "rho_c =",self.rho_c.value, "i =",self.i.value, "phi_1 =", self.phi_1.value, "n0 =", self.n0.value

	def p(self):
		if self.rho_c.value > (w/2.):
			return self.rho_c.value - math.sqrt(self.rho_c.value**2 - (w**2)/4.)
		elif self.rho_c.value == (w/2.) :
			return (w/2.) * (1 + math.sin(self.phi_1.value))

	def a(self):
		if self.rho_c.value > (w/2.):
			return w - 2*self.i.value
		elif self.rho_c.value == (w/2.) :
			return w * math.cos(self.phi_1.value) - 2.*self.i.value

	def r1(self):
		return refract[round(self.n0.value, 3)]

	def teta(self):
		if round(self.n0.value, 3) == 1.35:
			return 2. * math.atan(self.a() / (2. * self.p()))
		elif round(self.n0.value, 3) > 1.35:
			x 			= self.r1()**2. * self.a() / (2. * self.p())
			y 			= 1 + self.r1()**2. - self.r1()**2. * self.a()**2. / (4. * (self.p()**2.))
			self.display()
			self.rho_c.display()
			numerator 	= x - math.sqrt(y)
			denominator	= 1 + self.r1()**2.
			return 2 * math.asin(numerator / denominator)

	def isDead(self):
		if not self.paramAllValid():
			return True
		d1 = self.phi_1.value != 0 and self.rho_c.value != (w/2.)
		d2 = self.phi_1.value != 0 and self.i.value > (w * (math.cos(self.phi_1.value))/2.)
		d3 = round(self.n0.value, 3) != 1.35 and (self.p() > (self.r1() * (self.a() / 2.)) or self.p() < self.a()/2.)
		return d1 or d2 or d3

	#nu
	def v(self):
		if round(self.n0.value, 3) == 1.35:
			root = math.sqrt( math.log( 0.746 * self.a()**2 * math.sqrt(I) ) )
			return 0.375 * (self.p() / self.a()) * root
		elif round(self.n0.value, 3) > 1.35:
			return 1. / self.teta()


def random_pick(some_list, probabilities):
    x = random.uniform(0, 1)
    cumulative_probability = 0.0
    for item, item_probability in zip(some_list, probabilities):
        cumulative_probability += item_probability
        if x < cumulative_probability: break
    return item

def breed(p1, p2):
	cross = random.random()
	child = eye_to_be()
	if cross < CROSSOVER_RATE:
		#cross over
		rnd = random.random()
		if rnd < 0.5:
			child.rho_c	= p1.rho_c
		else:
			child.rho_c	= p2.rho_c
		rnd = random.random()
		if rnd < 0.5:
			child.i	= p1.i
		else:
			child.i	= p2.i
		rnd = random.random()
		if rnd < 0.5:
			child.phi_1	= p1.phi_1
		else:
			child.phi_1	= p2.phi_1
		rnd = random.random()
		if rnd < 0.5:
			child.n0	= p1.n0
		else:
			child.n0	= p2.n0
	else:
		#not cross over
		rnd = random.random()
		if rnd < 0.5:
			child.rho_c 	= p1.rho_c
			child.i 		= p1.i
			child.phi_1 	= p1.phi_1
			child.n0 		= p1.n0
		else:
			child.rho_c 	= p2.rho_c
			child.i 		= p2.i
			child.phi_1 	= p2.phi_1
			child.n0		= p2.n0

	rnd = random.random()
	if rnd < MUTATION_CHANCE:
		global NB_MUTATION
		NB_MUTATION += 1
		child.rho_c.mutate()
		child.i.mutate()
		child.phi_1.mutate()
		child.n0.mutate()

	return child

def algo_gen():
	tmp = 0
	#Generate the first generation
	pop = []
	for i in range(POP_SIZE):
		pop.append(eye_to_be())
	#For all generations
	for i in range(NB_GEN):
		print "Generation ", i
		#Fitness computation
		fitness = []
		for p in pop:
			fitness.append(p.v())
		# print fitness
		_sum = sum(fitness[:])
		#Probability to be picked for each individual
		proba = []
		for j in range(len(fitness)):
			#TODO see round
			# proba.append(round(fitness[j] / _sum, 5))
			proba.append(fitness[j] / _sum)
		#Create the children
		new_pop = []
		print "gen", i, " WHILE"
		while len(new_pop) < POP_SIZE:
			#Pick two different parents
			parent_1 = random_pick(pop, proba)
			parent_2 = random_pick(pop, proba)
			# print sorted(proba)
			while parent_1.id == parent_2.id:
				# tmp+=1
				# print tmp
				parent_2 = random_pick(pop, proba)

			child = breed(parent_1, parent_2)
			tmp += 1
			if not child.isDead():
				print "OK", i, tmp
				new_pop.append(child)
			#TODO clean pig
			to_rm = []
			for p in new_pop:
				if p.isDead():
					to_rm.append(p)
			for p in to_rm:
				new_pop.remove(p)
		print "gen", i, " END WHILE"
		print "END generation", i
		pop = new_pop



		

read_refract()
algo_gen()
