extends Node

@onready
var network = $GDNetworkTable

func _process(delta: float) -> void:
	print(network.push_value("test",1.234))
