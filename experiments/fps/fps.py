from SimpleCV import Camera
cam = Camera()
while True:
	img = cam.getImage()
	img.show()
	print cam.getAllProperties()