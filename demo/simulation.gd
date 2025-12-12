extends Node2D

@onready var nt : GDNetworkTable = $GDNetworkTable

func _process(_delta):
	position = Vector2(nt.fetch_double("x"),nt.fetch_double("y"))
	rotation = nt.fetch_double("rot")
