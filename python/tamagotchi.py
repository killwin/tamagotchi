from time import *

class Tamagotchi:

	def __init__(self, name):
		self.name = name
		self.state = "eeg"
		self.day_night = "night"
		self.hour = 0
		self.born = time()
		self.angry = 0
		self.thirst = 0
		self.tired = 0
		self.mood = 0
		self.prety = 0
		self.angry_speed = 0

	def age(self):
		return time() - self.born

	def update(self):
		
		self.hour = localtime().tm_hour
		
		if self.state <> "eeg":
			self.angry = self.angry_speed * 86400 - self.age()
			self.thirst = self.thirst_speed * 86400 - self.age()
		
		if self.hour > 8 and self.hour < 17:
			self.day_night = "day"
		elif self.hour < 22:
			self.day_night = "twilight"
		else:
			self.day_night = "night"

		if self.angry < 0 or self.thirst < 0:
			self.state = "death"

class subspecies_01(Tamagotchi):
	
	def __init__(self, name):
		Tamagotchi.__init__(self, name)
		self.angry_speed = 1
		self.thirst_speed = 1.5
		self.prety = 1
		self.mood = 1
	
	def update(self):

		Tamagotchi.update(self)
		
		if self.angry < 3000 or self.thirst < 3000:
			self.mood -= .1
			
		if self.mood < .5:
			self.prety -= .1
			
toto = subspecies_01('toto')
toto.update();

