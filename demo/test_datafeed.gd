extends CSGBox3D

@onready
var network = $GDNetworkTable

func _process(_delta):
	var x = network.fetch_value("xRot")
	var y = network.fetch_value("yRot")
	var z = network.fetch_value("zRot")
	rotation = Vector3(network.fetch_value("xRot"), network.fetch_value("yRot"), network.fetch_value("zRot"))
