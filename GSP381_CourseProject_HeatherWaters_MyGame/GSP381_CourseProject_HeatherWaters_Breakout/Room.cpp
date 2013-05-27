#include "Model.h"
#include "Room.h"

Room::Room(void)
{
}


Room::~Room(void)
{
}

bool Room::init(LPDIRECT3DDEVICE9 device)
{
	room = new Model();
	// load room
	room->loadModel(device, L"RoomFinal.x");
	// set the scale of the room
	room->setScale(D3DXVECTOR3(0.02f, 0.02f, 0.02f));

	return true;
}

void Room::render(LPDIRECT3DDEVICE9 device)
{
	room->setPosition(D3DXVECTOR3(0, -11, 18));
	//room->setRotation(D3DXVECTOR3(rotationY, 0, 0));
	room->render(device);
}

void Room::update()
{
}
