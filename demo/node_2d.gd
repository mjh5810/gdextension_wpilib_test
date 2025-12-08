extends Node
# Main scene.

var server : UDPServer

@export var displaySurface : TextureRect

func _ready():
	server = UDPServer.new()
	server.listen(1337)

func _process(_delta):
	server.poll()
	if server.is_connection_available():
		var peer = server.take_connection()
		var packet = peer.get_packet()
		#print(packet.get_string_from_ascii())
		var peerImage = texture_from_packet(packet)
		var peerImageTexture = ImageTexture.create_from_image(peerImage)
		displaySurface.texture = peerImageTexture
	else:
		pass
		#print("No connection")
	
func texture_from_packet(packet : PackedByteArray):
	var im = Image.new()
	im.load_jpg_from_buffer(packet)
	return im
