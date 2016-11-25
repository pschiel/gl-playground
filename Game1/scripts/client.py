import gamelib

client = gamelib.Client()
client.start()

world = client.world
world.load("world1")



while client.state != "stopped":
	pass

